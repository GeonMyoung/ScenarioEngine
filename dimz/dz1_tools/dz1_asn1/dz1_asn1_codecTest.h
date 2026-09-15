#ifndef DZ1_ASN1_CODEC_TEST_H
#define DZ1_ASN1_CODEC_TEST_H

#include "dz1_asn1_codecTest_util.h"
																										//                       {15} <- reserved
DZ1_CPPLINK void	 cmd_ber_simple_numeric(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[]);		// 1 2        9 10
DZ1_CPPLINK void	 cmd_ber_simple_binary(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[]);		//    3 4
DZ1_CPPLINK void	 cmd_ber_simple_string(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[]);		//	        7                   18 19 20 21 22     25 26 27
DZ1_CPPLINK void	 cmd_ber_simple_unicode(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[]);		//			        12                                     28  30
DZ1_CPPLINK void	 cmd_ber_simple_time(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[]);		//                     [14]                   23 24             [31 32 33 34]
DZ1_CPPLINK void	 cmd_ber_simple_exclusive(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[]);	//       5 6          13
DZ1_CPPLINK void	 cmd_exp_external_native(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[]);	//           8             (16)
DZ1_CPPLINK void	 cmd_exp_external_instance(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[]);	//           8             (16)
DZ1_CPPLINK void	 cmd_ber_exp_pdv(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[]);			//                11       (16)
DZ1_CPPLINK void	 cmd_ber_exp_charstring(void *ptr, Dz1Str parent_cmd, int argc, Dz1Str argv[]);		//                         (16)                              29
// some_set_test_fumc();																				//                            17 
#endif
