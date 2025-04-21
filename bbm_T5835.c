
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "UTSC.h"
#include "test.h"
#include "test_struct.h"
#include "bbm.h"
#include "common.h"



#define DEBUG 1
#define V *1.0
#define ms *1.0e-3
#define us *1.0e-6
#define ns *1.0e-9
#define mA *1.0e-3
#define uA *1.0e-6
#define nA *1.0e-9

#define BITCNT8  8
//////////////////////////////////////////////////////////////////////////
// BBM settings
//////////////////////////////////////////////////////////////////////////
#define DUTMAX  32
#define BBLMT   17         //BBC LIMIT
//////////////////////////////////////////////////////////////////////////
#define BBM_XBIT_ALL	18								//x bit count all block
//#define BBM_XBIT	4									//x bit count
#define BBM_XBIT	18									//x bit count
#define BBM_YBIT	0									//y bit count
#define BBM_XMAX_ALL	(0x1<<BBM_XBIT_ALL)-1
#define BBM_XMAX		(0x1<<BBM_XBIT)-1
#define BBM_YMAX		(0x1<<BBM_YBIT)-1
#define BBM_SIZE_ALL	(BBM_XMAX_ALL+1)*(BBM_YMAX+1)
#define BBM_SIZE		(BBM_XMAX+1)*(BBM_YMAX+1)
//////////////////////////////////////////////////////////////////////////

int pincount = 0;
USlider  bb_addr[DUTMAX][BBM_SIZE] = {{0}};
USlider  bbc[DUTMAX] = {0};

/**
 * @file main.c
 * @author Advantest Corp.
 * @brief Sample Code For BBM Test
 * @version 0.1
 * @date 2021-09
 */

/*
 *  ReadFunc
 *    Get pass/fail for each pin per DUT.
 *    It is useful for debugging.
 */
void ReadFunc()
{
    ScFailPinHandle scfph;
    PinCursor pinc;
    DutCursor dutc;
    UT_PIN pin;
    UT_DUT dut;
    CheckButton res;

    scfph = UTL_GetScFailPinHandle();

    pinc = UTL_GetPinCursor("IOPIN");
    while ((pin = UTL_NextPin(pinc)) != UT_NOMORE) {
       UTL_AddScFailPinTargetPinNumber(scfph, pin);
    }
    UTL_DeleteCursor(pinc);
    UTL_SetScFailPinUpdateMode(scfph, UT_RES_TOTAL_FAILED);
    UTL_UpdateScFailPin(scfph);

    dutc = UTL_GetDutCursor(UT_SDUT);
    while ((dut = UTL_NextDut(dutc)) != UT_NOMORE) {
       pinc = UTL_GetScFailPinTargetPinCursor(scfph);
       while ((pin = UTL_NextPin(pinc)) != UT_NOMORE) {
          UTL_GetScFailPin(scfph, dut, pin, &res);
          printf("DUT %2d, Pin %2d Res %d\n", dut, pin, res);
       }
       UTL_DeleteCursor(pinc);
    }
    UTL_DeleteCursor(dutc);
    UTL_DeleteHandle(scfph);
}

void SetResetDut(CheckButton setreset)
{
    UT_DUT dut;
    char *tname = UTL_ReadTestName();
    int exchld;

    if (strstr(tname,"<A1>") != NULL) exchld = 1;  //<A1>
    else                              exchld = 2;  //<A2>

    ExclusionHandle eh = UTL_GetExclusionHandle();
    DutCursor dutc = UTL_GetDutCursor(UT_SDUT); 
    while ((dut=UTL_NextDut(dutc))!=UT_NOMORE){
       if     (dut >=17 && exchld == 1) { UTL_AddExclusionDut(eh, dut); printf("DUT=%d\n",dut); }
       else if(dut <=16 && exchld == 2) { UTL_AddExclusionDut(eh, dut); printf("DUT=%d\n",dut); }
    }
    UTL_SetExclusionMask      (eh, UT_ON);
    UTL_SetExclusionSetOrReset(eh, setreset);
    UTL_SendExclusion(eh);

#if 1
    printf("%s child <A%1d> setreset=%d",__func__, exchld, setreset);
#endif

    UTL_DeleteHandle(eh);
    UTL_DeleteCursor(dutc);

}

//ilmode R031124
void ilmode(RadioButton ilmd)
{
//  RadioButton mode = 8;
    IlModeHandle ilmh = UTL_GetIlModeHandle();
    UTL_SetIlMode   (ilmh, ilmd);
    UTL_SendIlMode  (ilmh);
    UTL_DeleteHandle(ilmh);

}

void pin_list(void)
{
    const int ptyp[] = { UT_SOCKET_PINTYPE_IO, UT_SOCKET_PINTYPE_DR };
    const int ptypcnt = sizeof(ptyp)/sizeof(ptyp[0]);
    int ptypidx;
    int *plst[ptypcnt], pcnt[ptypcnt], i;

    pincount = 0;

    //Pin type loop (DR & IO)
    for (ptypidx=0; ptypidx<ptypcnt; ptypidx++){
        if (UTSOCK_Info_GetDutPinList(ptyp[ptypidx], &plst[ptypidx], &pcnt[ptypidx])!=UTSOCK_OK){
            fputs("ERROR: UTSOCK_Info_GetDutPinList returns non-UTSOCK_OK",stderr);
            UTL_Stop();
        }
        pincount += pcnt[ptypidx];
    }
    printf("[DEBUG]pincount = %d\n", pincount);
    
    
    if( pincount == 9) {
       UTL_CreatePinList ("IOPIN");
       UTL_SetPinType    ("IOPIN",UT_PINTYPE_PIN);
       for (i=0; i<pcnt[0]; i++) UTL_AddPinNumber ("IOPIN", plst[0][i] );
    }
    else if( pincount == BITCNT8) { // with a dr-cp DSA
       UTL_CreatePinList ("DRPIN");
       UTL_SetPinType    ("DRPIN",UT_PINTYPE_PIN);
       for (i=0; i<pcnt[0]/2; i++)       UTL_AddPinNumber ("DRPIN", plst[0][i] );
       UTL_CreatePinList ("IOPIN");
       UTL_SetPinType    ("IOPIN",UT_PINTYPE_PIN);
       for (i=pcnt[0]/2; i<pcnt[0]; i++) UTL_AddPinNumber ("IOPIN", plst[0][i] );
    }
    if (pcnt[1]) {
       fputs("ERROR: UT_SOCKET_PINTYPE_DR exists",stderr);
       UTL_Stop();
    }

}

void power_seq(void)
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
void pin_condition(void)
{
    int i;
    PinHandle tesph = UTL_GetPinHandle();

    printf("[DEBUG]%s\n",__func__);

    if(pincount == 9) {  //without any DSA
       UTL_SetPinViNumber     (tesph, 1);
       UTL_SetPinDrWaveform   (tesph, UT_WAV_RZO);
       UTL_SetPinDrClock      (tesph, UT_PIN_BCLK, 1);
       UTL_SetPinDrClock      (tesph, UT_PIN_CCLK, 1);
       UTL_SetPinIoCtrl       (tesph, UT_ON);
       UTL_SetPinVoNumber     (tesph, 1);
       UTL_SetPinVtNumber     (tesph, 1);
       UTL_SetPinTerm         (tesph, UT_ON);	//20211214
       UTL_SetPinDreNumber    (tesph, 1);
       UTL_SetPinDreWaveform  (tesph, UT_DREWAV_NRZ);
       UTL_SetPinDreClock     (tesph, 1); 
       UTL_AddPinStrbCpeNumber(tesph, 1, 1);
       for ( i=0; i<pincount; i++ )
       {
           UTL_AddPinPdsA      (tesph, UT_SIG_X(i), 1);
           UTL_AddPinPdsB      (tesph, UT_SIG_Y(i), 1);
           UTL_AddPinPdsA      (tesph, UT_SIG_Y(i), 2);
           UTL_AddPinPdsB      (tesph, UT_SIG_D(i), 2);
       }
       UTL_SendPin(tesph, "IOPIN");
    }

    else if(pincount == BITCNT8) {  //with dr-cp DSA
       UTL_SetPinViNumber     (tesph, 1);           
       UTL_SetPinDrWaveform   (tesph, UT_WAV_RZO);
       UTL_SetPinDrClock      (tesph, UT_PIN_BCLK, 1);
       UTL_SetPinDrClock      (tesph, UT_PIN_CCLK, 1);
       for (i=0; i<pincount/2; i++) {
          UTL_AddPinPdsA      (tesph, UT_SIG_X(i), 1);
          UTL_AddPinPdsA      (tesph, UT_SIG_Y(i), 2);
       }
       UTL_SetPinPatternInh   (tesph, UT_ON);         //BBM Mask(Only for T5771)
       UTL_SetPinPatternInhLevel(tesph, UT_PIN_LOW);  //BBM Mask(Only for T5771)
       UTL_SendPin            (tesph,"DRPIN");      

       UTL_InitializePinHandle(tesph);
       UTL_SetPinVoNumber     (tesph, 1);
       UTL_SetPinVtNumber     (tesph, 1);
       UTL_SetPinTerm         (tesph, UT_ON);
       UTL_AddPinStrbCpeNumber(tesph, 1, 1);
       for (i=0; i<pincount/2; i++) {
          UTL_AddPinPdsD      (tesph, UT_SIG_Y(i), 1);
          UTL_AddPinPdsD      (tesph, UT_SIG_D(i), 2);
       }
       UTL_SendPin            (tesph,"IOPIN");      
    }

    UTL_DeleteHandle(tesph);
}

//R031124 For @speed test
void pin_condition_ddr(RadioButton wvfm)
{
    int i;
    PinHandle tesph = UTL_GetPinHandle();

    UTL_SetPinViNumber     (tesph, 1);
    UTL_SetPinDrWaveform   (tesph, wvfm);
    UTL_SetPinTerm         (tesph, UT_ON);	//20211214
    UTL_SetPinIoCtrl       (tesph, UT_ON);
    UTL_SetPinDreNumber    (tesph, 1);
    UTL_SetPinDreWaveform  (tesph, UT_DREWAV_NRZ);
    UTL_SetPinDreClock     (tesph, 1); 
    UTL_SetPinVoNumber     (tesph, 1);
    UTL_AddPinStrbCpeNumber(tesph, 1, 1);
    UTL_AddPinStrbCpeNumber(tesph, 2, 1);
    UTL_AddPinExpStrbNumber(tesph, 1, UT_PIN_EXP_A);  //R31217
    UTL_AddPinExpStrbNumber(tesph, 2, UT_PIN_EXP_B);  //R31217

    for ( i=0; i<pincount; i++ ) {
        UTL_AddPinPdsA      (tesph, UT_SIG_D(i),  1); //R31217
        UTL_AddPinPdsB      (tesph, UT_SIG_SD(i), 1); //R31217
    }
    UTL_SendPin(tesph, "IOPIN");
}

void change_pds_for_nDUTs(int oedut)
{
    PinHandle pinh=UTL_GetPinHandle();
    DutCursor dutc;
    UT_DUT dut;
    int i;

    UTL_SetPinTargetDutCondition(pinh, UT_PIN_PDS_SET);
    dutc = UTL_GetDutCursor(UT_SDUT); 
    while ((dut=UTL_NextDut(dutc))!=UT_NOMORE){
       if(dut%2 == oedut)  UTL_AddPinTargetDut(pinh, dut);
    }

    for ( i=0; i<pincount; i++ )
    {
        UTL_AddPinPdsA      (pinh, UT_SIG_I_X(i), 1);
        UTL_AddPinPdsB      (pinh, UT_SIG_I_Y(i), 1);
        UTL_AddPinPdsA      (pinh, UT_SIG_I_Y(i), 2);
        UTL_AddPinPdsB      (pinh, UT_SIG_I_D(i), 2);
    }
    UTL_SendPin(pinh, "IOPIN");
}

void FailCaptureSelect(RadioButton dutgrp)
{
    FailCaptureSelectHandle fcsh = -1;

    printf("%s   dutgrp=%d\n",__func__, dutgrp);
    if(fcsh < 0) {
        fcsh = UTL_GetFailCaptureSelectHandle();
        UTL_SetFailCaptureSelectAllDutGroupNumber(fcsh, UT_OFF);
    }
    UTL_SetFailCaptureSelectDutGroupNumber(fcsh, dutgrp);
    UTL_SendFailCaptureSelect(fcsh);

}

void bbm_FailSelPin_(char *pins, RadioButton captdat)
{
    FailSelPinHandle failselpinh;
    UT_PIN  pin=0;
    PinCursor pcr;
    RadioButton target;
    int i=0;
#if 0
    fprintf( stdout, " ********************************************\n");
    fprintf( stdout, " ***  %s()\n", __FUNCTION__);
    fprintf( stdout, " ********************************************\n"); fflush(stdout);
#endif
    failselpinh = UTL_GetFailSelPinHandle();
    
//  UTL_ClearFailSelPinAssign(failselpinh);
    switch (captdat) {
        case UT_BBM_READFAIL:        target = UT_FAILSELPIN_TARGET_READ_FAIL; printf("%s READ_FAIL\n",__func__);i=9;break;
        case UT_BBM_ECCTOTALCOUNT(1):target = UT_FAILSELPIN_TARGET_ECC_TOTAL; printf("%s ECC_TOTAL\n",__func__);break;
        case UT_BBM_ECCORCOUNT(1):   target = UT_FAILSELPIN_TARGET_ECC_OR;    printf("%s ECC_OR   \n",__func__);break;
        defalut             : printf("%s : Unexpected FAILSELPIN is selected\n"); UTL_Stop();
    }
    UTL_SetFailSelPinTarget(failselpinh, target);
    
    pcr=UTL_GetPinCursor(pins);
    while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
        fprintf( stdout, "  UTL_SetFailSelPin( %2d )\n", pin);
    	UTL_SetFailSelPin(failselpinh, pin, UT_ON);
        i++;
        if(i == 8) break;
    }
    UTL_SendFailSelPin (failselpinh);
    UTL_DeleteHandle   (failselpinh);
}

/*
 * level_setting
 *
 */
void level_setting(int channel, DSlider high, DSlider low)
{
    printf("[DEBUG]%s\n",__func__);
    DSlider vtl = (high+low)/2;

    ViHandle vih = UTL_GetViHandle();
    UTL_SetViHigh(vih, high   );
    UTL_SetViLow (vih, low    );
    UTL_SendVi   (vih, channel);

    VtHandle vth = UTL_GetVtHandle();
    UTL_SetVt (vth, vtl);
    UTL_SendVt(vth, channel);

    VoHandle voh = UTL_GetVoHandle();
    UTL_SetVoHigh(voh, vtl);   //This is used as VOH & VOL
    UTL_SetVoLow (voh, vtl);
    UTL_SendVo   (voh, channel);

    UTL_DeleteHandle(vih);
    UTL_DeleteHandle(vth);
    UTL_DeleteHandle(voh);
}

void level_setting_ddr(int channel, DSlider high, DSlider low)
{
    printf("[DEBUG]%s\n",__func__);
    DSlider vtl = (high+low)/2;

    ViHandle vih = UTL_GetViHandle();
    UTL_SetViHigh(vih, high   );
    UTL_SetViLow (vih, low    );
    UTL_SendVi   (vih, channel);

    VtHandle vth = UTL_GetVtHandle();
    UTL_SetVt (vth, high);
    UTL_SendVt(vth, channel);

    VoHandle voh = UTL_GetVoHandle();
    UTL_SetVoHigh(voh, vtl);   //This is used as VOH & VOL
    UTL_SetVoLow (voh, vtl);
    UTL_SendVo   (voh, channel);

    UTL_DeleteHandle(vih);
    UTL_DeleteHandle(vth);
    UTL_DeleteHandle(voh);
}

void level_fix(UT_DUT dut, RadioButton level, char *pinname)
{
   static LevelFixHandle lfh = -1;
   UT_PIN pin;
   PinCursor pinc;

   if(lfh < 0) lfh = UTL_GetLevelFixHandle();

   UTL_SetLevelFixOutputLevel(lfh, UT_PIN_DR, level); /* UT_PIN_FIXH:Pass */
   pinc = UTL_GetPinCursor(pinname);
   while((pin = UTL_NextPin(pinc)) != UT_NOMORE) {
      UTL_SendLevelFix(lfh, pin, dut);
//    printf("%s .... pin %d DUT %d\n",__func__, pin, dut);
   }
   UTL_DeleteCursor(pinc);
}

void level_setting_perpin(void)
{
    UT_DUT dutc;
    DutCursor dutcur;
    UT_PIN pinc;
    PinCursor pincur;

    ViHandle vih = UTL_GetViHandle();
    dutcur = UTL_GetDutCursor(UT_CDUT); 
    while((dutc=UTL_NextDut(dutcur))!=UT_NOMORE){
        pincur = UTL_GetPinCursor("IOPIN");
        while((pinc=UTL_NextPin(pincur))!=UT_NOMORE){
            if     (dutc%2==0) UTL_SetViHigh (vih, 0.50 V);
            else if(dutc%2==1) UTL_SetViHigh (vih, 2.00 V);
            UTL_SetViLow(vih, 0.30 V);
            UTL_SendViPerPin(vih,pinc,dutc);	
        }
        UTL_DeleteCursor(pincur);
    }
    UTL_DeleteCursor(dutcur);


    DcHandle dch = UTL_GetDcHandle();
    UTL_SetDcMode     (dch, UT_DCT_MVM);
    UTL_SetDcMrange   (dch, 7.00 V, 0.00 V);
    UTL_SetDcLimitHigh(dch, 2.05 V, UT_OFF);
    UTL_SetDcLimitLow (dch, 0.45 V, UT_OFF);
    UTL_SetDcMeasCnt  (dch, 100);
    UTL_SendDc        (dch, 1);

    UTL_DeleteHandle(vih);
    UTL_DeleteHandle(dch);
}

/*
 *  timing_setting
 *    R031101  Modify Bclk 0.00 -> 0.25
      R031124  STRB2 is newly added.
 *
 */
void timing_setting(DSlider tck)
{
    TgHandle tgh = UTL_GetTgHandle();
    UTL_AddTgRate(tgh, 1,    tck);
    UTL_AddTgBclk(tgh, 1, 1, tck*0.25);  UTL_AddTgCclk(tgh, 1, 1, tck*0.75);
    UTL_AddTgDreL(tgh, 1, 1, tck*0.00);  UTL_AddTgDreT(tgh, 1, 1, tck*0.00);
    UTL_AddTgStrb(tgh, 1, 1, tck*0.50);  UTL_AddTgStrb(tgh, 1, 2, tck*1.00);
    UTL_SendTg   (tgh);

    UTL_DeleteHandle(tgh);
}

void readtname(){
    char *tname;
    tname = UTL_ReadTestName();
    printf("\nTEST NAME : %s\n",tname);	
}


void MeasFct(char *mpat, USlider pc, RadioButton pgstop, RadioButton pgclear)
{

    static FctHandle fct = -1;

    if (fct < 0) fct = UTL_GetFctHandle();
    UTL_SetFctMpatName   (fct, mpat);
    UTL_SetFctStartPc    (fct, pc);         
    UTL_SetFctFailInhibit(fct, pgstop);
    UTL_SetFctNoClear    (fct, pgclear);
	
    UTL_MeasFct(fct);
}

/**
* @brief Get the program counter value and execute MeasFct.
* 
*/
 

void bbm_set_condition_capture(TEST_bbmarg bbmarg)
{
    BbmConfigHandle	bbmconfigh;
    int i;
    
    bbm_FailSelPin_("IOPIN", bbmarg.captdat);
    
    bbmconfigh = UTL_GetBbmConfigHandle();

    for (i=0; i<BBM_YBIT; i++) UTL_SetBbmConfigAddrAssign      (bbmconfigh, i, UT_SIG_Y(i));
    for (i=0; i<BBM_XBIT; i++) UTL_SetBbmConfigAddrAssign      (bbmconfigh, i+BBM_YBIT, UT_SIG_X(i));
    UTL_SetBbmConfigMode                    (bbmconfigh, bbmarg.mode);
    UTL_SetBbmConfigAction                  (bbmconfigh, UT_BBM_MASKINH);
    UTL_SetBbmConfigStoreMode               (bbmconfigh, UT_BBM_SELECTEDDATA);
    UTL_SetBbmConfigDataGenerationMode      (bbmconfigh, UT_BBM_DISABLE);
    UTL_SetBbmConfigWriteEnableAllDut       (bbmconfigh, UT_ON);
    UTL_AddBbmConfigCaptureDataByTargetBank (bbmconfigh, 0, 1, 0, bbmarg.captdat);
    UTL_SetBbmConfigCounterNoClear          (bbmconfigh, UT_BBM_COUNTER_BBC, UT_OFF);
    UTL_SendBbmConfig                       (bbmconfigh);
    UTL_DeleteHandle                        (bbmconfigh);

    if (bbmarg.captdat != UT_BBM_READFAIL) {
       EccConfigHandle eccconfigh;

       eccconfigh = UTL_GetEccConfigHandle();
       if      (bbmarg.captdat == UT_BBM_ECCORCOUNT(1))    UTL_SetEccConfigCounterLimit(eccconfigh, UT_ECC_COUNTMODE_OR,    1, bbmarg.ecclmt);
       else if (bbmarg.captdat == UT_BBM_ECCTOTALCOUNT(1)) UTL_SetEccConfigCounterLimit(eccconfigh, UT_ECC_COUNTMODE_TOTAL, 1, bbmarg.ecclmt);
       UTL_SetEccConfigCounterEnableSignal     (eccconfigh, 0,   UT_SIG_C(7));
       UTL_SetEccConfigJudgeSignal             (eccconfigh, 0,   bbmarg.eccjdg);
       UTL_SetEccConfigCounterClearSignal      (eccconfigh,      UT_SIG_C(9));
       UTL_SetEccConfigSectorSwitchSignal      (eccconfigh,      UT_SIG_C(3));
       UTL_SetEccConfigSectorCount             (eccconfigh,      bbmarg.sector ); //T5835
       UTL_SendEccConfig                       (eccconfigh);
       UTL_DeleteHandle                        (eccconfigh);
    }

}

void bbm_set_condition_capture_limit(RadioButton mode, RadioButton captdat)
{
    BbmConfigHandle	bbmconfigh;
    
    bbm_FailSelPin_("IOPIN", captdat);
    
    int i;
    bbmconfigh = UTL_GetBbmConfigHandle();
    for (i=0; i<BBM_YBIT; i++) UTL_SetBbmConfigAddrAssign      (bbmconfigh, i, UT_SIG_Y(i));
    for (i=0; i<BBM_XBIT; i++) UTL_SetBbmConfigAddrAssign      (bbmconfigh, i+BBM_YBIT, UT_SIG_X(i));
    
    UTL_SetBbmConfigMode                    (bbmconfigh, mode);
    UTL_SetBbmConfigAction                  (bbmconfigh, UT_BBM_MASKINH);
//  UTL_SetBbmConfigAction                  (bbmconfigh, UT_BBM_CPINH);
    UTL_SetBbmConfigStoreMode               (bbmconfigh, UT_BBM_SELECTEDDATA);
    UTL_SetBbmConfigDataGenerationMode      (bbmconfigh, UT_BBM_MASK_SELECTEDBIT);
    UTL_SetBbmConfigWriteEnableAllDut       (bbmconfigh, UT_ON);
    UTL_AddBbmConfigCaptureDataByTargetBank (bbmconfigh, 0, 1, 0, UT_BBM_READFAIL);
    UTL_SetBbmConfigCounterNoClear          (bbmconfigh, UT_BBM_COUNTER_BBC, UT_OFF);
    
    UTL_SetBbmConfigBbcLimitByBit           (bbmconfigh,  BBLMT,0);
//  UTL_SetBbmConfigBbcLimitByBit           (bbmconfigh,0x7ffff,0);
    UTL_AddBbmConfigBbcLimitMaskBit         (bbmconfigh,     0);
//  UTL_AddBbmConfigMaskBitByTargetBank     (bbmconfigh, 1, 0, 0); 
    
    UTL_SendBbmConfig                       (bbmconfigh);
    UTL_DeleteHandle                        (bbmconfigh);

}


void bbm_read_address(RadioButton dutgrp, int disp_data)
{
    static BbmAccessHandle bbmaccessh = -1;
    DutCursor	dutc;
    int		dut;
    int		i;
    int		array_size = BBM_SIZE*DUTMAX;
    
    if (bbmaccessh < 0) { 
       bbmaccessh = UTL_GetBbmAccessHandle();
       UTL_SetBbmAccessBitMode     (bbmaccessh, UT_FCM_BITMODE_NORMAL); //<- UT_FCM_BITMODE_BLOCK
       UTL_SetBbmAccessStartAddr   (bbmaccessh, 0);
       UTL_SetBbmAccessStopAddr    (bbmaccessh, BBM_SIZE-1);
       UTL_SetBbmAccessAllBit      (bbmaccessh, UT_ON);
       UTL_SetBbmAccessAllDut      (bbmaccessh, UT_OFF);
       UTL_SetBbmAccessCounterMode (bbmaccessh, UT_BBM_COUNTERMODE_REALTIME_SELECTEDBIT); //By default
    }
    
    dutc = UTL_GetDutCursor(UT_SDUT);
    while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
       if(pincount == 9) {
           if      (dutgrp == 0 && (dut%4 == 3 || dut%4 == 0 )) continue;
           else if (dutgrp == 1 && (dut%4 == 1 || dut%4 == 2 )) continue;
       }
       else if(pincount == BITCNT8) {
           if      (dutgrp == 0 && (dut > 16 )) continue;
           else if (dutgrp == 1 && (dut < 17 )) continue;
       }
       UTL_SetBbmAccessDut         (bbmaccessh, dut);
       UTL_ReadBbm(bbmaccessh, bb_addr[dut-1], sizeof(bb_addr[dut-1]));
#if 0
           if(disp_data == 0 || disp_data ==1) {
              for (i=0; i<BBM_SIZE; i++) {
              	if (bb_addr[dut-1][i] == disp_data) printf(" ( %6d ):0x%02X\n", i, bb_addr[dut-1][i]);
              }
           }
           else if (disp_data == 2) {
              for (i=0; i<BBM_SIZE/2; i++) {
              	if (bb_addr[dut-1][i*2] != 0)   printf(" ( %6d ):0x%02X\n", i, bb_addr[dut-1][i*2]);
              	if (bb_addr[dut-1][i*2+1] != 1) printf(" ( %6d ):0x%02X\n", i, bb_addr[dut-1][i*2+1]);
              }
           }
           puts("");
#endif
    }
    UTL_DeleteCursor    (dutc);
//  UTL_DeleteHandle    (bbmaccessh);
}

void DebugReadBbm(RadioButton dutgrp)
{
    DutCursor	dutc;
    int		dut;
    int		i;
    int		bbm[DUTMAX][BBM_SIZE] = {{0}};
    int		array_size = BBM_SIZE*DUTMAX;
    
    BbmAccessHandle bbmaccessh = UTL_GetBbmAccessHandle();
    UTL_SetBbmAccessBitMode     (bbmaccessh, UT_FCM_BITMODE_BLOCK);
    UTL_SetBbmAccessStartAddr   (bbmaccessh, 0);
    UTL_SetBbmAccessStopAddr    (bbmaccessh, BBM_SIZE-1);
    UTL_SetBbmAccessAllBit      (bbmaccessh, UT_ON);
    UTL_SetBbmAccessAllDut      (bbmaccessh, UT_OFF);
    UTL_SetBbmAccessCounterMode (bbmaccessh, UT_BBM_COUNTERMODE_REALTIME_SELECTEDBIT);
    
    dutc = UTL_GetDutCursor(UT_SDUT);
    while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
       if(pincount == 9) {
           if      (dutgrp == 0 && (dut%4 == 3 || dut%4 == 0 )) continue;
           else if (dutgrp == 1 && (dut%4 == 1 || dut%4 == 2 )) continue;
       }
       else if(pincount == BITCNT8) {
           if      (dutgrp == 0 && (dut > 16 )) continue;
           else if (dutgrp == 1 && (dut < 17 )) continue;
       }
       UTL_SetBbmAccessDut         (bbmaccessh, dut);
       UTL_ReadBbm(bbmaccessh, bbm[dut-1], sizeof(bbm[dut-1]));

       if(dut <= 4) {
          for (i=0; i<10; i++) {
          	printf("[DEBUG] <DUT%2d> ( %6d ):0x%02X\n", dut, i, bbm[dut-1][i]);
          }
       }
    }
    UTL_DeleteCursor    (dutc);
    UTL_DeleteHandle    (bbmaccessh);
}

void bbm_read_count(RadioButton dutgrp)
{
    BbmAccessHandle	bbmaccessh;
    RadioButton	status;
    DutCursor	dutc;
    int		dut;
//  int		bbc[DUTMAX] = {0};
    
    
    bbmaccessh = UTL_GetBbmAccessHandle();
    UTL_SetBbmAccessBitMode     (bbmaccessh, UT_FCM_BITMODE_BLOCK);
    UTL_SetBbmAccessBitBlock    (bbmaccessh, 1); // n
//  UTL_SetBbmAccessBitMode     (bbmaccessh, UT_FCM_BITMODE_NORMAL); //R031111 unnecessary
    UTL_SetBbmAccessAllBit      (bbmaccessh, UT_OFF);
    UTL_ClearBbmAccessBit       (bbmaccessh);                       //n
    UTL_AddBbmAccessBit         (bbmaccessh, 0);

    UTL_SetBbmAccessCounterMode (bbmaccessh, UT_BBM_COUNTERMODE_REALTIME_SELECTEDBIT);
#if 0
    UTL_SetBbmAccessAllBit      (bbmaccessh, UT_ON);        //k
    UTL_SetBbmAccessStartAddr   (bbmaccessh, 0);            //k
    UTL_SetBbmAccessStopAddr    (bbmaccessh, BBM_SIZE-1);   //k
    UTL_SetBbmAccessCounterMode (bbmaccessh, UT_BBM_COUNTERMODE_BYCOUNT_SELECTEDBIT);
    UTL_SetBbmAccessAllDut      (bbmaccessh, UT_ON);
    UTL_CntBbmFailAddr          (bbmaccessh);
#endif
    UTL_SetBbmAccessAllDut      (bbmaccessh, UT_OFF);
    
    dutc = UTL_GetDutCursor(UT_SDUT);
    while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
        if(pincount == 9) {
           if      (dutgrp == 0 && (dut%4 == 3 || dut%4 == 0 )) continue;
           else if (dutgrp == 1 && (dut%4 == 1 || dut%4 == 2 )) continue;
        }
        else if(pincount == BITCNT8) {
            if      (dutgrp == 0 && (dut > 16 )) continue;
            else if (dutgrp == 1 && (dut < 17 )) continue;
        }
    	UTL_SetBbmAccessDut         (bbmaccessh, dut);
    
    	bbc[dut-1] = UTL_ReadBadBlockCounter(bbmaccessh, &status);
    	printf("  --- DUT-%2d ---\n", dut);
        switch (status) {
           case UT_BBM_LIMITOVER : puts("BBM LIMITOVER\n"); break;
           case UT_BBM_OVERFLOW  : puts("BBM OVERFLOW\n");  break;
           case UT_BBM_COMPLETE  :/* puts("BBM COMPLETE\n");*/  break;
           default: puts("UNEXPECTED STATUS UTL_ReadBadBlockCounter"); UTL_Stop();
        
        }
    	printf("BBC : %6d\n\n", bbc[dut-1]);
    }
    UTL_DeleteCursor    (dutc);
    UTL_DeleteHandle    (bbmaccessh);
}

void bbm_read()
{
	BbmAccessHandle	bbmaccessh;
	DutCursor	dutc;
	int		dut;

//	fprintf( stdout, " ********************************************\n");
//	fprintf( stdout, " ***  %s()\n", __FUNCTION__);
//	fprintf( stdout, " ********************************************\n"); fflush(stdout);

	bbmaccessh = UTL_GetBbmAccessHandle();

	dutc = UTL_GetDutCursor(UT_SDUT);
	while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
		UTL_SetBbmAccessBitMode     (bbmaccessh, UT_FCM_BITMODE_BLOCK);
		UTL_SetBbmAccessStartAddr   (bbmaccessh, 0);
		UTL_SetBbmAccessStopAddr    (bbmaccessh, BBM_SIZE-1);
		UTL_SetBbmAccessAllBit      (bbmaccessh, UT_ON);
		UTL_SetBbmAccessAllDut      (bbmaccessh, UT_OFF);
		UTL_SetBbmAccessDut         (bbmaccessh, dut);
		UTL_SetBbmAccessCounterMode (bbmaccessh, UT_BBM_COUNTERMODE_REALTIME_SELECTEDBIT);
//
		USlider		rbuf[BBM_SIZE];
		RadioButton	 status;
		int		i;
		fprintf( stdout, " BBC=%03d\n", UTL_ReadBadBlockCounter(bbmaccessh, &status));fflush(stdout);
		for (i=0; i<BBM_SIZE; i++) { rbuf[i]=0; }
		UTL_ReadBbm(bbmaccessh, rbuf, BBM_SIZE*sizeof(int));
		for (i=0; i<BBM_SIZE; i++) {
			printf(" ( %02d ):0x%02X\n", i, rbuf[i]);
		}
		fprintf( stdout, "\n"); fflush(stdout);
//
	}
	UTL_DeleteCursor    (dutc);
	UTL_DeleteHandle    (bbmaccessh);
}

void bbm_clear()
{
	BbmAccessHandle	bbmaccessh;
	bbmaccessh = UTL_GetBbmAccessHandle();

//	UTL_SetBbmAccessAllDut          (bbmaccessh, UT_ON); //R031111 unnecessary
	UTL_SetBbmAccessPresetAllMemory (bbmaccessh, UT_ON);
	UTL_PresetBbm                   (bbmaccessh, 0);
	UTL_DeleteHandle                (bbmaccessh);
}


void bbm_set_condition_cpmask(TEST_bbmarg bbmarg, RadioButton actmode)
{
    printf("[DEBUG] %s\n", __func__);
    BbmConfigHandle	bbmconfigh;
    int	i;
    bbm_FailSelPin_("IOPIN", bbmarg.captdat);
    bbmconfigh = UTL_GetBbmConfigHandle();
//  RadioButton bbmcmd;
//  UTL_UpdateBbmConfig                     (bbmconfigh);
//  UTL_GetBbmConfigMode                    (bbmconfigh, &bbmcmd);
//  if (bbmcmd == UT_BBM_DATACAPTURE) UTL_SetBbmConfigMode(bbmconfigh, UT_BBM_DATAGENERATE);
    for (i=0; i<BBM_YBIT; i++) UTL_SetBbmConfigAddrAssign      (bbmconfigh, i, UT_SIG_Y(i));
    for (i=0; i<BBM_XBIT; i++) UTL_SetBbmConfigAddrAssign      (bbmconfigh, i+BBM_YBIT, UT_SIG_X(i));
    UTL_SetBbmConfigMode                    (bbmconfigh, bbmarg.mode);
    UTL_SetBbmConfigAction                  (bbmconfigh, actmode);
    UTL_SetBbmConfigDataGenerationMode      (bbmconfigh, UT_BBM_MASK_SELECTEDBIT);
    UTL_SetBbmConfigWriteEnableAllDut       (bbmconfigh, UT_ON);
    UTL_AddBbmConfigMaskBit                 (bbmconfigh,0);
    UTL_SendBbmConfig                       (bbmconfigh);
    UTL_DeleteHandle                        (bbmconfigh);
}

void bbm_set_condition_drmask(TEST_bbmarg bbmarg, char *pins)
{
    BbmConfigHandle	bbmconfigh;
    UT_PIN	pin;
    int		i;
    
    bbm_FailSelPin_("IOPIN", bbmarg.captdat);

    bbmconfigh = UTL_GetBbmConfigHandle();
    
    for (i=0; i<BBM_YBIT; i++) UTL_SetBbmConfigAddrAssign      (bbmconfigh, i, UT_SIG_Y(i));
    for (i=0; i<BBM_XBIT; i++) UTL_SetBbmConfigAddrAssign      (bbmconfigh, i+BBM_YBIT, UT_SIG_X(i));
    UTL_SetBbmConfigMode                    (bbmconfigh, bbmarg.mode);
    UTL_SetBbmConfigAction                  (bbmconfigh, UT_BBM_CPDRINH);
//  UTL_SetBbmConfigAction                  (bbmconfigh, UT_BBM_MASKINH);
    UTL_SetBbmConfigStoreMode               (bbmconfigh, UT_BBM_SELECTEDDATA);     //DEFAULT
    UTL_SetBbmConfigDataGenerationMode      (bbmconfigh, UT_BBM_MASK_SELECTEDBIT);
    UTL_SetBbmConfigWriteEnableAllDut       (bbmconfigh, UT_ON);
    UTL_AddBbmConfigCaptureDataByTargetBank (bbmconfigh, 0, 1, 0, bbmarg.captdat);
    UTL_SetBbmConfigCounterNoClear          (bbmconfigh, UT_BBM_COUNTER_BBC, UT_OFF);
    UTL_AddBbmConfigMaskBit                 (bbmconfigh,0);  //8102 works without this line

    PinCursor pcr=UTL_GetPinCursor(pins);
    while((pin=UTL_NextPin(pcr))!=UT_NOMORE) UTL_AddBbmConfigDrInhPin	(bbmconfigh, pin , UT_PIN_HIGH);
    UTL_DeleteCursor                        (pcr);
    
    UTL_SendBbmConfig                       (bbmconfigh);
    UTL_DeleteHandle                        (bbmconfigh);
}

void bbm_disable()
{
	BbmConfigHandle	bbmconfigh;

//	fprintf( stdout, " ********************************************\n");
//	fprintf( stdout, " ***  %s()\n", __FUNCTION__);
//	fprintf( stdout, " ********************************************\n"); fflush(stdout);

	bbmconfigh = UTL_GetBbmConfigHandle();

	UTL_UpdateBbmConfig    (bbmconfigh);
//	UTL_AddBbmConfigAction (bbmconfigh, 1, UT_BBM_DISABLE);
	UTL_SetBbmConfigMode   (bbmconfigh, UT_BBM_DISABLE);
	UTL_SendBbmConfig      (bbmconfigh);
	UTL_DeleteHandle       (bbmconfigh);
}

/**
* @brief reads out the test result of a specified test name and disply Pass/Fail.
* @param (tname) test name
*/

void dut_test_result(char tname[]){

    RadioButton dut_test_res[DUTMAX]={0,};
    UT_DUT dutc;
    DutCursor dutcur;

    dutcur = UTL_GetDutCursor(UT_CDUT);
    while((dutc = UTL_NextDut(dutcur))!=UT_NOMORE){
        dut_test_res[dutc-1] = UTL_ReadTestResult(dutc, tname, UT_RES_ALL); 
        if(dut_test_res[dutc-1]==0)
            printf("DUT[%d] Do not Judgment\n", dutc);  //UT_RES_NOT_TESTED=0
        else if(dut_test_res[dutc-1]==2)
            printf("DUT[%d] is PASS\n", dutc);          //UT_RES_PASSED=2
        else if(dut_test_res[dutc-1]==3)
            printf("DUT[%d] is FAILED\n", dutc);        //UT_READ_FAILED=3
    }
    UTL_DeleteCursor(dutcur);
}

/**
* @brief Reads out the final test result and set the category..
*
*/

void dut_final_result(void){
    RadioButton dut_final_res[8]={0,};
    UT_DUT dutc;
    DutCursor dutcur;

    dutcur = UTL_GetDutCursor(UT_CDUT);
    while((dutc=UTL_NextDut(dutcur))!=UT_NOMORE){
        dut_final_res[dutc-1] = UTL_ReadFinalResult(dutc,UT_RES_ALL);
        if(dut_final_res[dutc-1]==2) UTL_SetCategory(dutc,1);
    }
    UTL_DeleteCursor(dutcur);
}

/**
* @brief reject the UT_FDUT From the Measurement Target.
*
*/

void dut_rejection(void){
    UT_DUT dutc;
    DutCursor dutcur;

    RejectionHandle rejh = UTL_GetRejectionHandle();

    dutcur = UTL_GetDutCursor(UT_FDUT);
    while((dutc=UTL_NextDut(dutcur))!=UT_NOMORE){
        UTL_AddRejectionDut(rejh, dutc);
    }
    UTL_DeleteCursor(dutcur);

    UTL_SetRejectionIgnoreWet(rejh, UT_OFF);  //UT_OFF: Follows the set mode
    UTL_SendRejection(rejh);
    UTL_DeleteHandle(rejh);
}

void fcm_config(USlider n1, USlider n2, char *pinlist)
{
    printf("[DEBUG]%s\n",__func__);
    static FcmConfigHandle fcmch = -1;
    int i;

    if (fcmch < 0) {
       fcmch = UTL_GetFcmConfigHandle();
       UTL_SetFcmConfigPinAssignTarget(fcmch, UT_FCM);
       UTL_AddFcmConfigAction         (fcmch, 1, UT_FCM_TOTALFAIL);
       UTL_SetFcmConfigPinAssignTarget(fcmch, UT_FCM_FLEX_PINASSIGN);
    }
    UTL_SetFcmConfigRate (fcmch, UT_FCM_LS);
    UTL_SetFcmConfigDutBitSize (fcmch, n1);
    UTL_SetFcmConfigBitSize    (fcmch, n2);
    for (i=0; i<BBM_YBIT; i++)
    	UTL_SetFcmConfigAddrAssign      (fcmch, i, UT_SIG_Y(i));
    for (i=0; i<BBM_XBIT; i++)
    	UTL_SetFcmConfigAddrAssign      (fcmch, i+BBM_YBIT, UT_SIG_X(i));

    PinCursor pinc = UTL_GetPinCursor(pinlist);
    UT_PIN pin;
    while((pin=UTL_NextPin(pinc))!=UT_NOMORE)
       UTL_AddFcmConfigPinAssign(fcmch, 0, pin);  //n2 = 1

    UTL_DeleteCursor(pinc);
//  UTL_SetFcmConfigTransferSize(fcmch, 0);
    UTL_SetFcmConfigRealTimeCountEnable(fcmch, UT_ON);
    UTL_SendFcmConfig(fcmch);
}

#define BST_YBIT 3   //8 Burst
void fcm_config_ddr(USlider n1, USlider n2, char *pinlist)
{
    printf("[DEBUG]%s\n",__func__);
    static FcmConfigHandle fcmch = -1;
    int i;

    if (fcmch < 0) {
       fcmch = UTL_GetFcmConfigHandle();
       UTL_SetFcmConfigPinAssignTarget(fcmch, UT_FCM);
       UTL_AddFcmConfigAction         (fcmch, 1, UT_FCM_TOTALFAIL);
       UTL_SetFcmConfigPinAssignTarget(fcmch, UT_FCM_FLEX_PINASSIGN);
       UTL_SetFcmConfigDdrMode        (fcmch, UT_ON);
    }
    UTL_SetFcmConfigRate (fcmch, UT_FCM_HS);
    UTL_SetFcmConfigDutBitSize (fcmch, n1);
    UTL_SetFcmConfigBitSize    (fcmch, n2);
    for (i=0; i<BST_YBIT; i++)
    	UTL_SetFcmConfigAddrAssign      (fcmch, i, UT_SIG_Y(i));
    for (i=0; i<BBM_XBIT-BST_YBIT; i++)
    	UTL_SetFcmConfigAddrAssign      (fcmch, i+BST_YBIT, UT_SIG_X(i));

    PinCursor pinc = UTL_GetPinCursor(pinlist);
    UT_PIN pin;
    while((pin=UTL_NextPin(pinc))!=UT_NOMORE)
       UTL_AddFcmConfigPinAssign(fcmch, 0, pin);  //n2 = 1

    UTL_DeleteCursor(pinc);
//  UTL_SetFcmConfigTransferSize(fcmch, 0);
    UTL_SetFcmConfigRealTimeCountEnable(fcmch, UT_ON);
    UTL_SetFcmConfigBurstCaptureLength (fcmch, 8);
    UTL_SendFcmConfig(fcmch);
}

void fcm_clear()
{
    printf("[DEBUG]%s\n",__func__);
    static FcmAccessHandle fcmah = -1;

    if (fcmah < 0) {
       fcmah = UTL_GetFcmAccessHandle();
       UTL_SetFcmAccessAllDut          (fcmah, UT_ON);
       UTL_SetFcmAccessAllBit          (fcmah, UT_ON);
       UTL_SetFcmAccessPresetAllMemory (fcmah, UT_ON);
    }
    UTL_PresetFcm(fcmah, 0);
}

/*
 *  fcm_read
 *   FCM can capture fail for DUT1n,2n or DUT3n,4n separately,
 *   when t5835_32dut_bit9.soc is used as socket program.
 *   When t5835_32dut_bit8 is used, FCM can capture fail of
 *   DUT1-16 or DUT17-32 separately at once.
 */
void fcm_read(RadioButton dutgrp, int disp_data)
{
    printf("[DEBUG]%s\n",__func__);
    FcmAccessHandle fcmah = -1;
    int i;
    UT_DUT dut;

    fcmah = UTL_GetFcmAccessHandle();
    UTL_SetFcmAccessAutoAddrAssignMode(fcmah, UT_ON);
    UTL_SetFcmAccessPfcMode           (fcmah, UT_FCM_PFCMODE_REALTIME);
    UTL_SetFcmAccessXAddr             (fcmah, 0x000, pow(2,18)-1);
    UTL_SetFcmAccessYAddr             (fcmah, 0x000, 0x000);
    UTL_SetFcmAccessApLink            (fcmah, UT_FCM_APLINK_XYZ);

    UTL_SetFcmAccessAllDut(fcmah, UT_OFF);

    DutCursor dutc = UTL_GetDutCursor(UT_SDUT);
    if( pincount == 9) {
       while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
          if      (dutgrp == 0 && (dut%4 == 3 || dut%4 == 0 )) continue;
          else if (dutgrp == 1 && (dut%4 == 1 || dut%4 == 2 )) continue;
          UTL_SetFcmAccessDut(fcmah, dut);
          bbc[dut-1] = UTL_GetFcmParallelFailCount(fcmah);
          printf("  --- DUT-%2d : %10d ---\n", dut, bbc[dut-1]);
       }
       UTL_DeleteCursor    (dutc);

       dutc = UTL_GetDutCursor(UT_SDUT);
       while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
          if      (dutgrp == 0 && (dut%4 == 3 || dut%4 == 0 )) continue;
          else if (dutgrp == 1 && (dut%4 == 1 || dut%4 == 2 )) continue;
          UTL_SetFcmAccessDut(fcmah, dut);
          UTL_ReadFcm        (fcmah, bb_addr[dut-1], sizeof bb_addr[dut-1]);
       }
       UTL_DeleteCursor    (dutc);
    }
    else if( pincount == BITCNT8) {
       while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
          if      (dutgrp == 0 && (dut > 16 )) continue;
          else if (dutgrp == 1 && (dut < 17 )) continue;
          UTL_SetFcmAccessDut(fcmah, dut);
          bbc[dut-1] = UTL_GetFcmParallelFailCount(fcmah);
          printf("  --- DUT-%2d : %10d ---\n", dut, bbc[dut-1]);
       }
       UTL_DeleteCursor    (dutc);

       dutc = UTL_GetDutCursor(UT_SDUT);
       while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
          if      (dutgrp == 0 && (dut > 16 )) continue;
          else if (dutgrp == 1 && (dut < 17 )) continue;
          UTL_SetFcmAccessDut(fcmah, dut);
          UTL_ReadFcm        (fcmah, bb_addr[dut-1], sizeof bb_addr[dut-1]);
       }
       UTL_DeleteCursor    (dutc);
    }
//tmp  for (i=0; i<BBM_XMAX; i++) if (bb_addr[dut-1][i] == disp_data) printf ("FCM [%6d] #%08x\n", i, bb_addr[i]);
}


void init(RadioButton ilmd)
{
    ilmode(ilmd);
    pin_list();
    power_seq();
    pin_condition();
    level_setting(1, 1.00 V, 0.00 V);    // (channel, Vi high, Vi low)
}

void init_ddr_bbm(RadioButton ilmd)
{
    ilmode(ilmd);
    pin_list();
    power_seq();
    pin_condition_ddr(UT_WAV_FIXH);
    level_setting(1, 1.00 V, 0.00 V);    // (channel, Vi high, Vi low)
}

void init_ddr_ecc(RadioButton ilmd)
{
    ilmode(ilmd);
    pin_list();
    power_seq();
    pin_condition_ddr(UT_WAV_FIXL);
    level_setting_ddr(1, 1.00 V, 0.00 V);    // (channel, Vi high, Vi low)
}

/*
 *  JudgeAllPF: 
 *    All block should be the same result, that is, all blocks are good and vice versa.
 *    The bbc has fail count.  The bb_addr has fail address of BBM or FCM
 */
void JudgeAllPF(TEST_bbmarg bbmarg)
{
   int dut, i;
   int efcnt;   //expected fail count
   int ng = 0;
   char *testname = UTL_ReadTestName();
   
   if( pincount == 9) {
      if (bbmarg.disp_data) efcnt = 0;
      else                  efcnt = pow(2,18);
   }
   else {
      efcnt = pow(2,18); //NON-MASKED
   }

   DutCursor dutc = UTL_GetDutCursor(UT_SDUT);
   while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
       if( pincount == 9) {
          if      (bbmarg.dutgrp == 0 && (dut%4 == 3 || dut%4 == 0 )) {
              UTL_ResetTestResult(dut, testname, UT_RES_ALL);
              continue;
          }
          else if (bbmarg.dutgrp == 1 && (dut%4 == 1 || dut%4 == 2 )) {
              UTL_ResetTestResult(dut, testname, UT_RES_ALL);
              continue;
          }
       }
       else if( pincount == BITCNT8) {
          if     ((bbmarg.dutgrp == 0 && (dut > 16 )) || (bbmarg.dutgrp == 1 && (dut < 17 ))) {
              UTL_ResetTestResult(dut, testname, UT_RES_ALL);
              continue;
          }
       }

       ng = 0;
       if(bbc[dut-1] != efcnt) {
          printf("DUT[%2d] BBC(%9d) EXP(%9d)\n", dut, bbc[dut-1], efcnt);
          ng=1;
       }
       for (i=0; i<BBM_SIZE; i++) {
          if(bb_addr[dut-1][i] == bbmarg.disp_data) {
               printf("BBM(%9d)=#%08x is unexpected\n", i, bb_addr[dut-1][i]);
               break;
               ng=1;
          }
       }
       if (ng == 0) UTL_ResetTestResult(dut, testname, UT_RES_ALL);
       else         UTL_SetTestResult  (dut, testname, UT_RES_ALL);
   }     
   UTL_DeleteCursor(dutc);
}

void JudgeDrMask(TEST_bbmarg bbmarg)
{
   UT_DUT dut;
   int i, data;
   int efcnt;   //expected fail count
   int ng = 0;
   char *testname = UTL_ReadTestName();
   
   DutCursor dutc = UTL_GetDutCursor(UT_SDUT);
   while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
       if (bbmarg.dutgrp == 0 && (dut > 16 )) {
           UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           continue;
       }
       else if (bbmarg.dutgrp == 1 && (dut < 17 )) {
           UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           continue;
       }
       if(!bbmarg.disp_data) { //pat_bbm.mpa 0x020 <1>all fail
          if ((dut%4 == 1) || (dut%4 == 2)) { efcnt = 0;         data = 0; }
          else                              { efcnt = pow(2,18); data = 1; }
       }
       else {                  //pat_bbm.mpa 0x040
          if ((dut%4 == 1) || (dut%4 == 2)) { efcnt = pow(2,18); data = 1; }
          else                              { efcnt = 0;         data = 0; }
       }

       ng = 0;
       if(bbc[dut-1] != efcnt) {
          printf("DUT[%2d] BBC(%9d) EXP(%9d)\n", dut, bbc[dut-1], efcnt);
          ng=1;
       }
       for (i=0; i<BBM_SIZE; i++) {
          if(bb_addr[dut-1][i] != data) {
               printf("DUT(%2d) BBM(%9d)=#%08x is unexpected\n", dut, i, bb_addr[dut-1][i]);
               ng=1;
               break;
          }
       }
       printf("[DEBUG]%s  DUT%d  ng=%d\n",__func__,dut,ng);
       if (ng == 0) UTL_ResetTestResult(dut, testname, UT_RES_ALL);
       else         UTL_SetTestResult  (dut, testname, UT_RES_ALL);
   }     
   UTL_DeleteCursor(dutc);
}

void JudgeDrMask2(TEST_bbmarg bbmarg)
{
   UT_DUT dut;
   int i, data;
   int efcnt;   //expected fail count
   int ng = 0;
   char *testname = UTL_ReadTestName();
   
   DutCursor dutc = UTL_GetDutCursor(UT_SDUT);
   while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
       if (bbmarg.dutgrp == 0 && (dut > 16 )) {
           UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           continue;
       }
       else if (bbmarg.dutgrp == 1 && (dut < 17 )) {
           UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           continue;
       }
       if ((dut%4 == 3) || (dut%4 == 0)) { efcnt = 0;         data = 0; }
       else                              { efcnt = pow(2,18); data = 1; }

       ng = 0;
       if(bbc[dut-1] != efcnt) {
          printf("DUT[%2d] BBC(%9d) EXP(%9d)\n", dut, bbc[dut-1], efcnt);
          ng=1;
       }
       for (i=0; i<BBM_SIZE; i++) {
          if(bb_addr[dut-1][i] != data) {
               printf("DUT(%2d) BBM(%9d)=#%08x is unexpected\n", dut, i, bb_addr[dut-1][i]);
               ng=1;
               break;
          }
       }
       printf("[DEBUG]%s  DUT%d  ng=%d\n",__func__,dut,ng);
       if (ng == 0) UTL_ResetTestResult(dut, testname, UT_RES_ALL);
       else         UTL_SetTestResult  (dut, testname, UT_RES_ALL);
   }     
   UTL_DeleteCursor(dutc);
}
void setexp(int *odd, int *even)
{
     if(*odd) { *odd = 0;  *even = 1; }
     else     { *odd = 1;  *even = 0; }
}
/*
 *  JudgeAllPF: All block should be the same result, that is, all blocks are good and vice versa.
 */
void JudgeHalfPass(TEST_bbmarg bbmarg)
{
   int dut, i;
   int efcnt = 0;      //expected fail count
   int ng = 0;
   int odd, even;      //expected value for odd/even blocks 
   char *testname = UTL_ReadTestName();

   if (pincount == 9) {
      if (bbmarg.pc == 0x40) {
          efcnt = pow(2,17);
          odd = 0;
          even= 1;
      }
      else if (bbmarg.pc == 0x20) {
          efcnt = pow(2,17);
          odd = 1;
          even= 0;
      }
      else if (bbmarg.pc == 0x60) {
          efcnt = pow(2,17);
          odd = 0;
          even= 1;
      }
   }
   else { /* with a dr-cp DSA */
      if (bbmarg.pc == 0x40) { /* BBM */
         efcnt = pow(2,17);
         even = 1; 
         odd = 0;
      }
      else { /* FCM */
         efcnt = pow(2,17);
         even = 0; 
         odd = 1;
      }
   }

   DutCursor dutc = UTL_GetDutCursor(UT_SDUT);
   if (pincount != BITCNT8) {
       while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
           if      (bbmarg.dutgrp == 0 && (dut%4 == 3 || dut%4 == 0 )) {
               UTL_ResetTestResult(dut, testname, UT_RES_ALL);
               continue;
           }
           else if (bbmarg.dutgrp == 1 && (dut%4 == 1 || dut%4 == 2 )) {
               UTL_ResetTestResult(dut, testname, UT_RES_ALL);
               continue;
           }
           ng = 0;
           if(bbc[dut-1] != efcnt) {
              printf("DUT[%2d] BBCount(%9d) EXP(%9d)\n", dut, bbc[dut-1], efcnt);
              ng=1;
           }
           for (i=0; i<BBM_SIZE/2; i++) {
              if (bb_addr[dut-1][i*2]   != even) {
                 printf("BBM(%9d)=#%08x is unexpected\n", i, bb_addr[dut-1][i*2]);
                 ng=1;
                 break;
              }
              if (bb_addr[dut-1][i*2+1] != odd)  {
                 printf("BBM(%9d)=#%08x is unexpected\n", i, bb_addr[dut-1][i*2+1]);
                 ng=1;
                 break;
              }
           }
           if (ng == 0) UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           else         UTL_SetTestResult  (dut, testname, UT_RES_ALL);
       }     
   }
   else {  /* with a dr-cp DSA */
       while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
           if      (bbmarg.dutgrp == 0 && (dut > 16 )) {
               UTL_ResetTestResult(dut, testname, UT_RES_ALL);
               continue;
           }
           else if (bbmarg.dutgrp == 1 && (dut < 17 )) {
               UTL_ResetTestResult(dut, testname, UT_RES_ALL);
               continue;
           }
           ng = 0;
           if (dut%4 == 1 || dut%4 == 3) setexp(&odd, &even);
           printf("[DEBUG]%s  dut=%d  odd=%d even=%d\n", __func__, dut, odd, even);
           if(bbc[dut-1] != efcnt) {
              printf("DUT[%2d] BBCount(%9d) EXP(%9d)\n", dut, bbc[dut-1], efcnt);
              ng=1;
           }
           for (i=0; i<BBM_SIZE/2; i++) {
              if (bb_addr[dut-1][i*2]   != even) {
                 printf("BBM(%9d)=#%08x is unexpected\n", i, bb_addr[dut-1][i*2]);
                 ng=1;
              }
              if (bb_addr[dut-1][i*2+1] != odd)  {
                 printf("BBM(%9d)=#%08x is unexpected\n", i, bb_addr[dut-1][i*2+1]);
                 ng=1;
              }
           }
           if (ng == 0) UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           else         UTL_SetTestResult  (dut, testname, UT_RES_ALL);
       }
   }
   UTL_DeleteCursor(dutc);
}

void JudgeOddDutPass(TEST_bbmarg bbmarg)
{
   int dut, i;
   int efcnt = 0;      //expected fail count
   int ng = 0;
   int odd, even;      //expected value for odd/even blocks 
   char *testname = UTL_ReadTestName();

   if (bbmarg.pc == 0x60) {
       efcnt = pow(2,17);
       odd = 1;
       even= 0;
   }
   DutCursor dutc = UTL_GetDutCursor(UT_SDUT);
   while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
       if  (bbmarg.dutgrp == 0 && (dut%4 == 3 || dut%4 == 0 )) {
           UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           continue;
       }
       else if (bbmarg.dutgrp == 1 && (dut%4 == 1 || dut%4 == 2 )) {
           UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           continue;
       }

       ng = 0;
       if(dut%2) {
          if(bbc[dut-1] != 0) {
             printf("DUT[%2d] BBCount(%9d) EXP(%9d)\n", dut, bbc[dut-1], 0);
             ng=1;
          }
          for (i=0; i<BBM_SIZE; i++) {
             if (bb_addr[dut-1][i] != 0) {
                printf("BBM(%9d)=#%08x is unexpected\n", i, bb_addr[dut-1][i]);
                ng=1;
             }
          }
       }
       else {
          if(bbc[dut-1] != efcnt) {
             printf("DUT[%2d] BBCount(%9d) EXP(%9d)\n", dut, bbc[dut-1], efcnt);
             ng=1;
          }
          for (i=0; i<BBM_SIZE/2; i++) {
             if (bb_addr[dut-1][i*2]   != even) {
                printf("BBM(%9d)=#%08x is unexpected\n", i, bb_addr[dut-1][i*2]);
                ng=1;
             }
             if (bb_addr[dut-1][i*2+1] != odd)  {
                printf("BBM(%9d)=#%08x is unexpected\n", i, bb_addr[dut-1][i*2+1]);
                ng=1;
             }
          }
       }
       if (ng == 0) UTL_ResetTestResult(dut, testname, UT_RES_ALL);
       else         UTL_SetTestResult  (dut, testname, UT_RES_ALL);
   }     
   UTL_DeleteCursor(dutc);
}

#define BBMAXCNT 20

/*
 * ecc_SSs_N[]
 *   SS: # of sectors 
 *   N: ECC(total) or ECC(or)
 */
int ecc_01s_0[] = {   100,  1285,  9987, 88776,101012,156789,191111,201377,212102};
int ecc_01s_2[] = {    58,   254,  4321,  8098, 32432,128876,192543,202109,228765,230432,230434};
int ecc_02s_0[] = {   635,  2593, 67143, 67144, 96143,109524,127324,201974,223561,223579,224386,237773,237816};
int ecc_02s_2[] = {   631,  2596, 67146, 67147, 96149,127330,201980,223567,223580,224365,237758,237801};
int ecc_04s_0[] = {     1, 98306,128310,134453};
int ecc_04s_2[] = {   749,   751,  8378, 12399, 36522, 36523, 88888,111111,222222,222223};
int ecc_08s_0[] = { 10987, 21098, 43210, 98766,123457,234568,260003,262142};
int ecc_08s_2[] = { 10987, 10988, 10990, 37898, 37899, 37900,260003,260004,260006};
int ecc_16s_0[] = {    82,  1127,  5227, 13419, 29789, 62541,128063,189505,242227,242229};
int ecc_16s_2[] = {    98,  1143,  5243, 13435, 29821, 62589,128095,189553,242291,242293};
int ecc_16s_0_9[] = {    82, 1127, 5227, 13419, 29789, 62541, 128063, 189505, 242227, 242229};
int ecc_16s_2_9[] = {    90, 1135, 5235, 13427, 29813, 62581, 128087, 189545, 242283, 242285 };
int ecc_16s_8wt[] = { 113, 1213, 10101, 49916, 97854, 175790};
int ecc_16s_8wo[] = { 789, 4068, 13270, 53918,113868, 191997, 202075};
int ecc_noclear[]  = {   1,    2,     3,     4,     5,      6,      7,     8};

void JudgeEcc(TEST_bbmarg bbmarg)
{
   int i, j, ng;
   int efcnt = 0;      //expected fail count
   int *bb;            //bad block address
   UT_DUT dut;
   char *testname = UTL_ReadTestName();

   if (!strcmp(bbmarg.mpat,"pat_ecc_1sec.mpa")) {
      if (bbmarg.pc == 0)   { bb = ecc_01s_0; efcnt = sizeof(ecc_01s_0)/sizeof(int); }
      else                  { bb = ecc_01s_2; efcnt = sizeof(ecc_01s_2)/sizeof(int); }
   } 
   else if (!strcmp(bbmarg.mpat,"pat_ecc_2sec.mpa")) {
      if (bbmarg.pc == 0)   { bb = ecc_02s_0; efcnt = sizeof(ecc_02s_0)/sizeof(int); }
      else                  { bb = ecc_02s_2; efcnt = sizeof(ecc_02s_2)/sizeof(int); }
   } 
   else if (!strcmp(bbmarg.mpat,"pat_ecc_4sec.mpa")) {
      if (bbmarg.pc == 0)   { bb = ecc_04s_0; efcnt = sizeof(ecc_04s_0)/sizeof(int); }
      else                  { bb = ecc_04s_2; efcnt = sizeof(ecc_04s_2)/sizeof(int); }
   } 
   else if (!strcmp(bbmarg.mpat,"pat_ecc_8sec.mpa")) {
      if (bbmarg.pc == 0)   { bb = ecc_08s_0; efcnt = sizeof(ecc_08s_0)/sizeof(int); }
      else                  { bb = ecc_08s_2; efcnt = sizeof(ecc_08s_2)/sizeof(int); }
   } 
   else if (!strcmp(bbmarg.mpat,"pat_ecc_16sec.mpa")) {
      if (bbmarg.pc == 0)   { bb = ecc_16s_0; efcnt = sizeof(ecc_16s_0)/sizeof(int); }
      else                  { bb = ecc_16s_2; efcnt = sizeof(ecc_16s_2)/sizeof(int); }
   } 
   else if (!strcmp(bbmarg.mpat,"pat_ecc_16sec_9io.mpa")) {
      if (bbmarg.pc == 0)   { bb = ecc_16s_0_9; efcnt = sizeof(ecc_16s_0_9)/sizeof(int); }
      else                  { bb = ecc_16s_2_9; efcnt = sizeof(ecc_16s_2_9)/sizeof(int); }
   } 
   else if (!strcmp(bbmarg.mpat,"pat_ecc_8w.mpa")) {
      if (bbmarg.pc == 0)   { bb = ecc_16s_8wt; efcnt = sizeof(ecc_16s_8wt)/sizeof(int); }
      else                  { bb = ecc_16s_8wo; efcnt = sizeof(ecc_16s_8wo)/sizeof(int); }
   } 
   else if (!strcmp(bbmarg.mpat,"pat_ecc_nc.mpa")) {
      if (bbmarg.pc == 0)   {  bb = ecc_noclear; efcnt = sizeof(ecc_noclear)/sizeof(int); }
      else                  {  bb = NULL; efcnt = 0; }
   } 
// printf("[DEBUG]pattern =%s\n", bbmarg.mpat );
// printf("[DEBUG]efcnt = %d \n", efcnt );
   DutCursor dutc = UTL_GetDutCursor(UT_SDUT);
   while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
       if  (bbmarg.dutgrp == 0 && (dut%4 == 3 || dut%4 == 0 )) {
           UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           continue;
       }
       else if (bbmarg.dutgrp == 1 && (dut%4 == 1 || dut%4 == 2 )) {
           UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           continue;
       }
       ng = 0;
       if(bbc[dut-1] != efcnt) {
          printf("DUT[%2d] BBC(%9d) EXP(%9d)\n", dut, bbc[dut-1], efcnt);
          ng = 1;
       }
       for (i=0; i<BBM_SIZE; i++) {
          if (bb_addr[dut-1][i]) {
             for(j=0; j<efcnt; j++) {
                if (i == bb[j]) {
//                 printf("[DEBUG] DUT(%2d) BBM(%9d)=#%08x is correct\n",dut, i, bb_addr[dut-1][i]);
                   break;
                }
                if (i <  bb[j]) { 
                   printf("DUT(%2d) BBM(%9d)=#%08x is unexpected\n", dut, i, bb_addr[dut-1][i]);
                   ng = 1;
                   break;
                }
             }
             if (j == efcnt) printf("DUT(%2d) BBM(%9d)=#%08x is unexpected\n", dut, i, bb_addr[dut-1][i]);
          }
       }
       if (ng == 0) UTL_ResetTestResult(dut, testname, UT_RES_ALL);
       else         UTL_SetTestResult  (dut, testname, UT_RES_ALL);
   }     
   UTL_DeleteCursor(dutc);
}

void JudgeAftrEcc(TEST_bbmarg bbmarg)  //This should be fixed
{
   int i, j, ng;
   int efcnt = 0;      //expected fail count
   int *bb;
   UT_DUT dut;
   char *testname = UTL_ReadTestName();

   if (bbmarg.captdat == UT_BBM_ECCORCOUNT(1)) {
      if      (bbmarg.sector ==  1)   bb = ecc_01s_0;
      else if (bbmarg.sector ==  2)   bb = ecc_02s_0;
      else if (bbmarg.sector ==  4)   bb = ecc_04s_0;
      else if (bbmarg.sector ==  8)   bb = ecc_08s_0;
      else /*  bbmarg.sector == 16 */ bb = ecc_16s_0;
   } 
   else /* UT_BBM_ECCTOtALCOUNT(1)*/ {
      if      (bbmarg.sector ==  1)   bb = ecc_01s_2;
      else if (bbmarg.sector ==  2)   bb = ecc_02s_2;
      else if (bbmarg.sector ==  4)   bb = ecc_04s_2;
      else if (bbmarg.sector ==  8)   bb = ecc_08s_2;
      else /*  bbmarg.sector == 16 */ bb = ecc_16s_2;
   } 
   efcnt = sizeof(bb) / sizeof(int);

   DutCursor dutc = UTL_GetDutCursor(UT_SDUT);
   while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
       if  (bbmarg.dutgrp == 0 && (dut%4 == 3 || dut%4 == 0 )) {
           UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           continue;
       }
       else if (bbmarg.dutgrp == 1 && (dut%4 == 1 || dut%4 == 2 )) {
           UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           continue;
       }
       ng = 0;
       if(bbc[dut-1] != pow(2,18)-efcnt) {
          printf("DUT[%2d] BBC(%9d) EXP(%9d)\n", dut, bbc[dut-1], efcnt);
          ng = 1;
       }
       for (i=0; i<BBM_SIZE; i++) {
          if (!bb_addr[dut-1][i]) {
             for(j=0; j<efcnt; j++) {
                if (i == bb[j]) {
//                 printf("[DEBUG] DUT(%2d) BBM(%9d)=#%08x is correct\n",dut, i, bb_addr[dut-1][i]);
                   break;
                }
                if (i <  bb[j]) {
                   printf("DUT(%2d) BBM(%9d)=#%08x is unexpected\n", dut, i, bb_addr[dut-1][i]);
                   ng = 1;
                   break;
                }
             }
             if (j == efcnt) printf("DUT(%2d) BBM(%9d)=#%08x is unexpected\n", dut, i, bb_addr[dut-1][i]);
          }
       }
       if (ng == 0) UTL_ResetTestResult(dut, testname, UT_RES_ALL);
       else         UTL_SetTestResult  (dut, testname, UT_RES_ALL);
   }     
   UTL_DeleteCursor(dutc);
}

void JudgeLmt(TEST_bbmarg bbmarg) //R031105 This routine has bug to be fixed
{
   int dut, ng, i;
   char *testname = UTL_ReadTestName();
 
   DutCursor dutc = UTL_GetDutCursor(UT_SDUT);

   while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
       if      (bbmarg.dutgrp == 0 && (dut%4 == 3 || dut%4 == 0 )) {
           UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           continue;
       }
       else if (bbmarg.dutgrp == 1 && (dut%4 == 1 || dut%4 == 2 )) {
           UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           continue;
       }

       ng = 0;
       if(bbc[dut-1] != BBLMT) printf("DUT[%2d] BBC(%9d) EXP(%3d)\n", dut, bbc[dut-1], BBLMT);
       for (i=0; i<BBLMT; i++) {
           if (!bb_addr[dut-1][i]) {
              printf("DUT[%2d] BBM(%9d)=#%08x is unexpected\n",dut, i, bb_addr[dut-1][i]);
              ng=1;
              break;
            }
       }
       for (i=BBLMT; i<BBM_SIZE; i++) {
           if (bb_addr[dut-1][i]) {
              printf("DUT[%2d] BBM(%9d)=#%08x is unexpected\n",dut, i, bb_addr[dut-1][i]);
              ng=1;
              break;
           }
       }
       if (ng == 0) UTL_ResetTestResult(dut, testname, UT_RES_ALL);
       else         UTL_SetTestResult  (dut, testname, UT_RES_ALL);
   }
   UTL_DeleteCursor(dutc);
   
}

void NoJudge(TEST_bbmarg bbmarg)
{
// char *testname = UTL_ReadTestName();
// testresult_pass4alldut(testname);
}

void burstscram(RadioButton onoff)
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


/**********************************************************************
 * bbm_test_1 
 *   [W/ pat_bbm.mpa, PC=#020]
 *    All BLKs fail.
 *   [W/ pat_bbm.mpa, PC=#040]
 *    Even BLKs fail.
 *
 **********************************************************************/
void bbm_test_1(TEST_testitem *testarg)
{
    init(BBMARG.ilmode);
    timing_setting(BBMARG.rate);
    readtname();
    
    FailCaptureSelect(BBMARG.dutgrp);
    bbm_set_condition_capture(BBMARG);
    bbm_clear();	

//  UTL_ExecCalb("cfctest1","normal");
//
    MeasFct(BBMARG.mpat, BBMARG.pc, UT_ON, UT_OFF);
    bbm_read_address(BBMARG.dutgrp, BBMARG.disp_data);
    bbm_read_count(BBMARG.dutgrp);
    bbm_disable();	

    BBMARG.post(BBMARG);
    dut_test_result(testarg->testname);
}

void bbm_test_8(TEST_testitem *testarg)
{
    timing_setting(BBMARG.rate);
    readtname();
    
//  bbm_set_condition_capture(BBMARG.mode, BBMARG.captdat);
    bbm_set_condition_capture(BBMARG);
    bbm_clear();	

//  UTL_ExecCalb("cfctest1","normal");
    MeasFct(BBMARG.mpat, BBMARG.pc, UT_OFF, UT_OFF);
	
    bbm_read_address(BBMARG.dutgrp, BBMARG.disp_data);
    bbm_read_count(BBMARG.dutgrp);
    bbm_disable();	

    BBMARG.post(BBMARG);
    dut_test_result(testarg->testname);
}

/**********************************************************************
 * bbm_test_9
 *  Make odd DUTs to output FL.
 *
 *   [W/ pat_bbm.mpa, PC=#040]
 *    Odd DUTs are Pass.
 *    Even DUTs are pass for even BLKs, fail for odd ones.
 *
 **********************************************************************/
void bbm_test_9(TEST_testitem *testarg)
{
    init(BBMARG.ilmode);
    timing_setting(BBMARG.rate);
    readtname();
    
    FailCaptureSelect(BBMARG.dutgrp);
    bbm_set_condition_capture(BBMARG);
    bbm_clear();	

//  UTL_ExecCalb("cfctest1","normal");
#if 1
    DutCursor dutc = UTL_GetDutCursor(UT_MDUT);
    UT_DUT dut;
    while((dut = UTL_NextDut(dutc)) != UT_NOMORE)
       if(dut%2) level_fix(dut, UT_PIN_FIXL, "IOPIN");
    UTL_DeleteCursor(dutc);
#endif
    MeasFct(BBMARG.mpat, BBMARG.pc, UT_OFF, UT_OFF);

#if 1
    dutc = UTL_GetDutCursor(UT_MDUT);
    while((dut = UTL_NextDut(dutc)) != UT_NOMORE)
       if(dut%2) level_fix(dut, UT_PIN_NONE, "IOPIN");
    UTL_DeleteCursor(dutc);
#endif
    bbm_read_address(BBMARG.dutgrp, BBMARG.disp_data);
    bbm_read_count(BBMARG.dutgrp);
    bbm_disable();	

    BBMARG.post(BBMARG);
    dut_test_result(testarg->testname);
}

/**********************************************************************
 * bbm_test_2
 * Check if the UTL_SetBbmConfigBbcLimitByBit works
 * # of bad blocks should equal to the specified to the above MCI,
 * using PC=#020, pat_bbm.
 *
 **********************************************************************/
void bbm_test_2(TEST_testitem *testarg)
{
    init(BBMARG.ilmode);
    timing_setting(BBMARG.rate);
    readtname();

    FailCaptureSelect(BBMARG.dutgrp);
    bbm_set_condition_capture_limit(BBMARG.mode, BBMARG.captdat);
    bbm_clear();	

//  UTL_ExecCalb("cfctest1","normal");
	
    MeasFct(BBMARG.mpat, BBMARG.pc, UT_OFF, UT_OFF);
	
    bbm_read_address(BBMARG.dutgrp, BBMARG.disp_data);
    bbm_read_count(BBMARG.dutgrp);
    BBMARG.post(BBMARG);
    dut_test_result(testarg->testname);
}

/**********************************************************************
 * bbm_test_3
 * Check if CP is inhibitted according to BBM data, by capturing
 * fails into FCM.
 *
 **********************************************************************/
void bbm_test_3(TEST_testitem *testarg)
{
    init(BBMARG.ilmode);
    timing_setting(BBMARG.rate);
    readtname();

    FailCaptureSelect(BBMARG.dutgrp);
    bbm_set_condition_capture(BBMARG);
//  bbm_read_address(BBMARG.dutgrp, BBMARG.disp_data);
    bbm_set_condition_cpmask(BBMARG, UT_BBM_CPINH);
#if 0
    bbm_clear();	//DEBUG
#endif
    fcm_config(9, 1, "IOPIN");
    fcm_clear();
    MeasFct(BBMARG.mpat, BBMARG.pc, UT_OFF, UT_ON);
//  ReadFunc();  //debug

    fcm_read(BBMARG.dutgrp,BBMARG.disp_data);
    bbm_disable();
    BBMARG.post(BBMARG);
    dut_test_result(testarg->testname);
}

void bbm_test_4(TEST_testitem *testarg)
{
    init(BBMARG.ilmode);
    timing_setting(BBMARG.rate);
    readtname();
    
    bbm_set_condition_capture(BBMARG);
    bbm_clear();	
//  UTL_ExecCalb("cfctest1","normal");

    MeasFct(BBMARG.mpat, BBMARG.pc, UT_OFF, UT_ON);

    bbm_read_address(BBMARG.dutgrp, BBMARG.disp_data);
    bbm_read_count(BBMARG.dutgrp);
#if 0
    bbm_set_condition_drmask("DRPIN");
#endif

    MeasFct(BBMARG.mpat, BBMARG.pc, UT_OFF, UT_ON);
//  UTL_SetFctStartPc    (fct, 0x40);      
//  UTL_MeasFct(fct);

//	bbm_read_address();
//	bbm_read_count();
    bbm_disable();
//  UTL_DeleteHandle(fct);
    BBMARG.post(BBMARG);
    dut_test_result(testarg->testname);
}

/**********************************************************************
 *  bbm_test_5
 *  DR Inhbit (Step2: Check DRInh)
 *  This function is callded after bbm_test_7 is done.
 *  
 *   [W/ pat_bbm.mpa, PC=#020 <- Previous test's PC=#020]
 *
 *    <DR>           <IO>
 *    DUT1n          DUT3n  P(INH)
 *    DUT2n          DUT4n  P(INH)
 *    DUT3n FH(INH)  DUT1n  P
 *    DUT4n FH(INH)  DUT2n  P
 *  
 *   [W/ pat_bbm.mpa, PC=#020 <- Previous test's PC=#040]
 *    (O: Odd BLK, E:Even BLK, M: MASK)
 *    <DR>           <IO>
 *    DUT1n     O:M  DUT3n  E:F O:P
 *    DUT2n     O:M  DUT4n  E:F O:P
 *    DUT3n E:M      DUT1n  E:P O:F
 *    DUT4n E:M      DUT2n  E:P O:F
 **********************************************************************/
void bbm_test_5(TEST_testitem *testarg)
{
    init(BBMARG.ilmode);
    timing_setting(BBMARG.rate);
    readtname();

    FailCaptureSelect(BBMARG.dutgrp);
    bbm_set_condition_drmask(BBMARG, "DRPIN");
    puts("BEFORE MEAS");
    DebugReadBbm(BBMARG.dutgrp); //DEBUG
    fcm_config(pincount/2, 1, "IOPIN");
    fcm_clear();

    MeasFct(BBMARG.mpat, BBMARG.pc, UT_OFF, UT_ON);

    fcm_read(BBMARG.dutgrp,BBMARG.disp_data);
    puts("AFTER MEAS");
    DebugReadBbm(BBMARG.dutgrp); //DEBUG
    bbm_disable();
    BBMARG.post(BBMARG);
    dut_test_result(testarg->testname);
}

/**********************************************************************
 *  bbm_test_7
 *  DR Inhbit (Step1: Make BBM data)
 *
 *   [W/ pat_bbm.mpa, PC=#020]
 *
 *    <DR>         <IO>
 *    DUT1n        DUT3n  F
 *    DUT2n        DUT4n  F
 *    DUT3n FL     DUT1n  P
 *    DUT4n FL     DUT2n  P
 *
 *   [W/ pat_bbm.mpa, PC=#040]
 *    (O: Odd BLK, E:Even BLK)
 *    <DR>         <IO>
 *    DUT1n        DUT3n  E:F, O:P
 *    DUT2n        DUT4n  E:F, O:P
 *    DUT3n FL     DUT1n  E:P, O:F
 *    DUT4n FL     DUT2n  E:P, O:F
 *
 *********************************************************************/
void bbm_test_7(TEST_testitem *testarg)
{
    init(BBMARG.ilmode);
    timing_setting(BBMARG.rate);
    readtname();
    
    FailCaptureSelect(BBMARG.dutgrp);
    bbm_set_condition_capture(BBMARG);
    bbm_clear();	

//  UTL_ExecCalb("cfctest1","normal");
#if 1
    DutCursor dutc = UTL_GetDutCursor(UT_MDUT);
    UT_DUT dut;
    while((dut = UTL_NextDut(dutc)) != UT_NOMORE)
       if(dut%4 == 3 || dut%4 == 0) level_fix(dut, UT_PIN_FIXL, "DRPIN");
    UTL_DeleteCursor(dutc);
#endif
    MeasFct(BBMARG.mpat, BBMARG.pc, UT_OFF, UT_OFF);

#if 1
    dutc = UTL_GetDutCursor(UT_MDUT);
    while((dut = UTL_NextDut(dutc)) != UT_NOMORE)
       if(dut%4 == 3 || dut%4 == 0) level_fix(dut, UT_PIN_NONE, "DRPIN");
    UTL_DeleteCursor(dutc);
#endif
    DebugReadBbm(BBMARG.dutgrp);   //DEBUG
    bbm_read_address(BBMARG.dutgrp, BBMARG.disp_data);
    bbm_read_count(BBMARG.dutgrp);
//  bbm_disable();

    BBMARG.post(BBMARG);
    dut_test_result(testarg->testname);

}

/**********************************************************************
 *  bbm_test_6
 *  DR Inhibit 
 *  BBM has only 0, which does not inhibit DR output.
 *  Therefore, results should be all block fail with PC=#020, pat_bbm.
 **********************************************************************/
void bbm_test_6(TEST_testitem *testarg)
{
    init(BBMARG.ilmode);
    timing_setting(BBMARG.rate);
    readtname();

    FailCaptureSelect(BBMARG.dutgrp);
    bbm_set_condition_drmask(BBMARG,"DRPIN");  // <- bbm_set_condition_capture(BBMARG);
    bbm_clear();	
//  puts("BEFORE MEAS");
//  DebugReadBbm(BBMARG.dutgrp);  //DEBUG

//  UTL_ExecCalb("cfctest1","normal");
    MeasFct(BBMARG.mpat, BBMARG.pc, UT_OFF, UT_OFF);

//  puts("AFTER MEAS");
//  DebugReadBbm(BBMARG.dutgrp);  //DEBUG

    bbm_read_address(BBMARG.dutgrp, BBMARG.disp_data);
    bbm_read_count(BBMARG.dutgrp);
    bbm_disable();

    BBMARG.post(BBMARG);
    dut_test_result(testarg->testname);
}

/**********************************************************************
 * bbm_test_d
 *   [W/ pat_bbm.mpa, PC=#020]
 *    All BLKs fail.
 *   [W/ pat_bbm.mpa, PC=#040]
 *    Even BLKs fail.
 *
 **********************************************************************/
void bbm_test_d1(TEST_testitem *testarg)
{
    init_ddr_bbm(BBMARG.ilmode);
    timing_setting(BBMARG.rate);
    readtname();
    
    FailCaptureSelect(BBMARG.dutgrp);
    bbm_set_condition_capture(BBMARG);
    bbm_clear();	

    fcm_config_ddr(pincount, 1, "IOPIN");
    burstscram(UT_ON);
//  puts("BEFORE MEAS");
//  DebugReadBbm(BBMARG.dutgrp);  //DEBUG
//  UTL_ExecCalb("cfctest1","normal");
//
    MeasFct(BBMARG.mpat, BBMARG.pc, UT_OFF, UT_OFF);
    bbm_read_address(BBMARG.dutgrp, BBMARG.disp_data);
    bbm_read_count(BBMARG.dutgrp);
//  puts("AFTER MEAS");
//  DebugReadBbm(BBMARG.dutgrp);  //DEBUG
    bbm_disable();	
    burstscram(UT_OFF);

    BBMARG.post(BBMARG);
    dut_test_result(testarg->testname);
}

void bbm_test_d2(TEST_testitem *testarg)
{
    init_ddr_ecc(BBMARG.ilmode);
    timing_setting(BBMARG.rate);
    readtname();
    
    FailCaptureSelect(BBMARG.dutgrp);
    bbm_set_condition_capture(BBMARG);
    bbm_clear();	

    fcm_config_ddr(pincount, 1, "IOPIN");
    burstscram(UT_ON);
//  puts("BEFORE MEAS");
//  DebugReadBbm(BBMARG.dutgrp);  //DEBUG
//  UTL_ExecCalb("cfctest1","normal");
//
    MeasFct(BBMARG.mpat, BBMARG.pc, UT_OFF, UT_OFF);
    bbm_read_address(BBMARG.dutgrp, BBMARG.disp_data);
    bbm_read_count(BBMARG.dutgrp);
//  puts("AFTER MEAS");
//  DebugReadBbm(BBMARG.dutgrp);  //DEBUG
    bbm_disable();	
    burstscram(UT_OFF);

    BBMARG.post(BBMARG);
    dut_test_result(testarg->testname);
}
