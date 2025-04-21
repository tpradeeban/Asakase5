#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "UTSC.h"
#include "test.h"
#include "test_struct.h"
#include "common.h"
#include "multipg.h"
bool flg_info=0;
int result_bit=0b01111111;	//Set 1 for the number of items in 32bit.

void multipg_check(TEST_testitem *testarg) {
//!:comment out
  printf("\n#Test###################################################\n%s\n",testarg->testname);
  display_revInfo();
  printf("\n#Condition#\nMax PG        :%d\nIOM assignment:%d (0:ALL, 1:LTD)\n", MULTIPGARG.max_pg, MULTIPGARG.flg_asg);
  set_pl();
  set_il(8);
  set_lv(1, 1.0, 0.0, 0.5, 0.5, 0.0);		//phase, vih/l, voh/l, vt
  set_timing(1, 100e-6, 1, 0.0, 0.5);		//ts, rate, clk, b_ratio, c_ratio
  int i; char pl[8];
  for (i=1; i<=SOCKET.dutblock_count; i++) {	//i=0~max_IOMs, IOM1-8->ALLPIN
    sprintf(pl, "IOM%d", i);
    set_pin_cond(pl, 1, UT_WAV_FIXL, 1, 1, 1);	//*pinlist, vi, wave, b/cclk, vo
  }
  set_match_pin(MULTIPGARG.max_pg);		//For match(FLGLI)-check

  //Make ary for IOM assignment to PG
  int pgs, ioms, assign;		//pgs:PGs, ioms:IOMs, assign:assignment PG-IOM
  int pg_iom[8][8]={0};			//[row][column]=[PG][IOM]. 0:Not assigned, 1:Assigned.
  for (pgs=1; pgs<=MULTIPGARG.max_pg; pgs++) {
    if (MULTIPGARG.max_pg==2) { 								//2PG, USECASE
      for (ioms=1; ioms<=SOCKET.dutblock_count; ioms++) {
        if      (pgs==1 && ioms!=3 && ioms!=4) { pg_iom[pgs-1][ioms-1]=1; }	//PG1:IOM1,2,5,6,7,8
        else if (pgs==2 && ioms==3 || ioms==4) { pg_iom[pgs-1][ioms-1]=1; }	//PG2:IOM3,4
        //printf("\n(pg%d, iom%d)=%d",pgs,ioms,pg_iom[pgs-1][ioms-1]);fflush(stdout);
      }
    } else if (MULTIPGARG.max_pg>=3 && MULTIPGARG.max_pg<=8 && MULTIPGARG.flg_asg==ALL) {	//3-8PG, ALL
      for (ioms=1; ioms<=SOCKET.dutblock_count; ioms++) {
        assign=ioms%MULTIPGARG.max_pg;
        if      (assign> 0) { pg_iom[assign-1][ioms-1]=1;            }
        else if (assign==0) { pg_iom[MULTIPGARG.max_pg-1][ioms-1]=1; }
        else { printf("[ERR] Incorrect IOM mod max PG number (=%d).", assign);fflush(stdout); }
        //printf("\n(pg%d, iom%d)=%d",pgs,ioms,pg_iom[pgs-1][ioms-1]);fflush(stdout);
      }
    } else if (MULTIPGARG.max_pg>=3 && MULTIPGARG.max_pg<=8 && MULTIPGARG.flg_asg==LTD) {	//3-8PG, LTD
      for (ioms=1; ioms<=SOCKET.dutblock_count; ioms++) {
        if (pgs==ioms) { pg_iom[pgs-1][ioms-1]=1; }
        //printf("\n(pg%d, iom%d)=%d",pgs,ioms,pg_iom[pgs-1][ioms-1]);fflush(stdout);
      }
    } else { printf("[ERR] Incorrect max PG number (=%d).", MULTIPGARG.max_pg);fflush(stdout); }
  }

send_as_1pg(testarg->testname);	//!:Workaround for hang-up when LTD->ALL

  set_multipg(MULTIPGARG.max_pg, pg_iom, 8);	//arg3:column of 2d-ary, thus pg_iom["8"][8]
  UTL_ExecSbcal("calfile", "NORMAL NOMBIDCHK NOPBIDCHK NOMBLOCKCHK NOMBTYPECHK NOPBLOCKCHK");
  MULTIPGARG.multipg_func(MULTIPGARG.max_pg);	//sendmpa(), mpatsel()

  //Skip match-check by CFLG1 when LTD and USECASE
  if (MULTIPGARG.flg_asg==LTD || MULTIPGARG.max_pg==2) {
    for (pgs=1; pgs<=MULTIPGARG.max_pg; pgs++) { write_reg_us(UT_REG_CFLG, 0x0001, 1, pgs); }
    if (MULTIPGARG.flg_asg==LTD) { printf("\n\n#Skip FLGLI when LTD because of hang-up#");fflush(stdout); }
    if (MULTIPGARG.max_pg==2)    { printf("\n\n#Skip FLGLI when USECASE because of special case#");fflush(stdout); }
  }

  meas(MULTIPGARG.max_pg, testarg->testname);
  judge_match(MULTIPGARG.max_pg, MULTIPGARG.flg_asg);
  judge_meas_result(MULTIPGARG.max_pg, pg_iom, 8, MULTIPGARG.flg_asg, testarg->testname);

  check_reg_us(MULTIPGARG.max_pg);
  check_reg_rb(MULTIPGARG.max_pg);

  judge_final_result(testarg->testname);

send_as_1pg(testarg->testname);	//!:Workaround for hang-up when ALL->LTD
}

void printb(int val, int flg_show) {	//printb(val,0);, arg2=1->all_bits, 0(or None)->the_lower_8bits
  int i;
  int bits = sizeof(int)*8;
  printf("0b");
  if (flg_show) { for (i=bits-1; i>=0; i--) { putchar(val & (1<<i)?'1':'0'); } }
  else          { for (i=7;      i>=0; i--) { putchar(val & (1<<i)?'1':'0'); } }
}

void display_revInfo() {
  if (flg_info==0) {
    printf("#Info#\n");fflush(stdout);
    printf("DATE :");fflush(stdout);system("date +%Y%m%d%H%M"); 
    printf("OS   :");fflush(stdout);system("echo $ATFSSYS\n"); 
    printf("DIAG :");fflush(stdout);system("echo $ATFSDIAG\n"); 
    flg_info=1;
////[jikken] MAXBLKCNT=the num of IOM, MAXBLKIOCNT=?, MAXDUTCNT=?, MAXIOPINNO=?
//printf("\n");fflush(stdout);										//	iom:8,   7
//printf("dut_iopin_count                       =%03d\n", SOCKET.dut_iopin_count);	fflush(stdout);	//072, 063	//pins/dut
//printf("dutblock_count                        =%03d\n", SOCKET.dutblock_count);		fflush(stdout);	//008, 007	//the num of IOM
//printf("dutblock_iopin_count[MAXBLKCNT]       =%03d\n", SOCKET.dutblock_iopin_count[1]);fflush(stdout);	//009, 009	//pins/IOM"n" in dut?
//printf("dutblock_iopin[MAXBLKCNT][MAXBLKIOCNT]=%03d\n", SOCKET.dutblock_iopin[1][1]);	fflush(stdout);	//066, 066
//printf("char *dutblock_iopinlist[MAXBLKCNT]   =%03d\n", SOCKET.dut_iopin_count);	fflush(stdout);	//072, 063
//printf("char *all_iopinlist                   =%s\n"  , SOCKET.all_iopinlist);		fflush(stdout);	//ALL_IOPIN
//printf("dut_child[MAXDUTCNT+1]                =%03d\n", SOCKET.dut_child[1+1]);		fflush(stdout);	//000, 000
//printf("testeriopin[MAXDUTCNT+1][MAXIOPINNO+1]=%0d3\n", SOCKET.testeriopin[1+1][1+1]);	fflush(stdout);	//113, 113
  }
}

void set_pl() {
  int i, j;
  char pl_name[8];

  UTL_CreatePinList("ALLPIN");
  UTL_SetPinType("ALLPIN", UT_PINTYPE_PIN);

  for (i=1; i<=8; i++) {			//IOM1-8
    sprintf(pl_name, "IOM%d", i);
    UTL_CreatePinList(pl_name);
    UTL_SetPinType   (pl_name, UT_PINTYPE_PIN);
    for (j=1+64*(i-1); j<=9+64*(i-1); j++) {	//01-09,65-73,...449-457 (ref: DUT# in soc)
      UTL_AddPinNumber(pl_name, j);
    }
    UTL_AppendPinList("ALLPIN", pl_name);	//IOM1-8 -> ALLPIN
  }
}

void set_il(unsigned int il_num) {
  int h_il = UTL_GetIlModeHandle();
  UTL_SetIlMode   (h_il,il_num);
  UTL_SendIlMode  (h_il);
  UTL_DeleteHandle(h_il);
}

void set_lv(unsigned int phase, double vih, double vil, double voh, double vol, double vt) {
  ViHandle h_vi = UTL_GetViHandle();
  UTL_SetViHigh    (h_vi, vih);
  UTL_SetViLow     (h_vi, vil);
  UTL_SendVi       (h_vi, phase);
  UTL_DeleteHandle (h_vi);

  VoHandle h_vo = UTL_GetVoHandle();
  UTL_SetVoHigh    (h_vo, voh);
  UTL_SetVoLow     (h_vo, vol);
  UTL_SendVo       (h_vo, phase);
  UTL_DeleteHandle (h_vo);

  VtHandle h_vt = UTL_GetVtHandle();
  UTL_SetVt        (h_vt, vt);
  UTL_SendVt       (h_vt, phase);
  UTL_DeleteHandle (h_vt);
  printf("\n#Level#\nvih=%.2fV\nvil=%.2fV\nvoh=%.2fV\nvol=%.2fV\nvt =%.2fV\n",vih,vil,voh,vol,vt);fflush(stdout);
}

void set_timing(unsigned int ts, double rate, unsigned int clk, double b_ratio, double c_ratio) {
  TgHandle h_tg = UTL_GetTgHandle();
  UTL_AddTgRate    (h_tg, ts, rate);
  UTL_AddTgBclk    (h_tg, ts, clk, rate*b_ratio);
  UTL_AddTgCclk    (h_tg, ts, clk, rate*c_ratio);
  UTL_AddTgStrb    (h_tg, ts, clk, rate*0.75);		//double strb1_ratio;
  UTL_AddTgDreL    (h_tg, ts, 1, rate*0.0);		//double drel1_ratio;
  UTL_AddTgDreT    (h_tg, ts, 1, rate*0.0);		//double dret1_ratio;
  UTL_SendTg       (h_tg);
  UTL_DeleteHandle (h_tg);
  printf("\n#Timing#\nrate=%6.2fus\nbclk=%6.2fus\ncclk=%6.2fus\nstrb=%6.2fus\n",rate*1e+6,rate*1e+6*b_ratio,rate*1e+6*c_ratio,rate*1e+6*0.25);fflush(stdout);
}

void set_pin_cond (char *pinlist, unsigned int vi, unsigned int wave, unsigned int bclk, unsigned int cclk, unsigned int vo) {
  PinHandle h_pin = UTL_GetPinHandle();
  UTL_InitializePinHandle (h_pin);
  UTL_SetPinViNumber      (h_pin, vi);
  UTL_SetPinDrWaveform    (h_pin, wave);		//ex) UT_WAV_RZO
  UTL_SetPinDrClock       (h_pin, UT_PIN_BCLK, bclk);
  UTL_SetPinDrClock       (h_pin, UT_PIN_CCLK, cclk);
  UTL_SetPinIoCtrl        (h_pin, UT_ON);		//unsigned int ioc;
  //UTL_SetPinInit         (h_pin, UT_PIN_LINIT);	//Dr's init state. UT_PIN_DEFAULT/HIMIT/LINIT

  UTL_SetPinVoNumber      (h_pin, vo);
  UTL_SetPinTerm          (h_pin, UT_ON);		//50ohm term.
  UTL_SetPinVtNumber      (h_pin, 1);			//unsigned int vt_num;
  UTL_SetPinDreNumber     (h_pin, 1);			//unsigned int dre;
  UTL_SetPinDreWaveform   (h_pin, UT_DREWAV_NRZ);	//unsigned int dre_wave; //ex.) UT_DREWAV_NRZ
  UTL_SetPinDreClock      (h_pin, 1);			//unsigned int dreclk;
  UTL_AddPinStrbCpeNumber (h_pin, 1, 1);		//unsigned int strb1; //strb2 if ddr
  UTL_AddPinStrbChannel   (h_pin, 1, 1);
  UTL_AddPinExpStrbNumber (h_pin, 1, UT_PIN_EXP_A);
  
  int sig_num;
  for (sig_num=0; sig_num<SOCKET.dutblock_iopin_count[1]; sig_num++){
    UTL_AddPinPdsA  (h_pin, UT_SIG_D(sig_num), 1);
  }
  UTL_SendPin     (h_pin, pinlist);
  UTL_DeleteHandle(h_pin);
}

void set_match_pin(int max_pg) {
  if (max_pg!=2) {
    int pg;
    int match_pins[8]={1,66,131,196,261,326,391,456};
    char pinlist[16];
    PinHandle h_pin = UTL_GetPinHandle();
  
    for (pg=1; pg<=max_pg; pg++) {
      sprintf(pinlist, "");
      sprintf(pinlist, "MATCHPIN%d", pg);
      UTL_CreatePinList  (pinlist);
      UTL_SetPinType     (pinlist, UT_PINTYPE_PIN);
      UTL_AddPinNumber   (pinlist, match_pins[pg-1]);
  
      UTL_SetPinSendMode (h_pin, UT_PIN_PART);
      UTL_SetPinMatchMode(h_pin, UT_SIG_MATCH);
      UTL_SendPin        (h_pin, pinlist);
    }
    UTL_DeleteHandle   (h_pin);
  }
}

void set_multipg(int max_pg, int ary[][8], int max_row) {
  int elem_pg, elem_iom;				//PG or IOM elements of the ary as arg2
  FuncBlockGroupHandle h_fbg=UTL_GetFuncBlockGroupHandle();
  
  printf("\n#IOM assignment to PG#");fflush(stdout);
  for (elem_pg=1; elem_pg<=max_pg; elem_pg++) {
    printf("\nPG%d: ",elem_pg);fflush(stdout);
    for (elem_iom=1; elem_iom<=max_row; elem_iom++) {	//max_row=max_col cuz of max_pg=max_iom in T5835
      if (ary[elem_pg-1][elem_iom-1]==1) { 
        UTL_AddFuncBlockGroupTargetBlock(h_fbg, elem_iom);
        printf("IOM%d ",elem_iom);fflush(stdout);
      }
    }
    UTL_SendFuncBlockGroup (h_fbg, UT_FUNCGRP(elem_pg));
    UTL_ClearFuncBlockGroup(h_fbg);
  }
  UTL_DeleteHandle(h_fbg);
}

void sendmpa(int max_pg) {
  int i;
  char pat_name[64]="";
  MpatHandle h_sendmpa=UTL_GetMpatHandle();
  printf("\n\n#Pattern#");fflush(stdout);
  for (i=1; i<=max_pg; i++) {
    sprintf(pat_name, "pat_multipg_sendmpa_%d.mpa", i);
    printf("\nPG%d: %s, pc#%d",i,pat_name,i);fflush(stdout);
    UTL_SetMpatFuncBlockGroup (h_sendmpa, UT_FUNCGRP(i));
    UTL_SetMpatFileName       (h_sendmpa, pat_name);
    UTL_SetMpatStartPc        (h_sendmpa, i);
    UTL_SendMpat              (h_sendmpa); 
  }
  UTL_DeleteHandle (h_sendmpa);

  //The following are for MpatSel's tests.
  result_bit &= ~(1<<0);	//Set 0 to 1bit
  result_bit &= ~(1<<1);	//Set 0 to 2bit
}

void display_mpatsel(int pg_num, int flg_target) {
  char pat_name[256];
  char label_name[16];
  int pc_num;
  MpatSelectorHandle mpsh = UTL_GetMpatSelectorHandle();
  UTL_SetMpatSelectorFuncBlockGroup(mpsh, UT_FUNCGRP(pg_num));
  UTL_UpdateMpatSelector(mpsh);

  MpatSelector *mpsel;
  MpatSelectorCursor mpsc = UTL_GetMpatSelectorCursor(mpsh);  
  while((mpsel=UTL_NextMpatSelector(mpsc))!=NULL) {
    printf("PG%d: %s, %s, (PC#%03x, PatCount:%d)\n",pg_num, mpsel->FileName, mpsel->label, mpsel->pc, mpsel->PatCount);fflush(stdout);
    strcpy(pat_name, mpsel->FileName);
    strcpy(label_name, mpsel->label); 
    pc_num=mpsel->pc;
  }
  UTL_DeleteCursor(mpsc);
  UTL_DeleteHandle(mpsh);
  
  //Check UpdateMpatSel and ResetMpatSel
  if (flg_target==1) {	//Check UTL_UpdateMpatSelector
    if (strstr(pat_name, "dummy")) {
      printf("[OK] UTL_UpdateMpatSelector\n");fflush(stdout);
      result_bit &= ~(1<<0);	//Set 0 to 1bit
    } else {
      printf("[NG] UTL_UpdateMpatSelector\n");fflush(stdout);
    }
  } else if (flg_target==2) {	//Check UTL_ResetMpatSelector
    if (!pat_name || !strlen(pat_name)) {
      printf("[OK] UTL_ResetMpatSelector\n");fflush(stdout);
      result_bit &= ~(1<<1);	//Set 0 to 2bit
    } else { 
      printf("[NG] UTL_ResetMpatSelector\n");fflush(stdout);
    }
  }
}

void mpatsel(int max_pg) {
  int i;
  char pat_name[64]="";
  char label_name1[64]="";
  char label_name2[64]="";	//for labels not used
  MpatSelectorHandle h_mpatsel=UTL_GetMpatSelectorHandle();
  printf("\n\n#Pattern, Label#\n");fflush(stdout);
  for (i=1; i<=max_pg; i++) {
    sprintf(pat_name, "pat_multipg_mpatsel_%d.mpa", i);
    sprintf(label_name1, "LABEL%d", i);
    sprintf(label_name2, "LABEL%d", i+10*i);

    //Check UpdateMpatSel w/ dummy-pat.
    UTL_SetMpatSelectorFuncBlockGroup(h_mpatsel, UT_FUNCGRP(i));
    UTL_ClearMpatSelector            (h_mpatsel);
    UTL_AddMpatSelector              (h_mpatsel, "pat_multipg_mpatsel_dummy.mpa", "DUMMY");
    UTL_SendMpatSelector             (h_mpatsel);
    UTL_UpdateMpatSelector           (h_mpatsel);
    printf("<Update>\n");fflush(stdout);display_mpatsel(i, 1);
    
    //Check RestMpatSel.
    UTL_SetMpatSelectorFuncBlockGroup(h_mpatsel, UT_FUNCGRP(i));
    UTL_ClearMpatSelector            (h_mpatsel);
    UTL_ResetMpatSelector            (h_mpatsel);
    UTL_SendMpatSelector             (h_mpatsel);
    UTL_UpdateMpatSelector           (h_mpatsel);
    printf("<Reset>\n");fflush(stdout);display_mpatsel(i, 2);

    //Set pat-files for measurement.
    UTL_SetMpatSelectorFuncBlockGroup(h_mpatsel, UT_FUNCGRP(i));
    UTL_ClearMpatSelector            (h_mpatsel);			//clear pat-file and label in the handle.
    UTL_AddMpatSelector              (h_mpatsel, pat_name, label_name1);
    UTL_AddMpatSelector              (h_mpatsel, pat_name, label_name2);//Transfer this a pattern never used.
    UTL_SendMpatSelector             (h_mpatsel);
    printf("<SetMpatSel>\n");fflush(stdout);display_mpatsel(i, 0);printf("\n");fflush(stdout);
  }
  UTL_DeleteHandle (h_mpatsel);
}

void meas(int max_pg, char *testname) {
  FctHandle h_fct = UTL_GetFctHandle();
  UTL_SetFctFailInhibit(h_fct, UT_ON);
  printf("\n\n#Transfer mode#\n");fflush(stdout);
  if (strstr(testname, "SENDMPA")) {
    printf("sendmpat");fflush(stdout);
    UTL_SetFctMpatTransferInhibit(h_fct, UT_ON);	//To not overwrite multipg settings.
  } else if (strstr(testname, "MPATSEL")) {
    printf("mpatsel");fflush(stdout);
    UTL_SetFctMpatTransferInhibit(h_fct, UT_OFF);
    int i; char pat[64], label[64];
    for (i=1; i<=max_pg; i++) {
      sprintf(pat, "pat_multipg_mpatsel_%d.mpa", i);
      sprintf(label, "LABEL%d", i);
      UTL_SetFctStartLabelNameOfMpatSelectorByFuncBlockGroup(h_fct, pat, label, UT_FUNCGRP(i));
    }
    UTL_SetFctMpatDataFileNameWithMpatSelector(h_fct, "pat_multipg_mpatsel_1.mpa", "LABEL1");	//For RESISTER
  }
  UTL_MeasFct      (h_fct);
  UTL_DeleteHandle (h_fct);
}

void judge_match(int max_pg, int flg_asg) {
  int i, yb, idx8, xh;
  int match_lp[2];	//=XC
  int match_result=1;
  bool reach_result=1;

  for (i=1; i<=max_pg; i++) {
    yb  =read_reg_us("YB"  , UT_REG_YB  , 1, i, 0);	//(CFLG1,YB) = Check(0,3), NotCheck(1,1)
    idx8=read_reg_us("IDX8", UT_REG_IDX8, 1, i, 0);
    xh  =read_reg_us("XH"  , UT_REG_XH  , 1, i, 0);

    if (i==1) { 
      match_lp[0]=read_reg_us("XC", UT_REG_XC, 1, i, 1);
    } else if (i>=2) {
      match_lp[1]=match_lp[0];
      match_lp[0]=read_reg_us("XC", UT_REG_XC, 1, i, 1);
    }
    //Check the num of FLGLI loop of each PG when ALL.
    if (flg_asg==ALL && i>=2) {
      if      (match_lp[0]!=match_lp[1]) { match_result=1; }	//ng1
      else if (yb==1)                    { match_result=2; }	//ng2
      else if (match_lp[0]>=idx8)        { match_result=3; }	//ng3
      else                               { match_result=0; }	//ok
    }
    //Check if each pat has reach STPS.
    if (xh==1) { reach_result=0; } //ok
    else       { reach_result=1; } //ng
  }

  //Judge the num of FLGLI loop of each PG when ALL.
  if (flg_asg==ALL) {
    if (match_result==0) {
      printf("\n[OK] FLGLI loops of each PG matched.");fflush(stdout);
      result_bit &= ~(1<<2);	//Set 0 to 3bit
    } else if (match_result==1) {
      printf("\n[NG] FLGLI loops of each PG did not match.");fflush(stdout);
    } else if (match_result==2) {
      printf("\n[NG] Skip FLGLI because YB=0x%x (Exp=0x3).",yb);fflush(stdout);
    } else if (match_result==3) {
      printf("\n[NG] Unmatched (FLGLI_loops>=IDX8).");fflush(stdout);
    }
  } else {	//Skip match-check when LTD
    result_bit &= ~(1<<2);	//Set 0 to 3bit
  }
  //Judge if each pat has reach STPS.
  if (reach_result==0) {
    printf("\n[OK] Reaching STPS.");fflush(stdout);
    result_bit &= ~(1<<3);	//Set 0 to 4bit
  } else {
    printf("\n[NG] Reaching STPS.");fflush(stdout);
  }
}


void judge_meas_result(int max_pg, int arr[][8], int max_x, int flg_assign, char *testname) {
  int pg, iom, max_pin, pin, target_pin, dut;
  UT_PIN cur_pin;
  int dutmax=UTL_GetDutCount(UT_DDUT);
  char pinlist_name[8];
  bool pin_result[dutmax];
  bool meas_result=1;			//init state is pass(=1).
  
  printf("\n\n#Judge P/F#");fflush(stdout);
  FctReadPinHandle h_rp = UTL_GetFctReadPinHandle();
  for (pg=1; pg<=max_pg; pg++) {
    for (iom=1; iom<=max_x; iom++) {	//max_x=max_y cuz of max_pg=max_iom in T5835
      if (max_pg==2 && arr[pg-1][iom-1]==1) { max_pin=pg;         }
      else if (max_pg>=3 && max_pg<=8     ) { max_pin=(iom%max_pg==0)? max_pg:(iom%max_pg); }
      //skip conditions
      if (max_pg==2 && pg==1 && (iom==3 || iom==4)) { continue; }
      if (max_pg==2 && pg==2 && (iom!=3 && iom!=4)) { continue; }
      if (max_pg>=3 && max_pg<=8 && flg_assign==0 && pg!=max_pin ) { continue; }  //Other than "PGn:IOMm(n)" when ALL
      if (max_pg>=3 && max_pg<=8 && flg_assign==1 && pg!=iom     ) { continue; }  //When LTD
      //select a pin to read p/f
      sprintf(pinlist_name, "IOM%d", iom);
      cur_pin=UTL_GetPinCursor(pinlist_name);
      for (pin=1; pin<=max_pin; pin++) { target_pin=UTL_NextPin(cur_pin); }
      UTL_SetFctReadPinNumber(h_rp, target_pin);
      UTL_DeleteCursor(cur_pin);
      //dut loop
      for (dut=1; dut<=dutmax; dut++) {
        UTL_SetFctReadPinDut(h_rp, dut);
        pin_result[dut] = UTL_ReadFctPin(h_rp);		//1:FAIL, 0:PASS
        meas_result &= pin_result[dut];			//Test=PASS(meas_result=1) when Pin=FAIL(pin_result=1)
        if (meas_result==1) {
          UTL_ResetTestResult(dut, testname, UT_RES_ALL);
          result_bit &= ~(1<<4);	//Set 0 to 5bit
        } else {
          UTL_SetTestResult (dut, testname, UT_RES_ALL);
          printf("\n[NG] DUT%d, P%03d isn't as expected!\n", dut, target_pin);fflush(stdout);
        }
        printf("\nPG%d, IOM%d(%d), P%03d, DUT%d, pin_result=%d, meas_result=%d", pg, iom, max_pin, target_pin, dut, pin_result[dut], meas_result);fflush(stdout);
      }
    } 
  } UTL_DeleteHandle(h_rp);
}

void wr_reg_us(char *reg_name, unsigned int reg, int *p_val, int size, int pg_num) {
  unsigned int reg_us;
  UTL_WriteRegUsFuncBlockGroup(reg, p_val, size, UT_FUNCGRP(pg_num));
  reg_us = UTL_ReadUSRegisterFuncBlockGroup(reg, size, UT_FUNCGRP(pg_num));
  if (reg_us!=*p_val) {
    printf("\n[NG] RegUs, PG%d: %s(=%d) is incorrect (exp=%d).", pg_num, reg_name, reg_us, *p_val);fflush(stdout);
  } else { 
    printf("\n[OK] PG%d: %s (=%d).", pg_num, reg_name, *p_val);fflush(stdout);	//pass-print
    result_bit &= ~(1<<5);	//Set 0 to 6bit
  }
}

void wr_reg_rb(char *reg_name, unsigned int reg, char *sig_name, int sig, int pg_num) {
  unsigned int reg_rb;
  UTL_WriteRegRbFuncBlockGroup(reg, sig, UT_FUNCGRP(pg_num));
  reg_rb = UTL_ReadRBRegisterFuncBlockGroup(reg, UT_FUNCGRP(pg_num));
  if (reg_rb!=sig) {
    printf("\n[NG] RegRb, PG%d: %s(=%d) is incorrect (exp=%d).", pg_num, reg_name, reg_rb, sig);fflush(stdout);
  } else { 
    if(strstr(sig_name, "UT_SIG_C")) {
      printf("\n[OK] PG%d: %s =UT_SIG_C(%2d).", pg_num, reg_name, sig-0x2000000);fflush(stdout);	//pass-print
      result_bit &= ~(1<<6);	//Set 0 to 07bit
    }
  }
}

void write_reg_us(unsigned int reg, int val, int size, int pg_num) {
  int *p_val=&val;
  unsigned int reg_us;
  UTL_WriteRegUsFuncBlockGroup(reg, p_val, size, UT_FUNCGRP(pg_num));
}

unsigned int read_reg_us(char *reg_name, unsigned int reg, int size, int pg_num, int flg_print) {
  unsigned int reg_val;
  reg_val=UTL_ReadUSRegisterFuncBlockGroup(reg, size, UT_FUNCGRP(pg_num));
  if (flg_print==1) { printf("\nPG%d: %s=0x%08x", pg_num,reg_name,reg_val);fflush(stdout); }
  return reg_val;
}

void check_reg_us(int max_pg) {
  int pg, i;
  int value[52];	//52Registers
  int *p_value=value;

  printf("\n\n#RegUs#");fflush(stdout);
  for (pg=1; pg<=max_pg; pg++) {
    for (i=0; i<52; i++) { value[i]=pg; }	//!:
    //               *reg_name,            reg,       val, size, pg_num
    wr_reg_us("UT_REG_ADDRMAP", UT_REG_ADDRMAP, p_value+0 , 1, pg);
    wr_reg_us("UT_REG_BAR1   ", UT_REG_BAR1   , p_value+1 , 1, pg);
    wr_reg_us("UT_REG_BD     ", UT_REG_BD     , p_value+2 , 1, pg);
    wr_reg_us("UT_REG_BD_2   ", UT_REG_BD_2   , p_value+3 , 1, pg);
    wr_reg_us("UT_REG_BH     ", UT_REG_BH     , p_value+4 , 1, pg);
    wr_reg_us("UT_REG_BH_2   ", UT_REG_BH_2   , p_value+5 , 1, pg);
    wr_reg_us("UT_REG_CCD    ", UT_REG_CCD    , p_value+6 , 1, pg);
    wr_reg_us("UT_REG_CFLG   ", UT_REG_CFLG   , p_value+7 , 1, pg);
    wr_reg_us("UT_REG_D1     ", UT_REG_D1     , p_value+8 , 1, pg);
    wr_reg_us("UT_REG_D1_2   ", UT_REG_D1_2   , p_value+9 , 1, pg);
    wr_reg_us("UT_REG_D2     ", UT_REG_D2     , p_value+10, 1, pg);
    wr_reg_us("UT_REG_D2_2   ", UT_REG_D2_2   , p_value+11, 1, pg);
    wr_reg_us("UT_REG_DATRMAP", UT_REG_DATRMAP, p_value+12, 1, pg);
    wr_reg_us("UT_REG_DINVD  ", UT_REG_DINVD  , p_value+13, 1, pg);
    wr_reg_us("UT_REG_DSD    ", UT_REG_DSD    , p_value+14, 1, pg);
    wr_reg_us("UT_REG_HMAX   ", UT_REG_HMAX   , p_value+15, 1, pg);
    wr_reg_us("UT_REG_IDX1   ", UT_REG_IDX1   , p_value+16, 1, pg);
    wr_reg_us("UT_REG_ISP    ", UT_REG_ISP    , p_value+17, 1, pg);
    wr_reg_us("UT_REG_LMAX   ", UT_REG_LMAX   , p_value+18, 1, pg);
    wr_reg_us("UT_REG_ND     ", UT_REG_ND     , p_value+19, 1, pg);
    wr_reg_us("UT_REG_ND_2   ", UT_REG_ND_2   , p_value+20, 1, pg);
    wr_reg_us("UT_REG_NH     ", UT_REG_NH     , p_value+21, 1, pg);
    wr_reg_us("UT_REG_NH_2   ", UT_REG_NH_2   , p_value+22, 1, pg);
    wr_reg_us("UT_REG_RCD    ", UT_REG_RCD    , p_value+23, 1, pg);
    wr_reg_us("UT_REG_STAPC  ", UT_REG_STAPC  , p_value+24, 1, pg);
    wr_reg_us("UT_REG_TINTMAX", UT_REG_TINTMAX, p_value+25, 1, pg);
    wr_reg_us("UT_REG_XCMR   ", UT_REG_XCMR   , p_value+26, 1, pg);
    wr_reg_us("UT_REG_XH     ", UT_REG_XH     , p_value+27, 1, pg);
    wr_reg_us("UT_REG_XH_2   ", UT_REG_XH_2   , p_value+28, 1, pg);
    wr_reg_us("UT_REG_XMASK  ", UT_REG_XMASK  , p_value+29, 1, pg);
    wr_reg_us("UT_REG_XMAX   ", UT_REG_XMAX   , p_value+30, 1, pg);
    wr_reg_us("UT_REG_XOS    ", UT_REG_XOS    , p_value+31, 1, pg);
    wr_reg_us("UT_REG_XT     ", UT_REG_XT     , p_value+32, 1, pg);
    wr_reg_us("UT_REG_YCMR   ", UT_REG_YCMR   , p_value+33, 1, pg);
    wr_reg_us("UT_REG_YH     ", UT_REG_YH     , p_value+34, 1, pg);
    wr_reg_us("UT_REG_YH_2   ", UT_REG_YH_2   , p_value+35, 1, pg);
    wr_reg_us("UT_REG_YMASK  ", UT_REG_YMASK  , p_value+36, 1, pg);
    wr_reg_us("UT_REG_YMAX   ", UT_REG_YMAX   , p_value+37, 1, pg);
    wr_reg_us("UT_REG_YOS    ", UT_REG_YOS    , p_value+38, 1, pg);
    wr_reg_us("UT_REG_YT     ", UT_REG_YT     , p_value+39, 1, pg);
    wr_reg_us("UT_REG_ZCMR   ", UT_REG_ZCMR   , p_value+40, 1, pg);
    wr_reg_us("UT_REG_ZD     ", UT_REG_ZD     , p_value+41, 1, pg);
    wr_reg_us("UT_REG_ZD_2   ", UT_REG_ZD_2   , p_value+42, 1, pg);
    wr_reg_us("UT_REG_ZH     ", UT_REG_ZH     , p_value+43, 1, pg);
    wr_reg_us("UT_REG_ZH_2   ", UT_REG_ZH_2   , p_value+44, 1, pg);
    wr_reg_us("UT_REG_D5     ", UT_REG_D5     , p_value+45, 2, pg);
    wr_reg_us("UT_REG_D5_2   ", UT_REG_D5_2   , p_value+46, 2, pg);
    wr_reg_us("UT_REG_DCMR   ", UT_REG_DCMR   , p_value+47, 2, pg);
    wr_reg_us("UT_REG_TPH    ", UT_REG_TPH    , p_value+48, 2, pg);
    wr_reg_us("UT_REG_TPH_2  ", UT_REG_TPH_2  , p_value+49, 2, pg);
    wr_reg_us("UT_REG_TPH2   ", UT_REG_TPH2   , p_value+50, 2, pg);
    wr_reg_us("UT_REG_TPH2_2 ", UT_REG_TPH2_2 , p_value+50, 2, pg);	//!:
    printf("\n");fflush(stdout);
  }
}

void check_reg_rb(int max_pg) {
  unsigned int value[15];	//15Registers
  int pg, i;

  printf("\n#RegRb#");fflush(stdout);
  for (pg=1; pg<=max_pg; pg++) {
    for (i=0; i<15; i++) { value[i]=UT_SIG_C(i+pg); }	//C8-C23
    //            *reg_name,         reg,   sig_name,    *p_val, pg_num
    wr_reg_rb("UT_REG_CPE1", UT_REG_CPE1, "UT_SIG_C", value[0] , pg);
    wr_reg_rb("UT_REG_CPE2", UT_REG_CPE2, "UT_SIG_C", value[1] , pg);
    wr_reg_rb("UT_REG_CPE3", UT_REG_CPE3, "UT_SIG_C", value[2] , pg);
    wr_reg_rb("UT_REG_CPE4", UT_REG_CPE4, "UT_SIG_C", value[3] , pg);
    wr_reg_rb("UT_REG_CPE5", UT_REG_CPE5, "UT_SIG_C", value[4] , pg);
    wr_reg_rb("UT_REG_CPE6", UT_REG_CPE6, "UT_SIG_C", value[5] , pg);
    wr_reg_rb("UT_REG_CPE7", UT_REG_CPE7, "UT_SIG_C", value[6] , pg);
    wr_reg_rb("UT_REG_CPE8", UT_REG_CPE8, "UT_SIG_C", value[7] , pg);
    wr_reg_rb("UT_REG_DRE1", UT_REG_DRE1, "UT_SIG_C", value[8] , pg);
    wr_reg_rb("UT_REG_DRE2", UT_REG_DRE2, "UT_SIG_C", value[9] , pg);
    wr_reg_rb("UT_REG_DRE3", UT_REG_DRE3, "UT_SIG_C", value[10], pg);
    wr_reg_rb("UT_REG_DRE4", UT_REG_DRE4, "UT_SIG_C", value[11], pg);
    wr_reg_rb("UT_REG_RINV", UT_REG_RINV, "UT_SIG_C", value[12], pg);
    wr_reg_rb("UT_REG_RHZA", UT_REG_RHZA, "UT_SIG_C", value[13], pg);
    wr_reg_rb("UT_REG_RHZB", UT_REG_RHZB, "UT_SIG_C", value[14], pg);
    printf("\n");fflush(stdout);
  }
}

void judge_final_result(char *testname) {
  printf("\n#Summary:%s\n", testname);fflush(stdout);
  printf("Bit=");printb(result_bit, 0);fflush(stdout);
  if (result_bit&0b00000001) { printf("\nFailBit1: UTL_UpdateMpatSelector");fflush(stdout);getchar(); }
  if (result_bit&0b00000010) { printf("\nFailBit2: UTL_ResetMpatSelector" );fflush(stdout);getchar(); }
  if (result_bit&0b00000100) { printf("\nFailBit3: Match"                 );fflush(stdout);getchar(); }
  if (result_bit&0b00001000) { printf("\nFailBit4: Reaching STPS"         );fflush(stdout);getchar(); }
  if (result_bit&0b00010000) { printf("\nFailBit5: Meas"                  );fflush(stdout);getchar(); }
  if (result_bit&0b00100000) { printf("\nFailBit6: RegUs"                 );fflush(stdout);getchar(); }
  if (result_bit&0b01000000) { printf("\nFailBit7: RegRb"                 );fflush(stdout);getchar(); }

  int dut; int dutmax=UTL_GetDutCount(UT_DDUT);
  for (dut=1; dut<=dutmax; dut++) {
    if (result_bit==0) { UTL_ResetTestResult(dut, testname, UT_RES_ALL); }
    else               { UTL_SetTestResult  (dut, testname, UT_RES_ALL); }
  }
  if (result_bit==0) { printf("\n#PASS#\n" );fflush(stdout); }
  else               { printf("#FAIL# ->Please grep NG from the log.\n"   );fflush(stdout); }
}

void send_as_1pg(char *testname) {	//!:Workaround for hang-up when ALL->LTD or LTD->ALL
  if (strstr(testname, "SENDMPA")) {
    MpatHandle h_sendmpa=UTL_GetMpatHandle();
    UTL_SetMpatFileName(h_sendmpa, "pat_multipg_sendmpa_stps.mpa");
    UTL_SetMpatStartPc (h_sendmpa, 9);
    UTL_SendMpat       (h_sendmpa);
    UTL_DeleteHandle   (h_sendmpa);
  } else if (strstr(testname, "MPATSEL")) {
    MpatSelectorHandle h_mpatsel=UTL_GetMpatSelectorHandle();
    UTL_ClearMpatSelector(h_mpatsel);
    UTL_AddMpatSelector  (h_mpatsel, "pat_multipg_mpatsel_stps.mpa", "LABEL9");
    UTL_SendMpatSelector (h_mpatsel);
    UTL_DeleteHandle     (h_mpatsel);
  }
}

