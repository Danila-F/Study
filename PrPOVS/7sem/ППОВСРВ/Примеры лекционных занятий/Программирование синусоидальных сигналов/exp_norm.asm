	.def	_c_int00
	.mmregs
	
	.data
operand	.word	3104	;0.075
thrshld	.word	0

	.text
_c_int00:
	ssbx	sxm
	ld	#operand, DP
	ld	operand, 16, A
	
	exp	A
	st	T, thrshld	;сохраняем содержимое T в память
	ld	#5, B		;какой-либо порог (максмальное число незначащих нулей)
	sub	thrshld, B
	neg	B		;делаем разность с порогом отрицательной для деления
	stl	B, thrshld
	ld	thrshld, T
	norm	A		;деление на 2^m
	
	nop
	nop
	nop
