#include <stdio.h>
#include "FPGAgates.h"
#include "tap.h"


void wire_set(wire w, bool v) ;
bool wire_get(wire w) ;


void test_buf(){
    wire a, b ;
    buf_(a, b) ;

    for (int va = 0 ; va < 2 ; va++){
        wire_set(a, va) ;
        settle() ;
        bool res = va ;
        ok(wire_get(b) == res, "%d == %d", wire_get(a), res) ;
    }
}


void test_not(){
    wire a, b ;
    not_(a, b) ;

    for (int va = 0 ; va < 2 ; va++){
        wire_set(a, va) ;
        settle() ;
        bool res = ~va ;
        ok(wire_get(b) == res, "~%d == %d", wire_get(a), res) ;
    }
}


void test_and(){
    wire a, b, c ;
    and_(a, b, c) ;

    for (int va = 0 ; va < 2 ; va++){
        for (int vb = 0 ; vb < 2 ; vb++){
            wire_set(a, va) ;
            wire_set(b, vb) ;
            settle() ;
            bool res = va & vb ;
            ok(wire_get(c) == res, "%d & %d == %d", wire_get(a), wire_get(b), res) ;
        }
    }
}


void test_or(){
    wire a, b, c ;
    or_(a, b, c) ;

    for (int va = 0 ; va < 2 ; va++){
        for (int vb = 0 ; vb < 2 ; vb++){
            wire_set(a, va) ;
            wire_set(b, vb) ;
            settle() ;
            bool res = va | vb ;
            ok(wire_get(c) == res, "%d | %d == %d", wire_get(a), wire_get(b), res) ;
        }
    }
}


void test_nand(){
    wire a, b, c ;
    nand_(a, b, c) ;

    for (int va = 0 ; va < 2 ; va++){
        for (int vb = 0 ; vb < 2 ; vb++){
            wire_set(a, va) ;
            wire_set(b, vb) ;
            settle() ;
            bool res = ~(va & vb) ;
            ok(wire_get(c) == res, "~(%d & %d) == %d", wire_get(a), wire_get(b), res) ;
        }
    }
}


void test_nor(){
    wire a, b, c ;
    nor_(a, b, c) ;

    for (int va = 0 ; va < 2 ; va++){
        for (int vb = 0 ; vb < 2 ; vb++){
            wire_set(a, va) ;
            wire_set(b, vb) ;
            settle() ;
            bool res = ~(va | vb) ;
            ok(wire_get(c) == res, "~(%d | %d) == %d", wire_get(a), wire_get(b), res) ;
        }
    }
}


void test_xor(){
    wire a, b, c ;
    xor_(a, b, c) ;

    for (int va = 0 ; va < 2 ; va++){
        for (int vb = 0 ; vb < 2 ; vb++){
            wire_set(a, va) ;
            wire_set(b, vb) ;
            settle() ;
            bool res = va ^ vb ;
            ok(wire_get(c) == res, "%d ^ %d == %d", wire_get(a), wire_get(b), res) ;
        }
    }
}


void fullAdder(input::wire a, input::wire b, input::wire ci, output::wire c, output::wire co){
  wire i, coa, cob ;
  xor_ xor1(a, b, i) ;
  xor_ xor2(i, ci, c) ;
  and_ and1(ci, i, coa) ;
  and_ and2(a, b, cob) ;
  or_ or1(coa, cob, co) ;
}


void test_add(){
    wire a, b, ci, c, co ;
    add_(a, b, ci, c, co) ;

    for (int va = 0 ; va < 2 ; va++){
        for (int vb = 0 ; vb < 2 ; vb++){
            for (int vci = 0 ; vci < 2 ; vci++){
                wire_set(a, va) ;
                wire_set(b, vb) ;
                wire_set(ci, vci) ;
                settle() ;
                uint8_t sum = va + vb + vci ;
                bool cy = sum >> 1 ;
                sum = sum & 1 ;
                ok(wire_get(c) == sum, "sum(%d + %d + %d) == %d", wire_get(a), wire_get(b), wire_get(ci), sum) ;
                ok(wire_get(co) == cy, "cy(%d + %d + %d) == %d", wire_get(a), wire_get(b), wire_get(ci), cy) ;
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
