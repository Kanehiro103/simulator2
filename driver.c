#include "driver.h"
#include "register.h"
#include "WB.h"
#include "EX.h"
#include "RF.h"
#include "IF.h"

// RFステージ用レジスタのコピー
void copy_rrf(reg_rf* rrf1, reg_rf* rrf2) {
    rrf1->inst32 = rrf2->inst32;
    rrf1->pc = rrf2->pc;
}

// EXステージ用レジスタのコピー
void copy_rex(reg_ex* rex1, reg_ex* rex2) {
    rex1->op = rex2->op;
    rex1->f5 = rex2->f5;
    rex1->f3 = rex2->f3;
    rex1->dest = rex2->dest;
    rex1->src1 = rex2->src1;
    rex1->src2 = rex2->src2;
    rex1->read1 = rex2->read1;
    rex1->read2 = rex2->read2;
    rex1->imm8 = rex2->imm8;
    rex1->imm10 = rex2->imm10;
    rex1->imm26 = rex2->imm26;
    rex1->pc = rex2->pc;
}

// WBステージ用レジスタのコピー
void copy_rwb(reg_wb* rwb1, reg_wb* rwb2) {
    rwb1->WE = rwb2->WE;
    rwb1->data = rwb2->data;
    rwb1->dest = rwb2->dest;
}

// 全ステージのレジスタのコピー
void copy(unit* un1, unit* un2) {
    un1->pc = un2->pc;
    copy_rrf(un1->rrf, un2->rrf);
    copy_rex(un1->rex, un2->rex);
    copy_rwb(un1->rwb, un2->rwb);
}

// 実行本体
void drive(reg_set* regs) {
    // コピー・ハザード初期化
    copy(regs->src, regs->next);
    flash_hzd(regs->hzd);

    // クロック
    regs->clk++;

    // WBステージ
    WB(regs);

    // EXステージ
    EX(regs);

    // RFステージ
    RF(regs);

    // IFステージ
    IF(regs);

    // pc更新
    if(regs->hzd->j_flag) {
        regs->next->pc = regs->hzd->new_pc;
    } else {
        regs->next->pc = regs->src->pc + 1;
    }
}