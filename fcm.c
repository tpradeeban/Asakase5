#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <memory.h>
#include <malloc.h>
#include <time.h>
#include "UTSC.h"
#include "test.h"
#include "test_struct.h"
#include "fcm.h"

#define DEBUG (1)
#define FCM_ACCESS_SEARCH_MAX_CNT (1024)
#define UBMSIZE (128*1024)
#define UBMADD_PER_AFMXFER (16)
USlider *UBM_DATA;

static void fcm_preset_all(USlider n);
static void fcm_preset_inuse(USlider n);
static double fcm_busy_wait();
static void burst_scram(TEST_testitem *testarg);
static USlider read_count(UT_DUT dut, int bit, int xsta, int xstp, int ysta, int ystp, double *time);
static void fcm_print_delay_log(TEST_testitem *testarg, UT_DUT dut, int delay, int x_fail_addr);
static int read_fail_address_delay(UT_DUT dut, int fmbit, int exp_xaddr, int exp_yaddr);
static void fcm_read_check(TEST_testitem *testarg, unsigned long exp_a, unsigned long exp_b);
static void memory_module_fcm();
static void failcapsel(TEST_testitem *testarg);
static void print_fcmconfig(TEST_testitem *testarg);
static void fcm_level(TEST_testitem *testarg);
static void fcm_timing(TEST_testitem *testarg);
static int fcm_mconfig();
static void fcm_pfc_clear(TEST_testitem *testarg);
static void preset_ubm(USlider n);
static void write_ubm_rand(TEST_testitem *testarg);
static void fcm_reg_fcsm(TEST_testitem *testarg);
static void set_ubm();
static void write_ubm_perdut(TEST_testitem *testarg);

static void fcm_preset_all(USlider n)
{
  FcmAccessHandle FcmAccess_H=UTL_GetFcmAccessHandle();
  UTL_SetFcmAccessAllDut          (FcmAccess_H, UT_ON);
  UTL_SetFcmAccessAllBit          (FcmAccess_H, UT_ON);
  UTL_SetFcmAccessPresetAllMemory (FcmAccess_H, UT_ON);
  UTL_PresetFcm                   (FcmAccess_H, n);
  UTL_DeleteHandle                (FcmAccess_H);
  return;
}

static void fcm_preset_inuse(USlider n)
{
  FcmAccessHandle FcmAccess_H=UTL_GetFcmAccessHandle();
  UTL_SetFcmAccessAllDut          (FcmAccess_H, UT_ON);
  UTL_SetFcmAccessAllBit          (FcmAccess_H, UT_ON);
  UTL_SetFcmAccessPresetMemoryInUse(FcmAccess_H, UT_ON);
  UTL_PresetFcm                   (FcmAccess_H, n);
  UTL_DeleteHandle                (FcmAccess_H);
  return;
}

void set_result(UT_DUT dut, int result){
  if(result<=0){
    if(result==0){
      printf("DUT%2d PASS\n", dut);
    }
    else{
      printf("DUT%2d SKIP\n", dut);
    }
    UTL_ResetTestResult(dut, UTL_ReadTestName(), UT_RES_FUNC);
  }
  else{
    printf("DUT%2d ****FAIL\n", dut);
    UTL_SetTestResult(dut, UTL_ReadTestName(), UT_RES_FUNC);
  }
  fflush(stdout);

  return;
}

static void burst_scram(TEST_testitem *testarg){
  BurstScramHandle BurstScram_H = UTL_GetBurstScramHandle();

  if(FCMARG.burstlength<2){
    UTL_SetBurstScramMode             (BurstScram_H, UT_OFF);
  }
  else{
    UTL_SetBurstScramMode             (BurstScram_H, UT_ON);
	UTL_SetBurstScramBaseFileName     (BurstScram_H, NULL);
    //UTL_SetBurstScramBaseFileName     (BurstScram_H, "fsbscrddr_BL16");
   	UTL_AddBurstScramWriteSignal      (BurstScram_H, UT_SIG_WT);

	if(FCMARG.burstlength<=2){
	    UTL_SetBurstScramDdrType          (BurstScram_H, 1);
	}else{
	    UTL_SetBurstScramDdrType          (BurstScram_H, 5);
	}

    if(FCMARG.ddrmode==UT_ON){
      UTL_SetBurstScramDataRate         (BurstScram_H, 2);
    }
    else{
      UTL_SetBurstScramDataRate         (BurstScram_H, 1);
    }
    UTL_SetBurstScramLength           (BurstScram_H, FCMARG.burstlength);
    UTL_SetBurstScramWrapType         (BurstScram_H, UT_WPTSQ);
    UTL_SetBurstScramAddrUnit         (BurstScram_H, UT_UNIT_PDS, UT_ON);
    UTL_SetBurstScramAddrUnit         (BurstScram_H, UT_UNIT_DFM, UT_ON);
    UTL_SetBurstScramAddrUnit         (BurstScram_H, UT_UNIT_FP , UT_ON);
  }
  UTL_SendBurstScram                (BurstScram_H);
  UTL_DeleteHandle                  (BurstScram_H);

  return;
}

static USlider read_count(UT_DUT dut, int bit, int xsta, int xstp, int ysta, int ystp, double *time){
  int i;
  USlider count = 0;
  double period1, period2;
  int    overflow;

  FcmAccessHandle FcmAccess_H = UTL_GetFcmAccessHandle();
  UTL_SetFcmAccessAction             (FcmAccess_H, 1);
  UTL_SetFcmAccessAllDut             (FcmAccess_H, UT_OFF);
  UTL_SetFcmAccessDut                (FcmAccess_H, dut);
  UTL_SetFcmAccessAllBit             (FcmAccess_H, UT_ON);
  UTL_SetFcmAccessAutoAddrAssignMode (FcmAccess_H, UT_ON);
  UTL_SetFcmAccessXAddr              (FcmAccess_H, xsta, xstp);
  UTL_SetFcmAccessYAddr              (FcmAccess_H, ysta, ystp);

  UTL_StartTimer(UT_TIMER_R1US);
  period1 = UTL_ReadTimer(&overflow);
  UTL_CntFcmFailAddr                 (FcmAccess_H);
  period2 = UTL_ReadTimer(&overflow);
  *time = period2 - period1;

  if(UTL_GetFcmFailAddrCntOverflow(bit)==UT_OFF){
    count = UTL_GetFcmFailAddrCnt(bit);
  }
  else{
    printf("OVERFLOW ERROR!!\n");
    count = -1;
  }

  return(count);
}

static void fcm_print_delay_log(TEST_testitem *testarg, UT_DUT dut, int delay, int x_fail_addr){
  unsigned long i, x, y;
  RadioButton fmblock;

  USlider  size;
  USlider  *fcm_rdata;

  size = (((0x1f) - (0x0) + 1))* (((0x0) - (0x0) + 1));
  fcm_rdata = (USlider *)calloc(size, sizeof(USlider));

  FcmAccessHandle FcmAccess_H = UTL_GetFcmAccessHandle();
  UTL_ClearFcmAccessBit              (FcmAccess_H);
  UTL_SetFcmAccessAction             (FcmAccess_H, 1);
  UTL_SetFcmAccessAllDut             (FcmAccess_H, UT_OFF);
  UTL_SetFcmAccessDut                (FcmAccess_H, dut);
  UTL_SetFcmAccessAllBit             (FcmAccess_H, UT_OFF);
  UTL_SetFcmAccessBitMode            (FcmAccess_H, UT_FCM_BITMODE_BLOCK);
  UTL_SetFcmAccessAutoAddrAssignMode (FcmAccess_H, UT_ON);
  UTL_SetFcmAccessXAddr              (FcmAccess_H, 0x0, 0x1f);
  UTL_SetFcmAccessYAddr              (FcmAccess_H, 0x0, 0x0);
  UTL_SetFcmAccessApLink             (FcmAccess_H, UT_FCM_APLINK_XYZ);

  for(fmblock=1; fmblock<=(SOCKET.dut_iopin_count/FCMARG.fmbitcomp+FMBLKBIT-1)/FMBLKBIT; fmblock++){
    UTL_SetFcmAccessBitBlock(FcmAccess_H, fmblock);
    UTL_ReadFcm(FcmAccess_H, fcm_rdata, sizeof(USlider)*size);

    i=0;
    printf("\tDUT%2d FMBLK%d delay=%2d xaddr=0x%x [FBMP] : ", dut, fmblock, delay, x_fail_addr);
    for(x=0;x<=0x1f;x++){
      if(fcm_rdata[i]==0x0){
        printf(".");
      }
      else{
        printf("F");
      }
      i++;
    }
    printf("\n");
    fflush(stdout);
  }

  UTL_DeleteHandle(FcmAccess_H);
  free(fcm_rdata);

  return;
}

static int read_fail_address_delay(UT_DUT dut, int fmbit, int exp_xaddr, int exp_yaddr)
{
  int i;
  int fail_count = 0;
  int result = 0;

  USlider x_fail_addr, y_fail_addr;
  AddrCursor addrcur;
  UT_ADDR    addr = 0;

  FcmAccessHandle FcmAccess_H = UTL_GetFcmAccessHandle();
  UTL_ClearFcmAccessBit              (FcmAccess_H);
  UTL_SetFcmAccessAction             (FcmAccess_H, 1);
  UTL_SetFcmAccessAllDut             (FcmAccess_H, UT_OFF);
  UTL_SetFcmAccessDut                (FcmAccess_H, dut);
  UTL_SetFcmAccessAllBit             (FcmAccess_H, UT_OFF);
  UTL_AddFcmAccessBit                (FcmAccess_H, fmbit);
  UTL_SetFcmAccessAutoAddrAssignMode (FcmAccess_H, UT_ON);
  UTL_SetFcmAccessXAddr              (FcmAccess_H, 0x0, 0xff);
  UTL_SetFcmAccessYAddr              (FcmAccess_H, 0x0, 0xff);
  UTL_CntFcmFailAddr                 (FcmAccess_H);

  fail_count =  UTL_GetFcmFailAddrCnt(fmbit);

  if(fail_count!=0){
    if(fail_count>FCM_ACCESS_SEARCH_MAX_CNT){
      fail_count = FCM_ACCESS_SEARCH_MAX_CNT;
    }
    UTL_SetFcmAccessSearchMaxCnt (FcmAccess_H, fail_count);
    UTL_SearchFcmFailAddr        (FcmAccess_H);
    addrcur = UTL_GetFcmFailAddr(fmbit);
    addr = UTL_NextAddr(addrcur);
    if(addr!=UT_NOMORE){
      x_fail_addr = UTL_GetXAddr(addr);
      y_fail_addr = UTL_GetYAddr(addr);
      if((x_fail_addr!=exp_xaddr)||(y_fail_addr!=exp_yaddr)){
        result = 1;
        printf("\tDUT%2d FMBIT%2d : X FAIL = 0x%x (EXP=0x%x)\n", dut, fmbit, x_fail_addr, exp_xaddr);
        printf("\tDUT%2d FMBIT%2d : Y FAIL = 0x%x (EXP=0x%x)\n", dut, fmbit, y_fail_addr, exp_yaddr);
      }
    }
    else{
      result = 1;
      printf("\tDUT%2d FMBIT%2d : SEARCH ERROR\n", dut, fmbit);
    }
    UTL_DeleteCursor(addrcur);
  }
  else {
    result = 1;
    printf("\tDUT%2d FMBIT%2d : FAIL COUNT = %d\n", dut, fmbit, fail_count);
  }
  UTL_DeleteHandle(FcmAccess_H);

  return(result);
}

static void fcm_read_check(TEST_testitem *testarg, unsigned long exp_a, unsigned long exp_b)
{
  int i;
  DutCursor dutc;
  UT_DUT dut = 0;
  RadioButton fmbit;
  int dutblock;
  USlider size;
  USlider *fcm_rdata1;
  USlider *fcm_rdata2;
  int x, y;
  USlider exp_data;
  USlider xsta = 0x0;
  USlider xspa = (0x1<<FCMARG.xbits)-1;
  USlider ysta = 0x0;
  USlider yspa = (0x1<<FCMARG.ybits)-1;

  size = (0x1<<(FCMARG.xbits+FCMARG.ybits));
  fcm_rdata1 = (USlider *)calloc(size, sizeof(USlider));
  fcm_rdata2 = (USlider *)calloc(size, sizeof(USlider));
  USlider fcm_rdata;

  FcmAccessHandle FcmAccess_H1 = UTL_GetFcmAccessHandle();
  UTL_ClearFcmAccessBit          (FcmAccess_H1);
  UTL_SetFcmAccessAction         (FcmAccess_H1, 1);
  UTL_SetFcmAccessAllDut         (FcmAccess_H1, UT_OFF);
  UTL_SetFcmAccessAllBit         (FcmAccess_H1, UT_OFF);
  UTL_SetFcmAccessAutoAddrAssignMode(FcmAccess_H1, UT_ON);
  UTL_SetFcmAccessXAddr          (FcmAccess_H1, xsta, xspa);
  UTL_SetFcmAccessYAddr          (FcmAccess_H1, ysta, yspa);
  UTL_SetFcmAccessApLink         (FcmAccess_H1, UT_FCM_APLINK_XYZ);

  FcmAccessHandle FcmAccess_H2 = UTL_GetFcmAccessHandle();
  UTL_ClearFcmAccessBit          (FcmAccess_H2);
  UTL_SetFcmAccessAction         (FcmAccess_H2, 1);
  UTL_SetFcmAccessAllDut         (FcmAccess_H2, UT_OFF);
  UTL_SetFcmAccessAllBit         (FcmAccess_H2, UT_OFF);
  UTL_SetFcmAccessAutoAddrAssignMode(FcmAccess_H2, UT_ON);
  UTL_SetFcmAccessXAddr          (FcmAccess_H2, xsta, xspa);
  UTL_SetFcmAccessYAddr          (FcmAccess_H2, ysta, yspa);
  UTL_SetFcmAccessApLink         (FcmAccess_H2, UT_FCM_APLINK_XYZ);

  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      set_result(dut, -1); //skip
      continue;
    }

    UTL_SetFcmAccessDut(FcmAccess_H1, dut);
    UTL_SetFcmAccessDut(FcmAccess_H2, dut);
    for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
      UTL_ClearFcmAccessBit(FcmAccess_H1);
      UTL_ClearFcmAccessBit(FcmAccess_H2);
      for(fmbit=SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp; fmbit<SOCKET.dutblock_iopin_count[0]*(dutblock+1)/FCMARG.fmbitcomp; fmbit++){
        if((SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp/FMBLKBIT)==(fmbit/FMBLKBIT)){
          UTL_AddFcmAccessBit(FcmAccess_H1, fmbit);
        }
        else{
          UTL_AddFcmAccessBit(FcmAccess_H2, fmbit);
        }
      }

      UTL_ReadFcm(FcmAccess_H1, fcm_rdata1, size*sizeof(USlider));
      if((SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp/FMBLKBIT)<((SOCKET.dutblock_iopin_count[0]*(dutblock+1)/FCMARG.fmbitcomp-1)/FMBLKBIT)){
        UTL_ReadFcm(FcmAccess_H2, fcm_rdata2, size*sizeof(USlider));
      }
      else{
        memset(fcm_rdata2, 0x0, size*sizeof(USlider));
      }
 
      i=0;
      if(DEBUG==1){
        for(y=0; y<=0x3; y++){
          fcm_rdata = (fcm_rdata1[i]>>(SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT))|(fcm_rdata2[i]<<(FMBLKBIT-SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT));
          printf("\tDUT%2d BLK%d : data[0x%08x] = 0x%08x\n", dut, dutblock, i, fcm_rdata);
          i++;
        }
      }
 
      i=0;
      for(y=ysta; y<=yspa; y++){
        for(x=xsta; x<=xspa; x++){
          if(((x^y)&0x1)==0x0){
            exp_data = exp_a;
          }
          else{
            exp_data = exp_b;
          }
 
          fcm_rdata = (fcm_rdata1[i]>>(SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT))|(fcm_rdata2[i]<<(FMBLKBIT-SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT));
          if(fcm_rdata!=exp_data){
            printf("\tDUT%2d BLK%d : data[0x%08x] = 0x%08x (EXP=0x%08x) (x=0x%x y=0x%x)\n", dut, dutblock, i, fcm_rdata, exp_data, x, y);
            fflush(stdout);
            set_result(dut, 1);
            goto fcm_read_fail;
          }
          i++;
        }
      }
    }
    set_result(dut, 0);
    fcm_read_fail: ;
  }
  UTL_DeleteCursor(dutc);
  UTL_DeleteHandle(FcmAccess_H1);
  UTL_DeleteHandle(FcmAccess_H2);
  free(fcm_rdata1);
  free(fcm_rdata2);

  return;
}

static void memory_module_fcm()
{
  MemoryModuleHandle MemoryModule_H = UTL_GetMemoryModuleHandle();
  UTL_AddMemoryModulePurpose (MemoryModule_H, UT_MEM_FCM, 1);
  UTL_SendMemoryModule       (MemoryModule_H);
  UTL_DeleteHandle           (MemoryModule_H);

  return;
}

CheckButton is_captured(TEST_testitem *testarg, UT_DUT dut)
{
  CheckButton capture_flag = UT_OFF;
  if((FCMARG.allchild==UT_ON)||(FCMARG.child==SOCKET.dut_child[dut])){
    capture_flag = UT_ON;
  }
  return(capture_flag);
}

static void failcapsel(TEST_testitem *testarg){
  FailCaptureSelectHandle fcsh;
  fcsh=UTL_GetFailCaptureSelectHandle();
  UTL_SetFailCaptureSelectAllDutGroupNumber(fcsh, FCMARG.allchild);
  UTL_SetFailCaptureSelectDutGroupNumber(fcsh, FCMARG.child);
  UTL_SetFailCaptureSelectAllPin(fcsh, FCMARG.allpin);
  UTL_SetFailCaptureSelectPinList(fcsh, SOCKET.all_iopinlist);
  UTL_SendFailCaptureSelect(fcsh);
  UTL_DeleteHandle(fcsh);
  return;
}

static void print_fcmconfig(TEST_testitem *testarg)
{
  printf("ilmode:\t\t%d\n", FCMARG.ilmode);
  printf("fcmrate:\t");
  if(FCMARG.fcmrate==UT_FCM_HS){
    printf("UT_FCM_HS\n");
  }
  else if(FCMARG.fcmrate==UT_FCM_MS){
    printf("UT_FCM_MS\n");
  }
  else{
    printf("UT_FCM_LS\n");
  }
  printf("FMBL:\t\t%d\n", FCMARG.burstlength);
  printf("mconfig:\tX%d\n", fcm_mconfig());
  printf("rate:\t\t%e\n", FCMARG.rate);
  printf("ddrmode:\t");
  if(FCMARG.ddrmode==UT_OFF){
    printf("UT_OFF\n");
  }
  else{
    printf("UT_ON\n");
  }
  printf("xbits:\t\t%d\n", FCMARG.xbits);
  printf("ybits:\t\t%d\n", FCMARG.ybits);
  printf("mapt:\t\t%s\n", FCMARG.mpat);
  printf("pc:\t\t0x%03x\n", FCMARG.pc);
  fflush(stdout);

  return;
}

void fcm_check(TEST_testitem *testarg)
{
  int tcount;
  DutCursor dutc;
  int result;
  UT_DUT dut;
  int speccheck;
  int mconfig;
  int dutblock;

  for(dutblock=0; dutblock<SOCKET.dutblock_count-1; dutblock++){
    if(SOCKET.dutblock_iopin_count[dutblock]!=SOCKET.dutblock_iopin_count[dutblock+1]){
      testarg->skipreason = TEST_SKIP_SOCKET;
      return;
    }
  }

  if(FCMARG.allchild==UT_ON){
    SOCKET.dut_iopin_count = 0;
    for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
      SOCKET.dutblock_iopin_count[dutblock]/=2;
      SOCKET.dut_iopin_count+=SOCKET.dutblock_iopin_count[dutblock];
    }
    refresh_pinlist();
    print_socketinfo();
  }

  set_ilmode(FCMARG.ilmode);
  memory_module_fcm();
  burst_scram(testarg);
  failcapsel(testarg);

  fcm_level(testarg);
  fcm_timing(testarg);

  if(FCMARG.pincond!=NULL){
    FCMARG.pincond(testarg);
  }

  int childnum = 1;
  if(FCMARG.allchild==UT_ON){
    childnum = 2;
  }

  FCMARG.fmbitcomp = 0;
  mconfig = 999;
  tcount = 0;
  result = 0;
  do{
    do{
      FCMARG.fmbitcomp++;
    }while((SOCKET.dutblock_iopin_count[0]%FCMARG.fmbitcomp!=0)&&(SOCKET.dutblock_iopin_count[0]>FCMARG.fmbitcomp));

    printf("\n%s n1=%d, n2=%d", testarg->testname, SOCKET.dut_iopin_count, SOCKET.dut_iopin_count/FCMARG.fmbitcomp);

    speccheck = SOCKET.dutblock_iopin_count[0]*childnum/FCMARG.fmbitcomp*FCMARG.burstlength;
    if(FCMARG.fcmrate==UT_FCM_MS){
      speccheck/=2;
    }
    else if(FCMARG.fcmrate==UT_FCM_LS || FCMARG.fcmrate==UT_FCM_BS){
      speccheck/=4;
    }
    if(speccheck>256){ // Invalid combination, mconfig&FMBL
      printf("\tSKIP\n");
      continue;
    }
    printf("\n");

    if(FCMARG.config!=NULL){
      FCMARG.config(testarg);
    }
    print_fcmconfig(testarg);

    if(FCMARG.premeas!=NULL){
      FCMARG.premeas(testarg);
    }

    if(FCMARG.fcmaction==UT_FCM_PFC_TO_FCSM){
      UTL_ResetFcsmStoreCnt();
    }
    else{
      fcm_preset_inuse(0);
    }

    if(strcmp(FCMARG.mpat, "")!=0){
      FctHandle Fct_H = UTL_GetFctHandle();
      UTL_SetFctMpatName    (Fct_H, FCMARG.mpat);
      UTL_SetFctFailInhibit (Fct_H, UT_ON);
      UTL_SetFctStartPc     (Fct_H, FCMARG.pc);
      UTL_MeasFct           (Fct_H);
      UTL_DeleteHandle      (Fct_H);
    }
    mconfig = fcm_mconfig();

    if(FCMARG.postmeas!=NULL){
      FCMARG.postmeas(testarg);
    }

    dutc = UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
      if(UTL_ReadTestResult(dut, testarg->testname, UT_RES_ALL)==UT_RES_FAILED){
        result|=1;
      }
    }
    UTL_DeleteCursor(dutc);

    tcount++;
  }while(mconfig>8);

  if(result!=0){
    testresult_fail4alldut(testarg->testname);
  }
  else if(tcount==0){
    testarg->skipreason = TEST_SKIP_FM_CONFIG;
  }

  return;
}

static void fcm_level(TEST_testitem *testarg){
  ViHandle Vi_H = UTL_GetViHandle();
  UTL_SetViHigh    (Vi_H, 1.0);
  UTL_SetViLow     (Vi_H, 0.0);
  UTL_SendVi       (Vi_H, 1);
  UTL_DeleteHandle (Vi_H);

  VoHandle Vo_H = UTL_GetVoHandle();
  UTL_SetVoHigh    (Vo_H, 0.5);
  UTL_SetVoLow     (Vo_H, 0.5);
  UTL_SendVo       (Vo_H, 1);
  UTL_DeleteHandle (Vo_H);

  VtHandle Vt_H = UTL_GetVtHandle();
  UTL_SetVt        (Vt_H, 0.0);
  UTL_SendVt       (Vt_H, 1);
  UTL_DeleteHandle (Vt_H);

  return;
}

static void fcm_timing(TEST_testitem *testarg){
  TgHandle Tg_H = UTL_GetTgHandle();

  UTL_AddTgRate    (Tg_H, 1, FCMARG.rate);

  UTL_AddTgBclk    (Tg_H, 1, 1, 0.0);
  UTL_AddTgCclk    (Tg_H, 1, 1, FCMARG.rate*0.50);
  UTL_AddTgBclk    (Tg_H, 1, 2, 0.0);
  UTL_AddTgCclk    (Tg_H, 1, 2, FCMARG.rate*0.50);

  UTL_AddTgDreL    (Tg_H, 1, 1, 0.0);
  UTL_AddTgDreT    (Tg_H, 1, 1, 0.0);

  UTL_AddTgStrb    (Tg_H, 1, 1, FCMARG.rate*0.25);
  UTL_AddTgStrb    (Tg_H, 1, 2, FCMARG.rate*0.75);

  UTL_SendTg       (Tg_H);
  UTL_DeleteHandle (Tg_H);

  return;
}

void fcm_pin_std(TEST_testitem *testarg){
  int i;
  int dutblock;

  PinHandle Pin_H = UTL_GetPinHandle();
  UTL_SetPinViNumber      (Pin_H, 1);
  UTL_SetPinHvDr          (Pin_H, UT_OFF);
  UTL_SetPinDrWaveform    (Pin_H, UT_WAV_FIXL);
  UTL_SetPinIoCtrl        (Pin_H, UT_ON);
  UTL_SetPinDreNumber     (Pin_H, 1);
  UTL_SetPinDreWaveform   (Pin_H, UT_DREWAV_NRZ);
  UTL_SetPinDreClock      (Pin_H, 1);
  UTL_SetPinVoNumber      (Pin_H, 1);
  UTL_SetPinVtNumber      (Pin_H, 1);
  UTL_SetPinTerm          (Pin_H, UT_ON);
  UTL_AddPinStrbCpeNumber (Pin_H, 1, 1);
  UTL_AddPinExpStrbNumber (Pin_H, 1, UT_PIN_EXP_A);
  if(FCMARG.ddrmode==UT_ON){
    UTL_AddPinStrbCpeNumber (Pin_H, 2, 1);
    UTL_AddPinExpStrbNumber (Pin_H, 2, UT_PIN_EXP_B);
  }
  UTL_SetPinCpeDelay(Pin_H, FCMARG.cpedelay);

  for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
    UTL_ClearPinPdsA(Pin_H);
    UTL_ClearPinPdsB(Pin_H);
    for(i=0; i<SOCKET.dutblock_iopin_count[dutblock]; i++){
      UTL_AddPinPdsA(Pin_H, UT_SIG_D(i), 1);
      if(FCMARG.ddrmode==UT_ON){
        UTL_AddPinPdsB(Pin_H, UT_SIG_SD(i), 1);
      }
    }
    UTL_SendPin(Pin_H, SOCKET.dutblock_iopinlist[dutblock]);
  }
  UTL_DeleteHandle(Pin_H);

  return;
}

void fcm_pin_pfc(TEST_testitem *testarg){
  int i;
  int dutblock;

  PinHandle Pin_H = UTL_GetPinHandle();
  UTL_SetPinViNumber      (Pin_H, 1);
  UTL_SetPinHvDr          (Pin_H, UT_OFF);
  UTL_SetPinDrWaveform    (Pin_H, UT_WAV_FIXL);
  UTL_SetPinIoCtrl        (Pin_H, UT_ON);
  UTL_SetPinDreNumber     (Pin_H, 1);
  UTL_SetPinDreWaveform   (Pin_H, UT_DREWAV_NRZ);
  UTL_SetPinDreClock      (Pin_H, 1);
  UTL_SetPinVoNumber      (Pin_H, 1);
  UTL_SetPinVtNumber      (Pin_H, 1);
  UTL_SetPinTerm          (Pin_H, UT_ON);
  UTL_AddPinStrbCpeNumber (Pin_H, 1, 1);
  UTL_AddPinExpStrbNumber (Pin_H, 1, UT_PIN_EXP_A);
  if(FCMARG.ddrmode==UT_ON){
    UTL_AddPinStrbCpeNumber (Pin_H, 2, 1);
    UTL_AddPinExpStrbNumber (Pin_H, 2, UT_PIN_EXP_B);
  }
  UTL_SetPinCpeDelay(Pin_H, FCMARG.cpedelay);

  for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
    UTL_ClearPinPdsA(Pin_H);
    UTL_ClearPinPdsB(Pin_H);
    for(i=0; i<SOCKET.dutblock_iopin_count[dutblock]; i++){
      UTL_AddPinPdsA(Pin_H, UT_SIG_D(0), 1);
      UTL_AddPinPdsA(Pin_H, UT_SIG_D(1), 2);
      UTL_AddPinPdsA(Pin_H, UT_SIG_D(2), 3);
      UTL_AddPinPdsA(Pin_H, UT_SIG_D(3), 4);
      UTL_AddPinPdsA(Pin_H, UT_SIG_D(4), 5);
      UTL_AddPinPdsA(Pin_H, UT_SIG_D(5), 6);
      UTL_AddPinPdsA(Pin_H, UT_SIG_D(6), 7);
      UTL_AddPinPdsA(Pin_H, UT_SIG_D(7), 8);
    }
    UTL_SendPin(Pin_H, SOCKET.dutblock_iopinlist[dutblock]);
  }
  UTL_DeleteHandle(Pin_H);

  return;
}

void fcm_pin_fcsm(TEST_testitem *testarg){
  int i;
  int dutblock;

  PinHandle Pin_H = UTL_GetPinHandle();
  UTL_SetPinViNumber      (Pin_H, 1);
  UTL_SetPinHvDr          (Pin_H, UT_OFF);
  UTL_SetPinDrWaveform    (Pin_H, UT_WAV_FIXL);
  UTL_SetPinIoCtrl        (Pin_H, UT_ON);
  UTL_SetPinDreNumber     (Pin_H, 1);
  UTL_SetPinDreWaveform   (Pin_H, UT_DREWAV_NRZ);
  UTL_SetPinDreClock      (Pin_H, 1);
  UTL_SetPinVoNumber      (Pin_H, 1);
  UTL_SetPinVtNumber      (Pin_H, 1);
  UTL_SetPinTerm          (Pin_H, UT_ON);
  UTL_AddPinStrbCpeNumber (Pin_H, 1, 1);
  UTL_AddPinExpStrbNumber (Pin_H, 1, UT_PIN_EXP_A);
  if(FCMARG.ddrmode==UT_ON){
    UTL_AddPinStrbCpeNumber (Pin_H, 2, 1);
    UTL_AddPinExpStrbNumber (Pin_H, 2, UT_PIN_EXP_B);
  }
  UTL_SetPinCpeDelay(Pin_H, FCMARG.cpedelay);

  for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
    UTL_ClearPinPdsA(Pin_H);
    UTL_ClearPinPdsB(Pin_H);
    for(i=0; i<SOCKET.dutblock_iopin_count[dutblock]; i++){
      UTL_AddPinPdsA(Pin_H, UT_SIG_FL, 1);
      UTL_AddPinPdsA(Pin_H, UT_SIG_FH, 2);
      if(FCMARG.ddrmode==UT_ON){
        UTL_AddPinPdsB(Pin_H, UT_SIG_FL, 1);
        UTL_AddPinPdsB(Pin_H, UT_SIG_FL, 2);
      }
    }
    UTL_SendPin(Pin_H, SOCKET.dutblock_iopinlist[dutblock]);
  }
  UTL_DeleteHandle(Pin_H);

  return;
}

void fcm_config_std(TEST_testitem *testarg)
{
  int i = 0;
  int dutblock;

  PinCursor pincur;
  UT_PIN    pin = 0;

  FcmConfigHandle FcmConfig_H = UTL_GetFcmConfigHandle();
  UTL_SetFcmConfigRate           (FcmConfig_H, FCMARG.fcmrate);
  UTL_SetFcmConfigBitSize        (FcmConfig_H, SOCKET.dut_iopin_count/FCMARG.fmbitcomp);
  UTL_SetFcmConfigDutBitSize     (FcmConfig_H, SOCKET.dut_iopin_count);
  UTL_SetFcmConfigBurstCaptureLength(FcmConfig_H, FCMARG.burstlength);
  UTL_SetFcmConfigDdrMode        (FcmConfig_H, FCMARG.ddrmode);
  for(i=0; i<FCMARG.ybits; i++){
    UTL_SetFcmConfigAddrAssign   (FcmConfig_H, i, UT_SIG_Y(i));
  }
  for(i=0; i<FCMARG.xbits; i++){
    UTL_SetFcmConfigAddrAssign   (FcmConfig_H, i+FCMARG.ybits, UT_SIG_X(i));
  }
  UTL_SetFcmConfigDelay          (FcmConfig_H, FCMARG.cpedelay);

  for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
    pincur = UTL_GetPinCursor(SOCKET.dutblock_iopinlist[dutblock]);
    for(i=SOCKET.dutblock_iopin_count[0]*dutblock; i<SOCKET.dutblock_iopin_count[0]*(dutblock+1); i++){
      UTL_AddFcmConfigPinAssign    (FcmConfig_H, i/FCMARG.fmbitcomp, UTL_NextPin(pincur));
    }
    UTL_DeleteCursor               (pincur);
  }

  UTL_AddFcmConfigAction         (FcmConfig_H, 1, FCMARG.fcmaction);
  UTL_SetFcmConfigPfcNoClear     (FcmConfig_H, FCMARG.pfcnoclear);
  UTL_SetFcmConfigRealTimeCountEnable(FcmConfig_H, FCMARG.realtimecount);
  UTL_SetFcmConfigStoreInhSignal (FcmConfig_H, FCMARG.storeinh);
  UTL_SetFcmConfigFcsmMaxStoreCnt(FcmConfig_H, FCMARG.storecnt);

  UTL_SendFcmConfig              (FcmConfig_H);
  UTL_DeleteHandle               (FcmConfig_H);

  return;
}

void fcm_config_std_or_cfm(TEST_testitem *testarg)
{
  int i;

  fcm_config_std(testarg);

  CfmConfigHandle CfmConfig_H = UTL_GetCfmConfigHandle();
  srand((unsigned int)time(NULL));
  if(rand()&0x1){
    printf("CFM config:	ON\n");

    for(i=0; i<FCMARG.ybits; i++){
      UTL_SetCfmConfigAddrAssign   (CfmConfig_H, i, UT_SIG_Y(i));
    }
    for(i=0; i<MIN(16-FCMARG.ybits, FCMARG.xbits); i++){
      UTL_SetCfmConfigAddrAssign   (CfmConfig_H, i+FCMARG.ybits, UT_SIG_X(i));
    }
  }
  else{
    printf("CFM config:	OFF\n");
  }
  UTL_SendCfmConfig              (CfmConfig_H);
  UTL_DeleteHandle               (CfmConfig_H);

  return;
}

void fcm_reg_std(TEST_testitem *testarg)
{
  set_reg(UT_REG_XMAX, (0x1<<FCMARG.xbits)-1);
  set_reg(UT_REG_YMAX, (0x1<<FCMARG.ybits)-1);
  set_reg(UT_REG_IDX1, (0x1<<(FCMARG.xbits+FCMARG.ybits))-2);		//IDX1 for JNI1(X/Y loop)
  set_reg(UT_REG_IDX2, (0x1<<FCMARG.xbits)-2);				//IDX2 for JNI2(X loop)
  set_reg(UT_REG_IDX3, (0x1<<FCMARG.ybits)-2);				//IDX3 for JNI3(Y loop)
  return;
}

static int fcm_mconfig(){
  int mconfig[] = {32, 16, 8}; //X32, X16, X8
  int reg = UTTB_HReg_Read(0xb15f6000); //Pg_FmXferMode
  //printf("Pg_FmXferMode 0x%08x\n", reg);
  return(mconfig[(reg>>8)&0x3]);
}

void fcm_reg_fifo(TEST_testitem *testarg)
{
  int fifosize;
  int mconfig = fcm_mconfig();
  fifosize = 32*1024*FCMARG.burstlength;
  if(FCMARG.burstlength==4 && mconfig==32){
    fifosize = 64*1024;
  }
  else if(FCMARG.burstlength>=8){
    fifosize = 256*1024/(mconfig/8);
  }
  fifosize/=2;
  printf("FailFIFO:\t%dk\n", fifosize/1024);
  fflush(stdout);

  int fifoloop = fifosize/(0x1<<FCMARG.ybits);
  set_reg(UT_REG_XMAX, (0x1<<FCMARG.xbits)-1);
  set_reg(UT_REG_YMAX, (0x1<<FCMARG.ybits)-1);
  set_reg(UT_REG_IDX1, fifoloop-2);				//IDX1 for JNI1(X loop up to fifosize)
  set_reg(UT_REG_IDX2, (0x1<<FCMARG.ybits)/FCMARG.burstlength-2-1);	//IDX2 for JNI2(Y loop)
  int idx3 = (0x1<<FCMARG.xbits)/fifoloop-2;
  if(idx3<0x0){
    idx3=0x0;
  }
  set_reg(UT_REG_IDX3, idx3);					//IDX3 for JNI3(X loop)
  set_reg(UT_REG_IDX4, FCMARG.ddrmode==UT_OFF ? (FCMARG.burstlength/8-2-2):(FCMARG.burstlength/16-2-2)); //IDX4 for SDR/BL32 or upper, DDR/BL64 or upper
  set_reg(UT_REG_D1  , FCMARG.burstlength);		//D1A  for YC<YC+D1A

  return;
}

void fcm_reg_burst(TEST_testitem *testarg){
  set_reg(UT_REG_XMAX, (0x1<<FCMARG.xbits)-1);
  set_reg(UT_REG_YMAX, (0x1<<FCMARG.ybits)-1);
  set_reg(UT_REG_IDX1, (0x1<<FCMARG.xbits)-2);				//IDX1 for JNI1(X loop)
  set_reg(UT_REG_IDX2, (0x1<<FCMARG.ybits)/FCMARG.burstlength-2-1);	//IDX2 for JNI2(Y loop)
  set_reg(UT_REG_IDX4, FCMARG.ddrmode==UT_OFF ? (FCMARG.burstlength/8-2-2):(FCMARG.burstlength/16-2-2)); //IDX4 for SDR/BL32 or upper, DDR/BL64 or upper
  set_reg(UT_REG_D1  , FCMARG.burstlength);				//D1A  for YC<YC+D1A
  return;
}

void fcm_config_pfc(TEST_testitem *testarg)
{
  FcmConfigHandle FcmConfig_H = UTL_GetFcmConfigHandle();
  UTL_UpdateFcmConfig       (FcmConfig_H);
  UTL_SetFcmConfigAddrAssign(FcmConfig_H, FCMARG.xbits+FCMARG.ybits  , UT_SIG_X(FCMARG.xbits));
  UTL_SetFcmConfigAddrAssign(FcmConfig_H, FCMARG.xbits+FCMARG.ybits+1, UT_SIG_Y(FCMARG.ybits));
  UTL_SendFcmConfig         (FcmConfig_H);
  UTL_DeleteHandle          (FcmConfig_H);
  return;
}

void fcm_config_pfc2(TEST_testitem *testarg)
{
  fcm_config_pfc(testarg);
  set_reg(UT_REG_IDX1, (0x1<<(FCMARG.ybits+1))-2);
  set_reg(UT_REG_IDX2, (0x1<<(FCMARG.xbits+1))-2);
  return;
}

void fcm_read_check_ckbd(TEST_testitem *testarg){
  unsigned long exp_a, exp_b;

  exp_a = 0xaaaaaaaa;
  exp_b = 0x55555555;

  if(FCMARG.fmbitcomp>1){
    exp_a = 0xffff;
    exp_b = 0xffff;
  }

  exp_a&=((0x1<<(SOCKET.dutblock_iopin_count[0]/FCMARG.fmbitcomp))-1);
  exp_b&=((0x1<<(SOCKET.dutblock_iopin_count[0]/FCMARG.fmbitcomp))-1);

  fcm_read_check(testarg, exp_a, exp_b);

  return;
}

void fcm_read_check_ckbd_bar(TEST_testitem *testarg){
  unsigned long exp_a, exp_b;

  exp_a = 0x55555555;
  exp_b = 0xaaaaaaaa;

  if(FCMARG.fmbitcomp>1){
    exp_a = 0xffff;
    exp_b = 0xffff;
  }

  exp_a&=((0x1<<(SOCKET.dutblock_iopin_count[0]/FCMARG.fmbitcomp))-1);
  exp_b&=((0x1<<(SOCKET.dutblock_iopin_count[0]/FCMARG.fmbitcomp))-1);

  fcm_read_check(testarg, exp_a, exp_b);

  return;
}

void fcm_read_check_allfail(TEST_testitem *testarg){
  unsigned long exp_a, exp_b;

  exp_a = 0xffffffff;
  exp_b = 0xffffffff;

  exp_a&=((0x1<<(SOCKET.dutblock_iopin_count[0]/FCMARG.fmbitcomp))-1);
  exp_b&=((0x1<<(SOCKET.dutblock_iopin_count[0]/FCMARG.fmbitcomp))-1);

  fcm_read_check(testarg, exp_a, exp_b);

  return;
}

void fcm_read_check_allpass(TEST_testitem *testarg){
  fcm_read_check(testarg, 0x0, 0x0);
  return;
}

static double fcm_busy_wait(){
  CheckButton ov;
  DSlider t;

  UTL_StartTimer(UT_TIMER_R1US);
  UTVTC_FcmCtrl_WaitNoLimit();
  t = UTL_ReadTimer(&ov);

  return(t);
}

void fcm_preset_all0_check(TEST_testitem *testarg){
  fcm_preset_all(0);
  fcm_pfc_check(testarg);
  return;
}

void fcm_preset_all1_check(TEST_testitem *testarg){
  fcm_preset_all(1);
  fcm_pfc_check(testarg);
  return;
}

void fcm_preset_inuse0_check(TEST_testitem *testarg){
  fcm_preset_inuse(0);
  fcm_pfc_check(testarg);
  return;
}

void fcm_preset_inuse1_check(TEST_testitem *testarg){
  fcm_preset_inuse(1);
  fcm_pfc_check(testarg);
  return;
}

void fcm_count_check(TEST_testitem *testarg){
  RadioButton fmbit;
  int dutblock;
  USlider count;
  USlider expcount;
  DutCursor dutc;
  UT_DUT dut = 0;
  int result = 0;
  int i;

  FcmAccessHandle FcmAccess_H = UTL_GetFcmAccessHandle();
  UTL_SetFcmAccessAction             (FcmAccess_H, 1);
  UTL_SetFcmAccessAllBit             (FcmAccess_H, UT_OFF);
  UTL_SetFcmAccessBitMode            (FcmAccess_H, UT_FCM_BITMODE_BLOCK);
  UTL_SetFcmAccessAutoAddrAssignMode (FcmAccess_H, UT_ON);
  UTL_SetFcmAccessXAddr              (FcmAccess_H, 0x0, (0x1<<FCMARG.xbits)-1);
  UTL_SetFcmAccessYAddr              (FcmAccess_H, 0x0, (0x1<<FCMARG.ybits)-1);

  USlider full = 0x1<<(FCMARG.xbits+FCMARG.ybits);
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      set_result(dut, -1); //skip
      continue;
    }

    result = 0;
    UTL_SetFcmAccessDut(FcmAccess_H, dut);
    for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
      for(fmbit=SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp; fmbit<SOCKET.dutblock_iopin_count[0]*(dutblock+1)/FCMARG.fmbitcomp; fmbit++){
        if(fmbit%FMBLKBIT==0){
          UTL_SetFcmAccessBitBlock(FcmAccess_H, fmbit/FMBLKBIT+1);
          UTL_CntFcmFailAddr(FcmAccess_H);
        }

        if(FCMARG.failratio>=0){
          expcount = (double)full*FCMARG.failratio+0.5;
        }
        else{ // for FCM FAIL COUNT READ CHECK (BY BIT)
          expcount = (double)full*pow(0.25,(int)((fmbit*FCMARG.fmbitcomp%SOCKET.dutblock_iopin_count[0])/3)+1)*(3-((fmbit*FCMARG.fmbitcomp%SOCKET.dutblock_iopin_count[0])%3))+0.5;
        }
 
        if(UTL_GetFcmFailAddrCntOverflow(fmbit)==UT_OFF){
          count = UTL_GetFcmFailAddrCnt(fmbit);
          if(DEBUG==1) printf("\tDUT%2d BLK%d FMBIT%2d : FAIL COUNT = 0x%08x\n", dut, dutblock, fmbit, count);
          if(count!=expcount){
            printf("\tDUT%2d BLK%d FMBIT%2d : FAIL COUNT = 0x%08x (EXP=0x%08x) FAIL***\n", dut, dutblock, fmbit, count, expcount);
            set_result(dut, 1);
            result|=1;
          }
        }
        else{
          printf("\tDUT%2d BLK%d FMBIT%2d : OVERFLOW ERROR!!\n", dut, dutblock, fmbit);
          result|=1;
        }
      }
      fflush(stdout);
    }
    set_result(dut, result);
  }
  fflush(stdout);
  UTL_DeleteHandle(FcmAccess_H);
  UTL_DeleteCursor(dutc);

  return;
}

void fcm_delay_check(TEST_testitem *testarg){
  unsigned long x_fail_addr;
  DutCursor dutc;
  UT_DUT dut = 0;
  RadioButton fmbit;
  int result = 0;

  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      set_result(dut, -1); //skip
      continue;
    }

    result = 0;
    for(fmbit=0; fmbit<SOCKET.dut_iopin_count/FCMARG.fmbitcomp; fmbit++){
      result|=read_fail_address_delay(dut, fmbit, 0xf, 0x0);
    }
    set_result(dut, result);
    if(DEBUG==1) fcm_print_delay_log(testarg, dut, FCMARG.cpedelay, 0xf);
  }
  UTL_DeleteCursor(dutc);

  return;
}

void fcm_search_check(TEST_testitem *testarg){
  int i;
  int fail_count = 0;

  USlider x_fail_addr;
  USlider y_fail_addr;

  DutCursor dutc = UTL_GetDutCursor(UT_CDUT);
  UT_DUT  dut = 0;

  RadioButton fmbit;
  AddrCursor addrcur;
  UT_ADDR  addr = 0;
  int print_addr_max = 0;

  FcmAccessHandle FcmAccess_H = UTL_GetFcmAccessHandle();
  UTL_ClearFcmAccessBit      (FcmAccess_H);
  UTL_SetFcmAccessAction     (FcmAccess_H, 1);
  UTL_SetFcmAccessAllDut     (FcmAccess_H, UT_OFF);
  UTL_SetFcmAccessAllBit     (FcmAccess_H, UT_OFF);
  UTL_SetFcmAccessAutoAddrAssignMode(FcmAccess_H, UT_ON);
  UTL_SetFcmAccessXAddr      (FcmAccess_H, 0x0, (0x1<<FCMARG.xbits)-1);
  UTL_SetFcmAccessYAddr      (FcmAccess_H, 0x0, (0x1<<FCMARG.ybits)-1);
  UTL_SetFcmAccessApLink     (FcmAccess_H, UT_FCM_APLINK_XYZ);

  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      set_result(dut, -1); //skip
      continue;
    }

    UTL_SetFcmAccessDut(FcmAccess_H, dut);
    for(fmbit=0; fmbit<SOCKET.dut_iopin_count/FCMARG.fmbitcomp; fmbit++){
      UTL_ClearFcmAccessBit(FcmAccess_H);
      UTL_AddFcmAccessBit(FcmAccess_H, fmbit);
      UTL_CntFcmFailAddr(FcmAccess_H);
      fail_count = UTL_GetFcmFailAddrCnt(fmbit);

      if(fail_count!=0){
        if(fail_count>FCM_ACCESS_SEARCH_MAX_CNT){
          fail_count = FCM_ACCESS_SEARCH_MAX_CNT;
        }
        UTL_SetFcmAccessSearchMaxCnt(FcmAccess_H, fail_count);
        UTL_SearchFcmFailAddr(FcmAccess_H);
        addrcur = UTL_GetFcmFailAddr(fmbit);
        print_addr_max = 0;
        while((addr=UTL_NextAddr(addrcur))!=UT_NOMORE){
          x_fail_addr = UTL_GetXAddr(addr);
          y_fail_addr = UTL_GetYAddr(addr);
          if(DEBUG==1){
            if(print_addr_max<=3){
              printf("\tDUT%2d FMBIT%2d : X=0x%x, Y=0x%x\n", dut, fmbit, x_fail_addr, y_fail_addr); fflush(stdout);
            }
          }

          if(x_fail_addr!=y_fail_addr){
            printf("\tDUT%2d FMBIT%2d : X=0x%x, Y=0x%x\n", dut, fmbit, x_fail_addr, y_fail_addr); fflush(stdout);
            set_result(dut, 1);
            goto fcm_search_check_fail;
          }
          print_addr_max++;
        }
        UTL_DeleteCursor(addrcur);
      }
      else{
        if(DEBUG==1) {printf("NO FAIL!!\n"); fflush(stdout);}
        set_result(dut, 1);
        goto fcm_search_check_fail;
      }
    }
    set_result(dut, 0);
    fcm_search_check_fail: ;
  }
  UTL_DeleteHandle(FcmAccess_H);
  UTL_DeleteCursor(dutc);

  return;
}

void fcm_pfc_check(TEST_testitem *testarg)
{
  int i, j, tmp;
  RadioButton fmbit;
  int io_loop;
  USlider pfc;
  USlider expcount;
  DutCursor dutc;
  UT_DUT dut = 0;
  int result;

  FcmAccessHandle FcmAccess_H = UTL_GetFcmAccessHandle();
  UTL_ClearFcmAccessBit              (FcmAccess_H);
  UTL_SetFcmAccessAction             (FcmAccess_H, 1);
  UTL_SetFcmAccessAllDut             (FcmAccess_H, UT_OFF);
  UTL_SetFcmAccessAutoAddrAssignMode (FcmAccess_H, UT_ON);
  UTL_SetFcmAccessXAddr              (FcmAccess_H, 0x0, (0x1<<FCMARG.xbits)-1);
  UTL_SetFcmAccessYAddr              (FcmAccess_H, 0x0, (0x1<<FCMARG.ybits)-1);
  if(FCMARG.realtimecount==UT_ON){
    UTL_SetFcmAccessPfcMode            (FcmAccess_H, UT_FCM_PFCMODE_REALTIME);
  }
  else{
    UTL_SetFcmAccessPfcMode            (FcmAccess_H, UT_FCM_PFCMODE_BYCOUNT_DIVIDED_AREA);
    UTL_ParallelFailCountFcm           (FcmAccess_H);
  }

  UTL_SetFcmAccessAllBit             (FcmAccess_H, FCMARG.allbit);
  if(FCMARG.allbit==UT_ON){
    io_loop = 1; //ALL BIT CHECK
  }
  else{
    io_loop = SOCKET.dut_iopin_count/FCMARG.fmbitcomp;
  }

  USlider full = 0x1<<(FCMARG.xbits+FCMARG.ybits);
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      set_result(dut, -1); //skip
      continue;
    }

    result = 0;
    UTL_SetFcmAccessDut                (FcmAccess_H, dut);
    for(fmbit=0; fmbit<io_loop; fmbit++){
      if(FCMARG.allbit==UT_OFF){
        UTL_ClearFcmAccessBit          (FcmAccess_H);
        UTL_AddFcmAccessBit            (FcmAccess_H, fmbit);

        if(FCMARG.failratio>=0){
          expcount = (double)full*FCMARG.failratio+0.5;
        }
        else{ // for FCM REALTIME PFC CHECK (BY BIT)
          expcount = (double)full*pow(0.25,(int)((fmbit*FCMARG.fmbitcomp%SOCKET.dutblock_iopin_count[0])/3)+1)*(3-((fmbit*FCMARG.fmbitcomp%SOCKET.dutblock_iopin_count[0])%3))+0.5;
        }
      }
      else{ //FCMARG.allbit==UT_ON
        if(FCMARG.failratio>=0){
          expcount = full*(SOCKET.dut_iopin_count/FCMARG.fmbitcomp); //FCM REALTIME PFC CHECK (ALL FAIL & ALL BIT)
        }
        else{ //FCM REALTIME PFC CHECK (BY BIT & ALL BIT)
          expcount = 0;
          for(i=0; i<SOCKET.dut_iopin_count/FCMARG.fmbitcomp; i++){
            expcount+=(double)full*pow(0.25,(int)((i*FCMARG.fmbitcomp%SOCKET.dutblock_iopin_count[0])/3)+1)*(3-((i*FCMARG.fmbitcomp%SOCKET.dutblock_iopin_count[0])%3))+0.5;
          }
        }
      }

      if(UTL_GetFcmParallelFailCountOverflow(FcmAccess_H)==UT_OFF){
        pfc = UTL_GetFcmParallelFailCount(FcmAccess_H);
        if(DEBUG==1){
          printf("\tDUT%2d FMBIT%2d : PFC = 0x%08x\n", dut, fmbit, pfc);
        }
        if(pfc!=expcount){
          printf("\tDUT%2d FMBIT%2d : PFC = 0x%08x (EXP=0x%08x) FAIL***\n", dut, fmbit, pfc, expcount);
          result|=1;
        }
      }
      else{
        printf("\tDUT%2d FMBIT%2d : OVERFLOW ERROR!!\n", dut, fmbit);
        result|=1;
      }
    }
    set_result(dut, result);
  }
  fflush(stdout);
  UTL_DeleteHandle(FcmAccess_H);
  UTL_DeleteCursor(dutc);

  return;
}

static void fcm_pfc_clear(TEST_testitem *testarg){
  FcmConfigHandle FcmConfig_H = UTL_GetFcmConfigHandle();
  UTL_SetFcmConfigPfcNoClear     (FcmConfig_H, UT_OFF);
  UTL_SendFcmConfig              (FcmConfig_H);
  UTL_DeleteHandle               (FcmConfig_H);

  FctHandle Fct_H3 = UTL_GetFctHandle();
  if(FCMARG.ilmode==8){
    UTL_SetFctMpatName  (Fct_H3, "pat_nop_8way.mpa");
  }
  else{
    UTL_SetFctMpatName  (Fct_H3, "pat_nop.mpa");
  }
  UTL_SetFctFailInhibit (Fct_H3, UT_ON);
  UTL_SetFctStartPc     (Fct_H3, 0x0);
  UTL_MeasFct           (Fct_H3);
  UTL_DeleteHandle      (Fct_H3);

  return;
}

void fcm_pfc_no_clear_check(TEST_testitem *testarg){
  int i = 0;

  fcm_pfc_clear(testarg);
  fcm_config_std(testarg);
  fcm_reg_std(testarg);

  FctHandle Fct_H2 = UTL_GetFctHandle();
  UTL_SetFctNoClear     (Fct_H2, UT_ON);
  UTL_SetFctFailInhibit (Fct_H2, UT_ON);
  UTL_SetFctMpatName    (Fct_H2, FCMARG.mpat);
  UTL_SetFctStartPc     (Fct_H2, FCMARG.pc);
  for(i=0; i<FCMARG.failratio; i++){
    UTL_MeasFct           (Fct_H2);
  }
  UTL_DeleteHandle      (Fct_H2);

  fcm_pfc_check(testarg);
  fcm_pfc_clear(testarg);

  return;
}

void fcm_pfc_div_check(TEST_testitem *testarg){
  UT_DUT dut = 0;
  DutCursor dutc;

  int i, j;
  RadioButton fmbit;
  USlider pfc;
  FcmAccessHandle FcmAccess_H;

  double period1, period2;
  int overflow;
  int result[MAXDUTCNT] = {0};

  RadioButton sig[] = {UT_SIG_FL, UT_SIG_FH, UT_SIG_NONE};
  char *sigw[] = {"FIXL", "FIXH", "NONE"};
  USlider exp_count[3][3];
  exp_count[0][0] = 0x01001000; //FIXL/FIXL
  exp_count[1][0] = 0x00C00000; //FIXH/FIXL
  exp_count[0][1] = 0x00300000; //FIXL/FIXH
  exp_count[1][1] = 0x00080000; //FIXH/FIXH
  exp_count[2][0] = exp_count[0][0]+exp_count[1][0]; //NONE/FIXL
  exp_count[2][1] = exp_count[0][1]+exp_count[1][1]; //NONE/FIXH
  exp_count[0][2] = exp_count[0][0]+exp_count[0][1]; //FIXL/NONE
  exp_count[1][2] = exp_count[1][0]+exp_count[1][1]; //FIXH/NONE
  exp_count[2][2] = exp_count[2][0]+exp_count[2][1]; //NONE/NONE

  UTL_StartTimer(UT_TIMER_R1US);

  FcmAccess_H = UTL_GetFcmAccessHandle();
  UTL_SetFcmAccessAutoAddrAssignMode(FcmAccess_H, UT_ON);
  UTL_SetFcmAccessXAddr(FcmAccess_H, 0x0, (0x1<<(FCMARG.xbits+1))-1);
  UTL_SetFcmAccessYAddr(FcmAccess_H, 0x0, (0x1<<(FCMARG.ybits+1))-1);
  UTL_SetFcmAccessAllDut                 (FcmAccess_H, UT_OFF);
  UTL_SetFcmAccessAllBit                 (FcmAccess_H, UT_OFF);

  for(i=0; i<3; i++){
    for(j=0; j<3; j++){
      UTL_SetFcmAccessPfcMode(FcmAccess_H, UT_FCM_PFCMODE_BYCOUNT_DIVIDED_AREA);
      UTL_SetFcmAccessAreaDivision(FcmAccess_H, FCMARG.xbits+FCMARG.ybits  , sig[i]);
      UTL_SetFcmAccessAreaDivision(FcmAccess_H, FCMARG.xbits+FCMARG.ybits+1, sig[j]);

      period1 = UTL_ReadTimer(&overflow);
      UTL_ParallelFailCountFcm(FcmAccess_H);
      period2 = UTL_ReadTimer(&overflow);
      printf("%s/%s EXEC_TIME %f\n", sigw[i], sigw[j], period2 - period1);

      dutc = UTL_GetDutCursor(UT_CDUT);
      while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
        if(is_captured(testarg, dut)==UT_OFF){
          result[dut] = -1; //skip
          continue;
        }

        UTL_SetFcmAccessDut(FcmAccess_H, dut);
        for(fmbit=0; fmbit<SOCKET.dut_iopin_count/FCMARG.fmbitcomp; fmbit++){
          UTL_ClearFcmAccessBit(FcmAccess_H);
          UTL_AddFcmAccessBit(FcmAccess_H, fmbit);
          if(UTL_GetFcmParallelFailCountOverflow(FcmAccess_H)==UT_OFF){
            pfc = UTL_GetFcmParallelFailCount(FcmAccess_H);
            if(pfc!=exp_count[i][j]){
              if(DEBUG==1){printf("\tDUT%2d FMBIT%2d : PFC = 0x%08x (0x%x) FAIL***\n", dut, fmbit, pfc, exp_count[i][j]);}
              result[dut]|=0x1;
            }
            else{
              if(DEBUG==1){printf("\tDUT%2d FMBIT%2d : PFC = 0x%08x\n", dut, fmbit, pfc);}
            }
          }
          else{
            printf("\tDUT%2d FMBIT%2d : OVERFLOW ERROR!!\n", dut, fmbit);
            result[dut]|=0x1;
          }
          fflush(stdout);
        }
      }
      UTL_DeleteCursor(dutc);
    }
  }
  UTL_DeleteHandle(FcmAccess_H);

  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    set_result(dut, result[dut]);
  }
  UTL_DeleteCursor(dutc);

  return;
}

void fcm_pfc_time_check(TEST_testitem *testarg){
  USlider pfc1, pfc2, pfc3;
  int overflow;
  double period1, period2;
  double time1, time2, time3;
  double overhead, ratio;
  int result = 1;
  int i;

  DutCursor dutc = UTL_GetDutCursor(UT_CDUT);
  UT_DUT dut;
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_ON){
      break;
    }
  }
  UTL_DeleteCursor(dutc);

  if(dut!=UT_NOMORE){
    UTL_StartTimer(UT_TIMER_R1US);

    for(i=0; i<10; i++){
      FcmAccessHandle FcmAccess_H = UTL_GetFcmAccessHandle();
      UTL_SetFcmAccessAutoAddrAssignMode(FcmAccess_H, UT_ON);
      UTL_SetFcmAccessXAddr        (FcmAccess_H, 0x0, (0x1<<(FCMARG.xbits+1))-1);
      UTL_SetFcmAccessYAddr        (FcmAccess_H, 0x0, (0x1<<(FCMARG.ybits+1))-1);
      UTL_SetFcmAccessPfcMode      (FcmAccess_H, UT_FCM_PFCMODE_BYCOUNT_DIVIDED_AREA);
      UTL_SetFcmAccessAreaDivision (FcmAccess_H, FCMARG.xbits+FCMARG.ybits  , UT_SIG_NONE);
      UTL_SetFcmAccessAreaDivision (FcmAccess_H, FCMARG.xbits+FCMARG.ybits+1, UT_SIG_NONE);
      UTL_ClearFcmAccessBit        (FcmAccess_H);
      UTL_SetFcmAccessAllDut       (FcmAccess_H, UT_OFF);
      UTL_SetFcmAccessDut          (FcmAccess_H, dut);
      UTL_SetFcmAccessAllBit       (FcmAccess_H, UT_OFF);
      UTL_AddFcmAccessBit          (FcmAccess_H, 0);
   
      period1 = UTL_ReadTimer(&overflow);
      UTL_ParallelFailCountFcm(FcmAccess_H); // ALL
      period2 = UTL_ReadTimer(&overflow);
      time1 = period2 - period1;
      if(UTL_GetFcmParallelFailCountOverflow(FcmAccess_H)==UT_OFF){
        pfc1 = UTL_GetFcmParallelFailCount(FcmAccess_H);
      }
      else{
        printf("OVERFLOW ERROR!!\n");
        pfc1 = -1;
      }
   
      UTL_SetFcmAccessAreaDivision (FcmAccess_H, FCMARG.xbits+FCMARG.ybits  , UT_SIG_NONE);
      UTL_SetFcmAccessAreaDivision (FcmAccess_H, FCMARG.xbits+FCMARG.ybits+1, UT_SIG_FL);
   
      period1 = UTL_ReadTimer(&overflow);
      UTL_ParallelFailCountFcm(FcmAccess_H); // 1/2
      period2 = UTL_ReadTimer(&overflow);
      time2 = period2 - period1;
      if(UTL_GetFcmParallelFailCountOverflow(FcmAccess_H)==UT_OFF){
        pfc2 = UTL_GetFcmParallelFailCount(FcmAccess_H);
      }
      else{
        printf("OVERFLOW ERROR!!\n");
        pfc2 = -1;
      }
   
      UTL_SetFcmAccessAreaDivision (FcmAccess_H, FCMARG.xbits+FCMARG.ybits  , UT_SIG_FL);
      UTL_SetFcmAccessAreaDivision (FcmAccess_H, FCMARG.xbits+FCMARG.ybits+1, UT_SIG_FL);
   
      period1 = UTL_ReadTimer(&overflow);
      UTL_ParallelFailCountFcm(FcmAccess_H); // 1/4
      period2 = UTL_ReadTimer(&overflow);
      time3 = period2 - period1;
      if(UTL_GetFcmParallelFailCountOverflow(FcmAccess_H)==UT_OFF){
        pfc3 = UTL_GetFcmParallelFailCount(FcmAccess_H);
      }
      else{
        printf("OVERFLOW ERROR!!\n");
        pfc3 = -1;
      }
      UTL_DeleteHandle(FcmAccess_H);
  
      overhead = 2*time2-time1;
      ratio = (time3-overhead)/(time1-overhead);
      if(DEBUG==1){
        printf("\tXBIT=%d+1 YBIT=%d+1 ALL=%e 1/2=%e -> overhead=%e\n", FCMARG.xbits, FCMARG.ybits, time1, time2, overhead);
        printf("\tXBIT=%d+1 YBIT=%d+1 ALL=%e 1/4=%e -> %4.1f%% (w/o overhead)\n", FCMARG.xbits, FCMARG.ybits, time1, time3, ratio*100);
        printf("\tPFC(ALL) = 0x%08x, PFC(1/2) = 0x%08x, PFC(1/4) = 0x%08x\n", pfc1, pfc2, pfc3);
      }
      fflush(stdout);

      if(fabs(ratio-0.25)<0.02){
        result = 0; //PASS
        break;
      }
      printf("\t****RETRY\n");
    }
  }
  else{
    result = 1; // dut=UT_NOMORE
    printf("DUT=UT_NOMORE\n");
  }

  set_result(dut, result);
  if(result==0){
    testresult_pass4alldut(testarg->testname);
  }
  else{
    testresult_fail4alldut(testarg->testname);
  }

  return;
}

void fcm_preset_time_check(TEST_testitem *testarg){
  double t1, t2, ratio, exp;
  double expall = 817.3e-3;
  int mconfig = fcm_mconfig();

  exp = 1.0/(0x1<<(28-FCMARG.xbits-FCMARG.ybits))/(32/mconfig);
  if(FCMARG.fcmrate==UT_FCM_MS){
    exp/=2;
  }
  else if(FCMARG.fcmrate==UT_FCM_LS || FCMARG.fcmrate==UT_FCM_BS){
    exp/=4;
  }

  fcm_preset_all(0);
  t1 = fcm_busy_wait();
  printf("\nPresetAll\t= %e (exp=%e)\n", t1, expall);

  fcm_preset_inuse(0);
  t2 = fcm_busy_wait();
  printf("PresetInUse\t= %e\n", t2);

  ratio = t2/t1;
  printf("Ratio\t\t= %f% (exp=%f%)", ratio*100, exp*100);

  if((exp-0.01<ratio)&&(ratio<exp+0.01)&&(expall*0.99<t1)&&(t1<expall*1.01)){
    printf("\tPASS\n");
  }
  else{
    printf("\t****FAIL\n");
    testresult_fail4alldut(testarg->testname);
  }

  return;
}

static void preset_ubm(USlider n)
{
  UbmAccessHandle uacsh = UTL_GetUbmAccessHandle();
  UTL_ClearUbmAccessPin(uacsh);
  UTL_PresetUbm(uacsh, n);
  UTL_DeleteHandle(uacsh);
  return;
}

static void write_ubm_rand(TEST_testitem *testarg)
{
  int i, j;
  RadioButton dutblock;
  UT_DUT dut;
  DutCursor dutc;
  USlider dutcnt = UTL_GetDutCount(UT_CDUT);
  USlider size;
  double trial;

  size = UBMSIZE*dutcnt*SOCKET.dutblock_count;
  UBM_DATA = (USlider *)calloc(size, sizeof(USlider));
  trial = 0.0; // for normal distribution
  for(i=0; i<MAXBLKIOCNT/FCMARG.fmbitcomp/2; i++){
    trial+=((double)MAXBLKIOCNT/(MAXBLKIOCNT-i));
  }
  srand((unsigned int)time(NULL));
  for(i=0; i<size; i++){
    for(j=0; j<trial; j++){
      UBM_DATA[i]|=(0x1<<(rand()%MAXBLKIOCNT));
    }
  }

  preset_ubm(0);

  UbmAccessHandle uacsh = UTL_GetUbmAccessHandle();
  UTL_SetUbmAccessBitReverse(uacsh, UT_ON);
  UTL_SetUbmAccessDdrMode(uacsh, UT_ON);
  UTL_SetUbmAccessStartAddr(uacsh, 0x0);
  UTL_SetUbmAccessStopAddr (uacsh, UBMSIZE/2-1);

  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      continue; //skip
    }
    UTL_SetUbmAccessDut(uacsh, dut);

    for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
      UTL_ClearUbmAccessPin(uacsh);
      UTL_SetUbmAccessPin(uacsh, SOCKET.dutblock_iopinlist[dutblock]);
      UTL_WriteUbm(uacsh, &UBM_DATA[UBMSIZE*((dut-1)*(SOCKET.dutblock_count)+dutblock)], sizeof(USlider)*UBMSIZE);
    }
  }
  UTL_DeleteCursor(dutc);

  return;
}

static void fcm_reg_fcsm(TEST_testitem *testarg)
{
  IdxModeHandle imh = UTL_GetIdxModeHandle();
  UTL_SetIdxMode(imh, UT_IDXMODE_IDXLOOP1);
  UTL_SendIdxMode(imh);
  UTL_DeleteHandle(imh);

  set_reg(UT_REG_IDX1, UBMADD_PER_AFMXFER/FCMARG.ilmode/2-1);		// Y loop
  set_reg(UT_REG_IDX2, (int)(1e-6/FCMARG.rate/FCMARG.ilmode+1)-(UBMADD_PER_AFMXFER/FCMARG.ilmode/2));// 1us, AFMXFER to AFMXFER interval
  set_reg(UT_REG_IDX3, FCMARG.storecnt-1);				// x AFMXFER(X loop)
  set_reg(UT_REG_D1  , FCMARG.burstlength);				// D1A  for YC<YC+D1A

  return;
}

static void set_ubm()
{
  UbmConfigHandle useth = UTL_GetUbmConfigHandle();
  UTL_InitializeUbmConfigHandle(useth);
  UTL_ClearUbmConfigFunctionSelect(useth);
  UTL_ClearUbmConfigPin(useth, UT_UBM_UNIT_EXP);
  UTL_ClearUbmConfigJumpAddr(useth, UT_UBM_UNIT_EXP, 0);

  UTL_AddUbmConfigFunctionSelect(useth, UT_UBM_UNIT_EXP, UT_SIG_C(30));
  UTL_SetUbmConfigJumpAddr(useth, UT_UBM_UNIT_EXP, 0, 0x0);
  UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_EXP, 0, UT_SIG_FL); //dummy
  UTL_SetUbmConfigJumpAddr(useth, UT_UBM_UNIT_EXP, 1, 0x0);
  UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_EXP, 1, UT_SIG_FL); //dummy
  UTL_SetUbmConfigJumpAddr(useth, UT_UBM_UNIT_EXP, 2, 0x0);
  UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_EXP, 2, UT_SIG_FL); //dummy

  UTL_SetUbmConfigPin(useth, UT_UBM_UNIT_EXP, SOCKET.all_iopinlist);
  UTL_SetUbmConfigJumpAddr(useth, UT_UBM_UNIT_EXP, 0, 0x0);
  UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_EXP, 0, UT_SIG_C(25));

  UTL_SetUbmConfigDdrMode(useth, UT_ON);
  UTL_SetUbmConfigApAutoIncMode(useth, UT_OFF);
  UTL_SetUbmConfigApIncCycle(useth, UT_SIG_C(31));

  UTL_SendUbmConfig(useth);
  UTL_DeleteHandle(useth);

  return;
}

void fcm_fcsm_set(TEST_testitem *testarg)
{
  set_ubm();
  write_ubm_rand(testarg);
  fcm_reg_fcsm(testarg);
  return;
}

void fcm_fcsm_check(TEST_testitem *testarg)
{
  FcmAccessHandle fah;
  USlider storecnt = 0;
  DutCursor dutc;
  UT_DUT dut;
  int pin;
  int bit;
  int dutblock;
  USlider bytesize;
  USlider *fcsm;
  USlider cntidx;
  USlider exp;
  USlider initfail;
  int result;
  int i, j;
  int fmbit;
  int fmbitcnt = SOCKET.dut_iopin_count/FCMARG.fmbitcomp;
  USlider dutcnt = UTL_GetDutCount(UT_CDUT);
  unsigned int bitmask;
  unsigned int exp_histogram[UBMADD_PER_AFMXFER+1] = {0};

  fah = UTL_GetFcmAccessHandle();
  UTL_SetFcmAccessAllDut(fah, UT_ON);
  UTL_SetFcmAccessBitMode(fah, UT_FCM_BITMODE_NORMAL);
  UTL_SetFcmAccessAllBit(fah, UT_ON);

  if(UTL_ReadFcsmStoreCnt(fah, &storecnt)==UT_ON){
    printf("FCSM store count overflow.\n");
    testresult_fail4alldut(testarg->testname);
    return;
  }
  printf("FCSM store count = %d\n", storecnt);
  if(storecnt!=FCMARG.storecnt){
    printf("FCSM store count mismatch. (exp=%d)\n", FCMARG.storecnt);
    testresult_fail4alldut(testarg->testname);
    return;
  }

  if((int)(UINT_MAX/sizeof(USlider)/storecnt)<dutcnt*fmbitcnt){
    printf("FCSM buffer size overflow. (STORECNT=%d, DUTCNT=%d, FMBITCNT=%d)\n", storecnt, dutcnt, fmbitcnt);
    testresult_fail4alldut(testarg->testname);
    return;
  }
  bytesize = sizeof(USlider)*dutcnt*fmbitcnt*storecnt;
  printf("FCSM buffer size = %u (STORECNT=%d, DUTCNT=%d, FMBITCNT=%d)\n", bytesize, storecnt, dutcnt, fmbitcnt);
  fcsm = (USlider *)malloc(bytesize);
  memset(fcsm, 0x0, bytesize);

  UTL_ReadFcsm(fah, (void *)fcsm, bytesize);
  UTL_DeleteHandle(fah);

  cntidx = 0;
  bitmask = (0x1<<FCMARG.fmbitcomp)-1;
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      cntidx+=(SOCKET.dutblock_count*storecnt*SOCKET.dutblock_iopin_count[0]/FCMARG.fmbitcomp);
      set_result(dut, -1); //skip
      continue;
    }

    result = 0;
    for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
      for(pin=0; pin<SOCKET.dutblock_iopin_count[dutblock]/FCMARG.fmbitcomp; pin++){
        for(i=0; i<storecnt; i++){
          exp = 0;
          for(j=0; j<UBMADD_PER_AFMXFER; j++){
            if(((UBM_DATA[(UBMSIZE*((dut-1)*(SOCKET.dutblock_count)+dutblock))+((i*UBMADD_PER_AFMXFER+j)%UBMSIZE)]>>(pin*FCMARG.fmbitcomp))&bitmask)!=0x0){
              exp++;
            }
          }

          exp_histogram[exp]++;
          if(fcsm[cntidx]!=exp){
            printf("DUT%d BLK%d BIT%02d STORECNT%d\tFCSM[%d]=%d\t(EXP=%d)\t****FAIL\n", dut, dutblock, pin, i, cntidx, fcsm[cntidx], exp);
            result|=1;
            break;
          }
          else{
            if(DEBUG>1){
              printf("DUT%d BLK%d BIT%02d STORECNT%d\tFCSM[%d]=%d\t\tPASS\n", dut, dutblock, pin, i, cntidx, fcsm[cntidx], exp);
            }
          }
          cntidx++;
        }
      }
    }
    set_result(dut, result);
  }
  UTL_DeleteCursor(dutc);
  free(fcsm);
  free(UBM_DATA);

  printf("Counter exp histogram\n");
  for(i=0; i<=UBMADD_PER_AFMXFER; i++){
    printf("%2d: %u\n", i, exp_histogram[i]);
  }

  return;
}

void fcm_fcsm_multimeas_check(TEST_testitem *testarg){
  int i = 0;
  int meascnt = 3;

  fcm_reg_fcsm(testarg);

  FCMARG.storecnt*=meascnt;
  {
    fcm_config_std(testarg);
    UTL_ResetFcsmStoreCnt();
  
    FctHandle Fct_H2 = UTL_GetFctHandle();
    UTL_SetFctNoClear     (Fct_H2, UT_ON);
    UTL_SetFctFailInhibit (Fct_H2, UT_ON);
    UTL_SetFctMpatName    (Fct_H2, FCMARG.mpat);
    UTL_SetFctStartPc     (Fct_H2, FCMARG.pc);
    for(i=0; i<meascnt; i++){
      UTL_MeasFct         (Fct_H2);
      set_reg(UT_REG_CFLG, 0x1);
    }
    UTL_DeleteHandle      (Fct_H2);
  
    fcm_fcsm_check(testarg);
  }
  FCMARG.storecnt/=meascnt; //recover

  return;
}

static void write_ubm_perdut(TEST_testitem *testarg)
{
  int i, j, k;
  RadioButton dutblock;
  UT_DUT dut;
  DutCursor dutc;
  USlider dutcnt = UTL_GetDutCount(UT_CDUT);
  USlider size;

  size = MAXCLDCNT*MAXBLKCNT*MAXBLKIOCNT;
  USlider data[size];

  preset_ubm(0);

  UbmAccessHandle uacsh = UTL_GetUbmAccessHandle();
  UTL_SetUbmAccessBitReverse(uacsh, UT_ON);
  UTL_SetUbmAccessDdrMode(uacsh, UT_ON);
  UTL_SetUbmAccessStartAddr(uacsh, 0x0);
  UTL_SetUbmAccessStopAddr (uacsh, size/2-1);

  k = 0;
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      continue; //skip
    }
    UTL_SetUbmAccessDut(uacsh, dut);

    for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
      memset(data, 0x0, sizeof(USlider)*size);
      for(i=0; i<SOCKET.dutblock_iopin_count[dutblock]; i++){
        k++;
        for(j=0; j<k; j++){
          data[j]|=(0x1<<i);
        }
      }

      UTL_ClearUbmAccessPin(uacsh);
      UTL_SetUbmAccessPin(uacsh, SOCKET.dutblock_iopinlist[dutblock]);
      UTL_WriteUbm(uacsh, data, sizeof(USlider)*size);
    }
  }
  UTL_DeleteCursor(dutc);

  return;
}

void fcm_perdut_set(TEST_testitem *testarg)
{
  set_ubm();
  write_ubm_perdut(testarg);

  set_reg(UT_REG_IDX1, MAXCLDCNT*MAXBLKCNT*MAXBLKIOCNT/FCMARG.ilmode/2-1);	// Y loop
  set_reg(UT_REG_D1  , FCMARG.burstlength);									// D1A  for YC<YC+D1A
  return;
}

void fcm_read_check_perdut(TEST_testitem *testarg)
{
  int i, j;
  DutCursor dutc;
  UT_DUT dut = 0;
  RadioButton fmbit;
  int dutblock;
  USlider size;
  USlider *fcm_rdata1;
  USlider *fcm_rdata2;
  int x, y;
  USlider exp_data;
  USlider xsta = 0x0;
  USlider xspa = (0x1<<FCMARG.xbits)-1;
  USlider ysta = 0x0;
  USlider yspa = (0x1<<FCMARG.ybits)-1;

  size = (0x1<<(FCMARG.xbits+FCMARG.ybits));
  fcm_rdata1 = (USlider *)calloc(size, sizeof(USlider));
  fcm_rdata2 = (USlider *)calloc(size, sizeof(USlider));
  USlider fcm_rdata;

  FcmAccessHandle FcmAccess_H1 = UTL_GetFcmAccessHandle();
  UTL_ClearFcmAccessBit          (FcmAccess_H1);
  UTL_SetFcmAccessAction         (FcmAccess_H1, 1);
  UTL_SetFcmAccessAllDut         (FcmAccess_H1, UT_OFF);
  UTL_SetFcmAccessAllBit         (FcmAccess_H1, UT_OFF);
  UTL_SetFcmAccessAutoAddrAssignMode(FcmAccess_H1, UT_ON);
  UTL_SetFcmAccessXAddr          (FcmAccess_H1, xsta, xspa);
  UTL_SetFcmAccessYAddr          (FcmAccess_H1, ysta, yspa);
  UTL_SetFcmAccessApLink         (FcmAccess_H1, UT_FCM_APLINK_XYZ);

  FcmAccessHandle FcmAccess_H2 = UTL_GetFcmAccessHandle();
  UTL_ClearFcmAccessBit          (FcmAccess_H2);
  UTL_SetFcmAccessAction         (FcmAccess_H2, 1);
  UTL_SetFcmAccessAllDut         (FcmAccess_H2, UT_OFF);
  UTL_SetFcmAccessAllBit         (FcmAccess_H2, UT_OFF);
  UTL_SetFcmAccessAutoAddrAssignMode(FcmAccess_H2, UT_ON);
  UTL_SetFcmAccessXAddr          (FcmAccess_H2, xsta, xspa);
  UTL_SetFcmAccessYAddr          (FcmAccess_H2, ysta, yspa);
  UTL_SetFcmAccessApLink         (FcmAccess_H2, UT_FCM_APLINK_XYZ);

  j = 0;
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      set_result(dut, -1); //skip
      continue;
    }

    UTL_SetFcmAccessDut(FcmAccess_H1, dut);
    UTL_SetFcmAccessDut(FcmAccess_H2, dut);
    for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
      UTL_ClearFcmAccessBit(FcmAccess_H1);
      UTL_ClearFcmAccessBit(FcmAccess_H2);
      for(fmbit=SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp; fmbit<SOCKET.dutblock_iopin_count[0]*(dutblock+1)/FCMARG.fmbitcomp; fmbit++){
        if((SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp/FMBLKBIT)==(fmbit/FMBLKBIT)){
          UTL_AddFcmAccessBit(FcmAccess_H1, fmbit);
        }
        else{
          UTL_AddFcmAccessBit(FcmAccess_H2, fmbit);
        }
      }

      UTL_ReadFcm(FcmAccess_H1, fcm_rdata1, size*sizeof(USlider));
      if((SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp/FMBLKBIT)<((SOCKET.dutblock_iopin_count[0]*(dutblock+1)/FCMARG.fmbitcomp-1)/FMBLKBIT)){
        UTL_ReadFcm(FcmAccess_H2, fcm_rdata2, size*sizeof(USlider));
      }
      else{
        memset(fcm_rdata2, 0x0, size*sizeof(USlider));
      }
 
      i = 0;
      if(DEBUG==1){
        for(y=0; y<=3; y++){
          fcm_rdata = (fcm_rdata1[i]>>(SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT))|(fcm_rdata2[i]<<(FMBLKBIT-SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT));
          printf("\tDUT%2d BLK%d : data[0x%08x] = 0x%08x\n", dut, dutblock, i, fcm_rdata);
          i++;
        }
      }
 
      i = 0;
      for(y=ysta; y<=yspa; y++){
        for(x=xsta; x<=xspa; x++){
          if(i<j){
            exp_data = 0xffffffff;
          }
          else if(i-j<32){
            exp_data = 0xffffffff<<((i-j)/FCMARG.fmbitcomp);
          }
          else{
            exp_data = 0x0;
          }
          exp_data&=((0x1<<(SOCKET.dutblock_iopin_count[dutblock]/FCMARG.fmbitcomp))-1);
 
          fcm_rdata = (fcm_rdata1[i]>>(SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT))|(fcm_rdata2[i]<<(FMBLKBIT-SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT));
          if(fcm_rdata!=exp_data){
            printf("\tDUT%2d BLK%d : data[0x%08x] = 0x%08x (EXP=0x%08x) (x=0x%x y=0x%x)\n", dut, dutblock, i, fcm_rdata, exp_data, x, y);
            fflush(stdout);
            set_result(dut, 1);
            goto fcm_read_fail_perdut;
          }
          i++;
        }
      }

      j+=SOCKET.dutblock_iopin_count[dutblock];
    }
    set_result(dut, 0);
    fcm_read_fail_perdut: ;
  }
  UTL_DeleteCursor(dutc);
  UTL_DeleteHandle(FcmAccess_H1);
  UTL_DeleteHandle(FcmAccess_H2);
  free(fcm_rdata1);
  free(fcm_rdata2);

  return;
}

void fcm_count_check_perdut(TEST_testitem *testarg)
{
  RadioButton fmbit;
  int dutblock;
  USlider count;
  USlider expcount;
  DutCursor dutc;
  UT_DUT dut = 0;
  int result = 0;
  int i;

  FcmAccessHandle FcmAccess_H = UTL_GetFcmAccessHandle();
  UTL_SetFcmAccessAction             (FcmAccess_H, 1);
  UTL_SetFcmAccessAllBit             (FcmAccess_H, UT_OFF);
  UTL_SetFcmAccessBitMode            (FcmAccess_H, UT_FCM_BITMODE_BLOCK);
  UTL_SetFcmAccessAutoAddrAssignMode (FcmAccess_H, UT_ON);
  UTL_SetFcmAccessXAddr              (FcmAccess_H, 0x0, (0x1<<FCMARG.xbits)-1);
  UTL_SetFcmAccessYAddr              (FcmAccess_H, 0x0, (0x1<<FCMARG.ybits)-1);

  i = 0;
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      set_result(dut, -1); //skip
      continue;
    }

    result = 0;
    UTL_SetFcmAccessDut(FcmAccess_H, dut);
    for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
      for(fmbit=SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp; fmbit<SOCKET.dutblock_iopin_count[0]*(dutblock+1)/FCMARG.fmbitcomp; fmbit++){
        i++;
        expcount = i*FCMARG.fmbitcomp;
 
        if(fmbit%FMBLKBIT==0){
          UTL_SetFcmAccessBitBlock(FcmAccess_H, fmbit/FMBLKBIT+1);
          UTL_CntFcmFailAddr(FcmAccess_H);
        }
        if(UTL_GetFcmFailAddrCntOverflow(fmbit)==UT_OFF){
          count = UTL_GetFcmFailAddrCnt(fmbit);
          if(DEBUG==1) printf("\tDUT%2d BLK%d FMBIT%2d : FAIL COUNT = 0x%08x\n", dut, dutblock, fmbit, count);
          if(count!=expcount){
            printf("\tDUT%2d BLK%d FMBIT%2d : FAIL COUNT = 0x%08x (EXP=0x%08x) FAIL***\n", dut, dutblock, fmbit, count, expcount);
            set_result(dut, 1);
            result|=1;
          }
        }
        else{
          printf("\tDUT%2d BLK%d FMBIT%2d : OVERFLOW ERROR!!\n", dut, dutblock, fmbit);
          result|=1;
        }
      }
      fflush(stdout);
    }
    set_result(dut, result);
  }
  fflush(stdout);
  UTL_DeleteHandle(FcmAccess_H);
  UTL_DeleteCursor(dutc);

  return;
}

void fcm_pfc_check_perdut(TEST_testitem *testarg)
{
  int i, j, tmp;
  RadioButton fmbit;
  int io_loop;
  USlider pfc;
  USlider expcount;
  DutCursor dutc;
  UT_DUT dut = 0;
  int result;

  FcmAccessHandle FcmAccess_H = UTL_GetFcmAccessHandle();
  UTL_ClearFcmAccessBit              (FcmAccess_H);
  UTL_SetFcmAccessAction             (FcmAccess_H, 1);
  UTL_SetFcmAccessAllDut             (FcmAccess_H, UT_OFF);
  UTL_SetFcmAccessAutoAddrAssignMode (FcmAccess_H, UT_ON);
  UTL_SetFcmAccessXAddr              (FcmAccess_H, 0x0, (0x1<<FCMARG.xbits)-1);
  UTL_SetFcmAccessYAddr              (FcmAccess_H, 0x0, (0x1<<FCMARG.ybits)-1);
  if(FCMARG.realtimecount==UT_ON){
    UTL_SetFcmAccessPfcMode            (FcmAccess_H, UT_FCM_PFCMODE_REALTIME);
  }
  else{
    UTL_SetFcmAccessPfcMode            (FcmAccess_H, UT_FCM_PFCMODE_BYCOUNT_DIVIDED_AREA);
    UTL_ParallelFailCountFcm           (FcmAccess_H);
  }

  UTL_SetFcmAccessAllBit             (FcmAccess_H, FCMARG.allbit);
  if(FCMARG.allbit==UT_ON){
    io_loop = 1; //ALL BIT CHECK
  }
  else{
    io_loop = SOCKET.dut_iopin_count/FCMARG.fmbitcomp;
  }

  i = 0;
  USlider full = 0x1<<(FCMARG.xbits+FCMARG.ybits);
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      set_result(dut, -1); //skip
      continue;
    }

    result = 0;
    UTL_SetFcmAccessDut                (FcmAccess_H, dut);
    for(fmbit=0; fmbit<io_loop; fmbit++){
      i++;
      expcount = i*FCMARG.fmbitcomp;

      UTL_ClearFcmAccessBit          (FcmAccess_H);
      UTL_AddFcmAccessBit            (FcmAccess_H, fmbit);
      if(UTL_GetFcmParallelFailCountOverflow(FcmAccess_H)==UT_OFF){
        pfc = UTL_GetFcmParallelFailCount(FcmAccess_H);
        if(DEBUG==1){
          printf("\tDUT%2d FMBIT%2d : PFC = 0x%08x\n", dut, fmbit, pfc);
        }
        if(pfc!=expcount){
          printf("\tDUT%2d FMBIT%2d : PFC = 0x%08x (EXP=0x%08x) FAIL***\n", dut, fmbit, pfc, expcount);
          result|=1;
        }
      }
      else{
        printf("\tDUT%2d FMBIT%2d : OVERFLOW ERROR!!\n", dut, fmbit);
        result|=1;
      }
    }
    set_result(dut, result);
  }
  fflush(stdout);
  UTL_DeleteHandle(FcmAccess_H);
  UTL_DeleteCursor(dutc);

  return;
}

