#ifndef _ERROR_H_
#define _ERROR_H_

union fi { float f; unsigned int i; };

// 誤差の表示
void error2(int, float, float);     // 二項演算子
void error1(int, float);        // 単項演算子

#endif