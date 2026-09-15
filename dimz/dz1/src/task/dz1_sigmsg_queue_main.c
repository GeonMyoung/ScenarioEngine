#include "dz1_sigmsg_queue.h"

int main(void)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	u32_t id = Dz1SigMsgQueue_new(10, &err);
	if (id == -1) { ERR_OUT(&err); }
	else
	{
		pthread_cleanup_push(Dz1SigMsgQueue_cancel, (void *)&id);

		if ((err = Dz1SigMsgQueue_post(id, id, 0x1,
										NULL,	// void **msg
										NULL,	// Dz1DelFunc del
										NULL,	// Dz1DumpFunc dump
										NULL,	// Dz1Error *initialStatus
										NULL,	// Dz1TaskSigMsgCallbackFunc msgTerm
										NULL	// void *param
										)).code) { ERR_OUT(&err); }

		pthread_cleanup_pop(1); // (Dz1SigMsgQueue_cancel, (void *)&id);
	}
	return err.code;
}
