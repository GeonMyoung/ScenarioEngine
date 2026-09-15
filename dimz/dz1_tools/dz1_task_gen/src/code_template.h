#ifndef CODE_TEMPLATE_H_LOCAL
#define CODE_TEMPLATE_H_LOCAL

#include "code_gen_env.h"
#include "txt_util.h"

#ifndef UNIX_SYSTEM // modified by gm 20230602 - extern value
DZ1_CPPLINK Dz1Str lib_def2[];
DZ1_CPPLINK Dz1Str lib_main_hdr2[];
DZ1_CPPLINK Dz1Str lib_main_src2[];
DZ1_CPPLINK Dz1Str lib_test_src2[];

DZ1_CPPLINK Dz1Str task_def2[];
DZ1_CPPLINK Dz1Str task_arg_def2[];
DZ1_CPPLINK Dz1Str task_env_def2[];
DZ1_CPPLINK Dz1Str task_timer_def2[];
DZ1_CPPLINK Dz1Str task_timer_util_hdr2[];
DZ1_CPPLINK Dz1Str task_timer_util_src2[];
DZ1_CPPLINK Dz1Str task_msg_hdr2[];
DZ1_CPPLINK Dz1Str task_msgs_def2[];
DZ1_CPPLINK Dz1Str task_main_hdr2[];
DZ1_CPPLINK Dz1Str task_main_src2[];
DZ1_CPPLINK Dz1Str task_test_src2[];

DZ1_CPPLINK Dz1Str vc90_library_proj[];
DZ1_CPPLINK Dz1Str vc90_task_proj[];
DZ1_CPPLINK Dz1Str vc90_test_proj[];
#else // UNIX_SYSTEM
DZ1_CPPLINK_VAR Dz1Str lib_def2[];
DZ1_CPPLINK_VAR Dz1Str lib_main_hdr2[];
DZ1_CPPLINK_VAR  Dz1Str lib_main_src2[];
DZ1_CPPLINK_VAR  Dz1Str lib_test_src2[];

DZ1_CPPLINK_VAR  Dz1Str task_def2[];
DZ1_CPPLINK_VAR  Dz1Str task_arg_def2[];
DZ1_CPPLINK_VAR  Dz1Str task_env_def2[];
DZ1_CPPLINK_VAR  Dz1Str task_timer_def2[];
DZ1_CPPLINK_VAR  Dz1Str task_timer_util_hdr2[];
DZ1_CPPLINK_VAR  Dz1Str task_timer_util_src2[];
DZ1_CPPLINK_VAR  Dz1Str task_msg_hdr2[];
DZ1_CPPLINK_VAR  Dz1Str task_msgs_def2[];
DZ1_CPPLINK_VAR  Dz1Str task_main_hdr2[];
DZ1_CPPLINK_VAR  Dz1Str task_main_src2[];
DZ1_CPPLINK_VAR  Dz1Str task_test_src2[];

DZ1_CPPLINK_VAR  Dz1Str vc90_library_proj[];
DZ1_CPPLINK_VAR  Dz1Str vc90_task_proj[];
DZ1_CPPLINK_VAR  Dz1Str vc90_test_proj[];
#endif // UNIX_SYSTEM

DZ1_CPPLINK bool_t vc90_solution(FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err);

DZ1_CPPLINK bool_t _vs2022_task_proj(   FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err);
DZ1_CPPLINK bool_t _vs2022_task_filters(FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err);

DZ1_CPPLINK bool_t _vs2022_lib_proj(   FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err);
DZ1_CPPLINK bool_t _vs2022_lib_filters(FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err);

DZ1_CPPLINK bool_t _vs2022_test_proj(   FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err);
DZ1_CPPLINK bool_t _vs2022_test_filters(FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err);

DZ1_CPPLINK bool_t _vs2022_sln(FILE *fp, GenEnv *env, Dz1Str work_path_abs, Dz1Error *err);

#endif
