#include "IF.h"
#include "register.h"


// IFステージ
void IF(reg_set* regs) {
    if(regs->hzd->j_flag) {
        flash_rrf(regs->next->rrf);
    } else {
        reg_rf* tgt = regs->next->rrf;
        unsigned int pc = regs->src->pc;
        tgt->inst32 = regs->mem[pc];
        tgt->pc = pc;
    }
}