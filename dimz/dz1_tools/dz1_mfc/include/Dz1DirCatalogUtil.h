#ifndef DZ1_DIR_CATALOG_UTIL_H
#define DZ1_DIR_CATALOG_UTIL_H

#include <Dz1MfcDef.h>

DZ1_CPPLINK Dz1DirCatalogA						*Dz1DirCatalogACache_getDirCatalog(Dz1DirCatalogACache *p, str_t path, bool_t refresh, Dz1Error *err);
DZ1_CPPLINK Dz1DirCatalogW						*Dz1DirCatalogWCache_getDirCatalog(Dz1DirCatalogWCache *p, wstr_t path, bool_t refresh, Dz1Error *err);

#ifdef UNICODE
#define Dz1DirCatalogCache						Dz1DirCatalogWCache
#define Dz1DirCatalogCache_new					Dz1DirCatalogWCache_new
#define Dz1DirCatalogCache_del					Dz1DirCatalogWCache_del
#define Dz1DirCatalogCache_delAndSetNull		Dz1DirCatalogWCache_delAndSetNull
#define Dz1DirCatalogCache_getDirCatalog		Dz1DirCatalogWCache_getDirCatalog
#else
#define Dz1DirCatalogCache						Dz1DirCatalogACache
#define Dz1DirCatalogCache_new					Dz1DirCatalogACache_new
#define Dz1DirCatalogCache_del					Dz1DirCatalogACache_del
#define Dz1DirCatalogCache_delAndSetNull		Dz1DirCatalogACache_delAndSetNull
#define Dz1DirCatalogCache_getDirCatalog		Dz1DirCatalogACache_getDirCatalog
#endif

#endif