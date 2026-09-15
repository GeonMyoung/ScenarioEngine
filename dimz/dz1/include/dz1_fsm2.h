#ifndef DZ1_FSM2_H
#define DZ1_FSM2_H

#include <dz1_fsm_common.h>

#define DZ1_FSM2_ERR_SET_A(fsm_ret, errp, code)		do { ERR_SET_OUT_A(errp, code); fsm_ret = Dz1FsmReturn_error; } while(0)
#define DZ1_FSM2_ERR_A(fsm_ret, errp)				do { ERR_OUT_A(errp); fsm_ret = Dz1FsmReturn_error; } while(0)

struct Dz1Fsm2A;
// Dz1Fsm2Func is Element type of FSM Function Table
typedef Dz1FsmReturn (*Dz1Fsm2FuncA)(struct Dz1Fsm2A *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp);
// Dz1Fsm2ProcFunc is root function to branching FSM Function Table
typedef Dz1Error (*Dz1Fsm2GetFuncA)(int state, int event, Dz1Fsm2FuncA *ret);
// Dz1Fsm2GetEventFunc is function to detect event of message
typedef int (*Dz1Fsm2GetEventByDataA)(struct Dz1Fsm2A *fsm, void *uArg, void *uRsc, void *data);
typedef int (*Dz1Fsm2GetEventByNameA)(struct Dz1Fsm2A *fsm, void *uArg, void *uRsc, void *name);

typedef struct Dz1Fsm2LogA
{
	int				 state;
	int				 event;
	Dz1Fsm2FuncA	 func;
	Dz1FsmReturn	 ret;
	Dz1Error		 err;
	int				 nextState;
} Dz1Fsm2LogA;

typedef struct Dz1Fsm2A
{
	str_t					 name;
	int						 state;

	bool_t					 trace;
	// FSM Trace Log
	Dz1Fsm2LogA				*fsmLog;
	int						 fsmLogSize;
	int						 fsmLogIdx;

	Dz1Fsm2GetEventByDataA	 getEventByData;
	Dz1Fsm2GetEventByNameA	 getEventByName;
	Dz1Fsm2GetFuncA			 getFunc;

	void					*fsmArg;
	Dz1DelFunc				 fsmArgDel;
} Dz1Fsm2A;

#define								  Dz1Fsm2A_new(name, trace, fsmLogSize, getEvByData,       getFunc, argpp, argDelF, errp) \
									 _Dz1Fsm2A_new(name, trace, fsmLogSize, getEvByData, NULL, getFunc, argpp, argDelF, errp)
DZ1_CPPLINK DZ1_DLLPORT Dz1Fsm2A	*_Dz1Fsm2A_new(str_t name, bool_t trace, u32_t fsmLogSize,
												   Dz1Fsm2GetEventByDataA getEventByData, 
												   Dz1Fsm2GetEventByNameA getEventByName, 
												   Dz1Fsm2GetFuncA getFunc, 
												   void **arg, Dz1DelFunc argDel, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void		  Dz1Fsm2A_del(Dz1Fsm2A *p);
static __inline__ void				  Dz1Fsm2A_delAndSetNull(void *ptr)
{
	Dz1Fsm2A **p = (Dz1Fsm2A **)ptr;
	Dz1Fsm2A_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void		   Dz1Fsm2A_dump(Dz1Fsm2A *fsm, int tab);

DZ1_CPPLINK DZ1_DLLPORT Dz1FsmReturn   Dz1Fsm2A_proc(Dz1Fsm2A *fsm, void *uArg, void *uRsc, void *timer, void **msg, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1FsmReturn   Dz1Fsm2A_proc2(Dz1Fsm2A *fsm, void *uArg, void *uRsc, void *timer, int ev, void **msg, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1FsmReturn   Dz1Fsm2A_proc3(Dz1Fsm2A *fsm, void *uArg, void *uRsc, void *timer, void *evName, void **msg, Dz1Error *err);

#ifndef UNIX_SYSTEM
#define DZ1_FSM2_ERR_SET_W(fsm_ret, errp, code)		do { ERR_SET_OUT_W(errp, code); fsm_ret = Dz1FsmReturn_error; } while(0)
#define DZ1_FSM2_ERR_W(fsm_ret, errp)				do { ERR_OUT_W(errp); fsm_ret = Dz1FsmReturn_error; } while(0)

struct Dz1Fsm2W;
// Dz1Fsm2Func is Element type of FSM Function Table
typedef Dz1FsmReturn (*Dz1Fsm2FuncW)(struct Dz1Fsm2W *fsm, void *uArg, void *uRsc, void *timer, int event, void **sg, Dz1Error *errp);
// Dz1Fsm2ProcFunc is root function to branching FSM Function Table
typedef Dz1Error (*Dz1Fsm2GetFuncW)(int state, int event, Dz1Fsm2FuncW *ret);
// Dz1Fsm2GetEventFunc is function to detect event of message
typedef int (*Dz1Fsm2GetEventByDataW)(struct Dz1Fsm2W *fsm, void *uArg, void *uRsc, void *data);
typedef int (*Dz1Fsm2GetEventByNameW)(struct Dz1Fsm2W *fsm, void *uArg, void *uRsc, void *name);

typedef struct Dz1Fsm2LogW
{
	int				 state;
	int				 event;
	Dz1Fsm2FuncW	 func;
	Dz1FsmReturn	 ret;
	Dz1Error		 err;
	int				 nextState;
} Dz1Fsm2LogW;

typedef struct Dz1Fsm2W
{
	wstr_t					 name;
	int						 state;

	bool_t					 trace;
	// FSM Trace Log
	Dz1Fsm2LogW				*fsmLog;
	int						 fsmLogSize;
	int						 fsmLogIdx;

	Dz1Fsm2GetEventByDataW	 getEventByData;
	Dz1Fsm2GetEventByNameW	 getEventByName;
	Dz1Fsm2GetFuncW			 getFunc;

	void					*fsmArg;
	Dz1DelFunc				 fsmArgDel;
} Dz1Fsm2W;
#define								  Dz1Fsm2W_new(name, trace, fsmLogSize, getEvent, getFunc, argpp, argDelF, errp) _Dz1Fsm2W_new(name, trace, fsmLogSize, getEvent, NULL, getFunc, argpp, argDelF, errp)
DZ1_CPPLINK DZ1_DLLPORT Dz1Fsm2W	*_Dz1Fsm2W_new(wstr_t name, bool_t trace, u32_t fsmLogSize, Dz1Fsm2GetEventByDataW getEventByData, Dz1Fsm2GetEventByNameW getEventByName, Dz1Fsm2GetFuncW getFunc, void **arg, Dz1DelFunc argDel, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT void		  Dz1Fsm2W_del(Dz1Fsm2W *p);
static __inline__ void				  Dz1Fsm2W_delAndSetNull(void *ptr)
{
	Dz1Fsm2W **p = (Dz1Fsm2W **)ptr;
	Dz1Fsm2W_del(*p); *p = NULL;
}
DZ1_CPPLINK DZ1_DLLPORT void		   Dz1Fsm2W_dump(Dz1Fsm2W *fsm, int tab);

DZ1_CPPLINK DZ1_DLLPORT Dz1FsmReturn   Dz1Fsm2W_proc(Dz1Fsm2W *fsm, void *uArg, void *uRsc, void *timer, void **msg, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1FsmReturn   Dz1Fsm2W_proc2(Dz1Fsm2W *fsm, void *uArg, void *uRsc, void *timer, int ev, void **msg, Dz1Error *err);
DZ1_CPPLINK DZ1_DLLPORT Dz1FsmReturn   Dz1Fsm2W_proc3(Dz1Fsm2W *fsm, void *uArg, void *uRsc, void *timer, void *evName, void **msg, Dz1Error *err);
#ifdef UNICODE
#define								   Dz1Fsm2					 Dz1Fsm2W
#define								   DZ1_FSM2_ERR_SET			 DZ1_FSM2_ERR_SET_A
#define								   DZ1_FSM2_ERR				 DZ1_FSM2_ERR_A
#define								   Dz1Fsm2Func				 Dz1Fsm2FuncW
#define								   Dz1Fsm2GetEventByData	 Dz1Fsm2GetEventByDataW
#define								   Dz1Fsm2GetEventByName	 Dz1Fsm2GetEventByNameW
#define								   Dz1Fsm2_new				_Dz1Fsm2W_new
#define								   Dz1Fsm2_del				 Dz1Fsm2W_del
#define								   Dz1Fsm2_delAndSetNull	 Dz1Fsm2W_delAndSetNull
#define								   Dz1Fsm2_dump				 Dz1Fsm2W_dump
#define								   Dz1Fsm2_proc				 Dz1Fsm2W_proc
#define								   Dz1Fsm2_proc2			 Dz1Fsm2W_proc2
#define								   Dz1Fsm2_proc3			 Dz1Fsm2W_proc3
#else // UNICODE
#define								   Dz1Fsm2					 Dz1Fsm2A
#define								   DZ1_FSM2_ERR_SET			 DZ1_FSM2_ERR_SET_A
#define								   DZ1_FSM2_ERR				 DZ1_FSM2_ERR_A
#define								   Dz1Fsm2Func				 Dz1Fsm2FuncA
#define								   Dz1Fsm2GetEventByData	 Dz1Fsm2GetEventByDataA
#define								   Dz1Fsm2GetEventByName	 Dz1Fsm2GetEventByNameA
#define								   Dz1Fsm2_new				_Dz1Fsm2A_new
#define								   Dz1Fsm2_del				 Dz1Fsm2A_del
#define								   Dz1Fsm2_delAndSetNull	 Dz1Fsm2A_delAndSetNull
#define								   Dz1Fsm2_dump				 Dz1Fsm2A_dump
#define								   Dz1Fsm2_proc				 Dz1Fsm2A_proc
#define								   Dz1Fsm2_proc2			 Dz1Fsm2A_proc2
#define								   Dz1Fsm2_proc3			 Dz1Fsm2A_proc3
#endif // UNICODE
#else // UNIX_SYSTEM
#define								   Dz1Fsm2					 Dz1Fsm2A
#define								   DZ1_FSM2_ERR_SET			 DZ1_FSM2_ERR_SET_A
#define								   DZ1_FSM2_ERR				 DZ1_FSM2_ERR_A
#define								   Dz1Fsm2Func				 Dz1Fsm2FuncA
#define								   Dz1Fsm2GetEventByData	 Dz1Fsm2GetEventByDataA
#define								   Dz1Fsm2GetEventByName	 Dz1Fsm2GetEventByNameA
#define								   Dz1Fsm2_new				_Dz1Fsm2A_new
#define								   Dz1Fsm2_del				 Dz1Fsm2A_del
#define								   Dz1Fsm2_delAndSetNull	 Dz1Fsm2A_delAndSetNull
#define								   Dz1Fsm2_dump				 Dz1Fsm2A_dump
#define								   Dz1Fsm2_proc				 Dz1Fsm2A_proc
#define								   Dz1Fsm2_proc2			 Dz1Fsm2A_proc2
#define								   Dz1Fsm2_proc3			 Dz1Fsm2A_proc3
#endif // UNIX_SYSTEM

#define Dz1Fsm2_getFuncDefine(FuncName, StateMax, EventMax, FSMArray) \
	static Dz1Error FuncName(int state, int event, Dz1Fsm2Func *ret)\
	{\
		Dz1Error err = DZ1_ERROR_INITIALIZER;\
		if (state < 0 || state >= StateMax)\
		{\
			Dz1Thread_printf(#FuncName"() : State is Out of range = %d\n", state);\
			ERR_SET_OUT(&err, EINVAL);\
		}\
		else if (event < 0 || event >= EventMax)\
		{\
			Dz1Thread_printf(#FuncName"() : Event is Out of range = %d\n", event);\
			ERR_SET_OUT(&err, EINVAL);\
		}\
		else (*ret) = FSMArray[state][event];\
		return err;\
	}


#endif

