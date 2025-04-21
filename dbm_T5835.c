#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include "test.h"
#include "test_struct.h"
#include "dbm.h"

#define DBMSIZE (0x10000000)	//256Mw
#define BUFSIZE (0x20000)	//128Kw
#define SQTABLESIZE (4096)	//SequenceTableSize
#define DATRMCOUNT (0x400)	//DCM
#define CBITS (3)	//C0,C1,C2
#define DEBUG (1)	//0:Not Debug Mode, 1<:Debug Mode

static void pin_condition_pbfree(TEST_testitem *testarg);
static void pin_condition_diagpb(TEST_testitem *testarg);
static void pin_condition_YMTC(TEST_testitem *testarg);
static void level_setting( int channel, double high, double low);
static void timing_setting(TEST_testitem *testarg);
static void meas_fct(TEST_testitem *testarg);
static void set_memory_module_dbm();
static void reset_dbm_memory();
static void dbm_setting(TEST_testitem *testarg);
static void reg_setting(TEST_testitem *testarg);
static void reg_setting_YMTC(TEST_testitem *testarg);
static void write_dbm(TEST_testitem *testarg);
static void write_dbm_sq(TEST_testitem *testarg, USlider *sqtable);
static int  read_dbm(TEST_testitem *testarg);
static void set_burst_scram(TEST_testitem *testarg);
static void display(TEST_testitem *testarg, int result);
static int is_diagsocket();

static int is_diagsocket(){
  int val = 0;
  if(strlen(UTL_ReadSocketProgramName())!=0){
    if(strstr(strrchr(UTL_ReadSocketProgramName(),'/'),"_diag")!=NULL){ //diagpb
      val = 1;
    }
  }
  return(val);
}

static void timing_setting(TEST_testitem *testarg)
{
  DSlider tck = DBMARG.rate;

  set_ilmode(DBMARG.ilmode);

  TgHandle tg_h = UTL_GetTgHandle();
  UTL_AddTgRate(tg_h, 1, tck );
  UTL_AddTgBclk(tg_h, 1, 1, tck*0.00);
  UTL_AddTgCclk(tg_h, 1, 1, tck*0.50);
  UTL_AddTgDreL(tg_h, 1, 1, tck*0.00);
  UTL_AddTgDreT(tg_h, 1, 1, tck*0.00);
  UTL_AddTgStrb(tg_h, 1, 1, tck*0.25);
  UTL_AddTgStrb(tg_h, 1, 2, tck*0.75);
  UTL_SendTg(tg_h);
  UTL_DeleteHandle(tg_h);
}

static void pin_condition_YMTC(TEST_testitem *testarg)
{
  int i, j;

  PinHandle pf_h = UTL_GetPinHandle();
  UTL_InitializePinHandle(pf_h);

  UTL_SetPinModeDreDelay(pf_h, UT_DELAY_CYCLE, 0);
  UTL_SetPinModeDrDelay (pf_h, UT_DELAY_CYCLE, 0);
  UTL_SetPinModeCpeDelay(pf_h, UT_DELAY_CYCLE, 0);
  UTL_SetPinModeExpDelay(pf_h, UT_DELAY_CYCLE, 0);

  if(DBMARG.ddrmode==UT_OFF){
    UTL_SetPinDrWaveform(pf_h, UT_WAV_NRZB);
  }
  else{
    UTL_SetPinDrWaveform(pf_h, UT_WAV_DNRZ);
  }
  UTL_SetPinDrClock(pf_h, UT_PIN_BCLK, 1);
  UTL_SetPinDrClock(pf_h, UT_PIN_CCLK, 1);
  UTL_SetPinViNumber(pf_h, 1); 
  UTL_SetPinVoNumber(pf_h, 1);
  UTL_SetPinVtNumber(pf_h, 1);
  UTL_SetPinIoCtrl(pf_h, UT_ON);
  UTL_SetPinTerm(pf_h, UT_ON);
  UTL_SetPinDreWaveform(pf_h, UT_DREWAV_NRZ);
  UTL_SetPinDreClock(pf_h, 1);

  UTL_ClearPinExpStrbNumber(pf_h);
  UTL_AddPinExpStrbNumber(pf_h, 1, UT_PIN_EXP_A);
  if(DBMARG.ddrmode==UT_ON){
     UTL_AddPinExpStrbNumber (pf_h, 2, UT_PIN_EXP_B);
  }

  //Block0,2 DR/TP
  UTL_ClearPinPdsA(pf_h);
  UTL_ClearPinPdsB(pf_h);
  for(i=0; i<SOCKET.dutblock_iopin_count[0]; i++){
    if(i<DBMARG.bitsize){
      UTL_AddPinPdsA(pf_h, i<CBITS ? UT_SIG_C(i) : UT_SIG_X(i-CBITS)	, 10); //for bit8 DDR
      UTL_AddPinPdsB(pf_h, UT_SIG_X(i-CBITS+8)				, 10);
      UTL_AddPinPdsA(pf_h, UT_SIG_Y(i)					, 11);
      UTL_AddPinPdsB(pf_h, UT_SIG_Y(i+8)				, 11);
    }
    else{
      for(j=1; j<=11; j++){
        UTL_AddPinPdsA(pf_h, UT_SIG_FL, j);
        UTL_AddPinPdsB(pf_h, UT_SIG_FL, j);
      }
    }
  }

  UTL_SetPinDreNumber(pf_h, 1);
  UTL_ClearPinStrbCpeNumber(pf_h);
  UTL_AddPinStrbCpeNumber(pf_h, 1, 2);//dummy CPE2
  if(DBMARG.ddrmode==UT_ON){
     UTL_AddPinStrbCpeNumber (pf_h, 2, 2);//dummy CPE2
  }
  UTL_SendPin(pf_h, SOCKET.dutblock_iopinlist[0]);
  UTL_SendPin(pf_h, SOCKET.dutblock_iopinlist[2]);

  //Block1,3 CP/DBM
  UTL_ClearPinPdsA(pf_h);
  UTL_ClearPinPdsB(pf_h);
  for(i=0; i<SOCKET.dutblock_iopin_count[0]; i++){
    if(i<DBMARG.bitsize){
      UTL_AddPinPdsA(pf_h, UT_SIG_PPAT_A, 10);
      UTL_AddPinPdsB(pf_h, UT_SIG_PPAT_B, 10);
      UTL_AddPinPdsA(pf_h, UT_SIG_PPAT_A, 11);
      UTL_AddPinPdsB(pf_h, UT_SIG_PPAT_B, 11);
    }
    else{
      for(j=1; j<=11; j++){
        UTL_AddPinPdsA(pf_h, UT_SIG_FL, j);
        UTL_AddPinPdsB(pf_h, UT_SIG_FL, j);
      }
    }
  }

  UTL_SetPinDreNumber(pf_h, 2);//dummy DRE2
  UTL_ClearPinStrbCpeNumber(pf_h);
  UTL_AddPinStrbCpeNumber(pf_h, 1, 1);
  if(DBMARG.ddrmode==UT_ON){
     UTL_AddPinStrbCpeNumber (pf_h, 2, 1);
  }
  UTL_SendPin(pf_h, SOCKET.dutblock_iopinlist[1]);
  UTL_SendPin(pf_h, SOCKET.dutblock_iopinlist[3]);

  UTL_DeleteHandle(pf_h); 

  return;
}

static void pin_condition_diagpb(TEST_testitem *testarg)
{
  PinHandle pf_h = UTL_GetPinHandle();
  UTL_InitializePinHandle(pf_h);

  int i, j;
  UTL_ClearPinPdsA(pf_h);
  UTL_ClearPinPdsB(pf_h);
  for(i=0; i<SOCKET.dutblock_iopin_count[0]; i++){
    if(i<DBMARG.bitsize){
      UTL_AddPinPdsA(pf_h, i<CBITS ? UT_SIG_C(i) : UT_SIG_X(i-CBITS)	, 1); //for bit16 SDR
      UTL_AddPinPdsB(pf_h, UT_SIG_FL					, 1);
      UTL_AddPinPdsA(pf_h, UT_SIG_Y(i)					, 2);
      UTL_AddPinPdsB(pf_h, UT_SIG_FL					, 2);

      UTL_AddPinPdsA(pf_h, i<CBITS ? UT_SIG_C(i) : UT_SIG_X(i-CBITS)	, 3); //for bit16 DDR
      UTL_AddPinPdsB(pf_h, UT_SIG_Y(i)					, 3);

      UTL_AddPinPdsA(pf_h, i<CBITS ? UT_SIG_C(i) : UT_SIG_X(i-CBITS)	, 4); //for bit8 SDR
      UTL_AddPinPdsB(pf_h, UT_SIG_FL					, 4);
      UTL_AddPinPdsA(pf_h, UT_SIG_X(i-CBITS+8)				, 5);
      UTL_AddPinPdsB(pf_h, UT_SIG_FL					, 5);
      UTL_AddPinPdsA(pf_h, UT_SIG_Y(i)					, 6);
      UTL_AddPinPdsB(pf_h, UT_SIG_FL					, 6);
      UTL_AddPinPdsA(pf_h, UT_SIG_Y(i+8)				, 7);
      UTL_AddPinPdsB(pf_h, UT_SIG_FL					, 7);

      UTL_AddPinPdsA(pf_h, i<CBITS ? UT_SIG_C(i) : UT_SIG_X(i-CBITS)	, 8); //for bit8 DDR
      UTL_AddPinPdsB(pf_h, UT_SIG_X(i-CBITS+8)				, 8);
      UTL_AddPinPdsA(pf_h, UT_SIG_Y(i)					, 9);
      UTL_AddPinPdsB(pf_h, UT_SIG_Y(i+8)				, 9);

      UTL_AddPinPdsA(pf_h, UT_SIG_PPAT_A, 10);
      UTL_AddPinPdsB(pf_h, UT_SIG_PPAT_B, 10);
    }
    else{
      for(j=1; j<=10; j++){
        UTL_AddPinPdsA(pf_h, UT_SIG_FL, j);
        UTL_AddPinPdsB(pf_h, UT_SIG_FL, j);
      }
    }
  }

  UTL_SetPinModeDreDelay(pf_h, UT_DELAY_CYCLE, 0);
  UTL_SetPinModeDrDelay (pf_h, UT_DELAY_CYCLE, 0);
  UTL_SetPinModeCpeDelay(pf_h, UT_DELAY_CYCLE, 8);
  UTL_SetPinModeExpDelay(pf_h, UT_DELAY_CYCLE, 8);

  if(DBMARG.ddrmode==UT_OFF){
    UTL_SetPinDrWaveform(pf_h, UT_WAV_NRZB);
  }
  else{
    UTL_SetPinDrWaveform(pf_h, UT_WAV_DNRZ);
  }
  UTL_SetPinDrClock(pf_h, UT_PIN_BCLK, 1);
  UTL_SetPinDrClock(pf_h, UT_PIN_CCLK, 1);
  UTL_SetPinViNumber(pf_h, 1); 
  UTL_SetPinVoNumber(pf_h, 1);
  UTL_SetPinVtNumber(pf_h, 1);
  UTL_SetPinIoCtrl(pf_h, UT_ON);
  UTL_SetPinTerm(pf_h, UT_ON);
  UTL_SetPinDreWaveform(pf_h, UT_DREWAV_NRZ);
  UTL_SetPinDreClock(pf_h, 1);

  UTL_ClearPinExpStrbNumber(pf_h);
  UTL_AddPinExpStrbNumber(pf_h, 1, UT_PIN_EXP_A);
  if(DBMARG.ddrmode==UT_ON){
     UTL_AddPinExpStrbNumber (pf_h, 2, UT_PIN_EXP_B);
  }

  UTL_SetPinDreNumber(pf_h, 1);
  UTL_ClearPinStrbCpeNumber(pf_h);
  UTL_AddPinStrbCpeNumber(pf_h, 1, 2);//dummy CPE2
  if(DBMARG.ddrmode==UT_ON){
     UTL_AddPinStrbCpeNumber (pf_h, 2, 2);//dummy CPE2
  }
  UTL_SendPin(pf_h, SOCKET.dutblock_iopinlist[0]);
  UTL_SendPin(pf_h, SOCKET.dutblock_iopinlist[2]);

  UTL_SetPinDreNumber(pf_h, 2);//dummy DRE2
  UTL_ClearPinStrbCpeNumber(pf_h);
  UTL_AddPinStrbCpeNumber(pf_h, 1, 1);
  if(DBMARG.ddrmode==UT_ON){
     UTL_AddPinStrbCpeNumber (pf_h, 2, 1);
  }
  UTL_SendPin(pf_h, SOCKET.dutblock_iopinlist[1]);
  UTL_SendPin(pf_h, SOCKET.dutblock_iopinlist[3]);

  UTL_DeleteHandle(pf_h); 

  return;
}

static void pin_condition_pbfree(TEST_testitem *testarg)
{
  PinHandle pf_h = UTL_GetPinHandle();
  UTL_InitializePinHandle(pf_h);

  UTL_SetPinViNumber(pf_h, 1); 

  if(DBMARG.ddrmode==UT_OFF){
    UTL_SetPinDrWaveform(pf_h, UT_WAV_NRZB);
  }
  else{
    UTL_SetPinDrWaveform(pf_h, UT_WAV_DNRZ);
  }
  UTL_SetPinDrClock(pf_h, UT_PIN_BCLK, 1);
  UTL_SetPinDrClock(pf_h, UT_PIN_CCLK, 1);

  UTL_SetPinVoNumber(pf_h, 1);
  UTL_SetPinVtNumber(pf_h, 1);
  UTL_SetPinIoCtrl(pf_h, UT_ON);
  UTL_SetPinTerm(pf_h, UT_ON);
  UTL_SetPinDreNumber(pf_h, 1);
  UTL_SetPinDreWaveform(pf_h, UT_DREWAV_NRZ);
  UTL_SetPinDreClock(pf_h, 1);
  UTL_AddPinStrbCpeNumber(pf_h, 1, 1);
  UTL_AddPinExpStrbNumber(pf_h, 1, UT_PIN_EXP_A);
  if(DBMARG.ddrmode==UT_ON){
     UTL_AddPinStrbCpeNumber (pf_h, 2, 1);
     UTL_AddPinExpStrbNumber (pf_h, 2, UT_PIN_EXP_B);
  }
  UTL_SetPinModeDreDelay(pf_h, UT_DELAY_CYCLE, 0);
  UTL_SetPinModeDrDelay (pf_h, UT_DELAY_CYCLE, 0);
  UTL_SetPinModeCpeDelay(pf_h, UT_DELAY_CYCLE, 8);
  UTL_SetPinModeExpDelay(pf_h, UT_DELAY_CYCLE, 8);

  int dutblock;
  int i, j;
  for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
    UTL_ClearPinPdsA(pf_h);
    UTL_ClearPinPdsB(pf_h);
    for(i=0; i<SOCKET.dutblock_iopin_count[dutblock]; i++){
      if(i<DBMARG.bitsize){
        UTL_AddPinPdsA(pf_h, i<CBITS ? UT_SIG_C(i) : UT_SIG_X(i-CBITS)	, 1); //for bit16 SDR
        UTL_AddPinPdsB(pf_h, UT_SIG_FL					, 1);
        UTL_AddPinPdsA(pf_h, UT_SIG_Y(i)				, 2);
        UTL_AddPinPdsB(pf_h, UT_SIG_FL					, 2);
 
        UTL_AddPinPdsA(pf_h, i<CBITS ? UT_SIG_C(i) : UT_SIG_X(i-CBITS)	, 3); //for bit16 DDR
        UTL_AddPinPdsB(pf_h, UT_SIG_Y(i)				, 3);
 
        UTL_AddPinPdsA(pf_h, i<CBITS ? UT_SIG_C(i) : UT_SIG_X(i-CBITS)	, 4); //for bit8 SDR
        UTL_AddPinPdsB(pf_h, UT_SIG_FL					, 4);
        UTL_AddPinPdsA(pf_h, UT_SIG_X(i-CBITS+8)			, 5);
        UTL_AddPinPdsB(pf_h, UT_SIG_FL					, 5);
        UTL_AddPinPdsA(pf_h, UT_SIG_Y(i)				, 6);
        UTL_AddPinPdsB(pf_h, UT_SIG_FL					, 6);
        UTL_AddPinPdsA(pf_h, UT_SIG_Y(i+8)				, 7);
        UTL_AddPinPdsB(pf_h, UT_SIG_FL					, 7);
 
        UTL_AddPinPdsA(pf_h, i<CBITS ? UT_SIG_C(i) : UT_SIG_X(i-CBITS)	, 8); //for bit8 DDR
        UTL_AddPinPdsB(pf_h, UT_SIG_X(i-CBITS+8)			, 8);
        UTL_AddPinPdsA(pf_h, UT_SIG_Y(i)				, 9);
        UTL_AddPinPdsB(pf_h, UT_SIG_Y(i+8)				, 9);
 
        UTL_AddPinPdsA(pf_h, UT_SIG_PPAT_A, 10);
        UTL_AddPinPdsB(pf_h, UT_SIG_PPAT_B, 10);
      }
      else{
        for(j=1; j<=10; j++){
          UTL_AddPinPdsA(pf_h, UT_SIG_FL, j);
          UTL_AddPinPdsB(pf_h, UT_SIG_FL, j);
        }
      }
    }
    UTL_SendPin(pf_h, SOCKET.dutblock_iopinlist[dutblock]);
  }
  UTL_DeleteHandle(pf_h); 

  return;
}

static void level_setting(int channel , double high, double low)
{
  ViHandle vi_h = UTL_GetViHandle();
  UTL_SetViHigh(vi_h, high);     
  UTL_SetViLow(vi_h, low);     
  UTL_SetViHvDr(vi_h, UT_OFF);
  UTL_SendVi(vi_h, channel);

  VoHandle vo_h = UTL_GetVoHandle();
  UTL_SetVoHigh(vo_h, 0.5);
  UTL_SetVoLow(vo_h, 0.5);
  UTL_SendVo(vo_h, channel);

  VtHandle vt_h = UTL_GetVtHandle();
  UTL_SetVt(vt_h, 0.5);
  UTL_SendVt(vt_h, channel);

  UTL_DeleteHandle(vi_h);
  UTL_DeleteHandle(vo_h);
  UTL_DeleteHandle(vt_h);

  return;
}

static void set_burst_scram(TEST_testitem *testarg)
{
  BurstScramHandle bscrh;

  bscrh = UTL_GetBurstScramHandle();
  UTL_SetBurstScramMode(bscrh, UT_ON);
  UTL_SetBurstScramBaseFileName (bscrh, "");
  UTL_SetBurstScramDdrType(bscrh, 3);
  if(DBMARG.ddrmode==UT_OFF){
     UTL_SetBurstScramDataRate(bscrh, 1);
  }
  else{
     UTL_SetBurstScramDataRate(bscrh, 2);
  }
  UTL_SetBurstScramLength(bscrh, 8); 
  UTL_SetBurstScramWrapType(bscrh, 0); 
  UTL_AddBurstScramWriteSignal(bscrh, UT_SIG_WT); 
  UTL_SetBurstScramAddrUnit(bscrh, UT_UNIT_PDS, UT_ON); 
  UTL_SetBurstScramAddrUnit(bscrh, UT_UNIT_DFM, UT_ON); 
  UTL_SetBurstScramAddrUnit(bscrh, UT_UNIT_FP, UT_ON); 
  UTL_SendBurstScram(bscrh);
  UTL_DeleteHandle(bscrh);

  return;
}

static void meas_fct(TEST_testitem *testarg)
{
  double ttt;
  int ovf;

  FctHandle fct_h = UTL_GetFctHandle();
  PowerCtrlHandle pch;
  MpatHandle h;
  h = UTL_GetMpatHandle();
  pch = UTL_GetPowerCtrlHandle();

  UTL_AddPowerCtrlAll(pch);
  UTL_OnPowerCtrl(pch);

  if(is_diagsocket()){ //diagpb
    printf("ExecSbcal\n"); fflush(stdout);
    UTL_ExecSbcal("dbm", "NORMAL,NOPBLOCKCHK");
  }

  MpatHandle mph = UTL_GetMpatHandle();
  UTL_SetMpatFileName(mph, DBMARG.mpat);
  UTL_SetMpatStartPc(mph, DBMARG.pc);
  UTL_SendMpat(mph);
  UTL_DeleteHandle(mph);

  UTL_StartTimer(UT_TIMER_R1US);
  UTL_SetFctMpatName(fct_h, DBMARG.mpat);
  UTL_SetFctStartPc(fct_h, DBMARG.pc);
  UTL_SetFctFailInhibit(fct_h,UT_ON);
  UTL_MeasFct(fct_h);

  ttt=UTL_ReadTimer(&ovf);
  if(DEBUG>0){printf("MeasFct Time: %lf\n",ttt);fflush(stdout);}

  UTL_DeleteHandle(pch);
  UTL_DeleteHandle(fct_h);

  return;
}

static void set_memory_module_dbm(void)
{
  MemoryModuleHandle mmh =UTL_GetMemoryModuleHandle();
  UTL_AddMemoryModulePurpose(mmh, UT_MEM_FCM, 3);
  UTL_AddMemoryModulePurpose(mmh, UT_MEM_DBM, 1);
  UTL_SendMemoryModule(mmh);
  UTL_DeleteHandle(mmh);
}

static void reset_dbm_memory(void) 
{
  DbmAccessHandle rdh = UTL_GetDbmAccessHandle();
  UTL_SetDbmAccessUnitNumber(rdh, 1);
  UTL_SetDbmAccessAllUnit(rdh, UT_ON);
  UTL_SetDbmAccessAllBlock(rdh, UT_ON);
  UTL_SetDbmAccessStartAddr(rdh, 0x0);
  UTL_SetDbmAccessStopAddr(rdh, DBMSIZE-1);
  UTL_SetDbmAccessDataKind(rdh, UT_DBM_PPAT);
  UTL_ResetDbm(rdh);
  UTL_DeleteHandle(rdh);
}   

static void dbm_setting(TEST_testitem *testarg)
{
  PinCursor pc,pcr;
  UT_PIN pin;
  int i, j;
  USlider sqtable[SQTABLESIZE] = {0};

  DbmConfigHandle dch = UTL_GetDbmConfigHandle();
  UTL_SetDbmConfigAccessMode(dch, DBMARG.dbmmode);
  if(DBMARG.dbmmode==UT_DBM_ACCESS_TABLE_DBMXFER || DBMARG.dbmmode==UT_DBM_ACCESS_TABLE_AUTOXFER || DBMARG.dcm==UT_ON){
    int sqmax = DBMARG.checksize/BUFSIZE;
    if(DEBUG>0){printf("sqnum\t\t: %d\n", sqmax);}
    for(i=0; i<sqmax; i++){
      sqtable[i] = i;
    }
    srand((unsigned int)time(NULL));
    int swap;
    for(i=0; i<sqmax; i++){
      j = rand()%sqmax;
      swap = sqtable[j];
      sqtable[j] = sqtable[i];
      sqtable[i] = swap;
    }
    if(DEBUG>0){
      printf("sqtable =");
      for(i=0; i<sqmax; i++){
        printf(" %d", sqtable[i]);
      }
      printf("\n");
    }

    if(DBMARG.dcm==UT_ON){ //DCM
      uint64_t dcmdata[DATRMCOUNT] = {0};
      for(i=0; i<DATRMCOUNT; i++){
        dcmdata[i] = sqtable[i];
      }

      printf("dcm\t\t: 0x0-0x%x\n", sqmax-1);
      RegMemoryHandle dcmh = UTL_GetRegMemoryHandle();
      UTL_SetRegMemoryTarget(dcmh, UT_REGMEMORY_DATRM);
      UTL_SetRegMemoryStartAddr(dcmh, 0x0);
      UTL_SetRegMemoryStopAddr(dcmh, sqmax-1);
      UTL_WriteRegMemory(dcmh, dcmdata, sqmax*sizeof(uint64_t));
      UTL_DeleteHandle(dcmh);
    }
    else{ //SQTABLE
      UTL_SetDbmConfigSequenceTable(dch, sqtable, sqmax*sizeof(USlider));
    }
  }

  UTL_SetDbmConfigBitSize(dch, DBMARG.bitsize);
  UTL_SetDbmConfigBitAssignMode(dch, DBMARG.bitmode);
  UTL_ClearDbmConfigPinAssign(dch);
  int dutblock;
  for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
    for(i=0; i<SOCKET.dutblock_iopin_count[dutblock]; i++){
      if(i<DBMARG.bitsize){
        if(DEBUG>1){printf("Set: bit:%d, pin:%d\n", i, SOCKET.dutblock_iopin[dutblock][i]); fflush(stdout);}
        UTL_AddDbmConfigPinAssign(dch, i, SOCKET.dutblock_iopin[dutblock][i]);
      }
    }
  }
  UTL_SendDbmConfig(dch);
  UTL_DeleteHandle(dch);

  if(DBMARG.dbmmode==UT_DBM_ACCESS_TABLE_DBMXFER || DBMARG.dbmmode==UT_DBM_ACCESS_TABLE_AUTOXFER || DBMARG.dcm==UT_ON){
    write_dbm_sq(testarg, sqtable);
  }
  else if(DBMARG.dbmmode==UT_DBM_ACCESS_AP || DBMARG.dbmmode==UT_DBM_ACCESS_AP_AUTOXFER){
    write_dbm(testarg);
  }
  else{
    printf("DBM mode error.\n");
    exit(1);
  }

  return;
}

static void reg_setting_YMTC(TEST_testitem *testarg)
{
  RegHandle regh;
  regh = UTL_GetRegHandle();

  USlider xmax = (0x1<<(16-CBITS))-1;
  USlider ymax = (DBMSIZE>>16)-1;
  UTL_SetRegUs(regh, UT_REG_XMAX, 1, xmax);
  UTL_SetRegUs(regh, UT_REG_LMAX, 1, xmax);
  UTL_SetRegUs(regh, UT_REG_YMAX, 1, ymax);
  UTL_SetRegUs(regh, UT_REG_HMAX, 1, ymax);

  double r2r = 7.68e-6; //7.68e-6=ave2400Mbps, 6.6e-6=ave2792Mbps // read-to-read cycle time
  USlider idx1 = 1024*18/2/DBMARG.ilmode/2-2;	// 18k(1page), DDR for PC#000
  //USlider idx1 = 1024*18/2/DBMARG.ilmode/2*1024*8-2;	// 18k*8kpage, DDR for PC#100
  USlider idx2 = 1024*8-2;			// 8k page
  USlider idx3 = ((r2r-((idx1+2)*2*DBMARG.ilmode*DBMARG.rate))/DBMARG.ilmode/DBMARG.rate)-2-1; // wait

  printf("tg_rate\t= %e\n", DBMARG.rate);
  printf("bit_rate\t= %dMbps\n", (int)(2.0/DBMARG.rate/1e6));
  printf("ave_rate\t= %dMbps\n", (int)(1024*18/r2r/1e6));
  printf("wait_idx\t= %d\n", idx3);
  printf("r2r\t= %e\n", r2r);
  printf("rtime\t= %e\n", (idx1+2)*2*DBMARG.ilmode*DBMARG.rate);
  printf("wait\t= %e\n", (idx3+2+1)*DBMARG.ilmode*DBMARG.rate);

  UTL_SetRegUs(regh, UT_REG_IDX1, 1, idx1);
  UTL_SetRegUs(regh, UT_REG_IDX2, 1, idx2);
  UTL_SetRegUs(regh, UT_REG_IDX3, 1, idx3);
  UTL_SetRegUs(regh, UT_REG_IDX7, 1, (USlider)(214e-6/DBMARG.rate/DBMARG.ilmode)); //DBM load wait time 214us

  UTL_SendReg(regh);
  UTL_DeleteHandle(regh);

  return;
}

static void reg_setting(TEST_testitem *testarg)
{
  RegHandle regh;
  regh = UTL_GetRegHandle();

  USlider xmax = (0x1<<(16-CBITS))-1;
  USlider ymax = (DBMSIZE>>16)-1;
  UTL_SetRegUs(regh, UT_REG_XMAX, 1, xmax);
  UTL_SetRegUs(regh, UT_REG_LMAX, 1, xmax);
  UTL_SetRegUs(regh, UT_REG_YMAX, 1, ymax);
  UTL_SetRegUs(regh, UT_REG_HMAX, 1, ymax);

  UTL_SetRegUs(regh, UT_REG_IDX1, 1, DBMARG.checksize/8-2); //for AUTOXFER
  UTL_SetRegUs(regh, UT_REG_IDX2, 1, DBMARG.checksize/8/2-2);

  UTL_SetRegUs(regh, UT_REG_IDX3, 1, BUFSIZE/8-2); //for DBMXFER, DCM
  UTL_SetRegUs(regh, UT_REG_IDX4, 1, BUFSIZE/8/2-2);
  UTL_SetRegUs(regh, UT_REG_IDX5, 1, DBMARG.checksize/BUFSIZE-2);

  UTL_SetRegUs(regh, UT_REG_IDX7, 1, (USlider)(214e-6/DBMARG.rate/DBMARG.ilmode)); //DBM load wait time 214us

  UTL_SendReg(regh);
  UTL_DeleteHandle(regh);

  return;
}

static void write_dbm(TEST_testitem *testarg)
{
  USlider *wdata;
  wdata = (USlider *)malloc(DBMARG.checksize*sizeof(USlider));

  int i;
  for(i=0; i<DBMARG.checksize; i++){
    wdata[i] = i;
    if(DEBUG>2){printf("wdata[0x%08x]=0x%08x\n", i, wdata[i]);}
  }

  DbmAccessHandle dah = UTL_GetDbmAccessHandle();
  UTL_SetDbmAccessAllUnit(dah, UT_ON);		//1unit
  UTL_SetDbmAccessAllBlock(dah, UT_ON);		//8block
  UTL_SetDbmAccessDataKind(dah, UT_DBM_PPAT);
  UTL_SetDbmAccessStartAddr(dah, 0x0);
  UTL_SetDbmAccessStopAddr(dah, DBMARG.checksize-1);

  printf("Start UTL_WriteDbm()\n"); fflush(stdout);
  UTL_WriteDbm(dah, wdata, DBMARG.checksize*sizeof(USlider));
  printf("End   UTL_WriteDbm()\n"); fflush(stdout);
  UTL_DeleteHandle(dah);
  free(wdata);

  return;
}

static void write_dbm_sq(TEST_testitem *testarg, USlider *sqtable)
{
  USlider *wdata;
  wdata = (USlider *)malloc(DBMARG.checksize*sizeof(USlider));

  int i;
  for(i=0; i<DBMARG.checksize; i++){
    wdata[(sqtable[i/BUFSIZE]*BUFSIZE)|(i%BUFSIZE)] = i;
  }
  if(DEBUG>1){
    for(i=0; i<DBMARG.checksize/BUFSIZE; i++){
      printf("BLOCK%d ADDR=0x%08x DATA=0x%08x\n", i, i*BUFSIZE, wdata[i*BUFSIZE]);
    }
  }

  DbmAccessHandle dah = UTL_GetDbmAccessHandle();
  UTL_SetDbmAccessAllUnit(dah, UT_ON);		//1unit
  UTL_SetDbmAccessAllBlock(dah, UT_ON);		//8block
  UTL_SetDbmAccessDataKind(dah, UT_DBM_PPAT);
  UTL_SetDbmAccessStartAddr(dah, 0x0);
  UTL_SetDbmAccessStopAddr(dah, DBMARG.checksize-1);

  printf("Start UTL_WriteDbm() SQ\n"); fflush(stdout);
  UTL_WriteDbm(dah, wdata, DBMARG.checksize*sizeof(USlider));
  printf("End   UTL_WriteDbm() SQ\n"); fflush(stdout);
  UTL_DeleteHandle(dah);
  free(wdata);

  return;
}

static int read_dbm(TEST_testitem *testarg)
{
  int i;
  int result;
  USlider *edata;
  USlider *rdata;

  edata = (USlider *)malloc(DBMARG.checksize*sizeof(USlider));
  rdata = (USlider *)malloc(DBMARG.checksize*sizeof(USlider));
  memset(rdata, 0x0, DBMARG.checksize*sizeof(USlider));

  for(i=0; i<DBMARG.checksize; i++){
    edata[i] = i;
    if(DEBUG>2){printf("edata[%d]=%08x\n", i, edata[i]);}
  }

  DbmAccessHandle dah = UTL_GetDbmAccessHandle();
  UTL_SetDbmAccessDataKind(dah, UT_DBM_PPAT);
  UTL_SetDbmAccessAllUnit(dah, UT_OFF);
  UTL_SetDbmAccessUnitNumber(dah, 1);  
  UTL_SetDbmAccessAllBlock(dah, UT_OFF);
  UTL_SetDbmAccessBlockNumber(dah, 1);
  UTL_SetDbmAccessStartAddr(dah, 0x0);
  UTL_SetDbmAccessStopAddr(dah, DBMARG.checksize-1);

  printf("Start UTL_ReadDbm()\n"); fflush(stdout);
  UTL_ReadDbm(dah, rdata, DBMARG.checksize*sizeof(USlider));
  printf("End   UTL_ReadDbm()\n"); fflush(stdout);
  UTL_DeleteHandle(dah);

  result = 0;
  for (i=0; i<DBMARG.checksize; i++){
    if(DEBUG>2){printf("rdata[0x%08x]=0x%08x\n", i, rdata[i]); fflush(stdout);}
    if(edata[i]!=rdata[i]){
      printf("Fail rdata[0x%08x]:0x%08x\n", i, rdata[i]); fflush(stdout);
      printf("Error!! Please Check Program or INIT/DIAG status.\n");
      fflush(stdout);
      result = 1;
      break;
    }
  }
  free(edata);
  free(rdata);

  return(result);
}

static void display(TEST_testitem *testarg, int result)
{
  printf("\n%-32s",UTL_ReadTestName());
  if(result==0){
    testresult_pass4alldut(testarg->testname);
    printf(" ***PASS"); 
  }else{
    testresult_fail4alldut(testarg->testname);
    if(result==3){
      printf("LOG CHECK!!");
    }else if(result!=0) printf(" FAIL** dut:%x",result); 
  }   
  fflush(stdout);

  return;
}

void dbm_wr_rd(TEST_testitem *testarg)
{
  if(DEBUG>0){printf("ilmode\t\t: %d\n",DBMARG.ilmode);fflush(stdout);}
  if(DEBUG>0){printf("check size\t: 0x%08x\n",DBMARG.checksize);fflush(stdout);}

  int result = 0;

  set_ilmode(DBMARG.ilmode);
  reset_dbm_memory();
  write_dbm(testarg);
  result = read_dbm(testarg);
  if(DEBUG>0) printf("result:%d\n",result); fflush(stdout);

  display(testarg, result);

  return;
}

void dbm_check_YMTC(TEST_testitem *testarg)
{
  DutCursor dutcur;
  UT_DUT dut;
  int dutblock;
  int i;
  int pingroup;
  int dbmbit[18+1];
  for(i=0; i<18+1; i++){
    dbmbit[i] = -1;
  }

  if(is_diagsocket()){ //diagpb
    SOCKET.dut_iopin_count = 36;
    SOCKET.dutblock_count = 4;
    SOCKET.dutblock_iopin_count[0] = 9;
    SOCKET.dutblock_iopin_count[1] = 9;
    SOCKET.dutblock_iopin_count[2] = 9;
    SOCKET.dutblock_iopin_count[3] = 9;
    for(i=0; i<9; i++){
      SOCKET.dutblock_iopin[0][i] = i+1;
      SOCKET.dutblock_iopin[1][i] = i+65;
      SOCKET.dutblock_iopin[2][i] = i+10;
      SOCKET.dutblock_iopin[3][i] = i+74;
    }
    refresh_pinlist();
    print_socketinfo();
  }

  //bitmode selection for UTL_SetDbmConfigBitAssignMode()
  DBMARG.bitmode = UT_DBM_PIN_GROUP;
  for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
    for(i=0; i<SOCKET.dutblock_iopin_count[dutblock]; i++){
      if(i<DBMARG.bitsize){
        dutcur = UTL_GetDutCursor(UT_CDUT);
        while((dut=UTL_NextDut(dutcur))!=UT_NOMORE){
          pingroup = SOCKET.testeriopin[dut][SOCKET.dutblock_iopin[dutblock][i]]%64;
          if(dbmbit[pingroup]<0){
            dbmbit[pingroup] = i;
          }
          else if(dbmbit[pingroup]!=i){
            DBMARG.bitmode = UT_DBM_PIN_DUT_COMMON;
            if(DEBUG>1) printf("      X"); //conflict
          }
          if(DEBUG>1) printf("\tDBM DUT%d DUTBLOCK%d PINGROUP%2d BLOCKBIT%2d DBMBIT%2d\n", dut, dutblock, pingroup, i, dbmbit[pingroup]);
        }
        UTL_DeleteCursor(dutcur);
      }
    }
  }

  if(DEBUG>0){
    printf("ilmode\t\t: %d\n",DBMARG.ilmode);
    printf("mpat\t\t: %s\n",DBMARG.mpat);
    printf("pc\t\t: 0x%03x\n",DBMARG.pc);
    printf("rate\t\t: %e\n",DBMARG.rate);
    printf("ddr_mode\t: ");
    if(DBMARG.ddrmode==UT_OFF){
      printf("UT_OFF\n");
    }
    else{
      printf("UT_ON\n");
    }
    printf("dbm_mode\t: %d\n", DBMARG.dbmmode);
    printf("bit_size\t: %d\n", DBMARG.bitsize);
    printf("bit_mode\t: ");
    if(DBMARG.bitmode==UT_DBM_PIN_GROUP){
      printf("UT_DBM_PIN_GROUP\n");
    }
    else{
      printf("UT_DBM_PIN_DUT_COMMON\n");
    }
    printf("check size\t: 0x%08x\n",DBMARG.checksize);
  }

  timing_setting(testarg);
  level_setting(1, 1.0, 0.0);
  printf("socket\t\t: diagpb_YMTC\n");
  pin_condition_YMTC(testarg);

  set_memory_module_dbm();
  set_burst_scram(testarg);

  reset_dbm_memory();
  dbm_setting(testarg);
  reg_setting_YMTC(testarg);

  meas_fct(testarg);

  return;
}

void dbm_check(TEST_testitem *testarg)
{
  DutCursor dutcur;
  UT_DUT dut;
  int dutblock;
  int i;
  int pingroup;
  int dbmbit[18+1];
  for(i=0; i<18+1; i++){
    dbmbit[i] = -1;
  }

  if(is_diagsocket()){ //diagpb
    SOCKET.dut_iopin_count = 36;
    SOCKET.dutblock_count = 4;
    SOCKET.dutblock_iopin_count[0] = 9;
    SOCKET.dutblock_iopin_count[1] = 9;
    SOCKET.dutblock_iopin_count[2] = 9;
    SOCKET.dutblock_iopin_count[3] = 9;
    for(i=0; i<9; i++){
      SOCKET.dutblock_iopin[0][i] = i+1;
      SOCKET.dutblock_iopin[1][i] = i+65;
      SOCKET.dutblock_iopin[2][i] = i+10;
      SOCKET.dutblock_iopin[3][i] = i+74;
    }
    refresh_pinlist();
    print_socketinfo();
  }

  //bitmode selection for UTL_SetDbmConfigBitAssignMode()
  DBMARG.bitmode = UT_DBM_PIN_GROUP;
  for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
    for(i=0; i<SOCKET.dutblock_iopin_count[dutblock]; i++){
      if(i<DBMARG.bitsize){
        dutcur = UTL_GetDutCursor(UT_CDUT);
        while((dut=UTL_NextDut(dutcur))!=UT_NOMORE){
          pingroup = SOCKET.testeriopin[dut][SOCKET.dutblock_iopin[dutblock][i]]%64;
          if(dbmbit[pingroup]<0){
            dbmbit[pingroup] = i;
          }
          else if(dbmbit[pingroup]!=i){
            DBMARG.bitmode = UT_DBM_PIN_DUT_COMMON;
            if(DEBUG>1) printf("      X"); //conflict
          }
          if(DEBUG>1) printf("\tDBM DUT%d DUTBLOCK%d PINGROUP%2d BLOCKBIT%2d DBMBIT%2d\n", dut, dutblock, pingroup, i, dbmbit[pingroup]);
        }
        UTL_DeleteCursor(dutcur);
      }
    }
  }

  if(DEBUG>0){
    printf("ilmode\t\t: %d\n",DBMARG.ilmode);
    printf("mpat\t\t: %s\n",DBMARG.mpat);
    printf("pc\t\t: 0x%03x\n",DBMARG.pc);
    printf("rate\t\t: %e\n",DBMARG.rate);
    printf("ddr_mode\t: ");
    if(DBMARG.ddrmode==UT_OFF){
      printf("UT_OFF\n");
    }
    else{
      printf("UT_ON\n");
    }
    printf("dbm_mode\t: %d\n", DBMARG.dbmmode);
    printf("bit_size\t: %d\n", DBMARG.bitsize);
    printf("bit_mode\t: ");
    if(DBMARG.bitmode==UT_DBM_PIN_GROUP){
      printf("UT_DBM_PIN_GROUP\n");
    }
    else{
      printf("UT_DBM_PIN_DUT_COMMON\n");
    }
    printf("check size\t: 0x%08x\n",DBMARG.checksize);
  }

  timing_setting(testarg);
  level_setting(1, 1.0, 0.0);
  if(is_diagsocket()){
    printf("socket\t\t: diagpb\n");
    pin_condition_diagpb(testarg);
  }
  else{
    printf("socket\t\t: pbfree\n");
    pin_condition_pbfree(testarg);
  }

  set_memory_module_dbm();
  set_burst_scram(testarg);

  reset_dbm_memory();
  dbm_setting(testarg);
  reg_setting(testarg);

  meas_fct(testarg);

  return;
}

