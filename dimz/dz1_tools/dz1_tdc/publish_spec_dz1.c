#include "publish_spec_parser.h"

static str_t text =
"publish spec definition {\n"									// 1
"	pthread = yes;\n"
"	primitive TCHAR		as			Dz1Letter	with prefix Dz1Letter;\n"
"	primitive TString	as pointer	Dz1Str		with prefix Dz1Str;\n"
"	primitive str		as pointer	str_t		with prefix dz1_built_in_str;\n"
"	primitive wstr		as pointer	wstr_t		with prefix dz1_built_in_wstr;\n"
"	primitive int8		as			s8_t		with prefix Dz1s8;\n"
"	primitive int16		as			s16_t		with prefix Dz1s16;\n"
"	primitive int32		as			s32_t		with prefix Dz1s32;\n"
"	primitive int64		as			s64_t		with prefix Dz1s64;\n"		// 10
"	primitive uint8		as			u8_t		with prefix Dz1u8;\n"
"	primitive uint16	as			u16_t		with prefix Dz1u16;\n"
"	primitive uint32	as			u32_t		with prefix Dz1u32;\n"
"	primitive uint64	as			u64_t		with prefix Dz1u64;\n"
"	primitive float		as			float		with prefix Dz1Real32;\n"
"	primitive real		as			real64_t	with prefix Dz1Real64;\n"
"	primitive real32	as			real32_t	with prefix Dz1Real32;\n"
"	primitive real64	as			real64_t	with prefix Dz1Real64;\n"
"	primitive bool		as			bool_t		with prefix Dz1Bool;\n"		
"	primitive time		as			time_t		with prefix time;\n"		// 20
"	primitive Dz1IPv4	as			Dz1IPv4		with prefix Dz1IPv4;\n"
"	primitive void		as sizeless	void		with prefix Dz1Void;\n"
"	basic {\n"
"		cplusplus = DZ1_CPPLINK;\n"
"		dllport = DZ1_DLLPORT;\n"
"		printf = Dz1Thread_printf;\n"
"		printfA = Dz1ThreadA_printf;\n"
"		printfW = Dz1ThreadW_printf;\n"
"		tabprintf = Dz1Thread_tprintf;\n"
"		tabprintfA = Dz1ThreadA_tprintf;\n"						// 30
"		tabprintfW = Dz1ThreadW_tprintf;\n"
"		fprintf = Dz1Thread_fprintf;\n"
"		fprintfA = Dz1ThreadA_fprintf;\n"
"		fprintfW = Dz1ThreadW_fprintf;\n"
"		ftabprintf = Dz1Thread_ftprintf;\n"
"		ftabprintfA = Dz1ThreadA_ftprintf;\n"
"		ftabprintfW = Dz1ThreadW_ftprintf;\n"
"	}\n"
"	error {\n"
"		type = Dz1Error;\n"										// 40
"		default = DZ1_ERROR_INITIALIZER;\n"
"		set = ERR_SET(*);\n"
"		print = ERR_OUT(*);\n"
"		setAndPrint = ERR_SET_OUT(*);\n"
"		probe = ERR_PROBE(*);\n"
"		clean = ERR_CLEAR(*);\n"
"	}\n"
"	cast {\n"
"		del = (Dz1DelFunc);\n"
"		cmp = (Dz1CmpFunc);\n"									// 50
"		dump = (Dz1DumpFunc);\n"
"	}\n"
"	memory {\n"
"		error	= include;\n"
"		malloc	= Dz1Malloc;\n"
"		calloc	= Dz1Calloc;\n"
"		free	= Dz1Free;\n"
"		cancel	= Dz1Memory_cancel;\n"
"	}\n"
"	postfix {\n"												// 60
"		new				= _new;\n"
"		gen				= _gen;\n"
"		purge			= _purge;\n"
"		del				= _del;\n"
"		delAndSetNull	= _delAndSetNull;\n"
"		dump			= _dump;\n"
"		fdump			= _fdump;\n"
"		compare			= _cmp;\n"
"		clone			= _clone;\n"
"		copy			= _copy;\n"								// 70
"		encode			= _enc;\n"
"		decode			= _dec;\n"
"	}\n"
"	array Dz1Fifo {\n"
"		travelFuncCast	= (Dz1FifoTravelFunc);\n"
"		new				= Dz1Fifo_newDynamic;\n"				// unique array->AATree ordered array->OrderedFIFO, array->FIFO
"		purge			= Dz1Fifo_empty;\n"
"		del				= Dz1Fifo_del;\n"
"		delAndSetNull	= Dz1Fifo_delAndSetNull;\n"
"		add				= Dz1Fifo_push;\n"						// 80
"		remove			= Dz1Fifo_remove;\n"
"		travelForward	= Dz1Fifo_travelForward;\n"
"		travelBackward	= Dz1Fifo_travelBackward;\n"
"		optional {\n"
//"			dump	= Dz1Fifo_dump;\n"
"			extract	= Dz1Fifo_extract;\n"
"			gethead	= Dz1Fifo_getFirst;\n"
"			gettail	= Dz1Fifo_getLast;\n"
"			count	= Dz1Fifo_count;\n"
"		}\n"													// 90
"	}\n"
"	ordered Dz1OrderedFifo {\n"
"		travelFuncCast	= (Dz1AATreeTravelFunc);\n"
"		new				= Dz1OrderedFifo_new;\n"
"		purge			= Dz1OrderedFifo_empty;\n"
"		del				= Dz1OrderedFifo_del;\n"
"		delAndSetNull	= Dz1OrderedFifo_delAndSetNull;\n"
"		add				= Dz1OrderedFifo_push;\n"
"		remove			= Dz1OrderedFifo_remove;\n"
"		travelForward	= Dz1OrderedFifo_travelForward;\n"		// 100
"		travelBackward	= Dz1OrderedFifo_travelBackward;\n"
"		optional {\n"
//"			dump	= Dz1OrderedFifo_dump;\n"
"			extract	= Dz1OrderedFifo_extract;\n"
"			find	= Dz1OrderedFifo_find;\n"
"			gethead	= Dz1OrderedFifo_getHead;\n"
"			gettail	= Dz1OrderedFifo_getTail;\n"
"			count	= Dz1OrderedFifo_count;\n"
"		}\n"
"	}\n"														// 110
"	unique Dz1AATree {\n"
"		travelFuncCast	= (Dz1AATreeTravelFunc);\n"
"		new				= Dz1AATree_new;\n"
"		purge			= Dz1AATree_empty;\n"
"		del				= Dz1AATree_del;\n"
"		delAndSetNull	= Dz1AATree_delAndSetNull;\n"
"		add				= Dz1AATree_insert;\n"
"		remove			= Dz1AATree_remove;\n"
"		travelForward	= Dz1AATree_travelForward;\n"
"		travelBackward	= Dz1AATree_travelBackward;\n"			// 120
"		optional {\n"
//"			dump	= Dz1AATree_dump;\n"
"			extract	= Dz1AATree_extract;\n"
"			find	= Dz1AATree_find;\n"
"			gethead	= Dz1AATree_getHead;\n"
"			gettail	= Dz1AATree_getTail;\n"
"			count	= Dz1AATree_count;\n"
"		}\n"
"	}\n"
"	header include {\n"											// 130
"		dz1_error,\n"
"		dz1_int,\n"
"		dz1_real,\n"
"		dz1_str,\n"
"		dz1_sock_addr\n"
"	}\n"
"	source include {\n"
"		dz1_time,\n"
"		dz1_thread_stdio,\n"
"		dz1_fifo,\n"											// 140
"		dz1_ordered_fifo,\n"
"		dz1_aatree\n"
"	}\n"
"}\n";

PublishSpec *PublishSpec_dz1(Dz1Error *err)
{
	void *p = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	PublishSpec *spec = NULL;
	
	pthread_cleanup_push(PublishSpec_delAndSetNull, (void *)&spec);

	if ((p = PublishSpecParser_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1Parser_del, p);

		if ((spec = PublishSpecParser_proc(p, text, errp)) == NULL) ERR_OUT(errp);
		else
		{
//			PublishSpec_dump(spec, 0);
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(1); // (Dz1Parser_del, p);
	}
	pthread_cleanup_pop(errp->code); // (PublishSpec_delAndSetNull, (void *)spec);

	return spec;
}

void PublishSpec_dz1Write(FILE *fp)
{
	fprintf(fp, "%s", text);
}
