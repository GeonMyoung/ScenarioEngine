#include <dz1.h>

#ifdef UNIX_SYSTEM

#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <utime.h>

#ifndef	MAC_OS_X
#	include <mntent.h>
#	include <sys/vfs.h>
#endif	// MAX_OS_X

#else	// UNIX_SYSTEM

#include <windows.h>
#include <io.h>
#include <direct.h>
#include <sys/stat.h>

#ifdef __BORLANDC__
#include <utime.h>
#else // __BORLANDC__
#include <sys/utime.h>
#endif // __BORLANDC__
#endif	// UNIX_SYSTEM

#include <dz1_malloc.h>
#include <dz1_str.h>
#include <dz1_stdio.h>
#include <dz1_thread_stdio.h>

#include "dz1_thread.h"

#define ARR_VAR_SIZE(el_type, var_name)		(sizeof(var_name) / sizeof(el_type))
///////////////////////////////////////////////////////////////////////////////
// primitive type dump
///////////////////////////////////////
// u64_t
void u64_t_dumpA(u64_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf(DZ1_FMT64XF_A(016) "(" DZ1_FMT64_A ")\n", *p, *p);
}

void u64_t_fdumpA(FILE *fp, u64_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, DZ1_FMT64XF_A(016) "(" DZ1_FMT64_A ")\n", *p, *p);
}

#ifndef UNIX_SYSTEM
void u64_t_dumpW(u64_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(DZ1_FMT64XF_W(016) L"(" DZ1_FMT64_W L")\n", *p, *p);
}

void u64_t_fdumpW(FILE *fp, u64_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, DZ1_FMT64XF_W(016) L"(" DZ1_FMT64_W L")\n", *p, *p);
}
#endif
// u64_t
///////////////////////////////////////

///////////////////////////////////////
// u32_t
void u32_t_dumpA(u32_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%08X(%u)\n", *p, *p);
}

void u32_t_fdumpA(FILE *fp, u32_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%08X(%u)\n", *p, *p);
}
#ifndef UNIX_SYSTEM
void u32_t_dumpW(u32_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%08X(%u)\n", *p, *p);
}

void u32_t_fdumpW(FILE *fp, u32_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%08X(%u)\n", *p, *p);
}
#endif
// u32_t
///////////////////////////////////////

///////////////////////////////////////
// u16_t
void u16_t_dumpA(u16_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%04X(%u)\n", *p, *p);
}

void u16_t_fdumpA(FILE *fp, u16_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%04X(%u)\n", *p, *p);
}
#ifndef UNIX_SYSTEM
void u16_t_dumpW(u16_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%04X(%u)\n", *p, *p);
}

void u16_t_fdumpW(FILE *fp, u16_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%04X(%u)\n", *p, *p);
}
#endif
// u16_t
///////////////////////////////////////

///////////////////////////////////////
// u8_t
void u8_t_dumpA(u8_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%02X(%u)\n", *p, *p);
}
void u8_t_fdumpA(FILE *fp, u8_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%02X(%u)\n", *p, *p);
}
#ifndef UNIX_SYSTEM
void u8_t_dumpW(u8_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%02X(%u)\n", *p, *p);
}
void u8_t_fdumpW(FILE *fp, u8_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%02X(%u)\n", *p, *p);
}
#endif
// u8_t
///////////////////////////////////////

///////////////////////////////////////
// s64_t
void s64_t_dumpA(s64_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf(DZ1_FMT64XF_A(016) "(" DZ1_FMT64_A ")\n", *p, *p);
}

void s64_t_fdumpA(FILE *fp, s64_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, DZ1_FMT64XF_A(016) "(" DZ1_FMT64_A ")\n", *p, *p);
}
#ifndef UNIX_SYSTEM
void s64_t_dumpW(s64_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(DZ1_FMT64XF_W(016) L"(" DZ1_FMT64_W L")\n", *p, *p);
}

void s64_t_fdumpW(FILE *fp, s64_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, DZ1_FMT64XF_W(016) L"(" DZ1_FMT64_W L")\n", *p, *p);
}
#endif
// s64_t
///////////////////////////////////////

///////////////////////////////////////
// s32_t
void s32_t_dumpA(s32_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%08X(%d)\n", *p, *p);
}

void s32_t_fdumpA(FILE *fp, s32_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%08X(%d)\n", *p, *p);
}
#ifndef UNIX_SYSTEM
void s32_t_dumpW(s32_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%08X(%d)\n", *p, *p);
}

void s32_t_fdumpW(FILE *fp, s32_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%08X(%d)\n", *p, *p);
}
#endif
// s32_t
///////////////////////////////////////

///////////////////////////////////////
// s16_t
void s16_t_dumpA(s16_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%04X(%d)\n", *p, *p);
}

void s16_t_fdumpA(FILE *fp, s16_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%04X(%d)\n", *p, *p);
}
#ifndef UNIX_SYSTEM
void s16_t_dumpW(s16_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%04X(%d)\n", *p, *p);
}

void s16_t_fdumpW(FILE *fp, s16_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%04X(%d)\n", *p, *p);
}
#endif
// s16_t
///////////////////////////////////////

///////////////////////////////////////
// s8_t
void s8_t_dumpA(s8_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else Dz1ThreadA_printf("%02X(%d)\n", *p, *p);
}

void s8_t_fdumpA(FILE *fp, s8_t *p, int tab)
{
	if (p == NULL) Dz1ThreadA_fprintf(fp, "NULL\n");
	else Dz1ThreadA_fprintf(fp, "%02X(%d)\n", *p, *p);
}
#ifndef UNIX_SYSTEM
void s8_t_dumpW(s8_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else Dz1ThreadW_printf(L"%02X(%d)\n", *p, *p);
}

void s8_t_fdumpW(FILE *fp, s8_t *p, int tab)
{
	if (p == NULL) Dz1ThreadW_fprintf(fp, L"NULL\n");
	else Dz1ThreadW_fprintf(fp, L"%02X(%d)\n", *p, *p);
}
#endif
// s8_t
///////////////////////////////////////
// primitive type dump
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO ENDIAN Convert Helper Function
static u16_t byteSwap16(u16_t src)
{
	u8_t *cp = (u8_t *)&src, temp = cp[0]; cp[0] = cp[1]; cp[1] = temp;
	return src;
}

static u32_t byteSwap32(u32_t src)
{
	u8_t *cp = (u8_t *)&src, temp;
	temp = cp[0]; cp[0] = cp[3]; cp[3] = temp;
	temp = cp[1]; cp[1] = cp[2]; cp[2] = temp;

	return src;
}

static u64_t byteSwap64(u64_t src)
{
	u8_t *cp = (u8_t *)&src, temp;
	temp = cp[0]; cp[0] = cp[7]; cp[7] = temp;
	temp = cp[1]; cp[1] = cp[6]; cp[6] = temp;
	temp = cp[2]; cp[2] = cp[5]; cp[5] = temp;
	temp = cp[3]; cp[3] = cp[4]; cp[4] = temp;

	return src;
}

//////////////////////////////////////////
// Host to Little Endian
u16_t Dz1Endian2_host2little(u16_t v)	// 2 Byte
{
#if DZ1_ENDIAN == DZ1_ENDIAN_BIG
	v = byteSwap16(v);
#endif
	return v;
}

u32_t Dz1Endian4_host2little(u32_t v)	// 4 Byte
{
#if DZ1_ENDIAN == DZ1_ENDIAN_BIG
	v = byteSwap32(v);
#endif
	return v;
}

u64_t Dz1Endian8_host2little(u64_t v)	// 8 Byte
{
#if DZ1_ENDIAN == DZ1_ENDIAN_BIG
	v = byteSwap64(v);
#endif
	return v;
}
// Host to Little Endian
//////////////////////////////////////////

//////////////////////////////////////////
// Little Endian to Host
u16_t Dz1Endian2_little2host(u16_t v)	// 2 Byte
{
#if DZ1_ENDIAN == DZ1_ENDIAN_BIG
	v = byteSwap16(v);
#endif
	return v;
}

u32_t Dz1Endian4_little2host(u32_t v)	// 4 Byte
{
#if DZ1_ENDIAN == DZ1_ENDIAN_BIG
	v = byteSwap32(v);
#endif
	return v;
}

u64_t Dz1Endian8_little2host(u64_t v)	// 8 Byte
{
#if DZ1_ENDIAN == DZ1_ENDIAN_BIG
	v = byteSwap64(v);
#endif
	return v;
}
// Little Endian to Host
//////////////////////////////////////////

//////////////////////////////////////////
// Host to Big Endian
u16_t Dz1Endian2_host2big(u16_t v)		// 2Byte
{
#if DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
	v = byteSwap16(v);
#endif
	return v;
}

u32_t Dz1Endian4_host2big(u32_t v)		// 4 Byte
{
#if DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
	v = byteSwap32(v);
#endif
	return v;
}

u64_t Dz1Endian8_host2big(u64_t v)		// 8 Byte
{
#if DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
	v = byteSwap64(v);
#endif
	return v;
}
// Host to Big Endian
//////////////////////////////////////////

//////////////////////////////////////////
// Big Endian to Host
u16_t Dz1Endian2_big2host(u16_t v)		// 2 Byte
{
#if DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
	v = byteSwap16(v);
#endif
	return v;
}

u32_t Dz1Endian4_big2host(u32_t v)		// 4 Byte
{
#if DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
	v = byteSwap32(v);
#endif
	return v;
}

u64_t Dz1Endian8_big2host(u64_t v)		// 8 Byte
{
#if DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
	v = byteSwap64(v);
#endif
	return v;
}
// Big Endian to Host
//////////////////////////////////////////

// STDIO ENDIAN Convert Helper Function
///////////////////////////////////////////////////////////////////////////////

size_t Dz1Kernel_getPhyFreeMem(void)
{
	size_t ret = 0;
#ifdef WIN32
	MEMORYSTATUS info;
	GlobalMemoryStatus(&info);
	ret = info.dwAvailPhys;
#endif // WIN32
	return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Partition Info
static str_t sizeUnitsA[] =
{
	(str_t)"B",
	(str_t)"KB",
	(str_t)"MB",
	(str_t)"GB",
	(str_t)"TB"
};
static int sizeUnitsMaxA = sizeof(sizeUnitsA) / sizeof(str_t);

static str_t _getSizeUnitStrA(u64_t *_v)
{
	int i;
	u64_t v = *_v;
	for (i = 0; i < sizeUnitsMaxA; i++)
	{
		if (v > (100 * 1024)) v /= 1024;
		else break;
	}
	*_v = v;
	return sizeUnitsA[i];
}

void Dz1KernelPartitionEntryA_dump(Dz1KernelPartitionEntry *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else
	{
		u64_t freeV = p->freeByte;
		u64_t totalV = p->totalByte;
		str_t strFree = _getSizeUnitStrA(&freeV);
		str_t strTotal = _getSizeUnitStrA(&totalV);
 		Dz1ThreadA_printf("%s(" DZ1_FMT64_A " / " DZ1_FMT64_A ")\n",p->name, freeV, strFree, totalV, strTotal);
	}
}

void Dz1KernelPartitionInfoA_dump(Dz1KernelPartitionInfo *p, int tab)
{
	if (p == NULL) Dz1ThreadA_printf("NULL\n");
	else if (p->numOfEntries == 0) Dz1ThreadA_printf("Empty\n");
	else
	{
		size_t i;
		Dz1ThreadA_printf("{\n"); tab++;
		for (i = 0; i < p->numOfEntries; i++)
		{
			Dz1ThreadA_tprintf(tab, "Partition = ");
			Dz1KernelPartitionEntryA_dump(&p->entries[i], tab);
		}
	}
}
#ifndef UNIX_SYSTEM
static wstr_t sizeUnitsW[] =
{
	(wstr_t)L"B",
	(wstr_t)L"KB",
	(wstr_t)L"MB",
	(wstr_t)L"GB",
	(wstr_t)L"TB"
};
static int sizeUnitsMaxW = sizeof(sizeUnitsW) / sizeof(wstr_t);

static wstr_t _getSizeUnitStrW(u64_t *_v)
{
	int i;
	u64_t v = *_v;
	for (i = 0; i < sizeUnitsMaxW; i++)
	{
		if (v > (100 * 1024)) v /= 1024;
		else break;
	}
	*_v = v;
	return sizeUnitsW[i];
}

void Dz1KernelPartitionEntryW_dump(Dz1KernelPartitionEntry *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		u64_t freeV = p->freeByte;
		u64_t totalV = p->totalByte;
		wstr_t strFree = _getSizeUnitStrW(&freeV);
		wstr_t strTotal = _getSizeUnitStrW(&totalV);
 		Dz1ThreadW_printf(L"%s(" DZ1_FMT64_W L" / " DZ1_FMT64_W L")\n",p->name, freeV, strFree, totalV, strTotal);
	}
}

void Dz1KernelPartitionInfoW_dump(Dz1KernelPartitionInfo *p, int tab)
{
	if (p == NULL) Dz1ThreadW_printf(L"NULL\n");
	else if (p->numOfEntries == 0) Dz1ThreadW_printf(L"Empty\n");
	else
	{
		size_t i;
		Dz1ThreadW_printf(L"{\n"); tab++;
		for (i = 0; i < p->numOfEntries; i++)
		{
			Dz1ThreadW_tprintf(tab, L"Partition = ");
			Dz1KernelPartitionEntryW_dump(&p->entries[i], tab);
		}
	}
}
#endif

#if		defined(UNIX_SYSTEM)
#if		!defined(MAC_OS_X)
static void setnmtent_cancel(void *ptr)
{
	FILE *s_mount_entry = (FILE *)ptr;
	endmntent(s_mount_entry);
}

static ssize_t _getPartitionCount(Dz1Error *errp)
{
	ssize_t ret = 0;
	FILE *s_mount_table;
	if ((s_mount_table = setmntent("/proc/mounts", MNTOPT_RO)) == NULL) ERR_SET_OUT(errp, errno);
	else
	{
		struct mntent *s_mount_entry = NULL;
		struct statfs s_status_fs;
		pthread_cleanup_push(setnmtent_cancel, (void *)s_mount_table);
		do
		{
			if ((s_mount_entry = getmntent(s_mount_table)) == NULL) break;
			else if (s_mount_entry->mnt_dir == NULL || s_mount_entry->mnt_fsname == NULL) continue;
			else if (statfs((str_t)s_mount_entry->mnt_dir, &s_status_fs) != 0) continue;
			else if (s_status_fs.f_blocks < 0) continue;
			else ret++;
		} while (1);
		pthread_cleanup_pop(1); // (setnmtent_cancel, (void *)s_mount_table);
	}
	return ret;
}

static Dz1Error _fillPartitionInfo(Dz1KernelPartitionEntry *dst)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	FILE *s_mount_table = NULL;
	if ((s_mount_table = setmntent("/proc/mounts", MNTOPT_RO)) == NULL) ERR_SET_OUT(&err, errno);
	else
	{
		struct mntent *s_mount_entry = NULL;
		struct statfs s_status_fs;
		pthread_cleanup_push(setnmtent_cancel, (void *)s_mount_table);
		do
		{
			if ((s_mount_entry = getmntent(s_mount_table)) == NULL) break;
			else if (s_mount_entry->mnt_dir == NULL || s_mount_entry->mnt_fsname == NULL) continue;
			else if (statfs((str_t)s_mount_entry->mnt_dir, &s_status_fs) != 0) continue;
			else if (s_status_fs.f_blocks < 0) continue;
			else if ((dst->name = Dz1StrA_dup((str_t)s_mount_entry->mnt_dir, &err)) == NULL) ERR_OUT(&err);
			else
			{
				dst->totalByte = (u64_t)s_status_fs.f_blocks * (u64_t)s_status_fs.f_bsize;
				dst->freeByte = (u64_t)s_status_fs.f_bavail * (u64_t)s_status_fs.f_bsize;
				dst++;
			}
		} while (1);
		pthread_cleanup_pop(1); // (setnmtent_cancel, (void *)s_mount_table);
	}
	return err;
}

#else	// !defined(MAC_OS_X)
static ssize_t _getPartitionCount(Dz1Error *errp)
{
	ERR_SET_OUT(errp, ENOSYS);
	return -1;
}

static Dz1Error _fillPartitionInfo(Dz1KernelPartitionEntry *dst)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ERR_SET_OUT(&err, ENOSYS);
	return err;
}
#endif	// MAC_OS_X

#else	// defined(UNIX_SYSTEM)

#ifdef	__BORLANDC__
static ssize_t _getPartitionCount(Dz1Error *errp)
{
	ERR_SET_OUT(errp, ENOSYS);
	return -1;
}

static Dz1Error _fillPartitionInfo(Dz1KernelPartitionEntry *dst)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	ERR_SET_OUT(&err, ENOSYS);
	return err;
}
#else	// __BORLANDC__
static ssize_t _getPartitionCount(Dz1Error *errp)
{
	ssize_t ret = 0;

	u32_t i;
	struct _diskfree_t info;
	for (i = 1 ; i <= 26; i++)
		if (_getdiskfree(i, &info) == 0) ret++;
	return ret;
}

static Dz1Error _fillPartitionInfo(Dz1KernelPartitionEntry *dst)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	u32_t i; struct _diskfree_t info;
	for (i = 1 ; i <= 26; i++)
	{
		if (_getdiskfree(i, &info) == 0)
		{
			char temp[3] = { 0, };
			temp[0] = (i == 1 || i == 2) ? 'A' + (i - 1) : 'C' + (i - 3);
			temp[1] = ':';
			if ((dst->name = Dz1StrA_dup(temp, &err)) == NULL) ERR_OUT(&err);
			else
			{
				u64_t cluster_per_byte = (u64_t)info.sectors_per_cluster * (u64_t)info.bytes_per_sector;
				dst->totalByte = (u64_t)info.total_clusters * cluster_per_byte;
				dst->freeByte = (u64_t)info.avail_clusters * cluster_per_byte;
				dst++;
			}
		}
	}
	return err;
}
#endif // __BORLANDC__
#endif //defined(UNIX_SYSTEM)

Dz1KernelPartitionInfo *Dz1Kernel_getPartitionInfo(Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1KernelPartitionInfo *ret = (Dz1KernelPartitionInfo *)Dz1Calloc(sizeof(Dz1KernelPartitionInfo), 1, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		ssize_t cnt = 0;
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ret);
		if ((cnt = _getPartitionCount(errp)) < 0) ERR_OUT(errp);
		else if ((ret->entries = (Dz1KernelPartitionEntry *)Dz1Calloc(sizeof(Dz1KernelPartitionEntry), (ret->numOfEntries = cnt), errp)) == NULL) ERR_OUT(errp);
		else
		{
			pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&ret->entries);
			if ((*errp = _fillPartitionInfo(ret->entries)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);
			pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret->entries);
		}
		pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)&ret);
	}
	return ret;
}

void Dz1Kernel_putPartitionInfo(Dz1KernelPartitionInfo *p)
{
	if (p == NULL) return;
	if (p->entries) { Dz1Free(p->entries); p->entries = NULL; } // modified by gm 20230601
	Dz1Free(p);
}
// Partition Info
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO Print Functions
static ssize_t tabPrintA(FILE *fp, int tab)
{
	ssize_t ret = 0;
	while(tab--) ret += fprintf(fp, DZ1_TAB_STR_A);
	return ret;
}

ssize_t Dz1A_vftprintf(FILE *fp, int tab, const str_t fmt, va_list ap)
{
	ssize_t ret = -1;
	if (fp && fmt && strlen(fmt))
	{
		ret = tabPrintA(fp, tab);
		ret += vfprintf(fp, fmt, ap);
	}
	return ret;
}
ssize_t Dz1A_vfprintf(FILE *fp, const str_t fmt, va_list ap) { return Dz1A_vftprintf(fp, 0, fmt, ap); }

ssize_t Dz1A_ftprintf(FILE *fp, int tab, const str_t fmt, ...)
{
	ssize_t ret;
	va_list ap;
	va_start(ap, fmt);
	ret = Dz1A_vftprintf(fp, tab, fmt, ap);
	va_end(ap);
	return ret;
}

static ssize_t _Dz1A_fprintb(FILE *fp, int tab, u32_t offset, u8_t *data, size_t size, size_t align)
{
	char *lp = (char *)data;
	u8_t *cp = data;
	size_t temp;

	ssize_t ret = tabPrintA(fp, tab);

	ret += fprintf(fp, "%08X : ", offset);

	temp = size; while(temp--) { ret += fprintf(fp, "%02X ", *cp++); align--; }
	fflush(fp);

	if (align) while(align--) ret += fprintf(fp, "   ");

	ret += fprintf(fp, ": ");

	temp = size; while(temp--) { ret += fprintf(fp, "%c", (*lp > 0x20 ? *lp : '.')); lp++; }

	ret += fprintf(fp, "\n");
	fflush(fp);

	return ret;

}

ssize_t Dz1A_ftprintb(FILE *fp, int tab, void *data, size_t size, size_t align)
{
	ssize_t ret = -1;
	if (fp && data && size && align)
	{
		u8_t *cp = (u8_t *)data, *base = (u8_t *)data;

		ssize_t jobSize;

		while(size)
		{
			jobSize = (ssize_t)(size > align ? align : size);
			ret += _Dz1A_fprintb(fp, tab, (u32_t)(cp - base), cp, jobSize, align);
			cp += jobSize; size -= jobSize;
		}
	}
	return ret;
}

ssize_t Dz1A_fprintb(FILE *fp, void *data, size_t size, size_t align)
{
	ssize_t ret = -1;
	if (fp && data && size && align)
	{
		u8_t *cp = (u8_t *)data, *base = (u8_t *)data;

		ssize_t jobSize;

		while(size)
		{
			jobSize = (ssize_t)(size > align ? align : size);
			ret += _Dz1A_fprintb(fp, 0, (u32_t)(cp - base), cp, jobSize, align);
			cp += jobSize; size -= jobSize;
		}
	}
	return ret;
}



#ifndef UNIX_SYSTEM
static ssize_t tabPrintW(FILE *fp, int tab)
{
	ssize_t ret = 0;
	while(tab--) ret += fwprintf(fp, DZ1_TAB_STR_W);
	return ret;
}

ssize_t Dz1W_vftprintf(FILE *fp, int tab, const wstr_t fmt, va_list ap)
{
	ssize_t ret = -1;
	if (fp && fmt && wcslen(fmt))
	{
		ret = tabPrintW(fp, tab);
		ret += vfwprintf(fp, fmt, ap);
	}
	return ret;
}

ssize_t Dz1W_vfprintf(FILE *fp, const wstr_t fmt, va_list ap) { return Dz1W_vftprintf(fp, 0, fmt, ap); }

ssize_t Dz1W_ftprintf(FILE *fp, int tab, const wstr_t fmt, ...)
{
	ssize_t ret;
	va_list ap;
	va_start(ap, fmt);
	ret = Dz1W_vftprintf(fp, tab, fmt, ap);
	va_end(ap);
	return ret;
}

static ssize_t _Dz1W_fprintb(FILE *fp, int tab, u32_t offset, u8_t *data, size_t size, size_t align)
{
	char *lp = (char *)data;
	u8_t *cp = data;
	size_t temp;

	ssize_t ret = tabPrintW(fp, tab);

	ret += fwprintf(fp, L"%08X : ", offset);

	temp = size; while(temp--) { ret += fwprintf(fp, L"%02X ", *cp++); align--; }
	fflush(fp);

	if (align) while(align--) ret += fwprintf(fp, L"   ");

	ret += fwprintf(fp, L": ");

	temp = size; while(temp--) { ret += fwprintf(fp, L"%c", (wchar_t)(*lp > 0x20 ? *lp : '.')); lp++; }

	ret += fwprintf(fp, L"\n");
	fflush(fp);

	return ret;

}

ssize_t Dz1W_ftprintb(FILE *fp, int tab, void *data, size_t size, size_t align)
{
	ssize_t ret = -1;
	if (fp && data && size && align)
	{
		u8_t *cp = (u8_t *)data, *base = (u8_t *)data;

		ssize_t jobSize;

		while(size)
		{
			jobSize = (ssize_t)(size > align ? align : size);
			ret += _Dz1W_fprintb(fp, tab, (u32_t)(cp - base), cp, jobSize, align);
			cp += jobSize; size -= jobSize;
		}
	}
	return ret;
}

ssize_t Dz1W_fprintb(FILE *fp, void *data, size_t size, size_t align)
{
	ssize_t ret = -1;
	if (fp && data && size && align)
	{
		u8_t *cp = (u8_t *)data, *base = (u8_t *)data;

		ssize_t jobSize;

		while(size)
		{
			jobSize = (ssize_t)(size > align ? align : size);
			ret += _Dz1W_fprintb(fp, 0, (u32_t)(cp - base), cp, jobSize, align);
			cp += jobSize; size -= jobSize;
		}
	}
	return ret;
}
#endif
// STDIO Print Functions
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// STDIO File CODEC Basic READ/WRITE functions
ssize_t _read1Byte(FILE *fp, u8_t *c, Dz1Error *errp)
{
	if (fread(c, sizeof(char), 1, fp) != 1)
	{
		int status;
		if ((status = ferror(fp))) ERR_SET_OUT(errp, status);
		else if (feof(fp))
		{
			ERR_SET_OUT(errp, EOF);
		}
		else ERR_SET_OUT(errp, EFAULT);
		return -1;
	}
	else Dz1Error_set(errp, 0);
	return 1;
}

ssize_t _readByte(FILE *fp, u8_t *buf, size_t readSize, Dz1Error *errp)
{
	if (fread(buf, sizeof(char), readSize, fp) != readSize)
	{
		int status;
		if ((status = ferror(fp))) Dz1Error_set(errp, status);
		else if (feof(fp)) Dz1Error_set(errp, EPIPE);
		else Dz1Error_set(errp, EFAULT);
		return -1;
	}
	else Dz1Error_set(errp, 0);

	return (ssize_t)readSize;
}

// ssize_t __read2Byte(FILE *fp, u8_t c[2], Dz1Error *errp)
// {
// 	if (fread(c, sizeof(char), 2, fp) != 2)
// 	{
// 		int status;
// 		if ((status = ferror(fp))) ERR_SET_OUT(errp, status);
// 		else if (feof(fp)) ERR_SET_OUT(errp, EOF);
// 		else ERR_SET_OUT(errp, EFAULT);
// 		return -1;
// 	}
// 	else { Dz1Error_set(errp, 0); return 2; }
// }

ssize_t _read2Byte(FILE *fp, u16_t *c, Dz1Error *errp)
{
	u8_t temp[2];
//	if (__read2Byte(fp, temp, errp) < 0) { ERR_OUT(errp); return -1; }
	if (_readByte(fp, temp, 2, errp) < 0) { ERR_OUT(errp); return -1; }
	else
	{
		*c = ((u16_t)(temp[0]) << 8) | ((u16_t)temp[1]);
		Dz1Error_set(errp, 0);
	}
	return 2;
}

ssize_t _read4Byte(FILE *fp, u32_t *c, Dz1Error *errp)
{
	char temp[4];
// 	if (fread(temp, sizeof(char), 4, fp) != 4)
// 	{
// 		int status;
// 		if ((status = ferror(fp))) Dz1Error_set(errp, status);
// 		else if (feof(fp)) Dz1Error_set(errp, EOF);
// 		else Dz1Error_set(errp, EFAULT);
// 		return -1;
// 	}
	if (_readByte(fp, temp, 4, errp) < 0) { ERR_OUT(errp); return -1; }
	else
	{
		*c =	(((u32_t)temp[0] & 0xFF) << 24) | 
				(((u32_t)temp[1] & 0xFF) << 16) | 
				(((u32_t)temp[2] & 0xFF) << 8) | 
				(((u32_t)temp[3] & 0xFF) << 0);
		Dz1Error_set(errp, 0);
	}

	return 4;
}

ssize_t _write1Byte(FILE *fp, u8_t c, Dz1Error *errp)
{
	if (fwrite(&c, sizeof(char), 1, fp) != 1)
	{
		int status;
		if ((status = ferror(fp))) ERR_SET_OUT(errp, status);
		else if (feof(fp)) ERR_SET_OUT(errp, EOF);
		else ERR_SET_OUT(errp, EFAULT);
		return -1;
	}
	else Dz1Error_set(errp, 0);
	return 1;
}

ssize_t _writeByte(FILE *fp, u8_t *buf, size_t writeSize, Dz1Error *errp)
{
	if (fwrite(buf, sizeof(char), writeSize, fp) != writeSize)
	{
		int status;
		if ((status = ferror(fp))) ERR_SET_OUT(errp, status);
		else if (feof(fp)) ERR_SET_OUT(errp, EOF);
		else ERR_SET_OUT(errp, EFAULT);
		return -1;
	}
	else Dz1Error_set(errp, 0);

	return (ssize_t)writeSize;
}

// ssize_t __write2Byte(FILE *fp, u8_t c[2], Dz1Error *errp)
// {
// 	if (fwrite(c, sizeof(char), 2, fp) != 2)
// 	{
// 		int status;
// 		if ((status = ferror(fp))) ERR_SET_OUT(errp, status);
// 		else if (feof(fp)) ERR_SET_OUT(errp, EOF);
// 		else ERR_SET_OUT(errp, EFAULT);
// 		return -1;
// 	}
// 	else { Dz1Error_set(errp, 0); return 2; }
// }

ssize_t _write2Byte(FILE *fp, u16_t c, Dz1Error *errp)
{
	u8_t temp[2];
	temp[0] = (u8_t)((c & 0xFF00) >> 8);
	temp[1] = (u8_t)(c & 0xFF);

	return _writeByte(fp, temp, 2, errp);
}

ssize_t _write4Byte(FILE *fp, u32_t c, Dz1Error *errp)
{
	char temp[4];
	temp[0] = (u8_t)((c & 0xFF000000) >> 24);
	temp[1] = (u8_t)((c & 0xFF0000) >> 16);
	temp[2] = (u8_t)((c & 0xFF00) >> 8);
	temp[3] = (u8_t)(c & 0xFF);

	return _writeByte(fp, temp, 4, errp);
// 	if (fwrite(temp, sizeof(char), 4, fp) != 4)
// 	{
// 		int status;
// 		if ((status = ferror(fp))) ERR_SET_OUT(errp, status);
// 		else if (feof(fp)) ERR_SET_OUT(errp, EOF);
// 		else ERR_SET_OUT(errp, EFAULT);
// 		return -1;
// 	}
// 	else Dz1Error_set(errp, 0);	
// 	return 4;
}
// STDIO File CODEC Basic READ/WRITE functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO File CODEC Extended READ/WRITE functions
static int _ascii2int(char c)
{
	int ret = 0;
	if (c >= '0' && c <= '9') ret = c - '0';
	return ret;
}

ssize_t _readDigitA(FILE *fp, u32_t *dst, size_t len, Dz1Error *errp)
{
	ssize_t ret = (ssize_t)len;
	char c;
	*dst = 0;
	while(len--)
	{
		if (fread(&c, sizeof(char), 1, fp) != 1)
		{
			int status;
			if ((status = ferror(fp))) ERR_SET_OUT(errp, status);
			else if (feof(fp)) ERR_SET_OUT(errp, EOF);
			else ERR_SET_OUT(errp, EFAULT);
			return -1;
		}
		else if (!isdigit(((int)c & 0xFF)))
		{
			if (c >= 0 && c <= 9) (*dst) = (*dst) * 10 + c;
			else
			{
				ERR_SET_OUT(errp, EINVAL);
				return -1;
			}
		}
		else (*dst) = (*dst) * 10 + _ascii2int(c);
	}
	return ret;
}

ssize_t _read8strA(FILE *fp, str_t *dst, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (!dst) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		u8_t len = 0;
		ssize_t status;
		str_t p = NULL;
		if ((status = _read1Byte(fp, &len, errp)) < 0) { ERR_OUT(errp); return -1; } else ret += status;

		if ((p = (*dst) = (str_t)Dz1Calloc(sizeof(char), (size_t)len + 1, errp)) == NULL) { ERR_OUT(errp); return -1; }
		else
		{
			pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)dst);
			
			if ((status  = _readByte(fp, (u8_t *)p, (size_t)len, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				ret += status;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // ((Dz1Str_delAndSetNull, (void *)dst);
		}
	}
	return ret;
}

ssize_t _read16strA(FILE *fp, str_t *dst, Dz1Error *errp)
{
	ssize_t ret = 0;
	if (!dst) { ERR_SET_OUT(errp, EINVAL); return -1; }
	else
	{
		u16_t len = 0;
		ssize_t status;
		str_t p = NULL;
		if ((status = _read2Byte(fp, &len, errp)) < 0) { ERR_OUT(errp); return -1; } else ret += status;

		if ((p = (*dst) = (str_t)Dz1Calloc(sizeof(char), len + 1, errp)) == NULL) { ERR_OUT(errp); return -1; }
		else
		{
			pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)dst);
			if ((status = _readByte(fp, (u8_t *)p, len, errp)) < 0) { ERR_OUT(errp); ret = -1; }
			else
			{
				ret += status;
				Dz1Error_set(errp, 0);
			}
			pthread_cleanup_pop(errp->code); // (Dz1Memory_freeAndSetNull, (void *)dst);
		}
	}
	return ret;
}

ssize_t _readLineA(FILE *fp, u8_t *dst, size_t size, Dz1Error *errp)
{
	ssize_t ret = 0;
	char c;
	u8_t *dp = dst;
	if (feof(fp)) return 0;
	while(size)
	{
		if (fread(&c, sizeof(char), 1, fp) != 1)
		{
			int status;
			if (feof(fp))
			{
				*dp++ = '\0'; size--;
				return ret;
			}
			else if ((status = ferror(fp)) != 0) ERR_SET_OUT(errp, status);
			else ERR_SET_OUT(errp, EFAULT);
			return -1;
		}
		else
		{
			ret++;
			if (c == '\r') continue;
			else if (c == '\n')
			{
				*dp++ = '\0'; size--;
				return ret;
			}
			else { *dp++ = c; size--; }
		}
	}

	ERR_SET_OUT(errp, E2BIG);
	return -1;
}

ssize_t _writeDigitA(FILE *fp, u32_t src, size_t len, Dz1Error *errp)
{
	ssize_t ret = (ssize_t)len;
	size_t _len;
	char temp[32] = { 0, };

	sprintf(temp, "%u", src);
	if ((_len = strlen(temp)) > len) { ERR_SET_OUT(errp, EINVAL); return -1; } 

	if (_len < len)
	{
		char c = '0';
		size_t pad = len - _len;
		while(pad--)
		{
			if (fwrite(&c, sizeof(char), 1, fp) != 1)
			{
				int status;
				if ((status = ferror(fp))) ERR_SET_OUT(errp, status);
				else if (feof(fp)) ERR_SET_OUT(errp, EOF);
				else ERR_SET_OUT(errp, EFAULT);
				return -1;
			}
		}
	}

	if (fwrite(temp, sizeof(char), _len, fp) != _len)
	{
		int status;
		if ((status = ferror(fp))) ERR_SET_OUT(errp, status);
		else if (feof(fp)) ERR_SET_OUT(errp, EOF);
		else ERR_SET_OUT(errp, EFAULT);
		return -1;
	}
	return ret;
}

ssize_t _write8strA(FILE *fp, str_t src, Dz1Error *errp)
{
	ssize_t ret = -1;
	if (!src)
	{
		if (_write1Byte(fp, 0, errp) < 0) ERR_OUT(errp);
		else ret = 1;
	}
	else
	{
		ssize_t sz;
		u8_t len = (u8_t)strlen(src);
		if (_write1Byte(fp, len, errp) < 0) ERR_OUT(errp);
		else if (len > 0 && (sz = _writeByte(fp, (u8_t *)src, (size_t)len, errp)) < 0) ERR_OUT(errp);
		else
		{
			ret = (ssize_t)(1 + (size_t)len);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

ssize_t _write16strA(FILE *fp, str_t src, Dz1Error *errp)
{
	ssize_t ret = -1, status;
	if (!src)
	{
		if (_write2Byte(fp, 0, errp) < 0) ERR_OUT(errp); else ret = 2;
	}
	else
	{
		u16_t len = (u16_t)strlen(src);
		if (_write2Byte(fp, len, errp) < 0) ERR_OUT(errp);
		else if ((status = _writeByte(fp, (u8_t *)src, (size_t)len, errp)) < 0) ERR_OUT(errp);
		else
		{
			ret = (ssize_t)(2 + (size_t)len);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

ssize_t _writeLineA(FILE *fp, u8_t *src, size_t size, Dz1Error *errp)
{
	ssize_t ret = 0;
	char c;
	u8_t *cp = src;
	while(size--)
	{
		if (fwrite(cp, sizeof(char), 1, fp) != 1)
		{
			int status;
			if (feof(fp)) ERR_SET_OUT(errp, EPIPE);
			else if ((status = ferror(fp)) != 0) ERR_SET_OUT(errp, status);
			else ERR_SET_OUT(errp, EFAULT);
			return -1;
		}
		else ret++;
	}
	c = '\r'; if (_write1Byte(fp, c, errp) < 0) { ERR_OUT(errp); return -1; } else ret++;
	c = '\n'; if (_write1Byte(fp, c, errp) < 0) { ERR_OUT(errp); return -1; } else ret++;

	return ret;
}
#ifndef UNIX_SYSTEM
// DZ1_CPPLINK DZ1_DLLPORT ssize_t  _readDigitW(FILE *fp, u32_t *dst, size_t len, Dz1Error *errp);
// DZ1_CPPLINK DZ1_DLLPORT ssize_t  _read8strW (FILE *fp, wstr_t *dst, Dz1Error *errp);
// DZ1_CPPLINK DZ1_DLLPORT ssize_t  _read16strW(FILE *fp, wstr_t *dst, Dz1Error *errp);
// DZ1_CPPLINK DZ1_DLLPORT ssize_t  _readLineW(FILE *fp, u8_t *dst, size_t size, Dz1Error *errp);
// 
// DZ1_CPPLINK DZ1_DLLPORT ssize_t  _writeDigitW(FILE *fp, u32_t src, size_t len, Dz1Error *errp);
// DZ1_CPPLINK DZ1_DLLPORT ssize_t  _write8strW (FILE *fp, wstr_t src, Dz1Error *errp);
// DZ1_CPPLINK DZ1_DLLPORT ssize_t  _write16strW(FILE *fp, wstr_t src, Dz1Error *errp);
// DZ1_CPPLINK DZ1_DLLPORT ssize_t  _writeLineW(FILE *fp, u8_t *src, size_t size, Dz1Error *errp);
#endif
// STDIO File CODEC Extended READ/WRITE functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Path Checker
static __inline__ bool_t _isNetworkAbsPathA(str_t str, size_t len)
{
	if (len > 2)
	{
		char *cp = str;
		if ( *cp != DIR_SEP_A) return FALSE; else { cp++; len--; }	// '\\' or '/'
		if ( *cp != DIR_SEP_A) return FALSE; else { cp++; len--; }	// '\\' or '/'

		while( *cp != 0 && *cp != DIR_SEP_A) { cp++; len--; }		// server name

		if (*cp == 0) return FALSE;									// 여기서 끝나면 out

		if (*cp != DIR_SEP_A) return FALSE;							// '\\' or '/'
		else { cp++; len--; }

		if (len == 0) return FALSE;									// DIR_SEP다음에 아무 문자도 없으면 out
		else return TRUE;
	}
	else return FALSE;
}

#ifndef UNIX_SYSTEM
static __inline__ bool_t _isNetworkAbsPathW(wstr_t str, size_t len)
{
	if (len > 2)
	{
		wchar_t *cp = str;
		if ( *cp != DIR_SEP_W) return FALSE; else { cp++; len--; }	// '\\'
		if ( *cp != DIR_SEP_W) return FALSE; else { cp++; len--; }	// '\\'

		while( *cp != 0 && *cp != DIR_SEP_W) { cp++; len--; }		// server name

		if (*cp == 0) return FALSE;									// 여기서 끝나면 out

		if (*cp != DIR_SEP_W) return FALSE;							// '\\'
		else { cp++; len--; }

		if (len == 0) return FALSE;									// DIR_SEP다음에 아무 문자도 없으면 out
		else return TRUE;
	}
	else return FALSE;
}

static bool_t _isNetPathNameA(str_t str)
{
	return _isNetworkAbsPathA(str, strlen(str));
// 	bool_t ret = FALSE;
// 	size_t len = strlen(str);
// 	if (len >= 2 && str[0] == DIR_SEP_A && str[1] == DIR_SEP_A)
// 	{
// 		str_t cp = &str[2];
// 		while(*cp != 0 && *cp != DIR_SEP_A) cp++; // pass server_name
// 		if (*cp == DIR_SEP_A)
// 		{
// 			cp++; // pass '\'
// 			if (*cp != 0 && *cp != DIR_SEP_A) ret = TRUE; // any letter then ok else not ok
// 		}
// 	}
// 	return ret;
}
#endif

#ifndef UNIX_SYSTEM
static bool_t _isNetPathNameW(wstr_t str)
{
	return _isNetworkAbsPathW(str, wcslen(str));
// 	bool_t ret = FALSE;
// 	size_t len = wcslen(str);
// 	if (len >= 2 && str[0] == DIR_SEP_W && str[1] == DIR_SEP_W)
// 	{	// 시작을 '\\'로 하는 문자열
// 		wstr_t cp = &str[2];
// 		while(*cp != 0 && *cp != DIR_SEP_W) cp++; // pass server_name
// 		if (*cp == DIR_SEP_W)
// 		{
// 			cp++; // pass '\'
// 			if (*cp != 0 && *cp != DIR_SEP_W) ret = TRUE; // any letter except '\' then ok else not ok
// 		}
// 	}
// 	return ret;
}

static bool_t _isLocalPathNameA(str_t str)
{
	bool_t ret = FALSE;
	size_t len = strlen(str);
	if (len >= 2 && str[0] == DIR_SEP_A && str[1] != DIR_SEP_A) ret = TRUE;										// "/some_path/...
	else if (len >= 3 && isalpha( ((int)str[0] & 0xFF) ) && str[1] == ':' && str[2] == DIR_SEP_A) ret = TRUE;	// [A..z]:/...
	else if (len >= 1 && str[0] != DIR_SEP_A) ret = TRUE;														// "some_path/...
	return ret;
}
#endif

#ifndef UNIX_SYSTEM
static bool_t _isLocalPathNameW(wstr_t str)
{
	bool_t ret = FALSE;
	size_t len = wcslen(str);
	if (len >= 2 && str[0] == DIR_SEP_W && str[1] != DIR_SEP_W) ret = TRUE;	// "\some_path...
	else if (len >= 3 && iswalpha( ((int)str[0] & 0xFFFF) ) && str[1] == L':' && str[2] == DIR_SEP_W) ret = TRUE;	// [A..z]:/...
	else if (len >= 1 && str[0] != DIR_SEP_W) ret = TRUE;					// "some_path...
	return ret;
}
#endif

#ifndef UNIX_SYSTEM
static void _mkLongAbsPathNameA(char *dst, str_t src)
{
	char *dp = dst;
	strcpy(dp, "\\\\?\\"); dp+= 4;
	strcpy(dp, src);
}
#endif

#ifndef UNIX_SYSTEM
static void _mkLongAbsPathNameW(wchar_t *dst, wstr_t src)
{
	wchar_t *dp = dst;
	if (wcslen(src) >= 255)
	{
		wcscpy(dp, L"\\\\?\\");
		dp+= 4;
	}
	wcscpy(dp, src);
}
#endif

#ifndef UNIX_SYSTEM
static void _mkLongNetAbsPathNameA(char *dst, str_t src)
{
	char *dp = dst;
	strcpy(dp, "\\\\?\\UNC\\"); dp+= 8;
	strcpy(dp, src + 2);
}
#endif

#ifndef UNIX_SYSTEM
static void _mkLongNetAbsPathNameW(wchar_t *dst, wstr_t src)
{
	wchar_t *dp = dst;
	wcscpy(dp, L"\\\\?\\UNC\\"); dp+= 8;
	wcscpy(dp, src + 2);
}
#endif
// Path Checker
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// PATH Helper
bool_t Dz1PathA_isAbsPath(str_t str)
{
	size_t len = str == NULL ? 0 : strlen(str);
#ifndef UNIX_SYSTEM
	if (len >= 2 && isalpha( (int)(str[0] & 0xFF)) && str[1] == ':') return TRUE;
	else if (len >= 1 && str[0] == DIR_SEP_A) return TRUE;
	else return _isNetworkAbsPathA(str, len);
#else
	if (len >= 1 && *str == DIR_SEP_A) return TRUE; else return FALSE;
#endif
}

#ifndef UNIX_SYSTEM
bool_t Dz1PathW_isAbsPath(wstr_t str)
{
	size_t len = wcslen(str);
	if (len >= 2 && iswalpha((wint_t)(str[0] & 0xFFFF)) && str[1] == L':') return TRUE;
	else if (len >= 1 && str[0] == DIR_SEP_W) return TRUE;
	else return _isNetworkAbsPathW(str, len);
}
#endif

str_t Dz1Path_getLastPathA(str_t src)
{
	str_t ret = NULL;
	if (src != NULL && strlen(src) > 1)
	{
		str_t cp = strrchr(src, DIR_SEP);
		if (cp != NULL) ret = (cp + 1);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
wstr_t Dz1Path_getLastPathW(wstr_t src)
{
	wstr_t ret = NULL;
	if (src != NULL && wcslen(src) > 1)
	{
		wstr_t cp = wcsrchr(src, DIR_SEP_W);
		if (cp != NULL) ret = (cp + 1);
	}
	return ret;
}
#endif

void Dz1Path_trimLastPathA(str_t dst)
{
	if (dst != NULL && strlen(dst) > 1)
	{
		str_t cp = strrchr(dst, DIR_SEP);
		if (cp != NULL) *cp = 0;
	}
}

#ifndef UNIX_SYSTEM
void Dz1Path_trimLastPathW(wstr_t dst)
{
	if (dst != NULL && wcslen(dst) > 1)
	{
		wstr_t cp = wcsrchr(dst, DIR_SEP_W);
		if (cp != NULL) *cp = 0;
	}
}
#endif

int Dz1Path_cmpA(str_t _a, str_t _b)
{
	if (_a == NULL && _b == NULL) return 0;
	else if (_a == NULL && _b != NULL) return -1;
	else if (_a != NULL && _b == NULL) return 1;
	else
	{
		int ret = 0;
		char *pa = _a, *pb = _b;
		int a, b;
		while(*pa && *pb)
		{
#ifndef UNIX_SYSTEM
			a = (int)(Dz1LetterA_ucase(*pa) & 0xFF);
			b = (int)(Dz1LetterA_ucase(*pb) & 0xFF);
#else
			a = (int)(*pa) & 0xFF;
			b = (int)(*pb) & 0xFF;
#endif
			if ((ret = a - b) != 0) return ret;

			pa++;
			pb++;
		}
		if		(*pa == 0 && *pb == 0) return 0;
		else if (*pa != 0 && *pb == 0) return -1;
		else if (*pa == 0 && *pb != 0) return 1;
		else return 0;
	}
}

#ifndef UNIX_SYSTEM
int Dz1Path_cmpW(wstr_t _a, wstr_t _b)
{
	if (_a == NULL && _b == NULL) return 0;
	else if (_a == NULL && _b != NULL) return -1;
	else if (_a != NULL && _b == NULL) return 1;
	else
	{
		int ret = 0;
		wchar_t *pa = _a, *pb = _b;
		int a, b;
		while(*pa && *pb)
		{
			a = (int)(Dz1LetterW_ucase(*pa) & 0xFFFF);
			b = (int)(Dz1LetterW_ucase(*pb) & 0xFFFF);

			if ((ret = a - b) != 0) return ret;

			pa++;
			pb++;
		}
		if		(*pa == 0 && *pb == 0) return 0;
		else if (*pa != 0 && *pb == 0) return -1;
		else if (*pa == 0 && *pb != 0) return 1;
		else return 0;
	}
}
#endif

Dz1Error Dz1PathStrA_appendSepStr(char dst[4096], str_t str)
{	// Append '/' + str
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (str != NULL && str[0] != 0)
	{
		size_t sz = 4095;

		char *ep = dst;
		while(sz && *ep != 0) { ep++; sz--; }

		if (sz > 0)
		{
			char *sp = str;
			*ep++ = DIR_SEP_A;

			while(sz && *sp != 0)
			{
				*ep++ = *sp++;
				sz--;
			}
			*ep = 0;

			if (*sp != 0) Dz1Error_set(errp, E2BIG);
			else Dz1Error_set(errp, 0);
		}
		else Dz1Error_set(errp, E2BIG);
	}
	else Dz1Error_set(errp, EINVAL);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1PathStrW_appendSepStr(wchar_t dst[4096], wstr_t str)
{	// Append '/' + str
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (Dz1Str_isVoid(str)) Dz1Error_set(errp, EINVAL);
	else
	{
		size_t sz = 4095;

		wchar_t *ep = dst;
		while(sz && *ep != 0) { ep++; sz--; }

		if (sz > 0)
		{
			wchar_t *sp = str;
			*ep++ = DIR_SEP_W;

			while(sz && *sp != 0)
			{
				*ep++ = *sp++;
				sz--;
			}
			*ep = 0;

			if (*sp != 0) Dz1Error_set(errp, E2BIG);
			else Dz1Error_set(errp, 0);
		}
		else Dz1Error_set(errp, E2BIG);
	}
	return err;
}
#endif

Dz1Error Dz1PathStrA_appendDotStr(char dst[4096], str_t str)
{	// Append '.' + str
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (str != NULL && str[0] != 0)
	{
		size_t sz = 4095;

		char *ep = dst;
		while(sz && *ep != 0) { ep++; sz--; }

		if (sz > 0)
		{
			char *sp = str;
			*ep++ = '.';

			while(sz && *sp != 0)
			{
				*ep++ = *sp++;
				sz--;
			}
			*ep = 0;

			if (*sp != 0) Dz1Error_set(errp, E2BIG);
			else Dz1Error_set(errp, 0);
		}
		else Dz1Error_set(errp, E2BIG);
	}
	else Dz1Error_set(errp, EINVAL);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1PathStrW_appendDotStr(wchar_t dst[4096], wstr_t str)
{	// Append '.' + str
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (str != NULL && str[0] != 0)
	{
		size_t sz = 4095;

		wchar_t *ep = dst;
		while(sz && *ep != 0) { ep++; sz--; }

		if (sz > 0)
		{
			wchar_t *sp = str;
			*ep++ = L'.'; sz--;

			while(sz && *sp != 0)
			{
				*ep++ = *sp++;
				sz--;
			}
			*ep = 0;

			if (*sp != 0) Dz1Error_set(errp, E2BIG);
			else Dz1Error_set(errp, 0);
		}
		else Dz1Error_set(errp, E2BIG);
	}
	else Dz1Error_set(errp, EINVAL);
	return err;
}
#endif

Dz1Error Dz1PathStrA_concat(char *dst, size_t dst_sz, ...)
{	// aaa / bbb / ...
	DZ1_ERROR_SAFE_VAR(errp, err);

	bool_t is_first = TRUE;
	char *name = NULL;
	char *dp = dst;
	size_t len;

	va_list ap;
	va_start(ap, dst_sz);
	while(errp->code == 0 && (name = (char *)va_arg(ap, char*)) != NULL)
	{
		if ((len = strlen(name)) > 0)
		{
			if (is_first) is_first = FALSE;
			else if (dst_sz <= 1) { ERR_SET_OUT(errp, E2BIG); break; }
			else { *dp++ = DIR_SEP_A; dst_sz--; }

			if (dst_sz <= len) { ERR_SET_OUT(errp, E2BIG); break; }
			else { strcpy(dp, name); dp+= len; }
		}
	}
	va_end(ap);
	*dp = 0;

	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1PathStrW_concat(wchar_t *dst, size_t dst_sz, ...)
{	// aaa / bbb / ...
	DZ1_ERROR_SAFE_VAR(errp, err);

	bool_t is_first = TRUE;
	wchar_t *name = NULL;
	wchar_t *dp = dst;
	size_t len;

	va_list ap;
	va_start(ap, dst_sz);
	while(errp->code == 0 && (name = (wchar_t *)va_arg(ap, wchar_t*)) != NULL)
	{
		if ((len = wcslen(name)) > 0)
		{
			if (is_first) is_first = FALSE;
			else if (dst_sz <= 1) { ERR_SET_OUT(errp, E2BIG); break; }
			else { *dp++ = DIR_SEP_W; dst_sz--; }

			if (dst_sz <= len) { ERR_SET_OUT(errp, E2BIG); break; }
			else { wcscpy(dp, name); dp+= len; }
		}
	}
	va_end(ap);
	*dp = 0;

	return err;
}
#endif
// PATH Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// File Name Helper
static void _concatPathNameA(char *dst, str_t path, size_t path_len, str_t name, size_t name_len)
{
	char *cp = dst;
	strcpy(cp, path); cp += path_len;
	if (*(cp - 1) != DIR_SEP_A) *cp++ = DIR_SEP_A;
	strcpy(cp, name); cp += name_len;
	*cp = 0;
}

bool_t _Dz1FileNameA_concatPathName(str_t dst, size_t dst_sz, str_t path, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || Dz1Str_isVoid(name)) Dz1Error_set(errp, EINVAL);
	else
	{
		size_t name_len = strlen(name);
		if (Dz1Str_isVoid(path))
		{
			if (name_len >= dst_sz) ERR_SET_OUT(errp, ENOMEM);
			else strcpy(dst, name);
		}
		else
		{
			size_t path_len = strlen(path);
			bool_t path_without_sep = (path[path_len - 1] != DIR_SEP_A) ? TRUE : FALSE;
			if (path_len + path_without_sep + name_len >= dst_sz) ERR_SET_OUT(errp, ENOMEM);
			else
			{
				_concatPathNameA(dst, path, path_len, name, name_len);
				Dz1Error_set(errp, 0);
			}
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

str_t Dz1FileNameA_genConcatPathName(str_t path, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t ret = NULL;
	if (Dz1Str_isVoid(name)) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1Str_isVoid(path))
	{
		if ((ret = Dz1StrA_dup(name, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		size_t name_len = strlen(name);
		size_t path_len = Dz1Str_isVoid(path) ? 0 : strlen(path);
		bool_t path_without_sep = (path[path_len - 1] != DIR_SEP_A) ? TRUE : FALSE;
		size_t total = path_len + path_without_sep + name_len + 1;
		if ((ret = (str_t)Dz1Calloc(sizeof(char), total, errp)) == NULL) ERR_OUT(errp);
		else
		{
			_concatPathNameA(ret, path, path_len, name, name_len);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

#ifndef UNIX_SYSTEM
static void _concatPathNameW(wchar_t *dst, wstr_t path, size_t path_len, wstr_t name, size_t name_len)
{
	wchar_t *cp = dst;
	wcscpy(cp, path); cp += path_len;
	if (*(cp - 1) != DIR_SEP_W) *cp++ = DIR_SEP_W;
	wcscpy(cp, name); cp += name_len;
	*cp = 0;
}

bool_t _Dz1FileNameW_concatPathName(wstr_t dst, size_t dst_sz, wstr_t path, wstr_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (dst == NULL || Dz1Str_isVoid(name)) Dz1Error_set(errp, EINVAL);
	else
	{
		size_t name_len = wcslen(name);
		if (Dz1Str_isVoid(path) == TRUE)
		{
			if (name_len >= dst_sz) ERR_SET_OUT(errp, ENOMEM);
			else wcscpy(dst, name);
		}
		else
		{
			size_t path_len = wcslen(path);
			bool_t path_without_sep = (path[path_len - 1] != DIR_SEP_W) ? TRUE : FALSE;
			if (path_len + path_without_sep + name_len >= dst_sz) ERR_SET_OUT(errp, ENOMEM);
			else
			{
				_concatPathNameW(dst, path, path_len, name, name_len);
				Dz1Error_set(errp, 0);
			}
			Dz1Error_set(errp, 0);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;;
}

wstr_t Dz1FileNameW_genConcatPathName(wstr_t path, wstr_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t ret = NULL;
	if (Dz1Str_isVoid(name)) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1Str_isVoid(path))
	{
		if ((ret = Dz1StrW_dup(name, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		size_t name_len = wcslen(name);
		size_t path_len = Dz1Str_isVoid(path) ? 0 : wcslen(path);
		bool_t path_without_sep = (path[path_len - 1] != DIR_SEP_W) ? TRUE : FALSE;
		size_t total = path_len + path_without_sep + name_len + 1;
		if ((ret = (wstr_t)Dz1Calloc(sizeof(wchar_t), total, errp)) == NULL) ERR_OUT(errp);
		else
		{
			_concatPathNameW(ret, path, path_len, name, name_len);
			Dz1Error_set(errp, 0);
		}
	}
	return ret;
}

#endif

Dz1Error Dz1FileNameA_concatPathName(char *dst, size_t dst_sz, str_t path, str_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1FileNameA_concatPathName(dst, dst_sz, path, name, errp) == FALSE) { }
	else Dz1Error_set(errp, 0);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1FileNameW_concatPathName(wchar_t *dst, size_t dst_sz, wstr_t path, wstr_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1FileNameW_concatPathName(dst, dst_sz, path, name, errp) == FALSE) { }
	else Dz1Error_set(errp, 0);
	return err;
}
#endif

bool_t _Dz1FileNameA_concatPathNameExt(char *dst, size_t dst_sz, str_t path, str_t name, str_t ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (name == NULL || name[0] == 0) Dz1Error_set(errp, EINVAL);
	else if (path == NULL || path[0] == 0)
	{
		if (_Dz1FileNameA_concatNameExt(dst, dst_sz, name, ext, errp) == FALSE) { }
		else Dz1Error_set(errp, 0);
	}
	else
	{
		size_t len = 0;
		strcpy(dst, path);
		len = strlen(dst);
		if (dst[len - 1] != DIR_SEP_A) strcat(dst, DIR_SEPRATOR_A);
		strcat(dst, name);
		if (ext != NULL && ext[0] != 0)
		{
			strcat(dst, ".");
			strcat(dst, ext);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}

#ifndef UNIX_SYSTEM
bool_t	_Dz1FileNameW_concatPathNameExt(wchar_t *dst, size_t dst_sz, wstr_t path, wstr_t name, wstr_t ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (Dz1Str_isVoid(name) == TRUE) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1Str_isVoid(path) == TRUE)
	{
//		if ((*errp = Dz1FileNameW_concatNameExt(dst, name, ext)).code) ERR_OUT(errp);
		if (_Dz1FileNameW_concatNameExt(dst, dst_sz, name, ext, errp) == FALSE) { }
		else Dz1Error_set(errp, 0);
	}
	else
	{
		size_t len = 0;
		wcscpy(dst, path);
		len = wcslen(dst);
		if (dst[len - 1] != DIR_SEP_W) wcscat(dst, DIR_SEPRATOR_W);
		wcscat(dst, name);
		if (ext != NULL && ext[0] != 0)
		{
			wcscat(dst, L".");
			wcscat(dst, ext);
		}
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#endif

Dz1Error Dz1FileNameA_concatPathNameExt(char *dst, size_t dst_sz, str_t path, str_t name, str_t ext)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1FileNameA_concatPathNameExt(dst, dst_sz, path, name, ext, errp) == FALSE) { }
	else Dz1Error_set(errp, 0);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1FileNameW_concatPathNameExt(wchar_t *dst, size_t dst_sz, wstr_t path, wstr_t name, wstr_t ext)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1FileNameW_concatPathNameExt(dst, dst_sz, path, name, ext, errp) == FALSE) { }
	else Dz1Error_set(errp, 0);
	return err;
}
#endif

bool_t _Dz1FileNameA_concatNameExt(char *dst, size_t dst_sz, str_t name, str_t ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (Dz1Str_isVoid(name) == TRUE) Dz1Error_set(errp, EINVAL);
	else
	{
		size_t name_len = strlen(name);
		if (Dz1Str_isVoid(ext))
		{
			if (name_len >= dst_sz) ERR_SET_OUT(errp, ENOMEM);
			else
			{
				strcpy(dst, name);
				Dz1Error_set(errp, 0);
			}
		}
		else
		{
			size_t ext_len = strlen(ext);
			if (name_len + 1 + ext_len >= dst_sz) ERR_SET_OUT(errp, ENOMEM);
			else
			{
				char *dp = dst;
				strcpy(dp, name); dp += name_len;
				*dp++ = '.';
				strcpy(dp, ext); dp += ext_len;
				*dp = 0;
				Dz1Error_set(errp, 0);
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}

#ifndef UNIX_SYSTEM
bool_t _Dz1FileNameW_concatNameExt(wchar_t *dst, size_t dst_sz, wstr_t name, wstr_t ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	if (name == NULL) Dz1Error_set(errp, EINVAL);
	else
	{
		size_t name_len = wcslen(name);
		if (Dz1Str_isVoid(ext))
		{
			if (name_len >= dst_sz) ERR_SET_OUT(errp, ENOMEM);
			else
			{
				wcscpy(dst, name);
				Dz1Error_set(errp, 0);
			}
		}
		else
		{
			size_t ext_len = wcslen(ext);
			if (name_len + 1 + ext_len >= dst_sz) ERR_SET_OUT(errp, ENOMEM);
			else
			{
				wchar_t *dp = dst;
				wcscpy(dp, name); dp += name_len;
				*dp++ = L'.';
				wcscpy(dp, ext); dp += ext_len;
				*dp = 0;
				Dz1Error_set(errp, 0);
			}
		}
	}
	return ERR_IS_SUCCESS(errp);
}
#endif

Dz1Error Dz1FileNameA_concatNameExt(char *dst, size_t dst_sz, str_t name, str_t ext)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (_Dz1FileNameA_concatNameExt(dst, dst_sz, name, ext, errp) == FALSE) { }
	else Dz1Error_set(errp, 0);

	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1FileNameW_concatNameExt(wchar_t *dst, size_t dst_sz, wstr_t name, wstr_t ext)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (_Dz1FileNameW_concatNameExt(dst, dst_sz, name, ext, errp) == FALSE) { }
	else Dz1Error_set(errp, 0);

	return err;
}
#endif

bool_t _Dz1FileNameA_splitPathName(char *dstPath, char *dstName, str_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t temp = NULL;
	if (Dz1Str_isVoid(src)) Dz1Error_set(errp, EINVAL);
	else if (dstPath == NULL && dstName == NULL) Dz1Error_set(errp, EINVAL);
	else if ((temp = Dz1StrA_dup(src, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char *cp = NULL;
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&temp);
		if ((cp = strrchr(temp, DIR_SEP)) == NULL)
		{	// path 구분자가 없다 -> 파일명으로만 된 문자열
			if (dstName != NULL) strcpy(dstName, src);
			if (dstPath != NULL) dstPath[0] = '\0';
		}
		else
		{	// path 구분자가 있다
			*cp++ = '\0';
			if (cp[0] == 0)
			{	// 구분자 다음이 끝이다 -> 경로명으로만 된 문자열
				if (dstPath != NULL) strcpy(dstPath, temp);
				if (dstName != NULL) dstName[0] = 0;
			}
			else
			{
				if (dstPath != NULL) strcpy(dstPath, temp);
				if (dstName != NULL) strcpy(dstName, cp);
			}
		}
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&temp);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

#ifndef UNIX_SYSTEM
bool_t _Dz1FileNameW_splitPathName(wchar_t *dstPath, wchar_t *dstName, wstr_t src, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wchar_t *temp = NULL;
	if (Dz1Str_isVoid(src)) Dz1Error_set(errp, EINVAL);
	else if (dstPath == NULL && dstName == NULL) Dz1Error_set(errp, EINVAL);
	else if ((temp = Dz1StrW_dup(src, errp)) == NULL) ERR_OUT(errp);
	else
	{
		wchar_t *cp = NULL;
		pthread_cleanup_push(Dz1StrW_delAndSetNull, (void *)&temp);
		if ((cp = wcsrchr(temp, DIR_SEP_W)) == NULL)
		{	// path 구분자가 없다 -> 파일명으로만 된 문자열
			if (dstPath != NULL) dstPath[0] = '\0';
			if (dstName != NULL) wcscpy(dstName, src);
		}
		else
		{	// path 구분자가 있다
			*cp++ = '\0';
			if (cp[0] == 0)
			{	// 구분자 끝이 0이다 -> 경로만으로 된 문자열
				if (dstPath != NULL) wcscpy(dstPath, temp);
				if (dstName != NULL) dstName[0] = 0;
			}
			else
			{
				if (dstPath != NULL) wcscpy(dstPath, temp);
				if (dstName != NULL) wcscpy(dstName, cp);
			}
		}
		pthread_cleanup_pop(1); // (Dz1StrW_delAndSetNull, (void *)&temp);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}
#endif

Dz1Error Dz1FileNameA_splitPathName(char *dstPath, char *dstName, str_t src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (_Dz1FileNameA_splitPathName(dstPath, dstName, src, errp) == FALSE) { }
	else Dz1Error_set(errp, 0);

	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1FileNameW_splitPathName(wchar_t *dstPath, wchar_t *dstName, wstr_t src)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (_Dz1FileNameW_splitPathName(dstPath, dstName, src, errp) == FALSE) { }
	else Dz1Error_set(errp, 0);

	return err;
}
#endif

bool_t _Dz1FileNameA_splitNameExt(char *dstName, char *dstExt, str_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	char *temp = NULL;
	if (Dz1Str_isVoid(name) == TRUE) Dz1Error_set(errp, EINVAL);
	else if (dstName == NULL && dstExt == NULL) Dz1Error_set(errp, EINVAL);
	else if ((temp = Dz1StrA_dup(name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		char *cp = NULL;
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&temp);
		if ((cp = strrchr(temp, '.')) == NULL)
		{	// 확장자 구분자가 없다 -> 확장자 없는 파일명
			if (dstName != NULL) strcpy(dstName, temp);
			if (dstExt != NULL) dstExt[0] = 0;
		}
		else
		{
			*cp++ = '\0';
			if (dstName != NULL) strcpy(dstName, temp);
			if (dstExt != NULL) strcpy(dstExt, cp);
		}
		pthread_cleanup_pop(1); // (Dz1StrA_delAndSetNull, (void *)&temp);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_SUCCESS(errp);
}

#ifndef UNIX_SYSTEM
bool_t _Dz1FileNameW_splitNameExt(wchar_t *dstName, wchar_t *dstExt, wstr_t name, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wchar_t *temp = NULL;
	if (Dz1Str_isVoid(name) == TRUE) Dz1Error_set(errp, EINVAL);
	else if (dstName == NULL && dstExt == NULL) Dz1Error_set(errp, EINVAL);
	else if ((temp = Dz1StrW_dup(name, errp)) == NULL) ERR_OUT(errp);
	else
	{
		wchar_t *pt = NULL;
		pthread_cleanup_push(Dz1StrW_delAndSetNull, (void *)&temp);
		if ((pt = wcsrchr(temp, L'.')) == NULL)
		{	// no ext
			if (dstName != NULL) wcscpy(dstName, temp);
			if (dstExt != NULL) dstExt[0] = 0;
		}
		else
		{
			*pt++ = 0;
			if (dstName != NULL) wcscpy(dstName, temp);
			if (dstExt != NULL) wcscpy(dstExt, pt);
		}
		pthread_cleanup_pop(1); // (Dz1StrW_delAndSetNull, (void *)&temp);
		Dz1Error_set(errp, 0);
	}
	return ERR_IS_FAIL(errp);
}
#endif

Dz1Error Dz1FileNameA_splitNameExt(char *dstName, char *dstExt, str_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (_Dz1FileNameA_splitNameExt(dstName, dstExt, name, errp) == FALSE) { }
	else Dz1Error_set(errp, 0);

	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1FileNameW_splitNameExt(wchar_t *dstName, wchar_t *dstExt, wstr_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1FileNameW_splitNameExt(dstName, dstExt, name, errp) == FALSE) { }
	else Dz1Error_set(errp, 0);
	return err;
}
#endif

bool_t _Dz1FileNameA_getExt(char *dstExt, str_t name, Dz1Error *err)
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if ((ret = _Dz1FileNameA_splitNameExt(NULL, dstExt, name, errp)) == FALSE) { }
	else Dz1Error_set(errp, 0);

	return ret;
}

#ifndef UNIX_SYSTEM
bool_t _Dz1FileNameW_getExt(wchar_t *dstExt, wstr_t name, Dz1Error *err)
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_PTR(errp, err);

	if ((ret = _Dz1FileNameW_splitNameExt(NULL, dstExt, name, errp)) == FALSE) { }
	else Dz1Error_set(errp, 0);

	return ret;
}
#endif

Dz1Error Dz1FileNameA_getExt(char *dstExt, str_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1FileNameA_getExt(dstExt, name, errp) == FALSE) { }
	else Dz1Error_set(errp, 0);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1FileNameW_getExt(wchar_t *dstExt, wstr_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_Dz1FileNameW_getExt(dstExt, name, errp) == FALSE) { }
	else Dz1Error_set(errp, 0);
	return err;
}
#endif
// File Name Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// File Operation Helper Functions
#ifdef UNIX_SYSTEM
bool_t Dz1StdioA_isFile(str_t pathname, Dz1Error *err)
{
	bool_t ret = TRUE;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	struct stat buf;
	if (stat(pathname, &buf) < 0) ERR_SET_OUT(errp, errno);
	else ret = S_ISDIR(buf.st_mode) ? FALSE : TRUE;
	return ret;
}

bool_t Dz1StdioW_isFile(wstr_t pathname, Dz1Error *err)
{
	bool_t ret = TRUE;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	struct stat buf;
	if (stat((str_t)pathname, &buf) < 0) ERR_SET_OUT(errp, errno);
	else ret = S_ISDIR(buf.st_mode) ? FALSE : TRUE;
	return ret;
}
#else
#ifdef __BORLANDC__
#define STRUCT_STAT64      	struct stati64
#define FUNC_STAT64A        _stati64
#define FUNC_STAT64W        _wstati64
#else // __BORLANDC__
#define STRUCT_STAT64		struct __stat64
#define FUNC_STAT64A        _stat64
#define FUNC_STAT64W        _wstat64
#endif // __BORLANDC__

bool_t Dz1StdioA_isFile(str_t pathname, Dz1Error *err)
{
	bool_t ret = TRUE;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	STRUCT_STAT64 buf;
	if (FUNC_STAT64A(pathname, &buf) < 0) ERR_SET_OUT(errp, errno);
	else ret = (buf.st_mode & _S_IFDIR) ? FALSE : TRUE;
	return ret;
}

bool_t Dz1StdioW_isFile(wstr_t pathname, Dz1Error *err)
{
	bool_t ret = TRUE;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	STRUCT_STAT64 buf;
	if (FUNC_STAT64W(pathname, &buf) < 0) ERR_SET_OUT(errp, errno);
	else ret = (buf.st_mode & _S_IFDIR) ? FALSE : TRUE;
	return ret;
}
#endif

#ifdef UNIX_SYSTEM
// File Existence Checker for UNIX
bool_t Dz1FileA_isExist(str_t fn)
{
	struct stat status;
	if (stat(fn, &status) < 0) return FALSE; 
	else return TRUE;
}
#else // UNIX_SYSTEM = FALSE
bool_t Dz1FileA_isExist(str_t fn)
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_VAR(errp, err);

// 	struct _stat status;
// 
// 	if (_stat(fn, &status) < 0) 
// 	{
// 		Dz1Error_set(errp, errno);
// 		if (errp->code != ENOENT) ERR_OUT(errp);
// 	}
// 	else if ((status.st_mode & _S_IFREG) == 0) ERR_SET_OUT(errp, EPERM);
// 	else ret = TRUE;

	DWORD flag = 0;
	char temp[4096] = { 0, };
	if (_isLocalPathNameA(fn) && strlen(fn) > 255)
		_mkLongAbsPathNameA(temp, fn);
	else strcpy(temp, fn);

	if ((flag = GetFileAttributesA(temp)) == INVALID_FILE_ATTRIBUTES)
	{
		Dz1Error_set(errp, GetLastError());
		if (errp->code != ENOENT) ERR_OUT(errp);
	}
	else if ((flag & 0x10) == 0x10) ERR_SET_OUT(errp, EPERM);	// not directory
	else ret = TRUE;

	return ret;
}

bool_t Dz1FileW_isExist(wstr_t fn)
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_VAR(errp, err);

	// 	struct _stat status;
// 
// 	if (_wstat(fn, &status) < 0)
// 	{
// 		Dz1Error_set(errp, errno);
// 		if (errp->code != ENOENT) ERR_OUT(errp);
// 	}
// 	else if ((status.st_mode & _S_IFREG) == 0) ERR_SET_OUT(errp, EPERM);
// 	else ret = TRUE;

	DWORD flag = 0;
	wchar_t temp[4096] = { 0, };
	if (_isLocalPathNameW(fn) && wcslen(fn) > 255)
		_mkLongAbsPathNameW(temp, fn);
	else wcscpy(temp, fn);

	if ((flag = GetFileAttributesW(temp)) == INVALID_FILE_ATTRIBUTES)
	{
		Dz1Error_set(errp, GetLastError());
		if (errp->code != ENOENT) ERR_OUT(errp);
	}
	else if ((flag & 0x10) == 0x10) ERR_SET_OUT(errp, EPERM);	// not directory
	else ret = TRUE;

	return ret;
}
#endif // UNIX_SYSTEM

bool_t Dz1FileA_isExist2(str_t path, str_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t ret = FALSE;

	char fn[4096];
	if ((*errp = Dz1FileNameA_concatPathName(fn, ARR_VAR_SIZE(char, fn), path, name)).code) ERR_OUT(errp);
	else ret = Dz1FileA_isExist(fn);

	return ret;
}

bool_t Dz1FileA_isExist3(str_t path, str_t name, str_t ext)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t ret = FALSE;

	char fn[4096];
	if ((*errp = Dz1FileNameA_concatPathNameExt(fn, ARR_VAR_SIZE(char, fn), path, name, ext)).code) ERR_OUT(errp);
	else ret = Dz1FileA_isExist(fn);

	return ret;
}

#ifndef UNIX_SYSTEM
bool_t Dz1FileW_isExist2(wstr_t path, wstr_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t ret = FALSE;

	wchar_t fn[4096];
	if ((*errp = Dz1FileNameW_concatPathName(fn, ARR_VAR_SIZE(wchar_t, fn), path, name)).code) ERR_OUT(errp);
	else ret = Dz1FileW_isExist(fn);

	return ret;
}

bool_t Dz1FileW_isExist3(wstr_t path, wstr_t name, wstr_t ext)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	bool_t ret = FALSE;

	wchar_t fn[4096];
	if ((*errp = Dz1FileNameW_concatPathNameExt(fn, ARR_VAR_SIZE(wchar_t, fn), path, name, ext)).code) ERR_OUT(errp);
	else ret = Dz1FileW_isExist(fn);

	return ret;
}
#endif //!UNIX_SYSTEM

Dz1Error Dz1FileA_delete(str_t fn)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (fn == NULL || fn[0] == 0) ERR_SET_OUT(errp, EINVAL);
#ifndef UNIX_SYSTEM
	else if (Dz1PathA_isAbsPath(fn))
	{
		char temp[4096];
		_mkLongAbsPathNameA(temp, fn);
		if (unlink(temp) != 0)
		{
			switch(errno)
			{
			case ENOENT:
				Dz1Error_set(errp, 0);
				break;
			default:
				Dz1Error_set(errp, errno);
				break;
			}
		}
	}
#endif
	else if (unlink(fn) != 0)
	{
		switch(errno)
		{
		case ENOENT:
			Dz1Error_set(errp, 0);
			break;
		default:
			Dz1Error_set(errp, errno);
			break;
		}
	}
	else Dz1Error_set(errp, 0);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1FileW_delete(wstr_t fn)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (fn == NULL || fn[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1PathW_isAbsPath(fn))
	{
		wchar_t temp[4096];
		_mkLongAbsPathNameW(temp, fn);
		if (_wunlink(temp) != 0)
		{
			switch(errno)
			{
			case ENOENT:
				Dz1Error_set(errp, 0);
				break;
			default:
				Dz1Error_set(errp, errno);
				break;
			}
		}
	}
	else
	{
		if (_wunlink(fn) != 0)
		{
			switch(errno)
			{
			case ENOENT:
				Dz1Error_set(errp, 0);
				break;
			default:
				Dz1Error_set(errp, errno);
				break;
			}
		}
	}
	return err;
}
#endif

Dz1Error Dz1FileA_delete2(str_t path, str_t name)
{
	char fn[4096];
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1FileNameA_concatPathName(fn, ARR_VAR_SIZE(char, fn), path, name)).code) ERR_OUT(errp);
	else if ((*errp = Dz1FileA_delete(fn)).code) { }
	return err;
}

Dz1Error Dz1FileA_delete3(str_t path, str_t name, str_t ext)
{
	char fn[2048];
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1FileNameA_concatNameExt(fn, ARR_VAR_SIZE(char, fn), name, ext)).code) ERR_OUT(errp);
	else if ((*errp = Dz1FileA_delete2(path, fn)).code) { }
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1FileW_delete2(wstr_t path, wstr_t name)
{
	wchar_t fn[4096];
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1FileNameW_concatPathName(fn, ARR_VAR_SIZE(wchar_t, fn), path, name)).code) ERR_OUT(errp);
	else if ((*errp = Dz1FileW_delete(fn)).code) { }
	return err;
}

Dz1Error Dz1FileW_delete3(wstr_t path, wstr_t name, wstr_t ext)
{
	wchar_t fn[2048];
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1FileNameW_concatNameExt(fn, ARR_VAR_SIZE(wchar_t, fn), name, ext)).code) ERR_OUT(errp);
	else if ((*errp = Dz1FileW_delete2(path, fn)).code) { }
	return err;
}
#endif

Dz1Error Dz1FileA_rename(str_t dstPathName, str_t srcPathName)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1Str_isVoid(dstPathName) == TRUE || Dz1Str_isVoid(srcPathName) == TRUE) Dz1Error_set(&err, EINVAL);
	else
	{
#ifdef UNIX_SYSTEM
		if (rename(srcPathName, dstPathName) != 0) Dz1Error_set(&err, errno);
#else
		char src[4096], dst[4096];
		if (_isNetPathNameA(srcPathName)) _mkLongNetAbsPathNameA(src, srcPathName);
		else if (Dz1PathA_isAbsPath(srcPathName)) _mkLongAbsPathNameA(src, srcPathName); 
		else strcpy(src, srcPathName);

		if (_isNetPathNameA(dstPathName)) _mkLongNetAbsPathNameA(dst, dstPathName);
		else if (Dz1PathA_isAbsPath(dstPathName)) _mkLongAbsPathNameA(dst, dstPathName); 
		else strcpy(dst, dstPathName);

		if (rename(src, dst) != 0) 
			Dz1Error_set(&err, errno);
#endif
	}
	return err;
}

#ifdef WIN32
Dz1Error Dz1FileW_rename(wstr_t dstPathName, wstr_t srcPathName)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	if (Dz1Str_isVoid(dstPathName) == TRUE || Dz1Str_isVoid(srcPathName) == TRUE) Dz1Error_set(&err, EINVAL);
	else
	{
		wchar_t src[4096], dst[4096];
		if (_isNetPathNameW(srcPathName)) _mkLongNetAbsPathNameW(src, srcPathName);
		else if (Dz1PathW_isAbsPath(srcPathName)) _mkLongAbsPathNameW(src, srcPathName);
		else wcscpy(src, srcPathName);

		if (_isNetPathNameW(dstPathName)) _mkLongNetAbsPathNameW(dst, dstPathName);
		else if (Dz1PathW_isAbsPath(dstPathName)) _mkLongAbsPathNameW(dst, dstPathName);
		else wcscpy(dst, dstPathName);

		if (_wrename(src, dst) != 0) Dz1Error_set(&err, errno);
	}
	return err;
}
#endif

Dz1Error Dz1FileA_rename2(str_t dstPath, str_t dstNameExt, str_t srcPath, str_t srcNameExt)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	char src[4096], dst[4096];
	if (Dz1Str_isVoid(dstPath) == TRUE || Dz1Str_isVoid(srcPath) == TRUE) Dz1Error_set(errp, EINVAL);
	else if (Dz1Str_isVoid(dstNameExt) == TRUE || Dz1Str_isVoid(srcNameExt) == TRUE) Dz1Error_set(errp, EINVAL);
	else if ((*errp = Dz1FileNameA_concatPathName(dst, 4096, dstPath, dstNameExt)).code) { }
	else if ((*errp = Dz1FileNameA_concatPathName(src, 4096, srcPath, srcNameExt)).code) { }
	else if ((*errp = Dz1FileA_rename(dst, src)).code) { }
	else Dz1Error_set(errp, 0);
	return err;
}

Dz1Error Dz1FileA_rename3(str_t dstPath, str_t dstName, str_t dstExt, str_t srcPath, str_t srcName, str_t srcExt)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	char src[4096], dst[4096];
	if (0) { }
	else if (Dz1Str_isVoid(dstPath) == TRUE || Dz1Str_isVoid(srcPath) == TRUE) Dz1Error_set(errp, EINVAL);
	else if (Dz1Str_isVoid(dstName) == TRUE || Dz1Str_isVoid(srcName) == TRUE) Dz1Error_set(errp, EINVAL);
	else if (Dz1Str_isVoid(dstExt) == TRUE || Dz1Str_isVoid(srcExt) == TRUE) Dz1Error_set(errp, EINVAL);
	else if (_Dz1FileNameA_concatPathNameExt(dst, ARR_VAR_SIZE(char, dst), dstPath, dstName, dstExt, errp) == FALSE) { }
	else if (_Dz1FileNameA_concatPathNameExt(src, ARR_VAR_SIZE(char, src), srcPath, srcName, srcExt, errp) == FALSE) { }
	else if ((*errp = Dz1FileA_rename(dst, src)).code) { }
	else Dz1Error_set(errp, 0);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1FileW_rename2(wstr_t dstPath, wstr_t dstNameExt, wstr_t srcPath, wstr_t srcNameExt)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	wchar_t src[4096], dst[4096];
	if (Dz1Str_isVoid(dstPath) == TRUE || Dz1Str_isVoid(srcPath) == TRUE) Dz1Error_set(errp, EINVAL);
	if (Dz1Str_isVoid(dstNameExt) == TRUE || Dz1Str_isVoid(srcNameExt) == TRUE) Dz1Error_set(errp, EINVAL);
	else if (_Dz1FileNameW_concatPathName(dst, ARR_VAR_SIZE(wchar_t, dst), dstPath, dstNameExt, errp) == FALSE) { }
	else if (_Dz1FileNameW_concatPathName(src, ARR_VAR_SIZE(wchar_t, src), srcPath, srcNameExt, errp) == FALSE) { }
	else if ((*errp = Dz1FileW_rename(dst, src)).code) { }
	else Dz1Error_set(errp, 0);
	return err;
}

Dz1Error Dz1FileW_rename3(wstr_t dstPath, wstr_t dstName, wstr_t dstExt, wstr_t srcPath, wstr_t srcName, wstr_t srcExt)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	wchar_t src[4096], dst[4096];
	if (0) { }
	else if (Dz1Str_isVoid(dstPath) == TRUE || Dz1Str_isVoid(srcPath) == TRUE) Dz1Error_set(errp, EINVAL);
	else if (Dz1Str_isVoid(dstName) == TRUE || Dz1Str_isVoid(srcName) == TRUE) Dz1Error_set(errp, EINVAL);
	else if (Dz1Str_isVoid(dstExt) == TRUE || Dz1Str_isVoid(srcExt) == TRUE) Dz1Error_set(errp, EINVAL);
	else if (_Dz1FileNameW_concatPathNameExt(dst, ARR_VAR_SIZE(wchar_t, dst), dstPath, dstName, dstExt, errp) == FALSE) ERR_OUT(errp);
	else if (_Dz1FileNameW_concatPathNameExt(src, ARR_VAR_SIZE(wchar_t, src), srcPath, srcName, srcExt, errp) == FALSE) ERR_OUT(errp);
	else if ((*errp = Dz1FileW_rename(dst, src)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
#endif

static Dz1Error _file_copy(FILE *dst, FILE *src, u32_t buf_size)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	u8_t *buf = (u8_t *)Dz1Malloc(buf_size, errp);
	if (buf == NULL) ERR_OUT(errp);
	else
	{
		size_t len = 0;
		pthread_cleanup_push(Dz1Memory_freeAndSetNull, (void *)&buf);
		while(1)
		{
			if ((len = fread(buf, sizeof(u8_t), buf_size, src)) == buf_size)
				fwrite(buf, sizeof(u8_t), buf_size, dst);
			else if (len > 0)
			{
				fwrite(buf, sizeof(u8_t), len, dst);
				break;
			}
			else break;
		}
		pthread_cleanup_pop(1); // (Dz1Memory_freeAndSetNull, (void *)&buf);
	}
	return err;
}

#ifdef UNIX_SYSTEM
static s64_t _getFileSizeA(str_t fn, Dz1Error *err)
{
	ssize_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	struct stat s;
	memset(&s, 0, sizeof(struct stat));
	if (stat(fn, &s) != 0) ERR_SET_OUT(errp, errno);
	else ret = s.st_size;
	return ret;
}
#else // UNIX_SYSTEM = FALSE
static s64_t _getFileSizeA(str_t fn, Dz1Error *err)
{
	s64_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	STRUCT_STAT64 s;
	memset(&s, 0, sizeof(struct _stat));

	if (Dz1PathA_isAbsPath(fn))
	{
		char temp[4096];
		_mkLongAbsPathNameA(temp, fn);
		if (FUNC_STAT64A(temp, &s) != 0) Dz1Error_set(errp, errno);
		else ret = s.st_size;
	}
	else
	{
		if (FUNC_STAT64A(fn, &s) != 0) Dz1Error_set(errp, errno);
		else ret = s.st_size;
	}

	return ret;
}

static s64_t _getFileSizeW(wstr_t fn, Dz1Error *err)
{
	s64_t ret = -1;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	STRUCT_STAT64 s;
	memset(&s, 0, sizeof(struct _stat));

// 	if (Dz1PathW_isAbsPath(fn))
// 	{
// 		wchar_t temp[4096];
// 		_mkLongAbsPathNameW(temp, fn);
// 
// 		if (_wstat64(temp, &s) != 0) Dz1Error_set(errp, errno);
// 		else ret = s.st_size;
// 
// 	}
// 	else
// 	{
		if (FUNC_STAT64W(fn, &s) != 0) Dz1Error_set(errp, errno);
		else ret = s.st_size;
//	}
	return ret;
}
#endif // UNIX_SYSTEM

Dz1Error Dz1FileA_copy(str_t dstPathName, str_t srcPathName)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	FILE *src = NULL;
	if ((src = Dz1FileStreamA_open(srcPathName, "rb", errp)) == NULL) { }
	else
	{
		FILE *dst = NULL;
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)src);

		if ((dst = Dz1FileStreamA_open(dstPathName, "wb", errp)) == NULL) { }
		else
		{
			pthread_cleanup_push(Dz1FileStream_cancel, (void *)dst);

			if ((*errp = _file_copy(dst, src, 4096)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)dst);
		}
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)src);
	}
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1FileW_copy(wstr_t dstPathName, wstr_t srcPathName)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;

	FILE *src = NULL;
	if ((src = Dz1FileStreamW_open(srcPathName, L"rb", errp)) == NULL) { }
	else
	{
		FILE *dst = NULL;
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)src);

		if ((dst = Dz1FileStreamW_open(dstPathName, L"wb", errp)) == NULL) { }
		else
		{
			pthread_cleanup_push(Dz1FileStream_cancel, (void *)dst);

			if ((*errp = _file_copy(dst, src, 4096)).code) ERR_OUT(errp);
			else Dz1Error_set(errp, 0);

			pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)dst);
		}
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)src);
	}
	return err;
}
#endif

s64_t Dz1FileA_getSize(str_t fn)
{
	s64_t ret = -1;
	DZ1_ERROR_SAFE_VAR(errp, err);

	if ((ret = _getFileSizeA(fn, errp)) == -1) ERR_OUT(errp);

	return ret;
}

s64_t Dz1FileA_getSize2(str_t path, str_t name)
{
	s64_t ret = -1;

	char fn[4096];
	DZ1_ERROR_SAFE_VAR(errp, err);

	if ((*errp = Dz1FileNameA_concatPathName(fn, ARR_VAR_SIZE(char, fn), path, name)).code) ERR_OUT(errp);
	else if ((ret = _getFileSizeA(fn, errp)) == -1) ERR_OUT(errp);

	return ret;
}

#ifndef UNIX_SYSTEM
s64_t Dz1FileW_getSize(wstr_t fn)
{
	s64_t ret = -1;
	DZ1_ERROR_SAFE_VAR(errp, err);

	if ((ret = _getFileSizeW(fn, errp)) == -1)
		ERR_OUT(errp);

	return ret;
}

s64_t Dz1FileW_getSize2(wstr_t path, wstr_t name)
{
	s64_t ret = -1;

	wchar_t fn[4096];
	DZ1_ERROR_SAFE_VAR(errp, err);

	if ((*errp = Dz1FileNameW_concatPathName(fn, ARR_VAR_SIZE(wchar_t, fn), path, name)).code) ERR_OUT(errp);
	else if ((ret = _getFileSizeW(fn, errp)) == -1) ERR_OUT(errp);

	return ret;
}
#endif

#ifdef UNIX_SYSTEM
static void _open_cancel(void *ptr)
{
	int *fd = (int *)ptr;
	if (fd != NULL) close(*fd);
}

static bool_t _unix_timespec_to_tm(struct tm *dst, struct timespec *src, Dz1Error *errp)
{
	time_t tStamp = (time_t)src->tv_sec;
	struct tm *tm_p = localtime(&tStamp);
	if (tm_p == NULL) ERR_SET_OUT(errp, EFAULT);
	else
	{
		memcpy(dst, tm_p, sizeof(struct tm));
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
static bool_t _unix_stat_getTime(struct tm *dstCre, struct tm *dstAcc, struct tm *dstMod, struct stat *st, Dz1Error *errp)
{
	if (st == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (dstAcc != NULL && _unix_timespec_to_tm(dstAcc, &st->st_atim, errp) == FALSE) ERR_OUT(errp);
	else if (dstMod != NULL && _unix_timespec_to_tm(dstMod, &st->st_mtim, errp) == FALSE) ERR_OUT(errp);
	else
	{
		if (dstCre != NULL) memset(dstCre, 0, sizeof(struct tm));
		Dz1Error_set(errp, 0);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#else
static bool_t _win32_filetime_to_tm(struct tm *dst, FILETIME *_src, Dz1Error *errp)
{
	FILETIME local_file_time;
	SYSTEMTIME local_file_systime;
	if (FileTimeToLocalFileTime(_src, &local_file_time) == FALSE) Dz1Error_set(errp, GetLastError());
	else if (FileTimeToSystemTime(&local_file_time, &local_file_systime) == FALSE) Dz1Error_set(errp, GetLastError());
	else
	{
		dst->tm_year = local_file_systime.wYear - 1900;
		dst->tm_mon  = local_file_systime.wMonth - 1;
		dst->tm_mday = local_file_systime.wDay;
		dst->tm_hour = local_file_systime.wHour;
		dst->tm_min  = local_file_systime.wMinute;
		dst->tm_sec  = local_file_systime.wSecond;
	}
	return errp->code == 0 ? TRUE : FALSE;
}

static bool_t _Dz1File_getTime(HANDLE f, struct tm *dstCre, struct tm *dstAcc, struct tm *dstMod, Dz1Error *errp)
{
	FILETIME tCre, tAcc, tMod;
	if (GetFileTime(f, &tCre, &tAcc, &tMod) == 0) ERR_SET_OUT(errp, GetLastError());
	else if (dstCre != NULL && (_win32_filetime_to_tm(dstCre, &tCre, errp)) == FALSE) ERR_OUT(errp);
	else if (dstAcc != NULL && (_win32_filetime_to_tm(dstAcc, &tAcc, errp)) == FALSE) ERR_OUT(errp);
	else if (dstMod != NULL && (_win32_filetime_to_tm(dstMod, &tMod, errp)) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

static void _CreateFileCancel(void *ptr)
{
	HANDLE *f = (HANDLE *)ptr;
	CloseHandle(*f);
}
#endif

#ifdef UNIX_SYSTEM
Dz1Error Dz1FileA_time(str_t fn, time_t *ret)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (ret == NULL) ERR_SET_OUT(errp, EINVAL);
	else 
	{
		struct tm tm_mod;
		if (Dz1FileA_getTime(NULL, NULL, &tm_mod, fn, errp) == FALSE) ERR_OUT(errp);
		else
		{
			*ret = mktime(&tm_mod);
			Dz1Error_set(errp, 0);
		}
	}
	return err;
}
#else
Dz1Error Dz1FileA_time(str_t fn, time_t *ret)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	STRUCT_STAT64 buf;
	memset(&buf, 0, sizeof(STRUCT_STAT64));
	if (FUNC_STAT64A(fn, &buf) < 0) Dz1Error_set(errp, errno);
	else
	{
		(*ret) = buf.st_mtime;
		Dz1Error_set(errp, 0);
	}
	return err;
}

Dz1Error Dz1FileW_time(wstr_t fn, time_t *ret)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	STRUCT_STAT64 buf;
	memset(&buf, 0, sizeof(STRUCT_STAT64));
	if (FUNC_STAT64W(fn, &buf) < 0) Dz1Error_set(errp, errno);
	else
	{
		(*ret) = buf.st_mtime;
		Dz1Error_set(errp, 0);
	}
	return err;
}
#endif

bool_t Dz1FileA_getTime(struct tm *dstCre, struct tm *dstAcc, struct tm *dstMod, str_t fn, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
#ifdef UNIX_SYSTEM
	int fd = open(fn, 0);
	if (fd < 0) ERR_SET_OUT(errp, errno);
	else
	{
		struct stat  st_buf;
		pthread_cleanup_push(_open_cancel, (void *)&fd);

		memset(&st_buf, 0, sizeof(struct stat));
		if (fstat(fd, &st_buf) < 0) ERR_SET_OUT(errp, errno);
		else if (_unix_stat_getTime(dstCre, dstAcc, dstMod, &st_buf, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (_open_cancel, (void *)&fd);
	}
#else
	HANDLE f = CreateFileA(fn, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (f == INVALID_HANDLE_VALUE) ERR_SET_OUT(errp, GetLastError());
	else
	{
		pthread_cleanup_push(_CreateFileCancel, (void *)&f);
		if (_Dz1File_getTime(f, dstCre, dstAcc, dstMod, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (_CreateFileCancel, (void *)&f);
	}
#endif
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1FileA_getTime2(struct tm *dstCre, struct tm *dstAcc, struct tm *dstMod, str_t path, str_t name_ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	char fn[4096];
	if (_Dz1FileNameA_concatPathName(fn, ARR_VAR_SIZE(char, fn), path, name_ext, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1FileA_getTime(dstCre, dstAcc, dstMod, fn, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1FileA_getTime3(struct tm *dstCre, struct tm *dstAcc, struct tm *dstMod, str_t path, str_t name, str_t ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	char fn[4096];
	if (_Dz1FileNameA_concatPathNameExt(fn, ARR_VAR_SIZE(char, fn), path, name, ext, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1FileA_getTime(dstCre, dstAcc, dstMod, fn, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

#ifndef UNIX_SYSTEM
bool_t Dz1FileW_getTime(struct tm *dstCre, struct tm *dstAcc, struct tm *dstMod, wstr_t fn, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	HANDLE f = INVALID_HANDLE_VALUE;
	if (dstCre == NULL && dstAcc == NULL && dstMod == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (Dz1Str_isVoid(fn) == TRUE) ERR_SET_OUT(errp, EINVAL);
	else if ((f = CreateFileW(fn, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE) ERR_SET_OUT(errp, GetLastError());
	else
	{
		pthread_cleanup_push(_CreateFileCancel, (void *)&f);
		if (_Dz1File_getTime(f, dstCre, dstAcc, dstMod, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (_CreateFileCancel, (void *)&f);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1FileW_getTime2(struct tm *dstCre, struct tm *dstAcc, struct tm *dstMod, wstr_t path, wstr_t name_ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	wchar_t fn[4096];
	if (_Dz1FileNameW_concatPathName(fn, ARR_VAR_SIZE(wchar_t, fn), path, name_ext, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1FileW_getTime(dstCre, dstAcc, dstMod, fn, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1FileW_getTime3(struct tm *dstCre, struct tm *dstAcc, struct tm *dstMod, wstr_t path, wstr_t name, wstr_t ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);

	wchar_t fn[4096];
	if (_Dz1FileNameW_concatPathNameExt(fn, ARR_VAR_SIZE(wchar_t, fn), path, name, ext, errp) == FALSE) ERR_OUT(errp);
	else if (Dz1FileW_getTime(dstCre, dstAcc, dstMod, fn, errp) == FALSE) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}
#endif

Dz1Error Dz1FileA_touch(str_t fn)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (utime(fn, NULL) < 0) ERR_SET_OUT(errp, errno);
	else Dz1Error_set(errp, 0);
	return err;
}

Dz1Error Dz1FileA_touch2(str_t path, str_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	char fn[4096];
	if ((*errp = Dz1FileNameA_concatPathName(fn, ARR_VAR_SIZE(char, fn), path, name)).code) ERR_OUT(errp);
	else if ((*errp = Dz1FileA_touch(fn)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1FileW_touch(wstr_t fn)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (_wutime(fn, NULL) < 0) ERR_SET_OUT(errp, errno);
	else Dz1Error_set(errp, 0);
	return err;
}

Dz1Error Dz1FileW_touch2(wstr_t path, wstr_t name)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	wchar_t fn[4096];
	if ((*errp = Dz1FileNameW_concatPathName(fn, ARR_VAR_SIZE(wchar_t, fn), path, name)).code) ERR_OUT(errp);
	else if ((*errp = Dz1FileW_touch(fn)).code) ERR_OUT(errp);
	else Dz1Error_set(errp, 0);
	return err;
}
#endif
// File Operation Helper Functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// FILE Stream Helper
static s64_t _fget_size(FILE *fp, Dz1Error *errp)
{
	s64_t ret = -1;
	FILEPOSt cur_pos = 0, last_pos = 0;
	cur_pos = DZ1_FTELL(fp);
	if (DZ1_FSEEK(fp, 0, SEEK_END) < 0) ERR_SET_OUT(errp, errno);
	else if ((last_pos = DZ1_FTELL(fp)) < 0) ERR_SET_OUT(errp, errno);
	else if (DZ1_FSEEK(fp, cur_pos, SEEK_SET) < 0) ERR_SET_OUT(errp, errno);
	else ret = (last_pos - cur_pos);
	return ret;
}
// FILE Stream Helper
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO Text File Helper Function
#define CHAR_SET_MBS			0
#define CHAR_SET_UTF8			1
#define CHAR_SET_UTF16BE		2
#define CHAR_SET_UTF16LE		3
#define CHAR_SET_UTF32BE		4
#define CHAR_SET_UTF32LE		5

#if 0
static str_t char_set_name[] = {
	"EUC-KR",
	"UTF-8",
	"UTF-16BE",
	"UTF-16LE",
	"UTF-32BE",
	"UTF-32LE",
	NULL
};

static Dz1Error _check_bom(FILE *fp, int *ret_char_set)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	FILEPOSt rollback_pos = 0;
	u8_t b = 0;
	if (fread(&b, sizeof(u8_t), 1, fp) != 1) (*ret_char_set) = 0;
	else if (b == 0xEF)
	{	// UTF8 = 0xEF, 0xBB, 0xBF
		if (fread(&b, sizeof(u8_t), 1, fp) != 1 || b != 0xBB)		{ DZ1_FSEEK(fp, rollback_pos, SEEK_SET); (*ret_char_set) = CHAR_SET_MBS; }
		else if (fread(&b, sizeof(u8_t), 1, fp) != 1 || b != 0xBF)	{ DZ1_FSEEK(fp, rollback_pos, SEEK_SET); (*ret_char_set) = CHAR_SET_MBS; }
		else (*ret_char_set) = CHAR_SET_UTF8;
	}
	else if (b == 0xFE)
	{	// UTF-16BE = 0xFE, 0xFF
		if (fread(&b, sizeof(u8_t), 1, fp) != 1 || b != 0xFF)		{ DZ1_FSEEK(fp, rollback_pos, SEEK_SET); (*ret_char_set) = CHAR_SET_MBS; }
		else (*ret_char_set) = CHAR_SET_UTF16BE;
	}
	else if (b == 0xFF)
	{	// UTF-16LE || UTF-32LE
		if (fread(&b, sizeof(u8_t), 1, fp) != 1 || b != 0xFE)		{ DZ1_FSEEK(fp, rollback_pos, SEEK_SET); (*ret_char_set) = CHAR_SET_MBS; }
		else
		{	// UTF-32LE = 0xFF 0xFE 0x00 0x00
			(*ret_char_set) = CHAR_SET_UTF16LE;
			rollback_pos = DZ1_FTELL(fp);

			if (fread(&b, sizeof(u8_t), 1, fp) != 1 || b != 0x00)		DZ1_FSEEK(fp, rollback_pos, SEEK_SET);
			else if (fread(&b, sizeof(u8_t), 1, fp) != 1 || b != 0x00)	DZ1_FSEEK(fp, rollback_pos, SEEK_SET);
			else (*ret_char_set) = CHAR_SET_UTF32LE;
		}
	}
	else if (b == 0x00)
	{	// UTF32-BE = 0x00 0x00 0xFE 0xFF
		if (fread(&b, sizeof(u8_t), 1, fp) != 1 || b != 0x00)		{ DZ1_FSEEK(fp, rollback_pos, SEEK_SET); (*ret_char_set) = CHAR_SET_MBS; }
		else if (fread(&b, sizeof(u8_t), 1, fp) != 1 || b != 0xFE)	{ DZ1_FSEEK(fp, rollback_pos, SEEK_SET); (*ret_char_set) = CHAR_SET_MBS; }
		else if (fread(&b, sizeof(u8_t), 1, fp) != 1 || b != 0xFF)	{ DZ1_FSEEK(fp, rollback_pos, SEEK_SET); (*ret_char_set) = CHAR_SET_MBS; }
	}
	else
	{
		DZ1_FSEEK(fp, rollback_pos, SEEK_SET);
		(*ret_char_set) = CHAR_SET_MBS;
		Dz1Error_set(errp, 0);
	}

	return err;
}
#endif

static u8_t *_text_load(FILE *fp, u32_t *ret_size, int letter_size, Dz1Error *errp)
{
	u8_t *ret = NULL;
	s64_t fsize = 0;

//	int ret_char_set = 0;

	(*ret_size = 0);

	if (0) { }
	else if ((fsize = _fget_size(fp, errp)) < 0) ERR_OUT(errp);
//	else if ((*errp = _check_bom(fp, &ret_char_set)).code) ERR_OUT(errp);
	else if (fsize > 1024 * 1024 * 256) ERR_SET_OUT(errp, E2BIG);	// 256MB가 넘는 TXT파일은 로드 사양
	else if ((ret = (u8_t *)Dz1Calloc((u32_t)(fsize + 4), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1StrA_delAndSetNull, (void *)&ret);

		if (fread(ret, sizeof(char), (size_t)fsize, fp) != (size_t)fsize) ERR_SET_OUT(errp, EFAULT);
		else
		{
			(*ret_size) = (u32_t)(fsize);
			Dz1Error_set(errp, 0);
		}

		pthread_cleanup_pop(errp->code); // (Dz1Str_delAndSetNull, (void *)&ret);
	}
	return ret;
}

str_t Dz1TextFileA_load0(char *fn, u32_t *_retSize, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	u32_t __retSize = 0, *retSize = _retSize ? _retSize : &__retSize;
	str_t ret = NULL;
	FILE *fp = NULL;
	
	if (Dz1Str_isVoid(fn))
	{
		ERR_SET_OUT(errp, EINVAL);
	}
	else if ((fp = Dz1FileStreamA_open(fn, "rb", errp)) == NULL) Dz1Error_set(errp, errno);
	else
	{
		//long sz = 0;
		(*retSize) = 0;
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

		if ((ret = (str_t)_text_load(fp, retSize, 1, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return ret;
}

str_t Dz1TextFileA_load(char *fn, Dz1Error *err)
{
	u32_t size = 0;
	return Dz1TextFileA_load0(fn, &size, err);
}

str_t Dz1TextFileA_load2(str_t path, str_t name, Dz1Error *err)
{
	str_t ret = NULL;
	char fn[4096];
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if ((*errp = Dz1FileNameA_concatPathName(fn, ARR_VAR_SIZE(char, fn), path, name)).code) ERR_OUT(errp);
	else if ((ret = Dz1TextFileA_load(fn, errp)) == NULL) { }
	return ret;
}

str_t Dz1TextFileA_load3(str_t path, str_t name, str_t ext, Dz1Error *err)
{
	str_t ret = NULL;
	char fn[4096];
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if ((*errp = Dz1FileNameA_concatPathNameExt(fn, ARR_VAR_SIZE(char, fn), path, name, ext)).code) ERR_OUT(errp);
	else if ((ret = Dz1TextFileA_load(fn, errp)) == NULL) { }
	return ret;
}

#ifndef UNIX_SYSTEM
wstr_t Dz1TextFileW_load0(wstr_t fn, u32_t *_retSize, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	wstr_t ret = NULL;
	u32_t __retSize = 0, *retSize = _retSize ? _retSize : &__retSize;
	FILE *fp = Dz1FileStreamW_open(fn, L"rb", errp);
	if (fp == NULL) Dz1Error_set(errp, errno);
	else
	{
		//long sz = 0;
		(*retSize = 0);
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

		if ((ret = (wstr_t)_text_load(fp, retSize, 2, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return ret;
}
wstr_t Dz1TextFileW_load(wstr_t fn, Dz1Error *err)
{
	u32_t size = 0;
	return Dz1TextFileW_load0(fn, &size, err);
}

wstr_t Dz1TextFileW_load2(wstr_t path, wstr_t name, Dz1Error *err)
{
	wstr_t ret = NULL;
	wchar_t fn[4096];
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if ((*errp = Dz1FileNameW_concatPathName(fn, ARR_VAR_SIZE(wchar_t, fn), path, name)).code) ERR_OUT(errp);
	else if ((ret = Dz1TextFileW_load(fn, errp)) == NULL) { }
	return ret;
}

wstr_t Dz1TextFileW_load3(wstr_t path, wstr_t name, wstr_t ext, Dz1Error *err)
{
	wstr_t ret = NULL;
	wchar_t fn[4096];
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if ((*errp = Dz1FileNameW_concatPathNameExt(fn, ARR_VAR_SIZE(wchar_t, fn), path, name, ext)).code) ERR_OUT(errp);
	else if ((ret = Dz1TextFileW_load(fn, errp)) == NULL) { }
	return ret;
}
#endif

str_t Dz1TextFileA_ixload(str_t path[], u32_t cnt, str_t name_ext, str_t *selected_path, Dz1Error *errp)
{
	str_t ret = NULL;
	u32_t i;
	Dz1Error_set(errp, 0);
	for (i = 0; i < cnt; i++)
	{
		if ((ret = Dz1TextFileA_load2(path[i], name_ext, errp)) != NULL)
		{
			ERR_SET_RET(errp, 0, ret);
			if (selected_path != NULL) *selected_path = path[i];
		}
	}
	Dz1Error_set(errp, ENOENT);
	return NULL;
}

#ifndef UNIX_SYSTEM
wstr_t Dz1TextFileW_ixload(wstr_t path[], u32_t cnt, wstr_t name_ext, wstr_t *selected_path, Dz1Error *errp)
{
	wstr_t ret = NULL;
	u32_t i;
	Dz1Error_set(errp, 0);
	for (i = 0; i < cnt; i++)
	{
		if ((ret = Dz1TextFileW_load2(path[i], name_ext, errp)) != NULL) 
		{
			ERR_SET_RET(errp, 0, ret);
			if (selected_path != NULL) *selected_path = path[i];
		}
	}
	Dz1Error_set(errp, ENOENT);
	return NULL;
}
#endif

str_t Dz1TextFileA_ixload2(str_t path[], u32_t cnt, str_t name, str_t ext, str_t *selected_path, Dz1Error *errp)
{
	str_t ret = NULL;
	u32_t i;
	Dz1Error_set(errp, 0);
	for (i = 0; i < cnt; i++)
	{
		if ((ret = Dz1TextFileA_load3(path[i], name, ext, errp)) != NULL)
		{
			ERR_SET_RET(errp, 0, ret);
			if (selected_path != NULL) *selected_path = path[i];
		}
	}
	Dz1Error_set(errp, ENOENT);
	return NULL;
}

#ifndef UNIX_SYSTEM
wstr_t Dz1TextFileW_ixload2(wstr_t path[], u32_t cnt, wstr_t name, wstr_t ext, wstr_t *selected_path, Dz1Error *errp)
{
	wstr_t ret = NULL;
	u32_t i;
	Dz1Error_set(errp, 0);
	for (i = 0; i < cnt; i++)
	{
		if ((ret = Dz1TextFileW_load3(path[i], name, ext, errp)) != NULL) 
		{
			ERR_SET_RET(errp, 0, ret);
			if (selected_path != NULL) *selected_path = path[i];
		}
	}
	Dz1Error_set(errp, ENOENT);
	return NULL;
}
#endif

// STDIO Text File Helper Function
///////////////////////////////////////////////////////////////////////////////

static str_t _Dz1StrA_load0(Dz1Binary *bin, Dz1Error *errp)
{
	str_t text = NULL;

	u8_t bom_ucs2be[] = { 0xFE, 0xFF };
	u8_t bom_ucs2le[] = { 0xFF, 0xFE };
	u8_t bom_utf8[] = { 0xEF, 0xBB, 0xBF };
	if (memcmp(bin->data, bom_ucs2le, sizeof(bom_ucs2le)) == 0)
	{	// UCS-2LE
		if ((text = (str_t)Dz1String_conv(bin->data + sizeof(bom_ucs2le), bin->size - sizeof(bom_ucs2le), "UCS-2LE", DZ1_SYSTEM_MBCS_CHARSET, NULL)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (memcmp(bin->data, bom_ucs2be, sizeof(bom_ucs2be)) == 0)
	{	// UCS-2BE
		if ((text = (str_t)Dz1String_conv(bin->data + sizeof(bom_ucs2be), bin->size - sizeof(bom_ucs2be), "UCS-2BE", DZ1_SYSTEM_MBCS_CHARSET, NULL)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (memcmp(bin->data, bom_utf8, sizeof(bom_utf8)) == 0)
	{	// UTF-8
		if ((text = (str_t)Dz1String_conv(bin->data + sizeof(bom_utf8), bin->size - sizeof(bom_utf8), "UTF-8", DZ1_SYSTEM_MBCS_CHARSET, NULL)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		size_t len = bin->size;
		if ((text = (str_t)Dz1Calloc(sizeof(char), len + 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			memcpy(text, bin->data, bin->size);
			Dz1Error_set(errp, 0);
		}
	}
	return text;
}

str_t Dz1StrA_loadFromFile(str_t fn, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t text = NULL;
	Dz1Binary *bin = NULL;
	if (Dz1Str_isVoid(fn)) ERR_SET_OUT(errp, EINVAL);
	else if ((bin = Dz1BinFileA_load(fn, errp)) == NULL) 
	{
		if (errp->code != ENOENT) ERR_OUT(errp);
	}
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((text = _Dz1StrA_load0(bin, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return text;
}

str_t Dz1StrA_loadFromFile2(str_t path, str_t name_ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t text = NULL;
	Dz1Binary *bin = NULL;
	if (Dz1Str_isVoid(name_ext)) ERR_SET_OUT(errp, EINVAL);
	else if ((bin = Dz1BinFileA_load2(path, name_ext, errp)) == NULL) 
	{
		if (errp->code != ENOENT) ERR_OUT(errp);
	}
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((text = _Dz1StrA_load0(bin, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return text;
}

str_t Dz1StrA_loadFromFile3(str_t path, str_t name, str_t ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	str_t text = NULL;
	Dz1Binary *bin = NULL;
	if (Dz1Str_isVoid(name) || Dz1Str_isVoid(ext)) ERR_SET_OUT(errp, EINVAL);
	else if ((bin = Dz1BinFileA_load3(path, name, ext, errp)) == NULL) 
	{
		if (errp->code != ENOENT) ERR_OUT(errp);
	}
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((text = _Dz1StrA_load0(bin, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return text;
}

#ifndef UNIX_SYSTEM
static wstr_t _Dz1StrW_load0(Dz1Binary *bin, Dz1Error *errp)
{
	wstr_t text = NULL;

	u8_t bom_ucs2be[] = { 0xFE, 0xFF };
	u8_t bom_ucs2le[] = { 0xFF, 0xFE };
	u8_t bom_utf8[] = { 0xEF, 0xBB, 0xBF };
	if (memcmp(bin->data, bom_ucs2le, sizeof(bom_ucs2le)) == 0)
	{	// UCS-2LE
		if ((text = (wstr_t)Dz1String_conv(bin->data + sizeof(bom_ucs2le), bin->size - sizeof(bom_ucs2le), "UCS-2LE", DZ1_SYSTEM_WIDE_CHARSET, NULL)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (memcmp(bin->data, bom_ucs2be, sizeof(bom_ucs2be)) == 0)
	{	// UCS-2BE
		if ((text = (wstr_t)Dz1String_conv(bin->data + sizeof(bom_ucs2be), bin->size - sizeof(bom_ucs2be), "UCS-2BE", DZ1_SYSTEM_WIDE_CHARSET, NULL)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else if (memcmp(bin->data, bom_utf8, sizeof(bom_utf8)) == 0)
	{	// UTF-8
		if ((text = (wstr_t)Dz1String_conv(bin->data + sizeof(bom_utf8), bin->size - sizeof(bom_utf8), "UTF-8", DZ1_SYSTEM_WIDE_CHARSET, NULL)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else
	{
		size_t len = bin->size / sizeof(wchar_t) + ((bin->size % sizeof(wchar_t)) ? 1 : 0);
		if ((text = (wstr_t)Dz1Calloc(sizeof(wchar_t), len + 1, errp)) == NULL) ERR_OUT(errp);
		else
		{
			memcpy(text, bin->data, bin->size);
			Dz1Error_set(errp, 0);
		}
	}
	return text;
}

wstr_t Dz1StrW_loadFromFile(wstr_t fn, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t text = NULL;
	Dz1Binary *bin = NULL;
	if (Dz1Str_isVoid(fn)) ERR_SET_OUT(errp, EINVAL);
	else if ((bin = Dz1BinFileW_load(fn, errp)) == NULL) 
	{
		if (errp->code != ENOENT) ERR_OUT(errp);
	}
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((text = _Dz1StrW_load0(bin, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return text;
}

wstr_t Dz1StrW_loadFromFile2(wstr_t path, wstr_t name_ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t text = NULL;
	Dz1Binary *bin = NULL;
	if (Dz1Str_isVoid(name_ext)) ERR_SET_OUT(errp, EINVAL);
	else if ((bin = Dz1BinFileW_load2(path, name_ext, errp)) == NULL) 
	{
		if (errp->code != ENOENT) ERR_OUT(errp);
	}
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((text = _Dz1StrW_load0(bin, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return text;
}

wstr_t Dz1StrW_loadFromFile3(wstr_t path, wstr_t name, wstr_t ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	wstr_t text = NULL;
	Dz1Binary *bin = NULL;
	if (Dz1Str_isVoid(name) || Dz1Str_isVoid(ext)) ERR_SET_OUT(errp, EINVAL);
	else if ((bin = Dz1BinFileW_load3(path, name, ext, errp)) == NULL) 
	{
		if (errp->code != ENOENT) ERR_OUT(errp);
	}
	else
	{
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&bin);
		if ((text = _Dz1StrW_load0(bin, errp)) == NULL) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(1); // (Dz1Binary_delAndSetNull, (void *)&bin);
	}
	return text;
}
#endif

static bool_t Dz1StrA_saveToFile0(FILE *fp, str_t str, Dz1Error *errp)
{
	ssize_t sz = 0, len = (ssize_t)strlen(str);
	if (0) { }
#ifndef UNIX_SYSTEM
	// No BOM
#else	// UNIX_SYSTEM
	else if (fwrite(DZ1_UNICODE_BOM_UTF8, sizeof(u8_t), DZ1_UNICODE_BOM_UTF8_LEN, fp) != DZ1_UNICODE_BOM_UTF8_LEN) ERR_SET_OUT(errp, EPIPE);
#endif	// UNIX_SYSTEM
	else if ((sz = (ssize_t)fwrite(str, sizeof(char), len, fp)) != len) ERR_SET_OUT(errp, EPIPE);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1StrA_saveToFile(str_t fn, str_t str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *fp = NULL;
	if (Dz1Str_isVoid(fn)) ERR_SET_OUT(errp, EINVAL);
	else if ((fp = Dz1FileStreamA_open(fn, "wb", errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);

		if (Dz1StrA_saveToFile0(fp, str, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1StrA_saveToFile2(str_t path, str_t name_ext, str_t str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *fp = NULL;
	if (Dz1Str_isVoid(name_ext)) ERR_SET_OUT(errp, EINVAL);
	else if ((fp = Dz1FileStreamA_open2(path, name_ext, Dz1T("wb"), errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);

		if (Dz1StrA_saveToFile0(fp, str, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1StrA_saveToFile3(Dz1Str path, str_t name, str_t ext, str_t str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *fp = NULL;
	if (Dz1Str_isVoid(name) || Dz1Str_isVoid(ext)) ERR_SET_OUT(errp, EINVAL);
	else if ((fp = Dz1FileStreamA_open3(path, name, ext, Dz1T("wb"), errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);

		if (Dz1StrA_saveToFile0(fp, str, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#ifndef UNIX_SYSTEM
static bool_t Dz1StrW_saveToFile0(FILE *fp, wstr_t str, Dz1Error *errp)
{
	ssize_t sz = 0, len = (ssize_t)wcslen(str);
	if (0) { }
#if DZ1_ENDIAN == DZ1_ENDIAN_BIG
	else if ((sz = fwrite(DZ1_UNICODE_BOM_UCS2BE, sizeof(u8_t), DZ1_UNICODE_BOM_UCS2_LEN, fp)) != DZ1_UNICODE_BOM_UCS2_LEN) ERR_SET_OUT(errp, EPIPE);
#elif DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
	else if ((sz = (ssize_t)fwrite(DZ1_UNICODE_BOM_UCS2LE, sizeof(u8_t), DZ1_UNICODE_BOM_UCS2_LEN, fp)) != DZ1_UNICODE_BOM_UCS2_LEN) ERR_SET_OUT(errp, EPIPE);
#else
#error "No ENDIAN"
#endif
	else if ((sz = (ssize_t)fwrite(str, sizeof(wchar_t), len, fp)) != len) ERR_SET_OUT(errp, EPIPE);
	else Dz1Error_set(errp, 0);
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1StrW_saveToFile(wstr_t fn, wstr_t str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *fp = NULL;
	if (Dz1Str_isVoid(fn)) ERR_SET_OUT(errp, EINVAL);
	else if ((fp = Dz1FileStreamW_open(fn, L"wb", errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);

		if (Dz1StrW_saveToFile0(fp, str, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1StrW_saveToFile2(wstr_t path, wstr_t name_ext, wstr_t str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *fp = NULL;
	if (Dz1Str_isVoid(name_ext)) ERR_SET_OUT(errp, EINVAL);
	else if ((fp = Dz1FileStreamW_open2(path, name_ext, L"wb", errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);

		if (Dz1StrW_saveToFile0(fp, str, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

bool_t Dz1StrW_saveToFile3(wstr_t path, wstr_t name, wstr_t ext, wstr_t str, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *fp = NULL;
	if (Dz1Str_isVoid(name) || Dz1Str_isVoid(ext)) ERR_SET_OUT(errp, EINVAL);
	else if ((fp = Dz1FileStreamW_open3(path, name, ext, L"wb", errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1FileStream_closeAndSetNull, (void *)&fp);

		if (Dz1StrW_saveToFile0(fp, str, errp) == FALSE) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(1); // (Dz1FileStream_closeAndSetNull, (void *)&fp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#endif
///////////////////////////////////////////////////////////////////////////////
// STDIO Binary File Helper Function
Dz1Binary *Dz1BinFile_loadf(FILE *fp, u64_t size, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	Dz1Binary *ret = Dz1Binary_new(NULL, 0, errp);
	if (ret == NULL) ERR_OUT(errp);
	else
	{
		s64_t sz = (s64_t)size;
		pthread_cleanup_push(Dz1Binary_delAndSetNull, (void *)&ret);

		if (size == (u64_t)-1 && (sz = _fget_size(fp, errp)) < 0) ERR_OUT(errp);
		else if ((ret->data = (u8_t *)Dz1Calloc(sizeof(u8_t), (ret->size = (u32_t)sz), errp)) == NULL) ERR_OUT(errp);
		else if (fread(ret->data, sizeof(u8_t), ret->size, fp) != ret->size) ERR_SET_OUT(errp, EFAULT);
		else Dz1Error_set(errp, 0);

		pthread_cleanup_pop(errp->code); // (Dz1Binary_delAndSetNull, (void *)&ret);
	}
	return ret;
}

Dz1Error Dz1BinFile_savef(Dz1Binary *bin, FILE *fp)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (bin == NULL || fp == NULL) ERR_SET_OUT(errp, EINVAL);
	else
	{
		ssize_t size = 0;
		if ((size = (ssize_t)fwrite(bin->data, sizeof(u8_t), bin->size, fp)) < 0)
		{
			if (feof(fp)) ERR_SET_OUT(&err, EPIPE);
			else ERR_SET_OUT(&err, ferror(fp));
		}
		else if (size != (ssize_t)bin->size) ERR_SET_OUT(&err, EFAULT);
	}
	return err;
}

Dz1Binary *Dz1BinFileA_load(str_t fn, Dz1Error *err)
{
	Dz1Binary *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	FILE *fp = NULL;
	if ((fp = Dz1FileStreamA_open(fn, "rb", errp)) == NULL) { }
	else
	{
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

		if ((ret = Dz1BinFile_loadf(fp, -1, errp)) == NULL) ERR_OUT(errp);

		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
Dz1Binary *Dz1BinFileW_load(wstr_t fn, Dz1Error *err)
{
	Dz1Binary *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	FILE *fp = NULL;
	if ((fp = Dz1FileStreamW_open(fn, L"rb", errp)) == NULL) { }
	else
	{
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

		if ((ret = Dz1BinFile_loadf(fp, -1, errp)) == NULL) ERR_OUT(errp);

		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return ret;
}
#endif

Dz1Binary *Dz1BinFileA_load2(str_t path, str_t name_ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1Binary *ret = NULL;
	char fn[4096];

	if ((*errp = Dz1FileNameA_mkFullName(fn, ARR_VAR_SIZE(char, fn), path, name_ext)).code) ERR_OUT(errp);
	else if ((ret = Dz1BinFileA_load(fn, errp)) == NULL) { }

	return ret;
}

#ifndef UNIX_SYSTEM
Dz1Binary *Dz1BinFileW_load2(wstr_t path, wstr_t name_ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1Binary *ret = NULL;
	wchar_t fn[4096];

	if ((*errp = Dz1FileNameW_mkFullName(fn, ARR_VAR_SIZE(wchar_t, fn), path, name_ext)).code) ERR_OUT(errp);
	else if ((ret = Dz1BinFileW_load(fn, errp)) == NULL)
	{
		if (errp->code != ENOENT) ERR_OUT(errp);
	}

	return ret;
}
#endif

Dz1Binary *Dz1BinFileA_load3(str_t path, str_t name, str_t ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1Binary *ret = NULL;
	char fn[4096];

	if ((*errp = Dz1FileNameA_concatPathNameExt(fn, ARR_VAR_SIZE(char, fn), path, name, ext)).code) ERR_OUT(errp);
	else if ((ret = Dz1BinFileA_load(fn, errp)) == NULL) { }

	return ret;
}

#ifndef UNIX_SYSTEM
Dz1Binary *Dz1BinFileW_load3(wstr_t path, wstr_t name, wstr_t ext, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1Binary *ret = NULL;
	wchar_t fn[4096];

	if ((*errp = Dz1FileNameW_concatPathNameExt(fn, ARR_VAR_SIZE(wchar_t, fn), path, name, ext)).code) ERR_OUT(errp);
	else if ((ret = Dz1BinFileW_load(fn, errp)) == NULL)
	{
		if (errp->code != ENOENT) ERR_OUT(errp);
	}

	return ret;
}
#endif

Dz1Binary *Dz1BinFileA_iload(str_t path[], u32_t cnt, str_t name_ext, Dz1Error *errp)
{
	Dz1Binary *ret = NULL;
	u32_t i;
	for (i = 0; i < cnt; i++)
	{
		if ((ret = Dz1BinFileA_load2(path[i], name_ext, errp)) != NULL) 
		{
			Dz1Error_set(errp, 0);
			return ret;
		}
		else Dz1Error_set(errp, 0);
	}
	if (ret == NULL && errp->code == 0)
	{
		ERR_SET_OUT(errp, ENOENT);
	}
	return NULL;
}

#ifndef UNIX_SYSTEM
Dz1Binary *Dz1BinFileW_iload(wstr_t path[], u32_t cnt, wstr_t name_ext, Dz1Error *errp)
{
	Dz1Binary *ret = NULL;
	u32_t i;
	for (i = 0; i < cnt; i++)
	{
		if ((ret = Dz1BinFileW_load2(path[i], name_ext, errp)) != NULL) 
		{
			Dz1Error_set(errp, 0);
			return ret;
		}
		else Dz1Error_set(errp, 0);
	}
	if (ret == NULL && errp->code == 0) ERR_SET_OUT(errp, ENOENT);
	return NULL;
}
#endif

Dz1Binary *Dz1BinFileA_iload2(str_t path[], u32_t cnt, str_t name, str_t ext, Dz1Error *errp)
{
	Dz1Binary *ret = NULL;
	u32_t i;
	for (i = 0; i < cnt; i++)
	{
		if ((ret = Dz1BinFileA_load3(path[i], name ,ext, errp)) != NULL) 
		{
			Dz1Error_set(errp, 0);
			return ret;
		}
		else Dz1Error_set(errp, 0);
	}
	if (ret == NULL && errp->code == 0) ERR_SET_OUT(errp, ENOENT);
	return NULL;
}

#ifndef UNIX_SYSTEM
Dz1Binary *Dz1BinFileW_iload2(wstr_t path[], u32_t cnt, wstr_t name, wstr_t ext, Dz1Error *errp)
{
	Dz1Binary *ret = NULL;
	u32_t i;
	for (i = 0; i < cnt; i++)
	{
		if ((ret = Dz1BinFileW_load3(path[i], name, ext, errp)) != NULL) 
		{
			Dz1Error_set(errp, 0);
			return ret;
		}
		else Dz1Error_set(errp, 0);
	}
	if (ret == NULL && errp->code == 0) ERR_SET_OUT(errp, ENOENT);
	return NULL;
}
#endif

Dz1Binary *Dz1BinFileA_read(str_t fn, size_t sz, Dz1Error *err)
{
	Dz1Binary *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	FILE *fp = NULL;
	if ((fp = Dz1FileStreamA_open(fn, "rb", errp)) == NULL) { }
	else
	{
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

		if ((ret = Dz1BinFile_loadf(fp, sz, errp)) == NULL) ERR_OUT(errp);

		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
Dz1Binary *Dz1BinFileW_read(wstr_t fn, size_t sz, Dz1Error *err)
{
	Dz1Binary *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	FILE *fp = NULL;
	if ((fp = Dz1FileStreamW_open(fn, L"rb", errp)) == NULL) { }
	else
	{
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);

		if ((ret = Dz1BinFile_loadf(fp, sz, errp)) == NULL) ERR_OUT(errp);

		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return ret;
}
#endif

Dz1Binary *Dz1BinFileA_read2(str_t path, str_t name, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1Binary *ret = NULL;
	char fn[4096];

	if ((*errp = Dz1FileNameA_mkFullName(fn, ARR_VAR_SIZE(char, fn), path, name)).code) ERR_OUT(errp);
	else if ((ret = Dz1BinFileA_read(fn, sz, errp)) == NULL) { }

	return ret;
}

#ifndef UNIX_SYSTEM
Dz1Binary *Dz1BinFileW_read2(wstr_t path, wstr_t name, size_t sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	Dz1Binary *ret = NULL;
	wchar_t fn[4096];

	if ((*errp = Dz1FileNameW_mkFullName(fn, ARR_VAR_SIZE(wchar_t, fn), path, name)).code) ERR_OUT(errp);
	else if ((ret = Dz1BinFileW_read(fn, sz, errp)) == NULL) { }

	return ret;
}
#endif

Dz1Error Dz1BinFileA_save(char *fn, Dz1Binary *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	FILE *fp = Dz1FileStreamA_open(fn, "wb", errp);
	if (fp == NULL) { }
	else
	{
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);
		if ((*errp = Dz1BinFile_savef(src, fp)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1BinFileW_save(wstr_t fn, Dz1Binary *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	FILE *fp = Dz1FileStreamW_open(fn, L"wb", errp);
	if (fp == NULL) { }
	else
	{
		//ssize_t size = 0;
		pthread_cleanup_push(Dz1FileStream_cancel, (void *)fp);
		if ((*errp = Dz1BinFile_savef(src, fp)).code) ERR_OUT(errp);
		pthread_cleanup_pop(1); // (Dz1FileStream_cancel, (void *)fp);
	}
	return err;
}
#endif

Dz1Error Dz1BinFileA_save2(char *path, char *name, Dz1Binary *src)
{
	char fn[4096];
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1FileNameA_concatPathName(fn, ARR_VAR_SIZE(char, fn), path, name)).code) ERR_OUT(errp);
	else if ((err = Dz1BinFileA_save(fn, src)).code) ERR_OUT(&err);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1BinFileW_save2(wstr_t path, wstr_t name, Dz1Binary *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	wchar_t fn[4096];
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((*errp = Dz1FileNameW_mkFullName(fn, ARR_VAR_SIZE(wchar_t, fn), path, name)).code) ERR_OUT(errp);
	else if ((err = Dz1BinFileW_save(fn, src)).code) ERR_OUT(&err);
	return err;
}
#endif

Dz1Error Dz1BinFileA_save3(char *path, char *name, char *ext, Dz1Binary *src)
{
	char fn[4096];
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (src == NULL) ERR_SET_OUT(errp, EINVAL);
	else if ((*errp = Dz1FileNameA_concatPathNameExt(fn, ARR_VAR_SIZE(char, fn), path, name, ext)).code) ERR_OUT(errp);
	else if ((err = Dz1BinFileA_save(fn, src)).code) ERR_OUT(&err);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1BinFileW_save3(wstr_t path, wstr_t name, wstr_t ext, Dz1Binary *src)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	wchar_t fn[4096];
	if (src == NULL) ERR_SET_OUT(&err, EINVAL);
	else if ((*errp = Dz1FileNameW_concatPathNameExt(fn, ARR_VAR_SIZE(wchar_t, fn), path, name, ext)).code) ERR_OUT(errp);
	else if ((err = Dz1BinFileW_save(fn, src)).code) ERR_OUT(&err);
	return err;
}
#endif
// STDIO Binary File Helper Function
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// STDIO File Descriptor
//DZ1_CPPLINK DZ1_DLLPORT Dz1FileDescr Dz1FileDescr_open();
// STDIO File Descriptor
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// File Stream
// typedef struct Dz1FileStreamGetSizeCancelArg
// {
// 	FILE *fp;
// 	long pos;
// } Dz1FileStreamGetSizeCancelArg;
// 
// static void Dz1FileStream_getSizeCancel(void *ptr)
// {
// 	Dz1FileStreamGetSizeCancelArg *arg = (Dz1FileStreamGetSizeCancelArg *)ptr;
// 	fseek(arg->fp, arg->pos, SEEK_SET);
// }

ssize_t Dz1FileStream_getSize(FILE *fp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ssize_t ret = -1;
	s64_t sz = _fget_size(fp, errp);
	if (sz < 0) ERR_OUT(errp);
	else
	{
		ret = (ssize_t)sz;
		Dz1Error_set(errp, 0);
	}
// 	long pos = ftell(fp);
// 	if (pos == -1L) ERR_SET_OUT(errp, EFAULT);
// 	else if (fseek(fp, 0, SEEK_END) != 0) ERR_SET_OUT(errp, EFAULT);
// 	else
// 	{
// 		Dz1FileStreamGetSizeCancelArg arg = { fp, pos };
// 		pthread_cleanup_push(Dz1FileStream_getSizeCancel, (void *)&arg);
// 		if ((ret = ftell(fp)) == -1L) ERR_SET_OUT(errp, EFAULT);
// 		else Dz1Error_set(errp, 0);
// 		pthread_cleanup_pop(1); // (Dz1FileStream_getSizeCancel, (void *)&arg);
// 	}
	return ret;
}

#ifdef UNIX_SYSTEM
static bool_t Dz1FileStream_textBOM_UTF8(FILE *fp, Dz1Error *errp)
{
	u8_t bom[3] = { 0xFF, 0xBB, 0xBF };
	fwrite(bom, sizeof(u8_t), 3, fp);
	Dz1Error_set(errp, 0);
	return TRUE;
}
#else
static bool_t Dz1FileStream_textBOM_UCS16(FILE *fp, Dz1Error *errp)
{
#if DZ1_ENDIAN == DZ1_ENDIAN_LITTLE
	u8_t bom[2] = { 0xFF, 0xFE };
#else 
	u8_t bom[2] = { 0xFE, 0xFF };
#endif
	fwrite(bom, sizeof(u8_t), 2, fp);
	Dz1Error_set(errp, 0);
	return TRUE;
}
#endif
bool_t Dz1FileStream_textBOM(FILE *fp, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	Dz1ConsoleMode mode = dz1DefCon_getMode();
	switch(mode)
	{
#ifdef UNIX_SYSTEM
	case Dz1ConsoleMode_mbcs: return Dz1FileStream_textBOM_UTF8(fp, errp);
	default: return TRUE;
#else
	default: return TRUE;
	case Dz1ConsoleMode_mbcs: return TRUE;
	case Dz1ConsoleMode_wide: return Dz1FileStream_textBOM_UCS16(fp, errp);
#endif
	}
}

FILE *Dz1FileStreamA_open(str_t fn, const char *attr, Dz1Error *err)
{
	FILE *fp = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (fn == NULL || fn[0] == 0 || attr == NULL || attr[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
#ifndef UNIX_SYSTEM
		if (Dz1PathA_isAbsPath(fn))
		{
			char temp[4096];
			sprintf(temp, DIR_SEPRATOR DIR_SEPRATOR "?" DIR_SEPRATOR "%s", fn);
			fp = fopen(temp, attr);
		}
		else fp = fopen(fn, attr);
#else
		fp = fopen(fn, attr);
#endif
		if (fp == NULL)
		{
			Dz1Error_set(errp, errno);
			if (errp->code != ENOENT)
			{
				Dz1ThreadA_printf("%s : ", fn);
				ERR_OUT(errp);
			}
		}
	}
	return fp;
}

#ifndef UNIX_SYSTEM
FILE *Dz1FileStreamW_open(wstr_t fn, const wchar_t *attr, Dz1Error *err)
{
	FILE *fp = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	if (fn == NULL || fn[0] == 0 || attr == NULL || attr[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		if (Dz1PathW_isAbsPath(fn))
		{
			wchar_t temp[4096];
			_mkLongAbsPathNameW(temp, fn);
			fp = _wfopen(temp, attr);
		}
		else fp = _wfopen(fn, attr);

		if (fp == NULL)
		{
			Dz1Error_set(errp, errno);
			if (errp->code != ENOENT)
			{
				Dz1ThreadW_printf(L"%s : ", fn);
				ERR_OUT(errp);
			}
		}
	}
	return fp;
}
#endif

FILE *Dz1FileStreamA_open2(str_t path, str_t name, const char *attr, Dz1Error *err)
{
	FILE *fp = NULL;
	char fn[4096];
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((*errp = Dz1FileNameA_concatPathName(fn, ARR_VAR_SIZE(char, fn), path, name)).code) ERR_OUT(errp);
	else if ((fp = Dz1FileStreamA_open(fn, attr, errp)) == NULL) { }
	return fp;
}

#ifndef UNIX_SYSTEM
FILE *Dz1FileStreamW_open2(wstr_t path, wstr_t name, const wchar_t *attr, Dz1Error *err)
{
	FILE *fp = NULL;
	wchar_t fn[4096];
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((*errp = Dz1FileNameW_concatPathName(fn, ARR_VAR_SIZE(wchar_t, fn), path, name)).code) ERR_OUT(errp);
	else if ((fp = Dz1FileStreamW_open(fn, attr, errp)) == NULL) { }
	return fp;
}
#endif

FILE *Dz1FileStreamA_open3(str_t path, str_t name, str_t ext, const char *attr, Dz1Error *err)
{
	FILE *fp = NULL;
	char fn[4096];
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((*errp = Dz1FileNameA_concatPathNameExt(fn, ARR_VAR_SIZE(char, fn), path, name, ext)).code) ERR_OUT(errp);
	else if ((fp = Dz1FileStreamA_open(fn, attr, errp)) == NULL) { }
	return fp;
}

#ifndef UNIX_SYSTEM
FILE *Dz1FileStreamW_open3(wstr_t path, wstr_t name, wstr_t ext, const wchar_t *attr, Dz1Error *err)
{
	FILE *fp = NULL;
	wchar_t fn[4096];
	DZ1_ERROR_SAFE_PTR(errp, err);
	if ((*errp = Dz1FileNameW_concatPathNameExt(fn, ARR_VAR_SIZE(wchar_t, fn), path, name, ext)).code) ERR_OUT(errp);
	else if ((fp = Dz1FileStreamW_open(fn, attr, errp)) == NULL) { }
	return fp;
}
#endif

FILE *Dz1FileStreamA_iopen(str_t path[], u32_t cnt, str_t name_ext, const char *attr, str_t *selected, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *ret = NULL;
	u32_t i;
	for (i = 0; i < cnt; i++)
	{
		if ((ret = Dz1FileStreamA_open2(path[i], name_ext, attr, errp)) != NULL)
		{
			if (selected) *selected = path[i];
			return ret;
		}
		else Dz1Error_set(errp, 0);
	}
	if (ret == NULL && errp->code == 0) ERR_SET_OUT(errp, ENOENT);
	return NULL;
}

#ifndef UNIX_SYSTEM
FILE *Dz1FileStreamW_iopen(wstr_t path[], u32_t cnt, wstr_t name_ext, const wchar_t *attr, wstr_t *selected, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *ret = NULL;
	u32_t i;
	for (i = 0; i < cnt; i++)
	{
		if ((ret = Dz1FileStreamW_open2(path[i], name_ext, attr, errp)) != NULL)
		{
			if (selected) *selected = path[i];
			return ret;
		}
		else Dz1Error_set(errp, 0);
	}
	if (ret == NULL && errp->code == 0) ERR_SET_OUT(errp, ENOENT);
	return NULL;
}
#endif

FILE *Dz1FileStreamA_iopen2(str_t path[], u32_t cnt, str_t name, str_t ext, const char *attr, str_t *selected, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *ret = NULL;
	u32_t i;
	for (i = 0; i < cnt; i++)
	{
		if ((ret = Dz1FileStreamA_open3(path[i], name, ext, attr, errp)) != NULL)
		{
			if (selected) *selected = path[i];
			return ret;
		}
		else Dz1Error_set(errp, 0);
	}
	if (ret == NULL && errp->code == 0) ERR_SET_OUT(errp, ENOENT);
	return NULL;
}

#ifndef UNIX_SYSTEM
FILE *Dz1FileStreamW_iopen2(wstr_t path[], u32_t cnt, wstr_t name, wstr_t ext, const wchar_t *attr, wstr_t *selected, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	FILE *ret = NULL;
	u32_t i;
	for (i = 0; i < cnt; i++)
	{
		if ((ret = Dz1FileStreamW_open3(path[i], name, ext, attr, errp)) != NULL)
		{
			if (selected) *selected = path[i];
			return ret;
		}
		else Dz1Error_set(errp, 0);
	}
	if (ret == NULL && errp->code == 0) ERR_SET_OUT(errp, ENOENT);
	return NULL;
}
#endif
// File Stream
///////////////////////////////////////////////////////////////////////////////
#define WILDCARD_W		L"*"

#ifndef UNIX_SYSTEM
#	ifdef __BORLANDC__
#		define STRUCT_FINDDATA_A			struct _finddata_t
#		define STRUCT_FINDDATA_W			struct _wfinddata_t
#		define FIND_FIRST_A					_findfirst
#		define FIND_FIRST_W					__wfindfirst
#		define FIND_NEXT_A					_findnext
#		define FIND_NEXT_W					__wfindnext
#	else // __BORLANDC__
#		if _MSC_VER >= 1400
#			define STRUCT_FINDDATA_A		struct __finddata64_t
#			define STRUCT_FINDDATA_W		struct _wfinddata64_t
#			define FIND_FIRST_A				_findfirst64
#			define FIND_NEXT_A				_findnext64
#			define FIND_FIRST_W				_wfindfirst64
#			define FIND_NEXT_W				_wfindnext64
#		else // _MSC_VER >= 1400
#			define STRUCT_FINDDATA_A		struct _finddata_t
#			define STRUCT_FINDDATA_W		struct _wfinddata_t
#			define FIND_FIRST_A				_findfirst
#			define FIND_NEXT_A				_findnext
#			define FIND_FIRST_W				_wfindfirst
#			define FIND_NEXT_W				_wfindnext
#		endif // _MSC_VER >= 1400
#	endif // __BORLANDC__
#else
#endif

///////////////////////////////////////////////////////////////////////////////
// STDIO Directory Operation Helper Functions
Dz1Error Dz1DirA_delete(str_t fn)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
#ifndef UNIX_SYSTEM
	if (Dz1PathA_isAbsPath(fn))
	{
		char temp[4096];
		_mkLongAbsPathNameA(temp, fn);
		if (rmdir(temp) != 0) Dz1Error_set(errp, errno);
	}
	else
	{
		if (rmdir(fn) != 0) Dz1Error_set(errp, errno);
	}
#else
	if (rmdir(fn) != 0) Dz1Error_set(errp, errno);
#endif
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1DirW_delete(wstr_t fn)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (Dz1PathW_isAbsPath(fn))
	{
		wchar_t temp[4096];
		_mkLongAbsPathNameW(temp, fn);
		if (_wrmdir(temp) != 0) Dz1Error_set(errp, errno);
	}
	else
	{
		if (_wrmdir(fn) != 0) Dz1Error_set(errp, errno);
	}
	return err;
}
#endif

Dz1Error Dz1DirA_delete2(str_t path, str_t name)
{
	char fn[4096];
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1FileNameA_concatPathName(fn, ARR_VAR_SIZE(char, fn), path, name)).code) ERR_OUT(errp);
	else if ((*errp = Dz1DirA_delete(fn)).code) { }
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1DirW_delete2(wstr_t path, wstr_t name)
{
	wchar_t fn[4096];
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1FileNameW_concatPathName(fn, ARR_VAR_SIZE(wchar_t, fn), path, name)).code) ERR_OUT(errp);
	else if ((*errp = Dz1DirW_delete(fn)).code) { }
	return err;
}
#endif

Dz1Error Dz1DirA_flush(str_t path)
{
	size_t i;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	Dz1DirCatalogA *files = NULL, *subDirs = NULL;
	if ((files = Dz1DirCatalogA_newFiles(path, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1DirCatalog_delAndSetNull, (void *)&files);
		for (i = 0; i < files->valid; i++) Dz1FileA_delete2(path, files->entries[i].name);
		pthread_cleanup_pop(1); // (Dz1DirCatalog_delAndSetNull, (void *)&files);
	}

	if ((subDirs = Dz1DirCatalogA_newSubDir(path, &err)) == NULL) ERR_OUT(&err);
	else
	{
		char subPath[4096] = { 0, };
		
		pthread_cleanup_push(Dz1DirCatalog_delAndSetNull, (void *)&subDirs);
		for (i = 0; i < subDirs->valid; i++)
		{
			sprintf(subPath, "%s" DIR_SEPRATOR "%s", path, subDirs->entries[i].name);

			if ((err = Dz1DirA_flush(subPath)).code) ERR_OUT(&err);
			else Dz1DirA_delete2(path, subDirs->entries[i].name);
		}
		pthread_cleanup_pop(1); // (Dz1DirCatalog_delAndSetNull, (void *)&subDirs);
	}
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1DirW_flush(wstr_t path)
{
	size_t i;
	DZ1_ERROR_SAFE_VAR(errp, err);

	Dz1DirCatalogW *files = NULL, *subDirs = NULL;
	if ((files = Dz1DirCatalogW_newFiles(path, &err)) == NULL) ERR_OUT(&err);
	else
	{
		pthread_cleanup_push(Dz1DirCatalog_delAndSetNull, (void *)&files);
		for (i = 0; i < files->valid; i++) Dz1FileW_delete2(path, files->entries[i].name);
		pthread_cleanup_pop(1); // (Dz1DirCatalog_delAndSetNull, (void *)&files);
	}

	if ((subDirs = Dz1DirCatalogW_newSubDir(path, &err)) == NULL) ERR_OUT(&err);
	else
	{
		wchar_t subPath[4096] = { 0, };
		
		pthread_cleanup_push(Dz1DirCatalog_delAndSetNull, (void *)&subDirs);
		for (i = 0; i < subDirs->valid; i++)
		{
			if ((*errp = Dz1FileNameW_concatPathName(subPath, ARR_VAR_SIZE(wchar_t, subPath), path, subDirs->entries[i].name)).code) ERR_OUT(errp);
			else if ((*errp = Dz1DirW_flush(subPath)).code) ERR_OUT(errp);
			else Dz1DirW_delete2(path, subDirs->entries[i].name);
		}
		pthread_cleanup_pop(1); // (Dz1DirCatalog_delAndSetNull, (void *)&subDirs);
	}
	return err;
}
#endif

Dz1Error Dz1DirA_flush2(str_t basePath, str_t dirName)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	char path[4096];
	if ((*errp = Dz1FileNameA_concatPathName(path, ARR_VAR_SIZE(char, path), basePath, dirName)).code) ERR_OUT(errp);
	else if ((*errp = Dz1DirA_flush(path)).code) ERR_OUT(errp);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1DirW_flush2(wstr_t basePath, wstr_t dirName)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	wchar_t path[4096];
	if ((*errp = Dz1FileNameW_concatPathName(path, ARR_VAR_SIZE(wchar_t, path), basePath, dirName)).code) ERR_OUT(errp);
	else if ((*errp = Dz1DirW_flush(path)).code) ERR_OUT(errp);
	return err;
}
#endif

Dz1Error Dz1DirA_mkDir(str_t targetPath)
{
	char *cp = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (targetPath == NULL || targetPath[0] == 0) ERR_SET_OUT(&err, EINVAL);
	else
	{
		//printf("Dz1Dir_mkDir() : Path = [%s]\n", targetPath);

		if ((cp = strchr(targetPath, ':')) != NULL) cp++; // if (targetPath == "C:\\") cp = "\\";
		else cp = targetPath;

		if (*cp != 0)
		{
			struct stat st;
			if (stat(targetPath, &st) < 0)
			{
				Dz1Error_set(&err, errno);
				if (err.code == ENOENT)
				{	// mkdir
#ifdef UNIX_SYSTEM
					mode_t mode = S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IXOTH;
					if (mkdir(targetPath, mode) < 0) ERR_SET_OUT(&err, errno);
#else
					if (mkdir(targetPath) < 0) Dz1Error_set(&err, errno);
#endif
					else Dz1Error_set(&err, 0);
				}
			}
#ifdef UNIX_SYSTEM
			else if (S_ISDIR(st.st_mode))
#else
			else if (st.st_mode & _S_IFDIR)
#endif
			{
				Dz1Error_set(&err, 0);
				//Dz1ThreadA_printf("Dz1Dir_mkDir() : Path \"%s\" is File\n", targetPath);
			}
			else Dz1Error_set(&err, EEXIST);
		}
	}
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1DirW_mkDir(wstr_t targetPath)
{
	wchar_t *cp = NULL;
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (Dz1Str_isVoid(targetPath) == TRUE) Dz1Error_set(&err, EINVAL);
	else
	{
		//printf("Dz1Dir_mkDir() : Path = [%s]\n", targetPath);

		if ((cp = wcschr(targetPath, L':')) != NULL) cp++; // if (targetPath == "C:\\") cp = "\\";
		else cp = targetPath;

		if (cp[0] != 0)
		{
			STRUCT_STAT64 st;
			if (FUNC_STAT64W(targetPath, &st) < 0)
			{
				Dz1Error_set(&err, errno);
				if (err.code == ENOENT)
				{	// mkdir
					if (_wmkdir(targetPath) < 0) Dz1Error_set(&err, errno);
					else Dz1Error_set(&err, 0);
				}
			}
			else if (st.st_mode & _S_IFDIR)
			{
				Dz1Error_set(&err, 0);
				//Dz1ThreadW_printf("Dz1Dir_mkDir() : Path \"%s\" is File\n", targetPath);
			}
			else Dz1Error_set(&err, EEXIST);
		}
	}
	return err;
}
#endif

static u32_t getNumOfSepratorA(str_t src)
{
	u32_t ret = 0;
	char *cp = src;
	while(*cp != '\0')
	{
		if (*cp == DIR_SEP) ret++;
		cp++;
	}
	return ret;
}

#ifndef UNIX_SYSTEM
static u32_t getNumOfSepratorW(wstr_t src)
{
	u32_t ret = 0;
	wchar_t *cp = src;
	while(*cp != 0)
	{
		if (*cp == DIR_SEP_W) ret++;
		cp++;
	}
	return ret;
}
#endif

Dz1Error Dz1DirA_mkDirNested(str_t targetPath)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	u32_t words = 0;
	str_t *arr = NULL, *ap = NULL;
	char temp[4096] = { 0, }, *cp = temp + strlen(targetPath) - 1, buf[4096] = { 0, };

	strcpy(temp, targetPath);

	// Trim last Directory Separator
	if (*cp == DIR_SEP) *cp-- = '\0';

	cp = temp;

	words = getNumOfSepratorA(temp) + 1;

	if ((ap = arr = (str_t *)Dz1Malloc(sizeof(str_t) * words, &err)) == NULL) { }
	else
	{
		u32_t i;
		char pathLast;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);

		*ap++ = temp;

		while ((cp = strchr(cp, DIR_SEP)) != NULL)
		{
			*cp++ = '\0';
			*ap++ = cp;
		}

		for (i = 0; err.code == 0 && i < words; i++)
		{
			strcat(buf, arr[i]);
			pathLast = buf[strlen(buf)-1];
			if (pathLast == ':') { }
			else if (strcmp(arr[i], ".") == 0 || strcmp(arr[i], "..") == 0) { }
			else if ((err = Dz1DirA_mkDir(buf)).code) { }
			strcat(buf, DIR_SEPRATOR);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1DirW_mkDirNested(wstr_t targetPath)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	u32_t words = 0;
	wstr_t *arr = NULL, *ap = NULL;
	wchar_t temp[4096] = { 0, }, *cp = temp + wcslen(targetPath) - 1, buf[4096] = { 0, };

	wcscpy(temp, targetPath);

	// Trim last Directory Separator
	if (*cp == DIR_SEP_W) *cp-- = 0;

	cp = temp;

	words = getNumOfSepratorW(temp) + 1;

	if ((ap = arr = (wstr_t *)Dz1Malloc(sizeof(wstr_t) * words, &err)) == NULL) { }
	else
	{
		u32_t i;
		wchar_t pathLast;
		pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);

		*ap++ = temp;

		while ((cp = wcschr(cp, DIR_SEP_W)) != NULL)
		{
			*cp++ = 0;
			*ap++ = cp;
		}

		for (i = 0; err.code == 0 && i < words; i++)
		{
			wcscat(buf, arr[i]);
			pathLast = buf[wcslen(buf) - 1];
			if (pathLast == L':') { }
			else if (wcscmp(arr[i], L".") == 0 || wcscmp(arr[i], L"..") == 0) { }
			else if ((err = Dz1DirW_mkDir(buf)).code) { }
			wcscat(buf, DIR_SEPRATOR_W);
		}
		pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
	}
	return err;
}
#endif

ssize_t Dz1DirA_pwd(char *buf, size_t buf_cnt, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
#ifndef UNIX_SYSTEM
	ret = GetCurrentDirectoryA((DWORD)buf_cnt, buf);
	if (ret == 0) { ERR_SET_OUT(errp, errno); ret = -1; }
	else if (ret > (ssize_t)buf_cnt) { ERR_SET_OUT(errp, ENOMEM); ret = -ret; }
#else
	if (getcwd(buf, buf_cnt) == NULL) { ERR_SET_OUT(errp, errno); ret = -1; }
	else { buf[buf_cnt - 1] = 0; ret = strlen(buf); }
#endif
	return ret;
}

#ifndef UNIX_SYSTEM
ssize_t Dz1DirW_pwd(wchar_t *buf, size_t buf_cnt, Dz1Error *err)
{
	ssize_t ret = 0;
	DZ1_ERROR_SAFE_DECLARE(errp, err);
	ret = GetCurrentDirectoryW((DWORD)buf_cnt, buf);
	if (ret == 0) { ERR_SET_OUT(errp, errno); }
	else if (ret > (ssize_t)buf_cnt) { ERR_SET_OUT(errp, ENOMEM); ret = -ret; }
	return ret;
}
#endif

Dz1Error Dz1DirA_chdir(str_t path)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
#ifndef UNIX_SYSTEM
	if (SetCurrentDirectory(path) == FALSE) ERR_SET_OUT(errp, GetLastError());
#else
	if (chdir(path) < 0) ERR_SET_OUT(errp, errno);
#endif
	else Dz1Error_set(errp, 0);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1DirW_chdir(wstr_t path)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER, *errp = &err;
	if (SetCurrentDirectoryW(path) == FALSE) ERR_SET_OUT(errp, GetLastError());
	else Dz1Error_set(errp, 0);
	return err;
}
#endif

#ifndef UNIX_SYSTEM
static __inline__ bool_t _isDriveNameA(str_t path, size_t len)
{
	if (len == 2 && path[1] == ':')
	{	// 길이가 2자고 2번째 문자가 콜론이면 확실함!!!
		return TRUE;
	}
	else
	{
		char *sp = path;
		if (path[0] == DIR_SEP_A && path[1] == DIR_SEP_A)
		{	// 첫 두 글자가 "\\"			\\servername\sharename
			sp += 2;					//	  servername\sharename
			if ((sp = strchr(sp, DIR_SEP_A)) != NULL)
			{							//				\sharename
				sp++;					//				 sharename
				if (strchr(sp, DIR_SEP_A) == NULL)
				{	// 확실히 공유 폴더의 이름이다.
					return TRUE;
				}
				else
				{	// 찾아졌다는 말은 sharename\... 이고, 이 함수가 들어오기 전에 맨끝 \는 삭제하기 때문에...
					return FALSE;
				}
			}
			else
			{	// 더이상 \\가 찾아지지 않는다. -> \\servername 인 경우 : 요곤 서버네임임으로 드라이브 네임처럼 시간값을 얻지 못함
				return TRUE;
			}
		}
		else
		{	// 첫 두글자가 아니면 상대경로...
			return FALSE;
		}
	}
}

static __inline__ bool_t _isDriveNameW(wstr_t path, size_t len)
{
	if (len == 2 && path[1] == L':')
	{	// 길이가 2자고 2번째 문자가 콜론이면 확실함!!!
		return TRUE;
	}
	else
	{
		//wchar_t *endp = path + len, *sp = path;
		wchar_t *sp = path;
		if (path[0] == DIR_SEP_W && path[1] == DIR_SEP_W)
		{	// 첫 두 글자가 "\\"			\\servername\sharename
			sp += 2;					//	  servername\sharename
			if ((sp = wcschr(sp, DIR_SEP_W)) != NULL)
			{							//				\sharename
				sp++;					//				 sharename
				if (wcschr(sp, DIR_SEP_W) == NULL)
				{	// 확실히 공유 폴더의 이름이다.
					return TRUE;
				}
				else
				{	// 찾아졌다는 말은 sharename\... 이고, 이 함수가 들어오기 전에 맨끝 \는 삭제하기 때문에...
					return FALSE;
				}
			}
			else
			{	// 더이상 \\가 찾아지지 않는다. -> \\servername 인 경우 : 요곤 서버네임임으로 드라이브 네임처럼 시간값을 얻지 못함
				return TRUE;
			}
		}
		else
		{	// 첫 두글자가 아니면 상대경로...
			return FALSE;
		}
	}
}
#endif

#define DRIVE_TIME_IS_CURRENT
time_t Dz1DirA_time(str_t path, Dz1Error *err)
{
	time_t ret = -1;
	DZ1_ERROR_SAFE_PTR(errp, err);
#ifdef UNIX_SYSTEM
	struct stat buf;
	if (path == NULL || path[0] == 0) { }
	else if (stat((char *)path, &buf) == 0)
	{
		if (buf.st_mode & S_IFDIR)
		{
			ret = (time_t)buf.st_mtim.tv_sec;
		}
		else ERR_SET_OUT(errp, EINVAL);
	}
	else ERR_SET_OUT(errp, errno);
#else
	size_t len;
	if (path == NULL || (len = strlen(path)) == 0) { }
	else
	{
		char _path[4096];

		strcpy(_path, path); 
		if (_path[len - 1] == DIR_SEP_W) { _path[len - 1] = 0; len--; }

		if (_isDriveNameA(_path, len))
		{
#ifdef DRIVE_TIME_IS_CURRENT
			ret = time(NULL);
#else
			ret = 0;
#endif
			Dz1Error_set(errp, 0);
		}
		else
		{
			STRUCT_STAT64 buf;
			if (Dz1PathA_isAbsPath(path))
			{
				_mkLongAbsPathNameA(_path, path);
				len = strlen(_path);
			}
			else strcpy(_path, path);

			if (FUNC_STAT64A(_path, &buf) != 0)
			{
				Dz1Error_set(errp, errno);
				if (Dz1DirA_isExist(_path) == TRUE)
				{
					Dz1Error_set(errp, 0);
					ret = 0;
				}
				else
				{
					ERR_OUT(errp);
				}
			}
			else if ((buf.st_mode & _S_IFDIR ) == 0) ERR_SET_OUT(errp, EINVAL);
			else
			{
				ret = buf.st_mtime;
				Dz1Error_set(errp, 0);
			}
		}
	}
#endif
	return ret;
}

#ifndef UNIX_SYSTEM
time_t Dz1DirW_time(wstr_t path, Dz1Error *err)
{
	time_t ret = -1;
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t len;
	if (path == NULL || (len = wcslen(path)) == 0) { }
	else
	{
		wchar_t _path[4096];

		wcscpy(_path, path); 
		if (_path[len - 1] == DIR_SEP_W) { _path[len - 1] = 0; len--; }

		if (_isDriveNameW(_path, len))
		{
#ifdef DRIVE_TIME_IS_CURRENT
			ret = time(NULL);
#else
			ret = 0;
#endif
			Dz1Error_set(errp, 0);
		}
		else
		{
			STRUCT_STAT64 buf;
			if (Dz1PathW_isAbsPath(path))
			{
				_mkLongAbsPathNameW(_path, path);
				len = wcslen(_path);
			}
			else wcscpy(_path, path);

			if (FUNC_STAT64W(_path, &buf) != 0)
			{
				Dz1Error_set(errp, errno);
				if (Dz1DirW_isExist(_path) == TRUE)
				{
					Dz1Error_set(errp, 0);
					ret = 0;
				}
				else
				{
					ERR_OUT(errp);
				}
			}
			else if ((buf.st_mode & _S_IFDIR ) == 0) ERR_SET_OUT(errp, EINVAL);
			else
			{
				ret = buf.st_mtime;
				Dz1Error_set(errp, 0);
			}
		}
	}
	return ret;
}
#endif

bool_t Dz1DirA_isExist(str_t path)
{
	bool_t ret = FALSE;
#ifdef UNIX_SYSTEM
	struct stat buf;
	if (path == NULL || path[0] == 0) { }
	else if (stat((char *)path, &buf) == 0)
	{
		if (buf.st_mode & S_IFDIR) ret = TRUE;
	}
#else
	size_t len;
	if (path == NULL || (len = strlen(path)) == 0) { }
	else
	{
		intptr_t h;
		STRUCT_FINDDATA_A data;
		char _path[4096];
		if (Dz1PathA_isAbsPath(path))
		{
			_mkLongAbsPathNameA(_path, path);
			len = strlen(_path);
		}
		else strcpy(_path, path);

		if (_path[len - 1] != DIR_SEP_A) strcat(_path, DIR_SEPRATOR_A);
		strcat(_path, "*");

		if ((h = FIND_FIRST_A(_path, &data)) != -1)
		{
			ret = TRUE;
			_findclose(h);
		}
	}
#endif
	return ret;
}

#ifndef UNIX_SYSTEM
bool_t Dz1DirW_isExist(wstr_t path)
{
	bool_t ret = FALSE;
	size_t len;
	if (path == NULL || (len = wcslen(path)) == 0) { }
	else
	{
		intptr_t h;
		STRUCT_FINDDATA_W data;
		wchar_t _path[4096];
		if (Dz1PathW_isAbsPath(path))
		{
			_mkLongAbsPathNameW(_path, path);
			len = wcslen(_path);
		}
		else wcscpy(_path, path);

		if (_path[len - 1] != DIR_SEP_W) wcscat(_path, DIR_SEPRATOR_W);
		wcscat(_path, WILDCARD_W);

		if ((h = FIND_FIRST_W(_path, &data)) != -1)
		{
			ret = TRUE;
			_findclose(h);
		}
	}
	return ret;
}
#endif

bool_t Dz1DirA_isExist2(str_t base_path, str_t dir_name)
{
	bool_t ret = FALSE;
	char temp[4096];
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1FileNameA_concatPathName(temp, ARR_VAR_SIZE(char, temp), base_path, dir_name)).code) ERR_OUT(errp);
	else ret = Dz1DirA_isExist(temp);
	return ret;
}

#ifndef UNIX_SYSTEM
bool_t Dz1DirW_isExist2(wstr_t base_path, wstr_t dir_name)
{
	bool_t ret = FALSE;
	wchar_t temp[4096];
	DZ1_ERROR_SAFE_VAR(errp, err);
	if ((*errp = Dz1FileNameW_concatPathName(temp, ARR_VAR_SIZE(wchar_t, temp), base_path, dir_name)).code) ERR_OUT(errp);
	else ret = Dz1DirW_isExist(temp);
	return ret;
}
#endif
// STDIO Directory Operation Helper Functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// DIR Catalog
typedef enum Dz1DirCatalogCount
{
	Dz1DirCatalogCount_file,
	Dz1DirCatalogCount_dir,
	Dz1DirCatalogCount_both
} Dz1DirCatalogCount;

#ifndef UNIX_SYSTEM
static bool_t _chkAndMkAbsPathA(char dst[4096], str_t src, str_t spec, Dz1Error *err)
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || src[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		char last = src[strlen(src) - 1];
		if (0) { }
		else if (Dz1PathA_isAbsPath(src)) _mkLongAbsPathNameA(dst, src);
		else if (_isNetPathNameA(src)) strcpy(dst, src);
		else if (_isLocalPathNameA(src)) strcpy(dst, src);
		else return FALSE;

		if (last != DIR_SEP_A) strcat(dst, DIR_SEPRATOR_A);

		if (spec == NULL || spec[0] == 0) strcat(dst, "*");
		else strcat(dst, spec);

		ret = TRUE;
	}
	return ret;
}

static bool_t _chkAndMkAbsPathW(wchar_t dst[4096], wstr_t src, wstr_t spec, Dz1Error *err)
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_PTR(errp, err);
	if (src == NULL || src[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		wchar_t last = src[wcslen(src) -1];

		if (0) { }
		else if (Dz1PathW_isAbsPath(src)) _mkLongAbsPathNameW(dst, src);
		else if (_isNetPathNameW(src)) wcscpy(dst, src);
		else if (_isLocalPathNameW(src)) wcscpy(dst, src);
		else return FALSE;

		if (last != DIR_SEP_W) wcscat(dst, DIR_SEPRATOR_W);

		if (spec == NULL || spec[0] == 0) wcscat(dst, WILDCARD_W);
		else wcscat(dst, spec);

		ret = TRUE;
	}
	return ret;
}


static void __findclose(void *ptr)
{
	intptr_t *h = (intptr_t *)ptr;
	_findclose(*h);
}

static int getDirEntryCountA(str_t _path, str_t spec, Dz1DirCatalogCount flag, Dz1Error *errp)
{
	intptr_t h;
	STRUCT_FINDDATA_A data;

	char path[4096] = { 0, };
	if (_chkAndMkAbsPathA(path, _path, spec, errp) == FALSE) ERR_OUT_RET(errp, -1);
	else if ((h = FIND_FIRST_A(path, &data)) == -1)
	{
		Dz1Error_set(errp, errno);
		if (errp->code == ENOENT) { Dz1Error_set(errp, 0); return 0; }
		else if (errp->code == EINVAL) { Dz1Error_set(errp, 0); return 0; }
		else ERR_OUT_RET(errp, -1);
	}
	else
	{
		int ret = 0;
		pthread_cleanup_push(__findclose, (void *)&h);

		do
		{
			if (data.attrib & _A_SUBDIR)
			{	// dir entry
				if (flag != Dz1DirCatalogCount_file) ret++;	// dir || both
			}
			else
			{	// file entry
				if (flag != Dz1DirCatalogCount_dir) ret++;	// file || both
			}
		} while(FIND_NEXT_A(h, &data) == 0);

		pthread_cleanup_pop(1); // (__findclose, (void *)&h);
		return ret;
	}
	return -1;
}

static int getDirEntryCountW(wchar_t *_path, wchar_t *spec, Dz1DirCatalogCount flag, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	int ret = 0;

	intptr_t h;
	STRUCT_FINDDATA_W data;

	wchar_t path[4096] = { 0, };
	if (_chkAndMkAbsPathW(path, _path, spec, errp) == FALSE) ERR_OUT_RET(errp, -1);
	else if ((h = FIND_FIRST_W(path, &data)) == -1)
	{
		Dz1Error_set(errp, errno);
		if (errp->code == ENOENT) { Dz1Error_set(errp, 0); return 0; }
		else if (errp->code == EINVAL) { Dz1Error_set(errp, 0); return 0; }
		else ERR_OUT_RET(errp, -1);
	}
	else
	{
		int ret = 0;
		pthread_cleanup_push(__findclose, (void *)&h);

		do
		{
			if (data.attrib & _A_SUBDIR)
			{	// dir entry
				if (flag != Dz1DirCatalogCount_file) ret++;	// dir || both
			}
			else
			{	// file entry
				if (flag != Dz1DirCatalogCount_dir) ret++;	// file || both
			}
		} while(FIND_NEXT_W(h, &data) == 0);

		pthread_cleanup_pop(1); // (__findclose, (void *)&h);
		return ret;
	}
	return -1;
}

static int getDirEntryFileCountA(str_t _path, str_t spec, Dz1Error *errp) { return getDirEntryCountA(_path, spec, Dz1DirCatalogCount_file, errp); }
static int getDirEntryDirCountA(str_t _path, str_t spec, Dz1Error *errp) { return getDirEntryCountA(_path, spec, Dz1DirCatalogCount_dir, errp); }

// Windows version of fillDirEntry[AW]
static Dz1Error fillDirEntryA(Dz1DirCatalogA *dst, Dz1DirCatalogCount flag)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	intptr_t h;
	STRUCT_FINDDATA_A data;

	char path[4096] = { 0, };
	if (_chkAndMkAbsPathA(path, dst->path, dst->spec, errp) == FALSE) ERR_OUT(errp);
	else if ((h = FIND_FIRST_A(path, &data)) == -1) Dz1Error_set(errp, errno);
	else
	{
		Dz1DirEntryA *p = dst->entries;
		pthread_cleanup_push((Dz1DelFunc)__findclose, (void *)&h);
		do
		{
			if (data.attrib & _A_SUBDIR)
			{	// dir entry
				if (flag != Dz1DirCatalogCount_file)
				{	// dir || both
					if (strcmp(data.name, ".") == 0 || strcmp(data.name, "..") == 0) { }	// exclude "." and ".."
					else
					{
						strcpy(p->name, data.name);
						p->date = data.time_write;
						p->cdate = data.time_create;
						p->size = data.size;
						p++; dst->valid++;
					}
				}
			}
			else
			{	// file entry
				if (flag != Dz1DirCatalogCount_dir)
				{	// file || both
					strcpy(p->name, data.name);
					p->date = data.time_write;
					p->cdate = data.time_create;
					p->size = data.size;
					p++; dst->valid++;
				}
			}
		} while(FIND_NEXT_A(h, &data) == 0);
		pthread_cleanup_pop(1); // ((Dz1DelFunc)__findclose, (void *)&h);
	}
	return err;
}

static Dz1Error fillDirEntryW(Dz1DirCatalogW *dst, Dz1DirCatalogCount flag)
{
	DZ1_ERROR_SAFE_VAR(errp, err);
	intptr_t h;
	STRUCT_FINDDATA_W data;

	wchar_t path[4096] = { 0, };
	if (_chkAndMkAbsPathW(path, dst->path, dst->spec, errp) == FALSE) ERR_OUT(errp);
	else if ((h = FIND_FIRST_W(path, &data)) == -1) ERR_SET_OUT(&err, errno);
	else
	{
		Dz1DirEntryW *p = dst->entries;
		pthread_cleanup_push((Dz1DelFunc)__findclose, (void *)&h);
		do
		{
			if (data.attrib & _A_SUBDIR)
			{	// dir
				if (flag != Dz1DirCatalogCount_file)
				{
					if (wcscmp(data.name, L".") == 0 || wcscmp(data.name, L"..") == 0) { }
					else
					{
						wcscpy(p->name, data.name);
						p->date = data.time_write;
						p->cdate = data.time_create;
						p->size = data.size;
						p++; dst->valid++;
					}
				}
			}
			else
			{
				if (flag != Dz1DirCatalogCount_dir)
				{
					wcscpy(p->name, data.name);
					p->date = data.time_write;
					p->cdate = data.time_create;
					p->size = data.size;
					p++; dst->valid++;
				}
			}
		} while(FIND_NEXT_W(h, &data) == 0);
		pthread_cleanup_pop(1); // ((Dz1DelFunc)__findclose, (void *)&h);
	}
	return err;
}
#else	// UNIX_SYSTEM
#include "dirent.h"
static __inline__ void opendir_cancel(void *ptr)
{
	DIR *dir = (DIR *)ptr;
	closedir(dir);
}

static __inline__ int _isFileA(str_t path, str_t name, Dz1Error *errp)
{
	int ret = -1;
	char fn[4096] = { 0, };
	if (name == NULL || name[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		struct stat s;
		if (path == NULL || path[0] == 0) strcpy(fn, name);
		else sprintf(fn, "%s"DIR_SEPRATOR"%s", path, name);

		if (stat(fn, &s) < 0) ERR_SET_OUT(errp, errno);
		else if (S_ISREG(s.st_mode)) ret = TRUE;
		else ret = FALSE;
	}
	return ret;
}

static __inline__ int _isDirA(str_t path, str_t name, Dz1Error *errp)
{
	int ret = -1;
	char fn[4096] = { 0, };
	if (name == NULL || name[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		struct stat s;
		if (path == NULL || path[0] == 0) strcpy(fn, name);
		else sprintf("%s"DIR_SEPRATOR"%s", path, name);

		if (stat(fn, &s) < 0) ERR_SET_OUT(errp, errno);
		else if (S_ISDIR(s.st_mode)) ret = TRUE;
		else ret = FALSE;
	}
	return ret;
}

static bool_t _takeEntryA(Dz1DirEntryA *dst, str_t path, str_t name, Dz1DirCatalogCount *flag)
{
	bool_t ret = FALSE;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (dst == NULL || flag == NULL) ERR_SET_OUT(errp, EINVAL);
	else if (name == NULL || name[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else
	{
		struct stat s;

		char fn[4096] = { 0, };
		if (path == NULL || path[0] == 0) strcpy(fn, name);
		else sprintf(fn, "%s" DIR_SEPRATOR_A "%s", path, name);

		if (stat(fn, &s) < 0) ERR_SET_OUT(&err, errno);
		else if (S_ISREG(s.st_mode))
		{
			(*flag) = Dz1DirCatalogCount_file;
			strcpy(dst->name, name);
			dst->date = s.st_mtime;
			dst->cdate = s.st_ctime;
			dst->size = s.st_size;
			ret = TRUE;
		}
		else if (S_ISDIR(s.st_mode))
		{
			(*flag) = Dz1DirCatalogCount_dir;
			strcpy(dst->name, name);
			dst->date = s.st_mtime;
			dst->cdate = s.st_ctime;
			dst->size = 0;
			ret = TRUE;
		}
	}
	return ret;
}

// Unix version : DirEntryCount[AW]
static int getDirEntryCountA(str_t _path, str_t spec, Dz1DirCatalogCount flag, Dz1Error *errp)
{
	int cnt = 0;
	char path[4096];
	DIR *dir = NULL;
	
	if (spec != NULL && spec[0] != 0) sprintf(path, "%s" DIR_SEPRATOR "%s", _path, spec);
	else strcpy(path, _path);

	Dz1ThreadA_printf("getDirEntryCountA() : path=[%s]\n", path);

	if ((dir = opendir(path)) == NULL) { ERR_SET_OUT(errp, errno); cnt = -1; }
	else
	{
		int status;
		struct dirent *ent = NULL;
		pthread_cleanup_push(opendir_cancel, (void *)dir);

		while(errp->code == 0 && (ent = readdir(dir)) != NULL)
		{
			status = 0;
			if (flag == Dz1DirCatalogCount_file)
			{
				if ((status = _isFileA(path, ent->d_name, errp)) == TRUE) cnt++;
			}
			else if (flag == Dz1DirCatalogCount_dir)
			{
				if ((status = _isDirA(path, ent->d_name, errp))  == TRUE) cnt++;
			}
		}
		pthread_cleanup_pop(1); // (opendir_cancel, (void *)dir);
	}
	return cnt;
}

static Dz1Error fillDirEntryA(Dz1DirCatalogA *dst, Dz1DirCatalogCount flag)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	DIR *dir = opendir(dst->path);
	if (dir == NULL) ERR_SET_OUT(&err, errno);
	else
	{
		Dz1DirCatalogCount taken;
		struct dirent *ent = NULL;
		Dz1DirEntryA *p = dst->entries;
		pthread_cleanup_push(opendir_cancel, (void *)dir);
		while(err.code == 0 && (ent = readdir(dir)) != NULL)
		{
			taken = -1;
			if (_takeEntryA(p, dst->path, ent->d_name, &taken) && taken == flag) { p++; dst->valid++; }
		}
		pthread_cleanup_pop(1); // (opendir_cancel, (void *)dir);
	}
	return err;
}
#endif // UNIX_SYSTEM
/////////////////////////////////////////////////////////////////////
// Files
Dz1Error Dz1DirCatalogA_updateFiles(Dz1DirCatalogA *ret)
{
	int cnt = 0;
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (ret->path == NULL || ret->path[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret->path_stamp = Dz1DirA_time(ret->path, errp)) == -1) ERR_OUT(errp);
	else if ((cnt = getDirEntryCountA(ret->path, ret->spec, Dz1DirCatalogCount_file, errp)) < 0) { }
	else if ((ret->size = cnt) > 0)
	{ 
		if (ret->entries != NULL) Dz1Memory_freeAndSetNull(&ret->entries);

		if ((ret->entries = (Dz1DirEntryA *)Dz1Malloc(sizeof(Dz1DirEntryA) * cnt, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = fillDirEntryA(ret, Dz1DirCatalogCount_file)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else Dz1Error_set(errp, 0);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1DirCatalogW_updateFiles(Dz1DirCatalogW *ret)
{
	int cnt = 0;
	DZ1_ERROR_SAFE_VAR(errp, err);

	if (ret->path == NULL || ret->path[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret->path_stamp = Dz1DirW_time(ret->path, errp)) == -1) ERR_OUT(errp);
	else if ((cnt = getDirEntryCountW(ret->path, ret->spec, Dz1DirCatalogCount_file, errp)) < 0) { }
	else if ((ret->size = cnt) > 0)
	{ 
		if (ret->entries != NULL) Dz1Memory_freeAndSetNull(&ret->entries);

		if ((ret->entries = (Dz1DirEntryW *)Dz1Malloc(sizeof(Dz1DirEntryW) * cnt, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = fillDirEntryW(ret, Dz1DirCatalogCount_file)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else Dz1Error_set(errp, 0);
	return err;
}
#endif

Dz1DirCatalogA *Dz1DirCatalogA_newFiles(str_t path, Dz1Error *err) 
{ 
	return Dz1DirCatalogA_newFiles2(path, NULL, err);
}

#ifndef UNIX_SYSTEM
Dz1DirCatalogW *Dz1DirCatalogW_newFiles(wstr_t path, Dz1Error *err) 
{ 
	return Dz1DirCatalogW_newFiles2(path, NULL, err); 
}
#endif

Dz1DirCatalogA *Dz1DirCatalogA_newFiles2(str_t path, str_t spec, Dz1Error *err)
{
	//time_t dir_stamp = 0;
	Dz1DirCatalogA *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if (path == NULL || path[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1DirCatalogA *)Dz1Calloc(sizeof(Dz1DirCatalogA), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1DirCatalog_delAndSetNull, (void *)&ret);
		if ((ret->path = Dz1StrA_dup(path, errp)) == NULL) ERR_OUT(errp);
		else if (spec != NULL && spec[0] != 0 && (ret->spec = Dz1StrA_dup(spec, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1DirCatalogA_updateFiles(ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1DirCatalog_delAndSetNull, (void *)&ret);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
Dz1DirCatalogW *Dz1DirCatalogW_newFiles2(wstr_t path, wstr_t spec, Dz1Error *err)
{
	Dz1DirCatalogW *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if (path == NULL || path[0] == 0)
	{
		ERR_SET_OUT(errp, EINVAL);
	}
	else if ((ret = (Dz1DirCatalogW *)Dz1Calloc(sizeof(Dz1DirCatalogW), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1DirCatalogW_delAndSetNull, (void *)&ret);
		if ((ret->path = Dz1StrW_dup(path, errp)) == NULL) ERR_OUT(errp);
		else if (spec != NULL && spec[0] != 0 && (ret->spec = Dz1StrW_dup(spec, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1DirCatalogW_updateFiles(ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1DirCatalogW_delAndSetNull, (void *)&ret);
	}
	return ret;
}
#endif

// Files
/////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
// SubDir
Dz1Error Dz1DirCatalogA_updateSubDir(Dz1DirCatalogA *ret)
{
	int cnt = 0;
	DZ1_ERROR_SAFE_VAR(errp, err);
	if (ret->path == NULL || ret->path[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret->path_stamp = Dz1DirA_time(ret->path, errp)) == -1) ERR_OUT(errp);
	//else if ((cnt = getDirEntryDirCountA(ret->path, ret->spec, errp)) < 0)
	else if ((cnt = getDirEntryCountA(ret->path, ret->spec, Dz1DirCatalogCount_dir, errp)) < 0)
	{
		if (errp->code != EINVAL && errp->code != ENOENT) ERR_OUT(errp);
	}
	else if ((ret->size = cnt) > 0)
	{ 
		ret->valid = 0;
		if (ret->entries != NULL) Dz1Memory_freeAndSetNull(&ret->entries);

		if ((ret->entries = (Dz1DirEntryA *)Dz1Malloc(sizeof(Dz1DirEntryA) * ret->size, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = fillDirEntryA(ret, Dz1DirCatalogCount_dir)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else Dz1Error_set(errp, 0);
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1DirCatalogW_updateSubDir(Dz1DirCatalogW *ret)
{
	DZ1_ERROR_SAFE_VAR(errp, err);

	int cnt = 0;
	if (ret->path == NULL || ret->path[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret->path_stamp = Dz1DirW_time(ret->path, errp)) == -1) ERR_OUT(errp);
	else if ((cnt = getDirEntryCountW(ret->path, ret->spec, Dz1DirCatalogCount_dir, errp)) < 0)
	{
		if (errp->code != EINVAL && errp->code != ENOENT) ERR_OUT(errp);
	}
	else if ((ret->size = cnt) > 0)
	{ 
		ret->valid = 0;
		if (ret->entries != NULL) { Dz1Free(ret->entries); ret->entries = NULL; }

		if ((ret->entries = (Dz1DirEntryW *)Dz1Malloc(sizeof(Dz1DirEntryW) * cnt, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = fillDirEntryW(ret, Dz1DirCatalogCount_dir)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
	}
	else Dz1Error_set(errp, 0);

	return err;
}
#endif

Dz1DirCatalogA *Dz1DirCatalogA_newSubDir(str_t path, Dz1Error *err) 
{ 
	return Dz1DirCatalogA_newSubDir2(path, NULL, err); 
}
#ifndef UNIX_SYSTEM
Dz1DirCatalogW *Dz1DirCatalogW_newSubDir(wstr_t path, Dz1Error *err) 
{ 
	return Dz1DirCatalogW_newSubDir2(path, NULL, err); 
}
#endif

Dz1DirCatalogA *Dz1DirCatalogA_newSubDir2(str_t path, str_t spec, Dz1Error *err)
{
	Dz1DirCatalogA *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if (path == NULL || path[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1DirCatalogA *)Dz1Calloc(sizeof(Dz1DirCatalogA), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1DirCatalog_delAndSetNull, (void *)&ret);
		if ((ret->path = Dz1StrA_dup(path, errp)) == NULL) ERR_OUT(errp);
		else if (spec != NULL && spec[0] != 0 && (ret->spec = Dz1StrA_dup(spec, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1DirCatalogA_updateSubDir(ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1DirCatalog_delAndSetNull, (void *)&ret);
	}
	return ret;
}

#ifndef UNIX_SYSTEM
Dz1DirCatalogW *Dz1DirCatalogW_newSubDir2(wstr_t path, wstr_t spec, Dz1Error *err)
{
	Dz1DirCatalogW *ret = NULL;
	DZ1_ERROR_SAFE_DECLARE(errp, err);

	if (path == NULL || path[0] == 0) ERR_SET_OUT(errp, EINVAL);
	else if ((ret = (Dz1DirCatalogW *)Dz1Calloc(sizeof(Dz1DirCatalogW), 1, errp)) == NULL) ERR_OUT(errp);
	else
	{
		pthread_cleanup_push(Dz1DirCatalogW_delAndSetNull, (void *)&ret);
		if ((ret->path = Dz1StrW_dup(path, errp)) == NULL) ERR_OUT(errp);
		else if (spec != NULL && spec[0] != 0 && (ret->spec = Dz1StrW_dup(spec, errp)) == NULL) ERR_OUT(errp);
		else if ((*errp = Dz1DirCatalogW_updateSubDir(ret)).code) ERR_OUT(errp);
		else Dz1Error_set(errp, 0);
		pthread_cleanup_pop(errp->code); // (Dz1DirCatalog_delAndSetNull, (void *)&ret);
	}
	return ret;
}
#endif
// SubDir
/////////////////////////////////////////////////////////////////////

void Dz1DirCatalogA_del(Dz1DirCatalogA *p)
{
	if (p == NULL) return;
	if (p->path) Dz1Free(p->path);
	if (p->spec) Dz1Free(p->spec);
	if (p->entries) Dz1Free(p->entries);
	Dz1Free(p);
}

#ifndef UNIX_SYSTEM
void Dz1DirCatalogW_del(Dz1DirCatalogW *p)
{
	if (p == NULL) return;
	if (p->path) Dz1Free(p->path);
	if (p->spec) Dz1Free(p->spec);
	if (p->entries) Dz1Free(p->entries);
	Dz1Free(p);
}
#endif

void Dz1DirCatalogA_dump(Dz1DirCatalogA *p, int tab)
{
	if (!p) Dz1ThreadA_printf("NULL\n");
	else
	{
		Dz1ThreadA_printf("{\n");
		Dz1ThreadA_tprintf(tab, "PATH = %s\n", p->path);
	}
}

#ifndef UNIX_SYSTEM
void Dz1DirCatalogW_dump(Dz1DirCatalogW *p, int tab)
{
	if (!p) Dz1ThreadW_printf(L"NULL\n");
	else
	{
		Dz1ThreadW_printf(L"{\n");
		Dz1ThreadW_tprintf(tab, L"PATH = %s\n", p->path);
	}
}
#endif

static int Dz1DirCatalogA_cmpName(Dz1DirEntryA *a, Dz1DirEntryA *b) { return strcmp(a->name, b->name); }
#ifndef UNIX_SYSTEM
static int Dz1DirCatalogW_cmpName(Dz1DirEntryW *a, Dz1DirEntryW *b)
{
	if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else
	{
		int ret = 0;
		ssize_t a_len = (ssize_t)wcslen(a->name), b_len = (ssize_t)wcslen(b->name);
		if ((ret = (int)(a_len - b_len)) != 0) return ret;
		else return wcscmp(a->name, b->name);
	}
}
#endif

static int Dz1DirCatalogA_cmpSize(Dz1DirEntryA *a, Dz1DirEntryA *b)
{
	if (a->size < b->size) return -1;
	else if (a->size > b->size) return 1;
	return 0;
}

#ifndef UNIX_SYSTEM
static int Dz1DirCatalogW_cmpSize(Dz1DirEntryW *a, Dz1DirEntryW *b)
{
	if (a->size < b->size) return -1;
	else if (a->size > b->size) return 1;
	return 0;
}
#endif

static int Dz1DirCatalogA_cmpDate(Dz1DirEntryA *a, Dz1DirEntryA *b)
{
	if (a->date < b->date) return -1;
	else if (a->date > b->date) return 1;
	return 0;
}

#ifndef UNIX_SYSTEM
static int Dz1DirCatalogW_cmpDate(Dz1DirEntryW *a, Dz1DirEntryW *b)
{
	if (a->date < b->date) return -1;
	else if (a->date > b->date) return 1;
	return 0;
}
#endif

u32_t Dz1DirCatalogA_find(Dz1DirCatalogA *p, str_t name)
{
	u32_t i;
	for (i = 0; i < p->valid; i++)
		if (strcmp(p->entries[i].name, name) == 0) return i;
	return -1;
}

#ifndef UNIX_SYSTEM
u32_t Dz1DirCatalogW_find(Dz1DirCatalogW *p, wstr_t name)
{
	u32_t i;
	for (i = 0; i < p->valid; i++)
		if (wcscmp(p->entries[i].name, name) == 0) return i;
	return -1;
}
#endif

int Dz1DirCatalogA_cmp(Dz1DirCatalogA *a, Dz1DirCatalogA *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else
	{
		if (a->path == NULL && b->path == NULL) return 0;
		else if (a->path == NULL && b->path != NULL) return -1;
		else if (a->path != NULL && b->path == NULL) return 1;
		return strcmp(a->path, b->path);
	}
}

#ifndef UNIX_SYSTEM
int Dz1DirCatalogW_cmp(Dz1DirCatalogW *a, Dz1DirCatalogW *b)
{
	if (a == NULL && b == NULL) return 0;
	else if (a == NULL && b != NULL) return -1;
	else if (a != NULL && b == NULL) return 1;
	else
	{
		if (a->path == NULL && b->path == NULL) return 0;
		else if (a->path == NULL && b->path != NULL) return -1;
		else if (a->path != NULL && b->path == NULL) return 1;
		return wcscmp(a->path, b->path);
	}
}
#endif

Dz1Error _Dz1DirCatalogA_sort(Dz1DirCatalogA *p, Dz1DirEntryACmpFunc cmp)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	size_t i, j;
	if (p->valid > 1)
	{
		for (i = 0; i < p->valid - 1; i++)
		{
			for (j = i + 1; j < p->valid; j++)
			{
				if (cmp(&p->entries[j], &p->entries[i]) < 0)
				{
					Dz1DirEntryA temp = p->entries[j];
					p->entries[j] = p->entries[i];
					p->entries[i] = temp;
				}
			}
		}
	}
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error _Dz1DirCatalogW_sort(Dz1DirCatalogW *p, Dz1DirEntryWCmpFunc cmp)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;
	size_t i, j;
	if (p->valid > 1)
	{
		for (i = 0; i < p->valid - 1; i++)
		{
			for (j = i + 1; j < p->valid; j++)
			{
				if (cmp(&p->entries[j], &p->entries[i]) < 0)
				{
					Dz1DirEntryW temp = p->entries[j];
					p->entries[j] = p->entries[i];
					p->entries[i] = temp;
				}
			}
		}
	}
	return err;
}
#endif

Dz1Error Dz1DirCatalogA_sort(Dz1DirCatalogA *p, Dz1DirCatalogSortBy sort)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (p == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (p->valid <= 1) { }
	else
	{
		Dz1DirEntryACmpFunc cmp = NULL;
		switch(sort)
		{
		case Dz1DirCatalogSortBy_name:
			cmp = Dz1DirCatalogA_cmpName;
			break;
		case Dz1DirCatalogSortBy_size:
			cmp = Dz1DirCatalogA_cmpSize;
			break;
		case Dz1DirCatalogSortBy_date:
			cmp = Dz1DirCatalogA_cmpDate;
			break;
		default:
			ERR_SET_OUT(&err, EINVAL);
			return err;
		}
		if ((err = _Dz1DirCatalogA_sort(p, cmp)).code) ERR_OUT(&err);
	}
	return err;
}

#ifndef UNIX_SYSTEM
Dz1Error Dz1DirCatalogW_sort(Dz1DirCatalogW *p, Dz1DirCatalogSortBy sort)
{
	Dz1Error err = DZ1_ERROR_INITIALIZER;

	if (p == NULL) ERR_SET_OUT(&err, EINVAL);
	else if (p->valid <= 1) { }
	else
	{
		Dz1DirEntryWCmpFunc cmp = NULL;
		switch(sort)
		{
		case Dz1DirCatalogSortBy_name:
			cmp = Dz1DirCatalogW_cmpName;
			break;
		case Dz1DirCatalogSortBy_size:
			cmp = Dz1DirCatalogW_cmpSize;
			break;
		case Dz1DirCatalogSortBy_date:
			cmp = Dz1DirCatalogW_cmpDate;
			break;
		default:
			ERR_SET_OUT(&err, EINVAL);
			return err;
		}
		if ((err = _Dz1DirCatalogW_sort(p, cmp)).code) ERR_OUT(&err);
	}
	return err;
}
#endif
// DIR Catalog
///////////////////////////////////////////////////////////////////////////////

#ifdef UNIX_SYSTEM
ssize_t GetTempPathA(size_t buf_sz, char *buf)
{
	ssize_t ret = -1;
	if (Dz1Dir_isExist("/tmp"))
	{
		strcpy(buf, "/tmp");
		ret = 4;
	}
	else if (Dz1Dir_isExist("/var/tmp"))
	{
		strcpy(buf, "/var/tmp");
		ret = 8;
	}
	return ret;
}

ssize_t GetTempFileNameA(str_t path, str_t prefix, int isUnique, char *buf)
{
	u16_t pid = (u16_t)(getpid() & 0xFFFF);
	u32_t tNow = (u32_t)(time(NULL) & 0xFFFFFFFF);
	u16_t mod = (u16_t)(rand() & 0xFFFF);
	sprintf(buf, "%s%04x%08x%04x", Dz1Str_isVoid(prefix) ? "" : prefix, pid, tNow, mod);
	return strlen(buf);
}
#endif
bool_t Dz1GetTempFileNameA(char *dst, size_t dst_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	char tmp_path[1024] = { 0, };
	char tmp_file[1024] = { 0, };
	size_t path_len = 0;
	if ((path_len = GetTempPathA(1024, tmp_path)) == 0) ERR_SET_OUT(errp, EFAULT);
	else if (GetTempFileNameA(tmp_path, NULL, 0, tmp_file) == 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		char temp[2048] = { 0, };
		if ((*errp = Dz1FileNameA_concatPathName(temp, ARR_VAR_SIZE(char, temp), tmp_path, tmp_file)).code) ERR_OUT(errp);
		else if (dst_sz <= strlen(temp)) ERR_SET_OUT(errp, E2BIG);
		else strcpy(dst, temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}

#ifndef UNIX_SYSTEM
bool_t Dz1GetTempFileNameW(wchar_t *dst, size_t dst_sz, Dz1Error *err)
{
	DZ1_ERROR_SAFE_PTR(errp, err);
	size_t path_len = 0;
	wchar_t tmp_path[1024] = { 0, };
	wchar_t tmp_file[1024] = { 0, };
	if ((path_len = GetTempPathW(1024, tmp_path)) == 0) ERR_SET_OUT(errp, EFAULT);
	else if (GetTempFileNameW(tmp_path, NULL, 0, tmp_file) == 0) ERR_SET_OUT(errp, EFAULT);
	else
	{
		wchar_t temp[2048] = { 0, };
		if ((*errp = Dz1FileNameW_concatPathName(temp, ARR_VAR_SIZE(wchar_t, temp), tmp_path, tmp_file)).code) ERR_OUT(errp);
		else if (dst_sz <= wcslen(temp)) ERR_SET_OUT(errp, E2BIG);
		else wcscpy(dst, temp);
	}
	return errp->code == 0 ? TRUE : FALSE;
}
#endif

