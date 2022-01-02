#ifndef FPGAGATES_H
#define FPGAGATES_H 	

#include <stdint.h>
#include "FPGAwire.h"


#define MAX_GATE_BYTES  1200

#define BUF             0
#define NOT             1
#define AND             2
#define OR              3
#define NAND            4
#define NOR             5
#define XOR             6
#define ADD             9
#define CMP             10


class buf_ {
  public:
    buf_(input::wire a, output::wire b) ;
} ;


class not_ {
  public:
    not_(input::wire a, output::wire b) ;
} ;


class and_ {
  public:
    and_(input::wire a, input::wire b, output::wire c) ;
} ;


class or_ {
  public:
    or_(input::wire a, input::wire b, output::wire c) ;
} ;


class nand_ {
  public:
    nand_(input::wire a, input::wire b, output::wire c) ;
} ;


class nor_ {
  public:
    nor_(input::wire a, input::wire b, output::wire c) ;
} ;


class xor_ {
  public:
    xor_(input::wire a, input::wire b, output::wire c) ;
} ;


class add_ {
  public:
    add_(input::wire a, input::wire b, input::wire ci, output::wire c, output::wire co) ;
} ;


void settle() ;


#endif
