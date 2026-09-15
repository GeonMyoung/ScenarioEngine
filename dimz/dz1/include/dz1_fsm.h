#ifndef DZ1_FSM_H
#define DZ1_FSM_H

#include <dz1_fsm_common.h>

struct Dz1Fsm;
// Dz1FsmFunc is Element type of FSM Function Table
typedef Dz1FsmReturn (*Dz1FsmFunc)(struct Dz1Fsm *fsm, void *user_param, void *user_resource, int event, void **msg, Dz1Error *errp);

// Dz1FsmGetEventFunc is function to detect event of message
typedef int (*Dz1FsmGetEvent)(struct Dz1Fsm *fsm, void *user_param, void *user_resource, void *msg);

// Dz1FsmProcFunc is root function to branching FSM Function Table
typedef Dz1Error (*Dz1FsmGetFunc)(int state, int event, Dz1FsmFunc *ret);

typedef struct Dz1FsmLog
{
	int state;
	int event;
	Dz1FsmFunc func;
	Dz1FsmReturn ret;
	Dz1Error err;
	int nextState;
} Dz1FsmLog;

/*
DZ1_CPPLINK DZ1_DLLPORT Dz1FsmLog_new(int state, int event, Dz1FsmReturn ret, Dz1Error error, int nextState, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1FsmLog_del(Dz1FsmLog *p);
DZ1_CPPLINK DZ1_DLLPORT Dz1FsmLog_dump(Dz1FsmLog *p, int tab);
static __inline__ void Dz1FsmLog_delAndSetNull(void *ptr)
{
	Dz1FsmLog **p = (Dz1FsmLog **)ptr;
	Dz1FsmLog_del(*p); *p = NULL;
}
*/

typedef struct Dz1Fsm
{
	int state;

	bool_t trace;
	// FSM Trace Log
	Dz1FsmLog *fsmLog;
	int fsmLogSize;
	int fsmLogIdx;

	Dz1FsmGetEvent getEvent;
	Dz1FsmGetFunc getFunc;

	void *fsmArg;
	Dz1DelFunc fsmArgDel;

} Dz1Fsm;

DZ1_CPPLINK DZ1_DLLPORT Dz1Fsm *Dz1Fsm_new(bool_t trace, u32_t fsmLogSize,
										   Dz1FsmGetEvent getEvent,
										   Dz1FsmGetFunc getFunc,
										   void **arg, Dz1DelFunc argDel, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void Dz1Fsm_del(Dz1Fsm *p);
static __inline__ void Dz1Fsm_delAndSetNull(void *ptr)
{
	Dz1Fsm **p = (Dz1Fsm **)ptr;
	Dz1Fsm_del(*p); *p = NULL;
}

DZ1_CPPLINK DZ1_DLLPORT Dz1FsmReturn Dz1FsmA_proc(Dz1Fsm *fsm, void *user_param, void *user_resource, void **msg, Dz1Error *err);
#ifndef UNIX_SYSTEM
DZ1_CPPLINK DZ1_DLLPORT Dz1FsmReturn Dz1FsmW_proc(Dz1Fsm *fsm, void *user_param, void *user_resource, void **msg, Dz1Error *err);
#ifdef UNICODE
#define								 Dz1Fsm_proc	Dz1FsmW_proc
#else // UNICODE
#define								 Dz1Fsm_proc	Dz1FsmA_proc
#endif // UNICODE
#else // UNIX_SYSTEM
#define								 Dz1Fsm_proc	Dz1FsmA_proc
#endif // UNIX_SYSTEM
#endif
