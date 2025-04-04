#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UTSC.h"
#include "test.h"
#include "test_struct.h"
#include "crc.h"

static void print_crcarg(TEST_testitem *testarg);
static void crc_pinlist(TEST_testitem *testarg);
static void crc_timing(TEST_testitem *testarg);
static void crc_level(TEST_testitem *testarg);
static void crc_burst(TEST_testitem *testarg);
static void crc_reg(TEST_testitem *testarg, USlider data[4], USlider crc);
static void crc_measfct(TEST_testitem *testarg);
static void crc_result(TEST_testitem *testarg);
static void print_crcarg(TEST_testitem *testarg);
static void crc_pinlist(TEST_testitem *testarg);
static void crc_timing(TEST_testitem *testarg);
static void crc_level(TEST_testitem *testarg);
static void crc_datagen(TEST_testitem *testarg, USlider data[4]);
static int bitcnt(long bits);
static void crc_dinv(TEST_testitem *testarg, USlider org_data[4], USlider dinv_data[4]);
static USlider crc_seri2para_crc(USlider s_crc[16]);
static void crc_para2seri_ddr4gddr5(TEST_testitem *testarg, USlider p_data[4], USlider s_data[72]);
static void crc_para2seri_ddr5(TEST_testitem *testarg, USlider p_data[4], USlider s_data[128]);
static void ecc_para2seri_lpddr5(TEST_testitem *testarg, USlider p_data[4], USlider s_data[144]);
static void crc_reg(TEST_testitem *testarg, USlider data[4], USlider crc);
static void crc_measfct(TEST_testitem *testarg);
static void crc_result(TEST_testitem *testarg);

static void print_crcarg(TEST_testitem *testarg){
  printf("\nilmode:\t\t%d\n", CRCARG.ilmode);
  printf("rate:\t\t%e\n", CRCARG.rate);
  printf("mapt:\t\t%s\n", CRCARG.mpat);
  printf("pc:\t\t0x%03x\n", CRCARG.pc);
  printf("bst:\t\t%d\n", CRCARG.bst);

  printf("crc_mode:\t");
  if(CRCARG.crcmode==CRC_CRC){
    printf("CRC\n");
  }
  else if(CRCARG.crcmode==CRC_CRCD){
    printf("CRCD\n");
  }
  else if(CRCARG.crcmode==CRC_CRCDM){
    printf("CRCDM\n");
  }

  printf("ddr_type:\t");
  if(CRCARG.ddrtype==CRC_DDR4){
    printf("DDR4\n");
  }
  else if(CRCARG.ddrtype==CRC_GDDR5){
    printf("GDDR5\n");
  }
  else if(CRCARG.ddrtype==CRC_DDR5){
    printf("DDR5\n");
  }
  else if(CRCARG.ddrtype==CRC_LPDDR5){
    printf("LPDDR5\n");
  }

  printf("m:\t\t%d\n", CRCARG.m);
  printf("fix:\t\t%d\n", CRCARG.fix);
  printf("act_mode:\t");
  if(CRCARG.actmode==CRC_LOW){
    printf("LOW\n");
  }
  else{
    printf("HIGH\n");
  }

  printf("dinv:\t\t");
  if(CRCARG.dinv==UT_OFF){
    printf("Disable\n");
  }
  else{
    printf("Enable\n");
  }

  printf("exp:\t\t");
  if(CRCARG.exp==0){
    printf("PASS\n");
  }
  else{
    printf("FAIL\n");
  }

  return;
}

static void crc_pinlist(TEST_testitem *testarg){
  RadioButton pin;

  UTL_CreatePinList("DQ_D");
  UTL_SetPinType("DQ_D", UT_PINTYPE_PIN);
  UTL_CreatePinList("DQ_C");
  UTL_SetPinType("DQ_C", UT_PINTYPE_PIN);
  for(pin=1; pin<=CRCARG.m; pin++){
    UTL_AddPinNumber("DQ_D", pin);
    UTL_AddPinNumber("DQ_C", pin+64);
  }

  UTL_CreatePinList("DBI_D");
  UTL_SetPinType("DBI_D", UT_PINTYPE_PIN);
  UTL_AddPinNumber("DBI_D", 17);

  UTL_CreatePinList("DBI_C");
  UTL_SetPinType("DBI_C", UT_PINTYPE_PIN);
  UTL_AddPinNumber("DBI_C", 17+64);

  UTL_CreatePinList("EDC_D");
  UTL_SetPinType("EDC_D", UT_PINTYPE_PIN);
  UTL_AddPinNumber("EDC_D", 18);

  UTL_CreatePinList("EDC_C");
  UTL_SetPinType("EDC_C", UT_PINTYPE_PIN);
  UTL_AddPinNumber("EDC_C", 18+64);

  return;
}

static void crc_timing(TEST_testitem *testarg){
  set_ilmode(CRCARG.ilmode);

  TgHandle Tg_H = UTL_GetTgHandle();

  UTL_AddTgRate    (Tg_H, 1, CRCARG.rate);

  UTL_AddTgBclk    (Tg_H, 1, 1, 0.0);
  UTL_AddTgCclk    (Tg_H, 1, 1, CRCARG.rate*0.50);

  UTL_AddTgDreL    (Tg_H, 1, 1, 0.0);
  UTL_AddTgDreT    (Tg_H, 1, 1, 0.0);

  UTL_AddTgStrb    (Tg_H, 1, 1, CRCARG.rate*0.25);
  UTL_AddTgStrb    (Tg_H, 1, 2, CRCARG.rate*0.75);

  UTL_SendTg       (Tg_H);
  UTL_DeleteHandle (Tg_H);

  return;
}

static void crc_level(TEST_testitem *testarg){
  ViHandle Vi_H = UTL_GetViHandle();
  UTL_SetViHigh    (Vi_H, 1.0);
  UTL_SetViLow     (Vi_H, 0.0);
  UTL_SendVi       (Vi_H, 1);
  UTL_DeleteHandle (Vi_H);

  VoHandle Vo_H = UTL_GetVoHandle();
  UTL_SetVoHigh    (Vo_H, 0.5);
  UTL_SetVoLow     (Vo_H, 0.5);
  UTL_SendVo       (Vo_H, 1);
  UTL_DeleteHandle (Vo_H);

  VtHandle Vt_H = UTL_GetVtHandle();
  UTL_SetVt        (Vt_H, 0.5);
  UTL_SendVt       (Vt_H, 1);
  UTL_DeleteHandle (Vt_H);

  return;
}

void crc_pin_ddr4(TEST_testitem *testarg){
  int i;
  PinHandle pinh;

  pinh = UTL_GetPinHandle();
  UTL_SetPinOpen(pinh, UT_ON);
  UTL_SendPin(pinh, SOCKET.all_iopinlist);

  //DR
  UTL_InitializePinHandle (pinh);
  UTL_SetPinViNumber      (pinh, 1);
  UTL_SetPinDrWaveform    (pinh, UT_WAV_DNRZ);
  UTL_SetPinDreNumber     (pinh, 1);
  UTL_SetPinDreWaveform   (pinh, UT_DREWAV_NRZ);
  UTL_SetPinDreClock      (pinh, 1);

  UTL_ClearPinPdsA(pinh);
  UTL_ClearPinPdsB(pinh);
  for(i=0; i<CRCARG.m; i++){
    UTL_AddPinPdsA(pinh, UT_SIG_D(i) , 2);
    UTL_AddPinPdsB(pinh, UT_SIG_SD(i), 2);
    if(CRCARG.m==4){
      UTL_AddPinPdsA(pinh, UT_SIG_D(i+8) , 3);
      UTL_AddPinPdsB(pinh, UT_SIG_D(i+12), 3);
    }
    else{ //m==8
      UTL_AddPinPdsA(pinh, UT_SIG_D(i+8), 3);
      UTL_AddPinPdsB(pinh, UT_SIG_FH    , 3);
    }
  }
  UTL_SendPin(pinh, "DQ_D");

  if(CRCARG.m==8){
    UTL_ClearPinPdsA(pinh);
    UTL_ClearPinPdsB(pinh);

    if(CRCARG.crcmode==CRC_CRC){
      UTL_AddPinPdsA(pinh, UT_SIG_FH, 3);
      UTL_AddPinPdsB(pinh, UT_SIG_FH, 3);
    }
    else if(CRCARG.crcmode==CRC_CRCD){
      UTL_AddPinPdsA(pinh, UT_SIG_D(16) , 2);
      UTL_AddPinPdsB(pinh, UT_SIG_SD(16), 2);
      UTL_AddPinPdsA(pinh, UT_SIG_FH    , 3);
      UTL_AddPinPdsB(pinh, UT_SIG_FH    , 3);
    }
    else if(CRCARG.crcmode==CRC_CRCDM){
      UTL_AddPinPdsA(pinh, UT_SIG_I_C(5), 2);
      UTL_AddPinPdsB(pinh, UT_SIG_I_C(6), 2);
      UTL_AddPinPdsA(pinh, UT_SIG_FH    , 3);
      UTL_AddPinPdsB(pinh, UT_SIG_FH    , 3);
    }
    UTL_SendPin(pinh, "DBI_D");
  }

  //CP
  UTL_InitializePinHandle (pinh);
  UTL_SetPinVoNumber      (pinh, 1);
  UTL_SetPinVtNumber      (pinh, 1);
  UTL_SetPinTerm          (pinh, UT_ON);
  UTL_AddPinStrbCpeNumber (pinh, 1, 1);
  UTL_AddPinExpStrbNumber (pinh, 1, UT_PIN_EXP_A);
  UTL_AddPinStrbCpeNumber (pinh, 2, 1);
  UTL_AddPinExpStrbNumber (pinh, 2, UT_PIN_EXP_B);

  UTL_ClearPinPdsA(pinh);
  UTL_ClearPinPdsB(pinh);
  for(i=0; i<CRCARG.m; i++){
    if(CRCARG.m==4){
      UTL_AddPinPdsA(pinh, UT_SIG_X(i)  , 3);
      UTL_AddPinPdsB(pinh, UT_SIG_X(i+4), 3);
    }
    else{ //m==8
      UTL_AddPinPdsA(pinh, UT_SIG_X(i)  , 3);
      UTL_AddPinPdsB(pinh, UT_SIG_FH    , 3);
    }
  }
  UTL_SendPin(pinh, "DQ_C");

  if(CRCARG.m==8){
    UTL_ClearPinPdsA(pinh);
    UTL_ClearPinPdsB(pinh);

    if(CRCARG.crcmode==CRC_CRC){
      UTL_AddPinPdsA(pinh, UT_SIG_FH, 3);
      UTL_AddPinPdsB(pinh, UT_SIG_FH, 3);
    }
    else if(CRCARG.crcmode==CRC_CRCD){
      UTL_AddPinPdsA(pinh, UT_SIG_FH    , 3);
      UTL_AddPinPdsB(pinh, UT_SIG_FH    , 3);
    }
    else if(CRCARG.crcmode==CRC_CRCDM){
      UTL_AddPinPdsA(pinh, UT_SIG_I_C(5), 2);
      UTL_AddPinPdsB(pinh, UT_SIG_I_C(6), 2);
      UTL_AddPinPdsA(pinh, UT_SIG_FH    , 3);
      UTL_AddPinPdsB(pinh, UT_SIG_FH    , 3);
    }
    UTL_SendPin(pinh, "DBI_C");
  }

  UTL_DeleteHandle(pinh);

  return;
}

void crc_pin_gddr5(TEST_testitem *testarg){
  int i;
  int cyp;
  PinHandle pinh;

  pinh = UTL_GetPinHandle();
  UTL_SetPinOpen(pinh, UT_ON);
  UTL_SendPin(pinh, SOCKET.all_iopinlist);

  //DR
  UTL_InitializePinHandle (pinh);
  UTL_SetPinViNumber      (pinh, 1);
  UTL_SetPinDrWaveform    (pinh, UT_WAV_DNRZ);
  UTL_SetPinDreNumber     (pinh, 1);
  UTL_SetPinDreWaveform   (pinh, UT_DREWAV_NRZ);
  UTL_SetPinDreClock      (pinh, 1);

  UTL_ClearPinPdsA(pinh);
  UTL_ClearPinPdsB(pinh);
  for(i=0; i<8; i++){
    for(cyp=2; cyp<=5; cyp++){
      UTL_AddPinPdsA(pinh, UT_SIG_D(i) , cyp);
      UTL_AddPinPdsB(pinh, UT_SIG_SD(i), cyp);
    }
  }
  UTL_SendPin(pinh, "DQ_D");

  UTL_ClearPinPdsA(pinh);
  UTL_ClearPinPdsB(pinh);
  for(cyp=2; cyp<=5; cyp++){
    if(CRCARG.crcmode==CRC_CRCDM){
      UTL_AddPinPdsA(pinh, UT_SIG_I_C(5), cyp);
      UTL_AddPinPdsB(pinh, UT_SIG_I_C(6), cyp);
    }
    else{
      UTL_AddPinPdsA(pinh, UT_SIG_D(16) , cyp);
      UTL_AddPinPdsB(pinh, UT_SIG_SD(16), cyp);
    }
  }
  UTL_SendPin(pinh, "DBI_D");

  UTL_ClearPinPdsA(pinh);
  UTL_ClearPinPdsB(pinh);
  i = 8;
  for(cyp=2; cyp<=5; cyp++){
    UTL_AddPinPdsA(pinh, UT_SIG_D(i++), cyp);
    UTL_AddPinPdsB(pinh, UT_SIG_D(i++), cyp);
  }
  UTL_SendPin(pinh, "EDC_D");

  //CP
  UTL_InitializePinHandle (pinh);
  UTL_SetPinVoNumber      (pinh, 1);
  UTL_SetPinVtNumber      (pinh, 1);
  UTL_SetPinTerm          (pinh, UT_ON);
  UTL_AddPinStrbCpeNumber (pinh, 1, 1);
  UTL_AddPinExpStrbNumber (pinh, 1, UT_PIN_EXP_A);
  UTL_AddPinStrbCpeNumber (pinh, 2, 1);
  UTL_AddPinExpStrbNumber (pinh, 2, UT_PIN_EXP_B);

  UTL_ClearPinPdsA(pinh);
  UTL_ClearPinPdsB(pinh);
  i = 0;
  for(cyp=2; cyp<=5; cyp++){
    UTL_AddPinPdsA(pinh, UT_SIG_X(i++), cyp);
    UTL_AddPinPdsB(pinh, UT_SIG_X(i++), cyp);
  }
  UTL_SendPin(pinh, "EDC_C");

  UTL_DeleteHandle(pinh);

  return;
}

void crc_pin_ddr5(TEST_testitem *testarg){
  int i;
  PinHandle pinh;

  pinh = UTL_GetPinHandle();
  UTL_SetPinOpen(pinh, UT_ON);
  UTL_SendPin(pinh, SOCKET.all_iopinlist);

  //DR
  UTL_InitializePinHandle (pinh);
  UTL_SetPinViNumber      (pinh, 1);
  UTL_SetPinDrWaveform    (pinh, UT_WAV_DNRZ);
  UTL_SetPinDreNumber     (pinh, 1);
  UTL_SetPinDreWaveform   (pinh, UT_DREWAV_NRZ);
  UTL_SetPinDreClock      (pinh, 1);

  UTL_ClearPinPdsA(pinh);
  UTL_ClearPinPdsB(pinh);
  for(i=0; i<CRCARG.m; i++){
    UTL_AddPinPdsA(pinh, UT_SIG_D(i) , 2);
    UTL_AddPinPdsB(pinh, UT_SIG_SD(i), 2);
    if(i<4){
      UTL_AddPinPdsA(pinh, UT_SIG_D(i+8) , 3);
      UTL_AddPinPdsB(pinh, UT_SIG_D(i+12), 3);
    }
    else{
      UTL_AddPinPdsA(pinh, UT_SIG_SD(i-4+8) , 3);
      UTL_AddPinPdsB(pinh, UT_SIG_SD(i-4+12), 3);
    }
  }
  UTL_SendPin(pinh, "DQ_D");

  //CP
  UTL_InitializePinHandle (pinh);
  UTL_SetPinVoNumber      (pinh, 1);
  UTL_SetPinVtNumber      (pinh, 1);
  UTL_SetPinTerm          (pinh, UT_ON);
  UTL_AddPinStrbCpeNumber (pinh, 1, 1);
  UTL_AddPinExpStrbNumber (pinh, 1, UT_PIN_EXP_A);
  UTL_AddPinStrbCpeNumber (pinh, 2, 1);
  UTL_AddPinExpStrbNumber (pinh, 2, UT_PIN_EXP_B);

  UTL_ClearPinPdsA(pinh);
  UTL_ClearPinPdsB(pinh);
  for(i=0; i<CRCARG.m; i++){
    if(i<4){
      UTL_AddPinPdsA(pinh, UT_SIG_X(i)  , 3);
      UTL_AddPinPdsB(pinh, UT_SIG_X(i+4), 3);
    }
    else{
      UTL_AddPinPdsA(pinh, UT_SIG_X(i-4+8) , 3);
      UTL_AddPinPdsB(pinh, UT_SIG_X(i-4+12), 3);
    }
  }
  UTL_SendPin(pinh, "DQ_C");

  UTL_DeleteHandle(pinh);

  return;
}

void ecc_pin_lpddr5(TEST_testitem *testarg){
  int i;
  int cyp;
  PinHandle pinh;

  pinh = UTL_GetPinHandle();
  UTL_SetPinOpen(pinh, UT_ON);
  UTL_SendPin(pinh, SOCKET.all_iopinlist);

  //DR
  UTL_InitializePinHandle (pinh);
  UTL_SetPinViNumber      (pinh, 1);
  UTL_SetPinDrWaveform    (pinh, UT_WAV_DNRZ);
  UTL_SetPinDreNumber     (pinh, 1);
  UTL_SetPinDreWaveform   (pinh, UT_DREWAV_NRZ);
  UTL_SetPinDreClock      (pinh, 1);

  UTL_ClearPinPdsA(pinh);
  UTL_ClearPinPdsB(pinh);
  for(i=0; i<8; i++){
    for(cyp=2; cyp<=9; cyp++){
      UTL_AddPinPdsA(pinh, UT_SIG_D(i) , cyp);
      UTL_AddPinPdsB(pinh, UT_SIG_SD(i), cyp);
    }
  }
  UTL_SendPin(pinh, "DQ_D");

  UTL_ClearPinPdsA(pinh);
  UTL_ClearPinPdsB(pinh);
  for(cyp=2; cyp<=9; cyp++){
    if(CRCARG.crcmode==CRC_CRCDM){
      UTL_AddPinPdsA(pinh, UT_SIG_I_C(5), cyp);
      UTL_AddPinPdsB(pinh, UT_SIG_I_C(6), cyp);
    }
    else{
      UTL_AddPinPdsA(pinh, UT_SIG_D(16) , cyp);
      UTL_AddPinPdsB(pinh, UT_SIG_SD(16), cyp);
    }
  }
  UTL_SendPin(pinh, "DBI_D");

  UTL_ClearPinPdsA(pinh);
  UTL_ClearPinPdsB(pinh);
  if(CRCARG.crcmode==CRC_CRCDM){
    UTL_AddPinPdsA(pinh, UT_SIG_FL    , 2);
    UTL_AddPinPdsB(pinh, UT_SIG_SD(9) , 2);
  }
  else{
    UTL_AddPinPdsA(pinh, UT_SIG_FL    , 2);
    UTL_AddPinPdsB(pinh, UT_SIG_D(9)  , 2);
  }
  UTL_AddPinPdsA(pinh, UT_SIG_SD(10), 3);
  UTL_AddPinPdsB(pinh, UT_SIG_SD(11), 3);
  UTL_AddPinPdsA(pinh, UT_SIG_SD(12), 4);
  UTL_AddPinPdsB(pinh, UT_SIG_SD(13), 4);
  UTL_AddPinPdsA(pinh, UT_SIG_SD(14), 5);
  UTL_AddPinPdsB(pinh, UT_SIG_D(8)  , 5);
  UTL_AddPinPdsA(pinh, UT_SIG_D(9)  , 6);
  UTL_AddPinPdsB(pinh, UT_SIG_D(10) , 6);
  UTL_AddPinPdsA(pinh, UT_SIG_D(11) , 7);
  UTL_AddPinPdsB(pinh, UT_SIG_D(12) , 7);
  UTL_AddPinPdsA(pinh, UT_SIG_D(13) , 8);
  UTL_AddPinPdsB(pinh, UT_SIG_D(14) , 8);
  UTL_AddPinPdsA(pinh, UT_SIG_D(15) , 9);
  UTL_AddPinPdsB(pinh, UT_SIG_SD(8) , 9);
  UTL_SendPin(pinh, "EDC_D");

  //CP
  UTL_InitializePinHandle (pinh);
  UTL_SetPinVoNumber      (pinh, 1);
  UTL_SetPinVtNumber      (pinh, 1);
  UTL_SetPinTerm          (pinh, UT_ON);
  UTL_AddPinStrbCpeNumber (pinh, 1, 1);
  UTL_AddPinExpStrbNumber (pinh, 1, UT_PIN_EXP_A);
  UTL_AddPinStrbCpeNumber (pinh, 2, 1);
  UTL_AddPinExpStrbNumber (pinh, 2, UT_PIN_EXP_B);

  UTL_ClearPinPdsA(pinh);
  UTL_ClearPinPdsB(pinh);
  i = 9;
  UTL_AddPinPdsA(pinh, UT_SIG_FL         , 2);
  UTL_AddPinPdsB(pinh, UT_SIG_X((i++)%15), 2);
  for(cyp=3; cyp<=9; cyp++){
    UTL_AddPinPdsA(pinh, UT_SIG_X((i++)%15), cyp);
    UTL_AddPinPdsB(pinh, UT_SIG_X((i++)%15), cyp);
  }
  UTL_SendPin(pinh, "EDC_C");

  UTL_DeleteHandle(pinh);

  return;
}

static void crc_burst(TEST_testitem *testarg){
  BurstScramHandle BurstScram_H = UTL_GetBurstScramHandle();

  UTL_SetBurstScramMode             (BurstScram_H, UT_ON);
  UTL_SetBurstScramDdrType          (BurstScram_H, 5);
  UTL_SetBurstScramBaseFileName     (BurstScram_H, NULL);
  //UTL_SetBurstScramDdrType          (BurstScram_H, 0);
  //UTL_SetBurstScramBaseFileName     (BurstScram_H, "fsbscrddr_BL16");
  UTL_SetBurstScramDataRate         (BurstScram_H, 2);
  UTL_SetBurstScramLength           (BurstScram_H, CRCARG.bst);
  UTL_SetBurstScramWrapType         (BurstScram_H, UT_WPTSQ);
  UTL_AddBurstScramWriteSignal      (BurstScram_H, UT_SIG_WT);
  UTL_SetBurstScramAddrUnit         (BurstScram_H, UT_UNIT_PDS, UT_ON);
  UTL_SetBurstScramAddrUnit         (BurstScram_H, UT_UNIT_DFM, UT_ON);
  UTL_SetBurstScramAddrUnit         (BurstScram_H, UT_UNIT_FP , UT_ON);
  UTL_SendBurstScram                (BurstScram_H);
  UTL_DeleteHandle                  (BurstScram_H);

  return;
}

static void crc_datagen(TEST_testitem *testarg, USlider data[4]){
  USlider dbi;
  int i;

  if(CRCARG.dinv==UT_ON){
    dbi = 0x0;
  }
  else{
    dbi = 0x10000;
  }

  struct timeval tv;
  gettimeofday(&tv, NULL);
  srand(tv.tv_sec + tv.tv_usec);

  for(i=0; i<4; i++){
    data[i] = dbi|(rand()&((0x1<<CRCARG.m)-1));
  }
#if 0
  data[0]=0x10001; //for debug
  data[1]=0x10002;
  data[2]=0x10003;
  data[3]=0x10004;
#endif
  printf("data[4]:\t0x%05x, 0x%05x, 0x%05x, 0x%05x\n", data[0], data[1], data[2], data[3]);

  return;
}

static int bitcnt(long bits){
  bits = (bits & 0x55555555) + (bits >> 1 & 0x55555555);
  bits = (bits & 0x33333333) + (bits >> 2 & 0x33333333);
  bits = (bits & 0x0f0f0f0f) + (bits >> 4 & 0x0f0f0f0f);
  bits = (bits & 0x00ff00ff) + (bits >> 8 & 0x00ff00ff);
  return (bits & 0x0000ffff) + (bits >>16 & 0x0000ffff);
}

static void crc_dinv(TEST_testitem *testarg, USlider org_data[4], USlider dinv_data[4]){
  int i;

  memcpy(dinv_data, org_data, sizeof(USlider)*4);

  if(CRCARG.dinv==UT_ON){
    for(i=0; i<4; i++){
      if(bitcnt(org_data[i]&0x100ff)<5){
        dinv_data[i]^=0x100ff;
      }
    }
    printf("dinv_data[4]:\t0x%05x, 0x%05x, 0x%05x, 0x%05x\n", dinv_data[0], dinv_data[1], dinv_data[2], dinv_data[3]);
  }

  return;
}

static USlider crc_seri2para_crc(USlider s_crc[16]){
  int i;
  USlider p_crc = 0x0;

  for(i=0; i<16; i++){
    p_crc|=(s_crc[i]<<i);
  }
  printf("crc:\t\t0x%04x\n", p_crc);

  return(p_crc);
}

static void crc_para2seri_ddr4gddr5(TEST_testitem *testarg, USlider p_data[4], USlider s_data[72]){
  int i, j;
  int bst, bit;
  int bitno[8] = {0,1,2,3, 0,1,2,3}; //TP1,TP2,TP1,TP2
  USlider d;

  for(i=0; i<72; i++){
    s_data[i] = CRCARG.fix;
  }

  for(bst=0; bst<CRCARG.bst; bst++){
    for(bit=0; bit<CRCARG.m; bit++){
      s_data[bit*8+((bit/8)*8)+bst] = (p_data[bitno[bst]]>>bit)&0x1;
    }

    //DBI
    if(CRCARG.m==8){
      bit = 16;
      if(CRCARG.crcmode==CRC_CRC){
        d = CRCARG.fix;
      }
      else{
        if(CRCARG.crcmode==CRC_CRCDM){
          if((bst==2)||(bst==5)){ //see pattern
            d = 0x1;
          }
          else{
            d = 0x0;
          }
        }
        else{
          d = (p_data[bitno[bst]]>>bit)&0x1;
        }
        if(CRCARG.actmode==CRC_LOW){
          d^=0x1;
        }
      }
      s_data[64+bst] = d;
    }
  }

  //Print
  for(bit=0; bit<8; bit++){
    printf("\tDQ%d:\t", bit);
    for(bst=0; bst<8; bst++){
      printf("%d", s_data[bit*8+bst]);
    }
    printf("\n");
  }
  bit = 8;
  printf("\tDBI:\t", bit);
  for(bst=0; bst<8; bst++){
    printf("%d", s_data[bit*8+bst]);
  }
  printf("\n");

  return;
}

//CRC8_D72(ATM) for DDR4/GDDR5
USlider crc_calc_ddr4gddr5(TEST_testitem *testarg, USlider p_data[4]){
  USlider s_data[72];
  USlider s_crc[16];
  USlider p_crc;

  crc_para2seri_ddr4gddr5(testarg, p_data, s_data);

  s_crc[ 0] = s_data[ 69]^s_data[ 68]^s_data[ 67]^s_data[ 66]^s_data[ 64]^s_data[ 63]^s_data[ 60]^s_data[ 56]^s_data[ 54]^s_data[ 53]^s_data[ 52]^s_data[ 50]^s_data[ 49]^s_data[ 48]^s_data[ 45]^s_data[ 43]^s_data[ 40]^s_data[ 39]^s_data[ 35]^s_data[ 34]^s_data[ 31]^s_data[ 30]^s_data[ 28]^s_data[ 23]^s_data[ 21]^s_data[ 19]^s_data[ 18]^s_data[ 16]^s_data[ 14]^s_data[ 12]^s_data[  8]^s_data[  7]^s_data[  6]^s_data[  0];
  s_crc[ 1] = s_data[ 70]^s_data[ 66]^s_data[ 65]^s_data[ 63]^s_data[ 61]^s_data[ 60]^s_data[ 57]^s_data[ 56]^s_data[ 55]^s_data[ 52]^s_data[ 51]^s_data[ 48]^s_data[ 46]^s_data[ 45]^s_data[ 44]^s_data[ 43]^s_data[ 41]^s_data[ 39]^s_data[ 36]^s_data[ 34]^s_data[ 32]^s_data[ 30]^s_data[ 29]^s_data[ 28]^s_data[ 24]^s_data[ 23]^s_data[ 22]^s_data[ 21]^s_data[ 20]^s_data[ 18]^s_data[ 17]^s_data[ 16]^s_data[ 15]^s_data[ 14]^s_data[ 13]^s_data[ 12]^s_data[  9]^s_data[  6]^s_data[  1]^s_data[  0];
  s_crc[ 2] = s_data[ 71]^s_data[ 69]^s_data[ 68]^s_data[ 63]^s_data[ 62]^s_data[ 61]^s_data[ 60]^s_data[ 58]^s_data[ 57]^s_data[ 54]^s_data[ 50]^s_data[ 48]^s_data[ 47]^s_data[ 46]^s_data[ 44]^s_data[ 43]^s_data[ 42]^s_data[ 39]^s_data[ 37]^s_data[ 34]^s_data[ 33]^s_data[ 29]^s_data[ 28]^s_data[ 25]^s_data[ 24]^s_data[ 22]^s_data[ 17]^s_data[ 15]^s_data[ 13]^s_data[ 12]^s_data[ 10]^s_data[  8]^s_data[  6]^s_data[  2]^s_data[  1]^s_data[  0];
  s_crc[ 3] = s_data[ 70]^s_data[ 69]^s_data[ 64]^s_data[ 63]^s_data[ 62]^s_data[ 61]^s_data[ 59]^s_data[ 58]^s_data[ 55]^s_data[ 51]^s_data[ 49]^s_data[ 48]^s_data[ 47]^s_data[ 45]^s_data[ 44]^s_data[ 43]^s_data[ 40]^s_data[ 38]^s_data[ 35]^s_data[ 34]^s_data[ 30]^s_data[ 29]^s_data[ 26]^s_data[ 25]^s_data[ 23]^s_data[ 18]^s_data[ 16]^s_data[ 14]^s_data[ 13]^s_data[ 11]^s_data[  9]^s_data[  7]^s_data[  3]^s_data[  2]^s_data[  1];
  s_crc[ 4] = s_data[ 71]^s_data[ 70]^s_data[ 65]^s_data[ 64]^s_data[ 63]^s_data[ 62]^s_data[ 60]^s_data[ 59]^s_data[ 56]^s_data[ 52]^s_data[ 50]^s_data[ 49]^s_data[ 48]^s_data[ 46]^s_data[ 45]^s_data[ 44]^s_data[ 41]^s_data[ 39]^s_data[ 36]^s_data[ 35]^s_data[ 31]^s_data[ 30]^s_data[ 27]^s_data[ 26]^s_data[ 24]^s_data[ 19]^s_data[ 17]^s_data[ 15]^s_data[ 14]^s_data[ 12]^s_data[ 10]^s_data[  8]^s_data[  4]^s_data[  3]^s_data[  2];
  s_crc[ 5] = s_data[ 71]^s_data[ 66]^s_data[ 65]^s_data[ 64]^s_data[ 63]^s_data[ 61]^s_data[ 60]^s_data[ 57]^s_data[ 53]^s_data[ 51]^s_data[ 50]^s_data[ 49]^s_data[ 47]^s_data[ 46]^s_data[ 45]^s_data[ 42]^s_data[ 40]^s_data[ 37]^s_data[ 36]^s_data[ 32]^s_data[ 31]^s_data[ 28]^s_data[ 27]^s_data[ 25]^s_data[ 20]^s_data[ 18]^s_data[ 16]^s_data[ 15]^s_data[ 13]^s_data[ 11]^s_data[  9]^s_data[  5]^s_data[  4]^s_data[  3];
  s_crc[ 6] = s_data[ 67]^s_data[ 66]^s_data[ 65]^s_data[ 64]^s_data[ 62]^s_data[ 61]^s_data[ 58]^s_data[ 54]^s_data[ 52]^s_data[ 51]^s_data[ 50]^s_data[ 48]^s_data[ 47]^s_data[ 46]^s_data[ 43]^s_data[ 41]^s_data[ 38]^s_data[ 37]^s_data[ 33]^s_data[ 32]^s_data[ 29]^s_data[ 28]^s_data[ 26]^s_data[ 21]^s_data[ 19]^s_data[ 17]^s_data[ 16]^s_data[ 14]^s_data[ 12]^s_data[ 10]^s_data[  6]^s_data[  5]^s_data[  4];
  s_crc[ 7] = s_data[ 68]^s_data[ 67]^s_data[ 66]^s_data[ 65]^s_data[ 63]^s_data[ 62]^s_data[ 59]^s_data[ 55]^s_data[ 53]^s_data[ 52]^s_data[ 51]^s_data[ 49]^s_data[ 48]^s_data[ 47]^s_data[ 44]^s_data[ 42]^s_data[ 39]^s_data[ 38]^s_data[ 34]^s_data[ 33]^s_data[ 30]^s_data[ 29]^s_data[ 27]^s_data[ 22]^s_data[ 20]^s_data[ 18]^s_data[ 17]^s_data[ 15]^s_data[ 13]^s_data[ 11]^s_data[  7]^s_data[  6]^s_data[  5];
  s_crc[ 8] = 0x0; //s_data[141]^s_data[140]^s_data[139]^s_data[138]^s_data[136]^s_data[135]^s_data[132]^s_data[128]^s_data[126]^s_data[125]^s_data[124]^s_data[122]^s_data[121]^s_data[120]^s_data[117]^s_data[115]^s_data[112]^s_data[111]^s_data[107]^s_data[106]^s_data[103]^s_data[102]^s_data[100]^s_data[ 95]^s_data[ 93]^s_data[ 91]^s_data[ 90]^s_data[ 88]^s_data[ 86]^s_data[ 84]^s_data[ 80]^s_data[ 79]^s_data[ 78]^s_data[ 72];
  s_crc[ 9] = 0x0; //s_data[142]^s_data[138]^s_data[137]^s_data[135]^s_data[133]^s_data[132]^s_data[129]^s_data[128]^s_data[127]^s_data[124]^s_data[123]^s_data[120]^s_data[118]^s_data[117]^s_data[116]^s_data[115]^s_data[113]^s_data[111]^s_data[108]^s_data[106]^s_data[104]^s_data[102]^s_data[101]^s_data[100]^s_data[ 96]^s_data[ 95]^s_data[ 94]^s_data[ 93]^s_data[ 92]^s_data[ 90]^s_data[ 89]^s_data[ 88]^s_data[ 87]^s_data[ 86]^s_data[ 85]^s_data[ 84]^s_data[ 81]^s_data[ 78]^s_data[ 73]^s_data[ 72];
  s_crc[10] = 0x0; //s_data[143]^s_data[141]^s_data[140]^s_data[135]^s_data[134]^s_data[133]^s_data[132]^s_data[130]^s_data[129]^s_data[126]^s_data[122]^s_data[120]^s_data[119]^s_data[118]^s_data[116]^s_data[115]^s_data[114]^s_data[111]^s_data[109]^s_data[106]^s_data[105]^s_data[101]^s_data[100]^s_data[ 97]^s_data[ 96]^s_data[ 94]^s_data[ 89]^s_data[ 87]^s_data[ 85]^s_data[ 84]^s_data[ 82]^s_data[ 80]^s_data[ 78]^s_data[ 74]^s_data[ 73]^s_data[ 72];
  s_crc[11] = 0x0; //s_data[142]^s_data[141]^s_data[136]^s_data[135]^s_data[134]^s_data[133]^s_data[131]^s_data[130]^s_data[127]^s_data[123]^s_data[121]^s_data[120]^s_data[119]^s_data[117]^s_data[116]^s_data[115]^s_data[112]^s_data[110]^s_data[107]^s_data[106]^s_data[102]^s_data[101]^s_data[ 98]^s_data[ 97]^s_data[ 95]^s_data[ 90]^s_data[ 88]^s_data[ 86]^s_data[ 85]^s_data[ 83]^s_data[ 81]^s_data[ 79]^s_data[ 75]^s_data[ 74]^s_data[ 73];
  s_crc[12] = 0x0; //s_data[143]^s_data[142]^s_data[137]^s_data[136]^s_data[135]^s_data[134]^s_data[132]^s_data[131]^s_data[128]^s_data[124]^s_data[122]^s_data[121]^s_data[120]^s_data[118]^s_data[117]^s_data[116]^s_data[113]^s_data[111]^s_data[108]^s_data[107]^s_data[103]^s_data[102]^s_data[ 99]^s_data[ 98]^s_data[ 96]^s_data[ 91]^s_data[ 89]^s_data[ 87]^s_data[ 86]^s_data[ 84]^s_data[ 82]^s_data[ 80]^s_data[ 76]^s_data[ 75]^s_data[ 74];
  s_crc[13] = 0x0; //s_data[143]^s_data[138]^s_data[137]^s_data[136]^s_data[135]^s_data[133]^s_data[132]^s_data[129]^s_data[125]^s_data[123]^s_data[122]^s_data[121]^s_data[119]^s_data[118]^s_data[117]^s_data[114]^s_data[112]^s_data[109]^s_data[108]^s_data[104]^s_data[103]^s_data[100]^s_data[ 99]^s_data[ 97]^s_data[ 92]^s_data[ 90]^s_data[ 88]^s_data[ 87]^s_data[ 85]^s_data[ 83]^s_data[ 81]^s_data[ 77]^s_data[ 76]^s_data[ 75];
  s_crc[14] = 0x0; //s_data[139]^s_data[138]^s_data[137]^s_data[136]^s_data[134]^s_data[133]^s_data[130]^s_data[126]^s_data[124]^s_data[123]^s_data[122]^s_data[120]^s_data[119]^s_data[118]^s_data[115]^s_data[113]^s_data[110]^s_data[109]^s_data[105]^s_data[104]^s_data[101]^s_data[100]^s_data[ 98]^s_data[ 93]^s_data[ 91]^s_data[ 89]^s_data[ 88]^s_data[ 86]^s_data[ 84]^s_data[ 82]^s_data[ 78]^s_data[ 77]^s_data[ 76];
  s_crc[15] = 0x0; //s_data[140]^s_data[139]^s_data[138]^s_data[137]^s_data[135]^s_data[134]^s_data[131]^s_data[127]^s_data[125]^s_data[124]^s_data[123]^s_data[121]^s_data[120]^s_data[119]^s_data[116]^s_data[114]^s_data[111]^s_data[110]^s_data[106]^s_data[105]^s_data[102]^s_data[101]^s_data[ 99]^s_data[ 94]^s_data[ 92]^s_data[ 90]^s_data[ 89]^s_data[ 87]^s_data[ 85]^s_data[ 83]^s_data[ 79]^s_data[ 78]^s_data[ 77];

  p_crc = crc_seri2para_crc(s_crc);

  return(p_crc);
}

static void crc_para2seri_ddr5(TEST_testitem *testarg, USlider p_data[4], USlider s_data[128]){
  int i;
  int bst, bit;
  int bitno[16] = {0,1,2,3, 0,1,2,3, 2,3,0,1, 2,3,0,1}; //TP1,TP2,TP1,TP2, TP2,TP1,TP2,TP1
  USlider d;

  for(i=0; i<128; i++){
    s_data[i] = CRCARG.fix;
  }

  for(bst=0; bst<CRCARG.bst; bst++){
    for(bit=0; bit<CRCARG.m; bit++){
      s_data[(bit/4)*64+bst*4+bit%4] = (p_data[bitno[bst]]>>bit)&0x1;
    }
  }

  //Print
  for(bit=0; bit<CRCARG.m; bit++){
    printf("\tDQ%d:\t", bit);
    for(bst=0; bst<16; bst++){
      printf("%d", s_data[(bit/4)*64+bst*4+bit%4]);
    }
    printf("\n");
  }

  return;
}

//CRC8_D64 for DDR5
USlider crc_calc_ddr5(TEST_testitem *testarg, USlider p_data[4]){
  USlider s_data[128];
  USlider s_crc[16];
  USlider p_crc;

  crc_para2seri_ddr5(testarg, p_data, s_data);

  s_crc[ 0] = s_data[ 63]^s_data[ 60]^s_data[ 56]^s_data[ 54]^s_data[ 53]^s_data[ 52]^s_data[ 50]^s_data[ 49]^s_data[ 48]^s_data[ 45]^s_data[ 43]^s_data[ 40]^s_data[ 39]^s_data[ 35]^s_data[ 34]^s_data[ 31]^s_data[ 30]^s_data[ 28]^s_data[ 23]^s_data[ 21]^s_data[ 19]^s_data[ 18]^s_data[ 16]^s_data[ 14]^s_data[ 12]^s_data[  8]^s_data[  7]^s_data[  6]^s_data[  0];
  s_crc[ 1] = s_data[ 63]^s_data[ 61]^s_data[ 60]^s_data[ 57]^s_data[ 56]^s_data[ 55]^s_data[ 52]^s_data[ 51]^s_data[ 48]^s_data[ 46]^s_data[ 45]^s_data[ 44]^s_data[ 43]^s_data[ 41]^s_data[ 39]^s_data[ 36]^s_data[ 34]^s_data[ 32]^s_data[ 30]^s_data[ 29]^s_data[ 28]^s_data[ 24]^s_data[ 23]^s_data[ 22]^s_data[ 21]^s_data[ 20]^s_data[ 18]^s_data[ 17]^s_data[ 16]^s_data[ 15]^s_data[ 14]^s_data[ 13]^s_data[ 12]^s_data[  9]^s_data[  6]^s_data[  1]^s_data[  0];
  s_crc[ 2] = s_data[ 63]^s_data[ 62]^s_data[ 61]^s_data[ 60]^s_data[ 58]^s_data[ 57]^s_data[ 54]^s_data[ 50]^s_data[ 48]^s_data[ 47]^s_data[ 46]^s_data[ 44]^s_data[ 43]^s_data[ 42]^s_data[ 39]^s_data[ 37]^s_data[ 34]^s_data[ 33]^s_data[ 29]^s_data[ 28]^s_data[ 25]^s_data[ 24]^s_data[ 22]^s_data[ 17]^s_data[ 15]^s_data[ 13]^s_data[ 12]^s_data[ 10]^s_data[  8]^s_data[  6]^s_data[  2]^s_data[  1]^s_data[  0];
  s_crc[ 3] = s_data[ 63]^s_data[ 62]^s_data[ 61]^s_data[ 59]^s_data[ 58]^s_data[ 55]^s_data[ 51]^s_data[ 49]^s_data[ 48]^s_data[ 47]^s_data[ 45]^s_data[ 44]^s_data[ 43]^s_data[ 40]^s_data[ 38]^s_data[ 35]^s_data[ 34]^s_data[ 30]^s_data[ 29]^s_data[ 26]^s_data[ 25]^s_data[ 23]^s_data[ 18]^s_data[ 16]^s_data[ 14]^s_data[ 13]^s_data[ 11]^s_data[  9]^s_data[  7]^s_data[  3]^s_data[  2]^s_data[  1];
  s_crc[ 4] = s_data[ 63]^s_data[ 62]^s_data[ 60]^s_data[ 59]^s_data[ 56]^s_data[ 52]^s_data[ 50]^s_data[ 49]^s_data[ 48]^s_data[ 46]^s_data[ 45]^s_data[ 44]^s_data[ 41]^s_data[ 39]^s_data[ 36]^s_data[ 35]^s_data[ 31]^s_data[ 30]^s_data[ 27]^s_data[ 26]^s_data[ 24]^s_data[ 19]^s_data[ 17]^s_data[ 15]^s_data[ 14]^s_data[ 12]^s_data[ 10]^s_data[  8]^s_data[  4]^s_data[  3]^s_data[  2];
  s_crc[ 5] = s_data[ 63]^s_data[ 61]^s_data[ 60]^s_data[ 57]^s_data[ 53]^s_data[ 51]^s_data[ 50]^s_data[ 49]^s_data[ 47]^s_data[ 46]^s_data[ 45]^s_data[ 42]^s_data[ 40]^s_data[ 37]^s_data[ 36]^s_data[ 32]^s_data[ 31]^s_data[ 28]^s_data[ 27]^s_data[ 25]^s_data[ 20]^s_data[ 18]^s_data[ 16]^s_data[ 15]^s_data[ 13]^s_data[ 11]^s_data[  9]^s_data[  5]^s_data[  4]^s_data[  3];
  s_crc[ 6] = s_data[ 62]^s_data[ 61]^s_data[ 58]^s_data[ 54]^s_data[ 52]^s_data[ 51]^s_data[ 50]^s_data[ 48]^s_data[ 47]^s_data[ 46]^s_data[ 43]^s_data[ 41]^s_data[ 38]^s_data[ 37]^s_data[ 33]^s_data[ 32]^s_data[ 29]^s_data[ 28]^s_data[ 26]^s_data[ 21]^s_data[ 19]^s_data[ 17]^s_data[ 16]^s_data[ 14]^s_data[ 12]^s_data[ 10]^s_data[  6]^s_data[  5]^s_data[  4];
  s_crc[ 7] = s_data[ 63]^s_data[ 62]^s_data[ 59]^s_data[ 55]^s_data[ 53]^s_data[ 52]^s_data[ 51]^s_data[ 49]^s_data[ 48]^s_data[ 47]^s_data[ 44]^s_data[ 42]^s_data[ 39]^s_data[ 38]^s_data[ 34]^s_data[ 33]^s_data[ 30]^s_data[ 29]^s_data[ 27]^s_data[ 22]^s_data[ 20]^s_data[ 18]^s_data[ 17]^s_data[ 15]^s_data[ 13]^s_data[ 11]^s_data[  7]^s_data[  6]^s_data[  5];
  s_crc[ 8] = s_data[127]^s_data[124]^s_data[120]^s_data[118]^s_data[117]^s_data[116]^s_data[114]^s_data[113]^s_data[112]^s_data[109]^s_data[107]^s_data[104]^s_data[103]^s_data[ 99]^s_data[ 98]^s_data[ 95]^s_data[ 94]^s_data[ 92]^s_data[ 87]^s_data[ 85]^s_data[ 83]^s_data[ 82]^s_data[ 80]^s_data[ 78]^s_data[ 76]^s_data[ 72]^s_data[ 71]^s_data[ 70]^s_data[ 64];
  s_crc[ 9] = s_data[127]^s_data[125]^s_data[124]^s_data[121]^s_data[120]^s_data[119]^s_data[116]^s_data[115]^s_data[112]^s_data[110]^s_data[109]^s_data[108]^s_data[107]^s_data[105]^s_data[103]^s_data[100]^s_data[ 98]^s_data[ 96]^s_data[ 94]^s_data[ 93]^s_data[ 92]^s_data[ 88]^s_data[ 87]^s_data[ 86]^s_data[ 85]^s_data[ 84]^s_data[ 82]^s_data[ 81]^s_data[ 80]^s_data[ 79]^s_data[ 78]^s_data[ 77]^s_data[ 76]^s_data[ 73]^s_data[ 70]^s_data[ 65]^s_data[ 64];
  s_crc[10] = s_data[127]^s_data[126]^s_data[125]^s_data[124]^s_data[122]^s_data[121]^s_data[118]^s_data[114]^s_data[112]^s_data[111]^s_data[110]^s_data[108]^s_data[107]^s_data[106]^s_data[103]^s_data[101]^s_data[ 98]^s_data[ 97]^s_data[ 93]^s_data[ 92]^s_data[ 89]^s_data[ 88]^s_data[ 86]^s_data[ 81]^s_data[ 79]^s_data[ 77]^s_data[ 76]^s_data[ 74]^s_data[ 72]^s_data[ 70]^s_data[ 66]^s_data[ 65]^s_data[ 64];
  s_crc[11] = s_data[127]^s_data[126]^s_data[125]^s_data[123]^s_data[122]^s_data[119]^s_data[115]^s_data[113]^s_data[112]^s_data[111]^s_data[109]^s_data[108]^s_data[107]^s_data[104]^s_data[102]^s_data[ 99]^s_data[ 98]^s_data[ 94]^s_data[ 93]^s_data[ 90]^s_data[ 89]^s_data[ 87]^s_data[ 82]^s_data[ 80]^s_data[ 78]^s_data[ 77]^s_data[ 75]^s_data[ 73]^s_data[ 71]^s_data[ 67]^s_data[ 66]^s_data[ 65];
  s_crc[12] = s_data[127]^s_data[126]^s_data[124]^s_data[123]^s_data[120]^s_data[116]^s_data[114]^s_data[113]^s_data[112]^s_data[110]^s_data[109]^s_data[108]^s_data[105]^s_data[103]^s_data[100]^s_data[ 99]^s_data[ 95]^s_data[ 94]^s_data[ 91]^s_data[ 90]^s_data[ 88]^s_data[ 83]^s_data[ 81]^s_data[ 79]^s_data[ 78]^s_data[ 76]^s_data[ 74]^s_data[ 72]^s_data[ 68]^s_data[ 67]^s_data[ 66];
  s_crc[13] = s_data[127]^s_data[125]^s_data[124]^s_data[121]^s_data[117]^s_data[115]^s_data[114]^s_data[113]^s_data[111]^s_data[110]^s_data[109]^s_data[106]^s_data[104]^s_data[101]^s_data[100]^s_data[ 96]^s_data[ 95]^s_data[ 92]^s_data[ 91]^s_data[ 89]^s_data[ 84]^s_data[ 82]^s_data[ 80]^s_data[ 79]^s_data[ 77]^s_data[ 75]^s_data[ 73]^s_data[ 69]^s_data[ 68]^s_data[ 67];
  s_crc[14] = s_data[126]^s_data[125]^s_data[122]^s_data[118]^s_data[116]^s_data[115]^s_data[114]^s_data[112]^s_data[111]^s_data[110]^s_data[107]^s_data[105]^s_data[102]^s_data[101]^s_data[ 97]^s_data[ 96]^s_data[ 93]^s_data[ 92]^s_data[ 90]^s_data[ 85]^s_data[ 83]^s_data[ 81]^s_data[ 80]^s_data[ 78]^s_data[ 76]^s_data[ 74]^s_data[ 70]^s_data[ 69]^s_data[ 68];
  s_crc[15] = s_data[127]^s_data[126]^s_data[123]^s_data[119]^s_data[117]^s_data[116]^s_data[115]^s_data[113]^s_data[112]^s_data[111]^s_data[108]^s_data[106]^s_data[103]^s_data[102]^s_data[ 98]^s_data[ 97]^s_data[ 94]^s_data[ 93]^s_data[ 91]^s_data[ 86]^s_data[ 84]^s_data[ 82]^s_data[ 81]^s_data[ 79]^s_data[ 77]^s_data[ 75]^s_data[ 71]^s_data[ 70]^s_data[ 69];

  p_crc = crc_seri2para_crc(s_crc);
  if(CRCARG.m==4){
    p_crc&=0xff;
  }

  return(p_crc);
}

static void ecc_para2seri_lpddr5(TEST_testitem *testarg, USlider p_data[4], USlider s_data[144]){
  int i;
  int bst, bit;
  int bitno[16] = {0,1,2,3, 0,1,2,3, 2,3,0,1, 2,3,0,1}; //TP1,TP2,TP1,TP2, TP2,TP1,TP2,TP1
  USlider d;

  for(i=0; i<144; i++){
    s_data[i] = CRCARG.fix;
  }

  for(bst=0; bst<CRCARG.bst; bst++){
    for(bit=0; bit<CRCARG.m; bit++){
      s_data[bst*8+bit] = (p_data[bitno[bst]]>>bit)&0x1;
    }
  }

  //DMI
  for(bst=0; bst<CRCARG.bst; bst++){
    if((CRCARG.crcmode==CRC_CRCDM)&&((bst==2)||(bst==5))){ //see pattern
      s_data[128+bst] = 0;
    }
    else{
      s_data[128+bst] = (p_data[bitno[bst]]>>16)&0x1;
    }
  }

  //Print
  for(bit=0; bit<CRCARG.m; bit++){
    printf("\tDQ%d:\t", bit);
    for(bst=0; bst<16; bst++){
      printf("%d", s_data[bst*8+bit]);
    }
    printf("\n");
  }
  printf("\tDMI:\t");
  for(bst=0; bst<CRCARG.bst; bst++){
    printf("%d", s_data[128+bst]);
  }
  printf("\n");

  return;
}

//ECC for LPDDR5
USlider ecc_calc_lpddr5(TEST_testitem *testarg, USlider p_data[4]){
  USlider s_data[144];
  USlider s_ecc[16];
  USlider p_ecc;

  ecc_para2seri_lpddr5(testarg, p_data, s_data);

  s_ecc[ 0] = s_data[127]^s_data[125]^s_data[123]^s_data[121]^s_data[119]^s_data[117]^s_data[115]^s_data[113]^s_data[111]^s_data[109]^s_data[107]^s_data[105]^s_data[103]^s_data[101]^s_data[ 99]^s_data[ 97]^s_data[ 95]^s_data[ 93]^s_data[ 91]^s_data[ 89]^s_data[ 87]^s_data[ 85]^s_data[ 83]^s_data[ 81]^s_data[ 79]^s_data[ 77]^s_data[ 75]^s_data[ 73]^s_data[ 71]^s_data[ 69]^s_data[ 67]^s_data[ 65]^s_data[ 63]^s_data[ 61]^s_data[ 59]^s_data[ 57]^s_data[ 55]^s_data[ 53]^s_data[ 51]^s_data[ 49]^s_data[ 47]^s_data[ 45]^s_data[ 43]^s_data[ 41]^s_data[ 39]^s_data[ 37]^s_data[ 35]^s_data[ 33]^s_data[ 31]^s_data[ 29]^s_data[ 27]^s_data[ 25]^s_data[ 23]^s_data[ 21]^s_data[ 19]^s_data[ 17]^s_data[ 15]^s_data[ 13]^s_data[ 11]^s_data[  9]^s_data[  7]^s_data[  5]^s_data[  3]^s_data[  1];
  s_ecc[ 1] = s_data[127]^s_data[126]^s_data[123]^s_data[122]^s_data[119]^s_data[118]^s_data[115]^s_data[114]^s_data[111]^s_data[110]^s_data[107]^s_data[106]^s_data[103]^s_data[102]^s_data[ 99]^s_data[ 98]^s_data[ 95]^s_data[ 94]^s_data[ 91]^s_data[ 90]^s_data[ 87]^s_data[ 86]^s_data[ 83]^s_data[ 82]^s_data[ 79]^s_data[ 78]^s_data[ 75]^s_data[ 74]^s_data[ 71]^s_data[ 70]^s_data[ 67]^s_data[ 66]^s_data[ 63]^s_data[ 62]^s_data[ 59]^s_data[ 58]^s_data[ 55]^s_data[ 54]^s_data[ 51]^s_data[ 50]^s_data[ 47]^s_data[ 46]^s_data[ 43]^s_data[ 42]^s_data[ 39]^s_data[ 38]^s_data[ 35]^s_data[ 34]^s_data[ 31]^s_data[ 30]^s_data[ 27]^s_data[ 26]^s_data[ 23]^s_data[ 22]^s_data[ 19]^s_data[ 18]^s_data[ 15]^s_data[ 14]^s_data[ 11]^s_data[ 10]^s_data[  7]^s_data[  6]^s_data[  3]^s_data[  2];
  s_ecc[ 2] = s_data[127]^s_data[126]^s_data[125]^s_data[124]^s_data[119]^s_data[118]^s_data[117]^s_data[116]^s_data[111]^s_data[110]^s_data[109]^s_data[108]^s_data[103]^s_data[102]^s_data[101]^s_data[100]^s_data[ 95]^s_data[ 94]^s_data[ 93]^s_data[ 92]^s_data[ 87]^s_data[ 86]^s_data[ 85]^s_data[ 84]^s_data[ 79]^s_data[ 78]^s_data[ 77]^s_data[ 76]^s_data[ 71]^s_data[ 70]^s_data[ 69]^s_data[ 68]^s_data[ 63]^s_data[ 62]^s_data[ 61]^s_data[ 60]^s_data[ 55]^s_data[ 54]^s_data[ 53]^s_data[ 52]^s_data[ 47]^s_data[ 46]^s_data[ 45]^s_data[ 44]^s_data[ 39]^s_data[ 38]^s_data[ 37]^s_data[ 36]^s_data[ 31]^s_data[ 30]^s_data[ 29]^s_data[ 28]^s_data[ 23]^s_data[ 22]^s_data[ 21]^s_data[ 20]^s_data[ 15]^s_data[ 14]^s_data[ 13]^s_data[ 12]^s_data[  7]^s_data[  6]^s_data[  5]^s_data[  4];
  s_ecc[ 3] = s_data[127]^s_data[126]^s_data[125]^s_data[124]^s_data[123]^s_data[122]^s_data[121]^s_data[120]^s_data[103]^s_data[102]^s_data[101]^s_data[100]^s_data[ 99]^s_data[ 98]^s_data[ 97]^s_data[ 96]^s_data[ 95]^s_data[ 94]^s_data[ 93]^s_data[ 92]^s_data[ 91]^s_data[ 90]^s_data[ 89]^s_data[ 88]^s_data[ 71]^s_data[ 70]^s_data[ 69]^s_data[ 68]^s_data[ 67]^s_data[ 66]^s_data[ 65]^s_data[ 64]^s_data[ 55]^s_data[ 54]^s_data[ 53]^s_data[ 52]^s_data[ 51]^s_data[ 50]^s_data[ 49]^s_data[ 48]^s_data[ 47]^s_data[ 46]^s_data[ 45]^s_data[ 44]^s_data[ 43]^s_data[ 42]^s_data[ 41]^s_data[ 40]^s_data[ 23]^s_data[ 22]^s_data[ 21]^s_data[ 20]^s_data[ 19]^s_data[ 18]^s_data[ 17]^s_data[ 16]^s_data[  7]^s_data[  6]^s_data[  5]^s_data[  4]^s_data[  3]^s_data[  2]^s_data[  1]^s_data[  0];
  s_ecc[ 4] = s_data[127]^s_data[126]^s_data[125]^s_data[124]^s_data[123]^s_data[122]^s_data[121]^s_data[120]^s_data[103]^s_data[102]^s_data[101]^s_data[100]^s_data[ 99]^s_data[ 98]^s_data[ 97]^s_data[ 96]^s_data[ 87]^s_data[ 86]^s_data[ 85]^s_data[ 84]^s_data[ 83]^s_data[ 82]^s_data[ 81]^s_data[ 80]^s_data[ 79]^s_data[ 78]^s_data[ 77]^s_data[ 76]^s_data[ 75]^s_data[ 74]^s_data[ 73]^s_data[ 72]^s_data[ 55]^s_data[ 54]^s_data[ 53]^s_data[ 52]^s_data[ 51]^s_data[ 50]^s_data[ 49]^s_data[ 48]^s_data[ 39]^s_data[ 38]^s_data[ 37]^s_data[ 36]^s_data[ 35]^s_data[ 34]^s_data[ 33]^s_data[ 32]^s_data[ 31]^s_data[ 30]^s_data[ 29]^s_data[ 28]^s_data[ 27]^s_data[ 26]^s_data[ 25]^s_data[ 24]^s_data[  7]^s_data[  6]^s_data[  5]^s_data[  4]^s_data[  3]^s_data[  2]^s_data[  1]^s_data[  0];
  s_ecc[ 5] = s_data[119]^s_data[118]^s_data[117]^s_data[116]^s_data[115]^s_data[114]^s_data[113]^s_data[112]^s_data[111]^s_data[110]^s_data[109]^s_data[108]^s_data[107]^s_data[106]^s_data[105]^s_data[104]^s_data[ 95]^s_data[ 94]^s_data[ 93]^s_data[ 92]^s_data[ 91]^s_data[ 90]^s_data[ 89]^s_data[ 88]^s_data[ 79]^s_data[ 78]^s_data[ 77]^s_data[ 76]^s_data[ 75]^s_data[ 74]^s_data[ 73]^s_data[ 72]^s_data[ 55]^s_data[ 54]^s_data[ 53]^s_data[ 52]^s_data[ 51]^s_data[ 50]^s_data[ 49]^s_data[ 48]^s_data[ 39]^s_data[ 38]^s_data[ 37]^s_data[ 36]^s_data[ 35]^s_data[ 34]^s_data[ 33]^s_data[ 32]^s_data[ 23]^s_data[ 22]^s_data[ 21]^s_data[ 20]^s_data[ 19]^s_data[ 18]^s_data[ 17]^s_data[ 16]^s_data[ 15]^s_data[ 14]^s_data[ 13]^s_data[ 12]^s_data[ 11]^s_data[ 10]^s_data[  9]^s_data[  8];
  s_ecc[ 6] = s_data[119]^s_data[118]^s_data[117]^s_data[116]^s_data[115]^s_data[114]^s_data[113]^s_data[112]^s_data[103]^s_data[102]^s_data[101]^s_data[100]^s_data[ 99]^s_data[ 98]^s_data[ 97]^s_data[ 96]^s_data[ 87]^s_data[ 86]^s_data[ 85]^s_data[ 84]^s_data[ 83]^s_data[ 82]^s_data[ 81]^s_data[ 80]^s_data[ 71]^s_data[ 70]^s_data[ 69]^s_data[ 68]^s_data[ 67]^s_data[ 66]^s_data[ 65]^s_data[ 64]^s_data[ 63]^s_data[ 62]^s_data[ 61]^s_data[ 60]^s_data[ 59]^s_data[ 58]^s_data[ 57]^s_data[ 56]^s_data[ 47]^s_data[ 46]^s_data[ 45]^s_data[ 44]^s_data[ 43]^s_data[ 42]^s_data[ 41]^s_data[ 40]^s_data[ 31]^s_data[ 30]^s_data[ 29]^s_data[ 28]^s_data[ 27]^s_data[ 26]^s_data[ 25]^s_data[ 24]^s_data[ 15]^s_data[ 14]^s_data[ 13]^s_data[ 12]^s_data[ 11]^s_data[ 10]^s_data[  9]^s_data[  8];
  s_ecc[ 7] = s_data[127]^s_data[126]^s_data[125]^s_data[124]^s_data[123]^s_data[122]^s_data[121]^s_data[120]^s_data[111]^s_data[110]^s_data[109]^s_data[108]^s_data[107]^s_data[106]^s_data[105]^s_data[104]^s_data[ 95]^s_data[ 94]^s_data[ 93]^s_data[ 92]^s_data[ 91]^s_data[ 90]^s_data[ 89]^s_data[ 88]^s_data[ 79]^s_data[ 78]^s_data[ 77]^s_data[ 76]^s_data[ 75]^s_data[ 74]^s_data[ 73]^s_data[ 72]^s_data[ 63]^s_data[ 62]^s_data[ 61]^s_data[ 60]^s_data[ 59]^s_data[ 58]^s_data[ 57]^s_data[ 56]^s_data[ 47]^s_data[ 46]^s_data[ 45]^s_data[ 44]^s_data[ 43]^s_data[ 42]^s_data[ 41]^s_data[ 40]^s_data[ 31]^s_data[ 30]^s_data[ 29]^s_data[ 28]^s_data[ 27]^s_data[ 26]^s_data[ 25]^s_data[ 24]^s_data[ 15]^s_data[ 14]^s_data[ 13]^s_data[ 12]^s_data[ 11]^s_data[ 10]^s_data[  9]^s_data[  8];
  s_ecc[ 8] = s_data[127]^s_data[126]^s_data[125]^s_data[124]^s_data[123]^s_data[122]^s_data[121]^s_data[120]^s_data[119]^s_data[118]^s_data[117]^s_data[116]^s_data[115]^s_data[114]^s_data[113]^s_data[112]^s_data[111]^s_data[110]^s_data[109]^s_data[108]^s_data[107]^s_data[106]^s_data[105]^s_data[104]^s_data[103]^s_data[102]^s_data[101]^s_data[100]^s_data[ 99]^s_data[ 98]^s_data[ 97]^s_data[ 96]^s_data[ 95]^s_data[ 94]^s_data[ 93]^s_data[ 92]^s_data[ 91]^s_data[ 90]^s_data[ 89]^s_data[ 88]^s_data[ 87]^s_data[ 86]^s_data[ 85]^s_data[ 84]^s_data[ 83]^s_data[ 82]^s_data[ 81]^s_data[ 80]^s_data[ 79]^s_data[ 78]^s_data[ 77]^s_data[ 76]^s_data[ 75]^s_data[ 74]^s_data[ 73]^s_data[ 72]^s_data[ 71]^s_data[ 70]^s_data[ 69]^s_data[ 68]^s_data[ 67]^s_data[ 66]^s_data[ 65]^s_data[ 64]^s_data[ 63]^s_data[ 62]^s_data[ 61]^s_data[ 60]^s_data[ 59]^s_data[ 58]^s_data[ 57]^s_data[ 56]^s_data[ 55]^s_data[ 54]^s_data[ 53]^s_data[ 52]^s_data[ 51]^s_data[ 50]^s_data[ 49]^s_data[ 48]^s_data[ 47]^s_data[ 46]^s_data[ 45]^s_data[ 44]^s_data[ 43]^s_data[ 42]^s_data[ 41]^s_data[ 40]^s_data[ 39]^s_data[ 38]^s_data[ 37]^s_data[ 36]^s_data[ 35]^s_data[ 34]^s_data[ 33]^s_data[ 32]^s_data[ 31]^s_data[ 30]^s_data[ 29]^s_data[ 28]^s_data[ 27]^s_data[ 26]^s_data[ 25]^s_data[ 24]^s_data[ 23]^s_data[ 22]^s_data[ 21]^s_data[ 20]^s_data[ 19]^s_data[ 18]^s_data[ 17]^s_data[ 16]^s_data[ 15]^s_data[ 14]^s_data[ 13]^s_data[ 12]^s_data[ 11]^s_data[ 10]^s_data[  9]^s_data[  8]^s_data[  7]^s_data[  6]^s_data[  5]^s_data[  4]^s_data[  3]^s_data[  2]^s_data[  1]^s_data[  0];

  //for DMI
  s_ecc[ 9] = s_data[143]^s_data[141]^s_data[139]^s_data[137]^s_data[135]^s_data[133]^s_data[131]^s_data[129];
  s_ecc[10] = s_data[143]^s_data[142]^s_data[139]^s_data[138]^s_data[135]^s_data[134]^s_data[131]^s_data[130];
  s_ecc[11] = s_data[143]^s_data[142]^s_data[141]^s_data[140]^s_data[139]^s_data[138]^s_data[137]^s_data[136]^s_data[131]^s_data[130]^s_data[129]^s_data[128];
  s_ecc[12] = s_data[143]^s_data[142]^s_data[141]^s_data[140]^s_data[135]^s_data[134]^s_data[133]^s_data[132]^s_data[131]^s_data[130]^s_data[129]^s_data[128];
  s_ecc[13] = s_data[143]^s_data[142]^s_data[141]^s_data[140]^s_data[139]^s_data[138]^s_data[137]^s_data[136]^s_data[135]^s_data[134]^s_data[133]^s_data[132];
  s_ecc[14] = s_data[143]^s_data[142]^s_data[141]^s_data[140]^s_data[139]^s_data[138]^s_data[137]^s_data[136]^s_data[135]^s_data[134]^s_data[133]^s_data[132]^s_data[131]^s_data[130]^s_data[129]^s_data[128];

  s_ecc[15] = 0x0;

  p_ecc = crc_seri2para_crc(s_ecc);

  return(p_ecc);
}

static void crc_reg(TEST_testitem *testarg, USlider data[4], USlider crc){
  RegHandle regh = UTL_GetRegHandle();
  UTL_SetRegCpe2(regh, UT_SIG_C(9));
  UTL_SendReg(regh);
  UTL_DeleteHandle(regh);

  if(CRCARG.exp!=0){
    crc^=0xffff;
  }

  set_reg(UT_REG_DINVD , 0x1ff);
  set_reg(UT_REG_TPH   , data[0]);
  set_reg(UT_REG_TPH2  , data[1]);
  set_reg(UT_REG_TPH_2 , data[2]);
  set_reg(UT_REG_TPH2_2, data[3]);
  set_reg(UT_REG_XT    , crc);

  return;
}

static void crc_measfct(TEST_testitem *testarg){
  UTL_ExecSbcal("cal", "NORMAL,NOMBTYPECHK,NOMBLOCKCHK,NOMBIDCHK,NOPBLOCKCHK");

  FctHandle fcth = UTL_GetFctHandle();
  UTL_SetFctMpatName    (fcth, CRCARG.mpat);
  UTL_SetFctFailInhibit (fcth, UT_ON);
  UTL_SetFctStartPc     (fcth, CRCARG.pc);
  UTL_MeasFct           (fcth);
  UTL_DeleteHandle      (fcth);

  return;
}

static void crc_result(TEST_testitem *testarg){
  int result = 0;
  RadioButton ut_res[2] = {UT_RES_PASSED, UT_RES_FAILED};
  DutCursor dutcur;
  UT_DUT dut;

  dutcur = UTL_GetDutCursor(UT_CDUT);
  while((dut=UTL_NextDut(dutcur))!=UT_NOMORE){
    if(UTL_ReadMeasResult(dut)!=ut_res[CRCARG.exp]){
      result++;
    }
  }
  UTL_DeleteCursor (dutcur);

  if(result==0){
    testresult_pass4alldut(testarg->testname);
  }
  else{
    testresult_fail4alldut(testarg->testname);
  }

  return;
}

void crc_check(TEST_testitem *testarg){
  USlider data[4];
  USlider p_data[4];
  USlider crc;

  print_crcarg(testarg);

  crc_pinlist(testarg);
  crc_timing(testarg);
  crc_level(testarg);
  CRCARG.pinfunc(testarg);
  crc_burst(testarg);

  crc_datagen(testarg, data);
  crc_dinv(testarg, data, p_data);
  crc = CRCARG.crcfunc(testarg, p_data);
  crc_reg(testarg, data, crc);

  crc_measfct(testarg);
  crc_result(testarg);

  return;
}

