#ifndef DZ1_TDQ_TYPES_H
#define DZ1_TDQ_TYPES_H

#include <dz1_error.h>
#include <dz1_str.h>

#ifndef UNIX_SYSTEM
#pragma warning(disable:5286)
#pragma warning(disable:5287)
#endif

///////////////////////////////////////////////////////////////////////////////
// DB Engine Setting
#define DBH_ENGINE_MY_SQL			0
#define DBH_ENGINE_MS_SQL			1
#define DBH_ENGINE_ORACLE8		2

#define DBH_ENGINE_MARIA			DBH_ENGINE_MY_SQL

#define DBH_ENGINE					DBH_ENGINE_MY_SQL
// DB Setting
///////////////////////////////////////////////////////////////////////////////

typedef struct Dz1TdqPageSpec
{
	u32_t					 pg_size;
	u32_t					 pg_num;
} Dz1TdqPageSpec;
DZ1_CPPLINK Dz1TdqPageSpec			*Dz1TdqPageSpec_new(u32_t pg_size, u32_t pg_num, Dz1Error *err);
static __inline__ Dz1TdqPageSpec	*Dz1TdqPageSpec_gen(Dz1Error *err) { return Dz1TdqPageSpec_new(0, 0, err); }
DZ1_CPPLINK Dz1TdqPageSpec			*Dz1TdqPageSpec_clone(Dz1TdqPageSpec *src, Dz1Error *err);
DZ1_CPPLINK void					 Dz1TdqPageSpec_del(Dz1TdqPageSpec *p);
static __inline__ void				 Dz1TdqPageSpec_delAndSetNull(void *pptr)
{
	Dz1TdqPageSpec **p = (Dz1TdqPageSpec **)pptr;
	Dz1TdqPageSpec_del(*p); *p = NULL;
}
DZ1_CPPLINK void					 Dz1TdqPageSpec_dump(Dz1TdqPageSpec *p, int tab);

#ifdef UNIX_SYSTEM

#if			DBH_ENGINE == DBH_ENGINE_MY_SQL
///////////////////////////////////////
// DB Interface for MY SQL
typedef struct Dz1TdqDbConnArg
{
	Dz1Str					 drv_name;
	Dz1Str					 svr_addr;
	u16_t					 svr_port;
	Dz1Str					 user;
	Dz1Str					 pw;
	Dz1Str					 dbn_opt;		// DB Name
} Dz1TdqDbConnArg;
DZ1_CPPLINK Dz1TdqDbConnArg			*Dz1TdqDbConnArg_new(Dz1Error *err);
DZ1_CPPLINK Dz1TdqDbConnArg			*Dz1TdqDbConnArg_clone(Dz1TdqDbConnArg *src, Dz1Error *err);
DZ1_CPPLINK void					 Dz1TdqDbConnArg_del(Dz1TdqDbConnArg *p);
DZ1_CPPLINK void					 Dz1TdqDbConnArg_dump(Dz1TdqDbConnArg *p, int tab);

typedef struct Dz1TdqDbIface
{
	void					*dumb;
} Dz1TdqDbIface;
DZ1_CPPLINK Dz1TdqDbIface			*Dz1TdqDbIface_new(Dz1TdqDbConnArg *arg, Dz1Error *err);
DZ1_CPPLINK void					 Dz1TdqDbIface_del(Dz1TdqDbIface *p);
DZ1_CPPLINK bool_t					 Dz1TdqDbIface_reconn(Dz1TdqDbIface *p, Dz1Error *err);
// DB Interface for MY SQL
///////////////////////////////////////

#else if	DBH_ENGINE == DBH_ENGINE_MS_SQL
///////////////////////////////////////
// DB Interface for M$ SQL
typedef struct Dz1TdqDbConnArg
{
	Dz1Str					 drv_name;
	Dz1Str					 svr_addr;
	u16_t					 svr_port;
	Dz1Str					 user;
	Dz1Str					 pw;
	Dz1Str					 dbn_opt;		// DB Name
} Dz1TdqDbConnArg;
DZ1_CPPLINK Dz1TdqDbConnArg			*Dz1TdqDbConnArg_new(Dz1Error *err);
DZ1_CPPLINK Dz1TdqDbConnArg			*Dz1TdqDbConnArg_clone(Dz1TdqDbConnArg *src, Dz1Error *err);
DZ1_CPPLINK void					 Dz1TdqDbConnArg_del(Dz1TdqDbConnArg *p);
DZ1_CPPLINK void					 Dz1TdqDbConnArg_dump(Dz1TdqDbConnArg *p, int tab);

typedef struct Dz1TdqDbIface
{
	void					*dumb;
} Dz1TdqDbIface;
DZ1_CPPLINK Dz1TdqDbIface			*Dz1TdqDbIface_new(Dz1TdqDbConnArg *arg, Dz1Error *err);
DZ1_CPPLINK void					 Dz1TdqDbIface_del(Dz1TdqDbIface *p);
DZ1_CPPLINK bool_t					 Dz1TdqDbIface_reconn(Dz1TdqDbIface *p, Dz1Error *err);
// DB Interface for M$ SQL
///////////////////////////////////////

#else if	DBH_ENGINE == DBH_ENGINE_ORACLE8
///////////////////////////////////////
// DB Interface for Oracle 8
typedef struct Dz1TdqDbConnArg
{
	Dz1Str					 tns_name;
	u16_t					 svr_port;
	Dz1Str					 user;
	Dz1Str					 pw;
	Dz1Str					 dbn_opt;		// DB Name
} Dz1TdqDbConnArg;
DZ1_CPPLINK Dz1TdqDbConnArg			*Dz1TdqDbConnArg_new(Dz1Error *err);
DZ1_CPPLINK Dz1TdqDbConnArg			*Dz1TdqDbConnArg_clone(Dz1TdqDbConnArg *src, Dz1Error *err);
DZ1_CPPLINK void					 Dz1TdqDbConnArg_del(Dz1TdqDbConnArg *p);
DZ1_CPPLINK void					 Dz1TdqDbConnArg_dump(Dz1TdqDbConnArg *p, int tab);

typedef struct Dz1TdqDbIface
{
	void					*dumb;
} Dz1TdqDbIface;
DZ1_CPPLINK Dz1TdqDbIface			*Dz1TdqDbIface_new(Dz1TdqDbConnArg *arg, Dz1Error *err);
DZ1_CPPLINK void					 Dz1TdqDbIface_del(Dz1TdqDbIface *p);
DZ1_CPPLINK bool_t					 Dz1TdqDbIface_reconn(Dz1TdqDbIface *p, Dz1Error *err);
// DB Interface for Oracle 8
///////////////////////////////////////

#else
#error "please define DBH_ENGINE"
#endif		// DBH_ENGINE

#else // UNIX_SYSTEM
///////////////////////////////////////////////////////////////////////////////
// Windows ODBC
#pragma comment(lib, "odbc32.lib") 
#include <odbcinst.h>
#include <sqlext.h>

#define MARIA_DB_DRIVER_3_0				Dz1Text("MariaDB ODBC 3.0 Driver")
#define MARIA_DB_DRIVER_3_1				Dz1Text("MariaDB ODBC 3.1 Driver")
#define MARIA_DB_PORT_NUM				3306

typedef struct Dz1TdqDbConnArg
{
	Dz1Str					 drv_name;
	Dz1Str					 svr_addr;
	u16_t					 svr_port;
	Dz1Str					 user;
	Dz1Str					 pw;
	Dz1Str					 dbn_opt;		// DB Name
} Dz1TdqDbConnArg;

DZ1_CPPLINK Dz1TdqDbConnArg			*Dz1TdqDbConnArg_new(Dz1Str drv_name, Dz1Str svr_Addr, u16_t svr_port, Dz1Str user, Dz1Str pw, Dz1Str dbn_opt, Dz1Error *err);
DZ1_CPPLINK Dz1TdqDbConnArg			*Dz1TdqDbConnArg_clone(Dz1TdqDbConnArg *src, Dz1Error *err);
DZ1_CPPLINK void					 Dz1TdqDbConnArg_del(Dz1TdqDbConnArg *p);
DZ1_CPPLINK void					 Dz1TdqDbConnArg_dump(Dz1TdqDbConnArg *p, int tab);

typedef struct Dz1TdqDbIface
{
	HENV					 h_db_env;
	HDBC					 h_odbc;
	Dz1TdqDbConnArg			*arg;			// reg ptr = scm->arg
} Dz1TdqDbIface;
DZ1_CPPLINK Dz1TdqDbIface			*Dz1TdqDbIface_new(Dz1TdqDbConnArg *arg, Dz1Error *err);
DZ1_CPPLINK void					 Dz1TdqDbIface_del(Dz1TdqDbIface *p);
DZ1_CPPLINK bool_t					 Dz1TdqDbIface_reconn(Dz1TdqDbIface *p, Dz1Error *err);

DZ1_CPPLINK bool_t					 Dz1TdqDbIface_sqlPaging(Dz1ElasticBuf *dst, Dz1TdqPageSpec *spec, Dz1Error *err);
// Windows ODBC
///////////////////////////////////////////////////////////////////////////////
#endif // UNIX_SYSTEM

///////////////////////////////////////////////////////////////////////////////
// Common inline macro
static __inline__ Dz1TdqDbConnArg	*Dz1TdqDbConnArg_gen(Dz1Error *err) { return Dz1TdqDbConnArg_new(NULL, NULL, 0, NULL, NULL, NULL, err); }
static __inline__ void				 Dz1TdqDbConnArg_delAndSetNull(void *pptr)
{
	Dz1TdqDbConnArg **p = (Dz1TdqDbConnArg **)pptr;
	Dz1TdqDbConnArg_del(*p); *p = NULL;
}

static __inline__ void				 Dz1TdqDbIface_delAndSetNull(void *pptr)
{
	Dz1TdqDbIface **p = (Dz1TdqDbIface **)pptr;
	Dz1TdqDbIface_del(*p); *p = NULL;
}
// Common inline macro
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// SQL Type Setting
#if DBH_ENGINE == DBH_ENGINE_MY_SQL
///////////////////////////////////////
// SQL Type Mapping for MY_SQL
#define DBH_TYPE_INT8					Dz1Text("TINYINT")
#define DBH_TYPE_INT16					Dz1Text("SMALLINT")
#define DBH_TYPE_INT32					Dz1Text("INT")
#define DBH_TYPE_INT64					Dz1Text("BIGINT")

#define DBH_TYPE_FLOAT32				Dz1Text("FLOAT")
#define DBH_TYPE_FLOAT64				Dz1Text("DOUBLE")

#define DBH_TYPE_STRING					Dz1Text("CHAR")
#define DBH_TYPE_VSTRING				Dz1Text("VARCHAR")
#define DBH_TYPE_NSTRING				Dz1Text("NCHAR")
#define DBH_TYPE_NVSTRING				Dz1Text("NVARCHAR")
#define DBH_TYPE_BINARY					Dz1Text("BINARY")
#define DBH_TYPE_VBINARY				Dz1Text("VARBINARY")

#define DBH_TYPE_DATE					Dz1Text("DATE")
#define DBH_TYPE_TIME					Dz1Text("TIME")
#define DBH_TYPE_DATETIME				Dz1Text("DATETIME")

#define DBH_TYPE_BLOB16M				Dz1Text("MEDIUMBLOB")
#define DBH_TYPE_BLOB					Dz1Text("LONGBLOB")
// SQL Type Mapping for MY_SQL
///////////////////////////////////////

#elif DBH_ENGINE == DBH_ENGINE_MS_SQL
///////////////////////////////////////
// SQL Type Mapping for MS_SQL
#define DBH_TYPE_INT8					Dz1Text("TINYINT")
#define DBH_TYPE_INT16					Dz1Text("SMALLINT")
#define DBH_TYPE_INT32					Dz1Text("INT")
#define DBH_TYPE_INT64					Dz1Text("BIGINT")

#define DBH_TYPE_FLOAT32				Dz1Text("REAL")
#define DBH_TYPE_FLOAT64				Dz1Text("FLOAT")

#define DBH_TYPE_STRING					Dz1Text("CHAR")
#define DBH_TYPE_VSTRING				Dz1Text("VARCHAR")
#define DBH_TYPE_NSTRING				Dz1Text("NCHAR")
#define DBH_TYPE_NVSTRING				Dz1Text("NVARCHAR")
#define DBH_TYPE_BINARY					Dz1Text("BINARY")
#define DBH_TYPE_VBINARY				Dz1Text("VARBINARY")

#define DBH_TYPE_DATE					Dz1Text("DATE")
#define DBH_TYPE_TIME					Dz1Text("TIME")
#define DBH_TYPE_DATETIME				Dz1Text("DATETIME")

#define DBH_TYPE_BLOB16M				Dz1Text("VARBINARY(16777215)")
#define DBH_TYPE_BLOB					Dz1Text("VARBINARY(2147483647)")
// SQL Type Mapping for MS_SQL
///////////////////////////////////////

#elif DBH_ENGINE == DBH_ENGINE_ORACLE8
///////////////////////////////////////
// SQL Type Mapping for Oracle8
// SQL Type Mapping for Oracle8
///////////////////////////////////////
#else	// DBH_ENGINE
#error "please define DBH_ENGINE"
#endif	// DBH_ENGINE
// SQL Type Setting
///////////////////////////////////////////////////////////////////////////////

#endif
