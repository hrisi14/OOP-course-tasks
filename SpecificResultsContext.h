#pragma once
#include "Context.h"

class SpecificResultsContext : public Context
{
public:
	SpecificResultsContext(const Pair<int, int>* newNumbers, size_t count);
	Pair<bool, int> operator()(int x) const override;
	Context* clone() const override;

private:
	Pair<int, int> numbers[GlobalConstants::MAX_NUMBERS];
	size_t count;
};

