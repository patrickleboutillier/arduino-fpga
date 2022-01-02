#include <stdio.h>
#include <stdlib.h>
#include "FPGAreg.h"


static int MAXID = 0 ;
static uint8_t STATE[MAX_REGS / 8] ;


reg::reg(){
	// TODO: Check if MAX_REGS is reached...
	_id = MAXID++ ;
	set(0) ;
} ;


void reg::set(bool v){
	int i = _id >> 3 ;
    int j = _id & 3 ;
	STATE[i] = (STATE[i] & ~(1 << j)) | (v << j) ;
}


bool reg::get(){
	int i = _id >> 3 ;
    int j = _id & 3 ;
    
	return (STATE[i] >> j) & 1 ;
}