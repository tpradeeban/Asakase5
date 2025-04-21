#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "UTSC.h"
#include "test.h"
#include "test_struct.h"
#include "common.h"
#include "fbgsync.h"

int grp8[FBGMAX] = {1,2,3,4,5,6,7,8};
int grp2[FBGMAX] = {1,1,2,2,1,1,1,1};
int grp2b[FBGMAX]= {1,2,2,1,1,2,2,1};
DSlider FBGrate[25]={
			0,
	      0.369699e-9,	//TS_DUMMY1, TSBASE
	    275.000000e-9,	//           TS_DINPRE
	     50.000000e-9,	//           TSDIN
	     56.499721e-9,	//           TS_DINPOST      
	    250.000000e-9,	//           TS_DOUTPRE,  TS_DOUT_PRE
	     50.000000e-9,	//           TSDOUT 
	     32.500000e-9,	//           TS_DOUTPOST
	    110.000000e-9,	//           TSPROTOCOLCHANGE
	   2000.000000e-9,	//           TSWAIT1US
	 125000.000000e-9,	//           TSWAITMAX
	     97.999442e-9,	//           TSTWHR
	     17.999442e-9,	//           TS_CAINPRE
	      3.999721e-9,	//           TSCAIN
	     50.000000e-9,	//           TS_CAINPOST
	     20.000000e-9,	//           TS_CAOUTPRE
	     10.000000e-9,	//           TSCAOUT
	     60.000000e-9,	//           TS_CAOUTPOST
	    123.500279e-9,	//           TSPOSTH,     TSSCAN
	    201.000279e-9,	//           TSADD5TOSCE, TS_A5_2_E
	    162.999442e-9,	//           TSE0TOSCE
	      0.375279e-9,	//TS_DUMMY2
	      0.372489e-9,	//TS_DUMMY3
	      0.739397e-9,	//TS_DUMMY4
	      0.371094e-9	//TS_DUMMY5
};

////////////////////////////////////////////
//for FBGSYNC shmoo (Rate Multiple)
////////////////////////////////////////////
DSlider FBGrateM[25]={
			0,
	      0.369699e-9,	//TS_DUMMY1, TSBASE
	    275.055804e-9,	//           TS_DINPRE
	     50.279018e-9,	//           TSDIN
	     56.194964e-9,	//           TS_DINPOST      
	    251.395089e-9,	//           TS_DOUTPRE,  TS_DOUT_PRE
	     50.279018e-9,	//           TSDOUT 
	     32.533482e-9,	//           TS_DOUTPOST
	    109.430803e-9,	//           TSPROTOCOLCHANGE
	   2002.287946e-9,	//           TSWAIT1US
	 124999.553571e-9,	//           TSWAITMAX
	     97.600446e-9,	//           TSTWHR
	     17.745536e-9,	//           TS_CAINPRE
	      5.915179e-9,	//           TSCAIN(4ns)
	     50.279018e-9,	//           TS_CAINPOST
	     20.703125e-9,	//           TS_CAOUTPRE
	     11.830317e-9,	//           TSCAOUT
	     59.151786e-9,	//           TS_CAOUTPOST
	    124.218750e-9,	//           TSPOSTH,     TSSCAN
	    201.116071e-9,	//           TSADD5TOSCE, TS_A5_2_E
	    162.667411e-9,	//           TSE0TOSCE
	      0.369699e-9,	//TS_DUMMY2
	      0.369699e-9,	//TS_DUMMY3
	      0.369699e-9,	//TS_DUMMY4
	      0.369699e-9	//TS_DUMMY5
};

	char*pat1[FBGMAX]={"pat_man_dq.mpa","pat_man_ca.mpa"};
	char*pat8[FBGMAX]={"pat_fbgsync_1.mpa","pat_fbgsync_2.mpa","pat_fbgsync_3.mpa","pat_fbgsync_4.mpa","pat_fbgsync_5.mpa","pat_fbgsync_6.mpa","pat_fbgsync_7.mpa","pat_fbgsync_8.mpa"};

	char*lab1[FBGMAX]={"Label1","Label2"};
	int   pc1[FBGMAX]={0x000, 0x000};
	int   pc000[FBGMAX]={0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000};
	int   pc100[FBGMAX]={0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100, 0x100};
	int   pc200[FBGMAX]={0x200, 0x200, 0x200, 0x200, 0x200, 0x200, 0x200, 0x200};
	int   pc240[FBGMAX]={0x240, 0x240, 0x240, 0x240, 0x240, 0x240, 0x240, 0x240};
	int   pc300[FBGMAX]={0x300, 0x300, 0x300, 0x300, 0x300, 0x300, 0x300, 0x300};
	int   pc340[FBGMAX]={0x340, 0x340, 0x340, 0x340, 0x340, 0x340, 0x340, 0x340};
	int   pc380[FBGMAX]={0x380, 0x380, 0x380, 0x380, 0x380, 0x380, 0x380, 0x380};
	int   pc3C0[FBGMAX]={0x3C0, 0x3C0, 0x3C0, 0x3C0, 0x3C0, 0x3C0, 0x3C0, 0x3C0};
	int   pc400[FBGMAX]={0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400, 0x400};
	int   pc440[FBGMAX]={0x440, 0x440, 0x440, 0x440, 0x440, 0x440, 0x440, 0x440};
	int   pc480[FBGMAX]={0x480, 0x480, 0x480, 0x480, 0x480, 0x480, 0x480, 0x480};
	int   pc500[FBGMAX]={0x500, 0x500, 0x500, 0x500, 0x500, 0x500, 0x500, 0x500};
	int   pc550[FBGMAX]={0x550, 0x550, 0x550, 0x550, 0x550, 0x550, 0x550, 0x550};
	int   pc600[FBGMAX]={0x600, 0x600, 0x600, 0x600, 0x600, 0x600, 0x600, 0x600};
	int   pc700[FBGMAX]={0x700, 0x700, 0x700, 0x700, 0x700, 0x700, 0x700, 0x700};
	int   pc800[FBGMAX]={0x800, 0x800, 0x800, 0x800, 0x800, 0x800, 0x800, 0x800};
	int   pc900[FBGMAX]={0x900, 0x900, 0x900, 0x900, 0x900, 0x900, 0x900, 0x900};
	int   pcA00[FBGMAX]={0xA00, 0xA00, 0xA00, 0xA00, 0xA00, 0xA00, 0xA00, 0xA00};
//////////////////////////////////////////////////////////////////
DSlider FBGrate2[25]={
			0,
	      0.369699e-9,	//TS_DUMMY1, TSBASE
	    275.000000e-9,	//           TS_DINPRE
	     50.000000e-9,	//           TSDIN
	     56.499721e-9,	//           TS_DINPOST      
	    250.000000e-9,	//           TS_DOUTPRE,  TS_DOUT_PRE
	     50.000000e-9,	//           TSDOUT 
	     32.500000e-9,	//           TS_DOUTPOST
	    110.000000e-9,	//           TSPROTOCOLCHANGE
	   1000.000000e-9,	//           TSWAIT1US
	 125000.000000e-9,	//           TSWAITMAX
	     97.999442e-9,	//           TSTWHR
	     17.999442e-9,	//           TS_CAINPRE
	      3.999721e-9,	//           TSCAIN
	     50.000000e-9,	//           TS_CAINPOST
	     20.000000e-9,	//           TS_CAOUTPRE
	     10.000000e-9,	//           TSCAOUT
	     60.000000e-9,	//           TS_CAOUTPOST
	    123.500279e-9,	//           TSPOSTH,     TSSCAN
	    201.000279e-9,	//           TSADD5TOSCE, TS_A5_2_E
	    162.999442e-9,	//           TSE0TOSCE
	      0.375279e-9,	//TS_DUMMY2
	      0.372489e-9,	//TS_DUMMY3
	      0.739397e-9,	//TS_DUMMY4
	      0.371094e-9	//TS_DUMMY5
};
	char*pat2[FBGMAX]={"pat_fbgsync_dq.mpa","pat_fbgsync_ca.mpa"};
	char*lab2[FBGMAX]={"Label1","Label2"};
	int   pc2[FBGMAX]={0x000, 0x000};

DSlider FBGrate0[25]={
			0,
	      2.957589286e-9,	
	      1999.330357e-9,	
	      0.369699e-9,	
	      1250e-12,
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9,	
	      1.000000e-9	
};
	char*adj0[FBGMAX]={"pat_adj0_dq.mpa","pat_adj0_ca.mpa"};
	char*pat0[FBGMAX]={"pat_wave_dq.mpa","pat_wave_ca.mpa"};
	char*patI[FBGMAX]={"pat_wave_ca.mpa","pat_wave_dq.mpa"};
	char*pat3[FBGMAX]={"pat_accu_dq.mpa","pat_accu_ca.mpa"};
	char*patH[FBGMAX]={"pat_fbgsync_hangchk_pg1.mpa","pat_fbgsync_hangchk_pg2.mpa"};
	char*patM[FBGMAX]={"pat_fbgsync_msel_pg1.mpa","pat_fbgsync_msel_pg2.mpa"};
	char*null[FBGMAX]={"Label1","Label2"};
	int   pc0[FBGMAX]={0x000, 0x000};
////////////////////////////////////////////
//for waveform test9003
////////////////////////////////////////////
DSlider FBGrate3[25]={
			0,
	      1.22e-9,
	      1999.330357e-9,	//
	      0.369699e-9,	//
	      1250e-12,
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9,	//
	      1.000000e-9	//
};
////////////////////////////////////////////
//for waveform test9002(Rate Multiple)
////////////////////////////////////////////
//FBGrateT[25]={
//	      2.957589286e-9,	//
//	      1999.330357e-9,	//
//	      0.369699e-9,	//
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16],
//	      FBGrateT[16]
//};
	int   pc10[FBGMAX]={0x010, 0x010};
	int   pc20[FBGMAX]={0x020, 0x020};
	int   pc30[FBGMAX]={0x030, 0x030};
	int   pc40[FBGMAX]={0x040, 0x040};
	int   pc50[FBGMAX]={0x050, 0x050};
	int   pc60[FBGMAX]={0x060, 0x060};
	int   pc70[FBGMAX]={0x070, 0x070};
	int   pc80[FBGMAX]={0x080, 0x080};
	int   pc90[FBGMAX]={0x090, 0x090};
	int   pcA0[FBGMAX]={0x0A0, 0x0A0};
	int   pcB0[FBGMAX]={0x0B0, 0x0B0};
	int   pcC0[FBGMAX]={0x0C0, 0x0C0};
	int   pcD0[FBGMAX]={0x0D0, 0x0D0};

void match(){
	PinHandle ph=UTL_GetPinHandle();
	UTL_SetPinSendMode	(ph, UT_PIN_PART);
	UTL_SetPinMatchMode	(ph, UT_SIG_MATCH);
	UTL_SendPin             (ph, "GR1CP");
	UTL_SendPin             (ph, "GR2CP");
	UTL_DeleteHandle	(ph);
}

void cal() {
//printf(" *** %s()\n", __func__);
	UTL_ExecSbcal("cal", "NORMAL NOMBIDCHK NOPBIDCHK NOMBLOCKCHK NOMBTYPECHK NOPBLOCKCHK");
}

void setOutSyncEnable(RadioButton onoff)
{
	if(onoff==UT_ON){
		UTL_SendExt( 0xB0700000,0x0);
		UTL_SendExt( 0xB0702000,0x500201);	//Enable //0x28 * 10ns = 800ns	//ok
	} else if(onoff==0x1234){
		UTL_SendExt( 0xB0700000,0x0);
		UTL_SendExt( 0xB0702000,0x270101);	//Enable(compatible)
	} else if(onoff==UT_OFF){
		UTL_SendExt( 0xB0700000,0x0);
		UTL_SendExt( 0xB0702000,0x500200);
	} else {
		printf(" *** Error:%s\n", __func__);
	}
}


void pinlist_drcp()
{
	UTL_CreatePinList("GR1DR");	UTL_AddPinNumber ("GR1DR",  4);	//Group1-Dr
	UTL_CreatePinList("GR2DR");	UTL_AddPinNumber ("GR2DR", 65);	//Group2-Dr
	UTL_CreatePinList("GR1CP");	UTL_AddPinNumber ("GR1CP",  3);	//Group1-Cp
	UTL_CreatePinList("GR2CP");	UTL_AddPinNumber ("GR2CP",  1);	//Group2-Cp

	UTL_CreatePinList("CPPINS");
	UTL_AppendPinList("CPPINS", "GR1CP");
	UTL_AppendPinList("CPPINS", "GR2CP");
}

void FBGdisplay_header(TEST_fbgarg fbgarg)
{
	int i;
    printf("*******************************************************************");
    printf("*******************************************************************");
    printf("********************************\n");
    printf("TEST NAME           : %s\n"        , UTL_ReadTestName()                );
    printf("ILMODE              : %3d WAY\n"   , fbgarg.ilmd                      );
	for(i=1;i<=24;i++){
		if(i%8==1) printf("RATE [TS%2d - TS%2d]  : ", i, i+7);
		//printf("%9.3f ", fbgarg->tck[i]*1e+9               );
		printf("%15.6f ", fbgarg.tck[i]*1e+9               );
		if(i%8==0) printf("[ns]\n");
	}
	printf("FBGSYNC MODE        : Start by %s" , fbgarg.mode==UT_ON ? "ON" : "OFF");
	int iom,grp,match;
	for(grp=1; grp<=FBGMAX; grp++){
		match=0;
		//UTL_ClearFuncBlockGroup       (fbh             ); 
		for(iom=0; iom<FBGMAX; iom++){
			if(grp==fbgarg.group[iom]){
				//UTL_AddFuncBlockGroupTargetBlock (fbh, iom+1); 
				if(match==0) printf("\nGROUP%d              : %d,", grp, iom+1);
				else         printf(" %d,", iom+1);
				//printf(" %d,", iom+1);
				//printf("(iom%d)", iom);
				match++;
			}
		}
		//if(match){ UTL_SendFuncBlockGroup (fbh, UT_FUNCGRP(grp) ); printf("\n"); }
	} //printf("\n");
//    printf("SDR/DDR             : %s(%d)\n"   , fbgarg->sdr_ddr, drate            );
//  printf("PATTERN             : %s(#%03X)\n", fbgarg->patname, fbgarg->pc        );
	for(grp=1; grp<=FBGMAX; grp++){
		match=0;
		for(iom=0; iom<FBGMAX; iom++){
			if(grp==fbgarg.group[iom]){
				printf("\nPATTERN%d            : %s(#%03X)", grp, fbgarg.patname[grp-1], fbgarg.pc[grp-1]);
				break;
				//else         printf(" %d,", iom+1);
				//match++;
			}
		}
	} printf("\n");
    printf("*******************************************************************");
    printf("*******************************************************************");
    printf("********************************\n");
}

static void ilmode_setting(TEST_fbgarg fbgarg)
{
    IlModeHandle ilm_h=UTL_GetIlModeHandle();
    UTL_SetIlMode     (ilm_h, fbgarg.ilmd);
    UTL_SendIlMode    (ilm_h);
    UTL_DeleteHandle  (ilm_h);
}

void func_block_group(TEST_fbgarg fbgarg)
{
//	printf(" *** %s()\n", __func__);
	int iom,grp,match;
	FuncBlockGroupHandle fbh=UTL_GetFuncBlockGroupHandle();
	for(grp=1; grp<=FBGMAX; grp++){
		match=0;
		UTL_ClearFuncBlockGroup       (fbh             ); 
		for(iom=0; iom<FBGMAX; iom++){
			if(grp==fbgarg.group[iom]){
				UTL_AddFuncBlockGroupTargetBlock (fbh, iom+1); 
				//if(match==0) printf(" *** grp:%d, iom:%d,", grp, iom+1);
				//else         printf(" %d,", iom+1);
				match++;
			}
		}
		if(match){ UTL_SendFuncBlockGroup (fbh, UT_FUNCGRP(grp) ); /*printf("\n");*/ }
	}
	UTL_DeleteHandle                      (fbh);
}

void send_mpat_per_group(TEST_fbgarg fbgarg)
{
	int grp,iom;
	MpatHandle mh1 = UTL_GetMpatHandle();
	for(grp=1; grp<=FBGMAX; grp++){
		for(iom=0; iom<FBGMAX; iom++){
			if(grp==fbgarg.group[iom]){
				mh1 = UTL_GetMpatHandle();
				UTL_SetMpatFuncBlockGroup(mh1, UT_FUNCGRP(grp)       );
				UTL_SetMpatFileName      (mh1, fbgarg.patname[grp-1]);
				UTL_SetMpatStartPc       (mh1, fbgarg.pc[grp-1]     );
				UTL_SendMpat             (mh1);
				UTL_DeleteHandle         (mh1);
				//printf("\nPATTERN%d            : %s(#%03X)", grp, fbgarg->patname[grp-1], fbgarg->pc[grp-1]);
				break;
			}
		}
	} printf("\n");
	
}

void send_mpat_sel_per_group(TEST_fbgarg fbgarg)
{
	int grp,iom;
	MpatSelectorHandle msh1=UTL_GetMpatSelectorHandle();
	for(grp=1; grp<=FBGMAX; grp++){
		for(iom=0; iom<FBGMAX; iom++){
			if(grp==fbgarg.group[iom]){
				msh1 = UTL_GetMpatSelectorHandle();
				UTL_SetMpatSelectorFuncBlockGroup( msh1, UT_FUNCGRP(grp));
				UTL_ClearMpatSelector( msh1 );
				UTL_AddMpatSelector( msh1, fbgarg.patname[0], "MSEL" );
				UTL_AddMpatSelector( msh1, fbgarg.patname[1], "MSEL" );
				UTL_AddMpatSelector( msh1, "pat_fbgsync_msel_common.mpa", "MSELCOM" );
				UTL_SendMpatSelector	 ( msh1 );
				UTL_DeleteHandle         (msh1);
				//printf("\nPATTERN%d            : %s(#%03X)", grp, fbgarg->patname[grp-1], fbgarg->pc[grp-1]);
				break;
			}
		}
	} printf("\n");
	
}

void dbm_setting()
{
	PinCursor pc,pc2,pcr;
	UT_PIN pin;
	int i, j;
	
	DbmConfigHandle dch = UTL_GetDbmConfigHandle();
	UTL_ClearDbmConfigPinAssign  (dch);
	UTL_SetDbmConfigAccessMode   (dch, UT_DBM_ACCESS_AP);
	
	int dbmbit=8;
	i = 0;
	UTL_SetDbmConfigBitAssignMode(dch, UT_DBM_PIN_DUT_COMMON);
	UTL_SetDbmConfigBitSize      (dch, dbmbit);
	pc = UTL_GetPinCursor("GR1DR");
	while((pin=UTL_NextPin(pc))!=UT_NOMORE){
	   UTL_AddDbmConfigPinAssign (dch, i, pin);
	}
	pc2= UTL_GetPinCursor("GR2DR");
	while((pin=UTL_NextPin(pc2))!=UT_NOMORE){
	   UTL_AddDbmConfigPinAssign (dch, i, pin);
	}
	UTL_SendDbmConfig(dch);
	UTL_DeleteHandle(dch);
	
	BurstScramHandle          h_BSTH = UTL_GetBurstScramHandle();
	UTL_SetBurstScramMode    (h_BSTH, UT_ON);
	UTL_SetBurstScramDdrType (h_BSTH, 5);
	UTL_SetBurstScramDataRate(h_BSTH, 2);
	UTL_SetBurstScramLength(h_BSTH, 16);
	UTL_SetBurstScramWrapType(h_BSTH, UT_WPTSQ);
	UTL_SetBurstScramAddrUnit(h_BSTH, UT_UNIT_PDS, UT_OFF);
	UTL_SetBurstScramAddrUnit(h_BSTH, UT_UNIT_DFM, UT_ON);
	UTL_SetBurstScramAddrUnit(h_BSTH, UT_UNIT_FP , UT_ON);
	UTL_SendBurstScram(h_BSTH);
	UTL_DeleteHandle(h_BSTH);
	
	PinHandle ph=UTL_GetPinHandle();
	UTL_SetPinSendMode	(ph, UT_PIN_PART);
	UTL_AddPinPdsA(ph, UT_SIG_PPAT_A	     , 1);
	UTL_AddPinPdsB(ph, UT_SIG_PPAT_B	     , 1);
	UTL_AddPinPdsA(ph, UT_SIG_PPAT_A	     , 2);
	UTL_AddPinPdsB(ph, UT_SIG_PPAT_B	     , 2);
	UTL_SendPin           (ph, "GR1DR");
	UTL_SendPin           (ph, "GR2DR");
	UTL_DeleteHandle	(ph);
}

void dbm_write()
{
	USlider *wdata;
	int dbmsize=0x10;
	wdata=(USlider *)malloc(dbmsize*sizeof(USlider));
	
	int i;
	for(i=0; i<dbmsize; i++){
	  wdata[i] = 0xffffffff;
	}
	DbmAccessHandle             h_DBM = UTL_GetDbmAccessHandle();
	UTL_SetDbmAccessUnitNumber (h_DBM, 1);
	UTL_SetDbmAccessAllUnit    (h_DBM, UT_ON);
	UTL_SetDbmAccessAllBlock   (h_DBM, UT_ON);
	UTL_SetDbmAccessDataKind   (h_DBM, UT_DBM_PPAT);
	UTL_SetDbmAccessStartAddr  (h_DBM, 0x0);
	UTL_SetDbmAccessStopAddr   (h_DBM, dbmsize-1);
	UTL_ResetDbm		     (h_DBM);
	UTL_WriteDbm               (h_DBM, wdata, dbmsize*sizeof(USlider));
	UTL_DeleteHandle           (h_DBM);
}

static void pin_setting(TEST_fbgarg fbgarg)
{
	UT_DUT dut;
	DutCursor dutc;
	int i;
    PinHandle pin_h;

	///////////////////////////////////
	/// DR
	///////////////////////////////////
    pin_h=UTL_GetPinHandle();
    UTL_InitializePinHandle       (pin_h);
    UTL_SetPinViNumber            (pin_h, 1);
//	if(strcmp(fbgarg->sdr_ddr,"SDR")==0){
//		UTL_SetPinDrWaveform      (pin_h, UT_WAV_NRZB);
//	} else {
		UTL_SetPinDrWaveform      (pin_h, UT_WAV_DNRZ);
//	}
    UTL_SetPinVoNumber            (pin_h, 1);
    UTL_SetPinVtNumber            (pin_h, 1);
    UTL_SetPinIoCtrl              (pin_h, UT_ON);
    UTL_SetPinTerm                (pin_h, UT_ON);
    UTL_SetPinDreNumber           (pin_h, 1);
    UTL_SetPinDreWaveform         (pin_h, UT_DREWAV_NRZ);
    UTL_SetPinDreClock            (pin_h, 1);
    UTL_AddPinStrbCpeNumber       (pin_h, 3, 3);
    UTL_AddPinStrbChannel         (pin_h, 3, 1);
    UTL_AddPinExpStrbNumber       (pin_h, 3, UT_PIN_EXP_A);
//	if(strcmp(fbgarg->sdr_ddr,"DDR")==0){
//     UTL_AddPinStrbCpeNumber    (pin_h, 2, 1);
//     UTL_AddPinExpStrbNumber    (pin_h, 2, UT_PIN_EXP_B);
//    }

//	if(fbgarg->chnum&0x1){
		UTL_ClearPinPdsA            (pin_h);
		UTL_ClearPinPdsB            (pin_h);
		for(i=0; i<BITMAX; i++){
//			if(fbgarg->pinCh1[i]==0){ break; }
			//printf("%d,", fbgarg->pinCh1[i]);
			UTL_AddPinPdsA(pin_h, UT_SIG_D (i)	     , 1);
			UTL_AddPinPdsB(pin_h, UT_SIG_SD(i)	     , 1);
			UTL_AddPinPdsA(pin_h, UT_SIG_D (i)	     , 2);
			UTL_AddPinPdsB(pin_h, UT_SIG_SD(i)	     , 2);
break;
	    }	//printf(" *** \n");
		UTL_SendPin               (pin_h, "GR1DR"     );
		UTL_SendPin               (pin_h, "GR2DR"     );

	///////////////////////////////////
	/// CP
	///////////////////////////////////
    pin_h=UTL_GetPinHandle();
    UTL_InitializePinHandle       (pin_h);
    UTL_SetPinViNumber            (pin_h, 1);
	UTL_SetPinDrWaveform      	  (pin_h, UT_WAV_NRZB);
    UTL_SetPinVoNumber            (pin_h, 1);
    UTL_SetPinVtNumber            (pin_h, 1);
    UTL_SetPinIoCtrl              (pin_h, UT_ON);
    UTL_SetPinTerm                (pin_h, UT_ON);
    UTL_SetPinDreNumber           (pin_h, 3);
    UTL_SetPinDreWaveform         (pin_h, UT_DREWAV_NRZ);
    UTL_SetPinDreClock            (pin_h, 1);
    UTL_AddPinStrbCpeNumber       (pin_h, 1, 1);
    UTL_AddPinExpStrbNumber       (pin_h, 1, UT_PIN_EXP_A);

	UTL_ClearPinPdsA            (pin_h);
	UTL_ClearPinPdsB            (pin_h);
	for(i=0; i<BITMAX; i++){
		UTL_AddPinPdsA(pin_h, UT_SIG_D (i)	     , 1);
		UTL_AddPinPdsB(pin_h, UT_SIG_SD(i)	     , 1);
		UTL_AddPinPdsA(pin_h, UT_SIG_FH		     , 2);
		UTL_AddPinPdsB(pin_h, UT_SIG_FH		     , 2);
break;
    }	//printf(" *** \n");
	UTL_SendPin                 (pin_h, "GR1CP"     );
	UTL_SendPin                 (pin_h, "GR2CP"     );
    UTL_DeleteHandle            (pin_h);
}

void pin_setting_match(TEST_fbgarg fbgarg)
{
	UT_DUT dut;
	DutCursor dutc;
	int i;
    PinHandle pin_h;

	///////////////////////////////////
	/// DR
	///////////////////////////////////
    	pin_h=UTL_GetPinHandle();
    	UTL_InitializePinHandle       (pin_h);
    	UTL_SetPinViNumber            (pin_h, 1);
//	if(strcmp(fbgarg->sdr_ddr,"SDR")==0){
//		UTL_SetPinDrWaveform      (pin_h, UT_WAV_NRZB);
//	} else {
		UTL_SetPinDrWaveform      (pin_h, UT_WAV_DNRZ);
//	}
    	UTL_SetPinVoNumber            (pin_h, 1);
    	UTL_SetPinVtNumber            (pin_h, 1);
    	UTL_SetPinIoCtrl              (pin_h, UT_ON);
    	UTL_SetPinTerm                (pin_h, UT_ON);
    	UTL_SetPinDreNumber           (pin_h, 1);
    	UTL_SetPinDreWaveform         (pin_h, UT_DREWAV_NRZ);
    	UTL_SetPinDreClock            (pin_h, 1);
    	UTL_AddPinStrbCpeNumber       (pin_h, 3, 3);
    	UTL_AddPinStrbChannel         (pin_h, 3, 1);
    	UTL_AddPinExpStrbNumber       (pin_h, 3, UT_PIN_EXP_A);

//	if(fbgarg->chnum&0x1){
		UTL_ClearPinPdsA            (pin_h);
		UTL_ClearPinPdsB            (pin_h);
		for(i=0; i<BITMAX; i++){
//			if(fbgarg->pinCh1[i]==0){ break; }
			//printf("%d,", fbgarg->pinCh1[i]);
			UTL_AddPinPdsA(pin_h, UT_SIG_D (i)	     , 1);
			UTL_AddPinPdsB(pin_h, UT_SIG_SD(i)	     , 1);
			UTL_AddPinPdsA(pin_h, UT_SIG_D (i)	     , 2);
			UTL_AddPinPdsB(pin_h, UT_SIG_SD(i)	     , 2);
break;
	    }	//printf(" *** \n");
		UTL_SendPin               (pin_h, "GR1DR"     );

    		UTL_InitializePinHandle       (pin_h);
    		UTL_SetPinViNumber            (pin_h, 1);
//	if(strcmp(fbgarg->sdr_ddr,"SDR")==0){
//		UTL_SetPinDrWaveform      (pin_h, UT_WAV_NRZB);
//	} else {
		UTL_SetPinDrWaveform      (pin_h, UT_WAV_DNRZ);
//	}
    		UTL_SetPinVoNumber            (pin_h, 1);
    		UTL_SetPinVtNumber            (pin_h, 1);
    		UTL_SetPinIoCtrl              (pin_h, UT_ON);
    		UTL_SetPinTerm                (pin_h, UT_ON);
    		UTL_SetPinDreNumber           (pin_h, 1);
    		UTL_SetPinDreWaveform         (pin_h, UT_DREWAV_NRZ);
    		UTL_SetPinDreClock            (pin_h, 1);
    		UTL_AddPinStrbCpeNumber       (pin_h, 3, 3);
    		UTL_AddPinStrbChannel         (pin_h, 3, 1);
    		UTL_AddPinExpStrbNumber       (pin_h, 3, UT_PIN_EXP_A);

		UTL_ClearPinPdsA            (pin_h);
		UTL_ClearPinPdsB            (pin_h);
		for(i=0; i<BITMAX; i++){
//			if(fbgarg->pinCh1[i]==0){ break; }
			//printf("%d,", fbgarg->pinCh1[i]);
			UTL_AddPinPdsA(pin_h, UT_SIG_D (i+1)	     , 1);
			UTL_AddPinPdsB(pin_h, UT_SIG_SD(i+1)	     , 1);
			UTL_AddPinPdsA(pin_h, UT_SIG_D (i+1)	     , 2);
			UTL_AddPinPdsB(pin_h, UT_SIG_SD(i+1)	     , 2);
break;
	    }	//printf(" *** \n");
		UTL_SendPin               (pin_h, "GR2DR"     );
//	}
//	if(fbgarg->chnum&0x2){
//		UTL_ClearPinPdsA            (pin_h);
//		UTL_ClearPinPdsB            (pin_h);
//		for(i=0; i<BITMAX; i++){
//			if(fbgarg->pinCh2[i]==0){ break; }
//			//printf("%d,", fbgarg->pinCh2[i]);
//			UTL_AddPinPdsA(pin_h, UT_SIG_D (i)	     , 1);
//			UTL_AddPinPdsB(pin_h, UT_SIG_SD(i)	     , 1);
//	    }	//printf(" *** \n");
//		UTL_SendPin               (pin_h, "IOPIN2"     );
//	}

	///////////////////////////////////
	/// CP
	///////////////////////////////////
    pin_h=UTL_GetPinHandle();
    UTL_InitializePinHandle       (pin_h);
    UTL_SetPinViNumber            (pin_h, 1);
	UTL_SetPinDrWaveform      	  (pin_h, UT_WAV_NRZB);
    UTL_SetPinVoNumber            (pin_h, 1);
    UTL_SetPinVtNumber            (pin_h, 1);
    UTL_SetPinIoCtrl              (pin_h, UT_ON);
    UTL_SetPinTerm                (pin_h, UT_ON);
    UTL_SetPinDreNumber           (pin_h, 3);
    UTL_SetPinDreWaveform         (pin_h, UT_DREWAV_NRZ);
    UTL_SetPinDreClock            (pin_h, 1);
    UTL_AddPinStrbCpeNumber       (pin_h, 1, 1);
    UTL_AddPinExpStrbNumber       (pin_h, 1, UT_PIN_EXP_A);

	UTL_ClearPinPdsA            (pin_h);
	UTL_ClearPinPdsB            (pin_h);
	for(i=0; i<BITMAX; i++){
		UTL_AddPinPdsA(pin_h, UT_SIG_FL   	     , 1);
		UTL_AddPinPdsB(pin_h, UT_SIG_FL   	     , 1);
		UTL_AddPinPdsA(pin_h, UT_SIG_FL		     , 2);
		UTL_AddPinPdsB(pin_h, UT_SIG_FL		     , 2);
break;
    }	//printf(" *** \n");
	UTL_SendPin                 (pin_h, "GR1CP"     );
	UTL_SendPin                 (pin_h, "GR2CP"     );
    UTL_DeleteHandle            (pin_h);
}

void pin_setting_FL(TEST_fbgarg fbgarg)
{
	UT_DUT dut;
	DutCursor dutc;
	int i;
    PinHandle pin_h;

	///////////////////////////////////
	/// DR
	///////////////////////////////////
    pin_h=UTL_GetPinHandle();
    UTL_InitializePinHandle       (pin_h);
    UTL_SetPinViNumber            (pin_h, 1);
    UTL_SetPinDrWaveform          (pin_h, UT_WAV_DNRZ);
    UTL_SetPinVoNumber            (pin_h, 1);
    UTL_SetPinVtNumber            (pin_h, 1);
    UTL_SetPinIoCtrl              (pin_h, UT_ON);
    UTL_SetPinTerm                (pin_h, UT_ON);
    UTL_SetPinDreNumber           (pin_h, 1);
    UTL_SetPinDreWaveform         (pin_h, UT_DREWAV_NRZ);
    UTL_SetPinDreClock            (pin_h, 1);
    UTL_AddPinStrbCpeNumber       (pin_h, 3, 3);
    UTL_AddPinStrbChannel         (pin_h, 3, 1);
    UTL_AddPinExpStrbNumber       (pin_h, 3, UT_PIN_EXP_A);
//	if(strcmp(fbgarg->sdr_ddr,"DDR")==0){
//     UTL_AddPinStrbCpeNumber    (pin_h, 2, 1);
//     UTL_AddPinExpStrbNumber    (pin_h, 2, UT_PIN_EXP_B);
//    }

//	if(fbgarg->chnum&0x1){
		UTL_ClearPinPdsA            (pin_h);
		UTL_ClearPinPdsB            (pin_h);
		for(i=0; i<BITMAX; i++){
//			if(fbgarg->pinCh1[i]==0){ break; }
			//printf("%d,", fbgarg->pinCh1[i]);
			UTL_AddPinPdsA(pin_h, UT_SIG_D (i)	     , 1);
			UTL_AddPinPdsB(pin_h, UT_SIG_SD(i)	     , 1);
			UTL_AddPinPdsA(pin_h, UT_SIG_D (i)	     , 2);
			UTL_AddPinPdsB(pin_h, UT_SIG_SD(i)	     , 2);
break;
	    }	//printf(" *** \n");
		UTL_SendPin               (pin_h, "GR1DR"     );
		UTL_SendPin               (pin_h, "GR2DR"     );
//	}
//	if(fbgarg->chnum&0x2){
//		UTL_ClearPinPdsA            (pin_h);
//		UTL_ClearPinPdsB            (pin_h);
//		for(i=0; i<BITMAX; i++){
//			if(fbgarg->pinCh2[i]==0){ break; }
//			//printf("%d,", fbgarg->pinCh2[i]);
//			UTL_AddPinPdsA(pin_h, UT_SIG_D (i)	     , 1);
//			UTL_AddPinPdsB(pin_h, UT_SIG_SD(i)	     , 1);
//	    }	//printf(" *** \n");
//		UTL_SendPin               (pin_h, "IOPIN2"     );
//	}

	///////////////////////////////////
	/// CP
	///////////////////////////////////
    pin_h=UTL_GetPinHandle();
    UTL_InitializePinHandle       (pin_h);
    UTL_SetPinViNumber            (pin_h, 1);
	UTL_SetPinDrWaveform      	  (pin_h, UT_WAV_NRZB);
    UTL_SetPinVoNumber            (pin_h, 1);
    UTL_SetPinVtNumber            (pin_h, 1);
    UTL_SetPinIoCtrl              (pin_h, UT_ON);
    UTL_SetPinTerm                (pin_h, UT_ON);
    UTL_SetPinDreNumber           (pin_h, 3);
    UTL_SetPinDreWaveform         (pin_h, UT_DREWAV_NRZ);
    UTL_SetPinDreClock            (pin_h, 1);
    UTL_AddPinStrbCpeNumber       (pin_h, 1, 1);
    UTL_AddPinExpStrbNumber       (pin_h, 1, UT_PIN_EXP_A);
//	if(strcmp(fbgarg->sdr_ddr,"DDR")==0){
//       UTL_AddPinStrbCpeNumber    (pin_h, 2, 1);
//       UTL_AddPinExpStrbNumber    (pin_h, 2, UT_PIN_EXP_B);
//    }

	UTL_ClearPinPdsA            (pin_h);
	UTL_ClearPinPdsB            (pin_h);
	for(i=0; i<BITMAX; i++){
		UTL_AddPinPdsA(pin_h, UT_SIG_FL   	     , 1);
		UTL_AddPinPdsB(pin_h, UT_SIG_FL   	     , 1);
		UTL_AddPinPdsA(pin_h, UT_SIG_FL		     , 2);
		UTL_AddPinPdsB(pin_h, UT_SIG_FL		     , 2);
break;
    }	//printf(" *** \n");
	UTL_SendPin                 (pin_h, "GR1CP"     );
	UTL_SendPin                 (pin_h, "GR2CP"     );
    UTL_DeleteHandle            (pin_h);
}

void pin_setting_wave(TEST_fbgarg fbgarg)
{
	UT_DUT dut;
	DutCursor dutc;
	int i;
    PinHandle pin_h;

	///////////////////////////////////
	/// DR
	///////////////////////////////////
    pin_h=UTL_GetPinHandle();
    UTL_InitializePinHandle       (pin_h);
    UTL_SetPinViNumber            (pin_h, 1);
		UTL_SetPinDrWaveform      (pin_h, UT_WAV_DNRZ);
		UTL_ClearPinPdsA            (pin_h);
		UTL_ClearPinPdsB            (pin_h);
		for(i=0; i<BITMAX; i++){
			UTL_AddPinPdsA(pin_h, UT_SIG_D (i)	     , 1);
			UTL_AddPinPdsB(pin_h, UT_SIG_SD(i)	     , 1);
break;
	    }	//printf(" *** \n");
		UTL_SendPin               (pin_h, "GR1DR"     );
		UTL_SendPin               (pin_h, "GR2DR"     );
}


static void tim_setting(TEST_fbgarg fbgarg)
{
  DSlider tck;
  TgHandle tg_h=UTL_GetTgHandle();
  int ts;
  for(ts=1;ts<=24;ts++)
  {
    tck=fbgarg.tck[ts];
//	printf("tck[%2d]:%16.9f ns\n", ts, tck*1e+9);
    UTL_AddTgRate(tg_h,ts,         tck);
    UTL_AddTgBclk(tg_h,ts, 1, tck*0/4   );
    UTL_AddTgCclk(tg_h,ts, 1, tck*2/4   );
    UTL_AddTgStrb(tg_h,ts, 1, tck/4);
  }
    UTL_SendTg(tg_h);
    UTL_DeleteHandle(tg_h);
}

void timScanStrb1(int ts, DSlider strb1_val)
{
		int h = UTL_GetTgHandle();
		UTL_AddTgStrb   (h, ts,  1, strb1_val);
		UTL_SendTg      (h);
		UTL_DeleteHandle(h);
}

/**
 * @brief Set the voltage of VI,VO and VT
*/
void lev_setting(void)
{
    ViHandle vi_h=UTL_GetViHandle();
    UTL_SetViHigh(vi_h, 1.20);
    UTL_SetViLow (vi_h, 0.20);
    UTL_SetViHvDr(vi_h, UT_OFF);
    UTL_SendVi   (vi_h, 1);
    UTL_DeleteHandle(vi_h);

    VoHandle vo_h=UTL_GetVoHandle();
    UTL_SetVoHigh(vo_h, 0.80);
    UTL_SetVoLow (vo_h, 0.60);
    UTL_SendVo   (vo_h, 1);
    UTL_DeleteHandle(vo_h);

    VtHandle vt_h=UTL_GetVtHandle();
    UTL_SetVt    (vt_h, 0.70);
    UTL_SendVt   (vt_h, 1);
    UTL_DeleteHandle(vt_h);
}

void meas_fct_with_pat(TEST_fbgarg fbgarg)
{
//	printf(" *** %s()\n", __func__);
    FctHandle fct_h=UTL_GetFctHandle();
    UTL_SetFctFailInhibit(fct_h, UT_ON          );
    UTL_SetFctStartPc    (fct_h, 0xbad          );
    UTL_SetFctNoClear    (fct_h, UT_ON          );
    UTL_MeasFct          (fct_h                 );
    UTL_DeleteHandle     (fct_h                 );
}

static void meas_fct(TEST_fbgarg fbgarg)
{
//	printf(" *** %s()\n", __func__);
    FctHandle fct_h=UTL_GetFctHandle();
    UTL_SetFctMpatName   (fct_h, fbgarg.patname[0]);
    UTL_SetFctFailInhibit(fct_h, UT_ON          );
    UTL_SetFctStartPc    (fct_h, fbgarg.pc[0]  );
    UTL_SetFctNoClear    (fct_h, UT_ON          );
    UTL_MeasFct          (fct_h                 );
    UTL_DeleteHandle     (fct_h                 );
}

void funcWithPat(char *pname, int pc)
{
	printf(" ********************************************\n");
	printf(" ***  funcWithPat(PAT:%s, PC:#%03X)\n", pname, pc);
	printf(" ********************************************\n"); fflush(stdout);
	int h = UTL_GetFctHandle();
	UTL_SetFctMpatName	(h, pname);
	UTL_SetFctFailInhibit	(h, UT_ON);
	UTL_SetFctSronInhibit	(h, UT_OFF);
	UTL_SetFctNoClear		(h, UT_ON);
	UTL_SetFctStartPc	(h, pc);
	UTL_MeasFct		(h);
	UTL_DeleteHandle	(h);
}

void meas_fct_per_group_mpatsel(TEST_fbgarg fbgarg)
{
//	printf(" *** %s(), mode:%d(UT_ON:%d, UT_OFF:%d)\n", __func__, fbgarg->mode, UT_ON, UT_OFF);
    FctHandle fct_h=UTL_GetFctHandle();
    UTL_SetFctFailInhibit         (fct_h, UT_ON          );
    UTL_SetFctNoClear             (fct_h, UT_ON          );
	UTL_SetFctFuncBlockGroupSync  (fct_h, fbgarg.mode   );

    UTL_SetFctMpatDataFileNameWithMpatSelector			(fct_h,fbgarg.patname[0],"MSEL");
    UTL_SetFctStartLabelNameOfMpatSelectorByFuncBlockGroup	(fct_h,fbgarg.patname[0],"MSEL", UT_FUNCGRP(1));
    UTL_SetFctStartLabelNameOfMpatSelectorByFuncBlockGroup	(fct_h,fbgarg.patname[1],"MSEL", UT_FUNCGRP(2));

//printf(" *** in:%s\n", __func__);
    UTL_MeasFct                   (fct_h                 );
    UTL_DeleteHandle              (fct_h                 );
}

void meas_fct_per_group(TEST_fbgarg fbgarg)
{
//	printf(" *** %s(), mode:%d(UT_ON:%d, UT_OFF:%d)\n", __func__, fbgarg->mode, UT_ON, UT_OFF);
    FctHandle fct_h=UTL_GetFctHandle();
	UTL_SetFctMpatTransferInhibit (fct_h, UT_ON          );
    UTL_SetFctFailInhibit         (fct_h, UT_ON          );
    UTL_SetFctNoClear             (fct_h, UT_ON          );
	UTL_SetFctFuncBlockGroupSync  (fct_h, fbgarg.mode   );
//printf(" *** in:%s\n", __func__);
    UTL_MeasFct                   (fct_h                 );
    UTL_DeleteHandle              (fct_h                 );
}

void meas_fct_per_group_CALM(TEST_fbgarg fbgarg)
{
//	printf(" *** %s(), mode:%d(UT_ON:%d, UT_OFF:%d)\n", __func__, fbgarg->mode, UT_ON, UT_OFF);
    FctHandle fct_h=UTL_GetFctHandle();
	UTL_SetFctMpatTransferInhibit (fct_h, UT_ON          );
    UTL_SetFctFailInhibit         (fct_h, UT_ON          );
    UTL_SetFctNoClear             (fct_h, UT_ON          );
	UTL_SetFctFuncBlockGroupSync  (fct_h, fbgarg.mode   );
//printf(" *** in:%s\n", __func__);
    UTL_MeasFct                   (fct_h                 );

    ViHandle Vi_H = UTL_GetViHandle();
    UTL_SetViHigh    (Vi_H, 0.3);
    UTL_SetViLow     (Vi_H, 0.2);
    UTL_SendVi       (Vi_H, 1);
    UTL_DeleteHandle (Vi_H);

//    if(strstr(fbgarg->testname, "CALM") != NULL){
    USlider calmflg=0;
    UTL_ReadAlpgCtrlReg(UT_REG_CALM_FLAG, &calmflg);
    if(calmflg==1){
    	UTL_WriteAlpgCtrlReg          (UT_REG_CONTINUE_FLAG, 1);
    	UTL_WriteAlpgCtrlReg          (UT_REG_CALM_FLAG, 0);
    }
    UTL_SetFctContinue            (fct_h, UT_ON);
    UTL_MeasFct                   (fct_h);

    UTL_DeleteHandle              (fct_h                 );
}

//void getFctResultDut(char *pinlst, int sampNum, unsigned int *data, UT_DUT dut) {
void getFctResultDut(char *pinlst, int sampNum, unsigned int *data) {
	UT_DUT                  dut;
	UT_PIN                  pin;
	DutCursor               dutc;
	PinCursor               pinc;
	FctReadPinHandle        fph;
	fph = UTL_GetFctReadPinHandle();
	UTL_SetFctReadPinMode(fph, UT_RES_TOTAL_FAILED);
	dutc = UTL_GetDutCursor(UT_CDUT);

	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
//masa	if(dut>=1 && dut<=3){
			UTL_SetFctReadPinDut(fph, dut);
			pinc=UTL_GetPinCursor(pinlst);
			int pinid=0;

			while ((pin=UTL_NextPin(pinc)) != UT_NOMORE) {
					UTL_SetFctReadPinNumber(fph, pin);
					data[((dut-1)*2*256*16)+(pinid*256*16)+sampNum] = UTL_ReadFctPin(fph);
//					printf("%d\n",((dut-1)*2*256*16)+(pinid*256*16)+sampNum);
					pinid++;
			}
//masa	}
	}
}

//void printFctResultDut(char *pinlst, int sampNum, unsigned int *data, DSlider sta, DSlider stp, DSlider reso, UT_DUT dut) {
void printFctResultDut(char *pinlst, int sampNum, unsigned int *data, DSlider sta, DSlider stp, DSlider reso) {
	UT_DUT                  dut;
	UT_PIN                  pin;
	DutCursor               dutc;
	PinCursor               pinc;
	DSlider                 strb;
	int pinid, i;
	dutc = UTL_GetDutCursor(UT_CDUT);
	char name[]="ShmooDiff";
	char name2[]="";
	char name3[]="";
	sprintf(name2, "%s%d", name, UTL_ReadSiteNumber());
//	printf("name2:%s\n",name2);

	printf(" *** start:   % 9.3f [ps]\n", sta*1e+12);
	printf(" *** stop :   % 9.3f [ps]\n", stp*1e+12);
	printf(" *** reso :   % 9.3f [ps]\n", reso*1e+12);
	printf(" ***                ");
	for(strb=sta; strb<stp; strb+=(reso*10)){	//print unit every 10cnt
		printf("% 10.0f", strb*1e+12);
	}	printf("[ps]\n");
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
	        	int valf[2]={0,0};
	        	int vall[2]={0,0};
//	printf("dut:%d\n",dut);
			printf(" *** dut  :   % d\n", dut);
			pinc=UTL_GetPinCursor(pinlst);
			pinid=0;

			printf(" *** pin:   (pinid:   ) data;");
			for(i=0; i<sampNum; i++){
				if(i%10==0){ printf("+"); }
				else       { printf("-"); }
			}	printf("\n");
			while ((pin=UTL_NextPin(pinc)) != UT_NOMORE) {
					int firstflg=0; int lastflg=0;
					printf(" *** pin:%3d(pinid:%3d) data:", pin, pinid);
					for(i=0; i<sampNum; i++){
					//	printf(" *** pin:%3d(pinid:%3d), sampNum:%3d, data:%d\n", pin, pinid, i, data[(pinid*256)+i]);
						if(data[((dut-1)*2*256*16)+(pinid*256*16)+i]!=0){ printf("*"); firstflg=1; vall[pinid]=i;}	//fail
						else                         			{ printf("_");}					//pass
						if(firstflg==0) valf[pinid]=i;									//first fail
					}	printf("\n");
					printf("Shmoo pass/fail transition point:%4d[cnt],%4d[cnt]\n",valf[pinid],vall[pinid]);
					if(firstflg==0 && vall[pinid]==0)printf("=>NO FAIL POINT!\n");
					if(firstflg==1 && valf[pinid]==0)printf("=>NO PASS POINT!\n");
					pinid++;
			}
		VariableHandle vh=UTL_GetVariableHandle();
		if(vall[0]==0 && vall[1]==0)				UTL_SetVariableDataSlider(vh,9999);
		else if(valf[0]==0 && valf[1]==0)			UTL_SetVariableDataSlider(vh,-1);
		else if(abs(valf[0]-valf[1]) >= abs(vall[0]-vall[1]))	UTL_SetVariableDataSlider(vh,abs(valf[0]-valf[1]));
		else							UTL_SetVariableDataSlider(vh,abs(vall[0]-vall[1]));
		sprintf(name3, "%s%d", name2, dut);
		UTL_SendVariable(vh, name3);
		UTL_DeleteHandle(vh);
	}
}

void expPASS(TEST_fbgarg fbgarg)
{
	UT_DUT                  dut;
	DutCursor               dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	RadioButton result;
	char *tname=UTL_ReadTestName();
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
//		printf("%s\tDUT:%d\t"        , UTL_ReadTestName(),dut                );
		printf("\tDUT:%d\t"        ,dut                );
		if(UTL_ReadMeasResult(dut)==UT_RES_PASSED)	{ printf("tPASS\n"); UTL_ResetTestResult(dut, tname, UT_RES_ALL); }
		else						{ printf("tFAIL\n"); UTL_SetTestResult  (dut, tname, UT_RES_ALL); }
	}
}

void expFAIL(TEST_fbgarg fbgarg)
{
	UT_DUT                  dut;
	DutCursor               dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	RadioButton result;
	char *tname=UTL_ReadTestName();
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
//		printf("%s\tDUT:%d\t"        , UTL_ReadTestName(),dut                );
		printf("\tDUT:%d\t"        , dut                );
		if(UTL_ReadMeasResult(dut)==UT_RES_FAILED)	{ printf("tPASS\n"); UTL_ResetTestResult(dut, tname, UT_RES_ALL);}
		else						{ printf("tFAIL\n"); UTL_SetTestResult  (dut, tname, UT_RES_ALL);}
	}
	UTL_DeleteCursor(dutc);
}

void regcheck(TEST_fbgarg fbgarg)
{
	UT_DUT                  dut;
	DutCursor               dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	char *tname=UTL_ReadTestName();
	int failflg=0;
//	printf("%s\t\t"        , UTL_ReadTestName()                );
	if(UT_ALPG_STPS == UTL_ReadAlpgStatus()){
		if((0xAAAA==UTL_ReadUSRegisterFuncBlockGroup(UT_REG_XB, 1, UT_FUNCGRP(1))) && (0x5555==UTL_ReadUSRegisterFuncBlockGroup(UT_REG_XB, 1, UT_FUNCGRP(2)))) {/*printf("tPASS\n");*/}
		else {/*printf("tFAIL\n");*/ failflg=1;}
	}
	else {/*printf("tFAIL\n");*/ failflg=1; }
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
		if(failflg==0) UTL_ResetTestResult(dut, tname, UT_RES_ALL);
		else           UTL_SetTestResult  (dut, tname, UT_RES_ALL);
	}
	UTL_DeleteCursor(dutc);
}

void expPASS_regcheck(TEST_fbgarg fbgarg)
{
	UT_DUT                  dut;
	DutCursor               dutc, dutc2;
	dutc = UTL_GetDutCursor(UT_CDUT);
	dutc2= UTL_GetDutCursor(UT_CDUT);
	RadioButton result;
	char *tname=UTL_ReadTestName();
	int failflg=0;
	if(UT_ALPG_STPS == UTL_ReadAlpgStatus()){
		if((0xAAAA==UTL_ReadUSRegisterFuncBlockGroup(UT_REG_XB, 1, UT_FUNCGRP(1))) && (0x5555==UTL_ReadUSRegisterFuncBlockGroup(UT_REG_XB, 1, UT_FUNCGRP(2)))){
			while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
//				printf("%s\tDUT:%d\t"        , UTL_ReadTestName(),dut                );
				printf("\tDUT:%d\t"        , dut                );
				if(UTL_ReadMeasResult(dut)==UT_RES_PASSED)	{printf("tPASS\n"); UTL_ResetTestResult(dut, tname, UT_RES_ALL);}
				else						{printf("tFAIL\n"); UTL_SetTestResult  (dut, tname, UT_RES_ALL);}
			}
		}
		else {
			//printf("%s\t", UTL_ReadTestName());
			//printf("tFAIL\n");
			failflg=1;
		}
	}
	else {
		//printf("%s\t", UTL_ReadTestName());
		//printf("tFAIL\n");
		failflg=1;
	}
	if(failflg==1){
		while ((dut=UTL_NextDut(dutc2)) != UT_NOMORE) {
			UTL_SetTestResult  (dut, tname, UT_RES_ALL);
		}
	}
	UTL_DeleteCursor(dutc);
}

void expFAIL_regcheck(TEST_fbgarg fbgarg)
{
	UT_DUT                  dut;
	DutCursor               dutc,dutc2;
	dutc = UTL_GetDutCursor(UT_CDUT);
	dutc2= UTL_GetDutCursor(UT_CDUT);
	RadioButton result;
	char *tname=UTL_ReadTestName();
	int failflg=0;
	if(UT_ALPG_STFL == UTL_ReadAlpgStatus()){
		if((0xAAAA==UTL_ReadUSRegisterFuncBlockGroup(UT_REG_XB, 1, UT_FUNCGRP(1))) && (0x5555==UTL_ReadUSRegisterFuncBlockGroup(UT_REG_XB, 1, UT_FUNCGRP(2)))){
			while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
//				printf("%s\tDUT:%d\t"        , UTL_ReadTestName(),dut                );
				printf("\tDUT:%d\t"        , dut                );
				if(UTL_ReadMeasResult(dut)==UT_RES_FAILED)	{printf("tPASS\n"); UTL_ResetTestResult(dut, tname, UT_RES_ALL);}
				else						{printf("tFAIL\n"); UTL_SetTestResult  (dut, tname, UT_RES_ALL);}
			}
		}
		else {
			//printf("%s\t", UTL_ReadTestName());
			//printf("tFAIL\n");
			failflg=1;
		}
	}
	else {
		//printf("%s\t", UTL_ReadTestName());
		//printf("tFAIL\n");
		failflg=1;
	}
	if(failflg==1){
		while ((dut=UTL_NextDut(dutc2)) != UT_NOMORE) {
			UTL_SetTestResult  (dut, tname, UT_RES_ALL);
		}
	}
	UTL_DeleteCursor(dutc);
}

void match_shmoo_check_teibai(TEST_fbgarg fbgarg)
{
	UT_DUT                  dut;
	DutCursor               dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	int data;
	char name[]="ShmooDiff";
	char name2[]="";
	char name3[]="";
	char *tname=UTL_ReadTestName();
	sprintf(name2, "%s%d", name, UTL_ReadSiteNumber());
	int xbpg1=UTL_ReadUSRegisterFuncBlockGroup(UT_REG_XB, 1, UT_FUNCGRP(1));	//exp:4 because need 0x11(0-3) * 12times(#A+2) by D0(0x1) and D1(0x10)
	int xbpg2=UTL_ReadUSRegisterFuncBlockGroup(UT_REG_XB, 1, UT_FUNCGRP(2));
	int idx4pg1=UTL_ReadUSRegisterFuncBlockGroup(UT_REG_IDX4, 1, UT_FUNCGRP(1));	//exp:4 because need 0x11(0-3) * 12times(#A+2) by D0(0x1) and D1(0x10)
	int idx4pg2=UTL_ReadUSRegisterFuncBlockGroup(UT_REG_IDX4, 1, UT_FUNCGRP(2));
	printf("XB   REG:%d(PG1),%d(PG2)\n",xbpg1, xbpg2);
	printf("IDX4 REG:%d(PG1),%d(PG2)\n",idx4pg1, idx4pg2);
	printf("Each loop increase +4cnt on XB\n");
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
		sprintf(name3, "%s%d", name2, dut);
		VariableHandle vh=UTL_GetVariableHandle();
		UTL_UpdateVariable(vh, name3);
		UTL_GetVariableDataSlider(vh,&data);
		printf("Dut%d Max Diff:%d\n",dut,data);
//		printf("%s\tDUT:%d\t"        , UTL_ReadTestName(),dut                );
		printf("\tDUT:%d\t"        , dut                );
		if(data>=0 && data<=7 && xbpg1==4*(idx4pg1+2) && xbpg2==4*(idx4pg2+2))	{printf("tPASS\n"); UTL_ResetTestResult(dut, tname, UT_RES_ALL);}
		else									{printf("tFAIL\n"); UTL_SetTestResult  (dut, tname, UT_RES_ALL);}
		UTL_DeleteHandle(vh);
	}
	UTL_DeleteCursor(dutc);
}

void shmoo_check_teibai(TEST_fbgarg fbgarg)
{
	UT_DUT                  dut;
	DutCursor               dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	int data;
	char name[]="ShmooDiff";
	char name2[]="";
	char name3[]="";
	char *tname=UTL_ReadTestName();
	sprintf(name2, "%s%d", name, UTL_ReadSiteNumber());
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
		sprintf(name3, "%s%d", name2, dut);
		VariableHandle vh=UTL_GetVariableHandle();
		UTL_UpdateVariable(vh, name3);
		UTL_GetVariableDataSlider(vh,&data);
		printf("Dut%d Max Diff:%d\n",dut,data);
//		printf("%s\tDUT:%d\t"        , UTL_ReadTestName(),dut                );
		printf("\tDUT:%d\t"        , dut                );
		if(data>=0 && data<=7)	{printf("tPASS\n"); UTL_ResetTestResult(dut, tname, UT_RES_ALL);}
		else			{printf("tFAIL\n"); UTL_SetTestResult  (dut, tname, UT_RES_ALL);}
		UTL_DeleteHandle(vh);
	}
	UTL_DeleteCursor(dutc);
}

void shmoo_check_allpass(TEST_fbgarg fbgarg)
{
	UT_DUT                  dut;
	DutCursor               dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	int data;
	char name[]="ShmooDiff";
	char name2[]="";
	char name3[]="";
	char *tname=UTL_ReadTestName();
	sprintf(name2, "%s%d", name, UTL_ReadSiteNumber());
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
		sprintf(name3, "%s%d", name2, dut);
		VariableHandle vh=UTL_GetVariableHandle();
		UTL_UpdateVariable(vh, name3);
		UTL_GetVariableDataSlider(vh,&data);
		printf("Dut%d Max Diff:%d\n",dut,data);
//		printf("%s\tDUT:%d\t"        , UTL_ReadTestName(),dut                );
		printf("\tDUT:%d\t"        , dut                );
		if(data==9999)	{printf("tPASS\n"); UTL_ResetTestResult(dut, tname, UT_RES_ALL);}
		else		{printf("tFAIL\n"); UTL_SetTestResult  (dut, tname, UT_RES_ALL);}
		UTL_DeleteHandle(vh);
	}
	UTL_DeleteCursor(dutc);
}

void shmoo_check_allfail(TEST_fbgarg fbgarg)
{
	UT_DUT                  dut;
	DutCursor               dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	int data;
	char name[]="ShmooDiff";
	char name2[]="";
	char name3[]="";
	char *tname=UTL_ReadTestName();
	sprintf(name2, "%s%d", name, UTL_ReadSiteNumber());
//	printf("name2:%s\n",name2);
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
		sprintf(name3, "%s%d", name2, dut);
		VariableHandle vh=UTL_GetVariableHandle();
		UTL_UpdateVariable(vh, name3);
		UTL_GetVariableDataSlider(vh,&data);
		printf("Dut%d Max Diff:%d\n",dut,data);
//		printf("%s\tDUT:%d\t"        , UTL_ReadTestName(),dut                );
		printf("\tDUT:%d\t"        , dut                );
		if(data==-1)	{printf("tPASS\n"); UTL_ResetTestResult(dut, tname, UT_RES_ALL);}
		else		{printf("tFAIL\n"); UTL_SetTestResult  (dut, tname, UT_RES_ALL);}
		UTL_DeleteHandle(vh);
	}
	UTL_DeleteCursor(dutc);
}

void shmoo_check_reject(TEST_fbgarg fbgarg)
{
	UT_DUT                  dut;
	DutCursor               dutc,dutc2;
	dutc = UTL_GetDutCursor(UT_CDUT);
	dutc2= UTL_GetDutCursor(UT_FDUT);	//For rejected dut need to be pass
	int data;
	char name[]="ShmooDiff";
	char name2[]="";
	char name3[]="";
	char *tname=UTL_ReadTestName();
	while ((dut=UTL_NextDut(dutc2)) != UT_NOMORE) {
		UTL_ResetTestResult(dut, tname, UT_RES_ALL);
	}
	UTL_DeleteCursor(dutc2);

	sprintf(name2, "%s%d", name, UTL_ReadSiteNumber());
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
		sprintf(name3, "%s%d", name2, dut);
		VariableHandle vh=UTL_GetVariableHandle();
		UTL_UpdateVariable(vh, name3);
		UTL_GetVariableDataSlider(vh,&data);
		printf("Dut%d Max Diff:%d\n",dut,data);
//		printf("%s\tDUT:%d\t"        , UTL_ReadTestName(),dut                );
		printf("\tDUT:%d\t"        , dut                );
		if(data>=0 && data<=303)	{printf("tPASS\n"); UTL_ResetTestResult(dut, tname, UT_RES_ALL);}
		else				{printf("tFAIL\n"); UTL_SetTestResult  (dut, tname, UT_RES_ALL);}
		UTL_DeleteHandle(vh);
	//}
	}
	UTL_DeleteCursor(dutc);
}

void shmoo_check(TEST_fbgarg fbgarg)
{
	UT_DUT                  dut;
	DutCursor               dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	int data;
	char name[]="ShmooDiff";
	char name2[]="";
	char name3[]="";
	char *tname=UTL_ReadTestName();
	sprintf(name2, "%s%d", name, UTL_ReadSiteNumber());
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
		sprintf(name3, "%s%d", name2, dut);
		VariableHandle vh=UTL_GetVariableHandle();
		UTL_UpdateVariable(vh, name3);
		UTL_GetVariableDataSlider(vh,&data);
		printf("Dut%d Max Diff:%d\n",dut,data);
//		printf("%s\tDUT:%d\t"        , UTL_ReadTestName(),dut                );
		printf("\tDUT:%d\t"        , dut                );
		if(data>=0 && data<=303)	{printf("tPASS\n"); UTL_ResetTestResult(dut, tname, UT_RES_ALL);}
		else				{printf("tFAIL\n"); UTL_SetTestResult  (dut, tname, UT_RES_ALL);}
		UTL_DeleteHandle(vh);
	}
}

void shmoo(TEST_fbgarg fbgarg)
{
	UT_DUT                  dut;
	DutCursor               dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	char *tname=UTL_ReadTestName();
	DSlider tck=fbgarg.tck[1];
	DSlider strb1_val=0, sta, stp, reso;
	int sampNum;
	USlider ddutno=UTL_GetDutCount(UT_DDUT);
	sta=0e-12; stp=tck; reso=10e-12;
	unsigned int data[ddutno*2*256*16];
	for(strb1_val=sta, sampNum=0; strb1_val<stp; strb1_val+=reso)
	{
		timScanStrb1          (1, strb1_val);
		meas_fct_per_group    (fbgarg);
       	getFctResultDut       ("CPPINS", sampNum, data);
       	sampNum++;
	}
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
		UTL_ResetTestResult(dut, tname, UT_RES_ALL);
	}
	UTL_DeleteCursor(dutc);
	printFctResultDut("CPPINS", sampNum, data, sta, stp, reso);
}

void shmoo_range(TEST_fbgarg fbgarg)
{
	UT_DUT                  dut;
	DutCursor               dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	char *tname=UTL_ReadTestName();
	DSlider tck=fbgarg.tck[1];
	DSlider strb1_val=0, sta, stp, reso;
	int sampNum;
	USlider ddutno=UTL_GetDutCount(UT_DDUT);
	sta=0e-12; stp=tck*16; reso=10e-12;
	unsigned int data[ddutno*2*256*16];
	for(strb1_val=sta, sampNum=0; strb1_val<stp; strb1_val+=reso)
	{
		timScanStrb1          (1, strb1_val);
		meas_fct_per_group    (fbgarg);
       	getFctResultDut       ("CPPINS", sampNum, data);
       	sampNum++;
	}
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
		UTL_ResetTestResult(dut, tname, UT_RES_ALL);
	}
	UTL_DeleteCursor(dutc);
	if(UTL_GetDutCount(UT_CDUT)!=UTL_GetDutCount(UT_DDUT)){
		int dutbit=0;
		UT_DUT                  dut;
		DutCursor               dutc;
		dutc = UTL_GetDutCursor(UT_CDUT);
		while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
			dutbit+=1<<(dut-1);
		}
		printf("dutbit=%x",dutbit);	fflush(stdout);
		if(dutbit == 0xfe)     { UTL_SetRejection(3, UT_ON); printf("1"); fflush(stdout);}
		else if(dutbit == 0xfd){ UTL_SetRejection(1, UT_ON); printf("2"); fflush(stdout);}
		else if(dutbit == 0xfb){ UTL_SetRejection(4, UT_ON); printf("3"); fflush(stdout);}
		else if(dutbit == 0xf7){ UTL_SetRejection(2, UT_ON); printf("4"); fflush(stdout);}
	}
	printFctResultDut("CPPINS", sampNum, data, sta, stp, reso);
}

void shmoo_range_mpatsel(TEST_fbgarg fbgarg)
{
	UT_DUT                  dut;
	DutCursor               dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	char *tname=UTL_ReadTestName();
	DSlider tck=fbgarg.tck[1];
	DSlider strb1_val=0, sta, stp, reso;
	int sampNum;
	USlider ddutno=UTL_GetDutCount(UT_DDUT);
	sta=0e-12; stp=tck*16; reso=10e-12;
	unsigned int data[ddutno*2*256*16];
	for(strb1_val=sta, sampNum=0; strb1_val<stp; strb1_val+=reso)
	{
		timScanStrb1          (1, strb1_val);
		meas_fct_per_group_mpatsel    (fbgarg);
       	getFctResultDut       ("CPPINS", sampNum, data);
       	sampNum++;
	}
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
		UTL_ResetTestResult(dut, tname, UT_RES_ALL);
	}
	UTL_DeleteCursor(dutc);
	if(UTL_GetDutCount(UT_CDUT)!=UTL_GetDutCount(UT_DDUT)){
		int dutbit=0;
		UT_DUT                  dut;
		DutCursor               dutc;
		dutc = UTL_GetDutCursor(UT_CDUT);
		while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
			dutbit+=1<<(dut-1);
		}
		printf("dutbit=%x",dutbit);	fflush(stdout);
		if(dutbit == 0xe)     { UTL_SetRejection(3, UT_ON); printf("1"); fflush(stdout);}
		else if(dutbit == 0xd){ UTL_SetRejection(1, UT_ON); printf("2"); fflush(stdout);}
		else if(dutbit == 0xb){ UTL_SetRejection(4, UT_ON); printf("3"); fflush(stdout);}
		else if(dutbit == 0x7){ UTL_SetRejection(2, UT_ON); printf("4"); fflush(stdout);}
	}
	printFctResultDut("CPPINS", sampNum, data, sta, stp, reso);
}

void shmoo_range_1pg(TEST_fbgarg fbgarg)
{

	UT_DUT                  dut;
	DutCursor               dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	char *tname=UTL_ReadTestName();
	DSlider tck=fbgarg.tck[1];
	DSlider strb1_val=0, sta, stp, reso;
	int sampNum;
	USlider ddutno=UTL_GetDutCount(UT_DDUT);
	sta=0e-12; stp=tck*16; reso=10e-12;
	unsigned int data[ddutno*2*256*16];
	for(strb1_val=sta, sampNum=0; strb1_val<stp; strb1_val+=reso)
	{
		timScanStrb1          (1, strb1_val);
		meas_fct              (fbgarg);
       	getFctResultDut       ("CPPINS", sampNum, data);
       	sampNum++;
	}
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
		UTL_ResetTestResult(dut, tname, UT_RES_ALL);
	}
	UTL_DeleteCursor(dutc);
	printFctResultDut("CPPINS", sampNum, data, sta, stp, reso);
}

void shmoo_range_CALM(TEST_fbgarg fbgarg)
{

	UT_DUT                  dut;
	DutCursor               dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	char *tname=UTL_ReadTestName();
	DSlider tck=fbgarg.tck[1];
	DSlider strb1_val=0, sta, stp, reso;
	int sampNum;
	USlider ddutno=UTL_GetDutCount(UT_DDUT);
	sta=0e-12; stp=tck*16; reso=10e-12;
	unsigned int data[ddutno*2*256*16];
	for(strb1_val=sta, sampNum=0; strb1_val<stp; strb1_val+=reso)
	{
		lev_setting          ();
		timScanStrb1          (1, strb1_val);
		meas_fct_per_group_CALM(fbgarg);
       	getFctResultDut       ("CPPINS", sampNum, data);
       	sampNum++;
	}
	if(UTL_GetDutCount(UT_CDUT)!=UTL_GetDutCount(UT_DDUT)){
		int dutbit=0;
		UT_DUT                  dut;
		DutCursor               dutc;
		dutc = UTL_GetDutCursor(UT_CDUT);
		while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
			dutbit+=1<<(dut-1);
		}
		printf("dutbit=%x",dutbit);	fflush(stdout);
		if(dutbit == 0xe)     { UTL_SetRejection(3, UT_ON); printf("1"); fflush(stdout);}
		else if(dutbit == 0xd){ UTL_SetRejection(1, UT_ON); printf("2"); fflush(stdout);}
		else if(dutbit == 0xb){ UTL_SetRejection(4, UT_ON); printf("3"); fflush(stdout);}
		else if(dutbit == 0x7){ UTL_SetRejection(2, UT_ON); printf("4"); fflush(stdout);}
	}
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
		UTL_ResetTestResult(dut, tname, UT_RES_ALL);
	}
	UTL_DeleteCursor(dutc);
	printFctResultDut("CPPINS", sampNum, data, sta, stp, reso);
}

void shmoo_range_DBM(TEST_fbgarg fbgarg)
{

	UT_DUT                  dut;
	DutCursor               dutc;
	dutc = UTL_GetDutCursor(UT_CDUT);
	char *tname=UTL_ReadTestName();
	dbm_setting();
	dbm_write();
	DSlider tck=fbgarg.tck[1];
	DSlider strb1_val=0, sta, stp, reso;
	int sampNum;
	USlider ddutno=UTL_GetDutCount(UT_DDUT);
	sta=0e-12; stp=tck*16; reso=10e-12;
	unsigned int data[ddutno*2*256*16];
	for(strb1_val=sta, sampNum=0; strb1_val<stp; strb1_val+=reso)
	{
		timScanStrb1          (1, strb1_val);
		meas_fct_per_group    (fbgarg);
       	getFctResultDut       ("CPPINS", sampNum, data);
       	sampNum++;
	}
	if(UTL_GetDutCount(UT_CDUT)!=UTL_GetDutCount(UT_DDUT)){
		int dutbit=0;
		UT_DUT                  dut;
		DutCursor               dutc;
		dutc = UTL_GetDutCursor(UT_CDUT);
		while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
			dutbit+=1<<(dut-1);
		}
		printf("dutbit=%x",dutbit);	fflush(stdout);
		if(dutbit == 0xe)     { UTL_SetRejection(3, UT_ON); printf("1"); fflush(stdout);}
		else if(dutbit == 0xd){ UTL_SetRejection(1, UT_ON); printf("2"); fflush(stdout);}
		else if(dutbit == 0xb){ UTL_SetRejection(4, UT_ON); printf("3"); fflush(stdout);}
		else if(dutbit == 0x7){ UTL_SetRejection(2, UT_ON); printf("4"); fflush(stdout);}
	}
	while ((dut=UTL_NextDut(dutc)) != UT_NOMORE) {
		UTL_ResetTestResult(dut, tname, UT_RES_ALL);
	}
	UTL_DeleteCursor(dutc);
	printFctResultDut("CPPINS", sampNum, data, sta, stp, reso);
}

void outsync_wave(TEST_testitem *testarg)
{
    FBGdisplay_header       (FBGARG);
	pinlist_drcp         ();
	ilmode_setting       (FBGARG);
    pin_setting_wave     (FBGARG);
	tim_setting          (FBGARG);
	lev_setting          ();
	func_block_group     (FBGARG);
    send_mpat_per_group  (FBGARG);
    cal                  ();
    meas_fct_per_group   (FBGARG);
    FBGARG.post         (FBGARG);
}

void common_pg(TEST_testitem *testarg)
{
    FBGdisplay_header       (FBGARG);
	pinlist_drcp         ();
	ilmode_setting       (FBGARG);
    if(FBGARG.patname[0]=="pat2")	pin_setting_FL          (FBGARG);
    else				pin_setting             (FBGARG);
	tim_setting          (FBGARG);
	lev_setting          ();
    cal                  ();
    FBGARG.pre          (FBGARG);
    FBGARG.post         (FBGARG);
}

void outsync_8grp(TEST_testitem *testarg)
{
    FBGdisplay_header       (FBGARG);
	pinlist_drcp         ();
	ilmode_setting       (FBGARG);
    	pin_setting             (FBGARG);
	tim_setting          (FBGARG);
	lev_setting          ();
	func_block_group     (FBGARG);
    	send_mpat_per_group  (FBGARG);
    cal                  ();
    FBGARG.pre          (FBGARG);
    FBGARG.post         (FBGARG);
}

void outsync(TEST_testitem *testarg)
{
    FBGdisplay_header       (FBGARG);
	pinlist_drcp         ();
	ilmode_setting       (FBGARG);
    	pin_setting_FL          (FBGARG);
	tim_setting          (FBGARG);
	lev_setting          ();
	func_block_group     (FBGARG);
    	send_mpat_per_group  (FBGARG);
    cal                  ();
    FBGARG.pre          (FBGARG);
    FBGARG.post         (FBGARG);
}

void outsync_sel(TEST_testitem *testarg)
{
    FBGdisplay_header       (FBGARG);
	pinlist_drcp         ();
	ilmode_setting       (FBGARG);
    	pin_setting_FL          (FBGARG);
	tim_setting          (FBGARG);
	lev_setting          ();
	func_block_group     (FBGARG);
	send_mpat_sel_per_group (FBGARG);
    cal                  ();
    FBGARG.pre          (FBGARG);
    FBGARG.post         (FBGARG);
}

void outsync_match(TEST_testitem *testarg)
{
    FBGdisplay_header       (FBGARG);
	pinlist_drcp         ();
	ilmode_setting       (FBGARG);
    pin_setting_match    (FBGARG);
	tim_setting          (FBGARG);
	lev_setting          ();
	func_block_group     (FBGARG);
    send_mpat_per_group  (FBGARG);
    cal                  ();
    match		 (FBGARG);
    FBGARG.pre          (FBGARG);
    FBGARG.post         (FBGARG);
}

void outsync_multi(TEST_testitem *testarg)
{
    int i;
    FBGdisplay_header       (FBGARG);
	pinlist_drcp         ();
	ilmode_setting       (FBGARG);
    	pin_setting_FL          (FBGARG);
	tim_setting          (FBGARG);
	lev_setting          ();
	func_block_group     (FBGARG);
    send_mpat_per_group  (FBGARG);
    cal                  ();
    for(i=0; i<100; i++){
        FBGARG.pre          (FBGARG);
        FBGARG.post         (FBGARG);
    }
}

void outsync_rej_1(TEST_testitem *testarg)
{
    FBGdisplay_header       (FBGARG);
    UTL_SetRejection     (1, UT_ON);	printf("Reject DUT1\n");	//affect to DUT4 result
	pinlist_drcp         ();
	ilmode_setting       (FBGARG);
    	pin_setting_FL          (FBGARG);
	tim_setting          (FBGARG);
	lev_setting          ();
	func_block_group     (FBGARG);
    send_mpat_per_group  (FBGARG);
    cal                  ();
    FBGARG.pre          (FBGARG);
    FBGARG.post         (FBGARG);
}

void outsync_rej_3(TEST_testitem *testarg)
{
    FBGdisplay_header       (FBGARG);
    UTL_SetRejection     (3, UT_ON);	printf("Reject DUT3\n");	//affect to DUT4 result
	pinlist_drcp         ();
	ilmode_setting       (FBGARG);
    	pin_setting_FL          (FBGARG);
	tim_setting          (FBGARG);
	lev_setting          ();
	func_block_group     (FBGARG);
    send_mpat_per_group  (FBGARG);
    cal                  ();
    FBGARG.pre          (FBGARG);
    FBGARG.post         (FBGARG);
}

