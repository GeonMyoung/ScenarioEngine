#ifndef GENERATOR_H
#define GENERATOR_H

#include <dz1_error.h>

//#include <ItsIcMsgDz1Codec.h>

typedef struct MsgGenerator
{
	int num;
	void *(*gen)(Dz1Error *errp);
	void (*delAndSetNull)(void *pptr);
} MsgGenerator;

/*
extern MsgGenerator ItsIcIPESGenerator[];
extern MsgGenerator ItsIcBLESGenerator[];
extern MsgGenerator ItsIcAVIGenerator[];
extern MsgGenerator ItsIcVDSGenerator[];
extern MsgGenerator ItsIcCCTVGenerator[];
*/

DZ1_CPPLINK MsgGenerator *MsgGenerator_find(int num, MsgGenerator table[]);

#endif