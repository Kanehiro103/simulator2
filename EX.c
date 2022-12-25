#include "EX.h"
#include "register.h"
#include "alu.h"
#include "fpu.h"
#include "branch.h"

// EXステージ
void EX(reg_set* regs) {
    reg_ex* src = regs->src->rex;
    reg_wb* tgt = regs->next->rwb;
    hazard* hzd = regs->hzd;
    
    unsigned int read1, read2;
    if(regs->src->rwb->WE && src->src1 == regs->src->rwb->dest) {
        read1 = regs->src->rwb->data;
    } else {
        read1 = src->read1;
    }
    if(regs->src->rwb->WE && src->src2 == regs->src->rwb->dest) {
        read2 = regs->src->rwb->data;
    } else {
        read2 = src->read2;
    }

    switch(identify_nemonic(src->op, src->f5, src->f3)) {
        case ADD:   tgt->WE = 1;
                    tgt->data = add_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case SUB:   tgt->WE = 1;
                    tgt->data = sub_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case SLL:   tgt->WE = 1;
                    tgt->data = sll_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case SRL:   tgt->WE = 1;
                    tgt->data = srl_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case SRA:   tgt->WE = 1;
                    tgt->data = sra_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case FISPOS:    tgt->WE = 1;
                        tgt->data = fispos_num(read2);
                        tgt->dest = src->dest;
                        break;
        case FISNEG:    tgt->WE = 1;
                        tgt->data = fisneg_num(read2);
                        tgt->dest = src->dest;
                        break;
        case FNEG:      tgt->WE = 1;
                        tgt->data = fneg_num(read2);
                        tgt->dest = src->dest;
                        break;
        case ADDI:  tgt->WE = 1;
                    tgt->data = addi_num(read1, src->imm8);
                    tgt->dest = src->dest;
                    break;
        case SUBI:  tgt->WE = 1;
                    tgt->data = subi_num(read1, src->imm8);
                    tgt->dest = src->dest;
                    break;
        case SLLI:  tgt->WE = 1;
                    tgt->data = slli_num(read1, src->imm8);
                    tgt->dest = src->dest;
                    break;
        case SRLI:  tgt->WE = 1;
                    tgt->data = srli_num(read1, src->imm8);
                    tgt->dest = src->dest;
                    break;
        case SRAI:  tgt->WE = 1;
                    tgt->data = srai_num(read1, src->imm8);
                    tgt->dest = src->dest;
                    break;
        case FADD:  tgt->WE = 1;
                    tgt->data = fadd_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case FSUB:  tgt->WE = 1;
                    tgt->data = fsub_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case FMUL:  tgt->WE = 1;
                    tgt->data = fmul_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case FDIV:  tgt->WE = 1;
                    tgt->data = fdiv_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case FLESS: tgt->WE = 1;
                    tgt->data = fless_num(read1, read2);
                    tgt->dest = src->dest;
                    break;
        case FTOI:  tgt->WE = 1;
                    tgt->data = ftoi_num(read2);
                    tgt->dest = src->dest;
                    break;
        case ITOF:  tgt->WE = 1;
                    tgt->data = itof_num(read2);
                    tgt->dest = src->dest;
                    break;
        case FSQRT: tgt->WE = 1;
                    tgt->data = fsqrt_num(read2);
                    tgt->dest = src->dest;
                    break;
        case BEQ:   flash_rwb(tgt);
                    beq_num(read1, read2, src->pc, src->imm10, hzd);
                    break;
        case BLT:   flash_rwb(tgt);
                    blt_num(read1, read2, src->pc, src->imm10, hzd);
                    break;
        case BLE:   flash_rwb(tgt);
                    ble_num(read1, read2, src->pc, src->imm10, hzd);
                    break;
        case J:     flash_rwb(tgt);
                    j_num(src->pc, src->imm26, hzd);
                    break;
        case JR:    flash_rwb(tgt);
                    jr_num(src->pc, read2, hzd);
                    break;
        case LW:    tgt->WE = 1;
                    tgt->data = regs->mem[read2];
                    tgt->dest = src->dest;
                    break;
        case SW:    flash_rwb(tgt);
                    regs->mem[read2] = read1;
                    break;
        default:    break;
    }
}