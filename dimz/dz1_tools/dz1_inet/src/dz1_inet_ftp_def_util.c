#include "dz1_inet_ftp_def_util.h"

static Dz1Error _Dz1InetFtpTransferList_validate(void *ptr, Dz1InetFtpTransfer *p)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (p->direction == Dz1InetFtpDirection_upload)
	{
		Dz1InetFtpFileInfo *local = p->local;
		switch(local->present)
		{
		case Dz1InetFtpFileInfoPresent_file:
			{
				Dz1InetFtpFileName *file = local->x.file;
				if (file == NULL) ERR_SET_OUT(&err, EINVAL);
				else
				{
					char fn[4096];
					FILE *fp = NULL;
					if (file->path == NULL) strcpy(fn, file->name);
					else sprintf(fn, "%s" DIR_SEPRATOR "%s", file->path, file->name);

					if ((fp = fopen(fn, "rb")) == NULL) ERR_SET_OUT(&err, errno);
					else fclose(fp);
				}
			}
			break;
		case Dz1InetFtpFileInfoPresent_buffer:
			{
				Dz1Binary *bin = local->x.buffer;
				if (bin == NULL) ERR_SET_OUT(&err, EINVAL);
				else if (bin->data == NULL && bin->size != 0) ERR_SET_OUT(&err, EINVAL);
			}
			break;
		default:
			ERR_SET_OUT(&err, EINVAL);
			break;
		}
	}
	return err;
}

Dz1Error Dz1InetFtpTransferList_validate(Dz1InetFtpTransferList *files)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if ((err = files->travel(files, _Dz1InetFtpTransferList_validate, NULL)).code) ERR_OUT(&err);

	return err;
}

