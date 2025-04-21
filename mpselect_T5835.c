#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "UTSC.h"
#include "test.h"
#include "test_struct.h"
#include "mpselect.h"
#include "common.h"



#define DEBUG 1
#define V *1.0
#define ms *1.0e-3
#define us *1.0e-6
#define ns *1.0e-9
#define mA *1.0e-3
#define uA *1.0e-6
#define nA *1.0e-9

DSlider TMR0, TMR1;
int pincount;
#define BITCNT8  8
//////////////////////////////////////////////////////////////////////////
// BBM settings
//////////////////////////////////////////////////////////////////////////
#define DUTMAX  32
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

char patnpc[][2][30] = {
  {"pat_pmc.mpa", "AAA"},      //0
  {"pat_pmc2.mpa","BBB"},
  {"END", ""}, 
  {"pat_fbrc1.mpa","A"},       //3
  {"pat_fbrc1.mpa","B"},
  {"pat_fbrc1.mpa","C"},
  {"pat_fbrc1.mpa","D"},       /* SUB STFL */
  {"pat_fbrc2.mpa","DD"},      /* SUB STFL */
  {"pat_fbrc3.mpa","DDD"},     /* SUB STFL */
  {"END", ""},
  {"pat_flgj1.mpa","E"},       //10
  {"pat_flgj1.mpa","F"},
  {"pat_fbrc3.mpa","DDD"},     /* SUB STFL */
  {"pat_flgj1.mpa","GG"},      /* SUB STPS */
  {"END", ""},
  {"pat_flgs1.mpa","H"},       //15
  {"pat_flgs1.mpa","I"},
  {"pat_flgs1.mpa","J"},
  {"pat_flgs1.mpa","KK"},      /* SUB STPS */
  {"pat_fbrc3.mpa","DDD"},     /* SUB STFL */
  {"END", ""},
  {"pat_flgl1.mpa","L"},       //21
  {"pat_flgl1.mpa","M"},
  {"pat_flgl1.mpa","NN"},      /* SUB STPS */
  {"pat_fbrc3.mpa","DDD"},     /* SUB STFL */
  {"END", ""},
  {"pat_stisp.mpa","P"},       //26
  {"pat_fbrc3.mpa","CREF1"},   /* SUB REFRESH */  
  {"pat_fbrc3.mpa","CREF2"},   /* SUB REFRESH */
  {"pat_fbrc3.mpa","CREF3"},   /* SUB REFRESH */
  {"pat_fbrc3.mpa","CREF4"},   /* SUB REFRESH */
  {"END", ""},
  {"pat_idx1.mpa","A"},        //32
  {"pat_idx3.mpa","C"},
  {"END", ""},
  {"pat_cflg1.mpa","A"},       //35
  {"pat_cflg2.mpa","B"},
  {"pat_cflg3.mpa","C"},
  {"pat_cflg4.mpa","D"},
  {"pat_cflg5.mpa","E"},
  {"pat_cflg6.mpa","F"},
  {"pat_cflg7.mpa","G"},
  {"pat_cflg8.mpa","H"},
  {"pat_cflg9.mpa","I"},
  {"pat_cflg10.mpa","J"},
  {"pat_cflg11.mpa","K"},
  {"pat_cflg12.mpa","L"},
  {"pat_cflg13.mpa","M"},
  {"pat_cflg14.mpa","N"},
  {"pat_cflg15.mpa","O"},
  {"pat_cflg16.mpa","P"},
  {"pat_cflg1.mpa","L1"},
  {"END", ""},
  {"pat_loopidxi1.mpa","A"},   //53
  {"pat_loopjni1.mpa", "B"},
  {"pat_loopsti1.mpa", "C"},   //sti 384
  {"pat_loopinc1.mpa", "D"},
  {"pat_loopldiidxi.mpa","F"},
  {"pat_loopldijni.mpa", "G"},
  {"pat_loopldisti.mpa", "H"},
  {"pat_loopldiinc.mpa", "I"}, 
  {"pat_loopdec1.mpa",   "E"},
  {"END", ""},
  {"pat_subr1.mpa", "A"}, //63
  {"pat_subr1.mpa", "B"},
  {"pat_subr1.mpa", "C"},
  {"pat_subr1.mpa", "D"},
  {"pat_subr1.mpa", "E"},
  {"pat_subr1.mpa", "F"},
  {"pat_subr1.mpa", "G"},
  {"pat_subr1.mpa", "H"},
  {"pat_subr2.mpa", "AA"},
  {"pat_subr3.mpa", "BB"},
  {"pat_subr4.mpa", "CC"},
  {"pat_subr5.mpa", "DD"},
  {"pat_subr6.mpa", "EE"},
  {"pat_subr7.mpa", "FF"},
  {"pat_subr8.mpa", "GG"},
  {"pat_subr9.mpa", "HH"},
  {"END", ""},
  {"pat_wait1.mpa", "A"}, //80
  {"pat_wait1.mpa", "B"},
  {"pat_wait1.mpa", "C"},
  {"pat_wait1.mpa", "D"},
  {"pat_wait1.mpa", "E"},
  {"pat_wait1.mpa", "F"},
  {"pat_wait1.mpa", "G"},
  {"pat_wait1.mpa", "H"},
  {"pat_wait2.mpa", "AA"},
  {"pat_wait3.mpa", "BB"},
  {"pat_wait4.mpa", "CC"},
  {"pat_wait5.mpa", "DD"},
  {"pat_wait6.mpa", "EE"},
  {"pat_wait7.mpa", "FF"},
  {"pat_wait8.mpa", "GG"},
  {"pat_wait9.mpa", "HH"},
  {"END", ""},
  {"pat_calm1.mpa", "A"}, //97
  {"pat_calm1.mpa", "B"},
  {"pat_calm1.mpa", "C"},
  {"pat_calm1.mpa", "D"},
  {"pat_calm1.mpa", "E"},
  {"pat_calm1.mpa", "F"},
  {"pat_calm1.mpa", "G"},
  {"pat_calm1.mpa", "H"},
  {"pat_calm2.mpa", "AA"},
  {"pat_calm3.mpa", "BB"},
  {"pat_calm4.mpa", "CC"},
  {"pat_calm5.mpa", "DD"},
  {"pat_calm6.mpa", "EE"},
  {"pat_calm7.mpa", "FF"},
  {"pat_calm8.mpa", "GG"},
  {"pat_calm9.mpa", "HH"},
  {"pat_calm1.mpa", "I"},
  {"END", ""},
  {"pat_stps.mpa", "SNGL"}, //115
  {"END", ""},
};

#define STOP 9999
USlider exp_reg[][10] =
{
  {2047,4095,STOP},              /*13000 PC MAX*/
  {0x1A,0x1C,0x20,STOP},         /*13001 FLAG BAR REGISTER*/
  {0x0D,0x0F,STOP},              /*13002 FLGJ1*/
  {0x1F,0x1B,0x12,STOP},         /*13003 FLGS1*/
  {0x1A,0x16,STOP},              /*13004 FLGL1*/
  {0x0D,0x0F,0x12,0x16,STOP},    /*13005 STISPn (ISPn)*/

  {0x1a,0x1e,0x22,0x26,0x2a,0x2e,0x32,0x36,STOP}, /*13010 WAIT 1*/
  {0x02,0x05,0x08,0x0b,0x0e,0x11,0x14,0x17,STOP}, /*13010 WAIT 2*/
  
  {0x1a,0x1f,0x24,0x29,0x2e,0x33,0x38,0x3d,STOP}, /*CALM2*/
  {0x02,0x05,0x08,0x0b,0x0e,0x11,0x14,0x17,STOP}, /*CALM2*/
};


FctHandle g_fcth;
/**
 * @file main.c
 * @author Advantest Corp.
 * @brief Sample Code For MpatSelect Test
 * @version 1.0
 * @date 2022-04
 */

/*
 *  ReadFunc
 *    Get pass/fail for each pin per DUT.
 *    It is useful for debugging.
 */
static void ReadFunc(unsigned int exp)
{
    ScFailPinHandle scfph;
    PinCursor pinc;
    DutCursor dutc;
    UT_PIN pin;
    UT_DUT dut;
    CheckButton res;
    unsigned int pinres=0;
    int i=0;

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
       pinres=0;
       i=0;
       while ((pin = UTL_NextPin(pinc)) != UT_NOMORE) {
          UTL_GetScFailPin(scfph, dut, pin, &res);
//        printf("DUT %2d, Pin %2d Res %d\n", dut, pin, res);
          if(res) pinres |=  (1<<i);
          i++;
       }
       printf("DUT%d Result=#%02X (Exp:#%02X)\n", dut, pinres, exp);
       UTL_DeleteCursor(pinc);
    }
    UTL_DeleteCursor(dutc);
    UTL_DeleteHandle(scfph);
}

static void SetResetDut(CheckButton setreset)
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
static void ilmode(RadioButton ilmd)
{
//  RadioButton mode = 8;
    IlModeHandle ilmh = UTL_GetIlModeHandle();
    UTL_SetIlMode   (ilmh, ilmd);
    UTL_SendIlMode  (ilmh);
    UTL_DeleteHandle(ilmh);

}

static void pin_list(void)
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
//  printf("[DEBUG]pincount = %d\n", pincount);
    
    
    if( pincount == 9) {
       UTL_CreatePinList ("IOPIN");
       UTL_SetPinType    ("IOPIN",UT_PINTYPE_PIN);
       for (i=0; i<pcnt[0]; i++) UTL_AddPinNumber ("IOPIN", plst[0][i] );
       //IO0 is only for FCM fail capture
       UTL_CreatePinList ("IO0");
       UTL_SetPinType    ("IO0",UT_PINTYPE_PIN);
       UTL_AddPinNumber  ("IO0", plst[0][0] );
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

static void power_seq(void)
{
//  printf("[DEBUG]%s\n",__func__);
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
static void pin_condition(void)
{
    int i;
    PinHandle tesph = UTL_GetPinHandle();

//  printf("[DEBUG]%s\n",__func__);

    UTL_SetPinViNumber     (tesph, 1);
    UTL_SetPinDrWaveform   (tesph, UT_WAV_RZO);
    UTL_SetPinDrClock      (tesph, UT_PIN_BCLK, 1);
    UTL_SetPinDrClock      (tesph, UT_PIN_CCLK, 1);
    UTL_SetPinIoCtrl       (tesph, UT_ON);
    UTL_SetPinVoNumber     (tesph, 1);
    UTL_SetPinVtNumber     (tesph, 1);
    UTL_SetPinTerm         (tesph, UT_ON);
    UTL_SetPinDreNumber    (tesph, 1);
    UTL_SetPinDreWaveform  (tesph, UT_DREWAV_NRZ);
    UTL_SetPinDreClock     (tesph, 1); 
    UTL_SetPinMatchMode    (tesph, UT_SIG_MATCH);
    UTL_AddPinStrbCpeNumber(tesph, 1, 1);

    for ( i=0; i<pincount; i++ )
    {
        UTL_AddPinPdsA      (tesph, UT_SIG_X(i), 1);
        UTL_AddPinPdsB      (tesph, UT_SIG_Y(i), 1);
        UTL_AddPinPdsA      (tesph, UT_SIG_Y(i), 2);
        UTL_AddPinPdsB      (tesph, UT_SIG_D(i), 2);
    }
    UTL_SendPin(tesph, "IOPIN");

    UTL_DeleteHandle(tesph);
}


static void change_pds_for_nDUTs(int oedut)
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
/*
 * level_setting
 *
 */
static void level_setting(int channel, DSlider high, DSlider low, DSlider vterm)
{
//  printf("[DEBUG]%s\n",__func__);
    DSlider vtl = (high+low)/2;

    ViHandle vih = UTL_GetViHandle();
    UTL_SetViHigh(vih, high   );
    UTL_SetViLow (vih, low    );
    UTL_SendVi   (vih, channel);

    VtHandle vth = UTL_GetVtHandle();
    UTL_SetVt (vth, vterm);
    UTL_SendVt(vth, channel);

    VoHandle voh = UTL_GetVoHandle();
    UTL_SetVoHigh(voh, vtl);   //This is used as VOH & VOL
    UTL_SetVoLow (voh, vtl);
    UTL_SendVo   (voh, channel);

    UTL_DeleteHandle(vih);
    UTL_DeleteHandle(vth);
    UTL_DeleteHandle(voh);
}


static void level_fix(UT_DUT dut, RadioButton level, char *pinname)
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

static void level_setting_perpin(void)
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
static void timing_setting(DSlider tck)
{
    TgHandle tgh = UTL_GetTgHandle();
    UTL_AddTgRate(tgh, 1,    tck);
    UTL_AddTgBclk(tgh, 1, 1, tck*0.25);      UTL_AddTgCclk(tgh, 1, 1, tck*0.75);
    UTL_AddTgDreL(tgh, 1, 1, tck*0.00);      UTL_AddTgDreT(tgh, 1, 1, tck*0.00);
    UTL_AddTgStrb(tgh, 1, 1, tck*0.50);

    const DSlider ts2_tck=850e-9;  /* At match cycle, RATE>=850nS + STRB position */
    UTL_AddTgRate(tgh, 2,    ts2_tck*2);
    UTL_AddTgBclk(tgh, 2, 1, ts2_tck*0.50);  UTL_AddTgCclk(tgh, 2, 1, ts2_tck*1.50);
    UTL_AddTgDreL(tgh, 2, 1, 0.00);          UTL_AddTgDreT(tgh, 2, 1, 0.00);
    UTL_AddTgStrb(tgh, 2, 1, ts2_tck);
    UTL_SendTg   (tgh);

    UTL_DeleteHandle(tgh);
}


static void readtname(){
    char *tname;
    tname = UTL_ReadTestName();
    printf("\nTEST NAME : %s\n",tname);	
}


static void MeasFct(char *mpat, USlider pc, RadioButton pgstop, RadioButton pgclear)
{

    static FctHandle fct = -1;

    if (fct < 0) fct = UTL_GetFctHandle();
    UTL_SetFctMpatName   (fct, mpat);
    UTL_SetFctStartPc    (fct, pc);         
    UTL_SetFctFailInhibit(fct, pgstop);
    UTL_SetFctNoClear    (fct, pgclear);
	
    UTL_MeasFct(fct);
}

static void MeasFct_MpatSelect(int startpat, int datapat, RadioButton pgstop)
{
//  printf("[DEBUG]%s  startpat(%s,%s), datapat(%s,%s)\n",__func__,patnpc[startpat][0],patnpc[startpat][1],patnpc[datapat][0], patnpc[datapat][1]);

    UTL_SetFctStartLabelNameOfMpatSelector    (g_fcth, patnpc[startpat][0],patnpc[startpat][1]);
    UTL_SetFctMpatDataFileNameWithMpatSelector(g_fcth, patnpc[datapat][0], patnpc[datapat][1]);
    UTL_SetFctMpatTransferDataInhibit         (g_fcth, UT_MPAT_INH_REGISTER, UT_OFF);
    UTL_SetFctFailInhibit                     (g_fcth, pgstop);
    UTL_MeasFct                               (g_fcth);
}

static void StartFct_MpatSelect(int startpat, int datapat, RadioButton pgstop)
{
//  printf("[DEBUG]%s  startpat(%s,%s), datapat(%s,%s)\n",__func__, patnpc[startpat][0],patnpc[startpat][1],patnpc[datapat][0], patnpc[datapat][1]);

    UTL_SetFctStartLabelNameOfMpatSelector    (g_fcth, patnpc[startpat][0],patnpc[startpat][1]);
    UTL_SetFctMpatDataFileNameWithMpatSelector(g_fcth, patnpc[datapat][0], patnpc[datapat][1]);
    UTL_SetFctMpatTransferDataInhibit         (g_fcth, UT_MPAT_INH_REGISTER, UT_OFF);
    UTL_SetFctFailInhibit                     (g_fcth, pgstop);
    UTL_StartFct                              (g_fcth);
}
/**
* @brief Get the program counter value and execute MeasFct.
* 
*/
 









/**
* @brief reads out the test result of a specified test name and disply Pass/Fail.
* @param (tname) test name
*/

static void dut_test_result(char tname[])
{
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

static void test_result(char tname[])
{
    RadioButton dut_test_res[DUTMAX]={0,};
    UT_DUT dutc;
    DutCursor dutcur;
    int fail=0;

    dutcur = UTL_GetDutCursor(UT_CDUT);
    while((dutc = UTL_NextDut(dutcur))!=UT_NOMORE){
        dut_test_res[dutc-1] = UTL_ReadTestResult(dutc, tname, UT_RES_ALL); 
        if(dut_test_res[dutc-1]==0) {
            printf("Do not Judgment\n", dutc);  //UT_RES_NOT_TESTED=0
            fail=1;
            break;
        }
        else if(dut_test_res[dutc-1]==3) {
            printf("FAILED\n", dutc);           //UT_READ_FAILED=3
            fail=1;
            break;
        }
    }
    if(fail == 0) printf("PASSED\n");
    UTL_DeleteCursor(dutcur);
}
/**
* @brief Reads out the final test result and set the category..
*
*/

static void dut_final_result(void){
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

static void dut_rejection(void){
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

static void fcm_config(USlider n1, USlider n2, char *pinlist)
{
#if 0
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
#endif
}


static void fcm_clear()
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



static void init(RadioButton ilmd, DSlider vterm)
{
    ilmode(ilmd);
    pin_list();
    power_seq();
    pin_condition();
    level_setting(1, 1.00 V, 0.00 V, vterm);    // (channel, Vi high, Vi low, Vt)
}

static void burstscram(RadioButton onoff)
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

static void AddMpatSelect(TEST_testitem *testarg, USlider *pcadd, int *pat_i)
{
    MpatSelectorHandle mpsh;
    MpatSelectorCursor mpsc;
    MpatSelector *mpsel;
    int i;

    mpsh = UTL_GetMpatSelectorHandle();
    for (i=MPSELARG.pind; strcmp(patnpc[i][0],"END")!=0; i++) { 
        UTL_AddMpatSelector  (mpsh, patnpc[i][0],  patnpc[i][1]);
        printf("pat=%s  label=%s\n",patnpc[i][0],  patnpc[i][1]);
        if(*pat_i == -1) *pat_i = i;
        fflush(stdout);
    }
    UTL_SendMpatSelector (mpsh);
    UTL_ClearMpatSelector(mpsh);

    UTL_UpdateMpatSelector(mpsh);
    mpsc = UTL_GetMpatSelectorCursor (mpsh);
    i=0;
    while((mpsel = UTL_NextMpatSelector(mpsc)) != NULL) {
        printf("[%s (PC #%04x, PatCount %d, LoadPC #%03x, labal:%s, )]\n",
              mpsel->FileName, mpsel->pc, mpsel->PatCount, mpsel->LoadPc, mpsel->label);
        fflush(stdout);
        pcadd[i++]=mpsel->LoadPc;
    }


}

void StartAlpg()
{
//  printf("[DEBUG]%s\n",__func__);
    USlider ovf;
    RadioButton pgstat;
    UTL_OnPowerSeq();
    UTL_WaitTime(1);
    TMR0=UTL_ReadTimer(&ovf);
    UTL_StartAlpg   (UT_ALPG_NORMAL_START);
    while((pgstat=UTL_ReadAlpgStatusFlag())!=UT_ALPG_STATUS_STOP) {
//      if     (pgstat == UT_ALPG_STATUS_SUSPEND) puts("ALPG...SUSPEND");
//      else if(pgstat == UT_ALPG_STATUS_RUNNING) puts("ALPG...RUNNING");
    } 
    TMR1=UTL_ReadTimer(&ovf);
//  printf(" *** TOTAL   funcWithPatStartAlpg               :%8.02f [uS]\n", (TMR1-TMR0)*1000*1000);

}

static void SetResultPc(USlider pcr, int exp_p, int i)
{
   char *testname = UTL_ReadTestName();
   static char prev_testname[100]="";
   static unsigned int acum_res;

   if(strcmp(testname, prev_testname) != 0) {
       strcpy(prev_testname, testname);
       acum_res = 0;
//     printf("%s  <- %s\n",testname, prev_testname);
   }

   DutCursor dutc;
   dutc=UTL_GetDutCursor(UT_MDUT);
   UT_DUT dut=0;
   while((dut=UTL_NextDut(dutc)) != UT_NOMORE){
       if (pcr != exp_reg[exp_p][i]) {
           UTL_SetTestResult  (dut, testname, UT_RES_ALL);
           acum_res |= (1<<(dut-1));
       }
       else if ((acum_res & (1<<(dut-1))) == 0)
           UTL_ResetTestResult(dut, testname, UT_RES_ALL);
   }
   UTL_DeleteCursor(dutc);

}

static USlider ReadUSReg(RadioButton reg_name)
{
   return  UTL_ReadUSRegister(reg_name, 1);

}

void ReadPc(int exp_p, int i)
{
   USlider pcr;

   pcr = UTL_ReadUSRegister            (UT_REG_PC, 1);
   printf("PC=#%04X(%4d)  \texp=#%04X(%4d)  \n",
              pcr, pcr, exp_reg[exp_p][i], exp_reg[exp_p][i]);
   SetResultPc(pcr, exp_p, i);

}

void ReadIsp(int exp_p, int i)
{
   int n;
   USlider ispr;
   RadioButton isp[]={UT_REG_ISP, UT_REG_ISP2, UT_REG_ISP3, UT_REG_ISP4};
   
   for(n=0; n<(sizeof(isp)/sizeof(RadioButton)); n++) {
      ispr = UTL_ReadUSRegister            (isp[n], 1);
      printf("ISP%d=#%04X(%4d)  \texp=#%04X(%4d)  \n",
                 n+1, ispr, ispr, exp_reg[exp_p][i+n], exp_reg[exp_p][i+n]);
      SetResultPc(ispr, exp_p, i+n);
   }

}
/**********************************************************************
 * mpsl_test1 
 * 13000 MPSEL PC MAX CHECK
 *
 *
 *
 *
 **********************************************************************/
void mpsel_test1(TEST_testitem *testarg)
{
    USlider pcadd[16];
    USlider pcr;
    int pat_i = -1;   //Index for initial pattern program   

    UTL_StartTimer(UT_TIMER_R1US);
    init(MPSELARG.ilmode, MPSELARG.vterm);
    timing_setting(MPSELARG.rate);
    readtname();
    
    AddMpatSelect(testarg, pcadd, &pat_i);

    int i=0;
    while(exp_reg[MPSELARG.exp_p][i] != STOP)
    {
        USlider pc = pcadd[i];
        UTL_WriteRegUs_Lite                 (UT_REG_STAPC, &pc,sizeof(pc));

        MPSELARG.pg_run();

        MPSELARG.post2(MPSELARG.exp_p,i);
        i++;
    }

}

/**********************************************************************
 * mpsl_test2 
 * 13001 MPSEL FLAG BAR REGISTER CHECK
 *
 *
 *
 *
 **********************************************************************/
void mpsel_test2(TEST_testitem *testarg)
{
    int i=0;
    USlider pcadd[16];
    USlider pcr;
    int pat_i = -1;   //Index for initial pattern program   

    init(MPSELARG.ilmode, MPSELARG.vterm);
    timing_setting(MPSELARG.rate);
    readtname();
    
//  FailCaptureSelect(MPSELARG.dutgrp);

    AddMpatSelect(testarg, pcadd, &pat_i);

    while(exp_reg[MPSELARG.exp_p][i] != STOP)
    {
        USlider pc = pcadd[i];
        UTL_WriteRegUs_Lite                       (UT_REG_STAPC, &pc,sizeof(pc));
        UTL_SetFctMpatDataFileNameWithMpatSelector(g_fcth, patnpc[i][0],patnpc[i][1]);
        UTL_SetFctMpatTransferDataInhibit         (g_fcth, UT_MPAT_INH_REGISTER, UT_ON);

        MPSELARG.pg_run;

        MPSELARG.post2(MPSELARG.exp_p,i);
//      pcr = UTL_ReadUSRegister            (MPSELARG.reg, 1);
//      printf("PC=#%04X(%4d)  \texp=#%04X(%4d)  \n",pcr, pcr, exp_reg[MPSELARG.exp_p][i], exp_reg[MPSELARG.exp_p][i]);
//      SetResultPc(pcr, exp_reg[MPSELARG.exp_p][i]);
        i++;
    }

    dut_test_result(testarg->testname);
}
#if 0
/**********************************************************************
 * mpsl_test2 
 * 13001 MPSEL FLAG BAR REGISTER CHECK
 *
 *
 *
 *
 **********************************************************************/
void mpsl_test02(TEST_testitem *testarg) //IDX CHECK
{
    int i;
    unsigned int pcadd[16];
    USlider pcr;

    init(MPSELARG.ilmode);
    timing_setting(MPSELARG.rate);
    readtname();
    
    FailCaptureSelect(MPSELARG.dutgrp);

    AddMpatSelect(pcadd);


    g_fcth = UTL_GetFctHandle();

    UTL_SetFctStartLabelNameOfMpatSelector          (g_fcth, patnpc[i][0], patnpc[i][1] );
    UTL_SetFctFailInhibit                           (g_fcth, UT_ON); 
    UTL_MeasFct				            (g_fcth				);

    readPfcRealAll2(expcount1);

    unsigned int val;
    getreg(UT_REG_XB, &val);
    getreg(UT_REG_YB, &val);

    USlider pc = pcadd[1];//0x7f0;
    UTL_WriteRegUs_Lite			(UT_REG_STAPC, &pc,sizeof(pc));

    TMR0=UTL_ReadTimer(&ovf);
    UTL_StartAlpg	(UT_ALPG_NORMAL_START);
    while(UTL_ReadAlpgStatusFlag()!=UT_ALPG_STATUS_STOP)
    {
    	;
    }
    TMR1=UTL_ReadTimer(&ovf);
    getreg(UT_REG_XB, &val);
    getreg(UT_REG_YB, &val);
    int expcount2=2*2*2*2*3*2*2*2;
    readPfcRealAll2(expcount2);
}

#endif

/*
 * When StartAlpg is used without using MeasFct first,
 * DRE is FL. The setdrereg is to set DRE WT.
 *
 */
static void setdrereg()
{

    RegHandle rh = UTL_GetRegHandle();
    UTL_SetRegDirection(rh, UT_HT);       //Handle -> ALPG
    UTL_SetRegDre1     (rh, UT_SIG_WT);
    UTL_SendReg        (rh);
    UTL_DeleteHandle   (rh);
}

void mpsel_test3(TEST_testitem *testarg)
{
    unsigned int pcadd[16];
    USlider pcr;
    int pat_i = -1;   //Index for initial pattern program   

    init(MPSELARG.ilmode, MPSELARG.vterm);    //Make match cycles failed
    timing_setting(MPSELARG.rate);
    readtname();

    AddMpatSelect(testarg, pcadd, &pat_i);

    g_fcth=UTL_GetFctHandle();

    UTL_SetFctMpatDataFileNameWithMpatSelector(g_fcth, patnpc[pat_i][0], patnpc[pat_i][1]);
    UTL_StartFct                              (g_fcth);
    MPSELARG.post2(MPSELARG.exp_p,0);
    
    setdrereg();
    int i=1;
    while(exp_reg[MPSELARG.exp_p][i] != STOP)
    {
        USlider pc = pcadd[i];

        UTL_WriteRegUs_Lite (UT_REG_STAPC, &pc,sizeof(pc));
        MPSELARG.pg_run();
        MPSELARG.post2(MPSELARG.exp_p,i);

        i++;
    }
    UTL_DeleteHandle(g_fcth);
}

void mpsel_flgj1(TEST_testitem *testarg)
{
    unsigned int pcadd[16];
    USlider pcr;
    int pat_i = -1;   //Index for initial pattern program   

    init(MPSELARG.ilmode, MPSELARG.vterm);    //Make match cycles failed
    timing_setting(MPSELARG.rate);
    readtname();

    AddMpatSelect(testarg, pcadd, &pat_i);

    g_fcth=UTL_GetFctHandle();

    UTL_SetFctMpatDataFileNameWithMpatSelector(g_fcth, patnpc[pat_i][0], patnpc[pat_i][1]);
    UTL_StartFct                              (g_fcth);
    MPSELARG.post2(MPSELARG.exp_p,0);

//  printf("exp_reg=#%02X\n",exp_reg[MPSELARG.exp_p][0]);
//  printf("exp_reg=#%02X\n",exp_reg[MPSELARG.exp_p][1]);
//  printf("pc=#%02X\n",pcadd[0]);
//  printf("pc=#%02X\n",pcadd[1]);

    setdrereg();
    int i=1;
    while(exp_reg[MPSELARG.exp_p][i] != STOP)
    {
        USlider pc = pcadd[i];

		UTL_WriteRegUs_Lite (UT_REG_STAPC, &pc,sizeof(pc));
        MPSELARG.pg_run();
		MPSELARG.post2(MPSELARG.exp_p,i);

        i++;
    }
    UTL_DeleteHandle(g_fcth);
}

static void readPfc(int exp)
{
    int i;
    unsigned int pfcval;
    UT_DUT dut;
    char *testname = UTL_ReadTestName();
    static char prev_testname[100]="";
    static unsigned int acum_res;
    
    if(strcmp(testname, prev_testname) != 0) {
        strcpy(prev_testname, testname);
        acum_res = 0;
//      printf("%s  <- %s\n",testname, prev_testname);
    }
    FcmAccessHandle h = UTL_GetFcmAccessHandle();
    
    UTL_SetFcmAccessAutoAddrAssignMode(h, UT_ON);
    UTL_SetFcmAccessAllBit     (h, UT_ON);
    UTL_SetFcmAccessPfcMode    (h, UT_FCM_PFCMODE_REALTIME);
    UTL_SetFcmAccessPfcNoClear (h, UT_ON);
    UTL_SetFcmAccessAllDut     (h, UT_OFF);
    
    DutCursor dutc = UTL_GetDutCursor(UT_MDUT);
    while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
       UTL_SetFcmAccessDut        (h, dut);
       pfcval=UTL_GetFcmParallelFailCount(h);
//     printf("[DEBUG]DUT%2d pfcval=%d\n", dut, pfcval); fflush(stdout);
       if (pfcval != exp){
            printf(" *** DUT%2d FAIL**(%d)\n", dut, pfcval);
            UTL_SetTestResult  (dut, testname, UT_RES_ALL);
            acum_res |= (1<<(dut-1));
       }
       else if ((acum_res & (1<<(dut-1))) == 0) UTL_ResetTestResult(dut, testname, UT_RES_ALL);
    }
//  printf("acum_res=#%08x\n",acum_res);
    UTL_DeleteCursor(dutc);
    UTL_DeleteHandle(h);
}

static void ConfigFcm()
{
	FcmConfigHandle h = UTL_GetFcmConfigHandle();

	UTL_SetFcmConfigBitSize      (h, 1);
	UTL_SetFcmConfigDutBitSize   (h, 1);
	UTL_AddFcmConfigAction       (h, 1, UT_FCM_TOTALFAIL);

	int y;
	for (y = 0; y < 10; y++) UTL_SetFcmConfigAddrAssign (h, y, UT_SIG_Y(y));
	UTL_AddFcmConfigPinAssign (h, 0, 1);

	UTL_SendFcmConfig(h);
	UTL_DeleteHandle (h);

}

static void FailCaptureSelect()
{
    FailCaptureSelectHandle fcsh = -1;

    if(fcsh < 0) {
        fcsh = UTL_GetFailCaptureSelectHandle();
        UTL_SetFailCaptureSelectAllDutGroupNumber(fcsh, UT_ON);
        UTL_SetFailCaptureSelectAllPin           (fcsh, UT_OFF);
        UTL_SetFailCaptureSelectPinList          (fcsh, "IO0");
    }
    UTL_SendFailCaptureSelect(fcsh);
}

void mpsel_idx(TEST_testitem *testarg)
{
    USlider pcadd[16];
    int pat_i = -1;   //Index for initial pattern program   

    init(MPSELARG.ilmode, MPSELARG.vterm);    //Make match cycles failed
    timing_setting(MPSELARG.rate);
    readtname();

    AddMpatSelect(testarg, pcadd, &pat_i);
    UTL_StartTimer(UT_TIMER_R1US);

    g_fcth=UTL_GetFctHandle();

    FailCaptureSelect();
    ConfigFcm();

    //SEND REGISTER VALUES
    UTL_SetFctMpatDataFileNameWithMpatSelector (g_fcth, "pat_idx3.mpa", "C");
    //REG MPAT PC & SEND MPAT
    UTL_SetFctStartLabelNameOfMpatSelector     (g_fcth, "pat_idx1.mpa", "A");
    UTL_SetFctMpatTransferDataInhibit          (g_fcth, UT_MPAT_INH_REGISTER, UT_OFF); 
    UTL_SetFctFailInhibit                      (g_fcth, UT_ON); 
    UTL_MeasFct   	                           (g_fcth);
    readPfc(2*4*5*6*7*8*9*10);
    UTL_DeleteHandle                           (g_fcth);

//  printf("pcadd #%02x\n", pcadd[1]);
    UTL_WriteRegUs_Lite	(UT_REG_STAPC, &pcadd[1], sizeof(pcadd[1]));
    StartAlpg();

#if 0
    //SEND REGISTER VALUES
    UTL_SetFctMpatDataFileNameWithMpatSelector (g_fcth, "pat_idx1.mpa", "A");
    //REG MPAT PC & SEND MPAT
    UTL_SetFctStartLabelNameOfMpatSelector     (g_fcth, "pat_idx3.mpa", "C");
    UTL_SetFctMpatTransferDataInhibit          (g_fcth, UT_MPAT_INH_REGISTER, UT_OFF); 
    UTL_SetFctFailInhibit                      (g_fcth, UT_ON); 
    UTL_MeasFct   	                       (g_fcth);
#endif
    readPfc(2*2*2*2*3*2*2*2);
}



void mpsel_isp(TEST_testitem *testarg)
{
    int i=0;
    USlider pcadd[16];
    USlider pcr;
    int pat_i = -1;   //Index for initial pattern program   

    UTL_StartTimer(UT_TIMER_R1US);
    init(MPSELARG.ilmode, MPSELARG.vterm);
    timing_setting(MPSELARG.rate);
    readtname();
    
    AddMpatSelect(testarg, pcadd, &pat_i);

    USlider pc = pcadd[i];
    UTL_WriteRegUs_Lite                 (UT_REG_STAPC, &pc,sizeof(pc));
    
    MPSELARG.pg_run();
    
    MPSELARG.post2(MPSELARG.exp_p,i);
}





void mpsel_cflg(TEST_testitem *testarg)
{
    USlider pcadd[16], cflg, idx1;
    int i;
    int pat_i = -1;   //Index for initial pattern program   

    UTL_StartTimer(UT_TIMER_R1US);
    init(MPSELARG.ilmode, MPSELARG.vterm);
    timing_setting(MPSELARG.rate);
    readtname();

    AddMpatSelect(testarg, pcadd, &pat_i);
    UTL_StartTimer(UT_TIMER_R1US);

    FailCaptureSelect();
    ConfigFcm();

    g_fcth=UTL_GetFctHandle();
    MeasFct_MpatSelect(MPSELARG.pind, MPSELARG.pind, UT_ON);
//  UTL_SetFctMpatDataFileNameWithMpatSelector (g_fcth, "cflg1.mpa", "A"           );
//  UTL_SetFctStartLabelNameOfMpatSelector     (g_fcth, "cflg1.mpa", "A"            );

//  UTL_SetFctMpatTransferDataInhibit          (g_fcth, UT_MPAT_INH_REGISTER, UT_OFF);
//  UTL_SetFctFailInhibit                      (g_fcth, UT_ON);
//  UTL_MeasFct                                (g_fcth                         );
//  UTL_DeleteHandle                           (g_fcth);

    readPfc(0);

    for(i=0; i<16; i++) {
       cflg = (1<<i);
       idx1=i;
       UTL_WriteRegUs_Lite (UT_REG_STAPC, &pcadd[i],sizeof(pcadd[i]));
       UTL_WriteRegUs_Lite (UT_REG_IDX1,  &idx1,    sizeof(idx1));
       UTL_WriteRegUs_Lite (UT_REG_CFLG,  &cflg,    sizeof(cflg));


       StartAlpg();
       readPfc(i+1);
//     printf("XB=%d\n", UTL_ReadUSRegister(UT_REG_YB, 1)); fflush(stdout);
    }

}


void mpsel_loop(TEST_testitem *testarg)
{
    USlider pcadd[16];
    int pat_i = -1;   //Index for initial pattern program   

    UTL_StartTimer(UT_TIMER_R1US);
    init(MPSELARG.ilmode, MPSELARG.vterm);
    timing_setting(MPSELARG.rate);
    readtname();

    AddMpatSelect(testarg, pcadd, &pat_i);
    UTL_StartTimer(UT_TIMER_R1US);

    FailCaptureSelect();
    ConfigFcm();

    int exp[9]={ 16, 256, 384,1025, 384, 384, 384, 3, 2297};
    g_fcth=UTL_GetFctHandle();
    UTL_SetFctMpatDataFileNameWithMpatSelector (g_fcth, "pat_loopidxi1.mpa", "A");
    UTL_SetFctStartLabelNameOfMpatSelector     (g_fcth, "pat_loopidxi1.mpa", "A");
    UTL_SetFctMpatTransferDataInhibit          (g_fcth, UT_MPAT_INH_REGISTER, UT_OFF);
    UTL_SetFctFailInhibit                      (g_fcth, UT_ON);
    UTL_MeasFct                                (g_fcth);
//  UTL_DeleteHandle                           (g_fcth);

    readPfc(exp[0]);
    int i;

    for(i=1;i<=8;i++)
    {
       UTL_WriteRegUs_Lite (UT_REG_STAPC, &pcadd[i],sizeof(pcadd[i]));
//     printf("[%d] PC=#%04x\n",i, pcadd[i]); fflush(stdout);

       if(i==3 || i==7)
       {
           USlider idx8 = 0x3FE;
           USlider idx9 = 0x2;
           UTL_WriteRegUs_Lite                 (UT_REG_IDX8, &idx8,sizeof(idx8));
           UTL_WriteRegUs_Lite                 (UT_REG_IDX9, &idx9,sizeof(idx9));
       }
       else
       {
           RadioButton idx_type[]={ UT_REG_IDX1, UT_REG_IDX2, UT_REG_IDX3, UT_REG_IDX4,
                                    UT_REG_IDX5, UT_REG_IDX6, UT_REG_IDX7, UT_REG_IDX8,
                                    UT_REG_IDX9, UT_REG_IDX10,UT_REG_IDX11,UT_REG_IDX12,
                                    UT_REG_IDX13,UT_REG_IDX14,UT_REG_IDX15,UT_REG_IDX16};
           USlider     idx_val[]= { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2};
           int j;

           for(j=0; j<16; j++) UTL_WriteRegUs_Lite (idx_type[j], &(idx_val[j]), sizeof(USlider));
       }
       if(i !=8) StartAlpg();
       else {
           UTL_SetFctMpatDataFileNameWithMpatSelector (g_fcth, "pat_loopidxi1.mpa", "A");
           UTL_SetFctStartLabelNameOfMpatSelector     (g_fcth, "pat_loopdec1.mpa", "E");
           UTL_SetFctMpatTransferDataInhibit          (g_fcth, UT_MPAT_INH_REGISTER, UT_OFF);
           UTL_SetFctFailInhibit                      (g_fcth, UT_ON);
           UTL_MeasFct                                (g_fcth);
           UTL_DeleteHandle                           (g_fcth);
       }
       readPfc(exp[i]);

//     printf("i=%d pcadd=#%x\n",i, pcadd[i]);fflush(stdout);
    }
//  dut_test_result(testarg->testname);
}

void mpsel_subr(TEST_testitem *testarg)
{
    USlider pcadd[16];
    int i;
    const USlider idx[8]={ 0x0FE, 0x7FE, 0x6FE, 0x5FE, 0x4FE, 0x3FE, 0x2FE, 0x1FE};
    const int     exp[8]={   255,  2047,  1791,  1535,  1279,  1023,   767,   511};
    int pat_i = -1;   //Index for initial pattern program   

    UTL_StartTimer(UT_TIMER_R1US);
    init(MPSELARG.ilmode, MPSELARG.vterm);
    timing_setting(MPSELARG.rate);
    readtname();

    AddMpatSelect(testarg, pcadd, &pat_i);
    UTL_StartTimer(UT_TIMER_R1US);

    FailCaptureSelect();
    ConfigFcm();

    g_fcth = UTL_GetFctHandle();
    MeasFct_MpatSelect(MPSELARG.pind,MPSELARG.pind,UT_ON);
    UTL_DeleteHandle(g_fcth);
    readPfc(2);

    for(i=0;i<=7;i++)
    {
        USlider pc = pcadd[i];

        UTL_WriteRegUs_Lite(UT_REG_STAPC,&pcadd[i], sizeof(USlider));
        UTL_WriteRegUs_Lite(UT_REG_IDX1, &idx[i],   sizeof(USlider));

        StartAlpg();
        readPfc(exp[i]);
    }    

//  dut_test_result(testarg->testname);
}

void mpsel_wait(TEST_testitem *testarg)
{
    USlider pcadd[16], val;
    int i;
    const USlider idx[8]={ 0x0FD, 0x7FD, 0x6FD, 0x5FD, 0x4FD, 0x3FD, 0x2FD, 0x1FD};
    const int     exp[8]={   255,  2047,  1791,  1535,  1279,  1023,   767,   511};
    int pat_i = -1;   //Index for initial pattern program   

    UTL_StartTimer(UT_TIMER_R1US);
    init(MPSELARG.ilmode, MPSELARG.vterm);
    timing_setting(MPSELARG.rate);
    readtname();

    AddMpatSelect(testarg, pcadd, &pat_i);
    UTL_StartTimer(UT_TIMER_R1US);

    FailCaptureSelect();
    ConfigFcm();

    for(i=0;i<=7;i++)
    {
       g_fcth = UTL_GetFctHandle();

       MeasFct_MpatSelect(MPSELARG.pind+i, MPSELARG.pind, UT_ON);
       readPfc(exp[i]);
       ReadPc(MPSELARG.exp_p,i);

       UTL_SetFctContinue              (g_fcth, UT_ON);
       UTL_StartFct                    (g_fcth);
       UTL_DeleteHandle                (g_fcth);

       ReadPc(MPSELARG.exp_p+1,i);
    }
//  dut_test_result(testarg->testname);
}

void mpsel_calm(TEST_testitem *testarg)
{

    USlider pcadd[16];
    int pat_i = -1;   //Index for initial pattern program   

    UTL_StartTimer(UT_TIMER_R1US);
    init(MPSELARG.ilmode, MPSELARG.vterm);
    timing_setting(MPSELARG.rate);
    readtname();

    AddMpatSelect(testarg, pcadd, &pat_i);
    UTL_StartTimer(UT_TIMER_R1US);

    FailCaptureSelect();
    ConfigFcm();

    g_fcth=UTL_GetFctHandle();
    UTL_SetFctMpatDataFileNameWithMpatSelector(g_fcth, "pat_calm1.mpa", "A");
    UTL_SetFctStartLabelNameOfMpatSelector    (g_fcth, "pat_calm1.mpa", "I");
    UTL_StartFct                              (g_fcth);
    UTL_DeleteHandle                          (g_fcth);

    int exp[8];
    exp[0]=255;
    exp[1]=2047;
    exp[2]=1791;
    exp[3]=1535;
    exp[4]=1279;
    exp[5]=1023;
    exp[6]=767;
    exp[7]=511;

//  int exppc[8];
//  exppc[0]=0x02;
//  exppc[1]=0x05;
//  exppc[2]=0x08;
//  exppc[3]=0x0b;
//  exppc[4]=0x0e;
//  exppc[5]=0x11;
//  exppc[6]=0x14;
//  exppc[7]=0x17;

//  int exppc2[8];
//  exppc2[0]=0x1a;
//  exppc2[1]=0x1f;
//  exppc2[2]=0x24;
//  exppc2[3]=0x29;
//  exppc2[4]=0x2e;
//  exppc2[5]=0x33;
//  exppc2[6]=0x38;
//  exppc2[7]=0x3d;
    int i;
    for (i=0; i<=7; i++)
    {
        g_fcth=UTL_GetFctHandle();

        StartFct_MpatSelect(MPSELARG.pind+i, MPSELARG.pind, UT_ON);
        if(UTL_ReadAlpgStatusFlag()==UT_ALPG_STATUS_RUNNING)
        {
            ReadPc(8, i);
        }
        UTL_WriteAlpgCtrlReg (UT_REG_CONTINUE_FLAG, 1);
        UTL_SetFctContinue   (g_fcth, UT_ON);
        UTL_StartFct         (g_fcth);

        UTL_DeleteHandle     (g_fcth);

        printf("JCZ Time= %9.3f[uS]\n",ReadUSReg (UT_REG_XB) * 2.857e-9 * 1e6);
        ReadPc    (9,i);
        readPfc(exp[i]);
    }
}


struct timespec tm[13];

void TmStartFct()
{
    int i;
    g_fcth=UTL_GetFctHandle();
//  UTL_SetFctMpatDataFileNameWithMpatSelector(g_fcth, "pat_stps.mpa", "SNGL");
    UTL_SetFctStartLabelNameOfMpatSelector    (g_fcth, "pat_stps.mpa", "SNGL");
    UTL_SetFctMpatTransferDataInhibit         (g_fcth, UT_MPAT_INH_REGISTER,UT_ON);
    UTL_SetFctSronInhibit                     (g_fcth, UT_ON);

    UTL_SetWet();
    UTL_OnPowerSeq();

    clock_gettime (CLOCK_REALTIME,&tm[0]);
    UTL_StartFct                              (g_fcth);
    clock_gettime (CLOCK_REALTIME,&tm[1]);
    UTL_SetFctMpatTransferInhibit             (g_fcth, UT_ON);

    clock_gettime (CLOCK_REALTIME,&tm[2]);
    for(i=0; i<10; i++)
       UTL_StartFct                              (g_fcth);
    clock_gettime (CLOCK_REALTIME,&tm[3]);

    UTL_DeleteHandle                          (g_fcth);
}

void TmMeasFct()
{
    int i;
    g_fcth=UTL_GetFctHandle();
//  UTL_SetFctMpatDataFileNameWithMpatSelector(g_fcth, "pat_stps.mpa", "SNGL");
    UTL_SetFctStartLabelNameOfMpatSelector    (g_fcth, "pat_stps.mpa", "SNGL");
    UTL_SetFctMpatTransferDataInhibit         (g_fcth, UT_MPAT_INH_REGISTER,UT_ON);
    UTL_SetFctSronInhibit                     (g_fcth, UT_ON);

    UTL_SetWet();
    UTL_OnPowerSeq();

    clock_gettime (CLOCK_REALTIME,&tm[0]);
    UTL_MeasFct                               (g_fcth);
    clock_gettime (CLOCK_REALTIME,&tm[1]);
    UTL_SetFctMpatTransferInhibit             (g_fcth, UT_ON);

    clock_gettime (CLOCK_REALTIME,&tm[2]);
    for(i=0; i<10; i++)
       UTL_MeasFct                            (g_fcth);
    clock_gettime (CLOCK_REALTIME,&tm[3]);

    UTL_DeleteHandle                          (g_fcth);
}

void JudgeTime(int fcttype, int dummy)
{
    struct timespec ave;
    int fail=0;
    UT_DUT dut;

    ave.tv_sec  = (tm[3].tv_sec -tm[2].tv_sec)/10;
    ave.tv_nsec = (tm[3].tv_nsec-tm[2].tv_nsec)/10;

    printf("1st Exec Time = %2ld.%09ld\n", tm[1].tv_sec-tm[0].tv_sec,tm[1].tv_nsec-tm[0].tv_nsec);
    printf("10 times Average Exec Time = %2ld.%09ld\n",ave.tv_sec, ave.tv_nsec);

    if (ave.tv_sec  > 0) fail=1; 
    else if (fcttype == 0) {  //MeasFct
       if(ave.tv_nsec > 920000) fail = 1;
    }
    else {  //StartFct
       if(ave.tv_nsec > 650000) fail = 1;
    }
    DutCursor dutc = UTL_GetDutCursor(UT_SDUT);
    char *testname = UTL_ReadTestName();

    if(fail) {
       while((dut=UTL_NextDut(dutc)) != UT_NOMORE){
          UTL_SetTestResult  (dut, testname, UT_RES_ALL);
       }
    }
    else {
       while((dut=UTL_NextDut(dutc)) != UT_NOMORE){
          UTL_ResetTestResult  (dut, testname, UT_RES_ALL);
       }
    }
    UTL_DeleteCursor(dutc);
}

void mpsel_measfct(TEST_testitem *testarg)
{
    unsigned int pcadd[2];
    int pat_i = -1;   //Index for initial pattern program   

    init(MPSELARG.ilmode, MPSELARG.vterm);
    timing_setting(MPSELARG.rate);
    readtname();
    
//  FailCaptureSelect(MPSELARG.dutgrp);

    AddMpatSelect(testarg, pcadd, &pat_i);

    MPSELARG.pg_run();

	MPSELARG.post2(0,0);

    test_result(testarg->testname);
}

void mpsel_startfct(TEST_testitem *testarg)
{
    unsigned int pcadd[2];
    int pat_i = -1;   //Index for initial pattern program   

    init(MPSELARG.ilmode, MPSELARG.vterm);
    timing_setting(MPSELARG.rate);
    readtname();
    
//  FailCaptureSelect(MPSELARG.dutgrp);

    AddMpatSelect(testarg, pcadd, &pat_i);

    MPSELARG.pg_run();

	MPSELARG.post2(1,0);

    test_result(testarg->testname);

}

void mpsel_debug(TEST_testitem *testarg)
{
    unsigned int pcadd[16];
    USlider pcr;
    int pat_i = -1;   //Index for initial pattern program   

    init(MPSELARG.ilmode, MPSELARG.vterm);    //Make match cycles failed
    timing_setting(MPSELARG.rate);
    readtname();

    AddMpatSelect(testarg, pcadd, &pat_i);

    UTL_StartTimer(UT_TIMER_R1US);

    g_fcth=UTL_GetFctHandle();

    int i=0;
    //REG MPAT PC & SEND MPAT
    UTL_SetFctStartLabelNameOfMpatSelector      (g_fcth, patnpc[MPSELARG.pind][0],patnpc[MPSELARG.pind][1]);
    //SEND REGISTER VALUES
    UTL_SetFctMpatDataFileNameWithMpatSelector  (g_fcth, patnpc[MPSELARG.pind][0],patnpc[MPSELARG.pind][1]);
    printf("pat=%s  pc=%s\n",patnpc[MPSELARG.pind][0],patnpc[MPSELARG.pind][1]);

    UTL_MeasFct				        (g_fcth	);

    MPSELARG.post2(MPSELARG.exp_p,i);

    //REG MPAT PC & SEND MPAT
    UTL_SetFctStartLabelNameOfMpatSelector      (g_fcth, patnpc[MPSELARG.pind+1][0],patnpc[MPSELARG.pind+1][1]);
    //SEND REGISTER VALUES
    UTL_SetFctMpatDataFileNameWithMpatSelector  (g_fcth, patnpc[MPSELARG.pind+1][0],patnpc[MPSELARG.pind+1][1]);
    UTL_MeasFct				        (g_fcth	);

    MPSELARG.post2(MPSELARG.exp_p,1);
    UTL_DeleteHandle(g_fcth);
}
