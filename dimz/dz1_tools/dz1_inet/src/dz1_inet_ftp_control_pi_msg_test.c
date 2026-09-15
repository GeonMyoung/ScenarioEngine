#include <dz1_str.h>
#include "dz1_inet_ftp_control_pi.h"
#include "dz1_inet_ftp_control_pi_msg_test.h"

static Dz1Error genNull(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	return err;
}

static Dz1Error genUser(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((p->x.__ptr__ = (str_t)Dz1Str_dup("testuser", &err)) == NULL) ERR_OUT(&err);
	return err;
}

static Dz1Error genPass(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((p->x.__ptr__ = (str_t)Dz1Str_dup("testpass", &err)) == NULL) ERR_OUT(&err);
	return err;
}

static Dz1Error genAcct(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((p->x.__ptr__ = (str_t)Dz1Str_dup("testaccount", &err)) == NULL) ERR_OUT(&err);
	return err;
}

static Dz1Error genPathName(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((p->x.__ptr__ = (str_t)Dz1Str_dup("\\root\\test\\sample", &err)) == NULL) ERR_OUT(&err);
	return err;
}

static Dz1Error genFileName(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((p->x.__ptr__ = (str_t)Dz1Str_dup("\\root\\test\\sample\\fsimg.fs", &err)) == NULL) ERR_OUT(&err);
	return err;
}

static Dz1Error genCmd(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((p->x.__ptr__ = (str_t)Dz1Str_dup("XCMD", &err)) == NULL) ERR_OUT(&err);
	return err;
}

static Dz1Error genPort(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1SockAddr addr;
	memset(&addr, 0, sizeof(Dz1SockAddr));

	if ((err = Dz1SockAddr_setAddrStr(&addr, "127.0.0.1")).code) ERR_OUT(&err);
	else if ((err = Dz1SockAddr_setPort(&addr, 12345)).code) ERR_OUT(&err);
	else if ((p->x.port = Dz1SockAddr_clone(&addr, &err)) == NULL) ERR_OUT(&err);
	return err;
}

static Dz1Error genType1(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((p->x.type = Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent_ascii, NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error genType2(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpDTPTextForm form = Dz1InetFtpDTPTextForm_nonPrint;
	if ((p->x.type = Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent_ascii, &form, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error genType3(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpDTPTextForm form = Dz1InetFtpDTPTextForm_telnet;
	if ((p->x.type = Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent_ascii, &form, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error genType4(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpDTPTextForm form = Dz1InetFtpDTPTextForm_asa;
	if ((p->x.type = Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent_ascii, &form, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error genType5(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((p->x.type = Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent_ebcdic, NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error genType6(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpDTPTextForm form = Dz1InetFtpDTPTextForm_nonPrint;
	if ((p->x.type = Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent_ebcdic, &form, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error genType7(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpDTPTextForm form = Dz1InetFtpDTPTextForm_telnet;
	if ((p->x.type = Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent_ebcdic, &form, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error genType8(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpDTPTextForm form = Dz1InetFtpDTPTextForm_asa;
	if ((p->x.type = Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent_ebcdic, &form, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error genType9(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((p->x.type = Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent_image, NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error genType10(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	u32_t bsz = 8;
	if ((p->x.type = Dz1InetFtpDTPType_new(Dz1InetFtpDTPTypePresent_local, &bsz, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error genStru1(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	p->x.stru = Dz1InetFtpDTPStruct_file;

	return err;
}

static Dz1Error genStru2(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	p->x.stru = Dz1InetFtpDTPStruct_record;

	return err;
}

static Dz1Error genStru3(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	p->x.stru = Dz1InetFtpDTPStruct_page;

	return err;
}

static Dz1Error genMode1(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	p->x.mode = Dz1InetFtpDTPMode_stream;

	return err;
}

static Dz1Error genMode2(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	p->x.mode = Dz1InetFtpDTPMode_block;

	return err;
}

static Dz1Error genMode3(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	p->x.mode = Dz1InetFtpDTPMode_compressed;

	return err;
}

static Dz1Error genAllo1(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((p->x.allo = Dz1InetFtpAlloc_new(100, NULL, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error genAllo2(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	u32_t nor = 20;
	if ((p->x.allo = Dz1InetFtpAlloc_new(100, &nor, &err)) == NULL) ERR_OUT(&err);

	return err;
}

static Dz1Error genRest(Dz1InetFtpCPIMsgReq *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if ((p->x.__ptr__ = (str_t)Dz1Str_dup("7AF46C", &err)) == NULL) ERR_OUT(&err);
	return err;
}

typedef struct Dz1InetFtpReqMsgGen
{
	Dz1InetFtpCPIMsgReqPresent present;
	Dz1Error (*gen)(Dz1InetFtpCPIMsgReq *p);
} Dz1InetFtpReqMsgGen;

static Dz1InetFtpReqMsgGen genMap[] =
{
	/*
	{ Dz1InetFtpCPIMsgReqPresent_user, genUser },
	{ Dz1InetFtpCPIMsgReqPresent_pass, genPass },
	{ Dz1InetFtpCPIMsgReqPresent_acct, genAcct },
	{ Dz1InetFtpCPIMsgReqPresent_cwd, genPathName },
	{ Dz1InetFtpCPIMsgReqPresent_cdup, genNull },
	{ Dz1InetFtpCPIMsgReqPresent_smnt, genFileName },
	{ Dz1InetFtpCPIMsgReqPresent_quit, genNull },
	{ Dz1InetFtpCPIMsgReqPresent_rein, genNull },
	*/
	{ Dz1InetFtpCPIMsgReqPresent_port, genPort },
	/*
	{ Dz1InetFtpCPIMsgReqPresent_pasv, genNull },
	{ Dz1InetFtpCPIMsgReqPresent_type, genType1 },
	{ Dz1InetFtpCPIMsgReqPresent_type, genType2 },
	{ Dz1InetFtpCPIMsgReqPresent_type, genType3 },
	{ Dz1InetFtpCPIMsgReqPresent_type, genType4 },
	{ Dz1InetFtpCPIMsgReqPresent_type, genType5 },
	{ Dz1InetFtpCPIMsgReqPresent_type, genType6 },
	{ Dz1InetFtpCPIMsgReqPresent_type, genType7 },
	{ Dz1InetFtpCPIMsgReqPresent_type, genType8 },
	{ Dz1InetFtpCPIMsgReqPresent_type, genType9 },
	{ Dz1InetFtpCPIMsgReqPresent_type, genType10 },
	{ Dz1InetFtpCPIMsgReqPresent_stru, genStru1 },
	{ Dz1InetFtpCPIMsgReqPresent_stru, genStru2 },
	{ Dz1InetFtpCPIMsgReqPresent_stru, genStru3 },
	{ Dz1InetFtpCPIMsgReqPresent_mode, genMode1 },
	{ Dz1InetFtpCPIMsgReqPresent_mode, genMode2 },
	{ Dz1InetFtpCPIMsgReqPresent_mode, genMode3 },
	{ Dz1InetFtpCPIMsgReqPresent_retr, genFileName },
	{ Dz1InetFtpCPIMsgReqPresent_stor, genFileName },
	{ Dz1InetFtpCPIMsgReqPresent_stou, genNull },
	{ Dz1InetFtpCPIMsgReqPresent_appe, genFileName },
	{ Dz1InetFtpCPIMsgReqPresent_allo, genAllo1 },
	{ Dz1InetFtpCPIMsgReqPresent_allo, genAllo2 },
	{ Dz1InetFtpCPIMsgReqPresent_rest, genRest },
	{ Dz1InetFtpCPIMsgReqPresent_rnfr, genFileName },
	{ Dz1InetFtpCPIMsgReqPresent_rnto, genFileName },
	{ Dz1InetFtpCPIMsgReqPresent_abor, genNull },
	{ Dz1InetFtpCPIMsgReqPresent_dele, genFileName },
	{ Dz1InetFtpCPIMsgReqPresent_rmd, genPathName },
	{ Dz1InetFtpCPIMsgReqPresent_mkd, genPathName },
	{ Dz1InetFtpCPIMsgReqPresent_pwd, genNull },
	{ Dz1InetFtpCPIMsgReqPresent_list, genPathName },
	{ Dz1InetFtpCPIMsgReqPresent_list, genNull },
	{ Dz1InetFtpCPIMsgReqPresent_nlst, genPathName },
	{ Dz1InetFtpCPIMsgReqPresent_nlst, genNull },
	{ Dz1InetFtpCPIMsgReqPresent_site, genCmd },
	{ Dz1InetFtpCPIMsgReqPresent_site, genNull },
	{ Dz1InetFtpCPIMsgReqPresent_syst, genNull },
	{ Dz1InetFtpCPIMsgReqPresent_stat, genFileName },
	{ Dz1InetFtpCPIMsgReqPresent_stat, genNull },
	{ Dz1InetFtpCPIMsgReqPresent_help, genCmd },
	{ Dz1InetFtpCPIMsgReqPresent_help, genNull },
	*/
	{ Dz1InetFtpCPIMsgReqPresent_max, NULL },
};

static Dz1Error codecTest(Dz1InetFtpCPIMsg *msg)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	u8_t *data = NULL;
	ssize_t size = 0;
	Dz1Thread_printf("Dz1InetFtpCPIMsg = "); Dz1InetFtpCPIMsg_dump(msg, 0);
	if ((size = Dz1InetFtpCPIMsg_encode(&data, msg, &err)) < 0) ERR_OUT(&err);
	else
	{
		bool_t isComplete = FALSE;
		Dz1InetFtpCPIMsg *_msg = NULL;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)data);
		Dz1Thread_printf("Encoded Message\n");
		Dz1Thread_tprintb(1, data, size, 8, FALSE);
		if (Dz1InetFtpCPIMsg_decode(&_msg, data, size, &isComplete, &err) < 0) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)_msg);
			if (isComplete == FALSE)
			{
				Dz1Thread_printf("Decoding Process incomplete\n");
			}
			else
			{
				Dz1Thread_printf("Decoded Message = "); Dz1InetFtpCPIMsg_dump(_msg, 0);
			}
			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)_msg);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)data);
	}
	return err;
}

static Dz1Error Dz1InetFtpCPIMsgReq_test(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpCPIMsg *msg = NULL;

	Dz1InetFtpReqMsgGen *i;
	for (i = genMap; err.code == 0 && i->present != Dz1InetFtpCPIMsgReqPresent_max; i++)
	{
		Dz1Thread_printf("\n===================================================\n");
		Dz1Thread_printf("%s Test\n", Dz1InetFtpCPIMsgReqPresentStr(i->present));
		Dz1Thread_printf("===================================================\n");
		if ((msg = Dz1InetFtpCPIMsg_new(Dz1InetFtpCPIMsgPresent_req, NULL, &err)) == NULL) ERR_OUT(&err);
		else
		{
			Dz1InetFtpCPIMsgReq *req = NULL;
			pthread_cleanup_push((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)msg);
			if ((req = msg->x.req = Dz1InetFtpCPIMsgReq_new(i->present, NULL, &err)) == NULL) ERR_OUT(&err);
			else if (i->gen && (err = i->gen(req)).code) ERR_OUT(&err);
			else if ((err = codecTest(msg)).code) ERR_OUT(&err);
			pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)msg);
		}
	}
	return err;
}

static Dz1Error Dz1InetFtpCPIMsgReply_singleLineTest(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpCPIMsg *msg = NULL;
	Dz1Thread_printf("\n===================================================\n");
	Dz1Thread_printf("Single-line Reply Test\n");
	Dz1Thread_printf("===================================================\n");
	if ((msg = Dz1InetFtpCPIMsg_new(Dz1InetFtpCPIMsgPresent_reply, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Dz1InetFtpCPIMsgReply *reply = NULL;
		pthread_cleanup_push((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)msg);
		if ((reply = msg->x.reply = Dz1InetFtpCPIMsgReply_new(200, "Success", &err)) == NULL) ERR_OUT(&err);
		else if ((err = codecTest(msg)).code) ERR_OUT(&err);
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)msg);
	}
	return err;
}

static Dz1Error setList(Dz1InetFtpCPIMsgReply *reply)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	str_t strings[] =
	{
		"Sample Line 1",
		"Sample Line 2",
		"Sample Line 3",
		"Sample Line 4",
		"Success",
		NULL
	}, *i, str = NULL;

	for (i = strings; err.code == 0 && *i != NULL; i++)
	{
		if ((str = Dz1Str_dup(*i, &err)) == NULL) ERR_OUT(&err);
		else
		{
			pthread_cleanup_push(Dz1Str_delAndSetNull, (void *)&str);
			if ((err = reply->list->add(reply->list, str)).code) ERR_OUT(&err);
			else str = NULL;
			pthread_cleanup_pop(1); // (Dz1Str_delAndSetNull, (void *)&str);
		}
	}

	return err;
}

static Dz1Error Dz1InetFtpCPIMsgReply_multiLineTest(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1InetFtpCPIMsg *msg = NULL;
	Dz1Thread_printf("\n===================================================\n");
	Dz1Thread_printf("Multi-line Reply Test\n");
	Dz1Thread_printf("===================================================\n");
	if ((msg = Dz1InetFtpCPIMsg_new(Dz1InetFtpCPIMsgPresent_reply, NULL, &err)) == NULL) ERR_OUT(&err);
	else
	{
		Dz1InetFtpCPIMsgReply *reply = NULL;
		pthread_cleanup_push((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)msg);

		if ((reply = msg->x.reply = Dz1InetFtpCPIMsgReply_new(200, "Success", &err)) == NULL) ERR_OUT(&err);
		else if ((err = setList(reply)).code) ERR_OUT(&err);
		else if ((err = codecTest(msg)).code) ERR_OUT(&err);

		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)msg);
	}
	return err;
}

static Dz1Error Dz1InetFtpCPIMsgReply_splitMultiLineTest(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	bool_t isComplete = FALSE;
	Dz1InetFtpCPIMsg *msg = NULL;
	str_t data1 = "200-Success\x0d\x0a"
				  "Line1\x0d\x0a"
				  "Line2\x0d\x0a";
	str_t data2 = "Line3\x0d\x0a"
				  "Line4\x0d\x0a"
				  "200 Success\x0d\x0a";

	Dz1Thread_printf("\n===================================================\n");
	Dz1Thread_printf("Split Decode Test\n");
	Dz1Thread_printf("===================================================\n");
	if (Dz1InetFtpCPIMsg_decode(&msg, (u8_t *)data1, strlen(data1), &isComplete, &err) < 0) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)msg);
		if (isComplete)
		{
			Dz1Thread_printf("PRE Decoded Message = "); Dz1InetFtpCPIMsg_dump(msg, 0);
		}
		else if (Dz1InetFtpCPIMsg_decode(&msg, (u8_t *)data2, strlen(data2), &isComplete, &err) < 0) ERR_OUT(&err);
		else if (isComplete)
		{
			Dz1Thread_printf("Decoded Message = "); Dz1InetFtpCPIMsg_dump(msg, 0);
		}
		else ERR_SET_OUT(&err, EFAULT);
		pthread_cleanup_pop(1); // ((Dz1DelFunc)Dz1InetFtpCPIMsg_del, (void *)msg);
	}
	return err;
}

Dz1Error Dz1InetFtpCPIMsg_test(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	//if ((err = Dz1InetFtpCPIMsgReq_test()).code) ERR_OUT(&err);
	//if ((err = Dz1InetFtpCPIMsgReply_singleLineTest()).code) ERR_OUT(&err);
	if ((err = Dz1InetFtpCPIMsgReply_multiLineTest()).code) ERR_OUT(&err);
	//if ((err = Dz1InetFtpCPIMsgReply_splitMultiLineTest()).code) ERR_OUT(&err);
	return err;
}

