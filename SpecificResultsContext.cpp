#include "SpecificResultsContext.h"

SpecificResultsContext::SpecificResultsContext(const Pair<int, int>* newNumbers, size_t count)
{
	this->count = count;

	for (size_t i = 0; i < count; i++)
	{
		this->numbers[i] = newNumbers[i];
	}
}

Pair<bool, int> SpecificResultsContext::operator()(int x) const
{
	for (size_t i = 0; i < count; i++)
	{
		if (x == numbers[i].getFirst())
		{
			return Pair<bool, int>(true, numbers[i].getSecond());   
		}
	}
	return Pair<bool, int>(false, -1);   //To do: find an appropriate invalid value!
}

Context* SpecificResultsContext::clone() const
{
	return new SpecificResultsContext(*this);
}

