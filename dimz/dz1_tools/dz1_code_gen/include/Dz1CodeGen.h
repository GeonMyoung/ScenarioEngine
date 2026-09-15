#ifndef DZ1_CODE_GEN_H
#define DZ1_CODE_GEN_H

#include <Dz1CodeGenDef.h>

DZ1_CPPLINK extern Dz1CodeGenSetupTable listCodeGenSetupTable[];
DZ1_CPPLINK Dz1Error Dz1CodeGen_listGen(str_t *dst, Dz1CodeGenListType type, ...);

DZ1_CPPLINK Dz1Error Dz1CodeGenListCtrl_gen(str_t path, str_t _name, bool_t isRefList, bool_t useUnicode,
											str_t list_type, str_t entry_type, str_t tdc_name, str_t parent_calss,
											Dz1CodeGenListColumnList *columns);

DZ1_CPPLINK extern Dz1CodeGenSetupTable stubCodeGenSetupTable[];
DZ1_CPPLINK Dz1Error Dz1CodeGen_stubGen(str_t *dst, Dz1CodeGenStubType type, ...);

DZ1_CPPLINK extern Dz1CodeGenSetupTable parserCodeGenSetupTable[];
DZ1_CPPLINK Dz1Error Dz1CodeGen_parserGen(str_t *dst, Dz1CodeGenParserType type, ...);

DZ1_CPPLINK extern Dz1CodeGenSetupTable shellCodeGenSetupTable[];
DZ1_CPPLINK Dz1Error Dz1CodeGen_shellGen(str_t *dst, Dz1CodeGenShellType type, ...);
#endif