#include "Utils.h"


int getBitFromStr(unsigned char chGenre) 
{
	switch (chGenre)
	{
	case 'r': return 0;  break;
	case 'p': return 1; break;
	case 'h': return 2;  break;
	case 't': return 3;  break;
	case 'j': return 4;  break;
	}
}
