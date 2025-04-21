#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <memory.h>
#include <malloc.h>
#include <time.h>
#include "UTSOCK.h"
#include "test.h"
#include "test_struct.h"
#include "hvlvdr.h"


#define DEBUG 0

static void display_hedder(TEST_testitem *testarg);
static void pin_list();
static void timing_setting();
static void level_setting(TEST_testitem *testarg);
static void pin_condition();
static void dc_setting(TEST_testitem *testarg);      
static void adc_setting(TEST_testitem *testarg);      
static void meas_dct();       
static void meas_adct();       
static int dct_result(TEST_testitem *testarg);
static void display(int result);



static void display_hedder(TEST_testitem *testarg)
{
	printf("\n--TEST CONDITION--\n");
	printf("METHOD : %s\n",HVARG.test);
	printf("VIH    : %.2fV\n",HVARG.vih);
	if	(HVARG.mmode == UT_HVLVDR_VM){
		printf("MODE   : VM\n");
		if(HVARG.u_onoff == UT_ON){
			printf("ULIMIT : %.2fV\n",HVARG.u_lmt);
		}else{
			printf("ULIMIT : NONE\n");
		}

		if(HVARG.l_onoff == UT_ON){
			printf("LLIMIT : %.2fV\n",HVARG.l_lmt);
		}else{
			printf("LLIMIT : NONE\n");
		}
	}else if(HVARG.mmode == UT_HVLVDR_IM){
		printf("MODE   : IM\n");
		if(HVARG.u_onoff == UT_ON){
			printf("ULIMIT : %.2fUA\n",HVARG.u_lmt*1e6);
		}else{
			printf("ULIMIT : NONE\n");
		}

		if(HVARG.l_onoff == UT_ON){
			printf("LLIMIT : %.2fUA\n",HVARG.l_lmt*1e6);
		}else{
			printf("LLIMIT : NONE\n");
		}
	}
	printf("------------------\n\n");
}


static void pin_list()
{
	int i;

	UTL_CreatePinList	("HVLVDRPIN"); 
	UTL_SetPinType		("HVLVDRPIN", UT_PINTYPE_PIN);
	UTL_AddPinNumber	("HVLVDRPIN", 25);
}

static void timing_setting(){

    double RATE=200e-9;

    TgHandle Tg_H = UTL_GetTgHandle();
    UTL_AddTgRate    (Tg_H, 1,    RATE);
    UTL_AddTgBclk    (Tg_H, 1, 1, 0.0e-9);
    UTL_AddTgStrb    (Tg_H, 1, 1, 0.0e-9);
    UTL_SendTg       (Tg_H);
    UTL_DeleteHandle (Tg_H);
}


static void level_setting(TEST_testitem *testarg){
    ViHandle Vi_H = UTL_GetViHandle();

    UTL_SetViHigh    (Vi_H, HVARG.vih	);
    UTL_SetViLow     (Vi_H, 0.0		);
    UTL_SetViHvLvDr  (Vi_H,UT_ON	); //Asakaze5 NewMCI
    UTL_SendVi       (Vi_H, 1		);
    UTL_DeleteHandle (Vi_H		);

}

static void pin_condition(){

	PinHandle Pin_h = UTL_GetPinHandle();
	UTL_InitializePinHandle (Pin_h);

	UTL_SetPinHvDr		(Pin_h, UT_OFF		);	
	UTL_SetPinHvLvDr	(Pin_h, UT_ON		);    //Asakaze5 NewMCI	
	UTL_SetPinViNumber      (Pin_h, 1		); 
	UTL_SetPinDrWaveform    (Pin_h, UT_WAV_FIXH	);    // Waveform DNRZ
//	UTL_SetPinDrClock       (Pin_h, UT_PIN_BCLK , 1 );    // (Handle, Kind of Clk, Phase Number)
//	UTL_SetPinDreNumber     (Pin_h, 1		);    // (Handle, DRECLOCK Number)
//	UTL_SetPinDreWaveform   (Pin_h, UT_DREWAV_NRZ	);    // (Handle, DRE Wave Form)
//	UTL_SetPinDreClock      (Pin_h, 1		);    // (Handle, DREn)
//	UTL_AddPinPdsA          (Pin_h, UT_SIG_C(1), 1 );     // (Handle, Data , CYP Number)

        UTL_SetPinDcConnect     (Pin_h, UT_OFF		);    // Normal DC unit cannot be connected HVLVDR pin
        UTL_SendPin             (Pin_h, "HVLVDRPIN"	);
        UTL_DeleteHandle        (Pin_h			); 
}


static void dc_setting(TEST_testitem *testarg)
{
        DcHvlvdrHandle dc_h = UTL_GetDcHvlvdrHandle();
	UTL_SetDcHvlvdrMode		(dc_h,	HVARG.mmode			); 
	if	(HVARG.mmode == UT_HVLVDR_VM){
		UTL_SetDcHvlvdrMrange	(dc_h,	30,		-10		);
	}else if(HVARG.mmode == UT_HVLVDR_IM){
		UTL_SetDcHvlvdrMrange	(dc_h,	20e-3,		-20e-3		);
	}
	UTL_SetDcHvlvdrLimitHigh	(dc_h,	HVARG.u_lmt,	HVARG.u_onoff	);
	UTL_SetDcHvlvdrLimitLow		(dc_h,	HVARG.l_lmt,	HVARG.l_onoff	);
	UTL_SetDcHvlvdrMeasCnt		(dc_h,	10				);//1 - 4095
	UTL_SendDcHvlvdr		(dc_h					);
        UTL_DeleteHandle		(dc_h					);
}


static void adc_setting(TEST_testitem *testarg)
{
	AdcHvlvdrHandle adc_h = UTL_GetAdcHvlvdrHandle(); 
	UTL_SetAdcHvlvdrPgEnable 	(adc_h,	UT_ON		);
	UTL_SetAdcHvlvdrStartCycle	(adc_h,	UT_ADC_C(10)	);
	UTL_SetAdcHvlvdrPinList 	(adc_h,	"HVLVDRPIN"	);
	UTL_SendAdcHvlvdr 		(adc_h			);
        UTL_DeleteHandle		(adc_h			);
}

static void meas_dct()
{
        DctHandle dct_h = UTL_GetDctHvlvdrHandle();
	UTL_SetDctHvlvdrPinList		(dct_h,	"HVLVDRPIN"	);
	UTL_MeasDctHvlvdr		(dct_h			);
        UTL_DeleteHandle		(dct_h			);
}

static void meas_adct()
{
	FctHandle adct_h = UTL_GetFctHandle();
	UTL_SetFctMpatName	(adct_h, "pat_hvlvdr.mpa"	);
	UTL_SetFctFailInhibit	(adct_h, UT_ON			);
	UTL_SetFctStartPc  	(adct_h, 0x0			);
	UTL_MeasFct        	(adct_h				);
	UTL_DeleteHandle   	(adct_h				);
}

static void meas_mpat(TEST_testitem *testarg){
    FctHandle Fct_H = UTL_GetFctHandle();
    UTL_SetFctMpatName (Fct_H, SSARG.mpat);
    UTL_SetFctFailInhibit (Fct_H, UT_ON);
    UTL_SetFctStartPc  (Fct_H, SSARG.pc);
    UTL_MeasFct        (Fct_H);
    UTL_DeleteHandle   (Fct_H);
}

static int dct_result(TEST_testitem *testarg)
{
	int i,j,k;
	int result=0;
	int flg=0;

	UT_DUT dut=0;
	UT_PIN pin=0;

	int DUTNUM=16;
	int ofl_dut[DUTNUM];

	double data[DUTNUM];
	CheckButton info[6][DUTNUM];

	for(i=0; i<DUTNUM; i++){
	   for(j=0; j<6; j++){	//DCT info mode=6
		ofl_dut[i]=0;
		data[i]=0;
		info[6][i]=0;
	   }
	}

	DctHvlvdrReadPinHandle dctr_h = UTL_GetDctHvlvdrReadPinHandle();
	DutCursor dutcur=UTL_GetDutCursor(UT_MDUT);
	while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
		UTL_SetDctHvlvdrReadPinDut 			(dctr_h, dut);
		PinCursor pincur=UTL_GetPinCursor("HVLVDRPIN");
		while((pin=UTL_NextPin(pincur)) != UT_NOMORE){
			UTL_SetDctHvlvdrReadPinNumber 		(dctr_h, pin); 

			data[dut-1]=UTL_ReadDctHvlvdrPinData  	(dctr_h);
			
			UTL_SetDctHvlvdrReadPinMode 	(dctr_h, UT_RES_FAILED		); info[0][dut-1]  = UTL_ReadDctHvlvdrPin(dctr_h );
			UTL_SetDctHvlvdrReadPinMode 	(dctr_h, UT_RES_HIGH_FAILED	); info[1][dut-1] = UTL_ReadDctHvlvdrPin(dctr_h );
			UTL_SetDctHvlvdrReadPinMode 	(dctr_h, UT_RES_LOW_FAILED	); info[2][dut-1] = UTL_ReadDctHvlvdrPin(dctr_h );
			UTL_SetDctHvlvdrReadPinMode 	(dctr_h, UT_RES_OVERFLOW	); info[3][dut-1]   = UTL_ReadDctHvlvdrPin(dctr_h );
			UTL_SetDctHvlvdrReadPinMode 	(dctr_h, UT_RES_PLUS_OVERFLOW	); info[4][dut-1]  = UTL_ReadDctHvlvdrPin(dctr_h );
			UTL_SetDctHvlvdrReadPinMode 	(dctr_h, UT_RES_MINUS_OVERFLOW	); info[5][dut-1]  = UTL_ReadDctHvlvdrPin(dctr_h );
		}
        	UTL_DeleteCursor (pincur);
	}
        UTL_DeleteCursor (dutcur);	
    	UTL_DeleteHandle (dctr_h);

//DISPLAY DC DATA
	printf("===============================\n");
	printf("       DCT DATA CHECK\n");
	printf("===============================\n");

	double vih_acc;
	if(HVARG.vih>=0){	vih_acc=((HVARG.vih*1.02+0.05) *1.002+0.008) - HVARG.vih;}
	else{			vih_acc=(((- HVARG.vih)*1.02+0.05) *1.002+0.008) + HVARG.vih;}

	//PASS CONDITION for DCT TEST
	if(HVARG.mmode==UT_HVLVDR_IM){
		printf("\nPASS COND: -40UA<DATA<40UA\n");fflush(stdout);
	}else if(HVARG.vih==30){	
		printf("\nPASS COND: DATA>%fV  or (+)OVER\n",HVARG.vih-vih_acc);fflush(stdout);
	}else if(HVARG.vih==-10){	
		printf("\nPASS COND: DATA<%fV  or (-)OVER\n",HVARG.vih+vih_acc);fflush(stdout);
	}else{	
		printf("\nPASS COND: %fV<DATA<%fV\n",HVARG.vih-vih_acc,HVARG.vih+vih_acc);fflush(stdout);
	}


	dutcur=UTL_GetDutCursor(UT_MDUT);
	while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){

		flg=0;


		//PASS FAIL JUDGE
		//VM
		if(HVARG.mmode==UT_HVLVDR_VM){
			//DC DATA
			printf("DUT%02d: %8.4fV | ",dut,data[dut-1]);
			
			//[PLUS OVERFLOW]
			if	(info[4][dut-1]==1){
				printf("(+)OVERFLOW | ");
				ofl_dut[dut-1]=1;
				if(HVARG.vih==30){}
				else {flg=1;}

			//[MINUS OVERFLOW]
			}else if(info[5][dut-1]==1){
				printf("(-)OVERFLOW | ");
				ofl_dut[dut-1]=1;
				if(HVARG.vih==-10){}
				else  {flg=1;}
			}
			//[NOT OVERFLOW]
			else{
				printf("    ----    | ");
				if(data[dut-1]<=HVARG.vih + vih_acc &&  data[dut-1]>=HVARG.vih - vih_acc){}
				//if(data[dut-1]<=HVARG.u_lmt && data[dut-1]>=HVARG.l_lmt){}
				else{flg=1;}
			}
		//IM
		}else if(HVARG.mmode==UT_HVLVDR_IM){
			//DC DATA
			printf("DUT%02d: %8.4fUA | ",dut,data[dut-1]*1e6);

			printf("    ----    | ");
			if(data[dut-1]<=10e-6 + vih_acc &&  data[dut-1]>=-10e-6){}
			//if(data[dut-1]<=HVARG.u_lmt && data[dut-1]>=HVARG.l_lmt){}
			else{flg=1;}
		}

		//PASS/FAIL Judge
		if(flg==0){
			printf("PASS**\n");fflush(stdout);
		}else{
			printf("       ***FAIL!!\n");fflush(stdout);
			result=result | 0x1<<dut-1;	
		}

	}
        UTL_DeleteCursor (dutcur);
	
//DISPLAY DC INFO
	printf("\n\n\n");
	printf("===============================\n");
	printf("       DCT INFO CHECK\n");
	printf("===============================\n");

	char item[6][64]={	"UT_RES_FAILED        ",
			 	"UT_RES_HIGH_FAILED   ",
				"UT_RES_LOW_FAILED    ",
				"UT_RES_OVERFLOW      ", 
				"UT_RES_PLUS_OVERFLOW ",
				"UT_RES_MINUS_OVERFLOW",};
	int exp[6]={HVARG.exp_f,HVARG.exp_hf,HVARG.exp_lf,0,0,0};

	if(HVARG.vih==30) {exp[3]=2;exp[4]=2;}  //2:DontCare
	if(HVARG.vih==-10){exp[3]=2;exp[5]=2;}  //2:DontCare

	//PASS CONDITION for DCT INFO
	if(HVARG.mmode==UT_HVLVDR_IM){
		if(HVARG.u_lmt<0){
			printf("\nPASS COND: H-FAIL=1\n");fflush(stdout);
		}else if(HVARG.l_lmt>0){
			printf("\nPASS COND: L-FAIL=1\n");fflush(stdout);
		}else{
			printf("\nPASS COND: ALL ITEMs=0\n");fflush(stdout);
		}
	}else if(HVARG.mmode==UT_HVLVDR_VM){
		if(HVARG.vih==30){
			if(HVARG.u_lmt<HVARG.vih){
				printf("\nPASS COND: H-FAIL=1 OR (+)OVER=1\n");fflush(stdout);
			}else{
				printf("\nPASS COND: ALL ITEMs=0 OR (+)OVER=1\n");fflush(stdout);
			}
		}else if(HVARG.vih==-10){
			if(HVARG.l_lmt>HVARG.vih){
				printf("\nPASS COND: L-FAIL=1 OR (-)OVER=1=0\n");fflush(stdout);
			}else{
				printf("\nPASS COND: ALL ITEMs=0 OR (-)OVER=1\n");fflush(stdout);
			}
		}else{
			if(HVARG.u_lmt<HVARG.vih){
				printf("\nPASS COND: H-FAIL=1\n");fflush(stdout);
			}else if(HVARG.l_lmt>HVARG.vih){
				printf("\nPASS COND: L-FAIL=1\n");fflush(stdout);
			}else{
				printf("\nPASS COND: ALL ITEMs=0\n");fflush(stdout);
			}
		}


	}

	printf("                     |DUT\n");
	printf("                     |");for(i=1;i<=DUTNUM;i++){printf("%d",i/10);}printf(" E \n");
	printf("INFO ITEM            |");for(i=1;i<=DUTNUM;i++){printf("%d",i%10);}printf(" X \n");
	printf("----------------------");for(i=1;i<=DUTNUM;i++){printf("-");}      printf("---\n");
	fflush(stdout);

	for(i=0;i<6;i++){
		printf("%s|",item[i]);fflush(stdout);

		flg=0;
		dutcur=UTL_GetDutCursor(UT_MDUT);
		while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
			if(i<=2 && ofl_dut[dut-1]==1){
				printf("-");
			}else{
				printf("%d",info[i][dut-1]);
				if(info[i][dut-1]!=exp[i]){flg=1;}	// PASS/FAIL judge
			}

		}
		UTL_DeleteCursor (dutcur);

		if	(exp[i]==2){
			printf(" - PASS**\n");
		}else if(flg==0){
			printf(" %d PASS**\n",exp[i]);
		}else{
			printf(" %d       ***FAIL!\n",exp[i]);
			result=result | 0x1<<dut-1;
		}
	}	
	return result;
}

static void display(int result)
{
     printf("\n%-32s",UTL_ReadTestName());
     if(result==0){
         testresult_pass4alldut(UTL_ReadTestName());
         printf(" ***PASS");
     }else{
         testresult_fail4alldut(UTL_ReadTestName());
         printf(" FAIL**"); 
     }   
     fflush(stdout);
}

void hvlvdr_check(TEST_testitem *testarg)
{
    int result=0;

    display_hedder(testarg);

    pin_list();                    
    timing_setting();
    level_setting(testarg);        
    pin_condition();        

    dc_setting(testarg);
    if	(strcmp(HVARG.test, "ADC") == 0){	adc_setting(testarg);}

    UTL_SetWet();
    UTL_OnPowerSeq();
   
    if		(strcmp(HVARG.test,  "DC") == 0){	meas_dct(); }           
    else if	(strcmp(HVARG.test, "ADC") == 0){	meas_adct();}

    result=dct_result(testarg);
    display(result);
}


