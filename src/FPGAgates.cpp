#include <stdio.h>
#include <stdlib.h>
#include "FPGAgates.h"


static uint16_t MAXPOS = 0 ;
static uint8_t GATES[MAX_GATE_BYTES] ;


void save_gate_3(uint8_t gate, wire a, wire b, wire c){
	// TODO: Check if MAX_GATE_BYTES is reached...
	uint32_t bytes = gate << 28 | a.id() << 19 | b.id() << 10 | c.id() << 1 ;
	GATES[MAXPOS++] = (bytes >> 24) & 0xFF ;  
	GATES[MAXPOS++] = (bytes >> 16) & 0xFF ;
	GATES[MAXPOS++] = (bytes >> 8) & 0xFF ;  
	GATES[MAXPOS++] = bytes & 0xFF ; 
}


void restore_gate_3(uint16_t pos, uint16_t &a, uint16_t &b, uint16_t &c){
	uint32_t bytes = GATES[pos++] << 24 | GATES[pos++] << 16 | GATES[pos++] << 8 | GATES[pos++] ;
	a = (bytes >> 19) & 0x1FF ;
	b = (bytes >> 10) & 0x1FF ;
	c = (bytes >> 1) & 0x1FF ;	
}


and_::and_(wire a, wire b, wire c){
	save_gate_3(AND, a, b, c) ;
}


or_::or_(wire a, wire b, wire c){
	save_gate_3(OR, a, b, c) ;
}


nand_::nand_(wire a, wire b, wire c){
	save_gate_3(NAND, a, b, c) ;
}


nor_::nor_(wire a, wire b, wire c){
	save_gate_3(NOR, a, b, c) ;
}


xor_::xor_(wire a, wire b, wire c){
	save_gate_3(XOR, a, b, c) ;
}


void settle() {
	bool change = 1 ;

	uint8_t iter = 0 ;
	while (change){
		iter++ ;
		change = 0 ;
		uint16_t p = 0 ;
		while (p < MAXPOS){
			uint8_t gate = GATES[p] >> 4 ;
			if (gate < 8){
				uint16_t ia, ib, ic ;
				restore_gate_3(p, ia, ib, ic) ;
				p += 4 ;
				bool prev = wire::get(ic) ;
				bool cur ;
				bool va = wire::get(ia), vb = wire::get(ib) ;
				// printf("gate=%d, p=%d, a=%d, b=%d\n", gate, p, wire::get(ia), wire::get(ib)) ;
				switch (gate){
					case AND: 
						cur = va & vb ;
						break ;
					case OR: 
						cur = va | vb ;
						break ;
					case NAND: 
						cur = ~(va & vb) ;
						break ;
					case NOR: 
						cur = ~(va | vb) ;
						break ;
					case XOR: 
						cur = va ^ vb ;
						break ;
				}
				if (cur != prev){
					wire::set(ic, cur) ;
					change = 1 ; 
				}
			}
		}
	}
}