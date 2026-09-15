#include "sample_util.h"

Dz1TdqSqlBlobToDB *MyDataDBIO_write(MyBinData  *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlBlobToDB *ret = NULL;
	switch(src->present)
	{
	case MyBinDataPresent_fn:
		if ((ret = Dz1TdqSqlBlobToDB_new(Dz1TdqSqlBlobToDBPresent_saved_file, src->x.fn, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		break;
	case MyBinDataPresent_buf:
		if ((ret = Dz1TdqSqlBlobToDB_new(Dz1TdqSqlBlobToDBPresent_ref_buf, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary *buf = src->x.buf;
			pthread_cleanup_push(Dz1TdqSqlBlobToDB_delAndSetNull, (void *)&ret);
			if ((ret->x.ref_buf = Dz1TdqSqlBlobRef_new(buf->data, buf->size, errp)) == NULL) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (Dz1TdqSqlBlobToDB_delAndSetNull, (void *)&ret);
		}
		break;
	default:
		ERR_SET_OUT(errp, EFAULT);
		break;
	}
	return ret;
}

bool_t MyDataDBIO_read(MyBinData **_dst, Dz1TdqSqlVar *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlBlobFromDB *src_blob = NULL;
	if (_dst == NULL || *_dst != NULL) ERR_SET_OUT(errp, EINVAL);
	else if (src == NULL || src->present != Dz1TdqSqlVarPresent_blob) ERR_SET_OUT(errp, EINVAL);
	else if ((src_blob = src->x.blob->readFromDB) == NULL)
	{
		*_dst = NULL;
		Dz1Error_set(errp, 0);
	}
	else
	{
		MyBinData *dst = NULL;
		switch(src_blob->present)
		{
		case Dz1TdqSqlBlobFromDBPresent_embedded:
			if ((*_dst = dst = MyBinData_new(MyBinDataPresent_buf, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				dst->x.buf = src_blob->x.embedded;
				src_blob->x.embedded = NULL;
				Dz1Error_set(errp, 0);
			}
			break;
		case Dz1TdqSqlBlobFromDBPresent_saved_file:
			if ((*_dst = dst = MyBinData_new(MyBinDataPresent_fn, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				dst->x.fn = src_blob->x.saved_file;
				src_blob->x.saved_file = NULL;
				Dz1Error_set(errp, 0);
			}
			break;
		default:
			ERR_SET_OUT(errp, EFAULT);
			break;
		}
	}
	return ERR_IS_SUCCESS(errp);
}

