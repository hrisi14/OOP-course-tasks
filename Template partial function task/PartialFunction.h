#pragma once
#include <iostream>
#include <iomanip>

class PartialFunction
{
public:
	virtual bool isDefined(int x) const = 0;
	virtual int evaluate(int x) const = 0;
	virtual PartialFunction* clone() const = 0;
	virtual ~PartialFunction() = default;
};

