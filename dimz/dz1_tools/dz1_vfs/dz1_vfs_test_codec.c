#include "src/dz1_vfs_codec.h"
#include "dz1_vfs_test_codec.h"

////////////////////////////////////////////////////////////////////////////////
// Dz1VfsFile CODEC Test
Dz1Error Dz1VfsFileCodec_test(Dz1VfsFile *src, bool_t verbose)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Binary *bin = NULL;

	if (verbose)
	{
		Dz1Thread_printf("============================================================\n");
		Dz1Thread_printf("SOURCE ="); Dz1VfsFile_dump(src, 0);
	}

	if ((bin = Dz1VfsFile_toStream(src, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1VfsFile *dec = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if (verbose)
		{
			Dz1Thread_printf("============================================================\n");
			Dz1Thread_printf("STREAM\n");
			Dz1Thread_tprintb(1, bin->data, bin->size, 16);
		}

		if ((dec = Dz1VfsFile_toStruct(bin, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary *chk = NULL;
			pthread_cleanup_push(Dz1VfsFile_delAndSetNull, (void *)&dec);
			if (verbose)
			{
				Dz1Thread_printf("============================================================\n");
				Dz1Thread_printf("DECODED ="); Dz1VfsFile_dump(dec, 0);
			}

			if ((chk = Dz1VfsFile_toStream(dec, NULL, errp)) == NULL) ERR_OUT(errp);
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
			pthread_cleanup_pop(1); // (Dz1VfsFile_delAndSetNull, (void *)&dec);
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}
// Dz1VfsFile CODEC Test
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Dz1VfsDir CODEC Test
Dz1Error Dz1VfsDirCodec_test(Dz1VfsDir *src, bool_t verbose)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Binary *bin = NULL;

	if (verbose)
	{
		Dz1Thread_printf("============================================================\n");
		Dz1Thread_printf("SOURCE ="); Dz1VfsDir_dump(src, 0);
	}

	if ((bin = Dz1VfsDir_toStream(src, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1VfsDir *dec = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if (verbose)
		{
			Dz1Thread_printf("============================================================\n");
			Dz1Thread_printf("STREAM\n");
			Dz1Thread_tprintb(1, bin->data, bin->size, 16);
		}

		if ((dec = Dz1VfsDir_toStruct(bin, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary *chk = NULL;
			pthread_cleanup_push(Dz1VfsDir_delAndSetNull, (void *)&dec);
			if (verbose)
			{
				Dz1Thread_printf("============================================================\n");
				Dz1Thread_printf("DECODED ="); Dz1VfsDir_dump(dec, 0);
			}

			if ((chk = Dz1VfsDir_toStream(dec, NULL, errp)) == NULL) ERR_OUT(errp);
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
			pthread_cleanup_pop(1); // (Dz1VfsDir_delAndSetNull, (void *)&dec);
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}
// Dz1VfsDir CODEC Test
////////////////////////////////////////////////////////////////////////////////

/*
////////////////////////////////////////////////////////////////////////////////
// Dz1Vfs CODEC Test
Dz1Error Dz1VfsCodec_test(Dz1Vfs *src, bool_t verbose)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1Binary *bin = NULL;

	if (verbose)
	{
		Dz1Thread_printf("============================================================\n");
		Dz1Thread_printf("SOURCE ="); Dz1Vfs_dump(src, 0);
	}

	if ((bin = Dz1Vfs_toStream(src, NULL, errp)) == NULL) ERR_OUT(errp);
	else
	{
		Dz1Vfs *dec = NULL;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if (verbose)
		{
			Dz1Thread_printf("============================================================\n");
			Dz1Thread_printf("STREAM\n");
			Dz1Thread_tprintb(1, bin->data, bin->size, 16);
		}

		if ((dec = Dz1Vfs_toStruct(bin, NULL, errp)) == NULL) ERR_OUT(errp);
		else
		{
			Dz1Binary *chk = NULL;
			pthread_cleanup_push(Dz1Vfs_delAndSetNull, (void *)&dec);
			if (verbose)
			{
				Dz1Thread_printf("============================================================\n");
				Dz1Thread_printf("DECODED ="); Dz1Vfs_dump(dec, 0);
			}

			if ((chk = Dz1Vfs_toStream(dec, NULL, errp)) == NULL) ERR_OUT(errp);
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
			pthread_cleanup_pop(1); // (Dz1Vfs_delAndSetNull, (void *)&dec);
		}
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return err;
}
// Dz1Vfs CODEC Test
////////////////////////////////////////////////////////////////////////////////

*/