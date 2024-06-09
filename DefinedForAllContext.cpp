#include "DefinedForAllContext.h"


DefinedForAllContext::DefinedForAllContext(const int* newNumbers, size_t count)
{
	this->count = count;

	for (size_t i = 0; i < count; i++)
	{
		this->numbers[i] = newNumbers[i];
	}
}

Pair<bool, int> DefinedForAllContext::operator()(int x) const
{
	for (size_t i = 0; i < count; i++)
	{
		if (x == numbers[i])
		{
			return Pair<bool, int>(true, 1);   //To do: find an appropriate invalid value
		}
	}
	return Pair<bool, int>(true, 0);
}

Context* DefinedForAllContext::clone() const
{
	return new DefinedForAllContext(*this);
}