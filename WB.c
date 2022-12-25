#include "WB.h"
#include "register.h"

// WBステージ
void WB(reg_set* regs) {
    if(regs->src->rwb->WE) {
        regs->reg[regs->src->rwb->dest] = regs->src->rwb->data;
    }
}