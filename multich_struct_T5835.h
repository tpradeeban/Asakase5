#ifndef ___TEST_MULTICH_STRUCT_H_
#define ___TEST_MULTICH_STRUCT_H_
#include "test.h"

#define MULTICHARG testarg->multicharg

typedef struct _TEST_multicharg{
    int  ilmode;
    char mpat[STR_MAX];
    int  pc;    
    DSlider rate;
	int afmxfer_cnt;
    USlider limit;          //BBM,FCSM ECC Limit , FLASH Flash counter limit
	RadioButton sector;
	USlider dutchcnt;	//
	USlider dutch;	//
//    RadioButton dutch;		//0(DutCh-0) or 1(DutCh-1) or 2(DutCh-2) or 3(DutCh-3)
    RadioButton dutgrp;		//0(A1) or 1(A2) or 2(A1A2 Both)
    int funblk;				//Function Block(1/2/3/4 = P1-18,P65-82,P129-146,P193-210) 
    int ubmno;
    int ubmjudge;
}TEST_multicharg;

#endif // ___TEST_MULTICH_STRUCT_H_

