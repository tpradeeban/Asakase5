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
#include "cfm.h"

#define DEBUG (1)

static void cfm_preset_all(USlider n);
static void cfm_read_check(TEST_testitem *testarg, unsigned long exp_a, unsigned long exp_b);

static void cfm_preset_all(USlider n)
{
  CfmAccessHandle CfmAccess_H=UTL_GetCfmAccessHandle();
  UTL_SetCfmAccessPresetAllMemory (CfmAccess_H, UT_ON);
  UTL_PresetCfm                   (CfmAccess_H, n);
  UTL_DeleteHandle                (CfmAccess_H);
  return;
}

static void cfm_read_check(TEST_testitem *testarg, unsigned long exp_a, unsigned long exp_b)
{
  int i;
  DutCursor dutc;
  UT_DUT dut = 0;
  RadioButton fmbit;
  int dutblock;
  USlider size;
  USlider *cfm_rdata1;
  USlider *cfm_rdata2;
  int x, y;
  USlider exp_data;
  USlider xsta = 0x0;
  USlider xspa = (0x1<<FCMARG.xbits)-1;
  USlider ysta = 0x0;
  USlider yspa = (0x1<<FCMARG.ybits)-1;

  size = (0x1<<(FCMARG.xbits+FCMARG.ybits));
  cfm_rdata1 = (USlider *)calloc(size, sizeof(USlider));
  cfm_rdata2 = (USlider *)calloc(size, sizeof(USlider));
  USlider cfm_rdata;

  CfmAccessHandle CfmAccess_H1 = UTL_GetCfmAccessHandle();
  UTL_ClearCfmAccessBit          (CfmAccess_H1);
  UTL_SetCfmAccessAllDut         (CfmAccess_H1, UT_OFF);
  UTL_SetCfmAccessAllBit         (CfmAccess_H1, UT_OFF);
  for(i=0; i<FCMARG.ybits; i++){
    UTL_SetCfmAccessAddrAssign   (CfmAccess_H1, i, UT_SIG_Y(i));
  }
  for(i=0; i<FCMARG.xbits; i++){
    UTL_SetCfmAccessAddrAssign   (CfmAccess_H1, i+FCMARG.ybits, UT_SIG_X(i));
  }
  UTL_SetCfmAccessXAddr          (CfmAccess_H1, xsta, xspa);
  UTL_SetCfmAccessYAddr          (CfmAccess_H1, ysta, yspa);
  UTL_SetCfmAccessApLink         (CfmAccess_H1, UT_FCM_APLINK_XYZ);

  CfmAccessHandle CfmAccess_H2 = UTL_GetCfmAccessHandle();
  UTL_ClearCfmAccessBit          (CfmAccess_H2);
  UTL_SetCfmAccessAllDut         (CfmAccess_H2, UT_OFF);
  UTL_SetCfmAccessAllBit         (CfmAccess_H2, UT_OFF);
  for(i=0; i<FCMARG.ybits; i++){
    UTL_SetCfmAccessAddrAssign   (CfmAccess_H2, i, UT_SIG_Y(i));
  }
  for(i=0; i<FCMARG.xbits; i++){
    UTL_SetCfmAccessAddrAssign   (CfmAccess_H2, i+FCMARG.ybits, UT_SIG_X(i));
  }
  UTL_SetCfmAccessXAddr          (CfmAccess_H2, xsta, xspa);
  UTL_SetCfmAccessYAddr          (CfmAccess_H2, ysta, yspa);
  UTL_SetCfmAccessApLink         (CfmAccess_H2, UT_FCM_APLINK_XYZ);

  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      set_result(dut, -1); //skip
      continue;
    }

    UTL_SetCfmAccessDut(CfmAccess_H1, dut);
    UTL_SetCfmAccessDut(CfmAccess_H2, dut);
    for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
      UTL_ClearCfmAccessBit(CfmAccess_H1);
      UTL_ClearCfmAccessBit(CfmAccess_H2);
      for(fmbit=SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp; fmbit<SOCKET.dutblock_iopin_count[0]*(dutblock+1)/FCMARG.fmbitcomp; fmbit++){
        if((SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp/FMBLKBIT)==(fmbit/FMBLKBIT)){
          UTL_AddCfmAccessBit(CfmAccess_H1, fmbit);
        }
        else{
          UTL_AddCfmAccessBit(CfmAccess_H2, fmbit);
        }
      }

      UTL_ReadCfm(CfmAccess_H1, cfm_rdata1, size*sizeof(USlider));
      if((SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp/FMBLKBIT)<((SOCKET.dutblock_iopin_count[0]*(dutblock+1)/FCMARG.fmbitcomp-1)/FMBLKBIT)){
        UTL_ReadCfm(CfmAccess_H2, cfm_rdata2, size*sizeof(USlider));
      }
      else{
        memset(cfm_rdata2, 0x0, size*sizeof(USlider));
      }
 
      i=0;
      if(DEBUG==1){
        for(y=0; y<=0x3; y++){
          cfm_rdata = (cfm_rdata1[i]>>(SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT))|(cfm_rdata2[i]<<(FMBLKBIT-SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT));
          printf("\tDUT%2d BLK%d : cfm_data[0x%08x] = 0x%08x\n", dut, dutblock, i, cfm_rdata);
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
 
          cfm_rdata = (cfm_rdata1[i]>>(SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT))|(cfm_rdata2[i]<<(FMBLKBIT-SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT));
          if(cfm_rdata!=exp_data){
            printf("\tDUT%2d BLK%d : cfm_data[0x%08x] = 0x%08x (EXP=0x%08x) (x=0x%x y=0x%x)\n", dut, dutblock, i, cfm_rdata, exp_data, x, y);
            fflush(stdout);
            set_result(dut, 1);
            goto cfm_read_fail;
          }
          i++;
        }
      }
    }
    set_result(dut, 0);
    cfm_read_fail: ;
  }
  UTL_DeleteCursor(dutc);
  UTL_DeleteHandle(CfmAccess_H1);
  UTL_DeleteHandle(CfmAccess_H2);
  free(cfm_rdata1);
  free(cfm_rdata2);

  return;
}

void fcm_config_cfm(TEST_testitem *testarg)
{
  int i;

  fcm_config_std(testarg);

  CfmConfigHandle CfmConfig_H = UTL_GetCfmConfigHandle();
  for(i=0; i<FCMARG.ybits; i++){
    UTL_SetCfmConfigAddrAssign   (CfmConfig_H, i, UT_SIG_Y(i));
  }
  for(i=0; i<FCMARG.xbits; i++){
    UTL_SetCfmConfigAddrAssign   (CfmConfig_H, i+FCMARG.ybits, UT_SIG_X(i));
  }
  UTL_SendCfmConfig              (CfmConfig_H);
  UTL_DeleteHandle               (CfmConfig_H);

  cfm_preset_all(0);

  return;
}

void cfm_read_check_ckbd(TEST_testitem *testarg){
  unsigned long exp_a, exp_b;

  exp_a = 0xaaaaaaaa;
  exp_b = 0x55555555;

  if(FCMARG.fmbitcomp>1){
    exp_a = 0xffff;
    exp_b = 0xffff;
  }

  exp_a&=((0x1<<(SOCKET.dutblock_iopin_count[0]/FCMARG.fmbitcomp))-1);
  exp_b&=((0x1<<(SOCKET.dutblock_iopin_count[0]/FCMARG.fmbitcomp))-1);

  cfm_read_check(testarg, exp_a, exp_b);

  return;
}

void cfm_read_check_ckbd_bar(TEST_testitem *testarg){
  unsigned long exp_a, exp_b;

  exp_a = 0x55555555;
  exp_b = 0xaaaaaaaa;

  if(FCMARG.fmbitcomp>1){
    exp_a = 0xffff;
    exp_b = 0xffff;
  }

  exp_a&=((0x1<<(SOCKET.dutblock_iopin_count[0]/FCMARG.fmbitcomp))-1);
  exp_b&=((0x1<<(SOCKET.dutblock_iopin_count[0]/FCMARG.fmbitcomp))-1);

  cfm_read_check(testarg, exp_a, exp_b);

  return;
}

void cfm_read_check_allfail(TEST_testitem *testarg){
  unsigned long exp_a, exp_b;

  exp_a = 0xffffffff;
  exp_b = 0xffffffff;

  exp_a&=((0x1<<(SOCKET.dutblock_iopin_count[0]/FCMARG.fmbitcomp))-1);
  exp_b&=((0x1<<(SOCKET.dutblock_iopin_count[0]/FCMARG.fmbitcomp))-1);

  cfm_read_check(testarg, exp_a, exp_b);

  return;
}

void cfm_read_check_allpass(TEST_testitem *testarg){
  cfm_read_check(testarg, 0x0, 0x0);
  return;
}

void cfm_preset_all0_check(TEST_testitem *testarg){
  cfm_preset_all(0);
  cfm_count_check(testarg);
  return;
}

void cfm_preset_all1_check(TEST_testitem *testarg){
  cfm_preset_all(1);
  cfm_count_check(testarg);
  return;
}

void cfm_count_check(TEST_testitem *testarg){
  RadioButton fmbit;
  int dutblock;
  USlider count;
  USlider expcount;
  DutCursor dutc;
  UT_DUT dut = 0;
  int result = 0;
  int i;

  CfmAccessHandle CfmAccess_H = UTL_GetCfmAccessHandle();
  UTL_SetCfmAccessAllBit             (CfmAccess_H, UT_OFF);
  UTL_SetCfmAccessBitMode            (CfmAccess_H, UT_FCM_BITMODE_BLOCK);
  for(i=0; i<FCMARG.ybits; i++){
    UTL_SetCfmAccessAddrAssign   (CfmAccess_H, i, UT_SIG_Y(i));
  }
  for(i=0; i<FCMARG.xbits; i++){
    UTL_SetCfmAccessAddrAssign   (CfmAccess_H, i+FCMARG.ybits, UT_SIG_X(i));
  }
  UTL_SetCfmAccessXAddr              (CfmAccess_H, 0x0, (0x1<<FCMARG.xbits)-1);
  UTL_SetCfmAccessYAddr              (CfmAccess_H, 0x0, (0x1<<FCMARG.ybits)-1);

  USlider full = 0x1<<(FCMARG.xbits+FCMARG.ybits);
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      set_result(dut, -1); //skip
      continue;
    }

    result = 0;
    UTL_SetCfmAccessDut(CfmAccess_H, dut);
    for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
      for(fmbit=SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp; fmbit<SOCKET.dutblock_iopin_count[0]*(dutblock+1)/FCMARG.fmbitcomp; fmbit++){
        if(fmbit%FMBLKBIT==0){
          UTL_SetCfmAccessBitBlock(CfmAccess_H, fmbit/FMBLKBIT+1);
          UTL_CntCfmFailAddr(CfmAccess_H);
        }

        if(FCMARG.failratio>=0){
          expcount = (double)full*FCMARG.failratio+0.5;
        }
        else{ // for CFM FAIL COUNT READ CHECK (BY BIT)
          expcount = (double)full*pow(0.25,(int)((fmbit*FCMARG.fmbitcomp%SOCKET.dutblock_iopin_count[0])/3)+1)*(3-((fmbit*FCMARG.fmbitcomp%SOCKET.dutblock_iopin_count[0])%3))+0.5;
        }
 
        if(UTL_GetCfmFailAddrCntOverflow(fmbit)==UT_OFF){
          count = UTL_GetCfmFailAddrCnt(fmbit);
          if(DEBUG==1) printf("\tDUT%2d BLK%d FMBIT%2d : CFM COUNT = 0x%08x\n", dut, dutblock, fmbit, count);
          if(count!=expcount){
            printf("\tDUT%2d BLK%d FMBIT%2d : CFM COUNT = 0x%08x (EXP=0x%08x) FAIL***\n", dut, dutblock, fmbit, count, expcount);
            set_result(dut, 1);
            result|=1;
          }
        }
        else{
          printf("\tDUT%2d BLK%d FMBIT%2d : CFM OVERFLOW ERROR!!\n", dut, dutblock, fmbit);
          result|=1;
        }
      }
      fflush(stdout);
    }
    set_result(dut, result);
  }
  fflush(stdout);
  UTL_DeleteHandle(CfmAccess_H);
  UTL_DeleteCursor(dutc);

  return;
}

void cfm_read_check_perdut(TEST_testitem *testarg)
{
  int i, j;
  DutCursor dutc;
  UT_DUT dut = 0;
  RadioButton fmbit;
  int dutblock;
  USlider size;
  USlider *cfm_rdata1;
  USlider *cfm_rdata2;
  int x, y;
  USlider exp_data;
  USlider xsta = 0x0;
  USlider xspa = (0x1<<FCMARG.xbits)-1;
  USlider ysta = 0x0;
  USlider yspa = (0x1<<FCMARG.ybits)-1;

  size = (0x1<<(FCMARG.xbits+FCMARG.ybits));
  cfm_rdata1 = (USlider *)calloc(size, sizeof(USlider));
  cfm_rdata2 = (USlider *)calloc(size, sizeof(USlider));
  USlider cfm_rdata;

  CfmAccessHandle CfmAccess_H1 = UTL_GetCfmAccessHandle();
  UTL_ClearCfmAccessBit          (CfmAccess_H1);
  UTL_SetCfmAccessAction         (CfmAccess_H1, 1);
  UTL_SetCfmAccessAllDut         (CfmAccess_H1, UT_OFF);
  UTL_SetCfmAccessAllBit         (CfmAccess_H1, UT_OFF);
  for(i=0; i<FCMARG.ybits; i++){
    UTL_SetCfmAccessAddrAssign   (CfmAccess_H1, i, UT_SIG_Y(i));
  }
  for(i=0; i<FCMARG.xbits; i++){
    UTL_SetCfmAccessAddrAssign   (CfmAccess_H1, i+FCMARG.ybits, UT_SIG_X(i));
  }
  UTL_SetCfmAccessXAddr          (CfmAccess_H1, xsta, xspa);
  UTL_SetCfmAccessYAddr          (CfmAccess_H1, ysta, yspa);
  UTL_SetCfmAccessApLink         (CfmAccess_H1, UT_FCM_APLINK_XYZ);

  CfmAccessHandle CfmAccess_H2 = UTL_GetCfmAccessHandle();
  UTL_ClearCfmAccessBit          (CfmAccess_H2);
  UTL_SetCfmAccessAction         (CfmAccess_H2, 1);
  UTL_SetCfmAccessAllDut         (CfmAccess_H2, UT_OFF);
  UTL_SetCfmAccessAllBit         (CfmAccess_H2, UT_OFF);
  for(i=0; i<FCMARG.ybits; i++){
    UTL_SetCfmAccessAddrAssign   (CfmAccess_H2, i, UT_SIG_Y(i));
  }
  for(i=0; i<FCMARG.xbits; i++){
    UTL_SetCfmAccessAddrAssign   (CfmAccess_H2, i+FCMARG.ybits, UT_SIG_X(i));
  }
  UTL_SetCfmAccessXAddr          (CfmAccess_H2, xsta, xspa);
  UTL_SetCfmAccessYAddr          (CfmAccess_H2, ysta, yspa);
  UTL_SetCfmAccessApLink         (CfmAccess_H2, UT_FCM_APLINK_XYZ);

  j = 0;
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      set_result(dut, -1); //skip
      continue;
    }

    UTL_SetCfmAccessDut(CfmAccess_H1, dut);
    UTL_SetCfmAccessDut(CfmAccess_H2, dut);
    for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
      UTL_ClearCfmAccessBit(CfmAccess_H1);
      UTL_ClearCfmAccessBit(CfmAccess_H2);
      for(fmbit=SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp; fmbit<SOCKET.dutblock_iopin_count[0]*(dutblock+1)/FCMARG.fmbitcomp; fmbit++){
        if((SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp/FMBLKBIT)==(fmbit/FMBLKBIT)){
          UTL_AddCfmAccessBit(CfmAccess_H1, fmbit);
        }
        else{
          UTL_AddCfmAccessBit(CfmAccess_H2, fmbit);
        }
      }

      UTL_ReadCfm(CfmAccess_H1, cfm_rdata1, size*sizeof(USlider));
      if((SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp/FMBLKBIT)<((SOCKET.dutblock_iopin_count[0]*(dutblock+1)/FCMARG.fmbitcomp-1)/FMBLKBIT)){
        UTL_ReadCfm(CfmAccess_H2, cfm_rdata2, size*sizeof(USlider));
      }
      else{
        memset(cfm_rdata2, 0x0, size*sizeof(USlider));
      }
 
      i = 0;
      if(DEBUG==1){
        for(y=0; y<=3; y++){
          cfm_rdata = (cfm_rdata1[i]>>(SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT))|(cfm_rdata2[i]<<(FMBLKBIT-SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT));
          printf("\tDUT%2d BLK%d : cfm_data[0x%08x] = 0x%08x\n", dut, dutblock, i, cfm_rdata);
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
 
          cfm_rdata = (cfm_rdata1[i]>>(SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT))|(cfm_rdata2[i]<<(FMBLKBIT-SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp%FMBLKBIT));
          if(cfm_rdata!=exp_data){
            printf("\tDUT%2d BLK%d : cfm_data[0x%08x] = 0x%08x (EXP=0x%08x) (x=0x%x y=0x%x)\n", dut, dutblock, i, cfm_rdata, exp_data, x, y);
            fflush(stdout);
            set_result(dut, 1);
            goto cfm_read_fail_perdut;
          }
          i++;
        }
      }

      j+=SOCKET.dutblock_iopin_count[dutblock];
    }
    set_result(dut, 0);
    cfm_read_fail_perdut: ;
  }
  UTL_DeleteCursor(dutc);
  UTL_DeleteHandle(CfmAccess_H1);
  UTL_DeleteHandle(CfmAccess_H2);
  free(cfm_rdata1);
  free(cfm_rdata2);

  return;
}

void cfm_count_check_perdut(TEST_testitem *testarg)
{
  RadioButton fmbit;
  int dutblock;
  USlider count;
  USlider expcount;
  DutCursor dutc;
  UT_DUT dut = 0;
  int result = 0;
  int i;

  CfmAccessHandle CfmAccess_H = UTL_GetCfmAccessHandle();
  UTL_SetCfmAccessAction             (CfmAccess_H, 1);
  UTL_SetCfmAccessAllBit             (CfmAccess_H, UT_OFF);
  UTL_SetCfmAccessBitMode            (CfmAccess_H, UT_FCM_BITMODE_BLOCK);
  for(i=0; i<FCMARG.ybits; i++){
    UTL_SetCfmAccessAddrAssign       (CfmAccess_H, i, UT_SIG_Y(i));
  }
  for(i=0; i<FCMARG.xbits; i++){
    UTL_SetCfmAccessAddrAssign       (CfmAccess_H, i+FCMARG.ybits, UT_SIG_X(i));
  }
  UTL_SetCfmAccessXAddr              (CfmAccess_H, 0x0, (0x1<<FCMARG.xbits)-1);
  UTL_SetCfmAccessYAddr              (CfmAccess_H, 0x0, (0x1<<FCMARG.ybits)-1);

  i = 0;
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(is_captured(testarg, dut)==UT_OFF){
      set_result(dut, -1); //skip
      continue;
    }

    result = 0;
    UTL_SetCfmAccessDut(CfmAccess_H, dut);
    for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
      for(fmbit=SOCKET.dutblock_iopin_count[0]*dutblock/FCMARG.fmbitcomp; fmbit<SOCKET.dutblock_iopin_count[0]*(dutblock+1)/FCMARG.fmbitcomp; fmbit++){
        i++;
        expcount = i*FCMARG.fmbitcomp;
 
        if(fmbit%FMBLKBIT==0){
          UTL_SetCfmAccessBitBlock(CfmAccess_H, fmbit/FMBLKBIT+1);
          UTL_CntCfmFailAddr(CfmAccess_H);
        }
        if(UTL_GetCfmFailAddrCntOverflow(fmbit)==UT_OFF){
          count = UTL_GetCfmFailAddrCnt(fmbit);
          if(DEBUG==1) printf("\tDUT%2d BLK%d FMBIT%2d : CFM COUNT = 0x%08x\n", dut, dutblock, fmbit, count);
          if(count!=expcount){
            printf("\tDUT%2d BLK%d FMBIT%2d : CFM COUNT = 0x%08x (EXP=0x%08x) FAIL***\n", dut, dutblock, fmbit, count, expcount);
            set_result(dut, 1);
            result|=1;
          }
        }
        else{
          printf("\tDUT%2d BLK%d FMBIT%2d : CFM OVERFLOW ERROR!!\n", dut, dutblock, fmbit);
          result|=1;
        }
      }
      fflush(stdout);
    }
    set_result(dut, result);
  }
  fflush(stdout);
  UTL_DeleteHandle(CfmAccess_H);
  UTL_DeleteCursor(dutc);

  return;
}

