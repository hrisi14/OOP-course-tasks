#include "Factory.h"

PFByCriteria<DefinedForAllContext>* readDefinedForAllContextFunction(std::ifstream& ifs)
{
	uint16_t size;
	int numbers[GlobalConstants::MAX_NUMBERS];
	ifs.read((char*)&size, sizeof(uint16_t));
	ifs.read((char*)numbers, size * sizeof(int));

	return new PFByCriteria<DefinedForAllContext>(DefinedForAllContext(numbers, size));
}

PFByCriteria<DefinedForNoContext>* readDefinedForNoContextFunction(std::ifstream& ifs)
{
	uint16_t size;
	int numbers[GlobalConstants::MAX_NUMBERS];
	ifs.read((char*)&size, sizeof(uint16_t));
	ifs.read((char*)numbers, size * sizeof(int));

	return new PFByCriteria<DefinedForNoContext>(DefinedForNoContext(numbers, size));
}

PFByCriteria<SpecificResultsContext>* readSpecificResultsFunction(std::ifstream& ifs)
{
	uint16_t size;
	int arguments[GlobalConstants::MAX_NUMBERS];
	int results[GlobalConstants::MAX_NUMBERS];

	ifs.read((char*)&size, sizeof(uint16_t));
	ifs.read((char*)arguments, size * sizeof(int));
	ifs.read((char*)results, size * sizeof(int));

	Pair<int, int> pairs[GlobalConstants::MAX_NUMBERS];

	for (size_t i = 0; i < size; i++)
	{
		pairs[i] = Pair<int, int>(arguments[i], results[i]);
	}

	return new PFByCriteria<SpecificResultsContext>(SpecificResultsContext(pairs, size));
}

PartialFunction** getPartialFunctionsFromFile(std::ifstream& ifs, uint16_t& size)
{
	ifs.read((char*)&size, sizeof(uint16_t));

	Factory f;
	PartialFunction** functions = new PartialFunction * [size];

	char buffer[GlobalConstants::MAX_BUFF];

	for (size_t i = 0; i < size; i++)
	{
		ifs.getline(buffer, GlobalConstants::MAX_BUFF, GlobalConstants::SEPARATOR);
		functions[i] = f.functionsFactory(buffer);
	}

	return functions;
}

void freeTempFunctions(PartialFunction** functions, uint16_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		delete functions[i];
	}
	delete[] functions;
}

MaxFunctions* readMaxFunctions(std::ifstream& ifs)
{
	uint16_t size;
	PartialFunction** functions = getPartialFunctionsFromFile(ifs, size);
	MaxFunctions* maxFunc = new MaxFunctions(std::move(functions), size);

	freeTempFunctions(functions, size);
	return maxFunc;
}

MinFunctions* readMinFunctions(std::ifstream& ifs)
{
	uint16_t size;
	PartialFunction** functions = getPartialFunctionsFromFile(ifs, size);
	MinFunctions* minFunc = new MinFunctions(std::move(functions), size);

	freeTempFunctions(functions, size);
	return minFunc;
}

PartialFunction* Factory::functionsFactory(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open())
	{
		throw std::exception("Error! File could not be opened!");
	}

	uint16_t T;   //determines file's content
	ifs.read((char*)&T, sizeof(uint16_t));

	PartialFunction* result;
	switch (T)
	{
	case 0: result = readSpecificResultsFunction(ifs); break;
	case 1: result = readDefinedForNoContextFunction(ifs); break;
	case 2: result = readDefinedForAllContextFunction(ifs); break;
	case 3: result = readMaxFunctions(ifs); break;
	case 4: result = readMinFunctions(ifs); break;
	default: ifs.close();  throw std::exception("A run-time error occurred! Invalid file's content parameter!"); break;
	}
	ifs.close();
	return result;
}
