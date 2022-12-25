#include "branch.h"
#include "register.h"
#include "library.h"

// read1 == read2 でジャンプ
void beq_num(unsigned int read1, unsigned int read2, unsigned int pc, unsigned int imm10, hazard* hzd) {
    if(read1 == read2) {
        hzd->j_flag = 1;
        hzd->new_pc = pc + to_signed(imm10, 10);
        if(pc == hzd->new_pc) {
            hzd->f_flag = 1;
        } else {
            hzd->f_flag = 0;
        }
    }
}

// read1 < read2 でジャンプ
void blt_num(unsigned int read1, unsigned int read2, unsigned int pc, unsigned int imm10, hazard* hzd) {
    if(read1 < read2) {
        hzd->j_flag = 1;
        hzd->new_pc = pc + to_signed(imm10, 10);
        if(pc == hzd->new_pc) {
            hzd->f_flag = 1;
        } else {
            hzd->f_flag = 0;
        }
    }
}

// read1 <= read2 でジャンプ
void ble_num(unsigned int read1, unsigned int read2, unsigned int pc, unsigned int imm10, hazard* hzd) {
    if(read1 <= read2) {
        hzd->j_flag = 1;
        hzd->new_pc = pc + to_signed(imm10, 10);
        if(pc == hzd->new_pc) {
            hzd->f_flag = 1;
        } else {
            hzd->f_flag = 0;
        }
    }
}

// 即値ジャンプ
void j_num(unsigned int pc, unsigned int imm26, hazard* hzd) {
    hzd->j_flag = 1;
    hzd->new_pc = pc + to_signed(imm26, 26);
    if(pc == hzd->new_pc) {
            hzd->f_flag = 1;
        } else {
            hzd->f_flag = 0;
        }
}

// アドレスを指定してジャンプ
void jr_num(unsigned int pc, unsigned int read2, hazard* hzd) {
    hzd->j_flag = 1;
    hzd->new_pc = read2;
    if(pc == hzd->new_pc) {
            hzd->f_flag = 1;
        } else {
            hzd->f_flag = 0;
        }
}