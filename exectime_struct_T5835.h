#ifndef ___TEST_EXECTIME_STRUCT_H_
#define ___TEST_EXECTIME_STRUCT_H_
#include "test.h"

#define EXECTIMEARG testarg->exectimearg

typedef struct{
  int target_testno;
  char target_mci[STR_MAX];
  CheckButton average;
  CheckButton all;
  double exp;
  double limit_rate;
  double limit_abs;
}TEST_exectimearg;

#endif // ___TEST_EXECTIME_STRUCT_H_

