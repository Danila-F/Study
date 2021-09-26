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