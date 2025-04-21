#include "progddr5.h"
#include "DcPrivate.h"

extern void DcContLow( const char *pinlist_name, double sampling_rate, double sampling_count, double upper_limit, double lower_limit)
{
  SamplingRate(sampling_rate);
  ISVM( -80.00e-6, R(-80.00e-6), M(-2.000e+0), CLAMP(600.0e-3,-1.400e+0), COUNT(sampling_count), LIMIT(upper_limit, lower_limit)); 
}

extern void DcMeasure( const char *pinlist_name)
{
  DctHandle Dct = UTL_GetDctHandle();
  UTL_SetDctPinList  ( Dct, (char *)pinlist_name);
  UTL_MeasDct      ( Dct);
  UTL_DeleteHandle ( Dct);
}

extern void DcMeasureAd( const char *pinlist_name, const char *pat)
{
  PinCursor pin_cursor = UTL_GetPinCursor((char *)pinlist_name);
  UT_PIN pin_single;

  while(( pin_single = UTL_NextPin( pin_cursor )) != UT_NOMORE ){ /* loop to get each pin from pinlist */
    UTL_CreatePinList( "pl_single"                 );
    UTL_SetPinType   ( "pl_single", UT_PINTYPE_PIN );
    UTL_AddPinNumber ( "pl_single", pin_single     );

    int dutGroupMaxNum = UTL_GetDctDutGroupMaxNumber( pin_single );
    int i,j;
    for( i = 0 ; i<=dutGroupMaxNum ; i++ ){ /* dut max group number loop */
      ExclusionHandle exclh = UTL_GetExclusionHandle();
      for( j = 0; j<=dutGroupMaxNum ; j++ ){
        if( j != i ){
            UT_DUT dut;
            DutCursor dut_cursor = UTL_GetDctDutGroupCursor( pin_single, j );
            while(( dut = UTL_NextDut( dut_cursor )) != UT_NOMORE ){
               UTL_AddExclusionDut ( exclh, dut   );
            }
            UTL_SetExclusionMask      ( exclh, UT_ON );
            UTL_SetExclusionSetOrReset( exclh, UT_ON );
            UTL_DeleteCursor( dut_cursor );
        }
      }
      UTL_SendExclusion( exclh ); /* exclusion */

      if( pat ){ //in case of ADM DC measurement and need to run pattern, need to run pattern again once dut is excluded.
        UTL_StopFct();
        FctHandle Fct = UTL_GetFctHandle();
        UTL_SetFctNoWait   ( Fct, UT_ON );
        UTL_SetFctStartPc  ( Fct, 0    );
        UTL_SetFctNoClear  ( Fct, UT_ON );
        UTL_StartFct       ( Fct        );
        UTL_WaitTime( 150.0e-3);
      }

      /* execute dc test */
      DctHandle Dct = UTL_GetDctHandle();
      UTL_SetDctPinList  ( Dct, "pl_single" );
//      UTL_SetDctPinVi    ( Dct, UT_ON);
//      UTL_SetDctRelayMode( Dct, UT_DCT_SWAP);
      UTL_MeasDct        ( Dct );
      UTL_DeleteHandle   ( Dct );

      if( pat ){
        UTL_StopFct();
      }

      UTL_SetExclusionSetOrReset( exclh, UT_OFF );
      UTL_SendExclusion         ( exclh         ); /* reset exclusion */
      UTL_DeleteHandle          ( exclh         );
    }
  }
}

extern void DcMvm    ( const char *pinlist_name,double sampling_rate, double sampling_count, double upper_limit, double lower_limit)
{
  SamplingRate(sampling_rate);
  MVM ( M(2.000e+0), COUNT(sampling_count), LIMIT(upper_limit, lower_limit));
}

extern void DcVsim0   ( const char *pinlist_name, double sampling_rate, double sampling_count, double upper_limit, double lower_limit)
{
  SamplingRate(sampling_rate);
  VSIM( 0.000e+0, R(0.000e+0), M(upper_limit), COUNT(sampling_count), LIMIT(upper_limit, lower_limit));
}
extern void DcVsim1p05   ( const char *pinlist_name, double sampling_rate, double sampling_count, double upper_limit, double lower_limit)
{
  SamplingRate(sampling_rate);
  VSIM( 1.050, R(1.0500e+0), M(upper_limit), COUNT(sampling_count), LIMIT(upper_limit, lower_limit));
}
extern void DcVsim0p75   ( const char *pinlist_name, double sampling_rate, double sampling_count, double upper_limit, double lower_limit)
{
  SamplingRate(sampling_rate);
  VSIM( 0.750, R(0.7500e+0), M(upper_limit), COUNT(sampling_count), LIMIT(upper_limit, lower_limit));
}
extern void DcVsim0p65   ( const char *pinlist_name, double sampling_rate, double sampling_count, double upper_limit, double lower_limit)
{
  SamplingRate(sampling_rate);
  VSIM( 0.650, R(0.6500e+0), M(upper_limit), COUNT(sampling_count), LIMIT(upper_limit, lower_limit));
}


