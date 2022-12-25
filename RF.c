#include "RF.h"
#include "register.h"
#include "instruction.h"
#include "library.h"

// RFステージ
void RF(reg_set* regs) {
    if(regs->hzd->j_flag) {
        flash_rex(regs->next->rex);
    } else {
        unsigned int tmp = regs->src->rrf->inst32;
        reg_ex* tgt = regs->next->rex;
        tgt->op = identify_opecode(tmp);
        tgt->f5 = identify_funct5(tmp);
        tgt->f3 = identify_funct3(tmp);
        tgt->dest = cut(tmp, 23, 16);
        unsigned int src1 = cut(tmp, 15, 8);
        unsigned int src2 = cut(tmp, 7, 0);
        tgt->src1 = src1;
        tgt->src2 = src2;
        tgt->read1 = regs->reg[src1];
        tgt->read2 = regs->reg[src2];
        tgt->imm8 = cut(tmp, 7, 0);
        tgt->imm10 = cut(tmp, 25, 16);
        tgt->imm26 = cut(tmp, 25, 0);
        tgt->pc = regs->src->rrf->pc;
    }
}