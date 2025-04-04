#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include "test.h"
#include <sys/time.h>
#include "test_struct.h"

#define DEBUG 1          //0:Not Debug Mode,1:Debug Mode,2:Add Option
#define BURST 0          //Pattern Burst Not supported:0 suppoted:1
#define MAXDUT 16

static int funcresult(int pfresulet);
static void display(int result);
static void timeset(double stime);

static void pin_list();
static void pin_condition(char *wav);                       //FIXL or FIXH or NRZB
static void pin_conditionCp();
static void level_setting( int channel, double high, double low);
static void timing_setting();
static void get_pin_condition();
static void adc_setting(char *pinty);
static void dc_setting(char *pinlist,int cnt);
static void vs_setting(int vsn, double vsorc,int cnt);
// void adc_start_pps();
// void adc_start_dc();
// void adc_start_inhi();
// void adc_start_samp();
// void adc_start_multi1();
// void adc_start_multi2();
// void adc_start_jikken1();
// void adc_start_jikken2();

#if 0
int test_main(int argc, char *argv)
{

	printf("\n***TEST START***\n");fflush(stdout);

	pin_list();                                                       // PinList Setting
        timeset(10e-3);

        TestHandle Test_H = UTL_GetTestHandle();
//      UTL_SetTestAction(Test_H, adc_start_pps    ); UTL_Test(Test_H, "TN501 ADC_Start_Check(PPS)      ");
//      UTL_SetTestAction(Test_H, adc_start_dc     ); UTL_Test(Test_H, "TN502 ADC_Start_Check(DC)       ");
//      UTL_SetTestAction(Test_H, adc_start_inhi   ); UTL_Test(Test_H, "TN503 ADC_Start_Inhi_Check      ");
//Asakaze5 notsupprted      UTL_SetTestAction(Test_H, adc_start_samp   ); UTL_Test(Test_H, "TN504 ADC_Start_Samp_Check      ");
//      UTL_SetTestAction(Test_H, adc_start_multi1 ); UTL_Test(Test_H, "TN505 ADC_Start_Multi_Check(PPS)");
//      UTL_SetTestAction(Test_H, adc_start_multi2 ); UTL_Test(Test_H, "TN506 ADC_Start_Multi_Check(DC) ");
//      UTL_SetTestAction(Test_H, adc_start_jikken1); UTL_Test(Test_H, "TN507 ADC_Start_Jikken(DC)      ");
        UTL_SetTestAction(Test_H, adc_start_jikken2); UTL_Test(Test_H, "TN508 ADC_Start_Jikken(PPS)     ");


	printf("***TEST END***\n");fflush(stdout);


return 0;
}
#endif

static void timeset(double stime)
{
    PowerSeqHandle PowerSeq_H = UTL_GetPowerSeqHandle();
    UTL_AddPowerSeqVsAll    (PowerSeq_H, 1);
    UTL_AddPowerSeqViAll    (PowerSeq_H, 1);
    UTL_AddPowerSeqVtAll    (PowerSeq_H, 1);
    UTL_AddPowerSeqOthers   (PowerSeq_H, 1);
    UTL_SetPowerSeqWaitTime (PowerSeq_H, 1, stime);
    UTL_SendPowerSeq        (PowerSeq_H);
    UTL_DeleteHandle        (PowerSeq_H);

}

static void timing_setting(void){
  	DSlider tck1 =200e-9;                                               // 440Mbps=4.5e-9,400Mbps=5e-9,200Mbps=10e-9,100Mbps=20e-9
  	DSlider tck2 =  1e-3;                                               // 440Mbps=4.5e-9,400Mbps=5e-9,200Mbps=10e-9,100Mbps=20e-9
  	DSlider tck3 =  5e-9;                                               // 440Mbps=4.5e-9,400Mbps=5e-9,200Mbps=10e-9,100Mbps=20e-9
//	DSlider tck2 =  1e-3;                                               // 440Mbps=4.5e-9,400Mbps=5e-9,200Mbps=10e-9,100Mbps=20e-9

        TgHandle tg_h = UTL_GetTgHandle();
	UTL_AddTgRate		(tg_h, 1 ,     tck1      );                           // (Handle, TS Number, Value)
	UTL_AddTgBclk		(tg_h, 1 , 1 , tck1*0.500);                 // (Handle, TS Number, Bclk Phase Number, Value)
	UTL_AddTgRate		(tg_h, 2 ,     tck2      );                           // (Handle, TS Number, Value)
	UTL_AddTgBclk		(tg_h, 2 , 1 , tck2*0.500);                 // (Handle, TS Number, Bclk Phase Number, Value)
	UTL_AddTgRate		(tg_h, 3 ,     tck3      );                           // (Handle, TS Number, Value)
	UTL_AddTgBclk		(tg_h, 3 , 1 , tck3*0.500);                 // (Handle, TS Number, Bclk Phase Number, Value)
	UTL_SendTg		(tg_h);
	UTL_DeleteHandle	(tg_h);
}

static void pin_condition(char *wav){
        PinHandle pf_h = UTL_GetPinHandle();
        UTL_InitializePinHandle (pf_h);
        UTL_ClearPinPdsA(pf_h);
        UTL_ClearPinPdsB(pf_h);

        UTL_SetPinViNumber      (pf_h , 1); 

        if(strcmp(wav,"FIXL")==0){
            printf("Waveform : FIXL\n");fflush(stdout);
            UTL_SetPinDrWaveform    (pf_h , UT_WAV_FIXL);                        // Waveform DNRZ
        }else if(strcmp(wav,"FIXH")==0){
            printf("Waveform : FIXH\n");fflush(stdout);
            UTL_SetPinDrWaveform    (pf_h , UT_WAV_FIXH);                        // Waveform DNRZ
        }else if(strcmp(wav,"NRZB")==0){
            printf("Waveform : NRZB\n");fflush(stdout);
            UTL_SetPinDrWaveform    (pf_h , UT_WAV_NRZB);                        // Waveform DNRZ
            UTL_SetPinDrClock       (pf_h , UT_PIN_BCLK , 1 );                  // (Handle, Kind of Clk, Phase Number)
            UTL_SetPinVtNumber      (pf_h , 1);                                 // Vt Number
            UTL_SetPinIoCtrl        (pf_h , UT_ON);                             // IO Controll
            UTL_SetPinTerm          (pf_h , UT_ON);                             // 50ohm Termination connect
            UTL_SetPinVoNumber      (pf_h , 1); 
            UTL_SetPinDreNumber     (pf_h , 1);                                 // (Handle, DRECLOCK Number)
            UTL_SetPinDreWaveform   (pf_h , UT_DREWAV_NRZ);                     // (Handle, DRE Wave Form)
            UTL_SetPinDreClock      (pf_h , 1);                                 // (Handle, DREn)
            UTL_AddPinPdsA          (pf_h , UT_SIG_C(1)  , 1 );     // (Handle, Data , CYP Number)
        }else{printf("\nError is occured. please check Main Program.\n");}

        UTL_SetPinDcConnect     (pf_h ,UT_ON);
        UTL_SendPin             (pf_h , "DR");
//        UTL_SendPin             (pf_h , "ALLPIN");
        UTL_DeleteHandle        (pf_h); 
}

static void level_setting(int channel , double high, double low){
        ViHandle vi_h = UTL_GetViHandle();
        UTL_SetViHigh           (vi_h , high );     
        UTL_SetViLow            (vi_h , low  );     
        UTL_SetViHvDr           (vi_h , UT_OFF);
        UTL_SendVi              (vi_h , channel);

        VoHandle vo_h = UTL_GetVoHandle();
        UTL_SetVoHigh           (vo_h , 0.5  );     
        UTL_SetVoLow            (vo_h , 0.5  );     
        UTL_SendVo              (vo_h , channel);

        VtHandle vt_h = UTL_GetVtHandle();
        UTL_SetVt        (vt_h, 0.5  );
        UTL_SendVt(vt_h, channel );

        UTL_DeleteHandle(vi_h);
        UTL_DeleteHandle(vo_h);
        UTL_DeleteHandle(vt_h);
       
}


static void pin_list(void){
        int i,j,k;
        int pin_cnt,pin_grp;

      	UTL_CreatePinList   ("DR");
      	UTL_SetPinType	    ("DR",UT_PINTYPE_PIN);
        UTL_AddPinNumber    ("DR", 1    );
//      UTL_AddPinNumber    ("DR", 2    );

     	UTL_CreatePinList	("ALLPIN");
     	UTL_SetPinType		("ALLPIN",UT_PINTYPE_PIN);

        pin_cnt=18;
        pin_grp=1;
        for(i=1;i<=pin_grp;i++){
           for(j=1;j<=pin_cnt;j++){
               k=(i-1)*32+j;
                       if(DEBUG==1){printf("****AllPin Pin:%d\n",k);fflush(stdout);}
                       UTL_AddPinNumber ("ALLPIN", k    );
           }
        }


}


static void dc_setting(char *pinlist,int cnt)
{
        DcHandle dh = UTL_GetDcHandle();
        UTL_SetDcMode(dh,UT_DCT_MVM);
//      UTL_SetDcMode(dh,UT_DCT_ISVM);
        UTL_SetDcSource(dh,-1.0e-6);
        UTL_SetDcSrange(dh, 2.0e-3, -2.0e-3);
        UTL_SetDcMrange(dh, 7.0, -0.30);
        UTL_SetDcPclamp(dh, 2.0 );
        UTL_SetDcMclamp(dh,-0.60);

        UTL_SetDcLimitHigh(dh,1.10 ,UT_ON);
        UTL_SetDcLimitLow (dh,0.90 ,UT_ON);

        UTL_SetDcMeasCnt(dh, cnt);
        UTL_SendDc(dh,1);
        
        UTL_DeleteHandle(dh);
}

static void vs_setting(int vsn,double vsorc,int cnt)
{
    VsHandle Vs_H = UTL_GetVsHandle();
    UTL_SetVsMode      (Vs_H,   UT_DCT_VSIM);
    UTL_SetVsSource    (Vs_H,        vsorc );
    UTL_SetVsSrange    (Vs_H,   2.00,     0);
    UTL_SetVsMrange    (Vs_H, 10e-3, -10e-3);
    UTL_SetVsLimitHigh (Vs_H,  1.1e-3,UT_OFF);
    UTL_SetVsLimitLow  (Vs_H,  0.9e-3,UT_OFF);
    UTL_SetVsSlewRate  (Vs_H,   4e-3        );
    UTL_SetVsMeasCnt   (Vs_H,          cnt );
    UTL_SendVs         (Vs_H,          vsn );
    UTL_DeleteHandle   (Vs_H);
}

static void adc_setting(char *pinty)
{
        AdcHandle adch = UTL_GetAdcHandle();       
        UTL_SetAdcPgEnable       ( adch , UT_ON          );
        UTL_SetAdcStartCycle     ( adch , UT_ADC_C(10)    );
        if(strcmp(pinty,"DC")==0){
             UTL_SetAdcInput  ( adch , UT_ADC_DC(1));
             printf("\nDC Entry!!\n");fflush(stdout);
             UTL_SetAdcPinList( adch , "DR"        );
             UTL_SetAdcHistoryMode    ( adch , UT_OFF         );
        }else if(strcmp(pinty,"VS")==0){
             UTL_SetAdcInput( adch , UT_ADC_VS(1));
             printf("\nVS Entry!!\n");fflush(stdout);
             UTL_SetAdcHistoryMode    ( adch , UT_ON          );

        }else{printf("\nError is occured. please check Main Program.\n");}
         
        UTL_SetAdcMeasMode       ( adch , UT_ADC_NORMAL  );
        UTL_SetAdcHistoryMode    ( adch , UT_ON          );
        UTL_SendAdc              ( adch ,  1             );
       
        UTL_DeleteHandle         ( adch );
 
}

void adc_start_pps(TEST_testitem *testarg)
{
    int result=0;
    int i,j;
    CheckButton ovc=0;
    DctHandle Dct_H;
    PinHandle Pin_H;
    PowerCtrlHandle PowerCtrl_H;
    DSlider *rdata;
    DSlider *data;
    DSlider rdata2={0.0,};
    DutCursor dutc;
    UT_DUT dut;


    vs_setting(  1 , 1.0 , 2  );                     //(ch_number,VSource Level,MeasCnt)
    adc_setting("VS");

    UTL_SetWet();
    UTL_OnPowerSeq();
    UTL_ResetAdcHistoryCount(UT_ADC_TYPE_VS);

    Pin_H = UTL_GetPinHandle();
    FctHandle Fct_H = UTL_GetFctHandle();
    UTL_SetFctMpatName      (Fct_H, "pat_adc.mpa");
    UTL_SetFctFailInhibit   (Fct_H, UT_ON);
    UTL_SetFctStartPc       (Fct_H, 0x000);
    UTL_SetFctNoWait        (Fct_H, UT_OFF);
    UTL_MeasFct             (Fct_H);

    UTL_DeleteHandle        (Fct_H);

    int hcnt = UTL_ReadAdcHistoryCount(UT_ADC_TYPE_VS, &ovc);
    if(ovc==UT_ON){printf("\n****Error.Please Check Program.\n");fflush(stdout);UTL_Stop();}
    printf("count value: %d\n",hcnt);fflush(stdout);
    
    data  = (DSlider *)malloc(sizeof(DSlider)*hcnt);

    DctReadPinHandle dcrph = UTL_GetDctReadPinHandle();
    dutc = UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc)) != UT_NOMORE){
         UTL_SetDctReadPinDut(dcrph,dut);
         UTL_SetDctReadPinType(dcrph, UT_PINTYPE_VS );
         UTL_SetDctReadPinNumber(dcrph,  1  );
         UTL_ReadDctPinAllHistoryData(dcrph, data, hcnt);
         for(i=0;i<hcnt;i++){
              printf(" DUT:%d,data:%lf\n", dut,data[i]*1000);fflush(stdout);
              if(data[i]<1.1e-3 && data[i]>0.9e-3){result=result | 0;}
              else{result=result | 0x1 << dut-1;}
         }
    }

    display(result);


}

void adc_start_dc(TEST_testitem *testarg)
{
    int result=0;
    int i,j;
    double rdata=0.0;
    DSlider *data;
    CheckButton ovc=0;
    DctHandle Dct_H;
    PinHandle Pin_H;
    PowerCtrlHandle PowerCtrl_H;
    DutCursor dutc;
    UT_DUT dut;

    pin_list();                                                       // PinList Setting
    level_setting( 1  , 1.0 , 0.0);              // VIH=1.0V,VIL=0V
    timing_setting();
    pin_condition("FIXH");                       // Set FIXH waveform
    dc_setting("DR",   5 );                      //(pinlist_name,MeasCnt)
//    dc_setting("ALLPIN",   5 );                      //(pinlist_name,MeasCnt)
    adc_setting("DC");

    UTL_SetWet();
    UTL_OnPowerSeq();
    UTL_ResetAdcHistoryCount(UT_ADC_TYPE_DC);

    Pin_H = UTL_GetPinHandle();
    FctHandle Fct_H = UTL_GetFctHandle();
    UTL_SetFctMpatName      (Fct_H, "pat_adc.mpa");
    UTL_SetFctFailInhibit   (Fct_H, UT_ON);
    UTL_SetFctStartPc       (Fct_H, 0x000);
    UTL_SetFctNoWait        (Fct_H, UT_OFF);
    UTL_MeasFct             (Fct_H);
    UTL_DeleteHandle        (Fct_H);
 
    UTL_WaitAdc(UT_ADC_TYPE_DC);
    int hcnt = UTL_ReadAdcHistoryCount(UT_ADC_TYPE_DC, &ovc);
    if(ovc==UT_ON){printf("\n****Error.Please Check Program.\n");fflush(stdout);UTL_Stop();}
    printf("count value: %d\n",hcnt);fflush(stdout);

    data  = (DSlider *)malloc(sizeof(DSlider)*hcnt);

    DctReadPinHandle dcrph = UTL_GetDctReadPinHandle();
    dutc = UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc)) != UT_NOMORE){
         UTL_SetDctReadPinDut(dcrph,dut);
         UTL_SetDctReadPinType(dcrph, UT_PINTYPE_PIN);
         UTL_SetDctReadPinNumber(dcrph,  1  );
         UTL_ReadDctPinAllHistoryData(dcrph, data, hcnt);
         for(i=0;i<hcnt;i++){
              if(DEBUG==1)printf(" data:%lf\n", data[i]);fflush(stdout);
              if(data[i]<1.1 && data[i]>0.9){result=result | 0;}
              else{result=result | 0x1 << dut-1;}
         }
    }
    free(data);
    display(result);
}

void adc_start_inhi(TEST_testitem *testarg){
    int result=0;
    int i,j;
    CheckButton ovc=0;
    DSlider rdata;
    DSlider *data;
    DctHandle Dct_H;
    PinHandle Pin_H;
    PowerCtrlHandle PowerCtrl_H;
    DutCursor dutc;
    UT_DUT dut;

    pin_list();                                                       // PinList Setting
    level_setting( 1  , 1.0 , 0.0);              // VIH=1.0V,VIL=0V
    pin_condition("FIXH");                       // Set FIXL
    dc_setting("DR",  5  );                      //(pinlist_name,MeasCnt)

    AdcHandle adchon = UTL_GetAdcHandle();       
    UTL_SetAdcPgEnable       ( adchon , UT_ON         );        // Enable Mode SET
    UTL_SetAdcStartCycle     ( adchon , UT_ADC_C(10)    );
    UTL_SetAdcInput          ( adchon , UT_ADC_DC(1));
    UTL_SetAdcPinList        ( adchon , "DR"        );
    UTL_SetAdcMeasMode       ( adchon , UT_ADC_NORMAL  );
    UTL_SetAdcHistoryMode    ( adchon , UT_ON          );
    UTL_SendAdc              ( adchon ,  1             );
    UTL_DeleteHandle         ( adchon );


    Pin_H = UTL_GetPinHandle();
    FctHandle Fct_Hon = UTL_GetFctHandle();
    UTL_SetFctMpatName      (Fct_Hon, "pat_adc.mpa");
    UTL_SetFctFailInhibit   (Fct_Hon, UT_ON);
    UTL_SetFctStartPc       (Fct_Hon, 0x000);
    UTL_SetFctNoWait        (Fct_Hon, UT_OFF);
    UTL_StartFct             (Fct_Hon);
    UTL_DeleteHandle        (Fct_Hon);


    UTL_ResetAdcHistoryCount(UT_ADC_TYPE_DC);

    AdcHandle adch = UTL_GetAdcHandle();       
    UTL_SetAdcPgEnable       ( adch , UT_OFF         );        // Disable Mode SET
    UTL_SetAdcStartCycle     ( adch , UT_ADC_C(10)    );
    UTL_SetAdcInput          ( adch , UT_ADC_DC(1));
    UTL_SetAdcPinList        ( adch , "DR"        );
    UTL_SetAdcMeasMode       ( adch , UT_ADC_NORMAL  );
    UTL_SetAdcHistoryMode    ( adch , UT_ON          );
    UTL_SendAdc              ( adch ,  1             );
    
    UTL_DeleteHandle         ( adch );


    Pin_H = UTL_GetPinHandle();
    FctHandle Fct_H = UTL_GetFctHandle();
    UTL_SetFctMpatName      (Fct_H, "pat_adc.mpa");
    UTL_SetFctFailInhibit   (Fct_H, UT_ON);
    UTL_SetFctStartPc       (Fct_H, 0x000);
    UTL_SetFctNoWait        (Fct_H, UT_OFF);
    UTL_MeasFct             (Fct_H);
    UTL_DeleteHandle        (Fct_H);

    UTL_WaitAdc(UT_ADC_TYPE_DC);
    int hcnt = UTL_ReadAdcHistoryCount(UT_ADC_TYPE_DC, &ovc);
    if(ovc==UT_ON){printf("\n****Error.Please Check Program.\n");fflush(stdout);UTL_Stop();}
    printf("count value: %d\n",hcnt);fflush(stdout);
    printf("if count value is 0, It is PASS Judgement.\n");fflush(stdout);
    if(hcnt!=0){result=0x1;}

    display(result);
}

#if 0
void adc_start_samp(TEST_testitem *testarg)
{
    int result=0;
    int i,j,ovc;
    double ttt1,ttt2,ttt3,ovh;
    int ovf;
    DctHandle Dct_H;
    PinHandle Pin_H;
    PowerCtrlHandle PowerCtrl_H;
    SamplingRateHandle srh;

    
    for(i=0;i<=2;i++){
         srh = UTL_GetSamplingRateHandle();
         if(i==0)UTL_SetSamplingRate(srh,10e-6);                    //SamplingRate:10us
         if(i==1)UTL_SetSamplingRate(srh,10e-5);                    //SamplingRate:100us
         if(i==2)UTL_SetSamplingRate(srh, 1e-3);                    //SamplingRate:1ms
         UTL_SendSamplingRate(srh);

         vs_setting(  1 , 1.0, 100);                                    //(ch_number,VSource Level,MeasCnt)
         adc_setting("VS");

         UTL_ResetAdcHistoryCount   ( UT_ADC_TYPE_VS );

         Pin_H = UTL_GetPinHandle();
         FctHandle Fct_H = UTL_GetFctHandle();
         UTL_SetFctMpatName      (Fct_H, "pat_adc.mpa");
         UTL_SetFctFailInhibit   (Fct_H, UT_ON);
         UTL_SetFctStartPc       (Fct_H, 0x000);
         UTL_SetFctNoWait        (Fct_H, UT_OFF);

         UTL_StartTimer(UT_TIMER_R10US);

         UTL_MeasFct            (Fct_H);
         UTL_DeleteHandle        (Fct_H);

         UTL_WaitAdc(UT_ADC_TYPE_DC);
         int hcnt = UTL_ReadAdcHistoryCount(UT_ADC_TYPE_DC, &ovc);
         if(ovc==UT_ON){printf("\n****Error.Please Check Program.\n");fflush(stdout);UTL_Stop();}
         printf("count:%d\n",hcnt);fflush(stdout);

         if(i==0){ttt1=UTL_ReadTimer(&ovf);printf("MeasFct Time: %lf\n",ttt1);fflush(stdout);}
         if(i==1){ttt2=UTL_ReadTimer(&ovf);printf("MeasFct Time: %lf\n",ttt2);fflush(stdout);}
         if(i==2){ttt3=UTL_ReadTimer(&ovf);printf("MeasFct Time: %lf\n",ttt3);fflush(stdout);}

    }
    ovh=ttt1-((ttt2-ttt1)/9);          
    int permlim=0.95; //0.90;     //limit percentage 95% or 90% is PASS
    int perplim=1.05; //0.90;     //limit percentage 95% or 90% is PASS
    if((ttt1-ovh)*10*permlim<=(ttt2-ovh) && (ttt1-ovh)*10*perplim>=(ttt2-ovh)){
         result=result | 0x0;
    }else{result=result | 0x1;}
    if((ttt2-ovh)*10*permlim<=(ttt3-ovh) && (ttt2-ovh)*10*perplim>=(ttt3-ovh)){
         result=result | 0x0;
    }else{result=result | 0x1;}


    display(result);
}
#endif

void adc_start_multi_pps(TEST_testitem *testarg){   //PSM Unit
    int result=0;
    int i,j,gnum,gmax,ovf;
    int mcnt = 1023;//1023 ;//2048;                         //MeasCnt
    //int mcnt = 2;//1023 ;//2048;                         //MeasCnt
    int acnt = 4;                            //ADC START Cnt
    CheckButton ovc=0;
    DSlider *data;
    DutCursor dutc;
    UT_DUT dut;

    SamplingRateHandle srh = UTL_GetSamplingRateHandle();
    UTL_SetSamplingRate(srh,  5e-6);                    //SamplingRate:10us
    UTL_SendSamplingRate(srh);
    UTL_DeleteHandle(srh);

    DctHandle Dct_H;
    PinHandle Pin_H;
    PowerCtrlHandle PowerCtrl_H;

#if BURST
    vs_setting(  1 , 0.0, mcnt);                     //(ch_number,VSource Level,MeasCnt)
#endif
    vs_setting(  1 , 1.0, mcnt);                     //(ch_number,VSource Level,MeasCnt)

    adc_setting("VS");

    gmax = UTL_GetAdcDutGroupMaxNumber(UT_ADC_TYPE_VS);
    if(DEBUG==1){printf("gmax:%d\n",gmax);fflush(stdout);}
    for(gnum=0;gnum<=gmax;gnum++){
         if(DEBUG==1)printf("gnum : %d\n",gnum);fflush(stdout);
         UTL_ResetAdcHistoryCount   ( UT_ADC_TYPE_VS );
         UTL_WriteAdcDutGroupNumber ( UT_ADC_TYPE_VS,gnum);

         Pin_H = UTL_GetPinHandle();
         FctHandle Fct_H = UTL_GetFctHandle();
         UTL_SetFctMpatName      (Fct_H, "pat_adc.mpa");
         UTL_SetFctFailInhibit   (Fct_H, UT_ON);
         UTL_SetFctStartPc       (Fct_H, 0x100);
         UTL_SetFctNoWait        (Fct_H, UT_OFF);
         UTL_MeasFct             (Fct_H);
         UTL_DeleteHandle        (Fct_H);
  
         UTL_WaitAdc(UT_ADC_TYPE_VS);
         int hcnt = UTL_ReadAdcHistoryCount(UT_ADC_TYPE_VS, &ovc);
         if(ovc==UT_ON){printf("\n****Error.Please Check Program.\n");fflush(stdout);UTL_Stop();}
         printf("count value: %d\n",hcnt);fflush(stdout);
         data  = (DSlider *)malloc(sizeof(DSlider)*hcnt);

         DctReadPinHandle dcrph = UTL_GetDctReadPinHandle();

//       dutc = UTL_GetDutCursor(UT_CDUT);
         dutc = UTL_GetAdcDutGroupDutCursor(UT_ADC_TYPE_VS,gnum);
         while((dut=UTL_NextDut(dutc)) != UT_NOMORE){
              UTL_SetDctReadPinDut(dcrph,dut);
              UTL_SetDctReadPinType(dcrph, UT_PINTYPE_VS );
              UTL_SetDctReadPinNumber(dcrph,  1  );
              UTL_ReadDctPinAllHistoryData(dcrph, data, hcnt);

              for(i=0;i<mcnt*acnt;i++){
                   if(DEBUG==1)printf("DUT : %d ,data[%d]:%lf\n",dut,i,data[i]*1000);fflush(stdout);
                   if(i>=mcnt*acnt*(dut-1) && i<mcnt+mcnt*acnt*(dut-1)){                                                                  //1st ADC START DATA
                        if(DEBUG==1)printf("1 str-end:0 - %d\n",mcnt);fflush(stdout);                //1st ADC START DATA
                        if(data[i]>= 0.9e-3 && data[i]<=1.1e-3){result = result | 0x0;                      //3rd ADC START DATA
//BURST                        if(data[i]>=-0.1 && data[i]<=0.1){result = result | 0x0;                      //1st ADC START DATA
                        }else{result = result | dut;}                                                                                     //1st ADC START DATA
                   }                                                                                                                      //1st ADC START DATA
                   if(i>=mcnt && i<mcnt*2){                                                           //2nd ADC START DATA
                        if(DEBUG==1)printf("2 str-end:%d - %d\n",mcnt,mcnt*2);fflush(stdout);         //2nd ADC START DATA
                        if(data[i]>= 0.9e-3 && data[i]<=1.1e-3){result = result | 0x0;                      //3rd ADC START DATA
//BURST                        if(data[i]>= 0.4e-3 && data[i]<=0.6e-3){result = result | 0x0;                      //2nd ADC START DATA
                        }else{result = result | dut;}                                                                                     //2nd ADC START DATA
                   }                                                                                                                      //2nd ADC START DATA
                   if(i>=mcnt*2 && i<mcnt*3){                                                         //3rd ADC START DATA
                        if(DEBUG==1)printf("3 str-end:%d - %d\n",mcnt*2,mcnt*3);fflush(stdout);       //3rd ADC START DATA
                        if(data[i]>= 0.9e-3 && data[i]<=1.1e-3){result = result | 0x0;                      //3rd ADC START DATA
                        }else{result = result | dut;}                                                                                     //3rd ADC START DATA
                   }                                                                                                                      //3rd ADC START DATA
                   if(i>=mcnt*3 && i<mcnt*4){                                                         //4th ADC START DATA
                        if(DEBUG==1)printf("4 str-end:%d - %d\n",mcnt*3,mcnt*4);fflush(stdout);       //4th ADC START DATA
                        if(data[i]>= 0.9e-3 && data[i]<=1.1e-3){result = result | 0x0;                      //3rd ADC START DATA
//BURST                        if(data[i]>= 1.4e-3 && data[i]<=1.6e-3){result = result | 0x0;                      //4th ADC START DATA
                        }else{result = result | dut;}                                                                                     //4th ADC START DATA
                   }                                                                                                                      //4th ADC START DATA
              }
         }
    }

    display(result);
} 

void adc_start_multi_dc(TEST_testitem *testarg){    //DC Unit
    int result=0;
    int i,j,gnum,gmax,ovf;
    int mcnt = 1023;//1024;                         //MeasCnt
    int acnt = 4;                            //ADC START Cnt
    CheckButton ovc=0;
//  DSlider data[MAXDUT*mcnt*acnt];
    DSlider *data;
    DutCursor dutc;
    UT_DUT dut;

    DctHandle Dct_H;
    PinHandle Pin_H;
    PowerCtrlHandle PowerCtrl_H;

    SamplingRateHandle srh = UTL_GetSamplingRateHandle();
    UTL_SetSamplingRate(srh,  5e-6);                    //SamplingRate:10us
    UTL_SendSamplingRate(srh);
    UTL_DeleteHandle(srh);

    pin_list();                                                       // PinList Setting
    level_setting( 1  , 1.0 , 0.0);              // VIH=1.0V,VIL=0V
    timing_setting();
    pin_condition("NRZB");                       // Set FIXH waveform
    dc_setting("DR", mcnt);                      //(ch_number,MeasCnt)
    adc_setting("DC");

    gmax = UTL_GetAdcDutGroupMaxNumber(UT_ADC_TYPE_DC);
    if(DEBUG==1)printf("gmax : %d\n",gmax);fflush(stdout);
    for(gnum=0;gnum<=gmax;gnum++){
         if(DEBUG==1)printf("gnum : %d\n",gnum);fflush(stdout);
         UTL_ResetAdcHistoryCount   ( UT_ADC_TYPE_DC );
         UTL_WriteAdcDutGroupNumber ( UT_ADC_TYPE_DC,gnum);

         Pin_H = UTL_GetPinHandle();
         FctHandle Fct_H = UTL_GetFctHandle();
         UTL_SetFctMpatName      (Fct_H, "pat_adc.mpa");
         UTL_SetFctFailInhibit   (Fct_H, UT_ON);
         UTL_SetFctStartPc       (Fct_H, 0x200);
         UTL_SetFctNoWait        (Fct_H, UT_OFF);
         UTL_MeasFct             (Fct_H);
         UTL_DeleteHandle        (Fct_H);
  
         UTL_WaitAdc(UT_ADC_TYPE_DC);
         int hcnt = UTL_ReadAdcHistoryCount(UT_ADC_TYPE_DC, &ovc);
         if(ovc==UT_ON){printf("\n****Error.Please Check Program.\n");fflush(stdout);UTL_Stop();}
         printf("count value: %d\n",hcnt);fflush(stdout);
         data  = (DSlider *)malloc(sizeof(DSlider)*hcnt);

         DctReadPinHandle dcrph = UTL_GetDctReadPinHandle();

//       dutc = UTL_GetDutCursor(UT_CDUT);
         dutc = UTL_GetAdcDutGroupDutCursor(UT_ADC_TYPE_DC,gnum);
         while((dut=UTL_NextDut(dutc)) != UT_NOMORE){
              UTL_SetDctReadPinDut(dcrph, dut );
              UTL_SetDctReadPinType(dcrph, UT_PINTYPE_PIN);
              UTL_SetDctReadPinNumber(dcrph,  1  );
              UTL_ReadDctPinAllHistoryData(dcrph, data, hcnt);

              for(i=0;i<mcnt*acnt;i++){
                   if(DEBUG==1)printf("DUT : %d ,data[%d]:%lf\n",dut,i,data[i]);fflush(stdout);
                   if(i<mcnt){                                                                   //1st ADC START DATA
                        if(DEBUG==1)printf("1 str-end:0 - %d\n",mcnt);fflush(stdout);            //1st ADC START DATA
                        if(data[i]>=-0.1 && data[i]<=0.1){result = result | 0x0;                 //1st ADC START DATA
                        }else{result = result | dut;printf("**FAIL\n");}                                            //1st ADC START DATA
                   }                                                                             //1st ADC START DATA
                   if(i>=mcnt && i<mcnt*2){                                                      //2nd ADC START DATA
                        if(DEBUG==1)printf("2 str-end:%d - %d\n",mcnt,mcnt*2);fflush(stdout);    //2nd ADC START DATA
                        if(data[i]>= 0.4 && data[i]<=0.6){result = result | 0x0;                 //2nd ADC START DATA
                        }else{result = result | dut;printf("**FAIL\n");}                                            //2nd ADC START DATA
                   }                                                                             //2nd ADC START DATA
                   if(i>=mcnt*2 && i<mcnt*3){                                                    //3rd ADC START DATA
                        if(DEBUG==1)printf("3 str-end:%d - %d\n",mcnt*2,mcnt*3);fflush(stdout);  //3rd ADC START DATA
                        if(data[i]>= 0.9 && data[i]<=1.1){result = result | 0x0;                 //3rd ADC START DATA
                        }else{result = result | dut;printf("**FAIL\n");}                                            //3rd ADC START DATA
                   }                                                                             //3rd ADC START DATA
                   if(i>=mcnt*3 && i<mcnt*4){                                                    //4th ADC START DATA
                        if(DEBUG==1)printf("4 str-end:%d - %d\n",mcnt*3,mcnt*4);fflush(stdout);  //4th ADC START DATA
                        if(data[i]>=-0.1 && data[i]<=0.1){result = result | 0x0;                 //4th ADC START DATA
                        }else{result = result | dut;printf("**FAIL\n");}                                            //4th ADC START DATA
                   }                                                                             //4th ADC START DATA
              }
         }
    }

    display(result);
} 
void adc_start_time_dc(TEST_testitem *testarg){
    int result=0;
    int i,j,gnum,gmax,ovf;
    int mcnt =  200;                         //MeasCnt
    double ref_val=0.0;
    double adct   =0.0;
    CheckButton ovc=0;
    DSlider *data;
    DutCursor dutc;
    UT_DUT dut;


    DctHandle Dct_H;
    PinHandle Pin_H;
    PowerCtrlHandle PowerCtrl_H;

    SamplingRateHandle srh = UTL_GetSamplingRateHandle();
    UTL_SetSamplingRate(srh,  5e-6);                    //SamplingRate:10us
//  UTL_SetSamplingRate(srh,  1e-3);                    //SamplingRate:10us
    UTL_SendSamplingRate(srh);
    UTL_DeleteHandle(srh);

    timing_setting();
    level_setting( 1  , 1.0 , 0.0);              // VIH=1.0V,VIL=0V
    pin_condition("NRZB");                       // Set FIXH waveform
    dc_setting("DR", mcnt);                      //(ch_number,MeasCnt)
    adc_setting("DC");


    UTL_ResetAdcHistoryCount   ( UT_ADC_TYPE_DC );

    Pin_H = UTL_GetPinHandle();
    FctHandle Fct_H = UTL_GetFctHandle();
    UTL_SetFctMpatName      (Fct_H, "pat_adc.mpa");
    UTL_SetFctFailInhibit   (Fct_H, UT_ON);
    UTL_SetFctStartPc       (Fct_H, 0x300);
    UTL_SetFctNoWait        (Fct_H, UT_OFF);
    UTL_MeasFct             (Fct_H);
    UTL_DeleteHandle        (Fct_H);

    UTL_WaitAdc(UT_ADC_TYPE_DC);
    int hcnt = UTL_ReadAdcHistoryCount(UT_ADC_TYPE_DC, &ovc);
    if(ovc==UT_ON){printf("\n****Error.Please Check Program.\n");fflush(stdout);UTL_Stop();}
    printf("count value: %d\n",hcnt);fflush(stdout);

    data  = (DSlider *)malloc(sizeof(DSlider)*hcnt);

    DctReadPinHandle dcrph = UTL_GetDctReadPinHandle();
    dutc = UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc)) != UT_NOMORE){
         UTL_SetDctReadPinDut(dcrph,dut);
         UTL_SetDctReadPinType(dcrph, UT_PINTYPE_PIN);
         UTL_SetDctReadPinNumber(dcrph,  1  );
         UTL_ReadDctPinAllHistoryData(dcrph, data, hcnt);
         for(i=0;i<hcnt;i++){
              if(DEBUG==1)printf(" data:%lf\n", data[i]);fflush(stdout);
                   if(data[i] >=0.5 ){
                        adct=500e-6-i*5e-6;
                        printf("time : %lf\n",adct);fflush(stdout);
                        break;
                   }
         }
    }
    free(data);

//       dutc = UTL_GetDutCursor(UT_CDUT);
//       while((dut=UTL_NextDut(dutc)) != UT_NOMORE){
//            for(i=0;i<mcnt;i++){
//                 if(DEBUG==1)printf("data[%d]:%lf\n",i,data[i]);fflush(stdout);
//                 if(data[i+mcnt*(dut-1)] >=0.5 ){
//                      adct=500e-6-i*5e-6;
//                      break;
//                 }
//            }
//       }
//       if(DEBUG==1)printf("data[%d]:%lf\n",i,data[i]);fflush(stdout);
//       if(adct >=ref_val*0.9 && adct <= ref_val*1.1){
//            result = result | 0x0;
//       }else{result = result | dut;}

    result=result | funcresult(0);

    display(result);
} 


void adc_start_time_pps(TEST_testitem *testarg){
    int result=0;
    int i,j,gnum,gmax,ovf;
    int mcnt = 1023;                         //MeasCnt
    double ref_val=0.0;                      //riron-ti 
    double adct=0.0;
    CheckButton ovc=0;
    DSlider *data;
    DutCursor dutc;
    UT_DUT dut;


    DctHandle Dct_H;
    PinHandle Pin_H;

    timeset(0e-3);
    SamplingRateHandle srh = UTL_GetSamplingRateHandle();
    UTL_SetSamplingRate(srh,  4e-6);                    //SamplingRate:10us
//  UTL_SetSamplingRate(srh,  1e-3);                    //SamplingRate:10us
    UTL_SendSamplingRate(srh);
    UTL_DeleteHandle(srh);

    timing_setting();
    vs_setting(  1 , 1.0 , mcnt);                      //(ch_number,VSource Level,MeasCnt)
    adc_setting("VS");

    UTL_ResetAdcHistoryCount   ( UT_ADC_TYPE_VS );

    Pin_H = UTL_GetPinHandle();
    FctHandle Fct_H = UTL_GetFctHandle();
    UTL_SetFctMpatName      (Fct_H, "pat_adc.mpa");
    UTL_SetFctFailInhibit   (Fct_H, UT_ON);
    UTL_SetFctStartPc       (Fct_H, 0x300);
    UTL_SetFctNoWait        (Fct_H, UT_OFF);
    UTL_MeasFct             (Fct_H);
    UTL_DeleteHandle        (Fct_H);
  

    UTL_WaitAdc(UT_ADC_TYPE_VS);
    int hcnt = UTL_ReadAdcHistoryCount(UT_ADC_TYPE_VS, &ovc);
    if(ovc==UT_ON){printf("\n****Error.Please Check Program.\n");fflush(stdout);UTL_Stop();}
    printf("count value: %d\n",hcnt);fflush(stdout);

    data  = (DSlider *)malloc(sizeof(DSlider)*hcnt);


    DctReadPinHandle dcrph = UTL_GetDctReadPinHandle();
    dutc = UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc)) != UT_NOMORE){
         UTL_SetDctReadPinDut(dcrph,dut);
         UTL_SetDctReadPinType(dcrph, UT_PINTYPE_VS );
         UTL_SetDctReadPinNumber(dcrph,  1  );
         UTL_ReadDctPinAllHistoryData(dcrph, data, hcnt);
         for(i=0;i<hcnt;i++){
              if(DEBUG==1)printf(" data:%lf\n", data[i]*1000);fflush(stdout);
         }
    }
    free(data);

//    adct=rdata*10e-3;
//
//    if(DEBUG==1)printf("rdata:%lf\n",rdata);fflush(stdout);
//    if(DEBUG==1)printf("adct:%lf\n",adct);fflush(stdout);
//    if(adct >=ref_val*0.9 && adct <= ref_val*1.1){
//         result = result | 0x0;
//    }else{result = result | dut;}

    display(result);
} 


int funcresult(int pfresult)
{    int result=0;
    DutCursor dutcur;
    if(pfresult==0) dutcur=UTL_GetDutCursor(UT_FDUT);
    if(pfresult==1) dutcur=UTL_GetDutCursor(UT_PDUT);

    UT_DUT dut=0;
    while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
        result=result | 0x1<<dut-1;
    }
    
    return result;
}

void display(int result)
{
     printf("\n%-32s",UTL_ReadTestName());
     if(result==0){
        testresult_pass4alldut(UTL_ReadTestName());
	printf(" ***PASS\n"); 
     }else{
         testresult_fail4alldut(UTL_ReadTestName());
	 if(result==3){ printf("LOG CHECK!!");
         }else if(result!=0) printf(" FAIL** dut:%x\n",result); 
     }   
     fflush(stdout);
}

