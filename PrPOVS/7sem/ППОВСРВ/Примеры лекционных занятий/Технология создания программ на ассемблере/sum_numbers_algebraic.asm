	.mmregs
	.def	_c_int00
	
	.text
	.algebraic
_c_int00:	
	DP = #X
	A = @X
	A += @Y
	@Z = A
	nop
	nop
	nop
	
	;.align
	.data
X	.word	0x1
Y	.word	0xA
Z	.word	0

	.end