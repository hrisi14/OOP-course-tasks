#include "MinFunctions.h"

MinFunctions::MinFunctions(const PartialFunction** newFunctions, uint16_t size) : PFOperation(newFunctions, size)
{}

MinFunctions::MinFunctions(PartialFunction**&& newFunctions, uint16_t size) : PFOperation(std::move(newFunctions), size)
{}

bool MinFunctions::isDefined(int x) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (!functions[i]->isDefined(x))
		{
			return false;   
		}
	}
	return true;
}

int MinFunctions::evaluate(int x) const
{
	if (!isDefined(x))
	{
		throw std::exception("Error! The function is not defined in the point given!");
	}
	
		int minResult = INT_MAX;  

		for (size_t i = 0; i < size; i++)
		{
			if (functions[i]->evaluate(x) < minResult)
			{
				minResult = functions[i]->evaluate(x);
			}
		}
		return minResult;
}

PartialFunction* MinFunctions::clone() const
{
	return new MinFunctions(*this);
}

