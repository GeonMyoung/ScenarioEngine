#ifndef SAMPLE_TEST_H_LOCAL
#define SAMPLE_TEST_H_LOCAL

#include "sample.h"
DZ1_CPPLINK bool_t	 sample_test_by_name(str_t name, bool_t verbose, Dz1Error *err);
DZ1_CPPLINK bool_t	 sample_test_by_idx(u32_t idx, bool_t verbose, Dz1Error *err);
DZ1_CPPLINK void	 sample_test_dump(int tab);
#endif
