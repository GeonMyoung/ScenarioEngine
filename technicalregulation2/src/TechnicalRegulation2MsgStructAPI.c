#include <dz1_gasn_support.h>
#include "TechnicalRegulation2EamDz1.h"

#include "TechnicalRegulation2MsgStructAPI.h"

#define TECHNICAL_REGULATION2_EAMP_PATH_201			Dz1T("comm_tx_pdu_list.json.txt")
#define TECHNICAL_REGULATION2_EAMP_PATH_202			Dz1T("comm_rx_pdu_list.json.txt")





static void* CommTxPDUList_convert(void* db_list_ptr, Dz1Error* errp)
{
	CommTxPDUList* list = (CommTxPDUList*)db_list_ptr;
	CommTxPDUEntry* entry = NULL;

	Dz1CommTxPDU* data = NULL;
	Dz1CommTxPDUResponse* p = NULL;
	if ((p = Dz1CommTxPDUResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CommTxPDUResponse_delAndSetNull, (void*)&p);
		while (errp->code == 0 && (entry = list->getHead(list)) != NULL)
		{
			list->extract(list, entry);
			pthread_cleanup_push(CommTxPDUEntry_delAndSetNull, (void*)&entry);
			if ((data = Dz1CommTxPDU_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1CommTxPDU_delAndSetNull, (void*)&data);

				if (0) {}
				else if ((data->ipAddressServicePort = Dz1NetworkInfo_new(NULL, entry->servicePort, NULL, errp)) == NULL) ERR_OUT(errp);
				else if ((data->ipAddressServicePort->ipAddress = Dz1Asn1UTF8Str_newFromStr(entry->ipAddress, errp)) == NULL) ERR_OUT(errp);
				else if ((data->ipAddressServicePort->providerServiceContext = Dz1Asn1UTF8Str_newFromStr(entry->provideServiceContext, errp)) == NULL) ERR_OUT(errp);
				else if ((data->deliveryStart = Dz1TimeVal_newFromTime(&entry->deliveryStart, errp)) == NULL) ERR_OUT(errp);	// fixed : Jake Lim
				else if ((data->deliveryStop = Dz1TimeVal_newFromTime(&entry->deliveryStop, errp)) == NULL) ERR_OUT(errp);		// fixed : Jake Lim
				else if ((data->signature = Dz1Bool_clone(&entry->signature, errp)) == NULL) ERR_OUT(errp);
				else if ((data->payloadType = Dz1s64_clone(&entry->payloadType, errp)) == NULL) ERR_OUT(errp);
				// else if ((data->payload = Dz1Asn1UTF8Str_newFromStr(entry->payload, errp)) == NULL) ERR_OUT(errp);
				else if ((data->payload = Dz1Asn1UTF8Str_new(entry->payload->data, entry->payload->size, errp)) == NULL) ERR_OUT(errp);
				else if ((data->txPower = Dz1s8_clone(&entry->txPower, errp)) == NULL) ERR_OUT(errp);
				else if ((data->txDataRate = Dz1u8_clone(&entry->txDataRate, errp)) == NULL) ERR_OUT(errp);
				else if ((data->channelNumberHdrExt = Dz1Bool_clone(&entry->channelNumberHdrExt, errp)) == NULL) ERR_OUT(errp);
				else if ((data->dataRateHdrExt = Dz1Bool_clone(&entry->dataRateHdrExt, errp)) == NULL) ERR_OUT(errp);
				else if ((data->txPowerHdrExt = Dz1Bool_clone(&entry->txPowerHdrExt, errp)) == NULL) ERR_OUT(errp);
				else
				{
					data->index = entry->idx;
					data->psid = entry->psid;
					data->priority = entry->priority;
					data->channel = entry->channel;
					data->txInterval = entry->txInterval;
					if ((*errp = p->add(p, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1CommTxPDU_delAndSetNull, (void *)&data);
			}
			pthread_cleanup_pop(1); // (CommTxPDUEntry_delAndSetNull, (void*)&entry);
		}
		pthread_cleanup_pop(errp->code); // (Dz1CommTxPDUResponse_delAndSetNull, (void *)&p);
	}
	return p;
}
static _encoder_declare_(Dz1CommTxPDUResponse, CommTxPDUResponse)
static _decoder_declare_(Dz1CommTxPDUResponse, CommTxPDUResponse)
static _get_eam_list_declare_(TechnicalRegulation2, CommTxPDUList, comm_tx_pdu, "TechnicalRegulation2_Eam", TECHNICAL_REGULATION2_EAMP_PATH_201)

static void* CommRxPDUList_convert(void* db_list_ptr, Dz1Error* errp)
{
	CommRxPDUList* list = (CommRxPDUList*)db_list_ptr;
	CommRxPDUEntry* entry = NULL;

	Dz1CommRxPDU* data = NULL;
	Dz1CommRxPDUResponse* p = NULL;
	if ((p = Dz1CommRxPDUResponse_new(errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1CommRxPDUResponse_delAndSetNull, (void*)&p);
		while ((entry = list->getHead(list)) != NULL)
		{
			list->extract(list, entry);
			pthread_cleanup_push(CommRxPDUEntry_delAndSetNull, (void*)&entry);
			if ((data = Dz1CommRxPDU_gen(errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1CommRxPDU_delAndSetNull, (void*)&data);

				if (0) {}
				else if ((data->peerAddress = Dz1Asn1UTF8Str_newFromStr(entry->peerAddress, errp)) == NULL) ERR_OUT(errp);
				else if ((data->sign = Dz1Bool_clone(&entry->sign, errp)) == NULL) ERR_OUT(errp);
				else if ((data->payloadType = Dz1s64_clone(&entry->payloadType, errp)) == NULL) ERR_OUT(errp);
				// else if ((data->payload = Dz1Asn1UTF8Str_newFromStr(entry->payload, errp)) == NULL) ERR_OUT(errp);
				else if ((data->payload = Dz1Asn1UTF8Str_new(entry->payload->data, entry->payload->size, errp)) == NULL) ERR_OUT(errp);
				else
				{
					data->psid = entry->psid;
					data->channel = entry->channel;
					data->rcpi = entry->rcpi;
					if ((*errp = p->add(p, data)).code) ERR_OUT(errp);
					else
					{
						data = NULL;
						entry = NULL;
						Dz1Error_set(errp, 0);
					}
				}
				pthread_cleanup_pop(1); // (Dz1CommTxPDU_delAndSetNull, (void *)&data);
			}
			pthread_cleanup_pop(1); // (CommTxPDUEntry_delAndSetNull, (void*)&entry);
		}
		pthread_cleanup_pop(errp->code); // (Dz1CommTxPDUResponse_delAndSetNull, (void *)&p);
	}
	return p;
}


static _encoder_declare_(Dz1CommRxPDUResponse, CommRxPDUResponse)
static _decoder_declare_(Dz1CommRxPDUResponse, CommRxPDUResponse)
static _get_eam_list_declare_(TechnicalRegulation2, CommRxPDUList, comm_rx_pdu, "TechnicalRegulation2_Eam", TECHNICAL_REGULATION2_EAMP_PATH_202)

static u8_t sample_map[] = {
	0x00, 0x12, 0x80, 0xA9,
	0x7F, 0x1E, 0x87, 0xA8, 0x01, 0x06, 0x07, 0x03, 0x83, 0x0A, 0x1C, 0x48, 0x00, 0x28, 0x03, 0x20,
	0x04, 0xD6, 0x93, 0xA4, 0x01, 0xAD, 0x27, 0x47, 0xFC, 0x40, 0x28, 0x03, 0x20, 0x10, 0x0C, 0x80,
	0x0F, 0xC0, 0x01, 0xC1, 0x85, 0x0E, 0x20, 0x02, 0xC5, 0x81, 0x01, 0x27, 0x00, 0x08, 0x80, 0x20,
	0x07, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x96, 0x80, 0x20, 0x06, 0xC0, 0x00, 0x40, 0x00, 0x3F, 0x00,
	0x00, 0x00, 0x00, 0x04, 0xB4, 0x01, 0x00, 0x00, 0x40, 0x24, 0xE0, 0x00, 0x01, 0xC1, 0xC1, 0x85,
	0x0E, 0x24, 0x00, 0x14, 0x00, 0x14, 0x02, 0x6B, 0x49, 0xD2, 0x00, 0xD6, 0x93, 0xA3, 0xFE, 0x20,
	0x14, 0x01, 0x90, 0x08, 0x06, 0x40, 0x07, 0xE0, 0x00, 0xE0, 0xC2, 0x87, 0x10, 0x00, 0x62, 0x80,
	0x80, 0x93, 0x00, 0x04, 0x40, 0x10, 0x03, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x4B, 0x40, 0x10, 0x03,
	0x60, 0x00, 0x20, 0x00, 0x1F, 0x80, 0x00, 0x00, 0x00, 0x02, 0x5A, 0x00, 0x80, 0x00, 0x20, 0x12,
	0x60, 0x00, 0x1E, 0x07, 0x06, 0x14, 0x38, 0x80, 0x70, 0x61, 0x43, 0x88, 0x07, 0x06, 0x14, 0x38,
	0x80, 0x70, 0x61, 0x43, 0x88, 0x00, 0x00, 0x00, 0x00
};

static u8_t  sample_spat[] =
{
	0x00, 0x13, 0x40,
	0x63, 0xD0, 0xF5, 0x0E, 0x0C, 0x28, 0x71, 0x00, 0xF8, 0x38, 0x30, 0xA1, 0xC4, 0x80, 0x02, 0x80,
	0x32, 0x00, 0xC1, 0x90, 0x3D, 0x0F, 0x50, 0x00, 0x00, 0x00, 0x00, 0x60, 0xE0, 0xC2, 0x87, 0x10,
	0x10, 0x18, 0x7E, 0x60, 0x72, 0x60, 0x72, 0x60, 0x72, 0x60, 0x72, 0x06, 0x07, 0x20, 0xF0, 0x41,
	0x50, 0x07, 0x80, 0x01, 0xE0, 0xF0, 0x07, 0x80, 0x1E, 0x81, 0xE0, 0xF0, 0x07, 0x80, 0x1E, 0x80
};

static u8_t sample_bsm[] =
{
	0x00, 0x14, 0x25, 0x00, 0x10, 0x50, 0x90, 0xD1, 0x00, 0x00, 0x1A, 0xD2, 0x74, 0x80, 0x35, 0xA4,
	0xE8, 0xFF, 0x88, 0x05, 0x32, 0x05, 0x00, 0x19, 0x10, 0x05, 0x00, 0x14, 0x7E, 0xBE, 0x83, 0xE8,
	0x3F, 0xBF, 0xFF, 0xD2, 0xAA, 0x64, 0x04, 0xB0
};

static u8_t sample_pvd[] = {
	0x00, 0x1A, 0x81, 0x18,
	0x71, 0xE8, 0x7A, 0x80, 0x01, 0x7E, 0x1C, 0x18, 0x50, 0xE2, 0x0D, 0x05, 0x09, 0x0D, 0x10, 0x70,
	0x61, 0x43, 0x88, 0x41, 0x42, 0x43, 0x44, 0x08, 0x03, 0xFF, 0xFB, 0xF4, 0xD8, 0x56, 0x58, 0x00,
	0x03, 0x48, 0x6B, 0x49, 0xD1, 0xFF, 0x6B, 0x49, 0xD2, 0x00, 0x20, 0x14, 0x00, 0x50, 0x81, 0x91,
	0x90, 0x28, 0x00, 0xCA, 0x79, 0xCD, 0x67, 0xF8, 0x14, 0x80, 0x01, 0x00, 0x10, 0x50, 0x03, 0xFF,
	0xFE, 0xFD, 0x36, 0x15, 0x96, 0x00, 0x00, 0xD2, 0x1A, 0xD2, 0x74, 0x7F, 0xDA, 0xD2, 0x74, 0x80,
	0x08, 0x05, 0x00, 0x14, 0x20, 0x64, 0x64, 0x0A, 0x00, 0x32, 0x9E, 0x73, 0x59, 0xE9, 0x81, 0x3F,
	0xFF, 0xEF, 0xD3, 0x61, 0x59, 0x60, 0x00, 0x0D, 0x21, 0xAD, 0x27, 0x47, 0xFD, 0xAD, 0x27, 0x48,
	0x00, 0x80, 0x50, 0x01, 0x42, 0x06, 0x46, 0x40, 0xA0, 0x03, 0x29, 0xE7, 0x35, 0xAC, 0xC1, 0xE0,
	0x00, 0x08, 0x00, 0x02, 0x00, 0x00, 0x02, 0x40, 0x28, 0xC8, 0x14, 0x00, 0x64, 0x14, 0xFF, 0xFE,
	0x64, 0x94, 0x3F, 0xFF, 0xFF, 0x4A, 0x0E, 0x21, 0x44, 0x2D, 0x2A, 0xA1, 0x14, 0x0A, 0x00, 0x42,
	0x9D, 0xFA, 0x7F, 0x80, 0xFD, 0xF4, 0x1F, 0x41, 0xFD, 0xFF, 0xFE, 0x9D, 0xDF, 0xFB, 0xDA, 0xD3,
	0xCE, 0x5A, 0x00, 0x18, 0x00, 0x17, 0xFB, 0xF4, 0xD8, 0x56, 0x58, 0x00, 0x03, 0x48, 0xFF, 0xFE,
	0xFD, 0x36, 0x15, 0x96, 0x00, 0x00, 0xD2, 0x1A, 0xD2, 0x74, 0x7F, 0xDA, 0xD2, 0x74, 0x80, 0x08,
	0x05, 0x00, 0x14, 0x20, 0x64, 0x64, 0x0A, 0x00, 0x32, 0x9E, 0x73, 0x58, 0x7B, 0x5A, 0xE4, 0x50,
	0xA1, 0x44, 0x04, 0xB0, 0x2F, 0xC3, 0x83, 0x0A, 0x1C, 0x41, 0xA0, 0xA1, 0x21, 0xA2, 0x0E, 0x0C,
	0x28, 0x71, 0x08, 0x28, 0x48, 0x68, 0x81, 0x00, 0x3F, 0xF0, 0x7F, 0x14, 0x1E, 0x22, 0xE8, 0x40,
	0x06, 0x40, 0x0C, 0xA0, 0x01, 0xE0, 0x04, 0xB0, 0x03, 0x21, 0x18, 0x50, 0x14, 0x46, 0x14, 0x14,
	0xF4, 0x9C, 0x40, 0x80, 0x19, 0x05, 0x59, 0x80
};

static u8_t sample_rsa[] = {
	0x00, 0x1B, 0x2D, 0x7F, 0x00, 0x3D, 0x0F, 0x50, 0x06, 0xF0, 0x00, 0xDE, 0x83, 0x83, 0x21, 0xEF,
	0xFF, 0xEF, 0xD3, 0x61, 0x59, 0x60, 0x00, 0x0D, 0x21, 0xAD, 0x27, 0x47, 0xFD, 0xAD, 0x27, 0x48,
	0x00, 0x80, 0x50, 0x01, 0x42, 0x06, 0x46, 0x40, 0xA0, 0x03, 0x29, 0xE7, 0x35, 0x90, 0x50, 0x80
};

static u8_t sample_tim[] = {
	0x00, 0x1F, 0x56, 0x70, 0x03, 0xD0, 0xF5, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
	0x0A, 0xAD, 0x29, 0x81, 0x80, 0x10, 0x50, 0x9F, 0xA4, 0xF4, 0x3D, 0x40, 0x1E, 0x20, 0x03, 0xFC,
	0x1C, 0x18, 0x50, 0xE2, 0x40, 0x01, 0x40, 0x01, 0x53, 0x5A, 0x4E, 0x90, 0x06, 0xB4, 0x9D, 0x1F,
	0xF1, 0x00, 0xA0, 0x0C, 0x9F, 0x06, 0x40, 0x40, 0x00, 0x88, 0x02, 0x00, 0x7E, 0x00, 0x00, 0x00,
	0x00, 0x09, 0x68, 0x02, 0x00, 0x44, 0x01, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x04, 0xB4, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x01, 0xBC, 0xBA, 0xF2, 0xD8
};

static u8_t sample_tim2[] = {
	0x00, 0x1F, 0x4D, 0x50, 0x03, 0xD0, 0xF5, 0x0A, 0xAD, 0x29, 0x81, 0x80, 0x10, 0x50, 0x9F, 0xA4,
	0xF4, 0x3D, 0x40, 0x1E, 0x20, 0x03, 0xFC, 0x1C, 0x18, 0x50, 0xE2, 0x40, 0x01, 0x40, 0x01, 0x53,
	0x5A, 0x4E, 0x90, 0x06, 0xB4, 0x9D, 0x1F, 0xF1, 0x00, 0xA0, 0x0C, 0x9F, 0x06, 0x40, 0x40, 0x00,
	0x88, 0x02, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x09, 0x68, 0x02, 0x00, 0x44, 0x01, 0x00, 0x3F,
	0x00, 0x00, 0x00, 0x00, 0x04, 0xB4, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0xBC, 0xBA, 0xF2, 0xD8
};


static u8_t sample_sdsm[] = {
	0x00, 0x29, 0x4F,
	0x80, 0x41, 0x42, 0x43, 0x44, 0x3F, 0xDF, 0xA6, 0xC2, 0xB2, 0xC0, 0x00, 0x1A, 0x42, 0x6B, 0x49,
	0xD2, 0x00, 0xD6, 0x93, 0xA3, 0xFE, 0x20, 0x14, 0xC8, 0x14, 0x00, 0x65, 0x80, 0x17, 0xF0, 0x28,
	0x00, 0x09, 0x90, 0x27, 0xBF, 0xFF, 0xBF, 0xFF, 0xBF, 0xFF, 0xCE, 0x00, 0x2A, 0x80, 0x2A, 0x80,
	0x14, 0xD7, 0xD0, 0x7D, 0x07, 0xF7, 0xFF, 0xF7, 0x77, 0xE3, 0xFF, 0x4A, 0x1C, 0x5C, 0x71, 0x0C,
	0xE2, 0x43, 0x6D, 0x00, 0xC7, 0x00, 0xC7, 0xFE, 0xC8, 0x09, 0x66, 0x4E, 0x66, 0x02, 0x8A
};

static u8_t sample_invalid[] = { 0xFF };

static u8_t sample_empty_list[] = { 0x30, 0x00 };


static Dz1Binary b_sample_map = { sample_map, 173 };
static Dz1Binary b_sample_spat = { sample_spat, 67 };
static Dz1Binary b_sample_bsm = { sample_bsm, 40 };
static Dz1Binary b_sample_pvd = { sample_pvd, 284 };
static Dz1Binary b_sample_rsa = { sample_rsa, 48 };
static Dz1Binary b_sample_tim = { sample_tim, 89 };
static Dz1Binary b_sample_tim2 = { sample_tim, 80 };
static Dz1Binary b_sample_sdsm = { sample_sdsm, 82 };

static Dz1Binary b_sample_invalid = { sample_invalid, 2 };
static Dz1Binary b_sample_invalid2 = { sample_empty_list, 2 };

const static time_t GetTimeT(int year, int mon, int day, int hour, int min)
{
	struct tm cur = { 0 };
	cur.tm_year = year - 1900;
	cur.tm_mon = mon - 1;
	cur.tm_mday = day;
	cur.tm_hour = hour;
	cur.tm_min = min;
	return mktime(&cur);
}

static CommTxPDUEntry commtxpduentry_arr[] =
{
	{1,82056,1,1,1,Dz1T("1"), 1, Dz1T("1"), 1, 2, TRUE, 18, &b_sample_map, 1, 1, TRUE, TRUE, TRUE},
	{2,82055,2,2,2,Dz1T("2"), 2, Dz1T("2"), 2, 9, TRUE, 19, &b_sample_spat, 2, 2, TRUE, TRUE, TRUE},
	{3,82051,3,3,3,Dz1T("3"), 3, Dz1T("3"), 4, 3, TRUE, 26, &b_sample_pvd, 3, 3, TRUE, TRUE, TRUE},
	{4,90000,3,3,3,Dz1T("3"), 3, Dz1T("3"), 4, 3, TRUE, 41, &b_sample_sdsm, 3, 3, TRUE, TRUE, TRUE},
	{5,82053,5,5,5,Dz1T("5"), 5, Dz1T("5"), 1, 2, TRUE, 27, &b_sample_rsa, 1, 1, TRUE, TRUE, TRUE},
	{6,82054,6,6,6,Dz1T("6"), 6, Dz1T("6"), 2, 9, TRUE, 31, &b_sample_tim2, 2, 2, TRUE, TRUE, TRUE},


	// {9,9999,1,1,1,Dz1T("1"), 1, Dz1T("1"), 1, 2, TRUE, 9999, &b_sample_invalid, 1, 1, TRUE, TRUE, TRUE},
	{9,9999,1,1,1,Dz1T("1"), 1, Dz1T("1"), 1, 2, TRUE, 9999, &b_sample_invalid2, 1, 1, TRUE, TRUE, TRUE},
	{0,0,0,0,0,NULL,0,NULL,0,0,FALSE,0,NULL,0,0,FALSE,FALSE,FALSE}
};

static bool_t CommTxPDUList_init_sample_data(CommTxPDUList* p, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		time_t t;
		CommTxPDUEntry* i;
		for (i = commtxpduentry_arr; errp->code == 0 && i->payload != NULL; i++)
		{
			CommTxPDUEntry* e;
			if ((e = CommTxPDUEntry_new(i->idx, i->psid, i->priority, i->channel, i->txInterval, (t = time(NULL) - i->deliveryStop), t + i->deliveryStart, i->payload, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(CommTxPDUEntry_delAndSetNull, (void*)&e);
				e->payloadType = i->payloadType;
				e->ipAddress = Dz1Str_clone(i->ipAddress, errp);
				e->provideServiceContext = Dz1Str_clone(i->provideServiceContext, errp);
				if ((*errp = p->add(p, e)).code) ERR_OUT(errp);
				else
				{
					e = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (CommTxPDUEntry_delAndSetNull, (void*)&e);
			}
		}
		Dz1Thread_printf("init_sample_data = \n");
		CommTxPDUList_dump(p, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t CommTxPDUList_init_sample_data_by_psid(CommTxPDUList* p, u32_t psid, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		CommTxPDUEntry* i = NULL;
		for (i = commtxpduentry_arr; errp->code == 0 && i->payload != NULL;i++)
		{
			time_t t;
			CommTxPDUEntry* e = NULL;
			if (i->psid == psid)
			{
				if ((e = CommTxPDUEntry_new(i->idx, i->psid, i->priority, i->channel, i->txInterval, (t = time(NULL) - i->deliveryStop), t + i->deliveryStart, i->payload, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(CommTxPDUEntry_delAndSetNull, (void*)&e);
					e->payloadType = i->payloadType;
					e->ipAddress = Dz1Str_clone(i->ipAddress, errp);
					e->provideServiceContext = Dz1Str_clone(i->provideServiceContext, errp);
					if ((*errp = p->add(p, e)).code) ERR_OUT(errp);
					else
					{
						e = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (CommTxPDUEntry_delAndSetNull, (void*)&e);
				}
				break;
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t CommTxPDUList_init_sample_data_by_psid_and_payload_type(CommTxPDUList* p, u32_t psid, u32_t payloadType, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		CommTxPDUEntry* i = NULL;
		for (i = commtxpduentry_arr; errp->code == 0 && i->payload != NULL;i++)
		{
			time_t t;
			CommTxPDUEntry* e = NULL;
			if (i->psid == psid && i->payloadType == payloadType)
			{
				if ((e = CommTxPDUEntry_new(i->idx, i->psid, i->priority, i->channel, i->txInterval, (t = time(NULL) - i->deliveryStop), t + i->deliveryStart, i->payload, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(CommTxPDUEntry_delAndSetNull, (void*)&e);
					e->payloadType = i->payloadType;
					e->ipAddress = Dz1Str_clone(i->ipAddress, errp);
					e->provideServiceContext = Dz1Str_clone(i->provideServiceContext, errp);
					if ((*errp = p->add(p, e)).code) ERR_OUT(errp);
					else
					{
						e = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (CommTxPDUEntry_delAndSetNull, (void*)&e);
				}
				break;
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static CommRxPDUEntry commrxpduentry_arr[] =
{
	{82050, 1, 1, Dz1T("1"), TRUE, 20, &b_sample_bsm},
	// {82051, 1, 1, Dz1T("1"), TRUE, 26, &b_sample_pvd },
	//{9999, 1, 1, Dz1T("1"), TRUE, 9999, &b_sample_invalid },
	 {9999, 1, 1, Dz1T("1"), TRUE, 9999, &b_sample_invalid2 },
	{0, 0, 0, NULL, FALSE, 0, NULL}
};

static bool_t CommRxPDUList_init_sample_data(CommRxPDUList* p, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		CommRxPDUEntry* i;
		for (i = commrxpduentry_arr; errp->code == 0 && i->payload != NULL; i++)
		{
			CommRxPDUEntry* e;
			if ((e = CommRxPDUEntry_clone(i, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(CommRxPDUEntry_delAndSetNull, (void*)&e);
				if ((*errp = p->add(p, e)).code) ERR_OUT(errp);
				else
				{
					e = NULL;
					Dz1Error_set(errp, 0);
				}
				pthread_cleanup_pop(1); // (CommRxPDUEntry_delAndSetNull, (void*)&e);
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t CommRxPDUList_init_sample_data_by_psid(CommRxPDUList* p, u32_t psid, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		CommRxPDUEntry* i;
		for (i = commrxpduentry_arr; errp->code == 0 && i->payload != NULL; i++)
		{
			if (i->psid == psid)
			{
				CommRxPDUEntry* e;
				if ((e = CommRxPDUEntry_clone(i, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(CommRxPDUEntry_delAndSetNull, (void*)&e);
					if ((*errp = p->add(p, e)).code) ERR_OUT(errp);
					else
					{
						e = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (CommRxPDUEntry_delAndSetNull, (void*)&e);
				}
				break;
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}

static bool_t CommRxPDUList_init_sample_data_by_psid_and_payload_type(CommRxPDUList* p, u32_t psid, u32_t payloadType, Dz1Error* err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (p == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		CommRxPDUEntry* i;
		for (i = commrxpduentry_arr; errp->code == 0 && i->payload != NULL; i++)
		{
			if (i->psid == psid && i->payloadType == payloadType)
			{
				CommRxPDUEntry* e;
				if ((e = CommRxPDUEntry_clone(i, errp)) == NULL) ERR_OUT(errp);
				else
				{
					pthread_cleanup_push(CommRxPDUEntry_delAndSetNull, (void*)&e);
					if ((*errp = p->add(p, e)).code) ERR_OUT(errp);
					else
					{
						e = NULL;
						Dz1Error_set(errp, 0);
					}
					pthread_cleanup_pop(1); // (CommRxPDUEntry_delAndSetNull, (void*)&e);
				}
				break;
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}

Iso14827TestMsgStructAPI TechnicalRegulation2MsgSet[] =
{	// XXX : gmkim = 각 자료 구조별 변환/인코드 API 등록
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.15784.2.0.1"), CommTxPDUList, Dz1CommTxPDUResponse),
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.15784.2.0.2"), CommRxPDUList, Dz1CommRxPDUResponse),	
	{ NULL, NULL }
};

Iso14827TestMsgStructAPI TechnicalRegulation2MsgTx[] =
{
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.15784.2.0.1"), CommTxPDUList, Dz1CommTxPDUResponse),
	{NULL, NULL}
};

Iso14827TestMsgStructAPI TechnicalRegulation2MsgRx[] =
{
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.15784.2.0.2"), CommRxPDUList, Dz1CommRxPDUResponse),
	{NULL, NULL}
};


Iso14827TestMsgStructAPI TechnicalRegulation2MsgTx_itsk[] =
{
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.15784.1.0.1"), CommTxPDUList, Dz1CommTxPDUResponse),
	{NULL, NULL}
};

Iso14827TestMsgStructAPI TechnicalRegulation2MsgRx_itsk[] =
{
	Iso14827TestMsgUtilAPIEntry(Dz1T("1.0.15784.1.0.2"), CommRxPDUList, Dz1CommRxPDUResponse),
	{NULL, NULL}
};
