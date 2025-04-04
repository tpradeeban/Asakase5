#ifndef ___TEST_DRCP_STRUCT_H_
#define ___TEST_DRCP_STRUCT_H_
#include "test.h"

#define DRCPARG testarg->drcparg

typedef struct{
  DSlider dr_vi;
  DSlider cp_vt;
  int exphl;
}TEST_drcparg;

#endif // ___TEST_DRCP_STRUCT_H_

