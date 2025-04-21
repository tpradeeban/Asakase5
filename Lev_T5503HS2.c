#include "progddr5.h"
#include "LevPrivate.h"

extern void LevStd ( Cond *cond)
{
  LevelStartTime = GetTime();
  double vdd       = cond->Vdd;
  double vref      = vdd * cond->ref;
  double viha      = vref + 0.350; // 
  double vila      = vref - 0.350; //
  double vihd      = vref + 0.280; // TODO should be work  +0.150V;after DRCP update 2019/E?
  double vild      = vref - 0.280; // TODO should be work  +0.150V;after DRCP update 2019/E?

  double r_ratio   = 50.0/60.0;
  double viha_odt  = viha  + r_ratio * (viha  - vdd);
  double vila_odt  = vila  + r_ratio * (vila  - vdd);
  double vihd_odt  = vihd  + r_ratio * (vihd  - vdd);
  double vild_odt  = vild  + r_ratio * (vild  - vdd);
  double voh       = vdd;
  double vol       = (50.0/(50.0+40.0))*vdd;
  double vo        = (voh+vol)/2;
  (void)viha_odt;
  (void)vila_odt;

  IN ( 1, viha           , vila       ); // CK/CK#              (Term: Hi-Z)
  IN ( 2, viha_odt       , vila_odt   ); // CMD                 (Term: ZQ/2)
  IN ( 3, viha_odt       , vila_odt   ); // ADR                 (Term: ZQ/2)
  IN ( 9, viha_odt       , vila_odt   ); // ABI                 (Term: ZQ/2)
  IN ( 4, viha_odt       , vila_odt   ); // CKE                 (Term: ZQ/2)
  IN ( 5, vdd            , 0.000      ); // MF SEN RESET#       (Term: Hi-Z)
  IN ( 6, viha           , vila       ); // WCK/WCK#            (Term: Hi-Z)
  IN ( 7, vihd_odt       , vild_odt   ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)    
  IN (11, vref           , 0.000      ); // VREFD1                              
  IN (12, vref           , 0.000      ); // VREFD2 - doesn't use half vref mode 
  IN (13, vref           , 0.000      ); // VREFC
  OUT( 1, vo             , vo         ); // DQ0-31 
  OUT( 2, vo             , vo         ); // DBI0-3 
  OUT( 3, vo             , vo         ); // EDC0-3 
  VT ( 1, viha                        ); // CK/CK#              (Term: Hi-Z) 
  VT ( 2, viha_odt                    ); // CMD                 (Term: ZQ/2) 
  VT ( 3, viha_odt                    ); // ADR                 (Term: ZQ/2) 
  VT ( 9, viha_odt                    ); // ABI                 (Term: ZQ/2) 
  VT ( 4, viha_odt                    ); // CKE                 (Term: ZQ/2) 
  VT ( 5, vdd                         ); // MF SEN RESET#       (Term: Hi-Z) 
  VT ( 6, viha                        ); // WCK/WCK#            (Term: Hi-Z) 
  VT ( 7, vdd                         ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2) 
  VsStd( cond);
  LevelEndTime = GetTime();
}

extern void LevDout( Cond *cond, double x)
{
  double vdd       = cond->Vdd;
  double voh       = vdd;
  double vol       = (50.0/(50.0+40.0))*vdd;
  double vo        = (voh+vol)/2;
  OUT( 1, vo +x  , vo +x  ); // DQ0-31
  OUT( 2, vo +x  , vo +x  ); // DBI0-3
  OUT( 3, vo +x  , vo +x  ); // EDC0-3
}

extern void LevDin( Cond *cond, double x)
{
  double vref      = cond->Vdd * cond->ref;
//IN ( 11, vref+x  , 0.0       ); // VREFD1
  IN (11, vref + 0.04 +x    , 0.000        ); // VREFD1                              //TODO rm offset after drcp update 2019/E ?
  IN (12, vref + 0.04 +x    , 0.000        ); // VREFD2 - doesn't use half vref mode //TODO rm offset after drcp update 2019/E ?
}

extern void LevWin ( Cond *cond, double x)
{
  double vdd       = cond->Vdd;
  double vref      = vdd * cond->ref;
  double viha      = vref + 0.250; 
  double vila      = vref - 0.250;
  IN ( 6, viha+x       , vila+x       ); // WCK/WCK#      (Term: Hi-Z)
}

extern void LevVdd( Cond *cond, double vdd)
{
  cond->Vdd  = vdd;
  LevStd(cond);
}
