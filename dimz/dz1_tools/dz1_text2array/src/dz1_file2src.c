#include "dz1_file2src_data_util.h"
#include <dz1_file2src.h>

Dz1Error Dz1File2Src_convert(File2SrcConvArg *arg, u32_t output_opt)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	Dz1File2SrcData *data = Dz1File2SrcData_new(&err);
	if (data == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1File2SrcData_delAndSetNull, (void *)&data);
		if ((err = Dz1File2SrcData_read(data, arg)).code) ERR_OUT(&err);
		else if (output_opt & DZ1_FILE2SRC_OUTPUT_HEADER_STATIC)
		{
			if ((err = Dz1File2Src_publishHdrStatic(data, arg)).code) ERR_OUT(&err);
		}
		else
		{
			if ((output_opt & DZ1_FILE2SRC_OUTPUT_HEADER) && (err = Dz1File2Src_publishHdr(data, arg)).code) ERR_OUT(&err);
			else if ((output_opt & DZ1_FILE2SRC_OUTPUT_SOURCE) && (err = Dz1File2Src_publishSrc(data, arg)).code) ERR_OUT(&err);
		}
		pthread_cleanup_pop(1); // (Dz1File2SrcData_delAndSetNull, (void *)&data);
	}
	return err;
}