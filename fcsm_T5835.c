#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "UTSC.h"
#include "test.h"
#include "test_struct.h"
#include "fcsm.h"
#include "common.h"

#define DEBUG 0

#define V *1.0
#define ms *1.0e-3
#define us *1.0e-6
#define ns *1.0e-9
#define mA *1.0e-3
#define uA *1.0e-6
#define nA *1.0e-9

void fcsm_ilmode(RadioButton ilmd)
{
    IlModeHandle ilmh = UTL_GetIlModeHandle();
    UTL_SetIlMode   (ilmh, ilmd);
    UTL_SendIlMode  (ilmh);
    UTL_DeleteHandle(ilmh);

}

void fcsm_pin_list(void)
{
    const int ptyp[] = { UT_SOCKET_PINTYPE_IO, UT_SOCKET_PINTYPE_DR };
    const int ptypcnt = sizeof(ptyp)/sizeof(ptyp[0]);
    int ptypidx;
    int *plst[ptypcnt], pcnt[ptypcnt], i;

    int pincount = 0;

    for (ptypidx=0; ptypidx<ptypcnt; ptypidx++){
        if (UTSOCK_Info_GetDutPinList(ptyp[ptypidx], &plst[ptypidx], &pcnt[ptypidx])!=UTSOCK_OK){
            fputs("ERROR: UTSOCK_Info_GetDutPinList returns non-UTSOCK_OK",stderr);
            UTL_Stop();
        }
        pincount += pcnt[ptypidx];
    }
    printf("[DEBUG]pincount = %d\n", pincount);
    
    
    UTL_CreatePinList ("IOPIN");
    UTL_SetPinType    ("IOPIN",UT_PINTYPE_PIN);
    for (i=0; i<pcnt[0]; i++) UTL_AddPinNumber ("IOPIN", plst[0][i] );
    if (pcnt[1]) {
       fputs("ERROR: UT_SOCKET_PINTYPE_DR exists",stderr);
       UTL_Stop();
    }

}

//void fcsm_pin_list_multi(void)
//{
//    const int ptyp[] = { UT_SOCKET_PINTYPE_IO, UT_SOCKET_PINTYPE_DR };
//    const int ptypcnt = sizeof(ptyp)/sizeof(ptyp[0]);
//    int ptypidx;
//    int *plst[ptypcnt], pcnt[ptypcnt], i;
//
//    int pincount = 0;
//
//    for (ptypidx=0; ptypidx<ptypcnt; ptypidx++){
//        if (UTSOCK_Info_GetDutPinList(ptyp[ptypidx], &plst[ptypidx], &pcnt[ptypidx])!=UTSOCK_OK){
//            fputs("ERROR: UTSOCK_Info_GetDutPinList returns non-UTSOCK_OK",stderr);
//            UTL_Stop();
//        }
//        pincount += pcnt[ptypidx];
//    }
//    printf("[DEBUG]pincount = %d\n", pincount);
//    
//
//	UTL_CreatePinList ("IOPIN0");
//	UTL_SetPinType    ("IOPIN0",UT_PINTYPE_PIN);
//	for (i=1; i<=8 ; i++) UTL_AddPinNumber ("IOPIN0", i );
//	UTL_CreatePinList ("IOPIN1");
//	UTL_SetPinType    ("IOPIN1",UT_PINTYPE_PIN);
//	for (i=9; i<=16; i++) UTL_AddPinNumber ("IOPIN1", i );
//	UTL_CreatePinList ("IOPINA");
//	UTL_SetPinType    ("IOPINA",UT_PINTYPE_PIN);
//	UTL_AppendPinList ("IOPINA", "IOPIN0" );
//	UTL_AppendPinList ("IOPINA", "IOPIN1" );
//
//}

void fcsm_pin_list_multi(int dutchcnt)
{
    const int ptyp[] = { UT_SOCKET_PINTYPE_IO, UT_SOCKET_PINTYPE_DR };
    const int ptypcnt = sizeof(ptyp)/sizeof(ptyp[0]);
    int ptypidx;
    int *plst[ptypcnt], pcnt[ptypcnt], i;

    int pincount = 0;

    for (ptypidx=0; ptypidx<ptypcnt; ptypidx++){
        if (UTSOCK_Info_GetDutPinList(ptyp[ptypidx], &plst[ptypidx], &pcnt[ptypidx])!=UTSOCK_OK){
            fputs("ERROR: UTSOCK_Info_GetDutPinList returns non-UTSOCK_OK",stderr);
            UTL_Stop();
        }
        pincount += pcnt[ptypidx];
    }
    printf("[DEBUG]pincount = %d\n", pincount);
    

	if(dutchcnt==2){
    	UTL_CreatePinList ("IOPIN0");
    	UTL_SetPinType    ("IOPIN0",UT_PINTYPE_PIN);
    	for (i=1; i<=8 ; i++) UTL_AddPinNumber ("IOPIN0", i );
    	UTL_CreatePinList ("IOPIN1");
    	UTL_SetPinType    ("IOPIN1",UT_PINTYPE_PIN);
    	for (i=9; i<=16; i++) UTL_AddPinNumber ("IOPIN1", i );
    	UTL_CreatePinList ("IOPINA");
    	UTL_SetPinType    ("IOPINA",UT_PINTYPE_PIN);
    	UTL_AppendPinList ("IOPINA", "IOPIN0" );
    	UTL_AppendPinList ("IOPINA", "IOPIN1" );
	}	

}

void fcsm_power_seq(void)
{
    printf("[DEBUG]%s\n",__func__);
    PowerSeqHandle psh = UTL_GetPowerSeqHandle();
    UTL_AddPowerSeqOthers  (psh, 1);
    UTL_SetPowerSeqWaitTime(psh, 1, 5 ms);
    UTL_SendPowerSeq(psh);
    UTL_DeleteHandle(psh);
}

/*
 * pin_condition
 *   When dr-cp DSA is used (e.g. pincount = 8), DRPINs
 *   are fixed to low level for bad blocks
 *
 */
void fcsm_pin_condition(int ddr)
{
    int i;
    int dutblock;

    PinHandle tesph = UTL_GetPinHandle();

    printf("[DEBUG]%s\n",__func__);

    UTL_SetPinViNumber     (tesph, 1);
    UTL_SetPinDrWaveform   (tesph, UT_WAV_FIXL);
    UTL_SetPinDrClock      (tesph, UT_PIN_BCLK, 1);
    UTL_SetPinDrClock      (tesph, UT_PIN_CCLK, 1);
    UTL_SetPinIoCtrl       (tesph, UT_ON);
    UTL_SetPinVoNumber     (tesph, 1);
    UTL_SetPinVtNumber     (tesph, 1);
    UTL_SetPinTerm         (tesph, UT_ON);
    UTL_SetPinDreNumber    (tesph, 1);
    UTL_SetPinDreWaveform  (tesph, UT_DREWAV_NRZ);
    UTL_SetPinDreClock     (tesph, 1); 
    UTL_AddPinStrbCpeNumber(tesph, 1, 1);
    UTL_AddPinExpStrbNumber(tesph, 1, UT_PIN_EXP_A);  
    if(ddr==1){
      UTL_AddPinStrbCpeNumber(tesph, 2, 1);
      UTL_AddPinExpStrbNumber(tesph, 2, UT_PIN_EXP_B); 
    }
    for ( dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++)
    {
           UTL_ClearPinPdsA(tesph);
           UTL_ClearPinPdsB(tesph);
           for ( i=1; i<=SOCKET.dutblock_iopin_count[dutblock]; i++ )
           {
               UTL_AddPinPdsA  (tesph, UT_SIG_C(i), 1);
               if(ddr==1){
                  UTL_AddPinPdsB  (tesph, UT_SIG_C(i), 1);
               }
           }
           UTL_SendPin(tesph, SOCKET.dutblock_iopinlist[dutblock] );
    }

    UTL_DeleteHandle(tesph);
}

void fcsm_pin_condition_multi(int ddr)
{
    int i;
    int j=0;
    int dutblock;

    PinHandle tesph = UTL_GetPinHandle();

    printf("[DEBUG]%s\n",__func__);

    UTL_SetPinViNumber     (tesph, 1);
    UTL_SetPinDrWaveform   (tesph, UT_WAV_FIXL);
    UTL_SetPinDrClock      (tesph, UT_PIN_BCLK, 1);
    UTL_SetPinDrClock      (tesph, UT_PIN_CCLK, 1);
    UTL_SetPinIoCtrl       (tesph, UT_ON);
    UTL_SetPinVoNumber     (tesph, 1);
    UTL_SetPinVtNumber     (tesph, 1);
    UTL_SetPinTerm         (tesph, UT_ON);
    UTL_SetPinDreNumber    (tesph, 1);
    UTL_SetPinDreWaveform  (tesph, UT_DREWAV_NRZ);
    UTL_SetPinDreClock     (tesph, 1); 
    UTL_AddPinStrbCpeNumber(tesph, 1, 1);
    UTL_AddPinExpStrbNumber(tesph, 1, UT_PIN_EXP_A);  
    if(ddr==1){
      UTL_AddPinStrbCpeNumber(tesph, 2, 1);
      UTL_AddPinExpStrbNumber(tesph, 2, UT_PIN_EXP_B); 
    }
    for ( dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++)
    {
           UTL_ClearPinPdsA(tesph);
           UTL_ClearPinPdsB(tesph);
           for ( i=1; i<=SOCKET.dutblock_iopin_count[dutblock]; i++ )
           {
               UTL_AddPinPdsA  (tesph, UT_SIG_C(j), 1);
               if(ddr==1){
                  UTL_AddPinPdsB  (tesph, UT_SIG_C(j), 1);
               }
           }
           UTL_SendPin(tesph, SOCKET.dutblock_iopinlist[dutblock] );
    }

    UTL_DeleteHandle(tesph);
}
void fcsm_FailSelPin_(char *pins, RadioButton captdat)
{
    FailSelPinHandle failselpinh;
    UT_PIN  pin=0;
    PinCursor pcr;
    RadioButton target;
    failselpinh = UTL_GetFailSelPinHandle();
    
    UTL_ClearFailSelPinAssign(failselpinh);
    switch (captdat) {
        case 0                       :target = UT_FAILSELPIN_TARGET_ECC_OR   ; printf("%s ECC_OR   \n",__func__);break;
        case 1                       :target = UT_FAILSELPIN_TARGET_ECC_TOTAL;    printf("%s ECC_TOTAL\n",__func__);break;
        defalut             : printf("%s : Unexpected FAILSELPIN is selected\n"); UTL_Stop();
    }
    UTL_SetFailSelPinTarget(failselpinh, target);
    
    pcr=UTL_GetPinCursor(pins);
    printf("UTL_SetFailSelPin:", pin);
    while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
        printf("%d ", pin);
    	UTL_SetFailSelPin(failselpinh, pin, UT_ON);
    }
    printf("\n");
    UTL_SendFailSelPin (failselpinh);
    UTL_DeleteHandle   (failselpinh);
}

void fcsm_level_setting(int channel, DSlider high, DSlider low)
{
    printf("[DEBUG]%s\n",__func__);
    DSlider vtl = (high+low)/2;

    ViHandle vih = UTL_GetViHandle();
    UTL_SetViHigh(vih, high   );
    UTL_SetViLow (vih, low    );
    UTL_SendVi   (vih, channel);

    VtHandle vth = UTL_GetVtHandle();
    UTL_SetVt (vth, 0  );
//  UTL_SetVt (vth, vtl);
    UTL_SendVt(vth, channel);

    VoHandle voh = UTL_GetVoHandle();
    UTL_SetVoHigh(voh, vtl);   //This is used as VOH & VOL
    UTL_SetVoLow (voh, vtl);
    UTL_SendVo   (voh, channel);

    UTL_DeleteHandle(vih);
    UTL_DeleteHandle(vth);
    UTL_DeleteHandle(voh);
}

void fcsm_timing_setting(DSlider tck,RadioButton ilmd)
{
    DutCursor dutcur;
    UT_DUT dut;
    PinCursor pincur;
    UT_PIN pin;
    DSlider offset;
    DSlider i,k;


    TgHandle tgh = UTL_GetTgHandle();
    UTL_AddTgRate(tgh, 1,    tck);              UTL_AddTgRate(tgh, 2,    tck);
    UTL_AddTgBclk(tgh, 1, 1, tck);              UTL_AddTgCclk(tgh, 1, 1, tck);
    UTL_AddTgBclk(tgh, 2, 1, tck);              UTL_AddTgCclk(tgh, 2, 1, tck);
    UTL_AddTgDreL(tgh, 1, 1, tck);              UTL_AddTgDreT(tgh, 1, 1, tck);
    UTL_AddTgDreL(tgh, 2, 1, tck);              UTL_AddTgDreT(tgh, 2, 1, tck);
    UTL_AddTgStrb(tgh, 1, 1, tck*0.00);         UTL_AddTgStrb(tgh, 1, 2, tck*0.50);
    UTL_AddTgStrb(tgh, 2, 1, tck*0.50);         UTL_AddTgStrb(tgh, 2, 2, tck*1.00);
    UTL_SendTg   (tgh);
    UTL_DeleteHandle(tgh);

}

void fcsm_readtname(){
    char *tname;
    tname = UTL_ReadTestName();
    printf("\nTEST NAME : %s\n",tname);	
}

void fcsm_MeasFct(TEST_fcsmarg fcsmarg, RadioButton pgstop, RadioButton pgclear)
{

    USlider idx1;
    RegHandle regh = UTL_GetRegHandle();
    idx1 = (fcsmarg.afmxfer_cnt/16)-2;
    UTL_SetRegUs(regh,UT_REG_IDX1,1,idx1);
    UTL_SendReg(regh);
    UTL_DeleteHandle(regh);

    FctHandle fct = UTL_GetFctHandle();
    UTL_SetFctMpatName   (fct, fcsmarg.mpat);
    UTL_SetFctStartPc    (fct, fcsmarg.pc);         
    UTL_SetFctFailInhibit(fct, pgstop);
    UTL_SetFctNoClear    (fct, pgclear);
	
    UTL_MeasFct(fct);
    UTL_DeleteHandle(fct);
}
void fcsm_MeasFct_multi(TEST_fcsmarg fcsmarg, RadioButton pgstop, RadioButton pgclear)
{

    USlider idx1, idx2, idx3,idx10;
    RegHandle regh = UTL_GetRegHandle();
    idx2 = 0xE; //xfer loop
    //uchi idx2 = 0x6; //xfer loop
    idx1 = (fcsmarg.afmxfer_cnt/(idx2+2))-2;
    UTL_SetRegUs(regh,UT_REG_IDX1,1,idx1);
    UTL_SetRegUs(regh,UT_REG_IDX2,1,idx2);

	idx10=(0x200/fcsmarg.ilmode)/(fcsmarg.ddr_mode+1)-2;
	//uchi idx10=(0x100/fcsmarg.ilmode)/(fcsmarg.ddr_mode+1)-2;
    UTL_SetRegUs(regh,UT_REG_IDX10,1,idx10);

    if(fcsmarg.sector==1){
    	idx3 = idx2-1;
    	UTL_SetRegUs(regh,UT_REG_IDX3,1,idx3);
    }else if(fcsmarg.sector!=1){
    	UTL_SetRegUs(regh,UT_REG_IDX4,1,fcsmarg.sector-2);
	}


    UTL_SendReg(regh);
    UTL_DeleteHandle(regh);

	if(fcsmarg.sector==1){printf("REG: IDX1=0x%05X IDX2=0x%03X IDX3=0x%03X IDX10=0x%02X -> XFER Loop=0x%05X (exp=0x%05X)\n",idx1,idx2,idx3,idx10,(idx1+2)*(idx2+2)+(idx3+2),fcsmarg.afmxfer_cnt);}
	if(fcsmarg.sector!=1){printf("REG: IDX1=0x%05X IDX2=0x%03X IDX4=0x%03X IDX10=0x%02X -> SECTOR Loop=%2d, XFER Loop=0x%05X(exp=0x%05X)\n",idx1,idx2,idx10,fcsmarg.sector-2,fcsmarg.sector,(idx1+2)*(idx2+2),fcsmarg.afmxfer_cnt);}
    FctHandle fct = UTL_GetFctHandle();
    UTL_SetFctMpatName   (fct, fcsmarg.mpat);
    UTL_SetFctStartPc    (fct, fcsmarg.pc);         
    UTL_SetFctFailInhibit(fct, pgstop);
    UTL_SetFctNoClear    (fct, pgclear);
	
    UTL_MeasFct(fct);
    UTL_DeleteHandle(fct);
}
void fcsm_MeasFct_2nd(TEST_fcsmarg fcsmarg, RadioButton pgstop, RadioButton pgclear)
{

    USlider idx1;
    RegHandle regh = UTL_GetRegHandle();
    idx1 = (fcsmarg.afmxfer_cnt/16)/2-2;
    UTL_SetRegUs(regh,UT_REG_IDX1,1,idx1);
    UTL_SendReg(regh);
    UTL_DeleteHandle(regh);

    FctHandle fct = UTL_GetFctHandle();
    UTL_SetFctMpatName   (fct, fcsmarg.mpat);
    UTL_SetFctStartPc    (fct, fcsmarg.pc);         
    UTL_SetFctFailInhibit(fct, pgstop);
    UTL_SetFctNoClear    (fct, pgclear);
	
    UTL_MeasFct(fct);
    UTL_DeleteHandle(fct);
}

void fcsm_MeasFct_Wait(TEST_fcsmarg fcsmarg, RadioButton pgstop, RadioButton pgclear)
{

    USlider idx1;
    RegHandle regh = UTL_GetRegHandle();
    idx1 = (fcsmarg.afmxfer_cnt/16)-2-1;      // "-1" for WAIT command
    UTL_SetRegUs(regh,UT_REG_IDX1,1,idx1);
    UTL_SendReg(regh);
    UTL_DeleteHandle(regh);

    FctHandle fct = UTL_GetFctHandle();
    UTL_SetFctMpatName   (fct, fcsmarg.mpat);
    UTL_SetFctStartPc    (fct, fcsmarg.pc); 
    UTL_SetFctFailInhibit(fct, pgstop);
    UTL_SetFctNoClear    (fct, pgclear);
	
    UTL_MeasFct(fct);
    printf("Return to Main Program!!\n");fflush(stdout);
    UTL_SetFctContinue(fct,UT_ON);
    UTL_MeasFct(fct);
    UTL_DeleteHandle(fct);
}

void fcsm_clear()
{
	FcmAccessHandle fcmach = UTL_GetFcmAccessHandle();
	UTL_ResetFcsmStoreCnt();
   	UTL_ResetFcsm		(fcmach);
	UTL_DeleteHandle	(fcmach);
}

void ecc_set_condition(TEST_fcsmarg fcsmarg)
{
    EccConfigHandle eccconfigh = UTL_GetEccConfigHandle();
    UTL_SetEccConfigSectorCount             (eccconfigh,      fcsmarg.sector ); //T5835
    if      (fcsmarg.captdat == 0) UTL_SetEccConfigCounterLimit(eccconfigh, UT_ECC_COUNTMODE_OR,    1, fcsmarg.ecclmt);
    else if (fcsmarg.captdat == 1) UTL_SetEccConfigCounterLimit(eccconfigh, UT_ECC_COUNTMODE_TOTAL, 1, fcsmarg.ecclmt);
    UTL_SetEccConfigCounterEnableSignal     (eccconfigh, 0,   fcsmarg.eccsig);
    UTL_SetEccConfigSectorSwitchSignal      (eccconfigh,      UT_SIG_C(20));
    UTL_SetEccConfigCounterClearSignal      (eccconfigh,      UT_SIG_C(19));
    UTL_SetEccConfigJudgeSignal             (eccconfigh, 0,   UT_SIG_C(18)   );
    UTL_SendEccConfig                       (eccconfigh);
    UTL_DeleteHandle                        (eccconfigh);

}

void get_failseltarget()
{
RadioButton target;

FailSelPinHandle h = UTL_GetFailSelPinHandle();
UTL_UpdateFailSelPin(h);
int erf=UTL_GetFailSelPinTarget(h,&target);
if(erf==-1)printf("ERROR\n");fflush(stdout);
if(erf== 1)printf("PASS \n");fflush(stdout);
if(erf== 0)printf("---- \n");fflush(stdout);

if(target==UT_FAILSELPIN_TARGET_ECC_TOTAL)printf("TOTAL MODE\n");fflush(stdout);
if(target==UT_FAILSELPIN_TARGET_ECC_OR   )printf("OR    MODE\n");fflush(stdout);
if(target==UT_FAILSELPIN_TARGET_READ_FAIL   )printf("READ FAIL  MODE\n");fflush(stdout);

UTL_DeleteHandle(h);

}



void fcsm_set_condition(TEST_fcsmarg fcsmarg)
{
if(fcsmarg.captdat==0)printf("ECC MODE: OR MODE\n");fflush(stdout);
if(fcsmarg.captdat==1)printf("ECC MODE: TOTAL MODE\n");fflush(stdout);

printf("fcsmarg.child:%d\n",fcsmarg.child);fflush(stdout);

    FailCaptureSelectHandle fcsh = UTL_GetFailCaptureSelectHandle();
    UTL_SetFailCaptureSelectAllDutGroupNumber	(fcsh,UT_ON );
    UTL_SetFailCaptureSelectAllPin		        (fcsh,UT_OFF);
    UTL_SetFailCaptureSelectPinList		        (fcsh,SOCKET.dutblock_iopinlist[fcsmarg.child]);
    UTL_SendFailCaptureSelect			        (fcsh);
    UTL_DeleteHandle				            (fcsh);

    fcsm_FailSelPin_(SOCKET.dutblock_iopinlist[fcsmarg.child], fcsmarg.captdat);

    FcmConfigHandle fcmconfigh = UTL_GetFcmConfigHandle();
    UTL_SetFcmConfigDelay	(fcmconfigh , 0);
    UTL_SetFcmConfigFcsmMaxStoreCnt (fcmconfigh, fcsmarg.afmxfer_cnt);
    if(fcsmarg.captdat==0) UTL_AddFcmConfigAction(fcmconfigh , 1 , UT_FCM_ECCCOUNT_OR_TO_FCSM );
    if(fcsmarg.captdat==1) UTL_AddFcmConfigAction(fcmconfigh , 1 , UT_FCM_ECCCOUNT_TOTAL_TO_FCSM );
    UTL_SendFcmConfig 		(fcmconfigh);
    UTL_DeleteHandle		(fcmconfigh);



}
void fcsm_set_condition_multi(TEST_fcsmarg fcsmarg, char *pinlist)
{
if(fcsmarg.captdat==0)printf("ECC MODE: OR MODE\n");fflush(stdout);
if(fcsmarg.captdat==1)printf("ECC MODE: TOTAL MODE\n");fflush(stdout);

printf("fcsmarg.child:%d\n",fcsmarg.child);fflush(stdout);

    FailCaptureSelectHandle fcsh = UTL_GetFailCaptureSelectHandle();
    UTL_SetFailCaptureSelectAllDutGroupNumber	(fcsh,UT_ON );
    UTL_SetFailCaptureSelectAllPin		        (fcsh,UT_OFF);
    UTL_SetFailCaptureSelectPinList		        (fcsh,pinlist);
    UTL_SendFailCaptureSelect			        (fcsh);
    UTL_DeleteHandle				            (fcsh);

    fcsm_FailSelPin_(pinlist, fcsmarg.captdat);

    FcmConfigHandle fcmconfigh = UTL_GetFcmConfigHandle();
    UTL_SetFcmConfigDelay	(fcmconfigh , 0);
    UTL_SetFcmConfigFcsmMaxStoreCnt (fcmconfigh, fcsmarg.afmxfer_cnt);
    if(fcsmarg.captdat==0) UTL_AddFcmConfigAction(fcmconfigh , 1 , UT_FCM_ECCCOUNT_OR_TO_FCSM );
    if(fcsmarg.captdat==1) UTL_AddFcmConfigAction(fcmconfigh , 1 , UT_FCM_ECCCOUNT_TOTAL_TO_FCSM );
    UTL_SendFcmConfig 		(fcmconfigh);
    UTL_DeleteHandle		(fcmconfigh);



}

void readfcsm(TEST_fcsmarg fcsmarg)
{
    printf("Sector:%d\n",fcsmarg.sector);
    printf("Afmxfer Count:0x%X\n",fcsmarg.afmxfer_cnt);
    printf("Ecc Limit:%d\n",fcsmarg.ecclmt);fflush(stdout);

    USlider dut_res[MAXDUTCNT]={0};
    USlider store_cnt;
    USlider size1=0;
    USlider size2=0;
    USlider *fcsm_data;
    USlider *exp_data1,*exp_data2;    //data1:odd dut,data2:even dut
    USlider rdata;
    DutCursor dutcur;
    UT_DUT dut;
    int sec;
    int afmx_cnt;
    int data_cnt=16;
    int i;
    size1 = (fcsmarg.afmxfer_cnt * fcsmarg.sector * MAXDUTCNT)*sizeof(USlider);
    size2 = sizeof(USlider) * (fcsmarg.afmxfer_cnt * fcsmarg.sector );
    fcsm_data = (USlider *)malloc(size1);
    exp_data1 = (USlider *)calloc(size2, sizeof(USlider));
    exp_data2 = (USlider *)calloc(size2, sizeof(USlider));
    int cnt_ex=0;
    cnt_ex= fcsmarg.ddr_mode <<  fcsmarg.captdat |fcsmarg.captdat;

    for(afmx_cnt=0;afmx_cnt<fcsmarg.afmxfer_cnt;afmx_cnt++)
    {
        if(afmx_cnt==data_cnt){break;}
        for(sec=0;sec<fcsmarg.sector;sec++)
        {
           exp_data1[(fcsmarg.sector*afmx_cnt)+sec]=(cnt_ex+1)*(afmx_cnt*data_cnt+(sec+1));
           exp_data2[(fcsmarg.sector*afmx_cnt)+sec]=(cnt_ex+1)*(256-(afmx_cnt*data_cnt+sec));
           if(exp_data1[(fcsmarg.sector*afmx_cnt)+sec]>=256)
           {
                exp_data1[(fcsmarg.sector*afmx_cnt)+sec]=256                       | 0x300;
//              exp_data1[(fcsmarg.sector*afmx_cnt)+sec]=afmx_cnt*data_cnt+(sec+1) | 0x300;
           }
           else if(exp_data1[(fcsmarg.sector*afmx_cnt)+sec]>=fcsmarg.ecclmt)
           {
                exp_data1[(fcsmarg.sector*afmx_cnt)+sec]=(cnt_ex+1)*(afmx_cnt*data_cnt+(sec+1)) | 0x100;
           }
           if(exp_data2[(fcsmarg.sector*afmx_cnt)+sec]>=256)
           {
                exp_data2[(fcsmarg.sector*afmx_cnt)+sec]=256                           | 0x300;
//              exp_data2[(fcsmarg.sector*afmx_cnt)+sec]=(256-(afmx_cnt*data_cnt+sec)) | 0x300;
           }
           else if(exp_data2[(fcsmarg.sector*afmx_cnt)+sec]>=fcsmarg.ecclmt)
           {
                exp_data2[(fcsmarg.sector*afmx_cnt)+sec]=(cnt_ex+1)*((256-(afmx_cnt*data_cnt+sec))) | 0x100;
           }
        }
    }


    FcmAccessHandle fcmach = UTL_GetFcmAccessHandle();
    UTL_SetFcmAccessAllDut	(fcmach, UT_ON );
    UTL_SetFcmAccessBitMode     (fcmach,UT_FCM_BITMODE_NORMAL);
    UTL_SetFcmAccessAllBit      (fcmach,UT_ON);

    UTL_ReadFcsmStoreCnt	(fcmach, &store_cnt);
    printf("***Store Count : %X *******\n",store_cnt);fflush(stdout);
    UTL_ReadFcsm		(fcmach,fcsm_data,size1);
    dutcur = UTL_GetDutCursor(UT_CDUT);
    while((dut= UTL_NextDut(dutcur)) != UT_NOMORE)
    {
        for(afmx_cnt=0;afmx_cnt<store_cnt;afmx_cnt++)
    	{
    	    for(sec=0;sec<fcsmarg.sector;sec++)
	    {
                rdata=fcsm_data[(fcsmarg.sector*store_cnt)*(dut-1)+(fcsmarg.sector*afmx_cnt)+sec];
                if(DEBUG){
           	   printf("DUT:%d,AFMXFER COUNT:%d,SECTOR:%d : %d ",dut,afmx_cnt,sec,rdata);fflush(stdout);
  		   if     ((rdata&0x300)==0x300){printf("***Overflow,Limit Over");}
  		   else if((rdata&0x200)==0x200){printf("***Overflow");}
  		   else if((rdata&0x100)==0x100){printf("***Limit Over");}
                   printf("\n");fflush(stdout);
                }
                if(fcsmarg.eccsig==UT_SIG_FL){
                   if(rdata!=0){dut_res[dut-1]=1;}
                }
                else if(fcsmarg.afmxfer_cnt<=0x1000){
                   if(dut%2==1){
                        if(rdata!=exp_data1[(fcsmarg.sector*(afmx_cnt%data_cnt))+sec]){
  	                     if(DEBUG){printf("**DUT:%d,AFMXFER COUNT:%d,SECTOR:%d : %d **FAIL\n",dut,afmx_cnt,sec,exp_data1[(fcsmarg.sector*(afmx_cnt%data_cnt))+sec]);fflush(stdout);}
                             dut_res[dut-1]=1;
                        }
                   }else if(dut%2==0){
                        if(rdata!=exp_data2[(fcsmarg.sector*(afmx_cnt%data_cnt))+sec]){
                             if(DEBUG){printf("**DUT:%d,AFMXFER COUNT:%d,SECTOR:%d : %d **FAIL\n",dut,afmx_cnt,sec,exp_data2[(fcsmarg.sector*(afmx_cnt%data_cnt))+sec]);fflush(stdout);}
                             dut_res[dut-1]=1;
                        }
                   }
                }
                else if(fcsmarg.afmxfer_cnt>0x1000){
                   if(rdata!=exp_data1[(fcsmarg.sector*(afmx_cnt%data_cnt))+sec]){
  	                if(DEBUG){printf("**DUT:%d,AFMXFER COUNT:%d,SECTOR:%d : %d **FAIL\n",dut,afmx_cnt,sec,exp_data1[(fcsmarg.sector*(afmx_cnt%data_cnt))+sec]);fflush(stdout);}
                        dut_res[dut-1]=1;
                   }
                }
	    }

	}

    }
    free(fcsm_data);
    fcsmarg.post(dut_res);
    

}

//void readfcsm_multi(TEST_fcsmarg fcsmarg)
//{
//    printf("Sector:%d\n",fcsmarg.sector);
//    printf("Afmxfer Count:%X\n",fcsmarg.afmxfer_cnt);
//    printf("Ecc Limit:%d\n",fcsmarg.ecclmt);fflush(stdout);
//
//    USlider dut_res[MAXDUTCNT]={0};
//    USlider store_cnt;
//    USlider dutch_cnt=0;
//    USlider size1=0;
//    USlider size2=0;
//    USlider *fcsm_data;
//    USlider *exp_data1,*exp_data2;    //data1:odd dut,data2:even dut
//    USlider rdata;
//    DutCursor dutcur;
//    UT_DUT dut;
//    int sec;
//    int afmx_cnt;
//    int dutchc;
//    int data_cnt=16;
//    int i;
//    DutChannelHandle dutch = UTL_GetDutChannelHandle();
//    UTL_UpdateDutChannel  (dutch);
//    UTL_GetDutChannelCount(dutch,&dutch_cnt);
//    UTL_DeleteHandle(dutch);
//
//    printf("dutch count:%d\n",dutch_cnt);fflush(stdout);
//
//    size1 = (fcsmarg.afmxfer_cnt * fcsmarg.sector * MAXDUTCNT * dutch_cnt)*sizeof(USlider);
//    size2 = sizeof(USlider) * (fcsmarg.afmxfer_cnt * fcsmarg.sector );
//    fcsm_data = (USlider *)malloc(size1);
//    exp_data1 = (USlider *)calloc(size2, sizeof(USlider));
//    exp_data2 = (USlider *)calloc(size2, sizeof(USlider));
//    int cnt_ex=0;
//    cnt_ex= fcsmarg.ddr_mode <<  fcsmarg.captdat |fcsmarg.captdat;
//
//    for(afmx_cnt=0;afmx_cnt<fcsmarg.afmxfer_cnt;afmx_cnt++)
//    {
//        if(afmx_cnt==data_cnt){break;}
//        for(sec=0;sec<fcsmarg.sector;sec++)
//        {
//           exp_data1[(fcsmarg.sector*afmx_cnt)+sec]=(cnt_ex+1)*(afmx_cnt*data_cnt+(sec+1));
//           exp_data2[(fcsmarg.sector*afmx_cnt)+sec]=(cnt_ex+1)*(256-(afmx_cnt*data_cnt+sec));
//           if(exp_data1[(fcsmarg.sector*afmx_cnt)+sec]>=256)
//           {
//                exp_data1[(fcsmarg.sector*afmx_cnt)+sec]=256                       | 0x300;
////              exp_data1[(fcsmarg.sector*afmx_cnt)+sec]=afmx_cnt*data_cnt+(sec+1) | 0x300;
//           }
//           else if(exp_data1[(fcsmarg.sector*afmx_cnt)+sec]>=fcsmarg.ecclmt)
//           {
//                exp_data1[(fcsmarg.sector*afmx_cnt)+sec]=(cnt_ex+1)*(afmx_cnt*data_cnt+(sec+1)) | 0x100;
//           }
//           if(exp_data2[(fcsmarg.sector*afmx_cnt)+sec]>=256)
//           {
//                exp_data2[(fcsmarg.sector*afmx_cnt)+sec]=256                           | 0x300;
////              exp_data2[(fcsmarg.sector*afmx_cnt)+sec]=(256-(afmx_cnt*data_cnt+sec)) | 0x300;
//           }
//           else if(exp_data2[(fcsmarg.sector*afmx_cnt)+sec]>=fcsmarg.ecclmt)
//           {
//                exp_data2[(fcsmarg.sector*afmx_cnt)+sec]=(cnt_ex+1)*((256-(afmx_cnt*data_cnt+sec))) | 0x100;
//           }
//        }
//    }
//
//
//    FcmAccessHandle fcmach = UTL_GetFcmAccessHandle();
//    UTL_SetFcmAccessAllDut	(fcmach, UT_ON );
//    UTL_SetFcmAccessBitMode     (fcmach,UT_FCM_BITMODE_NORMAL);
//    UTL_SetFcmAccessAllBit      (fcmach,UT_ON);
//
//    UTL_ReadFcsmStoreCnt	(fcmach, &store_cnt);
//    printf("***Store Count : %X *******\n",store_cnt);fflush(stdout);
//    UTL_ReadFcsm		(fcmach,fcsm_data,size1);
//    dutcur = UTL_GetDutCursor(UT_CDUT);
//    while((dut= UTL_NextDut(dutcur)) != UT_NOMORE)
//    {
//    	for(dutchc=0;dutchc<dutch_cnt;dutchc++)
//    	  {
//          for(afmx_cnt=0;afmx_cnt<store_cnt;afmx_cnt++)
//    	  {
//    	      for(sec=0;sec<fcsmarg.sector;sec++)
//	      {
//                  rdata=fcsm_data[(fcsmarg.sector*store_cnt*dutch_cnt)*(dut-1)+(dutchc*fcsmarg.sector*store_cnt)+(fcsmarg.sector*afmx_cnt)+sec];
////                printf("Count : %d\n",(fcsmarg.sector*store_cnt*dutch_cnt)*(dut-1)+(dutchc*fcsmarg.sector*store_cnt)+(fcsmarg.sector*afmx_cnt)+sec);fflush(stdout);
//                  if(DEBUG){
//             	   printf("DUT:%d,DUT CH:%d,AFMXFER COUNT:%d,SECTOR:%d : %d ",dut,dutchc,afmx_cnt,sec,rdata);fflush(stdout);
//  		     if     ((rdata&0x300)==0x300){printf("***Overflow,Limit Over");}
//  		     else if((rdata&0x200)==0x200){printf("***Overflow");}
//  		     else if((rdata&0x100)==0x100){printf("***Limit Over");}
//                     printf("\n");fflush(stdout);
//                  }
//                  if(fcsmarg.eccsig==UT_SIG_FL){
//                     if(rdata!=0){dut_res[dut-1]=1;}
//                  }
//                  else{
//                     if(dutchc%2!=dut%2){
//                          if(rdata!=exp_data1[(fcsmarg.sector*(afmx_cnt%data_cnt))+sec]){
//  	                       if(1){printf("**DUT:%d,AFMXFER COUNT:%d,SECTOR:%d : %d **FAIL\n",dut,afmx_cnt,sec,exp_data1[(fcsmarg.sector*(afmx_cnt%data_cnt))+sec]);fflush(stdout);}
//                               dut_res[dut-1]=1;
//                          }
//                     }else if(dutchc%2==dut%2){
//                          if(rdata!=exp_data2[(fcsmarg.sector*(afmx_cnt%data_cnt))+sec]){
//                               if(1){printf("**DUT:%d,AFMXFER COUNT:%d,SECTOR:%d : %d **FAIL\n",dut,afmx_cnt,sec,exp_data2[(fcsmarg.sector*(afmx_cnt%data_cnt))+sec]);fflush(stdout);}
//                               dut_res[dut-1]=1;
//                          }
//                     }
//                  }
//	      }
//	    }
//
//	}
//
//    }
//    free(fcsm_data);
//    fcsmarg.post(dut_res);
//    
//
//}

void readfcsm_multi(TEST_fcsmarg fcsmarg)
{
    printf("Sector:%d\n",fcsmarg.sector);
    printf("Afmxfer Count:%X\n",fcsmarg.afmxfer_cnt);
    printf("Ecc Limit:%d\n",fcsmarg.ecclmt);fflush(stdout);

    USlider dut_res[MAXDUTCNT]={0};
	int i, j,k;
	RadioButton dutblock;
	UT_DUT dut;
	UT_DUT dutmax;
	DutCursor dutc;
	USlider size;
	USlider fmsize;
    USlider *fcsm_data;
    USlider rdata;
    USlider store_cnt;
    USlider exp;
	int sec_cnt=0;
	int afm_cnt=0;
	int dut_area=0;

	int fcnt=0;
	int dutchcnt;
	int chcnt,xfercnt,sctrcnt,cnt;
	int xferlp=0x10;
	//uchi int xferlp=0x8;
	int lp=0x200;
	//uchi int lp=0x100;
	int fcsmap;

	dutmax = 0;
	dutc = UTL_GetDutCursor(UT_CDUT);
	while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
	  dutmax++;
	}
	UTL_DeleteCursor(dutc);

    DutChannelHandle dutch = UTL_GetDutChannelHandle();
    UTL_UpdateDutChannel  (dutch);
    UTL_GetDutChannelCount(dutch,&dutchcnt);
    UTL_DeleteHandle(dutch);
    printf("dutch count:%d\n",dutchcnt);fflush(stdout);

    fmsize = (fcsmarg.afmxfer_cnt * fcsmarg.sector * dutmax * dutchcnt)*sizeof(USlider);
    fcsm_data = (USlider *)malloc(fmsize);

    //cnt_ex= fcsmarg.ddr_mode <<  fcsmarg.captdat |fcsmarg.captdat;

	USlider expdata[dutmax][dutchcnt][xferlp][fcsmarg.sector];
	for(dut=1;dut<=dutmax;dut++){
		for(chcnt=1;chcnt<=dutchcnt;chcnt++){
			for(xfercnt=1;xfercnt<=xferlp;xfercnt++){
				for(sctrcnt=1;sctrcnt<=fcsmarg.sector;sctrcnt++){
					expdata[dut-1][chcnt-1][xfercnt-1][sctrcnt-1]=0;
				}
			}
		}
	}	

	for(dut=1;dut<=dutmax;dut++){
		for(chcnt=1;chcnt<=dutchcnt;chcnt++){
			for(xfercnt=1;xfercnt<=xferlp;xfercnt++){
				for(sctrcnt=1;sctrcnt<=fcsmarg.sector;sctrcnt++){
					fcnt=(chcnt-1)+dutchcnt*(dut-1)+(sctrcnt-1)+fcsmarg.sector*(xfercnt-1);
					for(cnt=0;cnt<lp;cnt++){
						if(fcnt>cnt){
							expdata[dut-1][chcnt-1][xfercnt-1][sctrcnt-1]++;
						}
//					if(DEBUG!=0){if(expdata[dut-1][chcnt-1][cnt]==0x6){printf("1");}else{printf("0");}	}
					}
				}
			}
		}
	}


    FcmAccessHandle fcmach = UTL_GetFcmAccessHandle();
    UTL_SetFcmAccessAllDut	(fcmach, UT_ON );
    UTL_SetFcmAccessBitMode     (fcmach,UT_FCM_BITMODE_NORMAL);
    UTL_SetFcmAccessAllBit      (fcmach,UT_ON);

    UTL_ReadFcsmStoreCnt	(fcmach, &store_cnt);
    printf("*** Store Count : 0x%X (exp:0x%X) *******",store_cnt,fcsmarg.afmxfer_cnt);fflush(stdout);
	if(store_cnt!=fcsmarg.afmxfer_cnt){printf("  ---- FAIL!\n");}else{printf("\n");}

    UTL_ReadFcsm		(fcmach,fcsm_data,fmsize);
    dutc = UTL_GetDutCursor(UT_CDUT);
	while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
		for(chcnt=1;chcnt<=dutchcnt;chcnt++){
			if(store_cnt!=fcsmarg.afmxfer_cnt){dut_res[dut-1]=1;}
			for(xfercnt=1;xfercnt<=store_cnt;xfercnt++){
				for(sctrcnt=1;sctrcnt<=fcsmarg.sector;sctrcnt++){
                  	fcsmap=(dut-1)*(dutchcnt*store_cnt*fcsmarg.sector) + (chcnt-1)*(store_cnt*fcsmarg.sector) + (xfercnt-1)*(fcsmarg.sector) + (sctrcnt-1);
                  	rdata=fcsm_data[fcsmap];
					exp=expdata[dut-1][chcnt-1][(xfercnt-1)%xferlp][sctrcnt-1];
					//DDR MODE
					if(fcsmarg.captdat==1){exp=exp*2;}
					//Over Flow
					if(exp>0xFF){exp=0x300;}
					//Limit Over
					if((exp&0xFF)>=fcsmarg.ecclmt){exp=exp|0x100;}
//                	printf("Count : %d\n",(fcsmarg.sector*store_cnt*dutch_cnt)*(dut-1)+(dutchc*fcsmarg.sector*store_cnt)+(fcsmarg.sector*afmx_cnt)+sec);fflush(stdout);
                	if(DEBUG){
             	   		printf("[FCSM RSLT] DUT:%2d,DUTCH:%2d,AFMXFER:0x%5X,SECTOR:%2d : FAIL CNT=0x%4X (exp=0x%5X)",dut,chcnt,xfercnt-1,sctrcnt,rdata,exp);fflush(stdout);
  		    			if     ((rdata&0x300)==0x300){printf("(Limit Over,Overflow) ");}
  		    			else if((rdata&0x100)==0x100){printf("(Limit Over         ) ");}
  		    			else                         {printf("(                   ) ");}
                		if(rdata!=exp){printf("   ---- FAIL!");}
                		printf("\n");fflush(stdout);
                	}	
                	if(rdata!=exp){
             			if(!DEBUG &&  dut_res[dut-1]==0){printf("DUT:%2d,DUTCH:%2d,AFMXFER:0x%5X,SECTOR:%2d : fcsm[0x%5X]=0x%5X (exp=0x%5X)    ---- FAIL!\n",dut,chcnt,xfercnt-1,sctrcnt,fcsmap,rdata,exp);fflush(stdout);}
						dut_res[dut-1]=1;
					}
	      		}
	      }
	    }
	}
	UTL_DeleteCursor(dutc);
	

    free(fcsm_data);
    fcsmarg.post(dut_res);

}
void readfcsm_each_dut(TEST_fcsmarg fcsmarg)
{
    printf("Sector:%d\n",fcsmarg.sector);
    printf("Afmxfer Count:%X\n",fcsmarg.afmxfer_cnt);
    printf("Ecc Limit:%d\n",fcsmarg.ecclmt);fflush(stdout);

    USlider dut_res[MAXDUTCNT]={0};
    USlider store_cnt;
    USlider size1=0;
    USlider size2=0;
    USlider *fcsm_data;
    USlider *exp_data1;    //data1:odd dut,data2:even dut
    USlider rdata;
    DutCursor dutcur;
    UT_DUT dut;
    int sec;
    int afmx_cnt;
    int data_cnt=2;
    int i;
    size1 = (fcsmarg.sector * fcsmarg.sector * MAXDUTCNT)*sizeof(USlider);
    size2 = sizeof(USlider) * (fcsmarg.afmxfer_cnt * fcsmarg.sector * MAXDUTCNT );
    fcsm_data = (USlider *)malloc(size1);
    exp_data1 = (USlider *)calloc(size2, sizeof(USlider));
    memset(fcsm_data,0x0,size1);
    memset(exp_data1,0x0,size2);
    
    dutcur=UTL_GetDutCursor(UT_CDUT);
    while((dut= UTL_NextDut(dutcur)) != UT_NOMORE)
    {
    for(afmx_cnt=0;afmx_cnt<fcsmarg.afmxfer_cnt;afmx_cnt++)
      {
          if(afmx_cnt==data_cnt ){break;}
          for(sec=0;sec<fcsmarg.sector;sec++)
          {
             exp_data1[(fcsmarg.sector*data_cnt)*(dut-1)+(fcsmarg.sector*afmx_cnt)+sec]=(fcsmarg.sector*afmx_cnt)+sec+dut;
//           printf("DUT:%d,exp1[%d]:%d\n",dut,(fcsmarg.sector*data_cnt)*(dut-1)+(fcsmarg.sector*afmx_cnt)+sec,exp_data1[(fcsmarg.sector*data_cnt)*(dut-1)+(fcsmarg.sector*afmx_cnt)+sec]);fflush(stdout);
             if(exp_data1[(fcsmarg.sector*data_cnt)*(dut-1)+(fcsmarg.sector*afmx_cnt)+sec]>=256)
             {
                  exp_data1[(fcsmarg.sector*data_cnt)*(dut-1)+(fcsmarg.sector*afmx_cnt)+sec]=(fcsmarg.sector*afmx_cnt)+sec+dut | 0x300;
             }
             else if(exp_data1[(fcsmarg.sector*data_cnt)*(dut-1)+(fcsmarg.sector*afmx_cnt)+sec]>=fcsmarg.ecclmt)
             {
                  exp_data1[(fcsmarg.sector*data_cnt)*(dut-1)+(fcsmarg.sector*afmx_cnt)+sec]=(fcsmarg.sector*afmx_cnt)+sec+dut | 0x100;
             }
          }
      }
    }


    FcmAccessHandle fcmach = UTL_GetFcmAccessHandle();
    UTL_SetFcmAccessAllDut	(fcmach, UT_ON );
    UTL_SetFcmAccessBitMode     (fcmach,UT_FCM_BITMODE_NORMAL);
    UTL_SetFcmAccessAllBit      (fcmach,UT_ON);

    UTL_ReadFcsmStoreCnt	(fcmach, &store_cnt);
    printf("***Store Count : %X *******\n",store_cnt);fflush(stdout);
    UTL_ReadFcsm		(fcmach,fcsm_data,size1);
    dutcur = UTL_GetDutCursor(UT_CDUT);
    while((dut= UTL_NextDut(dutcur)) != UT_NOMORE)
    {
        for(afmx_cnt=0;afmx_cnt<store_cnt;afmx_cnt++)
    	{
    	    for(sec=0;sec<fcsmarg.sector;sec++)
	    {
                rdata=fcsm_data[(fcsmarg.sector*store_cnt)*(dut-1)+(fcsmarg.sector*afmx_cnt)+sec];
                if(DEBUG){
          	printf("DUT:%d,AFMXFER COUNT:%d,SECTOR:%d : %d ",dut,afmx_cnt,sec,rdata);fflush(stdout);
  		   if     ((rdata&0x300)==0x300){printf("***Overflow,Limit Over");}
  		   else if((rdata&0x200)==0x200){printf("***Overflow");}
  		   else if((rdata&0x100)==0x100){printf("***Limit Over");}
                   printf("\n");fflush(stdout);
                }
                if(rdata!=exp_data1[(fcsmarg.sector*data_cnt)*(dut-1)+fcsmarg.sector*(afmx_cnt%data_cnt)+sec]){
  	             if(DEBUG){printf("**DUT:%d,AFMXFER COUNT:%d,SECTOR:%d : %d **FAIL\n",dut,afmx_cnt,sec,exp_data1[(fcsmarg.sector*data_cnt)*(dut-1)+fcsmarg.sector*(afmx_cnt%data_cnt)+sec]);fflush(stdout);}
                     dut_res[dut-1]=1;
                }
	    }

	}

    }
    free(fcsm_data);
    fcsmarg.post(dut_res);
    

}
void set_ubm_data(TEST_fcsmarg fcsmarg)
{

  UbmConfigHandle useth = UTL_GetUbmConfigHandle();
  UTL_InitializeUbmConfigHandle  (useth);
  UTL_ClearUbmConfigFunctionSelect(useth);
  UTL_ClearUbmConfigPin(useth, UT_UBM_UNIT_EXP);
  UTL_ClearUbmConfigJumpAddr(useth, UT_UBM_UNIT_EXP, 0x0);

  UTL_AddUbmConfigFunctionSelect(useth, UT_UBM_UNIT_EXP, UT_SIG_C(25));
  UTL_SetUbmConfigJumpAddr (useth, UT_UBM_UNIT_EXP, 0, 0x0);
  UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_EXP, 0, UT_SIG_FL); //dummy
  UTL_SetUbmConfigJumpAddr (useth, UT_UBM_UNIT_EXP, 1, 0x0);
  UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_EXP, 1, UT_SIG_FL); //dummy
  UTL_SetUbmConfigJumpAddr (useth, UT_UBM_UNIT_EXP, 2, 0x0);
  UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_EXP, 2, UT_SIG_FL); //dummy

  UTL_SetUbmConfigPin(useth, UT_UBM_UNIT_EXP, SOCKET.dutblock_iopinlist[fcsmarg.child]);
  UTL_SetUbmConfigJumpAddr(useth, UT_UBM_UNIT_EXP, 0, 0x0);
  UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_EXP, 0, UT_SIG_C(26));

  UTL_SetUbmConfigPmMode(useth, UT_UBM_UNIT_EXP);
  if(fcsmarg.ddr_mode==0){UTL_SetUbmConfigDdrMode(useth, UT_OFF);}
  if(fcsmarg.ddr_mode==1){UTL_SetUbmConfigDdrMode(useth, UT_ON );}

  UTL_SetUbmConfigApAutoIncMode(useth, UT_OFF);
  UTL_SetUbmConfigApIncCycle(useth, UT_SIG_C(27));
  UTL_SetUbmConfigApAllCycleIncMode(useth, UT_OFF);

  UTL_SendUbmConfig(useth);
  UTL_DeleteHandle(useth);

  return;
}

void set_ubm_data_multi(TEST_fcsmarg fcsmarg)
{

  UbmConfigHandle useth = UTL_GetUbmConfigHandle();
  UTL_InitializeUbmConfigHandle  (useth);
  UTL_ClearUbmConfigFunctionSelect(useth);
  UTL_ClearUbmConfigPin(useth, UT_UBM_UNIT_EXP);
  UTL_ClearUbmConfigJumpAddr(useth, UT_UBM_UNIT_EXP, 0x0);

  UTL_AddUbmConfigFunctionSelect(useth, UT_UBM_UNIT_EXP, UT_SIG_C(25));
  UTL_SetUbmConfigJumpAddr (useth, UT_UBM_UNIT_EXP, 0, 0x0);
  UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_EXP, 0, UT_SIG_FL); //dummy
  UTL_SetUbmConfigJumpAddr (useth, UT_UBM_UNIT_EXP, 1, 0x0);
  UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_EXP, 1, UT_SIG_FL); //dummy
  UTL_SetUbmConfigJumpAddr (useth, UT_UBM_UNIT_EXP, 2, 0x0);
  UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_EXP, 2, UT_SIG_FL); //dummy

  UTL_SetUbmConfigPin(useth, UT_UBM_UNIT_EXP, SOCKET.all_iopinlist);
  UTL_SetUbmConfigJumpAddr(useth, UT_UBM_UNIT_EXP, 0, 0x0);
  UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_EXP, 0, UT_SIG_C(26));

  UTL_SetUbmConfigPmMode(useth, UT_UBM_UNIT_EXP);
  if(fcsmarg.ddr_mode==0){UTL_SetUbmConfigDdrMode(useth, UT_OFF);}
  if(fcsmarg.ddr_mode==1){UTL_SetUbmConfigDdrMode(useth, UT_ON );}

  UTL_SetUbmConfigApAutoIncMode(useth, UT_OFF);
  UTL_SetUbmConfigApIncCycle(useth, UT_SIG_C(27));
  UTL_SetUbmConfigApAllCycleIncMode(useth, UT_OFF);

  UTL_SendUbmConfig(useth);
  UTL_DeleteHandle(useth);

  return;
}

static void ubm_preset(USlider n)
{
  UbmAccessHandle uacsh = UTL_GetUbmAccessHandle();
  UTL_ClearUbmAccessPin(uacsh);
  UTL_PresetUbm(uacsh, n);
  UTL_DeleteHandle(uacsh);
  return;

}

#define UBMSIZE 0x20000

void write_ubm_evenodd(TEST_fcsmarg fcsmarg,int mode)
{
  int i, j,k;
  RadioButton dutblock;
  UT_DUT dut;
  UT_DUT dutmax;
  DutCursor dutc;
  USlider *wdata;
  USlider size;
  int sec_cnt=0;
  int afm_cnt=0;
  int dut_area=0;

  dutmax = 0;
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    dutmax++;
  }
  UTL_DeleteCursor(dutc);

  size = UBMSIZE*dutmax*sizeof(USlider);
  wdata = (USlider *)malloc(size);
  memset(wdata, 0x0, size);

  printf("dutmax:%d\n",dutmax);
//  printf("block io pin count:%d\n",dutmax);
//SOCKET.dutblock_iopin_count[dutblock]
  if(fcsmarg.ddr_mode==1){
    for(dut=1;dut<=dutmax;dut++){
      for(j=0; j<UBMSIZE; j++){
         if     (dut%2==1){
            if     ((j/2)%2==1){
               if(fcsmarg.captdat==1){
                  if(SOCKET.dutblock_iopin_count[0]==8){
                     if(j%8==2)wdata[(dut-1)*UBMSIZE+j]=0x11;
                     if(j%8==3)wdata[(dut-1)*UBMSIZE+j]=0x84;
                     if(j%8==6)wdata[(dut-1)*UBMSIZE+j]=0x48;
                     if(j%8==7)wdata[(dut-1)*UBMSIZE+j]=0x28;
                  }else{
                     if(j%8==2)wdata[(dut-1)*UBMSIZE+j]=0xA;
                     if(j%8==3)wdata[(dut-1)*UBMSIZE+j]=0xC;
                     if(j%8==6)wdata[(dut-1)*UBMSIZE+j]=0x3;
                     if(j%8==7)wdata[(dut-1)*UBMSIZE+j]=0x5;
                  }
               }else{
                  if(j%16==0){wdata[(dut-1)*UBMSIZE+j]=0xFF << fcsmarg.child*mode*8;}
                  else{wdata[(dut-1)*UBMSIZE+j]=j%256 << fcsmarg.child*mode*8;}
               }
            }
         }
         else if(dut%2==0){
            if     ((j/2)%2==0){
               if(fcsmarg.captdat==1){
                  if(SOCKET.dutblock_iopin_count[0]==8){
                     if(j%8==0)wdata[(dut-1)*UBMSIZE+j]=0x24;
                     if(j%8==1)wdata[(dut-1)*UBMSIZE+j]=0x88;
                     if(j%8==4)wdata[(dut-1)*UBMSIZE+j]=0x11;
                     if(j%8==5)wdata[(dut-1)*UBMSIZE+j]=0x42;
                  }else{
                     if(j%8==0)wdata[(dut-1)*UBMSIZE+j]=0x6;
                     if(j%8==1)wdata[(dut-1)*UBMSIZE+j]=0xC;
                     if(j%8==4)wdata[(dut-1)*UBMSIZE+j]=0x9;
                     if(j%8==5)wdata[(dut-1)*UBMSIZE+j]=0x5;
                  }
               }else{
                  if(j%16==0){wdata[(dut-1)*UBMSIZE+j]=0xFF << fcsmarg.child*mode*8;}
                  else{wdata[(dut-1)*UBMSIZE+j]=j%256 << fcsmarg.child*mode*8;}
               }
            }
         }
      }
    }
  }
  else{
     for(dut=1;dut<=dutmax;dut++){
       for(j=0; j<UBMSIZE; j++){
         if     (dut%2==1){
           if     (j%2==1){
              if(fcsmarg.captdat==1){
                  if(SOCKET.dutblock_iopin_count[0]==8){
                     if(j%8==1)wdata[(dut-1)*UBMSIZE+j]=0x18;
                     if(j%8==3)wdata[(dut-1)*UBMSIZE+j]=0x30;
                     if(j%8==5)wdata[(dut-1)*UBMSIZE+j]=0x48;
                     if(j%8==7)wdata[(dut-1)*UBMSIZE+j]=0x81;
                  }else{
                     if(j%4==1)wdata[(dut-1)*UBMSIZE+j]=0x6;
                     if(j%4==3)wdata[(dut-1)*UBMSIZE+j]=0x9;
                  }
              }else{
                 if(j%16==0){wdata[(dut-1)*UBMSIZE+j]=0xFF << fcsmarg.child*mode*8;}
                 else{wdata[(dut-1)*UBMSIZE+j]=j%256 << fcsmarg.child*mode*8;}
              }
           }
         }
         else if(dut%2==0){
           if     (j%2==0){
              if(fcsmarg.captdat==1){
                  if(SOCKET.dutblock_iopin_count[0]==8){
                     if(j%8==0)wdata[(dut-1)*UBMSIZE+j]=0xC0;
                     if(j%8==2)wdata[(dut-1)*UBMSIZE+j]=0x24;
                     if(j%8==4)wdata[(dut-1)*UBMSIZE+j]=0x48;
                     if(j%8==6)wdata[(dut-1)*UBMSIZE+j]=0x18;
                  }else{
                     if(j%4==0)wdata[(dut-1)*UBMSIZE+j]=0x6;
                     if(j%4==2)wdata[(dut-1)*UBMSIZE+j]=0x9;
                  }
              }else{
                 if(j%16==0){wdata[(dut-1)*UBMSIZE+j]=0xFF << fcsmarg.child*mode*8;}
                 else{wdata[(dut-1)*UBMSIZE+j]=j%256 << fcsmarg.child*mode*8;}
              }
           }
         }
       }
     }
  }

  ubm_preset(0);

  UbmAccessHandle uacsh = UTL_GetUbmAccessHandle();
  UTL_SetUbmAccessBitReverse(uacsh, UT_ON);
  UTL_SetUbmAccessStartAddr(uacsh, 0x0);
  UTL_SetUbmAccessStopAddr (uacsh, UBMSIZE-1);
  if(fcsmarg.ddr_mode==0){
     UTL_SetUbmAccessDdrMode(uacsh, UT_OFF);
  }
  else if(fcsmarg.ddr_mode==1){
     UTL_SetUbmAccessDdrMode(uacsh, UT_ON );
  }
  dutc = UTL_GetDutCursor(UT_CDUT);
  UTL_ClearUbmAccessPin(uacsh);
  UTL_SetUbmAccessPin(uacsh, SOCKET.dutblock_iopinlist[fcsmarg.child]);
  if(fcsmarg.child==0){UTL_SetUbmAccessPinBlock(uacsh, 1);}
  if(fcsmarg.child==1){UTL_SetUbmAccessPinBlock(uacsh, 3);}
  UTL_WriteUbmAllDut(uacsh, dutmax, wdata, size);

  free(wdata);
  UTL_DeleteHandle(uacsh);

  return;
}

void write_ubm_evenodd_multi(TEST_fcsmarg fcsmarg)
{
  int i, j,k;
  RadioButton dutblock;
  UT_DUT dut;
  UT_DUT dutmax;
  DutCursor dutc;
  USlider *wdata;
  USlider size;
  int sec_cnt=0;
  int afm_cnt=0;
  int dut_area=0;

  dutmax = 0;
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    dutmax++;
  }
  UTL_DeleteCursor(dutc);

  size = UBMSIZE*dutmax*sizeof(USlider);
  wdata = (USlider *)malloc(size);
  memset(wdata, 0x0, size);

  printf("dutmax:%d\n",dutmax);
  if(fcsmarg.ddr_mode==1){
    for(dut=1;dut<=dutmax;dut++){
      for(j=0; j<UBMSIZE; j++){
         if     (dut%2==1){
            if     ((j/2)%2==1){
                  if(j%16==0){wdata[(dut-1)*UBMSIZE+j]=0xFF;}
                  else{wdata[(dut-1)*UBMSIZE+j]=j%256;}
            }else{
                  if(j%16==0){wdata[(dut-1)*UBMSIZE+j]=0xFF<<8;}
                  else{wdata[(dut-1)*UBMSIZE+j]=j%256<<8;}
            }
         }

         else if(dut%2==0){
            if     ((j/2)%2==0){
                  if(j%16==0){wdata[(dut-1)*UBMSIZE+j]=0xFF;}
                  else{wdata[(dut-1)*UBMSIZE+j]=j%256;}
            }else{
                  if(j%16==0){wdata[(dut-1)*UBMSIZE+j]=0xFF<<8;}
                  else{wdata[(dut-1)*UBMSIZE+j]=j%256<<8;}
            }
         }
      }
    }
  }

  ubm_preset(0);

  UbmAccessHandle uacsh = UTL_GetUbmAccessHandle();
  UTL_SetUbmAccessBitReverse(uacsh, UT_ON);
  UTL_SetUbmAccessStartAddr(uacsh, 0x0);
  UTL_SetUbmAccessStopAddr (uacsh, UBMSIZE-1);
  if(fcsmarg.ddr_mode==0){
     UTL_SetUbmAccessDdrMode(uacsh, UT_OFF);
  }
  else if(fcsmarg.ddr_mode==1){
     UTL_SetUbmAccessDdrMode(uacsh, UT_ON );
  }
  dutc = UTL_GetDutCursor(UT_CDUT);
  UTL_ClearUbmAccessPin(uacsh);
  int block=0;
  for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
     
    if(dutblock==0)block=1;
    if(dutblock==1)block=3;
    if(dutblock==2)block=5;
    if(dutblock==3)block=7;
    printf("block:%d\n",block);
    UTL_SetUbmAccessPin(uacsh, SOCKET.dutblock_iopinlist[dutblock]);
    UTL_SetUbmAccessPinBlock(uacsh, block);
    UTL_WriteUbmAllDut(uacsh, dutmax, wdata, size);
  }

  free(wdata);
  UTL_DeleteHandle(uacsh);

  return;
}

void write_ubm_multi(TEST_fcsmarg fcsmarg, int dutchcnt)
{
	int i, j,k;
	RadioButton dutblock;
	UT_DUT dut;
	UT_DUT dutmax;
	DutCursor dutc;
	USlider size;
	int sec_cnt=0;
	int afm_cnt=0;
	int dut_area=0;
	static fail_cnt=256;

	dutmax = 0;
	dutc = UTL_GetDutCursor(UT_CDUT);
	while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
		dutmax++;
	}
	UTL_DeleteCursor(dutc);
	
	size = UBMSIZE*sizeof(USlider);

//uchiyama
	int fcnt=0;
	int chcnt,xfercnt,sctrcnt,cnt;
	int xferlp=0x10;
	//uchiint xferlp=0x8;
	int lp=0x200;
	//uchi int lp=0x100;
	int ubmap=0;


	USlider wdata[dutmax][dutchcnt][UBMSIZE];
	for(i=0;i<dutmax;i++){
		for(j=0;j<dutchcnt;j++){
			for(k=0;k<UBMSIZE;k++){
				wdata[i][j][k]=0;
			}
		}
	}	

	for(chcnt=1;chcnt<=dutchcnt;chcnt++){
		for(dut=1;dut<=dutmax;dut++){
			ubmap=0;
			for(xfercnt=1;xfercnt<=xferlp;xfercnt++){
				for(sctrcnt=1;sctrcnt<=fcsmarg.sector;sctrcnt++){
					fcnt=(chcnt-1)+dutchcnt*(dut-1)+(sctrcnt-1)+fcsmarg.sector*(xfercnt-1);
					for(cnt=0;cnt<lp;cnt++){
						if(fcnt>cnt){
							if(cnt%4==0){wdata[dut-1][chcnt-1][ubmap]=0x03;}
							if(cnt%4==1){wdata[dut-1][chcnt-1][ubmap]=0x0C;}
							if(cnt%4==2){wdata[dut-1][chcnt-1][ubmap]=0x30;}
							if(cnt%4==3){wdata[dut-1][chcnt-1][ubmap]=0xC0;}
						}
//					if(DEBUG!=0){printf("[AP=0x%4X] ch=%2d, dut=%d, xfer=0x%2X, sector=%2d,fcnt=0x%4X cnt=0x%3X | wdata=0x%X \n",ubmap,chcnt,dut,xfercnt,sctrcnt,fcnt,cnt,wdata[dut-1][chcnt-1][ubmap]);}
					ubmap++;
//					if(DEBUG!=0){if(wdata[dut-1][chcnt-1][cnt]==0x6){printf("1");}else{printf("0");}	}
					}
				}
			}
		}
	}

	ubm_preset(0);
	
	UbmAccessHandle uacsh = UTL_GetUbmAccessHandle();
	UTL_SetUbmAccessBitReverse(uacsh, UT_ON);
	UTL_SetUbmAccessStartAddr(uacsh, 0x0);
	UTL_SetUbmAccessStopAddr (uacsh, UBMSIZE-1);
	UTL_SetUbmAccessDdrMode(uacsh, UT_OFF);		//SDR

	dutc = UTL_GetDutCursor(UT_CDUT);
	while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
		UTL_SetUbmAccessDut(uacsh, dut);
		for(chcnt=1;chcnt<=dutchcnt;chcnt++){
			UTL_ClearUbmAccessPin(uacsh);
			if      (dutchcnt==2){
				if     (chcnt==1){UTL_SetUbmAccessPin(uacsh, "IOPIN0");}
				else if(chcnt==2){UTL_SetUbmAccessPin(uacsh, "IOPIN1");}
				UTL_SetUbmAccessPinBlock(uacsh, 1);
			}else if(dutchcnt==4){
				UTL_SetUbmAccessPin(uacsh, SOCKET.dutblock_iopinlist[chcnt-1]);
				if     (dut%2==1 && chcnt==1){UTL_SetUbmAccessPinBlock(uacsh, 1);}	//P1-8
				else if(dut%2==1 && chcnt==2){UTL_SetUbmAccessPinBlock(uacsh, 3);}	//P65-72
				else if(dut%2==1 && chcnt==3){UTL_SetUbmAccessPinBlock(uacsh, 5);}	//P129-135
				else if(dut%2==1 && chcnt==4){UTL_SetUbmAccessPinBlock(uacsh, 7);}	//P193-200
				else if(dut%2==0 && chcnt==1){UTL_SetUbmAccessPinBlock(uacsh,11);}	//P1-8
				else if(dut%2==0 && chcnt==2){UTL_SetUbmAccessPinBlock(uacsh,13);}	//P65-72
				else if(dut%2==0 && chcnt==3){UTL_SetUbmAccessPinBlock(uacsh,15);}	//P129-135
				else if(dut%2==0 && chcnt==4){UTL_SetUbmAccessPinBlock(uacsh,17);}	//P193-200
			}
			UTL_WriteUbm(uacsh, wdata[dut-1][chcnt-1], size);
		}
	}
	UTL_DeleteCursor(dutc);
	UTL_DeleteHandle(uacsh);

#if (DEBUG)
	//Display UBM DATA
	uacsh = UTL_GetUbmAccessHandle();
	UTL_SetUbmAccessBitReverse(uacsh, UT_ON);
	UTL_SetUbmAccessStartAddr(uacsh, 0x0);
	UTL_SetUbmAccessStopAddr (uacsh, UBMSIZE-1);
	UTL_SetUbmAccessDdrMode(uacsh, UT_OFF);		//SDR

	dutc = UTL_GetDutCursor(UT_CDUT);
	while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
		UTL_SetUbmAccessDut(uacsh, dut);
		for(chcnt=1;chcnt<=dutchcnt;chcnt++){
			UTL_ClearUbmAccessPin(uacsh);
			if      (dutchcnt==2){
				if     (chcnt==1){UTL_SetUbmAccessPin(uacsh, "IOPIN0");}
				else if(chcnt==2){UTL_SetUbmAccessPin(uacsh, "IOPIN1");}
				UTL_SetUbmAccessPinBlock(uacsh, 1);
			}else if(dutchcnt==4){
				UTL_SetUbmAccessPin(uacsh, SOCKET.dutblock_iopinlist[chcnt-1]);
				if     (dut%2==1 && chcnt==1){UTL_SetUbmAccessPinBlock(uacsh, 1);}	//P1-8
				else if(dut%2==1 && chcnt==2){UTL_SetUbmAccessPinBlock(uacsh, 3);}	//P65-72
				else if(dut%2==1 && chcnt==3){UTL_SetUbmAccessPinBlock(uacsh, 5);}	//P129-135
				else if(dut%2==1 && chcnt==4){UTL_SetUbmAccessPinBlock(uacsh, 7);}	//P193-200
				else if(dut%2==0 && chcnt==1){UTL_SetUbmAccessPinBlock(uacsh,11);}	//P1-8
				else if(dut%2==0 && chcnt==2){UTL_SetUbmAccessPinBlock(uacsh,13);}	//P65-72
				else if(dut%2==0 && chcnt==3){UTL_SetUbmAccessPinBlock(uacsh,15);}	//P129-135
				else if(dut%2==0 && chcnt==4){UTL_SetUbmAccessPinBlock(uacsh,17);}	//P193-200
			}
			UTL_ReadUbm(uacsh, wdata[dut-1][chcnt-1], size);
		}
	}
	UTL_DeleteCursor(dutc);
	UTL_DeleteHandle(uacsh);


	int fail=0;
	for(dut=1;dut<=dutmax;dut++){
		for(chcnt=1;chcnt<=dutchcnt;chcnt++){
			ubmap=0;
			for(xfercnt=1;xfercnt<=xferlp;xfercnt++){
				for(sctrcnt=1;sctrcnt<=fcsmarg.sector;sctrcnt++){
					fail=0;
					for(cnt=0;cnt<lp;cnt++){
						if (wdata[dut-1][chcnt-1][ubmap]!=0x0){fail++;}
						ubmap++;
					}
					if(fcsmarg.captdat == 1){fail=fail*2;}
             	   	printf("[UBM WDATA] DUT:%2d,DUTCH:%2d,AFMXFER:0x%5X,SECTOR:%2d : FAIL CNT=0x%4X \n",dut,chcnt,xfercnt-1,sctrcnt,fail);fflush(stdout);
				}
			}
		}
	}


#endif


	
	return;
}

void write_ubm_each_dut(TEST_fcsmarg fcsmarg)
{
  int i, j,k;
  RadioButton dutblock;
  UT_DUT dut;
  UT_DUT dutmax;
  DutCursor dutc;
  USlider *wdata;
  USlider size;
  int sec_cnt=0;
  int afm_cnt=0;
  int dut_area=0;
  static fail_cnt=256;

  dutmax = 0;
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    dutmax++;
  }
  UTL_DeleteCursor(dutc);

  size = UBMSIZE*dutmax*sizeof(USlider);
  wdata = (USlider *)malloc(size);
  memset(wdata, 0x0, size);

  printf("dutmax:%d\n",dutmax);
  for(dut=1;dut<=dutmax;dut++){
    for(j=0; j<UBMSIZE/dutmax; j++){
      for(k=0;k<dutmax;k++){
        if((k+1)==dut){wdata[(dut-1)*UBMSIZE+j*dutmax+k]=1;}
      }
    }
  }

  ubm_preset(0);

  UbmAccessHandle uacsh = UTL_GetUbmAccessHandle();
  UTL_SetUbmAccessBitReverse(uacsh, UT_ON);
  UTL_SetUbmAccessDdrMode(uacsh, UT_OFF);
  UTL_SetUbmAccessStartAddr(uacsh, 0x0);
  UTL_SetUbmAccessStopAddr (uacsh, UBMSIZE-1);
  dutc = UTL_GetDutCursor(UT_CDUT);
  UTL_ClearUbmAccessPin(uacsh);
  UTL_SetUbmAccessPin(uacsh, SOCKET.all_iopinlist);
  UTL_SetUbmAccessPinBlock(uacsh, 1);
  UTL_WriteUbmAllDut(uacsh, dutmax, wdata, size);

  free(wdata);
  UTL_DeleteHandle(uacsh);

  return;
}

void burstscram_fcsm(RadioButton onoff)
{
    BurstScramHandle bsh = UTL_GetBurstScramHandle();
    UTL_SetBurstScramMode    (bsh, onoff   );
    UTL_SetBurstScramDdrType (bsh, 3       );
    UTL_SetBurstScramDataRate(bsh, 2       );  //DDR
    UTL_SetBurstScramLength  (bsh, 8       );
    UTL_SetBurstScramWrapType(bsh, UT_WPTIL);
    UTL_SetBurstScramAddrUnit(bsh, UT_UNIT_DFM, UT_ON);
    UTL_SendBurstScram       (bsh);
    UTL_DeleteHandle         (bsh);
}
void test_result(char tname[]){

    RadioButton dut_test_res[MAXDUTCNT]={0,};
    UT_DUT dutc;
    DutCursor dutcur;

    dutcur = UTL_GetDutCursor(UT_CDUT);
    while((dutc = UTL_NextDut(dutcur))!=UT_NOMORE){
        dut_test_res[dutc-1] = UTL_ReadTestResult(dutc, tname, UT_RES_ALL); 
        if(dut_test_res[dutc-1]==UT_RES_NOT_TESTED )
            printf("DUT[%d] Do not Judgment\n", dutc);  //UT_RES_NOT_TESTED=0
        else if(dut_test_res[dutc-1]==UT_RES_PASSED )
            printf("DUT[%d] is PASS\n", dutc);          //UT_RES_PASSED=2
        else if(dut_test_res[dutc-1]==UT_RES_FAILED )
            printf("DUT[%d] is FAILED\n", dutc);        //UT_READ_FAILED=3
    }
    UTL_DeleteCursor(dutcur);
}

void fcsm_init(RadioButton ilmd,int ddr)
{
    fcsm_ilmode(ilmd);
    fcsm_pin_list();
    fcsm_power_seq();
    fcsm_pin_condition(ddr);
    fcsm_level_setting(1, 1.00 V, 0.00 V);    // (channel, Vi high, Vi low)
}
void fcsm_init_multi(RadioButton ilmd,int ddr)
{
    fcsm_ilmode(ilmd);
//  fcsm_pin_list_multi();
    fcsm_power_seq();
    fcsm_pin_condition_multi(ddr);
    fcsm_level_setting(1, 1.00 V, 0.00 V);    // (channel, Vi high, Vi low)
}

void JudgeEccFcsm(USlider *dut_res )
{
     char *testname = UTL_ReadTestName();
     UT_DUT dut;
     DutCursor dutc;
     dutc = UTL_GetDutCursor(UT_CDUT);
     while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
          if(dut_res[dut-1]==0){
              UTL_ResetTestResult(dut, testname,UT_RES_ALL);
          }
          if(dut_res[dut-1]==1){
              UTL_SetTestResult(dut, testname,UT_RES_ALL);
          }
     }

}
void JudgeRte()
{
     char *testname = UTL_ReadTestName();
     UT_DUT dut;
     DutCursor dutc;
     dutc = UTL_GetDutCursor(UT_CDUT);
     while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
         UTL_SetTestResult(dut, testname,UT_RES_ALL);
     }

}

//static void fcsm_dutch_setting(TEST_fcsmarg fcsmarg)
//{
//    int dutblock;
//
//    DutChannelHandle dutch_h = UTL_GetDutChannelHandle();
//    UTL_SetDutChannelMode    (dutch_h, UT_ON);
//    UTL_SetDutChannelCount   (dutch_h, 2);
//
//	UTL_SetDutChannelPinList (dutch_h, 0 , "IOPIN0");
//	UTL_SetDutChannelPinList (dutch_h, 1 , "IOPIN1");
//
//    UTL_SendDutChannel       (dutch_h);
//    UTL_DeleteHandle         (dutch_h);
//}

static void fcsm_dutch_setting(TEST_fcsmarg fcsmarg, int dutchcnt)
{
	int i;

    DutChannelHandle dutch_h = UTL_GetDutChannelHandle();
    UTL_SetDutChannelMode    (dutch_h, UT_ON);
    UTL_SetDutChannelCount   (dutch_h, dutchcnt);

	printf("##### dutchcnt=%d \n", dutchcnt);
	if(dutchcnt==2){
		UTL_SetDutChannelPinList (dutch_h, 0, "IOPIN0");
		UTL_SetDutChannelPinList (dutch_h, 1, "IOPIN1");
	}else if(dutchcnt==4){
		for(i=0;i<dutchcnt;i++){
			UTL_SetDutChannelPinList (dutch_h, i, SOCKET.dutblock_iopinlist[i]);
		}
	}

    UTL_SendDutChannel       (dutch_h);
    UTL_DeleteHandle         (dutch_h);
}

/**********************************************************************
   Ecc Counter -> Fcsm Read Check(SDR Mode)
***********************************************************************/
void fcsm_test_1(TEST_testitem *testarg)
{
    int mode=0;
    fcsm_init(FCSMARG.ilmode,FCSMARG.ddr_mode);
    fcsm_timing_setting(FCSMARG.rate,FCSMARG.ilmode);
    fcsm_readtname();
    
    fcsm_set_condition(FCSMARG);
    fcsm_clear();	
    ecc_set_condition(FCSMARG);

    if(FCSMARG.afmxfer_cnt<=0x1000){
       set_ubm_data(FCSMARG);
       write_ubm_evenodd(FCSMARG,mode);
    }
    fcsm_MeasFct(FCSMARG, UT_OFF, UT_OFF);
    readfcsm(FCSMARG);
    test_result(testarg->testname);
}

/**********************************************************************
   Accumulation Fail Count Check
***********************************************************************/
void fcsm_test_2(TEST_testitem *testarg)
{
    int mode=0;
    fcsm_init(FCSMARG.ilmode,FCSMARG.ddr_mode);
    fcsm_timing_setting(FCSMARG.rate,FCSMARG.ilmode);
    fcsm_readtname();
    
    fcsm_set_condition(FCSMARG);
    fcsm_clear();	
    ecc_set_condition(FCSMARG);

    set_ubm_data(FCSMARG);
    write_ubm_evenodd(FCSMARG,mode);

    fcsm_MeasFct_2nd(FCSMARG, UT_OFF, UT_OFF);
    fcsm_MeasFct_2nd(FCSMARG, UT_OFF, UT_OFF);
    readfcsm(FCSMARG);
    test_result(testarg->testname);
}

/**********************************************************************
   Wait Function Check
***********************************************************************/
void fcsm_test_3(TEST_testitem *testarg)
{
    int mode=0;
    fcsm_init(FCSMARG.ilmode,FCSMARG.ddr_mode);
    fcsm_timing_setting(FCSMARG.rate,FCSMARG.ilmode);
    fcsm_readtname();
    
    fcsm_set_condition(FCSMARG);
    fcsm_clear();	
    ecc_set_condition(FCSMARG);

    set_ubm_data(FCSMARG);
    write_ubm_evenodd(FCSMARG,mode);

    fcsm_MeasFct_Wait(FCSMARG, UT_OFF, UT_OFF);
    readfcsm(FCSMARG);
    test_result(testarg->testname);
}

/**********************************************************************
   All Dut Ecc Count diffrent condition.
***********************************************************************/
void fcsm_test_4(TEST_testitem *testarg)
{
    fcsm_init(FCSMARG.ilmode,FCSMARG.ddr_mode);
    fcsm_timing_setting(FCSMARG.rate,FCSMARG.ilmode);
    fcsm_readtname();
    
    fcsm_set_condition(FCSMARG);
    fcsm_clear();	
    ecc_set_condition(FCSMARG);

    set_ubm_data(FCSMARG);
    write_ubm_each_dut(FCSMARG);

    fcsm_MeasFct(FCSMARG, UT_OFF, UT_OFF);
    readfcsm_each_dut(FCSMARG);
    test_result(testarg->testname);
}
/**********************************************************************
   Ecc Counter -> Fcsm Read Check(DDR Mode)
***********************************************************************/
void fcsm_test_5(TEST_testitem *testarg)
{
    int mode=0;
    fcsm_init(FCSMARG.ilmode,FCSMARG.ddr_mode);
    fcsm_timing_setting(FCSMARG.rate,FCSMARG.ilmode);
    fcsm_readtname();
    
    fcsm_set_condition(FCSMARG);
    fcsm_clear();	
    ecc_set_condition(FCSMARG);

    set_ubm_data(FCSMARG);
    write_ubm_evenodd(FCSMARG,mode);
    burstscram_fcsm(UT_ON);
    fcsm_MeasFct(FCSMARG, UT_OFF, UT_OFF);
    readfcsm(FCSMARG);
    test_result(testarg->testname);
}

///**********************************************************************
//   Ecc Counter -> Fcsm Read Check(t5835_8dut_bit16.soc)
//***********************************************************************/
//void fcsm_test_6(TEST_testitem *testarg)
//{
//    int mode=1;
//    fcsm_pin_list_multi();
//    fcsm_init_multi(FCSMARG.ilmode,FCSMARG.ddr_mode);
//    fcsm_timing_setting(FCSMARG.rate,FCSMARG.ilmode);
//    fcsm_readtname();
//    
//    if(FCSMARG.child==0)fcsm_set_condition_multi(FCSMARG,"IOPIN0");
//    if(FCSMARG.child==1)fcsm_set_condition_multi(FCSMARG,"IOPIN1");
//    fcsm_clear();	
//    ecc_set_condition(FCSMARG);
//
//    if(FCSMARG.afmxfer_cnt<=0x1000){
//       set_ubm_data(FCSMARG);
//       write_ubm_evenodd(FCSMARG,mode);
//    }
//    fcsm_MeasFct(FCSMARG, UT_OFF, UT_OFF);
//    readfcsm(FCSMARG);
//    test_result(testarg->testname);
//}


/**********************************************************************
   Ecc Counter -> Fcsm Read Check Multi Ch(t5835_8dut_bit16.soc)
***********************************************************************/
//void fcsm_multi_test(TEST_testitem *testarg)
//{
//
//    fcsm_pin_list_multi();
//    fcsm_dutch_setting(FCSMARG);
//    fcsm_init_multi(FCSMARG.ilmode,FCSMARG.ddr_mode);
//    fcsm_timing_setting(FCSMARG.rate,FCSMARG.ilmode);
//    fcsm_readtname();
//    
//    fcsm_set_condition_multi(FCSMARG,SOCKET.all_iopinlist);
//    fcsm_clear();	
//    ecc_set_condition(FCSMARG);
//
////  if(FCSMARG.afmxfer_cnt<=0x1000){
//       set_ubm_data_multi(FCSMARG);
//       write_ubm_evenodd_multi(FCSMARG);
////  }
//    fcsm_MeasFct(FCSMARG, UT_OFF, UT_OFF);
//    readfcsm_multi(FCSMARG);
//    test_result(testarg->testname);
//}

/**********************************************************************
   Ecc Counter -> Fcsm Read Check Multi Ch
***********************************************************************/
void fcsm_test_multi(TEST_testitem *testarg)
{
	int dutchcnt;
	if(SOCKET.dutblock_count==1){dutchcnt=2;} //for 1FB 2CH Socket
	if(SOCKET.dutblock_count==4){dutchcnt=4;} //for 4FB 4CH Socket

    fcsm_pin_list_multi(dutchcnt);
    fcsm_dutch_setting(FCSMARG, dutchcnt);
    fcsm_init_multi(FCSMARG.ilmode,FCSMARG.ddr_mode);
    fcsm_timing_setting(FCSMARG.rate,FCSMARG.ilmode);
    fcsm_readtname();
    
    fcsm_set_condition_multi(FCSMARG,SOCKET.all_iopinlist);
    fcsm_clear();	
    ecc_set_condition(FCSMARG);

    set_ubm_data_multi(FCSMARG);
    write_ubm_multi(FCSMARG, dutchcnt);
    fcsm_MeasFct_multi(FCSMARG, UT_ON, UT_ON);
    readfcsm_multi(FCSMARG);
    test_result(testarg->testname);
}
