#ifndef FPGAREG_H
#define FPGAREG_H 	

#include <stdint.h>


#define MAX_REGS   512


class reg {
  public:
    reg() ;
    void set(bool v) ;
    bool get() ;
  private:
    uint16_t _id ;
} ;


#endif
