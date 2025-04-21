#ifndef ___TEST_DBM_STRUCT_H_
#define ___TEST_DBM_STRUCT_H_
#include "test.h"

#define DBMARG testarg->dbmarg

typedef struct{
  int ilmode;
  DSlider rate;
  USlider bitsize;
  USlider checksize;
  CheckButton ddrmode;
  RadioButton dbmmode;
  CheckButton dcm;
  char mpat[STR_MAX];
  USlider pc;
  RadioButton bitmode; //for dbm.c internal use
}TEST_dbmarg;

#endif // ___TEST_DBM_STRUCT_H_

