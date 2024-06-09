#include "Field.h"


Field::Field(const char* value)
{
	if (strlen(value) < GlobalConstants::FIELD_MAX_SIZE)
	{
		strcpy(field, value);
	}	
}

void Field::printField(size_t maxColumnLen) const
{
	size_t diff = maxColumnLen - strlen(field);
	
	if (diff % 2)
	{
		printSymbol(' ', diff / 2 + 1);
	}
	else
	{
		printSymbol(' ', diff / 2);
	}
	
	if (isHeading)
	{
		std::cout <<'*'<<field<<'*';
	}
	else
	{
		std::cout << ' ' << field << ' ';
	}	
	printSymbol(' ', diff / 2);
}


void Field::saveFieldToFile(std::ofstream& ofs) const
{
	    if (isHeading)
		{
			ofs << "<th> ";
			ofs << field;
			ofs << "</th> "<<std::endl;
		}
		else
		{
			ofs << "<td> ";
			ofs << field;
			ofs << "</td> "<<std::endl;
		}	
}
