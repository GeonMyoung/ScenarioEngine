#include <dz1_stdio.h>
#include <dz1_thread_stdio.h>

#include "dz1_task_gen.h"
#include "dz1_task_gen_args_stream.h"
#include "code_gen.h"

bool_t Dz1TaskGen2(GenArgs2 *args, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (Dz1TaskGen2_code_generate(args, errp) == FALSE) ERR_OUT(errp);

	return errp->code == 0 ? TRUE : FALSE;
}

////////////////////////////////////////////////////////////////////////////////
// GenArgs2 Convert Utility
Dz1Error GenArgs2_toStream(GenArgs2 *src, Dz1Stream *dst, Dz1IOStreamEndian ed, void *param)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (src == NULL || dst == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ssize_t sz = 0;
		if ((sz = GenArgs2_write(dst, src, ed, param, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	return err;
}

GenArgs2 *GenArgs2_fromStream(Dz1Stream *src, void *param, Dz1IOStreamEndian ed, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	GenArgs2 *ret = GenArgs2_gen(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t sz = 0;
		pthread_cleanup_push(GenArgs2_delAndSetNull, (void *)&ret);
		if ((sz = GenArgs2_read(ret, src, ed, param, errp)) < 0) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (GenArgs2_delAndSetNull, (void *)&ret);
	}
	return ret;
}
// GenArgs2 Convert Utility
////////////////////////////////////////////////////////////////////////////////
