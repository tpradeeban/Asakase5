#ifndef   ___Lev_H
#define   ___Lev_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * 標準的な電圧条件を設定します。基本的にはクロック/アドレス/コマンド信号は
 * 終端している条件で振幅を計算します。これは初期段階でソケット・ボードが4種類
 * 用意されており、終端条件で電圧設定しないと全てのソケット・ボード上でデバイス
 * を動作させられないためです。
 * @param cond 試験条件
 */
extern void IODC_OFF_Setting(           );

/**
 * IODC設定用の関数です。IODCシュムのY軸を
 * 終端している条件で振幅を計算します。これは初期段階でソケット・ボードが4種類
 * 用意されており、終端条件で電圧設定しないと全てのソケット・ボード上でデバイス
 * を動作させられないためです。
 * @param cond 試験条件
 */
extern void LevStd_Swing_300( Cond *cond);

/**
 * IODC設定用の関数です。IODCシュムのY軸を
 * 終端している条件で振幅を計算します。これは初期段階でソケット・ボードが4種類
 * 用意されており、終端条件で電圧設定しないと全てのソケット・ボード上でデバイス
 * を動作させられないためです。
 * @param cond 試験条件
 */
extern void LevStd_Swing_350( Cond *cond);

/**
 * IODC設定用の関数です。IODCシュムのY軸を
 * 終端している条件で振幅を計算します。これは初期段階でソケット・ボードが4種類
 * 用意されており、終端条件で電圧設定しないと全てのソケット・ボード上でデバイス
 * を動作させられないためです。
 * @param cond 試験条件
 */
extern void LevStd_Swing_400( Cond *cond);

/**
 * IODC設定用の関数です。IODCシュムのY軸を
 * 終端している条件で振幅を計算します。これは初期段階でソケット・ボードが4種類
 * 用意されており、終端条件で電圧設定しないと全てのソケット・ボード上でデバイス
 * を動作させられないためです。
 * @param cond 試験条件
 */
extern void LevData ( Cond *cond);

/**
 * IODC設定用の関数です。IODCシュムのY軸を
 * 終端している条件で振幅を計算します。これは初期段階でソケット・ボードが4種類
 * 用意されており、終端条件で電圧設定しないと全てのソケット・ボード上でデバイス
 * を動作させられないためです。
 * @param cond 試験条件
 */
extern void LevStd ( Cond *cond);

/**
 * IODC設定用の関数です。IODCシュムのY軸を
 * 終端している条件で振幅を計算します。これは初期段階でソケット・ボードが4種類
 * 用意されており、終端条件で電圧設定しないと全てのソケット・ボード上でデバイス
 * を動作させられないためです。
 * @param cond 試験条件
 */
extern void LevIodc_Swing_300( Cond *cond);
/**
 * シュム条件設定用の関数です。Vdd-tCKシュムのY軸を設定する際に利用します。
 * 内部でLevStd()が呼び出されます。
 * @param cond 試験条件
 * @param x    シュム条件(= Vdd).
 */
extern void LevIodc_Swing_350( Cond *cond);
/**
 * シュム条件設定用の関数です。Vdd-tCKシュムのY軸を設定する際に利用します。
 * 内部でLevStd()が呼び出されます。
 * @param cond 試験条件
 * @param x    シュム条件(= Vdd).
 */
extern void LevIodc_Swing_400( Cond *cond);
/**
 * シュム条件設定用の関数です。Vdd-tCKシュムのY軸を設定する際に利用します。
 * 内部でLevStd()が呼び出されます。
 * @param cond 試験条件
 * @param x    シュム条件(= Vdd).
 */
extern void LevIodc( Cond *cond);
/**
 * シュム条件設定用の関数です。Vdd-tCKシュムのY軸を設定する際に利用します。
 * 内部でLevStd()が呼び出されます。
 * @param cond 試験条件
 * @param x    シュム条件(= Vdd).
 */
extern void LevVdd_Swing_300( Cond *cond, double x);
extern void LevVdd_Swing_350( Cond *cond, double x);
extern void LevVdd_Swing_400( Cond *cond, double x);

extern void LevVddIodc_Swing_300( Cond *cond, double x);
extern void LevVddIodc_Swing_350( Cond *cond, double x);
extern void LevVddIodc_Swing_400( Cond *cond, double x);

extern void LevVddIodc ( Cond *cond, double x);

/**
 * シュム条件設定用の関数です。DoutシュムのY軸を設定する際に利用します。
 * @param cond 試験条件
 * @param x    シュム条件
 */
extern void LevVdd ( Cond *cond, double x);

/**
 * シュム条件設定用の関数です。DoutシュムのY軸を設定する際に利用します。
 * @param cond 試験条件
 * @param x    シュム条件
 */
extern void LevDout_DQ( Cond *cond, double x);
extern void LevDout( Cond *cond, double x);

/**
 * シュム条件設定用の関数です。WCK inputシュムのY軸を設定する際に利用します。
 * @param cond 試験条件
 * @param x    シュム条件
 */
extern void LevWin ( Cond *cond, double x);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ___Lev_H
