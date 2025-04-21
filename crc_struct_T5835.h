#ifndef ___TEST_CRC_STRUCT_H_
#define ___TEST_CRC_STRUCT_H_
#include "test.h"

#define CRCARG testarg->crcarg

#define CRC_CRC   (0)
#define CRC_CRCD  (1)
#define CRC_CRCDM (2)

#define CRC_DDR4	(0)
#define CRC_GDDR5	(1)
#define CRC_DDR5	(2)
#define CRC_LPDDR5	(3)

#define CRC_LOW		(0)
#define CRC_HIGH	(1)

typedef struct{
  RadioButton ilmode;
  DSlider rate;
  int crcmode;
  CheckButton dinv;
  int ddrtype;
  int m;
  USlider bst;
  int fix;
  int actmode;
  void (*pinfunc)();
  USlider (*crcfunc)();
  char mpat[STR_MAX];
  USlider pc;
  int exp;
}TEST_crcarg;

#endif // ___TEST_CRC_STRUCT_H_

