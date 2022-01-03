#include <stdio.h>
#include <stdlib.h>
#include "FPGAwire.h"


static int MAXID = 0 ;
static uint8_t STATE[MAX_WIRES / 8] ;


void wire_set(uint16_t id, bool v){
	uint8_t i = id >> 3 ;
    uint8_t j = id & 7 ;
	//printf("  id=%d, i=%d, j=%d\n", id, i, j) ;
	STATE[i] = (STATE[i] & ~(1 << j)) | (v << j) ;
}


void wire_set(wire w, bool v){
	uint16_t id = w.id() ;
	uint8_t i = id >> 3 ;
    uint8_t j = id & 7 ;
	//printf("  id=%d, i=%d, j=%d\n", id, i, j) ;
	STATE[i] = (STATE[i] & ~(1 << j)) | (v << j) ;
}


bool wire_get(wire w){	
	uint16_t id = w.id() ;
	uint8_t i = id >> 3 ;
    uint8_t j = id & 7 ;

	return (STATE[i] >> j) & 1 ;
}


bool wire_get(uint16_t id){
	uint8_t i = id >> 3 ;
    uint8_t j = id & 7 ;

	return (STATE[i] >> j) & 1 ;
}


wire::wire(){
	// TODO: Check if MAX_WIRES is reached...
	_id = MAXID++ ;
	wire_set(_id, 0) ;
} ;


wire::wire(uint16_t id){
	// TODO: Check if MAX_WIRES is reached...
	_id = id ;
} ;