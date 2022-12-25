#include "print.h"
#include "library.h"
#include "register.h"
#include "instruction.h"
#include <stdio.h>

// オペコードの表示
void print_opecode(enum opecode op) {
    switch(op) {
        case OOO_op:    printf("opecode: 000"); break;
        case OOI_op:    printf("opecode: 001"); break;
        case OIO_op:    printf("opecode: 010"); break;
        case IOO_op:    printf("opecode: 100"); break;
        case IOI_op:    printf("opecode: 101"); break;
        case III_op:    printf("opecode: 111"); break;
        case IIO_op:    printf("opecode: 110"); break;
        case Undefined_opecode: printf("opecode: UNDEFINED"); break;
    }
}

// funct(5桁)の表示
void print_funct5(enum funct5 f5) {
    switch(f5) {
        case OOOOI: printf("funct5: 00001"); break;
        case OOOIO: printf("funct5: 00010"); break;
        case OOIOO: printf("funct5: 00100"); break;
        case OIOOO: printf("funct5: 01000"); break;
        case OIOOI: printf("funct5: 01001"); break;
        case OIOIO: printf("funct5: 01010"); break;
        case OIIOO: printf("funct5: 01100"); break;
        case IOOOO: printf("funct5: 10000"); break;
        case IOOOI: printf("funct5: 10001"); break;
        case IOOIO: printf("funct5: 10010"); break;
        case IOIOO: printf("funct5: 10100"); break;
        case IIOOO: printf("funct5: 11000"); break;
        case Undefined_funct5:  printf("funct5: UNDEFINED"); break;
    }
}

// funct(3桁)の表示
void print_funct3(enum funct3 f3) {
    switch(f3) {
        case OOI:   printf("funct3: 001"); break;
        case OIO:   printf("funct3: 010"); break;
        case IOO:   printf("funct3: 100"); break;
        case OOO:   printf("funct3: 000"); break;
        case Undefined_funct3:  printf("funct3: UNDEFINED"); break;
    }
}

// ニーモニック・使用レジスタの表示
void print_op(unit* un) {
    switch(identify_nemonic(un->rex->op, un->rex->f5, un->rex->f3)) {
        case ADD:   printf("op: add r%u r%u r%u", un->rex->dest, un->rex->src1, un->rex->src2); break;
        case SUB:   printf("op: sub r%u r%u r%u", un->rex->dest, un->rex->src1, un->rex->src2); break;
        case SLL:   printf("op: sll r%u r%u r%u", un->rex->dest, un->rex->src1, un->rex->src2); break;
        case SRL:   printf("op: srl r%u r%u r%u", un->rex->dest, un->rex->src1, un->rex->src2); break;
        case SRA:   printf("op: sra r%u r%u r%u", un->rex->dest, un->rex->src1, un->rex->src2); break;
        case FISPOS:   printf("op: fispos r%u r%u", un->rex->dest, un->rex->src2); break;
        case FISNEG:   printf("op: fisneg r%u r%u", un->rex->dest, un->rex->src2); break;
        case FNEG:  printf("op: fneg r%u r%u", un->rex->dest, un->rex->src2); break;
        case ADDI:  printf("op: addi r%u r%u %u", un->rex->dest, un->rex->src1, un->rex->imm8); break;
        case SUBI:  printf("op: subi r%u r%u %u", un->rex->dest, un->rex->src1, un->rex->imm8); break;
        case SLLI:  printf("op: slli r%u r%u %u", un->rex->dest, un->rex->src1, un->rex->imm8); break;
        case SRLI:  printf("op: srli r%u r%u %u", un->rex->dest, un->rex->src1, un->rex->imm8); break;
        case SRAI:  printf("op: srai r%u r%u %u", un->rex->dest, un->rex->src1, un->rex->imm8); break;
        case FADD:  printf("op: fadd r%u r%u r%u", un->rex->dest, un->rex->src1, un->rex->src2); break;
        case FSUB:  printf("op: fsub r%u r%u r%u", un->rex->dest, un->rex->src1, un->rex->src2); break;
        case FMUL:  printf("op: fmul r%u r%u r%u", un->rex->dest, un->rex->src1, un->rex->src2); break;
        case FDIV:  printf("op: fdiv r%u r%u r%u", un->rex->dest, un->rex->src1, un->rex->src2); break;
        case FLESS: printf("op: fless r%u r%u r%u", un->rex->dest, un->rex->src1, un->rex->src2); break;
        case FTOI:  printf("op: ftoi r%u r%u", un->rex->dest, un->rex->src2); break;
        case ITOF:  printf("op: itof r%u r%u", un->rex->dest, un->rex->src2); break;
        case FSQRT: printf("op: fsqrt r%u r%u", un->rex->dest, un->rex->src2); break;
        case BEQ:   printf("op: beq r%u r%u %d",un->rex->src1, un->rex->src2, to_signed(un->rex->imm10, 10)); break;
        case BLT:   printf("op: blt r%u r%u %d",un->rex->src1, un->rex->src2, to_signed(un->rex->imm10, 10)); break;
        case BLE:   printf("op: ble r%u r%u %d",un->rex->src1, un->rex->src2, to_signed(un->rex->imm10, 10)); break;
        case J:     printf("op: j %d", to_signed(un->rex->imm26, 26)); break;
        case JR:    printf("op: jr r%u", un->rex->src2); break;
        case LW:    printf("op: lw r%u r%u", un->rex->dest, un->rex->src2); break;
        case SW:    printf("op: sw r%u r%u", un->rex->src1, un->rex->src2); break;
        default:    printf("op: nop"); break;
    }
}

// 各ステージのレジスタの表示
void print_unit(unit* un) {
    // IFユニット
    printf("\nIF:\n");
    printf("pc: %u\n", un->pc);

    // RFユニット
    printf("\nRF\n");
    printf("inst32: %u   pc: %u\n", un->rrf->inst32, un->rrf->pc);

    // EXユニット
    printf("\nEX:\n");
    print_opecode(un->rex->op);
    printf("   ");
    print_funct5(un->rex->f5);
    printf("   ");
    print_funct3(un->rex->f3);
    printf("\n");
    printf("dest: %u   src1: %u   src2: %u\n", un->rex->dest, un->rex->src1, un->rex->src2);
    printf("read1: %u   read2: %u\n", un->rex->read1, un->rex->read2);
    printf("imm8: %u   imm10: %u   imm26: %u\n", un->rex->imm8, un->rex->imm10, un->rex->imm26);
    printf("pc: %u   ", un->rex->pc);
    print_op(un);
    printf("\n");

    // WBユニット
    printf("\nWB:\n");
    printf("WE: %u   dest: %u   data: %u\n", un->rwb->WE, un->rwb->dest, un->rwb->data);

    printf("\n");
}

// ソースレジスタの表示
void print_src(reg_set* regs) {
    printf("\nSrc:\n=====================================================================================\n");
    print_unit(regs->src);
    printf("=====================================================================================\n\n");
}

// 更新後レジスタの表示
void print_next(reg_set* regs) {
    printf("\nNext:\n=====================================================================================\n");
    print_unit(regs->next);
    printf("=====================================================================================\n\n");
}

// ハザードユニットの表示
void print_hzd(reg_set* regs) {
    printf("\nHazard:\n=====================================================================================\n\n");
    printf("j_flag: %u   ", regs->hzd->j_flag);
    printf("new_pc: %u   ", regs->hzd->new_pc);
    printf("f_flag: %u\n", regs->hzd->f_flag);
    printf("\n=====================================================================================\n\n");
}

// レジスタファイルの表示
void print_reg(reg_set* regs) {
    int i, j;
    printf("\nReg:\n=====================================================================================\n\n");
    for(i = 0; i * NEW_LINE < REG_SIZE; i++) {
        printf("%10d ", i);
        for(j = 0; j < NEW_LINE; j++) {
            printf("%08x ", regs->reg[i * NEW_LINE + j]);
        }
        printf("\n");
    }
    printf("\n=====================================================================================\n\n");
}

// メモリの表示
// 第一引数・第二引数で範囲(行単位)を指定
void print_mem(reg_set* regs, int start, int end) {
    long i;
    int j;
    printf("\nMem:\n=====================================================================================\n\n");
    for(i = (long)start; i <= (long)end && i * NEW_LINE < MEM_SIZE; i++) {
        printf("%10ld ", i);
        for(j = 0; j < NEW_LINE; j++) {
            printf("%08x ", regs->mem[i * NEW_LINE + j]);
        }
        printf("\n");
    }
    printf("\n=====================================================================================\n\n");
}