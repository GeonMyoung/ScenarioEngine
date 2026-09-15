#include "dz1_meta_tag_test_codec.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagData CODEC Test
Dz1Error Dz1MetaTagDataCodec_test(Dz1MetaTagData *src, bool_t verbose)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Binary *bin = NULL;

	if (verbose)
	{
		Dz1Thread_printf("============================================================\n");
		Dz1Thread_printf("SOURCE ="); Dz1MetaTagData_dump(src, 0);
	}

	if ((bin = Dz1MetaTagData_toStream(src, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagData *dec = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if (verbose)
		{
			Dz1Thread_printf("============================================================\n");
			Dz1Thread_printf("STREAM\n");
			Dz1Thread_tprintb(1, bin->data, bin->size, 16, FALSE);
		}

		if ((dec = Dz1MetaTagData_toStruct(bin, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary *chk = NULL;
			pthread_cleanup_push(Dz1MetaTagData_delAndSetNull, (void *)&dec);
			if (verbose)
			{
				Dz1Thread_printf("============================================================\n");
				Dz1Thread_printf("DECODED ="); Dz1MetaTagData_dump(dec, 0);
			}

			if ((chk = Dz1MetaTagData_toStream(dec, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&chk);
				if (bin->size != chk->size)
				{
					Dz1Thread_printf("!!! Different Size\n");
					ERR_SET_OUT(errp, EFAULT);
				}
				else if (memcmp(bin->data, chk->data, bin->size) != 0)
				{
					Dz1Thread_printf("!!! Different Data\n");
					ERR_SET_OUT(errp, EFAULT);
				}
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&chk);
			}
			pthread_cleanup_pop(1); // (Dz1MetaTagData_delAndSetNull, (void *)&dec);
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}
// Dz1MetaTagData CODEC Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1MetaTagDB CODEC Test
Dz1Error Dz1MetaTagDBCodec_test(Dz1MetaTagDB *src, bool_t verbose)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Binary *bin = NULL;

	if (verbose)
	{
		Dz1Thread_printf("============================================================\n");
		Dz1Thread_printf("SOURCE = "); Dz1MetaTagDB_dump(src, 0);
	}

	if ((bin = Dz1MetaTagDB_toStream(src, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagDB *dec = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if (verbose)
		{
			Dz1Thread_printf("============================================================\n");
			Dz1Thread_printf("STREAM\n");
			Dz1Thread_tprintb(1, bin->data, bin->size, 16, FALSE);
		}

		if ((dec = Dz1MetaTagDB_toStruct(bin, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary *chk = NULL;
			pthread_cleanup_push(Dz1MetaTagDB_delAndSetNull, (void *)&dec);
			if (verbose)
			{
				Dz1Thread_printf("============================================================\n");
				Dz1Thread_printf("DECODED = "); Dz1MetaTagDB_dump(dec, 0);
			}

			if ((chk = Dz1MetaTagDB_toStream(dec, NULL, errp)) == NULL) ERR_OUT(errp);
			else
			{
				pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&chk);
				if (bin->size != chk->size)
				{
					Dz1Thread_printf("!!! Different Size\n");
					ERR_SET_OUT(errp, EFAULT);
				}
				else if (memcmp(bin->data, chk->data, bin->size) != 0)
				{
					Dz1Thread_printf("!!! Different Data\n");
					ERR_SET_OUT(errp, EFAULT);
				}
				pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&chk);
			}
			pthread_cleanup_pop(1); // (Dz1MetaTagDB_delAndSetNull, (void *)&dec);
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}
// Dz1MetaTagDB CODEC Test
////////////////////////////////////////////////////////////////////////////////

