#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "UTSC.h"
#include "test.h"
#include "test_struct.h"
#include "common.h"

void print_socketinfo() {
  int dutblock;
  int pidx;
  int i;
  DutCursor dutc;
  UT_DUT dut;

  printf("\nSOCKET INFO\n");
  printf("DUT IOPIN COUNT = %d\n", SOCKET.dut_iopin_count);
  printf("DUTBLOCK COUNT  = %d\n", SOCKET.dutblock_count);
  for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
    printf("DUTBLOCK%d (%d)\t: DUTPIN", dutblock, SOCKET.dutblock_iopin_count[dutblock]);
    for(i=0; i<SOCKET.dutblock_iopin_count[dutblock]; i++){
      printf(" %3d", SOCKET.dutblock_iopin[dutblock][i]);
    }
    printf("\n");
  }

  printf("\nDUTIOPIN");
  for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
    for(i=0; i<SOCKET.dutblock_iopin_count[dutblock]; i++){
      printf(" %3d", SOCKET.dutblock_iopin[dutblock][i]);
    }
  }
  printf("\nTESTERIOCH\n");
  dutc = UTL_GetDutCursor(UT_DDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    printf("DUT%3d :", dut);
    for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
      for(i=0; i<SOCKET.dutblock_iopin_count[dutblock]; i++){
        printf(" %3d", SOCKET.testeriopin[dut][SOCKET.dutblock_iopin[dutblock][i]]);
      }
    }
    printf("\n");
  }
  printf("\n");
  UTL_DeleteCursor(dutc);

  dutc = UTL_GetDutCursor(UT_DDUT);
  printf("CHILD A1\t: DUT ");
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(SOCKET.dut_child[dut]==0){
      printf(" %2d", dut);
    }
  }
  printf("\n");
  UTL_DeleteCursor(dutc);

  dutc = UTL_GetDutCursor(UT_DDUT);
  printf("CHILD A2\t: DUT ");
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
    if(SOCKET.dut_child[dut]==1){
      printf(" %2d", dut);
    }
  }
  printf("\n\n");
  UTL_DeleteCursor(dutc);

  fflush(stdout);

  return;
}

void refresh_pinlist()
{
  RadioButton dutblock;
  int pidx;

  SOCKET.dutblock_iopinlist[0] = "DUTBLOCK0_IOPIN";
  SOCKET.dutblock_iopinlist[1] = "DUTBLOCK1_IOPIN";
  SOCKET.dutblock_iopinlist[2] = "DUTBLOCK2_IOPIN";
  SOCKET.dutblock_iopinlist[3] = "DUTBLOCK3_IOPIN";
  SOCKET.dutblock_iopinlist[4] = "DUTBLOCK4_IOPIN";
  SOCKET.dutblock_iopinlist[5] = "DUTBLOCK5_IOPIN";
  SOCKET.dutblock_iopinlist[6] = "DUTBLOCK6_IOPIN";
  SOCKET.dutblock_iopinlist[7] = "DUTBLOCK7_IOPIN";
  SOCKET.all_iopinlist = "ALL_IOPIN";

  UTL_CreatePinList(SOCKET.all_iopinlist);
  UTL_SetPinType(SOCKET.all_iopinlist, UT_PINTYPE_PIN);
  for(dutblock=0; dutblock<SOCKET.dutblock_count; dutblock++){
    UTL_CreatePinList(SOCKET.dutblock_iopinlist[dutblock]);
    UTL_SetPinType(SOCKET.dutblock_iopinlist[dutblock], UT_PINTYPE_PIN);

    for(pidx=0; pidx<SOCKET.dutblock_iopin_count[dutblock]; pidx++){
      UTL_AddPinNumber(SOCKET.dutblock_iopinlist[dutblock], SOCKET.dutblock_iopin[dutblock][pidx]);
    }
    UTL_AppendPinList(SOCKET.all_iopinlist, SOCKET.dutblock_iopinlist[dutblock]);
  }

  return;
}

void testresult_pass4alldut(char *testname)
{
  DutCursor dutcur;
  UT_DUT    dut = 0;

  dutcur = UTL_GetDutCursor(UT_DDUT);
  while((dut=UTL_NextDut(dutcur))!=UT_NOMORE){
    UTL_ResetTestResult(dut, testname, UT_RES_ALL);
  }
  UTL_DeleteCursor(dutcur);

  return;
}

void testresult_fail4alldut(char *testname)
{
  DutCursor dutcur;
  UT_DUT    dut = 0;

  dutcur = UTL_GetDutCursor(UT_DDUT);
  while((dut=UTL_NextDut(dutcur))!=UT_NOMORE){
    UTL_SetTestResult(dut, testname, UT_RES_ALL);
  }
  UTL_DeleteCursor(dutcur);

  return;
}

void set_reg(RadioButton name, USlider data){
  RegHandle reg_H=UTL_GetRegHandle();
  UTL_SetRegUs     (reg_H, name, 1, data);
  UTL_SendReg      (reg_H);
  UTL_DeleteHandle (reg_H);

  return;
}

void set_ilmode(RadioButton ilmode)
{
  IlModeHandle IlMode_H = UTL_GetIlModeHandle();
  UTL_SetIlMode    (IlMode_H, ilmode);
  UTL_SendIlMode   (IlMode_H);
  UTL_DeleteHandle (IlMode_H);
  return;
}

void failcapsel_a2(){
  printf("FailCaptureSelect(A2)\n");
  FailCaptureSelectHandle fcsh;
  fcsh=UTL_GetFailCaptureSelectHandle();
  UTL_SetFailCaptureSelectAllDutGroupNumber(fcsh, UT_OFF);
  UTL_SetFailCaptureSelectDutGroupNumber(fcsh, 1);
  UTL_SetFailCaptureSelectAllPin(fcsh, UT_ON);
  UTL_SendFailCaptureSelect(fcsh);
  UTL_DeleteHandle(fcsh);
  return;
}

double calc_sum(double nums[], int n){
  int i;
  double sum = 0.0;

  for(i=0; i<n; i++) {
    sum = sum + nums[i];
  }

  return(sum);
}

double calc_ave(double nums[], int n){
  if(n==0){
    return(0.0);
  }

  double sum = calc_sum(nums, n);
  double ave = sum/n;

  return(ave);
}

double calc_var(double nums[], int n){
  if(n==0){
    return(0.0);
  }

  int i;
  double ave = calc_ave(nums, n);
  double sum = 0.0;
  for(i=0; i<n; i++){
    sum+=(nums[i]-ave)*(nums[i]-ave);
  }

  double var = sum/n;

  return(var);
}

double calc_sd(double nums[], int n){
  double var = calc_var(nums, n);
  double sd = sqrt(var);
  
  return(sd);
}

DSlider dct_data(UT_DUT dut, UT_PIN pin, int action){
  static DSlider storedata[MAXPINNO][MAXCLDCNT];
  int tch, child;
  Slider mcnt;
  DSlider dctdata[MAXDCTCNT];
  DSlider data = -1;

  dutpin_to_testerch(dut, pin, &tch, &child);
  tch--;

  if((action&DCT_STORE)!=0x0){
    DctReadPinHandle drph = UTL_GetDctReadPinHandle();
    UTL_SetDctReadPinType(drph, UT_PINTYPE_PIN);
    UTL_SetDctReadPinDut(drph, dut);
    UTL_SetDctReadPinNumber(drph, pin);

    if((action&DCT_HISTORY)!=0x0){ // Calculate mean from DCT history data.
      // This can be fine resolution than tester spec.
      // The data must be read before next DCT to avoid overwitten.
      DctHandle dch = UTL_GetDcHandle();
      UTL_UpdateDc(dch, 1);
      UTL_GetDcMeasCnt(dch, &mcnt);
      UTL_DeleteHandle(dch);

      UTL_ReadDctPinAllHistoryData(drph, dctdata, mcnt);
      data = calc_ave(dctdata, mcnt);
    }
    else if((action&DCT_PINDATA)!=0x0){ // Read mean DCT data calculated in OS.
      data = UTL_ReadDctPinData(drph);
    }
    UTL_DeleteHandle(drph);

    storedata[tch][child] = data;
  }
  else if(action==DCT_READ){
    data = storedata[tch][child];
  }

  return(data);
}

void store_dct(char* pinname, int mode)
{
    PinCursor pincur;
    UT_PIN pin;
    DutCursor dutcur; 
    UT_DUT dut;

    dutcur = UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutcur))!=UT_NOMORE){
      pincur = UTL_GetPinCursor(pinname);
      while((pin=UTL_NextPin(pincur))!=UT_NOMORE){
        dct_data(dut, pin, DCT_STORE|mode);
      }
      UTL_DeleteCursor(pincur);
    }
    UTL_DeleteCursor(dutcur);

    return;
}

void stat_dct(char *pinlist, DSlider hlimit, DSlider llimit, DSlider *data){
    int total, lcnt, ucnt;
    DSlider max, min;
    DutCursor dutcur; 
    UT_DUT    dut = 0;
    PinCursor pincur;
    UT_PIN    pin = 0;
    int freeflag = 0;
    int tch, child;
    char *childstr[] = {"A1", "A2"};

    if(data==NULL){
      freeflag = 1;
      data = (DSlider *)malloc(sizeof(DSlider)*MAXIOPINNO);
    }
    memset(data, 0x0, sizeof(DSlider)*MAXIOPINNO);

    printf("---------------------------------------------------------------------------------\n");
    printf("GO/NOGO   DATA         UPPER        LOWER        PIN       DUT       TESTERCH\n");
    printf("---------------------------------------------------------------------------------\n");

    total = 0;
    lcnt = 0;
    ucnt = 0;
    max = -1e3;
    min = +1e3;
	dutcur = UTL_GetDutCursor(UT_MDUT);
	while((dut=UTL_NextDut(dutcur))!=UT_NOMORE){

      pincur = UTL_GetPinCursor(pinlist);
      while((pin=UTL_NextPin(pincur))!=UT_NOMORE){
       	data[total] = dct_data(dut, pin, DCT_READ);
        max = MAX(max, data[total]);
        min = MIN(min, data[total]);

        if(data[total]<llimit){
          lcnt++;
          printf("L-FAIL");
        }
        else if(data[total]>hlimit){
          ucnt++;
          printf("U-FAIL");
        }
        else{
          printf("      ");
        }
	    printf("   % fV   % fV   % fV    PIN%-3d    DUT%-3d", data[total], hlimit, llimit, pin, dut);
        dutpin_to_testerch(dut, pin, &tch, &child);
        printf("    P%d%s\n", tch, childstr[child]); fflush(stdout);

        total++;
      }
      UTL_DeleteCursor(pincur);
    }
  	UTL_DeleteCursor(dutcur);

    printf("\nSTATISTICS\n");
    printf("\tU-FAIL %9d , PASS %9d , L-FAIL %9d\n", ucnt, total-ucnt-lcnt, lcnt);
    printf("\tULIMIT % fV, EXP  % fV, LLIMIT % fV\n", hlimit, (hlimit+llimit)/2.0, llimit);
    printf("\tMAX    % fV, AVE  % fV, MIN    % fV\n", max, calc_ave(data, total), min);
    printf("\tStdDev % fV, LIMIT +/-%.1fsigma\n", calc_sd(data, total), (hlimit-llimit)/2.0/calc_sd(data, total));

    if(freeflag!=0){
      free(data);
    }

    return;
}

void dutpin_to_testerch(UT_DUT dut, int dut_pin, int *tester_channel, int *child){
  int vtc_pin, vtc_station;

  UTVTC_SocketConversion_DutPin_ToVtcPin(UT_SOCKET_PINTYPE_IO, dut_pin-1, &vtc_pin);
  UTVTC_SocketConversion_VtcPin_ToPbPin(dut-1, vtc_pin, &vtc_station, tester_channel, child);

  *tester_channel = (*tester_channel)+1;
  *child = ((*child)&0x3)-1; //A1:0, A2:1

  return;
}

