#pragma once
#include "PFOperation.h"

class MaxFunctions: public PFOperation
{
public:
	MaxFunctions(const PartialFunction** newFunctions, uint16_t size);
	MaxFunctions(PartialFunction**&& newFunctions, uint16_t size);
	bool isDefined(int x) const override;
	int evaluate(int x) const override;
	PartialFunction* clone() const override;
};

