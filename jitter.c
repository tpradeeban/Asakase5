#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include "test.h"
#include "test_struct.h"
#include "jitter.h"

#define DUTMAX (16)
#define PATMAX (2000)
#define CP_PIN(dutpin) (dutpin%2==1 ? (dutpin+1):(dutpin-1))
#define STRB_LIMIT (370e-12*0.25)
#define STRB_RESO (1.0/11.2e9/64*10)
#define AMP_MARGIN (100e-3) //for amp_check
//#define CHILD_SKIP (1) //for DIAG SB
#define DEBUG (0) //0:Normal Mode, 1:Debug Mode(for pause meas)

static void pin_dummy();
static void pin_open();
static void meas_fct(TEST_testitem *testarg, USlider pc);
static void clear_ubm(TEST_testitem *testarg, int n);
static void set_ubm_capture(TEST_testitem *testarg);
static void read_ubm(TEST_testitem *testarg, void *data, UT_DUT dut, int cycle_cnt);
static void print_jitterarg(TEST_testitem *testarg);
static void print_header(TEST_testitem *testarg);
static void read_dqs_status(UT_DUT dut);
static void failcnt(TEST_testitem *testarg, UT_PIN pin, int cycle_cnt, int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX], int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX], int *allpass, int *allfail);
static void failchk(TEST_testitem *testarg, int cycle_cnt, int strb, int *allpass, int *allfail);
static void manual_wstrb(TEST_testitem *testarg, int cycle_cnt, int strb, int wstrb_data[DUTMAX][PATMAX]);
static void failcnt_wstrb(TEST_testitem *testarg, UT_PIN pin, int cycle_cnt, int wstrb_data[DUTMAX][PATMAX], int failcnt_btm[DUTMAX][MAXBLKIOCNT][PATMAX], int *allpass, int *allfail);
static void print_setedge(TEST_testitem *testarg, int ref_point[MAXBLKIOCNT], int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX], int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX], UT_DUT dut, int pin, int pcnt, int avecnt);
static void print_rstedge(TEST_testitem *testarg, int ref_point[MAXBLKIOCNT], int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX], int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX], UT_DUT dut, int pin, int pcnt, int avecnt);
static void print_duty(TEST_testitem *testarg, int ref_point[MAXBLKIOCNT], int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX], int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX], UT_DUT dut, int pin, int pcnt, int avecnt);
static void dump_edge_duty(TEST_testitem *testarg, int cycle_cnt, int ref_point[MAXBLKIOCNT], int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX], int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX], int avecnt);
static void dump_ave_edge(TEST_testitem *testarg, int cycle_cnt, int ref_point[MAXBLKIOCNT], int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX], int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX], int avecnt);
static void dump_last_edge(TEST_testitem *testarg, int cycle_cnt, int ref_point[MAXBLKIOCNT], int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX], int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX], int avecnt);
static void print_top(TEST_testitem *testarg, int ref_point_top[MAXBLKIOCNT], int failcnt_top[DUTMAX][MAXBLKIOCNT][PATMAX], int ref_point_btm[MAXBLKIOCNT], int failcnt_btm[DUTMAX][MAXBLKIOCNT][PATMAX], UT_DUT dut, int pin, int pcnt);
static void print_btm(TEST_testitem *testarg, int ref_point_top[MAXBLKIOCNT], int failcnt_top[DUTMAX][MAXBLKIOCNT][PATMAX], int ref_point_btm[MAXBLKIOCNT], int failcnt_btm[DUTMAX][MAXBLKIOCNT][PATMAX], UT_DUT dut, int pin, int pcnt);
static void print_amp(TEST_testitem *testarg, int ref_point_top[MAXBLKIOCNT], int failcnt_top[DUTMAX][MAXBLKIOCNT][PATMAX], int ref_point_btm[MAXBLKIOCNT], int failcnt_btm[DUTMAX][MAXBLKIOCNT][PATMAX], UT_DUT dut, int pin, int pcnt);
static void dump_top_btm_amp(TEST_testitem *testarg, int cycle_cnt, int ref_point_top[MAXBLKIOCNT], int failcnt_top[DUTMAX][MAXBLKIOCNT][PATMAX], int ref_point_btm[MAXBLKIOCNT], int failcnt_btm[DUTMAX][MAXBLKIOCNT][PATMAX]);
static void dump_last_top_btm_amp(TEST_testitem *testarg, int cycle_cnt, int ref_point_top[MAXBLKIOCNT], int failcnt_top[DUTMAX][MAXBLKIOCNT][PATMAX], int ref_point_btm[MAXBLKIOCNT], int failcnt_btm[DUTMAX][MAXBLKIOCNT][PATMAX]);
static void thermal_drift(TEST_testitem *testarg, int t);

void jitter_timing(TEST_testitem *testarg, DSlider offset)
{
  DSlider tck;

  TgHandle tg_h = UTL_GetTgHandle();
  tck = JITTERARG.rate;
  UTL_AddTgRate(tg_h, 1, tck);
  UTL_AddTgDreL(tg_h, 1, 1, 0.0);
  UTL_AddTgDreT(tg_h, 1, 1, 0.0);
  UTL_AddTgBclk(tg_h, 1, 1, tck*0.0);
  UTL_AddTgCclk(tg_h, 1, 1, tck*0.5);
  UTL_AddTgStrb(tg_h, 1, 1, offset+(tck*0.50));
  UTL_AddTgStrb(tg_h, 1, 2, offset+(tck*1.00));

  tck = 30e-9;
  UTL_AddTgRate(tg_h, 2, tck);
  UTL_AddTgBclk(tg_h, 2, 1, tck*0.0);
  UTL_AddTgCclk(tg_h, 2, 1, tck*0.5);

  tck = 1e-9;
  UTL_AddTgRate(tg_h, 3, tck);
  UTL_AddTgBclk(tg_h, 3, 1, tck*0.0);
  UTL_AddTgCclk(tg_h, 3, 1, tck*0.5);
  UTL_SendTg(tg_h);

  UTL_DeleteHandle(tg_h);

  return;
}

void jitter_ss_tgset(TEST_testitem *testarg)
{
  DSlider tck[3] = {0.0, JITTERARG.rate, 30e-9};
  int tsnum;

  TgHandle Tg_H = UTL_GetTgHandle();    

  for(tsnum=1; tsnum<=2; tsnum++){
   UTL_AddTgRate    (Tg_H, tsnum, tck[tsnum]);

   UTL_AddTgDreL    (Tg_H, tsnum, 1, 0.0);
   UTL_AddTgDreT    (Tg_H, tsnum, 1, 0.0);

   UTL_AddTgBclk    (Tg_H, tsnum, 1, tck[tsnum]*0.00); // for DQS_SS
   UTL_AddTgCclk    (Tg_H, tsnum, 1, tck[tsnum]*0.50); // for DQS_SS
   UTL_AddTgBclk    (Tg_H, tsnum, 2, tck[tsnum]*0.00); // for DQ_SS
   UTL_AddTgCclk    (Tg_H, tsnum, 2, tck[tsnum]*0.50); // for DQ_SS

   UTL_AddTgBclk    (Tg_H, tsnum, 3, tck[tsnum]*0.00); // for DQS_DEVICE
   UTL_AddTgCclk    (Tg_H, tsnum, 3, tck[tsnum]*0.50); // for DQS_DEVICE
   UTL_AddTgBclk    (Tg_H, tsnum, 4, tck[tsnum]*0.00); // for DQ_DEVICE
   UTL_AddTgCclk    (Tg_H, tsnum, 4, tck[tsnum]*0.50); // for DQ_DEVICE
  
   UTL_AddTgStrb    (Tg_H, tsnum, 1, tck[tsnum]*0.25); // for edgeSTRB
   UTL_AddTgStrb    (Tg_H, tsnum, 2, tck[tsnum]*0.75); // for edgeSTRB
   UTL_AddTgStrb    (Tg_H, tsnum, 3, tck[tsnum]*0.00); // for DQS STRB
   UTL_AddTgStrb    (Tg_H, tsnum, 4, tck[tsnum]*0.00); // for DQS STRB
  }

  UTL_SendTg       (Tg_H);
  UTL_DeleteHandle (Tg_H);

  return;
}

void jitter_sssc_tgset(TEST_testitem *testarg)
{
  DSlider tck[3] = {0.0, JITTERARG.rate, JITTERARG.rate};
  int tsnum;

  TgHandle Tg_H = UTL_GetTgHandle();    

  for(tsnum=1; tsnum<=2; tsnum++){
   UTL_AddTgRate    (Tg_H, tsnum, tck[tsnum]);

   //UTL_AddTgDreL    (Tg_H, tsnum, 1, 0.0);
   //UTL_AddTgDreT    (Tg_H, tsnum, 1, 0.0);

   //UTL_AddTgBclk    (Tg_H, tsnum, 1, tck[tsnum]*0.00); // for DQS_SS
   //UTL_AddTgCclk    (Tg_H, tsnum, 1, tck[tsnum]*0.50); // for DQS_SS
   //UTL_AddTgBclk    (Tg_H, tsnum, 2, tck[tsnum]*0.00); // for DQ_SS
   //UTL_AddTgCclk    (Tg_H, tsnum, 2, tck[tsnum]*0.50); // for DQ_SS

   UTL_AddTgBclk    (Tg_H, tsnum, 3, tck[tsnum]*0.50); // for DQS_DEVICE
   //UTL_AddTgCclk    (Tg_H, tsnum, 3, tck[tsnum]*0.50); // for DQS_DEVICE
   UTL_AddTgBclk    (Tg_H, tsnum, 4, tck[tsnum]*0.50); // for DQ_DEVICE
   //UTL_AddTgCclk    (Tg_H, tsnum, 4, tck[tsnum]*0.50); // for DQ_DEVICE
  
   //UTL_AddTgStrb    (Tg_H, tsnum, 1, tck[tsnum]*0.25); // for edgeSTRB
   //UTL_AddTgStrb    (Tg_H, tsnum, 2, tck[tsnum]*0.75); // for edgeSTRB
   UTL_AddTgStrb    (Tg_H, tsnum, 3, tck[tsnum]*0.00); // for DQS STRB
   UTL_AddTgStrb    (Tg_H, tsnum, 4, tck[tsnum]*0.00); // for DQS STRB
  }

  UTL_SendTg       (Tg_H);
  UTL_DeleteHandle (Tg_H);

  return;
}

void jitter_sssc_timing(TEST_testitem *testarg, DSlider offset)
{
  DSlider tck[3] = {0.0, JITTERARG.rate, JITTERARG.rate};
  int tsnum;

  TgHandle Tg_H = UTL_GetTgHandle();    

  for(tsnum=1; tsnum<=2; tsnum++){
   UTL_AddTgRate    (Tg_H, tsnum, tck[tsnum]);

   //UTL_AddTgDreL    (Tg_H, tsnum, 1, 0.0);
   //UTL_AddTgDreT    (Tg_H, tsnum, 1, 0.0);

   //UTL_AddTgBclk    (Tg_H, tsnum, 1, tck[tsnum]*0.00); // for DQS_SS
   //UTL_AddTgCclk    (Tg_H, tsnum, 1, tck[tsnum]*0.50); // for DQS_SS
   //UTL_AddTgBclk    (Tg_H, tsnum, 2, tck[tsnum]*0.00); // for DQ_SS
   //UTL_AddTgCclk    (Tg_H, tsnum, 2, tck[tsnum]*0.50); // for DQ_SS

   UTL_AddTgBclk    (Tg_H, tsnum, 3, tck[tsnum]*0.50); // for DQS_DEVICE
   //UTL_AddTgCclk    (Tg_H, tsnum, 3, tck[tsnum]*0.50); // for DQS_DEVICE
   UTL_AddTgBclk    (Tg_H, tsnum, 4, tck[tsnum]*0.50); // for DQ_DEVICE
   //UTL_AddTgCclk    (Tg_H, tsnum, 4, tck[tsnum]*0.50); // for DQ_DEVICE
  
   //UTL_AddTgStrb    (Tg_H, tsnum, 1, tck[tsnum]*0.25); // for edgeSTRB
   //UTL_AddTgStrb    (Tg_H, tsnum, 2, tck[tsnum]*0.75); // for edgeSTRB
   UTL_AddTgStrb    (Tg_H, tsnum, 3, tck[tsnum]*0.50+offset); // for DQS STRB
   UTL_AddTgStrb    (Tg_H, tsnum, 4, tck[tsnum]*0.50+offset); // for DQ STRB
  }

  UTL_SendTg       (Tg_H);
  UTL_DeleteHandle (Tg_H);

  return;
}

void jitter_ss_timing(TEST_testitem *testarg, DSlider offset)
{
  //Reset DQS setting
  UTL_ResetDqs(UT_DQS_SOURCE_SYNC);

  DqsSourceSyncHandle ss_h = UTL_GetDqsSourceSyncHandle();
  UTL_SetDqsSourceSyncMode				(ss_h, UT_DQS_SS1); // NAND mode
  UTL_SetDqsSourceSyncEnableCycle		(ss_h, UT_SIG_C(11));
  UTL_SetDqsSourceSyncReadCycle			(ss_h, UT_SIG_C(10));
  UTL_SetDqsSourceSyncDqPinCount		(ss_h, 16); // 16DQ mode
  UTL_SetDqsSourceSyncDqsPhaseAdjust	(ss_h, offset);
  UTL_SetDqsSourceSyncFailStopCtrl		(ss_h, UT_DQS_DQSCNT_ERROR, UT_OFF);
  UTL_SetDqsSourceSyncDqsPin			(ss_h, "DQS_SS");
  UTL_SetDqsSourceSyncDqPin				(ss_h, "DQ_SS");
  UTL_SendDqsSourceSync(ss_h);
  UTL_DeleteHandle(ss_h);

  return;
}

static void pin_dummy()
{
  PinHandle pf_h;
  UT_PIN pin;
  PinCursor pcr;

  //dummy
  pf_h = UTL_GetPinHandle();
  UTL_InitializePinHandle(pf_h);
  UTL_SetPinDrWaveform(pf_h, UT_WAV_DNRZ);
  UTL_SetPinDrClock(pf_h, UT_PIN_BCLK, 1);
  UTL_SetPinDrClock(pf_h, UT_PIN_CCLK, 1);
  UTL_SetPinIoCtrl(pf_h, UT_ON);
  UTL_SetPinViNumber(pf_h, 1);
  UTL_SetPinVoNumber(pf_h, 1);
  UTL_SetPinVtNumber(pf_h, 1);
  UTL_SetPinTerm(pf_h, UT_ON);
  UTL_SetPinDreNumber(pf_h, 3); // dummy DRE3
  UTL_SetPinDreWaveform(pf_h, UT_DREWAV_NRZ);
  UTL_SetPinDreClock(pf_h, 1);
  UTL_AddPinStrbCpeNumber(pf_h, 1, 3); // dummy CPE3
  UTL_AddPinExpStrbNumber(pf_h, 1, UT_PIN_EXP_A);
  UTL_AddPinStrbCpeNumber(pf_h, 2, 3);
  UTL_AddPinExpStrbNumber(pf_h, 2, UT_PIN_EXP_B);
  pcr = UTL_GetPinCursor("PODD");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(pf_h, UT_SIG_FL, 1);
    UTL_AddPinPdsB(pf_h, UT_SIG_FH, 1);
  }
  UTL_DeleteCursor(pcr);
  UTL_SendPin(pf_h, "PODD");
  UTL_SetPinDrWaveform(pf_h, UT_WAV_IDNRZ);
  UTL_SendPin(pf_h, "PEVEN"); // for crosstalk cancellation
  UTL_DeleteHandle(pf_h);

  return;
}

static void pin_open()
{
  PinHandle pf_h = UTL_GetPinHandle();
  UTL_InitializePinHandle(pf_h);
  UTL_SendPin(pf_h, SOCKET.all_iopinlist);
  UTL_DeleteHandle(pf_h);
  return;
}

void jitter_pincond(TEST_testitem *testarg, RadioButton pdsa, RadioButton pdsb)
{
  PinHandle pf_h;
  UT_PIN pin;
  PinCursor pcr;

  pin_dummy();
  //pin_open();

  //PDR
  pf_h = UTL_GetPinHandle();
  UTL_InitializePinHandle(pf_h);
  UTL_SetPinDrWaveform(pf_h, UT_WAV_DNRZ);
  UTL_SetPinDrClock(pf_h, UT_PIN_BCLK, 1);
  UTL_SetPinDrClock(pf_h, UT_PIN_CCLK, 1);
  UTL_SetPinIoCtrl(pf_h, UT_ON);
  UTL_SetPinViNumber(pf_h, 1);
  UTL_SetPinVoNumber(pf_h, 1);
  UTL_SetPinVtNumber(pf_h, 1);
  UTL_SetPinTerm(pf_h, UT_ON);
  UTL_SetPinDreNumber(pf_h, 1); // DRE1
  UTL_SetPinDreWaveform(pf_h, UT_DREWAV_NRZ);
  UTL_SetPinDreClock(pf_h, 1);
  UTL_AddPinStrbCpeNumber(pf_h, 1, 2); // CPE2
  UTL_AddPinExpStrbNumber(pf_h, 1, UT_PIN_EXP_A);
  UTL_AddPinStrbCpeNumber(pf_h, 2, 2);
  UTL_AddPinExpStrbNumber(pf_h, 2, UT_PIN_EXP_B);
  pcr = UTL_GetPinCursor("PDR");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(pf_h, UT_SIG_C(3), 1);
    UTL_AddPinPdsB(pf_h, UT_SIG_C(4), 1);
  }
  UTL_DeleteCursor(pcr);
  UTL_SendPin(pf_h, "PDR");
  UTL_DeleteHandle(pf_h);

  //PCP
  pf_h = UTL_GetPinHandle();
  UTL_InitializePinHandle(pf_h);
  UTL_SetPinDrWaveform(pf_h, UT_WAV_DNRZ);
  UTL_SetPinDrClock(pf_h, UT_PIN_BCLK, 1);
  UTL_SetPinDrClock(pf_h, UT_PIN_CCLK, 1);
  UTL_SetPinIoCtrl(pf_h, UT_ON);
  UTL_SetPinViNumber(pf_h, 1);
  UTL_SetPinVoNumber(pf_h, 1);
  UTL_SetPinVtNumber(pf_h, 1);
  UTL_SetPinTerm(pf_h, UT_ON);
  UTL_SetPinDreNumber(pf_h, 2); // DRE2
  UTL_SetPinDreWaveform(pf_h, UT_DREWAV_NRZ);
  UTL_SetPinDreClock(pf_h, 1);
  UTL_AddPinStrbCpeNumber(pf_h, 1, 1); // CPE1
  UTL_AddPinExpStrbNumber(pf_h, 1, UT_PIN_EXP_A);
  UTL_AddPinStrbCpeNumber(pf_h, 2, 1);
  UTL_AddPinExpStrbNumber(pf_h, 2, UT_PIN_EXP_B);
  pcr = UTL_GetPinCursor("PCP");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(pf_h, pdsa, 1);
    UTL_AddPinPdsB(pf_h, pdsb, 1);
  }
  UTL_DeleteCursor(pcr);
  UTL_SendPin(pf_h, "PCP");
  UTL_DeleteHandle(pf_h);

  return;
}

void jitter_ss_pincond(TEST_testitem *testarg, RadioButton pdsa, RadioButton pdsb)
{
  int dutblock;
  UT_PIN pin;
  PinCursor pcr;

  //Clear Pincondition
  PinHandle pin_H = UTL_GetPinHandle();
  UTL_SendPin(pin_H, SOCKET.all_iopinlist);
  UTL_DeleteHandle(pin_H);

  //DQS pin(SS)   
  PinHandle DQSpin_H = UTL_GetPinHandle();
  UTL_SetPinViNumber         (DQSpin_H, 1              );
  UTL_SetPinVoNumber         (DQSpin_H, 1              );
  UTL_AddPinStrbCpeNumber    (DQSpin_H, 1, 1           );
  UTL_AddPinExpStrbNumber    (DQSpin_H, 1, UT_PIN_EXP_A);
  UTL_AddPinStrbCpeNumber    (DQSpin_H, 2, 1           );
  UTL_AddPinExpStrbNumber    (DQSpin_H, 2, UT_PIN_EXP_B);
  UTL_SetPinDrWaveform       (DQSpin_H, UT_WAV_RZO     );
  UTL_SetPinInit             (DQSpin_H, UT_PIN_DEFAULT );
  UTL_SetPinDrClock          (DQSpin_H, UT_PIN_BCLK, 1 );
  UTL_SetPinDrClock          (DQSpin_H, UT_PIN_CCLK, 1 );
  UTL_SetPinIoCtrl           (DQSpin_H, UT_ON          );  
  UTL_SetPinTerm             (DQSpin_H, UT_ON          ); 
  UTL_SetPinVtNumber         (DQSpin_H, 1              );
  UTL_SetPinDreClock         (DQSpin_H, 1              );
  UTL_SetPinDreNumber        (DQSpin_H, 1              );
  UTL_SetPinDreWaveform      (DQSpin_H, UT_DREWAV_NRZ  );
  pcr = UTL_GetPinCursor("DQS_SS");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(DQSpin_H, UT_SIG_C(8), 1);
    UTL_AddPinPdsB(DQSpin_H, UT_SIG_C(8), 1);
  }
  UTL_DeleteCursor(pcr);
  UTL_SendPin                (DQSpin_H, "DQS_SS"        );
  UTL_DeleteHandle           (DQSpin_H                  );

  //DQ pin(SS)   
  PinHandle DQpin_H = UTL_GetPinHandle();
  UTL_SetPinViNumber         (DQpin_H, 1               );
  UTL_SetPinVoNumber         (DQpin_H, 1               );
  UTL_AddPinStrbCpeNumber    (DQpin_H, 1, 2            );
  UTL_AddPinExpStrbNumber    (DQpin_H, 1, UT_PIN_EXP_A );
  UTL_AddPinStrbCpeNumber    (DQpin_H, 2, 2            );
  UTL_AddPinExpStrbNumber    (DQpin_H, 2, UT_PIN_EXP_B );
  UTL_SetPinDrWaveform       (DQpin_H, UT_WAV_DNRZ     );
  UTL_SetPinInit             (DQpin_H, UT_PIN_DEFAULT  );
  UTL_SetPinDrClock          (DQpin_H, UT_PIN_BCLK, 2  );
  UTL_SetPinDrClock          (DQpin_H, UT_PIN_CCLK, 2  );
  UTL_SetPinIoCtrl           (DQpin_H, UT_ON           );  
  UTL_SetPinTerm             (DQpin_H, UT_ON           ); 
  UTL_SetPinVtNumber         (DQpin_H, 1               );
  UTL_SetPinDreClock         (DQpin_H, 1               );
  UTL_SetPinDreNumber        (DQpin_H, 2               );
  UTL_SetPinDreWaveform      (DQpin_H, UT_DREWAV_NRZ   );
  pcr = UTL_GetPinCursor("DQ_SS");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(DQpin_H, pdsa, 1);
    UTL_AddPinPdsB(DQpin_H, pdsb, 1);
  }
  UTL_DeleteCursor(pcr);
  UTL_SendPin                (DQpin_H, "DQ_SS"         );
  UTL_DeleteHandle           (DQpin_H                  );

  //DQS pin(DEVICE)   
  PinHandle DQSDEVpin_H = UTL_GetPinHandle();
  UTL_SetPinViNumber         (DQSDEVpin_H, 1               );
  UTL_SetPinVoNumber         (DQSDEVpin_H, 1               );
  UTL_AddPinStrbCpeNumber    (DQSDEVpin_H, 1, 3            );
  UTL_AddPinExpStrbNumber    (DQSDEVpin_H, 1, UT_PIN_EXP_A );
  UTL_AddPinStrbCpeNumber    (DQSDEVpin_H, 2, 3            );
  UTL_AddPinExpStrbNumber    (DQSDEVpin_H, 2, UT_PIN_EXP_B );
  UTL_SetPinDrWaveform       (DQSDEVpin_H, UT_WAV_RZO      );
  UTL_SetPinInit             (DQSDEVpin_H, UT_PIN_DEFAULT  );
  UTL_SetPinDrClock          (DQSDEVpin_H, UT_PIN_BCLK, 3  );
  UTL_SetPinDrClock          (DQSDEVpin_H, UT_PIN_CCLK, 3  );
  UTL_SetPinIoCtrl           (DQSDEVpin_H, UT_ON           );  
  UTL_SetPinTerm             (DQSDEVpin_H, UT_ON           ); 
  UTL_SetPinVtNumber         (DQSDEVpin_H, 1               );
  UTL_SetPinDreClock         (DQSDEVpin_H, 1               );
  UTL_SetPinDreNumber        (DQSDEVpin_H, 3               );
  UTL_SetPinDreWaveform      (DQSDEVpin_H, UT_DREWAV_NRZ   );
  pcr = UTL_GetPinCursor("DQS_DV");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(DQSDEVpin_H, UT_SIG_C(13)  , 1);
    UTL_AddPinPdsB(DQSDEVpin_H, UT_SIG_I_C(13), 1);
  }
  UTL_DeleteCursor(pcr);
  UTL_SendPin                (DQSDEVpin_H, "DQS_DV"        );
  UTL_DeleteHandle           (DQSDEVpin_H                  );

  //DQ pin(DEVICE)   
  PinHandle DQDEVpin_H = UTL_GetPinHandle();
  UTL_SetPinViNumber         (DQDEVpin_H, 1              );
  UTL_SetPinVoNumber         (DQDEVpin_H, 1              );
  UTL_AddPinStrbCpeNumber    (DQDEVpin_H, 1, 4           );
  UTL_AddPinExpStrbNumber    (DQDEVpin_H, 1, UT_PIN_EXP_A);
  UTL_AddPinStrbCpeNumber    (DQDEVpin_H, 2, 4           );
  UTL_AddPinExpStrbNumber    (DQDEVpin_H, 2, UT_PIN_EXP_B);
  UTL_SetPinDrWaveform       (DQDEVpin_H, UT_WAV_IDNRZ   );
  UTL_SetPinInit             (DQDEVpin_H, UT_PIN_DEFAULT );
  UTL_SetPinDrClock          (DQDEVpin_H, UT_PIN_BCLK, 4 );
  UTL_SetPinDrClock          (DQDEVpin_H, UT_PIN_CCLK, 4 );
  UTL_SetPinIoCtrl           (DQDEVpin_H, UT_ON          );  
  UTL_SetPinTerm             (DQDEVpin_H, UT_ON          ); 
  UTL_SetPinVtNumber         (DQDEVpin_H, 1              );
  UTL_SetPinDreClock         (DQDEVpin_H, 1              );
  UTL_SetPinDreNumber        (DQDEVpin_H, 4              );
  UTL_SetPinDreWaveform      (DQDEVpin_H, UT_DREWAV_NRZ  );
  pcr = UTL_GetPinCursor("DQ_DV1");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(DQDEVpin_H, UT_SIG_C(3), 1);
    UTL_AddPinPdsB(DQDEVpin_H, UT_SIG_C(4), 1);
  }
  UTL_SendPin                (DQDEVpin_H, "DQ_DV1"       );
  UTL_SetPinDrWaveform       (DQDEVpin_H, UT_WAV_DNRZ    );
  UTL_SendPin                (DQDEVpin_H, "DQ_DV2"       );
  UTL_DeleteHandle           (DQDEVpin_H                 );
  
  return;
}

void jitter_sssc_pincond(TEST_testitem *testarg, RadioButton pdsa, RadioButton pdsb)
{
  int dutblock;
  UT_PIN pin;
  PinCursor pcr;

  //Clear Pincondition
  PinHandle pin_H = UTL_GetPinHandle();
  UTL_SendPin(pin_H, SOCKET.all_iopinlist);
  UTL_DeleteHandle(pin_H);

  //DQS pin(SS)   
  PinHandle DQSpin_H = UTL_GetPinHandle();
  //UTL_SetPinViNumber         (DQSpin_H, 1              );
  UTL_SetPinVoNumber         (DQSpin_H, 1              );
  UTL_AddPinStrbCpeNumber    (DQSpin_H, 3, 1           );
  UTL_AddPinExpStrbNumber    (DQSpin_H, 1, UT_PIN_EXP_A);
  //UTL_AddPinStrbCpeNumber    (DQSpin_H, 2, 1           );
  //UTL_AddPinExpStrbNumber    (DQSpin_H, 2, UT_PIN_EXP_B);
  //UTL_SetPinDrWaveform       (DQSpin_H, UT_WAV_NRZB    );
  //UTL_SetPinInit             (DQSpin_H, UT_PIN_DEFAULT );
  //UTL_SetPinDrClock          (DQSpin_H, UT_PIN_BCLK, 1 );
  //UTL_SetPinDrClock          (DQSpin_H, UT_PIN_CCLK, 1 );
  UTL_SetPinIoCtrl           (DQSpin_H, UT_OFF         );  
  UTL_SetPinTerm             (DQSpin_H, UT_ON          ); 
  UTL_SetPinVtNumber         (DQSpin_H, 1              );
  //UTL_SetPinDreClock         (DQSpin_H, 1              );
  //UTL_SetPinDreNumber        (DQSpin_H, 1              );
  //UTL_SetPinDreWaveform      (DQSpin_H, UT_DREWAV_NRZ  );
  pcr = UTL_GetPinCursor("DQS_SS");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(DQSpin_H, pdsa, 1);
    //UTL_AddPinPdsB(DQSpin_H, UT_SIG_C(8), 1);
  }
  UTL_DeleteCursor(pcr);
  UTL_SendPin                (DQSpin_H, "DQS_SS"        );
  UTL_DeleteHandle           (DQSpin_H                  );

  //DQ pin(SS)   
  PinHandle DQpin_H = UTL_GetPinHandle();
  //UTL_SetPinViNumber         (DQpin_H, 1               );
  UTL_SetPinVoNumber         (DQpin_H, 1               );
  UTL_AddPinStrbCpeNumber    (DQpin_H, 4, 2            );
  UTL_AddPinExpStrbNumber    (DQpin_H, 1, UT_PIN_EXP_A );
  //UTL_AddPinStrbCpeNumber    (DQpin_H, 2, 2            );
  //UTL_AddPinExpStrbNumber    (DQpin_H, 2, UT_PIN_EXP_B );
  //UTL_SetPinDrWaveform       (DQpin_H, UT_WAV_NRZB     );
  //UTL_SetPinInit             (DQpin_H, UT_PIN_DEFAULT  );
  //UTL_SetPinDrClock          (DQpin_H, UT_PIN_BCLK, 2  );
  //UTL_SetPinDrClock          (DQpin_H, UT_PIN_CCLK, 2  );
  UTL_SetPinIoCtrl           (DQpin_H, UT_OFF          );  
  UTL_SetPinTerm             (DQpin_H, UT_ON           ); 
  UTL_SetPinVtNumber         (DQpin_H, 1               );
  //UTL_SetPinDreClock         (DQpin_H, 1               );
  //UTL_SetPinDreNumber        (DQpin_H, 2               );
  //UTL_SetPinDreWaveform      (DQpin_H, UT_DREWAV_NRZ   );
  pcr = UTL_GetPinCursor("DQ_SS");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(DQpin_H, pdsa, 1);
    //UTL_AddPinPdsB(DQpin_H, pdsb, 1);
  }
  UTL_DeleteCursor(pcr);
  UTL_SendPin                (DQpin_H, "DQ_SS"         );
  UTL_DeleteHandle           (DQpin_H                  );

  //DQS pin(DEVICE)   
  PinHandle DQSDEVpin_H = UTL_GetPinHandle();
  UTL_SetPinViNumber         (DQSDEVpin_H, 1               );
  //UTL_SetPinVoNumber         (DQSDEVpin_H, 1               );
  //UTL_AddPinStrbCpeNumber    (DQSDEVpin_H, 1, 3            );
  //UTL_AddPinExpStrbNumber    (DQSDEVpin_H, 1, UT_PIN_EXP_A );
  //UTL_AddPinStrbCpeNumber    (DQSDEVpin_H, 2, 3            );
  //UTL_AddPinExpStrbNumber    (DQSDEVpin_H, 2, UT_PIN_EXP_B );
  UTL_SetPinDrWaveform       (DQSDEVpin_H, UT_WAV_NRZB     );
  UTL_SetPinInit             (DQSDEVpin_H, UT_PIN_DEFAULT  );
  UTL_SetPinDrClock          (DQSDEVpin_H, UT_PIN_BCLK, 3  );
  //UTL_SetPinDrClock          (DQSDEVpin_H, UT_PIN_CCLK, 3  );
  UTL_SetPinIoCtrl           (DQSDEVpin_H, UT_OFF          );  
  //UTL_SetPinTerm             (DQSDEVpin_H, UT_ON           ); 
  //UTL_SetPinVtNumber         (DQSDEVpin_H, 1               );
  //UTL_SetPinDreClock         (DQSDEVpin_H, 1               );
  //UTL_SetPinDreNumber        (DQSDEVpin_H, 3               );
  //UTL_SetPinDreWaveform      (DQSDEVpin_H, UT_DREWAV_NRZ   );
  pcr = UTL_GetPinCursor("DQS_DV");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(DQSDEVpin_H, UT_SIG_C(0)  , 1);
    //UTL_AddPinPdsB(DQSDEVpin_H, UT_SIG_I_C(13), 1);
  }
  UTL_DeleteCursor(pcr);
  UTL_SendPin                (DQSDEVpin_H, "DQS_DV"        );
  UTL_DeleteHandle           (DQSDEVpin_H                  );

  //DQ pin(DEVICE)   
  PinHandle DQDEVpin_H = UTL_GetPinHandle();
  UTL_SetPinViNumber         (DQDEVpin_H, 1              );
  //UTL_SetPinVoNumber         (DQDEVpin_H, 1              );
  //UTL_AddPinStrbCpeNumber    (DQDEVpin_H, 1, 4           );
  //UTL_AddPinExpStrbNumber    (DQDEVpin_H, 1, UT_PIN_EXP_A);
  //UTL_AddPinStrbCpeNumber    (DQDEVpin_H, 2, 4           );
  //UTL_AddPinExpStrbNumber    (DQDEVpin_H, 2, UT_PIN_EXP_B);
  UTL_SetPinDrWaveform       (DQDEVpin_H, UT_WAV_NRZB    );
  UTL_SetPinInit             (DQDEVpin_H, UT_PIN_DEFAULT );
  UTL_SetPinDrClock          (DQDEVpin_H, UT_PIN_BCLK, 4 );
  //UTL_SetPinDrClock          (DQDEVpin_H, UT_PIN_CCLK, 4 );
  UTL_SetPinIoCtrl           (DQDEVpin_H, UT_OFF         );  
  //UTL_SetPinTerm             (DQDEVpin_H, UT_ON          ); 
  //UTL_SetPinVtNumber         (DQDEVpin_H, 1              );
  //UTL_SetPinDreClock         (DQDEVpin_H, 1              );
  //UTL_SetPinDreNumber        (DQDEVpin_H, 4              );
  //UTL_SetPinDreWaveform      (DQDEVpin_H, UT_DREWAV_NRZ  );
  pcr = UTL_GetPinCursor("DQ_DV");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(DQDEVpin_H, UT_SIG_C(1), 1);
    //UTL_AddPinPdsB(DQDEVpin_H, UT_SIG_C(4), 1);
  }
  UTL_SendPin                (DQDEVpin_H, "DQ_DV"        );
  UTL_DeleteHandle           (DQDEVpin_H                 );
  
  return;
}

void jitter_sssc_edge_pincond(TEST_testitem *testarg, RadioButton pdsa, RadioButton pdsb)
{
  int dutblock;
  UT_PIN pin;
  PinCursor pcr;

  //Clear Pincondition
  PinHandle pin_H = UTL_GetPinHandle();
  UTL_SendPin(pin_H, SOCKET.all_iopinlist);
  UTL_DeleteHandle(pin_H);

#if 0
  //DQS pin(SS)   
  PinHandle DQSpin_H = UTL_GetPinHandle();
  //UTL_SetPinViNumber         (DQSpin_H, 1              );
  UTL_SetPinVoNumber         (DQSpin_H, 1              );
  UTL_AddPinStrbCpeNumber    (DQSpin_H, 3, 1           );
  UTL_AddPinExpStrbNumber    (DQSpin_H, 1, UT_PIN_EXP_A);
  //UTL_AddPinStrbCpeNumber    (DQSpin_H, 2, 1           );
  //UTL_AddPinExpStrbNumber    (DQSpin_H, 2, UT_PIN_EXP_B);
  //UTL_SetPinDrWaveform       (DQSpin_H, UT_WAV_NRZB    );
  //UTL_SetPinInit             (DQSpin_H, UT_PIN_DEFAULT );
  //UTL_SetPinDrClock          (DQSpin_H, UT_PIN_BCLK, 1 );
  //UTL_SetPinDrClock          (DQSpin_H, UT_PIN_CCLK, 1 );
  UTL_SetPinIoCtrl           (DQSpin_H, UT_OFF         );  
  UTL_SetPinTerm             (DQSpin_H, UT_ON          ); 
  UTL_SetPinVtNumber         (DQSpin_H, 1              );
  //UTL_SetPinDreClock         (DQSpin_H, 1              );
  //UTL_SetPinDreNumber        (DQSpin_H, 1              );
  //UTL_SetPinDreWaveform      (DQSpin_H, UT_DREWAV_NRZ  );
  pcr = UTL_GetPinCursor("DQS_SS");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(DQSpin_H, pdsa, 1);
    //UTL_AddPinPdsB(DQSpin_H, UT_SIG_C(8), 1);
  }
  UTL_DeleteCursor(pcr);
  UTL_SendPin                (DQSpin_H, "DQS_SS"        );
  UTL_DeleteHandle           (DQSpin_H                  );
#endif

  //DQ pin(SS)   
  PinHandle DQpin_H = UTL_GetPinHandle();
  //UTL_SetPinViNumber         (DQpin_H, 1               );
  UTL_SetPinVoNumber         (DQpin_H, 1               );
  UTL_AddPinStrbCpeNumber    (DQpin_H, 4, 2            );
  UTL_AddPinExpStrbNumber    (DQpin_H, 1, UT_PIN_EXP_A );
  //UTL_AddPinStrbCpeNumber    (DQpin_H, 2, 2            );
  //UTL_AddPinExpStrbNumber    (DQpin_H, 2, UT_PIN_EXP_B );
  //UTL_SetPinDrWaveform       (DQpin_H, UT_WAV_NRZB     );
  //UTL_SetPinInit             (DQpin_H, UT_PIN_DEFAULT  );
  //UTL_SetPinDrClock          (DQpin_H, UT_PIN_BCLK, 2  );
  //UTL_SetPinDrClock          (DQpin_H, UT_PIN_CCLK, 2  );
  UTL_SetPinIoCtrl           (DQpin_H, UT_OFF          );  
  UTL_SetPinTerm             (DQpin_H, UT_ON           ); 
  UTL_SetPinVtNumber         (DQpin_H, 1               );
  //UTL_SetPinDreClock         (DQpin_H, 1               );
  //UTL_SetPinDreNumber        (DQpin_H, 2               );
  //UTL_SetPinDreWaveform      (DQpin_H, UT_DREWAV_NRZ   );
  pcr = UTL_GetPinCursor("DQ_SS");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(DQpin_H, pdsa, 1);
    //UTL_AddPinPdsB(DQpin_H, pdsb, 1);
  }
  UTL_DeleteCursor(pcr);
  UTL_SendPin                (DQpin_H, "DQ_SS"         );
  UTL_DeleteHandle           (DQpin_H                  );

#if 0
  //DQS pin(DEVICE)   
  PinHandle DQSDEVpin_H = UTL_GetPinHandle();
  UTL_SetPinViNumber         (DQSDEVpin_H, 1               );
  //UTL_SetPinVoNumber         (DQSDEVpin_H, 1               );
  //UTL_AddPinStrbCpeNumber    (DQSDEVpin_H, 1, 3            );
  //UTL_AddPinExpStrbNumber    (DQSDEVpin_H, 1, UT_PIN_EXP_A );
  //UTL_AddPinStrbCpeNumber    (DQSDEVpin_H, 2, 3            );
  //UTL_AddPinExpStrbNumber    (DQSDEVpin_H, 2, UT_PIN_EXP_B );
  UTL_SetPinDrWaveform       (DQSDEVpin_H, UT_WAV_NRZB     );
  UTL_SetPinInit             (DQSDEVpin_H, UT_PIN_DEFAULT  );
  UTL_SetPinDrClock          (DQSDEVpin_H, UT_PIN_BCLK, 3  );
  //UTL_SetPinDrClock          (DQSDEVpin_H, UT_PIN_CCLK, 3  );
  UTL_SetPinIoCtrl           (DQSDEVpin_H, UT_OFF          );  
  //UTL_SetPinTerm             (DQSDEVpin_H, UT_ON           ); 
  //UTL_SetPinVtNumber         (DQSDEVpin_H, 1               );
  //UTL_SetPinDreClock         (DQSDEVpin_H, 1               );
  //UTL_SetPinDreNumber        (DQSDEVpin_H, 3               );
  //UTL_SetPinDreWaveform      (DQSDEVpin_H, UT_DREWAV_NRZ   );
  pcr = UTL_GetPinCursor("DQS_DV");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(DQSDEVpin_H, UT_SIG_C(0)  , 1);
    //UTL_AddPinPdsB(DQSDEVpin_H, UT_SIG_I_C(13), 1);
  }
  UTL_DeleteCursor(pcr);
  UTL_SendPin                (DQSDEVpin_H, "DQS_DV"        );
  UTL_DeleteHandle           (DQSDEVpin_H                  );
#endif

  //DQ pin(DEVICE)   
  PinHandle DQDEVpin_H = UTL_GetPinHandle();
  UTL_SetPinViNumber         (DQDEVpin_H, 1              );
  //UTL_SetPinVoNumber         (DQDEVpin_H, 1              );
  //UTL_AddPinStrbCpeNumber    (DQDEVpin_H, 1, 4           );
  //UTL_AddPinExpStrbNumber    (DQDEVpin_H, 1, UT_PIN_EXP_A);
  //UTL_AddPinStrbCpeNumber    (DQDEVpin_H, 2, 4           );
  //UTL_AddPinExpStrbNumber    (DQDEVpin_H, 2, UT_PIN_EXP_B);
  UTL_SetPinDrWaveform       (DQDEVpin_H, UT_WAV_NRZB    );
  UTL_SetPinInit             (DQDEVpin_H, UT_PIN_DEFAULT );
  UTL_SetPinDrClock          (DQDEVpin_H, UT_PIN_BCLK, 4 );
  //UTL_SetPinDrClock          (DQDEVpin_H, UT_PIN_CCLK, 4 );
  UTL_SetPinIoCtrl           (DQDEVpin_H, UT_OFF         );  
  //UTL_SetPinTerm             (DQDEVpin_H, UT_ON          ); 
  //UTL_SetPinVtNumber         (DQDEVpin_H, 1              );
  //UTL_SetPinDreClock         (DQDEVpin_H, 1              );
  //UTL_SetPinDreNumber        (DQDEVpin_H, 4              );
  //UTL_SetPinDreWaveform      (DQDEVpin_H, UT_DREWAV_NRZ  );
  pcr = UTL_GetPinCursor("DQ_DV");
  while((pin=UTL_NextPin(pcr))!=UT_NOMORE){
    UTL_AddPinPdsA(DQDEVpin_H, UT_SIG_C(1), 1);
    //UTL_AddPinPdsB(DQDEVpin_H, UT_SIG_C(4), 1);
  }
  UTL_SendPin                (DQDEVpin_H, "DQ_DV"        );
  UTL_DeleteHandle           (DQDEVpin_H                 );
  
  return;
}
void jitter_level(TEST_testitem *testarg, DSlider offset)
{
  ViHandle vi_h = UTL_GetViHandle();
  UTL_SetViHigh(vi_h, JITTERARG.vih);
  UTL_SetViLow (vi_h, JITTERARG.vil);
  UTL_SetViHvDr(vi_h, UT_OFF);
  UTL_SendVi   (vi_h, 1);

  VtHandle vt_h = UTL_GetVtHandle();
  UTL_SetVt    (vt_h, JITTERARG.vt);
  UTL_SendVt   (vt_h, 1);

  DSlider vo;
  vo = ((JITTERARG.vih+JITTERARG.vt)/2+(JITTERARG.vil+JITTERARG.vt)/2)/2+offset;
  //printf("vo\t\t: %f\n", vo);
  VoHandle vo_h = UTL_GetVoHandle();
  UTL_SetVoHigh(vo_h, vo);
  UTL_SetVoLow (vo_h, vo);
  UTL_SendVo   (vo_h, 1);

  UTL_DeleteHandle(vo_h);
  UTL_DeleteHandle(vt_h);
  UTL_DeleteHandle(vi_h);

  return;
}

void jitter_pinlist(RadioButton dutpin)
{
  int i;

  UTL_CreatePinList	("PDR");
  UTL_SetPinType	("PDR", UT_PINTYPE_PIN);
  UTL_AddPinNumber	("PDR", dutpin);

  UTL_CreatePinList	("PCP");
  UTL_SetPinType	("PCP", UT_PINTYPE_PIN);
  UTL_AddPinNumber	("PCP", CP_PIN(dutpin));

  UTL_CreatePinList	("PODD"); // dummy
  UTL_SetPinType	("PODD", UT_PINTYPE_PIN);
  UTL_CreatePinList	("PEVEN"); // dummy
  UTL_SetPinType	("PEVEN", UT_PINTYPE_PIN);
  for(i=0; i<SOCKET.dutblock_iopin_count[0]; i++){
    if(i%2==1){
      UTL_AddPinNumber("PODD", SOCKET.dutblock_iopin[0][i]);
    }
    else{
      UTL_AddPinNumber("PEVEN", SOCKET.dutblock_iopin[0][i]);
    }
  }

  return;
}

void jitter_ss_pinlist(RadioButton dutpin)
{
  int i;
  UT_PIN pin;

  UTL_CreatePinList	("PCP");
  UTL_SetPinType	("PCP", UT_PINTYPE_PIN);
  UTL_AddPinNumber	("PCP", CP_PIN(dutpin));

  //DQ Pin List
  UTL_CreatePinList     ("DQ_SS");
  UTL_SetPinType        ("DQ_SS", UT_PINTYPE_PIN);
  UTL_CreatePinList     ("DQ_DV1");
  UTL_SetPinType        ("DQ_DV1", UT_PINTYPE_PIN);
  UTL_CreatePinList     ("DQ_DV2");
  UTL_SetPinType        ("DQ_DV2", UT_PINTYPE_PIN);
  
  for(i=0; i<SOCKET.dutblock_iopin_count[0]-2; i=i+2){
    pin = SOCKET.dutblock_iopin[0][i];
    UTL_AddPinNumber    ("DQ_SS", pin+(dutpin%2));
  }
  for(i=0; i<SOCKET.dutblock_iopin_count[0]-2; i=i+4){
    pin = SOCKET.dutblock_iopin[0][i];
    UTL_AddPinNumber    ("DQ_DV1", pin+(  (dutpin-1)%4)      );
    UTL_AddPinNumber    ("DQ_DV2", pin+((((dutpin-1)%4)+2)%4));
  }

  //DQS Pin List
  UTL_CreatePinList     ("DQS_SS");
  UTL_SetPinType        ("DQS_SS", UT_PINTYPE_PIN);
  UTL_CreatePinList     ("DQS_DV");
  UTL_SetPinType        ("DQS_DV", UT_PINTYPE_PIN);

  pin = SOCKET.dutblock_iopin[0][16];
  UTL_AddPinNumber    ("DQS_SS", pin);
  pin = SOCKET.dutblock_iopin[0][17];
  UTL_AddPinNumber    ("DQS_DV", pin);

  return;
}

void jitter_sssc_pinlist(RadioButton dutpin)
{
  int i;
  UT_PIN pin;

  UTL_CreatePinList	("PCP");
  UTL_SetPinType	("PCP", UT_PINTYPE_PIN);
  UTL_AddPinNumber	("PCP", CP_PIN(dutpin));

  //DQ Pin List
  UTL_CreatePinList	("DQ_SS");
  UTL_SetPinType	("DQ_SS", UT_PINTYPE_PIN);
  UTL_AddPinNumber	("DQ_SS", CP_PIN(dutpin));

  UTL_CreatePinList	("DQ_DV");
  UTL_SetPinType	("DQ_DV", UT_PINTYPE_PIN);
  UTL_AddPinNumber	("DQ_DV", dutpin);

  //DQS Pin List
  UTL_CreatePinList ("DQS_SS");
  UTL_SetPinType    ("DQS_SS", UT_PINTYPE_PIN);
  UTL_CreatePinList ("DQS_DV");
  UTL_SetPinType    ("DQS_DV", UT_PINTYPE_PIN);

  pin = SOCKET.dutblock_iopin[0][16];
  UTL_AddPinNumber  ("DQS_SS", pin);
  pin = SOCKET.dutblock_iopin[0][17];
  UTL_AddPinNumber  ("DQS_DV", pin);

  return;
}

void jitter_sssc_edge_pinlist(RadioButton dutpin)
{
  int i;
  UT_PIN pin;

  UTL_CreatePinList	("PCP");
  UTL_SetPinType	("PCP", UT_PINTYPE_PIN);
  UTL_AddPinNumber	("PCP", CP_PIN(dutpin));

  //DQ Pin List
  UTL_CreatePinList	("DQ_SS");
  UTL_SetPinType	("DQ_SS", UT_PINTYPE_PIN);
  UTL_AddPinNumber	("DQ_SS", CP_PIN(dutpin));

  UTL_CreatePinList	("DQ_DV");
  UTL_SetPinType	("DQ_DV", UT_PINTYPE_PIN);
  UTL_AddPinNumber	("DQ_DV", dutpin);

  //DQS Pin List
  UTL_CreatePinList ("DQS_SS");
  UTL_SetPinType    ("DQS_SS", UT_PINTYPE_PIN);
  UTL_CreatePinList ("DQS_DV");
  UTL_SetPinType    ("DQS_DV", UT_PINTYPE_PIN);

  pin = SOCKET.dutblock_iopin[0][16];
  UTL_AddPinNumber  ("DQS_SS", pin);
  //UTL_AddPinNumber	("PCP"   , pin);
  pin = SOCKET.dutblock_iopin[0][17];
  UTL_AddPinNumber  ("DQS_DV", pin);

  return;
}

static void meas_fct(TEST_testitem *testarg, USlider pc)
{
  FctHandle fct_h = UTL_GetFctHandle();

  UTL_SetFctMpatName(fct_h, JITTERARG.mpat);
  UTL_SetFctFailInhibit(fct_h, UT_ON);
  UTL_SetFctStartPc(fct_h, pc);
  UTL_SetFctNoClear(fct_h, UT_ON);
  UTL_MeasFct(fct_h);

  UTL_DeleteHandle(fct_h);

  return;
}

static void clear_ubm(TEST_testitem *testarg, int n)
{
  UbmAccessHandle uacsh = UTL_GetUbmAccessHandle();
  UTL_PresetUbm(uacsh, 0);
  UTL_DeleteHandle(uacsh);

  return;
}

static void set_ubm_capture(TEST_testitem *testarg)
{
  UbmConfigHandle useth = UTL_GetUbmConfigHandle();
  UTL_InitializeUbmConfigHandle(useth);
  UTL_ClearUbmConfigFunctionSelect(useth);
  UTL_ClearUbmConfigPin(useth, UT_UBM_UNIT_SCRESULTMEMORY);
  UTL_ClearUbmConfigJumpAddr(useth, UT_UBM_UNIT_SCRESULTMEMORY, 0);
  UTL_ClearUbmConfigStrbChannel(useth);

  UTL_AddUbmConfigFunctionSelect(useth, UT_UBM_UNIT_SCRESULTMEMORY, UT_SIG_C(30));
  UTL_SetUbmConfigPin(useth, UT_UBM_UNIT_SCRESULTMEMORY, "PCP");
  UTL_SetUbmConfigJumpAddr(useth, UT_UBM_UNIT_SCRESULTMEMORY, 0, 0x0);
  UTL_SetUbmConfigJumpCycle(useth, UT_UBM_UNIT_SCRESULTMEMORY, 0, UT_SIG_C(25));

  UTL_SetUbmConfigPmMode(useth, UT_UBM_MODE_NOTUSE);
  UTL_SetUbmConfigDdrMode(useth, JITTERARG.ddr);

  UTL_SetUbmConfigCaptureMode(useth, UT_UBM_NORMAL);
  if(JITTERARG.ddr==UT_ON){
  UTL_SetUbmConfigStrbMode(useth, UT_UBM_INDIVIDUAL);
    UTL_AddUbmConfigStrbChannel(useth, 0, 0);
    UTL_AddUbmConfigStrbChannel(useth, 0, 1);
  }
  else{
    UTL_SetUbmConfigStrbMode(useth, UT_UBM_ORFAIL);
    UTL_AddUbmConfigStrbChannel(useth, 0, 0);
  }

  UTL_SendUbmConfig(useth);
  UTL_DeleteHandle(useth);

  return;
}

static void read_ubm(TEST_testitem *testarg, void *data, UT_DUT dut, int cycle_cnt)
{
  USlider size;
  size = cycle_cnt;
  if(JITTERARG.ddr==UT_ON){
    size*=2;
  }

  UbmAccessHandle uacsh = UTL_GetUbmAccessHandle();
  UTL_SetUbmAccessDut(uacsh, dut);
  UTL_SetUbmAccessPin(uacsh, "PCP");
  UTL_SetUbmAccessStartAddr(uacsh, 0x0);
  UTL_SetUbmAccessStopAddr(uacsh, size-1);
  //UTL_SetUbmAccessPinBlock(uacsh, 1);
  UTL_SetUbmAccessBitReverse(uacsh, UT_ON);
  UTL_SetUbmAccessDdrMode(uacsh, JITTERARG.ddr);

  UTL_ReadUbm(uacsh, data, sizeof(USlider)*size);

  UTL_DeleteHandle(uacsh);

  return;
}

static void print_jitterarg(TEST_testitem *testarg)
{
  printf("ilmode\t\t: %d\n", JITTERARG.ilmode);
  printf("rate\t\t: %e\n", JITTERARG.rate);
  printf("vih\t\t: %f\n", JITTERARG.vih);
  printf("vil\t\t: %f\n", JITTERARG.vil);
  printf("vt\t\t: %f\n", JITTERARG.vt);
  printf("time_window\t: %e\n", JITTERARG.time_window);
  printf("mapt\t\t: %s\n", JITTERARG.mpat);
  printf("pc\t\t: 0x%03x\n", JITTERARG.pc);

  return;
}

static void print_header(TEST_testitem *testarg)
{
  int i;
  printf("pcnt, time       ");
  for(i=1; i<=JITTERARG.pincnt; i++){
    printf(", P%2d ", i);
  }
  printf("\n");

  return;
}

static void read_dqs_status(UT_DUT dut)
{
  USlider dqsstat, dqsc, dqsec;
  DqsStatusHandle dqssh = UTL_GetDqsStatusHandle();
  UTL_SetDqsStatusDut(dqssh, dut);
  UTL_SetDqsStatusPin(dqssh, "DQS_SS");
  UTL_ReadDqsStatus(dqssh, &dqsstat);
  UTL_ReadDqsCounter(dqssh, &dqsc, &dqsec);
  printf("dqsstat=0x%x dqscnt=%d dqsec=%d\n", dqsstat, dqsc, dqsec);
  UTL_DeleteHandle(dqssh);
  return;
}

static void failcnt(TEST_testitem *testarg, UT_PIN pin, int cycle_cnt, int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX], int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX], int *allpass, int *allfail)
{
  USlider data[PATMAX*2] = {0x0};
  int pcnt;
  DutCursor dutc;
  UT_DUT dut;

  *allpass = 0x0;
  *allfail = 0x1;
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
#ifdef CHILD_SKIP
    if(SOCKET.dut_child[dut]==CHILD_SKIP) continue;
#endif
    read_ubm(testarg, (void *)(data), dut, cycle_cnt);
    for(pcnt=0; pcnt<cycle_cnt; pcnt++){
      if(JITTERARG.ddr==UT_ON){
        failcnt_set[dut-1][pin][pcnt]+=(data[pcnt*2  ]&0x1);
        failcnt_rst[dut-1][pin][pcnt]+=(data[pcnt*2+1]&0x1);

        *allpass|=(data[pcnt*2]&0x1)|(data[pcnt*2+1]&0x1);
        *allfail&=(data[pcnt*2]&0x1)&(data[pcnt*2+1]&0x1);
      }
      else{
        failcnt_set[dut-1][pin][pcnt]+=(data[pcnt]&0x1);

        *allpass|=(data[pcnt]&0x1);
        *allfail&=(data[pcnt]&0x1);
      }
    }
    //if(dut==1) printf("%d", data[0]);
  }
  UTL_DeleteCursor(dutc);

  return;
}

static void failchk(TEST_testitem *testarg, int cycle_cnt, int strb, int *allpass, int *allfail)
{
  USlider data[PATMAX*2] = {0x0};
  int pcnt;
  DutCursor dutc;
  UT_DUT dut;

  *allpass = 0x0;
  *allfail = 0x1;
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
#ifdef CHILD_SKIP
    if(SOCKET.dut_child[dut]==CHILD_SKIP) continue;
#endif
    read_ubm(testarg, (void *)(data), dut, cycle_cnt);
    for(pcnt=0; pcnt<cycle_cnt; pcnt++){
      if(JITTERARG.ddr==UT_ON){
        *allpass|=(data[pcnt*2+strb]&0x1);
        *allfail&=(data[pcnt*2+strb]&0x1);
      }
      else{
        *allpass|=(data[pcnt]&0x1);
        *allfail&=(data[pcnt]&0x1);
      }
    }
    //if(dut==1) printf("%d", data[0*2+strb]);
  }
  UTL_DeleteCursor(dutc);

  return;
}

static void manual_wstrb(TEST_testitem *testarg, int cycle_cnt, int strb, int wstrb_data[DUTMAX][PATMAX])
{
  USlider data[PATMAX*2] = {0x0};
  int pcnt;
  DutCursor dutc;
  UT_DUT dut;

  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
#ifdef CHILD_SKIP
    if(SOCKET.dut_child[dut]==CHILD_SKIP) continue;
#endif
    read_ubm(testarg, (void *)(data), dut, cycle_cnt);
    for(pcnt=0; pcnt<cycle_cnt; pcnt++){
      if(JITTERARG.ddr==UT_ON){
        wstrb_data[dut-1][pcnt]|=(data[pcnt*2+strb]&0x1);
      }
      else{
        wstrb_data[dut-1][pcnt]|=(data[pcnt]&0x1);
      }
    }
    //if(dut==1) printf("%d", data[0*2+strb]);
  }
  UTL_DeleteCursor(dutc);

  return;
}

static void failcnt_wstrb(TEST_testitem *testarg, UT_PIN pin, int cycle_cnt, int wstrb_data[DUTMAX][PATMAX], int failcnt_btm[DUTMAX][MAXBLKIOCNT][PATMAX], int *allpass, int *allfail)
{
  int pcnt;
  DutCursor dutc;
  UT_DUT dut;

  *allpass = 0x0;
  *allfail = 0x1;
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
#ifdef CHILD_SKIP
    if(SOCKET.dut_child[dut]==CHILD_SKIP) continue;
#endif
    for(pcnt=0; pcnt<cycle_cnt; pcnt++){
      failcnt_btm[dut-1][pin][pcnt]+=(wstrb_data[dut-1][pcnt]&0x1);

      *allpass|=(wstrb_data[dut-1][pcnt]&0x1);
      *allfail&=(wstrb_data[dut-1][pcnt]&0x1);
    }
    //if(dut==1) printf("%d", wstrb_data[0]);
  }
  UTL_DeleteCursor(dutc);
  printf("."); fflush(stdout);

  return;
}

static void print_setedge(TEST_testitem *testarg, int ref_point[MAXBLKIOCNT], int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX], int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX], UT_DUT dut, int pin, int pcnt, int avecnt)
{
  double set_edge = (0.5+(failcnt_set[dut-1][pin][pcnt]-ref_point[pin])/(double)avecnt)*JITTERARG.step;
  //printf(",%+e", set_edge);
  printf(",%5.1f", set_edge*1e12);
  return;
}
static void print_rstedge(TEST_testitem *testarg, int ref_point[MAXBLKIOCNT], int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX], int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX], UT_DUT dut, int pin, int pcnt, int avecnt)
{
  double rst_edge = (0.5+(failcnt_rst[dut-1][pin][pcnt]-ref_point[pin])/(double)avecnt)*JITTERARG.step;
  //printf(",%+e", rst_edge);
  printf(",%5.1f", rst_edge*1e12);
  return;
}
static void print_duty(TEST_testitem *testarg, int ref_point[MAXBLKIOCNT], int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX], int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX], UT_DUT dut, int pin, int pcnt, int avecnt)
{
  double duty = (failcnt_rst[dut-1][pin][pcnt]-failcnt_set[dut-1][pin][pcnt])/(double)avecnt*JITTERARG.step/JITTERARG.rate+0.5;
  //printf(",%+e", duty);
  printf(",%5.3f", duty);
  return;
}

static void dump_edge_duty(TEST_testitem *testarg, int cycle_cnt, int ref_point[MAXBLKIOCNT], int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX], int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX], int avecnt)
{
  int pin;
  int pcnt;
  UT_DUT dut;
  DutCursor dutc;
  double duty;
  double set_edge;
  double rst_edge;
  int i;
  char *kind[] = {"SET_EDGE [ps]", "RESET_EDGE [ps]", "DUTY"};
  void (* const print_func[])() = {print_setedge, print_rstedge, print_duty};

  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
#ifdef CHILD_SKIP
    if(SOCKET.dut_child[dut]==CHILD_SKIP) continue;
#endif
    for(i=0; i<3; i++){
      printf("DUT%d %s\n", dut, kind[i]);
      print_header(testarg);
      for(pcnt=0; pcnt<cycle_cnt; pcnt++){
        printf("%04d,%e", pcnt, pcnt*JITTERARG.rate);
        for(pin=0; pin<JITTERARG.pincnt; pin++){
          print_func[i](testarg, ref_point, failcnt_set, failcnt_rst, dut, pin, pcnt, avecnt);
        }
        printf("\n");
      }
      if(JITTERARG.ddr!=UT_ON){
        break;
      }
    }
  }
  UTL_DeleteCursor(dutc);

  return;
}

static void dump_ave_edge(TEST_testitem *testarg, int cycle_cnt, int ref_point[MAXBLKIOCNT], int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX], int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX], int avecnt)
{
  int pin;
  int pcnt;
  UT_DUT dut;
  DutCursor dutc;
  //double duty[DUTMAX][MAXBLKIOCNT]={0};
  double set_edge[DUTMAX][MAXBLKIOCNT]={0};
  //double rst_edge[DUTMAX][MAXBLKIOCNT]={0};
  int i;

  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
#ifdef CHILD_SKIP
    if(SOCKET.dut_child[dut]==CHILD_SKIP) continue;
#endif
    for(pin=0; pin<JITTERARG.pincnt; pin++){
      for(pcnt=0; pcnt<cycle_cnt; pcnt++){
        set_edge[dut-1][pin]+=((0.5+(failcnt_set[dut-1][pin][pcnt]-ref_point[pin])/(double)avecnt)*JITTERARG.step)/cycle_cnt;
        //rst_edge[dut-1][pin]+=((0.5+(failcnt_rst[dut-1][pin][pcnt]-ref_point[pin])/(double)avecnt)*JITTERARG.step)/cycle_cnt;
        //duty[dut-1][pin]+=((failcnt_rst[dut-1][pin][pcnt]-failcnt_set[dut-1][pin][pcnt])/(double)avecnt*JITTERARG.step/JITTERARG.rate+0.5)/cycle_cnt;
      }
    }
  }
  UTL_DeleteCursor(dutc);

  printf("AVERAGE SET_EDGE [ps]\ndut,");
  print_header(testarg);
  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
#ifdef CHILD_SKIP
    if(SOCKET.dut_child[dut]==CHILD_SKIP) continue;
#endif
    printf("%3d,%04d,%e", dut, 0, 0.0);
    for(pin=0; pin<JITTERARG.pincnt; pin++){
      printf(",%5.1f", set_edge[dut-1][pin]*1e12);
    }
    printf("\n");
  }

  return;
}

static void dump_last_edge(TEST_testitem *testarg, int cycle_cnt, int ref_point[MAXBLKIOCNT], int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX], int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX], int avecnt)
{
  int pin;
  int pcnt = cycle_cnt-1;
  UT_DUT dut;
  DutCursor dutc;
  double duty;
  double set_edge;
  double rst_edge;
  int i;
  char *kind[] = {"SET_EDGE [ps]", "RESET_EDGE [ps]"};
  void (* const print_func[])() = {print_setedge, print_rstedge};

  for(i=0; i<2; i++){
    printf("%s\ndut,", kind[i]);
    print_header(testarg);
    dutc = UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
#ifdef CHILD_SKIP
      if(SOCKET.dut_child[dut]==CHILD_SKIP) continue;
#endif
      printf("%3d,%04d,%e", dut, pcnt, pcnt*JITTERARG.rate);
      for(pin=0; pin<JITTERARG.pincnt; pin++){
        print_func[i](testarg, ref_point, failcnt_set, failcnt_rst, dut, pin, pcnt, avecnt);
      }
      printf("\n");
    }
    UTL_DeleteCursor(dutc);
    if(JITTERARG.ddr!=UT_ON){
      break;
    }
  }

  return;
}

static void print_top(TEST_testitem *testarg, int ref_point_top[MAXBLKIOCNT], int failcnt_top[DUTMAX][MAXBLKIOCNT][PATMAX], int ref_point_btm[MAXBLKIOCNT], int failcnt_btm[DUTMAX][MAXBLKIOCNT][PATMAX], UT_DUT dut, int pin, int pcnt)
{
  double top = ((JITTERARG.vih+JITTERARG.vt)/2+AMP_MARGIN)-(-0.5+ref_point_top[pin]-failcnt_top[dut-1][pin][pcnt])*JITTERARG.step;
  printf(",%5.3f", top);
  return;
}
static void print_btm(TEST_testitem *testarg, int ref_point_top[MAXBLKIOCNT], int failcnt_top[DUTMAX][MAXBLKIOCNT][PATMAX], int ref_point_btm[MAXBLKIOCNT], int failcnt_btm[DUTMAX][MAXBLKIOCNT][PATMAX], UT_DUT dut, int pin, int pcnt)
{
  double btm = ((JITTERARG.vil+JITTERARG.vt)/2-AMP_MARGIN)+(0.5+ref_point_btm[pin]-failcnt_btm[dut-1][pin][pcnt])*JITTERARG.step;
  printf(",%5.3f", btm);
  return;
}
static void print_amp(TEST_testitem *testarg, int ref_point_top[MAXBLKIOCNT], int failcnt_top[DUTMAX][MAXBLKIOCNT][PATMAX], int ref_point_btm[MAXBLKIOCNT], int failcnt_btm[DUTMAX][MAXBLKIOCNT][PATMAX], UT_DUT dut, int pin, int pcnt)
{
  double amp = ((JITTERARG.vih-JITTERARG.vil)/2+AMP_MARGIN*2)-((ref_point_top[pin]-failcnt_top[dut-1][pin][pcnt])+(ref_point_btm[pin]-failcnt_btm[dut-1][pin][pcnt]))*JITTERARG.step;
  printf(",%5.3f", amp);
  return;
}

static void dump_top_btm_amp(TEST_testitem *testarg, int cycle_cnt, int ref_point_top[MAXBLKIOCNT], int failcnt_top[DUTMAX][MAXBLKIOCNT][PATMAX], int ref_point_btm[MAXBLKIOCNT], int failcnt_btm[DUTMAX][MAXBLKIOCNT][PATMAX])
{
  int pin;
  int pcnt;
  UT_DUT dut;
  DutCursor dutc;
  double duty;
  double set_edge;
  double rst_edge;
  int i;
  char *kind[] = {"TOP [V]", "BOTTOM [V]", "AMPLITUDE [V]"};
  void (* const print_func[])() = {print_top, print_btm, print_amp};

  dutc = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
#ifdef CHILD_SKIP
    if(SOCKET.dut_child[dut]==CHILD_SKIP) continue;
#endif
    for(i=0; i<3; i++){
      printf("DUT%d %s\n", dut, kind[i]);
      print_header(testarg);
      for(pcnt=0; pcnt<cycle_cnt; pcnt++){
        printf("%04d,%e", pcnt, pcnt*JITTERARG.rate);
        for(pin=0; pin<JITTERARG.pincnt; pin++){
          print_func[i](testarg, ref_point_top, failcnt_top, ref_point_btm, failcnt_btm, dut, pin, pcnt);
        }
        printf("\n");
      }
    }
  }
  UTL_DeleteCursor(dutc);

  return;
}

static void dump_last_top_btm_amp(TEST_testitem *testarg, int cycle_cnt, int ref_point_top[MAXBLKIOCNT], int failcnt_top[DUTMAX][MAXBLKIOCNT][PATMAX], int ref_point_btm[MAXBLKIOCNT], int failcnt_btm[DUTMAX][MAXBLKIOCNT][PATMAX])
{
  int pin;
  int pcnt = cycle_cnt-1;
  UT_DUT dut;
  DutCursor dutc;
  double duty;
  double set_edge;
  double rst_edge;
  int i;
  char *kind[] = {"TOP [V]", "BOTTOM [V]", "AMPLITUDE [V]"};
  void (* const print_func[])() = {print_top, print_btm, print_amp};

  for(i=0; i<3; i++){
    printf("%s\ndut,", kind[i]);
    print_header(testarg);
    dutc = UTL_GetDutCursor(UT_CDUT);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
#ifdef CHILD_SKIP
      if(SOCKET.dut_child[dut]==CHILD_SKIP) continue;
#endif
      printf("%3d,%04d,%e", dut, pcnt, pcnt*JITTERARG.rate);
      for(pin=0; pin<JITTERARG.pincnt; pin++){
        print_func[i](testarg, ref_point_top, failcnt_top, ref_point_btm, failcnt_btm, dut, pin, pcnt);
      }
      printf("\n");
    }
  }
  UTL_DeleteCursor(dutc);

  return;
}

static void thermal_drift(TEST_testitem *testarg, int t)
{
  int i;
  CheckButton ov;
  DSlider ttotal;

  set_reg(UT_REG_IDX1, (int)(5.0/JITTERARG.rate/JITTERARG.ilmode)); // 1s per meas
  level_setting(testarg, 0.0);
  pin_list(1);
  pin_dummy();
  timing_setting(testarg, 0.0);
  UTL_ExecSbcal("calfile", "NOMBLOCKCHK,NOPBLOCKCHK,NOMBTYPECHK,NOMBIDCHK");
  UTL_StartTimer(UT_TIMER_R1US);
  for(i=0; i<t; i++){
    meas_fct(testarg, JITTERARG.pc);
  }
  ttotal = UTL_ReadTimer(&ov);
  printf("dummy pattern t=%e\n", ttotal);

  return;
}

void jitter_check(TEST_testitem *testarg)
{
  int i, j;
  int pin;
  UT_PIN dutpin;
  int limitflag;
  int cycle_cnt;
  int strb_max;
  int failcnt_set[DUTMAX][MAXBLKIOCNT][PATMAX] = {0};
  int failcnt_rst[DUTMAX][MAXBLKIOCNT][PATMAX] = {0};
  int allpass, allfail;
  int ref_point[MAXBLKIOCNT] = {0};
  int avecnt = 1;

#ifdef CHILD_SKIP
  printf("****************CHILD_SKIP(%d)\n", CHILD_SKIP);
#endif
  print_jitterarg(testarg);
  set_ilmode(JITTERARG.ilmode);

  //thermal_drift(testarg, 5);

  // for data capture
  cycle_cnt = JITTERARG.time_window/JITTERARG.rate+2;
  set_reg(UT_REG_IDX1, cycle_cnt/JITTERARG.ilmode-2);
  set_reg(UT_REG_IDX2, cycle_cnt/JITTERARG.ilmode/5-2);
  set_reg(UT_REG_IDX3, 100); // for sssc warm-up

  JITTERARG.level(testarg, 0.0);
  if(JITTERARG.prefunc!=NULL){
    JITTERARG.prefunc(testarg);
  }

  strb_max = (int)(STRB_LIMIT/JITTERARG.step);
  printf("\n");
  printf("cycle_cnt\t= %d\n", cycle_cnt);
  printf("step\t\t= %e\n", JITTERARG.step);
  printf("limit\t\t= +/-%e\n", STRB_LIMIT);
  printf("strb_max\t= %d\n", strb_max);
  printf("pin_cnt\t\t= %d\n", JITTERARG.pincnt);
  fflush(stdout);

  limitflag = 0;
  for(j=0; j<avecnt; j++){
    for(pin=0; pin<JITTERARG.pincnt; pin++){ // pin loop **********************************
      dutpin = SOCKET.dutblock_iopin[0][pin];
      printf("P%2d ", dutpin); fflush(stdout);
      JITTERARG.pinlist(dutpin);
      JITTERARG.pincond(testarg, UT_SIG_FH, UT_SIG_FL);
      set_ubm_capture(testarg);
  
      JITTERARG.timing(testarg, 0.0);
      clear_ubm(testarg, 0);
      UTL_ExecSbcal("calfile", "NOMBLOCKCHK,NOPBLOCKCHK,NOMBTYPECHK,NOMBIDCHK");
      meas_fct(testarg, JITTERARG.pc);
  
      // Search in the negative direction -------------------------------------------------
      i = 0;
      do{
        JITTERARG.timing(testarg, -i*JITTERARG.step);
        clear_ubm(testarg, 0);
        meas_fct(testarg, JITTERARG.pc);
        //read_dqs_status(1);
        if(DEBUG==1){
          break;
        }
  
        // Read UBM and post process per STRB
        failcnt(testarg, pin, cycle_cnt, failcnt_set, failcnt_rst, &allpass, &allfail);
  
        if(i>strb_max){
          limitflag = 1;
          printf("-limit!");
          break;
        }
        i++;
      }while(allfail!=0x1);
      printf("-step%02d ", i);
      ref_point[pin]+=i;
  
      // Search in the positive direction -------------------------------------------------
      i = 1;
      do{
        JITTERARG.timing(testarg, +i*JITTERARG.step);
        clear_ubm(testarg, 0);
        meas_fct(testarg, JITTERARG.pc);
        //read_dqs_status(1);
        if(DEBUG==1){
          break;
        }
  
        // Read UBM and post process per STRB
        failcnt(testarg, pin, cycle_cnt, failcnt_set, failcnt_rst, &allpass, &allfail);
  
        if(i>strb_max){
          limitflag = 1;
          printf("+limit!");
          break;
        }
        i++;
      }while(allpass!=0x0);
      printf("+step%02d ", i);
      printf("\n"); fflush(stdout);
    } // pin loop *************************************************************************
    printf("\n");
  }

  //dump_edge_duty(testarg, cycle_cnt, ref_point, failcnt_set, failcnt_rst, avecnt);
  dump_ave_edge(testarg, cycle_cnt, ref_point, failcnt_set, failcnt_rst, avecnt);
  //dump_last_edge(testarg, cycle_cnt, ref_point, failcnt_set, failcnt_rst, avecnt);

  if(limitflag!=0){
    printf("\nData collection ****FAIL\n");
    testresult_fail4alldut(testarg->testname);
  }
  else{
    printf("\nData collection PASS\n");
    testresult_pass4alldut(testarg->testname);
  }

  return;
}

void amp_check(TEST_testitem *testarg)
{
  int i, j;
  int pin;
  UT_PIN dutpin;
  int limitflag;
  int cycle_cnt;
  int step_max;
  int wstrb_data[DUTMAX][PATMAX] = {0};
  int failcnt_top[DUTMAX][MAXBLKIOCNT][PATMAX] = {0};
  int failcnt_btm[DUTMAX][MAXBLKIOCNT][PATMAX] = {0};
  int allpass, allfail;
  int ref_point_top[MAXBLKIOCNT] = {0};
  int ref_point_btm[MAXBLKIOCNT] = {0};
  double level_fh, level_fl;

#ifdef CHILD_SKIP
  printf("****************CHILD_SKIP(%d)\n", CHILD_SKIP);
#endif
  print_jitterarg(testarg);
  set_ilmode(JITTERARG.ilmode);

  //thermal_drift(testarg, 5);

  // for data capture
  cycle_cnt = JITTERARG.time_window/JITTERARG.rate+2;
  set_reg(UT_REG_IDX1, cycle_cnt/JITTERARG.ilmode-2);
  set_reg(UT_REG_IDX2, cycle_cnt/JITTERARG.ilmode/5-2);

  JITTERARG.level(testarg, 0.0);
  if(JITTERARG.prefunc!=NULL){
    JITTERARG.prefunc(testarg);
  }

  step_max = (int)(((JITTERARG.vih+JITTERARG.vil)/2/2+AMP_MARGIN)/JITTERARG.step);
  printf("\n");
  printf("cycle_cnt\t= %d\n", cycle_cnt);
  printf("step\t\t= %e\n", JITTERARG.step);
  printf("step_max\t= %d\n", step_max);
  printf("pin_cnt\t\t= %d\n", JITTERARG.pincnt);
  fflush(stdout);

  limitflag = 0;
  for(pin=0; pin<JITTERARG.pincnt; pin++){ // pin loop **********************************
    dutpin = SOCKET.dutblock_iopin[0][pin];
    printf("P%2d ", dutpin); fflush(stdout);
    JITTERARG.pinlist(dutpin);
    JITTERARG.pincond(testarg, UT_SIG_FH, UT_SIG_FL);
    set_ubm_capture(testarg);

    JITTERARG.timing(testarg, 0.0);
    JITTERARG.level(testarg, 0.0);
    clear_ubm(testarg, 0);
    UTL_ExecSbcal("calfile", "NOMBLOCKCHK,NOPBLOCKCHK,NOMBTYPECHK,NOMBIDCHK");
    meas_fct(testarg, JITTERARG.pc);

    // Bottom search --------------------------------------------------------------------
    // Search ref point for TTR ---
    JITTERARG.timing(testarg, -0.25*JITTERARG.rate);
    level_fl = -(JITTERARG.vih+JITTERARG.vil)/2/2-AMP_MARGIN;
    i = 0;
    do{
      JITTERARG.level(testarg, level_fl+i*JITTERARG.step);
      clear_ubm(testarg, 0);
      meas_fct(testarg, JITTERARG.pc);
      //read_dqs_status(1);
      if(DEBUG==1){
        break;
      }

      // Read UBM and post process
      failchk(testarg, cycle_cnt, 0, &allpass, &allfail);

      if(i>step_max){
        limitflag = 1;
        printf("-limit1!");
        break;
      }
      i++;
    }while(allfail!=0x1);
    printf("-step%03d ", i); fflush(stdout);
    ref_point_btm[pin] = i;

    // Search bottom point per cycle ---
    j = 0;
    do{
      JITTERARG.level(testarg, level_fl+(ref_point_btm[pin]-j)*JITTERARG.step);

      // Manual wstrb
      memset(wstrb_data, 0x0, sizeof(int)*DUTMAX*PATMAX);
      for(i=0; i<JITTERARG.rate/2/STRB_RESO; i++){
        JITTERARG.timing(testarg, -0.5*JITTERARG.rate+(i*STRB_RESO));
        clear_ubm(testarg, 0);
        meas_fct(testarg, JITTERARG.pc);
        //read_dqs_status(1);
        if(DEBUG==1){
          break;
        }

        // Read UBM and manual wstrb
        manual_wstrb(testarg, cycle_cnt, 0, wstrb_data);
      }
      // Accumulate wstrb data
      failcnt_wstrb(testarg, pin, cycle_cnt, wstrb_data, failcnt_btm, &allpass, &allfail);

      if(j>ref_point_btm[pin]){
        limitflag = 1;
        printf("-limit2!");
        break;
      }
      j++;
    }while(allpass!=0x0);
    printf("-wstrb%02d\n", j); fflush(stdout);

    // Top search -----------------------------------------------------------------------
    // Search ref point for TTR
    JITTERARG.timing(testarg, -0.25*JITTERARG.rate);
    level_fh = +(JITTERARG.vih+JITTERARG.vil)/2/2+AMP_MARGIN;
    i = 0;
    do{
      JITTERARG.level(testarg, level_fh-i*JITTERARG.step);
      clear_ubm(testarg, 0);
      meas_fct(testarg, JITTERARG.pc);
      //read_dqs_status(1);
      if(DEBUG==1){
        break;
      }

      // Read UBM and post process
      failchk(testarg, cycle_cnt, 1, &allpass, &allfail);

      if(i>step_max){
        limitflag = 1;
        printf("+limit1!");
        break;
      }
      i++;
    }while(allfail!=0x1);
    printf("    +step%03d ", i); fflush(stdout);
    ref_point_top[pin] = i;

    // Search top point per cycle ---
    j = 0;
    do{
      JITTERARG.level(testarg, level_fh-(ref_point_top[pin]-j)*JITTERARG.step);

      // Manual wstrb
      memset(wstrb_data, 0x0, sizeof(int)*DUTMAX*PATMAX);
      for(i=0; i<JITTERARG.rate/2/STRB_RESO; i++){
        JITTERARG.timing(testarg, -0.5*JITTERARG.rate+(i*STRB_RESO));
        clear_ubm(testarg, 0);
        meas_fct(testarg, JITTERARG.pc);
        //read_dqs_status(1);
        if(DEBUG==1){
          break;
        }

        // Read UBM and manual wstrb
        manual_wstrb(testarg, cycle_cnt, 1, wstrb_data);
      }
      // Accumulate wstrb data
      failcnt_wstrb(testarg, pin, cycle_cnt, wstrb_data, failcnt_top, &allpass, &allfail);

      if(j>ref_point_top[pin]){
        limitflag = 1;
        printf("+limit2!");
        break;
      }
      j++;
    }while(allpass!=0x0);
    printf("+wstrb%02d ", j); fflush(stdout);

    printf("\n"); fflush(stdout);
  } // pin loop *************************************************************************
  printf("\n");

  dump_top_btm_amp(testarg, cycle_cnt, ref_point_top, failcnt_top, ref_point_btm, failcnt_btm);
  //dump_last_top_btm_amp(testarg, cycle_cnt, ref_point_top, failcnt_top, ref_point_btm, failcnt_btm);

  if(limitflag!=0){
    printf("\nData collection ****FAIL\n");
    testresult_fail4alldut(testarg->testname);
  }
  else{
    printf("\nData collection PASS\n");
    testresult_pass4alldut(testarg->testname);
  }

  return;
}

void drift_check(TEST_testitem *testarg)
{
  CheckButton ov;
  DSlider ttotal;
  int i, j;
  UT_PIN dutpin;
  int pin;
  char *pfstr[] = {"*", "."};
  FctReadPinHandle rph;
  int n[16];
  UT_DUT dut;
  DutCursor dutc;
  int tch, child;
  char *childstr[] = {"A1", "A2"};

  print_jitterarg(testarg);
  set_ilmode(JITTERARG.ilmode);

  JITTERARG.level(testarg, 0.0);
  if(JITTERARG.prefunc!=NULL){
    JITTERARG.prefunc(testarg);
  }

  rph = UTL_GetFctReadPinHandle();
  UTL_SetFctReadPinMode(rph, UT_RES_STRB1_FAILED);

  for(pin=0; pin<JITTERARG.pincnt; pin++){ // pin loop **********************************
    dutpin = SOCKET.dutblock_iopin[0][pin];
    printf("P%d\n", dutpin); fflush(stdout);
    JITTERARG.pinlist(dutpin);
    JITTERARG.pincond(testarg, UT_SIG_FH, UT_SIG_FL);
  
    set_reg(UT_REG_IDX1, 0);
    set_reg(UT_REG_IDX2, 0);

    JITTERARG.timing(testarg, 0.0);
    UTL_ExecSbcal("calfile", "NOMBLOCKCHK,NOPBLOCKCHK,NOMBTYPECHK,NOMBIDCHK");
    meas_fct(testarg, JITTERARG.pc);

    for(j=0; j<300; j++){
      // Meas
      set_reg(UT_REG_IDX1, 1000);  // Dummy W
      set_reg(UT_REG_IDX2, 10000); // W&R
      memset(n, 0x0, sizeof(int)*16);
      UTL_StartTimer(UT_TIMER_R1US);
      for(i=-JITTERARG.rate/JITTERARG.step*0.10; i<JITTERARG.rate/JITTERARG.step*0.20; i++){
        JITTERARG.timing(testarg, i*JITTERARG.step);
        meas_fct(testarg, JITTERARG.pc);

        dutc = UTL_GetDutCursor(UT_CDUT);
        UTL_SetFctReadPinNumber(rph, CP_PIN(dutpin));
        while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
          UTL_SetFctReadPinDut(rph, dut);
          n[dut-1]+=UTL_ReadFctPin(rph);
          //printf("%s", pfstr[UTL_ReadFctPin(rph)]);
        }
        UTL_DeleteCursor(dutc);
      }
      ttotal = UTL_ReadTimer(&ov);
      dutc = UTL_GetDutCursor(UT_CDUT);
      UTL_SetFctReadPinNumber(rph, CP_PIN(dutpin));
      while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
        dutpin_to_testerch(dut, dutpin, &tch, &child);
        printf("DUT%02d,P%02d,P%03d%s,%3d,%f,%f\n", dut, dutpin, tch, childstr[child], j, n[dut-1]*JITTERARG.step*1e12, ttotal);
      }
      UTL_DeleteCursor(dutc);
      fflush(stdout);

#if 1
      // Dummy
      set_reg(UT_REG_IDX1, (int)(1.0/JITTERARG.rate/JITTERARG.ilmode)); // 1s per meas
      set_reg(UT_REG_IDX2, 0);
      UTL_StartTimer(UT_TIMER_R1US);
      meas_fct(testarg, JITTERARG.pc);
      ttotal = UTL_ReadTimer(&ov);
      //printf(" dummy t=%f\n", ttotal);
#endif
    }

    sleep(300);
  } // pin loop *************************************************************************

  UTL_DeleteHandle(rph);

  return;
}

