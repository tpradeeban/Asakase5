#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "UTSC.h"
#include "test.h"
#include "test_struct.h"
#include "drcp.h"

#define TCYC 100e-9
//#define LONG 100e-6
#define LONG 500e-9
#define KK 17
#define SINGLE_STRB 1
#define DOUBLE_STRB 2

#define DEBUG 1
#define DUTNUM 32
#define JIG 0
#define CHECK_ReadFct 0

//--------------------------Handle Declare----------------------------
TestHandle		TEST_;

VsHandle		VS_[10];
ViHandle		IN_[10];
VoHandle		OUT_[10];
VtHandle		VT_[10];
IlHandle		IL_[10];

TgHandle		TG_;
RegHandle		REG_;


PinHandle		P1_,PD25_;
PinHandle		IOPIN_,HCDRPIN_,ALLPIN_;

PowerCtrlHandle		CTRL_;
PowerSeqHandle		SEQ_;
DcHandle		ISVM_;
DcHandle		VSIM_;
DcHandle		VSVM_;
SettlingTimeHandle	SETTLING_; 
DctHandle		DCT_,DCT2_;
FctHandle		FCT_;
IlModeHandle		ILMODE_;
VihhHandle		VIHH_;

FctReadPinHandle	rph;
DctReadPinHandle	drph;
DclpHandle		dclp;

//--------------------------Variable Define--------------------------
int i;

int IO_number=10;  //dosoku
//int IO_number=160; //tansoku

char PIN_number[512][6]={

"P1",	"P2",	"P3",	"P4",	"P5",	"P6",	"P7",	"P8",	"P9",	"P10",	"P11",	"P12",	"P13",	"P14",	"P15",	"P16",	"P17",	"P18",	"",	"",	"",	"",	"",	"",	"PD25",	"PD26",	"PD27",	"PD28",	"PD29",	"PD30",	"",	"",
"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",
"P65",	"P66",	"P67",	"P68",	"P69",	"P70",	"P71",	"P72",	"P73",	"P74",	"P75",	"P76",	"P77",	"P78",	"P79",	"P80",	"P81",	"P82",	"",	"",	"",	"",	"",	"",	"PD89",	"PD90",	"PD91",	"PD92",	"PD93",	"PD94",	"",	"",
"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",
"P129",	"P130",	"P131",	"P132",	"P133",	"P134",	"P135",	"P136",	"P137",	"P138",	"P139",	"P140",	"P141",	"P142",	"P143",	"P144",	"P145",	"P146",	"",	"",	"",	"",	"",	"",	"PD153","PD154","PD155","PD156","PD157","PD158","",	"",
"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",
"P193",	"P194",	"P195",	"P196",	"P197",	"P198",	"P199",	"P200",	"P201",	"P202",	"P203",	"P204",	"P205",	"P206",	"P207",	"P208",	"P209",	"P210",	"",	"",	"",	"",	"",	"",	"PD217","PD218","PD219","PD220","PD221","PD222","",	"",
"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",
"P257",	"P258",	"P259",	"P260",	"P261",	"P262",	"P263",	"P264",	"P265",	"P266",	"P267",	"P268",	"P269",	"P270",	"P271",	"P272",	"P273",	"P274",	"",	"",	"",	"",	"",	"",	"PD281","PD282","PD283","PD284","PD285","PD286","",	"",
"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",
"P321",	"P322",	"P323",	"P324",	"P325",	"P326",	"P327",	"P328",	"P329",	"P330",	"P331",	"P332",	"P333",	"P334",	"P335",	"P336",	"P337",	"P338",	"",	"",	"",	"",	"",	"",	"PD345","PD346","PD347","PD348","PD349","PD350","",	"",
"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",
"P385",	"P386",	"P387",	"P388",	"P389",	"P390",	"P391",	"P392",	"P393",	"P394",	"P395",	"P396",	"P397",	"P398",	"P399",	"P400",	"P401",	"P402",	"",	"",	"",	"",	"",	"",	"PD409","PD410","PD411","PD412","PD413","PD414","",	"",
"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",
"P449",	"P450",	"P451",	"P452",	"P453",	"P454",	"P455",	"P456",	"P457",	"P458",	"P459",	"P460",	"P461",	"P462",	"P463",	"P464",	"P465",	"P466",	"",	"",	"",	"",	"",	"",	"PD473","PD474","PD475","PD476","PD477","PD478","",	"",
"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",	"",

#if  0
"P1",	"P2",	"P3",	"P4",	"P5",	"P6",	"P7",	"P8",	"P9",	"P10",	"P11",	"P12",	"P13",	"P14",	"P15",	"P16",	"P17",	"P18",	"",	"",	"",	"",	"",	"",	"PD25",	"PD26",	"PD27",	"PD28",	"PD29",	"PD30",	"",	"",
"P33",	"P34",	"P35",	"P36",	"P37",	"P38",	"P39",	"P40",	"P41",	"P42",	"P43",	"P44",	"P45",	"P46",	"P47",	"P48",	"P49",	"P50",	"",	"",	"",	"",	"",	"",	"PD57",	"PD58",	"PD59",	"PD60",	"PD61",	"PD62",	"",	"",
"P65",	"P66",	"P67",	"P68",	"P69",	"P70",	"P71",	"P72",	"P73",	"P74",	"P75",	"P76",	"P77",	"P78",	"P79",	"P80",	"P81",	"P82",	"",	"",	"",	"",	"",	"",	"PD89",	"PD90",	"PD91",	"PD92",	"PD93",	"PD94",	"",	"",
"P97",	"P98",	"P99",	"P100",	"P101",	"P102",	"P103",	"P104",	"P105",	"P106",	"P107",	"P108",	"P109",	"P110",	"P111",	"P112",	"P113",	"P114",	"",	"",	"",	"",	"",	"",	"PD121","PD122","PD123","PD124","PD125","PD126","",	"",
"P129",	"P130",	"P131",	"P132",	"P133",	"P134",	"P135",	"P136",	"P137",	"P138",	"P139",	"P140",	"P141",	"P142",	"P143",	"P144",	"P145",	"P146",	"",	"",	"",	"",	"",	"",	"PD153","PD154","PD155","PD156","PD157","PD158","",	"",
"P161",	"P162",	"P163",	"P164",	"P165",	"P166",	"P167",	"P168",	"P169",	"P170",	"P171",	"P172",	"P173",	"P174",	"P175",	"P176",	"P177",	"P178",	"",	"",	"",	"",	"",	"",	"PD185","PD186","PD187","PD188","PD189","PD190","",	"",
"P193",	"P194",	"P195",	"P196",	"P197",	"P198",	"P199",	"P200",	"P201",	"P202",	"P203",	"P204",	"P205",	"P206",	"P207",	"P208",	"P209",	"P210",	"",	"",	"",	"",	"",	"",	"PD217","PD218","PD219","PD220","PD221","PD222","",	"",
"P225",	"P226",	"P227",	"P228",	"P229",	"P230",	"P231",	"P232",	"P233",	"P234",	"P235",	"P236",	"P237",	"P238",	"P239",	"P240",	"P241",	"P242",	"",	"",	"",	"",	"",	"",	"PD249","PD250","PD251","PD252","PD253","PD254","",	"",
"P257",	"P258",	"P259",	"P260",	"P261",	"P262",	"P263",	"P264",	"P265",	"P266",	"P267",	"P268",	"P269",	"P270",	"P271",	"P272",	"P273",	"P274",	"",	"",	"",	"",	"",	"",	"PD281","PD282","PD283","PD284","PD285","PD286","",	"",
"P289",	"P290",	"P291",	"P292",	"P293",	"P294",	"P295",	"P296",	"P297",	"P298",	"P299",	"P300",	"P301",	"P302",	"P303",	"P304",	"P305",	"P306",	"",	"",	"",	"",	"",	"",	"PD313","PD314","PD315","PD316","PD317","PD318","",	"",
"P321",	"P322",	"P323",	"P324",	"P325",	"P326",	"P327",	"P328",	"P329",	"P330",	"P331",	"P332",	"P333",	"P334",	"P335",	"P336",	"P337",	"P338",	"",	"",	"",	"",	"",	"",	"PD345","PD346","PD347","PD348","PD349","PD350","",	"",
"P353",	"P354",	"P355",	"P356",	"P357",	"P358",	"P359",	"P360",	"P361",	"P362",	"P363",	"P364",	"P365",	"P366",	"P367",	"P368",	"P369",	"P370",	"",	"",	"",	"",	"",	"",	"PD377","PD378","PD379","PD380","PD381","PD382","",	"",
"P385",	"P386",	"P387",	"P388",	"P389",	"P390",	"P391",	"P392",	"P393",	"P394",	"P395",	"P396",	"P397",	"P398",	"P399",	"P400",	"P401",	"P402",	"",	"",	"",	"",	"",	"",	"PD409","PD410","PD411","PD412","PD413","PD414","",	"",
"P417",	"P418",	"P419",	"P420",	"P421",	"P422",	"P423",	"P424",	"P425",	"P426",	"P427",	"P428",	"P429",	"P430",	"P431",	"P432",	"P433",	"P434",	"",	"",	"",	"",	"",	"",	"PD441","PD442","PD443","PD444","PD445","PD446","",	"",
"P449",	"P450",	"P451",	"P452",	"P453",	"P454",	"P455",	"P456",	"P457",	"P458",	"P459",	"P460",	"P461",	"P462",	"P463",	"P464",	"P465",	"P466",	"",	"",	"",	"",	"",	"",	"PD473","PD474","PD475","PD476","PD477","PD478","",	"",
"P481",	"P482",	"P483",	"P484",	"P485",	"P486",	"P487",	"P488",	"P489",	"P490",	"P491",	"P492",	"P493",	"P494",	"P495",	"P496",	"P497",	"P498",	"",	"",	"",	"",	"",	"",	"PD505","PD506","PD507","PD508","PD509","PD510","",	"",
#endif

};

char DUT_number[DUTNUM];

static void GetHandle();
static void DeleteHandle();
static void PinList();
static void PowerSeq();
static void drcp_init();
//int  diagpc_check();
//
static void TNO006(double hlimit, double llimit, int III, TEST_testitem *testarg);
static void TNO006b(double hlimit, double llimit, TEST_testitem *testarg);

static void STRBSCAN1(TEST_testitem *testarg, RadioButton wave, int strbcnt, int exp1, int exp2, int exp3, int exp4, int exp5, int exp6);
static void STRBSCAN2(TEST_testitem *testarg, RadioButton wave, int strbcnt, int exp1, int exp2, int exp3, int exp4, int exp5, int exp6);
static void STRBSCAN4(TEST_testitem *testarg, int group);

static void out_check_1dshmoo(char *PDR, char *PCP, DSlider dr_vi, DSlider cp_vt, DSlider sta, DSlider stp, DSlider step, DSlider *cp_vo, int exphl);

static void GetHandle()
{
  int phase = 0;

  for (phase = 1; phase < 10; phase++)
          VS_[phase] = UTL_GetVsHandle();

  for (phase = 1; phase < 10; phase++)
          IN_[phase] = UTL_GetViHandle();

  for (phase = 1; phase < 10; phase++)
          OUT_[phase] = UTL_GetVoHandle();

  for (phase = 1; phase < 10; phase++)
          VT_[phase] = UTL_GetVtHandle();

  for (phase = 1; phase < 10; phase++)
          IL_[phase] = UTL_GetIlHandle();

  TG_       = UTL_GetTgHandle();
  REG_      = UTL_GetRegHandle();

  P1_       = UTL_GetPinHandle();
  PD25_     = UTL_GetPinHandle();

  IOPIN_    = UTL_GetPinHandle();
  HCDRPIN_  = UTL_GetPinHandle();
  ALLPIN_   = UTL_GetPinHandle();

  CTRL_     = UTL_GetPowerCtrlHandle();
  SEQ_      = UTL_GetPowerSeqHandle();
  ISVM_     = UTL_GetDcHandle();
  VSIM_     = UTL_GetDcHandle();
  VSVM_     = UTL_GetDcHandle();
  SETTLING_ = UTL_GetSettlingTimeHandle();
  DCT_      = UTL_GetDctHandle();
  DCT2_     = UTL_GetDctHandle();
  FCT_      = UTL_GetFctHandle();
  ILMODE_   = UTL_GetIlModeHandle(); 
  VIHH_     = UTL_GetVihhHandle();

  rph       = UTL_GetFctReadPinHandle();
  drph      = UTL_GetDctReadPinHandle();
  dclp      = UTL_GetDclpHandle();
}

static void DeleteHandle(){
  int phase = 0;

  for (phase = 1; phase < 10; phase++)
          UTL_DeleteHandle(VS_[phase]);

  for (phase = 1; phase < 10; phase++)
          UTL_DeleteHandle(IN_[phase]);

  for (phase = 1; phase < 10; phase++)
          UTL_DeleteHandle(OUT_[phase]);

  for (phase = 1; phase < 10; phase++)
          UTL_DeleteHandle(VT_[phase]);

  for (phase = 1; phase < 10; phase++)
          UTL_DeleteHandle(IL_[phase]);

  UTL_DeleteHandle(TG_);
  UTL_DeleteHandle(REG_);

  UTL_DeleteHandle(P1_);
  UTL_DeleteHandle(PD25_);

  UTL_DeleteHandle(IOPIN_);
  UTL_DeleteHandle(HCDRPIN_);
  UTL_DeleteHandle(ALLPIN_);

  UTL_DeleteHandle(CTRL_);
  UTL_DeleteHandle(SEQ_);
  UTL_DeleteHandle(ISVM_);
  UTL_DeleteHandle(VSIM_);
  UTL_DeleteHandle(VSVM_);
  UTL_DeleteHandle(SETTLING_);
  UTL_DeleteHandle(DCT_);
  UTL_DeleteHandle(DCT2_);
  UTL_DeleteHandle(FCT_);
  UTL_DeleteHandle(ILMODE_);
  UTL_DeleteHandle(VIHH_);

  UTL_DeleteHandle(rph);
  UTL_DeleteHandle(drph);
  UTL_DeleteHandle(dclp);
}

static void PinList(){
   int III=0;

/*----------------VS Define------------------------*/


/*------------Outputpin Define--------------------*/

 if(IO_number==160){
   for(III=1;III<=512;III++) {
//	printf("III=%d PIN_number[%d]=%s\n",III-1,III-1,PIN_number[III-1]); fflush(stdout);
	UTL_CreatePinList(PIN_number[III-1]);
	UTL_SetPinType(PIN_number[III-1],UT_PINTYPE_PIN);
	UTL_AddPinNumber(PIN_number[III-1],III);

	if(III%64==18) III=III+46;
   }
}

 if(IO_number==10){
   for(III=1;III<=8;III++) {
//	printf("III=%d PIN_number[%d]=%s\n",III-1,III-1,PIN_number[III-1]); fflush(stdout);
	UTL_CreatePinList(PIN_number[III-1]);
	UTL_SetPinType(PIN_number[III-1],UT_PINTYPE_PIN);
	UTL_AddPinNumber(PIN_number[III-1],III);
   }
   
	UTL_CreatePinList(PIN_number[16]);
	UTL_SetPinType(PIN_number[16],UT_PINTYPE_PIN);
	UTL_AddPinNumber(PIN_number[16],17);
 }

/*----------------HCDRpin  Define-----------------*/
 if(IO_number==160){
   for(III=25;III<=512;III++) {
//	printf("III=%d PIN_number[%d]=%s\n",III-1,III-1,PIN_number[III-1]); fflush(stdout);
	UTL_CreatePinList(PIN_number[III-1]);
	UTL_SetPinType(PIN_number[III-1],UT_PINTYPE_PIN);
	UTL_AddPinNumber(PIN_number[III-1],III);

	if(III%64==30) III=III+58;
   }
}


 if(IO_number==10){
   for(III=25;III<=27;III++) {
//	printf("III=%d PIN_number[%d]=%s\n",III-1,III-1,PIN_number[III-1]); fflush(stdout);
	UTL_CreatePinList(PIN_number[III-1]);
	UTL_SetPinType(PIN_number[III-1],UT_PINTYPE_PIN);
	UTL_AddPinNumber(PIN_number[III-1],III);
   }
 }


/*------------Appendpin Define--------------------*/

 UTL_CreatePinList("IOPIN");
 UTL_SetPinType("IOPIN",UT_PINTYPE_PIN);
 if(IO_number==160){
   for(III=1;III<=512;III++) {
	UTL_AddPinNumber("IOPIN",III);
	if(III%64==18) III=III+46;
   }
 }
 if(IO_number==10){
    for(III=1;III<=18;III++){
	   UTL_AddPinNumber("IOPIN",III);
    }
 }


 UTL_CreatePinList("HCDRPIN");
 UTL_SetPinType("HCDRPIN",UT_PINTYPE_PIN);
 
 if(IO_number==160){
   for(III=25;III<=512;III++) {
	UTL_AddPinNumber("HCDRPIN",III);
	if(III%64==30) III=III+58;
   }
 }
  if(IO_number==10){
    for(III=25;III<=30;III++){
	   UTL_AddPinNumber("HCDRPIN",III);
    }
  }

	UTL_CreatePinList("ALLPIN");
	UTL_SetPinType("ALLPIN",UT_PINTYPE_PIN);
	UTL_AppendPinList("ALLPIN","IOPIN");
	UTL_AppendPinList("ALLPIN","HCDRPIN");
}

static void PowerSeq(){
	UTL_AddPowerSeqVsAll(SEQ_,1);
	UTL_AddPowerSeqViAll(SEQ_,2);
	UTL_AddPowerSeqOthers(SEQ_,3);
	UTL_SetPowerSeqWaitTime(SEQ_,1,3e-3);
	UTL_SetPowerSeqWaitTime(SEQ_,2,3e-3);
	UTL_SetPowerSeqWaitTime(SEQ_,3,3e-3);
	UTL_SendPowerSeq(SEQ_);

        // SETTLING TIME=10MS,10MS
        UTL_SetSettlingTime(SETTLING_,10.0e-3);
	UTL_SetSettlingTimeAfterRof(SETTLING_,10.0e-3);
        UTL_SendSettlingTime(SETTLING_);
}

static void drcp_init()
{
//    int flg = diagpc_check();
//    if(flg==1) goto AA;

    //printf("PROGRAM START!!\n"); fflush(stdout);
    GetHandle();
    PinList();   
    PowerSeq();

    i = 1;
    sprintf(DUT_number,"DUT%d",i);

    return;
}

void TNO001(TEST_testitem *testarg){
    drcp_init();
    //printf("\nTEST  001 FIXH LEVEL CHECK"); fflush(stdout);
    int III=0;

    // IN1=2.0V,1.0V
    UTL_SetViHigh              (IN_[1], 2.0);
    UTL_SetViLow               (IN_[1], 1.0);
    UTL_SendVi                 (IN_[1], 1);

    // ALLPIN=OPEN
    UTL_SetPinOpen             (ALLPIN_, UT_ON);
    UTL_SendPin                (ALLPIN_, "ALLPIN");

    // ISVM=MVM,M(20V)
    UTL_SetDcMode              (ISVM_,  UT_DCT_MVM);
    UTL_SetDcMrange            (ISVM_, 7, 0);

    // LIMIT DC=2.04V,1.96V
    double HLIMIT=2.04;
    double LLIMIT=1.96;
    UTL_SetDcLimitHigh         (ISVM_, HLIMIT, UT_ON);
    UTL_SetDcLimitLow          (ISVM_, LLIMIT, UT_ON);
    UTL_SendDc                 (ISVM_, 1);

    // TIME1=3MS:VS
    // TIME2=3MS:IN
    // TIME3=3MS:OTHERS
    // SETTLING TIME=10MS,10MS
    PowerSeq();

  if(IO_number==160){
        printf(" (tansoku)\n"); fflush(stdout);
    	printf("---------------------------------------------------------------------\n"); fflush(stdout);
    	printf("GO/NOGO    DATA     UPPER     LOWER      PIN       DUT   \n"); fflush(stdout);
    	printf("---------------------------------------------------------------------\n"); fflush(stdout);
     for(III=1;III<=512;III++) {
        // PD1=IN1,FIXH,DC
        UTL_SetPinOpen             (IOPIN_, UT_OFF);
        UTL_SetPinViNumber         (IOPIN_, 1);
        UTL_SetPinDrWaveform       (IOPIN_, UT_WAV_FIXH);
        UTL_SetPinInit             (IOPIN_, UT_PIN_DEFAULT);
        UTL_SendPin                (IOPIN_, PIN_number[III-1]);

        // MEAS DC
        UTL_SetDctPinList          (DCT_, PIN_number[III-1]);
        UTL_SetDctRelayMode        (DCT_, UT_DCT_SWAP);		//alpha2
        UTL_SetDctPinVi            (DCT_, UT_ON);		//alpha2
        UTL_SetDctPinHvDr          (DCT_, UT_OFF);		//alpha2
        UTL_MeasDct                (DCT_);
       TNO006(HLIMIT,LLIMIT,III,testarg);

        // PD1=OPEN
        UTL_SetPinOpen             (IOPIN_, UT_ON);
        UTL_SendPin                (IOPIN_, PIN_number[III-1]);
    	
	if(III%64==18) III=III+46;	
	}
  }

  if(IO_number==10){
        printf(" (dosoku)\n"); fflush(stdout);
        // P1=IN1,FIXH,DC
        UTL_SetPinOpen             (P1_, UT_OFF);
        UTL_SetPinViNumber         (P1_, 1);
        UTL_SetPinDrWaveform       (P1_, UT_WAV_FIXH);
        UTL_SetPinInit             (P1_, UT_PIN_DEFAULT);
        UTL_SendPin                (P1_, "IOPIN");

        // MEAS DC
        UTL_SetDctPinList          (DCT_, "IOPIN");
        UTL_SetDctRelayMode        (DCT_, UT_DCT_SWAP);		//alpha2
        UTL_SetDctPinVi            (DCT_, UT_ON);		//alpha2
        UTL_SetDctPinHvDr          (DCT_, UT_OFF);		//alpha2
        UTL_MeasDct                (DCT_);
        TNO006b(HLIMIT,LLIMIT,testarg);

        // ALLPIN=OPEN
        UTL_SetPinOpen             (P1_, UT_ON);
        UTL_SendPin                (P1_, "ALLPIN");
    }
    DeleteHandle();
}

void TNO002(TEST_testitem *testarg){
    drcp_init();
    //printf("\nTEST  002 FIXL LEVEL CHECK"); fflush(stdout);
    int III=0;

    // IN1=2.0V,1.0V
    UTL_SetViHigh              (IN_[1], 2.0);
    UTL_SetViLow               (IN_[1], 1.0);
    UTL_SendVi                 (IN_[1], 1);

    // ALLPIN=OPEN
    UTL_SetPinOpen             (ALLPIN_, UT_ON);
    UTL_SendPin                (ALLPIN_, "ALLPIN");

    // ISVM=MVM,M(10V)
    UTL_SetDcMode              (ISVM_,  UT_DCT_MVM);
    UTL_SetDcMrange            (ISVM_, 7, 0);

    // LIMIT DC=1.04V,0.96V
    double HLIMIT=1.04;
    double LLIMIT=0.96;
    UTL_SetDcLimitHigh         (ISVM_, HLIMIT, UT_ON);
    UTL_SetDcLimitLow          (ISVM_, LLIMIT, UT_ON);
    UTL_SendDc                 (ISVM_, 1);

    // TIME1=3MS:VS
    // TIME2=3MS:IN
    // TIME3=3MS:OTHERS
    // SETTLING TIME=10MS,10MS
    PowerSeq();

  if(IO_number==160){
        printf(" (tansoku)\n"); fflush(stdout);
    	printf("---------------------------------------------------------------------\n"); fflush(stdout);
    	printf("GO/NOGO    DATA     UPPER     LOWER      PIN       DUT   \n"); fflush(stdout);
    	printf("---------------------------------------------------------------------\n"); fflush(stdout);
     for(III=1;III<=512;III++) {
        // PD1=IN1,FIXH,DC
        UTL_SetPinOpen             (IOPIN_, UT_OFF);
        UTL_SetPinViNumber         (IOPIN_, 1);
        UTL_SetPinDrWaveform       (IOPIN_, UT_WAV_FIXL);
        UTL_SetPinInit             (IOPIN_, UT_PIN_DEFAULT);
        UTL_SendPin                (IOPIN_, PIN_number[III-1]);

        // MEAS DC
        UTL_SetDctPinList          (DCT_, PIN_number[III-1]);
        UTL_SetDctRelayMode        (DCT_, UT_DCT_SWAP);		//alpha2
        UTL_SetDctPinVi            (DCT_, UT_ON);		//alpha2
        UTL_SetDctPinHvDr          (DCT_, UT_OFF);		//alpha2
        UTL_MeasDct                (DCT_);
       TNO006(HLIMIT,LLIMIT,III,testarg);

        // PD1=OPEN
        UTL_SetPinOpen             (IOPIN_, UT_ON);
        UTL_SendPin                (IOPIN_, PIN_number[III-1]);
    	
	if(III%64==18) III=III+46;	
	}
  }

  if(IO_number==10){
        printf(" (dosoku)\n"); fflush(stdout);
        // P1=IN1,FIXL,DC
        UTL_SetPinOpen             (P1_, UT_OFF);
        UTL_SetPinViNumber         (P1_, 1);
        UTL_SetPinDrWaveform       (P1_, UT_WAV_FIXL);
        UTL_SetPinInit             (P1_, UT_PIN_DEFAULT);
        UTL_SendPin                (P1_, "IOPIN");

        // MEAS DC
        UTL_SetDctPinList          (DCT_, "IOPIN");
        UTL_SetDctRelayMode        (DCT_, UT_DCT_SWAP);		//alpha2
        UTL_SetDctPinVi            (DCT_, UT_ON);		//alpha2
        UTL_MeasDct                (DCT_);
        TNO006b(HLIMIT,LLIMIT,testarg);

        // ALLPIN=OPEN
        UTL_SetPinOpen             (P1_, UT_ON);
        UTL_SendPin                (P1_, "ALLPIN");
    }
    DeleteHandle();
}

void TNO003(TEST_testitem *testarg){
    drcp_init();
    //printf("\nTEST  003 OPEN CHECK"); fflush(stdout);
    int III=0;

    // IN1=2.0V,1.0V
    UTL_SetViHigh              (IN_[1], 2.0);
    UTL_SetViLow               (IN_[1], 1.0);
    UTL_SendVi                 (IN_[1], 1);

    // IOPIN=IN1,FIXH
    UTL_SetPinOpen             (IOPIN_, UT_OFF);
    UTL_SetPinViNumber         (IOPIN_, 1);
    UTL_SetPinDrWaveform       (IOPIN_, UT_WAV_FIXH);
    UTL_SetPinInit             (IOPIN_, UT_PIN_DEFAULT);
    UTL_SendPin                (IOPIN_, "IOPIN");

    // INH2=7V,2V
    UTL_SetViHvDr              (IN_[2], UT_ON);
    UTL_SetViHigh              (IN_[2], 7);
    UTL_SetViLow               (IN_[2], 2);
    UTL_SendVi                 (IN_[2], 2);

    // HCDRPIN=IN1,FIXH
    UTL_SetPinOpen             (HCDRPIN_, UT_OFF);
    UTL_SetPinViNumber         (HCDRPIN_, 2);
    UTL_SetPinDrWaveform       (HCDRPIN_, UT_WAV_FIXH);
    UTL_SetPinInit             (HCDRPIN_, UT_PIN_DEFAULT);
    UTL_SetPinHvDr             (HCDRPIN_, UT_ON);
    UTL_SendPin                (HCDRPIN_, "HCDRPIN");
    
    // ISVM=-100UA,R(800UA),M(25V),0.6V,-0.6V
    UTL_SetDcMode              (ISVM_, UT_DCT_ISVM);
    UTL_SetDcSource            (ISVM_, -100e-6);
    UTL_SetDcSrange            (ISVM_, 800e-6, -800e-6);
    UTL_SetDcMrange            (ISVM_, 0, -7.0);
    UTL_SetDcPclamp            (ISVM_,  0.6);
    UTL_SetDcMclamp            (ISVM_, -0.6);
    // LIMIT DC=-0.59,-0.61V
    double HLIMIT=-0.5;
    double LLIMIT=-0.7;
    UTL_SetDcLimitHigh         (ISVM_, HLIMIT, UT_ON);
    UTL_SetDcLimitLow          (ISVM_, LLIMIT, UT_ON);
    UTL_SendDc                 (ISVM_, 1);

    // TIME1=3MS:VS
    // TIME2=3MS:IN
    // TIME3=3MS:OTHERS
    // SETTLING TIME=10MS,10MS
    PowerSeq();

  if(IO_number==160){
    printf(" (tansoku)\n"); fflush(stdout);
    printf("-----------------------------------------------------------------------\n"); fflush(stdout);
    printf("GO/NOGO    DATA      UPPER      LOWER      PIN       DUT   \n"); fflush(stdout);
    printf("-----------------------------------------------------------------------\n"); fflush(stdout);
    for(III=1;III<=512;III++) {
        // PD1=OPEN,DC
        UTL_SetPinOpen             (ALLPIN_, UT_ON);
        UTL_SendPin                (ALLPIN_, PIN_number[III-1]);

        // MEAS DC
        UTL_SetDctPinList          (DCT_, PIN_number[III-1]);
        UTL_MeasDct                (DCT_);
        TNO006(HLIMIT,LLIMIT,III,testarg);

        // PD1=OPEN
        UTL_SetPinOpen             (ALLPIN_, UT_ON);
        UTL_SendPin                (ALLPIN_, PIN_number[III-1]);

//	if(III%32==18) III=III+6;
//	else if(III%32==30) III=III+2;
	if(III%64==18) III=III+6;
	else if(III%64==30) III=III+34;
    }
  }

  if(IO_number==10){
        printf(" (dosoku)\n"); fflush(stdout);
        // ALLPIN=OPEN,DC
        UTL_SetPinOpen             (ALLPIN_, UT_ON);
        UTL_SendPin                (ALLPIN_, "ALLPIN");

        // MEAS DC (IO pin)
        UTL_SetDctPinList          (DCT_, "ALLPIN");
        UTL_MeasDct                (DCT_);
        TNO006b(HLIMIT,LLIMIT,testarg);

        // ALLPIN=OPEN
        UTL_SetPinOpen             (ALLPIN_, UT_ON);
        UTL_SendPin                (ALLPIN_, "ALLPIN");
    }
    DeleteHandle();
}

void TNO004(TEST_testitem *testarg){
    drcp_init();
    //printf("\nTEST  004 INH LEVEL CHECK"); fflush(stdout);
    int III=0;

    // INH2=15V,2V
    UTL_SetViHvDr              (IN_[2], UT_ON);
    UTL_SetViHigh              (IN_[2], 7);
    UTL_SetViLow               (IN_[2], 1);
    UTL_SendVi                 (IN_[2], 2);

    // ALLPIN=OPEN
    UTL_SetPinOpen             (ALLPIN_, UT_ON);
    UTL_SendPin                (ALLPIN_, "ALLPIN");

    // ISVM=MVM,M(20V)
    UTL_SetDcMode              (ISVM_,  UT_DCT_MVM);
    UTL_SetDcMrange            (ISVM_, 7, 0);

    // LIMIT DC=7.14V,6.86V(+/-2%)
    double HLIMIT=7.14;
    double LLIMIT=6.86;
    UTL_SetDcLimitHigh         (ISVM_, HLIMIT, UT_ON);
    UTL_SetDcLimitLow          (ISVM_, LLIMIT, UT_ON);
    UTL_SendDc                 (ISVM_, 1);

    // TIME1=3MS:VS
    // TIME2=3MS:IN
    // TIME3=3MS:OTHERS
    // SETTLING TIME=10MS,10MS
    PowerSeq();

  if(IO_number==160){
    printf(" (tansoku)\n"); fflush(stdout);
    printf("---------------------------------------------------------------------\n"); fflush(stdout);
    printf("GO/NOGO    DATA     UPPER     LOWER      PIN       DUT   \n"); fflush(stdout);
    printf("---------------------------------------------------------------------\n"); fflush(stdout); 

    for(III=25;III<=512;III++) {
        // PD1=INH2,FIXH,DC
        UTL_SetPinOpen             (PD25_, UT_OFF);
        UTL_SetPinViNumber         (PD25_, 2);
        UTL_SetPinDrWaveform       (PD25_, UT_WAV_FIXH);
        UTL_SetPinInit             (PD25_, UT_PIN_DEFAULT);
        UTL_SetPinHvDr             (PD25_, UT_ON);
        UTL_SendPin                (PD25_, PIN_number[III-1]);

        // MEAS DC
        UTL_SetDctPinList          (DCT_, PIN_number[III-1]);
        UTL_SetDctRelayMode        (DCT_, UT_DCT_SWAP);		//alpha2
        UTL_SetDctPinVi            (DCT_, UT_ON);		//alpha2
        UTL_SetDctPinHvDr          (DCT_, UT_ON);		//alpha2
        UTL_MeasDct                (DCT_);
        TNO006(HLIMIT,LLIMIT,III,testarg);

        // PD1=OPEN
        UTL_SetPinOpen             (PD25_, UT_ON);
        UTL_SendPin                (PD25_, PIN_number[III-1]);

	if(III%64==30) III=III+58;
    }
  }

  if(IO_number==10){
        printf(" (dosoku)\n"); fflush(stdout);
        // PD1=INH2,FIXH,DC
        UTL_SetPinOpen             (PD25_, UT_OFF);
        UTL_SetPinViNumber         (PD25_, 2);
        UTL_SetPinDrWaveform       (PD25_, UT_WAV_FIXH);
        UTL_SetPinInit             (PD25_, UT_PIN_DEFAULT);
        UTL_SetPinHvDr             (PD25_, UT_ON);
        UTL_SendPin                (PD25_, "HCDRPIN");

        // MEAS DC
        UTL_SetDctPinList          (DCT_, "HCDRPIN");
        UTL_SetDctRelayMode        (DCT_, UT_DCT_SWAP);		//alpha2
        UTL_SetDctPinVi            (DCT_, UT_ON);		//alpha2
        UTL_SetDctPinHvDr          (DCT_, UT_ON);		//alpha2
        UTL_MeasDct                (DCT_);
        TNO006b(HLIMIT,LLIMIT,testarg);

        // PD1=OPEN
        UTL_SetPinOpen             (PD25_, UT_ON);
        UTL_SendPin                (PD25_, "HCDRPIN");
    }
    DeleteHandle();
}


//tansoku
static void TNO006(double hlimit, double llimit, int III, TEST_testitem *testarg){
    drcp_init();
    UT_DUT  dut;
    UT_PIN  pin;
    DutCursor dutc;
    PinCursor pinc;
    DctReadPinHandle drph = UTL_GetDctReadPinHandle();
//    DctReadPinHandle drph;
    CheckButton over[4][2];
    DSlider data[4][2];
    int j=0;

    UTL_SetDctReadPinType(drph,UT_PINTYPE_PIN);
    UTL_SetDctReadPinMode(drph,UT_RES_OVERFLOW);
    dutc=UTL_GetDutCursor(UT_CDUT);

    dut=UTL_NextDut(dutc);
    UTL_SetDctReadPinDut(drph,dut);
    pinc=UTL_GetPinCursor(PIN_number[III-1]);
    pin=UTL_NextPin(pinc);
    UTL_SetDctReadPinNumber(drph,pin);
    over[0][0] = UTL_ReadDctPin(drph);
    data[0][0] = UTL_ReadDctPinData(drph);
    UTL_DeleteCursor(pinc);
    UTL_DeleteCursor(dutc);
	
    if(testarg->testno==120){
        if     (dut%2==0 && pin%2==0) {llimit=0.45; hlimit=0.55;}
        else if(dut%2==0 && pin%2==1) {llimit=0.95; hlimit=1.05;}
        else if(dut%2==1 && pin%2==0) {llimit=1.45; hlimit=1.55;}
        else if(dut%2==1 && pin%2==1) {llimit=1.95; hlimit=2.05;}
    }

    double Y=0.0;
    Y = data[0][0];
    UTL_ResetTestResult(1, testarg->testname, UT_RES_DC);
    if(Y<llimit){
         printf("L-FAIL    %3.3lfV",Y); fflush(stdout);
         UTL_SetTestResult(1, testarg->testname, UT_RES_DC);
    }
    else if(Y>hlimit){
         printf("U-FAIL    %3.3lfV",Y); fflush(stdout);
         UTL_SetTestResult(1, testarg->testname, UT_RES_DC);
    }
    else{
         printf("          %3.3lfV",Y); fflush(stdout);
    }
    printf("    %.3lfV    %.3lfV    PIN%-3d    DUT%-3d  @READ DCT\n",hlimit,llimit,pin,dut); fflush(stdout);
    return;
}

//dosoku
static void TNO006b(double hlimit, double llimit, TEST_testitem *testarg){
    drcp_init();
    double data[DUTNUM][32];
    double Y=0.0;
    DutCursor dutcur; 
    UT_DUT    dut = 0;
    PinCursor pincur;
    UT_PIN    pin = 0;
    DctReadPinHandle drph = UTL_GetDctReadPinHandle();

    UTL_SetDctReadPinType(drph,UT_PINTYPE_PIN);
    UTL_SetDctReadPinMode(drph,UT_RES_OVERFLOW);
    printf("---------------------------------------------------------------------\n"); fflush(stdout);
    printf("GO/NOGO    DATA     UPPER     LOWER      PIN       DUT   \n"); fflush(stdout);
    printf("---------------------------------------------------------------------\n"); fflush(stdout);

	dutcur = UTL_GetDutCursor(UT_MDUT);
	while((dut=UTL_NextDut(dutcur)) != UT_NOMORE){
            UTL_ResetTestResult(dut, testarg->testname, UT_RES_DC);
	    UTL_SetDctReadPinDut(drph,dut);

            if(testarg->testno==30) pincur = UTL_GetPinCursor("ALLPIN");
	    else if(testarg->testno==40) pincur = UTL_GetPinCursor("HCDRPIN");
            else pincur = UTL_GetPinCursor("IOPIN");
	    while((pin=UTL_NextPin(pincur)) != UT_NOMORE){
                UTL_SetDctReadPinNumber(drph,pin);

             	data[dut-1][pin-1] = UTL_ReadDctPinData(drph);
             	Y = data[dut-1][pin-1];

		if(testarg->testno==120){
    	    		if     (dut%2==0 && pin%2==0) {llimit=0.45; hlimit=0.55;}
    	    		else if(dut%2==0 && pin%2==1) {llimit=0.95; hlimit=1.05;}
    	    		else if(dut%2==1 && pin%2==0) {llimit=1.45; hlimit=1.55;}
    	    		else if(dut%2==1 && pin%2==1) {llimit=1.95; hlimit=2.05;}
		}

             	if(Y<llimit){
                	 printf("L-FAIL    %3.3lfV",Y); fflush(stdout);
                 	 UTL_SetTestResult(dut, testarg->testname, UT_RES_DC);
             	}else if(Y>hlimit){
                	 printf("U-FAIL    %3.3lfV",Y); fflush(stdout);
                 	 UTL_SetTestResult(dut, testarg->testname, UT_RES_DC);
                }else{
                  	 printf("          %3.3lfV",Y); fflush(stdout);
                }
	        printf("    %.3lfV    %.3lfV    PIN%-3d    DUT%-3d  @READ DCT\n",hlimit,llimit,pin,dut); fflush(stdout);
            }
            UTL_DeleteCursor(pincur);
        }
    	UTL_DeleteCursor(dutcur);
    return;
}


void TNO005(TEST_testitem *testarg){
    drcp_init();
    //printf("\nTEST  005 VT LEVEL CHECK"); fflush(stdout);
    int III=0;

    // OUT1=1.5V
    UTL_SetVoHigh              (OUT_[1], 1.5);
    UTL_SetVoLow               (OUT_[1], 1.0);
    UTL_SendVo                 (OUT_[1], 1);

    // VT1=1.5V
    UTL_SetVt                  (VT_[1], 1.5);
    UTL_SendVt                 (VT_[1], 1);

    // ALLPIN=OPEN
    UTL_SetPinOpen             (ALLPIN_, UT_ON);
    UTL_SendPin                (ALLPIN_, "ALLPIN");

    // ISVM=MVM,M(10V)
    UTL_SetDcMode              (ISVM_,  UT_DCT_MVM);
    UTL_SetDcMrange            (ISVM_, 7, 0);

    // LIMIT DC=1.53V,1.47V
    double HLIMIT=1.53;
    double LLIMIT=1.47;
    UTL_SetDcLimitHigh         (ISVM_, HLIMIT, UT_ON);
    UTL_SetDcLimitLow          (ISVM_, LLIMIT, UT_ON);
    UTL_SendDc                 (ISVM_, 1);

    // TIME1=3MS:VS
    // TIME2=3MS:IN
    // TIME3=3MS:OTHERS
    // SETTLING TIME=10MS,10MS
    PowerSeq();

  if(IO_number==160){
    printf(" (tansoku)\n"); fflush(stdout);
    printf("---------------------------------------------------------------------\n"); fflush(stdout);
    printf("GO/NOGO    DATA     UPPER     LOWER      PIN       DUT   \n"); fflush(stdout);
    printf("---------------------------------------------------------------------\n"); fflush(stdout);
    for(III=1;III<=512;III++) {
//        printf("%s START!!",PIN_number[III-1]); fflush(stdout);
    // P33=OUTL1,VT1,DC
    UTL_SetPinOpen             (P1_, UT_OFF);
    UTL_SetPinVoNumber         (P1_, 1);
    UTL_SetPinVtNumber         (P1_, 1);
    UTL_SetPinTerm             (P1_, UT_ON);
    UTL_SendPin                (P1_, PIN_number[III-1]);

    // MEAS DC
    UTL_SetDctPinList          (DCT_, PIN_number[III-1]);
    UTL_SetDctRelayMode        (DCT_, UT_DCT_SWAP);		//alpha2
    UTL_SetDctPinVo            (DCT_, UT_ON);		//alpha2
    UTL_SetDctPinHvDr          (DCT_, UT_OFF);		//alpha2
    UTL_SetDctPinTerm          (DCT_, UT_ON);
    UTL_MeasDct                (DCT_);
    TNO006(HLIMIT,LLIMIT,III,testarg);

    // P33=OPEN
    UTL_SetPinOpen             (P1_, UT_ON);
    UTL_SendPin                (P1_, PIN_number[III-1]);

    if(III%64==18) III=III+46;	
    }
  }

  if(IO_number==10){
        printf(" (dosoku)\n"); fflush(stdout);
//        printf("%s START!!",PIN_number[III-1]); fflush(stdout);
        // P33=OUTL1,VT1,DC
        UTL_SetPinOpen             (P1_, UT_OFF);
        UTL_SetPinVoNumber         (P1_, 1);
        UTL_SetPinVtNumber         (P1_, 1);
        UTL_SetPinTerm             (P1_, UT_ON);
        UTL_SendPin                (P1_, "IOPIN");

        // MEAS DC
        UTL_SetDctPinList          (DCT_, "IOPIN");
        UTL_SetDctRelayMode        (DCT_, UT_DCT_SWAP);		//alpha2
        UTL_SetDctPinVo            (DCT_, UT_ON);		//alpha2
        UTL_SetDctPinHvDr          (DCT_, UT_OFF);		//alpha2
        UTL_SetDctPinTerm          (DCT_, UT_ON);
        UTL_MeasDct                (DCT_);
        TNO006b(HLIMIT,LLIMIT,testarg);

        // PD1=OPEN
        UTL_SetPinOpen             (P1_, UT_ON);
        UTL_SendPin                (P1_, "IOPIN");
  }
  DeleteHandle();
}

void TNO007(TEST_testitem *testarg){
    drcp_init();
    //printf("\nTEST  007 READ FCT CHECK (dosoku)\n"); fflush(stdout);
    int III=0;
    int i=0, j=0;
    int LP=0;
    int rmode=0;
//    int BUF1[512][32][2]; //VOH-Scan[pin][dut][VO1/2]
//    int BUF2[512][32][2]; //VOL-Scan[pin][dut][VO1/2]
//ChildA-H
//    int BUF1[512][32][2];
//    int BUF2[512][32][2];

    int DATA[512][DUTNUM][4][3]={-1};
    int EXP[4][3] ={{1,0,1},{1,1,0},{0,0,0},{1,1,1}};
    RadioButton mode;

    //IN1=2V,1V
    UTL_SetViHigh              (IN_[1], 2.0);
    UTL_SetViLow               (IN_[1], 0.0);
    UTL_SendVi                 (IN_[1], 1);

    // VT
    UTL_SetVt                  (VT_[1], 1.0);
    UTL_SendVt                 (VT_[1], 1);

    // VO
    UTL_SetVoHigh              (OUT_[1], 1.5);
    UTL_SetVoLow               (OUT_[1], 0.5);
    UTL_SendVo                 (OUT_[1], 1);

    // RATE=100NS
    UTL_AddTgRate              (TG_, 1,  TCYC);
    UTL_AddTgBclk              (TG_, 1, 1, 0);
    UTL_AddTgCclk              (TG_, 1, 1, TCYC*1/2);
    UTL_AddTgStrb              (TG_, 1, 1, TCYC*5/4);
    UTL_AddTgStrb              (TG_, 1, 2, TCYC*7/4);
    UTL_SendTg                 (TG_);

    // ALLPIN=OPEN
    UTL_SetPinOpen             (ALLPIN_, UT_ON);
    UTL_SendPin                (ALLPIN_, "ALLPIN");

    // P33=OUTL1,VT1,STRB1,<D0>
    UTL_InitializePinHandle    (P1_);
    UTL_SetPinViNumber         (P1_, 1);
    UTL_SetPinInit             (P1_, UT_PIN_DEFAULT);
    UTL_SetPinDrClock          (P1_, UT_PIN_BCLK, 1);
    UTL_SetPinDrClock          (P1_, UT_PIN_CCLK, 1);
    UTL_SetPinDreClock         (P1_, 1);
    UTL_SetPinDreNumber        (P1_, 1);
    UTL_SetPinDreWaveform      (P1_, UT_DREWAV_NRZ);
    UTL_SetPinVoNumber         (P1_, 1);
    UTL_SetPinTerm             (P1_, UT_ON); //20211214
    UTL_SetPinIoCtrl           (P1_, UT_ON);
    UTL_AddPinStrbCpeNumber    (P1_, 1, 1);
    UTL_AddPinStrbCpeNumber    (P1_, 2, 1);
    UTL_AddPinExpStrbNumber    (P1_, 1, UT_PIN_EXP_FH);
    UTL_AddPinExpStrbNumber    (P1_, 2, UT_PIN_EXP_FH);
    UTL_AddPinPdsA             (P1_, UT_SIG_C(0), 1);
    UTL_AddPinPdsB             (P1_, UT_SIG_C(1), 1);
    UTL_SendPin                (P1_, "IOPIN");

    for(LP=1;LP<=4;LP++){
        if(LP==1) UTL_SetPinDrWaveform       (P1_, UT_WAV_RZO);
        if(LP==2) UTL_SetPinDrWaveform       (P1_, UT_WAV_IRZO);
        if(LP==3) UTL_SetPinDrWaveform       (P1_, UT_WAV_FIXH);
        if(LP==4) UTL_SetPinDrWaveform       (P1_, UT_WAV_FIXL);
        UTL_SendPin                (P1_, "IOPIN");
        // SEND MPAT PATT
        UTL_SetFctMpatName         (FCT_, "pat_ppat.mpa");
        UTL_SetFctFailInhibit      (FCT_, UT_OFF);
        UTL_SetFctStartPc          (FCT_, 0x100);
        UTL_MeasFct                (FCT_);

	for(rmode=1; rmode<=3; rmode++){
       	    if(rmode==1) mode=UT_RES_TOTAL_FAILED;
       	    if(rmode==2) mode=UT_RES_STRB1_FAILED;
       	    if(rmode==3) mode=UT_RES_STRB2_FAILED;
	    UTL_SetFctReadPinMode (rph, mode);

            DutCursor dutcur = UTL_GetDutCursor(UT_MDUT);
            UT_DUT    dut = 0;
            PinCursor pincur;
            UT_PIN    pin = 0;
            while((dut = UTL_NextDut (dutcur)) != UT_NOMORE){
                UTL_SetFctReadPinDut (rph, dut);
                pincur = UTL_GetPinCursor ("IOPIN");
                while((pin = UTL_NextPin (pincur)) != UT_NOMORE){
                    UTL_SetFctReadPinNumber (rph, pin);
                    DATA[pin-1][dut-1][LP-1][rmode-1]= UTL_ReadFctPin(rph);
                }
                UTL_DeleteCursor (pincur);
            }
            UTL_DeleteCursor (dutcur);
	}
    }

    int FLG=0;
    DutCursor dutcur = UTL_GetDutCursor(UT_MDUT);
    UT_DUT    dut = 0;
    PinCursor pincur;
    UT_PIN    pin = 0;
    while((dut = UTL_NextDut(dutcur)) != UT_NOMORE){
        UTL_ResetTestResult(dut, testarg->testname, UT_RES_FUNC);
        pincur = UTL_GetPinCursor ("IOPIN");
        while((pin = UTL_NextPin(pincur)) != UT_NOMORE){
            for(j=0;j<4;j++){
                for(i=0;i<3;i++){
                    if(DEBUG==1){printf("DUT%d P%d WAVE%d READMODE%d EXP=%d DATA=%d", dut, pin, j+1, i+1, EXP[j][i], DATA[pin-1][dut-1][j][i]);}
                    if(DATA[pin-1][dut-1][j][i]!=EXP[j][i]){
                        if(DEBUG==1){printf("  FAIL***\n"); fflush(stdout);}
                        UTL_SetTestResult(dut, testarg->testname, UT_RES_FUNC);
                    }
                    else{
                        if(DEBUG==1){printf("  ***PASS\n"); fflush(stdout);}
                    }
                }
            }
        }
        UTL_DeleteCursor (pincur);

        FLG = UTL_ReadTestResult(dut, testarg->testname, UT_RES_FUNC);
        if(FLG==UT_RES_PASSED) printf("DUT%d  ***PASS\n",dut);
        if(FLG==UT_RES_FAILED) printf("DUT%d  FAIL***\n",dut);
    }
    UTL_DeleteCursor (dutcur);
   
    DeleteHandle();
}

//#define SELF_DR_CP
static void out_check_1dshmoo(char *PDR, char *PCP, DSlider dr_vi, DSlider cp_vt, DSlider sta, DSlider stp, DSlider step, DSlider *cp_vo, int exphl){
  ViHandle vih = UTL_GetViHandle();
  if(dr_vi<0.0){ //FIXL
    UTL_SetViHigh              (vih, dr_vi+1.0);//dummy
    UTL_SetViLow               (vih, dr_vi);
  }
  else{ //FIXH
    UTL_SetViHigh              (vih, dr_vi);
    UTL_SetViLow               (vih, dr_vi-1.0);//dummy
  }
  UTL_SendVi                 (vih, 1);
  UTL_DeleteHandle(vih);

  VtHandle vth = UTL_GetVtHandle();
  UTL_SetVt                  (vth, cp_vt);
  UTL_SendVt                 (vth, 1);
  UTL_DeleteHandle(vth);

  double rate = 100e-9;
  TgHandle tgh = UTL_GetTgHandle();
  UTL_AddTgRate              (tgh, 1, rate);
  UTL_AddTgDreL              (tgh, 1, 1, 0.0);
  UTL_AddTgDreT              (tgh, 1, 1, 0.0);
  UTL_AddTgStrb              (tgh, 1, 1, rate*0.5);
  UTL_SendTg                 (tgh);
  UTL_DeleteHandle(tgh);

  PinHandle ph;
  ph = UTL_GetPinHandle();
  UTL_SetPinOpen             (ph, UT_ON);
  UTL_SendPin                (ph, "PINALL");
  UTL_DeleteHandle(ph);

#ifndef SELF_DR_CP
  ph = UTL_GetPinHandle();
  UTL_InitializePinHandle    (ph);
  UTL_SetPinViNumber         (ph, 1);
  if(dr_vi<0.0){ //FIXL
    UTL_SetPinDrWaveform       (ph, UT_WAV_FIXL);
  }
  else{ //FIXH
    UTL_SetPinDrWaveform       (ph, UT_WAV_FIXH);
  }
  UTL_SendPin                (ph, PDR);
  UTL_DeleteHandle(ph);
#endif

  ph = UTL_GetPinHandle();
  UTL_InitializePinHandle    (ph);
  UTL_SetPinVoNumber         (ph, 1);
  UTL_SetPinVtNumber         (ph, 1);
  UTL_SetPinTerm             (ph, UT_ON);
  UTL_SetPinDreNumber(ph, 2); //debug
  UTL_AddPinStrbCpeNumber    (ph, 1, 1);
  UTL_AddPinPdsA             (ph, UT_SIG_D(0), 1);
  UTL_AddPinPdsB             (ph, UT_SIG_D(0), 1);
#ifdef SELF_DR_CP
  UTL_SetPinViNumber         (ph, 1);
  if(dr_vi<0.0){ //FIXL
    UTL_SetPinDrWaveform       (ph, UT_WAV_FIXL);
  }
  else{ //FIXH
    UTL_SetPinDrWaveform       (ph, UT_WAV_FIXH);
  }
  UTL_SetPinIoCtrl           (ph, UT_ON);
  UTL_SetPinDreWaveform      (ph, UT_DREWAV_NRZ);
  UTL_SetPinDreClock         (ph, 1);
#endif
  UTL_SendPin                (ph, PCP);
  UTL_DeleteHandle(ph);

  RegHandle regh;
  regh = UTL_GetRegHandle();
  UTL_SetRegUs(regh, UT_REG_TPH, 1, 0xff*exphl);
  UTL_SendReg(regh);
  UTL_DeleteHandle(regh);

  FctHandle fcth = UTL_GetFctHandle();
  UTL_SetFctMpatName         (fcth, "pat_ppat.mpa");
  UTL_SetFctFailInhibit      (fcth, UT_OFF);
  UTL_SetFctNoClear          (fcth, UT_ON);
  UTL_SetFctStartPc          (fcth, 0x000);

  DutCursor dutcur;
  PinCursor pincur;
  UT_DUT    dut = 0;
  UT_PIN    pin = 0;

  rph = UTL_GetFctReadPinHandle();
  UTL_SetFctReadPinMode(rph, UT_RES_STRB1_FAILED);

  printf("\n%s->%s", PDR, PCP);
  char shmoo[2] = {'*', '.'};
  DSlider vo;
  CheckButton pf;
  int pfflag[1025] = {0};
  VoHandle voh = UTL_GetVoHandle();
  for(vo=sta; vo<stp; vo+=step){
    printf("\nVO=%.3fV\t", vo); fflush(stdout);
    UTL_SetVoHigh              (voh, vo);
    UTL_SetVoLow               (voh, vo);
    UTL_SendVo                 (voh, 1);

    UTL_MeasFct                (fcth);

    dutcur = UTL_GetDutCursor(UT_MDUT);
    while((dut=UTL_NextDut(dutcur))!=UT_NOMORE){
      UTL_SetFctReadPinDut(rph, dut);
      pincur = UTL_GetPinCursor(PCP);
      while((pin=UTL_NextPin(pincur))!=UT_NOMORE){
        UTL_SetFctReadPinNumber(rph, pin);
        pf = UTL_ReadFctPin(rph);
        if(pfflag[(dut-1)*512+pin]!=pf){
          if(exphl==1){ //VOH
            if(pfflag[(dut-1)*512+pin]<2){
              pfflag[(dut-1)*512+pin] = 2;
              cp_vo[(dut-1)*512+pin] = vo-step;
            }
          }
          else{ //VOL
            pfflag[(dut-1)*512+pin] = pf;
            cp_vo[(dut-1)*512+pin] = vo;
          }
        }
        printf("%c", shmoo[pf]); fflush(stdout);
      }
      printf(" ");
      UTL_DeleteCursor(pincur);
    }
    UTL_DeleteCursor(dutcur);
  }
  printf("\n");
  UTL_DeleteHandle(fcth);

  ph = UTL_GetPinHandle();
  UTL_SetPinOpen             (ph, UT_ON);
  UTL_SendPin                (ph, "PINALL");
  UTL_DeleteHandle(ph);

  return;
}

void out_check(TEST_testitem *testarg){
  int i, j;

  DSlider exp = (DRCPARG.dr_vi+DRCPARG.cp_vt)/2;
#ifdef SELF_DR_CP
  exp = DRCPARG.dr_vi;
#endif
  DSlider ulim = exp*(1.0+0.01)+40e-3; // (+/-)0.5%+20mV x2
  DSlider llim = exp*(1.0-0.01)-40e-3; // (+/-)0.5%+20mV x2
  DSlider step = 1e-3;
  DSlider sta = llim - step*5;
  DSlider stp = ulim + step*5;

  UTL_CreatePinList("PINA");
  UTL_CreatePinList("PINB");
  UTL_SetPinType("PINA" ,UT_PINTYPE_PIN);
  for(i=0; i<8; i++){
    for(j=0; j<18; j+=2){
      UTL_AddPinNumber("PINA", i*64+j+1);
      UTL_AddPinNumber("PINB", i*64+j+2);
    }
  }
  UTL_CreatePinList("PINALL");
  UTL_SetPinType("PINALL", UT_PINTYPE_PIN);
  UTL_AppendPinList("PINALL", "PINA");
  UTL_AppendPinList("PINALL", "PINB");

  DSlider cp_vo[1025] = {0.0};
  out_check_1dshmoo("PINA", "PINB", DRCPARG.dr_vi, DRCPARG.cp_vt, sta, stp, step, cp_vo, DRCPARG.exphl);
  out_check_1dshmoo("PINB", "PINA", DRCPARG.dr_vi, DRCPARG.cp_vt, sta, stp, step, cp_vo, DRCPARG.exphl);

  printf("\n");
#ifdef SELF_DR_CP
  printf("USE SELF_DR_CP\n");
#endif
  DutCursor dutcur;
  PinCursor pincur;
  UT_DUT    dut = 0;
  UT_PIN    pin = 0;
  printf("DR_VI=%fV CP_VT=%fV EXP=%fV LLIM=%f ULIM=%f EXPHL=%d\n", DRCPARG.dr_vi, DRCPARG.cp_vt, exp, llim, ulim, DRCPARG.exphl);
  testresult_pass4alldut(testarg->testname);
  dutcur = UTL_GetDutCursor(UT_MDUT);
  while((dut=UTL_NextDut(dutcur))!=UT_NOMORE){
    pincur = UTL_GetPinCursor ("PINALL");
    while((pin=UTL_NextPin(pincur))!=UT_NOMORE){
      printf("DUT%d P%03d %.3fV delta % .1f%%", dut, pin, cp_vo[(dut-1)*512+pin], (cp_vo[(dut-1)*512+pin]-exp)/exp*100); fflush(stdout);
      if(cp_vo[(dut-1)*512+pin]<llim || ulim<cp_vo[(dut-1)*512+pin]){
        UTL_SetTestResult(dut, testarg->testname, UT_RES_FUNC);
        printf("\t****FAIL\n");
      }
      else{
        printf("\tPASS\n");
      }
    }
    UTL_DeleteCursor(pincur);
  }
  UTL_DeleteCursor(dutcur);

  return;
}

void TNO008(TEST_testitem *testarg){
    drcp_init();
    //printf("\nTEST  008 OUT LEVEL SCAN (dosoku)\n"); fflush(stdout);
    int III=0;
    int i=0;
    int j=0;
    int LP=0;
    int BUF1[512][DUTNUM][2]; //VOH-Scan[pin][dut][VO1/2]
    int BUF2[512][DUTNUM][2]; //VOL-Scan[pin][dut][VO1/2]
//ChildA-H
//    int BUF1[512][32][2];
//    int BUF2[512][32][2];

    double VT1=1.0;

    //debug IN1=2V,1V
    UTL_SetViHigh              (IN_[1], 2.0);
    UTL_SetViLow               (IN_[1], 1.0);
    UTL_SendVi                 (IN_[1], 1);

    // VT1=1V
    UTL_SetVt                  (VT_[1], VT1);
    UTL_SendVt                 (VT_[1], 1);

    // RATE=100NS
    UTL_AddTgRate              (TG_, 1,  TCYC);
    UTL_AddTgStrb              (TG_, 1, 1, TCYC/2);
    UTL_SendTg                 (TG_);

    // ALLPIN=OPEN
    UTL_SetPinOpen             (ALLPIN_, UT_ON);
    UTL_SendPin                (ALLPIN_, "ALLPIN");

    // P33=OUTL1,VT1,STRB1,<D0>
    UTL_InitializePinHandle    (P1_);
    UTL_SetPinVoNumber         (P1_, 1);
    UTL_SetPinVtNumber         (P1_, 1);
    UTL_SetPinTerm             (P1_, UT_ON);
UTL_SetPinDreNumber(P1_, 2); //debug
    UTL_AddPinStrbCpeNumber    (P1_, 1, 1);
    UTL_AddPinPdsA             (P1_, UT_SIG_D(0), 1);
    UTL_AddPinPdsB             (P1_, UT_SIG_D(0), 1);
    UTL_SendPin                (P1_, "IOPIN");

    ////////////////////////////////////////////////////////////////////// High Fail/Low Pass
    printf("\nHigh Fail/Low Pass"); fflush(stdout);
    printf("\nPASS = 0, FAIL = 1");

#if 0
	int iii;
 	printf("\n------------");	for(iii=1;iii<=DUTNUM;iii++) {printf("----------",iii);}
 	printf("\n            ");	for(iii=1;iii<=DUTNUM;iii++) {printf("<DUT%03d>  ",iii);}
 	printf("\n            ");	for(iii=1;iii<=DUTNUM;iii++) {printf("        1 ",iii);}
 	printf("\n            ");	for(iii=1;iii<=DUTNUM;iii++) {printf("123456787 ",iii);}
 	printf("\n------------");	for(iii=1;iii<=DUTNUM;iii++) {printf("----------",iii);}
#endif

    for(LP=1;LP<15;LP++){
	// OUT1=2V,2V
        printf("\nVOH=%3.2fV   ",1.55-0.1*LP); fflush(stdout);
        UTL_SetVoHigh              (OUT_[1], 1.55-0.1*LP);
        UTL_SetVoLow               (OUT_[1], 1.0);
        UTL_SendVo                 (OUT_[1], 1);

        // SEND MPAT PATT
        UTL_SetFctMpatName         (FCT_, "pat_ppat.mpa");
        UTL_SetFctFailInhibit      (FCT_, UT_OFF);
        UTL_SetFctStartPc          (FCT_, 0x000);

        // MEAS MPAT
        UTL_MeasFct                (FCT_);

        // READ FUNC2 for STRB1 
        DutCursor dutcur = UTL_GetDutCursor(UT_MDUT);
        UT_DUT    dut = 0;
        PinCursor pincur;
        UT_PIN    pin = 0;
        rph = UTL_GetFctReadPinHandle();

        UTL_SetFctReadPinMode (rph, UT_RES_STRB1_FAILED );

        while((dut = UTL_NextDut (dutcur)) != UT_NOMORE){
            UTL_SetFctReadPinDut (rph, dut);
            pincur = UTL_GetPinCursor ("IOPIN");
            while((pin = UTL_NextPin (pincur)) != UT_NOMORE){
                UTL_SetFctReadPinNumber (rph, pin);
                if(LP==5) BUF1[pin-1][dut-1][0]=UTL_ReadFctPin(rph);
                if(LP==6) BUF1[pin-1][dut-1][1]=UTL_ReadFctPin(rph);
                printf("%1d", UTL_ReadFctPin (rph)); fflush(stdout);
            }
            printf(" ");
            UTL_DeleteCursor (pincur);
        }
        UTL_DeleteCursor (dutcur);
    }
    printf("\n");

    int FLG=0;
    DutCursor dutcur = UTL_GetDutCursor(UT_MDUT);
    UT_DUT    dut = 0;
    PinCursor pincur;
    UT_PIN    pin = 0;
    while((dut = UTL_NextDut(dutcur)) != UT_NOMORE){
        FLG = UTL_ReadTestResult(dut, testarg->testname, UT_RES_FUNC);
        if(FLG!=UT_RES_FAILED){
          UTL_ResetTestResult(dut, testarg->testname, UT_RES_FUNC);
	}
        pincur = UTL_GetPinCursor ("IOPIN");
        while((pin = UTL_NextPin(pincur)) != UT_NOMORE){
                if(BUF1[pin-1][dut-1][0]==1 && BUF1[pin-1][dut-1][1]==0){
                    if(DEBUG==1){printf("DUT%d P%d  ***PASS\n",dut, pin); fflush(stdout);}
                }
                else{
                    if(DEBUG==1){printf("DUT%d P%d  FAIL**\n",dut, pin); fflush(stdout);}
                    UTL_SetTestResult(dut, testarg->testname, UT_RES_FUNC);
                }
        } 
        UTL_DeleteCursor (pincur);

        FLG = UTL_ReadTestResult(dut, testarg->testname, UT_RES_FUNC);
        if(FLG==UT_RES_PASSED) printf("DUT%d  ***PASS\n",dut);
        if(FLG==UT_RES_FAILED) printf("DUT%d  FAIL**\n",dut);
    }
    UTL_DeleteCursor (dutcur);

/////////////////////////////////////////////////////////////////////////// High Pass/Low Fail
    // P33=OUTL1,VT1,STRB1,<D0>
    UTL_InitializePinHandle    (P1_);
    UTL_SetPinVoNumber         (P1_, 1);
    UTL_SetPinVtNumber         (P1_, 1);
    UTL_SetPinTerm             (P1_, UT_ON);
    UTL_AddPinStrbCpeNumber    (P1_, 1, 1);
    UTL_AddPinPdsA             (P1_, UT_SIG_D(0), 1);
    UTL_AddPinPdsB             (P1_, UT_SIG_D(0), 1);
    UTL_SendPin                (P1_, "IOPIN");

    printf("\nHigh Pass/Low Fail"); fflush(stdout);
    printf("\nPASS = 0, FAIL = 1");

#if 0
 	printf("\n------------");	for(iii=1;iii<=DUTNUM;iii++) {printf("----------",iii);}
	printf("\n            ");	for(iii=1;iii<=DUTNUM;iii++) {printf("<DUT%03d>  ",iii);}
 	printf("\n            ");	for(iii=1;iii<=DUTNUM;iii++) {printf("        1 ",iii);}
 	printf("\n            ");	for(iii=1;iii<=DUTNUM;iii++) {printf("123456787 ",iii);}
 	printf("\n------------");	for(iii=1;iii<=DUTNUM;iii++) {printf("----------",iii);}
#endif

    for(LP=1;LP<15;LP++){
        // OUT1=3V,2V
        printf("\nVOL=%3.2fV   ",1.55-0.1*LP); fflush(stdout);
        UTL_SetVoHigh              (OUT_[1], 1.0);
        UTL_SetVoLow               (OUT_[1], 1.55-0.1*LP);
        UTL_SendVo                 (OUT_[1], 1);

        // SEND MPAT PATT
        UTL_SetFctMpatName         (FCT_, "pat_ppat.mpa");
        UTL_SetFctFailInhibit      (FCT_, UT_OFF);
        UTL_SetFctStartPc          (FCT_, 0x020);
        // MEAS MPAT
        UTL_MeasFct                (FCT_);

        // READ FUNC2 for STRB1 
        DutCursor dutcur = UTL_GetDutCursor(UT_MDUT);
        UT_DUT    dut = 0;
        PinCursor pincur;
        UT_PIN    pin = 0;
        rph = UTL_GetFctReadPinHandle();

        UTL_SetFctReadPinMode (rph, UT_RES_STRB1_FAILED );
//        printf("P%d RESULTS = ",III);

        while((dut = UTL_NextDut (dutcur)) != UT_NOMORE){
            UTL_SetFctReadPinDut (rph, dut);
            pincur = UTL_GetPinCursor ("IOPIN");
            while((pin = UTL_NextPin (pincur)) != UT_NOMORE){
                UTL_SetFctReadPinNumber (rph, pin);
                if(LP==5) BUF2[pin-1][dut-1][0]=UTL_ReadFctPin(rph);
                if(LP==6) BUF2[pin-1][dut-1][1]=UTL_ReadFctPin(rph);
                printf("%1d", UTL_ReadFctPin (rph)); fflush(stdout);
            }
            printf(" "); fflush(stdout);
            UTL_DeleteCursor (pincur);
        }
        UTL_DeleteCursor (dutcur);
    }
    printf("\n");fflush(stdout);

    FLG=0;
    dutcur = UTL_GetDutCursor(UT_MDUT);
    dut = 0;
    pin = 0;
    while((dut = UTL_NextDut(dutcur)) != UT_NOMORE){
        FLG = UTL_ReadTestResult(dut, testarg->testname, UT_RES_FUNC);
        if(FLG!=UT_RES_FAILED){
          UTL_ResetTestResult(dut, testarg->testname, UT_RES_FUNC);
	}
        pincur = UTL_GetPinCursor ("IOPIN");
        while((pin = UTL_NextPin(pincur)) != UT_NOMORE){
                if(BUF2[pin-1][dut-1][0]==0 && BUF2[pin-1][dut-1][1]==1){
                    if(DEBUG==1){printf("DUT%d P%d  ***PASS\n",dut, pin); fflush(stdout);}
                }
                else{
                    if(DEBUG==1){printf("DUT%d P%d  FAIL**\n",dut, pin); fflush(stdout);}
                    UTL_SetTestResult(dut, testarg->testname, UT_RES_FUNC);
                }
        } 
        UTL_DeleteCursor (pincur);

        FLG = UTL_ReadTestResult(dut, testarg->testname, UT_RES_FUNC);
        if(FLG==UT_RES_PASSED) printf("DUT%d  ***PASS\n",dut);
        if(FLG==UT_RES_FAILED) printf("DUT%d  FAIL**\n",dut);
    }
    UTL_DeleteCursor (dutcur);

    // P33=OPEN
//    UTL_SetPinOpen             (P1_, UT_ON);	//20211214
//    UTL_SendPin                (P1_, "IOPIN");//20211214

    DeleteHandle();
}

static void STRBSCAN1(TEST_testitem *testarg, RadioButton wave, int strbcnt, int exp1, int exp2, int exp3, int exp4, int exp5, int exp6){


    int III=0;
    int LP=0;

    // IN1=3V,0V
    UTL_SetViHigh              (IN_[1], 2.0);
    UTL_SetViLow               (IN_[1], 0.0);
    UTL_SendVi                 (IN_[1], 1);

    // VT1=1.5V
    UTL_SetVt                  (VT_[1], 1.5);
    UTL_SendVt                 (VT_[1], 1);

    // OUT1=1.5V,1.5V
    UTL_SetVoHigh              (OUT_[1], 1.5);
    UTL_SetVoLow               (OUT_[1], 1.5);
    UTL_SendVo                 (OUT_[1], 1);

    UTL_AddTgRate              (TG_, 1,  LONG);
    UTL_AddTgAclk              (TG_, 1, 1, 0.2*LONG);
    UTL_AddTgBclk              (TG_, 1, 1, 0.4*LONG);
    UTL_AddTgCclk              (TG_, 1, 1, 0.6*LONG);
    UTL_AddTgDreL              (TG_, 1, 1, 0e-6);
    UTL_AddTgDreT              (TG_, 1, 1, 0e-6);
    UTL_SendTg                 (TG_);

    // ALLPIN=OPEN
    UTL_SetPinOpen             (ALLPIN_, UT_ON);
    UTL_SendPin                (ALLPIN_, "ALLPIN");

    int i,j;
    int DATA1[512][DUTNUM][6];
    int DATA2[512][DUTNUM][6];
    int EXP[6];
        EXP[0]=exp1; 
        EXP[1]=exp2; 
        EXP[2]=exp3; 
        EXP[3]=exp4; 
        EXP[4]=exp5; 
        EXP[5]=exp6; 
    double STEP=0.0;

    if(strbcnt==SINGLE_STRB){
        // P1=IN1,RZX,BCLK1,DRECLK1,DRENRZ,STRB1,OUT1,<C0,FH>
        UTL_InitializePinHandle    (P1_);
        UTL_SetPinViNumber         (P1_, 1);
        UTL_SetPinDrWaveform       (P1_, wave);
        UTL_SetPinInit             (P1_, UT_PIN_DEFAULT);
        UTL_SetPinDrClock          (P1_, UT_PIN_BCLK, 1);
        UTL_SetPinDrClock          (P1_, UT_PIN_CCLK, 1);
        UTL_SetPinDreClock         (P1_, 1);
        UTL_SetPinDreNumber        (P1_, 1);
        UTL_SetPinDreWaveform      (P1_, UT_DREWAV_NRZ);
        UTL_SetPinVoNumber         (P1_, 1);
    	UTL_SetPinTerm             (P1_, UT_ON); //20211214
    	UTL_SetPinIoCtrl           (P1_, UT_ON);
        UTL_AddPinStrbCpeNumber    (P1_, 1, 1);
        UTL_AddPinExpStrbNumber    (P1_, 1, UT_PIN_EXP_FH);
        UTL_AddPinPdsA             (P1_, UT_SIG_C(0), 1);
        UTL_AddPinPdsB             (P1_, UT_SIG_FH, 1);
        UTL_SendPin                (P1_, "IOPIN");
    }
    if(strbcnt==DOUBLE_STRB){
        // P1=IN1,RZX,BCLK1,DRECLK1,DRENRZ,IOC,STRB1,STRB2,OUT1,<C0,FH>
        UTL_InitializePinHandle    (P1_);
        UTL_SetPinViNumber         (P1_, 1);
        UTL_SetPinDrWaveform       (P1_, wave);
        UTL_SetPinInit             (P1_, UT_PIN_DEFAULT);
        UTL_SetPinDrClock          (P1_, UT_PIN_BCLK, 1);
        UTL_SetPinDrClock          (P1_, UT_PIN_CCLK, 1);
        UTL_SetPinDreClock         (P1_, 1);
        UTL_SetPinDreNumber        (P1_, 1);
        UTL_SetPinDreWaveform      (P1_, UT_DREWAV_NRZ);
        UTL_SetPinVoNumber         (P1_, 1);
    	UTL_SetPinTerm             (P1_, UT_ON); //20211214
    	UTL_SetPinIoCtrl           (P1_, UT_ON);
        UTL_AddPinStrbCpeNumber    (P1_, 1, 1);
        UTL_AddPinStrbCpeNumber    (P1_, 2, 1);
        UTL_AddPinExpStrbNumber    (P1_, 1, UT_PIN_EXP_FH);
        UTL_AddPinExpStrbNumber    (P1_, 2, UT_PIN_EXP_FH);
        UTL_AddPinPdsA             (P1_, UT_SIG_C(0), 1);
        UTL_AddPinPdsB             (P1_, UT_SIG_FH, 1);
        UTL_SendPin                (P1_, "IOPIN");
    }

    for(LP=1;LP<=6;LP++){

        if(LP==1) STEP=LONG*1/4;
        if(LP==2) STEP=LONG*2/4;
        if(LP==3) STEP=LONG*3/4;
        if(LP==4) STEP=LONG*5/4;
        if(LP==5) STEP=LONG*6/4;
        if(LP==6) STEP=LONG*7/4;


        UTL_AddTgStrb              (TG_, 1, 1, STEP);
        if(strbcnt==DOUBLE_STRB){
            UTL_AddTgStrb              (TG_, 1, 2, STEP);
        }
        UTL_SendTg                 (TG_);

        // SEND MPAT PATT
        UTL_SetFctMpatName         (FCT_, "pat_ppat.mpa");
        UTL_SetFctFailInhibit      (FCT_, UT_OFF);
        UTL_SetFctStartPc          (FCT_, 0x100);
        // MEAS MPAT
        UTL_MeasFct                (FCT_);

        // READ FUNC2 for STRB1 
        DutCursor dutcur = UTL_GetDutCursor(UT_MDUT);
        UT_DUT    dut = 0;
        PinCursor pincur;
        UT_PIN    pin = 0;
        rph = UTL_GetFctReadPinHandle();

        UTL_SetFctReadPinMode (rph, UT_RES_STRB1_FAILED );

        while((dut = UTL_NextDut (dutcur)) != UT_NOMORE){
            UTL_SetFctReadPinDut (rph, dut);
            pincur = UTL_GetPinCursor ("IOPIN");
            while((pin = UTL_NextPin (pincur)) != UT_NOMORE){
                UTL_SetFctReadPinNumber (rph, pin);
                DATA1[pin-1][dut-1][LP-1]= UTL_ReadFctPin(rph);
                if(DEBUG==1) printf("DATA[%d][%d][%d]=%d \n", pin-1,dut-1,LP-1,DATA1[pin-1][dut-1][LP-1]); fflush(stdout);
            }
            UTL_DeleteCursor (pincur);
        }
        UTL_DeleteCursor (dutcur);

        if(strbcnt==DOUBLE_STRB){
            // READ FUNC2 for STRB2
            dutcur = UTL_GetDutCursor(UT_MDUT);
            dut = 0;
            pin = 0;
            rph = UTL_GetFctReadPinHandle();

            UTL_SetFctReadPinMode (rph, UT_RES_STRB2_FAILED );

            while((dut = UTL_NextDut (dutcur)) != UT_NOMORE){
                UTL_SetFctReadPinDut (rph, dut);
                pincur = UTL_GetPinCursor ("IOPIN");
                while((pin = UTL_NextPin (pincur)) != UT_NOMORE){
                    UTL_SetFctReadPinNumber (rph, pin);
                    DATA2[pin-1][dut-1][LP-1]= UTL_ReadFctPin(rph);
                    if(DEBUG==1) printf("DATA[%d][%d][%d]=%d \n", pin-1,dut-1,LP-1,DATA2[pin-1][dut-1][LP-1]); fflush(stdout);
                }
                UTL_DeleteCursor (pincur);
            }
            UTL_DeleteCursor (dutcur);
        }
    }


    int FLG=0;
    DutCursor dutcur = UTL_GetDutCursor(UT_MDUT);
    UT_DUT    dut = 0;
    PinCursor pincur;
    UT_PIN    pin = 0;
    while((dut = UTL_NextDut(dutcur)) != UT_NOMORE){
        UTL_ResetTestResult(dut, testarg->testname, UT_RES_FUNC);
        pincur = UTL_GetPinCursor ("IOPIN");
        while((pin = UTL_NextPin(pincur)) != UT_NOMORE){
            for(j=0;j<6;j++){
                if(DATA1[pin-1][dut-1][j]!=EXP[j]){
                    if(DEBUG==1){printf("DUT%d P%d STRB1-%d  FAIL**\n",dut, pin,j+1); fflush(stdout);}
                    UTL_SetTestResult(dut, testarg->testname, UT_RES_FUNC);
                }
                else{
                    if(DEBUG==1){printf("DUT%d P%d STRB1-%d  ***PASS\n",dut, pin,j+1); fflush(stdout);}
                }
                if(strbcnt==DOUBLE_STRB){
                    if(DATA2[pin-1][dut-1][j]!=EXP[j]){
                        if(DEBUG==1){printf("DUT%d P%d STRB2-%d  FAIL**\n",dut, pin,j+1); fflush(stdout);}
                        UTL_SetTestResult(dut, testarg->testname, UT_RES_FUNC);
                    }
                    else{
                        if(DEBUG==1){printf("DUT%d P%d STRB2-%d  ***PASS\n",dut, pin,j+1); fflush(stdout);}
                    }
                }
            }
        } 
        UTL_DeleteCursor (pincur);

        FLG = UTL_ReadTestResult(dut, testarg->testname, UT_RES_FUNC);
        if(FLG==UT_RES_PASSED) printf("DUT%d  ***PASS\n",dut);
        if(FLG==UT_RES_FAILED) printf("DUT%d  FAIL**\n",dut);
    }
    UTL_DeleteCursor (dutcur);
}

static void STRBSCAN2(TEST_testitem *testarg, RadioButton wave, int strbcnt, int exp1, int exp2, int exp3, int exp4, int exp5, int exp6){
    int III=0;
    int LP=0;

    // IN1=3V,0V
    UTL_SetViHigh              (IN_[1], 2.0);
    UTL_SetViLow               (IN_[1], 0.0);
    UTL_SendVi                 (IN_[1], 1);

    // VT1=1.5V
    UTL_SetVt                  (VT_[1], 1.5);
    UTL_SendVt                 (VT_[1], 1);

    // OUT1=1.5V,1.5V
    UTL_SetVoHigh              (OUT_[1], 1.5);
    UTL_SetVoLow               (OUT_[1], 1.5);
    UTL_SendVo                 (OUT_[1], 1);

    UTL_AddTgRate              (TG_, 1,  LONG);
    UTL_AddTgBclk              (TG_, 1, 1, 0.4*LONG);
    UTL_AddTgCclk              (TG_, 1, 1, 0.6*LONG);
    UTL_AddTgDreL              (TG_, 1, 1, 0e-6);
    UTL_AddTgDreT              (TG_, 1, 1, 0e-6);
    UTL_SendTg                 (TG_);

    // IOPIN CONNECT
    UTL_SetPinOpen             (ALLPIN_, UT_OFF);
    UTL_SendPin                (ALLPIN_, "IOPIN");

    int i,j;
    int DATA1[512][DUTNUM][6];
    int DATA2[512][DUTNUM][6];
    int EXP1[6];
    int EXP2[6];

        EXP1[0]=exp1;//1 
        EXP1[1]=exp2;//1 
        EXP1[2]=exp3;//1 
        EXP1[3]=exp4;//1 
        EXP1[4]=exp5;//0 
        EXP1[5]=exp6;//1 

        EXP2[0]=exp2;//1 
        EXP2[1]=exp3;//1 
        EXP2[2]=exp4;//1 
        EXP2[3]=exp5;//0 
        EXP2[4]=exp6;//1 
        EXP2[5]=exp1;//1 

    double STEP1=0.0;
    double STEP2=0.0;

    if(strbcnt==SINGLE_STRB){
        UTL_SetPinViNumber         (P1_, 1);
        UTL_SetPinDrWaveform       (P1_, wave);
        UTL_SetPinInit             (P1_, UT_PIN_DEFAULT);
        UTL_SetPinDrClock          (P1_, UT_PIN_BCLK, 1);
        UTL_SetPinDrClock          (P1_, UT_PIN_CCLK, 1);
        UTL_SetPinDreClock         (P1_, 1);
        UTL_SetPinDreNumber        (P1_, 1);
        UTL_SetPinDreWaveform      (P1_, UT_DREWAV_NRZ);
        UTL_SetPinVoNumber         (P1_, 1);
    	UTL_SetPinTerm             (P1_, UT_ON); //20211214
        UTL_AddPinStrbCpeNumber    (P1_, 1, 1);
        UTL_AddPinExpStrbNumber    (P1_, 1, UT_PIN_EXP_FH);
        UTL_AddPinPdsA             (P1_, UT_SIG_C(0), 1);
        UTL_AddPinPdsB             (P1_, UT_SIG_FH, 1);
        UTL_SendPin                (P1_, "IOPIN");
    }
    if(strbcnt==DOUBLE_STRB){
        UTL_InitializePinHandle    (P1_);
        UTL_SetPinViNumber         (P1_, 1);
        UTL_SetPinDrWaveform       (P1_, wave);
        UTL_SetPinInit             (P1_, UT_PIN_DEFAULT);
        UTL_SetPinDrClock          (P1_, UT_PIN_BCLK, 1);
        UTL_SetPinDrClock          (P1_, UT_PIN_CCLK, 1);
        UTL_SetPinDreClock         (P1_, 1);
        UTL_SetPinDreNumber        (P1_, 1);
        UTL_SetPinDreWaveform      (P1_, UT_DREWAV_NRZ);
        UTL_SetPinVoNumber         (P1_, 1);
    	UTL_SetPinTerm             (P1_, UT_ON); //20211214
    	UTL_SetPinIoCtrl           (P1_, UT_ON);
        UTL_AddPinStrbCpeNumber    (P1_, 1, 1);
        UTL_AddPinStrbCpeNumber    (P1_, 2, 1);
        UTL_AddPinExpStrbNumber    (P1_, 1, UT_PIN_EXP_FH);
        UTL_AddPinExpStrbNumber    (P1_, 2, UT_PIN_EXP_FH);
        UTL_AddPinPdsA             (P1_, UT_SIG_C(0), 1);
        UTL_AddPinPdsB             (P1_, UT_SIG_FH, 1);
        UTL_SendPin                (P1_, "IOPIN");
    }

    for(LP=1;LP<=6;LP++){

        if(LP==1){ STEP1=LONG*1/4;STEP2=LONG*2/4;}
        if(LP==2){ STEP1=LONG*2/4;STEP2=LONG*3/4;}
        if(LP==3){ STEP1=LONG*3/4;STEP2=LONG*5/4;}
        if(LP==4){ STEP1=LONG*5/4;STEP2=LONG*6/4;}
        if(LP==5){ STEP1=LONG*6/4;STEP2=LONG*7/4;}
        if(LP==6){ STEP1=LONG*7/4;STEP2=LONG*9/4;}

        UTL_AddTgStrb              (TG_, 1, 1, STEP1);
        if(strbcnt==DOUBLE_STRB){
            UTL_AddTgStrb              (TG_, 1, 2, STEP2);
        }
        UTL_SendTg                 (TG_);

        // SEND MPAT PATT
        UTL_SetFctMpatName         (FCT_, "pat_ppat.mpa");
        UTL_SetFctFailInhibit      (FCT_, UT_OFF);
        UTL_SetFctStartPc          (FCT_, 0x100);
        UTL_MeasFct                (FCT_);

        // READ FUNC2 for STRB1 
        DutCursor dutcur = UTL_GetDutCursor(UT_MDUT);
        UT_DUT    dut = 0;
        PinCursor pincur;
        UT_PIN    pin = 0;
        rph = UTL_GetFctReadPinHandle();

        UTL_SetFctReadPinMode (rph, UT_RES_STRB1_FAILED );

        while((dut = UTL_NextDut (dutcur)) != UT_NOMORE){
            UTL_SetFctReadPinDut (rph, dut);
            pincur = UTL_GetPinCursor ("IOPIN");
            while((pin = UTL_NextPin (pincur)) != UT_NOMORE){
                UTL_SetFctReadPinNumber (rph, pin);
                DATA1[pin-1][dut-1][LP-1]= UTL_ReadFctPin(rph);
                if(DEBUG==1) printf("DATA[%d][%d][%d]=%d \n", pin-1,dut-1,LP-1,DATA1[pin-1][dut-1][LP-1]); fflush(stdout);
            }
            UTL_DeleteCursor (pincur);
        }
        UTL_DeleteCursor (dutcur);

        if(strbcnt==DOUBLE_STRB){
            // READ FUNC2 for STRB2
            dutcur = UTL_GetDutCursor(UT_MDUT);
            dut = 0;
            pin = 0;
            rph = UTL_GetFctReadPinHandle();

            UTL_SetFctReadPinMode (rph, UT_RES_STRB2_FAILED );

            while((dut = UTL_NextDut (dutcur)) != UT_NOMORE){
                UTL_SetFctReadPinDut (rph, dut);
                pincur = UTL_GetPinCursor ("IOPIN");
                while((pin = UTL_NextPin (pincur)) != UT_NOMORE){
                    UTL_SetFctReadPinNumber (rph, pin);
                    DATA2[pin-1][dut-1][LP-1]= UTL_ReadFctPin(rph);
                    if(DEBUG==1) printf("DATA[%d][%d][%d]=%d \n", pin-1,dut-1,LP-1,DATA2[pin-1][dut-1][LP-1]); fflush(stdout);
                }
                UTL_DeleteCursor (pincur);
            }
            UTL_DeleteCursor (dutcur);
        }
    }


    int FLG=0;
    DutCursor dutcur = UTL_GetDutCursor(UT_MDUT);
    UT_DUT    dut = 0;
    PinCursor pincur;
    UT_PIN    pin = 0;
    while((dut = UTL_NextDut(dutcur)) != UT_NOMORE){
        UTL_ResetTestResult(dut, testarg->testname, UT_RES_FUNC);
        pincur = UTL_GetPinCursor ("IOPIN");
        while((pin = UTL_NextPin(pincur)) != UT_NOMORE){
            for(j=0;j<6;j++){
                if(DATA1[pin-1][dut-1][j]!=EXP1[j]){
                    if(DEBUG==1){printf("DUT%d P%d STRB1-%d  FAIL**\n",dut, pin,j+1); fflush(stdout);}
                    UTL_SetTestResult(dut, testarg->testname, UT_RES_FUNC);
                }
                else{
                    if(DEBUG==1){printf("DUT%d P%d STRB1-%d  ***PASS\n",dut, pin,j+1); fflush(stdout);}
                }
                if(strbcnt==DOUBLE_STRB){
                    if(DATA2[pin-1][dut-1][j]!=EXP2[j]){
                        if(DEBUG==1){printf("DUT%d P%d STRB2-%d  FAIL**\n",dut, pin,j+1); fflush(stdout);}
                        UTL_SetTestResult(dut, testarg->testname, UT_RES_FUNC);
                    }
                    else{
                        if(DEBUG==1){printf("DUT%d P%d STRB2-%d  ***PASS\n",dut, pin,j+1); fflush(stdout);}
                    }
                }
            }
        } 
        UTL_DeleteCursor (pincur);

        FLG = UTL_ReadTestResult(dut, testarg->testname, UT_RES_FUNC);
        if(FLG==UT_RES_PASSED) printf("DUT%d  ***PASS\n",dut);
        if(FLG==UT_RES_FAILED) printf("DUT%d  FAIL**\n",dut);
    }
    UTL_DeleteCursor (dutcur);
}


static void STRBSCAN4(TEST_testitem *testarg, int group){
    int DATA[512][DUTNUM][6];

    double STEP=0.0;
    int j=0;
    int LP=0;
    int fix;

    //EXP[group][fix][strb]
    //         DUT/PIN:|  Even/Even  |  Even/Odd   |  Odd/Even   |   Odd/Odd    |     
    int EXP[4][4][6]= {{{1,1,1,1,0,1},{0,0,0,0,0,0},{1,1,1,1,0,1},{1,1,1,1,1,1}}, //GROUP1 (DR)
		       {{0,0,0,0,0,0},{1,1,1,1,1,1},{1,1,1,1,0,1},{1,1,1,1,0,1}}, //GROUP2 (DR)
		       {{1,1,1,0,0,0},{0,0,0,0,0,0},{1,1,1,0,0,0},{1,1,1,1,1,1}}, //GROUP3 (DRE)
		       {{0,0,0,0,0,0},{1,1,1,1,1,1},{1,1,1,0,0,0},{1,1,1,0,0,0}}};//GROUP4 (DRE)
   
    for(LP=1;LP<=6;LP++){
        if(LP==1){ STEP=LONG*1/4;}
        if(LP==2){ STEP=LONG*2/4;}
        if(LP==3){ STEP=LONG*3/4;}
        if(LP==4){ STEP=LONG*5/4;}
        if(LP==5){ STEP=LONG*6/4;}
        if(LP==6){ STEP=LONG*7/4;}

//        printf("\n STRB= %.3e   ",STEP); fflush(stdout);

        // IOPIN CONNECT
//        UTL_SetPinOpen             (ALLPIN_, UT_OFF);
//        UTL_SendPin                (ALLPIN_, "IOPIN");

        // STRB1=50US
        UTL_AddTgStrb              (TG_, 1, 1, STEP);
        UTL_SendTg                 (TG_);

        // SEND MPAT PATT
        UTL_SetFctMpatName         (FCT_, "pat_ppat.mpa");
        UTL_SetFctFailInhibit      (FCT_, UT_OFF);
        if     (group==0 || group==1) UTL_SetFctStartPc(FCT_, 0x100);
        else if(group==2 || group==3) UTL_SetFctStartPc(FCT_, 0x110);
        UTL_MeasFct                (FCT_);

        // READ FUNC for STRB1 
        DutCursor dutcur = UTL_GetDutCursor(UT_MDUT);
        UT_DUT    dut = 0;
        PinCursor pincur;
        UT_PIN    pin = 0;
        rph = UTL_GetFctReadPinHandle();

        UTL_SetFctReadPinMode (rph, UT_RES_STRB1_FAILED );

        while((dut = UTL_NextDut (dutcur)) != UT_NOMORE){
            UTL_SetFctReadPinDut (rph, dut);
            pincur = UTL_GetPinCursor ("IOPIN");
            while((pin = UTL_NextPin (pincur)) != UT_NOMORE){
                UTL_SetFctReadPinNumber (rph, pin);
                DATA[pin-1][dut-1][LP-1]= UTL_ReadFctPin(rph);
            }
            UTL_DeleteCursor (pincur);
        }
        UTL_DeleteCursor (dutcur);
    }

    DutCursor dutcur = UTL_GetDutCursor(UT_MDUT);
    UT_DUT    dut = 0;
    PinCursor pincur;
    UT_PIN    pin = 0;
    while((dut = UTL_NextDut(dutcur)) != UT_NOMORE){
        pincur = UTL_GetPinCursor ("IOPIN");
        while((pin = UTL_NextPin(pincur)) != UT_NOMORE){
	    if     (dut%2==0 && pin%2==0) fix=0; 
	    else if(dut%2==0 && pin%2==1) fix=1;
	    else if(dut%2==1 && pin%2==0) fix=2;
	    else if(dut%2==1 && pin%2==1) fix=3;

            for(j=0;j<6;j++){
                if(DEBUG==1) printf("DUT%d PIN%2d STRB1-%d = %d", dut, pin, j, DATA[pin-1][dut-1][j]); fflush(stdout);
                if(DATA[pin-1][dut-1][j]!=EXP[group][fix][j]){
                    if(DEBUG==1){printf("\t\tFAIL**\n"); fflush(stdout);}
                    UTL_SetTestResult(dut, testarg->testname, UT_RES_FUNC);
                }
                else{
                    if(DEBUG==1){printf("\t***PASS\n"); fflush(stdout);}
                }
            }
        } 
        UTL_DeleteCursor (pincur);

        if(UTL_ReadTestResult(dut, testarg->testname, UT_RES_FUNC)!=UT_RES_FAILED){
            UTL_ResetTestResult(dut, testarg->testname, UT_RES_FUNC);
        }
    }
    UTL_DeleteCursor (dutcur);

    return;
}


void TNO009(TEST_testitem *testarg){
    drcp_init();
    //printf("\nTEST  009 SINGLE STRB TIMING SCAN (dosoku)\n"); fflush(stdout);
//    printf("\n#########RZO##########");
    RadioButton wave = UT_WAV_RZO;
    int strbcnt = SINGLE_STRB;
    int exp1 = 1;
    int exp2 = 1;
    int exp3 = 1;
    int exp4 = 1;
    int exp5 = 0;
    int exp6 = 1;
    STRBSCAN1(testarg,wave,strbcnt,exp1,exp2,exp3,exp4,exp5,exp6);
    DeleteHandle();
}

void TNO010(TEST_testitem *testarg){
    drcp_init();
    //printf("\nTEST  010 DOUBLE STRB TIMING SCAN1 (dosoku)\n"); fflush(stdout);
//    printf("\n#########RZO##########");
    RadioButton wave = UT_WAV_RZO;
    int strbcnt = DOUBLE_STRB;
    int exp1 = 1;
    int exp2 = 1;
    int exp3 = 1;
    int exp4 = 1;
    int exp5 = 0;
    int exp6 = 1;
    STRBSCAN1(testarg,wave,strbcnt,exp1,exp2,exp3,exp4,exp5,exp6);
    DeleteHandle();
}

void TNO011(TEST_testitem *testarg){
    drcp_init();
    //printf("\nTEST  011 DOUBLE STRB TIMING SCAN2 (dosoku)\n"); fflush(stdout);
//    printf("\n#########RZO##########");
    RadioButton wave = UT_WAV_RZO;
    int strbcnt = DOUBLE_STRB;
    int exp1 = 1;
    int exp2 = 1;
    int exp3 = 1;
    int exp4 = 1;
    int exp5 = 0;
    int exp6 = 1;
    STRBSCAN2(testarg,wave,strbcnt,exp1,exp2,exp3,exp4,exp5,exp6);
    DeleteHandle();
}


void TNO012(TEST_testitem *testarg){
    drcp_init();
    //printf("\nTEST  012 LEVEL SET"); fflush(stdout);
    int III=0;

    //set vi per pin/dut
    DutCursor dutc;
    UT_DUT    dut;
    PinCursor pincur;
    UT_PIN    pin = 0;

    dutc = UTL_GetDutCursor(UT_DDUT);
    UTL_SetViHvDr(IN_[3], UT_OFF);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
   	pincur = UTL_GetPinCursor("IOPIN");
    	while((pin=UTL_NextPin(pincur)) != UT_NOMORE){
    	    if     (dut%2==0 && pin%2==0) UTL_SetViHigh (IN_[3], 0.5); 
    	    else if(dut%2==0 && pin%2==1) UTL_SetViHigh (IN_[3], 1.0); 
    	    else if(dut%2==1 && pin%2==0) UTL_SetViHigh (IN_[3], 1.5); 
    	    else if(dut%2==1 && pin%2==1) UTL_SetViHigh (IN_[3], 2.0); 
    	    UTL_SetViLow               (IN_[3], 0.0);
    	    UTL_SendViPerPin(IN_[3],pin,dut);	
    //	    UTL_DeleteHandle(IN_[1]);
    	}
    	UTL_DeleteCursor(pincur);
    }
    UTL_DeleteCursor(dutc);

    // ALLPIN=OPEN
    UTL_SetPinOpen             (ALLPIN_, UT_ON);
    UTL_SendPin                (ALLPIN_, "ALLPIN");

    // ISVM=MVM,M(10V)
    UTL_SetDcMode              (ISVM_,  UT_DCT_MVM);
    UTL_SetDcMrange            (ISVM_, 7, 0);

    // LIMIT DC=2.05V,0.45V
    double HLIMIT=2.05;
    double LLIMIT=0.45;
    UTL_SetDcLimitHigh         (ISVM_, HLIMIT, UT_OFF);
    UTL_SetDcLimitLow          (ISVM_, LLIMIT, UT_OFF);
    UTL_SendDc                 (ISVM_, 1);

    // TIME1=3MS:VS
    // TIME2=3MS:IN
    // TIME3=3MS:OTHERS
    // SETTLING TIME=10MS,10MS
    PowerSeq();

  if(IO_number==160){
        printf(" (tansoku)\n"); fflush(stdout);
    	printf("---------------------------------------------------------------------\n"); fflush(stdout);
    	printf("GO/NOGO    DATA     UPPER     LOWER      PIN       DUT   \n"); fflush(stdout);
    	printf("---------------------------------------------------------------------\n"); fflush(stdout);
     for(III=1;III<=512;III++) {
        // P1=IN1,FIXH,DC
        UTL_SetPinOpen             (IOPIN_, UT_OFF);
        UTL_SetPinViNumber         (IOPIN_, 3);
        UTL_SetPinDrWaveform       (IOPIN_, UT_WAV_FIXH);
        UTL_SetPinInit             (IOPIN_, UT_PIN_DEFAULT);
        UTL_SendPin                (IOPIN_, PIN_number[III-1]);

        // MEAS DC
        UTL_SetDctPinList          (DCT_, PIN_number[III-1]);
        UTL_SetDctRelayMode        (DCT_, UT_DCT_SWAP);		//alpha2
        UTL_SetDctPinVi            (DCT_, UT_ON);		//alpha2
        UTL_SetDctPinHvDr          (DCT_, UT_OFF);		//alpha2
        UTL_MeasDct                (DCT_);
        TNO006(HLIMIT,LLIMIT,III,testarg);

        // PD1=OPEN
        UTL_SetPinOpen             (IOPIN_, UT_ON);
        UTL_SendPin                (IOPIN_, PIN_number[III-1]);
    	
	if(III%64==18) III=III+46;	
	}
  }

  if(IO_number==10){
        printf(" (dosoku)\n"); fflush(stdout);
        // PD1=IN1,FIXH,DC
        UTL_SetPinOpen             (P1_, UT_OFF);
        UTL_SetPinViNumber         (P1_, 3);
        UTL_SetPinDrWaveform       (P1_, UT_WAV_FIXH);
        UTL_SetPinInit             (P1_, UT_PIN_DEFAULT);
        UTL_SetPinHvDr             (P1_, UT_OFF);
        UTL_SendPin                (P1_, "IOPIN");

        // MEAS DC
        UTL_SetDctPinList          (DCT_, "IOPIN");
        UTL_SetDctRelayMode        (DCT_, UT_DCT_SWAP);		//alpha2
        UTL_SetDctPinVi            (DCT_, UT_ON);		//alpha2
        UTL_SetDctPinHvDr          (DCT_, UT_OFF);		//alpha2
        UTL_MeasDct                (DCT_);
        TNO006b(HLIMIT,LLIMIT,testarg);

        // PD1=OPEN
        UTL_SetPinOpen             (P1_, UT_ON);
        UTL_SendPin                (P1_, "ALLPIN");
    }

    DeleteHandle();
}

void TNO013(TEST_testitem *testarg){
    drcp_init();
    //printf("\nTEST  013 FIXED WAVEFORM OUTPUT LEVEL (DR)\n"); fflush(stdout);
    RadioButton wave = UT_WAV_RZO;
    int group;   
 
    UTL_SetViHigh              (IN_[1], 2.0);
    UTL_SetViLow               (IN_[1], 0.0);
    UTL_SendVi                 (IN_[1], 1);

    UTL_SetVt                  (VT_[1], 0.0);
    UTL_SendVt                 (VT_[1], 1);

    UTL_SetVoHigh              (OUT_[1], 1.5);
    UTL_SetVoLow               (OUT_[1], 0.5);
    UTL_SendVo                 (OUT_[1], 1);

    UTL_AddTgRate              (TG_, 1,  LONG);
    UTL_AddTgAclk              (TG_, 1, 1, 0.2*LONG);
    UTL_AddTgBclk              (TG_, 1, 1, 0.4*LONG);
    UTL_AddTgCclk              (TG_, 1, 1, 0.6*LONG);
    UTL_AddTgDreL              (TG_, 1, 1, 0e-6);
    UTL_AddTgDreT              (TG_, 1, 1, 0e-6);
    UTL_SendTg                 (TG_);

    // ALLPIN OPEN
    UTL_SetPinOpen             (ALLPIN_, UT_ON);
    UTL_SendPin                (ALLPIN_, "ALLPIN");

    //P1=IN1,RZX,BCLK1,DRECLK1,DRENRZ,STRB1,OUT1,<C0,FH>
    UTL_InitializePinHandle    (P1_);
    UTL_SetPinViNumber         (P1_, 1);
    UTL_SetPinDrWaveform       (P1_, wave);
    UTL_SetPinInit             (P1_, UT_PIN_DEFAULT);
    UTL_SetPinDrClock          (P1_, UT_PIN_BCLK, 1);
    UTL_SetPinDrClock          (P1_, UT_PIN_CCLK, 1);
    UTL_SetPinDreClock         (P1_, 1);
    UTL_SetPinDreNumber        (P1_, 1);
    UTL_SetPinDreWaveform      (P1_, UT_DREWAV_NRZ);
    UTL_SetPinTerm             (P1_, UT_ON); //20211214
    UTL_SetPinIoCtrl           (P1_, UT_ON);
    UTL_SetPinVoNumber         (P1_, 1);
    UTL_AddPinStrbCpeNumber    (P1_, 1, 1);
    UTL_AddPinExpStrbNumber    (P1_, 1, UT_PIN_EXP_FH);
    UTL_AddPinPdsA             (P1_, UT_SIG_C(0), 1);
    UTL_AddPinPdsB             (P1_, UT_SIG_FH, 1);
    UTL_SendPin                (P1_, "IOPIN");

    //FixLevel
    LevelFixHandle  fix_h=UTL_GetLevelFixHandle();
    RadioButton level;
    DutCursor dutc;
    UT_DUT dut;
    PinCursor pincur;
    UT_PIN pin;

    dutc = UTL_GetDutCursor(UT_DDUT);
    printf("\n#### PIN x FIX-LEVEL <CHECK1/2> #### \n"); fflush(stdout);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
   	pincur = UTL_GetPinCursor("IOPIN");
    	while((pin=UTL_NextPin(pincur)) != UT_NOMORE){
    	    if     (dut%2==0 && pin%2==0)  level=UT_PIN_NONE;
    	    else if(dut%2==0 && pin%2==1)  level=UT_PIN_FIXH;
    	    else if(dut%2==1 && pin%2==0)  level=UT_PIN_NONE;
    	    else if(dut%2==1 && pin%2==1)  level=UT_PIN_FIXL;
            UTL_SetLevelFixOutputLevel(fix_h,UT_PIN_DR,level);
            UTL_SendLevelFix(fix_h,pin,dut);
	}
	UTL_DeleteCursor (pincur);
    }
    UTL_DeleteCursor(dutc);
    group=0;
    STRBSCAN4(testarg,group);

    dutc = UTL_GetDutCursor(UT_DDUT);
    printf("\n#### PIN x FIX-LEVEL <CHECK2/2> #### \n"); fflush(stdout);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
   	pincur = UTL_GetPinCursor("IOPIN");
    	while((pin=UTL_NextPin(pincur)) != UT_NOMORE){
    	    if     (dut%2==0 && pin%2==0)  level=UT_PIN_FIXH;
    	    else if(dut%2==0 && pin%2==1)  level=UT_PIN_FIXL;
    	    else if(dut%2==1 && pin%2==0)  level=UT_PIN_NONE;
    	    else if(dut%2==1 && pin%2==1)  level=UT_PIN_NONE;
            UTL_SetLevelFixOutputLevel(fix_h,UT_PIN_DR,level);
            UTL_SendLevelFix(fix_h,pin,dut);
	}
	UTL_DeleteCursor (pincur);
    }
    UTL_DeleteCursor(dutc);
    group=1;
    STRBSCAN4(testarg,group);

    // ALLPIN OPEN
    //UTL_SetPinOpen             (ALLPIN_, UT_ON);	//20211214
    //UTL_SendPin                (ALLPIN_, "ALLPIN");	//20211214
    //DeleteHandle();					//20211214
}

void TNO014(TEST_testitem *testarg){
    drcp_init();
    //printf("\nTEST  014 FIXED WAVEFORM OUTPUT LEVEL (DRE)\n"); fflush(stdout);
    RadioButton wave = UT_WAV_FIXH;
    int group;   
 
    UTL_SetViHigh              (IN_[1], 2.0);
    UTL_SetViLow               (IN_[1], 0.0);
    UTL_SendVi                 (IN_[1], 1);

    UTL_SetVt                  (VT_[1], 0.0);
    UTL_SendVt                 (VT_[1], 1);

    UTL_SetVoHigh              (OUT_[1], 1.5);
    UTL_SetVoLow               (OUT_[1], 0.5);
    UTL_SendVo                 (OUT_[1], 1);

    UTL_AddTgRate              (TG_, 1,  LONG);
    UTL_AddTgAclk              (TG_, 1, 1, 0.2*LONG);
    UTL_AddTgBclk              (TG_, 1, 1, 0.4*LONG);
    UTL_AddTgCclk              (TG_, 1, 1, 0.6*LONG);
    UTL_AddTgDreL              (TG_, 1, 1, 0e-6);
    UTL_AddTgDreT              (TG_, 1, 1, 0e-6);
    UTL_SendTg                 (TG_);

    // ALLPIN OPEN
    UTL_SetPinOpen             (ALLPIN_, UT_ON);
    UTL_SendPin                (ALLPIN_, "ALLPIN");

    //P1=IN1,FIXH,BCLK1,DRECLK1,DRENRZ,STRB1,OUT1,<C0,FH>
    UTL_InitializePinHandle    (P1_);
    UTL_SetPinViNumber         (P1_, 1);
    UTL_SetPinDrWaveform       (P1_, wave);
    UTL_SetPinInit             (P1_, UT_PIN_DEFAULT);
    //UTL_SetPinDrClock          (P1_, UT_PIN_BCLK, 1);
    //UTL_SetPinDrClock          (P1_, UT_PIN_CCLK, 1);
    UTL_SetPinDreClock         (P1_, 1);
    UTL_SetPinDreNumber        (P1_, 1);
    UTL_SetPinDreWaveform      (P1_, UT_DREWAV_NRZ);
    UTL_SetPinVoNumber         (P1_, 1);
    UTL_AddPinStrbCpeNumber    (P1_, 1, 1);
    UTL_AddPinExpStrbNumber    (P1_, 1, UT_PIN_EXP_FH);
    UTL_AddPinPdsA             (P1_, UT_SIG_C(0), 1);
    UTL_AddPinPdsB             (P1_, UT_SIG_FH, 1);
    UTL_SetPinVtNumber         (P1_, 1); 
    UTL_SetPinIoCtrl           (P1_, UT_ON);
    UTL_SetPinTerm             (P1_, UT_ON);
    UTL_SendPin                (P1_, "IOPIN");

    //FixLevel
    LevelFixHandle  fix_h=UTL_GetLevelFixHandle();
    RadioButton level;
    DutCursor dutc;
    UT_DUT dut;
    PinCursor pincur;
    UT_PIN pin;

    dutc = UTL_GetDutCursor(UT_DDUT);
    printf("\n#### PIN x FIX-LEVEL <CHECK1/2> #### \n"); fflush(stdout);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
   	pincur = UTL_GetPinCursor("IOPIN");
    	while((pin=UTL_NextPin(pincur)) != UT_NOMORE){
    	    if     (dut%2==0 && pin%2==0)  level=UT_PIN_NONE;
    	    else if(dut%2==0 && pin%2==1)  level=UT_PIN_FIXH;
    	    else if(dut%2==1 && pin%2==0)  level=UT_PIN_NONE;
    	    else if(dut%2==1 && pin%2==1)  level=UT_PIN_FIXL;
            UTL_SetLevelFixOutputLevel(fix_h,UT_PIN_DRE,level);
            UTL_SendLevelFix(fix_h,pin,dut);
	}
	UTL_DeleteCursor (pincur);
    }
    UTL_DeleteCursor(dutc);
    group=2;
    STRBSCAN4(testarg,group);

    dutc = UTL_GetDutCursor(UT_DDUT);
    printf("\n#### PIN x FIX-LEVEL <CHECK2/2> #### \n"); fflush(stdout);
    while((dut=UTL_NextDut(dutc))!=UT_NOMORE){
   	pincur = UTL_GetPinCursor("IOPIN");
    	while((pin=UTL_NextPin(pincur)) != UT_NOMORE){
    	    if     (dut%2==0 && pin%2==0)  level=UT_PIN_FIXH;
    	    else if(dut%2==0 && pin%2==1)  level=UT_PIN_FIXL;
    	    else if(dut%2==1 && pin%2==0)  level=UT_PIN_NONE;
    	    else if(dut%2==1 && pin%2==1)  level=UT_PIN_NONE;
            UTL_SetLevelFixOutputLevel(fix_h,UT_PIN_DRE,level);
            UTL_SendLevelFix(fix_h,pin,dut);
	}
	UTL_DeleteCursor (pincur);
    }
    UTL_DeleteCursor(dutc);
    group=3;
    STRBSCAN4(testarg,group);

    // ALLPIN OPEN
    //UTL_SetPinOpen             (ALLPIN_, UT_ON);	//20211214
    //UTL_SendPin                (ALLPIN_, "ALLPIN");	//20211214
    //DeleteHandle();					//20211214
}

void andfail(TEST_testitem *testarg){
    drcp_init();

    //IN1=2V,1V
    UTL_SetViHigh              (IN_[1], 2.0);
    UTL_SetViLow               (IN_[1], 0.0);
    UTL_SendVi                 (IN_[1], 1);

    // VT
    UTL_SetVt                  (VT_[1], 1.0);
    UTL_SendVt                 (VT_[1], 1);

    // VO
    UTL_SetVoHigh              (OUT_[1], 1.5);
    UTL_SetVoLow               (OUT_[1], 0.5);
    UTL_SendVo                 (OUT_[1], 1);

    // RATE=100NS
    UTL_AddTgRate              (TG_, 1,  TCYC);
    UTL_AddTgBclk              (TG_, 1, 1, 0);
    UTL_AddTgCclk              (TG_, 1, 1, TCYC*1/2);
    UTL_AddTgStrb              (TG_, 1, 1, TCYC*5/4);
    UTL_AddTgStrb              (TG_, 1, 2, TCYC*7/4);
    UTL_SendTg                 (TG_);

    // ALLPIN=OPEN
    UTL_SetPinOpen             (ALLPIN_, UT_ON);
    UTL_SendPin                (ALLPIN_, "ALLPIN");

    // P33=OUTL1,VT1,STRB1,<D0>
    UTL_InitializePinHandle    (P1_);
    UTL_SetPinViNumber         (P1_, 1);
    UTL_SetPinInit             (P1_, UT_PIN_DEFAULT);
    UTL_SetPinDrClock          (P1_, UT_PIN_BCLK, 1);
    UTL_SetPinDrClock          (P1_, UT_PIN_CCLK, 1);
    UTL_SetPinDreClock         (P1_, 1);
    UTL_SetPinDreNumber        (P1_, 1);
    UTL_SetPinDreWaveform      (P1_, UT_DREWAV_NRZ);
    UTL_SetPinVoNumber         (P1_, 1);
    UTL_SetPinTerm             (P1_, UT_ON);
    UTL_SetPinIoCtrl           (P1_, UT_ON);
    UTL_AddPinStrbCpeNumber    (P1_, 1, 1);
    UTL_AddPinStrbCpeNumber    (P1_, 2, 1);
    UTL_AddPinExpStrbNumber    (P1_, 1, UT_PIN_EXP_FH);
    UTL_AddPinExpStrbNumber    (P1_, 2, UT_PIN_EXP_FH);
    UTL_AddPinPdsA             (P1_, UT_SIG_C(0), 1);
    UTL_AddPinPdsB             (P1_, UT_SIG_C(1), 1);
    UTL_SetPinDrWaveform       (P1_, UT_WAV_RZO);
    UTL_SendPin                (P1_, "IOPIN");

    // SEND MPAT PAT
    set_reg(UT_REG_IDX1, 1e7-3); // 1e7*100ns=1s
    UTL_SetFctMpatName         (FCT_, "pat_ppat.mpa");
    UTL_SetFctFailInhibit      (FCT_, UT_OFF);
    UTL_SetFctStartPc          (FCT_, 0x200);

    CheckButton ov;
    DSlider t;
    UTL_StartTimer(UT_TIMER_R1US);
    UTL_MeasFct                (FCT_);
    t = UTL_ReadTimer(&ov);

    double exp_t = 100e-3;
    USlider exp_xb = 1000;
    USlider xb = UTL_ReadUSRegister(UT_REG_XB, 1);
    printf("t=%f (exp_t<%f), XB=%d (0<exp_xb<%d)", t, exp_t, xb, exp_xb);
    if((t<exp_t)&&(xb!=0)&&(xb<exp_xb)){
      testresult_pass4alldut(testarg->testname);
      printf(" PASS\n");
    }
    else{
      testresult_fail4alldut(testarg->testname);
      printf(" ****FAIL\n");
    }
   
    DeleteHandle();
    return;
}

#if 0
/*=================Check==================*/	

//debug//printf("--------------------------------------------------------------------------------\n"); fflush(stdout);
	UTL_SetTestAction(TEST_,TNO001);
	UTL_Test(TEST_,"TNO001");
	InitHandle();

//debug//printf("--------------------------------------------------------------------------------\n"); fflush(stdout);
	UTL_SetTestAction(TEST_,TNO002);
	UTL_Test(TEST_,"TNO002");
	InitHandle();

//printf("--------------------------------------------------------------------------------\n"); fflush(stdout);
	UTL_SetTestAction(TEST_,TNO003);
	UTL_Test(TEST_,"TNO003");
	InitHandle();

//debug//printf("--------------------------------------------------------------------------------\n"); fflush(stdout);
	UTL_SetTestAction(TEST_,TNO004);
	UTL_Test(TEST_,"TNO004");
	InitHandle();
//debug//printf("--------------------------------------------------------------------------------\n"); fflush(stdout);
	UTL_SetTestAction(TEST_,TNO005);
	UTL_Test(TEST_,"TNO005");
	InitHandle();

#if CHECK_ReadFct
//debug//printf("--------------------------------------------------------------------------------\n"); fflush(stdout);
	UTL_SetTestAction(TEST_,TNO007);
	UTL_Test(TEST_,"TNO007");
	InitHandle();
#endif

//debug//printf("--------------------------------------------------------------------------------\n"); fflush(stdout);
	UTL_SetTestAction(TEST_,TNO008);
	UTL_Test(TEST_,"TNO008");
	InitHandle();
//debug//printf("--------------------------------------------------------------------------------\n"); fflush(stdout);
	UTL_SetTestAction(TEST_,TNO009);
	UTL_Test(TEST_,"TNO009");
	InitHandle();
//debug//printf("--------------------------------------------------------------------------------\n"); fflush(stdout);
	UTL_SetTestAction(TEST_,TNO010);
	UTL_Test(TEST_,"TNO010");
	InitHandle();
//debug//printf("--------------------------------------------------------------------------------\n"); fflush(stdout);
	UTL_SetTestAction(TEST_,TNO011);
	UTL_Test(TEST_,"TNO011");
	InitHandle();
//debug//printf("--------------------------------------------------------------------------------\n"); fflush(stdout);
	UTL_SetTestAction(TEST_,TNO012);
	UTL_Test(TEST_,"TNO012");
	InitHandle();
#if JIG
//debug//printf("--------------------------------------------------------------------------------\n"); fflush(stdout);
	UTL_SetTestAction(TEST_,TNO013);
	UTL_Test(TEST_,"TNO013");
	InitHandle();
//debug//printf("--------------------------------------------------------------------------------\n"); fflush(stdout);
	UTL_SetTestAction(TEST_,TNO014);
	UTL_Test(TEST_,"TNO014");
	InitHandle();
#endif

    printf("!!!!!!!!!!!!!END\n"); fflush(stdout);
    return 0;
}	
#endif

