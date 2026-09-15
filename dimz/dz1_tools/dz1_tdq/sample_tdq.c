#include <dz1_tdq_util.h>
#include <dz1_tdq_qry_def_util.h>

#include <dz1_tdq_var_def_util.h>

#include "sample_tdq.h"
#include "sample_util.h"

static bool_t MyDataRow_regShape(Dz1TdqDbScheme *dst, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1TdqTblShape *node = Dz1TdqTblShape_new(Dz1Text("MyDataRow"), NULL, NULL, errp);
    if (node == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1TdqTblShape_delAndSetNull, (void *)&node);
        if ((node->row = Dz1TdqRow_new(errp)) == NULL) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("id"), Dz1TdqType_num_u32, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addStr(node->row, Dz1Text("name"), Dz1TdqType_vtstring, 127, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addBlob(node->row, Dz1Text("data"), Dz1TdqType_blob, Dz1TdqSqlBlobSpec_embedded, not_null_no_default, errp) == FALSE) ERR_OUT(errp);

        else if ((node->pk = Dz1TdqRowRef_new(errp)) == NULL) ERR_OUT(errp);
        else if (Dz1TdqRowRef_addCol(node->pk, Dz1Text("id"), node->row, errp) == FALSE) ERR_OUT(errp);

        else if ((*errp = dst->shapes->add(dst->shapes, node)).code) ERR_OUT(errp);
        else
        {
            node = NULL;
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Dz1TdqTblShape_delAndSetNull, (void *)&node);
    }
    return errp->code == 0 ? TRUE : FALSE;;
}

static bool_t _MyDataRow_writeRow(Dz1TdqSqlVar **dst, u32_t cnt, MyDataRow *src, Dz1Error *errp)
{
    Dz1TdqSqlBlobToDB *blob_write = NULL;
    dst[0]->x.u32 = src->id;

    if (Dz1Str_isVoid(src->name)) Dz1TdqSqlVar_setNullValue(dst[1]);
    else Dz1STRNCPY(dst[1]->x.vtstring->text, src->name, (dst[1]->x.vtstring->alloc_byte / sizeof(TCHAR)) - 1);

    if (src->data == NULL) Dz1TdqSqlVar_setNullValue(dst[2]);
    else if ((blob_write = MyDataDBIO_write(src->data, errp)) == NULL) ERR_OUT_RET(errp, FALSE);
    else { Dz1TdqSqlBlobToDB_delAndSetNull(&dst[2]->x.blob->writeToDB); dst[2]->x.blob->writeToDB = blob_write; Dz1Error_set(errp, 0); }

    return errp->code == 0 ? TRUE : FALSE;
}

static Dz1TdqRowSupply MyDataRow_writeRow(void *ptr, u32_t row_idx, Dz1TdqSqlVar **dst, u32_t cnt, Dz1Error *errp)
{
    Dz1TdqRowSupply ret = Dz1TdqRowSupply_end;
    if (row_idx == 0)
    {
        if (_MyDataRow_writeRow(dst, cnt, (MyDataRow *)ptr, errp) == FALSE) ret = Dz1TdqRowSupply_error;
        else ret = Dz1TdqRowSupply_ok;
    }
    return ret;
}

static Dz1TdqRowSupply MyDataRow_writeRows(void *ptr, u32_t row_idx, Dz1TdqSqlVar **dst, u32_t cnt, Dz1Error *errp)
{
    Dz1TdqRowSupply ret = Dz1TdqRowSupply_ok;
    Dz1TdqSupplyArg *arg = (Dz1TdqSupplyArg *)ptr;
    if (row_idx < arg->cnt)
    {
        MyDataRow **arr = (MyDataRow **)arg->arr;
        if (_MyDataRow_writeRow(dst, cnt, arr[row_idx], errp) == FALSE) ret = Dz1TdqRowSupply_error;
        else ret = Dz1TdqRowSupply_ok;
    }
    else ret = Dz1TdqRowSupply_end;
    return ret;
}

static void MyDataRow_readRow(void *ptr, u32_t idx, Dz1TdqSqlVar **src, SQLLEN *src_stat, u32_t cnt)
{
    DZ1_ERROR_SAFE_VAR(errp, err);
    MyDataTbl *dst = (MyDataTbl *)ptr;
    MyDataRow *node = MyDataRow_gen(errp);
    if (node == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(MyDataRow_delAndSetNull, (void *)&node);
        if (0) { }
        else if (Dz1TdqSqlVarGetStr(&node->name, src[1], errp) == FALSE) ERR_OUT(errp);
        else if (MyDataDBIO_read(&node->data, src[2], errp) == FALSE) ERR_OUT(errp);
        else
        {
            node->id = Dz1TdqSqlVarGetNum(src[0], u32, 0);
            if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
            else
            {
                node = NULL;
                Dz1Error_set(errp, 0);
            }
        }
        pthread_cleanup_pop(1); // (MyStructAAAA_delAndSetNull, (void *)&node);
    }
}

static Dz1TdqSqlNamedVarList *_MyDataRow_nvListGen(MyDataRow *src, Dz1Error *errp)
{
    Dz1TdqSqlNamedVarList *ret = NULL;
    if (src == NULL) ERR_SET_OUT(errp, EINVAL);
    else if ((ret = Dz1TdqSqlNamedVarList_new(errp)) == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&ret);
        if (0) { }
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("id"), Dz1TdqSqlVarPresent_u32, &src->id, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addStr(ret, Dz1Text("name"), Dz1TdqSqlVarPresent_vtstring, src->name, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addBlob(ret, Dz1Text("data"), Dz1TdqSqlVarPresent_blob, MyDataDBIO_write, src->data, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&ret);
    }
    return ret;
}

static Dz1TdqSqlNamedVarList *MyDataRow_nvListGen(MyDataRow *src, Dz1Str comma_seprated_names, Dz1Error *err) // (names == NULL | ZeroLen) : All, (names == "@") : All except keys
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1TdqSqlNamedVarList *ret = NULL, *temp = NULL;
    if (src == NULL) ERR_SET_OUT(errp, EINVAL);
    else if ((temp = _MyDataRow_nvListGen(src, errp)) == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&temp);
        if (Dz1Str_isVoid(comma_seprated_names) == TRUE)
        {
            ret = temp;
            temp = NULL;
            Dz1Error_set(errp, 0);
        }
        else if (Dz1STRCMP(Dz1Text("@"), comma_seprated_names) == 0)
        {
            Dz1TdqSqlNamedVarList_removeByName(temp, Dz1Text("id"));
            ret = temp;
            temp = NULL;
            Dz1Error_set(errp, 0);
        }
        else if ((ret = Dz1TdqSqlNamedVarList_collect(temp, comma_seprated_names, errp)) == NULL) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&temp);
    }
    return ret;
}

static bool_t MyDataTbl_regTable(Dz1TdqDbScheme *dst, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1TdqTblInstance *node = Dz1TdqTblInstance_new(Dz1Text("my_data_tbl"), NULL, errp);
    if (node == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1TdqTblInstance_delAndSetNull, (void *)&node);
        if (0) { }
        else if ((node->shape = Dz1TdqTblShapeList_findByName(dst->shapes, Dz1Text("MyDataRow") )) == NULL) ERR_SET_OUT(errp, ENOENT);
        else if (Dz1TdqDbScheme_appendInstance(dst, node, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqDbScheme_regSimpleQuery(dst, node, errp) == FALSE) ERR_OUT(errp);
        else
        {
            node = NULL;
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Dz1TdqTblInstance_delAndSetNull, (void *)&ret);
    }
    return errp->code == 0 ? TRUE : FALSE;
}


bool_t MyDataTbl_insert(Dz1TdqDbScheme *scm, MyDataRow *row, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    if (scm == NULL || row == NULL) ERR_SET_OUT(errp, EINVAL);
    else if (Dz1TdqDbScheme_insert(scm, Dz1Text("my_data_tbl"), NULL, MyDataRow_writeRow, row, commit, errp) == FALSE) ERR_OUT(errp);
    else Dz1Error_set(errp, 0);
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyDataTbl_insertA(Dz1TdqDbScheme *scm, MyDataRow **arr, u32_t cnt, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    if (scm == NULL || arr == NULL || cnt == 0) ERR_SET_OUT(errp, EINVAL);
    else
    {
        Dz1TdqSupplyArg arg = { arr, cnt };
        if (Dz1TdqDbScheme_insert(scm, Dz1Text("my_data_tbl"), NULL, MyDataRow_writeRows, (void *)&arg, commit, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyDataTbl_insertL(Dz1TdqDbScheme *scm, MyDataTbl *rows, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    u32_t cnt = 0;
    MyDataRow **arr = NULL;
    if (scm == NULL || rows == NULL || rows->count(rows) == 0) ERR_SET_OUT(errp, EINVAL);
    else if ((arr = rows->get_array(rows, &cnt, errp)) == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
        if (MyDataTbl_insertA(scm, arr, cnt, commit, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyDataTbl_update(Dz1TdqDbScheme *scm, MyDataRow *key, MyDataRow *row, Dz1Str update_cols_str, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1Str whr = Dz1Text("id=?");
    Dz1TdqSqlVarArray *args = Dz1TdqSqlVarArray_new(errp);
    if (args == NULL) ERR_OUT(errp);
    else
    {
        Dz1TdqSqlNamedVarList *update_vars = NULL;
        pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);

        if (0) { }

        else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_u32, &key->id, errp) == FALSE) ERR_OUT(errp);

        else if ((update_vars = MyDataRow_nvListGen(row, update_cols_str, errp)) == NULL) ERR_OUT(errp);
        else 
        {
            pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&update_vars);
            if (Dz1TdqDbScheme_update(scm, Dz1Text("my_data_tbl"), update_vars, whr, args, commit, errp) == FALSE) ERR_OUT(errp);
            else Dz1Error_set(errp, 0);
            pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)update_vars);
        }
        pthread_cleanup_pop(1); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyDataTbl_delete(Dz1TdqDbScheme *scm, MyDataRow *key, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1Str whr = Dz1Text("id=?");
    Dz1TdqSqlVarArray *args = Dz1TdqSqlVarArray_new(errp);
    if (args == NULL) ERR_OUT(errp);
    else
    {
        Dz1TdqSqlVar *my_unum64 = NULL;
        pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);
        if (0) { }

        else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_u32, &key->id, errp) == FALSE) ERR_OUT(errp);

        else if (Dz1TdqDbScheme_delete(scm, Dz1Text("my_data_tbl"), whr, args, commit, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(1); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

MyDataTbl *MyDataTbl_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    MyDataTbl *ret = MyDataTbl_gen(errp);
    if (ret == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(MyDataTbl_delAndSetNull, (void *)&ret);
        if (Dz1TdqDbScheme_select(scm, Dz1Text("my_data_tbl"), MyDataRow_readRow, (void *)ret, whr, args, paging, errp) == FALSE)
        {
            if (errp->code != ENOENT) ERR_OUT(errp);
        }
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (MyStructAAAAList_delAndSetNull, (void *)&ret);
    }
    return ret;
}

static bool_t AAAA_regShape(Dz1TdqDbScheme *dst, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1TdqTblShape *node = Dz1TdqTblShape_new(Dz1Text("AAAA"), NULL, NULL, errp);
    if (node == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1TdqTblShape_delAndSetNull, (void *)&node);
        if ((node->row = Dz1TdqRow_new(errp)) == NULL) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_unum64"), Dz1TdqType_num_u64, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_num64"), Dz1TdqType_num_s64, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_unum32"), Dz1TdqType_num_u32, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_num32"), Dz1TdqType_num_s32, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_unum16"), Dz1TdqType_num_u16, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_num16"), Dz1TdqType_num_s16, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_unum8"), Dz1TdqType_num_u8, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_num8"), Dz1TdqType_num_s8, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addReal(node->row, Dz1Text("my_real"), Dz1TdqType_num_r64, -1, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addStr(node->row, Dz1Text("my_str"), Dz1TdqType_vtstring, 64, NULL, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addTime(node->row, Dz1Text("my_date"), Dz1TdqType_date, NULL, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addTime(node->row, Dz1Text("my_clock"), Dz1TdqType_time, NULL, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addTime(node->row, Dz1Text("my_stamp"), Dz1TdqType_timestamp, NULL, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addBlob(node->row, Dz1Text("my_blob"), Dz1TdqType_blobL, Dz1TdqSqlBlobSpec_embedded, NULL, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addBlob(node->row, Dz1Text("my_blobl"), Dz1TdqType_blob, Dz1TdqSqlBlobSpec_embedded, NULL, errp) == FALSE) ERR_OUT(errp);

        else if ((node->pk = Dz1TdqRowRef_new(errp)) == NULL) ERR_OUT(errp);
        else if (Dz1TdqRowRef_addCol(node->pk, Dz1Text("my_unum64"), node->row, errp) == FALSE) ERR_OUT(errp);

        else if ((*errp = Dz1TdqIndexList_append(node->indexes, Dz1Text("_NUM64_INDEX"), TRUE, node->row, Dz1Text("my_num64"), NULL)).code) ERR_OUT(errp);

        else if ((*errp = dst->shapes->add(dst->shapes, node)).code) ERR_OUT(errp);
        else
        {
            node = NULL;
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Dz1TdqTblShape_delAndSetNull, (void *)&node);
    }
    return errp->code == 0 ? TRUE : FALSE;;
}

static bool_t _MyStructAAAA_writeRow(Dz1TdqSqlVar **dst, u32_t cnt, MyStructAAAA *src, Dz1Error *errp)
{
    Dz1TdqSqlBlobToDB *blob_write = NULL;
    dst[0]->x.u64 = src->my_unum64;
    dst[1]->x.s64 = src->my_num64;
    dst[2]->x.u32 = src->my_unum32;
    dst[3]->x.s32 = src->my_num32;
    dst[4]->x.u16 = src->my_unum16;
    dst[5]->x.s16 = src->my_num16;
    dst[6]->x.u8 = src->my_unum8;
    dst[7]->x.s8 = src->my_num8;
    dst[8]->x.r64 = src->my_real;

    if (Dz1Str_isVoid(src->my_str)) Dz1TdqSqlVar_setNullValue(dst[9]);
    else Dz1STRNCPY(dst[9]->x.vtstring->text, src->my_str, (dst[9]->x.vtstring->alloc_byte / sizeof(TCHAR)) - 1);

    if (src->my_date == 0) Dz1TdqSqlVar_setNullValue(dst[10]);
    else if (Dz1TdqSqlDate_setFromT(dst[10]->x.ymd, src->my_date, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

    if (src->my_clock == 0) Dz1TdqSqlVar_setNullValue(dst[11]);
    else if (Dz1TdqSqlTime_setFromT(dst[11]->x.hms, src->my_clock, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

    if (src->my_stamp == 0) Dz1TdqSqlVar_setNullValue(dst[12]);
    else if (Dz1TdqSqlStamp_setFromT(dst[12]->x.stamp, src->my_stamp, errp) == FALSE) ERR_OUT_RET(errp, FALSE); else Dz1Error_set(errp, 0);

    if (src->my_blob == NULL) Dz1TdqSqlVar_setNullValue(dst[13]);
    else if ((blob_write = MyBinaryDBIO_write(src->my_blob, errp)) == NULL) ERR_OUT_RET(errp, FALSE);
    else { Dz1TdqSqlBlobToDB_delAndSetNull(&dst[13]->x.blobL->writeToDB); dst[13]->x.blobL->writeToDB = blob_write; Dz1Error_set(errp, 0); }

    if (src->my_blobl == NULL) Dz1TdqSqlVar_setNullValue(dst[14]);
    else if ((blob_write = Dz1BinaryDB_write(src->my_blobl, errp)) == NULL) ERR_OUT_RET(errp, FALSE);
    else { Dz1TdqSqlBlobToDB_delAndSetNull(&dst[14]->x.blob->writeToDB); dst[14]->x.blob->writeToDB = blob_write; Dz1Error_set(errp, 0); }

    return errp->code == 0 ? TRUE : FALSE;
}

static Dz1TdqRowSupply MyStructAAAA_writeRow(void *ptr, u32_t row_idx, Dz1TdqSqlVar **dst, u32_t cnt, Dz1Error *errp)
{
    Dz1TdqRowSupply ret = Dz1TdqRowSupply_end;
    if (row_idx == 0)
    {
        if (_MyStructAAAA_writeRow(dst, cnt, (MyStructAAAA *)ptr, errp) == FALSE) ret = Dz1TdqRowSupply_error;
        else ret = Dz1TdqRowSupply_ok;
    }
    return ret;
}

static Dz1TdqRowSupply MyStructAAAA_writeRows(void *ptr, u32_t row_idx, Dz1TdqSqlVar **dst, u32_t cnt, Dz1Error *errp)
{
    Dz1TdqRowSupply ret = Dz1TdqRowSupply_ok;
    Dz1TdqSupplyArg *arg = (Dz1TdqSupplyArg *)ptr;
    if (row_idx < arg->cnt)
    {
        MyStructAAAA **arr = (MyStructAAAA **)arg->arr;
        if (_MyStructAAAA_writeRow(dst, cnt, arr[row_idx], errp) == FALSE) ret = Dz1TdqRowSupply_error;
        else ret = Dz1TdqRowSupply_ok;
    }
    else ret = Dz1TdqRowSupply_end;
    return ret;
}

static void MyStructAAAA_readRow(void *ptr, u32_t idx, Dz1TdqSqlVar **src, SQLLEN *src_stat, u32_t cnt)
{
    DZ1_ERROR_SAFE_VAR(errp, err);
    MyStructAAAAList *dst = (MyStructAAAAList *)ptr;
    MyStructAAAA *node = MyStructAAAA_gen(errp);
    if (node == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(MyStructAAAA_delAndSetNull, (void *)&node);
        if (0) { }
        else if (Dz1TdqSqlVarGetStr(&node->my_str, src[9], errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlVarGetDate(&node->my_date, src[10], errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlVarGetTime(&node->my_clock, src[11], errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlVarGetStamp(&node->my_stamp, src[12], errp) == FALSE) ERR_OUT(errp);
        else if (MyBinaryDBIO_read(&node->my_blob, src[13], errp) == FALSE) ERR_OUT(errp);
        else if (Dz1BinaryDB_read(&node->my_blobl, src[14], errp) == FALSE) ERR_OUT(errp);
        else
        {
            node->my_unum64 = Dz1TdqSqlVarGetNum(src[0], u64, 0);
            node->my_num64 = Dz1TdqSqlVarGetNum(src[1], s64, 0);
            node->my_unum32 = Dz1TdqSqlVarGetNum(src[2], u32, 0);
            node->my_num32 = Dz1TdqSqlVarGetNum(src[3], s32, 0);
            node->my_unum16 = Dz1TdqSqlVarGetNum(src[4], u16, 0);
            node->my_num16 = Dz1TdqSqlVarGetNum(src[5], s16, 0);
            node->my_unum8 = Dz1TdqSqlVarGetNum(src[6], u8, 0);
            node->my_num8 = Dz1TdqSqlVarGetNum(src[7], s8, 0);
            node->my_real = Dz1TdqSqlVarGetNum(src[8], r64, 0);
            if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
            else
            {
                node = NULL;
                Dz1Error_set(errp, 0);
            }
        }
        pthread_cleanup_pop(1); // (MyStructAAAA_delAndSetNull, (void *)&node);
    }
}

static Dz1TdqSqlNamedVarList *_MyStructAAAA_nvListGen(MyStructAAAA *src, Dz1Error *errp)
{
    Dz1TdqSqlNamedVarList *ret = NULL;
    if (src == NULL) ERR_SET_OUT(errp, EINVAL);
    else if ((ret = Dz1TdqSqlNamedVarList_new(errp)) == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&ret);
        if (0) { }
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_unum64"), Dz1TdqSqlVarPresent_u64, &src->my_unum64, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_num64"), Dz1TdqSqlVarPresent_s64, &src->my_num64, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_unum32"), Dz1TdqSqlVarPresent_u32, &src->my_unum32, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_num32"), Dz1TdqSqlVarPresent_s32, &src->my_num32, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_unum16"), Dz1TdqSqlVarPresent_u16, &src->my_unum16, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_num16"), Dz1TdqSqlVarPresent_s16, &src->my_num16, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_unum8"), Dz1TdqSqlVarPresent_u8, &src->my_unum8, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_num8"), Dz1TdqSqlVarPresent_s8, &src->my_num8, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addReal(ret, Dz1Text("my_real"), Dz1TdqType_num_r64, &src->my_real, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addStr(ret, Dz1Text("my_str"), Dz1TdqSqlVarPresent_vtstring, src->my_str, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addTime(ret, Dz1Text("my_date"), Dz1TdqSqlVarPresent_ymd, &src->my_date, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addTime(ret, Dz1Text("my_clock"), Dz1TdqSqlVarPresent_hms, &src->my_clock, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addTime(ret, Dz1Text("my_stamp"), Dz1TdqSqlVarPresent_stamp, &src->my_stamp, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addBlob(ret, Dz1Text("my_blob"), Dz1TdqSqlVarPresent_blobL, MyBinaryDBIO_write, src->my_blob, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addBlob(ret, Dz1Text("my_blobl"), Dz1TdqSqlVarPresent_blob, Dz1BinaryDB_write, src->my_blobl, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&ret);
    }
    return ret;
}

static Dz1TdqSqlNamedVarList *MyStructAAAA_nvListGen(MyStructAAAA *src, Dz1Str comma_seprated_names, Dz1Error *err) // (names == NULL | ZeroLen) : All, (names == "@") : All except keys
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1TdqSqlNamedVarList *ret = NULL, *temp = NULL;
    if (src == NULL) ERR_SET_OUT(errp, EINVAL);
    else if ((temp = _MyStructAAAA_nvListGen(src, errp)) == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&temp);
        if (Dz1Str_isVoid(comma_seprated_names) == TRUE)
        {
            ret = temp;
            temp = NULL;
            Dz1Error_set(errp, 0);
        }
        else if (Dz1STRCMP(Dz1Text("@"), comma_seprated_names) == 0)
        {
            Dz1TdqSqlNamedVarList_removeByName(temp, Dz1Text("my_unum64"));
            ret = temp;
            temp = NULL;
            Dz1Error_set(errp, 0);
        }
        else if ((ret = Dz1TdqSqlNamedVarList_collect(temp, comma_seprated_names, errp)) == NULL) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&temp);
    }
    return ret;
}

static bool_t BBBB_regShape(Dz1TdqDbScheme *dst, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1TdqTblShape *node = Dz1TdqTblShape_new(Dz1Text("BBBB"), NULL, NULL, errp);
    if (node == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1TdqTblShape_delAndSetNull, (void *)&node);
        if ((node->row = Dz1TdqRow_new(errp)) == NULL) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_unum64"), Dz1TdqType_num_u64, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_num64"), Dz1TdqType_num_s64, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_unum32"), Dz1TdqType_num_u32, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_num32"), Dz1TdqType_num_s32, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_unum16"), Dz1TdqType_num_u16, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_num16"), Dz1TdqType_num_s16, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_unum8"), Dz1TdqType_num_u8, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRow_addNum(node->row, Dz1Text("my_num8"), Dz1TdqType_num_s8, NULL, not_null_no_default, errp) == FALSE) ERR_OUT(errp);

        else if ((node->pk = Dz1TdqRowRef_new(errp)) == NULL) ERR_OUT(errp);
        else if (Dz1TdqRowRef_addCol(node->pk, Dz1Text("my_unum64"), node->row, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqRowRef_addCol(node->pk, Dz1Text("my_num64"), node->row, errp) == FALSE) ERR_OUT(errp);

        else if ((*errp = dst->shapes->add(dst->shapes, node)).code) ERR_OUT(errp);
        else
        {
            node = NULL;
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Dz1TdqTblShape_delAndSetNull, (void *)&node);
    }
    return errp->code == 0 ? TRUE : FALSE;;
}

static bool_t _MyStructBBBB_writeRow(Dz1TdqSqlVar **dst, u32_t cnt, MyStructBBBB *src, Dz1Error *errp)
{
    dst[0]->x.u64 = src->my_unum64;
    dst[1]->x.s64 = src->my_num64;
    dst[2]->x.u32 = src->my_unum32;
    dst[3]->x.s32 = src->my_num32;
    dst[4]->x.u16 = src->my_unum16;
    dst[5]->x.s16 = src->my_num16;
    dst[6]->x.u8 = src->my_unum8;
    dst[7]->x.s8 = src->my_num8;

    return errp->code == 0 ? TRUE : FALSE;
}

static Dz1TdqRowSupply MyStructBBBB_writeRow(void *ptr, u32_t row_idx, Dz1TdqSqlVar **dst, u32_t cnt, Dz1Error *errp)
{
    Dz1TdqRowSupply ret = Dz1TdqRowSupply_end;
    if (row_idx == 0)
    {
        if (_MyStructBBBB_writeRow(dst, cnt, (MyStructBBBB *)ptr, errp) == FALSE) ret = Dz1TdqRowSupply_error;
        else ret = Dz1TdqRowSupply_ok;
    }
    return ret;
}

static Dz1TdqRowSupply MyStructBBBB_writeRows(void *ptr, u32_t row_idx, Dz1TdqSqlVar **dst, u32_t cnt, Dz1Error *errp)
{
    Dz1TdqRowSupply ret = Dz1TdqRowSupply_ok;
    Dz1TdqSupplyArg *arg = (Dz1TdqSupplyArg *)ptr;
    if (row_idx < arg->cnt)
    {
        MyStructBBBB **arr = (MyStructBBBB **)arg->arr;
        if (_MyStructBBBB_writeRow(dst, cnt, arr[row_idx], errp) == FALSE) ret = Dz1TdqRowSupply_error;
        else ret = Dz1TdqRowSupply_ok;
    }
    else ret = Dz1TdqRowSupply_end;
    return ret;
}

static void MyStructBBBB_readRow(void *ptr, u32_t idx, Dz1TdqSqlVar **src, SQLLEN *src_stat, u32_t cnt)
{
    DZ1_ERROR_SAFE_VAR(errp, err);
    MyStructBBBBList *dst = (MyStructBBBBList *)ptr;
    MyStructBBBB *node = MyStructBBBB_gen(errp);
    if (node == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(MyStructBBBB_delAndSetNull, (void *)&node);
        if (0) { }
        else
        {
            node->my_unum64 = Dz1TdqSqlVarGetNum(src[0], u64, 0);
            node->my_num64 = Dz1TdqSqlVarGetNum(src[1], s64, 0);
            node->my_unum32 = Dz1TdqSqlVarGetNum(src[2], u32, 0);
            node->my_num32 = Dz1TdqSqlVarGetNum(src[3], s32, 0);
            node->my_unum16 = Dz1TdqSqlVarGetNum(src[4], u16, 0);
            node->my_num16 = Dz1TdqSqlVarGetNum(src[5], s16, 0);
            node->my_unum8 = Dz1TdqSqlVarGetNum(src[6], u8, 0);
            node->my_num8 = Dz1TdqSqlVarGetNum(src[7], s8, 0);
            if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
            else
            {
                node = NULL;
                Dz1Error_set(errp, 0);
            }
        }
        pthread_cleanup_pop(1); // (MyStructAAAA_delAndSetNull, (void *)&node);
    }
}

static Dz1TdqSqlNamedVarList *_MyStructBBBB_nvListGen(MyStructBBBB *src, Dz1Error *errp)
{
    Dz1TdqSqlNamedVarList *ret = NULL;
    if (src == NULL) ERR_SET_OUT(errp, EINVAL);
    else if ((ret = Dz1TdqSqlNamedVarList_new(errp)) == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&ret);
        if (0) { }
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_unum64"), Dz1TdqSqlVarPresent_u64, &src->my_unum64, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_num64"), Dz1TdqSqlVarPresent_s64, &src->my_num64, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_unum32"), Dz1TdqSqlVarPresent_u32, &src->my_unum32, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_num32"), Dz1TdqSqlVarPresent_s32, &src->my_num32, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_unum16"), Dz1TdqSqlVarPresent_u16, &src->my_unum16, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_num16"), Dz1TdqSqlVarPresent_s16, &src->my_num16, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_unum8"), Dz1TdqSqlVarPresent_u8, &src->my_unum8, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlNamedVarList_addNum(ret, Dz1Text("my_num8"), Dz1TdqSqlVarPresent_s8, &src->my_num8, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&ret);
    }
    return ret;
}

static Dz1TdqSqlNamedVarList *MyStructBBBB_nvListGen(MyStructBBBB *src, Dz1Str comma_seprated_names, Dz1Error *err) // (names == NULL | ZeroLen) : All, (names == "@") : All except keys
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1TdqSqlNamedVarList *ret = NULL, *temp = NULL;
    if (src == NULL) ERR_SET_OUT(errp, EINVAL);
    else if ((temp = _MyStructBBBB_nvListGen(src, errp)) == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&temp);
        if (Dz1Str_isVoid(comma_seprated_names) == TRUE)
        {
            ret = temp;
            temp = NULL;
            Dz1Error_set(errp, 0);
        }
        else if (Dz1STRCMP(Dz1Text("@"), comma_seprated_names) == 0)
        {
            Dz1TdqSqlNamedVarList_removeByName(temp, Dz1Text("my_unum64"));
            Dz1TdqSqlNamedVarList_removeByName(temp, Dz1Text("my_num64"));
            ret = temp;
            temp = NULL;
            Dz1Error_set(errp, 0);
        }
        else if ((ret = Dz1TdqSqlNamedVarList_collect(temp, comma_seprated_names, errp)) == NULL) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&temp);
    }
    return ret;
}

static bool_t MyTableA_regTable(Dz1TdqDbScheme *dst, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1TdqTblInstance *node = Dz1TdqTblInstance_new(Dz1Text("my_table_a"), NULL, errp);
    if (node == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1TdqTblInstance_delAndSetNull, (void *)&node);
        if (0) { }
        else if ((node->shape = Dz1TdqTblShapeList_findByName(dst->shapes, Dz1Text("AAAA") )) == NULL) ERR_SET_OUT(errp, ENOENT);
        else if (Dz1TdqDbScheme_appendInstance(dst, node, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqDbScheme_regSimpleQuery(dst, node, errp) == FALSE) ERR_OUT(errp);
        else
        {
            node = NULL;
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Dz1TdqTblInstance_delAndSetNull, (void *)&ret);
    }
    return errp->code == 0 ? TRUE : FALSE;
}


bool_t MyTableA_insert(Dz1TdqDbScheme *scm, MyStructAAAA *row, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    if (scm == NULL || row == NULL) ERR_SET_OUT(errp, EINVAL);
    else if (Dz1TdqDbScheme_insert(scm, Dz1Text("my_table_a"), NULL, MyStructAAAA_writeRow, row, commit, errp) == FALSE) ERR_OUT(errp);
    else Dz1Error_set(errp, 0);
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyTableA_insertA(Dz1TdqDbScheme *scm, MyStructAAAA **arr, u32_t cnt, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    if (scm == NULL || arr == NULL || cnt == 0) ERR_SET_OUT(errp, EINVAL);
    else
    {
        Dz1TdqSupplyArg arg = { arr, cnt };
        if (Dz1TdqDbScheme_insert(scm, Dz1Text("my_table_a"), NULL, MyStructAAAA_writeRows, (void *)&arg, commit, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyTableA_insertL(Dz1TdqDbScheme *scm, MyStructAAAAList *rows, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    u32_t cnt = 0;
    MyStructAAAA **arr = NULL;
    if (scm == NULL || rows == NULL || rows->count(rows) == 0) ERR_SET_OUT(errp, EINVAL);
    else if ((arr = rows->get_array(rows, &cnt, errp)) == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
        if (MyTableA_insertA(scm, arr, cnt, commit, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyTableA_update(Dz1TdqDbScheme *scm, MyStructAAAA *key, MyStructAAAA *row, Dz1Str update_cols_str, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1Str whr = Dz1Text("my_unum64=?");
    Dz1TdqSqlVarArray *args = Dz1TdqSqlVarArray_new(errp);
    if (args == NULL) ERR_OUT(errp);
    else
    {
        Dz1TdqSqlNamedVarList *update_vars = NULL;
        pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);

        if (0) { }

        else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_u64, &key->my_unum64, errp) == FALSE) ERR_OUT(errp);

        else if ((update_vars = MyStructAAAA_nvListGen(row, update_cols_str, errp)) == NULL) ERR_OUT(errp);
        else 
        {
            pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&update_vars);
            if (Dz1TdqDbScheme_update(scm, Dz1Text("my_table_a"), update_vars, whr, args, commit, errp) == FALSE) ERR_OUT(errp);
            else Dz1Error_set(errp, 0);
            pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)update_vars);
        }
        pthread_cleanup_pop(1); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyTableA_delete(Dz1TdqDbScheme *scm, MyStructAAAA *key, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1Str whr = Dz1Text("my_unum64=?");
    Dz1TdqSqlVarArray *args = Dz1TdqSqlVarArray_new(errp);
    if (args == NULL) ERR_OUT(errp);
    else
    {
        Dz1TdqSqlVar *my_unum64 = NULL;
        pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);
        if (0) { }

        else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_u64, &key->my_unum64, errp) == FALSE) ERR_OUT(errp);

        else if (Dz1TdqDbScheme_delete(scm, Dz1Text("my_table_a"), whr, args, commit, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(1); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

MyStructAAAAList *MyTableA_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    MyStructAAAAList *ret = MyStructAAAAList_gen(errp);
    if (ret == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(MyStructAAAAList_delAndSetNull, (void *)&ret);
        if (Dz1TdqDbScheme_select(scm, Dz1Text("my_table_a"), MyStructAAAA_readRow, (void *)ret, whr, args, paging, errp) == FALSE)
        {
            if (errp->code != ENOENT) ERR_OUT(errp);
        }
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (MyStructAAAAList_delAndSetNull, (void *)&ret);
    }
    return ret;
}

static bool_t MyTableB_regTable(Dz1TdqDbScheme *dst, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1TdqTblInstance *node = Dz1TdqTblInstance_new(Dz1Text("my_table_b"), NULL, errp);
    if (node == NULL) ERR_OUT(errp);
    else
    {
        Dz1TdqTblShape *shp = NULL;
        pthread_cleanup_push(Dz1TdqTblInstance_delAndSetNull, (void *)&node);
        if (0) { }
        else if ((node->shape = shp = Dz1TdqTblShapeList_findByName(dst->shapes, Dz1Text("BBBB") )) == NULL) ERR_SET_OUT(errp, ENOENT);
        else if ((*errp = Dz1TdqFKList_append(node->fks, Dz1Text("_TableAFK"), Dz1Text("my_table_a"), NULL, Dz1TdqForeignKeyMode_restrict, Dz1TdqForeignKeyMode_restrict, shp->row, dst->tables, Dz1Text("my_unum64"), NULL)).code) ERR_OUT(errp);
        else if (Dz1TdqDbScheme_appendInstance(dst, node, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqDbScheme_regSimpleQuery(dst, node, errp) == FALSE) ERR_OUT(errp);
        else
        {
            node = NULL;
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Dz1TdqTblInstance_delAndSetNull, (void *)&ret);
    }
    return errp->code == 0 ? TRUE : FALSE;
}


bool_t MyTableB_insert(Dz1TdqDbScheme *scm, MyStructBBBB *row, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    if (scm == NULL || row == NULL) ERR_SET_OUT(errp, EINVAL);
    else if (Dz1TdqDbScheme_insert(scm, Dz1Text("my_table_b"), NULL, MyStructBBBB_writeRow, row, commit, errp) == FALSE) ERR_OUT(errp);
    else Dz1Error_set(errp, 0);
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyTableB_insertA(Dz1TdqDbScheme *scm, MyStructBBBB **arr, u32_t cnt, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    if (scm == NULL || arr == NULL || cnt == 0) ERR_SET_OUT(errp, EINVAL);
    else
    {
        Dz1TdqSupplyArg arg = { arr, cnt };
        if (Dz1TdqDbScheme_insert(scm, Dz1Text("my_table_b"), NULL, MyStructBBBB_writeRows, (void *)&arg, commit, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyTableB_insertL(Dz1TdqDbScheme *scm, MyStructBBBBList *rows, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    u32_t cnt = 0;
    MyStructBBBB **arr = NULL;
    if (scm == NULL || rows == NULL || rows->count(rows) == 0) ERR_SET_OUT(errp, EINVAL);
    else if ((arr = rows->get_array(rows, &cnt, errp)) == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
        if (MyTableB_insertA(scm, arr, cnt, commit, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyTableB_update(Dz1TdqDbScheme *scm, MyStructBBBB *key, MyStructBBBB *row, Dz1Str update_cols_str, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1Str whr = Dz1Text("my_unum64=? AND my_num64=?");
    Dz1TdqSqlVarArray *args = Dz1TdqSqlVarArray_new(errp);
    if (args == NULL) ERR_OUT(errp);
    else
    {
        Dz1TdqSqlNamedVarList *update_vars = NULL;
        pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);

        if (0) { }

        else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_u64, &key->my_unum64, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_s64, &key->my_num64, errp) == FALSE) ERR_OUT(errp);

        else if ((update_vars = MyStructBBBB_nvListGen(row, update_cols_str, errp)) == NULL) ERR_OUT(errp);
        else 
        {
            pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&update_vars);
            if (Dz1TdqDbScheme_update(scm, Dz1Text("my_table_b"), update_vars, whr, args, commit, errp) == FALSE) ERR_OUT(errp);
            else Dz1Error_set(errp, 0);
            pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)update_vars);
        }
        pthread_cleanup_pop(1); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyTableB_delete(Dz1TdqDbScheme *scm, MyStructBBBB *key, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1Str whr = Dz1Text("my_unum64=? AND my_num64=?");
    Dz1TdqSqlVarArray *args = Dz1TdqSqlVarArray_new(errp);
    if (args == NULL) ERR_OUT(errp);
    else
    {
        Dz1TdqSqlVar *my_unum64 = NULL;
        pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);
        if (0) { }

        else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_u64, &key->my_unum64, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_s64, &key->my_num64, errp) == FALSE) ERR_OUT(errp);

        else if (Dz1TdqDbScheme_delete(scm, Dz1Text("my_table_b"), whr, args, commit, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(1); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

MyStructBBBBList *MyTableB_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    MyStructBBBBList *ret = MyStructBBBBList_gen(errp);
    if (ret == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(MyStructBBBBList_delAndSetNull, (void *)&ret);
        if (Dz1TdqDbScheme_select(scm, Dz1Text("my_table_b"), MyStructBBBB_readRow, (void *)ret, whr, args, paging, errp) == FALSE)
        {
            if (errp->code != ENOENT) ERR_OUT(errp);
        }
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (MyStructAAAAList_delAndSetNull, (void *)&ret);
    }
    return ret;
}

static bool_t MyTableC_regTable(Dz1TdqDbScheme *dst, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1TdqTblInstance *node = Dz1TdqTblInstance_new(Dz1Text("my_table_c"), NULL, errp);
    if (node == NULL) ERR_OUT(errp);
    else
    {
        Dz1TdqTblShape *shp = NULL;
        pthread_cleanup_push(Dz1TdqTblInstance_delAndSetNull, (void *)&node);
        if (0) { }
        else if ((node->shape = shp = Dz1TdqTblShapeList_findByName(dst->shapes, Dz1Text("BBBB") )) == NULL) ERR_SET_OUT(errp, ENOENT);
        else if ((*errp = Dz1TdqFKList_append(node->fks, Dz1Text("_TableAFK"), Dz1Text("my_table_a"), Dz1Text("_NUM64_INDEX"), Dz1TdqForeignKeyMode_cascade, Dz1TdqForeignKeyMode_cascade, shp->row, dst->tables, Dz1Text("my_unum64"), NULL)).code) ERR_OUT(errp);
        else if (Dz1TdqDbScheme_appendInstance(dst, node, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqDbScheme_regSimpleQuery(dst, node, errp) == FALSE) ERR_OUT(errp);
        else
        {
            node = NULL;
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(errp->code); // (Dz1TdqTblInstance_delAndSetNull, (void *)&ret);
    }
    return errp->code == 0 ? TRUE : FALSE;
}


bool_t MyTableC_insert(Dz1TdqDbScheme *scm, MyStructBBBB *row, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    if (scm == NULL || row == NULL) ERR_SET_OUT(errp, EINVAL);
    else if (Dz1TdqDbScheme_insert(scm, Dz1Text("my_table_c"), NULL, MyStructBBBB_writeRow, row, commit, errp) == FALSE) ERR_OUT(errp);
    else Dz1Error_set(errp, 0);
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyTableC_insertA(Dz1TdqDbScheme *scm, MyStructBBBB **arr, u32_t cnt, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    if (scm == NULL || arr == NULL || cnt == 0) ERR_SET_OUT(errp, EINVAL);
    else
    {
        Dz1TdqSupplyArg arg = { arr, cnt };
        if (Dz1TdqDbScheme_insert(scm, Dz1Text("my_table_c"), NULL, MyStructBBBB_writeRows, (void *)&arg, commit, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyTableC_insertL(Dz1TdqDbScheme *scm, MyStructBBBBList *rows, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    u32_t cnt = 0;
    MyStructBBBB **arr = NULL;
    if (scm == NULL || rows == NULL || rows->count(rows) == 0) ERR_SET_OUT(errp, EINVAL);
    else if ((arr = rows->get_array(rows, &cnt, errp)) == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(Dz1Memory_cancel, (void *)arr);
        if (MyTableC_insertA(scm, arr, cnt, commit, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(1); // (Dz1Memory_cancel, (void *)arr);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyTableC_update(Dz1TdqDbScheme *scm, MyStructBBBB *key, MyStructBBBB *row, Dz1Str update_cols_str, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1Str whr = Dz1Text("my_unum64=? AND my_num64=?");
    Dz1TdqSqlVarArray *args = Dz1TdqSqlVarArray_new(errp);
    if (args == NULL) ERR_OUT(errp);
    else
    {
        Dz1TdqSqlNamedVarList *update_vars = NULL;
        pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);

        if (0) { }

        else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_u64, &key->my_unum64, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_s64, &key->my_num64, errp) == FALSE) ERR_OUT(errp);

        else if ((update_vars = MyStructBBBB_nvListGen(row, update_cols_str, errp)) == NULL) ERR_OUT(errp);
        else 
        {
            pthread_cleanup_push(Dz1TdqSqlNamedVarList_delAndSetNull, (void *)&update_vars);
            if (Dz1TdqDbScheme_update(scm, Dz1Text("my_table_c"), update_vars, whr, args, commit, errp) == FALSE) ERR_OUT(errp);
            else Dz1Error_set(errp, 0);
            pthread_cleanup_pop(1); // (Dz1TdqSqlNamedVarList_delAndSetNull, (void *)update_vars);
        }
        pthread_cleanup_pop(1); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

bool_t MyTableC_delete(Dz1TdqDbScheme *scm, MyStructBBBB *key, bool_t commit, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    Dz1Str whr = Dz1Text("my_unum64=? AND my_num64=?");
    Dz1TdqSqlVarArray *args = Dz1TdqSqlVarArray_new(errp);
    if (args == NULL) ERR_OUT(errp);
    else
    {
        Dz1TdqSqlVar *my_unum64 = NULL;
        pthread_cleanup_push(Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);
        if (0) { }

        else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_u64, &key->my_unum64, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqSqlVarArray_addNum(args, Dz1TdqSqlVarPresent_s64, &key->my_num64, errp) == FALSE) ERR_OUT(errp);

        else if (Dz1TdqDbScheme_delete(scm, Dz1Text("my_table_c"), whr, args, commit, errp) == FALSE) ERR_OUT(errp);
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(1); // (Dz1TdqSqlVarArray_delAndSetNull, (void *)&args);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

MyStructBBBBList *MyTableC_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    MyStructBBBBList *ret = MyStructBBBBList_gen(errp);
    if (ret == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(MyStructBBBBList_delAndSetNull, (void *)&ret);
        if (Dz1TdqDbScheme_select(scm, Dz1Text("my_table_c"), MyStructBBBB_readRow, (void *)ret, whr, args, paging, errp) == FALSE)
        {
            if (errp->code != ENOENT) ERR_OUT(errp);
        }
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (MyStructAAAAList_delAndSetNull, (void *)&ret);
    }
    return ret;
}

static void CentralEntry_readRow(void *ptr, u32_t idx, Dz1TdqSqlVar **src, SQLLEN *src_stat, u32_t cnt)
{
    DZ1_ERROR_SAFE_VAR(errp, err);
    CentralList *dst = (CentralList *)ptr;
    CentralEntry *node = CentralEntry_gen(errp);
    if (node == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(CentralEntry_delAndSetNull, (void *)&node);
        if (0) { }
        else if (MyBinaryDBIO_read(&node->my_blob, src[3], errp) == FALSE) ERR_OUT(errp);
        else
        {
            node->my_unum64 = Dz1TdqSqlVarGetNum(src[0], u64, 0);
            node->my_unum32 = Dz1TdqSqlVarGetNum(src[1], u32, 0);
            node->my_unum16 = Dz1TdqSqlVarGetNum(src[2], u16, 0);
            node->value = Dz1TdqSqlVarGetNum(src[4], u64, 0);
            if ((*errp = dst->add(dst, node)).code) ERR_OUT(errp);
            else
            {
                node = NULL;
                Dz1Error_set(errp, 0);
            }
        }
        pthread_cleanup_pop(1); // (MyStructAAAA_delAndSetNull, (void *)&node);
    }
}

static bool_t CentralData2_queryReg(Dz1TdqDbScheme *scm, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);

    Dz1TdqQuery *node = Dz1TdqQuery_new(Dz1Text("CentralData2"), NULL, NULL, errp);
    if (node == NULL) ERR_OUT(errp);
    else
    {
        Dz1TdqQryRow *sel = NULL;
        Dz1TdqQueryTblSpec *from = NULL;
        pthread_cleanup_push(Dz1TdqQuery_delAndSetNull, (void *)&node);
        if (0) { }
        else if ((node->from = from = Dz1TdqQueryTblSpec_new(NULL, errp)) == NULL) ERR_OUT(errp);
        else if (Dz1TdqQueryTblSpec_setBiasTbl(from, Dz1Text("my_table_a"), Dz1Text("A"), scm, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqQueryTblSpec_appendJoinTbl(from, Dz1Text("my_table_b"), Dz1Text("B"), Dz1TdqQueryTblJoin_left, Dz1Text("B.my_unum64=A.my_unum64"), scm, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqQueryTblSpec_appendJoinTbl(from, Dz1Text("my_table_c"), Dz1Text("C"), Dz1TdqQueryTblJoin_left, Dz1Text("C.my_unum64=A.my_unum64"), scm, errp) == FALSE) ERR_OUT(errp);

        else if ((node->sel = sel = Dz1TdqQryRow_new(errp)) == NULL) ERR_OUT(errp);
        else if (Dz1TdqQryRow_appendTableCol(sel, Dz1Text("my_unum64"), Dz1Text("A"), Dz1Text("my_unum64"), from, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqQryRow_appendTableCol(sel, Dz1Text("my_unum32"), Dz1Text("B"), Dz1Text("my_unum32"), from, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqQryRow_appendTableCol(sel, Dz1Text("my_unum16"), Dz1Text("C"), Dz1Text("my_unum16"), from, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqQryRow_appendTableCol(sel, Dz1Text("my_blob"), Dz1Text("A"), Dz1Text("my_blob"), from, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqQryRow_appendExprColNum(sel, Dz1TdqType_num_u64, Dz1Text("A.my_unum64 + B.my_unum64 + C.my_unum64"), Dz1Text("value"), errp) == FALSE) ERR_OUT(errp);
        else if ((*errp = scm->queries->add(scm->queries, node)).code) ERR_OUT(errp);
        else
        {
            node = NULL;
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(1); // (Dz1TdqQuery_delAndSetNull, (void *)&node);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

CentralList *CentralData2_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    CentralList *ret = CentralList_gen(errp);
    if (ret == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(CentralList_delAndSetNull, (void *)&ret);
        if (Dz1TdqDbScheme_select(scm, Dz1Text("CentralData2"), CentralEntry_readRow, (void *)ret, whr, args, paging, errp) == FALSE)
        {
            if (errp->code != ENOENT) ERR_OUT(errp);
        }
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (CentralList_delAndSetNull, (void *)&ret);
    }
    return ret;
}

static bool_t CentralData_queryReg(Dz1TdqDbScheme *scm, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);

    Dz1TdqQuery *node = Dz1TdqQuery_new(Dz1Text("CentralData"), NULL, NULL, errp);
    if (node == NULL) ERR_OUT(errp);
    else
    {
        Dz1TdqQryRow *sel = NULL;
        Dz1TdqQueryTblSpec *from = NULL;
        pthread_cleanup_push(Dz1TdqQuery_delAndSetNull, (void *)&node);
        if (0) { }
        else if ((node->from = from = Dz1TdqQueryTblSpec_new(NULL, errp)) == NULL) ERR_OUT(errp);
        else if (Dz1TdqQueryTblSpec_setBiasTbl(from, Dz1Text("my_table_a"), Dz1Text("A"), scm, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqQueryTblSpec_appendJoinTbl(from, Dz1Text("my_table_b"), Dz1Text("B"), Dz1TdqQueryTblJoin_left, Dz1Text("B.my_unum64=A.my_unum64"), scm, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqQueryTblSpec_appendJoinTbl(from, Dz1Text("my_table_c"), Dz1Text("C"), Dz1TdqQueryTblJoin_left, Dz1Text("C.my_unum64=A.my_unum64"), scm, errp) == FALSE) ERR_OUT(errp);

        else if ((node->sel = sel = Dz1TdqQryRow_new(errp)) == NULL) ERR_OUT(errp);
        else if (Dz1TdqQryRow_appendTableCol(sel, Dz1Text("my_unum64"), Dz1Text("A"), Dz1Text("my_unum64"), from, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqQryRow_appendTableCol(sel, Dz1Text("my_unum32"), Dz1Text("B"), Dz1Text("my_unum32"), from, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqQryRow_appendTableCol(sel, Dz1Text("my_unum16"), Dz1Text("C"), Dz1Text("my_unum16"), from, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqQryRow_appendTableCol(sel, Dz1Text("my_blob"), Dz1Text("A"), Dz1Text("my_blob"), from, errp) == FALSE) ERR_OUT(errp);
        else if (Dz1TdqQryRow_appendExprColNum(sel, Dz1TdqType_num_u64, Dz1Text("A.my_unum64 + B.my_unum64 + C.my_unum64"), Dz1Text("value"), errp) == FALSE) ERR_OUT(errp);
        else if ((*errp = scm->queries->add(scm->queries, node)).code) ERR_OUT(errp);
        else
        {
            node = NULL;
            Dz1Error_set(errp, 0);
        }
        pthread_cleanup_pop(1); // (Dz1TdqQuery_delAndSetNull, (void *)&node);
    }
    return errp->code == 0 ? TRUE : FALSE;
}

CentralList *CentralData_select(Dz1TdqDbScheme *scm, Dz1Str whr, Dz1TdqSqlVarArray *args, Dz1TdqPageSpec *paging, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    CentralList *ret = CentralList_gen(errp);
    if (ret == NULL) ERR_OUT(errp);
    else
    {
        pthread_cleanup_push(CentralList_delAndSetNull, (void *)&ret);
        if (Dz1TdqDbScheme_select(scm, Dz1Text("CentralData"), CentralEntry_readRow, (void *)ret, whr, args, paging, errp) == FALSE)
        {
            if (errp->code != ENOENT) ERR_OUT(errp);
        }
        else Dz1Error_set(errp, 0);
        pthread_cleanup_pop(errp->code); // (CentralList_delAndSetNull, (void *)&ret);
    }
    return ret;
}

bool_t sample_tdq_init(Dz1TdqDbScheme *scm, Dz1Error *err)
{
    DZ1_ERROR_SAFE_PTR(errp, err);
    if (0) { }
    else if (AAAA_regShape(scm, errp) == FALSE) ERR_OUT(errp);
    else if (BBBB_regShape(scm, errp) == FALSE) ERR_OUT(errp);
    else if (MyDataRow_regShape(scm, errp) == FALSE) ERR_OUT(errp);

    else if (MyDataTbl_regTable(scm, errp) == FALSE) ERR_OUT(errp);
    else if (MyTableA_regTable(scm, errp) == FALSE) ERR_OUT(errp);
    else if (MyTableB_regTable(scm, errp) == FALSE) ERR_OUT(errp);
    else if (MyTableC_regTable(scm, errp) == FALSE) ERR_OUT(errp);

    else if (CentralData_queryReg(scm, errp) == FALSE) ERR_OUT(errp);
    else if (CentralData2_queryReg(scm, errp) == FALSE) ERR_OUT(errp);

    else Dz1Error_set(errp, 0);
    return errp->code == 0 ? TRUE : FALSE;
}
