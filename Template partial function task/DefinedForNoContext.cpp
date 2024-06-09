#include "DefinedForNoContext.h"

DefinedForNoContext::DefinedForNoContext(const int* newNumbers, size_t count)
{
	this->count = count;

	for (size_t i = 0; i < count; i++)
	{
		this->numbers[i] = newNumbers[i];
	}
}

Pair<bool, int> DefinedForNoContext::operator()(int x) const
{
	for (size_t i = 0; i < count; i++)
	{
		if (x == numbers[i])
		{
			return Pair<bool, int>(false, -1);   //To do: find an appropriate invalid value!
		}
	}
	return Pair<bool, int>(true, x);
}

Context* DefinedForNoContext::clone() const
{
	return new DefinedForNoContext(*this);
}
