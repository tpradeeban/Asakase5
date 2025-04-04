#ifndef ___TEST_FCM_STRUCT_H_
#define ___TEST_FCM_STRUCT_H_
#include "test.h"

#define FCMARG testarg->fcmarg

typedef struct{
  int ilmode;
  CheckButton ddrmode;
  USlider burstlength;
  RadioButton fcmaction;
  USlider storecnt;
  RadioButton fcmrate;
  double rate;
  CheckButton allchild;
  RadioButton child;
  CheckButton allpin;
  int xbits;
  int ybits;
  RadioButton storeinh;
  CheckButton realtimecount;
  CheckButton pfcnoclear;
  CheckButton allbit;
  void (*config)();
  void (*pincond)();
  int cpedelay;
  void (*premeas)();
  char mpat[STR_MAX];
  int  pc;
  void (*postmeas)();
  double failratio;
  int fmbitcomp; //for fcm.c internal use
}TEST_fcmarg;

#endif // ___TEST_FCM_STRUCT_H_

