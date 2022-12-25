#include "fpu.h"
#include "library.h"
#include "grad_list.h"
#include <math.h>

// 浮動小数点数の加算
unsigned int fadd_num(unsigned int read1, unsigned int read2) {
    unsigned int s1 = cut(read1, 31, 31);   //符号
    unsigned int s2 = cut(read2, 31, 31);
    unsigned int e1 = cut(read1, 30, 23);   //指数部
    unsigned int e2 = cut(read2, 30, 23);
    unsigned int m1 = cut(read1, 22, 0);    //仮数部
    unsigned int m2 = cut(read2, 22, 0);

    unsigned int m1a = m1 + pow2(23);   //ケチ表現の再生
    unsigned int m2a = m2 + pow2(23);

    unsigned int nzm1, nzm2;

    if(m1 == 0) {
        nzm1 = 0;
    } else {
        nzm1 = 1;
    }
    if(m2 == 0) {
        nzm2 = 0;
    } else {
        nzm2 = 1;
    }

    //無限大処理
    if(e1 == 255 && e2 != 255) {
        return fpn(s1, 255, nzm1 * pow2(22) + cut(m1, 21, 0));
    } else if(e1 != 255 && e2 == 255) {
        return fpn(s2, 255, nzm2 * pow2(22) + cut(m2, 21, 0)); 
    } else if(e1 == 255 && e2 == 255) {
        if(nzm2 != 0) {
            return fpn(s2, 255, pow2(22) + cut(m2, 21, 0));
        } else if(nzm1 != 0) {
            return fpn(s1, 255, pow2(22) + cut(m1, 21, 0));
        } else if(s1 == s2) {
            return fpn(s1, 255, 0);
        } else {
            return fpn(1, 255, pow2(22));
        }
    } else {
        //オペランドが両方とも有限の場合
        unsigned int i;
        unsigned int e1a, e2a;
        unsigned int te;
        unsigned int ce, tde;
        unsigned int de;
        unsigned int sel;
        unsigned int ms, mi, es, ei, ss;
        unsigned long mie; 
        unsigned long mia;
        unsigned int tstck;
        unsigned int mye;
        unsigned int esi;
        unsigned int eyd, myd, stck;
        unsigned int se;
        unsigned int eyf;
        unsigned int eyr, myf;
        unsigned int myr;
        unsigned int eyri;
        unsigned int ey, my;
        unsigned int sy;

        e1a = e1;
        e2a = e2;

        te = pow2(8) - 1 + e1a - e2a;

        if(cut(te, 8, 8) == 1) {
            ce = 0;
            tde = cut(te + 1, 7, 0);
        } else {
            ce = 1;
            tde = cut(pow2(8) - 1 - te, 7, 0);
        }

        if(tde > 31) {
            de = 31;
        } else {
            de = tde;
        }

        if(de == 0) {
            if(m1a > m2a) {
                sel = 0;
            } else {
                sel = 1;
            }
        } else {
            sel = ce;
        }

        if(sel == 0) {
            ms = m1a;
            mi = m2a;
            es = e1a;
            ei = e2a;
            ss = s1;
        } else {
            ms = m2a;
            mi = m1a;
            es = e2a;
            ei = e1a;
            ss = s2;
        }

        mie = (unsigned long)mi << 31;

        mia = mie >> de;

        if(cut_ul(mia, 28, 0) == 0) {
            tstck = 0;
        } else {
            tstck = 1;
        }

        if(s1 == s2) {
            mye = (ms << 2) + (unsigned int)cut_ul(mia, 55, 29);
        } else {
            mye = (ms << 2) - (unsigned int)cut_ul(mia, 55, 29);
        }


        esi = es + 1;

        if(cut(mye, 26, 26) == 1) {
            if(esi == 255) {
                eyd = 255;
                myd = pow2(25);
                stck = 0;
            } else {
                eyd = esi;
                myd = mye >> 1;
                if(tstck == 1 || cut(mye, 0, 0) == 1) {
                    stck = 1;
                } else {
                    stck = 0;
                }
            }
        } else {
            eyd = es;
            myd = mye;
            stck = tstck;
        }

        se = 26;
        for(i = 0; i < 26; i++) {
            if(cut(myd, 25 - i, 25 - i) != 0) {
                se = i;
                break;
            }
        }

        eyf = eyd - se;

        if(eyf > 0) {
            myf = myd << se;
            eyr = cut(eyf, 7, 0);
        } else {
            myf = myd << (cut(eyd, 4, 0) - 1);
            eyr = 0;
        }

        if(cut(myf, 1, 1) == 1 && cut(myf, 0, 0) == 0 && stck == 0 && cut(myf, 2, 2) == 1) {
            myr = cut(myf, 26, 2) + 1;
        } else if(cut(myf, 1, 1) == 1 && cut(myf, 0, 0) == 0 && s1 == s2 && stck == 1) {
            myr = cut(myf, 26, 2) + 1;
        } else if(cut(myf, 1, 1) == 1 && cut(myf, 0, 0) == 1) {
            myr = cut(myf, 26, 2) + 1;
        } else {
            myr = cut(myf, 26, 2);
        }

        eyri = eyr + 1;

        if(cut(myr, 24, 24) == 1) {
            ey = eyri;
            my = 0;
        } else {
            if(cut(myr, 23, 0) == 0) {
                ey = 0;
                my = 0;
            } else {
                ey = eyr;
                my = cut(myr, 22, 0);
            }
        }

        if(ey == 0 && my == 0) {
            if(s1 == 1 && s2 == 1) {
                sy = 1;
            } else {
                sy = 0;
            }
        } else {
            sy = ss;
        }

        return fpn(sy, ey, my);
    }
}

// 浮動小数点数の減算
unsigned int fsub_num(unsigned int read1, unsigned int read2) {
    unsigned int read2_opp;    // -read2

    if(cut(read2, 31, 31) == 0) {
        read2_opp = read2 + pow2(31);
    } else {
        read2_opp = read2 - pow2(31);
    }

    return fadd_num(read1, read2_opp);
}

// 浮動小数点数の乗算
unsigned int fmul_num(unsigned int read1, unsigned int read2) {
    unsigned int s1 = cut(read1, 31, 31);
    unsigned int s2 = cut(read2, 31, 31);
    unsigned int e1 = cut(read1, 30, 23);
    unsigned int e2 = cut(read2, 30, 23);
    unsigned int h1 = cut(read1, 22, 11) + pow2(12);
    unsigned int h2 = cut(read2, 22, 11) + pow2(12);
    unsigned int l1 = cut(read1, 10, 0);
    unsigned int l2 = cut(read2, 10, 0);
    unsigned int hh;
    unsigned int hl;
    unsigned int lh;
    unsigned int e_tmp;
    unsigned int s;
    unsigned int hh_hl_lh;
    unsigned int e_p1;
    unsigned int ovf, unf;
    unsigned int m;
    unsigned int e;

    hh = h1 * h2;
    hl = h1 * l2;
    lh = l1 * h2;

    e_tmp = e1 + e2 + 129;

    if(s1 == s2) {
        s = 0;
    } else {
        s = 1;
    }

    hh_hl_lh = hh + (hl >> 11) + (lh >> 11) + 2;

    e_p1 = e_tmp + 1;

    if(cut(e_tmp, 8, 7) == 0) {
        ovf = 1;
        unf = 0;
    } else if(cut(e_tmp, 8, 7) == 1) {
        ovf = 0;
        unf = 1;
    } else {
        ovf = 0;
        unf = 0;
    }

    if(ovf == 1 || unf == 1) {
        m = 0;
    } else {
        if(cut(hh_hl_lh, 25, 25) == 1) {
            m = cut(hh_hl_lh, 24, 2);
        } else {
            m = cut(hh_hl_lh, 23, 1);
        }
    }

    if(ovf == 1) {
        e = 0;
    } else {
        if(unf == 1) {
            e = 255;
        } else {
            if(cut(hh_hl_lh, 25, 25) == 1) {
                e = cut(e_p1, 7, 0);
            } else {
                e = cut(e_tmp, 7, 0);
            }
        }
    }

    if(cut(read1, 30, 0) != 0 && cut(read2, 30, 0) != 0) {
        return fpn(s, cut(e, 7, 0), m);
    } else {
        return 0;
    }
}

// 浮動小数点数の逆数
unsigned int finv_num(unsigned int x1) {
    unsigned int s1 = cut(x1, 31, 31);
    unsigned int e1 = cut(x1, 30, 23);
    unsigned int m1 = cut(x1, 22, 0);
    unsigned int index;
    unsigned long Q;
    unsigned int a, b;
    unsigned int e_a;
    unsigned int x1_mul, x2_mul;
    unsigned int m1_inv_sub;
    unsigned int x1_sub;
    unsigned int m1_inv;
    unsigned int s, e, m;

    index = cut(m1, 22, 13);

    Q = finv_list[index];

    a = (unsigned int)cut_ul(Q, 34, 23);
    b = (unsigned int)cut_ul(Q, 22, 0);

    if(cut_ul(Q, 35, 35) == 0) {
        e_a = 0b01111110;
    } else {
        e_a = 0b01111101;
    }

    x1_mul = fpn(0, e_a, a * pow2(11));
    x2_mul =  fpn(0, 0b01111111, m1);
    m1_inv_sub = fmul_num(x1_mul, x2_mul);

    x1_sub = fpn(0, 0b01111111, b);
    m1_inv = fsub_num(x1_sub, m1_inv_sub);
    
    s = s1;
    if(m1 != 0) {
        e = 0b11111101 - e1;
    } else {
        e = 0b11111110 - e1;
    }
    m = cut(m1_inv, 22, 0);

    return fpn(s, e, m);
}

// 浮動小数点数の除算
unsigned int fdiv_num(unsigned int read1, unsigned int read2) {
    unsigned int read2_inv = finv_num(read2);
    return fmul_num(read1, read2_inv);
}

// 浮動小数点数の比較
// x1 < x2 なら1, そうでないなら0
unsigned int fless_num(unsigned int x1, unsigned int x2) {
    if(to_float(x1) < to_float(x2)) {
        return 1;
    } else {
        return 0;
    }
}

// 浮動小数点数の内部表現を整数に変換
// 小数点以下四捨五入
unsigned int ftoi_num(unsigned int x2) {
    return (unsigned int)(round(to_float(x2)));
}

// 最初に 1 が立つ桁を求める
// 全部 0 だったら -1
int top(unsigned int num32) {
    int i;
    for(i = 31; i >= 0; i--) {
        if(cut(num32, i, i) == 1) {
            break;
        }
    }
    return i;
}

// 非負整数を受け取り、浮動小数点数に直す場合の指数部と仮数部を求める
void itof_plus(unsigned int int32, unsigned int* e, unsigned int* m) {
    int i = top(int32);
    if(i < 0) {
        *e = 0;
        *m = 0;
    } else if(i == 0){
        *e = 127;
        *m = 0;
    } else {
        unsigned long a = (unsigned long)int32 << 22;
        *e = 127 + i;
        *m = cut_ul(a, i + 21, i - 1);
    }
}

// 整数型の数を受け取り、浮動小数点型(の内部表現)に変換
unsigned int itof_num(unsigned int int32) {
    unsigned int e, m;
    int i = top(int32);
    if(i == 31) {
        itof_plus(-int32, &e, &m);
        return fpn(1, e, m);
    } else {
        itof_plus(int32, &e, &m);
        return fpn(0, e, m);
    }
}

// 浮動小数点数の平方根
unsigned int fsqrt_num(unsigned int x2) {
    unsigned int s1, e1, m1;
    unsigned int index_m, index_e, index;
    unsigned long Q;
    unsigned int a, b;
    unsigned int e_a;
    unsigned int x2_e;
    unsigned int x1_fmul, x2_fmul;
    unsigned int m1_sqrt_before_add;
    unsigned int x1_fadd;
    unsigned int m1_sqrt;
    unsigned int s, e, m;

    s1 = cut(x2, 31, 31);
    e1 = cut(x2, 30, 23);
    m1 = cut(x2, 22, 0);

    index_m = cut(m1, 22, 14);
    if(cut(e1, 0, 0)) {
        index_e = 0;
    } else {
        index_e = 1;
    }
    index = (index_e << 9) + index_m;

    Q = fsqrt_list[index];
    a = (unsigned int)cut_ul(Q, 35, 23);
    b = (unsigned int)cut_ul(Q, 22, 0);

    e_a = 0b01111101;
    if(cut(e1, 0, 0) == 1) {
        x2_e = 0b01111111;
    } else {
        x2_e = 0b10000000;
    }
    x1_fmul = fpn(0, e_a, (a << 10));
    x2_fmul = fpn(0, x2_e, m1);

    m1_sqrt_before_add = fmul_num(x1_fmul, x2_fmul);
    x1_fadd = fpn(0, 0b01111110, b);

    m1_sqrt = fadd_num(x1_fadd, m1_sqrt_before_add);

    s = s1;
    if(cut(e1, 0, 0) == 1) {
        e = cut(m1_sqrt, 30, 23) + ((e1 + 1) >> 1) - 64;
    } else {
        e = cut(m1_sqrt, 30, 23) + (e1 >> 1) - 64;
    }
    m = cut(m1_sqrt, 22, 0);
    
    return fpn(s, e, m);
}