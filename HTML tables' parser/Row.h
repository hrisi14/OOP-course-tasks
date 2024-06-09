#pragma once
#include "Field.h"

struct Row
{
	Field fields[GlobalConstants::MAX_FIELDS_ROW];
	size_t fieldsCount = 0;

	Row() = default;
	Row(const char values[GlobalConstants::MAX_FIELDS_ROW][GlobalConstants::FIELD_MAX_SIZE], size_t numberOfFields);
	void printRow(const size_t colLens[GlobalConstants::MAX_FIELDS_ROW]) const;
	void saveRowToFile(std::ofstream& ofs) const;
};

