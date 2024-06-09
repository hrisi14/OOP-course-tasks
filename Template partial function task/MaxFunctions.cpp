#include "MaxFunctions.h"


MaxFunctions::MaxFunctions(const PartialFunction** newFunctions, uint16_t size): PFOperation(newFunctions, size)
{}

MaxFunctions::MaxFunctions(PartialFunction**&& newFunctions, uint16_t size):PFOperation(std::move(newFunctions), size)
{}

bool MaxFunctions::isDefined(int x) const
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

int MaxFunctions::evaluate(int x) const
{
	if (!isDefined(x))
	{
		throw std::exception("Error! The function is not defined in the point given!");
	}
	
		int maxResult = INT_MIN; 

		for (size_t i = 0; i < size; i++)
		{
			if (functions[i]->evaluate(x)>maxResult)
			{
				maxResult = functions[i]->evaluate(x);
			}
		}
		return maxResult;	
}

PartialFunction* MaxFunctions::clone() const
{
	return new MaxFunctions(*this);
}
