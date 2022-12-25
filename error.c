#include "error.h"
#include "fpu.h"
#include "library.h"
#include <stdio.h>
#include <math.h>

// (fadd x1 x2) のシミュレート結果と、実際の x1 + x2 の相対誤差
void fadd_rerror(float x1, float x2) {
    union fi f1, f2;
    f1.f = x1;
    f2.f = x2;
    float ans = x1 + x2;
    float sim = to_float(fadd_num(f1.i, f2.i));
    printf("sim:   %f\n", sim);
    printf("ans:   %f\n", ans);
    printf("error: %f\n", (sim - ans) / ans);
}

// (fsub x1 x2) のシミュレート結果と、実際の x1 - x2 の相対誤差
void fsub_rerror(float x1, float x2) {
    union fi f1, f2;
    f1.f = x1;
    f2.f = x2;
    float ans = x1 - x2;
    float sim = to_float(fsub_num(f1.i, f2.i));
    printf("sim:   %f\n", sim);
    printf("ans:   %f\n", ans);
    printf("error: %f\n", (sim - ans) / ans);
}

// (fmul x1 x2) のシミュレート結果と、実際の x1 * x2 の相対誤差
void fmul_rerror(float x1, float x2) {
    union fi f1, f2;
    f1.f = x1;
    f2.f = x2;
    float ans = x1 * x2;
    float sim = to_float(fmul_num(f1.i, f2.i));
    printf("sim:   %f\n", sim);
    printf("ans:   %f\n", ans);
    printf("error: %f\n", (sim - ans) / ans);
}

// (fdiv x1 x2) のシミュレート結果と、実際の x1 / x2 の相対誤差
void fdiv_rerror(float x1, float x2) {
    union fi f1, f2;
    f1.f = x1;
    f2.f = x2;
    float ans = x1 / x2;
    float sim = to_float(fdiv_num(f1.i, f2.i));
    printf("sim:   %f\n", sim);
    printf("ans:   %f\n", ans);
    printf("error: %f\n", (sim - ans) / ans);
}

// (fsqrt x) のシミュレート結果と、実際の sqrtf(x) の相対誤差
void fsqrt_rerror(float x) {
    union fi f;
    f.f = x;
    float ans = sqrtf(x);
    float sim = to_float(fsqrt_num(f.i));
    printf("sim:   %f\n", sim);
    printf("ans:   %f\n", ans);
    printf("error: %f\n", (sim - ans) / ans);
}

// (finv x) のシミュレート結果と、実際の 1.0 / x の相対誤差
void finv_rerror(float x) {
    union fi f;
    f.f = x;
    float ans = 1.0 / x;
    float sim = to_float(finv_num(f.i));
    printf("sim:   %f\n", sim);
    printf("ans:   %f\n", ans);
    printf("error: %f\n", (sim - ans) / ans);
}

// (fadd x1 x2) のシミュレート結果と、実際の x1 + x2 の絶対誤差
void fadd_aerror(float x1, float x2) {
    union fi f1, f2;
    f1.f = x1;
    f2.f = x2;
    float ans = x1 + x2;
    float sim = to_float(fadd_num(f1.i, f2.i));
    printf("sim:   %f\n", sim);
    printf("ans:   %f\n", ans);
    printf("error: %f\n", sim - ans);
}

// (fsub x1 x2) のシミュレート結果と、実際の x1 - x2 の絶対誤差
void fsub_aerror(float x1, float x2) {
    union fi f1, f2;
    f1.f = x1;
    f2.f = x2;
    float ans = x1 - x2;
    float sim = to_float(fsub_num(f1.i, f2.i));
    printf("sim:   %f\n", sim);
    printf("ans:   %f\n", ans);
    printf("error: %f\n", sim - ans);
}

// (fmul x1 x2) のシミュレート結果と、実際の x1 * x2 の絶対誤差
void fmul_aerror(float x1, float x2) {
    union fi f1, f2;
    f1.f = x1;
    f2.f = x2;
    float ans = x1 * x2;
    float sim = to_float(fmul_num(f1.i, f2.i));
    printf("sim:   %f\n", sim);
    printf("ans:   %f\n", ans);
    printf("error: %f\n", sim - ans);
}

// (fdiv x1 x2) のシミュレート結果と、実際の x1 / x2 の絶対誤差
void fdiv_aerror(float x1, float x2) {
    union fi f1, f2;
    f1.f = x1;
    f2.f = x2;
    float ans = x1 / x2;
    float sim = to_float(fdiv_num(f1.i, f2.i));
    printf("sim:   %f\n", sim);
    printf("ans:   %f\n", ans);
    printf("error: %f\n", sim - ans);
}

// (fsqrt x) のシミュレート結果と、実際の sqrtf(x) の絶対誤差
void fsqrt_aerror(float x) {
    union fi f;
    f.f = x;
    float ans = sqrtf(x);
    float sim = to_float(fsqrt_num(f.i));
    printf("sim:   %f\n", sim);
    printf("ans:   %f\n", ans);
    printf("error: %f\n", sim - ans);
}

// (finv x) のシミュレート結果と、実際の 1.0 / x の接待誤差
void finv_aerror(float x) {
    union fi f;
    f.f = x;
    float ans = 1.0 / x;
    float sim = to_float(finv_num(f.i));
    printf("sim:   %f\n", sim);
    printf("ans:   %f\n", ans);
    printf("error: %f\n", sim - ans);
}

// 二項演算子
void error2(int i, float x1, float x2) {
    switch(i) {
        case 1: fadd_rerror(x1, x2); break;
        case 2: fsub_rerror(x1, x2); break;
        case 3: fmul_rerror(x1, x2); break;
        case 4: fdiv_rerror(x1, x2); break;
        case -1: fadd_aerror(x1, x2); break;
        case -2: fsub_rerror(x1, x2); break;
        case -3: fmul_rerror(x1, x2); break;
        case -4: fdiv_rerror(x1, x2); break;
        default: printf("%d\n", 0);
    }
    printf("\n");
}

// 単項演算子
void error1(int i, float x) {
    switch(i) {
        case 5: fsqrt_rerror(x); break;
        case 6: finv_rerror(x); break;
        case -5: fsqrt_aerror(x); break;
        case -6: finv_aerror(x); break;
        default: printf("%d\n", 0);
    }
    printf("\n");
}