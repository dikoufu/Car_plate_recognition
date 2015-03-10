// ************************************************************************
//  �ļ�����detect.cpp
//
//  ͼ���������API�����⣺
//
//  ThresholdDIB()	- ͼ����ֵ�ָ�����
//  AddMinusDIB()   - ͼ��Ӽ�����
//  HprojectDIB()	- ͼ��ˮƽͶӰ
//  VprojectDIB()	- ͼ��ֱͶӰ
//	TemplateDIB()	- ͼ��ģ��ƥ������
//
// ************************************************************************

#include "stdafx.h"
#include "detect.h"
#include "DIBAPI.h"
#include <math.h>
#include <direct.h>

/*************************************************************************
 *
 * �������ƣ�
 *   ThresholdDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ�������ֵ�ָ����㡣
 * 
 ************************************************************************/

BOOL WINAPI ThresholdDIB(LPSTR lpDIBBits,LONG lWidth, LONG lHeight)
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
	unsigned char pixel;

	//ֱ��ͼ����
	long lHistogram[256];

	//��ֵ�����Ҷ�ֵ����С�Ҷ�ֵ�����������ƽ���Ҷ�ֵ
	unsigned char iThreshold,iNewThreshold,iMaxGrayValue,iMinGrayValue,iMean1GrayValue,iMean2GrayValue;

	//���ڼ�������Ҷ�ƽ��ֵ���м����
	long lP1,lP2,lS1,lS2;

	//��������
	int iIterationTimes;

	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;

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

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);

	for (i = 0; i < 256;i++)
	{
		lHistogram[i]=0;
	}

	//���ֱ��ͼ
	iMaxGrayValue = 0;
	iMinGrayValue = 255;
	for (i = 0;i < lWidth ;i++)
	{
		for(j = 0;j < lHeight ;j++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (char *)lpDIBBits + lLineBytes * j + i;
	
			pixel = (unsigned char)*lpSrc;
			
			lHistogram[pixel]++;
			//�޸������С�Ҷ�ֵ
			if(iMinGrayValue > pixel)
			{
				iMinGrayValue = pixel;
			}
			if(iMaxGrayValue < pixel)
			{
				iMaxGrayValue = pixel;
			}
		}
	}

	//�����������ֵ
	iNewThreshold = (iMinGrayValue + iMaxGrayValue)/2;
	iThreshold = 0;
	
	for(iIterationTimes = 0; iThreshold != iNewThreshold && iIterationTimes < 100;iIterationTimes ++)
	{
		iThreshold = iNewThreshold;
		lP1 =0;
		lP2 =0;
		lS1 = 0;
		lS2 = 0;
		//����������ĻҶ�ƽ��ֵ
		for (i = iMinGrayValue;i < iThreshold;i++)
		{
			lP1 += lHistogram[i]*i;
			lS1 += lHistogram[i];
		}
		iMean1GrayValue = (unsigned char)(lP1 / lS1);
		for (i = iThreshold+1;i < iMaxGrayValue;i++)
		{
			lP2 += lHistogram[i]*i;
			lS2 += lHistogram[i];
		}
		iMean2GrayValue = (unsigned char)(lP2 / lS2);
		iNewThreshold =  (iMean1GrayValue + iMean2GrayValue)/2;
	}

	iThreshold=80;
	//������ֵ��ͼ���ֵ��
	for (i = 0;i < lWidth ;i++)
	{
		for(j = 0;j < lHeight ;j++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (char *)lpDIBBits + lLineBytes * j + i;
	
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst = (char *)lpNewDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;
			
			if(pixel <= iThreshold)
			{
				*lpDst = (unsigned char)0;
			}
			else
			{
				*lpDst = (unsigned char)255;
			}
		}
	}

	// ����ͼ��
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
 *   AddMinusDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LPSTR lpDIBBitsBK  - ָ�򱳾�DIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *	 bool  bAddMinus	- Ϊtrueʱִ�м����㣬����ִ�м����㡣
 *
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�����ͼ����мӼ����㡣
 * 
 * Ҫ��Ŀ��ͼ��Ϊ255���Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL WINAPI AddMinusDIB(LPSTR lpDIBBits, LPSTR lpDIBBitsBK, LONG lWidth, LONG lHeight ,bool bAddMinus)
{
	
	// ָ��Դͼ���ָ��
	LPSTR	lpSrc,lpSrcBK;
	
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//ѭ������
	long i;
	long j;

	//����ֵ
	unsigned char pixel,pixelBK;

	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;

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

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);

	for (j = 0;j < lHeight ;j++)
	{
		for(i = 0;i < lWidth ;i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (char *)lpDIBBits + lLineBytes * j + i;
			lpSrcBK = (char *)lpDIBBitsBK + lLineBytes * j + i;
	
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst = (char *)lpNewDIBBits + lLineBytes * j + i;

			pixel = (unsigned char)*lpSrc;
			pixelBK = (unsigned char)*lpSrcBK;
			if(bAddMinus)
				*lpDst = pixel + pixelBK > 255 ? 255 : pixel + pixelBK;
			else
				*lpDst = pixel - pixelBK < 0 ? 0 : pixel - pixelBK;


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
 *   HprojectDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�����ͼ�����ˮƽͶӰ���㡣
 * 
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL WINAPI HprojectDIB(LPSTR lpDIBBits,LONG lWidth, LONG lHeight)
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

	//ͼ����ÿ���ڵĺڵ����
	long lWhiteNumber;

	//����ֵ
	unsigned char pixel;

	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;

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

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);

	for (j = 0;j < lHeight ;j++)
	{
		lWhiteNumber = 0;
		for(i = 0;i < lWidth ;i++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (char *)lpDIBBits + lLineBytes * j + i;
	
			pixel = (unsigned char)*lpSrc;

			if (pixel != 255 && pixel != 0)
			{
				return false;
			}
			if(pixel == 0)
			{
				lWhiteNumber++;
			}
		}
		for(i = 0;i < lWhiteNumber ;i++)
		{	
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst = (char *)lpNewDIBBits + lLineBytes * j + i;

			*lpDst = (unsigned char)0;
		}		
	}

			
	// ����ͶӰͼ��
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
 *   VprojectDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�����ͼ����д�ֱͶӰ���㡣
 * 
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL WINAPI VprojectDIB(LPSTR lpDIBBits,LONG lWidth, LONG lHeight)
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

	//ͼ����ÿ���ڵĺڵ����
	long lWhiteNumber;

	//����ֵ
	unsigned char pixel;

	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;

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

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);

	for (i = 0;i < lWidth ;i++)
	{
		lWhiteNumber = 0;
		for(j = 0;j < lHeight ;j++)
		{
			// ָ��Դͼ������j�У���i�����ص�ָ��			
			lpSrc = (char *)lpDIBBits + lLineBytes * j + i;
	
			pixel = (unsigned char)*lpSrc;

			if (pixel != 255 && pixel != 0)
			{
				return false;
			}
			if(pixel == 255)
			{
				lWhiteNumber++;
			}
		}
		for(j = 0;j < lWhiteNumber ;j++)
		{	
			// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
			lpDst = (char *)lpNewDIBBits + lLineBytes * j + i;

			*lpDst = (unsigned char)0;
		}		
	}

			
	// ����ͶӰͼ��
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
 *   TemplateMatchDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LPSTR lpDIBBitsBK  - ָ�򱳾�DIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   LONG  lTemplateWidth       - ģ��ͼ���ȣ���������
 *   LONG  lTemplateHeight      - ģ��ͼ��߶ȣ���������
 *
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ�����ģ��ƥ�����㡣
 * 
 * Ҫ��Ŀ��ͼ��Ϊ255���Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL WINAPI TemplateMatchDIB (LPSTR lpDIBBits, LPSTR lpTemplateDIBBits, LONG lWidth, LONG lHeight,
							  LONG lTemplateWidth,LONG lTemplateHeight)
{	
	// ָ��Դͼ���ָ��
	LPSTR	lpSrc,lpTemplateSrc;
	
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//ѭ������
	long i;
	long j;
	long m;
	long n;

	//�м���
	double dSigmaST;
	double dSigmaS;
	double dSigmaT;

	//�����Բ��
	double R;

	//��������Բ��
	double MaxR;

	//��������Գ���λ��
	long lMaxWidth;
	long lMaxHeight;

	//����ֵ
	unsigned char pixel;
	unsigned char templatepixel;

	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes,lTemplateLineBytes;

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

	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	lTemplateLineBytes = WIDTHBYTES(lTemplateWidth * 8);

	//����dSigmaT
	dSigmaT = 0;
	for (n = 0;n < lTemplateHeight ;n++)
	{
		for(m = 0;m < lTemplateWidth ;m++)
		{
			// ָ��ģ��ͼ������j�У���i�����ص�ָ��			
			lpTemplateSrc = (char *)lpTemplateDIBBits + lTemplateLineBytes * n + m;
			templatepixel = (unsigned char)*lpTemplateSrc;
			dSigmaT += (double)templatepixel*templatepixel;
		}
	}

	//�ҵ�ͼ������������Եĳ���λ��
	MaxR = 0.0;
	for (j = 0;j < lHeight - lTemplateHeight +1 ;j++)
	{
		for(i = 0;i < lWidth - lTemplateWidth + 1;i++)
		{
			dSigmaST = 0;
			dSigmaS = 0;
	
			for (n = 0;n < lTemplateHeight ;n++)
			{
				for(m = 0;m < lTemplateWidth ;m++)
				{
					// ָ��Դͼ������j+n�У���i+m�����ص�ָ��			
					lpSrc  = (char *)lpDIBBits + lLineBytes * (j+n) + (i+m);
			
					// ָ��ģ��ͼ������n�У���m�����ص�ָ��			
					lpTemplateSrc  = (char *)lpTemplateDIBBits + lTemplateLineBytes * n + m;

					pixel = (unsigned char)*lpSrc;
					templatepixel = (unsigned char)*lpTemplateSrc;

					dSigmaS += (double)pixel*pixel;
					dSigmaST += (double)pixel*templatepixel;
				}
			}
			//����������
			R = dSigmaST / ( sqrt(dSigmaS)*sqrt(dSigmaT));
			//����������ԱȽ�
			if (R > MaxR)
			{
				MaxR = R;
				lMaxWidth = i;
				lMaxHeight = j;
			}
		}
	}

	//����������Գ������򲿷ָ��Ƶ�Ŀ��ͼ��
	for (n = 0;n < lTemplateHeight ;n++)
	{
		for(m = 0;m < lTemplateWidth ;m++)
		{
			lpTemplateSrc = (char *)lpTemplateDIBBits + lTemplateLineBytes * n + m;
			lpDst = (char *)lpNewDIBBits + lLineBytes * (n+lMaxHeight) + (m+lMaxWidth);
			*lpDst = *lpTemplateSrc;
		}
	}
	
	// ����ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
	return TRUE;
}
