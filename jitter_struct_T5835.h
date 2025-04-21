#ifndef ___TEST_JITTER_STRUCT_H_
#define ___TEST_JITTER_STRUCT_H_
#include "test.h"

#define JITTERARG testarg->jitterarg

typedef struct{
  RadioButton ilmode;
  DSlider rate;
  CheckButton ddr;
  DSlider vih;
  DSlider vil;
  DSlider vt;
  double time_window;
  int pincnt;
  void (*pinlist)();
  void (*pincond)();
  void (*prefunc)();
  DSlider step;
  void (*timing)();
  void (*level)();
  char mpat[STR_MAX];
  USlider pc;
}TEST_jitterarg;

#endif // ___TEST_JITTER_STRUCT_H_

