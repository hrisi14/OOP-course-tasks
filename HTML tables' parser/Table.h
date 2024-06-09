#pragma once
#include <fstream>
#include <sstream>
#include "Row.h"

class Table
{
public:
	Row rows[GlobalConstants::MAX_ROWS_TABLE];
	size_t colLens[GlobalConstants::MAX_FIELDS_ROW] = { 0 };
	size_t rowsCount = 0;
	size_t columnsCount = 0;

	bool addRow(size_t rowNumber, const char values[GlobalConstants::MAX_FIELDS_ROW][GlobalConstants::FIELD_MAX_SIZE], size_t numberOfFields);
	bool removeRow(size_t rowNumber);	
	void parseField(const char* fieldStr, size_t& rowIndex, size_t& colIndex);
	void parseRow(const char* rowStr, size_t& rowIndex, size_t& colIndex); //returns the number of the parsed row's fields (=columnsCounter)
	bool parseFromFile(const char* fileName); 
	void parseFromFile(std::ifstream& ifs);  
	bool saveToFile(const char* fileName) const;
	void saveToFile(std::ofstream& ofs) const;
	size_t getRowsCount() const;
	size_t getColumnsCount() const;
	bool modify(size_t rowIndex, size_t columnIndex, const char* value);
	void upgradeColLens(const Row& newRow);
	void print() const;
};

