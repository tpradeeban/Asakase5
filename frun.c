#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include "test.h"
#include "test_struct.h"
#include "frun.h"

#define TESIM 0

#define DEBUG 1       // Not Debug Mode:0, Debug Mode:1
#define WAVEFORM {\
                  UT_WAV_FRUN_FIXL\
                 ,UT_WAV_FRUN_FIXH\
                 ,UT_WAV_FRUN_NRZA\
                 ,UT_WAV_FRUN_INRZA\
                 ,UT_WAV_FRUN_NRZB\
                 ,UT_WAV_FRUN_INRZB\
                 ,UT_WAV_FRUN_NRZC  \
                 ,UT_WAV_FRUN_INRZC \
                 ,UT_WAV_FRUN_NRZBC \
                 ,UT_WAV_FRUN_INRZBC\
                 ,UT_WAV_FRUN_NRZCB \
                 ,UT_WAV_FRUN_INRZCB\
                 ,UT_WAV_FRUN_RZO   \
                 ,UT_WAV_FRUN_IRZO  \
                 ,UT_WAV_FRUN_RZZ   \
                 ,UT_WAV_FRUN_IRZZ  \
                 ,UT_WAV_FRUN_RZX   \
                 ,UT_WAV_FRUN_IRZX  \
                 ,UT_WAV_FRUN_XORBC \
                 ,UT_WAV_FRUN_IXORBC\
                 ,UT_WAV_FRUN_DNRZ  \
                 ,UT_WAV_FRUN_IDNRZ \
                 }

static void set_interleave_mode(int ilmode);
static void pin_list(TEST_testitem *testarg);
static void pin_condition_frun(char *pinlist, TEST_testitem *testarg);
static void level_setting( int channel, double high, double low);
//static void SetTg();
static void SetPinOpen(void);
static void timing_setting(TEST_testitem *testarg);
static void start_fct(TEST_testitem *testarg);
static void MeasDC(int lmode, char *pinlist);

static void display(int result);
static int funcresult(int pfresult);

void dc_setting(void);
void adc_condition(void);
void adc_history_read(int lmode, char *pinlist);
void samplingrate_setting(void);

static void set_interleave_mode(int ilmode)
{
    IlModeHandle IlMode_H = UTL_GetIlModeHandle();
    UTL_SetIlMode    (IlMode_H, ilmode);
    UTL_SendIlMode   (IlMode_H);
    UTL_DeleteHandle (IlMode_H);
}

static void timing_setting(TEST_testitem *testarg)
{
    DSlider tck=50e-9;                              // 440Mbps=4.5e-9,400Mbps=5e-9,200Mbps=10e-9,100Mbps=20e-9
    DSlider offset;                                 // 440Mbps=4.5e-9,400Mbps=5e-9,200Mbps=10e-9,100Mbps=20e-9

    if(FRUNARG.wfnu==2 || FRUNARG.wfnu==3){
        offset = 45e-9;                             // NRZA
	}
    else if(FRUNARG.wfnu==6 || FRUNARG.wfnu==7|| FRUNARG.wfnu==10|| FRUNARG.wfnu==11){
        offset = 95e-9;                             // NRZC NRZCB
	}
    else{
        offset = 70e-9;                             // NRZB NRZBC
    }

    TgHandle tg_h=UTL_GetTgHandle();
	UTL_AddTgRate(tg_h, 1, tck);                    // (Handle, TS Number, Value)
    if(FRUNARG.wfnu==2 || FRUNARG.wfnu==3){         // NRZA       
	    UTL_AddTgAclk(tg_h, 1, 1, tck*0.000);       // (Handle, TS Number, Bclk Phase Number, Value)
	    UTL_AddTgBclk(tg_h, 1, 1, tck*0.500);       // (Handle, TS Number, Bclk Phase Number, Value)
        UTL_AddTgCclk(tg_h, 1, 1, tck*1.000);       // (Handle, TS Number, Cclk Phase Number, Value)
	}else if(FRUNARG.wfnu==6 || FRUNARG.wfnu==7|| FRUNARG.wfnu==10|| FRUNARG.wfnu==11){                //NRZC NRZCB 
	    UTL_AddTgAclk(tg_h, 1, 1, tck*1.000);       // (Handle, TS Number, Bclk Phase Number, Value)
	    UTL_AddTgBclk(tg_h, 1, 1, tck*0.500);       // (Handle, TS Number, Bclk Phase Number, Value)
        UTL_AddTgCclk(tg_h, 1, 1, tck*0.000);       // (Handle, TS Number, Cclk Phase Number, Value)
  	}else{                                          //NRZB NRZBC 
	    UTL_AddTgAclk(tg_h, 1, 1, tck*1.000);       // (Handle, TS Number, Bclk Phase Number, Value)
	    UTL_AddTgBclk(tg_h, 1, 1, tck*0.000);       // (Handle, TS Number, Bclk Phase Number, Value)
        UTL_AddTgCclk(tg_h, 1, 1, tck*0.500);       // (Handle, TS Number, Cclk Phase Number, Value)
    }
    UTL_AddTgStrb(tg_h, 1, 1, tck*0.000+offset);    // (Handle, TS Number, Cclk Phase Number, Value)
    UTL_AddTgStrb(tg_h, 1, 2, tck*0.500+offset);    // (Handle, TS Number, Cclk Phase Number, Value)
	UTL_SendTg(tg_h);
	UTL_DeleteHandle(tg_h);
}
static void pin_condition_frun(char *pinlist, TEST_testitem *testarg)
{
    const RadioButton wfl[]=WAVEFORM;

    PinHandle pf_h=UTL_GetPinHandle();
    UTL_InitializePinHandle(pf_h);
    UTL_SetPinViNumber(pf_h, 1); 

    UTL_SetPinDrWaveform(pf_h, wfl[FRUNARG.wfnu]);  // Waveform DNRZ
    UTL_SetPinDrClock(pf_h, UT_PIN_BCLK, 1);        // (Handle, Kind of Clk, Phase Number)
    UTL_SetPinDrClock(pf_h, UT_PIN_CCLK, 1);        // (Handle, Kind of Clk, Phase Number)
   
    if(FRUNARG.wfnu==14 || FRUNARG.wfnu==15){
        UTL_AddPinPdsA(pf_h , UT_SIG_C(1), 1);      // (Handle, Data , CYP Number)
    }else if(FRUNARG.wfnu>11){
        UTL_AddPinPdsA(pf_h, UT_SIG_C(0), 1);       // (Handle, Data , CYP Number)
        UTL_AddPinPdsB(pf_h, UT_SIG_C(1), 1);       // (Handle, Data , CYP Number)
    }else{
        UTL_AddPinPdsA(pf_h, UT_SIG_C(0), 1);       // (Handle, Data , CYP Number)
    }
    UTL_SetPinDcConnect (pf_h, UT_ON);
    UTL_SendPin(pf_h, pinlist);
    UTL_DeleteHandle(pf_h); 
}

static void level_setting(int channel , double high, double low)
{
    ViHandle vi_h=UTL_GetViHandle();
    UTL_SetViHigh   (vi_h, high);     
    UTL_SetViLow    (vi_h, low);     
    UTL_SetViHvDr   (vi_h, UT_OFF);
    UTL_SendVi      (vi_h, channel);
    UTL_DeleteHandle(vi_h);

    VoHandle vo_h=UTL_GetVoHandle();
    UTL_SetVoHigh   (vo_h, 0.5);     
    UTL_SetVoLow    (vo_h, 0.5);     
    UTL_SendVo      (vo_h, channel);
    UTL_DeleteHandle(vo_h);

    VtHandle vt_h = UTL_GetVtHandle();
    UTL_SetVt       (vt_h, 0.5);
    UTL_SendVt      (vt_h, channel);
    UTL_DeleteHandle(vt_h);  
}

static void pin_list(TEST_testitem *testarg)
{
    int *plst, pcnt, pidx;
    UT_PIN pin;

    if(FRUNARG.pc==0x020){ //For PAUSE Test
        UTL_CreatePinList("IOPIN");
        UTL_SetPinType   ("IOPIN", UT_PINTYPE_PIN);
        UTL_AddPinNumber ("IOPIN", 1);
    }
    if(FRUNARG.pc!=0x020){ //For PAUSE Test    
        UTL_CreatePinList("IOPIN");
        UTL_SetPinType("IOPIN", UT_PINTYPE_PIN);
        UTSOCK_Info_GetDutPinList(UT_SOCKET_PINTYPE_IO, &plst, &pcnt);
        for(pidx=0; pidx<pcnt; pidx++){
            pin = plst[pidx];
            if(25<=pin%64){
                continue; //LVDR
            }
            UTL_AddPinNumber("IOPIN", pin);
        }
    }
    return;
}

static void SetPinOpen(void)
{
    PinHandle pinh;
    pinh=UTL_GetPinHandle();
    UTL_SetPinOpen(pinh,UT_ON);
    UTL_SendPin(pinh,"IOPIN");
    UTL_DeleteHandle(pinh);
}

static void start_fct(TEST_testitem *testarg){
	//               wfnu 0  1  2  3  4  5  6  7  8  9 10 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21
    const int mode1[] = { 1, 3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2};
    const int mode2[] = { 1, 3, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,  1,  3,  1,  3,  1,  3,  1,  3,  1,  3};//after stop frun

    double ttt1,ttt2;
    int ovf;
    char *PatName;
    char *tname;
	FctHandle fct_h = UTL_GetFctHandle();
    PowerCtrlHandle pch;
    MpatHandle h;
    h = UTL_GetMpatHandle();
    pch = UTL_GetPowerCtrlHandle();

    tname = UTL_ReadTestName();
    printf("TEST NAME : %s\n",tname);

    PatName="pat_frun.mpa";
    UTL_SetFctMpatName   (fct_h, PatName);
    UTL_SetFctFailInhibit(fct_h, UT_ON);
    UTL_SetFctStartPc    (fct_h, FRUNARG.pc);
    UTL_SetFctNoWait     (fct_h, UT_OFF);
    if(FRUNARG.pc==0x040){ //For PAUSE Test
        UTL_SetFctNoWait(fct_h, UT_ON);
    }

    //UTL_ExecCalb("calfile","NOMBLOCKCHK NOPBLOCKCHK NOMBIDCHK NOPBIDCHK");

    UTL_SetWet();
    UTL_AddPowerCtrlAll(pch);
    UTL_OnPowerCtrl(pch);

    UTL_StartFrun();

    if(FRUNARG.pc==0x020){ // For Patern Burst Test
        adc_condition();
    }

    UTL_StartTimer(UT_TIMER_R10US);
	UTL_StartFct(fct_h);
    ttt1=UTL_ReadTimer(&ovf);
    printf("*************StartFct Time: %lf\n",ttt1);fflush(stdout);

    if(FRUNARG.pc==0x020){ // For Patern Burst Test
        adc_history_read(mode1[FRUNARG.wfnu], "IOPIN");
//        display(funcresult(0));        
    }

    if(FRUNARG.pc!=0x020){ // For Patern Burst Test
        if(FRUNARG.afterstopfrun==0){
            MeasDC(mode1[FRUNARG.wfnu], "IOPIN");
            display(funcresult(0));
        }
    }

    if(FRUNARG.pc==0x010){ //For WAIT Test
        UTL_SetFctContinue(fct_h, UT_ON);
	    UTL_StartFct      (fct_h);
    }

    UTL_StopFct();
    UTL_StopFrun();
	if(FRUNARG.afterstopfrun!=0){
        MeasDC(mode2[FRUNARG.wfnu], "IOPIN");
        display(funcresult(0));
	}

    UTL_ResetWet();
    UTL_OffPowerCtrl(pch);

	UTL_DeleteHandle	(pch);
	UTL_DeleteHandle	(fct_h);
}

void samplingrate_setting(void)
{
    SamplingRateHandle sr_h=UTL_GetSamplingRateHandle();
    UTL_SetSamplingRate (sr_h, 5e-6);
    UTL_SendSamplingRate(sr_h);
    UTL_DeleteHandle(sr_h);
}

void dc_setting(void)
{
    DcHandle dc_h = UTL_GetDcHandle();
    UTL_SetDcMode  (dc_h, UT_DCT_MVM);
    UTL_SetDcSource(dc_h, -1.0e-6);
    UTL_SetDcSrange(dc_h, 2.0e-3, -2.0e-3);
    UTL_SetDcMrange(dc_h, 7.00, -0.30);
    UTL_SetDcPclamp(dc_h, 2.00);
    UTL_SetDcMclamp(dc_h, -0.60);
    
    UTL_SetDcLimitHigh(dc_h, 1.10, UT_OFF);
    UTL_SetDcLimitLow (dc_h, 0.90, UT_OFF);
    
    UTL_SetDcMeasCnt  (dc_h, 100);
    UTL_SendDc(dc_h, 1);
    UTL_DeleteHandle(dc_h);
}

void adc_condition(void)
{
    dc_setting();
    samplingrate_setting();

    AdcHandle adc_h=UTL_GetAdcHandle();
    UTL_SetAdcPgEnable   (adc_h, UT_ON);
    UTL_SetAdcStartCycle (adc_h, UT_ADC_C(10));
    UTL_SetAdcInput      (adc_h, UT_ADC_DC(1));
    UTL_SetAdcPinList    (adc_h, "IOPIN");
    UTL_SetAdcHistoryMode(adc_h, UT_ON);
    UTL_SendAdc          (adc_h, 1);
    UTL_DeleteHandle(adc_h);

    UTL_ResetAdcHistoryCount(UT_ADC_TYPE_DC);
}

void adc_history_read(int lmode, char *pinlist)
{
    double total_data=0;
    int test_result=0;
    int i=0;
    DSlider *data;
    CheckButton ovc=0;
    DutCursor dutc;
    UT_DUT dut;
    PinCursor pinc;
    UT_PIN pin;

    if(DEBUG==1 )printf("###lmode=%d\n",lmode);fflush(stdout);

    UTL_WaitAdc(UT_ADC_TYPE_DC);
    int hcnt = UTL_ReadAdcHistoryCount(UT_ADC_TYPE_DC, &ovc);
    if(ovc==UT_ON){printf("\n***Error.Please Check Program.\n");fflush(stdout);UTL_Stop();}
//    if(DEBUG==1){printf("Count value: %d\n", hcnt);fflush(stdout);}
    
    data = (DSlider *)malloc(sizeof(DSlider)*hcnt);
    
    DctReadPinHandle drp_h = UTL_GetDctReadPinHandle();
    pinc = UTL_GetPinCursor(pinlist);
    while((pin=UTL_NextPin(pinc))!=UT_NOMORE){
        dutc = UTL_GetDutCursor(UT_CDUT);
        while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
            UTL_SetDctReadPinDut        (drp_h, dut);
            UTL_SetDctReadPinType       (drp_h, UT_PINTYPE_PIN);
            UTL_SetDctReadPinNumber     (drp_h, pin);
            UTL_ReadDctPinAllHistoryData(drp_h, data, hcnt);
            total_data=0;
            for(i=0; i<hcnt; i++){
//                if(DEBUG==1)printf("DUT=%d, data:%1f\n", dut, data[i]);fflush(stdout);
                total_data = total_data + data[i];
            }
            total_data = total_data / hcnt;
//            if(DEBUG==1)printf("DUT=%d, data:%1f\n", dut, total_data);fflush(stdout);

//            if(DEBUG==1 )printf("###lmode=%d\n",lmode);fflush(stdout);
            switch(lmode){
                case 1:
                    if(total_data>0.1 || total_data<-0.1){test_result=1;}
                    break;
                case 2:
                    if(total_data>0.6 || total_data<0.4){test_result=1;}
                    break;
                case 3:
                    if(total_data>1.1 || total_data<0.9){test_result=1;}
                    break;
            }
        }
    }
    free(data);
    display(test_result);
    if(test_result==0){testresult_pass4alldut(UTL_ReadTestName());}
    if(test_result==1){testresult_fail4alldut(UTL_ReadTestName());}
}

static void MeasDC(int lmode, char *pinlist){
    DcHandle dh = UTL_GetDcHandle();
    UTL_SetDcMode(dh,UT_DCT_MVM);
//  UTL_SetDcMode(dh,UT_DCT_ISVM);
    UTL_SetDcSource(dh,-1.0e-6);
    UTL_SetDcSrange(dh, 2.0e-3, -2.0e-3);
    UTL_SetDcMrange(dh, 7.0, -0.30);
    UTL_SetDcPclamp(dh, 2.0 );
    UTL_SetDcMclamp(dh,-0.60);
     
    if(DEBUG==1 )printf("###lmode=%d\n",lmode);fflush(stdout);
    switch(lmode){
        case 1:
            UTL_SetDcLimitHigh(dh,  0.10, UT_ON);
            UTL_SetDcLimitLow (dh, -0.10, UT_ON);
            break;
        case 2:
            UTL_SetDcLimitHigh(dh,  0.60, UT_ON);
            UTL_SetDcLimitLow (dh,  0.40, UT_ON);
            break;
        case 3:
            UTL_SetDcLimitHigh(dh,  1.10, UT_ON);
            UTL_SetDcLimitLow (dh,  0.90, UT_ON);
            break;
    }

    UTL_SetDcMeasCnt(dh, 100);
    UTL_SendDc(dh,1);

    DctHandle dch = UTL_GetDctHandle();
    UTL_SetDctPinList(dch,pinlist);
	UTL_SetDctRelayMode(dch,UT_DCT_SWAP);
    UTL_SetDctPinVi(dch,UT_ON);
    UTL_MeasDct(dch);
        
    UTL_DeleteHandle(dch);
    UTL_DeleteHandle(dh);
}

static int funcresult(int pfresult)
{   
    int result=0;
    DutCursor dutcur;
    if(pfresult==0) dutcur=UTL_GetDutCursor(UT_FDUT);
    if(pfresult==1) dutcur=UTL_GetDutCursor(UT_PDUT);

    UT_DUT dut=0;
    while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
        result=result | 0x1<<dut-1;
    }
    
    return result;
}

static void display(int result)
{
     printf("\n%-32s",UTL_ReadTestName());
     if(result==0){
         //testresult_pass4alldut(UTL_ReadTestName());
         printf(" ***PASS");
     }else{
         //testresult_fail4alldut(UTL_ReadTestName());
	 if(result==3){ printf("LOG CHECK!!");
         }else if(result!=0) printf(" FAIL** dut:%x",result); 
     }   
     fflush(stdout);
}

void frun_check(TEST_testitem *testarg)
{
    set_interleave_mode(1);
    pin_list(testarg);              // PinList Setting
    SetPinOpen();

    level_setting(1, 1.0, 0.0);     // VIH=2.0V,VIL=0V
    timing_setting(testarg);        // Timing Setting
    pin_condition_frun("IOPIN", testarg);

    if(DEBUG==1)printf("*****wfnu=%d pc=0x%03x\n", FRUNARG.wfnu, FRUNARG.pc); fflush(stdout);
    start_fct(testarg);             //mode  1:0.0V/2:500MV/3:1.0V

    return;
}
