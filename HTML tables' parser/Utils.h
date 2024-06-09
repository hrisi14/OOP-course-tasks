#pragma once
#include <iostream>

namespace GlobalConstants
{
	constexpr int FIELD_MAX_SIZE = 50;
	constexpr int MAX_FIELDS_ROW = 30;
	constexpr int MAX_ROWS_TABLE = 300;
	constexpr int BUFFER_SIZE = 1024;
	constexpr char TAG_LEN = 10;

	constexpr char TABLE_TAG[TAG_LEN] = "<table";	
	constexpr char HEADER_TAG1[TAG_LEN] = "<th";
	constexpr char HEADER_TAG2[TAG_LEN] = "th";

	constexpr char ROW_TAG_CLOSE[TAG_LEN] = "/tr";
}

void printSymbol(char symbol, unsigned numberOfTimes);
bool isEmptyLine(const char* fieldStr);


