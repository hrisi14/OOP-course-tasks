#include "Utils.h"

void printSymbol(char symbol, unsigned numberOfTimes)
{
	for (unsigned i = 0; i < numberOfTimes; i++)
	{
		std::cout << symbol;
	}
}

bool isEmptyLine(const char* fieldStr)
{
	for (int i = 0; fieldStr[i] != '\0'; i++)   //removing empty lines 
	{
		if (fieldStr[i] != ' ')
		{
			return false;
		}
	}
	return true;
}