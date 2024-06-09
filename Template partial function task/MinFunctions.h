#pragma once
#include "PFOperation.h"

class MinFunctions : public PFOperation
{
public:
	MinFunctions(const PartialFunction** newFunctions, uint16_t size);
	MinFunctions(PartialFunction**&& newFunctions, uint16_t size);
	bool isDefined(int x) const override;
	int evaluate(int x) const override;
	PartialFunction* clone() const override;
};

