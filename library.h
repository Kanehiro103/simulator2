#ifndef _LIBRARY_H_
#define _LIBRARY_H_

// 2^i
unsigned int pow2(unsigned int);    // unsigned int
unsigned long pow2_ul(unsigned int);    // unsigned long

// num[a,b]
unsigned int cut(unsigned int, unsigned int, unsigned int);  // unsigned int
unsigned long cut_ul(unsigned long, unsigned int, unsigned int);    // unsigned long

// 符号なし整数を"符号あり"と見做して変換
// 第二引数で変換元のビット数(2以上)を指定
int to_signed(unsigned int, int);

// 符号・指数・仮数を受け取り、浮動小数点数の内部表現(floating-point notation)にして返す
unsigned int fpn(unsigned int, unsigned int, unsigned int);

// 浮動小数点数の内部表現を数値に変換
float to_float(unsigned int);

// 浮動小数点数の内部表現を獲得
unsigned int to_fpn(float);

#endif