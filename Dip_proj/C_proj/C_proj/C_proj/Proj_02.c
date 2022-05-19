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

	err_t resB;
	char destB[8] = { 0 };
	char srcB[8] = "12345678";
	size_t countB = 8;
	size_t lenB = 16;
	const octet keyB[16] = "8765432112345678";
	const octet ivB[16] = "1111111111111111";
	// ������� ���������
	void* stateB = blobCreate(beltCTR_keep());
	beltCTRStart(stateB, keyB, lenB, ivB);
	// �����������
	for (int i = 0; i < countB; i++)
	{
		//resB = beltCTRB(destB + i, srcB + i, keyB, 
			//lenB, ivB, stateB);
		beltCTRStepE(srcB + i, 1, stateB);
	}
	// ���������
	blobClose(stateB);

	// ������� ���������
	void* stateBE = blobCreate(beltCTR_keep());
	beltCTRStart(stateBE, keyB, lenB, ivB);
	// ������������
	for (int i = 0; i < countB; i++)
	{
		//resB = beltCTRB(destB + i, srcB + i, keyB, 
			//lenB, ivB, stateB);
		beltCTRStepE(srcB + i, 1, stateBE);
	}
	// ���������
	blobClose(stateBE);

    return(0);
}