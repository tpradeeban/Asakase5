#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include "test.h"
#include "test_struct.h"
#include "flash.h"

#define V  *1.0
#define ns *1.0e-9

#define DEBUG 1
#define tdut 32
#define ubmcnt 1024

Slider rdcounter[tdut]={0,};
CheckButton rdmaxfail[tdut]={0,};
int rdhold[tdut]={0,};
int myfunc[tdut]={0,};
int status[tdut]={0,};

int FDIAGPC=0;
int FDIAGCHK=0;
static void fdiagpclockskip(TEST_testitem *testarg);
static void fdiagpcfreeskip(TEST_testitem *testarg);
static int fdiagpc_check();

void fpin_list(TEST_testitem *testarg);
void status_write(TEST_testitem *testarg);
void ilmode_setting(TEST_testitem *testarg);
void pin_setting(TEST_testitem *testarg);
void tim_setting(TEST_testitem *testarg);
void vol_setting();
void reg_setting(TEST_testitem *testarg);
void meas_fct(TEST_testitem *testarg);
void ubmset(TEST_testitem *testarg);
void ubmconf();
void ubmclear();
void ubmwrt(UT_DUT dut, int *wdata, unsigned int size);
void flash_setting();
void read_flash_hold(TEST_testitem *testarg);
void read_flash_counter();
void read_flash_maxfail();
void read_function();
void result_display();
void check_result(TEST_testitem *testarg);
void readfcsm_flash();

void flash_test(TEST_testitem *testarg)
{

    if(FDIAGCHK==0){
        FDIAGPC=fdiagpc_check();
        if(DEBUG==1){
		    if(FDIAGPC==1){printf("DIAG-PC:ON\n"); fflush(stdout);}
            if(FDIAGPC==0){printf("DIAG-PC:OFF\n");fflush(stdout);}
        }
///        if(FDIAGPC==0){fdiagpcfreeskip(testarg); return; }
        FDIAGCHK=1;
    }

///printf("*** %s, LINE:%d ***\n", __FILE__, __LINE__); fflush(stdout);
    fpin_list(testarg);
    status_write(testarg);
    ilmode_setting(testarg);

    pin_setting(testarg);
    tim_setting(testarg);
    vol_setting();
    reg_setting(testarg);
    flash_setting(testarg);
    ubmset(testarg);

    meas_fct(testarg);

    if( DEBUG == 1){
		int i;
		int dut_cnt = UTL_GetDutCount(UT_DDUT);
    	printf("                      ");
		for (i=1; i<=dut_cnt; i++)
		{
	    	printf(" DUT%02d", i);
		}
    	printf("\n");fflush(stdout);
	}

	if(FLASHARG.testcond<64) {
    	read_flash_counter();
    	read_flash_maxfail();
    	read_flash_hold(testarg);
    	read_function();
	    result_display();
    	check_result(testarg);
	} else {
		readfcsm_flash();
	}

}

void fpin_list(TEST_testitem *testarg)
{
	if(FLASHARG.testcond<64) {
    	UTL_CreatePinList ( "pin_1" );
    	UTL_SetPinType    ( "pin_1" , UT_PINTYPE_PIN );
    	UTL_AddPinNumber  ( "pin_1" , 1 );

    	UTL_CreatePinList ( "pin_2" );
    	UTL_SetPinType    ( "pin_2" , UT_PINTYPE_PIN );
    	UTL_AddPinNumber  ( "pin_2" , 2);

    	UTL_CreatePinList ( "pin_3" );
    	UTL_SetPinType    ( "pin_3" , UT_PINTYPE_PIN );
    	UTL_AddPinNumber  ( "pin_3" , 3 );

    	UTL_CreatePinList ( "pin_4" );
    	UTL_SetPinType    ( "pin_4" , UT_PINTYPE_PIN );
    	UTL_AddPinNumber  ( "pin_4" , 4 );

    	UTL_CreatePinList ( "devout" );
    	UTL_SetPinType    ( "devout" , UT_PINTYPE_PIN );
    	UTL_AppendPinList ( "devout" , "pin_1" );
    	UTL_AppendPinList ( "devout" , "pin_2" );
    	UTL_AppendPinList ( "devout" , "pin_3" );
    	UTL_AppendPinList ( "devout" , "pin_4" );

    	UTL_CreatePinList ( "pin_65" );
    	UTL_SetPinType    ( "pin_65" , UT_PINTYPE_PIN );
    	UTL_AddPinNumber  ( "pin_65" , 65 );

    	UTL_CreatePinList ( "pin_66" );
    	UTL_SetPinType    ( "pin_66" , UT_PINTYPE_PIN );
    	UTL_AddPinNumber  ( "pin_66" , 66 );

    	UTL_CreatePinList ( "outpin" );
    	UTL_SetPinType    ( "outpin" , UT_PINTYPE_PIN );
    	UTL_AppendPinList ( "outpin" , "pin_65" );
    	UTL_AppendPinList ( "outpin" , "pin_66" );
	} else {
		if(SOCKET.dut_iopin_count==16) {
		    UTL_CreatePinList ( "pin_1" );
    		UTL_SetPinType    ( "pin_1" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_1" , 1 );

    		UTL_CreatePinList ( "pin_2" );
    		UTL_SetPinType    ( "pin_2" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_2" , 3);

    		UTL_CreatePinList ( "pin_3" );
    		UTL_SetPinType    ( "pin_3" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_3" , 5 );

    		UTL_CreatePinList ( "pin_4" );
    		UTL_SetPinType    ( "pin_4" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_4" , 7 );

		    UTL_CreatePinList ( "pin_5" );
    		UTL_SetPinType    ( "pin_5" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_5" , 65 );

    		UTL_CreatePinList ( "pin_6" );
    		UTL_SetPinType    ( "pin_6" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_6" , 67);

    		UTL_CreatePinList ( "pin_7" );
    		UTL_SetPinType    ( "pin_7" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_7" , 69);

    		UTL_CreatePinList ( "pin_8" );
    		UTL_SetPinType    ( "pin_8" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_8" , 71);

    		UTL_CreatePinList ( "devout" );
    		UTL_SetPinType    ( "devout" , UT_PINTYPE_PIN );
    		UTL_AppendPinList ( "devout" , "pin_1" );
    		UTL_AppendPinList ( "devout" , "pin_2" );
    		UTL_AppendPinList ( "devout" , "pin_3" );
    		UTL_AppendPinList ( "devout" , "pin_4" );
    		UTL_AppendPinList ( "devout" , "pin_5" );
    		UTL_AppendPinList ( "devout" , "pin_6" );
    		UTL_AppendPinList ( "devout" , "pin_7" );
    		UTL_AppendPinList ( "devout" , "pin_8" );

    		UTL_CreatePinList ( "pin_65" );
    		UTL_SetPinType    ( "pin_65" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_65" , 2 );

    		UTL_CreatePinList ( "pin_66" );
    		UTL_SetPinType    ( "pin_66" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_66" , 66 );

    		UTL_CreatePinList ( "outpin" );
    		UTL_SetPinType    ( "outpin" , UT_PINTYPE_PIN );
    		UTL_AppendPinList ( "outpin" , "pin_65" );
    		UTL_AppendPinList ( "outpin" , "pin_66" );

    		UTL_CreatePinList ( "ch0_pin" );
    		UTL_SetPinType    ( "ch0_pin" , UT_PINTYPE_PIN );
    		UTL_AppendPinList ( "ch0_pin" , "pin_1" );
    		UTL_AppendPinList ( "ch0_pin" , "pin_2" );
    		UTL_AppendPinList ( "ch0_pin" , "pin_3" );
    		UTL_AppendPinList ( "ch0_pin" , "pin_4" );
    		UTL_AppendPinList ( "ch0_pin" , "pin_65" );

    		UTL_CreatePinList ( "ch1_pin" );
    		UTL_SetPinType    ( "ch1_pin" , UT_PINTYPE_PIN );
    		UTL_AppendPinList ( "ch1_pin" , "pin_5" );
    		UTL_AppendPinList ( "ch1_pin" , "pin_6" );
    		UTL_AppendPinList ( "ch1_pin" , "pin_7" );
    		UTL_AppendPinList ( "ch1_pin" , "pin_8" );
    		UTL_AppendPinList ( "ch1_pin" , "pin_66" );
		} else {
		    UTL_CreatePinList ( "pin_1" );
    		UTL_SetPinType    ( "pin_1" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_1" , 1 );

    		UTL_CreatePinList ( "pin_2" );
    		UTL_SetPinType    ( "pin_2" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_2" , 3);

    		UTL_CreatePinList ( "pin_3" );
    		UTL_SetPinType    ( "pin_3" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_3" , 5 );

    		UTL_CreatePinList ( "pin_4" );
    		UTL_SetPinType    ( "pin_4" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_4" , 7 );

    		UTL_CreatePinList ( "devout" );
    		UTL_SetPinType    ( "devout" , UT_PINTYPE_PIN );
    		UTL_AppendPinList ( "devout" , "pin_1" );
    		UTL_AppendPinList ( "devout" , "pin_2" );
    		UTL_AppendPinList ( "devout" , "pin_3" );
    		UTL_AppendPinList ( "devout" , "pin_4" );

    		UTL_CreatePinList ( "pin_65" );
    		UTL_SetPinType    ( "pin_65" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_65" , 2 );

    		UTL_CreatePinList ( "pin_66" );
    		UTL_SetPinType    ( "pin_66" , UT_PINTYPE_PIN );
    		UTL_AddPinNumber  ( "pin_66" , 4 );

    		UTL_CreatePinList ( "outpin" );
    		UTL_SetPinType    ( "outpin" , UT_PINTYPE_PIN );
    		UTL_AppendPinList ( "outpin" , "pin_65" );
    		UTL_AppendPinList ( "outpin" , "pin_66" );
		}
	}
}

void status_write ( TEST_testitem *testarg )
{
    if (DEBUG==1){
        char *tname;
        tname = UTL_ReadTestName();
        printf("\n");
        printf("TEST NAME           : %s\n", tname );
        printf("ILMODE              : %1d WAY\n", FLASHARG.ilmd );
        printf("FLASHMODE           : %s\n", FLASHARG.fmode );
        printf("HOLDMODE            : %s\n", FLASHARG.hmode );
        printf("Pattern             : %s\n", FLASHARG.patname );
        printf("Counter limit       : %d\n", FLASHARG.flmt );
        printf("IDX8                : %d\n", FLASHARG.rgidx8+2 );
        printf("UBMCOND             : %d\n", FLASHARG.ubmno );
        printf("TESTCOND            : %2d\n", FLASHARG.testcond);
        fflush(stdout);
    }
}

/**
 * @brief Set the interleave mode
 * @param Set "ilmd" from testarg
*/
void ilmode_setting(TEST_testitem *testarg)
{
    IlModeHandle ilm_h=UTL_GetIlModeHandle();
    UTL_SetIlMode(ilm_h, FLASHARG.ilmd);
    UTL_SendIlMode(ilm_h);
    UTL_DeleteHandle(ilm_h);
}

/**
 * @brief Set pin conditios
 * @param Set "hmode" from testarg
*/
void pin_setting(TEST_testitem *testarg)
{
    PinHandle pin_h;

    pin_h=UTL_GetPinHandle();
    UTL_InitializePinHandle(pin_h);
    UTL_SetPinViNumber     (pin_h, 1);                  //(handle, vi number)
    UTL_SetPinDrWaveform   (pin_h, UT_WAV_NRZB);        //(handle, driver waveform mode)
    UTL_SetPinDrClock      (pin_h, UT_PIN_BCLK, 1);	    //(handle, clock type, clock number)
    UTL_AddPinPdsA         (pin_h, UT_SIG_C(3), 1);     //(handle, pin data selector, cycle palette number)
    UTL_AddPinPdsA         (pin_h, UT_SIG_FL,   2);     //(handle, pin data selector, cycle palette number)
	UTL_SendPin            (pin_h, "devout" );
    UTL_DeleteHandle(pin_h);

    pin_h=UTL_GetPinHandle();
    UTL_InitializePinHandle  (pin_h);
    UTL_SetPinViNumber       (pin_h, 1 );               //(handle, vi number)
    UTL_SetPinDrWaveform     (pin_h, UT_WAV_NRZB);      //(handle, driver waveform mode)
    UTL_SetPinDrClock        (pin_h, UT_PIN_BCLK, 1);   //(handle, clock type, clock number)
    UTL_AddPinPdsA           (pin_h, UT_SIG_C(3), 1);   //(handle, pin data selector, cycle palette number)
    UTL_AddPinPdsA           (pin_h, UT_SIG_C(3), 2);   //(handle, pin data selector, cycle palette number)
    UTL_SetPinPatternInh     (pin_h, UT_ON);            //(handle, Inhibits or enables driver outputs) ***UT_ON:Inhibits driver outputs
    UTL_SetPinPatternInhLevel(pin_h, UT_PIN_LOW);       //(handle, Driver output level kept when driver outputs are inhibited) ***UT_PIN_LOW:low level
    UTL_SendPin              (pin_h, "pin_4");
    UTL_DeleteHandle(pin_h);

    if(strcmp(FLASHARG.hmode, "MATCH") == 0 || strcmp(FLASHARG.hmode, "MATCH2") == 0){
        pin_h=UTL_GetPinHandle();
        UTL_InitializePinHandle(pin_h);
        UTL_SetPinViNumber     (pin_h, 1);                 //(handle, vi number)
        UTL_SetPinDrWaveform   (pin_h, UT_WAV_FIXH);
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
        UTL_SendPin            (pin_h, "pin_65");
        if(FLASHARG.testcond>=64)UTL_SendPin            (pin_h, "pin_66");
        UTL_DeleteHandle(pin_h);

		if(FLASHARG.testcond<64) {
    	    pin_h=UTL_GetPinHandle();
        	UTL_InitializePinHandle(pin_h);
        	UTL_SetPinViNumber     (pin_h, 1);                 //(handle, vi number)
        	UTL_SetPinDrWaveform   (pin_h, UT_WAV_FIXL);
        	UTL_SetPinIoCtrl       (pin_h, UT_ON);             //(handle, onoff)
        	UTL_SetPinTerm         (pin_h, UT_ON);             //(handle, onoff)
        	UTL_SetPinVoNumber     (pin_h, 1);                 //(handle, vo number)
        	UTL_SetPinVtNumber     (pin_h, 1);                 //(handle, vt number)
        	UTL_SetPinDreNumber    (pin_h, 1);                 //(handle, DRECLOCK Number)
        	UTL_SetPinDreWaveform  (pin_h, UT_DREWAV_NRZ);     //(handle, DRE Wave Form)
        	UTL_SetPinDreClock     (pin_h, 1);                 //(handle, DREn)
        	UTL_AddPinStrbCpeNumber(pin_h, 1, 2);              //(handle, strb number, cpe number)
        	UTL_SetPinMatchMode    (pin_h, UT_SIG_NONE);       //(handle, Selects or deselects the MATCH mode) ***UT_SIG_NONE:Clears the existing match mode
        	UTL_AddPinExpStrbNumber(pin_h, 1, UT_PIN_EXP_FL);  //(handle, strb number, expected value pattern) ***UT_PIN_EXP_FL:Selects FIXL
        	UTL_SendPin            (pin_h, "pin_66");
        	UTL_DeleteHandle(pin_h);
		}
	}else if(strcmp(FLASHARG.hmode, "STACK") == 0 || strcmp(FLASHARG.hmode, "STACK2") == 0 ){
        pin_h=UTL_GetPinHandle();
        UTL_InitializePinHandle(pin_h);
        UTL_SetPinViNumber     (pin_h, 1);                 //(handle, vi number)
        UTL_SetPinDrWaveform   (pin_h, UT_WAV_FIXL);
        UTL_SetPinIoCtrl       (pin_h, UT_ON);             //(handle, onoff)
        UTL_SetPinTerm         (pin_h, UT_ON);             //(handle, onoff)
        UTL_SetPinVoNumber     (pin_h, 1);                 //(handle, vo number)
        UTL_SetPinVtNumber     (pin_h, 1);                 //(handle, vt number)
        UTL_SetPinDreNumber    (pin_h, 1);                 //(handle, DRECLOCK Number)
        UTL_SetPinDreWaveform  (pin_h, UT_DREWAV_NRZ);     //(handle, DRE Wave Form)
        UTL_SetPinDreClock     (pin_h, 1);                 //(handle, DREn)
        UTL_AddPinStrbCpeNumber(pin_h, 1 , 1);             //(handle, strb number, cpe number)
        UTL_SetPinMatchMode    (pin_h, UT_SIG_MATCH);       //(handle, Selects or deselects the MATCH mode) ***UT_SIG_NONE:Clears the existing match mode
       // UTL_SetPinMatchMode    (pin_h, UT_SIG_NONE);       //(handle, Selects or deselects the MATCH mode) ***UT_SIG_NONE:Clears the existing match mode
        UTL_AddPinExpStrbNumber(pin_h, 1 , UT_PIN_EXP_FL); //(handle, strb number, expected value pattern) ***UT_PIN_EXP_FL:Selects FIXL
        UTL_SendPin            (pin_h, "pin_65");
        UTL_DeleteHandle(pin_h);

        pin_h=UTL_GetPinHandle();
        UTL_InitializePinHandle(pin_h);
        UTL_SetPinViNumber     (pin_h, 1 );                //(handle, vi number)
        UTL_SetPinDrWaveform   (pin_h, UT_WAV_FIXL);
        UTL_SetPinIoCtrl       (pin_h, UT_ON);             //(handle, onoff)
        UTL_SetPinTerm         (pin_h, UT_ON);             //(handle, onoff)
        UTL_SetPinVoNumber     (pin_h, 1);                 //(handle, vo number)
        UTL_SetPinDreNumber    (pin_h, 1);                 //(handle, DRECLOCK Number)
        UTL_SetPinDreWaveform  (pin_h, UT_DREWAV_NRZ);     //(handle, DRE Wave Form)
        UTL_SetPinDreClock     (pin_h, 1);                 //(handle, DREn)
        UTL_SetPinVtNumber     (pin_h, 1);                 //(handle, vt number)
        UTL_AddPinStrbCpeNumber(pin_h, 1, 1);              //(handle, strb number, cpe number)
        UTL_SetPinMatchMode    (pin_h, UT_SIG_NONE);       //(handle, Selects or deselects the MATCH mode) ***UT_SIG_NONE:Clears the existing match mode
        UTL_AddPinExpStrbNumber(pin_h, 1 , UT_PIN_EXP_FL); //(handle, strb number, expected value pattern) ***UT_PIN_EXP_FL:Selects FIXL
        UTL_SendPin            (pin_h, "pin_66");
        UTL_DeleteHandle(pin_h);

    }else {printf("\n***** hold mode is not specify *****\n");fflush(stdout);}
}

/**
 * @brief Set the timing of TS1 to TS3
 * @param Set "tck" from testarg
*/
void tim_setting(TEST_testitem *testarg)
{
    TgHandle tg_h=UTL_GetTgHandle();
	if(FLASHARG.testcond<64) {
	    UTL_AddTgRate(tg_h,  1, 1000.0 ns);
    	UTL_AddTgRate(tg_h,  2, 1000.0 ns);
    	UTL_AddTgRate(tg_h,  3, 1000.0 ns);
	    UTL_AddTgStrb(tg_h,  1, 1, 100.0 ns);
		UTL_AddTgStrb(tg_h,  2, 1, 100.0 ns);
		UTL_AddTgStrb(tg_h,  3, 1, 100.0 ns);
    	UTL_AddTgBclk(tg_h,  1, 1,   0.0 ns);
    	UTL_AddTgBclk(tg_h,  2, 1,   0.0 ns);
	    UTL_AddTgBclk(tg_h,  3, 1,   0.0 ns);
	} else {
	    UTL_AddTgRate(tg_h,  1, 2.857 ns);
    	UTL_AddTgRate(tg_h,  2, 2.857 ns);
    	UTL_AddTgRate(tg_h,  3, 2.857 ns);
	    UTL_AddTgStrb(tg_h,  1, 1,   1.0 ns);
		UTL_AddTgStrb(tg_h,  2, 1,   1.0 ns);
		UTL_AddTgStrb(tg_h,  3, 1,   1.0 ns);
    	UTL_AddTgBclk(tg_h,  1, 1,   0.0 ns);
    	UTL_AddTgBclk(tg_h,  2, 1,   0.0 ns);
	    UTL_AddTgBclk(tg_h,  3, 1,   0.0 ns);
    	UTL_AddTgRate(tg_h, 15, 1000.0 ns);
    	UTL_AddTgRate(tg_h, 16, 1000.0 ns);
    	UTL_AddTgBclk(tg_h, 15, 1,   0.0 ns);
    	UTL_AddTgBclk(tg_h, 16, 1,   0.0 ns);
		UTL_AddTgStrb(tg_h, 15, 1, 100.0 ns);
		UTL_AddTgStrb(tg_h, 16, 1, 100.0 ns);
	}
    UTL_SendTg(tg_h);
    UTL_DeleteHandle(tg_h);
}

/**
 * @brief Set the voltage of VI,VO and VT
*/
void vol_setting(void)
{
    ViHandle vi_h=UTL_GetViHandle();
    UTL_SetViHigh(vi_h, 2.00 V);    //(handle, value)
    UTL_SetViLow (vi_h, 0.00 V);    //(handle, value)
    UTL_SetViHvDr(vi_h, UT_OFF);    //(handle, driver mode) ***UT_OFF:normal driver
    UTL_SendVi   (vi_h, 1 );        //(handle, vi channel number)
    UTL_DeleteHandle(vi_h);

    VoHandle vo_h=UTL_GetVoHandle();
    UTL_SetVoHigh(vo_h, 1.00 V);    //(handle, value)
    UTL_SetVoLow (vo_h, 1.00 V);    //(handle, value)
    UTL_SendVo   (vo_h, 1);         //(handle, vo channel number)
    UTL_DeleteHandle(vo_h);

    VtHandle vt_h=UTL_GetVtHandle();
    UTL_SetVt    (vt_h, 1.00 V);
    UTL_SendVt   (vt_h, 1);
    UTL_DeleteHandle(vt_h);

}

/**
 * @brief Set IDX8 register
 * @param Set "rgidx8" from testarg
*/
void reg_setting(TEST_testitem *testarg)
{
    RegHandle reg_h=UTL_GetRegHandle();
    UTL_ClearRegHandle(reg_h);
    UTL_SetRegIdx8    (reg_h, 1, FLASHARG.rgidx8);  //(handle, block(fixed to 1) ,value)
    UTL_SendReg(reg_h);
    UTL_DeleteHandle(reg_h);
}

/**
 * @brief Perform Functional Test by Using ALPG
 * @param Set "patname" from testarg
*/
void meas_fct(TEST_testitem *testarg)
{
    FctHandle fct_h=UTL_GetFctHandle();
    UTL_SetFctMpatName   (fct_h, FLASHARG.patname);  //(handle, pattern filename)
    UTL_SetFctFailInhibit(fct_h, UT_ON);             //(handle, fail inhibit mode) ***UT_ON:Fail inhibit mode is set
    UTL_SetFctStartPc    (fct_h, 0x0);               //(handle, program counter value)
    UTL_SetFctNoClear    (fct_h, UT_ON);             //(handle, register clear) ***UT_ON:Registers are not cleared.
    UTL_MeasFct(fct_h);
    UTL_DeleteHandle(fct_h);
}

/**
 * @brief Set UBM write data
 * @param Set "ilmd" from testarg
 * @param Set "ubmno" from testarg
*/
void ubmset(TEST_testitem *testarg)
{
int i;

    int idx1,idx2;
    int wdata[ubmcnt]={0,};
    unsigned int size=ubmcnt * sizeof(int);

    ubmconf();
    ubmclear();

    /*UBM write data setting description
    UTL_SetUbmAccessBitReverse(ua_h, UT_ON);
              33222222222211111111110000000000
              10987654321098765432109876543210
	wdata1 =  ----------------------------PPPP
                                          DDDD
                                          4321
    */

	UT_DUT dut;
    DutCursor dutcur = UTL_GetDutCursor(UT_DDUT);
	int ch;
    USlider ch_cnt;
	DutChannelHandle dchh = UTL_GetDutChannelHandle();
    while((dut= UTL_NextDut(dutcur)) != UT_NOMORE) {
///if(dut>1) break;
   	    for(idx1=0; idx1<ubmcnt; idx1++)wdata[idx1]=0;
	    switch(FLASHARG.ubmno){
    	    case 1:
        	    for(idx1=0; idx1<ubmcnt; idx1++){
            	    if(dut==1) if(idx1 >= 20*FLASHARG.ilmd){wdata[idx1]=wdata[idx1] | 0x1;}  //DUT1 PD1 - DUT1 P65 MATCH
                	if(dut==1) if(idx1 >= 80*FLASHARG.ilmd){wdata[idx1]=wdata[idx1] | 0x4;}  //DUT1 PD3 - DUT3 P65 MATCH
                	if(dut==3) wdata[idx1]=wdata[idx1] | 0x0;
            	}
            	for(idx2=0; idx2<ubmcnt; idx2++){
                	if(dut==2) if(idx2 >= 80*FLASHARG.ilmd){wdata[idx2]=wdata[idx2] | 0x1;}  //DUT2 PD1 - DUT2 P65 MATCH
                	if(dut==2) if(idx2 >= 80*FLASHARG.ilmd){wdata[idx2]=wdata[idx2] | 0x4;}  //DUT2 PD3 - DUT4 P65 MATCH
                	if(dut==4) wdata[idx2]=wdata[idx2] | 0x0;
            	}
            	break;
        	case 2:
            	for(idx1=0; idx1<ubmcnt; idx1++){
                	if(dut==1) if(idx1 >= 20*FLASHARG.ilmd){wdata[idx1]=wdata[idx1] | 0x1;}  //DUT1 PD1 - DUT1 P65 MATCH
                	if(dut==1) if(idx1 >= 20*FLASHARG.ilmd){wdata[idx1]=wdata[idx1] | 0x4;}  //DUT1 PD3 - DUT3 P65 MATCH
                	if(dut==3) wdata[idx1]=wdata[idx1] | 0x0;
            	}
            	for(idx2=0; idx2<ubmcnt; idx2++){
                	if(dut==2) if(idx2 >= 80*FLASHARG.ilmd){wdata[idx2]=wdata[idx2] | 0x1;}  //DUT2 PD1 - DUT2 P65 MATCH
                	if(dut==2) if(idx2 >= 20*FLASHARG.ilmd){wdata[idx2]=wdata[idx2] | 0x4;}  //DUT2 PD3 - DUT4 P65 MATCH
                	if(dut==4) wdata[idx2]=wdata[idx2] | 0x0;
            	}
            	break;
        	case 3:
            	for(idx1=0; idx1<ubmcnt; idx1++){
               		if(dut==1) if(idx1 <= 19*FLASHARG.ilmd){wdata[idx1]=wdata[idx1] | 0x1;}  //DUT1 PD1   - DUT1 P65
                	if(dut==1) wdata[idx1]=wdata[idx1] | 0xc;                                //DUT1 PD3-4 - DUT3 P65-66
                	if(dut==3) wdata[idx1]=wdata[idx1] | 0xf;
            	}
            	for(idx2=0; idx2<ubmcnt; idx2++){
                	if(dut==2) if(idx2 <= 79*FLASHARG.ilmd){wdata[idx2]=wdata[idx2] | 0x1;}  //DUT2 PD1   - DUT2 P65
                	if(dut==2) wdata[idx2]=wdata[idx2] | 0xc;                                //DUT2 PD3-4 - DUT4 P65-66
                	if(dut==4) wdata[idx2]=wdata[idx2] | 0xf;
            	}
            	break;
        	case 4:
            	for(idx1=0; idx1<ubmcnt; idx1++){
                	if(dut==1) if(idx1 <= 19*FLASHARG.ilmd){wdata[idx1]=wdata[idx1] | 0x1;}  //DUT1 PD1 - DUT1 P65
                	if(dut==3) wdata[idx1]=wdata[idx1] | 0xf;
            	}
            	for(idx2=0; idx2<ubmcnt; idx2++){
                	if(dut==2) if(idx2 <= 79*FLASHARG.ilmd){wdata[idx2]=wdata[idx2] | 0x1;}  //DUT2 PD1 - DUT2 P65
                	if(dut==4) wdata[idx2]=wdata[idx2] | 0xf;
            	}
            	break;
        	case 5:
 				UTL_UpdateDutChannel(dchh);
  				int res = UTL_GetDutChannelCount(dchh, &ch_cnt);
///    printf("***UTL_GetDutChannelCount returns 0x%X *******\n",res);fflush(stdout);
    			if(res!=1) {ch_cnt=1;}
        	    for(idx1=0; idx1<ubmcnt/ch_cnt; idx1++){
	        	    for(ch=0; ch<ch_cnt; ch++){
   	        	    	if(idx1 >= (dut-1)*FLASHARG.ilmd*ch_cnt+ch){wdata[idx1]=wdata[idx1] | (0xF<<(4*ch));}  //DUT1 PD1 - DUT1 P65 MATCH
					}
///if(idx1<64)printf("DUT%d, wdata[%d]=%d, LINE%d on %s \n", dut, idx1, wdata[idx1], __LINE__, __FILE__);fflush(stdout);
            	}
            	break;
        	default:
            printf("\n***** ubm condition is not specify *****\n");fflush(stdout);
		}
    	ubmwrt( dut, wdata, size);
	}
	UTL_DeleteHandle(dchh);
///      printf("Write UBM data, UBMNO:%d, LINE%d on %s \n", FLASHARG.ubmno, __LINE__, __FILE__);fflush(stdout);
}

/**
 * @brief Set UBM conditions
*/
void ubmconf(void)
{
    UbmConfigHandle uc_h=UTL_GetUbmConfigHandle();
    UTL_InitializeUbmConfigHandle   (uc_h);
    UTL_ClearUbmConfigFunctionSelect(uc_h);
    UTL_ClearUbmConfigPin           (uc_h, UT_UBM_UNIT_PM);     //(handle, UBM function specify) ***UT_UBM_UNIT_PM:Generates a pattern
    UTL_ClearUbmConfigJumpAddr      (uc_h, UT_UBM_UNIT_PM, 0);  //(handle, UBM function specify, jump address index number)
    UTL_ClearUbmConfigStrbChannel   (uc_h);

    UTL_AddUbmConfigFunctionSelect  (uc_h, UT_UBM_UNIT_PM, UT_SIGNAL_C(22));      //(handle, UBM function specify, enable cycle)
    UTL_SetUbmConfigPin             (uc_h, UT_UBM_UNIT_PM, "devout");             //(handle, UBM function specify, pinlist)
    UTL_SetUbmConfigJumpAddr        (uc_h, UT_UBM_UNIT_PM, 0 , 0x0);              //(handle, UBM function specify, jump address index number, jump address)
    UTL_SetUbmConfigJumpCycle       (uc_h, UT_UBM_UNIT_PM, 0 , UT_SIGNAL_C(24));  //(handle, UBM function specify, jump address index number, jump cycle)
	UTL_SetUbmConfigPmMode          (uc_h, UT_UBM_MODE_DRPAT);  //(handle, pmmode) ***UT_UBM_MODE_DRPAT:Uses the universal buffer memory pattern data as the driver waveform pattern
    UTL_SetUbmConfigDdrMode         (uc_h, UT_OFF);             //(handle, ddr setting) ***UT_OFF:Cancel
    UTL_SetUbmConfigApAutoIncMode   (uc_h, UT_ON);              //(handle, auto inc mode) ***UT_ON:Increments the address pointer
    UTL_SendUbmConfig(uc_h);
    UTL_DeleteHandle(uc_h);
}

/**
 * @brief Set UBM write conditions
 * @param UBM write data of odd  dut
 * @param UBM write data of even dut
 * @param odd  dut data buffer size
 * @param even dut data buffer size
*/
void ubmclear()
{
    UbmAccessHandle ua_h=UTL_GetUbmAccessHandle();
    UTL_ClearUbmAccessPin     (ua_h );
    UTL_PresetUbm             (ua_h, 0);         //(handle, preset at 0)
}

void ubmwrt(UT_DUT dut, int *wdata, unsigned int size)
{
    UbmAccessHandle ua_h=UTL_GetUbmAccessHandle();
    UTL_SetUbmAccessPin       (ua_h, "devout");  //(handle, pinlist)
    UTL_SetUbmAccessPinBlock  (ua_h, 1);         //(handle, pin block number) ***1:P1 to P18
    UTL_SetUbmAccessStartAddr (ua_h, 0x0);       //(handle, access start address)
    UTL_SetUbmAccessDdrMode   (ua_h, UT_OFF);    //(handle, ddr mode setting) ***UT_OFF:Cancel
    UTL_SetUbmAccessStopAddr  (ua_h, ubmcnt-1);  //(handle, access end address)
    UTL_SetUbmAccessBitReverse(ua_h, UT_ON);     //(handle, bit inversion) ***UT_ON:Performs bit inversion of data.

    UTL_SetUbmAccessDut(ua_h, dut);          //(handle, UBM access dut)
    UTL_WriteUbm(ua_h, wdata, size);
    UTL_DeleteHandle(ua_h);
///printf("*** Write UBM on DUT%d,  %s, LINE:%d ***\n", dut, __FILE__, __LINE__); fflush(stdout);
}

/**
 * @brief Set the flash conditions
 * @param Set "fmode" from testarg
 * @param Set "hmode" from testarg
*/
void flash_setting(TEST_testitem *testarg)
{
///printf("FLASHARG.testcond=%d, DEBUG=%d on %s, LINE:%d", FLASHARG.testcond, DEBUG, __FILE__, __LINE__);
	if(FLASHARG.testcond>=64) {
    	FailCaptureSelectHandle fcsh = UTL_GetFailCaptureSelectHandle();
    	UTL_SetFailCaptureSelectAllDutGroupNumber	(fcsh,UT_ON );
    	UTL_SetFailCaptureSelectAllPin				(fcsh,UT_OFF);
///    	UTL_SetFailCaptureSelectPinList				(fcsh,SOCKET.dutblock_iopinlist[fcsmarg.child]);
    	UTL_SendFailCaptureSelect					(fcsh);
    	UTL_DeleteHandle							(fcsh);
	
///    	fcsm_FailSelPin_(SOCKET.dutblock_iopinlist[fcsmarg.child], fcsmarg.captdat);

    	FcmConfigHandle fcmconfigh = UTL_GetFcmConfigHandle();
    	UTL_SetFcmConfigDelay	(fcmconfigh , 0);
    	UTL_AddFcmConfigAction  (fcmconfigh , 1 , 	UT_FCM_FLASHCOUNT_TO_FCSM );
    	UTL_SendFcmConfig 		(fcmconfigh);
    	UTL_DeleteHandle		(fcmconfigh);

		FcmAccessHandle fcmach = UTL_GetFcmAccessHandle();
		UTL_ResetFcsmStoreCnt();
    	UTL_ResetFcsm		(fcmach);
		UTL_DeleteHandle	(fcmach);
///printf("*** Executed UTL_ResetFcsm,  %s, LINE:%d ***\n", __FILE__, __LINE__); fflush(stdout);

printf("DUT IOPIN COUNT = %d\n", SOCKET.dut_iopin_count);
printf("DUT BLOCK COUNT = %d\n", SOCKET.dutblock_count);

		DutChannelHandle dchh = UTL_GetDutChannelHandle();
		if(SOCKET.dutblock_count==1){
			UTL_SetDutChannelMode(dchh, UT_OFF);
printf("DutChannelMode is OFF\n");
		} else {
			UTL_SetDutChannelMode(dchh, UT_ON);
			UTL_SetDutChannelCount(dchh, SOCKET.dutblock_count);
			UTL_SetDutChannelPinList(dchh, 0, "ch0_pin");
			UTL_SetDutChannelPinList(dchh, 1, "ch1_pin");
printf("UTL_SetDutChannelCount is %d\n", SOCKET.dutblock_count);
		}
		UTL_SendDutChannel(dchh);
    	UTL_DeleteHandle(dchh);


		if((SOCKET.dutblock_count>1)&&(FLASHARG.ilmd==1)){
	    	RegHandle reg_h=UTL_GetRegHandle();
	    	UTL_ClearRegHandle(reg_h);
	    	UTL_SetRegIdx2    (reg_h, 1, 5);
	    	UTL_SendReg(reg_h);
	    	UTL_DeleteHandle(reg_h);
		}
	}

    FlashHandle flash_h=UTL_GetFlashHandle();

    UTL_SetFlashLimitAllDut(flash_h, FLASHARG.flmt);  //(handle, limit value for the flash counter)

#if 1
    UTL_SetFlashCpInhPinMode(flash_h, UT_OFF);
#else
    UTL_SetFlashCpInhPinMode(flash_h, UT_ON);
    UTL_SetFlashCpInhPin(flash_h,"outpin");
#endif

	if     (strcmp(FLASHARG.fmode, "MAXFAIL")==0){UTL_SetFlashModeAllDut(flash_h, UT_FLASH_MAXFAIL);}    //(handle, operating mode)
	else if(strcmp(FLASHARG.fmode, "ORFAIL" )==0){UTL_SetFlashModeAllDut(flash_h, UT_FLASH_ORFAIL);}     //(handle, operating mode)
	else if(strcmp(FLASHARG.fmode, "DISABLE")==0){UTL_SetFlashModeAllDut(flash_h, UT_FLASH_DISABLE);}    //(handle, operating mode)
	else{printf("\n***** flash mode is not specify *****\n");fflush(stdout);}

	if     (strcmp(FLASHARG.hmode, "MATCH") ==0){UTL_SetFlashHoldModeAllDut(flash_h, UT_FLASH_MATCH);}   //(handle, hold mode)
	else if(strcmp(FLASHARG.hmode, "STACK") ==0){UTL_SetFlashHoldModeAllDut(flash_h, UT_FLASH_STACK);}   //(handle, hold mode)
	else if(strcmp(FLASHARG.hmode, "MATCH2")==0){UTL_SetFlashHoldModeAllDut(flash_h, UT_FLASH_MATCH2);}  //(handle, hold mode)
	else if(strcmp(FLASHARG.hmode, "STACK2")==0){UTL_SetFlashHoldModeAllDut(flash_h, UT_FLASH_STACK2);}  //(handle, hold mode)
	else{printf("\n***** hold mode is not specify *****\n");fflush(stdout);}

	UTL_SetFlashHoldConditionAllDut   (flash_h, UT_SIG_C(25), UT_SIG_C(26)); //(handle, load, clear)
	UTL_SetFlashCounterConditionAllDut(flash_h, UT_SIG_C(27), UT_SIG_C(28)); //(handle, increment, clear)

    UTL_SendFlash(flash_h);
    UTL_DeleteHandle(flash_h);
///printf("*** %s, LINE:%d ***\n", __FILE__, __LINE__); fflush(stdout);

}

/**
 * @brief Read hold register
 * @param Set "hmode" from testarg
*/
void read_flash_hold(TEST_testitem *testarg)
{
    int i,j,k;
    int pin_sel=0;
//    int rdhold[tdut]={0,};
    CheckButton rdhold_p65[tdut]={0,};
    CheckButton rdhold_p66[tdut]={0,};
	int dut_cnt = UTL_GetDutCount(UT_DDUT);
    for(i=0; i<dut_cnt; i++){rdhold[i]=0;}

    if(strcmp(FLASHARG.hmode, "MATCH")==0 || strcmp(FLASHARG.hmode, "MATCH2")==0){pin_sel=1;}
    if(strcmp(FLASHARG.hmode, "STACK")==0 || strcmp(FLASHARG.hmode, "STACK2")==0){pin_sel=2;}

    ReadFlashHoldHandle rfh_h;
    DutCursor dutc;
    UT_DUT dut;
    PinCursor pinc;
    UT_PIN pin;

    rfh_h=UTL_GetReadFlashHoldHandle();
    dutc=UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
        UTL_SetReadFlashHoldDut(rfh_h, dut);

        if(pin_sel==1){pinc = UTL_GetPinCursor("pin_65");}
        if(pin_sel==2){pinc = UTL_GetPinCursor("outpin");}

        while((pin=UTL_NextPin(pinc))!=UT_NOMORE){
            UTL_SetReadFlashHoldPin(rfh_h, pin);
            if(pin==65){rdhold_p65[dut-1]=UTL_ReadFlashHold(rfh_h);}
            if(pin==66){rdhold_p66[dut-1]=UTL_ReadFlashHold(rfh_h);}
	    }UTL_DeleteCursor(pinc);
    }UTL_DeleteCursor(dutc);
    UTL_DeleteHandle(rfh_h);

    for(j=0; j<dut_cnt; j++){
        if(rdhold_p65[j]==1){rdhold[j]=rdhold[j] | 0x1;}
        if(rdhold_p66[j]==1){rdhold[j]=rdhold[j] | 0x2;}
    }

    if(DEBUG==1){
        printf("FLASH HOLD(P66 P65) : ");
        for(j=0; j<dut_cnt; j++){printf("%6x", rdhold[j]);}
        printf("\n");fflush(stdout);
    }
}

/**
 * @brief Read the value of the flash counter
*/
void read_flash_counter(void)
{
    int i,j;
	int dut_cnt = UTL_GetDutCount(UT_DDUT);
    for(i=0; i<dut_cnt; i++){rdcounter[i]=0;}

    ReadFlashCounterHandle rfc_h;
    DutCursor dutc;
    UT_DUT dut;

    rfc_h=UTL_GetReadFlashCounterHandle();
    dutc=UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
        UTL_SetReadFlashCounterDut(rfc_h, dut);
        rdcounter[dut-1]=UTL_ReadFlashCounter(rfc_h);
    }UTL_DeleteCursor(dutc);
    UTL_DeleteHandle(rfc_h);

    if(DEBUG==1){
        printf("FLASH COUNTER       : ");
        for(j=0; j<dut_cnt; j++ ){printf("%6d", rdcounter[j]);}
        printf("\n");fflush(stdout);
    }
}

/**
 * @brief Read if maxfail has occurred
*/
void read_flash_maxfail(void)
{
    int i,j;
	int dut_cnt = UTL_GetDutCount(UT_DDUT);
    for(i=0; i<dut_cnt; i++){rdmaxfail[i]=0;}

    ReadFlashMaxFailHandle rfmf_h;

    DutCursor dutc;
    UT_DUT dut;

    rfmf_h=UTL_GetReadFlashMaxFailHandle();
    dutc=UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
        UTL_SetReadFlashMaxFailDut(rfmf_h, dut);
        rdmaxfail[dut-1]=UTL_ReadFlashMaxFail(rfmf_h);
    }UTL_DeleteCursor(dutc);
    UTL_DeleteHandle(rfmf_h);

    if(DEBUG==1){
        printf("FLASH MAXFAIL       : ");
        for(j=0; j<dut_cnt; j++){printf("%6d", rdmaxfail[j]);}
        printf("\n");fflush(stdout);
    }
}

void read_function(void)
{
    int i,j,k;
    int myfunc_p65[tdut]={0,};
    int myfunc_p66[tdut]={0,};
    for(i=0; i<tdut; i++){myfunc[i]=0;}

    FctReadPinHandle frp_h;
    DutCursor dutc;
    UT_DUT dut;
    PinCursor pinc;
    UT_PIN pin;

    frp_h = UTL_GetFctReadPinHandle();
    UTL_SetFctReadPinMode(frp_h, UT_RES_STRB1_FAILED);

    dutc=UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
        UTL_SetFctReadPinDut(frp_h, dut);

        pinc = UTL_GetPinCursor("outpin");
        while((pin=UTL_NextPin(pinc))!=UT_NOMORE){
            UTL_SetFctReadPinNumber(frp_h, pin);
            if(pin==65){myfunc_p65[dut-1]=UTL_ReadFctPin(frp_h);}
            if(pin==66){myfunc_p66[dut-1]=UTL_ReadFctPin(frp_h);}
        }UTL_DeleteCursor(pinc);
    }UTL_DeleteCursor(dutc);
    UTL_DeleteHandle(frp_h);

	int dut_cnt = UTL_GetDutCount(UT_DDUT);
    for(j=0; j<dut_cnt; j++){
        if(myfunc_p65[j]==1){myfunc[j]=myfunc[j] | 0x1;}
        if(myfunc_p66[j]==1){myfunc[j]=myfunc[j] | 0x2;}
    }

    if(DEBUG==1){
        printf("READ FUNC (P66 P65) : ");
        for(k=0; k<dut_cnt; k++){printf("%6x", myfunc[k]);}
		printf("\n");fflush(stdout);
    }
}

void result_display(void)
{
    int i,j;
    DutCursor dutc;
    UT_DUT dut;
	int dut_cnt = UTL_GetDutCount(UT_DDUT);

    for(i=0; i<dut_cnt; i++){status[i]=0;}

    dutc=UTL_GetDutCursor(UT_FDUT);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
        status[dut-1]=1;
    }UTL_DeleteCursor(dutc);

    if(DEBUG==1){
        printf("READ FDUT           : ");
        for(j=0; j<dut_cnt; j++){printf("%6d", status[j]);}
        printf("\n");fflush(stdout);
    }
}

void check_result(TEST_testitem *testarg)
{
    int i,j;
    int chk_result=0;
    int chk_rdcounter[tdut]={0,};
    int chk_rdmaxfail[tdut]={0,};
    int chk_rdhold[tdut]={0,};
    int chk_myfunc[tdut]={0,};
    int chk_status[tdut]={0,};

    switch(FLASHARG.testcond){
        case 1:
            chk_rdcounter[0]=20;chk_rdcounter[1]=30;chk_rdcounter[2]=30;chk_rdcounter[3]=30;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=0; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0x1;  chk_rdhold[1]=0x0;  chk_rdhold[2]=0x0;  chk_rdhold[3]=0x0;
            chk_myfunc[0]=0x0;  chk_myfunc[1]=0x2;  chk_myfunc[2]=0x0;  chk_myfunc[3]=0x2;
            chk_status[0]=0;    chk_status[1]=1;    chk_status[2]=0;    chk_status[3]=1;
            break;
        case 2:
            chk_rdcounter[0]=20;chk_rdcounter[1]=30;chk_rdcounter[2]=30;chk_rdcounter[3]=30;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=0; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0x0;  chk_rdhold[1]=0x0;  chk_rdhold[2]=0x0;  chk_rdhold[3]=0x0;
            chk_myfunc[0]=0x2;  chk_myfunc[1]=0x2;  chk_myfunc[2]=0x2;  chk_myfunc[3]=0x2;
            chk_status[0]=1;    chk_status[1]=1;    chk_status[2]=1;    chk_status[3]=1;
            break;
        case 3:
            chk_rdcounter[0]=20;chk_rdcounter[1]=40;chk_rdcounter[2]=20;chk_rdcounter[3]=20;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=1; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0x0;  chk_rdhold[1]=0x0;  chk_rdhold[2]=0x0;  chk_rdhold[3]=0x0;
            chk_myfunc[0]=0x2;  chk_myfunc[1]=0;    chk_myfunc[2]=0x2;  chk_myfunc[3]=0;
            chk_status[0]=1;    chk_status[1]=1;    chk_status[2]=1;    chk_status[3]=0;
            break;
        case 4:
            chk_rdcounter[0]=0; chk_rdcounter[1]=0; chk_rdcounter[2]=0; chk_rdcounter[3]=0;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=0; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0;    chk_rdhold[1]=0;    chk_rdhold[2]=0;    chk_rdhold[3]=0;
            chk_myfunc[0]=0x2;  chk_myfunc[1]=0x2;  chk_myfunc[2]=0x2;  chk_myfunc[3]=0x2;
            chk_status[0]=1;    chk_status[1]=1;    chk_status[2]=1;    chk_status[3]=1;
            break;
        case 5:
            chk_rdcounter[0]=20;chk_rdcounter[1]=30;chk_rdcounter[2]=30;chk_rdcounter[3]=30;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=0; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0x1;  chk_rdhold[1]=0x0;  chk_rdhold[2]=0x0;  chk_rdhold[3]=0x0;
            chk_myfunc[0]=0x0;  chk_myfunc[1]=0x2;  chk_myfunc[2]=0x0;  chk_myfunc[3]=0x2;
            chk_status[0]=0;    chk_status[1]=1;    chk_status[2]=0;    chk_status[3]=1;
            break;
        case 6:
            chk_rdcounter[0]=20;chk_rdcounter[1]=30;chk_rdcounter[2]=30;chk_rdcounter[3]=30;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=0; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0x0;  chk_rdhold[1]=0x0;  chk_rdhold[2]=0x0;  chk_rdhold[3]=0x0;
            chk_myfunc[0]=0x2;  chk_myfunc[1]=0x2;  chk_myfunc[2]=0x2;  chk_myfunc[3]=0x2;
            chk_status[0]=1;    chk_status[1]=1;    chk_status[2]=1;    chk_status[3]=1;
            break;
        case 7:
            chk_rdcounter[0]=20;chk_rdcounter[1]=40;chk_rdcounter[2]=20;chk_rdcounter[3]=20;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=1; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0x0;  chk_rdhold[1]=0x0;  chk_rdhold[2]=0x0;  chk_rdhold[3]=0x0;
            chk_myfunc[0]=0x2;  chk_myfunc[1]=0;    chk_myfunc[2]=0x2;  chk_myfunc[3]=0;
            chk_status[0]=1;    chk_status[1]=1;    chk_status[2]=1;    chk_status[3]=0;
            break;
        case 8:
            chk_rdcounter[0]=0; chk_rdcounter[1]=40;chk_rdcounter[2]=0; chk_rdcounter[3]=0;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=1; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0;    chk_rdhold[1]=0;    chk_rdhold[2]=0;    chk_rdhold[3]=0;
            chk_myfunc[0]=0x2;  chk_myfunc[1]=0x0;  chk_myfunc[2]=0x2;  chk_myfunc[3]=0x0;
            chk_status[0]=1;    chk_status[1]=1;    chk_status[2]=1;    chk_status[3]=0;
            break;
        case 9:
            chk_rdcounter[0]=20;chk_rdcounter[1]=50;chk_rdcounter[2]=50;chk_rdcounter[3]=50;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=0; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0x3;  chk_rdhold[1]=0x2;  chk_rdhold[2]=0x2;  chk_rdhold[3]=0x0;
            chk_myfunc[0]=0x0;  chk_myfunc[1]=0x3;  chk_myfunc[2]=0x1;  chk_myfunc[3]=0x3;
            chk_status[0]=0;    chk_status[1]=1;    chk_status[2]=1;    chk_status[3]=1;
            break;
        case 10:
            chk_rdcounter[0]=20;chk_rdcounter[1]=50;chk_rdcounter[2]=50;chk_rdcounter[3]=50;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=0; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0x0;  chk_rdhold[1]=0x0;  chk_rdhold[2]=0x0;  chk_rdhold[3]=0x0;
            chk_myfunc[0]=0x3;  chk_myfunc[1]=0x3;  chk_myfunc[2]=0x3;  chk_myfunc[3]=0x3;
            chk_status[0]=1;    chk_status[1]=1;    chk_status[2]=1;    chk_status[3]=1;
            break;
        case 11:
            chk_rdcounter[0]=20;chk_rdcounter[1]=40;chk_rdcounter[2]=0; chk_rdcounter[3]=0;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=1; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0x0;  chk_rdhold[1]=0x0;  chk_rdhold[2]=0x0;  chk_rdhold[3]=0x0;
            chk_myfunc[0]=0x3;  chk_myfunc[1]=0x0;  chk_myfunc[2]=0x3;  chk_myfunc[3]=0x1;
            chk_status[0]=1;    chk_status[1]=1;    chk_status[2]=1;    chk_status[3]=1;
            break;
        case 12:
            chk_rdcounter[0]=0; chk_rdcounter[1]=0; chk_rdcounter[2]=0; chk_rdcounter[3]=0;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=0; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0;    chk_rdhold[1]=0;    chk_rdhold[2]=0;    chk_rdhold[3]=0;
            chk_myfunc[0]=0x3;  chk_myfunc[1]=0x3;  chk_myfunc[2]=0x3;  chk_myfunc[3]=0x3;
            chk_status[0]=1;    chk_status[1]=1;    chk_status[2]=1;    chk_status[3]=1;
            break;
        case 13:
            chk_rdcounter[0]=20;chk_rdcounter[1]=50;chk_rdcounter[2]=50;chk_rdcounter[3]=50;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=0; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0x3;  chk_rdhold[1]=0x2;  chk_rdhold[2]=0x2;  chk_rdhold[3]=0x0;
            chk_myfunc[0]=0x0;  chk_myfunc[1]=0x3;  chk_myfunc[2]=0x1;  chk_myfunc[3]=0x3;
            chk_status[0]=0;    chk_status[1]=1;    chk_status[2]=1;    chk_status[3]=1;
            break;
        case 14:
            chk_rdcounter[0]=20;chk_rdcounter[1]=50;chk_rdcounter[2]=50;chk_rdcounter[3]=50;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=0; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0x0;  chk_rdhold[1]=0x0;  chk_rdhold[2]=0x0;  chk_rdhold[3]=0x0;
            chk_myfunc[0]=0x3;  chk_myfunc[1]=0x3;  chk_myfunc[2]=0x3;  chk_myfunc[3]=0x3;
            chk_status[0]=1;    chk_status[1]=1;    chk_status[2]=1;    chk_status[3]=1;
            break;
        case 15:
            chk_rdcounter[0]=20;chk_rdcounter[1]=40;chk_rdcounter[2]=0; chk_rdcounter[3]=0;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=1; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0x0;  chk_rdhold[1]=0x0;  chk_rdhold[2]=0x0;  chk_rdhold[3]=0x0;
            chk_myfunc[0]=0x3;  chk_myfunc[1]=0x0;  chk_myfunc[2]=0x3;  chk_myfunc[3]=0x1;
            chk_status[0]=1;    chk_status[1]=1;    chk_status[2]=1;    chk_status[3]=1;
            break;
        case 16:
            chk_rdcounter[0]=0; chk_rdcounter[1]=40;chk_rdcounter[2]=0; chk_rdcounter[3]=0;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=1; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0x0;  chk_rdhold[1]=0x0;  chk_rdhold[2]=0x0;  chk_rdhold[3]=0x0;
            chk_myfunc[0]=0x3;  chk_myfunc[1]=0x0;  chk_myfunc[2]=0x3;  chk_myfunc[3]=0x1;
            chk_status[0]=1;    chk_status[1]=1;    chk_status[2]=1;    chk_status[3]=1;
            break;
        case 64:
            chk_rdcounter[0]=20;chk_rdcounter[1]=30;chk_rdcounter[2]=30;chk_rdcounter[3]=30;
            chk_rdmaxfail[0]=0; chk_rdmaxfail[1]=0; chk_rdmaxfail[2]=0; chk_rdmaxfail[3]=0;
            chk_rdhold[0]=0x1;  chk_rdhold[1]=0x0;  chk_rdhold[2]=0x0;  chk_rdhold[3]=0x0;
            chk_myfunc[0]=0x0;  chk_myfunc[1]=0x2;  chk_myfunc[2]=0x0;  chk_myfunc[3]=0x2;
            chk_status[0]=0;    chk_status[1]=1;    chk_status[2]=0;    chk_status[3]=1;
            break;
        default:
            printf("\n***** test number is not specify *****\n");fflush(stdout);
    }

	int dut_cnt = UTL_GetDutCount(UT_DDUT);
    for(i=0; i<dut_cnt; i++){
        if(chk_rdcounter[i]!=rdcounter[i]){chk_result=1; printf("**FAIL!  [DUT%d] FLASH COUNTER <chk_rdcounter> = %d (exp=%d)\n",i+1, rdcounter[i], chk_rdcounter[i]);}
        if(chk_rdmaxfail[i]!=rdmaxfail[i]){chk_result=1; printf("**FAIL!  [DUT%d] FLASH MAXFAIL <chk_rdmaxfail> = %d (exp=%d)\n",i+1, rdmaxfail[i], chk_rdmaxfail[i]);}
        if(chk_rdhold[i]!=rdhold[i])      {chk_result=1; printf("**FAIL!  [DUT%d] FLASH HOLD <chk_rdhold> = %d (exp=%d)\n",i+1, rdhold[i], chk_rdhold[i]);}
        if(chk_myfunc[i]!=myfunc[i])      {chk_result=1; printf("**FAIL!  [DUT%d] READ FUNC <chk_myfunc> = %d (exp=%d)\n",i+1, myfunc[i], chk_myfunc[i]);}
        if(chk_status[i]!=status[i])      {chk_result=1; printf("**FAIL!  [DUT%d] READ FDUT <chk_status> = %d (exp=%d)\n",i+1, status[i], chk_status[i]);}
    }

    if(DEBUG==1){
        printf("TOTAL RESULT        : ");
        if(chk_result==0){printf("Pass");}
        if(chk_result==1){printf("Fail");}
        printf("\n");fflush(stdout);
    }

    char *tname;
    tname=UTL_ReadTestName();
    for(j=0; j<dut_cnt; j++){
        if(chk_result==0){UTL_ResetTestResult(j+1, tname, UT_RES_ALL);}
        if(chk_result==1){UTL_SetTestResult(j+1, tname, UT_RES_ALL);}
    }
}

static int fdiagpc_check(void)
{
    UTTB_HReg_Write(0x048CA000, 0x7F); //STLT_UTL_ONPBMB_SELECT ON
    UTL_WaitTime(1);

    RadioButton siteno = UTL_ReadSiteNumber();
    RadioButton block = 1+((siteno-1)/16)*2;
    int rdata;
    int result=0;
    int snddata=0;
    int getdata=0;
    snddata =snddata  | (0x1 << (1 - 1)); getdata= snddata  | (0x1 << (2 - 1));
    AuxDutSignalHandle ads_h=UTL_GetAuxDutSignalHandle();
    UTL_SetAuxDutSignalStationNumber(ads_h, UTL_ReadStationNumber());
    UTL_SetAuxDutSignalData         (ads_h, snddata );
    UTL_SendAuxDutSignal            (ads_h, UT_AUXDUTSIGNAL_MCW, block);
    UTL_UpdateAuxDutSignal          (ads_h, UT_AUXDUTSIGNAL_MCW, block);
    UTL_GetAuxDutSignalData         (ads_h, &rdata );
    if(rdata==getdata){result=1;}
    if(DEBUG==1){printf("block:%d send:%8x exp:%8x get:%8x \n",block,snddata,getdata,rdata);}
    UTL_DeleteHandle                (ads_h);

    UTTB_HReg_Write(0x048CA000, 0x00); //STLT_UTL_ONPBMB_SELECT OFF
    UTL_WaitTime(1);

    return result;
}

static void fdiagpclockskip(TEST_testitem *testarg)
{
     testarg->skipreason = TEST_SKIP_DIAGPB_LOCK;
     printf("\n%-32s",UTL_ReadTestName());
     printf(" ---ON_DIAGPC_SKIP");
}

static void fdiagpcfreeskip(TEST_testitem *testarg)
{
     testarg->skipreason = TEST_SKIP_DIAGPB_FREE;
     printf("\n%-32s",UTL_ReadTestName());
     printf(" ---OFF_DIAGPC_SKIP");
}

void readfcsm_flash()
{
    int chk_result[tdut]={0};
    int fail1[tdut]={0};
    int fail2[tdut]={0};
    int fail3[tdut]={0};
    int total_result=0;

    USlider dut_res[MAXDUTCNT]={0};
    USlider store_cnt;
    USlider ch_cnt;
    USlider *fcsm_data;
    USlider *exp_data;    //data1:odd dut,data2:even dut
    USlider rdata;
    DutCursor dutcur;
    UT_DUT dut;
    int sec;
    int afmx_cnt;
    int ch;
    int i;

	DutChannelHandle dchh = UTL_GetDutChannelHandle();
 	UTL_UpdateDutChannel(dchh);
  	int res = UTL_GetDutChannelCount(dchh, &ch_cnt);
///    printf("***UTL_GetDutChannelCount returns 0x%X *******\n",res);fflush(stdout);
    if(res!=1) {ch_cnt=1;}
    UTL_DeleteHandle(dchh);

    FcmAccessHandle fcmach = UTL_GetFcmAccessHandle();
    UTL_SetFcmAccessAllDut	(fcmach, UT_ON );
    UTL_SetFcmAccessBitMode (fcmach,UT_FCM_BITMODE_NORMAL);
    UTL_SetFcmAccessAllBit  (fcmach,UT_ON);

    UTL_ReadFcsmStoreCnt	(fcmach, &store_cnt);

	int dut_cnt = UTL_GetDutCount(UT_DDUT);
    fcsm_data = (USlider *)malloc(dut_cnt * store_cnt * ch_cnt * sizeof(USlider));
    exp_data  = (USlider *)calloc(store_cnt, sizeof(USlider));
///	printf("***Store   Count : 0x%X, size is 0x%X*******\n",store_cnt, store_cnt*ch_cnt*dut_cnt*sizeof(USlider));fflush(stdout);

    UTL_ReadFcsm		(fcmach,fcsm_data,store_cnt*ch_cnt*dut_cnt*sizeof(USlider));
    UTL_DeleteHandle(fcmach);

    dutcur = UTL_GetDutCursor(UT_CDUT);
    while((dut= UTL_NextDut(dutcur)) != UT_NOMORE) {
        for(ch=0;ch<ch_cnt;ch++) {
	        for(afmx_cnt=0;afmx_cnt<store_cnt;afmx_cnt++) {
        		rdata=fcsm_data[(dut-1)*store_cnt*ch_cnt+store_cnt*ch+afmx_cnt];
///if(afmx_cnt<2)printf("DUT:%d, CH%d, afx_cnt=%d, fcsm_data[%d]=%d(%d)\n",dut, ch, afmx_cnt, (dut-1)*store_cnt*ch_cnt+store_cnt*ch+afmx_cnt, fcsm_data[(dut-1)*store_cnt*ch_cnt+store_cnt*ch+afmx_cnt], 1+((dut-1)*ch_cnt)+ch+(afmx_cnt%32));fflush(stdout);
				if(rdata!=1+((dut-1)*ch_cnt)+ch+(afmx_cnt%32)){
					if(chk_result[dut-1]==0) {
						chk_result[dut-1]=1; total_result=1;
						fail1[dut-1]=ch; fail2[dut-1]=afmx_cnt; fail3[dut-1]=rdata;
					}
				} 
            }
	    }
	}

    free(fcsm_data);
    free(exp_data);

    char *tname;
    tname=UTL_ReadTestName();
    for(i=0; i<dut_cnt; i++){
        if(chk_result[i]==0){UTL_ResetTestResult(i+1, tname, UT_RES_ALL);}
        if(chk_result[i]==1){UTL_SetTestResult(i+1, tname, UT_RES_ALL);}
    }
    if(DEBUG==1){
        printf("READ FDUT           : ");
        for(i=0; i<dut_cnt; i++){printf("%6d", chk_result[i]);}
        printf("\n");fflush(stdout);
        printf("TOTAL RESULT        : ");
        if(total_result==0){printf("Pass");}
        if(total_result==1){printf("Fail");}
        printf("\n");fflush(stdout);
		if(total_result) {
		    printf("***Channel Count : %d *******\n",ch_cnt);fflush(stdout);
		    printf("***Store   Count : %d *******\n",store_cnt);fflush(stdout);
	    	dutcur = UTL_GetDutCursor(UT_CDUT);
    		while((dut= UTL_NextDut(dutcur)) != UT_NOMORE) {
				if(chk_result[dut-1]==1) {
					printf("DUT:%d, CH%d, afmx_cnt=%d, fcsm_data[%d]=%d(%d)\n",dut, fail1[dut-1], fail2[dut-1], (dut-1)*store_cnt+fail1[dut-1], fail3[dut-1], 1+((dut-1)*ch_cnt)+ch+(afmx_cnt%32));fflush(stdout);
				}
			} 
	    }
    }
///	printf("***Store   Count : 0x%X *******\n",store_cnt);fflush(stdout);
}
