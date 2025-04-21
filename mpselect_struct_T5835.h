#ifndef ___TEST_MPSEL_STRUCT_H_
#define ___TEST_MPSEL_STRUCT_H_
#include "test.h"

#define MPSELARG testarg->mpselarg

typedef struct _TEST_mpselarg{
    int  ilmode;
    char mpat[STR_MAX];
    DSlider rate;
    DSlider vterm;
    int pind;   
    int exp_p;
    void (*post)(struct _TEST_mpselarg);
    void (*post2)(int, int);
    void (*pg_run)();
    
}TEST_mpselarg;

#endif // ___TEST_MPSEL_STRUCT_H_

