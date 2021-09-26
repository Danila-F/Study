	.mmregs
	.mlib	"two_func_lib.lib"
	.def	_c_int00
			
	.text
_c_int00:
	sum_mul	0x1, 0x2, 0x3, 1
	sum_mul	0x3, 0x2, 0x1, 2
	sub_mul 0xA, 0x7, 0x2, 3
	ld	res1, A
	ld	res2, B
	mvdk	res1, resM1
	mvdk	res2, resM2
	ld 	res3, A
	nop
	nop
	nop
	
	.data
resM1	.word	0
resM2 	.word	0

	.end