
// FutureSuite T5835 1.04
#ifndef _MCITIME_H_
#define _MCITIME_H_

#include <test.h>
#include <UTSC.h>
#include <UTHN.h>

#ifdef __cplusplus
extern "C" {
#endif

#define T_MAX (2695)
#define NUM_MAX (100)

extern char *MCI_LIST[T_MAX];
extern double ACCUMULATED_TIME[T_MAX];
extern double ACCUMULATED_INDIVIDUAL_TIME[T_MAX][NUM_MAX];
extern int    CALLS[T_MAX];

typedef struct pinstr{
	UT_PIN pin;
	long pb_pin_number;
	long pb_pin_child;
} pinstr;	//for cell1_utility(libcell1.so)

extern void _UTL_Test(TestHandle h, char *tname);
#define UTL_Test _UTL_Test

extern int _UTL_Xtest(TestHandle h, char *tname);
#define UTL_Xtest _UTL_Xtest

extern void _UTL_InitTest(int argc, char **argv);
#define UTL_InitTest _UTL_InitTest
extern void _UTL_CreatePinList ( char * );
#define UTL_CreatePinList _UTL_CreatePinList
extern void _UTL_SetPinType ( char *, RadioButton );
#define UTL_SetPinType _UTL_SetPinType
extern void _UTL_AddPinNumber ( char *, RadioButton );
#define UTL_AddPinNumber _UTL_AddPinNumber
extern void _UTL_ClearPinNumber ( char * );
#define UTL_ClearPinNumber _UTL_ClearPinNumber
extern void _UTL_AppendPinList ( char *, char * );
#define UTL_AppendPinList _UTL_AppendPinList
TestHandle _UTL_GetTestHandle(void);
#define UTL_GetTestHandle _UTL_GetTestHandle
void _UTL_SetTestAction(TestHandle, void (*)());
#define UTL_SetTestAction _UTL_SetTestAction
void _UTL_SetXtestAction(TestHandle, int (*)());
#define UTL_SetXtestAction _UTL_SetXtestAction
void _UTL_SetTestArg(TestHandle, void *);
#define UTL_SetTestArg _UTL_SetTestArg
extern void _UTL_SetCategory ( UT_DUT , RadioButton );
#define UTL_SetCategory _UTL_SetCategory
extern void _UTL_ResetCategory ( UT_DUT , RadioButton );
#define UTL_ResetCategory _UTL_ResetCategory
extern CheckButton _UTL_ReadCategory ( UT_DUT , RadioButton );
#define UTL_ReadCategory _UTL_ReadCategory
extern CategoryCursor _UTL_GetCategoryCursor( UT_DUT );
#define UTL_GetCategoryCursor _UTL_GetCategoryCursor
extern RadioButton _UTL_NextCategory ( CategoryCursor );
#define UTL_NextCategory _UTL_NextCategory
extern void _UTL_SendSort ( UT_DUT , RadioButton );
#define UTL_SendSort _UTL_SendSort
extern RadioButton _UTL_ReadSort ( UT_DUT );
#define UTL_ReadSort _UTL_ReadSort
extern void _UTL_SendSymbol( char *, char * );
#define UTL_SendSymbol _UTL_SendSymbol
extern char *_UTL_ReadSymbol( char * );
#define UTL_ReadSymbol _UTL_ReadSymbol
extern void _UTL_SendSystemValue( char *, char * );
#define UTL_SendSystemValue _UTL_SendSystemValue
extern char *_UTL_ReadSystemValue( char * );
#define UTL_ReadSystemValue _UTL_ReadSystemValue
VariableHandle _UTL_GetVariableHandle(void);
#define UTL_GetVariableHandle _UTL_GetVariableHandle
void _UTL_SetVariableStation(VariableHandle, int);
#define UTL_SetVariableStation _UTL_SetVariableStation
void _UTL_SetVariableDataChar(VariableHandle, char *);
#define UTL_SetVariableDataChar _UTL_SetVariableDataChar
void _UTL_SetVariableDataCheckButton(VariableHandle, CheckButton);
#define UTL_SetVariableDataCheckButton _UTL_SetVariableDataCheckButton
void _UTL_SetVariableDataSlider(VariableHandle, Slider);
#define UTL_SetVariableDataSlider _UTL_SetVariableDataSlider
void _UTL_SetVariableDataUSlider(VariableHandle, USlider);
#define UTL_SetVariableDataUSlider _UTL_SetVariableDataUSlider
void _UTL_SendVariable(VariableHandle, char *);
#define UTL_SendVariable _UTL_SendVariable
void _UTL_UpdateVariable(VariableHandle, char *);
#define UTL_UpdateVariable _UTL_UpdateVariable
int _UTL_GetVariableStation(VariableHandle, int *);
#define UTL_GetVariableStation _UTL_GetVariableStation
int _UTL_GetVariableDataChar(VariableHandle, char **);
#define UTL_GetVariableDataChar _UTL_GetVariableDataChar
int _UTL_GetVariableDataCheckButton(VariableHandle, CheckButton *);
#define UTL_GetVariableDataCheckButton _UTL_GetVariableDataCheckButton
int _UTL_GetVariableDataSlider(VariableHandle, Slider *);
#define UTL_GetVariableDataSlider _UTL_GetVariableDataSlider
int _UTL_GetVariableDataUSlider(VariableHandle, USlider *);
#define UTL_GetVariableDataUSlider _UTL_GetVariableDataUSlider
extern PinCursor _UTL_GetPinCursor(char *);
#define UTL_GetPinCursor _UTL_GetPinCursor
extern UT_PIN _UTL_NextPin(PinCursor);
#define UTL_NextPin _UTL_NextPin
extern DutCursor _UTL_GetDutCursor ( RadioButton );
#define UTL_GetDutCursor _UTL_GetDutCursor
extern UT_DUT _UTL_NextDut ( DutCursor );
#define UTL_NextDut _UTL_NextDut
extern USlider _UTL_GetDutCount ( RadioButton );
#define UTL_GetDutCount _UTL_GetDutCount
extern int _UTL_ConvertDutNumber ( RadioButton , UT_DUT , RadioButton , int *, UT_DUT * );
#define UTL_ConvertDutNumber _UTL_ConvertDutNumber
extern void _UTL_ConfirmSystemDut ( RadioButton );
#define UTL_ConfirmSystemDut _UTL_ConfirmSystemDut
extern RadioButton _UTL_NextSignal ( SignalCursor );
#define UTL_NextSignal _UTL_NextSignal
extern void _UTL_StartTimer(RadioButton);
#define UTL_StartTimer _UTL_StartTimer
extern DSlider _UTL_ReadTimer(CheckButton *);
#define UTL_ReadTimer _UTL_ReadTimer
extern void _UTL_WaitTime(DSlider);
#define UTL_WaitTime _UTL_WaitTime
extern void _UTL_Stop(void);
#define UTL_Stop _UTL_Stop
extern RadioButton _UTL_ReadSiteNumber ( void );
#define UTL_ReadSiteNumber _UTL_ReadSiteNumber
extern void _UTL_SendSocketConditionByFile( char * );
#define UTL_SendSocketConditionByFile _UTL_SendSocketConditionByFile
extern void _UTL_SetRejectionByDutBit(USlider *, USlider, CheckButton);
#define UTL_SetRejectionByDutBit _UTL_SetRejectionByDutBit
extern void _UTL_SetResetExclusionByDutBit(USlider *Dutbit, USlider, CheckButton, CheckButton);
#define UTL_SetResetExclusionByDutBit _UTL_SetResetExclusionByDutBit
extern CheckButton _UTL_SetRejection(UT_DUT, CheckButton);
#define UTL_SetRejection _UTL_SetRejection
extern CheckButton _UTL_SetExclusion(UT_DUT, CheckButton, CheckButton);
#define UTL_SetExclusion _UTL_SetExclusion
extern CheckButton _UTL_ResetExclusion(UT_DUT);
#define UTL_ResetExclusion _UTL_ResetExclusion
extern RejectionHandle _UTL_GetRejectionHandle(void);
#define UTL_GetRejectionHandle _UTL_GetRejectionHandle
extern void _UTL_ClearRejectionDut(RejectionHandle);
#define UTL_ClearRejectionDut _UTL_ClearRejectionDut
extern void _UTL_AddRejectionDut(RejectionHandle, UT_DUT);
#define UTL_AddRejectionDut _UTL_AddRejectionDut
extern void _UTL_SetRejectionIgnoreWet(RejectionHandle, CheckButton);
#define UTL_SetRejectionIgnoreWet _UTL_SetRejectionIgnoreWet
extern void _UTL_SendRejection(RejectionHandle);
#define UTL_SendRejection _UTL_SendRejection
extern int _UTL_GetRejectionIgnoreWet( RejectionHandle, CheckButton * );
#define UTL_GetRejectionIgnoreWet _UTL_GetRejectionIgnoreWet
extern ExclusionHandle _UTL_GetExclusionHandle(void);
#define UTL_GetExclusionHandle _UTL_GetExclusionHandle
extern void _UTL_ClearExclusionDut(ExclusionHandle);
#define UTL_ClearExclusionDut _UTL_ClearExclusionDut
extern void _UTL_AddExclusionDut(ExclusionHandle, UT_DUT);
#define UTL_AddExclusionDut _UTL_AddExclusionDut
extern void _UTL_SetExclusionIgnoreWet(ExclusionHandle, CheckButton);
#define UTL_SetExclusionIgnoreWet _UTL_SetExclusionIgnoreWet
extern void _UTL_SetExclusionMask(ExclusionHandle, CheckButton);
#define UTL_SetExclusionMask _UTL_SetExclusionMask
extern void _UTL_SetExclusionSetOrReset(ExclusionHandle, CheckButton);
#define UTL_SetExclusionSetOrReset _UTL_SetExclusionSetOrReset
extern void _UTL_SendExclusion(ExclusionHandle);
#define UTL_SendExclusion _UTL_SendExclusion
extern int _UTL_GetExclusionIgnoreWet( ExclusionHandle, CheckButton * );
#define UTL_GetExclusionIgnoreWet _UTL_GetExclusionIgnoreWet
extern int _UTL_GetExclusionMask( ExclusionHandle, CheckButton * );
#define UTL_GetExclusionMask _UTL_GetExclusionMask
extern int _UTL_GetExclusionSetOrReset( ExclusionHandle, CheckButton * );
#define UTL_GetExclusionSetOrReset _UTL_GetExclusionSetOrReset
extern Slider _UTL_ReadDutXLocation( UT_DUT );
#define UTL_ReadDutXLocation _UTL_ReadDutXLocation
extern Slider _UTL_ReadDutYLocation( UT_DUT );
#define UTL_ReadDutYLocation _UTL_ReadDutYLocation
extern void _UTL_DeleteHandle( int );
#define UTL_DeleteHandle _UTL_DeleteHandle
extern void _UTL_DeleteCursor( int );
#define UTL_DeleteCursor _UTL_DeleteCursor
extern void _UTL_SendStrToWFMP ( UT_DUT, char *, char * );
#define UTL_SendStrToWFMP _UTL_SendStrToWFMP
extern RadioButton _UTL_ReadStationNumber( void );
#define UTL_ReadStationNumber _UTL_ReadStationNumber
extern CheckButton _UTL_ReadFirstFlag(void);
#define UTL_ReadFirstFlag _UTL_ReadFirstFlag
extern PbidHandle _UTL_GetPbidHandle ( void );
#define UTL_GetPbidHandle _UTL_GetPbidHandle
extern void _UTL_SetPbidStationNumber ( PbidHandle, RadioButton );
#define UTL_SetPbidStationNumber _UTL_SetPbidStationNumber
extern int _UTL_GetPbidStationNumber ( PbidHandle, RadioButton * );
#define UTL_GetPbidStationNumber _UTL_GetPbidStationNumber
extern void _UTL_SetPbidMbNumber ( PbidHandle, RadioButton );
#define UTL_SetPbidMbNumber _UTL_SetPbidMbNumber
extern int _UTL_GetPbidMbNumber ( PbidHandle, RadioButton * );
#define UTL_GetPbidMbNumber _UTL_GetPbidMbNumber
extern void _UTL_SetPbidPbNumber ( PbidHandle, RadioButton );
#define UTL_SetPbidPbNumber _UTL_SetPbidPbNumber
extern int _UTL_GetPbidPbNumber ( PbidHandle, RadioButton * );
#define UTL_GetPbidPbNumber _UTL_GetPbidPbNumber
extern USlider _UTL_ReadPbid ( PbidHandle );
#define UTL_ReadPbid _UTL_ReadPbid
extern PbTypeHandle _UTL_GetPbTypeHandle ( void );
#define UTL_GetPbTypeHandle _UTL_GetPbTypeHandle
extern void _UTL_SetPbTypeStationNumber( PbTypeHandle, RadioButton );
#define UTL_SetPbTypeStationNumber _UTL_SetPbTypeStationNumber
extern int _UTL_GetPbTypeStationNumber( PbTypeHandle, RadioButton * );
#define UTL_GetPbTypeStationNumber _UTL_GetPbTypeStationNumber
extern void _UTL_SetPbTypeMbNumber ( PbTypeHandle, RadioButton );
#define UTL_SetPbTypeMbNumber _UTL_SetPbTypeMbNumber
extern int _UTL_GetPbTypeMbNumber( PbTypeHandle, RadioButton * );
#define UTL_GetPbTypeMbNumber _UTL_GetPbTypeMbNumber
extern void _UTL_SetPbTypePbNumber ( PbTypeHandle, RadioButton );
#define UTL_SetPbTypePbNumber _UTL_SetPbTypePbNumber
extern int _UTL_GetPbTypePbNumber( PbTypeHandle, RadioButton * );
#define UTL_GetPbTypePbNumber _UTL_GetPbTypePbNumber
extern USlider _UTL_ReadPbType ( PbTypeHandle );
#define UTL_ReadPbType _UTL_ReadPbType
extern HifixTypeHandle _UTL_GetHifixTypeHandle ( void );
#define UTL_GetHifixTypeHandle _UTL_GetHifixTypeHandle
extern void _UTL_SetHifixTypeStationNumber( HifixTypeHandle, RadioButton );
#define UTL_SetHifixTypeStationNumber _UTL_SetHifixTypeStationNumber
extern int _UTL_GetHifixTypeStationNumber( HifixTypeHandle, RadioButton * );
#define UTL_GetHifixTypeStationNumber _UTL_GetHifixTypeStationNumber
extern int _UTL_GetHifixType( HifixTypeHandle, RadioButton * );
#define UTL_GetHifixType _UTL_GetHifixType
extern void _UTL_UpdateHifixType( HifixTypeHandle );
#define UTL_UpdateHifixType _UTL_UpdateHifixType
extern USlider _UTL_ReadDutSampleNumber(void);
#define UTL_ReadDutSampleNumber _UTL_ReadDutSampleNumber
extern PinMaskHandle _UTL_GetPinMaskHandle( void );
#define UTL_GetPinMaskHandle _UTL_GetPinMaskHandle
extern void _UTL_SetPinMaskKind( PinMaskHandle , RadioButton );
#define UTL_SetPinMaskKind _UTL_SetPinMaskKind
extern void _UTL_SetPinMask( PinMaskHandle , CheckButton );
#define UTL_SetPinMask _UTL_SetPinMask
extern void _UTL_AddPinMaskDut( PinMaskHandle , UT_DUT );
#define UTL_AddPinMaskDut _UTL_AddPinMaskDut
extern void _UTL_ClearPinMaskDut( PinMaskHandle );
#define UTL_ClearPinMaskDut _UTL_ClearPinMaskDut
extern void _UTL_SendPinMask( PinMaskHandle , char * );
#define UTL_SendPinMask _UTL_SendPinMask
extern void _UTL_RuntimeError(UT_ErrorInfo);
#define UTL_RuntimeError _UTL_RuntimeError
extern void _UTL_SetNoRejectionVs(RadioButton);
#define UTL_SetNoRejectionVs _UTL_SetNoRejectionVs
extern void _UTL_ResetNoRejectionVs(RadioButton);
#define UTL_ResetNoRejectionVs _UTL_ResetNoRejectionVs
extern IlModeHandle _UTL_GetIlModeHandle (void);
#define UTL_GetIlModeHandle _UTL_GetIlModeHandle
extern void _UTL_SetIlMode (IlModeHandle hid, RadioButton mode);
#define UTL_SetIlMode _UTL_SetIlMode
extern int _UTL_GetIlMode( IlModeHandle hid, RadioButton *mode );
#define UTL_GetIlMode _UTL_GetIlMode
extern void _UTL_SendIlMode (IlModeHandle hid);
#define UTL_SendIlMode _UTL_SendIlMode
extern void _UTL_UpdateIlMode (IlModeHandle hid);
#define UTL_UpdateIlMode _UTL_UpdateIlMode
extern ComparisonModeHandle _UTL_GetComparisonModeHandle (void);
#define UTL_GetComparisonModeHandle _UTL_GetComparisonModeHandle
extern void _UTL_SetComparisonMode (ComparisonModeHandle hid, RadioButton mode);
#define UTL_SetComparisonMode _UTL_SetComparisonMode
extern int _UTL_GetComparisonMode ( ComparisonModeHandle h, RadioButton *val );
#define UTL_GetComparisonMode _UTL_GetComparisonMode
extern void _UTL_SendComparisonMode (ComparisonModeHandle hid);
#define UTL_SendComparisonMode _UTL_SendComparisonMode
extern void _UTL_UpdateComparisonMode (ComparisonModeHandle hid);
#define UTL_UpdateComparisonMode _UTL_UpdateComparisonMode
extern char *_UTL_ReadProgramName(void);
#define UTL_ReadProgramName _UTL_ReadProgramName
extern char *_UTL_ReadSocketProgramName(void);
#define UTL_ReadSocketProgramName _UTL_ReadSocketProgramName
extern char *_UTL_ReadTestName(void);
#define UTL_ReadTestName _UTL_ReadTestName
extern TargetSwitchHandle _UTL_GetTargetSwitchHandle ( void );
#define UTL_GetTargetSwitchHandle _UTL_GetTargetSwitchHandle
extern void _UTL_SetTargetSwitchIOShareCount ( TargetSwitchHandle, USlider );
#define UTL_SetTargetSwitchIOShareCount _UTL_SetTargetSwitchIOShareCount
extern int _UTL_GetTargetSwitchIOShareCount ( TargetSwitchHandle, USlider * );
#define UTL_GetTargetSwitchIOShareCount _UTL_GetTargetSwitchIOShareCount
extern void _UTL_SetTargetSwitchIOShareSignal ( TargetSwitchHandle, UT_DUT, RadioButton );
#define UTL_SetTargetSwitchIOShareSignal _UTL_SetTargetSwitchIOShareSignal
extern int _UTL_GetTargetSwitchIOShareSignal ( TargetSwitchHandle, UT_DUT, RadioButton * );
#define UTL_GetTargetSwitchIOShareSignal _UTL_GetTargetSwitchIOShareSignal
extern void _UTL_SetTargetSwitchMultiBankCount ( TargetSwitchHandle, USlider );
#define UTL_SetTargetSwitchMultiBankCount _UTL_SetTargetSwitchMultiBankCount
extern int _UTL_GetTargetSwitchMultiBankCount ( TargetSwitchHandle, USlider * );
#define UTL_GetTargetSwitchMultiBankCount _UTL_GetTargetSwitchMultiBankCount
extern void _UTL_SetTargetSwitchMultiBankSignal( TargetSwitchHandle, RadioButton, RadioButton );
#define UTL_SetTargetSwitchMultiBankSignal _UTL_SetTargetSwitchMultiBankSignal
extern int _UTL_GetTargetSwitchMultiBankSignal( TargetSwitchHandle, RadioButton, RadioButton * );
#define UTL_GetTargetSwitchMultiBankSignal _UTL_GetTargetSwitchMultiBankSignal
extern void _UTL_SendTargetSwitch ( TargetSwitchHandle );
#define UTL_SendTargetSwitch _UTL_SendTargetSwitch
extern void _UTL_UpdateTargetSwitch ( TargetSwitchHandle );
#define UTL_UpdateTargetSwitch _UTL_UpdateTargetSwitch
extern DutGroupHandle _UTL_GetDutGroupHandle(void);
#define UTL_GetDutGroupHandle _UTL_GetDutGroupHandle
extern void _UTL_ClearDutGroupTargetDut(DutGroupHandle);
#define UTL_ClearDutGroupTargetDut _UTL_ClearDutGroupTargetDut
extern void _UTL_AddDutGroupTargetDut(DutGroupHandle, UT_DUT, CheckButton);
#define UTL_AddDutGroupTargetDut _UTL_AddDutGroupTargetDut
extern void _UTL_SendDutGroup(DutGroupHandle, RadioButton);
#define UTL_SendDutGroup _UTL_SendDutGroup
extern VsMaskHandle _UTL_GetVsMaskHandle( void );
#define UTL_GetVsMaskHandle _UTL_GetVsMaskHandle
extern void _UTL_AddVsMaskDutVsMask( VsMaskHandle , UT_DUT , RadioButton , CheckButton );
#define UTL_AddVsMaskDutVsMask _UTL_AddVsMaskDutVsMask
extern void _UTL_ClearVsMaskDutVsMask( VsMaskHandle );
#define UTL_ClearVsMaskDutVsMask _UTL_ClearVsMaskDutVsMask
extern void _UTL_SendVsMask( VsMaskHandle );
#define UTL_SendVsMask _UTL_SendVsMask
extern void _UTL_ReadDutBit( RadioButton, USlider *, USlider );
#define UTL_ReadDutBit _UTL_ReadDutBit
extern void _UTL_SetDutBit ( RadioButton, USlider *, USlider );
#define UTL_SetDutBit _UTL_SetDutBit
extern PinHandle _UTL_GetPinHandle(void);
#define UTL_GetPinHandle _UTL_GetPinHandle
extern void _UTL_InitializePinHandle(PinHandle);
#define UTL_InitializePinHandle _UTL_InitializePinHandle
extern void _UTL_SetPinSendMode(PinHandle, RadioButton);
#define UTL_SetPinSendMode _UTL_SetPinSendMode
extern void _UTL_AddPinTargetDut(PinHandle, UT_DUT);
#define UTL_AddPinTargetDut _UTL_AddPinTargetDut
extern void _UTL_ClearPinTargetDut(PinHandle);
#define UTL_ClearPinTargetDut _UTL_ClearPinTargetDut
extern void _UTL_SetPinTargetDutCondition(PinHandle, RadioButton);
#define UTL_SetPinTargetDutCondition _UTL_SetPinTargetDutCondition
extern void _UTL_SetPinViNumber(PinHandle, RadioButton);
#define UTL_SetPinViNumber _UTL_SetPinViNumber
extern void _UTL_SetPinVihhNumber(PinHandle, RadioButton);
#define UTL_SetPinVihhNumber _UTL_SetPinVihhNumber
extern void _UTL_SetPinVihhMutSignal(PinHandle, CheckButton);
#define UTL_SetPinVihhMutSignal _UTL_SetPinVihhMutSignal
extern void _UTL_SetPinDrWaveform(PinHandle, RadioButton);
#define UTL_SetPinDrWaveform _UTL_SetPinDrWaveform
extern void _UTL_SetPinDrClock(PinHandle, RadioButton, RadioButton);
#define UTL_SetPinDrClock _UTL_SetPinDrClock
extern void _UTL_SetPinInit(PinHandle, RadioButton);
#define UTL_SetPinInit _UTL_SetPinInit
extern void _UTL_SetPinHvDr(PinHandle, CheckButton);
#define UTL_SetPinHvDr _UTL_SetPinHvDr
extern void _UTL_SetPinHvLvDr(PinHandle, CheckButton);
#define UTL_SetPinHvLvDr _UTL_SetPinHvLvDr
extern void _UTL_SetPinDbmPinPattern(PinHandle, CheckButton);
#define UTL_SetPinDbmPinPattern _UTL_SetPinDbmPinPattern
extern void _UTL_SetPinDrzPulseWidth(PinHandle, RadioButton);
#define UTL_SetPinDrzPulseWidth _UTL_SetPinDrzPulseWidth
extern void _UTL_SetPinDreOffTermMode(PinHandle, RadioButton);
#define UTL_SetPinDreOffTermMode _UTL_SetPinDreOffTermMode
extern void _UTL_SetPinDrPort(PinHandle, RadioButton);
#define UTL_SetPinDrPort _UTL_SetPinDrPort
extern void _UTL_AddPinWfs(PinHandle, RadioButton, RadioButton);
#define UTL_AddPinWfs _UTL_AddPinWfs
extern void _UTL_ClearPinWfs(PinHandle);
#define UTL_ClearPinWfs _UTL_ClearPinWfs
extern void _UTL_SetPinVoNumber(PinHandle, RadioButton);
#define UTL_SetPinVoNumber _UTL_SetPinVoNumber
extern void _UTL_SetPinVodNumber(PinHandle, RadioButton);
#define UTL_SetPinVodNumber _UTL_SetPinVodNumber
extern void _UTL_AddPinStrbCpeNumber(PinHandle, RadioButton, RadioButton);
#define UTL_AddPinStrbCpeNumber _UTL_AddPinStrbCpeNumber
extern void _UTL_ClearPinStrbCpeNumber(PinHandle);
#define UTL_ClearPinStrbCpeNumber _UTL_ClearPinStrbCpeNumber
extern void _UTL_AddPinWstrbCpeNumber(PinHandle, RadioButton, RadioButton);
#define UTL_AddPinWstrbCpeNumber _UTL_AddPinWstrbCpeNumber
extern void _UTL_ClearPinWstrbCpeNumber(PinHandle);
#define UTL_ClearPinWstrbCpeNumber _UTL_ClearPinWstrbCpeNumber
extern void _UTL_SetPinEinv(PinHandle, CheckButton);
#define UTL_SetPinEinv _UTL_SetPinEinv
extern void _UTL_SetPinMatchMode(PinHandle, RadioButton);
#define UTL_SetPinMatchMode _UTL_SetPinMatchMode
extern void _UTL_SetPinMatchGroup(PinHandle, RadioButton, CheckButton);
#define UTL_SetPinMatchGroup _UTL_SetPinMatchGroup
extern void _UTL_AddPinHz(PinHandle, RadioButton);
#define UTL_AddPinHz _UTL_AddPinHz
extern void _UTL_ClearPinHz(PinHandle);
#define UTL_ClearPinHz _UTL_ClearPinHz
extern void _UTL_AddPinRhz(PinHandle, RadioButton, RadioButton);
#define UTL_AddPinRhz _UTL_AddPinRhz
extern void _UTL_ClearPinRhz(PinHandle);
#define UTL_ClearPinRhz _UTL_ClearPinRhz
extern void _UTL_AddPinExpStrbNumber(PinHandle, RadioButton, RadioButton);
#define UTL_AddPinExpStrbNumber _UTL_AddPinExpStrbNumber
extern void _UTL_ClearPinExpStrbNumber(PinHandle);
#define UTL_ClearPinExpStrbNumber _UTL_ClearPinExpStrbNumber
extern void _UTL_AddPinExpWstrbNumber(PinHandle, RadioButton, RadioButton);
#define UTL_AddPinExpWstrbNumber _UTL_AddPinExpWstrbNumber
extern void _UTL_ClearPinExpWstrbNumber(PinHandle);
#define UTL_ClearPinExpWstrbNumber _UTL_ClearPinExpWstrbNumber
extern void _UTL_AddPinEinvStrbNumber(PinHandle, RadioButton);
#define UTL_AddPinEinvStrbNumber _UTL_AddPinEinvStrbNumber
extern void _UTL_ClearPinEinvStrbNumber(PinHandle);
#define UTL_ClearPinEinvStrbNumber _UTL_ClearPinEinvStrbNumber
extern void _UTL_AddPinEinvWstrbNumber(PinHandle, RadioButton);
#define UTL_AddPinEinvWstrbNumber _UTL_AddPinEinvWstrbNumber
extern void _UTL_ClearPinEinvWstrbNumber(PinHandle);
#define UTL_ClearPinEinvWstrbNumber _UTL_ClearPinEinvWstrbNumber
extern void _UTL_AddPinStrbChannel(PinHandle, RadioButton, RadioButton);
#define UTL_AddPinStrbChannel _UTL_AddPinStrbChannel
extern void _UTL_ClearPinStrbChannel(PinHandle);
#define UTL_ClearPinStrbChannel _UTL_ClearPinStrbChannel
extern void _UTL_AddPinStrbBank(PinHandle, RadioButton, RadioButton);
#define UTL_AddPinStrbBank _UTL_AddPinStrbBank
extern void _UTL_ClearPinStrbBank(PinHandle);
#define UTL_ClearPinStrbBank _UTL_ClearPinStrbBank
extern void _UTL_AddPinStrbCpeMode(PinHandle, RadioButton, RadioButton);
#define UTL_AddPinStrbCpeMode _UTL_AddPinStrbCpeMode
extern void _UTL_ClearPinStrbCpeMode(PinHandle);
#define UTL_ClearPinStrbCpeMode _UTL_ClearPinStrbCpeMode
extern void _UTL_AddPinWstrbCpeMode(PinHandle, RadioButton, RadioButton);
#define UTL_AddPinWstrbCpeMode _UTL_AddPinWstrbCpeMode
extern void _UTL_ClearPinWstrbCpeMode(PinHandle);
#define UTL_ClearPinWstrbCpeMode _UTL_ClearPinWstrbCpeMode
extern void _UTL_SetPinIoCtrl(PinHandle, CheckButton);
#define UTL_SetPinIoCtrl _UTL_SetPinIoCtrl
extern void _UTL_SetPinDreNumber(PinHandle, RadioButton);
#define UTL_SetPinDreNumber _UTL_SetPinDreNumber
extern void _UTL_SetPinDreWaveform(PinHandle, RadioButton);
#define UTL_SetPinDreWaveform _UTL_SetPinDreWaveform
extern void _UTL_SetPinDreClock(PinHandle, RadioButton);
#define UTL_SetPinDreClock _UTL_SetPinDreClock
extern void _UTL_SetPinDronInit(PinHandle, CheckButton);
#define UTL_SetPinDronInit _UTL_SetPinDronInit
extern void _UTL_SetPinDbmPinDrePattern(PinHandle, CheckButton);
#define UTL_SetPinDbmPinDrePattern _UTL_SetPinDbmPinDrePattern
extern void _UTL_SetPinDreOffsetClock(PinHandle, RadioButton);
#define UTL_SetPinDreOffsetClock _UTL_SetPinDreOffsetClock
extern void _UTL_SetPinPdsSendMode(PinHandle, RadioButton);
#define UTL_SetPinPdsSendMode _UTL_SetPinPdsSendMode
extern void _UTL_AddPinPdsA(PinHandle, RadioButton, RadioButton);
#define UTL_AddPinPdsA _UTL_AddPinPdsA
extern void _UTL_ClearPinPdsA(PinHandle);
#define UTL_ClearPinPdsA _UTL_ClearPinPdsA
extern void _UTL_AddPinPdsB(PinHandle, RadioButton, RadioButton);
#define UTL_AddPinPdsB _UTL_AddPinPdsB
extern void _UTL_ClearPinPdsB(PinHandle);
#define UTL_ClearPinPdsB _UTL_ClearPinPdsB
extern void _UTL_AddPinPdsD(PinHandle, RadioButton, RadioButton);
#define UTL_AddPinPdsD _UTL_AddPinPdsD
extern void _UTL_ClearPinPdsD(PinHandle);
#define UTL_ClearPinPdsD _UTL_ClearPinPdsD
extern void _UTL_AddPinPdsE(PinHandle, RadioButton, RadioButton);
#define UTL_AddPinPdsE _UTL_AddPinPdsE
extern void _UTL_ClearPinPdsE(PinHandle);
#define UTL_ClearPinPdsE _UTL_ClearPinPdsE
extern void _UTL_SetPinCyclePaletteSet(PinHandle, RadioButton);
#define UTL_SetPinCyclePaletteSet _UTL_SetPinCyclePaletteSet
extern void _UTL_SetPinRinv(PinHandle, CheckButton);
#define UTL_SetPinRinv _UTL_SetPinRinv
extern void _UTL_SetPinRdsm(PinHandle, CheckButton);
#define UTL_SetPinRdsm _UTL_SetPinRdsm
extern void _UTL_SetPinPsm(PinHandle, CheckButton);
#define UTL_SetPinPsm _UTL_SetPinPsm
extern void _UTL_SetPinSdm(PinHandle, CheckButton);
#define UTL_SetPinSdm _UTL_SetPinSdm
extern void _UTL_SetPinSmc(PinHandle, CheckButton);
#define UTL_SetPinSmc _UTL_SetPinSmc
extern void _UTL_SetPinAinv(PinHandle, CheckButton);
#define UTL_SetPinAinv _UTL_SetPinAinv
extern void _UTL_SetPinDssNumber(PinHandle, RadioButton);
#define UTL_SetPinDssNumber _UTL_SetPinDssNumber
extern void _UTL_SetPinDrDelay(PinHandle, RadioButton);
#define UTL_SetPinDrDelay _UTL_SetPinDrDelay
extern void _UTL_SetPinDreDelay(PinHandle, RadioButton);
#define UTL_SetPinDreDelay _UTL_SetPinDreDelay
extern void _UTL_SetPinExpDelay(PinHandle, RadioButton);
#define UTL_SetPinExpDelay _UTL_SetPinExpDelay
extern void _UTL_SetPinCpeDelay(PinHandle, RadioButton);
#define UTL_SetPinCpeDelay _UTL_SetPinCpeDelay
extern void _UTL_SetPinModeDrDelay(PinHandle, RadioButton, RadioButton);
#define UTL_SetPinModeDrDelay _UTL_SetPinModeDrDelay
extern void _UTL_SetPinModeDreDelay(PinHandle, RadioButton, RadioButton);
#define UTL_SetPinModeDreDelay _UTL_SetPinModeDreDelay
extern void _UTL_SetPinModeExpDelay(PinHandle, RadioButton, RadioButton);
#define UTL_SetPinModeExpDelay _UTL_SetPinModeExpDelay
extern void _UTL_SetPinModeCpeDelay(PinHandle, RadioButton, RadioButton);
#define UTL_SetPinModeCpeDelay _UTL_SetPinModeCpeDelay
extern void _UTL_SetPinDrPatternLevel(PinHandle, RadioButton);
#define UTL_SetPinDrPatternLevel _UTL_SetPinDrPatternLevel
extern void _UTL_SetPinDrePatternLevel(PinHandle, RadioButton);
#define UTL_SetPinDrePatternLevel _UTL_SetPinDrePatternLevel
extern void _UTL_SetPinBankMultiplex(PinHandle, RadioButton);
#define UTL_SetPinBankMultiplex _UTL_SetPinBankMultiplex
extern void _UTL_SetPinBankNumber(PinHandle, RadioButton);
#define UTL_SetPinBankNumber _UTL_SetPinBankNumber
extern void _UTL_SetPinTerm(PinHandle, CheckButton);
#define UTL_SetPinTerm _UTL_SetPinTerm
extern void _UTL_SetPinIlNumber(PinHandle, RadioButton);
#define UTL_SetPinIlNumber _UTL_SetPinIlNumber
extern void _UTL_SetPinPl(PinHandle, RadioButton);
#define UTL_SetPinPl _UTL_SetPinPl
extern void _UTL_SetPinVtNumber(PinHandle, RadioButton);
#define UTL_SetPinVtNumber _UTL_SetPinVtNumber
extern void _UTL_SetPinDclp(PinHandle, CheckButton);
#define UTL_SetPinDclp _UTL_SetPinDclp
extern void _UTL_SetPinVloadNumber(PinHandle, RadioButton);
#define UTL_SetPinVloadNumber _UTL_SetPinVloadNumber
extern void _UTL_SetPinVloadResistor(PinHandle, RadioButton);
#define UTL_SetPinVloadResistor _UTL_SetPinVloadResistor
extern void _UTL_SetPinOpen(PinHandle, CheckButton);
#define UTL_SetPinOpen _UTL_SetPinOpen
extern void _UTL_SetPinPatternInh(PinHandle, CheckButton);
#define UTL_SetPinPatternInh _UTL_SetPinPatternInh
extern void _UTL_SetPinPatternInhLevel(PinHandle, RadioButton);
#define UTL_SetPinPatternInhLevel _UTL_SetPinPatternInhLevel
extern void _UTL_SetPinDrePatternInh(PinHandle, CheckButton);
#define UTL_SetPinDrePatternInh _UTL_SetPinDrePatternInh
extern void _UTL_SetPinPatternInhPerPin(PinHandle, CheckButton);
#define UTL_SetPinPatternInhPerPin _UTL_SetPinPatternInhPerPin
extern void _UTL_SetPinDbmPinFix(PinHandle, CheckButton);
#define UTL_SetPinDbmPinFix _UTL_SetPinDbmPinFix
extern void _UTL_SetPinVsDisconnect(PinHandle, CheckButton);
#define UTL_SetPinVsDisconnect _UTL_SetPinVsDisconnect
extern void _UTL_SetPinVsBypassCapacitor(PinHandle, CheckButton);
#define UTL_SetPinVsBypassCapacitor _UTL_SetPinVsBypassCapacitor
extern void _UTL_SetPinVsBypassCapacitorNumber(PinHandle, RadioButton, CheckButton);
#define UTL_SetPinVsBypassCapacitorNumber _UTL_SetPinVsBypassCapacitorNumber
extern void _UTL_SetPinDcConnect(PinHandle, CheckButton);
#define UTL_SetPinDcConnect _UTL_SetPinDcConnect
extern void _UTL_SendPin(PinHandle, char *);
#define UTL_SendPin _UTL_SendPin
extern void _UTL_ResetDriverLevel(void);
#define UTL_ResetDriverLevel _UTL_ResetDriverLevel
extern LevelHoldHandle _UTL_GetLevelHoldHandle(void);
#define UTL_GetLevelHoldHandle _UTL_GetLevelHoldHandle
extern void _UTL_SetLevelHoldInit(LevelHoldHandle, CheckButton);
#define UTL_SetLevelHoldInit _UTL_SetLevelHoldInit
extern void _UTL_SendLevelHold(LevelHoldHandle);
#define UTL_SendLevelHold _UTL_SendLevelHold
extern DbmDelayHandle _UTL_GetDbmDelayHandle(void);
#define UTL_GetDbmDelayHandle _UTL_GetDbmDelayHandle
extern void _UTL_SetDbmDelayInhibit(DbmDelayHandle, CheckButton);
#define UTL_SetDbmDelayInhibit _UTL_SetDbmDelayInhibit
extern void _UTL_SendDbmDelay(DbmDelayHandle);
#define UTL_SendDbmDelay _UTL_SendDbmDelay
extern LevelFixHandle _UTL_GetLevelFixHandle(void);
#define UTL_GetLevelFixHandle _UTL_GetLevelFixHandle
extern void _UTL_SetLevelFixOutputLevel(LevelFixHandle, RadioButton, RadioButton);
#define UTL_SetLevelFixOutputLevel _UTL_SetLevelFixOutputLevel
extern void _UTL_SendLevelFix(LevelFixHandle, UT_PIN, UT_DUT);
#define UTL_SendLevelFix _UTL_SendLevelFix
extern MatchPinGroupHandle _UTL_GetMatchPinGroupHandle( void );
#define UTL_GetMatchPinGroupHandle _UTL_GetMatchPinGroupHandle
extern void _UTL_SetMatchPinGroupSignal ( MatchPinGroupHandle, RadioButton, RadioButton );
#define UTL_SetMatchPinGroupSignal _UTL_SetMatchPinGroupSignal
extern void _UTL_SendMatchPinGroup ( MatchPinGroupHandle );
#define UTL_SendMatchPinGroup _UTL_SendMatchPinGroup
extern VihhMutHandle _UTL_GetVihhMutHandle( void );
#define UTL_GetVihhMutHandle _UTL_GetVihhMutHandle
extern void _UTL_SetVihhMutSignal ( VihhMutHandle, RadioButton );
#define UTL_SetVihhMutSignal _UTL_SetVihhMutSignal
extern void _UTL_SendVihhMut ( VihhMutHandle );
#define UTL_SendVihhMut _UTL_SendVihhMut
extern VihhMutStartCtrlHandle _UTL_GetVihhMutStartCtrlHandle( void );
#define UTL_GetVihhMutStartCtrlHandle _UTL_GetVihhMutStartCtrlHandle
extern void _UTL_SetVihhMutStartCtrl ( VihhMutStartCtrlHandle, RadioButton );
#define UTL_SetVihhMutStartCtrl _UTL_SetVihhMutStartCtrl
extern void _UTL_SendVihhMutStartCtrl ( VihhMutStartCtrlHandle );
#define UTL_SendVihhMutStartCtrl _UTL_SendVihhMutStartCtrl
extern VsHandle _UTL_GetVsHandle( void );
#define UTL_GetVsHandle _UTL_GetVsHandle
extern void _UTL_SetVsMode( VsHandle , RadioButton );
#define UTL_SetVsMode _UTL_SetVsMode
extern void _UTL_SetVsSource( VsHandle , DSlider );
#define UTL_SetVsSource _UTL_SetVsSource
extern void _UTL_SetVsSrange( VsHandle , DSlider , DSlider );
#define UTL_SetVsSrange _UTL_SetVsSrange
extern void _UTL_SetVsMrange( VsHandle , DSlider , DSlider );
#define UTL_SetVsMrange _UTL_SetVsMrange
extern void _UTL_SetVsPclamp( VsHandle , DSlider );
#define UTL_SetVsPclamp _UTL_SetVsPclamp
extern void _UTL_SetVsMclamp( VsHandle , DSlider );
#define UTL_SetVsMclamp _UTL_SetVsMclamp
extern void _UTL_SetVsFilter( VsHandle , RadioButton );
#define UTL_SetVsFilter _UTL_SetVsFilter
extern void _UTL_SetVsHighSpeedSlewRateMode( VsHandle , CheckButton );
#define UTL_SetVsHighSpeedSlewRateMode _UTL_SetVsHighSpeedSlewRateMode
extern void _UTL_SetVsSlewRate( VsHandle , DSlider );
#define UTL_SetVsSlewRate _UTL_SetVsSlewRate
extern void _UTL_SetVsPhaseCompensation( VsHandle , RadioButton );
#define UTL_SetVsPhaseCompensation _UTL_SetVsPhaseCompensation
extern void _UTL_SetVsLimitHigh( VsHandle , DSlider , CheckButton );
#define UTL_SetVsLimitHigh _UTL_SetVsLimitHigh
extern void _UTL_SetVsLimitLow( VsHandle , DSlider , CheckButton );
#define UTL_SetVsLimitLow _UTL_SetVsLimitLow
extern void _UTL_SetVsMeasCnt( VsHandle , Slider );
#define UTL_SetVsMeasCnt _UTL_SetVsMeasCnt
extern void _UTL_AddVsWetItem( VsHandle , RadioButton );
#define UTL_AddVsWetItem _UTL_AddVsWetItem
extern void _UTL_ClearVsWetItem( VsHandle );
#define UTL_ClearVsWetItem _UTL_ClearVsWetItem
extern void _UTL_SetVsParaDrive( VsHandle , CheckButton );
#define UTL_SetVsParaDrive _UTL_SetVsParaDrive
extern void _UTL_SendVs( VsHandle , RadioButton );
#define UTL_SendVs _UTL_SendVs
extern void _UTL_SendVsTargetDut( VsHandle , RadioButton , UT_DUT );
#define UTL_SendVsTargetDut _UTL_SendVsTargetDut
extern void _UTL_SendVsTargetPps( VsHandle , RadioButton );
#define UTL_SendVsTargetPps _UTL_SendVsTargetPps
extern ViHandle _UTL_GetViHandle( void );
#define UTL_GetViHandle _UTL_GetViHandle
extern void _UTL_SetViHigh( ViHandle , DSlider );
#define UTL_SetViHigh _UTL_SetViHigh
extern void _UTL_SetViLow ( ViHandle , DSlider );
#define UTL_SetViLow _UTL_SetViLow
extern void _UTL_SetViHvDr( ViHandle , CheckButton );
#define UTL_SetViHvDr _UTL_SetViHvDr
extern void _UTL_SetViHvLvDr( ViHandle , CheckButton );
#define UTL_SetViHvLvDr _UTL_SetViHvLvDr
extern void _UTL_SendVi ( ViHandle , RadioButton );
#define UTL_SendVi _UTL_SendVi
extern void _UTL_SendViPerPin ( ViHandle , UT_PIN , UT_DUT );
#define UTL_SendViPerPin _UTL_SendViPerPin
extern VoHandle _UTL_GetVoHandle( void );
#define UTL_GetVoHandle _UTL_GetVoHandle
extern void _UTL_SetVoHigh( VoHandle , DSlider );
#define UTL_SetVoHigh _UTL_SetVoHigh
extern void _UTL_SetVoLow ( VoHandle , DSlider );
#define UTL_SetVoLow _UTL_SetVoLow
extern void _UTL_SendVo ( VoHandle , RadioButton );
#define UTL_SendVo _UTL_SendVo
extern VodHandle _UTL_GetVodHandle( void );
#define UTL_GetVodHandle _UTL_GetVodHandle
extern void _UTL_SetVodHigh( VodHandle , DSlider );
#define UTL_SetVodHigh _UTL_SetVodHigh
extern void _UTL_SetVodLow ( VodHandle , DSlider );
#define UTL_SetVodLow _UTL_SetVodLow
extern void _UTL_SendVod ( VodHandle , RadioButton );
#define UTL_SendVod _UTL_SendVod
extern IlHandle _UTL_GetIlHandle( void );
#define UTL_GetIlHandle _UTL_GetIlHandle
extern void _UTL_SetIlHigh( IlHandle , DSlider );
#define UTL_SetIlHigh _UTL_SetIlHigh
extern void _UTL_SetIlLow ( IlHandle , DSlider );
#define UTL_SetIlLow _UTL_SetIlLow
extern void _UTL_SendIl ( IlHandle , RadioButton );
#define UTL_SendIl _UTL_SendIl
extern VtHandle _UTL_GetVtHandle( void );
#define UTL_GetVtHandle _UTL_GetVtHandle
extern void _UTL_SetVt ( VtHandle , DSlider );
#define UTL_SetVt _UTL_SetVt
extern void _UTL_SendVt ( VtHandle , RadioButton );
#define UTL_SendVt _UTL_SendVt
extern DclpHandle _UTL_GetDclpHandle( void );
#define UTL_GetDclpHandle _UTL_GetDclpHandle
extern void _UTL_SetDclpHigh( DclpHandle , DSlider );
#define UTL_SetDclpHigh _UTL_SetDclpHigh
extern void _UTL_SetDclpLow ( DclpHandle , DSlider );
#define UTL_SetDclpLow _UTL_SetDclpLow
extern void _UTL_SendDclp ( DclpHandle , RadioButton );
#define UTL_SendDclp _UTL_SendDclp
extern VihhHandle _UTL_GetVihhHandle( void );
#define UTL_GetVihhHandle _UTL_GetVihhHandle
extern void _UTL_SetVihhHigh( VihhHandle , DSlider );
#define UTL_SetVihhHigh _UTL_SetVihhHigh
extern void _UTL_SetVihhHv ( VihhHandle , DSlider );
#define UTL_SetVihhHv _UTL_SetVihhHv
extern void _UTL_SetVihhLow ( VihhHandle , DSlider );
#define UTL_SetVihhLow _UTL_SetVihhLow
extern void _UTL_SendVihh ( VihhHandle , RadioButton );
#define UTL_SendVihh _UTL_SendVihh
extern void _UTL_SendVihhPerPin ( VihhHandle , UT_PIN , UT_DUT );
#define UTL_SendVihhPerPin _UTL_SendVihhPerPin
extern IodModeHandle _UTL_GetIodModeHandle( void );
#define UTL_GetIodModeHandle _UTL_GetIodModeHandle
extern void _UTL_AddIodModePin ( IodModeHandle , UT_PIN );
#define UTL_AddIodModePin _UTL_AddIodModePin
extern void _UTL_ClearIodModePin ( IodModeHandle );
#define UTL_ClearIodModePin _UTL_ClearIodModePin
extern void _UTL_SetIodMode ( IodModeHandle , CheckButton );
#define UTL_SetIodMode _UTL_SetIodMode
extern void _UTL_SetIodModeAuto ( IodModeHandle , CheckButton );
#define UTL_SetIodModeAuto _UTL_SetIodModeAuto
extern void _UTL_SetIodModeCalcFunc( IodModeHandle , void (*)(IodCalcFunc *) );
#define UTL_SetIodModeCalcFunc _UTL_SetIodModeCalcFunc
extern void _UTL_SetIodModeCalcFuncAndLibrary( IodModeHandle , char * , char * );
#define UTL_SetIodModeCalcFuncAndLibrary _UTL_SetIodModeCalcFuncAndLibrary
extern void _UTL_SendIodMode ( IodModeHandle );
#define UTL_SendIodMode _UTL_SendIodMode
extern IodHandle _UTL_GetIodHandle( void );
#define UTL_GetIodHandle _UTL_GetIodHandle
extern void _UTL_AddIodPin ( IodHandle , UT_PIN );
#define UTL_AddIodPin _UTL_AddIodPin
extern void _UTL_ClearIodPin( IodHandle );
#define UTL_ClearIodPin _UTL_ClearIodPin
extern void _UTL_AddIodDut ( IodHandle , UT_DUT );
#define UTL_AddIodDut _UTL_AddIodDut
extern void _UTL_ClearIodDut( IodHandle );
#define UTL_ClearIodDut _UTL_ClearIodDut
extern void _UTL_SetIodHigh ( IodHandle , DSlider );
#define UTL_SetIodHigh _UTL_SetIodHigh
extern void _UTL_SetIodLow ( IodHandle , DSlider );
#define UTL_SetIodLow _UTL_SetIodLow
extern void _UTL_SendIod ( IodHandle );
#define UTL_SendIod _UTL_SendIod
extern VloadHandle _UTL_GetVloadHandle( void );
#define UTL_GetVloadHandle _UTL_GetVloadHandle
extern void _UTL_SetVload ( VloadHandle , DSlider );
#define UTL_SetVload _UTL_SetVload
extern void _UTL_SendVload ( VloadHandle , RadioButton );
#define UTL_SendVload _UTL_SendVload
extern void _UTL_SendCw ( RadioButton , unsigned );
#define UTL_SendCw _UTL_SendCw
extern unsigned int _UTL_ReadCw ( RadioButton , UT_DUT );
#define UTL_ReadCw _UTL_ReadCw
extern AuxDutSignalHandle _UTL_GetAuxDutSignalHandle( void );
#define UTL_GetAuxDutSignalHandle _UTL_GetAuxDutSignalHandle
extern void _UTL_SetAuxDutSignalStationNumber( AuxDutSignalHandle, USlider );
#define UTL_SetAuxDutSignalStationNumber _UTL_SetAuxDutSignalStationNumber
extern void _UTL_SetAuxDutSignalAllStation( AuxDutSignalHandle, CheckButton );
#define UTL_SetAuxDutSignalAllStation _UTL_SetAuxDutSignalAllStation
extern void _UTL_SetAuxDutSignalData( AuxDutSignalHandle, USlider );
#define UTL_SetAuxDutSignalData _UTL_SetAuxDutSignalData
extern void _UTL_SendAuxDutSignal ( AuxDutSignalHandle, RadioButton, RadioButton );
#define UTL_SendAuxDutSignal _UTL_SendAuxDutSignal
extern void _UTL_SyncAuxDutSignal( RadioButton );
#define UTL_SyncAuxDutSignal _UTL_SyncAuxDutSignal
extern LbCtrlHandle _UTL_GetLbCtrlHandle( void );
#define UTL_GetLbCtrlHandle _UTL_GetLbCtrlHandle
extern void _UTL_SetLbCtrlClockTiming( LbCtrlHandle , DSlider , DSlider );
#define UTL_SetLbCtrlClockTiming _UTL_SetLbCtrlClockTiming
extern void _UTL_SetLbCtrlDataPacketCount( LbCtrlHandle , USlider );
#define UTL_SetLbCtrlDataPacketCount _UTL_SetLbCtrlDataPacketCount
extern void _UTL_SetLbCtrlDataFirstBit( LbCtrlHandle , RadioButton );
#define UTL_SetLbCtrlDataFirstBit _UTL_SetLbCtrlDataFirstBit
extern void _UTL_SetLbCtrlSSPolarity( LbCtrlHandle , RadioButton );
#define UTL_SetLbCtrlSSPolarity _UTL_SetLbCtrlSSPolarity
extern void _UTL_SetLbCtrlResetPolarity( LbCtrlHandle , RadioButton );
#define UTL_SetLbCtrlResetPolarity _UTL_SetLbCtrlResetPolarity
extern void _UTL_SetLbCtrlStartDelayTime( LbCtrlHandle , DSlider );
#define UTL_SetLbCtrlStartDelayTime _UTL_SetLbCtrlStartDelayTime
extern void _UTL_SetLbCtrlClockCount( LbCtrlHandle , USlider );
#define UTL_SetLbCtrlClockCount _UTL_SetLbCtrlClockCount
extern void _UTL_SetLbCtrlData( LbCtrlHandle , USlider );
#define UTL_SetLbCtrlData _UTL_SetLbCtrlData
extern void _UTL_SetLbCtrlStrbSkewAdjust( LbCtrlHandle , DSlider );
#define UTL_SetLbCtrlStrbSkewAdjust _UTL_SetLbCtrlStrbSkewAdjust
extern void _UTL_StartLbCtrl( LbCtrlHandle );
#define UTL_StartLbCtrl _UTL_StartLbCtrl
extern void _UTL_SetLbCtrlResetDurationTime( LbCtrlHandle , DSlider );
#define UTL_SetLbCtrlResetDurationTime _UTL_SetLbCtrlResetDurationTime
extern void _UTL_ResetLbCtrl( LbCtrlHandle );
#define UTL_ResetLbCtrl _UTL_ResetLbCtrl
extern USlider _UTL_ReadLbCtrlData( void );
#define UTL_ReadLbCtrlData _UTL_ReadLbCtrlData
extern SpiCtrlHandle _UTL_GetSpiCtrlHandle( void );
#define UTL_GetSpiCtrlHandle _UTL_GetSpiCtrlHandle
extern void _UTL_SetSpiCtrlClockTiming( SpiCtrlHandle , DSlider , DSlider );
#define UTL_SetSpiCtrlClockTiming _UTL_SetSpiCtrlClockTiming
extern void _UTL_SetSpiCtrlSSPolarity( SpiCtrlHandle , RadioButton );
#define UTL_SetSpiCtrlSSPolarity _UTL_SetSpiCtrlSSPolarity
extern void _UTL_SetSpiCtrlStartDelayTime( SpiCtrlHandle , DSlider );
#define UTL_SetSpiCtrlStartDelayTime _UTL_SetSpiCtrlStartDelayTime
extern void _UTL_SetSpiCtrlData( SpiCtrlHandle , USlider * , USlider );
#define UTL_SetSpiCtrlData _UTL_SetSpiCtrlData
extern void _UTL_SetSpiCtrlStrbSkewAdjust( SpiCtrlHandle , DSlider );
#define UTL_SetSpiCtrlStrbSkewAdjust _UTL_SetSpiCtrlStrbSkewAdjust
extern void _UTL_SetSpiCtrlMode( SpiCtrlHandle , RadioButton );
#define UTL_SetSpiCtrlMode _UTL_SetSpiCtrlMode
extern void _UTL_SetSpiCtrlHighSpeedInterval( SpiCtrlHandle , DSlider , DSlider );
#define UTL_SetSpiCtrlHighSpeedInterval _UTL_SetSpiCtrlHighSpeedInterval
extern void _UTL_StartSpiCtrl( SpiCtrlHandle , RadioButton );
#define UTL_StartSpiCtrl _UTL_StartSpiCtrl
extern void _UTL_ReadSpiCtrlData( RadioButton , USlider * , USlider *);
#define UTL_ReadSpiCtrlData _UTL_ReadSpiCtrlData
extern PowerSeqHandle _UTL_GetPowerSeqHandle(void);
#define UTL_GetPowerSeqHandle _UTL_GetPowerSeqHandle
extern void _UTL_AddPowerSeqVs(PowerSeqHandle, USlider, RadioButton);
#define UTL_AddPowerSeqVs _UTL_AddPowerSeqVs
extern void _UTL_AddPowerSeqVsAll(PowerSeqHandle, USlider);
#define UTL_AddPowerSeqVsAll _UTL_AddPowerSeqVsAll
extern void _UTL_AddPowerSeqDcAll(PowerSeqHandle, USlider);
#define UTL_AddPowerSeqDcAll _UTL_AddPowerSeqDcAll
extern void _UTL_AddPowerSeqDclpAll(PowerSeqHandle, USlider);
#define UTL_AddPowerSeqDclpAll _UTL_AddPowerSeqDclpAll
extern void _UTL_AddPowerSeqViAll(PowerSeqHandle, USlider);
#define UTL_AddPowerSeqViAll _UTL_AddPowerSeqViAll
extern void _UTL_AddPowerSeqVtAll(PowerSeqHandle, USlider);
#define UTL_AddPowerSeqVtAll _UTL_AddPowerSeqVtAll
extern void _UTL_AddPowerSeqIlAll(PowerSeqHandle, USlider);
#define UTL_AddPowerSeqIlAll _UTL_AddPowerSeqIlAll
extern void _UTL_AddPowerSeqOthers(PowerSeqHandle, USlider);
#define UTL_AddPowerSeqOthers _UTL_AddPowerSeqOthers
extern void _UTL_AddPowerSeqAll(PowerSeqHandle, USlider);
#define UTL_AddPowerSeqAll _UTL_AddPowerSeqAll
extern void _UTL_AddPowerSeqUnit(PowerSeqHandle, RadioButton, USlider);
#define UTL_AddPowerSeqUnit _UTL_AddPowerSeqUnit
extern void _UTL_ClearPowerSeqUnit(PowerSeqHandle, USlider);
#define UTL_ClearPowerSeqUnit _UTL_ClearPowerSeqUnit
extern void _UTL_SetPowerSeqWaitTime(PowerSeqHandle, USlider, DSlider);
#define UTL_SetPowerSeqWaitTime _UTL_SetPowerSeqWaitTime
extern void _UTL_SendPowerSeq(PowerSeqHandle);
#define UTL_SendPowerSeq _UTL_SendPowerSeq
extern void _UTL_OnPowerSeq(void);
#define UTL_OnPowerSeq _UTL_OnPowerSeq
extern void _UTL_OffPowerSeq(void);
#define UTL_OffPowerSeq _UTL_OffPowerSeq
extern PowerCtrlHandle _UTL_GetPowerCtrlHandle(void);
#define UTL_GetPowerCtrlHandle _UTL_GetPowerCtrlHandle
extern void _UTL_AddPowerCtrlVs(PowerCtrlHandle, RadioButton);
#define UTL_AddPowerCtrlVs _UTL_AddPowerCtrlVs
extern void _UTL_AddPowerCtrlVsAll(PowerCtrlHandle);
#define UTL_AddPowerCtrlVsAll _UTL_AddPowerCtrlVsAll
extern void _UTL_AddPowerCtrlDcAll(PowerCtrlHandle);
#define UTL_AddPowerCtrlDcAll _UTL_AddPowerCtrlDcAll
extern void _UTL_AddPowerCtrlDclpAll(PowerCtrlHandle);
#define UTL_AddPowerCtrlDclpAll _UTL_AddPowerCtrlDclpAll
extern void _UTL_AddPowerCtrlViAll(PowerCtrlHandle);
#define UTL_AddPowerCtrlViAll _UTL_AddPowerCtrlViAll
extern void _UTL_AddPowerCtrlVtAll(PowerCtrlHandle);
#define UTL_AddPowerCtrlVtAll _UTL_AddPowerCtrlVtAll
extern void _UTL_AddPowerCtrlIlAll(PowerCtrlHandle);
#define UTL_AddPowerCtrlIlAll _UTL_AddPowerCtrlIlAll
extern void _UTL_AddPowerCtrlAll(PowerCtrlHandle);
#define UTL_AddPowerCtrlAll _UTL_AddPowerCtrlAll
extern void _UTL_AddPowerCtrlUnit(PowerCtrlHandle, RadioButton);
#define UTL_AddPowerCtrlUnit _UTL_AddPowerCtrlUnit
extern void _UTL_ClearPowerCtrlUnit(PowerCtrlHandle);
#define UTL_ClearPowerCtrlUnit _UTL_ClearPowerCtrlUnit
extern void _UTL_SetPowerCtrlWaitTime(PowerCtrlHandle, DSlider);
#define UTL_SetPowerCtrlWaitTime _UTL_SetPowerCtrlWaitTime
extern void _UTL_OnPowerCtrl(PowerCtrlHandle);
#define UTL_OnPowerCtrl _UTL_OnPowerCtrl
extern void _UTL_OffPowerCtrl(PowerCtrlHandle);
#define UTL_OffPowerCtrl _UTL_OffPowerCtrl
extern void _UTL_SetWet(void);
#define UTL_SetWet _UTL_SetWet
extern void _UTL_ResetWet(void);
#define UTL_ResetWet _UTL_ResetWet
extern TgHandle _UTL_GetTgHandle(void);
#define UTL_GetTgHandle _UTL_GetTgHandle
extern void _UTL_AddTgRate(TgHandle, RadioButton, DSlider);
#define UTL_AddTgRate _UTL_AddTgRate
extern void _UTL_AddTgAclk(TgHandle, RadioButton, RadioButton, DSlider);
#define UTL_AddTgAclk _UTL_AddTgAclk
extern void _UTL_AddTgAclkOff(TgHandle, RadioButton, RadioButton);
#define UTL_AddTgAclkOff _UTL_AddTgAclkOff
extern void _UTL_AddTgBclk(TgHandle, RadioButton, RadioButton, DSlider);
#define UTL_AddTgBclk _UTL_AddTgBclk
extern void _UTL_AddTgBclkOff(TgHandle, RadioButton, RadioButton);
#define UTL_AddTgBclkOff _UTL_AddTgBclkOff
extern void _UTL_AddTgCclk(TgHandle, RadioButton, RadioButton, DSlider);
#define UTL_AddTgCclk _UTL_AddTgCclk
extern void _UTL_AddTgCclkOff(TgHandle, RadioButton, RadioButton);
#define UTL_AddTgCclkOff _UTL_AddTgCclkOff
extern void _UTL_AddTgStrb(TgHandle, RadioButton, RadioButton, DSlider);
#define UTL_AddTgStrb _UTL_AddTgStrb
extern void _UTL_AddTgStrbOff(TgHandle, RadioButton, RadioButton);
#define UTL_AddTgStrbOff _UTL_AddTgStrbOff
extern void _UTL_AddTgPairStrbL(TgHandle, RadioButton, RadioButton, DSlider);
#define UTL_AddTgPairStrbL _UTL_AddTgPairStrbL
extern void _UTL_AddTgPairStrbT(TgHandle, RadioButton, RadioButton, DSlider);
#define UTL_AddTgPairStrbT _UTL_AddTgPairStrbT
extern void _UTL_AddTgDreL(TgHandle, RadioButton, RadioButton, DSlider);
#define UTL_AddTgDreL _UTL_AddTgDreL
extern void _UTL_AddTgDreLOff(TgHandle, RadioButton, RadioButton);
#define UTL_AddTgDreLOff _UTL_AddTgDreLOff
extern void _UTL_AddTgDreT(TgHandle, RadioButton, RadioButton, DSlider);
#define UTL_AddTgDreT _UTL_AddTgDreT
extern void _UTL_AddTgDreTOff(TgHandle, RadioButton, RadioButton);
#define UTL_AddTgDreTOff _UTL_AddTgDreTOff
extern void _UTL_AddTgDrzPulseWidth(TgHandle, RadioButton, DSlider);
#define UTL_AddTgDrzPulseWidth _UTL_AddTgDrzPulseWidth
extern void _UTL_AddTgDreLOffset(TgHandle, RadioButton, DSlider);
#define UTL_AddTgDreLOffset _UTL_AddTgDreLOffset
extern void _UTL_AddTgDreTOffset(TgHandle, RadioButton, DSlider);
#define UTL_AddTgDreTOffset _UTL_AddTgDreTOffset
extern void _UTL_ClearTgHandle(TgHandle);
#define UTL_ClearTgHandle _UTL_ClearTgHandle
extern void _UTL_SendTg(TgHandle);
#define UTL_SendTg _UTL_SendTg
extern void _UTL_StartFrun(void);
#define UTL_StartFrun _UTL_StartFrun
extern void _UTL_StopFrun(void);
#define UTL_StopFrun _UTL_StopFrun
extern DSlider _UTL_ReadTgRate(RadioButton, RadioButton);
#define UTL_ReadTgRate _UTL_ReadTgRate
extern DSlider _UTL_ReadTgAclk(RadioButton, RadioButton, RadioButton);
#define UTL_ReadTgAclk _UTL_ReadTgAclk
extern CheckButton _UTL_ReadTgAclkOff(RadioButton, RadioButton, RadioButton);
#define UTL_ReadTgAclkOff _UTL_ReadTgAclkOff
extern DSlider _UTL_ReadTgBclk(RadioButton, RadioButton, RadioButton);
#define UTL_ReadTgBclk _UTL_ReadTgBclk
extern CheckButton _UTL_ReadTgBclkOff(RadioButton, RadioButton, RadioButton);
#define UTL_ReadTgBclkOff _UTL_ReadTgBclkOff
extern DSlider _UTL_ReadTgCclk(RadioButton, RadioButton, RadioButton);
#define UTL_ReadTgCclk _UTL_ReadTgCclk
extern CheckButton _UTL_ReadTgCclkOff(RadioButton, RadioButton, RadioButton);
#define UTL_ReadTgCclkOff _UTL_ReadTgCclkOff
extern DSlider _UTL_ReadTgDreL(RadioButton, RadioButton, RadioButton);
#define UTL_ReadTgDreL _UTL_ReadTgDreL
extern CheckButton _UTL_ReadTgDreLOff(RadioButton, RadioButton, RadioButton);
#define UTL_ReadTgDreLOff _UTL_ReadTgDreLOff
extern DSlider _UTL_ReadTgDreT(RadioButton, RadioButton, RadioButton);
#define UTL_ReadTgDreT _UTL_ReadTgDreT
extern CheckButton _UTL_ReadTgDreTOff(RadioButton, RadioButton, RadioButton);
#define UTL_ReadTgDreTOff _UTL_ReadTgDreTOff
extern DSlider _UTL_ReadTgStrb(RadioButton, RadioButton, RadioButton);
#define UTL_ReadTgStrb _UTL_ReadTgStrb
extern CheckButton _UTL_ReadTgStrbOff(RadioButton, RadioButton, RadioButton);
#define UTL_ReadTgStrbOff _UTL_ReadTgStrbOff
extern TgAdjustHandle _UTL_GetTgAdjustHandle( void );
#define UTL_GetTgAdjustHandle _UTL_GetTgAdjustHandle
extern void _UTL_AddTgAdjustTargetDut( TgAdjustHandle , UT_DUT );
#define UTL_AddTgAdjustTargetDut _UTL_AddTgAdjustTargetDut
extern void _UTL_ClearTgAdjustTargetDut( TgAdjustHandle );
#define UTL_ClearTgAdjustTargetDut _UTL_ClearTgAdjustTargetDut
extern void _UTL_AddTgAdjustTargetPin( TgAdjustHandle , UT_PIN );
#define UTL_AddTgAdjustTargetPin _UTL_AddTgAdjustTargetPin
extern void _UTL_ClearTgAdjustTargetPin( TgAdjustHandle );
#define UTL_ClearTgAdjustTargetPin _UTL_ClearTgAdjustTargetPin
extern void _UTL_SetTgAdjustTargetTgType(TgAdjustHandle ,RadioButton);
#define UTL_SetTgAdjustTargetTgType _UTL_SetTgAdjustTargetTgType
extern void _UTL_AddTgAdjustTargetEdge( TgAdjustHandle , RadioButton );
#define UTL_AddTgAdjustTargetEdge _UTL_AddTgAdjustTargetEdge
extern void _UTL_ClearTgAdjustTargetEdge( TgAdjustHandle );
#define UTL_ClearTgAdjustTargetEdge _UTL_ClearTgAdjustTargetEdge
extern void _UTL_AddTgAdjustTargetBank(TgAdjustHandle , RadioButton );
#define UTL_AddTgAdjustTargetBank _UTL_AddTgAdjustTargetBank
extern void _UTL_ClearTgAdjustTargetBank(TgAdjustHandle );
#define UTL_ClearTgAdjustTargetBank _UTL_ClearTgAdjustTargetBank
extern void _UTL_SetTgAdjustValue(TgAdjustHandle ,DSlider );
#define UTL_SetTgAdjustValue _UTL_SetTgAdjustValue
extern void _UTL_SendTgAdjust(TgAdjustHandle );
#define UTL_SendTgAdjust _UTL_SendTgAdjust
extern void _UTL_ResetTgAdjust(TgAdjustHandle );
#define UTL_ResetTgAdjust _UTL_ResetTgAdjust
extern TgBaseRateHandle _UTL_GetTgBaseRateHandle( void );
#define UTL_GetTgBaseRateHandle _UTL_GetTgBaseRateHandle
extern void _UTL_SetTgBaseRate(TgBaseRateHandle, DSlider );
#define UTL_SetTgBaseRate _UTL_SetTgBaseRate
extern void _UTL_SendTgBaseRate(TgBaseRateHandle);
#define UTL_SendTgBaseRate _UTL_SendTgBaseRate
extern TgFixedDelayEdgeHandle _UTL_GetTgFixedDelayEdgeHandle( void );
#define UTL_GetTgFixedDelayEdgeHandle _UTL_GetTgFixedDelayEdgeHandle
extern void _UTL_AddTgFixedDelayEdgeTargetPin( TgFixedDelayEdgeHandle, UT_PIN );
#define UTL_AddTgFixedDelayEdgeTargetPin _UTL_AddTgFixedDelayEdgeTargetPin
extern void _UTL_ClearTgFixedDelayEdgeTargetPin( TgFixedDelayEdgeHandle );
#define UTL_ClearTgFixedDelayEdgeTargetPin _UTL_ClearTgFixedDelayEdgeTargetPin
extern void _UTL_AddTgFixedDelayEdgeTargetTs( TgFixedDelayEdgeHandle, RadioButton );
#define UTL_AddTgFixedDelayEdgeTargetTs _UTL_AddTgFixedDelayEdgeTargetTs
extern void _UTL_ClearTgFixedDelayEdgeTargetTs( TgFixedDelayEdgeHandle );
#define UTL_ClearTgFixedDelayEdgeTargetTs _UTL_ClearTgFixedDelayEdgeTargetTs
extern void _UTL_SetTgFixedDelayEdgeValue( TgFixedDelayEdgeHandle, DSlider );
#define UTL_SetTgFixedDelayEdgeValue _UTL_SetTgFixedDelayEdgeValue
extern void _UTL_SendTgFixedDelayEdge( TgFixedDelayEdgeHandle );
#define UTL_SendTgFixedDelayEdge _UTL_SendTgFixedDelayEdge
extern void _UTL_ResetTgFixedDelayEdge( void );
#define UTL_ResetTgFixedDelayEdge _UTL_ResetTgFixedDelayEdge
extern MpatSelectorHandle _UTL_GetMpatSelectorHandle( void );
#define UTL_GetMpatSelectorHandle _UTL_GetMpatSelectorHandle
extern void _UTL_AddMpatSelector ( MpatSelectorHandle, char * , char * );
#define UTL_AddMpatSelector _UTL_AddMpatSelector
extern void _UTL_ClearMpatSelector ( MpatSelectorHandle );
#define UTL_ClearMpatSelector _UTL_ClearMpatSelector
extern void _UTL_SendMpatSelector ( MpatSelectorHandle );
#define UTL_SendMpatSelector _UTL_SendMpatSelector
extern void _UTL_UpdateMpatSelector ( MpatSelectorHandle );
#define UTL_UpdateMpatSelector _UTL_UpdateMpatSelector
extern MpatSelectorCursor _UTL_GetMpatSelectorCursor ( MpatSelectorHandle );
#define UTL_GetMpatSelectorCursor _UTL_GetMpatSelectorCursor
extern MpatSelector *_UTL_NextMpatSelector ( MpatSelectorCursor );
#define UTL_NextMpatSelector _UTL_NextMpatSelector
extern AddrScramHandle _UTL_GetAddrScramHandle(void);
#define UTL_GetAddrScramHandle _UTL_GetAddrScramHandle
extern void _UTL_SetAddrScramMode (AddrScramHandle, RadioButton);
#define UTL_SetAddrScramMode _UTL_SetAddrScramMode
extern void _UTL_SetAddrScramFileName (AddrScramHandle, char *);
#define UTL_SetAddrScramFileName _UTL_SetAddrScramFileName
extern void _UTL_SetAddrScramAddrAssign (AddrScramHandle, RadioButton, RadioButton);
#define UTL_SetAddrScramAddrAssign _UTL_SetAddrScramAddrAssign
extern void _UTL_SetAddrScramAlpgUnit (AddrScramHandle, RadioButton);
#define UTL_SetAddrScramAlpgUnit _UTL_SetAddrScramAlpgUnit
extern void _UTL_SetAddrScramEnableBit (AddrScramHandle, RadioButton, USlider, RadioButton);
#define UTL_SetAddrScramEnableBit _UTL_SetAddrScramEnableBit
extern void _UTL_SetAddrScramSeparateMode(AddrScramHandle, CheckButton);
#define UTL_SetAddrScramSeparateMode _UTL_SetAddrScramSeparateMode
extern void _UTL_SetAddrScramSideSelect (AddrScramHandle, RadioButton);
#define UTL_SetAddrScramSideSelect _UTL_SetAddrScramSideSelect
extern void _UTL_SendPreScram (AddrScramHandle);
#define UTL_SendPreScram _UTL_SendPreScram
extern void _UTL_SendAddrScram (AddrScramHandle);
#define UTL_SendAddrScram _UTL_SendAddrScram
extern ScramConditionHandle _UTL_GetScramConditionHandle(void);
#define UTL_GetScramConditionHandle _UTL_GetScramConditionHandle
extern void _UTL_SetScramConditionAlpgUnit(ScramConditionHandle, RadioButton);
#define UTL_SetScramConditionAlpgUnit _UTL_SetScramConditionAlpgUnit
extern void _UTL_SetScramConditionDivideMode(ScramConditionHandle, RadioButton);
#define UTL_SetScramConditionDivideMode _UTL_SetScramConditionDivideMode
extern void _UTL_SendScramCondition(ScramConditionHandle);
#define UTL_SendScramCondition _UTL_SendScramCondition
extern PreScramConditionHandle _UTL_GetPreScramConditionHandle(void);
#define UTL_GetPreScramConditionHandle _UTL_GetPreScramConditionHandle
extern void _UTL_SetPreScramConditionAddr(PreScramConditionHandle, RadioButton, CheckButton);
#define UTL_SetPreScramConditionAddr _UTL_SetPreScramConditionAddr
extern void _UTL_SetPreScramConditionAlpgUnit(PreScramConditionHandle, RadioButton);
#define UTL_SetPreScramConditionAlpgUnit _UTL_SetPreScramConditionAlpgUnit
extern void _UTL_SetPreScramConditionMode(PreScramConditionHandle, RadioButton);
#define UTL_SetPreScramConditionMode _UTL_SetPreScramConditionMode
extern void _UTL_SetPreScramConditionMixMode(PreScramConditionHandle, CheckButton);
#define UTL_SetPreScramConditionMixMode _UTL_SetPreScramConditionMixMode
extern void _UTL_AddPreScramConditionWriteSignal(PreScramConditionHandle, RadioButton);
#define UTL_AddPreScramConditionWriteSignal _UTL_AddPreScramConditionWriteSignal
extern void _UTL_ClearPreScramConditionWriteSignal(PreScramConditionHandle);
#define UTL_ClearPreScramConditionWriteSignal _UTL_ClearPreScramConditionWriteSignal
extern void _UTL_SendPreScramCondition(PreScramConditionHandle);
#define UTL_SendPreScramCondition _UTL_SendPreScramCondition
extern BurstScramHandle _UTL_GetBurstScramHandle(void);
#define UTL_GetBurstScramHandle _UTL_GetBurstScramHandle
extern void _UTL_SetBurstScramMode(BurstScramHandle,CheckButton);
#define UTL_SetBurstScramMode _UTL_SetBurstScramMode
extern void _UTL_SetBurstScramDdrType(BurstScramHandle,RadioButton);
#define UTL_SetBurstScramDdrType _UTL_SetBurstScramDdrType
extern void _UTL_SetBurstScramBaseFileName(BurstScramHandle,char *);
#define UTL_SetBurstScramBaseFileName _UTL_SetBurstScramBaseFileName
extern void _UTL_SetBurstScramDataRate(BurstScramHandle,USlider);
#define UTL_SetBurstScramDataRate _UTL_SetBurstScramDataRate
extern void _UTL_SetBurstScramLength(BurstScramHandle,USlider);
#define UTL_SetBurstScramLength _UTL_SetBurstScramLength
extern void _UTL_SetBurstScramWrapType(BurstScramHandle,RadioButton);
#define UTL_SetBurstScramWrapType _UTL_SetBurstScramWrapType
extern void _UTL_AddBurstScramWriteSignal(BurstScramHandle,RadioButton);
#define UTL_AddBurstScramWriteSignal _UTL_AddBurstScramWriteSignal
extern void _UTL_ClearBurstScramWriteSignal(BurstScramHandle);
#define UTL_ClearBurstScramWriteSignal _UTL_ClearBurstScramWriteSignal
extern void _UTL_SetBurstScramAddrUnit(BurstScramHandle, RadioButton, CheckButton);
#define UTL_SetBurstScramAddrUnit _UTL_SetBurstScramAddrUnit
extern void _UTL_SetBurstScramBankAddrLoadUnit(BurstScramHandle, RadioButton, CheckButton);
#define UTL_SetBurstScramBankAddrLoadUnit _UTL_SetBurstScramBankAddrLoadUnit
extern void _UTL_SendBurstScram(BurstScramHandle);
#define UTL_SendBurstScram _UTL_SendBurstScram
extern void _UTL_WriteRegUs(RadioButton, USlider *, int, RadioButton);
#define UTL_WriteRegUs _UTL_WriteRegUs
extern RegHandle _UTL_GetRegHandle(void);
#define UTL_GetRegHandle _UTL_GetRegHandle
extern void _UTL_ClearRegHandle(RegHandle);
#define UTL_ClearRegHandle _UTL_ClearRegHandle
extern void _UTL_SetRegDirection(RegHandle, RadioButton);
#define UTL_SetRegDirection _UTL_SetRegDirection
extern void _UTL_SetRegUs(RegHandle, RadioButton, RadioButton, USlider);
#define UTL_SetRegUs _UTL_SetRegUs
extern void _UTL_SetRegRb(RegHandle, RadioButton, USlider);
#define UTL_SetRegRb _UTL_SetRegRb
extern void _UTL_SetRegBar1(RegHandle, RadioButton, USlider);
#define UTL_SetRegBar1 _UTL_SetRegBar1
extern void _UTL_SetRegJar(RegHandle, RadioButton, USlider);
#define UTL_SetRegJar _UTL_SetRegJar
extern void _UTL_SetRegDre1(RegHandle, RadioButton);
#define UTL_SetRegDre1 _UTL_SetRegDre1
extern void _UTL_SetRegDre2(RegHandle, RadioButton);
#define UTL_SetRegDre2 _UTL_SetRegDre2
extern void _UTL_SetRegCpe1(RegHandle, RadioButton);
#define UTL_SetRegCpe1 _UTL_SetRegCpe1
extern void _UTL_SetRegCpe2(RegHandle, RadioButton);
#define UTL_SetRegCpe2 _UTL_SetRegCpe2
extern void _UTL_SetRegIdx1(RegHandle, RadioButton, USlider);
#define UTL_SetRegIdx1 _UTL_SetRegIdx1
extern void _UTL_SetRegIdx2(RegHandle, RadioButton, USlider);
#define UTL_SetRegIdx2 _UTL_SetRegIdx2
extern void _UTL_SetRegIdx3(RegHandle, RadioButton, USlider);
#define UTL_SetRegIdx3 _UTL_SetRegIdx3
extern void _UTL_SetRegIdx4(RegHandle, RadioButton, USlider);
#define UTL_SetRegIdx4 _UTL_SetRegIdx4
extern void _UTL_SetRegIdx5(RegHandle, RadioButton, USlider);
#define UTL_SetRegIdx5 _UTL_SetRegIdx5
extern void _UTL_SetRegIdx6(RegHandle, RadioButton, USlider);
#define UTL_SetRegIdx6 _UTL_SetRegIdx6
extern void _UTL_SetRegIdx7(RegHandle, RadioButton, USlider);
#define UTL_SetRegIdx7 _UTL_SetRegIdx7
extern void _UTL_SetRegIdx8(RegHandle, RadioButton, USlider);
#define UTL_SetRegIdx8 _UTL_SetRegIdx8
extern void _UTL_SetRegXmax(RegHandle, RadioButton, USlider);
#define UTL_SetRegXmax _UTL_SetRegXmax
extern void _UTL_SetRegYmax(RegHandle, RadioButton, USlider);
#define UTL_SetRegYmax _UTL_SetRegYmax
extern void _UTL_SetRegZmax(RegHandle, RadioButton, USlider);
#define UTL_SetRegZmax _UTL_SetRegZmax
extern void _UTL_SetRegLmax(RegHandle, RadioButton, USlider);
#define UTL_SetRegLmax _UTL_SetRegLmax
extern void _UTL_SetRegHmax(RegHandle, RadioButton, USlider);
#define UTL_SetRegHmax _UTL_SetRegHmax
extern void _UTL_SetRegXh(RegHandle, RadioButton, USlider);
#define UTL_SetRegXh _UTL_SetRegXh
extern void _UTL_SetRegYh(RegHandle, RadioButton, USlider);
#define UTL_SetRegYh _UTL_SetRegYh
extern void _UTL_SetRegZh(RegHandle, RadioButton, USlider);
#define UTL_SetRegZh _UTL_SetRegZh
extern void _UTL_SetRegD1(RegHandle, RadioButton, USlider);
#define UTL_SetRegD1 _UTL_SetRegD1
extern void _UTL_SetRegD2(RegHandle, RadioButton, USlider);
#define UTL_SetRegD2 _UTL_SetRegD2
extern void _UTL_SetRegD3(RegHandle, RadioButton, USlider);
#define UTL_SetRegD3 _UTL_SetRegD3
extern void _UTL_SetRegD4(RegHandle, RadioButton, USlider);
#define UTL_SetRegD4 _UTL_SetRegD4
extern void _UTL_SetRegDsd(RegHandle, RadioButton, USlider);
#define UTL_SetRegDsd _UTL_SetRegDsd
extern void _UTL_SetRegTph(RegHandle, RadioButton, USlider);
#define UTL_SetRegTph _UTL_SetRegTph
extern void _UTL_SetRegDcmr(RegHandle, RadioButton, USlider);
#define UTL_SetRegDcmr _UTL_SetRegDcmr
extern void _UTL_SetRegCd(RegHandle, RadioButton, USlider);
#define UTL_SetRegCd _UTL_SetRegCd
extern void _UTL_SetRegAlpgUnit (RegHandle, RadioButton);
#define UTL_SetRegAlpgUnit _UTL_SetRegAlpgUnit
extern void _UTL_SetRegTimerCycleCnt(RegHandle, RadioButton, RadioButton, USlider);
#define UTL_SetRegTimerCycleCnt _UTL_SetRegTimerCycleCnt
extern void _UTL_SetRegTimerTime(RegHandle, RadioButton, double);
#define UTL_SetRegTimerTime _UTL_SetRegTimerTime
extern void _UTL_SetRegUpdateUnitNumber(RegHandle, RadioButton);
#define UTL_SetRegUpdateUnitNumber _UTL_SetRegUpdateUnitNumber
extern void _UTL_SendReg(RegHandle);
#define UTL_SendReg _UTL_SendReg
extern void _UTL_ResetReg(RegHandle);
#define UTL_ResetReg _UTL_ResetReg
extern USlider _UTL_ReadUSRegister(RadioButton, RadioButton);
#define UTL_ReadUSRegister _UTL_ReadUSRegister
extern RadioButton _UTL_ReadRBRegister(RadioButton);
#define UTL_ReadRBRegister _UTL_ReadRBRegister
extern RegMemoryHandle _UTL_GetRegMemoryHandle( void );
#define UTL_GetRegMemoryHandle _UTL_GetRegMemoryHandle
extern void _UTL_SetRegMemoryTarget ( RegMemoryHandle, RadioButton );
#define UTL_SetRegMemoryTarget _UTL_SetRegMemoryTarget
extern void _UTL_SetRegMemoryStartAddr( RegMemoryHandle, USlider );
#define UTL_SetRegMemoryStartAddr _UTL_SetRegMemoryStartAddr
extern void _UTL_SetRegMemoryStopAddr( RegMemoryHandle, USlider );
#define UTL_SetRegMemoryStopAddr _UTL_SetRegMemoryStopAddr
extern void _UTL_WriteRegMemory ( RegMemoryHandle, void *, USlider );
#define UTL_WriteRegMemory _UTL_WriteRegMemory
extern TimerModeHandle _UTL_GetTimerModeHandle (void);
#define UTL_GetTimerModeHandle _UTL_GetTimerModeHandle
extern void _UTL_AddTimerMode (TimerModeHandle hid, RadioButton timer, RadioButton mode);
#define UTL_AddTimerMode _UTL_AddTimerMode
extern void _UTL_SetTimerModeDirection (TimerModeHandle hid, RadioButton direct);
#define UTL_SetTimerModeDirection _UTL_SetTimerModeDirection
extern void _UTL_SendTimerMode (TimerModeHandle hid);
#define UTL_SendTimerMode _UTL_SendTimerMode
extern IdxModeHandle _UTL_GetIdxModeHandle (void);
#define UTL_GetIdxModeHandle _UTL_GetIdxModeHandle
extern void _UTL_SetIdxMode (IdxModeHandle hid, RadioButton mode);
#define UTL_SetIdxMode _UTL_SetIdxMode
extern void _UTL_SendIdxMode (IdxModeHandle hid);
#define UTL_SendIdxMode _UTL_SendIdxMode
extern void _UTL_UpdateIdxMode (IdxModeHandle hid);
#define UTL_UpdateIdxMode _UTL_UpdateIdxMode
extern int _UTL_GetIdxMode (IdxModeHandle hid, RadioButton *mode);
#define UTL_GetIdxMode _UTL_GetIdxMode
extern ReadMpatPcHandle _UTL_GetReadMpatPcHandle(void);
#define UTL_GetReadMpatPcHandle _UTL_GetReadMpatPcHandle
extern void _UTL_SetReadMpatStartName(ReadMpatPcHandle,char *);
#define UTL_SetReadMpatStartName _UTL_SetReadMpatStartName
extern void _UTL_SetReadMpatLabelName(ReadMpatPcHandle,char *);
#define UTL_SetReadMpatLabelName _UTL_SetReadMpatLabelName
extern void _UTL_SetReadMpatModuleName(ReadMpatPcHandle,char *);
#define UTL_SetReadMpatModuleName _UTL_SetReadMpatModuleName
extern void _UTL_SetReadMpatFileName(ReadMpatPcHandle,char *);
#define UTL_SetReadMpatFileName _UTL_SetReadMpatFileName
extern RadioButton _UTL_ReadMpatStartPc(ReadMpatPcHandle, USlider *);
#define UTL_ReadMpatStartPc _UTL_ReadMpatStartPc
extern RadioButton _UTL_ReadMpatLabelPc(ReadMpatPcHandle, USlider *);
#define UTL_ReadMpatLabelPc _UTL_ReadMpatLabelPc
extern AriramHandle _UTL_GetAriramHandle(void);
#define UTL_GetAriramHandle _UTL_GetAriramHandle
extern void _UTL_SetAriramAlpgUnit(AriramHandle, RadioButton);
#define UTL_SetAriramAlpgUnit _UTL_SetAriramAlpgUnit
extern void _UTL_SetAriramMode(AriramHandle, RadioButton);
#define UTL_SetAriramMode _UTL_SetAriramMode
extern void _UTL_SendAriram(AriramHandle);
#define UTL_SendAriram _UTL_SendAriram
extern PdsDataHandle _UTL_GetPdsDataHandle (void);
#define UTL_GetPdsDataHandle _UTL_GetPdsDataHandle
extern void _UTL_SetPdsDataAlpgUnit (PdsDataHandle hid, RadioButton alpg);
#define UTL_SetPdsDataAlpgUnit _UTL_SetPdsDataAlpgUnit
extern void _UTL_SetPdsDataDirection (PdsDataHandle hid, RadioButton direct);
#define UTL_SetPdsDataDirection _UTL_SetPdsDataDirection
extern void _UTL_SetPdsDataPdsUnit (PdsDataHandle hid, RadioButton pds);
#define UTL_SetPdsDataPdsUnit _UTL_SetPdsDataPdsUnit
extern void _UTL_SetPdsDataSelectorDa (PdsDataHandle hid, RadioButton da);
#define UTL_SetPdsDataSelectorDa _UTL_SetPdsDataSelectorDa
extern void _UTL_SetPdsDataSelectorDb (PdsDataHandle hid, RadioButton db);
#define UTL_SetPdsDataSelectorDb _UTL_SetPdsDataSelectorDb
extern void _UTL_SendPdsData (PdsDataHandle hid);
#define UTL_SendPdsData _UTL_SendPdsData
extern PatDelayHandle _UTL_GetPatDelayHandle (void);
#define UTL_GetPatDelayHandle _UTL_GetPatDelayHandle
extern void _UTL_AddPatDelayCycle (PatDelayHandle hid, RadioButton data, USlider delay_val);
#define UTL_AddPatDelayCycle _UTL_AddPatDelayCycle
extern void _UTL_SetPatDelayAlpgUnit (PatDelayHandle hid, RadioButton alpg);
#define UTL_SetPatDelayAlpgUnit _UTL_SetPatDelayAlpgUnit
extern void _UTL_SendPatDelay (PatDelayHandle hid);
#define UTL_SendPatDelay _UTL_SendPatDelay
extern StrbFailCounterConditionHandle _UTL_GetStrbFailCounterConditionHandle(void);
#define UTL_GetStrbFailCounterConditionHandle _UTL_GetStrbFailCounterConditionHandle
extern void _UTL_AddStrbFailCounterConditionStrbChannelAllDut(StrbFailCounterConditionHandle, RadioButton);
#define UTL_AddStrbFailCounterConditionStrbChannelAllDut _UTL_AddStrbFailCounterConditionStrbChannelAllDut
extern void _UTL_AddStrbFailCounterConditionStrbChannelByDut(StrbFailCounterConditionHandle, UT_DUT, RadioButton);
#define UTL_AddStrbFailCounterConditionStrbChannelByDut _UTL_AddStrbFailCounterConditionStrbChannelByDut
extern void _UTL_ClearStrbFailCounterConditionStrbChannelAllDut(StrbFailCounterConditionHandle);
#define UTL_ClearStrbFailCounterConditionStrbChannelAllDut _UTL_ClearStrbFailCounterConditionStrbChannelAllDut
extern void _UTL_ClearStrbFailCounterConditionStrbChannelByDut(StrbFailCounterConditionHandle, UT_DUT);
#define UTL_ClearStrbFailCounterConditionStrbChannelByDut _UTL_ClearStrbFailCounterConditionStrbChannelByDut
extern void _UTL_SetStrbFailCounterConditionFailStopAllDut(StrbFailCounterConditionHandle, CheckButton);
#define UTL_SetStrbFailCounterConditionFailStopAllDut _UTL_SetStrbFailCounterConditionFailStopAllDut
extern void _UTL_SetStrbFailCounterConditionFailStopByDut(StrbFailCounterConditionHandle, UT_DUT, CheckButton);
#define UTL_SetStrbFailCounterConditionFailStopByDut _UTL_SetStrbFailCounterConditionFailStopByDut
extern void _UTL_SetStrbFailCounterConditionLimitAllDut(StrbFailCounterConditionHandle, Slider);
#define UTL_SetStrbFailCounterConditionLimitAllDut _UTL_SetStrbFailCounterConditionLimitAllDut
extern void _UTL_SetStrbFailCounterConditionLimitByDut(StrbFailCounterConditionHandle, UT_DUT, Slider);
#define UTL_SetStrbFailCounterConditionLimitByDut _UTL_SetStrbFailCounterConditionLimitByDut
extern void _UTL_SetStrbFailCounterConditionPin(StrbFailCounterConditionHandle, UT_PIN);
#define UTL_SetStrbFailCounterConditionPin _UTL_SetStrbFailCounterConditionPin
extern void _UTL_SendStrbFailCounterCondition(StrbFailCounterConditionHandle);
#define UTL_SendStrbFailCounterCondition _UTL_SendStrbFailCounterCondition
extern StrbFailCounterHandle _UTL_GetStrbFailCounterHandle(void);
#define UTL_GetStrbFailCounterHandle _UTL_GetStrbFailCounterHandle
extern void _UTL_SetStrbFailCounterPin(StrbFailCounterHandle, UT_PIN);
#define UTL_SetStrbFailCounterPin _UTL_SetStrbFailCounterPin
extern void _UTL_SetStrbFailCounterDut(StrbFailCounterHandle, UT_DUT);
#define UTL_SetStrbFailCounterDut _UTL_SetStrbFailCounterDut
extern void _UTL_UpdateStrbFailCounter(StrbFailCounterHandle);
#define UTL_UpdateStrbFailCounter _UTL_UpdateStrbFailCounter
extern int _UTL_GetStrbFailCounterValue(StrbFailCounterHandle, Slider *);
#define UTL_GetStrbFailCounterValue _UTL_GetStrbFailCounterValue
extern int _UTL_GetStrbFailCounterMaxFail(StrbFailCounterHandle, CheckButton *);
#define UTL_GetStrbFailCounterMaxFail _UTL_GetStrbFailCounterMaxFail
extern PseudoRandomHandle _UTL_GetPseudoRandomHandle (void);
#define UTL_GetPseudoRandomHandle _UTL_GetPseudoRandomHandle
extern void _UTL_SetPseudoRandomAlpgUnit (PseudoRandomHandle, RadioButton);
#define UTL_SetPseudoRandomAlpgUnit _UTL_SetPseudoRandomAlpgUnit
extern void _UTL_SetPseudoRandomDirection (PseudoRandomHandle, RadioButton);
#define UTL_SetPseudoRandomDirection _UTL_SetPseudoRandomDirection
extern void _UTL_SetPseudoRandomGenerationMethod (PseudoRandomHandle, RadioButton);
#define UTL_SetPseudoRandomGenerationMethod _UTL_SetPseudoRandomGenerationMethod
extern void _UTL_SetPseudoRandomUpdateUnitNumber (PseudoRandomHandle, RadioButton);
#define UTL_SetPseudoRandomUpdateUnitNumber _UTL_SetPseudoRandomUpdateUnitNumber
extern void _UTL_AddPseudoRandomTermOfPolynomial (PseudoRandomHandle, RadioButton);
#define UTL_AddPseudoRandomTermOfPolynomial _UTL_AddPseudoRandomTermOfPolynomial
extern void _UTL_ClearPseudoRandomTermOfPolynomial (PseudoRandomHandle);
#define UTL_ClearPseudoRandomTermOfPolynomial _UTL_ClearPseudoRandomTermOfPolynomial
extern void _UTL_ResetPseudoRandom (PseudoRandomHandle);
#define UTL_ResetPseudoRandom _UTL_ResetPseudoRandom
extern void _UTL_SendPseudoRandom (PseudoRandomHandle);
#define UTL_SendPseudoRandom _UTL_SendPseudoRandom
extern DcSwitchHandle _UTL_GetDcSwitchHandle( void );
#define UTL_GetDcSwitchHandle _UTL_GetDcSwitchHandle
extern void _UTL_SetDcSwitch( DcSwitchHandle , RadioButton );
#define UTL_SetDcSwitch _UTL_SetDcSwitch
extern void _UTL_SendDcSwitch( DcSwitchHandle );
#define UTL_SendDcSwitch _UTL_SendDcSwitch
extern void _UTL_UpdateDcSwitch( DcSwitchHandle );
#define UTL_UpdateDcSwitch _UTL_UpdateDcSwitch
extern int _UTL_GetDcSwitch( DcSwitchHandle h, RadioButton *val );
#define UTL_GetDcSwitch _UTL_GetDcSwitch
extern DcHandle _UTL_GetDcHandle( void );
#define UTL_GetDcHandle _UTL_GetDcHandle
extern void _UTL_SetDcMode( DcHandle , RadioButton );
#define UTL_SetDcMode _UTL_SetDcMode
extern void _UTL_SetDcSource( DcHandle , DSlider );
#define UTL_SetDcSource _UTL_SetDcSource
extern void _UTL_SetDcSrange( DcHandle , DSlider , DSlider );
#define UTL_SetDcSrange _UTL_SetDcSrange
extern void _UTL_SetDcMrange( DcHandle , DSlider , DSlider );
#define UTL_SetDcMrange _UTL_SetDcMrange
extern void _UTL_SetDcPclamp( DcHandle , DSlider );
#define UTL_SetDcPclamp _UTL_SetDcPclamp
extern void _UTL_SetDcMclamp( DcHandle , DSlider );
#define UTL_SetDcMclamp _UTL_SetDcMclamp
extern void _UTL_SetDcFilter( DcHandle , RadioButton );
#define UTL_SetDcFilter _UTL_SetDcFilter
extern void _UTL_SetDcLimitHigh( DcHandle , DSlider , CheckButton );
#define UTL_SetDcLimitHigh _UTL_SetDcLimitHigh
extern void _UTL_SetDcLimitLow( DcHandle , DSlider , CheckButton );
#define UTL_SetDcLimitLow _UTL_SetDcLimitLow
extern void _UTL_SetDcMeasCnt( DcHandle , Slider );
#define UTL_SetDcMeasCnt _UTL_SetDcMeasCnt
extern void _UTL_SetDcSlewRate( DcHandle , DSlider );
#define UTL_SetDcSlewRate _UTL_SetDcSlewRate
extern void _UTL_AddDcWetItem( DcHandle , RadioButton );
#define UTL_AddDcWetItem _UTL_AddDcWetItem
extern void _UTL_ClearDcWetItem( DcHandle );
#define UTL_ClearDcWetItem _UTL_ClearDcWetItem
extern void _UTL_SendDc( DcHandle , RadioButton );
#define UTL_SendDc _UTL_SendDc
extern SettlingTimeHandle _UTL_GetSettlingTimeHandle( void );
#define UTL_GetSettlingTimeHandle _UTL_GetSettlingTimeHandle
extern void _UTL_SetSettlingTime ( SettlingTimeHandle, DSlider );
#define UTL_SetSettlingTime _UTL_SetSettlingTime
extern void _UTL_SetSettlingTimeAfterRon ( SettlingTimeHandle, DSlider );
#define UTL_SetSettlingTimeAfterRon _UTL_SetSettlingTimeAfterRon
extern void _UTL_SetSettlingTimeAfterRof ( SettlingTimeHandle, DSlider );
#define UTL_SetSettlingTimeAfterRof _UTL_SetSettlingTimeAfterRof
extern void _UTL_SendSettlingTime ( SettlingTimeHandle );
#define UTL_SendSettlingTime _UTL_SendSettlingTime
extern DctHandle _UTL_GetDctHandle( void );
#define UTL_GetDctHandle _UTL_GetDctHandle
extern void _UTL_SetDctPinList( DctHandle , char * );
#define UTL_SetDctPinList _UTL_SetDctPinList
extern void _UTL_SetDctRelayMode( DctHandle , RadioButton );
#define UTL_SetDctRelayMode _UTL_SetDctRelayMode
extern void _UTL_SetDctPinVi( DctHandle , CheckButton );
#define UTL_SetDctPinVi _UTL_SetDctPinVi
extern void _UTL_SetDctPinVo( DctHandle , CheckButton );
#define UTL_SetDctPinVo _UTL_SetDctPinVo
extern void _UTL_SetDctPinVihh( DctHandle , CheckButton );
#define UTL_SetDctPinVihh _UTL_SetDctPinVihh
extern void _UTL_SetDctPinHvDr( DctHandle , CheckButton );
#define UTL_SetDctPinHvDr _UTL_SetDctPinHvDr
extern void _UTL_SetDctPinTerm( DctHandle , CheckButton );
#define UTL_SetDctPinTerm _UTL_SetDctPinTerm
extern void _UTL_SetDctPinPl( DctHandle , RadioButton );
#define UTL_SetDctPinPl _UTL_SetDctPinPl
extern void _UTL_SetDctAltMode( DctHandle , RadioButton );
#define UTL_SetDctAltMode _UTL_SetDctAltMode
extern void _UTL_SetDctAltSource( DctHandle , DSlider );
#define UTL_SetDctAltSource _UTL_SetDctAltSource
extern void _UTL_SetDctAltPclamp( DctHandle , DSlider );
#define UTL_SetDctAltPclamp _UTL_SetDctAltPclamp
extern void _UTL_SetDctAltMclamp( DctHandle , DSlider );
#define UTL_SetDctAltMclamp _UTL_SetDctAltMclamp
extern void _UTL_SetDctAfterDcOn( DctHandle , RadioButton );
#define UTL_SetDctAfterDcOn _UTL_SetDctAfterDcOn
extern void _UTL_SetDctBeforeFunc( DctHandle , void (*)(void) );
#define UTL_SetDctBeforeFunc _UTL_SetDctBeforeFunc
extern void _UTL_SetDctAfterFunc( DctHandle , void (*)(void) );
#define UTL_SetDctAfterFunc _UTL_SetDctAfterFunc
extern void _UTL_SetDctFailAction( DctHandle , void (*)(void) );
#define UTL_SetDctFailAction _UTL_SetDctFailAction
extern void _UTL_SetDctPassAction( DctHandle , void (*)(void) );
#define UTL_SetDctPassAction _UTL_SetDctPassAction
extern void _UTL_SetDctHidarCondition( DctHandle , HidarConfigHandle );
#define UTL_SetDctHidarCondition _UTL_SetDctHidarCondition
extern void _UTL_SetDctAutoRangeMode( DctHandle , CheckButton );
#define UTL_SetDctAutoRangeMode _UTL_SetDctAutoRangeMode
extern void _UTL_SetDctGoNogoOnly( DctHandle , CheckButton );
#define UTL_SetDctGoNogoOnly _UTL_SetDctGoNogoOnly
extern void _UTL_SetDctAutoTestName( DctHandle , CheckButton );
#define UTL_SetDctAutoTestName _UTL_SetDctAutoTestName
extern void _UTL_MeasDct( DctHandle );
#define UTL_MeasDct _UTL_MeasDct
extern void _UTL_StartDct( DctHandle );
#define UTL_StartDct _UTL_StartDct
extern void _UTL_SetDctReferenceMode( RadioButton );
#define UTL_SetDctReferenceMode _UTL_SetDctReferenceMode
extern RadioButton _UTL_ReadDctReferenceMode( void );
#define UTL_ReadDctReferenceMode _UTL_ReadDctReferenceMode
extern void _UTL_SetDctSepaDrCtrlMode( RadioButton );
#define UTL_SetDctSepaDrCtrlMode _UTL_SetDctSepaDrCtrlMode
extern RadioButton _UTL_ReadDctSepaDrCtrlMode( void );
#define UTL_ReadDctSepaDrCtrlMode _UTL_ReadDctSepaDrCtrlMode
extern AdcHandle _UTL_GetAdcHandle ( void );
#define UTL_GetAdcHandle _UTL_GetAdcHandle
extern void _UTL_SetAdcPgEnable ( AdcHandle, CheckButton );
#define UTL_SetAdcPgEnable _UTL_SetAdcPgEnable
extern void _UTL_SetAdcStartCycle ( AdcHandle, RadioButton );
#define UTL_SetAdcStartCycle _UTL_SetAdcStartCycle
extern void _UTL_SetAdcInput ( AdcHandle, RadioButton );
#define UTL_SetAdcInput _UTL_SetAdcInput
extern void _UTL_SetAdcPinList ( AdcHandle , char * );
#define UTL_SetAdcPinList _UTL_SetAdcPinList
extern void _UTL_SetAdcMeasMode ( AdcHandle, RadioButton );
#define UTL_SetAdcMeasMode _UTL_SetAdcMeasMode
extern void _UTL_SetAdcHistoryMode ( AdcHandle, CheckButton );
#define UTL_SetAdcHistoryMode _UTL_SetAdcHistoryMode
extern void _UTL_SetAdcSettlingTime ( AdcHandle, DSlider );
#define UTL_SetAdcSettlingTime _UTL_SetAdcSettlingTime
extern void _UTL_SendAdc ( AdcHandle, RadioButton );
#define UTL_SendAdc _UTL_SendAdc
void _UTL_WaitAdc ( RadioButton );
#define UTL_WaitAdc _UTL_WaitAdc
void _UTL_ResetAdcHistoryCount ( RadioButton );
#define UTL_ResetAdcHistoryCount _UTL_ResetAdcHistoryCount
USlider _UTL_ReadAdcHistoryCount ( RadioButton , CheckButton * );
#define UTL_ReadAdcHistoryCount _UTL_ReadAdcHistoryCount
RadioButton _UTL_GetAdcDutGroupMaxNumber( RadioButton );
#define UTL_GetAdcDutGroupMaxNumber _UTL_GetAdcDutGroupMaxNumber
void _UTL_WriteAdcDutGroupNumber ( RadioButton , RadioButton );
#define UTL_WriteAdcDutGroupNumber _UTL_WriteAdcDutGroupNumber
RadioButton _UTL_ReadAdcDutGroupNumber ( RadioButton );
#define UTL_ReadAdcDutGroupNumber _UTL_ReadAdcDutGroupNumber
DutCursor _UTL_GetAdcDutGroupDutCursor( RadioButton , RadioButton );
#define UTL_GetAdcDutGroupDutCursor _UTL_GetAdcDutGroupDutCursor
extern SamplingRateHandle _UTL_GetSamplingRateHandle( void );
#define UTL_GetSamplingRateHandle _UTL_GetSamplingRateHandle
extern void _UTL_SetSamplingRate ( SettlingTimeHandle, DSlider );
#define UTL_SetSamplingRate _UTL_SetSamplingRate
extern void _UTL_SendSamplingRate ( SamplingRateHandle );
#define UTL_SendSamplingRate _UTL_SendSamplingRate
extern DcComparatorHandle _UTL_GetDcComparatorHandle( void );
#define UTL_GetDcComparatorHandle _UTL_GetDcComparatorHandle
extern void _UTL_SetDcComparatorLimitHigh( DcComparatorHandle , DSlider );
#define UTL_SetDcComparatorLimitHigh _UTL_SetDcComparatorLimitHigh
extern void _UTL_SetDcComparatorLimitLow( DcComparatorHandle , DSlider );
#define UTL_SetDcComparatorLimitLow _UTL_SetDcComparatorLimitLow
extern void _UTL_SendDcComparator( DcComparatorHandle );
#define UTL_SendDcComparator _UTL_SendDcComparator
extern DcComparatorReadPinHandle _UTL_GetDcComparatorReadPinHandle( void );
#define UTL_GetDcComparatorReadPinHandle _UTL_GetDcComparatorReadPinHandle
extern void _UTL_SetDcComparatorReadPinDut( DcComparatorReadPinHandle , UT_DUT );
#define UTL_SetDcComparatorReadPinDut _UTL_SetDcComparatorReadPinDut
extern void _UTL_SetDcComparatorReadPinNumber( DcComparatorReadPinHandle , UT_PIN );
#define UTL_SetDcComparatorReadPinNumber _UTL_SetDcComparatorReadPinNumber
extern void _UTL_SetDcComparatorReadPinMode( DcComparatorReadPinHandle , RadioButton );
#define UTL_SetDcComparatorReadPinMode _UTL_SetDcComparatorReadPinMode
extern FctHandle _UTL_GetFctHandle (void);
#define UTL_GetFctHandle _UTL_GetFctHandle
extern void _UTL_SetFctContinue (FctHandle, CheckButton);
#define UTL_SetFctContinue _UTL_SetFctContinue
extern void _UTL_SetFctNoWait (FctHandle, CheckButton);
#define UTL_SetFctNoWait _UTL_SetFctNoWait
extern void _UTL_SetFctNoClear (FctHandle, CheckButton);
#define UTL_SetFctNoClear _UTL_SetFctNoClear
extern void _UTL_SetFctFailInhibit (FctHandle, CheckButton);
#define UTL_SetFctFailInhibit _UTL_SetFctFailInhibit
extern void _UTL_SetFctRepeat (FctHandle, CheckButton);
#define UTL_SetFctRepeat _UTL_SetFctRepeat
extern void _UTL_SetFctSronInhibit (FctHandle, CheckButton);
#define UTL_SetFctSronInhibit _UTL_SetFctSronInhibit
extern void _UTL_SetFctMpatTransferInhibit(FctHandle, CheckButton);
#define UTL_SetFctMpatTransferInhibit _UTL_SetFctMpatTransferInhibit
extern void _UTL_SetFctMpatTransferDataInhibit(FctHandle, RadioButton, CheckButton);
#define UTL_SetFctMpatTransferDataInhibit _UTL_SetFctMpatTransferDataInhibit
extern void _UTL_SetFctStartLabelNameOfMpatSelector(FctHandle, char *, char *);
#define UTL_SetFctStartLabelNameOfMpatSelector _UTL_SetFctStartLabelNameOfMpatSelector
extern void _UTL_SetFctMpatDataFileNameWithMpatSelector(FctHandle , char *, char *);
#define UTL_SetFctMpatDataFileNameWithMpatSelector _UTL_SetFctMpatDataFileNameWithMpatSelector
extern void _UTL_SetFctMpatName (FctHandle, char *);
#define UTL_SetFctMpatName _UTL_SetFctMpatName
extern void _UTL_SetFctStartPc (FctHandle, USlider);
#define UTL_SetFctStartPc _UTL_SetFctStartPc
extern void _UTL_SetFctTimeLimit (FctHandle, CheckButton, DSlider);
#define UTL_SetFctTimeLimit _UTL_SetFctTimeLimit
extern void _UTL_SetFctTimeLimitAction (FctHandle, void (*)(void));
#define UTL_SetFctTimeLimitAction _UTL_SetFctTimeLimitAction
extern void _UTL_SetFctFailAction (FctHandle, void (*)(void));
#define UTL_SetFctFailAction _UTL_SetFctFailAction
extern void _UTL_SetFctPassAction (FctHandle, void (*)(void));
#define UTL_SetFctPassAction _UTL_SetFctPassAction
extern void _UTL_SetFctBeforeFunc (FctHandle, void (*)(void));
#define UTL_SetFctBeforeFunc _UTL_SetFctBeforeFunc
extern void _UTL_SetFctStartFunc (FctHandle, void (*)(void));
#define UTL_SetFctStartFunc _UTL_SetFctStartFunc
extern void _UTL_SetFctAfterFunc (FctHandle, void (*)(void));
#define UTL_SetFctAfterFunc _UTL_SetFctAfterFunc
extern void _UTL_MeasFct (FctHandle);
#define UTL_MeasFct _UTL_MeasFct
extern void _UTL_StartFct (FctHandle);
#define UTL_StartFct _UTL_StartFct
extern void _UTL_StopFct (void);
#define UTL_StopFct _UTL_StopFct
extern VpatHandle _UTL_GetVpatHandle (void);
#define UTL_GetVpatHandle _UTL_GetVpatHandle
extern void _UTL_SetVpatName (VpatHandle, char *);
#define UTL_SetVpatName _UTL_SetVpatName
extern void _UTL_SetVpatFailInhibit (VpatHandle, CheckButton);
#define UTL_SetVpatFailInhibit _UTL_SetVpatFailInhibit
extern void _UTL_SetVpatFailAction (VpatHandle, void (*)(void));
#define UTL_SetVpatFailAction _UTL_SetVpatFailAction
extern void _UTL_SetVpatPassAction (VpatHandle, void (*)(void));
#define UTL_SetVpatPassAction _UTL_SetVpatPassAction
extern void _UTL_SetVpatBeforeFunc (VpatHandle, void (*)(void));
#define UTL_SetVpatBeforeFunc _UTL_SetVpatBeforeFunc
extern void _UTL_SetVpatStartFunc (VpatHandle, void (*)(void));
#define UTL_SetVpatStartFunc _UTL_SetVpatStartFunc
extern void _UTL_SetVpatAfterFunc (VpatHandle, void (*)(void));
#define UTL_SetVpatAfterFunc _UTL_SetVpatAfterFunc
extern void _UTL_MeasVpat (VpatHandle);
#define UTL_MeasVpat _UTL_MeasVpat
extern DctReadPinHandle _UTL_GetDctReadPinHandle( void );
#define UTL_GetDctReadPinHandle _UTL_GetDctReadPinHandle
extern void _UTL_SetDctReadPinDut ( DctReadPinHandle , UT_DUT );
#define UTL_SetDctReadPinDut _UTL_SetDctReadPinDut
extern void _UTL_SetDctReadPinNumber ( DctReadPinHandle , UT_PIN );
#define UTL_SetDctReadPinNumber _UTL_SetDctReadPinNumber
extern void _UTL_SetDctReadPinType ( DctReadPinHandle , RadioButton );
#define UTL_SetDctReadPinType _UTL_SetDctReadPinType
extern void _UTL_SetDctReadPinMode ( DctReadPinHandle , RadioButton );
#define UTL_SetDctReadPinMode _UTL_SetDctReadPinMode
extern void _UTL_SetDctReadPinHistoryNumber ( DctReadPinHandle , RadioButton );
#define UTL_SetDctReadPinHistoryNumber _UTL_SetDctReadPinHistoryNumber
extern DSlider _UTL_ReadDctPinData ( DctReadPinHandle );
#define UTL_ReadDctPinData _UTL_ReadDctPinData
extern CheckButton _UTL_ReadDctPin ( DctReadPinHandle );
#define UTL_ReadDctPin _UTL_ReadDctPin
extern RadioButton _UTL_ReadDctPinMeasMode ( DctReadPinHandle );
#define UTL_ReadDctPinMeasMode _UTL_ReadDctPinMeasMode
extern CheckButton _UTL_ReadDctPinOverflowPolarity( DctReadPinHandle );
#define UTL_ReadDctPinOverflowPolarity _UTL_ReadDctPinOverflowPolarity
extern UT_PIN _UTL_ReadDctLatestPinNumber ( void );
#define UTL_ReadDctLatestPinNumber _UTL_ReadDctLatestPinNumber
extern DSlider _UTL_ReadDctPinHistoryData ( DctReadPinHandle );
#define UTL_ReadDctPinHistoryData _UTL_ReadDctPinHistoryData
extern void _UTL_ReadDctPinAllHistoryData ( DctReadPinHandle , DSlider * , USlider);
#define UTL_ReadDctPinAllHistoryData _UTL_ReadDctPinAllHistoryData
extern void _UTL_ReadDctPinAllHistoryDataAllDut ( DctReadPinHandle , DSlider * , CheckButton * , USlider );
#define UTL_ReadDctPinAllHistoryDataAllDut _UTL_ReadDctPinAllHistoryDataAllDut
extern FctReadPinHandle _UTL_GetFctReadPinHandle( void );
#define UTL_GetFctReadPinHandle _UTL_GetFctReadPinHandle
extern void _UTL_SetFctReadPinMode( FctReadPinHandle, RadioButton );
#define UTL_SetFctReadPinMode _UTL_SetFctReadPinMode
extern void _UTL_SetFctReadPinDut( FctReadPinHandle, UT_DUT );
#define UTL_SetFctReadPinDut _UTL_SetFctReadPinDut
extern void _UTL_SetFctReadPinNumber( FctReadPinHandle, UT_PIN );
#define UTL_SetFctReadPinNumber _UTL_SetFctReadPinNumber
extern CheckButton _UTL_ReadFctPin( FctReadPinHandle );
#define UTL_ReadFctPin _UTL_ReadFctPin
extern ScFailPinHandle _UTL_GetScFailPinHandle( void );
#define UTL_GetScFailPinHandle _UTL_GetScFailPinHandle
extern void _UTL_AddScFailPinTargetPinNumber( ScFailPinHandle, UT_PIN );
#define UTL_AddScFailPinTargetPinNumber _UTL_AddScFailPinTargetPinNumber
extern void _UTL_ClearScFailPinTargetPinNumber( ScFailPinHandle );
#define UTL_ClearScFailPinTargetPinNumber _UTL_ClearScFailPinTargetPinNumber
extern void _UTL_SetScFailPinUpdateMode( ScFailPinHandle, RadioButton );
#define UTL_SetScFailPinUpdateMode _UTL_SetScFailPinUpdateMode
extern void _UTL_SetScFailPinTargetBank( ScFailPinHandle, RadioButton );
#define UTL_SetScFailPinTargetBank _UTL_SetScFailPinTargetBank
extern void _UTL_UpdateScFailPin( ScFailPinHandle );
#define UTL_UpdateScFailPin _UTL_UpdateScFailPin
extern int _UTL_GetScFailPin( ScFailPinHandle, UT_DUT, UT_PIN, CheckButton * );
#define UTL_GetScFailPin _UTL_GetScFailPin
extern PinCursor _UTL_GetScFailPinTargetPinCursor( ScFailPinHandle );
#define UTL_GetScFailPinTargetPinCursor _UTL_GetScFailPinTargetPinCursor
extern int _UTL_GetScFailPinUpdateMode( ScFailPinHandle, RadioButton *);
#define UTL_GetScFailPinUpdateMode _UTL_GetScFailPinUpdateMode
extern int _UTL_GetScFailPinTargetBank( ScFailPinHandle, RadioButton *);
#define UTL_GetScFailPinTargetBank _UTL_GetScFailPinTargetBank
extern RadioButton _UTL_ReadMeasResult( UT_DUT );
#define UTL_ReadMeasResult _UTL_ReadMeasResult
extern RadioButton _UTL_ReadMeasKind ( void );
#define UTL_ReadMeasKind _UTL_ReadMeasKind
extern void _UTL_SetTestResult ( UT_DUT , char * , RadioButton );
#define UTL_SetTestResult _UTL_SetTestResult
extern void _UTL_ResetTestResult( UT_DUT , char * , RadioButton );
#define UTL_ResetTestResult _UTL_ResetTestResult
extern RadioButton _UTL_ReadTestResult ( UT_DUT , char * , RadioButton );
#define UTL_ReadTestResult _UTL_ReadTestResult
extern USlider _UTL_ReadTestFailCount(char *);
#define UTL_ReadTestFailCount _UTL_ReadTestFailCount
extern void _UTL_SetFinalResult ( UT_DUT , RadioButton );
#define UTL_SetFinalResult _UTL_SetFinalResult
extern void _UTL_ResetFinalResult ( UT_DUT , RadioButton );
#define UTL_ResetFinalResult _UTL_ResetFinalResult
extern void _UTL_SetFinalResultOnly ( UT_DUT , RadioButton );
#define UTL_SetFinalResultOnly _UTL_SetFinalResultOnly
extern void _UTL_ResetFinalResultOnly( UT_DUT , RadioButton );
#define UTL_ResetFinalResultOnly _UTL_ResetFinalResultOnly
extern RadioButton _UTL_ReadFinalResult ( UT_DUT , RadioButton );
#define UTL_ReadFinalResult _UTL_ReadFinalResult
 extern DutChannelHandle _UTL_GetDutChannelHandle (void);
#define UTL_GetDutChannelHandle _UTL_GetDutChannelHandle
 extern void _UTL_SetDutChannelMode (DutChannelHandle, CheckButton);
#define UTL_SetDutChannelMode _UTL_SetDutChannelMode
 extern void _UTL_SetDutChannelCount (DutChannelHandle, USlider);
#define UTL_SetDutChannelCount _UTL_SetDutChannelCount
 extern void _UTL_SetDutChannelPinList (DutChannelHandle, USlider, char *);
#define UTL_SetDutChannelPinList _UTL_SetDutChannelPinList
 extern void _UTL_SendDutChannel (DutChannelHandle);
#define UTL_SendDutChannel _UTL_SendDutChannel
 extern void _UTL_UpdateDutChannel (DutChannelHandle);
#define UTL_UpdateDutChannel _UTL_UpdateDutChannel
extern int _UTL_GetDutChannelMode (DutChannelHandle, CheckButton *);
#define UTL_GetDutChannelMode _UTL_GetDutChannelMode
extern int _UTL_GetDutChannelCount (DutChannelHandle, USlider *);
#define UTL_GetDutChannelCount _UTL_GetDutChannelCount
extern int _UTL_GetDutChannelPinList (DutChannelHandle, USlider, char **);
#define UTL_GetDutChannelPinList _UTL_GetDutChannelPinList
 extern FailCaptureSelectHandle _UTL_GetFailCaptureSelectHandle (void);
#define UTL_GetFailCaptureSelectHandle _UTL_GetFailCaptureSelectHandle
 extern void _UTL_SetFailCaptureSelectDutGroupNumber (FailCaptureSelectHandle, RadioButton);
#define UTL_SetFailCaptureSelectDutGroupNumber _UTL_SetFailCaptureSelectDutGroupNumber
 extern void _UTL_SetFailCaptureSelectAllDutGroupNumber (FailCaptureSelectHandle, CheckButton);
#define UTL_SetFailCaptureSelectAllDutGroupNumber _UTL_SetFailCaptureSelectAllDutGroupNumber
 extern void _UTL_SetFailCaptureSelectPinList (FailCaptureSelectHandle, char *);
#define UTL_SetFailCaptureSelectPinList _UTL_SetFailCaptureSelectPinList
 extern void _UTL_SetFailCaptureSelectAllPin (FailCaptureSelectHandle, CheckButton);
#define UTL_SetFailCaptureSelectAllPin _UTL_SetFailCaptureSelectAllPin
 extern void _UTL_SendFailCaptureSelect (FailCaptureSelectHandle);
#define UTL_SendFailCaptureSelect _UTL_SendFailCaptureSelect
 extern MemoryModuleHandle _UTL_GetMemoryModuleHandle( void );
#define UTL_GetMemoryModuleHandle _UTL_GetMemoryModuleHandle
 extern void _UTL_AddMemoryModulePurpose( MemoryModuleHandle h, RadioButton purpose, USlider purposeCount );
#define UTL_AddMemoryModulePurpose _UTL_AddMemoryModulePurpose
 extern void _UTL_ClearMemoryModulePurpose( MemoryModuleHandle h );
#define UTL_ClearMemoryModulePurpose _UTL_ClearMemoryModulePurpose
 extern void _UTL_SendMemoryModule( MemoryModuleHandle h );
#define UTL_SendMemoryModule _UTL_SendMemoryModule
 extern FcmConfigHandle _UTL_GetFcmConfigHandle ( void );
#define UTL_GetFcmConfigHandle _UTL_GetFcmConfigHandle
 extern void _UTL_SetFcmConfigMultiMode ( FcmConfigHandle, RadioButton );
#define UTL_SetFcmConfigMultiMode _UTL_SetFcmConfigMultiMode
 extern void _UTL_SetFcmConfigDut ( FcmConfigHandle, UT_DUT );
#define UTL_SetFcmConfigDut _UTL_SetFcmConfigDut
 extern void _UTL_SetFcmConfigBitSize ( FcmConfigHandle, USlider );
#define UTL_SetFcmConfigBitSize _UTL_SetFcmConfigBitSize
 extern void _UTL_SetFcmConfigDutBitSize ( FcmConfigHandle, USlider );
#define UTL_SetFcmConfigDutBitSize _UTL_SetFcmConfigDutBitSize
 extern void _UTL_SetFcmConfigAddrAssign ( FcmConfigHandle, RadioButton, RadioButton );
#define UTL_SetFcmConfigAddrAssign _UTL_SetFcmConfigAddrAssign
 extern void _UTL_SetFcmConfigSplitAddrAssign ( FcmConfigHandle, RadioButton, RadioButton );
#define UTL_SetFcmConfigSplitAddrAssign _UTL_SetFcmConfigSplitAddrAssign
 extern void _UTL_SetFcmConfigAddrAssignByAlpg ( FcmConfigHandle, RadioButton, RadioButton, RadioButton );
#define UTL_SetFcmConfigAddrAssignByAlpg _UTL_SetFcmConfigAddrAssignByAlpg
 extern void _UTL_SetFcmConfigAlpgUnit ( FcmConfigHandle, RadioButton );
#define UTL_SetFcmConfigAlpgUnit _UTL_SetFcmConfigAlpgUnit
 extern void _UTL_AddFcmConfigPinAssign ( FcmConfigHandle, RadioButton, UT_PIN );
#define UTL_AddFcmConfigPinAssign _UTL_AddFcmConfigPinAssign
 extern void _UTL_ClearFcmConfigPinAssign ( FcmConfigHandle );
#define UTL_ClearFcmConfigPinAssign _UTL_ClearFcmConfigPinAssign
 extern void _UTL_SetFcmConfigPinAssignTarget ( FcmConfigHandle, RadioButton );
#define UTL_SetFcmConfigPinAssignTarget _UTL_SetFcmConfigPinAssignTarget
 extern void _UTL_AddFcmConfigMaskPinAssign ( FcmConfigHandle, RadioButton, UT_PIN );
#define UTL_AddFcmConfigMaskPinAssign _UTL_AddFcmConfigMaskPinAssign
 extern void _UTL_ClearFcmConfigMaskPinAssign ( FcmConfigHandle );
#define UTL_ClearFcmConfigMaskPinAssign _UTL_ClearFcmConfigMaskPinAssign
 extern void _UTL_AddFcmConfigBitSelect ( FcmConfigHandle, RadioButton, RadioButton );
#define UTL_AddFcmConfigBitSelect _UTL_AddFcmConfigBitSelect
 extern void _UTL_ClearFcmConfigBitSelect ( FcmConfigHandle );
#define UTL_ClearFcmConfigBitSelect _UTL_ClearFcmConfigBitSelect
 extern void _UTL_SetFcmConfigBitSelectTarget ( FcmConfigHandle, RadioButton );
#define UTL_SetFcmConfigBitSelectTarget _UTL_SetFcmConfigBitSelectTarget
 extern void _UTL_SetFcmConfigStoreSignal ( FcmConfigHandle, RadioButton );
#define UTL_SetFcmConfigStoreSignal _UTL_SetFcmConfigStoreSignal
 extern void _UTL_SetFcmConfigStoreSignalByMMType( FcmConfigHandle, RadioButton, RadioButton );
#define UTL_SetFcmConfigStoreSignalByMMType _UTL_SetFcmConfigStoreSignalByMMType
 extern void _UTL_SetFcmConfigStoreInhSignal (FcmConfigHandle, RadioButton);
#define UTL_SetFcmConfigStoreInhSignal _UTL_SetFcmConfigStoreInhSignal
 extern void _UTL_SetFcmConfigAddrScram ( FcmConfigHandle, CheckButton );
#define UTL_SetFcmConfigAddrScram _UTL_SetFcmConfigAddrScram
 extern void _UTL_SetFcmConfigAddrScramByAlpg ( FcmConfigHandle, RadioButton, CheckButton );
#define UTL_SetFcmConfigAddrScramByAlpg _UTL_SetFcmConfigAddrScramByAlpg
 extern void _UTL_AddFcmConfigAction ( FcmConfigHandle, RadioButton, RadioButton );
#define UTL_AddFcmConfigAction _UTL_AddFcmConfigAction
 extern void _UTL_ClearFcmConfigAction ( FcmConfigHandle );
#define UTL_ClearFcmConfigAction _UTL_ClearFcmConfigAction
 extern void _UTL_AddFcmConfigStrbChannel ( FcmConfigHandle, RadioButton, RadioButton, RadioButton, RadioButton );
#define UTL_AddFcmConfigStrbChannel _UTL_AddFcmConfigStrbChannel
 extern void _UTL_ClearFcmConfigStrbChannel ( FcmConfigHandle, RadioButton );
#define UTL_ClearFcmConfigStrbChannel _UTL_ClearFcmConfigStrbChannel
 extern void _UTL_SetFcmConfigRate ( FcmConfigHandle, RadioButton );
#define UTL_SetFcmConfigRate _UTL_SetFcmConfigRate
 extern void _UTL_SetFcmConfigDelay ( FcmConfigHandle, USlider );
#define UTL_SetFcmConfigDelay _UTL_SetFcmConfigDelay
 extern void _UTL_SetFcmConfigDelayByAlpg ( FcmConfigHandle, RadioButton, USlider );
#define UTL_SetFcmConfigDelayByAlpg _UTL_SetFcmConfigDelayByAlpg
 extern void _UTL_SetFcmConfigModeDelayByAlpg ( FcmConfigHandle h, RadioButton alpg, RadioButton mode, USlider delay );
#define UTL_SetFcmConfigModeDelayByAlpg _UTL_SetFcmConfigModeDelayByAlpg
 extern void _UTL_SetFcmConfigSparePackageMode ( FcmConfigHandle, CheckButton );
#define UTL_SetFcmConfigSparePackageMode _UTL_SetFcmConfigSparePackageMode
 extern void _UTL_SetFcmConfigSpareAddrAssign ( FcmConfigHandle, RadioButton, RadioButton, RadioButton );
#define UTL_SetFcmConfigSpareAddrAssign _UTL_SetFcmConfigSpareAddrAssign
 extern void _UTL_SetFcmConfigDdrMode ( FcmConfigHandle, CheckButton );
#define UTL_SetFcmConfigDdrMode _UTL_SetFcmConfigDdrMode
 extern void _UTL_SetFcmConfigExMode ( FcmConfigHandle, CheckButton );
#define UTL_SetFcmConfigExMode _UTL_SetFcmConfigExMode
 extern void _UTL_SetFcmConfigPfcNoClear ( FcmConfigHandle, CheckButton );
#define UTL_SetFcmConfigPfcNoClear _UTL_SetFcmConfigPfcNoClear
 extern void _UTL_SetFcmConfigTransferSize ( FcmConfigHandle , USlider);
#define UTL_SetFcmConfigTransferSize _UTL_SetFcmConfigTransferSize
 extern void _UTL_SetFcmConfigResetInhibit ( FcmConfigHandle, CheckButton );
#define UTL_SetFcmConfigResetInhibit _UTL_SetFcmConfigResetInhibit
 extern void _UTL_SetFcmConfigScramEnableStartAddrBit (FcmConfigHandle, USlider );
#define UTL_SetFcmConfigScramEnableStartAddrBit _UTL_SetFcmConfigScramEnableStartAddrBit
 extern void _UTL_SetFcmConfigBurstCaptureLength ( FcmConfigHandle, RadioButton );
#define UTL_SetFcmConfigBurstCaptureLength _UTL_SetFcmConfigBurstCaptureLength
 extern void _UTL_SetFcmConfigRealTimeCountEnable( FcmConfigHandle , CheckButton);
#define UTL_SetFcmConfigRealTimeCountEnable _UTL_SetFcmConfigRealTimeCountEnable
 extern void _UTL_SetFcmConfigFcsmMaxStoreCnt (FcmConfigHandle, USlider);
#define UTL_SetFcmConfigFcsmMaxStoreCnt _UTL_SetFcmConfigFcsmMaxStoreCnt
 extern void _UTL_AddFcmConfigAreaDivisionBit (FcmConfigHandle, RadioButton, RadioButton );
#define UTL_AddFcmConfigAreaDivisionBit _UTL_AddFcmConfigAreaDivisionBit
 extern void _UTL_ClearFcmConfigAreaDivisionBit (FcmConfigHandle);
#define UTL_ClearFcmConfigAreaDivisionBit _UTL_ClearFcmConfigAreaDivisionBit
 extern void _UTL_SendFcmConfig ( FcmConfigHandle );
#define UTL_SendFcmConfig _UTL_SendFcmConfig
 extern FcmAccessHandle _UTL_GetFcmAccessHandle ( void );
#define UTL_GetFcmAccessHandle _UTL_GetFcmAccessHandle
 extern void _UTL_SetFcmAccessAlpgUnit ( FcmAccessHandle, RadioButton );
#define UTL_SetFcmAccessAlpgUnit _UTL_SetFcmAccessAlpgUnit
 extern void _UTL_SetFcmAccessAction ( FcmAccessHandle, RadioButton );
#define UTL_SetFcmAccessAction _UTL_SetFcmAccessAction
 extern void _UTL_SetFcmAccessActionNumber ( FcmAccessHandle, RadioButton, RadioButton );
#define UTL_SetFcmAccessActionNumber _UTL_SetFcmAccessActionNumber
 extern void _UTL_SetFcmAccessCompactionMode ( FcmAccessHandle, RadioButton );
#define UTL_SetFcmAccessCompactionMode _UTL_SetFcmAccessCompactionMode
 extern void _UTL_SetFcmAccessBitMode ( FcmAccessHandle, RadioButton );
#define UTL_SetFcmAccessBitMode _UTL_SetFcmAccessBitMode
 extern void _UTL_SetFcmAccessAllBit ( FcmAccessHandle, CheckButton );
#define UTL_SetFcmAccessAllBit _UTL_SetFcmAccessAllBit
 extern void _UTL_AddFcmAccessBit ( FcmAccessHandle, RadioButton );
#define UTL_AddFcmAccessBit _UTL_AddFcmAccessBit
 extern void _UTL_ClearFcmAccessBit ( FcmAccessHandle );
#define UTL_ClearFcmAccessBit _UTL_ClearFcmAccessBit
 extern void _UTL_SetFcmAccessBitBlock ( FcmAccessHandle, RadioButton );
#define UTL_SetFcmAccessBitBlock _UTL_SetFcmAccessBitBlock
 extern void _UTL_SetFcmAccessPresetAllMemory ( FcmAccessHandle, CheckButton );
#define UTL_SetFcmAccessPresetAllMemory _UTL_SetFcmAccessPresetAllMemory
 extern void _UTL_SetFcmAccessPresetMemoryInUse ( FcmAccessHandle, CheckButton );
#define UTL_SetFcmAccessPresetMemoryInUse _UTL_SetFcmAccessPresetMemoryInUse
 extern void _UTL_SetFcmAccessPresetIgnoreAddr ( FcmAccessHandle, CheckButton );
#define UTL_SetFcmAccessPresetIgnoreAddr _UTL_SetFcmAccessPresetIgnoreAddr
 extern void _UTL_SetFcmAccessPresetPreserveFbm ( FcmAccessHandle, CheckButton );
#define UTL_SetFcmAccessPresetPreserveFbm _UTL_SetFcmAccessPresetPreserveFbm
 extern void _UTL_SetFcmAccessAutoAddrAssignMode ( FcmAccessHandle, CheckButton );
#define UTL_SetFcmAccessAutoAddrAssignMode _UTL_SetFcmAccessAutoAddrAssignMode
 extern void _UTL_SetFcmAccessAddrAssign ( FcmAccessHandle, RadioButton, RadioButton );
#define UTL_SetFcmAccessAddrAssign _UTL_SetFcmAccessAddrAssign
 extern void _UTL_SetFcmAccessApLink ( FcmAccessHandle, RadioButton );
#define UTL_SetFcmAccessApLink _UTL_SetFcmAccessApLink
 extern void _UTL_SetFcmAccessXAddr ( FcmAccessHandle, USlider, USlider );
#define UTL_SetFcmAccessXAddr _UTL_SetFcmAccessXAddr
 extern void _UTL_SetFcmAccessYAddr ( FcmAccessHandle, USlider, USlider );
#define UTL_SetFcmAccessYAddr _UTL_SetFcmAccessYAddr
 extern void _UTL_SetFcmAccessZAddr ( FcmAccessHandle, USlider, USlider );
#define UTL_SetFcmAccessZAddr _UTL_SetFcmAccessZAddr
 extern void _UTL_SetFcmAccessAllDut ( FcmAccessHandle, CheckButton );
#define UTL_SetFcmAccessAllDut _UTL_SetFcmAccessAllDut
 extern void _UTL_SetFcmAccessDut ( FcmAccessHandle, UT_DUT );
#define UTL_SetFcmAccessDut _UTL_SetFcmAccessDut
 extern void _UTL_SetFcmAccessSearchMaxCnt ( FcmAccessHandle, USlider );
#define UTL_SetFcmAccessSearchMaxCnt _UTL_SetFcmAccessSearchMaxCnt
 extern void _UTL_SetFcmAccessSparePackageMode ( FcmAccessHandle, CheckButton );
#define UTL_SetFcmAccessSparePackageMode _UTL_SetFcmAccessSparePackageMode
 extern void _UTL_SetFcmAccessSpareAddrAssign ( FcmAccessHandle, RadioButton, RadioButton, RadioButton );
#define UTL_SetFcmAccessSpareAddrAssign _UTL_SetFcmAccessSpareAddrAssign
 extern void _UTL_SetFcmAccessPfcMode ( FcmAccessHandle, RadioButton );
#define UTL_SetFcmAccessPfcMode _UTL_SetFcmAccessPfcMode
 extern void _UTL_SetFcmAccessPfcNoClear ( FcmAccessHandle, CheckButton );
#define UTL_SetFcmAccessPfcNoClear _UTL_SetFcmAccessPfcNoClear
 extern void _UTL_SetFcmAccessAreaDivision ( FcmAccessHandle, RadioButton, RadioButton );
#define UTL_SetFcmAccessAreaDivision _UTL_SetFcmAccessAreaDivision
 extern void _UTL_SetFcmAccessAreaDivisionInv ( FcmAccessHandle, CheckButton );
#define UTL_SetFcmAccessAreaDivisionInv _UTL_SetFcmAccessAreaDivisionInv
 extern void _UTL_AddFcmAccessAreaDivisionByName ( FcmAccessHandle, RadioButton );
#define UTL_AddFcmAccessAreaDivisionByName _UTL_AddFcmAccessAreaDivisionByName
 extern void _UTL_ClearFcmAccessAreaDivisionByName( FcmAccessHandle );
#define UTL_ClearFcmAccessAreaDivisionByName _UTL_ClearFcmAccessAreaDivisionByName
 extern void _UTL_PresetFcm ( FcmAccessHandle, USlider );
#define UTL_PresetFcm _UTL_PresetFcm
 extern void _UTL_ReadFcm ( FcmAccessHandle, void *, USlider );
#define UTL_ReadFcm _UTL_ReadFcm
 extern void _UTL_WriteFcm ( FcmAccessHandle, void *, USlider );
#define UTL_WriteFcm _UTL_WriteFcm
 extern void _UTL_SearchFcmFailAddr ( FcmAccessHandle );
#define UTL_SearchFcmFailAddr _UTL_SearchFcmFailAddr
 extern AddrCursor _UTL_GetFcmFailAddr ( RadioButton );
#define UTL_GetFcmFailAddr _UTL_GetFcmFailAddr
 extern CheckButton _UTL_GetFcmSearchComplete ( void );
#define UTL_GetFcmSearchComplete _UTL_GetFcmSearchComplete
 extern void _UTL_CntFcmFailAddr ( FcmAccessHandle );
#define UTL_CntFcmFailAddr _UTL_CntFcmFailAddr
 extern USlider _UTL_GetFcmFailAddrCnt ( RadioButton );
#define UTL_GetFcmFailAddrCnt _UTL_GetFcmFailAddrCnt
 extern CheckButton _UTL_GetFcmFailAddrCntOverflow( RadioButton );
#define UTL_GetFcmFailAddrCntOverflow _UTL_GetFcmFailAddrCntOverflow
 extern void _UTL_ParallelFailCountFcm ( FcmAccessHandle );
#define UTL_ParallelFailCountFcm _UTL_ParallelFailCountFcm
 extern USlider _UTL_GetFcmParallelFailCount ( FcmAccessHandle );
#define UTL_GetFcmParallelFailCount _UTL_GetFcmParallelFailCount
 extern CheckButton _UTL_GetFcmParallelFailCountOverflow( FcmAccessHandle );
#define UTL_GetFcmParallelFailCountOverflow _UTL_GetFcmParallelFailCountOverflow
 extern void _UTL_MoveFcm ( FcmAccessHandle );
#define UTL_MoveFcm _UTL_MoveFcm
 extern void _UTL_RemoveFcm ( FcmAccessHandle );
#define UTL_RemoveFcm _UTL_RemoveFcm
 extern RadioButton _UTL_ReadFcmFailOverflow ( FcmAccessHandle h );
#define UTL_ReadFcmFailOverflow _UTL_ReadFcmFailOverflow
 extern void _UTL_ResetFcsmStoreCnt ( void );
#define UTL_ResetFcsmStoreCnt _UTL_ResetFcsmStoreCnt
 extern void _UTL_ResetFcsm ( FcmAccessHandle h );
#define UTL_ResetFcsm _UTL_ResetFcsm
 extern CheckButton _UTL_ReadFcsmStoreCnt ( FcmAccessHandle h, USlider *store_cnt );
#define UTL_ReadFcsmStoreCnt _UTL_ReadFcsmStoreCnt
 extern void _UTL_ReadFcsm ( FcmAccessHandle h, void *data, USlider size );
#define UTL_ReadFcsm _UTL_ReadFcsm
 extern UT_ADDR _UTL_NextAddr ( AddrCursor );
#define UTL_NextAddr _UTL_NextAddr
 extern USlider _UTL_GetXAddr ( UT_ADDR );
#define UTL_GetXAddr _UTL_GetXAddr
 extern USlider _UTL_GetYAddr ( UT_ADDR );
#define UTL_GetYAddr _UTL_GetYAddr
 extern USlider _UTL_GetZAddr ( UT_ADDR );
#define UTL_GetZAddr _UTL_GetZAddr
extern BbmConfigHandle _UTL_GetBbmConfigHandle(void);
#define UTL_GetBbmConfigHandle _UTL_GetBbmConfigHandle
extern void _UTL_SetBbmConfigMode( BbmConfigHandle, RadioButton );
#define UTL_SetBbmConfigMode _UTL_SetBbmConfigMode
extern void _UTL_SetBbmConfigAction( BbmConfigHandle, RadioButton );
#define UTL_SetBbmConfigAction _UTL_SetBbmConfigAction
extern void _UTL_SetBbmConfigStoreMode( BbmConfigHandle, RadioButton );
#define UTL_SetBbmConfigStoreMode _UTL_SetBbmConfigStoreMode
extern void _UTL_SetBbmConfigCaptureSignal(BbmConfigHandle, RadioButton);
#define UTL_SetBbmConfigCaptureSignal _UTL_SetBbmConfigCaptureSignal
extern void _UTL_SetBbmConfigDataGenerationMode( BbmConfigHandle, RadioButton );
#define UTL_SetBbmConfigDataGenerationMode _UTL_SetBbmConfigDataGenerationMode
extern void _UTL_SetBbmConfigWriteEnableAllDut( BbmConfigHandle, CheckButton );
#define UTL_SetBbmConfigWriteEnableAllDut _UTL_SetBbmConfigWriteEnableAllDut
extern void _UTL_SetBbmConfigWriteEnableByDut( BbmConfigHandle, CheckButton,UT_DUT);
#define UTL_SetBbmConfigWriteEnableByDut _UTL_SetBbmConfigWriteEnableByDut
extern void _UTL_SetBbmConfigBitSize( BbmConfigHandle, USlider );
#define UTL_SetBbmConfigBitSize _UTL_SetBbmConfigBitSize
extern void _UTL_SetBbmConfigAddrAssign( BbmConfigHandle, RadioButton, RadioButton );
#define UTL_SetBbmConfigAddrAssign _UTL_SetBbmConfigAddrAssign
extern void _UTL_SetBbmConfigDelay( BbmConfigHandle, USlider );
#define UTL_SetBbmConfigDelay _UTL_SetBbmConfigDelay
extern void _UTL_AddBbmConfigStrbChannel( BbmConfigHandle, RadioButton );
#define UTL_AddBbmConfigStrbChannel _UTL_AddBbmConfigStrbChannel
extern void _UTL_ClearBbmConfigStrbChannel( BbmConfigHandle );
#define UTL_ClearBbmConfigStrbChannel _UTL_ClearBbmConfigStrbChannel
extern void _UTL_SetBbmConfigBbcLimitAllDut( BbmConfigHandle, USlider );
#define UTL_SetBbmConfigBbcLimitAllDut _UTL_SetBbmConfigBbcLimitAllDut
extern void _UTL_SetBbmConfigBbcLimitByDut( BbmConfigHandle, USlider, UT_DUT );
#define UTL_SetBbmConfigBbcLimitByDut _UTL_SetBbmConfigBbcLimitByDut
extern void _UTL_SetBbmConfigBbcLimitByBit( BbmConfigHandle, USlider, RadioButton );
#define UTL_SetBbmConfigBbcLimitByBit _UTL_SetBbmConfigBbcLimitByBit
extern void _UTL_AddBbmConfigDrInhPin( BbmConfigHandle, UT_PIN, RadioButton );
#define UTL_AddBbmConfigDrInhPin _UTL_AddBbmConfigDrInhPin
extern void _UTL_ClearBbmConfigDrInhPin( BbmConfigHandle );
#define UTL_ClearBbmConfigDrInhPin _UTL_ClearBbmConfigDrInhPin
extern void _UTL_AddBbmConfigFailLoopBackPin( BbmConfigHandle, UT_PIN );
#define UTL_AddBbmConfigFailLoopBackPin _UTL_AddBbmConfigFailLoopBackPin
extern void _UTL_ClearBbmConfigFailLoopBackPin( BbmConfigHandle );
#define UTL_ClearBbmConfigFailLoopBackPin _UTL_ClearBbmConfigFailLoopBackPin
extern void _UTL_SetBbmConfigPatternCycle( BbmConfigHandle, RadioButton, RadioButton );
#define UTL_SetBbmConfigPatternCycle _UTL_SetBbmConfigPatternCycle
extern void _UTL_AddBbmConfigCaptureDataByTargetBank( BbmConfigHandle, RadioButton, UT_DUT, RadioButton, RadioButton );
#define UTL_AddBbmConfigCaptureDataByTargetBank _UTL_AddBbmConfigCaptureDataByTargetBank
extern void _UTL_ClearBbmConfigCaptureData( BbmConfigHandle );
#define UTL_ClearBbmConfigCaptureData _UTL_ClearBbmConfigCaptureData
extern void _UTL_AddBbmConfigMaskBit( BbmConfigHandle, RadioButton );
#define UTL_AddBbmConfigMaskBit _UTL_AddBbmConfigMaskBit
extern void _UTL_AddBbmConfigMaskBitByTargetBank ( BbmConfigHandle, UT_DUT, RadioButton, RadioButton );
#define UTL_AddBbmConfigMaskBitByTargetBank _UTL_AddBbmConfigMaskBitByTargetBank
extern void _UTL_ClearBbmConfigMaskBit( BbmConfigHandle );
#define UTL_ClearBbmConfigMaskBit _UTL_ClearBbmConfigMaskBit
extern void _UTL_AddBbmConfigBbcLimitMaskBit( BbmConfigHandle, RadioButton );
#define UTL_AddBbmConfigBbcLimitMaskBit _UTL_AddBbmConfigBbcLimitMaskBit
extern void _UTL_AddBbmConfigBbcLimitMaskBitByTargetBank ( BbmConfigHandle, UT_DUT, RadioButton, RadioButton );
#define UTL_AddBbmConfigBbcLimitMaskBitByTargetBank _UTL_AddBbmConfigBbcLimitMaskBitByTargetBank
extern void _UTL_ClearBbmConfigBbcLimitMaskBit( BbmConfigHandle );
#define UTL_ClearBbmConfigBbcLimitMaskBit _UTL_ClearBbmConfigBbcLimitMaskBit
extern void _UTL_SetBbmConfigSkipSignal( BbmConfigHandle, RadioButton );
#define UTL_SetBbmConfigSkipSignal _UTL_SetBbmConfigSkipSignal
extern void _UTL_SetBbmConfigStatusSignal( BbmConfigHandle, RadioButton );
#define UTL_SetBbmConfigStatusSignal _UTL_SetBbmConfigStatusSignal
extern void _UTL_SetBbmConfigCounterNoClear( BbmConfigHandle, RadioButton, CheckButton );
#define UTL_SetBbmConfigCounterNoClear _UTL_SetBbmConfigCounterNoClear
extern void _UTL_SetBbmConfigPlaneCount( BbmConfigHandle, USlider );
#define UTL_SetBbmConfigPlaneCount _UTL_SetBbmConfigPlaneCount
extern void _UTL_SendBbmConfig( BbmConfigHandle );
#define UTL_SendBbmConfig _UTL_SendBbmConfig
extern BbmAccessHandle _UTL_GetBbmAccessHandle(void);
#define UTL_GetBbmAccessHandle _UTL_GetBbmAccessHandle
extern void _UTL_SetBbmAccessPresetAllMemory( BbmAccessHandle, CheckButton );
#define UTL_SetBbmAccessPresetAllMemory _UTL_SetBbmAccessPresetAllMemory
extern void _UTL_SetBbmAccessAllDut( BbmAccessHandle, CheckButton);
#define UTL_SetBbmAccessAllDut _UTL_SetBbmAccessAllDut
extern void _UTL_SetBbmAccessDut( BbmAccessHandle,UT_DUT);
#define UTL_SetBbmAccessDut _UTL_SetBbmAccessDut
extern void _UTL_SetBbmAccessChannel( BbmAccessHandle, USlider);
#define UTL_SetBbmAccessChannel _UTL_SetBbmAccessChannel
extern void _UTL_SetBbmAccessStartAddr( BbmAccessHandle,USlider);
#define UTL_SetBbmAccessStartAddr _UTL_SetBbmAccessStartAddr
extern void _UTL_SetBbmAccessStopAddr( BbmAccessHandle,USlider);
#define UTL_SetBbmAccessStopAddr _UTL_SetBbmAccessStopAddr
extern void _UTL_SetBbmAccessAddrAssign ( BbmAccessHandle, RadioButton, RadioButton );
#define UTL_SetBbmAccessAddrAssign _UTL_SetBbmAccessAddrAssign
extern void _UTL_SetBbmAccessXAddr ( BbmAccessHandle, USlider, USlider );
#define UTL_SetBbmAccessXAddr _UTL_SetBbmAccessXAddr
extern void _UTL_SetBbmAccessYAddr ( BbmAccessHandle, USlider, USlider );
#define UTL_SetBbmAccessYAddr _UTL_SetBbmAccessYAddr
extern void _UTL_SetBbmAccessZAddr ( BbmAccessHandle, USlider, USlider );
#define UTL_SetBbmAccessZAddr _UTL_SetBbmAccessZAddr
extern void _UTL_SetBbmAccessApLink ( BbmAccessHandle, RadioButton );
#define UTL_SetBbmAccessApLink _UTL_SetBbmAccessApLink
extern void _UTL_SetBbmAccessBitBlock( BbmAccessHandle, RadioButton );
#define UTL_SetBbmAccessBitBlock _UTL_SetBbmAccessBitBlock
extern void _UTL_SetBbmAccessCounterMode( BbmAccessHandle, RadioButton );
#define UTL_SetBbmAccessCounterMode _UTL_SetBbmAccessCounterMode
extern void _UTL_SetBbmAccessEnableCounter( BbmAccessHandle, RadioButton, CheckButton );
#define UTL_SetBbmAccessEnableCounter _UTL_SetBbmAccessEnableCounter
extern void _UTL_SetBbmAccessSearchMaxCnt( BbmAccessHandle, USlider );
#define UTL_SetBbmAccessSearchMaxCnt _UTL_SetBbmAccessSearchMaxCnt
extern void _UTL_SetBbmAccessBitMode( BbmAccessHandle, RadioButton );
#define UTL_SetBbmAccessBitMode _UTL_SetBbmAccessBitMode
extern void _UTL_SetBbmAccessAllBit( BbmAccessHandle, CheckButton );
#define UTL_SetBbmAccessAllBit _UTL_SetBbmAccessAllBit
extern void _UTL_AddBbmAccessBit(BbmAccessHandle, RadioButton);
#define UTL_AddBbmAccessBit _UTL_AddBbmAccessBit
extern void _UTL_ClearBbmAccessBit(BbmAccessHandle);
#define UTL_ClearBbmAccessBit _UTL_ClearBbmAccessBit
extern void _UTL_SetBbmAccessMatchData(BbmAccessHandle, RadioButton, USlider);
#define UTL_SetBbmAccessMatchData _UTL_SetBbmAccessMatchData
extern void _UTL_SetBbmAccessScanInvert(BbmAccessHandle, CheckButton);
#define UTL_SetBbmAccessScanInvert _UTL_SetBbmAccessScanInvert
extern void _UTL_SetBbmAccessWriteMode(BbmAccessHandle, RadioButton);
#define UTL_SetBbmAccessWriteMode _UTL_SetBbmAccessWriteMode
extern void _UTL_SetBbmAccessCounterNoClear( BbmConfigHandle, RadioButton, CheckButton );
#define UTL_SetBbmAccessCounterNoClear _UTL_SetBbmAccessCounterNoClear
extern void _UTL_PresetBbm( BbmAccessHandle,USlider);
#define UTL_PresetBbm _UTL_PresetBbm
extern void _UTL_ReadBbm( BbmAccessHandle,void *,USlider);
#define UTL_ReadBbm _UTL_ReadBbm
extern void _UTL_WriteBbm( BbmAccessHandle,void *,USlider);
#define UTL_WriteBbm _UTL_WriteBbm
extern void _UTL_CntBbmFailAddr( BbmAccessHandle );
#define UTL_CntBbmFailAddr _UTL_CntBbmFailAddr
extern USlider _UTL_ReadBadBlockCounter( BbmAccessHandle,RadioButton *);
#define UTL_ReadBadBlockCounter _UTL_ReadBadBlockCounter
extern void _UTL_WriteBadBlockCounter( BbmAccessHandle, USlider);
#define UTL_WriteBadBlockCounter _UTL_WriteBadBlockCounter
extern void _UTL_SearchBbmFailAddr( BbmAccessHandle );
#define UTL_SearchBbmFailAddr _UTL_SearchBbmFailAddr
extern AddrPointerCursor _UTL_GetBbmFailAddrPointer( BbmAccessHandle );
#define UTL_GetBbmFailAddrPointer _UTL_GetBbmFailAddrPointer
extern USlider _UTL_NextAddrPointer( AddrPointerCursor );
#define UTL_NextAddrPointer _UTL_NextAddrPointer
extern CheckButton _UTL_GetBbmSearchComplete( BbmAccessHandle );
#define UTL_GetBbmSearchComplete _UTL_GetBbmSearchComplete
extern RfcmConfigHandle _UTL_GetRfcmConfigHandle ( void );
#define UTL_GetRfcmConfigHandle _UTL_GetRfcmConfigHandle
extern void _UTL_SetRfcmConfigMode ( RfcmConfigHandle, RadioButton );
#define UTL_SetRfcmConfigMode _UTL_SetRfcmConfigMode
extern void _UTL_SetRfcmConfigAddrAssign ( RfcmConfigHandle, RadioButton, RadioButton );
#define UTL_SetRfcmConfigAddrAssign _UTL_SetRfcmConfigAddrAssign
extern void _UTL_SetRfcmConfigStopAddr ( RfcmConfigHandle, USlider );
#define UTL_SetRfcmConfigStopAddr _UTL_SetRfcmConfigStopAddr
extern void _UTL_SetRfcmConfigTransferSignal ( RfcmConfigHandle, RadioButton );
#define UTL_SetRfcmConfigTransferSignal _UTL_SetRfcmConfigTransferSignal
extern void _UTL_SetRfcmConfigClearSignal ( RfcmConfigHandle, RadioButton );
#define UTL_SetRfcmConfigClearSignal _UTL_SetRfcmConfigClearSignal
extern void _UTL_SetRfcmConfigRfcsmTransferSignal ( RfcmConfigHandle, RadioButton );
#define UTL_SetRfcmConfigRfcsmTransferSignal _UTL_SetRfcmConfigRfcsmTransferSignal
extern void _UTL_SetRfcmConfigRfcsmTransferMode ( RfcmConfigHandle, RadioButton );
#define UTL_SetRfcmConfigRfcsmTransferMode _UTL_SetRfcmConfigRfcsmTransferMode
extern void _UTL_SetRfcmConfigRfcsmClearSignal ( RfcmConfigHandle, RadioButton );
#define UTL_SetRfcmConfigRfcsmClearSignal _UTL_SetRfcmConfigRfcsmClearSignal
extern void _UTL_SetRfcmConfigFccLimitAllDut ( RfcmConfigHandle, USlider );
#define UTL_SetRfcmConfigFccLimitAllDut _UTL_SetRfcmConfigFccLimitAllDut
extern void _UTL_SetRfcmConfigFccLimitByDut ( RfcmConfigHandle, USlider, UT_DUT );
#define UTL_SetRfcmConfigFccLimitByDut _UTL_SetRfcmConfigFccLimitByDut
extern void _UTL_SetRfcmConfigRfcsmLimitAllDut ( RfcmConfigHandle, USlider );
#define UTL_SetRfcmConfigRfcsmLimitAllDut _UTL_SetRfcmConfigRfcsmLimitAllDut
extern void _UTL_SetRfcmConfigRfcsmLimitByDut ( RfcmConfigHandle, USlider, UT_DUT );
#define UTL_SetRfcmConfigRfcsmLimitByDut _UTL_SetRfcmConfigRfcsmLimitByDut
extern void _UTL_SendRfcmConfig ( RfcmConfigHandle );
#define UTL_SendRfcmConfig _UTL_SendRfcmConfig
extern RfcmAccessHandle _UTL_GetRfcmAccessHandle ( void );
#define UTL_GetRfcmAccessHandle _UTL_GetRfcmAccessHandle
extern void _UTL_SetRfcmAccessPresetAllMemory ( RfcmAccessHandle, CheckButton );
#define UTL_SetRfcmAccessPresetAllMemory _UTL_SetRfcmAccessPresetAllMemory
extern void _UTL_SetRfcmAccessDut ( RfcmAccessHandle, UT_DUT );
#define UTL_SetRfcmAccessDut _UTL_SetRfcmAccessDut
extern void _UTL_PresetRfcm ( RfcmAccessHandle, USlider );
#define UTL_PresetRfcm _UTL_PresetRfcm
extern USlider _UTL_ReadFailColumnCounter ( RfcmAccessHandle, RadioButton * );
#define UTL_ReadFailColumnCounter _UTL_ReadFailColumnCounter
extern CfbmConfigHandle _UTL_GetCfbmConfigHandle ( void );
#define UTL_GetCfbmConfigHandle _UTL_GetCfbmConfigHandle
extern void _UTL_SetCfbmConfigSplitMemory ( CfbmConfigHandle, USlider );
#define UTL_SetCfbmConfigSplitMemory _UTL_SetCfbmConfigSplitMemory
extern void _UTL_SetCfbmConfigCompressMode ( CfbmConfigHandle, USlider );
#define UTL_SetCfbmConfigCompressMode _UTL_SetCfbmConfigCompressMode
extern void _UTL_SetCfbmConfigSelectBit ( CfbmConfigHandle, USlider, UT_DUT, USlider );
#define UTL_SetCfbmConfigSelectBit _UTL_SetCfbmConfigSelectBit
extern void _UTL_SetCfbmConfigAddrAssign ( CfbmConfigHandle, RadioButton, RadioButton );
#define UTL_SetCfbmConfigAddrAssign _UTL_SetCfbmConfigAddrAssign
extern void _UTL_SetCfbmConfigXAddr ( CfbmConfigHandle, USlider, USlider );
#define UTL_SetCfbmConfigXAddr _UTL_SetCfbmConfigXAddr
extern void _UTL_SetCfbmConfigYAddr ( CfbmConfigHandle, USlider, USlider );
#define UTL_SetCfbmConfigYAddr _UTL_SetCfbmConfigYAddr
extern void _UTL_SetCfbmConfigZAddr ( CfbmConfigHandle, USlider, USlider );
#define UTL_SetCfbmConfigZAddr _UTL_SetCfbmConfigZAddr
extern void _UTL_CompressCfbm ( CfbmConfigHandle );
#define UTL_CompressCfbm _UTL_CompressCfbm
extern CfbmAccessHandle _UTL_GetCfbmAccessHandle ( void );
#define UTL_GetCfbmAccessHandle _UTL_GetCfbmAccessHandle
extern void _UTL_SetCfbmAccessPresetAllMemory ( CfbmAccessHandle, CheckButton );
#define UTL_SetCfbmAccessPresetAllMemory _UTL_SetCfbmAccessPresetAllMemory
extern void _UTL_SetCfbmAccessAddrBlock ( CfbmAccessHandle, USlider );
#define UTL_SetCfbmAccessAddrBlock _UTL_SetCfbmAccessAddrBlock
extern void _UTL_SetCfbmAccessAddrPointer ( CfbmAccessHandle, USlider, USlider );
#define UTL_SetCfbmAccessAddrPointer _UTL_SetCfbmAccessAddrPointer
extern void _UTL_PresetCfbm ( CfbmAccessHandle, USlider );
#define UTL_PresetCfbm _UTL_PresetCfbm
extern void _UTL_ReadCfbm ( CfbmAccessHandle, void *, USlider );
#define UTL_ReadCfbm _UTL_ReadCfbm
extern void _UTL_WriteCfbm ( CfbmAccessHandle, void *, USlider );
#define UTL_WriteCfbm _UTL_WriteCfbm
extern USlider _UTL_ReadCfbmDataCount ( CfbmAccessHandle );
#define UTL_ReadCfbmDataCount _UTL_ReadCfbmDataCount
extern USlider _UTL_ReadCfbmFailCount ( CfbmAccessHandle, CheckButton * );
#define UTL_ReadCfbmFailCount _UTL_ReadCfbmFailCount
extern CheckButton _UTL_ReadCfbmStatus ( CfbmAccessHandle );
#define UTL_ReadCfbmStatus _UTL_ReadCfbmStatus
extern RadioButton _UTL_ReadCfbmPassFailInfo ( CfbmAccessHandle );
#define UTL_ReadCfbmPassFailInfo _UTL_ReadCfbmPassFailInfo
 extern CfmConfigHandle _UTL_GetCfmConfigHandle ( void );
#define UTL_GetCfmConfigHandle _UTL_GetCfmConfigHandle
 extern void _UTL_SetCfmConfigBitSize ( CfmConfigHandle, USlider );
#define UTL_SetCfmConfigBitSize _UTL_SetCfmConfigBitSize
 extern void _UTL_SetCfmConfigDutBitSize ( CfmConfigHandle, USlider );
#define UTL_SetCfmConfigDutBitSize _UTL_SetCfmConfigDutBitSize
 extern void _UTL_SetCfmConfigAddrAssign ( CfmConfigHandle, RadioButton, RadioButton );
#define UTL_SetCfmConfigAddrAssign _UTL_SetCfmConfigAddrAssign
 extern void _UTL_SetCfmConfigAddrAssignByAlpg ( CfmConfigHandle, RadioButton, RadioButton, RadioButton );
#define UTL_SetCfmConfigAddrAssignByAlpg _UTL_SetCfmConfigAddrAssignByAlpg
 extern void _UTL_AddCfmConfigPinAssign ( CfmConfigHandle, RadioButton, UT_PIN );
#define UTL_AddCfmConfigPinAssign _UTL_AddCfmConfigPinAssign
 extern void _UTL_ClearCfmConfigPinAssign ( CfmConfigHandle );
#define UTL_ClearCfmConfigPinAssign _UTL_ClearCfmConfigPinAssign
 extern void _UTL_SetCfmConfigStoreSignalByMMType( CfmConfigHandle, RadioButton, RadioButton );
#define UTL_SetCfmConfigStoreSignalByMMType _UTL_SetCfmConfigStoreSignalByMMType
 extern void _UTL_AddCfmConfigAction ( CfmConfigHandle, RadioButton, RadioButton );
#define UTL_AddCfmConfigAction _UTL_AddCfmConfigAction
 extern void _UTL_ClearCfmConfigAction ( CfmConfigHandle );
#define UTL_ClearCfmConfigAction _UTL_ClearCfmConfigAction
 extern void _UTL_SetCfmConfigSpareInhMode ( CfmConfigHandle, CheckButton );
#define UTL_SetCfmConfigSpareInhMode _UTL_SetCfmConfigSpareInhMode
 extern void _UTL_SetCfmConfigBbmLinkMode ( CfmConfigHandle, CheckButton );
#define UTL_SetCfmConfigBbmLinkMode _UTL_SetCfmConfigBbmLinkMode
 extern void _UTL_SendCfmConfig ( CfmConfigHandle );
#define UTL_SendCfmConfig _UTL_SendCfmConfig
 extern CfmAccessHandle _UTL_GetCfmAccessHandle ( void );
#define UTL_GetCfmAccessHandle _UTL_GetCfmAccessHandle
 extern void _UTL_SetCfmAccessAlpgUnit ( CfmAccessHandle, RadioButton );
#define UTL_SetCfmAccessAlpgUnit _UTL_SetCfmAccessAlpgUnit
 extern void _UTL_SetCfmAccessActionNumber ( CfmAccessHandle, RadioButton, RadioButton );
#define UTL_SetCfmAccessActionNumber _UTL_SetCfmAccessActionNumber
 extern void _UTL_SetCfmAccessBitMode ( CfmAccessHandle, RadioButton );
#define UTL_SetCfmAccessBitMode _UTL_SetCfmAccessBitMode
 extern void _UTL_SetCfmAccessAllBit ( CfmAccessHandle, CheckButton );
#define UTL_SetCfmAccessAllBit _UTL_SetCfmAccessAllBit
 extern void _UTL_AddCfmAccessBit ( CfmAccessHandle, RadioButton );
#define UTL_AddCfmAccessBit _UTL_AddCfmAccessBit
 extern void _UTL_ClearCfmAccessBit ( CfmAccessHandle );
#define UTL_ClearCfmAccessBit _UTL_ClearCfmAccessBit
 extern void _UTL_SetCfmAccessBitBlock ( CfmAccessHandle, RadioButton );
#define UTL_SetCfmAccessBitBlock _UTL_SetCfmAccessBitBlock
 extern void _UTL_SetCfmAccessPresetAllMemory ( CfmAccessHandle, CheckButton );
#define UTL_SetCfmAccessPresetAllMemory _UTL_SetCfmAccessPresetAllMemory
 extern void _UTL_SetCfmAccessAddrAssign ( CfmAccessHandle, RadioButton, RadioButton );
#define UTL_SetCfmAccessAddrAssign _UTL_SetCfmAccessAddrAssign
 extern void _UTL_SetCfmAccessApLink ( CfmAccessHandle, RadioButton );
#define UTL_SetCfmAccessApLink _UTL_SetCfmAccessApLink
 extern void _UTL_SetCfmAccessXAddr ( CfmAccessHandle, USlider, USlider );
#define UTL_SetCfmAccessXAddr _UTL_SetCfmAccessXAddr
 extern void _UTL_SetCfmAccessYAddr ( CfmAccessHandle, USlider, USlider );
#define UTL_SetCfmAccessYAddr _UTL_SetCfmAccessYAddr
 extern void _UTL_SetCfmAccessZAddr ( CfmAccessHandle, USlider, USlider );
#define UTL_SetCfmAccessZAddr _UTL_SetCfmAccessZAddr
 extern void _UTL_SetCfmAccessAllDut ( CfmAccessHandle, CheckButton );
#define UTL_SetCfmAccessAllDut _UTL_SetCfmAccessAllDut
 extern void _UTL_SetCfmAccessDut ( CfmAccessHandle, UT_DUT );
#define UTL_SetCfmAccessDut _UTL_SetCfmAccessDut
 extern void _UTL_PresetCfm ( CfmAccessHandle, USlider );
#define UTL_PresetCfm _UTL_PresetCfm
 extern void _UTL_ReadCfm ( CfmAccessHandle, void *, USlider );
#define UTL_ReadCfm _UTL_ReadCfm
 extern void _UTL_CntCfmFailAddr ( CfmAccessHandle );
#define UTL_CntCfmFailAddr _UTL_CntCfmFailAddr
 extern USlider _UTL_GetCfmFailAddrCnt ( RadioButton );
#define UTL_GetCfmFailAddrCnt _UTL_GetCfmFailAddrCnt
 extern CheckButton _UTL_GetCfmFailAddrCntOverflow( RadioButton );
#define UTL_GetCfmFailAddrCntOverflow _UTL_GetCfmFailAddrCntOverflow
extern FasmAccessHandle _UTL_GetFasmAccessHandle( void );
#define UTL_GetFasmAccessHandle _UTL_GetFasmAccessHandle
extern void _UTL_SetFasmAccessStartAddr( FasmAccessHandle, USlider );
#define UTL_SetFasmAccessStartAddr _UTL_SetFasmAccessStartAddr
extern void _UTL_SetFasmAccessStopAddr ( FasmAccessHandle, USlider );
#define UTL_SetFasmAccessStopAddr _UTL_SetFasmAccessStopAddr
extern void _UTL_SetFasmAccessBitBlock ( FasmAccessHandle, RadioButton );
#define UTL_SetFasmAccessBitBlock _UTL_SetFasmAccessBitBlock
extern USlider _UTL_ReadFasmStoreCnt ( FasmAccessHandle );
#define UTL_ReadFasmStoreCnt _UTL_ReadFasmStoreCnt
extern CheckButton _UTL_ReadFasmStoreLimitOver( FasmAccessHandle );
#define UTL_ReadFasmStoreLimitOver _UTL_ReadFasmStoreLimitOver
extern void _UTL_ReadFasm ( FasmAccessHandle, void *, void *, void *, void *, USlider, USlider );
#define UTL_ReadFasm _UTL_ReadFasm
extern void _UTL_WriteFasm ( FasmAccessHandle, void *, void *, void *, void *, USlider, USlider );
#define UTL_WriteFasm _UTL_WriteFasm
extern void _UTL_ReadFasmRawData ( FasmAccessHandle, void *, USlider);
#define UTL_ReadFasmRawData _UTL_ReadFasmRawData
 extern FailFilterConfigHandle _UTL_GetFailFilterConfigHandle ( void );
#define UTL_GetFailFilterConfigHandle _UTL_GetFailFilterConfigHandle
 extern void _UTL_SetFailFilterConfigAction ( FailFilterConfigHandle, RadioButton );
#define UTL_SetFailFilterConfigAction _UTL_SetFailFilterConfigAction
 extern void _UTL_SetFailFilterConfigDutBitSize ( FailFilterConfigHandle, USlider );
#define UTL_SetFailFilterConfigDutBitSize _UTL_SetFailFilterConfigDutBitSize
 extern void _UTL_SetFailFilterConfigBitSize ( FailFilterConfigHandle, USlider );
#define UTL_SetFailFilterConfigBitSize _UTL_SetFailFilterConfigBitSize
 extern void _UTL_SetFailFilterConfigPinList ( FailFilterConfigHandle, USlider, char *, CheckButton, USlider );
#define UTL_SetFailFilterConfigPinList _UTL_SetFailFilterConfigPinList
 extern void _UTL_SetFailFilterConfigNibbleMode ( FailFilterConfigHandle, RadioButton );
#define UTL_SetFailFilterConfigNibbleMode _UTL_SetFailFilterConfigNibbleMode
 extern void _UTL_SetFailFilterConfigBlockSize ( FailFilterConfigHandle, USlider );
#define UTL_SetFailFilterConfigBlockSize _UTL_SetFailFilterConfigBlockSize
 extern void _UTL_SetFailFilterConfigStatusBytes ( FailFilterConfigHandle, RadioButton );
#define UTL_SetFailFilterConfigStatusBytes _UTL_SetFailFilterConfigStatusBytes
 extern void _UTL_SetFailFilterConfigPageSize ( FailFilterConfigHandle, USlider );
#define UTL_SetFailFilterConfigPageSize _UTL_SetFailFilterConfigPageSize
 extern void _UTL_SetFailFilterConfigLowThreshold ( FailFilterConfigHandle, RadioButton, USlider );
#define UTL_SetFailFilterConfigLowThreshold _UTL_SetFailFilterConfigLowThreshold
 extern void _UTL_SetFailFilterConfigHighThreshold ( FailFilterConfigHandle, RadioButton, USlider );
#define UTL_SetFailFilterConfigHighThreshold _UTL_SetFailFilterConfigHighThreshold
 extern void _UTL_SetFailFilterConfigRepairRegionHighThreshold ( FailFilterConfigHandle, RadioButton, USlider );
#define UTL_SetFailFilterConfigRepairRegionHighThreshold _UTL_SetFailFilterConfigRepairRegionHighThreshold
 extern void _UTL_SetFailFilterConfigTFCHighThreshold ( FailFilterConfigHandle, RadioButton, USlider );
#define UTL_SetFailFilterConfigTFCHighThreshold _UTL_SetFailFilterConfigTFCHighThreshold
 extern void _UTL_SetFailFilterConfigECCSectors ( FailFilterConfigHandle, USlider, USlider, USlider );
#define UTL_SetFailFilterConfigECCSectors _UTL_SetFailFilterConfigECCSectors
 extern void _UTL_SetFailFilterConfigRepairRegion ( FailFilterConfigHandle, USlider, USlider, USlider );
#define UTL_SetFailFilterConfigRepairRegion _UTL_SetFailFilterConfigRepairRegion
 extern void _UTL_SetFailFilterConfigMode ( FailFilterConfigHandle, RadioButton, CheckButton );
#define UTL_SetFailFilterConfigMode _UTL_SetFailFilterConfigMode
 extern void _UTL_SetFailFilterConfigFailListCounterSelect ( FailFilterConfigHandle, RadioButton, CheckButton );
#define UTL_SetFailFilterConfigFailListCounterSelect _UTL_SetFailFilterConfigFailListCounterSelect
 extern void _UTL_SetFailFilterConfigTFCOverlayCount ( FailFilterConfigHandle, CheckButton );
#define UTL_SetFailFilterConfigTFCOverlayCount _UTL_SetFailFilterConfigTFCOverlayCount
 extern void _UTL_SetFailFilterConfigOverlaySignal ( FailFilterConfigHandle, RadioButton, RadioButton );
#define UTL_SetFailFilterConfigOverlaySignal _UTL_SetFailFilterConfigOverlaySignal
 extern void _UTL_SetFailFilterConfigAddrAssign ( FailFilterConfigHandle, RadioButton, RadioButton, RadioButton );
#define UTL_SetFailFilterConfigAddrAssign _UTL_SetFailFilterConfigAddrAssign
 extern void _UTL_SetFailFilterConfigColumnStartAddressBit ( FailFilterConfigHandle, USlider*, USlider );
#define UTL_SetFailFilterConfigColumnStartAddressBit _UTL_SetFailFilterConfigColumnStartAddressBit
 extern void _UTL_SetFailFilterConfigColumnAddress ( FailFilterConfigHandle, USlider*, USlider );
#define UTL_SetFailFilterConfigColumnAddress _UTL_SetFailFilterConfigColumnAddress
 extern void _UTL_SetFailFilterConfigDdrMode ( FailFilterConfigHandle, CheckButton );
#define UTL_SetFailFilterConfigDdrMode _UTL_SetFailFilterConfigDdrMode
 extern void _UTL_SetFailFilterConfigBypassSignal ( FailFilterConfigHandle, RadioButton, RadioButton );
#define UTL_SetFailFilterConfigBypassSignal _UTL_SetFailFilterConfigBypassSignal
 extern void _UTL_SetFailFilterConfigFlashCounterTransferSignal ( FailFilterConfigHandle, RadioButton );
#define UTL_SetFailFilterConfigFlashCounterTransferSignal _UTL_SetFailFilterConfigFlashCounterTransferSignal
 extern void _UTL_SendFailFilterConfig ( FailFilterConfigHandle );
#define UTL_SendFailFilterConfig _UTL_SendFailFilterConfig
 extern FailListAccessHandle _UTL_GetFailListAccessHandle ( void );
#define UTL_GetFailListAccessHandle _UTL_GetFailListAccessHandle
 extern void _UTL_SetFailListAccessTestSelect ( FailListAccessHandle, RadioButton );
#define UTL_SetFailListAccessTestSelect _UTL_SetFailListAccessTestSelect
 extern void _UTL_AddFailListAccessTestName ( FailListAccessHandle, char *);
#define UTL_AddFailListAccessTestName _UTL_AddFailListAccessTestName
 extern void _UTL_ClearFailListAccessTestName ( FailListAccessHandle );
#define UTL_ClearFailListAccessTestName _UTL_ClearFailListAccessTestName
 extern void _UTL_SetFailListAccessAllDut ( FailListAccessHandle, CheckButton );
#define UTL_SetFailListAccessAllDut _UTL_SetFailListAccessAllDut
 extern void _UTL_SetFailListAccessDut ( FailListAccessHandle, UT_DUT );
#define UTL_SetFailListAccessDut _UTL_SetFailListAccessDut
 extern void _UTL_SetFailListAccessDeviceChannel ( FailListAccessHandle, USlider );
#define UTL_SetFailListAccessDeviceChannel _UTL_SetFailListAccessDeviceChannel
 extern void _UTL_SetFailListAccessAllBit ( FailListAccessHandle, CheckButton );
#define UTL_SetFailListAccessAllBit _UTL_SetFailListAccessAllBit
 extern void _UTL_AddFailListAccessBit ( FailListAccessHandle, RadioButton );
#define UTL_AddFailListAccessBit _UTL_AddFailListAccessBit
 extern void _UTL_ClearFailListAccessBit ( FailListAccessHandle );
#define UTL_ClearFailListAccessBit _UTL_ClearFailListAccessBit
 extern void _UTL_SetFailListAccessCountType ( FailListAccessHandle, RadioButton );
#define UTL_SetFailListAccessCountType _UTL_SetFailListAccessCountType
 extern void _UTL_SetFailListAccessApLink ( FailListAccessHandle, RadioButton );
#define UTL_SetFailListAccessApLink _UTL_SetFailListAccessApLink
 extern void _UTL_SetFailListAccessXAddr ( FailListAccessHandle, USlider, USlider );
#define UTL_SetFailListAccessXAddr _UTL_SetFailListAccessXAddr
 extern void _UTL_SetFailListAccessYAddr ( FailListAccessHandle, USlider, USlider );
#define UTL_SetFailListAccessYAddr _UTL_SetFailListAccessYAddr
 extern USlider _UTL_ReadFailListBadBlockCount ( FailListAccessHandle h, RadioButton *status );
#define UTL_ReadFailListBadBlockCount _UTL_ReadFailListBadBlockCount
 extern void _UTL_ReadFailListBadBlock ( FailListAccessHandle h, USlider *blockNum, RadioButton *reason, USlider bbCnt );
#define UTL_ReadFailListBadBlock _UTL_ReadFailListBadBlock
 extern void _UTL_WriteFailListBadBlock ( FailListAccessHandle h, USlider *blockNum, RadioButton *reason, USlider bbCnt );
#define UTL_WriteFailListBadBlock _UTL_WriteFailListBadBlock
 extern USlider _UTL_ReadFailListAddressCount ( FailListAccessHandle h, RadioButton *status );
#define UTL_ReadFailListAddressCount _UTL_ReadFailListAddressCount
 extern void _UTL_ReadFailList ( FailListAccessHandle h, USlider *xList, USlider *yList, USlider *dqList, USlider *ndqList, USlider bufSize );
#define UTL_ReadFailList _UTL_ReadFailList
 extern void _UTL_ReadFailListBitMap ( FailListAccessHandle h, unsigned char *bitMapData, USlider bufSize );
#define UTL_ReadFailListBitMap _UTL_ReadFailListBitMap
 extern void _UTL_ReadFailListStatusBytes ( FailListAccessHandle h, USlider *pageX, USlider *pageY, USlider *statusByteList, USlider pageCnt);
#define UTL_ReadFailListStatusBytes _UTL_ReadFailListStatusBytes
 extern USlider _UTL_ReadFailListFlashCounter ( FailListAccessHandle h );
#define UTL_ReadFailListFlashCounter _UTL_ReadFailListFlashCounter
 extern void _UTL_ReadFailListTfcCount ( FailListAccessHandle h, USlider *tfcCnt, RadioButton *status );
#define UTL_ReadFailListTfcCount _UTL_ReadFailListTfcCount
 extern void _UTL_ReadFailListEccCount ( FailListAccessHandle h, USlider *eccCntList, RadioButton *statusList, USlider bufSize );
#define UTL_ReadFailListEccCount _UTL_ReadFailListEccCount
 extern void _UTL_ReadFailListRrCount ( FailListAccessHandle h, USlider *rrCntList, RadioButton *statusList, USlider bufSize );
#define UTL_ReadFailListRrCount _UTL_ReadFailListRrCount
 extern void _UTL_SetFailListAccessRecordType ( FailListAccessHandle, RadioButton );
#define UTL_SetFailListAccessRecordType _UTL_SetFailListAccessRecordType
 extern void _UTL_ReadFailListRecordCount ( FailListAccessHandle h, USlider *pageCnt, USlider *dataCnt);
#define UTL_ReadFailListRecordCount _UTL_ReadFailListRecordCount
 extern void _UTL_ReadFailListFlashCounters ( FailListAccessHandle h, USlider *pageX, USlider *pageY, USlider *flashCounterList, USlider pageCnt);
#define UTL_ReadFailListFlashCounters _UTL_ReadFailListFlashCounters
 extern void _UTL_OverlayFailList ( FailListAccessHandle h, CheckButton deleteSource );
#define UTL_OverlayFailList _UTL_OverlayFailList
 extern void _UTL_ResetFailList ( FailListAccessHandle h, CheckButton clearFailAddr, CheckButton clearFailCnt );
#define UTL_ResetFailList _UTL_ResetFailList
 extern void _UTL_DeleteFailList ( FailListAccessHandle h );
#define UTL_DeleteFailList _UTL_DeleteFailList
extern void _UTL_WriteMultiPlaneStatusJudgeTable( USlider *, USlider );
#define UTL_WriteMultiPlaneStatusJudgeTable _UTL_WriteMultiPlaneStatusJudgeTable
extern FailSelPinHandle _UTL_GetFailSelPinHandle( void );
#define UTL_GetFailSelPinHandle _UTL_GetFailSelPinHandle
extern void _UTL_SetFailSelPinTarget( FailSelPinHandle, RadioButton );
#define UTL_SetFailSelPinTarget _UTL_SetFailSelPinTarget
extern void _UTL_AddFailSelPinAssign( FailSelPinHandle, RadioButton, UT_PIN );
#define UTL_AddFailSelPinAssign _UTL_AddFailSelPinAssign
extern void _UTL_ClearFailSelPinAssign( FailSelPinHandle );
#define UTL_ClearFailSelPinAssign _UTL_ClearFailSelPinAssign
extern void _UTL_SetFailSelPin( FailSelPinHandle, UT_PIN, CheckButton );
#define UTL_SetFailSelPin _UTL_SetFailSelPin
extern void _UTL_SendFailSelPin( FailSelPinHandle );
#define UTL_SendFailSelPin _UTL_SendFailSelPin
 extern EccConfigHandle _UTL_GetEccConfigHandle (void);
#define UTL_GetEccConfigHandle _UTL_GetEccConfigHandle
 extern void _UTL_SetEccConfigCounterNoClear (EccConfigHandle, CheckButton);
#define UTL_SetEccConfigCounterNoClear _UTL_SetEccConfigCounterNoClear
 extern void _UTL_SetEccConfigCounterLimit (EccConfigHandle, RadioButton, RadioButton, USlider);
#define UTL_SetEccConfigCounterLimit _UTL_SetEccConfigCounterLimit
 extern void _UTL_SetEccConfigCounterEnableSignal (EccConfigHandle, RadioButton, RadioButton);
#define UTL_SetEccConfigCounterEnableSignal _UTL_SetEccConfigCounterEnableSignal
 extern void _UTL_SetEccConfigJudgeSignal (EccConfigHandle, RadioButton, RadioButton);
#define UTL_SetEccConfigJudgeSignal _UTL_SetEccConfigJudgeSignal
 extern void _UTL_SetEccConfigCounterClearSignal (EccConfigHandle, RadioButton);
#define UTL_SetEccConfigCounterClearSignal _UTL_SetEccConfigCounterClearSignal
 extern void _UTL_SetEccConfigSectorCount (EccConfigHandle, RadioButton);
#define UTL_SetEccConfigSectorCount _UTL_SetEccConfigSectorCount
 extern void _UTL_SetEccConfigSectorSwitchSignal (EccConfigHandle, RadioButton);
#define UTL_SetEccConfigSectorSwitchSignal _UTL_SetEccConfigSectorSwitchSignal
 extern void _UTL_SendEccConfig (EccConfigHandle);
#define UTL_SendEccConfig _UTL_SendEccConfig
 extern TprogConfigHandle _UTL_GetTprogConfigHandle (void);
#define UTL_GetTprogConfigHandle _UTL_GetTprogConfigHandle
 extern void _UTL_SetTprogConfigAverageLimit (TprogConfigHandle, USlider);
#define UTL_SetTprogConfigAverageLimit _UTL_SetTprogConfigAverageLimit
 extern void _UTL_SetTprogConfigMaxLimit (TprogConfigHandle, USlider);
#define UTL_SetTprogConfigMaxLimit _UTL_SetTprogConfigMaxLimit
 extern void _UTL_SetTprogConfigCounterEnableSignal (TprogConfigHandle, RadioButton);
#define UTL_SetTprogConfigCounterEnableSignal _UTL_SetTprogConfigCounterEnableSignal
 extern void _UTL_SetTprogConfigJudgeSignal (TprogConfigHandle, RadioButton);
#define UTL_SetTprogConfigJudgeSignal _UTL_SetTprogConfigJudgeSignal
 extern void _UTL_SetTprogConfigCounterClearSignal (TprogConfigHandle, RadioButton);
#define UTL_SetTprogConfigCounterClearSignal _UTL_SetTprogConfigCounterClearSignal
 extern void _UTL_SendTprogConfig (TprogConfigHandle);
#define UTL_SendTprogConfig _UTL_SendTprogConfig
 extern AfmPatternInfoHandle _UTL_GetAfmPatternInfoHandle (void);
#define UTL_GetAfmPatternInfoHandle _UTL_GetAfmPatternInfoHandle
 extern void _UTL_SetAfmPatternInfoMpatName (AfmPatternInfoHandle, char *);
#define UTL_SetAfmPatternInfoMpatName _UTL_SetAfmPatternInfoMpatName
 extern USlider _UTL_AddAfmPatternInfoModule (AfmPatternInfoHandle);
#define UTL_AddAfmPatternInfoModule _UTL_AddAfmPatternInfoModule
 extern void _UTL_SetAfmPatternInfoStartPc (AfmPatternInfoHandle, USlider, USlider);
#define UTL_SetAfmPatternInfoStartPc _UTL_SetAfmPatternInfoStartPc
 extern void _UTL_SetAfmPatternInfoBitSize (AfmPatternInfoHandle, USlider, USlider);
#define UTL_SetAfmPatternInfoBitSize _UTL_SetAfmPatternInfoBitSize
 extern void _UTL_SetAfmPatternInfoAMinXAddr (AfmPatternInfoHandle, USlider, USlider);
#define UTL_SetAfmPatternInfoAMinXAddr _UTL_SetAfmPatternInfoAMinXAddr
 extern void _UTL_SetAfmPatternInfoAMinYAddr (AfmPatternInfoHandle, USlider, USlider);
#define UTL_SetAfmPatternInfoAMinYAddr _UTL_SetAfmPatternInfoAMinYAddr
 extern void _UTL_SetAfmPatternInfoAMinZAddr (AfmPatternInfoHandle, USlider, USlider);
#define UTL_SetAfmPatternInfoAMinZAddr _UTL_SetAfmPatternInfoAMinZAddr
 extern void _UTL_SetAfmPatternInfoAMaxXAddr (AfmPatternInfoHandle, USlider, USlider);
#define UTL_SetAfmPatternInfoAMaxXAddr _UTL_SetAfmPatternInfoAMaxXAddr
 extern void _UTL_SetAfmPatternInfoAMaxYAddr (AfmPatternInfoHandle, USlider, USlider);
#define UTL_SetAfmPatternInfoAMaxYAddr _UTL_SetAfmPatternInfoAMaxYAddr
 extern void _UTL_SetAfmPatternInfoAMaxZAddr (AfmPatternInfoHandle, USlider, USlider);
#define UTL_SetAfmPatternInfoAMaxZAddr _UTL_SetAfmPatternInfoAMaxZAddr
 extern void _UTL_ReadAfmPatternInfo (AfmPatternInfoHandle);
#define UTL_ReadAfmPatternInfo _UTL_ReadAfmPatternInfo
 extern void _UTL_WriteAfmPatternInfo (AfmPatternInfoHandle);
#define UTL_WriteAfmPatternInfo _UTL_WriteAfmPatternInfo
 extern AfmPatternAccessHandle _UTL_GetAfmPatternAccessHandle (void);
#define UTL_GetAfmPatternAccessHandle _UTL_GetAfmPatternAccessHandle
 extern void _UTL_SetAfmPatternAccessAfmPatternInfo (AfmPatternAccessHandle, AfmPatternInfoHandle);
#define UTL_SetAfmPatternAccessAfmPatternInfo _UTL_SetAfmPatternAccessAfmPatternInfo
 extern void _UTL_SetAfmPatternAccessModuleIndex (AfmPatternAccessHandle, USlider);
#define UTL_SetAfmPatternAccessModuleIndex _UTL_SetAfmPatternAccessModuleIndex
 extern void _UTL_SetAfmPatternAccessAreaIndex (AfmPatternAccessHandle, RadioButton);
#define UTL_SetAfmPatternAccessAreaIndex _UTL_SetAfmPatternAccessAreaIndex
 extern void _UTL_SetAfmPatternAccessAreaReadMode (AfmPatternAccessHandle, CheckButton);
#define UTL_SetAfmPatternAccessAreaReadMode _UTL_SetAfmPatternAccessAreaReadMode
 extern void _UTL_SetAfmPatternAccessDataFormat (AfmPatternAccessHandle, RadioButton);
#define UTL_SetAfmPatternAccessDataFormat _UTL_SetAfmPatternAccessDataFormat
 extern void _UTL_SetAfmPatternAccessBitBlockNum (AfmPatternAccessHandle, USlider);
#define UTL_SetAfmPatternAccessBitBlockNum _UTL_SetAfmPatternAccessBitBlockNum
 extern void _UTL_SetAfmPatternAccessBitBlock (AfmPatternAccessHandle, RadioButton);
#define UTL_SetAfmPatternAccessBitBlock _UTL_SetAfmPatternAccessBitBlock
 extern void _UTL_SetAfmPatternAccessXAddr (AfmPatternAccessHandle, USlider, USlider);
#define UTL_SetAfmPatternAccessXAddr _UTL_SetAfmPatternAccessXAddr
 extern void _UTL_SetAfmPatternAccessYAddr (AfmPatternAccessHandle, USlider, USlider);
#define UTL_SetAfmPatternAccessYAddr _UTL_SetAfmPatternAccessYAddr
 extern void _UTL_SetAfmPatternAccessZAddr (AfmPatternAccessHandle, USlider, USlider);
#define UTL_SetAfmPatternAccessZAddr _UTL_SetAfmPatternAccessZAddr
 extern void _UTL_SetAfmPatternAccessAMaxXAddr (AfmPatternAccessHandle, USlider);
#define UTL_SetAfmPatternAccessAMaxXAddr _UTL_SetAfmPatternAccessAMaxXAddr
 extern void _UTL_SetAfmPatternAccessAMaxYAddr (AfmPatternAccessHandle, USlider);
#define UTL_SetAfmPatternAccessAMaxYAddr _UTL_SetAfmPatternAccessAMaxYAddr
 extern void _UTL_SetAfmPatternAccessAMaxZAddr (AfmPatternAccessHandle, USlider);
#define UTL_SetAfmPatternAccessAMaxZAddr _UTL_SetAfmPatternAccessAMaxZAddr
 extern void _UTL_ReadAfmPattern (AfmPatternAccessHandle, void *, USlider);
#define UTL_ReadAfmPattern _UTL_ReadAfmPattern
 extern void _UTL_WriteAfmPattern (AfmPatternAccessHandle, void *, USlider);
#define UTL_WriteAfmPattern _UTL_WriteAfmPattern
 extern FcmMultiSideConfigHandle _UTL_GetFcmMultiSideConfigHandle ( void );
#define UTL_GetFcmMultiSideConfigHandle _UTL_GetFcmMultiSideConfigHandle
 extern void _UTL_SetFcmMultiSideConfigSideCount( FcmMultiSideConfigHandle, RadioButton );
#define UTL_SetFcmMultiSideConfigSideCount _UTL_SetFcmMultiSideConfigSideCount
 extern void _UTL_SetFcmMultiSideConfigSideMode ( FcmMultiSideConfigHandle, RadioButton, RadioButton );
#define UTL_SetFcmMultiSideConfigSideMode _UTL_SetFcmMultiSideConfigSideMode
 extern void _UTL_SendFcmMultiSideConfig ( FcmMultiSideConfigHandle );
#define UTL_SendFcmMultiSideConfig _UTL_SendFcmMultiSideConfig
extern PmConfigHandle _UTL_GetPmConfigHandle ( void );
#define UTL_GetPmConfigHandle _UTL_GetPmConfigHandle
extern void _UTL_SetPmConfigBitSize ( PmConfigHandle, USlider );
#define UTL_SetPmConfigBitSize _UTL_SetPmConfigBitSize
extern void _UTL_SetPmConfigAddrAssign ( PmConfigHandle, RadioButton, RadioButton );
#define UTL_SetPmConfigAddrAssign _UTL_SetPmConfigAddrAssign
extern void _UTL_SetPmConfigAction ( PmConfigHandle, RadioButton );
#define UTL_SetPmConfigAction _UTL_SetPmConfigAction
extern void _UTL_SetPmConfigFixData ( PmConfigHandle, RadioButton, USlider );
#define UTL_SetPmConfigFixData _UTL_SetPmConfigFixData
extern void _UTL_SetPmConfigRate( PmConfigHandle, RadioButton );
#define UTL_SetPmConfigRate _UTL_SetPmConfigRate
extern void _UTL_SendPmConfig ( PmConfigHandle );
#define UTL_SendPmConfig _UTL_SendPmConfig
extern PmAccessHandle _UTL_GetPmAccessHandle ( void );
#define UTL_GetPmAccessHandle _UTL_GetPmAccessHandle
extern void _UTL_SetPmAccessCompactionMode ( PmAccessHandle, RadioButton );
#define UTL_SetPmAccessCompactionMode _UTL_SetPmAccessCompactionMode
extern void _UTL_SetPmAccessBitMode ( PmAccessHandle, RadioButton );
#define UTL_SetPmAccessBitMode _UTL_SetPmAccessBitMode
extern void _UTL_SetPmAccessAllBit ( PmAccessHandle, CheckButton );
#define UTL_SetPmAccessAllBit _UTL_SetPmAccessAllBit
extern void _UTL_AddPmAccessBit ( PmAccessHandle, RadioButton );
#define UTL_AddPmAccessBit _UTL_AddPmAccessBit
extern void _UTL_ClearPmAccessBit ( PmAccessHandle );
#define UTL_ClearPmAccessBit _UTL_ClearPmAccessBit
extern void _UTL_SetPmAccessBitBlock ( PmAccessHandle, RadioButton );
#define UTL_SetPmAccessBitBlock _UTL_SetPmAccessBitBlock
extern void _UTL_SetPmAccessPresetAllMemory ( PmAccessHandle, CheckButton );
#define UTL_SetPmAccessPresetAllMemory _UTL_SetPmAccessPresetAllMemory
extern void _UTL_SetPmAccessAddrAssign ( PmAccessHandle, RadioButton, RadioButton );
#define UTL_SetPmAccessAddrAssign _UTL_SetPmAccessAddrAssign
extern void _UTL_SetPmAccessApLink ( PmAccessHandle, RadioButton );
#define UTL_SetPmAccessApLink _UTL_SetPmAccessApLink
extern void _UTL_SetPmAccessStartAddr ( PmAccessHandle, USlider );
#define UTL_SetPmAccessStartAddr _UTL_SetPmAccessStartAddr
extern void _UTL_SetPmAccessStopAddr ( PmAccessHandle, USlider );
#define UTL_SetPmAccessStopAddr _UTL_SetPmAccessStopAddr
extern void _UTL_SetPmAccessXAddr ( PmAccessHandle, USlider, USlider );
#define UTL_SetPmAccessXAddr _UTL_SetPmAccessXAddr
extern void _UTL_SetPmAccessYAddr ( PmAccessHandle, USlider, USlider );
#define UTL_SetPmAccessYAddr _UTL_SetPmAccessYAddr
extern void _UTL_SetPmAccessAllDut ( PmAccessHandle, CheckButton );
#define UTL_SetPmAccessAllDut _UTL_SetPmAccessAllDut
extern void _UTL_SetPmAccessDut ( PmAccessHandle, UT_DUT );
#define UTL_SetPmAccessDut _UTL_SetPmAccessDut
extern void _UTL_PresetPm ( PmAccessHandle, USlider );
#define UTL_PresetPm _UTL_PresetPm
extern void _UTL_ReadPm ( PmAccessHandle, void *, USlider );
#define UTL_ReadPm _UTL_ReadPm
extern void _UTL_WritePm ( PmAccessHandle, void *, USlider );
#define UTL_WritePm _UTL_WritePm
extern EbmConfigHandle _UTL_GetEbmConfigHandle( void );
#define UTL_GetEbmConfigHandle _UTL_GetEbmConfigHandle
extern void _UTL_SetEbmConfigPatternSelect( EbmConfigHandle, RadioButton );
#define UTL_SetEbmConfigPatternSelect _UTL_SetEbmConfigPatternSelect
extern void _UTL_SetEbmConfigBitSize( EbmConfigHandle, USlider );
#define UTL_SetEbmConfigBitSize _UTL_SetEbmConfigBitSize
extern void _UTL_SetEbmConfigDdrMode( EbmConfigHandle, CheckButton );
#define UTL_SetEbmConfigDdrMode _UTL_SetEbmConfigDdrMode
extern void _UTL_SetEbmConfigTransferSignal( EbmConfigHandle, RadioButton );
#define UTL_SetEbmConfigTransferSignal _UTL_SetEbmConfigTransferSignal
extern void _UTL_SetEbmConfigTransferAreaSize( EbmConfigHandle, USlider );
#define UTL_SetEbmConfigTransferAreaSize _UTL_SetEbmConfigTransferAreaSize
extern void _UTL_SetEbmConfigTransferAreaCount( EbmConfigHandle, USlider );
#define UTL_SetEbmConfigTransferAreaCount _UTL_SetEbmConfigTransferAreaCount
extern void _UTL_SetEbmConfigTransferAreaRepeatCount( EbmConfigHandle, USlider );
#define UTL_SetEbmConfigTransferAreaRepeatCount _UTL_SetEbmConfigTransferAreaRepeatCount
extern void _UTL_SetEbmConfigSequenceTable( EbmConfigHandle, void *, USlider );
#define UTL_SetEbmConfigSequenceTable _UTL_SetEbmConfigSequenceTable
extern void _UTL_SendEbmConfig( EbmConfigHandle );
#define UTL_SendEbmConfig _UTL_SendEbmConfig
extern EbmAccessHandle _UTL_GetEbmAccessHandle( void );
#define UTL_GetEbmAccessHandle _UTL_GetEbmAccessHandle
extern void _UTL_SetEbmAccessStartIndex( EbmAccessHandle, USlider );
#define UTL_SetEbmAccessStartIndex _UTL_SetEbmAccessStartIndex
extern void _UTL_WriteEbm( EbmAccessHandle, void *, USlider );
#define UTL_WriteEbm _UTL_WriteEbm
extern void _UTL_WriteEbmFromFile( EbmAccessHandle, char * );
#define UTL_WriteEbmFromFile _UTL_WriteEbmFromFile
extern DfmConfigHandle _UTL_GetDfmConfigHandle( void );
#define UTL_GetDfmConfigHandle _UTL_GetDfmConfigHandle
extern void _UTL_SetDfmConfigStoreCycle( DfmConfigHandle, RadioButton );
#define UTL_SetDfmConfigStoreCycle _UTL_SetDfmConfigStoreCycle
extern void _UTL_SetDfmConfigCountMode ( DfmConfigHandle, RadioButton );
#define UTL_SetDfmConfigCountMode _UTL_SetDfmConfigCountMode
extern void _UTL_SetDfmConfigCountValue( DfmConfigHandle, USlider, RadioButton );
#define UTL_SetDfmConfigCountValue _UTL_SetDfmConfigCountValue
extern void _UTL_SetDfmConfigAddrScramByAlpg( DfmConfigHandle, RadioButton, CheckButton );
#define UTL_SetDfmConfigAddrScramByAlpg _UTL_SetDfmConfigAddrScramByAlpg
extern void _UTL_SetDfmConfigModeDelayByAlpg( DfmConfigHandle, RadioButton, RadioButton, USlider );
#define UTL_SetDfmConfigModeDelayByAlpg _UTL_SetDfmConfigModeDelayByAlpg
extern void _UTL_SetDfmConfigModeDelayByPds ( DfmConfigHandle, RadioButton, RadioButton, USlider );
#define UTL_SetDfmConfigModeDelayByPds _UTL_SetDfmConfigModeDelayByPds
extern void _UTL_SetDfmConfigMultiMode( DfmConfigHandle, RadioButton );
#define UTL_SetDfmConfigMultiMode _UTL_SetDfmConfigMultiMode
extern void _UTL_SetDfmConfigDut ( DfmConfigHandle, UT_DUT );
#define UTL_SetDfmConfigDut _UTL_SetDfmConfigDut
extern void _UTL_SetDfmConfigAllPin ( DfmConfigHandle, CheckButton );
#define UTL_SetDfmConfigAllPin _UTL_SetDfmConfigAllPin
extern void _UTL_AddDfmConfigTargetPin ( DfmConfigHandle, UT_PIN );
#define UTL_AddDfmConfigTargetPin _UTL_AddDfmConfigTargetPin
extern void _UTL_ClearDfmConfigTargetPin( DfmConfigHandle );
#define UTL_ClearDfmConfigTargetPin _UTL_ClearDfmConfigTargetPin
extern void _UTL_SetDfmConfigTargetMemory( DfmConfigHandle, RadioButton );
#define UTL_SetDfmConfigTargetMemory _UTL_SetDfmConfigTargetMemory
extern void _UTL_SendDfmConfig( DfmConfigHandle );
#define UTL_SendDfmConfig _UTL_SendDfmConfig
extern DfmAccessHandle _UTL_GetDfmAccessHandle ( void );
#define UTL_GetDfmAccessHandle _UTL_GetDfmAccessHandle
extern void _UTL_SetDfmAccessAlpgUnit ( DfmAccessHandle, RadioButton );
#define UTL_SetDfmAccessAlpgUnit _UTL_SetDfmAccessAlpgUnit
extern void _UTL_SetDfmAccessDataNumber ( DfmAccessHandle, USlider );
#define UTL_SetDfmAccessDataNumber _UTL_SetDfmAccessDataNumber
extern void _UTL_SetDfmAccessDataCount ( DfmAccessHandle, USlider );
#define UTL_SetDfmAccessDataCount _UTL_SetDfmAccessDataCount
extern void _UTL_AddDfmAccessDut ( DfmAccessHandle, UT_DUT );
#define UTL_AddDfmAccessDut _UTL_AddDfmAccessDut
extern void _UTL_ClearDfmAccessDut ( DfmAccessHandle );
#define UTL_ClearDfmAccessDut _UTL_ClearDfmAccessDut
extern void _UTL_UpdateDfmData( DfmAccessHandle );
#define UTL_UpdateDfmData _UTL_UpdateDfmData
extern int _UTL_GetDfmDataUs ( DfmAccessHandle, RadioButton, RadioButton, USlider, USlider * );
#define UTL_GetDfmDataUs _UTL_GetDfmDataUs
extern int _UTL_GetDfmDataCb ( DfmAccessHandle, RadioButton, USlider, USlider, CheckButton * );
#define UTL_GetDfmDataCb _UTL_GetDfmDataCb
extern int _UTL_GetDfmDataPin( DfmAccessHandle, RadioButton, UT_DUT, UT_PIN, USlider, USlider, CheckButton * );
#define UTL_GetDfmDataPin _UTL_GetDfmDataPin
extern DfmFailAddrHandle _UTL_GetDfmFailAddrHandle( void );
#define UTL_GetDfmFailAddrHandle _UTL_GetDfmFailAddrHandle
extern void _UTL_SetDfmFailAddrAlpgUnit ( DfmFailAddrHandle , RadioButton ) ;
#define UTL_SetDfmFailAddrAlpgUnit _UTL_SetDfmFailAddrAlpgUnit
extern void _UTL_SetDfmFailAddrDataNumber ( DfmFailAddrHandle , USlider );
#define UTL_SetDfmFailAddrDataNumber _UTL_SetDfmFailAddrDataNumber
extern void _UTL_SetDfmFailAddrDataCount ( DfmFailAddrHandle , USlider );
#define UTL_SetDfmFailAddrDataCount _UTL_SetDfmFailAddrDataCount
extern void _UTL_SetDfmFailAddrDut ( DfmFailAddrHandle , UT_DUT );
#define UTL_SetDfmFailAddrDut _UTL_SetDfmFailAddrDut
extern void _UTL_SetDfmFailAddrTargetPin ( DfmFailAddrHandle , UT_PIN );
#define UTL_SetDfmFailAddrTargetPin _UTL_SetDfmFailAddrTargetPin
extern void _UTL_UpdateDfmFailAddr ( DfmFailAddrHandle );
#define UTL_UpdateDfmFailAddr _UTL_UpdateDfmFailAddr
extern int _UTL_GetDfmFailAddrFailCount ( DfmFailAddrHandle , USlider * );
#define UTL_GetDfmFailAddrFailCount _UTL_GetDfmFailAddrFailCount
extern void _UTL_GetDfmFailAddrData ( DfmFailAddrHandle , void *, USlider, USlider );
#define UTL_GetDfmFailAddrData _UTL_GetDfmFailAddrData
extern DfmStatusHandle _UTL_GetDfmStatusHandle( void );
#define UTL_GetDfmStatusHandle _UTL_GetDfmStatusHandle
extern void _UTL_SetDfmStatusAlpgUnit( DfmStatusHandle , RadioButton ) ;
#define UTL_SetDfmStatusAlpgUnit _UTL_SetDfmStatusAlpgUnit
extern void _UTL_SetDfmStatusDut ( DfmStatusHandle , UT_DUT );
#define UTL_SetDfmStatusDut _UTL_SetDfmStatusDut
extern void _UTL_UpdateDfmStatus ( DfmStatusHandle );
#define UTL_UpdateDfmStatus _UTL_UpdateDfmStatus
extern int _UTL_GetDfmCounter ( DfmStatusHandle , RadioButton , USlider * , CheckButton * );
#define UTL_GetDfmCounter _UTL_GetDfmCounter
extern int _UTL_GetDfmStopFlag ( DfmStatusHandle , CheckButton * );
#define UTL_GetDfmStopFlag _UTL_GetDfmStopFlag
extern int _UTL_GetDfmDataNumber ( DfmStatusHandle , USlider * );
#define UTL_GetDfmDataNumber _UTL_GetDfmDataNumber
extern int _UTL_GetDfmPatternCounter( DfmStatusHandle , RadioButton , USlider * , CheckButton * );
#define UTL_GetDfmPatternCounter _UTL_GetDfmPatternCounter
extern FlashHandle _UTL_GetFlashHandle(void);
#define UTL_GetFlashHandle _UTL_GetFlashHandle
extern void _UTL_SetFlashMaskModeAllDut(FlashHandle, CheckButton);
#define UTL_SetFlashMaskModeAllDut _UTL_SetFlashMaskModeAllDut
extern void _UTL_SetFlashMaskModeByDut(FlashHandle, UT_DUT, CheckButton);
#define UTL_SetFlashMaskModeByDut _UTL_SetFlashMaskModeByDut
extern void _UTL_SetFlashLimitAllDut(FlashHandle, Slider);
#define UTL_SetFlashLimitAllDut _UTL_SetFlashLimitAllDut
extern void _UTL_SetFlashLimitByDut (FlashHandle, UT_DUT, Slider);
#define UTL_SetFlashLimitByDut _UTL_SetFlashLimitByDut
extern void _UTL_SetFlashModeAllDut (FlashHandle, RadioButton);
#define UTL_SetFlashModeAllDut _UTL_SetFlashModeAllDut
extern void _UTL_SetFlashHoldModeAllDut(FlashHandle, RadioButton);
#define UTL_SetFlashHoldModeAllDut _UTL_SetFlashHoldModeAllDut
extern void _UTL_SetFlashHoldConditionAllDut(FlashHandle, RadioButton, RadioButton);
#define UTL_SetFlashHoldConditionAllDut _UTL_SetFlashHoldConditionAllDut
extern void _UTL_SetFlashCounterConditionAllDut(FlashHandle, RadioButton, RadioButton);
#define UTL_SetFlashCounterConditionAllDut _UTL_SetFlashCounterConditionAllDut
extern void _UTL_SetFlashCpInhPinMode (FlashHandle, CheckButton);
#define UTL_SetFlashCpInhPinMode _UTL_SetFlashCpInhPinMode
extern void _UTL_SetFlashCpInhPin (FlashHandle, char *);
#define UTL_SetFlashCpInhPin _UTL_SetFlashCpInhPin
extern void _UTL_SendFlash(FlashHandle);
#define UTL_SendFlash _UTL_SendFlash
extern ReadFlashHoldHandle _UTL_GetReadFlashHoldHandle(void);
#define UTL_GetReadFlashHoldHandle _UTL_GetReadFlashHoldHandle
extern void _UTL_SetReadFlashHoldDut(ReadFlashHoldHandle, UT_DUT);
#define UTL_SetReadFlashHoldDut _UTL_SetReadFlashHoldDut
extern void _UTL_SetReadFlashHoldPin(ReadFlashHoldHandle, UT_PIN);
#define UTL_SetReadFlashHoldPin _UTL_SetReadFlashHoldPin
extern void _UTL_SetReadFlashHoldTargetBank(ReadFlashHoldHandle, RadioButton);
#define UTL_SetReadFlashHoldTargetBank _UTL_SetReadFlashHoldTargetBank
extern RadioButton _UTL_ReadFlashHold(ReadFlashHoldHandle);
#define UTL_ReadFlashHold _UTL_ReadFlashHold
extern ReadFlashCounterHandle _UTL_GetReadFlashCounterHandle(void);
#define UTL_GetReadFlashCounterHandle _UTL_GetReadFlashCounterHandle
extern void _UTL_SetReadFlashCounterDut(ReadFlashCounterHandle, UT_DUT);
#define UTL_SetReadFlashCounterDut _UTL_SetReadFlashCounterDut
extern void _UTL_SetReadFlashCounterChannel(ReadFlashCounterHandle, USlider);
#define UTL_SetReadFlashCounterChannel _UTL_SetReadFlashCounterChannel
extern void _UTL_SetReadFlashCounterTargetBank(ReadFlashCounterHandle, RadioButton);
#define UTL_SetReadFlashCounterTargetBank _UTL_SetReadFlashCounterTargetBank
extern Slider _UTL_ReadFlashCounter(ReadFlashCounterHandle);
#define UTL_ReadFlashCounter _UTL_ReadFlashCounter
extern ReadFlashMaxFailHandle _UTL_GetReadFlashMaxFailHandle(void);
#define UTL_GetReadFlashMaxFailHandle _UTL_GetReadFlashMaxFailHandle
extern void _UTL_SetReadFlashMaxFailDut(ReadFlashMaxFailHandle, UT_DUT);
#define UTL_SetReadFlashMaxFailDut _UTL_SetReadFlashMaxFailDut
extern void _UTL_SetReadFlashMaxFailTargetBank(ReadFlashMaxFailHandle, RadioButton);
#define UTL_SetReadFlashMaxFailTargetBank _UTL_SetReadFlashMaxFailTargetBank
extern CheckButton _UTL_ReadFlashMaxFail(ReadFlashMaxFailHandle);
#define UTL_ReadFlashMaxFail _UTL_ReadFlashMaxFail
extern DbmConfigHandle _UTL_GetDbmConfigHandle(void);
#define UTL_GetDbmConfigHandle _UTL_GetDbmConfigHandle
extern void _UTL_SetDbmConfigAccessMode( DbmConfigHandle , RadioButton );
#define UTL_SetDbmConfigAccessMode _UTL_SetDbmConfigAccessMode
extern int _UTL_GetDbmConfigAccessMode( DbmConfigHandle , RadioButton * );
#define UTL_GetDbmConfigAccessMode _UTL_GetDbmConfigAccessMode
extern void _UTL_SetDbmConfigBitSize( DbmConfigHandle , USlider );
#define UTL_SetDbmConfigBitSize _UTL_SetDbmConfigBitSize
extern int _UTL_GetDbmConfigBitSize( DbmConfigHandle , USlider * );
#define UTL_GetDbmConfigBitSize _UTL_GetDbmConfigBitSize
extern void _UTL_SetDbmConfigBlockSize( DbmConfigHandle h , USlider size );
#define UTL_SetDbmConfigBlockSize _UTL_SetDbmConfigBlockSize
extern int _UTL_GetDbmConfigBlockSize( DbmConfigHandle h, USlider *val );
#define UTL_GetDbmConfigBlockSize _UTL_GetDbmConfigBlockSize
extern void _UTL_SetDbmConfigSequenceTable( DbmConfigHandle h , USlider *SequenceTable, USlider size );
#define UTL_SetDbmConfigSequenceTable _UTL_SetDbmConfigSequenceTable
extern void _UTL_SetDbmConfigAddrAssign( DbmConfigHandle , RadioButton , RadioButton );
#define UTL_SetDbmConfigAddrAssign _UTL_SetDbmConfigAddrAssign
extern int _UTL_GetDbmConfigAddrAssign( DbmConfigHandle , RadioButton , RadioButton * );
#define UTL_GetDbmConfigAddrAssign _UTL_GetDbmConfigAddrAssign
extern void _UTL_SetDbmConfigBitAssignMode( DbmConfigHandle h , RadioButton );
#define UTL_SetDbmConfigBitAssignMode _UTL_SetDbmConfigBitAssignMode
extern int _UTL_GetDbmConfigBitAssignMode( DbmConfigHandle h , RadioButton * );
#define UTL_GetDbmConfigBitAssignMode _UTL_GetDbmConfigBitAssignMode
extern void _UTL_AddDbmConfigPinAssign( DbmConfigHandle , RadioButton , UT_PIN );
#define UTL_AddDbmConfigPinAssign _UTL_AddDbmConfigPinAssign
extern PinCursor _UTL_GetDbmConfigPinAssign( DbmConfigHandle , RadioButton );
#define UTL_GetDbmConfigPinAssign _UTL_GetDbmConfigPinAssign
extern void _UTL_ClearDbmConfigPinAssign( DbmConfigHandle );
#define UTL_ClearDbmConfigPinAssign _UTL_ClearDbmConfigPinAssign
extern void _UTL_SendDbmConfig( DbmConfigHandle );
#define UTL_SendDbmConfig _UTL_SendDbmConfig
extern void _UTL_UpdateDbmConfig( DbmConfigHandle );
#define UTL_UpdateDbmConfig _UTL_UpdateDbmConfig
extern DbmFileHandle _UTL_GetDbmFileHandle(void);
#define UTL_GetDbmFileHandle _UTL_GetDbmFileHandle
extern void _UTL_SetDbmFileMpatName(DbmFileHandle, char *);
#define UTL_SetDbmFileMpatName _UTL_SetDbmFileMpatName
extern void _UTL_SetDbmFileStartPc(DbmFileHandle, USlider);
#define UTL_SetDbmFileStartPc _UTL_SetDbmFileStartPc
extern void _UTL_SendDbmFile(DbmFileHandle);
#define UTL_SendDbmFile _UTL_SendDbmFile
extern void _UTL_SetDbmFileResetMode(DbmFileHandle, RadioButton);
#define UTL_SetDbmFileResetMode _UTL_SetDbmFileResetMode
extern void _UTL_ResetDbmFile(DbmFileHandle);
#define UTL_ResetDbmFile _UTL_ResetDbmFile
extern DbmAccessHandle _UTL_GetDbmAccessHandle(void);
#define UTL_GetDbmAccessHandle _UTL_GetDbmAccessHandle
extern void _UTL_SetDbmAccessUnitNumber(DbmAccessHandle, RadioButton);
#define UTL_SetDbmAccessUnitNumber _UTL_SetDbmAccessUnitNumber
extern void _UTL_SetDbmAccessAllUnit(DbmAccessHandle, CheckButton);
#define UTL_SetDbmAccessAllUnit _UTL_SetDbmAccessAllUnit
extern void _UTL_SetDbmAccessChildFlag(DbmAccessHandle, USlider);
#define UTL_SetDbmAccessChildFlag _UTL_SetDbmAccessChildFlag
extern void _UTL_SetDbmAccessDataKind(DbmAccessHandle, RadioButton);
#define UTL_SetDbmAccessDataKind _UTL_SetDbmAccessDataKind
extern void _UTL_SetDbmAccessBlockNumber(DbmAccessHandle, RadioButton);
#define UTL_SetDbmAccessBlockNumber _UTL_SetDbmAccessBlockNumber
extern void _UTL_SetDbmAccessAllBlock(DbmAccessHandle, CheckButton);
#define UTL_SetDbmAccessAllBlock _UTL_SetDbmAccessAllBlock
extern void _UTL_SetDbmAccessStartAddr(DbmAccessHandle, USlider);
#define UTL_SetDbmAccessStartAddr _UTL_SetDbmAccessStartAddr
extern void _UTL_SetDbmAccessStopAddr(DbmAccessHandle, USlider);
#define UTL_SetDbmAccessStopAddr _UTL_SetDbmAccessStopAddr
extern void _UTL_WriteDbm(DbmAccessHandle, void *, USlider);
#define UTL_WriteDbm _UTL_WriteDbm
extern void _UTL_ReadDbm(DbmAccessHandle, void *, USlider);
#define UTL_ReadDbm _UTL_ReadDbm
extern void _UTL_ResetDbm(DbmAccessHandle);
#define UTL_ResetDbm _UTL_ResetDbm
DbmPatCtrlHandle _UTL_GetDbmPatCtrlHandle (void);
#define UTL_GetDbmPatCtrlHandle _UTL_GetDbmPatCtrlHandle
extern void _UTL_SetDbmPatCtrlMode (DbmPatCtrlHandle , RadioButton);
#define UTL_SetDbmPatCtrlMode _UTL_SetDbmPatCtrlMode
extern int _UTL_GetDbmPatCtrlMode (DbmPatCtrlHandle hid, RadioButton *);
#define UTL_GetDbmPatCtrlMode _UTL_GetDbmPatCtrlMode
extern void _UTL_SetDbmPatCtrlDbmFix (DbmPatCtrlHandle, RadioButton, CheckButton);
#define UTL_SetDbmPatCtrlDbmFix _UTL_SetDbmPatCtrlDbmFix
extern int _UTL_GetDbmPatCtrlDbmFix (DbmPatCtrlHandle, RadioButton, CheckButton *);
#define UTL_GetDbmPatCtrlDbmFix _UTL_GetDbmPatCtrlDbmFix
extern void _UTL_SendDbmPatCtrl (DbmPatCtrlHandle);
#define UTL_SendDbmPatCtrl _UTL_SendDbmPatCtrl
extern void _UTL_UpdateDbmPatCtrl (DbmPatCtrlHandle);
#define UTL_UpdateDbmPatCtrl _UTL_UpdateDbmPatCtrl
extern CbmFileHandle _UTL_GetCbmFileHandle(void);
#define UTL_GetCbmFileHandle _UTL_GetCbmFileHandle
extern void _UTL_SetCbmFileMpatName(CbmFileHandle, char *);
#define UTL_SetCbmFileMpatName _UTL_SetCbmFileMpatName
extern void _UTL_SetCbmFileStartPc(CbmFileHandle, USlider);
#define UTL_SetCbmFileStartPc _UTL_SetCbmFileStartPc
extern void _UTL_SendCbmFile(CbmFileHandle);
#define UTL_SendCbmFile _UTL_SendCbmFile
extern void _UTL_SetCbmFileResetMode(CbmFileHandle, RadioButton);
#define UTL_SetCbmFileResetMode _UTL_SetCbmFileResetMode
extern void _UTL_ResetCbmFile(CbmFileHandle);
#define UTL_ResetCbmFile _UTL_ResetCbmFile
extern CbmAccessHandle _UTL_GetCbmAccessHandle(void);
#define UTL_GetCbmAccessHandle _UTL_GetCbmAccessHandle
extern void _UTL_SetCbmAccessUnitNumber(CbmAccessHandle, RadioButton);
#define UTL_SetCbmAccessUnitNumber _UTL_SetCbmAccessUnitNumber
extern void _UTL_SetCbmAccessAllUnit(CbmAccessHandle, CheckButton);
#define UTL_SetCbmAccessAllUnit _UTL_SetCbmAccessAllUnit
extern void _UTL_SetCbmAccessDataKind(CbmAccessHandle, RadioButton);
#define UTL_SetCbmAccessDataKind _UTL_SetCbmAccessDataKind
extern void _UTL_SetCbmAccessStartAddr(CbmAccessHandle, USlider);
#define UTL_SetCbmAccessStartAddr _UTL_SetCbmAccessStartAddr
extern void _UTL_SetCbmAccessStopAddr(CbmAccessHandle, USlider);
#define UTL_SetCbmAccessStopAddr _UTL_SetCbmAccessStopAddr
extern void _UTL_WriteCbm(CbmAccessHandle, void *, USlider);
#define UTL_WriteCbm _UTL_WriteCbm
extern void _UTL_ReadCbm(CbmAccessHandle, void *, USlider);
#define UTL_ReadCbm _UTL_ReadCbm
extern void _UTL_ResetCbm(CbmAccessHandle);
#define UTL_ResetCbm _UTL_ResetCbm
extern VpatFileHandle _UTL_GetVpatFileHandle(void);
#define UTL_GetVpatFileHandle _UTL_GetVpatFileHandle
extern void _UTL_SetVpatFileName(VpatFileHandle, char *);
#define UTL_SetVpatFileName _UTL_SetVpatFileName
extern void _UTL_SendVpatFile(VpatFileHandle);
#define UTL_SendVpatFile _UTL_SendVpatFile
extern void _UTL_SetVpatFileResetMode(VpatFileHandle, RadioButton);
#define UTL_SetVpatFileResetMode _UTL_SetVpatFileResetMode
extern void _UTL_ResetVpatFile(VpatFileHandle);
#define UTL_ResetVpatFile _UTL_ResetVpatFile
extern PdsMemorySelHandle _UTL_GetPdsMemorySelHandle( void );
#define UTL_GetPdsMemorySelHandle _UTL_GetPdsMemorySelHandle
extern void _UTL_SetPdsMemorySelPin( PdsMemorySelHandle, UT_PIN );
#define UTL_SetPdsMemorySelPin _UTL_SetPdsMemorySelPin
extern void _UTL_SetPdsMemorySelPinList( PdsMemorySelHandle, char * );
#define UTL_SetPdsMemorySelPinList _UTL_SetPdsMemorySelPinList
extern void _UTL_SetPdsMemorySelDataMux( PdsMemorySelHandle, RadioButton, RadioButton );
#define UTL_SetPdsMemorySelDataMux _UTL_SetPdsMemorySelDataMux
extern void _UTL_AddPdsMemorySelDut( PdsMemorySelHandle, UT_DUT );
#define UTL_AddPdsMemorySelDut _UTL_AddPdsMemorySelDut
extern void _UTL_ClearPdsMemorySelDut( PdsMemorySelHandle );
#define UTL_ClearPdsMemorySelDut _UTL_ClearPdsMemorySelDut
extern void _UTL_SendPdsMemorySel( PdsMemorySelHandle );
#define UTL_SendPdsMemorySel _UTL_SendPdsMemorySel
extern PdsMemoryHandle _UTL_GetPdsMemoryHandle( void );
#define UTL_GetPdsMemoryHandle _UTL_GetPdsMemoryHandle
extern void _UTL_SetPdsMemoryIncPat( PdsMemoryHandle, RadioButton );
#define UTL_SetPdsMemoryIncPat _UTL_SetPdsMemoryIncPat
extern void _UTL_SetPdsMemoryClearPat( PdsMemoryHandle, RadioButton );
#define UTL_SetPdsMemoryClearPat _UTL_SetPdsMemoryClearPat
extern void _UTL_SetPdsMemoryJumpPat( PdsMemoryHandle, RadioButton );
#define UTL_SetPdsMemoryJumpPat _UTL_SetPdsMemoryJumpPat
extern void _UTL_SetPdsMemoryJumpAddr( PdsMemoryHandle, USlider );
#define UTL_SetPdsMemoryJumpAddr _UTL_SetPdsMemoryJumpAddr
extern void _UTL_SetPdsMemoryPat( PdsMemoryHandle, USlider, RadioButton, RadioButton );
#define UTL_SetPdsMemoryPat _UTL_SetPdsMemoryPat
extern void _UTL_SetPdsMemoryDataRate( PdsMemoryHandle, USlider );
#define UTL_SetPdsMemoryDataRate _UTL_SetPdsMemoryDataRate
extern void _UTL_SendPdsMemory( PdsMemoryHandle );
#define UTL_SendPdsMemory _UTL_SendPdsMemory
void _UTL_InvokeTool(CheckButton,char *,int,char **);
#define UTL_InvokeTool _UTL_InvokeTool
extern BurstHandle _UTL_GetBurstHandle(void);
#define UTL_GetBurstHandle _UTL_GetBurstHandle
extern void _UTL_SetBurstBlock(BurstHandle, void (*)(void));
#define UTL_SetBurstBlock _UTL_SetBurstBlock
extern void _UTL_SetBurstBlockName(BurstHandle, char *);
#define UTL_SetBurstBlockName _UTL_SetBurstBlockName
extern void _UTL_SendBurstData(BurstHandle, RadioButton);
#define UTL_SendBurstData _UTL_SendBurstData
extern void _UTL_BurstPin(PinHandle, char *);
#define UTL_BurstPin _UTL_BurstPin
extern void _UTL_BurstDc( DcHandle , RadioButton );
#define UTL_BurstDc _UTL_BurstDc
extern void _UTL_BurstVs( VsHandle , RadioButton );
#define UTL_BurstVs _UTL_BurstVs
extern void _UTL_BurstVi ( ViHandle , RadioButton );
#define UTL_BurstVi _UTL_BurstVi
extern void _UTL_BurstVo ( VoHandle , RadioButton );
#define UTL_BurstVo _UTL_BurstVo
extern void _UTL_BurstIl ( IlHandle , RadioButton );
#define UTL_BurstIl _UTL_BurstIl
extern void _UTL_BurstVt ( VtHandle , RadioButton );
#define UTL_BurstVt _UTL_BurstVt
extern void _UTL_BurstDclp ( DclpHandle , RadioButton );
#define UTL_BurstDclp _UTL_BurstDclp
extern void _UTL_BurstOnPowerCtrl(PowerCtrlHandle);
#define UTL_BurstOnPowerCtrl _UTL_BurstOnPowerCtrl
extern void _UTL_BurstOffPowerCtrl(PowerCtrlHandle);
#define UTL_BurstOffPowerCtrl _UTL_BurstOffPowerCtrl
extern void _UTL_BurstWaitTime(DSlider);
#define UTL_BurstWaitTime _UTL_BurstWaitTime
extern void _UTL_BurstDefineVariable(char *, USlider);
#define UTL_BurstDefineVariable _UTL_BurstDefineVariable
extern void _UTL_BurstDefineArray(char *, USlider, CheckButton, USlider);
#define UTL_BurstDefineArray _UTL_BurstDefineArray
extern void _UTL_BurstArrayLoad(char *, char *, char *);
#define UTL_BurstArrayLoad _UTL_BurstArrayLoad
extern void _UTL_BurstArrayMov(char *, char *, char *);
#define UTL_BurstArrayMov _UTL_BurstArrayMov
extern USlider _UTL_ReadBurstArray(char *, USlider);
#define UTL_ReadBurstArray _UTL_ReadBurstArray
extern void _UTL_ReadBurstArrayAll(char *, USlider *, USlider);
#define UTL_ReadBurstArrayAll _UTL_ReadBurstArrayAll
extern void _UTL_BurstLoad_I(char *, USlider);
#define UTL_BurstLoad_I _UTL_BurstLoad_I
extern void _UTL_BurstInc(char *);
#define UTL_BurstInc _UTL_BurstInc
extern void _UTL_BurstDec(char *);
#define UTL_BurstDec _UTL_BurstDec
extern void _UTL_BurstInv(char *);
#define UTL_BurstInv _UTL_BurstInv
extern void _UTL_BurstSr(char *);
#define UTL_BurstSr _UTL_BurstSr
extern void _UTL_BurstSl(char *);
#define UTL_BurstSl _UTL_BurstSl
extern void _UTL_BurstAdd_I(char *, USlider);
#define UTL_BurstAdd_I _UTL_BurstAdd_I
extern void _UTL_BurstSub_I(char *, USlider);
#define UTL_BurstSub_I _UTL_BurstSub_I
extern void _UTL_BurstAnd_I(char *, USlider);
#define UTL_BurstAnd_I _UTL_BurstAnd_I
extern void _UTL_BurstOr_I(char *, USlider);
#define UTL_BurstOr_I _UTL_BurstOr_I
extern void _UTL_BurstXor_I(char *, USlider);
#define UTL_BurstXor_I _UTL_BurstXor_I
extern void _UTL_BurstAdd_V(char *, char *);
#define UTL_BurstAdd_V _UTL_BurstAdd_V
extern void _UTL_BurstSub_V(char *, char *);
#define UTL_BurstSub_V _UTL_BurstSub_V
extern void _UTL_BurstAnd_V(char *, char *);
#define UTL_BurstAnd_V _UTL_BurstAnd_V
extern void _UTL_BurstOr_V(char *, char *);
#define UTL_BurstOr_V _UTL_BurstOr_V
extern void _UTL_BurstXor_V(char *, char *);
#define UTL_BurstXor_V _UTL_BurstXor_V
extern void _UTL_BurstMov(char *, char *);
#define UTL_BurstMov _UTL_BurstMov
extern void _UTL_BurstLabel(char *);
#define UTL_BurstLabel _UTL_BurstLabel
extern void _UTL_BurstGoto(char *);
#define UTL_BurstGoto _UTL_BurstGoto
extern void _UTL_BurstIf_I(char *, RadioButton, USlider, char *);
#define UTL_BurstIf_I _UTL_BurstIf_I
extern void _UTL_BurstIf_V(char *, RadioButton, char *, char *);
#define UTL_BurstIf_V _UTL_BurstIf_V
extern void _UTL_BurstRegBar1(USlider);
#define UTL_BurstRegBar1 _UTL_BurstRegBar1
extern void _UTL_BurstRegJar(USlider);
#define UTL_BurstRegJar _UTL_BurstRegJar
extern void _UTL_BurstFailCounterCondition(FailCounterHandle);
#define UTL_BurstFailCounterCondition _UTL_BurstFailCounterCondition
extern void _UTL_BurstReadFailCounter(UT_DUT, char *);
#define UTL_BurstReadFailCounter _UTL_BurstReadFailCounter
extern void _UTL_BurstReadFailCounterMaxFail(UT_DUT, char *);
#define UTL_BurstReadFailCounterMaxFail _UTL_BurstReadFailCounterMaxFail
extern void _UTL_BurstFlash(FlashHandle);
#define UTL_BurstFlash _UTL_BurstFlash
extern void _UTL_BurstReadFlashHold(UT_DUT, UT_PIN, char *);
#define UTL_BurstReadFlashHold _UTL_BurstReadFlashHold
extern void _UTL_BurstReadFlashCounter(UT_DUT, char *);
#define UTL_BurstReadFlashCounter _UTL_BurstReadFlashCounter
extern void _UTL_BurstReadFlashMaxFail(UT_DUT, char *);
#define UTL_BurstReadFlashMaxFail _UTL_BurstReadFlashMaxFail
extern void _UTL_SetAuxDutSignalBurstVariableName( AuxDutSignalHandle, char * );
#define UTL_SetAuxDutSignalBurstVariableName _UTL_SetAuxDutSignalBurstVariableName
extern void _UTL_BurstAuxDutSignal ( AuxDutSignalHandle, RadioButton, RadioButton );
#define UTL_BurstAuxDutSignal _UTL_BurstAuxDutSignal
extern void _UTL_BurstReadAuxDutSignal( AuxDutSignalHandle, RadioButton, RadioButton );
#define UTL_BurstReadAuxDutSignal _UTL_BurstReadAuxDutSignal
extern USlider _UTL_ReadBurstVariable(char *);
#define UTL_ReadBurstVariable _UTL_ReadBurstVariable
extern void _UTL_BurstClearAll(void);
#define UTL_BurstClearAll _UTL_BurstClearAll
extern void _UTL_ExecCalb( char *, char * );
#define UTL_ExecCalb _UTL_ExecCalb
extern void _UTL_ExecSbcal( char *, char * );
#define UTL_ExecSbcal _UTL_ExecSbcal
extern RadioButton _UTL_CheckPartTestMode(RadioButton);
#define UTL_CheckPartTestMode _UTL_CheckPartTestMode
extern CheckButton _UTL_CheckAlarmOccurrence(RadioButton);
#define UTL_CheckAlarmOccurrence _UTL_CheckAlarmOccurrence
extern RadioButton _UTL_ReadTestMode(void);
#define UTL_ReadTestMode _UTL_ReadTestMode
extern char *_UTL_ReadStartTestName(void);
#define UTL_ReadStartTestName _UTL_ReadStartTestName
extern CheckButton _UTL_ReadDataLogSwitchCondition(RadioButton);
#define UTL_ReadDataLogSwitchCondition _UTL_ReadDataLogSwitchCondition
extern CheckButton _UTL_ReadTestModeOptionsSwitchCondition(RadioButton);
#define UTL_ReadTestModeOptionsSwitchCondition _UTL_ReadTestModeOptionsSwitchCondition
extern void _UTL_InitResult(void);
#define UTL_InitResult _UTL_InitResult
extern RadioButton _UTL_SaveResult(RadioButton);
#define UTL_SaveResult _UTL_SaveResult
extern RadioButton _UTL_CheckRepeatPause(void);
#define UTL_CheckRepeatPause _UTL_CheckRepeatPause
extern void _UTL_ResetDctAllPin ( RadioButton );
#define UTL_ResetDctAllPin _UTL_ResetDctAllPin
extern DctCtrlRelayHandle _UTL_GetDctCtrlRelayHandle( void );
#define UTL_GetDctCtrlRelayHandle _UTL_GetDctCtrlRelayHandle
extern void _UTL_InitializeDctCtrlRelayHandle( DctCtrlRelayHandle );
#define UTL_InitializeDctCtrlRelayHandle _UTL_InitializeDctCtrlRelayHandle
extern void _UTL_SetDctCtrlRelayVi( DctCtrlRelayHandle , CheckButton );
#define UTL_SetDctCtrlRelayVi _UTL_SetDctCtrlRelayVi
extern void _UTL_SetDctCtrlRelayVo( DctCtrlRelayHandle , CheckButton );
#define UTL_SetDctCtrlRelayVo _UTL_SetDctCtrlRelayVo
extern void _UTL_SetDctCtrlRelayVihh( DctCtrlRelayHandle , CheckButton );
#define UTL_SetDctCtrlRelayVihh _UTL_SetDctCtrlRelayVihh
extern void _UTL_SetDctCtrlRelayHvDr( DctCtrlRelayHandle , CheckButton );
#define UTL_SetDctCtrlRelayHvDr _UTL_SetDctCtrlRelayHvDr
extern void _UTL_SetDctCtrlRelayTerm( DctCtrlRelayHandle , CheckButton );
#define UTL_SetDctCtrlRelayTerm _UTL_SetDctCtrlRelayTerm
extern void _UTL_SetDctCtrlRelayPl( DctCtrlRelayHandle , RadioButton );
#define UTL_SetDctCtrlRelayPl _UTL_SetDctCtrlRelayPl
extern void _UTL_SetDctCtrlRelayDc( DctCtrlRelayHandle , CheckButton );
#define UTL_SetDctCtrlRelayDc _UTL_SetDctCtrlRelayDc
extern void _UTL_SetDctCtrlRelayDutCtrl( DctCtrlRelayHandle , RadioButton , RadioButton );
#define UTL_SetDctCtrlRelayDutCtrl _UTL_SetDctCtrlRelayDutCtrl
extern void _UTL_SetDctCtrlRelayWaitTime( DctCtrlRelayHandle , DSlider );
#define UTL_SetDctCtrlRelayWaitTime _UTL_SetDctCtrlRelayWaitTime
extern void _UTL_SendDctCtrlRelay( DctCtrlRelayHandle , UT_PIN );
#define UTL_SendDctCtrlRelay _UTL_SendDctCtrlRelay
extern DSlider _UTL_ReadDctCtrlRelayActionTime( UT_PIN , RadioButton );
#define UTL_ReadDctCtrlRelayActionTime _UTL_ReadDctCtrlRelayActionTime
extern DSlider _UTL_ReadDctWaitTime( RadioButton , UT_PIN , RadioButton );
#define UTL_ReadDctWaitTime _UTL_ReadDctWaitTime
extern DutCursor _UTL_GetDctDutGroupCursor( UT_PIN , RadioButton );
#define UTL_GetDctDutGroupCursor _UTL_GetDctDutGroupCursor
extern RadioButton _UTL_GetDctDutGroupMaxNumber( UT_PIN );
#define UTL_GetDctDutGroupMaxNumber _UTL_GetDctDutGroupMaxNumber
extern StartAdcHandle _UTL_GetStartAdcHandle( void );
#define UTL_GetStartAdcHandle _UTL_GetStartAdcHandle
extern void _UTL_SetStartAdcPinType( StartAdcHandle , RadioButton );
#define UTL_SetStartAdcPinType _UTL_SetStartAdcPinType
extern void _UTL_AddStartAdcPinNumber( StartAdcHandle , UT_PIN );
#define UTL_AddStartAdcPinNumber _UTL_AddStartAdcPinNumber
extern void _UTL_ClearStartAdcPinNumber( StartAdcHandle );
#define UTL_ClearStartAdcPinNumber _UTL_ClearStartAdcPinNumber
extern void _UTL_SetStartAdcTargetDctPin( StartAdcHandle , RadioButton );
#define UTL_SetStartAdcTargetDctPin _UTL_SetStartAdcTargetDctPin
extern void _UTL_SetStartAdcSettlingTime( StartAdcHandle , DSlider );
#define UTL_SetStartAdcSettlingTime _UTL_SetStartAdcSettlingTime
extern void _UTL_SendStartAdc( StartAdcHandle );
#define UTL_SendStartAdc _UTL_SendStartAdc
extern void _UTL_StartAdc( void );
#define UTL_StartAdc _UTL_StartAdc
extern void _UTL_SaveStartAdcDctPin( StartAdcHandle );
#define UTL_SaveStartAdcDctPin _UTL_SaveStartAdcDctPin
extern RadioButton _UTL_ReadStartAdcResult( RadioButton , UT_PIN , UT_DUT );
#define UTL_ReadStartAdcResult _UTL_ReadStartAdcResult
extern DSlider _UTL_ReadStartAdcMeasData( RadioButton , UT_PIN , UT_DUT , CheckButton * );
#define UTL_ReadStartAdcMeasData _UTL_ReadStartAdcMeasData
extern void _UTL_PrintDctDataLog( RadioButton , RadioButton , UT_PIN , UT_DUT );
#define UTL_PrintDctDataLog _UTL_PrintDctDataLog
extern PinCursor _UTL_GetDctPinGroupCursor( char * , RadioButton );
#define UTL_GetDctPinGroupCursor _UTL_GetDctPinGroupCursor
extern RadioButton _UTL_GetDctPinGroupMaxNumber( char * );
#define UTL_GetDctPinGroupMaxNumber _UTL_GetDctPinGroupMaxNumber
extern DctVsCtrlRelayHandle _UTL_GetDctVsCtrlRelayHandle( void );
#define UTL_GetDctVsCtrlRelayHandle _UTL_GetDctVsCtrlRelayHandle
extern void _UTL_InitializeDctVsCtrlRelayHandle( DctVsCtrlRelayHandle );
#define UTL_InitializeDctVsCtrlRelayHandle _UTL_InitializeDctVsCtrlRelayHandle
extern void _UTL_SetDctVsCtrlRelayDutCtrl( DctVsCtrlRelayHandle , RadioButton , RadioButton );
#define UTL_SetDctVsCtrlRelayDutCtrl _UTL_SetDctVsCtrlRelayDutCtrl
extern void _UTL_SetDctVsCtrlRelayWaitTime( DctVsCtrlRelayHandle , DSlider );
#define UTL_SetDctVsCtrlRelayWaitTime _UTL_SetDctVsCtrlRelayWaitTime
extern void _UTL_SendDctVsCtrlRelay( DctVsCtrlRelayHandle , RadioButton );
#define UTL_SendDctVsCtrlRelay _UTL_SendDctVsCtrlRelay
extern DSlider _UTL_ReadDctVsCtrlRelayActionTime( RadioButton , RadioButton );
#define UTL_ReadDctVsCtrlRelayActionTime _UTL_ReadDctVsCtrlRelayActionTime
extern DutCursor _UTL_GetDctVsDutGroupCursor( RadioButton , RadioButton );
#define UTL_GetDctVsDutGroupCursor _UTL_GetDctVsDutGroupCursor
extern RadioButton _UTL_GetDctVsDutGroupMaxNumber( RadioButton );
#define UTL_GetDctVsDutGroupMaxNumber _UTL_GetDctVsDutGroupMaxNumber
extern RadioButton _UTL_ReadAlpgStatus(void);
#define UTL_ReadAlpgStatus _UTL_ReadAlpgStatus
extern RadioButton _UTL_ReadAlpgStatusFlag(void);
#define UTL_ReadAlpgStatusFlag _UTL_ReadAlpgStatusFlag
extern CheckButton _UTL_CheckAlpgStatusFlag(RadioButton);
#define UTL_CheckAlpgStatusFlag _UTL_CheckAlpgStatusFlag
extern void _UTL_ResetFctAllPin( void );
#define UTL_ResetFctAllPin _UTL_ResetFctAllPin
extern MpatHandle _UTL_GetMpatHandle (void);
#define UTL_GetMpatHandle _UTL_GetMpatHandle
extern void _UTL_SetMpatStartPc (MpatHandle, USlider);
#define UTL_SetMpatStartPc _UTL_SetMpatStartPc
extern void _UTL_SetMpatFileName (MpatHandle, char *);
#define UTL_SetMpatFileName _UTL_SetMpatFileName
extern void _UTL_SendMpat (MpatHandle);
#define UTL_SendMpat _UTL_SendMpat
extern TrigHandle _UTL_GetTrigHandle(void);
#define UTL_GetTrigHandle _UTL_GetTrigHandle
extern void _UTL_InitializeTrigHandle(TrigHandle);
#define UTL_InitializeTrigHandle _UTL_InitializeTrigHandle
extern void _UTL_SetTrigOutputCtrl(TrigHandle, CheckButton);
#define UTL_SetTrigOutputCtrl _UTL_SetTrigOutputCtrl
extern void _UTL_SetTrigStateMode(TrigHandle, RadioButton, CheckButton);
#define UTL_SetTrigStateMode _UTL_SetTrigStateMode
extern void _UTL_SetTrigStateValue(TrigHandle, RadioButton, RadioButton, USlider);
#define UTL_SetTrigStateValue _UTL_SetTrigStateValue
extern void _UTL_SetTrigStrbPhase(TrigHandle, RadioButton);
#define UTL_SetTrigStrbPhase _UTL_SetTrigStrbPhase
extern void _UTL_SetTrigAlpgUnit (TrigHandle, RadioButton);
#define UTL_SetTrigAlpgUnit _UTL_SetTrigAlpgUnit
extern void _UTL_SetTrigMode(TrigHandle, RadioButton, CheckButton);
#define UTL_SetTrigMode _UTL_SetTrigMode
extern void _UTL_AddTrigFailDut(TrigHandle, UT_DUT, CheckButton);
#define UTL_AddTrigFailDut _UTL_AddTrigFailDut
extern void _UTL_SetTrigDirection(TrigHandle, RadioButton);
#define UTL_SetTrigDirection _UTL_SetTrigDirection
extern void _UTL_SendTrig(TrigHandle);
#define UTL_SendTrig _UTL_SendTrig
extern void _UTL_ClearTrig(void);
#define UTL_ClearTrig _UTL_ClearTrig
extern AlpgCtrlHandle _UTL_GetAlpgCtrlHandle(void);
#define UTL_GetAlpgCtrlHandle _UTL_GetAlpgCtrlHandle
extern void _UTL_AddAlpgCtrlMode(AlpgCtrlHandle, RadioButton, CheckButton);
#define UTL_AddAlpgCtrlMode _UTL_AddAlpgCtrlMode
extern void _UTL_ClearAlpgCtrlMode(AlpgCtrlHandle);
#define UTL_ClearAlpgCtrlMode _UTL_ClearAlpgCtrlMode
extern void _UTL_SendAlpgCtrlMode(AlpgCtrlHandle);
#define UTL_SendAlpgCtrlMode _UTL_SendAlpgCtrlMode
extern void _UTL_StartAlpg (RadioButton);
#define UTL_StartAlpg _UTL_StartAlpg
extern void _UTL_StopAlpg (void);
#define UTL_StopAlpg _UTL_StopAlpg
extern void _UTL_SendFctDataLogCondition(void);
#define UTL_SendFctDataLogCondition _UTL_SendFctDataLogCondition
extern void _UTL_PrintFctDataLog(void);
#define UTL_PrintFctDataLog _UTL_PrintFctDataLog
extern TmeasHandle _UTL_GetTmeasHandle(void);
#define UTL_GetTmeasHandle _UTL_GetTmeasHandle
extern void _UTL_SetTmeasRange(TmeasHandle,DSlider,DSlider);
#define UTL_SetTmeasRange _UTL_SetTmeasRange
extern void _UTL_SetTmeasResolution(TmeasHandle,DSlider);
#define UTL_SetTmeasResolution _UTL_SetTmeasResolution
extern void _UTL_SetTmeasUnit(TmeasHandle,RadioButton,RadioButton,RadioButton,RadioButton);
#define UTL_SetTmeasUnit _UTL_SetTmeasUnit
extern void _UTL_SetTmeasMpatName(TmeasHandle,char *);
#define UTL_SetTmeasMpatName _UTL_SetTmeasMpatName
extern void _UTL_SetTmeasStartPc(TmeasHandle,USlider);
#define UTL_SetTmeasStartPc _UTL_SetTmeasStartPc
extern void _UTL_AddTmeasDut(TmeasHandle,UT_DUT);
#define UTL_AddTmeasDut _UTL_AddTmeasDut
extern void _UTL_ClearTmeasDut(TmeasHandle);
#define UTL_ClearTmeasDut _UTL_ClearTmeasDut
extern void _UTL_AddTmeasTrackingUnit(TmeasHandle,RadioButton,RadioButton,RadioButton,RadioButton,DSlider);
#define UTL_AddTmeasTrackingUnit _UTL_AddTmeasTrackingUnit
extern void _UTL_ClearTmeasTrackingUnit(TmeasHandle);
#define UTL_ClearTmeasTrackingUnit _UTL_ClearTmeasTrackingUnit
extern int _UTL_Tmeas(TmeasHandle);
#define UTL_Tmeas _UTL_Tmeas
extern int _UTL_GetTmeasResult(TmeasHandle,UT_DUT,DSlider *);
#define UTL_GetTmeasResult _UTL_GetTmeasResult
extern VmeasHandle _UTL_GetVmeasHandle(void);
#define UTL_GetVmeasHandle _UTL_GetVmeasHandle
extern void _UTL_SetVmeasRange(VmeasHandle,DSlider,DSlider);
#define UTL_SetVmeasRange _UTL_SetVmeasRange
extern void _UTL_SetVmeasResolution(VmeasHandle,DSlider);
#define UTL_SetVmeasResolution _UTL_SetVmeasResolution
extern void _UTL_SetVmeasUnit(VmeasHandle,RadioButton,RadioButton);
#define UTL_SetVmeasUnit _UTL_SetVmeasUnit
extern void _UTL_SetVmeasMpatName(VmeasHandle,char *);
#define UTL_SetVmeasMpatName _UTL_SetVmeasMpatName
extern void _UTL_SetVmeasStartPc(VmeasHandle,USlider);
#define UTL_SetVmeasStartPc _UTL_SetVmeasStartPc
extern void _UTL_SetVmeasWaitTime(VmeasHandle,DSlider);
#define UTL_SetVmeasWaitTime _UTL_SetVmeasWaitTime
extern void _UTL_SetVmeasWaitInhibit(VmeasHandle,CheckButton);
#define UTL_SetVmeasWaitInhibit _UTL_SetVmeasWaitInhibit
extern void _UTL_AddVmeasDut(VmeasHandle,UT_DUT);
#define UTL_AddVmeasDut _UTL_AddVmeasDut
extern void _UTL_ClearVmeasDut(VmeasHandle);
#define UTL_ClearVmeasDut _UTL_ClearVmeasDut
extern void _UTL_AddVmeasTrackingUnit(VmeasHandle,RadioButton,RadioButton,DSlider);
#define UTL_AddVmeasTrackingUnit _UTL_AddVmeasTrackingUnit
extern void _UTL_ClearVmeasTrackingUnit(VmeasHandle);
#define UTL_ClearVmeasTrackingUnit _UTL_ClearVmeasTrackingUnit
extern int _UTL_Vmeas(VmeasHandle);
#define UTL_Vmeas _UTL_Vmeas
extern int _UTL_GetVmeasResult(VmeasHandle,UT_DUT,DSlider *);
#define UTL_GetVmeasResult _UTL_GetVmeasResult
 extern HidarConfigHandle _UTL_GetHidarConfigHandle ( void );
#define UTL_GetHidarConfigHandle _UTL_GetHidarConfigHandle
 extern void _UTL_SetHidarConfigProgramName(HidarConfigHandle hch,char *program_name);
#define UTL_SetHidarConfigProgramName _UTL_SetHidarConfigProgramName
 extern void _UTL_SetHidarConfigType(HidarConfigHandle hch,RadioButton hidar_type);
#define UTL_SetHidarConfigType _UTL_SetHidarConfigType
 extern void _UTL_SetHidarConfigItem(HidarConfigHandle hch,char *item);
#define UTL_SetHidarConfigItem _UTL_SetHidarConfigItem
 extern void _UTL_SetHidarConfigStartTestNumber(HidarConfigHandle hch,Slider start_test_num);
#define UTL_SetHidarConfigStartTestNumber _UTL_SetHidarConfigStartTestNumber
 extern void _UTL_SetHidarConfigStopTestNumber(HidarConfigHandle hch,Slider stop_test_num);
#define UTL_SetHidarConfigStopTestNumber _UTL_SetHidarConfigStopTestNumber
 extern void _UTL_AddHidarConfigTestName(HidarConfigHandle hch,char *test_name);
#define UTL_AddHidarConfigTestName _UTL_AddHidarConfigTestName
 extern void _UTL_ClearHidarConfigTestName(HidarConfigHandle hch);
#define UTL_ClearHidarConfigTestName _UTL_ClearHidarConfigTestName
 extern void _UTL_SetHidarConfigTestNamePattern(HidarConfigHandle hch,char *test_name_pattern);
#define UTL_SetHidarConfigTestNamePattern _UTL_SetHidarConfigTestNamePattern
 extern void _UTL_SetHidarConfigRangeMode(HidarConfigHandle hch,RadioButton range_mode);
#define UTL_SetHidarConfigRangeMode _UTL_SetHidarConfigRangeMode
 extern void _UTL_SetHidarConfigCellNumber(HidarConfigHandle hch,Slider cell_number);
#define UTL_SetHidarConfigCellNumber _UTL_SetHidarConfigCellNumber
 extern void _UTL_SetHidarConfigCellResolutionMin(HidarConfigHandle hch,DSlider resolution);
#define UTL_SetHidarConfigCellResolutionMin _UTL_SetHidarConfigCellResolutionMin
 extern void _UTL_SetHidarConfigCollectionRangeMax(HidarConfigHandle hch,DSlider collection_range_max);
#define UTL_SetHidarConfigCollectionRangeMax _UTL_SetHidarConfigCollectionRangeMax
 extern void _UTL_SetHidarConfigCollectionRangeMin(HidarConfigHandle hch,DSlider collection_range_min);
#define UTL_SetHidarConfigCollectionRangeMin _UTL_SetHidarConfigCollectionRangeMin
 extern void _UTL_SetHidarConfigStatisticRangeMax(HidarConfigHandle hch,DSlider statistic_range_max);
#define UTL_SetHidarConfigStatisticRangeMax _UTL_SetHidarConfigStatisticRangeMax
 extern void _UTL_SetHidarConfigStatisticRangeMin(HidarConfigHandle hch,DSlider statistic_range_min);
#define UTL_SetHidarConfigStatisticRangeMin _UTL_SetHidarConfigStatisticRangeMin
 extern int _UTL_GetHidarConfigProgramName(HidarConfigHandle hch,char **program_name);
#define UTL_GetHidarConfigProgramName _UTL_GetHidarConfigProgramName
 extern int _UTL_GetHidarConfigType(HidarConfigHandle hch,RadioButton *hidar_type);
#define UTL_GetHidarConfigType _UTL_GetHidarConfigType
 extern int _UTL_GetHidarConfigItem(HidarConfigHandle hch,char **item);
#define UTL_GetHidarConfigItem _UTL_GetHidarConfigItem
 extern int _UTL_GetHidarConfigStartTestNumber(HidarConfigHandle hch,Slider *start_test_num);
#define UTL_GetHidarConfigStartTestNumber _UTL_GetHidarConfigStartTestNumber
 extern int _UTL_GetHidarConfigStopTestNumber(HidarConfigHandle hch,Slider *stop_test_num);
#define UTL_GetHidarConfigStopTestNumber _UTL_GetHidarConfigStopTestNumber
 extern int _UTL_GetHidarConfigNumberOfTestNames(HidarConfigHandle hch,Slider *number_of_test_name);
#define UTL_GetHidarConfigNumberOfTestNames _UTL_GetHidarConfigNumberOfTestNames
 extern int _UTL_GetHidarConfigTestName(HidarConfigHandle hch,RadioButton n,char **test_name);
#define UTL_GetHidarConfigTestName _UTL_GetHidarConfigTestName
 extern int _UTL_GetHidarConfigTestNamePattern(HidarConfigHandle hch,char **test_name_pattern);
#define UTL_GetHidarConfigTestNamePattern _UTL_GetHidarConfigTestNamePattern
 extern int _UTL_GetHidarConfigRangeMode(HidarConfigHandle hch,RadioButton *range_mode);
#define UTL_GetHidarConfigRangeMode _UTL_GetHidarConfigRangeMode
 extern int _UTL_GetHidarConfigCellNumber(HidarConfigHandle hch,Slider *cell_number);
#define UTL_GetHidarConfigCellNumber _UTL_GetHidarConfigCellNumber
 extern int _UTL_GetHidarConfigCellResolutionMin(HidarConfigHandle hch,DSlider *resolution);
#define UTL_GetHidarConfigCellResolutionMin _UTL_GetHidarConfigCellResolutionMin
 extern int _UTL_GetHidarConfigCollectionRangeMax(HidarConfigHandle hch,DSlider *collection_range_max);
#define UTL_GetHidarConfigCollectionRangeMax _UTL_GetHidarConfigCollectionRangeMax
 extern int _UTL_GetHidarConfigCollectionRangeMin(HidarConfigHandle hch,DSlider *collection_range_min);
#define UTL_GetHidarConfigCollectionRangeMin _UTL_GetHidarConfigCollectionRangeMin
 extern int _UTL_GetHidarConfigStatisticRangeMax(HidarConfigHandle hch,DSlider *statistic_range_max);
#define UTL_GetHidarConfigStatisticRangeMax _UTL_GetHidarConfigStatisticRangeMax
 extern int _UTL_GetHidarConfigStatisticRangeMin(HidarConfigHandle hch,DSlider *statistic_range_min);
#define UTL_GetHidarConfigStatisticRangeMin _UTL_GetHidarConfigStatisticRangeMin
 extern HidarConfigListHandle _UTL_GetHidarConfigListHandle( RadioButton site );
#define UTL_GetHidarConfigListHandle _UTL_GetHidarConfigListHandle
 extern HidarConfigListHandle _UTL_GetHidarConfigListTargetStationHandle( RadioButton , RadioButton );
#define UTL_GetHidarConfigListTargetStationHandle _UTL_GetHidarConfigListTargetStationHandle
 extern void _UTL_AppendHidarConfigList( HidarConfigListHandle , HidarConfigHandle );
#define UTL_AppendHidarConfigList _UTL_AppendHidarConfigList
 extern int _UTL_GetHidarConfigListCount( HidarConfigListHandle , Slider * );
#define UTL_GetHidarConfigListCount _UTL_GetHidarConfigListCount
 extern int _UTL_GetHidarConfigListIndex( HidarConfigListHandle , RadioButton , HidarConfigHandle * );
#define UTL_GetHidarConfigListIndex _UTL_GetHidarConfigListIndex
 extern int _UTL_DeleteHidarConfigList( HidarConfigListHandle , RadioButton );
#define UTL_DeleteHidarConfigList _UTL_DeleteHidarConfigList
 extern HidarAccessHandle _UTL_GetHidarAccessHandle( void );
#define UTL_GetHidarAccessHandle _UTL_GetHidarAccessHandle
 extern void _UTL_SetHidarAccessStationNumber( HidarAccessHandle , RadioButton );
#define UTL_SetHidarAccessStationNumber _UTL_SetHidarAccessStationNumber
 extern void _UTL_SetHidarAccessSiteNumber( HidarAccessHandle hah, RadioButton siteno );
#define UTL_SetHidarAccessSiteNumber _UTL_SetHidarAccessSiteNumber
 extern void _UTL_AddHidarAccessTestName ( HidarAccessHandle hah, char *test_name );
#define UTL_AddHidarAccessTestName _UTL_AddHidarAccessTestName
 extern void _UTL_SetHidarAccessTestCount ( HidarAccessHandle hah, Slider testcount );
#define UTL_SetHidarAccessTestCount _UTL_SetHidarAccessTestCount
 extern void _UTL_SetHidarAccessErrTestCount ( HidarAccessHandle hah, Slider err_test_count );
#define UTL_SetHidarAccessErrTestCount _UTL_SetHidarAccessErrTestCount
 extern void _UTL_SetHidarAccessFailCountLow ( HidarAccessHandle hah, Slider low_fail_count );
#define UTL_SetHidarAccessFailCountLow _UTL_SetHidarAccessFailCountLow
 extern void _UTL_SetHidarAccessFailCountHigh ( HidarAccessHandle hah, Slider high_fail_count );
#define UTL_SetHidarAccessFailCountHigh _UTL_SetHidarAccessFailCountHigh
 extern void _UTL_SetHidarAccessOverCountLow ( HidarAccessHandle hah, Slider over_count_low );
#define UTL_SetHidarAccessOverCountLow _UTL_SetHidarAccessOverCountLow
 extern void _UTL_SetHidarAccessOverCountHigh ( HidarAccessHandle hah, Slider over_count_high );
#define UTL_SetHidarAccessOverCountHigh _UTL_SetHidarAccessOverCountHigh
 extern void _UTL_SetHidarAccessLimitLow ( HidarAccessHandle hah, DSlider limit_low, CheckButton ldo );
#define UTL_SetHidarAccessLimitLow _UTL_SetHidarAccessLimitLow
 extern void _UTL_SetHidarAccessLimitHigh ( HidarAccessHandle hah, DSlider limit_high, CheckButton hdo );
#define UTL_SetHidarAccessLimitHigh _UTL_SetHidarAccessLimitHigh
 extern void _UTL_SetHidarAccessDataMin ( HidarAccessHandle hah, DSlider data_min );
#define UTL_SetHidarAccessDataMin _UTL_SetHidarAccessDataMin
 extern void _UTL_SetHidarAccessDataMax ( HidarAccessHandle hah, DSlider data_max );
#define UTL_SetHidarAccessDataMax _UTL_SetHidarAccessDataMax
 extern void _UTL_SetHidarAccessAddVal( HidarAccessHandle hah, DSlider addval );
#define UTL_SetHidarAccessAddVal _UTL_SetHidarAccessAddVal
 extern void _UTL_SetHidarAccessSquareSum( HidarAccessHandle hah, DSlider square_sum );
#define UTL_SetHidarAccessSquareSum _UTL_SetHidarAccessSquareSum
 extern void _UTL_SetHidarAccessRankMin( HidarAccessHandle hah, DSlider rankmin );
#define UTL_SetHidarAccessRankMin _UTL_SetHidarAccessRankMin
 extern void _UTL_SetHidarAccessRankMax( HidarAccessHandle hah, DSlider rankmax );
#define UTL_SetHidarAccessRankMax _UTL_SetHidarAccessRankMax
 extern void _UTL_SetHidarAccessRankResolution ( HidarAccessHandle hah, DSlider rank_reso );
#define UTL_SetHidarAccessRankResolution _UTL_SetHidarAccessRankResolution
 extern void _UTL_SetHidarAccessRankPassCount ( HidarAccessHandle hah, RadioButton rankno, Slider rank_pass_count );
#define UTL_SetHidarAccessRankPassCount _UTL_SetHidarAccessRankPassCount
 extern void _UTL_SetHidarAccessRankFailCount ( HidarAccessHandle hah, RadioButton rankno, Slider rank_fail_count );
#define UTL_SetHidarAccessRankFailCount _UTL_SetHidarAccessRankFailCount
 extern void _UTL_AddHidarAccessOverData ( HidarAccessHandle hah, DSlider overdata , RadioButton result);
#define UTL_AddHidarAccessOverData _UTL_AddHidarAccessOverData
 extern void _UTL_SendHidarData ( HidarAccessHandle hah, HidarConfigHandle hch );
#define UTL_SendHidarData _UTL_SendHidarData
 extern void _UTL_ReconstructHidarData( HidarAccessHandle hah, HidarConfigHandle hch );
#define UTL_ReconstructHidarData _UTL_ReconstructHidarData
 extern HidarAccessHandle _UTL_MergeHidar( HidarConfigHandle hch, RadioButtonList list );
#define UTL_MergeHidar _UTL_MergeHidar
 extern void _UTL_UpdateHidarData ( HidarAccessHandle hah, HidarConfigHandle hch );
#define UTL_UpdateHidarData _UTL_UpdateHidarData
 extern int _UTL_GetHidarAccessTestNameCount( HidarAccessHandle hah, Slider *number_of_test_name );
#define UTL_GetHidarAccessTestNameCount _UTL_GetHidarAccessTestNameCount
 extern int _UTL_GetHidarAccessTestName ( HidarAccessHandle hah, RadioButton n, char **testname );
#define UTL_GetHidarAccessTestName _UTL_GetHidarAccessTestName
 extern int _UTL_GetHidarAccessTestCount ( HidarAccessHandle hah, Slider *testcount );
#define UTL_GetHidarAccessTestCount _UTL_GetHidarAccessTestCount
 extern int _UTL_GetHidarAccessErrTestCount ( HidarAccessHandle hah, Slider *err_test_count );
#define UTL_GetHidarAccessErrTestCount _UTL_GetHidarAccessErrTestCount
 extern int _UTL_GetHidarAccessFailCountLow ( HidarAccessHandle hah, Slider *low_fail_count );
#define UTL_GetHidarAccessFailCountLow _UTL_GetHidarAccessFailCountLow
 extern int _UTL_GetHidarAccessFailCountHigh ( HidarAccessHandle hah, Slider *high_fail_count );
#define UTL_GetHidarAccessFailCountHigh _UTL_GetHidarAccessFailCountHigh
 extern int _UTL_GetHidarAccessOverCountLow ( HidarAccessHandle hah, Slider *over_count_low );
#define UTL_GetHidarAccessOverCountLow _UTL_GetHidarAccessOverCountLow
 extern int _UTL_GetHidarAccessOverCountHigh ( HidarAccessHandle hah, Slider *over_count_high );
#define UTL_GetHidarAccessOverCountHigh _UTL_GetHidarAccessOverCountHigh
 extern int _UTL_GetHidarAccessLimitLow ( HidarAccessHandle hah, DSlider *limit_low, CheckButton *ldo );
#define UTL_GetHidarAccessLimitLow _UTL_GetHidarAccessLimitLow
 extern int _UTL_GetHidarAccessLimitHigh ( HidarAccessHandle hah, DSlider *limit_high, CheckButton *hdo );
#define UTL_GetHidarAccessLimitHigh _UTL_GetHidarAccessLimitHigh
 extern int _UTL_GetHidarAccessDataMin ( HidarAccessHandle hah, DSlider *data_min );
#define UTL_GetHidarAccessDataMin _UTL_GetHidarAccessDataMin
 extern int _UTL_GetHidarAccessDataMax ( HidarAccessHandle hah, DSlider *data_max );
#define UTL_GetHidarAccessDataMax _UTL_GetHidarAccessDataMax
 extern int _UTL_GetHidarAccessAddVal( HidarAccessHandle hah, DSlider *addval );
#define UTL_GetHidarAccessAddVal _UTL_GetHidarAccessAddVal
 extern int _UTL_GetHidarAccessSquareSum( HidarAccessHandle hah, DSlider *square_sum );
#define UTL_GetHidarAccessSquareSum _UTL_GetHidarAccessSquareSum
 extern int _UTL_GetHidarAccessRankMin( HidarAccessHandle hah, DSlider *rankmin );
#define UTL_GetHidarAccessRankMin _UTL_GetHidarAccessRankMin
 extern int _UTL_GetHidarAccessRankMax( HidarAccessHandle hah, DSlider *rankmax );
#define UTL_GetHidarAccessRankMax _UTL_GetHidarAccessRankMax
 extern int _UTL_GetHidarAccessRankNumber( HidarAccessHandle hah, Slider *rank_number );
#define UTL_GetHidarAccessRankNumber _UTL_GetHidarAccessRankNumber
 extern int _UTL_GetHidarAccessRankResolution ( HidarAccessHandle hah, DSlider *rank_reso );
#define UTL_GetHidarAccessRankResolution _UTL_GetHidarAccessRankResolution
 extern int _UTL_GetHidarAccessRankPassCount ( HidarAccessHandle hah, RadioButton rankno, Slider *rank_pass_count );
#define UTL_GetHidarAccessRankPassCount _UTL_GetHidarAccessRankPassCount
 extern int _UTL_GetHidarAccessRankFailCount ( HidarAccessHandle hah, RadioButton rankno, Slider *rank_fail_count );
#define UTL_GetHidarAccessRankFailCount _UTL_GetHidarAccessRankFailCount
 extern int _UTL_GetHidarAccessOverDataCount ( HidarAccessHandle hah, Slider *over_data_count );
#define UTL_GetHidarAccessOverDataCount _UTL_GetHidarAccessOverDataCount
 extern int _UTL_GetHidarAccessOverData ( HidarAccessHandle hah, RadioButton n, DSlider *overdata , RadioButton *result);
#define UTL_GetHidarAccessOverData _UTL_GetHidarAccessOverData
 extern HidarConstructHandle _UTL_GetHidarConstructHandle ( void );
#define UTL_GetHidarConstructHandle _UTL_GetHidarConstructHandle
 extern void _UTL_SetHidarConstructStationNumber( HidarConstructHandle , RadioButton );
#define UTL_SetHidarConstructStationNumber _UTL_SetHidarConstructStationNumber
 extern void _UTL_SetHidarConstructConfigHandle( HidarConstructHandle , HidarConfigHandle );
#define UTL_SetHidarConstructConfigHandle _UTL_SetHidarConstructConfigHandle
 extern void _UTL_SetHidarConstructMeasMode( HidarConstructHandle , RadioButton );
#define UTL_SetHidarConstructMeasMode _UTL_SetHidarConstructMeasMode
 extern void _UTL_SetHidarConstructPin( HidarConstructHandle , UT_PIN );
#define UTL_SetHidarConstructPin _UTL_SetHidarConstructPin
 extern void _UTL_SetHidarConstructDut( HidarConstructHandle , UT_DUT );
#define UTL_SetHidarConstructDut _UTL_SetHidarConstructDut
 extern void _UTL_AddHidarConstructData( HidarConstructHandle , HidarJudgeDataHandle );
#define UTL_AddHidarConstructData _UTL_AddHidarConstructData
 extern HidarConstructDataCursor _UTL_GetHidarConstructDataCursor( HidarConstructHandle );
#define UTL_GetHidarConstructDataCursor _UTL_GetHidarConstructDataCursor
 extern HidarJudgeDataHandle _UTL_NextHidarConstructData( HidarConstructDataCursor );
#define UTL_NextHidarConstructData _UTL_NextHidarConstructData
 extern void _UTL_ClearHidarConstructData( HidarConstructHandle );
#define UTL_ClearHidarConstructData _UTL_ClearHidarConstructData
 extern void _UTL_ConstructHidar( HidarConstructHandle );
#define UTL_ConstructHidar _UTL_ConstructHidar
 extern HidarJudgeDataHandle _UTL_GetHidarJudgeDataHandle( void );
#define UTL_GetHidarJudgeDataHandle _UTL_GetHidarJudgeDataHandle
 extern void _UTL_SetHidarJudgeData( HidarJudgeDataHandle , DSlider );
#define UTL_SetHidarJudgeData _UTL_SetHidarJudgeData
 extern void _UTL_SetHidarJudgeDataHighFail( HidarJudgeDataHandle , CheckButton );
#define UTL_SetHidarJudgeDataHighFail _UTL_SetHidarJudgeDataHighFail
 extern void _UTL_SetHidarJudgeDataLowFail( HidarJudgeDataHandle , CheckButton );
#define UTL_SetHidarJudgeDataLowFail _UTL_SetHidarJudgeDataLowFail
extern void _UTL_UpdateAdc( AdcHandle, RadioButton );
#define UTL_UpdateAdc _UTL_UpdateAdc
extern int _UTL_GetAdcInput( AdcHandle h, RadioButton *val );
#define UTL_GetAdcInput _UTL_GetAdcInput
extern int _UTL_GetAdcPinList ( AdcHandle h, char ** val );
#define UTL_GetAdcPinList _UTL_GetAdcPinList
extern int _UTL_GetAdcPgEnable( AdcHandle h, CheckButton *val );
#define UTL_GetAdcPgEnable _UTL_GetAdcPgEnable
extern int _UTL_GetAdcStartCycle( AdcHandle h, RadioButton *val );
#define UTL_GetAdcStartCycle _UTL_GetAdcStartCycle
extern int _UTL_GetAdcMeasMode( AdcHandle h, RadioButton *val );
#define UTL_GetAdcMeasMode _UTL_GetAdcMeasMode
extern int _UTL_GetAdcHistoryMode( AdcHandle h, CheckButton *val );
#define UTL_GetAdcHistoryMode _UTL_GetAdcHistoryMode
extern int _UTL_GetAdcSettlingTime( AdcHandle h, DSlider *val );
#define UTL_GetAdcSettlingTime _UTL_GetAdcSettlingTime
extern int _UTL_GetAlpgCtrlMode(AlpgCtrlHandle h, RadioButton AlpgCtrlMode , CheckButton *val );
#define UTL_GetAlpgCtrlMode _UTL_GetAlpgCtrlMode
extern void _UTL_UpdateAuxDutSignal ( AuxDutSignalHandle, RadioButton, RadioButton );
#define UTL_UpdateAuxDutSignal _UTL_UpdateAuxDutSignal
extern int _UTL_GetAuxDutSignalStationNumber( AuxDutSignalHandle, USlider * );
#define UTL_GetAuxDutSignalStationNumber _UTL_GetAuxDutSignalStationNumber
extern int _UTL_GetAuxDutSignalAllStation( AuxDutSignalHandle, CheckButton * );
#define UTL_GetAuxDutSignalAllStation _UTL_GetAuxDutSignalAllStation
extern int _UTL_GetAuxDutSignalData( AuxDutSignalHandle, USlider * );
#define UTL_GetAuxDutSignalData _UTL_GetAuxDutSignalData
extern int _UTL_GetAuxDutSignalBurstVariableName( AuxDutSignalHandle, char ** );
#define UTL_GetAuxDutSignalBurstVariableName _UTL_GetAuxDutSignalBurstVariableName
extern void _UTL_UpdateLbCtrl( LbCtrlHandle );
#define UTL_UpdateLbCtrl _UTL_UpdateLbCtrl
extern int _UTL_GetLbCtrlClockTiming( LbCtrlHandle h, DSlider *low , DSlider *high );
#define UTL_GetLbCtrlClockTiming _UTL_GetLbCtrlClockTiming
extern int _UTL_GetLbCtrlDataPacketCount( LbCtrlHandle h, USlider *count );
#define UTL_GetLbCtrlDataPacketCount _UTL_GetLbCtrlDataPacketCount
extern int _UTL_GetLbCtrlDataFirstBit( LbCtrlHandle h, RadioButton *endian );
#define UTL_GetLbCtrlDataFirstBit _UTL_GetLbCtrlDataFirstBit
extern int _UTL_GetLbCtrlSSPolarity( LbCtrlHandle h, RadioButton *type );
#define UTL_GetLbCtrlSSPolarity _UTL_GetLbCtrlSSPolarity
extern int _UTL_GetLbCtrlResetPolarity( LbCtrlHandle h, RadioButton *type );
#define UTL_GetLbCtrlResetPolarity _UTL_GetLbCtrlResetPolarity
extern int _UTL_GetLbCtrlStartDelayTime( LbCtrlHandle h, DSlider *delay_time );
#define UTL_GetLbCtrlStartDelayTime _UTL_GetLbCtrlStartDelayTime
extern int _UTL_GetLbCtrlClockCount( LbCtrlHandle h, USlider *clock_count );
#define UTL_GetLbCtrlClockCount _UTL_GetLbCtrlClockCount
extern int _UTL_GetLbCtrlData( LbCtrlHandle h, USlider *data );
#define UTL_GetLbCtrlData _UTL_GetLbCtrlData
extern int _UTL_GetLbCtrlResetDurationTime( LbCtrlHandle h, DSlider *val );
#define UTL_GetLbCtrlResetDurationTime _UTL_GetLbCtrlResetDurationTime
extern int _UTL_GetLbCtrlStrbSkewAdjust( LbCtrlHandle h, DSlider *value );
#define UTL_GetLbCtrlStrbSkewAdjust _UTL_GetLbCtrlStrbSkewAdjust
extern void _UTL_UpdateSpiCtrl( SpiCtrlHandle , RadioButton );
#define UTL_UpdateSpiCtrl _UTL_UpdateSpiCtrl
extern int _UTL_GetSpiCtrlClockTiming( SpiCtrlHandle h, DSlider *low , DSlider *high );
#define UTL_GetSpiCtrlClockTiming _UTL_GetSpiCtrlClockTiming
extern int _UTL_GetSpiCtrlSSPolarity( SpiCtrlHandle h, RadioButton *type );
#define UTL_GetSpiCtrlSSPolarity _UTL_GetSpiCtrlSSPolarity
extern int _UTL_GetSpiCtrlStartDelayTime( SpiCtrlHandle h, DSlider *delay_time );
#define UTL_GetSpiCtrlStartDelayTime _UTL_GetSpiCtrlStartDelayTime
extern int _UTL_GetSpiCtrlData( SpiCtrlHandle h, USlider **data , USlider *size );
#define UTL_GetSpiCtrlData _UTL_GetSpiCtrlData
extern int _UTL_GetSpiCtrlStrbSkewAdjust( SpiCtrlHandle h, DSlider *value );
#define UTL_GetSpiCtrlStrbSkewAdjust _UTL_GetSpiCtrlStrbSkewAdjust
extern int _UTL_GetSpiCtrlMode( SpiCtrlHandle h, RadioButton *mode);
#define UTL_GetSpiCtrlMode _UTL_GetSpiCtrlMode
extern int _UTL_GetSpiCtrlHighSpeedInterval( SpiCtrlHandle h, DSlider *command_time, DSlider *data_time);
#define UTL_GetSpiCtrlHighSpeedInterval _UTL_GetSpiCtrlHighSpeedInterval
extern void _UTL_UpdateDc( DcHandle, RadioButton );
#define UTL_UpdateDc _UTL_UpdateDc
extern int _UTL_GetDcFilter( DcHandle h, RadioButton *val );
#define UTL_GetDcFilter _UTL_GetDcFilter
extern int _UTL_GetDcLimitHigh( DcHandle h, DSlider *val );
#define UTL_GetDcLimitHigh _UTL_GetDcLimitHigh
extern int _UTL_GetDcLimitHighDo( DcHandle dch, CheckButton *val);
#define UTL_GetDcLimitHighDo _UTL_GetDcLimitHighDo
extern int _UTL_GetDcLimitLow( DcHandle h, DSlider *val );
#define UTL_GetDcLimitLow _UTL_GetDcLimitLow
extern int _UTL_GetDcLimitLowDo( DcHandle dch, CheckButton *val);
#define UTL_GetDcLimitLowDo _UTL_GetDcLimitLowDo
extern int _UTL_GetDcMclamp( DcHandle h, DSlider *val );
#define UTL_GetDcMclamp _UTL_GetDcMclamp
extern int _UTL_GetDcMeasCnt( DcHandle h, Slider *val );
#define UTL_GetDcMeasCnt _UTL_GetDcMeasCnt
extern int _UTL_GetDcMode( DcHandle h, RadioButton *val );
#define UTL_GetDcMode _UTL_GetDcMode
extern int _UTL_GetDcMrangeMax( DcHandle h, DSlider *val );
#define UTL_GetDcMrangeMax _UTL_GetDcMrangeMax
extern int _UTL_GetDcMrangeMin( DcHandle h, DSlider *val );
#define UTL_GetDcMrangeMin _UTL_GetDcMrangeMin
extern int _UTL_GetDcPclamp( DcHandle h, DSlider *val );
#define UTL_GetDcPclamp _UTL_GetDcPclamp
extern int _UTL_GetDcSource( DcHandle h, DSlider *val );
#define UTL_GetDcSource _UTL_GetDcSource
extern int _UTL_GetDcSrangeMax( DcHandle h, DSlider *val );
#define UTL_GetDcSrangeMax _UTL_GetDcSrangeMax
extern int _UTL_GetDcSrangeMin( DcHandle h, DSlider *val );
#define UTL_GetDcSrangeMin _UTL_GetDcSrangeMin
extern int _UTL_GetDcWetItem( DcHandle h, RadioButton i , CheckButton *val );
#define UTL_GetDcWetItem _UTL_GetDcWetItem
extern int _UTL_GetDcSlewRate( DcHandle h, DSlider *val );
#define UTL_GetDcSlewRate _UTL_GetDcSlewRate
extern void _UTL_UpdateDclp ( DclpHandle , RadioButton );
#define UTL_UpdateDclp _UTL_UpdateDclp
extern int _UTL_GetDclpHigh( DclpHandle h, DSlider *val );
#define UTL_GetDclpHigh _UTL_GetDclpHigh
extern int _UTL_GetDclpLow( DclpHandle h, DSlider *val );
#define UTL_GetDclpLow _UTL_GetDclpLow
extern void _UTL_UpdateVihh ( VihhHandle , RadioButton );
#define UTL_UpdateVihh _UTL_UpdateVihh
extern void _UTL_UpdateVihhPerPin( VihhHandle , UT_PIN , UT_DUT );
#define UTL_UpdateVihhPerPin _UTL_UpdateVihhPerPin
extern int _UTL_GetVihhHigh( VihhHandle h, DSlider *val );
#define UTL_GetVihhHigh _UTL_GetVihhHigh
extern int _UTL_GetVihhHv( VihhHandle h, DSlider *val );
#define UTL_GetVihhHv _UTL_GetVihhHv
extern int _UTL_GetVihhLow( VihhHandle h, DSlider *val );
#define UTL_GetVihhLow _UTL_GetVihhLow
extern void _UTL_UpdateDctCtrlRelay( DctCtrlRelayHandle, UT_PIN );
#define UTL_UpdateDctCtrlRelay _UTL_UpdateDctCtrlRelay
extern int _UTL_GetDctCtrlRelayDc( DctCtrlRelayHandle h , CheckButton *val );
#define UTL_GetDctCtrlRelayDc _UTL_GetDctCtrlRelayDc
extern int _UTL_GetDctCtrlRelayDutCtrl( DctCtrlRelayHandle h , RadioButton *val );
#define UTL_GetDctCtrlRelayDutCtrl _UTL_GetDctCtrlRelayDutCtrl
extern int _UTL_GetDctCtrlRelayDutCtrlGrpNum( DctCtrlRelayHandle h , RadioButton *val );
#define UTL_GetDctCtrlRelayDutCtrlGrpNum _UTL_GetDctCtrlRelayDutCtrlGrpNum
extern int _UTL_GetDctCtrlRelayPl( DctCtrlRelayHandle h , RadioButton *val );
#define UTL_GetDctCtrlRelayPl _UTL_GetDctCtrlRelayPl
extern int _UTL_GetDctCtrlRelayHvDr( DctCtrlRelayHandle h , CheckButton *val );
#define UTL_GetDctCtrlRelayHvDr _UTL_GetDctCtrlRelayHvDr
extern int _UTL_GetDctCtrlRelayTerm( DctCtrlRelayHandle h , CheckButton *val );
#define UTL_GetDctCtrlRelayTerm _UTL_GetDctCtrlRelayTerm
extern int _UTL_GetDctCtrlRelayVi( DctCtrlRelayHandle h , CheckButton *val );
#define UTL_GetDctCtrlRelayVi _UTL_GetDctCtrlRelayVi
extern int _UTL_GetDctCtrlRelayVo( DctCtrlRelayHandle h , CheckButton *val );
#define UTL_GetDctCtrlRelayVo _UTL_GetDctCtrlRelayVo
extern int _UTL_GetDctCtrlRelayVihh( DctCtrlRelayHandle h , CheckButton *val );
#define UTL_GetDctCtrlRelayVihh _UTL_GetDctCtrlRelayVihh
extern int _UTL_GetDctCtrlRelayWaitTime( DctCtrlRelayHandle h , DSlider *val );
#define UTL_GetDctCtrlRelayWaitTime _UTL_GetDctCtrlRelayWaitTime
extern void _UTL_UpdateDctVsCtrlRelay( DctVsCtrlRelayHandle, RadioButton );
#define UTL_UpdateDctVsCtrlRelay _UTL_UpdateDctVsCtrlRelay
extern int _UTL_GetDctVsCtrlRelayDutCtrl( DctVsCtrlRelayHandle h , RadioButton *val );
#define UTL_GetDctVsCtrlRelayDutCtrl _UTL_GetDctVsCtrlRelayDutCtrl
extern int _UTL_GetDctVsCtrlRelayDutCtrlGrpNum( DctVsCtrlRelayHandle h , RadioButton *val );
#define UTL_GetDctVsCtrlRelayDutCtrlGrpNum _UTL_GetDctVsCtrlRelayDutCtrlGrpNum
extern int _UTL_GetDctVsCtrlRelayWaitTime( DctVsCtrlRelayHandle h , DSlider *val );
#define UTL_GetDctVsCtrlRelayWaitTime _UTL_GetDctVsCtrlRelayWaitTime
extern int _UTL_GetDbmAccessUnitNumber(DbmAccessHandle h, RadioButton * val);
#define UTL_GetDbmAccessUnitNumber _UTL_GetDbmAccessUnitNumber
extern int _UTL_GetDbmAccessAllUnit(DbmAccessHandle h, CheckButton * val);
#define UTL_GetDbmAccessAllUnit _UTL_GetDbmAccessAllUnit
extern int _UTL_GetDbmAccessDataKind(DbmAccessHandle h, RadioButton * val);
#define UTL_GetDbmAccessDataKind _UTL_GetDbmAccessDataKind
extern int _UTL_GetDbmAccessBlockNumber(DbmAccessHandle h, RadioButton * val);
#define UTL_GetDbmAccessBlockNumber _UTL_GetDbmAccessBlockNumber
extern int _UTL_GetDbmAccessStartAddr(DbmAccessHandle h, USlider * val);
#define UTL_GetDbmAccessStartAddr _UTL_GetDbmAccessStartAddr
extern int _UTL_GetDbmAccessStopAddr(DbmAccessHandle h, USlider * val);
#define UTL_GetDbmAccessStopAddr _UTL_GetDbmAccessStopAddr
extern void _UTL_UpdateDbmFile(DbmFileHandle);
#define UTL_UpdateDbmFile _UTL_UpdateDbmFile
extern int _UTL_GetDbmFileMpatName(DbmFileHandle h, char **val);
#define UTL_GetDbmFileMpatName _UTL_GetDbmFileMpatName
extern int _UTL_GetDbmFileStartPc(DbmFileHandle h, USlider * val);
#define UTL_GetDbmFileStartPc _UTL_GetDbmFileStartPc
extern int _UTL_GetDbmFileResetMode(DbmFileHandle h, RadioButton * val);
#define UTL_GetDbmFileResetMode _UTL_GetDbmFileResetMode
extern DbmPatternInfoHandle _UTL_GetDbmPatternInfoHandle(void);
#define UTL_GetDbmPatternInfoHandle _UTL_GetDbmPatternInfoHandle
extern void _UTL_SetDbmPatternInfoMpatName(DbmPatternInfoHandle, char *);
#define UTL_SetDbmPatternInfoMpatName _UTL_SetDbmPatternInfoMpatName
extern void _UTL_SetDbmPatternInfoStartPc(DbmPatternInfoHandle, USlider);
#define UTL_SetDbmPatternInfoStartPc _UTL_SetDbmPatternInfoStartPc
extern void _UTL_UpdateDbmPatternInfo(DbmPatternInfoHandle);
#define UTL_UpdateDbmPatternInfo _UTL_UpdateDbmPatternInfo
extern int _UTL_GetDbmPatternInfoMpatName(DbmPatternInfoHandle h, char **val);
#define UTL_GetDbmPatternInfoMpatName _UTL_GetDbmPatternInfoMpatName
extern int _UTL_GetDbmPatternInfoStartPc(DbmPatternInfoHandle h, USlider * val);
#define UTL_GetDbmPatternInfoStartPc _UTL_GetDbmPatternInfoStartPc
extern int _UTL_GetDbmPatternInfoBaseAddr(DbmPatternInfoHandle h, USlider * val);
#define UTL_GetDbmPatternInfoBaseAddr _UTL_GetDbmPatternInfoBaseAddr
extern int _UTL_GetDbmPatternInfoDataSize(DbmPatternInfoHandle h, RadioButton alpg, USlider * val);
#define UTL_GetDbmPatternInfoDataSize _UTL_GetDbmPatternInfoDataSize
extern int _UTL_GetDbmPatternInfoStartAddr(DbmPatternInfoHandle h, RadioButton alpg, USlider * val);
#define UTL_GetDbmPatternInfoStartAddr _UTL_GetDbmPatternInfoStartAddr
extern int _UTL_GetCbmAccessUnitNumber(CbmAccessHandle h, RadioButton * val);
#define UTL_GetCbmAccessUnitNumber _UTL_GetCbmAccessUnitNumber
extern int _UTL_GetCbmAccessAllUnit(CbmAccessHandle h, CheckButton * val);
#define UTL_GetCbmAccessAllUnit _UTL_GetCbmAccessAllUnit
extern int _UTL_GetCbmAccessDataKind(CbmAccessHandle h, RadioButton * val);
#define UTL_GetCbmAccessDataKind _UTL_GetCbmAccessDataKind
extern int _UTL_GetCbmAccessStartAddr(CbmAccessHandle h, USlider * val);
#define UTL_GetCbmAccessStartAddr _UTL_GetCbmAccessStartAddr
extern int _UTL_GetCbmAccessStopAddr(CbmAccessHandle h, USlider * val);
#define UTL_GetCbmAccessStopAddr _UTL_GetCbmAccessStopAddr
extern void _UTL_UpdateCbmFile(CbmFileHandle);
#define UTL_UpdateCbmFile _UTL_UpdateCbmFile
extern int _UTL_GetCbmFileMpatName(CbmFileHandle h, char **val);
#define UTL_GetCbmFileMpatName _UTL_GetCbmFileMpatName
extern int _UTL_GetCbmFileStartPc(CbmFileHandle h, USlider * val);
#define UTL_GetCbmFileStartPc _UTL_GetCbmFileStartPc
extern int _UTL_GetCbmFileResetMode(CbmFileHandle h, RadioButton * val);
#define UTL_GetCbmFileResetMode _UTL_GetCbmFileResetMode
extern int _UTL_GetFctReadPinDut( FctReadPinHandle h, UT_DUT dut, CheckButton *val );
#define UTL_GetFctReadPinDut _UTL_GetFctReadPinDut
extern int _UTL_GetFctReadPinMode( FctReadPinHandle h, RadioButton *val );
#define UTL_GetFctReadPinMode _UTL_GetFctReadPinMode
extern int _UTL_GetFctReadPinNumber( FctReadPinHandle h, UT_PIN *val );
#define UTL_GetFctReadPinNumber _UTL_GetFctReadPinNumber
extern int _UTL_GetFctReadPinTargetBank (FctReadPinHandle h, RadioButton *val);
#define UTL_GetFctReadPinTargetBank _UTL_GetFctReadPinTargetBank
extern void _UTL_UpdateIl ( IlHandle , RadioButton );
#define UTL_UpdateIl _UTL_UpdateIl
extern int _UTL_GetIlHigh( IlHandle h, DSlider *val );
#define UTL_GetIlHigh _UTL_GetIlHigh
extern int _UTL_GetIlLow( IlHandle h, DSlider *val );
#define UTL_GetIlLow _UTL_GetIlLow
extern int _UTL_GetDctAfterDcOn( DctHandle h, RadioButton *val );
#define UTL_GetDctAfterDcOn _UTL_GetDctAfterDcOn
extern int _UTL_GetDctAfterFunc( DctHandle h, void **val );
#define UTL_GetDctAfterFunc _UTL_GetDctAfterFunc
extern int _UTL_GetDctAltMclamp( DctHandle h, DSlider *val );
#define UTL_GetDctAltMclamp _UTL_GetDctAltMclamp
extern int _UTL_GetDctAltMode( DctHandle h, RadioButton *val );
#define UTL_GetDctAltMode _UTL_GetDctAltMode
extern int _UTL_GetDctAltPclamp( DctHandle h, DSlider *val );
#define UTL_GetDctAltPclamp _UTL_GetDctAltPclamp
extern int _UTL_GetDctAltSource( DctHandle h, DSlider *val );
#define UTL_GetDctAltSource _UTL_GetDctAltSource
extern int _UTL_GetDctBeforeFunc( DctHandle h, void **val );
#define UTL_GetDctBeforeFunc _UTL_GetDctBeforeFunc
extern int _UTL_GetDctFailAction( DctHandle h, void **val );
#define UTL_GetDctFailAction _UTL_GetDctFailAction
extern int _UTL_GetDctPassAction( DctHandle h, void **val );
#define UTL_GetDctPassAction _UTL_GetDctPassAction
extern int _UTL_GetDctPinList( DctHandle h, char **val );
#define UTL_GetDctPinList _UTL_GetDctPinList
extern int _UTL_GetDctPinPl( DctHandle h, RadioButton *val );
#define UTL_GetDctPinPl _UTL_GetDctPinPl
extern int _UTL_GetDctPinHvDr( DctHandle h, CheckButton *val );
#define UTL_GetDctPinHvDr _UTL_GetDctPinHvDr
extern int _UTL_GetDctPinTerm( DctHandle h, CheckButton *val );
#define UTL_GetDctPinTerm _UTL_GetDctPinTerm
extern int _UTL_GetDctPinVi( DctHandle h, CheckButton *val );
#define UTL_GetDctPinVi _UTL_GetDctPinVi
extern int _UTL_GetDctPinVo( DctHandle h, CheckButton *val );
#define UTL_GetDctPinVo _UTL_GetDctPinVo
extern int _UTL_GetDctPinVihh( DctHandle h, CheckButton *val );
#define UTL_GetDctPinVihh _UTL_GetDctPinVihh
extern int _UTL_GetDctRelayMode( DctHandle h, RadioButton *val );
#define UTL_GetDctRelayMode _UTL_GetDctRelayMode
extern int _UTL_GetDctAutoRangeMode( DctHandle h, CheckButton *val );
#define UTL_GetDctAutoRangeMode _UTL_GetDctAutoRangeMode
extern int _UTL_GetDctGoNogoOnly( DctHandle h, CheckButton *val );
#define UTL_GetDctGoNogoOnly _UTL_GetDctGoNogoOnly
extern int _UTL_GetDctAutoTestName( DctHandle h, CheckButton *val );
#define UTL_GetDctAutoTestName _UTL_GetDctAutoTestName
extern int _UTL_GetReadMpatFileName( ReadMpatPcHandle h, char **val );
#define UTL_GetReadMpatFileName _UTL_GetReadMpatFileName
extern int _UTL_GetReadMpatLabelName( ReadMpatPcHandle h, char **val );
#define UTL_GetReadMpatLabelName _UTL_GetReadMpatLabelName
extern int _UTL_GetReadMpatModuleName( ReadMpatPcHandle h, char **val );
#define UTL_GetReadMpatModuleName _UTL_GetReadMpatModuleName
extern int _UTL_GetReadMpatStartName( ReadMpatPcHandle h, char **val );
#define UTL_GetReadMpatStartName _UTL_GetReadMpatStartName
extern PinListCursor _UTL_GetPinListCursor( void );
#define UTL_GetPinListCursor _UTL_GetPinListCursor
extern char * _UTL_NextPinList( PinListCursor csr );
#define UTL_NextPinList _UTL_NextPinList
extern int _UTL_GetPinType( char *pinlist_name, RadioButton *val );
#define UTL_GetPinType _UTL_GetPinType
extern void _UTL_UpdateReg(RegHandle);
#define UTL_UpdateReg _UTL_UpdateReg
extern int _UTL_GetRegDirection(RegHandle h, RadioButton *val );
#define UTL_GetRegDirection _UTL_GetRegDirection
extern int _UTL_GetRegRb(RegHandle, RadioButton, RadioButton *);
#define UTL_GetRegRb _UTL_GetRegRb
extern int _UTL_GetRegUs(RegHandle, RadioButton, RadioButton, USlider *);
#define UTL_GetRegUs _UTL_GetRegUs
extern int _UTL_GetRegAlpgUnit (RegHandle h, RadioButton *val);
#define UTL_GetRegAlpgUnit _UTL_GetRegAlpgUnit
extern int _UTL_GetRegTimerCycleCnt(RegHandle, RadioButton, RadioButton *, USlider *);
#define UTL_GetRegTimerCycleCnt _UTL_GetRegTimerCycleCnt
extern int _UTL_GetRegTimerTime(RegHandle, RadioButton, DSlider *);
#define UTL_GetRegTimerTime _UTL_GetRegTimerTime
extern int _UTL_GetRegUpdateUnitNumber (RegHandle h, RadioButton *val);
#define UTL_GetRegUpdateUnitNumber _UTL_GetRegUpdateUnitNumber
extern int _UTL_GetTimerMode (TimerModeHandle hid, RadioButton timer, RadioButton *mode);
#define UTL_GetTimerMode _UTL_GetTimerMode
extern int _UTL_GetTimerModeDirection (TimerModeHandle hid, RadioButton *direct);
#define UTL_GetTimerModeDirection _UTL_GetTimerModeDirection
extern void _UTL_UpdateTimerMode (TimerModeHandle hid);
#define UTL_UpdateTimerMode _UTL_UpdateTimerMode
extern void _UTL_UpdateAddrScram (AddrScramHandle);
#define UTL_UpdateAddrScram _UTL_UpdateAddrScram
extern int _UTL_GetAddrScramFileName( AddrScramHandle h, char **val );
#define UTL_GetAddrScramFileName _UTL_GetAddrScramFileName
extern int _UTL_GetAddrScramMode( AddrScramHandle h, RadioButton *val );
#define UTL_GetAddrScramMode _UTL_GetAddrScramMode
extern void _UTL_UpdatePreScram (AddrScramHandle);
#define UTL_UpdatePreScram _UTL_UpdatePreScram
extern int _UTL_GetAddrScramAddrAssign(AddrScramHandle h, RadioButton ScramAddr , RadioButton *val );
#define UTL_GetAddrScramAddrAssign _UTL_GetAddrScramAddrAssign
extern int _UTL_GetAddrScramAlpgUnit (AddrScramHandle, RadioButton *);
#define UTL_GetAddrScramAlpgUnit _UTL_GetAddrScramAlpgUnit
extern int _UTL_GetAddrScramEnableBit( AddrScramHandle h, RadioButton type, RadioButton block, USlider *val );
#define UTL_GetAddrScramEnableBit _UTL_GetAddrScramEnableBit
extern int _UTL_GetAddrScramPdsEnable( AddrScramHandle h, CheckButton *onoff );
#define UTL_GetAddrScramPdsEnable _UTL_GetAddrScramPdsEnable
extern int _UTL_GetAddrScramSeparateMode (AddrScramHandle, CheckButton *);
#define UTL_GetAddrScramSeparateMode _UTL_GetAddrScramSeparateMode
extern int _UTL_GetAddrScramSideSelect (AddrScramHandle, RadioButton *);
#define UTL_GetAddrScramSideSelect _UTL_GetAddrScramSideSelect
extern int _UTL_GetAddrScramOutputMethod (AddrScramHandle, RadioButton *);
#define UTL_GetAddrScramOutputMethod _UTL_GetAddrScramOutputMethod
extern void _UTL_UpdateScramCondition(ScramConditionHandle);
#define UTL_UpdateScramCondition _UTL_UpdateScramCondition
extern int _UTL_GetScramConditionAlpgUnit(ScramConditionHandle, RadioButton *);
#define UTL_GetScramConditionAlpgUnit _UTL_GetScramConditionAlpgUnit
extern int _UTL_GetScramConditionDivideMode(ScramConditionHandle, RadioButton *);
#define UTL_GetScramConditionDivideMode _UTL_GetScramConditionDivideMode
extern void _UTL_UpdatePreScramCondition(PreScramConditionHandle);
#define UTL_UpdatePreScramCondition _UTL_UpdatePreScramCondition
extern int _UTL_GetPreScramConditionAddr( PreScramConditionHandle h, RadioButton unit, CheckButton *val );
#define UTL_GetPreScramConditionAddr _UTL_GetPreScramConditionAddr
extern int _UTL_GetPreScramConditionAlpgUnit(PreScramConditionHandle, RadioButton *);
#define UTL_GetPreScramConditionAlpgUnit _UTL_GetPreScramConditionAlpgUnit
extern int _UTL_GetPreScramConditionMode( PreScramConditionHandle h, RadioButton *val );
#define UTL_GetPreScramConditionMode _UTL_GetPreScramConditionMode
extern int _UTL_GetPreScramConditionMixMode(PreScramConditionHandle, CheckButton *);
#define UTL_GetPreScramConditionMixMode _UTL_GetPreScramConditionMixMode
extern SignalCursor _UTL_GetPreScramConditionWriteSignalCursor(PreScramConditionHandle);
#define UTL_GetPreScramConditionWriteSignalCursor _UTL_GetPreScramConditionWriteSignalCursor
extern void _UTL_UpdateBurstScram(BurstScramHandle);
#define UTL_UpdateBurstScram _UTL_UpdateBurstScram
extern int _UTL_GetBurstScramMode(BurstScramHandle, CheckButton *);
#define UTL_GetBurstScramMode _UTL_GetBurstScramMode
extern int _UTL_GetBurstScramDdrType(BurstScramHandle,RadioButton *);
#define UTL_GetBurstScramDdrType _UTL_GetBurstScramDdrType
extern int _UTL_GetBurstScramBaseFileName(BurstScramHandle ,char **);
#define UTL_GetBurstScramBaseFileName _UTL_GetBurstScramBaseFileName
extern int _UTL_GetBurstScramDataRate(BurstScramHandle,RadioButton *);
#define UTL_GetBurstScramDataRate _UTL_GetBurstScramDataRate
extern int _UTL_GetBurstScramLength(BurstScramHandle,RadioButton *);
#define UTL_GetBurstScramLength _UTL_GetBurstScramLength
extern int _UTL_GetBurstScramWrapType(BurstScramHandle,RadioButton *);
#define UTL_GetBurstScramWrapType _UTL_GetBurstScramWrapType
extern SignalCursor _UTL_GetBurstScramWriteSignalCursor(BurstScramHandle);
#define UTL_GetBurstScramWriteSignalCursor _UTL_GetBurstScramWriteSignalCursor
extern int _UTL_GetBurstScramAddrUnit(BurstScramHandle, RadioButton, CheckButton *);
#define UTL_GetBurstScramAddrUnit _UTL_GetBurstScramAddrUnit
extern int _UTL_GetBurstScramBankAddrLoadUnit(BurstScramHandle, RadioButton , CheckButton *);
#define UTL_GetBurstScramBankAddrLoadUnit _UTL_GetBurstScramBankAddrLoadUnit
extern int _UTL_GetPatDelayCycle (PatDelayHandle hid, RadioButton data, USlider *delay_value);
#define UTL_GetPatDelayCycle _UTL_GetPatDelayCycle
extern int _UTL_GetPatDelayAlpgUnit (PatDelayHandle hid, RadioButton *alpg);
#define UTL_GetPatDelayAlpgUnit _UTL_GetPatDelayAlpgUnit
extern void _UTL_UpdatePatDelay (PatDelayHandle hid);
#define UTL_UpdatePatDelay _UTL_UpdatePatDelay
extern void _UTL_UpdateMpat (MpatHandle);
#define UTL_UpdateMpat _UTL_UpdateMpat
extern int _UTL_GetMpatFileName (MpatHandle, char **);
#define UTL_GetMpatFileName _UTL_GetMpatFileName
extern int _UTL_GetMpatStartPc (MpatHandle, USlider *);
#define UTL_GetMpatStartPc _UTL_GetMpatStartPc
extern void _UTL_UpdateAriram(AriramHandle);
#define UTL_UpdateAriram _UTL_UpdateAriram
extern int _UTL_GetAriramAlpgUnit(AriramHandle, RadioButton *);
#define UTL_GetAriramAlpgUnit _UTL_GetAriramAlpgUnit
extern int _UTL_GetAriramMode(AriramHandle, RadioButton *);
#define UTL_GetAriramMode _UTL_GetAriramMode
extern void _UTL_UpdatePdsData (PdsDataHandle hid);
#define UTL_UpdatePdsData _UTL_UpdatePdsData
extern int _UTL_GetPdsDataAlpgUnit( PdsDataHandle hid, RadioButton *alpg );
#define UTL_GetPdsDataAlpgUnit _UTL_GetPdsDataAlpgUnit
extern int _UTL_GetPdsDataDirection( PdsDataHandle hid, RadioButton *direct );
#define UTL_GetPdsDataDirection _UTL_GetPdsDataDirection
extern int _UTL_GetPdsDataPdsUnit( PdsDataHandle hid, RadioButton *pds );
#define UTL_GetPdsDataPdsUnit _UTL_GetPdsDataPdsUnit
extern int _UTL_GetPdsDataSelectorDa( PdsDataHandle hid, RadioButton *da );
#define UTL_GetPdsDataSelectorDa _UTL_GetPdsDataSelectorDa
extern int _UTL_GetPdsDataSelectorDb( PdsDataHandle hid, RadioButton *db );
#define UTL_GetPdsDataSelectorDb _UTL_GetPdsDataSelectorDb
extern int _UTL_GetPseudoRandomAlpgUnit (PseudoRandomHandle, RadioButton *);
#define UTL_GetPseudoRandomAlpgUnit _UTL_GetPseudoRandomAlpgUnit
extern int _UTL_GetPseudoRandomDirection (PseudoRandomHandle, RadioButton *);
#define UTL_GetPseudoRandomDirection _UTL_GetPseudoRandomDirection
extern int _UTL_GetPseudoRandomGenerationMethod (PseudoRandomHandle, RadioButton *);
#define UTL_GetPseudoRandomGenerationMethod _UTL_GetPseudoRandomGenerationMethod
extern int _UTL_GetPseudoRandomUpdateUnitNumber (PseudoRandomHandle, RadioButton *);
#define UTL_GetPseudoRandomUpdateUnitNumber _UTL_GetPseudoRandomUpdateUnitNumber
extern PseudoRandomTermCursor _UTL_GetPseudoRandomTermCursor (PseudoRandomHandle);
#define UTL_GetPseudoRandomTermCursor _UTL_GetPseudoRandomTermCursor
extern RadioButton _UTL_NextPseudoRandomTerm (PseudoRandomTermCursor);
#define UTL_NextPseudoRandomTerm _UTL_NextPseudoRandomTerm
extern void _UTL_UpdatePseudoRandom (PseudoRandomHandle);
#define UTL_UpdatePseudoRandom _UTL_UpdatePseudoRandom
extern void _UTL_UpdateSettlingTime( SettlingTimeHandle );
#define UTL_UpdateSettlingTime _UTL_UpdateSettlingTime
extern int _UTL_GetSettlingTime( SettlingTimeHandle h, DSlider *val );
#define UTL_GetSettlingTime _UTL_GetSettlingTime
extern int _UTL_GetSettlingTimeAfterRon( SettlingTimeHandle h, DSlider *val );
#define UTL_GetSettlingTimeAfterRon _UTL_GetSettlingTimeAfterRon
extern int _UTL_GetSettlingTimeAfterRof( SettlingTimeHandle h, DSlider *val );
#define UTL_GetSettlingTimeAfterRof _UTL_GetSettlingTimeAfterRof
extern int _UTL_GetTestAction( TestHandle h, void **val );
#define UTL_GetTestAction _UTL_GetTestAction
extern int _UTL_GetTestArg( TestHandle h, void **val );
#define UTL_GetTestArg _UTL_GetTestArg
extern void _UTL_UpdateTrig(TrigHandle);
#define UTL_UpdateTrig _UTL_UpdateTrig
extern int _UTL_GetTrigDirection(TrigHandle h , RadioButton *val);
#define UTL_GetTrigDirection _UTL_GetTrigDirection
extern int _UTL_GetTrigFailDut(TrigHandle h, UT_DUT dut,CheckButton *val);
#define UTL_GetTrigFailDut _UTL_GetTrigFailDut
extern int _UTL_GetTrigOutputCtrl(TrigHandle h,CheckButton *val);
#define UTL_GetTrigOutputCtrl _UTL_GetTrigOutputCtrl
extern int _UTL_GetTrigStateMode(TrigHandle h, RadioButton mode,CheckButton *val);
#define UTL_GetTrigStateMode _UTL_GetTrigStateMode
extern int _UTL_GetTrigStateValue(TrigHandle h, RadioButton mode, RadioButton block,USlider *val);
#define UTL_GetTrigStateValue _UTL_GetTrigStateValue
extern int _UTL_GetTrigStrbPhase(TrigHandle h,RadioButton *val);
#define UTL_GetTrigStrbPhase _UTL_GetTrigStrbPhase
extern int _UTL_GetTrigAlpgUnit (TrigHandle h, RadioButton *val);
#define UTL_GetTrigAlpgUnit _UTL_GetTrigAlpgUnit
extern int _UTL_GetTrigMode(TrigHandle, RadioButton, CheckButton *);
#define UTL_GetTrigMode _UTL_GetTrigMode
extern void _UTL_UpdateVi ( ViHandle , RadioButton );
#define UTL_UpdateVi _UTL_UpdateVi
extern void _UTL_UpdateViPerPin( ViHandle , UT_PIN , UT_DUT );
#define UTL_UpdateViPerPin _UTL_UpdateViPerPin
extern int _UTL_GetViHigh( ViHandle h, DSlider *val );
#define UTL_GetViHigh _UTL_GetViHigh
extern int _UTL_GetViHvDr( ViHandle h, CheckButton *val );
#define UTL_GetViHvDr _UTL_GetViHvDr
extern int _UTL_GetViHvLvDr( ViHandle h, CheckButton *val );
#define UTL_GetViHvLvDr _UTL_GetViHvLvDr
extern int _UTL_GetViLow( ViHandle h, DSlider *val );
#define UTL_GetViLow _UTL_GetViLow
extern void _UTL_UpdateVo ( VoHandle , RadioButton );
#define UTL_UpdateVo _UTL_UpdateVo
extern int _UTL_GetVoHigh( VoHandle h, DSlider *val );
#define UTL_GetVoHigh _UTL_GetVoHigh
extern int _UTL_GetVoLow( VoHandle h, DSlider *val );
#define UTL_GetVoLow _UTL_GetVoLow
extern void _UTL_UpdateVod ( VodHandle , RadioButton );
#define UTL_UpdateVod _UTL_UpdateVod
extern int _UTL_GetVodHigh( VodHandle h, DSlider *val );
#define UTL_GetVodHigh _UTL_GetVodHigh
extern int _UTL_GetVodLow( VodHandle h, DSlider *val );
#define UTL_GetVodLow _UTL_GetVodLow
extern void _UTL_UpdateVs( VsHandle, RadioButton );
#define UTL_UpdateVs _UTL_UpdateVs
extern void _UTL_UpdateVsTargetDut( VsHandle, RadioButton , UT_DUT );
#define UTL_UpdateVsTargetDut _UTL_UpdateVsTargetDut
extern void _UTL_UpdateVsTargetPps( VsHandle, RadioButton );
#define UTL_UpdateVsTargetPps _UTL_UpdateVsTargetPps
extern int _UTL_GetVsFilter( VsHandle h, RadioButton *val );
#define UTL_GetVsFilter _UTL_GetVsFilter
extern int _UTL_GetVsLimitHigh( VsHandle h, DSlider *val );
#define UTL_GetVsLimitHigh _UTL_GetVsLimitHigh
extern int _UTL_GetVsLimitHighDo( VsHandle vsh, CheckButton *val );
#define UTL_GetVsLimitHighDo _UTL_GetVsLimitHighDo
extern int _UTL_GetVsLimitLow( VsHandle h, DSlider *val );
#define UTL_GetVsLimitLow _UTL_GetVsLimitLow
extern int _UTL_GetVsLimitLowDo( VsHandle vsh, CheckButton *val );
#define UTL_GetVsLimitLowDo _UTL_GetVsLimitLowDo
extern int _UTL_GetVsMclamp( VsHandle h, DSlider *val );
#define UTL_GetVsMclamp _UTL_GetVsMclamp
extern int _UTL_GetVsMeasCnt( VsHandle h, Slider *val );
#define UTL_GetVsMeasCnt _UTL_GetVsMeasCnt
extern int _UTL_GetVsMode( VsHandle h, RadioButton *val );
#define UTL_GetVsMode _UTL_GetVsMode
extern int _UTL_GetVsMrangeMax( VsHandle h, DSlider *val );
#define UTL_GetVsMrangeMax _UTL_GetVsMrangeMax
extern int _UTL_GetVsMrangeMin( VsHandle h, DSlider *val );
#define UTL_GetVsMrangeMin _UTL_GetVsMrangeMin
extern int _UTL_GetVsPclamp( VsHandle h, DSlider *val );
#define UTL_GetVsPclamp _UTL_GetVsPclamp
extern int _UTL_GetVsPhaseCompensation( VsHandle h, RadioButton *val );
#define UTL_GetVsPhaseCompensation _UTL_GetVsPhaseCompensation
extern int _UTL_GetVsHighSpeedSlewRateMode( VsHandle h, CheckButton *val );
#define UTL_GetVsHighSpeedSlewRateMode _UTL_GetVsHighSpeedSlewRateMode
extern int _UTL_GetVsSlewRate( VsHandle h, DSlider *val );
#define UTL_GetVsSlewRate _UTL_GetVsSlewRate
extern int _UTL_GetVsSource( VsHandle h, DSlider *val );
#define UTL_GetVsSource _UTL_GetVsSource
extern int _UTL_GetVsSrangeMax( VsHandle h, DSlider *val );
#define UTL_GetVsSrangeMax _UTL_GetVsSrangeMax
extern int _UTL_GetVsSrangeMin( VsHandle h, DSlider *val );
#define UTL_GetVsSrangeMin _UTL_GetVsSrangeMin
extern int _UTL_GetVsWetItem( VsHandle h, RadioButton i , CheckButton *val );
#define UTL_GetVsWetItem _UTL_GetVsWetItem
extern int _UTL_GetVsParaDrive( VsHandle h, CheckButton *val );
#define UTL_GetVsParaDrive _UTL_GetVsParaDrive
extern void _UTL_UpdateVt ( VtHandle , RadioButton );
#define UTL_UpdateVt _UTL_UpdateVt
extern int _UTL_GetVt( VtHandle h, DSlider *val );
#define UTL_GetVt _UTL_GetVt
 extern int _UTL_GetBbmAccessDut( BbmAccessHandle, UT_DUT * );
#define UTL_GetBbmAccessDut _UTL_GetBbmAccessDut
 extern int _UTL_GetBbmAccessPresetAllMemory( BbmAccessHandle, CheckButton * );
#define UTL_GetBbmAccessPresetAllMemory _UTL_GetBbmAccessPresetAllMemory
 extern int _UTL_GetBbmAccessStartAddr( BbmAccessHandle, USlider * );
#define UTL_GetBbmAccessStartAddr _UTL_GetBbmAccessStartAddr
 extern int _UTL_GetBbmAccessStopAddr( BbmAccessHandle, USlider * );
#define UTL_GetBbmAccessStopAddr _UTL_GetBbmAccessStopAddr
 extern int _UTL_GetBbmAccessEnableCounter( BbmAccessHandle, RadioButton, CheckButton * );
#define UTL_GetBbmAccessEnableCounter _UTL_GetBbmAccessEnableCounter
 extern int _UTL_GetBbmAccessCounterNoClear( BbmAccessHandle, RadioButton, CheckButton * );
#define UTL_GetBbmAccessCounterNoClear _UTL_GetBbmAccessCounterNoClear
extern void _UTL_UpdateBbmConfig( BbmConfigHandle );
#define UTL_UpdateBbmConfig _UTL_UpdateBbmConfig
 extern int _UTL_GetBbmConfigAction( BbmConfigHandle, RadioButton * );
#define UTL_GetBbmConfigAction _UTL_GetBbmConfigAction
 extern int _UTL_GetBbmConfigStoreMode( BbmConfigHandle, RadioButton * );
#define UTL_GetBbmConfigStoreMode _UTL_GetBbmConfigStoreMode
 extern int _UTL_GetBbmConfigCaptureSignal( BbmConfigHandle , RadioButton * );
#define UTL_GetBbmConfigCaptureSignal _UTL_GetBbmConfigCaptureSignal
 extern int _UTL_GetBbmConfigAddrAssign( BbmConfigHandle, RadioButton, RadioButton * );
#define UTL_GetBbmConfigAddrAssign _UTL_GetBbmConfigAddrAssign
 extern int _UTL_GetBbmConfigBbcLimit( BbmConfigHandle, UT_DUT, USlider * );
#define UTL_GetBbmConfigBbcLimit _UTL_GetBbmConfigBbcLimit
 extern int _UTL_GetBbmConfigMode( BbmConfigHandle, RadioButton * );
#define UTL_GetBbmConfigMode _UTL_GetBbmConfigMode
 extern int _UTL_GetBbmConfigWriteEnable( BbmConfigHandle, UT_DUT , CheckButton * );
#define UTL_GetBbmConfigWriteEnable _UTL_GetBbmConfigWriteEnable
 extern int _UTL_GetBbmConfigSkipSignal( BbmConfigHandle, RadioButton * );
#define UTL_GetBbmConfigSkipSignal _UTL_GetBbmConfigSkipSignal
 extern int _UTL_GetBbmConfigCounterNoClear( BbmConfigHandle, RadioButton, CheckButton *);
#define UTL_GetBbmConfigCounterNoClear _UTL_GetBbmConfigCounterNoClear
 extern int _UTL_GetBbmConfigPlaneCount( BbmConfigHandle, USlider * );
#define UTL_GetBbmConfigPlaneCount _UTL_GetBbmConfigPlaneCount
extern int _UTL_GetCfbmAccessAddrBlock( CfbmAccessHandle h, USlider *val );
#define UTL_GetCfbmAccessAddrBlock _UTL_GetCfbmAccessAddrBlock
extern int _UTL_GetCfbmAccessAddrEndPointer( CfbmAccessHandle h, USlider *val );
#define UTL_GetCfbmAccessAddrEndPointer _UTL_GetCfbmAccessAddrEndPointer
extern int _UTL_GetCfbmAccessAddrStartPointer( CfbmAccessHandle h, USlider *val );
#define UTL_GetCfbmAccessAddrStartPointer _UTL_GetCfbmAccessAddrStartPointer
extern int _UTL_GetCfbmAccessPresetAllMemory( CfbmAccessHandle h, CheckButton *val );
#define UTL_GetCfbmAccessPresetAllMemory _UTL_GetCfbmAccessPresetAllMemory
extern int _UTL_GetCfbmConfigAddrAssign( CfbmConfigHandle h, RadioButton bit, RadioButton *val );
#define UTL_GetCfbmConfigAddrAssign _UTL_GetCfbmConfigAddrAssign
extern int _UTL_GetCfbmConfigCompressMode( CfbmConfigHandle h, USlider *val );
#define UTL_GetCfbmConfigCompressMode _UTL_GetCfbmConfigCompressMode
extern int _UTL_GetCfbmConfigEndXAddr( CfbmConfigHandle h, USlider *val );
#define UTL_GetCfbmConfigEndXAddr _UTL_GetCfbmConfigEndXAddr
extern int _UTL_GetCfbmConfigEndYAddr( CfbmConfigHandle h, USlider *val );
#define UTL_GetCfbmConfigEndYAddr _UTL_GetCfbmConfigEndYAddr
extern int _UTL_GetCfbmConfigEndZAddr( CfbmConfigHandle h, USlider *val );
#define UTL_GetCfbmConfigEndZAddr _UTL_GetCfbmConfigEndZAddr
extern int _UTL_GetCfbmConfigSelectBit( CfbmConfigHandle h, USlider block, USlider *val );
#define UTL_GetCfbmConfigSelectBit _UTL_GetCfbmConfigSelectBit
extern int _UTL_GetCfbmConfigSelectBitDut( CfbmConfigHandle h, USlider block, UT_DUT *val );
#define UTL_GetCfbmConfigSelectBitDut _UTL_GetCfbmConfigSelectBitDut
extern int _UTL_GetCfbmConfigSplitMemory( CfbmConfigHandle h, USlider *val );
#define UTL_GetCfbmConfigSplitMemory _UTL_GetCfbmConfigSplitMemory
extern int _UTL_GetCfbmConfigStartXAddr( CfbmConfigHandle h, USlider *val );
#define UTL_GetCfbmConfigStartXAddr _UTL_GetCfbmConfigStartXAddr
extern int _UTL_GetCfbmConfigStartYAddr( CfbmConfigHandle h, USlider *val );
#define UTL_GetCfbmConfigStartYAddr _UTL_GetCfbmConfigStartYAddr
extern int _UTL_GetCfbmConfigStartZAddr( CfbmConfigHandle h, USlider *val );
#define UTL_GetCfbmConfigStartZAddr _UTL_GetCfbmConfigStartZAddr
extern int _UTL_GetDctReadPinDut( DctReadPinHandle h, UT_DUT dut, CheckButton *val );
#define UTL_GetDctReadPinDut _UTL_GetDctReadPinDut
extern int _UTL_GetDctReadPinMode( DctReadPinHandle h, RadioButton *val );
#define UTL_GetDctReadPinMode _UTL_GetDctReadPinMode
extern int _UTL_GetDctReadPinNumber( DctReadPinHandle h, UT_PIN *val );
#define UTL_GetDctReadPinNumber _UTL_GetDctReadPinNumber
extern int _UTL_GetDctReadPinType( DctReadPinHandle h, RadioButton *val );
#define UTL_GetDctReadPinType _UTL_GetDctReadPinType
extern int _UTL_GetDctReadPinHistoryNumber( DctReadPinHandle h, RadioButton *val );
#define UTL_GetDctReadPinHistoryNumber _UTL_GetDctReadPinHistoryNumber
extern int _UTL_GetFcmAccessAction( FcmAccessHandle h, RadioButton *val );
#define UTL_GetFcmAccessAction _UTL_GetFcmAccessAction
extern int _UTL_GetFcmAccessAutoAddrAssignMode( FcmAccessHandle h, CheckButton *onoff );
#define UTL_GetFcmAccessAutoAddrAssignMode _UTL_GetFcmAccessAutoAddrAssignMode
extern int _UTL_GetFcmAccessAddrAssign( FcmAccessHandle h, RadioButton bit, RadioButton *val );
#define UTL_GetFcmAccessAddrAssign _UTL_GetFcmAccessAddrAssign
extern int _UTL_GetFcmAccessAddrAssignByFcmConfig( FcmAccessHandle fah, FcmConfigHandle fch, RadioButton area, RadioButton bit, RadioButton *sig );
#define UTL_GetFcmAccessAddrAssignByFcmConfig _UTL_GetFcmAccessAddrAssignByFcmConfig
extern int _UTL_GetFcmAccessAllBit( FcmAccessHandle h, CheckButton *val );
#define UTL_GetFcmAccessAllBit _UTL_GetFcmAccessAllBit
extern int _UTL_GetFcmAccessAllDut( FcmAccessHandle h, CheckButton *val );
#define UTL_GetFcmAccessAllDut _UTL_GetFcmAccessAllDut
extern FcmAccessBitCursor _UTL_GetFcmAccessBitCursor( FcmAccessHandle h );
#define UTL_GetFcmAccessBitCursor _UTL_GetFcmAccessBitCursor
extern RadioButton _UTL_NextFcmAccessBit( FcmAccessBitCursor csr );
#define UTL_NextFcmAccessBit _UTL_NextFcmAccessBit
extern int _UTL_GetFcmAccessDut( FcmAccessHandle h, UT_DUT *val );
#define UTL_GetFcmAccessDut _UTL_GetFcmAccessDut
extern int _UTL_GetFcmAccessEndXAddr( FcmAccessHandle h, USlider *val );
#define UTL_GetFcmAccessEndXAddr _UTL_GetFcmAccessEndXAddr
extern int _UTL_GetFcmAccessEndYAddr( FcmAccessHandle h, USlider *val );
#define UTL_GetFcmAccessEndYAddr _UTL_GetFcmAccessEndYAddr
extern int _UTL_GetFcmAccessEndZAddr( FcmAccessHandle h, USlider *val );
#define UTL_GetFcmAccessEndZAddr _UTL_GetFcmAccessEndZAddr
extern int _UTL_GetFcmAccessPresetAllMemory( FcmAccessHandle h, CheckButton *val );
#define UTL_GetFcmAccessPresetAllMemory _UTL_GetFcmAccessPresetAllMemory
extern int _UTL_GetFcmAccessPresetIgnoreAddr( FcmAccessHandle , CheckButton * );
#define UTL_GetFcmAccessPresetIgnoreAddr _UTL_GetFcmAccessPresetIgnoreAddr
extern int _UTL_GetFcmAccessPresetPreserveFbm( FcmAccessHandle , CheckButton * );
#define UTL_GetFcmAccessPresetPreserveFbm _UTL_GetFcmAccessPresetPreserveFbm
extern int _UTL_GetFcmAccessSearchMaxCnt( FcmAccessHandle h, USlider *val );
#define UTL_GetFcmAccessSearchMaxCnt _UTL_GetFcmAccessSearchMaxCnt
extern int _UTL_GetFcmAccessStartXAddr( FcmAccessHandle h, USlider *val );
#define UTL_GetFcmAccessStartXAddr _UTL_GetFcmAccessStartXAddr
extern int _UTL_GetFcmAccessStartYAddr( FcmAccessHandle h, USlider *val );
#define UTL_GetFcmAccessStartYAddr _UTL_GetFcmAccessStartYAddr
extern int _UTL_GetFcmAccessStartZAddr( FcmAccessHandle h, USlider *val );
#define UTL_GetFcmAccessStartZAddr _UTL_GetFcmAccessStartZAddr
extern int _UTL_GetFcmAccessAlpgUnit( FcmAccessHandle h, RadioButton *alpg );
#define UTL_GetFcmAccessAlpgUnit _UTL_GetFcmAccessAlpgUnit
extern int _UTL_GetFcmAccessActionNumber( FcmAccessHandle h, RadioButton action_index, RadioButton *action_num );
#define UTL_GetFcmAccessActionNumber _UTL_GetFcmAccessActionNumber
extern int _UTL_GetFcmAccessCompactionMode( FcmAccessHandle h, RadioButton *compactionmode );
#define UTL_GetFcmAccessCompactionMode _UTL_GetFcmAccessCompactionMode
extern int _UTL_GetFcmAccessBitMode( FcmAccessHandle h, RadioButton *bitmode );
#define UTL_GetFcmAccessBitMode _UTL_GetFcmAccessBitMode
extern int _UTL_GetFcmAccessBitBlock( FcmAccessHandle h, RadioButton *bitblock );
#define UTL_GetFcmAccessBitBlock _UTL_GetFcmAccessBitBlock
extern int _UTL_GetFcmAccessApLink( FcmAccessHandle h, RadioButton *aplink );
#define UTL_GetFcmAccessApLink _UTL_GetFcmAccessApLink
extern int _UTL_GetFcmAccessSparePackageMode( FcmAccessHandle h, CheckButton *onoff );
#define UTL_GetFcmAccessSparePackageMode _UTL_GetFcmAccessSparePackageMode
extern int _UTL_GetFcmAccessSpareAddrAssign( FcmAccessHandle h, RadioButton type, RadioButton bit, RadioButton *signal );
#define UTL_GetFcmAccessSpareAddrAssign _UTL_GetFcmAccessSpareAddrAssign
extern int _UTL_GetFcmAccessPfcMode( FcmAccessHandle h, RadioButton *mode );
#define UTL_GetFcmAccessPfcMode _UTL_GetFcmAccessPfcMode
extern int _UTL_GetFcmAccessPfcNoClear( FcmAccessHandle h, CheckButton *onoff );
#define UTL_GetFcmAccessPfcNoClear _UTL_GetFcmAccessPfcNoClear
extern int _UTL_GetFcmAccessAreaDivision (FcmAccessHandle h, RadioButton bit, RadioButton *val);
#define UTL_GetFcmAccessAreaDivision _UTL_GetFcmAccessAreaDivision
 extern void _UTL_UpdateFcmConfig ( FcmConfigHandle );
#define UTL_UpdateFcmConfig _UTL_UpdateFcmConfig
extern int _UTL_GetFcmConfigMultiMode( FcmConfigHandle h, RadioButton *multimode );
#define UTL_GetFcmConfigMultiMode _UTL_GetFcmConfigMultiMode
extern int _UTL_GetFcmConfigDut( FcmConfigHandle h, UT_DUT *dut );
#define UTL_GetFcmConfigDut _UTL_GetFcmConfigDut
 extern USlider _UTL_ReadFcmConfigGroupCount ( FcmConfigHandle );
#define UTL_ReadFcmConfigGroupCount _UTL_ReadFcmConfigGroupCount
 extern USlider _UTL_ReadFcmConfigGroupDutCount( FcmConfigHandle );
#define UTL_ReadFcmConfigGroupDutCount _UTL_ReadFcmConfigGroupDutCount
 extern DutCursor _UTL_GetFcmConfigGroupDutCursor( FcmConfigHandle, RadioButton );
#define UTL_GetFcmConfigGroupDutCursor _UTL_GetFcmConfigGroupDutCursor
 extern DutCursor _UTL_GetFcmConfigDutCursor ( void );
#define UTL_GetFcmConfigDutCursor _UTL_GetFcmConfigDutCursor
extern int _UTL_GetFcmConfigBitSize( FcmConfigHandle h, USlider *val );
#define UTL_GetFcmConfigBitSize _UTL_GetFcmConfigBitSize
extern int _UTL_GetFcmConfigDutBitSize( FcmConfigHandle h, RadioButton *size );
#define UTL_GetFcmConfigDutBitSize _UTL_GetFcmConfigDutBitSize
extern int _UTL_GetFcmConfigAddrAssign( FcmConfigHandle h, RadioButton bit, RadioButton *val );
#define UTL_GetFcmConfigAddrAssign _UTL_GetFcmConfigAddrAssign
extern int _UTL_GetFcmConfigSplitAddrAssign( FcmConfigHandle h, RadioButton idx, RadioButton *signal );
#define UTL_GetFcmConfigSplitAddrAssign _UTL_GetFcmConfigSplitAddrAssign
extern int _UTL_GetFcmConfigAddrAssignByAlpg( FcmConfigHandle h, RadioButton alpg, RadioButton address_bit, RadioButton *signal );
#define UTL_GetFcmConfigAddrAssignByAlpg _UTL_GetFcmConfigAddrAssignByAlpg
extern int _UTL_GetFcmConfigMaxAddrBitNum( FcmConfigHandle h , USlider *val );
#define UTL_GetFcmConfigMaxAddrBitNum _UTL_GetFcmConfigMaxAddrBitNum
extern int _UTL_GetFcmConfigAlpgUnit( FcmConfigHandle h, RadioButton *alpg );
#define UTL_GetFcmConfigAlpgUnit _UTL_GetFcmConfigAlpgUnit
 extern PinCursor _UTL_GetFcmConfigPinAssign ( FcmConfigHandle, RadioButton );
#define UTL_GetFcmConfigPinAssign _UTL_GetFcmConfigPinAssign
extern int _UTL_GetFcmConfigPinAssignTarget( FcmConfigHandle h, RadioButton *target );
#define UTL_GetFcmConfigPinAssignTarget _UTL_GetFcmConfigPinAssignTarget
 extern PinCursor _UTL_GetFcmConfigMaskPinAssign( FcmConfigHandle, RadioButton );
#define UTL_GetFcmConfigMaskPinAssign _UTL_GetFcmConfigMaskPinAssign
extern FcmConfigBitSelectCursor _UTL_GetFcmConfigBitSelectCursor( FcmConfigHandle h, RadioButton fcmbit );
#define UTL_GetFcmConfigBitSelectCursor _UTL_GetFcmConfigBitSelectCursor
extern RadioButton _UTL_NextFcmConfigBitSelect( FcmConfigBitSelectCursor csr );
#define UTL_NextFcmConfigBitSelect _UTL_NextFcmConfigBitSelect
extern int _UTL_GetFcmConfigBitSelectTarget( FcmConfigHandle h, RadioButton *bitseltarget );
#define UTL_GetFcmConfigBitSelectTarget _UTL_GetFcmConfigBitSelectTarget
extern int _UTL_GetFcmConfigStoreSignal( FcmConfigHandle h, RadioButton *val );
#define UTL_GetFcmConfigStoreSignal _UTL_GetFcmConfigStoreSignal
extern int _UTL_GetFcmConfigStoreSignalByMMType( FcmConfigHandle h, RadioButton mmtype, RadioButton *storesig );
#define UTL_GetFcmConfigStoreSignalByMMType _UTL_GetFcmConfigStoreSignalByMMType
extern int _UTL_GetFcmConfigStoreInhSignal( FcmConfigHandle h, RadioButton *storeinhsig);
#define UTL_GetFcmConfigStoreInhSignal _UTL_GetFcmConfigStoreInhSignal
extern int _UTL_GetFcmConfigAddrScram( FcmConfigHandle h, CheckButton *val );
#define UTL_GetFcmConfigAddrScram _UTL_GetFcmConfigAddrScram
extern int _UTL_GetFcmConfigAddrScramByAlpg( FcmConfigHandle h, RadioButton alpg, CheckButton *onoff );
#define UTL_GetFcmConfigAddrScramByAlpg _UTL_GetFcmConfigAddrScramByAlpg
extern int _UTL_GetFcmConfigAction( FcmConfigHandle h, RadioButton n, RadioButton *val );
#define UTL_GetFcmConfigAction _UTL_GetFcmConfigAction
extern int _UTL_GetFcmConfigMaxActionNum( FcmConfigHandle h , USlider *val );
#define UTL_GetFcmConfigMaxActionNum _UTL_GetFcmConfigMaxActionNum
extern FcmConfigStrbChannelCursor _UTL_GetFcmConfigStrbChannelCursor( FcmConfigHandle h, RadioButton action_num, RadioButton alpg, RadioButton splitindex );
#define UTL_GetFcmConfigStrbChannelCursor _UTL_GetFcmConfigStrbChannelCursor
extern RadioButton _UTL_NextFcmConfigStrbChannel( FcmConfigStrbChannelCursor csr );
#define UTL_NextFcmConfigStrbChannel _UTL_NextFcmConfigStrbChannel
extern int _UTL_GetFcmConfigRate( FcmConfigHandle h, RadioButton *val );
#define UTL_GetFcmConfigRate _UTL_GetFcmConfigRate
extern int _UTL_GetFcmConfigDelay( FcmConfigHandle h, USlider *delay );
#define UTL_GetFcmConfigDelay _UTL_GetFcmConfigDelay
extern int _UTL_GetFcmConfigDelayByAlpg( FcmConfigHandle h, RadioButton alpg, USlider *delay );
#define UTL_GetFcmConfigDelayByAlpg _UTL_GetFcmConfigDelayByAlpg
extern int _UTL_GetFcmConfigModeDelayByAlpg( FcmConfigHandle h, RadioButton alpg, RadioButton mode, USlider *delay );
#define UTL_GetFcmConfigModeDelayByAlpg _UTL_GetFcmConfigModeDelayByAlpg
extern int _UTL_GetFcmConfigSparePackageMode( FcmConfigHandle h, CheckButton *onoff );
#define UTL_GetFcmConfigSparePackageMode _UTL_GetFcmConfigSparePackageMode
extern int _UTL_GetFcmConfigSpareAddrAssign( FcmConfigHandle h, RadioButton type, RadioButton bit, RadioButton *signal );
#define UTL_GetFcmConfigSpareAddrAssign _UTL_GetFcmConfigSpareAddrAssign
extern int _UTL_GetFcmConfigDdrMode( FcmConfigHandle h, CheckButton *onoff );
#define UTL_GetFcmConfigDdrMode _UTL_GetFcmConfigDdrMode
extern int _UTL_GetFcmConfigExMode( FcmConfigHandle h, CheckButton *onoff );
#define UTL_GetFcmConfigExMode _UTL_GetFcmConfigExMode
extern int _UTL_GetFcmConfigPfcNoClear( FcmConfigHandle h, CheckButton *onoff );
#define UTL_GetFcmConfigPfcNoClear _UTL_GetFcmConfigPfcNoClear
extern int _UTL_GetFcmConfigScramEnableStartAddrBit( FcmConfigHandle, USlider * );
#define UTL_GetFcmConfigScramEnableStartAddrBit _UTL_GetFcmConfigScramEnableStartAddrBit
extern int _UTL_GetFcmConfigBurstCaptureLength( FcmConfigHandle h, RadioButton *len );
#define UTL_GetFcmConfigBurstCaptureLength _UTL_GetFcmConfigBurstCaptureLength
extern int _UTL_GetFcmConfigRealTimeCountEnable( FcmConfigHandle handle, CheckButton *onoff );
#define UTL_GetFcmConfigRealTimeCountEnable _UTL_GetFcmConfigRealTimeCountEnable
extern int _UTL_GetFcmConfigFcsmMaxStoreCnt (FcmConfigHandle, USlider *max_cnt);
#define UTL_GetFcmConfigFcsmMaxStoreCnt _UTL_GetFcmConfigFcsmMaxStoreCnt
extern FcmConfigAreaDivisionBitCursor _UTL_GetFcmConfigAreaDivisionBitCursor(FcmConfigHandle h, RadioButton type);
#define UTL_GetFcmConfigAreaDivisionBitCursor _UTL_GetFcmConfigAreaDivisionBitCursor
extern RadioButton _UTL_NextFcmConfigAreaDivisionBit( FcmConfigAreaDivisionBitCursor csr );
#define UTL_NextFcmConfigAreaDivisionBit _UTL_NextFcmConfigAreaDivisionBit
extern int _UTL_GetFasmAccessStartAddr( FasmAccessHandle h , USlider *val );
#define UTL_GetFasmAccessStartAddr _UTL_GetFasmAccessStartAddr
extern int _UTL_GetFasmAccessStopAddr( FasmAccessHandle h , USlider *val );
#define UTL_GetFasmAccessStopAddr _UTL_GetFasmAccessStopAddr
extern int _UTL_GetFasmAccessBitBlock( FasmAccessHandle h , RadioButton *bitblock );
#define UTL_GetFasmAccessBitBlock _UTL_GetFasmAccessBitBlock
 extern void _UTL_UpdateEccConfig (EccConfigHandle);
#define UTL_UpdateEccConfig _UTL_UpdateEccConfig
extern int _UTL_GetEccConfigCounterNoClear (EccConfigHandle, CheckButton *);
#define UTL_GetEccConfigCounterNoClear _UTL_GetEccConfigCounterNoClear
extern int _UTL_GetEccConfigCounterLimit (EccConfigHandle, RadioButton, RadioButton, USlider *);
#define UTL_GetEccConfigCounterLimit _UTL_GetEccConfigCounterLimit
extern int _UTL_GetEccConfigCounterEnableSignal (EccConfigHandle, RadioButton, RadioButton *);
#define UTL_GetEccConfigCounterEnableSignal _UTL_GetEccConfigCounterEnableSignal
extern int _UTL_GetEccConfigJudgeSignal (EccConfigHandle, RadioButton, RadioButton *);
#define UTL_GetEccConfigJudgeSignal _UTL_GetEccConfigJudgeSignal
extern int _UTL_GetEccConfigCounterClearSignal (EccConfigHandle, RadioButton *);
#define UTL_GetEccConfigCounterClearSignal _UTL_GetEccConfigCounterClearSignal
 extern void _UTL_UpdateTprogConfig (TprogConfigHandle);
#define UTL_UpdateTprogConfig _UTL_UpdateTprogConfig
 extern int _UTL_GetTprogConfigAverageLimit(TprogConfigHandle h, USlider *AverageLimit);
#define UTL_GetTprogConfigAverageLimit _UTL_GetTprogConfigAverageLimit
 extern int _UTL_GetTprogConfigMaxLimit(TprogConfigHandle h, USlider *MaxLimit);
#define UTL_GetTprogConfigMaxLimit _UTL_GetTprogConfigMaxLimit
 extern int _UTL_GetTprogConfigCounterEnableSignal(TprogConfigHandle h, RadioButton *CounterEnableSignal);
#define UTL_GetTprogConfigCounterEnableSignal _UTL_GetTprogConfigCounterEnableSignal
 extern int _UTL_GetTprogConfigJudgeSignal(TprogConfigHandle h, RadioButton *JudgeSignal);
#define UTL_GetTprogConfigJudgeSignal _UTL_GetTprogConfigJudgeSignal
 extern int _UTL_GetTprogConfigCounterClearSignal(TprogConfigHandle h, RadioButton *CounterClearSignal);
#define UTL_GetTprogConfigCounterClearSignal _UTL_GetTprogConfigCounterClearSignal
extern int _UTL_GetAfmPatternInfoMpatName (AfmPatternInfoHandle, char **);
#define UTL_GetAfmPatternInfoMpatName _UTL_GetAfmPatternInfoMpatName
extern int _UTL_GetAfmPatternInfoModuleNum (AfmPatternInfoHandle, USlider *);
#define UTL_GetAfmPatternInfoModuleNum _UTL_GetAfmPatternInfoModuleNum
extern int _UTL_GetAfmPatternInfoStartPc (AfmPatternInfoHandle, USlider, USlider *);
#define UTL_GetAfmPatternInfoStartPc _UTL_GetAfmPatternInfoStartPc
extern int _UTL_GetAfmPatternInfoBitSize (AfmPatternInfoHandle, USlider, USlider *);
#define UTL_GetAfmPatternInfoBitSize _UTL_GetAfmPatternInfoBitSize
extern int _UTL_GetAfmPatternInfoAMinXAddr (AfmPatternInfoHandle, USlider, USlider *);
#define UTL_GetAfmPatternInfoAMinXAddr _UTL_GetAfmPatternInfoAMinXAddr
extern int _UTL_GetAfmPatternInfoAMinYAddr (AfmPatternInfoHandle, USlider, USlider *);
#define UTL_GetAfmPatternInfoAMinYAddr _UTL_GetAfmPatternInfoAMinYAddr
extern int _UTL_GetAfmPatternInfoAMinZAddr (AfmPatternInfoHandle, USlider, USlider *);
#define UTL_GetAfmPatternInfoAMinZAddr _UTL_GetAfmPatternInfoAMinZAddr
extern int _UTL_GetAfmPatternInfoAMaxXAddr (AfmPatternInfoHandle, USlider, USlider *);
#define UTL_GetAfmPatternInfoAMaxXAddr _UTL_GetAfmPatternInfoAMaxXAddr
extern int _UTL_GetAfmPatternInfoAMaxYAddr (AfmPatternInfoHandle, USlider, USlider *);
#define UTL_GetAfmPatternInfoAMaxYAddr _UTL_GetAfmPatternInfoAMaxYAddr
extern int _UTL_GetAfmPatternInfoAMaxZAddr (AfmPatternInfoHandle, USlider, USlider *);
#define UTL_GetAfmPatternInfoAMaxZAddr _UTL_GetAfmPatternInfoAMaxZAddr
extern int _UTL_GetAfmPatternAccessAfmPatternInfo(AfmPatternAccessHandle ah, AfmPatternInfoHandle * ih);
#define UTL_GetAfmPatternAccessAfmPatternInfo _UTL_GetAfmPatternAccessAfmPatternInfo
extern int _UTL_GetAfmPatternAccessModuleIndex (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessModuleIndex _UTL_GetAfmPatternAccessModuleIndex
extern int _UTL_GetAfmPatternAccessAreaIndex (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessAreaIndex _UTL_GetAfmPatternAccessAreaIndex
extern int _UTL_GetAfmPatternAccessAreaReadMode (AfmPatternAccessHandle, CheckButton *);
#define UTL_GetAfmPatternAccessAreaReadMode _UTL_GetAfmPatternAccessAreaReadMode
extern int _UTL_GetAfmPatternAccessDataFormat (AfmPatternAccessHandle, RadioButton *);
#define UTL_GetAfmPatternAccessDataFormat _UTL_GetAfmPatternAccessDataFormat
extern int _UTL_GetAfmPatternAccessBitBlockNum (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessBitBlockNum _UTL_GetAfmPatternAccessBitBlockNum
extern int _UTL_GetAfmPatternAccessBitBlock (AfmPatternAccessHandle, RadioButton *);
#define UTL_GetAfmPatternAccessBitBlock _UTL_GetAfmPatternAccessBitBlock
extern int _UTL_GetAfmPatternAccessStartXAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessStartXAddr _UTL_GetAfmPatternAccessStartXAddr
extern int _UTL_GetAfmPatternAccessStartYAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessStartYAddr _UTL_GetAfmPatternAccessStartYAddr
extern int _UTL_GetAfmPatternAccessStartZAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessStartZAddr _UTL_GetAfmPatternAccessStartZAddr
extern int _UTL_GetAfmPatternAccessStopXAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessStopXAddr _UTL_GetAfmPatternAccessStopXAddr
extern int _UTL_GetAfmPatternAccessStopYAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessStopYAddr _UTL_GetAfmPatternAccessStopYAddr
extern int _UTL_GetAfmPatternAccessStopZAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessStopZAddr _UTL_GetAfmPatternAccessStopZAddr
extern int _UTL_GetAfmPatternAccessAMaxXAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessAMaxXAddr _UTL_GetAfmPatternAccessAMaxXAddr
extern int _UTL_GetAfmPatternAccessAMaxYAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessAMaxYAddr _UTL_GetAfmPatternAccessAMaxYAddr
extern int _UTL_GetAfmPatternAccessAMaxZAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessAMaxZAddr _UTL_GetAfmPatternAccessAMaxZAddr
extern int _UTL_GetAfmPatternAccessAreaNum (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessAreaNum _UTL_GetAfmPatternAccessAreaNum
extern int _UTL_GetAfmPatternAccessAreaStartXAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessAreaStartXAddr _UTL_GetAfmPatternAccessAreaStartXAddr
extern int _UTL_GetAfmPatternAccessAreaStartYAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessAreaStartYAddr _UTL_GetAfmPatternAccessAreaStartYAddr
extern int _UTL_GetAfmPatternAccessAreaStartZAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessAreaStartZAddr _UTL_GetAfmPatternAccessAreaStartZAddr
extern int _UTL_GetAfmPatternAccessAreaStopXAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessAreaStopXAddr _UTL_GetAfmPatternAccessAreaStopXAddr
extern int _UTL_GetAfmPatternAccessAreaStopYAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessAreaStopYAddr _UTL_GetAfmPatternAccessAreaStopYAddr
extern int _UTL_GetAfmPatternAccessAreaStopZAddr (AfmPatternAccessHandle, USlider *);
#define UTL_GetAfmPatternAccessAreaStopZAddr _UTL_GetAfmPatternAccessAreaStopZAddr
 extern void _UTL_UpdateFcmMultiSideConfig ( FcmMultiSideConfigHandle );
#define UTL_UpdateFcmMultiSideConfig _UTL_UpdateFcmMultiSideConfig
extern int _UTL_GetFcmMultiSideConfigSideCount( FcmMultiSideConfigHandle, RadioButton * );
#define UTL_GetFcmMultiSideConfigSideCount _UTL_GetFcmMultiSideConfigSideCount
extern int _UTL_GetFcmMultiSideConfigSideMode( FcmMultiSideConfigHandle, RadioButton, RadioButton * );
#define UTL_GetFcmMultiSideConfigSideMode _UTL_GetFcmMultiSideConfigSideMode
extern int _UTL_GetFctAfterFunc( FctHandle h, void **val );
#define UTL_GetFctAfterFunc _UTL_GetFctAfterFunc
extern int _UTL_GetFctBeforeFunc( FctHandle h, void **val );
#define UTL_GetFctBeforeFunc _UTL_GetFctBeforeFunc
extern int _UTL_GetFctContinue( FctHandle h, CheckButton *val );
#define UTL_GetFctContinue _UTL_GetFctContinue
extern int _UTL_GetFctFailAction( FctHandle h, void **val );
#define UTL_GetFctFailAction _UTL_GetFctFailAction
extern int _UTL_GetFctFailInhibit( FctHandle h, CheckButton *val );
#define UTL_GetFctFailInhibit _UTL_GetFctFailInhibit
extern int _UTL_GetFctMpatName( FctHandle h, char **val );
#define UTL_GetFctMpatName _UTL_GetFctMpatName
extern int _UTL_GetFctNoClear( FctHandle h, CheckButton *val );
#define UTL_GetFctNoClear _UTL_GetFctNoClear
extern int _UTL_GetFctNoWait( FctHandle h, CheckButton *val );
#define UTL_GetFctNoWait _UTL_GetFctNoWait
extern int _UTL_GetFctPassAction( FctHandle h, void **val );
#define UTL_GetFctPassAction _UTL_GetFctPassAction
extern int _UTL_GetFctRepeat( FctHandle h, CheckButton *val );
#define UTL_GetFctRepeat _UTL_GetFctRepeat
extern int _UTL_GetFctSronInhibit( FctHandle h, CheckButton *val );
#define UTL_GetFctSronInhibit _UTL_GetFctSronInhibit
extern int _UTL_GetFctMpatTransferInhibit( FctHandle h, CheckButton *val );
#define UTL_GetFctMpatTransferInhibit _UTL_GetFctMpatTransferInhibit
extern int _UTL_GetFctStartFunc( FctHandle h, void **val );
#define UTL_GetFctStartFunc _UTL_GetFctStartFunc
extern int _UTL_GetFctStartPc( FctHandle h, USlider *val );
#define UTL_GetFctStartPc _UTL_GetFctStartPc
extern int _UTL_GetFctTimeLimitAction( FctHandle h, void **val );
#define UTL_GetFctTimeLimitAction _UTL_GetFctTimeLimitAction
extern int _UTL_GetFctTimeLimitData( FctHandle h, USlider *val );
#define UTL_GetFctTimeLimitData _UTL_GetFctTimeLimitData
extern int _UTL_GetFctTimeLimitMode( FctHandle h, CheckButton *val );
#define UTL_GetFctTimeLimitMode _UTL_GetFctTimeLimitMode
extern void _UTL_UpdateFlash(FlashHandle);
#define UTL_UpdateFlash _UTL_UpdateFlash
extern int _UTL_GetFlashCounterClearCondition( FlashHandle h, UT_DUT dut, RadioButton *val );
#define UTL_GetFlashCounterClearCondition _UTL_GetFlashCounterClearCondition
extern int _UTL_GetFlashCounterIncCondition( FlashHandle h, UT_DUT dut, RadioButton *val );
#define UTL_GetFlashCounterIncCondition _UTL_GetFlashCounterIncCondition
extern int _UTL_GetFlashHoldClearCondition( FlashHandle h, UT_DUT dut, RadioButton *val );
#define UTL_GetFlashHoldClearCondition _UTL_GetFlashHoldClearCondition
extern int _UTL_GetFlashHoldLoadCondition( FlashHandle h, UT_DUT dut, RadioButton *val );
#define UTL_GetFlashHoldLoadCondition _UTL_GetFlashHoldLoadCondition
extern int _UTL_GetFlashHoldMode( FlashHandle h, UT_DUT dut, RadioButton *val );
#define UTL_GetFlashHoldMode _UTL_GetFlashHoldMode
extern int _UTL_GetFlashLimitCount( FlashHandle h, UT_DUT dut, Slider *val );
#define UTL_GetFlashLimitCount _UTL_GetFlashLimitCount
extern int _UTL_GetFlashMaskMode( FlashHandle h, UT_DUT dut, CheckButton *val );
#define UTL_GetFlashMaskMode _UTL_GetFlashMaskMode
extern int _UTL_GetFlashMode( FlashHandle h, UT_DUT dut, RadioButton *val );
#define UTL_GetFlashMode _UTL_GetFlashMode
extern int _UTL_GetFlashCpInhPinMode( FlashHandle handle, CheckButton * val );
#define UTL_GetFlashCpInhPinMode _UTL_GetFlashCpInhPinMode
extern int _UTL_GetFlashCpInhPin( FlashHandle handle, char ** pinlist_name );
#define UTL_GetFlashCpInhPin _UTL_GetFlashCpInhPin
extern int _UTL_GetReadFlashCounterDut( ReadFlashCounterHandle h, UT_DUT *val );
#define UTL_GetReadFlashCounterDut _UTL_GetReadFlashCounterDut
extern int _UTL_GetReadFlashHoldDut( ReadFlashHoldHandle h, UT_DUT *val );
#define UTL_GetReadFlashHoldDut _UTL_GetReadFlashHoldDut
extern int _UTL_GetReadFlashHoldPin( ReadFlashHoldHandle h, UT_PIN *val );
#define UTL_GetReadFlashHoldPin _UTL_GetReadFlashHoldPin
extern int _UTL_GetReadFlashMaxFailDut( ReadFlashMaxFailHandle h, UT_DUT *val );
#define UTL_GetReadFlashMaxFailDut _UTL_GetReadFlashMaxFailDut
extern void _UTL_UpdatePin(PinHandle, UT_PIN, RadioButton, UT_DUT);
#define UTL_UpdatePin _UTL_UpdatePin
extern int _UTL_GetPinDcConnect( PinHandle ph, CheckButton *val );
#define UTL_GetPinDcConnect _UTL_GetPinDcConnect
extern int _UTL_GetPinDclp( PinHandle ph, CheckButton *val );
#define UTL_GetPinDclp _UTL_GetPinDclp
extern int _UTL_GetPinDrClock( PinHandle ph, RadioButton type, RadioButton *val );
#define UTL_GetPinDrClock _UTL_GetPinDrClock
extern int _UTL_GetPinDreOffTermMode(PinHandle pinh, RadioButton *val);
#define UTL_GetPinDreOffTermMode _UTL_GetPinDreOffTermMode
extern int _UTL_GetPinDrzPulseWidth( PinHandle ph, RadioButton *val );
#define UTL_GetPinDrzPulseWidth _UTL_GetPinDrzPulseWidth
extern int _UTL_GetPinDrWaveform( PinHandle ph, RadioButton *val );
#define UTL_GetPinDrWaveform _UTL_GetPinDrWaveform
extern int _UTL_GetPinDrPort( PinHandle ph, RadioButton *val );
#define UTL_GetPinDrPort _UTL_GetPinDrPort
extern int _UTL_GetPinDreClock( PinHandle ph, RadioButton *val );
#define UTL_GetPinDreClock _UTL_GetPinDreClock
extern int _UTL_GetPinDreOffsetClock( PinHandle ph, RadioButton *val );
#define UTL_GetPinDreOffsetClock _UTL_GetPinDreOffsetClock
extern int _UTL_GetPinDreNumber( PinHandle ph, RadioButton *val );
#define UTL_GetPinDreNumber _UTL_GetPinDreNumber
extern int _UTL_GetPinDrePatternInh( PinHandle ph, CheckButton *val );
#define UTL_GetPinDrePatternInh _UTL_GetPinDrePatternInh
extern int _UTL_GetPinDreWaveform( PinHandle ph, RadioButton *val );
#define UTL_GetPinDreWaveform _UTL_GetPinDreWaveform
extern int _UTL_GetPinDronInit( PinHandle ph, CheckButton *val );
#define UTL_GetPinDronInit _UTL_GetPinDronInit
extern int _UTL_GetPinDbmPinDrePattern(PinHandle pinh, CheckButton *val);
#define UTL_GetPinDbmPinDrePattern _UTL_GetPinDbmPinDrePattern
extern int _UTL_GetPinEinv( PinHandle ph, CheckButton *val );
#define UTL_GetPinEinv _UTL_GetPinEinv
extern int _UTL_GetPinHvDr( PinHandle ph, CheckButton *val );
#define UTL_GetPinHvDr _UTL_GetPinHvDr
extern int _UTL_GetPinHvLvDr( PinHandle ph, CheckButton *val );
#define UTL_GetPinHvLvDr _UTL_GetPinHvLvDr
extern int _UTL_GetPinDbmPinPattern(PinHandle pinh, CheckButton *val);
#define UTL_GetPinDbmPinPattern _UTL_GetPinDbmPinPattern
extern int _UTL_GetPinIlNumber( PinHandle ph, RadioButton *val );
#define UTL_GetPinIlNumber _UTL_GetPinIlNumber
extern int _UTL_GetPinInit( PinHandle ph, RadioButton *val );
#define UTL_GetPinInit _UTL_GetPinInit
extern int _UTL_GetPinIoCtrl( PinHandle ph, CheckButton *val );
#define UTL_GetPinIoCtrl _UTL_GetPinIoCtrl
extern int _UTL_GetPinMatchMode( PinHandle ph, RadioButton *val );
#define UTL_GetPinMatchMode _UTL_GetPinMatchMode
extern int _UTL_GetPinMatchGroup( PinHandle ph, RadioButton sel, CheckButton *val );
#define UTL_GetPinMatchGroup _UTL_GetPinMatchGroup
extern int _UTL_GetPinOpen( PinHandle ph, CheckButton *val );
#define UTL_GetPinOpen _UTL_GetPinOpen
extern int _UTL_GetPinPatternInh( PinHandle ph, CheckButton *val );
#define UTL_GetPinPatternInh _UTL_GetPinPatternInh
extern int _UTL_GetPinPatternInhLevel( PinHandle ph, RadioButton *val );
#define UTL_GetPinPatternInhLevel _UTL_GetPinPatternInhLevel
extern int _UTL_GetPinPatternInhPerPin( PinHandle ph, CheckButton *val );
#define UTL_GetPinPatternInhPerPin _UTL_GetPinPatternInhPerPin
extern int _UTL_GetPinDbmPinFix(PinHandle pinh, CheckButton *val);
#define UTL_GetPinDbmPinFix _UTL_GetPinDbmPinFix
extern int _UTL_GetPinPdsSendMode( PinHandle ph , RadioButton *val );
#define UTL_GetPinPdsSendMode _UTL_GetPinPdsSendMode
extern int _UTL_GetPinPl( PinHandle ph, RadioButton *val );
#define UTL_GetPinPl _UTL_GetPinPl
extern int _UTL_GetPinTerm( PinHandle ph, CheckButton *val );
#define UTL_GetPinTerm _UTL_GetPinTerm
extern int _UTL_GetPinViNumber( PinHandle ph, RadioButton *val );
#define UTL_GetPinViNumber _UTL_GetPinViNumber
extern int _UTL_GetPinVihhNumber(PinHandle pinh, RadioButton *val);
#define UTL_GetPinVihhNumber _UTL_GetPinVihhNumber
extern int _UTL_GetPinVihhMutSignal(PinHandle pinh, CheckButton *val);
#define UTL_GetPinVihhMutSignal _UTL_GetPinVihhMutSignal
extern int _UTL_GetPinVoNumber( PinHandle ph, RadioButton *val );
#define UTL_GetPinVoNumber _UTL_GetPinVoNumber
extern int _UTL_GetPinVodNumber( PinHandle ph, RadioButton *val );
#define UTL_GetPinVodNumber _UTL_GetPinVodNumber
extern int _UTL_GetPinVtNumber( PinHandle ph, RadioButton *val );
#define UTL_GetPinVtNumber _UTL_GetPinVtNumber
extern int _UTL_GetPinVloadNumber( PinHandle ph, RadioButton *val );
#define UTL_GetPinVloadNumber _UTL_GetPinVloadNumber
extern int _UTL_GetPinVloadResistor( PinHandle ph, RadioButton *val );
#define UTL_GetPinVloadResistor _UTL_GetPinVloadResistor
extern int _UTL_GetPinBankMultiplex(PinHandle pinh, RadioButton *val);
#define UTL_GetPinBankMultiplex _UTL_GetPinBankMultiplex
extern int _UTL_GetPinBankNumber(PinHandle pinh, RadioButton *val);
#define UTL_GetPinBankNumber _UTL_GetPinBankNumber
extern int _UTL_GetPinCpeDelay( PinHandle ph, RadioButton *val );
#define UTL_GetPinCpeDelay _UTL_GetPinCpeDelay
extern int _UTL_GetPinModeCpeDelay(PinHandle ph, RadioButton mode, RadioButton *val);
#define UTL_GetPinModeCpeDelay _UTL_GetPinModeCpeDelay
extern int _UTL_GetPinCyclePaletteSet(PinHandle pinh, RadioButton *val);
#define UTL_GetPinCyclePaletteSet _UTL_GetPinCyclePaletteSet
extern int _UTL_GetPinDrDelay(PinHandle pinh, RadioButton *val);
#define UTL_GetPinDrDelay _UTL_GetPinDrDelay
extern int _UTL_GetPinModeDrDelay(PinHandle ph, RadioButton mode, RadioButton *val);
#define UTL_GetPinModeDrDelay _UTL_GetPinModeDrDelay
extern int _UTL_GetPinDrPatternLevel(PinHandle pinh, RadioButton *val);
#define UTL_GetPinDrPatternLevel _UTL_GetPinDrPatternLevel
extern int _UTL_GetPinDreDelay(PinHandle pinh, RadioButton *val);
#define UTL_GetPinDreDelay _UTL_GetPinDreDelay
extern int _UTL_GetPinModeDreDelay(PinHandle ph, RadioButton mode, RadioButton *val);
#define UTL_GetPinModeDreDelay _UTL_GetPinModeDreDelay
extern int _UTL_GetPinDrePatternLevel(PinHandle pinh, RadioButton *val);
#define UTL_GetPinDrePatternLevel _UTL_GetPinDrePatternLevel
extern int _UTL_GetPinDssNumber(PinHandle pinh, RadioButton *val);
#define UTL_GetPinDssNumber _UTL_GetPinDssNumber
extern int _UTL_GetPinExpDelay( PinHandle ph, RadioButton *val );
#define UTL_GetPinExpDelay _UTL_GetPinExpDelay
extern int _UTL_GetPinModeExpDelay(PinHandle ph, RadioButton mode, RadioButton *val);
#define UTL_GetPinModeExpDelay _UTL_GetPinModeExpDelay
extern int _UTL_GetPinPatternSwapMode( PinHandle ph, CheckButton *val );
#define UTL_GetPinPatternSwapMode _UTL_GetPinPatternSwapMode
extern int _UTL_GetPinRdsm(PinHandle pinh, CheckButton *val);
#define UTL_GetPinRdsm _UTL_GetPinRdsm
extern int _UTL_GetPinRinv(PinHandle pinh, CheckButton *val);
#define UTL_GetPinRinv _UTL_GetPinRinv
extern int _UTL_GetPinSdm(PinHandle pinh, CheckButton *val);
#define UTL_GetPinSdm _UTL_GetPinSdm
extern int _UTL_GetPinSmc(PinHandle pinh, CheckButton *val);
#define UTL_GetPinSmc _UTL_GetPinSmc
extern int _UTL_GetPinAinv(PinHandle pinh, CheckButton *val);
#define UTL_GetPinAinv _UTL_GetPinAinv
extern PinStrbCursor _UTL_GetPinStrbCursor(PinHandle ph);
#define UTL_GetPinStrbCursor _UTL_GetPinStrbCursor
extern PinStrbHandle _UTL_NextPinStrb(PinStrbCursor csr);
#define UTL_NextPinStrb _UTL_NextPinStrb
extern int _UTL_GetPinStrbNumber( PinStrbHandle strb, RadioButton *val );
#define UTL_GetPinStrbNumber _UTL_GetPinStrbNumber
extern int _UTL_GetPinStrbCpeNumber( PinStrbHandle strb, RadioButton *val );
#define UTL_GetPinStrbCpeNumber _UTL_GetPinStrbCpeNumber
extern int _UTL_GetPinStrbEinv(PinStrbHandle strb, CheckButton *val);
#define UTL_GetPinStrbEinv _UTL_GetPinStrbEinv
extern int _UTL_GetPinStrbExp(PinStrbHandle strb, RadioButton *val);
#define UTL_GetPinStrbExp _UTL_GetPinStrbExp
extern int _UTL_GetPinStrbHz(PinStrbHandle strb, CheckButton *val);
#define UTL_GetPinStrbHz _UTL_GetPinStrbHz
extern int _UTL_GetPinStrbRhz(PinStrbHandle strb, RadioButton *val);
#define UTL_GetPinStrbRhz _UTL_GetPinStrbRhz
extern int _UTL_GetPinStrbBank(PinStrbHandle strb, RadioButton *val);
#define UTL_GetPinStrbBank _UTL_GetPinStrbBank
extern int _UTL_GetPinStrbChannel(PinStrbHandle strb, RadioButton *val);
#define UTL_GetPinStrbChannel _UTL_GetPinStrbChannel
extern int _UTL_GetPinStrbCpeMode(PinStrbHandle strb, RadioButton *val);
#define UTL_GetPinStrbCpeMode _UTL_GetPinStrbCpeMode
extern PinWstrbCursor _UTL_GetPinWstrbCursor(PinHandle ph);
#define UTL_GetPinWstrbCursor _UTL_GetPinWstrbCursor
extern PinWstrbHandle _UTL_NextPinWstrb(PinWstrbCursor csr);
#define UTL_NextPinWstrb _UTL_NextPinWstrb
extern int _UTL_GetPinWstrbNumber( PinWstrbHandle wstrb, RadioButton *val );
#define UTL_GetPinWstrbNumber _UTL_GetPinWstrbNumber
extern int _UTL_GetPinWstrbCpeNumber( PinWstrbHandle wstrb, RadioButton *val );
#define UTL_GetPinWstrbCpeNumber _UTL_GetPinWstrbCpeNumber
extern int _UTL_GetPinWstrbEinv(PinWstrbHandle wstrb, CheckButton *val);
#define UTL_GetPinWstrbEinv _UTL_GetPinWstrbEinv
extern int _UTL_GetPinWstrbExp(PinWstrbHandle wstrb, RadioButton *val);
#define UTL_GetPinWstrbExp _UTL_GetPinWstrbExp
extern int _UTL_GetPinWstrbBank(PinWstrbHandle wstrb, RadioButton *val);
#define UTL_GetPinWstrbBank _UTL_GetPinWstrbBank
extern int _UTL_GetPinWstrbLeadingChannel(PinWstrbHandle wstrb, RadioButton *val);
#define UTL_GetPinWstrbLeadingChannel _UTL_GetPinWstrbLeadingChannel
extern int _UTL_GetPinWstrbTrailingChannel(PinWstrbHandle wstrb, RadioButton *val);
#define UTL_GetPinWstrbTrailingChannel _UTL_GetPinWstrbTrailingChannel
extern int _UTL_GetPinWstrbCpeMode(PinWstrbHandle wstrb, RadioButton *val);
#define UTL_GetPinWstrbCpeMode _UTL_GetPinWstrbCpeMode
extern PinPdsCursor _UTL_GetPinPdsACursor(PinHandle ph);
#define UTL_GetPinPdsACursor _UTL_GetPinPdsACursor
extern PinPdsCursor _UTL_GetPinPdsBCursor(PinHandle ph);
#define UTL_GetPinPdsBCursor _UTL_GetPinPdsBCursor
extern PinPdsCursor _UTL_GetPinPdsDCursor(PinHandle ph);
#define UTL_GetPinPdsDCursor _UTL_GetPinPdsDCursor
extern PinPdsCursor _UTL_GetPinPdsECursor(PinHandle ph);
#define UTL_GetPinPdsECursor _UTL_GetPinPdsECursor
extern PinPdsHandle _UTL_NextPinPds( PinPdsCursor csr );
#define UTL_NextPinPds _UTL_NextPinPds
extern int _UTL_GetPinPdsName( PinPdsHandle pds, RadioButton *val );
#define UTL_GetPinPdsName _UTL_GetPinPdsName
extern int _UTL_GetPinPdsNumber( PinPdsHandle pds, RadioButton *val );
#define UTL_GetPinPdsNumber _UTL_GetPinPdsNumber
extern int _UTL_GetPinCyclePaletteNumber( PinPdsHandle pds, RadioButton *val );
#define UTL_GetPinCyclePaletteNumber _UTL_GetPinCyclePaletteNumber
extern int _UTL_GetPinVsBypassCapacitor( PinHandle ph, CheckButton *val );
#define UTL_GetPinVsBypassCapacitor _UTL_GetPinVsBypassCapacitor
extern int _UTL_GetPinVsBypassCapacitorNumber( PinHandle ph, RadioButton pcon, CheckButton *val );
#define UTL_GetPinVsBypassCapacitorNumber _UTL_GetPinVsBypassCapacitorNumber
extern int _UTL_GetPinVsDisconnect( PinHandle ph, CheckButton *val );
#define UTL_GetPinVsDisconnect _UTL_GetPinVsDisconnect
extern int _UTL_GetPmAccessAllDut( PmAccessHandle h, CheckButton *val );
#define UTL_GetPmAccessAllDut _UTL_GetPmAccessAllDut
extern int _UTL_GetPmAccessDut( PmAccessHandle h, UT_DUT *val );
#define UTL_GetPmAccessDut _UTL_GetPmAccessDut
extern int _UTL_GetPmAccessPresetAllMemory( PmAccessHandle h, CheckButton *val );
#define UTL_GetPmAccessPresetAllMemory _UTL_GetPmAccessPresetAllMemory
extern int _UTL_GetPmAccessStartAddr( PmAccessHandle h, USlider *val );
#define UTL_GetPmAccessStartAddr _UTL_GetPmAccessStartAddr
extern int _UTL_GetPmAccessStopAddr( PmAccessHandle h, USlider *val );
#define UTL_GetPmAccessStopAddr _UTL_GetPmAccessStopAddr
extern int _UTL_GetPmAccessAddrAssign( PmAccessHandle h, RadioButton bit , RadioButton *val );
#define UTL_GetPmAccessAddrAssign _UTL_GetPmAccessAddrAssign
extern int _UTL_GetPmAccessStartXAddr( PmAccessHandle h , USlider *val );
#define UTL_GetPmAccessStartXAddr _UTL_GetPmAccessStartXAddr
extern int _UTL_GetPmAccessEndXAddr( PmAccessHandle h , USlider *val );
#define UTL_GetPmAccessEndXAddr _UTL_GetPmAccessEndXAddr
extern int _UTL_GetPmAccessStartYAddr( PmAccessHandle h , USlider *val );
#define UTL_GetPmAccessStartYAddr _UTL_GetPmAccessStartYAddr
extern int _UTL_GetPmAccessEndYAddr( PmAccessHandle h , USlider *val );
#define UTL_GetPmAccessEndYAddr _UTL_GetPmAccessEndYAddr
extern int _UTL_GetPmAccessStartZAddr( PmAccessHandle h , USlider *val );
#define UTL_GetPmAccessStartZAddr _UTL_GetPmAccessStartZAddr
extern int _UTL_GetPmAccessEndZAddr( PmAccessHandle h , USlider *val );
#define UTL_GetPmAccessEndZAddr _UTL_GetPmAccessEndZAddr
extern int _UTL_GetPmAccessBitBlock ( PmAccessHandle, RadioButton *);
#define UTL_GetPmAccessBitBlock _UTL_GetPmAccessBitBlock
extern int _UTL_GetPmAccessBitMode ( PmAccessHandle, RadioButton *);
#define UTL_GetPmAccessBitMode _UTL_GetPmAccessBitMode
extern int _UTL_GetPmAccessCompactionMode ( PmAccessHandle, RadioButton *);
#define UTL_GetPmAccessCompactionMode _UTL_GetPmAccessCompactionMode
extern int _UTL_GetPmAccessApLink ( PmAccessHandle, RadioButton *);
#define UTL_GetPmAccessApLink _UTL_GetPmAccessApLink
extern int _UTL_GetPmAccessAllBit ( PmAccessHandle, CheckButton *);
#define UTL_GetPmAccessAllBit _UTL_GetPmAccessAllBit
extern PmAccessBitCursor _UTL_GetPmAccessBitCursor( PmAccessHandle );
#define UTL_GetPmAccessBitCursor _UTL_GetPmAccessBitCursor
extern RadioButton _UTL_NextPmAccessBit ( PmAccessBitCursor );
#define UTL_NextPmAccessBit _UTL_NextPmAccessBit
extern void _UTL_UpdatePmConfig ( PmConfigHandle );
#define UTL_UpdatePmConfig _UTL_UpdatePmConfig
extern int _UTL_GetPmConfigAction( PmConfigHandle h, RadioButton *val );
#define UTL_GetPmConfigAction _UTL_GetPmConfigAction
extern int _UTL_GetPmConfigAddrAssign( PmConfigHandle h, RadioButton bit, RadioButton *val );
#define UTL_GetPmConfigAddrAssign _UTL_GetPmConfigAddrAssign
extern int _UTL_GetPmConfigBitSize( PmConfigHandle h, USlider *val );
#define UTL_GetPmConfigBitSize _UTL_GetPmConfigBitSize
extern int _UTL_GetPmConfigFixData( PmConfigHandle h, RadioButton block, USlider *val );
#define UTL_GetPmConfigFixData _UTL_GetPmConfigFixData
extern int _UTL_GetPmConfigRate( PmConfigHandle, RadioButton * );
#define UTL_GetPmConfigRate _UTL_GetPmConfigRate
extern void _UTL_UpdatePowerCtrl(PowerCtrlHandle);
#define UTL_UpdatePowerCtrl _UTL_UpdatePowerCtrl
extern void _UTL_UpdatePowerSeq(PowerSeqHandle);
#define UTL_UpdatePowerSeq _UTL_UpdatePowerSeq
extern PowerUnitCursor _UTL_GetPowerCtrlUnitCursor( PowerCtrlHandle h );
#define UTL_GetPowerCtrlUnitCursor _UTL_GetPowerCtrlUnitCursor
extern int _UTL_GetPowerCtrlWaitTime( PowerCtrlHandle h, DSlider *val );
#define UTL_GetPowerCtrlWaitTime _UTL_GetPowerCtrlWaitTime
extern int _UTL_GetPowerSeqId( PowerSeqHandle h, USlider n, USlider *val );
#define UTL_GetPowerSeqId _UTL_GetPowerSeqId
extern PowerUnitCursor _UTL_GetPowerSeqUnitCursor( PowerSeqHandle h, USlider seq );
#define UTL_GetPowerSeqUnitCursor _UTL_GetPowerSeqUnitCursor
extern RadioButton _UTL_NextPowerUnit( PowerUnitCursor csr );
#define UTL_NextPowerUnit _UTL_NextPowerUnit
extern int _UTL_GetPowerSeqWaitTime( PowerSeqHandle h, USlider seq, DSlider *val );
#define UTL_GetPowerSeqWaitTime _UTL_GetPowerSeqWaitTime
extern int _UTL_GetPowerUnitChannelNumber( RadioButton unit, RadioButton *val );
#define UTL_GetPowerUnitChannelNumber _UTL_GetPowerUnitChannelNumber
extern int _UTL_GetPowerUnitType( RadioButton unit, RadioButton *val );
#define UTL_GetPowerUnitType _UTL_GetPowerUnitType
extern int _UTL_GetRfcmAccessDut( RfcmAccessHandle h, UT_DUT *val );
#define UTL_GetRfcmAccessDut _UTL_GetRfcmAccessDut
extern int _UTL_GetRfcmAccessPresetAllMemory( RfcmAccessHandle h, CheckButton *val );
#define UTL_GetRfcmAccessPresetAllMemory _UTL_GetRfcmAccessPresetAllMemory
extern void _UTL_UpdateRfcmConfig ( RfcmConfigHandle );
#define UTL_UpdateRfcmConfig _UTL_UpdateRfcmConfig
extern int _UTL_GetRfcmConfigAddrAssign( RfcmConfigHandle h, RadioButton bit, RadioButton *val );
#define UTL_GetRfcmConfigAddrAssign _UTL_GetRfcmConfigAddrAssign
extern int _UTL_GetRfcmConfigClearSignal( RfcmConfigHandle h, RadioButton *val );
#define UTL_GetRfcmConfigClearSignal _UTL_GetRfcmConfigClearSignal
extern int _UTL_GetRfcmConfigFccLimit( RfcmConfigHandle h, UT_DUT dut, USlider *val );
#define UTL_GetRfcmConfigFccLimit _UTL_GetRfcmConfigFccLimit
extern int _UTL_GetRfcmConfigMode( RfcmConfigHandle h, RadioButton *val );
#define UTL_GetRfcmConfigMode _UTL_GetRfcmConfigMode
extern int _UTL_GetRfcmConfigRfcsmClearSignal( RfcmConfigHandle h, RadioButton *val );
#define UTL_GetRfcmConfigRfcsmClearSignal _UTL_GetRfcmConfigRfcsmClearSignal
extern int _UTL_GetRfcmConfigRfcsmLimit( RfcmConfigHandle h, UT_DUT dut, USlider *val );
#define UTL_GetRfcmConfigRfcsmLimit _UTL_GetRfcmConfigRfcsmLimit
extern int _UTL_GetRfcmConfigRfcsmTransferMode( RfcmConfigHandle h, RadioButton *val );
#define UTL_GetRfcmConfigRfcsmTransferMode _UTL_GetRfcmConfigRfcsmTransferMode
extern int _UTL_GetRfcmConfigRfcsmTransferSignal( RfcmConfigHandle h, RadioButton *val );
#define UTL_GetRfcmConfigRfcsmTransferSignal _UTL_GetRfcmConfigRfcsmTransferSignal
extern int _UTL_GetRfcmConfigStopAddr( RfcmConfigHandle h, USlider *val );
#define UTL_GetRfcmConfigStopAddr _UTL_GetRfcmConfigStopAddr
extern int _UTL_GetRfcmConfigTransferSignal( RfcmConfigHandle h, RadioButton *val );
#define UTL_GetRfcmConfigTransferSignal _UTL_GetRfcmConfigTransferSignal
extern void _UTL_UpdateTg(TgHandle);
#define UTL_UpdateTg _UTL_UpdateTg
extern int _UTL_GetTgAclk( TgHandle h, RadioButton ts, RadioButton phase, DSlider *val );
#define UTL_GetTgAclk _UTL_GetTgAclk
extern int _UTL_GetTgAclkOff( TgHandle h, RadioButton ts, RadioButton phase, CheckButton *val );
#define UTL_GetTgAclkOff _UTL_GetTgAclkOff
extern int _UTL_GetTgBclk( TgHandle h, RadioButton ts, RadioButton phase, DSlider *val );
#define UTL_GetTgBclk _UTL_GetTgBclk
extern int _UTL_GetTgBclkOff( TgHandle h, RadioButton ts, RadioButton phase, CheckButton *val );
#define UTL_GetTgBclkOff _UTL_GetTgBclkOff
extern int _UTL_GetTgCclk( TgHandle h, RadioButton ts, RadioButton phase, DSlider *val );
#define UTL_GetTgCclk _UTL_GetTgCclk
extern int _UTL_GetTgCclkOff( TgHandle h, RadioButton ts, RadioButton phase, CheckButton *val );
#define UTL_GetTgCclkOff _UTL_GetTgCclkOff
extern int _UTL_GetTgStrbOff( TgHandle h, RadioButton ts, RadioButton phase, CheckButton *val );
#define UTL_GetTgStrbOff _UTL_GetTgStrbOff
extern int _UTL_GetTgDreL( TgHandle h, RadioButton ts, RadioButton phase, DSlider *val );
#define UTL_GetTgDreL _UTL_GetTgDreL
extern int _UTL_GetTgDreLOff( TgHandle h, RadioButton ts, RadioButton phase, CheckButton *val );
#define UTL_GetTgDreLOff _UTL_GetTgDreLOff
extern int _UTL_GetTgDreT( TgHandle h, RadioButton ts, RadioButton phase, DSlider *val );
#define UTL_GetTgDreT _UTL_GetTgDreT
extern int _UTL_GetTgDreTOff( TgHandle h, RadioButton ts, RadioButton phase, CheckButton *val );
#define UTL_GetTgDreTOff _UTL_GetTgDreTOff
extern int _UTL_GetTgPairStrbL( TgHandle h, RadioButton ts, RadioButton phase, DSlider *val );
#define UTL_GetTgPairStrbL _UTL_GetTgPairStrbL
extern int _UTL_GetTgPairStrbT( TgHandle h, RadioButton ts, RadioButton phase, DSlider *val );
#define UTL_GetTgPairStrbT _UTL_GetTgPairStrbT
extern int _UTL_GetTgRate( TgHandle h, RadioButton ts, DSlider *val );
#define UTL_GetTgRate _UTL_GetTgRate
extern int _UTL_GetTgStrb( TgHandle h, RadioButton ts, RadioButton phase, DSlider *val );
#define UTL_GetTgStrb _UTL_GetTgStrb
extern int _UTL_GetTgDrzPulseWidth( TgHandle h, RadioButton phase, DSlider *val );
#define UTL_GetTgDrzPulseWidth _UTL_GetTgDrzPulseWidth
extern int _UTL_GetTgDreLOffset(TgHandle h, RadioButton phase, DSlider *val );
#define UTL_GetTgDreLOffset _UTL_GetTgDreLOffset
extern int _UTL_GetTgDreTOffset(TgHandle h, RadioButton phase, DSlider *val );
#define UTL_GetTgDreTOffset _UTL_GetTgDreTOffset
extern void _UTL_UpdateTgAdjust(TgAdjustHandle );
#define UTL_UpdateTgAdjust _UTL_UpdateTgAdjust
extern int _UTL_GetTgAdjustEachValue(TgAdjustHandle , UT_DUT ,UT_PIN ,RadioButton ,RadioButton ,RadioButton ,DSlider *);
#define UTL_GetTgAdjustEachValue _UTL_GetTgAdjustEachValue
extern void _UTL_UpdateTgBaseRate(TgBaseRateHandle);
#define UTL_UpdateTgBaseRate _UTL_UpdateTgBaseRate
extern int _UTL_GetTgBaseRate(TgBaseRateHandle, DSlider *);
#define UTL_GetTgBaseRate _UTL_GetTgBaseRate
extern void _UTL_UpdateTgFixedDelayEdge( TgFixedDelayEdgeHandle, UT_PIN );
#define UTL_UpdateTgFixedDelayEdge _UTL_UpdateTgFixedDelayEdge
extern int _UTL_GetTgFixedDelayEdgeTargetTs( TgFixedDelayEdgeHandle h, RadioButton ts, CheckButton *val );
#define UTL_GetTgFixedDelayEdgeTargetTs _UTL_GetTgFixedDelayEdgeTargetTs
extern int _UTL_GetTgFixedDelayEdgeValue( TgFixedDelayEdgeHandle h, RadioButton ts, DSlider *val );
#define UTL_GetTgFixedDelayEdgeValue _UTL_GetTgFixedDelayEdgeValue
extern PinCursor _UTL_GetTgFixedDelayEdgeTargetPinCursor( TgFixedDelayEdgeHandle h );
#define UTL_GetTgFixedDelayEdgeTargetPinCursor _UTL_GetTgFixedDelayEdgeTargetPinCursor
extern void _UTL_UpdateLevelHold(LevelHoldHandle);
#define UTL_UpdateLevelHold _UTL_UpdateLevelHold
extern int _UTL_GetLevelHoldInit( LevelHoldHandle h, CheckButton *val );
#define UTL_GetLevelHoldInit _UTL_GetLevelHoldInit
extern void _UTL_UpdateDbmDelay(DbmDelayHandle);
#define UTL_UpdateDbmDelay _UTL_UpdateDbmDelay
extern int _UTL_GetDbmDelayInhibit( DbmDelayHandle h, CheckButton *val );
#define UTL_GetDbmDelayInhibit _UTL_GetDbmDelayInhibit
extern int _UTL_GetCfmAccessAlpgUnit (CfmAccessHandle h, RadioButton * val);
#define UTL_GetCfmAccessAlpgUnit _UTL_GetCfmAccessAlpgUnit
extern int _UTL_GetCfmAccessActionNumber( CfmAccessHandle h, RadioButton idx, RadioButton *num );
#define UTL_GetCfmAccessActionNumber _UTL_GetCfmAccessActionNumber
extern int _UTL_GetCfmAccessBitMode (CfmAccessHandle h, RadioButton * val);
#define UTL_GetCfmAccessBitMode _UTL_GetCfmAccessBitMode
extern int _UTL_GetCfmAccessAllBit (CfmAccessHandle h, CheckButton * val);
#define UTL_GetCfmAccessAllBit _UTL_GetCfmAccessAllBit
extern int _UTL_GetCfmAccessBitBlock (CfmAccessHandle h, RadioButton * val);
#define UTL_GetCfmAccessBitBlock _UTL_GetCfmAccessBitBlock
extern int _UTL_GetCfmAccessPresetAllMemory (CfmAccessHandle h, CheckButton * val);
#define UTL_GetCfmAccessPresetAllMemory _UTL_GetCfmAccessPresetAllMemory
extern int _UTL_GetCfmAccessAddrAssign (CfmAccessHandle h, RadioButton bit, RadioButton * val);
#define UTL_GetCfmAccessAddrAssign _UTL_GetCfmAccessAddrAssign
extern int _UTL_GetCfmAccessApLink (CfmAccessHandle h, RadioButton * val);
#define UTL_GetCfmAccessApLink _UTL_GetCfmAccessApLink
extern int _UTL_GetCfmAccessStartXAddr (CfmAccessHandle h, USlider * val);
#define UTL_GetCfmAccessStartXAddr _UTL_GetCfmAccessStartXAddr
extern int _UTL_GetCfmAccessEndXAddr (CfmAccessHandle h, USlider * val);
#define UTL_GetCfmAccessEndXAddr _UTL_GetCfmAccessEndXAddr
extern int _UTL_GetCfmAccessStartYAddr (CfmAccessHandle h, USlider * val);
#define UTL_GetCfmAccessStartYAddr _UTL_GetCfmAccessStartYAddr
extern int _UTL_GetCfmAccessEndYAddr (CfmAccessHandle h, USlider * val);
#define UTL_GetCfmAccessEndYAddr _UTL_GetCfmAccessEndYAddr
extern int _UTL_GetCfmAccessStartZAddr (CfmAccessHandle h, USlider * val);
#define UTL_GetCfmAccessStartZAddr _UTL_GetCfmAccessStartZAddr
extern int _UTL_GetCfmAccessEndZAddr (CfmAccessHandle h, USlider * val);
#define UTL_GetCfmAccessEndZAddr _UTL_GetCfmAccessEndZAddr
extern int _UTL_GetCfmAccessAllDut (CfmAccessHandle h, CheckButton * val);
#define UTL_GetCfmAccessAllDut _UTL_GetCfmAccessAllDut
extern int _UTL_GetCfmAccessDut (CfmAccessHandle h, UT_DUT * val);
#define UTL_GetCfmAccessDut _UTL_GetCfmAccessDut
extern CfmAccessBitCursor _UTL_GetCfmAccessBitCursor (CfmAccessHandle h);
#define UTL_GetCfmAccessBitCursor _UTL_GetCfmAccessBitCursor
extern RadioButton _UTL_NextCfmAccessBit (CfmAccessBitCursor csr);
#define UTL_NextCfmAccessBit _UTL_NextCfmAccessBit
 extern void _UTL_UpdateCfmConfig ( CfmConfigHandle );
#define UTL_UpdateCfmConfig _UTL_UpdateCfmConfig
extern int _UTL_GetCfmConfigAddrAssign (CfmConfigHandle h, RadioButton bit, RadioButton * val);
#define UTL_GetCfmConfigAddrAssign _UTL_GetCfmConfigAddrAssign
extern int _UTL_GetCfmConfigAddrAssignByAlpg (CfmConfigHandle h, RadioButton alpg, RadioButton bit, RadioButton * val);
#define UTL_GetCfmConfigAddrAssignByAlpg _UTL_GetCfmConfigAddrAssignByAlpg
extern void _UTL_UpdateLevelFix(LevelFixHandle, UT_PIN, UT_DUT);
#define UTL_UpdateLevelFix _UTL_UpdateLevelFix
extern int _UTL_GetLevelFixOutputLevel( LevelFixHandle h, RadioButton wave, RadioButton *val );
#define UTL_GetLevelFixOutputLevel _UTL_GetLevelFixOutputLevel
extern void _UTL_UpdateRteMask(RteMaskHandle);
#define UTL_UpdateRteMask _UTL_UpdateRteMask
extern int _UTL_GetRteMaskDcGuardAlarm( RteMaskHandle hdl, CheckButton *val );
#define UTL_GetRteMaskDcGuardAlarm _UTL_GetRteMaskDcGuardAlarm
extern int _UTL_GetRteMaskPpsGuardAlarm( RteMaskHandle hdl, CheckButton *val );
#define UTL_GetRteMaskPpsGuardAlarm _UTL_GetRteMaskPpsGuardAlarm
extern int _UTL_GetRteMaskPpsKelvinAlarm( RteMaskHandle hdl, CheckButton *val );
#define UTL_GetRteMaskPpsKelvinAlarm _UTL_GetRteMaskPpsKelvinAlarm
extern int _UTL_GetRteMaskLimiterFail( RteMaskHandle hdl, CheckButton *val );
#define UTL_GetRteMaskLimiterFail _UTL_GetRteMaskLimiterFail
 extern MemoryModulePurposeCursor _UTL_GetMemoryModulePurposeCursor( MemoryModuleHandle h );
#define UTL_GetMemoryModulePurposeCursor _UTL_GetMemoryModulePurposeCursor
 extern RadioButton _UTL_NextMemoryModulePurpose( MemoryModulePurposeCursor csr );
#define UTL_NextMemoryModulePurpose _UTL_NextMemoryModulePurpose
 extern USlider _UTL_GetMemoryModulePurposeCount( MemoryModuleHandle h, RadioButton purpose );
#define UTL_GetMemoryModulePurposeCount _UTL_GetMemoryModulePurposeCount
 extern void _UTL_UpdateMemoryModule( MemoryModuleHandle h );
#define UTL_UpdateMemoryModule _UTL_UpdateMemoryModule
extern int _UTL_GetFailSelPinTarget( FailSelPinHandle h, RadioButton *target );
#define UTL_GetFailSelPinTarget _UTL_GetFailSelPinTarget
extern PinCursor _UTL_GetFailSelPinAssignCursor( FailSelPinHandle h, RadioButton bit );
#define UTL_GetFailSelPinAssignCursor _UTL_GetFailSelPinAssignCursor
extern int _UTL_GetFailSelPin( FailSelPinHandle h, RadioButton pin, CheckButton *onoff );
#define UTL_GetFailSelPin _UTL_GetFailSelPin
extern void _UTL_UpdateFailSelPin( FailSelPinHandle );
#define UTL_UpdateFailSelPin _UTL_UpdateFailSelPin
extern void _UTL_UpdateIodMode ( IodModeHandle , UT_PIN , UT_DUT );
#define UTL_UpdateIodMode _UTL_UpdateIodMode
extern int _UTL_GetIodMode(IodModeHandle h, CheckButton *val);
#define UTL_GetIodMode _UTL_GetIodMode
extern int _UTL_GetIodModeAuto(IodModeHandle h, CheckButton *val);
#define UTL_GetIodModeAuto _UTL_GetIodModeAuto
extern int _UTL_GetIodModeCalcFunc(IodModeHandle h, void **val);
#define UTL_GetIodModeCalcFunc _UTL_GetIodModeCalcFunc
extern int _UTL_GetIodModeCalcFuncAndLibrary(IodModeHandle h, char **val1, char **val2);
#define UTL_GetIodModeCalcFuncAndLibrary _UTL_GetIodModeCalcFuncAndLibrary
extern PinCursor _UTL_GetIodModePinCursor(IodModeHandle h);
#define UTL_GetIodModePinCursor _UTL_GetIodModePinCursor
extern void _UTL_UpdateIod ( IodHandle , UT_PIN , UT_DUT );
#define UTL_UpdateIod _UTL_UpdateIod
extern int _UTL_GetIodHigh(IodHandle h, DSlider *val);
#define UTL_GetIodHigh _UTL_GetIodHigh
extern int _UTL_GetIodLow(IodHandle h, DSlider *val);
#define UTL_GetIodLow _UTL_GetIodLow
extern PinCursor _UTL_GetIodPinCursor (IodHandle h);
#define UTL_GetIodPinCursor _UTL_GetIodPinCursor
extern DutCursor _UTL_GetIodDutCursor (IodHandle h);
#define UTL_GetIodDutCursor _UTL_GetIodDutCursor
extern void _UTL_UpdateSdc( SdcHandle );
#define UTL_UpdateSdc _UTL_UpdateSdc
extern int _UTL_GetSdcSourceHigh( SdcHandle , DSlider * );
#define UTL_GetSdcSourceHigh _UTL_GetSdcSourceHigh
extern int _UTL_GetSdcSourceLow( SdcHandle , DSlider * );
#define UTL_GetSdcSourceLow _UTL_GetSdcSourceLow
extern int _UTL_GetSdcComparisonHigh( SdcHandle , DSlider * );
#define UTL_GetSdcComparisonHigh _UTL_GetSdcComparisonHigh
extern int _UTL_GetSdcComparisonLow( SdcHandle , DSlider * );
#define UTL_GetSdcComparisonLow _UTL_GetSdcComparisonLow
extern int _UTL_GetSdcDctPinList( SdcDctHandle , char ** );
#define UTL_GetSdcDctPinList _UTL_GetSdcDctPinList
extern int _UTL_GetSdcDctMeasPin( SdcDctHandle , RadioButton * );
#define UTL_GetSdcDctMeasPin _UTL_GetSdcDctMeasPin
extern int _UTL_GetSdcDctSourceSelect( SdcDctHandle , RadioButton * );
#define UTL_GetSdcDctSourceSelect _UTL_GetSdcDctSourceSelect
extern int _UTL_GetSdcDctPinDut( SdcDctPinHandle , UT_DUT * );
#define UTL_GetSdcDctPinDut _UTL_GetSdcDctPinDut
extern int _UTL_GetSdcDctPinNumber( SdcDctPinHandle , UT_PIN * );
#define UTL_GetSdcDctPinNumber _UTL_GetSdcDctPinNumber
extern int _UTL_GetSdcDctPinMode( SdcDctPinHandle , RadioButton * );
#define UTL_GetSdcDctPinMode _UTL_GetSdcDctPinMode
 extern void _UTL_UpdateTimingTrainingCondition ( TimingTrainingConditionHandle, RadioButton );
#define UTL_UpdateTimingTrainingCondition _UTL_UpdateTimingTrainingCondition
 extern PinCursor _UTL_GetTimingTrainingConditionTargetPinCursor( TimingTrainingConditionHandle );
#define UTL_GetTimingTrainingConditionTargetPinCursor _UTL_GetTimingTrainingConditionTargetPinCursor
 extern PinCursor _UTL_GetTimingTrainingConditionCheckPinCursor ( TimingTrainingConditionHandle, UT_PIN );
#define UTL_GetTimingTrainingConditionCheckPinCursor _UTL_GetTimingTrainingConditionCheckPinCursor
 extern int _UTL_GetTimingTrainingConditionEdgeSelect ( TimingTrainingConditionHandle, RadioButton * );
#define UTL_GetTimingTrainingConditionEdgeSelect _UTL_GetTimingTrainingConditionEdgeSelect
 extern int _UTL_GetTimingTrainingConditionStartPoint ( TimingTrainingConditionHandle, DSlider * );
#define UTL_GetTimingTrainingConditionStartPoint _UTL_GetTimingTrainingConditionStartPoint
 extern int _UTL_GetTimingTrainingConditionStopPoint ( TimingTrainingConditionHandle, DSlider * );
#define UTL_GetTimingTrainingConditionStopPoint _UTL_GetTimingTrainingConditionStopPoint
 extern int _UTL_GetTimingTrainingConditionShiftValue ( TimingTrainingConditionHandle, DSlider * );
#define UTL_GetTimingTrainingConditionShiftValue _UTL_GetTimingTrainingConditionShiftValue
 extern int _UTL_GetTimingTrainingConditionJudgeLoopCount( TimingTrainingConditionHandle, USlider * );
#define UTL_GetTimingTrainingConditionJudgeLoopCount _UTL_GetTimingTrainingConditionJudgeLoopCount
 extern int _UTL_GetTimingTrainingConditionJudgeLimitLow ( TimingTrainingConditionHandle, USlider * );
#define UTL_GetTimingTrainingConditionJudgeLimitLow _UTL_GetTimingTrainingConditionJudgeLimitLow
 extern int _UTL_GetTimingTrainingConditionJudgeLimitHigh( TimingTrainingConditionHandle, USlider * );
#define UTL_GetTimingTrainingConditionJudgeLimitHigh _UTL_GetTimingTrainingConditionJudgeLimitHigh
 extern int _UTL_GetTimingTrainingConditionJudgeWidth ( TimingTrainingConditionHandle, DSlider * );
#define UTL_GetTimingTrainingConditionJudgeWidth _UTL_GetTimingTrainingConditionJudgeWidth
 extern int _UTL_GetTimingTrainingConditionCalcMode ( TimingTrainingConditionHandle, RadioButton * );
#define UTL_GetTimingTrainingConditionCalcMode _UTL_GetTimingTrainingConditionCalcMode
 extern int _UTL_GetTimingTrainingConditionEdgeRatio ( TimingTrainingConditionHandle, DSlider * );
#define UTL_GetTimingTrainingConditionEdgeRatio _UTL_GetTimingTrainingConditionEdgeRatio
 extern int _UTL_GetTimingTrainingConditionEdgeOffset ( TimingTrainingConditionHandle, DSlider * );
#define UTL_GetTimingTrainingConditionEdgeOffset _UTL_GetTimingTrainingConditionEdgeOffset
 extern void _UTL_UpdateTimingTrainingCtrl ( TimingTrainingCtrlHandle, RadioButton );
#define UTL_UpdateTimingTrainingCtrl _UTL_UpdateTimingTrainingCtrl
 extern int _UTL_GetTimingTrainingCtrlExecuteMode( TimingTrainingCtrlHandle, RadioButton * );
#define UTL_GetTimingTrainingCtrlExecuteMode _UTL_GetTimingTrainingCtrlExecuteMode
extern void _UTL_UpdateJi ( JiHandle );
#define UTL_UpdateJi _UTL_UpdateJi
extern int _UTL_GetJiWaveform( JiHandle h, RadioButton *val );
#define UTL_GetJiWaveform _UTL_GetJiWaveform
extern int _UTL_GetJiFrequency( JiHandle h, DSlider *val );
#define UTL_GetJiFrequency _UTL_GetJiFrequency
extern int _UTL_GetJiAmplitude( JiHandle h, DSlider *val );
#define UTL_GetJiAmplitude _UTL_GetJiAmplitude
extern void _UTL_UpdateJiPin ( JiPinHandle , UT_PIN );
#define UTL_UpdateJiPin _UTL_UpdateJiPin
extern int _UTL_GetJiPinTargetClock( JiPinHandle h, RadioButton *val );
#define UTL_GetJiPinTargetClock _UTL_GetJiPinTargetClock
extern PinCursor _UTL_GetJiPinCursor( JiPinHandle h );
#define UTL_GetJiPinCursor _UTL_GetJiPinCursor
extern void _UTL_UpdateCtConfig ( CtConfigHandle );
#define UTL_UpdateCtConfig _UTL_UpdateCtConfig
extern int _UTL_GetCtConfigMethod( CtConfigHandle h, RadioButton *val );
#define UTL_GetCtConfigMethod _UTL_GetCtConfigMethod
extern int _UTL_GetCtConfigStartPoint( CtConfigHandle h, DSlider *val );
#define UTL_GetCtConfigStartPoint _UTL_GetCtConfigStartPoint
extern void _UTL_UpdateCtPin ( CtPinHandle );
#define UTL_UpdateCtPin _UTL_UpdateCtPin
extern int _UTL_GetCtPinListCount( CtPinHandle h, USlider *val );
#define UTL_GetCtPinListCount _UTL_GetCtPinListCount
extern int _UTL_GetCtPinList( CtPinHandle h, int idx, char **val1, char **val2);
#define UTL_GetCtPinList _UTL_GetCtPinList
extern int _UTL_GetCtPinExecMode( CtPinHandle h, RadioButton *val );
#define UTL_GetCtPinExecMode _UTL_GetCtPinExecMode
extern void _UTL_UpdateCtLog ( CtLogHandle );
#define UTL_UpdateCtLog _UTL_UpdateCtLog
extern int _UTL_GetCtLogWaitTime( CtLogHandle h, DSlider *val );
#define UTL_GetCtLogWaitTime _UTL_GetCtLogWaitTime
extern int _UTL_GetCtLogDecimation( CtLogHandle h, USlider *val );
#define UTL_GetCtLogDecimation _UTL_GetCtLogDecimation
extern int _UTL_GetCtLogEnable( CtLogHandle h, CheckButton *val);
#define UTL_GetCtLogEnable _UTL_GetCtLogEnable
extern void _UTL_UpdateVload( VloadHandle , RadioButton );
#define UTL_UpdateVload _UTL_UpdateVload
extern int _UTL_GetVload( VloadHandle h, DSlider *val );
#define UTL_GetVload _UTL_GetVload
extern void _UTL_UpdateSamplingRate( SamplingRateHandle );
#define UTL_UpdateSamplingRate _UTL_UpdateSamplingRate
extern int _UTL_GetSamplingRate( SamplingRateHandle h, DSlider *val );
#define UTL_GetSamplingRate _UTL_GetSamplingRate
extern void _UTL_UpdateMatchPinGroup ( MatchPinGroupHandle );
#define UTL_UpdateMatchPinGroup _UTL_UpdateMatchPinGroup
extern int _UTL_GetMatchPinGroupSignal( MatchPinGroupHandle h, RadioButton groupno, RadioButton *val );
#define UTL_GetMatchPinGroupSignal _UTL_GetMatchPinGroupSignal
extern void _UTL_UpdateDcComparator( DcComparatorHandle );
#define UTL_UpdateDcComparator _UTL_UpdateDcComparator
extern int _UTL_GetDcComparatorLimitHigh( DcComparatorHandle h, DSlider *val );
#define UTL_GetDcComparatorLimitHigh _UTL_GetDcComparatorLimitHigh
extern int _UTL_GetDcComparatorLimitLow( DcComparatorHandle h, DSlider *val );
#define UTL_GetDcComparatorLimitLow _UTL_GetDcComparatorLimitLow
extern int _UTL_GetDcComparatorReadPinDut( DcComparatorReadPinHandle h, UT_DUT *val );
#define UTL_GetDcComparatorReadPinDut _UTL_GetDcComparatorReadPinDut
extern int _UTL_GetDcComparatorReadPinNumber( DcComparatorReadPinHandle h, UT_PIN *val );
#define UTL_GetDcComparatorReadPinNumber _UTL_GetDcComparatorReadPinNumber
extern int _UTL_GetDcComparatorReadPinMode( DcComparatorReadPinHandle h, RadioButton *val );
#define UTL_GetDcComparatorReadPinMode _UTL_GetDcComparatorReadPinMode
extern void _UTL_UpdateVihhMut ( VihhMutHandle );
#define UTL_UpdateVihhMut _UTL_UpdateVihhMut
extern int _UTL_GetVihhMutSignal( VihhMutHandle h, RadioButton *val );
#define UTL_GetVihhMutSignal _UTL_GetVihhMutSignal
extern void _UTL_UpdateVihhMutStartCtrl ( VihhMutStartCtrlHandle );
#define UTL_UpdateVihhMutStartCtrl _UTL_UpdateVihhMutStartCtrl
extern int _UTL_GetVihhMutStartCtrl( VihhMutStartCtrlHandle h, RadioButton *val );
#define UTL_GetVihhMutStartCtrl _UTL_GetVihhMutStartCtrl
extern void _UTL_UpdateSourceSyncCp( SourceSyncCpHandle, UT_PIN );
#define UTL_UpdateSourceSyncCp _UTL_UpdateSourceSyncCp
extern PinCursor _UTL_GetSourceSyncCpTargetPinCursor( SourceSyncCpHandle h );
#define UTL_GetSourceSyncCpTargetPinCursor _UTL_GetSourceSyncCpTargetPinCursor
extern int _UTL_GetSourceSyncCpMode( SourceSyncCpHandle h, CheckButton *val );
#define UTL_GetSourceSyncCpMode _UTL_GetSourceSyncCpMode
 extern UbmConfigHandle _UTL_GetUbmConfigHandle( void );
#define UTL_GetUbmConfigHandle _UTL_GetUbmConfigHandle
 extern void _UTL_InitializeUbmConfigHandle ( UbmConfigHandle );
#define UTL_InitializeUbmConfigHandle _UTL_InitializeUbmConfigHandle
 extern void _UTL_AddUbmConfigFunctionSelect ( UbmConfigHandle, RadioButton, RadioButton );
#define UTL_AddUbmConfigFunctionSelect _UTL_AddUbmConfigFunctionSelect
 extern void _UTL_ClearUbmConfigFunctionSelect( UbmConfigHandle );
#define UTL_ClearUbmConfigFunctionSelect _UTL_ClearUbmConfigFunctionSelect
 extern void _UTL_SetUbmConfigPin ( UbmConfigHandle, RadioButton, char *);
#define UTL_SetUbmConfigPin _UTL_SetUbmConfigPin
 extern void _UTL_ClearUbmConfigPin ( UbmConfigHandle, RadioButton );
#define UTL_ClearUbmConfigPin _UTL_ClearUbmConfigPin
 extern void _UTL_SetUbmConfigJumpAddr ( UbmConfigHandle, RadioButton, RadioButton, USlider);
#define UTL_SetUbmConfigJumpAddr _UTL_SetUbmConfigJumpAddr
 extern void _UTL_SetUbmConfigJumpCycle ( UbmConfigHandle, RadioButton, RadioButton ,RadioButton );
#define UTL_SetUbmConfigJumpCycle _UTL_SetUbmConfigJumpCycle
 extern void _UTL_ClearUbmConfigJumpAddr ( UbmConfigHandle, RadioButton, RadioButton);
#define UTL_ClearUbmConfigJumpAddr _UTL_ClearUbmConfigJumpAddr
 extern void _UTL_SetUbmConfigPmMode ( UbmConfigHandle, RadioButton);
#define UTL_SetUbmConfigPmMode _UTL_SetUbmConfigPmMode
 extern void _UTL_SetUbmConfigStrbMode ( UbmConfigHandle, RadioButton);
#define UTL_SetUbmConfigStrbMode _UTL_SetUbmConfigStrbMode
 extern void _UTL_AddUbmConfigStrbChannel ( UbmConfigHandle, RadioButton, RadioButton);
#define UTL_AddUbmConfigStrbChannel _UTL_AddUbmConfigStrbChannel
 extern void _UTL_ClearUbmConfigStrbChannel ( UbmConfigHandle );
#define UTL_ClearUbmConfigStrbChannel _UTL_ClearUbmConfigStrbChannel
 extern void _UTL_SetUbmConfigPatternInvEnable( UbmConfigHandle, CheckButton );
#define UTL_SetUbmConfigPatternInvEnable _UTL_SetUbmConfigPatternInvEnable
 extern void _UTL_SetUbmConfigDdrMode ( UbmConfigHandle, CheckButton );
#define UTL_SetUbmConfigDdrMode _UTL_SetUbmConfigDdrMode
 extern void _UTL_SetUbmConfigApAutoIncMode ( UbmConfigHandle, CheckButton );
#define UTL_SetUbmConfigApAutoIncMode _UTL_SetUbmConfigApAutoIncMode
 extern void _UTL_SetUbmConfigApIncCycle ( UbmConfigHandle, RadioButton );
#define UTL_SetUbmConfigApIncCycle _UTL_SetUbmConfigApIncCycle
 extern void _UTL_SetUbmConfigApAllCycleIncMode ( UbmConfigHandle, CheckButton );
#define UTL_SetUbmConfigApAllCycleIncMode _UTL_SetUbmConfigApAllCycleIncMode
 extern void _UTL_SetUbmConfigPinLinkMode ( UbmConfigHandle, RadioButton, RadioButton );
#define UTL_SetUbmConfigPinLinkMode _UTL_SetUbmConfigPinLinkMode
 extern void _UTL_SetUbmConfigCaptureMode ( UbmConfigHandle, RadioButton );
#define UTL_SetUbmConfigCaptureMode _UTL_SetUbmConfigCaptureMode
 extern void _UTL_SetUbmConfigExpDelayMode ( UbmConfigHandle, CheckButton );
#define UTL_SetUbmConfigExpDelayMode _UTL_SetUbmConfigExpDelayMode
 extern void _UTL_SetUbmConfigOverlayCycle ( UbmConfigHandle, RadioButton );
#define UTL_SetUbmConfigOverlayCycle _UTL_SetUbmConfigOverlayCycle
 extern void _UTL_SetUbmConfigTransferCycle( UbmConfigHandle, RadioButton );
#define UTL_SetUbmConfigTransferCycle _UTL_SetUbmConfigTransferCycle
 extern void _UTL_SetUbmConfigTransferSize ( UbmConfigHandle, USlider );
#define UTL_SetUbmConfigTransferSize _UTL_SetUbmConfigTransferSize
 extern void _UTL_SendUbmConfig ( UbmConfigHandle );
#define UTL_SendUbmConfig _UTL_SendUbmConfig
 extern void _UTL_UpdateUbmConfig ( UbmConfigHandle );
#define UTL_UpdateUbmConfig _UTL_UpdateUbmConfig
 extern UbmConfigFunctionSelectCursor _UTL_GetUbmConfigFunctionSelectCursor( UbmConfigHandle );
#define UTL_GetUbmConfigFunctionSelectCursor _UTL_GetUbmConfigFunctionSelectCursor
 extern RadioButton _UTL_NextUbmConfigFunctionSelect ( UbmConfigFunctionSelectCursor );
#define UTL_NextUbmConfigFunctionSelect _UTL_NextUbmConfigFunctionSelect
 extern int _UTL_GetUbmConfigFunctionSelectEnableCycle( UbmConfigHandle, RadioButton, RadioButton *);
#define UTL_GetUbmConfigFunctionSelectEnableCycle _UTL_GetUbmConfigFunctionSelectEnableCycle
 extern int _UTL_GetUbmConfigPin ( UbmConfigHandle, RadioButton, char **);
#define UTL_GetUbmConfigPin _UTL_GetUbmConfigPin
 extern UbmConfigJumpIndexNoCursor _UTL_GetUbmConfigJumpIndexNoCursor( UbmConfigHandle, RadioButton );
#define UTL_GetUbmConfigJumpIndexNoCursor _UTL_GetUbmConfigJumpIndexNoCursor
 extern RadioButton _UTL_NextUbmConfigJumpIndexNo( UbmConfigJumpIndexNoCursor );
#define UTL_NextUbmConfigJumpIndexNo _UTL_NextUbmConfigJumpIndexNo
 extern int _UTL_GetUbmConfigJumpAddr ( UbmConfigHandle, RadioButton, RadioButton, USlider *);
#define UTL_GetUbmConfigJumpAddr _UTL_GetUbmConfigJumpAddr
 extern int _UTL_GetUbmConfigJumpCycle ( UbmConfigHandle, RadioButton, RadioButton, RadioButton *);
#define UTL_GetUbmConfigJumpCycle _UTL_GetUbmConfigJumpCycle
 extern int _UTL_GetUbmConfigPmMode ( UbmConfigHandle, RadioButton *);
#define UTL_GetUbmConfigPmMode _UTL_GetUbmConfigPmMode
 extern int _UTL_GetUbmConfigStrbMode ( UbmConfigHandle, RadioButton *);
#define UTL_GetUbmConfigStrbMode _UTL_GetUbmConfigStrbMode
 extern int _UTL_GetUbmConfigPatternInvEnable ( UbmConfigHandle, CheckButton *);
#define UTL_GetUbmConfigPatternInvEnable _UTL_GetUbmConfigPatternInvEnable
 extern int _UTL_GetUbmConfigDdrMode ( UbmConfigHandle, CheckButton *);
#define UTL_GetUbmConfigDdrMode _UTL_GetUbmConfigDdrMode
 extern UbmConfigAlpgBankCursor _UTL_GetUbmConfigAlpgBankCursor( UbmConfigHandle );
#define UTL_GetUbmConfigAlpgBankCursor _UTL_GetUbmConfigAlpgBankCursor
 extern RadioButton _UTL_NextUbmConfigAlpgBank( UbmConfigAlpgBankCursor );
#define UTL_NextUbmConfigAlpgBank _UTL_NextUbmConfigAlpgBank
 extern UbmConfigStrbChannelCursor _UTL_GetUbmConfigStrbChannelCursor( UbmConfigHandle, RadioButton );
#define UTL_GetUbmConfigStrbChannelCursor _UTL_GetUbmConfigStrbChannelCursor
 extern RadioButton _UTL_NextUbmConfigStrbChannel( UbmConfigStrbChannelCursor );
#define UTL_NextUbmConfigStrbChannel _UTL_NextUbmConfigStrbChannel
 extern int _UTL_GetUbmConfigApAutoIncMode ( UbmConfigHandle, CheckButton * );
#define UTL_GetUbmConfigApAutoIncMode _UTL_GetUbmConfigApAutoIncMode
 extern int _UTL_GetUbmConfigApIncCycle ( UbmConfigHandle, RadioButton * );
#define UTL_GetUbmConfigApIncCycle _UTL_GetUbmConfigApIncCycle
 extern int _UTL_GetUbmConfigApAllCycleIncMode ( UbmConfigHandle, CheckButton * );
#define UTL_GetUbmConfigApAllCycleIncMode _UTL_GetUbmConfigApAllCycleIncMode
 extern int _UTL_GetUbmConfigPinLinkMode ( UbmConfigHandle, RadioButton *, RadioButton * );
#define UTL_GetUbmConfigPinLinkMode _UTL_GetUbmConfigPinLinkMode
 extern int _UTL_GetUbmConfigCaptureMode ( UbmConfigHandle, RadioButton *);
#define UTL_GetUbmConfigCaptureMode _UTL_GetUbmConfigCaptureMode
 extern int _UTL_GetUbmConfigExpDelayMode ( UbmConfigHandle, CheckButton *);
#define UTL_GetUbmConfigExpDelayMode _UTL_GetUbmConfigExpDelayMode
 extern int _UTL_GetUbmConfigOverlayCycle ( UbmConfigHandle, RadioButton *);
#define UTL_GetUbmConfigOverlayCycle _UTL_GetUbmConfigOverlayCycle
 extern int _UTL_GetUbmConfigTransferCycle( UbmConfigHandle, RadioButton *);
#define UTL_GetUbmConfigTransferCycle _UTL_GetUbmConfigTransferCycle
 extern int _UTL_GetUbmConfigTransferSize ( UbmConfigHandle, USlider *);
#define UTL_GetUbmConfigTransferSize _UTL_GetUbmConfigTransferSize
 extern UbmAccessHandle _UTL_GetUbmAccessHandle( void );
#define UTL_GetUbmAccessHandle _UTL_GetUbmAccessHandle
 extern void _UTL_SetUbmAccessDut ( UbmAccessHandle, UT_DUT);
#define UTL_SetUbmAccessDut _UTL_SetUbmAccessDut
 extern void _UTL_SetUbmAccessPin ( UbmAccessHandle, char *);
#define UTL_SetUbmAccessPin _UTL_SetUbmAccessPin
 extern void _UTL_ClearUbmAccessPin ( UbmAccessHandle );
#define UTL_ClearUbmAccessPin _UTL_ClearUbmAccessPin
 extern void _UTL_SetUbmAccessStartAddr ( UbmAccessHandle, USlider);
#define UTL_SetUbmAccessStartAddr _UTL_SetUbmAccessStartAddr
 extern void _UTL_SetUbmAccessStopAddr ( UbmAccessHandle, USlider);
#define UTL_SetUbmAccessStopAddr _UTL_SetUbmAccessStopAddr
 extern void _UTL_SetUbmAccessStrbChannel ( UbmAccessHandle, RadioButton, RadioButton);
#define UTL_SetUbmAccessStrbChannel _UTL_SetUbmAccessStrbChannel
 extern void _UTL_SetUbmAccessDdrMode ( UbmAccessHandle, CheckButton);
#define UTL_SetUbmAccessDdrMode _UTL_SetUbmAccessDdrMode
 extern void _UTL_SetUbmAccessPinBlock ( UbmAccessHandle, RadioButton);
#define UTL_SetUbmAccessPinBlock _UTL_SetUbmAccessPinBlock
 extern void _UTL_SetUbmAccessBitReverse ( UbmAccessHandle, CheckButton);
#define UTL_SetUbmAccessBitReverse _UTL_SetUbmAccessBitReverse
 extern void _UTL_SetUbmAccessWriteMode ( UbmAccessHandle, RadioButton);
#define UTL_SetUbmAccessWriteMode _UTL_SetUbmAccessWriteMode
 extern int _UTL_GetUbmAccessDut ( UbmAccessHandle, UT_DUT *);
#define UTL_GetUbmAccessDut _UTL_GetUbmAccessDut
 extern int _UTL_GetUbmAccessPin ( UbmAccessHandle, char **);
#define UTL_GetUbmAccessPin _UTL_GetUbmAccessPin
 extern int _UTL_GetUbmAccessStartAddr ( UbmAccessHandle, USlider *);
#define UTL_GetUbmAccessStartAddr _UTL_GetUbmAccessStartAddr
 extern int _UTL_GetUbmAccessStopAddr ( UbmAccessHandle, USlider *);
#define UTL_GetUbmAccessStopAddr _UTL_GetUbmAccessStopAddr
 extern int _UTL_GetUbmAccessAlpgBank ( UbmAccessHandle, RadioButton *);
#define UTL_GetUbmAccessAlpgBank _UTL_GetUbmAccessAlpgBank
 extern int _UTL_GetUbmAccessStrbChannel ( UbmAccessHandle, RadioButton *);
#define UTL_GetUbmAccessStrbChannel _UTL_GetUbmAccessStrbChannel
 extern int _UTL_GetUbmAccessDdrMode ( UbmAccessHandle, CheckButton *);
#define UTL_GetUbmAccessDdrMode _UTL_GetUbmAccessDdrMode
 extern int _UTL_GetUbmAccessPinBlock ( UbmAccessHandle, RadioButton *);
#define UTL_GetUbmAccessPinBlock _UTL_GetUbmAccessPinBlock
 extern int _UTL_GetUbmAccessBitReverse ( UbmAccessHandle, CheckButton *);
#define UTL_GetUbmAccessBitReverse _UTL_GetUbmAccessBitReverse
 extern int _UTL_GetUbmAccessWriteMode ( UbmAccessHandle, RadioButton *);
#define UTL_GetUbmAccessWriteMode _UTL_GetUbmAccessWriteMode
 extern void _UTL_ReadUbm ( UbmAccessHandle, void *, USlider);
#define UTL_ReadUbm _UTL_ReadUbm
 extern void _UTL_ReadUbmAllDut ( UbmAccessHandle, UT_DUT, void *, USlider);
#define UTL_ReadUbmAllDut _UTL_ReadUbmAllDut
 extern void _UTL_WriteUbm ( UbmAccessHandle, void *, USlider);
#define UTL_WriteUbm _UTL_WriteUbm
 extern void _UTL_WriteUbmAllDut ( UbmAccessHandle, UT_DUT, void *, USlider);
#define UTL_WriteUbmAllDut _UTL_WriteUbmAllDut
 extern void _UTL_WriteUbmRawData_Lite ( RadioButton , RadioButton , RadioButton , USlider , USlider , void *);
#define UTL_WriteUbmRawData_Lite _UTL_WriteUbmRawData_Lite
 extern void _UTL_PresetUbm ( UbmConfigHandle, USlider);
#define UTL_PresetUbm _UTL_PresetUbm
extern int _UTL_WriteAlpgCtrlReg(RadioButton, USlider);
#define UTL_WriteAlpgCtrlReg _UTL_WriteAlpgCtrlReg
extern int _UTL_ReadAlpgCtrlReg(RadioButton, USlider *);
#define UTL_ReadAlpgCtrlReg _UTL_ReadAlpgCtrlReg
extern RteMaskHandle _UTL_GetRteMaskHandle(void);
#define UTL_GetRteMaskHandle _UTL_GetRteMaskHandle
extern void _UTL_InitializeRteMaskHandle(RteMaskHandle);
#define UTL_InitializeRteMaskHandle _UTL_InitializeRteMaskHandle
extern void _UTL_SetRteMaskDcGuardAlarm(RteMaskHandle, CheckButton);
#define UTL_SetRteMaskDcGuardAlarm _UTL_SetRteMaskDcGuardAlarm
extern void _UTL_SetRteMaskPpsGuardAlarm(RteMaskHandle, CheckButton);
#define UTL_SetRteMaskPpsGuardAlarm _UTL_SetRteMaskPpsGuardAlarm
extern void _UTL_SetRteMaskPpsKelvinAlarm(RteMaskHandle, CheckButton);
#define UTL_SetRteMaskPpsKelvinAlarm _UTL_SetRteMaskPpsKelvinAlarm
extern void _UTL_SetRteMaskLimiterFail(RteMaskHandle, CheckButton);
#define UTL_SetRteMaskLimiterFail _UTL_SetRteMaskLimiterFail
extern void _UTL_SendRteMask(RteMaskHandle);
#define UTL_SendRteMask _UTL_SendRteMask
extern SdcHandle _UTL_GetSdcHandle( void );
#define UTL_GetSdcHandle _UTL_GetSdcHandle
extern void _UTL_SetSdcSourceHigh( SdcHandle , DSlider );
#define UTL_SetSdcSourceHigh _UTL_SetSdcSourceHigh
extern void _UTL_SetSdcSourceLow( SdcHandle , DSlider );
#define UTL_SetSdcSourceLow _UTL_SetSdcSourceLow
extern void _UTL_SetSdcComparisonHigh( SdcHandle , DSlider );
#define UTL_SetSdcComparisonHigh _UTL_SetSdcComparisonHigh
extern void _UTL_SetSdcComparisonLow( SdcHandle , DSlider );
#define UTL_SetSdcComparisonLow _UTL_SetSdcComparisonLow
extern void _UTL_SendSdc( SdcHandle );
#define UTL_SendSdc _UTL_SendSdc
extern SdcDctHandle _UTL_GetSdcDctHandle( void );
#define UTL_GetSdcDctHandle _UTL_GetSdcDctHandle
extern void _UTL_SetSdcDctPinList( SdcDctHandle , char * );
#define UTL_SetSdcDctPinList _UTL_SetSdcDctPinList
extern void _UTL_SetSdcDctMeasPin( SdcDctHandle , RadioButton );
#define UTL_SetSdcDctMeasPin _UTL_SetSdcDctMeasPin
extern void _UTL_SetSdcDctSourceSelect( SdcDctHandle , RadioButton );
#define UTL_SetSdcDctSourceSelect _UTL_SetSdcDctSourceSelect
extern void _UTL_MeasSdcDct( SdcDctHandle );
#define UTL_MeasSdcDct _UTL_MeasSdcDct
extern SdcDctPinHandle _UTL_GetSdcDctPinHandle( void );
#define UTL_GetSdcDctPinHandle _UTL_GetSdcDctPinHandle
extern void _UTL_SetSdcDctPinDut( SdcDctPinHandle , UT_DUT );
#define UTL_SetSdcDctPinDut _UTL_SetSdcDctPinDut
extern void _UTL_SetSdcDctPinNumber( SdcDctPinHandle , UT_PIN );
#define UTL_SetSdcDctPinNumber _UTL_SetSdcDctPinNumber
extern void _UTL_SetSdcDctPinMode( SdcDctPinHandle , RadioButton );
#define UTL_SetSdcDctPinMode _UTL_SetSdcDctPinMode
extern CheckButton _UTL_ReadSdcDctPin ( SdcDctPinHandle );
#define UTL_ReadSdcDctPin _UTL_ReadSdcDctPin
extern DqsLookupTableHandle _UTL_GetDqsLookupTableHandle(void);
#define UTL_GetDqsLookupTableHandle _UTL_GetDqsLookupTableHandle
extern void _UTL_SetDqsLookupTableMode(DqsLookupTableHandle, RadioButton);
#define UTL_SetDqsLookupTableMode _UTL_SetDqsLookupTableMode
extern void _UTL_SetDqsLookupTableDqsPin(DqsLookupTableHandle, char *);
#define UTL_SetDqsLookupTableDqsPin _UTL_SetDqsLookupTableDqsPin
extern void _UTL_SetDqsLookupTableDqPin(DqsLookupTableHandle, char *);
#define UTL_SetDqsLookupTableDqPin _UTL_SetDqsLookupTableDqPin
extern void _UTL_AddDqsLookupTableCapture(DqsLookupTableHandle, RadioButton);
#define UTL_AddDqsLookupTableCapture _UTL_AddDqsLookupTableCapture
extern void _UTL_ClearDqsLookupTableCapture(DqsLookupTableHandle);
#define UTL_ClearDqsLookupTableCapture _UTL_ClearDqsLookupTableCapture
extern void _UTL_InitDqsLookupTableDqsCombination(DqsLookupTableHandle, RadioButton);
#define UTL_InitDqsLookupTableDqsCombination _UTL_InitDqsLookupTableDqsCombination
extern void _UTL_SetDqsLookupTableDqsCombination(DqsLookupTableHandle, RadioButton, RadioButton, RadioButton);
#define UTL_SetDqsLookupTableDqsCombination _UTL_SetDqsLookupTableDqsCombination
extern void _UTL_InitDqsLookupTableDqCombination(DqsLookupTableHandle, RadioButton);
#define UTL_InitDqsLookupTableDqCombination _UTL_InitDqsLookupTableDqCombination
extern void _UTL_SetDqsLookupTableDqCombination(DqsLookupTableHandle, RadioButton, RadioButton, RadioButton);
#define UTL_SetDqsLookupTableDqCombination _UTL_SetDqsLookupTableDqCombination
extern void _UTL_InitDqsLookupTableCycleCombination(DqsLookupTableHandle, RadioButton);
#define UTL_InitDqsLookupTableCycleCombination _UTL_InitDqsLookupTableCycleCombination
extern void _UTL_SetDqsLookupTableCycleCombination(DqsLookupTableHandle, RadioButton, RadioButton, RadioButton, RadioButton, RadioButton, RadioButton);
#define UTL_SetDqsLookupTableCycleCombination _UTL_SetDqsLookupTableCycleCombination
extern void _UTL_SendDqsLookupTable(DqsLookupTableHandle);
#define UTL_SendDqsLookupTable _UTL_SendDqsLookupTable
extern DqsSourceSyncHandle _UTL_GetDqsSourceSyncHandle(void);
#define UTL_GetDqsSourceSyncHandle _UTL_GetDqsSourceSyncHandle
extern void _UTL_SetDqsSourceSyncMode(DqsSourceSyncHandle, RadioButton);
#define UTL_SetDqsSourceSyncMode _UTL_SetDqsSourceSyncMode
extern void _UTL_SetDqsSourceSyncDqsPin(DqsSourceSyncHandle, char *);
#define UTL_SetDqsSourceSyncDqsPin _UTL_SetDqsSourceSyncDqsPin
extern void _UTL_SetDqsSourceSyncDqsPinNega(DqsSourceSyncHandle, char *);
#define UTL_SetDqsSourceSyncDqsPinNega _UTL_SetDqsSourceSyncDqsPinNega
extern void _UTL_SetDqsSourceSyncDqPin(DqsSourceSyncHandle, char *);
#define UTL_SetDqsSourceSyncDqPin _UTL_SetDqsSourceSyncDqPin
extern void _UTL_SetDqsSourceSyncDqPinCount (DqsSourceSyncHandle, USlider);
#define UTL_SetDqsSourceSyncDqPinCount _UTL_SetDqsSourceSyncDqPinCount
extern void _UTL_SetDqsSourceSyncReadCycle(DqsSourceSyncHandle, RadioButton);
#define UTL_SetDqsSourceSyncReadCycle _UTL_SetDqsSourceSyncReadCycle
extern void _UTL_SetDqsSourceSyncEnableCycle(DqsSourceSyncHandle, RadioButton);
#define UTL_SetDqsSourceSyncEnableCycle _UTL_SetDqsSourceSyncEnableCycle
extern void _UTL_SetDqsSourceSyncEnableCycleNega(DqsSourceSyncHandle, RadioButton);
#define UTL_SetDqsSourceSyncEnableCycleNega _UTL_SetDqsSourceSyncEnableCycleNega
extern void _UTL_SetDqsSourceSyncDqsPhaseAdjust(DqsSourceSyncHandle, DSlider);
#define UTL_SetDqsSourceSyncDqsPhaseAdjust _UTL_SetDqsSourceSyncDqsPhaseAdjust
 extern void _UTL_SetDqsSourceSyncDqsPhaseAdjustPerPin(DqsSourceSyncHandle, USlider, DSlider *);
#define UTL_SetDqsSourceSyncDqsPhaseAdjustPerPin _UTL_SetDqsSourceSyncDqsPhaseAdjustPerPin
extern void _UTL_SetDqsSourceSyncFirstEdge(DqsSourceSyncHandle, CheckButton, CheckButton);
#define UTL_SetDqsSourceSyncFirstEdge _UTL_SetDqsSourceSyncFirstEdge
extern void _UTL_SetDqsSourceSyncFirstEdgeNega(DqsSourceSyncHandle, CheckButton, CheckButton);
#define UTL_SetDqsSourceSyncFirstEdgeNega _UTL_SetDqsSourceSyncFirstEdgeNega
extern void _UTL_SetDqsSourceSyncFailStopCtrl(DqsSourceSyncHandle, RadioButton, CheckButton);
#define UTL_SetDqsSourceSyncFailStopCtrl _UTL_SetDqsSourceSyncFailStopCtrl
extern void _UTL_SetDqsSourceSyncCounterCtrl(DqsSourceSyncHandle, CheckButton);
#define UTL_SetDqsSourceSyncCounterCtrl _UTL_SetDqsSourceSyncCounterCtrl
extern void _UTL_SetDqsSourceSyncReadEnable (DqsSourceSyncHandle, CheckButton);
#define UTL_SetDqsSourceSyncReadEnable _UTL_SetDqsSourceSyncReadEnable
extern void _UTL_SendDqsSourceSync(DqsSourceSyncHandle);
#define UTL_SendDqsSourceSync _UTL_SendDqsSourceSync
extern void _UTL_WriteDqsSourceSyncPhaseAdjust (USlider , UT_PIN *, DSlider * );
#define UTL_WriteDqsSourceSyncPhaseAdjust _UTL_WriteDqsSourceSyncPhaseAdjust
extern void _UTL_WriteDqsSourceSyncPhaseAdjustByDut (USlider , UT_PIN *, DSlider *, UT_DUT );
#define UTL_WriteDqsSourceSyncPhaseAdjustByDut _UTL_WriteDqsSourceSyncPhaseAdjustByDut
extern DqsStatusHandle _UTL_GetDqsStatusHandle(void);
#define UTL_GetDqsStatusHandle _UTL_GetDqsStatusHandle
extern void _UTL_SetDqsStatusDut(DqsStatusHandle, UT_DUT);
#define UTL_SetDqsStatusDut _UTL_SetDqsStatusDut
extern void _UTL_SetDqsStatusPin(DqsStatusHandle, char *);
#define UTL_SetDqsStatusPin _UTL_SetDqsStatusPin
extern void _UTL_ReadDqsStatus(DqsStatusHandle, USlider *);
#define UTL_ReadDqsStatus _UTL_ReadDqsStatus
extern void _UTL_ReadDqsCounter(DqsStatusHandle, USlider *, USlider *);
#define UTL_ReadDqsCounter _UTL_ReadDqsCounter
extern void _UTL_ResetDqs(RadioButton);
#define UTL_ResetDqs _UTL_ResetDqs
extern PassFailCounterConfigHandle _UTL_GetPassFailCounterConfigHandle( void );
#define UTL_GetPassFailCounterConfigHandle _UTL_GetPassFailCounterConfigHandle
extern void _UTL_SetPassFailCounterConfigMode ( PassFailCounterConfigHandle, RadioButton );
#define UTL_SetPassFailCounterConfigMode _UTL_SetPassFailCounterConfigMode
extern void _UTL_SetPassFailCounterConfigPin ( PassFailCounterConfigHandle, char * );
#define UTL_SetPassFailCounterConfigPin _UTL_SetPassFailCounterConfigPin
extern void _UTL_SetPassFailCounterConfigStrbMode ( PassFailCounterConfigHandle, RadioButton );
#define UTL_SetPassFailCounterConfigStrbMode _UTL_SetPassFailCounterConfigStrbMode
extern void _UTL_AddPassFailCounterConfigStrbChannel ( PassFailCounterConfigHandle, RadioButton, RadioButton );
#define UTL_AddPassFailCounterConfigStrbChannel _UTL_AddPassFailCounterConfigStrbChannel
extern void _UTL_ClearPassFailCounterConfigStrbChannel ( PassFailCounterConfigHandle );
#define UTL_ClearPassFailCounterConfigStrbChannel _UTL_ClearPassFailCounterConfigStrbChannel
extern void _UTL_SetPassFailCounterConfigCountUpTableSelect ( PassFailCounterConfigHandle, CheckButton );
#define UTL_SetPassFailCounterConfigCountUpTableSelect _UTL_SetPassFailCounterConfigCountUpTableSelect
extern void _UTL_SetPassFailCounterConfigLimit ( PassFailCounterConfigHandle, RadioButton, RadioButton, USlider );
#define UTL_SetPassFailCounterConfigLimit _UTL_SetPassFailCounterConfigLimit
extern void _UTL_SendPassFailCounterConfig ( PassFailCounterConfigHandle );
#define UTL_SendPassFailCounterConfig _UTL_SendPassFailCounterConfig
extern PassFailCounterAccessHandle _UTL_GetPassFailCounterAccessHandle ( void );
#define UTL_GetPassFailCounterAccessHandle _UTL_GetPassFailCounterAccessHandle
extern void _UTL_SetPassFailCounterAccessAllCounter ( PassFailCounterAccessHandle, CheckButton );
#define UTL_SetPassFailCounterAccessAllCounter _UTL_SetPassFailCounterAccessAllCounter
extern void _UTL_SetPassFailCounterAccessCounter ( PassFailCounterAccessHandle, RadioButton );
#define UTL_SetPassFailCounterAccessCounter _UTL_SetPassFailCounterAccessCounter
extern void _UTL_SetPassFailCounterAccessAllDut ( PassFailCounterAccessHandle, CheckButton );
#define UTL_SetPassFailCounterAccessAllDut _UTL_SetPassFailCounterAccessAllDut
extern void _UTL_SetPassFailCounterAccessDut ( PassFailCounterAccessHandle, UT_DUT );
#define UTL_SetPassFailCounterAccessDut _UTL_SetPassFailCounterAccessDut
extern void _UTL_SetPassFailCounterAccessAllPin ( PassFailCounterAccessHandle, CheckButton );
#define UTL_SetPassFailCounterAccessAllPin _UTL_SetPassFailCounterAccessAllPin
extern void _UTL_SetPassFailCounterAccessPin ( PassFailCounterAccessHandle, UT_PIN );
#define UTL_SetPassFailCounterAccessPin _UTL_SetPassFailCounterAccessPin
extern void _UTL_UpdatePassFailCounter ( PassFailCounterAccessHandle );
#define UTL_UpdatePassFailCounter _UTL_UpdatePassFailCounter
extern USlider _UTL_GetPassFailCounterValue ( PassFailCounterAccessHandle, RadioButton * );
#define UTL_GetPassFailCounterValue _UTL_GetPassFailCounterValue
 extern TimingTrainingConditionHandle _UTL_GetTimingTrainingConditionHandle( void );
#define UTL_GetTimingTrainingConditionHandle _UTL_GetTimingTrainingConditionHandle
 extern void _UTL_AddTimingTrainingConditionPin ( TimingTrainingConditionHandle, UT_PIN, UT_PIN );
#define UTL_AddTimingTrainingConditionPin _UTL_AddTimingTrainingConditionPin
 extern void _UTL_ClearTimingTrainingConditionPin ( TimingTrainingConditionHandle );
#define UTL_ClearTimingTrainingConditionPin _UTL_ClearTimingTrainingConditionPin
 extern void _UTL_SetTimingTrainingConditionEdgeSelect ( TimingTrainingConditionHandle, RadioButton );
#define UTL_SetTimingTrainingConditionEdgeSelect _UTL_SetTimingTrainingConditionEdgeSelect
 extern void _UTL_SetTimingTrainingConditionStartPoint ( TimingTrainingConditionHandle, DSlider );
#define UTL_SetTimingTrainingConditionStartPoint _UTL_SetTimingTrainingConditionStartPoint
 extern void _UTL_SetTimingTrainingConditionStopPoint ( TimingTrainingConditionHandle, DSlider );
#define UTL_SetTimingTrainingConditionStopPoint _UTL_SetTimingTrainingConditionStopPoint
 extern void _UTL_SetTimingTrainingConditionShiftValue ( TimingTrainingConditionHandle, DSlider );
#define UTL_SetTimingTrainingConditionShiftValue _UTL_SetTimingTrainingConditionShiftValue
 extern void _UTL_SetTimingTrainingConditionJudgeLoopCount( TimingTrainingConditionHandle, USlider );
#define UTL_SetTimingTrainingConditionJudgeLoopCount _UTL_SetTimingTrainingConditionJudgeLoopCount
 extern void _UTL_SetTimingTrainingConditionJudgeLimit ( TimingTrainingConditionHandle, USlider, USlider );
#define UTL_SetTimingTrainingConditionJudgeLimit _UTL_SetTimingTrainingConditionJudgeLimit
 extern void _UTL_SetTimingTrainingConditionJudgeWidth ( TimingTrainingConditionHandle, DSlider );
#define UTL_SetTimingTrainingConditionJudgeWidth _UTL_SetTimingTrainingConditionJudgeWidth
 extern void _UTL_SetTimingTrainingConditionCalcMode ( TimingTrainingConditionHandle, RadioButton );
#define UTL_SetTimingTrainingConditionCalcMode _UTL_SetTimingTrainingConditionCalcMode
 extern void _UTL_SetTimingTrainingConditionEdgeRatio ( TimingTrainingConditionHandle, DSlider );
#define UTL_SetTimingTrainingConditionEdgeRatio _UTL_SetTimingTrainingConditionEdgeRatio
 extern void _UTL_SetTimingTrainingConditionEdgeOffset ( TimingTrainingConditionHandle, DSlider );
#define UTL_SetTimingTrainingConditionEdgeOffset _UTL_SetTimingTrainingConditionEdgeOffset
 extern void _UTL_SendTimingTrainingCondition ( TimingTrainingConditionHandle, RadioButton );
#define UTL_SendTimingTrainingCondition _UTL_SendTimingTrainingCondition
 extern TimingTrainingCtrlHandle _UTL_GetTimingTrainingCtrlHandle( void );
#define UTL_GetTimingTrainingCtrlHandle _UTL_GetTimingTrainingCtrlHandle
 extern void _UTL_SetTimingTrainingCtrlExecuteMode( TimingTrainingCtrlHandle, RadioButton );
#define UTL_SetTimingTrainingCtrlExecuteMode _UTL_SetTimingTrainingCtrlExecuteMode
 extern void _UTL_SendTimingTrainingCtrl ( TimingTrainingCtrlHandle, RadioButton );
#define UTL_SendTimingTrainingCtrl _UTL_SendTimingTrainingCtrl
 extern TimingTrainingPinHandle _UTL_GetTimingTrainingPinHandle( void );
#define UTL_GetTimingTrainingPinHandle _UTL_GetTimingTrainingPinHandle
 extern void _UTL_UpdateTimingTrainingPin ( TimingTrainingPinHandle, RadioButton );
#define UTL_UpdateTimingTrainingPin _UTL_UpdateTimingTrainingPin
 extern int _UTL_GetTimingTrainingPinTargetPinStatus ( TimingTrainingPinHandle, UT_DUT, UT_PIN, int * );
#define UTL_GetTimingTrainingPinTargetPinStatus _UTL_GetTimingTrainingPinTargetPinStatus
 extern int _UTL_GetTimingTrainingPinTargetPinFailToPassMax( TimingTrainingPinHandle, UT_DUT, UT_PIN, DSlider * );
#define UTL_GetTimingTrainingPinTargetPinFailToPassMax _UTL_GetTimingTrainingPinTargetPinFailToPassMax
 extern int _UTL_GetTimingTrainingPinTargetPinPassToFailMin( TimingTrainingPinHandle, UT_DUT, UT_PIN, DSlider * );
#define UTL_GetTimingTrainingPinTargetPinPassToFailMin _UTL_GetTimingTrainingPinTargetPinPassToFailMin
 extern int _UTL_GetTimingTrainingPinTargetPinAdjustValueByDut( TimingTrainingPinHandle, UT_DUT, UT_PIN, DSlider * );
#define UTL_GetTimingTrainingPinTargetPinAdjustValueByDut _UTL_GetTimingTrainingPinTargetPinAdjustValueByDut
 extern int _UTL_GetTimingTrainingPinCheckPinStatus ( TimingTrainingPinHandle, UT_DUT, UT_PIN, int * );
#define UTL_GetTimingTrainingPinCheckPinStatus _UTL_GetTimingTrainingPinCheckPinStatus
 extern int _UTL_GetTimingTrainingPinCheckPinFailToPass ( TimingTrainingPinHandle, UT_DUT, UT_PIN, DSlider * );
#define UTL_GetTimingTrainingPinCheckPinFailToPass _UTL_GetTimingTrainingPinCheckPinFailToPass
 extern int _UTL_GetTimingTrainingPinCheckPinPassToFail ( TimingTrainingPinHandle, UT_DUT, UT_PIN, DSlider * );
#define UTL_GetTimingTrainingPinCheckPinPassToFail _UTL_GetTimingTrainingPinCheckPinPassToFail
 extern int _UTL_GetTimingTrainingPinEdgeCount ( TimingTrainingPinHandle, USlider * );
#define UTL_GetTimingTrainingPinEdgeCount _UTL_GetTimingTrainingPinEdgeCount
 extern int _UTL_GetTimingTrainingPinCheckPinFailCount ( TimingTrainingPinHandle, UT_DUT, UT_PIN, USlider, USlider * );
#define UTL_GetTimingTrainingPinCheckPinFailCount _UTL_GetTimingTrainingPinCheckPinFailCount
 extern int _UTL_GetTimingTrainingPinIsLatestFailCount ( TimingTrainingPinHandle, CheckButton * );
#define UTL_GetTimingTrainingPinIsLatestFailCount _UTL_GetTimingTrainingPinIsLatestFailCount
extern JiHandle _UTL_GetJiHandle( void );
#define UTL_GetJiHandle _UTL_GetJiHandle
extern void _UTL_SetJiWaveform ( JiHandle , RadioButton );
#define UTL_SetJiWaveform _UTL_SetJiWaveform
extern void _UTL_SetJiFrequency ( JiHandle , DSlider );
#define UTL_SetJiFrequency _UTL_SetJiFrequency
extern void _UTL_SetJiAmplitude ( JiHandle , DSlider );
#define UTL_SetJiAmplitude _UTL_SetJiAmplitude
extern void _UTL_SendJi ( JiHandle );
#define UTL_SendJi _UTL_SendJi
extern JiPinHandle _UTL_GetJiPinHandle( void );
#define UTL_GetJiPinHandle _UTL_GetJiPinHandle
extern void _UTL_ClearJiPinNumber ( JiPinHandle );
#define UTL_ClearJiPinNumber _UTL_ClearJiPinNumber
extern void _UTL_AddJiPinNumber ( JiPinHandle , UT_PIN );
#define UTL_AddJiPinNumber _UTL_AddJiPinNumber
extern void _UTL_SetJiPinTargetClock ( JiPinHandle , RadioButton );
#define UTL_SetJiPinTargetClock _UTL_SetJiPinTargetClock
extern void _UTL_SendJiPin ( JiPinHandle );
#define UTL_SendJiPin _UTL_SendJiPin
extern JiStatusHandle _UTL_GetJiStatusHandle( void );
#define UTL_GetJiStatusHandle _UTL_GetJiStatusHandle
extern CheckButton _UTL_ReadJiStatusClamp( JiStatusHandle );
#define UTL_ReadJiStatusClamp _UTL_ReadJiStatusClamp
extern CtConfigHandle _UTL_GetCtConfigHandle ( void );
#define UTL_GetCtConfigHandle _UTL_GetCtConfigHandle
extern void _UTL_SetCtConfigMethod ( CtConfigHandle , RadioButton );
#define UTL_SetCtConfigMethod _UTL_SetCtConfigMethod
extern void _UTL_SetCtConfigStartPoint ( CtConfigHandle , DSlider );
#define UTL_SetCtConfigStartPoint _UTL_SetCtConfigStartPoint
extern void _UTL_SendCtConfig ( CtConfigHandle );
#define UTL_SendCtConfig _UTL_SendCtConfig
extern CtPinHandle _UTL_GetCtPinHandle ( void );
#define UTL_GetCtPinHandle _UTL_GetCtPinHandle
extern int _UTL_AddCtPinList ( CtPinHandle , char * , char * );
#define UTL_AddCtPinList _UTL_AddCtPinList
extern void _UTL_ClearCtPinList ( CtPinHandle );
#define UTL_ClearCtPinList _UTL_ClearCtPinList
extern void _UTL_SetCtPinExecMode ( CtPinHandle , RadioButton );
#define UTL_SetCtPinExecMode _UTL_SetCtPinExecMode
extern void _UTL_SendCtPin ( CtPinHandle );
#define UTL_SendCtPin _UTL_SendCtPin
extern CtLogHandle _UTL_GetCtLogHandle ( void );
#define UTL_GetCtLogHandle _UTL_GetCtLogHandle
extern void _UTL_SetCtLogWaitTime ( CtLogHandle , DSlider );
#define UTL_SetCtLogWaitTime _UTL_SetCtLogWaitTime
extern void _UTL_SetCtLogDecimation ( CtLogHandle , USlider );
#define UTL_SetCtLogDecimation _UTL_SetCtLogDecimation
extern void _UTL_SetCtLogEnable ( CtLogHandle , CheckButton );
#define UTL_SetCtLogEnable _UTL_SetCtLogEnable
extern void _UTL_SendCtLog ( CtLogHandle );
#define UTL_SendCtLog _UTL_SendCtLog
extern CheckButton _UTL_ReadCtStatusClamp ( UT_PIN , UT_DUT );
#define UTL_ReadCtStatusClamp _UTL_ReadCtStatusClamp
extern void _UTL_ReadCtStatusLogData ( UT_PIN , UT_DUT , DSlider * , USlider );
#define UTL_ReadCtStatusLogData _UTL_ReadCtStatusLogData
extern USlider _UTL_ReadCtStatusLogDataLength ( UT_PIN , UT_DUT );
#define UTL_ReadCtStatusLogDataLength _UTL_ReadCtStatusLogDataLength
extern RadioButton _UTL_ReadCtStatusResult ( UT_PIN , UT_DUT );
#define UTL_ReadCtStatusResult _UTL_ReadCtStatusResult
extern void _UTL_ResetCt ( RadioButton );
#define UTL_ResetCt _UTL_ResetCt
extern SourceSyncCpHandle _UTL_GetSourceSyncCpHandle( void );
#define UTL_GetSourceSyncCpHandle _UTL_GetSourceSyncCpHandle
extern void _UTL_AddSourceSyncCpTargetPin( SourceSyncCpHandle, UT_PIN );
#define UTL_AddSourceSyncCpTargetPin _UTL_AddSourceSyncCpTargetPin
extern void _UTL_ClearSourceSyncCpTargetPin( SourceSyncCpHandle );
#define UTL_ClearSourceSyncCpTargetPin _UTL_ClearSourceSyncCpTargetPin
extern void _UTL_SetSourceSyncCpMode( SourceSyncCpHandle, CheckButton );
#define UTL_SetSourceSyncCpMode _UTL_SetSourceSyncCpMode
extern void _UTL_SendSourceSyncCp( SourceSyncCpHandle );
#define UTL_SendSourceSyncCp _UTL_SendSourceSyncCp
extern void _UTL_ResetSourceSyncCp( void );
#define UTL_ResetSourceSyncCp _UTL_ResetSourceSyncCp
extern DcHvlvdrHandle _UTL_GetDcHvlvdrHandle(void);
#define UTL_GetDcHvlvdrHandle _UTL_GetDcHvlvdrHandle
extern void _UTL_SetDcHvlvdrMode(DcHvlvdrHandle h, RadioButton mode);
#define UTL_SetDcHvlvdrMode _UTL_SetDcHvlvdrMode
extern void _UTL_SetDcHvlvdrMrange(DcHvlvdrHandle h, DSlider mmax, DSlider mmin);
#define UTL_SetDcHvlvdrMrange _UTL_SetDcHvlvdrMrange
extern void _UTL_SetDcHvlvdrLimitHigh(DcHvlvdrHandle h, DSlider ulmt, CheckButton onoff);
#define UTL_SetDcHvlvdrLimitHigh _UTL_SetDcHvlvdrLimitHigh
extern void _UTL_SetDcHvlvdrLimitLow(DcHvlvdrHandle h, DSlider llmt, CheckButton onoff);
#define UTL_SetDcHvlvdrLimitLow _UTL_SetDcHvlvdrLimitLow
extern void _UTL_SetDcHvlvdrMeasCnt(DcHvlvdrHandle h, Slider cnt);
#define UTL_SetDcHvlvdrMeasCnt _UTL_SetDcHvlvdrMeasCnt
extern void _UTL_SendDcHvlvdr(DcHvlvdrHandle h);
#define UTL_SendDcHvlvdr _UTL_SendDcHvlvdr
extern void _UTL_WriteDcHvlvdrSettlingTime(DSlider st);
#define UTL_WriteDcHvlvdrSettlingTime _UTL_WriteDcHvlvdrSettlingTime
extern void _UTL_UpdateDcHvlvdr( DcHvlvdrHandle );
#define UTL_UpdateDcHvlvdr _UTL_UpdateDcHvlvdr
extern int _UTL_GetDcHvlvdrMode (DcHvlvdrHandle h, RadioButton * val);
#define UTL_GetDcHvlvdrMode _UTL_GetDcHvlvdrMode
extern int _UTL_GetDcHvlvdrMrangeMax (DcHvlvdrHandle h, DSlider * val);
#define UTL_GetDcHvlvdrMrangeMax _UTL_GetDcHvlvdrMrangeMax
extern int _UTL_GetDcHvlvdrMrangeMin (DcHvlvdrHandle h, DSlider * val);
#define UTL_GetDcHvlvdrMrangeMin _UTL_GetDcHvlvdrMrangeMin
extern int _UTL_GetDcHvlvdrLimitHigh (DcHvlvdrHandle h, DSlider * val);
#define UTL_GetDcHvlvdrLimitHigh _UTL_GetDcHvlvdrLimitHigh
extern int _UTL_GetDcHvlvdrLimitHighDo (DcHvlvdrHandle dch, CheckButton * val);
#define UTL_GetDcHvlvdrLimitHighDo _UTL_GetDcHvlvdrLimitHighDo
extern int _UTL_GetDcHvlvdrLimitLow (DcHvlvdrHandle h, DSlider * val);
#define UTL_GetDcHvlvdrLimitLow _UTL_GetDcHvlvdrLimitLow
extern int _UTL_GetDcHvlvdrLimitLowDo (DcHvlvdrHandle dch, CheckButton * val);
#define UTL_GetDcHvlvdrLimitLowDo _UTL_GetDcHvlvdrLimitLowDo
extern int _UTL_GetDcHvlvdrMeasCnt (DcHvlvdrHandle h, Slider * val);
#define UTL_GetDcHvlvdrMeasCnt _UTL_GetDcHvlvdrMeasCnt
extern DSlider _UTL_ReadDcHvlvdrSettlingTime( void );
#define UTL_ReadDcHvlvdrSettlingTime _UTL_ReadDcHvlvdrSettlingTime
extern DctHvlvdrHandle _UTL_GetDctHvlvdrHandle(void);
#define UTL_GetDctHvlvdrHandle _UTL_GetDctHvlvdrHandle
extern void _UTL_SetDctHvlvdrPinList(DctHvlvdrHandle h, char *plst);
#define UTL_SetDctHvlvdrPinList _UTL_SetDctHvlvdrPinList
extern void _UTL_MeasDctHvlvdr(DctHvlvdrHandle h);
#define UTL_MeasDctHvlvdr _UTL_MeasDctHvlvdr
extern AdcHvlvdrHandle _UTL_GetAdcHvlvdrHandle( void );
#define UTL_GetAdcHvlvdrHandle _UTL_GetAdcHvlvdrHandle
extern void _UTL_SetAdcHvlvdrPgEnable( AdcHvlvdrHandle , CheckButton );
#define UTL_SetAdcHvlvdrPgEnable _UTL_SetAdcHvlvdrPgEnable
extern void _UTL_SetAdcHvlvdrStartCycle( AdcHvlvdrHandle , RadioButton );
#define UTL_SetAdcHvlvdrStartCycle _UTL_SetAdcHvlvdrStartCycle
extern void _UTL_SetAdcHvlvdrPinList( AdcHvlvdrHandle , char * );
#define UTL_SetAdcHvlvdrPinList _UTL_SetAdcHvlvdrPinList
extern void _UTL_SendAdcHvlvdr( AdcHvlvdrHandle );
#define UTL_SendAdcHvlvdr _UTL_SendAdcHvlvdr
extern void _UTL_UpdateAdcHvlvdr( AdcHvlvdrHandle );
#define UTL_UpdateAdcHvlvdr _UTL_UpdateAdcHvlvdr
extern int _UTL_GetAdcHvlvdrPgEnable (AdcHvlvdrHandle h, CheckButton * val);
#define UTL_GetAdcHvlvdrPgEnable _UTL_GetAdcHvlvdrPgEnable
extern int _UTL_GetAdcHvlvdrStartCycle (AdcHvlvdrHandle h, RadioButton * val);
#define UTL_GetAdcHvlvdrStartCycle _UTL_GetAdcHvlvdrStartCycle
extern int _UTL_GetAdcHvlvdrPinList (AdcHvlvdrHandle h, char ** val);
#define UTL_GetAdcHvlvdrPinList _UTL_GetAdcHvlvdrPinList
extern DctHvlvdrReadPinHandle _UTL_GetDctHvlvdrReadPinHandle(void);
#define UTL_GetDctHvlvdrReadPinHandle _UTL_GetDctHvlvdrReadPinHandle
extern void _UTL_SetDctHvlvdrReadPinDut(DctHvlvdrReadPinHandle h, UT_DUT dut);
#define UTL_SetDctHvlvdrReadPinDut _UTL_SetDctHvlvdrReadPinDut
extern void _UTL_SetDctHvlvdrReadPinNumber(DctHvlvdrReadPinHandle h, UT_PIN pin);
#define UTL_SetDctHvlvdrReadPinNumber _UTL_SetDctHvlvdrReadPinNumber
extern void _UTL_SetDctHvlvdrReadPinMode(DctHvlvdrReadPinHandle h, RadioButton mode);
#define UTL_SetDctHvlvdrReadPinMode _UTL_SetDctHvlvdrReadPinMode
extern DSlider _UTL_ReadDctHvlvdrPinData(DctHvlvdrReadPinHandle h);
#define UTL_ReadDctHvlvdrPinData _UTL_ReadDctHvlvdrPinData
extern CheckButton _UTL_ReadDctHvlvdrPin(DctHvlvdrReadPinHandle h);
#define UTL_ReadDctHvlvdrPin _UTL_ReadDctHvlvdrPin
extern UT_ErrorInfo _UTSC_ErrorInfo_Construct(void);
#define UTSC_ErrorInfo_Construct _UTSC_ErrorInfo_Construct
extern int _UTSC_ErrorInfo_Destruct(UT_ErrorInfo);
#define UTSC_ErrorInfo_Destruct _UTSC_ErrorInfo_Destruct
extern int _UTSC_ErrorInfo_SetMessageId(UT_ErrorInfo,char *);
#define UTSC_ErrorInfo_SetMessageId _UTSC_ErrorInfo_SetMessageId
extern char *_UTSC_ErrorInfo_GetMessageId(UT_ErrorInfo);
#define UTSC_ErrorInfo_GetMessageId _UTSC_ErrorInfo_GetMessageId
extern int _UTSC_ErrorInfo_AddMessageArgs(UT_ErrorInfo,char *);
#define UTSC_ErrorInfo_AddMessageArgs _UTSC_ErrorInfo_AddMessageArgs
extern UT_ErrorInfoList _UTSC_ErrorInfo_GetMessageArgsList(UT_ErrorInfo);
#define UTSC_ErrorInfo_GetMessageArgsList _UTSC_ErrorInfo_GetMessageArgsList
extern int _UTSC_ErrorInfo_GetMessageArgsNum(UT_ErrorInfoList);
#define UTSC_ErrorInfo_GetMessageArgsNum _UTSC_ErrorInfo_GetMessageArgsNum
extern char *_UTSC_ErrorInfo_GetMessageArgs(UT_ErrorInfoList,int);
#define UTSC_ErrorInfo_GetMessageArgs _UTSC_ErrorInfo_GetMessageArgs
extern int _UTSC_ErrorInfo_SetStation(UT_ErrorInfo,char *);
#define UTSC_ErrorInfo_SetStation _UTSC_ErrorInfo_SetStation
extern char *_UTSC_ErrorInfo_GetStation(UT_ErrorInfo);
#define UTSC_ErrorInfo_GetStation _UTSC_ErrorInfo_GetStation
extern int _UTSC_ErrorInfo_SetSite(UT_ErrorInfo,char *);
#define UTSC_ErrorInfo_SetSite _UTSC_ErrorInfo_SetSite
extern char *_UTSC_ErrorInfo_GetSite(UT_ErrorInfo);
#define UTSC_ErrorInfo_GetSite _UTSC_ErrorInfo_GetSite
extern int _UTSC_ErrorInfo_SetComponent(UT_ErrorInfo,char *);
#define UTSC_ErrorInfo_SetComponent _UTSC_ErrorInfo_SetComponent
extern char *_UTSC_ErrorInfo_GetComponent(UT_ErrorInfo);
#define UTSC_ErrorInfo_GetComponent _UTSC_ErrorInfo_GetComponent
extern int _UTSC_ErrorInfo_SetProgram(UT_ErrorInfo,char *);
#define UTSC_ErrorInfo_SetProgram _UTSC_ErrorInfo_SetProgram
extern char *_UTSC_ErrorInfo_GetProgram(UT_ErrorInfo);
#define UTSC_ErrorInfo_GetProgram _UTSC_ErrorInfo_GetProgram
extern int _UTSC_ErrorInfo_SetTestName(UT_ErrorInfo,char *);
#define UTSC_ErrorInfo_SetTestName _UTSC_ErrorInfo_SetTestName
extern char *_UTSC_ErrorInfo_GetTestName(UT_ErrorInfo);
#define UTSC_ErrorInfo_GetTestName _UTSC_ErrorInfo_GetTestName
extern int _UTSC_ErrorInfo_SetFunction(UT_ErrorInfo,char *);
#define UTSC_ErrorInfo_SetFunction _UTSC_ErrorInfo_SetFunction
extern char *_UTSC_ErrorInfo_GetFunction(UT_ErrorInfo);
#define UTSC_ErrorInfo_GetFunction _UTSC_ErrorInfo_GetFunction
extern int _UTSC_ErrorInfo_SetCatalog(UT_ErrorInfo,char *);
#define UTSC_ErrorInfo_SetCatalog _UTSC_ErrorInfo_SetCatalog
extern char *_UTSC_ErrorInfo_GetCatalog(UT_ErrorInfo);
#define UTSC_ErrorInfo_GetCatalog _UTSC_ErrorInfo_GetCatalog
extern int _UTSC_ErrorInfo_AddExtra(UT_ErrorInfo,char *);
#define UTSC_ErrorInfo_AddExtra _UTSC_ErrorInfo_AddExtra
extern UT_ErrorInfoList _UTSC_ErrorInfo_GetExtraList(UT_ErrorInfo);
#define UTSC_ErrorInfo_GetExtraList _UTSC_ErrorInfo_GetExtraList
extern int _UTSC_ErrorInfo_GetExtraNum(UT_ErrorInfoList);
#define UTSC_ErrorInfo_GetExtraNum _UTSC_ErrorInfo_GetExtraNum
extern char *_UTSC_ErrorInfo_GetExtra(UT_ErrorInfoList,int);
#define UTSC_ErrorInfo_GetExtra _UTSC_ErrorInfo_GetExtra
extern UT_ErrorInfo _UTSC_ErrorInfo_Get(int);
#define UTSC_ErrorInfo_Get _UTSC_ErrorInfo_Get
extern UT_ErrorInfo _UTSC_ErrorInfo_Deserialize(char *,size_t);
#define UTSC_ErrorInfo_Deserialize _UTSC_ErrorInfo_Deserialize
extern int _UTSC_Rm_Lock(char *, char *);
#define UTSC_Rm_Lock _UTSC_Rm_Lock
extern int _UTSC_Rm_TryLock(char *, char *);
#define UTSC_Rm_TryLock _UTSC_Rm_TryLock
extern int _UTSC_Rm_Unlock(char *);
#define UTSC_Rm_Unlock _UTSC_Rm_Unlock
extern void _UTSC_Rm_ExitOnError(int);
#define UTSC_Rm_ExitOnError _UTSC_Rm_ExitOnError
extern char *_UTSC_Rm_GetErrorMessage( void );
#define UTSC_Rm_GetErrorMessage _UTSC_Rm_GetErrorMessage
extern int _UTSC_Gpib_Open ( char *, UTSC_Gpib * );
#define UTSC_Gpib_Open _UTSC_Gpib_Open
extern int _UTSC_Gpib_Close ( UTSC_Gpib );
#define UTSC_Gpib_Close _UTSC_Gpib_Close
extern int _UTSC_Gpib_SetConfig( UTSC_Gpib, char *, char * );
#define UTSC_Gpib_SetConfig _UTSC_Gpib_SetConfig
extern int _UTSC_Gpib_GetConfig( UTSC_Gpib, char *, char *, UTSC_size_t );
#define UTSC_Gpib_GetConfig _UTSC_Gpib_GetConfig
extern int _UTSC_Gpib_SendData ( UTSC_Gpib, void *, UTSC_size_t );
#define UTSC_Gpib_SendData _UTSC_Gpib_SendData
extern int _UTSC_Gpib_RecvData ( UTSC_Gpib, void *, UTSC_size_t, UTSC_size_t *);
#define UTSC_Gpib_RecvData _UTSC_Gpib_RecvData
extern int _UTSC_Gpib_ClearDevice( UTSC_Gpib );
#define UTSC_Gpib_ClearDevice _UTSC_Gpib_ClearDevice
extern int _UTSC_Gpib_TriggerDevice( UTSC_Gpib );
#define UTSC_Gpib_TriggerDevice _UTSC_Gpib_TriggerDevice
extern int _UTSC_Gpib_RecvStb ( UTSC_Gpib, int * );
#define UTSC_Gpib_RecvStb _UTSC_Gpib_RecvStb
extern int _UTSC_Gpib_RecvStbAll( UTSC_Gpib, int * );
#define UTSC_Gpib_RecvStbAll _UTSC_Gpib_RecvStbAll
extern int _UTSC_Gpib_WaitSrq ( UTSC_Gpib, long );
#define UTSC_Gpib_WaitSrq _UTSC_Gpib_WaitSrq
extern int _UTSC_Gpib_GetChannel( UTSC_Gpib, int * );
#define UTSC_Gpib_GetChannel _UTSC_Gpib_GetChannel
extern void _UTSC_Gpib_ExitOnError( int );
#define UTSC_Gpib_ExitOnError _UTSC_Gpib_ExitOnError
extern char *_UTSC_Gpib_GetErrorMessage( void );
#define UTSC_Gpib_GetErrorMessage _UTSC_Gpib_GetErrorMessage
extern int _UTSC_Sm_Attach(const char *);
#define UTSC_Sm_Attach _UTSC_Sm_Attach
extern int _UTSC_Sm_Detach(void);
#define UTSC_Sm_Detach _UTSC_Sm_Detach
extern int _UTSC_Sm_GetSessionId(char **);
#define UTSC_Sm_GetSessionId _UTSC_Sm_GetSessionId
extern int _UTSC_Sm_GetSessionAttribute(int, char **);
#define UTSC_Sm_GetSessionAttribute _UTSC_Sm_GetSessionAttribute
extern int _UTSC_Sm_GetSessionPgid(char **);
#define UTSC_Sm_GetSessionPgid _UTSC_Sm_GetSessionPgid
extern int _UTSC_Sm_GetTestUnitNumber(int *);
#define UTSC_Sm_GetTestUnitNumber _UTSC_Sm_GetTestUnitNumber
extern int _UTSC_Sm_GetTestSiteNumber(int *);
#define UTSC_Sm_GetTestSiteNumber _UTSC_Sm_GetTestSiteNumber
extern int _UTSC_Sm_GetRepairSiteNumber(int *);
#define UTSC_Sm_GetRepairSiteNumber _UTSC_Sm_GetRepairSiteNumber
extern int _UTSC_Sm_ProcessGroup_Reserve(char *, int, char **);
#define UTSC_Sm_ProcessGroup_Reserve _UTSC_Sm_ProcessGroup_Reserve
extern int _UTSC_Sm_Exec(char *, UTSC_SmPro);
#define UTSC_Sm_Exec _UTSC_Sm_Exec
extern int _UTSC_Sm_Term(char *, char *);
#define UTSC_Sm_Term _UTSC_Sm_Term
extern int _UTSC_Sm_Kill(char *, char *);
#define UTSC_Sm_Kill _UTSC_Sm_Kill
extern int _UTSC_Sm_GetPgidStatus(char *, char *, char **, void **, size_t *);
#define UTSC_Sm_GetPgidStatus _UTSC_Sm_GetPgidStatus
extern int _UTSC_SmPro_Construct(UTSC_SmPro *);
#define UTSC_SmPro_Construct _UTSC_SmPro_Construct
extern int _UTSC_SmPro_Destruct(UTSC_SmPro);
#define UTSC_SmPro_Destruct _UTSC_SmPro_Destruct
extern int _UTSC_SmPro_File_Set(UTSC_SmPro, char *);
#define UTSC_SmPro_File_Set _UTSC_SmPro_File_Set
extern int _UTSC_SmPro_Argument_Add(UTSC_SmPro, char *);
#define UTSC_SmPro_Argument_Add _UTSC_SmPro_Argument_Add
extern int _UTSC_SmPro_Argument_Clear(UTSC_SmPro);
#define UTSC_SmPro_Argument_Clear _UTSC_SmPro_Argument_Clear
extern int _UTSC_SmPro_Place_Set(UTSC_SmPro, char *);
#define UTSC_SmPro_Place_Set _UTSC_SmPro_Place_Set
extern int _UTSC_SmPro_StdoutStream_Set(UTSC_SmPro, char *);
#define UTSC_SmPro_StdoutStream_Set _UTSC_SmPro_StdoutStream_Set
extern int _UTSC_SmPro_StderrStream_Set(UTSC_SmPro, char *);
#define UTSC_SmPro_StderrStream_Set _UTSC_SmPro_StderrStream_Set
extern int _UTSC_Sm_RequestNotice(char *, UTSC_SmNtf, int);
#define UTSC_Sm_RequestNotice _UTSC_Sm_RequestNotice
extern int _UTSC_Sm_GetChannel(int *);
#define UTSC_Sm_GetChannel _UTSC_Sm_GetChannel
extern int _UTSC_Sm_CheckNotice(char **, UTSC_SmNtf *);
#define UTSC_Sm_CheckNotice _UTSC_Sm_CheckNotice
extern int _UTSC_SmNtf_Construct(UTSC_SmNtf *);
#define UTSC_SmNtf_Construct _UTSC_SmNtf_Construct
extern int _UTSC_SmNtf_Destruct(UTSC_SmNtf);
#define UTSC_SmNtf_Destruct _UTSC_SmNtf_Destruct
extern int _UTSC_SmNtf_SessionPgid_Set(UTSC_SmNtf, char *);
#define UTSC_SmNtf_SessionPgid_Set _UTSC_SmNtf_SessionPgid_Set
extern int _UTSC_SmNtf_SessionPgid_Get(UTSC_SmNtf, char **);
#define UTSC_SmNtf_SessionPgid_Get _UTSC_SmNtf_SessionPgid_Get
extern int _UTSC_SmNtf_Place_Get(UTSC_SmNtf, char **);
#define UTSC_SmNtf_Place_Get _UTSC_SmNtf_Place_Get
extern int _UTSC_SmNtf_Transition_Get(UTSC_SmNtf, char **);
#define UTSC_SmNtf_Transition_Get _UTSC_SmNtf_Transition_Get
extern int _UTSC_Sm_LockSession(const char *);
#define UTSC_Sm_LockSession _UTSC_Sm_LockSession
extern int _UTSC_Sm_UnlockSession(const char *);
#define UTSC_Sm_UnlockSession _UTSC_Sm_UnlockSession
extern int _UTSC_Sm_GetLockState(const char *, int *);
#define UTSC_Sm_GetLockState _UTSC_Sm_GetLockState
extern int _UTSC_Sm_GetLockTerminal(const char *, char **);
#define UTSC_Sm_GetLockTerminal _UTSC_Sm_GetLockTerminal
extern int _UTSC_Sm_GetLockTime(const char *, time_t *);
#define UTSC_Sm_GetLockTime _UTSC_Sm_GetLockTime
extern int _UTSC_Sm_GetLockSession(const char *, char **);
#define UTSC_Sm_GetLockSession _UTSC_Sm_GetLockSession
extern int _UTSC_Sm_GetLastOperatedSessionId(char **);
#define UTSC_Sm_GetLastOperatedSessionId _UTSC_Sm_GetLastOperatedSessionId
extern char *_UTSC_Sm_GetErrorMessage(void);
#define UTSC_Sm_GetErrorMessage _UTSC_Sm_GetErrorMessage
extern int _UTSC_TestUnit_GetTestUnit(int **, int *);
#define UTSC_TestUnit_GetTestUnit _UTSC_TestUnit_GetTestUnit
extern int _UTSC_TestUnit_GetPStn(int, int **, int *);
#define UTSC_TestUnit_GetPStn _UTSC_TestUnit_GetPStn
extern int _UTSC_TestUnit_GetTestSite(int, int **, int *);
#define UTSC_TestUnit_GetTestSite _UTSC_TestUnit_GetTestSite
extern int _UTSC_TestUnit_GetTestUnitByPStn(int, int *);
#define UTSC_TestUnit_GetTestUnitByPStn _UTSC_TestUnit_GetTestUnitByPStn
extern int _UTSC_TestSite_GetHostName(int, int, char **);
#define UTSC_TestSite_GetHostName _UTSC_TestSite_GetHostName
extern int _UTSC_TestSite_GetTbusNumber(int, int, int *);
#define UTSC_TestSite_GetTbusNumber _UTSC_TestSite_GetTbusNumber
extern int _UTSC_TestSite_GetRepairSite(int, int, int **, int *);
#define UTSC_TestSite_GetRepairSite _UTSC_TestSite_GetRepairSite
extern int _UTSC_RepairSite_GetHostName(int, int, int, char **);
#define UTSC_RepairSite_GetHostName _UTSC_RepairSite_GetHostName
extern int _UTSC_RepairSite_GetRcbNumber(int, int, int, int **, int *);
#define UTSC_RepairSite_GetRcbNumber _UTSC_RepairSite_GetRcbNumber
extern int _UTSC_Em_Open(UTSC_Em *, char *);
#define UTSC_Em_Open _UTSC_Em_Open
extern int _UTSC_Em_Close(UTSC_Em);
#define UTSC_Em_Close _UTSC_Em_Close
extern int _UTSC_Em_SendEvent(UTSC_Em, char *, void *, UTSC_size_t);
#define UTSC_Em_SendEvent _UTSC_Em_SendEvent
extern int _UTSC_Em_ReceiveEvent(UTSC_Em, char **, void **, UTSC_size_t *);
#define UTSC_Em_ReceiveEvent _UTSC_Em_ReceiveEvent
extern int _UTSC_Em_SetOption(UTSC_Em, int, char *, int);
#define UTSC_Em_SetOption _UTSC_Em_SetOption
extern int _UTSC_Em_GetOption(UTSC_Em, int, char *, int *);
#define UTSC_Em_GetOption _UTSC_Em_GetOption
extern int _UTSC_Em_GetChannel(UTSC_Em, int *);
#define UTSC_Em_GetChannel _UTSC_Em_GetChannel
extern char *_UTSC_Em_GetErrorMessage(void);
#define UTSC_Em_GetErrorMessage _UTSC_Em_GetErrorMessage
extern int _UTSC_Pf_Open(UTSC_Pf *, char *);
#define UTSC_Pf_Open _UTSC_Pf_Open
extern int _UTSC_Pf_Close(UTSC_Pf);
#define UTSC_Pf_Close _UTSC_Pf_Close
extern int _UTSC_Pf_Create(UTSC_Pf, char *, long);
#define UTSC_Pf_Create _UTSC_Pf_Create
extern int _UTSC_Pf_Delete(UTSC_Pf, char *);
#define UTSC_Pf_Delete _UTSC_Pf_Delete
extern int _UTSC_Pf_WriteData(UTSC_Pf, char *, void *, UTSC_size_t);
#define UTSC_Pf_WriteData _UTSC_Pf_WriteData
extern int _UTSC_Pf_ReadData(UTSC_Pf, char *, void **, UTSC_size_t *);
#define UTSC_Pf_ReadData _UTSC_Pf_ReadData
extern int _UTSC_Pf_SetOption(UTSC_Pf, int, char *, int);
#define UTSC_Pf_SetOption _UTSC_Pf_SetOption
extern int _UTSC_Pf_GetOption(UTSC_Pf, int, char *, int *);
#define UTSC_Pf_GetOption _UTSC_Pf_GetOption
extern int _UTSC_Pf_Find(UTSC_Pf, int, void *, UTSC_NameSet *);
#define UTSC_Pf_Find _UTSC_Pf_Find
extern char *_UTSC_Pf_GetErrorMessage(void);
#define UTSC_Pf_GetErrorMessage _UTSC_Pf_GetErrorMessage
extern int _UTSC_NameSet_Construct(UTSC_NameSet *);
#define UTSC_NameSet_Construct _UTSC_NameSet_Construct
extern int _UTSC_NameSet_Destruct(UTSC_NameSet);
#define UTSC_NameSet_Destruct _UTSC_NameSet_Destruct
extern int _UTSC_NameSet_GetCount(UTSC_NameSet, int *);
#define UTSC_NameSet_GetCount _UTSC_NameSet_GetCount
extern int _UTSC_NameSet_Add(UTSC_NameSet, int, char *);
#define UTSC_NameSet_Add _UTSC_NameSet_Add
extern int _UTSC_NameSet_Delete(UTSC_NameSet, int);
#define UTSC_NameSet_Delete _UTSC_NameSet_Delete
extern int _UTSC_NameSet_Clear(UTSC_NameSet);
#define UTSC_NameSet_Clear _UTSC_NameSet_Clear
extern int _UTSC_NameSet_Includes(UTSC_NameSet, char *, int *);
#define UTSC_NameSet_Includes _UTSC_NameSet_Includes
extern int _UTSC_NameSet_Get(UTSC_NameSet, int, char **);
#define UTSC_NameSet_Get _UTSC_NameSet_Get
extern int _UTSC_Flow_TestSiteSync_Wait(char *, int *);
#define UTSC_Flow_TestSiteSync_Wait _UTSC_Flow_TestSiteSync_Wait
extern void _UTSC_Flow_ExitOnError(int);
#define UTSC_Flow_ExitOnError _UTSC_Flow_ExitOnError
extern char *_UTSC_Flow_GetErrorMessage(void);
#define UTSC_Flow_GetErrorMessage _UTSC_Flow_GetErrorMessage
extern int _UTSC_TesterCondition_ReadInfo ( int, double **, int * );
#define UTSC_TesterCondition_ReadInfo _UTSC_TesterCondition_ReadInfo
extern void _UTSC_TesterCondition_ExitOnError ( int );
#define UTSC_TesterCondition_ExitOnError _UTSC_TesterCondition_ExitOnError
extern char *_UTSC_TesterCondition_GetErrorMessage( void );
#define UTSC_TesterCondition_GetErrorMessage _UTSC_TesterCondition_GetErrorMessage


#ifdef __cplusplus
}
#endif
#endif
