#ifndef _PRINT_H_
#define _PRINT_H_

#include "register.h"

#define NEW_LINE 8

// 各種レジスタの表示
void print_src(reg_set*);   // ソースレジスタ
void print_next(reg_set*);  // 更新後レジスタ
void print_hzd(reg_set*);   // ハザードユニット
void print_reg(reg_set*);   // レジスタファイル
void print_mem(reg_set*, int, int); // メモリ

#endif