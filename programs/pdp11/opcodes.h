#ifndef OPCODES_H
#define OPCODES_H

#include <stdlib.h>
#include <string.h>

const char OPNAMES[][8] = { "CLR", "COM", "INC", "DEC", "NEG", "TST", "ROR", "ROL", 
                            "ASR", "ASL", "SWAB", "ADC", "SBC", "SXT", "MOV", "CMP", 
                            "ADD", "SUB", "BIT", "BIC", "BIS", "MUL", "DIV", "ASH", 
                            "ASHC", "XOR", "BR", "BNE", "BEQ", "BPL", "BMI", "BVC", 
                            "BVS", "BCC", "BCS", "BGE", "BLT", "BGT", "BLE", "BHI", 
                            "BLOS", "BHIS", "BLO", "JMP", "JSR", "RTS", "MARK", "SOB", 
                            "BPT", "IOT", "RTI", "RTT", "HALT", "WAIT", "RESET", "NOP", 
                            "SPL", "MFPI", "MTPI", "MFPD", "MTPD", "CLC", "CLV", "CLZ", 
                            "CLN", "CCC", "SEC", "SEV", "SEZ", "SEN", "SCC" };

const char OPOCTAL[][8] = { "050DD", "051DD", "052DD", "053DD", "054DD", "057DD", "060DD", "061DD", 
                            "062DD", "063DD", "0003DD", "055DD", "056DD", "067DD", "1SSDD", "2SSDD", 
                            "06SSDD", "16SSDD", "3SSDD", "4SSDD", "5SSDD", "070RSS", "071RSS", "072RSS", 
                            "073RSS", "074RDD", "000400", "001000", "001400", "100000", "100400", "102000", 
                            "102400", "103000", "103400", "002000", "002400", "003000", "003400", "101000", 
                            "101400", "103000", "103400", "0001DD", "004RDD", "00020R", "0064NN", "077RNN", 
                            "000003", "000004", "000002", "000006", "000000", "000001", "000005", "000240", 
                            "00023N", "0065SS", "0066DD", "1065SS", "1066DD", "000241", "000242", "000244", 
                            "000250", "000257", "000261", "000262", "000264", "000270", "000277" };

/* 71 opcodes, their index in the list determines their instruction type */
#define NUM_OPCODES 71
#define SINGLE_S     0
#define SINGLE_E    13
#define DOUBLE_S    14
#define DOUBLE_E    25
#define BRANCH_S    26
#define BRANCH_E    42
#define JUMP_S      43
#define JUMP_E      44
#define RET_S       45
#define RET_E       47
#define TRAP_S      48
#define TRAP_E      51
#define MISC_S      52
#define MISC_E      60
#define COND_S      61
#define COND_E      70

/* Type of instruction to be performed */
enum TYPES { SINGLE, DOUBLE, BRANCH, JUMP, RET, TRAP, MISC, COND };

typedef struct opcode
{
	int type;       /* Instruction type */
	int index;      /* Index in opcode list */
	char name[8];   /* Instruction (such as CLR) */
	char octal[8];  /* Octal code for the instruction (050DD for CLR) */
} Opcode;

/* Copy opcode info from one opcode to another */
extern void opcode_copy(struct opcode *src, struct opcode **dst)
{
	(*dst)->type = src->type;
	(*dst)->index = src->index;
	memcpy((*dst)->name, src->name, strlen(src->name));
	memcpy((*dst)->octal, src->octal, strlen(src->octal));
}

/* Returns type of an opcode depending on its index in the list of opcodes */
extern int opcode_type(int index)
{
	switch(index){
		case SINGLE_S ... SINGLE_E:
			return SINGLE;
		case DOUBLE_S ... DOUBLE_E:
			return DOUBLE;
		case BRANCH_S ... BRANCH_E:
			return BRANCH;
		case JUMP_S ... JUMP_E:
			return JUMP;
		case RET_S ... RET_E:
			return RET;
		case TRAP_S ... TRAP_E:
			return TRAP;
		case MISC_S ... MISC_E:
			return MISC;
		case COND_S ... COND_E:
			return COND;
	}
}

/* Create array of all 71 opcodes, setting their type, name, and octal values */
extern struct opcode **opcode_init()
{
	struct opcode **ops;
	struct opcode *o;
	int i;

	ops = calloc(NUM_OPCODES+1, sizeof(struct opcode *));

	for (i = 0; i < NUM_OPCODES; i++){
		o = calloc(1, sizeof(struct opcode));
		memcpy(o->name, OPNAMES[i], strlen(OPNAMES[i]));
		memcpy(o->octal, OPOCTAL[i], strlen(OPOCTAL[i]));
		o->type = opcode_type(i);
		o->index = i;
		ops[i] = o;
	}

	return ops;
}

extern void opcode_print(struct opcode *op)
{
	printf("%-10s %7s\n", op->name, op->octal);
}

extern void opcode_print_all(struct opcode **ops)
{
	int i;

	for (i = 0; i < NUM_OPCODES; i++){
		opcode_print(ops[i]);
	}
}

extern void opcode_free(struct opcode *op)
{
	free(op);
}

extern void opcode_free_all(struct opcode **ops)
{
	int i;

	for (i = 0; i < NUM_OPCODES; i++){
		opcode_free(ops[i]);
	}

	free(ops);
}

extern struct opcode *opcode_check(char *input, struct opcode **ops)
{
	int i;
	char opname[8];
	char c;
	struct opcode *o;

	if (strlen(input) == 0) return NULL;

	/* Get opcode only */
	i = 0;
	while ((c = input[i]) != ' ' && (c = input[i]) != '\t' && (c = input[i]) != '\0'){
		opname[i] = input[i];
		i++;
	}
	opname[i] = '\0';

	/* Check if opcode exists, return it if so */
	for (i = 0; i < NUM_OPCODES; i++){
		if (strncmp(opname, ops[i]->name, strlen(opname)) == 0){
			o = malloc(sizeof(struct opcode));
			opcode_copy(ops[i], &o);
			return o;
		}
	}
	fprintf(stderr, "error: opcode %s not found\n", opname);
	return NULL;
}

#endif
