#ifndef ___TEST_BURST_STRUCT_H_
#define ___TEST_BURST_STRUCT_H_
#include "test.h"

#define BURSTARG testarg->burstarg

typedef struct{
  char mpat[STR_MAX];
  int  pc_addr;
  DSlider hlimit;
  DSlider llimit;
  int  exp;
}TEST_burstarg;

#endif // ___TEST_BURST_STRUCT_H_

