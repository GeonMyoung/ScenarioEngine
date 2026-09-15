#include "dz1_tdq_util.h"
#include "dz1_tdq_var_def_util.h"

Dz1TdqSqlBlobToDB *Dz1BinaryDB_write(Dz1Binary *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1TdqSqlBlobToDB *ret = NULL;
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = Dz1TdqSqlBlobToDB_new(Dz1TdqSqlBlobToDBPresent_ref_buf, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1TdqSqlBlobToDB_delAndSetNull, (void *)&ret);
		if ((ret->x.ref_buf = Dz1TdqSqlBlobRef_new(src->data, src->size, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1TdqSqlBlobToDB_delAndSetNull, (void *)&ret);
	}
	return ret;
}

bool_t Dz1BinaryDB_read(Dz1Binary **dst, Dz1TdqSqlVar *src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src->present == Dz1TdqSqlVarPresent_nul)
		Dz1Binary_delAndSetNull(dst);
	else if (_category_of(src->present) != 0x04) ERR_SET_OUT(errp, EINVAL);
	else
	{
		Dz1TdqSqlBlob *b = src->x.__ptr__;
		Dz1TdqSqlBlobFromDB *br = b->readFromDB;
		switch(br->present)
		{
		case Dz1TdqSqlBlobFromDBPresent_embedded: // runtime generated binary buffer
			(*dst) = br->x.embedded;
			br->x.embedded = NULL;
			Dz1Error_set(errp, 0);
			break;
		case Dz1TdqSqlBlobFromDBPresent_saved_file:
			if (( (*dst) = Dz1BinFile_load(br->x.saved_file, errp)) == NULL) ERR_OUT(errp);
			else
			{
				Dz1File_delete(br->x.saved_file);
				Dz1Error_set(errp, 0);
			}
			break;
		default:
			break;
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

// static pthread_mutex_t tz_lock = PTHREAD_MUTEX_INITIALIZER;
// static bool_t tz_flag = FALSE;
// static s32_t tz_sec = 0;
// 
// static s32_t Dz1Tdq_TimeZone_init(void)
// {
// 	s32_t ret = 0;
// 	pthread_mutex_lock(&tz_lock);
// 	if (tz_flag == FALSE)
// 	{
// 		time_t tBias, tRef;
// 		struct tm tmB, *tmTemp = NULL, tmR;
// 		tmB.tm_year = 71;			// 1971
// 		tmB.tm_mon = 0;				// 1
// 		tmB.tm_mday = 1;			// 1
// 		tmB.tm_hour = 0;			// 0
// 		tmB.tm_min = 0;				// 0
// 		tmB.tm_sec = 0;				// 0
// 		tBias = mktime(&tmB);		// UTC time
// 		tmTemp = gmtime(&tBias); 
// 		tmR = *tmTemp;				// GMT Date-Time
// 		tRef = mktime(&tmR);		// Ref time
// 
// 		tz_sec = (s32_t)(tBias - tRef);
// 	}
// 	ret = tz_sec;
// 	pthread_mutex_unlock(&tz_lock);
// 	return ret;
// }

time_t Dz1Tdq_mktime(struct tm *p, bool_t is_gmt_tm)
{
	time_t ret = -1;

	if (p == NULL) { }
	else if ((ret = mktime(p)) == -1) { }
	else if (is_gmt_tm) ret += Dz1Time_GetGmtOffset();

	return ret;
}