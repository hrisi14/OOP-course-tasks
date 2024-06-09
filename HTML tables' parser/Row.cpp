#include "Row.h"

Row::Row(const char values[GlobalConstants::MAX_FIELDS_ROW][GlobalConstants::FIELD_MAX_SIZE], size_t numberOfFields)
{
	if (numberOfFields < GlobalConstants::MAX_FIELDS_ROW)
	{
		for (size_t i = 0; i < numberOfFields; i++)
		{
			strcpy(fields[i].field, values[i]);
		}
	}
	fieldsCount = numberOfFields;
}

void Row::printRow(const size_t colLens[GlobalConstants::MAX_FIELDS_ROW]) const
{
	std::cout << std::endl;
	for (size_t i = 0; i < fieldsCount; i++)
	{
		std::cout << "|";
		fields[i].printField(colLens[i]);
	}
	std::cout<<"|";
}

void Row::saveRowToFile(std::ofstream& ofs) const
{
	ofs << "<tr>" << std::endl;
	for (size_t i = 0; i < fieldsCount; i++)
	{
		fields[i].saveFieldToFile(ofs);
	}
	ofs << "</tr>" << std::endl;
}
