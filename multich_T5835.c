#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "UTSC.h"
#include "test.h"
#include "test_struct.h"
#include "multich.h"
#include "common.h"

#define DEBUG 0
#define DEBUG2 1

#define V *1.0
#define ms *1.0e-3
#define us *1.0e-6
#define ns *1.0e-9
#define mA *1.0e-3
#define uA *1.0e-6
#define nA *1.0e-9

#define CAPTDAT 1

//////////////////////////////////////////////////////////////////////////
// BBM settings
//////////////////////////////////////////////////////////////////////////
#define DUTMAX		4
#define IOCNT		8
//////////////////////////////////////////////////////////////////////////
// DUT Channnel settings
//////////////////////////////////////////////////////////////////////////
#define DUTCHMAX	4
//////////////////////////////////////////////////////////////////////////
#define BBM_XBIT	6									//x bit count
#define BBM_YBIT	0									//y bit count
#define BBM_XMAX	(0x1<<BBM_XBIT)-1
#define BBM_YMAX	(0x1<<BBM_YBIT)-1
#define BBM_SIZE	(BBM_XMAX+1)*(BBM_YMAX+1)
//////////////////////////////////////////////////////////////////////////
#define tdut 4
#define ubmcnt 1024
#define FLASHMODE "MAXFAIL"
#define HOLDMODE  "MATCH"

/** global variables */
USlider  multich_bb_addr[DUTMAX][BBM_SIZE] = {{0}};
USlider  multich_bbc[DUTMAX] = {0};
//! Only one of child A1 and A2 are stored into BBM/FCM. capdutgrp[0] indicates A1 DUTs, capdutgrp[1] does A2 DUTs. 
USlider  capdutgrp[2];

//Flash judge
Slider rdcounter0[tdut]={0,};
Slider rdcounter1[tdut]={0,};
Slider rdcounter2[tdut]={0,};
Slider rdcounter3[tdut]={0,};
CheckButton multich_rdmaxfail[tdut]={0,};
int multich_rdhold[tdut]={0,};

static void ilmode_setting(RadioButton ilmode)
{
	IlModeHandle ilm_h = UTL_GetIlModeHandle();
	UTL_SetIlMode   (ilm_h, ilmode);
	UTL_SendIlMode  (ilm_h);
	UTL_DeleteHandle(ilm_h);
}

static void pin_list(RadioButton dutchcnt)
{
    const int ptyp[] = { UT_SOCKET_PINTYPE_IO, UT_SOCKET_PINTYPE_DR };
    const int ptypcnt = sizeof(ptyp)/sizeof(ptyp[0]);
    int ptypidx;
    int *plst[ptypcnt], pcnt[ptypcnt], i;
    int pincount = 0;

    capdutgrp[0] = 0x00000003;
    capdutgrp[1] = 0x0000000c;

    for (ptypidx=0; ptypidx<ptypcnt; ptypidx++){
        if (UTSOCK_Info_GetDutPinList(ptyp[ptypidx], &plst[ptypidx], &pcnt[ptypidx])!=UTSOCK_OK){
            fputs("ERROR: UTSOCK_Info_GetDutPinList returns non-UTSOCK_OK",stderr);
            UTL_Stop();
        }
        pincount += pcnt[ptypidx];
    }
    printf("[DEBUG]pincount = %d\n", pincount);
    
    UTL_CreatePinList ("IOPIN");
    UTL_SetPinType    ("IOPIN",UT_PINTYPE_PIN);
    for(i=0; i<pcnt[0]; i++) UTL_AddPinNumber ("IOPIN", plst[0][i]);
    if(pcnt[1]){
		fputs("ERROR: UT_SOCKET_PINTYPE_DR exists",stderr);
		UTL_Stop();
	}

	//BBM test 1FunctionBlock/2DutChannel
	if(dutchcnt==2){
		UTL_CreatePinList("iopinlist0");
		UTL_SetPinType   ("iopinlist0", UT_PINTYPE_PIN);
		for(i=1; i<=8;  i++){UTL_AddPinNumber ("iopinlist0", i);}
	
		UTL_CreatePinList("iopinlist1");
		UTL_SetPinType   ("iopinlist1", UT_PINTYPE_PIN);
		for(i=9; i<=16; i++){UTL_AddPinNumber ("iopinlist1", i);}
	}

	//Flash test
    UTL_CreatePinList("matchpin0");
    UTL_SetPinType   ("matchpin0", UT_PINTYPE_PIN);
    UTL_AddPinNumber ("matchpin0", 1);

    if(dutchcnt==2){
		UTL_CreatePinList("matchpin1");
		UTL_SetPinType   ("matchpin1", UT_PINTYPE_PIN);
		UTL_AddPinNumber ("matchpin1", 9);
	}
    if(dutchcnt==4){
		UTL_CreatePinList("matchpin1");
		UTL_SetPinType   ("matchpin1", UT_PINTYPE_PIN);
		UTL_AddPinNumber ("matchpin1", 65);

		UTL_CreatePinList("matchpin2");
		UTL_SetPinType   ("matchpin2", UT_PINTYPE_PIN);
		UTL_AddPinNumber ("matchpin2", 129);

		UTL_CreatePinList("matchpin3");
		UTL_SetPinType   ("matchpin3", UT_PINTYPE_PIN);
		UTL_AddPinNumber ("matchpin3", 193);
	}

    UTL_CreatePinList("matchpin_all");
    UTL_SetPinType   ("matchpin_all", UT_PINTYPE_PIN);
	UTL_AppendPinList("matchpin_all", "matchpin0");
	UTL_AppendPinList("matchpin_all", "matchpin1");
	if(dutchcnt==4){
		UTL_AppendPinList("matchpin_all", "matchpin2");
		UTL_AppendPinList("matchpin_all", "matchpin3");
	}
}

static void power_seq(void)
{
    printf("[DEBUG]%s\n",__func__);
    PowerSeqHandle psh = UTL_GetPowerSeqHandle();
    UTL_AddPowerSeqOthers  (psh, 1);
    UTL_SetPowerSeqWaitTime(psh, 1, 5 ms);
    UTL_SendPowerSeq(psh);
    UTL_DeleteHandle(psh);
}

static void bbm_pin_condition(USlider dutchcnt)
{
    int i;
    int dutblock;

	PinHandle pin_h;
	pin_h=UTL_GetPinHandle();
	UTL_SetPinOpen  (pin_h,UT_ON);
//	UTL_SendPin     (pin_h, "hmode_pin");
	UTL_SendPin     (pin_h, "IOPIN");
	UTL_DeleteHandle(pin_h);

    PinHandle tesph = UTL_GetPinHandle();

    UTL_SetPinViNumber     (tesph, 1);
    UTL_SetPinDrWaveform   (tesph, UT_WAV_RZO);
    UTL_SetPinDrClock      (tesph, UT_PIN_BCLK, 1);
    UTL_SetPinDrClock      (tesph, UT_PIN_CCLK, 1);
    UTL_SetPinIoCtrl       (tesph, UT_ON);
    UTL_SetPinTerm         (tesph, UT_ON);
    UTL_SetPinVoNumber     (tesph, 1);
    UTL_SetPinVtNumber     (tesph, 1);
    UTL_SetPinDreNumber    (tesph, 1);
    UTL_SetPinDreWaveform  (tesph, UT_DREWAV_NRZ);
    UTL_SetPinDreClock     (tesph, 1); 
    UTL_AddPinStrbCpeNumber(tesph, 1, 1);

	UTL_ClearPinPdsA(tesph);
	UTL_ClearPinPdsB(tesph);

	for(i=0; i<8; i++){
		UTL_AddPinPdsA (tesph, UT_SIG_X(i), 1);
		UTL_AddPinPdsB (tesph, UT_SIG_Y(i), 1);
		UTL_AddPinPdsA (tesph, UT_SIG_D(i), 2);
		UTL_AddPinPdsB (tesph, UT_SIG_D(i), 2);
	}

	if(dutchcnt==2){
		UTL_SendPin(tesph, "iopinlist0" );
		UTL_SendPin(tesph, "iopinlist1" );
	}
	if(dutchcnt==4){
		UTL_SendPin(tesph, SOCKET.dutblock_iopinlist[0] );
		UTL_SendPin(tesph, SOCKET.dutblock_iopinlist[1] );
		UTL_SendPin(tesph, SOCKET.dutblock_iopinlist[2] );
		UTL_SendPin(tesph, SOCKET.dutblock_iopinlist[3] );
	}

    UTL_DeleteHandle(tesph);
}

/*
 * pin_condition
 *   When dr-cp DSA is used (e.g. pincount = 8), DRPINs
 *   are fixed to low level for bad blocks
 *
 */
static void fcsm_pin_condition(USlider dutchcnt)
{
    int i;
    int dutblock;

	PinHandle pin_h;
	pin_h=UTL_GetPinHandle();
	UTL_SetPinOpen  (pin_h,UT_ON);
//	UTL_SendPin     (pin_h, "hmode_pin");
	UTL_SendPin     (pin_h, "IOPIN");
	UTL_DeleteHandle(pin_h);


    PinHandle tesph = UTL_GetPinHandle();

    printf("[DEBUG]%s\n",__func__);

    UTL_SetPinViNumber     (tesph, 1);
    UTL_SetPinDrWaveform   (tesph, UT_WAV_FIXL);
    UTL_SetPinDrClock      (tesph, UT_PIN_BCLK, 1);
    UTL_SetPinDrClock      (tesph, UT_PIN_CCLK, 1);
    UTL_SetPinIoCtrl       (tesph, UT_ON);
    UTL_SetPinVoNumber     (tesph, 1);
    UTL_SetPinVtNumber     (tesph, 1);
    UTL_SetPinTerm         (tesph, UT_ON);
    UTL_SetPinDreNumber    (tesph, 1);
    UTL_SetPinDreWaveform  (tesph, UT_DREWAV_NRZ);
    UTL_SetPinDreClock     (tesph, 1); 
    UTL_AddPinStrbCpeNumber(tesph, 1, 1);
    UTL_AddPinExpStrbNumber(tesph, 1, UT_PIN_EXP_A);  

	UTL_ClearPinPdsA(tesph);
	UTL_ClearPinPdsB(tesph);
	for(i=1; i<=8; i++){
		UTL_AddPinPdsA(tesph, UT_SIG_C(i), 1);
	}
	if(dutchcnt==2){
		UTL_SendPin(tesph, "iopinlist0" );
		UTL_SendPin(tesph, "iopinlist1" );
	}
	if(dutchcnt==4){
		UTL_SendPin(tesph, SOCKET.dutblock_iopinlist[0] );
		UTL_SendPin(tesph, SOCKET.dutblock_iopinlist[1] );
		UTL_SendPin(tesph, SOCKET.dutblock_iopinlist[2] );
		UTL_SendPin(tesph, SOCKET.dutblock_iopinlist[3] );
	}

    UTL_DeleteHandle(tesph);
}

static void flash_pin_condition(RadioButton dutch)
{
	PinHandle pin_h;
	pin_h=UTL_GetPinHandle();
	UTL_SetPinOpen  (pin_h,UT_ON);
	UTL_ClearPinPdsA(pin_h);
	UTL_ClearPinPdsB(pin_h);
	UTL_SendPin     (pin_h, "IOPIN");
	UTL_DeleteHandle(pin_h);
	
	pin_h=UTL_GetPinHandle();
	UTL_InitializePinHandle(pin_h);
	UTL_SetPinViNumber     (pin_h, 1);                 //(handle, vi number)
	UTL_SetPinDrWaveform   (pin_h, UT_WAV_NRZB);
	UTL_SetPinDrClock      (pin_h, UT_PIN_BCLK, 1);	   //(handle, clock type, clock number)
	UTL_AddPinPdsA         (pin_h, UT_SIG_C(3), 1);    //(handle, pin data selector, cycle palette number)
	UTL_SetPinIoCtrl       (pin_h, UT_ON);             //(handle, onoff)
	UTL_SetPinTerm         (pin_h, UT_ON);             //(handle, onoff)
	UTL_SetPinVoNumber     (pin_h, 1);                 //(handle, vo number)
	UTL_SetPinVtNumber     (pin_h, 1);                 //(handle, vt number)
	UTL_SetPinDreNumber    (pin_h, 1);                 //(handle, DRECLOCK Number)
	UTL_SetPinDreWaveform  (pin_h, UT_DREWAV_NRZ);     //(handle, DRE Wave Form)
	UTL_SetPinDreClock     (pin_h, 1);                 //(handle, DREn)
	UTL_AddPinStrbCpeNumber(pin_h, 1, 1);              //(handle, strb number, cpe number)
	UTL_SetPinMatchMode    (pin_h, UT_SIG_MATCH);      //(handle, Selects or deselects the MATCH mode) ***UT_SIG_MATCH:Sets MATCH as the match mode
	UTL_AddPinExpStrbNumber(pin_h, 1, UT_PIN_EXP_FH);  //(handle, strb number, expected value pattern) ***UT_PIN_EXP_FH:Selects FIXH
	UTL_SetPinOpen         (pin_h, UT_OFF);
	
	if(dutch==0){UTL_SendPin(pin_h, "matchpin0");}
	if(dutch==1){UTL_SendPin(pin_h, "matchpin1");}
	if(dutch==2){UTL_SendPin(pin_h, "matchpin2");}
	if(dutch==3){UTL_SendPin(pin_h, "matchpin3");}
	
	UTL_DeleteHandle(pin_h);
}

static void bbm_failselpin(char *pins, RadioButton captdat)
{
    FailSelPinHandle failselpinh;
    UT_PIN  pin=0;
    PinCursor pcr;
    RadioButton target;

    failselpinh = UTL_GetFailSelPinHandle();
    
    switch (captdat) {
        case UT_BBM_ECCTOTALCOUNT(1): target = UT_FAILSELPIN_TARGET_ECC_TOTAL; printf("%s ECC_TOTAL\n",__func__);break;
        case UT_BBM_ECCORCOUNT(1)   : target = UT_FAILSELPIN_TARGET_ECC_OR;    printf("%s ECC_OR   \n",__func__);break;
        defalut                     : printf("%s : Unexpected FAILSELPIN is selected\n"); UTL_Stop();
    }
    UTL_SetFailSelPinTarget(failselpinh, target);
    
    pcr=UTL_GetPinCursor(pins);
    while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
//		printf("  UTL_SetFailSelPin( %2d )\n", pin);
    	UTL_SetFailSelPin(failselpinh, pin, UT_ON);
    }
    UTL_SendFailSelPin (failselpinh);
    UTL_DeleteHandle   (failselpinh);
}

static void FailSelPin_(char *pins, RadioButton captdat)
{
    FailSelPinHandle failselpinh;
    UT_PIN  pin=0;
    PinCursor pcr;
    RadioButton target;
    failselpinh = UTL_GetFailSelPinHandle();
    
    UTL_ClearFailSelPinAssign(failselpinh);
    switch(captdat) {
	case 0  : target = UT_FAILSELPIN_TARGET_ECC_OR;    printf("%s ECC_OR   \n",__func__);break;
        case 1  : target = UT_FAILSELPIN_TARGET_ECC_TOTAL; printf("%s ECC_TOTAL\n",__func__);break;
        defalut : printf("%s : Unexpected FAILSELPIN is selected\n"); UTL_Stop();
    }
    UTL_SetFailSelPinTarget(failselpinh, target);
    
    pcr=UTL_GetPinCursor(pins);
    while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
//		fprintf( stdout, "  UTL_SetFailSelPin( %2d )\n", pin);
    	UTL_SetFailSelPin(failselpinh, pin, UT_ON);
    }
    UTL_SendFailSelPin (failselpinh);
    UTL_DeleteHandle   (failselpinh);
}

static void level_setting(int channel, DSlider high, DSlider low)
{
    DSlider vtl = (high+low)/2;

    ViHandle vih = UTL_GetViHandle();
    UTL_SetViHigh(vih, high   );
    UTL_SetViLow (vih, low    );
    UTL_SendVi   (vih, channel);
    UTL_DeleteHandle(vih);
 
    VoHandle voh = UTL_GetVoHandle();
    UTL_SetVoHigh(voh, vtl);
    UTL_SetVoLow (voh, vtl);
    UTL_SendVo   (voh, channel);
    UTL_DeleteHandle(voh);

    VtHandle vt = UTL_GetVtHandle();
    UTL_SetVt    (vt, vtl);
    UTL_SendVt   (vt, channel);
    UTL_DeleteHandle(vt);
}

static void fcsm_level_setting(int channel, DSlider high, DSlider low)
{
    printf("[DEBUG]%s\n",__func__);
    DSlider vtl = (high+low)/2;

    ViHandle vih = UTL_GetViHandle();
    UTL_SetViHigh(vih, high   );
    UTL_SetViLow (vih, low    );
    UTL_SendVi   (vih, channel);
    UTL_DeleteHandle(vih);

    VoHandle voh = UTL_GetVoHandle();
    UTL_SetVoHigh(voh, vtl);   //This is used as VOH & VOL
    UTL_SetVoLow (voh, vtl);
    UTL_SendVo   (voh, channel);
    UTL_DeleteHandle(voh);

    VtHandle vth = UTL_GetVtHandle();
    UTL_SetVt (vth, 0  );
    UTL_SendVt(vth, channel);
    UTL_DeleteHandle(vth);
}

static void bbm_timing_setting(DSlider tck)
{
    TgHandle tgh = UTL_GetTgHandle();
    UTL_AddTgRate(tgh, 1,    tck);
    UTL_AddTgBclk(tgh, 1, 1, tck*0.25);
	UTL_AddTgCclk(tgh, 1, 1, tck*0.75);
    UTL_AddTgStrb(tgh, 1, 1, tck*0.50);
    UTL_SendTg   (tgh);
    UTL_DeleteHandle(tgh);
}

static void fcsm_timing_setting(DSlider tck)
{
    TgHandle tgh = UTL_GetTgHandle();
    UTL_AddTgRate(tgh, 1,    tck);          UTL_AddTgRate(tgh, 2,    tck);
    UTL_AddTgBclk(tgh, 1, 1, tck);          UTL_AddTgCclk(tgh, 1, 1, tck);
    UTL_AddTgBclk(tgh, 2, 1, tck);          UTL_AddTgCclk(tgh, 2, 1, tck);
    UTL_AddTgDreL(tgh, 1, 1, tck);          UTL_AddTgDreT(tgh, 1, 1, tck);
    UTL_AddTgDreL(tgh, 2, 1, tck);          UTL_AddTgDreT(tgh, 2, 1, tck);
    UTL_AddTgStrb(tgh, 1, 1, tck*0.00);		UTL_AddTgStrb(tgh, 1, 2, tck*0.50);
    UTL_AddTgStrb(tgh, 2, 1, tck*0.50);     UTL_AddTgStrb(tgh, 2, 2, tck*1.00);
    UTL_SendTg   (tgh);
    UTL_DeleteHandle(tgh);
}

static void flash_timing_setting(DSlider tck)
{
    TgHandle tg_h=UTL_GetTgHandle();
    UTL_AddTgRate(tg_h, 1,    tck);
    UTL_AddTgRate(tg_h, 2,    tck);
    UTL_AddTgRate(tg_h, 3,    tck);
    UTL_AddTgBclk(tg_h, 1, 1, tck*0.00);
    UTL_AddTgBclk(tg_h, 2, 1, tck*0.00);
    UTL_AddTgBclk(tg_h, 3, 1, tck*0.00);
    UTL_AddTgStrb(tg_h, 1, 1, tck*0.10);
	UTL_AddTgStrb(tg_h, 2, 1, tck*0.10);
	UTL_AddTgStrb(tg_h, 3, 1, tck*0.10);
    UTL_SendTg(tg_h);
    UTL_DeleteHandle(tg_h);
}

/**
 * @brief Set IDX8 register
 * @param Set "rgidx8" from testarg
*/
static void flash_reg_setting(USlider rgidx8)
{
    RegHandle reg_h=UTL_GetRegHandle();
    UTL_ClearRegHandle(reg_h);
    UTL_SetRegIdx8    (reg_h, 1, rgidx8);  //(handle, block(fixed to 1) ,value)
    UTL_SendReg(reg_h);
    UTL_DeleteHandle(reg_h);
}

/**
 *@brief Select child to be captured into BBM/FCM
 *@param [in] dutgrp RadioButton variable that is equivalent to the target child (0:A1, 1:A2)
 *
 */
static void bbm_fail_capture_select(RadioButton dutgrp)
{
    FailCaptureSelectHandle fcsh;
    printf("%s   dutgrp=%d\n",__func__, dutgrp);
    fcsh = UTL_GetFailCaptureSelectHandle();
    UTL_SetFailCaptureSelectAllDutGroupNumber(fcsh, UT_ON);

    UTL_SendFailCaptureSelect(fcsh);

    UTL_DeleteHandle(fcsh);
}

static void readtname(void)
{
    printf("\nTEST NAME : %s\n", UTL_ReadTestName());	
}

static void MeasFct(TEST_multicharg multicharg, RadioButton pgstop, RadioButton pgclear)
{
    USlider idx1;
    RegHandle regh = UTL_GetRegHandle();
    idx1 = (multicharg.afmxfer_cnt/16)-2;
    UTL_SetRegUs(regh,UT_REG_IDX1,1,idx1);
    UTL_SendReg(regh);
    UTL_DeleteHandle(regh);

    static FctHandle fct = -1;

    if (fct < 0) fct = UTL_GetFctHandle();
    UTL_SetFctMpatName   (fct, multicharg.mpat);
    UTL_SetFctStartPc    (fct, multicharg.pc);         
    UTL_SetFctFailInhibit(fct, pgstop);
    UTL_SetFctNoClear    (fct, pgclear);
	
    UTL_MeasFct(fct);
}

/**
* @brief Get the program counter value and execute MeasFct.
* 
*/
static void fcsm_clear(void)
{
	FcmAccessHandle fcmach = UTL_GetFcmAccessHandle();
	UTL_ResetFcsmStoreCnt();
   	UTL_ResetFcsm		(fcmach);
	UTL_DeleteHandle	(fcmach);
}

static void ecc_set_condition(TEST_multicharg multicharg)
{
    EccConfigHandle eccconfigh = UTL_GetEccConfigHandle();
    UTL_SetEccConfigSectorCount             (eccconfigh, multicharg.sector); //T5835
    if      (CAPTDAT == 0) UTL_SetEccConfigCounterLimit(eccconfigh, UT_ECC_COUNTMODE_OR,    1, multicharg.limit);
    else if (CAPTDAT == 1) UTL_SetEccConfigCounterLimit(eccconfigh, UT_ECC_COUNTMODE_TOTAL, 1, multicharg.limit);
	UTL_SetEccConfigCounterEnableSignal     (eccconfigh, 0, UT_SIG_C(31));
	UTL_SetEccConfigSectorSwitchSignal      (eccconfigh,    UT_SIG_C(20));
	UTL_SetEccConfigCounterClearSignal      (eccconfigh,    UT_SIG_C(19));
	UTL_SetEccConfigJudgeSignal             (eccconfigh, 0, UT_SIG_C(18));
    UTL_SendEccConfig                       (eccconfigh);
    UTL_DeleteHandle                        (eccconfigh);

}

static void fcsm_set_condition(TEST_multicharg multicharg)
{
	if(CAPTDAT==0)printf("ECC MODE: OR MODE\n");fflush(stdout);
	if(CAPTDAT==1)printf("ECC MODE: TOTAL MODE\n");fflush(stdout);
	printf("multicharg.dutch:%d\n",multicharg.dutch);fflush(stdout);

    FailCaptureSelectHandle fcsh = UTL_GetFailCaptureSelectHandle();
    UTL_SetFailCaptureSelectAllDutGroupNumber	(fcsh,UT_ON );
    UTL_SetFailCaptureSelectAllPin				(fcsh,UT_OFF);
	if(multicharg.dutchcnt==2){
		if(multicharg.dutch==0){UTL_SetFailCaptureSelectPinList (fcsh, "iopinlist0");}
		if(multicharg.dutch==1){UTL_SetFailCaptureSelectPinList (fcsh, "iopinlist1");}
	}
	if(multicharg.dutchcnt==4){
		UTL_SetFailCaptureSelectPinList			(fcsh,SOCKET.dutblock_iopinlist[multicharg.dutch]);
	}
    UTL_SendFailCaptureSelect					(fcsh);
    UTL_DeleteHandle(fcsh);

	if(multicharg.dutchcnt==2){
		if(multicharg.dutch==0){FailSelPin_("iopinlist0", CAPTDAT);}
		if(multicharg.dutch==1){FailSelPin_("iopinlist1", CAPTDAT);}
	}
	if(multicharg.dutchcnt==4){
		FailSelPin_(SOCKET.dutblock_iopinlist[multicharg.dutch], CAPTDAT);
	}

    FcmConfigHandle fcmconfigh = UTL_GetFcmConfigHandle();
    UTL_SetFcmConfigDelay	                (fcmconfigh , 0);
    UTL_SetFcmConfigFcsmMaxStoreCnt             (fcmconfigh, multicharg.afmxfer_cnt);
    if(CAPTDAT==0)UTL_AddFcmConfigAction	(fcmconfigh , 1 , UT_FCM_ECCCOUNT_OR_TO_FCSM );
    if(CAPTDAT==1)UTL_AddFcmConfigAction	(fcmconfigh , 1 , UT_FCM_ECCCOUNT_TOTAL_TO_FCSM );
    UTL_SendFcmConfig		                (fcmconfigh);
    UTL_DeleteHandle                            (fcmconfigh);
}

static void readfcsm(TEST_multicharg multicharg)
{
	printf("Sector:%d\n",multicharg.sector);
	printf("Afmxfer Count:%X\n",multicharg.afmxfer_cnt);
	printf("Ecc Limit:%d\n",multicharg.limit);fflush(stdout);
	
	USlider dut_res[MAXDUTCNT]={0};
	USlider store_cnt;
	USlider size1=0;
	USlider size2=0;
	USlider *fcsm_data;
	USlider *exp_data1,*exp_data2;    //data1:odd dut,data2:even dut
	USlider rdata;
	DutCursor dutcur;
	UT_DUT dut;
	int sec;
	int afmx_cnt;
	int data_cnt=16;
	int i;
	size1 = (multicharg.afmxfer_cnt * multicharg.sector * MAXDUTCNT)*sizeof(USlider);
	size2 = sizeof(USlider) * (multicharg.afmxfer_cnt * multicharg.sector );
	fcsm_data = (USlider *)malloc(size1);
	exp_data1 = (USlider *)calloc(size2, sizeof(USlider));
	exp_data2 = (USlider *)calloc(size2, sizeof(USlider));
	int cnt_ex=0;
	cnt_ex= 0 <<  CAPTDAT |CAPTDAT;
	
	for(afmx_cnt=0;afmx_cnt<multicharg.afmxfer_cnt;afmx_cnt++){
		if(afmx_cnt==data_cnt){break;}
		for(sec=0;sec<multicharg.sector;sec++){
			exp_data1[(multicharg.sector*afmx_cnt)+sec]=(cnt_ex+1)*(afmx_cnt*data_cnt+(sec+1));
			exp_data2[(multicharg.sector*afmx_cnt)+sec]=(cnt_ex+1)*(256-(afmx_cnt*data_cnt+sec));
			if(exp_data1[(multicharg.sector*afmx_cnt)+sec]>=256){
				exp_data1[(multicharg.sector*afmx_cnt)+sec]=256 | 0x300;
			}
			else if(exp_data1[(multicharg.sector*afmx_cnt)+sec]>=multicharg.limit){
				exp_data1[(multicharg.sector*afmx_cnt)+sec]=(cnt_ex+1)*(afmx_cnt*data_cnt+(sec+1)) | 0x100;
			}
			if(exp_data2[(multicharg.sector*afmx_cnt)+sec]>=256){
				exp_data2[(multicharg.sector*afmx_cnt)+sec]=256 | 0x300;
			}
			else if(exp_data2[(multicharg.sector*afmx_cnt)+sec]>=multicharg.limit){
				exp_data2[(multicharg.sector*afmx_cnt)+sec]=(cnt_ex+1)*((256-(afmx_cnt*data_cnt+sec))) | 0x100;
			}
		}
	}
	
	FcmAccessHandle fcmach = UTL_GetFcmAccessHandle();
	UTL_SetFcmAccessAllDut	(fcmach, UT_ON );
	UTL_SetFcmAccessBitMode (fcmach,UT_FCM_BITMODE_NORMAL);
	UTL_SetFcmAccessAllBit  (fcmach,UT_ON);
	
	UTL_ReadFcsmStoreCnt	(fcmach, &store_cnt);
	printf("***Store Count : %X *******\n",store_cnt);fflush(stdout);
	UTL_ReadFcsm		    (fcmach,fcsm_data,size1);

	dutcur = UTL_GetDutCursor(UT_CDUT);
	while((dut= UTL_NextDut(dutcur)) != UT_NOMORE){
		for(afmx_cnt=0;afmx_cnt<store_cnt;afmx_cnt++){
			for(sec=0;sec<multicharg.sector;sec++){
				rdata=fcsm_data[(multicharg.sector*store_cnt)*(dut-1)+(multicharg.sector*afmx_cnt)+sec];
				if(DEBUG){
					printf("DUT:%d,AFMXFER COUNT:%d,multicharg.sector:%d : %d ",dut,afmx_cnt,sec,rdata);fflush(stdout);
					if     ((rdata&0x300)==0x300){printf("***Overflow,Limit Over");}
					else if((rdata&0x200)==0x200){printf("***Overflow");}
					else if((rdata&0x100)==0x100){printf("***Limit Over");}
					printf("\n");fflush(stdout);
				}
				if(multicharg.afmxfer_cnt<=0x1000){
					if(dut%2==1){
						if(rdata!=exp_data1[(multicharg.sector*(afmx_cnt%data_cnt))+sec]){
							if(DEBUG){printf("**DUT:%d,AFMXFER COUNT:%d,multicharg.sector:%d : %d **FAIL\n",dut,afmx_cnt,sec,exp_data1[(multicharg.sector*(afmx_cnt%data_cnt))+sec]);fflush(stdout);}
							dut_res[dut-1]=1;
						}
					}else if(dut%2==0){
						if(rdata!=exp_data2[(multicharg.sector*(afmx_cnt%data_cnt))+sec]){
							if(DEBUG){printf("**DUT:%d,AFMXFER COUNT:%d,multicharg.sector:%d : %d **FAIL\n",dut,afmx_cnt,sec,exp_data2[(multicharg.sector*(afmx_cnt%data_cnt))+sec]);fflush(stdout);}
							dut_res[dut-1]=1;
						}
					}
				}
				else if(multicharg.afmxfer_cnt>0x1000){
					if(rdata!=exp_data1[(multicharg.sector*(afmx_cnt%data_cnt))+sec]){
						if(DEBUG){printf("**DUT:%d,AFMXFER COUNT:%d,multicharg.sector:%d : %d **FAIL\n",dut,afmx_cnt,sec,exp_data1[(multicharg.sector*(afmx_cnt%data_cnt))+sec]);fflush(stdout);}
						dut_res[dut-1]=1;
					}
				}
			}
		}
	}
	free(fcsm_data);
	multich_JudgeEccFcsm(dut_res);
}

static void set_ubm_data(TEST_multicharg multicharg)
{
	UbmConfigHandle useth = UTL_GetUbmConfigHandle();
	UTL_InitializeUbmConfigHandle  (useth);
	UTL_ClearUbmConfigFunctionSelect(useth);
	UTL_ClearUbmConfigPin(useth, UT_UBM_UNIT_EXP);
	UTL_ClearUbmConfigJumpAddr(useth, UT_UBM_UNIT_EXP, 0x0);
	
	UTL_AddUbmConfigFunctionSelect(useth, UT_UBM_UNIT_EXP, UT_SIG_C(25));
	
	if(multicharg.dutchcnt==2){
		if(multicharg.dutch==0){UTL_SetUbmConfigPin(useth, UT_UBM_UNIT_EXP, "iopinlist0");}
		if(multicharg.dutch==1){UTL_SetUbmConfigPin(useth, UT_UBM_UNIT_EXP, "iopinlist1");}
	}
	if(multicharg.dutchcnt==4){
		UTL_SetUbmConfigPin(useth, UT_UBM_UNIT_EXP, SOCKET.dutblock_iopinlist[multicharg.dutch]);
	}
	UTL_SetUbmConfigJumpAddr (useth, UT_UBM_UNIT_EXP, 0, 0x0);
	UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_EXP, 0, UT_SIG_C(26));
	
	UTL_SetUbmConfigPmMode(useth, UT_UBM_UNIT_EXP);
	UTL_SetUbmConfigDdrMode(useth, UT_OFF);		//SDR
	
	UTL_SetUbmConfigApAutoIncMode(useth, UT_OFF);
	UTL_SetUbmConfigApIncCycle(useth, UT_SIG_C(27));
	UTL_SetUbmConfigApAllCycleIncMode(useth, UT_OFF);
	
	UTL_SendUbmConfig(useth);
	UTL_DeleteHandle(useth);
	
	return;
}

/**
 * @brief Set UBM conditions
*/
static void bbm_set_ubm_data(void)
{
    UbmConfigHandle uc_h=UTL_GetUbmConfigHandle();
    UTL_InitializeUbmConfigHandle   (uc_h);
    UTL_ClearUbmConfigFunctionSelect(uc_h);
    UTL_ClearUbmConfigPin           (uc_h, UT_UBM_UNIT_PM);                         //(handle, UBM function specify) ***UT_UBM_UNIT_PM:Generates a pattern
    UTL_ClearUbmConfigJumpAddr      (uc_h, UT_UBM_UNIT_PM, 0);                      //(handle, UBM function specify, jump address index number)
    UTL_ClearUbmConfigStrbChannel   (uc_h);

    UTL_AddUbmConfigFunctionSelect  (uc_h, UT_UBM_UNIT_PM, UT_SIGNAL_C(22));        //(handle, UBM function specify, enable cycle)
    UTL_SetUbmConfigPin             (uc_h, UT_UBM_UNIT_PM, "IOPIN");            //(handle, UBM function specify, pinlist)
    UTL_SetUbmConfigJumpAddr        (uc_h, UT_UBM_UNIT_PM, 0 , 0x0);                //(handle, UBM function specify, jump address index number, jump address)
    UTL_SetUbmConfigJumpCycle       (uc_h, UT_UBM_UNIT_PM, 0 , UT_SIGNAL_C(24));    //(handle, UBM function specify, jump address index number, jump cycle)
	UTL_SetUbmConfigPmMode          (uc_h, UT_UBM_MODE_DRPAT);                      //(handle, pmmode) ***UT_UBM_MODE_DRPAT:Uses the universal buffer memory pattern data as the driver waveform pattern
    UTL_SetUbmConfigDdrMode         (uc_h, UT_OFF);                                 //(handle, ddr setting) ***UT_OFF:Cancel
    UTL_SetUbmConfigApAutoIncMode   (uc_h, UT_ON);                                  //(handle, auto inc mode) ***UT_ON:Increments the address pointer
    UTL_SendUbmConfig(uc_h);
    UTL_DeleteHandle(uc_h);
}


/**
 * @brief Set UBM conditions
*/
static void flash_set_ubm_data(void)
{
    UbmConfigHandle uc_h=UTL_GetUbmConfigHandle();
    UTL_InitializeUbmConfigHandle   (uc_h);
    UTL_ClearUbmConfigFunctionSelect(uc_h);
    UTL_ClearUbmConfigPin           (uc_h, UT_UBM_UNIT_PM);                         //(handle, UBM function specify) ***UT_UBM_UNIT_PM:Generates a pattern
    UTL_ClearUbmConfigJumpAddr      (uc_h, UT_UBM_UNIT_PM, 0);                      //(handle, UBM function specify, jump address index number)
    UTL_ClearUbmConfigStrbChannel   (uc_h);

    UTL_AddUbmConfigFunctionSelect  (uc_h, UT_UBM_UNIT_PM, UT_SIGNAL_C(22));        //(handle, UBM function specify, enable cycle)
    UTL_SetUbmConfigPin             (uc_h, UT_UBM_UNIT_PM, "matchpin_all");            //(handle, UBM function specify, pinlist)
    UTL_SetUbmConfigJumpAddr        (uc_h, UT_UBM_UNIT_PM, 0 , 0x0);                //(handle, UBM function specify, jump address index number, jump address)
    UTL_SetUbmConfigJumpCycle       (uc_h, UT_UBM_UNIT_PM, 0 , UT_SIGNAL_C(24));    //(handle, UBM function specify, jump address index number, jump cycle)
	UTL_SetUbmConfigPmMode          (uc_h, UT_UBM_MODE_DRPAT);                      //(handle, pmmode) ***UT_UBM_MODE_DRPAT:Uses the universal buffer memory pattern data as the driver waveform pattern
    UTL_SetUbmConfigDdrMode         (uc_h, UT_OFF);                                 //(handle, ddr setting) ***UT_OFF:Cancel
    UTL_SetUbmConfigApAutoIncMode   (uc_h, UT_ON);                                  //(handle, auto inc mode) ***UT_ON:Increments the address pointer
    UTL_SendUbmConfig(uc_h);
    UTL_DeleteHandle(uc_h);
}

static void ubm_preset(USlider n)
{
	UbmAccessHandle uacsh = UTL_GetUbmAccessHandle();
	UTL_ClearUbmAccessPin(uacsh);
	UTL_PresetUbm(uacsh, n);
	UTL_DeleteHandle(uacsh);
	return;
}

#define UBMSIZE 0x20000

static void write_ubm_evenodd(TEST_multicharg multicharg)
{
	int i, j,k;
	RadioButton dutblock;
	UT_DUT dut;
	UT_DUT dutmax;
	DutCursor dutc;
	USlider *wdata;
	USlider size;
	int sec_cnt=0;
	int afm_cnt=0;
	int dut_area=0;
	static fail_cnt=256;

	dutmax = 0;
	dutc = UTL_GetDutCursor(UT_CDUT);
	while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
	dutmax++;
	}
	UTL_DeleteCursor(dutc);
	
	size = UBMSIZE*dutmax*sizeof(USlider);
	wdata = (USlider *)malloc(size);
	memset(wdata, 0x0, size);
	
	printf("dutmax:%d\n",dutmax);
	for(dut=1;dut<=dutmax;dut++){
		for(j=0; j<UBMSIZE; j++){
			if(dut%2==1){
				if(j%2==1){
					if(CAPTDAT==1){
                                           if(j%4==0)wdata[(dut-1)*UBMSIZE+j]=0x6;
                                           if(j%4==1)wdata[(dut-1)*UBMSIZE+j]=0xC;
                                           if(j%4==2)wdata[(dut-1)*UBMSIZE+j]=0x9;
                                           if(j%4==3)wdata[(dut-1)*UBMSIZE+j]=0x5;
					}else{
                                           if(j%16==0){wdata[(dut-1)*UBMSIZE+j]=0xF;}
                                           else{wdata[(dut-1)*UBMSIZE+j]=j%16;}
					}
				}
			}
			else if(dut%2==0){
				if(j%2==0){
					if(CAPTDAT==1){
                                           if(j%4==0)wdata[(dut-1)*UBMSIZE+j]=0x6;
                                           if(j%4==1)wdata[(dut-1)*UBMSIZE+j]=0xC;
                                           if(j%4==2)wdata[(dut-1)*UBMSIZE+j]=0x9;
                                           if(j%4==3)wdata[(dut-1)*UBMSIZE+j]=0x5;
					}else{
                                           if(j%16==0){wdata[(dut-1)*UBMSIZE+j]=0xF;}
                                           else{wdata[(dut-1)*UBMSIZE+j]=j%16;}
					}
				}
			}
		}
	}

	ubm_preset(0);
	
	UbmAccessHandle uacsh = UTL_GetUbmAccessHandle();
	UTL_SetUbmAccessBitReverse(uacsh, UT_ON);
	UTL_SetUbmAccessStartAddr(uacsh, 0x0);
	UTL_SetUbmAccessStopAddr (uacsh, UBMSIZE-1);
	UTL_SetUbmAccessDdrMode(uacsh, UT_OFF);		//SDR

	dutc = UTL_GetDutCursor(UT_CDUT);
	UTL_ClearUbmAccessPin(uacsh);
	if(multicharg.dutchcnt==2){
		if(multicharg.dutch==0){UTL_SetUbmAccessPin(uacsh, "iopinlist0");}
		if(multicharg.dutch==1){UTL_SetUbmAccessPin(uacsh, "iopinlist1");}
	}
	if(multicharg.dutchcnt==4){
		UTL_SetUbmAccessPin(uacsh, SOCKET.dutblock_iopinlist[multicharg.dutch]);
	}
	if(multicharg.dutch==0 && multicharg.funblk==1){UTL_SetUbmAccessPinBlock(uacsh, 1);}	//P1-8
	if(multicharg.dutch==1 && multicharg.funblk==1){UTL_SetUbmAccessPinBlock(uacsh, 1);}	//P9-16
	if(multicharg.dutch==1 && multicharg.funblk==2){UTL_SetUbmAccessPinBlock(uacsh, 3);}	//P65-72
	if(multicharg.dutch==2 && multicharg.funblk==3){UTL_SetUbmAccessPinBlock(uacsh, 5);}	//P129-135
	if(multicharg.dutch==3 && multicharg.funblk==4){UTL_SetUbmAccessPinBlock(uacsh, 7);}	//P193-200
	UTL_WriteUbmAllDut(uacsh, dutmax, wdata, size);
	
	free(wdata);
	UTL_DeleteHandle(uacsh);
	
	return;
}

static void bbm_write_ubm_data(TEST_multicharg multicharg)
{
    int i;
    int wdata[ubmcnt]={0,};
    unsigned int size=0;
    size=sizeof(wdata);

    DutCursor dutc;
	UT_DUT dut;

    UbmAccessHandle ua_h=UTL_GetUbmAccessHandle();
    UTL_ClearUbmAccessPin     (ua_h );
    UTL_PresetUbm             (ua_h, 0);         //(handle, preset at 0)

	if(multicharg.dutchcnt==2){
		if(multicharg.dutch==0){UTL_SetUbmAccessPin(ua_h, "iopinlist0");}
		if(multicharg.dutch==1){UTL_SetUbmAccessPin(ua_h, "iopinlist1");}
	}
	if(multicharg.dutchcnt==4){
		UTL_SetUbmAccessPin(ua_h, SOCKET.dutblock_iopinlist[multicharg.dutch]);
	}
	if(multicharg.dutch==0 && multicharg.funblk==1){UTL_SetUbmAccessPinBlock(ua_h, 1);}	//P1-8
	if(multicharg.dutch==1 && multicharg.funblk==1){UTL_SetUbmAccessPinBlock(ua_h, 1);}	//P9-16
	if(multicharg.dutch==1 && multicharg.funblk==2){UTL_SetUbmAccessPinBlock(ua_h, 3);}	//P65-72
	if(multicharg.dutch==2 && multicharg.funblk==3){UTL_SetUbmAccessPinBlock(ua_h, 5);}	//P129-135
	if(multicharg.dutch==3 && multicharg.funblk==4){UTL_SetUbmAccessPinBlock(ua_h, 7);}	//P193-200
    UTL_SetUbmAccessStartAddr (ua_h, 0x0);           //(handle, access start address)
    UTL_SetUbmAccessDdrMode   (ua_h, UT_OFF);        //(handle, ddr mode setting) ***UT_OFF:Cancel
    UTL_SetUbmAccessStopAddr  (ua_h, ubmcnt-1);      //(handle, access end address)
    UTL_SetUbmAccessBitReverse(ua_h, UT_ON);         //(handle, bit inversion) ***UT_ON:Performs bit inversion of data.

    dutc=UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
		for(i=0; i<ubmcnt; i++){
			if(dut%2==0 && i%2==0){wdata[i]=0x33;}
			if(dut%2==0 && i%2==1){wdata[i]=0xcc;}
			if(dut%2==1 && i%2==0){wdata[i]=0x55;}
			if(dut%2==1 && i%2==1){wdata[i]=0xaa;}
		}
        UTL_SetUbmAccessDut(ua_h, dut);          //(handle, UBM access dut)
        UTL_WriteUbm(ua_h, wdata, size);
    }UTL_DeleteCursor(dutc);
    UTL_DeleteHandle(ua_h);
}

/**
 * @brief Set UBM write data
 * @param Set "ilmd" from testarg
 * @param Set "ubmno" from testarg
*/
static void flash_write_ubm_data(TEST_multicharg multicharg)
{
    int idx1;
    int wdata1[ubmcnt]={0,};
    int wdata2[ubmcnt]={0,};
    int wdata3[ubmcnt]={0,};
    int wdata4[ubmcnt]={0,};

    unsigned int size1=0;
    unsigned int size2=0;
    unsigned int size3=0;
    unsigned int size4=0;

    size1=sizeof(wdata1);
    size2=sizeof(wdata2);
    size3=sizeof(wdata3);
    size4=sizeof(wdata4);

    /*UBM write data setting description
    UTL_SetUbmAccessBitReverse(ua_h, UT_ON);
              33222222222211111111110000000000
              10987654321098765432109876543210
	wdata1 =  ----------------------------PPPP
                                          DDDD
                                          4321
    */

	if(multicharg.ubmno==1){
		for(idx1=0; idx1<ubmcnt; idx1++){
			if(idx1>=30*multicharg.ilmode){wdata1[idx1]=wdata1[idx1] | 0xf;}  //DUT1 P1

			if(idx1>=35*multicharg.ilmode){wdata2[idx1]=wdata2[idx1] | 0xf;}  //DUT2 P65

			if(idx1>=40*multicharg.ilmode){wdata3[idx1]=wdata3[idx1] | 0xf;}  //DUT3 P129

			if(idx1>=45*multicharg.ilmode){wdata4[idx1]=wdata4[idx1] | 0xf;}  //DUT4 P193
		}
	}
	if(multicharg.ubmno==2){
		for(idx1=0; idx1<ubmcnt; idx1++){
			if(idx1>=30*multicharg.ilmode){wdata1[idx1]=wdata1[idx1] | 0x1;}  //DUT1 P1
			if(idx1>=10*multicharg.ilmode){wdata1[idx1]=wdata1[idx1] | 0xe;}  //DUT1 P65,129,193

			if(idx1>=35*multicharg.ilmode){wdata2[idx1]=wdata2[idx1] | 0x2;}  //DUT2 P65
			if(idx1>=10*multicharg.ilmode){wdata2[idx1]=wdata2[idx1] | 0xd;}  //DUT2 P1,129,193

			if(idx1>=40*multicharg.ilmode){wdata3[idx1]=wdata3[idx1] | 0x4;}  //DUT3 P129
			if(idx1>=10*multicharg.ilmode){wdata3[idx1]=wdata3[idx1] | 0xb;}  //DUT3 P1,65,193

			if(idx1>=45*multicharg.ilmode){wdata4[idx1]=wdata4[idx1] | 0x8;}  //DUT4 P193
			if(idx1>=10*multicharg.ilmode){wdata4[idx1]=wdata4[idx1] | 0x7;}  //DUT4 P1,54,129
		}
	}

    DutCursor dutc;
	UT_DUT dut;

    UbmAccessHandle ua_h=UTL_GetUbmAccessHandle();
    UTL_ClearUbmAccessPin     (ua_h );
    UTL_PresetUbm             (ua_h, 0);         //(handle, preset at 0)

    UTL_SetUbmAccessPin       (ua_h, "matchpin_all");   //(handle, pinlist) 
//    UTL_SetUbmAccessPinBlock  (ua_h, 1);             //(handle, pin block number) ***1:P1 to P18
	if(multicharg.dutch==0 && multicharg.funblk==1){UTL_SetUbmAccessPinBlock(ua_h, 1);}	//P1-8
	if(multicharg.dutch==1 && multicharg.funblk==1){UTL_SetUbmAccessPinBlock(ua_h, 1);}	//P9-16
	if(multicharg.dutch==1 && multicharg.funblk==2){UTL_SetUbmAccessPinBlock(ua_h, 3);}	//P65-72
	if(multicharg.dutch==2 && multicharg.funblk==3){UTL_SetUbmAccessPinBlock(ua_h, 5);}	//P129-135
	if(multicharg.dutch==3 && multicharg.funblk==4){UTL_SetUbmAccessPinBlock(ua_h, 7);}	//P193-200
    UTL_SetUbmAccessStartAddr (ua_h, 0x0);           //(handle, access start address)
    UTL_SetUbmAccessDdrMode   (ua_h, UT_OFF);        //(handle, ddr mode setting) ***UT_OFF:Cancel
    UTL_SetUbmAccessStopAddr  (ua_h, ubmcnt-1);      //(handle, access end address)
    UTL_SetUbmAccessBitReverse(ua_h, UT_ON);         //(handle, bit inversion) ***UT_ON:Performs bit inversion of data.

    dutc=UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
        UTL_SetUbmAccessDut(ua_h, dut);          //(handle, UBM access dut)
        if(dut==1){UTL_WriteUbm(ua_h, wdata1, size1);}
        if(dut==2){UTL_WriteUbm(ua_h, wdata2, size2);}
        if(dut==3){UTL_WriteUbm(ua_h, wdata3, size3);}
        if(dut==4){UTL_WriteUbm(ua_h, wdata4, size4);}
    }UTL_DeleteCursor(dutc);
    UTL_DeleteHandle(ua_h);
}

static void test_result(char tname[])
{
    RadioButton dut_test_res[MAXDUTCNT]={0,};
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

static void bbm_init(USlider ilmode, USlider dutchcnt)
{
    ilmode_setting(ilmode);
//    pin_list(dutchcnt);
    power_seq();
    bbm_pin_condition(dutchcnt);
    level_setting(1, 1.00 V, 0.00 V);    // (channel, Vi high, Vi low)
}

static void fcsm_init(USlider ilmode, USlider dutchcnt)
{
    ilmode_setting(ilmode);
//    pin_list(dutchcnt);
    power_seq();
    fcsm_pin_condition(dutchcnt);
    fcsm_level_setting(1, 1.00 V, 0.00 V);    // (channel, Vi high, Vi low)
}

static void flash_init(USlider ilmode, RadioButton dutch)
{
    ilmode_setting(ilmode);
//	pin_list();
//	flash_dutch_setting();
    power_seq();
    flash_pin_condition(dutch);
    level_setting(1, 1.00 V, 0.00 V);    // (channel, Vi high, Vi low)
}

//
// ***temporary setting : R1.01 Beta1 need BbmConfig setting for switch Ecc Count TOTAL/OR mode.
//
//#define BBM_XBIT	18									//x bit count
//#define BBM_YBIT	0									//y bit count
static void bbm_set_condition_capture(int bbm_ybit, int bbm_xbit)
{
    BbmConfigHandle	bbmconfigh;
    int i;
    
    bbmconfigh = UTL_GetBbmConfigHandle();

    for (i=0; i<bbm_ybit; i++) UTL_SetBbmConfigAddrAssign(bbmconfigh, i, UT_SIG_Y(i));
    for (i=0; i<bbm_xbit; i++) UTL_SetBbmConfigAddrAssign(bbmconfigh, i+bbm_ybit, UT_SIG_X(i));
    UTL_SetBbmConfigMode                    (bbmconfigh, UT_BBM_DATACAPTURE);
    UTL_SetBbmConfigAction                  (bbmconfigh, UT_BBM_MASKINH);
    UTL_SetBbmConfigStoreMode               (bbmconfigh, UT_BBM_SELECTEDDATA);
    UTL_SetBbmConfigDataGenerationMode      (bbmconfigh, UT_BBM_DISABLE);
    UTL_SetBbmConfigWriteEnableAllDut       (bbmconfigh, UT_ON);
/// by my, 18/june/2022    UTL_AddBbmConfigCaptureDataByTargetBank (bbmconfigh, 0, 1, 0, UT_BBM_ECCORCOUNT(1));
    UTL_AddBbmConfigCaptureDataByTargetBank (bbmconfigh, 0, 1, 0, UT_BBM_ECCTOTALCOUNT(1));
    UTL_SetBbmConfigCounterNoClear          (bbmconfigh, UT_BBM_COUNTER_BBC, UT_OFF);
    UTL_SendBbmConfig                       (bbmconfigh);
    UTL_DeleteHandle                        (bbmconfigh);
}

static void bbm_read_address(TEST_multicharg multicharg, int disp_data)
{
    int i,j;
    DutCursor dutc;
    UT_DUT dut;
    
    BbmAccessHandle ba_h =  UTL_GetBbmAccessHandle();
    UTL_SetBbmAccessAllDut      (ba_h, UT_OFF);
    UTL_SetBbmAccessStartAddr   (ba_h, 0);
    UTL_SetBbmAccessStopAddr    (ba_h, BBM_SIZE-1);
    UTL_SetBbmAccessAllBit      (ba_h, UT_ON);
    UTL_SetBbmAccessCounterMode (ba_h, UT_BBM_COUNTERMODE_REALTIME_SELECTEDBIT); //By default

	dutc = UTL_GetDutCursor(UT_SDUT);
	while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
		if ((capdutgrp[multicharg.dutgrp] & (1 << (dut-1))) == 0)  continue;
		printf("  --- DUT-%2d ---\n", dut);

///////
		printf("Dut Channel =%d\n", multicharg.dutch);
		UTL_SetBbmAccessChannel (ba_h, multicharg.dutch);
///////
		UTL_SetBbmAccessDut     (ba_h, dut);
		UTL_ReadBbm             (ba_h, multich_bb_addr[dut-1], sizeof(multich_bb_addr[dut-1]));
///////
		RadioButton	status;
		multich_bbc[dut-1] = UTL_ReadBadBlockCounter(ba_h, &status);
#if 1
		switch (status) {
			case UT_BBM_LIMITOVER : puts("BBM LIMITOVER\n"); break;
			case UT_BBM_OVERFLOW  : puts("BBM OVERFLOW\n");  break;
			case UT_BBM_COMPLETE  : puts("BBM COMPLETE\n");  break;
			default: puts("UNEXPECTED STATUS UTL_ReadBadBlockCounter"); UTL_Stop();
		}
#endif
		printf("BBC : %6d\n\n", multich_bbc[dut-1]);fflush(stdout);
//////
#if 1
		for (i=0; i<BBM_SIZE; i++) {
			if (multich_bb_addr[dut-1][i] == disp_data) printf("DUT%2d ( %6d ):0x%02X\n", dut, i, multich_bb_addr[dut-1][i]);
		}
		puts("");
#endif
//////
	}
	UTL_DeleteCursor (dutc);
    UTL_DeleteHandle (ba_h);
}

/**
* @brief write 0 to whole BBM. This routine needs executing before MeasFct.
*/
static void bbm_clear()
{
    BbmAccessHandle	bbmaccessh;
    bbmaccessh = UTL_GetBbmAccessHandle();
    UTL_SetBbmAccessPresetAllMemory (bbmaccessh, UT_ON);
    UTL_PresetBbm                   (bbmaccessh, 0);
    UTL_DeleteHandle                (bbmaccessh);
}

static void bbm_disable()
{
	BbmConfigHandle	bbmconfigh;
	bbmconfigh = UTL_GetBbmConfigHandle();
	UTL_UpdateBbmConfig    (bbmconfigh);
	UTL_SetBbmConfigMode   (bbmconfigh, UT_BBM_DISABLE);
	UTL_SendBbmConfig      (bbmconfigh);
	UTL_DeleteHandle       (bbmconfigh);
}

//#define FLASHMODE "MAXFAIL"
//#define HOLDMODE  "MATCH"

/**
 * @brief Set the flash conditions
 * @param Set "fmode" from testarg
 * @param Set "hmode" from testarg
*/
static void flash_setting(TEST_multicharg multicharg)
{
    FlashHandle flash_h=UTL_GetFlashHandle();

    UTL_SetFlashLimitAllDut(flash_h, multicharg.limit);  //(handle, limit value for the flash counter)

//    UTL_SetFlashCpInhPinMode(flash_h, UT_ON);
//    UTL_SetFlashCpInhPin(flash_h,"matchpin_all");


	if     (strcmp(FLASHMODE, "MAXFAIL")==0){UTL_SetFlashModeAllDut(flash_h, UT_FLASH_MAXFAIL);}    //(handle, operating mode)
	else if(strcmp(FLASHMODE, "ORFAIL" )==0){UTL_SetFlashModeAllDut(flash_h, UT_FLASH_ORFAIL);}     //(handle, operating mode)
	else if(strcmp(FLASHMODE, "DISABLE")==0){UTL_SetFlashModeAllDut(flash_h, UT_FLASH_DISABLE);}    //(handle, operating mode)
	else{printf("\n***** flash mode is not specify *****\n");fflush(stdout);}

	if     (strcmp(HOLDMODE, "MATCH") ==0){UTL_SetFlashHoldModeAllDut(flash_h, UT_FLASH_MATCH);}   //(handle, hold mode)
	else if(strcmp(HOLDMODE, "STACK") ==0){UTL_SetFlashHoldModeAllDut(flash_h, UT_FLASH_STACK);}   //(handle, hold mode)
	else if(strcmp(HOLDMODE, "MATCH2")==0){UTL_SetFlashHoldModeAllDut(flash_h, UT_FLASH_MATCH2);}  //(handle, hold mode)
	else if(strcmp(HOLDMODE, "STACK2")==0){UTL_SetFlashHoldModeAllDut(flash_h, UT_FLASH_STACK2);}  //(handle, hold mode)
	else{printf("\n***** hold mode is not specify *****\n");fflush(stdout);}

	UTL_SetFlashHoldConditionAllDut   (flash_h, UT_SIG_C(25), UT_SIG_C(26)); //(handle, load, clear)
	UTL_SetFlashCounterConditionAllDut(flash_h, UT_SIG_C(27), UT_SIG_C(28)); //(handle, increment, clear)

    UTL_SendFlash(flash_h);
    UTL_DeleteHandle(flash_h);
}

/*
 * ecc_SSs_N[]
 *   SS: # of sectors 
 *   N: ECC(total) or ECC(or)
 */
int multich_ecc_16s_0[] = {  10,  23,  45};
int multich_ecc_16s_2[] = {   5,  44};

static void judge_ecc(TEST_multicharg multicharg)
{
   int i, j, ng;
   int efcnt = 0;      //expected fail count
   int *bb;            //bad block address
   UT_DUT dut;
   char *testname = UTL_ReadTestName();

   if(multicharg.pc == 0){ bb = multich_ecc_16s_0; efcnt = sizeof(multich_ecc_16s_0)/sizeof(int);}
   else                  { bb = multich_ecc_16s_2; efcnt = sizeof(multich_ecc_16s_2)/sizeof(int);}

// printf("[DEBUG]pattern =%s  efcnt = %d \n", bbmarg.mpat, efcnt);

   DutCursor dutc = UTL_GetDutCursor(UT_SDUT);
   while ((dut = UTL_NextDut(dutc))!=UT_NOMORE) {
       if ((capdutgrp[multicharg.dutgrp] & (1 << (dut-1))) == 0) {
           UTL_ResetTestResult(dut, testname, UT_RES_ALL);
           continue;
       }
       ng = 0;
       if(multich_bbc[dut-1] != efcnt) {
          printf("DUT[%2d] BBC(%9d) EXP(%9d)\n", dut, multich_bbc[dut-1], efcnt);
          ng = 1;
       }
       for (i=0; i<BBM_SIZE; i++) {
          if (multich_bb_addr[dut-1][i]) {
             for(j=0; j<efcnt; j++) {
                if (i == bb[j]) {
//                 printf("[DEBUG] DUT(%2d) BBM(%9d)=#%08x is correct\n",dut, i, multich_bb_addr[dut-1][i]);
                   break;
                }
                if (i <  bb[j]) { 
                   printf("DUT(%2d) BBM(%9d)=#%08x is unexpected\n", dut, i, multich_bb_addr[dut-1][i]);
                   ng = 1;
                   break;
                }
             }
             if (j == efcnt) printf("DUT(%2d) BBM(%9d)=#%08x is unexpected\n", dut, i, multich_bb_addr[dut-1][i]);
          }
       }
       if (ng == 0) UTL_ResetTestResult(dut, testname, UT_RES_ALL);
       else         UTL_SetTestResult  (dut, testname, UT_RES_ALL);
   }     
   UTL_DeleteCursor(dutc);
}

void multich_JudgeEccFcsm(USlider *dut_res )
{
	char *testname = UTL_ReadTestName();
	UT_DUT dut;
	DutCursor dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
		if(dut_res[dut-1]==0){
			UTL_ResetTestResult(dut, testname,UT_RES_ALL);
		}
	}
}

/**
 * @brief Read hold register
 * @param Set "hmode" from testarg
*/
static void read_flash_hold(TEST_multicharg multicharg)
{
    int i,j,k;
//    int pin_sel=0;
    CheckButton multich_rdhold_p1[tdut]={0,};
    CheckButton multich_rdhold_p9[tdut]={0,};
    CheckButton multich_rdhold_p65[tdut]={0,};
    CheckButton multich_rdhold_p129[tdut]={0,};
    CheckButton multich_rdhold_p193[tdut]={0,};
    for(i=0; i<tdut; i++){multich_rdhold[i]=0;}		

    ReadFlashHoldHandle rfh_h;
    DutCursor dutc;
    UT_DUT dut;
    PinCursor pinc;
    UT_PIN pin;

    rfh_h=UTL_GetReadFlashHoldHandle();
    dutc=UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
        UTL_SetReadFlashHoldDut(rfh_h, dut);
  
        if(multicharg.dutch==0){pinc = UTL_GetPinCursor("matchpin0");}
        if(multicharg.dutch==1){pinc = UTL_GetPinCursor("matchpin1");}
        if(multicharg.dutch==2){pinc = UTL_GetPinCursor("matchpin2");}
        if(multicharg.dutch==3){pinc = UTL_GetPinCursor("matchpin3");}

        while((pin=UTL_NextPin(pinc))!=UT_NOMORE){
            UTL_SetReadFlashHoldPin(rfh_h, pin);
            if(pin==1)  {multich_rdhold_p1[dut-1]=UTL_ReadFlashHold(rfh_h);}
            if(pin==9)  {multich_rdhold_p9[dut-1]=UTL_ReadFlashHold(rfh_h);}
            if(pin==65) {multich_rdhold_p65[dut-1]=UTL_ReadFlashHold(rfh_h);}
            if(pin==129){multich_rdhold_p129[dut-1]=UTL_ReadFlashHold(rfh_h);}
            if(pin==193){multich_rdhold_p193[dut-1]=UTL_ReadFlashHold(rfh_h);}

	    }UTL_DeleteCursor(pinc);
    }UTL_DeleteCursor(dutc);
    UTL_DeleteHandle(rfh_h);

    for(j=0; j<tdut; j++){
        if(multich_rdhold_p1[j]  ==1){multich_rdhold[j]=multich_rdhold[j] | 0x1;}
        if(multich_rdhold_p9[j]  ==1){multich_rdhold[j]=multich_rdhold[j] | 0x1;}
        if(multich_rdhold_p65[j] ==1){multich_rdhold[j]=multich_rdhold[j] | 0x1;}
        if(multich_rdhold_p129[j]==1){multich_rdhold[j]=multich_rdhold[j] | 0x1;}
        if(multich_rdhold_p193[j]==1){multich_rdhold[j]=multich_rdhold[j] | 0x1;}
    }

    if(DEBUG2==1){
        printf("FLASH HOLD    : ");
        for(j=0; j<tdut; j++){printf("%5x", multich_rdhold[j]);}		
        printf("\n");fflush(stdout);
    } 
}

/**
 * @brief Read the value of the flash counter
*/
static void read_flash_counter(TEST_multicharg multicharg)
{
    int i,j,k;
    for(i=0; i<tdut; i++){
		rdcounter0[i]=0; 
		rdcounter1[i]=0; 
		rdcounter2[i]=0; 
		rdcounter3[i]=0; 
	}

    ReadFlashCounterHandle rfc_h;
    DutCursor dutc;
    UT_DUT dut;

    rfc_h=UTL_GetReadFlashCounterHandle();

	//printf("flash counter dutch=%d\n",flasharg->dutch);
	for (k=0; k<multicharg.dutchcnt; k++){
		UTL_SetReadFlashCounterChannel(rfc_h, k);

		dutc=UTL_GetDutCursor(UT_CDUT);
		while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
			UTL_SetReadFlashCounterDut(rfc_h, dut);
			if(k==0){rdcounter0[dut-1]=UTL_ReadFlashCounter(rfc_h);}
			if(k==1){rdcounter1[dut-1]=UTL_ReadFlashCounter(rfc_h);}
			if(k==2){rdcounter2[dut-1]=UTL_ReadFlashCounter(rfc_h);}
			if(k==3){rdcounter3[dut-1]=UTL_ReadFlashCounter(rfc_h);}
		}UTL_DeleteCursor(dutc);

		if(DEBUG2==1){
			printf("Dut Channel %1d : ", k);
			if(k==0){for(j=0; j<tdut; j++ ){printf("%5d", rdcounter0[j]);} printf("\n");fflush(stdout);}
			if(k==1){for(j=0; j<tdut; j++ ){printf("%5d", rdcounter1[j]);} printf("\n");fflush(stdout);}
			if(k==2){for(j=0; j<tdut; j++ ){printf("%5d", rdcounter2[j]);} printf("\n");fflush(stdout);}
			if(k==3){for(j=0; j<tdut; j++ ){printf("%5d", rdcounter3[j]);} printf("\n");fflush(stdout);}
		}
	}
	UTL_DeleteHandle(rfc_h);
}

/**
 * @brief Read if maxfail has occurred
*/
static void read_flash_maxfail(TEST_multicharg multicharg)
{
    int i,j;
    for(i=0; i<tdut; i++){multich_rdmaxfail[i]=0;} 

    ReadFlashMaxFailHandle rfmf_h;

    DutCursor dutc;
    UT_DUT dut;

    rfmf_h=UTL_GetReadFlashMaxFailHandle();

	//printf("flash maxfail dutch=%d\n",flasharg->dutch);
	UTL_SetReadFlashMaxFailChannel(rfmf_h, multicharg.dutch);

    dutc=UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
        UTL_SetReadFlashMaxFailDut(rfmf_h, dut);
        multich_rdmaxfail[dut-1]=UTL_ReadFlashMaxFail(rfmf_h);
    }UTL_DeleteCursor(dutc);
    UTL_DeleteHandle(rfmf_h);

    if(DEBUG2==1){
        printf("FLASH MAXFAIL : ");
        for(j=0; j<tdut; j++){printf("%5d", multich_rdmaxfail[j]);}		
        printf("\n");fflush(stdout);
    }
}

/**
 * @brief Set the expected value of the test result
*/
static void check_result(TEST_multicharg multicharg)
{
    int i,j;
    int chk_result=0;
    int chk_rdcounter0[tdut]={0,};
    int chk_rdcounter1[tdut]={0,};
    int chk_rdcounter2[tdut]={0,};
    int chk_rdcounter3[tdut]={0,};
    int chk_multich_rdmaxfail[tdut]={0,};
    int chk_multich_rdhold[tdut]={0,};

    switch(multicharg.ubmjudge){
        case 1:
            chk_rdcounter0[0]=30;chk_rdcounter0[1]=35;chk_rdcounter0[2]=40;chk_rdcounter0[3]=45;
            chk_rdcounter1[0]=0; chk_rdcounter1[1]=0; chk_rdcounter1[2]=0; chk_rdcounter1[3]=0;
			chk_rdcounter2[0]=0; chk_rdcounter2[1]=0; chk_rdcounter2[2]=0; chk_rdcounter2[3]=0;
			chk_rdcounter3[0]=0; chk_rdcounter3[1]=0; chk_rdcounter3[2]=0; chk_rdcounter3[3]=0;
            chk_multich_rdmaxfail[0]=0;  chk_multich_rdmaxfail[1]=0;  chk_multich_rdmaxfail[2]=0;  chk_multich_rdmaxfail[3]=0;
            chk_multich_rdhold[0]=0x1;   chk_multich_rdhold[1]=0x1;   chk_multich_rdhold[2]=0x1;   chk_multich_rdhold[3]=0x1;
            break;
        case 2:
            chk_rdcounter0[0]=0; chk_rdcounter0[1]=0; chk_rdcounter0[2]=0; chk_rdcounter0[3]=0;
            chk_rdcounter1[0]=30;chk_rdcounter1[1]=35;chk_rdcounter1[2]=40;chk_rdcounter1[3]=45;
			chk_rdcounter2[0]=0; chk_rdcounter2[1]=0; chk_rdcounter2[2]=0; chk_rdcounter2[3]=0;
			chk_rdcounter3[0]=0; chk_rdcounter3[1]=0; chk_rdcounter3[2]=0; chk_rdcounter3[3]=0;
            chk_multich_rdmaxfail[0]=0; chk_multich_rdmaxfail[1]=0; chk_multich_rdmaxfail[2]=0; chk_multich_rdmaxfail[3]=0;
            chk_multich_rdhold[0]=0x1;  chk_multich_rdhold[1]=0x1;  chk_multich_rdhold[2]=0x1;  chk_multich_rdhold[3]=0x1;
            break;
        case 3:
            chk_rdcounter0[0]=0; chk_rdcounter0[1]=0; chk_rdcounter0[2]=0; chk_rdcounter0[3]=0;
            chk_rdcounter1[0]=0; chk_rdcounter1[1]=0; chk_rdcounter1[2]=0; chk_rdcounter1[3]=0;
			chk_rdcounter2[0]=30;chk_rdcounter2[1]=35;chk_rdcounter2[2]=40;chk_rdcounter2[3]=45;
            chk_rdcounter3[0]=0; chk_rdcounter3[1]=0; chk_rdcounter3[2]=0; chk_rdcounter3[3]=0;
            chk_multich_rdmaxfail[0]=0; chk_multich_rdmaxfail[1]=0; chk_multich_rdmaxfail[2]=0; chk_multich_rdmaxfail[3]=0;
            chk_multich_rdhold[0]=0x1;  chk_multich_rdhold[1]=0x1;  chk_multich_rdhold[2]=0x1;  chk_multich_rdhold[3]=0x1;
            break;
        case 4:
            chk_rdcounter0[0]=0; chk_rdcounter0[1]=0; chk_rdcounter0[2]=0; chk_rdcounter0[3]=0;
            chk_rdcounter1[0]=0; chk_rdcounter1[1]=0; chk_rdcounter1[2]=0; chk_rdcounter1[3]=0;
            chk_rdcounter2[0]=0; chk_rdcounter2[1]=0; chk_rdcounter2[2]=0; chk_rdcounter2[3]=0;
            chk_rdcounter3[0]=30;chk_rdcounter3[1]=35;chk_rdcounter3[2]=40;chk_rdcounter3[3]=45;
            chk_multich_rdmaxfail[0]=0; chk_multich_rdmaxfail[1]=0; chk_multich_rdmaxfail[2]=0; chk_multich_rdmaxfail[3]=0;
            chk_multich_rdhold[0]=0x1;  chk_multich_rdhold[1]=0x1;  chk_multich_rdhold[2]=0x1;  chk_multich_rdhold[3]=0x1;
            break;
        case 5:
            chk_rdcounter0[0]=20;chk_rdcounter0[1]=10;chk_rdcounter0[2]=10;chk_rdcounter0[3]=10;
            chk_rdcounter1[0]=0; chk_rdcounter1[1]=0; chk_rdcounter1[2]=0; chk_rdcounter1[3]=0;
			chk_rdcounter2[0]=0; chk_rdcounter2[1]=0; chk_rdcounter2[2]=0; chk_rdcounter2[3]=0;
			chk_rdcounter3[0]=0; chk_rdcounter3[1]=0; chk_rdcounter3[2]=0; chk_rdcounter3[3]=0;
            chk_multich_rdmaxfail[0]=1;  chk_multich_rdmaxfail[1]=0;  chk_multich_rdmaxfail[2]=0;  chk_multich_rdmaxfail[3]=0;
            chk_multich_rdhold[0]=0x1;   chk_multich_rdhold[1]=0x1;   chk_multich_rdhold[2]=0x1;   chk_multich_rdhold[3]=0x1;
            break;
        case 6:
            chk_rdcounter0[0]=0; chk_rdcounter0[1]=0; chk_rdcounter0[2]=0; chk_rdcounter0[3]=0;
            chk_rdcounter1[0]=10;chk_rdcounter1[1]=20;chk_rdcounter1[2]=10;chk_rdcounter1[3]=10;
			chk_rdcounter2[0]=0; chk_rdcounter2[1]=0; chk_rdcounter2[2]=0; chk_rdcounter2[3]=0;
			chk_rdcounter3[0]=0; chk_rdcounter3[1]=0; chk_rdcounter3[2]=0; chk_rdcounter3[3]=0;
            chk_multich_rdmaxfail[0]=0;  chk_multich_rdmaxfail[1]=1; chk_multich_rdmaxfail[2]=0; chk_multich_rdmaxfail[3]=0;
            chk_multich_rdhold[0]=0x1;   chk_multich_rdhold[1]=0x1;  chk_multich_rdhold[2]=0x1;  chk_multich_rdhold[3]=0x1;
            break;
        case 7:
            chk_rdcounter0[0]=0; chk_rdcounter0[1]=0; chk_rdcounter0[2]=0; chk_rdcounter0[3]=0;
            chk_rdcounter1[0]=0; chk_rdcounter1[1]=0; chk_rdcounter1[2]=0; chk_rdcounter1[3]=0;
            chk_rdcounter2[0]=10;chk_rdcounter2[1]=10;chk_rdcounter2[2]=20;chk_rdcounter2[3]=10;
            chk_rdcounter3[0]=0; chk_rdcounter3[1]=0; chk_rdcounter3[2]=0; chk_rdcounter3[3]=0;
            chk_multich_rdmaxfail[0]=0; chk_multich_rdmaxfail[1]=0; chk_multich_rdmaxfail[2]=1; chk_multich_rdmaxfail[3]=0;
            chk_multich_rdhold[0]=0x1;  chk_multich_rdhold[1]=0x1;  chk_multich_rdhold[2]=0x1;  chk_multich_rdhold[3]=0x1;
            break;
        case 8:
            chk_rdcounter0[0]=0; chk_rdcounter0[1]=0; chk_rdcounter0[2]=0; chk_rdcounter0[3]=0;
            chk_rdcounter1[0]=0; chk_rdcounter1[1]=0; chk_rdcounter1[2]=0; chk_rdcounter1[3]=0;
            chk_rdcounter2[0]=0; chk_rdcounter2[1]=0; chk_rdcounter2[2]=0; chk_rdcounter2[3]=0;
            chk_rdcounter3[0]=10;chk_rdcounter3[1]=10;chk_rdcounter3[2]=10;chk_rdcounter3[3]=20;
            chk_multich_rdmaxfail[0]=0; chk_multich_rdmaxfail[1]=0; chk_multich_rdmaxfail[2]=0; chk_multich_rdmaxfail[3]=1;
            chk_multich_rdhold[0]=0x1;  chk_multich_rdhold[1]=0x1;  chk_multich_rdhold[2]=0x1;  chk_multich_rdhold[3]=0x1;
            break;
        default:
            printf("\n***** test number is not specify *****\n");fflush(stdout);
    }

    for(i=0; i<tdut; i++){
        if(chk_rdcounter0[i]!=rdcounter0[i]){chk_result=1;}
        if(chk_rdcounter1[i]!=rdcounter1[i]){chk_result=1;}
        if(chk_rdcounter2[i]!=rdcounter2[i]){chk_result=1;}
        if(chk_rdcounter3[i]!=rdcounter3[i]){chk_result=1;}
        if(chk_multich_rdmaxfail[i]!=multich_rdmaxfail[i]){chk_result=1;}
        if(chk_multich_rdhold[i]!=multich_rdhold[i]){chk_result=1;}
    }

    if(DEBUG==1){
        printf("TOTAL RESULT        : ");
        if(chk_result==0){printf("Pass");}
        if(chk_result==1){printf("Fail");}
        printf("\n");fflush(stdout);
    }

    for(j=0; j<tdut; j++){
        if(chk_result==0){UTL_ResetTestResult(j+1, UTL_ReadTestName(), UT_RES_ALL);}
        if(chk_result==1){UTL_SetTestResult(j+1, UTL_ReadTestName(), UT_RES_ALL);}
    }
}

static void bbm_dutch_setting(TEST_multicharg multicharg)
{
	int i;
    DutChannelHandle dutch_h = UTL_GetDutChannelHandle();
    UTL_SetDutChannelMode    (dutch_h, UT_ON);
    UTL_SetDutChannelCount   (dutch_h, multicharg.dutchcnt);
	if(multicharg.dutchcnt==2){
		UTL_SetDutChannelPinList (dutch_h, 0, "iopinlist0");
		UTL_SetDutChannelPinList (dutch_h, 1, "iopinlist1");
	}
	if(multicharg.dutchcnt==4){
		for(i=0; i<multicharg.dutchcnt; i++){
			UTL_SetDutChannelPinList (dutch_h, i, SOCKET.dutblock_iopinlist[i]);
		}
	}
    UTL_SendDutChannel       (dutch_h);
    UTL_DeleteHandle         (dutch_h);
}

static void fcsm_dutch_setting(TEST_multicharg multicharg)
{
    DutChannelHandle dutch_h = UTL_GetDutChannelHandle();
    UTL_SetDutChannelMode    (dutch_h, UT_ON);
    UTL_SetDutChannelCount   (dutch_h, 1);

	printf("##### dutchcnt=%d dutch=%d\n", multicharg.dutchcnt, multicharg.dutch);
	if(multicharg.dutchcnt==2){
		if(multicharg.dutch==0){UTL_SetDutChannelPinList (dutch_h, 0, "iopinlist0");}
		if(multicharg.dutch==1){UTL_SetDutChannelPinList (dutch_h, 0, "iopinlist1");}
	}
	if(multicharg.dutchcnt==4){
		UTL_SetDutChannelPinList (dutch_h, 0, SOCKET.dutblock_iopinlist[multicharg.dutch]);
	}

    UTL_SendDutChannel       (dutch_h);
    UTL_DeleteHandle         (dutch_h);
}

static void flash_dutch_setting(TEST_multicharg multicharg)
{
    DutChannelHandle dutch_h = UTL_GetDutChannelHandle();
    UTL_SetDutChannelMode    (dutch_h, UT_ON);

	UTL_SetDutChannelCount   (dutch_h, multicharg.dutchcnt);
	UTL_SetDutChannelPinList (dutch_h, 0, "matchpin0");
	UTL_SetDutChannelPinList (dutch_h, 1, "matchpin1");
	if(multicharg.dutchcnt==4){
		UTL_SetDutChannelPinList (dutch_h, 2, "matchpin2");
		UTL_SetDutChannelPinList (dutch_h, 3, "matchpin3");
	}
    UTL_SendDutChannel       (dutch_h);
    UTL_DeleteHandle         (dutch_h);
}

/**
 *@brief main routine to execute ECC test
 */
void multich_bbm_test(TEST_testitem *testarg)
{
	pin_list(MULTICHARG.dutchcnt);
	bbm_dutch_setting(MULTICHARG);
    bbm_init(MULTICHARG.ilmode, MULTICHARG.dutchcnt);
    bbm_timing_setting(MULTICHARG.rate);
    readtname();
    
    bbm_fail_capture_select(MULTICHARG.dutgrp);
    FailSelPin_("IOPIN", CAPTDAT);
    bbm_set_condition_capture(0,6);
    ecc_set_condition(MULTICHARG);
    bbm_clear();	

    bbm_set_ubm_data();
    bbm_write_ubm_data(MULTICHARG);
	
    MeasFct(MULTICHARG, UT_ON, UT_ON);
    bbm_read_address(MULTICHARG, 1);
    bbm_disable();	

    judge_ecc(MULTICHARG);
    test_result(testarg->testname);
}

/**********************************************************************
   Ecc Counter -> Fcsm Read Check(SDR Mode)
***********************************************************************/
void multich_fcsm_test(TEST_testitem *testarg)
{
    pin_list(MULTICHARG.dutchcnt);
    fcsm_dutch_setting(MULTICHARG);
    fcsm_init(MULTICHARG.ilmode, MULTICHARG.dutchcnt);
    fcsm_timing_setting(MULTICHARG.rate);
    readtname();
    
    fcsm_set_condition(MULTICHARG);
    fcsm_clear();	
//  bbm_set_condition_capture(0,18);
    ecc_set_condition(MULTICHARG);

    set_ubm_data(MULTICHARG);
    write_ubm_evenodd(MULTICHARG);

    MeasFct(MULTICHARG, UT_OFF, UT_OFF);
    readfcsm(MULTICHARG);
    test_result(testarg->testname);
}


void multich_flash_test(TEST_testitem *testarg)
{
	pin_list(MULTICHARG.dutchcnt);
	flash_dutch_setting(MULTICHARG);

	flash_init(MULTICHARG.ilmode, MULTICHARG.dutch);
    flash_timing_setting(MULTICHARG.rate);
    flash_reg_setting(0x30);

    flash_setting(MULTICHARG);
    flash_set_ubm_data();
    flash_write_ubm_data(MULTICHARG);
    MeasFct(MULTICHARG, UT_ON, UT_ON);

    if(DEBUG2==1){printf("                 DUT1 DUT2 DUT3 DUT4\n");fflush(stdout);}
    read_flash_counter(MULTICHARG);
    read_flash_maxfail(MULTICHARG);
    read_flash_hold(MULTICHARG);
    check_result(MULTICHARG);
}
