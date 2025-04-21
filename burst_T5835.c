#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "UTSC.h"
#include "test.h"
#include "test_struct.h"
#include "pinppsbump.h"
#include "burst.h"

#define DEBUG (1)

static void display(int result);
static void pin_list();
static void vio_condition();
static void meas_fct(TEST_testitem *testarg);
static int dct_result_hvlvdr(TEST_testitem *testarg);

static void display(int result)
{
     printf("\n%-32s",UTL_ReadTestName());
     if(result==0){
        testresult_pass4alldut(UTL_ReadTestName());
	printf(" ***PASS");
     }else{
	if(result==3){ printf("LOG CHECK!!");
        }else if(result!=0){
        	testresult_fail4alldut(UTL_ReadTestName());
		printf(" FAIL** dut:%x",result);
	}
     }
     fflush(stdout);
}

static void pin_list(){
    int *plst, pcnt, pidx;
    UT_PIN pin;

    UTL_CreatePinList("IOPIN");
    UTL_SetPinType("IOPIN", UT_PINTYPE_PIN);
    UTSOCK_Info_GetDutPinList(UT_SOCKET_PINTYPE_IO, &plst, &pcnt);
//    printf(" test pin cnt :%d\n",pcnt);
    for(pidx=0; pidx<pcnt; pidx++){
      pin = plst[pidx];
      if(25<=pin%64){
        continue; //LVDR
          printf("skip pin %d\n",pin);fflush(stdout);
      }
      UTL_AddPinNumber("IOPIN", pin);
//    	printf("IO pin idx:%d, pin num:%d\n",pidx,pin);
    }
          fflush(stdout);

    return;
}

static void vio_condition()
{

    ViHandle  Vi_H;
    VoHandle  Vo_H;
    VtHandle  Vt_H;
    PinHandle Pin_H;

    Pin_H = UTL_GetPinHandle();
    UTL_SetPinOpen   (Pin_H, UT_ON);
    UTL_SendPin      (Pin_H, "IOPIN");
    UTL_DeleteHandle (Pin_H);

    Vi_H = UTL_GetViHandle();
    UTL_SetViHigh    (Vi_H, 2.0);
    UTL_SetViLow     (Vi_H, 0.0);
    UTL_SendVi       (Vi_H, 1);
    UTL_DeleteHandle (Vi_H);

    Vo_H = UTL_GetVoHandle();
    UTL_SetVoHigh    (Vo_H, 1);
    UTL_SetVoLow     (Vo_H, 1);
    UTL_SendVo       (Vo_H, 1);
    UTL_DeleteHandle (Vo_H);

    Vt_H = UTL_GetVtHandle();
    UTL_SetVt        (Vt_H, 0);
    UTL_SendVt       (Vt_H, 1);
    UTL_DeleteHandle (Vt_H);

}


void pattern_burst_wait(TEST_testitem *testarg)
{
    double period1;
    double period2;
    int    overflow;
    int result =0;

	printf(" burst wait start...\n");fflush(stdout);

    TgHandle Tg_H = UTL_GetTgHandle();
    UTL_AddTgRate           (Tg_H,1,         1e-6);
    UTL_SendTg              (Tg_H);
    UTL_DeleteHandle        (Tg_H);

//	printf(" set pin list\n");fflush(stdout);
    pin_list();
//	printf(" set vio condition\n");fflush(stdout);
    vio_condition();

    //MEAS MPAT
    UTL_StartTimer(UT_TIMER_R1MS);
    FctHandle Fct_H = UTL_GetFctHandle();
    UTL_SetFctMpatName      (Fct_H, BURSTARG.mpat);
    UTL_SetFctFailInhibit   (Fct_H, UT_ON);
    UTL_SetFctStartPc       (Fct_H, BURSTARG.pc_addr);
    UTL_OnPowerSeq();

//    period1 = UTL_ReadTimer (&overflow);
//    sleep(3);
//    period2 = UTL_ReadTimer (&overflow);
//    printf("\n wait(3) time:%f \n",period2-period1);

    period1 = UTL_ReadTimer (&overflow);
    UTL_MeasFct             (Fct_H);
    period2 = UTL_ReadTimer (&overflow);
    printf("\n patburst wait 3s time:%f \n",period2-period1);

    UTL_DeleteHandle        (Fct_H);
    if((period2-period1) <= 2.9 || (period2-period1) >= 3.1) result=1;
    display(result);

    UTL_OffPowerSeq();
}

void test_burst_wait(){
	UTL_WaitTime(3);
}

void pattern_burst_wait_MCI()
{
    double period1;
    int    overflow;
    int result =0;
    BurstHandle bh;

    TgHandle Tg_H = UTL_GetTgHandle();
    UTL_AddTgRate           (Tg_H,1,         1e-6);
    UTL_SendTg              (Tg_H);
    UTL_DeleteHandle        (Tg_H);

    pin_list();
    vio_condition();

    bh = UTL_GetBurstHandle();
    UTL_SetBurstBlock(bh,test_burst_wait);
    UTL_SendBurstData(bh,1);

    UTL_StartTimer(UT_TIMER_R1MS);
    //MEAS MPAT
    FctHandle Fct_H = UTL_GetFctHandle();
    UTL_SetFctMpatName      (Fct_H, "pat_burst.mpa");
    UTL_SetFctFailInhibit   (Fct_H, UT_ON);
    UTL_SetFctStartPc       (Fct_H, 0x860);
    UTL_MeasFct             (Fct_H);

    UTL_WaitTime(1.0);
    UTL_WriteAlpgCtrlReg( UT_REG_CONTINUE_FLAG, 1);
    UTL_DeleteHandle        (Fct_H);
    period1 = UTL_ReadTimer (&overflow);
    printf("\ntime:%f \n",period1);
    if(period1-1.0 <= 2.9 || period1-1.0 >= 3.1) result=1;
     display(result);

    UTL_BurstClearAll();
}

void pattern_burst_sti(TEST_testitem *testarg)
{
    int result =0;
    int xadd_before;
    int idx1_before;
    int xadd;
    int idx1;

    TgHandle Tg_H = UTL_GetTgHandle();
    UTL_AddTgRate           (Tg_H,1,         1e-6);
    UTL_SendTg              (Tg_H);
    UTL_DeleteHandle        (Tg_H);

    pin_list();
    vio_condition();

//    IdxModeHandle idxhdl = UTL_GetIdxModeHandle();
//    UTL_SetIdxMode(idxhdl,UT_IDXMODE_IDXLOOP1);
//    UTL_SendIdxMode(idxhdl);
     xadd_before=UTL_ReadUSRegister      (UT_REG_XB,1);
     idx1_before=UTL_ReadUSRegister      (UT_REG_IDX1,1);
     printf("\nIDX1_before:0x%x %d\n",idx1_before,idx1_before);
     printf("xadd_before:0x%x %d\n",xadd_before,xadd_before);
    //MEAS MPAT
    FctHandle Fct_H = UTL_GetFctHandle();
    UTL_SetFctMpatName      (Fct_H, BURSTARG.mpat);
    UTL_SetFctFailInhibit   (Fct_H, UT_ON);
    UTL_SetFctStartPc       (Fct_H, BURSTARG.pc_addr);

//printf(" %s checkpoin01 \n",__func__);fflush(stdout);
    UTL_MeasFct             (Fct_H);

//	UTL_SetFctNoWait( Fct_H, UT_ON);     //choi
//	UTL_SetFctNoClear  ( Fct_H, UT_ON ); //choi
//	UTL_StartFct( Fct_H );               //choi


//printf(" %s checkpoin02 \n",__func__);fflush(stdout);
//    UTL_WaitTime(1.0);                               //choi
//    UTL_WriteAlpgCtrlReg( UT_REG_CONTINUE_FLAG, 1);  //choi

    UTL_DeleteHandle(Fct_H);

    xadd=UTL_ReadUSRegister(UT_REG_XB,1);
    idx1=UTL_ReadUSRegister      (UT_REG_IDX1,1);
    printf("\nIDX1:0x%x %d\n",idx1,idx1);
    printf("xadd:0x%x %d\n",xadd,xadd);
    if(xadd==0x10000) {
        result=0;
    }else{
        result=1;
    }
    display(result);
}

void pattern_burst_stisp(TEST_testitem *testarg)
{
    int result =0;
    int xadd;

    TgHandle Tg_H = UTL_GetTgHandle();
    UTL_AddTgRate           (Tg_H,1,         1e-6);
    UTL_SendTg              (Tg_H);
    UTL_DeleteHandle        (Tg_H);

    pin_list();
//    printf("%s checkpoint 00 \n",__func__);fflush(stdout);
    vio_condition();

    //MEAS MPAT
//    printf("%s checkpoint 01 \n",__func__);fflush(stdout);
    FctHandle Fct_H = UTL_GetFctHandle();
    UTL_SetFctMpatName      (Fct_H, BURSTARG.mpat);
    UTL_SetFctFailInhibit   (Fct_H, UT_ON);
    UTL_SetFctStartPc       (Fct_H, BURSTARG.pc_addr);
//    printf("%s checkpoint 02 \n",__func__);fflush(stdout);
    UTL_MeasFct             (Fct_H);
//    printf("%s checkpoint 03 \n",__func__);fflush(stdout);
    UTL_DeleteHandle        (Fct_H);

//    printf("%s checkpoint 04 \n",__func__);fflush(stdout);
    xadd=UTL_ReadUSRegister      (UT_REG_XB,1);
    printf("\nxadd: %d\n",xadd);
    if(xadd==0x2) {
        result=0;
    }else{
        result=1;
    }
    display(result);
}

static void meas_fct(TEST_testitem *testarg){
    UTL_OnPowerSeq();

    FctHandle fcth = UTL_GetFctHandle();
    UTL_SetFctMpatName         (fcth, BURSTARG.mpat);
    UTL_SetFctFailInhibit      (fcth, UT_OFF);
    UTL_SetFctStartPc          (fcth, BURSTARG.pc_addr);
    UTL_MeasFct                (fcth);
    UTL_DeleteHandle(fcth);

    return;
}

void pattern_burst_inh(TEST_testitem *testarg){
    ViHandle vih = UTL_GetViHandle();
    UTL_SetViHvDr              (vih, UT_ON);
    UTL_SetViHigh              (vih, 6.0);
    UTL_SetViLow               (vih, 0.0);
    UTL_SendVi                 (vih, 2);
    UTL_DeleteHandle(vih);

    PinHandle pinh = UTL_GetPinHandle();
    UTL_SetPinOpen             (pinh, UT_ON);
    UTL_SendPin                (pinh, SOCKET.all_iopinlist);

    int i;
    UTL_CreatePinList("HCDRPIN");
    UTL_SetPinType("HCDRPIN", UT_PINTYPE_PIN);
    for(i=25; i<=30; i++){
	  UTL_AddPinNumber("HCDRPIN", i);
    }
    UTL_InitializePinHandle    (pinh);
    UTL_SetPinOpen             (pinh, UT_OFF);
    UTL_SetPinViNumber         (pinh, 2);
    UTL_SetPinDrWaveform       (pinh, UT_WAV_FIXH);
    UTL_SetPinInit             (pinh, UT_PIN_DEFAULT);
    UTL_SetPinHvDr             (pinh, UT_ON);
    UTL_SendPin                (pinh, "HCDRPIN");

    meas_fct(testarg);

    DcHandle dch = UTL_GetDcHandle();
    UTL_SetDcMode              (dch, UT_DCT_MVM);
    UTL_SetDcMrange            (dch, BURSTARG.llimit, BURSTARG.llimit);
    UTL_SetDcLimitHigh         (dch, BURSTARG.hlimit, UT_ON);
    UTL_SetDcLimitLow          (dch, BURSTARG.llimit, UT_ON);
    UTL_SendDc                 (dch, 1);
    UTL_DeleteHandle(dch);

    DctHandle dcth = UTL_GetDctHandle();
    UTL_SetDctPinList          (dcth, "HCDRPIN");
    UTL_SetDctRelayMode        (dcth, UT_DCT_SWAP);
    UTL_SetDctPinVi            (dcth, UT_ON);
    UTL_SetDctPinHvDr          (dcth, UT_ON);
    UTL_MeasDct                (dcth);
    UTL_DeleteHandle(dcth);

    store_dct("HCDRPIN", DCT_PINDATA);
    stat_dct("HCDRPIN", BURSTARG.hlimit, BURSTARG.llimit, NULL);

    UTL_InitializePinHandle    (pinh);
    UTL_SetPinOpen             (pinh, UT_ON);
    UTL_SendPin                (pinh, "HCDRPIN");
    UTL_DeleteHandle(pinh);

    return;
}


void pattern_burst_inhh(TEST_testitem *testarg){
    ViHandle vih = UTL_GetViHandle();
    UTL_SetViHvLvDr            (vih, UT_ON);
    UTL_SetViHigh              (vih,10.0);
    UTL_SetViLow               (vih, 0.0);
    UTL_SendVi                 (vih, 1);
    UTL_DeleteHandle(vih);

    PinHandle pinh = UTL_GetPinHandle();
    UTL_SetPinOpen             (pinh, UT_ON);
    UTL_SendPin                (pinh, SOCKET.all_iopinlist);

    int i;
    UTL_CreatePinList("HVLVDRPIN");
    UTL_SetPinType("HVLVDRPIN", UT_PINTYPE_PIN);
	UTL_AddPinNumber("HVLVDRPIN", 25);
    
    UTL_InitializePinHandle    (pinh);
    UTL_SetPinOpen             (pinh, UT_OFF);
    UTL_SetPinViNumber         (pinh, 1);
    UTL_SetPinDrWaveform       (pinh, UT_WAV_FIXH);
    UTL_SetPinInit             (pinh, UT_PIN_DEFAULT);
    UTL_SetPinHvLvDr           (pinh, UT_ON);
    UTL_SetPinDcConnect        (pinh, UT_OFF		);    // Normal DC unit cannot be connected HVLVDR pin
    UTL_SendPin                (pinh, "HVLVDRPIN");

    meas_fct(testarg);

    DcHvlvdrHandle dc_h = UTL_GetDcHvlvdrHandle();
	UTL_SetDcHvlvdrMode			(dc_h, UT_HVLVDR_VM); 
	UTL_SetDcHvlvdrMrange		(dc_h,	30,		-10		);
	UTL_SetDcHvlvdrLimitLow		(dc_h,	BURSTARG.llimit, UT_ON);
	UTL_SetDcHvlvdrLimitHigh	(dc_h,	BURSTARG.hlimit, UT_ON);
	UTL_SendDcHvlvdr			(dc_h					);
    UTL_DeleteHandle			(dc_h					);

    DctHandle dct_h = UTL_GetDctHvlvdrHandle();
	UTL_SetDctHvlvdrPinList		(dct_h,	"HVLVDRPIN"	);
	UTL_MeasDctHvlvdr		(dct_h			);
    UTL_DeleteHandle		(dct_h			);

    int result=0;
    result=dct_result_hvlvdr(testarg);
    display(result);

    UTL_InitializePinHandle    (pinh);
    UTL_SetPinOpen             (pinh, UT_ON);
    UTL_SendPin                (pinh, "HVLVDRPIN");
    UTL_DeleteHandle(pinh);

    return;
}

void pattern_burst_vt(TEST_testitem *testarg){
    VoHandle voh = UTL_GetVoHandle();
    UTL_SetVoHigh              (voh, 1.0);
    UTL_SetVoLow               (voh, 0.0);
    UTL_SendVo                 (voh, 1);
    UTL_DeleteHandle(voh);

    VtHandle vth = UTL_GetVtHandle();
    UTL_SetVt                  (vth, 2.0);
    UTL_SendVt                 (vth, 1);
    UTL_DeleteHandle(vth);

    PinHandle pinh = UTL_GetPinHandle();
    UTL_SetPinOpen             (pinh, UT_OFF);
    UTL_SetPinVoNumber         (pinh, 1);
    UTL_SetPinVtNumber         (pinh, 1);
    UTL_SetPinTerm             (pinh, UT_ON);
    UTL_SendPin                (pinh, SOCKET.all_iopinlist);

    meas_fct(testarg);

    DcHandle dch = UTL_GetDcHandle();
    UTL_SetDcMode              (dch, UT_DCT_MVM);
    UTL_SetDcMrange            (dch, BURSTARG.llimit, BURSTARG.llimit);
    UTL_SetDcLimitHigh         (dch, BURSTARG.hlimit, UT_ON);
    UTL_SetDcLimitLow          (dch, BURSTARG.llimit, UT_ON);
    UTL_SendDc                 (dch, 1);
    UTL_DeleteHandle(dch);

    DctHandle dcth = UTL_GetDctHandle();
    UTL_SetDctPinList          (dcth, SOCKET.all_iopinlist);
    UTL_SetDctRelayMode        (dcth, UT_DCT_SWAP);
    UTL_SetDctPinVo            (dcth, UT_ON);
    UTL_SetDctPinTerm          (dcth, UT_ON);
    UTL_MeasDct                (dcth);
    UTL_DeleteHandle(dcth);

    store_dct(SOCKET.all_iopinlist, DCT_PINDATA);
    stat_dct(SOCKET.all_iopinlist, BURSTARG.hlimit, BURSTARG.llimit, NULL);

    UTL_InitializePinHandle    (pinh);
    UTL_SetPinOpen             (pinh, UT_ON);
    UTL_SendPin                (pinh, SOCKET.all_iopinlist);
    UTL_DeleteHandle(pinh);

    return;
}

void pattern_burst_inout(TEST_testitem *testarg){
    ViHandle vih = UTL_GetViHandle();
    UTL_SetViHigh              (vih, 0.9);
    UTL_SetViLow               (vih, 0.1);
    UTL_SendVi                 (vih, 1);
    UTL_DeleteHandle(vih);

    VtHandle vth = UTL_GetVtHandle();
    UTL_SetVt                  (vth, 0.5);
    UTL_SendVt                 (vth, 1);
    UTL_DeleteHandle(vth);

    VoHandle voh = UTL_GetVoHandle();
    UTL_SetVoHigh              (voh, 0.8);
    UTL_SetVoLow               (voh, 0.2);
    UTL_SendVo                 (voh, 1);
    UTL_DeleteHandle(voh);

    TgHandle tgh = UTL_GetTgHandle();
    DSlider rate = 100e-9;
    UTL_AddTgRate              (tgh, 1, rate);
    UTL_AddTgDreL              (tgh, 1, 1, rate*0.0);
    UTL_AddTgDreT              (tgh, 1, 1, rate*0.0);
    UTL_AddTgBclk              (tgh, 1, 1, rate*0.0);
    UTL_AddTgCclk              (tgh, 1, 1, rate*0.5);
    UTL_AddTgStrb              (tgh, 1, 1, rate*1.25);
    UTL_AddTgStrb              (tgh, 1, 2, rate*1.75);
    UTL_SendTg                 (tgh);
    UTL_DeleteHandle(tgh);

    PinHandle pinh = UTL_GetPinHandle();
    UTL_SetPinViNumber         (pinh, 1);
    UTL_SetPinInit             (pinh, UT_PIN_DEFAULT);
    UTL_SetPinDrClock          (pinh, UT_PIN_BCLK, 1);
    UTL_SetPinDrClock          (pinh, UT_PIN_CCLK, 1);
    UTL_SetPinDrWaveform       (pinh, UT_WAV_RZX);
    UTL_SetPinDreClock         (pinh, 1);
    UTL_SetPinDreNumber        (pinh, 1);
    UTL_SetPinDreWaveform      (pinh, UT_DREWAV_NRZ);
    UTL_SetPinVoNumber         (pinh, 1);
    UTL_SetPinTerm             (pinh, UT_ON);
    UTL_SetPinIoCtrl           (pinh, UT_ON);
    UTL_AddPinStrbCpeNumber    (pinh, 1, 1);
    UTL_AddPinStrbCpeNumber    (pinh, 2, 1);
    UTL_AddPinExpStrbNumber    (pinh, 1, UT_PIN_EXP_FH);
    UTL_AddPinExpStrbNumber    (pinh, 2, UT_PIN_EXP_FL);
    UTL_SendPin                (pinh, SOCKET.all_iopinlist);
    UTL_DeleteHandle(pinh);

    meas_fct(testarg);

    int i;
    int data;
    RadioButton result;
    RadioButton rmode[] = {UT_RES_STRB1_FAILED, UT_RES_STRB2_FAILED};
    FctReadPinHandle rph = UTL_GetFctReadPinHandle();
    DutCursor dutcur = UTL_GetDutCursor(UT_MDUT);
    UT_DUT    dut = 0;
    PinCursor pincur;
    UT_PIN    pin = 0;
    while((dut=UTL_NextDut(dutcur))!=UT_NOMORE){
      UTL_ResetTestResult(dut, testarg->testname, UT_RES_FUNC);

      UTL_SetFctReadPinDut(rph, dut);
      pincur = UTL_GetPinCursor(SOCKET.all_iopinlist);
      while((pin=UTL_NextPin(pincur))!=UT_NOMORE){
        UTL_SetFctReadPinNumber(rph, pin);
        data = 0x0;
        for(i=0; i<2; i++){
          UTL_SetFctReadPinMode(rph, rmode[i]);
          data|=(UTL_ReadFctPin(rph)<<i);
        }

        if(DEBUG==1){printf("DUT%2d P%2d EXP=0x%x DATA=0x%x", dut, pin, BURSTARG.exp, data);}
        if(data!=BURSTARG.exp){
          if(DEBUG==1){printf("  FAIL***\n"); fflush(stdout);}
          UTL_SetTestResult(dut, testarg->testname, UT_RES_FUNC);
        }
        else{
          if(DEBUG==1){printf("  ***PASS\n"); fflush(stdout);}
        }
      }
      UTL_DeleteCursor(pincur);

      result = UTL_ReadTestResult(dut, testarg->testname, UT_RES_FUNC);
      if(result==UT_RES_PASSED) printf("DUT%2d  ***PASS\n",dut);
      if(result==UT_RES_FAILED) printf("DUT%2d  FAIL***\n",dut);
    }
    UTL_DeleteCursor(dutcur);
    UTL_DeleteHandle(rph);

    return;
}

static int dct_result_hvlvdr(TEST_testitem *testarg)
{
	int i,j,k;
	int result=0;
	int flg=0;
	UT_DUT dut=0;
	UT_PIN pin=0;
	int DUTNUM=16;
	double data[DUTNUM];
	for(i=0; i<DUTNUM; i++){data[i]=0;}

	DctHvlvdrReadPinHandle dctr_h = UTL_GetDctHvlvdrReadPinHandle();
	DutCursor dutcur=UTL_GetDutCursor(UT_MDUT);
	while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
		UTL_SetDctHvlvdrReadPinDut 			(dctr_h, dut);
		PinCursor pincur=UTL_GetPinCursor("HVLVDRPIN");
		while((pin=UTL_NextPin(pincur)) != UT_NOMORE){
			UTL_SetDctHvlvdrReadPinNumber 		(dctr_h, pin); 
			data[dut-1]=UTL_ReadDctHvlvdrPinData  	(dctr_h);
		}
        UTL_DeleteCursor (pincur);
	}
    UTL_DeleteCursor (dutcur);	
    UTL_DeleteHandle (dctr_h);

	dutcur=UTL_GetDutCursor(UT_MDUT);
	while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
		flg=0;
		printf("DUT%02d: %8.4fV | ",dut,data[dut-1]);
		if(data[dut-1]<=BURSTARG.hlimit && data[dut-1]>=BURSTARG.llimit){
			printf("PASS**\n");fflush(stdout);
		}else{
			printf("       ***FAIL!!\n");fflush(stdout);
			result=result | 0x1<<dut-1;	
		}
	}
    UTL_DeleteCursor (dutcur);
	return result;
}
