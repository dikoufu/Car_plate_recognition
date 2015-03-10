// ************************************************************************
//  �ļ�����edgecontour.cpp
//
//  ͼ���Ե����������API�����⣺
//
//  RobertDIB()		- robert��Ե�������
//  SobelDIB()		- sobel��Ե�������
//  PrewittDIB()	- prewitt��Ե�������
//  KirschDIB()		- kirsch��Ե�������
//  GaussDIB()		- gauss��Ե�������
//  HoughDIB()		- ����Hough�任���ƽ��ֱ��
//  ContourDIB()	- ������ȡ
//  TraceDIB()		- ��������
//  FillDIB()		- ��������㷨1
//  Fill2DIB()		- ��������㷨2

//
// ************************************************************************

#include "stdafx.h"
#include "edgecontour.h"
#include "TemplateTrans.h"
#include "DIBAPI.h"

#include <math.h>
#include <direct.h>

/*************************************************************************
 *
 * �������ƣ�
 *   RobertDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ��Ե���ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú�����Robert��Ե������Ӷ�ͼ����б�Ե������㡣
 * 
 * Ҫ��Ŀ��ͼ��Ϊ�Ҷ�ͼ��
 ************************************************************************/

BOOL WINAPI RobertDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;
	
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//ѭ������
	long i;
	long j;

	//����ֵ
	double result;
	unsigned char pixel[4];

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (char *)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);


	//ʹ��ˮƽ����ĽṹԪ�ؽ��и�ʴ
	for(j = lHeight-1; j > 0; j--)
	{
		for(i = 0;i <lWidth-1; i++)
		{
			//����ʹ��2��2��ģ�壬Ϊ��ֹԽ�磬���Բ��������±ߺ����ұߵ���������

			// ָ��Դͼ���j�У���i�����ص�ָ��			
			lpSrc = (char *)lpDIBBits + lWidth * j + i;

			// ָ��Ŀ��ͼ���j�У���i�����ص�ָ��			
			lpDst = (char *)lpNewDIBBits + lWidth * j + i;

			//ȡ�õ�ǰָ�봦2*2���������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel[0] = (unsigned char)*lpSrc;
			pixel[1] = (unsigned char)*(lpSrc + 1);
			pixel[2] = (unsigned char)*(lpSrc - lWidth);
			pixel[3] = (unsigned char)*(lpSrc - lWidth + 1);

			//����Ŀ��ͼ���еĵ�ǰ��
			 result = sqrt(( pixel[0] - pixel[3] )*( pixel[0] - pixel[3] ) + \
				  ( pixel[1] - pixel[2] )*( pixel[1] - pixel[2] ));
			*lpDst = (unsigned char)result;
		
		}
	}

	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   SobelDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ��Ե���ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú�����Sobel��Ե������Ӷ�ͼ����б�Ե������㡣
 * 
 * Ҫ��Ŀ��ͼ��Ϊ�Ҷ�ͼ��
 ************************************************************************/

BOOL WINAPI SobelDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst1;
	LPSTR	lpDst2;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;

	//ѭ������
	long i;
	long j;

	// ģ��߶�
	int		iTempH;
	
	// ģ����
	int		iTempW;
	
	// ģ��ϵ��
	FLOAT	fTempC;
	
	// ģ������Ԫ��X����
	int		iTempMX;
	
	// ģ������Ԫ��Y����
	int		iTempMY;
	
	//ģ������
	FLOAT aTemplate[9];

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits1 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits1 == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits1 = (char * )LocalLock(hNewDIBBits1);

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits2 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits2 == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits2 = (char * )LocalLock(hNewDIBBits2);

	// ����Դͼ�񵽻���ͼ����
	lpDst1 = (char *)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lWidth * lHeight);
	lpDst2 = (char *)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);

	// ����Sobelģ�����
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 1;
	iTempMY = 1;
	aTemplate[0] = -1.0;
	aTemplate[1] = -2.0;
	aTemplate[2] = -1.0;
	aTemplate[3] = 0.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 0.0;
	aTemplate[6] = 1.0;
	aTemplate[7] = 2.0;
	aTemplate[8] = 1.0;

	// ����Template()����
	if (!Template(lpNewDIBBits1, lWidth, lHeight, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// ����Sobelģ�����
	aTemplate[0] = -1.0;
	aTemplate[1] = 0.0;
	aTemplate[2] = 1.0;
	aTemplate[3] = -2.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 2.0;
	aTemplate[6] = -1.0;
	aTemplate[7] = 0.0;
	aTemplate[8] = 1.0;

	// ����Template()����
	if (!Template(lpNewDIBBits2, lWidth, lHeight, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//����������ͼ������ֵ
	for(j = 0; j <lHeight; j++)
	{
		for(i = 0;i <lWidth-1; i++)
		{

			// ָ�򻺴�ͼ��1������j�У���i�����ص�ָ��			
			lpDst1 = (char *)lpNewDIBBits1 + lWidth * j + i;

			// ָ�򻺴�ͼ��2������j�У���i�����ص�ָ��			
			lpDst2 = (char *)lpNewDIBBits2 + lWidth * j + i;
			
			if(*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;
		
		}
	}

	// ���ƾ���ģ��������ͼ��Դͼ��
	memcpy(lpDIBBits, lpNewDIBBits1, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   PrewittDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ��Ե���ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú�����Prewitt��Ե������Ӷ�ͼ����б�Ե������㡣
 * 
 * Ҫ��Ŀ��ͼ��Ϊ�Ҷ�ͼ��
 ************************************************************************/

BOOL WINAPI PrewittDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst1;
	LPSTR	lpDst2;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;

	//ѭ������
	long i;
	long j;

	// ģ��߶�
	int		iTempH;
	
	// ģ����
	int		iTempW;
	
	// ģ��ϵ��
	FLOAT	fTempC;
	
	// ģ������Ԫ��X����
	int		iTempMX;
	
	// ģ������Ԫ��Y����
	int		iTempMY;
	
	//ģ������
	FLOAT aTemplate[9];

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits1 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits1 == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits1 = (char * )LocalLock(hNewDIBBits1);

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits2 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits2 == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits2 = (char * )LocalLock(hNewDIBBits2);

	// ����Դͼ�񵽻���ͼ����
	lpDst1 = (char *)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lWidth * lHeight);
	lpDst2 = (char *)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);


	// ����Prewittģ�����
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 1;
	iTempMY = 1;
	aTemplate[0] = -1.0;
	aTemplate[1] = -1.0;
	aTemplate[2] = -1.0;
	aTemplate[3] = 0.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 0.0;
	aTemplate[6] = 1.0;
	aTemplate[7] = 1.0;
	aTemplate[8] = 1.0;

	// ����Template()����
	if (!Template(lpNewDIBBits1, lWidth, lHeight, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// ����Prewittģ�����
	aTemplate[0] = 1.0;
	aTemplate[1] = 0.0;
	aTemplate[2] = -1.0;
	aTemplate[3] = 1.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = -1.0;
	aTemplate[6] = 1.0;
	aTemplate[7] = 0.0;
	aTemplate[8] = -1.0;

	// ����Template()����
	if (!Template(lpNewDIBBits2, lWidth, lHeight, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//����������ͼ������ֵ
	for(j = 0; j <lHeight; j++)
	{
		for(i = 0;i <lWidth-1; i++)
		{

			// ָ�򻺴�ͼ��1������j�У���i�����ص�ָ��			
			lpDst1 = (char *)lpNewDIBBits1 + lWidth * j + i;

			// ָ�򻺴�ͼ��2������j�У���i�����ص�ָ��			
			lpDst2 = (char *)lpNewDIBBits2 + lWidth * j + i;
			
			if(*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;
		
		}
	}

	// ���ƾ���ģ��������ͼ��Դͼ��
	memcpy(lpDIBBits, lpNewDIBBits1, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   KirschDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ��Ե���ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú�����kirsch��Ե������Ӷ�ͼ����б�Ե������㡣
 * 
 * Ҫ��Ŀ��ͼ��Ϊ�Ҷ�ͼ��
 ************************************************************************/

BOOL WINAPI KirschDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst1;
	LPSTR	lpDst2;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;

	//ѭ������
	long i;
	long j;

	// ģ��߶�
	int		iTempH;
	
	// ģ����
	int		iTempW;
	
	// ģ��ϵ��
	FLOAT	fTempC;
	
	// ģ������Ԫ��X����
	int		iTempMX;
	
	// ģ������Ԫ��Y����
	int		iTempMY;
	
	//ģ������
	FLOAT aTemplate[9];

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits1 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits1 == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits1 = (char * )LocalLock(hNewDIBBits1);

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits2 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits2 == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits2 = (char * )LocalLock(hNewDIBBits2);

	// ����Դͼ�񵽻���ͼ����
	lpDst1 = (char *)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lWidth * lHeight);
	lpDst2 = (char *)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);


	// ����Kirschģ��1����
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 1;
	iTempMY = 1;
	aTemplate[0] = 5.0;
	aTemplate[1] = 5.0;
	aTemplate[2] = 5.0;
	aTemplate[3] = -3.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = -3.0;
	aTemplate[6] = -3.0;
	aTemplate[7] = -3.0;
	aTemplate[8] = -3.0;

	// ����Template()����
	if (!Template(lpNewDIBBits1, lWidth, lHeight, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// ����Kirschģ��2����
	aTemplate[0] = -3.0;
	aTemplate[1] = 5.0;
	aTemplate[2] = 5.0;
	aTemplate[3] = -3.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 5.0;
	aTemplate[6] = -3.0;
	aTemplate[7] = -3.0;
	aTemplate[8] = -3.0;

	// ����Template()����
	if (!Template(lpNewDIBBits2, lWidth, lHeight, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//����������ͼ������ֵ
	for(j = 0; j <lHeight; j++)
	{
		for(i = 0;i <lWidth-1; i++)
		{

			// ָ�򻺴�ͼ��1������j�У���i�����ص�ָ��			
			lpDst1 = (char *)lpNewDIBBits1 + lWidth * j + i;

			// ָ�򻺴�ͼ��2������j�У���i�����ص�ָ��			
			lpDst2 = (char *)lpNewDIBBits2 + lWidth * j + i;
			
			if(*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;
		
		}
	}

	// ����Դͼ�񵽻���ͼ����
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);

	// ����Kirschģ��3����
	aTemplate[0] = -3.0;
	aTemplate[1] = -3.0;
	aTemplate[2] = 5.0;
	aTemplate[3] = -3.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 5.0;
	aTemplate[6] = -3.0;
	aTemplate[7] = -3.0;
	aTemplate[8] = 5.0;

	// ����Template()����
	if (!Template(lpNewDIBBits2, lWidth, lHeight, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//����������ͼ������ֵ
	for(j = 0; j <lHeight; j++)
	{
		for(i = 0;i <lWidth-1; i++)
		{

			// ָ�򻺴�ͼ��1������j�У���i�����ص�ָ��			
			lpDst1 = (char *)lpNewDIBBits1 + lWidth * j + i;

			// ָ�򻺴�ͼ��2������j�У���i�����ص�ָ��			
			lpDst2 = (char *)lpNewDIBBits2 + lWidth * j + i;
			
			if(*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;
		
		}
	}

	// ����Դͼ�񵽻���ͼ����
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);
	
	// ����Kirschģ��4����
	aTemplate[0] = -3.0;
	aTemplate[1] = -3.0;
	aTemplate[2] = -3.0;
	aTemplate[3] = -3.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = 5.0;
	aTemplate[6] = -3.0;
	aTemplate[7] = 5.0;
	aTemplate[8] = 5.0;

	// ����Template()����
	if (!Template(lpNewDIBBits2, lWidth, lHeight, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//����������ͼ������ֵ
	for(j = 0; j <lHeight; j++)
	{
		for(i = 0;i <lWidth-1; i++)
		{

			// ָ�򻺴�ͼ��1������j�У���i�����ص�ָ��			
			lpDst1 = (char *)lpNewDIBBits1 + lWidth * j + i;

			// ָ�򻺴�ͼ��2������j�У���i�����ص�ָ��			
			lpDst2 = (char *)lpNewDIBBits2 + lWidth * j + i;
			
			if(*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;
		
		}
	}

	// ����Դͼ�񵽻���ͼ����
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);
	
	// ����Kirschģ��5����
	aTemplate[0] = -3.0;
	aTemplate[1] = -3.0;
	aTemplate[2] = -3.0;
	aTemplate[3] = -3.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = -3.0;
	aTemplate[6] = 5.0;
	aTemplate[7] = 5.0;
	aTemplate[8] = 5.0;

	// ����Template()����
	if (!Template(lpNewDIBBits2, lWidth, lHeight, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// ����Դͼ�񵽻���ͼ����
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);
	//����������ͼ������ֵ
	for(j = 0; j <lHeight; j++)
	{
		for(i = 0;i <lWidth-1; i++)
		{

			// ָ�򻺴�ͼ��1������j�У���i�����ص�ָ��			
			lpDst1 = (char *)lpNewDIBBits1 + lWidth * j + i;

			// ָ�򻺴�ͼ��2������j�У���i�����ص�ָ��			
			lpDst2 = (char *)lpNewDIBBits2 + lWidth * j + i;
			
			if(*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;
		
		}
	}

	// ����Դͼ�񵽻���ͼ����
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);
	
	// ����Kirschģ��6����
	aTemplate[0] = -3.0;
	aTemplate[1] = -3.0;
	aTemplate[2] = -3.0;
	aTemplate[3] = 5.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = -3.0;
	aTemplate[6] = 5.0;
	aTemplate[7] = 5.0;
	aTemplate[8] = -3.0;

	// ����Template()����
	if (!Template(lpNewDIBBits2, lWidth, lHeight, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//����������ͼ������ֵ
	for(j = 0; j <lHeight; j++)
	{
		for(i = 0;i <lWidth-1; i++)
		{

			// ָ�򻺴�ͼ��1������j�У���i�����ص�ָ��			
			lpDst1 = (char *)lpNewDIBBits1 + lWidth * j + i;

			// ָ�򻺴�ͼ��2������j�У���i�����ص�ָ��			
			lpDst2 = (char *)lpNewDIBBits2 + lWidth * j + i;
			
			if(*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;
		
		}
	}

	// ����Դͼ�񵽻���ͼ����
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);
	
	// ����Kirschģ��7����
	aTemplate[0] = 5.0;
	aTemplate[1] = -3.0;
	aTemplate[2] = -3.0;
	aTemplate[3] = 5.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = -3.0;
	aTemplate[6] = 5.0;
	aTemplate[7] = -3.0;
	aTemplate[8] = -3.0;

	// ����Template()����
	if (!Template(lpNewDIBBits2, lWidth, lHeight, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//����������ͼ������ֵ
	for(j = 0; j <lHeight; j++)
	{
		for(i = 0;i <lWidth-1; i++)
		{

			// ָ�򻺴�ͼ��1������j�У���i�����ص�ָ��			
			lpDst1 = (char *)lpNewDIBBits1 + lWidth * j + i;

			// ָ�򻺴�ͼ��2������j�У���i�����ص�ָ��			
			lpDst2 = (char *)lpNewDIBBits2 + lWidth * j + i;
			
			if(*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;
		
		}
	}

	// ����Դͼ�񵽻���ͼ����
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);
	
	// ����Kirschģ��8����
	aTemplate[0] = 5.0;
	aTemplate[1] = 5.0;
	aTemplate[2] = -3.0;
	aTemplate[3] = 5.0;
	aTemplate[4] = 0.0;
	aTemplate[5] = -3.0;
	aTemplate[6] = -3.0;
	aTemplate[7] = -3.0;
	aTemplate[8] = -3.0;

	// ����Template()����
	if (!Template(lpNewDIBBits2, lWidth, lHeight, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	//����������ͼ������ֵ
	for(j = 0; j <lHeight; j++)
	{
		for(i = 0;i <lWidth-1; i++)
		{

			// ָ�򻺴�ͼ��1������j�У���i�����ص�ָ��			
			lpDst1 = (char *)lpNewDIBBits1 + lWidth * j + i;

			// ָ�򻺴�ͼ��2������j�У���i�����ص�ָ��			
			lpDst2 = (char *)lpNewDIBBits2 + lWidth * j + i;
			
			if(*lpDst2 > *lpDst1)
				*lpDst1 = *lpDst2;
		
		}
	}

	// ���ƾ���ģ��������ͼ��Դͼ��
	memcpy(lpDIBBits, lpNewDIBBits1, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *  GaussDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ��Ե���ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú����ø�˹������˹��Ե������Ӷ�ͼ����б�Ե������㡣
 * 
 * Ҫ��Ŀ��ͼ��Ϊ�Ҷ�ͼ��
 ************************************************************************/

BOOL WINAPI GaussDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst1;
	LPSTR	lpDst2;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits1;
	HLOCAL	hNewDIBBits1;
	LPSTR	lpNewDIBBits2;
	HLOCAL	hNewDIBBits2;

	// ģ��߶�
	int		iTempH;
	
	// ģ����
	int		iTempW;
	
	// ģ��ϵ��
	FLOAT	fTempC;
	
	// ģ������Ԫ��X����
	int		iTempMX;
	
	// ģ������Ԫ��Y����
	int		iTempMY;
	
	//ģ������
	FLOAT aTemplate[25];

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits1 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits1 == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits1 = (char * )LocalLock(hNewDIBBits1);

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits2 = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits2 == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits2 = (char * )LocalLock(hNewDIBBits2);

	// ����Դͼ�񵽻���ͼ����
	lpDst1 = (char *)lpNewDIBBits1;
	memcpy(lpNewDIBBits1, lpDIBBits, lWidth * lHeight);
	lpDst2 = (char *)lpNewDIBBits2;
	memcpy(lpNewDIBBits2, lpDIBBits, lWidth * lHeight);


	// ����Gaussģ�����
	iTempW = 5;
	iTempH = 5;
	fTempC = 1.0;
	iTempMX = 3;
	iTempMY = 3;
	aTemplate[0] = -2.0;
	aTemplate[1] = -4.0;
	aTemplate[2] = -4.0;
	aTemplate[3] = -4.0;
	aTemplate[4] = -2.0;
	aTemplate[5] = -4.0;
	aTemplate[6] = 0.0;
	aTemplate[7] = 8.0;
	aTemplate[8] = 0.0;
	aTemplate[9] = -4.0;
	aTemplate[10] = -4.0;
	aTemplate[11] = 8.0;
	aTemplate[12] = 24.0;
	aTemplate[13] = 8.0;
	aTemplate[14] = -4.0;
	aTemplate[15] = -4.0;
	aTemplate[16] = 0.0;
	aTemplate[17] = 8.0;
	aTemplate[18] = 0.0;
	aTemplate[19] = -4.0;
	aTemplate[20] = -2.0;
	aTemplate[21] = -4.0;
	aTemplate[22] = -4.0;
	aTemplate[23] = -4.0;
	aTemplate[24] = -2.0;

	// ����Template()����
	if (!Template(lpNewDIBBits1, lWidth, lHeight, 
		iTempH, iTempW, iTempMX, iTempMY, aTemplate, fTempC))
	{
		return FALSE;
	}

	// ���ƾ���ģ��������ͼ��Դͼ��
	memcpy(lpDIBBits, lpNewDIBBits1, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits1);
	LocalFree(hNewDIBBits1);

	LocalUnlock(hNewDIBBits2);
	LocalFree(hNewDIBBits2);
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   HoughDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶԼ��ͼ���е�ƽ��ֱ�ߡ����ͼ����������ƽ�е�ֱ�ߣ���������ƽ��ֱ��
 * ��ȡ������
 * 
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL WINAPI HoughDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
		
	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;
	
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst;
	
	// ָ��任���ָ��
	LPSTR   lpTrans;

	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//ָ��任���ָ��
	LPSTR	lpTransArea;
	HLOCAL	hTransArea;

	//�任��ĳߴ�
	int iMaxDist;
	int iMaxAngleNumber;

	//�任�������
	int iDist;
	int iAngleNumber;

	//ѭ������
	long i;
	long j;

	//����ֵ
	unsigned char pixel;

	//�洢�任���е��������ֵ
	MaxValue MaxValue1;
	MaxValue MaxValue2;

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (char *)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);

	//����任��ĳߴ�
	//������
	iMaxDist = (int) sqrt(lWidth*lWidth + lHeight*lHeight);

	//�Ƕȴ�0��180��ÿ��2��
	iMaxAngleNumber = 90;

	//Ϊ�任������ڴ�
	hTransArea = LocalAlloc(LHND, lWidth * lHeight * sizeof(int));

	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpTransArea = (char * )LocalLock(hTransArea);
		
	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ0
	lpTrans = (char *)lpTransArea;
	memset(lpTrans, 0, lWidth * lHeight * sizeof(int));

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);

	for(j = 0; j <lHeight; j++)
	{
		for(i = 0;i <lWidth; i++)
		{

			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (char *)lpDIBBits + lLineBytes * j + i;

			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel = (unsigned char)*lpSrc;

			//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
			if(pixel != 255 && *lpSrc != 0)
				return FALSE;

			//����Ǻڵ㣬���ڱ任��Ķ�Ӧ�����ϼ�1
			if(pixel == 0)
			{
				//ע�ⲽ����2��
				for(iAngleNumber=0; iAngleNumber<iMaxAngleNumber; iAngleNumber++)
				{
					iDist = (int) fabs(i*cos(iAngleNumber*2*pi/180.0) + \
						j*sin(iAngleNumber*2*pi/180.0));
				
					//�任��Ķ�Ӧ���ϼ�1
					*(lpTransArea+iDist*iMaxAngleNumber+iAngleNumber) = \
						*(lpTransArea+iDist*iMaxAngleNumber+iAngleNumber) +1;
				}
			}
		
		}
	}
				
	//�ҵ��任���е��������ֵ��
	MaxValue1.Value=0;
	MaxValue2.Value=0;
	
	//�ҵ���һ�����ֵ��
	for (iDist=0; iDist<iMaxDist;iDist++)
	{
		for(iAngleNumber=0; iAngleNumber<iMaxAngleNumber; iAngleNumber++)
		{
			if((int)*(lpTransArea+iDist*iMaxAngleNumber+iAngleNumber)>MaxValue1.Value)
			{
				MaxValue1.Value = (int)*(lpTransArea+iDist*iMaxAngleNumber+iAngleNumber);
				MaxValue1.Dist = iDist;
				MaxValue1.AngleNumber = iAngleNumber;
			}

		}
	}

	//����һ�����ֵ�㸽������
	for (iDist = -9;iDist < 10;iDist++)
	{
		for(iAngleNumber=-1; iAngleNumber<2; iAngleNumber++)
		{
			if(iDist+MaxValue1.Dist>=0 && iDist+MaxValue1.Dist<iMaxDist \
				&& iAngleNumber+MaxValue1.AngleNumber>=0 && iAngleNumber+MaxValue1.AngleNumber<=iMaxAngleNumber)
			{
				*(lpTransArea+(iDist+MaxValue1.Dist)*iMaxAngleNumber+\
					(iAngleNumber+MaxValue1.AngleNumber))=0;
			}
		}
	}

	//�ҵ��ڶ������ֵ��
	for (iDist=0; iDist<iMaxDist;iDist++)
	{
		for(iAngleNumber=0; iAngleNumber<iMaxAngleNumber; iAngleNumber++)
		{
			if((int)*(lpTransArea+iDist*iMaxAngleNumber+iAngleNumber)>MaxValue2.Value)
			{
				MaxValue2.Value = (int)*(lpTransArea+iDist*iMaxAngleNumber+iAngleNumber);
				MaxValue2.Dist = iDist;
				MaxValue2.AngleNumber = iAngleNumber;
			}

		}
	}


	//�ж���ֱ���Ƿ�ƽ��
	if(abs(MaxValue1.AngleNumber-MaxValue2.AngleNumber)<=2)
	{
		//��ֱ��ƽ�У��ڻ���ͼ�����ػ�������ֱ��
		for(j = 0; j <lHeight; j++)
		{
			for(i = 0;i <lWidth; i++)
			{	

				// ָ�򻺴�ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lLineBytes * j + i;	

				//����õ���ĳһ��ƽ��ֱ���ϣ����ڻ���ͼ���Ͻ��õ㸳Ϊ��

				//�ڵ�һ��ֱ����
				iDist = (int) fabs(i*cos(MaxValue1.AngleNumber*2*pi/180.0) + \
							j*sin(MaxValue1.AngleNumber*2*pi/180.0));
				if (iDist == MaxValue1.Dist)
					*lpDst = (unsigned char)0;
			
				//�ڵڶ���ֱ����
				iDist = (int) fabs(i*cos(MaxValue2.AngleNumber*2*pi/180.0) + \
							j*sin(MaxValue2.AngleNumber*2*pi/180.0));
				if (iDist == MaxValue2.Dist)
					*lpDst = (unsigned char)0;
			}
		}
	}

	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// �ͷ��ڴ�
	LocalUnlock(hTransArea);
	LocalFree(hTransArea);

	// ����
	return TRUE;

}

/*************************************************************************
 *
 * �������ƣ�
 *   Fill2DIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - �������ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ���������������㡣
 * 
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL WINAPI Fill2DIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;

	//ѭ������
	long i;

	//����ֵ
	unsigned char pixel;

	//���ұ߽�����λ��
	int xl,xr;

	//�Ƿ���������߽�
	BOOL bFilll,bFillr;

	//���Ӷ�ջ��ָ��
	Seed Seeds[10];
	int StackPoint;

	//��ǰ����λ��
	int iCurrentPixelx,iCurrentPixely;
	int iBufferPixelx,iBufferPixely;

	//��ʼ������
	Seeds[1].Height = lHeight / 2;
	Seeds[1].Width = lWidth / 2;
	StackPoint = 1;

	while( StackPoint != 0)
	{
		//ȡ������
		iCurrentPixelx = Seeds[StackPoint].Width;
		iCurrentPixely = Seeds[StackPoint].Height;
		StackPoint--;
//		if(Seed2.Height== 75)
//		{
//			return true;
//			i++;
//		}
		bFilll = true;
		bFillr = true;
		//����������ڵ���
		//�����������ص�λ��
		iBufferPixelx = iCurrentPixelx;
		iBufferPixely = iCurrentPixely;
		//���������
		while(bFilll)
		{
			lpSrc = (char *)lpDIBBits + lWidth * iCurrentPixely + iCurrentPixelx;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel = (unsigned char)*lpSrc;

			//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
			if(pixel != 255 && pixel != 0)
				return FALSE;
			//�����߽�
			if(pixel == 0)
			{
				bFilll = false;
				xl=iCurrentPixelx+1;
			}
			else
			{
				*lpSrc = (unsigned char)0;
				iCurrentPixelx--;
				//��ֹԽ��
				if(iCurrentPixelx<0)
				{	
					bFilll = false;
					iCurrentPixelx = 0;
					xl = 0; 
				}
			}		
		}
		//���������
		//ȡ���������ص�λ��
		iCurrentPixelx = iBufferPixelx+1;
		if(iCurrentPixelx>lWidth)
		{	
			bFillr = false;
			iCurrentPixelx = lWidth;
			xr = lWidth; 
		}
		iCurrentPixely = iBufferPixely;
		while(bFillr)
		{
			lpSrc = (char *)lpDIBBits + lWidth * iCurrentPixely + iCurrentPixelx;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel = (unsigned char)*lpSrc;

			//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
			if(pixel != 255 && pixel != 0)
				return FALSE;
			//�����߽�
			if(pixel == 0)
			{
				bFillr = false;
				xr=iCurrentPixelx-1;
			}
			else
			{
				*lpSrc = (unsigned char)0;
				iCurrentPixelx++;
				//��ֹԽ��
				if(iCurrentPixelx>lWidth)
				{	
					bFillr = false;
					iCurrentPixelx = lWidth;
					xr = lWidth; 
				}
			}		
		}
		//�ϡ�������ɨ�����Ƿ�ȫΪ�߽����ػ�������
		//�ȿ������ɨ����
		iCurrentPixely--;
		if(iCurrentPixely < 0)
		{
			iCurrentPixely = 0;
		}
		for (i = xr; i>= xl;i--)
		{
			lpSrc = (char *)lpDIBBits + lWidth * iCurrentPixely + i;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel = (unsigned char)*lpSrc;

			//��δ�������أ����µ�����ѹ���ջ
			if (pixel == 255)
			{
				StackPoint++;
				Seeds[StackPoint].Height = iCurrentPixely;
				Seeds[StackPoint].Width = i;
				break;
			}				
		}
		//�ٿ������ɨ����
		iCurrentPixely+=2;
		if(iCurrentPixely > lHeight)
		{
			iCurrentPixely = lHeight;
		}
		for (i = xr; i>= xl;i--)
		{
			lpSrc = (char *)lpDIBBits + lWidth * iCurrentPixely + i;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel = (unsigned char)*lpSrc;

			//��δ�������أ����µ�����ѹ���ջ
			if (pixel == 255)
			{
				StackPoint++;
				Seeds[StackPoint].Height = iCurrentPixely;
				Seeds[StackPoint].Width = i;
				break;
			}				
		}


	}

	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   FillDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - �������ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ���������������㡣
 * 
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL WINAPI FillDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;

	//����ֵ
	unsigned char pixel;

	//���Ӷ�ջ��ָ��
	Seed *Seeds;
	int StackPoint;

	//��ǰ����λ��
	int iCurrentPixelx,iCurrentPixely;

	//��ʼ������
	Seeds = new Seed[lWidth*lHeight];
	Seeds[1].Height = lHeight / 2;
	Seeds[1].Width = lWidth / 2;
	StackPoint = 1;

	while( StackPoint != 0)
	{
		//ȡ������
		iCurrentPixelx = Seeds[StackPoint].Width;
		iCurrentPixely = Seeds[StackPoint].Height;
		StackPoint--;

		lpSrc = (char *)lpDIBBits + lWidth * iCurrentPixely + iCurrentPixelx;
		//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
		pixel = (unsigned char)*lpSrc;

		//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
		if(pixel != 255 && pixel != 0)
			return FALSE;

		//����ǰ��Ϳ��
		*lpSrc = (unsigned char)0;

		//�ж�����ĵ㣬���Ϊ�ף���ѹ���ջ
		//ע���ֹԽ��
		if(iCurrentPixelx > 0)
		{
			lpSrc = (char *)lpDIBBits + lWidth * iCurrentPixely + iCurrentPixelx - 1;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel = (unsigned char)*lpSrc;
			if (pixel == 255)
			{
				StackPoint++;
				Seeds[StackPoint].Height = iCurrentPixely;
				Seeds[StackPoint].Width = iCurrentPixelx - 1;
			}
			//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
			if(pixel != 255 && pixel != 0)
				return FALSE;
		}

		//�ж�����ĵ㣬���Ϊ�ף���ѹ���ջ
		//ע���ֹԽ��
		if(iCurrentPixely < lHeight - 1)
		{
			lpSrc = (char *)lpDIBBits + lWidth * (iCurrentPixely + 1) + iCurrentPixelx;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel = (unsigned char)*lpSrc;
			if (pixel == 255)
			{
				StackPoint++;
				Seeds[StackPoint].Height = iCurrentPixely + 1;
				Seeds[StackPoint].Width = iCurrentPixelx;
			}
			//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
			if(pixel != 255 && pixel != 0)
				return FALSE;
		}

		//�ж�����ĵ㣬���Ϊ�ף���ѹ���ջ
		//ע���ֹԽ��
		if(iCurrentPixelx < lWidth - 1)
		{
			lpSrc = (char *)lpDIBBits + lWidth * iCurrentPixely + iCurrentPixelx + 1;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel = (unsigned char)*lpSrc;
			if (pixel == 255)
			{
				StackPoint++;
				Seeds[StackPoint].Height = iCurrentPixely;
				Seeds[StackPoint].Width = iCurrentPixelx + 1;
			}
			//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
			if(pixel != 255 && pixel != 0)
				return FALSE;
		}

		//�ж�����ĵ㣬���Ϊ�ף���ѹ���ջ
		//ע���ֹԽ��
		if(iCurrentPixely > 0)
		{
			lpSrc = (char *)lpDIBBits + lWidth * (iCurrentPixely - 1) + iCurrentPixelx;
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel = (unsigned char)*lpSrc;
			if (pixel == 255)
			{
				StackPoint++;
				Seeds[StackPoint].Height = iCurrentPixely - 1;
				Seeds[StackPoint].Width = iCurrentPixelx;
			}
			//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
			if(pixel != 255 && pixel != 0)
				return FALSE;
		}
	}

	//�ͷŶ�ջ
	delete Seeds;
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   ContourDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ�����������ȡ���㡣
 * 
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL WINAPI ContourDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;
	
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//ѭ������
	long i;
	long j;
	unsigned char n,e,s,w,ne,se,nw,sw;

	//����ֵ
	unsigned char pixel;

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lWidth * lHeight);

	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (char *)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lWidth * lHeight);
	for(j = 1; j <lHeight-1; j++)
	{
		for(i = 1;i <lWidth-1; i++)
		{
			
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (char *)lpDIBBits + lWidth * j + i;
			
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst = (char *)lpNewDIBBits + lWidth * j + i;
			
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel = (unsigned char)*lpSrc;

			//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
//			if(pixel != 255 && pixel != 0)
//				return FALSE;
			if(pixel == 0)
			{
				*lpDst = (unsigned char)0;
				nw = (unsigned char)*(lpSrc + lWidth -1);
				n  = (unsigned char)*(lpSrc + lWidth );
				ne = (unsigned char)*(lpSrc + lWidth +1);
				w = (unsigned char)*(lpSrc -1);
				e = (unsigned char)*(lpSrc +1);
				sw = (unsigned char)*(lpSrc - lWidth -1);
				s  = (unsigned char)*(lpSrc - lWidth );
				se = (unsigned char)*(lpSrc - lWidth +1);
				//������ڵİ˸��㶼�Ǻڵ�
				if(nw+n+ne+w+e+sw+s+se==0)
				{
					*lpDst = (unsigned char)255;
				}
			}
		}
	}

	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   TraceDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ����������������㡣
 * 
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL WINAPI TraceDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;
	
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;
	
	//ѭ������
	long i;
	long j;

	//����ֵ
	unsigned char pixel;

	//�Ƿ��ҵ���ʼ�㼰�ص���ʼ��
	bool bFindStartPoint;

	//�Ƿ�ɨ�赽һ���߽��
	bool bFindPoint;

	//��ʼ�߽���뵱ǰ�߽��
	Point StartPoint,CurrentPoint;

	//�˸��������ʼɨ�跽��
	int Direction[8][2]={{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0}};
	int BeginDirect;

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);

	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);

	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);

	// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
	lpDst = (char *)lpNewDIBBits;
	memset(lpDst, (BYTE)255, lLineBytes * lHeight);

	//���ҵ������Ϸ��ı߽��
	bFindStartPoint = false;
	for (j = 0;j < lHeight && !bFindStartPoint;j++)
	{
		for(i = 0;i < lWidth && !bFindStartPoint;i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (char *)lpDIBBits + lLineBytes * j + i;
			
			//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
			pixel = (unsigned char)*lpSrc;
			
			if(pixel == 0)
			{
				bFindStartPoint = true;

				StartPoint.Height = j;
				StartPoint.Width = i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lLineBytes * j + i;	
				*lpDst = (unsigned char)0;
			}		
		}
	}

	//������ʼ���������·�������ʼɨ�������Ϸ���
	BeginDirect = 0;
	//���ٱ߽�
	bFindStartPoint = false;
	//�ӳ�ʼ�㿪ʼɨ��
	CurrentPoint.Height = StartPoint.Height;
	CurrentPoint.Width = StartPoint.Width;
	while(!bFindStartPoint)
	{
		bFindPoint = false;
		while(!bFindPoint)
		{
			//��ɨ�跽��鿴һ������
			lpSrc = (char *)lpDIBBits + lLineBytes * ( CurrentPoint.Height + Direction[BeginDirect][1])
				+ (CurrentPoint.Width + Direction[BeginDirect][0]);
			pixel = (unsigned char)*lpSrc;
			if(pixel == 0)
			{
				bFindPoint = true;
				CurrentPoint.Height = CurrentPoint.Height + Direction[BeginDirect][1];
				CurrentPoint.Width = CurrentPoint.Width + Direction[BeginDirect][0];
				if(CurrentPoint.Height == StartPoint.Height && CurrentPoint.Width == StartPoint.Width)
				{
					bFindStartPoint = true;
				}
				lpDst = (char *)lpNewDIBBits + lLineBytes * CurrentPoint.Height + CurrentPoint.Width;
				*lpDst = (unsigned char)0;
				//ɨ��ķ�����ʱ����ת����
				BeginDirect--;
				if(BeginDirect == -1)
					BeginDirect = 7;
				BeginDirect--;
				if(BeginDirect == -1)
					BeginDirect = 7;
			}
			else
			{
				//ɨ�跽��˳ʱ����תһ��
				BeginDirect++;
				if(BeginDirect == 8)
					BeginDirect = 0;

			}

		}
	}

	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
	return TRUE;
}


