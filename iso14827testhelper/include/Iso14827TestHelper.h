#ifndef ISO14827_TEST_HELPER_H
#define ISO14827_TEST_HELPER_H

#include <Iso14827TestHelperDef.h>

#define MY14827_PKT_DUMP_FLAG	(ITS_ISO14827_PACKET_DUMP_PDU_LOGIN |\
								 ITS_ISO14827_PACKET_DUMP_PDU_TERM |\
								 ITS_ISO14827_PACKET_DUMP_PDU_LOGOUT |\
								 ITS_ISO14827_PACKET_DUMP_PDU_SUBSCRIPTION |\
								 ITS_ISO14827_PACKET_DUMP_PDU_PUBLICATION |\
								 ITS_ISO14827_PACKET_DUMP_PDU_TRANSFER_DONE |\
								 ITS_ISO14827_PACKET_DUMP_PDU_ACCEPT |\
								 ITS_ISO14827_PACKET_DUMP_PDU_REJECT)

#define DEFAULT_HB_DUR	25
#define DEFAULT_RSP_TIMEOUT	7
#define DEFAULT_INITIAL_CODEC Dz1Asn1Codec_ber

DZ1_CPPLINK void *Iso14827TestHelper_new(void *tMain, Dz1Str testScenario, Iso14827TestHelperException exceptionProc, void *exceptionArg, Dz1Error *err);
DZ1_CPPLINK void Iso14827TestHelper_del(void *task);


DZ1_CPPLINK bool_t Iso14827TestHeleprTest_test(void* task, Dz1Error* err);
DZ1_CPPLINK bool_t Iso14827TestHeleprTest_tr1(void* task, Dz1Error* err);

#endif // ISO14827_TEST_HELPER
