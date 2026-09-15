#include "dz1_storage_def.h"

void Dz1StorageBlock_dump(Dz1StorageBlock *p, int tab)
{
	if (!p) { Dz1Thread_printf("NULL\n"); return; }
	Dz1Thread_printf("<<%08X [%08X][%03u] %08X>>\n", p->prev_idx, p->idx, p->flag, p->next_idx);
}

