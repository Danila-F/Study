//#include <iostream>
#include <stdlib.h>
#include "belt.h"

err_t main()
{
	char dest[8] = {0};
	const char src[8] = "12345678";
	size_t count = 8;
	size_t len = 16;
	const octet key[16] = "8765432112345678";
	const octet iv[16] = "1111111111111111";
	
	err_t res = 
	beltCTR(
		dest,					/*!< [out] ��������� / �������� ����� */
		src,					/*!< [in] �������� ����� / ��������� */
		count,					/*!< [in] ����� ������� ������ */
		key,					/*!< [in] ���� */
		len,					/*!< [in] ����� ����� */
		iv						/*!< [in] ������������� */
	);

	char decr[8] = { 0 };
	err_t res1 =
		beltCTR(
			decr,					/*!< [out] ��������� / �������� ����� */
			dest,					/*!< [in] �������� ����� / ��������� */
			count,					/*!< [in] ����� ������� ������ */
			key,					/*!< [in] ���� */
			len,					/*!< [in] ����� ����� */
			iv						/*!< [in] ������������� */
		);

    return(res);
}