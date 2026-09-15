#include <ITSK00144_2TestScenarioTest.h>

#include "ITSK00144_2TestScenarioArg.h"
#include "ITSK00144_2TestScenarioEnv.h"
#include "ITSK00144_2TestScenarioMsg.h"
#include <ITSK00144_2TestMsg.h>


static ITSK00144_2Reserved0* sample_req_link_unit_status;
static I2XTrafficSafetyDeviceLinkUnitStatus* sample_rsp_link_unit_status;
static ITSK00144_2Reserved0* sample_req_status;
static I2XTrafficSafetyDeviceStatusInfo* sample_rsp_status;
static ITSK00144_2Reserved0* sample_req_list;
static I2XTrafficSafetyDeviceList* sample_rsp_list;
static I2XTrafficSafetyDeviceList* sample_req_update_list;
static I2XTrafficSafetyDeviceList* sample_rsp_update_list;
static ITSK00144_2Reserved0* sample_reset;
static ITSK00144_2Reserved0* sample_ack;
static ITSK00144_2Reserved0* sample_nack;

static I2XTrafficSafetyDeviceSerialNo sample_serial_no =
{
	0x50, 0x0000000011
};

static I2XTrafficSafetyDeviceLinkUnitStatus* init_sample_link_unit_status(Dz1Error *errp)
{
	I2XTrafficSafetyDeviceLinkUnitStatus* ret = NULL;

	if ((ret = I2XTrafficSafetyDeviceLinkUnitStatus_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(I2XTrafficSafetyDeviceLinkUnitStatus_delAndSetNull, (void*)&ret);

		ret->isActive = TRUE;
		ret->control_comm = TRUE;
		ret->wave_comm = TRUE;
		ret->temperature = 36;
		ret->humidity = 60;
		ret->isOpen = TRUE;
		ret->isFanOn = TRUE;
		ret->isHeaterOn = TRUE;
		pthread_cleanup_pop(errp->code); // (I2XTrafficSafetyDeviceLinkUnitStatus_delAndSetNull, (void*)&ret);
	}
	return ret;
}

ITSK00144_2Data* init_sample_data(ITSK00144_2DataPresent present, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	ITSK00144_2Data* ret = NULL;

	if ((ret = ITSK00144_2Data_gen(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(ITSK00144_2Data_delAndSetNull, (void*)&ret);
		switch (present)
		{
			case ITSK00144_2DataPresent_req_link_unit_status:
			case ITSK00144_2DataPresent_req_status:
			case ITSK00144_2DataPresent_req_list:
			case ITSK00144_2DataPresent_reset:
			case ITSK00144_2DataPresent_ack:
			case ITSK00144_2DataPresent_nack:
				break;

			case ITSK00144_2DataPresent_rsp_link_unit_status:
				if ((ret->x.rsp_link_unit_status = init_sample_link_unit_status(errp)) == NULL) ERR_OUT(errp);
				else
				{
					ret->present = present;
					Dz1Error_set(errp, 0);
				}
				break;

			case ITSK00144_2DataPresent_rsp_status:
				break;
			
			case ITSK00144_2DataPresent_rsp_list:
			case ITSK00144_2DataPresent_req_update_list:
			case ITSK00144_2DataPresent_rsp_update_list:
				break;
		}
		pthread_cleanup_pop(errp->code); //(ITSK00144_2Data_delAndSetNull, (void*)&ret);
	}
	return ret;
}

static Dz1TaskProcStatus _test_enc(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;

	ITSK00144_2ProtocolFrame* fs = NULL;
	ITSK00144_2ProtocolFrame* fr = NULL;

	I2XTrafficSafetyDeviceSerialNo_dump(&sample_serial_no, 0);



	if ((fs = ITSK00144_2ProtocolFrame_fromITSK00144_2Reserved0(&sample_serial_no, 1, ITSK00144_2DataPresent_req_link_unit_status, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ITSK00144_2ProtocolFrame_dump(fs, 4);
		Dz1Binary* src = NULL;
		if ((src = ITSK00144_2ProtocolFrame_encode(fs, errp)) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Binary_dump(src, 0);

			ITSK00144_2ProtocolFrame *dec = NULL; 
			if ((dec = ITSK00144_2ProtocolFrame_decode(src, errp)) == NULL) ERR_OUT(errp);
			else
			{
				ITSK00144_2ProtocolFrame_dump(dec, 4);
				Dz1Error_set(errp, 0);
			}
		}
	}

	Dz1Thread_printf("\n\n\n");

	ITSK00144_2Data* d = NULL;
	if ((d = init_sample_data(ITSK00144_2DataPresent_rsp_link_unit_status, errp)) == NULL) ERR_OUT(errp);
	else if ((fr = ITSK00144_2ProtocolFrame_fromITSK00144_2Data(&sample_serial_no, 1, d, Dz1IOStreamEndian_big, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		ITSK00144_2ProtocolFrame_dump(fr, 4);
		Dz1Binary* src = NULL;
		if ((src = ITSK00144_2ProtocolFrame_encode(fr, errp)) == FALSE) ERR_OUT(errp);
		else
		{
			Dz1Binary_dump(src, 0);

			ITSK00144_2ProtocolFrame* dec = NULL;
			if ((dec = ITSK00144_2ProtocolFrame_decode(src, errp)) == NULL) ERR_OUT(errp);
			else
			{
				ITSK00144_2ProtocolFrame_dump(dec, 4);
				Dz1Error_set(errp, 0);
			}
		}
	}
	return ret;
}


static Dz1TaskProcStatus _test_dec(void* uArg, void* uRsc, void* timer, Dz1TaskSigMsg** sg, Dz1Error* errp)
{
	Dz1TaskProcStatus ret = Dz1TaskProcStatus_processed;

	ITSK001442TestScenarioArg* arg = (ITSK001442TestScenarioArg*)uArg;
	ITSK001442TestScenarioEnv* env = (ITSK001442TestScenarioEnv*)uRsc;


	return ret;
}



bool_t ITSK00144_2TestScenarioTest_enc(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if ((*errp = Dz1Task_postSimple(task, DZ1_TASK_QUEUE_NONE, ITSK00144_2_TEST_SCENARIO_TEST_ENC)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
bool_t ITSK00144_2TestScenarioTest_dec(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);


	return ERR_IS_SUCCESS(errp);
}

bool_t ITSK00144_2TestScenarioTest_msgInit(void* task, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (0) {}
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00144_2_TEST_SCENARIO_TEST_ENC), _test_enc)).code);
	else if ((*errp = Dz1Task_regMsg(task, DZ1_TASK_MSG_EXACT(ITSK00144_2_TEST_SCENARIO_TEST_DEC), _test_dec)).code);
	else Dz1Error_set(errp, 0);

	return ERR_IS_SUCCESS(errp);
}
