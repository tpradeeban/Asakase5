#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "test.h"
#include "UTSC.h"
#include "test_struct.h"
#include "mcw.h"

#define DEBUG 1

int DIAGPC=0;
int DIAGCHK=0;
static void diagpclockskip(TEST_testitem *testarg);
static void diagpcfreeskip(TEST_testitem *testarg);
static int diagpc_check();

int MBSTA=0;
int MBCHK=0;
static void mbfreeskip(TEST_testitem *testarg);
static int mbsta_check();

void mcw_check( TEST_testitem *testarg )
{
    if(MBCHK==0){
        MBSTA=mbsta_check();
        if(DEBUG==1){
            if(MBSTA==0){printf("MB:OFF\n");fflush(stdout);}
            if(MBSTA==1){printf("MB:ON\n");fflush(stdout);}
        }
        if(MBSTA==0){mbfreeskip(testarg); return;}
        MBCHK=1;
    }

    if(DIAGCHK==0){
        DIAGPC=diagpc_check();
        if(DEBUG==1){
            if(DIAGPC == 1){printf("DIAG-PC:ON\n"); fflush(stdout);}
            if(DIAGPC == 0){printf("DIAG-PC:OFF\n");fflush(stdout);}
        }
        if(DIAGPC == 1){diagpclockskip(testarg); return; }
        DIAGCHK=1;
    }

    int i,j,selblk,clrblk,chkblk;
    int result=0;
	int test_result=0;
    USlider setbit=0;
    USlider getbit=0;
    USlider getstn=0;

    UTTB_HReg_Write(0x048CA000, 0x7F); //STLT_UTL_ONPBMB_SELECT ON
    UTL_WaitTime(1);

    AuxDutSignalHandle ads_h;
	ads_h=UTL_GetAuxDutSignalHandle();

    for(i=1; i<=MCWARG.sta_max; i++){
        UTL_SetAuxDutSignalStationNumber(ads_h, i );
        UTL_SetAuxDutSignalAllStation   (ads_h, MCWARG.aps_onoff);

        selblk=0;
        for(selblk=1; selblk<=MCWARG.blk_max; selblk++){
            if(DEBUG==1){printf("Check Block =%d\n",selblk);}

            clrblk=0;
            for(clrblk=1; clrblk<=MCWARG.blk_max; clrblk++){
                UTL_SetAuxDutSignalData(ads_h, 0); 
                UTL_SendAuxDutSignal   (ads_h, MCWARG.mcw_mode, clrblk); 
            }

            j=0;
            setbit=0x1;
            for(j=1; j<=MCWARG.bit_max; j++){
                UTL_SetAuxDutSignalData(ads_h, setbit); 
                UTL_SendAuxDutSignal   (ads_h, MCWARG.mcw_mode, selblk); 
                UTL_UpdateAuxDutSignal (ads_h, MCWARG.mcw_mode, selblk);
                UTL_GetAuxDutSignalStationNumber(ads_h, &getstn);
                UTL_GetAuxDutSignalData(ads_h, &getbit); 

                if(setbit==getbit){
                    result=0;
                    if(DEBUG==1){printf ("STN = %d Block = %d setbit = %04x getbit = %04x PASS****\n", getstn, selblk, setbit, getbit); fflush(stdout);}
                }else{
                    result=1;
                    if(DEBUG==1){printf ("STN = %d Block = %d setbit = %04x getbit = %04x ****FAIL\n", getstn, selblk, setbit, getbit); fflush(stdout);}
                }
                if(result==1){test_result=1;}

                chkblk=0;
                for(chkblk=1; chkblk<=MCWARG.blk_max; chkblk++){
                    if(selblk != chkblk){
                        UTL_UpdateAuxDutSignal(ads_h, MCWARG.mcw_mode, chkblk);
                        UTL_GetAuxDutSignalStationNumber(ads_h, &getstn);
                        UTL_GetAuxDutSignalData(ads_h, &getbit); 
                        if(getbit==0){
                            result=0;
                            if(DEBUG==1){printf ("STN = %d Block = %d chkbit = %04x getbit = %04x PASS****\n", getstn, chkblk, 0, getbit); fflush(stdout);}
                        }
                        if(getbit!=0){
                            result=1;
                            if(DEBUG==1){printf ("STN = %d Block = %d chkbit = %04x getbit = %04x ****FAIL\n", getstn, chkblk, 0, getbit); fflush(stdout);}
                        }
                        if(result==1){test_result=1;}
                   }
                }
                setbit *= 2;
            }
        }
    }
    UTL_DeleteHandle(ads_h );

    UTTB_HReg_Write(0x048CA000, 0x00); //STLT_UTL_ONPBMB_SELECT OFF
    UTL_WaitTime(1);

    if(test_result==0){testresult_pass4alldut(UTL_ReadTestName());}
    if(test_result==1){testresult_fail4alldut(UTL_ReadTestName());}
}

static int diagpc_check(void)
{
    UTTB_HReg_Write(0x048CA000, 0x7F); //STLT_UTL_ONPBMB_SELECT ON
    UTL_WaitTime(1);

    int rdata;
    int result=0;
    int snddata=0;
    int getdata=0;
    snddata =snddata  | (0x1 << (1 - 1)); getdata= snddata  | (0x1 << (4 - 1)); 
    AuxDutSignalHandle ads_h=UTL_GetAuxDutSignalHandle();
    UTL_SetAuxDutSignalStationNumber(ads_h, UTL_ReadStationNumber());
    UTL_SetAuxDutSignalData         (ads_h, snddata );
    UTL_SendAuxDutSignal            (ads_h, UT_AUXDUTSIGNAL_MCW, 1 ); 
    UTL_UpdateAuxDutSignal          (ads_h, UT_AUXDUTSIGNAL_MCW, 1 ); 
    UTL_GetAuxDutSignalData         (ads_h, &rdata );
    if(rdata==getdata){result=1;}
//    if(DEBUG==1){printf("send:%8x exp:%8x get:%8x \n",snddata,getdata,rdata);}
    UTL_DeleteHandle                (ads_h);

    UTTB_HReg_Write(0x048CA000, 0x00); //STLT_UTL_ONPBMB_SELECT OFF
    UTL_WaitTime(1);

    return result;
}

static int mbsta_check(void)
{
    int mb_result=0;
    mb_result=UTTB_HReg_Read(0x04832000); //STLT_MB_SENSE_READ
    UTL_WaitTime(1);
    return mb_result;
}

static void diagpclockskip(TEST_testitem *testarg)
{
     testarg->skipreason = TEST_SKIP_DIAGPB_LOCK;
     printf("\n%-32s",UTL_ReadTestName());
     printf(" ---ON_DIAGPC_SKIP"); 
}

static void diagpcfreeskip(TEST_testitem *testarg)
{
     testarg->skipreason = TEST_SKIP_DIAGPB_FREE;
     printf("\n%-32s",UTL_ReadTestName());
     printf(" ---OFF_DIAGPC_SKIP"); 
}

static void mbfreeskip(TEST_testitem *testarg)
{
     testarg->skipreason = TEST_SKIP_MB_FREE;
     printf("\n%-32s",UTL_ReadTestName());
     printf(" ---OFF_MB_SKIP"); 
}