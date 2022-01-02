#include <stdio.h>
#include "FPGAgates.h"
#include "tap.h"


void test_buf(){
    wire a, b ;
    buf_(a, b) ;

    for (int va = 0 ; va < 2 ; va++){
        a.set(va) ;
        settle() ;
        bool res = va ;
        ok(b.get() == res, "%d == %d", a.get(), res) ;
    }
}


void test_not(){
    wire a, b ;
    not_(a, b) ;

    for (int va = 0 ; va < 2 ; va++){
        a.set(va) ;
        settle() ;
        bool res = ~va ;
        ok(b.get() == res, "~%d == %d", a.get(), res) ;
    }
}


void test_and(){
    wire a, b, c ;
    and_(a, b, c) ;

    for (int va = 0 ; va < 2 ; va++){
        for (int vb = 0 ; vb < 2 ; vb++){
            a.set(va) ;
            b.set(vb) ;
            settle() ;
            bool res = va & vb ;
            ok(c.get() == res, "%d & %d == %d", a.get(), b.get(), res) ;
        }
    }
}


void test_or(){
    wire a, b, c ;
    or_(a, b, c) ;

    for (int va = 0 ; va < 2 ; va++){
        for (int vb = 0 ; vb < 2 ; vb++){
            a.set(va) ;
            b.set(vb) ;
            settle() ;
            bool res = va | vb ;
            ok(c.get() == res, "%d | %d == %d", a.get(), b.get(), res) ;
        }
    }
}


void test_nand(){
    wire a, b, c ;
    nand_(a, b, c) ;

    for (int va = 0 ; va < 2 ; va++){
        for (int vb = 0 ; vb < 2 ; vb++){
            a.set(va) ;
            b.set(vb) ;
            settle() ;
            bool res = ~(va & vb) ;
            ok(c.get() == res, "~(%d & %d) == %d", a.get(), b.get(), res) ;
        }
    }
}


void test_nor(){
    wire a, b, c ;
    nor_(a, b, c) ;

    for (int va = 0 ; va < 2 ; va++){
        for (int vb = 0 ; vb < 2 ; vb++){
            a.set(va) ;
            b.set(vb) ;
            settle() ;
            bool res = ~(va | vb) ;
            ok(c.get() == res, "~(%d | %d) == %d", a.get(), b.get(), res) ;
        }
    }
}


void test_xor(){
    wire a, b, c ;
    xor_(a, b, c) ;

    for (int va = 0 ; va < 2 ; va++){
        for (int vb = 0 ; vb < 2 ; vb++){
            a.set(va) ;
            b.set(vb) ;
            settle() ;
            bool res = va ^ vb ;
            ok(c.get() == res, "%d ^ %d == %d", a.get(), b.get(), res) ;
        }
    }
}


void test_add(){
    wire a, b, ci, c, co ;
    add_(a, b, ci, c, co) ;

    for (int va = 0 ; va < 2 ; va++){
        for (int vb = 0 ; vb < 2 ; vb++){
            for (int vci = 0 ; vci < 2 ; vci++){
                a.set(va) ;
                b.set(vb) ;
                ci.set(vci) ;
                settle() ;
                uint8_t sum = va + vb + vci ;
                bool cy = sum >> 1 ;
                sum = sum & 1 ;
                ok(c.get() == sum, "sum(%d + %d + %d) == %d", a.get(), b.get(), ci.get(), sum) ;
                ok(co.get() == cy, "cy(%d + %d + %d) == %d", a.get(), b.get(), ci.get(), cy) ;
            }
        }
    }
}


int main(){
    test_buf() ;
    test_not() ;
    test_and() ;
    test_or() ;
    test_nand() ;
    test_nor() ;
    test_xor() ;
    test_add() ;
}
