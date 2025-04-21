#ifndef   ___Dc_H
#define   ___Dc_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * 各ピンのコンタクト試験用のDC設定を行います。GDDR5-SGRAMの入出力ピンはODTで
 * 終端されています。そのため、電流印加で、ある電圧値に落ち着きます。
 * もし、入力ピンがショートしていたら、電圧は0Vですし、OPENだったらクランプ値に
 * 張り付きます。ここで指定するピン名称には何も意味はありません。VS設定とDC設定
 * の関数型を一致させるためのだけに存在しています。
 * @param pinlist_name 試験対象ピンリスト名称
 * @param upper_limit  DC試験のパス上限値
 * @param lower_limit  DC試験のパス下限値
 */
extern void DcContLow ( const char *pinlist_name, double upper_limit, double lower_limit);

/**
 * 引数で指定したピンに対してDC試験を行う関数です。
 * @param pinlist_name 試験対象ピンリスト名称
 */
extern void DcMeasure ( const char *pinlist_name                                        );

/**
 * DCユニットに対してMVM指定する関数です。ODT終端電圧を測定する際に利用します。
 * ここで指定するピン名称には何も意味はありません。VS設定とDC設定の関数型を一致
 * させるためのだけに存在しています。
 * @param pinlist_name 試験対象ピンリスト名称
 * @param upper_limit  DC試験のパス上限値
 * @param lower_limit  DC試験のパス下限値
 */
extern void DcMvm     ( const char *pinlist_name, double upper_limit, double lower_limit);

/**
 * DCユニットに対してVSIM指定する関数です。ODT終端抵抗を調べるために電流測定する
 * 際に利用します。対象ピンには0Vを設定します。
 * ここで指定するピン名称には何も意味はありません。VS設定とDC設定の関数型を一致
 * させるためのだけに存在しています。
 * @param pinlist_name 試験対象ピンリスト名称
 * @param upper_limit  DC試験のパス上限値
 * @param lower_limit  DC試験のパス下限値
 */
extern void DcVsim0   ( const char *pinlist_name, double upper_limit, double lower_limit);

//! DC試験の上限・下限値の設定において設定しない場合に用いる値
#define NEGLECT                 (999999.0)

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ___Dc_H
