#pragma once
#include <iostream>
#include <fstream>
#pragma warning (disable:4996)
#include "Utils.h"

struct Field
{
	char field[GlobalConstants::FIELD_MAX_SIZE] = " ";
	bool isHeading = false;

	Field() = default;
	Field(const char* value);
	void printField(size_t maxColumnLen) const;
	void saveFieldToFile(std::ofstream& ofs) const;
};

