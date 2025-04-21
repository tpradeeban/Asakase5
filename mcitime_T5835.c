

// FutureSuite T5835 1.04
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <test.h>
#include <UTSC.h>
#include <UTHN.h>

extern int FK[17];

#ifdef __cplusplus
extern "C" {
#endif

#define T_MAX (2695)
#define NUM_MAX (100)
#
static struct timespec LAP_TIME[T_MAX] = { { 0, 0 } };
char *MCI_LIST[T_MAX];
double ACCUMULATED_TIME[T_MAX] = { 0.0 };
double ACCUMULATED_INDIVIDUAL_TIME[T_MAX][NUM_MAX] = { 0.0 };
int    CALLS[T_MAX]={0};

inline static void START_LAPTIMER(int id)
{
	clock_gettime(CLOCK_REALTIME, LAP_TIME+id);
}

inline static void STOP_LAPTIMER(int id)
{
	int s, n;
	struct timespec t;
	double d;

	clock_gettime(CLOCK_REALTIME, &t);
	s = t.tv_sec -  LAP_TIME[id].tv_sec;
	n = t.tv_nsec - LAP_TIME[id].tv_nsec;
	d = (double) ((double)s + (double)n * 1.0E-9);

	ACCUMULATED_TIME[id] += d;
	if(CALLS[id]<NUM_MAX){
		ACCUMULATED_INDIVIDUAL_TIME[id][CALLS[id]] = d;
	}
	CALLS[id]++;
}

static void TimeAnalyzeInit()
{
	int id;
	for(id = 0; id < T_MAX; id++)
	{
		ACCUMULATED_TIME[id] = 0.0;
		CALLS[id]=0;
	}
}

static void TimeAnalyzeResult(char* TestName)
{
	int id;
	int num;
	double meatime = 0;
	double mcitime = 0;
	double womci   = 0;

	//Average
	if(FK[2]==UT_ON){
		printf("[TA]  Average ------------------------------------------------------------------------\n");
		printf("[TA]  MCI Statement                            Time(mS)  Count       Ave    Test_Name \n");
		for(id = 1; id < T_MAX; id++)
		{
			if(CALLS[id]) {
				//if (ACCUMULATED_TIME[id] >= 0.0001 )
				printf("[TA]  %-35s %10.1f %8d %10.1f    %s\n",MCI_LIST[id],ACCUMULATED_TIME[id]*1000,CALLS[id],ACCUMULATED_TIME[id]*1000/CALLS[id],TestName);
				if      (strcmp(MCI_LIST[id], "UTL_MeasDct" ) == 0) meatime += ACCUMULATED_TIME[id];
				else if (strcmp(MCI_LIST[id], "UTL_MeasFct" ) == 0) meatime += ACCUMULATED_TIME[id];
				else if (strcmp(MCI_LIST[id], "UTL_StartFct") == 0) meatime += ACCUMULATED_TIME[id];
				else if (strcmp(MCI_LIST[id], "UTL_StartDct") == 0) meatime += ACCUMULATED_TIME[id];
				else if (strcmp(MCI_LIST[id], "UTL_WaitTime") == 0) meatime += ACCUMULATED_TIME[id];
				else mcitime += ACCUMULATED_TIME[id];
			}
		}

		womci = ACCUMULATED_TIME[0]-meatime-mcitime;
		printf("[TA]  %-35s %10.1f %8d %10.1f    %s\n",MCI_LIST[0],ACCUMULATED_TIME[0]*1000,CALLS[0],ACCUMULATED_TIME[0]*1000/CALLS[0],TestName);
		printf("[TA]  %-35s %10.1f %8d %10.1f    %s\n","total_meas_wait"    , meatime*1000,0,0.0,TestName);
		printf("[TA]  %-35s %10.1f %8d %10.1f    %s\n","total_mci_wo_meas"  , mcitime*1000,0,0.0,TestName);
		printf("[TA]  %-35s %10.1f %8d %10.1f    %s\n","wo_mci"             ,   womci*1000,0,0.0,TestName);
		printf("\n");
	}

	//Individual
	if(FK[3]==UT_ON){
		printf("[TA]  Individual ---------------------------------------------------------------------\n");
		printf("[TA]  MCI Statement                      Seq.  Time(S)                      Test_Name \n");
		for(id = 0; id < T_MAX; id++)
		{
			for(num = 0; num < (CALLS[id]<NUM_MAX ? CALLS[id]:NUM_MAX); num++){
				printf("[TA]  %-35s(%3d) %e                 %s\n",MCI_LIST[id],num+1,ACCUMULATED_INDIVIDUAL_TIME[id][num],TestName);
			}
		}
		printf("\n");
	}
}




void _UTL_Test(TestHandle h, char *tname)
{
	TimeAnalyzeInit();
	MCI_LIST[0] = "UTL_Test";
	START_LAPTIMER(0);
	UTL_Test (h, tname);
	STOP_LAPTIMER(0);
	TimeAnalyzeResult(tname);
}

int _UTL_Xtest(TestHandle h, char *tname)
{
	TimeAnalyzeInit();
	MCI_LIST[0] = "UTL_Test";
	START_LAPTIMER(0);
	int ret = UTL_Xtest (h, tname);
	STOP_LAPTIMER(0);
	TimeAnalyzeResult(tname);
	return ret;
}

void _UTL_InitTest( int  arg1, char ** arg2)
{
	MCI_LIST[1] = "UTL_InitTest";
	START_LAPTIMER(1);
	UTL_InitTest( arg1, arg2);
	STOP_LAPTIMER(1);
}
void _UTL_CreatePinList( char * arg1)
{
	MCI_LIST[2] = "UTL_CreatePinList";
	START_LAPTIMER(2);
	UTL_CreatePinList( arg1);
	STOP_LAPTIMER(2);
}
void _UTL_SetPinType( char * arg1, RadioButton arg2)
{
	MCI_LIST[3] = "UTL_SetPinType";
	START_LAPTIMER(3);
	UTL_SetPinType( arg1, arg2);
	STOP_LAPTIMER(3);
}
void _UTL_AddPinNumber( char * arg1, RadioButton arg2)
{
	MCI_LIST[4] = "UTL_AddPinNumber";
	START_LAPTIMER(4);
	UTL_AddPinNumber( arg1, arg2);
	STOP_LAPTIMER(4);
}
void _UTL_ClearPinNumber( char * arg1)
{
	MCI_LIST[5] = "UTL_ClearPinNumber";
	START_LAPTIMER(5);
	UTL_ClearPinNumber( arg1);
	STOP_LAPTIMER(5);
}
void _UTL_AppendPinList( char * arg1, char * arg2)
{
	MCI_LIST[6] = "UTL_AppendPinList";
	START_LAPTIMER(6);
	UTL_AppendPinList( arg1, arg2);
	STOP_LAPTIMER(6);
}
TestHandle _UTL_GetTestHandle()
{
	MCI_LIST[7] = "UTL_GetTestHandle";
	START_LAPTIMER(7);
	TestHandle retval = UTL_GetTestHandle();
	STOP_LAPTIMER(7);
	return retval;
}
void _UTL_SetTestAction( TestHandle arg1, void (*arg2)())
{
	MCI_LIST[8] = "UTL_SetTestAction";
	START_LAPTIMER(8);
	UTL_SetTestAction( arg1, arg2);
	STOP_LAPTIMER(8);
}
void _UTL_SetXtestAction( TestHandle arg1, int (*arg2)())
{
	MCI_LIST[9] = "UTL_SetXtestAction";
	START_LAPTIMER(9);
	UTL_SetXtestAction( arg1, arg2);
	STOP_LAPTIMER(9);
}
void _UTL_SetTestArg( TestHandle arg1, void * arg2)
{
	MCI_LIST[10] = "UTL_SetTestArg";
	START_LAPTIMER(10);
	UTL_SetTestArg( arg1, arg2);
	STOP_LAPTIMER(10);
}
void _UTL_SetCategory( UT_DUT arg1, RadioButton arg2)
{
	MCI_LIST[11] = "UTL_SetCategory";
	START_LAPTIMER(11);
	UTL_SetCategory( arg1, arg2);
	STOP_LAPTIMER(11);
}
void _UTL_ResetCategory( UT_DUT arg1, RadioButton arg2)
{
	MCI_LIST[12] = "UTL_ResetCategory";
	START_LAPTIMER(12);
	UTL_ResetCategory( arg1, arg2);
	STOP_LAPTIMER(12);
}
CheckButton _UTL_ReadCategory( UT_DUT arg1, RadioButton arg2)
{
	MCI_LIST[13] = "UTL_ReadCategory";
	START_LAPTIMER(13);
	CheckButton retval = UTL_ReadCategory( arg1, arg2);
	STOP_LAPTIMER(13);
	return retval;
}
CategoryCursor _UTL_GetCategoryCursor( UT_DUT arg1)
{
	MCI_LIST[14] = "UTL_GetCategoryCursor";
	START_LAPTIMER(14);
	CategoryCursor retval = UTL_GetCategoryCursor( arg1);
	STOP_LAPTIMER(14);
	return retval;
}
RadioButton _UTL_NextCategory( CategoryCursor arg1)
{
	MCI_LIST[15] = "UTL_NextCategory";
	START_LAPTIMER(15);
	RadioButton retval = UTL_NextCategory( arg1);
	STOP_LAPTIMER(15);
	return retval;
}
void _UTL_SendSort( UT_DUT arg1, RadioButton arg2)
{
	MCI_LIST[16] = "UTL_SendSort";
	START_LAPTIMER(16);
	UTL_SendSort( arg1, arg2);
	STOP_LAPTIMER(16);
}
RadioButton _UTL_ReadSort( UT_DUT arg1)
{
	MCI_LIST[17] = "UTL_ReadSort";
	START_LAPTIMER(17);
	RadioButton retval = UTL_ReadSort( arg1);
	STOP_LAPTIMER(17);
	return retval;
}
void _UTL_SendSymbol( char * arg1, char * arg2)
{
	MCI_LIST[18] = "UTL_SendSymbol";
	START_LAPTIMER(18);
	UTL_SendSymbol( arg1, arg2);
	STOP_LAPTIMER(18);
}
char * _UTL_ReadSymbol( char * arg1)
{
	MCI_LIST[19] = "UTL_ReadSymbol";
	START_LAPTIMER(19);
	char * retval = UTL_ReadSymbol( arg1);
	STOP_LAPTIMER(19);
	return retval;
}
void _UTL_SendSystemValue( char * arg1, char * arg2)
{
	MCI_LIST[20] = "UTL_SendSystemValue";
	START_LAPTIMER(20);
	UTL_SendSystemValue( arg1, arg2);
	STOP_LAPTIMER(20);
}
char * _UTL_ReadSystemValue( char * arg1)
{
	MCI_LIST[21] = "UTL_ReadSystemValue";
	START_LAPTIMER(21);
	char * retval = UTL_ReadSystemValue( arg1);
	STOP_LAPTIMER(21);
	return retval;
}
VariableHandle _UTL_GetVariableHandle()
{
	MCI_LIST[22] = "UTL_GetVariableHandle";
	START_LAPTIMER(22);
	VariableHandle retval = UTL_GetVariableHandle();
	STOP_LAPTIMER(22);
	return retval;
}
void _UTL_SetVariableStation( VariableHandle arg1, int arg2)
{
	MCI_LIST[23] = "UTL_SetVariableStation";
	START_LAPTIMER(23);
	UTL_SetVariableStation( arg1, arg2);
	STOP_LAPTIMER(23);
}
void _UTL_SetVariableDataChar( VariableHandle arg1, char * arg2)
{
	MCI_LIST[24] = "UTL_SetVariableDataChar";
	START_LAPTIMER(24);
	UTL_SetVariableDataChar( arg1, arg2);
	STOP_LAPTIMER(24);
}
void _UTL_SetVariableDataCheckButton( VariableHandle arg1, CheckButton arg2)
{
	MCI_LIST[25] = "UTL_SetVariableDataCheckButton";
	START_LAPTIMER(25);
	UTL_SetVariableDataCheckButton( arg1, arg2);
	STOP_LAPTIMER(25);
}
void _UTL_SetVariableDataSlider( VariableHandle arg1, Slider arg2)
{
	MCI_LIST[26] = "UTL_SetVariableDataSlider";
	START_LAPTIMER(26);
	UTL_SetVariableDataSlider( arg1, arg2);
	STOP_LAPTIMER(26);
}
void _UTL_SetVariableDataUSlider( VariableHandle arg1, USlider arg2)
{
	MCI_LIST[27] = "UTL_SetVariableDataUSlider";
	START_LAPTIMER(27);
	UTL_SetVariableDataUSlider( arg1, arg2);
	STOP_LAPTIMER(27);
}
void _UTL_SendVariable( VariableHandle arg1, char * arg2)
{
	MCI_LIST[28] = "UTL_SendVariable";
	START_LAPTIMER(28);
	UTL_SendVariable( arg1, arg2);
	STOP_LAPTIMER(28);
}
void _UTL_UpdateVariable( VariableHandle arg1, char * arg2)
{
	MCI_LIST[29] = "UTL_UpdateVariable";
	START_LAPTIMER(29);
	UTL_UpdateVariable( arg1, arg2);
	STOP_LAPTIMER(29);
}
int _UTL_GetVariableStation( VariableHandle arg1, int * arg2)
{
	MCI_LIST[30] = "UTL_GetVariableStation";
	START_LAPTIMER(30);
	int retval = UTL_GetVariableStation( arg1, arg2);
	STOP_LAPTIMER(30);
	return retval;
}
int _UTL_GetVariableDataChar( VariableHandle arg1, char ** arg2)
{
	MCI_LIST[31] = "UTL_GetVariableDataChar";
	START_LAPTIMER(31);
	int retval = UTL_GetVariableDataChar( arg1, arg2);
	STOP_LAPTIMER(31);
	return retval;
}
int _UTL_GetVariableDataCheckButton( VariableHandle arg1, CheckButton * arg2)
{
	MCI_LIST[32] = "UTL_GetVariableDataCheckButton";
	START_LAPTIMER(32);
	int retval = UTL_GetVariableDataCheckButton( arg1, arg2);
	STOP_LAPTIMER(32);
	return retval;
}
int _UTL_GetVariableDataSlider( VariableHandle arg1, Slider * arg2)
{
	MCI_LIST[33] = "UTL_GetVariableDataSlider";
	START_LAPTIMER(33);
	int retval = UTL_GetVariableDataSlider( arg1, arg2);
	STOP_LAPTIMER(33);
	return retval;
}
int _UTL_GetVariableDataUSlider( VariableHandle arg1, USlider * arg2)
{
	MCI_LIST[34] = "UTL_GetVariableDataUSlider";
	START_LAPTIMER(34);
	int retval = UTL_GetVariableDataUSlider( arg1, arg2);
	STOP_LAPTIMER(34);
	return retval;
}
PinCursor _UTL_GetPinCursor( char * arg1)
{
	MCI_LIST[35] = "UTL_GetPinCursor";
	START_LAPTIMER(35);
	PinCursor retval = UTL_GetPinCursor( arg1);
	STOP_LAPTIMER(35);
	return retval;
}
UT_PIN _UTL_NextPin( PinCursor arg1)
{
	MCI_LIST[36] = "UTL_NextPin";
	START_LAPTIMER(36);
	UT_PIN retval = UTL_NextPin( arg1);
	STOP_LAPTIMER(36);
	return retval;
}
DutCursor _UTL_GetDutCursor( RadioButton arg1)
{
	MCI_LIST[37] = "UTL_GetDutCursor";
	START_LAPTIMER(37);
	DutCursor retval = UTL_GetDutCursor( arg1);
	STOP_LAPTIMER(37);
	return retval;
}
UT_DUT _UTL_NextDut( DutCursor arg1)
{
	MCI_LIST[38] = "UTL_NextDut";
	START_LAPTIMER(38);
	UT_DUT retval = UTL_NextDut( arg1);
	STOP_LAPTIMER(38);
	return retval;
}
USlider _UTL_GetDutCount( RadioButton arg1)
{
	MCI_LIST[39] = "UTL_GetDutCount";
	START_LAPTIMER(39);
	USlider retval = UTL_GetDutCount( arg1);
	STOP_LAPTIMER(39);
	return retval;
}
int _UTL_ConvertDutNumber( RadioButton arg1, UT_DUT arg2, RadioButton arg3, int * arg4, UT_DUT * arg5)
{
	MCI_LIST[40] = "UTL_ConvertDutNumber";
	START_LAPTIMER(40);
	int retval = UTL_ConvertDutNumber( arg1, arg2, arg3, arg4, arg5);
	STOP_LAPTIMER(40);
	return retval;
}
void _UTL_ConfirmSystemDut( RadioButton arg1)
{
	MCI_LIST[41] = "UTL_ConfirmSystemDut";
	START_LAPTIMER(41);
	UTL_ConfirmSystemDut( arg1);
	STOP_LAPTIMER(41);
}
RadioButton _UTL_NextSignal( SignalCursor arg1)
{
	MCI_LIST[42] = "UTL_NextSignal";
	START_LAPTIMER(42);
	RadioButton retval = UTL_NextSignal( arg1);
	STOP_LAPTIMER(42);
	return retval;
}
void _UTL_StartTimer( RadioButton arg1)
{
	MCI_LIST[43] = "UTL_StartTimer";
	START_LAPTIMER(43);
	UTL_StartTimer( arg1);
	STOP_LAPTIMER(43);
}
DSlider _UTL_ReadTimer( CheckButton * arg1)
{
	MCI_LIST[44] = "UTL_ReadTimer";
	START_LAPTIMER(44);
	DSlider retval = UTL_ReadTimer( arg1);
	STOP_LAPTIMER(44);
	return retval;
}
void _UTL_WaitTime( DSlider arg1)
{
	MCI_LIST[45] = "UTL_WaitTime";
	START_LAPTIMER(45);
	UTL_WaitTime( arg1);
	STOP_LAPTIMER(45);
}
void _UTL_Stop()
{
	MCI_LIST[46] = "UTL_Stop";
	START_LAPTIMER(46);
	UTL_Stop();
	STOP_LAPTIMER(46);
}
RadioButton _UTL_ReadSiteNumber()
{
	MCI_LIST[47] = "UTL_ReadSiteNumber";
	START_LAPTIMER(47);
	RadioButton retval = UTL_ReadSiteNumber();
	STOP_LAPTIMER(47);
	return retval;
}
void _UTL_SendSocketConditionByFile( char * arg1)
{
	MCI_LIST[48] = "UTL_SendSocketConditionByFile";
	START_LAPTIMER(48);
	UTL_SendSocketConditionByFile( arg1);
	STOP_LAPTIMER(48);
}
void _UTL_SetRejectionByDutBit( USlider * arg1, USlider arg2, CheckButton arg3)
{
	MCI_LIST[49] = "UTL_SetRejectionByDutBit";
	START_LAPTIMER(49);
	UTL_SetRejectionByDutBit( arg1, arg2, arg3);
	STOP_LAPTIMER(49);
}
void _UTL_SetResetExclusionByDutBit( USlider * arg1, USlider arg2, CheckButton arg3, CheckButton arg4)
{
	MCI_LIST[50] = "UTL_SetResetExclusionByDutBit";
	START_LAPTIMER(50);
	UTL_SetResetExclusionByDutBit( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(50);
}
CheckButton _UTL_SetRejection( UT_DUT arg1, CheckButton arg2)
{
	MCI_LIST[51] = "UTL_SetRejection";
	START_LAPTIMER(51);
	CheckButton retval = UTL_SetRejection( arg1, arg2);
	STOP_LAPTIMER(51);
	return retval;
}
CheckButton _UTL_SetExclusion( UT_DUT arg1, CheckButton arg2, CheckButton arg3)
{
	MCI_LIST[52] = "UTL_SetExclusion";
	START_LAPTIMER(52);
	CheckButton retval = UTL_SetExclusion( arg1, arg2, arg3);
	STOP_LAPTIMER(52);
	return retval;
}
CheckButton _UTL_ResetExclusion( UT_DUT arg1)
{
	MCI_LIST[53] = "UTL_ResetExclusion";
	START_LAPTIMER(53);
	CheckButton retval = UTL_ResetExclusion( arg1);
	STOP_LAPTIMER(53);
	return retval;
}
RejectionHandle _UTL_GetRejectionHandle()
{
	MCI_LIST[54] = "UTL_GetRejectionHandle";
	START_LAPTIMER(54);
	RejectionHandle retval = UTL_GetRejectionHandle();
	STOP_LAPTIMER(54);
	return retval;
}
void _UTL_ClearRejectionDut( RejectionHandle arg1)
{
	MCI_LIST[55] = "UTL_ClearRejectionDut";
	START_LAPTIMER(55);
	UTL_ClearRejectionDut( arg1);
	STOP_LAPTIMER(55);
}
void _UTL_AddRejectionDut( RejectionHandle arg1, UT_DUT arg2)
{
	MCI_LIST[56] = "UTL_AddRejectionDut";
	START_LAPTIMER(56);
	UTL_AddRejectionDut( arg1, arg2);
	STOP_LAPTIMER(56);
}
void _UTL_SetRejectionIgnoreWet( RejectionHandle arg1, CheckButton arg2)
{
	MCI_LIST[57] = "UTL_SetRejectionIgnoreWet";
	START_LAPTIMER(57);
	UTL_SetRejectionIgnoreWet( arg1, arg2);
	STOP_LAPTIMER(57);
}
void _UTL_SendRejection( RejectionHandle arg1)
{
	MCI_LIST[58] = "UTL_SendRejection";
	START_LAPTIMER(58);
	UTL_SendRejection( arg1);
	STOP_LAPTIMER(58);
}
int _UTL_GetRejectionIgnoreWet( RejectionHandle arg1, CheckButton * arg2)
{
	MCI_LIST[59] = "UTL_GetRejectionIgnoreWet";
	START_LAPTIMER(59);
	int retval = UTL_GetRejectionIgnoreWet( arg1, arg2);
	STOP_LAPTIMER(59);
	return retval;
}
ExclusionHandle _UTL_GetExclusionHandle()
{
	MCI_LIST[60] = "UTL_GetExclusionHandle";
	START_LAPTIMER(60);
	ExclusionHandle retval = UTL_GetExclusionHandle();
	STOP_LAPTIMER(60);
	return retval;
}
void _UTL_ClearExclusionDut( ExclusionHandle arg1)
{
	MCI_LIST[61] = "UTL_ClearExclusionDut";
	START_LAPTIMER(61);
	UTL_ClearExclusionDut( arg1);
	STOP_LAPTIMER(61);
}
void _UTL_AddExclusionDut( ExclusionHandle arg1, UT_DUT arg2)
{
	MCI_LIST[62] = "UTL_AddExclusionDut";
	START_LAPTIMER(62);
	UTL_AddExclusionDut( arg1, arg2);
	STOP_LAPTIMER(62);
}
void _UTL_SetExclusionIgnoreWet( ExclusionHandle arg1, CheckButton arg2)
{
	MCI_LIST[63] = "UTL_SetExclusionIgnoreWet";
	START_LAPTIMER(63);
	UTL_SetExclusionIgnoreWet( arg1, arg2);
	STOP_LAPTIMER(63);
}
void _UTL_SetExclusionMask( ExclusionHandle arg1, CheckButton arg2)
{
	MCI_LIST[64] = "UTL_SetExclusionMask";
	START_LAPTIMER(64);
	UTL_SetExclusionMask( arg1, arg2);
	STOP_LAPTIMER(64);
}
void _UTL_SetExclusionSetOrReset( ExclusionHandle arg1, CheckButton arg2)
{
	MCI_LIST[65] = "UTL_SetExclusionSetOrReset";
	START_LAPTIMER(65);
	UTL_SetExclusionSetOrReset( arg1, arg2);
	STOP_LAPTIMER(65);
}
void _UTL_SendExclusion( ExclusionHandle arg1)
{
	MCI_LIST[66] = "UTL_SendExclusion";
	START_LAPTIMER(66);
	UTL_SendExclusion( arg1);
	STOP_LAPTIMER(66);
}
int _UTL_GetExclusionIgnoreWet( ExclusionHandle arg1, CheckButton * arg2)
{
	MCI_LIST[67] = "UTL_GetExclusionIgnoreWet";
	START_LAPTIMER(67);
	int retval = UTL_GetExclusionIgnoreWet( arg1, arg2);
	STOP_LAPTIMER(67);
	return retval;
}
int _UTL_GetExclusionMask( ExclusionHandle arg1, CheckButton * arg2)
{
	MCI_LIST[68] = "UTL_GetExclusionMask";
	START_LAPTIMER(68);
	int retval = UTL_GetExclusionMask( arg1, arg2);
	STOP_LAPTIMER(68);
	return retval;
}
int _UTL_GetExclusionSetOrReset( ExclusionHandle arg1, CheckButton * arg2)
{
	MCI_LIST[69] = "UTL_GetExclusionSetOrReset";
	START_LAPTIMER(69);
	int retval = UTL_GetExclusionSetOrReset( arg1, arg2);
	STOP_LAPTIMER(69);
	return retval;
}
Slider _UTL_ReadDutXLocation( UT_DUT arg1)
{
	MCI_LIST[70] = "UTL_ReadDutXLocation";
	START_LAPTIMER(70);
	Slider retval = UTL_ReadDutXLocation( arg1);
	STOP_LAPTIMER(70);
	return retval;
}
Slider _UTL_ReadDutYLocation( UT_DUT arg1)
{
	MCI_LIST[71] = "UTL_ReadDutYLocation";
	START_LAPTIMER(71);
	Slider retval = UTL_ReadDutYLocation( arg1);
	STOP_LAPTIMER(71);
	return retval;
}
void _UTL_DeleteHandle( int arg1)
{
	MCI_LIST[72] = "UTL_DeleteHandle";
	START_LAPTIMER(72);
	UTL_DeleteHandle( arg1);
	STOP_LAPTIMER(72);
}
void _UTL_DeleteCursor( int arg1)
{
	MCI_LIST[73] = "UTL_DeleteCursor";
	START_LAPTIMER(73);
	UTL_DeleteCursor( arg1);
	STOP_LAPTIMER(73);
}
void _UTL_SendStrToWFMP( UT_DUT arg1, char * arg2, char * arg3)
{
	MCI_LIST[74] = "UTL_SendStrToWFMP";
	START_LAPTIMER(74);
	UTL_SendStrToWFMP( arg1, arg2, arg3);
	STOP_LAPTIMER(74);
}
RadioButton _UTL_ReadStationNumber()
{
	MCI_LIST[75] = "UTL_ReadStationNumber";
	START_LAPTIMER(75);
	RadioButton retval = UTL_ReadStationNumber();
	STOP_LAPTIMER(75);
	return retval;
}
CheckButton _UTL_ReadFirstFlag()
{
	MCI_LIST[76] = "UTL_ReadFirstFlag";
	START_LAPTIMER(76);
	CheckButton retval = UTL_ReadFirstFlag();
	STOP_LAPTIMER(76);
	return retval;
}
PbidHandle _UTL_GetPbidHandle()
{
	MCI_LIST[77] = "UTL_GetPbidHandle";
	START_LAPTIMER(77);
	PbidHandle retval = UTL_GetPbidHandle();
	STOP_LAPTIMER(77);
	return retval;
}
void _UTL_SetPbidStationNumber( PbidHandle arg1, RadioButton arg2)
{
	MCI_LIST[78] = "UTL_SetPbidStationNumber";
	START_LAPTIMER(78);
	UTL_SetPbidStationNumber( arg1, arg2);
	STOP_LAPTIMER(78);
}
int _UTL_GetPbidStationNumber( PbidHandle arg1, RadioButton * arg2)
{
	MCI_LIST[79] = "UTL_GetPbidStationNumber";
	START_LAPTIMER(79);
	int retval = UTL_GetPbidStationNumber( arg1, arg2);
	STOP_LAPTIMER(79);
	return retval;
}
void _UTL_SetPbidMbNumber( PbidHandle arg1, RadioButton arg2)
{
	MCI_LIST[80] = "UTL_SetPbidMbNumber";
	START_LAPTIMER(80);
	UTL_SetPbidMbNumber( arg1, arg2);
	STOP_LAPTIMER(80);
}
int _UTL_GetPbidMbNumber( PbidHandle arg1, RadioButton * arg2)
{
	MCI_LIST[81] = "UTL_GetPbidMbNumber";
	START_LAPTIMER(81);
	int retval = UTL_GetPbidMbNumber( arg1, arg2);
	STOP_LAPTIMER(81);
	return retval;
}
void _UTL_SetPbidPbNumber( PbidHandle arg1, RadioButton arg2)
{
	MCI_LIST[82] = "UTL_SetPbidPbNumber";
	START_LAPTIMER(82);
	UTL_SetPbidPbNumber( arg1, arg2);
	STOP_LAPTIMER(82);
}
int _UTL_GetPbidPbNumber( PbidHandle arg1, RadioButton * arg2)
{
	MCI_LIST[83] = "UTL_GetPbidPbNumber";
	START_LAPTIMER(83);
	int retval = UTL_GetPbidPbNumber( arg1, arg2);
	STOP_LAPTIMER(83);
	return retval;
}
USlider _UTL_ReadPbid( PbidHandle arg1)
{
	MCI_LIST[84] = "UTL_ReadPbid";
	START_LAPTIMER(84);
	USlider retval = UTL_ReadPbid( arg1);
	STOP_LAPTIMER(84);
	return retval;
}
PbTypeHandle _UTL_GetPbTypeHandle()
{
	MCI_LIST[85] = "UTL_GetPbTypeHandle";
	START_LAPTIMER(85);
	PbTypeHandle retval = UTL_GetPbTypeHandle();
	STOP_LAPTIMER(85);
	return retval;
}
void _UTL_SetPbTypeStationNumber( PbTypeHandle arg1, RadioButton arg2)
{
	MCI_LIST[86] = "UTL_SetPbTypeStationNumber";
	START_LAPTIMER(86);
	UTL_SetPbTypeStationNumber( arg1, arg2);
	STOP_LAPTIMER(86);
}
int _UTL_GetPbTypeStationNumber( PbTypeHandle arg1, RadioButton * arg2)
{
	MCI_LIST[87] = "UTL_GetPbTypeStationNumber";
	START_LAPTIMER(87);
	int retval = UTL_GetPbTypeStationNumber( arg1, arg2);
	STOP_LAPTIMER(87);
	return retval;
}
void _UTL_SetPbTypeMbNumber( PbTypeHandle arg1, RadioButton arg2)
{
	MCI_LIST[88] = "UTL_SetPbTypeMbNumber";
	START_LAPTIMER(88);
	UTL_SetPbTypeMbNumber( arg1, arg2);
	STOP_LAPTIMER(88);
}
int _UTL_GetPbTypeMbNumber( PbTypeHandle arg1, RadioButton * arg2)
{
	MCI_LIST[89] = "UTL_GetPbTypeMbNumber";
	START_LAPTIMER(89);
	int retval = UTL_GetPbTypeMbNumber( arg1, arg2);
	STOP_LAPTIMER(89);
	return retval;
}
void _UTL_SetPbTypePbNumber( PbTypeHandle arg1, RadioButton arg2)
{
	MCI_LIST[90] = "UTL_SetPbTypePbNumber";
	START_LAPTIMER(90);
	UTL_SetPbTypePbNumber( arg1, arg2);
	STOP_LAPTIMER(90);
}
int _UTL_GetPbTypePbNumber( PbTypeHandle arg1, RadioButton * arg2)
{
	MCI_LIST[91] = "UTL_GetPbTypePbNumber";
	START_LAPTIMER(91);
	int retval = UTL_GetPbTypePbNumber( arg1, arg2);
	STOP_LAPTIMER(91);
	return retval;
}
USlider _UTL_ReadPbType( PbTypeHandle arg1)
{
	MCI_LIST[92] = "UTL_ReadPbType";
	START_LAPTIMER(92);
	USlider retval = UTL_ReadPbType( arg1);
	STOP_LAPTIMER(92);
	return retval;
}
HifixTypeHandle _UTL_GetHifixTypeHandle()
{
	MCI_LIST[93] = "UTL_GetHifixTypeHandle";
	START_LAPTIMER(93);
	HifixTypeHandle retval = UTL_GetHifixTypeHandle();
	STOP_LAPTIMER(93);
	return retval;
}
void _UTL_SetHifixTypeStationNumber( HifixTypeHandle arg1, RadioButton arg2)
{
	MCI_LIST[94] = "UTL_SetHifixTypeStationNumber";
	START_LAPTIMER(94);
	UTL_SetHifixTypeStationNumber( arg1, arg2);
	STOP_LAPTIMER(94);
}
int _UTL_GetHifixTypeStationNumber( HifixTypeHandle arg1, RadioButton * arg2)
{
	MCI_LIST[95] = "UTL_GetHifixTypeStationNumber";
	START_LAPTIMER(95);
	int retval = UTL_GetHifixTypeStationNumber( arg1, arg2);
	STOP_LAPTIMER(95);
	return retval;
}
int _UTL_GetHifixType( HifixTypeHandle arg1, RadioButton * arg2)
{
	MCI_LIST[96] = "UTL_GetHifixType";
	START_LAPTIMER(96);
	int retval = UTL_GetHifixType( arg1, arg2);
	STOP_LAPTIMER(96);
	return retval;
}
void _UTL_UpdateHifixType( HifixTypeHandle arg1)
{
	MCI_LIST[97] = "UTL_UpdateHifixType";
	START_LAPTIMER(97);
	UTL_UpdateHifixType( arg1);
	STOP_LAPTIMER(97);
}
USlider _UTL_ReadDutSampleNumber()
{
	MCI_LIST[98] = "UTL_ReadDutSampleNumber";
	START_LAPTIMER(98);
	USlider retval = UTL_ReadDutSampleNumber();
	STOP_LAPTIMER(98);
	return retval;
}
PinMaskHandle _UTL_GetPinMaskHandle()
{
	MCI_LIST[99] = "UTL_GetPinMaskHandle";
	START_LAPTIMER(99);
	PinMaskHandle retval = UTL_GetPinMaskHandle();
	STOP_LAPTIMER(99);
	return retval;
}
void _UTL_SetPinMaskKind( PinMaskHandle arg1, RadioButton arg2)
{
	MCI_LIST[100] = "UTL_SetPinMaskKind";
	START_LAPTIMER(100);
	UTL_SetPinMaskKind( arg1, arg2);
	STOP_LAPTIMER(100);
}
void _UTL_SetPinMask( PinMaskHandle arg1, CheckButton arg2)
{
	MCI_LIST[101] = "UTL_SetPinMask";
	START_LAPTIMER(101);
	UTL_SetPinMask( arg1, arg2);
	STOP_LAPTIMER(101);
}
void _UTL_AddPinMaskDut( PinMaskHandle arg1, UT_DUT arg2)
{
	MCI_LIST[102] = "UTL_AddPinMaskDut";
	START_LAPTIMER(102);
	UTL_AddPinMaskDut( arg1, arg2);
	STOP_LAPTIMER(102);
}
void _UTL_ClearPinMaskDut( PinMaskHandle arg1)
{
	MCI_LIST[103] = "UTL_ClearPinMaskDut";
	START_LAPTIMER(103);
	UTL_ClearPinMaskDut( arg1);
	STOP_LAPTIMER(103);
}
void _UTL_SendPinMask( PinMaskHandle arg1, char * arg2)
{
	MCI_LIST[104] = "UTL_SendPinMask";
	START_LAPTIMER(104);
	UTL_SendPinMask( arg1, arg2);
	STOP_LAPTIMER(104);
}
void _UTL_RuntimeError( UT_ErrorInfo arg1)
{
	MCI_LIST[105] = "UTL_RuntimeError";
	START_LAPTIMER(105);
	UTL_RuntimeError( arg1);
	STOP_LAPTIMER(105);
}
void _UTL_SetNoRejectionVs( RadioButton arg1)
{
	MCI_LIST[106] = "UTL_SetNoRejectionVs";
	START_LAPTIMER(106);
	UTL_SetNoRejectionVs( arg1);
	STOP_LAPTIMER(106);
}
void _UTL_ResetNoRejectionVs( RadioButton arg1)
{
	MCI_LIST[107] = "UTL_ResetNoRejectionVs";
	START_LAPTIMER(107);
	UTL_ResetNoRejectionVs( arg1);
	STOP_LAPTIMER(107);
}
IlModeHandle _UTL_GetIlModeHandle()
{
	MCI_LIST[108] = "UTL_GetIlModeHandle";
	START_LAPTIMER(108);
	IlModeHandle retval = UTL_GetIlModeHandle();
	STOP_LAPTIMER(108);
	return retval;
}
void _UTL_SetIlMode( IlModeHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[109] = "UTL_SetIlMode";
	START_LAPTIMER(109);
	UTL_SetIlMode( arg1, arg2);
	STOP_LAPTIMER(109);
}
int _UTL_GetIlMode( IlModeHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[110] = "UTL_GetIlMode";
	START_LAPTIMER(110);
	int retval = UTL_GetIlMode( arg1, arg2);
	STOP_LAPTIMER(110);
	return retval;
}
void _UTL_SendIlMode( IlModeHandle  arg1)
{
	MCI_LIST[111] = "UTL_SendIlMode";
	START_LAPTIMER(111);
	UTL_SendIlMode( arg1);
	STOP_LAPTIMER(111);
}
void _UTL_UpdateIlMode( IlModeHandle  arg1)
{
	MCI_LIST[112] = "UTL_UpdateIlMode";
	START_LAPTIMER(112);
	UTL_UpdateIlMode( arg1);
	STOP_LAPTIMER(112);
}
ComparisonModeHandle _UTL_GetComparisonModeHandle()
{
	MCI_LIST[113] = "UTL_GetComparisonModeHandle";
	START_LAPTIMER(113);
	ComparisonModeHandle retval = UTL_GetComparisonModeHandle();
	STOP_LAPTIMER(113);
	return retval;
}
void _UTL_SetComparisonMode( ComparisonModeHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[114] = "UTL_SetComparisonMode";
	START_LAPTIMER(114);
	UTL_SetComparisonMode( arg1, arg2);
	STOP_LAPTIMER(114);
}
int _UTL_GetComparisonMode( ComparisonModeHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[115] = "UTL_GetComparisonMode";
	START_LAPTIMER(115);
	int retval = UTL_GetComparisonMode( arg1, arg2);
	STOP_LAPTIMER(115);
	return retval;
}
void _UTL_SendComparisonMode( ComparisonModeHandle  arg1)
{
	MCI_LIST[116] = "UTL_SendComparisonMode";
	START_LAPTIMER(116);
	UTL_SendComparisonMode( arg1);
	STOP_LAPTIMER(116);
}
void _UTL_UpdateComparisonMode( ComparisonModeHandle  arg1)
{
	MCI_LIST[117] = "UTL_UpdateComparisonMode";
	START_LAPTIMER(117);
	UTL_UpdateComparisonMode( arg1);
	STOP_LAPTIMER(117);
}
char * _UTL_ReadProgramName()
{
	MCI_LIST[118] = "UTL_ReadProgramName";
	START_LAPTIMER(118);
	char * retval = UTL_ReadProgramName();
	STOP_LAPTIMER(118);
	return retval;
}
char * _UTL_ReadSocketProgramName()
{
	MCI_LIST[119] = "UTL_ReadSocketProgramName";
	START_LAPTIMER(119);
	char * retval = UTL_ReadSocketProgramName();
	STOP_LAPTIMER(119);
	return retval;
}
char * _UTL_ReadTestName()
{
	MCI_LIST[120] = "UTL_ReadTestName";
	START_LAPTIMER(120);
	char * retval = UTL_ReadTestName();
	STOP_LAPTIMER(120);
	return retval;
}
TargetSwitchHandle _UTL_GetTargetSwitchHandle()
{
	MCI_LIST[121] = "UTL_GetTargetSwitchHandle";
	START_LAPTIMER(121);
	TargetSwitchHandle retval = UTL_GetTargetSwitchHandle();
	STOP_LAPTIMER(121);
	return retval;
}
void _UTL_SetTargetSwitchIOShareCount( TargetSwitchHandle arg1, USlider arg2)
{
	MCI_LIST[122] = "UTL_SetTargetSwitchIOShareCount";
	START_LAPTIMER(122);
	UTL_SetTargetSwitchIOShareCount( arg1, arg2);
	STOP_LAPTIMER(122);
}
int _UTL_GetTargetSwitchIOShareCount( TargetSwitchHandle arg1, USlider * arg2)
{
	MCI_LIST[123] = "UTL_GetTargetSwitchIOShareCount";
	START_LAPTIMER(123);
	int retval = UTL_GetTargetSwitchIOShareCount( arg1, arg2);
	STOP_LAPTIMER(123);
	return retval;
}
void _UTL_SetTargetSwitchIOShareSignal( TargetSwitchHandle arg1, UT_DUT arg2, RadioButton arg3)
{
	MCI_LIST[124] = "UTL_SetTargetSwitchIOShareSignal";
	START_LAPTIMER(124);
	UTL_SetTargetSwitchIOShareSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(124);
}
int _UTL_GetTargetSwitchIOShareSignal( TargetSwitchHandle arg1, UT_DUT arg2, RadioButton * arg3)
{
	MCI_LIST[125] = "UTL_GetTargetSwitchIOShareSignal";
	START_LAPTIMER(125);
	int retval = UTL_GetTargetSwitchIOShareSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(125);
	return retval;
}
void _UTL_SetTargetSwitchMultiBankCount( TargetSwitchHandle arg1, USlider arg2)
{
	MCI_LIST[126] = "UTL_SetTargetSwitchMultiBankCount";
	START_LAPTIMER(126);
	UTL_SetTargetSwitchMultiBankCount( arg1, arg2);
	STOP_LAPTIMER(126);
}
int _UTL_GetTargetSwitchMultiBankCount( TargetSwitchHandle arg1, USlider * arg2)
{
	MCI_LIST[127] = "UTL_GetTargetSwitchMultiBankCount";
	START_LAPTIMER(127);
	int retval = UTL_GetTargetSwitchMultiBankCount( arg1, arg2);
	STOP_LAPTIMER(127);
	return retval;
}
void _UTL_SetTargetSwitchMultiBankSignal( TargetSwitchHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[128] = "UTL_SetTargetSwitchMultiBankSignal";
	START_LAPTIMER(128);
	UTL_SetTargetSwitchMultiBankSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(128);
}
int _UTL_GetTargetSwitchMultiBankSignal( TargetSwitchHandle arg1, RadioButton arg2, RadioButton * arg3)
{
	MCI_LIST[129] = "UTL_GetTargetSwitchMultiBankSignal";
	START_LAPTIMER(129);
	int retval = UTL_GetTargetSwitchMultiBankSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(129);
	return retval;
}
void _UTL_SendTargetSwitch( TargetSwitchHandle arg1)
{
	MCI_LIST[130] = "UTL_SendTargetSwitch";
	START_LAPTIMER(130);
	UTL_SendTargetSwitch( arg1);
	STOP_LAPTIMER(130);
}
void _UTL_UpdateTargetSwitch( TargetSwitchHandle arg1)
{
	MCI_LIST[131] = "UTL_UpdateTargetSwitch";
	START_LAPTIMER(131);
	UTL_UpdateTargetSwitch( arg1);
	STOP_LAPTIMER(131);
}
DutGroupHandle _UTL_GetDutGroupHandle()
{
	MCI_LIST[132] = "UTL_GetDutGroupHandle";
	START_LAPTIMER(132);
	DutGroupHandle retval = UTL_GetDutGroupHandle();
	STOP_LAPTIMER(132);
	return retval;
}
void _UTL_ClearDutGroupTargetDut( DutGroupHandle arg1)
{
	MCI_LIST[133] = "UTL_ClearDutGroupTargetDut";
	START_LAPTIMER(133);
	UTL_ClearDutGroupTargetDut( arg1);
	STOP_LAPTIMER(133);
}
void _UTL_AddDutGroupTargetDut( DutGroupHandle arg1, UT_DUT arg2, CheckButton arg3)
{
	MCI_LIST[134] = "UTL_AddDutGroupTargetDut";
	START_LAPTIMER(134);
	UTL_AddDutGroupTargetDut( arg1, arg2, arg3);
	STOP_LAPTIMER(134);
}
void _UTL_SendDutGroup( DutGroupHandle arg1, RadioButton arg2)
{
	MCI_LIST[135] = "UTL_SendDutGroup";
	START_LAPTIMER(135);
	UTL_SendDutGroup( arg1, arg2);
	STOP_LAPTIMER(135);
}
VsMaskHandle _UTL_GetVsMaskHandle()
{
	MCI_LIST[136] = "UTL_GetVsMaskHandle";
	START_LAPTIMER(136);
	VsMaskHandle retval = UTL_GetVsMaskHandle();
	STOP_LAPTIMER(136);
	return retval;
}
void _UTL_AddVsMaskDutVsMask( VsMaskHandle arg1, UT_DUT arg2, RadioButton arg3, CheckButton arg4)
{
	MCI_LIST[137] = "UTL_AddVsMaskDutVsMask";
	START_LAPTIMER(137);
	UTL_AddVsMaskDutVsMask( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(137);
}
void _UTL_ClearVsMaskDutVsMask( VsMaskHandle arg1)
{
	MCI_LIST[138] = "UTL_ClearVsMaskDutVsMask";
	START_LAPTIMER(138);
	UTL_ClearVsMaskDutVsMask( arg1);
	STOP_LAPTIMER(138);
}
void _UTL_SendVsMask( VsMaskHandle arg1)
{
	MCI_LIST[139] = "UTL_SendVsMask";
	START_LAPTIMER(139);
	UTL_SendVsMask( arg1);
	STOP_LAPTIMER(139);
}
void _UTL_ReadDutBit( RadioButton arg1, USlider * arg2, USlider arg3)
{
	MCI_LIST[140] = "UTL_ReadDutBit";
	START_LAPTIMER(140);
	UTL_ReadDutBit( arg1, arg2, arg3);
	STOP_LAPTIMER(140);
}
void _UTL_SetDutBit( RadioButton arg1, USlider * arg2, USlider arg3)
{
	MCI_LIST[141] = "UTL_SetDutBit";
	START_LAPTIMER(141);
	UTL_SetDutBit( arg1, arg2, arg3);
	STOP_LAPTIMER(141);
}
PinHandle _UTL_GetPinHandle()
{
	MCI_LIST[142] = "UTL_GetPinHandle";
	START_LAPTIMER(142);
	PinHandle retval = UTL_GetPinHandle();
	STOP_LAPTIMER(142);
	return retval;
}
void _UTL_InitializePinHandle( PinHandle arg1)
{
	MCI_LIST[143] = "UTL_InitializePinHandle";
	START_LAPTIMER(143);
	UTL_InitializePinHandle( arg1);
	STOP_LAPTIMER(143);
}
void _UTL_SetPinSendMode( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[144] = "UTL_SetPinSendMode";
	START_LAPTIMER(144);
	UTL_SetPinSendMode( arg1, arg2);
	STOP_LAPTIMER(144);
}
void _UTL_AddPinTargetDut( PinHandle arg1, UT_DUT arg2)
{
	MCI_LIST[145] = "UTL_AddPinTargetDut";
	START_LAPTIMER(145);
	UTL_AddPinTargetDut( arg1, arg2);
	STOP_LAPTIMER(145);
}
void _UTL_ClearPinTargetDut( PinHandle arg1)
{
	MCI_LIST[146] = "UTL_ClearPinTargetDut";
	START_LAPTIMER(146);
	UTL_ClearPinTargetDut( arg1);
	STOP_LAPTIMER(146);
}
void _UTL_SetPinTargetDutCondition( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[147] = "UTL_SetPinTargetDutCondition";
	START_LAPTIMER(147);
	UTL_SetPinTargetDutCondition( arg1, arg2);
	STOP_LAPTIMER(147);
}
void _UTL_SetPinViNumber( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[148] = "UTL_SetPinViNumber";
	START_LAPTIMER(148);
	UTL_SetPinViNumber( arg1, arg2);
	STOP_LAPTIMER(148);
}
void _UTL_SetPinVihhNumber( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[149] = "UTL_SetPinVihhNumber";
	START_LAPTIMER(149);
	UTL_SetPinVihhNumber( arg1, arg2);
	STOP_LAPTIMER(149);
}
void _UTL_SetPinVihhMutSignal( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[150] = "UTL_SetPinVihhMutSignal";
	START_LAPTIMER(150);
	UTL_SetPinVihhMutSignal( arg1, arg2);
	STOP_LAPTIMER(150);
}
void _UTL_SetPinDrWaveform( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[151] = "UTL_SetPinDrWaveform";
	START_LAPTIMER(151);
	UTL_SetPinDrWaveform( arg1, arg2);
	STOP_LAPTIMER(151);
}
void _UTL_SetPinDrClock( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[152] = "UTL_SetPinDrClock";
	START_LAPTIMER(152);
	UTL_SetPinDrClock( arg1, arg2, arg3);
	STOP_LAPTIMER(152);
}
void _UTL_SetPinInit( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[153] = "UTL_SetPinInit";
	START_LAPTIMER(153);
	UTL_SetPinInit( arg1, arg2);
	STOP_LAPTIMER(153);
}
void _UTL_SetPinHvDr( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[154] = "UTL_SetPinHvDr";
	START_LAPTIMER(154);
	UTL_SetPinHvDr( arg1, arg2);
	STOP_LAPTIMER(154);
}
void _UTL_SetPinHvLvDr( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[155] = "UTL_SetPinHvLvDr";
	START_LAPTIMER(155);
	UTL_SetPinHvLvDr( arg1, arg2);
	STOP_LAPTIMER(155);
}
void _UTL_SetPinDbmPinPattern( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[156] = "UTL_SetPinDbmPinPattern";
	START_LAPTIMER(156);
	UTL_SetPinDbmPinPattern( arg1, arg2);
	STOP_LAPTIMER(156);
}
void _UTL_SetPinDrzPulseWidth( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[157] = "UTL_SetPinDrzPulseWidth";
	START_LAPTIMER(157);
	UTL_SetPinDrzPulseWidth( arg1, arg2);
	STOP_LAPTIMER(157);
}
void _UTL_SetPinDreOffTermMode( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[158] = "UTL_SetPinDreOffTermMode";
	START_LAPTIMER(158);
	UTL_SetPinDreOffTermMode( arg1, arg2);
	STOP_LAPTIMER(158);
}
void _UTL_SetPinDrPort( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[159] = "UTL_SetPinDrPort";
	START_LAPTIMER(159);
	UTL_SetPinDrPort( arg1, arg2);
	STOP_LAPTIMER(159);
}
void _UTL_AddPinWfs( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[160] = "UTL_AddPinWfs";
	START_LAPTIMER(160);
	UTL_AddPinWfs( arg1, arg2, arg3);
	STOP_LAPTIMER(160);
}
void _UTL_ClearPinWfs( PinHandle arg1)
{
	MCI_LIST[161] = "UTL_ClearPinWfs";
	START_LAPTIMER(161);
	UTL_ClearPinWfs( arg1);
	STOP_LAPTIMER(161);
}
void _UTL_SetPinVoNumber( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[162] = "UTL_SetPinVoNumber";
	START_LAPTIMER(162);
	UTL_SetPinVoNumber( arg1, arg2);
	STOP_LAPTIMER(162);
}
void _UTL_SetPinVodNumber( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[163] = "UTL_SetPinVodNumber";
	START_LAPTIMER(163);
	UTL_SetPinVodNumber( arg1, arg2);
	STOP_LAPTIMER(163);
}
void _UTL_AddPinStrbCpeNumber( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[164] = "UTL_AddPinStrbCpeNumber";
	START_LAPTIMER(164);
	UTL_AddPinStrbCpeNumber( arg1, arg2, arg3);
	STOP_LAPTIMER(164);
}
void _UTL_ClearPinStrbCpeNumber( PinHandle arg1)
{
	MCI_LIST[165] = "UTL_ClearPinStrbCpeNumber";
	START_LAPTIMER(165);
	UTL_ClearPinStrbCpeNumber( arg1);
	STOP_LAPTIMER(165);
}
void _UTL_AddPinWstrbCpeNumber( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[166] = "UTL_AddPinWstrbCpeNumber";
	START_LAPTIMER(166);
	UTL_AddPinWstrbCpeNumber( arg1, arg2, arg3);
	STOP_LAPTIMER(166);
}
void _UTL_ClearPinWstrbCpeNumber( PinHandle arg1)
{
	MCI_LIST[167] = "UTL_ClearPinWstrbCpeNumber";
	START_LAPTIMER(167);
	UTL_ClearPinWstrbCpeNumber( arg1);
	STOP_LAPTIMER(167);
}
void _UTL_SetPinEinv( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[168] = "UTL_SetPinEinv";
	START_LAPTIMER(168);
	UTL_SetPinEinv( arg1, arg2);
	STOP_LAPTIMER(168);
}
void _UTL_SetPinMatchMode( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[169] = "UTL_SetPinMatchMode";
	START_LAPTIMER(169);
	UTL_SetPinMatchMode( arg1, arg2);
	STOP_LAPTIMER(169);
}
void _UTL_SetPinMatchGroup( PinHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[170] = "UTL_SetPinMatchGroup";
	START_LAPTIMER(170);
	UTL_SetPinMatchGroup( arg1, arg2, arg3);
	STOP_LAPTIMER(170);
}
void _UTL_AddPinHz( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[171] = "UTL_AddPinHz";
	START_LAPTIMER(171);
	UTL_AddPinHz( arg1, arg2);
	STOP_LAPTIMER(171);
}
void _UTL_ClearPinHz( PinHandle arg1)
{
	MCI_LIST[172] = "UTL_ClearPinHz";
	START_LAPTIMER(172);
	UTL_ClearPinHz( arg1);
	STOP_LAPTIMER(172);
}
void _UTL_AddPinRhz( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[173] = "UTL_AddPinRhz";
	START_LAPTIMER(173);
	UTL_AddPinRhz( arg1, arg2, arg3);
	STOP_LAPTIMER(173);
}
void _UTL_ClearPinRhz( PinHandle arg1)
{
	MCI_LIST[174] = "UTL_ClearPinRhz";
	START_LAPTIMER(174);
	UTL_ClearPinRhz( arg1);
	STOP_LAPTIMER(174);
}
void _UTL_AddPinExpStrbNumber( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[175] = "UTL_AddPinExpStrbNumber";
	START_LAPTIMER(175);
	UTL_AddPinExpStrbNumber( arg1, arg2, arg3);
	STOP_LAPTIMER(175);
}
void _UTL_ClearPinExpStrbNumber( PinHandle arg1)
{
	MCI_LIST[176] = "UTL_ClearPinExpStrbNumber";
	START_LAPTIMER(176);
	UTL_ClearPinExpStrbNumber( arg1);
	STOP_LAPTIMER(176);
}
void _UTL_AddPinExpWstrbNumber( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[177] = "UTL_AddPinExpWstrbNumber";
	START_LAPTIMER(177);
	UTL_AddPinExpWstrbNumber( arg1, arg2, arg3);
	STOP_LAPTIMER(177);
}
void _UTL_ClearPinExpWstrbNumber( PinHandle arg1)
{
	MCI_LIST[178] = "UTL_ClearPinExpWstrbNumber";
	START_LAPTIMER(178);
	UTL_ClearPinExpWstrbNumber( arg1);
	STOP_LAPTIMER(178);
}
void _UTL_AddPinEinvStrbNumber( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[179] = "UTL_AddPinEinvStrbNumber";
	START_LAPTIMER(179);
	UTL_AddPinEinvStrbNumber( arg1, arg2);
	STOP_LAPTIMER(179);
}
void _UTL_ClearPinEinvStrbNumber( PinHandle arg1)
{
	MCI_LIST[180] = "UTL_ClearPinEinvStrbNumber";
	START_LAPTIMER(180);
	UTL_ClearPinEinvStrbNumber( arg1);
	STOP_LAPTIMER(180);
}
void _UTL_AddPinEinvWstrbNumber( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[181] = "UTL_AddPinEinvWstrbNumber";
	START_LAPTIMER(181);
	UTL_AddPinEinvWstrbNumber( arg1, arg2);
	STOP_LAPTIMER(181);
}
void _UTL_ClearPinEinvWstrbNumber( PinHandle arg1)
{
	MCI_LIST[182] = "UTL_ClearPinEinvWstrbNumber";
	START_LAPTIMER(182);
	UTL_ClearPinEinvWstrbNumber( arg1);
	STOP_LAPTIMER(182);
}
void _UTL_AddPinStrbChannel( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[183] = "UTL_AddPinStrbChannel";
	START_LAPTIMER(183);
	UTL_AddPinStrbChannel( arg1, arg2, arg3);
	STOP_LAPTIMER(183);
}
void _UTL_ClearPinStrbChannel( PinHandle arg1)
{
	MCI_LIST[184] = "UTL_ClearPinStrbChannel";
	START_LAPTIMER(184);
	UTL_ClearPinStrbChannel( arg1);
	STOP_LAPTIMER(184);
}
void _UTL_AddPinStrbBank( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[185] = "UTL_AddPinStrbBank";
	START_LAPTIMER(185);
	UTL_AddPinStrbBank( arg1, arg2, arg3);
	STOP_LAPTIMER(185);
}
void _UTL_ClearPinStrbBank( PinHandle arg1)
{
	MCI_LIST[186] = "UTL_ClearPinStrbBank";
	START_LAPTIMER(186);
	UTL_ClearPinStrbBank( arg1);
	STOP_LAPTIMER(186);
}
void _UTL_AddPinStrbCpeMode( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[187] = "UTL_AddPinStrbCpeMode";
	START_LAPTIMER(187);
	UTL_AddPinStrbCpeMode( arg1, arg2, arg3);
	STOP_LAPTIMER(187);
}
void _UTL_ClearPinStrbCpeMode( PinHandle arg1)
{
	MCI_LIST[188] = "UTL_ClearPinStrbCpeMode";
	START_LAPTIMER(188);
	UTL_ClearPinStrbCpeMode( arg1);
	STOP_LAPTIMER(188);
}
void _UTL_AddPinWstrbCpeMode( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[189] = "UTL_AddPinWstrbCpeMode";
	START_LAPTIMER(189);
	UTL_AddPinWstrbCpeMode( arg1, arg2, arg3);
	STOP_LAPTIMER(189);
}
void _UTL_ClearPinWstrbCpeMode( PinHandle arg1)
{
	MCI_LIST[190] = "UTL_ClearPinWstrbCpeMode";
	START_LAPTIMER(190);
	UTL_ClearPinWstrbCpeMode( arg1);
	STOP_LAPTIMER(190);
}
void _UTL_SetPinIoCtrl( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[191] = "UTL_SetPinIoCtrl";
	START_LAPTIMER(191);
	UTL_SetPinIoCtrl( arg1, arg2);
	STOP_LAPTIMER(191);
}
void _UTL_SetPinDreNumber( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[192] = "UTL_SetPinDreNumber";
	START_LAPTIMER(192);
	UTL_SetPinDreNumber( arg1, arg2);
	STOP_LAPTIMER(192);
}
void _UTL_SetPinDreWaveform( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[193] = "UTL_SetPinDreWaveform";
	START_LAPTIMER(193);
	UTL_SetPinDreWaveform( arg1, arg2);
	STOP_LAPTIMER(193);
}
void _UTL_SetPinDreClock( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[194] = "UTL_SetPinDreClock";
	START_LAPTIMER(194);
	UTL_SetPinDreClock( arg1, arg2);
	STOP_LAPTIMER(194);
}
void _UTL_SetPinDronInit( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[195] = "UTL_SetPinDronInit";
	START_LAPTIMER(195);
	UTL_SetPinDronInit( arg1, arg2);
	STOP_LAPTIMER(195);
}
void _UTL_SetPinDbmPinDrePattern( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[196] = "UTL_SetPinDbmPinDrePattern";
	START_LAPTIMER(196);
	UTL_SetPinDbmPinDrePattern( arg1, arg2);
	STOP_LAPTIMER(196);
}
void _UTL_SetPinDreOffsetClock( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[197] = "UTL_SetPinDreOffsetClock";
	START_LAPTIMER(197);
	UTL_SetPinDreOffsetClock( arg1, arg2);
	STOP_LAPTIMER(197);
}
void _UTL_SetPinPdsSendMode( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[198] = "UTL_SetPinPdsSendMode";
	START_LAPTIMER(198);
	UTL_SetPinPdsSendMode( arg1, arg2);
	STOP_LAPTIMER(198);
}
void _UTL_AddPinPdsA( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[199] = "UTL_AddPinPdsA";
	START_LAPTIMER(199);
	UTL_AddPinPdsA( arg1, arg2, arg3);
	STOP_LAPTIMER(199);
}
void _UTL_ClearPinPdsA( PinHandle arg1)
{
	MCI_LIST[200] = "UTL_ClearPinPdsA";
	START_LAPTIMER(200);
	UTL_ClearPinPdsA( arg1);
	STOP_LAPTIMER(200);
}
void _UTL_AddPinPdsB( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[201] = "UTL_AddPinPdsB";
	START_LAPTIMER(201);
	UTL_AddPinPdsB( arg1, arg2, arg3);
	STOP_LAPTIMER(201);
}
void _UTL_ClearPinPdsB( PinHandle arg1)
{
	MCI_LIST[202] = "UTL_ClearPinPdsB";
	START_LAPTIMER(202);
	UTL_ClearPinPdsB( arg1);
	STOP_LAPTIMER(202);
}
void _UTL_AddPinPdsD( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[203] = "UTL_AddPinPdsD";
	START_LAPTIMER(203);
	UTL_AddPinPdsD( arg1, arg2, arg3);
	STOP_LAPTIMER(203);
}
void _UTL_ClearPinPdsD( PinHandle arg1)
{
	MCI_LIST[204] = "UTL_ClearPinPdsD";
	START_LAPTIMER(204);
	UTL_ClearPinPdsD( arg1);
	STOP_LAPTIMER(204);
}
void _UTL_AddPinPdsE( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[205] = "UTL_AddPinPdsE";
	START_LAPTIMER(205);
	UTL_AddPinPdsE( arg1, arg2, arg3);
	STOP_LAPTIMER(205);
}
void _UTL_ClearPinPdsE( PinHandle arg1)
{
	MCI_LIST[206] = "UTL_ClearPinPdsE";
	START_LAPTIMER(206);
	UTL_ClearPinPdsE( arg1);
	STOP_LAPTIMER(206);
}
void _UTL_SetPinCyclePaletteSet( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[207] = "UTL_SetPinCyclePaletteSet";
	START_LAPTIMER(207);
	UTL_SetPinCyclePaletteSet( arg1, arg2);
	STOP_LAPTIMER(207);
}
void _UTL_SetPinRinv( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[208] = "UTL_SetPinRinv";
	START_LAPTIMER(208);
	UTL_SetPinRinv( arg1, arg2);
	STOP_LAPTIMER(208);
}
void _UTL_SetPinRdsm( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[209] = "UTL_SetPinRdsm";
	START_LAPTIMER(209);
	UTL_SetPinRdsm( arg1, arg2);
	STOP_LAPTIMER(209);
}
void _UTL_SetPinPsm( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[210] = "UTL_SetPinPsm";
	START_LAPTIMER(210);
	UTL_SetPinPsm( arg1, arg2);
	STOP_LAPTIMER(210);
}
void _UTL_SetPinSdm( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[211] = "UTL_SetPinSdm";
	START_LAPTIMER(211);
	UTL_SetPinSdm( arg1, arg2);
	STOP_LAPTIMER(211);
}
void _UTL_SetPinSmc( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[212] = "UTL_SetPinSmc";
	START_LAPTIMER(212);
	UTL_SetPinSmc( arg1, arg2);
	STOP_LAPTIMER(212);
}
void _UTL_SetPinAinv( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[213] = "UTL_SetPinAinv";
	START_LAPTIMER(213);
	UTL_SetPinAinv( arg1, arg2);
	STOP_LAPTIMER(213);
}
void _UTL_SetPinDssNumber( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[214] = "UTL_SetPinDssNumber";
	START_LAPTIMER(214);
	UTL_SetPinDssNumber( arg1, arg2);
	STOP_LAPTIMER(214);
}
void _UTL_SetPinDrDelay( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[215] = "UTL_SetPinDrDelay";
	START_LAPTIMER(215);
	UTL_SetPinDrDelay( arg1, arg2);
	STOP_LAPTIMER(215);
}
void _UTL_SetPinDreDelay( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[216] = "UTL_SetPinDreDelay";
	START_LAPTIMER(216);
	UTL_SetPinDreDelay( arg1, arg2);
	STOP_LAPTIMER(216);
}
void _UTL_SetPinExpDelay( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[217] = "UTL_SetPinExpDelay";
	START_LAPTIMER(217);
	UTL_SetPinExpDelay( arg1, arg2);
	STOP_LAPTIMER(217);
}
void _UTL_SetPinCpeDelay( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[218] = "UTL_SetPinCpeDelay";
	START_LAPTIMER(218);
	UTL_SetPinCpeDelay( arg1, arg2);
	STOP_LAPTIMER(218);
}
void _UTL_SetPinModeDrDelay( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[219] = "UTL_SetPinModeDrDelay";
	START_LAPTIMER(219);
	UTL_SetPinModeDrDelay( arg1, arg2, arg3);
	STOP_LAPTIMER(219);
}
void _UTL_SetPinModeDreDelay( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[220] = "UTL_SetPinModeDreDelay";
	START_LAPTIMER(220);
	UTL_SetPinModeDreDelay( arg1, arg2, arg3);
	STOP_LAPTIMER(220);
}
void _UTL_SetPinModeExpDelay( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[221] = "UTL_SetPinModeExpDelay";
	START_LAPTIMER(221);
	UTL_SetPinModeExpDelay( arg1, arg2, arg3);
	STOP_LAPTIMER(221);
}
void _UTL_SetPinModeCpeDelay( PinHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[222] = "UTL_SetPinModeCpeDelay";
	START_LAPTIMER(222);
	UTL_SetPinModeCpeDelay( arg1, arg2, arg3);
	STOP_LAPTIMER(222);
}
void _UTL_SetPinDrPatternLevel( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[223] = "UTL_SetPinDrPatternLevel";
	START_LAPTIMER(223);
	UTL_SetPinDrPatternLevel( arg1, arg2);
	STOP_LAPTIMER(223);
}
void _UTL_SetPinDrePatternLevel( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[224] = "UTL_SetPinDrePatternLevel";
	START_LAPTIMER(224);
	UTL_SetPinDrePatternLevel( arg1, arg2);
	STOP_LAPTIMER(224);
}
void _UTL_SetPinBankMultiplex( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[225] = "UTL_SetPinBankMultiplex";
	START_LAPTIMER(225);
	UTL_SetPinBankMultiplex( arg1, arg2);
	STOP_LAPTIMER(225);
}
void _UTL_SetPinBankNumber( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[226] = "UTL_SetPinBankNumber";
	START_LAPTIMER(226);
	UTL_SetPinBankNumber( arg1, arg2);
	STOP_LAPTIMER(226);
}
void _UTL_SetPinTerm( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[227] = "UTL_SetPinTerm";
	START_LAPTIMER(227);
	UTL_SetPinTerm( arg1, arg2);
	STOP_LAPTIMER(227);
}
void _UTL_SetPinIlNumber( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[228] = "UTL_SetPinIlNumber";
	START_LAPTIMER(228);
	UTL_SetPinIlNumber( arg1, arg2);
	STOP_LAPTIMER(228);
}
void _UTL_SetPinPl( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[229] = "UTL_SetPinPl";
	START_LAPTIMER(229);
	UTL_SetPinPl( arg1, arg2);
	STOP_LAPTIMER(229);
}
void _UTL_SetPinVtNumber( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[230] = "UTL_SetPinVtNumber";
	START_LAPTIMER(230);
	UTL_SetPinVtNumber( arg1, arg2);
	STOP_LAPTIMER(230);
}
void _UTL_SetPinDclp( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[231] = "UTL_SetPinDclp";
	START_LAPTIMER(231);
	UTL_SetPinDclp( arg1, arg2);
	STOP_LAPTIMER(231);
}
void _UTL_SetPinVloadNumber( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[232] = "UTL_SetPinVloadNumber";
	START_LAPTIMER(232);
	UTL_SetPinVloadNumber( arg1, arg2);
	STOP_LAPTIMER(232);
}
void _UTL_SetPinVloadResistor( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[233] = "UTL_SetPinVloadResistor";
	START_LAPTIMER(233);
	UTL_SetPinVloadResistor( arg1, arg2);
	STOP_LAPTIMER(233);
}
void _UTL_SetPinOpen( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[234] = "UTL_SetPinOpen";
	START_LAPTIMER(234);
	UTL_SetPinOpen( arg1, arg2);
	STOP_LAPTIMER(234);
}
void _UTL_SetPinPatternInh( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[235] = "UTL_SetPinPatternInh";
	START_LAPTIMER(235);
	UTL_SetPinPatternInh( arg1, arg2);
	STOP_LAPTIMER(235);
}
void _UTL_SetPinPatternInhLevel( PinHandle arg1, RadioButton arg2)
{
	MCI_LIST[236] = "UTL_SetPinPatternInhLevel";
	START_LAPTIMER(236);
	UTL_SetPinPatternInhLevel( arg1, arg2);
	STOP_LAPTIMER(236);
}
void _UTL_SetPinDrePatternInh( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[237] = "UTL_SetPinDrePatternInh";
	START_LAPTIMER(237);
	UTL_SetPinDrePatternInh( arg1, arg2);
	STOP_LAPTIMER(237);
}
void _UTL_SetPinPatternInhPerPin( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[238] = "UTL_SetPinPatternInhPerPin";
	START_LAPTIMER(238);
	UTL_SetPinPatternInhPerPin( arg1, arg2);
	STOP_LAPTIMER(238);
}
void _UTL_SetPinDbmPinFix( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[239] = "UTL_SetPinDbmPinFix";
	START_LAPTIMER(239);
	UTL_SetPinDbmPinFix( arg1, arg2);
	STOP_LAPTIMER(239);
}
void _UTL_SetPinVsDisconnect( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[240] = "UTL_SetPinVsDisconnect";
	START_LAPTIMER(240);
	UTL_SetPinVsDisconnect( arg1, arg2);
	STOP_LAPTIMER(240);
}
void _UTL_SetPinVsBypassCapacitor( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[241] = "UTL_SetPinVsBypassCapacitor";
	START_LAPTIMER(241);
	UTL_SetPinVsBypassCapacitor( arg1, arg2);
	STOP_LAPTIMER(241);
}
void _UTL_SetPinVsBypassCapacitorNumber( PinHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[242] = "UTL_SetPinVsBypassCapacitorNumber";
	START_LAPTIMER(242);
	UTL_SetPinVsBypassCapacitorNumber( arg1, arg2, arg3);
	STOP_LAPTIMER(242);
}
void _UTL_SetPinDcConnect( PinHandle arg1, CheckButton arg2)
{
	MCI_LIST[243] = "UTL_SetPinDcConnect";
	START_LAPTIMER(243);
	UTL_SetPinDcConnect( arg1, arg2);
	STOP_LAPTIMER(243);
}
void _UTL_SendPin( PinHandle arg1, char * arg2)
{
	MCI_LIST[244] = "UTL_SendPin";
	START_LAPTIMER(244);
	UTL_SendPin( arg1, arg2);
	STOP_LAPTIMER(244);
}
void _UTL_ResetDriverLevel()
{
	MCI_LIST[245] = "UTL_ResetDriverLevel";
	START_LAPTIMER(245);
	UTL_ResetDriverLevel();
	STOP_LAPTIMER(245);
}
LevelHoldHandle _UTL_GetLevelHoldHandle()
{
	MCI_LIST[246] = "UTL_GetLevelHoldHandle";
	START_LAPTIMER(246);
	LevelHoldHandle retval = UTL_GetLevelHoldHandle();
	STOP_LAPTIMER(246);
	return retval;
}
void _UTL_SetLevelHoldInit( LevelHoldHandle arg1, CheckButton arg2)
{
	MCI_LIST[247] = "UTL_SetLevelHoldInit";
	START_LAPTIMER(247);
	UTL_SetLevelHoldInit( arg1, arg2);
	STOP_LAPTIMER(247);
}
void _UTL_SendLevelHold( LevelHoldHandle arg1)
{
	MCI_LIST[248] = "UTL_SendLevelHold";
	START_LAPTIMER(248);
	UTL_SendLevelHold( arg1);
	STOP_LAPTIMER(248);
}
DbmDelayHandle _UTL_GetDbmDelayHandle()
{
	MCI_LIST[249] = "UTL_GetDbmDelayHandle";
	START_LAPTIMER(249);
	DbmDelayHandle retval = UTL_GetDbmDelayHandle();
	STOP_LAPTIMER(249);
	return retval;
}
void _UTL_SetDbmDelayInhibit( DbmDelayHandle arg1, CheckButton arg2)
{
	MCI_LIST[250] = "UTL_SetDbmDelayInhibit";
	START_LAPTIMER(250);
	UTL_SetDbmDelayInhibit( arg1, arg2);
	STOP_LAPTIMER(250);
}
void _UTL_SendDbmDelay( DbmDelayHandle arg1)
{
	MCI_LIST[251] = "UTL_SendDbmDelay";
	START_LAPTIMER(251);
	UTL_SendDbmDelay( arg1);
	STOP_LAPTIMER(251);
}
LevelFixHandle _UTL_GetLevelFixHandle()
{
	MCI_LIST[252] = "UTL_GetLevelFixHandle";
	START_LAPTIMER(252);
	LevelFixHandle retval = UTL_GetLevelFixHandle();
	STOP_LAPTIMER(252);
	return retval;
}
void _UTL_SetLevelFixOutputLevel( LevelFixHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[253] = "UTL_SetLevelFixOutputLevel";
	START_LAPTIMER(253);
	UTL_SetLevelFixOutputLevel( arg1, arg2, arg3);
	STOP_LAPTIMER(253);
}
void _UTL_SendLevelFix( LevelFixHandle arg1, UT_PIN arg2, UT_DUT arg3)
{
	MCI_LIST[254] = "UTL_SendLevelFix";
	START_LAPTIMER(254);
	UTL_SendLevelFix( arg1, arg2, arg3);
	STOP_LAPTIMER(254);
}
MatchPinGroupHandle _UTL_GetMatchPinGroupHandle()
{
	MCI_LIST[255] = "UTL_GetMatchPinGroupHandle";
	START_LAPTIMER(255);
	MatchPinGroupHandle retval = UTL_GetMatchPinGroupHandle();
	STOP_LAPTIMER(255);
	return retval;
}
void _UTL_SetMatchPinGroupSignal( MatchPinGroupHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[256] = "UTL_SetMatchPinGroupSignal";
	START_LAPTIMER(256);
	UTL_SetMatchPinGroupSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(256);
}
void _UTL_SendMatchPinGroup( MatchPinGroupHandle arg1)
{
	MCI_LIST[257] = "UTL_SendMatchPinGroup";
	START_LAPTIMER(257);
	UTL_SendMatchPinGroup( arg1);
	STOP_LAPTIMER(257);
}
VihhMutHandle _UTL_GetVihhMutHandle()
{
	MCI_LIST[258] = "UTL_GetVihhMutHandle";
	START_LAPTIMER(258);
	VihhMutHandle retval = UTL_GetVihhMutHandle();
	STOP_LAPTIMER(258);
	return retval;
}
void _UTL_SetVihhMutSignal( VihhMutHandle arg1, RadioButton arg2)
{
	MCI_LIST[259] = "UTL_SetVihhMutSignal";
	START_LAPTIMER(259);
	UTL_SetVihhMutSignal( arg1, arg2);
	STOP_LAPTIMER(259);
}
void _UTL_SendVihhMut( VihhMutHandle arg1)
{
	MCI_LIST[260] = "UTL_SendVihhMut";
	START_LAPTIMER(260);
	UTL_SendVihhMut( arg1);
	STOP_LAPTIMER(260);
}
VihhMutStartCtrlHandle _UTL_GetVihhMutStartCtrlHandle()
{
	MCI_LIST[261] = "UTL_GetVihhMutStartCtrlHandle";
	START_LAPTIMER(261);
	VihhMutStartCtrlHandle retval = UTL_GetVihhMutStartCtrlHandle();
	STOP_LAPTIMER(261);
	return retval;
}
void _UTL_SetVihhMutStartCtrl( VihhMutStartCtrlHandle arg1, RadioButton arg2)
{
	MCI_LIST[262] = "UTL_SetVihhMutStartCtrl";
	START_LAPTIMER(262);
	UTL_SetVihhMutStartCtrl( arg1, arg2);
	STOP_LAPTIMER(262);
}
void _UTL_SendVihhMutStartCtrl( VihhMutStartCtrlHandle arg1)
{
	MCI_LIST[263] = "UTL_SendVihhMutStartCtrl";
	START_LAPTIMER(263);
	UTL_SendVihhMutStartCtrl( arg1);
	STOP_LAPTIMER(263);
}
VsHandle _UTL_GetVsHandle()
{
	MCI_LIST[264] = "UTL_GetVsHandle";
	START_LAPTIMER(264);
	VsHandle retval = UTL_GetVsHandle();
	STOP_LAPTIMER(264);
	return retval;
}
void _UTL_SetVsMode( VsHandle arg1, RadioButton arg2)
{
	MCI_LIST[265] = "UTL_SetVsMode";
	START_LAPTIMER(265);
	UTL_SetVsMode( arg1, arg2);
	STOP_LAPTIMER(265);
}
void _UTL_SetVsSource( VsHandle arg1, DSlider arg2)
{
	MCI_LIST[266] = "UTL_SetVsSource";
	START_LAPTIMER(266);
	UTL_SetVsSource( arg1, arg2);
	STOP_LAPTIMER(266);
}
void _UTL_SetVsSrange( VsHandle arg1, DSlider arg2, DSlider arg3)
{
	MCI_LIST[267] = "UTL_SetVsSrange";
	START_LAPTIMER(267);
	UTL_SetVsSrange( arg1, arg2, arg3);
	STOP_LAPTIMER(267);
}
void _UTL_SetVsMrange( VsHandle arg1, DSlider arg2, DSlider arg3)
{
	MCI_LIST[268] = "UTL_SetVsMrange";
	START_LAPTIMER(268);
	UTL_SetVsMrange( arg1, arg2, arg3);
	STOP_LAPTIMER(268);
}
void _UTL_SetVsPclamp( VsHandle arg1, DSlider arg2)
{
	MCI_LIST[269] = "UTL_SetVsPclamp";
	START_LAPTIMER(269);
	UTL_SetVsPclamp( arg1, arg2);
	STOP_LAPTIMER(269);
}
void _UTL_SetVsMclamp( VsHandle arg1, DSlider arg2)
{
	MCI_LIST[270] = "UTL_SetVsMclamp";
	START_LAPTIMER(270);
	UTL_SetVsMclamp( arg1, arg2);
	STOP_LAPTIMER(270);
}
void _UTL_SetVsFilter( VsHandle arg1, RadioButton arg2)
{
	MCI_LIST[271] = "UTL_SetVsFilter";
	START_LAPTIMER(271);
	UTL_SetVsFilter( arg1, arg2);
	STOP_LAPTIMER(271);
}
void _UTL_SetVsHighSpeedSlewRateMode( VsHandle arg1, CheckButton arg2)
{
	MCI_LIST[272] = "UTL_SetVsHighSpeedSlewRateMode";
	START_LAPTIMER(272);
	UTL_SetVsHighSpeedSlewRateMode( arg1, arg2);
	STOP_LAPTIMER(272);
}
void _UTL_SetVsSlewRate( VsHandle arg1, DSlider arg2)
{
	MCI_LIST[273] = "UTL_SetVsSlewRate";
	START_LAPTIMER(273);
	UTL_SetVsSlewRate( arg1, arg2);
	STOP_LAPTIMER(273);
}
void _UTL_SetVsPhaseCompensation( VsHandle arg1, RadioButton arg2)
{
	MCI_LIST[274] = "UTL_SetVsPhaseCompensation";
	START_LAPTIMER(274);
	UTL_SetVsPhaseCompensation( arg1, arg2);
	STOP_LAPTIMER(274);
}
void _UTL_SetVsLimitHigh( VsHandle arg1, DSlider arg2, CheckButton arg3)
{
	MCI_LIST[275] = "UTL_SetVsLimitHigh";
	START_LAPTIMER(275);
	UTL_SetVsLimitHigh( arg1, arg2, arg3);
	STOP_LAPTIMER(275);
}
void _UTL_SetVsLimitLow( VsHandle arg1, DSlider arg2, CheckButton arg3)
{
	MCI_LIST[276] = "UTL_SetVsLimitLow";
	START_LAPTIMER(276);
	UTL_SetVsLimitLow( arg1, arg2, arg3);
	STOP_LAPTIMER(276);
}
void _UTL_SetVsMeasCnt( VsHandle arg1, Slider arg2)
{
	MCI_LIST[277] = "UTL_SetVsMeasCnt";
	START_LAPTIMER(277);
	UTL_SetVsMeasCnt( arg1, arg2);
	STOP_LAPTIMER(277);
}
void _UTL_AddVsWetItem( VsHandle arg1, RadioButton arg2)
{
	MCI_LIST[278] = "UTL_AddVsWetItem";
	START_LAPTIMER(278);
	UTL_AddVsWetItem( arg1, arg2);
	STOP_LAPTIMER(278);
}
void _UTL_ClearVsWetItem( VsHandle arg1)
{
	MCI_LIST[279] = "UTL_ClearVsWetItem";
	START_LAPTIMER(279);
	UTL_ClearVsWetItem( arg1);
	STOP_LAPTIMER(279);
}
void _UTL_SetVsParaDrive( VsHandle arg1, CheckButton arg2)
{
	MCI_LIST[280] = "UTL_SetVsParaDrive";
	START_LAPTIMER(280);
	UTL_SetVsParaDrive( arg1, arg2);
	STOP_LAPTIMER(280);
}
void _UTL_SendVs( VsHandle arg1, RadioButton arg2)
{
	MCI_LIST[281] = "UTL_SendVs";
	START_LAPTIMER(281);
	UTL_SendVs( arg1, arg2);
	STOP_LAPTIMER(281);
}
void _UTL_SendVsTargetDut( VsHandle arg1, RadioButton arg2, UT_DUT arg3)
{
	MCI_LIST[282] = "UTL_SendVsTargetDut";
	START_LAPTIMER(282);
	UTL_SendVsTargetDut( arg1, arg2, arg3);
	STOP_LAPTIMER(282);
}
void _UTL_SendVsTargetPps( VsHandle arg1, RadioButton arg2)
{
	MCI_LIST[283] = "UTL_SendVsTargetPps";
	START_LAPTIMER(283);
	UTL_SendVsTargetPps( arg1, arg2);
	STOP_LAPTIMER(283);
}
ViHandle _UTL_GetViHandle()
{
	MCI_LIST[284] = "UTL_GetViHandle";
	START_LAPTIMER(284);
	ViHandle retval = UTL_GetViHandle();
	STOP_LAPTIMER(284);
	return retval;
}
void _UTL_SetViHigh( ViHandle arg1, DSlider arg2)
{
	MCI_LIST[285] = "UTL_SetViHigh";
	START_LAPTIMER(285);
	UTL_SetViHigh( arg1, arg2);
	STOP_LAPTIMER(285);
}
void _UTL_SetViLow( ViHandle arg1, DSlider arg2)
{
	MCI_LIST[286] = "UTL_SetViLow";
	START_LAPTIMER(286);
	UTL_SetViLow( arg1, arg2);
	STOP_LAPTIMER(286);
}
void _UTL_SetViHvDr( ViHandle arg1, CheckButton arg2)
{
	MCI_LIST[287] = "UTL_SetViHvDr";
	START_LAPTIMER(287);
	UTL_SetViHvDr( arg1, arg2);
	STOP_LAPTIMER(287);
}
void _UTL_SetViHvLvDr( ViHandle arg1, CheckButton arg2)
{
	MCI_LIST[288] = "UTL_SetViHvLvDr";
	START_LAPTIMER(288);
	UTL_SetViHvLvDr( arg1, arg2);
	STOP_LAPTIMER(288);
}
void _UTL_SendVi( ViHandle arg1, RadioButton arg2)
{
	MCI_LIST[289] = "UTL_SendVi";
	START_LAPTIMER(289);
	UTL_SendVi( arg1, arg2);
	STOP_LAPTIMER(289);
}
void _UTL_SendViPerPin( ViHandle arg1, UT_PIN arg2, UT_DUT arg3)
{
	MCI_LIST[290] = "UTL_SendViPerPin";
	START_LAPTIMER(290);
	UTL_SendViPerPin( arg1, arg2, arg3);
	STOP_LAPTIMER(290);
}
VoHandle _UTL_GetVoHandle()
{
	MCI_LIST[291] = "UTL_GetVoHandle";
	START_LAPTIMER(291);
	VoHandle retval = UTL_GetVoHandle();
	STOP_LAPTIMER(291);
	return retval;
}
void _UTL_SetVoHigh( VoHandle arg1, DSlider arg2)
{
	MCI_LIST[292] = "UTL_SetVoHigh";
	START_LAPTIMER(292);
	UTL_SetVoHigh( arg1, arg2);
	STOP_LAPTIMER(292);
}
void _UTL_SetVoLow( VoHandle arg1, DSlider arg2)
{
	MCI_LIST[293] = "UTL_SetVoLow";
	START_LAPTIMER(293);
	UTL_SetVoLow( arg1, arg2);
	STOP_LAPTIMER(293);
}
void _UTL_SendVo( VoHandle arg1, RadioButton arg2)
{
	MCI_LIST[294] = "UTL_SendVo";
	START_LAPTIMER(294);
	UTL_SendVo( arg1, arg2);
	STOP_LAPTIMER(294);
}
VodHandle _UTL_GetVodHandle()
{
	MCI_LIST[295] = "UTL_GetVodHandle";
	START_LAPTIMER(295);
	VodHandle retval = UTL_GetVodHandle();
	STOP_LAPTIMER(295);
	return retval;
}
void _UTL_SetVodHigh( VodHandle arg1, DSlider arg2)
{
	MCI_LIST[296] = "UTL_SetVodHigh";
	START_LAPTIMER(296);
	UTL_SetVodHigh( arg1, arg2);
	STOP_LAPTIMER(296);
}
void _UTL_SetVodLow( VodHandle arg1, DSlider arg2)
{
	MCI_LIST[297] = "UTL_SetVodLow";
	START_LAPTIMER(297);
	UTL_SetVodLow( arg1, arg2);
	STOP_LAPTIMER(297);
}
void _UTL_SendVod( VodHandle arg1, RadioButton arg2)
{
	MCI_LIST[298] = "UTL_SendVod";
	START_LAPTIMER(298);
	UTL_SendVod( arg1, arg2);
	STOP_LAPTIMER(298);
}
IlHandle _UTL_GetIlHandle()
{
	MCI_LIST[299] = "UTL_GetIlHandle";
	START_LAPTIMER(299);
	IlHandle retval = UTL_GetIlHandle();
	STOP_LAPTIMER(299);
	return retval;
}
void _UTL_SetIlHigh( IlHandle arg1, DSlider arg2)
{
	MCI_LIST[300] = "UTL_SetIlHigh";
	START_LAPTIMER(300);
	UTL_SetIlHigh( arg1, arg2);
	STOP_LAPTIMER(300);
}
void _UTL_SetIlLow( IlHandle arg1, DSlider arg2)
{
	MCI_LIST[301] = "UTL_SetIlLow";
	START_LAPTIMER(301);
	UTL_SetIlLow( arg1, arg2);
	STOP_LAPTIMER(301);
}
void _UTL_SendIl( IlHandle arg1, RadioButton arg2)
{
	MCI_LIST[302] = "UTL_SendIl";
	START_LAPTIMER(302);
	UTL_SendIl( arg1, arg2);
	STOP_LAPTIMER(302);
}
VtHandle _UTL_GetVtHandle()
{
	MCI_LIST[303] = "UTL_GetVtHandle";
	START_LAPTIMER(303);
	VtHandle retval = UTL_GetVtHandle();
	STOP_LAPTIMER(303);
	return retval;
}
void _UTL_SetVt( VtHandle arg1, DSlider arg2)
{
	MCI_LIST[304] = "UTL_SetVt";
	START_LAPTIMER(304);
	UTL_SetVt( arg1, arg2);
	STOP_LAPTIMER(304);
}
void _UTL_SendVt( VtHandle arg1, RadioButton arg2)
{
	MCI_LIST[305] = "UTL_SendVt";
	START_LAPTIMER(305);
	UTL_SendVt( arg1, arg2);
	STOP_LAPTIMER(305);
}
DclpHandle _UTL_GetDclpHandle()
{
	MCI_LIST[306] = "UTL_GetDclpHandle";
	START_LAPTIMER(306);
	DclpHandle retval = UTL_GetDclpHandle();
	STOP_LAPTIMER(306);
	return retval;
}
void _UTL_SetDclpHigh( DclpHandle arg1, DSlider arg2)
{
	MCI_LIST[307] = "UTL_SetDclpHigh";
	START_LAPTIMER(307);
	UTL_SetDclpHigh( arg1, arg2);
	STOP_LAPTIMER(307);
}
void _UTL_SetDclpLow( DclpHandle arg1, DSlider arg2)
{
	MCI_LIST[308] = "UTL_SetDclpLow";
	START_LAPTIMER(308);
	UTL_SetDclpLow( arg1, arg2);
	STOP_LAPTIMER(308);
}
void _UTL_SendDclp( DclpHandle arg1, RadioButton arg2)
{
	MCI_LIST[309] = "UTL_SendDclp";
	START_LAPTIMER(309);
	UTL_SendDclp( arg1, arg2);
	STOP_LAPTIMER(309);
}
VihhHandle _UTL_GetVihhHandle()
{
	MCI_LIST[310] = "UTL_GetVihhHandle";
	START_LAPTIMER(310);
	VihhHandle retval = UTL_GetVihhHandle();
	STOP_LAPTIMER(310);
	return retval;
}
void _UTL_SetVihhHigh( VihhHandle arg1, DSlider arg2)
{
	MCI_LIST[311] = "UTL_SetVihhHigh";
	START_LAPTIMER(311);
	UTL_SetVihhHigh( arg1, arg2);
	STOP_LAPTIMER(311);
}
void _UTL_SetVihhHv( VihhHandle arg1, DSlider arg2)
{
	MCI_LIST[312] = "UTL_SetVihhHv";
	START_LAPTIMER(312);
	UTL_SetVihhHv( arg1, arg2);
	STOP_LAPTIMER(312);
}
void _UTL_SetVihhLow( VihhHandle arg1, DSlider arg2)
{
	MCI_LIST[313] = "UTL_SetVihhLow";
	START_LAPTIMER(313);
	UTL_SetVihhLow( arg1, arg2);
	STOP_LAPTIMER(313);
}
void _UTL_SendVihh( VihhHandle arg1, RadioButton arg2)
{
	MCI_LIST[314] = "UTL_SendVihh";
	START_LAPTIMER(314);
	UTL_SendVihh( arg1, arg2);
	STOP_LAPTIMER(314);
}
void _UTL_SendVihhPerPin( VihhHandle arg1, UT_PIN arg2, UT_DUT arg3)
{
	MCI_LIST[315] = "UTL_SendVihhPerPin";
	START_LAPTIMER(315);
	UTL_SendVihhPerPin( arg1, arg2, arg3);
	STOP_LAPTIMER(315);
}
IodModeHandle _UTL_GetIodModeHandle()
{
	MCI_LIST[316] = "UTL_GetIodModeHandle";
	START_LAPTIMER(316);
	IodModeHandle retval = UTL_GetIodModeHandle();
	STOP_LAPTIMER(316);
	return retval;
}
void _UTL_AddIodModePin( IodModeHandle arg1, UT_PIN arg2)
{
	MCI_LIST[317] = "UTL_AddIodModePin";
	START_LAPTIMER(317);
	UTL_AddIodModePin( arg1, arg2);
	STOP_LAPTIMER(317);
}
void _UTL_ClearIodModePin( IodModeHandle arg1)
{
	MCI_LIST[318] = "UTL_ClearIodModePin";
	START_LAPTIMER(318);
	UTL_ClearIodModePin( arg1);
	STOP_LAPTIMER(318);
}
void _UTL_SetIodMode( IodModeHandle arg1, CheckButton arg2)
{
	MCI_LIST[319] = "UTL_SetIodMode";
	START_LAPTIMER(319);
	UTL_SetIodMode( arg1, arg2);
	STOP_LAPTIMER(319);
}
void _UTL_SetIodModeAuto( IodModeHandle arg1, CheckButton arg2)
{
	MCI_LIST[320] = "UTL_SetIodModeAuto";
	START_LAPTIMER(320);
	UTL_SetIodModeAuto( arg1, arg2);
	STOP_LAPTIMER(320);
}
void _UTL_SetIodModeCalcFunc( IodModeHandle arg1, void (*arg2)(IodCalcFunc *))
{
	MCI_LIST[321] = "UTL_SetIodModeCalcFunc";
	START_LAPTIMER(321);
	UTL_SetIodModeCalcFunc( arg1, arg2);
	STOP_LAPTIMER(321);
}
void _UTL_SetIodModeCalcFuncAndLibrary( IodModeHandle arg1, char * arg2, char * arg3)
{
	MCI_LIST[322] = "UTL_SetIodModeCalcFuncAndLibrary";
	START_LAPTIMER(322);
	UTL_SetIodModeCalcFuncAndLibrary( arg1, arg2, arg3);
	STOP_LAPTIMER(322);
}
void _UTL_SendIodMode( IodModeHandle arg1)
{
	MCI_LIST[323] = "UTL_SendIodMode";
	START_LAPTIMER(323);
	UTL_SendIodMode( arg1);
	STOP_LAPTIMER(323);
}
IodHandle _UTL_GetIodHandle()
{
	MCI_LIST[324] = "UTL_GetIodHandle";
	START_LAPTIMER(324);
	IodHandle retval = UTL_GetIodHandle();
	STOP_LAPTIMER(324);
	return retval;
}
void _UTL_AddIodPin( IodHandle arg1, UT_PIN arg2)
{
	MCI_LIST[325] = "UTL_AddIodPin";
	START_LAPTIMER(325);
	UTL_AddIodPin( arg1, arg2);
	STOP_LAPTIMER(325);
}
void _UTL_ClearIodPin( IodHandle arg1)
{
	MCI_LIST[326] = "UTL_ClearIodPin";
	START_LAPTIMER(326);
	UTL_ClearIodPin( arg1);
	STOP_LAPTIMER(326);
}
void _UTL_AddIodDut( IodHandle arg1, UT_DUT arg2)
{
	MCI_LIST[327] = "UTL_AddIodDut";
	START_LAPTIMER(327);
	UTL_AddIodDut( arg1, arg2);
	STOP_LAPTIMER(327);
}
void _UTL_ClearIodDut( IodHandle arg1)
{
	MCI_LIST[328] = "UTL_ClearIodDut";
	START_LAPTIMER(328);
	UTL_ClearIodDut( arg1);
	STOP_LAPTIMER(328);
}
void _UTL_SetIodHigh( IodHandle arg1, DSlider arg2)
{
	MCI_LIST[329] = "UTL_SetIodHigh";
	START_LAPTIMER(329);
	UTL_SetIodHigh( arg1, arg2);
	STOP_LAPTIMER(329);
}
void _UTL_SetIodLow( IodHandle arg1, DSlider arg2)
{
	MCI_LIST[330] = "UTL_SetIodLow";
	START_LAPTIMER(330);
	UTL_SetIodLow( arg1, arg2);
	STOP_LAPTIMER(330);
}
void _UTL_SendIod( IodHandle arg1)
{
	MCI_LIST[331] = "UTL_SendIod";
	START_LAPTIMER(331);
	UTL_SendIod( arg1);
	STOP_LAPTIMER(331);
}
VloadHandle _UTL_GetVloadHandle()
{
	MCI_LIST[332] = "UTL_GetVloadHandle";
	START_LAPTIMER(332);
	VloadHandle retval = UTL_GetVloadHandle();
	STOP_LAPTIMER(332);
	return retval;
}
void _UTL_SetVload( VloadHandle arg1, DSlider arg2)
{
	MCI_LIST[333] = "UTL_SetVload";
	START_LAPTIMER(333);
	UTL_SetVload( arg1, arg2);
	STOP_LAPTIMER(333);
}
void _UTL_SendVload( VloadHandle arg1, RadioButton arg2)
{
	MCI_LIST[334] = "UTL_SendVload";
	START_LAPTIMER(334);
	UTL_SendVload( arg1, arg2);
	STOP_LAPTIMER(334);
}
void _UTL_SendCw( RadioButton arg1, unsigned arg2)
{
	MCI_LIST[335] = "UTL_SendCw";
	START_LAPTIMER(335);
	UTL_SendCw( arg1, arg2);
	STOP_LAPTIMER(335);
}
unsigned int _UTL_ReadCw( RadioButton arg1, UT_DUT arg2)
{
	MCI_LIST[336] = "UTL_ReadCw";
	START_LAPTIMER(336);
	unsigned int retval = UTL_ReadCw( arg1, arg2);
	STOP_LAPTIMER(336);
	return retval;
}
AuxDutSignalHandle _UTL_GetAuxDutSignalHandle()
{
	MCI_LIST[337] = "UTL_GetAuxDutSignalHandle";
	START_LAPTIMER(337);
	AuxDutSignalHandle retval = UTL_GetAuxDutSignalHandle();
	STOP_LAPTIMER(337);
	return retval;
}
void _UTL_SetAuxDutSignalStationNumber( AuxDutSignalHandle arg1, USlider arg2)
{
	MCI_LIST[338] = "UTL_SetAuxDutSignalStationNumber";
	START_LAPTIMER(338);
	UTL_SetAuxDutSignalStationNumber( arg1, arg2);
	STOP_LAPTIMER(338);
}
void _UTL_SetAuxDutSignalAllStation( AuxDutSignalHandle arg1, CheckButton arg2)
{
	MCI_LIST[339] = "UTL_SetAuxDutSignalAllStation";
	START_LAPTIMER(339);
	UTL_SetAuxDutSignalAllStation( arg1, arg2);
	STOP_LAPTIMER(339);
}
void _UTL_SetAuxDutSignalData( AuxDutSignalHandle arg1, USlider arg2)
{
	MCI_LIST[340] = "UTL_SetAuxDutSignalData";
	START_LAPTIMER(340);
	UTL_SetAuxDutSignalData( arg1, arg2);
	STOP_LAPTIMER(340);
}
void _UTL_SendAuxDutSignal( AuxDutSignalHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[341] = "UTL_SendAuxDutSignal";
	START_LAPTIMER(341);
	UTL_SendAuxDutSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(341);
}
void _UTL_SyncAuxDutSignal( RadioButton arg1)
{
	MCI_LIST[342] = "UTL_SyncAuxDutSignal";
	START_LAPTIMER(342);
	UTL_SyncAuxDutSignal( arg1);
	STOP_LAPTIMER(342);
}
LbCtrlHandle _UTL_GetLbCtrlHandle()
{
	MCI_LIST[343] = "UTL_GetLbCtrlHandle";
	START_LAPTIMER(343);
	LbCtrlHandle retval = UTL_GetLbCtrlHandle();
	STOP_LAPTIMER(343);
	return retval;
}
void _UTL_SetLbCtrlClockTiming( LbCtrlHandle arg1, DSlider arg2, DSlider arg3)
{
	MCI_LIST[344] = "UTL_SetLbCtrlClockTiming";
	START_LAPTIMER(344);
	UTL_SetLbCtrlClockTiming( arg1, arg2, arg3);
	STOP_LAPTIMER(344);
}
void _UTL_SetLbCtrlDataPacketCount( LbCtrlHandle arg1, USlider arg2)
{
	MCI_LIST[345] = "UTL_SetLbCtrlDataPacketCount";
	START_LAPTIMER(345);
	UTL_SetLbCtrlDataPacketCount( arg1, arg2);
	STOP_LAPTIMER(345);
}
void _UTL_SetLbCtrlDataFirstBit( LbCtrlHandle arg1, RadioButton arg2)
{
	MCI_LIST[346] = "UTL_SetLbCtrlDataFirstBit";
	START_LAPTIMER(346);
	UTL_SetLbCtrlDataFirstBit( arg1, arg2);
	STOP_LAPTIMER(346);
}
void _UTL_SetLbCtrlSSPolarity( LbCtrlHandle arg1, RadioButton arg2)
{
	MCI_LIST[347] = "UTL_SetLbCtrlSSPolarity";
	START_LAPTIMER(347);
	UTL_SetLbCtrlSSPolarity( arg1, arg2);
	STOP_LAPTIMER(347);
}
void _UTL_SetLbCtrlResetPolarity( LbCtrlHandle arg1, RadioButton arg2)
{
	MCI_LIST[348] = "UTL_SetLbCtrlResetPolarity";
	START_LAPTIMER(348);
	UTL_SetLbCtrlResetPolarity( arg1, arg2);
	STOP_LAPTIMER(348);
}
void _UTL_SetLbCtrlStartDelayTime( LbCtrlHandle arg1, DSlider arg2)
{
	MCI_LIST[349] = "UTL_SetLbCtrlStartDelayTime";
	START_LAPTIMER(349);
	UTL_SetLbCtrlStartDelayTime( arg1, arg2);
	STOP_LAPTIMER(349);
}
void _UTL_SetLbCtrlClockCount( LbCtrlHandle arg1, USlider arg2)
{
	MCI_LIST[350] = "UTL_SetLbCtrlClockCount";
	START_LAPTIMER(350);
	UTL_SetLbCtrlClockCount( arg1, arg2);
	STOP_LAPTIMER(350);
}
void _UTL_SetLbCtrlData( LbCtrlHandle arg1, USlider arg2)
{
	MCI_LIST[351] = "UTL_SetLbCtrlData";
	START_LAPTIMER(351);
	UTL_SetLbCtrlData( arg1, arg2);
	STOP_LAPTIMER(351);
}
void _UTL_SetLbCtrlStrbSkewAdjust( LbCtrlHandle arg1, DSlider arg2)
{
	MCI_LIST[352] = "UTL_SetLbCtrlStrbSkewAdjust";
	START_LAPTIMER(352);
	UTL_SetLbCtrlStrbSkewAdjust( arg1, arg2);
	STOP_LAPTIMER(352);
}
void _UTL_StartLbCtrl( LbCtrlHandle arg1)
{
	MCI_LIST[353] = "UTL_StartLbCtrl";
	START_LAPTIMER(353);
	UTL_StartLbCtrl( arg1);
	STOP_LAPTIMER(353);
}
void _UTL_SetLbCtrlResetDurationTime( LbCtrlHandle arg1, DSlider arg2)
{
	MCI_LIST[354] = "UTL_SetLbCtrlResetDurationTime";
	START_LAPTIMER(354);
	UTL_SetLbCtrlResetDurationTime( arg1, arg2);
	STOP_LAPTIMER(354);
}
void _UTL_ResetLbCtrl( LbCtrlHandle arg1)
{
	MCI_LIST[355] = "UTL_ResetLbCtrl";
	START_LAPTIMER(355);
	UTL_ResetLbCtrl( arg1);
	STOP_LAPTIMER(355);
}
USlider _UTL_ReadLbCtrlData()
{
	MCI_LIST[356] = "UTL_ReadLbCtrlData";
	START_LAPTIMER(356);
	USlider retval = UTL_ReadLbCtrlData();
	STOP_LAPTIMER(356);
	return retval;
}
SpiCtrlHandle _UTL_GetSpiCtrlHandle()
{
	MCI_LIST[357] = "UTL_GetSpiCtrlHandle";
	START_LAPTIMER(357);
	SpiCtrlHandle retval = UTL_GetSpiCtrlHandle();
	STOP_LAPTIMER(357);
	return retval;
}
void _UTL_SetSpiCtrlClockTiming( SpiCtrlHandle arg1, DSlider arg2, DSlider arg3)
{
	MCI_LIST[358] = "UTL_SetSpiCtrlClockTiming";
	START_LAPTIMER(358);
	UTL_SetSpiCtrlClockTiming( arg1, arg2, arg3);
	STOP_LAPTIMER(358);
}
void _UTL_SetSpiCtrlSSPolarity( SpiCtrlHandle arg1, RadioButton arg2)
{
	MCI_LIST[359] = "UTL_SetSpiCtrlSSPolarity";
	START_LAPTIMER(359);
	UTL_SetSpiCtrlSSPolarity( arg1, arg2);
	STOP_LAPTIMER(359);
}
void _UTL_SetSpiCtrlStartDelayTime( SpiCtrlHandle arg1, DSlider arg2)
{
	MCI_LIST[360] = "UTL_SetSpiCtrlStartDelayTime";
	START_LAPTIMER(360);
	UTL_SetSpiCtrlStartDelayTime( arg1, arg2);
	STOP_LAPTIMER(360);
}
void _UTL_SetSpiCtrlData( SpiCtrlHandle arg1, USlider * arg2, USlider arg3)
{
	MCI_LIST[361] = "UTL_SetSpiCtrlData";
	START_LAPTIMER(361);
	UTL_SetSpiCtrlData( arg1, arg2, arg3);
	STOP_LAPTIMER(361);
}
void _UTL_SetSpiCtrlStrbSkewAdjust( SpiCtrlHandle arg1, DSlider arg2)
{
	MCI_LIST[362] = "UTL_SetSpiCtrlStrbSkewAdjust";
	START_LAPTIMER(362);
	UTL_SetSpiCtrlStrbSkewAdjust( arg1, arg2);
	STOP_LAPTIMER(362);
}
void _UTL_SetSpiCtrlMode( SpiCtrlHandle arg1, RadioButton arg2)
{
	MCI_LIST[363] = "UTL_SetSpiCtrlMode";
	START_LAPTIMER(363);
	UTL_SetSpiCtrlMode( arg1, arg2);
	STOP_LAPTIMER(363);
}
void _UTL_SetSpiCtrlHighSpeedInterval( SpiCtrlHandle arg1, DSlider arg2, DSlider arg3)
{
	MCI_LIST[364] = "UTL_SetSpiCtrlHighSpeedInterval";
	START_LAPTIMER(364);
	UTL_SetSpiCtrlHighSpeedInterval( arg1, arg2, arg3);
	STOP_LAPTIMER(364);
}
void _UTL_StartSpiCtrl( SpiCtrlHandle arg1, RadioButton arg2)
{
	MCI_LIST[365] = "UTL_StartSpiCtrl";
	START_LAPTIMER(365);
	UTL_StartSpiCtrl( arg1, arg2);
	STOP_LAPTIMER(365);
}
void _UTL_ReadSpiCtrlData( RadioButton arg1, USlider * arg2, USlider * arg3)
{
	MCI_LIST[366] = "UTL_ReadSpiCtrlData";
	START_LAPTIMER(366);
	UTL_ReadSpiCtrlData( arg1, arg2, arg3);
	STOP_LAPTIMER(366);
}
PowerSeqHandle _UTL_GetPowerSeqHandle()
{
	MCI_LIST[367] = "UTL_GetPowerSeqHandle";
	START_LAPTIMER(367);
	PowerSeqHandle retval = UTL_GetPowerSeqHandle();
	STOP_LAPTIMER(367);
	return retval;
}
void _UTL_AddPowerSeqVs( PowerSeqHandle arg1, USlider arg2, RadioButton arg3)
{
	MCI_LIST[368] = "UTL_AddPowerSeqVs";
	START_LAPTIMER(368);
	UTL_AddPowerSeqVs( arg1, arg2, arg3);
	STOP_LAPTIMER(368);
}
void _UTL_AddPowerSeqVsAll( PowerSeqHandle arg1, USlider arg2)
{
	MCI_LIST[369] = "UTL_AddPowerSeqVsAll";
	START_LAPTIMER(369);
	UTL_AddPowerSeqVsAll( arg1, arg2);
	STOP_LAPTIMER(369);
}
void _UTL_AddPowerSeqDcAll( PowerSeqHandle arg1, USlider arg2)
{
	MCI_LIST[370] = "UTL_AddPowerSeqDcAll";
	START_LAPTIMER(370);
	UTL_AddPowerSeqDcAll( arg1, arg2);
	STOP_LAPTIMER(370);
}
void _UTL_AddPowerSeqDclpAll( PowerSeqHandle arg1, USlider arg2)
{
	MCI_LIST[371] = "UTL_AddPowerSeqDclpAll";
	START_LAPTIMER(371);
	UTL_AddPowerSeqDclpAll( arg1, arg2);
	STOP_LAPTIMER(371);
}
void _UTL_AddPowerSeqViAll( PowerSeqHandle arg1, USlider arg2)
{
	MCI_LIST[372] = "UTL_AddPowerSeqViAll";
	START_LAPTIMER(372);
	UTL_AddPowerSeqViAll( arg1, arg2);
	STOP_LAPTIMER(372);
}
void _UTL_AddPowerSeqVtAll( PowerSeqHandle arg1, USlider arg2)
{
	MCI_LIST[373] = "UTL_AddPowerSeqVtAll";
	START_LAPTIMER(373);
	UTL_AddPowerSeqVtAll( arg1, arg2);
	STOP_LAPTIMER(373);
}
void _UTL_AddPowerSeqIlAll( PowerSeqHandle arg1, USlider arg2)
{
	MCI_LIST[374] = "UTL_AddPowerSeqIlAll";
	START_LAPTIMER(374);
	UTL_AddPowerSeqIlAll( arg1, arg2);
	STOP_LAPTIMER(374);
}
void _UTL_AddPowerSeqOthers( PowerSeqHandle arg1, USlider arg2)
{
	MCI_LIST[375] = "UTL_AddPowerSeqOthers";
	START_LAPTIMER(375);
	UTL_AddPowerSeqOthers( arg1, arg2);
	STOP_LAPTIMER(375);
}
void _UTL_AddPowerSeqAll( PowerSeqHandle arg1, USlider arg2)
{
	MCI_LIST[376] = "UTL_AddPowerSeqAll";
	START_LAPTIMER(376);
	UTL_AddPowerSeqAll( arg1, arg2);
	STOP_LAPTIMER(376);
}
void _UTL_AddPowerSeqUnit( PowerSeqHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[377] = "UTL_AddPowerSeqUnit";
	START_LAPTIMER(377);
	UTL_AddPowerSeqUnit( arg1, arg2, arg3);
	STOP_LAPTIMER(377);
}
void _UTL_ClearPowerSeqUnit( PowerSeqHandle arg1, USlider arg2)
{
	MCI_LIST[378] = "UTL_ClearPowerSeqUnit";
	START_LAPTIMER(378);
	UTL_ClearPowerSeqUnit( arg1, arg2);
	STOP_LAPTIMER(378);
}
void _UTL_SetPowerSeqWaitTime( PowerSeqHandle arg1, USlider arg2, DSlider arg3)
{
	MCI_LIST[379] = "UTL_SetPowerSeqWaitTime";
	START_LAPTIMER(379);
	UTL_SetPowerSeqWaitTime( arg1, arg2, arg3);
	STOP_LAPTIMER(379);
}
void _UTL_SendPowerSeq( PowerSeqHandle arg1)
{
	MCI_LIST[380] = "UTL_SendPowerSeq";
	START_LAPTIMER(380);
	UTL_SendPowerSeq( arg1);
	STOP_LAPTIMER(380);
}
void _UTL_OnPowerSeq()
{
	MCI_LIST[381] = "UTL_OnPowerSeq";
	START_LAPTIMER(381);
	UTL_OnPowerSeq();
	STOP_LAPTIMER(381);
}
void _UTL_OffPowerSeq()
{
	MCI_LIST[382] = "UTL_OffPowerSeq";
	START_LAPTIMER(382);
	UTL_OffPowerSeq();
	STOP_LAPTIMER(382);
}
PowerCtrlHandle _UTL_GetPowerCtrlHandle()
{
	MCI_LIST[383] = "UTL_GetPowerCtrlHandle";
	START_LAPTIMER(383);
	PowerCtrlHandle retval = UTL_GetPowerCtrlHandle();
	STOP_LAPTIMER(383);
	return retval;
}
void _UTL_AddPowerCtrlVs( PowerCtrlHandle arg1, RadioButton arg2)
{
	MCI_LIST[384] = "UTL_AddPowerCtrlVs";
	START_LAPTIMER(384);
	UTL_AddPowerCtrlVs( arg1, arg2);
	STOP_LAPTIMER(384);
}
void _UTL_AddPowerCtrlVsAll( PowerCtrlHandle arg1)
{
	MCI_LIST[385] = "UTL_AddPowerCtrlVsAll";
	START_LAPTIMER(385);
	UTL_AddPowerCtrlVsAll( arg1);
	STOP_LAPTIMER(385);
}
void _UTL_AddPowerCtrlDcAll( PowerCtrlHandle arg1)
{
	MCI_LIST[386] = "UTL_AddPowerCtrlDcAll";
	START_LAPTIMER(386);
	UTL_AddPowerCtrlDcAll( arg1);
	STOP_LAPTIMER(386);
}
void _UTL_AddPowerCtrlDclpAll( PowerCtrlHandle arg1)
{
	MCI_LIST[387] = "UTL_AddPowerCtrlDclpAll";
	START_LAPTIMER(387);
	UTL_AddPowerCtrlDclpAll( arg1);
	STOP_LAPTIMER(387);
}
void _UTL_AddPowerCtrlViAll( PowerCtrlHandle arg1)
{
	MCI_LIST[388] = "UTL_AddPowerCtrlViAll";
	START_LAPTIMER(388);
	UTL_AddPowerCtrlViAll( arg1);
	STOP_LAPTIMER(388);
}
void _UTL_AddPowerCtrlVtAll( PowerCtrlHandle arg1)
{
	MCI_LIST[389] = "UTL_AddPowerCtrlVtAll";
	START_LAPTIMER(389);
	UTL_AddPowerCtrlVtAll( arg1);
	STOP_LAPTIMER(389);
}
void _UTL_AddPowerCtrlIlAll( PowerCtrlHandle arg1)
{
	MCI_LIST[390] = "UTL_AddPowerCtrlIlAll";
	START_LAPTIMER(390);
	UTL_AddPowerCtrlIlAll( arg1);
	STOP_LAPTIMER(390);
}
void _UTL_AddPowerCtrlAll( PowerCtrlHandle arg1)
{
	MCI_LIST[391] = "UTL_AddPowerCtrlAll";
	START_LAPTIMER(391);
	UTL_AddPowerCtrlAll( arg1);
	STOP_LAPTIMER(391);
}
void _UTL_AddPowerCtrlUnit( PowerCtrlHandle arg1, RadioButton arg2)
{
	MCI_LIST[392] = "UTL_AddPowerCtrlUnit";
	START_LAPTIMER(392);
	UTL_AddPowerCtrlUnit( arg1, arg2);
	STOP_LAPTIMER(392);
}
void _UTL_ClearPowerCtrlUnit( PowerCtrlHandle arg1)
{
	MCI_LIST[393] = "UTL_ClearPowerCtrlUnit";
	START_LAPTIMER(393);
	UTL_ClearPowerCtrlUnit( arg1);
	STOP_LAPTIMER(393);
}
void _UTL_SetPowerCtrlWaitTime( PowerCtrlHandle arg1, DSlider arg2)
{
	MCI_LIST[394] = "UTL_SetPowerCtrlWaitTime";
	START_LAPTIMER(394);
	UTL_SetPowerCtrlWaitTime( arg1, arg2);
	STOP_LAPTIMER(394);
}
void _UTL_OnPowerCtrl( PowerCtrlHandle arg1)
{
	MCI_LIST[395] = "UTL_OnPowerCtrl";
	START_LAPTIMER(395);
	UTL_OnPowerCtrl( arg1);
	STOP_LAPTIMER(395);
}
void _UTL_OffPowerCtrl( PowerCtrlHandle arg1)
{
	MCI_LIST[396] = "UTL_OffPowerCtrl";
	START_LAPTIMER(396);
	UTL_OffPowerCtrl( arg1);
	STOP_LAPTIMER(396);
}
void _UTL_SetWet()
{
	MCI_LIST[397] = "UTL_SetWet";
	START_LAPTIMER(397);
	UTL_SetWet();
	STOP_LAPTIMER(397);
}
void _UTL_ResetWet()
{
	MCI_LIST[398] = "UTL_ResetWet";
	START_LAPTIMER(398);
	UTL_ResetWet();
	STOP_LAPTIMER(398);
}
TgHandle _UTL_GetTgHandle()
{
	MCI_LIST[399] = "UTL_GetTgHandle";
	START_LAPTIMER(399);
	TgHandle retval = UTL_GetTgHandle();
	STOP_LAPTIMER(399);
	return retval;
}
void _UTL_AddTgRate( TgHandle arg1, RadioButton arg2, DSlider arg3)
{
	MCI_LIST[400] = "UTL_AddTgRate";
	START_LAPTIMER(400);
	UTL_AddTgRate( arg1, arg2, arg3);
	STOP_LAPTIMER(400);
}
void _UTL_AddTgAclk( TgHandle arg1, RadioButton arg2, RadioButton arg3, DSlider arg4)
{
	MCI_LIST[401] = "UTL_AddTgAclk";
	START_LAPTIMER(401);
	UTL_AddTgAclk( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(401);
}
void _UTL_AddTgAclkOff( TgHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[402] = "UTL_AddTgAclkOff";
	START_LAPTIMER(402);
	UTL_AddTgAclkOff( arg1, arg2, arg3);
	STOP_LAPTIMER(402);
}
void _UTL_AddTgBclk( TgHandle arg1, RadioButton arg2, RadioButton arg3, DSlider arg4)
{
	MCI_LIST[403] = "UTL_AddTgBclk";
	START_LAPTIMER(403);
	UTL_AddTgBclk( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(403);
}
void _UTL_AddTgBclkOff( TgHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[404] = "UTL_AddTgBclkOff";
	START_LAPTIMER(404);
	UTL_AddTgBclkOff( arg1, arg2, arg3);
	STOP_LAPTIMER(404);
}
void _UTL_AddTgCclk( TgHandle arg1, RadioButton arg2, RadioButton arg3, DSlider arg4)
{
	MCI_LIST[405] = "UTL_AddTgCclk";
	START_LAPTIMER(405);
	UTL_AddTgCclk( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(405);
}
void _UTL_AddTgCclkOff( TgHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[406] = "UTL_AddTgCclkOff";
	START_LAPTIMER(406);
	UTL_AddTgCclkOff( arg1, arg2, arg3);
	STOP_LAPTIMER(406);
}
void _UTL_AddTgStrb( TgHandle arg1, RadioButton arg2, RadioButton arg3, DSlider arg4)
{
	MCI_LIST[407] = "UTL_AddTgStrb";
	START_LAPTIMER(407);
	UTL_AddTgStrb( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(407);
}
void _UTL_AddTgStrbOff( TgHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[408] = "UTL_AddTgStrbOff";
	START_LAPTIMER(408);
	UTL_AddTgStrbOff( arg1, arg2, arg3);
	STOP_LAPTIMER(408);
}
void _UTL_AddTgPairStrbL( TgHandle arg1, RadioButton arg2, RadioButton arg3, DSlider arg4)
{
	MCI_LIST[409] = "UTL_AddTgPairStrbL";
	START_LAPTIMER(409);
	UTL_AddTgPairStrbL( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(409);
}
void _UTL_AddTgPairStrbT( TgHandle arg1, RadioButton arg2, RadioButton arg3, DSlider arg4)
{
	MCI_LIST[410] = "UTL_AddTgPairStrbT";
	START_LAPTIMER(410);
	UTL_AddTgPairStrbT( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(410);
}
void _UTL_AddTgDreL( TgHandle arg1, RadioButton arg2, RadioButton arg3, DSlider arg4)
{
	MCI_LIST[411] = "UTL_AddTgDreL";
	START_LAPTIMER(411);
	UTL_AddTgDreL( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(411);
}
void _UTL_AddTgDreLOff( TgHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[412] = "UTL_AddTgDreLOff";
	START_LAPTIMER(412);
	UTL_AddTgDreLOff( arg1, arg2, arg3);
	STOP_LAPTIMER(412);
}
void _UTL_AddTgDreT( TgHandle arg1, RadioButton arg2, RadioButton arg3, DSlider arg4)
{
	MCI_LIST[413] = "UTL_AddTgDreT";
	START_LAPTIMER(413);
	UTL_AddTgDreT( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(413);
}
void _UTL_AddTgDreTOff( TgHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[414] = "UTL_AddTgDreTOff";
	START_LAPTIMER(414);
	UTL_AddTgDreTOff( arg1, arg2, arg3);
	STOP_LAPTIMER(414);
}
void _UTL_AddTgDrzPulseWidth( TgHandle arg1, RadioButton arg2, DSlider arg3)
{
	MCI_LIST[415] = "UTL_AddTgDrzPulseWidth";
	START_LAPTIMER(415);
	UTL_AddTgDrzPulseWidth( arg1, arg2, arg3);
	STOP_LAPTIMER(415);
}
void _UTL_AddTgDreLOffset( TgHandle arg1, RadioButton arg2, DSlider arg3)
{
	MCI_LIST[416] = "UTL_AddTgDreLOffset";
	START_LAPTIMER(416);
	UTL_AddTgDreLOffset( arg1, arg2, arg3);
	STOP_LAPTIMER(416);
}
void _UTL_AddTgDreTOffset( TgHandle arg1, RadioButton arg2, DSlider arg3)
{
	MCI_LIST[417] = "UTL_AddTgDreTOffset";
	START_LAPTIMER(417);
	UTL_AddTgDreTOffset( arg1, arg2, arg3);
	STOP_LAPTIMER(417);
}
void _UTL_ClearTgHandle( TgHandle arg1)
{
	MCI_LIST[418] = "UTL_ClearTgHandle";
	START_LAPTIMER(418);
	UTL_ClearTgHandle( arg1);
	STOP_LAPTIMER(418);
}
void _UTL_SendTg( TgHandle arg1)
{
	MCI_LIST[419] = "UTL_SendTg";
	START_LAPTIMER(419);
	UTL_SendTg( arg1);
	STOP_LAPTIMER(419);
}
void _UTL_StartFrun()
{
	MCI_LIST[420] = "UTL_StartFrun";
	START_LAPTIMER(420);
	UTL_StartFrun();
	STOP_LAPTIMER(420);
}
void _UTL_StopFrun()
{
	MCI_LIST[421] = "UTL_StopFrun";
	START_LAPTIMER(421);
	UTL_StopFrun();
	STOP_LAPTIMER(421);
}
DSlider _UTL_ReadTgRate( RadioButton arg1, RadioButton arg2)
{
	MCI_LIST[422] = "UTL_ReadTgRate";
	START_LAPTIMER(422);
	DSlider retval = UTL_ReadTgRate( arg1, arg2);
	STOP_LAPTIMER(422);
	return retval;
}
DSlider _UTL_ReadTgAclk( RadioButton arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[423] = "UTL_ReadTgAclk";
	START_LAPTIMER(423);
	DSlider retval = UTL_ReadTgAclk( arg1, arg2, arg3);
	STOP_LAPTIMER(423);
	return retval;
}
CheckButton _UTL_ReadTgAclkOff( RadioButton arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[424] = "UTL_ReadTgAclkOff";
	START_LAPTIMER(424);
	CheckButton retval = UTL_ReadTgAclkOff( arg1, arg2, arg3);
	STOP_LAPTIMER(424);
	return retval;
}
DSlider _UTL_ReadTgBclk( RadioButton arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[425] = "UTL_ReadTgBclk";
	START_LAPTIMER(425);
	DSlider retval = UTL_ReadTgBclk( arg1, arg2, arg3);
	STOP_LAPTIMER(425);
	return retval;
}
CheckButton _UTL_ReadTgBclkOff( RadioButton arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[426] = "UTL_ReadTgBclkOff";
	START_LAPTIMER(426);
	CheckButton retval = UTL_ReadTgBclkOff( arg1, arg2, arg3);
	STOP_LAPTIMER(426);
	return retval;
}
DSlider _UTL_ReadTgCclk( RadioButton arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[427] = "UTL_ReadTgCclk";
	START_LAPTIMER(427);
	DSlider retval = UTL_ReadTgCclk( arg1, arg2, arg3);
	STOP_LAPTIMER(427);
	return retval;
}
CheckButton _UTL_ReadTgCclkOff( RadioButton arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[428] = "UTL_ReadTgCclkOff";
	START_LAPTIMER(428);
	CheckButton retval = UTL_ReadTgCclkOff( arg1, arg2, arg3);
	STOP_LAPTIMER(428);
	return retval;
}
DSlider _UTL_ReadTgDreL( RadioButton arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[429] = "UTL_ReadTgDreL";
	START_LAPTIMER(429);
	DSlider retval = UTL_ReadTgDreL( arg1, arg2, arg3);
	STOP_LAPTIMER(429);
	return retval;
}
CheckButton _UTL_ReadTgDreLOff( RadioButton arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[430] = "UTL_ReadTgDreLOff";
	START_LAPTIMER(430);
	CheckButton retval = UTL_ReadTgDreLOff( arg1, arg2, arg3);
	STOP_LAPTIMER(430);
	return retval;
}
DSlider _UTL_ReadTgDreT( RadioButton arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[431] = "UTL_ReadTgDreT";
	START_LAPTIMER(431);
	DSlider retval = UTL_ReadTgDreT( arg1, arg2, arg3);
	STOP_LAPTIMER(431);
	return retval;
}
CheckButton _UTL_ReadTgDreTOff( RadioButton arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[432] = "UTL_ReadTgDreTOff";
	START_LAPTIMER(432);
	CheckButton retval = UTL_ReadTgDreTOff( arg1, arg2, arg3);
	STOP_LAPTIMER(432);
	return retval;
}
DSlider _UTL_ReadTgStrb( RadioButton arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[433] = "UTL_ReadTgStrb";
	START_LAPTIMER(433);
	DSlider retval = UTL_ReadTgStrb( arg1, arg2, arg3);
	STOP_LAPTIMER(433);
	return retval;
}
CheckButton _UTL_ReadTgStrbOff( RadioButton arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[434] = "UTL_ReadTgStrbOff";
	START_LAPTIMER(434);
	CheckButton retval = UTL_ReadTgStrbOff( arg1, arg2, arg3);
	STOP_LAPTIMER(434);
	return retval;
}
TgAdjustHandle _UTL_GetTgAdjustHandle()
{
	MCI_LIST[435] = "UTL_GetTgAdjustHandle";
	START_LAPTIMER(435);
	TgAdjustHandle retval = UTL_GetTgAdjustHandle();
	STOP_LAPTIMER(435);
	return retval;
}
void _UTL_AddTgAdjustTargetDut( TgAdjustHandle arg1, UT_DUT arg2)
{
	MCI_LIST[436] = "UTL_AddTgAdjustTargetDut";
	START_LAPTIMER(436);
	UTL_AddTgAdjustTargetDut( arg1, arg2);
	STOP_LAPTIMER(436);
}
void _UTL_ClearTgAdjustTargetDut( TgAdjustHandle arg1)
{
	MCI_LIST[437] = "UTL_ClearTgAdjustTargetDut";
	START_LAPTIMER(437);
	UTL_ClearTgAdjustTargetDut( arg1);
	STOP_LAPTIMER(437);
}
void _UTL_AddTgAdjustTargetPin( TgAdjustHandle arg1, UT_PIN arg2)
{
	MCI_LIST[438] = "UTL_AddTgAdjustTargetPin";
	START_LAPTIMER(438);
	UTL_AddTgAdjustTargetPin( arg1, arg2);
	STOP_LAPTIMER(438);
}
void _UTL_ClearTgAdjustTargetPin( TgAdjustHandle arg1)
{
	MCI_LIST[439] = "UTL_ClearTgAdjustTargetPin";
	START_LAPTIMER(439);
	UTL_ClearTgAdjustTargetPin( arg1);
	STOP_LAPTIMER(439);
}
void _UTL_SetTgAdjustTargetTgType( TgAdjustHandle arg1, RadioButton arg2)
{
	MCI_LIST[440] = "UTL_SetTgAdjustTargetTgType";
	START_LAPTIMER(440);
	UTL_SetTgAdjustTargetTgType( arg1, arg2);
	STOP_LAPTIMER(440);
}
void _UTL_AddTgAdjustTargetEdge( TgAdjustHandle arg1, RadioButton arg2)
{
	MCI_LIST[441] = "UTL_AddTgAdjustTargetEdge";
	START_LAPTIMER(441);
	UTL_AddTgAdjustTargetEdge( arg1, arg2);
	STOP_LAPTIMER(441);
}
void _UTL_ClearTgAdjustTargetEdge( TgAdjustHandle arg1)
{
	MCI_LIST[442] = "UTL_ClearTgAdjustTargetEdge";
	START_LAPTIMER(442);
	UTL_ClearTgAdjustTargetEdge( arg1);
	STOP_LAPTIMER(442);
}
void _UTL_AddTgAdjustTargetBank( TgAdjustHandle arg1, RadioButton arg2)
{
	MCI_LIST[443] = "UTL_AddTgAdjustTargetBank";
	START_LAPTIMER(443);
	UTL_AddTgAdjustTargetBank( arg1, arg2);
	STOP_LAPTIMER(443);
}
void _UTL_ClearTgAdjustTargetBank( TgAdjustHandle arg1)
{
	MCI_LIST[444] = "UTL_ClearTgAdjustTargetBank";
	START_LAPTIMER(444);
	UTL_ClearTgAdjustTargetBank( arg1);
	STOP_LAPTIMER(444);
}
void _UTL_SetTgAdjustValue( TgAdjustHandle arg1, DSlider arg2)
{
	MCI_LIST[445] = "UTL_SetTgAdjustValue";
	START_LAPTIMER(445);
	UTL_SetTgAdjustValue( arg1, arg2);
	STOP_LAPTIMER(445);
}
void _UTL_SendTgAdjust( TgAdjustHandle arg1)
{
	MCI_LIST[446] = "UTL_SendTgAdjust";
	START_LAPTIMER(446);
	UTL_SendTgAdjust( arg1);
	STOP_LAPTIMER(446);
}
void _UTL_ResetTgAdjust( TgAdjustHandle arg1)
{
	MCI_LIST[447] = "UTL_ResetTgAdjust";
	START_LAPTIMER(447);
	UTL_ResetTgAdjust( arg1);
	STOP_LAPTIMER(447);
}
TgBaseRateHandle _UTL_GetTgBaseRateHandle()
{
	MCI_LIST[448] = "UTL_GetTgBaseRateHandle";
	START_LAPTIMER(448);
	TgBaseRateHandle retval = UTL_GetTgBaseRateHandle();
	STOP_LAPTIMER(448);
	return retval;
}
void _UTL_SetTgBaseRate( TgBaseRateHandle arg1, DSlider arg2)
{
	MCI_LIST[449] = "UTL_SetTgBaseRate";
	START_LAPTIMER(449);
	UTL_SetTgBaseRate( arg1, arg2);
	STOP_LAPTIMER(449);
}
void _UTL_SendTgBaseRate( TgBaseRateHandle arg1)
{
	MCI_LIST[450] = "UTL_SendTgBaseRate";
	START_LAPTIMER(450);
	UTL_SendTgBaseRate( arg1);
	STOP_LAPTIMER(450);
}
TgFixedDelayEdgeHandle _UTL_GetTgFixedDelayEdgeHandle()
{
	MCI_LIST[451] = "UTL_GetTgFixedDelayEdgeHandle";
	START_LAPTIMER(451);
	TgFixedDelayEdgeHandle retval = UTL_GetTgFixedDelayEdgeHandle();
	STOP_LAPTIMER(451);
	return retval;
}
void _UTL_AddTgFixedDelayEdgeTargetPin( TgFixedDelayEdgeHandle arg1, UT_PIN arg2)
{
	MCI_LIST[452] = "UTL_AddTgFixedDelayEdgeTargetPin";
	START_LAPTIMER(452);
	UTL_AddTgFixedDelayEdgeTargetPin( arg1, arg2);
	STOP_LAPTIMER(452);
}
void _UTL_ClearTgFixedDelayEdgeTargetPin( TgFixedDelayEdgeHandle arg1)
{
	MCI_LIST[453] = "UTL_ClearTgFixedDelayEdgeTargetPin";
	START_LAPTIMER(453);
	UTL_ClearTgFixedDelayEdgeTargetPin( arg1);
	STOP_LAPTIMER(453);
}
void _UTL_AddTgFixedDelayEdgeTargetTs( TgFixedDelayEdgeHandle arg1, RadioButton arg2)
{
	MCI_LIST[454] = "UTL_AddTgFixedDelayEdgeTargetTs";
	START_LAPTIMER(454);
	UTL_AddTgFixedDelayEdgeTargetTs( arg1, arg2);
	STOP_LAPTIMER(454);
}
void _UTL_ClearTgFixedDelayEdgeTargetTs( TgFixedDelayEdgeHandle arg1)
{
	MCI_LIST[455] = "UTL_ClearTgFixedDelayEdgeTargetTs";
	START_LAPTIMER(455);
	UTL_ClearTgFixedDelayEdgeTargetTs( arg1);
	STOP_LAPTIMER(455);
}
void _UTL_SetTgFixedDelayEdgeValue( TgFixedDelayEdgeHandle arg1, DSlider arg2)
{
	MCI_LIST[456] = "UTL_SetTgFixedDelayEdgeValue";
	START_LAPTIMER(456);
	UTL_SetTgFixedDelayEdgeValue( arg1, arg2);
	STOP_LAPTIMER(456);
}
void _UTL_SendTgFixedDelayEdge( TgFixedDelayEdgeHandle arg1)
{
	MCI_LIST[457] = "UTL_SendTgFixedDelayEdge";
	START_LAPTIMER(457);
	UTL_SendTgFixedDelayEdge( arg1);
	STOP_LAPTIMER(457);
}
void _UTL_ResetTgFixedDelayEdge()
{
	MCI_LIST[458] = "UTL_ResetTgFixedDelayEdge";
	START_LAPTIMER(458);
	UTL_ResetTgFixedDelayEdge();
	STOP_LAPTIMER(458);
}
MpatSelectorHandle _UTL_GetMpatSelectorHandle()
{
	MCI_LIST[459] = "UTL_GetMpatSelectorHandle";
	START_LAPTIMER(459);
	MpatSelectorHandle retval = UTL_GetMpatSelectorHandle();
	STOP_LAPTIMER(459);
	return retval;
}
void _UTL_AddMpatSelector( MpatSelectorHandle arg1, char * arg2, char * arg3)
{
	MCI_LIST[460] = "UTL_AddMpatSelector";
	START_LAPTIMER(460);
	UTL_AddMpatSelector( arg1, arg2, arg3);
	STOP_LAPTIMER(460);
}
void _UTL_ClearMpatSelector( MpatSelectorHandle arg1)
{
	MCI_LIST[461] = "UTL_ClearMpatSelector";
	START_LAPTIMER(461);
	UTL_ClearMpatSelector( arg1);
	STOP_LAPTIMER(461);
}
void _UTL_SendMpatSelector( MpatSelectorHandle arg1)
{
	MCI_LIST[462] = "UTL_SendMpatSelector";
	START_LAPTIMER(462);
	UTL_SendMpatSelector( arg1);
	STOP_LAPTIMER(462);
}
void _UTL_UpdateMpatSelector( MpatSelectorHandle arg1)
{
	MCI_LIST[463] = "UTL_UpdateMpatSelector";
	START_LAPTIMER(463);
	UTL_UpdateMpatSelector( arg1);
	STOP_LAPTIMER(463);
}
MpatSelectorCursor _UTL_GetMpatSelectorCursor( MpatSelectorHandle arg1)
{
	MCI_LIST[464] = "UTL_GetMpatSelectorCursor";
	START_LAPTIMER(464);
	MpatSelectorCursor retval = UTL_GetMpatSelectorCursor( arg1);
	STOP_LAPTIMER(464);
	return retval;
}
MpatSelector * _UTL_NextMpatSelector( MpatSelectorCursor arg1)
{
	MCI_LIST[465] = "UTL_NextMpatSelector";
	START_LAPTIMER(465);
	MpatSelector * retval = UTL_NextMpatSelector( arg1);
	STOP_LAPTIMER(465);
	return retval;
}
AddrScramHandle _UTL_GetAddrScramHandle()
{
	MCI_LIST[466] = "UTL_GetAddrScramHandle";
	START_LAPTIMER(466);
	AddrScramHandle retval = UTL_GetAddrScramHandle();
	STOP_LAPTIMER(466);
	return retval;
}
void _UTL_SetAddrScramMode( AddrScramHandle arg1, RadioButton arg2)
{
	MCI_LIST[467] = "UTL_SetAddrScramMode";
	START_LAPTIMER(467);
	UTL_SetAddrScramMode( arg1, arg2);
	STOP_LAPTIMER(467);
}
void _UTL_SetAddrScramFileName( AddrScramHandle arg1, char * arg2)
{
	MCI_LIST[468] = "UTL_SetAddrScramFileName";
	START_LAPTIMER(468);
	UTL_SetAddrScramFileName( arg1, arg2);
	STOP_LAPTIMER(468);
}
void _UTL_SetAddrScramAddrAssign( AddrScramHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[469] = "UTL_SetAddrScramAddrAssign";
	START_LAPTIMER(469);
	UTL_SetAddrScramAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(469);
}
void _UTL_SetAddrScramAlpgUnit( AddrScramHandle arg1, RadioButton arg2)
{
	MCI_LIST[470] = "UTL_SetAddrScramAlpgUnit";
	START_LAPTIMER(470);
	UTL_SetAddrScramAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(470);
}
void _UTL_SetAddrScramEnableBit( AddrScramHandle arg1, RadioButton arg2, USlider arg3, RadioButton arg4)
{
	MCI_LIST[471] = "UTL_SetAddrScramEnableBit";
	START_LAPTIMER(471);
	UTL_SetAddrScramEnableBit( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(471);
}
void _UTL_SetAddrScramSeparateMode( AddrScramHandle arg1, CheckButton arg2)
{
	MCI_LIST[472] = "UTL_SetAddrScramSeparateMode";
	START_LAPTIMER(472);
	UTL_SetAddrScramSeparateMode( arg1, arg2);
	STOP_LAPTIMER(472);
}
void _UTL_SetAddrScramSideSelect( AddrScramHandle arg1, RadioButton arg2)
{
	MCI_LIST[473] = "UTL_SetAddrScramSideSelect";
	START_LAPTIMER(473);
	UTL_SetAddrScramSideSelect( arg1, arg2);
	STOP_LAPTIMER(473);
}
void _UTL_SendPreScram( AddrScramHandle arg1)
{
	MCI_LIST[474] = "UTL_SendPreScram";
	START_LAPTIMER(474);
	UTL_SendPreScram( arg1);
	STOP_LAPTIMER(474);
}
void _UTL_SendAddrScram( AddrScramHandle arg1)
{
	MCI_LIST[475] = "UTL_SendAddrScram";
	START_LAPTIMER(475);
	UTL_SendAddrScram( arg1);
	STOP_LAPTIMER(475);
}
ScramConditionHandle _UTL_GetScramConditionHandle()
{
	MCI_LIST[476] = "UTL_GetScramConditionHandle";
	START_LAPTIMER(476);
	ScramConditionHandle retval = UTL_GetScramConditionHandle();
	STOP_LAPTIMER(476);
	return retval;
}
void _UTL_SetScramConditionAlpgUnit( ScramConditionHandle arg1, RadioButton arg2)
{
	MCI_LIST[477] = "UTL_SetScramConditionAlpgUnit";
	START_LAPTIMER(477);
	UTL_SetScramConditionAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(477);
}
void _UTL_SetScramConditionDivideMode( ScramConditionHandle arg1, RadioButton arg2)
{
	MCI_LIST[478] = "UTL_SetScramConditionDivideMode";
	START_LAPTIMER(478);
	UTL_SetScramConditionDivideMode( arg1, arg2);
	STOP_LAPTIMER(478);
}
void _UTL_SendScramCondition( ScramConditionHandle arg1)
{
	MCI_LIST[479] = "UTL_SendScramCondition";
	START_LAPTIMER(479);
	UTL_SendScramCondition( arg1);
	STOP_LAPTIMER(479);
}
PreScramConditionHandle _UTL_GetPreScramConditionHandle()
{
	MCI_LIST[480] = "UTL_GetPreScramConditionHandle";
	START_LAPTIMER(480);
	PreScramConditionHandle retval = UTL_GetPreScramConditionHandle();
	STOP_LAPTIMER(480);
	return retval;
}
void _UTL_SetPreScramConditionAddr( PreScramConditionHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[481] = "UTL_SetPreScramConditionAddr";
	START_LAPTIMER(481);
	UTL_SetPreScramConditionAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(481);
}
void _UTL_SetPreScramConditionAlpgUnit( PreScramConditionHandle arg1, RadioButton arg2)
{
	MCI_LIST[482] = "UTL_SetPreScramConditionAlpgUnit";
	START_LAPTIMER(482);
	UTL_SetPreScramConditionAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(482);
}
void _UTL_SetPreScramConditionMode( PreScramConditionHandle arg1, RadioButton arg2)
{
	MCI_LIST[483] = "UTL_SetPreScramConditionMode";
	START_LAPTIMER(483);
	UTL_SetPreScramConditionMode( arg1, arg2);
	STOP_LAPTIMER(483);
}
void _UTL_SetPreScramConditionMixMode( PreScramConditionHandle arg1, CheckButton arg2)
{
	MCI_LIST[484] = "UTL_SetPreScramConditionMixMode";
	START_LAPTIMER(484);
	UTL_SetPreScramConditionMixMode( arg1, arg2);
	STOP_LAPTIMER(484);
}
void _UTL_AddPreScramConditionWriteSignal( PreScramConditionHandle arg1, RadioButton arg2)
{
	MCI_LIST[485] = "UTL_AddPreScramConditionWriteSignal";
	START_LAPTIMER(485);
	UTL_AddPreScramConditionWriteSignal( arg1, arg2);
	STOP_LAPTIMER(485);
}
void _UTL_ClearPreScramConditionWriteSignal( PreScramConditionHandle arg1)
{
	MCI_LIST[486] = "UTL_ClearPreScramConditionWriteSignal";
	START_LAPTIMER(486);
	UTL_ClearPreScramConditionWriteSignal( arg1);
	STOP_LAPTIMER(486);
}
void _UTL_SendPreScramCondition( PreScramConditionHandle arg1)
{
	MCI_LIST[487] = "UTL_SendPreScramCondition";
	START_LAPTIMER(487);
	UTL_SendPreScramCondition( arg1);
	STOP_LAPTIMER(487);
}
BurstScramHandle _UTL_GetBurstScramHandle()
{
	MCI_LIST[488] = "UTL_GetBurstScramHandle";
	START_LAPTIMER(488);
	BurstScramHandle retval = UTL_GetBurstScramHandle();
	STOP_LAPTIMER(488);
	return retval;
}
void _UTL_SetBurstScramMode( BurstScramHandle arg1, CheckButton arg2)
{
	MCI_LIST[489] = "UTL_SetBurstScramMode";
	START_LAPTIMER(489);
	UTL_SetBurstScramMode( arg1, arg2);
	STOP_LAPTIMER(489);
}
void _UTL_SetBurstScramDdrType( BurstScramHandle arg1, RadioButton arg2)
{
	MCI_LIST[490] = "UTL_SetBurstScramDdrType";
	START_LAPTIMER(490);
	UTL_SetBurstScramDdrType( arg1, arg2);
	STOP_LAPTIMER(490);
}
void _UTL_SetBurstScramBaseFileName( BurstScramHandle arg1, char * arg2)
{
	MCI_LIST[491] = "UTL_SetBurstScramBaseFileName";
	START_LAPTIMER(491);
	UTL_SetBurstScramBaseFileName( arg1, arg2);
	STOP_LAPTIMER(491);
}
void _UTL_SetBurstScramDataRate( BurstScramHandle arg1, USlider arg2)
{
	MCI_LIST[492] = "UTL_SetBurstScramDataRate";
	START_LAPTIMER(492);
	UTL_SetBurstScramDataRate( arg1, arg2);
	STOP_LAPTIMER(492);
}
void _UTL_SetBurstScramLength( BurstScramHandle arg1, USlider arg2)
{
	MCI_LIST[493] = "UTL_SetBurstScramLength";
	START_LAPTIMER(493);
	UTL_SetBurstScramLength( arg1, arg2);
	STOP_LAPTIMER(493);
}
void _UTL_SetBurstScramWrapType( BurstScramHandle arg1, RadioButton arg2)
{
	MCI_LIST[494] = "UTL_SetBurstScramWrapType";
	START_LAPTIMER(494);
	UTL_SetBurstScramWrapType( arg1, arg2);
	STOP_LAPTIMER(494);
}
void _UTL_AddBurstScramWriteSignal( BurstScramHandle arg1, RadioButton arg2)
{
	MCI_LIST[495] = "UTL_AddBurstScramWriteSignal";
	START_LAPTIMER(495);
	UTL_AddBurstScramWriteSignal( arg1, arg2);
	STOP_LAPTIMER(495);
}
void _UTL_ClearBurstScramWriteSignal( BurstScramHandle arg1)
{
	MCI_LIST[496] = "UTL_ClearBurstScramWriteSignal";
	START_LAPTIMER(496);
	UTL_ClearBurstScramWriteSignal( arg1);
	STOP_LAPTIMER(496);
}
void _UTL_SetBurstScramAddrUnit( BurstScramHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[497] = "UTL_SetBurstScramAddrUnit";
	START_LAPTIMER(497);
	UTL_SetBurstScramAddrUnit( arg1, arg2, arg3);
	STOP_LAPTIMER(497);
}
void _UTL_SetBurstScramBankAddrLoadUnit( BurstScramHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[498] = "UTL_SetBurstScramBankAddrLoadUnit";
	START_LAPTIMER(498);
	UTL_SetBurstScramBankAddrLoadUnit( arg1, arg2, arg3);
	STOP_LAPTIMER(498);
}
void _UTL_SendBurstScram( BurstScramHandle arg1)
{
	MCI_LIST[499] = "UTL_SendBurstScram";
	START_LAPTIMER(499);
	UTL_SendBurstScram( arg1);
	STOP_LAPTIMER(499);
}
void _UTL_WriteRegUs( RadioButton arg1, USlider * arg2, int arg3, RadioButton arg4)
{
	MCI_LIST[500] = "UTL_WriteRegUs";
	START_LAPTIMER(500);
	UTL_WriteRegUs( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(500);
}
RegHandle _UTL_GetRegHandle()
{
	MCI_LIST[501] = "UTL_GetRegHandle";
	START_LAPTIMER(501);
	RegHandle retval = UTL_GetRegHandle();
	STOP_LAPTIMER(501);
	return retval;
}
void _UTL_ClearRegHandle( RegHandle arg1)
{
	MCI_LIST[502] = "UTL_ClearRegHandle";
	START_LAPTIMER(502);
	UTL_ClearRegHandle( arg1);
	STOP_LAPTIMER(502);
}
void _UTL_SetRegDirection( RegHandle arg1, RadioButton arg2)
{
	MCI_LIST[503] = "UTL_SetRegDirection";
	START_LAPTIMER(503);
	UTL_SetRegDirection( arg1, arg2);
	STOP_LAPTIMER(503);
}
void _UTL_SetRegUs( RegHandle arg1, RadioButton arg2, RadioButton arg3, USlider arg4)
{
	MCI_LIST[504] = "UTL_SetRegUs";
	START_LAPTIMER(504);
	UTL_SetRegUs( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(504);
}
void _UTL_SetRegRb( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[505] = "UTL_SetRegRb";
	START_LAPTIMER(505);
	UTL_SetRegRb( arg1, arg2, arg3);
	STOP_LAPTIMER(505);
}
void _UTL_SetRegBar1( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[506] = "UTL_SetRegBar1";
	START_LAPTIMER(506);
	UTL_SetRegBar1( arg1, arg2, arg3);
	STOP_LAPTIMER(506);
}
void _UTL_SetRegJar( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[507] = "UTL_SetRegJar";
	START_LAPTIMER(507);
	UTL_SetRegJar( arg1, arg2, arg3);
	STOP_LAPTIMER(507);
}
void _UTL_SetRegDre1( RegHandle arg1, RadioButton arg2)
{
	MCI_LIST[508] = "UTL_SetRegDre1";
	START_LAPTIMER(508);
	UTL_SetRegDre1( arg1, arg2);
	STOP_LAPTIMER(508);
}
void _UTL_SetRegDre2( RegHandle arg1, RadioButton arg2)
{
	MCI_LIST[509] = "UTL_SetRegDre2";
	START_LAPTIMER(509);
	UTL_SetRegDre2( arg1, arg2);
	STOP_LAPTIMER(509);
}
void _UTL_SetRegCpe1( RegHandle arg1, RadioButton arg2)
{
	MCI_LIST[510] = "UTL_SetRegCpe1";
	START_LAPTIMER(510);
	UTL_SetRegCpe1( arg1, arg2);
	STOP_LAPTIMER(510);
}
void _UTL_SetRegCpe2( RegHandle arg1, RadioButton arg2)
{
	MCI_LIST[511] = "UTL_SetRegCpe2";
	START_LAPTIMER(511);
	UTL_SetRegCpe2( arg1, arg2);
	STOP_LAPTIMER(511);
}
void _UTL_SetRegIdx1( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[512] = "UTL_SetRegIdx1";
	START_LAPTIMER(512);
	UTL_SetRegIdx1( arg1, arg2, arg3);
	STOP_LAPTIMER(512);
}
void _UTL_SetRegIdx2( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[513] = "UTL_SetRegIdx2";
	START_LAPTIMER(513);
	UTL_SetRegIdx2( arg1, arg2, arg3);
	STOP_LAPTIMER(513);
}
void _UTL_SetRegIdx3( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[514] = "UTL_SetRegIdx3";
	START_LAPTIMER(514);
	UTL_SetRegIdx3( arg1, arg2, arg3);
	STOP_LAPTIMER(514);
}
void _UTL_SetRegIdx4( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[515] = "UTL_SetRegIdx4";
	START_LAPTIMER(515);
	UTL_SetRegIdx4( arg1, arg2, arg3);
	STOP_LAPTIMER(515);
}
void _UTL_SetRegIdx5( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[516] = "UTL_SetRegIdx5";
	START_LAPTIMER(516);
	UTL_SetRegIdx5( arg1, arg2, arg3);
	STOP_LAPTIMER(516);
}
void _UTL_SetRegIdx6( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[517] = "UTL_SetRegIdx6";
	START_LAPTIMER(517);
	UTL_SetRegIdx6( arg1, arg2, arg3);
	STOP_LAPTIMER(517);
}
void _UTL_SetRegIdx7( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[518] = "UTL_SetRegIdx7";
	START_LAPTIMER(518);
	UTL_SetRegIdx7( arg1, arg2, arg3);
	STOP_LAPTIMER(518);
}
void _UTL_SetRegIdx8( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[519] = "UTL_SetRegIdx8";
	START_LAPTIMER(519);
	UTL_SetRegIdx8( arg1, arg2, arg3);
	STOP_LAPTIMER(519);
}
void _UTL_SetRegXmax( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[520] = "UTL_SetRegXmax";
	START_LAPTIMER(520);
	UTL_SetRegXmax( arg1, arg2, arg3);
	STOP_LAPTIMER(520);
}
void _UTL_SetRegYmax( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[521] = "UTL_SetRegYmax";
	START_LAPTIMER(521);
	UTL_SetRegYmax( arg1, arg2, arg3);
	STOP_LAPTIMER(521);
}
void _UTL_SetRegZmax( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[522] = "UTL_SetRegZmax";
	START_LAPTIMER(522);
	UTL_SetRegZmax( arg1, arg2, arg3);
	STOP_LAPTIMER(522);
}
void _UTL_SetRegLmax( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[523] = "UTL_SetRegLmax";
	START_LAPTIMER(523);
	UTL_SetRegLmax( arg1, arg2, arg3);
	STOP_LAPTIMER(523);
}
void _UTL_SetRegHmax( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[524] = "UTL_SetRegHmax";
	START_LAPTIMER(524);
	UTL_SetRegHmax( arg1, arg2, arg3);
	STOP_LAPTIMER(524);
}
void _UTL_SetRegXh( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[525] = "UTL_SetRegXh";
	START_LAPTIMER(525);
	UTL_SetRegXh( arg1, arg2, arg3);
	STOP_LAPTIMER(525);
}
void _UTL_SetRegYh( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[526] = "UTL_SetRegYh";
	START_LAPTIMER(526);
	UTL_SetRegYh( arg1, arg2, arg3);
	STOP_LAPTIMER(526);
}
void _UTL_SetRegZh( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[527] = "UTL_SetRegZh";
	START_LAPTIMER(527);
	UTL_SetRegZh( arg1, arg2, arg3);
	STOP_LAPTIMER(527);
}
void _UTL_SetRegD1( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[528] = "UTL_SetRegD1";
	START_LAPTIMER(528);
	UTL_SetRegD1( arg1, arg2, arg3);
	STOP_LAPTIMER(528);
}
void _UTL_SetRegD2( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[529] = "UTL_SetRegD2";
	START_LAPTIMER(529);
	UTL_SetRegD2( arg1, arg2, arg3);
	STOP_LAPTIMER(529);
}
void _UTL_SetRegD3( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[530] = "UTL_SetRegD3";
	START_LAPTIMER(530);
	UTL_SetRegD3( arg1, arg2, arg3);
	STOP_LAPTIMER(530);
}
void _UTL_SetRegD4( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[531] = "UTL_SetRegD4";
	START_LAPTIMER(531);
	UTL_SetRegD4( arg1, arg2, arg3);
	STOP_LAPTIMER(531);
}
void _UTL_SetRegDsd( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[532] = "UTL_SetRegDsd";
	START_LAPTIMER(532);
	UTL_SetRegDsd( arg1, arg2, arg3);
	STOP_LAPTIMER(532);
}
void _UTL_SetRegTph( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[533] = "UTL_SetRegTph";
	START_LAPTIMER(533);
	UTL_SetRegTph( arg1, arg2, arg3);
	STOP_LAPTIMER(533);
}
void _UTL_SetRegDcmr( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[534] = "UTL_SetRegDcmr";
	START_LAPTIMER(534);
	UTL_SetRegDcmr( arg1, arg2, arg3);
	STOP_LAPTIMER(534);
}
void _UTL_SetRegCd( RegHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[535] = "UTL_SetRegCd";
	START_LAPTIMER(535);
	UTL_SetRegCd( arg1, arg2, arg3);
	STOP_LAPTIMER(535);
}
void _UTL_SetRegAlpgUnit( RegHandle arg1, RadioButton arg2)
{
	MCI_LIST[536] = "UTL_SetRegAlpgUnit";
	START_LAPTIMER(536);
	UTL_SetRegAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(536);
}
void _UTL_SetRegTimerCycleCnt( RegHandle arg1, RadioButton arg2, RadioButton arg3, USlider arg4)
{
	MCI_LIST[537] = "UTL_SetRegTimerCycleCnt";
	START_LAPTIMER(537);
	UTL_SetRegTimerCycleCnt( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(537);
}
void _UTL_SetRegTimerTime( RegHandle arg1, RadioButton arg2, double arg3)
{
	MCI_LIST[538] = "UTL_SetRegTimerTime";
	START_LAPTIMER(538);
	UTL_SetRegTimerTime( arg1, arg2, arg3);
	STOP_LAPTIMER(538);
}
void _UTL_SetRegUpdateUnitNumber( RegHandle arg1, RadioButton arg2)
{
	MCI_LIST[539] = "UTL_SetRegUpdateUnitNumber";
	START_LAPTIMER(539);
	UTL_SetRegUpdateUnitNumber( arg1, arg2);
	STOP_LAPTIMER(539);
}
void _UTL_SendReg( RegHandle arg1)
{
	MCI_LIST[540] = "UTL_SendReg";
	START_LAPTIMER(540);
	UTL_SendReg( arg1);
	STOP_LAPTIMER(540);
}
void _UTL_ResetReg( RegHandle arg1)
{
	MCI_LIST[541] = "UTL_ResetReg";
	START_LAPTIMER(541);
	UTL_ResetReg( arg1);
	STOP_LAPTIMER(541);
}
USlider _UTL_ReadUSRegister( RadioButton arg1, RadioButton arg2)
{
	MCI_LIST[542] = "UTL_ReadUSRegister";
	START_LAPTIMER(542);
	USlider retval = UTL_ReadUSRegister( arg1, arg2);
	STOP_LAPTIMER(542);
	return retval;
}
RadioButton _UTL_ReadRBRegister( RadioButton arg1)
{
	MCI_LIST[543] = "UTL_ReadRBRegister";
	START_LAPTIMER(543);
	RadioButton retval = UTL_ReadRBRegister( arg1);
	STOP_LAPTIMER(543);
	return retval;
}
RegMemoryHandle _UTL_GetRegMemoryHandle()
{
	MCI_LIST[544] = "UTL_GetRegMemoryHandle";
	START_LAPTIMER(544);
	RegMemoryHandle retval = UTL_GetRegMemoryHandle();
	STOP_LAPTIMER(544);
	return retval;
}
void _UTL_SetRegMemoryTarget( RegMemoryHandle arg1, RadioButton arg2)
{
	MCI_LIST[545] = "UTL_SetRegMemoryTarget";
	START_LAPTIMER(545);
	UTL_SetRegMemoryTarget( arg1, arg2);
	STOP_LAPTIMER(545);
}
void _UTL_SetRegMemoryStartAddr( RegMemoryHandle arg1, USlider arg2)
{
	MCI_LIST[546] = "UTL_SetRegMemoryStartAddr";
	START_LAPTIMER(546);
	UTL_SetRegMemoryStartAddr( arg1, arg2);
	STOP_LAPTIMER(546);
}
void _UTL_SetRegMemoryStopAddr( RegMemoryHandle arg1, USlider arg2)
{
	MCI_LIST[547] = "UTL_SetRegMemoryStopAddr";
	START_LAPTIMER(547);
	UTL_SetRegMemoryStopAddr( arg1, arg2);
	STOP_LAPTIMER(547);
}
void _UTL_WriteRegMemory( RegMemoryHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[548] = "UTL_WriteRegMemory";
	START_LAPTIMER(548);
	UTL_WriteRegMemory( arg1, arg2, arg3);
	STOP_LAPTIMER(548);
}
TimerModeHandle _UTL_GetTimerModeHandle()
{
	MCI_LIST[549] = "UTL_GetTimerModeHandle";
	START_LAPTIMER(549);
	TimerModeHandle retval = UTL_GetTimerModeHandle();
	STOP_LAPTIMER(549);
	return retval;
}
void _UTL_AddTimerMode( TimerModeHandle  arg1, RadioButton  arg2, RadioButton  arg3)
{
	MCI_LIST[550] = "UTL_AddTimerMode";
	START_LAPTIMER(550);
	UTL_AddTimerMode( arg1, arg2, arg3);
	STOP_LAPTIMER(550);
}
void _UTL_SetTimerModeDirection( TimerModeHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[551] = "UTL_SetTimerModeDirection";
	START_LAPTIMER(551);
	UTL_SetTimerModeDirection( arg1, arg2);
	STOP_LAPTIMER(551);
}
void _UTL_SendTimerMode( TimerModeHandle  arg1)
{
	MCI_LIST[552] = "UTL_SendTimerMode";
	START_LAPTIMER(552);
	UTL_SendTimerMode( arg1);
	STOP_LAPTIMER(552);
}
IdxModeHandle _UTL_GetIdxModeHandle()
{
	MCI_LIST[553] = "UTL_GetIdxModeHandle";
	START_LAPTIMER(553);
	IdxModeHandle retval = UTL_GetIdxModeHandle();
	STOP_LAPTIMER(553);
	return retval;
}
void _UTL_SetIdxMode( IdxModeHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[554] = "UTL_SetIdxMode";
	START_LAPTIMER(554);
	UTL_SetIdxMode( arg1, arg2);
	STOP_LAPTIMER(554);
}
void _UTL_SendIdxMode( IdxModeHandle  arg1)
{
	MCI_LIST[555] = "UTL_SendIdxMode";
	START_LAPTIMER(555);
	UTL_SendIdxMode( arg1);
	STOP_LAPTIMER(555);
}
void _UTL_UpdateIdxMode( IdxModeHandle  arg1)
{
	MCI_LIST[556] = "UTL_UpdateIdxMode";
	START_LAPTIMER(556);
	UTL_UpdateIdxMode( arg1);
	STOP_LAPTIMER(556);
}
int _UTL_GetIdxMode( IdxModeHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[557] = "UTL_GetIdxMode";
	START_LAPTIMER(557);
	int retval = UTL_GetIdxMode( arg1, arg2);
	STOP_LAPTIMER(557);
	return retval;
}
ReadMpatPcHandle _UTL_GetReadMpatPcHandle()
{
	MCI_LIST[558] = "UTL_GetReadMpatPcHandle";
	START_LAPTIMER(558);
	ReadMpatPcHandle retval = UTL_GetReadMpatPcHandle();
	STOP_LAPTIMER(558);
	return retval;
}
void _UTL_SetReadMpatStartName( ReadMpatPcHandle arg1, char * arg2)
{
	MCI_LIST[559] = "UTL_SetReadMpatStartName";
	START_LAPTIMER(559);
	UTL_SetReadMpatStartName( arg1, arg2);
	STOP_LAPTIMER(559);
}
void _UTL_SetReadMpatLabelName( ReadMpatPcHandle arg1, char * arg2)
{
	MCI_LIST[560] = "UTL_SetReadMpatLabelName";
	START_LAPTIMER(560);
	UTL_SetReadMpatLabelName( arg1, arg2);
	STOP_LAPTIMER(560);
}
void _UTL_SetReadMpatModuleName( ReadMpatPcHandle arg1, char * arg2)
{
	MCI_LIST[561] = "UTL_SetReadMpatModuleName";
	START_LAPTIMER(561);
	UTL_SetReadMpatModuleName( arg1, arg2);
	STOP_LAPTIMER(561);
}
void _UTL_SetReadMpatFileName( ReadMpatPcHandle arg1, char * arg2)
{
	MCI_LIST[562] = "UTL_SetReadMpatFileName";
	START_LAPTIMER(562);
	UTL_SetReadMpatFileName( arg1, arg2);
	STOP_LAPTIMER(562);
}
RadioButton _UTL_ReadMpatStartPc( ReadMpatPcHandle arg1, USlider * arg2)
{
	MCI_LIST[563] = "UTL_ReadMpatStartPc";
	START_LAPTIMER(563);
	RadioButton retval = UTL_ReadMpatStartPc( arg1, arg2);
	STOP_LAPTIMER(563);
	return retval;
}
RadioButton _UTL_ReadMpatLabelPc( ReadMpatPcHandle arg1, USlider * arg2)
{
	MCI_LIST[564] = "UTL_ReadMpatLabelPc";
	START_LAPTIMER(564);
	RadioButton retval = UTL_ReadMpatLabelPc( arg1, arg2);
	STOP_LAPTIMER(564);
	return retval;
}
AriramHandle _UTL_GetAriramHandle()
{
	MCI_LIST[565] = "UTL_GetAriramHandle";
	START_LAPTIMER(565);
	AriramHandle retval = UTL_GetAriramHandle();
	STOP_LAPTIMER(565);
	return retval;
}
void _UTL_SetAriramAlpgUnit( AriramHandle arg1, RadioButton arg2)
{
	MCI_LIST[566] = "UTL_SetAriramAlpgUnit";
	START_LAPTIMER(566);
	UTL_SetAriramAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(566);
}
void _UTL_SetAriramMode( AriramHandle arg1, RadioButton arg2)
{
	MCI_LIST[567] = "UTL_SetAriramMode";
	START_LAPTIMER(567);
	UTL_SetAriramMode( arg1, arg2);
	STOP_LAPTIMER(567);
}
void _UTL_SendAriram( AriramHandle arg1)
{
	MCI_LIST[568] = "UTL_SendAriram";
	START_LAPTIMER(568);
	UTL_SendAriram( arg1);
	STOP_LAPTIMER(568);
}
PdsDataHandle _UTL_GetPdsDataHandle()
{
	MCI_LIST[569] = "UTL_GetPdsDataHandle";
	START_LAPTIMER(569);
	PdsDataHandle retval = UTL_GetPdsDataHandle();
	STOP_LAPTIMER(569);
	return retval;
}
void _UTL_SetPdsDataAlpgUnit( PdsDataHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[570] = "UTL_SetPdsDataAlpgUnit";
	START_LAPTIMER(570);
	UTL_SetPdsDataAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(570);
}
void _UTL_SetPdsDataDirection( PdsDataHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[571] = "UTL_SetPdsDataDirection";
	START_LAPTIMER(571);
	UTL_SetPdsDataDirection( arg1, arg2);
	STOP_LAPTIMER(571);
}
void _UTL_SetPdsDataPdsUnit( PdsDataHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[572] = "UTL_SetPdsDataPdsUnit";
	START_LAPTIMER(572);
	UTL_SetPdsDataPdsUnit( arg1, arg2);
	STOP_LAPTIMER(572);
}
void _UTL_SetPdsDataSelectorDa( PdsDataHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[573] = "UTL_SetPdsDataSelectorDa";
	START_LAPTIMER(573);
	UTL_SetPdsDataSelectorDa( arg1, arg2);
	STOP_LAPTIMER(573);
}
void _UTL_SetPdsDataSelectorDb( PdsDataHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[574] = "UTL_SetPdsDataSelectorDb";
	START_LAPTIMER(574);
	UTL_SetPdsDataSelectorDb( arg1, arg2);
	STOP_LAPTIMER(574);
}
void _UTL_SendPdsData( PdsDataHandle  arg1)
{
	MCI_LIST[575] = "UTL_SendPdsData";
	START_LAPTIMER(575);
	UTL_SendPdsData( arg1);
	STOP_LAPTIMER(575);
}
PatDelayHandle _UTL_GetPatDelayHandle()
{
	MCI_LIST[576] = "UTL_GetPatDelayHandle";
	START_LAPTIMER(576);
	PatDelayHandle retval = UTL_GetPatDelayHandle();
	STOP_LAPTIMER(576);
	return retval;
}
void _UTL_AddPatDelayCycle( PatDelayHandle  arg1, RadioButton  arg2, USlider  arg3)
{
	MCI_LIST[577] = "UTL_AddPatDelayCycle";
	START_LAPTIMER(577);
	UTL_AddPatDelayCycle( arg1, arg2, arg3);
	STOP_LAPTIMER(577);
}
void _UTL_SetPatDelayAlpgUnit( PatDelayHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[578] = "UTL_SetPatDelayAlpgUnit";
	START_LAPTIMER(578);
	UTL_SetPatDelayAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(578);
}
void _UTL_SendPatDelay( PatDelayHandle  arg1)
{
	MCI_LIST[579] = "UTL_SendPatDelay";
	START_LAPTIMER(579);
	UTL_SendPatDelay( arg1);
	STOP_LAPTIMER(579);
}
StrbFailCounterConditionHandle _UTL_GetStrbFailCounterConditionHandle()
{
	MCI_LIST[580] = "UTL_GetStrbFailCounterConditionHandle";
	START_LAPTIMER(580);
	StrbFailCounterConditionHandle retval = UTL_GetStrbFailCounterConditionHandle();
	STOP_LAPTIMER(580);
	return retval;
}
void _UTL_AddStrbFailCounterConditionStrbChannelAllDut( StrbFailCounterConditionHandle arg1, RadioButton arg2)
{
	MCI_LIST[581] = "UTL_AddStrbFailCounterConditionStrbChannelAllDut";
	START_LAPTIMER(581);
	UTL_AddStrbFailCounterConditionStrbChannelAllDut( arg1, arg2);
	STOP_LAPTIMER(581);
}
void _UTL_AddStrbFailCounterConditionStrbChannelByDut( StrbFailCounterConditionHandle arg1, UT_DUT arg2, RadioButton arg3)
{
	MCI_LIST[582] = "UTL_AddStrbFailCounterConditionStrbChannelByDut";
	START_LAPTIMER(582);
	UTL_AddStrbFailCounterConditionStrbChannelByDut( arg1, arg2, arg3);
	STOP_LAPTIMER(582);
}
void _UTL_ClearStrbFailCounterConditionStrbChannelAllDut( StrbFailCounterConditionHandle arg1)
{
	MCI_LIST[583] = "UTL_ClearStrbFailCounterConditionStrbChannelAllDut";
	START_LAPTIMER(583);
	UTL_ClearStrbFailCounterConditionStrbChannelAllDut( arg1);
	STOP_LAPTIMER(583);
}
void _UTL_ClearStrbFailCounterConditionStrbChannelByDut( StrbFailCounterConditionHandle arg1, UT_DUT arg2)
{
	MCI_LIST[584] = "UTL_ClearStrbFailCounterConditionStrbChannelByDut";
	START_LAPTIMER(584);
	UTL_ClearStrbFailCounterConditionStrbChannelByDut( arg1, arg2);
	STOP_LAPTIMER(584);
}
void _UTL_SetStrbFailCounterConditionFailStopAllDut( StrbFailCounterConditionHandle arg1, CheckButton arg2)
{
	MCI_LIST[585] = "UTL_SetStrbFailCounterConditionFailStopAllDut";
	START_LAPTIMER(585);
	UTL_SetStrbFailCounterConditionFailStopAllDut( arg1, arg2);
	STOP_LAPTIMER(585);
}
void _UTL_SetStrbFailCounterConditionFailStopByDut( StrbFailCounterConditionHandle arg1, UT_DUT arg2, CheckButton arg3)
{
	MCI_LIST[586] = "UTL_SetStrbFailCounterConditionFailStopByDut";
	START_LAPTIMER(586);
	UTL_SetStrbFailCounterConditionFailStopByDut( arg1, arg2, arg3);
	STOP_LAPTIMER(586);
}
void _UTL_SetStrbFailCounterConditionLimitAllDut( StrbFailCounterConditionHandle arg1, Slider arg2)
{
	MCI_LIST[587] = "UTL_SetStrbFailCounterConditionLimitAllDut";
	START_LAPTIMER(587);
	UTL_SetStrbFailCounterConditionLimitAllDut( arg1, arg2);
	STOP_LAPTIMER(587);
}
void _UTL_SetStrbFailCounterConditionLimitByDut( StrbFailCounterConditionHandle arg1, UT_DUT arg2, Slider arg3)
{
	MCI_LIST[588] = "UTL_SetStrbFailCounterConditionLimitByDut";
	START_LAPTIMER(588);
	UTL_SetStrbFailCounterConditionLimitByDut( arg1, arg2, arg3);
	STOP_LAPTIMER(588);
}
void _UTL_SetStrbFailCounterConditionPin( StrbFailCounterConditionHandle arg1, UT_PIN arg2)
{
	MCI_LIST[589] = "UTL_SetStrbFailCounterConditionPin";
	START_LAPTIMER(589);
	UTL_SetStrbFailCounterConditionPin( arg1, arg2);
	STOP_LAPTIMER(589);
}
void _UTL_SendStrbFailCounterCondition( StrbFailCounterConditionHandle arg1)
{
	MCI_LIST[590] = "UTL_SendStrbFailCounterCondition";
	START_LAPTIMER(590);
	UTL_SendStrbFailCounterCondition( arg1);
	STOP_LAPTIMER(590);
}
StrbFailCounterHandle _UTL_GetStrbFailCounterHandle()
{
	MCI_LIST[591] = "UTL_GetStrbFailCounterHandle";
	START_LAPTIMER(591);
	StrbFailCounterHandle retval = UTL_GetStrbFailCounterHandle();
	STOP_LAPTIMER(591);
	return retval;
}
void _UTL_SetStrbFailCounterPin( StrbFailCounterHandle arg1, UT_PIN arg2)
{
	MCI_LIST[592] = "UTL_SetStrbFailCounterPin";
	START_LAPTIMER(592);
	UTL_SetStrbFailCounterPin( arg1, arg2);
	STOP_LAPTIMER(592);
}
void _UTL_SetStrbFailCounterDut( StrbFailCounterHandle arg1, UT_DUT arg2)
{
	MCI_LIST[593] = "UTL_SetStrbFailCounterDut";
	START_LAPTIMER(593);
	UTL_SetStrbFailCounterDut( arg1, arg2);
	STOP_LAPTIMER(593);
}
void _UTL_UpdateStrbFailCounter( StrbFailCounterHandle arg1)
{
	MCI_LIST[594] = "UTL_UpdateStrbFailCounter";
	START_LAPTIMER(594);
	UTL_UpdateStrbFailCounter( arg1);
	STOP_LAPTIMER(594);
}
int _UTL_GetStrbFailCounterValue( StrbFailCounterHandle arg1, Slider * arg2)
{
	MCI_LIST[595] = "UTL_GetStrbFailCounterValue";
	START_LAPTIMER(595);
	int retval = UTL_GetStrbFailCounterValue( arg1, arg2);
	STOP_LAPTIMER(595);
	return retval;
}
int _UTL_GetStrbFailCounterMaxFail( StrbFailCounterHandle arg1, CheckButton * arg2)
{
	MCI_LIST[596] = "UTL_GetStrbFailCounterMaxFail";
	START_LAPTIMER(596);
	int retval = UTL_GetStrbFailCounterMaxFail( arg1, arg2);
	STOP_LAPTIMER(596);
	return retval;
}
PseudoRandomHandle _UTL_GetPseudoRandomHandle()
{
	MCI_LIST[597] = "UTL_GetPseudoRandomHandle";
	START_LAPTIMER(597);
	PseudoRandomHandle retval = UTL_GetPseudoRandomHandle();
	STOP_LAPTIMER(597);
	return retval;
}
void _UTL_SetPseudoRandomAlpgUnit( PseudoRandomHandle arg1, RadioButton arg2)
{
	MCI_LIST[598] = "UTL_SetPseudoRandomAlpgUnit";
	START_LAPTIMER(598);
	UTL_SetPseudoRandomAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(598);
}
void _UTL_SetPseudoRandomDirection( PseudoRandomHandle arg1, RadioButton arg2)
{
	MCI_LIST[599] = "UTL_SetPseudoRandomDirection";
	START_LAPTIMER(599);
	UTL_SetPseudoRandomDirection( arg1, arg2);
	STOP_LAPTIMER(599);
}
void _UTL_SetPseudoRandomGenerationMethod( PseudoRandomHandle arg1, RadioButton arg2)
{
	MCI_LIST[600] = "UTL_SetPseudoRandomGenerationMethod";
	START_LAPTIMER(600);
	UTL_SetPseudoRandomGenerationMethod( arg1, arg2);
	STOP_LAPTIMER(600);
}
void _UTL_SetPseudoRandomUpdateUnitNumber( PseudoRandomHandle arg1, RadioButton arg2)
{
	MCI_LIST[601] = "UTL_SetPseudoRandomUpdateUnitNumber";
	START_LAPTIMER(601);
	UTL_SetPseudoRandomUpdateUnitNumber( arg1, arg2);
	STOP_LAPTIMER(601);
}
void _UTL_AddPseudoRandomTermOfPolynomial( PseudoRandomHandle arg1, RadioButton arg2)
{
	MCI_LIST[602] = "UTL_AddPseudoRandomTermOfPolynomial";
	START_LAPTIMER(602);
	UTL_AddPseudoRandomTermOfPolynomial( arg1, arg2);
	STOP_LAPTIMER(602);
}
void _UTL_ClearPseudoRandomTermOfPolynomial( PseudoRandomHandle arg1)
{
	MCI_LIST[603] = "UTL_ClearPseudoRandomTermOfPolynomial";
	START_LAPTIMER(603);
	UTL_ClearPseudoRandomTermOfPolynomial( arg1);
	STOP_LAPTIMER(603);
}
void _UTL_ResetPseudoRandom( PseudoRandomHandle arg1)
{
	MCI_LIST[604] = "UTL_ResetPseudoRandom";
	START_LAPTIMER(604);
	UTL_ResetPseudoRandom( arg1);
	STOP_LAPTIMER(604);
}
void _UTL_SendPseudoRandom( PseudoRandomHandle arg1)
{
	MCI_LIST[605] = "UTL_SendPseudoRandom";
	START_LAPTIMER(605);
	UTL_SendPseudoRandom( arg1);
	STOP_LAPTIMER(605);
}
DcSwitchHandle _UTL_GetDcSwitchHandle()
{
	MCI_LIST[606] = "UTL_GetDcSwitchHandle";
	START_LAPTIMER(606);
	DcSwitchHandle retval = UTL_GetDcSwitchHandle();
	STOP_LAPTIMER(606);
	return retval;
}
void _UTL_SetDcSwitch( DcSwitchHandle arg1, RadioButton arg2)
{
	MCI_LIST[607] = "UTL_SetDcSwitch";
	START_LAPTIMER(607);
	UTL_SetDcSwitch( arg1, arg2);
	STOP_LAPTIMER(607);
}
void _UTL_SendDcSwitch( DcSwitchHandle arg1)
{
	MCI_LIST[608] = "UTL_SendDcSwitch";
	START_LAPTIMER(608);
	UTL_SendDcSwitch( arg1);
	STOP_LAPTIMER(608);
}
void _UTL_UpdateDcSwitch( DcSwitchHandle arg1)
{
	MCI_LIST[609] = "UTL_UpdateDcSwitch";
	START_LAPTIMER(609);
	UTL_UpdateDcSwitch( arg1);
	STOP_LAPTIMER(609);
}
int _UTL_GetDcSwitch( DcSwitchHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[610] = "UTL_GetDcSwitch";
	START_LAPTIMER(610);
	int retval = UTL_GetDcSwitch( arg1, arg2);
	STOP_LAPTIMER(610);
	return retval;
}
DcHandle _UTL_GetDcHandle()
{
	MCI_LIST[611] = "UTL_GetDcHandle";
	START_LAPTIMER(611);
	DcHandle retval = UTL_GetDcHandle();
	STOP_LAPTIMER(611);
	return retval;
}
void _UTL_SetDcMode( DcHandle arg1, RadioButton arg2)
{
	MCI_LIST[612] = "UTL_SetDcMode";
	START_LAPTIMER(612);
	UTL_SetDcMode( arg1, arg2);
	STOP_LAPTIMER(612);
}
void _UTL_SetDcSource( DcHandle arg1, DSlider arg2)
{
	MCI_LIST[613] = "UTL_SetDcSource";
	START_LAPTIMER(613);
	UTL_SetDcSource( arg1, arg2);
	STOP_LAPTIMER(613);
}
void _UTL_SetDcSrange( DcHandle arg1, DSlider arg2, DSlider arg3)
{
	MCI_LIST[614] = "UTL_SetDcSrange";
	START_LAPTIMER(614);
	UTL_SetDcSrange( arg1, arg2, arg3);
	STOP_LAPTIMER(614);
}
void _UTL_SetDcMrange( DcHandle arg1, DSlider arg2, DSlider arg3)
{
	MCI_LIST[615] = "UTL_SetDcMrange";
	START_LAPTIMER(615);
	UTL_SetDcMrange( arg1, arg2, arg3);
	STOP_LAPTIMER(615);
}
void _UTL_SetDcPclamp( DcHandle arg1, DSlider arg2)
{
	MCI_LIST[616] = "UTL_SetDcPclamp";
	START_LAPTIMER(616);
	UTL_SetDcPclamp( arg1, arg2);
	STOP_LAPTIMER(616);
}
void _UTL_SetDcMclamp( DcHandle arg1, DSlider arg2)
{
	MCI_LIST[617] = "UTL_SetDcMclamp";
	START_LAPTIMER(617);
	UTL_SetDcMclamp( arg1, arg2);
	STOP_LAPTIMER(617);
}
void _UTL_SetDcFilter( DcHandle arg1, RadioButton arg2)
{
	MCI_LIST[618] = "UTL_SetDcFilter";
	START_LAPTIMER(618);
	UTL_SetDcFilter( arg1, arg2);
	STOP_LAPTIMER(618);
}
void _UTL_SetDcLimitHigh( DcHandle arg1, DSlider arg2, CheckButton arg3)
{
	MCI_LIST[619] = "UTL_SetDcLimitHigh";
	START_LAPTIMER(619);
	UTL_SetDcLimitHigh( arg1, arg2, arg3);
	STOP_LAPTIMER(619);
}
void _UTL_SetDcLimitLow( DcHandle arg1, DSlider arg2, CheckButton arg3)
{
	MCI_LIST[620] = "UTL_SetDcLimitLow";
	START_LAPTIMER(620);
	UTL_SetDcLimitLow( arg1, arg2, arg3);
	STOP_LAPTIMER(620);
}
void _UTL_SetDcMeasCnt( DcHandle arg1, Slider arg2)
{
	MCI_LIST[621] = "UTL_SetDcMeasCnt";
	START_LAPTIMER(621);
	UTL_SetDcMeasCnt( arg1, arg2);
	STOP_LAPTIMER(621);
}
void _UTL_SetDcSlewRate( DcHandle arg1, DSlider arg2)
{
	MCI_LIST[622] = "UTL_SetDcSlewRate";
	START_LAPTIMER(622);
	UTL_SetDcSlewRate( arg1, arg2);
	STOP_LAPTIMER(622);
}
void _UTL_AddDcWetItem( DcHandle arg1, RadioButton arg2)
{
	MCI_LIST[623] = "UTL_AddDcWetItem";
	START_LAPTIMER(623);
	UTL_AddDcWetItem( arg1, arg2);
	STOP_LAPTIMER(623);
}
void _UTL_ClearDcWetItem( DcHandle arg1)
{
	MCI_LIST[624] = "UTL_ClearDcWetItem";
	START_LAPTIMER(624);
	UTL_ClearDcWetItem( arg1);
	STOP_LAPTIMER(624);
}
void _UTL_SendDc( DcHandle arg1, RadioButton arg2)
{
	MCI_LIST[625] = "UTL_SendDc";
	START_LAPTIMER(625);
	UTL_SendDc( arg1, arg2);
	STOP_LAPTIMER(625);
}
SettlingTimeHandle _UTL_GetSettlingTimeHandle()
{
	MCI_LIST[626] = "UTL_GetSettlingTimeHandle";
	START_LAPTIMER(626);
	SettlingTimeHandle retval = UTL_GetSettlingTimeHandle();
	STOP_LAPTIMER(626);
	return retval;
}
void _UTL_SetSettlingTime( SettlingTimeHandle arg1, DSlider arg2)
{
	MCI_LIST[627] = "UTL_SetSettlingTime";
	START_LAPTIMER(627);
	UTL_SetSettlingTime( arg1, arg2);
	STOP_LAPTIMER(627);
}
void _UTL_SetSettlingTimeAfterRon( SettlingTimeHandle arg1, DSlider arg2)
{
	MCI_LIST[628] = "UTL_SetSettlingTimeAfterRon";
	START_LAPTIMER(628);
	UTL_SetSettlingTimeAfterRon( arg1, arg2);
	STOP_LAPTIMER(628);
}
void _UTL_SetSettlingTimeAfterRof( SettlingTimeHandle arg1, DSlider arg2)
{
	MCI_LIST[629] = "UTL_SetSettlingTimeAfterRof";
	START_LAPTIMER(629);
	UTL_SetSettlingTimeAfterRof( arg1, arg2);
	STOP_LAPTIMER(629);
}
void _UTL_SendSettlingTime( SettlingTimeHandle arg1)
{
	MCI_LIST[630] = "UTL_SendSettlingTime";
	START_LAPTIMER(630);
	UTL_SendSettlingTime( arg1);
	STOP_LAPTIMER(630);
}
DctHandle _UTL_GetDctHandle()
{
	MCI_LIST[631] = "UTL_GetDctHandle";
	START_LAPTIMER(631);
	DctHandle retval = UTL_GetDctHandle();
	STOP_LAPTIMER(631);
	return retval;
}
void _UTL_SetDctPinList( DctHandle arg1, char * arg2)
{
	MCI_LIST[632] = "UTL_SetDctPinList";
	START_LAPTIMER(632);
	UTL_SetDctPinList( arg1, arg2);
	STOP_LAPTIMER(632);
}
void _UTL_SetDctRelayMode( DctHandle arg1, RadioButton arg2)
{
	MCI_LIST[633] = "UTL_SetDctRelayMode";
	START_LAPTIMER(633);
	UTL_SetDctRelayMode( arg1, arg2);
	STOP_LAPTIMER(633);
}
void _UTL_SetDctPinVi( DctHandle arg1, CheckButton arg2)
{
	MCI_LIST[634] = "UTL_SetDctPinVi";
	START_LAPTIMER(634);
	UTL_SetDctPinVi( arg1, arg2);
	STOP_LAPTIMER(634);
}
void _UTL_SetDctPinVo( DctHandle arg1, CheckButton arg2)
{
	MCI_LIST[635] = "UTL_SetDctPinVo";
	START_LAPTIMER(635);
	UTL_SetDctPinVo( arg1, arg2);
	STOP_LAPTIMER(635);
}
void _UTL_SetDctPinVihh( DctHandle arg1, CheckButton arg2)
{
	MCI_LIST[636] = "UTL_SetDctPinVihh";
	START_LAPTIMER(636);
	UTL_SetDctPinVihh( arg1, arg2);
	STOP_LAPTIMER(636);
}
void _UTL_SetDctPinHvDr( DctHandle arg1, CheckButton arg2)
{
	MCI_LIST[637] = "UTL_SetDctPinHvDr";
	START_LAPTIMER(637);
	UTL_SetDctPinHvDr( arg1, arg2);
	STOP_LAPTIMER(637);
}
void _UTL_SetDctPinTerm( DctHandle arg1, CheckButton arg2)
{
	MCI_LIST[638] = "UTL_SetDctPinTerm";
	START_LAPTIMER(638);
	UTL_SetDctPinTerm( arg1, arg2);
	STOP_LAPTIMER(638);
}
void _UTL_SetDctPinPl( DctHandle arg1, RadioButton arg2)
{
	MCI_LIST[639] = "UTL_SetDctPinPl";
	START_LAPTIMER(639);
	UTL_SetDctPinPl( arg1, arg2);
	STOP_LAPTIMER(639);
}
void _UTL_SetDctAltMode( DctHandle arg1, RadioButton arg2)
{
	MCI_LIST[640] = "UTL_SetDctAltMode";
	START_LAPTIMER(640);
	UTL_SetDctAltMode( arg1, arg2);
	STOP_LAPTIMER(640);
}
void _UTL_SetDctAltSource( DctHandle arg1, DSlider arg2)
{
	MCI_LIST[641] = "UTL_SetDctAltSource";
	START_LAPTIMER(641);
	UTL_SetDctAltSource( arg1, arg2);
	STOP_LAPTIMER(641);
}
void _UTL_SetDctAltPclamp( DctHandle arg1, DSlider arg2)
{
	MCI_LIST[642] = "UTL_SetDctAltPclamp";
	START_LAPTIMER(642);
	UTL_SetDctAltPclamp( arg1, arg2);
	STOP_LAPTIMER(642);
}
void _UTL_SetDctAltMclamp( DctHandle arg1, DSlider arg2)
{
	MCI_LIST[643] = "UTL_SetDctAltMclamp";
	START_LAPTIMER(643);
	UTL_SetDctAltMclamp( arg1, arg2);
	STOP_LAPTIMER(643);
}
void _UTL_SetDctAfterDcOn( DctHandle arg1, RadioButton arg2)
{
	MCI_LIST[644] = "UTL_SetDctAfterDcOn";
	START_LAPTIMER(644);
	UTL_SetDctAfterDcOn( arg1, arg2);
	STOP_LAPTIMER(644);
}
void _UTL_SetDctBeforeFunc( DctHandle arg1, void (*arg2)(void))
{
	MCI_LIST[645] = "UTL_SetDctBeforeFunc";
	START_LAPTIMER(645);
	UTL_SetDctBeforeFunc( arg1, arg2);
	STOP_LAPTIMER(645);
}
void _UTL_SetDctAfterFunc( DctHandle arg1, void (*arg2)(void))
{
	MCI_LIST[646] = "UTL_SetDctAfterFunc";
	START_LAPTIMER(646);
	UTL_SetDctAfterFunc( arg1, arg2);
	STOP_LAPTIMER(646);
}
void _UTL_SetDctFailAction( DctHandle arg1, void (*arg2)(void))
{
	MCI_LIST[647] = "UTL_SetDctFailAction";
	START_LAPTIMER(647);
	UTL_SetDctFailAction( arg1, arg2);
	STOP_LAPTIMER(647);
}
void _UTL_SetDctPassAction( DctHandle arg1, void (*arg2)(void))
{
	MCI_LIST[648] = "UTL_SetDctPassAction";
	START_LAPTIMER(648);
	UTL_SetDctPassAction( arg1, arg2);
	STOP_LAPTIMER(648);
}
void _UTL_SetDctHidarCondition( DctHandle arg1, HidarConfigHandle arg2)
{
	MCI_LIST[649] = "UTL_SetDctHidarCondition";
	START_LAPTIMER(649);
	UTL_SetDctHidarCondition( arg1, arg2);
	STOP_LAPTIMER(649);
}
void _UTL_SetDctAutoRangeMode( DctHandle arg1, CheckButton arg2)
{
	MCI_LIST[650] = "UTL_SetDctAutoRangeMode";
	START_LAPTIMER(650);
	UTL_SetDctAutoRangeMode( arg1, arg2);
	STOP_LAPTIMER(650);
}
void _UTL_SetDctGoNogoOnly( DctHandle arg1, CheckButton arg2)
{
	MCI_LIST[651] = "UTL_SetDctGoNogoOnly";
	START_LAPTIMER(651);
	UTL_SetDctGoNogoOnly( arg1, arg2);
	STOP_LAPTIMER(651);
}
void _UTL_SetDctAutoTestName( DctHandle arg1, CheckButton arg2)
{
	MCI_LIST[652] = "UTL_SetDctAutoTestName";
	START_LAPTIMER(652);
	UTL_SetDctAutoTestName( arg1, arg2);
	STOP_LAPTIMER(652);
}
void _UTL_MeasDct( DctHandle arg1)
{
	MCI_LIST[653] = "UTL_MeasDct";
	START_LAPTIMER(653);
	UTL_MeasDct( arg1);
	STOP_LAPTIMER(653);
}
void _UTL_StartDct( DctHandle arg1)
{
	MCI_LIST[654] = "UTL_StartDct";
	START_LAPTIMER(654);
	UTL_StartDct( arg1);
	STOP_LAPTIMER(654);
}
void _UTL_SetDctReferenceMode( RadioButton arg1)
{
	MCI_LIST[655] = "UTL_SetDctReferenceMode";
	START_LAPTIMER(655);
	UTL_SetDctReferenceMode( arg1);
	STOP_LAPTIMER(655);
}
RadioButton _UTL_ReadDctReferenceMode()
{
	MCI_LIST[656] = "UTL_ReadDctReferenceMode";
	START_LAPTIMER(656);
	RadioButton retval = UTL_ReadDctReferenceMode();
	STOP_LAPTIMER(656);
	return retval;
}
void _UTL_SetDctSepaDrCtrlMode( RadioButton arg1)
{
	MCI_LIST[657] = "UTL_SetDctSepaDrCtrlMode";
	START_LAPTIMER(657);
	UTL_SetDctSepaDrCtrlMode( arg1);
	STOP_LAPTIMER(657);
}
RadioButton _UTL_ReadDctSepaDrCtrlMode()
{
	MCI_LIST[658] = "UTL_ReadDctSepaDrCtrlMode";
	START_LAPTIMER(658);
	RadioButton retval = UTL_ReadDctSepaDrCtrlMode();
	STOP_LAPTIMER(658);
	return retval;
}
AdcHandle _UTL_GetAdcHandle()
{
	MCI_LIST[659] = "UTL_GetAdcHandle";
	START_LAPTIMER(659);
	AdcHandle retval = UTL_GetAdcHandle();
	STOP_LAPTIMER(659);
	return retval;
}
void _UTL_SetAdcPgEnable( AdcHandle arg1, CheckButton arg2)
{
	MCI_LIST[660] = "UTL_SetAdcPgEnable";
	START_LAPTIMER(660);
	UTL_SetAdcPgEnable( arg1, arg2);
	STOP_LAPTIMER(660);
}
void _UTL_SetAdcStartCycle( AdcHandle arg1, RadioButton arg2)
{
	MCI_LIST[661] = "UTL_SetAdcStartCycle";
	START_LAPTIMER(661);
	UTL_SetAdcStartCycle( arg1, arg2);
	STOP_LAPTIMER(661);
}
void _UTL_SetAdcInput( AdcHandle arg1, RadioButton arg2)
{
	MCI_LIST[662] = "UTL_SetAdcInput";
	START_LAPTIMER(662);
	UTL_SetAdcInput( arg1, arg2);
	STOP_LAPTIMER(662);
}
void _UTL_SetAdcPinList( AdcHandle arg1, char * arg2)
{
	MCI_LIST[663] = "UTL_SetAdcPinList";
	START_LAPTIMER(663);
	UTL_SetAdcPinList( arg1, arg2);
	STOP_LAPTIMER(663);
}
void _UTL_SetAdcMeasMode( AdcHandle arg1, RadioButton arg2)
{
	MCI_LIST[664] = "UTL_SetAdcMeasMode";
	START_LAPTIMER(664);
	UTL_SetAdcMeasMode( arg1, arg2);
	STOP_LAPTIMER(664);
}
void _UTL_SetAdcHistoryMode( AdcHandle arg1, CheckButton arg2)
{
	MCI_LIST[665] = "UTL_SetAdcHistoryMode";
	START_LAPTIMER(665);
	UTL_SetAdcHistoryMode( arg1, arg2);
	STOP_LAPTIMER(665);
}
void _UTL_SetAdcSettlingTime( AdcHandle arg1, DSlider arg2)
{
	MCI_LIST[666] = "UTL_SetAdcSettlingTime";
	START_LAPTIMER(666);
	UTL_SetAdcSettlingTime( arg1, arg2);
	STOP_LAPTIMER(666);
}
void _UTL_SendAdc( AdcHandle arg1, RadioButton arg2)
{
	MCI_LIST[667] = "UTL_SendAdc";
	START_LAPTIMER(667);
	UTL_SendAdc( arg1, arg2);
	STOP_LAPTIMER(667);
}
void _UTL_WaitAdc( RadioButton arg1)
{
	MCI_LIST[668] = "UTL_WaitAdc";
	START_LAPTIMER(668);
	UTL_WaitAdc( arg1);
	STOP_LAPTIMER(668);
}
void _UTL_ResetAdcHistoryCount( RadioButton arg1)
{
	MCI_LIST[669] = "UTL_ResetAdcHistoryCount";
	START_LAPTIMER(669);
	UTL_ResetAdcHistoryCount( arg1);
	STOP_LAPTIMER(669);
}
USlider _UTL_ReadAdcHistoryCount( RadioButton arg1, CheckButton * arg2)
{
	MCI_LIST[670] = "UTL_ReadAdcHistoryCount";
	START_LAPTIMER(670);
	USlider retval = UTL_ReadAdcHistoryCount( arg1, arg2);
	STOP_LAPTIMER(670);
	return retval;
}
RadioButton _UTL_GetAdcDutGroupMaxNumber( RadioButton arg1)
{
	MCI_LIST[671] = "UTL_GetAdcDutGroupMaxNumber";
	START_LAPTIMER(671);
	RadioButton retval = UTL_GetAdcDutGroupMaxNumber( arg1);
	STOP_LAPTIMER(671);
	return retval;
}
void _UTL_WriteAdcDutGroupNumber( RadioButton arg1, RadioButton arg2)
{
	MCI_LIST[672] = "UTL_WriteAdcDutGroupNumber";
	START_LAPTIMER(672);
	UTL_WriteAdcDutGroupNumber( arg1, arg2);
	STOP_LAPTIMER(672);
}
RadioButton _UTL_ReadAdcDutGroupNumber( RadioButton arg1)
{
	MCI_LIST[673] = "UTL_ReadAdcDutGroupNumber";
	START_LAPTIMER(673);
	RadioButton retval = UTL_ReadAdcDutGroupNumber( arg1);
	STOP_LAPTIMER(673);
	return retval;
}
DutCursor _UTL_GetAdcDutGroupDutCursor( RadioButton arg1, RadioButton arg2)
{
	MCI_LIST[674] = "UTL_GetAdcDutGroupDutCursor";
	START_LAPTIMER(674);
	DutCursor retval = UTL_GetAdcDutGroupDutCursor( arg1, arg2);
	STOP_LAPTIMER(674);
	return retval;
}
SamplingRateHandle _UTL_GetSamplingRateHandle()
{
	MCI_LIST[675] = "UTL_GetSamplingRateHandle";
	START_LAPTIMER(675);
	SamplingRateHandle retval = UTL_GetSamplingRateHandle();
	STOP_LAPTIMER(675);
	return retval;
}
void _UTL_SetSamplingRate( SettlingTimeHandle arg1, DSlider arg2)
{
	MCI_LIST[676] = "UTL_SetSamplingRate";
	START_LAPTIMER(676);
	UTL_SetSamplingRate( arg1, arg2);
	STOP_LAPTIMER(676);
}
void _UTL_SendSamplingRate( SamplingRateHandle arg1)
{
	MCI_LIST[677] = "UTL_SendSamplingRate";
	START_LAPTIMER(677);
	UTL_SendSamplingRate( arg1);
	STOP_LAPTIMER(677);
}
DcComparatorHandle _UTL_GetDcComparatorHandle()
{
	MCI_LIST[678] = "UTL_GetDcComparatorHandle";
	START_LAPTIMER(678);
	DcComparatorHandle retval = UTL_GetDcComparatorHandle();
	STOP_LAPTIMER(678);
	return retval;
}
void _UTL_SetDcComparatorLimitHigh( DcComparatorHandle arg1, DSlider arg2)
{
	MCI_LIST[679] = "UTL_SetDcComparatorLimitHigh";
	START_LAPTIMER(679);
	UTL_SetDcComparatorLimitHigh( arg1, arg2);
	STOP_LAPTIMER(679);
}
void _UTL_SetDcComparatorLimitLow( DcComparatorHandle arg1, DSlider arg2)
{
	MCI_LIST[680] = "UTL_SetDcComparatorLimitLow";
	START_LAPTIMER(680);
	UTL_SetDcComparatorLimitLow( arg1, arg2);
	STOP_LAPTIMER(680);
}
void _UTL_SendDcComparator( DcComparatorHandle arg1)
{
	MCI_LIST[681] = "UTL_SendDcComparator";
	START_LAPTIMER(681);
	UTL_SendDcComparator( arg1);
	STOP_LAPTIMER(681);
}
DcComparatorReadPinHandle _UTL_GetDcComparatorReadPinHandle()
{
	MCI_LIST[682] = "UTL_GetDcComparatorReadPinHandle";
	START_LAPTIMER(682);
	DcComparatorReadPinHandle retval = UTL_GetDcComparatorReadPinHandle();
	STOP_LAPTIMER(682);
	return retval;
}
void _UTL_SetDcComparatorReadPinDut( DcComparatorReadPinHandle arg1, UT_DUT arg2)
{
	MCI_LIST[683] = "UTL_SetDcComparatorReadPinDut";
	START_LAPTIMER(683);
	UTL_SetDcComparatorReadPinDut( arg1, arg2);
	STOP_LAPTIMER(683);
}
void _UTL_SetDcComparatorReadPinNumber( DcComparatorReadPinHandle arg1, UT_PIN arg2)
{
	MCI_LIST[684] = "UTL_SetDcComparatorReadPinNumber";
	START_LAPTIMER(684);
	UTL_SetDcComparatorReadPinNumber( arg1, arg2);
	STOP_LAPTIMER(684);
}
void _UTL_SetDcComparatorReadPinMode( DcComparatorReadPinHandle arg1, RadioButton arg2)
{
	MCI_LIST[685] = "UTL_SetDcComparatorReadPinMode";
	START_LAPTIMER(685);
	UTL_SetDcComparatorReadPinMode( arg1, arg2);
	STOP_LAPTIMER(685);
}
FctHandle _UTL_GetFctHandle()
{
	MCI_LIST[686] = "UTL_GetFctHandle";
	START_LAPTIMER(686);
	FctHandle retval = UTL_GetFctHandle();
	STOP_LAPTIMER(686);
	return retval;
}
void _UTL_SetFctContinue( FctHandle arg1, CheckButton arg2)
{
	MCI_LIST[687] = "UTL_SetFctContinue";
	START_LAPTIMER(687);
	UTL_SetFctContinue( arg1, arg2);
	STOP_LAPTIMER(687);
}
void _UTL_SetFctNoWait( FctHandle arg1, CheckButton arg2)
{
	MCI_LIST[688] = "UTL_SetFctNoWait";
	START_LAPTIMER(688);
	UTL_SetFctNoWait( arg1, arg2);
	STOP_LAPTIMER(688);
}
void _UTL_SetFctNoClear( FctHandle arg1, CheckButton arg2)
{
	MCI_LIST[689] = "UTL_SetFctNoClear";
	START_LAPTIMER(689);
	UTL_SetFctNoClear( arg1, arg2);
	STOP_LAPTIMER(689);
}
void _UTL_SetFctFailInhibit( FctHandle arg1, CheckButton arg2)
{
	MCI_LIST[690] = "UTL_SetFctFailInhibit";
	START_LAPTIMER(690);
	UTL_SetFctFailInhibit( arg1, arg2);
	STOP_LAPTIMER(690);
}
void _UTL_SetFctRepeat( FctHandle arg1, CheckButton arg2)
{
	MCI_LIST[691] = "UTL_SetFctRepeat";
	START_LAPTIMER(691);
	UTL_SetFctRepeat( arg1, arg2);
	STOP_LAPTIMER(691);
}
void _UTL_SetFctSronInhibit( FctHandle arg1, CheckButton arg2)
{
	MCI_LIST[692] = "UTL_SetFctSronInhibit";
	START_LAPTIMER(692);
	UTL_SetFctSronInhibit( arg1, arg2);
	STOP_LAPTIMER(692);
}
void _UTL_SetFctMpatTransferInhibit( FctHandle arg1, CheckButton arg2)
{
	MCI_LIST[693] = "UTL_SetFctMpatTransferInhibit";
	START_LAPTIMER(693);
	UTL_SetFctMpatTransferInhibit( arg1, arg2);
	STOP_LAPTIMER(693);
}
void _UTL_SetFctMpatTransferDataInhibit( FctHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[694] = "UTL_SetFctMpatTransferDataInhibit";
	START_LAPTIMER(694);
	UTL_SetFctMpatTransferDataInhibit( arg1, arg2, arg3);
	STOP_LAPTIMER(694);
}
void _UTL_SetFctStartLabelNameOfMpatSelector( FctHandle arg1, char * arg2, char * arg3)
{
	MCI_LIST[695] = "UTL_SetFctStartLabelNameOfMpatSelector";
	START_LAPTIMER(695);
	UTL_SetFctStartLabelNameOfMpatSelector( arg1, arg2, arg3);
	STOP_LAPTIMER(695);
}
void _UTL_SetFctMpatDataFileNameWithMpatSelector( FctHandle arg1, char * arg2, char * arg3)
{
	MCI_LIST[696] = "UTL_SetFctMpatDataFileNameWithMpatSelector";
	START_LAPTIMER(696);
	UTL_SetFctMpatDataFileNameWithMpatSelector( arg1, arg2, arg3);
	STOP_LAPTIMER(696);
}
void _UTL_SetFctMpatName( FctHandle arg1, char * arg2)
{
	MCI_LIST[697] = "UTL_SetFctMpatName";
	START_LAPTIMER(697);
	UTL_SetFctMpatName( arg1, arg2);
	STOP_LAPTIMER(697);
}
void _UTL_SetFctStartPc( FctHandle arg1, USlider arg2)
{
	MCI_LIST[698] = "UTL_SetFctStartPc";
	START_LAPTIMER(698);
	UTL_SetFctStartPc( arg1, arg2);
	STOP_LAPTIMER(698);
}
void _UTL_SetFctTimeLimit( FctHandle arg1, CheckButton arg2, DSlider arg3)
{
	MCI_LIST[699] = "UTL_SetFctTimeLimit";
	START_LAPTIMER(699);
	UTL_SetFctTimeLimit( arg1, arg2, arg3);
	STOP_LAPTIMER(699);
}
void _UTL_SetFctTimeLimitAction( FctHandle arg1, void (*arg2)(void))
{
	MCI_LIST[700] = "UTL_SetFctTimeLimitAction";
	START_LAPTIMER(700);
	UTL_SetFctTimeLimitAction( arg1, arg2);
	STOP_LAPTIMER(700);
}
void _UTL_SetFctFailAction( FctHandle arg1, void (*arg2)(void))
{
	MCI_LIST[701] = "UTL_SetFctFailAction";
	START_LAPTIMER(701);
	UTL_SetFctFailAction( arg1, arg2);
	STOP_LAPTIMER(701);
}
void _UTL_SetFctPassAction( FctHandle arg1, void (*arg2)(void))
{
	MCI_LIST[702] = "UTL_SetFctPassAction";
	START_LAPTIMER(702);
	UTL_SetFctPassAction( arg1, arg2);
	STOP_LAPTIMER(702);
}
void _UTL_SetFctBeforeFunc( FctHandle arg1, void (*arg2)(void))
{
	MCI_LIST[703] = "UTL_SetFctBeforeFunc";
	START_LAPTIMER(703);
	UTL_SetFctBeforeFunc( arg1, arg2);
	STOP_LAPTIMER(703);
}
void _UTL_SetFctStartFunc( FctHandle arg1, void (*arg2)(void))
{
	MCI_LIST[704] = "UTL_SetFctStartFunc";
	START_LAPTIMER(704);
	UTL_SetFctStartFunc( arg1, arg2);
	STOP_LAPTIMER(704);
}
void _UTL_SetFctAfterFunc( FctHandle arg1, void (*arg2)(void))
{
	MCI_LIST[705] = "UTL_SetFctAfterFunc";
	START_LAPTIMER(705);
	UTL_SetFctAfterFunc( arg1, arg2);
	STOP_LAPTIMER(705);
}
void _UTL_MeasFct( FctHandle arg1)
{
	MCI_LIST[706] = "UTL_MeasFct";
	START_LAPTIMER(706);
	UTL_MeasFct( arg1);
	STOP_LAPTIMER(706);
}
void _UTL_StartFct( FctHandle arg1)
{
	MCI_LIST[707] = "UTL_StartFct";
	START_LAPTIMER(707);
	UTL_StartFct( arg1);
	STOP_LAPTIMER(707);
}
void _UTL_StopFct()
{
	MCI_LIST[708] = "UTL_StopFct";
	START_LAPTIMER(708);
	UTL_StopFct();
	STOP_LAPTIMER(708);
}
VpatHandle _UTL_GetVpatHandle()
{
	MCI_LIST[709] = "UTL_GetVpatHandle";
	START_LAPTIMER(709);
	VpatHandle retval = UTL_GetVpatHandle();
	STOP_LAPTIMER(709);
	return retval;
}
void _UTL_SetVpatName( VpatHandle arg1, char * arg2)
{
	MCI_LIST[710] = "UTL_SetVpatName";
	START_LAPTIMER(710);
	UTL_SetVpatName( arg1, arg2);
	STOP_LAPTIMER(710);
}
void _UTL_SetVpatFailInhibit( VpatHandle arg1, CheckButton arg2)
{
	MCI_LIST[711] = "UTL_SetVpatFailInhibit";
	START_LAPTIMER(711);
	UTL_SetVpatFailInhibit( arg1, arg2);
	STOP_LAPTIMER(711);
}
void _UTL_SetVpatFailAction( VpatHandle arg1, void (*arg2)(void))
{
	MCI_LIST[712] = "UTL_SetVpatFailAction";
	START_LAPTIMER(712);
	UTL_SetVpatFailAction( arg1, arg2);
	STOP_LAPTIMER(712);
}
void _UTL_SetVpatPassAction( VpatHandle arg1, void (*arg2)(void))
{
	MCI_LIST[713] = "UTL_SetVpatPassAction";
	START_LAPTIMER(713);
	UTL_SetVpatPassAction( arg1, arg2);
	STOP_LAPTIMER(713);
}
void _UTL_SetVpatBeforeFunc( VpatHandle arg1, void (*arg2)(void))
{
	MCI_LIST[714] = "UTL_SetVpatBeforeFunc";
	START_LAPTIMER(714);
	UTL_SetVpatBeforeFunc( arg1, arg2);
	STOP_LAPTIMER(714);
}
void _UTL_SetVpatStartFunc( VpatHandle arg1, void (*arg2)(void))
{
	MCI_LIST[715] = "UTL_SetVpatStartFunc";
	START_LAPTIMER(715);
	UTL_SetVpatStartFunc( arg1, arg2);
	STOP_LAPTIMER(715);
}
void _UTL_SetVpatAfterFunc( VpatHandle arg1, void (*arg2)(void))
{
	MCI_LIST[716] = "UTL_SetVpatAfterFunc";
	START_LAPTIMER(716);
	UTL_SetVpatAfterFunc( arg1, arg2);
	STOP_LAPTIMER(716);
}
void _UTL_MeasVpat( VpatHandle arg1)
{
	MCI_LIST[717] = "UTL_MeasVpat";
	START_LAPTIMER(717);
	UTL_MeasVpat( arg1);
	STOP_LAPTIMER(717);
}
DctReadPinHandle _UTL_GetDctReadPinHandle()
{
	MCI_LIST[718] = "UTL_GetDctReadPinHandle";
	START_LAPTIMER(718);
	DctReadPinHandle retval = UTL_GetDctReadPinHandle();
	STOP_LAPTIMER(718);
	return retval;
}
void _UTL_SetDctReadPinDut( DctReadPinHandle arg1, UT_DUT arg2)
{
	MCI_LIST[719] = "UTL_SetDctReadPinDut";
	START_LAPTIMER(719);
	UTL_SetDctReadPinDut( arg1, arg2);
	STOP_LAPTIMER(719);
}
void _UTL_SetDctReadPinNumber( DctReadPinHandle arg1, UT_PIN arg2)
{
	MCI_LIST[720] = "UTL_SetDctReadPinNumber";
	START_LAPTIMER(720);
	UTL_SetDctReadPinNumber( arg1, arg2);
	STOP_LAPTIMER(720);
}
void _UTL_SetDctReadPinType( DctReadPinHandle arg1, RadioButton arg2)
{
	MCI_LIST[721] = "UTL_SetDctReadPinType";
	START_LAPTIMER(721);
	UTL_SetDctReadPinType( arg1, arg2);
	STOP_LAPTIMER(721);
}
void _UTL_SetDctReadPinMode( DctReadPinHandle arg1, RadioButton arg2)
{
	MCI_LIST[722] = "UTL_SetDctReadPinMode";
	START_LAPTIMER(722);
	UTL_SetDctReadPinMode( arg1, arg2);
	STOP_LAPTIMER(722);
}
void _UTL_SetDctReadPinHistoryNumber( DctReadPinHandle arg1, RadioButton arg2)
{
	MCI_LIST[723] = "UTL_SetDctReadPinHistoryNumber";
	START_LAPTIMER(723);
	UTL_SetDctReadPinHistoryNumber( arg1, arg2);
	STOP_LAPTIMER(723);
}
DSlider _UTL_ReadDctPinData( DctReadPinHandle arg1)
{
	MCI_LIST[724] = "UTL_ReadDctPinData";
	START_LAPTIMER(724);
	DSlider retval = UTL_ReadDctPinData( arg1);
	STOP_LAPTIMER(724);
	return retval;
}
CheckButton _UTL_ReadDctPin( DctReadPinHandle arg1)
{
	MCI_LIST[725] = "UTL_ReadDctPin";
	START_LAPTIMER(725);
	CheckButton retval = UTL_ReadDctPin( arg1);
	STOP_LAPTIMER(725);
	return retval;
}
RadioButton _UTL_ReadDctPinMeasMode( DctReadPinHandle arg1)
{
	MCI_LIST[726] = "UTL_ReadDctPinMeasMode";
	START_LAPTIMER(726);
	RadioButton retval = UTL_ReadDctPinMeasMode( arg1);
	STOP_LAPTIMER(726);
	return retval;
}
CheckButton _UTL_ReadDctPinOverflowPolarity( DctReadPinHandle arg1)
{
	MCI_LIST[727] = "UTL_ReadDctPinOverflowPolarity";
	START_LAPTIMER(727);
	CheckButton retval = UTL_ReadDctPinOverflowPolarity( arg1);
	STOP_LAPTIMER(727);
	return retval;
}
UT_PIN _UTL_ReadDctLatestPinNumber()
{
	MCI_LIST[728] = "UTL_ReadDctLatestPinNumber";
	START_LAPTIMER(728);
	UT_PIN retval = UTL_ReadDctLatestPinNumber();
	STOP_LAPTIMER(728);
	return retval;
}
DSlider _UTL_ReadDctPinHistoryData( DctReadPinHandle arg1)
{
	MCI_LIST[729] = "UTL_ReadDctPinHistoryData";
	START_LAPTIMER(729);
	DSlider retval = UTL_ReadDctPinHistoryData( arg1);
	STOP_LAPTIMER(729);
	return retval;
}
void _UTL_ReadDctPinAllHistoryData( DctReadPinHandle arg1, DSlider * arg2, USlider arg3)
{
	MCI_LIST[730] = "UTL_ReadDctPinAllHistoryData";
	START_LAPTIMER(730);
	UTL_ReadDctPinAllHistoryData( arg1, arg2, arg3);
	STOP_LAPTIMER(730);
}
void _UTL_ReadDctPinAllHistoryDataAllDut( DctReadPinHandle arg1, DSlider * arg2, CheckButton * arg3, USlider arg4)
{
	MCI_LIST[731] = "UTL_ReadDctPinAllHistoryDataAllDut";
	START_LAPTIMER(731);
	UTL_ReadDctPinAllHistoryDataAllDut( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(731);
}
FctReadPinHandle _UTL_GetFctReadPinHandle()
{
	MCI_LIST[732] = "UTL_GetFctReadPinHandle";
	START_LAPTIMER(732);
	FctReadPinHandle retval = UTL_GetFctReadPinHandle();
	STOP_LAPTIMER(732);
	return retval;
}
void _UTL_SetFctReadPinMode( FctReadPinHandle arg1, RadioButton arg2)
{
	MCI_LIST[733] = "UTL_SetFctReadPinMode";
	START_LAPTIMER(733);
	UTL_SetFctReadPinMode( arg1, arg2);
	STOP_LAPTIMER(733);
}
void _UTL_SetFctReadPinDut( FctReadPinHandle arg1, UT_DUT arg2)
{
	MCI_LIST[734] = "UTL_SetFctReadPinDut";
	START_LAPTIMER(734);
	UTL_SetFctReadPinDut( arg1, arg2);
	STOP_LAPTIMER(734);
}
void _UTL_SetFctReadPinNumber( FctReadPinHandle arg1, UT_PIN arg2)
{
	MCI_LIST[735] = "UTL_SetFctReadPinNumber";
	START_LAPTIMER(735);
	UTL_SetFctReadPinNumber( arg1, arg2);
	STOP_LAPTIMER(735);
}
CheckButton _UTL_ReadFctPin( FctReadPinHandle arg1)
{
	MCI_LIST[736] = "UTL_ReadFctPin";
	START_LAPTIMER(736);
	CheckButton retval = UTL_ReadFctPin( arg1);
	STOP_LAPTIMER(736);
	return retval;
}
ScFailPinHandle _UTL_GetScFailPinHandle()
{
	MCI_LIST[737] = "UTL_GetScFailPinHandle";
	START_LAPTIMER(737);
	ScFailPinHandle retval = UTL_GetScFailPinHandle();
	STOP_LAPTIMER(737);
	return retval;
}
void _UTL_AddScFailPinTargetPinNumber( ScFailPinHandle arg1, UT_PIN arg2)
{
	MCI_LIST[738] = "UTL_AddScFailPinTargetPinNumber";
	START_LAPTIMER(738);
	UTL_AddScFailPinTargetPinNumber( arg1, arg2);
	STOP_LAPTIMER(738);
}
void _UTL_ClearScFailPinTargetPinNumber( ScFailPinHandle arg1)
{
	MCI_LIST[739] = "UTL_ClearScFailPinTargetPinNumber";
	START_LAPTIMER(739);
	UTL_ClearScFailPinTargetPinNumber( arg1);
	STOP_LAPTIMER(739);
}
void _UTL_SetScFailPinUpdateMode( ScFailPinHandle arg1, RadioButton arg2)
{
	MCI_LIST[740] = "UTL_SetScFailPinUpdateMode";
	START_LAPTIMER(740);
	UTL_SetScFailPinUpdateMode( arg1, arg2);
	STOP_LAPTIMER(740);
}
void _UTL_SetScFailPinTargetBank( ScFailPinHandle arg1, RadioButton arg2)
{
	MCI_LIST[741] = "UTL_SetScFailPinTargetBank";
	START_LAPTIMER(741);
	UTL_SetScFailPinTargetBank( arg1, arg2);
	STOP_LAPTIMER(741);
}
void _UTL_UpdateScFailPin( ScFailPinHandle arg1)
{
	MCI_LIST[742] = "UTL_UpdateScFailPin";
	START_LAPTIMER(742);
	UTL_UpdateScFailPin( arg1);
	STOP_LAPTIMER(742);
}
int _UTL_GetScFailPin( ScFailPinHandle arg1, UT_DUT arg2, UT_PIN arg3, CheckButton * arg4)
{
	MCI_LIST[743] = "UTL_GetScFailPin";
	START_LAPTIMER(743);
	int retval = UTL_GetScFailPin( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(743);
	return retval;
}
PinCursor _UTL_GetScFailPinTargetPinCursor( ScFailPinHandle arg1)
{
	MCI_LIST[744] = "UTL_GetScFailPinTargetPinCursor";
	START_LAPTIMER(744);
	PinCursor retval = UTL_GetScFailPinTargetPinCursor( arg1);
	STOP_LAPTIMER(744);
	return retval;
}
int _UTL_GetScFailPinUpdateMode( ScFailPinHandle arg1, RadioButton * arg2)
{
	MCI_LIST[745] = "UTL_GetScFailPinUpdateMode";
	START_LAPTIMER(745);
	int retval = UTL_GetScFailPinUpdateMode( arg1, arg2);
	STOP_LAPTIMER(745);
	return retval;
}
int _UTL_GetScFailPinTargetBank( ScFailPinHandle arg1, RadioButton * arg2)
{
	MCI_LIST[746] = "UTL_GetScFailPinTargetBank";
	START_LAPTIMER(746);
	int retval = UTL_GetScFailPinTargetBank( arg1, arg2);
	STOP_LAPTIMER(746);
	return retval;
}
RadioButton _UTL_ReadMeasResult( UT_DUT arg1)
{
	MCI_LIST[747] = "UTL_ReadMeasResult";
	START_LAPTIMER(747);
	RadioButton retval = UTL_ReadMeasResult( arg1);
	STOP_LAPTIMER(747);
	return retval;
}
RadioButton _UTL_ReadMeasKind()
{
	MCI_LIST[748] = "UTL_ReadMeasKind";
	START_LAPTIMER(748);
	RadioButton retval = UTL_ReadMeasKind();
	STOP_LAPTIMER(748);
	return retval;
}
void _UTL_SetTestResult( UT_DUT arg1, char * arg2, RadioButton arg3)
{
	MCI_LIST[749] = "UTL_SetTestResult";
	START_LAPTIMER(749);
	UTL_SetTestResult( arg1, arg2, arg3);
	STOP_LAPTIMER(749);
}
void _UTL_ResetTestResult( UT_DUT arg1, char * arg2, RadioButton arg3)
{
	MCI_LIST[750] = "UTL_ResetTestResult";
	START_LAPTIMER(750);
	UTL_ResetTestResult( arg1, arg2, arg3);
	STOP_LAPTIMER(750);
}
RadioButton _UTL_ReadTestResult( UT_DUT arg1, char * arg2, RadioButton arg3)
{
	MCI_LIST[751] = "UTL_ReadTestResult";
	START_LAPTIMER(751);
	RadioButton retval = UTL_ReadTestResult( arg1, arg2, arg3);
	STOP_LAPTIMER(751);
	return retval;
}
USlider _UTL_ReadTestFailCount( char * arg1)
{
	MCI_LIST[752] = "UTL_ReadTestFailCount";
	START_LAPTIMER(752);
	USlider retval = UTL_ReadTestFailCount( arg1);
	STOP_LAPTIMER(752);
	return retval;
}
void _UTL_SetFinalResult( UT_DUT arg1, RadioButton arg2)
{
	MCI_LIST[753] = "UTL_SetFinalResult";
	START_LAPTIMER(753);
	UTL_SetFinalResult( arg1, arg2);
	STOP_LAPTIMER(753);
}
void _UTL_ResetFinalResult( UT_DUT arg1, RadioButton arg2)
{
	MCI_LIST[754] = "UTL_ResetFinalResult";
	START_LAPTIMER(754);
	UTL_ResetFinalResult( arg1, arg2);
	STOP_LAPTIMER(754);
}
void _UTL_SetFinalResultOnly( UT_DUT arg1, RadioButton arg2)
{
	MCI_LIST[755] = "UTL_SetFinalResultOnly";
	START_LAPTIMER(755);
	UTL_SetFinalResultOnly( arg1, arg2);
	STOP_LAPTIMER(755);
}
void _UTL_ResetFinalResultOnly( UT_DUT arg1, RadioButton arg2)
{
	MCI_LIST[756] = "UTL_ResetFinalResultOnly";
	START_LAPTIMER(756);
	UTL_ResetFinalResultOnly( arg1, arg2);
	STOP_LAPTIMER(756);
}
RadioButton _UTL_ReadFinalResult( UT_DUT arg1, RadioButton arg2)
{
	MCI_LIST[757] = "UTL_ReadFinalResult";
	START_LAPTIMER(757);
	RadioButton retval = UTL_ReadFinalResult( arg1, arg2);
	STOP_LAPTIMER(757);
	return retval;
}
DutChannelHandle _UTL_GetDutChannelHandle()
{
	MCI_LIST[758] = "UTL_GetDutChannelHandle";
	START_LAPTIMER(758);
	DutChannelHandle retval = UTL_GetDutChannelHandle();
	STOP_LAPTIMER(758);
	return retval;
}
void _UTL_SetDutChannelMode( DutChannelHandle arg1, CheckButton arg2)
{
	MCI_LIST[759] = "UTL_SetDutChannelMode";
	START_LAPTIMER(759);
	UTL_SetDutChannelMode( arg1, arg2);
	STOP_LAPTIMER(759);
}
void _UTL_SetDutChannelCount( DutChannelHandle arg1, USlider arg2)
{
	MCI_LIST[760] = "UTL_SetDutChannelCount";
	START_LAPTIMER(760);
	UTL_SetDutChannelCount( arg1, arg2);
	STOP_LAPTIMER(760);
}
void _UTL_SetDutChannelPinList( DutChannelHandle arg1, USlider arg2, char * arg3)
{
	MCI_LIST[761] = "UTL_SetDutChannelPinList";
	START_LAPTIMER(761);
	UTL_SetDutChannelPinList( arg1, arg2, arg3);
	STOP_LAPTIMER(761);
}
void _UTL_SendDutChannel( DutChannelHandle arg1)
{
	MCI_LIST[762] = "UTL_SendDutChannel";
	START_LAPTIMER(762);
	UTL_SendDutChannel( arg1);
	STOP_LAPTIMER(762);
}
void _UTL_UpdateDutChannel( DutChannelHandle arg1)
{
	MCI_LIST[763] = "UTL_UpdateDutChannel";
	START_LAPTIMER(763);
	UTL_UpdateDutChannel( arg1);
	STOP_LAPTIMER(763);
}
int _UTL_GetDutChannelMode( DutChannelHandle arg1, CheckButton * arg2)
{
	MCI_LIST[764] = "UTL_GetDutChannelMode";
	START_LAPTIMER(764);
	int retval = UTL_GetDutChannelMode( arg1, arg2);
	STOP_LAPTIMER(764);
	return retval;
}
int _UTL_GetDutChannelCount( DutChannelHandle arg1, USlider * arg2)
{
	MCI_LIST[765] = "UTL_GetDutChannelCount";
	START_LAPTIMER(765);
	int retval = UTL_GetDutChannelCount( arg1, arg2);
	STOP_LAPTIMER(765);
	return retval;
}
int _UTL_GetDutChannelPinList( DutChannelHandle arg1, USlider arg2, char ** arg3)
{
	MCI_LIST[766] = "UTL_GetDutChannelPinList";
	START_LAPTIMER(766);
	int retval = UTL_GetDutChannelPinList( arg1, arg2, arg3);
	STOP_LAPTIMER(766);
	return retval;
}
FailCaptureSelectHandle _UTL_GetFailCaptureSelectHandle()
{
	MCI_LIST[767] = "UTL_GetFailCaptureSelectHandle";
	START_LAPTIMER(767);
	FailCaptureSelectHandle retval = UTL_GetFailCaptureSelectHandle();
	STOP_LAPTIMER(767);
	return retval;
}
void _UTL_SetFailCaptureSelectDutGroupNumber( FailCaptureSelectHandle arg1, RadioButton arg2)
{
	MCI_LIST[768] = "UTL_SetFailCaptureSelectDutGroupNumber";
	START_LAPTIMER(768);
	UTL_SetFailCaptureSelectDutGroupNumber( arg1, arg2);
	STOP_LAPTIMER(768);
}
void _UTL_SetFailCaptureSelectAllDutGroupNumber( FailCaptureSelectHandle arg1, CheckButton arg2)
{
	MCI_LIST[769] = "UTL_SetFailCaptureSelectAllDutGroupNumber";
	START_LAPTIMER(769);
	UTL_SetFailCaptureSelectAllDutGroupNumber( arg1, arg2);
	STOP_LAPTIMER(769);
}
void _UTL_SetFailCaptureSelectPinList( FailCaptureSelectHandle arg1, char * arg2)
{
	MCI_LIST[770] = "UTL_SetFailCaptureSelectPinList";
	START_LAPTIMER(770);
	UTL_SetFailCaptureSelectPinList( arg1, arg2);
	STOP_LAPTIMER(770);
}
void _UTL_SetFailCaptureSelectAllPin( FailCaptureSelectHandle arg1, CheckButton arg2)
{
	MCI_LIST[771] = "UTL_SetFailCaptureSelectAllPin";
	START_LAPTIMER(771);
	UTL_SetFailCaptureSelectAllPin( arg1, arg2);
	STOP_LAPTIMER(771);
}
void _UTL_SendFailCaptureSelect( FailCaptureSelectHandle arg1)
{
	MCI_LIST[772] = "UTL_SendFailCaptureSelect";
	START_LAPTIMER(772);
	UTL_SendFailCaptureSelect( arg1);
	STOP_LAPTIMER(772);
}
MemoryModuleHandle _UTL_GetMemoryModuleHandle()
{
	MCI_LIST[773] = "UTL_GetMemoryModuleHandle";
	START_LAPTIMER(773);
	MemoryModuleHandle retval = UTL_GetMemoryModuleHandle();
	STOP_LAPTIMER(773);
	return retval;
}
void _UTL_AddMemoryModulePurpose( MemoryModuleHandle  arg1, RadioButton  arg2, USlider  arg3)
{
	MCI_LIST[774] = "UTL_AddMemoryModulePurpose";
	START_LAPTIMER(774);
	UTL_AddMemoryModulePurpose( arg1, arg2, arg3);
	STOP_LAPTIMER(774);
}
void _UTL_ClearMemoryModulePurpose( MemoryModuleHandle  arg1)
{
	MCI_LIST[775] = "UTL_ClearMemoryModulePurpose";
	START_LAPTIMER(775);
	UTL_ClearMemoryModulePurpose( arg1);
	STOP_LAPTIMER(775);
}
void _UTL_SendMemoryModule( MemoryModuleHandle  arg1)
{
	MCI_LIST[776] = "UTL_SendMemoryModule";
	START_LAPTIMER(776);
	UTL_SendMemoryModule( arg1);
	STOP_LAPTIMER(776);
}
FcmConfigHandle _UTL_GetFcmConfigHandle()
{
	MCI_LIST[777] = "UTL_GetFcmConfigHandle";
	START_LAPTIMER(777);
	FcmConfigHandle retval = UTL_GetFcmConfigHandle();
	STOP_LAPTIMER(777);
	return retval;
}
void _UTL_SetFcmConfigMultiMode( FcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[778] = "UTL_SetFcmConfigMultiMode";
	START_LAPTIMER(778);
	UTL_SetFcmConfigMultiMode( arg1, arg2);
	STOP_LAPTIMER(778);
}
void _UTL_SetFcmConfigDut( FcmConfigHandle arg1, UT_DUT arg2)
{
	MCI_LIST[779] = "UTL_SetFcmConfigDut";
	START_LAPTIMER(779);
	UTL_SetFcmConfigDut( arg1, arg2);
	STOP_LAPTIMER(779);
}
void _UTL_SetFcmConfigBitSize( FcmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[780] = "UTL_SetFcmConfigBitSize";
	START_LAPTIMER(780);
	UTL_SetFcmConfigBitSize( arg1, arg2);
	STOP_LAPTIMER(780);
}
void _UTL_SetFcmConfigDutBitSize( FcmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[781] = "UTL_SetFcmConfigDutBitSize";
	START_LAPTIMER(781);
	UTL_SetFcmConfigDutBitSize( arg1, arg2);
	STOP_LAPTIMER(781);
}
void _UTL_SetFcmConfigAddrAssign( FcmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[782] = "UTL_SetFcmConfigAddrAssign";
	START_LAPTIMER(782);
	UTL_SetFcmConfigAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(782);
}
void _UTL_SetFcmConfigSplitAddrAssign( FcmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[783] = "UTL_SetFcmConfigSplitAddrAssign";
	START_LAPTIMER(783);
	UTL_SetFcmConfigSplitAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(783);
}
void _UTL_SetFcmConfigAddrAssignByAlpg( FcmConfigHandle arg1, RadioButton arg2, RadioButton arg3, RadioButton arg4)
{
	MCI_LIST[784] = "UTL_SetFcmConfigAddrAssignByAlpg";
	START_LAPTIMER(784);
	UTL_SetFcmConfigAddrAssignByAlpg( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(784);
}
void _UTL_SetFcmConfigAlpgUnit( FcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[785] = "UTL_SetFcmConfigAlpgUnit";
	START_LAPTIMER(785);
	UTL_SetFcmConfigAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(785);
}
void _UTL_AddFcmConfigPinAssign( FcmConfigHandle arg1, RadioButton arg2, UT_PIN arg3)
{
	MCI_LIST[786] = "UTL_AddFcmConfigPinAssign";
	START_LAPTIMER(786);
	UTL_AddFcmConfigPinAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(786);
}
void _UTL_ClearFcmConfigPinAssign( FcmConfigHandle arg1)
{
	MCI_LIST[787] = "UTL_ClearFcmConfigPinAssign";
	START_LAPTIMER(787);
	UTL_ClearFcmConfigPinAssign( arg1);
	STOP_LAPTIMER(787);
}
void _UTL_SetFcmConfigPinAssignTarget( FcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[788] = "UTL_SetFcmConfigPinAssignTarget";
	START_LAPTIMER(788);
	UTL_SetFcmConfigPinAssignTarget( arg1, arg2);
	STOP_LAPTIMER(788);
}
void _UTL_AddFcmConfigMaskPinAssign( FcmConfigHandle arg1, RadioButton arg2, UT_PIN arg3)
{
	MCI_LIST[789] = "UTL_AddFcmConfigMaskPinAssign";
	START_LAPTIMER(789);
	UTL_AddFcmConfigMaskPinAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(789);
}
void _UTL_ClearFcmConfigMaskPinAssign( FcmConfigHandle arg1)
{
	MCI_LIST[790] = "UTL_ClearFcmConfigMaskPinAssign";
	START_LAPTIMER(790);
	UTL_ClearFcmConfigMaskPinAssign( arg1);
	STOP_LAPTIMER(790);
}
void _UTL_AddFcmConfigBitSelect( FcmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[791] = "UTL_AddFcmConfigBitSelect";
	START_LAPTIMER(791);
	UTL_AddFcmConfigBitSelect( arg1, arg2, arg3);
	STOP_LAPTIMER(791);
}
void _UTL_ClearFcmConfigBitSelect( FcmConfigHandle arg1)
{
	MCI_LIST[792] = "UTL_ClearFcmConfigBitSelect";
	START_LAPTIMER(792);
	UTL_ClearFcmConfigBitSelect( arg1);
	STOP_LAPTIMER(792);
}
void _UTL_SetFcmConfigBitSelectTarget( FcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[793] = "UTL_SetFcmConfigBitSelectTarget";
	START_LAPTIMER(793);
	UTL_SetFcmConfigBitSelectTarget( arg1, arg2);
	STOP_LAPTIMER(793);
}
void _UTL_SetFcmConfigStoreSignal( FcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[794] = "UTL_SetFcmConfigStoreSignal";
	START_LAPTIMER(794);
	UTL_SetFcmConfigStoreSignal( arg1, arg2);
	STOP_LAPTIMER(794);
}
void _UTL_SetFcmConfigStoreSignalByMMType( FcmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[795] = "UTL_SetFcmConfigStoreSignalByMMType";
	START_LAPTIMER(795);
	UTL_SetFcmConfigStoreSignalByMMType( arg1, arg2, arg3);
	STOP_LAPTIMER(795);
}
void _UTL_SetFcmConfigStoreInhSignal( FcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[796] = "UTL_SetFcmConfigStoreInhSignal";
	START_LAPTIMER(796);
	UTL_SetFcmConfigStoreInhSignal( arg1, arg2);
	STOP_LAPTIMER(796);
}
void _UTL_SetFcmConfigAddrScram( FcmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[797] = "UTL_SetFcmConfigAddrScram";
	START_LAPTIMER(797);
	UTL_SetFcmConfigAddrScram( arg1, arg2);
	STOP_LAPTIMER(797);
}
void _UTL_SetFcmConfigAddrScramByAlpg( FcmConfigHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[798] = "UTL_SetFcmConfigAddrScramByAlpg";
	START_LAPTIMER(798);
	UTL_SetFcmConfigAddrScramByAlpg( arg1, arg2, arg3);
	STOP_LAPTIMER(798);
}
void _UTL_AddFcmConfigAction( FcmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[799] = "UTL_AddFcmConfigAction";
	START_LAPTIMER(799);
	UTL_AddFcmConfigAction( arg1, arg2, arg3);
	STOP_LAPTIMER(799);
}
void _UTL_ClearFcmConfigAction( FcmConfigHandle arg1)
{
	MCI_LIST[800] = "UTL_ClearFcmConfigAction";
	START_LAPTIMER(800);
	UTL_ClearFcmConfigAction( arg1);
	STOP_LAPTIMER(800);
}
void _UTL_AddFcmConfigStrbChannel( FcmConfigHandle arg1, RadioButton arg2, RadioButton arg3, RadioButton arg4, RadioButton arg5)
{
	MCI_LIST[801] = "UTL_AddFcmConfigStrbChannel";
	START_LAPTIMER(801);
	UTL_AddFcmConfigStrbChannel( arg1, arg2, arg3, arg4, arg5);
	STOP_LAPTIMER(801);
}
void _UTL_ClearFcmConfigStrbChannel( FcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[802] = "UTL_ClearFcmConfigStrbChannel";
	START_LAPTIMER(802);
	UTL_ClearFcmConfigStrbChannel( arg1, arg2);
	STOP_LAPTIMER(802);
}
void _UTL_SetFcmConfigRate( FcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[803] = "UTL_SetFcmConfigRate";
	START_LAPTIMER(803);
	UTL_SetFcmConfigRate( arg1, arg2);
	STOP_LAPTIMER(803);
}
void _UTL_SetFcmConfigDelay( FcmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[804] = "UTL_SetFcmConfigDelay";
	START_LAPTIMER(804);
	UTL_SetFcmConfigDelay( arg1, arg2);
	STOP_LAPTIMER(804);
}
void _UTL_SetFcmConfigDelayByAlpg( FcmConfigHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[805] = "UTL_SetFcmConfigDelayByAlpg";
	START_LAPTIMER(805);
	UTL_SetFcmConfigDelayByAlpg( arg1, arg2, arg3);
	STOP_LAPTIMER(805);
}
void _UTL_SetFcmConfigModeDelayByAlpg( FcmConfigHandle  arg1, RadioButton  arg2, RadioButton  arg3, USlider  arg4)
{
	MCI_LIST[806] = "UTL_SetFcmConfigModeDelayByAlpg";
	START_LAPTIMER(806);
	UTL_SetFcmConfigModeDelayByAlpg( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(806);
}
void _UTL_SetFcmConfigSparePackageMode( FcmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[807] = "UTL_SetFcmConfigSparePackageMode";
	START_LAPTIMER(807);
	UTL_SetFcmConfigSparePackageMode( arg1, arg2);
	STOP_LAPTIMER(807);
}
void _UTL_SetFcmConfigSpareAddrAssign( FcmConfigHandle arg1, RadioButton arg2, RadioButton arg3, RadioButton arg4)
{
	MCI_LIST[808] = "UTL_SetFcmConfigSpareAddrAssign";
	START_LAPTIMER(808);
	UTL_SetFcmConfigSpareAddrAssign( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(808);
}
void _UTL_SetFcmConfigDdrMode( FcmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[809] = "UTL_SetFcmConfigDdrMode";
	START_LAPTIMER(809);
	UTL_SetFcmConfigDdrMode( arg1, arg2);
	STOP_LAPTIMER(809);
}
void _UTL_SetFcmConfigExMode( FcmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[810] = "UTL_SetFcmConfigExMode";
	START_LAPTIMER(810);
	UTL_SetFcmConfigExMode( arg1, arg2);
	STOP_LAPTIMER(810);
}
void _UTL_SetFcmConfigPfcNoClear( FcmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[811] = "UTL_SetFcmConfigPfcNoClear";
	START_LAPTIMER(811);
	UTL_SetFcmConfigPfcNoClear( arg1, arg2);
	STOP_LAPTIMER(811);
}
void _UTL_SetFcmConfigTransferSize( FcmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[812] = "UTL_SetFcmConfigTransferSize";
	START_LAPTIMER(812);
	UTL_SetFcmConfigTransferSize( arg1, arg2);
	STOP_LAPTIMER(812);
}
void _UTL_SetFcmConfigResetInhibit( FcmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[813] = "UTL_SetFcmConfigResetInhibit";
	START_LAPTIMER(813);
	UTL_SetFcmConfigResetInhibit( arg1, arg2);
	STOP_LAPTIMER(813);
}
void _UTL_SetFcmConfigScramEnableStartAddrBit( FcmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[814] = "UTL_SetFcmConfigScramEnableStartAddrBit";
	START_LAPTIMER(814);
	UTL_SetFcmConfigScramEnableStartAddrBit( arg1, arg2);
	STOP_LAPTIMER(814);
}
void _UTL_SetFcmConfigBurstCaptureLength( FcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[815] = "UTL_SetFcmConfigBurstCaptureLength";
	START_LAPTIMER(815);
	UTL_SetFcmConfigBurstCaptureLength( arg1, arg2);
	STOP_LAPTIMER(815);
}
void _UTL_SetFcmConfigRealTimeCountEnable( FcmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[816] = "UTL_SetFcmConfigRealTimeCountEnable";
	START_LAPTIMER(816);
	UTL_SetFcmConfigRealTimeCountEnable( arg1, arg2);
	STOP_LAPTIMER(816);
}
void _UTL_SetFcmConfigFcsmMaxStoreCnt( FcmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[817] = "UTL_SetFcmConfigFcsmMaxStoreCnt";
	START_LAPTIMER(817);
	UTL_SetFcmConfigFcsmMaxStoreCnt( arg1, arg2);
	STOP_LAPTIMER(817);
}
void _UTL_AddFcmConfigAreaDivisionBit( FcmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[818] = "UTL_AddFcmConfigAreaDivisionBit";
	START_LAPTIMER(818);
	UTL_AddFcmConfigAreaDivisionBit( arg1, arg2, arg3);
	STOP_LAPTIMER(818);
}
void _UTL_ClearFcmConfigAreaDivisionBit( FcmConfigHandle arg1)
{
	MCI_LIST[819] = "UTL_ClearFcmConfigAreaDivisionBit";
	START_LAPTIMER(819);
	UTL_ClearFcmConfigAreaDivisionBit( arg1);
	STOP_LAPTIMER(819);
}
void _UTL_SendFcmConfig( FcmConfigHandle arg1)
{
	MCI_LIST[820] = "UTL_SendFcmConfig";
	START_LAPTIMER(820);
	UTL_SendFcmConfig( arg1);
	STOP_LAPTIMER(820);
}
FcmAccessHandle _UTL_GetFcmAccessHandle()
{
	MCI_LIST[821] = "UTL_GetFcmAccessHandle";
	START_LAPTIMER(821);
	FcmAccessHandle retval = UTL_GetFcmAccessHandle();
	STOP_LAPTIMER(821);
	return retval;
}
void _UTL_SetFcmAccessAlpgUnit( FcmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[822] = "UTL_SetFcmAccessAlpgUnit";
	START_LAPTIMER(822);
	UTL_SetFcmAccessAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(822);
}
void _UTL_SetFcmAccessAction( FcmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[823] = "UTL_SetFcmAccessAction";
	START_LAPTIMER(823);
	UTL_SetFcmAccessAction( arg1, arg2);
	STOP_LAPTIMER(823);
}
void _UTL_SetFcmAccessActionNumber( FcmAccessHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[824] = "UTL_SetFcmAccessActionNumber";
	START_LAPTIMER(824);
	UTL_SetFcmAccessActionNumber( arg1, arg2, arg3);
	STOP_LAPTIMER(824);
}
void _UTL_SetFcmAccessCompactionMode( FcmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[825] = "UTL_SetFcmAccessCompactionMode";
	START_LAPTIMER(825);
	UTL_SetFcmAccessCompactionMode( arg1, arg2);
	STOP_LAPTIMER(825);
}
void _UTL_SetFcmAccessBitMode( FcmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[826] = "UTL_SetFcmAccessBitMode";
	START_LAPTIMER(826);
	UTL_SetFcmAccessBitMode( arg1, arg2);
	STOP_LAPTIMER(826);
}
void _UTL_SetFcmAccessAllBit( FcmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[827] = "UTL_SetFcmAccessAllBit";
	START_LAPTIMER(827);
	UTL_SetFcmAccessAllBit( arg1, arg2);
	STOP_LAPTIMER(827);
}
void _UTL_AddFcmAccessBit( FcmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[828] = "UTL_AddFcmAccessBit";
	START_LAPTIMER(828);
	UTL_AddFcmAccessBit( arg1, arg2);
	STOP_LAPTIMER(828);
}
void _UTL_ClearFcmAccessBit( FcmAccessHandle arg1)
{
	MCI_LIST[829] = "UTL_ClearFcmAccessBit";
	START_LAPTIMER(829);
	UTL_ClearFcmAccessBit( arg1);
	STOP_LAPTIMER(829);
}
void _UTL_SetFcmAccessBitBlock( FcmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[830] = "UTL_SetFcmAccessBitBlock";
	START_LAPTIMER(830);
	UTL_SetFcmAccessBitBlock( arg1, arg2);
	STOP_LAPTIMER(830);
}
void _UTL_SetFcmAccessPresetAllMemory( FcmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[831] = "UTL_SetFcmAccessPresetAllMemory";
	START_LAPTIMER(831);
	UTL_SetFcmAccessPresetAllMemory( arg1, arg2);
	STOP_LAPTIMER(831);
}
void _UTL_SetFcmAccessPresetMemoryInUse( FcmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[832] = "UTL_SetFcmAccessPresetMemoryInUse";
	START_LAPTIMER(832);
	UTL_SetFcmAccessPresetMemoryInUse( arg1, arg2);
	STOP_LAPTIMER(832);
}
void _UTL_SetFcmAccessPresetIgnoreAddr( FcmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[833] = "UTL_SetFcmAccessPresetIgnoreAddr";
	START_LAPTIMER(833);
	UTL_SetFcmAccessPresetIgnoreAddr( arg1, arg2);
	STOP_LAPTIMER(833);
}
void _UTL_SetFcmAccessPresetPreserveFbm( FcmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[834] = "UTL_SetFcmAccessPresetPreserveFbm";
	START_LAPTIMER(834);
	UTL_SetFcmAccessPresetPreserveFbm( arg1, arg2);
	STOP_LAPTIMER(834);
}
void _UTL_SetFcmAccessAutoAddrAssignMode( FcmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[835] = "UTL_SetFcmAccessAutoAddrAssignMode";
	START_LAPTIMER(835);
	UTL_SetFcmAccessAutoAddrAssignMode( arg1, arg2);
	STOP_LAPTIMER(835);
}
void _UTL_SetFcmAccessAddrAssign( FcmAccessHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[836] = "UTL_SetFcmAccessAddrAssign";
	START_LAPTIMER(836);
	UTL_SetFcmAccessAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(836);
}
void _UTL_SetFcmAccessApLink( FcmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[837] = "UTL_SetFcmAccessApLink";
	START_LAPTIMER(837);
	UTL_SetFcmAccessApLink( arg1, arg2);
	STOP_LAPTIMER(837);
}
void _UTL_SetFcmAccessXAddr( FcmAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[838] = "UTL_SetFcmAccessXAddr";
	START_LAPTIMER(838);
	UTL_SetFcmAccessXAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(838);
}
void _UTL_SetFcmAccessYAddr( FcmAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[839] = "UTL_SetFcmAccessYAddr";
	START_LAPTIMER(839);
	UTL_SetFcmAccessYAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(839);
}
void _UTL_SetFcmAccessZAddr( FcmAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[840] = "UTL_SetFcmAccessZAddr";
	START_LAPTIMER(840);
	UTL_SetFcmAccessZAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(840);
}
void _UTL_SetFcmAccessAllDut( FcmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[841] = "UTL_SetFcmAccessAllDut";
	START_LAPTIMER(841);
	UTL_SetFcmAccessAllDut( arg1, arg2);
	STOP_LAPTIMER(841);
}
void _UTL_SetFcmAccessDut( FcmAccessHandle arg1, UT_DUT arg2)
{
	MCI_LIST[842] = "UTL_SetFcmAccessDut";
	START_LAPTIMER(842);
	UTL_SetFcmAccessDut( arg1, arg2);
	STOP_LAPTIMER(842);
}
void _UTL_SetFcmAccessSearchMaxCnt( FcmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[843] = "UTL_SetFcmAccessSearchMaxCnt";
	START_LAPTIMER(843);
	UTL_SetFcmAccessSearchMaxCnt( arg1, arg2);
	STOP_LAPTIMER(843);
}
void _UTL_SetFcmAccessSparePackageMode( FcmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[844] = "UTL_SetFcmAccessSparePackageMode";
	START_LAPTIMER(844);
	UTL_SetFcmAccessSparePackageMode( arg1, arg2);
	STOP_LAPTIMER(844);
}
void _UTL_SetFcmAccessSpareAddrAssign( FcmAccessHandle arg1, RadioButton arg2, RadioButton arg3, RadioButton arg4)
{
	MCI_LIST[845] = "UTL_SetFcmAccessSpareAddrAssign";
	START_LAPTIMER(845);
	UTL_SetFcmAccessSpareAddrAssign( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(845);
}
void _UTL_SetFcmAccessPfcMode( FcmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[846] = "UTL_SetFcmAccessPfcMode";
	START_LAPTIMER(846);
	UTL_SetFcmAccessPfcMode( arg1, arg2);
	STOP_LAPTIMER(846);
}
void _UTL_SetFcmAccessPfcNoClear( FcmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[847] = "UTL_SetFcmAccessPfcNoClear";
	START_LAPTIMER(847);
	UTL_SetFcmAccessPfcNoClear( arg1, arg2);
	STOP_LAPTIMER(847);
}
void _UTL_SetFcmAccessAreaDivision( FcmAccessHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[848] = "UTL_SetFcmAccessAreaDivision";
	START_LAPTIMER(848);
	UTL_SetFcmAccessAreaDivision( arg1, arg2, arg3);
	STOP_LAPTIMER(848);
}
void _UTL_SetFcmAccessAreaDivisionInv( FcmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[849] = "UTL_SetFcmAccessAreaDivisionInv";
	START_LAPTIMER(849);
	UTL_SetFcmAccessAreaDivisionInv( arg1, arg2);
	STOP_LAPTIMER(849);
}
void _UTL_AddFcmAccessAreaDivisionByName( FcmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[850] = "UTL_AddFcmAccessAreaDivisionByName";
	START_LAPTIMER(850);
	UTL_AddFcmAccessAreaDivisionByName( arg1, arg2);
	STOP_LAPTIMER(850);
}
void _UTL_ClearFcmAccessAreaDivisionByName( FcmAccessHandle arg1)
{
	MCI_LIST[851] = "UTL_ClearFcmAccessAreaDivisionByName";
	START_LAPTIMER(851);
	UTL_ClearFcmAccessAreaDivisionByName( arg1);
	STOP_LAPTIMER(851);
}
void _UTL_PresetFcm( FcmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[852] = "UTL_PresetFcm";
	START_LAPTIMER(852);
	UTL_PresetFcm( arg1, arg2);
	STOP_LAPTIMER(852);
}
void _UTL_ReadFcm( FcmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[853] = "UTL_ReadFcm";
	START_LAPTIMER(853);
	UTL_ReadFcm( arg1, arg2, arg3);
	STOP_LAPTIMER(853);
}
void _UTL_WriteFcm( FcmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[854] = "UTL_WriteFcm";
	START_LAPTIMER(854);
	UTL_WriteFcm( arg1, arg2, arg3);
	STOP_LAPTIMER(854);
}
void _UTL_SearchFcmFailAddr( FcmAccessHandle arg1)
{
	MCI_LIST[855] = "UTL_SearchFcmFailAddr";
	START_LAPTIMER(855);
	UTL_SearchFcmFailAddr( arg1);
	STOP_LAPTIMER(855);
}
AddrCursor _UTL_GetFcmFailAddr( RadioButton arg1)
{
	MCI_LIST[856] = "UTL_GetFcmFailAddr";
	START_LAPTIMER(856);
	AddrCursor retval = UTL_GetFcmFailAddr( arg1);
	STOP_LAPTIMER(856);
	return retval;
}
CheckButton _UTL_GetFcmSearchComplete()
{
	MCI_LIST[857] = "UTL_GetFcmSearchComplete";
	START_LAPTIMER(857);
	CheckButton retval = UTL_GetFcmSearchComplete();
	STOP_LAPTIMER(857);
	return retval;
}
void _UTL_CntFcmFailAddr( FcmAccessHandle arg1)
{
	MCI_LIST[858] = "UTL_CntFcmFailAddr";
	START_LAPTIMER(858);
	UTL_CntFcmFailAddr( arg1);
	STOP_LAPTIMER(858);
}
USlider _UTL_GetFcmFailAddrCnt( RadioButton arg1)
{
	MCI_LIST[859] = "UTL_GetFcmFailAddrCnt";
	START_LAPTIMER(859);
	USlider retval = UTL_GetFcmFailAddrCnt( arg1);
	STOP_LAPTIMER(859);
	return retval;
}
CheckButton _UTL_GetFcmFailAddrCntOverflow( RadioButton arg1)
{
	MCI_LIST[860] = "UTL_GetFcmFailAddrCntOverflow";
	START_LAPTIMER(860);
	CheckButton retval = UTL_GetFcmFailAddrCntOverflow( arg1);
	STOP_LAPTIMER(860);
	return retval;
}
void _UTL_ParallelFailCountFcm( FcmAccessHandle arg1)
{
	MCI_LIST[861] = "UTL_ParallelFailCountFcm";
	START_LAPTIMER(861);
	UTL_ParallelFailCountFcm( arg1);
	STOP_LAPTIMER(861);
}
USlider _UTL_GetFcmParallelFailCount( FcmAccessHandle arg1)
{
	MCI_LIST[862] = "UTL_GetFcmParallelFailCount";
	START_LAPTIMER(862);
	USlider retval = UTL_GetFcmParallelFailCount( arg1);
	STOP_LAPTIMER(862);
	return retval;
}
CheckButton _UTL_GetFcmParallelFailCountOverflow( FcmAccessHandle arg1)
{
	MCI_LIST[863] = "UTL_GetFcmParallelFailCountOverflow";
	START_LAPTIMER(863);
	CheckButton retval = UTL_GetFcmParallelFailCountOverflow( arg1);
	STOP_LAPTIMER(863);
	return retval;
}
void _UTL_MoveFcm( FcmAccessHandle arg1)
{
	MCI_LIST[864] = "UTL_MoveFcm";
	START_LAPTIMER(864);
	UTL_MoveFcm( arg1);
	STOP_LAPTIMER(864);
}
void _UTL_RemoveFcm( FcmAccessHandle arg1)
{
	MCI_LIST[865] = "UTL_RemoveFcm";
	START_LAPTIMER(865);
	UTL_RemoveFcm( arg1);
	STOP_LAPTIMER(865);
}
RadioButton _UTL_ReadFcmFailOverflow( FcmAccessHandle  arg1)
{
	MCI_LIST[866] = "UTL_ReadFcmFailOverflow";
	START_LAPTIMER(866);
	RadioButton retval = UTL_ReadFcmFailOverflow( arg1);
	STOP_LAPTIMER(866);
	return retval;
}
void _UTL_ResetFcsmStoreCnt()
{
	MCI_LIST[867] = "UTL_ResetFcsmStoreCnt";
	START_LAPTIMER(867);
	UTL_ResetFcsmStoreCnt();
	STOP_LAPTIMER(867);
}
void _UTL_ResetFcsm( FcmAccessHandle  arg1)
{
	MCI_LIST[868] = "UTL_ResetFcsm";
	START_LAPTIMER(868);
	UTL_ResetFcsm( arg1);
	STOP_LAPTIMER(868);
}
CheckButton _UTL_ReadFcsmStoreCnt( FcmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[869] = "UTL_ReadFcsmStoreCnt";
	START_LAPTIMER(869);
	CheckButton retval = UTL_ReadFcsmStoreCnt( arg1, arg2);
	STOP_LAPTIMER(869);
	return retval;
}
void _UTL_ReadFcsm( FcmAccessHandle  arg1, void * arg2, USlider  arg3)
{
	MCI_LIST[870] = "UTL_ReadFcsm";
	START_LAPTIMER(870);
	UTL_ReadFcsm( arg1, arg2, arg3);
	STOP_LAPTIMER(870);
}
UT_ADDR _UTL_NextAddr( AddrCursor arg1)
{
	MCI_LIST[871] = "UTL_NextAddr";
	START_LAPTIMER(871);
	UT_ADDR retval = UTL_NextAddr( arg1);
	STOP_LAPTIMER(871);
	return retval;
}
USlider _UTL_GetXAddr( UT_ADDR arg1)
{
	MCI_LIST[872] = "UTL_GetXAddr";
	START_LAPTIMER(872);
	USlider retval = UTL_GetXAddr( arg1);
	STOP_LAPTIMER(872);
	return retval;
}
USlider _UTL_GetYAddr( UT_ADDR arg1)
{
	MCI_LIST[873] = "UTL_GetYAddr";
	START_LAPTIMER(873);
	USlider retval = UTL_GetYAddr( arg1);
	STOP_LAPTIMER(873);
	return retval;
}
USlider _UTL_GetZAddr( UT_ADDR arg1)
{
	MCI_LIST[874] = "UTL_GetZAddr";
	START_LAPTIMER(874);
	USlider retval = UTL_GetZAddr( arg1);
	STOP_LAPTIMER(874);
	return retval;
}
BbmConfigHandle _UTL_GetBbmConfigHandle()
{
	MCI_LIST[875] = "UTL_GetBbmConfigHandle";
	START_LAPTIMER(875);
	BbmConfigHandle retval = UTL_GetBbmConfigHandle();
	STOP_LAPTIMER(875);
	return retval;
}
void _UTL_SetBbmConfigMode( BbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[876] = "UTL_SetBbmConfigMode";
	START_LAPTIMER(876);
	UTL_SetBbmConfigMode( arg1, arg2);
	STOP_LAPTIMER(876);
}
void _UTL_SetBbmConfigAction( BbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[877] = "UTL_SetBbmConfigAction";
	START_LAPTIMER(877);
	UTL_SetBbmConfigAction( arg1, arg2);
	STOP_LAPTIMER(877);
}
void _UTL_SetBbmConfigStoreMode( BbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[878] = "UTL_SetBbmConfigStoreMode";
	START_LAPTIMER(878);
	UTL_SetBbmConfigStoreMode( arg1, arg2);
	STOP_LAPTIMER(878);
}
void _UTL_SetBbmConfigCaptureSignal( BbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[879] = "UTL_SetBbmConfigCaptureSignal";
	START_LAPTIMER(879);
	UTL_SetBbmConfigCaptureSignal( arg1, arg2);
	STOP_LAPTIMER(879);
}
void _UTL_SetBbmConfigDataGenerationMode( BbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[880] = "UTL_SetBbmConfigDataGenerationMode";
	START_LAPTIMER(880);
	UTL_SetBbmConfigDataGenerationMode( arg1, arg2);
	STOP_LAPTIMER(880);
}
void _UTL_SetBbmConfigWriteEnableAllDut( BbmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[881] = "UTL_SetBbmConfigWriteEnableAllDut";
	START_LAPTIMER(881);
	UTL_SetBbmConfigWriteEnableAllDut( arg1, arg2);
	STOP_LAPTIMER(881);
}
void _UTL_SetBbmConfigWriteEnableByDut( BbmConfigHandle arg1, CheckButton arg2, UT_DUT arg3)
{
	MCI_LIST[882] = "UTL_SetBbmConfigWriteEnableByDut";
	START_LAPTIMER(882);
	UTL_SetBbmConfigWriteEnableByDut( arg1, arg2, arg3);
	STOP_LAPTIMER(882);
}
void _UTL_SetBbmConfigBitSize( BbmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[883] = "UTL_SetBbmConfigBitSize";
	START_LAPTIMER(883);
	UTL_SetBbmConfigBitSize( arg1, arg2);
	STOP_LAPTIMER(883);
}
void _UTL_SetBbmConfigAddrAssign( BbmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[884] = "UTL_SetBbmConfigAddrAssign";
	START_LAPTIMER(884);
	UTL_SetBbmConfigAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(884);
}
void _UTL_SetBbmConfigDelay( BbmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[885] = "UTL_SetBbmConfigDelay";
	START_LAPTIMER(885);
	UTL_SetBbmConfigDelay( arg1, arg2);
	STOP_LAPTIMER(885);
}
void _UTL_AddBbmConfigStrbChannel( BbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[886] = "UTL_AddBbmConfigStrbChannel";
	START_LAPTIMER(886);
	UTL_AddBbmConfigStrbChannel( arg1, arg2);
	STOP_LAPTIMER(886);
}
void _UTL_ClearBbmConfigStrbChannel( BbmConfigHandle arg1)
{
	MCI_LIST[887] = "UTL_ClearBbmConfigStrbChannel";
	START_LAPTIMER(887);
	UTL_ClearBbmConfigStrbChannel( arg1);
	STOP_LAPTIMER(887);
}
void _UTL_SetBbmConfigBbcLimitAllDut( BbmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[888] = "UTL_SetBbmConfigBbcLimitAllDut";
	START_LAPTIMER(888);
	UTL_SetBbmConfigBbcLimitAllDut( arg1, arg2);
	STOP_LAPTIMER(888);
}
void _UTL_SetBbmConfigBbcLimitByDut( BbmConfigHandle arg1, USlider arg2, UT_DUT arg3)
{
	MCI_LIST[889] = "UTL_SetBbmConfigBbcLimitByDut";
	START_LAPTIMER(889);
	UTL_SetBbmConfigBbcLimitByDut( arg1, arg2, arg3);
	STOP_LAPTIMER(889);
}
void _UTL_SetBbmConfigBbcLimitByBit( BbmConfigHandle arg1, USlider arg2, RadioButton arg3)
{
	MCI_LIST[890] = "UTL_SetBbmConfigBbcLimitByBit";
	START_LAPTIMER(890);
	UTL_SetBbmConfigBbcLimitByBit( arg1, arg2, arg3);
	STOP_LAPTIMER(890);
}
void _UTL_AddBbmConfigDrInhPin( BbmConfigHandle arg1, UT_PIN arg2, RadioButton arg3)
{
	MCI_LIST[891] = "UTL_AddBbmConfigDrInhPin";
	START_LAPTIMER(891);
	UTL_AddBbmConfigDrInhPin( arg1, arg2, arg3);
	STOP_LAPTIMER(891);
}
void _UTL_ClearBbmConfigDrInhPin( BbmConfigHandle arg1)
{
	MCI_LIST[892] = "UTL_ClearBbmConfigDrInhPin";
	START_LAPTIMER(892);
	UTL_ClearBbmConfigDrInhPin( arg1);
	STOP_LAPTIMER(892);
}
void _UTL_AddBbmConfigFailLoopBackPin( BbmConfigHandle arg1, UT_PIN arg2)
{
	MCI_LIST[893] = "UTL_AddBbmConfigFailLoopBackPin";
	START_LAPTIMER(893);
	UTL_AddBbmConfigFailLoopBackPin( arg1, arg2);
	STOP_LAPTIMER(893);
}
void _UTL_ClearBbmConfigFailLoopBackPin( BbmConfigHandle arg1)
{
	MCI_LIST[894] = "UTL_ClearBbmConfigFailLoopBackPin";
	START_LAPTIMER(894);
	UTL_ClearBbmConfigFailLoopBackPin( arg1);
	STOP_LAPTIMER(894);
}
void _UTL_SetBbmConfigPatternCycle( BbmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[895] = "UTL_SetBbmConfigPatternCycle";
	START_LAPTIMER(895);
	UTL_SetBbmConfigPatternCycle( arg1, arg2, arg3);
	STOP_LAPTIMER(895);
}
void _UTL_AddBbmConfigCaptureDataByTargetBank( BbmConfigHandle arg1, RadioButton arg2, UT_DUT arg3, RadioButton arg4, RadioButton arg5)
{
	MCI_LIST[896] = "UTL_AddBbmConfigCaptureDataByTargetBank";
	START_LAPTIMER(896);
	UTL_AddBbmConfigCaptureDataByTargetBank( arg1, arg2, arg3, arg4, arg5);
	STOP_LAPTIMER(896);
}
void _UTL_ClearBbmConfigCaptureData( BbmConfigHandle arg1)
{
	MCI_LIST[897] = "UTL_ClearBbmConfigCaptureData";
	START_LAPTIMER(897);
	UTL_ClearBbmConfigCaptureData( arg1);
	STOP_LAPTIMER(897);
}
void _UTL_AddBbmConfigMaskBit( BbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[898] = "UTL_AddBbmConfigMaskBit";
	START_LAPTIMER(898);
	UTL_AddBbmConfigMaskBit( arg1, arg2);
	STOP_LAPTIMER(898);
}
void _UTL_AddBbmConfigMaskBitByTargetBank( BbmConfigHandle arg1, UT_DUT arg2, RadioButton arg3, RadioButton arg4)
{
	MCI_LIST[899] = "UTL_AddBbmConfigMaskBitByTargetBank";
	START_LAPTIMER(899);
	UTL_AddBbmConfigMaskBitByTargetBank( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(899);
}
void _UTL_ClearBbmConfigMaskBit( BbmConfigHandle arg1)
{
	MCI_LIST[900] = "UTL_ClearBbmConfigMaskBit";
	START_LAPTIMER(900);
	UTL_ClearBbmConfigMaskBit( arg1);
	STOP_LAPTIMER(900);
}
void _UTL_AddBbmConfigBbcLimitMaskBit( BbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[901] = "UTL_AddBbmConfigBbcLimitMaskBit";
	START_LAPTIMER(901);
	UTL_AddBbmConfigBbcLimitMaskBit( arg1, arg2);
	STOP_LAPTIMER(901);
}
void _UTL_AddBbmConfigBbcLimitMaskBitByTargetBank( BbmConfigHandle arg1, UT_DUT arg2, RadioButton arg3, RadioButton arg4)
{
	MCI_LIST[902] = "UTL_AddBbmConfigBbcLimitMaskBitByTargetBank";
	START_LAPTIMER(902);
	UTL_AddBbmConfigBbcLimitMaskBitByTargetBank( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(902);
}
void _UTL_ClearBbmConfigBbcLimitMaskBit( BbmConfigHandle arg1)
{
	MCI_LIST[903] = "UTL_ClearBbmConfigBbcLimitMaskBit";
	START_LAPTIMER(903);
	UTL_ClearBbmConfigBbcLimitMaskBit( arg1);
	STOP_LAPTIMER(903);
}
void _UTL_SetBbmConfigSkipSignal( BbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[904] = "UTL_SetBbmConfigSkipSignal";
	START_LAPTIMER(904);
	UTL_SetBbmConfigSkipSignal( arg1, arg2);
	STOP_LAPTIMER(904);
}
void _UTL_SetBbmConfigStatusSignal( BbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[905] = "UTL_SetBbmConfigStatusSignal";
	START_LAPTIMER(905);
	UTL_SetBbmConfigStatusSignal( arg1, arg2);
	STOP_LAPTIMER(905);
}
void _UTL_SetBbmConfigCounterNoClear( BbmConfigHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[906] = "UTL_SetBbmConfigCounterNoClear";
	START_LAPTIMER(906);
	UTL_SetBbmConfigCounterNoClear( arg1, arg2, arg3);
	STOP_LAPTIMER(906);
}
void _UTL_SetBbmConfigPlaneCount( BbmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[907] = "UTL_SetBbmConfigPlaneCount";
	START_LAPTIMER(907);
	UTL_SetBbmConfigPlaneCount( arg1, arg2);
	STOP_LAPTIMER(907);
}
void _UTL_SendBbmConfig( BbmConfigHandle arg1)
{
	MCI_LIST[908] = "UTL_SendBbmConfig";
	START_LAPTIMER(908);
	UTL_SendBbmConfig( arg1);
	STOP_LAPTIMER(908);
}
BbmAccessHandle _UTL_GetBbmAccessHandle()
{
	MCI_LIST[909] = "UTL_GetBbmAccessHandle";
	START_LAPTIMER(909);
	BbmAccessHandle retval = UTL_GetBbmAccessHandle();
	STOP_LAPTIMER(909);
	return retval;
}
void _UTL_SetBbmAccessPresetAllMemory( BbmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[910] = "UTL_SetBbmAccessPresetAllMemory";
	START_LAPTIMER(910);
	UTL_SetBbmAccessPresetAllMemory( arg1, arg2);
	STOP_LAPTIMER(910);
}
void _UTL_SetBbmAccessAllDut( BbmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[911] = "UTL_SetBbmAccessAllDut";
	START_LAPTIMER(911);
	UTL_SetBbmAccessAllDut( arg1, arg2);
	STOP_LAPTIMER(911);
}
void _UTL_SetBbmAccessDut( BbmAccessHandle arg1, UT_DUT arg2)
{
	MCI_LIST[912] = "UTL_SetBbmAccessDut";
	START_LAPTIMER(912);
	UTL_SetBbmAccessDut( arg1, arg2);
	STOP_LAPTIMER(912);
}
void _UTL_SetBbmAccessChannel( BbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[913] = "UTL_SetBbmAccessChannel";
	START_LAPTIMER(913);
	UTL_SetBbmAccessChannel( arg1, arg2);
	STOP_LAPTIMER(913);
}
void _UTL_SetBbmAccessStartAddr( BbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[914] = "UTL_SetBbmAccessStartAddr";
	START_LAPTIMER(914);
	UTL_SetBbmAccessStartAddr( arg1, arg2);
	STOP_LAPTIMER(914);
}
void _UTL_SetBbmAccessStopAddr( BbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[915] = "UTL_SetBbmAccessStopAddr";
	START_LAPTIMER(915);
	UTL_SetBbmAccessStopAddr( arg1, arg2);
	STOP_LAPTIMER(915);
}
void _UTL_SetBbmAccessAddrAssign( BbmAccessHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[916] = "UTL_SetBbmAccessAddrAssign";
	START_LAPTIMER(916);
	UTL_SetBbmAccessAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(916);
}
void _UTL_SetBbmAccessXAddr( BbmAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[917] = "UTL_SetBbmAccessXAddr";
	START_LAPTIMER(917);
	UTL_SetBbmAccessXAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(917);
}
void _UTL_SetBbmAccessYAddr( BbmAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[918] = "UTL_SetBbmAccessYAddr";
	START_LAPTIMER(918);
	UTL_SetBbmAccessYAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(918);
}
void _UTL_SetBbmAccessZAddr( BbmAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[919] = "UTL_SetBbmAccessZAddr";
	START_LAPTIMER(919);
	UTL_SetBbmAccessZAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(919);
}
void _UTL_SetBbmAccessApLink( BbmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[920] = "UTL_SetBbmAccessApLink";
	START_LAPTIMER(920);
	UTL_SetBbmAccessApLink( arg1, arg2);
	STOP_LAPTIMER(920);
}
void _UTL_SetBbmAccessBitBlock( BbmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[921] = "UTL_SetBbmAccessBitBlock";
	START_LAPTIMER(921);
	UTL_SetBbmAccessBitBlock( arg1, arg2);
	STOP_LAPTIMER(921);
}
void _UTL_SetBbmAccessCounterMode( BbmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[922] = "UTL_SetBbmAccessCounterMode";
	START_LAPTIMER(922);
	UTL_SetBbmAccessCounterMode( arg1, arg2);
	STOP_LAPTIMER(922);
}
void _UTL_SetBbmAccessEnableCounter( BbmAccessHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[923] = "UTL_SetBbmAccessEnableCounter";
	START_LAPTIMER(923);
	UTL_SetBbmAccessEnableCounter( arg1, arg2, arg3);
	STOP_LAPTIMER(923);
}
void _UTL_SetBbmAccessSearchMaxCnt( BbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[924] = "UTL_SetBbmAccessSearchMaxCnt";
	START_LAPTIMER(924);
	UTL_SetBbmAccessSearchMaxCnt( arg1, arg2);
	STOP_LAPTIMER(924);
}
void _UTL_SetBbmAccessBitMode( BbmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[925] = "UTL_SetBbmAccessBitMode";
	START_LAPTIMER(925);
	UTL_SetBbmAccessBitMode( arg1, arg2);
	STOP_LAPTIMER(925);
}
void _UTL_SetBbmAccessAllBit( BbmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[926] = "UTL_SetBbmAccessAllBit";
	START_LAPTIMER(926);
	UTL_SetBbmAccessAllBit( arg1, arg2);
	STOP_LAPTIMER(926);
}
void _UTL_AddBbmAccessBit( BbmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[927] = "UTL_AddBbmAccessBit";
	START_LAPTIMER(927);
	UTL_AddBbmAccessBit( arg1, arg2);
	STOP_LAPTIMER(927);
}
void _UTL_ClearBbmAccessBit( BbmAccessHandle arg1)
{
	MCI_LIST[928] = "UTL_ClearBbmAccessBit";
	START_LAPTIMER(928);
	UTL_ClearBbmAccessBit( arg1);
	STOP_LAPTIMER(928);
}
void _UTL_SetBbmAccessMatchData( BbmAccessHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[929] = "UTL_SetBbmAccessMatchData";
	START_LAPTIMER(929);
	UTL_SetBbmAccessMatchData( arg1, arg2, arg3);
	STOP_LAPTIMER(929);
}
void _UTL_SetBbmAccessScanInvert( BbmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[930] = "UTL_SetBbmAccessScanInvert";
	START_LAPTIMER(930);
	UTL_SetBbmAccessScanInvert( arg1, arg2);
	STOP_LAPTIMER(930);
}
void _UTL_SetBbmAccessWriteMode( BbmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[931] = "UTL_SetBbmAccessWriteMode";
	START_LAPTIMER(931);
	UTL_SetBbmAccessWriteMode( arg1, arg2);
	STOP_LAPTIMER(931);
}
void _UTL_SetBbmAccessCounterNoClear( BbmConfigHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[932] = "UTL_SetBbmAccessCounterNoClear";
	START_LAPTIMER(932);
	UTL_SetBbmAccessCounterNoClear( arg1, arg2, arg3);
	STOP_LAPTIMER(932);
}
void _UTL_PresetBbm( BbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[933] = "UTL_PresetBbm";
	START_LAPTIMER(933);
	UTL_PresetBbm( arg1, arg2);
	STOP_LAPTIMER(933);
}
void _UTL_ReadBbm( BbmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[934] = "UTL_ReadBbm";
	START_LAPTIMER(934);
	UTL_ReadBbm( arg1, arg2, arg3);
	STOP_LAPTIMER(934);
}
void _UTL_WriteBbm( BbmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[935] = "UTL_WriteBbm";
	START_LAPTIMER(935);
	UTL_WriteBbm( arg1, arg2, arg3);
	STOP_LAPTIMER(935);
}
void _UTL_CntBbmFailAddr( BbmAccessHandle arg1)
{
	MCI_LIST[936] = "UTL_CntBbmFailAddr";
	START_LAPTIMER(936);
	UTL_CntBbmFailAddr( arg1);
	STOP_LAPTIMER(936);
}
USlider _UTL_ReadBadBlockCounter( BbmAccessHandle arg1, RadioButton * arg2)
{
	MCI_LIST[937] = "UTL_ReadBadBlockCounter";
	START_LAPTIMER(937);
	USlider retval = UTL_ReadBadBlockCounter( arg1, arg2);
	STOP_LAPTIMER(937);
	return retval;
}
void _UTL_WriteBadBlockCounter( BbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[938] = "UTL_WriteBadBlockCounter";
	START_LAPTIMER(938);
	UTL_WriteBadBlockCounter( arg1, arg2);
	STOP_LAPTIMER(938);
}
void _UTL_SearchBbmFailAddr( BbmAccessHandle arg1)
{
	MCI_LIST[939] = "UTL_SearchBbmFailAddr";
	START_LAPTIMER(939);
	UTL_SearchBbmFailAddr( arg1);
	STOP_LAPTIMER(939);
}
AddrPointerCursor _UTL_GetBbmFailAddrPointer( BbmAccessHandle arg1)
{
	MCI_LIST[940] = "UTL_GetBbmFailAddrPointer";
	START_LAPTIMER(940);
	AddrPointerCursor retval = UTL_GetBbmFailAddrPointer( arg1);
	STOP_LAPTIMER(940);
	return retval;
}
USlider _UTL_NextAddrPointer( AddrPointerCursor arg1)
{
	MCI_LIST[941] = "UTL_NextAddrPointer";
	START_LAPTIMER(941);
	USlider retval = UTL_NextAddrPointer( arg1);
	STOP_LAPTIMER(941);
	return retval;
}
CheckButton _UTL_GetBbmSearchComplete( BbmAccessHandle arg1)
{
	MCI_LIST[942] = "UTL_GetBbmSearchComplete";
	START_LAPTIMER(942);
	CheckButton retval = UTL_GetBbmSearchComplete( arg1);
	STOP_LAPTIMER(942);
	return retval;
}
RfcmConfigHandle _UTL_GetRfcmConfigHandle()
{
	MCI_LIST[943] = "UTL_GetRfcmConfigHandle";
	START_LAPTIMER(943);
	RfcmConfigHandle retval = UTL_GetRfcmConfigHandle();
	STOP_LAPTIMER(943);
	return retval;
}
void _UTL_SetRfcmConfigMode( RfcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[944] = "UTL_SetRfcmConfigMode";
	START_LAPTIMER(944);
	UTL_SetRfcmConfigMode( arg1, arg2);
	STOP_LAPTIMER(944);
}
void _UTL_SetRfcmConfigAddrAssign( RfcmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[945] = "UTL_SetRfcmConfigAddrAssign";
	START_LAPTIMER(945);
	UTL_SetRfcmConfigAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(945);
}
void _UTL_SetRfcmConfigStopAddr( RfcmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[946] = "UTL_SetRfcmConfigStopAddr";
	START_LAPTIMER(946);
	UTL_SetRfcmConfigStopAddr( arg1, arg2);
	STOP_LAPTIMER(946);
}
void _UTL_SetRfcmConfigTransferSignal( RfcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[947] = "UTL_SetRfcmConfigTransferSignal";
	START_LAPTIMER(947);
	UTL_SetRfcmConfigTransferSignal( arg1, arg2);
	STOP_LAPTIMER(947);
}
void _UTL_SetRfcmConfigClearSignal( RfcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[948] = "UTL_SetRfcmConfigClearSignal";
	START_LAPTIMER(948);
	UTL_SetRfcmConfigClearSignal( arg1, arg2);
	STOP_LAPTIMER(948);
}
void _UTL_SetRfcmConfigRfcsmTransferSignal( RfcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[949] = "UTL_SetRfcmConfigRfcsmTransferSignal";
	START_LAPTIMER(949);
	UTL_SetRfcmConfigRfcsmTransferSignal( arg1, arg2);
	STOP_LAPTIMER(949);
}
void _UTL_SetRfcmConfigRfcsmTransferMode( RfcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[950] = "UTL_SetRfcmConfigRfcsmTransferMode";
	START_LAPTIMER(950);
	UTL_SetRfcmConfigRfcsmTransferMode( arg1, arg2);
	STOP_LAPTIMER(950);
}
void _UTL_SetRfcmConfigRfcsmClearSignal( RfcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[951] = "UTL_SetRfcmConfigRfcsmClearSignal";
	START_LAPTIMER(951);
	UTL_SetRfcmConfigRfcsmClearSignal( arg1, arg2);
	STOP_LAPTIMER(951);
}
void _UTL_SetRfcmConfigFccLimitAllDut( RfcmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[952] = "UTL_SetRfcmConfigFccLimitAllDut";
	START_LAPTIMER(952);
	UTL_SetRfcmConfigFccLimitAllDut( arg1, arg2);
	STOP_LAPTIMER(952);
}
void _UTL_SetRfcmConfigFccLimitByDut( RfcmConfigHandle arg1, USlider arg2, UT_DUT arg3)
{
	MCI_LIST[953] = "UTL_SetRfcmConfigFccLimitByDut";
	START_LAPTIMER(953);
	UTL_SetRfcmConfigFccLimitByDut( arg1, arg2, arg3);
	STOP_LAPTIMER(953);
}
void _UTL_SetRfcmConfigRfcsmLimitAllDut( RfcmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[954] = "UTL_SetRfcmConfigRfcsmLimitAllDut";
	START_LAPTIMER(954);
	UTL_SetRfcmConfigRfcsmLimitAllDut( arg1, arg2);
	STOP_LAPTIMER(954);
}
void _UTL_SetRfcmConfigRfcsmLimitByDut( RfcmConfigHandle arg1, USlider arg2, UT_DUT arg3)
{
	MCI_LIST[955] = "UTL_SetRfcmConfigRfcsmLimitByDut";
	START_LAPTIMER(955);
	UTL_SetRfcmConfigRfcsmLimitByDut( arg1, arg2, arg3);
	STOP_LAPTIMER(955);
}
void _UTL_SendRfcmConfig( RfcmConfigHandle arg1)
{
	MCI_LIST[956] = "UTL_SendRfcmConfig";
	START_LAPTIMER(956);
	UTL_SendRfcmConfig( arg1);
	STOP_LAPTIMER(956);
}
RfcmAccessHandle _UTL_GetRfcmAccessHandle()
{
	MCI_LIST[957] = "UTL_GetRfcmAccessHandle";
	START_LAPTIMER(957);
	RfcmAccessHandle retval = UTL_GetRfcmAccessHandle();
	STOP_LAPTIMER(957);
	return retval;
}
void _UTL_SetRfcmAccessPresetAllMemory( RfcmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[958] = "UTL_SetRfcmAccessPresetAllMemory";
	START_LAPTIMER(958);
	UTL_SetRfcmAccessPresetAllMemory( arg1, arg2);
	STOP_LAPTIMER(958);
}
void _UTL_SetRfcmAccessDut( RfcmAccessHandle arg1, UT_DUT arg2)
{
	MCI_LIST[959] = "UTL_SetRfcmAccessDut";
	START_LAPTIMER(959);
	UTL_SetRfcmAccessDut( arg1, arg2);
	STOP_LAPTIMER(959);
}
void _UTL_PresetRfcm( RfcmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[960] = "UTL_PresetRfcm";
	START_LAPTIMER(960);
	UTL_PresetRfcm( arg1, arg2);
	STOP_LAPTIMER(960);
}
USlider _UTL_ReadFailColumnCounter( RfcmAccessHandle arg1, RadioButton * arg2)
{
	MCI_LIST[961] = "UTL_ReadFailColumnCounter";
	START_LAPTIMER(961);
	USlider retval = UTL_ReadFailColumnCounter( arg1, arg2);
	STOP_LAPTIMER(961);
	return retval;
}
CfbmConfigHandle _UTL_GetCfbmConfigHandle()
{
	MCI_LIST[962] = "UTL_GetCfbmConfigHandle";
	START_LAPTIMER(962);
	CfbmConfigHandle retval = UTL_GetCfbmConfigHandle();
	STOP_LAPTIMER(962);
	return retval;
}
void _UTL_SetCfbmConfigSplitMemory( CfbmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[963] = "UTL_SetCfbmConfigSplitMemory";
	START_LAPTIMER(963);
	UTL_SetCfbmConfigSplitMemory( arg1, arg2);
	STOP_LAPTIMER(963);
}
void _UTL_SetCfbmConfigCompressMode( CfbmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[964] = "UTL_SetCfbmConfigCompressMode";
	START_LAPTIMER(964);
	UTL_SetCfbmConfigCompressMode( arg1, arg2);
	STOP_LAPTIMER(964);
}
void _UTL_SetCfbmConfigSelectBit( CfbmConfigHandle arg1, USlider arg2, UT_DUT arg3, USlider arg4)
{
	MCI_LIST[965] = "UTL_SetCfbmConfigSelectBit";
	START_LAPTIMER(965);
	UTL_SetCfbmConfigSelectBit( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(965);
}
void _UTL_SetCfbmConfigAddrAssign( CfbmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[966] = "UTL_SetCfbmConfigAddrAssign";
	START_LAPTIMER(966);
	UTL_SetCfbmConfigAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(966);
}
void _UTL_SetCfbmConfigXAddr( CfbmConfigHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[967] = "UTL_SetCfbmConfigXAddr";
	START_LAPTIMER(967);
	UTL_SetCfbmConfigXAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(967);
}
void _UTL_SetCfbmConfigYAddr( CfbmConfigHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[968] = "UTL_SetCfbmConfigYAddr";
	START_LAPTIMER(968);
	UTL_SetCfbmConfigYAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(968);
}
void _UTL_SetCfbmConfigZAddr( CfbmConfigHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[969] = "UTL_SetCfbmConfigZAddr";
	START_LAPTIMER(969);
	UTL_SetCfbmConfigZAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(969);
}
void _UTL_CompressCfbm( CfbmConfigHandle arg1)
{
	MCI_LIST[970] = "UTL_CompressCfbm";
	START_LAPTIMER(970);
	UTL_CompressCfbm( arg1);
	STOP_LAPTIMER(970);
}
CfbmAccessHandle _UTL_GetCfbmAccessHandle()
{
	MCI_LIST[971] = "UTL_GetCfbmAccessHandle";
	START_LAPTIMER(971);
	CfbmAccessHandle retval = UTL_GetCfbmAccessHandle();
	STOP_LAPTIMER(971);
	return retval;
}
void _UTL_SetCfbmAccessPresetAllMemory( CfbmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[972] = "UTL_SetCfbmAccessPresetAllMemory";
	START_LAPTIMER(972);
	UTL_SetCfbmAccessPresetAllMemory( arg1, arg2);
	STOP_LAPTIMER(972);
}
void _UTL_SetCfbmAccessAddrBlock( CfbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[973] = "UTL_SetCfbmAccessAddrBlock";
	START_LAPTIMER(973);
	UTL_SetCfbmAccessAddrBlock( arg1, arg2);
	STOP_LAPTIMER(973);
}
void _UTL_SetCfbmAccessAddrPointer( CfbmAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[974] = "UTL_SetCfbmAccessAddrPointer";
	START_LAPTIMER(974);
	UTL_SetCfbmAccessAddrPointer( arg1, arg2, arg3);
	STOP_LAPTIMER(974);
}
void _UTL_PresetCfbm( CfbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[975] = "UTL_PresetCfbm";
	START_LAPTIMER(975);
	UTL_PresetCfbm( arg1, arg2);
	STOP_LAPTIMER(975);
}
void _UTL_ReadCfbm( CfbmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[976] = "UTL_ReadCfbm";
	START_LAPTIMER(976);
	UTL_ReadCfbm( arg1, arg2, arg3);
	STOP_LAPTIMER(976);
}
void _UTL_WriteCfbm( CfbmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[977] = "UTL_WriteCfbm";
	START_LAPTIMER(977);
	UTL_WriteCfbm( arg1, arg2, arg3);
	STOP_LAPTIMER(977);
}
USlider _UTL_ReadCfbmDataCount( CfbmAccessHandle arg1)
{
	MCI_LIST[978] = "UTL_ReadCfbmDataCount";
	START_LAPTIMER(978);
	USlider retval = UTL_ReadCfbmDataCount( arg1);
	STOP_LAPTIMER(978);
	return retval;
}
USlider _UTL_ReadCfbmFailCount( CfbmAccessHandle arg1, CheckButton * arg2)
{
	MCI_LIST[979] = "UTL_ReadCfbmFailCount";
	START_LAPTIMER(979);
	USlider retval = UTL_ReadCfbmFailCount( arg1, arg2);
	STOP_LAPTIMER(979);
	return retval;
}
CheckButton _UTL_ReadCfbmStatus( CfbmAccessHandle arg1)
{
	MCI_LIST[980] = "UTL_ReadCfbmStatus";
	START_LAPTIMER(980);
	CheckButton retval = UTL_ReadCfbmStatus( arg1);
	STOP_LAPTIMER(980);
	return retval;
}
RadioButton _UTL_ReadCfbmPassFailInfo( CfbmAccessHandle arg1)
{
	MCI_LIST[981] = "UTL_ReadCfbmPassFailInfo";
	START_LAPTIMER(981);
	RadioButton retval = UTL_ReadCfbmPassFailInfo( arg1);
	STOP_LAPTIMER(981);
	return retval;
}
CfmConfigHandle _UTL_GetCfmConfigHandle()
{
	MCI_LIST[982] = "UTL_GetCfmConfigHandle";
	START_LAPTIMER(982);
	CfmConfigHandle retval = UTL_GetCfmConfigHandle();
	STOP_LAPTIMER(982);
	return retval;
}
void _UTL_SetCfmConfigBitSize( CfmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[983] = "UTL_SetCfmConfigBitSize";
	START_LAPTIMER(983);
	UTL_SetCfmConfigBitSize( arg1, arg2);
	STOP_LAPTIMER(983);
}
void _UTL_SetCfmConfigDutBitSize( CfmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[984] = "UTL_SetCfmConfigDutBitSize";
	START_LAPTIMER(984);
	UTL_SetCfmConfigDutBitSize( arg1, arg2);
	STOP_LAPTIMER(984);
}
void _UTL_SetCfmConfigAddrAssign( CfmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[985] = "UTL_SetCfmConfigAddrAssign";
	START_LAPTIMER(985);
	UTL_SetCfmConfigAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(985);
}
void _UTL_SetCfmConfigAddrAssignByAlpg( CfmConfigHandle arg1, RadioButton arg2, RadioButton arg3, RadioButton arg4)
{
	MCI_LIST[986] = "UTL_SetCfmConfigAddrAssignByAlpg";
	START_LAPTIMER(986);
	UTL_SetCfmConfigAddrAssignByAlpg( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(986);
}
void _UTL_AddCfmConfigPinAssign( CfmConfigHandle arg1, RadioButton arg2, UT_PIN arg3)
{
	MCI_LIST[987] = "UTL_AddCfmConfigPinAssign";
	START_LAPTIMER(987);
	UTL_AddCfmConfigPinAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(987);
}
void _UTL_ClearCfmConfigPinAssign( CfmConfigHandle arg1)
{
	MCI_LIST[988] = "UTL_ClearCfmConfigPinAssign";
	START_LAPTIMER(988);
	UTL_ClearCfmConfigPinAssign( arg1);
	STOP_LAPTIMER(988);
}
void _UTL_SetCfmConfigStoreSignalByMMType( CfmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[989] = "UTL_SetCfmConfigStoreSignalByMMType";
	START_LAPTIMER(989);
	UTL_SetCfmConfigStoreSignalByMMType( arg1, arg2, arg3);
	STOP_LAPTIMER(989);
}
void _UTL_AddCfmConfigAction( CfmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[990] = "UTL_AddCfmConfigAction";
	START_LAPTIMER(990);
	UTL_AddCfmConfigAction( arg1, arg2, arg3);
	STOP_LAPTIMER(990);
}
void _UTL_ClearCfmConfigAction( CfmConfigHandle arg1)
{
	MCI_LIST[991] = "UTL_ClearCfmConfigAction";
	START_LAPTIMER(991);
	UTL_ClearCfmConfigAction( arg1);
	STOP_LAPTIMER(991);
}
void _UTL_SetCfmConfigSpareInhMode( CfmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[992] = "UTL_SetCfmConfigSpareInhMode";
	START_LAPTIMER(992);
	UTL_SetCfmConfigSpareInhMode( arg1, arg2);
	STOP_LAPTIMER(992);
}
void _UTL_SetCfmConfigBbmLinkMode( CfmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[993] = "UTL_SetCfmConfigBbmLinkMode";
	START_LAPTIMER(993);
	UTL_SetCfmConfigBbmLinkMode( arg1, arg2);
	STOP_LAPTIMER(993);
}
void _UTL_SendCfmConfig( CfmConfigHandle arg1)
{
	MCI_LIST[994] = "UTL_SendCfmConfig";
	START_LAPTIMER(994);
	UTL_SendCfmConfig( arg1);
	STOP_LAPTIMER(994);
}
CfmAccessHandle _UTL_GetCfmAccessHandle()
{
	MCI_LIST[995] = "UTL_GetCfmAccessHandle";
	START_LAPTIMER(995);
	CfmAccessHandle retval = UTL_GetCfmAccessHandle();
	STOP_LAPTIMER(995);
	return retval;
}
void _UTL_SetCfmAccessAlpgUnit( CfmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[996] = "UTL_SetCfmAccessAlpgUnit";
	START_LAPTIMER(996);
	UTL_SetCfmAccessAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(996);
}
void _UTL_SetCfmAccessActionNumber( CfmAccessHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[997] = "UTL_SetCfmAccessActionNumber";
	START_LAPTIMER(997);
	UTL_SetCfmAccessActionNumber( arg1, arg2, arg3);
	STOP_LAPTIMER(997);
}
void _UTL_SetCfmAccessBitMode( CfmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[998] = "UTL_SetCfmAccessBitMode";
	START_LAPTIMER(998);
	UTL_SetCfmAccessBitMode( arg1, arg2);
	STOP_LAPTIMER(998);
}
void _UTL_SetCfmAccessAllBit( CfmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[999] = "UTL_SetCfmAccessAllBit";
	START_LAPTIMER(999);
	UTL_SetCfmAccessAllBit( arg1, arg2);
	STOP_LAPTIMER(999);
}
void _UTL_AddCfmAccessBit( CfmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1000] = "UTL_AddCfmAccessBit";
	START_LAPTIMER(1000);
	UTL_AddCfmAccessBit( arg1, arg2);
	STOP_LAPTIMER(1000);
}
void _UTL_ClearCfmAccessBit( CfmAccessHandle arg1)
{
	MCI_LIST[1001] = "UTL_ClearCfmAccessBit";
	START_LAPTIMER(1001);
	UTL_ClearCfmAccessBit( arg1);
	STOP_LAPTIMER(1001);
}
void _UTL_SetCfmAccessBitBlock( CfmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1002] = "UTL_SetCfmAccessBitBlock";
	START_LAPTIMER(1002);
	UTL_SetCfmAccessBitBlock( arg1, arg2);
	STOP_LAPTIMER(1002);
}
void _UTL_SetCfmAccessPresetAllMemory( CfmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[1003] = "UTL_SetCfmAccessPresetAllMemory";
	START_LAPTIMER(1003);
	UTL_SetCfmAccessPresetAllMemory( arg1, arg2);
	STOP_LAPTIMER(1003);
}
void _UTL_SetCfmAccessAddrAssign( CfmAccessHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1004] = "UTL_SetCfmAccessAddrAssign";
	START_LAPTIMER(1004);
	UTL_SetCfmAccessAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(1004);
}
void _UTL_SetCfmAccessApLink( CfmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1005] = "UTL_SetCfmAccessApLink";
	START_LAPTIMER(1005);
	UTL_SetCfmAccessApLink( arg1, arg2);
	STOP_LAPTIMER(1005);
}
void _UTL_SetCfmAccessXAddr( CfmAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1006] = "UTL_SetCfmAccessXAddr";
	START_LAPTIMER(1006);
	UTL_SetCfmAccessXAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1006);
}
void _UTL_SetCfmAccessYAddr( CfmAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1007] = "UTL_SetCfmAccessYAddr";
	START_LAPTIMER(1007);
	UTL_SetCfmAccessYAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1007);
}
void _UTL_SetCfmAccessZAddr( CfmAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1008] = "UTL_SetCfmAccessZAddr";
	START_LAPTIMER(1008);
	UTL_SetCfmAccessZAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1008);
}
void _UTL_SetCfmAccessAllDut( CfmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[1009] = "UTL_SetCfmAccessAllDut";
	START_LAPTIMER(1009);
	UTL_SetCfmAccessAllDut( arg1, arg2);
	STOP_LAPTIMER(1009);
}
void _UTL_SetCfmAccessDut( CfmAccessHandle arg1, UT_DUT arg2)
{
	MCI_LIST[1010] = "UTL_SetCfmAccessDut";
	START_LAPTIMER(1010);
	UTL_SetCfmAccessDut( arg1, arg2);
	STOP_LAPTIMER(1010);
}
void _UTL_PresetCfm( CfmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1011] = "UTL_PresetCfm";
	START_LAPTIMER(1011);
	UTL_PresetCfm( arg1, arg2);
	STOP_LAPTIMER(1011);
}
void _UTL_ReadCfm( CfmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[1012] = "UTL_ReadCfm";
	START_LAPTIMER(1012);
	UTL_ReadCfm( arg1, arg2, arg3);
	STOP_LAPTIMER(1012);
}
void _UTL_CntCfmFailAddr( CfmAccessHandle arg1)
{
	MCI_LIST[1013] = "UTL_CntCfmFailAddr";
	START_LAPTIMER(1013);
	UTL_CntCfmFailAddr( arg1);
	STOP_LAPTIMER(1013);
}
USlider _UTL_GetCfmFailAddrCnt( RadioButton arg1)
{
	MCI_LIST[1014] = "UTL_GetCfmFailAddrCnt";
	START_LAPTIMER(1014);
	USlider retval = UTL_GetCfmFailAddrCnt( arg1);
	STOP_LAPTIMER(1014);
	return retval;
}
CheckButton _UTL_GetCfmFailAddrCntOverflow( RadioButton arg1)
{
	MCI_LIST[1015] = "UTL_GetCfmFailAddrCntOverflow";
	START_LAPTIMER(1015);
	CheckButton retval = UTL_GetCfmFailAddrCntOverflow( arg1);
	STOP_LAPTIMER(1015);
	return retval;
}
FasmAccessHandle _UTL_GetFasmAccessHandle()
{
	MCI_LIST[1016] = "UTL_GetFasmAccessHandle";
	START_LAPTIMER(1016);
	FasmAccessHandle retval = UTL_GetFasmAccessHandle();
	STOP_LAPTIMER(1016);
	return retval;
}
void _UTL_SetFasmAccessStartAddr( FasmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1017] = "UTL_SetFasmAccessStartAddr";
	START_LAPTIMER(1017);
	UTL_SetFasmAccessStartAddr( arg1, arg2);
	STOP_LAPTIMER(1017);
}
void _UTL_SetFasmAccessStopAddr( FasmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1018] = "UTL_SetFasmAccessStopAddr";
	START_LAPTIMER(1018);
	UTL_SetFasmAccessStopAddr( arg1, arg2);
	STOP_LAPTIMER(1018);
}
void _UTL_SetFasmAccessBitBlock( FasmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1019] = "UTL_SetFasmAccessBitBlock";
	START_LAPTIMER(1019);
	UTL_SetFasmAccessBitBlock( arg1, arg2);
	STOP_LAPTIMER(1019);
}
USlider _UTL_ReadFasmStoreCnt( FasmAccessHandle arg1)
{
	MCI_LIST[1020] = "UTL_ReadFasmStoreCnt";
	START_LAPTIMER(1020);
	USlider retval = UTL_ReadFasmStoreCnt( arg1);
	STOP_LAPTIMER(1020);
	return retval;
}
CheckButton _UTL_ReadFasmStoreLimitOver( FasmAccessHandle arg1)
{
	MCI_LIST[1021] = "UTL_ReadFasmStoreLimitOver";
	START_LAPTIMER(1021);
	CheckButton retval = UTL_ReadFasmStoreLimitOver( arg1);
	STOP_LAPTIMER(1021);
	return retval;
}
void _UTL_ReadFasm( FasmAccessHandle arg1, void * arg2, void * arg3, void * arg4, void * arg5, USlider arg6, USlider arg7)
{
	MCI_LIST[1022] = "UTL_ReadFasm";
	START_LAPTIMER(1022);
	UTL_ReadFasm( arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	STOP_LAPTIMER(1022);
}
void _UTL_WriteFasm( FasmAccessHandle arg1, void * arg2, void * arg3, void * arg4, void * arg5, USlider arg6, USlider arg7)
{
	MCI_LIST[1023] = "UTL_WriteFasm";
	START_LAPTIMER(1023);
	UTL_WriteFasm( arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	STOP_LAPTIMER(1023);
}
void _UTL_ReadFasmRawData( FasmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[1024] = "UTL_ReadFasmRawData";
	START_LAPTIMER(1024);
	UTL_ReadFasmRawData( arg1, arg2, arg3);
	STOP_LAPTIMER(1024);
}
FailFilterConfigHandle _UTL_GetFailFilterConfigHandle()
{
	MCI_LIST[1025] = "UTL_GetFailFilterConfigHandle";
	START_LAPTIMER(1025);
	FailFilterConfigHandle retval = UTL_GetFailFilterConfigHandle();
	STOP_LAPTIMER(1025);
	return retval;
}
void _UTL_SetFailFilterConfigAction( FailFilterConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1026] = "UTL_SetFailFilterConfigAction";
	START_LAPTIMER(1026);
	UTL_SetFailFilterConfigAction( arg1, arg2);
	STOP_LAPTIMER(1026);
}
void _UTL_SetFailFilterConfigDutBitSize( FailFilterConfigHandle arg1, USlider arg2)
{
	MCI_LIST[1027] = "UTL_SetFailFilterConfigDutBitSize";
	START_LAPTIMER(1027);
	UTL_SetFailFilterConfigDutBitSize( arg1, arg2);
	STOP_LAPTIMER(1027);
}
void _UTL_SetFailFilterConfigBitSize( FailFilterConfigHandle arg1, USlider arg2)
{
	MCI_LIST[1028] = "UTL_SetFailFilterConfigBitSize";
	START_LAPTIMER(1028);
	UTL_SetFailFilterConfigBitSize( arg1, arg2);
	STOP_LAPTIMER(1028);
}
void _UTL_SetFailFilterConfigPinList( FailFilterConfigHandle arg1, USlider arg2, char * arg3, CheckButton arg4, USlider arg5)
{
	MCI_LIST[1029] = "UTL_SetFailFilterConfigPinList";
	START_LAPTIMER(1029);
	UTL_SetFailFilterConfigPinList( arg1, arg2, arg3, arg4, arg5);
	STOP_LAPTIMER(1029);
}
void _UTL_SetFailFilterConfigNibbleMode( FailFilterConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1030] = "UTL_SetFailFilterConfigNibbleMode";
	START_LAPTIMER(1030);
	UTL_SetFailFilterConfigNibbleMode( arg1, arg2);
	STOP_LAPTIMER(1030);
}
void _UTL_SetFailFilterConfigBlockSize( FailFilterConfigHandle arg1, USlider arg2)
{
	MCI_LIST[1031] = "UTL_SetFailFilterConfigBlockSize";
	START_LAPTIMER(1031);
	UTL_SetFailFilterConfigBlockSize( arg1, arg2);
	STOP_LAPTIMER(1031);
}
void _UTL_SetFailFilterConfigStatusBytes( FailFilterConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1032] = "UTL_SetFailFilterConfigStatusBytes";
	START_LAPTIMER(1032);
	UTL_SetFailFilterConfigStatusBytes( arg1, arg2);
	STOP_LAPTIMER(1032);
}
void _UTL_SetFailFilterConfigPageSize( FailFilterConfigHandle arg1, USlider arg2)
{
	MCI_LIST[1033] = "UTL_SetFailFilterConfigPageSize";
	START_LAPTIMER(1033);
	UTL_SetFailFilterConfigPageSize( arg1, arg2);
	STOP_LAPTIMER(1033);
}
void _UTL_SetFailFilterConfigLowThreshold( FailFilterConfigHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[1034] = "UTL_SetFailFilterConfigLowThreshold";
	START_LAPTIMER(1034);
	UTL_SetFailFilterConfigLowThreshold( arg1, arg2, arg3);
	STOP_LAPTIMER(1034);
}
void _UTL_SetFailFilterConfigHighThreshold( FailFilterConfigHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[1035] = "UTL_SetFailFilterConfigHighThreshold";
	START_LAPTIMER(1035);
	UTL_SetFailFilterConfigHighThreshold( arg1, arg2, arg3);
	STOP_LAPTIMER(1035);
}
void _UTL_SetFailFilterConfigRepairRegionHighThreshold( FailFilterConfigHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[1036] = "UTL_SetFailFilterConfigRepairRegionHighThreshold";
	START_LAPTIMER(1036);
	UTL_SetFailFilterConfigRepairRegionHighThreshold( arg1, arg2, arg3);
	STOP_LAPTIMER(1036);
}
void _UTL_SetFailFilterConfigTFCHighThreshold( FailFilterConfigHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[1037] = "UTL_SetFailFilterConfigTFCHighThreshold";
	START_LAPTIMER(1037);
	UTL_SetFailFilterConfigTFCHighThreshold( arg1, arg2, arg3);
	STOP_LAPTIMER(1037);
}
void _UTL_SetFailFilterConfigECCSectors( FailFilterConfigHandle arg1, USlider arg2, USlider arg3, USlider arg4)
{
	MCI_LIST[1038] = "UTL_SetFailFilterConfigECCSectors";
	START_LAPTIMER(1038);
	UTL_SetFailFilterConfigECCSectors( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1038);
}
void _UTL_SetFailFilterConfigRepairRegion( FailFilterConfigHandle arg1, USlider arg2, USlider arg3, USlider arg4)
{
	MCI_LIST[1039] = "UTL_SetFailFilterConfigRepairRegion";
	START_LAPTIMER(1039);
	UTL_SetFailFilterConfigRepairRegion( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1039);
}
void _UTL_SetFailFilterConfigMode( FailFilterConfigHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[1040] = "UTL_SetFailFilterConfigMode";
	START_LAPTIMER(1040);
	UTL_SetFailFilterConfigMode( arg1, arg2, arg3);
	STOP_LAPTIMER(1040);
}
void _UTL_SetFailFilterConfigFailListCounterSelect( FailFilterConfigHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[1041] = "UTL_SetFailFilterConfigFailListCounterSelect";
	START_LAPTIMER(1041);
	UTL_SetFailFilterConfigFailListCounterSelect( arg1, arg2, arg3);
	STOP_LAPTIMER(1041);
}
void _UTL_SetFailFilterConfigTFCOverlayCount( FailFilterConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[1042] = "UTL_SetFailFilterConfigTFCOverlayCount";
	START_LAPTIMER(1042);
	UTL_SetFailFilterConfigTFCOverlayCount( arg1, arg2);
	STOP_LAPTIMER(1042);
}
void _UTL_SetFailFilterConfigOverlaySignal( FailFilterConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1043] = "UTL_SetFailFilterConfigOverlaySignal";
	START_LAPTIMER(1043);
	UTL_SetFailFilterConfigOverlaySignal( arg1, arg2, arg3);
	STOP_LAPTIMER(1043);
}
void _UTL_SetFailFilterConfigAddrAssign( FailFilterConfigHandle arg1, RadioButton arg2, RadioButton arg3, RadioButton arg4)
{
	MCI_LIST[1044] = "UTL_SetFailFilterConfigAddrAssign";
	START_LAPTIMER(1044);
	UTL_SetFailFilterConfigAddrAssign( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1044);
}
void _UTL_SetFailFilterConfigColumnStartAddressBit( FailFilterConfigHandle arg1, USlider* arg2, USlider arg3)
{
	MCI_LIST[1045] = "UTL_SetFailFilterConfigColumnStartAddressBit";
	START_LAPTIMER(1045);
	UTL_SetFailFilterConfigColumnStartAddressBit( arg1, arg2, arg3);
	STOP_LAPTIMER(1045);
}
void _UTL_SetFailFilterConfigColumnAddress( FailFilterConfigHandle arg1, USlider* arg2, USlider arg3)
{
	MCI_LIST[1046] = "UTL_SetFailFilterConfigColumnAddress";
	START_LAPTIMER(1046);
	UTL_SetFailFilterConfigColumnAddress( arg1, arg2, arg3);
	STOP_LAPTIMER(1046);
}
void _UTL_SetFailFilterConfigDdrMode( FailFilterConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[1047] = "UTL_SetFailFilterConfigDdrMode";
	START_LAPTIMER(1047);
	UTL_SetFailFilterConfigDdrMode( arg1, arg2);
	STOP_LAPTIMER(1047);
}
void _UTL_SetFailFilterConfigBypassSignal( FailFilterConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1048] = "UTL_SetFailFilterConfigBypassSignal";
	START_LAPTIMER(1048);
	UTL_SetFailFilterConfigBypassSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(1048);
}
void _UTL_SetFailFilterConfigFlashCounterTransferSignal( FailFilterConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1049] = "UTL_SetFailFilterConfigFlashCounterTransferSignal";
	START_LAPTIMER(1049);
	UTL_SetFailFilterConfigFlashCounterTransferSignal( arg1, arg2);
	STOP_LAPTIMER(1049);
}
void _UTL_SendFailFilterConfig( FailFilterConfigHandle arg1)
{
	MCI_LIST[1050] = "UTL_SendFailFilterConfig";
	START_LAPTIMER(1050);
	UTL_SendFailFilterConfig( arg1);
	STOP_LAPTIMER(1050);
}
FailListAccessHandle _UTL_GetFailListAccessHandle()
{
	MCI_LIST[1051] = "UTL_GetFailListAccessHandle";
	START_LAPTIMER(1051);
	FailListAccessHandle retval = UTL_GetFailListAccessHandle();
	STOP_LAPTIMER(1051);
	return retval;
}
void _UTL_SetFailListAccessTestSelect( FailListAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1052] = "UTL_SetFailListAccessTestSelect";
	START_LAPTIMER(1052);
	UTL_SetFailListAccessTestSelect( arg1, arg2);
	STOP_LAPTIMER(1052);
}
void _UTL_AddFailListAccessTestName( FailListAccessHandle arg1, char * arg2)
{
	MCI_LIST[1053] = "UTL_AddFailListAccessTestName";
	START_LAPTIMER(1053);
	UTL_AddFailListAccessTestName( arg1, arg2);
	STOP_LAPTIMER(1053);
}
void _UTL_ClearFailListAccessTestName( FailListAccessHandle arg1)
{
	MCI_LIST[1054] = "UTL_ClearFailListAccessTestName";
	START_LAPTIMER(1054);
	UTL_ClearFailListAccessTestName( arg1);
	STOP_LAPTIMER(1054);
}
void _UTL_SetFailListAccessAllDut( FailListAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[1055] = "UTL_SetFailListAccessAllDut";
	START_LAPTIMER(1055);
	UTL_SetFailListAccessAllDut( arg1, arg2);
	STOP_LAPTIMER(1055);
}
void _UTL_SetFailListAccessDut( FailListAccessHandle arg1, UT_DUT arg2)
{
	MCI_LIST[1056] = "UTL_SetFailListAccessDut";
	START_LAPTIMER(1056);
	UTL_SetFailListAccessDut( arg1, arg2);
	STOP_LAPTIMER(1056);
}
void _UTL_SetFailListAccessDeviceChannel( FailListAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1057] = "UTL_SetFailListAccessDeviceChannel";
	START_LAPTIMER(1057);
	UTL_SetFailListAccessDeviceChannel( arg1, arg2);
	STOP_LAPTIMER(1057);
}
void _UTL_SetFailListAccessAllBit( FailListAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[1058] = "UTL_SetFailListAccessAllBit";
	START_LAPTIMER(1058);
	UTL_SetFailListAccessAllBit( arg1, arg2);
	STOP_LAPTIMER(1058);
}
void _UTL_AddFailListAccessBit( FailListAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1059] = "UTL_AddFailListAccessBit";
	START_LAPTIMER(1059);
	UTL_AddFailListAccessBit( arg1, arg2);
	STOP_LAPTIMER(1059);
}
void _UTL_ClearFailListAccessBit( FailListAccessHandle arg1)
{
	MCI_LIST[1060] = "UTL_ClearFailListAccessBit";
	START_LAPTIMER(1060);
	UTL_ClearFailListAccessBit( arg1);
	STOP_LAPTIMER(1060);
}
void _UTL_SetFailListAccessCountType( FailListAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1061] = "UTL_SetFailListAccessCountType";
	START_LAPTIMER(1061);
	UTL_SetFailListAccessCountType( arg1, arg2);
	STOP_LAPTIMER(1061);
}
void _UTL_SetFailListAccessApLink( FailListAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1062] = "UTL_SetFailListAccessApLink";
	START_LAPTIMER(1062);
	UTL_SetFailListAccessApLink( arg1, arg2);
	STOP_LAPTIMER(1062);
}
void _UTL_SetFailListAccessXAddr( FailListAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1063] = "UTL_SetFailListAccessXAddr";
	START_LAPTIMER(1063);
	UTL_SetFailListAccessXAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1063);
}
void _UTL_SetFailListAccessYAddr( FailListAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1064] = "UTL_SetFailListAccessYAddr";
	START_LAPTIMER(1064);
	UTL_SetFailListAccessYAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1064);
}
USlider _UTL_ReadFailListBadBlockCount( FailListAccessHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1065] = "UTL_ReadFailListBadBlockCount";
	START_LAPTIMER(1065);
	USlider retval = UTL_ReadFailListBadBlockCount( arg1, arg2);
	STOP_LAPTIMER(1065);
	return retval;
}
void _UTL_ReadFailListBadBlock( FailListAccessHandle  arg1, USlider * arg2, RadioButton * arg3, USlider  arg4)
{
	MCI_LIST[1066] = "UTL_ReadFailListBadBlock";
	START_LAPTIMER(1066);
	UTL_ReadFailListBadBlock( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1066);
}
void _UTL_WriteFailListBadBlock( FailListAccessHandle  arg1, USlider * arg2, RadioButton * arg3, USlider  arg4)
{
	MCI_LIST[1067] = "UTL_WriteFailListBadBlock";
	START_LAPTIMER(1067);
	UTL_WriteFailListBadBlock( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1067);
}
USlider _UTL_ReadFailListAddressCount( FailListAccessHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1068] = "UTL_ReadFailListAddressCount";
	START_LAPTIMER(1068);
	USlider retval = UTL_ReadFailListAddressCount( arg1, arg2);
	STOP_LAPTIMER(1068);
	return retval;
}
void _UTL_ReadFailList( FailListAccessHandle  arg1, USlider * arg2, USlider * arg3, USlider * arg4, USlider * arg5, USlider  arg6)
{
	MCI_LIST[1069] = "UTL_ReadFailList";
	START_LAPTIMER(1069);
	UTL_ReadFailList( arg1, arg2, arg3, arg4, arg5, arg6);
	STOP_LAPTIMER(1069);
}
void _UTL_ReadFailListBitMap( FailListAccessHandle  arg1, unsigned char * arg2, USlider  arg3)
{
	MCI_LIST[1070] = "UTL_ReadFailListBitMap";
	START_LAPTIMER(1070);
	UTL_ReadFailListBitMap( arg1, arg2, arg3);
	STOP_LAPTIMER(1070);
}
void _UTL_ReadFailListStatusBytes( FailListAccessHandle  arg1, USlider * arg2, USlider * arg3, USlider * arg4, USlider  arg5)
{
	MCI_LIST[1071] = "UTL_ReadFailListStatusBytes";
	START_LAPTIMER(1071);
	UTL_ReadFailListStatusBytes( arg1, arg2, arg3, arg4, arg5);
	STOP_LAPTIMER(1071);
}
USlider _UTL_ReadFailListFlashCounter( FailListAccessHandle  arg1)
{
	MCI_LIST[1072] = "UTL_ReadFailListFlashCounter";
	START_LAPTIMER(1072);
	USlider retval = UTL_ReadFailListFlashCounter( arg1);
	STOP_LAPTIMER(1072);
	return retval;
}
void _UTL_ReadFailListTfcCount( FailListAccessHandle  arg1, USlider * arg2, RadioButton * arg3)
{
	MCI_LIST[1073] = "UTL_ReadFailListTfcCount";
	START_LAPTIMER(1073);
	UTL_ReadFailListTfcCount( arg1, arg2, arg3);
	STOP_LAPTIMER(1073);
}
void _UTL_ReadFailListEccCount( FailListAccessHandle  arg1, USlider * arg2, RadioButton * arg3, USlider  arg4)
{
	MCI_LIST[1074] = "UTL_ReadFailListEccCount";
	START_LAPTIMER(1074);
	UTL_ReadFailListEccCount( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1074);
}
void _UTL_ReadFailListRrCount( FailListAccessHandle  arg1, USlider * arg2, RadioButton * arg3, USlider  arg4)
{
	MCI_LIST[1075] = "UTL_ReadFailListRrCount";
	START_LAPTIMER(1075);
	UTL_ReadFailListRrCount( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1075);
}
void _UTL_SetFailListAccessRecordType( FailListAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1076] = "UTL_SetFailListAccessRecordType";
	START_LAPTIMER(1076);
	UTL_SetFailListAccessRecordType( arg1, arg2);
	STOP_LAPTIMER(1076);
}
void _UTL_ReadFailListRecordCount( FailListAccessHandle  arg1, USlider * arg2, USlider * arg3)
{
	MCI_LIST[1077] = "UTL_ReadFailListRecordCount";
	START_LAPTIMER(1077);
	UTL_ReadFailListRecordCount( arg1, arg2, arg3);
	STOP_LAPTIMER(1077);
}
void _UTL_ReadFailListFlashCounters( FailListAccessHandle  arg1, USlider * arg2, USlider * arg3, USlider * arg4, USlider  arg5)
{
	MCI_LIST[1078] = "UTL_ReadFailListFlashCounters";
	START_LAPTIMER(1078);
	UTL_ReadFailListFlashCounters( arg1, arg2, arg3, arg4, arg5);
	STOP_LAPTIMER(1078);
}
void _UTL_OverlayFailList( FailListAccessHandle  arg1, CheckButton  arg2)
{
	MCI_LIST[1079] = "UTL_OverlayFailList";
	START_LAPTIMER(1079);
	UTL_OverlayFailList( arg1, arg2);
	STOP_LAPTIMER(1079);
}
void _UTL_ResetFailList( FailListAccessHandle  arg1, CheckButton  arg2, CheckButton  arg3)
{
	MCI_LIST[1080] = "UTL_ResetFailList";
	START_LAPTIMER(1080);
	UTL_ResetFailList( arg1, arg2, arg3);
	STOP_LAPTIMER(1080);
}
void _UTL_DeleteFailList( FailListAccessHandle  arg1)
{
	MCI_LIST[1081] = "UTL_DeleteFailList";
	START_LAPTIMER(1081);
	UTL_DeleteFailList( arg1);
	STOP_LAPTIMER(1081);
}
void _UTL_WriteMultiPlaneStatusJudgeTable( USlider * arg1, USlider arg2)
{
	MCI_LIST[1082] = "UTL_WriteMultiPlaneStatusJudgeTable";
	START_LAPTIMER(1082);
	UTL_WriteMultiPlaneStatusJudgeTable( arg1, arg2);
	STOP_LAPTIMER(1082);
}
FailSelPinHandle _UTL_GetFailSelPinHandle()
{
	MCI_LIST[1083] = "UTL_GetFailSelPinHandle";
	START_LAPTIMER(1083);
	FailSelPinHandle retval = UTL_GetFailSelPinHandle();
	STOP_LAPTIMER(1083);
	return retval;
}
void _UTL_SetFailSelPinTarget( FailSelPinHandle arg1, RadioButton arg2)
{
	MCI_LIST[1084] = "UTL_SetFailSelPinTarget";
	START_LAPTIMER(1084);
	UTL_SetFailSelPinTarget( arg1, arg2);
	STOP_LAPTIMER(1084);
}
void _UTL_AddFailSelPinAssign( FailSelPinHandle arg1, RadioButton arg2, UT_PIN arg3)
{
	MCI_LIST[1085] = "UTL_AddFailSelPinAssign";
	START_LAPTIMER(1085);
	UTL_AddFailSelPinAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(1085);
}
void _UTL_ClearFailSelPinAssign( FailSelPinHandle arg1)
{
	MCI_LIST[1086] = "UTL_ClearFailSelPinAssign";
	START_LAPTIMER(1086);
	UTL_ClearFailSelPinAssign( arg1);
	STOP_LAPTIMER(1086);
}
void _UTL_SetFailSelPin( FailSelPinHandle arg1, UT_PIN arg2, CheckButton arg3)
{
	MCI_LIST[1087] = "UTL_SetFailSelPin";
	START_LAPTIMER(1087);
	UTL_SetFailSelPin( arg1, arg2, arg3);
	STOP_LAPTIMER(1087);
}
void _UTL_SendFailSelPin( FailSelPinHandle arg1)
{
	MCI_LIST[1088] = "UTL_SendFailSelPin";
	START_LAPTIMER(1088);
	UTL_SendFailSelPin( arg1);
	STOP_LAPTIMER(1088);
}
EccConfigHandle _UTL_GetEccConfigHandle()
{
	MCI_LIST[1089] = "UTL_GetEccConfigHandle";
	START_LAPTIMER(1089);
	EccConfigHandle retval = UTL_GetEccConfigHandle();
	STOP_LAPTIMER(1089);
	return retval;
}
void _UTL_SetEccConfigCounterNoClear( EccConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[1090] = "UTL_SetEccConfigCounterNoClear";
	START_LAPTIMER(1090);
	UTL_SetEccConfigCounterNoClear( arg1, arg2);
	STOP_LAPTIMER(1090);
}
void _UTL_SetEccConfigCounterLimit( EccConfigHandle arg1, RadioButton arg2, RadioButton arg3, USlider arg4)
{
	MCI_LIST[1091] = "UTL_SetEccConfigCounterLimit";
	START_LAPTIMER(1091);
	UTL_SetEccConfigCounterLimit( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1091);
}
void _UTL_SetEccConfigCounterEnableSignal( EccConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1092] = "UTL_SetEccConfigCounterEnableSignal";
	START_LAPTIMER(1092);
	UTL_SetEccConfigCounterEnableSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(1092);
}
void _UTL_SetEccConfigJudgeSignal( EccConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1093] = "UTL_SetEccConfigJudgeSignal";
	START_LAPTIMER(1093);
	UTL_SetEccConfigJudgeSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(1093);
}
void _UTL_SetEccConfigCounterClearSignal( EccConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1094] = "UTL_SetEccConfigCounterClearSignal";
	START_LAPTIMER(1094);
	UTL_SetEccConfigCounterClearSignal( arg1, arg2);
	STOP_LAPTIMER(1094);
}
void _UTL_SetEccConfigSectorCount( EccConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1095] = "UTL_SetEccConfigSectorCount";
	START_LAPTIMER(1095);
	UTL_SetEccConfigSectorCount( arg1, arg2);
	STOP_LAPTIMER(1095);
}
void _UTL_SetEccConfigSectorSwitchSignal( EccConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1096] = "UTL_SetEccConfigSectorSwitchSignal";
	START_LAPTIMER(1096);
	UTL_SetEccConfigSectorSwitchSignal( arg1, arg2);
	STOP_LAPTIMER(1096);
}
void _UTL_SendEccConfig( EccConfigHandle arg1)
{
	MCI_LIST[1097] = "UTL_SendEccConfig";
	START_LAPTIMER(1097);
	UTL_SendEccConfig( arg1);
	STOP_LAPTIMER(1097);
}
TprogConfigHandle _UTL_GetTprogConfigHandle()
{
	MCI_LIST[1098] = "UTL_GetTprogConfigHandle";
	START_LAPTIMER(1098);
	TprogConfigHandle retval = UTL_GetTprogConfigHandle();
	STOP_LAPTIMER(1098);
	return retval;
}
void _UTL_SetTprogConfigAverageLimit( TprogConfigHandle arg1, USlider arg2)
{
	MCI_LIST[1099] = "UTL_SetTprogConfigAverageLimit";
	START_LAPTIMER(1099);
	UTL_SetTprogConfigAverageLimit( arg1, arg2);
	STOP_LAPTIMER(1099);
}
void _UTL_SetTprogConfigMaxLimit( TprogConfigHandle arg1, USlider arg2)
{
	MCI_LIST[1100] = "UTL_SetTprogConfigMaxLimit";
	START_LAPTIMER(1100);
	UTL_SetTprogConfigMaxLimit( arg1, arg2);
	STOP_LAPTIMER(1100);
}
void _UTL_SetTprogConfigCounterEnableSignal( TprogConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1101] = "UTL_SetTprogConfigCounterEnableSignal";
	START_LAPTIMER(1101);
	UTL_SetTprogConfigCounterEnableSignal( arg1, arg2);
	STOP_LAPTIMER(1101);
}
void _UTL_SetTprogConfigJudgeSignal( TprogConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1102] = "UTL_SetTprogConfigJudgeSignal";
	START_LAPTIMER(1102);
	UTL_SetTprogConfigJudgeSignal( arg1, arg2);
	STOP_LAPTIMER(1102);
}
void _UTL_SetTprogConfigCounterClearSignal( TprogConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1103] = "UTL_SetTprogConfigCounterClearSignal";
	START_LAPTIMER(1103);
	UTL_SetTprogConfigCounterClearSignal( arg1, arg2);
	STOP_LAPTIMER(1103);
}
void _UTL_SendTprogConfig( TprogConfigHandle arg1)
{
	MCI_LIST[1104] = "UTL_SendTprogConfig";
	START_LAPTIMER(1104);
	UTL_SendTprogConfig( arg1);
	STOP_LAPTIMER(1104);
}
AfmPatternInfoHandle _UTL_GetAfmPatternInfoHandle()
{
	MCI_LIST[1105] = "UTL_GetAfmPatternInfoHandle";
	START_LAPTIMER(1105);
	AfmPatternInfoHandle retval = UTL_GetAfmPatternInfoHandle();
	STOP_LAPTIMER(1105);
	return retval;
}
void _UTL_SetAfmPatternInfoMpatName( AfmPatternInfoHandle arg1, char * arg2)
{
	MCI_LIST[1106] = "UTL_SetAfmPatternInfoMpatName";
	START_LAPTIMER(1106);
	UTL_SetAfmPatternInfoMpatName( arg1, arg2);
	STOP_LAPTIMER(1106);
}
USlider _UTL_AddAfmPatternInfoModule( AfmPatternInfoHandle arg1)
{
	MCI_LIST[1107] = "UTL_AddAfmPatternInfoModule";
	START_LAPTIMER(1107);
	USlider retval = UTL_AddAfmPatternInfoModule( arg1);
	STOP_LAPTIMER(1107);
	return retval;
}
void _UTL_SetAfmPatternInfoStartPc( AfmPatternInfoHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1108] = "UTL_SetAfmPatternInfoStartPc";
	START_LAPTIMER(1108);
	UTL_SetAfmPatternInfoStartPc( arg1, arg2, arg3);
	STOP_LAPTIMER(1108);
}
void _UTL_SetAfmPatternInfoBitSize( AfmPatternInfoHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1109] = "UTL_SetAfmPatternInfoBitSize";
	START_LAPTIMER(1109);
	UTL_SetAfmPatternInfoBitSize( arg1, arg2, arg3);
	STOP_LAPTIMER(1109);
}
void _UTL_SetAfmPatternInfoAMinXAddr( AfmPatternInfoHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1110] = "UTL_SetAfmPatternInfoAMinXAddr";
	START_LAPTIMER(1110);
	UTL_SetAfmPatternInfoAMinXAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1110);
}
void _UTL_SetAfmPatternInfoAMinYAddr( AfmPatternInfoHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1111] = "UTL_SetAfmPatternInfoAMinYAddr";
	START_LAPTIMER(1111);
	UTL_SetAfmPatternInfoAMinYAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1111);
}
void _UTL_SetAfmPatternInfoAMinZAddr( AfmPatternInfoHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1112] = "UTL_SetAfmPatternInfoAMinZAddr";
	START_LAPTIMER(1112);
	UTL_SetAfmPatternInfoAMinZAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1112);
}
void _UTL_SetAfmPatternInfoAMaxXAddr( AfmPatternInfoHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1113] = "UTL_SetAfmPatternInfoAMaxXAddr";
	START_LAPTIMER(1113);
	UTL_SetAfmPatternInfoAMaxXAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1113);
}
void _UTL_SetAfmPatternInfoAMaxYAddr( AfmPatternInfoHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1114] = "UTL_SetAfmPatternInfoAMaxYAddr";
	START_LAPTIMER(1114);
	UTL_SetAfmPatternInfoAMaxYAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1114);
}
void _UTL_SetAfmPatternInfoAMaxZAddr( AfmPatternInfoHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1115] = "UTL_SetAfmPatternInfoAMaxZAddr";
	START_LAPTIMER(1115);
	UTL_SetAfmPatternInfoAMaxZAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1115);
}
void _UTL_ReadAfmPatternInfo( AfmPatternInfoHandle arg1)
{
	MCI_LIST[1116] = "UTL_ReadAfmPatternInfo";
	START_LAPTIMER(1116);
	UTL_ReadAfmPatternInfo( arg1);
	STOP_LAPTIMER(1116);
}
void _UTL_WriteAfmPatternInfo( AfmPatternInfoHandle arg1)
{
	MCI_LIST[1117] = "UTL_WriteAfmPatternInfo";
	START_LAPTIMER(1117);
	UTL_WriteAfmPatternInfo( arg1);
	STOP_LAPTIMER(1117);
}
AfmPatternAccessHandle _UTL_GetAfmPatternAccessHandle()
{
	MCI_LIST[1118] = "UTL_GetAfmPatternAccessHandle";
	START_LAPTIMER(1118);
	AfmPatternAccessHandle retval = UTL_GetAfmPatternAccessHandle();
	STOP_LAPTIMER(1118);
	return retval;
}
void _UTL_SetAfmPatternAccessAfmPatternInfo( AfmPatternAccessHandle arg1, AfmPatternInfoHandle arg2)
{
	MCI_LIST[1119] = "UTL_SetAfmPatternAccessAfmPatternInfo";
	START_LAPTIMER(1119);
	UTL_SetAfmPatternAccessAfmPatternInfo( arg1, arg2);
	STOP_LAPTIMER(1119);
}
void _UTL_SetAfmPatternAccessModuleIndex( AfmPatternAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1120] = "UTL_SetAfmPatternAccessModuleIndex";
	START_LAPTIMER(1120);
	UTL_SetAfmPatternAccessModuleIndex( arg1, arg2);
	STOP_LAPTIMER(1120);
}
void _UTL_SetAfmPatternAccessAreaIndex( AfmPatternAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1121] = "UTL_SetAfmPatternAccessAreaIndex";
	START_LAPTIMER(1121);
	UTL_SetAfmPatternAccessAreaIndex( arg1, arg2);
	STOP_LAPTIMER(1121);
}
void _UTL_SetAfmPatternAccessAreaReadMode( AfmPatternAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[1122] = "UTL_SetAfmPatternAccessAreaReadMode";
	START_LAPTIMER(1122);
	UTL_SetAfmPatternAccessAreaReadMode( arg1, arg2);
	STOP_LAPTIMER(1122);
}
void _UTL_SetAfmPatternAccessDataFormat( AfmPatternAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1123] = "UTL_SetAfmPatternAccessDataFormat";
	START_LAPTIMER(1123);
	UTL_SetAfmPatternAccessDataFormat( arg1, arg2);
	STOP_LAPTIMER(1123);
}
void _UTL_SetAfmPatternAccessBitBlockNum( AfmPatternAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1124] = "UTL_SetAfmPatternAccessBitBlockNum";
	START_LAPTIMER(1124);
	UTL_SetAfmPatternAccessBitBlockNum( arg1, arg2);
	STOP_LAPTIMER(1124);
}
void _UTL_SetAfmPatternAccessBitBlock( AfmPatternAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1125] = "UTL_SetAfmPatternAccessBitBlock";
	START_LAPTIMER(1125);
	UTL_SetAfmPatternAccessBitBlock( arg1, arg2);
	STOP_LAPTIMER(1125);
}
void _UTL_SetAfmPatternAccessXAddr( AfmPatternAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1126] = "UTL_SetAfmPatternAccessXAddr";
	START_LAPTIMER(1126);
	UTL_SetAfmPatternAccessXAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1126);
}
void _UTL_SetAfmPatternAccessYAddr( AfmPatternAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1127] = "UTL_SetAfmPatternAccessYAddr";
	START_LAPTIMER(1127);
	UTL_SetAfmPatternAccessYAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1127);
}
void _UTL_SetAfmPatternAccessZAddr( AfmPatternAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1128] = "UTL_SetAfmPatternAccessZAddr";
	START_LAPTIMER(1128);
	UTL_SetAfmPatternAccessZAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1128);
}
void _UTL_SetAfmPatternAccessAMaxXAddr( AfmPatternAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1129] = "UTL_SetAfmPatternAccessAMaxXAddr";
	START_LAPTIMER(1129);
	UTL_SetAfmPatternAccessAMaxXAddr( arg1, arg2);
	STOP_LAPTIMER(1129);
}
void _UTL_SetAfmPatternAccessAMaxYAddr( AfmPatternAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1130] = "UTL_SetAfmPatternAccessAMaxYAddr";
	START_LAPTIMER(1130);
	UTL_SetAfmPatternAccessAMaxYAddr( arg1, arg2);
	STOP_LAPTIMER(1130);
}
void _UTL_SetAfmPatternAccessAMaxZAddr( AfmPatternAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1131] = "UTL_SetAfmPatternAccessAMaxZAddr";
	START_LAPTIMER(1131);
	UTL_SetAfmPatternAccessAMaxZAddr( arg1, arg2);
	STOP_LAPTIMER(1131);
}
void _UTL_ReadAfmPattern( AfmPatternAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[1132] = "UTL_ReadAfmPattern";
	START_LAPTIMER(1132);
	UTL_ReadAfmPattern( arg1, arg2, arg3);
	STOP_LAPTIMER(1132);
}
void _UTL_WriteAfmPattern( AfmPatternAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[1133] = "UTL_WriteAfmPattern";
	START_LAPTIMER(1133);
	UTL_WriteAfmPattern( arg1, arg2, arg3);
	STOP_LAPTIMER(1133);
}
FcmMultiSideConfigHandle _UTL_GetFcmMultiSideConfigHandle()
{
	MCI_LIST[1134] = "UTL_GetFcmMultiSideConfigHandle";
	START_LAPTIMER(1134);
	FcmMultiSideConfigHandle retval = UTL_GetFcmMultiSideConfigHandle();
	STOP_LAPTIMER(1134);
	return retval;
}
void _UTL_SetFcmMultiSideConfigSideCount( FcmMultiSideConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1135] = "UTL_SetFcmMultiSideConfigSideCount";
	START_LAPTIMER(1135);
	UTL_SetFcmMultiSideConfigSideCount( arg1, arg2);
	STOP_LAPTIMER(1135);
}
void _UTL_SetFcmMultiSideConfigSideMode( FcmMultiSideConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1136] = "UTL_SetFcmMultiSideConfigSideMode";
	START_LAPTIMER(1136);
	UTL_SetFcmMultiSideConfigSideMode( arg1, arg2, arg3);
	STOP_LAPTIMER(1136);
}
void _UTL_SendFcmMultiSideConfig( FcmMultiSideConfigHandle arg1)
{
	MCI_LIST[1137] = "UTL_SendFcmMultiSideConfig";
	START_LAPTIMER(1137);
	UTL_SendFcmMultiSideConfig( arg1);
	STOP_LAPTIMER(1137);
}
PmConfigHandle _UTL_GetPmConfigHandle()
{
	MCI_LIST[1138] = "UTL_GetPmConfigHandle";
	START_LAPTIMER(1138);
	PmConfigHandle retval = UTL_GetPmConfigHandle();
	STOP_LAPTIMER(1138);
	return retval;
}
void _UTL_SetPmConfigBitSize( PmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[1139] = "UTL_SetPmConfigBitSize";
	START_LAPTIMER(1139);
	UTL_SetPmConfigBitSize( arg1, arg2);
	STOP_LAPTIMER(1139);
}
void _UTL_SetPmConfigAddrAssign( PmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1140] = "UTL_SetPmConfigAddrAssign";
	START_LAPTIMER(1140);
	UTL_SetPmConfigAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(1140);
}
void _UTL_SetPmConfigAction( PmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1141] = "UTL_SetPmConfigAction";
	START_LAPTIMER(1141);
	UTL_SetPmConfigAction( arg1, arg2);
	STOP_LAPTIMER(1141);
}
void _UTL_SetPmConfigFixData( PmConfigHandle arg1, RadioButton arg2, USlider arg3)
{
	MCI_LIST[1142] = "UTL_SetPmConfigFixData";
	START_LAPTIMER(1142);
	UTL_SetPmConfigFixData( arg1, arg2, arg3);
	STOP_LAPTIMER(1142);
}
void _UTL_SetPmConfigRate( PmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1143] = "UTL_SetPmConfigRate";
	START_LAPTIMER(1143);
	UTL_SetPmConfigRate( arg1, arg2);
	STOP_LAPTIMER(1143);
}
void _UTL_SendPmConfig( PmConfigHandle arg1)
{
	MCI_LIST[1144] = "UTL_SendPmConfig";
	START_LAPTIMER(1144);
	UTL_SendPmConfig( arg1);
	STOP_LAPTIMER(1144);
}
PmAccessHandle _UTL_GetPmAccessHandle()
{
	MCI_LIST[1145] = "UTL_GetPmAccessHandle";
	START_LAPTIMER(1145);
	PmAccessHandle retval = UTL_GetPmAccessHandle();
	STOP_LAPTIMER(1145);
	return retval;
}
void _UTL_SetPmAccessCompactionMode( PmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1146] = "UTL_SetPmAccessCompactionMode";
	START_LAPTIMER(1146);
	UTL_SetPmAccessCompactionMode( arg1, arg2);
	STOP_LAPTIMER(1146);
}
void _UTL_SetPmAccessBitMode( PmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1147] = "UTL_SetPmAccessBitMode";
	START_LAPTIMER(1147);
	UTL_SetPmAccessBitMode( arg1, arg2);
	STOP_LAPTIMER(1147);
}
void _UTL_SetPmAccessAllBit( PmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[1148] = "UTL_SetPmAccessAllBit";
	START_LAPTIMER(1148);
	UTL_SetPmAccessAllBit( arg1, arg2);
	STOP_LAPTIMER(1148);
}
void _UTL_AddPmAccessBit( PmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1149] = "UTL_AddPmAccessBit";
	START_LAPTIMER(1149);
	UTL_AddPmAccessBit( arg1, arg2);
	STOP_LAPTIMER(1149);
}
void _UTL_ClearPmAccessBit( PmAccessHandle arg1)
{
	MCI_LIST[1150] = "UTL_ClearPmAccessBit";
	START_LAPTIMER(1150);
	UTL_ClearPmAccessBit( arg1);
	STOP_LAPTIMER(1150);
}
void _UTL_SetPmAccessBitBlock( PmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1151] = "UTL_SetPmAccessBitBlock";
	START_LAPTIMER(1151);
	UTL_SetPmAccessBitBlock( arg1, arg2);
	STOP_LAPTIMER(1151);
}
void _UTL_SetPmAccessPresetAllMemory( PmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[1152] = "UTL_SetPmAccessPresetAllMemory";
	START_LAPTIMER(1152);
	UTL_SetPmAccessPresetAllMemory( arg1, arg2);
	STOP_LAPTIMER(1152);
}
void _UTL_SetPmAccessAddrAssign( PmAccessHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1153] = "UTL_SetPmAccessAddrAssign";
	START_LAPTIMER(1153);
	UTL_SetPmAccessAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(1153);
}
void _UTL_SetPmAccessApLink( PmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1154] = "UTL_SetPmAccessApLink";
	START_LAPTIMER(1154);
	UTL_SetPmAccessApLink( arg1, arg2);
	STOP_LAPTIMER(1154);
}
void _UTL_SetPmAccessStartAddr( PmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1155] = "UTL_SetPmAccessStartAddr";
	START_LAPTIMER(1155);
	UTL_SetPmAccessStartAddr( arg1, arg2);
	STOP_LAPTIMER(1155);
}
void _UTL_SetPmAccessStopAddr( PmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1156] = "UTL_SetPmAccessStopAddr";
	START_LAPTIMER(1156);
	UTL_SetPmAccessStopAddr( arg1, arg2);
	STOP_LAPTIMER(1156);
}
void _UTL_SetPmAccessXAddr( PmAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1157] = "UTL_SetPmAccessXAddr";
	START_LAPTIMER(1157);
	UTL_SetPmAccessXAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1157);
}
void _UTL_SetPmAccessYAddr( PmAccessHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[1158] = "UTL_SetPmAccessYAddr";
	START_LAPTIMER(1158);
	UTL_SetPmAccessYAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1158);
}
void _UTL_SetPmAccessAllDut( PmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[1159] = "UTL_SetPmAccessAllDut";
	START_LAPTIMER(1159);
	UTL_SetPmAccessAllDut( arg1, arg2);
	STOP_LAPTIMER(1159);
}
void _UTL_SetPmAccessDut( PmAccessHandle arg1, UT_DUT arg2)
{
	MCI_LIST[1160] = "UTL_SetPmAccessDut";
	START_LAPTIMER(1160);
	UTL_SetPmAccessDut( arg1, arg2);
	STOP_LAPTIMER(1160);
}
void _UTL_PresetPm( PmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1161] = "UTL_PresetPm";
	START_LAPTIMER(1161);
	UTL_PresetPm( arg1, arg2);
	STOP_LAPTIMER(1161);
}
void _UTL_ReadPm( PmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[1162] = "UTL_ReadPm";
	START_LAPTIMER(1162);
	UTL_ReadPm( arg1, arg2, arg3);
	STOP_LAPTIMER(1162);
}
void _UTL_WritePm( PmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[1163] = "UTL_WritePm";
	START_LAPTIMER(1163);
	UTL_WritePm( arg1, arg2, arg3);
	STOP_LAPTIMER(1163);
}
EbmConfigHandle _UTL_GetEbmConfigHandle()
{
	MCI_LIST[1164] = "UTL_GetEbmConfigHandle";
	START_LAPTIMER(1164);
	EbmConfigHandle retval = UTL_GetEbmConfigHandle();
	STOP_LAPTIMER(1164);
	return retval;
}
void _UTL_SetEbmConfigPatternSelect( EbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1165] = "UTL_SetEbmConfigPatternSelect";
	START_LAPTIMER(1165);
	UTL_SetEbmConfigPatternSelect( arg1, arg2);
	STOP_LAPTIMER(1165);
}
void _UTL_SetEbmConfigBitSize( EbmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[1166] = "UTL_SetEbmConfigBitSize";
	START_LAPTIMER(1166);
	UTL_SetEbmConfigBitSize( arg1, arg2);
	STOP_LAPTIMER(1166);
}
void _UTL_SetEbmConfigDdrMode( EbmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[1167] = "UTL_SetEbmConfigDdrMode";
	START_LAPTIMER(1167);
	UTL_SetEbmConfigDdrMode( arg1, arg2);
	STOP_LAPTIMER(1167);
}
void _UTL_SetEbmConfigTransferSignal( EbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1168] = "UTL_SetEbmConfigTransferSignal";
	START_LAPTIMER(1168);
	UTL_SetEbmConfigTransferSignal( arg1, arg2);
	STOP_LAPTIMER(1168);
}
void _UTL_SetEbmConfigTransferAreaSize( EbmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[1169] = "UTL_SetEbmConfigTransferAreaSize";
	START_LAPTIMER(1169);
	UTL_SetEbmConfigTransferAreaSize( arg1, arg2);
	STOP_LAPTIMER(1169);
}
void _UTL_SetEbmConfigTransferAreaCount( EbmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[1170] = "UTL_SetEbmConfigTransferAreaCount";
	START_LAPTIMER(1170);
	UTL_SetEbmConfigTransferAreaCount( arg1, arg2);
	STOP_LAPTIMER(1170);
}
void _UTL_SetEbmConfigTransferAreaRepeatCount( EbmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[1171] = "UTL_SetEbmConfigTransferAreaRepeatCount";
	START_LAPTIMER(1171);
	UTL_SetEbmConfigTransferAreaRepeatCount( arg1, arg2);
	STOP_LAPTIMER(1171);
}
void _UTL_SetEbmConfigSequenceTable( EbmConfigHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[1172] = "UTL_SetEbmConfigSequenceTable";
	START_LAPTIMER(1172);
	UTL_SetEbmConfigSequenceTable( arg1, arg2, arg3);
	STOP_LAPTIMER(1172);
}
void _UTL_SendEbmConfig( EbmConfigHandle arg1)
{
	MCI_LIST[1173] = "UTL_SendEbmConfig";
	START_LAPTIMER(1173);
	UTL_SendEbmConfig( arg1);
	STOP_LAPTIMER(1173);
}
EbmAccessHandle _UTL_GetEbmAccessHandle()
{
	MCI_LIST[1174] = "UTL_GetEbmAccessHandle";
	START_LAPTIMER(1174);
	EbmAccessHandle retval = UTL_GetEbmAccessHandle();
	STOP_LAPTIMER(1174);
	return retval;
}
void _UTL_SetEbmAccessStartIndex( EbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1175] = "UTL_SetEbmAccessStartIndex";
	START_LAPTIMER(1175);
	UTL_SetEbmAccessStartIndex( arg1, arg2);
	STOP_LAPTIMER(1175);
}
void _UTL_WriteEbm( EbmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[1176] = "UTL_WriteEbm";
	START_LAPTIMER(1176);
	UTL_WriteEbm( arg1, arg2, arg3);
	STOP_LAPTIMER(1176);
}
void _UTL_WriteEbmFromFile( EbmAccessHandle arg1, char * arg2)
{
	MCI_LIST[1177] = "UTL_WriteEbmFromFile";
	START_LAPTIMER(1177);
	UTL_WriteEbmFromFile( arg1, arg2);
	STOP_LAPTIMER(1177);
}
DfmConfigHandle _UTL_GetDfmConfigHandle()
{
	MCI_LIST[1178] = "UTL_GetDfmConfigHandle";
	START_LAPTIMER(1178);
	DfmConfigHandle retval = UTL_GetDfmConfigHandle();
	STOP_LAPTIMER(1178);
	return retval;
}
void _UTL_SetDfmConfigStoreCycle( DfmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1179] = "UTL_SetDfmConfigStoreCycle";
	START_LAPTIMER(1179);
	UTL_SetDfmConfigStoreCycle( arg1, arg2);
	STOP_LAPTIMER(1179);
}
void _UTL_SetDfmConfigCountMode( DfmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1180] = "UTL_SetDfmConfigCountMode";
	START_LAPTIMER(1180);
	UTL_SetDfmConfigCountMode( arg1, arg2);
	STOP_LAPTIMER(1180);
}
void _UTL_SetDfmConfigCountValue( DfmConfigHandle arg1, USlider arg2, RadioButton arg3)
{
	MCI_LIST[1181] = "UTL_SetDfmConfigCountValue";
	START_LAPTIMER(1181);
	UTL_SetDfmConfigCountValue( arg1, arg2, arg3);
	STOP_LAPTIMER(1181);
}
void _UTL_SetDfmConfigAddrScramByAlpg( DfmConfigHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[1182] = "UTL_SetDfmConfigAddrScramByAlpg";
	START_LAPTIMER(1182);
	UTL_SetDfmConfigAddrScramByAlpg( arg1, arg2, arg3);
	STOP_LAPTIMER(1182);
}
void _UTL_SetDfmConfigModeDelayByAlpg( DfmConfigHandle arg1, RadioButton arg2, RadioButton arg3, USlider arg4)
{
	MCI_LIST[1183] = "UTL_SetDfmConfigModeDelayByAlpg";
	START_LAPTIMER(1183);
	UTL_SetDfmConfigModeDelayByAlpg( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1183);
}
void _UTL_SetDfmConfigModeDelayByPds( DfmConfigHandle arg1, RadioButton arg2, RadioButton arg3, USlider arg4)
{
	MCI_LIST[1184] = "UTL_SetDfmConfigModeDelayByPds";
	START_LAPTIMER(1184);
	UTL_SetDfmConfigModeDelayByPds( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1184);
}
void _UTL_SetDfmConfigMultiMode( DfmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1185] = "UTL_SetDfmConfigMultiMode";
	START_LAPTIMER(1185);
	UTL_SetDfmConfigMultiMode( arg1, arg2);
	STOP_LAPTIMER(1185);
}
void _UTL_SetDfmConfigDut( DfmConfigHandle arg1, UT_DUT arg2)
{
	MCI_LIST[1186] = "UTL_SetDfmConfigDut";
	START_LAPTIMER(1186);
	UTL_SetDfmConfigDut( arg1, arg2);
	STOP_LAPTIMER(1186);
}
void _UTL_SetDfmConfigAllPin( DfmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[1187] = "UTL_SetDfmConfigAllPin";
	START_LAPTIMER(1187);
	UTL_SetDfmConfigAllPin( arg1, arg2);
	STOP_LAPTIMER(1187);
}
void _UTL_AddDfmConfigTargetPin( DfmConfigHandle arg1, UT_PIN arg2)
{
	MCI_LIST[1188] = "UTL_AddDfmConfigTargetPin";
	START_LAPTIMER(1188);
	UTL_AddDfmConfigTargetPin( arg1, arg2);
	STOP_LAPTIMER(1188);
}
void _UTL_ClearDfmConfigTargetPin( DfmConfigHandle arg1)
{
	MCI_LIST[1189] = "UTL_ClearDfmConfigTargetPin";
	START_LAPTIMER(1189);
	UTL_ClearDfmConfigTargetPin( arg1);
	STOP_LAPTIMER(1189);
}
void _UTL_SetDfmConfigTargetMemory( DfmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1190] = "UTL_SetDfmConfigTargetMemory";
	START_LAPTIMER(1190);
	UTL_SetDfmConfigTargetMemory( arg1, arg2);
	STOP_LAPTIMER(1190);
}
void _UTL_SendDfmConfig( DfmConfigHandle arg1)
{
	MCI_LIST[1191] = "UTL_SendDfmConfig";
	START_LAPTIMER(1191);
	UTL_SendDfmConfig( arg1);
	STOP_LAPTIMER(1191);
}
DfmAccessHandle _UTL_GetDfmAccessHandle()
{
	MCI_LIST[1192] = "UTL_GetDfmAccessHandle";
	START_LAPTIMER(1192);
	DfmAccessHandle retval = UTL_GetDfmAccessHandle();
	STOP_LAPTIMER(1192);
	return retval;
}
void _UTL_SetDfmAccessAlpgUnit( DfmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1193] = "UTL_SetDfmAccessAlpgUnit";
	START_LAPTIMER(1193);
	UTL_SetDfmAccessAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1193);
}
void _UTL_SetDfmAccessDataNumber( DfmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1194] = "UTL_SetDfmAccessDataNumber";
	START_LAPTIMER(1194);
	UTL_SetDfmAccessDataNumber( arg1, arg2);
	STOP_LAPTIMER(1194);
}
void _UTL_SetDfmAccessDataCount( DfmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1195] = "UTL_SetDfmAccessDataCount";
	START_LAPTIMER(1195);
	UTL_SetDfmAccessDataCount( arg1, arg2);
	STOP_LAPTIMER(1195);
}
void _UTL_AddDfmAccessDut( DfmAccessHandle arg1, UT_DUT arg2)
{
	MCI_LIST[1196] = "UTL_AddDfmAccessDut";
	START_LAPTIMER(1196);
	UTL_AddDfmAccessDut( arg1, arg2);
	STOP_LAPTIMER(1196);
}
void _UTL_ClearDfmAccessDut( DfmAccessHandle arg1)
{
	MCI_LIST[1197] = "UTL_ClearDfmAccessDut";
	START_LAPTIMER(1197);
	UTL_ClearDfmAccessDut( arg1);
	STOP_LAPTIMER(1197);
}
void _UTL_UpdateDfmData( DfmAccessHandle arg1)
{
	MCI_LIST[1198] = "UTL_UpdateDfmData";
	START_LAPTIMER(1198);
	UTL_UpdateDfmData( arg1);
	STOP_LAPTIMER(1198);
}
int _UTL_GetDfmDataUs( DfmAccessHandle arg1, RadioButton arg2, RadioButton arg3, USlider arg4, USlider * arg5)
{
	MCI_LIST[1199] = "UTL_GetDfmDataUs";
	START_LAPTIMER(1199);
	int retval = UTL_GetDfmDataUs( arg1, arg2, arg3, arg4, arg5);
	STOP_LAPTIMER(1199);
	return retval;
}
int _UTL_GetDfmDataCb( DfmAccessHandle arg1, RadioButton arg2, USlider arg3, USlider arg4, CheckButton * arg5)
{
	MCI_LIST[1200] = "UTL_GetDfmDataCb";
	START_LAPTIMER(1200);
	int retval = UTL_GetDfmDataCb( arg1, arg2, arg3, arg4, arg5);
	STOP_LAPTIMER(1200);
	return retval;
}
int _UTL_GetDfmDataPin( DfmAccessHandle arg1, RadioButton arg2, UT_DUT arg3, UT_PIN arg4, USlider arg5, USlider arg6, CheckButton * arg7)
{
	MCI_LIST[1201] = "UTL_GetDfmDataPin";
	START_LAPTIMER(1201);
	int retval = UTL_GetDfmDataPin( arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	STOP_LAPTIMER(1201);
	return retval;
}
DfmFailAddrHandle _UTL_GetDfmFailAddrHandle()
{
	MCI_LIST[1202] = "UTL_GetDfmFailAddrHandle";
	START_LAPTIMER(1202);
	DfmFailAddrHandle retval = UTL_GetDfmFailAddrHandle();
	STOP_LAPTIMER(1202);
	return retval;
}
void _UTL_SetDfmFailAddrAlpgUnit( DfmFailAddrHandle arg1, RadioButton arg2)
{
	MCI_LIST[1203] = "UTL_SetDfmFailAddrAlpgUnit";
	START_LAPTIMER(1203);
	UTL_SetDfmFailAddrAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1203);
}
void _UTL_SetDfmFailAddrDataNumber( DfmFailAddrHandle arg1, USlider arg2)
{
	MCI_LIST[1204] = "UTL_SetDfmFailAddrDataNumber";
	START_LAPTIMER(1204);
	UTL_SetDfmFailAddrDataNumber( arg1, arg2);
	STOP_LAPTIMER(1204);
}
void _UTL_SetDfmFailAddrDataCount( DfmFailAddrHandle arg1, USlider arg2)
{
	MCI_LIST[1205] = "UTL_SetDfmFailAddrDataCount";
	START_LAPTIMER(1205);
	UTL_SetDfmFailAddrDataCount( arg1, arg2);
	STOP_LAPTIMER(1205);
}
void _UTL_SetDfmFailAddrDut( DfmFailAddrHandle arg1, UT_DUT arg2)
{
	MCI_LIST[1206] = "UTL_SetDfmFailAddrDut";
	START_LAPTIMER(1206);
	UTL_SetDfmFailAddrDut( arg1, arg2);
	STOP_LAPTIMER(1206);
}
void _UTL_SetDfmFailAddrTargetPin( DfmFailAddrHandle arg1, UT_PIN arg2)
{
	MCI_LIST[1207] = "UTL_SetDfmFailAddrTargetPin";
	START_LAPTIMER(1207);
	UTL_SetDfmFailAddrTargetPin( arg1, arg2);
	STOP_LAPTIMER(1207);
}
void _UTL_UpdateDfmFailAddr( DfmFailAddrHandle arg1)
{
	MCI_LIST[1208] = "UTL_UpdateDfmFailAddr";
	START_LAPTIMER(1208);
	UTL_UpdateDfmFailAddr( arg1);
	STOP_LAPTIMER(1208);
}
int _UTL_GetDfmFailAddrFailCount( DfmFailAddrHandle arg1, USlider * arg2)
{
	MCI_LIST[1209] = "UTL_GetDfmFailAddrFailCount";
	START_LAPTIMER(1209);
	int retval = UTL_GetDfmFailAddrFailCount( arg1, arg2);
	STOP_LAPTIMER(1209);
	return retval;
}
void _UTL_GetDfmFailAddrData( DfmFailAddrHandle arg1, void * arg2, USlider arg3, USlider arg4)
{
	MCI_LIST[1210] = "UTL_GetDfmFailAddrData";
	START_LAPTIMER(1210);
	UTL_GetDfmFailAddrData( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1210);
}
DfmStatusHandle _UTL_GetDfmStatusHandle()
{
	MCI_LIST[1211] = "UTL_GetDfmStatusHandle";
	START_LAPTIMER(1211);
	DfmStatusHandle retval = UTL_GetDfmStatusHandle();
	STOP_LAPTIMER(1211);
	return retval;
}
void _UTL_SetDfmStatusAlpgUnit( DfmStatusHandle arg1, RadioButton arg2)
{
	MCI_LIST[1212] = "UTL_SetDfmStatusAlpgUnit";
	START_LAPTIMER(1212);
	UTL_SetDfmStatusAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1212);
}
void _UTL_SetDfmStatusDut( DfmStatusHandle arg1, UT_DUT arg2)
{
	MCI_LIST[1213] = "UTL_SetDfmStatusDut";
	START_LAPTIMER(1213);
	UTL_SetDfmStatusDut( arg1, arg2);
	STOP_LAPTIMER(1213);
}
void _UTL_UpdateDfmStatus( DfmStatusHandle arg1)
{
	MCI_LIST[1214] = "UTL_UpdateDfmStatus";
	START_LAPTIMER(1214);
	UTL_UpdateDfmStatus( arg1);
	STOP_LAPTIMER(1214);
}
int _UTL_GetDfmCounter( DfmStatusHandle arg1, RadioButton arg2, USlider * arg3, CheckButton * arg4)
{
	MCI_LIST[1215] = "UTL_GetDfmCounter";
	START_LAPTIMER(1215);
	int retval = UTL_GetDfmCounter( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1215);
	return retval;
}
int _UTL_GetDfmStopFlag( DfmStatusHandle arg1, CheckButton * arg2)
{
	MCI_LIST[1216] = "UTL_GetDfmStopFlag";
	START_LAPTIMER(1216);
	int retval = UTL_GetDfmStopFlag( arg1, arg2);
	STOP_LAPTIMER(1216);
	return retval;
}
int _UTL_GetDfmDataNumber( DfmStatusHandle arg1, USlider * arg2)
{
	MCI_LIST[1217] = "UTL_GetDfmDataNumber";
	START_LAPTIMER(1217);
	int retval = UTL_GetDfmDataNumber( arg1, arg2);
	STOP_LAPTIMER(1217);
	return retval;
}
int _UTL_GetDfmPatternCounter( DfmStatusHandle arg1, RadioButton arg2, USlider * arg3, CheckButton * arg4)
{
	MCI_LIST[1218] = "UTL_GetDfmPatternCounter";
	START_LAPTIMER(1218);
	int retval = UTL_GetDfmPatternCounter( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1218);
	return retval;
}
FlashHandle _UTL_GetFlashHandle()
{
	MCI_LIST[1219] = "UTL_GetFlashHandle";
	START_LAPTIMER(1219);
	FlashHandle retval = UTL_GetFlashHandle();
	STOP_LAPTIMER(1219);
	return retval;
}
void _UTL_SetFlashMaskModeAllDut( FlashHandle arg1, CheckButton arg2)
{
	MCI_LIST[1220] = "UTL_SetFlashMaskModeAllDut";
	START_LAPTIMER(1220);
	UTL_SetFlashMaskModeAllDut( arg1, arg2);
	STOP_LAPTIMER(1220);
}
void _UTL_SetFlashMaskModeByDut( FlashHandle arg1, UT_DUT arg2, CheckButton arg3)
{
	MCI_LIST[1221] = "UTL_SetFlashMaskModeByDut";
	START_LAPTIMER(1221);
	UTL_SetFlashMaskModeByDut( arg1, arg2, arg3);
	STOP_LAPTIMER(1221);
}
void _UTL_SetFlashLimitAllDut( FlashHandle arg1, Slider arg2)
{
	MCI_LIST[1222] = "UTL_SetFlashLimitAllDut";
	START_LAPTIMER(1222);
	UTL_SetFlashLimitAllDut( arg1, arg2);
	STOP_LAPTIMER(1222);
}
void _UTL_SetFlashLimitByDut( FlashHandle arg1, UT_DUT arg2, Slider arg3)
{
	MCI_LIST[1223] = "UTL_SetFlashLimitByDut";
	START_LAPTIMER(1223);
	UTL_SetFlashLimitByDut( arg1, arg2, arg3);
	STOP_LAPTIMER(1223);
}
void _UTL_SetFlashModeAllDut( FlashHandle arg1, RadioButton arg2)
{
	MCI_LIST[1224] = "UTL_SetFlashModeAllDut";
	START_LAPTIMER(1224);
	UTL_SetFlashModeAllDut( arg1, arg2);
	STOP_LAPTIMER(1224);
}
void _UTL_SetFlashHoldModeAllDut( FlashHandle arg1, RadioButton arg2)
{
	MCI_LIST[1225] = "UTL_SetFlashHoldModeAllDut";
	START_LAPTIMER(1225);
	UTL_SetFlashHoldModeAllDut( arg1, arg2);
	STOP_LAPTIMER(1225);
}
void _UTL_SetFlashHoldConditionAllDut( FlashHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1226] = "UTL_SetFlashHoldConditionAllDut";
	START_LAPTIMER(1226);
	UTL_SetFlashHoldConditionAllDut( arg1, arg2, arg3);
	STOP_LAPTIMER(1226);
}
void _UTL_SetFlashCounterConditionAllDut( FlashHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1227] = "UTL_SetFlashCounterConditionAllDut";
	START_LAPTIMER(1227);
	UTL_SetFlashCounterConditionAllDut( arg1, arg2, arg3);
	STOP_LAPTIMER(1227);
}
void _UTL_SetFlashCpInhPinMode( FlashHandle arg1, CheckButton arg2)
{
	MCI_LIST[1228] = "UTL_SetFlashCpInhPinMode";
	START_LAPTIMER(1228);
	UTL_SetFlashCpInhPinMode( arg1, arg2);
	STOP_LAPTIMER(1228);
}
void _UTL_SetFlashCpInhPin( FlashHandle arg1, char * arg2)
{
	MCI_LIST[1229] = "UTL_SetFlashCpInhPin";
	START_LAPTIMER(1229);
	UTL_SetFlashCpInhPin( arg1, arg2);
	STOP_LAPTIMER(1229);
}
void _UTL_SendFlash( FlashHandle arg1)
{
	MCI_LIST[1230] = "UTL_SendFlash";
	START_LAPTIMER(1230);
	UTL_SendFlash( arg1);
	STOP_LAPTIMER(1230);
}
ReadFlashHoldHandle _UTL_GetReadFlashHoldHandle()
{
	MCI_LIST[1231] = "UTL_GetReadFlashHoldHandle";
	START_LAPTIMER(1231);
	ReadFlashHoldHandle retval = UTL_GetReadFlashHoldHandle();
	STOP_LAPTIMER(1231);
	return retval;
}
void _UTL_SetReadFlashHoldDut( ReadFlashHoldHandle arg1, UT_DUT arg2)
{
	MCI_LIST[1232] = "UTL_SetReadFlashHoldDut";
	START_LAPTIMER(1232);
	UTL_SetReadFlashHoldDut( arg1, arg2);
	STOP_LAPTIMER(1232);
}
void _UTL_SetReadFlashHoldPin( ReadFlashHoldHandle arg1, UT_PIN arg2)
{
	MCI_LIST[1233] = "UTL_SetReadFlashHoldPin";
	START_LAPTIMER(1233);
	UTL_SetReadFlashHoldPin( arg1, arg2);
	STOP_LAPTIMER(1233);
}
void _UTL_SetReadFlashHoldTargetBank( ReadFlashHoldHandle arg1, RadioButton arg2)
{
	MCI_LIST[1234] = "UTL_SetReadFlashHoldTargetBank";
	START_LAPTIMER(1234);
	UTL_SetReadFlashHoldTargetBank( arg1, arg2);
	STOP_LAPTIMER(1234);
}
RadioButton _UTL_ReadFlashHold( ReadFlashHoldHandle arg1)
{
	MCI_LIST[1235] = "UTL_ReadFlashHold";
	START_LAPTIMER(1235);
	RadioButton retval = UTL_ReadFlashHold( arg1);
	STOP_LAPTIMER(1235);
	return retval;
}
ReadFlashCounterHandle _UTL_GetReadFlashCounterHandle()
{
	MCI_LIST[1236] = "UTL_GetReadFlashCounterHandle";
	START_LAPTIMER(1236);
	ReadFlashCounterHandle retval = UTL_GetReadFlashCounterHandle();
	STOP_LAPTIMER(1236);
	return retval;
}
void _UTL_SetReadFlashCounterDut( ReadFlashCounterHandle arg1, UT_DUT arg2)
{
	MCI_LIST[1237] = "UTL_SetReadFlashCounterDut";
	START_LAPTIMER(1237);
	UTL_SetReadFlashCounterDut( arg1, arg2);
	STOP_LAPTIMER(1237);
}
void _UTL_SetReadFlashCounterChannel( ReadFlashCounterHandle arg1, USlider arg2)
{
	MCI_LIST[1238] = "UTL_SetReadFlashCounterChannel";
	START_LAPTIMER(1238);
	UTL_SetReadFlashCounterChannel( arg1, arg2);
	STOP_LAPTIMER(1238);
}
void _UTL_SetReadFlashCounterTargetBank( ReadFlashCounterHandle arg1, RadioButton arg2)
{
	MCI_LIST[1239] = "UTL_SetReadFlashCounterTargetBank";
	START_LAPTIMER(1239);
	UTL_SetReadFlashCounterTargetBank( arg1, arg2);
	STOP_LAPTIMER(1239);
}
Slider _UTL_ReadFlashCounter( ReadFlashCounterHandle arg1)
{
	MCI_LIST[1240] = "UTL_ReadFlashCounter";
	START_LAPTIMER(1240);
	Slider retval = UTL_ReadFlashCounter( arg1);
	STOP_LAPTIMER(1240);
	return retval;
}
ReadFlashMaxFailHandle _UTL_GetReadFlashMaxFailHandle()
{
	MCI_LIST[1241] = "UTL_GetReadFlashMaxFailHandle";
	START_LAPTIMER(1241);
	ReadFlashMaxFailHandle retval = UTL_GetReadFlashMaxFailHandle();
	STOP_LAPTIMER(1241);
	return retval;
}
void _UTL_SetReadFlashMaxFailDut( ReadFlashMaxFailHandle arg1, UT_DUT arg2)
{
	MCI_LIST[1242] = "UTL_SetReadFlashMaxFailDut";
	START_LAPTIMER(1242);
	UTL_SetReadFlashMaxFailDut( arg1, arg2);
	STOP_LAPTIMER(1242);
}
void _UTL_SetReadFlashMaxFailTargetBank( ReadFlashMaxFailHandle arg1, RadioButton arg2)
{
	MCI_LIST[1243] = "UTL_SetReadFlashMaxFailTargetBank";
	START_LAPTIMER(1243);
	UTL_SetReadFlashMaxFailTargetBank( arg1, arg2);
	STOP_LAPTIMER(1243);
}
CheckButton _UTL_ReadFlashMaxFail( ReadFlashMaxFailHandle arg1)
{
	MCI_LIST[1244] = "UTL_ReadFlashMaxFail";
	START_LAPTIMER(1244);
	CheckButton retval = UTL_ReadFlashMaxFail( arg1);
	STOP_LAPTIMER(1244);
	return retval;
}
DbmConfigHandle _UTL_GetDbmConfigHandle()
{
	MCI_LIST[1245] = "UTL_GetDbmConfigHandle";
	START_LAPTIMER(1245);
	DbmConfigHandle retval = UTL_GetDbmConfigHandle();
	STOP_LAPTIMER(1245);
	return retval;
}
void _UTL_SetDbmConfigAccessMode( DbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1246] = "UTL_SetDbmConfigAccessMode";
	START_LAPTIMER(1246);
	UTL_SetDbmConfigAccessMode( arg1, arg2);
	STOP_LAPTIMER(1246);
}
int _UTL_GetDbmConfigAccessMode( DbmConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1247] = "UTL_GetDbmConfigAccessMode";
	START_LAPTIMER(1247);
	int retval = UTL_GetDbmConfigAccessMode( arg1, arg2);
	STOP_LAPTIMER(1247);
	return retval;
}
void _UTL_SetDbmConfigBitSize( DbmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[1248] = "UTL_SetDbmConfigBitSize";
	START_LAPTIMER(1248);
	UTL_SetDbmConfigBitSize( arg1, arg2);
	STOP_LAPTIMER(1248);
}
int _UTL_GetDbmConfigBitSize( DbmConfigHandle arg1, USlider * arg2)
{
	MCI_LIST[1249] = "UTL_GetDbmConfigBitSize";
	START_LAPTIMER(1249);
	int retval = UTL_GetDbmConfigBitSize( arg1, arg2);
	STOP_LAPTIMER(1249);
	return retval;
}
void _UTL_SetDbmConfigBlockSize( DbmConfigHandle  arg1, USlider  arg2)
{
	MCI_LIST[1250] = "UTL_SetDbmConfigBlockSize";
	START_LAPTIMER(1250);
	UTL_SetDbmConfigBlockSize( arg1, arg2);
	STOP_LAPTIMER(1250);
}
int _UTL_GetDbmConfigBlockSize( DbmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1251] = "UTL_GetDbmConfigBlockSize";
	START_LAPTIMER(1251);
	int retval = UTL_GetDbmConfigBlockSize( arg1, arg2);
	STOP_LAPTIMER(1251);
	return retval;
}
void _UTL_SetDbmConfigSequenceTable( DbmConfigHandle  arg1, USlider * arg2, USlider  arg3)
{
	MCI_LIST[1252] = "UTL_SetDbmConfigSequenceTable";
	START_LAPTIMER(1252);
	UTL_SetDbmConfigSequenceTable( arg1, arg2, arg3);
	STOP_LAPTIMER(1252);
}
void _UTL_SetDbmConfigAddrAssign( DbmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1253] = "UTL_SetDbmConfigAddrAssign";
	START_LAPTIMER(1253);
	UTL_SetDbmConfigAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(1253);
}
int _UTL_GetDbmConfigAddrAssign( DbmConfigHandle arg1, RadioButton arg2, RadioButton * arg3)
{
	MCI_LIST[1254] = "UTL_GetDbmConfigAddrAssign";
	START_LAPTIMER(1254);
	int retval = UTL_GetDbmConfigAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(1254);
	return retval;
}
void _UTL_SetDbmConfigBitAssignMode( DbmConfigHandle  arg1, RadioButton arg2)
{
	MCI_LIST[1255] = "UTL_SetDbmConfigBitAssignMode";
	START_LAPTIMER(1255);
	UTL_SetDbmConfigBitAssignMode( arg1, arg2);
	STOP_LAPTIMER(1255);
}
int _UTL_GetDbmConfigBitAssignMode( DbmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1256] = "UTL_GetDbmConfigBitAssignMode";
	START_LAPTIMER(1256);
	int retval = UTL_GetDbmConfigBitAssignMode( arg1, arg2);
	STOP_LAPTIMER(1256);
	return retval;
}
void _UTL_AddDbmConfigPinAssign( DbmConfigHandle arg1, RadioButton arg2, UT_PIN arg3)
{
	MCI_LIST[1257] = "UTL_AddDbmConfigPinAssign";
	START_LAPTIMER(1257);
	UTL_AddDbmConfigPinAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(1257);
}
PinCursor _UTL_GetDbmConfigPinAssign( DbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1258] = "UTL_GetDbmConfigPinAssign";
	START_LAPTIMER(1258);
	PinCursor retval = UTL_GetDbmConfigPinAssign( arg1, arg2);
	STOP_LAPTIMER(1258);
	return retval;
}
void _UTL_ClearDbmConfigPinAssign( DbmConfigHandle arg1)
{
	MCI_LIST[1259] = "UTL_ClearDbmConfigPinAssign";
	START_LAPTIMER(1259);
	UTL_ClearDbmConfigPinAssign( arg1);
	STOP_LAPTIMER(1259);
}
void _UTL_SendDbmConfig( DbmConfigHandle arg1)
{
	MCI_LIST[1260] = "UTL_SendDbmConfig";
	START_LAPTIMER(1260);
	UTL_SendDbmConfig( arg1);
	STOP_LAPTIMER(1260);
}
void _UTL_UpdateDbmConfig( DbmConfigHandle arg1)
{
	MCI_LIST[1261] = "UTL_UpdateDbmConfig";
	START_LAPTIMER(1261);
	UTL_UpdateDbmConfig( arg1);
	STOP_LAPTIMER(1261);
}
DbmFileHandle _UTL_GetDbmFileHandle()
{
	MCI_LIST[1262] = "UTL_GetDbmFileHandle";
	START_LAPTIMER(1262);
	DbmFileHandle retval = UTL_GetDbmFileHandle();
	STOP_LAPTIMER(1262);
	return retval;
}
void _UTL_SetDbmFileMpatName( DbmFileHandle arg1, char * arg2)
{
	MCI_LIST[1263] = "UTL_SetDbmFileMpatName";
	START_LAPTIMER(1263);
	UTL_SetDbmFileMpatName( arg1, arg2);
	STOP_LAPTIMER(1263);
}
void _UTL_SetDbmFileStartPc( DbmFileHandle arg1, USlider arg2)
{
	MCI_LIST[1264] = "UTL_SetDbmFileStartPc";
	START_LAPTIMER(1264);
	UTL_SetDbmFileStartPc( arg1, arg2);
	STOP_LAPTIMER(1264);
}
void _UTL_SendDbmFile( DbmFileHandle arg1)
{
	MCI_LIST[1265] = "UTL_SendDbmFile";
	START_LAPTIMER(1265);
	UTL_SendDbmFile( arg1);
	STOP_LAPTIMER(1265);
}
void _UTL_SetDbmFileResetMode( DbmFileHandle arg1, RadioButton arg2)
{
	MCI_LIST[1266] = "UTL_SetDbmFileResetMode";
	START_LAPTIMER(1266);
	UTL_SetDbmFileResetMode( arg1, arg2);
	STOP_LAPTIMER(1266);
}
void _UTL_ResetDbmFile( DbmFileHandle arg1)
{
	MCI_LIST[1267] = "UTL_ResetDbmFile";
	START_LAPTIMER(1267);
	UTL_ResetDbmFile( arg1);
	STOP_LAPTIMER(1267);
}
DbmAccessHandle _UTL_GetDbmAccessHandle()
{
	MCI_LIST[1268] = "UTL_GetDbmAccessHandle";
	START_LAPTIMER(1268);
	DbmAccessHandle retval = UTL_GetDbmAccessHandle();
	STOP_LAPTIMER(1268);
	return retval;
}
void _UTL_SetDbmAccessUnitNumber( DbmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1269] = "UTL_SetDbmAccessUnitNumber";
	START_LAPTIMER(1269);
	UTL_SetDbmAccessUnitNumber( arg1, arg2);
	STOP_LAPTIMER(1269);
}
void _UTL_SetDbmAccessAllUnit( DbmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[1270] = "UTL_SetDbmAccessAllUnit";
	START_LAPTIMER(1270);
	UTL_SetDbmAccessAllUnit( arg1, arg2);
	STOP_LAPTIMER(1270);
}
void _UTL_SetDbmAccessChildFlag( DbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1271] = "UTL_SetDbmAccessChildFlag";
	START_LAPTIMER(1271);
	UTL_SetDbmAccessChildFlag( arg1, arg2);
	STOP_LAPTIMER(1271);
}
void _UTL_SetDbmAccessDataKind( DbmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1272] = "UTL_SetDbmAccessDataKind";
	START_LAPTIMER(1272);
	UTL_SetDbmAccessDataKind( arg1, arg2);
	STOP_LAPTIMER(1272);
}
void _UTL_SetDbmAccessBlockNumber( DbmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1273] = "UTL_SetDbmAccessBlockNumber";
	START_LAPTIMER(1273);
	UTL_SetDbmAccessBlockNumber( arg1, arg2);
	STOP_LAPTIMER(1273);
}
void _UTL_SetDbmAccessAllBlock( DbmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[1274] = "UTL_SetDbmAccessAllBlock";
	START_LAPTIMER(1274);
	UTL_SetDbmAccessAllBlock( arg1, arg2);
	STOP_LAPTIMER(1274);
}
void _UTL_SetDbmAccessStartAddr( DbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1275] = "UTL_SetDbmAccessStartAddr";
	START_LAPTIMER(1275);
	UTL_SetDbmAccessStartAddr( arg1, arg2);
	STOP_LAPTIMER(1275);
}
void _UTL_SetDbmAccessStopAddr( DbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1276] = "UTL_SetDbmAccessStopAddr";
	START_LAPTIMER(1276);
	UTL_SetDbmAccessStopAddr( arg1, arg2);
	STOP_LAPTIMER(1276);
}
void _UTL_WriteDbm( DbmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[1277] = "UTL_WriteDbm";
	START_LAPTIMER(1277);
	UTL_WriteDbm( arg1, arg2, arg3);
	STOP_LAPTIMER(1277);
}
void _UTL_ReadDbm( DbmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[1278] = "UTL_ReadDbm";
	START_LAPTIMER(1278);
	UTL_ReadDbm( arg1, arg2, arg3);
	STOP_LAPTIMER(1278);
}
void _UTL_ResetDbm( DbmAccessHandle arg1)
{
	MCI_LIST[1279] = "UTL_ResetDbm";
	START_LAPTIMER(1279);
	UTL_ResetDbm( arg1);
	STOP_LAPTIMER(1279);
}
DbmPatCtrlHandle _UTL_GetDbmPatCtrlHandle()
{
	MCI_LIST[1280] = "UTL_GetDbmPatCtrlHandle";
	START_LAPTIMER(1280);
	DbmPatCtrlHandle retval = UTL_GetDbmPatCtrlHandle();
	STOP_LAPTIMER(1280);
	return retval;
}
void _UTL_SetDbmPatCtrlMode( DbmPatCtrlHandle arg1, RadioButton arg2)
{
	MCI_LIST[1281] = "UTL_SetDbmPatCtrlMode";
	START_LAPTIMER(1281);
	UTL_SetDbmPatCtrlMode( arg1, arg2);
	STOP_LAPTIMER(1281);
}
int _UTL_GetDbmPatCtrlMode( DbmPatCtrlHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1282] = "UTL_GetDbmPatCtrlMode";
	START_LAPTIMER(1282);
	int retval = UTL_GetDbmPatCtrlMode( arg1, arg2);
	STOP_LAPTIMER(1282);
	return retval;
}
void _UTL_SetDbmPatCtrlDbmFix( DbmPatCtrlHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[1283] = "UTL_SetDbmPatCtrlDbmFix";
	START_LAPTIMER(1283);
	UTL_SetDbmPatCtrlDbmFix( arg1, arg2, arg3);
	STOP_LAPTIMER(1283);
}
int _UTL_GetDbmPatCtrlDbmFix( DbmPatCtrlHandle arg1, RadioButton arg2, CheckButton * arg3)
{
	MCI_LIST[1284] = "UTL_GetDbmPatCtrlDbmFix";
	START_LAPTIMER(1284);
	int retval = UTL_GetDbmPatCtrlDbmFix( arg1, arg2, arg3);
	STOP_LAPTIMER(1284);
	return retval;
}
void _UTL_SendDbmPatCtrl( DbmPatCtrlHandle arg1)
{
	MCI_LIST[1285] = "UTL_SendDbmPatCtrl";
	START_LAPTIMER(1285);
	UTL_SendDbmPatCtrl( arg1);
	STOP_LAPTIMER(1285);
}
void _UTL_UpdateDbmPatCtrl( DbmPatCtrlHandle arg1)
{
	MCI_LIST[1286] = "UTL_UpdateDbmPatCtrl";
	START_LAPTIMER(1286);
	UTL_UpdateDbmPatCtrl( arg1);
	STOP_LAPTIMER(1286);
}
CbmFileHandle _UTL_GetCbmFileHandle()
{
	MCI_LIST[1287] = "UTL_GetCbmFileHandle";
	START_LAPTIMER(1287);
	CbmFileHandle retval = UTL_GetCbmFileHandle();
	STOP_LAPTIMER(1287);
	return retval;
}
void _UTL_SetCbmFileMpatName( CbmFileHandle arg1, char * arg2)
{
	MCI_LIST[1288] = "UTL_SetCbmFileMpatName";
	START_LAPTIMER(1288);
	UTL_SetCbmFileMpatName( arg1, arg2);
	STOP_LAPTIMER(1288);
}
void _UTL_SetCbmFileStartPc( CbmFileHandle arg1, USlider arg2)
{
	MCI_LIST[1289] = "UTL_SetCbmFileStartPc";
	START_LAPTIMER(1289);
	UTL_SetCbmFileStartPc( arg1, arg2);
	STOP_LAPTIMER(1289);
}
void _UTL_SendCbmFile( CbmFileHandle arg1)
{
	MCI_LIST[1290] = "UTL_SendCbmFile";
	START_LAPTIMER(1290);
	UTL_SendCbmFile( arg1);
	STOP_LAPTIMER(1290);
}
void _UTL_SetCbmFileResetMode( CbmFileHandle arg1, RadioButton arg2)
{
	MCI_LIST[1291] = "UTL_SetCbmFileResetMode";
	START_LAPTIMER(1291);
	UTL_SetCbmFileResetMode( arg1, arg2);
	STOP_LAPTIMER(1291);
}
void _UTL_ResetCbmFile( CbmFileHandle arg1)
{
	MCI_LIST[1292] = "UTL_ResetCbmFile";
	START_LAPTIMER(1292);
	UTL_ResetCbmFile( arg1);
	STOP_LAPTIMER(1292);
}
CbmAccessHandle _UTL_GetCbmAccessHandle()
{
	MCI_LIST[1293] = "UTL_GetCbmAccessHandle";
	START_LAPTIMER(1293);
	CbmAccessHandle retval = UTL_GetCbmAccessHandle();
	STOP_LAPTIMER(1293);
	return retval;
}
void _UTL_SetCbmAccessUnitNumber( CbmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1294] = "UTL_SetCbmAccessUnitNumber";
	START_LAPTIMER(1294);
	UTL_SetCbmAccessUnitNumber( arg1, arg2);
	STOP_LAPTIMER(1294);
}
void _UTL_SetCbmAccessAllUnit( CbmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[1295] = "UTL_SetCbmAccessAllUnit";
	START_LAPTIMER(1295);
	UTL_SetCbmAccessAllUnit( arg1, arg2);
	STOP_LAPTIMER(1295);
}
void _UTL_SetCbmAccessDataKind( CbmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1296] = "UTL_SetCbmAccessDataKind";
	START_LAPTIMER(1296);
	UTL_SetCbmAccessDataKind( arg1, arg2);
	STOP_LAPTIMER(1296);
}
void _UTL_SetCbmAccessStartAddr( CbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1297] = "UTL_SetCbmAccessStartAddr";
	START_LAPTIMER(1297);
	UTL_SetCbmAccessStartAddr( arg1, arg2);
	STOP_LAPTIMER(1297);
}
void _UTL_SetCbmAccessStopAddr( CbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[1298] = "UTL_SetCbmAccessStopAddr";
	START_LAPTIMER(1298);
	UTL_SetCbmAccessStopAddr( arg1, arg2);
	STOP_LAPTIMER(1298);
}
void _UTL_WriteCbm( CbmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[1299] = "UTL_WriteCbm";
	START_LAPTIMER(1299);
	UTL_WriteCbm( arg1, arg2, arg3);
	STOP_LAPTIMER(1299);
}
void _UTL_ReadCbm( CbmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[1300] = "UTL_ReadCbm";
	START_LAPTIMER(1300);
	UTL_ReadCbm( arg1, arg2, arg3);
	STOP_LAPTIMER(1300);
}
void _UTL_ResetCbm( CbmAccessHandle arg1)
{
	MCI_LIST[1301] = "UTL_ResetCbm";
	START_LAPTIMER(1301);
	UTL_ResetCbm( arg1);
	STOP_LAPTIMER(1301);
}
VpatFileHandle _UTL_GetVpatFileHandle()
{
	MCI_LIST[1302] = "UTL_GetVpatFileHandle";
	START_LAPTIMER(1302);
	VpatFileHandle retval = UTL_GetVpatFileHandle();
	STOP_LAPTIMER(1302);
	return retval;
}
void _UTL_SetVpatFileName( VpatFileHandle arg1, char * arg2)
{
	MCI_LIST[1303] = "UTL_SetVpatFileName";
	START_LAPTIMER(1303);
	UTL_SetVpatFileName( arg1, arg2);
	STOP_LAPTIMER(1303);
}
void _UTL_SendVpatFile( VpatFileHandle arg1)
{
	MCI_LIST[1304] = "UTL_SendVpatFile";
	START_LAPTIMER(1304);
	UTL_SendVpatFile( arg1);
	STOP_LAPTIMER(1304);
}
void _UTL_SetVpatFileResetMode( VpatFileHandle arg1, RadioButton arg2)
{
	MCI_LIST[1305] = "UTL_SetVpatFileResetMode";
	START_LAPTIMER(1305);
	UTL_SetVpatFileResetMode( arg1, arg2);
	STOP_LAPTIMER(1305);
}
void _UTL_ResetVpatFile( VpatFileHandle arg1)
{
	MCI_LIST[1306] = "UTL_ResetVpatFile";
	START_LAPTIMER(1306);
	UTL_ResetVpatFile( arg1);
	STOP_LAPTIMER(1306);
}
PdsMemorySelHandle _UTL_GetPdsMemorySelHandle()
{
	MCI_LIST[1307] = "UTL_GetPdsMemorySelHandle";
	START_LAPTIMER(1307);
	PdsMemorySelHandle retval = UTL_GetPdsMemorySelHandle();
	STOP_LAPTIMER(1307);
	return retval;
}
void _UTL_SetPdsMemorySelPin( PdsMemorySelHandle arg1, UT_PIN arg2)
{
	MCI_LIST[1308] = "UTL_SetPdsMemorySelPin";
	START_LAPTIMER(1308);
	UTL_SetPdsMemorySelPin( arg1, arg2);
	STOP_LAPTIMER(1308);
}
void _UTL_SetPdsMemorySelPinList( PdsMemorySelHandle arg1, char * arg2)
{
	MCI_LIST[1309] = "UTL_SetPdsMemorySelPinList";
	START_LAPTIMER(1309);
	UTL_SetPdsMemorySelPinList( arg1, arg2);
	STOP_LAPTIMER(1309);
}
void _UTL_SetPdsMemorySelDataMux( PdsMemorySelHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1310] = "UTL_SetPdsMemorySelDataMux";
	START_LAPTIMER(1310);
	UTL_SetPdsMemorySelDataMux( arg1, arg2, arg3);
	STOP_LAPTIMER(1310);
}
void _UTL_AddPdsMemorySelDut( PdsMemorySelHandle arg1, UT_DUT arg2)
{
	MCI_LIST[1311] = "UTL_AddPdsMemorySelDut";
	START_LAPTIMER(1311);
	UTL_AddPdsMemorySelDut( arg1, arg2);
	STOP_LAPTIMER(1311);
}
void _UTL_ClearPdsMemorySelDut( PdsMemorySelHandle arg1)
{
	MCI_LIST[1312] = "UTL_ClearPdsMemorySelDut";
	START_LAPTIMER(1312);
	UTL_ClearPdsMemorySelDut( arg1);
	STOP_LAPTIMER(1312);
}
void _UTL_SendPdsMemorySel( PdsMemorySelHandle arg1)
{
	MCI_LIST[1313] = "UTL_SendPdsMemorySel";
	START_LAPTIMER(1313);
	UTL_SendPdsMemorySel( arg1);
	STOP_LAPTIMER(1313);
}
PdsMemoryHandle _UTL_GetPdsMemoryHandle()
{
	MCI_LIST[1314] = "UTL_GetPdsMemoryHandle";
	START_LAPTIMER(1314);
	PdsMemoryHandle retval = UTL_GetPdsMemoryHandle();
	STOP_LAPTIMER(1314);
	return retval;
}
void _UTL_SetPdsMemoryIncPat( PdsMemoryHandle arg1, RadioButton arg2)
{
	MCI_LIST[1315] = "UTL_SetPdsMemoryIncPat";
	START_LAPTIMER(1315);
	UTL_SetPdsMemoryIncPat( arg1, arg2);
	STOP_LAPTIMER(1315);
}
void _UTL_SetPdsMemoryClearPat( PdsMemoryHandle arg1, RadioButton arg2)
{
	MCI_LIST[1316] = "UTL_SetPdsMemoryClearPat";
	START_LAPTIMER(1316);
	UTL_SetPdsMemoryClearPat( arg1, arg2);
	STOP_LAPTIMER(1316);
}
void _UTL_SetPdsMemoryJumpPat( PdsMemoryHandle arg1, RadioButton arg2)
{
	MCI_LIST[1317] = "UTL_SetPdsMemoryJumpPat";
	START_LAPTIMER(1317);
	UTL_SetPdsMemoryJumpPat( arg1, arg2);
	STOP_LAPTIMER(1317);
}
void _UTL_SetPdsMemoryJumpAddr( PdsMemoryHandle arg1, USlider arg2)
{
	MCI_LIST[1318] = "UTL_SetPdsMemoryJumpAddr";
	START_LAPTIMER(1318);
	UTL_SetPdsMemoryJumpAddr( arg1, arg2);
	STOP_LAPTIMER(1318);
}
void _UTL_SetPdsMemoryPat( PdsMemoryHandle arg1, USlider arg2, RadioButton arg3, RadioButton arg4)
{
	MCI_LIST[1319] = "UTL_SetPdsMemoryPat";
	START_LAPTIMER(1319);
	UTL_SetPdsMemoryPat( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1319);
}
void _UTL_SetPdsMemoryDataRate( PdsMemoryHandle arg1, USlider arg2)
{
	MCI_LIST[1320] = "UTL_SetPdsMemoryDataRate";
	START_LAPTIMER(1320);
	UTL_SetPdsMemoryDataRate( arg1, arg2);
	STOP_LAPTIMER(1320);
}
void _UTL_SendPdsMemory( PdsMemoryHandle arg1)
{
	MCI_LIST[1321] = "UTL_SendPdsMemory";
	START_LAPTIMER(1321);
	UTL_SendPdsMemory( arg1);
	STOP_LAPTIMER(1321);
}
void _UTL_InvokeTool( CheckButton arg1, char * arg2, int arg3, char ** arg4)
{
	MCI_LIST[1322] = "UTL_InvokeTool";
	START_LAPTIMER(1322);
	UTL_InvokeTool( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1322);
}
BurstHandle _UTL_GetBurstHandle()
{
	MCI_LIST[1323] = "UTL_GetBurstHandle";
	START_LAPTIMER(1323);
	BurstHandle retval = UTL_GetBurstHandle();
	STOP_LAPTIMER(1323);
	return retval;
}
void _UTL_SetBurstBlock( BurstHandle arg1, void (*arg2)(void))
{
	MCI_LIST[1324] = "UTL_SetBurstBlock";
	START_LAPTIMER(1324);
	UTL_SetBurstBlock( arg1, arg2);
	STOP_LAPTIMER(1324);
}
void _UTL_SetBurstBlockName( BurstHandle arg1, char * arg2)
{
	MCI_LIST[1325] = "UTL_SetBurstBlockName";
	START_LAPTIMER(1325);
	UTL_SetBurstBlockName( arg1, arg2);
	STOP_LAPTIMER(1325);
}
void _UTL_SendBurstData( BurstHandle arg1, RadioButton arg2)
{
	MCI_LIST[1326] = "UTL_SendBurstData";
	START_LAPTIMER(1326);
	UTL_SendBurstData( arg1, arg2);
	STOP_LAPTIMER(1326);
}
void _UTL_BurstPin( PinHandle arg1, char * arg2)
{
	MCI_LIST[1327] = "UTL_BurstPin";
	START_LAPTIMER(1327);
	UTL_BurstPin( arg1, arg2);
	STOP_LAPTIMER(1327);
}
void _UTL_BurstDc( DcHandle arg1, RadioButton arg2)
{
	MCI_LIST[1328] = "UTL_BurstDc";
	START_LAPTIMER(1328);
	UTL_BurstDc( arg1, arg2);
	STOP_LAPTIMER(1328);
}
void _UTL_BurstVs( VsHandle arg1, RadioButton arg2)
{
	MCI_LIST[1329] = "UTL_BurstVs";
	START_LAPTIMER(1329);
	UTL_BurstVs( arg1, arg2);
	STOP_LAPTIMER(1329);
}
void _UTL_BurstVi( ViHandle arg1, RadioButton arg2)
{
	MCI_LIST[1330] = "UTL_BurstVi";
	START_LAPTIMER(1330);
	UTL_BurstVi( arg1, arg2);
	STOP_LAPTIMER(1330);
}
void _UTL_BurstVo( VoHandle arg1, RadioButton arg2)
{
	MCI_LIST[1331] = "UTL_BurstVo";
	START_LAPTIMER(1331);
	UTL_BurstVo( arg1, arg2);
	STOP_LAPTIMER(1331);
}
void _UTL_BurstIl( IlHandle arg1, RadioButton arg2)
{
	MCI_LIST[1332] = "UTL_BurstIl";
	START_LAPTIMER(1332);
	UTL_BurstIl( arg1, arg2);
	STOP_LAPTIMER(1332);
}
void _UTL_BurstVt( VtHandle arg1, RadioButton arg2)
{
	MCI_LIST[1333] = "UTL_BurstVt";
	START_LAPTIMER(1333);
	UTL_BurstVt( arg1, arg2);
	STOP_LAPTIMER(1333);
}
void _UTL_BurstDclp( DclpHandle arg1, RadioButton arg2)
{
	MCI_LIST[1334] = "UTL_BurstDclp";
	START_LAPTIMER(1334);
	UTL_BurstDclp( arg1, arg2);
	STOP_LAPTIMER(1334);
}
void _UTL_BurstOnPowerCtrl( PowerCtrlHandle arg1)
{
	MCI_LIST[1335] = "UTL_BurstOnPowerCtrl";
	START_LAPTIMER(1335);
	UTL_BurstOnPowerCtrl( arg1);
	STOP_LAPTIMER(1335);
}
void _UTL_BurstOffPowerCtrl( PowerCtrlHandle arg1)
{
	MCI_LIST[1336] = "UTL_BurstOffPowerCtrl";
	START_LAPTIMER(1336);
	UTL_BurstOffPowerCtrl( arg1);
	STOP_LAPTIMER(1336);
}
void _UTL_BurstWaitTime( DSlider arg1)
{
	MCI_LIST[1337] = "UTL_BurstWaitTime";
	START_LAPTIMER(1337);
	UTL_BurstWaitTime( arg1);
	STOP_LAPTIMER(1337);
}
void _UTL_BurstDefineVariable( char * arg1, USlider arg2)
{
	MCI_LIST[1338] = "UTL_BurstDefineVariable";
	START_LAPTIMER(1338);
	UTL_BurstDefineVariable( arg1, arg2);
	STOP_LAPTIMER(1338);
}
void _UTL_BurstDefineArray( char * arg1, USlider arg2, CheckButton arg3, USlider arg4)
{
	MCI_LIST[1339] = "UTL_BurstDefineArray";
	START_LAPTIMER(1339);
	UTL_BurstDefineArray( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1339);
}
void _UTL_BurstArrayLoad( char * arg1, char * arg2, char * arg3)
{
	MCI_LIST[1340] = "UTL_BurstArrayLoad";
	START_LAPTIMER(1340);
	UTL_BurstArrayLoad( arg1, arg2, arg3);
	STOP_LAPTIMER(1340);
}
void _UTL_BurstArrayMov( char * arg1, char * arg2, char * arg3)
{
	MCI_LIST[1341] = "UTL_BurstArrayMov";
	START_LAPTIMER(1341);
	UTL_BurstArrayMov( arg1, arg2, arg3);
	STOP_LAPTIMER(1341);
}
USlider _UTL_ReadBurstArray( char * arg1, USlider arg2)
{
	MCI_LIST[1342] = "UTL_ReadBurstArray";
	START_LAPTIMER(1342);
	USlider retval = UTL_ReadBurstArray( arg1, arg2);
	STOP_LAPTIMER(1342);
	return retval;
}
void _UTL_ReadBurstArrayAll( char * arg1, USlider * arg2, USlider arg3)
{
	MCI_LIST[1343] = "UTL_ReadBurstArrayAll";
	START_LAPTIMER(1343);
	UTL_ReadBurstArrayAll( arg1, arg2, arg3);
	STOP_LAPTIMER(1343);
}
void _UTL_BurstLoad_I( char * arg1, USlider arg2)
{
	MCI_LIST[1344] = "UTL_BurstLoad_I";
	START_LAPTIMER(1344);
	UTL_BurstLoad_I( arg1, arg2);
	STOP_LAPTIMER(1344);
}
void _UTL_BurstInc( char * arg1)
{
	MCI_LIST[1345] = "UTL_BurstInc";
	START_LAPTIMER(1345);
	UTL_BurstInc( arg1);
	STOP_LAPTIMER(1345);
}
void _UTL_BurstDec( char * arg1)
{
	MCI_LIST[1346] = "UTL_BurstDec";
	START_LAPTIMER(1346);
	UTL_BurstDec( arg1);
	STOP_LAPTIMER(1346);
}
void _UTL_BurstInv( char * arg1)
{
	MCI_LIST[1347] = "UTL_BurstInv";
	START_LAPTIMER(1347);
	UTL_BurstInv( arg1);
	STOP_LAPTIMER(1347);
}
void _UTL_BurstSr( char * arg1)
{
	MCI_LIST[1348] = "UTL_BurstSr";
	START_LAPTIMER(1348);
	UTL_BurstSr( arg1);
	STOP_LAPTIMER(1348);
}
void _UTL_BurstSl( char * arg1)
{
	MCI_LIST[1349] = "UTL_BurstSl";
	START_LAPTIMER(1349);
	UTL_BurstSl( arg1);
	STOP_LAPTIMER(1349);
}
void _UTL_BurstAdd_I( char * arg1, USlider arg2)
{
	MCI_LIST[1350] = "UTL_BurstAdd_I";
	START_LAPTIMER(1350);
	UTL_BurstAdd_I( arg1, arg2);
	STOP_LAPTIMER(1350);
}
void _UTL_BurstSub_I( char * arg1, USlider arg2)
{
	MCI_LIST[1351] = "UTL_BurstSub_I";
	START_LAPTIMER(1351);
	UTL_BurstSub_I( arg1, arg2);
	STOP_LAPTIMER(1351);
}
void _UTL_BurstAnd_I( char * arg1, USlider arg2)
{
	MCI_LIST[1352] = "UTL_BurstAnd_I";
	START_LAPTIMER(1352);
	UTL_BurstAnd_I( arg1, arg2);
	STOP_LAPTIMER(1352);
}
void _UTL_BurstOr_I( char * arg1, USlider arg2)
{
	MCI_LIST[1353] = "UTL_BurstOr_I";
	START_LAPTIMER(1353);
	UTL_BurstOr_I( arg1, arg2);
	STOP_LAPTIMER(1353);
}
void _UTL_BurstXor_I( char * arg1, USlider arg2)
{
	MCI_LIST[1354] = "UTL_BurstXor_I";
	START_LAPTIMER(1354);
	UTL_BurstXor_I( arg1, arg2);
	STOP_LAPTIMER(1354);
}
void _UTL_BurstAdd_V( char * arg1, char * arg2)
{
	MCI_LIST[1355] = "UTL_BurstAdd_V";
	START_LAPTIMER(1355);
	UTL_BurstAdd_V( arg1, arg2);
	STOP_LAPTIMER(1355);
}
void _UTL_BurstSub_V( char * arg1, char * arg2)
{
	MCI_LIST[1356] = "UTL_BurstSub_V";
	START_LAPTIMER(1356);
	UTL_BurstSub_V( arg1, arg2);
	STOP_LAPTIMER(1356);
}
void _UTL_BurstAnd_V( char * arg1, char * arg2)
{
	MCI_LIST[1357] = "UTL_BurstAnd_V";
	START_LAPTIMER(1357);
	UTL_BurstAnd_V( arg1, arg2);
	STOP_LAPTIMER(1357);
}
void _UTL_BurstOr_V( char * arg1, char * arg2)
{
	MCI_LIST[1358] = "UTL_BurstOr_V";
	START_LAPTIMER(1358);
	UTL_BurstOr_V( arg1, arg2);
	STOP_LAPTIMER(1358);
}
void _UTL_BurstXor_V( char * arg1, char * arg2)
{
	MCI_LIST[1359] = "UTL_BurstXor_V";
	START_LAPTIMER(1359);
	UTL_BurstXor_V( arg1, arg2);
	STOP_LAPTIMER(1359);
}
void _UTL_BurstMov( char * arg1, char * arg2)
{
	MCI_LIST[1360] = "UTL_BurstMov";
	START_LAPTIMER(1360);
	UTL_BurstMov( arg1, arg2);
	STOP_LAPTIMER(1360);
}
void _UTL_BurstLabel( char * arg1)
{
	MCI_LIST[1361] = "UTL_BurstLabel";
	START_LAPTIMER(1361);
	UTL_BurstLabel( arg1);
	STOP_LAPTIMER(1361);
}
void _UTL_BurstGoto( char * arg1)
{
	MCI_LIST[1362] = "UTL_BurstGoto";
	START_LAPTIMER(1362);
	UTL_BurstGoto( arg1);
	STOP_LAPTIMER(1362);
}
void _UTL_BurstIf_I( char * arg1, RadioButton arg2, USlider arg3, char * arg4)
{
	MCI_LIST[1363] = "UTL_BurstIf_I";
	START_LAPTIMER(1363);
	UTL_BurstIf_I( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1363);
}
void _UTL_BurstIf_V( char * arg1, RadioButton arg2, char * arg3, char * arg4)
{
	MCI_LIST[1364] = "UTL_BurstIf_V";
	START_LAPTIMER(1364);
	UTL_BurstIf_V( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1364);
}
void _UTL_BurstRegBar1( USlider arg1)
{
	MCI_LIST[1365] = "UTL_BurstRegBar1";
	START_LAPTIMER(1365);
	UTL_BurstRegBar1( arg1);
	STOP_LAPTIMER(1365);
}
void _UTL_BurstRegJar( USlider arg1)
{
	MCI_LIST[1366] = "UTL_BurstRegJar";
	START_LAPTIMER(1366);
	UTL_BurstRegJar( arg1);
	STOP_LAPTIMER(1366);
}
void _UTL_BurstFailCounterCondition( FailCounterHandle arg1)
{
	MCI_LIST[1367] = "UTL_BurstFailCounterCondition";
	START_LAPTIMER(1367);
	UTL_BurstFailCounterCondition( arg1);
	STOP_LAPTIMER(1367);
}
void _UTL_BurstReadFailCounter( UT_DUT arg1, char * arg2)
{
	MCI_LIST[1368] = "UTL_BurstReadFailCounter";
	START_LAPTIMER(1368);
	UTL_BurstReadFailCounter( arg1, arg2);
	STOP_LAPTIMER(1368);
}
void _UTL_BurstReadFailCounterMaxFail( UT_DUT arg1, char * arg2)
{
	MCI_LIST[1369] = "UTL_BurstReadFailCounterMaxFail";
	START_LAPTIMER(1369);
	UTL_BurstReadFailCounterMaxFail( arg1, arg2);
	STOP_LAPTIMER(1369);
}
void _UTL_BurstFlash( FlashHandle arg1)
{
	MCI_LIST[1370] = "UTL_BurstFlash";
	START_LAPTIMER(1370);
	UTL_BurstFlash( arg1);
	STOP_LAPTIMER(1370);
}
void _UTL_BurstReadFlashHold( UT_DUT arg1, UT_PIN arg2, char * arg3)
{
	MCI_LIST[1371] = "UTL_BurstReadFlashHold";
	START_LAPTIMER(1371);
	UTL_BurstReadFlashHold( arg1, arg2, arg3);
	STOP_LAPTIMER(1371);
}
void _UTL_BurstReadFlashCounter( UT_DUT arg1, char * arg2)
{
	MCI_LIST[1372] = "UTL_BurstReadFlashCounter";
	START_LAPTIMER(1372);
	UTL_BurstReadFlashCounter( arg1, arg2);
	STOP_LAPTIMER(1372);
}
void _UTL_BurstReadFlashMaxFail( UT_DUT arg1, char * arg2)
{
	MCI_LIST[1373] = "UTL_BurstReadFlashMaxFail";
	START_LAPTIMER(1373);
	UTL_BurstReadFlashMaxFail( arg1, arg2);
	STOP_LAPTIMER(1373);
}
void _UTL_SetAuxDutSignalBurstVariableName( AuxDutSignalHandle arg1, char * arg2)
{
	MCI_LIST[1374] = "UTL_SetAuxDutSignalBurstVariableName";
	START_LAPTIMER(1374);
	UTL_SetAuxDutSignalBurstVariableName( arg1, arg2);
	STOP_LAPTIMER(1374);
}
void _UTL_BurstAuxDutSignal( AuxDutSignalHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1375] = "UTL_BurstAuxDutSignal";
	START_LAPTIMER(1375);
	UTL_BurstAuxDutSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(1375);
}
void _UTL_BurstReadAuxDutSignal( AuxDutSignalHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1376] = "UTL_BurstReadAuxDutSignal";
	START_LAPTIMER(1376);
	UTL_BurstReadAuxDutSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(1376);
}
USlider _UTL_ReadBurstVariable( char * arg1)
{
	MCI_LIST[1377] = "UTL_ReadBurstVariable";
	START_LAPTIMER(1377);
	USlider retval = UTL_ReadBurstVariable( arg1);
	STOP_LAPTIMER(1377);
	return retval;
}
void _UTL_BurstClearAll()
{
	MCI_LIST[1378] = "UTL_BurstClearAll";
	START_LAPTIMER(1378);
	UTL_BurstClearAll();
	STOP_LAPTIMER(1378);
}
void _UTL_ExecCalb( char * arg1, char * arg2)
{
	MCI_LIST[1379] = "UTL_ExecCalb";
	START_LAPTIMER(1379);
	UTL_ExecCalb( arg1, arg2);
	STOP_LAPTIMER(1379);
}
void _UTL_ExecSbcal( char * arg1, char * arg2)
{
	MCI_LIST[1380] = "UTL_ExecSbcal";
	START_LAPTIMER(1380);
	UTL_ExecSbcal( arg1, arg2);
	STOP_LAPTIMER(1380);
}
RadioButton _UTL_CheckPartTestMode( RadioButton arg1)
{
	MCI_LIST[1381] = "UTL_CheckPartTestMode";
	START_LAPTIMER(1381);
	RadioButton retval = UTL_CheckPartTestMode( arg1);
	STOP_LAPTIMER(1381);
	return retval;
}
CheckButton _UTL_CheckAlarmOccurrence( RadioButton arg1)
{
	MCI_LIST[1382] = "UTL_CheckAlarmOccurrence";
	START_LAPTIMER(1382);
	CheckButton retval = UTL_CheckAlarmOccurrence( arg1);
	STOP_LAPTIMER(1382);
	return retval;
}
RadioButton _UTL_ReadTestMode()
{
	MCI_LIST[1383] = "UTL_ReadTestMode";
	START_LAPTIMER(1383);
	RadioButton retval = UTL_ReadTestMode();
	STOP_LAPTIMER(1383);
	return retval;
}
char * _UTL_ReadStartTestName()
{
	MCI_LIST[1384] = "UTL_ReadStartTestName";
	START_LAPTIMER(1384);
	char * retval = UTL_ReadStartTestName();
	STOP_LAPTIMER(1384);
	return retval;
}
CheckButton _UTL_ReadDataLogSwitchCondition( RadioButton arg1)
{
	MCI_LIST[1385] = "UTL_ReadDataLogSwitchCondition";
	START_LAPTIMER(1385);
	CheckButton retval = UTL_ReadDataLogSwitchCondition( arg1);
	STOP_LAPTIMER(1385);
	return retval;
}
CheckButton _UTL_ReadTestModeOptionsSwitchCondition( RadioButton arg1)
{
	MCI_LIST[1386] = "UTL_ReadTestModeOptionsSwitchCondition";
	START_LAPTIMER(1386);
	CheckButton retval = UTL_ReadTestModeOptionsSwitchCondition( arg1);
	STOP_LAPTIMER(1386);
	return retval;
}
void _UTL_InitResult()
{
	MCI_LIST[1387] = "UTL_InitResult";
	START_LAPTIMER(1387);
	UTL_InitResult();
	STOP_LAPTIMER(1387);
}
RadioButton _UTL_SaveResult( RadioButton arg1)
{
	MCI_LIST[1388] = "UTL_SaveResult";
	START_LAPTIMER(1388);
	RadioButton retval = UTL_SaveResult( arg1);
	STOP_LAPTIMER(1388);
	return retval;
}
RadioButton _UTL_CheckRepeatPause()
{
	MCI_LIST[1389] = "UTL_CheckRepeatPause";
	START_LAPTIMER(1389);
	RadioButton retval = UTL_CheckRepeatPause();
	STOP_LAPTIMER(1389);
	return retval;
}
void _UTL_ResetDctAllPin( RadioButton arg1)
{
	MCI_LIST[1390] = "UTL_ResetDctAllPin";
	START_LAPTIMER(1390);
	UTL_ResetDctAllPin( arg1);
	STOP_LAPTIMER(1390);
}
DctCtrlRelayHandle _UTL_GetDctCtrlRelayHandle()
{
	MCI_LIST[1391] = "UTL_GetDctCtrlRelayHandle";
	START_LAPTIMER(1391);
	DctCtrlRelayHandle retval = UTL_GetDctCtrlRelayHandle();
	STOP_LAPTIMER(1391);
	return retval;
}
void _UTL_InitializeDctCtrlRelayHandle( DctCtrlRelayHandle arg1)
{
	MCI_LIST[1392] = "UTL_InitializeDctCtrlRelayHandle";
	START_LAPTIMER(1392);
	UTL_InitializeDctCtrlRelayHandle( arg1);
	STOP_LAPTIMER(1392);
}
void _UTL_SetDctCtrlRelayVi( DctCtrlRelayHandle arg1, CheckButton arg2)
{
	MCI_LIST[1393] = "UTL_SetDctCtrlRelayVi";
	START_LAPTIMER(1393);
	UTL_SetDctCtrlRelayVi( arg1, arg2);
	STOP_LAPTIMER(1393);
}
void _UTL_SetDctCtrlRelayVo( DctCtrlRelayHandle arg1, CheckButton arg2)
{
	MCI_LIST[1394] = "UTL_SetDctCtrlRelayVo";
	START_LAPTIMER(1394);
	UTL_SetDctCtrlRelayVo( arg1, arg2);
	STOP_LAPTIMER(1394);
}
void _UTL_SetDctCtrlRelayVihh( DctCtrlRelayHandle arg1, CheckButton arg2)
{
	MCI_LIST[1395] = "UTL_SetDctCtrlRelayVihh";
	START_LAPTIMER(1395);
	UTL_SetDctCtrlRelayVihh( arg1, arg2);
	STOP_LAPTIMER(1395);
}
void _UTL_SetDctCtrlRelayHvDr( DctCtrlRelayHandle arg1, CheckButton arg2)
{
	MCI_LIST[1396] = "UTL_SetDctCtrlRelayHvDr";
	START_LAPTIMER(1396);
	UTL_SetDctCtrlRelayHvDr( arg1, arg2);
	STOP_LAPTIMER(1396);
}
void _UTL_SetDctCtrlRelayTerm( DctCtrlRelayHandle arg1, CheckButton arg2)
{
	MCI_LIST[1397] = "UTL_SetDctCtrlRelayTerm";
	START_LAPTIMER(1397);
	UTL_SetDctCtrlRelayTerm( arg1, arg2);
	STOP_LAPTIMER(1397);
}
void _UTL_SetDctCtrlRelayPl( DctCtrlRelayHandle arg1, RadioButton arg2)
{
	MCI_LIST[1398] = "UTL_SetDctCtrlRelayPl";
	START_LAPTIMER(1398);
	UTL_SetDctCtrlRelayPl( arg1, arg2);
	STOP_LAPTIMER(1398);
}
void _UTL_SetDctCtrlRelayDc( DctCtrlRelayHandle arg1, CheckButton arg2)
{
	MCI_LIST[1399] = "UTL_SetDctCtrlRelayDc";
	START_LAPTIMER(1399);
	UTL_SetDctCtrlRelayDc( arg1, arg2);
	STOP_LAPTIMER(1399);
}
void _UTL_SetDctCtrlRelayDutCtrl( DctCtrlRelayHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1400] = "UTL_SetDctCtrlRelayDutCtrl";
	START_LAPTIMER(1400);
	UTL_SetDctCtrlRelayDutCtrl( arg1, arg2, arg3);
	STOP_LAPTIMER(1400);
}
void _UTL_SetDctCtrlRelayWaitTime( DctCtrlRelayHandle arg1, DSlider arg2)
{
	MCI_LIST[1401] = "UTL_SetDctCtrlRelayWaitTime";
	START_LAPTIMER(1401);
	UTL_SetDctCtrlRelayWaitTime( arg1, arg2);
	STOP_LAPTIMER(1401);
}
void _UTL_SendDctCtrlRelay( DctCtrlRelayHandle arg1, UT_PIN arg2)
{
	MCI_LIST[1402] = "UTL_SendDctCtrlRelay";
	START_LAPTIMER(1402);
	UTL_SendDctCtrlRelay( arg1, arg2);
	STOP_LAPTIMER(1402);
}
DSlider _UTL_ReadDctCtrlRelayActionTime( UT_PIN arg1, RadioButton arg2)
{
	MCI_LIST[1403] = "UTL_ReadDctCtrlRelayActionTime";
	START_LAPTIMER(1403);
	DSlider retval = UTL_ReadDctCtrlRelayActionTime( arg1, arg2);
	STOP_LAPTIMER(1403);
	return retval;
}
DSlider _UTL_ReadDctWaitTime( RadioButton arg1, UT_PIN arg2, RadioButton arg3)
{
	MCI_LIST[1404] = "UTL_ReadDctWaitTime";
	START_LAPTIMER(1404);
	DSlider retval = UTL_ReadDctWaitTime( arg1, arg2, arg3);
	STOP_LAPTIMER(1404);
	return retval;
}
DutCursor _UTL_GetDctDutGroupCursor( UT_PIN arg1, RadioButton arg2)
{
	MCI_LIST[1405] = "UTL_GetDctDutGroupCursor";
	START_LAPTIMER(1405);
	DutCursor retval = UTL_GetDctDutGroupCursor( arg1, arg2);
	STOP_LAPTIMER(1405);
	return retval;
}
RadioButton _UTL_GetDctDutGroupMaxNumber( UT_PIN arg1)
{
	MCI_LIST[1406] = "UTL_GetDctDutGroupMaxNumber";
	START_LAPTIMER(1406);
	RadioButton retval = UTL_GetDctDutGroupMaxNumber( arg1);
	STOP_LAPTIMER(1406);
	return retval;
}
StartAdcHandle _UTL_GetStartAdcHandle()
{
	MCI_LIST[1407] = "UTL_GetStartAdcHandle";
	START_LAPTIMER(1407);
	StartAdcHandle retval = UTL_GetStartAdcHandle();
	STOP_LAPTIMER(1407);
	return retval;
}
void _UTL_SetStartAdcPinType( StartAdcHandle arg1, RadioButton arg2)
{
	MCI_LIST[1408] = "UTL_SetStartAdcPinType";
	START_LAPTIMER(1408);
	UTL_SetStartAdcPinType( arg1, arg2);
	STOP_LAPTIMER(1408);
}
void _UTL_AddStartAdcPinNumber( StartAdcHandle arg1, UT_PIN arg2)
{
	MCI_LIST[1409] = "UTL_AddStartAdcPinNumber";
	START_LAPTIMER(1409);
	UTL_AddStartAdcPinNumber( arg1, arg2);
	STOP_LAPTIMER(1409);
}
void _UTL_ClearStartAdcPinNumber( StartAdcHandle arg1)
{
	MCI_LIST[1410] = "UTL_ClearStartAdcPinNumber";
	START_LAPTIMER(1410);
	UTL_ClearStartAdcPinNumber( arg1);
	STOP_LAPTIMER(1410);
}
void _UTL_SetStartAdcTargetDctPin( StartAdcHandle arg1, RadioButton arg2)
{
	MCI_LIST[1411] = "UTL_SetStartAdcTargetDctPin";
	START_LAPTIMER(1411);
	UTL_SetStartAdcTargetDctPin( arg1, arg2);
	STOP_LAPTIMER(1411);
}
void _UTL_SetStartAdcSettlingTime( StartAdcHandle arg1, DSlider arg2)
{
	MCI_LIST[1412] = "UTL_SetStartAdcSettlingTime";
	START_LAPTIMER(1412);
	UTL_SetStartAdcSettlingTime( arg1, arg2);
	STOP_LAPTIMER(1412);
}
void _UTL_SendStartAdc( StartAdcHandle arg1)
{
	MCI_LIST[1413] = "UTL_SendStartAdc";
	START_LAPTIMER(1413);
	UTL_SendStartAdc( arg1);
	STOP_LAPTIMER(1413);
}
void _UTL_StartAdc()
{
	MCI_LIST[1414] = "UTL_StartAdc";
	START_LAPTIMER(1414);
	UTL_StartAdc();
	STOP_LAPTIMER(1414);
}
void _UTL_SaveStartAdcDctPin( StartAdcHandle arg1)
{
	MCI_LIST[1415] = "UTL_SaveStartAdcDctPin";
	START_LAPTIMER(1415);
	UTL_SaveStartAdcDctPin( arg1);
	STOP_LAPTIMER(1415);
}
RadioButton _UTL_ReadStartAdcResult( RadioButton arg1, UT_PIN arg2, UT_DUT arg3)
{
	MCI_LIST[1416] = "UTL_ReadStartAdcResult";
	START_LAPTIMER(1416);
	RadioButton retval = UTL_ReadStartAdcResult( arg1, arg2, arg3);
	STOP_LAPTIMER(1416);
	return retval;
}
DSlider _UTL_ReadStartAdcMeasData( RadioButton arg1, UT_PIN arg2, UT_DUT arg3, CheckButton * arg4)
{
	MCI_LIST[1417] = "UTL_ReadStartAdcMeasData";
	START_LAPTIMER(1417);
	DSlider retval = UTL_ReadStartAdcMeasData( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1417);
	return retval;
}
void _UTL_PrintDctDataLog( RadioButton arg1, RadioButton arg2, UT_PIN arg3, UT_DUT arg4)
{
	MCI_LIST[1418] = "UTL_PrintDctDataLog";
	START_LAPTIMER(1418);
	UTL_PrintDctDataLog( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1418);
}
PinCursor _UTL_GetDctPinGroupCursor( char * arg1, RadioButton arg2)
{
	MCI_LIST[1419] = "UTL_GetDctPinGroupCursor";
	START_LAPTIMER(1419);
	PinCursor retval = UTL_GetDctPinGroupCursor( arg1, arg2);
	STOP_LAPTIMER(1419);
	return retval;
}
RadioButton _UTL_GetDctPinGroupMaxNumber( char * arg1)
{
	MCI_LIST[1420] = "UTL_GetDctPinGroupMaxNumber";
	START_LAPTIMER(1420);
	RadioButton retval = UTL_GetDctPinGroupMaxNumber( arg1);
	STOP_LAPTIMER(1420);
	return retval;
}
DctVsCtrlRelayHandle _UTL_GetDctVsCtrlRelayHandle()
{
	MCI_LIST[1421] = "UTL_GetDctVsCtrlRelayHandle";
	START_LAPTIMER(1421);
	DctVsCtrlRelayHandle retval = UTL_GetDctVsCtrlRelayHandle();
	STOP_LAPTIMER(1421);
	return retval;
}
void _UTL_InitializeDctVsCtrlRelayHandle( DctVsCtrlRelayHandle arg1)
{
	MCI_LIST[1422] = "UTL_InitializeDctVsCtrlRelayHandle";
	START_LAPTIMER(1422);
	UTL_InitializeDctVsCtrlRelayHandle( arg1);
	STOP_LAPTIMER(1422);
}
void _UTL_SetDctVsCtrlRelayDutCtrl( DctVsCtrlRelayHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1423] = "UTL_SetDctVsCtrlRelayDutCtrl";
	START_LAPTIMER(1423);
	UTL_SetDctVsCtrlRelayDutCtrl( arg1, arg2, arg3);
	STOP_LAPTIMER(1423);
}
void _UTL_SetDctVsCtrlRelayWaitTime( DctVsCtrlRelayHandle arg1, DSlider arg2)
{
	MCI_LIST[1424] = "UTL_SetDctVsCtrlRelayWaitTime";
	START_LAPTIMER(1424);
	UTL_SetDctVsCtrlRelayWaitTime( arg1, arg2);
	STOP_LAPTIMER(1424);
}
void _UTL_SendDctVsCtrlRelay( DctVsCtrlRelayHandle arg1, RadioButton arg2)
{
	MCI_LIST[1425] = "UTL_SendDctVsCtrlRelay";
	START_LAPTIMER(1425);
	UTL_SendDctVsCtrlRelay( arg1, arg2);
	STOP_LAPTIMER(1425);
}
DSlider _UTL_ReadDctVsCtrlRelayActionTime( RadioButton arg1, RadioButton arg2)
{
	MCI_LIST[1426] = "UTL_ReadDctVsCtrlRelayActionTime";
	START_LAPTIMER(1426);
	DSlider retval = UTL_ReadDctVsCtrlRelayActionTime( arg1, arg2);
	STOP_LAPTIMER(1426);
	return retval;
}
DutCursor _UTL_GetDctVsDutGroupCursor( RadioButton arg1, RadioButton arg2)
{
	MCI_LIST[1427] = "UTL_GetDctVsDutGroupCursor";
	START_LAPTIMER(1427);
	DutCursor retval = UTL_GetDctVsDutGroupCursor( arg1, arg2);
	STOP_LAPTIMER(1427);
	return retval;
}
RadioButton _UTL_GetDctVsDutGroupMaxNumber( RadioButton arg1)
{
	MCI_LIST[1428] = "UTL_GetDctVsDutGroupMaxNumber";
	START_LAPTIMER(1428);
	RadioButton retval = UTL_GetDctVsDutGroupMaxNumber( arg1);
	STOP_LAPTIMER(1428);
	return retval;
}
RadioButton _UTL_ReadAlpgStatus()
{
	MCI_LIST[1429] = "UTL_ReadAlpgStatus";
	START_LAPTIMER(1429);
	RadioButton retval = UTL_ReadAlpgStatus();
	STOP_LAPTIMER(1429);
	return retval;
}
RadioButton _UTL_ReadAlpgStatusFlag()
{
	MCI_LIST[1430] = "UTL_ReadAlpgStatusFlag";
	START_LAPTIMER(1430);
	RadioButton retval = UTL_ReadAlpgStatusFlag();
	STOP_LAPTIMER(1430);
	return retval;
}
CheckButton _UTL_CheckAlpgStatusFlag( RadioButton arg1)
{
	MCI_LIST[1431] = "UTL_CheckAlpgStatusFlag";
	START_LAPTIMER(1431);
	CheckButton retval = UTL_CheckAlpgStatusFlag( arg1);
	STOP_LAPTIMER(1431);
	return retval;
}
void _UTL_ResetFctAllPin()
{
	MCI_LIST[1432] = "UTL_ResetFctAllPin";
	START_LAPTIMER(1432);
	UTL_ResetFctAllPin();
	STOP_LAPTIMER(1432);
}
MpatHandle _UTL_GetMpatHandle()
{
	MCI_LIST[1433] = "UTL_GetMpatHandle";
	START_LAPTIMER(1433);
	MpatHandle retval = UTL_GetMpatHandle();
	STOP_LAPTIMER(1433);
	return retval;
}
void _UTL_SetMpatStartPc( MpatHandle arg1, USlider arg2)
{
	MCI_LIST[1434] = "UTL_SetMpatStartPc";
	START_LAPTIMER(1434);
	UTL_SetMpatStartPc( arg1, arg2);
	STOP_LAPTIMER(1434);
}
void _UTL_SetMpatFileName( MpatHandle arg1, char * arg2)
{
	MCI_LIST[1435] = "UTL_SetMpatFileName";
	START_LAPTIMER(1435);
	UTL_SetMpatFileName( arg1, arg2);
	STOP_LAPTIMER(1435);
}
void _UTL_SendMpat( MpatHandle arg1)
{
	MCI_LIST[1436] = "UTL_SendMpat";
	START_LAPTIMER(1436);
	UTL_SendMpat( arg1);
	STOP_LAPTIMER(1436);
}
TrigHandle _UTL_GetTrigHandle()
{
	MCI_LIST[1437] = "UTL_GetTrigHandle";
	START_LAPTIMER(1437);
	TrigHandle retval = UTL_GetTrigHandle();
	STOP_LAPTIMER(1437);
	return retval;
}
void _UTL_InitializeTrigHandle( TrigHandle arg1)
{
	MCI_LIST[1438] = "UTL_InitializeTrigHandle";
	START_LAPTIMER(1438);
	UTL_InitializeTrigHandle( arg1);
	STOP_LAPTIMER(1438);
}
void _UTL_SetTrigOutputCtrl( TrigHandle arg1, CheckButton arg2)
{
	MCI_LIST[1439] = "UTL_SetTrigOutputCtrl";
	START_LAPTIMER(1439);
	UTL_SetTrigOutputCtrl( arg1, arg2);
	STOP_LAPTIMER(1439);
}
void _UTL_SetTrigStateMode( TrigHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[1440] = "UTL_SetTrigStateMode";
	START_LAPTIMER(1440);
	UTL_SetTrigStateMode( arg1, arg2, arg3);
	STOP_LAPTIMER(1440);
}
void _UTL_SetTrigStateValue( TrigHandle arg1, RadioButton arg2, RadioButton arg3, USlider arg4)
{
	MCI_LIST[1441] = "UTL_SetTrigStateValue";
	START_LAPTIMER(1441);
	UTL_SetTrigStateValue( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1441);
}
void _UTL_SetTrigStrbPhase( TrigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1442] = "UTL_SetTrigStrbPhase";
	START_LAPTIMER(1442);
	UTL_SetTrigStrbPhase( arg1, arg2);
	STOP_LAPTIMER(1442);
}
void _UTL_SetTrigAlpgUnit( TrigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1443] = "UTL_SetTrigAlpgUnit";
	START_LAPTIMER(1443);
	UTL_SetTrigAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1443);
}
void _UTL_SetTrigMode( TrigHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[1444] = "UTL_SetTrigMode";
	START_LAPTIMER(1444);
	UTL_SetTrigMode( arg1, arg2, arg3);
	STOP_LAPTIMER(1444);
}
void _UTL_AddTrigFailDut( TrigHandle arg1, UT_DUT arg2, CheckButton arg3)
{
	MCI_LIST[1445] = "UTL_AddTrigFailDut";
	START_LAPTIMER(1445);
	UTL_AddTrigFailDut( arg1, arg2, arg3);
	STOP_LAPTIMER(1445);
}
void _UTL_SetTrigDirection( TrigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1446] = "UTL_SetTrigDirection";
	START_LAPTIMER(1446);
	UTL_SetTrigDirection( arg1, arg2);
	STOP_LAPTIMER(1446);
}
void _UTL_SendTrig( TrigHandle arg1)
{
	MCI_LIST[1447] = "UTL_SendTrig";
	START_LAPTIMER(1447);
	UTL_SendTrig( arg1);
	STOP_LAPTIMER(1447);
}
void _UTL_ClearTrig()
{
	MCI_LIST[1448] = "UTL_ClearTrig";
	START_LAPTIMER(1448);
	UTL_ClearTrig();
	STOP_LAPTIMER(1448);
}
AlpgCtrlHandle _UTL_GetAlpgCtrlHandle()
{
	MCI_LIST[1449] = "UTL_GetAlpgCtrlHandle";
	START_LAPTIMER(1449);
	AlpgCtrlHandle retval = UTL_GetAlpgCtrlHandle();
	STOP_LAPTIMER(1449);
	return retval;
}
void _UTL_AddAlpgCtrlMode( AlpgCtrlHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[1450] = "UTL_AddAlpgCtrlMode";
	START_LAPTIMER(1450);
	UTL_AddAlpgCtrlMode( arg1, arg2, arg3);
	STOP_LAPTIMER(1450);
}
void _UTL_ClearAlpgCtrlMode( AlpgCtrlHandle arg1)
{
	MCI_LIST[1451] = "UTL_ClearAlpgCtrlMode";
	START_LAPTIMER(1451);
	UTL_ClearAlpgCtrlMode( arg1);
	STOP_LAPTIMER(1451);
}
void _UTL_SendAlpgCtrlMode( AlpgCtrlHandle arg1)
{
	MCI_LIST[1452] = "UTL_SendAlpgCtrlMode";
	START_LAPTIMER(1452);
	UTL_SendAlpgCtrlMode( arg1);
	STOP_LAPTIMER(1452);
}
void _UTL_StartAlpg( RadioButton arg1)
{
	MCI_LIST[1453] = "UTL_StartAlpg";
	START_LAPTIMER(1453);
	UTL_StartAlpg( arg1);
	STOP_LAPTIMER(1453);
}
void _UTL_StopAlpg()
{
	MCI_LIST[1454] = "UTL_StopAlpg";
	START_LAPTIMER(1454);
	UTL_StopAlpg();
	STOP_LAPTIMER(1454);
}
void _UTL_SendFctDataLogCondition()
{
	MCI_LIST[1455] = "UTL_SendFctDataLogCondition";
	START_LAPTIMER(1455);
	UTL_SendFctDataLogCondition();
	STOP_LAPTIMER(1455);
}
void _UTL_PrintFctDataLog()
{
	MCI_LIST[1456] = "UTL_PrintFctDataLog";
	START_LAPTIMER(1456);
	UTL_PrintFctDataLog();
	STOP_LAPTIMER(1456);
}
TmeasHandle _UTL_GetTmeasHandle()
{
	MCI_LIST[1457] = "UTL_GetTmeasHandle";
	START_LAPTIMER(1457);
	TmeasHandle retval = UTL_GetTmeasHandle();
	STOP_LAPTIMER(1457);
	return retval;
}
void _UTL_SetTmeasRange( TmeasHandle arg1, DSlider arg2, DSlider arg3)
{
	MCI_LIST[1458] = "UTL_SetTmeasRange";
	START_LAPTIMER(1458);
	UTL_SetTmeasRange( arg1, arg2, arg3);
	STOP_LAPTIMER(1458);
}
void _UTL_SetTmeasResolution( TmeasHandle arg1, DSlider arg2)
{
	MCI_LIST[1459] = "UTL_SetTmeasResolution";
	START_LAPTIMER(1459);
	UTL_SetTmeasResolution( arg1, arg2);
	STOP_LAPTIMER(1459);
}
void _UTL_SetTmeasUnit( TmeasHandle arg1, RadioButton arg2, RadioButton arg3, RadioButton arg4, RadioButton arg5)
{
	MCI_LIST[1460] = "UTL_SetTmeasUnit";
	START_LAPTIMER(1460);
	UTL_SetTmeasUnit( arg1, arg2, arg3, arg4, arg5);
	STOP_LAPTIMER(1460);
}
void _UTL_SetTmeasMpatName( TmeasHandle arg1, char * arg2)
{
	MCI_LIST[1461] = "UTL_SetTmeasMpatName";
	START_LAPTIMER(1461);
	UTL_SetTmeasMpatName( arg1, arg2);
	STOP_LAPTIMER(1461);
}
void _UTL_SetTmeasStartPc( TmeasHandle arg1, USlider arg2)
{
	MCI_LIST[1462] = "UTL_SetTmeasStartPc";
	START_LAPTIMER(1462);
	UTL_SetTmeasStartPc( arg1, arg2);
	STOP_LAPTIMER(1462);
}
void _UTL_AddTmeasDut( TmeasHandle arg1, UT_DUT arg2)
{
	MCI_LIST[1463] = "UTL_AddTmeasDut";
	START_LAPTIMER(1463);
	UTL_AddTmeasDut( arg1, arg2);
	STOP_LAPTIMER(1463);
}
void _UTL_ClearTmeasDut( TmeasHandle arg1)
{
	MCI_LIST[1464] = "UTL_ClearTmeasDut";
	START_LAPTIMER(1464);
	UTL_ClearTmeasDut( arg1);
	STOP_LAPTIMER(1464);
}
void _UTL_AddTmeasTrackingUnit( TmeasHandle arg1, RadioButton arg2, RadioButton arg3, RadioButton arg4, RadioButton arg5, DSlider arg6)
{
	MCI_LIST[1465] = "UTL_AddTmeasTrackingUnit";
	START_LAPTIMER(1465);
	UTL_AddTmeasTrackingUnit( arg1, arg2, arg3, arg4, arg5, arg6);
	STOP_LAPTIMER(1465);
}
void _UTL_ClearTmeasTrackingUnit( TmeasHandle arg1)
{
	MCI_LIST[1466] = "UTL_ClearTmeasTrackingUnit";
	START_LAPTIMER(1466);
	UTL_ClearTmeasTrackingUnit( arg1);
	STOP_LAPTIMER(1466);
}
int _UTL_Tmeas( TmeasHandle arg1)
{
	MCI_LIST[1467] = "UTL_Tmeas";
	START_LAPTIMER(1467);
	int retval = UTL_Tmeas( arg1);
	STOP_LAPTIMER(1467);
	return retval;
}
int _UTL_GetTmeasResult( TmeasHandle arg1, UT_DUT arg2, DSlider * arg3)
{
	MCI_LIST[1468] = "UTL_GetTmeasResult";
	START_LAPTIMER(1468);
	int retval = UTL_GetTmeasResult( arg1, arg2, arg3);
	STOP_LAPTIMER(1468);
	return retval;
}
VmeasHandle _UTL_GetVmeasHandle()
{
	MCI_LIST[1469] = "UTL_GetVmeasHandle";
	START_LAPTIMER(1469);
	VmeasHandle retval = UTL_GetVmeasHandle();
	STOP_LAPTIMER(1469);
	return retval;
}
void _UTL_SetVmeasRange( VmeasHandle arg1, DSlider arg2, DSlider arg3)
{
	MCI_LIST[1470] = "UTL_SetVmeasRange";
	START_LAPTIMER(1470);
	UTL_SetVmeasRange( arg1, arg2, arg3);
	STOP_LAPTIMER(1470);
}
void _UTL_SetVmeasResolution( VmeasHandle arg1, DSlider arg2)
{
	MCI_LIST[1471] = "UTL_SetVmeasResolution";
	START_LAPTIMER(1471);
	UTL_SetVmeasResolution( arg1, arg2);
	STOP_LAPTIMER(1471);
}
void _UTL_SetVmeasUnit( VmeasHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1472] = "UTL_SetVmeasUnit";
	START_LAPTIMER(1472);
	UTL_SetVmeasUnit( arg1, arg2, arg3);
	STOP_LAPTIMER(1472);
}
void _UTL_SetVmeasMpatName( VmeasHandle arg1, char * arg2)
{
	MCI_LIST[1473] = "UTL_SetVmeasMpatName";
	START_LAPTIMER(1473);
	UTL_SetVmeasMpatName( arg1, arg2);
	STOP_LAPTIMER(1473);
}
void _UTL_SetVmeasStartPc( VmeasHandle arg1, USlider arg2)
{
	MCI_LIST[1474] = "UTL_SetVmeasStartPc";
	START_LAPTIMER(1474);
	UTL_SetVmeasStartPc( arg1, arg2);
	STOP_LAPTIMER(1474);
}
void _UTL_SetVmeasWaitTime( VmeasHandle arg1, DSlider arg2)
{
	MCI_LIST[1475] = "UTL_SetVmeasWaitTime";
	START_LAPTIMER(1475);
	UTL_SetVmeasWaitTime( arg1, arg2);
	STOP_LAPTIMER(1475);
}
void _UTL_SetVmeasWaitInhibit( VmeasHandle arg1, CheckButton arg2)
{
	MCI_LIST[1476] = "UTL_SetVmeasWaitInhibit";
	START_LAPTIMER(1476);
	UTL_SetVmeasWaitInhibit( arg1, arg2);
	STOP_LAPTIMER(1476);
}
void _UTL_AddVmeasDut( VmeasHandle arg1, UT_DUT arg2)
{
	MCI_LIST[1477] = "UTL_AddVmeasDut";
	START_LAPTIMER(1477);
	UTL_AddVmeasDut( arg1, arg2);
	STOP_LAPTIMER(1477);
}
void _UTL_ClearVmeasDut( VmeasHandle arg1)
{
	MCI_LIST[1478] = "UTL_ClearVmeasDut";
	START_LAPTIMER(1478);
	UTL_ClearVmeasDut( arg1);
	STOP_LAPTIMER(1478);
}
void _UTL_AddVmeasTrackingUnit( VmeasHandle arg1, RadioButton arg2, RadioButton arg3, DSlider arg4)
{
	MCI_LIST[1479] = "UTL_AddVmeasTrackingUnit";
	START_LAPTIMER(1479);
	UTL_AddVmeasTrackingUnit( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1479);
}
void _UTL_ClearVmeasTrackingUnit( VmeasHandle arg1)
{
	MCI_LIST[1480] = "UTL_ClearVmeasTrackingUnit";
	START_LAPTIMER(1480);
	UTL_ClearVmeasTrackingUnit( arg1);
	STOP_LAPTIMER(1480);
}
int _UTL_Vmeas( VmeasHandle arg1)
{
	MCI_LIST[1481] = "UTL_Vmeas";
	START_LAPTIMER(1481);
	int retval = UTL_Vmeas( arg1);
	STOP_LAPTIMER(1481);
	return retval;
}
int _UTL_GetVmeasResult( VmeasHandle arg1, UT_DUT arg2, DSlider * arg3)
{
	MCI_LIST[1482] = "UTL_GetVmeasResult";
	START_LAPTIMER(1482);
	int retval = UTL_GetVmeasResult( arg1, arg2, arg3);
	STOP_LAPTIMER(1482);
	return retval;
}
HidarConfigHandle _UTL_GetHidarConfigHandle()
{
	MCI_LIST[1483] = "UTL_GetHidarConfigHandle";
	START_LAPTIMER(1483);
	HidarConfigHandle retval = UTL_GetHidarConfigHandle();
	STOP_LAPTIMER(1483);
	return retval;
}
void _UTL_SetHidarConfigProgramName( HidarConfigHandle  arg1, char * arg2)
{
	MCI_LIST[1484] = "UTL_SetHidarConfigProgramName";
	START_LAPTIMER(1484);
	UTL_SetHidarConfigProgramName( arg1, arg2);
	STOP_LAPTIMER(1484);
}
void _UTL_SetHidarConfigType( HidarConfigHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[1485] = "UTL_SetHidarConfigType";
	START_LAPTIMER(1485);
	UTL_SetHidarConfigType( arg1, arg2);
	STOP_LAPTIMER(1485);
}
void _UTL_SetHidarConfigItem( HidarConfigHandle  arg1, char * arg2)
{
	MCI_LIST[1486] = "UTL_SetHidarConfigItem";
	START_LAPTIMER(1486);
	UTL_SetHidarConfigItem( arg1, arg2);
	STOP_LAPTIMER(1486);
}
void _UTL_SetHidarConfigStartTestNumber( HidarConfigHandle  arg1, Slider  arg2)
{
	MCI_LIST[1487] = "UTL_SetHidarConfigStartTestNumber";
	START_LAPTIMER(1487);
	UTL_SetHidarConfigStartTestNumber( arg1, arg2);
	STOP_LAPTIMER(1487);
}
void _UTL_SetHidarConfigStopTestNumber( HidarConfigHandle  arg1, Slider  arg2)
{
	MCI_LIST[1488] = "UTL_SetHidarConfigStopTestNumber";
	START_LAPTIMER(1488);
	UTL_SetHidarConfigStopTestNumber( arg1, arg2);
	STOP_LAPTIMER(1488);
}
void _UTL_AddHidarConfigTestName( HidarConfigHandle  arg1, char * arg2)
{
	MCI_LIST[1489] = "UTL_AddHidarConfigTestName";
	START_LAPTIMER(1489);
	UTL_AddHidarConfigTestName( arg1, arg2);
	STOP_LAPTIMER(1489);
}
void _UTL_ClearHidarConfigTestName( HidarConfigHandle  arg1)
{
	MCI_LIST[1490] = "UTL_ClearHidarConfigTestName";
	START_LAPTIMER(1490);
	UTL_ClearHidarConfigTestName( arg1);
	STOP_LAPTIMER(1490);
}
void _UTL_SetHidarConfigTestNamePattern( HidarConfigHandle  arg1, char * arg2)
{
	MCI_LIST[1491] = "UTL_SetHidarConfigTestNamePattern";
	START_LAPTIMER(1491);
	UTL_SetHidarConfigTestNamePattern( arg1, arg2);
	STOP_LAPTIMER(1491);
}
void _UTL_SetHidarConfigRangeMode( HidarConfigHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[1492] = "UTL_SetHidarConfigRangeMode";
	START_LAPTIMER(1492);
	UTL_SetHidarConfigRangeMode( arg1, arg2);
	STOP_LAPTIMER(1492);
}
void _UTL_SetHidarConfigCellNumber( HidarConfigHandle  arg1, Slider  arg2)
{
	MCI_LIST[1493] = "UTL_SetHidarConfigCellNumber";
	START_LAPTIMER(1493);
	UTL_SetHidarConfigCellNumber( arg1, arg2);
	STOP_LAPTIMER(1493);
}
void _UTL_SetHidarConfigCellResolutionMin( HidarConfigHandle  arg1, DSlider  arg2)
{
	MCI_LIST[1494] = "UTL_SetHidarConfigCellResolutionMin";
	START_LAPTIMER(1494);
	UTL_SetHidarConfigCellResolutionMin( arg1, arg2);
	STOP_LAPTIMER(1494);
}
void _UTL_SetHidarConfigCollectionRangeMax( HidarConfigHandle  arg1, DSlider  arg2)
{
	MCI_LIST[1495] = "UTL_SetHidarConfigCollectionRangeMax";
	START_LAPTIMER(1495);
	UTL_SetHidarConfigCollectionRangeMax( arg1, arg2);
	STOP_LAPTIMER(1495);
}
void _UTL_SetHidarConfigCollectionRangeMin( HidarConfigHandle  arg1, DSlider  arg2)
{
	MCI_LIST[1496] = "UTL_SetHidarConfigCollectionRangeMin";
	START_LAPTIMER(1496);
	UTL_SetHidarConfigCollectionRangeMin( arg1, arg2);
	STOP_LAPTIMER(1496);
}
void _UTL_SetHidarConfigStatisticRangeMax( HidarConfigHandle  arg1, DSlider  arg2)
{
	MCI_LIST[1497] = "UTL_SetHidarConfigStatisticRangeMax";
	START_LAPTIMER(1497);
	UTL_SetHidarConfigStatisticRangeMax( arg1, arg2);
	STOP_LAPTIMER(1497);
}
void _UTL_SetHidarConfigStatisticRangeMin( HidarConfigHandle  arg1, DSlider  arg2)
{
	MCI_LIST[1498] = "UTL_SetHidarConfigStatisticRangeMin";
	START_LAPTIMER(1498);
	UTL_SetHidarConfigStatisticRangeMin( arg1, arg2);
	STOP_LAPTIMER(1498);
}
int _UTL_GetHidarConfigProgramName( HidarConfigHandle  arg1, char ** arg2)
{
	MCI_LIST[1499] = "UTL_GetHidarConfigProgramName";
	START_LAPTIMER(1499);
	int retval = UTL_GetHidarConfigProgramName( arg1, arg2);
	STOP_LAPTIMER(1499);
	return retval;
}
int _UTL_GetHidarConfigType( HidarConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1500] = "UTL_GetHidarConfigType";
	START_LAPTIMER(1500);
	int retval = UTL_GetHidarConfigType( arg1, arg2);
	STOP_LAPTIMER(1500);
	return retval;
}
int _UTL_GetHidarConfigItem( HidarConfigHandle  arg1, char ** arg2)
{
	MCI_LIST[1501] = "UTL_GetHidarConfigItem";
	START_LAPTIMER(1501);
	int retval = UTL_GetHidarConfigItem( arg1, arg2);
	STOP_LAPTIMER(1501);
	return retval;
}
int _UTL_GetHidarConfigStartTestNumber( HidarConfigHandle  arg1, Slider * arg2)
{
	MCI_LIST[1502] = "UTL_GetHidarConfigStartTestNumber";
	START_LAPTIMER(1502);
	int retval = UTL_GetHidarConfigStartTestNumber( arg1, arg2);
	STOP_LAPTIMER(1502);
	return retval;
}
int _UTL_GetHidarConfigStopTestNumber( HidarConfigHandle  arg1, Slider * arg2)
{
	MCI_LIST[1503] = "UTL_GetHidarConfigStopTestNumber";
	START_LAPTIMER(1503);
	int retval = UTL_GetHidarConfigStopTestNumber( arg1, arg2);
	STOP_LAPTIMER(1503);
	return retval;
}
int _UTL_GetHidarConfigNumberOfTestNames( HidarConfigHandle  arg1, Slider * arg2)
{
	MCI_LIST[1504] = "UTL_GetHidarConfigNumberOfTestNames";
	START_LAPTIMER(1504);
	int retval = UTL_GetHidarConfigNumberOfTestNames( arg1, arg2);
	STOP_LAPTIMER(1504);
	return retval;
}
int _UTL_GetHidarConfigTestName( HidarConfigHandle  arg1, RadioButton  arg2, char ** arg3)
{
	MCI_LIST[1505] = "UTL_GetHidarConfigTestName";
	START_LAPTIMER(1505);
	int retval = UTL_GetHidarConfigTestName( arg1, arg2, arg3);
	STOP_LAPTIMER(1505);
	return retval;
}
int _UTL_GetHidarConfigTestNamePattern( HidarConfigHandle  arg1, char ** arg2)
{
	MCI_LIST[1506] = "UTL_GetHidarConfigTestNamePattern";
	START_LAPTIMER(1506);
	int retval = UTL_GetHidarConfigTestNamePattern( arg1, arg2);
	STOP_LAPTIMER(1506);
	return retval;
}
int _UTL_GetHidarConfigRangeMode( HidarConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1507] = "UTL_GetHidarConfigRangeMode";
	START_LAPTIMER(1507);
	int retval = UTL_GetHidarConfigRangeMode( arg1, arg2);
	STOP_LAPTIMER(1507);
	return retval;
}
int _UTL_GetHidarConfigCellNumber( HidarConfigHandle  arg1, Slider * arg2)
{
	MCI_LIST[1508] = "UTL_GetHidarConfigCellNumber";
	START_LAPTIMER(1508);
	int retval = UTL_GetHidarConfigCellNumber( arg1, arg2);
	STOP_LAPTIMER(1508);
	return retval;
}
int _UTL_GetHidarConfigCellResolutionMin( HidarConfigHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1509] = "UTL_GetHidarConfigCellResolutionMin";
	START_LAPTIMER(1509);
	int retval = UTL_GetHidarConfigCellResolutionMin( arg1, arg2);
	STOP_LAPTIMER(1509);
	return retval;
}
int _UTL_GetHidarConfigCollectionRangeMax( HidarConfigHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1510] = "UTL_GetHidarConfigCollectionRangeMax";
	START_LAPTIMER(1510);
	int retval = UTL_GetHidarConfigCollectionRangeMax( arg1, arg2);
	STOP_LAPTIMER(1510);
	return retval;
}
int _UTL_GetHidarConfigCollectionRangeMin( HidarConfigHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1511] = "UTL_GetHidarConfigCollectionRangeMin";
	START_LAPTIMER(1511);
	int retval = UTL_GetHidarConfigCollectionRangeMin( arg1, arg2);
	STOP_LAPTIMER(1511);
	return retval;
}
int _UTL_GetHidarConfigStatisticRangeMax( HidarConfigHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1512] = "UTL_GetHidarConfigStatisticRangeMax";
	START_LAPTIMER(1512);
	int retval = UTL_GetHidarConfigStatisticRangeMax( arg1, arg2);
	STOP_LAPTIMER(1512);
	return retval;
}
int _UTL_GetHidarConfigStatisticRangeMin( HidarConfigHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1513] = "UTL_GetHidarConfigStatisticRangeMin";
	START_LAPTIMER(1513);
	int retval = UTL_GetHidarConfigStatisticRangeMin( arg1, arg2);
	STOP_LAPTIMER(1513);
	return retval;
}
HidarConfigListHandle _UTL_GetHidarConfigListHandle( RadioButton  arg1)
{
	MCI_LIST[1514] = "UTL_GetHidarConfigListHandle";
	START_LAPTIMER(1514);
	HidarConfigListHandle retval = UTL_GetHidarConfigListHandle( arg1);
	STOP_LAPTIMER(1514);
	return retval;
}
HidarConfigListHandle _UTL_GetHidarConfigListTargetStationHandle( RadioButton arg1, RadioButton arg2)
{
	MCI_LIST[1515] = "UTL_GetHidarConfigListTargetStationHandle";
	START_LAPTIMER(1515);
	HidarConfigListHandle retval = UTL_GetHidarConfigListTargetStationHandle( arg1, arg2);
	STOP_LAPTIMER(1515);
	return retval;
}
void _UTL_AppendHidarConfigList( HidarConfigListHandle arg1, HidarConfigHandle arg2)
{
	MCI_LIST[1516] = "UTL_AppendHidarConfigList";
	START_LAPTIMER(1516);
	UTL_AppendHidarConfigList( arg1, arg2);
	STOP_LAPTIMER(1516);
}
int _UTL_GetHidarConfigListCount( HidarConfigListHandle arg1, Slider * arg2)
{
	MCI_LIST[1517] = "UTL_GetHidarConfigListCount";
	START_LAPTIMER(1517);
	int retval = UTL_GetHidarConfigListCount( arg1, arg2);
	STOP_LAPTIMER(1517);
	return retval;
}
int _UTL_GetHidarConfigListIndex( HidarConfigListHandle arg1, RadioButton arg2, HidarConfigHandle * arg3)
{
	MCI_LIST[1518] = "UTL_GetHidarConfigListIndex";
	START_LAPTIMER(1518);
	int retval = UTL_GetHidarConfigListIndex( arg1, arg2, arg3);
	STOP_LAPTIMER(1518);
	return retval;
}
int _UTL_DeleteHidarConfigList( HidarConfigListHandle arg1, RadioButton arg2)
{
	MCI_LIST[1519] = "UTL_DeleteHidarConfigList";
	START_LAPTIMER(1519);
	int retval = UTL_DeleteHidarConfigList( arg1, arg2);
	STOP_LAPTIMER(1519);
	return retval;
}
HidarAccessHandle _UTL_GetHidarAccessHandle()
{
	MCI_LIST[1520] = "UTL_GetHidarAccessHandle";
	START_LAPTIMER(1520);
	HidarAccessHandle retval = UTL_GetHidarAccessHandle();
	STOP_LAPTIMER(1520);
	return retval;
}
void _UTL_SetHidarAccessStationNumber( HidarAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[1521] = "UTL_SetHidarAccessStationNumber";
	START_LAPTIMER(1521);
	UTL_SetHidarAccessStationNumber( arg1, arg2);
	STOP_LAPTIMER(1521);
}
void _UTL_SetHidarAccessSiteNumber( HidarAccessHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[1522] = "UTL_SetHidarAccessSiteNumber";
	START_LAPTIMER(1522);
	UTL_SetHidarAccessSiteNumber( arg1, arg2);
	STOP_LAPTIMER(1522);
}
void _UTL_AddHidarAccessTestName( HidarAccessHandle  arg1, char * arg2)
{
	MCI_LIST[1523] = "UTL_AddHidarAccessTestName";
	START_LAPTIMER(1523);
	UTL_AddHidarAccessTestName( arg1, arg2);
	STOP_LAPTIMER(1523);
}
void _UTL_SetHidarAccessTestCount( HidarAccessHandle  arg1, Slider  arg2)
{
	MCI_LIST[1524] = "UTL_SetHidarAccessTestCount";
	START_LAPTIMER(1524);
	UTL_SetHidarAccessTestCount( arg1, arg2);
	STOP_LAPTIMER(1524);
}
void _UTL_SetHidarAccessErrTestCount( HidarAccessHandle  arg1, Slider  arg2)
{
	MCI_LIST[1525] = "UTL_SetHidarAccessErrTestCount";
	START_LAPTIMER(1525);
	UTL_SetHidarAccessErrTestCount( arg1, arg2);
	STOP_LAPTIMER(1525);
}
void _UTL_SetHidarAccessFailCountLow( HidarAccessHandle  arg1, Slider  arg2)
{
	MCI_LIST[1526] = "UTL_SetHidarAccessFailCountLow";
	START_LAPTIMER(1526);
	UTL_SetHidarAccessFailCountLow( arg1, arg2);
	STOP_LAPTIMER(1526);
}
void _UTL_SetHidarAccessFailCountHigh( HidarAccessHandle  arg1, Slider  arg2)
{
	MCI_LIST[1527] = "UTL_SetHidarAccessFailCountHigh";
	START_LAPTIMER(1527);
	UTL_SetHidarAccessFailCountHigh( arg1, arg2);
	STOP_LAPTIMER(1527);
}
void _UTL_SetHidarAccessOverCountLow( HidarAccessHandle  arg1, Slider  arg2)
{
	MCI_LIST[1528] = "UTL_SetHidarAccessOverCountLow";
	START_LAPTIMER(1528);
	UTL_SetHidarAccessOverCountLow( arg1, arg2);
	STOP_LAPTIMER(1528);
}
void _UTL_SetHidarAccessOverCountHigh( HidarAccessHandle  arg1, Slider  arg2)
{
	MCI_LIST[1529] = "UTL_SetHidarAccessOverCountHigh";
	START_LAPTIMER(1529);
	UTL_SetHidarAccessOverCountHigh( arg1, arg2);
	STOP_LAPTIMER(1529);
}
void _UTL_SetHidarAccessLimitLow( HidarAccessHandle  arg1, DSlider  arg2, CheckButton  arg3)
{
	MCI_LIST[1530] = "UTL_SetHidarAccessLimitLow";
	START_LAPTIMER(1530);
	UTL_SetHidarAccessLimitLow( arg1, arg2, arg3);
	STOP_LAPTIMER(1530);
}
void _UTL_SetHidarAccessLimitHigh( HidarAccessHandle  arg1, DSlider  arg2, CheckButton  arg3)
{
	MCI_LIST[1531] = "UTL_SetHidarAccessLimitHigh";
	START_LAPTIMER(1531);
	UTL_SetHidarAccessLimitHigh( arg1, arg2, arg3);
	STOP_LAPTIMER(1531);
}
void _UTL_SetHidarAccessDataMin( HidarAccessHandle  arg1, DSlider  arg2)
{
	MCI_LIST[1532] = "UTL_SetHidarAccessDataMin";
	START_LAPTIMER(1532);
	UTL_SetHidarAccessDataMin( arg1, arg2);
	STOP_LAPTIMER(1532);
}
void _UTL_SetHidarAccessDataMax( HidarAccessHandle  arg1, DSlider  arg2)
{
	MCI_LIST[1533] = "UTL_SetHidarAccessDataMax";
	START_LAPTIMER(1533);
	UTL_SetHidarAccessDataMax( arg1, arg2);
	STOP_LAPTIMER(1533);
}
void _UTL_SetHidarAccessAddVal( HidarAccessHandle  arg1, DSlider  arg2)
{
	MCI_LIST[1534] = "UTL_SetHidarAccessAddVal";
	START_LAPTIMER(1534);
	UTL_SetHidarAccessAddVal( arg1, arg2);
	STOP_LAPTIMER(1534);
}
void _UTL_SetHidarAccessSquareSum( HidarAccessHandle  arg1, DSlider  arg2)
{
	MCI_LIST[1535] = "UTL_SetHidarAccessSquareSum";
	START_LAPTIMER(1535);
	UTL_SetHidarAccessSquareSum( arg1, arg2);
	STOP_LAPTIMER(1535);
}
void _UTL_SetHidarAccessRankMin( HidarAccessHandle  arg1, DSlider  arg2)
{
	MCI_LIST[1536] = "UTL_SetHidarAccessRankMin";
	START_LAPTIMER(1536);
	UTL_SetHidarAccessRankMin( arg1, arg2);
	STOP_LAPTIMER(1536);
}
void _UTL_SetHidarAccessRankMax( HidarAccessHandle  arg1, DSlider  arg2)
{
	MCI_LIST[1537] = "UTL_SetHidarAccessRankMax";
	START_LAPTIMER(1537);
	UTL_SetHidarAccessRankMax( arg1, arg2);
	STOP_LAPTIMER(1537);
}
void _UTL_SetHidarAccessRankResolution( HidarAccessHandle  arg1, DSlider  arg2)
{
	MCI_LIST[1538] = "UTL_SetHidarAccessRankResolution";
	START_LAPTIMER(1538);
	UTL_SetHidarAccessRankResolution( arg1, arg2);
	STOP_LAPTIMER(1538);
}
void _UTL_SetHidarAccessRankPassCount( HidarAccessHandle  arg1, RadioButton  arg2, Slider  arg3)
{
	MCI_LIST[1539] = "UTL_SetHidarAccessRankPassCount";
	START_LAPTIMER(1539);
	UTL_SetHidarAccessRankPassCount( arg1, arg2, arg3);
	STOP_LAPTIMER(1539);
}
void _UTL_SetHidarAccessRankFailCount( HidarAccessHandle  arg1, RadioButton  arg2, Slider  arg3)
{
	MCI_LIST[1540] = "UTL_SetHidarAccessRankFailCount";
	START_LAPTIMER(1540);
	UTL_SetHidarAccessRankFailCount( arg1, arg2, arg3);
	STOP_LAPTIMER(1540);
}
void _UTL_AddHidarAccessOverData( HidarAccessHandle  arg1, DSlider  arg2, RadioButton  arg3)
{
	MCI_LIST[1541] = "UTL_AddHidarAccessOverData";
	START_LAPTIMER(1541);
	UTL_AddHidarAccessOverData( arg1, arg2, arg3);
	STOP_LAPTIMER(1541);
}
void _UTL_SendHidarData( HidarAccessHandle  arg1, HidarConfigHandle  arg2)
{
	MCI_LIST[1542] = "UTL_SendHidarData";
	START_LAPTIMER(1542);
	UTL_SendHidarData( arg1, arg2);
	STOP_LAPTIMER(1542);
}
void _UTL_ReconstructHidarData( HidarAccessHandle  arg1, HidarConfigHandle  arg2)
{
	MCI_LIST[1543] = "UTL_ReconstructHidarData";
	START_LAPTIMER(1543);
	UTL_ReconstructHidarData( arg1, arg2);
	STOP_LAPTIMER(1543);
}
HidarAccessHandle _UTL_MergeHidar( HidarConfigHandle  arg1, RadioButtonList  arg2)
{
	MCI_LIST[1544] = "UTL_MergeHidar";
	START_LAPTIMER(1544);
	HidarAccessHandle retval = UTL_MergeHidar( arg1, arg2);
	STOP_LAPTIMER(1544);
	return retval;
}
void _UTL_UpdateHidarData( HidarAccessHandle  arg1, HidarConfigHandle  arg2)
{
	MCI_LIST[1545] = "UTL_UpdateHidarData";
	START_LAPTIMER(1545);
	UTL_UpdateHidarData( arg1, arg2);
	STOP_LAPTIMER(1545);
}
int _UTL_GetHidarAccessTestNameCount( HidarAccessHandle  arg1, Slider * arg2)
{
	MCI_LIST[1546] = "UTL_GetHidarAccessTestNameCount";
	START_LAPTIMER(1546);
	int retval = UTL_GetHidarAccessTestNameCount( arg1, arg2);
	STOP_LAPTIMER(1546);
	return retval;
}
int _UTL_GetHidarAccessTestName( HidarAccessHandle  arg1, RadioButton  arg2, char ** arg3)
{
	MCI_LIST[1547] = "UTL_GetHidarAccessTestName";
	START_LAPTIMER(1547);
	int retval = UTL_GetHidarAccessTestName( arg1, arg2, arg3);
	STOP_LAPTIMER(1547);
	return retval;
}
int _UTL_GetHidarAccessTestCount( HidarAccessHandle  arg1, Slider * arg2)
{
	MCI_LIST[1548] = "UTL_GetHidarAccessTestCount";
	START_LAPTIMER(1548);
	int retval = UTL_GetHidarAccessTestCount( arg1, arg2);
	STOP_LAPTIMER(1548);
	return retval;
}
int _UTL_GetHidarAccessErrTestCount( HidarAccessHandle  arg1, Slider * arg2)
{
	MCI_LIST[1549] = "UTL_GetHidarAccessErrTestCount";
	START_LAPTIMER(1549);
	int retval = UTL_GetHidarAccessErrTestCount( arg1, arg2);
	STOP_LAPTIMER(1549);
	return retval;
}
int _UTL_GetHidarAccessFailCountLow( HidarAccessHandle  arg1, Slider * arg2)
{
	MCI_LIST[1550] = "UTL_GetHidarAccessFailCountLow";
	START_LAPTIMER(1550);
	int retval = UTL_GetHidarAccessFailCountLow( arg1, arg2);
	STOP_LAPTIMER(1550);
	return retval;
}
int _UTL_GetHidarAccessFailCountHigh( HidarAccessHandle  arg1, Slider * arg2)
{
	MCI_LIST[1551] = "UTL_GetHidarAccessFailCountHigh";
	START_LAPTIMER(1551);
	int retval = UTL_GetHidarAccessFailCountHigh( arg1, arg2);
	STOP_LAPTIMER(1551);
	return retval;
}
int _UTL_GetHidarAccessOverCountLow( HidarAccessHandle  arg1, Slider * arg2)
{
	MCI_LIST[1552] = "UTL_GetHidarAccessOverCountLow";
	START_LAPTIMER(1552);
	int retval = UTL_GetHidarAccessOverCountLow( arg1, arg2);
	STOP_LAPTIMER(1552);
	return retval;
}
int _UTL_GetHidarAccessOverCountHigh( HidarAccessHandle  arg1, Slider * arg2)
{
	MCI_LIST[1553] = "UTL_GetHidarAccessOverCountHigh";
	START_LAPTIMER(1553);
	int retval = UTL_GetHidarAccessOverCountHigh( arg1, arg2);
	STOP_LAPTIMER(1553);
	return retval;
}
int _UTL_GetHidarAccessLimitLow( HidarAccessHandle  arg1, DSlider * arg2, CheckButton * arg3)
{
	MCI_LIST[1554] = "UTL_GetHidarAccessLimitLow";
	START_LAPTIMER(1554);
	int retval = UTL_GetHidarAccessLimitLow( arg1, arg2, arg3);
	STOP_LAPTIMER(1554);
	return retval;
}
int _UTL_GetHidarAccessLimitHigh( HidarAccessHandle  arg1, DSlider * arg2, CheckButton * arg3)
{
	MCI_LIST[1555] = "UTL_GetHidarAccessLimitHigh";
	START_LAPTIMER(1555);
	int retval = UTL_GetHidarAccessLimitHigh( arg1, arg2, arg3);
	STOP_LAPTIMER(1555);
	return retval;
}
int _UTL_GetHidarAccessDataMin( HidarAccessHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1556] = "UTL_GetHidarAccessDataMin";
	START_LAPTIMER(1556);
	int retval = UTL_GetHidarAccessDataMin( arg1, arg2);
	STOP_LAPTIMER(1556);
	return retval;
}
int _UTL_GetHidarAccessDataMax( HidarAccessHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1557] = "UTL_GetHidarAccessDataMax";
	START_LAPTIMER(1557);
	int retval = UTL_GetHidarAccessDataMax( arg1, arg2);
	STOP_LAPTIMER(1557);
	return retval;
}
int _UTL_GetHidarAccessAddVal( HidarAccessHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1558] = "UTL_GetHidarAccessAddVal";
	START_LAPTIMER(1558);
	int retval = UTL_GetHidarAccessAddVal( arg1, arg2);
	STOP_LAPTIMER(1558);
	return retval;
}
int _UTL_GetHidarAccessSquareSum( HidarAccessHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1559] = "UTL_GetHidarAccessSquareSum";
	START_LAPTIMER(1559);
	int retval = UTL_GetHidarAccessSquareSum( arg1, arg2);
	STOP_LAPTIMER(1559);
	return retval;
}
int _UTL_GetHidarAccessRankMin( HidarAccessHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1560] = "UTL_GetHidarAccessRankMin";
	START_LAPTIMER(1560);
	int retval = UTL_GetHidarAccessRankMin( arg1, arg2);
	STOP_LAPTIMER(1560);
	return retval;
}
int _UTL_GetHidarAccessRankMax( HidarAccessHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1561] = "UTL_GetHidarAccessRankMax";
	START_LAPTIMER(1561);
	int retval = UTL_GetHidarAccessRankMax( arg1, arg2);
	STOP_LAPTIMER(1561);
	return retval;
}
int _UTL_GetHidarAccessRankNumber( HidarAccessHandle  arg1, Slider * arg2)
{
	MCI_LIST[1562] = "UTL_GetHidarAccessRankNumber";
	START_LAPTIMER(1562);
	int retval = UTL_GetHidarAccessRankNumber( arg1, arg2);
	STOP_LAPTIMER(1562);
	return retval;
}
int _UTL_GetHidarAccessRankResolution( HidarAccessHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1563] = "UTL_GetHidarAccessRankResolution";
	START_LAPTIMER(1563);
	int retval = UTL_GetHidarAccessRankResolution( arg1, arg2);
	STOP_LAPTIMER(1563);
	return retval;
}
int _UTL_GetHidarAccessRankPassCount( HidarAccessHandle  arg1, RadioButton  arg2, Slider * arg3)
{
	MCI_LIST[1564] = "UTL_GetHidarAccessRankPassCount";
	START_LAPTIMER(1564);
	int retval = UTL_GetHidarAccessRankPassCount( arg1, arg2, arg3);
	STOP_LAPTIMER(1564);
	return retval;
}
int _UTL_GetHidarAccessRankFailCount( HidarAccessHandle  arg1, RadioButton  arg2, Slider * arg3)
{
	MCI_LIST[1565] = "UTL_GetHidarAccessRankFailCount";
	START_LAPTIMER(1565);
	int retval = UTL_GetHidarAccessRankFailCount( arg1, arg2, arg3);
	STOP_LAPTIMER(1565);
	return retval;
}
int _UTL_GetHidarAccessOverDataCount( HidarAccessHandle  arg1, Slider * arg2)
{
	MCI_LIST[1566] = "UTL_GetHidarAccessOverDataCount";
	START_LAPTIMER(1566);
	int retval = UTL_GetHidarAccessOverDataCount( arg1, arg2);
	STOP_LAPTIMER(1566);
	return retval;
}
int _UTL_GetHidarAccessOverData( HidarAccessHandle  arg1, RadioButton  arg2, DSlider * arg3, RadioButton * arg4)
{
	MCI_LIST[1567] = "UTL_GetHidarAccessOverData";
	START_LAPTIMER(1567);
	int retval = UTL_GetHidarAccessOverData( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1567);
	return retval;
}
HidarConstructHandle _UTL_GetHidarConstructHandle()
{
	MCI_LIST[1568] = "UTL_GetHidarConstructHandle";
	START_LAPTIMER(1568);
	HidarConstructHandle retval = UTL_GetHidarConstructHandle();
	STOP_LAPTIMER(1568);
	return retval;
}
void _UTL_SetHidarConstructStationNumber( HidarConstructHandle arg1, RadioButton arg2)
{
	MCI_LIST[1569] = "UTL_SetHidarConstructStationNumber";
	START_LAPTIMER(1569);
	UTL_SetHidarConstructStationNumber( arg1, arg2);
	STOP_LAPTIMER(1569);
}
void _UTL_SetHidarConstructConfigHandle( HidarConstructHandle arg1, HidarConfigHandle arg2)
{
	MCI_LIST[1570] = "UTL_SetHidarConstructConfigHandle";
	START_LAPTIMER(1570);
	UTL_SetHidarConstructConfigHandle( arg1, arg2);
	STOP_LAPTIMER(1570);
}
void _UTL_SetHidarConstructMeasMode( HidarConstructHandle arg1, RadioButton arg2)
{
	MCI_LIST[1571] = "UTL_SetHidarConstructMeasMode";
	START_LAPTIMER(1571);
	UTL_SetHidarConstructMeasMode( arg1, arg2);
	STOP_LAPTIMER(1571);
}
void _UTL_SetHidarConstructPin( HidarConstructHandle arg1, UT_PIN arg2)
{
	MCI_LIST[1572] = "UTL_SetHidarConstructPin";
	START_LAPTIMER(1572);
	UTL_SetHidarConstructPin( arg1, arg2);
	STOP_LAPTIMER(1572);
}
void _UTL_SetHidarConstructDut( HidarConstructHandle arg1, UT_DUT arg2)
{
	MCI_LIST[1573] = "UTL_SetHidarConstructDut";
	START_LAPTIMER(1573);
	UTL_SetHidarConstructDut( arg1, arg2);
	STOP_LAPTIMER(1573);
}
void _UTL_AddHidarConstructData( HidarConstructHandle arg1, HidarJudgeDataHandle arg2)
{
	MCI_LIST[1574] = "UTL_AddHidarConstructData";
	START_LAPTIMER(1574);
	UTL_AddHidarConstructData( arg1, arg2);
	STOP_LAPTIMER(1574);
}
HidarConstructDataCursor _UTL_GetHidarConstructDataCursor( HidarConstructHandle arg1)
{
	MCI_LIST[1575] = "UTL_GetHidarConstructDataCursor";
	START_LAPTIMER(1575);
	HidarConstructDataCursor retval = UTL_GetHidarConstructDataCursor( arg1);
	STOP_LAPTIMER(1575);
	return retval;
}
HidarJudgeDataHandle _UTL_NextHidarConstructData( HidarConstructDataCursor arg1)
{
	MCI_LIST[1576] = "UTL_NextHidarConstructData";
	START_LAPTIMER(1576);
	HidarJudgeDataHandle retval = UTL_NextHidarConstructData( arg1);
	STOP_LAPTIMER(1576);
	return retval;
}
void _UTL_ClearHidarConstructData( HidarConstructHandle arg1)
{
	MCI_LIST[1577] = "UTL_ClearHidarConstructData";
	START_LAPTIMER(1577);
	UTL_ClearHidarConstructData( arg1);
	STOP_LAPTIMER(1577);
}
void _UTL_ConstructHidar( HidarConstructHandle arg1)
{
	MCI_LIST[1578] = "UTL_ConstructHidar";
	START_LAPTIMER(1578);
	UTL_ConstructHidar( arg1);
	STOP_LAPTIMER(1578);
}
HidarJudgeDataHandle _UTL_GetHidarJudgeDataHandle()
{
	MCI_LIST[1579] = "UTL_GetHidarJudgeDataHandle";
	START_LAPTIMER(1579);
	HidarJudgeDataHandle retval = UTL_GetHidarJudgeDataHandle();
	STOP_LAPTIMER(1579);
	return retval;
}
void _UTL_SetHidarJudgeData( HidarJudgeDataHandle arg1, DSlider arg2)
{
	MCI_LIST[1580] = "UTL_SetHidarJudgeData";
	START_LAPTIMER(1580);
	UTL_SetHidarJudgeData( arg1, arg2);
	STOP_LAPTIMER(1580);
}
void _UTL_SetHidarJudgeDataHighFail( HidarJudgeDataHandle arg1, CheckButton arg2)
{
	MCI_LIST[1581] = "UTL_SetHidarJudgeDataHighFail";
	START_LAPTIMER(1581);
	UTL_SetHidarJudgeDataHighFail( arg1, arg2);
	STOP_LAPTIMER(1581);
}
void _UTL_SetHidarJudgeDataLowFail( HidarJudgeDataHandle arg1, CheckButton arg2)
{
	MCI_LIST[1582] = "UTL_SetHidarJudgeDataLowFail";
	START_LAPTIMER(1582);
	UTL_SetHidarJudgeDataLowFail( arg1, arg2);
	STOP_LAPTIMER(1582);
}
void _UTL_UpdateAdc( AdcHandle arg1, RadioButton arg2)
{
	MCI_LIST[1583] = "UTL_UpdateAdc";
	START_LAPTIMER(1583);
	UTL_UpdateAdc( arg1, arg2);
	STOP_LAPTIMER(1583);
}
int _UTL_GetAdcInput( AdcHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1584] = "UTL_GetAdcInput";
	START_LAPTIMER(1584);
	int retval = UTL_GetAdcInput( arg1, arg2);
	STOP_LAPTIMER(1584);
	return retval;
}
int _UTL_GetAdcPinList( AdcHandle  arg1, char **  arg2)
{
	MCI_LIST[1585] = "UTL_GetAdcPinList";
	START_LAPTIMER(1585);
	int retval = UTL_GetAdcPinList( arg1, arg2);
	STOP_LAPTIMER(1585);
	return retval;
}
int _UTL_GetAdcPgEnable( AdcHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1586] = "UTL_GetAdcPgEnable";
	START_LAPTIMER(1586);
	int retval = UTL_GetAdcPgEnable( arg1, arg2);
	STOP_LAPTIMER(1586);
	return retval;
}
int _UTL_GetAdcStartCycle( AdcHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1587] = "UTL_GetAdcStartCycle";
	START_LAPTIMER(1587);
	int retval = UTL_GetAdcStartCycle( arg1, arg2);
	STOP_LAPTIMER(1587);
	return retval;
}
int _UTL_GetAdcMeasMode( AdcHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1588] = "UTL_GetAdcMeasMode";
	START_LAPTIMER(1588);
	int retval = UTL_GetAdcMeasMode( arg1, arg2);
	STOP_LAPTIMER(1588);
	return retval;
}
int _UTL_GetAdcHistoryMode( AdcHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1589] = "UTL_GetAdcHistoryMode";
	START_LAPTIMER(1589);
	int retval = UTL_GetAdcHistoryMode( arg1, arg2);
	STOP_LAPTIMER(1589);
	return retval;
}
int _UTL_GetAdcSettlingTime( AdcHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1590] = "UTL_GetAdcSettlingTime";
	START_LAPTIMER(1590);
	int retval = UTL_GetAdcSettlingTime( arg1, arg2);
	STOP_LAPTIMER(1590);
	return retval;
}
int _UTL_GetAlpgCtrlMode( AlpgCtrlHandle  arg1, RadioButton  arg2, CheckButton * arg3)
{
	MCI_LIST[1591] = "UTL_GetAlpgCtrlMode";
	START_LAPTIMER(1591);
	int retval = UTL_GetAlpgCtrlMode( arg1, arg2, arg3);
	STOP_LAPTIMER(1591);
	return retval;
}
void _UTL_UpdateAuxDutSignal( AuxDutSignalHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[1592] = "UTL_UpdateAuxDutSignal";
	START_LAPTIMER(1592);
	UTL_UpdateAuxDutSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(1592);
}
int _UTL_GetAuxDutSignalStationNumber( AuxDutSignalHandle arg1, USlider * arg2)
{
	MCI_LIST[1593] = "UTL_GetAuxDutSignalStationNumber";
	START_LAPTIMER(1593);
	int retval = UTL_GetAuxDutSignalStationNumber( arg1, arg2);
	STOP_LAPTIMER(1593);
	return retval;
}
int _UTL_GetAuxDutSignalAllStation( AuxDutSignalHandle arg1, CheckButton * arg2)
{
	MCI_LIST[1594] = "UTL_GetAuxDutSignalAllStation";
	START_LAPTIMER(1594);
	int retval = UTL_GetAuxDutSignalAllStation( arg1, arg2);
	STOP_LAPTIMER(1594);
	return retval;
}
int _UTL_GetAuxDutSignalData( AuxDutSignalHandle arg1, USlider * arg2)
{
	MCI_LIST[1595] = "UTL_GetAuxDutSignalData";
	START_LAPTIMER(1595);
	int retval = UTL_GetAuxDutSignalData( arg1, arg2);
	STOP_LAPTIMER(1595);
	return retval;
}
int _UTL_GetAuxDutSignalBurstVariableName( AuxDutSignalHandle arg1, char ** arg2)
{
	MCI_LIST[1596] = "UTL_GetAuxDutSignalBurstVariableName";
	START_LAPTIMER(1596);
	int retval = UTL_GetAuxDutSignalBurstVariableName( arg1, arg2);
	STOP_LAPTIMER(1596);
	return retval;
}
void _UTL_UpdateLbCtrl( LbCtrlHandle arg1)
{
	MCI_LIST[1597] = "UTL_UpdateLbCtrl";
	START_LAPTIMER(1597);
	UTL_UpdateLbCtrl( arg1);
	STOP_LAPTIMER(1597);
}
int _UTL_GetLbCtrlClockTiming( LbCtrlHandle  arg1, DSlider * arg2, DSlider * arg3)
{
	MCI_LIST[1598] = "UTL_GetLbCtrlClockTiming";
	START_LAPTIMER(1598);
	int retval = UTL_GetLbCtrlClockTiming( arg1, arg2, arg3);
	STOP_LAPTIMER(1598);
	return retval;
}
int _UTL_GetLbCtrlDataPacketCount( LbCtrlHandle  arg1, USlider * arg2)
{
	MCI_LIST[1599] = "UTL_GetLbCtrlDataPacketCount";
	START_LAPTIMER(1599);
	int retval = UTL_GetLbCtrlDataPacketCount( arg1, arg2);
	STOP_LAPTIMER(1599);
	return retval;
}
int _UTL_GetLbCtrlDataFirstBit( LbCtrlHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1600] = "UTL_GetLbCtrlDataFirstBit";
	START_LAPTIMER(1600);
	int retval = UTL_GetLbCtrlDataFirstBit( arg1, arg2);
	STOP_LAPTIMER(1600);
	return retval;
}
int _UTL_GetLbCtrlSSPolarity( LbCtrlHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1601] = "UTL_GetLbCtrlSSPolarity";
	START_LAPTIMER(1601);
	int retval = UTL_GetLbCtrlSSPolarity( arg1, arg2);
	STOP_LAPTIMER(1601);
	return retval;
}
int _UTL_GetLbCtrlResetPolarity( LbCtrlHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1602] = "UTL_GetLbCtrlResetPolarity";
	START_LAPTIMER(1602);
	int retval = UTL_GetLbCtrlResetPolarity( arg1, arg2);
	STOP_LAPTIMER(1602);
	return retval;
}
int _UTL_GetLbCtrlStartDelayTime( LbCtrlHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1603] = "UTL_GetLbCtrlStartDelayTime";
	START_LAPTIMER(1603);
	int retval = UTL_GetLbCtrlStartDelayTime( arg1, arg2);
	STOP_LAPTIMER(1603);
	return retval;
}
int _UTL_GetLbCtrlClockCount( LbCtrlHandle  arg1, USlider * arg2)
{
	MCI_LIST[1604] = "UTL_GetLbCtrlClockCount";
	START_LAPTIMER(1604);
	int retval = UTL_GetLbCtrlClockCount( arg1, arg2);
	STOP_LAPTIMER(1604);
	return retval;
}
int _UTL_GetLbCtrlData( LbCtrlHandle  arg1, USlider * arg2)
{
	MCI_LIST[1605] = "UTL_GetLbCtrlData";
	START_LAPTIMER(1605);
	int retval = UTL_GetLbCtrlData( arg1, arg2);
	STOP_LAPTIMER(1605);
	return retval;
}
int _UTL_GetLbCtrlResetDurationTime( LbCtrlHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1606] = "UTL_GetLbCtrlResetDurationTime";
	START_LAPTIMER(1606);
	int retval = UTL_GetLbCtrlResetDurationTime( arg1, arg2);
	STOP_LAPTIMER(1606);
	return retval;
}
int _UTL_GetLbCtrlStrbSkewAdjust( LbCtrlHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1607] = "UTL_GetLbCtrlStrbSkewAdjust";
	START_LAPTIMER(1607);
	int retval = UTL_GetLbCtrlStrbSkewAdjust( arg1, arg2);
	STOP_LAPTIMER(1607);
	return retval;
}
void _UTL_UpdateSpiCtrl( SpiCtrlHandle arg1, RadioButton arg2)
{
	MCI_LIST[1608] = "UTL_UpdateSpiCtrl";
	START_LAPTIMER(1608);
	UTL_UpdateSpiCtrl( arg1, arg2);
	STOP_LAPTIMER(1608);
}
int _UTL_GetSpiCtrlClockTiming( SpiCtrlHandle  arg1, DSlider * arg2, DSlider * arg3)
{
	MCI_LIST[1609] = "UTL_GetSpiCtrlClockTiming";
	START_LAPTIMER(1609);
	int retval = UTL_GetSpiCtrlClockTiming( arg1, arg2, arg3);
	STOP_LAPTIMER(1609);
	return retval;
}
int _UTL_GetSpiCtrlSSPolarity( SpiCtrlHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1610] = "UTL_GetSpiCtrlSSPolarity";
	START_LAPTIMER(1610);
	int retval = UTL_GetSpiCtrlSSPolarity( arg1, arg2);
	STOP_LAPTIMER(1610);
	return retval;
}
int _UTL_GetSpiCtrlStartDelayTime( SpiCtrlHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1611] = "UTL_GetSpiCtrlStartDelayTime";
	START_LAPTIMER(1611);
	int retval = UTL_GetSpiCtrlStartDelayTime( arg1, arg2);
	STOP_LAPTIMER(1611);
	return retval;
}
int _UTL_GetSpiCtrlData( SpiCtrlHandle  arg1, USlider ** arg2, USlider * arg3)
{
	MCI_LIST[1612] = "UTL_GetSpiCtrlData";
	START_LAPTIMER(1612);
	int retval = UTL_GetSpiCtrlData( arg1, arg2, arg3);
	STOP_LAPTIMER(1612);
	return retval;
}
int _UTL_GetSpiCtrlStrbSkewAdjust( SpiCtrlHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1613] = "UTL_GetSpiCtrlStrbSkewAdjust";
	START_LAPTIMER(1613);
	int retval = UTL_GetSpiCtrlStrbSkewAdjust( arg1, arg2);
	STOP_LAPTIMER(1613);
	return retval;
}
int _UTL_GetSpiCtrlMode( SpiCtrlHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1614] = "UTL_GetSpiCtrlMode";
	START_LAPTIMER(1614);
	int retval = UTL_GetSpiCtrlMode( arg1, arg2);
	STOP_LAPTIMER(1614);
	return retval;
}
int _UTL_GetSpiCtrlHighSpeedInterval( SpiCtrlHandle  arg1, DSlider * arg2, DSlider * arg3)
{
	MCI_LIST[1615] = "UTL_GetSpiCtrlHighSpeedInterval";
	START_LAPTIMER(1615);
	int retval = UTL_GetSpiCtrlHighSpeedInterval( arg1, arg2, arg3);
	STOP_LAPTIMER(1615);
	return retval;
}
void _UTL_UpdateDc( DcHandle arg1, RadioButton arg2)
{
	MCI_LIST[1616] = "UTL_UpdateDc";
	START_LAPTIMER(1616);
	UTL_UpdateDc( arg1, arg2);
	STOP_LAPTIMER(1616);
}
int _UTL_GetDcFilter( DcHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1617] = "UTL_GetDcFilter";
	START_LAPTIMER(1617);
	int retval = UTL_GetDcFilter( arg1, arg2);
	STOP_LAPTIMER(1617);
	return retval;
}
int _UTL_GetDcLimitHigh( DcHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1618] = "UTL_GetDcLimitHigh";
	START_LAPTIMER(1618);
	int retval = UTL_GetDcLimitHigh( arg1, arg2);
	STOP_LAPTIMER(1618);
	return retval;
}
int _UTL_GetDcLimitHighDo( DcHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1619] = "UTL_GetDcLimitHighDo";
	START_LAPTIMER(1619);
	int retval = UTL_GetDcLimitHighDo( arg1, arg2);
	STOP_LAPTIMER(1619);
	return retval;
}
int _UTL_GetDcLimitLow( DcHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1620] = "UTL_GetDcLimitLow";
	START_LAPTIMER(1620);
	int retval = UTL_GetDcLimitLow( arg1, arg2);
	STOP_LAPTIMER(1620);
	return retval;
}
int _UTL_GetDcLimitLowDo( DcHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1621] = "UTL_GetDcLimitLowDo";
	START_LAPTIMER(1621);
	int retval = UTL_GetDcLimitLowDo( arg1, arg2);
	STOP_LAPTIMER(1621);
	return retval;
}
int _UTL_GetDcMclamp( DcHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1622] = "UTL_GetDcMclamp";
	START_LAPTIMER(1622);
	int retval = UTL_GetDcMclamp( arg1, arg2);
	STOP_LAPTIMER(1622);
	return retval;
}
int _UTL_GetDcMeasCnt( DcHandle  arg1, Slider * arg2)
{
	MCI_LIST[1623] = "UTL_GetDcMeasCnt";
	START_LAPTIMER(1623);
	int retval = UTL_GetDcMeasCnt( arg1, arg2);
	STOP_LAPTIMER(1623);
	return retval;
}
int _UTL_GetDcMode( DcHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1624] = "UTL_GetDcMode";
	START_LAPTIMER(1624);
	int retval = UTL_GetDcMode( arg1, arg2);
	STOP_LAPTIMER(1624);
	return retval;
}
int _UTL_GetDcMrangeMax( DcHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1625] = "UTL_GetDcMrangeMax";
	START_LAPTIMER(1625);
	int retval = UTL_GetDcMrangeMax( arg1, arg2);
	STOP_LAPTIMER(1625);
	return retval;
}
int _UTL_GetDcMrangeMin( DcHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1626] = "UTL_GetDcMrangeMin";
	START_LAPTIMER(1626);
	int retval = UTL_GetDcMrangeMin( arg1, arg2);
	STOP_LAPTIMER(1626);
	return retval;
}
int _UTL_GetDcPclamp( DcHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1627] = "UTL_GetDcPclamp";
	START_LAPTIMER(1627);
	int retval = UTL_GetDcPclamp( arg1, arg2);
	STOP_LAPTIMER(1627);
	return retval;
}
int _UTL_GetDcSource( DcHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1628] = "UTL_GetDcSource";
	START_LAPTIMER(1628);
	int retval = UTL_GetDcSource( arg1, arg2);
	STOP_LAPTIMER(1628);
	return retval;
}
int _UTL_GetDcSrangeMax( DcHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1629] = "UTL_GetDcSrangeMax";
	START_LAPTIMER(1629);
	int retval = UTL_GetDcSrangeMax( arg1, arg2);
	STOP_LAPTIMER(1629);
	return retval;
}
int _UTL_GetDcSrangeMin( DcHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1630] = "UTL_GetDcSrangeMin";
	START_LAPTIMER(1630);
	int retval = UTL_GetDcSrangeMin( arg1, arg2);
	STOP_LAPTIMER(1630);
	return retval;
}
int _UTL_GetDcWetItem( DcHandle  arg1, RadioButton  arg2, CheckButton * arg3)
{
	MCI_LIST[1631] = "UTL_GetDcWetItem";
	START_LAPTIMER(1631);
	int retval = UTL_GetDcWetItem( arg1, arg2, arg3);
	STOP_LAPTIMER(1631);
	return retval;
}
int _UTL_GetDcSlewRate( DcHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1632] = "UTL_GetDcSlewRate";
	START_LAPTIMER(1632);
	int retval = UTL_GetDcSlewRate( arg1, arg2);
	STOP_LAPTIMER(1632);
	return retval;
}
void _UTL_UpdateDclp( DclpHandle arg1, RadioButton arg2)
{
	MCI_LIST[1633] = "UTL_UpdateDclp";
	START_LAPTIMER(1633);
	UTL_UpdateDclp( arg1, arg2);
	STOP_LAPTIMER(1633);
}
int _UTL_GetDclpHigh( DclpHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1634] = "UTL_GetDclpHigh";
	START_LAPTIMER(1634);
	int retval = UTL_GetDclpHigh( arg1, arg2);
	STOP_LAPTIMER(1634);
	return retval;
}
int _UTL_GetDclpLow( DclpHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1635] = "UTL_GetDclpLow";
	START_LAPTIMER(1635);
	int retval = UTL_GetDclpLow( arg1, arg2);
	STOP_LAPTIMER(1635);
	return retval;
}
void _UTL_UpdateVihh( VihhHandle arg1, RadioButton arg2)
{
	MCI_LIST[1636] = "UTL_UpdateVihh";
	START_LAPTIMER(1636);
	UTL_UpdateVihh( arg1, arg2);
	STOP_LAPTIMER(1636);
}
void _UTL_UpdateVihhPerPin( VihhHandle arg1, UT_PIN arg2, UT_DUT arg3)
{
	MCI_LIST[1637] = "UTL_UpdateVihhPerPin";
	START_LAPTIMER(1637);
	UTL_UpdateVihhPerPin( arg1, arg2, arg3);
	STOP_LAPTIMER(1637);
}
int _UTL_GetVihhHigh( VihhHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1638] = "UTL_GetVihhHigh";
	START_LAPTIMER(1638);
	int retval = UTL_GetVihhHigh( arg1, arg2);
	STOP_LAPTIMER(1638);
	return retval;
}
int _UTL_GetVihhHv( VihhHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1639] = "UTL_GetVihhHv";
	START_LAPTIMER(1639);
	int retval = UTL_GetVihhHv( arg1, arg2);
	STOP_LAPTIMER(1639);
	return retval;
}
int _UTL_GetVihhLow( VihhHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1640] = "UTL_GetVihhLow";
	START_LAPTIMER(1640);
	int retval = UTL_GetVihhLow( arg1, arg2);
	STOP_LAPTIMER(1640);
	return retval;
}
void _UTL_UpdateDctCtrlRelay( DctCtrlRelayHandle arg1, UT_PIN arg2)
{
	MCI_LIST[1641] = "UTL_UpdateDctCtrlRelay";
	START_LAPTIMER(1641);
	UTL_UpdateDctCtrlRelay( arg1, arg2);
	STOP_LAPTIMER(1641);
}
int _UTL_GetDctCtrlRelayDc( DctCtrlRelayHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1642] = "UTL_GetDctCtrlRelayDc";
	START_LAPTIMER(1642);
	int retval = UTL_GetDctCtrlRelayDc( arg1, arg2);
	STOP_LAPTIMER(1642);
	return retval;
}
int _UTL_GetDctCtrlRelayDutCtrl( DctCtrlRelayHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1643] = "UTL_GetDctCtrlRelayDutCtrl";
	START_LAPTIMER(1643);
	int retval = UTL_GetDctCtrlRelayDutCtrl( arg1, arg2);
	STOP_LAPTIMER(1643);
	return retval;
}
int _UTL_GetDctCtrlRelayDutCtrlGrpNum( DctCtrlRelayHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1644] = "UTL_GetDctCtrlRelayDutCtrlGrpNum";
	START_LAPTIMER(1644);
	int retval = UTL_GetDctCtrlRelayDutCtrlGrpNum( arg1, arg2);
	STOP_LAPTIMER(1644);
	return retval;
}
int _UTL_GetDctCtrlRelayPl( DctCtrlRelayHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1645] = "UTL_GetDctCtrlRelayPl";
	START_LAPTIMER(1645);
	int retval = UTL_GetDctCtrlRelayPl( arg1, arg2);
	STOP_LAPTIMER(1645);
	return retval;
}
int _UTL_GetDctCtrlRelayHvDr( DctCtrlRelayHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1646] = "UTL_GetDctCtrlRelayHvDr";
	START_LAPTIMER(1646);
	int retval = UTL_GetDctCtrlRelayHvDr( arg1, arg2);
	STOP_LAPTIMER(1646);
	return retval;
}
int _UTL_GetDctCtrlRelayTerm( DctCtrlRelayHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1647] = "UTL_GetDctCtrlRelayTerm";
	START_LAPTIMER(1647);
	int retval = UTL_GetDctCtrlRelayTerm( arg1, arg2);
	STOP_LAPTIMER(1647);
	return retval;
}
int _UTL_GetDctCtrlRelayVi( DctCtrlRelayHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1648] = "UTL_GetDctCtrlRelayVi";
	START_LAPTIMER(1648);
	int retval = UTL_GetDctCtrlRelayVi( arg1, arg2);
	STOP_LAPTIMER(1648);
	return retval;
}
int _UTL_GetDctCtrlRelayVo( DctCtrlRelayHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1649] = "UTL_GetDctCtrlRelayVo";
	START_LAPTIMER(1649);
	int retval = UTL_GetDctCtrlRelayVo( arg1, arg2);
	STOP_LAPTIMER(1649);
	return retval;
}
int _UTL_GetDctCtrlRelayVihh( DctCtrlRelayHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1650] = "UTL_GetDctCtrlRelayVihh";
	START_LAPTIMER(1650);
	int retval = UTL_GetDctCtrlRelayVihh( arg1, arg2);
	STOP_LAPTIMER(1650);
	return retval;
}
int _UTL_GetDctCtrlRelayWaitTime( DctCtrlRelayHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1651] = "UTL_GetDctCtrlRelayWaitTime";
	START_LAPTIMER(1651);
	int retval = UTL_GetDctCtrlRelayWaitTime( arg1, arg2);
	STOP_LAPTIMER(1651);
	return retval;
}
void _UTL_UpdateDctVsCtrlRelay( DctVsCtrlRelayHandle arg1, RadioButton arg2)
{
	MCI_LIST[1652] = "UTL_UpdateDctVsCtrlRelay";
	START_LAPTIMER(1652);
	UTL_UpdateDctVsCtrlRelay( arg1, arg2);
	STOP_LAPTIMER(1652);
}
int _UTL_GetDctVsCtrlRelayDutCtrl( DctVsCtrlRelayHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1653] = "UTL_GetDctVsCtrlRelayDutCtrl";
	START_LAPTIMER(1653);
	int retval = UTL_GetDctVsCtrlRelayDutCtrl( arg1, arg2);
	STOP_LAPTIMER(1653);
	return retval;
}
int _UTL_GetDctVsCtrlRelayDutCtrlGrpNum( DctVsCtrlRelayHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1654] = "UTL_GetDctVsCtrlRelayDutCtrlGrpNum";
	START_LAPTIMER(1654);
	int retval = UTL_GetDctVsCtrlRelayDutCtrlGrpNum( arg1, arg2);
	STOP_LAPTIMER(1654);
	return retval;
}
int _UTL_GetDctVsCtrlRelayWaitTime( DctVsCtrlRelayHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1655] = "UTL_GetDctVsCtrlRelayWaitTime";
	START_LAPTIMER(1655);
	int retval = UTL_GetDctVsCtrlRelayWaitTime( arg1, arg2);
	STOP_LAPTIMER(1655);
	return retval;
}
int _UTL_GetDbmAccessUnitNumber( DbmAccessHandle  arg1, RadioButton *  arg2)
{
	MCI_LIST[1656] = "UTL_GetDbmAccessUnitNumber";
	START_LAPTIMER(1656);
	int retval = UTL_GetDbmAccessUnitNumber( arg1, arg2);
	STOP_LAPTIMER(1656);
	return retval;
}
int _UTL_GetDbmAccessAllUnit( DbmAccessHandle  arg1, CheckButton *  arg2)
{
	MCI_LIST[1657] = "UTL_GetDbmAccessAllUnit";
	START_LAPTIMER(1657);
	int retval = UTL_GetDbmAccessAllUnit( arg1, arg2);
	STOP_LAPTIMER(1657);
	return retval;
}
int _UTL_GetDbmAccessDataKind( DbmAccessHandle  arg1, RadioButton *  arg2)
{
	MCI_LIST[1658] = "UTL_GetDbmAccessDataKind";
	START_LAPTIMER(1658);
	int retval = UTL_GetDbmAccessDataKind( arg1, arg2);
	STOP_LAPTIMER(1658);
	return retval;
}
int _UTL_GetDbmAccessBlockNumber( DbmAccessHandle  arg1, RadioButton *  arg2)
{
	MCI_LIST[1659] = "UTL_GetDbmAccessBlockNumber";
	START_LAPTIMER(1659);
	int retval = UTL_GetDbmAccessBlockNumber( arg1, arg2);
	STOP_LAPTIMER(1659);
	return retval;
}
int _UTL_GetDbmAccessStartAddr( DbmAccessHandle  arg1, USlider *  arg2)
{
	MCI_LIST[1660] = "UTL_GetDbmAccessStartAddr";
	START_LAPTIMER(1660);
	int retval = UTL_GetDbmAccessStartAddr( arg1, arg2);
	STOP_LAPTIMER(1660);
	return retval;
}
int _UTL_GetDbmAccessStopAddr( DbmAccessHandle  arg1, USlider *  arg2)
{
	MCI_LIST[1661] = "UTL_GetDbmAccessStopAddr";
	START_LAPTIMER(1661);
	int retval = UTL_GetDbmAccessStopAddr( arg1, arg2);
	STOP_LAPTIMER(1661);
	return retval;
}
void _UTL_UpdateDbmFile( DbmFileHandle arg1)
{
	MCI_LIST[1662] = "UTL_UpdateDbmFile";
	START_LAPTIMER(1662);
	UTL_UpdateDbmFile( arg1);
	STOP_LAPTIMER(1662);
}
int _UTL_GetDbmFileMpatName( DbmFileHandle  arg1, char ** arg2)
{
	MCI_LIST[1663] = "UTL_GetDbmFileMpatName";
	START_LAPTIMER(1663);
	int retval = UTL_GetDbmFileMpatName( arg1, arg2);
	STOP_LAPTIMER(1663);
	return retval;
}
int _UTL_GetDbmFileStartPc( DbmFileHandle  arg1, USlider *  arg2)
{
	MCI_LIST[1664] = "UTL_GetDbmFileStartPc";
	START_LAPTIMER(1664);
	int retval = UTL_GetDbmFileStartPc( arg1, arg2);
	STOP_LAPTIMER(1664);
	return retval;
}
int _UTL_GetDbmFileResetMode( DbmFileHandle  arg1, RadioButton *  arg2)
{
	MCI_LIST[1665] = "UTL_GetDbmFileResetMode";
	START_LAPTIMER(1665);
	int retval = UTL_GetDbmFileResetMode( arg1, arg2);
	STOP_LAPTIMER(1665);
	return retval;
}
DbmPatternInfoHandle _UTL_GetDbmPatternInfoHandle()
{
	MCI_LIST[1666] = "UTL_GetDbmPatternInfoHandle";
	START_LAPTIMER(1666);
	DbmPatternInfoHandle retval = UTL_GetDbmPatternInfoHandle();
	STOP_LAPTIMER(1666);
	return retval;
}
void _UTL_SetDbmPatternInfoMpatName( DbmPatternInfoHandle arg1, char * arg2)
{
	MCI_LIST[1667] = "UTL_SetDbmPatternInfoMpatName";
	START_LAPTIMER(1667);
	UTL_SetDbmPatternInfoMpatName( arg1, arg2);
	STOP_LAPTIMER(1667);
}
void _UTL_SetDbmPatternInfoStartPc( DbmPatternInfoHandle arg1, USlider arg2)
{
	MCI_LIST[1668] = "UTL_SetDbmPatternInfoStartPc";
	START_LAPTIMER(1668);
	UTL_SetDbmPatternInfoStartPc( arg1, arg2);
	STOP_LAPTIMER(1668);
}
void _UTL_UpdateDbmPatternInfo( DbmPatternInfoHandle arg1)
{
	MCI_LIST[1669] = "UTL_UpdateDbmPatternInfo";
	START_LAPTIMER(1669);
	UTL_UpdateDbmPatternInfo( arg1);
	STOP_LAPTIMER(1669);
}
int _UTL_GetDbmPatternInfoMpatName( DbmPatternInfoHandle  arg1, char ** arg2)
{
	MCI_LIST[1670] = "UTL_GetDbmPatternInfoMpatName";
	START_LAPTIMER(1670);
	int retval = UTL_GetDbmPatternInfoMpatName( arg1, arg2);
	STOP_LAPTIMER(1670);
	return retval;
}
int _UTL_GetDbmPatternInfoStartPc( DbmPatternInfoHandle  arg1, USlider *  arg2)
{
	MCI_LIST[1671] = "UTL_GetDbmPatternInfoStartPc";
	START_LAPTIMER(1671);
	int retval = UTL_GetDbmPatternInfoStartPc( arg1, arg2);
	STOP_LAPTIMER(1671);
	return retval;
}
int _UTL_GetDbmPatternInfoBaseAddr( DbmPatternInfoHandle  arg1, USlider *  arg2)
{
	MCI_LIST[1672] = "UTL_GetDbmPatternInfoBaseAddr";
	START_LAPTIMER(1672);
	int retval = UTL_GetDbmPatternInfoBaseAddr( arg1, arg2);
	STOP_LAPTIMER(1672);
	return retval;
}
int _UTL_GetDbmPatternInfoDataSize( DbmPatternInfoHandle  arg1, RadioButton  arg2, USlider *  arg3)
{
	MCI_LIST[1673] = "UTL_GetDbmPatternInfoDataSize";
	START_LAPTIMER(1673);
	int retval = UTL_GetDbmPatternInfoDataSize( arg1, arg2, arg3);
	STOP_LAPTIMER(1673);
	return retval;
}
int _UTL_GetDbmPatternInfoStartAddr( DbmPatternInfoHandle  arg1, RadioButton  arg2, USlider *  arg3)
{
	MCI_LIST[1674] = "UTL_GetDbmPatternInfoStartAddr";
	START_LAPTIMER(1674);
	int retval = UTL_GetDbmPatternInfoStartAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1674);
	return retval;
}
int _UTL_GetCbmAccessUnitNumber( CbmAccessHandle  arg1, RadioButton *  arg2)
{
	MCI_LIST[1675] = "UTL_GetCbmAccessUnitNumber";
	START_LAPTIMER(1675);
	int retval = UTL_GetCbmAccessUnitNumber( arg1, arg2);
	STOP_LAPTIMER(1675);
	return retval;
}
int _UTL_GetCbmAccessAllUnit( CbmAccessHandle  arg1, CheckButton *  arg2)
{
	MCI_LIST[1676] = "UTL_GetCbmAccessAllUnit";
	START_LAPTIMER(1676);
	int retval = UTL_GetCbmAccessAllUnit( arg1, arg2);
	STOP_LAPTIMER(1676);
	return retval;
}
int _UTL_GetCbmAccessDataKind( CbmAccessHandle  arg1, RadioButton *  arg2)
{
	MCI_LIST[1677] = "UTL_GetCbmAccessDataKind";
	START_LAPTIMER(1677);
	int retval = UTL_GetCbmAccessDataKind( arg1, arg2);
	STOP_LAPTIMER(1677);
	return retval;
}
int _UTL_GetCbmAccessStartAddr( CbmAccessHandle  arg1, USlider *  arg2)
{
	MCI_LIST[1678] = "UTL_GetCbmAccessStartAddr";
	START_LAPTIMER(1678);
	int retval = UTL_GetCbmAccessStartAddr( arg1, arg2);
	STOP_LAPTIMER(1678);
	return retval;
}
int _UTL_GetCbmAccessStopAddr( CbmAccessHandle  arg1, USlider *  arg2)
{
	MCI_LIST[1679] = "UTL_GetCbmAccessStopAddr";
	START_LAPTIMER(1679);
	int retval = UTL_GetCbmAccessStopAddr( arg1, arg2);
	STOP_LAPTIMER(1679);
	return retval;
}
void _UTL_UpdateCbmFile( CbmFileHandle arg1)
{
	MCI_LIST[1680] = "UTL_UpdateCbmFile";
	START_LAPTIMER(1680);
	UTL_UpdateCbmFile( arg1);
	STOP_LAPTIMER(1680);
}
int _UTL_GetCbmFileMpatName( CbmFileHandle  arg1, char ** arg2)
{
	MCI_LIST[1681] = "UTL_GetCbmFileMpatName";
	START_LAPTIMER(1681);
	int retval = UTL_GetCbmFileMpatName( arg1, arg2);
	STOP_LAPTIMER(1681);
	return retval;
}
int _UTL_GetCbmFileStartPc( CbmFileHandle  arg1, USlider *  arg2)
{
	MCI_LIST[1682] = "UTL_GetCbmFileStartPc";
	START_LAPTIMER(1682);
	int retval = UTL_GetCbmFileStartPc( arg1, arg2);
	STOP_LAPTIMER(1682);
	return retval;
}
int _UTL_GetCbmFileResetMode( CbmFileHandle  arg1, RadioButton *  arg2)
{
	MCI_LIST[1683] = "UTL_GetCbmFileResetMode";
	START_LAPTIMER(1683);
	int retval = UTL_GetCbmFileResetMode( arg1, arg2);
	STOP_LAPTIMER(1683);
	return retval;
}
int _UTL_GetFctReadPinDut( FctReadPinHandle  arg1, UT_DUT  arg2, CheckButton * arg3)
{
	MCI_LIST[1684] = "UTL_GetFctReadPinDut";
	START_LAPTIMER(1684);
	int retval = UTL_GetFctReadPinDut( arg1, arg2, arg3);
	STOP_LAPTIMER(1684);
	return retval;
}
int _UTL_GetFctReadPinMode( FctReadPinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1685] = "UTL_GetFctReadPinMode";
	START_LAPTIMER(1685);
	int retval = UTL_GetFctReadPinMode( arg1, arg2);
	STOP_LAPTIMER(1685);
	return retval;
}
int _UTL_GetFctReadPinNumber( FctReadPinHandle  arg1, UT_PIN * arg2)
{
	MCI_LIST[1686] = "UTL_GetFctReadPinNumber";
	START_LAPTIMER(1686);
	int retval = UTL_GetFctReadPinNumber( arg1, arg2);
	STOP_LAPTIMER(1686);
	return retval;
}
int _UTL_GetFctReadPinTargetBank( FctReadPinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1687] = "UTL_GetFctReadPinTargetBank";
	START_LAPTIMER(1687);
	int retval = UTL_GetFctReadPinTargetBank( arg1, arg2);
	STOP_LAPTIMER(1687);
	return retval;
}
void _UTL_UpdateIl( IlHandle arg1, RadioButton arg2)
{
	MCI_LIST[1688] = "UTL_UpdateIl";
	START_LAPTIMER(1688);
	UTL_UpdateIl( arg1, arg2);
	STOP_LAPTIMER(1688);
}
int _UTL_GetIlHigh( IlHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1689] = "UTL_GetIlHigh";
	START_LAPTIMER(1689);
	int retval = UTL_GetIlHigh( arg1, arg2);
	STOP_LAPTIMER(1689);
	return retval;
}
int _UTL_GetIlLow( IlHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1690] = "UTL_GetIlLow";
	START_LAPTIMER(1690);
	int retval = UTL_GetIlLow( arg1, arg2);
	STOP_LAPTIMER(1690);
	return retval;
}
int _UTL_GetDctAfterDcOn( DctHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1691] = "UTL_GetDctAfterDcOn";
	START_LAPTIMER(1691);
	int retval = UTL_GetDctAfterDcOn( arg1, arg2);
	STOP_LAPTIMER(1691);
	return retval;
}
int _UTL_GetDctAfterFunc( DctHandle  arg1, void ** arg2)
{
	MCI_LIST[1692] = "UTL_GetDctAfterFunc";
	START_LAPTIMER(1692);
	int retval = UTL_GetDctAfterFunc( arg1, arg2);
	STOP_LAPTIMER(1692);
	return retval;
}
int _UTL_GetDctAltMclamp( DctHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1693] = "UTL_GetDctAltMclamp";
	START_LAPTIMER(1693);
	int retval = UTL_GetDctAltMclamp( arg1, arg2);
	STOP_LAPTIMER(1693);
	return retval;
}
int _UTL_GetDctAltMode( DctHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1694] = "UTL_GetDctAltMode";
	START_LAPTIMER(1694);
	int retval = UTL_GetDctAltMode( arg1, arg2);
	STOP_LAPTIMER(1694);
	return retval;
}
int _UTL_GetDctAltPclamp( DctHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1695] = "UTL_GetDctAltPclamp";
	START_LAPTIMER(1695);
	int retval = UTL_GetDctAltPclamp( arg1, arg2);
	STOP_LAPTIMER(1695);
	return retval;
}
int _UTL_GetDctAltSource( DctHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1696] = "UTL_GetDctAltSource";
	START_LAPTIMER(1696);
	int retval = UTL_GetDctAltSource( arg1, arg2);
	STOP_LAPTIMER(1696);
	return retval;
}
int _UTL_GetDctBeforeFunc( DctHandle  arg1, void ** arg2)
{
	MCI_LIST[1697] = "UTL_GetDctBeforeFunc";
	START_LAPTIMER(1697);
	int retval = UTL_GetDctBeforeFunc( arg1, arg2);
	STOP_LAPTIMER(1697);
	return retval;
}
int _UTL_GetDctFailAction( DctHandle  arg1, void ** arg2)
{
	MCI_LIST[1698] = "UTL_GetDctFailAction";
	START_LAPTIMER(1698);
	int retval = UTL_GetDctFailAction( arg1, arg2);
	STOP_LAPTIMER(1698);
	return retval;
}
int _UTL_GetDctPassAction( DctHandle  arg1, void ** arg2)
{
	MCI_LIST[1699] = "UTL_GetDctPassAction";
	START_LAPTIMER(1699);
	int retval = UTL_GetDctPassAction( arg1, arg2);
	STOP_LAPTIMER(1699);
	return retval;
}
int _UTL_GetDctPinList( DctHandle  arg1, char ** arg2)
{
	MCI_LIST[1700] = "UTL_GetDctPinList";
	START_LAPTIMER(1700);
	int retval = UTL_GetDctPinList( arg1, arg2);
	STOP_LAPTIMER(1700);
	return retval;
}
int _UTL_GetDctPinPl( DctHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1701] = "UTL_GetDctPinPl";
	START_LAPTIMER(1701);
	int retval = UTL_GetDctPinPl( arg1, arg2);
	STOP_LAPTIMER(1701);
	return retval;
}
int _UTL_GetDctPinHvDr( DctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1702] = "UTL_GetDctPinHvDr";
	START_LAPTIMER(1702);
	int retval = UTL_GetDctPinHvDr( arg1, arg2);
	STOP_LAPTIMER(1702);
	return retval;
}
int _UTL_GetDctPinTerm( DctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1703] = "UTL_GetDctPinTerm";
	START_LAPTIMER(1703);
	int retval = UTL_GetDctPinTerm( arg1, arg2);
	STOP_LAPTIMER(1703);
	return retval;
}
int _UTL_GetDctPinVi( DctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1704] = "UTL_GetDctPinVi";
	START_LAPTIMER(1704);
	int retval = UTL_GetDctPinVi( arg1, arg2);
	STOP_LAPTIMER(1704);
	return retval;
}
int _UTL_GetDctPinVo( DctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1705] = "UTL_GetDctPinVo";
	START_LAPTIMER(1705);
	int retval = UTL_GetDctPinVo( arg1, arg2);
	STOP_LAPTIMER(1705);
	return retval;
}
int _UTL_GetDctPinVihh( DctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1706] = "UTL_GetDctPinVihh";
	START_LAPTIMER(1706);
	int retval = UTL_GetDctPinVihh( arg1, arg2);
	STOP_LAPTIMER(1706);
	return retval;
}
int _UTL_GetDctRelayMode( DctHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1707] = "UTL_GetDctRelayMode";
	START_LAPTIMER(1707);
	int retval = UTL_GetDctRelayMode( arg1, arg2);
	STOP_LAPTIMER(1707);
	return retval;
}
int _UTL_GetDctAutoRangeMode( DctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1708] = "UTL_GetDctAutoRangeMode";
	START_LAPTIMER(1708);
	int retval = UTL_GetDctAutoRangeMode( arg1, arg2);
	STOP_LAPTIMER(1708);
	return retval;
}
int _UTL_GetDctGoNogoOnly( DctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1709] = "UTL_GetDctGoNogoOnly";
	START_LAPTIMER(1709);
	int retval = UTL_GetDctGoNogoOnly( arg1, arg2);
	STOP_LAPTIMER(1709);
	return retval;
}
int _UTL_GetDctAutoTestName( DctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1710] = "UTL_GetDctAutoTestName";
	START_LAPTIMER(1710);
	int retval = UTL_GetDctAutoTestName( arg1, arg2);
	STOP_LAPTIMER(1710);
	return retval;
}
int _UTL_GetReadMpatFileName( ReadMpatPcHandle  arg1, char ** arg2)
{
	MCI_LIST[1711] = "UTL_GetReadMpatFileName";
	START_LAPTIMER(1711);
	int retval = UTL_GetReadMpatFileName( arg1, arg2);
	STOP_LAPTIMER(1711);
	return retval;
}
int _UTL_GetReadMpatLabelName( ReadMpatPcHandle  arg1, char ** arg2)
{
	MCI_LIST[1712] = "UTL_GetReadMpatLabelName";
	START_LAPTIMER(1712);
	int retval = UTL_GetReadMpatLabelName( arg1, arg2);
	STOP_LAPTIMER(1712);
	return retval;
}
int _UTL_GetReadMpatModuleName( ReadMpatPcHandle  arg1, char ** arg2)
{
	MCI_LIST[1713] = "UTL_GetReadMpatModuleName";
	START_LAPTIMER(1713);
	int retval = UTL_GetReadMpatModuleName( arg1, arg2);
	STOP_LAPTIMER(1713);
	return retval;
}
int _UTL_GetReadMpatStartName( ReadMpatPcHandle  arg1, char ** arg2)
{
	MCI_LIST[1714] = "UTL_GetReadMpatStartName";
	START_LAPTIMER(1714);
	int retval = UTL_GetReadMpatStartName( arg1, arg2);
	STOP_LAPTIMER(1714);
	return retval;
}
PinListCursor _UTL_GetPinListCursor()
{
	MCI_LIST[1715] = "UTL_GetPinListCursor";
	START_LAPTIMER(1715);
	PinListCursor retval = UTL_GetPinListCursor();
	STOP_LAPTIMER(1715);
	return retval;
}
char * _UTL_NextPinList( PinListCursor  arg1)
{
	MCI_LIST[1716] = "UTL_NextPinList";
	START_LAPTIMER(1716);
	char * retval = UTL_NextPinList( arg1);
	STOP_LAPTIMER(1716);
	return retval;
}
int _UTL_GetPinType( char * arg1, RadioButton * arg2)
{
	MCI_LIST[1717] = "UTL_GetPinType";
	START_LAPTIMER(1717);
	int retval = UTL_GetPinType( arg1, arg2);
	STOP_LAPTIMER(1717);
	return retval;
}
void _UTL_UpdateReg( RegHandle arg1)
{
	MCI_LIST[1718] = "UTL_UpdateReg";
	START_LAPTIMER(1718);
	UTL_UpdateReg( arg1);
	STOP_LAPTIMER(1718);
}
int _UTL_GetRegDirection( RegHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1719] = "UTL_GetRegDirection";
	START_LAPTIMER(1719);
	int retval = UTL_GetRegDirection( arg1, arg2);
	STOP_LAPTIMER(1719);
	return retval;
}
int _UTL_GetRegRb( RegHandle arg1, RadioButton arg2, RadioButton * arg3)
{
	MCI_LIST[1720] = "UTL_GetRegRb";
	START_LAPTIMER(1720);
	int retval = UTL_GetRegRb( arg1, arg2, arg3);
	STOP_LAPTIMER(1720);
	return retval;
}
int _UTL_GetRegUs( RegHandle arg1, RadioButton arg2, RadioButton arg3, USlider * arg4)
{
	MCI_LIST[1721] = "UTL_GetRegUs";
	START_LAPTIMER(1721);
	int retval = UTL_GetRegUs( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1721);
	return retval;
}
int _UTL_GetRegAlpgUnit( RegHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1722] = "UTL_GetRegAlpgUnit";
	START_LAPTIMER(1722);
	int retval = UTL_GetRegAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1722);
	return retval;
}
int _UTL_GetRegTimerCycleCnt( RegHandle arg1, RadioButton arg2, RadioButton * arg3, USlider * arg4)
{
	MCI_LIST[1723] = "UTL_GetRegTimerCycleCnt";
	START_LAPTIMER(1723);
	int retval = UTL_GetRegTimerCycleCnt( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1723);
	return retval;
}
int _UTL_GetRegTimerTime( RegHandle arg1, RadioButton arg2, DSlider * arg3)
{
	MCI_LIST[1724] = "UTL_GetRegTimerTime";
	START_LAPTIMER(1724);
	int retval = UTL_GetRegTimerTime( arg1, arg2, arg3);
	STOP_LAPTIMER(1724);
	return retval;
}
int _UTL_GetRegUpdateUnitNumber( RegHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1725] = "UTL_GetRegUpdateUnitNumber";
	START_LAPTIMER(1725);
	int retval = UTL_GetRegUpdateUnitNumber( arg1, arg2);
	STOP_LAPTIMER(1725);
	return retval;
}
int _UTL_GetTimerMode( TimerModeHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[1726] = "UTL_GetTimerMode";
	START_LAPTIMER(1726);
	int retval = UTL_GetTimerMode( arg1, arg2, arg3);
	STOP_LAPTIMER(1726);
	return retval;
}
int _UTL_GetTimerModeDirection( TimerModeHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1727] = "UTL_GetTimerModeDirection";
	START_LAPTIMER(1727);
	int retval = UTL_GetTimerModeDirection( arg1, arg2);
	STOP_LAPTIMER(1727);
	return retval;
}
void _UTL_UpdateTimerMode( TimerModeHandle  arg1)
{
	MCI_LIST[1728] = "UTL_UpdateTimerMode";
	START_LAPTIMER(1728);
	UTL_UpdateTimerMode( arg1);
	STOP_LAPTIMER(1728);
}
void _UTL_UpdateAddrScram( AddrScramHandle arg1)
{
	MCI_LIST[1729] = "UTL_UpdateAddrScram";
	START_LAPTIMER(1729);
	UTL_UpdateAddrScram( arg1);
	STOP_LAPTIMER(1729);
}
int _UTL_GetAddrScramFileName( AddrScramHandle  arg1, char ** arg2)
{
	MCI_LIST[1730] = "UTL_GetAddrScramFileName";
	START_LAPTIMER(1730);
	int retval = UTL_GetAddrScramFileName( arg1, arg2);
	STOP_LAPTIMER(1730);
	return retval;
}
int _UTL_GetAddrScramMode( AddrScramHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1731] = "UTL_GetAddrScramMode";
	START_LAPTIMER(1731);
	int retval = UTL_GetAddrScramMode( arg1, arg2);
	STOP_LAPTIMER(1731);
	return retval;
}
void _UTL_UpdatePreScram( AddrScramHandle arg1)
{
	MCI_LIST[1732] = "UTL_UpdatePreScram";
	START_LAPTIMER(1732);
	UTL_UpdatePreScram( arg1);
	STOP_LAPTIMER(1732);
}
int _UTL_GetAddrScramAddrAssign( AddrScramHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[1733] = "UTL_GetAddrScramAddrAssign";
	START_LAPTIMER(1733);
	int retval = UTL_GetAddrScramAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(1733);
	return retval;
}
int _UTL_GetAddrScramAlpgUnit( AddrScramHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1734] = "UTL_GetAddrScramAlpgUnit";
	START_LAPTIMER(1734);
	int retval = UTL_GetAddrScramAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1734);
	return retval;
}
int _UTL_GetAddrScramEnableBit( AddrScramHandle  arg1, RadioButton  arg2, RadioButton  arg3, USlider * arg4)
{
	MCI_LIST[1735] = "UTL_GetAddrScramEnableBit";
	START_LAPTIMER(1735);
	int retval = UTL_GetAddrScramEnableBit( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1735);
	return retval;
}
int _UTL_GetAddrScramPdsEnable( AddrScramHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1736] = "UTL_GetAddrScramPdsEnable";
	START_LAPTIMER(1736);
	int retval = UTL_GetAddrScramPdsEnable( arg1, arg2);
	STOP_LAPTIMER(1736);
	return retval;
}
int _UTL_GetAddrScramSeparateMode( AddrScramHandle arg1, CheckButton * arg2)
{
	MCI_LIST[1737] = "UTL_GetAddrScramSeparateMode";
	START_LAPTIMER(1737);
	int retval = UTL_GetAddrScramSeparateMode( arg1, arg2);
	STOP_LAPTIMER(1737);
	return retval;
}
int _UTL_GetAddrScramSideSelect( AddrScramHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1738] = "UTL_GetAddrScramSideSelect";
	START_LAPTIMER(1738);
	int retval = UTL_GetAddrScramSideSelect( arg1, arg2);
	STOP_LAPTIMER(1738);
	return retval;
}
int _UTL_GetAddrScramOutputMethod( AddrScramHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1739] = "UTL_GetAddrScramOutputMethod";
	START_LAPTIMER(1739);
	int retval = UTL_GetAddrScramOutputMethod( arg1, arg2);
	STOP_LAPTIMER(1739);
	return retval;
}
void _UTL_UpdateScramCondition( ScramConditionHandle arg1)
{
	MCI_LIST[1740] = "UTL_UpdateScramCondition";
	START_LAPTIMER(1740);
	UTL_UpdateScramCondition( arg1);
	STOP_LAPTIMER(1740);
}
int _UTL_GetScramConditionAlpgUnit( ScramConditionHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1741] = "UTL_GetScramConditionAlpgUnit";
	START_LAPTIMER(1741);
	int retval = UTL_GetScramConditionAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1741);
	return retval;
}
int _UTL_GetScramConditionDivideMode( ScramConditionHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1742] = "UTL_GetScramConditionDivideMode";
	START_LAPTIMER(1742);
	int retval = UTL_GetScramConditionDivideMode( arg1, arg2);
	STOP_LAPTIMER(1742);
	return retval;
}
void _UTL_UpdatePreScramCondition( PreScramConditionHandle arg1)
{
	MCI_LIST[1743] = "UTL_UpdatePreScramCondition";
	START_LAPTIMER(1743);
	UTL_UpdatePreScramCondition( arg1);
	STOP_LAPTIMER(1743);
}
int _UTL_GetPreScramConditionAddr( PreScramConditionHandle  arg1, RadioButton  arg2, CheckButton * arg3)
{
	MCI_LIST[1744] = "UTL_GetPreScramConditionAddr";
	START_LAPTIMER(1744);
	int retval = UTL_GetPreScramConditionAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1744);
	return retval;
}
int _UTL_GetPreScramConditionAlpgUnit( PreScramConditionHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1745] = "UTL_GetPreScramConditionAlpgUnit";
	START_LAPTIMER(1745);
	int retval = UTL_GetPreScramConditionAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1745);
	return retval;
}
int _UTL_GetPreScramConditionMode( PreScramConditionHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1746] = "UTL_GetPreScramConditionMode";
	START_LAPTIMER(1746);
	int retval = UTL_GetPreScramConditionMode( arg1, arg2);
	STOP_LAPTIMER(1746);
	return retval;
}
int _UTL_GetPreScramConditionMixMode( PreScramConditionHandle arg1, CheckButton * arg2)
{
	MCI_LIST[1747] = "UTL_GetPreScramConditionMixMode";
	START_LAPTIMER(1747);
	int retval = UTL_GetPreScramConditionMixMode( arg1, arg2);
	STOP_LAPTIMER(1747);
	return retval;
}
SignalCursor _UTL_GetPreScramConditionWriteSignalCursor( PreScramConditionHandle arg1)
{
	MCI_LIST[1748] = "UTL_GetPreScramConditionWriteSignalCursor";
	START_LAPTIMER(1748);
	SignalCursor retval = UTL_GetPreScramConditionWriteSignalCursor( arg1);
	STOP_LAPTIMER(1748);
	return retval;
}
void _UTL_UpdateBurstScram( BurstScramHandle arg1)
{
	MCI_LIST[1749] = "UTL_UpdateBurstScram";
	START_LAPTIMER(1749);
	UTL_UpdateBurstScram( arg1);
	STOP_LAPTIMER(1749);
}
int _UTL_GetBurstScramMode( BurstScramHandle arg1, CheckButton * arg2)
{
	MCI_LIST[1750] = "UTL_GetBurstScramMode";
	START_LAPTIMER(1750);
	int retval = UTL_GetBurstScramMode( arg1, arg2);
	STOP_LAPTIMER(1750);
	return retval;
}
int _UTL_GetBurstScramDdrType( BurstScramHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1751] = "UTL_GetBurstScramDdrType";
	START_LAPTIMER(1751);
	int retval = UTL_GetBurstScramDdrType( arg1, arg2);
	STOP_LAPTIMER(1751);
	return retval;
}
int _UTL_GetBurstScramBaseFileName( BurstScramHandle arg1, char ** arg2)
{
	MCI_LIST[1752] = "UTL_GetBurstScramBaseFileName";
	START_LAPTIMER(1752);
	int retval = UTL_GetBurstScramBaseFileName( arg1, arg2);
	STOP_LAPTIMER(1752);
	return retval;
}
int _UTL_GetBurstScramDataRate( BurstScramHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1753] = "UTL_GetBurstScramDataRate";
	START_LAPTIMER(1753);
	int retval = UTL_GetBurstScramDataRate( arg1, arg2);
	STOP_LAPTIMER(1753);
	return retval;
}
int _UTL_GetBurstScramLength( BurstScramHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1754] = "UTL_GetBurstScramLength";
	START_LAPTIMER(1754);
	int retval = UTL_GetBurstScramLength( arg1, arg2);
	STOP_LAPTIMER(1754);
	return retval;
}
int _UTL_GetBurstScramWrapType( BurstScramHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1755] = "UTL_GetBurstScramWrapType";
	START_LAPTIMER(1755);
	int retval = UTL_GetBurstScramWrapType( arg1, arg2);
	STOP_LAPTIMER(1755);
	return retval;
}
SignalCursor _UTL_GetBurstScramWriteSignalCursor( BurstScramHandle arg1)
{
	MCI_LIST[1756] = "UTL_GetBurstScramWriteSignalCursor";
	START_LAPTIMER(1756);
	SignalCursor retval = UTL_GetBurstScramWriteSignalCursor( arg1);
	STOP_LAPTIMER(1756);
	return retval;
}
int _UTL_GetBurstScramAddrUnit( BurstScramHandle arg1, RadioButton arg2, CheckButton * arg3)
{
	MCI_LIST[1757] = "UTL_GetBurstScramAddrUnit";
	START_LAPTIMER(1757);
	int retval = UTL_GetBurstScramAddrUnit( arg1, arg2, arg3);
	STOP_LAPTIMER(1757);
	return retval;
}
int _UTL_GetBurstScramBankAddrLoadUnit( BurstScramHandle arg1, RadioButton arg2, CheckButton * arg3)
{
	MCI_LIST[1758] = "UTL_GetBurstScramBankAddrLoadUnit";
	START_LAPTIMER(1758);
	int retval = UTL_GetBurstScramBankAddrLoadUnit( arg1, arg2, arg3);
	STOP_LAPTIMER(1758);
	return retval;
}
int _UTL_GetPatDelayCycle( PatDelayHandle  arg1, RadioButton  arg2, USlider * arg3)
{
	MCI_LIST[1759] = "UTL_GetPatDelayCycle";
	START_LAPTIMER(1759);
	int retval = UTL_GetPatDelayCycle( arg1, arg2, arg3);
	STOP_LAPTIMER(1759);
	return retval;
}
int _UTL_GetPatDelayAlpgUnit( PatDelayHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1760] = "UTL_GetPatDelayAlpgUnit";
	START_LAPTIMER(1760);
	int retval = UTL_GetPatDelayAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1760);
	return retval;
}
void _UTL_UpdatePatDelay( PatDelayHandle  arg1)
{
	MCI_LIST[1761] = "UTL_UpdatePatDelay";
	START_LAPTIMER(1761);
	UTL_UpdatePatDelay( arg1);
	STOP_LAPTIMER(1761);
}
void _UTL_UpdateMpat( MpatHandle arg1)
{
	MCI_LIST[1762] = "UTL_UpdateMpat";
	START_LAPTIMER(1762);
	UTL_UpdateMpat( arg1);
	STOP_LAPTIMER(1762);
}
int _UTL_GetMpatFileName( MpatHandle arg1, char ** arg2)
{
	MCI_LIST[1763] = "UTL_GetMpatFileName";
	START_LAPTIMER(1763);
	int retval = UTL_GetMpatFileName( arg1, arg2);
	STOP_LAPTIMER(1763);
	return retval;
}
int _UTL_GetMpatStartPc( MpatHandle arg1, USlider * arg2)
{
	MCI_LIST[1764] = "UTL_GetMpatStartPc";
	START_LAPTIMER(1764);
	int retval = UTL_GetMpatStartPc( arg1, arg2);
	STOP_LAPTIMER(1764);
	return retval;
}
void _UTL_UpdateAriram( AriramHandle arg1)
{
	MCI_LIST[1765] = "UTL_UpdateAriram";
	START_LAPTIMER(1765);
	UTL_UpdateAriram( arg1);
	STOP_LAPTIMER(1765);
}
int _UTL_GetAriramAlpgUnit( AriramHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1766] = "UTL_GetAriramAlpgUnit";
	START_LAPTIMER(1766);
	int retval = UTL_GetAriramAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1766);
	return retval;
}
int _UTL_GetAriramMode( AriramHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1767] = "UTL_GetAriramMode";
	START_LAPTIMER(1767);
	int retval = UTL_GetAriramMode( arg1, arg2);
	STOP_LAPTIMER(1767);
	return retval;
}
void _UTL_UpdatePdsData( PdsDataHandle  arg1)
{
	MCI_LIST[1768] = "UTL_UpdatePdsData";
	START_LAPTIMER(1768);
	UTL_UpdatePdsData( arg1);
	STOP_LAPTIMER(1768);
}
int _UTL_GetPdsDataAlpgUnit( PdsDataHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1769] = "UTL_GetPdsDataAlpgUnit";
	START_LAPTIMER(1769);
	int retval = UTL_GetPdsDataAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1769);
	return retval;
}
int _UTL_GetPdsDataDirection( PdsDataHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1770] = "UTL_GetPdsDataDirection";
	START_LAPTIMER(1770);
	int retval = UTL_GetPdsDataDirection( arg1, arg2);
	STOP_LAPTIMER(1770);
	return retval;
}
int _UTL_GetPdsDataPdsUnit( PdsDataHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1771] = "UTL_GetPdsDataPdsUnit";
	START_LAPTIMER(1771);
	int retval = UTL_GetPdsDataPdsUnit( arg1, arg2);
	STOP_LAPTIMER(1771);
	return retval;
}
int _UTL_GetPdsDataSelectorDa( PdsDataHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1772] = "UTL_GetPdsDataSelectorDa";
	START_LAPTIMER(1772);
	int retval = UTL_GetPdsDataSelectorDa( arg1, arg2);
	STOP_LAPTIMER(1772);
	return retval;
}
int _UTL_GetPdsDataSelectorDb( PdsDataHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1773] = "UTL_GetPdsDataSelectorDb";
	START_LAPTIMER(1773);
	int retval = UTL_GetPdsDataSelectorDb( arg1, arg2);
	STOP_LAPTIMER(1773);
	return retval;
}
int _UTL_GetPseudoRandomAlpgUnit( PseudoRandomHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1774] = "UTL_GetPseudoRandomAlpgUnit";
	START_LAPTIMER(1774);
	int retval = UTL_GetPseudoRandomAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1774);
	return retval;
}
int _UTL_GetPseudoRandomDirection( PseudoRandomHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1775] = "UTL_GetPseudoRandomDirection";
	START_LAPTIMER(1775);
	int retval = UTL_GetPseudoRandomDirection( arg1, arg2);
	STOP_LAPTIMER(1775);
	return retval;
}
int _UTL_GetPseudoRandomGenerationMethod( PseudoRandomHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1776] = "UTL_GetPseudoRandomGenerationMethod";
	START_LAPTIMER(1776);
	int retval = UTL_GetPseudoRandomGenerationMethod( arg1, arg2);
	STOP_LAPTIMER(1776);
	return retval;
}
int _UTL_GetPseudoRandomUpdateUnitNumber( PseudoRandomHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1777] = "UTL_GetPseudoRandomUpdateUnitNumber";
	START_LAPTIMER(1777);
	int retval = UTL_GetPseudoRandomUpdateUnitNumber( arg1, arg2);
	STOP_LAPTIMER(1777);
	return retval;
}
PseudoRandomTermCursor _UTL_GetPseudoRandomTermCursor( PseudoRandomHandle arg1)
{
	MCI_LIST[1778] = "UTL_GetPseudoRandomTermCursor";
	START_LAPTIMER(1778);
	PseudoRandomTermCursor retval = UTL_GetPseudoRandomTermCursor( arg1);
	STOP_LAPTIMER(1778);
	return retval;
}
RadioButton _UTL_NextPseudoRandomTerm( PseudoRandomTermCursor arg1)
{
	MCI_LIST[1779] = "UTL_NextPseudoRandomTerm";
	START_LAPTIMER(1779);
	RadioButton retval = UTL_NextPseudoRandomTerm( arg1);
	STOP_LAPTIMER(1779);
	return retval;
}
void _UTL_UpdatePseudoRandom( PseudoRandomHandle arg1)
{
	MCI_LIST[1780] = "UTL_UpdatePseudoRandom";
	START_LAPTIMER(1780);
	UTL_UpdatePseudoRandom( arg1);
	STOP_LAPTIMER(1780);
}
void _UTL_UpdateSettlingTime( SettlingTimeHandle arg1)
{
	MCI_LIST[1781] = "UTL_UpdateSettlingTime";
	START_LAPTIMER(1781);
	UTL_UpdateSettlingTime( arg1);
	STOP_LAPTIMER(1781);
}
int _UTL_GetSettlingTime( SettlingTimeHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1782] = "UTL_GetSettlingTime";
	START_LAPTIMER(1782);
	int retval = UTL_GetSettlingTime( arg1, arg2);
	STOP_LAPTIMER(1782);
	return retval;
}
int _UTL_GetSettlingTimeAfterRon( SettlingTimeHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1783] = "UTL_GetSettlingTimeAfterRon";
	START_LAPTIMER(1783);
	int retval = UTL_GetSettlingTimeAfterRon( arg1, arg2);
	STOP_LAPTIMER(1783);
	return retval;
}
int _UTL_GetSettlingTimeAfterRof( SettlingTimeHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1784] = "UTL_GetSettlingTimeAfterRof";
	START_LAPTIMER(1784);
	int retval = UTL_GetSettlingTimeAfterRof( arg1, arg2);
	STOP_LAPTIMER(1784);
	return retval;
}
int _UTL_GetTestAction( TestHandle  arg1, void ** arg2)
{
	MCI_LIST[1785] = "UTL_GetTestAction";
	START_LAPTIMER(1785);
	int retval = UTL_GetTestAction( arg1, arg2);
	STOP_LAPTIMER(1785);
	return retval;
}
int _UTL_GetTestArg( TestHandle  arg1, void ** arg2)
{
	MCI_LIST[1786] = "UTL_GetTestArg";
	START_LAPTIMER(1786);
	int retval = UTL_GetTestArg( arg1, arg2);
	STOP_LAPTIMER(1786);
	return retval;
}
void _UTL_UpdateTrig( TrigHandle arg1)
{
	MCI_LIST[1787] = "UTL_UpdateTrig";
	START_LAPTIMER(1787);
	UTL_UpdateTrig( arg1);
	STOP_LAPTIMER(1787);
}
int _UTL_GetTrigDirection( TrigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1788] = "UTL_GetTrigDirection";
	START_LAPTIMER(1788);
	int retval = UTL_GetTrigDirection( arg1, arg2);
	STOP_LAPTIMER(1788);
	return retval;
}
int _UTL_GetTrigFailDut( TrigHandle  arg1, UT_DUT  arg2, CheckButton * arg3)
{
	MCI_LIST[1789] = "UTL_GetTrigFailDut";
	START_LAPTIMER(1789);
	int retval = UTL_GetTrigFailDut( arg1, arg2, arg3);
	STOP_LAPTIMER(1789);
	return retval;
}
int _UTL_GetTrigOutputCtrl( TrigHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1790] = "UTL_GetTrigOutputCtrl";
	START_LAPTIMER(1790);
	int retval = UTL_GetTrigOutputCtrl( arg1, arg2);
	STOP_LAPTIMER(1790);
	return retval;
}
int _UTL_GetTrigStateMode( TrigHandle  arg1, RadioButton  arg2, CheckButton * arg3)
{
	MCI_LIST[1791] = "UTL_GetTrigStateMode";
	START_LAPTIMER(1791);
	int retval = UTL_GetTrigStateMode( arg1, arg2, arg3);
	STOP_LAPTIMER(1791);
	return retval;
}
int _UTL_GetTrigStateValue( TrigHandle  arg1, RadioButton  arg2, RadioButton  arg3, USlider * arg4)
{
	MCI_LIST[1792] = "UTL_GetTrigStateValue";
	START_LAPTIMER(1792);
	int retval = UTL_GetTrigStateValue( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1792);
	return retval;
}
int _UTL_GetTrigStrbPhase( TrigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1793] = "UTL_GetTrigStrbPhase";
	START_LAPTIMER(1793);
	int retval = UTL_GetTrigStrbPhase( arg1, arg2);
	STOP_LAPTIMER(1793);
	return retval;
}
int _UTL_GetTrigAlpgUnit( TrigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1794] = "UTL_GetTrigAlpgUnit";
	START_LAPTIMER(1794);
	int retval = UTL_GetTrigAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1794);
	return retval;
}
int _UTL_GetTrigMode( TrigHandle arg1, RadioButton arg2, CheckButton * arg3)
{
	MCI_LIST[1795] = "UTL_GetTrigMode";
	START_LAPTIMER(1795);
	int retval = UTL_GetTrigMode( arg1, arg2, arg3);
	STOP_LAPTIMER(1795);
	return retval;
}
void _UTL_UpdateVi( ViHandle arg1, RadioButton arg2)
{
	MCI_LIST[1796] = "UTL_UpdateVi";
	START_LAPTIMER(1796);
	UTL_UpdateVi( arg1, arg2);
	STOP_LAPTIMER(1796);
}
void _UTL_UpdateViPerPin( ViHandle arg1, UT_PIN arg2, UT_DUT arg3)
{
	MCI_LIST[1797] = "UTL_UpdateViPerPin";
	START_LAPTIMER(1797);
	UTL_UpdateViPerPin( arg1, arg2, arg3);
	STOP_LAPTIMER(1797);
}
int _UTL_GetViHigh( ViHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1798] = "UTL_GetViHigh";
	START_LAPTIMER(1798);
	int retval = UTL_GetViHigh( arg1, arg2);
	STOP_LAPTIMER(1798);
	return retval;
}
int _UTL_GetViHvDr( ViHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1799] = "UTL_GetViHvDr";
	START_LAPTIMER(1799);
	int retval = UTL_GetViHvDr( arg1, arg2);
	STOP_LAPTIMER(1799);
	return retval;
}
int _UTL_GetViHvLvDr( ViHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1800] = "UTL_GetViHvLvDr";
	START_LAPTIMER(1800);
	int retval = UTL_GetViHvLvDr( arg1, arg2);
	STOP_LAPTIMER(1800);
	return retval;
}
int _UTL_GetViLow( ViHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1801] = "UTL_GetViLow";
	START_LAPTIMER(1801);
	int retval = UTL_GetViLow( arg1, arg2);
	STOP_LAPTIMER(1801);
	return retval;
}
void _UTL_UpdateVo( VoHandle arg1, RadioButton arg2)
{
	MCI_LIST[1802] = "UTL_UpdateVo";
	START_LAPTIMER(1802);
	UTL_UpdateVo( arg1, arg2);
	STOP_LAPTIMER(1802);
}
int _UTL_GetVoHigh( VoHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1803] = "UTL_GetVoHigh";
	START_LAPTIMER(1803);
	int retval = UTL_GetVoHigh( arg1, arg2);
	STOP_LAPTIMER(1803);
	return retval;
}
int _UTL_GetVoLow( VoHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1804] = "UTL_GetVoLow";
	START_LAPTIMER(1804);
	int retval = UTL_GetVoLow( arg1, arg2);
	STOP_LAPTIMER(1804);
	return retval;
}
void _UTL_UpdateVod( VodHandle arg1, RadioButton arg2)
{
	MCI_LIST[1805] = "UTL_UpdateVod";
	START_LAPTIMER(1805);
	UTL_UpdateVod( arg1, arg2);
	STOP_LAPTIMER(1805);
}
int _UTL_GetVodHigh( VodHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1806] = "UTL_GetVodHigh";
	START_LAPTIMER(1806);
	int retval = UTL_GetVodHigh( arg1, arg2);
	STOP_LAPTIMER(1806);
	return retval;
}
int _UTL_GetVodLow( VodHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1807] = "UTL_GetVodLow";
	START_LAPTIMER(1807);
	int retval = UTL_GetVodLow( arg1, arg2);
	STOP_LAPTIMER(1807);
	return retval;
}
void _UTL_UpdateVs( VsHandle arg1, RadioButton arg2)
{
	MCI_LIST[1808] = "UTL_UpdateVs";
	START_LAPTIMER(1808);
	UTL_UpdateVs( arg1, arg2);
	STOP_LAPTIMER(1808);
}
void _UTL_UpdateVsTargetDut( VsHandle arg1, RadioButton arg2, UT_DUT arg3)
{
	MCI_LIST[1809] = "UTL_UpdateVsTargetDut";
	START_LAPTIMER(1809);
	UTL_UpdateVsTargetDut( arg1, arg2, arg3);
	STOP_LAPTIMER(1809);
}
void _UTL_UpdateVsTargetPps( VsHandle arg1, RadioButton arg2)
{
	MCI_LIST[1810] = "UTL_UpdateVsTargetPps";
	START_LAPTIMER(1810);
	UTL_UpdateVsTargetPps( arg1, arg2);
	STOP_LAPTIMER(1810);
}
int _UTL_GetVsFilter( VsHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1811] = "UTL_GetVsFilter";
	START_LAPTIMER(1811);
	int retval = UTL_GetVsFilter( arg1, arg2);
	STOP_LAPTIMER(1811);
	return retval;
}
int _UTL_GetVsLimitHigh( VsHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1812] = "UTL_GetVsLimitHigh";
	START_LAPTIMER(1812);
	int retval = UTL_GetVsLimitHigh( arg1, arg2);
	STOP_LAPTIMER(1812);
	return retval;
}
int _UTL_GetVsLimitHighDo( VsHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1813] = "UTL_GetVsLimitHighDo";
	START_LAPTIMER(1813);
	int retval = UTL_GetVsLimitHighDo( arg1, arg2);
	STOP_LAPTIMER(1813);
	return retval;
}
int _UTL_GetVsLimitLow( VsHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1814] = "UTL_GetVsLimitLow";
	START_LAPTIMER(1814);
	int retval = UTL_GetVsLimitLow( arg1, arg2);
	STOP_LAPTIMER(1814);
	return retval;
}
int _UTL_GetVsLimitLowDo( VsHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1815] = "UTL_GetVsLimitLowDo";
	START_LAPTIMER(1815);
	int retval = UTL_GetVsLimitLowDo( arg1, arg2);
	STOP_LAPTIMER(1815);
	return retval;
}
int _UTL_GetVsMclamp( VsHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1816] = "UTL_GetVsMclamp";
	START_LAPTIMER(1816);
	int retval = UTL_GetVsMclamp( arg1, arg2);
	STOP_LAPTIMER(1816);
	return retval;
}
int _UTL_GetVsMeasCnt( VsHandle  arg1, Slider * arg2)
{
	MCI_LIST[1817] = "UTL_GetVsMeasCnt";
	START_LAPTIMER(1817);
	int retval = UTL_GetVsMeasCnt( arg1, arg2);
	STOP_LAPTIMER(1817);
	return retval;
}
int _UTL_GetVsMode( VsHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1818] = "UTL_GetVsMode";
	START_LAPTIMER(1818);
	int retval = UTL_GetVsMode( arg1, arg2);
	STOP_LAPTIMER(1818);
	return retval;
}
int _UTL_GetVsMrangeMax( VsHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1819] = "UTL_GetVsMrangeMax";
	START_LAPTIMER(1819);
	int retval = UTL_GetVsMrangeMax( arg1, arg2);
	STOP_LAPTIMER(1819);
	return retval;
}
int _UTL_GetVsMrangeMin( VsHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1820] = "UTL_GetVsMrangeMin";
	START_LAPTIMER(1820);
	int retval = UTL_GetVsMrangeMin( arg1, arg2);
	STOP_LAPTIMER(1820);
	return retval;
}
int _UTL_GetVsPclamp( VsHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1821] = "UTL_GetVsPclamp";
	START_LAPTIMER(1821);
	int retval = UTL_GetVsPclamp( arg1, arg2);
	STOP_LAPTIMER(1821);
	return retval;
}
int _UTL_GetVsPhaseCompensation( VsHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1822] = "UTL_GetVsPhaseCompensation";
	START_LAPTIMER(1822);
	int retval = UTL_GetVsPhaseCompensation( arg1, arg2);
	STOP_LAPTIMER(1822);
	return retval;
}
int _UTL_GetVsHighSpeedSlewRateMode( VsHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1823] = "UTL_GetVsHighSpeedSlewRateMode";
	START_LAPTIMER(1823);
	int retval = UTL_GetVsHighSpeedSlewRateMode( arg1, arg2);
	STOP_LAPTIMER(1823);
	return retval;
}
int _UTL_GetVsSlewRate( VsHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1824] = "UTL_GetVsSlewRate";
	START_LAPTIMER(1824);
	int retval = UTL_GetVsSlewRate( arg1, arg2);
	STOP_LAPTIMER(1824);
	return retval;
}
int _UTL_GetVsSource( VsHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1825] = "UTL_GetVsSource";
	START_LAPTIMER(1825);
	int retval = UTL_GetVsSource( arg1, arg2);
	STOP_LAPTIMER(1825);
	return retval;
}
int _UTL_GetVsSrangeMax( VsHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1826] = "UTL_GetVsSrangeMax";
	START_LAPTIMER(1826);
	int retval = UTL_GetVsSrangeMax( arg1, arg2);
	STOP_LAPTIMER(1826);
	return retval;
}
int _UTL_GetVsSrangeMin( VsHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1827] = "UTL_GetVsSrangeMin";
	START_LAPTIMER(1827);
	int retval = UTL_GetVsSrangeMin( arg1, arg2);
	STOP_LAPTIMER(1827);
	return retval;
}
int _UTL_GetVsWetItem( VsHandle  arg1, RadioButton  arg2, CheckButton * arg3)
{
	MCI_LIST[1828] = "UTL_GetVsWetItem";
	START_LAPTIMER(1828);
	int retval = UTL_GetVsWetItem( arg1, arg2, arg3);
	STOP_LAPTIMER(1828);
	return retval;
}
int _UTL_GetVsParaDrive( VsHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1829] = "UTL_GetVsParaDrive";
	START_LAPTIMER(1829);
	int retval = UTL_GetVsParaDrive( arg1, arg2);
	STOP_LAPTIMER(1829);
	return retval;
}
void _UTL_UpdateVt( VtHandle arg1, RadioButton arg2)
{
	MCI_LIST[1830] = "UTL_UpdateVt";
	START_LAPTIMER(1830);
	UTL_UpdateVt( arg1, arg2);
	STOP_LAPTIMER(1830);
}
int _UTL_GetVt( VtHandle  arg1, DSlider * arg2)
{
	MCI_LIST[1831] = "UTL_GetVt";
	START_LAPTIMER(1831);
	int retval = UTL_GetVt( arg1, arg2);
	STOP_LAPTIMER(1831);
	return retval;
}
int _UTL_GetBbmAccessDut( BbmAccessHandle arg1, UT_DUT * arg2)
{
	MCI_LIST[1832] = "UTL_GetBbmAccessDut";
	START_LAPTIMER(1832);
	int retval = UTL_GetBbmAccessDut( arg1, arg2);
	STOP_LAPTIMER(1832);
	return retval;
}
int _UTL_GetBbmAccessPresetAllMemory( BbmAccessHandle arg1, CheckButton * arg2)
{
	MCI_LIST[1833] = "UTL_GetBbmAccessPresetAllMemory";
	START_LAPTIMER(1833);
	int retval = UTL_GetBbmAccessPresetAllMemory( arg1, arg2);
	STOP_LAPTIMER(1833);
	return retval;
}
int _UTL_GetBbmAccessStartAddr( BbmAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1834] = "UTL_GetBbmAccessStartAddr";
	START_LAPTIMER(1834);
	int retval = UTL_GetBbmAccessStartAddr( arg1, arg2);
	STOP_LAPTIMER(1834);
	return retval;
}
int _UTL_GetBbmAccessStopAddr( BbmAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1835] = "UTL_GetBbmAccessStopAddr";
	START_LAPTIMER(1835);
	int retval = UTL_GetBbmAccessStopAddr( arg1, arg2);
	STOP_LAPTIMER(1835);
	return retval;
}
int _UTL_GetBbmAccessEnableCounter( BbmAccessHandle arg1, RadioButton arg2, CheckButton * arg3)
{
	MCI_LIST[1836] = "UTL_GetBbmAccessEnableCounter";
	START_LAPTIMER(1836);
	int retval = UTL_GetBbmAccessEnableCounter( arg1, arg2, arg3);
	STOP_LAPTIMER(1836);
	return retval;
}
int _UTL_GetBbmAccessCounterNoClear( BbmAccessHandle arg1, RadioButton arg2, CheckButton * arg3)
{
	MCI_LIST[1837] = "UTL_GetBbmAccessCounterNoClear";
	START_LAPTIMER(1837);
	int retval = UTL_GetBbmAccessCounterNoClear( arg1, arg2, arg3);
	STOP_LAPTIMER(1837);
	return retval;
}
void _UTL_UpdateBbmConfig( BbmConfigHandle arg1)
{
	MCI_LIST[1838] = "UTL_UpdateBbmConfig";
	START_LAPTIMER(1838);
	UTL_UpdateBbmConfig( arg1);
	STOP_LAPTIMER(1838);
}
int _UTL_GetBbmConfigAction( BbmConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1839] = "UTL_GetBbmConfigAction";
	START_LAPTIMER(1839);
	int retval = UTL_GetBbmConfigAction( arg1, arg2);
	STOP_LAPTIMER(1839);
	return retval;
}
int _UTL_GetBbmConfigStoreMode( BbmConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1840] = "UTL_GetBbmConfigStoreMode";
	START_LAPTIMER(1840);
	int retval = UTL_GetBbmConfigStoreMode( arg1, arg2);
	STOP_LAPTIMER(1840);
	return retval;
}
int _UTL_GetBbmConfigCaptureSignal( BbmConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1841] = "UTL_GetBbmConfigCaptureSignal";
	START_LAPTIMER(1841);
	int retval = UTL_GetBbmConfigCaptureSignal( arg1, arg2);
	STOP_LAPTIMER(1841);
	return retval;
}
int _UTL_GetBbmConfigAddrAssign( BbmConfigHandle arg1, RadioButton arg2, RadioButton * arg3)
{
	MCI_LIST[1842] = "UTL_GetBbmConfigAddrAssign";
	START_LAPTIMER(1842);
	int retval = UTL_GetBbmConfigAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(1842);
	return retval;
}
int _UTL_GetBbmConfigBbcLimit( BbmConfigHandle arg1, UT_DUT arg2, USlider * arg3)
{
	MCI_LIST[1843] = "UTL_GetBbmConfigBbcLimit";
	START_LAPTIMER(1843);
	int retval = UTL_GetBbmConfigBbcLimit( arg1, arg2, arg3);
	STOP_LAPTIMER(1843);
	return retval;
}
int _UTL_GetBbmConfigMode( BbmConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1844] = "UTL_GetBbmConfigMode";
	START_LAPTIMER(1844);
	int retval = UTL_GetBbmConfigMode( arg1, arg2);
	STOP_LAPTIMER(1844);
	return retval;
}
int _UTL_GetBbmConfigWriteEnable( BbmConfigHandle arg1, UT_DUT arg2, CheckButton * arg3)
{
	MCI_LIST[1845] = "UTL_GetBbmConfigWriteEnable";
	START_LAPTIMER(1845);
	int retval = UTL_GetBbmConfigWriteEnable( arg1, arg2, arg3);
	STOP_LAPTIMER(1845);
	return retval;
}
int _UTL_GetBbmConfigSkipSignal( BbmConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1846] = "UTL_GetBbmConfigSkipSignal";
	START_LAPTIMER(1846);
	int retval = UTL_GetBbmConfigSkipSignal( arg1, arg2);
	STOP_LAPTIMER(1846);
	return retval;
}
int _UTL_GetBbmConfigCounterNoClear( BbmConfigHandle arg1, RadioButton arg2, CheckButton * arg3)
{
	MCI_LIST[1847] = "UTL_GetBbmConfigCounterNoClear";
	START_LAPTIMER(1847);
	int retval = UTL_GetBbmConfigCounterNoClear( arg1, arg2, arg3);
	STOP_LAPTIMER(1847);
	return retval;
}
int _UTL_GetBbmConfigPlaneCount( BbmConfigHandle arg1, USlider * arg2)
{
	MCI_LIST[1848] = "UTL_GetBbmConfigPlaneCount";
	START_LAPTIMER(1848);
	int retval = UTL_GetBbmConfigPlaneCount( arg1, arg2);
	STOP_LAPTIMER(1848);
	return retval;
}
int _UTL_GetCfbmAccessAddrBlock( CfbmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[1849] = "UTL_GetCfbmAccessAddrBlock";
	START_LAPTIMER(1849);
	int retval = UTL_GetCfbmAccessAddrBlock( arg1, arg2);
	STOP_LAPTIMER(1849);
	return retval;
}
int _UTL_GetCfbmAccessAddrEndPointer( CfbmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[1850] = "UTL_GetCfbmAccessAddrEndPointer";
	START_LAPTIMER(1850);
	int retval = UTL_GetCfbmAccessAddrEndPointer( arg1, arg2);
	STOP_LAPTIMER(1850);
	return retval;
}
int _UTL_GetCfbmAccessAddrStartPointer( CfbmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[1851] = "UTL_GetCfbmAccessAddrStartPointer";
	START_LAPTIMER(1851);
	int retval = UTL_GetCfbmAccessAddrStartPointer( arg1, arg2);
	STOP_LAPTIMER(1851);
	return retval;
}
int _UTL_GetCfbmAccessPresetAllMemory( CfbmAccessHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1852] = "UTL_GetCfbmAccessPresetAllMemory";
	START_LAPTIMER(1852);
	int retval = UTL_GetCfbmAccessPresetAllMemory( arg1, arg2);
	STOP_LAPTIMER(1852);
	return retval;
}
int _UTL_GetCfbmConfigAddrAssign( CfbmConfigHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[1853] = "UTL_GetCfbmConfigAddrAssign";
	START_LAPTIMER(1853);
	int retval = UTL_GetCfbmConfigAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(1853);
	return retval;
}
int _UTL_GetCfbmConfigCompressMode( CfbmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1854] = "UTL_GetCfbmConfigCompressMode";
	START_LAPTIMER(1854);
	int retval = UTL_GetCfbmConfigCompressMode( arg1, arg2);
	STOP_LAPTIMER(1854);
	return retval;
}
int _UTL_GetCfbmConfigEndXAddr( CfbmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1855] = "UTL_GetCfbmConfigEndXAddr";
	START_LAPTIMER(1855);
	int retval = UTL_GetCfbmConfigEndXAddr( arg1, arg2);
	STOP_LAPTIMER(1855);
	return retval;
}
int _UTL_GetCfbmConfigEndYAddr( CfbmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1856] = "UTL_GetCfbmConfigEndYAddr";
	START_LAPTIMER(1856);
	int retval = UTL_GetCfbmConfigEndYAddr( arg1, arg2);
	STOP_LAPTIMER(1856);
	return retval;
}
int _UTL_GetCfbmConfigEndZAddr( CfbmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1857] = "UTL_GetCfbmConfigEndZAddr";
	START_LAPTIMER(1857);
	int retval = UTL_GetCfbmConfigEndZAddr( arg1, arg2);
	STOP_LAPTIMER(1857);
	return retval;
}
int _UTL_GetCfbmConfigSelectBit( CfbmConfigHandle  arg1, USlider  arg2, USlider * arg3)
{
	MCI_LIST[1858] = "UTL_GetCfbmConfigSelectBit";
	START_LAPTIMER(1858);
	int retval = UTL_GetCfbmConfigSelectBit( arg1, arg2, arg3);
	STOP_LAPTIMER(1858);
	return retval;
}
int _UTL_GetCfbmConfigSelectBitDut( CfbmConfigHandle  arg1, USlider  arg2, UT_DUT * arg3)
{
	MCI_LIST[1859] = "UTL_GetCfbmConfigSelectBitDut";
	START_LAPTIMER(1859);
	int retval = UTL_GetCfbmConfigSelectBitDut( arg1, arg2, arg3);
	STOP_LAPTIMER(1859);
	return retval;
}
int _UTL_GetCfbmConfigSplitMemory( CfbmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1860] = "UTL_GetCfbmConfigSplitMemory";
	START_LAPTIMER(1860);
	int retval = UTL_GetCfbmConfigSplitMemory( arg1, arg2);
	STOP_LAPTIMER(1860);
	return retval;
}
int _UTL_GetCfbmConfigStartXAddr( CfbmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1861] = "UTL_GetCfbmConfigStartXAddr";
	START_LAPTIMER(1861);
	int retval = UTL_GetCfbmConfigStartXAddr( arg1, arg2);
	STOP_LAPTIMER(1861);
	return retval;
}
int _UTL_GetCfbmConfigStartYAddr( CfbmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1862] = "UTL_GetCfbmConfigStartYAddr";
	START_LAPTIMER(1862);
	int retval = UTL_GetCfbmConfigStartYAddr( arg1, arg2);
	STOP_LAPTIMER(1862);
	return retval;
}
int _UTL_GetCfbmConfigStartZAddr( CfbmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1863] = "UTL_GetCfbmConfigStartZAddr";
	START_LAPTIMER(1863);
	int retval = UTL_GetCfbmConfigStartZAddr( arg1, arg2);
	STOP_LAPTIMER(1863);
	return retval;
}
int _UTL_GetDctReadPinDut( DctReadPinHandle  arg1, UT_DUT  arg2, CheckButton * arg3)
{
	MCI_LIST[1864] = "UTL_GetDctReadPinDut";
	START_LAPTIMER(1864);
	int retval = UTL_GetDctReadPinDut( arg1, arg2, arg3);
	STOP_LAPTIMER(1864);
	return retval;
}
int _UTL_GetDctReadPinMode( DctReadPinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1865] = "UTL_GetDctReadPinMode";
	START_LAPTIMER(1865);
	int retval = UTL_GetDctReadPinMode( arg1, arg2);
	STOP_LAPTIMER(1865);
	return retval;
}
int _UTL_GetDctReadPinNumber( DctReadPinHandle  arg1, UT_PIN * arg2)
{
	MCI_LIST[1866] = "UTL_GetDctReadPinNumber";
	START_LAPTIMER(1866);
	int retval = UTL_GetDctReadPinNumber( arg1, arg2);
	STOP_LAPTIMER(1866);
	return retval;
}
int _UTL_GetDctReadPinType( DctReadPinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1867] = "UTL_GetDctReadPinType";
	START_LAPTIMER(1867);
	int retval = UTL_GetDctReadPinType( arg1, arg2);
	STOP_LAPTIMER(1867);
	return retval;
}
int _UTL_GetDctReadPinHistoryNumber( DctReadPinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1868] = "UTL_GetDctReadPinHistoryNumber";
	START_LAPTIMER(1868);
	int retval = UTL_GetDctReadPinHistoryNumber( arg1, arg2);
	STOP_LAPTIMER(1868);
	return retval;
}
int _UTL_GetFcmAccessAction( FcmAccessHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1869] = "UTL_GetFcmAccessAction";
	START_LAPTIMER(1869);
	int retval = UTL_GetFcmAccessAction( arg1, arg2);
	STOP_LAPTIMER(1869);
	return retval;
}
int _UTL_GetFcmAccessAutoAddrAssignMode( FcmAccessHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1870] = "UTL_GetFcmAccessAutoAddrAssignMode";
	START_LAPTIMER(1870);
	int retval = UTL_GetFcmAccessAutoAddrAssignMode( arg1, arg2);
	STOP_LAPTIMER(1870);
	return retval;
}
int _UTL_GetFcmAccessAddrAssign( FcmAccessHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[1871] = "UTL_GetFcmAccessAddrAssign";
	START_LAPTIMER(1871);
	int retval = UTL_GetFcmAccessAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(1871);
	return retval;
}
int _UTL_GetFcmAccessAddrAssignByFcmConfig( FcmAccessHandle  arg1, FcmConfigHandle  arg2, RadioButton  arg3, RadioButton  arg4, RadioButton * arg5)
{
	MCI_LIST[1872] = "UTL_GetFcmAccessAddrAssignByFcmConfig";
	START_LAPTIMER(1872);
	int retval = UTL_GetFcmAccessAddrAssignByFcmConfig( arg1, arg2, arg3, arg4, arg5);
	STOP_LAPTIMER(1872);
	return retval;
}
int _UTL_GetFcmAccessAllBit( FcmAccessHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1873] = "UTL_GetFcmAccessAllBit";
	START_LAPTIMER(1873);
	int retval = UTL_GetFcmAccessAllBit( arg1, arg2);
	STOP_LAPTIMER(1873);
	return retval;
}
int _UTL_GetFcmAccessAllDut( FcmAccessHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1874] = "UTL_GetFcmAccessAllDut";
	START_LAPTIMER(1874);
	int retval = UTL_GetFcmAccessAllDut( arg1, arg2);
	STOP_LAPTIMER(1874);
	return retval;
}
FcmAccessBitCursor _UTL_GetFcmAccessBitCursor( FcmAccessHandle  arg1)
{
	MCI_LIST[1875] = "UTL_GetFcmAccessBitCursor";
	START_LAPTIMER(1875);
	FcmAccessBitCursor retval = UTL_GetFcmAccessBitCursor( arg1);
	STOP_LAPTIMER(1875);
	return retval;
}
RadioButton _UTL_NextFcmAccessBit( FcmAccessBitCursor  arg1)
{
	MCI_LIST[1876] = "UTL_NextFcmAccessBit";
	START_LAPTIMER(1876);
	RadioButton retval = UTL_NextFcmAccessBit( arg1);
	STOP_LAPTIMER(1876);
	return retval;
}
int _UTL_GetFcmAccessDut( FcmAccessHandle  arg1, UT_DUT * arg2)
{
	MCI_LIST[1877] = "UTL_GetFcmAccessDut";
	START_LAPTIMER(1877);
	int retval = UTL_GetFcmAccessDut( arg1, arg2);
	STOP_LAPTIMER(1877);
	return retval;
}
int _UTL_GetFcmAccessEndXAddr( FcmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[1878] = "UTL_GetFcmAccessEndXAddr";
	START_LAPTIMER(1878);
	int retval = UTL_GetFcmAccessEndXAddr( arg1, arg2);
	STOP_LAPTIMER(1878);
	return retval;
}
int _UTL_GetFcmAccessEndYAddr( FcmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[1879] = "UTL_GetFcmAccessEndYAddr";
	START_LAPTIMER(1879);
	int retval = UTL_GetFcmAccessEndYAddr( arg1, arg2);
	STOP_LAPTIMER(1879);
	return retval;
}
int _UTL_GetFcmAccessEndZAddr( FcmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[1880] = "UTL_GetFcmAccessEndZAddr";
	START_LAPTIMER(1880);
	int retval = UTL_GetFcmAccessEndZAddr( arg1, arg2);
	STOP_LAPTIMER(1880);
	return retval;
}
int _UTL_GetFcmAccessPresetAllMemory( FcmAccessHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1881] = "UTL_GetFcmAccessPresetAllMemory";
	START_LAPTIMER(1881);
	int retval = UTL_GetFcmAccessPresetAllMemory( arg1, arg2);
	STOP_LAPTIMER(1881);
	return retval;
}
int _UTL_GetFcmAccessPresetIgnoreAddr( FcmAccessHandle arg1, CheckButton * arg2)
{
	MCI_LIST[1882] = "UTL_GetFcmAccessPresetIgnoreAddr";
	START_LAPTIMER(1882);
	int retval = UTL_GetFcmAccessPresetIgnoreAddr( arg1, arg2);
	STOP_LAPTIMER(1882);
	return retval;
}
int _UTL_GetFcmAccessPresetPreserveFbm( FcmAccessHandle arg1, CheckButton * arg2)
{
	MCI_LIST[1883] = "UTL_GetFcmAccessPresetPreserveFbm";
	START_LAPTIMER(1883);
	int retval = UTL_GetFcmAccessPresetPreserveFbm( arg1, arg2);
	STOP_LAPTIMER(1883);
	return retval;
}
int _UTL_GetFcmAccessSearchMaxCnt( FcmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[1884] = "UTL_GetFcmAccessSearchMaxCnt";
	START_LAPTIMER(1884);
	int retval = UTL_GetFcmAccessSearchMaxCnt( arg1, arg2);
	STOP_LAPTIMER(1884);
	return retval;
}
int _UTL_GetFcmAccessStartXAddr( FcmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[1885] = "UTL_GetFcmAccessStartXAddr";
	START_LAPTIMER(1885);
	int retval = UTL_GetFcmAccessStartXAddr( arg1, arg2);
	STOP_LAPTIMER(1885);
	return retval;
}
int _UTL_GetFcmAccessStartYAddr( FcmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[1886] = "UTL_GetFcmAccessStartYAddr";
	START_LAPTIMER(1886);
	int retval = UTL_GetFcmAccessStartYAddr( arg1, arg2);
	STOP_LAPTIMER(1886);
	return retval;
}
int _UTL_GetFcmAccessStartZAddr( FcmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[1887] = "UTL_GetFcmAccessStartZAddr";
	START_LAPTIMER(1887);
	int retval = UTL_GetFcmAccessStartZAddr( arg1, arg2);
	STOP_LAPTIMER(1887);
	return retval;
}
int _UTL_GetFcmAccessAlpgUnit( FcmAccessHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1888] = "UTL_GetFcmAccessAlpgUnit";
	START_LAPTIMER(1888);
	int retval = UTL_GetFcmAccessAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1888);
	return retval;
}
int _UTL_GetFcmAccessActionNumber( FcmAccessHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[1889] = "UTL_GetFcmAccessActionNumber";
	START_LAPTIMER(1889);
	int retval = UTL_GetFcmAccessActionNumber( arg1, arg2, arg3);
	STOP_LAPTIMER(1889);
	return retval;
}
int _UTL_GetFcmAccessCompactionMode( FcmAccessHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1890] = "UTL_GetFcmAccessCompactionMode";
	START_LAPTIMER(1890);
	int retval = UTL_GetFcmAccessCompactionMode( arg1, arg2);
	STOP_LAPTIMER(1890);
	return retval;
}
int _UTL_GetFcmAccessBitMode( FcmAccessHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1891] = "UTL_GetFcmAccessBitMode";
	START_LAPTIMER(1891);
	int retval = UTL_GetFcmAccessBitMode( arg1, arg2);
	STOP_LAPTIMER(1891);
	return retval;
}
int _UTL_GetFcmAccessBitBlock( FcmAccessHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1892] = "UTL_GetFcmAccessBitBlock";
	START_LAPTIMER(1892);
	int retval = UTL_GetFcmAccessBitBlock( arg1, arg2);
	STOP_LAPTIMER(1892);
	return retval;
}
int _UTL_GetFcmAccessApLink( FcmAccessHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1893] = "UTL_GetFcmAccessApLink";
	START_LAPTIMER(1893);
	int retval = UTL_GetFcmAccessApLink( arg1, arg2);
	STOP_LAPTIMER(1893);
	return retval;
}
int _UTL_GetFcmAccessSparePackageMode( FcmAccessHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1894] = "UTL_GetFcmAccessSparePackageMode";
	START_LAPTIMER(1894);
	int retval = UTL_GetFcmAccessSparePackageMode( arg1, arg2);
	STOP_LAPTIMER(1894);
	return retval;
}
int _UTL_GetFcmAccessSpareAddrAssign( FcmAccessHandle  arg1, RadioButton  arg2, RadioButton  arg3, RadioButton * arg4)
{
	MCI_LIST[1895] = "UTL_GetFcmAccessSpareAddrAssign";
	START_LAPTIMER(1895);
	int retval = UTL_GetFcmAccessSpareAddrAssign( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1895);
	return retval;
}
int _UTL_GetFcmAccessPfcMode( FcmAccessHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1896] = "UTL_GetFcmAccessPfcMode";
	START_LAPTIMER(1896);
	int retval = UTL_GetFcmAccessPfcMode( arg1, arg2);
	STOP_LAPTIMER(1896);
	return retval;
}
int _UTL_GetFcmAccessPfcNoClear( FcmAccessHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1897] = "UTL_GetFcmAccessPfcNoClear";
	START_LAPTIMER(1897);
	int retval = UTL_GetFcmAccessPfcNoClear( arg1, arg2);
	STOP_LAPTIMER(1897);
	return retval;
}
int _UTL_GetFcmAccessAreaDivision( FcmAccessHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[1898] = "UTL_GetFcmAccessAreaDivision";
	START_LAPTIMER(1898);
	int retval = UTL_GetFcmAccessAreaDivision( arg1, arg2, arg3);
	STOP_LAPTIMER(1898);
	return retval;
}
void _UTL_UpdateFcmConfig( FcmConfigHandle arg1)
{
	MCI_LIST[1899] = "UTL_UpdateFcmConfig";
	START_LAPTIMER(1899);
	UTL_UpdateFcmConfig( arg1);
	STOP_LAPTIMER(1899);
}
int _UTL_GetFcmConfigMultiMode( FcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1900] = "UTL_GetFcmConfigMultiMode";
	START_LAPTIMER(1900);
	int retval = UTL_GetFcmConfigMultiMode( arg1, arg2);
	STOP_LAPTIMER(1900);
	return retval;
}
int _UTL_GetFcmConfigDut( FcmConfigHandle  arg1, UT_DUT * arg2)
{
	MCI_LIST[1901] = "UTL_GetFcmConfigDut";
	START_LAPTIMER(1901);
	int retval = UTL_GetFcmConfigDut( arg1, arg2);
	STOP_LAPTIMER(1901);
	return retval;
}
USlider _UTL_ReadFcmConfigGroupCount( FcmConfigHandle arg1)
{
	MCI_LIST[1902] = "UTL_ReadFcmConfigGroupCount";
	START_LAPTIMER(1902);
	USlider retval = UTL_ReadFcmConfigGroupCount( arg1);
	STOP_LAPTIMER(1902);
	return retval;
}
USlider _UTL_ReadFcmConfigGroupDutCount( FcmConfigHandle arg1)
{
	MCI_LIST[1903] = "UTL_ReadFcmConfigGroupDutCount";
	START_LAPTIMER(1903);
	USlider retval = UTL_ReadFcmConfigGroupDutCount( arg1);
	STOP_LAPTIMER(1903);
	return retval;
}
DutCursor _UTL_GetFcmConfigGroupDutCursor( FcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1904] = "UTL_GetFcmConfigGroupDutCursor";
	START_LAPTIMER(1904);
	DutCursor retval = UTL_GetFcmConfigGroupDutCursor( arg1, arg2);
	STOP_LAPTIMER(1904);
	return retval;
}
DutCursor _UTL_GetFcmConfigDutCursor()
{
	MCI_LIST[1905] = "UTL_GetFcmConfigDutCursor";
	START_LAPTIMER(1905);
	DutCursor retval = UTL_GetFcmConfigDutCursor();
	STOP_LAPTIMER(1905);
	return retval;
}
int _UTL_GetFcmConfigBitSize( FcmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1906] = "UTL_GetFcmConfigBitSize";
	START_LAPTIMER(1906);
	int retval = UTL_GetFcmConfigBitSize( arg1, arg2);
	STOP_LAPTIMER(1906);
	return retval;
}
int _UTL_GetFcmConfigDutBitSize( FcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1907] = "UTL_GetFcmConfigDutBitSize";
	START_LAPTIMER(1907);
	int retval = UTL_GetFcmConfigDutBitSize( arg1, arg2);
	STOP_LAPTIMER(1907);
	return retval;
}
int _UTL_GetFcmConfigAddrAssign( FcmConfigHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[1908] = "UTL_GetFcmConfigAddrAssign";
	START_LAPTIMER(1908);
	int retval = UTL_GetFcmConfigAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(1908);
	return retval;
}
int _UTL_GetFcmConfigSplitAddrAssign( FcmConfigHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[1909] = "UTL_GetFcmConfigSplitAddrAssign";
	START_LAPTIMER(1909);
	int retval = UTL_GetFcmConfigSplitAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(1909);
	return retval;
}
int _UTL_GetFcmConfigAddrAssignByAlpg( FcmConfigHandle  arg1, RadioButton  arg2, RadioButton  arg3, RadioButton * arg4)
{
	MCI_LIST[1910] = "UTL_GetFcmConfigAddrAssignByAlpg";
	START_LAPTIMER(1910);
	int retval = UTL_GetFcmConfigAddrAssignByAlpg( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1910);
	return retval;
}
int _UTL_GetFcmConfigMaxAddrBitNum( FcmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1911] = "UTL_GetFcmConfigMaxAddrBitNum";
	START_LAPTIMER(1911);
	int retval = UTL_GetFcmConfigMaxAddrBitNum( arg1, arg2);
	STOP_LAPTIMER(1911);
	return retval;
}
int _UTL_GetFcmConfigAlpgUnit( FcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1912] = "UTL_GetFcmConfigAlpgUnit";
	START_LAPTIMER(1912);
	int retval = UTL_GetFcmConfigAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(1912);
	return retval;
}
PinCursor _UTL_GetFcmConfigPinAssign( FcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1913] = "UTL_GetFcmConfigPinAssign";
	START_LAPTIMER(1913);
	PinCursor retval = UTL_GetFcmConfigPinAssign( arg1, arg2);
	STOP_LAPTIMER(1913);
	return retval;
}
int _UTL_GetFcmConfigPinAssignTarget( FcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1914] = "UTL_GetFcmConfigPinAssignTarget";
	START_LAPTIMER(1914);
	int retval = UTL_GetFcmConfigPinAssignTarget( arg1, arg2);
	STOP_LAPTIMER(1914);
	return retval;
}
PinCursor _UTL_GetFcmConfigMaskPinAssign( FcmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[1915] = "UTL_GetFcmConfigMaskPinAssign";
	START_LAPTIMER(1915);
	PinCursor retval = UTL_GetFcmConfigMaskPinAssign( arg1, arg2);
	STOP_LAPTIMER(1915);
	return retval;
}
FcmConfigBitSelectCursor _UTL_GetFcmConfigBitSelectCursor( FcmConfigHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[1916] = "UTL_GetFcmConfigBitSelectCursor";
	START_LAPTIMER(1916);
	FcmConfigBitSelectCursor retval = UTL_GetFcmConfigBitSelectCursor( arg1, arg2);
	STOP_LAPTIMER(1916);
	return retval;
}
RadioButton _UTL_NextFcmConfigBitSelect( FcmConfigBitSelectCursor  arg1)
{
	MCI_LIST[1917] = "UTL_NextFcmConfigBitSelect";
	START_LAPTIMER(1917);
	RadioButton retval = UTL_NextFcmConfigBitSelect( arg1);
	STOP_LAPTIMER(1917);
	return retval;
}
int _UTL_GetFcmConfigBitSelectTarget( FcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1918] = "UTL_GetFcmConfigBitSelectTarget";
	START_LAPTIMER(1918);
	int retval = UTL_GetFcmConfigBitSelectTarget( arg1, arg2);
	STOP_LAPTIMER(1918);
	return retval;
}
int _UTL_GetFcmConfigStoreSignal( FcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1919] = "UTL_GetFcmConfigStoreSignal";
	START_LAPTIMER(1919);
	int retval = UTL_GetFcmConfigStoreSignal( arg1, arg2);
	STOP_LAPTIMER(1919);
	return retval;
}
int _UTL_GetFcmConfigStoreSignalByMMType( FcmConfigHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[1920] = "UTL_GetFcmConfigStoreSignalByMMType";
	START_LAPTIMER(1920);
	int retval = UTL_GetFcmConfigStoreSignalByMMType( arg1, arg2, arg3);
	STOP_LAPTIMER(1920);
	return retval;
}
int _UTL_GetFcmConfigStoreInhSignal( FcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1921] = "UTL_GetFcmConfigStoreInhSignal";
	START_LAPTIMER(1921);
	int retval = UTL_GetFcmConfigStoreInhSignal( arg1, arg2);
	STOP_LAPTIMER(1921);
	return retval;
}
int _UTL_GetFcmConfigAddrScram( FcmConfigHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1922] = "UTL_GetFcmConfigAddrScram";
	START_LAPTIMER(1922);
	int retval = UTL_GetFcmConfigAddrScram( arg1, arg2);
	STOP_LAPTIMER(1922);
	return retval;
}
int _UTL_GetFcmConfigAddrScramByAlpg( FcmConfigHandle  arg1, RadioButton  arg2, CheckButton * arg3)
{
	MCI_LIST[1923] = "UTL_GetFcmConfigAddrScramByAlpg";
	START_LAPTIMER(1923);
	int retval = UTL_GetFcmConfigAddrScramByAlpg( arg1, arg2, arg3);
	STOP_LAPTIMER(1923);
	return retval;
}
int _UTL_GetFcmConfigAction( FcmConfigHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[1924] = "UTL_GetFcmConfigAction";
	START_LAPTIMER(1924);
	int retval = UTL_GetFcmConfigAction( arg1, arg2, arg3);
	STOP_LAPTIMER(1924);
	return retval;
}
int _UTL_GetFcmConfigMaxActionNum( FcmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1925] = "UTL_GetFcmConfigMaxActionNum";
	START_LAPTIMER(1925);
	int retval = UTL_GetFcmConfigMaxActionNum( arg1, arg2);
	STOP_LAPTIMER(1925);
	return retval;
}
FcmConfigStrbChannelCursor _UTL_GetFcmConfigStrbChannelCursor( FcmConfigHandle  arg1, RadioButton  arg2, RadioButton  arg3, RadioButton  arg4)
{
	MCI_LIST[1926] = "UTL_GetFcmConfigStrbChannelCursor";
	START_LAPTIMER(1926);
	FcmConfigStrbChannelCursor retval = UTL_GetFcmConfigStrbChannelCursor( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1926);
	return retval;
}
RadioButton _UTL_NextFcmConfigStrbChannel( FcmConfigStrbChannelCursor  arg1)
{
	MCI_LIST[1927] = "UTL_NextFcmConfigStrbChannel";
	START_LAPTIMER(1927);
	RadioButton retval = UTL_NextFcmConfigStrbChannel( arg1);
	STOP_LAPTIMER(1927);
	return retval;
}
int _UTL_GetFcmConfigRate( FcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1928] = "UTL_GetFcmConfigRate";
	START_LAPTIMER(1928);
	int retval = UTL_GetFcmConfigRate( arg1, arg2);
	STOP_LAPTIMER(1928);
	return retval;
}
int _UTL_GetFcmConfigDelay( FcmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1929] = "UTL_GetFcmConfigDelay";
	START_LAPTIMER(1929);
	int retval = UTL_GetFcmConfigDelay( arg1, arg2);
	STOP_LAPTIMER(1929);
	return retval;
}
int _UTL_GetFcmConfigDelayByAlpg( FcmConfigHandle  arg1, RadioButton  arg2, USlider * arg3)
{
	MCI_LIST[1930] = "UTL_GetFcmConfigDelayByAlpg";
	START_LAPTIMER(1930);
	int retval = UTL_GetFcmConfigDelayByAlpg( arg1, arg2, arg3);
	STOP_LAPTIMER(1930);
	return retval;
}
int _UTL_GetFcmConfigModeDelayByAlpg( FcmConfigHandle  arg1, RadioButton  arg2, RadioButton  arg3, USlider * arg4)
{
	MCI_LIST[1931] = "UTL_GetFcmConfigModeDelayByAlpg";
	START_LAPTIMER(1931);
	int retval = UTL_GetFcmConfigModeDelayByAlpg( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1931);
	return retval;
}
int _UTL_GetFcmConfigSparePackageMode( FcmConfigHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1932] = "UTL_GetFcmConfigSparePackageMode";
	START_LAPTIMER(1932);
	int retval = UTL_GetFcmConfigSparePackageMode( arg1, arg2);
	STOP_LAPTIMER(1932);
	return retval;
}
int _UTL_GetFcmConfigSpareAddrAssign( FcmConfigHandle  arg1, RadioButton  arg2, RadioButton  arg3, RadioButton * arg4)
{
	MCI_LIST[1933] = "UTL_GetFcmConfigSpareAddrAssign";
	START_LAPTIMER(1933);
	int retval = UTL_GetFcmConfigSpareAddrAssign( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1933);
	return retval;
}
int _UTL_GetFcmConfigDdrMode( FcmConfigHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1934] = "UTL_GetFcmConfigDdrMode";
	START_LAPTIMER(1934);
	int retval = UTL_GetFcmConfigDdrMode( arg1, arg2);
	STOP_LAPTIMER(1934);
	return retval;
}
int _UTL_GetFcmConfigExMode( FcmConfigHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1935] = "UTL_GetFcmConfigExMode";
	START_LAPTIMER(1935);
	int retval = UTL_GetFcmConfigExMode( arg1, arg2);
	STOP_LAPTIMER(1935);
	return retval;
}
int _UTL_GetFcmConfigPfcNoClear( FcmConfigHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1936] = "UTL_GetFcmConfigPfcNoClear";
	START_LAPTIMER(1936);
	int retval = UTL_GetFcmConfigPfcNoClear( arg1, arg2);
	STOP_LAPTIMER(1936);
	return retval;
}
int _UTL_GetFcmConfigScramEnableStartAddrBit( FcmConfigHandle arg1, USlider * arg2)
{
	MCI_LIST[1937] = "UTL_GetFcmConfigScramEnableStartAddrBit";
	START_LAPTIMER(1937);
	int retval = UTL_GetFcmConfigScramEnableStartAddrBit( arg1, arg2);
	STOP_LAPTIMER(1937);
	return retval;
}
int _UTL_GetFcmConfigBurstCaptureLength( FcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1938] = "UTL_GetFcmConfigBurstCaptureLength";
	START_LAPTIMER(1938);
	int retval = UTL_GetFcmConfigBurstCaptureLength( arg1, arg2);
	STOP_LAPTIMER(1938);
	return retval;
}
int _UTL_GetFcmConfigRealTimeCountEnable( FcmConfigHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1939] = "UTL_GetFcmConfigRealTimeCountEnable";
	START_LAPTIMER(1939);
	int retval = UTL_GetFcmConfigRealTimeCountEnable( arg1, arg2);
	STOP_LAPTIMER(1939);
	return retval;
}
int _UTL_GetFcmConfigFcsmMaxStoreCnt( FcmConfigHandle arg1, USlider * arg2)
{
	MCI_LIST[1940] = "UTL_GetFcmConfigFcsmMaxStoreCnt";
	START_LAPTIMER(1940);
	int retval = UTL_GetFcmConfigFcsmMaxStoreCnt( arg1, arg2);
	STOP_LAPTIMER(1940);
	return retval;
}
FcmConfigAreaDivisionBitCursor _UTL_GetFcmConfigAreaDivisionBitCursor( FcmConfigHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[1941] = "UTL_GetFcmConfigAreaDivisionBitCursor";
	START_LAPTIMER(1941);
	FcmConfigAreaDivisionBitCursor retval = UTL_GetFcmConfigAreaDivisionBitCursor( arg1, arg2);
	STOP_LAPTIMER(1941);
	return retval;
}
RadioButton _UTL_NextFcmConfigAreaDivisionBit( FcmConfigAreaDivisionBitCursor  arg1)
{
	MCI_LIST[1942] = "UTL_NextFcmConfigAreaDivisionBit";
	START_LAPTIMER(1942);
	RadioButton retval = UTL_NextFcmConfigAreaDivisionBit( arg1);
	STOP_LAPTIMER(1942);
	return retval;
}
int _UTL_GetFasmAccessStartAddr( FasmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[1943] = "UTL_GetFasmAccessStartAddr";
	START_LAPTIMER(1943);
	int retval = UTL_GetFasmAccessStartAddr( arg1, arg2);
	STOP_LAPTIMER(1943);
	return retval;
}
int _UTL_GetFasmAccessStopAddr( FasmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[1944] = "UTL_GetFasmAccessStopAddr";
	START_LAPTIMER(1944);
	int retval = UTL_GetFasmAccessStopAddr( arg1, arg2);
	STOP_LAPTIMER(1944);
	return retval;
}
int _UTL_GetFasmAccessBitBlock( FasmAccessHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1945] = "UTL_GetFasmAccessBitBlock";
	START_LAPTIMER(1945);
	int retval = UTL_GetFasmAccessBitBlock( arg1, arg2);
	STOP_LAPTIMER(1945);
	return retval;
}
void _UTL_UpdateEccConfig( EccConfigHandle arg1)
{
	MCI_LIST[1946] = "UTL_UpdateEccConfig";
	START_LAPTIMER(1946);
	UTL_UpdateEccConfig( arg1);
	STOP_LAPTIMER(1946);
}
int _UTL_GetEccConfigCounterNoClear( EccConfigHandle arg1, CheckButton * arg2)
{
	MCI_LIST[1947] = "UTL_GetEccConfigCounterNoClear";
	START_LAPTIMER(1947);
	int retval = UTL_GetEccConfigCounterNoClear( arg1, arg2);
	STOP_LAPTIMER(1947);
	return retval;
}
int _UTL_GetEccConfigCounterLimit( EccConfigHandle arg1, RadioButton arg2, RadioButton arg3, USlider * arg4)
{
	MCI_LIST[1948] = "UTL_GetEccConfigCounterLimit";
	START_LAPTIMER(1948);
	int retval = UTL_GetEccConfigCounterLimit( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(1948);
	return retval;
}
int _UTL_GetEccConfigCounterEnableSignal( EccConfigHandle arg1, RadioButton arg2, RadioButton * arg3)
{
	MCI_LIST[1949] = "UTL_GetEccConfigCounterEnableSignal";
	START_LAPTIMER(1949);
	int retval = UTL_GetEccConfigCounterEnableSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(1949);
	return retval;
}
int _UTL_GetEccConfigJudgeSignal( EccConfigHandle arg1, RadioButton arg2, RadioButton * arg3)
{
	MCI_LIST[1950] = "UTL_GetEccConfigJudgeSignal";
	START_LAPTIMER(1950);
	int retval = UTL_GetEccConfigJudgeSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(1950);
	return retval;
}
int _UTL_GetEccConfigCounterClearSignal( EccConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1951] = "UTL_GetEccConfigCounterClearSignal";
	START_LAPTIMER(1951);
	int retval = UTL_GetEccConfigCounterClearSignal( arg1, arg2);
	STOP_LAPTIMER(1951);
	return retval;
}
void _UTL_UpdateTprogConfig( TprogConfigHandle arg1)
{
	MCI_LIST[1952] = "UTL_UpdateTprogConfig";
	START_LAPTIMER(1952);
	UTL_UpdateTprogConfig( arg1);
	STOP_LAPTIMER(1952);
}
int _UTL_GetTprogConfigAverageLimit( TprogConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1953] = "UTL_GetTprogConfigAverageLimit";
	START_LAPTIMER(1953);
	int retval = UTL_GetTprogConfigAverageLimit( arg1, arg2);
	STOP_LAPTIMER(1953);
	return retval;
}
int _UTL_GetTprogConfigMaxLimit( TprogConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[1954] = "UTL_GetTprogConfigMaxLimit";
	START_LAPTIMER(1954);
	int retval = UTL_GetTprogConfigMaxLimit( arg1, arg2);
	STOP_LAPTIMER(1954);
	return retval;
}
int _UTL_GetTprogConfigCounterEnableSignal( TprogConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1955] = "UTL_GetTprogConfigCounterEnableSignal";
	START_LAPTIMER(1955);
	int retval = UTL_GetTprogConfigCounterEnableSignal( arg1, arg2);
	STOP_LAPTIMER(1955);
	return retval;
}
int _UTL_GetTprogConfigJudgeSignal( TprogConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1956] = "UTL_GetTprogConfigJudgeSignal";
	START_LAPTIMER(1956);
	int retval = UTL_GetTprogConfigJudgeSignal( arg1, arg2);
	STOP_LAPTIMER(1956);
	return retval;
}
int _UTL_GetTprogConfigCounterClearSignal( TprogConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[1957] = "UTL_GetTprogConfigCounterClearSignal";
	START_LAPTIMER(1957);
	int retval = UTL_GetTprogConfigCounterClearSignal( arg1, arg2);
	STOP_LAPTIMER(1957);
	return retval;
}
int _UTL_GetAfmPatternInfoMpatName( AfmPatternInfoHandle arg1, char ** arg2)
{
	MCI_LIST[1958] = "UTL_GetAfmPatternInfoMpatName";
	START_LAPTIMER(1958);
	int retval = UTL_GetAfmPatternInfoMpatName( arg1, arg2);
	STOP_LAPTIMER(1958);
	return retval;
}
int _UTL_GetAfmPatternInfoModuleNum( AfmPatternInfoHandle arg1, USlider * arg2)
{
	MCI_LIST[1959] = "UTL_GetAfmPatternInfoModuleNum";
	START_LAPTIMER(1959);
	int retval = UTL_GetAfmPatternInfoModuleNum( arg1, arg2);
	STOP_LAPTIMER(1959);
	return retval;
}
int _UTL_GetAfmPatternInfoStartPc( AfmPatternInfoHandle arg1, USlider arg2, USlider * arg3)
{
	MCI_LIST[1960] = "UTL_GetAfmPatternInfoStartPc";
	START_LAPTIMER(1960);
	int retval = UTL_GetAfmPatternInfoStartPc( arg1, arg2, arg3);
	STOP_LAPTIMER(1960);
	return retval;
}
int _UTL_GetAfmPatternInfoBitSize( AfmPatternInfoHandle arg1, USlider arg2, USlider * arg3)
{
	MCI_LIST[1961] = "UTL_GetAfmPatternInfoBitSize";
	START_LAPTIMER(1961);
	int retval = UTL_GetAfmPatternInfoBitSize( arg1, arg2, arg3);
	STOP_LAPTIMER(1961);
	return retval;
}
int _UTL_GetAfmPatternInfoAMinXAddr( AfmPatternInfoHandle arg1, USlider arg2, USlider * arg3)
{
	MCI_LIST[1962] = "UTL_GetAfmPatternInfoAMinXAddr";
	START_LAPTIMER(1962);
	int retval = UTL_GetAfmPatternInfoAMinXAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1962);
	return retval;
}
int _UTL_GetAfmPatternInfoAMinYAddr( AfmPatternInfoHandle arg1, USlider arg2, USlider * arg3)
{
	MCI_LIST[1963] = "UTL_GetAfmPatternInfoAMinYAddr";
	START_LAPTIMER(1963);
	int retval = UTL_GetAfmPatternInfoAMinYAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1963);
	return retval;
}
int _UTL_GetAfmPatternInfoAMinZAddr( AfmPatternInfoHandle arg1, USlider arg2, USlider * arg3)
{
	MCI_LIST[1964] = "UTL_GetAfmPatternInfoAMinZAddr";
	START_LAPTIMER(1964);
	int retval = UTL_GetAfmPatternInfoAMinZAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1964);
	return retval;
}
int _UTL_GetAfmPatternInfoAMaxXAddr( AfmPatternInfoHandle arg1, USlider arg2, USlider * arg3)
{
	MCI_LIST[1965] = "UTL_GetAfmPatternInfoAMaxXAddr";
	START_LAPTIMER(1965);
	int retval = UTL_GetAfmPatternInfoAMaxXAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1965);
	return retval;
}
int _UTL_GetAfmPatternInfoAMaxYAddr( AfmPatternInfoHandle arg1, USlider arg2, USlider * arg3)
{
	MCI_LIST[1966] = "UTL_GetAfmPatternInfoAMaxYAddr";
	START_LAPTIMER(1966);
	int retval = UTL_GetAfmPatternInfoAMaxYAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1966);
	return retval;
}
int _UTL_GetAfmPatternInfoAMaxZAddr( AfmPatternInfoHandle arg1, USlider arg2, USlider * arg3)
{
	MCI_LIST[1967] = "UTL_GetAfmPatternInfoAMaxZAddr";
	START_LAPTIMER(1967);
	int retval = UTL_GetAfmPatternInfoAMaxZAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(1967);
	return retval;
}
int _UTL_GetAfmPatternAccessAfmPatternInfo( AfmPatternAccessHandle  arg1, AfmPatternInfoHandle *  arg2)
{
	MCI_LIST[1968] = "UTL_GetAfmPatternAccessAfmPatternInfo";
	START_LAPTIMER(1968);
	int retval = UTL_GetAfmPatternAccessAfmPatternInfo( arg1, arg2);
	STOP_LAPTIMER(1968);
	return retval;
}
int _UTL_GetAfmPatternAccessModuleIndex( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1969] = "UTL_GetAfmPatternAccessModuleIndex";
	START_LAPTIMER(1969);
	int retval = UTL_GetAfmPatternAccessModuleIndex( arg1, arg2);
	STOP_LAPTIMER(1969);
	return retval;
}
int _UTL_GetAfmPatternAccessAreaIndex( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1970] = "UTL_GetAfmPatternAccessAreaIndex";
	START_LAPTIMER(1970);
	int retval = UTL_GetAfmPatternAccessAreaIndex( arg1, arg2);
	STOP_LAPTIMER(1970);
	return retval;
}
int _UTL_GetAfmPatternAccessAreaReadMode( AfmPatternAccessHandle arg1, CheckButton * arg2)
{
	MCI_LIST[1971] = "UTL_GetAfmPatternAccessAreaReadMode";
	START_LAPTIMER(1971);
	int retval = UTL_GetAfmPatternAccessAreaReadMode( arg1, arg2);
	STOP_LAPTIMER(1971);
	return retval;
}
int _UTL_GetAfmPatternAccessDataFormat( AfmPatternAccessHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1972] = "UTL_GetAfmPatternAccessDataFormat";
	START_LAPTIMER(1972);
	int retval = UTL_GetAfmPatternAccessDataFormat( arg1, arg2);
	STOP_LAPTIMER(1972);
	return retval;
}
int _UTL_GetAfmPatternAccessBitBlockNum( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1973] = "UTL_GetAfmPatternAccessBitBlockNum";
	START_LAPTIMER(1973);
	int retval = UTL_GetAfmPatternAccessBitBlockNum( arg1, arg2);
	STOP_LAPTIMER(1973);
	return retval;
}
int _UTL_GetAfmPatternAccessBitBlock( AfmPatternAccessHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1974] = "UTL_GetAfmPatternAccessBitBlock";
	START_LAPTIMER(1974);
	int retval = UTL_GetAfmPatternAccessBitBlock( arg1, arg2);
	STOP_LAPTIMER(1974);
	return retval;
}
int _UTL_GetAfmPatternAccessStartXAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1975] = "UTL_GetAfmPatternAccessStartXAddr";
	START_LAPTIMER(1975);
	int retval = UTL_GetAfmPatternAccessStartXAddr( arg1, arg2);
	STOP_LAPTIMER(1975);
	return retval;
}
int _UTL_GetAfmPatternAccessStartYAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1976] = "UTL_GetAfmPatternAccessStartYAddr";
	START_LAPTIMER(1976);
	int retval = UTL_GetAfmPatternAccessStartYAddr( arg1, arg2);
	STOP_LAPTIMER(1976);
	return retval;
}
int _UTL_GetAfmPatternAccessStartZAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1977] = "UTL_GetAfmPatternAccessStartZAddr";
	START_LAPTIMER(1977);
	int retval = UTL_GetAfmPatternAccessStartZAddr( arg1, arg2);
	STOP_LAPTIMER(1977);
	return retval;
}
int _UTL_GetAfmPatternAccessStopXAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1978] = "UTL_GetAfmPatternAccessStopXAddr";
	START_LAPTIMER(1978);
	int retval = UTL_GetAfmPatternAccessStopXAddr( arg1, arg2);
	STOP_LAPTIMER(1978);
	return retval;
}
int _UTL_GetAfmPatternAccessStopYAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1979] = "UTL_GetAfmPatternAccessStopYAddr";
	START_LAPTIMER(1979);
	int retval = UTL_GetAfmPatternAccessStopYAddr( arg1, arg2);
	STOP_LAPTIMER(1979);
	return retval;
}
int _UTL_GetAfmPatternAccessStopZAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1980] = "UTL_GetAfmPatternAccessStopZAddr";
	START_LAPTIMER(1980);
	int retval = UTL_GetAfmPatternAccessStopZAddr( arg1, arg2);
	STOP_LAPTIMER(1980);
	return retval;
}
int _UTL_GetAfmPatternAccessAMaxXAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1981] = "UTL_GetAfmPatternAccessAMaxXAddr";
	START_LAPTIMER(1981);
	int retval = UTL_GetAfmPatternAccessAMaxXAddr( arg1, arg2);
	STOP_LAPTIMER(1981);
	return retval;
}
int _UTL_GetAfmPatternAccessAMaxYAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1982] = "UTL_GetAfmPatternAccessAMaxYAddr";
	START_LAPTIMER(1982);
	int retval = UTL_GetAfmPatternAccessAMaxYAddr( arg1, arg2);
	STOP_LAPTIMER(1982);
	return retval;
}
int _UTL_GetAfmPatternAccessAMaxZAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1983] = "UTL_GetAfmPatternAccessAMaxZAddr";
	START_LAPTIMER(1983);
	int retval = UTL_GetAfmPatternAccessAMaxZAddr( arg1, arg2);
	STOP_LAPTIMER(1983);
	return retval;
}
int _UTL_GetAfmPatternAccessAreaNum( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1984] = "UTL_GetAfmPatternAccessAreaNum";
	START_LAPTIMER(1984);
	int retval = UTL_GetAfmPatternAccessAreaNum( arg1, arg2);
	STOP_LAPTIMER(1984);
	return retval;
}
int _UTL_GetAfmPatternAccessAreaStartXAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1985] = "UTL_GetAfmPatternAccessAreaStartXAddr";
	START_LAPTIMER(1985);
	int retval = UTL_GetAfmPatternAccessAreaStartXAddr( arg1, arg2);
	STOP_LAPTIMER(1985);
	return retval;
}
int _UTL_GetAfmPatternAccessAreaStartYAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1986] = "UTL_GetAfmPatternAccessAreaStartYAddr";
	START_LAPTIMER(1986);
	int retval = UTL_GetAfmPatternAccessAreaStartYAddr( arg1, arg2);
	STOP_LAPTIMER(1986);
	return retval;
}
int _UTL_GetAfmPatternAccessAreaStartZAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1987] = "UTL_GetAfmPatternAccessAreaStartZAddr";
	START_LAPTIMER(1987);
	int retval = UTL_GetAfmPatternAccessAreaStartZAddr( arg1, arg2);
	STOP_LAPTIMER(1987);
	return retval;
}
int _UTL_GetAfmPatternAccessAreaStopXAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1988] = "UTL_GetAfmPatternAccessAreaStopXAddr";
	START_LAPTIMER(1988);
	int retval = UTL_GetAfmPatternAccessAreaStopXAddr( arg1, arg2);
	STOP_LAPTIMER(1988);
	return retval;
}
int _UTL_GetAfmPatternAccessAreaStopYAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1989] = "UTL_GetAfmPatternAccessAreaStopYAddr";
	START_LAPTIMER(1989);
	int retval = UTL_GetAfmPatternAccessAreaStopYAddr( arg1, arg2);
	STOP_LAPTIMER(1989);
	return retval;
}
int _UTL_GetAfmPatternAccessAreaStopZAddr( AfmPatternAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[1990] = "UTL_GetAfmPatternAccessAreaStopZAddr";
	START_LAPTIMER(1990);
	int retval = UTL_GetAfmPatternAccessAreaStopZAddr( arg1, arg2);
	STOP_LAPTIMER(1990);
	return retval;
}
void _UTL_UpdateFcmMultiSideConfig( FcmMultiSideConfigHandle arg1)
{
	MCI_LIST[1991] = "UTL_UpdateFcmMultiSideConfig";
	START_LAPTIMER(1991);
	UTL_UpdateFcmMultiSideConfig( arg1);
	STOP_LAPTIMER(1991);
}
int _UTL_GetFcmMultiSideConfigSideCount( FcmMultiSideConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[1992] = "UTL_GetFcmMultiSideConfigSideCount";
	START_LAPTIMER(1992);
	int retval = UTL_GetFcmMultiSideConfigSideCount( arg1, arg2);
	STOP_LAPTIMER(1992);
	return retval;
}
int _UTL_GetFcmMultiSideConfigSideMode( FcmMultiSideConfigHandle arg1, RadioButton arg2, RadioButton * arg3)
{
	MCI_LIST[1993] = "UTL_GetFcmMultiSideConfigSideMode";
	START_LAPTIMER(1993);
	int retval = UTL_GetFcmMultiSideConfigSideMode( arg1, arg2, arg3);
	STOP_LAPTIMER(1993);
	return retval;
}
int _UTL_GetFctAfterFunc( FctHandle  arg1, void ** arg2)
{
	MCI_LIST[1994] = "UTL_GetFctAfterFunc";
	START_LAPTIMER(1994);
	int retval = UTL_GetFctAfterFunc( arg1, arg2);
	STOP_LAPTIMER(1994);
	return retval;
}
int _UTL_GetFctBeforeFunc( FctHandle  arg1, void ** arg2)
{
	MCI_LIST[1995] = "UTL_GetFctBeforeFunc";
	START_LAPTIMER(1995);
	int retval = UTL_GetFctBeforeFunc( arg1, arg2);
	STOP_LAPTIMER(1995);
	return retval;
}
int _UTL_GetFctContinue( FctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1996] = "UTL_GetFctContinue";
	START_LAPTIMER(1996);
	int retval = UTL_GetFctContinue( arg1, arg2);
	STOP_LAPTIMER(1996);
	return retval;
}
int _UTL_GetFctFailAction( FctHandle  arg1, void ** arg2)
{
	MCI_LIST[1997] = "UTL_GetFctFailAction";
	START_LAPTIMER(1997);
	int retval = UTL_GetFctFailAction( arg1, arg2);
	STOP_LAPTIMER(1997);
	return retval;
}
int _UTL_GetFctFailInhibit( FctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[1998] = "UTL_GetFctFailInhibit";
	START_LAPTIMER(1998);
	int retval = UTL_GetFctFailInhibit( arg1, arg2);
	STOP_LAPTIMER(1998);
	return retval;
}
int _UTL_GetFctMpatName( FctHandle  arg1, char ** arg2)
{
	MCI_LIST[1999] = "UTL_GetFctMpatName";
	START_LAPTIMER(1999);
	int retval = UTL_GetFctMpatName( arg1, arg2);
	STOP_LAPTIMER(1999);
	return retval;
}
int _UTL_GetFctNoClear( FctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2000] = "UTL_GetFctNoClear";
	START_LAPTIMER(2000);
	int retval = UTL_GetFctNoClear( arg1, arg2);
	STOP_LAPTIMER(2000);
	return retval;
}
int _UTL_GetFctNoWait( FctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2001] = "UTL_GetFctNoWait";
	START_LAPTIMER(2001);
	int retval = UTL_GetFctNoWait( arg1, arg2);
	STOP_LAPTIMER(2001);
	return retval;
}
int _UTL_GetFctPassAction( FctHandle  arg1, void ** arg2)
{
	MCI_LIST[2002] = "UTL_GetFctPassAction";
	START_LAPTIMER(2002);
	int retval = UTL_GetFctPassAction( arg1, arg2);
	STOP_LAPTIMER(2002);
	return retval;
}
int _UTL_GetFctRepeat( FctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2003] = "UTL_GetFctRepeat";
	START_LAPTIMER(2003);
	int retval = UTL_GetFctRepeat( arg1, arg2);
	STOP_LAPTIMER(2003);
	return retval;
}
int _UTL_GetFctSronInhibit( FctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2004] = "UTL_GetFctSronInhibit";
	START_LAPTIMER(2004);
	int retval = UTL_GetFctSronInhibit( arg1, arg2);
	STOP_LAPTIMER(2004);
	return retval;
}
int _UTL_GetFctMpatTransferInhibit( FctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2005] = "UTL_GetFctMpatTransferInhibit";
	START_LAPTIMER(2005);
	int retval = UTL_GetFctMpatTransferInhibit( arg1, arg2);
	STOP_LAPTIMER(2005);
	return retval;
}
int _UTL_GetFctStartFunc( FctHandle  arg1, void ** arg2)
{
	MCI_LIST[2006] = "UTL_GetFctStartFunc";
	START_LAPTIMER(2006);
	int retval = UTL_GetFctStartFunc( arg1, arg2);
	STOP_LAPTIMER(2006);
	return retval;
}
int _UTL_GetFctStartPc( FctHandle  arg1, USlider * arg2)
{
	MCI_LIST[2007] = "UTL_GetFctStartPc";
	START_LAPTIMER(2007);
	int retval = UTL_GetFctStartPc( arg1, arg2);
	STOP_LAPTIMER(2007);
	return retval;
}
int _UTL_GetFctTimeLimitAction( FctHandle  arg1, void ** arg2)
{
	MCI_LIST[2008] = "UTL_GetFctTimeLimitAction";
	START_LAPTIMER(2008);
	int retval = UTL_GetFctTimeLimitAction( arg1, arg2);
	STOP_LAPTIMER(2008);
	return retval;
}
int _UTL_GetFctTimeLimitData( FctHandle  arg1, USlider * arg2)
{
	MCI_LIST[2009] = "UTL_GetFctTimeLimitData";
	START_LAPTIMER(2009);
	int retval = UTL_GetFctTimeLimitData( arg1, arg2);
	STOP_LAPTIMER(2009);
	return retval;
}
int _UTL_GetFctTimeLimitMode( FctHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2010] = "UTL_GetFctTimeLimitMode";
	START_LAPTIMER(2010);
	int retval = UTL_GetFctTimeLimitMode( arg1, arg2);
	STOP_LAPTIMER(2010);
	return retval;
}
void _UTL_UpdateFlash( FlashHandle arg1)
{
	MCI_LIST[2011] = "UTL_UpdateFlash";
	START_LAPTIMER(2011);
	UTL_UpdateFlash( arg1);
	STOP_LAPTIMER(2011);
}
int _UTL_GetFlashCounterClearCondition( FlashHandle  arg1, UT_DUT  arg2, RadioButton * arg3)
{
	MCI_LIST[2012] = "UTL_GetFlashCounterClearCondition";
	START_LAPTIMER(2012);
	int retval = UTL_GetFlashCounterClearCondition( arg1, arg2, arg3);
	STOP_LAPTIMER(2012);
	return retval;
}
int _UTL_GetFlashCounterIncCondition( FlashHandle  arg1, UT_DUT  arg2, RadioButton * arg3)
{
	MCI_LIST[2013] = "UTL_GetFlashCounterIncCondition";
	START_LAPTIMER(2013);
	int retval = UTL_GetFlashCounterIncCondition( arg1, arg2, arg3);
	STOP_LAPTIMER(2013);
	return retval;
}
int _UTL_GetFlashHoldClearCondition( FlashHandle  arg1, UT_DUT  arg2, RadioButton * arg3)
{
	MCI_LIST[2014] = "UTL_GetFlashHoldClearCondition";
	START_LAPTIMER(2014);
	int retval = UTL_GetFlashHoldClearCondition( arg1, arg2, arg3);
	STOP_LAPTIMER(2014);
	return retval;
}
int _UTL_GetFlashHoldLoadCondition( FlashHandle  arg1, UT_DUT  arg2, RadioButton * arg3)
{
	MCI_LIST[2015] = "UTL_GetFlashHoldLoadCondition";
	START_LAPTIMER(2015);
	int retval = UTL_GetFlashHoldLoadCondition( arg1, arg2, arg3);
	STOP_LAPTIMER(2015);
	return retval;
}
int _UTL_GetFlashHoldMode( FlashHandle  arg1, UT_DUT  arg2, RadioButton * arg3)
{
	MCI_LIST[2016] = "UTL_GetFlashHoldMode";
	START_LAPTIMER(2016);
	int retval = UTL_GetFlashHoldMode( arg1, arg2, arg3);
	STOP_LAPTIMER(2016);
	return retval;
}
int _UTL_GetFlashLimitCount( FlashHandle  arg1, UT_DUT  arg2, Slider * arg3)
{
	MCI_LIST[2017] = "UTL_GetFlashLimitCount";
	START_LAPTIMER(2017);
	int retval = UTL_GetFlashLimitCount( arg1, arg2, arg3);
	STOP_LAPTIMER(2017);
	return retval;
}
int _UTL_GetFlashMaskMode( FlashHandle  arg1, UT_DUT  arg2, CheckButton * arg3)
{
	MCI_LIST[2018] = "UTL_GetFlashMaskMode";
	START_LAPTIMER(2018);
	int retval = UTL_GetFlashMaskMode( arg1, arg2, arg3);
	STOP_LAPTIMER(2018);
	return retval;
}
int _UTL_GetFlashMode( FlashHandle  arg1, UT_DUT  arg2, RadioButton * arg3)
{
	MCI_LIST[2019] = "UTL_GetFlashMode";
	START_LAPTIMER(2019);
	int retval = UTL_GetFlashMode( arg1, arg2, arg3);
	STOP_LAPTIMER(2019);
	return retval;
}
int _UTL_GetFlashCpInhPinMode( FlashHandle  arg1, CheckButton *  arg2)
{
	MCI_LIST[2020] = "UTL_GetFlashCpInhPinMode";
	START_LAPTIMER(2020);
	int retval = UTL_GetFlashCpInhPinMode( arg1, arg2);
	STOP_LAPTIMER(2020);
	return retval;
}
int _UTL_GetFlashCpInhPin( FlashHandle  arg1, char **  arg2)
{
	MCI_LIST[2021] = "UTL_GetFlashCpInhPin";
	START_LAPTIMER(2021);
	int retval = UTL_GetFlashCpInhPin( arg1, arg2);
	STOP_LAPTIMER(2021);
	return retval;
}
int _UTL_GetReadFlashCounterDut( ReadFlashCounterHandle  arg1, UT_DUT * arg2)
{
	MCI_LIST[2022] = "UTL_GetReadFlashCounterDut";
	START_LAPTIMER(2022);
	int retval = UTL_GetReadFlashCounterDut( arg1, arg2);
	STOP_LAPTIMER(2022);
	return retval;
}
int _UTL_GetReadFlashHoldDut( ReadFlashHoldHandle  arg1, UT_DUT * arg2)
{
	MCI_LIST[2023] = "UTL_GetReadFlashHoldDut";
	START_LAPTIMER(2023);
	int retval = UTL_GetReadFlashHoldDut( arg1, arg2);
	STOP_LAPTIMER(2023);
	return retval;
}
int _UTL_GetReadFlashHoldPin( ReadFlashHoldHandle  arg1, UT_PIN * arg2)
{
	MCI_LIST[2024] = "UTL_GetReadFlashHoldPin";
	START_LAPTIMER(2024);
	int retval = UTL_GetReadFlashHoldPin( arg1, arg2);
	STOP_LAPTIMER(2024);
	return retval;
}
int _UTL_GetReadFlashMaxFailDut( ReadFlashMaxFailHandle  arg1, UT_DUT * arg2)
{
	MCI_LIST[2025] = "UTL_GetReadFlashMaxFailDut";
	START_LAPTIMER(2025);
	int retval = UTL_GetReadFlashMaxFailDut( arg1, arg2);
	STOP_LAPTIMER(2025);
	return retval;
}
void _UTL_UpdatePin( PinHandle arg1, UT_PIN arg2, RadioButton arg3, UT_DUT arg4)
{
	MCI_LIST[2026] = "UTL_UpdatePin";
	START_LAPTIMER(2026);
	UTL_UpdatePin( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2026);
}
int _UTL_GetPinDcConnect( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2027] = "UTL_GetPinDcConnect";
	START_LAPTIMER(2027);
	int retval = UTL_GetPinDcConnect( arg1, arg2);
	STOP_LAPTIMER(2027);
	return retval;
}
int _UTL_GetPinDclp( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2028] = "UTL_GetPinDclp";
	START_LAPTIMER(2028);
	int retval = UTL_GetPinDclp( arg1, arg2);
	STOP_LAPTIMER(2028);
	return retval;
}
int _UTL_GetPinDrClock( PinHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[2029] = "UTL_GetPinDrClock";
	START_LAPTIMER(2029);
	int retval = UTL_GetPinDrClock( arg1, arg2, arg3);
	STOP_LAPTIMER(2029);
	return retval;
}
int _UTL_GetPinDreOffTermMode( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2030] = "UTL_GetPinDreOffTermMode";
	START_LAPTIMER(2030);
	int retval = UTL_GetPinDreOffTermMode( arg1, arg2);
	STOP_LAPTIMER(2030);
	return retval;
}
int _UTL_GetPinDrzPulseWidth( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2031] = "UTL_GetPinDrzPulseWidth";
	START_LAPTIMER(2031);
	int retval = UTL_GetPinDrzPulseWidth( arg1, arg2);
	STOP_LAPTIMER(2031);
	return retval;
}
int _UTL_GetPinDrWaveform( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2032] = "UTL_GetPinDrWaveform";
	START_LAPTIMER(2032);
	int retval = UTL_GetPinDrWaveform( arg1, arg2);
	STOP_LAPTIMER(2032);
	return retval;
}
int _UTL_GetPinDrPort( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2033] = "UTL_GetPinDrPort";
	START_LAPTIMER(2033);
	int retval = UTL_GetPinDrPort( arg1, arg2);
	STOP_LAPTIMER(2033);
	return retval;
}
int _UTL_GetPinDreClock( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2034] = "UTL_GetPinDreClock";
	START_LAPTIMER(2034);
	int retval = UTL_GetPinDreClock( arg1, arg2);
	STOP_LAPTIMER(2034);
	return retval;
}
int _UTL_GetPinDreOffsetClock( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2035] = "UTL_GetPinDreOffsetClock";
	START_LAPTIMER(2035);
	int retval = UTL_GetPinDreOffsetClock( arg1, arg2);
	STOP_LAPTIMER(2035);
	return retval;
}
int _UTL_GetPinDreNumber( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2036] = "UTL_GetPinDreNumber";
	START_LAPTIMER(2036);
	int retval = UTL_GetPinDreNumber( arg1, arg2);
	STOP_LAPTIMER(2036);
	return retval;
}
int _UTL_GetPinDrePatternInh( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2037] = "UTL_GetPinDrePatternInh";
	START_LAPTIMER(2037);
	int retval = UTL_GetPinDrePatternInh( arg1, arg2);
	STOP_LAPTIMER(2037);
	return retval;
}
int _UTL_GetPinDreWaveform( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2038] = "UTL_GetPinDreWaveform";
	START_LAPTIMER(2038);
	int retval = UTL_GetPinDreWaveform( arg1, arg2);
	STOP_LAPTIMER(2038);
	return retval;
}
int _UTL_GetPinDronInit( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2039] = "UTL_GetPinDronInit";
	START_LAPTIMER(2039);
	int retval = UTL_GetPinDronInit( arg1, arg2);
	STOP_LAPTIMER(2039);
	return retval;
}
int _UTL_GetPinDbmPinDrePattern( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2040] = "UTL_GetPinDbmPinDrePattern";
	START_LAPTIMER(2040);
	int retval = UTL_GetPinDbmPinDrePattern( arg1, arg2);
	STOP_LAPTIMER(2040);
	return retval;
}
int _UTL_GetPinEinv( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2041] = "UTL_GetPinEinv";
	START_LAPTIMER(2041);
	int retval = UTL_GetPinEinv( arg1, arg2);
	STOP_LAPTIMER(2041);
	return retval;
}
int _UTL_GetPinHvDr( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2042] = "UTL_GetPinHvDr";
	START_LAPTIMER(2042);
	int retval = UTL_GetPinHvDr( arg1, arg2);
	STOP_LAPTIMER(2042);
	return retval;
}
int _UTL_GetPinHvLvDr( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2043] = "UTL_GetPinHvLvDr";
	START_LAPTIMER(2043);
	int retval = UTL_GetPinHvLvDr( arg1, arg2);
	STOP_LAPTIMER(2043);
	return retval;
}
int _UTL_GetPinDbmPinPattern( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2044] = "UTL_GetPinDbmPinPattern";
	START_LAPTIMER(2044);
	int retval = UTL_GetPinDbmPinPattern( arg1, arg2);
	STOP_LAPTIMER(2044);
	return retval;
}
int _UTL_GetPinIlNumber( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2045] = "UTL_GetPinIlNumber";
	START_LAPTIMER(2045);
	int retval = UTL_GetPinIlNumber( arg1, arg2);
	STOP_LAPTIMER(2045);
	return retval;
}
int _UTL_GetPinInit( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2046] = "UTL_GetPinInit";
	START_LAPTIMER(2046);
	int retval = UTL_GetPinInit( arg1, arg2);
	STOP_LAPTIMER(2046);
	return retval;
}
int _UTL_GetPinIoCtrl( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2047] = "UTL_GetPinIoCtrl";
	START_LAPTIMER(2047);
	int retval = UTL_GetPinIoCtrl( arg1, arg2);
	STOP_LAPTIMER(2047);
	return retval;
}
int _UTL_GetPinMatchMode( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2048] = "UTL_GetPinMatchMode";
	START_LAPTIMER(2048);
	int retval = UTL_GetPinMatchMode( arg1, arg2);
	STOP_LAPTIMER(2048);
	return retval;
}
int _UTL_GetPinMatchGroup( PinHandle  arg1, RadioButton  arg2, CheckButton * arg3)
{
	MCI_LIST[2049] = "UTL_GetPinMatchGroup";
	START_LAPTIMER(2049);
	int retval = UTL_GetPinMatchGroup( arg1, arg2, arg3);
	STOP_LAPTIMER(2049);
	return retval;
}
int _UTL_GetPinOpen( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2050] = "UTL_GetPinOpen";
	START_LAPTIMER(2050);
	int retval = UTL_GetPinOpen( arg1, arg2);
	STOP_LAPTIMER(2050);
	return retval;
}
int _UTL_GetPinPatternInh( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2051] = "UTL_GetPinPatternInh";
	START_LAPTIMER(2051);
	int retval = UTL_GetPinPatternInh( arg1, arg2);
	STOP_LAPTIMER(2051);
	return retval;
}
int _UTL_GetPinPatternInhLevel( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2052] = "UTL_GetPinPatternInhLevel";
	START_LAPTIMER(2052);
	int retval = UTL_GetPinPatternInhLevel( arg1, arg2);
	STOP_LAPTIMER(2052);
	return retval;
}
int _UTL_GetPinPatternInhPerPin( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2053] = "UTL_GetPinPatternInhPerPin";
	START_LAPTIMER(2053);
	int retval = UTL_GetPinPatternInhPerPin( arg1, arg2);
	STOP_LAPTIMER(2053);
	return retval;
}
int _UTL_GetPinDbmPinFix( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2054] = "UTL_GetPinDbmPinFix";
	START_LAPTIMER(2054);
	int retval = UTL_GetPinDbmPinFix( arg1, arg2);
	STOP_LAPTIMER(2054);
	return retval;
}
int _UTL_GetPinPdsSendMode( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2055] = "UTL_GetPinPdsSendMode";
	START_LAPTIMER(2055);
	int retval = UTL_GetPinPdsSendMode( arg1, arg2);
	STOP_LAPTIMER(2055);
	return retval;
}
int _UTL_GetPinPl( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2056] = "UTL_GetPinPl";
	START_LAPTIMER(2056);
	int retval = UTL_GetPinPl( arg1, arg2);
	STOP_LAPTIMER(2056);
	return retval;
}
int _UTL_GetPinTerm( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2057] = "UTL_GetPinTerm";
	START_LAPTIMER(2057);
	int retval = UTL_GetPinTerm( arg1, arg2);
	STOP_LAPTIMER(2057);
	return retval;
}
int _UTL_GetPinViNumber( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2058] = "UTL_GetPinViNumber";
	START_LAPTIMER(2058);
	int retval = UTL_GetPinViNumber( arg1, arg2);
	STOP_LAPTIMER(2058);
	return retval;
}
int _UTL_GetPinVihhNumber( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2059] = "UTL_GetPinVihhNumber";
	START_LAPTIMER(2059);
	int retval = UTL_GetPinVihhNumber( arg1, arg2);
	STOP_LAPTIMER(2059);
	return retval;
}
int _UTL_GetPinVihhMutSignal( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2060] = "UTL_GetPinVihhMutSignal";
	START_LAPTIMER(2060);
	int retval = UTL_GetPinVihhMutSignal( arg1, arg2);
	STOP_LAPTIMER(2060);
	return retval;
}
int _UTL_GetPinVoNumber( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2061] = "UTL_GetPinVoNumber";
	START_LAPTIMER(2061);
	int retval = UTL_GetPinVoNumber( arg1, arg2);
	STOP_LAPTIMER(2061);
	return retval;
}
int _UTL_GetPinVodNumber( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2062] = "UTL_GetPinVodNumber";
	START_LAPTIMER(2062);
	int retval = UTL_GetPinVodNumber( arg1, arg2);
	STOP_LAPTIMER(2062);
	return retval;
}
int _UTL_GetPinVtNumber( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2063] = "UTL_GetPinVtNumber";
	START_LAPTIMER(2063);
	int retval = UTL_GetPinVtNumber( arg1, arg2);
	STOP_LAPTIMER(2063);
	return retval;
}
int _UTL_GetPinVloadNumber( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2064] = "UTL_GetPinVloadNumber";
	START_LAPTIMER(2064);
	int retval = UTL_GetPinVloadNumber( arg1, arg2);
	STOP_LAPTIMER(2064);
	return retval;
}
int _UTL_GetPinVloadResistor( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2065] = "UTL_GetPinVloadResistor";
	START_LAPTIMER(2065);
	int retval = UTL_GetPinVloadResistor( arg1, arg2);
	STOP_LAPTIMER(2065);
	return retval;
}
int _UTL_GetPinBankMultiplex( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2066] = "UTL_GetPinBankMultiplex";
	START_LAPTIMER(2066);
	int retval = UTL_GetPinBankMultiplex( arg1, arg2);
	STOP_LAPTIMER(2066);
	return retval;
}
int _UTL_GetPinBankNumber( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2067] = "UTL_GetPinBankNumber";
	START_LAPTIMER(2067);
	int retval = UTL_GetPinBankNumber( arg1, arg2);
	STOP_LAPTIMER(2067);
	return retval;
}
int _UTL_GetPinCpeDelay( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2068] = "UTL_GetPinCpeDelay";
	START_LAPTIMER(2068);
	int retval = UTL_GetPinCpeDelay( arg1, arg2);
	STOP_LAPTIMER(2068);
	return retval;
}
int _UTL_GetPinModeCpeDelay( PinHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[2069] = "UTL_GetPinModeCpeDelay";
	START_LAPTIMER(2069);
	int retval = UTL_GetPinModeCpeDelay( arg1, arg2, arg3);
	STOP_LAPTIMER(2069);
	return retval;
}
int _UTL_GetPinCyclePaletteSet( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2070] = "UTL_GetPinCyclePaletteSet";
	START_LAPTIMER(2070);
	int retval = UTL_GetPinCyclePaletteSet( arg1, arg2);
	STOP_LAPTIMER(2070);
	return retval;
}
int _UTL_GetPinDrDelay( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2071] = "UTL_GetPinDrDelay";
	START_LAPTIMER(2071);
	int retval = UTL_GetPinDrDelay( arg1, arg2);
	STOP_LAPTIMER(2071);
	return retval;
}
int _UTL_GetPinModeDrDelay( PinHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[2072] = "UTL_GetPinModeDrDelay";
	START_LAPTIMER(2072);
	int retval = UTL_GetPinModeDrDelay( arg1, arg2, arg3);
	STOP_LAPTIMER(2072);
	return retval;
}
int _UTL_GetPinDrPatternLevel( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2073] = "UTL_GetPinDrPatternLevel";
	START_LAPTIMER(2073);
	int retval = UTL_GetPinDrPatternLevel( arg1, arg2);
	STOP_LAPTIMER(2073);
	return retval;
}
int _UTL_GetPinDreDelay( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2074] = "UTL_GetPinDreDelay";
	START_LAPTIMER(2074);
	int retval = UTL_GetPinDreDelay( arg1, arg2);
	STOP_LAPTIMER(2074);
	return retval;
}
int _UTL_GetPinModeDreDelay( PinHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[2075] = "UTL_GetPinModeDreDelay";
	START_LAPTIMER(2075);
	int retval = UTL_GetPinModeDreDelay( arg1, arg2, arg3);
	STOP_LAPTIMER(2075);
	return retval;
}
int _UTL_GetPinDrePatternLevel( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2076] = "UTL_GetPinDrePatternLevel";
	START_LAPTIMER(2076);
	int retval = UTL_GetPinDrePatternLevel( arg1, arg2);
	STOP_LAPTIMER(2076);
	return retval;
}
int _UTL_GetPinDssNumber( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2077] = "UTL_GetPinDssNumber";
	START_LAPTIMER(2077);
	int retval = UTL_GetPinDssNumber( arg1, arg2);
	STOP_LAPTIMER(2077);
	return retval;
}
int _UTL_GetPinExpDelay( PinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2078] = "UTL_GetPinExpDelay";
	START_LAPTIMER(2078);
	int retval = UTL_GetPinExpDelay( arg1, arg2);
	STOP_LAPTIMER(2078);
	return retval;
}
int _UTL_GetPinModeExpDelay( PinHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[2079] = "UTL_GetPinModeExpDelay";
	START_LAPTIMER(2079);
	int retval = UTL_GetPinModeExpDelay( arg1, arg2, arg3);
	STOP_LAPTIMER(2079);
	return retval;
}
int _UTL_GetPinPatternSwapMode( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2080] = "UTL_GetPinPatternSwapMode";
	START_LAPTIMER(2080);
	int retval = UTL_GetPinPatternSwapMode( arg1, arg2);
	STOP_LAPTIMER(2080);
	return retval;
}
int _UTL_GetPinRdsm( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2081] = "UTL_GetPinRdsm";
	START_LAPTIMER(2081);
	int retval = UTL_GetPinRdsm( arg1, arg2);
	STOP_LAPTIMER(2081);
	return retval;
}
int _UTL_GetPinRinv( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2082] = "UTL_GetPinRinv";
	START_LAPTIMER(2082);
	int retval = UTL_GetPinRinv( arg1, arg2);
	STOP_LAPTIMER(2082);
	return retval;
}
int _UTL_GetPinSdm( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2083] = "UTL_GetPinSdm";
	START_LAPTIMER(2083);
	int retval = UTL_GetPinSdm( arg1, arg2);
	STOP_LAPTIMER(2083);
	return retval;
}
int _UTL_GetPinSmc( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2084] = "UTL_GetPinSmc";
	START_LAPTIMER(2084);
	int retval = UTL_GetPinSmc( arg1, arg2);
	STOP_LAPTIMER(2084);
	return retval;
}
int _UTL_GetPinAinv( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2085] = "UTL_GetPinAinv";
	START_LAPTIMER(2085);
	int retval = UTL_GetPinAinv( arg1, arg2);
	STOP_LAPTIMER(2085);
	return retval;
}
PinStrbCursor _UTL_GetPinStrbCursor( PinHandle  arg1)
{
	MCI_LIST[2086] = "UTL_GetPinStrbCursor";
	START_LAPTIMER(2086);
	PinStrbCursor retval = UTL_GetPinStrbCursor( arg1);
	STOP_LAPTIMER(2086);
	return retval;
}
PinStrbHandle _UTL_NextPinStrb( PinStrbCursor  arg1)
{
	MCI_LIST[2087] = "UTL_NextPinStrb";
	START_LAPTIMER(2087);
	PinStrbHandle retval = UTL_NextPinStrb( arg1);
	STOP_LAPTIMER(2087);
	return retval;
}
int _UTL_GetPinStrbNumber( PinStrbHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2088] = "UTL_GetPinStrbNumber";
	START_LAPTIMER(2088);
	int retval = UTL_GetPinStrbNumber( arg1, arg2);
	STOP_LAPTIMER(2088);
	return retval;
}
int _UTL_GetPinStrbCpeNumber( PinStrbHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2089] = "UTL_GetPinStrbCpeNumber";
	START_LAPTIMER(2089);
	int retval = UTL_GetPinStrbCpeNumber( arg1, arg2);
	STOP_LAPTIMER(2089);
	return retval;
}
int _UTL_GetPinStrbEinv( PinStrbHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2090] = "UTL_GetPinStrbEinv";
	START_LAPTIMER(2090);
	int retval = UTL_GetPinStrbEinv( arg1, arg2);
	STOP_LAPTIMER(2090);
	return retval;
}
int _UTL_GetPinStrbExp( PinStrbHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2091] = "UTL_GetPinStrbExp";
	START_LAPTIMER(2091);
	int retval = UTL_GetPinStrbExp( arg1, arg2);
	STOP_LAPTIMER(2091);
	return retval;
}
int _UTL_GetPinStrbHz( PinStrbHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2092] = "UTL_GetPinStrbHz";
	START_LAPTIMER(2092);
	int retval = UTL_GetPinStrbHz( arg1, arg2);
	STOP_LAPTIMER(2092);
	return retval;
}
int _UTL_GetPinStrbRhz( PinStrbHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2093] = "UTL_GetPinStrbRhz";
	START_LAPTIMER(2093);
	int retval = UTL_GetPinStrbRhz( arg1, arg2);
	STOP_LAPTIMER(2093);
	return retval;
}
int _UTL_GetPinStrbBank( PinStrbHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2094] = "UTL_GetPinStrbBank";
	START_LAPTIMER(2094);
	int retval = UTL_GetPinStrbBank( arg1, arg2);
	STOP_LAPTIMER(2094);
	return retval;
}
int _UTL_GetPinStrbChannel( PinStrbHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2095] = "UTL_GetPinStrbChannel";
	START_LAPTIMER(2095);
	int retval = UTL_GetPinStrbChannel( arg1, arg2);
	STOP_LAPTIMER(2095);
	return retval;
}
int _UTL_GetPinStrbCpeMode( PinStrbHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2096] = "UTL_GetPinStrbCpeMode";
	START_LAPTIMER(2096);
	int retval = UTL_GetPinStrbCpeMode( arg1, arg2);
	STOP_LAPTIMER(2096);
	return retval;
}
PinWstrbCursor _UTL_GetPinWstrbCursor( PinHandle  arg1)
{
	MCI_LIST[2097] = "UTL_GetPinWstrbCursor";
	START_LAPTIMER(2097);
	PinWstrbCursor retval = UTL_GetPinWstrbCursor( arg1);
	STOP_LAPTIMER(2097);
	return retval;
}
PinWstrbHandle _UTL_NextPinWstrb( PinWstrbCursor  arg1)
{
	MCI_LIST[2098] = "UTL_NextPinWstrb";
	START_LAPTIMER(2098);
	PinWstrbHandle retval = UTL_NextPinWstrb( arg1);
	STOP_LAPTIMER(2098);
	return retval;
}
int _UTL_GetPinWstrbNumber( PinWstrbHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2099] = "UTL_GetPinWstrbNumber";
	START_LAPTIMER(2099);
	int retval = UTL_GetPinWstrbNumber( arg1, arg2);
	STOP_LAPTIMER(2099);
	return retval;
}
int _UTL_GetPinWstrbCpeNumber( PinWstrbHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2100] = "UTL_GetPinWstrbCpeNumber";
	START_LAPTIMER(2100);
	int retval = UTL_GetPinWstrbCpeNumber( arg1, arg2);
	STOP_LAPTIMER(2100);
	return retval;
}
int _UTL_GetPinWstrbEinv( PinWstrbHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2101] = "UTL_GetPinWstrbEinv";
	START_LAPTIMER(2101);
	int retval = UTL_GetPinWstrbEinv( arg1, arg2);
	STOP_LAPTIMER(2101);
	return retval;
}
int _UTL_GetPinWstrbExp( PinWstrbHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2102] = "UTL_GetPinWstrbExp";
	START_LAPTIMER(2102);
	int retval = UTL_GetPinWstrbExp( arg1, arg2);
	STOP_LAPTIMER(2102);
	return retval;
}
int _UTL_GetPinWstrbBank( PinWstrbHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2103] = "UTL_GetPinWstrbBank";
	START_LAPTIMER(2103);
	int retval = UTL_GetPinWstrbBank( arg1, arg2);
	STOP_LAPTIMER(2103);
	return retval;
}
int _UTL_GetPinWstrbLeadingChannel( PinWstrbHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2104] = "UTL_GetPinWstrbLeadingChannel";
	START_LAPTIMER(2104);
	int retval = UTL_GetPinWstrbLeadingChannel( arg1, arg2);
	STOP_LAPTIMER(2104);
	return retval;
}
int _UTL_GetPinWstrbTrailingChannel( PinWstrbHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2105] = "UTL_GetPinWstrbTrailingChannel";
	START_LAPTIMER(2105);
	int retval = UTL_GetPinWstrbTrailingChannel( arg1, arg2);
	STOP_LAPTIMER(2105);
	return retval;
}
int _UTL_GetPinWstrbCpeMode( PinWstrbHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2106] = "UTL_GetPinWstrbCpeMode";
	START_LAPTIMER(2106);
	int retval = UTL_GetPinWstrbCpeMode( arg1, arg2);
	STOP_LAPTIMER(2106);
	return retval;
}
PinPdsCursor _UTL_GetPinPdsACursor( PinHandle  arg1)
{
	MCI_LIST[2107] = "UTL_GetPinPdsACursor";
	START_LAPTIMER(2107);
	PinPdsCursor retval = UTL_GetPinPdsACursor( arg1);
	STOP_LAPTIMER(2107);
	return retval;
}
PinPdsCursor _UTL_GetPinPdsBCursor( PinHandle  arg1)
{
	MCI_LIST[2108] = "UTL_GetPinPdsBCursor";
	START_LAPTIMER(2108);
	PinPdsCursor retval = UTL_GetPinPdsBCursor( arg1);
	STOP_LAPTIMER(2108);
	return retval;
}
PinPdsCursor _UTL_GetPinPdsDCursor( PinHandle  arg1)
{
	MCI_LIST[2109] = "UTL_GetPinPdsDCursor";
	START_LAPTIMER(2109);
	PinPdsCursor retval = UTL_GetPinPdsDCursor( arg1);
	STOP_LAPTIMER(2109);
	return retval;
}
PinPdsCursor _UTL_GetPinPdsECursor( PinHandle  arg1)
{
	MCI_LIST[2110] = "UTL_GetPinPdsECursor";
	START_LAPTIMER(2110);
	PinPdsCursor retval = UTL_GetPinPdsECursor( arg1);
	STOP_LAPTIMER(2110);
	return retval;
}
PinPdsHandle _UTL_NextPinPds( PinPdsCursor  arg1)
{
	MCI_LIST[2111] = "UTL_NextPinPds";
	START_LAPTIMER(2111);
	PinPdsHandle retval = UTL_NextPinPds( arg1);
	STOP_LAPTIMER(2111);
	return retval;
}
int _UTL_GetPinPdsName( PinPdsHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2112] = "UTL_GetPinPdsName";
	START_LAPTIMER(2112);
	int retval = UTL_GetPinPdsName( arg1, arg2);
	STOP_LAPTIMER(2112);
	return retval;
}
int _UTL_GetPinPdsNumber( PinPdsHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2113] = "UTL_GetPinPdsNumber";
	START_LAPTIMER(2113);
	int retval = UTL_GetPinPdsNumber( arg1, arg2);
	STOP_LAPTIMER(2113);
	return retval;
}
int _UTL_GetPinCyclePaletteNumber( PinPdsHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2114] = "UTL_GetPinCyclePaletteNumber";
	START_LAPTIMER(2114);
	int retval = UTL_GetPinCyclePaletteNumber( arg1, arg2);
	STOP_LAPTIMER(2114);
	return retval;
}
int _UTL_GetPinVsBypassCapacitor( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2115] = "UTL_GetPinVsBypassCapacitor";
	START_LAPTIMER(2115);
	int retval = UTL_GetPinVsBypassCapacitor( arg1, arg2);
	STOP_LAPTIMER(2115);
	return retval;
}
int _UTL_GetPinVsBypassCapacitorNumber( PinHandle  arg1, RadioButton  arg2, CheckButton * arg3)
{
	MCI_LIST[2116] = "UTL_GetPinVsBypassCapacitorNumber";
	START_LAPTIMER(2116);
	int retval = UTL_GetPinVsBypassCapacitorNumber( arg1, arg2, arg3);
	STOP_LAPTIMER(2116);
	return retval;
}
int _UTL_GetPinVsDisconnect( PinHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2117] = "UTL_GetPinVsDisconnect";
	START_LAPTIMER(2117);
	int retval = UTL_GetPinVsDisconnect( arg1, arg2);
	STOP_LAPTIMER(2117);
	return retval;
}
int _UTL_GetPmAccessAllDut( PmAccessHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2118] = "UTL_GetPmAccessAllDut";
	START_LAPTIMER(2118);
	int retval = UTL_GetPmAccessAllDut( arg1, arg2);
	STOP_LAPTIMER(2118);
	return retval;
}
int _UTL_GetPmAccessDut( PmAccessHandle  arg1, UT_DUT * arg2)
{
	MCI_LIST[2119] = "UTL_GetPmAccessDut";
	START_LAPTIMER(2119);
	int retval = UTL_GetPmAccessDut( arg1, arg2);
	STOP_LAPTIMER(2119);
	return retval;
}
int _UTL_GetPmAccessPresetAllMemory( PmAccessHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2120] = "UTL_GetPmAccessPresetAllMemory";
	START_LAPTIMER(2120);
	int retval = UTL_GetPmAccessPresetAllMemory( arg1, arg2);
	STOP_LAPTIMER(2120);
	return retval;
}
int _UTL_GetPmAccessStartAddr( PmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[2121] = "UTL_GetPmAccessStartAddr";
	START_LAPTIMER(2121);
	int retval = UTL_GetPmAccessStartAddr( arg1, arg2);
	STOP_LAPTIMER(2121);
	return retval;
}
int _UTL_GetPmAccessStopAddr( PmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[2122] = "UTL_GetPmAccessStopAddr";
	START_LAPTIMER(2122);
	int retval = UTL_GetPmAccessStopAddr( arg1, arg2);
	STOP_LAPTIMER(2122);
	return retval;
}
int _UTL_GetPmAccessAddrAssign( PmAccessHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[2123] = "UTL_GetPmAccessAddrAssign";
	START_LAPTIMER(2123);
	int retval = UTL_GetPmAccessAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(2123);
	return retval;
}
int _UTL_GetPmAccessStartXAddr( PmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[2124] = "UTL_GetPmAccessStartXAddr";
	START_LAPTIMER(2124);
	int retval = UTL_GetPmAccessStartXAddr( arg1, arg2);
	STOP_LAPTIMER(2124);
	return retval;
}
int _UTL_GetPmAccessEndXAddr( PmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[2125] = "UTL_GetPmAccessEndXAddr";
	START_LAPTIMER(2125);
	int retval = UTL_GetPmAccessEndXAddr( arg1, arg2);
	STOP_LAPTIMER(2125);
	return retval;
}
int _UTL_GetPmAccessStartYAddr( PmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[2126] = "UTL_GetPmAccessStartYAddr";
	START_LAPTIMER(2126);
	int retval = UTL_GetPmAccessStartYAddr( arg1, arg2);
	STOP_LAPTIMER(2126);
	return retval;
}
int _UTL_GetPmAccessEndYAddr( PmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[2127] = "UTL_GetPmAccessEndYAddr";
	START_LAPTIMER(2127);
	int retval = UTL_GetPmAccessEndYAddr( arg1, arg2);
	STOP_LAPTIMER(2127);
	return retval;
}
int _UTL_GetPmAccessStartZAddr( PmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[2128] = "UTL_GetPmAccessStartZAddr";
	START_LAPTIMER(2128);
	int retval = UTL_GetPmAccessStartZAddr( arg1, arg2);
	STOP_LAPTIMER(2128);
	return retval;
}
int _UTL_GetPmAccessEndZAddr( PmAccessHandle  arg1, USlider * arg2)
{
	MCI_LIST[2129] = "UTL_GetPmAccessEndZAddr";
	START_LAPTIMER(2129);
	int retval = UTL_GetPmAccessEndZAddr( arg1, arg2);
	STOP_LAPTIMER(2129);
	return retval;
}
int _UTL_GetPmAccessBitBlock( PmAccessHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2130] = "UTL_GetPmAccessBitBlock";
	START_LAPTIMER(2130);
	int retval = UTL_GetPmAccessBitBlock( arg1, arg2);
	STOP_LAPTIMER(2130);
	return retval;
}
int _UTL_GetPmAccessBitMode( PmAccessHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2131] = "UTL_GetPmAccessBitMode";
	START_LAPTIMER(2131);
	int retval = UTL_GetPmAccessBitMode( arg1, arg2);
	STOP_LAPTIMER(2131);
	return retval;
}
int _UTL_GetPmAccessCompactionMode( PmAccessHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2132] = "UTL_GetPmAccessCompactionMode";
	START_LAPTIMER(2132);
	int retval = UTL_GetPmAccessCompactionMode( arg1, arg2);
	STOP_LAPTIMER(2132);
	return retval;
}
int _UTL_GetPmAccessApLink( PmAccessHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2133] = "UTL_GetPmAccessApLink";
	START_LAPTIMER(2133);
	int retval = UTL_GetPmAccessApLink( arg1, arg2);
	STOP_LAPTIMER(2133);
	return retval;
}
int _UTL_GetPmAccessAllBit( PmAccessHandle arg1, CheckButton * arg2)
{
	MCI_LIST[2134] = "UTL_GetPmAccessAllBit";
	START_LAPTIMER(2134);
	int retval = UTL_GetPmAccessAllBit( arg1, arg2);
	STOP_LAPTIMER(2134);
	return retval;
}
PmAccessBitCursor _UTL_GetPmAccessBitCursor( PmAccessHandle arg1)
{
	MCI_LIST[2135] = "UTL_GetPmAccessBitCursor";
	START_LAPTIMER(2135);
	PmAccessBitCursor retval = UTL_GetPmAccessBitCursor( arg1);
	STOP_LAPTIMER(2135);
	return retval;
}
RadioButton _UTL_NextPmAccessBit( PmAccessBitCursor arg1)
{
	MCI_LIST[2136] = "UTL_NextPmAccessBit";
	START_LAPTIMER(2136);
	RadioButton retval = UTL_NextPmAccessBit( arg1);
	STOP_LAPTIMER(2136);
	return retval;
}
void _UTL_UpdatePmConfig( PmConfigHandle arg1)
{
	MCI_LIST[2137] = "UTL_UpdatePmConfig";
	START_LAPTIMER(2137);
	UTL_UpdatePmConfig( arg1);
	STOP_LAPTIMER(2137);
}
int _UTL_GetPmConfigAction( PmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2138] = "UTL_GetPmConfigAction";
	START_LAPTIMER(2138);
	int retval = UTL_GetPmConfigAction( arg1, arg2);
	STOP_LAPTIMER(2138);
	return retval;
}
int _UTL_GetPmConfigAddrAssign( PmConfigHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[2139] = "UTL_GetPmConfigAddrAssign";
	START_LAPTIMER(2139);
	int retval = UTL_GetPmConfigAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(2139);
	return retval;
}
int _UTL_GetPmConfigBitSize( PmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[2140] = "UTL_GetPmConfigBitSize";
	START_LAPTIMER(2140);
	int retval = UTL_GetPmConfigBitSize( arg1, arg2);
	STOP_LAPTIMER(2140);
	return retval;
}
int _UTL_GetPmConfigFixData( PmConfigHandle  arg1, RadioButton  arg2, USlider * arg3)
{
	MCI_LIST[2141] = "UTL_GetPmConfigFixData";
	START_LAPTIMER(2141);
	int retval = UTL_GetPmConfigFixData( arg1, arg2, arg3);
	STOP_LAPTIMER(2141);
	return retval;
}
int _UTL_GetPmConfigRate( PmConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2142] = "UTL_GetPmConfigRate";
	START_LAPTIMER(2142);
	int retval = UTL_GetPmConfigRate( arg1, arg2);
	STOP_LAPTIMER(2142);
	return retval;
}
void _UTL_UpdatePowerCtrl( PowerCtrlHandle arg1)
{
	MCI_LIST[2143] = "UTL_UpdatePowerCtrl";
	START_LAPTIMER(2143);
	UTL_UpdatePowerCtrl( arg1);
	STOP_LAPTIMER(2143);
}
void _UTL_UpdatePowerSeq( PowerSeqHandle arg1)
{
	MCI_LIST[2144] = "UTL_UpdatePowerSeq";
	START_LAPTIMER(2144);
	UTL_UpdatePowerSeq( arg1);
	STOP_LAPTIMER(2144);
}
PowerUnitCursor _UTL_GetPowerCtrlUnitCursor( PowerCtrlHandle  arg1)
{
	MCI_LIST[2145] = "UTL_GetPowerCtrlUnitCursor";
	START_LAPTIMER(2145);
	PowerUnitCursor retval = UTL_GetPowerCtrlUnitCursor( arg1);
	STOP_LAPTIMER(2145);
	return retval;
}
int _UTL_GetPowerCtrlWaitTime( PowerCtrlHandle  arg1, DSlider * arg2)
{
	MCI_LIST[2146] = "UTL_GetPowerCtrlWaitTime";
	START_LAPTIMER(2146);
	int retval = UTL_GetPowerCtrlWaitTime( arg1, arg2);
	STOP_LAPTIMER(2146);
	return retval;
}
int _UTL_GetPowerSeqId( PowerSeqHandle  arg1, USlider  arg2, USlider * arg3)
{
	MCI_LIST[2147] = "UTL_GetPowerSeqId";
	START_LAPTIMER(2147);
	int retval = UTL_GetPowerSeqId( arg1, arg2, arg3);
	STOP_LAPTIMER(2147);
	return retval;
}
PowerUnitCursor _UTL_GetPowerSeqUnitCursor( PowerSeqHandle  arg1, USlider  arg2)
{
	MCI_LIST[2148] = "UTL_GetPowerSeqUnitCursor";
	START_LAPTIMER(2148);
	PowerUnitCursor retval = UTL_GetPowerSeqUnitCursor( arg1, arg2);
	STOP_LAPTIMER(2148);
	return retval;
}
RadioButton _UTL_NextPowerUnit( PowerUnitCursor  arg1)
{
	MCI_LIST[2149] = "UTL_NextPowerUnit";
	START_LAPTIMER(2149);
	RadioButton retval = UTL_NextPowerUnit( arg1);
	STOP_LAPTIMER(2149);
	return retval;
}
int _UTL_GetPowerSeqWaitTime( PowerSeqHandle  arg1, USlider  arg2, DSlider * arg3)
{
	MCI_LIST[2150] = "UTL_GetPowerSeqWaitTime";
	START_LAPTIMER(2150);
	int retval = UTL_GetPowerSeqWaitTime( arg1, arg2, arg3);
	STOP_LAPTIMER(2150);
	return retval;
}
int _UTL_GetPowerUnitChannelNumber( RadioButton  arg1, RadioButton * arg2)
{
	MCI_LIST[2151] = "UTL_GetPowerUnitChannelNumber";
	START_LAPTIMER(2151);
	int retval = UTL_GetPowerUnitChannelNumber( arg1, arg2);
	STOP_LAPTIMER(2151);
	return retval;
}
int _UTL_GetPowerUnitType( RadioButton  arg1, RadioButton * arg2)
{
	MCI_LIST[2152] = "UTL_GetPowerUnitType";
	START_LAPTIMER(2152);
	int retval = UTL_GetPowerUnitType( arg1, arg2);
	STOP_LAPTIMER(2152);
	return retval;
}
int _UTL_GetRfcmAccessDut( RfcmAccessHandle  arg1, UT_DUT * arg2)
{
	MCI_LIST[2153] = "UTL_GetRfcmAccessDut";
	START_LAPTIMER(2153);
	int retval = UTL_GetRfcmAccessDut( arg1, arg2);
	STOP_LAPTIMER(2153);
	return retval;
}
int _UTL_GetRfcmAccessPresetAllMemory( RfcmAccessHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2154] = "UTL_GetRfcmAccessPresetAllMemory";
	START_LAPTIMER(2154);
	int retval = UTL_GetRfcmAccessPresetAllMemory( arg1, arg2);
	STOP_LAPTIMER(2154);
	return retval;
}
void _UTL_UpdateRfcmConfig( RfcmConfigHandle arg1)
{
	MCI_LIST[2155] = "UTL_UpdateRfcmConfig";
	START_LAPTIMER(2155);
	UTL_UpdateRfcmConfig( arg1);
	STOP_LAPTIMER(2155);
}
int _UTL_GetRfcmConfigAddrAssign( RfcmConfigHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[2156] = "UTL_GetRfcmConfigAddrAssign";
	START_LAPTIMER(2156);
	int retval = UTL_GetRfcmConfigAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(2156);
	return retval;
}
int _UTL_GetRfcmConfigClearSignal( RfcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2157] = "UTL_GetRfcmConfigClearSignal";
	START_LAPTIMER(2157);
	int retval = UTL_GetRfcmConfigClearSignal( arg1, arg2);
	STOP_LAPTIMER(2157);
	return retval;
}
int _UTL_GetRfcmConfigFccLimit( RfcmConfigHandle  arg1, UT_DUT  arg2, USlider * arg3)
{
	MCI_LIST[2158] = "UTL_GetRfcmConfigFccLimit";
	START_LAPTIMER(2158);
	int retval = UTL_GetRfcmConfigFccLimit( arg1, arg2, arg3);
	STOP_LAPTIMER(2158);
	return retval;
}
int _UTL_GetRfcmConfigMode( RfcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2159] = "UTL_GetRfcmConfigMode";
	START_LAPTIMER(2159);
	int retval = UTL_GetRfcmConfigMode( arg1, arg2);
	STOP_LAPTIMER(2159);
	return retval;
}
int _UTL_GetRfcmConfigRfcsmClearSignal( RfcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2160] = "UTL_GetRfcmConfigRfcsmClearSignal";
	START_LAPTIMER(2160);
	int retval = UTL_GetRfcmConfigRfcsmClearSignal( arg1, arg2);
	STOP_LAPTIMER(2160);
	return retval;
}
int _UTL_GetRfcmConfigRfcsmLimit( RfcmConfigHandle  arg1, UT_DUT  arg2, USlider * arg3)
{
	MCI_LIST[2161] = "UTL_GetRfcmConfigRfcsmLimit";
	START_LAPTIMER(2161);
	int retval = UTL_GetRfcmConfigRfcsmLimit( arg1, arg2, arg3);
	STOP_LAPTIMER(2161);
	return retval;
}
int _UTL_GetRfcmConfigRfcsmTransferMode( RfcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2162] = "UTL_GetRfcmConfigRfcsmTransferMode";
	START_LAPTIMER(2162);
	int retval = UTL_GetRfcmConfigRfcsmTransferMode( arg1, arg2);
	STOP_LAPTIMER(2162);
	return retval;
}
int _UTL_GetRfcmConfigRfcsmTransferSignal( RfcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2163] = "UTL_GetRfcmConfigRfcsmTransferSignal";
	START_LAPTIMER(2163);
	int retval = UTL_GetRfcmConfigRfcsmTransferSignal( arg1, arg2);
	STOP_LAPTIMER(2163);
	return retval;
}
int _UTL_GetRfcmConfigStopAddr( RfcmConfigHandle  arg1, USlider * arg2)
{
	MCI_LIST[2164] = "UTL_GetRfcmConfigStopAddr";
	START_LAPTIMER(2164);
	int retval = UTL_GetRfcmConfigStopAddr( arg1, arg2);
	STOP_LAPTIMER(2164);
	return retval;
}
int _UTL_GetRfcmConfigTransferSignal( RfcmConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2165] = "UTL_GetRfcmConfigTransferSignal";
	START_LAPTIMER(2165);
	int retval = UTL_GetRfcmConfigTransferSignal( arg1, arg2);
	STOP_LAPTIMER(2165);
	return retval;
}
void _UTL_UpdateTg( TgHandle arg1)
{
	MCI_LIST[2166] = "UTL_UpdateTg";
	START_LAPTIMER(2166);
	UTL_UpdateTg( arg1);
	STOP_LAPTIMER(2166);
}
int _UTL_GetTgAclk( TgHandle  arg1, RadioButton  arg2, RadioButton  arg3, DSlider * arg4)
{
	MCI_LIST[2167] = "UTL_GetTgAclk";
	START_LAPTIMER(2167);
	int retval = UTL_GetTgAclk( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2167);
	return retval;
}
int _UTL_GetTgAclkOff( TgHandle  arg1, RadioButton  arg2, RadioButton  arg3, CheckButton * arg4)
{
	MCI_LIST[2168] = "UTL_GetTgAclkOff";
	START_LAPTIMER(2168);
	int retval = UTL_GetTgAclkOff( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2168);
	return retval;
}
int _UTL_GetTgBclk( TgHandle  arg1, RadioButton  arg2, RadioButton  arg3, DSlider * arg4)
{
	MCI_LIST[2169] = "UTL_GetTgBclk";
	START_LAPTIMER(2169);
	int retval = UTL_GetTgBclk( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2169);
	return retval;
}
int _UTL_GetTgBclkOff( TgHandle  arg1, RadioButton  arg2, RadioButton  arg3, CheckButton * arg4)
{
	MCI_LIST[2170] = "UTL_GetTgBclkOff";
	START_LAPTIMER(2170);
	int retval = UTL_GetTgBclkOff( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2170);
	return retval;
}
int _UTL_GetTgCclk( TgHandle  arg1, RadioButton  arg2, RadioButton  arg3, DSlider * arg4)
{
	MCI_LIST[2171] = "UTL_GetTgCclk";
	START_LAPTIMER(2171);
	int retval = UTL_GetTgCclk( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2171);
	return retval;
}
int _UTL_GetTgCclkOff( TgHandle  arg1, RadioButton  arg2, RadioButton  arg3, CheckButton * arg4)
{
	MCI_LIST[2172] = "UTL_GetTgCclkOff";
	START_LAPTIMER(2172);
	int retval = UTL_GetTgCclkOff( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2172);
	return retval;
}
int _UTL_GetTgStrbOff( TgHandle  arg1, RadioButton  arg2, RadioButton  arg3, CheckButton * arg4)
{
	MCI_LIST[2173] = "UTL_GetTgStrbOff";
	START_LAPTIMER(2173);
	int retval = UTL_GetTgStrbOff( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2173);
	return retval;
}
int _UTL_GetTgDreL( TgHandle  arg1, RadioButton  arg2, RadioButton  arg3, DSlider * arg4)
{
	MCI_LIST[2174] = "UTL_GetTgDreL";
	START_LAPTIMER(2174);
	int retval = UTL_GetTgDreL( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2174);
	return retval;
}
int _UTL_GetTgDreLOff( TgHandle  arg1, RadioButton  arg2, RadioButton  arg3, CheckButton * arg4)
{
	MCI_LIST[2175] = "UTL_GetTgDreLOff";
	START_LAPTIMER(2175);
	int retval = UTL_GetTgDreLOff( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2175);
	return retval;
}
int _UTL_GetTgDreT( TgHandle  arg1, RadioButton  arg2, RadioButton  arg3, DSlider * arg4)
{
	MCI_LIST[2176] = "UTL_GetTgDreT";
	START_LAPTIMER(2176);
	int retval = UTL_GetTgDreT( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2176);
	return retval;
}
int _UTL_GetTgDreTOff( TgHandle  arg1, RadioButton  arg2, RadioButton  arg3, CheckButton * arg4)
{
	MCI_LIST[2177] = "UTL_GetTgDreTOff";
	START_LAPTIMER(2177);
	int retval = UTL_GetTgDreTOff( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2177);
	return retval;
}
int _UTL_GetTgPairStrbL( TgHandle  arg1, RadioButton  arg2, RadioButton  arg3, DSlider * arg4)
{
	MCI_LIST[2178] = "UTL_GetTgPairStrbL";
	START_LAPTIMER(2178);
	int retval = UTL_GetTgPairStrbL( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2178);
	return retval;
}
int _UTL_GetTgPairStrbT( TgHandle  arg1, RadioButton  arg2, RadioButton  arg3, DSlider * arg4)
{
	MCI_LIST[2179] = "UTL_GetTgPairStrbT";
	START_LAPTIMER(2179);
	int retval = UTL_GetTgPairStrbT( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2179);
	return retval;
}
int _UTL_GetTgRate( TgHandle  arg1, RadioButton  arg2, DSlider * arg3)
{
	MCI_LIST[2180] = "UTL_GetTgRate";
	START_LAPTIMER(2180);
	int retval = UTL_GetTgRate( arg1, arg2, arg3);
	STOP_LAPTIMER(2180);
	return retval;
}
int _UTL_GetTgStrb( TgHandle  arg1, RadioButton  arg2, RadioButton  arg3, DSlider * arg4)
{
	MCI_LIST[2181] = "UTL_GetTgStrb";
	START_LAPTIMER(2181);
	int retval = UTL_GetTgStrb( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2181);
	return retval;
}
int _UTL_GetTgDrzPulseWidth( TgHandle  arg1, RadioButton  arg2, DSlider * arg3)
{
	MCI_LIST[2182] = "UTL_GetTgDrzPulseWidth";
	START_LAPTIMER(2182);
	int retval = UTL_GetTgDrzPulseWidth( arg1, arg2, arg3);
	STOP_LAPTIMER(2182);
	return retval;
}
int _UTL_GetTgDreLOffset( TgHandle  arg1, RadioButton  arg2, DSlider * arg3)
{
	MCI_LIST[2183] = "UTL_GetTgDreLOffset";
	START_LAPTIMER(2183);
	int retval = UTL_GetTgDreLOffset( arg1, arg2, arg3);
	STOP_LAPTIMER(2183);
	return retval;
}
int _UTL_GetTgDreTOffset( TgHandle  arg1, RadioButton  arg2, DSlider * arg3)
{
	MCI_LIST[2184] = "UTL_GetTgDreTOffset";
	START_LAPTIMER(2184);
	int retval = UTL_GetTgDreTOffset( arg1, arg2, arg3);
	STOP_LAPTIMER(2184);
	return retval;
}
void _UTL_UpdateTgAdjust( TgAdjustHandle arg1)
{
	MCI_LIST[2185] = "UTL_UpdateTgAdjust";
	START_LAPTIMER(2185);
	UTL_UpdateTgAdjust( arg1);
	STOP_LAPTIMER(2185);
}
int _UTL_GetTgAdjustEachValue( TgAdjustHandle arg1, UT_DUT arg2, UT_PIN arg3, RadioButton arg4, RadioButton arg5, RadioButton arg6, DSlider * arg7)
{
	MCI_LIST[2186] = "UTL_GetTgAdjustEachValue";
	START_LAPTIMER(2186);
	int retval = UTL_GetTgAdjustEachValue( arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	STOP_LAPTIMER(2186);
	return retval;
}
void _UTL_UpdateTgBaseRate( TgBaseRateHandle arg1)
{
	MCI_LIST[2187] = "UTL_UpdateTgBaseRate";
	START_LAPTIMER(2187);
	UTL_UpdateTgBaseRate( arg1);
	STOP_LAPTIMER(2187);
}
int _UTL_GetTgBaseRate( TgBaseRateHandle arg1, DSlider * arg2)
{
	MCI_LIST[2188] = "UTL_GetTgBaseRate";
	START_LAPTIMER(2188);
	int retval = UTL_GetTgBaseRate( arg1, arg2);
	STOP_LAPTIMER(2188);
	return retval;
}
void _UTL_UpdateTgFixedDelayEdge( TgFixedDelayEdgeHandle arg1, UT_PIN arg2)
{
	MCI_LIST[2189] = "UTL_UpdateTgFixedDelayEdge";
	START_LAPTIMER(2189);
	UTL_UpdateTgFixedDelayEdge( arg1, arg2);
	STOP_LAPTIMER(2189);
}
int _UTL_GetTgFixedDelayEdgeTargetTs( TgFixedDelayEdgeHandle  arg1, RadioButton  arg2, CheckButton * arg3)
{
	MCI_LIST[2190] = "UTL_GetTgFixedDelayEdgeTargetTs";
	START_LAPTIMER(2190);
	int retval = UTL_GetTgFixedDelayEdgeTargetTs( arg1, arg2, arg3);
	STOP_LAPTIMER(2190);
	return retval;
}
int _UTL_GetTgFixedDelayEdgeValue( TgFixedDelayEdgeHandle  arg1, RadioButton  arg2, DSlider * arg3)
{
	MCI_LIST[2191] = "UTL_GetTgFixedDelayEdgeValue";
	START_LAPTIMER(2191);
	int retval = UTL_GetTgFixedDelayEdgeValue( arg1, arg2, arg3);
	STOP_LAPTIMER(2191);
	return retval;
}
PinCursor _UTL_GetTgFixedDelayEdgeTargetPinCursor( TgFixedDelayEdgeHandle  arg1)
{
	MCI_LIST[2192] = "UTL_GetTgFixedDelayEdgeTargetPinCursor";
	START_LAPTIMER(2192);
	PinCursor retval = UTL_GetTgFixedDelayEdgeTargetPinCursor( arg1);
	STOP_LAPTIMER(2192);
	return retval;
}
void _UTL_UpdateLevelHold( LevelHoldHandle arg1)
{
	MCI_LIST[2193] = "UTL_UpdateLevelHold";
	START_LAPTIMER(2193);
	UTL_UpdateLevelHold( arg1);
	STOP_LAPTIMER(2193);
}
int _UTL_GetLevelHoldInit( LevelHoldHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2194] = "UTL_GetLevelHoldInit";
	START_LAPTIMER(2194);
	int retval = UTL_GetLevelHoldInit( arg1, arg2);
	STOP_LAPTIMER(2194);
	return retval;
}
void _UTL_UpdateDbmDelay( DbmDelayHandle arg1)
{
	MCI_LIST[2195] = "UTL_UpdateDbmDelay";
	START_LAPTIMER(2195);
	UTL_UpdateDbmDelay( arg1);
	STOP_LAPTIMER(2195);
}
int _UTL_GetDbmDelayInhibit( DbmDelayHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2196] = "UTL_GetDbmDelayInhibit";
	START_LAPTIMER(2196);
	int retval = UTL_GetDbmDelayInhibit( arg1, arg2);
	STOP_LAPTIMER(2196);
	return retval;
}
int _UTL_GetCfmAccessAlpgUnit( CfmAccessHandle  arg1, RadioButton *  arg2)
{
	MCI_LIST[2197] = "UTL_GetCfmAccessAlpgUnit";
	START_LAPTIMER(2197);
	int retval = UTL_GetCfmAccessAlpgUnit( arg1, arg2);
	STOP_LAPTIMER(2197);
	return retval;
}
int _UTL_GetCfmAccessActionNumber( CfmAccessHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[2198] = "UTL_GetCfmAccessActionNumber";
	START_LAPTIMER(2198);
	int retval = UTL_GetCfmAccessActionNumber( arg1, arg2, arg3);
	STOP_LAPTIMER(2198);
	return retval;
}
int _UTL_GetCfmAccessBitMode( CfmAccessHandle  arg1, RadioButton *  arg2)
{
	MCI_LIST[2199] = "UTL_GetCfmAccessBitMode";
	START_LAPTIMER(2199);
	int retval = UTL_GetCfmAccessBitMode( arg1, arg2);
	STOP_LAPTIMER(2199);
	return retval;
}
int _UTL_GetCfmAccessAllBit( CfmAccessHandle  arg1, CheckButton *  arg2)
{
	MCI_LIST[2200] = "UTL_GetCfmAccessAllBit";
	START_LAPTIMER(2200);
	int retval = UTL_GetCfmAccessAllBit( arg1, arg2);
	STOP_LAPTIMER(2200);
	return retval;
}
int _UTL_GetCfmAccessBitBlock( CfmAccessHandle  arg1, RadioButton *  arg2)
{
	MCI_LIST[2201] = "UTL_GetCfmAccessBitBlock";
	START_LAPTIMER(2201);
	int retval = UTL_GetCfmAccessBitBlock( arg1, arg2);
	STOP_LAPTIMER(2201);
	return retval;
}
int _UTL_GetCfmAccessPresetAllMemory( CfmAccessHandle  arg1, CheckButton *  arg2)
{
	MCI_LIST[2202] = "UTL_GetCfmAccessPresetAllMemory";
	START_LAPTIMER(2202);
	int retval = UTL_GetCfmAccessPresetAllMemory( arg1, arg2);
	STOP_LAPTIMER(2202);
	return retval;
}
int _UTL_GetCfmAccessAddrAssign( CfmAccessHandle  arg1, RadioButton  arg2, RadioButton *  arg3)
{
	MCI_LIST[2203] = "UTL_GetCfmAccessAddrAssign";
	START_LAPTIMER(2203);
	int retval = UTL_GetCfmAccessAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(2203);
	return retval;
}
int _UTL_GetCfmAccessApLink( CfmAccessHandle  arg1, RadioButton *  arg2)
{
	MCI_LIST[2204] = "UTL_GetCfmAccessApLink";
	START_LAPTIMER(2204);
	int retval = UTL_GetCfmAccessApLink( arg1, arg2);
	STOP_LAPTIMER(2204);
	return retval;
}
int _UTL_GetCfmAccessStartXAddr( CfmAccessHandle  arg1, USlider *  arg2)
{
	MCI_LIST[2205] = "UTL_GetCfmAccessStartXAddr";
	START_LAPTIMER(2205);
	int retval = UTL_GetCfmAccessStartXAddr( arg1, arg2);
	STOP_LAPTIMER(2205);
	return retval;
}
int _UTL_GetCfmAccessEndXAddr( CfmAccessHandle  arg1, USlider *  arg2)
{
	MCI_LIST[2206] = "UTL_GetCfmAccessEndXAddr";
	START_LAPTIMER(2206);
	int retval = UTL_GetCfmAccessEndXAddr( arg1, arg2);
	STOP_LAPTIMER(2206);
	return retval;
}
int _UTL_GetCfmAccessStartYAddr( CfmAccessHandle  arg1, USlider *  arg2)
{
	MCI_LIST[2207] = "UTL_GetCfmAccessStartYAddr";
	START_LAPTIMER(2207);
	int retval = UTL_GetCfmAccessStartYAddr( arg1, arg2);
	STOP_LAPTIMER(2207);
	return retval;
}
int _UTL_GetCfmAccessEndYAddr( CfmAccessHandle  arg1, USlider *  arg2)
{
	MCI_LIST[2208] = "UTL_GetCfmAccessEndYAddr";
	START_LAPTIMER(2208);
	int retval = UTL_GetCfmAccessEndYAddr( arg1, arg2);
	STOP_LAPTIMER(2208);
	return retval;
}
int _UTL_GetCfmAccessStartZAddr( CfmAccessHandle  arg1, USlider *  arg2)
{
	MCI_LIST[2209] = "UTL_GetCfmAccessStartZAddr";
	START_LAPTIMER(2209);
	int retval = UTL_GetCfmAccessStartZAddr( arg1, arg2);
	STOP_LAPTIMER(2209);
	return retval;
}
int _UTL_GetCfmAccessEndZAddr( CfmAccessHandle  arg1, USlider *  arg2)
{
	MCI_LIST[2210] = "UTL_GetCfmAccessEndZAddr";
	START_LAPTIMER(2210);
	int retval = UTL_GetCfmAccessEndZAddr( arg1, arg2);
	STOP_LAPTIMER(2210);
	return retval;
}
int _UTL_GetCfmAccessAllDut( CfmAccessHandle  arg1, CheckButton *  arg2)
{
	MCI_LIST[2211] = "UTL_GetCfmAccessAllDut";
	START_LAPTIMER(2211);
	int retval = UTL_GetCfmAccessAllDut( arg1, arg2);
	STOP_LAPTIMER(2211);
	return retval;
}
int _UTL_GetCfmAccessDut( CfmAccessHandle  arg1, UT_DUT *  arg2)
{
	MCI_LIST[2212] = "UTL_GetCfmAccessDut";
	START_LAPTIMER(2212);
	int retval = UTL_GetCfmAccessDut( arg1, arg2);
	STOP_LAPTIMER(2212);
	return retval;
}
CfmAccessBitCursor _UTL_GetCfmAccessBitCursor( CfmAccessHandle  arg1)
{
	MCI_LIST[2213] = "UTL_GetCfmAccessBitCursor";
	START_LAPTIMER(2213);
	CfmAccessBitCursor retval = UTL_GetCfmAccessBitCursor( arg1);
	STOP_LAPTIMER(2213);
	return retval;
}
RadioButton _UTL_NextCfmAccessBit( CfmAccessBitCursor  arg1)
{
	MCI_LIST[2214] = "UTL_NextCfmAccessBit";
	START_LAPTIMER(2214);
	RadioButton retval = UTL_NextCfmAccessBit( arg1);
	STOP_LAPTIMER(2214);
	return retval;
}
void _UTL_UpdateCfmConfig( CfmConfigHandle arg1)
{
	MCI_LIST[2215] = "UTL_UpdateCfmConfig";
	START_LAPTIMER(2215);
	UTL_UpdateCfmConfig( arg1);
	STOP_LAPTIMER(2215);
}
int _UTL_GetCfmConfigAddrAssign( CfmConfigHandle  arg1, RadioButton  arg2, RadioButton *  arg3)
{
	MCI_LIST[2216] = "UTL_GetCfmConfigAddrAssign";
	START_LAPTIMER(2216);
	int retval = UTL_GetCfmConfigAddrAssign( arg1, arg2, arg3);
	STOP_LAPTIMER(2216);
	return retval;
}
int _UTL_GetCfmConfigAddrAssignByAlpg( CfmConfigHandle  arg1, RadioButton  arg2, RadioButton  arg3, RadioButton *  arg4)
{
	MCI_LIST[2217] = "UTL_GetCfmConfigAddrAssignByAlpg";
	START_LAPTIMER(2217);
	int retval = UTL_GetCfmConfigAddrAssignByAlpg( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2217);
	return retval;
}
void _UTL_UpdateLevelFix( LevelFixHandle arg1, UT_PIN arg2, UT_DUT arg3)
{
	MCI_LIST[2218] = "UTL_UpdateLevelFix";
	START_LAPTIMER(2218);
	UTL_UpdateLevelFix( arg1, arg2, arg3);
	STOP_LAPTIMER(2218);
}
int _UTL_GetLevelFixOutputLevel( LevelFixHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[2219] = "UTL_GetLevelFixOutputLevel";
	START_LAPTIMER(2219);
	int retval = UTL_GetLevelFixOutputLevel( arg1, arg2, arg3);
	STOP_LAPTIMER(2219);
	return retval;
}
void _UTL_UpdateRteMask( RteMaskHandle arg1)
{
	MCI_LIST[2220] = "UTL_UpdateRteMask";
	START_LAPTIMER(2220);
	UTL_UpdateRteMask( arg1);
	STOP_LAPTIMER(2220);
}
int _UTL_GetRteMaskDcGuardAlarm( RteMaskHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2221] = "UTL_GetRteMaskDcGuardAlarm";
	START_LAPTIMER(2221);
	int retval = UTL_GetRteMaskDcGuardAlarm( arg1, arg2);
	STOP_LAPTIMER(2221);
	return retval;
}
int _UTL_GetRteMaskPpsGuardAlarm( RteMaskHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2222] = "UTL_GetRteMaskPpsGuardAlarm";
	START_LAPTIMER(2222);
	int retval = UTL_GetRteMaskPpsGuardAlarm( arg1, arg2);
	STOP_LAPTIMER(2222);
	return retval;
}
int _UTL_GetRteMaskPpsKelvinAlarm( RteMaskHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2223] = "UTL_GetRteMaskPpsKelvinAlarm";
	START_LAPTIMER(2223);
	int retval = UTL_GetRteMaskPpsKelvinAlarm( arg1, arg2);
	STOP_LAPTIMER(2223);
	return retval;
}
int _UTL_GetRteMaskLimiterFail( RteMaskHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2224] = "UTL_GetRteMaskLimiterFail";
	START_LAPTIMER(2224);
	int retval = UTL_GetRteMaskLimiterFail( arg1, arg2);
	STOP_LAPTIMER(2224);
	return retval;
}
MemoryModulePurposeCursor _UTL_GetMemoryModulePurposeCursor( MemoryModuleHandle  arg1)
{
	MCI_LIST[2225] = "UTL_GetMemoryModulePurposeCursor";
	START_LAPTIMER(2225);
	MemoryModulePurposeCursor retval = UTL_GetMemoryModulePurposeCursor( arg1);
	STOP_LAPTIMER(2225);
	return retval;
}
RadioButton _UTL_NextMemoryModulePurpose( MemoryModulePurposeCursor  arg1)
{
	MCI_LIST[2226] = "UTL_NextMemoryModulePurpose";
	START_LAPTIMER(2226);
	RadioButton retval = UTL_NextMemoryModulePurpose( arg1);
	STOP_LAPTIMER(2226);
	return retval;
}
USlider _UTL_GetMemoryModulePurposeCount( MemoryModuleHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[2227] = "UTL_GetMemoryModulePurposeCount";
	START_LAPTIMER(2227);
	USlider retval = UTL_GetMemoryModulePurposeCount( arg1, arg2);
	STOP_LAPTIMER(2227);
	return retval;
}
void _UTL_UpdateMemoryModule( MemoryModuleHandle  arg1)
{
	MCI_LIST[2228] = "UTL_UpdateMemoryModule";
	START_LAPTIMER(2228);
	UTL_UpdateMemoryModule( arg1);
	STOP_LAPTIMER(2228);
}
int _UTL_GetFailSelPinTarget( FailSelPinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2229] = "UTL_GetFailSelPinTarget";
	START_LAPTIMER(2229);
	int retval = UTL_GetFailSelPinTarget( arg1, arg2);
	STOP_LAPTIMER(2229);
	return retval;
}
PinCursor _UTL_GetFailSelPinAssignCursor( FailSelPinHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[2230] = "UTL_GetFailSelPinAssignCursor";
	START_LAPTIMER(2230);
	PinCursor retval = UTL_GetFailSelPinAssignCursor( arg1, arg2);
	STOP_LAPTIMER(2230);
	return retval;
}
int _UTL_GetFailSelPin( FailSelPinHandle  arg1, RadioButton  arg2, CheckButton * arg3)
{
	MCI_LIST[2231] = "UTL_GetFailSelPin";
	START_LAPTIMER(2231);
	int retval = UTL_GetFailSelPin( arg1, arg2, arg3);
	STOP_LAPTIMER(2231);
	return retval;
}
void _UTL_UpdateFailSelPin( FailSelPinHandle arg1)
{
	MCI_LIST[2232] = "UTL_UpdateFailSelPin";
	START_LAPTIMER(2232);
	UTL_UpdateFailSelPin( arg1);
	STOP_LAPTIMER(2232);
}
void _UTL_UpdateIodMode( IodModeHandle arg1, UT_PIN arg2, UT_DUT arg3)
{
	MCI_LIST[2233] = "UTL_UpdateIodMode";
	START_LAPTIMER(2233);
	UTL_UpdateIodMode( arg1, arg2, arg3);
	STOP_LAPTIMER(2233);
}
int _UTL_GetIodMode( IodModeHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2234] = "UTL_GetIodMode";
	START_LAPTIMER(2234);
	int retval = UTL_GetIodMode( arg1, arg2);
	STOP_LAPTIMER(2234);
	return retval;
}
int _UTL_GetIodModeAuto( IodModeHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2235] = "UTL_GetIodModeAuto";
	START_LAPTIMER(2235);
	int retval = UTL_GetIodModeAuto( arg1, arg2);
	STOP_LAPTIMER(2235);
	return retval;
}
int _UTL_GetIodModeCalcFunc( IodModeHandle  arg1, void ** arg2)
{
	MCI_LIST[2236] = "UTL_GetIodModeCalcFunc";
	START_LAPTIMER(2236);
	int retval = UTL_GetIodModeCalcFunc( arg1, arg2);
	STOP_LAPTIMER(2236);
	return retval;
}
int _UTL_GetIodModeCalcFuncAndLibrary( IodModeHandle  arg1, char ** arg2, char ** arg3)
{
	MCI_LIST[2237] = "UTL_GetIodModeCalcFuncAndLibrary";
	START_LAPTIMER(2237);
	int retval = UTL_GetIodModeCalcFuncAndLibrary( arg1, arg2, arg3);
	STOP_LAPTIMER(2237);
	return retval;
}
PinCursor _UTL_GetIodModePinCursor( IodModeHandle  arg1)
{
	MCI_LIST[2238] = "UTL_GetIodModePinCursor";
	START_LAPTIMER(2238);
	PinCursor retval = UTL_GetIodModePinCursor( arg1);
	STOP_LAPTIMER(2238);
	return retval;
}
void _UTL_UpdateIod( IodHandle arg1, UT_PIN arg2, UT_DUT arg3)
{
	MCI_LIST[2239] = "UTL_UpdateIod";
	START_LAPTIMER(2239);
	UTL_UpdateIod( arg1, arg2, arg3);
	STOP_LAPTIMER(2239);
}
int _UTL_GetIodHigh( IodHandle  arg1, DSlider * arg2)
{
	MCI_LIST[2240] = "UTL_GetIodHigh";
	START_LAPTIMER(2240);
	int retval = UTL_GetIodHigh( arg1, arg2);
	STOP_LAPTIMER(2240);
	return retval;
}
int _UTL_GetIodLow( IodHandle  arg1, DSlider * arg2)
{
	MCI_LIST[2241] = "UTL_GetIodLow";
	START_LAPTIMER(2241);
	int retval = UTL_GetIodLow( arg1, arg2);
	STOP_LAPTIMER(2241);
	return retval;
}
PinCursor _UTL_GetIodPinCursor( IodHandle  arg1)
{
	MCI_LIST[2242] = "UTL_GetIodPinCursor";
	START_LAPTIMER(2242);
	PinCursor retval = UTL_GetIodPinCursor( arg1);
	STOP_LAPTIMER(2242);
	return retval;
}
DutCursor _UTL_GetIodDutCursor( IodHandle  arg1)
{
	MCI_LIST[2243] = "UTL_GetIodDutCursor";
	START_LAPTIMER(2243);
	DutCursor retval = UTL_GetIodDutCursor( arg1);
	STOP_LAPTIMER(2243);
	return retval;
}
void _UTL_UpdateSdc( SdcHandle arg1)
{
	MCI_LIST[2244] = "UTL_UpdateSdc";
	START_LAPTIMER(2244);
	UTL_UpdateSdc( arg1);
	STOP_LAPTIMER(2244);
}
int _UTL_GetSdcSourceHigh( SdcHandle arg1, DSlider * arg2)
{
	MCI_LIST[2245] = "UTL_GetSdcSourceHigh";
	START_LAPTIMER(2245);
	int retval = UTL_GetSdcSourceHigh( arg1, arg2);
	STOP_LAPTIMER(2245);
	return retval;
}
int _UTL_GetSdcSourceLow( SdcHandle arg1, DSlider * arg2)
{
	MCI_LIST[2246] = "UTL_GetSdcSourceLow";
	START_LAPTIMER(2246);
	int retval = UTL_GetSdcSourceLow( arg1, arg2);
	STOP_LAPTIMER(2246);
	return retval;
}
int _UTL_GetSdcComparisonHigh( SdcHandle arg1, DSlider * arg2)
{
	MCI_LIST[2247] = "UTL_GetSdcComparisonHigh";
	START_LAPTIMER(2247);
	int retval = UTL_GetSdcComparisonHigh( arg1, arg2);
	STOP_LAPTIMER(2247);
	return retval;
}
int _UTL_GetSdcComparisonLow( SdcHandle arg1, DSlider * arg2)
{
	MCI_LIST[2248] = "UTL_GetSdcComparisonLow";
	START_LAPTIMER(2248);
	int retval = UTL_GetSdcComparisonLow( arg1, arg2);
	STOP_LAPTIMER(2248);
	return retval;
}
int _UTL_GetSdcDctPinList( SdcDctHandle arg1, char ** arg2)
{
	MCI_LIST[2249] = "UTL_GetSdcDctPinList";
	START_LAPTIMER(2249);
	int retval = UTL_GetSdcDctPinList( arg1, arg2);
	STOP_LAPTIMER(2249);
	return retval;
}
int _UTL_GetSdcDctMeasPin( SdcDctHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2250] = "UTL_GetSdcDctMeasPin";
	START_LAPTIMER(2250);
	int retval = UTL_GetSdcDctMeasPin( arg1, arg2);
	STOP_LAPTIMER(2250);
	return retval;
}
int _UTL_GetSdcDctSourceSelect( SdcDctHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2251] = "UTL_GetSdcDctSourceSelect";
	START_LAPTIMER(2251);
	int retval = UTL_GetSdcDctSourceSelect( arg1, arg2);
	STOP_LAPTIMER(2251);
	return retval;
}
int _UTL_GetSdcDctPinDut( SdcDctPinHandle arg1, UT_DUT * arg2)
{
	MCI_LIST[2252] = "UTL_GetSdcDctPinDut";
	START_LAPTIMER(2252);
	int retval = UTL_GetSdcDctPinDut( arg1, arg2);
	STOP_LAPTIMER(2252);
	return retval;
}
int _UTL_GetSdcDctPinNumber( SdcDctPinHandle arg1, UT_PIN * arg2)
{
	MCI_LIST[2253] = "UTL_GetSdcDctPinNumber";
	START_LAPTIMER(2253);
	int retval = UTL_GetSdcDctPinNumber( arg1, arg2);
	STOP_LAPTIMER(2253);
	return retval;
}
int _UTL_GetSdcDctPinMode( SdcDctPinHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2254] = "UTL_GetSdcDctPinMode";
	START_LAPTIMER(2254);
	int retval = UTL_GetSdcDctPinMode( arg1, arg2);
	STOP_LAPTIMER(2254);
	return retval;
}
void _UTL_UpdateTimingTrainingCondition( TimingTrainingConditionHandle arg1, RadioButton arg2)
{
	MCI_LIST[2255] = "UTL_UpdateTimingTrainingCondition";
	START_LAPTIMER(2255);
	UTL_UpdateTimingTrainingCondition( arg1, arg2);
	STOP_LAPTIMER(2255);
}
PinCursor _UTL_GetTimingTrainingConditionTargetPinCursor( TimingTrainingConditionHandle arg1)
{
	MCI_LIST[2256] = "UTL_GetTimingTrainingConditionTargetPinCursor";
	START_LAPTIMER(2256);
	PinCursor retval = UTL_GetTimingTrainingConditionTargetPinCursor( arg1);
	STOP_LAPTIMER(2256);
	return retval;
}
PinCursor _UTL_GetTimingTrainingConditionCheckPinCursor( TimingTrainingConditionHandle arg1, UT_PIN arg2)
{
	MCI_LIST[2257] = "UTL_GetTimingTrainingConditionCheckPinCursor";
	START_LAPTIMER(2257);
	PinCursor retval = UTL_GetTimingTrainingConditionCheckPinCursor( arg1, arg2);
	STOP_LAPTIMER(2257);
	return retval;
}
int _UTL_GetTimingTrainingConditionEdgeSelect( TimingTrainingConditionHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2258] = "UTL_GetTimingTrainingConditionEdgeSelect";
	START_LAPTIMER(2258);
	int retval = UTL_GetTimingTrainingConditionEdgeSelect( arg1, arg2);
	STOP_LAPTIMER(2258);
	return retval;
}
int _UTL_GetTimingTrainingConditionStartPoint( TimingTrainingConditionHandle arg1, DSlider * arg2)
{
	MCI_LIST[2259] = "UTL_GetTimingTrainingConditionStartPoint";
	START_LAPTIMER(2259);
	int retval = UTL_GetTimingTrainingConditionStartPoint( arg1, arg2);
	STOP_LAPTIMER(2259);
	return retval;
}
int _UTL_GetTimingTrainingConditionStopPoint( TimingTrainingConditionHandle arg1, DSlider * arg2)
{
	MCI_LIST[2260] = "UTL_GetTimingTrainingConditionStopPoint";
	START_LAPTIMER(2260);
	int retval = UTL_GetTimingTrainingConditionStopPoint( arg1, arg2);
	STOP_LAPTIMER(2260);
	return retval;
}
int _UTL_GetTimingTrainingConditionShiftValue( TimingTrainingConditionHandle arg1, DSlider * arg2)
{
	MCI_LIST[2261] = "UTL_GetTimingTrainingConditionShiftValue";
	START_LAPTIMER(2261);
	int retval = UTL_GetTimingTrainingConditionShiftValue( arg1, arg2);
	STOP_LAPTIMER(2261);
	return retval;
}
int _UTL_GetTimingTrainingConditionJudgeLoopCount( TimingTrainingConditionHandle arg1, USlider * arg2)
{
	MCI_LIST[2262] = "UTL_GetTimingTrainingConditionJudgeLoopCount";
	START_LAPTIMER(2262);
	int retval = UTL_GetTimingTrainingConditionJudgeLoopCount( arg1, arg2);
	STOP_LAPTIMER(2262);
	return retval;
}
int _UTL_GetTimingTrainingConditionJudgeLimitLow( TimingTrainingConditionHandle arg1, USlider * arg2)
{
	MCI_LIST[2263] = "UTL_GetTimingTrainingConditionJudgeLimitLow";
	START_LAPTIMER(2263);
	int retval = UTL_GetTimingTrainingConditionJudgeLimitLow( arg1, arg2);
	STOP_LAPTIMER(2263);
	return retval;
}
int _UTL_GetTimingTrainingConditionJudgeLimitHigh( TimingTrainingConditionHandle arg1, USlider * arg2)
{
	MCI_LIST[2264] = "UTL_GetTimingTrainingConditionJudgeLimitHigh";
	START_LAPTIMER(2264);
	int retval = UTL_GetTimingTrainingConditionJudgeLimitHigh( arg1, arg2);
	STOP_LAPTIMER(2264);
	return retval;
}
int _UTL_GetTimingTrainingConditionJudgeWidth( TimingTrainingConditionHandle arg1, DSlider * arg2)
{
	MCI_LIST[2265] = "UTL_GetTimingTrainingConditionJudgeWidth";
	START_LAPTIMER(2265);
	int retval = UTL_GetTimingTrainingConditionJudgeWidth( arg1, arg2);
	STOP_LAPTIMER(2265);
	return retval;
}
int _UTL_GetTimingTrainingConditionCalcMode( TimingTrainingConditionHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2266] = "UTL_GetTimingTrainingConditionCalcMode";
	START_LAPTIMER(2266);
	int retval = UTL_GetTimingTrainingConditionCalcMode( arg1, arg2);
	STOP_LAPTIMER(2266);
	return retval;
}
int _UTL_GetTimingTrainingConditionEdgeRatio( TimingTrainingConditionHandle arg1, DSlider * arg2)
{
	MCI_LIST[2267] = "UTL_GetTimingTrainingConditionEdgeRatio";
	START_LAPTIMER(2267);
	int retval = UTL_GetTimingTrainingConditionEdgeRatio( arg1, arg2);
	STOP_LAPTIMER(2267);
	return retval;
}
int _UTL_GetTimingTrainingConditionEdgeOffset( TimingTrainingConditionHandle arg1, DSlider * arg2)
{
	MCI_LIST[2268] = "UTL_GetTimingTrainingConditionEdgeOffset";
	START_LAPTIMER(2268);
	int retval = UTL_GetTimingTrainingConditionEdgeOffset( arg1, arg2);
	STOP_LAPTIMER(2268);
	return retval;
}
void _UTL_UpdateTimingTrainingCtrl( TimingTrainingCtrlHandle arg1, RadioButton arg2)
{
	MCI_LIST[2269] = "UTL_UpdateTimingTrainingCtrl";
	START_LAPTIMER(2269);
	UTL_UpdateTimingTrainingCtrl( arg1, arg2);
	STOP_LAPTIMER(2269);
}
int _UTL_GetTimingTrainingCtrlExecuteMode( TimingTrainingCtrlHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2270] = "UTL_GetTimingTrainingCtrlExecuteMode";
	START_LAPTIMER(2270);
	int retval = UTL_GetTimingTrainingCtrlExecuteMode( arg1, arg2);
	STOP_LAPTIMER(2270);
	return retval;
}
void _UTL_UpdateJi( JiHandle arg1)
{
	MCI_LIST[2271] = "UTL_UpdateJi";
	START_LAPTIMER(2271);
	UTL_UpdateJi( arg1);
	STOP_LAPTIMER(2271);
}
int _UTL_GetJiWaveform( JiHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2272] = "UTL_GetJiWaveform";
	START_LAPTIMER(2272);
	int retval = UTL_GetJiWaveform( arg1, arg2);
	STOP_LAPTIMER(2272);
	return retval;
}
int _UTL_GetJiFrequency( JiHandle  arg1, DSlider * arg2)
{
	MCI_LIST[2273] = "UTL_GetJiFrequency";
	START_LAPTIMER(2273);
	int retval = UTL_GetJiFrequency( arg1, arg2);
	STOP_LAPTIMER(2273);
	return retval;
}
int _UTL_GetJiAmplitude( JiHandle  arg1, DSlider * arg2)
{
	MCI_LIST[2274] = "UTL_GetJiAmplitude";
	START_LAPTIMER(2274);
	int retval = UTL_GetJiAmplitude( arg1, arg2);
	STOP_LAPTIMER(2274);
	return retval;
}
void _UTL_UpdateJiPin( JiPinHandle arg1, UT_PIN arg2)
{
	MCI_LIST[2275] = "UTL_UpdateJiPin";
	START_LAPTIMER(2275);
	UTL_UpdateJiPin( arg1, arg2);
	STOP_LAPTIMER(2275);
}
int _UTL_GetJiPinTargetClock( JiPinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2276] = "UTL_GetJiPinTargetClock";
	START_LAPTIMER(2276);
	int retval = UTL_GetJiPinTargetClock( arg1, arg2);
	STOP_LAPTIMER(2276);
	return retval;
}
PinCursor _UTL_GetJiPinCursor( JiPinHandle  arg1)
{
	MCI_LIST[2277] = "UTL_GetJiPinCursor";
	START_LAPTIMER(2277);
	PinCursor retval = UTL_GetJiPinCursor( arg1);
	STOP_LAPTIMER(2277);
	return retval;
}
void _UTL_UpdateCtConfig( CtConfigHandle arg1)
{
	MCI_LIST[2278] = "UTL_UpdateCtConfig";
	START_LAPTIMER(2278);
	UTL_UpdateCtConfig( arg1);
	STOP_LAPTIMER(2278);
}
int _UTL_GetCtConfigMethod( CtConfigHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2279] = "UTL_GetCtConfigMethod";
	START_LAPTIMER(2279);
	int retval = UTL_GetCtConfigMethod( arg1, arg2);
	STOP_LAPTIMER(2279);
	return retval;
}
int _UTL_GetCtConfigStartPoint( CtConfigHandle  arg1, DSlider * arg2)
{
	MCI_LIST[2280] = "UTL_GetCtConfigStartPoint";
	START_LAPTIMER(2280);
	int retval = UTL_GetCtConfigStartPoint( arg1, arg2);
	STOP_LAPTIMER(2280);
	return retval;
}
void _UTL_UpdateCtPin( CtPinHandle arg1)
{
	MCI_LIST[2281] = "UTL_UpdateCtPin";
	START_LAPTIMER(2281);
	UTL_UpdateCtPin( arg1);
	STOP_LAPTIMER(2281);
}
int _UTL_GetCtPinListCount( CtPinHandle  arg1, USlider * arg2)
{
	MCI_LIST[2282] = "UTL_GetCtPinListCount";
	START_LAPTIMER(2282);
	int retval = UTL_GetCtPinListCount( arg1, arg2);
	STOP_LAPTIMER(2282);
	return retval;
}
int _UTL_GetCtPinList( CtPinHandle  arg1, int  arg2, char ** arg3, char ** arg4)
{
	MCI_LIST[2283] = "UTL_GetCtPinList";
	START_LAPTIMER(2283);
	int retval = UTL_GetCtPinList( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2283);
	return retval;
}
int _UTL_GetCtPinExecMode( CtPinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2284] = "UTL_GetCtPinExecMode";
	START_LAPTIMER(2284);
	int retval = UTL_GetCtPinExecMode( arg1, arg2);
	STOP_LAPTIMER(2284);
	return retval;
}
void _UTL_UpdateCtLog( CtLogHandle arg1)
{
	MCI_LIST[2285] = "UTL_UpdateCtLog";
	START_LAPTIMER(2285);
	UTL_UpdateCtLog( arg1);
	STOP_LAPTIMER(2285);
}
int _UTL_GetCtLogWaitTime( CtLogHandle  arg1, DSlider * arg2)
{
	MCI_LIST[2286] = "UTL_GetCtLogWaitTime";
	START_LAPTIMER(2286);
	int retval = UTL_GetCtLogWaitTime( arg1, arg2);
	STOP_LAPTIMER(2286);
	return retval;
}
int _UTL_GetCtLogDecimation( CtLogHandle  arg1, USlider * arg2)
{
	MCI_LIST[2287] = "UTL_GetCtLogDecimation";
	START_LAPTIMER(2287);
	int retval = UTL_GetCtLogDecimation( arg1, arg2);
	STOP_LAPTIMER(2287);
	return retval;
}
int _UTL_GetCtLogEnable( CtLogHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2288] = "UTL_GetCtLogEnable";
	START_LAPTIMER(2288);
	int retval = UTL_GetCtLogEnable( arg1, arg2);
	STOP_LAPTIMER(2288);
	return retval;
}
void _UTL_UpdateVload( VloadHandle arg1, RadioButton arg2)
{
	MCI_LIST[2289] = "UTL_UpdateVload";
	START_LAPTIMER(2289);
	UTL_UpdateVload( arg1, arg2);
	STOP_LAPTIMER(2289);
}
int _UTL_GetVload( VloadHandle  arg1, DSlider * arg2)
{
	MCI_LIST[2290] = "UTL_GetVload";
	START_LAPTIMER(2290);
	int retval = UTL_GetVload( arg1, arg2);
	STOP_LAPTIMER(2290);
	return retval;
}
void _UTL_UpdateSamplingRate( SamplingRateHandle arg1)
{
	MCI_LIST[2291] = "UTL_UpdateSamplingRate";
	START_LAPTIMER(2291);
	UTL_UpdateSamplingRate( arg1);
	STOP_LAPTIMER(2291);
}
int _UTL_GetSamplingRate( SamplingRateHandle  arg1, DSlider * arg2)
{
	MCI_LIST[2292] = "UTL_GetSamplingRate";
	START_LAPTIMER(2292);
	int retval = UTL_GetSamplingRate( arg1, arg2);
	STOP_LAPTIMER(2292);
	return retval;
}
void _UTL_UpdateMatchPinGroup( MatchPinGroupHandle arg1)
{
	MCI_LIST[2293] = "UTL_UpdateMatchPinGroup";
	START_LAPTIMER(2293);
	UTL_UpdateMatchPinGroup( arg1);
	STOP_LAPTIMER(2293);
}
int _UTL_GetMatchPinGroupSignal( MatchPinGroupHandle  arg1, RadioButton  arg2, RadioButton * arg3)
{
	MCI_LIST[2294] = "UTL_GetMatchPinGroupSignal";
	START_LAPTIMER(2294);
	int retval = UTL_GetMatchPinGroupSignal( arg1, arg2, arg3);
	STOP_LAPTIMER(2294);
	return retval;
}
void _UTL_UpdateDcComparator( DcComparatorHandle arg1)
{
	MCI_LIST[2295] = "UTL_UpdateDcComparator";
	START_LAPTIMER(2295);
	UTL_UpdateDcComparator( arg1);
	STOP_LAPTIMER(2295);
}
int _UTL_GetDcComparatorLimitHigh( DcComparatorHandle  arg1, DSlider * arg2)
{
	MCI_LIST[2296] = "UTL_GetDcComparatorLimitHigh";
	START_LAPTIMER(2296);
	int retval = UTL_GetDcComparatorLimitHigh( arg1, arg2);
	STOP_LAPTIMER(2296);
	return retval;
}
int _UTL_GetDcComparatorLimitLow( DcComparatorHandle  arg1, DSlider * arg2)
{
	MCI_LIST[2297] = "UTL_GetDcComparatorLimitLow";
	START_LAPTIMER(2297);
	int retval = UTL_GetDcComparatorLimitLow( arg1, arg2);
	STOP_LAPTIMER(2297);
	return retval;
}
int _UTL_GetDcComparatorReadPinDut( DcComparatorReadPinHandle  arg1, UT_DUT * arg2)
{
	MCI_LIST[2298] = "UTL_GetDcComparatorReadPinDut";
	START_LAPTIMER(2298);
	int retval = UTL_GetDcComparatorReadPinDut( arg1, arg2);
	STOP_LAPTIMER(2298);
	return retval;
}
int _UTL_GetDcComparatorReadPinNumber( DcComparatorReadPinHandle  arg1, UT_PIN * arg2)
{
	MCI_LIST[2299] = "UTL_GetDcComparatorReadPinNumber";
	START_LAPTIMER(2299);
	int retval = UTL_GetDcComparatorReadPinNumber( arg1, arg2);
	STOP_LAPTIMER(2299);
	return retval;
}
int _UTL_GetDcComparatorReadPinMode( DcComparatorReadPinHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2300] = "UTL_GetDcComparatorReadPinMode";
	START_LAPTIMER(2300);
	int retval = UTL_GetDcComparatorReadPinMode( arg1, arg2);
	STOP_LAPTIMER(2300);
	return retval;
}
void _UTL_UpdateVihhMut( VihhMutHandle arg1)
{
	MCI_LIST[2301] = "UTL_UpdateVihhMut";
	START_LAPTIMER(2301);
	UTL_UpdateVihhMut( arg1);
	STOP_LAPTIMER(2301);
}
int _UTL_GetVihhMutSignal( VihhMutHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2302] = "UTL_GetVihhMutSignal";
	START_LAPTIMER(2302);
	int retval = UTL_GetVihhMutSignal( arg1, arg2);
	STOP_LAPTIMER(2302);
	return retval;
}
void _UTL_UpdateVihhMutStartCtrl( VihhMutStartCtrlHandle arg1)
{
	MCI_LIST[2303] = "UTL_UpdateVihhMutStartCtrl";
	START_LAPTIMER(2303);
	UTL_UpdateVihhMutStartCtrl( arg1);
	STOP_LAPTIMER(2303);
}
int _UTL_GetVihhMutStartCtrl( VihhMutStartCtrlHandle  arg1, RadioButton * arg2)
{
	MCI_LIST[2304] = "UTL_GetVihhMutStartCtrl";
	START_LAPTIMER(2304);
	int retval = UTL_GetVihhMutStartCtrl( arg1, arg2);
	STOP_LAPTIMER(2304);
	return retval;
}
void _UTL_UpdateSourceSyncCp( SourceSyncCpHandle arg1, UT_PIN arg2)
{
	MCI_LIST[2305] = "UTL_UpdateSourceSyncCp";
	START_LAPTIMER(2305);
	UTL_UpdateSourceSyncCp( arg1, arg2);
	STOP_LAPTIMER(2305);
}
PinCursor _UTL_GetSourceSyncCpTargetPinCursor( SourceSyncCpHandle  arg1)
{
	MCI_LIST[2306] = "UTL_GetSourceSyncCpTargetPinCursor";
	START_LAPTIMER(2306);
	PinCursor retval = UTL_GetSourceSyncCpTargetPinCursor( arg1);
	STOP_LAPTIMER(2306);
	return retval;
}
int _UTL_GetSourceSyncCpMode( SourceSyncCpHandle  arg1, CheckButton * arg2)
{
	MCI_LIST[2307] = "UTL_GetSourceSyncCpMode";
	START_LAPTIMER(2307);
	int retval = UTL_GetSourceSyncCpMode( arg1, arg2);
	STOP_LAPTIMER(2307);
	return retval;
}
UbmConfigHandle _UTL_GetUbmConfigHandle()
{
	MCI_LIST[2308] = "UTL_GetUbmConfigHandle";
	START_LAPTIMER(2308);
	UbmConfigHandle retval = UTL_GetUbmConfigHandle();
	STOP_LAPTIMER(2308);
	return retval;
}
void _UTL_InitializeUbmConfigHandle( UbmConfigHandle arg1)
{
	MCI_LIST[2309] = "UTL_InitializeUbmConfigHandle";
	START_LAPTIMER(2309);
	UTL_InitializeUbmConfigHandle( arg1);
	STOP_LAPTIMER(2309);
}
void _UTL_AddUbmConfigFunctionSelect( UbmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[2310] = "UTL_AddUbmConfigFunctionSelect";
	START_LAPTIMER(2310);
	UTL_AddUbmConfigFunctionSelect( arg1, arg2, arg3);
	STOP_LAPTIMER(2310);
}
void _UTL_ClearUbmConfigFunctionSelect( UbmConfigHandle arg1)
{
	MCI_LIST[2311] = "UTL_ClearUbmConfigFunctionSelect";
	START_LAPTIMER(2311);
	UTL_ClearUbmConfigFunctionSelect( arg1);
	STOP_LAPTIMER(2311);
}
void _UTL_SetUbmConfigPin( UbmConfigHandle arg1, RadioButton arg2, char * arg3)
{
	MCI_LIST[2312] = "UTL_SetUbmConfigPin";
	START_LAPTIMER(2312);
	UTL_SetUbmConfigPin( arg1, arg2, arg3);
	STOP_LAPTIMER(2312);
}
void _UTL_ClearUbmConfigPin( UbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[2313] = "UTL_ClearUbmConfigPin";
	START_LAPTIMER(2313);
	UTL_ClearUbmConfigPin( arg1, arg2);
	STOP_LAPTIMER(2313);
}
void _UTL_SetUbmConfigJumpAddr( UbmConfigHandle arg1, RadioButton arg2, RadioButton arg3, USlider arg4)
{
	MCI_LIST[2314] = "UTL_SetUbmConfigJumpAddr";
	START_LAPTIMER(2314);
	UTL_SetUbmConfigJumpAddr( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2314);
}
void _UTL_SetUbmConfigJumpCycle( UbmConfigHandle arg1, RadioButton arg2, RadioButton arg3, RadioButton arg4)
{
	MCI_LIST[2315] = "UTL_SetUbmConfigJumpCycle";
	START_LAPTIMER(2315);
	UTL_SetUbmConfigJumpCycle( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2315);
}
void _UTL_ClearUbmConfigJumpAddr( UbmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[2316] = "UTL_ClearUbmConfigJumpAddr";
	START_LAPTIMER(2316);
	UTL_ClearUbmConfigJumpAddr( arg1, arg2, arg3);
	STOP_LAPTIMER(2316);
}
void _UTL_SetUbmConfigPmMode( UbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[2317] = "UTL_SetUbmConfigPmMode";
	START_LAPTIMER(2317);
	UTL_SetUbmConfigPmMode( arg1, arg2);
	STOP_LAPTIMER(2317);
}
void _UTL_SetUbmConfigStrbMode( UbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[2318] = "UTL_SetUbmConfigStrbMode";
	START_LAPTIMER(2318);
	UTL_SetUbmConfigStrbMode( arg1, arg2);
	STOP_LAPTIMER(2318);
}
void _UTL_AddUbmConfigStrbChannel( UbmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[2319] = "UTL_AddUbmConfigStrbChannel";
	START_LAPTIMER(2319);
	UTL_AddUbmConfigStrbChannel( arg1, arg2, arg3);
	STOP_LAPTIMER(2319);
}
void _UTL_ClearUbmConfigStrbChannel( UbmConfigHandle arg1)
{
	MCI_LIST[2320] = "UTL_ClearUbmConfigStrbChannel";
	START_LAPTIMER(2320);
	UTL_ClearUbmConfigStrbChannel( arg1);
	STOP_LAPTIMER(2320);
}
void _UTL_SetUbmConfigPatternInvEnable( UbmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[2321] = "UTL_SetUbmConfigPatternInvEnable";
	START_LAPTIMER(2321);
	UTL_SetUbmConfigPatternInvEnable( arg1, arg2);
	STOP_LAPTIMER(2321);
}
void _UTL_SetUbmConfigDdrMode( UbmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[2322] = "UTL_SetUbmConfigDdrMode";
	START_LAPTIMER(2322);
	UTL_SetUbmConfigDdrMode( arg1, arg2);
	STOP_LAPTIMER(2322);
}
void _UTL_SetUbmConfigApAutoIncMode( UbmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[2323] = "UTL_SetUbmConfigApAutoIncMode";
	START_LAPTIMER(2323);
	UTL_SetUbmConfigApAutoIncMode( arg1, arg2);
	STOP_LAPTIMER(2323);
}
void _UTL_SetUbmConfigApIncCycle( UbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[2324] = "UTL_SetUbmConfigApIncCycle";
	START_LAPTIMER(2324);
	UTL_SetUbmConfigApIncCycle( arg1, arg2);
	STOP_LAPTIMER(2324);
}
void _UTL_SetUbmConfigApAllCycleIncMode( UbmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[2325] = "UTL_SetUbmConfigApAllCycleIncMode";
	START_LAPTIMER(2325);
	UTL_SetUbmConfigApAllCycleIncMode( arg1, arg2);
	STOP_LAPTIMER(2325);
}
void _UTL_SetUbmConfigPinLinkMode( UbmConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[2326] = "UTL_SetUbmConfigPinLinkMode";
	START_LAPTIMER(2326);
	UTL_SetUbmConfigPinLinkMode( arg1, arg2, arg3);
	STOP_LAPTIMER(2326);
}
void _UTL_SetUbmConfigCaptureMode( UbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[2327] = "UTL_SetUbmConfigCaptureMode";
	START_LAPTIMER(2327);
	UTL_SetUbmConfigCaptureMode( arg1, arg2);
	STOP_LAPTIMER(2327);
}
void _UTL_SetUbmConfigExpDelayMode( UbmConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[2328] = "UTL_SetUbmConfigExpDelayMode";
	START_LAPTIMER(2328);
	UTL_SetUbmConfigExpDelayMode( arg1, arg2);
	STOP_LAPTIMER(2328);
}
void _UTL_SetUbmConfigOverlayCycle( UbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[2329] = "UTL_SetUbmConfigOverlayCycle";
	START_LAPTIMER(2329);
	UTL_SetUbmConfigOverlayCycle( arg1, arg2);
	STOP_LAPTIMER(2329);
}
void _UTL_SetUbmConfigTransferCycle( UbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[2330] = "UTL_SetUbmConfigTransferCycle";
	START_LAPTIMER(2330);
	UTL_SetUbmConfigTransferCycle( arg1, arg2);
	STOP_LAPTIMER(2330);
}
void _UTL_SetUbmConfigTransferSize( UbmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[2331] = "UTL_SetUbmConfigTransferSize";
	START_LAPTIMER(2331);
	UTL_SetUbmConfigTransferSize( arg1, arg2);
	STOP_LAPTIMER(2331);
}
void _UTL_SendUbmConfig( UbmConfigHandle arg1)
{
	MCI_LIST[2332] = "UTL_SendUbmConfig";
	START_LAPTIMER(2332);
	UTL_SendUbmConfig( arg1);
	STOP_LAPTIMER(2332);
}
void _UTL_UpdateUbmConfig( UbmConfigHandle arg1)
{
	MCI_LIST[2333] = "UTL_UpdateUbmConfig";
	START_LAPTIMER(2333);
	UTL_UpdateUbmConfig( arg1);
	STOP_LAPTIMER(2333);
}
UbmConfigFunctionSelectCursor _UTL_GetUbmConfigFunctionSelectCursor( UbmConfigHandle arg1)
{
	MCI_LIST[2334] = "UTL_GetUbmConfigFunctionSelectCursor";
	START_LAPTIMER(2334);
	UbmConfigFunctionSelectCursor retval = UTL_GetUbmConfigFunctionSelectCursor( arg1);
	STOP_LAPTIMER(2334);
	return retval;
}
RadioButton _UTL_NextUbmConfigFunctionSelect( UbmConfigFunctionSelectCursor arg1)
{
	MCI_LIST[2335] = "UTL_NextUbmConfigFunctionSelect";
	START_LAPTIMER(2335);
	RadioButton retval = UTL_NextUbmConfigFunctionSelect( arg1);
	STOP_LAPTIMER(2335);
	return retval;
}
int _UTL_GetUbmConfigFunctionSelectEnableCycle( UbmConfigHandle arg1, RadioButton arg2, RadioButton * arg3)
{
	MCI_LIST[2336] = "UTL_GetUbmConfigFunctionSelectEnableCycle";
	START_LAPTIMER(2336);
	int retval = UTL_GetUbmConfigFunctionSelectEnableCycle( arg1, arg2, arg3);
	STOP_LAPTIMER(2336);
	return retval;
}
int _UTL_GetUbmConfigPin( UbmConfigHandle arg1, RadioButton arg2, char ** arg3)
{
	MCI_LIST[2337] = "UTL_GetUbmConfigPin";
	START_LAPTIMER(2337);
	int retval = UTL_GetUbmConfigPin( arg1, arg2, arg3);
	STOP_LAPTIMER(2337);
	return retval;
}
UbmConfigJumpIndexNoCursor _UTL_GetUbmConfigJumpIndexNoCursor( UbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[2338] = "UTL_GetUbmConfigJumpIndexNoCursor";
	START_LAPTIMER(2338);
	UbmConfigJumpIndexNoCursor retval = UTL_GetUbmConfigJumpIndexNoCursor( arg1, arg2);
	STOP_LAPTIMER(2338);
	return retval;
}
RadioButton _UTL_NextUbmConfigJumpIndexNo( UbmConfigJumpIndexNoCursor arg1)
{
	MCI_LIST[2339] = "UTL_NextUbmConfigJumpIndexNo";
	START_LAPTIMER(2339);
	RadioButton retval = UTL_NextUbmConfigJumpIndexNo( arg1);
	STOP_LAPTIMER(2339);
	return retval;
}
int _UTL_GetUbmConfigJumpAddr( UbmConfigHandle arg1, RadioButton arg2, RadioButton arg3, USlider * arg4)
{
	MCI_LIST[2340] = "UTL_GetUbmConfigJumpAddr";
	START_LAPTIMER(2340);
	int retval = UTL_GetUbmConfigJumpAddr( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2340);
	return retval;
}
int _UTL_GetUbmConfigJumpCycle( UbmConfigHandle arg1, RadioButton arg2, RadioButton arg3, RadioButton * arg4)
{
	MCI_LIST[2341] = "UTL_GetUbmConfigJumpCycle";
	START_LAPTIMER(2341);
	int retval = UTL_GetUbmConfigJumpCycle( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2341);
	return retval;
}
int _UTL_GetUbmConfigPmMode( UbmConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2342] = "UTL_GetUbmConfigPmMode";
	START_LAPTIMER(2342);
	int retval = UTL_GetUbmConfigPmMode( arg1, arg2);
	STOP_LAPTIMER(2342);
	return retval;
}
int _UTL_GetUbmConfigStrbMode( UbmConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2343] = "UTL_GetUbmConfigStrbMode";
	START_LAPTIMER(2343);
	int retval = UTL_GetUbmConfigStrbMode( arg1, arg2);
	STOP_LAPTIMER(2343);
	return retval;
}
int _UTL_GetUbmConfigPatternInvEnable( UbmConfigHandle arg1, CheckButton * arg2)
{
	MCI_LIST[2344] = "UTL_GetUbmConfigPatternInvEnable";
	START_LAPTIMER(2344);
	int retval = UTL_GetUbmConfigPatternInvEnable( arg1, arg2);
	STOP_LAPTIMER(2344);
	return retval;
}
int _UTL_GetUbmConfigDdrMode( UbmConfigHandle arg1, CheckButton * arg2)
{
	MCI_LIST[2345] = "UTL_GetUbmConfigDdrMode";
	START_LAPTIMER(2345);
	int retval = UTL_GetUbmConfigDdrMode( arg1, arg2);
	STOP_LAPTIMER(2345);
	return retval;
}
UbmConfigAlpgBankCursor _UTL_GetUbmConfigAlpgBankCursor( UbmConfigHandle arg1)
{
	MCI_LIST[2346] = "UTL_GetUbmConfigAlpgBankCursor";
	START_LAPTIMER(2346);
	UbmConfigAlpgBankCursor retval = UTL_GetUbmConfigAlpgBankCursor( arg1);
	STOP_LAPTIMER(2346);
	return retval;
}
RadioButton _UTL_NextUbmConfigAlpgBank( UbmConfigAlpgBankCursor arg1)
{
	MCI_LIST[2347] = "UTL_NextUbmConfigAlpgBank";
	START_LAPTIMER(2347);
	RadioButton retval = UTL_NextUbmConfigAlpgBank( arg1);
	STOP_LAPTIMER(2347);
	return retval;
}
UbmConfigStrbChannelCursor _UTL_GetUbmConfigStrbChannelCursor( UbmConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[2348] = "UTL_GetUbmConfigStrbChannelCursor";
	START_LAPTIMER(2348);
	UbmConfigStrbChannelCursor retval = UTL_GetUbmConfigStrbChannelCursor( arg1, arg2);
	STOP_LAPTIMER(2348);
	return retval;
}
RadioButton _UTL_NextUbmConfigStrbChannel( UbmConfigStrbChannelCursor arg1)
{
	MCI_LIST[2349] = "UTL_NextUbmConfigStrbChannel";
	START_LAPTIMER(2349);
	RadioButton retval = UTL_NextUbmConfigStrbChannel( arg1);
	STOP_LAPTIMER(2349);
	return retval;
}
int _UTL_GetUbmConfigApAutoIncMode( UbmConfigHandle arg1, CheckButton * arg2)
{
	MCI_LIST[2350] = "UTL_GetUbmConfigApAutoIncMode";
	START_LAPTIMER(2350);
	int retval = UTL_GetUbmConfigApAutoIncMode( arg1, arg2);
	STOP_LAPTIMER(2350);
	return retval;
}
int _UTL_GetUbmConfigApIncCycle( UbmConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2351] = "UTL_GetUbmConfigApIncCycle";
	START_LAPTIMER(2351);
	int retval = UTL_GetUbmConfigApIncCycle( arg1, arg2);
	STOP_LAPTIMER(2351);
	return retval;
}
int _UTL_GetUbmConfigApAllCycleIncMode( UbmConfigHandle arg1, CheckButton * arg2)
{
	MCI_LIST[2352] = "UTL_GetUbmConfigApAllCycleIncMode";
	START_LAPTIMER(2352);
	int retval = UTL_GetUbmConfigApAllCycleIncMode( arg1, arg2);
	STOP_LAPTIMER(2352);
	return retval;
}
int _UTL_GetUbmConfigPinLinkMode( UbmConfigHandle arg1, RadioButton * arg2, RadioButton * arg3)
{
	MCI_LIST[2353] = "UTL_GetUbmConfigPinLinkMode";
	START_LAPTIMER(2353);
	int retval = UTL_GetUbmConfigPinLinkMode( arg1, arg2, arg3);
	STOP_LAPTIMER(2353);
	return retval;
}
int _UTL_GetUbmConfigCaptureMode( UbmConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2354] = "UTL_GetUbmConfigCaptureMode";
	START_LAPTIMER(2354);
	int retval = UTL_GetUbmConfigCaptureMode( arg1, arg2);
	STOP_LAPTIMER(2354);
	return retval;
}
int _UTL_GetUbmConfigExpDelayMode( UbmConfigHandle arg1, CheckButton * arg2)
{
	MCI_LIST[2355] = "UTL_GetUbmConfigExpDelayMode";
	START_LAPTIMER(2355);
	int retval = UTL_GetUbmConfigExpDelayMode( arg1, arg2);
	STOP_LAPTIMER(2355);
	return retval;
}
int _UTL_GetUbmConfigOverlayCycle( UbmConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2356] = "UTL_GetUbmConfigOverlayCycle";
	START_LAPTIMER(2356);
	int retval = UTL_GetUbmConfigOverlayCycle( arg1, arg2);
	STOP_LAPTIMER(2356);
	return retval;
}
int _UTL_GetUbmConfigTransferCycle( UbmConfigHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2357] = "UTL_GetUbmConfigTransferCycle";
	START_LAPTIMER(2357);
	int retval = UTL_GetUbmConfigTransferCycle( arg1, arg2);
	STOP_LAPTIMER(2357);
	return retval;
}
int _UTL_GetUbmConfigTransferSize( UbmConfigHandle arg1, USlider * arg2)
{
	MCI_LIST[2358] = "UTL_GetUbmConfigTransferSize";
	START_LAPTIMER(2358);
	int retval = UTL_GetUbmConfigTransferSize( arg1, arg2);
	STOP_LAPTIMER(2358);
	return retval;
}
UbmAccessHandle _UTL_GetUbmAccessHandle()
{
	MCI_LIST[2359] = "UTL_GetUbmAccessHandle";
	START_LAPTIMER(2359);
	UbmAccessHandle retval = UTL_GetUbmAccessHandle();
	STOP_LAPTIMER(2359);
	return retval;
}
void _UTL_SetUbmAccessDut( UbmAccessHandle arg1, UT_DUT arg2)
{
	MCI_LIST[2360] = "UTL_SetUbmAccessDut";
	START_LAPTIMER(2360);
	UTL_SetUbmAccessDut( arg1, arg2);
	STOP_LAPTIMER(2360);
}
void _UTL_SetUbmAccessPin( UbmAccessHandle arg1, char * arg2)
{
	MCI_LIST[2361] = "UTL_SetUbmAccessPin";
	START_LAPTIMER(2361);
	UTL_SetUbmAccessPin( arg1, arg2);
	STOP_LAPTIMER(2361);
}
void _UTL_ClearUbmAccessPin( UbmAccessHandle arg1)
{
	MCI_LIST[2362] = "UTL_ClearUbmAccessPin";
	START_LAPTIMER(2362);
	UTL_ClearUbmAccessPin( arg1);
	STOP_LAPTIMER(2362);
}
void _UTL_SetUbmAccessStartAddr( UbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[2363] = "UTL_SetUbmAccessStartAddr";
	START_LAPTIMER(2363);
	UTL_SetUbmAccessStartAddr( arg1, arg2);
	STOP_LAPTIMER(2363);
}
void _UTL_SetUbmAccessStopAddr( UbmAccessHandle arg1, USlider arg2)
{
	MCI_LIST[2364] = "UTL_SetUbmAccessStopAddr";
	START_LAPTIMER(2364);
	UTL_SetUbmAccessStopAddr( arg1, arg2);
	STOP_LAPTIMER(2364);
}
void _UTL_SetUbmAccessStrbChannel( UbmAccessHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[2365] = "UTL_SetUbmAccessStrbChannel";
	START_LAPTIMER(2365);
	UTL_SetUbmAccessStrbChannel( arg1, arg2, arg3);
	STOP_LAPTIMER(2365);
}
void _UTL_SetUbmAccessDdrMode( UbmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[2366] = "UTL_SetUbmAccessDdrMode";
	START_LAPTIMER(2366);
	UTL_SetUbmAccessDdrMode( arg1, arg2);
	STOP_LAPTIMER(2366);
}
void _UTL_SetUbmAccessPinBlock( UbmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[2367] = "UTL_SetUbmAccessPinBlock";
	START_LAPTIMER(2367);
	UTL_SetUbmAccessPinBlock( arg1, arg2);
	STOP_LAPTIMER(2367);
}
void _UTL_SetUbmAccessBitReverse( UbmAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[2368] = "UTL_SetUbmAccessBitReverse";
	START_LAPTIMER(2368);
	UTL_SetUbmAccessBitReverse( arg1, arg2);
	STOP_LAPTIMER(2368);
}
void _UTL_SetUbmAccessWriteMode( UbmAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[2369] = "UTL_SetUbmAccessWriteMode";
	START_LAPTIMER(2369);
	UTL_SetUbmAccessWriteMode( arg1, arg2);
	STOP_LAPTIMER(2369);
}
int _UTL_GetUbmAccessDut( UbmAccessHandle arg1, UT_DUT * arg2)
{
	MCI_LIST[2370] = "UTL_GetUbmAccessDut";
	START_LAPTIMER(2370);
	int retval = UTL_GetUbmAccessDut( arg1, arg2);
	STOP_LAPTIMER(2370);
	return retval;
}
int _UTL_GetUbmAccessPin( UbmAccessHandle arg1, char ** arg2)
{
	MCI_LIST[2371] = "UTL_GetUbmAccessPin";
	START_LAPTIMER(2371);
	int retval = UTL_GetUbmAccessPin( arg1, arg2);
	STOP_LAPTIMER(2371);
	return retval;
}
int _UTL_GetUbmAccessStartAddr( UbmAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[2372] = "UTL_GetUbmAccessStartAddr";
	START_LAPTIMER(2372);
	int retval = UTL_GetUbmAccessStartAddr( arg1, arg2);
	STOP_LAPTIMER(2372);
	return retval;
}
int _UTL_GetUbmAccessStopAddr( UbmAccessHandle arg1, USlider * arg2)
{
	MCI_LIST[2373] = "UTL_GetUbmAccessStopAddr";
	START_LAPTIMER(2373);
	int retval = UTL_GetUbmAccessStopAddr( arg1, arg2);
	STOP_LAPTIMER(2373);
	return retval;
}
int _UTL_GetUbmAccessAlpgBank( UbmAccessHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2374] = "UTL_GetUbmAccessAlpgBank";
	START_LAPTIMER(2374);
	int retval = UTL_GetUbmAccessAlpgBank( arg1, arg2);
	STOP_LAPTIMER(2374);
	return retval;
}
int _UTL_GetUbmAccessStrbChannel( UbmAccessHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2375] = "UTL_GetUbmAccessStrbChannel";
	START_LAPTIMER(2375);
	int retval = UTL_GetUbmAccessStrbChannel( arg1, arg2);
	STOP_LAPTIMER(2375);
	return retval;
}
int _UTL_GetUbmAccessDdrMode( UbmAccessHandle arg1, CheckButton * arg2)
{
	MCI_LIST[2376] = "UTL_GetUbmAccessDdrMode";
	START_LAPTIMER(2376);
	int retval = UTL_GetUbmAccessDdrMode( arg1, arg2);
	STOP_LAPTIMER(2376);
	return retval;
}
int _UTL_GetUbmAccessPinBlock( UbmAccessHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2377] = "UTL_GetUbmAccessPinBlock";
	START_LAPTIMER(2377);
	int retval = UTL_GetUbmAccessPinBlock( arg1, arg2);
	STOP_LAPTIMER(2377);
	return retval;
}
int _UTL_GetUbmAccessBitReverse( UbmAccessHandle arg1, CheckButton * arg2)
{
	MCI_LIST[2378] = "UTL_GetUbmAccessBitReverse";
	START_LAPTIMER(2378);
	int retval = UTL_GetUbmAccessBitReverse( arg1, arg2);
	STOP_LAPTIMER(2378);
	return retval;
}
int _UTL_GetUbmAccessWriteMode( UbmAccessHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2379] = "UTL_GetUbmAccessWriteMode";
	START_LAPTIMER(2379);
	int retval = UTL_GetUbmAccessWriteMode( arg1, arg2);
	STOP_LAPTIMER(2379);
	return retval;
}
void _UTL_ReadUbm( UbmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[2380] = "UTL_ReadUbm";
	START_LAPTIMER(2380);
	UTL_ReadUbm( arg1, arg2, arg3);
	STOP_LAPTIMER(2380);
}
void _UTL_ReadUbmAllDut( UbmAccessHandle arg1, UT_DUT arg2, void * arg3, USlider arg4)
{
	MCI_LIST[2381] = "UTL_ReadUbmAllDut";
	START_LAPTIMER(2381);
	UTL_ReadUbmAllDut( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2381);
}
void _UTL_WriteUbm( UbmAccessHandle arg1, void * arg2, USlider arg3)
{
	MCI_LIST[2382] = "UTL_WriteUbm";
	START_LAPTIMER(2382);
	UTL_WriteUbm( arg1, arg2, arg3);
	STOP_LAPTIMER(2382);
}
void _UTL_WriteUbmAllDut( UbmAccessHandle arg1, UT_DUT arg2, void * arg3, USlider arg4)
{
	MCI_LIST[2383] = "UTL_WriteUbmAllDut";
	START_LAPTIMER(2383);
	UTL_WriteUbmAllDut( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2383);
}
void _UTL_WriteUbmRawData_Lite( RadioButton arg1, RadioButton arg2, RadioButton arg3, USlider arg4, USlider arg5, void * arg6)
{
	MCI_LIST[2384] = "UTL_WriteUbmRawData_Lite";
	START_LAPTIMER(2384);
	UTL_WriteUbmRawData_Lite( arg1, arg2, arg3, arg4, arg5, arg6);
	STOP_LAPTIMER(2384);
}
void _UTL_PresetUbm( UbmConfigHandle arg1, USlider arg2)
{
	MCI_LIST[2385] = "UTL_PresetUbm";
	START_LAPTIMER(2385);
	UTL_PresetUbm( arg1, arg2);
	STOP_LAPTIMER(2385);
}
int _UTL_WriteAlpgCtrlReg( RadioButton arg1, USlider arg2)
{
	MCI_LIST[2386] = "UTL_WriteAlpgCtrlReg";
	START_LAPTIMER(2386);
	int retval = UTL_WriteAlpgCtrlReg( arg1, arg2);
	STOP_LAPTIMER(2386);
	return retval;
}
int _UTL_ReadAlpgCtrlReg( RadioButton arg1, USlider * arg2)
{
	MCI_LIST[2387] = "UTL_ReadAlpgCtrlReg";
	START_LAPTIMER(2387);
	int retval = UTL_ReadAlpgCtrlReg( arg1, arg2);
	STOP_LAPTIMER(2387);
	return retval;
}
RteMaskHandle _UTL_GetRteMaskHandle()
{
	MCI_LIST[2388] = "UTL_GetRteMaskHandle";
	START_LAPTIMER(2388);
	RteMaskHandle retval = UTL_GetRteMaskHandle();
	STOP_LAPTIMER(2388);
	return retval;
}
void _UTL_InitializeRteMaskHandle( RteMaskHandle arg1)
{
	MCI_LIST[2389] = "UTL_InitializeRteMaskHandle";
	START_LAPTIMER(2389);
	UTL_InitializeRteMaskHandle( arg1);
	STOP_LAPTIMER(2389);
}
void _UTL_SetRteMaskDcGuardAlarm( RteMaskHandle arg1, CheckButton arg2)
{
	MCI_LIST[2390] = "UTL_SetRteMaskDcGuardAlarm";
	START_LAPTIMER(2390);
	UTL_SetRteMaskDcGuardAlarm( arg1, arg2);
	STOP_LAPTIMER(2390);
}
void _UTL_SetRteMaskPpsGuardAlarm( RteMaskHandle arg1, CheckButton arg2)
{
	MCI_LIST[2391] = "UTL_SetRteMaskPpsGuardAlarm";
	START_LAPTIMER(2391);
	UTL_SetRteMaskPpsGuardAlarm( arg1, arg2);
	STOP_LAPTIMER(2391);
}
void _UTL_SetRteMaskPpsKelvinAlarm( RteMaskHandle arg1, CheckButton arg2)
{
	MCI_LIST[2392] = "UTL_SetRteMaskPpsKelvinAlarm";
	START_LAPTIMER(2392);
	UTL_SetRteMaskPpsKelvinAlarm( arg1, arg2);
	STOP_LAPTIMER(2392);
}
void _UTL_SetRteMaskLimiterFail( RteMaskHandle arg1, CheckButton arg2)
{
	MCI_LIST[2393] = "UTL_SetRteMaskLimiterFail";
	START_LAPTIMER(2393);
	UTL_SetRteMaskLimiterFail( arg1, arg2);
	STOP_LAPTIMER(2393);
}
void _UTL_SendRteMask( RteMaskHandle arg1)
{
	MCI_LIST[2394] = "UTL_SendRteMask";
	START_LAPTIMER(2394);
	UTL_SendRteMask( arg1);
	STOP_LAPTIMER(2394);
}
SdcHandle _UTL_GetSdcHandle()
{
	MCI_LIST[2395] = "UTL_GetSdcHandle";
	START_LAPTIMER(2395);
	SdcHandle retval = UTL_GetSdcHandle();
	STOP_LAPTIMER(2395);
	return retval;
}
void _UTL_SetSdcSourceHigh( SdcHandle arg1, DSlider arg2)
{
	MCI_LIST[2396] = "UTL_SetSdcSourceHigh";
	START_LAPTIMER(2396);
	UTL_SetSdcSourceHigh( arg1, arg2);
	STOP_LAPTIMER(2396);
}
void _UTL_SetSdcSourceLow( SdcHandle arg1, DSlider arg2)
{
	MCI_LIST[2397] = "UTL_SetSdcSourceLow";
	START_LAPTIMER(2397);
	UTL_SetSdcSourceLow( arg1, arg2);
	STOP_LAPTIMER(2397);
}
void _UTL_SetSdcComparisonHigh( SdcHandle arg1, DSlider arg2)
{
	MCI_LIST[2398] = "UTL_SetSdcComparisonHigh";
	START_LAPTIMER(2398);
	UTL_SetSdcComparisonHigh( arg1, arg2);
	STOP_LAPTIMER(2398);
}
void _UTL_SetSdcComparisonLow( SdcHandle arg1, DSlider arg2)
{
	MCI_LIST[2399] = "UTL_SetSdcComparisonLow";
	START_LAPTIMER(2399);
	UTL_SetSdcComparisonLow( arg1, arg2);
	STOP_LAPTIMER(2399);
}
void _UTL_SendSdc( SdcHandle arg1)
{
	MCI_LIST[2400] = "UTL_SendSdc";
	START_LAPTIMER(2400);
	UTL_SendSdc( arg1);
	STOP_LAPTIMER(2400);
}
SdcDctHandle _UTL_GetSdcDctHandle()
{
	MCI_LIST[2401] = "UTL_GetSdcDctHandle";
	START_LAPTIMER(2401);
	SdcDctHandle retval = UTL_GetSdcDctHandle();
	STOP_LAPTIMER(2401);
	return retval;
}
void _UTL_SetSdcDctPinList( SdcDctHandle arg1, char * arg2)
{
	MCI_LIST[2402] = "UTL_SetSdcDctPinList";
	START_LAPTIMER(2402);
	UTL_SetSdcDctPinList( arg1, arg2);
	STOP_LAPTIMER(2402);
}
void _UTL_SetSdcDctMeasPin( SdcDctHandle arg1, RadioButton arg2)
{
	MCI_LIST[2403] = "UTL_SetSdcDctMeasPin";
	START_LAPTIMER(2403);
	UTL_SetSdcDctMeasPin( arg1, arg2);
	STOP_LAPTIMER(2403);
}
void _UTL_SetSdcDctSourceSelect( SdcDctHandle arg1, RadioButton arg2)
{
	MCI_LIST[2404] = "UTL_SetSdcDctSourceSelect";
	START_LAPTIMER(2404);
	UTL_SetSdcDctSourceSelect( arg1, arg2);
	STOP_LAPTIMER(2404);
}
void _UTL_MeasSdcDct( SdcDctHandle arg1)
{
	MCI_LIST[2405] = "UTL_MeasSdcDct";
	START_LAPTIMER(2405);
	UTL_MeasSdcDct( arg1);
	STOP_LAPTIMER(2405);
}
SdcDctPinHandle _UTL_GetSdcDctPinHandle()
{
	MCI_LIST[2406] = "UTL_GetSdcDctPinHandle";
	START_LAPTIMER(2406);
	SdcDctPinHandle retval = UTL_GetSdcDctPinHandle();
	STOP_LAPTIMER(2406);
	return retval;
}
void _UTL_SetSdcDctPinDut( SdcDctPinHandle arg1, UT_DUT arg2)
{
	MCI_LIST[2407] = "UTL_SetSdcDctPinDut";
	START_LAPTIMER(2407);
	UTL_SetSdcDctPinDut( arg1, arg2);
	STOP_LAPTIMER(2407);
}
void _UTL_SetSdcDctPinNumber( SdcDctPinHandle arg1, UT_PIN arg2)
{
	MCI_LIST[2408] = "UTL_SetSdcDctPinNumber";
	START_LAPTIMER(2408);
	UTL_SetSdcDctPinNumber( arg1, arg2);
	STOP_LAPTIMER(2408);
}
void _UTL_SetSdcDctPinMode( SdcDctPinHandle arg1, RadioButton arg2)
{
	MCI_LIST[2409] = "UTL_SetSdcDctPinMode";
	START_LAPTIMER(2409);
	UTL_SetSdcDctPinMode( arg1, arg2);
	STOP_LAPTIMER(2409);
}
CheckButton _UTL_ReadSdcDctPin( SdcDctPinHandle arg1)
{
	MCI_LIST[2410] = "UTL_ReadSdcDctPin";
	START_LAPTIMER(2410);
	CheckButton retval = UTL_ReadSdcDctPin( arg1);
	STOP_LAPTIMER(2410);
	return retval;
}
DqsLookupTableHandle _UTL_GetDqsLookupTableHandle()
{
	MCI_LIST[2411] = "UTL_GetDqsLookupTableHandle";
	START_LAPTIMER(2411);
	DqsLookupTableHandle retval = UTL_GetDqsLookupTableHandle();
	STOP_LAPTIMER(2411);
	return retval;
}
void _UTL_SetDqsLookupTableMode( DqsLookupTableHandle arg1, RadioButton arg2)
{
	MCI_LIST[2412] = "UTL_SetDqsLookupTableMode";
	START_LAPTIMER(2412);
	UTL_SetDqsLookupTableMode( arg1, arg2);
	STOP_LAPTIMER(2412);
}
void _UTL_SetDqsLookupTableDqsPin( DqsLookupTableHandle arg1, char * arg2)
{
	MCI_LIST[2413] = "UTL_SetDqsLookupTableDqsPin";
	START_LAPTIMER(2413);
	UTL_SetDqsLookupTableDqsPin( arg1, arg2);
	STOP_LAPTIMER(2413);
}
void _UTL_SetDqsLookupTableDqPin( DqsLookupTableHandle arg1, char * arg2)
{
	MCI_LIST[2414] = "UTL_SetDqsLookupTableDqPin";
	START_LAPTIMER(2414);
	UTL_SetDqsLookupTableDqPin( arg1, arg2);
	STOP_LAPTIMER(2414);
}
void _UTL_AddDqsLookupTableCapture( DqsLookupTableHandle arg1, RadioButton arg2)
{
	MCI_LIST[2415] = "UTL_AddDqsLookupTableCapture";
	START_LAPTIMER(2415);
	UTL_AddDqsLookupTableCapture( arg1, arg2);
	STOP_LAPTIMER(2415);
}
void _UTL_ClearDqsLookupTableCapture( DqsLookupTableHandle arg1)
{
	MCI_LIST[2416] = "UTL_ClearDqsLookupTableCapture";
	START_LAPTIMER(2416);
	UTL_ClearDqsLookupTableCapture( arg1);
	STOP_LAPTIMER(2416);
}
void _UTL_InitDqsLookupTableDqsCombination( DqsLookupTableHandle arg1, RadioButton arg2)
{
	MCI_LIST[2417] = "UTL_InitDqsLookupTableDqsCombination";
	START_LAPTIMER(2417);
	UTL_InitDqsLookupTableDqsCombination( arg1, arg2);
	STOP_LAPTIMER(2417);
}
void _UTL_SetDqsLookupTableDqsCombination( DqsLookupTableHandle arg1, RadioButton arg2, RadioButton arg3, RadioButton arg4)
{
	MCI_LIST[2418] = "UTL_SetDqsLookupTableDqsCombination";
	START_LAPTIMER(2418);
	UTL_SetDqsLookupTableDqsCombination( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2418);
}
void _UTL_InitDqsLookupTableDqCombination( DqsLookupTableHandle arg1, RadioButton arg2)
{
	MCI_LIST[2419] = "UTL_InitDqsLookupTableDqCombination";
	START_LAPTIMER(2419);
	UTL_InitDqsLookupTableDqCombination( arg1, arg2);
	STOP_LAPTIMER(2419);
}
void _UTL_SetDqsLookupTableDqCombination( DqsLookupTableHandle arg1, RadioButton arg2, RadioButton arg3, RadioButton arg4)
{
	MCI_LIST[2420] = "UTL_SetDqsLookupTableDqCombination";
	START_LAPTIMER(2420);
	UTL_SetDqsLookupTableDqCombination( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2420);
}
void _UTL_InitDqsLookupTableCycleCombination( DqsLookupTableHandle arg1, RadioButton arg2)
{
	MCI_LIST[2421] = "UTL_InitDqsLookupTableCycleCombination";
	START_LAPTIMER(2421);
	UTL_InitDqsLookupTableCycleCombination( arg1, arg2);
	STOP_LAPTIMER(2421);
}
void _UTL_SetDqsLookupTableCycleCombination( DqsLookupTableHandle arg1, RadioButton arg2, RadioButton arg3, RadioButton arg4, RadioButton arg5, RadioButton arg6, RadioButton arg7)
{
	MCI_LIST[2422] = "UTL_SetDqsLookupTableCycleCombination";
	START_LAPTIMER(2422);
	UTL_SetDqsLookupTableCycleCombination( arg1, arg2, arg3, arg4, arg5, arg6, arg7);
	STOP_LAPTIMER(2422);
}
void _UTL_SendDqsLookupTable( DqsLookupTableHandle arg1)
{
	MCI_LIST[2423] = "UTL_SendDqsLookupTable";
	START_LAPTIMER(2423);
	UTL_SendDqsLookupTable( arg1);
	STOP_LAPTIMER(2423);
}
DqsSourceSyncHandle _UTL_GetDqsSourceSyncHandle()
{
	MCI_LIST[2424] = "UTL_GetDqsSourceSyncHandle";
	START_LAPTIMER(2424);
	DqsSourceSyncHandle retval = UTL_GetDqsSourceSyncHandle();
	STOP_LAPTIMER(2424);
	return retval;
}
void _UTL_SetDqsSourceSyncMode( DqsSourceSyncHandle arg1, RadioButton arg2)
{
	MCI_LIST[2425] = "UTL_SetDqsSourceSyncMode";
	START_LAPTIMER(2425);
	UTL_SetDqsSourceSyncMode( arg1, arg2);
	STOP_LAPTIMER(2425);
}
void _UTL_SetDqsSourceSyncDqsPin( DqsSourceSyncHandle arg1, char * arg2)
{
	MCI_LIST[2426] = "UTL_SetDqsSourceSyncDqsPin";
	START_LAPTIMER(2426);
	UTL_SetDqsSourceSyncDqsPin( arg1, arg2);
	STOP_LAPTIMER(2426);
}
void _UTL_SetDqsSourceSyncDqsPinNega( DqsSourceSyncHandle arg1, char * arg2)
{
	MCI_LIST[2427] = "UTL_SetDqsSourceSyncDqsPinNega";
	START_LAPTIMER(2427);
	UTL_SetDqsSourceSyncDqsPinNega( arg1, arg2);
	STOP_LAPTIMER(2427);
}
void _UTL_SetDqsSourceSyncDqPin( DqsSourceSyncHandle arg1, char * arg2)
{
	MCI_LIST[2428] = "UTL_SetDqsSourceSyncDqPin";
	START_LAPTIMER(2428);
	UTL_SetDqsSourceSyncDqPin( arg1, arg2);
	STOP_LAPTIMER(2428);
}
void _UTL_SetDqsSourceSyncDqPinCount( DqsSourceSyncHandle arg1, USlider arg2)
{
	MCI_LIST[2429] = "UTL_SetDqsSourceSyncDqPinCount";
	START_LAPTIMER(2429);
	UTL_SetDqsSourceSyncDqPinCount( arg1, arg2);
	STOP_LAPTIMER(2429);
}
void _UTL_SetDqsSourceSyncReadCycle( DqsSourceSyncHandle arg1, RadioButton arg2)
{
	MCI_LIST[2430] = "UTL_SetDqsSourceSyncReadCycle";
	START_LAPTIMER(2430);
	UTL_SetDqsSourceSyncReadCycle( arg1, arg2);
	STOP_LAPTIMER(2430);
}
void _UTL_SetDqsSourceSyncEnableCycle( DqsSourceSyncHandle arg1, RadioButton arg2)
{
	MCI_LIST[2431] = "UTL_SetDqsSourceSyncEnableCycle";
	START_LAPTIMER(2431);
	UTL_SetDqsSourceSyncEnableCycle( arg1, arg2);
	STOP_LAPTIMER(2431);
}
void _UTL_SetDqsSourceSyncEnableCycleNega( DqsSourceSyncHandle arg1, RadioButton arg2)
{
	MCI_LIST[2432] = "UTL_SetDqsSourceSyncEnableCycleNega";
	START_LAPTIMER(2432);
	UTL_SetDqsSourceSyncEnableCycleNega( arg1, arg2);
	STOP_LAPTIMER(2432);
}
void _UTL_SetDqsSourceSyncDqsPhaseAdjust( DqsSourceSyncHandle arg1, DSlider arg2)
{
	MCI_LIST[2433] = "UTL_SetDqsSourceSyncDqsPhaseAdjust";
	START_LAPTIMER(2433);
	UTL_SetDqsSourceSyncDqsPhaseAdjust( arg1, arg2);
	STOP_LAPTIMER(2433);
}
void _UTL_SetDqsSourceSyncDqsPhaseAdjustPerPin( DqsSourceSyncHandle arg1, USlider arg2, DSlider * arg3)
{
	MCI_LIST[2434] = "UTL_SetDqsSourceSyncDqsPhaseAdjustPerPin";
	START_LAPTIMER(2434);
	UTL_SetDqsSourceSyncDqsPhaseAdjustPerPin( arg1, arg2, arg3);
	STOP_LAPTIMER(2434);
}
void _UTL_SetDqsSourceSyncFirstEdge( DqsSourceSyncHandle arg1, CheckButton arg2, CheckButton arg3)
{
	MCI_LIST[2435] = "UTL_SetDqsSourceSyncFirstEdge";
	START_LAPTIMER(2435);
	UTL_SetDqsSourceSyncFirstEdge( arg1, arg2, arg3);
	STOP_LAPTIMER(2435);
}
void _UTL_SetDqsSourceSyncFirstEdgeNega( DqsSourceSyncHandle arg1, CheckButton arg2, CheckButton arg3)
{
	MCI_LIST[2436] = "UTL_SetDqsSourceSyncFirstEdgeNega";
	START_LAPTIMER(2436);
	UTL_SetDqsSourceSyncFirstEdgeNega( arg1, arg2, arg3);
	STOP_LAPTIMER(2436);
}
void _UTL_SetDqsSourceSyncFailStopCtrl( DqsSourceSyncHandle arg1, RadioButton arg2, CheckButton arg3)
{
	MCI_LIST[2437] = "UTL_SetDqsSourceSyncFailStopCtrl";
	START_LAPTIMER(2437);
	UTL_SetDqsSourceSyncFailStopCtrl( arg1, arg2, arg3);
	STOP_LAPTIMER(2437);
}
void _UTL_SetDqsSourceSyncCounterCtrl( DqsSourceSyncHandle arg1, CheckButton arg2)
{
	MCI_LIST[2438] = "UTL_SetDqsSourceSyncCounterCtrl";
	START_LAPTIMER(2438);
	UTL_SetDqsSourceSyncCounterCtrl( arg1, arg2);
	STOP_LAPTIMER(2438);
}
void _UTL_SetDqsSourceSyncReadEnable( DqsSourceSyncHandle arg1, CheckButton arg2)
{
	MCI_LIST[2439] = "UTL_SetDqsSourceSyncReadEnable";
	START_LAPTIMER(2439);
	UTL_SetDqsSourceSyncReadEnable( arg1, arg2);
	STOP_LAPTIMER(2439);
}
void _UTL_SendDqsSourceSync( DqsSourceSyncHandle arg1)
{
	MCI_LIST[2440] = "UTL_SendDqsSourceSync";
	START_LAPTIMER(2440);
	UTL_SendDqsSourceSync( arg1);
	STOP_LAPTIMER(2440);
}
void _UTL_WriteDqsSourceSyncPhaseAdjust( USlider arg1, UT_PIN * arg2, DSlider * arg3)
{
	MCI_LIST[2441] = "UTL_WriteDqsSourceSyncPhaseAdjust";
	START_LAPTIMER(2441);
	UTL_WriteDqsSourceSyncPhaseAdjust( arg1, arg2, arg3);
	STOP_LAPTIMER(2441);
}
void _UTL_WriteDqsSourceSyncPhaseAdjustByDut( USlider arg1, UT_PIN * arg2, DSlider * arg3, UT_DUT arg4)
{
	MCI_LIST[2442] = "UTL_WriteDqsSourceSyncPhaseAdjustByDut";
	START_LAPTIMER(2442);
	UTL_WriteDqsSourceSyncPhaseAdjustByDut( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2442);
}
DqsStatusHandle _UTL_GetDqsStatusHandle()
{
	MCI_LIST[2443] = "UTL_GetDqsStatusHandle";
	START_LAPTIMER(2443);
	DqsStatusHandle retval = UTL_GetDqsStatusHandle();
	STOP_LAPTIMER(2443);
	return retval;
}
void _UTL_SetDqsStatusDut( DqsStatusHandle arg1, UT_DUT arg2)
{
	MCI_LIST[2444] = "UTL_SetDqsStatusDut";
	START_LAPTIMER(2444);
	UTL_SetDqsStatusDut( arg1, arg2);
	STOP_LAPTIMER(2444);
}
void _UTL_SetDqsStatusPin( DqsStatusHandle arg1, char * arg2)
{
	MCI_LIST[2445] = "UTL_SetDqsStatusPin";
	START_LAPTIMER(2445);
	UTL_SetDqsStatusPin( arg1, arg2);
	STOP_LAPTIMER(2445);
}
void _UTL_ReadDqsStatus( DqsStatusHandle arg1, USlider * arg2)
{
	MCI_LIST[2446] = "UTL_ReadDqsStatus";
	START_LAPTIMER(2446);
	UTL_ReadDqsStatus( arg1, arg2);
	STOP_LAPTIMER(2446);
}
void _UTL_ReadDqsCounter( DqsStatusHandle arg1, USlider * arg2, USlider * arg3)
{
	MCI_LIST[2447] = "UTL_ReadDqsCounter";
	START_LAPTIMER(2447);
	UTL_ReadDqsCounter( arg1, arg2, arg3);
	STOP_LAPTIMER(2447);
}
void _UTL_ResetDqs( RadioButton arg1)
{
	MCI_LIST[2448] = "UTL_ResetDqs";
	START_LAPTIMER(2448);
	UTL_ResetDqs( arg1);
	STOP_LAPTIMER(2448);
}
PassFailCounterConfigHandle _UTL_GetPassFailCounterConfigHandle()
{
	MCI_LIST[2449] = "UTL_GetPassFailCounterConfigHandle";
	START_LAPTIMER(2449);
	PassFailCounterConfigHandle retval = UTL_GetPassFailCounterConfigHandle();
	STOP_LAPTIMER(2449);
	return retval;
}
void _UTL_SetPassFailCounterConfigMode( PassFailCounterConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[2450] = "UTL_SetPassFailCounterConfigMode";
	START_LAPTIMER(2450);
	UTL_SetPassFailCounterConfigMode( arg1, arg2);
	STOP_LAPTIMER(2450);
}
void _UTL_SetPassFailCounterConfigPin( PassFailCounterConfigHandle arg1, char * arg2)
{
	MCI_LIST[2451] = "UTL_SetPassFailCounterConfigPin";
	START_LAPTIMER(2451);
	UTL_SetPassFailCounterConfigPin( arg1, arg2);
	STOP_LAPTIMER(2451);
}
void _UTL_SetPassFailCounterConfigStrbMode( PassFailCounterConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[2452] = "UTL_SetPassFailCounterConfigStrbMode";
	START_LAPTIMER(2452);
	UTL_SetPassFailCounterConfigStrbMode( arg1, arg2);
	STOP_LAPTIMER(2452);
}
void _UTL_AddPassFailCounterConfigStrbChannel( PassFailCounterConfigHandle arg1, RadioButton arg2, RadioButton arg3)
{
	MCI_LIST[2453] = "UTL_AddPassFailCounterConfigStrbChannel";
	START_LAPTIMER(2453);
	UTL_AddPassFailCounterConfigStrbChannel( arg1, arg2, arg3);
	STOP_LAPTIMER(2453);
}
void _UTL_ClearPassFailCounterConfigStrbChannel( PassFailCounterConfigHandle arg1)
{
	MCI_LIST[2454] = "UTL_ClearPassFailCounterConfigStrbChannel";
	START_LAPTIMER(2454);
	UTL_ClearPassFailCounterConfigStrbChannel( arg1);
	STOP_LAPTIMER(2454);
}
void _UTL_SetPassFailCounterConfigCountUpTableSelect( PassFailCounterConfigHandle arg1, CheckButton arg2)
{
	MCI_LIST[2455] = "UTL_SetPassFailCounterConfigCountUpTableSelect";
	START_LAPTIMER(2455);
	UTL_SetPassFailCounterConfigCountUpTableSelect( arg1, arg2);
	STOP_LAPTIMER(2455);
}
void _UTL_SetPassFailCounterConfigLimit( PassFailCounterConfigHandle arg1, RadioButton arg2, RadioButton arg3, USlider arg4)
{
	MCI_LIST[2456] = "UTL_SetPassFailCounterConfigLimit";
	START_LAPTIMER(2456);
	UTL_SetPassFailCounterConfigLimit( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2456);
}
void _UTL_SendPassFailCounterConfig( PassFailCounterConfigHandle arg1)
{
	MCI_LIST[2457] = "UTL_SendPassFailCounterConfig";
	START_LAPTIMER(2457);
	UTL_SendPassFailCounterConfig( arg1);
	STOP_LAPTIMER(2457);
}
PassFailCounterAccessHandle _UTL_GetPassFailCounterAccessHandle()
{
	MCI_LIST[2458] = "UTL_GetPassFailCounterAccessHandle";
	START_LAPTIMER(2458);
	PassFailCounterAccessHandle retval = UTL_GetPassFailCounterAccessHandle();
	STOP_LAPTIMER(2458);
	return retval;
}
void _UTL_SetPassFailCounterAccessAllCounter( PassFailCounterAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[2459] = "UTL_SetPassFailCounterAccessAllCounter";
	START_LAPTIMER(2459);
	UTL_SetPassFailCounterAccessAllCounter( arg1, arg2);
	STOP_LAPTIMER(2459);
}
void _UTL_SetPassFailCounterAccessCounter( PassFailCounterAccessHandle arg1, RadioButton arg2)
{
	MCI_LIST[2460] = "UTL_SetPassFailCounterAccessCounter";
	START_LAPTIMER(2460);
	UTL_SetPassFailCounterAccessCounter( arg1, arg2);
	STOP_LAPTIMER(2460);
}
void _UTL_SetPassFailCounterAccessAllDut( PassFailCounterAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[2461] = "UTL_SetPassFailCounterAccessAllDut";
	START_LAPTIMER(2461);
	UTL_SetPassFailCounterAccessAllDut( arg1, arg2);
	STOP_LAPTIMER(2461);
}
void _UTL_SetPassFailCounterAccessDut( PassFailCounterAccessHandle arg1, UT_DUT arg2)
{
	MCI_LIST[2462] = "UTL_SetPassFailCounterAccessDut";
	START_LAPTIMER(2462);
	UTL_SetPassFailCounterAccessDut( arg1, arg2);
	STOP_LAPTIMER(2462);
}
void _UTL_SetPassFailCounterAccessAllPin( PassFailCounterAccessHandle arg1, CheckButton arg2)
{
	MCI_LIST[2463] = "UTL_SetPassFailCounterAccessAllPin";
	START_LAPTIMER(2463);
	UTL_SetPassFailCounterAccessAllPin( arg1, arg2);
	STOP_LAPTIMER(2463);
}
void _UTL_SetPassFailCounterAccessPin( PassFailCounterAccessHandle arg1, UT_PIN arg2)
{
	MCI_LIST[2464] = "UTL_SetPassFailCounterAccessPin";
	START_LAPTIMER(2464);
	UTL_SetPassFailCounterAccessPin( arg1, arg2);
	STOP_LAPTIMER(2464);
}
void _UTL_UpdatePassFailCounter( PassFailCounterAccessHandle arg1)
{
	MCI_LIST[2465] = "UTL_UpdatePassFailCounter";
	START_LAPTIMER(2465);
	UTL_UpdatePassFailCounter( arg1);
	STOP_LAPTIMER(2465);
}
USlider _UTL_GetPassFailCounterValue( PassFailCounterAccessHandle arg1, RadioButton * arg2)
{
	MCI_LIST[2466] = "UTL_GetPassFailCounterValue";
	START_LAPTIMER(2466);
	USlider retval = UTL_GetPassFailCounterValue( arg1, arg2);
	STOP_LAPTIMER(2466);
	return retval;
}
TimingTrainingConditionHandle _UTL_GetTimingTrainingConditionHandle()
{
	MCI_LIST[2467] = "UTL_GetTimingTrainingConditionHandle";
	START_LAPTIMER(2467);
	TimingTrainingConditionHandle retval = UTL_GetTimingTrainingConditionHandle();
	STOP_LAPTIMER(2467);
	return retval;
}
void _UTL_AddTimingTrainingConditionPin( TimingTrainingConditionHandle arg1, UT_PIN arg2, UT_PIN arg3)
{
	MCI_LIST[2468] = "UTL_AddTimingTrainingConditionPin";
	START_LAPTIMER(2468);
	UTL_AddTimingTrainingConditionPin( arg1, arg2, arg3);
	STOP_LAPTIMER(2468);
}
void _UTL_ClearTimingTrainingConditionPin( TimingTrainingConditionHandle arg1)
{
	MCI_LIST[2469] = "UTL_ClearTimingTrainingConditionPin";
	START_LAPTIMER(2469);
	UTL_ClearTimingTrainingConditionPin( arg1);
	STOP_LAPTIMER(2469);
}
void _UTL_SetTimingTrainingConditionEdgeSelect( TimingTrainingConditionHandle arg1, RadioButton arg2)
{
	MCI_LIST[2470] = "UTL_SetTimingTrainingConditionEdgeSelect";
	START_LAPTIMER(2470);
	UTL_SetTimingTrainingConditionEdgeSelect( arg1, arg2);
	STOP_LAPTIMER(2470);
}
void _UTL_SetTimingTrainingConditionStartPoint( TimingTrainingConditionHandle arg1, DSlider arg2)
{
	MCI_LIST[2471] = "UTL_SetTimingTrainingConditionStartPoint";
	START_LAPTIMER(2471);
	UTL_SetTimingTrainingConditionStartPoint( arg1, arg2);
	STOP_LAPTIMER(2471);
}
void _UTL_SetTimingTrainingConditionStopPoint( TimingTrainingConditionHandle arg1, DSlider arg2)
{
	MCI_LIST[2472] = "UTL_SetTimingTrainingConditionStopPoint";
	START_LAPTIMER(2472);
	UTL_SetTimingTrainingConditionStopPoint( arg1, arg2);
	STOP_LAPTIMER(2472);
}
void _UTL_SetTimingTrainingConditionShiftValue( TimingTrainingConditionHandle arg1, DSlider arg2)
{
	MCI_LIST[2473] = "UTL_SetTimingTrainingConditionShiftValue";
	START_LAPTIMER(2473);
	UTL_SetTimingTrainingConditionShiftValue( arg1, arg2);
	STOP_LAPTIMER(2473);
}
void _UTL_SetTimingTrainingConditionJudgeLoopCount( TimingTrainingConditionHandle arg1, USlider arg2)
{
	MCI_LIST[2474] = "UTL_SetTimingTrainingConditionJudgeLoopCount";
	START_LAPTIMER(2474);
	UTL_SetTimingTrainingConditionJudgeLoopCount( arg1, arg2);
	STOP_LAPTIMER(2474);
}
void _UTL_SetTimingTrainingConditionJudgeLimit( TimingTrainingConditionHandle arg1, USlider arg2, USlider arg3)
{
	MCI_LIST[2475] = "UTL_SetTimingTrainingConditionJudgeLimit";
	START_LAPTIMER(2475);
	UTL_SetTimingTrainingConditionJudgeLimit( arg1, arg2, arg3);
	STOP_LAPTIMER(2475);
}
void _UTL_SetTimingTrainingConditionJudgeWidth( TimingTrainingConditionHandle arg1, DSlider arg2)
{
	MCI_LIST[2476] = "UTL_SetTimingTrainingConditionJudgeWidth";
	START_LAPTIMER(2476);
	UTL_SetTimingTrainingConditionJudgeWidth( arg1, arg2);
	STOP_LAPTIMER(2476);
}
void _UTL_SetTimingTrainingConditionCalcMode( TimingTrainingConditionHandle arg1, RadioButton arg2)
{
	MCI_LIST[2477] = "UTL_SetTimingTrainingConditionCalcMode";
	START_LAPTIMER(2477);
	UTL_SetTimingTrainingConditionCalcMode( arg1, arg2);
	STOP_LAPTIMER(2477);
}
void _UTL_SetTimingTrainingConditionEdgeRatio( TimingTrainingConditionHandle arg1, DSlider arg2)
{
	MCI_LIST[2478] = "UTL_SetTimingTrainingConditionEdgeRatio";
	START_LAPTIMER(2478);
	UTL_SetTimingTrainingConditionEdgeRatio( arg1, arg2);
	STOP_LAPTIMER(2478);
}
void _UTL_SetTimingTrainingConditionEdgeOffset( TimingTrainingConditionHandle arg1, DSlider arg2)
{
	MCI_LIST[2479] = "UTL_SetTimingTrainingConditionEdgeOffset";
	START_LAPTIMER(2479);
	UTL_SetTimingTrainingConditionEdgeOffset( arg1, arg2);
	STOP_LAPTIMER(2479);
}
void _UTL_SendTimingTrainingCondition( TimingTrainingConditionHandle arg1, RadioButton arg2)
{
	MCI_LIST[2480] = "UTL_SendTimingTrainingCondition";
	START_LAPTIMER(2480);
	UTL_SendTimingTrainingCondition( arg1, arg2);
	STOP_LAPTIMER(2480);
}
TimingTrainingCtrlHandle _UTL_GetTimingTrainingCtrlHandle()
{
	MCI_LIST[2481] = "UTL_GetTimingTrainingCtrlHandle";
	START_LAPTIMER(2481);
	TimingTrainingCtrlHandle retval = UTL_GetTimingTrainingCtrlHandle();
	STOP_LAPTIMER(2481);
	return retval;
}
void _UTL_SetTimingTrainingCtrlExecuteMode( TimingTrainingCtrlHandle arg1, RadioButton arg2)
{
	MCI_LIST[2482] = "UTL_SetTimingTrainingCtrlExecuteMode";
	START_LAPTIMER(2482);
	UTL_SetTimingTrainingCtrlExecuteMode( arg1, arg2);
	STOP_LAPTIMER(2482);
}
void _UTL_SendTimingTrainingCtrl( TimingTrainingCtrlHandle arg1, RadioButton arg2)
{
	MCI_LIST[2483] = "UTL_SendTimingTrainingCtrl";
	START_LAPTIMER(2483);
	UTL_SendTimingTrainingCtrl( arg1, arg2);
	STOP_LAPTIMER(2483);
}
TimingTrainingPinHandle _UTL_GetTimingTrainingPinHandle()
{
	MCI_LIST[2484] = "UTL_GetTimingTrainingPinHandle";
	START_LAPTIMER(2484);
	TimingTrainingPinHandle retval = UTL_GetTimingTrainingPinHandle();
	STOP_LAPTIMER(2484);
	return retval;
}
void _UTL_UpdateTimingTrainingPin( TimingTrainingPinHandle arg1, RadioButton arg2)
{
	MCI_LIST[2485] = "UTL_UpdateTimingTrainingPin";
	START_LAPTIMER(2485);
	UTL_UpdateTimingTrainingPin( arg1, arg2);
	STOP_LAPTIMER(2485);
}
int _UTL_GetTimingTrainingPinTargetPinStatus( TimingTrainingPinHandle arg1, UT_DUT arg2, UT_PIN arg3, int * arg4)
{
	MCI_LIST[2486] = "UTL_GetTimingTrainingPinTargetPinStatus";
	START_LAPTIMER(2486);
	int retval = UTL_GetTimingTrainingPinTargetPinStatus( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2486);
	return retval;
}
int _UTL_GetTimingTrainingPinTargetPinFailToPassMax( TimingTrainingPinHandle arg1, UT_DUT arg2, UT_PIN arg3, DSlider * arg4)
{
	MCI_LIST[2487] = "UTL_GetTimingTrainingPinTargetPinFailToPassMax";
	START_LAPTIMER(2487);
	int retval = UTL_GetTimingTrainingPinTargetPinFailToPassMax( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2487);
	return retval;
}
int _UTL_GetTimingTrainingPinTargetPinPassToFailMin( TimingTrainingPinHandle arg1, UT_DUT arg2, UT_PIN arg3, DSlider * arg4)
{
	MCI_LIST[2488] = "UTL_GetTimingTrainingPinTargetPinPassToFailMin";
	START_LAPTIMER(2488);
	int retval = UTL_GetTimingTrainingPinTargetPinPassToFailMin( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2488);
	return retval;
}
int _UTL_GetTimingTrainingPinTargetPinAdjustValueByDut( TimingTrainingPinHandle arg1, UT_DUT arg2, UT_PIN arg3, DSlider * arg4)
{
	MCI_LIST[2489] = "UTL_GetTimingTrainingPinTargetPinAdjustValueByDut";
	START_LAPTIMER(2489);
	int retval = UTL_GetTimingTrainingPinTargetPinAdjustValueByDut( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2489);
	return retval;
}
int _UTL_GetTimingTrainingPinCheckPinStatus( TimingTrainingPinHandle arg1, UT_DUT arg2, UT_PIN arg3, int * arg4)
{
	MCI_LIST[2490] = "UTL_GetTimingTrainingPinCheckPinStatus";
	START_LAPTIMER(2490);
	int retval = UTL_GetTimingTrainingPinCheckPinStatus( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2490);
	return retval;
}
int _UTL_GetTimingTrainingPinCheckPinFailToPass( TimingTrainingPinHandle arg1, UT_DUT arg2, UT_PIN arg3, DSlider * arg4)
{
	MCI_LIST[2491] = "UTL_GetTimingTrainingPinCheckPinFailToPass";
	START_LAPTIMER(2491);
	int retval = UTL_GetTimingTrainingPinCheckPinFailToPass( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2491);
	return retval;
}
int _UTL_GetTimingTrainingPinCheckPinPassToFail( TimingTrainingPinHandle arg1, UT_DUT arg2, UT_PIN arg3, DSlider * arg4)
{
	MCI_LIST[2492] = "UTL_GetTimingTrainingPinCheckPinPassToFail";
	START_LAPTIMER(2492);
	int retval = UTL_GetTimingTrainingPinCheckPinPassToFail( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2492);
	return retval;
}
int _UTL_GetTimingTrainingPinEdgeCount( TimingTrainingPinHandle arg1, USlider * arg2)
{
	MCI_LIST[2493] = "UTL_GetTimingTrainingPinEdgeCount";
	START_LAPTIMER(2493);
	int retval = UTL_GetTimingTrainingPinEdgeCount( arg1, arg2);
	STOP_LAPTIMER(2493);
	return retval;
}
int _UTL_GetTimingTrainingPinCheckPinFailCount( TimingTrainingPinHandle arg1, UT_DUT arg2, UT_PIN arg3, USlider arg4, USlider * arg5)
{
	MCI_LIST[2494] = "UTL_GetTimingTrainingPinCheckPinFailCount";
	START_LAPTIMER(2494);
	int retval = UTL_GetTimingTrainingPinCheckPinFailCount( arg1, arg2, arg3, arg4, arg5);
	STOP_LAPTIMER(2494);
	return retval;
}
int _UTL_GetTimingTrainingPinIsLatestFailCount( TimingTrainingPinHandle arg1, CheckButton * arg2)
{
	MCI_LIST[2495] = "UTL_GetTimingTrainingPinIsLatestFailCount";
	START_LAPTIMER(2495);
	int retval = UTL_GetTimingTrainingPinIsLatestFailCount( arg1, arg2);
	STOP_LAPTIMER(2495);
	return retval;
}
JiHandle _UTL_GetJiHandle()
{
	MCI_LIST[2496] = "UTL_GetJiHandle";
	START_LAPTIMER(2496);
	JiHandle retval = UTL_GetJiHandle();
	STOP_LAPTIMER(2496);
	return retval;
}
void _UTL_SetJiWaveform( JiHandle arg1, RadioButton arg2)
{
	MCI_LIST[2497] = "UTL_SetJiWaveform";
	START_LAPTIMER(2497);
	UTL_SetJiWaveform( arg1, arg2);
	STOP_LAPTIMER(2497);
}
void _UTL_SetJiFrequency( JiHandle arg1, DSlider arg2)
{
	MCI_LIST[2498] = "UTL_SetJiFrequency";
	START_LAPTIMER(2498);
	UTL_SetJiFrequency( arg1, arg2);
	STOP_LAPTIMER(2498);
}
void _UTL_SetJiAmplitude( JiHandle arg1, DSlider arg2)
{
	MCI_LIST[2499] = "UTL_SetJiAmplitude";
	START_LAPTIMER(2499);
	UTL_SetJiAmplitude( arg1, arg2);
	STOP_LAPTIMER(2499);
}
void _UTL_SendJi( JiHandle arg1)
{
	MCI_LIST[2500] = "UTL_SendJi";
	START_LAPTIMER(2500);
	UTL_SendJi( arg1);
	STOP_LAPTIMER(2500);
}
JiPinHandle _UTL_GetJiPinHandle()
{
	MCI_LIST[2501] = "UTL_GetJiPinHandle";
	START_LAPTIMER(2501);
	JiPinHandle retval = UTL_GetJiPinHandle();
	STOP_LAPTIMER(2501);
	return retval;
}
void _UTL_ClearJiPinNumber( JiPinHandle arg1)
{
	MCI_LIST[2502] = "UTL_ClearJiPinNumber";
	START_LAPTIMER(2502);
	UTL_ClearJiPinNumber( arg1);
	STOP_LAPTIMER(2502);
}
void _UTL_AddJiPinNumber( JiPinHandle arg1, UT_PIN arg2)
{
	MCI_LIST[2503] = "UTL_AddJiPinNumber";
	START_LAPTIMER(2503);
	UTL_AddJiPinNumber( arg1, arg2);
	STOP_LAPTIMER(2503);
}
void _UTL_SetJiPinTargetClock( JiPinHandle arg1, RadioButton arg2)
{
	MCI_LIST[2504] = "UTL_SetJiPinTargetClock";
	START_LAPTIMER(2504);
	UTL_SetJiPinTargetClock( arg1, arg2);
	STOP_LAPTIMER(2504);
}
void _UTL_SendJiPin( JiPinHandle arg1)
{
	MCI_LIST[2505] = "UTL_SendJiPin";
	START_LAPTIMER(2505);
	UTL_SendJiPin( arg1);
	STOP_LAPTIMER(2505);
}
JiStatusHandle _UTL_GetJiStatusHandle()
{
	MCI_LIST[2506] = "UTL_GetJiStatusHandle";
	START_LAPTIMER(2506);
	JiStatusHandle retval = UTL_GetJiStatusHandle();
	STOP_LAPTIMER(2506);
	return retval;
}
CheckButton _UTL_ReadJiStatusClamp( JiStatusHandle arg1)
{
	MCI_LIST[2507] = "UTL_ReadJiStatusClamp";
	START_LAPTIMER(2507);
	CheckButton retval = UTL_ReadJiStatusClamp( arg1);
	STOP_LAPTIMER(2507);
	return retval;
}
CtConfigHandle _UTL_GetCtConfigHandle()
{
	MCI_LIST[2508] = "UTL_GetCtConfigHandle";
	START_LAPTIMER(2508);
	CtConfigHandle retval = UTL_GetCtConfigHandle();
	STOP_LAPTIMER(2508);
	return retval;
}
void _UTL_SetCtConfigMethod( CtConfigHandle arg1, RadioButton arg2)
{
	MCI_LIST[2509] = "UTL_SetCtConfigMethod";
	START_LAPTIMER(2509);
	UTL_SetCtConfigMethod( arg1, arg2);
	STOP_LAPTIMER(2509);
}
void _UTL_SetCtConfigStartPoint( CtConfigHandle arg1, DSlider arg2)
{
	MCI_LIST[2510] = "UTL_SetCtConfigStartPoint";
	START_LAPTIMER(2510);
	UTL_SetCtConfigStartPoint( arg1, arg2);
	STOP_LAPTIMER(2510);
}
void _UTL_SendCtConfig( CtConfigHandle arg1)
{
	MCI_LIST[2511] = "UTL_SendCtConfig";
	START_LAPTIMER(2511);
	UTL_SendCtConfig( arg1);
	STOP_LAPTIMER(2511);
}
CtPinHandle _UTL_GetCtPinHandle()
{
	MCI_LIST[2512] = "UTL_GetCtPinHandle";
	START_LAPTIMER(2512);
	CtPinHandle retval = UTL_GetCtPinHandle();
	STOP_LAPTIMER(2512);
	return retval;
}
int _UTL_AddCtPinList( CtPinHandle arg1, char * arg2, char * arg3)
{
	MCI_LIST[2513] = "UTL_AddCtPinList";
	START_LAPTIMER(2513);
	int retval = UTL_AddCtPinList( arg1, arg2, arg3);
	STOP_LAPTIMER(2513);
	return retval;
}
void _UTL_ClearCtPinList( CtPinHandle arg1)
{
	MCI_LIST[2514] = "UTL_ClearCtPinList";
	START_LAPTIMER(2514);
	UTL_ClearCtPinList( arg1);
	STOP_LAPTIMER(2514);
}
void _UTL_SetCtPinExecMode( CtPinHandle arg1, RadioButton arg2)
{
	MCI_LIST[2515] = "UTL_SetCtPinExecMode";
	START_LAPTIMER(2515);
	UTL_SetCtPinExecMode( arg1, arg2);
	STOP_LAPTIMER(2515);
}
void _UTL_SendCtPin( CtPinHandle arg1)
{
	MCI_LIST[2516] = "UTL_SendCtPin";
	START_LAPTIMER(2516);
	UTL_SendCtPin( arg1);
	STOP_LAPTIMER(2516);
}
CtLogHandle _UTL_GetCtLogHandle()
{
	MCI_LIST[2517] = "UTL_GetCtLogHandle";
	START_LAPTIMER(2517);
	CtLogHandle retval = UTL_GetCtLogHandle();
	STOP_LAPTIMER(2517);
	return retval;
}
void _UTL_SetCtLogWaitTime( CtLogHandle arg1, DSlider arg2)
{
	MCI_LIST[2518] = "UTL_SetCtLogWaitTime";
	START_LAPTIMER(2518);
	UTL_SetCtLogWaitTime( arg1, arg2);
	STOP_LAPTIMER(2518);
}
void _UTL_SetCtLogDecimation( CtLogHandle arg1, USlider arg2)
{
	MCI_LIST[2519] = "UTL_SetCtLogDecimation";
	START_LAPTIMER(2519);
	UTL_SetCtLogDecimation( arg1, arg2);
	STOP_LAPTIMER(2519);
}
void _UTL_SetCtLogEnable( CtLogHandle arg1, CheckButton arg2)
{
	MCI_LIST[2520] = "UTL_SetCtLogEnable";
	START_LAPTIMER(2520);
	UTL_SetCtLogEnable( arg1, arg2);
	STOP_LAPTIMER(2520);
}
void _UTL_SendCtLog( CtLogHandle arg1)
{
	MCI_LIST[2521] = "UTL_SendCtLog";
	START_LAPTIMER(2521);
	UTL_SendCtLog( arg1);
	STOP_LAPTIMER(2521);
}
CheckButton _UTL_ReadCtStatusClamp( UT_PIN arg1, UT_DUT arg2)
{
	MCI_LIST[2522] = "UTL_ReadCtStatusClamp";
	START_LAPTIMER(2522);
	CheckButton retval = UTL_ReadCtStatusClamp( arg1, arg2);
	STOP_LAPTIMER(2522);
	return retval;
}
void _UTL_ReadCtStatusLogData( UT_PIN arg1, UT_DUT arg2, DSlider * arg3, USlider arg4)
{
	MCI_LIST[2523] = "UTL_ReadCtStatusLogData";
	START_LAPTIMER(2523);
	UTL_ReadCtStatusLogData( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2523);
}
USlider _UTL_ReadCtStatusLogDataLength( UT_PIN arg1, UT_DUT arg2)
{
	MCI_LIST[2524] = "UTL_ReadCtStatusLogDataLength";
	START_LAPTIMER(2524);
	USlider retval = UTL_ReadCtStatusLogDataLength( arg1, arg2);
	STOP_LAPTIMER(2524);
	return retval;
}
RadioButton _UTL_ReadCtStatusResult( UT_PIN arg1, UT_DUT arg2)
{
	MCI_LIST[2525] = "UTL_ReadCtStatusResult";
	START_LAPTIMER(2525);
	RadioButton retval = UTL_ReadCtStatusResult( arg1, arg2);
	STOP_LAPTIMER(2525);
	return retval;
}
void _UTL_ResetCt( RadioButton arg1)
{
	MCI_LIST[2526] = "UTL_ResetCt";
	START_LAPTIMER(2526);
	UTL_ResetCt( arg1);
	STOP_LAPTIMER(2526);
}
SourceSyncCpHandle _UTL_GetSourceSyncCpHandle()
{
	MCI_LIST[2527] = "UTL_GetSourceSyncCpHandle";
	START_LAPTIMER(2527);
	SourceSyncCpHandle retval = UTL_GetSourceSyncCpHandle();
	STOP_LAPTIMER(2527);
	return retval;
}
void _UTL_AddSourceSyncCpTargetPin( SourceSyncCpHandle arg1, UT_PIN arg2)
{
	MCI_LIST[2528] = "UTL_AddSourceSyncCpTargetPin";
	START_LAPTIMER(2528);
	UTL_AddSourceSyncCpTargetPin( arg1, arg2);
	STOP_LAPTIMER(2528);
}
void _UTL_ClearSourceSyncCpTargetPin( SourceSyncCpHandle arg1)
{
	MCI_LIST[2529] = "UTL_ClearSourceSyncCpTargetPin";
	START_LAPTIMER(2529);
	UTL_ClearSourceSyncCpTargetPin( arg1);
	STOP_LAPTIMER(2529);
}
void _UTL_SetSourceSyncCpMode( SourceSyncCpHandle arg1, CheckButton arg2)
{
	MCI_LIST[2530] = "UTL_SetSourceSyncCpMode";
	START_LAPTIMER(2530);
	UTL_SetSourceSyncCpMode( arg1, arg2);
	STOP_LAPTIMER(2530);
}
void _UTL_SendSourceSyncCp( SourceSyncCpHandle arg1)
{
	MCI_LIST[2531] = "UTL_SendSourceSyncCp";
	START_LAPTIMER(2531);
	UTL_SendSourceSyncCp( arg1);
	STOP_LAPTIMER(2531);
}
void _UTL_ResetSourceSyncCp()
{
	MCI_LIST[2532] = "UTL_ResetSourceSyncCp";
	START_LAPTIMER(2532);
	UTL_ResetSourceSyncCp();
	STOP_LAPTIMER(2532);
}
DcHvlvdrHandle _UTL_GetDcHvlvdrHandle()
{
	MCI_LIST[2533] = "UTL_GetDcHvlvdrHandle";
	START_LAPTIMER(2533);
	DcHvlvdrHandle retval = UTL_GetDcHvlvdrHandle();
	STOP_LAPTIMER(2533);
	return retval;
}
void _UTL_SetDcHvlvdrMode( DcHvlvdrHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[2534] = "UTL_SetDcHvlvdrMode";
	START_LAPTIMER(2534);
	UTL_SetDcHvlvdrMode( arg1, arg2);
	STOP_LAPTIMER(2534);
}
void _UTL_SetDcHvlvdrMrange( DcHvlvdrHandle  arg1, DSlider  arg2, DSlider  arg3)
{
	MCI_LIST[2535] = "UTL_SetDcHvlvdrMrange";
	START_LAPTIMER(2535);
	UTL_SetDcHvlvdrMrange( arg1, arg2, arg3);
	STOP_LAPTIMER(2535);
}
void _UTL_SetDcHvlvdrLimitHigh( DcHvlvdrHandle  arg1, DSlider  arg2, CheckButton  arg3)
{
	MCI_LIST[2536] = "UTL_SetDcHvlvdrLimitHigh";
	START_LAPTIMER(2536);
	UTL_SetDcHvlvdrLimitHigh( arg1, arg2, arg3);
	STOP_LAPTIMER(2536);
}
void _UTL_SetDcHvlvdrLimitLow( DcHvlvdrHandle  arg1, DSlider  arg2, CheckButton  arg3)
{
	MCI_LIST[2537] = "UTL_SetDcHvlvdrLimitLow";
	START_LAPTIMER(2537);
	UTL_SetDcHvlvdrLimitLow( arg1, arg2, arg3);
	STOP_LAPTIMER(2537);
}
void _UTL_SetDcHvlvdrMeasCnt( DcHvlvdrHandle  arg1, Slider  arg2)
{
	MCI_LIST[2538] = "UTL_SetDcHvlvdrMeasCnt";
	START_LAPTIMER(2538);
	UTL_SetDcHvlvdrMeasCnt( arg1, arg2);
	STOP_LAPTIMER(2538);
}
void _UTL_SendDcHvlvdr( DcHvlvdrHandle  arg1)
{
	MCI_LIST[2539] = "UTL_SendDcHvlvdr";
	START_LAPTIMER(2539);
	UTL_SendDcHvlvdr( arg1);
	STOP_LAPTIMER(2539);
}
void _UTL_WriteDcHvlvdrSettlingTime( DSlider  arg1)
{
	MCI_LIST[2540] = "UTL_WriteDcHvlvdrSettlingTime";
	START_LAPTIMER(2540);
	UTL_WriteDcHvlvdrSettlingTime( arg1);
	STOP_LAPTIMER(2540);
}
void _UTL_UpdateDcHvlvdr( DcHvlvdrHandle arg1)
{
	MCI_LIST[2541] = "UTL_UpdateDcHvlvdr";
	START_LAPTIMER(2541);
	UTL_UpdateDcHvlvdr( arg1);
	STOP_LAPTIMER(2541);
}
int _UTL_GetDcHvlvdrMode( DcHvlvdrHandle  arg1, RadioButton *  arg2)
{
	MCI_LIST[2542] = "UTL_GetDcHvlvdrMode";
	START_LAPTIMER(2542);
	int retval = UTL_GetDcHvlvdrMode( arg1, arg2);
	STOP_LAPTIMER(2542);
	return retval;
}
int _UTL_GetDcHvlvdrMrangeMax( DcHvlvdrHandle  arg1, DSlider *  arg2)
{
	MCI_LIST[2543] = "UTL_GetDcHvlvdrMrangeMax";
	START_LAPTIMER(2543);
	int retval = UTL_GetDcHvlvdrMrangeMax( arg1, arg2);
	STOP_LAPTIMER(2543);
	return retval;
}
int _UTL_GetDcHvlvdrMrangeMin( DcHvlvdrHandle  arg1, DSlider *  arg2)
{
	MCI_LIST[2544] = "UTL_GetDcHvlvdrMrangeMin";
	START_LAPTIMER(2544);
	int retval = UTL_GetDcHvlvdrMrangeMin( arg1, arg2);
	STOP_LAPTIMER(2544);
	return retval;
}
int _UTL_GetDcHvlvdrLimitHigh( DcHvlvdrHandle  arg1, DSlider *  arg2)
{
	MCI_LIST[2545] = "UTL_GetDcHvlvdrLimitHigh";
	START_LAPTIMER(2545);
	int retval = UTL_GetDcHvlvdrLimitHigh( arg1, arg2);
	STOP_LAPTIMER(2545);
	return retval;
}
int _UTL_GetDcHvlvdrLimitHighDo( DcHvlvdrHandle  arg1, CheckButton *  arg2)
{
	MCI_LIST[2546] = "UTL_GetDcHvlvdrLimitHighDo";
	START_LAPTIMER(2546);
	int retval = UTL_GetDcHvlvdrLimitHighDo( arg1, arg2);
	STOP_LAPTIMER(2546);
	return retval;
}
int _UTL_GetDcHvlvdrLimitLow( DcHvlvdrHandle  arg1, DSlider *  arg2)
{
	MCI_LIST[2547] = "UTL_GetDcHvlvdrLimitLow";
	START_LAPTIMER(2547);
	int retval = UTL_GetDcHvlvdrLimitLow( arg1, arg2);
	STOP_LAPTIMER(2547);
	return retval;
}
int _UTL_GetDcHvlvdrLimitLowDo( DcHvlvdrHandle  arg1, CheckButton *  arg2)
{
	MCI_LIST[2548] = "UTL_GetDcHvlvdrLimitLowDo";
	START_LAPTIMER(2548);
	int retval = UTL_GetDcHvlvdrLimitLowDo( arg1, arg2);
	STOP_LAPTIMER(2548);
	return retval;
}
int _UTL_GetDcHvlvdrMeasCnt( DcHvlvdrHandle  arg1, Slider *  arg2)
{
	MCI_LIST[2549] = "UTL_GetDcHvlvdrMeasCnt";
	START_LAPTIMER(2549);
	int retval = UTL_GetDcHvlvdrMeasCnt( arg1, arg2);
	STOP_LAPTIMER(2549);
	return retval;
}
DSlider _UTL_ReadDcHvlvdrSettlingTime()
{
	MCI_LIST[2550] = "UTL_ReadDcHvlvdrSettlingTime";
	START_LAPTIMER(2550);
	DSlider retval = UTL_ReadDcHvlvdrSettlingTime();
	STOP_LAPTIMER(2550);
	return retval;
}
DctHvlvdrHandle _UTL_GetDctHvlvdrHandle()
{
	MCI_LIST[2551] = "UTL_GetDctHvlvdrHandle";
	START_LAPTIMER(2551);
	DctHvlvdrHandle retval = UTL_GetDctHvlvdrHandle();
	STOP_LAPTIMER(2551);
	return retval;
}
void _UTL_SetDctHvlvdrPinList( DctHvlvdrHandle  arg1, char * arg2)
{
	MCI_LIST[2552] = "UTL_SetDctHvlvdrPinList";
	START_LAPTIMER(2552);
	UTL_SetDctHvlvdrPinList( arg1, arg2);
	STOP_LAPTIMER(2552);
}
void _UTL_MeasDctHvlvdr( DctHvlvdrHandle  arg1)
{
	MCI_LIST[2553] = "UTL_MeasDctHvlvdr";
	START_LAPTIMER(2553);
	UTL_MeasDctHvlvdr( arg1);
	STOP_LAPTIMER(2553);
}
AdcHvlvdrHandle _UTL_GetAdcHvlvdrHandle()
{
	MCI_LIST[2554] = "UTL_GetAdcHvlvdrHandle";
	START_LAPTIMER(2554);
	AdcHvlvdrHandle retval = UTL_GetAdcHvlvdrHandle();
	STOP_LAPTIMER(2554);
	return retval;
}
void _UTL_SetAdcHvlvdrPgEnable( AdcHvlvdrHandle arg1, CheckButton arg2)
{
	MCI_LIST[2555] = "UTL_SetAdcHvlvdrPgEnable";
	START_LAPTIMER(2555);
	UTL_SetAdcHvlvdrPgEnable( arg1, arg2);
	STOP_LAPTIMER(2555);
}
void _UTL_SetAdcHvlvdrStartCycle( AdcHvlvdrHandle arg1, RadioButton arg2)
{
	MCI_LIST[2556] = "UTL_SetAdcHvlvdrStartCycle";
	START_LAPTIMER(2556);
	UTL_SetAdcHvlvdrStartCycle( arg1, arg2);
	STOP_LAPTIMER(2556);
}
void _UTL_SetAdcHvlvdrPinList( AdcHvlvdrHandle arg1, char * arg2)
{
	MCI_LIST[2557] = "UTL_SetAdcHvlvdrPinList";
	START_LAPTIMER(2557);
	UTL_SetAdcHvlvdrPinList( arg1, arg2);
	STOP_LAPTIMER(2557);
}
void _UTL_SendAdcHvlvdr( AdcHvlvdrHandle arg1)
{
	MCI_LIST[2558] = "UTL_SendAdcHvlvdr";
	START_LAPTIMER(2558);
	UTL_SendAdcHvlvdr( arg1);
	STOP_LAPTIMER(2558);
}
void _UTL_UpdateAdcHvlvdr( AdcHvlvdrHandle arg1)
{
	MCI_LIST[2559] = "UTL_UpdateAdcHvlvdr";
	START_LAPTIMER(2559);
	UTL_UpdateAdcHvlvdr( arg1);
	STOP_LAPTIMER(2559);
}
int _UTL_GetAdcHvlvdrPgEnable( AdcHvlvdrHandle  arg1, CheckButton *  arg2)
{
	MCI_LIST[2560] = "UTL_GetAdcHvlvdrPgEnable";
	START_LAPTIMER(2560);
	int retval = UTL_GetAdcHvlvdrPgEnable( arg1, arg2);
	STOP_LAPTIMER(2560);
	return retval;
}
int _UTL_GetAdcHvlvdrStartCycle( AdcHvlvdrHandle  arg1, RadioButton *  arg2)
{
	MCI_LIST[2561] = "UTL_GetAdcHvlvdrStartCycle";
	START_LAPTIMER(2561);
	int retval = UTL_GetAdcHvlvdrStartCycle( arg1, arg2);
	STOP_LAPTIMER(2561);
	return retval;
}
int _UTL_GetAdcHvlvdrPinList( AdcHvlvdrHandle  arg1, char **  arg2)
{
	MCI_LIST[2562] = "UTL_GetAdcHvlvdrPinList";
	START_LAPTIMER(2562);
	int retval = UTL_GetAdcHvlvdrPinList( arg1, arg2);
	STOP_LAPTIMER(2562);
	return retval;
}
DctHvlvdrReadPinHandle _UTL_GetDctHvlvdrReadPinHandle()
{
	MCI_LIST[2563] = "UTL_GetDctHvlvdrReadPinHandle";
	START_LAPTIMER(2563);
	DctHvlvdrReadPinHandle retval = UTL_GetDctHvlvdrReadPinHandle();
	STOP_LAPTIMER(2563);
	return retval;
}
void _UTL_SetDctHvlvdrReadPinDut( DctHvlvdrReadPinHandle  arg1, UT_DUT  arg2)
{
	MCI_LIST[2564] = "UTL_SetDctHvlvdrReadPinDut";
	START_LAPTIMER(2564);
	UTL_SetDctHvlvdrReadPinDut( arg1, arg2);
	STOP_LAPTIMER(2564);
}
void _UTL_SetDctHvlvdrReadPinNumber( DctHvlvdrReadPinHandle  arg1, UT_PIN  arg2)
{
	MCI_LIST[2565] = "UTL_SetDctHvlvdrReadPinNumber";
	START_LAPTIMER(2565);
	UTL_SetDctHvlvdrReadPinNumber( arg1, arg2);
	STOP_LAPTIMER(2565);
}
void _UTL_SetDctHvlvdrReadPinMode( DctHvlvdrReadPinHandle  arg1, RadioButton  arg2)
{
	MCI_LIST[2566] = "UTL_SetDctHvlvdrReadPinMode";
	START_LAPTIMER(2566);
	UTL_SetDctHvlvdrReadPinMode( arg1, arg2);
	STOP_LAPTIMER(2566);
}
DSlider _UTL_ReadDctHvlvdrPinData( DctHvlvdrReadPinHandle  arg1)
{
	MCI_LIST[2567] = "UTL_ReadDctHvlvdrPinData";
	START_LAPTIMER(2567);
	DSlider retval = UTL_ReadDctHvlvdrPinData( arg1);
	STOP_LAPTIMER(2567);
	return retval;
}
CheckButton _UTL_ReadDctHvlvdrPin( DctHvlvdrReadPinHandle  arg1)
{
	MCI_LIST[2568] = "UTL_ReadDctHvlvdrPin";
	START_LAPTIMER(2568);
	CheckButton retval = UTL_ReadDctHvlvdrPin( arg1);
	STOP_LAPTIMER(2568);
	return retval;
}
UT_ErrorInfo _UTSC_ErrorInfo_Construct()
{
	MCI_LIST[2569] = "UTSC_ErrorInfo_Construct";
	START_LAPTIMER(2569);
	UT_ErrorInfo retval = UTSC_ErrorInfo_Construct();
	STOP_LAPTIMER(2569);
	return retval;
}
int _UTSC_ErrorInfo_Destruct( UT_ErrorInfo arg1)
{
	MCI_LIST[2570] = "UTSC_ErrorInfo_Destruct";
	START_LAPTIMER(2570);
	int retval = UTSC_ErrorInfo_Destruct( arg1);
	STOP_LAPTIMER(2570);
	return retval;
}
int _UTSC_ErrorInfo_SetMessageId( UT_ErrorInfo arg1, char * arg2)
{
	MCI_LIST[2571] = "UTSC_ErrorInfo_SetMessageId";
	START_LAPTIMER(2571);
	int retval = UTSC_ErrorInfo_SetMessageId( arg1, arg2);
	STOP_LAPTIMER(2571);
	return retval;
}
char * _UTSC_ErrorInfo_GetMessageId( UT_ErrorInfo arg1)
{
	MCI_LIST[2572] = "UTSC_ErrorInfo_GetMessageId";
	START_LAPTIMER(2572);
	char * retval = UTSC_ErrorInfo_GetMessageId( arg1);
	STOP_LAPTIMER(2572);
	return retval;
}
int _UTSC_ErrorInfo_AddMessageArgs( UT_ErrorInfo arg1, char * arg2)
{
	MCI_LIST[2573] = "UTSC_ErrorInfo_AddMessageArgs";
	START_LAPTIMER(2573);
	int retval = UTSC_ErrorInfo_AddMessageArgs( arg1, arg2);
	STOP_LAPTIMER(2573);
	return retval;
}
UT_ErrorInfoList _UTSC_ErrorInfo_GetMessageArgsList( UT_ErrorInfo arg1)
{
	MCI_LIST[2574] = "UTSC_ErrorInfo_GetMessageArgsList";
	START_LAPTIMER(2574);
	UT_ErrorInfoList retval = UTSC_ErrorInfo_GetMessageArgsList( arg1);
	STOP_LAPTIMER(2574);
	return retval;
}
int _UTSC_ErrorInfo_GetMessageArgsNum( UT_ErrorInfoList arg1)
{
	MCI_LIST[2575] = "UTSC_ErrorInfo_GetMessageArgsNum";
	START_LAPTIMER(2575);
	int retval = UTSC_ErrorInfo_GetMessageArgsNum( arg1);
	STOP_LAPTIMER(2575);
	return retval;
}
char * _UTSC_ErrorInfo_GetMessageArgs( UT_ErrorInfoList arg1, int arg2)
{
	MCI_LIST[2576] = "UTSC_ErrorInfo_GetMessageArgs";
	START_LAPTIMER(2576);
	char * retval = UTSC_ErrorInfo_GetMessageArgs( arg1, arg2);
	STOP_LAPTIMER(2576);
	return retval;
}
int _UTSC_ErrorInfo_SetStation( UT_ErrorInfo arg1, char * arg2)
{
	MCI_LIST[2577] = "UTSC_ErrorInfo_SetStation";
	START_LAPTIMER(2577);
	int retval = UTSC_ErrorInfo_SetStation( arg1, arg2);
	STOP_LAPTIMER(2577);
	return retval;
}
char * _UTSC_ErrorInfo_GetStation( UT_ErrorInfo arg1)
{
	MCI_LIST[2578] = "UTSC_ErrorInfo_GetStation";
	START_LAPTIMER(2578);
	char * retval = UTSC_ErrorInfo_GetStation( arg1);
	STOP_LAPTIMER(2578);
	return retval;
}
int _UTSC_ErrorInfo_SetSite( UT_ErrorInfo arg1, char * arg2)
{
	MCI_LIST[2579] = "UTSC_ErrorInfo_SetSite";
	START_LAPTIMER(2579);
	int retval = UTSC_ErrorInfo_SetSite( arg1, arg2);
	STOP_LAPTIMER(2579);
	return retval;
}
char * _UTSC_ErrorInfo_GetSite( UT_ErrorInfo arg1)
{
	MCI_LIST[2580] = "UTSC_ErrorInfo_GetSite";
	START_LAPTIMER(2580);
	char * retval = UTSC_ErrorInfo_GetSite( arg1);
	STOP_LAPTIMER(2580);
	return retval;
}
int _UTSC_ErrorInfo_SetComponent( UT_ErrorInfo arg1, char * arg2)
{
	MCI_LIST[2581] = "UTSC_ErrorInfo_SetComponent";
	START_LAPTIMER(2581);
	int retval = UTSC_ErrorInfo_SetComponent( arg1, arg2);
	STOP_LAPTIMER(2581);
	return retval;
}
char * _UTSC_ErrorInfo_GetComponent( UT_ErrorInfo arg1)
{
	MCI_LIST[2582] = "UTSC_ErrorInfo_GetComponent";
	START_LAPTIMER(2582);
	char * retval = UTSC_ErrorInfo_GetComponent( arg1);
	STOP_LAPTIMER(2582);
	return retval;
}
int _UTSC_ErrorInfo_SetProgram( UT_ErrorInfo arg1, char * arg2)
{
	MCI_LIST[2583] = "UTSC_ErrorInfo_SetProgram";
	START_LAPTIMER(2583);
	int retval = UTSC_ErrorInfo_SetProgram( arg1, arg2);
	STOP_LAPTIMER(2583);
	return retval;
}
char * _UTSC_ErrorInfo_GetProgram( UT_ErrorInfo arg1)
{
	MCI_LIST[2584] = "UTSC_ErrorInfo_GetProgram";
	START_LAPTIMER(2584);
	char * retval = UTSC_ErrorInfo_GetProgram( arg1);
	STOP_LAPTIMER(2584);
	return retval;
}
int _UTSC_ErrorInfo_SetTestName( UT_ErrorInfo arg1, char * arg2)
{
	MCI_LIST[2585] = "UTSC_ErrorInfo_SetTestName";
	START_LAPTIMER(2585);
	int retval = UTSC_ErrorInfo_SetTestName( arg1, arg2);
	STOP_LAPTIMER(2585);
	return retval;
}
char * _UTSC_ErrorInfo_GetTestName( UT_ErrorInfo arg1)
{
	MCI_LIST[2586] = "UTSC_ErrorInfo_GetTestName";
	START_LAPTIMER(2586);
	char * retval = UTSC_ErrorInfo_GetTestName( arg1);
	STOP_LAPTIMER(2586);
	return retval;
}
int _UTSC_ErrorInfo_SetFunction( UT_ErrorInfo arg1, char * arg2)
{
	MCI_LIST[2587] = "UTSC_ErrorInfo_SetFunction";
	START_LAPTIMER(2587);
	int retval = UTSC_ErrorInfo_SetFunction( arg1, arg2);
	STOP_LAPTIMER(2587);
	return retval;
}
char * _UTSC_ErrorInfo_GetFunction( UT_ErrorInfo arg1)
{
	MCI_LIST[2588] = "UTSC_ErrorInfo_GetFunction";
	START_LAPTIMER(2588);
	char * retval = UTSC_ErrorInfo_GetFunction( arg1);
	STOP_LAPTIMER(2588);
	return retval;
}
int _UTSC_ErrorInfo_SetCatalog( UT_ErrorInfo arg1, char * arg2)
{
	MCI_LIST[2589] = "UTSC_ErrorInfo_SetCatalog";
	START_LAPTIMER(2589);
	int retval = UTSC_ErrorInfo_SetCatalog( arg1, arg2);
	STOP_LAPTIMER(2589);
	return retval;
}
char * _UTSC_ErrorInfo_GetCatalog( UT_ErrorInfo arg1)
{
	MCI_LIST[2590] = "UTSC_ErrorInfo_GetCatalog";
	START_LAPTIMER(2590);
	char * retval = UTSC_ErrorInfo_GetCatalog( arg1);
	STOP_LAPTIMER(2590);
	return retval;
}
int _UTSC_ErrorInfo_AddExtra( UT_ErrorInfo arg1, char * arg2)
{
	MCI_LIST[2591] = "UTSC_ErrorInfo_AddExtra";
	START_LAPTIMER(2591);
	int retval = UTSC_ErrorInfo_AddExtra( arg1, arg2);
	STOP_LAPTIMER(2591);
	return retval;
}
UT_ErrorInfoList _UTSC_ErrorInfo_GetExtraList( UT_ErrorInfo arg1)
{
	MCI_LIST[2592] = "UTSC_ErrorInfo_GetExtraList";
	START_LAPTIMER(2592);
	UT_ErrorInfoList retval = UTSC_ErrorInfo_GetExtraList( arg1);
	STOP_LAPTIMER(2592);
	return retval;
}
int _UTSC_ErrorInfo_GetExtraNum( UT_ErrorInfoList arg1)
{
	MCI_LIST[2593] = "UTSC_ErrorInfo_GetExtraNum";
	START_LAPTIMER(2593);
	int retval = UTSC_ErrorInfo_GetExtraNum( arg1);
	STOP_LAPTIMER(2593);
	return retval;
}
char * _UTSC_ErrorInfo_GetExtra( UT_ErrorInfoList arg1, int arg2)
{
	MCI_LIST[2594] = "UTSC_ErrorInfo_GetExtra";
	START_LAPTIMER(2594);
	char * retval = UTSC_ErrorInfo_GetExtra( arg1, arg2);
	STOP_LAPTIMER(2594);
	return retval;
}
UT_ErrorInfo _UTSC_ErrorInfo_Get( int arg1)
{
	MCI_LIST[2595] = "UTSC_ErrorInfo_Get";
	START_LAPTIMER(2595);
	UT_ErrorInfo retval = UTSC_ErrorInfo_Get( arg1);
	STOP_LAPTIMER(2595);
	return retval;
}
UT_ErrorInfo _UTSC_ErrorInfo_Deserialize( char * arg1, size_t arg2)
{
	MCI_LIST[2596] = "UTSC_ErrorInfo_Deserialize";
	START_LAPTIMER(2596);
	UT_ErrorInfo retval = UTSC_ErrorInfo_Deserialize( arg1, arg2);
	STOP_LAPTIMER(2596);
	return retval;
}
int _UTSC_Rm_Lock( char * arg1, char * arg2)
{
	MCI_LIST[2597] = "UTSC_Rm_Lock";
	START_LAPTIMER(2597);
	int retval = UTSC_Rm_Lock( arg1, arg2);
	STOP_LAPTIMER(2597);
	return retval;
}
int _UTSC_Rm_TryLock( char * arg1, char * arg2)
{
	MCI_LIST[2598] = "UTSC_Rm_TryLock";
	START_LAPTIMER(2598);
	int retval = UTSC_Rm_TryLock( arg1, arg2);
	STOP_LAPTIMER(2598);
	return retval;
}
int _UTSC_Rm_Unlock( char * arg1)
{
	MCI_LIST[2599] = "UTSC_Rm_Unlock";
	START_LAPTIMER(2599);
	int retval = UTSC_Rm_Unlock( arg1);
	STOP_LAPTIMER(2599);
	return retval;
}
void _UTSC_Rm_ExitOnError( int arg1)
{
	MCI_LIST[2600] = "UTSC_Rm_ExitOnError";
	START_LAPTIMER(2600);
	UTSC_Rm_ExitOnError( arg1);
	STOP_LAPTIMER(2600);
}
char * _UTSC_Rm_GetErrorMessage()
{
	MCI_LIST[2601] = "UTSC_Rm_GetErrorMessage";
	START_LAPTIMER(2601);
	char * retval = UTSC_Rm_GetErrorMessage();
	STOP_LAPTIMER(2601);
	return retval;
}
int _UTSC_Gpib_Open( char * arg1, UTSC_Gpib * arg2)
{
	MCI_LIST[2602] = "UTSC_Gpib_Open";
	START_LAPTIMER(2602);
	int retval = UTSC_Gpib_Open( arg1, arg2);
	STOP_LAPTIMER(2602);
	return retval;
}
int _UTSC_Gpib_Close( UTSC_Gpib arg1)
{
	MCI_LIST[2603] = "UTSC_Gpib_Close";
	START_LAPTIMER(2603);
	int retval = UTSC_Gpib_Close( arg1);
	STOP_LAPTIMER(2603);
	return retval;
}
int _UTSC_Gpib_SetConfig( UTSC_Gpib arg1, char * arg2, char * arg3)
{
	MCI_LIST[2604] = "UTSC_Gpib_SetConfig";
	START_LAPTIMER(2604);
	int retval = UTSC_Gpib_SetConfig( arg1, arg2, arg3);
	STOP_LAPTIMER(2604);
	return retval;
}
int _UTSC_Gpib_GetConfig( UTSC_Gpib arg1, char * arg2, char * arg3, UTSC_size_t arg4)
{
	MCI_LIST[2605] = "UTSC_Gpib_GetConfig";
	START_LAPTIMER(2605);
	int retval = UTSC_Gpib_GetConfig( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2605);
	return retval;
}
int _UTSC_Gpib_SendData( UTSC_Gpib arg1, void * arg2, UTSC_size_t arg3)
{
	MCI_LIST[2606] = "UTSC_Gpib_SendData";
	START_LAPTIMER(2606);
	int retval = UTSC_Gpib_SendData( arg1, arg2, arg3);
	STOP_LAPTIMER(2606);
	return retval;
}
int _UTSC_Gpib_RecvData( UTSC_Gpib arg1, void * arg2, UTSC_size_t arg3, UTSC_size_t * arg4)
{
	MCI_LIST[2607] = "UTSC_Gpib_RecvData";
	START_LAPTIMER(2607);
	int retval = UTSC_Gpib_RecvData( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2607);
	return retval;
}
int _UTSC_Gpib_ClearDevice( UTSC_Gpib arg1)
{
	MCI_LIST[2608] = "UTSC_Gpib_ClearDevice";
	START_LAPTIMER(2608);
	int retval = UTSC_Gpib_ClearDevice( arg1);
	STOP_LAPTIMER(2608);
	return retval;
}
int _UTSC_Gpib_TriggerDevice( UTSC_Gpib arg1)
{
	MCI_LIST[2609] = "UTSC_Gpib_TriggerDevice";
	START_LAPTIMER(2609);
	int retval = UTSC_Gpib_TriggerDevice( arg1);
	STOP_LAPTIMER(2609);
	return retval;
}
int _UTSC_Gpib_RecvStb( UTSC_Gpib arg1, int * arg2)
{
	MCI_LIST[2610] = "UTSC_Gpib_RecvStb";
	START_LAPTIMER(2610);
	int retval = UTSC_Gpib_RecvStb( arg1, arg2);
	STOP_LAPTIMER(2610);
	return retval;
}
int _UTSC_Gpib_RecvStbAll( UTSC_Gpib arg1, int * arg2)
{
	MCI_LIST[2611] = "UTSC_Gpib_RecvStbAll";
	START_LAPTIMER(2611);
	int retval = UTSC_Gpib_RecvStbAll( arg1, arg2);
	STOP_LAPTIMER(2611);
	return retval;
}
int _UTSC_Gpib_WaitSrq( UTSC_Gpib arg1, long arg2)
{
	MCI_LIST[2612] = "UTSC_Gpib_WaitSrq";
	START_LAPTIMER(2612);
	int retval = UTSC_Gpib_WaitSrq( arg1, arg2);
	STOP_LAPTIMER(2612);
	return retval;
}
int _UTSC_Gpib_GetChannel( UTSC_Gpib arg1, int * arg2)
{
	MCI_LIST[2613] = "UTSC_Gpib_GetChannel";
	START_LAPTIMER(2613);
	int retval = UTSC_Gpib_GetChannel( arg1, arg2);
	STOP_LAPTIMER(2613);
	return retval;
}
void _UTSC_Gpib_ExitOnError( int arg1)
{
	MCI_LIST[2614] = "UTSC_Gpib_ExitOnError";
	START_LAPTIMER(2614);
	UTSC_Gpib_ExitOnError( arg1);
	STOP_LAPTIMER(2614);
}
char * _UTSC_Gpib_GetErrorMessage()
{
	MCI_LIST[2615] = "UTSC_Gpib_GetErrorMessage";
	START_LAPTIMER(2615);
	char * retval = UTSC_Gpib_GetErrorMessage();
	STOP_LAPTIMER(2615);
	return retval;
}
int _UTSC_Sm_Attach( const char * arg1)
{
	MCI_LIST[2616] = "UTSC_Sm_Attach";
	START_LAPTIMER(2616);
	int retval = UTSC_Sm_Attach( arg1);
	STOP_LAPTIMER(2616);
	return retval;
}
int _UTSC_Sm_Detach()
{
	MCI_LIST[2617] = "UTSC_Sm_Detach";
	START_LAPTIMER(2617);
	int retval = UTSC_Sm_Detach();
	STOP_LAPTIMER(2617);
	return retval;
}
int _UTSC_Sm_GetSessionId( char ** arg1)
{
	MCI_LIST[2618] = "UTSC_Sm_GetSessionId";
	START_LAPTIMER(2618);
	int retval = UTSC_Sm_GetSessionId( arg1);
	STOP_LAPTIMER(2618);
	return retval;
}
int _UTSC_Sm_GetSessionAttribute( int arg1, char ** arg2)
{
	MCI_LIST[2619] = "UTSC_Sm_GetSessionAttribute";
	START_LAPTIMER(2619);
	int retval = UTSC_Sm_GetSessionAttribute( arg1, arg2);
	STOP_LAPTIMER(2619);
	return retval;
}
int _UTSC_Sm_GetSessionPgid( char ** arg1)
{
	MCI_LIST[2620] = "UTSC_Sm_GetSessionPgid";
	START_LAPTIMER(2620);
	int retval = UTSC_Sm_GetSessionPgid( arg1);
	STOP_LAPTIMER(2620);
	return retval;
}
int _UTSC_Sm_GetTestUnitNumber( int * arg1)
{
	MCI_LIST[2621] = "UTSC_Sm_GetTestUnitNumber";
	START_LAPTIMER(2621);
	int retval = UTSC_Sm_GetTestUnitNumber( arg1);
	STOP_LAPTIMER(2621);
	return retval;
}
int _UTSC_Sm_GetTestSiteNumber( int * arg1)
{
	MCI_LIST[2622] = "UTSC_Sm_GetTestSiteNumber";
	START_LAPTIMER(2622);
	int retval = UTSC_Sm_GetTestSiteNumber( arg1);
	STOP_LAPTIMER(2622);
	return retval;
}
int _UTSC_Sm_GetRepairSiteNumber( int * arg1)
{
	MCI_LIST[2623] = "UTSC_Sm_GetRepairSiteNumber";
	START_LAPTIMER(2623);
	int retval = UTSC_Sm_GetRepairSiteNumber( arg1);
	STOP_LAPTIMER(2623);
	return retval;
}
int _UTSC_Sm_ProcessGroup_Reserve( char * arg1, int arg2, char ** arg3)
{
	MCI_LIST[2624] = "UTSC_Sm_ProcessGroup_Reserve";
	START_LAPTIMER(2624);
	int retval = UTSC_Sm_ProcessGroup_Reserve( arg1, arg2, arg3);
	STOP_LAPTIMER(2624);
	return retval;
}
int _UTSC_Sm_Exec( char * arg1, UTSC_SmPro arg2)
{
	MCI_LIST[2625] = "UTSC_Sm_Exec";
	START_LAPTIMER(2625);
	int retval = UTSC_Sm_Exec( arg1, arg2);
	STOP_LAPTIMER(2625);
	return retval;
}
int _UTSC_Sm_Term( char * arg1, char * arg2)
{
	MCI_LIST[2626] = "UTSC_Sm_Term";
	START_LAPTIMER(2626);
	int retval = UTSC_Sm_Term( arg1, arg2);
	STOP_LAPTIMER(2626);
	return retval;
}
int _UTSC_Sm_Kill( char * arg1, char * arg2)
{
	MCI_LIST[2627] = "UTSC_Sm_Kill";
	START_LAPTIMER(2627);
	int retval = UTSC_Sm_Kill( arg1, arg2);
	STOP_LAPTIMER(2627);
	return retval;
}
int _UTSC_Sm_GetPgidStatus( char * arg1, char * arg2, char ** arg3, void ** arg4, size_t * arg5)
{
	MCI_LIST[2628] = "UTSC_Sm_GetPgidStatus";
	START_LAPTIMER(2628);
	int retval = UTSC_Sm_GetPgidStatus( arg1, arg2, arg3, arg4, arg5);
	STOP_LAPTIMER(2628);
	return retval;
}
int _UTSC_SmPro_Construct( UTSC_SmPro * arg1)
{
	MCI_LIST[2629] = "UTSC_SmPro_Construct";
	START_LAPTIMER(2629);
	int retval = UTSC_SmPro_Construct( arg1);
	STOP_LAPTIMER(2629);
	return retval;
}
int _UTSC_SmPro_Destruct( UTSC_SmPro arg1)
{
	MCI_LIST[2630] = "UTSC_SmPro_Destruct";
	START_LAPTIMER(2630);
	int retval = UTSC_SmPro_Destruct( arg1);
	STOP_LAPTIMER(2630);
	return retval;
}
int _UTSC_SmPro_File_Set( UTSC_SmPro arg1, char * arg2)
{
	MCI_LIST[2631] = "UTSC_SmPro_File_Set";
	START_LAPTIMER(2631);
	int retval = UTSC_SmPro_File_Set( arg1, arg2);
	STOP_LAPTIMER(2631);
	return retval;
}
int _UTSC_SmPro_Argument_Add( UTSC_SmPro arg1, char * arg2)
{
	MCI_LIST[2632] = "UTSC_SmPro_Argument_Add";
	START_LAPTIMER(2632);
	int retval = UTSC_SmPro_Argument_Add( arg1, arg2);
	STOP_LAPTIMER(2632);
	return retval;
}
int _UTSC_SmPro_Argument_Clear( UTSC_SmPro arg1)
{
	MCI_LIST[2633] = "UTSC_SmPro_Argument_Clear";
	START_LAPTIMER(2633);
	int retval = UTSC_SmPro_Argument_Clear( arg1);
	STOP_LAPTIMER(2633);
	return retval;
}
int _UTSC_SmPro_Place_Set( UTSC_SmPro arg1, char * arg2)
{
	MCI_LIST[2634] = "UTSC_SmPro_Place_Set";
	START_LAPTIMER(2634);
	int retval = UTSC_SmPro_Place_Set( arg1, arg2);
	STOP_LAPTIMER(2634);
	return retval;
}
int _UTSC_SmPro_StdoutStream_Set( UTSC_SmPro arg1, char * arg2)
{
	MCI_LIST[2635] = "UTSC_SmPro_StdoutStream_Set";
	START_LAPTIMER(2635);
	int retval = UTSC_SmPro_StdoutStream_Set( arg1, arg2);
	STOP_LAPTIMER(2635);
	return retval;
}
int _UTSC_SmPro_StderrStream_Set( UTSC_SmPro arg1, char * arg2)
{
	MCI_LIST[2636] = "UTSC_SmPro_StderrStream_Set";
	START_LAPTIMER(2636);
	int retval = UTSC_SmPro_StderrStream_Set( arg1, arg2);
	STOP_LAPTIMER(2636);
	return retval;
}
int _UTSC_Sm_RequestNotice( char * arg1, UTSC_SmNtf arg2, int arg3)
{
	MCI_LIST[2637] = "UTSC_Sm_RequestNotice";
	START_LAPTIMER(2637);
	int retval = UTSC_Sm_RequestNotice( arg1, arg2, arg3);
	STOP_LAPTIMER(2637);
	return retval;
}
int _UTSC_Sm_GetChannel( int * arg1)
{
	MCI_LIST[2638] = "UTSC_Sm_GetChannel";
	START_LAPTIMER(2638);
	int retval = UTSC_Sm_GetChannel( arg1);
	STOP_LAPTIMER(2638);
	return retval;
}
int _UTSC_Sm_CheckNotice( char ** arg1, UTSC_SmNtf * arg2)
{
	MCI_LIST[2639] = "UTSC_Sm_CheckNotice";
	START_LAPTIMER(2639);
	int retval = UTSC_Sm_CheckNotice( arg1, arg2);
	STOP_LAPTIMER(2639);
	return retval;
}
int _UTSC_SmNtf_Construct( UTSC_SmNtf * arg1)
{
	MCI_LIST[2640] = "UTSC_SmNtf_Construct";
	START_LAPTIMER(2640);
	int retval = UTSC_SmNtf_Construct( arg1);
	STOP_LAPTIMER(2640);
	return retval;
}
int _UTSC_SmNtf_Destruct( UTSC_SmNtf arg1)
{
	MCI_LIST[2641] = "UTSC_SmNtf_Destruct";
	START_LAPTIMER(2641);
	int retval = UTSC_SmNtf_Destruct( arg1);
	STOP_LAPTIMER(2641);
	return retval;
}
int _UTSC_SmNtf_SessionPgid_Set( UTSC_SmNtf arg1, char * arg2)
{
	MCI_LIST[2642] = "UTSC_SmNtf_SessionPgid_Set";
	START_LAPTIMER(2642);
	int retval = UTSC_SmNtf_SessionPgid_Set( arg1, arg2);
	STOP_LAPTIMER(2642);
	return retval;
}
int _UTSC_SmNtf_SessionPgid_Get( UTSC_SmNtf arg1, char ** arg2)
{
	MCI_LIST[2643] = "UTSC_SmNtf_SessionPgid_Get";
	START_LAPTIMER(2643);
	int retval = UTSC_SmNtf_SessionPgid_Get( arg1, arg2);
	STOP_LAPTIMER(2643);
	return retval;
}
int _UTSC_SmNtf_Place_Get( UTSC_SmNtf arg1, char ** arg2)
{
	MCI_LIST[2644] = "UTSC_SmNtf_Place_Get";
	START_LAPTIMER(2644);
	int retval = UTSC_SmNtf_Place_Get( arg1, arg2);
	STOP_LAPTIMER(2644);
	return retval;
}
int _UTSC_SmNtf_Transition_Get( UTSC_SmNtf arg1, char ** arg2)
{
	MCI_LIST[2645] = "UTSC_SmNtf_Transition_Get";
	START_LAPTIMER(2645);
	int retval = UTSC_SmNtf_Transition_Get( arg1, arg2);
	STOP_LAPTIMER(2645);
	return retval;
}
int _UTSC_Sm_LockSession( const char * arg1)
{
	MCI_LIST[2646] = "UTSC_Sm_LockSession";
	START_LAPTIMER(2646);
	int retval = UTSC_Sm_LockSession( arg1);
	STOP_LAPTIMER(2646);
	return retval;
}
int _UTSC_Sm_UnlockSession( const char * arg1)
{
	MCI_LIST[2647] = "UTSC_Sm_UnlockSession";
	START_LAPTIMER(2647);
	int retval = UTSC_Sm_UnlockSession( arg1);
	STOP_LAPTIMER(2647);
	return retval;
}
int _UTSC_Sm_GetLockState( const char * arg1, int * arg2)
{
	MCI_LIST[2648] = "UTSC_Sm_GetLockState";
	START_LAPTIMER(2648);
	int retval = UTSC_Sm_GetLockState( arg1, arg2);
	STOP_LAPTIMER(2648);
	return retval;
}
int _UTSC_Sm_GetLockTerminal( const char * arg1, char ** arg2)
{
	MCI_LIST[2649] = "UTSC_Sm_GetLockTerminal";
	START_LAPTIMER(2649);
	int retval = UTSC_Sm_GetLockTerminal( arg1, arg2);
	STOP_LAPTIMER(2649);
	return retval;
}
int _UTSC_Sm_GetLockTime( const char * arg1, time_t * arg2)
{
	MCI_LIST[2650] = "UTSC_Sm_GetLockTime";
	START_LAPTIMER(2650);
	int retval = UTSC_Sm_GetLockTime( arg1, arg2);
	STOP_LAPTIMER(2650);
	return retval;
}
int _UTSC_Sm_GetLockSession( const char * arg1, char ** arg2)
{
	MCI_LIST[2651] = "UTSC_Sm_GetLockSession";
	START_LAPTIMER(2651);
	int retval = UTSC_Sm_GetLockSession( arg1, arg2);
	STOP_LAPTIMER(2651);
	return retval;
}
int _UTSC_Sm_GetLastOperatedSessionId( char ** arg1)
{
	MCI_LIST[2652] = "UTSC_Sm_GetLastOperatedSessionId";
	START_LAPTIMER(2652);
	int retval = UTSC_Sm_GetLastOperatedSessionId( arg1);
	STOP_LAPTIMER(2652);
	return retval;
}
char * _UTSC_Sm_GetErrorMessage()
{
	MCI_LIST[2653] = "UTSC_Sm_GetErrorMessage";
	START_LAPTIMER(2653);
	char * retval = UTSC_Sm_GetErrorMessage();
	STOP_LAPTIMER(2653);
	return retval;
}
int _UTSC_TestUnit_GetTestUnit( int ** arg1, int * arg2)
{
	MCI_LIST[2654] = "UTSC_TestUnit_GetTestUnit";
	START_LAPTIMER(2654);
	int retval = UTSC_TestUnit_GetTestUnit( arg1, arg2);
	STOP_LAPTIMER(2654);
	return retval;
}
int _UTSC_TestUnit_GetPStn( int arg1, int ** arg2, int * arg3)
{
	MCI_LIST[2655] = "UTSC_TestUnit_GetPStn";
	START_LAPTIMER(2655);
	int retval = UTSC_TestUnit_GetPStn( arg1, arg2, arg3);
	STOP_LAPTIMER(2655);
	return retval;
}
int _UTSC_TestUnit_GetTestSite( int arg1, int ** arg2, int * arg3)
{
	MCI_LIST[2656] = "UTSC_TestUnit_GetTestSite";
	START_LAPTIMER(2656);
	int retval = UTSC_TestUnit_GetTestSite( arg1, arg2, arg3);
	STOP_LAPTIMER(2656);
	return retval;
}
int _UTSC_TestUnit_GetTestUnitByPStn( int arg1, int * arg2)
{
	MCI_LIST[2657] = "UTSC_TestUnit_GetTestUnitByPStn";
	START_LAPTIMER(2657);
	int retval = UTSC_TestUnit_GetTestUnitByPStn( arg1, arg2);
	STOP_LAPTIMER(2657);
	return retval;
}
int _UTSC_TestSite_GetHostName( int arg1, int arg2, char ** arg3)
{
	MCI_LIST[2658] = "UTSC_TestSite_GetHostName";
	START_LAPTIMER(2658);
	int retval = UTSC_TestSite_GetHostName( arg1, arg2, arg3);
	STOP_LAPTIMER(2658);
	return retval;
}
int _UTSC_TestSite_GetTbusNumber( int arg1, int arg2, int * arg3)
{
	MCI_LIST[2659] = "UTSC_TestSite_GetTbusNumber";
	START_LAPTIMER(2659);
	int retval = UTSC_TestSite_GetTbusNumber( arg1, arg2, arg3);
	STOP_LAPTIMER(2659);
	return retval;
}
int _UTSC_TestSite_GetRepairSite( int arg1, int arg2, int ** arg3, int * arg4)
{
	MCI_LIST[2660] = "UTSC_TestSite_GetRepairSite";
	START_LAPTIMER(2660);
	int retval = UTSC_TestSite_GetRepairSite( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2660);
	return retval;
}
int _UTSC_RepairSite_GetHostName( int arg1, int arg2, int arg3, char ** arg4)
{
	MCI_LIST[2661] = "UTSC_RepairSite_GetHostName";
	START_LAPTIMER(2661);
	int retval = UTSC_RepairSite_GetHostName( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2661);
	return retval;
}
int _UTSC_RepairSite_GetRcbNumber( int arg1, int arg2, int arg3, int ** arg4, int * arg5)
{
	MCI_LIST[2662] = "UTSC_RepairSite_GetRcbNumber";
	START_LAPTIMER(2662);
	int retval = UTSC_RepairSite_GetRcbNumber( arg1, arg2, arg3, arg4, arg5);
	STOP_LAPTIMER(2662);
	return retval;
}
int _UTSC_Em_Open( UTSC_Em * arg1, char * arg2)
{
	MCI_LIST[2663] = "UTSC_Em_Open";
	START_LAPTIMER(2663);
	int retval = UTSC_Em_Open( arg1, arg2);
	STOP_LAPTIMER(2663);
	return retval;
}
int _UTSC_Em_Close( UTSC_Em arg1)
{
	MCI_LIST[2664] = "UTSC_Em_Close";
	START_LAPTIMER(2664);
	int retval = UTSC_Em_Close( arg1);
	STOP_LAPTIMER(2664);
	return retval;
}
int _UTSC_Em_SendEvent( UTSC_Em arg1, char * arg2, void * arg3, UTSC_size_t arg4)
{
	MCI_LIST[2665] = "UTSC_Em_SendEvent";
	START_LAPTIMER(2665);
	int retval = UTSC_Em_SendEvent( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2665);
	return retval;
}
int _UTSC_Em_ReceiveEvent( UTSC_Em arg1, char ** arg2, void ** arg3, UTSC_size_t * arg4)
{
	MCI_LIST[2666] = "UTSC_Em_ReceiveEvent";
	START_LAPTIMER(2666);
	int retval = UTSC_Em_ReceiveEvent( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2666);
	return retval;
}
int _UTSC_Em_SetOption( UTSC_Em arg1, int arg2, char * arg3, int arg4)
{
	MCI_LIST[2667] = "UTSC_Em_SetOption";
	START_LAPTIMER(2667);
	int retval = UTSC_Em_SetOption( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2667);
	return retval;
}
int _UTSC_Em_GetOption( UTSC_Em arg1, int arg2, char * arg3, int * arg4)
{
	MCI_LIST[2668] = "UTSC_Em_GetOption";
	START_LAPTIMER(2668);
	int retval = UTSC_Em_GetOption( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2668);
	return retval;
}
int _UTSC_Em_GetChannel( UTSC_Em arg1, int * arg2)
{
	MCI_LIST[2669] = "UTSC_Em_GetChannel";
	START_LAPTIMER(2669);
	int retval = UTSC_Em_GetChannel( arg1, arg2);
	STOP_LAPTIMER(2669);
	return retval;
}
char * _UTSC_Em_GetErrorMessage()
{
	MCI_LIST[2670] = "UTSC_Em_GetErrorMessage";
	START_LAPTIMER(2670);
	char * retval = UTSC_Em_GetErrorMessage();
	STOP_LAPTIMER(2670);
	return retval;
}
int _UTSC_Pf_Open( UTSC_Pf * arg1, char * arg2)
{
	MCI_LIST[2671] = "UTSC_Pf_Open";
	START_LAPTIMER(2671);
	int retval = UTSC_Pf_Open( arg1, arg2);
	STOP_LAPTIMER(2671);
	return retval;
}
int _UTSC_Pf_Close( UTSC_Pf arg1)
{
	MCI_LIST[2672] = "UTSC_Pf_Close";
	START_LAPTIMER(2672);
	int retval = UTSC_Pf_Close( arg1);
	STOP_LAPTIMER(2672);
	return retval;
}
int _UTSC_Pf_Create( UTSC_Pf arg1, char * arg2, long arg3)
{
	MCI_LIST[2673] = "UTSC_Pf_Create";
	START_LAPTIMER(2673);
	int retval = UTSC_Pf_Create( arg1, arg2, arg3);
	STOP_LAPTIMER(2673);
	return retval;
}
int _UTSC_Pf_Delete( UTSC_Pf arg1, char * arg2)
{
	MCI_LIST[2674] = "UTSC_Pf_Delete";
	START_LAPTIMER(2674);
	int retval = UTSC_Pf_Delete( arg1, arg2);
	STOP_LAPTIMER(2674);
	return retval;
}
int _UTSC_Pf_WriteData( UTSC_Pf arg1, char * arg2, void * arg3, UTSC_size_t arg4)
{
	MCI_LIST[2675] = "UTSC_Pf_WriteData";
	START_LAPTIMER(2675);
	int retval = UTSC_Pf_WriteData( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2675);
	return retval;
}
int _UTSC_Pf_ReadData( UTSC_Pf arg1, char * arg2, void ** arg3, UTSC_size_t * arg4)
{
	MCI_LIST[2676] = "UTSC_Pf_ReadData";
	START_LAPTIMER(2676);
	int retval = UTSC_Pf_ReadData( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2676);
	return retval;
}
int _UTSC_Pf_SetOption( UTSC_Pf arg1, int arg2, char * arg3, int arg4)
{
	MCI_LIST[2677] = "UTSC_Pf_SetOption";
	START_LAPTIMER(2677);
	int retval = UTSC_Pf_SetOption( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2677);
	return retval;
}
int _UTSC_Pf_GetOption( UTSC_Pf arg1, int arg2, char * arg3, int * arg4)
{
	MCI_LIST[2678] = "UTSC_Pf_GetOption";
	START_LAPTIMER(2678);
	int retval = UTSC_Pf_GetOption( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2678);
	return retval;
}
int _UTSC_Pf_Find( UTSC_Pf arg1, int arg2, void * arg3, UTSC_NameSet * arg4)
{
	MCI_LIST[2679] = "UTSC_Pf_Find";
	START_LAPTIMER(2679);
	int retval = UTSC_Pf_Find( arg1, arg2, arg3, arg4);
	STOP_LAPTIMER(2679);
	return retval;
}
char * _UTSC_Pf_GetErrorMessage()
{
	MCI_LIST[2680] = "UTSC_Pf_GetErrorMessage";
	START_LAPTIMER(2680);
	char * retval = UTSC_Pf_GetErrorMessage();
	STOP_LAPTIMER(2680);
	return retval;
}
int _UTSC_NameSet_Construct( UTSC_NameSet * arg1)
{
	MCI_LIST[2681] = "UTSC_NameSet_Construct";
	START_LAPTIMER(2681);
	int retval = UTSC_NameSet_Construct( arg1);
	STOP_LAPTIMER(2681);
	return retval;
}
int _UTSC_NameSet_Destruct( UTSC_NameSet arg1)
{
	MCI_LIST[2682] = "UTSC_NameSet_Destruct";
	START_LAPTIMER(2682);
	int retval = UTSC_NameSet_Destruct( arg1);
	STOP_LAPTIMER(2682);
	return retval;
}
int _UTSC_NameSet_GetCount( UTSC_NameSet arg1, int * arg2)
{
	MCI_LIST[2683] = "UTSC_NameSet_GetCount";
	START_LAPTIMER(2683);
	int retval = UTSC_NameSet_GetCount( arg1, arg2);
	STOP_LAPTIMER(2683);
	return retval;
}
int _UTSC_NameSet_Add( UTSC_NameSet arg1, int arg2, char * arg3)
{
	MCI_LIST[2684] = "UTSC_NameSet_Add";
	START_LAPTIMER(2684);
	int retval = UTSC_NameSet_Add( arg1, arg2, arg3);
	STOP_LAPTIMER(2684);
	return retval;
}
int _UTSC_NameSet_Delete( UTSC_NameSet arg1, int arg2)
{
	MCI_LIST[2685] = "UTSC_NameSet_Delete";
	START_LAPTIMER(2685);
	int retval = UTSC_NameSet_Delete( arg1, arg2);
	STOP_LAPTIMER(2685);
	return retval;
}
int _UTSC_NameSet_Clear( UTSC_NameSet arg1)
{
	MCI_LIST[2686] = "UTSC_NameSet_Clear";
	START_LAPTIMER(2686);
	int retval = UTSC_NameSet_Clear( arg1);
	STOP_LAPTIMER(2686);
	return retval;
}
int _UTSC_NameSet_Includes( UTSC_NameSet arg1, char * arg2, int * arg3)
{
	MCI_LIST[2687] = "UTSC_NameSet_Includes";
	START_LAPTIMER(2687);
	int retval = UTSC_NameSet_Includes( arg1, arg2, arg3);
	STOP_LAPTIMER(2687);
	return retval;
}
int _UTSC_NameSet_Get( UTSC_NameSet arg1, int arg2, char ** arg3)
{
	MCI_LIST[2688] = "UTSC_NameSet_Get";
	START_LAPTIMER(2688);
	int retval = UTSC_NameSet_Get( arg1, arg2, arg3);
	STOP_LAPTIMER(2688);
	return retval;
}
int _UTSC_Flow_TestSiteSync_Wait( char * arg1, int * arg2)
{
	MCI_LIST[2689] = "UTSC_Flow_TestSiteSync_Wait";
	START_LAPTIMER(2689);
	int retval = UTSC_Flow_TestSiteSync_Wait( arg1, arg2);
	STOP_LAPTIMER(2689);
	return retval;
}
void _UTSC_Flow_ExitOnError( int arg1)
{
	MCI_LIST[2690] = "UTSC_Flow_ExitOnError";
	START_LAPTIMER(2690);
	UTSC_Flow_ExitOnError( arg1);
	STOP_LAPTIMER(2690);
}
char * _UTSC_Flow_GetErrorMessage()
{
	MCI_LIST[2691] = "UTSC_Flow_GetErrorMessage";
	START_LAPTIMER(2691);
	char * retval = UTSC_Flow_GetErrorMessage();
	STOP_LAPTIMER(2691);
	return retval;
}
int _UTSC_TesterCondition_ReadInfo( int arg1, double ** arg2, int * arg3)
{
	MCI_LIST[2692] = "UTSC_TesterCondition_ReadInfo";
	START_LAPTIMER(2692);
	int retval = UTSC_TesterCondition_ReadInfo( arg1, arg2, arg3);
	STOP_LAPTIMER(2692);
	return retval;
}
void _UTSC_TesterCondition_ExitOnError( int arg1)
{
	MCI_LIST[2693] = "UTSC_TesterCondition_ExitOnError";
	START_LAPTIMER(2693);
	UTSC_TesterCondition_ExitOnError( arg1);
	STOP_LAPTIMER(2693);
}
char * _UTSC_TesterCondition_GetErrorMessage()
{
	MCI_LIST[2694] = "UTSC_TesterCondition_GetErrorMessage";
	START_LAPTIMER(2694);
	char * retval = UTSC_TesterCondition_GetErrorMessage();
	STOP_LAPTIMER(2694);
	return retval;
}
#ifdef __cplusplus
}
#endif


