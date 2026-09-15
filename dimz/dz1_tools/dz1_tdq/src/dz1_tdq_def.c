////////////////////////////////////////////////////////////////////////////////
#include <dz1_time.h>
#include <dz1_thread_stdio.h>
#include <dz1_fifo.h>
#include <dz1_ordered_fifo.h>
#include <dz1_aatree.h>
////////////////////////////////////////////////////////////////////////////////

#include "dz1_tdq_def.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1TdqDbScheme
void Dz1TdqDbScheme_purge(Dz1TdqDbScheme *p)
{
	if (p == NULL) return;
	Dz1TdqDbConnArg_del(p->arg);
	Dz1TdqDbIface_del(p->dbh);
	Dz1TdqTblShapeList_del(p->shapes);
	Dz1TdqTblInstanceList_del(p->tables);
	Dz1TdqTblInstanceSeq_del(p->tblseq);
	Dz1TdqQueryList_del(p->queries);
}

void Dz1TdqDbScheme_del(Dz1TdqDbScheme *p)
{
	if (p == NULL) return;
	Dz1TdqDbScheme_purge(p);
	Dz1Free(p);
}

void Dz1TdqDbScheme_dump(Dz1TdqDbScheme *p, int tab)
{
	if (!p) Dz1Thread_printf(Dz1T("NULL\n"));
	else
	{
		Dz1Thread_printf(Dz1T("{\n")); tab++;
		// _imp_dump
		// _imp_dump : pointer
		Dz1Thread_tprintf(tab, Dz1T("arg = ")); Dz1TdqDbConnArg_dump(p->arg, tab); 
		Dz1Thread_tprintf(tab, Dz1T("shapes = ")); Dz1TdqTblShapeList_dump(p->shapes, tab); 
		Dz1Thread_tprintf(tab, Dz1T("tables = ")); Dz1TdqTblInstanceList_dump(p->tables, tab); 
		Dz1Thread_tprintf(tab, Dz1T("tblseq = ")); Dz1TdqTblInstanceSeq_dump(p->tblseq, tab); 
		Dz1Thread_tprintf(tab, Dz1T("queries = ")); Dz1TdqQueryList_dump(p->queries, tab); 
		Dz1Thread_tprintf(--tab, Dz1T("}\n"));
	}
}
// Dz1TdqDbScheme
////////////////////////////////////////////////////////////////////////////////

