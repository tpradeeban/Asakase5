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
extern void LevStd ( Cond *cond);

/**
 * シュム条件設定用の関数です。Dout/DinシュムのY軸を設定する際に利用します。
 * @param cond 試験条件
 * @param x    シュム条件
 */
extern void LevDout( Cond *cond, double x);
extern void LevDin( Cond *cond, double x);

/**
 * シュム条件設定用の関数です。WCK inputシュムのY軸を設定する際に利用します。
 * @param cond 試験条件
 * @param x    シュム条件
 */
extern void LevWin ( Cond *cond, double x);


/*function to set the Vdd shmoo
 * @param cond 試験条件
 * @param vdd  シュム条件
 */
extern void LevVdd( Cond *cond, double vdd);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ___Lev_H
