#ifndef _REGISTER_H_
#define _REGISTER_H_

#include "instruction.h"

#define REG_SIZE 256
#define MEM_SIZE 4294967296

// RFステージ用レジスタ
typedef struct {
    unsigned int inst32;
    unsigned int pc;
} reg_rf;

// EXステージ用レジスタ
typedef struct {
    enum opecode op;
    enum funct5 f5;
    enum funct3 f3;
    unsigned int dest;
    unsigned int src1;
    unsigned int src2;
    unsigned int read1;
    unsigned int read2;
    unsigned int imm8;
    unsigned int imm10;
    unsigned int imm26;
    unsigned int pc;
} reg_ex;

// WBステージ用レジスタ
typedef struct {
    unsigned int WE;
    unsigned int dest;
    unsigned int data;
} reg_wb;

// ステージ全体
typedef struct {
    unsigned int pc;    // IFステージ
    reg_rf* rrf;    // RFステージ
    reg_ex* rex;    // EXステージ
    reg_wb* rwb;    // WBステージ
} unit;

// ハザードユニット
typedef struct {
    unsigned int j_flag;    // 分岐するか否か
    unsigned int new_pc;    // 分岐先
    unsigned int f_flag;    // 実行を終了するか否か
} hazard;

// レジスタ全体
typedef struct {
    unsigned int clk;   // クロック
    unit* src;  // ソースレジスタ
    unit* next; // 更新後レジスタ
    hazard* hzd;    // ハザードユニット
    unsigned int* reg;  // レジスタファイル
    unsigned int* mem;  // メモリ
} reg_set;

// 各種初期化
void flash_rrf(reg_rf*);    // RFステージ
void flash_rex(reg_ex*);    // EXステージ
void flash_rwb(reg_wb*);    // EBステージ
void flash_hzd(hazard*);    // ハザードユニット
void init_regs(reg_set*);   // 全体

// 領域解放
void free_regs(reg_set*);

#endif