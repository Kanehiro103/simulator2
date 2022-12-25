#include "library.h"
#include <math.h>

// 2^i
unsigned int pow2(unsigned int i) { // unsigned int
    unsigned int ans = 1;
    return ans << i;
}
unsigned long pow2_ul(unsigned int i) { // unsigned long
    unsigned long ans = 1;
    return ans << i;
}

// num[a, b]
unsigned int cut(unsigned int num, unsigned int a, unsigned int b) {    // unsigned int
    return (num << (31 - a)) >> (31 - a + b);
}
unsigned long cut_ul(unsigned long num, unsigned int a, unsigned int b) {   // unsigned long
    return (num << (63 - a)) >> (63 - a + b);
}

// 符号なし整数を"符号あり"と見做して変換
// 第二引数で変換元のビット数(2以上)を指定
int to_signed(unsigned int num, int i) {
    unsigned int s = cut(num, i - 1, i - 1);
    unsigned int m = cut(num, i - 2, 0);
    if(s == 0) {
        return (int)m;
    } else {
        return ((int)pow2(i - 1) - (int)m) * (-1);
    }
}

// 符号・指数・仮数を受け取り、浮動小数点数の内部表現(floating-point notation)にして返す
unsigned int fpn(unsigned int s, unsigned int e, unsigned int m) {
    return (s << 31) + (e << 23) + m;
}

// 浮動小数点数の内部表現を数値に変換
float to_float(unsigned int x) {
    unsigned int s = cut(x, 31, 31);
    unsigned int e = cut(x, 30, 23);
    unsigned int m = cut(x, 22, 0);
    unsigned int ma = m + pow2(23);
    if(e == 0) {
         if(m == 0) {
            if(s == 0) {
                return 0.0;
            } else {
                return -0.0;
            }
         } else {
            if(s == 0) {
                return (float)m * powf(2.0, -150.0);
            } else {
                return (float)m * powf(2.0, -150.0) * (-1);
            }
         }
    } else if(e == 255) {
        if(m == 0) {
            if(s == 0) {
                return INFINITY;
            } else {
                return -INFINITY;
            }
        } else {
            return NAN;
        }
    } else {
        if(s == 0) {
            return (float)ma * powf(2.0, (float)e - 150.0);
        } else {
            return (float)ma * powf(2.0, (float)e - 150.0) * (-1);
        }
    }
}

// 浮動小数点数の内部表現を獲得
unsigned int to_fpn(float x) {
    union { float f; unsigned int i; } u;
    u.f = x;
    return u.i;
}