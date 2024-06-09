#include "Table.h"

void Table::parseField(const char* fieldStr, size_t& rowIndex, size_t& colIndex)
{
	std::stringstream ss(fieldStr, std::ios::in);
	char resultField[GlobalConstants::FIELD_MAX_SIZE] = "/0";
	size_t arrIndex = 0;

	while (true)
	{
		char ch = ss.get();
		if (ss.eof())
		{
			break;
		}
		if (ch == '&') //the flag for an alternative coding reference
		{
			ss.ignore();  //ignores the '#'
			int number;
			ss >> number; //get the ASCII code of the char only
			ch = number;
		}
		resultField[arrIndex++] = ch;
	}	
	strcpy(rows[rowIndex].fields[colIndex].field, resultField);
}

void Table::parseRow(const char* rowStr, size_t& rowIndex, size_t& colIndex)   //changes columnsCount as well
{
	std::stringstream ss(rowStr);
	char fieldStr[GlobalConstants::FIELD_MAX_SIZE];

	while (!ss.eof())
	{
		ss.getline(fieldStr, GlobalConstants::FIELD_MAX_SIZE);		
		if (isEmptyLine(fieldStr))
		{
			continue;
		}
		colLens[colIndex] = std::max(colLens[colIndex], strlen(fieldStr));			
		parseField(fieldStr, rowIndex, colIndex);
		colIndex++;
	}
}

void Table::parseFromFile(std::ifstream& ifs)   
{
	size_t rowIndex = 0;
	size_t colIndex = 0;

	char buff[GlobalConstants::BUFFER_SIZE];
	char tag[GlobalConstants::TAG_LEN];   

	while (!ifs.eof())
	{
		ifs.getline(tag, 10, '>');  //reads the tag itself

		if (strcmp(tag, GlobalConstants::TABLE_TAG) == 0)
		{
			continue;
		}
		if (strcmp(tag, GlobalConstants::ROW_TAG_CLOSE) == 0)
		{
			rowIndex++;
			colIndex = 0;			
		}

		if (strcmp(tag, GlobalConstants::HEADER_TAG1) == 0 || strcmp(tag, GlobalConstants::HEADER_TAG2) == 0)   
		{
			rows[rowIndex].fields[colIndex].isHeading = true;   //needed when printing the separate header fields			
		}	
		ifs.getline(buff, GlobalConstants::BUFFER_SIZE, '<');   //reads the content between two tags		
		parseRow(buff, rowIndex, colIndex);		
		columnsCount = std::max(columnsCount, colIndex);
		rows[rowIndex].fieldsCount = columnsCount;
		rowsCount = std::max(rowsCount, rowIndex);
	}
}

bool Table::parseFromFile(const char* fileName)
{
	std::ifstream ifs(fileName, std::ios::in);
	if (!ifs.is_open())
	{
		return false;
	}
	parseFromFile(ifs);
	ifs.close();
	return true;
}

void Table::upgradeColLens(const Row& newRow)
{
	for (size_t i = 0; i < newRow.fieldsCount; i++)
	{		
	  colLens[i] = std::max(colLens[i], strlen(newRow.fields[i].field));	
	}
}

bool Table::addRow(size_t rowNumber, const char values[GlobalConstants::MAX_FIELDS_ROW][GlobalConstants::FIELD_MAX_SIZE], size_t numberOfFields)
{
	if (rowsCount >= GlobalConstants::MAX_ROWS_TABLE || numberOfFields>=GlobalConstants::MAX_FIELDS_ROW)
	{
		return false;
	}

	Row newRow(values, numberOfFields);	
	upgradeColLens(newRow);
	columnsCount = std::max(columnsCount, numberOfFields);
	rows[rowsCount++] = newRow;

	return true;
}

bool Table::removeRow(size_t rowIndex)
{
	if (rowIndex<0 || rowIndex>rowsCount)
	{
		return false;
	}
	std::swap(rows[rowIndex], rows[rowsCount]);
	rowsCount--;
	return true;
}

size_t Table::getRowsCount() const
{
	return rowsCount;
}

size_t Table::getColumnsCount() const
{
	return columnsCount;
}

bool Table::modify(size_t rowIndex, size_t columnIndex, const char* value)
{
	if (rowIndex >= rowsCount || columnIndex >= columnsCount)
	{
		return false;
	}

	strcpy(rows[rowIndex].fields[columnIndex].field, value);
	return true;
}

void Table::saveToFile(std::ofstream& ofs) const
{
	ofs << "<table>" << std::endl;
	for (size_t i = 0; i < rowsCount; i++)
	{
		rows[i].saveRowToFile(ofs);
	}
	ofs << "</table>"<<std::endl;
}

bool Table::saveToFile(const char* fileName) const
{
	std::ofstream ofs(fileName);
	if (!ofs.is_open())
	{
		return false;
	}
	saveToFile(ofs);
	ofs.close();
	return true;
}

void Table::print() const
{
	for (size_t i = 0; i < rowsCount; i++)
	{
		rows[i].printRow(colLens);
    }
	std::cout<<std::endl;
}
