#include "Dz1DirCatalogUtil.h"

Dz1DirCatalogA *Dz1DirCatalogACache_getDirCatalog(Dz1DirCatalogACache *p, str_t path, bool_t refresh, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1DirCatalogA *ret = NULL;
	Dz1DirCatalogA key = { path  }, *cat = p->find(p, &key);
	if (cat == NULL)
	{
		if ((cat = Dz1DirCatalogA_newSubDir(path, errp)) == NULL) { }
		else
		{
			pthread_cleanup_push(Dz1DirCatalogA_delAndSetNull, (void *)&cat);
			if ((*errp = p->add(p, cat)).code) ERR_OUT(errp);
			else
			{
				ret = cat;
				cat = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1DirCatalog_delAndSetNull, (void *)&cat);
		}
	}
	else
	{
		Dz1ThreadA_printf("DirCatalog() : Cache Hit = "); Dz1StrA_dump(path, 0);
		if (refresh)
		{
			Dz1ThreadA_printf("DirCatalog() : Force Update\n");
			Dz1DirCatalogA_updateSubDir(cat);
		}
		else
		{
			time_t dir_stamp = Dz1DirA_time(path, NULL);
			if (dir_stamp != -1 && dir_stamp != cat->path_stamp)
			{
				Dz1ThreadA_printf("DirCatalog() : different time -> Update\n");
				Dz1DirCatalogA_updateSubDir(cat);
			}
		}
		ret = cat;
	}		
	return ret;
}

Dz1DirCatalogW *Dz1DirCatalogWCache_getDirCatalog(Dz1DirCatalogWCache *p, wstr_t path, bool_t refresh, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	Dz1DirCatalogW *ret = NULL;
	Dz1DirCatalogW key = { path  }, *cat = p->find(p, &key);
	if (cat == NULL)
	{
		if ((cat = Dz1DirCatalogW_newSubDir(path, errp)) == NULL) { }
		else
		{
			pthread_cleanup_push(Dz1DirCatalogW_delAndSetNull, (void *)&cat);
			if ((*errp = p->add(p, cat)).code) ERR_OUT(errp);
			else
			{
				ret = cat;
				cat = NULL;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(1); // (Dz1DirCatalog_delAndSetNull, (void *)&cat);
		}
	}
	else
	{
		Dz1ThreadW_printf(L"DirCatalog() : Cache Hit = "); Dz1StrW_dump(path, 0);
		if (refresh)
		{
			Dz1ThreadW_printf(L"DirCatalog() : Force Update\n");
			Dz1DirCatalogW_updateSubDir(cat);
		}
		else
		{
			time_t dir_stamp = 0;
			dir_stamp = Dz1DirW_time(path, NULL);
			if (dir_stamp != -1 && dir_stamp != cat->path_stamp)
			{
				Dz1ThreadW_printf(L"DirCatalog() : different time -> Update\n");
				Dz1DirCatalogW_updateSubDir(cat);
			}
		}
		ret = cat;
	}		
	return ret;
}
