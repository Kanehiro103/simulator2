#include "alu.h"
#include "library.h"

// 整数の加算
unsigned int add_num(unsigned int read1, unsigned int read2) {
    return read1 + read2;
}

// 整数の減算
unsigned int sub_num(unsigned int read1, unsigned int read2) {
    return read1 - read2;
}

// 左シフト
unsigned int sll_num(unsigned int read1, unsigned int read2) {
    return read1 << read2;
}

// 右論理シフト
unsigned int srl_num(unsigned int read1, unsigned int read2) {
    return read1 >> read2;
}

// 右算術シフト
unsigned int sra_num(unsigned int read1, unsigned int read2) {
    unsigned int s = cut(read1, 31, 31);
    return (s << 31) + (cut(read1, 30, 0) >> read2);
}

// 即値の加算
unsigned int addi_num(unsigned int read1, unsigned int imm8) {
    return read1 + imm8;
}

// 即値の減算
unsigned int subi_num(unsigned int read1, unsigned int imm8) {
    return read1 - imm8;
}

// 即値による左シフト
unsigned int slli_num(unsigned int read1, unsigned int imm8) {
    return read1 << imm8;
}

// 即値による右論理シフト
unsigned int srli_num(unsigned int read1, unsigned int imm8) {
    return read1 >> imm8;
}

// 即値による右算術シフト
unsigned int srai_num(unsigned read1, unsigned int imm8) {
    unsigned int s = cut(read1, 31, 31);
    return (s << 31) + (cut(read1, 30, 0) >> imm8);
}

// 浮動小数点数が正であるか否か
// 正ならば0, 0以下ならば1
unsigned int fispos_num(unsigned int x2) {
    if(cut(x2, 31, 31)) {
        return 0;
    } else {
        if(x2 == 0) {
            return 0;
        } else {
            return 1;
        }
    }
}

// 浮動小数点数が負であるか否か
// 負ならば1, 0以上ならば1
unsigned int fisneg_num(unsigned int x2) {
    if(cut(x2, 31, 31)) {
        return 1;
    } else {
        return 0;
    }
}

// 浮動小数点数の符号反転
unsigned int fneg_num(unsigned int x2) {
    if(cut(x2, 31, 31)) {
        return cut(x2, 30, 0);
    } else {
        return x2 + (1 << 31);
    }
}