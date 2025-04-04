#ifndef ___TEST_HV_STRUCT_H_
#define ___TEST_HV_STRUCT_H_
#include "test.h"

#define HVARG testarg->hvarg

typedef struct{
    RadioButton mmode;
    double vih;
    double u_lmt;
    CheckButton u_onoff;
    double l_lmt;
    CheckButton l_onoff;
    char test[64];
    int exp_f;
    int exp_hf;
    int exp_lf;
}TEST_hvarg;

#endif // ___TEST_HV_STRUCT_H_

