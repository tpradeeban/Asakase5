#include "progddr5.h"
#include "LevPrivate.h"

extern void IODC_OFF_Setting ()
{
  IodModeHandle iodc_setting;
  iodc_setting = UTL_GetIodModeHandle();
  UTL_SetIodModeAuto(iodc_setting, UT_OFF);
//  fprintf(stderr,"IODC_OFF\n");
  UTL_SendIodMode(iodc_setting);

}

extern void LevStd_Swing_300( Cond *cond)
{
  double vdd       = cond->Vdd;
  double vref      = vdd * cond->ref;
  double vihd      = vref + 0.150;
  double vild      = vref - 0.150;
  double r_ratio   = 50.0/60.0;
  double vihd_odt  = vihd  + r_ratio * (vihd  - vdd);
  double vild_odt  = vild  + r_ratio * (vild  - vdd);
  IN ( 7, vihd_odt     , vild_odt     ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
  LevData ( cond); 
}

extern void LevStd_Swing_350( Cond *cond)
{
  double vdd       = cond->Vdd;
  double vref      = vdd * cond->ref;
  double vihd      = vref + 0.175;
  double vild      = vref - 0.175;
  double r_ratio   = 50.0/60.0;
  double vihd_odt  = vihd  + r_ratio * (vihd  - vdd);
  double vild_odt  = vild  + r_ratio * (vild  - vdd);
  IN ( 7, vihd_odt     , vild_odt     ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
  LevData ( cond); 
}

extern void LevStd_Swing_400( Cond *cond)
{
  double vdd       = cond->Vdd;
  double vref      = vdd * cond->ref;
  double vihd      = vref + 0.200;
  double vild      = vref - 0.200;
  double r_ratio   = 50.0/60.0;
  double vihd_odt  = vihd  + r_ratio * (vihd  - vdd);
  double vild_odt  = vild  + r_ratio * (vild  - vdd);
  IN ( 7, vihd_odt     , vild_odt     ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
  LevData ( cond); 
}
extern void LevStd ( Cond *cond)
{
  double vdd       = cond->Vdd;
  double vref      = vdd * cond->ref;
  double viha      = vref + 0.250; // STL
  double vila      = vref - 0.250; // STL
  double vihd      = vref + 0.200;
  double vild      = vref - 0.200;
  double viha2     = vref + 0.500; // DTL
  double vila2     = vref - 0.500; // DTL
  double r_ratio   = 50.0/60.0;
  double viha_odt  = viha  + r_ratio * (viha  - vdd);
  double vila_odt  = vila  + r_ratio * (vila  - vdd);
  double vihd_odt  = vihd  + r_ratio * (vihd  - vdd);
  double vild_odt  = vild  + r_ratio * (vild  - vdd);
  double viha_odt2 = viha2 + r_ratio * (viha2 - vdd);
  double vila_odt2 = vila2 + r_ratio * (vila2 - vdd);
  (void)viha_odt;
  (void)vila_odt;

  IN ( 1, viha2        , vila2        ); // CK/CK#              (Term: Hi-Z & term on SB)
  IN ( 2, viha_odt2    , vila_odt2    ); // CMD                 (Term: ZQ/2 & term on MB)
  IN ( 3, viha_odt2    , vila_odt2    ); // ADR                 (Term: ZQ/2 & term on MB)
  IN ( 9, viha_odt2    , vila_odt2    ); // ABI                 (Term: ZQ/2 & term on MB)
  IN ( 4, viha_odt2    , vila_odt2    ); // CKE                 (Term: ZQ/2 & term on MB)
  IN ( 5, vdd          , 0.000        ); // MF SEN RESET#       (Term: Hi-Z)
  IN ( 6, viha         , vila         ); // WCK/WCK#            (Term: Hi-Z)
  IN ( 7, vihd_odt     , vild_odt     ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
  OUT( 1, vref         , vref         ); // DQ0-31
  OUT( 2, vref         , vref         ); // DBI0-3
  OUT( 3, vref         , vref         ); // EDC0-3
  VT ( 1, viha2                       ); // CK/CK#              (Term: Hi-Z & term on SB) // 新しいPEではViHとVTTの差が大きいと発振してしまう。
  VT ( 2, viha_odt2                   ); // CMD                 (Term: ZQ/2 & term on MB) // これはDREコントロールしない(従ってVTを使わない)
  VT ( 3, viha_odt2                   ); // ADR                 (Term: ZQ/2 & term on MB) // DR専用ピンであっても同様である。そこで暫定対策
  VT ( 9, viha_odt2                   ); // ABI                 (Term: ZQ/2 & term on MB) // として全てのDR専用ピンに対してOUTLを記述し、
  VT ( 4, viha_odt2                   ); // CKE                 (Term: ZQ/2 & term on MB) // VTに対してViHと同じ値を設定する。
  VT ( 5, vdd                         ); // MF SEN RESET#       (Term: Hi-Z)              //
  VT ( 6, viha                        ); // WCK/WCK#            (Term: Hi-Z)              //
  VT ( 7, vdd                         ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
  VsStd( cond);
}

extern void LevData ( Cond *cond)
{
  double vdd       = cond->Vdd;
  double vref      = vdd * cond->ref;
  double viha      = vref + 0.250; // STL
  double vila      = vref - 0.250; // STL
//double vihd      = vref + 0.150;
//double vild      = vref - 0.150;
  double viha2     = vref + 0.500; // DTL
  double vila2     = vref - 0.500; // DTL
  double r_ratio   = 50.0/60.0;
  double viha_odt  = viha  + r_ratio * (viha  - vdd);
  double vila_odt  = vila  + r_ratio * (vila  - vdd);
//double vihd_odt  = vihd  + r_ratio * (vihd  - vdd);
//double vild_odt  = vild  + r_ratio * (vild  - vdd);
  double viha_odt2 = viha2 + r_ratio * (viha2 - vdd);
  double vila_odt2 = vila2 + r_ratio * (vila2 - vdd);
  (void)viha_odt;
  (void)vila_odt;

  IN ( 1, viha2        , vila2        ); // CK/CK#              (Term: Hi-Z & term on SB)
  IN ( 2, viha_odt2    , vila_odt2    ); // CMD                 (Term: ZQ/2 & term on MB)
  IN ( 3, viha_odt2    , vila_odt2    ); // ADR                 (Term: ZQ/2 & term on MB)
  IN ( 9, viha_odt2    , vila_odt2    ); // ABI                 (Term: ZQ/2 & term on MB)
  IN ( 4, viha_odt2    , vila_odt2    ); // CKE                 (Term: ZQ/2 & term on MB)
  IN ( 5, vdd          , 0.000        ); // MF SEN RESET#       (Term: Hi-Z)
  IN ( 6, viha         , vila         ); // WCK/WCK#            (Term: Hi-Z)
//IN ( 7, vihd_odt     , vild_odt     ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
  OUT( 1, vref         , vref         ); // DQ0-31
  OUT( 2, vref         , vref         ); // DBI0-3
  OUT( 3, vref         , vref         ); // EDC0-3
  VT ( 1, viha2                       ); // CK/CK#              (Term: Hi-Z & term on SB) // 新しいPEではViHとVTTの差が大きいと発振してしまう。
  VT ( 2, viha_odt2                   ); // CMD                 (Term: ZQ/2 & term on MB) // これはDREコントロールしない(従ってVTを使わない)
  VT ( 3, viha_odt2                   ); // ADR                 (Term: ZQ/2 & term on MB) // DR専用ピンであっても同様である。そこで暫定対策
  VT ( 9, viha_odt2                   ); // ABI                 (Term: ZQ/2 & term on MB) // として全てのDR専用ピンに対してOUTLを記述し、
  VT ( 4, viha_odt2                   ); // CKE                 (Term: ZQ/2 & term on MB) // VTに対してViHと同じ値を設定する。
  VT ( 5, vdd                         ); // MF SEN RESET#       (Term: Hi-Z)              //
  VT ( 6, viha                        ); // WCK/WCK#            (Term: Hi-Z)              //
  VT ( 7, vdd                         ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
  VsStd( cond);
}

extern void LevIodc_Swing_300( Cond *cond)
{
  double vdd       = cond->Vdd;
  double vref      = vdd * cond->ref;
  double viha      = vref + 0.250; // STL
  double vila      = vref - 0.250; // STL
  double vihd      = vref + 0.150;
  double vild      = vref - 0.150;
  double viha2     = vref + 0.500; // DTL
  double vila2     = vref - 0.500; // DTL
  double r_ratio   = 50.0/60.0;
  double viha_odt  = viha  + r_ratio * (viha  - vdd);
  double vila_odt  = vila  + r_ratio * (vila  - vdd);
  double vihd_odt  = vihd  + r_ratio * (vihd  - vdd);
  double vild_odt  = vild  + r_ratio * (vild  - vdd);
  double viha_odt2 = viha2 + r_ratio * (viha2 - vdd);
  double vila_odt2 = vila2 + r_ratio * (vila2 - vdd);
  (void)viha_odt;
  (void)vila_odt;

  IN ( 1, viha2        , vila2        ); // CK/CK#              (Term: Hi-Z & term on SB)
  IN ( 2, viha_odt2    , vila_odt2    ); // CMD                 (Term: ZQ/2 & term on MB)
  IN ( 3, viha_odt2    , vila_odt2    ); // ADR                 (Term: ZQ/2 & term on MB)
  IN ( 9, viha_odt2    , vila_odt2    ); // ABI                 (Term: ZQ/2 & term on MB)
  IN ( 4, viha_odt2    , vila_odt2    ); // CKE                 (Term: ZQ/2 & term on MB)
  IN ( 5, vdd          , 0.000        ); // MF SEN RESET#       (Term: Hi-Z)
  IN ( 6, viha         , vila         ); // WCK/WCK#            (Term: Hi-Z)
  IN ( 7, vihd_odt     , vild_odt     ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
  OUT( 1, vref         , vref         ); // DQ0-31
  OUT( 2, vref         , vref         ); // DBI0-3
  OUT( 3, vref         , vref         ); // EDC0-3
  VT ( 1, viha2                       ); // CK/CK#              (Term: Hi-Z & term on SB) // 新しいPEではViHとVTTの差が大きいと発振してしまう。
  VT ( 2, viha_odt2                   ); // CMD                 (Term: ZQ/2 & term on MB) // これはDREコントロールしない(従ってVTを使わない)
  VT ( 3, viha_odt2                   ); // ADR                 (Term: ZQ/2 & term on MB) // DR専用ピンであっても同様である。そこで暫定対策
  VT ( 9, viha_odt2                   ); // ABI                 (Term: ZQ/2 & term on MB) // として全てのDR専用ピンに対してOUTLを記述し、
  VT ( 4, viha_odt2                   ); // CKE                 (Term: ZQ/2 & term on MB) // VTに対してViHと同じ値を設定する。
  VT ( 5, vdd                         ); // MF SEN RESET#       (Term: Hi-Z)              //
  VT ( 6, viha                        ); // WCK/WCK#            (Term: Hi-Z)              //
  VT ( 7, vdd                         ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
              IodModeHandle iodc_setting;
              IodHandle iodc_level;
              DSlider iodh = (vihd_odt - vdd)/2;   /* iodh = (vih - vt)/2 */
              DSlider iodl = (vild_odt - vdd)/2;   /* iodl = (vil - vt)/2 */
              iodc_setting = UTL_GetIodModeHandle();
              iodc_level = UTL_GetIodHandle();
          
              UTL_SetIodMode(iodc_setting,UT_ON);
          //  UTL_SetIodModeAuto(iodc_setting, UT_OFF);
              UTL_SetIodHigh(iodc_level, iodh); 
              UTL_SetIodLow (iodc_level, iodl); 
              UTL_SendIodMode(iodc_setting);
              UTL_SendIod(iodc_level);
  VsStd( cond);
}
extern void LevIodc_Swing_350( Cond *cond)
{
  double vdd       = cond->Vdd;
  double vref      = vdd * cond->ref;
  double viha      = vref + 0.250; // STL
  double vila      = vref - 0.250; // STL
  double vihd      = vref + 0.175;
  double vild      = vref - 0.175;
  double viha2     = vref + 0.500; // DTL
  double vila2     = vref - 0.500; // DTL
  double r_ratio   = 50.0/60.0;
  double viha_odt  = viha  + r_ratio * (viha  - vdd);
  double vila_odt  = vila  + r_ratio * (vila  - vdd);
  double vihd_odt  = vihd  + r_ratio * (vihd  - vdd);
  double vild_odt  = vild  + r_ratio * (vild  - vdd);
  double viha_odt2 = viha2 + r_ratio * (viha2 - vdd);
  double vila_odt2 = vila2 + r_ratio * (vila2 - vdd);
  (void)viha_odt;
  (void)vila_odt;

  IN ( 1, viha2        , vila2        ); // CK/CK#              (Term: Hi-Z & term on SB)
  IN ( 2, viha_odt2    , vila_odt2    ); // CMD                 (Term: ZQ/2 & term on MB)
  IN ( 3, viha_odt2    , vila_odt2    ); // ADR                 (Term: ZQ/2 & term on MB)
  IN ( 9, viha_odt2    , vila_odt2    ); // ABI                 (Term: ZQ/2 & term on MB)
  IN ( 4, viha_odt2    , vila_odt2    ); // CKE                 (Term: ZQ/2 & term on MB)
  IN ( 5, vdd          , 0.000        ); // MF SEN RESET#       (Term: Hi-Z)
  IN ( 6, viha         , vila         ); // WCK/WCK#            (Term: Hi-Z)
  IN ( 7, vihd_odt     , vild_odt     ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
  OUT( 1, vref         , vref         ); // DQ0-31
  OUT( 2, vref         , vref         ); // DBI0-3
  OUT( 3, vref         , vref         ); // EDC0-3
  VT ( 1, viha2                       ); // CK/CK#              (Term: Hi-Z & term on SB) // 新しいPEではViHとVTTの差が大きいと発振してしまう。
  VT ( 2, viha_odt2                   ); // CMD                 (Term: ZQ/2 & term on MB) // これはDREコントロールしない(従ってVTを使わない)
  VT ( 3, viha_odt2                   ); // ADR                 (Term: ZQ/2 & term on MB) // DR専用ピンであっても同様である。そこで暫定対策
  VT ( 9, viha_odt2                   ); // ABI                 (Term: ZQ/2 & term on MB) // として全てのDR専用ピンに対してOUTLを記述し、
  VT ( 4, viha_odt2                   ); // CKE                 (Term: ZQ/2 & term on MB) // VTに対してViHと同じ値を設定する。
  VT ( 5, vdd                         ); // MF SEN RESET#       (Term: Hi-Z)              //
  VT ( 6, viha                        ); // WCK/WCK#            (Term: Hi-Z)              //
  VT ( 7, vdd                         ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
              IodModeHandle iodc_setting;
              IodHandle iodc_level;
              DSlider iodh = (vihd_odt - vdd)/2;   /* iodh = (vih - vt)/2 */
              DSlider iodl = (vild_odt - vdd)/2;   /* iodl = (vil - vt)/2 */
              iodc_setting = UTL_GetIodModeHandle();
              iodc_level = UTL_GetIodHandle();
          
              UTL_SetIodMode(iodc_setting,UT_ON);
          //  UTL_SetIodModeAuto(iodc_setting, UT_OFF);
              UTL_SetIodHigh(iodc_level, iodh); 
              UTL_SetIodLow (iodc_level, iodl); 
              UTL_SendIodMode(iodc_setting);
              UTL_SendIod(iodc_level);
  VsStd( cond);
}
extern void LevIodc_Swing_400( Cond *cond)
{
  double vdd       = cond->Vdd;
  double vref      = vdd * cond->ref;
  double viha      = vref + 0.250; // STL
  double vila      = vref - 0.250; // STL
  double vihd      = vref + 0.200;
  double vild      = vref - 0.200;
  double viha2     = vref + 0.500; // DTL
  double vila2     = vref - 0.500; // DTL
  double r_ratio   = 50.0/60.0;
  double viha_odt  = viha  + r_ratio * (viha  - vdd);
  double vila_odt  = vila  + r_ratio * (vila  - vdd);
  double vihd_odt  = vihd  + r_ratio * (vihd  - vdd);
  double vild_odt  = vild  + r_ratio * (vild  - vdd);
  double viha_odt2 = viha2 + r_ratio * (viha2 - vdd);
  double vila_odt2 = vila2 + r_ratio * (vila2 - vdd);
  (void)viha_odt;
  (void)vila_odt;

  IN ( 1, viha2        , vila2        ); // CK/CK#              (Term: Hi-Z & term on SB)
  IN ( 2, viha_odt2    , vila_odt2    ); // CMD                 (Term: ZQ/2 & term on MB)
  IN ( 3, viha_odt2    , vila_odt2    ); // ADR                 (Term: ZQ/2 & term on MB)
  IN ( 9, viha_odt2    , vila_odt2    ); // ABI                 (Term: ZQ/2 & term on MB)
  IN ( 4, viha_odt2    , vila_odt2    ); // CKE                 (Term: ZQ/2 & term on MB)
  IN ( 5, vdd          , 0.000        ); // MF SEN RESET#       (Term: Hi-Z)
  IN ( 6, viha         , vila         ); // WCK/WCK#            (Term: Hi-Z)
  IN ( 7, vihd_odt     , vild_odt     ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
  OUT( 1, vref         , vref         ); // DQ0-31
  OUT( 2, vref         , vref         ); // DBI0-3
  OUT( 3, vref         , vref         ); // EDC0-3
  VT ( 1, viha2                       ); // CK/CK#              (Term: Hi-Z & term on SB) // 新しいPEではViHとVTTの差が大きいと発振してしまう。
  VT ( 2, viha_odt2                   ); // CMD                 (Term: ZQ/2 & term on MB) // これはDREコントロールしない(従ってVTを使わない)
  VT ( 3, viha_odt2                   ); // ADR                 (Term: ZQ/2 & term on MB) // DR専用ピンであっても同様である。そこで暫定対策
  VT ( 9, viha_odt2                   ); // ABI                 (Term: ZQ/2 & term on MB) // として全てのDR専用ピンに対してOUTLを記述し、
  VT ( 4, viha_odt2                   ); // CKE                 (Term: ZQ/2 & term on MB) // VTに対してViHと同じ値を設定する。
  VT ( 5, vdd                         ); // MF SEN RESET#       (Term: Hi-Z)              //
  VT ( 6, viha                        ); // WCK/WCK#            (Term: Hi-Z)              //
  VT ( 7, vdd                         ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
              IodModeHandle iodc_setting;
              IodHandle iodc_level;
              DSlider iodh = (vihd_odt - vdd)/2;   /* iodh = (vih - vt)/2 */
              DSlider iodl = (vild_odt - vdd)/2;   /* iodl = (vil - vt)/2 */
              iodc_setting = UTL_GetIodModeHandle();
              iodc_level = UTL_GetIodHandle();
          
              UTL_SetIodMode(iodc_setting,UT_ON);
          //  UTL_SetIodModeAuto(iodc_setting, UT_OFF);
              UTL_SetIodHigh(iodc_level, iodh); 
              UTL_SetIodLow (iodc_level, iodl); 
              UTL_SendIodMode(iodc_setting);
              UTL_SendIod(iodc_level);
  VsStd( cond);
}
extern void LevIodc( Cond *cond)
{
  double vdd       = cond->Vdd;
  double vref      = vdd * cond->ref;
  double viha      = vref + 0.250; // STL
  double vila      = vref - 0.250; // STL
  double vihd      = vref + 0.150;
  double vild      = vref - 0.150;
  double viha2     = vref + 0.500; // DTL
  double vila2     = vref - 0.500; // DTL
  double r_ratio   = 50.0/60.0;
  double viha_odt  = viha  + r_ratio * (viha  - vdd);
  double vila_odt  = vila  + r_ratio * (vila  - vdd);
  double vihd_odt  = vihd  + r_ratio * (vihd  - vdd);
  double vild_odt  = vild  + r_ratio * (vild  - vdd);
  double viha_odt2 = viha2 + r_ratio * (viha2 - vdd);
  double vila_odt2 = vila2 + r_ratio * (vila2 - vdd);
  (void)viha_odt;
  (void)vila_odt;

  IN ( 1, viha2        , vila2        ); // CK/CK#              (Term: Hi-Z & term on SB)
  IN ( 2, viha_odt2    , vila_odt2    ); // CMD                 (Term: ZQ/2 & term on MB)
  IN ( 3, viha_odt2    , vila_odt2    ); // ADR                 (Term: ZQ/2 & term on MB)
  IN ( 9, viha_odt2    , vila_odt2    ); // ABI                 (Term: ZQ/2 & term on MB)
  IN ( 4, viha_odt2    , vila_odt2    ); // CKE                 (Term: ZQ/2 & term on MB)
  IN ( 5, vdd          , 0.000        ); // MF SEN RESET#       (Term: Hi-Z)
  IN ( 6, viha         , vila         ); // WCK/WCK#            (Term: Hi-Z)
  IN ( 7, vihd_odt     , vild_odt     ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
  OUT( 1, vref         , vref         ); // DQ0-31
  OUT( 2, vref         , vref         ); // DBI0-3
  OUT( 3, vref         , vref         ); // EDC0-3
  VT ( 1, viha2                       ); // CK/CK#              (Term: Hi-Z & term on SB) // 新しいPEではViHとVTTの差が大きいと発振してしまう。
  VT ( 2, viha_odt2                   ); // CMD                 (Term: ZQ/2 & term on MB) // これはDREコントロールしない(従ってVTを使わない)
  VT ( 3, viha_odt2                   ); // ADR                 (Term: ZQ/2 & term on MB) // DR専用ピンであっても同様である。そこで暫定対策
  VT ( 9, viha_odt2                   ); // ABI                 (Term: ZQ/2 & term on MB) // として全てのDR専用ピンに対してOUTLを記述し、
  VT ( 4, viha_odt2                   ); // CKE                 (Term: ZQ/2 & term on MB) // VTに対してViHと同じ値を設定する。
  VT ( 5, vdd                         ); // MF SEN RESET#       (Term: Hi-Z)              //
  VT ( 6, viha                        ); // WCK/WCK#            (Term: Hi-Z)              //
  VT ( 7, vdd                         ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
  //            IodModeHandle iodc_setting;
  //            IodHandle iodc_level;
  //            DSlider iodh = (vihd_odt - vdd)/2;   /* iodh = (vih - vt)/2 */
  //            DSlider iodl = (vild_odt - vdd)/2;   /* iodl = (vil - vt)/2 */
  //            iodc_setting = UTL_GetIodModeHandle();
  //            iodc_level = UTL_GetIodHandle();
  //        
  //            UTL_SetIodMode(iodc_setting,UT_ON);
  //        //  UTL_SetIodModeAuto(iodc_setting, UT_OFF);
  //            UTL_SetIodHigh(iodc_level, iodh+0.150); 
  //            UTL_SetIodLow (iodc_level, iodl); 
  //            UTL_SendIodMode(iodc_setting);
  //            UTL_SendIod(iodc_level);
  VsStd( cond);
}

//extern void LevIodc( Cond *cond)
//{
//  double vdd       = cond->Vdd;
//  double vref      = vdd * cond->ref;
//  double viha      = vref + 0.250; // STL
//  double vila      = vref - 0.250; // STL
//  double vihd      = vref + 0.200;
//  double vild      = vref - 0.200;
//  double viha2     = vref + 0.500; // DTL
//  double vila2     = vref - 0.500; // DTL
//  double r_ratio   = 50.0/60.0;
//  double viha_odt  = viha  + r_ratio * (viha  - vdd);
//  double vila_odt  = vila  + r_ratio * (vila  - vdd);
//  double vihd_odt  = vihd  + r_ratio * (vihd  - vdd);
//  double vild_odt  = vild  + r_ratio * (vild  - vdd);
//  double viha_odt2 = viha2 + r_ratio * (viha2 - vdd);
//  double vila_odt2 = vila2 + r_ratio * (vila2 - vdd);
//  (void)viha_odt;
//  (void)vila_odt;
//
//  IN ( 1, viha2        , vila2        ); // CK/CK#              (Term: Hi-Z & term on SB)
//  IN ( 2, viha_odt2    , vila_odt2    ); // CMD                 (Term: ZQ/2 & term on MB)
//  IN ( 3, viha_odt2    , vila_odt2    ); // ADR                 (Term: ZQ/2 & term on MB)
//  IN ( 9, viha_odt2    , vila_odt2    ); // ABI                 (Term: ZQ/2 & term on MB)
//  IN ( 4, viha_odt2    , vila_odt2    ); // CKE                 (Term: ZQ/2 & term on MB)
//  IN ( 5, vdd          , 0.000        ); // MF SEN RESET#       (Term: Hi-Z)
//  IN ( 6, viha         , vila         ); // WCK/WCK#            (Term: Hi-Z)
//  IN ( 7, vihd_odt     , vild_odt     ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
//  OUT( 1, vref         , vref         ); // DQ0-31
//  OUT( 2, vref         , vref         ); // DBI0-3
//  OUT( 3, vref         , vref         ); // EDC0-3
//  VT ( 1, viha2                       ); // CK/CK#              (Term: Hi-Z & term on SB) // 新しいPEではViHとVTTの差が大きいと発振してしまう。
//  VT ( 2, viha_odt2                   ); // CMD                 (Term: ZQ/2 & term on MB) // これはDREコントロールしない(従ってVTを使わない)
//  VT ( 3, viha_odt2                   ); // ADR                 (Term: ZQ/2 & term on MB) // DR専用ピンであっても同様である。そこで暫定対策
//  VT ( 9, viha_odt2                   ); // ABI                 (Term: ZQ/2 & term on MB) // として全てのDR専用ピンに対してOUTLを記述し、
//  VT ( 4, viha_odt2                   ); // CKE                 (Term: ZQ/2 & term on MB) // VTに対してViHと同じ値を設定する。
//  VT ( 5, vdd                         ); // MF SEN RESET#       (Term: Hi-Z)              //
//  VT ( 6, viha                        ); // WCK/WCK#            (Term: Hi-Z)              //
//  VT ( 7, vdd                         ); // DQ0-31,DBI0-3,EDC0-3(Term: ZQ/2)
//  
//              IodModeHandle iodc_setting;
//              IodHandle iodc_level;
//              DSlider iodh = (vihd_odt - vdd)/2;   /* iodh = (vih - vt)/2 */
//              DSlider iodl = (vild_odt - vdd)/2;   /* iodl = (vil - vt)/2 */
//              iodc_setting = UTL_GetIodModeHandle();
//              iodc_level = UTL_GetIodHandle();
//          
//              UTL_SetIodMode(iodc_setting,UT_ON);
//          //  UTL_SetIodModeAuto(iodc_setting, UT_OFF);
//              UTL_SetIodHigh(iodc_level, iodh+0.150); 
//              UTL_SetIodLow (iodc_level, iodl); 
//              UTL_SendIodMode(iodc_setting);
//              UTL_SendIod(iodc_level);
//  VsStd( cond);
//}

extern void LevVddIodc_Swing_300 ( Cond *cond, double vdd)
{
  cond->Vdd = vdd;
  LevIodc_Swing_300( cond);
}

extern void LevVddIodc_Swing_350( Cond *cond, double vdd)
{
  cond->Vdd = vdd;
  LevIodc_Swing_350( cond);
}
extern void LevVddIodc_Swing_400 ( Cond *cond, double vdd)
{
  cond->Vdd = vdd;
  LevIodc_Swing_400( cond);
}
extern void LevVdd_Swing_300 ( Cond *cond, double vdd)
{
  cond->Vdd = vdd;
  LevStd_Swing_300( cond);
}
extern void LevVdd_Swing_350 ( Cond *cond, double vdd)
{
  cond->Vdd = vdd;
  LevStd_Swing_350( cond);
}
extern void LevVdd_Swing_400 ( Cond *cond, double vdd)
{
  cond->Vdd = vdd;
  LevStd_Swing_400( cond);
}
extern void LevVddIodc ( Cond *cond, double vdd)
{
  cond->Vdd = vdd;
  LevIodc( cond);
}

extern void LevVdd ( Cond *cond, double vdd)
{
  cond->Vdd = vdd;
  LevStd( cond);
}

extern void LevDout_DQ( Cond *cond, double x)
{
  double vref      = cond->Vdd * cond->ref;
  OUT( 1, vref+x  , vref+x  ); // DQ0-31
}

extern void LevDout( Cond *cond, double x)
{
  double vref      = cond->Vdd * cond->ref;
  OUT( 1, vref+x  , vref+x  ); // DQ0-31
  OUT( 2, vref+x  , vref+x  ); // DBI0-3
  OUT( 3, vref+x  , vref+x  ); // EDC0-3
}

extern void LevWin ( Cond *cond, double x)
{
  double vdd       = cond->Vdd;
  double vref      = vdd * cond->ref;
  double viha      = vref + 0.250; // STL
  double vila      = vref - 0.250; // STL
  IN ( 6, viha+x       , vila+x       ); // WCK/WCK#      (Term: Hi-Z)
}

