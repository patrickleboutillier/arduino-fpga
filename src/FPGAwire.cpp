#include <stdio.h>
#include <stdlib.h>
#include "FPGAwire.h"


static int MAXID = 0 ;
static uint8_t STATE[MAX_WIRES / 8] ;


wire::wire(){
	// TODO: Check if MAX_WIRES is reached...
	_id = MAXID++ ;
	set(0) ;
} ;


void wire::set(uint16_t id, bool v){
	uint8_t i = id >> 3 ;
    uint8_t j = id & 7 ;
	//printf("  id=%d, i=%d, j=%d\n", id, i, j) ;
	STATE[i] = (STATE[i] & ~(1 << j)) | (v << j) ;
}


void wire::set(bool v){
	set(_id, v) ;
}


bool wire::get(uint16_t id){
	uint8_t i = id >> 3 ;
    uint8_t j = id & 7 ;

	return (STATE[i] >> j) & 1 ;
}


bool wire::get(){
	return get(_id) ;
}


uint16_t wire::id(){
	return _id ;
}