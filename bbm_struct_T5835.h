#ifndef ___TEST_BBM_STRUCT_H_
#define ___TEST_BBM_STRUCT_H_
#include "test.h"

#define BBMARG testarg->bbmarg

typedef struct _TEST_bbmarg{
    int  ilmode;
    char mpat[STR_MAX];
    int  pc;    
    DSlider rate;
    void (*post)(struct _TEST_bbmarg);
    RadioButton mode;
    RadioButton captdat;
    RadioButton dutgrp;   //0(A1) or 1(A2)
    int disp_data;        //Display 0 or 1
    RadioButton sector;
    RadioButton eccjdg;
    USlider ecclmt;
    
#if 0
    RadioButton fcmrate;
    double rate;
    void (*levelcond)();
    void (*timingcond)();
    void (*pincond)();
    void (*premeas)();
    void (*postmeas)();
#endif
}TEST_bbmarg;

#endif // ___TEST_BBM_STRUCT_H_

