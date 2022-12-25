#include "pseudo.h"
#include "fpu.h"
#include "alu.h"
#include "library.h"

// 即値
unsigned int pi = 0x40490fdb;   // 3.14159265

// x^i
unsigned int powg(unsigned int x, unsigned int i) {
    unsigned int k;
    unsigned int ans = 0x3f800000;    // 1.0
    for(k = 0; k < i; k++) {
        ans = fmul_num(ans, x);
    }
    return ans;
}

// reduction で使用
unsigned int rem(unsigned int x, unsigned int y, unsigned int p) {
    unsigned int tmp1 = fsub_num(x, y);
    if(fless_num(tmp1, p)) {
        return tmp1;
    } else {
        unsigned int tmp2 = fadd_num(y, p);
        return rem(x, tmp2, p);
    }
}

// 0 <= x < 2π に変換
unsigned int reduction(unsigned int x) {
    unsigned int tmp = to_fpn(2.0);
    unsigned int pi2 = fmul_num(pi, tmp);
    return rem(x, to_fpn(0.0), pi2);
}

// テイラー展開
unsigned int taylor_sin(unsigned int x) {   // sin
    unsigned int tmp1 = powg(x, 3);
    unsigned int tmp2 = powg(x, 5);
    unsigned int tmp3 = powg(x, 7);
    unsigned int tmp4 = powg(x, 9);
    unsigned int mul1 = fmul_num(to_fpn(0.166666666), tmp1);
    unsigned int mul2 = fmul_num(to_fpn(0.00833333333), tmp2);
    unsigned int mul3 = fmul_num(to_fpn(0.000198412698), tmp3);
    unsigned int mul4 = fmul_num(to_fpn(0.00000275573192), tmp4);
    unsigned int tmp;
    tmp = fsub_num(x, mul1);
    tmp = fadd_num(tmp, mul2);
    tmp = fsub_num(tmp, mul3);
    tmp = fadd_num(tmp, mul4);
    return tmp;
}

unsigned int taylor_cos(unsigned int x) {   // cos
    unsigned int tmp1 = powg(x, 2);
    unsigned int tmp2 = powg(x, 4);
    unsigned int tmp3 = powg(x, 6);
    unsigned int tmp4 = powg(x, 8);
    unsigned int mul1 = fmul_num(to_fpn(0.5), tmp1);
    unsigned int mul2 = fmul_num(to_fpn(0.0416666666), tmp2);
    unsigned int mul3 = fmul_num(to_fpn(0.00138888888), tmp3);
    unsigned int mul4 = fmul_num(to_fpn(0.0000248015873), tmp4);
    unsigned int tmp;
    tmp = fsub_num(to_fpn(1.0), mul1);
    tmp = fadd_num(tmp, mul2);
    tmp = fsub_num(tmp, mul3);
    tmp = fadd_num(tmp, mul4);
    return tmp;
}

unsigned int taylor_atan(unsigned int x) {  // atan
    unsigned int tmp1 = powg(x, 3);
    unsigned int tmp2 = powg(x, 5);
    unsigned int tmp3 = powg(x, 7);
    unsigned int tmp4 = powg(x, 9);
    unsigned int tmp5 = powg(x, 11);
    unsigned int mul1 = fmul_num(to_fpn(0.333333333), tmp1);
    unsigned int mul2 = fmul_num(to_fpn(0.2), tmp2);
    unsigned int mul3 = fmul_num(to_fpn(0.142857142), tmp3);
    unsigned int mul4 = fmul_num(to_fpn(0.111111111), tmp4);
    unsigned int mul5 = fmul_num(to_fpn(0.0909090909), tmp5);
    unsigned int tmp;
    tmp = fsub_num(x, mul1);
    tmp = fadd_num(tmp, mul2);
    tmp = fsub_num(tmp, mul3);
    tmp = fadd_num(tmp, mul4);
    tmp = fsub_num(tmp, mul5);
    return tmp;
}

// sin
unsigned int sing(unsigned int x) {
    return 0;
}

// cos
unsigned int cosg(unsigned int x) {
    return 0;
}

// atan
unsigned int atang(unsigned int x) {
    return 0;
}