#ifndef DZ1_SYSLOG_H
#define DZ1_SYSLOG_H

#include <dz1_error.h>
#include <dz1_str.h>
#include <dz1_bin.h>

DZ1_CPPLINK Dz1Error	 Dz1SysLog_init(Dz1Str _path, Dz1Str _basename, size_t _segSize);
DZ1_CPPLINK void		 Dz1SysLog_clean(void);
static __inline__ void  _Dz1SysLog_cleanup(void *ptr) { Dz1SysLog_clean(); }

DZ1_CPPLINK Dz1Binary	*Dz1Syslog_get(Dz1Error *err);

DZ1_CPPLINK Dz1Error	 Dz1SysLog_write(u8_t *data, size_t size);
DZ1_CPPLINK void		 Dz1SysLog_hook(void *ptr, u8_t *data, size_t size);

DZ1_CPPLINK void		 Dz1SysLog_memExport(bool_t exportData);
static __inline__ void	 Dz1SysLog_memExportWithData(void *ptr) { Dz1SysLog_memExport(TRUE); }
static __inline__ void	 Dz1SysLog_memExportWithoutData(void *ptr) { Dz1SysLog_memExport(FALSE); }




typedef void Dz1SyslogF;
DZ1_CPPLINK Dz1SyslogF	*Dz1SyslogF_new(Dz1Str path, Dz1Str basename, size_t seg_size, Dz1Error *err);
DZ1_CPPLINK void		 Dz1SyslogF_del(Dz1SyslogF *p);
static __inline__ void	 Dz1SyslogF_delAndSetNull(void *pptr)
{
	Dz1SyslogF **p = (Dz1SyslogF **)pptr;
	Dz1SyslogF_del(*p); *p = NULL;
}
DZ1_CPPLINK bool_t		 Dz1SyslogF_write(Dz1SyslogF *p, u8_t *data, size_t size, Dz1Error *err);
DZ1_CPPLINK void		 Dz1SysLogF_hook(void *ptr, u8_t *data, size_t size);

DZ1_CPPLINK void		 Dz1SysLogF_memExport(Dz1SyslogF *p, bool_t exportData);
static __inline__ void	 Dz1SysLogF_memExportWithData(void *ptr) { Dz1SysLogF_memExport((Dz1SyslogF *)ptr, TRUE); }
static __inline__ void	 Dz1SysLogF_memExportWithoutData(void *ptr) { Dz1SysLogF_memExport((Dz1SyslogF *)ptr, FALSE); }


DZ1_CPPLINK Dz1Error	 Dz1SysLogFS_init(Dz1Str _path, Dz1Str _basename, size_t _segSize);
DZ1_CPPLINK void		 Dz1SysLogFS_clean(void);
static __inline__ void  _Dz1SysLogFS_cleanup(void *ptr) { Dz1SysLogFS_clean(); }

DZ1_CPPLINK Dz1Error	 Dz1SysLogFS_write(u8_t *data, size_t size);
DZ1_CPPLINK void		 Dz1SysLogFS_hook(void *ptr, u8_t *data, size_t size);

DZ1_CPPLINK void		 Dz1SysLogFS_memExport(bool_t exportData);
static __inline__ void	 Dz1SysLogFS_memExportWithData(void *ptr) { Dz1SysLogFS_memExport(TRUE); }
static __inline__ void	 Dz1SysLogFS_memExportWithoutData(void *ptr) { Dz1SysLogFS_memExport(FALSE); }
#endif

