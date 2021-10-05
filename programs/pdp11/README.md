# PDP-11 Notes

## General Purpose Registers (GPR)

R0, R1, R2, R3, R4, R5 (FP), R6 (SP), R7 (PC)

## Categories of instructions
Can be __word-based__ or __byte-based (has a 'B' after instruction)__
1. Single-Operand:
 - General: CLR(B), COM(B), INC(B), DEC(B), NEG(B), NOP, TST(B), TSTSET, WRTLCK
 - Shift & Rotate: ASR(B), ASL(B), ROR(B), ROL(B), SWAB
 - Multiple Precision: ADC(B), SBC(B), SXT
 -    15: word or byte operation
 -  14-6: opcode
 -   5-0: 3-bit addressing mode and 3-bit general register
2. Double-Operand:
 - General: MOV(B), ADD, SUB, CMP(B), ASH, ASHC, MUL, DIV
 - Logical: BIT(B), BIC(B), BIS(B), XOR
 -    15: word or byte (ADD or SUB if opcode 6)
 - 14-12: opcode
 -  11-6: SOURCE 3-bit addressing mode and 3-bit general register
 -   5-0: DEST 3-bit addressing mode and 3-bit general register
 -  NOTE: some instructions (ASH, ASHC, MUL, DIV) _must_ have the DEST operand only in a register.
  - 15-9: opcode
	-  5-0: SOURCE
 - For XOR:
  - 15-9: opcode
	-  8-6: SOURCE
	-  5-0: DEST
3. Byte:
 - Specified by __setting bit 15__
 - CLR:  0050DD    Clear word
 - CLRB: 1050DD    Clear Byte
4. Branch:
 - Branch: BR, BNE, BEQ, BPL, BMI, BVC, BVS, BCC, BCS
 - Signed Conditional Branch: BGE, BLT, BGT, BLE, SOB
 - Unsigned Conditional Branch: BHI, BLOS, BHIS, BLO
 -  15-8: condition to be tested
 -   7-0: signed offset value in words to jump to (-128 to +127 words from __updated__ PC)
5. Jump:
 - JMP, JSR
 -  15-9: always octal 004 (opcode for JSR)
 -   8-6: link register (any general register except R6 a.k.a. SP)
 -   5-0: DEST 3-bit addressing mode and 3-bit general register
 -  NOTE: register R7 (PC) is frequently used for both link and destination. Other GPRs cannot be both link and destination.
6. Return:
 - RTS, MARK
 -  15-3: always octal 00020 (opcode for RTS)
 -   2-0: any general register
 -  NOTE: the 2-0 register specified must be the same register used as link between the JSR causing the jump
7. Traps and Interrupts:
 - EMT, TRAP, BPT, IOT, CSM, RTI, RTT
 - Software exit: program specifies a jump to some subroutine
 - Trap exit: internal hardware on a special instruction forces a jump to an error handling routine
 - Interrupt exit: external hardware forces a jump to an interrupt service routine
8. Miscellaneous:
 - HALT, WAIT, RESET, MTPD, MTPI, MFPD, MFPI, MTPS, MFPS, MFPT
9. Condition Code Operation:
 - CLC, CLV, CLZ, CLN, CCC: clear
 - SEC, SEV, SEZ, SEN, SCC: set
 - N: indicates a negative condition when set to 1
 - Z: indicates a zero condition when set to 1
 - V: indicates an overflow condition when set to 1
 - C: indicates a carry condition when set to 1
 -  15-5: opcode
 -     4: "operator" which indicates set  or clear (1 or 0). If set, selected bits are set. If not set, selected bits are cleared.
 -   3-0: mask field. Each bit corresponds to one of the four condition code bits. When one is set, the corresponding condition code bit is set or cleared depending on the state of the "operator" (bit 4)

## Opcodes

### General Registers
R0     777 700
R1     777 701
R2     777 702
R3     777 703
R4     777 704
R5     777 705
R6     777 706
R7     777 707

### Single-Operand (0-13 inclusive):
General:
CLR(B)  050DD     clear
COM(B)  051DD     complement (1's)
INC(B)  052DD     increment
DEC(B)  053DD     decrement
NEG(B)  054DD     negate (2's)
TST(B)  057DD     test
Rotate & Shift:
ROR(B)  060DD     rotate right
ROL(B)  061DD     rotate left
ASR(B)  062DD     arith shift right
ASL(B)  063DD     arith shift left
SWAB    0003DD    swap bytes
Multiple Precision:
ADC(B)  055DD     add carry
SBC(B)  056DD     subtract carry
SXT     067DD     sign extend

### Double-Operand (14 - 25 inclusive):
General:
MOV(B)  1SSDD     move
CMP(B)  2SSDD     compare
ADD    06SSDD     add
SUB    16SSDD     subtract
Logical:
BIT(B)  3SSDD     bit test (AND)
BIC(B)  4SSDD     bit clear
BIS(B)  5SSDD     bit set (OR)
Register:
MUL    070RSS     multiply
DIV    071RSS     divide
ASH    072RSS     shift arith
ASHC   073RSS     arith shift combined
XOR    074RDD     exclusive OR

### Branches (26 - 42 inclusive):
General:
BR     000400     branch
BNE    001000     br if not equal to 0
BEQ    001400     br if equal to 0
BPL    100000     branch if plus
BMI    100400     branch if minus
BVC    102000     br if overflow is clear
BVS    102400     br if overflow is set
BCC    103000     br if carry is clear
BCS    103400     br if carry is set
Signed Conditional:
BGE    002000     br if greater or eq to 0
BLT    002400     br if less than 0
BGT    003000     br if greater than 0
BLE    003400     br if less or eq to 0
Unsigned Conditional:
BHI    101000     br if higher
BLOS   101400     br if less or eq
BHIS   103000     br if greater or eq
BLO    103400     br if lower

### Jump & Subroutine (43 - 47 inclusive):
JMP    0001DD     jump
JSR    004RDD     jump to subroutine
RTS    00020R     return from subroutine
MARK   0064NN     mark
SOB    077RNN     subtract 1 and br (if not eq to 0)

### Trap & Interrupt (48 - 51 inclusive):
EMT    104000     emulator trap
    to 104377
TRAP   104400     trap
    to 104777
BPT    000003     breakpoint trap
IOT    000004     input/output trap
RTI    000002     return from interrupt
RTT    000006     return from interrupt

### Miscellaneous (52 - 60 inclusive):
HALT   000000     halt
WAIT   000001     wait for interrupt
RESET  000005     reset external bus
NOP    000240     no operation
SPL    00023N     set priority level to N
MFPI   0065SS     move from previous instr space
MTPI   0066DD     move to previous instr space
MFPD   1065SS     move from previous data space
MTPD   1066DD     move to previous data space

### Condition Code (61 - 70 inclusive):
CLC    000241     clear C
CLV    000242     clear V
CLZ    000244     clear Z
CLN    000250     clear N
CCC    000257     clear all cc bits

SEC    000261     set C
SEV    000262     set V
SEZ    000264     set Z
SEN    000270     set N
SCC    000277     set all cc bits
