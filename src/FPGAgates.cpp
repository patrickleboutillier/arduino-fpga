#include <stdio.h>
#include <stdlib.h>
#include "FPGAgates.h"


static uint16_t MAXPOS = 0 ;
static uint8_t GATES[MAX_GATE_BYTES] ;


void wire_set(uint16_t id, bool v) ;
bool wire_get(uint16_t id) ;


uint8_t peek_gate(uint16_t pos){
	return GATES[pos] >> 4 ;
}


void save_gate_2(uint8_t gate, uint16_t a, uint16_t b){
	// TODO: Check if MAX_GATE_BYTES is reached...
	uint32_t bytes = 
		(uint32_t)gate << 28 | 
		(uint32_t)a << 19 | 
		(uint32_t)b << 10 ;
	GATES[MAXPOS++] = (bytes >> 24) & 0xFF ;  
	GATES[MAXPOS++] = (bytes >> 16) & 0xFF ;
	GATES[MAXPOS++] = (bytes >> 8) & 0xFF ;   
}


void restore_gate_2(uint16_t pos, uint16_t &a, uint16_t &b){
	uint32_t bytes = 
		(uint32_t)GATES[pos++] << 24 | 
		(uint32_t)GATES[pos++] << 16 | 
		(uint32_t)GATES[pos++] << 8 ;
	a = (bytes >> 19) & 0x1FF ;
	b = (bytes >> 10) & 0x1FF ;
}


bool eval_gate_11(uint8_t gate, uint16_t a, uint16_t b){
	bool prev = wire_get(b) ;
	bool cur ;
	bool va = wire_get(a) ;
	switch (gate){
		case BUF: 
			cur = va ;
			break ;
		case NOT: 
			cur = ~va ;
			break ;
	}
	if (cur != prev){
		wire_set(b, cur) ;
		return 1 ; 
	}

	return 0 ;
}


void save_gate_3(uint8_t gate, uint16_t a, uint16_t b, uint16_t c){
	// TODO: Check if MAX_GATE_BYTES is reached...
	uint32_t bytes = 
		(uint32_t)gate << 28 | 
		(uint32_t)a << 19 | 
		(uint32_t)b << 10 | 
		(uint32_t)c << 1 ;
	GATES[MAXPOS++] = (bytes >> 24) & 0xFF ;  
	GATES[MAXPOS++] = (bytes >> 16) & 0xFF ;
	GATES[MAXPOS++] = (bytes >> 8) & 0xFF ;  
	GATES[MAXPOS++] = bytes & 0xFF ; 
}


void restore_gate_3(uint16_t pos, uint16_t &a, uint16_t &b, uint16_t &c){
	uint32_t bytes = 
		(uint32_t)GATES[pos++] << 24 | 
		(uint32_t)GATES[pos++] << 16 | 
		(uint32_t)GATES[pos++] << 8 | 
		(uint32_t)GATES[pos++] ;
	a = (bytes >> 19) & 0x1FF ;
	b = (bytes >> 10) & 0x1FF ;
	c = (bytes >> 1) & 0x1FF ;	
}


bool eval_gate_21(uint8_t gate, uint16_t a, uint16_t b, uint16_t c){
	bool prev = wire_get(c) ;
	bool cur ;
	bool va = wire_get(a), vb = wire_get(b) ;

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
		wire_set(c, cur) ;
		return 1 ; 
	}

	return 0 ;
}


void save_gate_5(uint8_t gate, uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e){
	// TODO: Check if MAX_GATE_BYTES is reached...
	uint16_t id = d ;
	uint32_t bytes = 
		(uint32_t)gate << 28 | 
		(uint32_t)a << 19 | 
		(uint32_t)b << 10 | 
		(uint32_t)c << 1 | 
		(uint32_t)id >> 8 ;
	uint32_t bytes2 = 
		(uint32_t)id << 24 | 
		(uint32_t)e << 15 ;
	GATES[MAXPOS++] = (bytes >> 24) & 0xFF ;  
	GATES[MAXPOS++] = (bytes >> 16) & 0xFF ;
	GATES[MAXPOS++] = (bytes >> 8) & 0xFF ;  
	GATES[MAXPOS++] = bytes & 0xFF ; 
	GATES[MAXPOS++] = (bytes2 >> 24) & 0xFF ;  
	GATES[MAXPOS++] = (bytes2 >> 16) & 0xFF ;
	GATES[MAXPOS++] = (bytes2 >> 8) & 0xFF ; 
}


void restore_gate_5(uint16_t pos, uint16_t &a, uint16_t &b, uint16_t &c, uint16_t &d, uint16_t &e){
	uint32_t bytes = 
		(uint32_t)GATES[pos++] << 24 | 
		(uint32_t)GATES[pos++] << 16 | 
		(uint32_t)GATES[pos++] << 8 | 
		(uint32_t)GATES[pos++] ;
	uint32_t bytes2 = 
		(uint32_t)GATES[pos++] << 24 | 
		(uint32_t)GATES[pos++] << 16 | 
		(uint32_t)GATES[pos++] << 8 ;
	a = (bytes >> 19) & 0x1FF ;
	b = (bytes >> 10) & 0x1FF ;
	c = (bytes >> 1) & 0x1FF ;
	d = ((bytes & 1) << 8) | ((bytes2 >> 24) & 0xFF) ;
	e = (bytes2 >> 15) & 0x1FF ;
}


// 3 inputs, 2 outputs
bool eval_gate_32(uint8_t gate, uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e){
	bool prev1 = wire_get(d) ;
	bool prev2 = wire_get(e) ;
	bool cur1, cur2 ;
	bool va = wire_get(a), vb = wire_get(b), vc = wire_get(c) ;
	switch (gate){
		case ADD: { 
			uint8_t sum = va + vb + vc ;
			cur1 = sum & 1 ;
			cur2 = sum >> 1 ;
			break ;
		}
	}

	bool change = 0 ;
	if (cur1 != prev1){
		wire_set(d, cur1) ;
		change = 1 ; 
	}
	if (cur2 != prev2){
		wire_set(e, cur2) ;
		change = 1 ; 
	}

	return change ;
}


buf_::buf_(input::wire a, output::wire b){
	save_gate_2(BUF, a.id(), b.id()) ;
}


not_::not_(input::wire a, output::wire b){
	save_gate_2(NOT, a.id(), b.id()) ;
}


and_::and_(input::wire a, input::wire b, output::wire c){
	save_gate_3(AND, a.id(), b.id(), c.id()) ;
}


or_::or_(input::wire a, input::wire b, output::wire c){
	save_gate_3(OR, a.id(), b.id(), c.id()) ;
}


nand_::nand_(input::wire a, input::wire b, output::wire c){
	save_gate_3(NAND, a.id(), b.id(), c.id()) ;
}


nor_::nor_(input::wire a, input::wire b, output::wire c){
	save_gate_3(NOR, a.id(), b.id(), c.id()) ;
}


xor_::xor_(input::wire a, input::wire b, output::wire c){
	save_gate_3(XOR, a.id(), b.id(), c.id()) ;
}


add_::add_(input::wire a, input::wire b, input::wire ci, output::wire c, output::wire co){
	save_gate_5(ADD, a.id(), b.id(), ci.id(), c.id(), co.id()) ;
}


void settle() {
	bool change = 1 ;

	uint8_t iter = 0 ;
	while (change){
		iter++ ;
		change = 0 ;
		uint16_t p = 0 ;
		while (p < MAXPOS){
			uint8_t gate = peek_gate(p) ;
			if (gate < 2){
				uint16_t ia, ib ;
				restore_gate_2(p, ia, ib) ;
				p += 3 ;
				change = eval_gate_11(gate, ia, ib) ;
			}
			else if (gate < 8){
				uint16_t ia, ib, ic ;
				restore_gate_3(p, ia, ib, ic) ;
				p += 4 ;
				change = eval_gate_21(gate, ia, ib, ic) ;
			}
			else if (gate == ADD){
				uint16_t ia, ib, ic, id, ie ;
				restore_gate_5(p, ia, ib, ic, id, ie) ;
				p += 7 ;
				change = eval_gate_32(gate, ia, ib, ic, id, ie) ;
			}
		}
	}
}