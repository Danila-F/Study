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
	st	T, thrshld	;��������� ���������� T � ������
	ld	#5, B		;�����-���� ����� (����������� ����� ���������� �����)
	sub	thrshld, B
	neg	B		;������ �������� � ������� ������������� ��� �������
	stl	B, thrshld
	ld	thrshld, T
	norm	A		;������� �� 2^m
	
	nop
	nop
	nop
