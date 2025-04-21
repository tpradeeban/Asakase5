#ifndef ___TEST_FCSM_STRUCT_H_
#define ___TEST_FCSM_STRUCT_H_
#include "test.h"

#define FCSMARG testarg->fcsmarg

typedef struct _TEST_fcsmarg{
    int  ilmode;
    char mpat[STR_MAX];
    int  pc;    
    DSlider rate;
    void (*post)(USlider *dut_res);
    int  afmxfer_cnt;         //afmxfer count(MAX:32M-1)
    RadioButton captdat;      //UT_FCSM_ECCORCOUNT(1),UTFCSM_ECCTOTALCOUNT(1)
    RadioButton child;       //0(A1) or 1(A2) or 2(A1A2 Both)
    int ddr_mode;            //DDR Mode  0 or 1
    RadioButton sector;
    RadioButton eccsig;      //ECC Enable Sig
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
}TEST_fcsmarg;

#endif // ___TEST_FCSM_STRUCT_H_

