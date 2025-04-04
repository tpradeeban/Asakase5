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
#include "dcm.h"

#define  V  *1.0
#define mA  *1.0e-3
#define  s  *1.0
#define ms  *1.0e-3
#define us  *1.0e-6
#define ns  *1.0e-9
#define ps  *1.0e-12


#define DEBUG 0

double RATE=200e-9;

static void pin_list();
static void set_interleave_mode(int ilmode);
static void level_setting();
static void timing_setting();
static void timing_setting_match();
static void pin_setting();         //R030402 
static void pin_setting_match();         //R030402 
static void display(int result);



static void pin_list()
{
	int i;

	UTL_CreatePinList("IOPIN"); 
	UTL_SetPinType("IOPIN", UT_PINTYPE_PIN);
	for(i=1 ; i<=18; i++){
		UTL_AddPinNumber("IOPIN", i);
	}
}

static void set_interleave_mode(int ilmode)
{
    IlModeHandle IlMode_H = UTL_GetIlModeHandle();
    UTL_SetIlMode    (IlMode_H, ilmode);
    UTL_SendIlMode   (IlMode_H);
    UTL_DeleteHandle (IlMode_H);
}


static void pin_setting_match(){

    PinHandle Pin_H = UTL_GetPinHandle();
    UTL_SetPinViNumber      (Pin_H, 1);
    UTL_SetPinDrWaveform    (Pin_H, UT_WAV_FIXH);
    UTL_SetPinTerm          (Pin_H, UT_ON); //20211214
    UTL_SetPinIoCtrl        (Pin_H, UT_ON);
    UTL_SetPinDreNumber     (Pin_H, 1);
    UTL_SetPinDreWaveform   (Pin_H, UT_DREWAV_NRZ);
    UTL_SetPinDreClock      (Pin_H, 1);
    UTL_SetPinVoNumber      (Pin_H, 1);
    UTL_SetPinMatchMode     (Pin_H, UT_SIG_MATCH);
    UTL_AddPinStrbCpeNumber (Pin_H, 1, 1);
    UTL_AddPinExpStrbNumber (Pin_H, 1, UT_PIN_EXP_A);


    UTL_AddPinPdsA          (Pin_H, UT_SIG_X(3), 1);
    UTL_SendPin             (Pin_H, "IOPIN");
    UTL_DeleteHandle        (Pin_H);

}

static void pin_setting(){

    int i;

    PinHandle Pin_H = UTL_GetPinHandle();
    UTL_SetPinViNumber      (Pin_H, 1);
    UTL_SetPinDrWaveform    (Pin_H, UT_WAV_NRZB);
    UTL_SetPinDrClock       (Pin_H, UT_PIN_BCLK, 1);
    UTL_SetPinDreNumber     (Pin_H, 1);
    UTL_SetPinDreWaveform   (Pin_H, UT_DREWAV_NRZ);
    UTL_SetPinDreClock      (Pin_H, 1);
    UTL_SetPinIoCtrl        (Pin_H, UT_ON);
    UTL_SetPinVoNumber      (Pin_H, 1);
    UTL_AddPinStrbCpeNumber (Pin_H, 1, 1);
    UTL_AddPinExpStrbNumber (Pin_H, 1, UT_PIN_EXP_B);
    UTL_SetPinTerm          (Pin_H, UT_ON);
    UTL_SetPinVtNumber      (Pin_H, 1);

    for(i=0; i<18; i++){
	UTL_AddPinPdsA(Pin_H , UT_SIG_X(i)	, 1);
	UTL_AddPinPdsB(Pin_H , UT_SIG_D(i)	, 1);
    }

    UTL_SendPin             (Pin_H, "IOPIN");
    UTL_DeleteHandle	    (Pin_H);
}


static void level_setting(){
    ViHandle Vi_H = UTL_GetViHandle();
    UTL_SetViHigh    (Vi_H, 2.0);
    UTL_SetViLow     (Vi_H, 0.0);
    UTL_SendVi       (Vi_H, 1);
    UTL_DeleteHandle (Vi_H);

    VoHandle Vo_H = UTL_GetVoHandle();
    UTL_SetVoHigh    (Vo_H, 1.0);
    UTL_SetVoLow     (Vo_H, 1.0);
    UTL_SendVo       (Vo_H, 1);
    UTL_DeleteHandle (Vo_H);

    VtHandle Vt_H = UTL_GetVtHandle();
    UTL_SetVt        (Vt_H, 1.0);
    UTL_SendVt       (Vt_H, 1);
    UTL_DeleteHandle (Vt_H);

    return;
}

static void timing_setting(){
    TgHandle Tg_H = UTL_GetTgHandle();
    UTL_AddTgRate    (Tg_H, 1,    RATE);
    UTL_AddTgBclk    (Tg_H, 1, 1, 0.0e-9);
    UTL_AddTgDreL    (Tg_H, 1, 1, 0.0e-9);
    UTL_AddTgDreT    (Tg_H, 1, 1, 0.0e-9);
    UTL_AddTgStrb    (Tg_H, 1, 1, RATE*0.5);
    UTL_SendTg       (Tg_H);
    UTL_DeleteHandle (Tg_H);
}

static void timing_setting_match(){
    TgHandle Tg_H = UTL_GetTgHandle();
    UTL_AddTgRate    (Tg_H, 1,    2e-6);
    UTL_AddTgDreL    (Tg_H, 1, 1, 0.0e-9);
    UTL_AddTgDreT    (Tg_H, 1, 1, 0.0e-9);
    UTL_AddTgStrb    (Tg_H, 1, 1, 0.0);
    UTL_SendTg       (Tg_H);
    UTL_DeleteHandle (Tg_H);
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

void dcm_seqrm_idx_check()
{
	int i,j,k;
	int result=0;

	int REG1_EXP[16]={0xE,	0xE,	0xE,	0xE,	0xE,	0xE,	0xE,	0xE,	0xE,	0xE,	0xE,	0xE,	0xE,	0xE,	0xE,	0xE};	
	int REG2_EXP[16]={0x10,	0x20,	0x30,	0x40,	0x50,	0x60,	0x70,	0x80,	0x90,	0xA0,	0xB0,	0xC0,	0xD0,	0xE0,	0xF0,	0x100};	

	int REG1_DATA[16];	//[XB,TB,...,YR3]
	int REG2_DATA[16];	//[XB,TB,...,YR3]
	for(i=0;i<16;i++){
		REG1_DATA[i]=0;
		REG2_DATA[i]=0;
	}

	set_interleave_mode(1);
	timing_setting();
	
	//DCM setting
        int dcmsize=0x80;
        USlider  size = dcmsize * sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	for(i=0;i<16;i++){
		DCM_DATA[i]=0xF+0x10*i;
		if(DEBUG==1){printf("DCMAP[0x%X]=0x%02X\n",i,DCM_DATA[i]);fflush(stdout);}
	}

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_SEQRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize);
        UTL_DeleteHandle                (dcm_h);

	//MEAS MPAT
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x000);
	UTL_MeasFct(Fct_H); 
	
	//Read Register
	REG1_DATA[0x0]=UTL_ReadUSRegister	(UT_REG_XB,	1);
	REG1_DATA[0x1]=UTL_ReadUSRegister	(UT_REG_YB,	1);
	REG1_DATA[0x2]=UTL_ReadUSRegister	(UT_REG_Z,	1);
	REG1_DATA[0x3]=UTL_ReadUSRegister	(UT_REG_XC,	1);
	REG1_DATA[0x4]=UTL_ReadUSRegister	(UT_REG_YC,	1);
	REG1_DATA[0x5]=UTL_ReadUSRegister	(UT_REG_XS,	1);
	REG1_DATA[0x6]=UTL_ReadUSRegister	(UT_REG_YS,	1);
	REG1_DATA[0x7]=UTL_ReadUSRegister	(UT_REG_XK,	1);
	REG1_DATA[0x8]=UTL_ReadUSRegister	(UT_REG_YK,	1);
	REG1_DATA[0x9]=UTL_ReadUSRegister	(UT_REG_XR,	1);
	REG1_DATA[0xA]=UTL_ReadUSRegister	(UT_REG_XR2,	1);
	REG1_DATA[0xB]=UTL_ReadUSRegister	(UT_REG_XR3,	1);
	REG1_DATA[0xC]=UTL_ReadUSRegister	(UT_REG_XR4,	1);
	REG1_DATA[0xD]=UTL_ReadUSRegister	(UT_REG_YR,	1);
	REG1_DATA[0xE]=UTL_ReadUSRegister	(UT_REG_YR2,	1);
	REG1_DATA[0xF]=UTL_ReadUSRegister	(UT_REG_YR3,	1);

	REG2_DATA[0x0]=UTL_ReadUSRegister	(UT_REG_XB_2,	1);
	REG2_DATA[0x1]=UTL_ReadUSRegister	(UT_REG_YB_2,	1);
	REG2_DATA[0x2]=UTL_ReadUSRegister	(UT_REG_Z_2,	1);
	REG2_DATA[0x3]=UTL_ReadUSRegister	(UT_REG_XC_2,	1);
	REG2_DATA[0x4]=UTL_ReadUSRegister	(UT_REG_YC_2,	1);
	REG2_DATA[0x5]=UTL_ReadUSRegister	(UT_REG_XS_2,	1);
	REG2_DATA[0x6]=UTL_ReadUSRegister	(UT_REG_YS_2,	1);
	REG2_DATA[0x7]=UTL_ReadUSRegister	(UT_REG_XK_2,	1);
	REG2_DATA[0x8]=UTL_ReadUSRegister	(UT_REG_YK_2,	1);
	REG2_DATA[0x9]=UTL_ReadUSRegister	(UT_REG_XR_2,	1);
	REG2_DATA[0xA]=UTL_ReadUSRegister	(UT_REG_XR2_2,	1);
	REG2_DATA[0xB]=UTL_ReadUSRegister	(UT_REG_XR3_2,	1);
	REG2_DATA[0xC]=UTL_ReadUSRegister	(UT_REG_XR4_2,	1);
	REG2_DATA[0xD]=UTL_ReadUSRegister	(UT_REG_YR_2,	1);
	REG2_DATA[0xE]=UTL_ReadUSRegister	(UT_REG_YR2_2,	1);
	REG2_DATA[0xF]=UTL_ReadUSRegister	(UT_REG_YR3_2,	1);

	//Display Result
	printf("\n-------------------------------------------\n");
	printf("     | #LOAD BF     | #LOAD AF     | \n");
	printf(" REG | EXP    MEAS  | EXP    MEAS  |RESULT\n");
	printf("-------------------------------------------\n");
	for(i=0;i<16;i++){
	printf("IDX%2d| 0x%03X  0x%03X | 0x%03X  0x%03X |",i+1,REG1_EXP[i],REG1_DATA[i],REG2_EXP[i],REG2_DATA[i]);
	if(REG1_DATA[i]==REG1_EXP[i] && REG2_DATA[i]==REG2_EXP[i]){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
	}
	printf("-------------------------------------------\n");
	
	display(result);
}


void dcm_seqrm_bar_check()
{
	int i,j,k;
	int result=0;
	int xb_data;

	for(i=0;i<4;i++){
		xb_data=0;
	}

	pin_list();
	level_setting();
	timing_setting_match();
	pin_setting_match(); 
	
	//DCM setting
        int dcmsize=0x80;
        USlider  size = dcmsize * sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	DCM_DATA[0]=0x068;
        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_SEQRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize);
        UTL_DeleteHandle                (dcm_h);

	//MEAS MPAT
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x060);
	UTL_MeasFct(Fct_H); 
	UTL_DeleteHandle        (Fct_H);
	
	//Read Register
	xb_data=UTL_ReadUSRegister	(UT_REG_XB,	1);

	//Display Result
	printf("\n-----------------------------\n");
	printf(" REG | EXP   MEAS  |RESULT\n");
	printf("-----------------------------\n");
	printf("  XB | 0xAA  0x%02X  |",xb_data);
	if(xb_data==0xAA){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
	printf("-----------------------------\n");
	
	display(result);

}


void dcm_seqrm_isp_check()
{
	int i,j,k;
	int result=0;

	int XB_DATA[4];	//[ISP1-4]
	int XC_DATA[4];	//[ISP1-4]
	for(i=0;i<4;i++){
		XB_DATA[i]=0;
		XC_DATA[i]=0;
	}

	timing_setting();
	
	//DCM setting
        int dcmsize=0x80;
        USlider  size = dcmsize * sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	for(i=0;i<4;i++){
//		DCM_DATA[i]=0x8A+0x20*i;
		DCM_DATA[i]=0x90+(i*0x2);
		if(DEBUG==1){printf("DCMAP[0x%X]=0x%02X\n",i,DCM_DATA[i]);fflush(stdout);}
	}

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_SEQRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize);
        UTL_DeleteHandle                (dcm_h);


	//MEAS MPAT
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x080);
	UTL_MeasFct(Fct_H); 
	UTL_DeleteHandle        (Fct_H);
	
	//Read Register
	int xb_data=UTL_ReadUSRegister	(UT_REG_XB,	1);
	int yb_data=UTL_ReadUSRegister	(UT_REG_YB,	1);
	int xc_data=UTL_ReadUSRegister	(UT_REG_XC,	1);
	int yc_data=UTL_ReadUSRegister	(UT_REG_YC,	1);
	int xk_data=UTL_ReadUSRegister	(UT_REG_XK,	1);
	int yk_data=UTL_ReadUSRegister	(UT_REG_YK,	1);
	int xs_data=UTL_ReadUSRegister	(UT_REG_XS,	1);
	int ys_data=UTL_ReadUSRegister	(UT_REG_YS,	1);

	//Display Result
	printf("\n-------------------------------------------\n");
	printf("    |#LOAD BF (X)  |#LOAD AF (Y)  | \n");
	printf("REG | EXP   MEAS   | EXP   MEAS   |RESULT\n");
	printf("-------------------------------------------\n");
	printf("ISP1| 0xAA  0x%02X   | 0xFF  0x%02X   |",xb_data,yb_data);
	if(xb_data==0xAA && yb_data==0xFF){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
	printf("ISP2| 0xAA  0x%02X   | 0xFF  0x%02X   |",xc_data,yc_data);
	if(xc_data==0xAA && yc_data==0xFF){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
	printf("ISP3| 0xAA  0x%02X   | 0xFF  0x%02X   |",xk_data,yk_data);
	if(xk_data==0xAA && yk_data==0xFF){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
	printf("ISP4| 0xAA  0x%02X   | 0xFF  0x%02X   |",xs_data,ys_data);
	if(xs_data==0xAA && ys_data==0xFF){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
	printf("-------------------------------------------\n");
	
	display(result);
}


void dcm_seqrm_cflg_check()
{
	int i,j,k;
	int result=0;

	int XB_DATA=0;	
	int XC_DATA=0;	

	timing_setting();
	
	//DCM setting
        int dcmsize=0x80;
        USlider  size = dcmsize * sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	DCM_DATA[0]=1;
	if(DEBUG==1){printf("DCMAP[0x00]=0x%02X\n",DCM_DATA[i]);fflush(stdout);}

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_SEQRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize);
        UTL_DeleteHandle                (dcm_h);

	//MEAS MPAT
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x100);
	UTL_MeasFct(Fct_H); 
	UTL_DeleteHandle        (Fct_H);
	
	//Read Register
	XB_DATA=UTL_ReadUSRegister	(UT_REG_XB,	1);
	XC_DATA=UTL_ReadUSRegister	(UT_REG_XC,	1);

	//Display Result
	printf("\n-------------------------------------------\n");
	printf("     |#LOAD BF (XB) |#LOAD AF (XC) | \n");
	printf(" REG | EXP   MEAS   | EXP   MEAS   |RESULT\n");
	printf("-------------------------------------------\n");
	printf("CFLG | 0xAA  0x%02X   | 0xFF  0x%02X   |",XB_DATA,XC_DATA);
	if(XB_DATA==0xAA && XC_DATA==0xFF){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
	printf("-------------------------------------------\n");
	
	display(result);
}


void dcm_seqrm_ubmapld1_check()
{
	int i,j,k;
	int result=0;
	int PATSIZE=0xFF;
	UT_DUT dut;
	DutCursor dutc;

	pin_list();
	level_setting();
	timing_setting();
	pin_setting(); 

	//UBM config
	UbmConfigHandle useth = UTL_GetUbmConfigHandle();
	UTL_InitializeUbmConfigHandle  (useth);
	UTL_ClearUbmConfigFunctionSelect(useth);
	UTL_ClearUbmConfigPin(useth, UT_UBM_UNIT_PM);
	UTL_ClearUbmConfigJumpAddr(useth,UT_UBM_UNIT_PM, 0);
	UTL_AddUbmConfigFunctionSelect(useth, UT_UBM_UNIT_PM, UT_SIG_C(30));
	UTL_SetUbmConfigPin(useth, UT_UBM_UNIT_PM, "IOPIN");
	UTL_SetUbmConfigJumpAddr(useth, UT_UBM_UNIT_PM, 1, 0x0);
	UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_PM, 1, UT_SIG_C(25));
	UTL_SetUbmConfigPmMode(useth, UT_UBM_MODE_DRPAT);
	UTL_SetUbmConfigDdrMode(useth, UT_OFF);
	UTL_SetUbmConfigApAutoIncMode(useth, UT_ON);
	UTL_SendUbmConfig(useth);
	UTL_DeleteHandle(useth);

	//Write UBM
	int wdata[PATSIZE];
	int rdata[PATSIZE];
	unsigned int ubmsize=sizeof(wdata);
	UbmAccessHandle uacsh = UTL_GetUbmAccessHandle();
	UTL_ClearUbmAccessPin(uacsh);
	UTL_PresetUbm(uacsh,0);
	
	for (j=0; j<PATSIZE; j++){
	  wdata[j]=j;
	  rdata[j]=0;
	  if(DEBUG==1){printf("wdata[0x%05x]=0x%05x\n", j, wdata[j]); fflush(stdout);}
	}
	
	UTL_SetUbmAccessPinBlock(uacsh, 1);
	UTL_SetUbmAccessBitReverse(uacsh, UT_ON);
	UTL_SetUbmAccessDdrMode(uacsh, UT_OFF);
	UTL_SetUbmAccessPin(uacsh, "IOPIN");
	UTL_SetUbmAccessStartAddr(uacsh, 0x0);
	UTL_SetUbmAccessStopAddr (uacsh, PATSIZE-1);
	dutc = UTL_GetDutCursor(UT_CDUT);
	while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
	  UTL_SetUbmAccessDut(uacsh, dut);
	  UTL_WriteUbm(uacsh, wdata, ubmsize);
	}
	UTL_DeleteCursor(dutc);
	UTL_ReadUbm(uacsh, rdata, ubmsize);
	for(i=0;i<PATSIZE;i++){
	  if(DEBUG==1){
	    printf("wrchk[0x%05x]=0x%05x\n", i, rdata[i]);fflush(stdout);
	  }
	}
	UTL_DeleteHandle(uacsh);
	
	//DCM setting
        int dcmsize=0x80;
        USlider  size = dcmsize * sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	DCM_DATA[0]=0x030;

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_SEQRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize);
        UTL_DeleteHandle                (dcm_h);

	//MEAS MPAT
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x120);
	UTL_MeasFct(Fct_H); 
	UTL_DeleteHandle        (Fct_H);
	

	//display Result
	DutCursor dutcur=UTL_GetDutCursor(UT_FDUT);
	dut=0;
	while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
	    result=result | 0x1<<dut-1;
	}
        UTL_DeleteCursor (dutcur);

	display(result);
}


void dcm_seqrm_ap_check()
{
	int i,j,k;
	int result=0;

	int REG_DATA[0x80];
	int REG_EXP[0x80];
	for(i=0;i<0x80;i++){
		REG_DATA[i]=0;
		REG_EXP[i]=0x10*(i+1)+0x1;
	}

	timing_setting();
	
	//DCM setting
        int dcmsize=0x80;
        USlider  size = dcmsize * sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	for(i=0;i<0x80;i++){
		DCM_DATA[i]=0x10*(i+1);
		if(DEBUG==1){printf("DCMAP[0x%X]=0x%02X\n",i,DCM_DATA[i]);fflush(stdout);}
	}

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_SEQRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize);
        UTL_DeleteHandle                (dcm_h);

	for(i=0;i<0x80;i++){
		//MEAS MPAT
		FctHandle Fct_H = UTL_GetFctHandle();
		UTL_SetFctMpatName      (Fct_H, "pat_dcm1_ap.mpa");
		UTL_SetFctFailInhibit   (Fct_H, UT_ON);
		UTL_SetFctStartPc       (Fct_H, 0x010*i	);
		UTL_MeasFct(Fct_H); 
		UTL_DeleteHandle        (Fct_H);
		
		//Read Register
		REG_DATA[i]=UTL_ReadUSRegister	(UT_REG_XB,	1);
	}
	//Display Result
	printf("\n-----------------------------\n");
	printf("DCMAP| EXP    MEAS  |RESULT\n");
	printf("-----------------------------\n");
	for(i=0;i<0x80;i++){
		printf("0x%02X | 0x%03X  0x%03X |",i,REG_EXP[i],REG_DATA[i]);
		if(REG_DATA[i]==REG_EXP[i]){
			printf("**PASS\n");
		}else{
			printf("FAIL***\n");result=1;}
	}
	printf("-----------------------------\n");

	display(result);
}


void dcm_addrm_check()
{
	int i,j,k;
	int result=0;
	char REG_NAME[0x1DE][4]={"XH","YH","D1","D2","D3B","D4B","ZD","ZH","NH","BH","ND1","ND2","ND3","ND4","ND5","ND6","ND7","BD1","BD2","BD3","BD4","BD5","BD6","BD7","Z","XOS","YOS","XT","YT"};
	int REG_EXP[0x1D]={0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x90,0xA0,0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0x190,0x1A0,0x1B0,0x1C0,0x1D0};	

	int REG1_DATA[0x1D];	//[XB,TB,...,YR3]
	int REG2_DATA[0x1D];	//[XB,TB,...,YR3]
	for(i=0;i<0x1D;i++){
		REG1_DATA[i]=0;
		REG2_DATA[i]=0;
	}

	timing_setting();
	
	//DCM setting
        int dcmsize=0x400;
        USlider  size = dcmsize * sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	j=0;
	k=0;
	for(i=0;i<0x1D;i++){
		if	(i>=0xA && i<=0x10)	{	DCM_DATA[i]=0xB0+j; j++;}
		else if	(i>=0x11 && i<=0x17)	{	DCM_DATA[i]=0xC0+k; k++;}
		else				{	DCM_DATA[i]=0x10*(i+1);	}

		if(DEBUG==1){printf("DCMAP[0x%X]=0x%02X\n",i,DCM_DATA[i]);fflush(stdout);}
	}

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_ADDRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize);
        UTL_DeleteHandle                (dcm_h);

	//MEAS MPAT (REG_1)
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x200);
	UTL_MeasFct(Fct_H); 
        UTL_DeleteHandle                (Fct_H);
	
	//Read Register (REG_1)
	REG1_DATA[0x0]=UTL_ReadUSRegister	(UT_REG_XH,	1);
	REG1_DATA[0x1]=UTL_ReadUSRegister	(UT_REG_YH,	1);
	REG1_DATA[0x2]=UTL_ReadUSRegister	(UT_REG_D1,	1);
	REG1_DATA[0x3]=UTL_ReadUSRegister	(UT_REG_D2,	1);
	REG1_DATA[0x4]=UTL_ReadUSRegister	(UT_REG_D3,	1);
	//REG1_DATA[0x4]=UTL_ReadUSRegister	(UT_REG_D3B,	1);
	REG1_DATA[0x5]=UTL_ReadUSRegister	(UT_REG_D4,	1);
	//REG1_DATA[0x5]=UTL_ReadUSRegister	(UT_REG_D4B,	1);
	REG1_DATA[0x6]=UTL_ReadUSRegister	(UT_REG_ZD,	1);
	REG1_DATA[0x7]=UTL_ReadUSRegister	(UT_REG_ZH,	1);
	REG1_DATA[0x8]=UTL_ReadUSRegister	(UT_REG_NH,	1);
	REG1_DATA[0x9]=UTL_ReadUSRegister	(UT_REG_BH,	1);
	REG1_DATA[0xA]=UTL_ReadUSRegister	(UT_REG_ND,	1);
	REG1_DATA[0xB]=UTL_ReadUSRegister	(UT_REG_ND2,	1);
	REG1_DATA[0xC]=UTL_ReadUSRegister	(UT_REG_ND3,	1);
	REG1_DATA[0xD]=UTL_ReadUSRegister	(UT_REG_ND4,	1);
	REG1_DATA[0xE]=UTL_ReadUSRegister	(UT_REG_ND5,	1);
	REG1_DATA[0xF]=UTL_ReadUSRegister	(UT_REG_ND6,	1);
	REG1_DATA[0x10]=UTL_ReadUSRegister	(UT_REG_ND7,	1);
	REG1_DATA[0x11]=UTL_ReadUSRegister	(UT_REG_BD,	1);
	REG1_DATA[0x12]=UTL_ReadUSRegister	(UT_REG_BD2,	1);
	REG1_DATA[0x13]=UTL_ReadUSRegister	(UT_REG_BD3,	1);
	REG1_DATA[0x14]=UTL_ReadUSRegister	(UT_REG_BD4,	1);
	REG1_DATA[0x15]=UTL_ReadUSRegister	(UT_REG_BD5,	1);
	REG1_DATA[0x16]=UTL_ReadUSRegister	(UT_REG_BD6,	1);
	REG1_DATA[0x17]=UTL_ReadUSRegister	(UT_REG_BD7,	1);
	REG1_DATA[0x18]=UTL_ReadUSRegister	(UT_REG_Z,	1);
	REG1_DATA[0x19]=UTL_ReadUSRegister	(UT_REG_XOS,	1);
	REG1_DATA[0x1A]=UTL_ReadUSRegister	(UT_REG_YOS,	1);
	REG1_DATA[0x1B]=UTL_ReadUSRegister	(UT_REG_XT,	1);
	REG1_DATA[0x1C]=UTL_ReadUSRegister	(UT_REG_YT,	1);


	//MEAS MPAT (REG_2)
	Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x240);
	UTL_MeasFct(Fct_H); 
	
	//Read Register (REG_2)
	REG2_DATA[0x0]=UTL_ReadUSRegister	(UT_REG_XH_2,	1);
	REG2_DATA[0x1]=UTL_ReadUSRegister	(UT_REG_YH_2,	1);
	REG2_DATA[0x2]=UTL_ReadUSRegister	(UT_REG_D1_2,	1);
	REG2_DATA[0x3]=UTL_ReadUSRegister	(UT_REG_D2_2,	1);
	REG2_DATA[0x4]=UTL_ReadUSRegister	(UT_REG_D3_2,	1);
	//REG2_DATA[0x4]=UTL_ReadUSRegister	(UT_REG_D3B_2,	1);
	REG2_DATA[0x5]=UTL_ReadUSRegister	(UT_REG_D4_2,	1);
	//REG2_DATA[0x5]=UTL_ReadUSRegister	(UT_REG_D4B_2,	1);
	REG2_DATA[0x6]=UTL_ReadUSRegister	(UT_REG_ZD_2,	1);
	REG2_DATA[0x7]=UTL_ReadUSRegister	(UT_REG_ZH_2,	1);
	REG2_DATA[0x8]=UTL_ReadUSRegister	(UT_REG_NH_2,	1);
	REG2_DATA[0x9]=UTL_ReadUSRegister	(UT_REG_BH_2,	1);
	REG2_DATA[0xA]=UTL_ReadUSRegister	(UT_REG_ND_2,	1);
	REG2_DATA[0xB]=UTL_ReadUSRegister	(UT_REG_ND2_2,	1);
	REG2_DATA[0xC]=UTL_ReadUSRegister	(UT_REG_ND3_2,	1);
	REG2_DATA[0xD]=UTL_ReadUSRegister	(UT_REG_ND4_2,	1);
	REG2_DATA[0xE]=UTL_ReadUSRegister	(UT_REG_ND5_2,	1);
	REG2_DATA[0xF]=UTL_ReadUSRegister	(UT_REG_ND6_2,	1);
	REG2_DATA[0x10]=UTL_ReadUSRegister	(UT_REG_ND7_2,	1);
	REG2_DATA[0x11]=UTL_ReadUSRegister	(UT_REG_BD_2,	1);
	REG2_DATA[0x12]=UTL_ReadUSRegister	(UT_REG_BD2_2,	1);
	REG2_DATA[0x13]=UTL_ReadUSRegister	(UT_REG_BD3_2,	1);
	REG2_DATA[0x14]=UTL_ReadUSRegister	(UT_REG_BD4_2,	1);
	REG2_DATA[0x15]=UTL_ReadUSRegister	(UT_REG_BD5_2,	1);
	REG2_DATA[0x16]=UTL_ReadUSRegister	(UT_REG_BD6_2,	1);
	REG2_DATA[0x17]=UTL_ReadUSRegister	(UT_REG_BD7_2,	1);
	REG2_DATA[0x18]=UTL_ReadUSRegister	(UT_REG_Z_2,	1);

	//Display Result
	printf("[REG_1]\n");
	printf("-------------------------------------------\n");
	printf("    | [REG_1]      | [REG_2]      | \n");
	printf(" REG| EXP    MEAS  | EXP    MEAS  |RESULT\n");
	printf("-------------------------------------------\n");
	for(i=0;i<0x1D;i++){
		if(i<=0x18){
			printf(" %3s| 0x%03X  0x%03X | 0x%03X  0x%03X |",REG_NAME[i],REG_EXP[i],REG1_DATA[i],REG_EXP[i],REG2_DATA[i]);
			if(REG1_DATA[i]==REG_EXP[i] && REG2_DATA[i]==REG_EXP[i]){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
		}else{
			printf(" %3s| 0x%03X  0x%03X | -----  ----- |",REG_NAME[i],REG_EXP[i],REG1_DATA[i]);
			if(REG1_DATA[i]==REG_EXP[i]){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
		}
	}
	printf("-------------------------------------------\n");
	
	display(result);

}


void dcm_addrm_ap_check()
{
	int i,j,k;
	int result=0;

	pin_list();
	level_setting();
	timing_setting();
	pin_setting(); 
	
	//DCM setting
        int dcmsize=0x400;
        USlider  size = dcmsize * sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	for(i=0;i<0x400;i++){
		DCM_DATA[i]=i;
		if(DEBUG==1){printf("DCMAP[0x%X]=0x%03X\n",i,DCM_DATA[i]);fflush(stdout);}
	}

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_ADDRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize);
        UTL_DeleteHandle                (dcm_h);

	//MEAS MPAT 
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm2_ap.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x000);
	UTL_MeasFct(Fct_H); 
        UTL_DeleteHandle                (Fct_H);
	

	//Display Result
	DutCursor dutcur=UTL_GetDutCursor(UT_FDUT);
	UT_DUT dut=0;
	while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
	    result=result | 0x1<<dut-1;
	}
        UTL_DeleteCursor (dutcur);

	display(result);

}


void dcm_addrm_apset_pat_check()
{
	int i,j,k;
	int result=0;

	pin_list();
	level_setting();
	timing_setting();
	pin_setting(); 
	
	//DCM setting
        int dcmsize=0x400;
        USlider  size = dcmsize * sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	for(i=0;i<0x400;i++){
		DCM_DATA[i]=i;
		if(DEBUG==1){printf("DCMAP[0x%X]=0x%03X\n",i,DCM_DATA[i]);fflush(stdout);}
	}

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_ADDRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize);
        UTL_DeleteHandle                (dcm_h);

	//MEAS MPAT 
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm2_apset.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x000);
	UTL_MeasFct(Fct_H); 
        UTL_DeleteHandle                (Fct_H);
	

	//Display Result
	DutCursor dutcur=UTL_GetDutCursor(UT_FDUT);
	UT_DUT dut=0;
	while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
	    result=result | 0x1<<dut-1;
	}
        UTL_DeleteCursor (dutcur);

	display(result);

}


void dcm_addrm_apset_main_check()
{
	int i,j,k;
	int result=0;
	int data1=0; //for REGISTER
	int data2=0; //for SetRegUs
	int data3=0; //for SetRegUs(AP)

	pin_list();
	level_setting();
	timing_setting();
	pin_setting(); 
	
	//DCM setting
        int dcmsize=0x400;
        USlider  size = dcmsize * sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	for(i=0;i<0x400;i++){
		DCM_DATA[i]=i;
		if(DEBUG==1){printf("DCMAP[0x%X]=0x%03X\n",i,DCM_DATA[i]);fflush(stdout);}
	}

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_ADDRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize);
        UTL_DeleteHandle                (dcm_h);

	// -- REGISTER check --
	//MEAS MPAT 
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm2_apset.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x100);
	UTL_MeasFct(Fct_H); 
        UTL_DeleteHandle                (Fct_H);
	//Read Register 
	data1=UTL_ReadUSRegister	(UT_REG_XH,	1);

	// -- SetRegUs check --
	RegHandle regh=UTL_GetRegHandle();
	UTL_SetRegUs(regh,UT_REG_ADDRMAP,1,0x3FF);
	UTL_SendReg (regh);
	//MEAS MPAT 
	Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm2_apset.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x100);
	UTL_MeasFct(Fct_H); 
        UTL_DeleteHandle                (Fct_H);
	//Read Register 
	data2=UTL_ReadUSRegister	(UT_REG_XH,	1);
	data3=UTL_ReadUSRegister	(UT_REG_ADDRMAP,1);

	//Display Result
	printf("------------------------------------\n");
	printf(" SET     |REG| EXP    MEAS  |RESULT\n");
	printf("------------------------------------\n");
	printf(" REGISTER|XH | 0x100  0x%03X |",data1);
	if(data1==0x100){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
	printf(" SetRegUs|XH | 0x3FF  0x%03X |",data2);
	if(data2==0x3FF){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
	printf(" SetRegUs|AP | 0x3FF  0x%03X |",data3);
	if(data3==0x3FF){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
	printf("-------------------------------------------\n");


	//Display Result
	DutCursor dutcur=UTL_GetDutCursor(UT_FDUT);
	UT_DUT dut=0;
	while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
	    result=result | 0x1<<dut-1;
	}
        UTL_DeleteCursor (dutcur);

	display(result);

}


void dcm_addrm_apinc_check()
{
	int i,j,k;
	int result=0;

	pin_list();
	level_setting();
	timing_setting();
	pin_setting(); 
	
	//DCM setting
        int dcmsize=0x400;
        USlider  size = dcmsize * sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	for(i=0;i<0x400;i++){
		DCM_DATA[i]=i;
		if(DEBUG==1){printf("DCMAP[0x%X]=0x%03X\n",i,DCM_DATA[i]);fflush(stdout);}
	}

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_ADDRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize);
        UTL_DeleteHandle                (dcm_h);

	//MEAS MPAT 
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm2_apset.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x200);
	UTL_MeasFct(Fct_H); 
        UTL_DeleteHandle                (Fct_H);
	

	//Display Result
	DutCursor dutcur=UTL_GetDutCursor(UT_FDUT);
	UT_DUT dut=0;
	while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
	    result=result | 0x1<<dut-1;
	}
        UTL_DeleteCursor (dutcur);

	display(result);

}


void dcm_datrm_check()
{
	int i=0,j=0,k=0;
	RadioButton block;
	int result=0;
	char REG_NAME[0xE][6]={"TP1","TP2","TPH1A","TPH2A","D5A","D6A","DCMR1","DCMR2","XMASK","YMASK","RCD","CCD","DSD","DBMAP"};

	int REG1_DATA[2][0xE];	//[block][XB,TB,...,YR3]
	int REG2_DATA[2][0xE];	//[block][XB,TB,...,YR3]
	for(block=0;block<2;block++){
		for(i=0;i<0xE;i++){
			REG1_DATA[block][i]=0;
			REG2_DATA[block][i]=0;
		}
	}

	timing_setting();
	
	//DCM setting
        int dcmsize=0x400;
        USlider  size = dcmsize * sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	DCM_DATA[0x00]=0xAAAAAAAA;	DCM_DATA[0x01]=0xA;	//DATRM(#0)=TP1
	DCM_DATA[0x02]=0xBBBBBBBB;	DCM_DATA[0x03]=0xB;	//DATRM(#1)=TP2
	DCM_DATA[0x04]=0xCCCCCCCC;	DCM_DATA[0x05]=0xC;	//DATRM(#2)=TPH1
	DCM_DATA[0x06]=0xDDDDDDDD;	DCM_DATA[0x07]=0xD;	//DATRM(#3)=TPH2
	DCM_DATA[0x08]=0xEEEEEEEE;	DCM_DATA[0x09]=0xE;	//DATRM(#4)=D5
	DCM_DATA[0x0A]=0xFFFFFFFF;	DCM_DATA[0x0B]=0xF;	//DATRM(#5)=D6
	DCM_DATA[0x0C]=0xF0F0F0F0;	DCM_DATA[0x0D]=0x0;	//DATRM(#6)=DCMR1
	DCM_DATA[0x0E]=0x0F0F0F0F;	DCM_DATA[0x0F]=0xF;	//DATRM(#7)=DCMR2
	DCM_DATA[0x10]=0x00BBBBBB;	DCM_DATA[0x11]=0x0;	//DATRM(#8)=XMASK
	DCM_DATA[0x12]=0x00CCCCCC;	DCM_DATA[0x13]=0x0;	//DATRM(#9)=YMASK
	DCM_DATA[0x14]=0x00DDDDDD;	DCM_DATA[0x15]=0x0;	//DATRM(#A)=RCD
	DCM_DATA[0x16]=0x00EEEEEE;	DCM_DATA[0x17]=0x0;	//DATRM(#B)=CCD
	DCM_DATA[0x18]=0x00FFFFFF;	DCM_DATA[0x19]=0x0;	//DATRM(#C)=DSD
	DCM_DATA[0x1A]=0x0FFFFFFF;	DCM_DATA[0x1B]=0x0;	//DATRM(#D)=DBMAP

	if(DEBUG==1){printf("DCMAP[0x%X]=0x%03X\n",i,DCM_DATA[i]);fflush(stdout);}

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_DATRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize);
        UTL_DeleteHandle                (dcm_h);

	//MEAS MPAT (REG_1)
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x300);
	UTL_MeasFct(Fct_H); 
        UTL_DeleteHandle                (Fct_H);
	
	//Read Register (REG_1)
	USlider bitsize;
	for(block=1;block<=2;block++){
		if(block==1) bitsize=0xFFFFFFFF;
		if(block==2) bitsize=0xF;

		REG1_DATA[block-1][0x0]=UTL_ReadUSRegister	(UT_REG_TP,	block);
		REG1_DATA[block-1][0x1]=UTL_ReadUSRegister	(UT_REG_TP2,	block);
		REG1_DATA[block-1][0x2]=UTL_ReadUSRegister	(UT_REG_TPH,	block);
		REG1_DATA[block-1][0x3]=UTL_ReadUSRegister	(UT_REG_TPH2,	block);
		REG1_DATA[block-1][0x4]=UTL_ReadUSRegister	(UT_REG_D5,	block);
		REG1_DATA[block-1][0x5]=UTL_ReadUSRegister	(UT_REG_D6,	block);
		REG1_DATA[block-1][0x6]=bitsize&~UTL_ReadUSRegister	(UT_REG_DCMR,	block);
		REG1_DATA[block-1][0x7]=bitsize&~UTL_ReadUSRegister	(UT_REG_DCMR2,	block);
	}

	REG1_DATA[0][0x8]=UTL_ReadUSRegister	(UT_REG_XMASK,	1);
	REG1_DATA[0][0x9]=UTL_ReadUSRegister	(UT_REG_YMASK,	1);
	REG1_DATA[0][0xA]=UTL_ReadUSRegister	(UT_REG_RCD,	1);
	REG1_DATA[0][0xB]=UTL_ReadUSRegister	(UT_REG_CCD,	1);
	REG1_DATA[0][0xC]=UTL_ReadUSRegister	(UT_REG_DSD,	1);
//	REG1_DATA[0][0xD]=UTL_ReadUSRegister	(UT_REG_DBMA,	1);	

	//MEAS MPAT (REG_2)
	Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x340);
	UTL_MeasFct(Fct_H); 
        UTL_DeleteHandle                (Fct_H);
	
	//Read Register (REG_2)
	for(block=1;block<=2;block++){

		REG2_DATA[block-1][0x0]=UTL_ReadUSRegister	(UT_REG_TP_2,	block);
		REG2_DATA[block-1][0x1]=UTL_ReadUSRegister	(UT_REG_TP2_2,	block);
		REG2_DATA[block-1][0x2]=UTL_ReadUSRegister	(UT_REG_TPH_2,	block);
		REG2_DATA[block-1][0x3]=UTL_ReadUSRegister	(UT_REG_TPH2_2,	block);
		REG2_DATA[block-1][0x4]=UTL_ReadUSRegister	(UT_REG_D5_2,	block);
		REG2_DATA[block-1][0x5]=UTL_ReadUSRegister	(UT_REG_D6_2,	block);
	}
	
	//Display Result
	printf("\n------------------------------------------------------------------\n");
	printf("     |              | [REG_1]              | [REG_2]             |\n");
	printf(" REG | EXP          |  MEAS         RESULT | MEAS         RESULT |\n");
	printf("------------------------------------------------------------------\n");
	for(i=0;i<0xD;i++){
	//for(i=0;i<0xE;i++){  //+DBMAP
		printf("%5s|",REG_NAME[i]);
		printf(" 0x%01X %08X | ",DCM_DATA[i*2+1] ,DCM_DATA[i*2]);
		//REG_1
		printf(" 0x%01X %08X ",REG1_DATA[1][i],REG1_DATA[0][i]);
		if(REG1_DATA[1][i] == DCM_DATA[i*2+1] && REG1_DATA[0][i]==DCM_DATA[i*2]){printf("**PASS |");}else{printf("FAIL** |");result=1;}
		//REG_2
		if(i<=0x5){
			printf(" 0x%01X %08X ",REG2_DATA[1][i],REG2_DATA[0][i]);
			if(REG2_DATA[1][i]==DCM_DATA[i*2+1] && REG2_DATA[0][i]==DCM_DATA[i*2]){printf("**PASS |\n");}else{printf("FAIL** |\n");result=1;}
		}else{
			printf(" ------------  ----- |\n");
		}
	}
	printf("------------------------------------------------------------------\n");
	
	display(result);
}


void dcm_datrm_ap_check()
{

	int i=0,j=0,k=0;
	int result=0;

	pin_list();
	level_setting();
	timing_setting();
	pin_setting(); 
	
	//DCM setting
        int dcmsize=0x400;
        USlider  size = dcmsize *4*2* sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	for(i=0;i<dcmsize*2;i++){
		if(i%2==0){DCM_DATA[i]=j;j++;}
		else{DCM_DATA[i]=0;}
		if(DEBUG==1){printf("DCMAP[0x%X]=0x%03X\n",i,DCM_DATA[i]);fflush(stdout);}
	}

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_DATRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize*4*2);
        UTL_DeleteHandle                (dcm_h);

	//MEAS MPAT 
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm3_ap.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x000);
	UTL_MeasFct(Fct_H); 
        UTL_DeleteHandle                (Fct_H);
	

	//Display Result
	DutCursor dutcur=UTL_GetDutCursor(UT_FDUT);
	UT_DUT dut=0;
	while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
	    result=result | 0x1<<dut-1;
	}
        UTL_DeleteCursor (dutcur);

	display(result);

}


void dcm_datrm_apset_pat_check()
{

	int i=0,j=0,k=0;
	int result=0;

	pin_list();
	level_setting();
	timing_setting();
	pin_setting(); 
	
	//DCM setting
        int dcmsize=0x400;
        USlider  size = dcmsize *4*2* sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	for(i=0;i<dcmsize*2;i++){
		if(i%2==0){DCM_DATA[i]=j;j++;}
		else{DCM_DATA[i]=0;}
		if(DEBUG==1){printf("DCMAP[0x%X]=0x%03X\n",i,DCM_DATA[i]);fflush(stdout);}
	}

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_DATRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize*4*2);
        UTL_DeleteHandle                (dcm_h);

	//MEAS MPAT 
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm3_apset.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x000);
	UTL_MeasFct(Fct_H); 
        UTL_DeleteHandle                (Fct_H);
	

	//Display Result
	DutCursor dutcur=UTL_GetDutCursor(UT_FDUT);
	UT_DUT dut=0;
	while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
	    result=result | 0x1<<dut-1;
	}
        UTL_DeleteCursor (dutcur);

	display(result);

}

void dcm_datrm_apset_main_check()
{
	int i=0,j=0,k=0;
	int result=0;
	int data1=0; //for REGISTER
	int data2=0; //for SetRegUs
	int data3=0; //for SetRegUs(TP)

	pin_list();
	level_setting();
	timing_setting();
	pin_setting(); 
	//DCM setting
        int dcmsize=0x400;
        USlider  size = dcmsize *4*2* sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	for(i=0;i<dcmsize*2;i++){
		if(i%2==0){DCM_DATA[i]=j;j++;}
		else{DCM_DATA[i]=0;}
	}

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_DATRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize*4*2);
        UTL_DeleteHandle                (dcm_h);

	// -- REGISTER check --
	//MEAS MPAT 
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm3_apset.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x100);
	UTL_MeasFct(Fct_H); 
        UTL_DeleteHandle                (Fct_H);
	//Read Register 
	data1=UTL_ReadUSRegister	(UT_REG_TP,	1);

	// -- SetRegUs check --
	RegHandle regh=UTL_GetRegHandle();
	UTL_SetRegUs(regh,UT_REG_DATRMAP,1,0x3FF);
	UTL_SendReg (regh);
	//MEAS MPAT 
	Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm3_apset.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x100);
	UTL_MeasFct(Fct_H); 
        UTL_DeleteHandle                (Fct_H);
	//Read Register 
	data2=UTL_ReadUSRegister	(UT_REG_TP,	1);
	data3=UTL_ReadUSRegister	(UT_REG_DATRMAP,1);

	//Display Result
	printf("------------------------------------\n");
	printf(" SET     |REG| EXP    MEAS  |RESULT\n");
	printf("------------------------------------\n");
	printf(" REGISTER|TP | 0x100  0x%03X |",data1);
	if(data1==0x100){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
	printf(" SetRegUs|TP | 0x3FF  0x%03X |",data2);
	if(data2==0x3FF){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
	printf(" SetRegUs|AP | 0x3FF  0x%03X |",data3);
	if(data3==0x3FF){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
	printf("-------------------------------------------\n");


	//Display Result
	DutCursor dutcur=UTL_GetDutCursor(UT_FDUT);
	UT_DUT dut=0;
	while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
	    result=result | 0x1<<dut-1;
	}
        UTL_DeleteCursor (dutcur);

	display(result);

}



void dcm_datrm_apinc_check()
{

	int i=0,j=0,k=0;
	int result=0;

	pin_list();
	level_setting();
	timing_setting();
	pin_setting(); 
	
	//DCM setting
        int dcmsize=0x400;
        USlider  size = dcmsize *4*2* sizeof(USlider); /*exp*/
        USlider *DCM_DATA = NULL;                                               /*exp*/
        DCM_DATA = (USlider *)malloc(size);                                     /*exp*/
        if(DCM_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM_DATA, 0x0, sizeof(DCM_DATA));
        
	for(i=0;i<dcmsize*2;i++){
		if(i%2==0){DCM_DATA[i]=j;j++;}
		else{DCM_DATA[i]=0;}
		if(DEBUG==1){printf("DCMAP[0x%X]=0x%03X\n",i,DCM_DATA[i]);fflush(stdout);}
	}

        int sta=0x00;
        int stp=sta+dcmsize-1;

        RegMemoryHandle dcm_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm_h, UT_REGMEMORY_DATRM);
        UTL_SetRegMemoryStartAddr       (dcm_h, sta              );
        UTL_SetRegMemoryStopAddr        (dcm_h, stp              );
        UTL_WriteRegMemory              (dcm_h, DCM_DATA, dcmsize*4*2);
        UTL_DeleteHandle                (dcm_h);

	//MEAS MPAT 
	FctHandle Fct_H = UTL_GetFctHandle();
	UTL_SetFctMpatName      (Fct_H, "pat_dcm3_apset.mpa");
	UTL_SetFctFailInhibit   (Fct_H, UT_ON);
	UTL_SetFctStartPc       (Fct_H, 0x200);
	UTL_MeasFct(Fct_H); 
        UTL_DeleteHandle                (Fct_H);
	

	//Display Result
	DutCursor dutcur=UTL_GetDutCursor(UT_FDUT);
	UT_DUT dut=0;
	while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
	    result=result | 0x1<<dut-1;
	}
        UTL_DeleteCursor (dutcur);

	display(result);

}


void dcm_way_check()
{
	int i,j,k;
	int result=0;
	int idx1_data=0;

	timing_setting();
	
	//DCM1 setting
        int dcmsize1=0x80;
        USlider  size1 = dcmsize1 * sizeof(USlider); /*exp*/
        USlider *DCM1_DATA = NULL;                                               /*exp*/
        DCM1_DATA = (USlider *)malloc(size1);                                     /*exp*/
        if(DCM1_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM1_DATA, 0x0, sizeof(DCM1_DATA));
        
	DCM1_DATA[0]=0x10;
	if(DEBUG==1){printf("SEQRM AP[0x%X]=0x%02X\n",i,DCM1_DATA[0]);fflush(stdout);}
	
        int sta1=0x00;
        int stp1=sta1+dcmsize1-1;

        RegMemoryHandle dcm1_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm1_h, UT_REGMEMORY_SEQRM);
        UTL_SetRegMemoryStartAddr       (dcm1_h, sta1              );
        UTL_SetRegMemoryStopAddr        (dcm1_h, stp1              );
        UTL_WriteRegMemory              (dcm1_h, DCM1_DATA, dcmsize1);
        UTL_DeleteHandle                (dcm1_h);

	//DCM2 setting
        int dcmsize2=0x400;
        USlider  size2 = dcmsize2 * sizeof(USlider); /*exp*/
        USlider *DCM2_DATA = NULL;                                               /*exp*/
        DCM2_DATA = (USlider *)malloc(size2);                                     /*exp*/
        if(DCM2_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM2_DATA, 0x0, sizeof(DCM2_DATA));
        
	DCM2_DATA[0]=0x20;
	DCM2_DATA[1]=0x30;
	if(DEBUG==1){printf("ADDRM AP[0x0]=0x%02X\n",DCM2_DATA[0]);fflush(stdout);}
	if(DEBUG==1){printf("ADDRM AP[0x1]=0x%02X\n",DCM2_DATA[1]);fflush(stdout);}
	
        int sta2=0x00;
        int stp2=sta2+dcmsize2-1;

        RegMemoryHandle dcm2_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm2_h, UT_REGMEMORY_ADDRM);
        UTL_SetRegMemoryStartAddr       (dcm2_h, sta2              );
        UTL_SetRegMemoryStopAddr        (dcm2_h, stp2              );
        UTL_WriteRegMemory              (dcm2_h, DCM2_DATA, dcmsize2);
        UTL_DeleteHandle                (dcm2_h);

	//DCM3 setting
        int dcmsize3=0x400;
        USlider  size3 = dcmsize3 * sizeof(USlider); /*exp*/
        USlider *DCM3_DATA = NULL;                                               /*exp*/
        DCM3_DATA = (USlider *)malloc(size3);                                     /*exp*/
        if(DCM3_DATA==NULL) { printf(" *** malloc error\n"); return; }
        memset(DCM3_DATA, 0x0, sizeof(DCM3_DATA));
        
	DCM3_DATA[0]=0x40;
	DCM3_DATA[1]=0x00;
	DCM3_DATA[2]=0x50;//test
	DCM3_DATA[3]=0x00;
	if(DEBUG==1){printf("DATRM AP[0x0]=0x%02X\n",DCM3_DATA[0]);fflush(stdout);}
	if(DEBUG==1){printf("DATRM AP[0x1]=0x%02X\n",DCM3_DATA[1]);fflush(stdout);}

        int sta3=0x00;
        int stp3=sta3+dcmsize3-1;

        RegMemoryHandle dcm3_h=UTL_GetRegMemoryHandle();
        UTL_SetRegMemoryTarget          (dcm3_h, UT_REGMEMORY_DATRM);
        UTL_SetRegMemoryStartAddr       (dcm3_h, sta3              );
        UTL_SetRegMemoryStopAddr        (dcm3_h, stp3              );
        UTL_WriteRegMemory              (dcm3_h, DCM3_DATA, dcmsize3);
        UTL_DeleteHandle                (dcm3_h);


	int way;
	for(way=2; way<=8; way=way*2){	

		int xh_data=0;
		int yh_data=0;		
		int tp1_data=0;	
		int tp2_data=0;	

		set_interleave_mode(way);
	
		//MEAS MPAT
		int pc;
		if(way==2) pc=0x400;
		if(way==4) pc=0x420;
		if(way==8) pc=0x440;
	 
		FctHandle Fct_H = UTL_GetFctHandle();
		UTL_SetFctMpatName      (Fct_H, "pat_dcm.mpa");
		UTL_SetFctFailInhibit   (Fct_H, UT_ON);
		UTL_SetFctStartPc       (Fct_H, pc);
		UTL_MeasFct(Fct_H); 
	        UTL_DeleteHandle                (Fct_H);
		
		//Read Register 
		idx1_data=UTL_ReadUSRegister	(UT_REG_IDX1,	1);//IDX1=ReadData+1 @IDXLOOP1
		xh_data=UTL_ReadUSRegister	(UT_REG_XH,	1);
		yh_data=UTL_ReadUSRegister	(UT_REG_YH,	1);
		tp1_data=UTL_ReadUSRegister	(UT_REG_TP,	1);
		tp2_data=UTL_ReadUSRegister	(UT_REG_TP2,	1);
		
		//Display Result
		printf("\n[%dWAY]\n",way);
		printf("----------------------------\n");
		printf(" REG | EXP   MEAS  |RESULT\n");
		printf("----------------------------\n");
		printf(" IDX1| 0x10  0x%03X |",idx1_data+1); if(idx1_data+1==0x10){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
		printf("   XH| 0x20  0x%03X |",xh_data	  ); if(    xh_data==0x20){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
		printf("   YH| 0x30  0x%03X |",yh_data	  ); if(    yh_data==0x30){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
		printf("  TP1| 0x40  0x%03X |",tp1_data	  ); if(   tp1_data==0x40){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
		printf("  TP2| 0x50  0x%03X |",tp2_data	  ); if(   tp2_data==0x50){printf("**PASS\n");}else{printf("FAIL***\n");result=1;}
		printf("----------------------------\n");

		//Display Result
		DutCursor dutcur=UTL_GetDutCursor(UT_FDUT);
		UT_DUT dut=0;
		while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
		    result=result | 0x1<<dut-1;
		}
	        UTL_DeleteCursor (dutcur);
	}
	display(result);

}
