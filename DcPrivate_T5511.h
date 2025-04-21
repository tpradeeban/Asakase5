#ifndef ___DcPrivate_H
#define ___DcPrivate_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @file
 * このファイルは"Dc.c"の記述を簡素で見やすくする目的で導入されているファイルです。"Dc.c"でのみincludeされ、"Dc.c"以外のソースファイルからincludeされません。
 */

/// DCユニット設定ハンドルです。DC設定用のVSIM()/ISVM()/MVM()マクロ内で使います。
static DcHandle           Dc;
/**
 * DCユニットの設定をATL風に容易にわかりやすくするためのマクロです。
 * 2番目以降の引数にはR()/M()/CLAMP()/LIMIT()/COUT()が指定可能です。
 * DCユニットに対してVSIMを設定します。
 * @attention VS設定用とDC設定用に同名のマクロがあります。
 * @param s 設定電圧
 */
#define VSIM(s,...)             (Dc=UTL_GetDcHandle(),UTL_SetDcMode ( Dc, UT_DCT_VSIM), UTL_SetDcSource( Dc, s),## __VA_ARGS__,UTL_SendDc(Dc,1),UTL_DeleteHandle(Dc))
/**
 * DCユニットの設定をATL風に容易にわかりやすくするためのマクロです。
 * 2番目以降の引数にはR()/M()/CLAMP()/LIMIT()/COUT()が指定可能です。
 * DCユニットに対してISVMを設定します。
 * @attention VS設定用とDC設定用に同名のマクロがあります。
 * @param s 設定電流
 */
#define ISVM(s,...)             (Dc=UTL_GetDcHandle(),UTL_SetDcMode ( Dc, UT_DCT_ISVM), UTL_SetDcSource( Dc, s),## __VA_ARGS__,UTL_SendDc(Dc,1),UTL_DeleteHandle(Dc))
/**
 * DCユニットの設定をATL風に容易にわかりやすくするためのマクロです。
 * 2番目以降の引数にはM()//LIMIT()/COUT()が指定可能です。
 * DCユニットに対してMVMを設定します。
 * @attention VS設定用とDC設定用に同名のマクロがあります。
 */
#define MVM(...)                (Dc=UTL_GetDcHandle(),UTL_SetDcMode ( Dc, UT_DCT_MVM )                         ,## __VA_ARGS__,UTL_SendDc(Dc,1),UTL_DeleteHandle(Dc))
/**
 * DCユニットの設定をATL風に容易にわかりやすくするためのマクロです。
 * VSIM()/ISVM()マクロ中に記述します。
 * DCユニットに対してソース・レンジを指定します。
 * @attention VS設定用とDC設定用に同名のマクロがあります。
 * @param r ソース・レンジ
 */
#define R(r)                    (UTL_SetDcSrange   ( Dc, r, r)                             )
/**
 * DCユニットの設定をATL風に容易にわかりやすくするためのマクロです。
 * VSIM()/ISVM()マクロ中に記述します。
 * DCユニットに対して測定レンジを指定します。
 * @attention VS設定用とDC設定用に同名のマクロがあります。
 * @param m 測定レンジ
 */
#define M(m)                    (UTL_SetDcMrange   ( Dc, m, m)                             )
/**
 * DCユニットの設定をATL風に容易にわかりやすくするためのマクロです。
 * VSIM()/ISVM()マクロ中に記述します。
 * DCユニットに対してクランプを指定します。
 * @attention VS設定用とDC設定用に同名のマクロがあります。
 * @param p プラス・クランプ
 * @param m マイナス・クランプ
 */
#define CLAMP(p,m)              (UTL_SetDcPclamp   ( Dc, p), UTL_SetDcMclamp( Dc, m)       )
/**
 * DCユニットの設定をATL風に容易にわかりやすくするためのマクロです。
 * VSIM()/ISVM()マクロ中に記述します。
 * DCユニットに対してパス範囲の上限・下限値を指定します。
 * @attention VS設定用とDC設定用に同名のマクロがあります。
 * @param u 上限値
 * @param l 下限値
 */
#define LIMIT(u,l)              (UTL_SetDcLimitHigh( Dc, u, ((u==NEGLECT)?UT_OFF:UT_ON)), \
                                 UTL_SetDcLimitLow ( Dc, l, ((l==NEGLECT)?UT_OFF:UT_ON))   )
/**
 * DCユニットの設定をATL風に容易にわかりやすくするためのマクロです。
 * VSIM()/ISVM()マクロ中に記述します。
 * DCユニットに対して測定回数を指定します。
 * @attention VS設定用とDC設定用に同名のマクロがあります。
 * @param c 測定回数
 */
#define COUNT(c)                (UTL_SetDcMeasCnt  ( Dc, cnt_)                             )

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // ___DcPrivate_H
