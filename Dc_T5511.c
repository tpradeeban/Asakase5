#include "progddr5.h"
#include "DcPrivate.h"

extern void DcContLow( const char *pinlist_name, double upper_limit, double lower_limit)
{
  ISVM( -80.00e-6, R(-80.00e-6), M(2.000e+0), CLAMP(600.0e-3,-1.200e+0), LIMIT(upper_limit, lower_limit));
  Term(UT_OFF);
}

extern void DcMeasure( const char *pinlist_name)
{
  DcHandle Dct = UTL_GetDctHandle();
  UTL_SetDctPinList  ( Dct, (char *)pinlist_name);
  UTL_MeasDct      ( Dct);
  UTL_DeleteHandle ( Dct);
}

extern void DcMvm    ( const char *pinlist_name, double upper_limit, double lower_limit)
{
  MVM ( M(2.000e+0), LIMIT(upper_limit, lower_limit));
  Term(UT_OFF);
}

extern void DcVsim0   ( const char *pinlist_name, double upper_limit, double lower_limit)
{
  VSIM( 0.000e+0, R(0.000e+0), M(upper_limit), LIMIT(upper_limit, lower_limit));
  Term(UT_OFF);
}


