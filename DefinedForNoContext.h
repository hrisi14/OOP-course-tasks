#pragma once
#include "Context.h"

class DefinedForNoContext: public Context
{
public:
	DefinedForNoContext(const int* newNumbers, size_t count);
	Pair<bool, int> operator()(int x) const override;
	Context* clone() const override;

private:
	int numbers[GlobalConstants::MAX_NUMBERS];
	size_t count;
};

