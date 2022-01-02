#include "FPGA.h"


void settle() ;


FPGA::FPGA(){
    for (byte i = 0 ; i < 24 ; i++){
        pins[i] = 255 ;
    }
}


byte FPGA::attachPin(byte p){
    byte i = 0 ;
    while (pins[i] != 255){ i++ ; } ;
    byte reg, pin ;
    if (p < 16){
        reg = p >> 3 ;
        pin = p & 7 ;
    }
    else {
        reg = 2 ;
        pin = p - A0 ;
    }
    pins[i] = reg << 5 | pin << 2 ;

    return i ;
}


wire FPGA::attachInputPin(byte p){
    byte i = attachPin(p) ;

    return wire(i) ;
}


wire FPGA::attachOutputPin(byte p){
    byte i = attachPin(p) ;
    pins[i] |= 1 ;

    byte reg = (pins[i] >> 5) & 7 ;
    byte pin = (pins[i] >> 2) & 7 ;
    switch (reg){
        case 0:
            bitSet(DDRD, pin) ;
            break ;
        case 1:
            bitSet(DDRB, pin) ;
            break ;
        case 2:
            bitSet(DDRC, pin) ;
            break ;
    }

    return wire(i) ;
}


void FPGA::loop(){
    byte i = 0 ;
    while (pins[i] != 255){
        if (! (pins[i] & 1)){ // input pins
            byte reg = (pins[i] >> 5) & 7 ;
            byte pin = (pins[i] >> 2) & 7 ;

            switch (reg){
                case 0:
                    wire::set(i, bitRead(PIND, pin)) ;
                    break ;
                case 1:
                    wire::set(i, bitRead(PINB, pin)) ;
                    break ;
                case 2:
                    wire::set(i, bitRead(PINC, pin)) ;
                    break ;
            }
        }
        i++ ;
    }

    settle() ; 

    i = 0 ;
    while (pins[i] != 255){
        if (pins[i] & 1){   // output pins
            byte reg = (pins[i] >> 5) & 7 ;
            byte pin = (pins[i] >> 2) & 7 ;

            switch (reg){
                case 0:
                    bitWrite(PORTD, pin, wire::get(i)) ;
                    break ;
                case 1:
                    bitWrite(PORTB, pin, wire::get(i)) ;
                    break ;
                case 2:
                    bitWrite(PORTC, pin, wire::get(i)) ;
                    break ;
            }
        }
        i++ ;
    }
}