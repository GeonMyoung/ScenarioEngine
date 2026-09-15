
#include "generator.h"

MsgGenerator *MsgGenerator_find(int num, MsgGenerator table[])
{
	MsgGenerator *i;
	for (i = table; i->num != -1; i++)
		if (i->num == num) return i;
	return NULL;
}

