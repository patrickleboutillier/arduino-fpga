#ifndef FPGA_H
#define FPGA_H 	

#include <Arduino.h>
#include "FPGAwire.h"
#include "FPGAgates.h"

class FPGA {
  public:
    FPGA() ;
    void loop() ;
    wire attachInputPin(byte pin) ;
    wire attachOutputPin(byte pin) ;
  private:
    byte pins[24] ;
    byte attachPin(byte pin) ;
} ;


#endif
