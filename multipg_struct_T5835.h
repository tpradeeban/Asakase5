#ifndef ___TEST_MULTIPG_STRUCT_H_
#define ___TEST_MULTIPG_STRUCT_H_
#include "test.h"

#define MULTIPGARG testarg->multipgarg

enum iom_asg { ALL=0, LTD=1, USECASE=2 };	//IOM assignment: LTD=Limited, USE:UseCase(<-not yet used)

typedef struct _TEST_multipg {
  int  max_pg;
  void (*multipg_func)();
  enum iom_asg flg_asg;
} TEST_multipgarg;

#endif // ___TEST_MULTIPG_STRUCT_H_
