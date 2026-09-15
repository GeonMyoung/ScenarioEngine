#include <dz1_meta_tag_util.h>

#include "dz1_vfs_test_tags.h"

Dz1MetaTagDB *Dz1VfsTestTags_new(Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1MetaTagDB *ret = Dz1MetaTagDB_new(errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		Dz1MetaTagDescrEntry *descr = NULL;
		pthread_cleanup_push(Dz1MetaTagDB_delAndSetNull, (void *)&ret);
		if (0) { }

		else if ((descr = Dz1MetaTagDB_addTagDescrAnsi(ret, 1, "Tag#1", "EUC-KR", Dz1MetaTagValueStoragePresent_simple, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1MetaTagDescrEntry_setDescrString(descr, "EUC-KR")).code) ERR_OUT(errp);

		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1MetaTagDB_delAndSetNull, (void *)&ret);
	}
	return ret;
}