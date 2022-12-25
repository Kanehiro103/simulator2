#include "register.h"
#include "instruction.h"
#include <stdlib.h>

// RFステージ用レジスタの初期化
void flash_rrf(reg_rf* rrf) {
    rrf->inst32 = 0;
    rrf->pc = 0;
}

// EXステージ用レジスタの初期化
void flash_rex(reg_ex* rex) {
    rex->op = Undefined_opecode;
    rex->f5 = Undefined_funct5;
    rex->f3 = Undefined_funct3;
    rex->dest = 0;
    rex->src1 = 0;
    rex->src2 = 0;
    rex->read1 = 0;
    rex->read2 = 0;
    rex->imm8 = 0;
    rex->imm10 = 0;
    rex->imm26 = 0;
    rex->pc = 0;
}

// WB用レジスタの初期化
void flash_rwb(reg_wb* rwb) {
    rwb->WE = 0;
    rwb->dest = 0;
    rwb->data = 0;
}

// 全ステージの初期化
void init_unit(unit* un) {
    un->pc = 0;
    un->rrf = (reg_rf*)malloc(sizeof(reg_rf));
    flash_rrf(un->rrf);
    un->rex = (reg_ex*)malloc(sizeof(reg_ex));
    flash_rex(un->rex);
    un->rwb = (reg_wb*)malloc(sizeof(reg_wb));
    flash_rwb(un->rwb);
}

// ハザードユニットの初期化
void flash_hzd(hazard* hzd) {
    hzd->j_flag = 0;
    hzd->new_pc = 0;
    hzd->f_flag = 0;
}

// 全体の初期化
void init_regs(reg_set* regs) {
    regs->clk = 0;
    regs->src = (unit*)malloc(sizeof(unit));
    init_unit(regs->src);
    regs->next = (unit*)malloc(sizeof(unit));
    init_unit(regs->next);
    regs->hzd = (hazard*)malloc(sizeof(hazard));
    flash_hzd(regs->hzd);
    regs->reg = (unsigned int*)calloc(REG_SIZE, sizeof(unsigned int));
    regs->mem = (unsigned int*)calloc(MEM_SIZE, sizeof(unsigned int ));
}

// 各ステージの解放
void free_unit(unit* un) {
    free(un->rrf);
    free(un->rex);
    free(un->rwb);
    free(un);
}

// 全体の解放
void free_regs(reg_set* regs) {
    free_unit(regs->src);
    free_unit(regs->next);
    free(regs->hzd);
    free(regs->reg);
    free(regs->mem);
    free(regs);
}