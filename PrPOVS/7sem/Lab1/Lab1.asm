N		.equ	208
GAR		.equ	10
CNT		.equ	2
SIZE	.equ	N*CNT
S1GAR	.equ	990; S1 = sin(2*pi/N)*2^15 = 989,69 (0,0302030278)
C1GAR	.equ	32753; C1 = cos(2*pi/N)*2^15 = 32 753,05 (0,9995437845)
	
	.mmregs
	.def _c_int00
	.text
_c_int00:
	LD	#Sn, DP
	SSBX SXM
	SSBX OVM
	
	STM GAR-1, AR0; AR0 = GAR-1
	STM #Sk, AR1; AR1 = addr(Sk)
	STM #Ck, AR2; AR2 = addr(Ck)
	STM #S1, AR3; AR3 = addr(S1)
	STM #C1, AR4; AR4 = addr(C1)
	STM #RES, AR5; AR5 = addr(RES)
	STM #0, AR6; AR6 = CNT-1
	STM #0, AR7
	
garm_n:
	LD *AR4, T; T = *AR4 = C1
	MPY *AR1, A; A = T * (*AR1) = C1 * Sk
	LD *AR3, T; T = *AR3 = S1
	MAC *AR2, A; A = A + T * (*AR2) = C1 * Sk + S1 * Ck
	;MPY *AR3, *AR2, B
	;ADD B, A
	STL A, -15, *AR5+; *AR5 (RES) = AR1 (Sn)
	
	LD *AR4, T; T = *AR4 = C1
	MPY *AR2, B; B = T * (*AR2) = C1 * Ck
	LD *AR3, T; T = *AR3 = S1
	MAS *AR1, B; B = B - T * (*AR1) = C1 * Ck - S1 * Sk
	;MPY *AR3, *AR2, A
	;SUB A, B
	
	STL A, -15, *AR1; *AR1 = Sk = high(A)
	STL B, -15, *AR2; *AR2 = Ck = high(A)

	BANZ garm_n, *AR0-; for (i = AR0, i!=0, i--)
	
	BANZ cnt, *AR6; for (i = AR6, i!=0, i--)
	BANZ end, *AR7
	
	STM #Sn, AR1; AR1 = addr(Sn)
	STM #Cn, AR2; AR2 = addr(Cn)
	STM #Sk, AR3; AR3 = addr(Sk)
	STM #Ck, AR4; AR4 = addr(Ck)
	STM #RES, AR5; AR5 = addr(RES)
	STM CNT, AR6; AR6 = CNT
	STM #1, AR7
cnt:
	STM N-1, AR0; AR0 = N-1
	BANZ garm_n, *AR6-; for (i = AR6, i!=0, i--)
end:
	
	NOP
	NOP
	NOP
	.align
	.data

Sn		.word	0x0000; Sn(0) = 0
Cn		.word	0x7FFF; Cn(0) = 1

Sk		.word	0x0000; Sk(0) = 0
Ck		.word	0x7FFF; Ck(0) = 1

S1		.word	S1GAR
C1		.word	C1GAR

RES		.space	SIZE*16; результирующий массив
