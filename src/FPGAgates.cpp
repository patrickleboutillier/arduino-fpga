#include <stdio.h>
#include <stdlib.h>
#include "FPGAgates.h"


static uint16_t MAXPOS = 0 ;
static uint8_t GATES[MAX_GATE_BYTES] ;


uint8_t peek_gate(uint16_t pos){
	return GATES[pos] >> 4 ;
}


void save_gate_2(uint8_t gate, wire a, wire b){
	// TODO: Check if MAX_GATE_BYTES is reached...
	uint32_t bytes = gate << 28 | a.id() << 19 | b.id() << 10 ;
	GATES[MAXPOS++] = (bytes >> 24) & 0xFF ;  
	GATES[MAXPOS++] = (bytes >> 16) & 0xFF ;
	GATES[MAXPOS++] = (bytes >> 8) & 0xFF ;   
}


void restore_gate_2(uint16_t pos, uint16_t &a, uint16_t &b){
	uint32_t bytes = GATES[pos++] << 24 | GATES[pos++] << 16 | GATES[pos++] << 8 ;
	a = (bytes >> 19) & 0x1FF ;
	b = (bytes >> 10) & 0x1FF ;
}


bool eval_gate_2(uint8_t gate, uint16_t a, uint16_t b){
	bool prev = wire::get(b) ;
	bool cur ;
	bool va = wire::get(a) ;
	// printf("gate=%d, p=%d, a=%d, b=%d\n", gate, p, wire::get(ia), wire::get(ib)) ;
	switch (gate){
		case BUF: 
			cur = va ;
			break ;
		case NOT: 
			cur = ~va ;
			break ;
	}
	if (cur != prev){
		wire::set(b, cur) ;
		return 1 ; 
	}

	return 0 ;
}


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


bool eval_gate_3(uint8_t gate, uint16_t a, uint16_t b, uint16_t c){
	bool prev = wire::get(c) ;
	bool cur ;
	bool va = wire::get(a), vb = wire::get(b) ;
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
		wire::set(c, cur) ;
		return 1 ; 
	}

	return 0 ;
}


/*
void save_gate_4(uint8_t gate, wire a, wire b, wire c, wire d){
	// TODO: Check if MAX_GATE_BYTES is reached...
	uint16_t id = d.id() ;
	uint32_t bytes = gate << 28 | a.id() << 19 | b.id() << 10 | c.id() << 1 | id >> 8 ;
	uint8_t xtra = id & 0xFF ;
	GATES[MAXPOS++] = (bytes >> 24) & 0xFF ;  
	GATES[MAXPOS++] = (bytes >> 16) & 0xFF ;
	GATES[MAXPOS++] = (bytes >> 8) & 0xFF ;  
	GATES[MAXPOS++] = bytes & 0xFF ; 
	GATES[MAXPOS++] = xtra ; 
}


void restore_gate_4(uint16_t pos, uint16_t &a, uint16_t &b, uint16_t &c, uint16_t &d){
	uint32_t bytes = GATES[pos++] << 24 | GATES[pos++] << 16 | GATES[pos++] << 8 | GATES[pos++] ;
	d = ((bytes & 1) << 8) | GATES[pos++] ;
	a = (bytes >> 19) & 0x1FF ;
	b = (bytes >> 10) & 0x1FF ;
	c = (bytes >> 1) & 0x1FF ;
}
*/


void save_gate_5(uint8_t gate, wire a, wire b, wire c, wire d, wire e){
	// TODO: Check if MAX_GATE_BYTES is reached...
	printf("save gate=%d, MAXPOS=%d, a=%d, b=%d, c=%d, d=%d, e=%d\n", gate, MAXPOS, a.id(), b.id(),
		c.id(), d.id(), e.id()) ;
	uint16_t id = d.id() ;
	uint32_t bytes = gate << 28 | a.id() << 19 | b.id() << 10 | c.id() << 1 | id >> 8 ;
	uint32_t bytes2 = (id << 24) | e.id() << 15 ;
	GATES[MAXPOS++] = (bytes >> 24) & 0xFF ;  
	GATES[MAXPOS++] = (bytes >> 16) & 0xFF ;
	GATES[MAXPOS++] = (bytes >> 8) & 0xFF ;  
	GATES[MAXPOS++] = bytes & 0xFF ; 
	GATES[MAXPOS++] = (bytes2 >> 24) & 0xFF ;  
	GATES[MAXPOS++] = (bytes2 >> 16) & 0xFF ;
	GATES[MAXPOS++] = (bytes2 >> 8) & 0xFF ; 
}


void restore_gate_5(uint16_t pos, uint16_t &a, uint16_t &b, uint16_t &c, uint16_t &d, uint16_t &e){
	uint32_t bytes = GATES[pos++] << 24 | GATES[pos++] << 16 | GATES[pos++] << 8 | GATES[pos++] ;
	uint32_t bytes2 = GATES[pos++] << 24 | GATES[pos++] << 16 | GATES[pos++] << 8 ;
	a = (bytes >> 19) & 0x1FF ;
	b = (bytes >> 10) & 0x1FF ;
	c = (bytes >> 1) & 0x1FF ;
	d = ((bytes & 1) << 8) | ((bytes2 >> 24) & 0xFF) ;
	e = (bytes2 >> 15) & 0x1FF ;
	printf("rsto gate=%d, MAXPOS=%d, a=%d, b=%d, c=%d, d=%d, e=%d\n", bytes >> 28, MAXPOS, a, b,
		c, d, e) ;
}


// 3 inputs, 2 outputs
bool eval_gate_5(uint8_t gate, uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e){
	bool prev1 = wire::get(d) ;
	bool prev2 = wire::get(e) ;
	bool cur1, cur2 ;
	bool va = wire::get(a), vb = wire::get(b), vc = wire::get(c) ;
	switch (gate){
		case ADD: { 
			uint8_t sum = va + vb + vc ;
			cur1 = sum & 1 ;
			cur2 = sum >> 1 ;
			break ;
		}
	}
	//printf("eval gate=%d, a=%d, b=%d, c=%d, d=%d(%d), e=%d(%d)\n", gate, wire::get(a), wire::get(b), wire::get(c),
	//	cur1, prev1, cur2, prev2) ;

	bool change = 0 ;
	if (cur1 != prev1){
		wire::set(d, cur1) ;
		change = 1 ; 
	}
	if (cur2 != prev2){
		wire::set(e, cur2) ;
		change = 1 ; 
	}

	return change ;
}


void save_gate_6(uint8_t gate, wire a, wire b, wire c, wire d, wire e, wire f){
	// TODO: Check if MAX_GATE_BYTES is reached...
	uint16_t id = d.id() ;
	uint32_t bytes = gate << 28 | a.id() << 19 | b.id() << 10 | c.id() << 1 | id >> 8 ;
	uint32_t bytes2 = (id << 24) | e.id() << 15 | f.id() << 6 ;
	GATES[MAXPOS++] = (bytes >> 24) & 0xFF ;  
	GATES[MAXPOS++] = (bytes >> 16) & 0xFF ;
	GATES[MAXPOS++] = (bytes >> 8) & 0xFF ;  
	GATES[MAXPOS++] = bytes & 0xFF ; 
	GATES[MAXPOS++] = (bytes2 >> 24) & 0xFF ;  
	GATES[MAXPOS++] = (bytes2 >> 16) & 0xFF ;
	GATES[MAXPOS++] = (bytes2 >> 8) & 0xFF ; 
	GATES[MAXPOS++] = bytes2 & 0xFF ; 
}


void restore_gate_6(uint16_t pos, uint16_t &a, uint16_t &b, uint16_t &c, uint16_t &d, uint16_t &e, uint16_t &f){
	uint32_t bytes = GATES[pos++] << 24 | GATES[pos++] << 16 | GATES[pos++] << 8 | GATES[pos++] ;
	uint32_t bytes2 = GATES[pos++] << 24 | GATES[pos++] << 16 | GATES[pos++] << 8 | GATES[pos++] ;
	a = (bytes >> 19) & 0x1FF ;
	b = (bytes >> 10) & 0x1FF ;
	c = (bytes >> 1) & 0x1FF ;
	d = ((bytes & 1) << 8) | ((bytes2 >> 24) & 0xFF) ;
	e = (bytes2 >> 15) & 0x1FF ;
	f = (bytes2 >> 6) & 0x1FF ;
}


buf_::buf_(wire a, wire b){
	save_gate_2(BUF, a, b) ;
}


not_::not_(wire a, wire b){
	save_gate_2(NOT, a, b) ;
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


add_::add_(wire a, wire b, wire ci, wire c, wire co){
	save_gate_5(ADD, a, b, ci, c, co) ;
}


cmp_::cmp_(wire a, wire b, wire ci, wire c, wire co){
	save_gate_5(ADD, a, b, ci, c, co) ;
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
				change = eval_gate_2(gate, ia, ib) ;
			}
			else if (gate < 8){
				uint16_t ia, ib, ic ;
				restore_gate_3(p, ia, ib, ic) ;
				p += 4 ;
				change = eval_gate_3(gate, ia, ib, ic) ;
			}
			else if (gate == ADD){
				uint16_t ia, ib, ic, id, ie ;
				restore_gate_5(p, ia, ib, ic, id, ie) ;
				p += 7 ;
				change = eval_gate_5(gate, ia, ib, ic, id, ie) ;
			}
			else if (gate == CMP){
				uint16_t ia, ib, ic, id, ie, if_ ;
				restore_gate_6(p, ia, ib, ic, id, ie, if_) ;
				p += 8 ;
				change = eval_gate_6(gate, ia, ib, ic, id, ie, if_) ;
			}
		}
	}
}