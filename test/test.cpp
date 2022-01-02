#include <stdio.h>
#include "FPGAgates.h"
#include "tap.h"


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


int main(){
    test_and() ;
    test_or() ;
    test_nand() ;
    test_nor() ;
    test_xor() ;
}
