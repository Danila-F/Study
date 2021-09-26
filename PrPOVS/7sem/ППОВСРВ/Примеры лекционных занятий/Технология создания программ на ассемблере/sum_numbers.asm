	.def	_c_int00
	
	.text
_c_int00	
	ld	#X, DP
	ld	X, A
	add	Y, A
	stl	A, Z
	nop
	nop
	nop
	
	.align
	.data
X	.word	0x1
Y	.word	0xA
Z	.word	0