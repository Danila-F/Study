	.mmregs
	.def	_c_int00
	.text
	
sum_mul	.macro	firstNum, secondNum, thirdNum, n
	.text
	ld	#X:n:, DP
	ld	X:n:, A
	add	Y:n:, A
	stl	A, tmp:n:
	ld	Z:n:, T
	mpy	tmp:n:, A
	stl	A, res:n:
	nop
	
	.data	
	.align	2
X:n:	.word	firstNum
Y:n:	.word	secondNum;
Z:n:	.word	thirdNum
res:n:	.word	0
tmp:n:	.word	0

	.text
	.endm
	
_c_int00:
	sum_mul	0x1, 0x2, 0x3, 1
	sum_mul	0x3, 0x2, 0x1, 2
	ld	res1, A
	ld	res2, B
	mvdk	res1, resM1
	mvdk	res2, resM2
	nop
	nop
	nop
	
	.data
resM1	.word	0
resM2 	.word	0
	
	.end