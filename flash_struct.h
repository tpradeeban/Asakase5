#ifndef ___TEST_FLASH_STRUCT_H_
#define ___TEST_FLASH_STRUCT_H_
#include "test.h"

#define FLASHARG testarg->flasharg

typedef struct{
    RadioButton ilmd;
    char *patname;
	char *fmode;  //RadioButton
    char *hmode;  //RadioButton
    Slider flmt;
    USlider rgidx8;
    int ubmno;
    int testcond;
}TEST_flasharg;

#endif //___TEST_FLASH_STRUCT_H_