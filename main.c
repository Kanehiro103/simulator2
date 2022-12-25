#include "register.h"
#include "print.h"
#include "driver.h"
#include "read.h"
#include "error.h"
#include "pseudo.h"
#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    ///*
    if(argc <= 1) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 0;
    }

    if(strcmp(argv[1], "#error") == 0) {    // 誤差計算
        int i;
        while(1) {
            printf("0:quit   1:add   2:sub   3:mul   4:div   5:sqrt   6:inv\n");
            scanf("%d", &i);
            if(i == 0) {
                break;
            } else if(-4 <= i && i <= 4) {
                float x1, x2;
                printf("x1: ");
                scanf("%f", &x1);
                printf("x2: ");
                scanf("%f", &x2);
                error2(i, x1, x2);
            } else if((-6 <= i && i <= -5) || (5 <= i && i <= 6)) {
                float x;
                printf("x: ");
                scanf("%f", &x);
                error1(i, x);
            }
        }
    } else {        // コアシミュレーション
        char* samples = "./samples/";
        char* dat = ".dat";
        char read_file[128];
        sprintf(read_file, "%s%s%s", samples, argv[1], dat);

        reg_set* regs = (reg_set*)malloc(sizeof(reg_set));
        init_regs(regs);

        if(read(regs, read_file)) {
            printf("file not found\n");
            exit(1);
        }

        while(!regs->hzd->f_flag) {
            drive(regs);
            if(regs->clk > 130) {
                print_src(regs);
            }
        }
    
        print_src(regs);
        print_next(regs);
        print_hzd(regs);
        print_reg(regs);
        printf("clk: %d\n\n", regs->clk);
        free_regs(regs);
    }
    //*/
    /*
    unsigned int x = to_fpn(4.91);
    printf("%x\n", x);
    */
    return 0;
}