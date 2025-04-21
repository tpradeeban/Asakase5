#ifndef ___LevPrivate_H
#define ___LevPrivate_H
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @file
 * このファイルは"Lev.c"の記述を簡素で見やすくする目的で導入されているファイルです。"Lev.c"でのみincludeされ、"Lev.c"以外のソースファイルからincludeされません。
 */

/// ドライバ入力電圧設定ハンドル
static ViHandle  Vi ;

/**
 * 電圧設定をATL風に容易にわかりやすくするためのマクロです。
 * ドライバの入力電圧を指定します。
 * @param n 相番号
 * @param h Vihを指定します。
 * @param l Vilを指定します。
 */
#define IN(n,h,l)               (Vi=UTL_GetViHandle(),UTL_SetViHigh(Vi,h),UTL_SetViLow(Vi,l),UTL_SendVi(Vi,n),UTL_DeleteHandle(Vi))

/// コンパレータ比較電圧設定ハンドル
static VoHandle  Vo ;
/**
 * 電圧設定をATL風に容易にわかりやすくするためのマクロです。
 * コンパレータの比較電圧を指定します。
 * @param n 相番号
 * @param h Vohを指定します。
 * @param l Volを指定します。
 */
#define OUT(n,h,l)              (Vo=UTL_GetVoHandle(),UTL_SetVoHigh(Vo,h),UTL_SetVoLow(Vo,l),UTL_SendVo(Vo,n),UTL_DeleteHandle(Vo))

/// 終端電圧設定ハンドル
static VtHandle  Vt ;

/**
 * 電圧設定をATL風に容易にわかりやすくするためのマクロです。
 * IOピンの終端電圧を指定します。
 * @param n 相番号
 * @param t Vttを指定します。
 */
#define VT(n,t)                 (Vt=UTL_GetVtHandle(),UTL_SetVt(Vt,t)                       ,UTL_SendVt(Vt,n),UTL_DeleteHandle(Vt))

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // ___LevPrivate_H
