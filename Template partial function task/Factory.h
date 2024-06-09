#pragma once
#include <iostream>
#include<fstream>
#include <iomanip>
#include "PFByCriteria.hpp"
#include "DefinedForAllContext.h"
#include "DefinedForNoContext.h"
#include "SpecificResultsContext.h"
#include "MaxFunctions.h"
#include "MinFunctions.h"

class Factory
{
public:
	PartialFunction* functionsFactory(const char* fileName);
};

