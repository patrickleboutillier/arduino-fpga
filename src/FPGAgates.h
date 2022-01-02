#ifndef FPGAGATES_H
#define FPGAGATES_H 	

#include <stdint.h>
#include "FPGAwire.h"


#define MAX_GATE_BYTES  1200

#define AND             0
#define OR              1
#define NAND            2
#define NOR             3
#define XOR             4


class and_ {
  public:
    and_(wire a, wire b, wire c) ;
} ;


class or_ {
  public:
    or_(wire a, wire b, wire c) ;
} ;


class nand_ {
  public:
    nand_(wire a, wire b, wire c) ;
} ;


class nor_ {
  public:
    nor_(wire a, wire b, wire c) ;
} ;


class xor_ {
  public:
    xor_(wire a, wire b, wire c) ;
} ;


void settle() ;


#endif
