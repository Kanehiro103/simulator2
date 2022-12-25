#ifndef _BRANCH_H_
#define _BRANCH_H_

#include "register.h"

// ジャンプ命令
void beq_num(unsigned int, unsigned int, unsigned int, unsigned int, hazard*);
void blt_num(unsigned int, unsigned int, unsigned int, unsigned int, hazard*);
void ble_num(unsigned int, unsigned int, unsigned int, unsigned int, hazard*);
void j_num(unsigned int, unsigned int, hazard*);
void jr_num(unsigned int, unsigned int, hazard*);

#endif