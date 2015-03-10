
/**************************************************************************
 *  �ļ�����TemplateTrans.cpp
 *
 *  ͼ��ģ��任API�����⣺
 *
 *  Template()			- ͼ��ģ��任��ͨ���ı�ģ�壬��������ʵ��
 *						  ͼ���ƽ�����񻯡���Եʶ��Ȳ�����
 *  MedianFilter()		- ͼ����ֵ�˲���
 *  GetMedianNum()		- ��ȡ��ֵ��������MedianFilter()����������ֵ��
 *  ReplaceColorPal()	- ����α��ɫ�����
 *
 *************************************************************************/

#include "stdafx.h"
#include "TemplateTrans.h"
#include "DIBAPI.h"

#include <math.h>
#include <direct.h>

/*************************************************************************
 *
 * �������ƣ�
 *   Template()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int   iTempH		- ģ��ĸ߶�
 *   int   iTempW		- ģ��Ŀ��
 *   int   iTempMX		- ģ�������Ԫ��X���� ( < iTempW - 1)
 *   int   iTempMY		- ģ�������Ԫ��Y���� ( < iTempH - 1)
 *	 FLOAT * fpArray	- ָ��ģ�������ָ��
 *	 FLOAT fCoef		- ģ��ϵ��
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�����ָ����ģ�壨�����С������ͼ����в���������iTempHָ��ģ��
 * �ĸ߶ȣ�����iTempWָ��ģ��Ŀ�ȣ�����iTempMX��iTempMYָ��ģ�������
 * Ԫ�����꣬����fpArrayָ��ģ��Ԫ�أ�fCoefָ��ϵ����
 *
 ************************************************************************/

BOOL WINAPI Template(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, 
					 int iTempH, int iTempW, 
					 int iTempMX, int iTempMY,
					 FLOAT * fpArray, FLOAT fCoef)
{
	// ָ����ͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	
	// ѭ������
	LONG	i;
	LONG	j;
	LONG	k;
	LONG	l;
	
	// ������
	FLOAT	fResult;
	
	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);
	
	// �ж��Ƿ��ڴ����ʧ��
	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);
	
	// ��ʼ��ͼ��Ϊԭʼͼ��
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);
	
	// ��(��ȥ��Ե����)
	for(i = iTempMY; i < lHeight - iTempH + iTempMY + 1; i++)
	{
		// ��(��ȥ��Ե����)
		for(j = iTempMX; j < lWidth - iTempW + iTempMX + 1; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			fResult = 0;
			
			// ����
			for (k = 0; k < iTempH; k++)
			{
				for (l = 0; l < iTempW; l++)
				{
					// ָ��DIB��i - iTempMY + k�У���j - iTempMX + l�����ص�ָ��
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iTempMY - k)
						+ j - iTempMX + l;
					
					// ��������ֵ
					fResult += (* lpSrc) * fpArray[k * iTempW + l];
				}
			}
			
			// ����ϵ��
			fResult *= fCoef;
			
			// ȡ����ֵ
			fResult = (FLOAT ) fabs(fResult);
			
			// �ж��Ƿ񳬹�255
			if(fResult > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				* lpDst = 255;
			}
			else
			{
				// ��ֵ
				* lpDst = (unsigned char) (fResult + 0.5);
			}
			
		}
	}
	
	// ���Ʊ任���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);
	
	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	
	// ����
	return TRUE;

}

/*************************************************************************
 *
 * �������ƣ�
 *   MedianFilter()
 *
 * ����:
 *   LPSTR lpDIBBits		- ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth			- Դͼ���ȣ���������
 *   LONG  lHeight			- Դͼ��߶ȣ���������
 *   int   iFilterH			- �˲����ĸ߶�
 *   int   iFilterW			- �˲����Ŀ��
 *   int   iFilterMX		- �˲���������Ԫ��X����
 *   int   iFilterMY		- �˲���������Ԫ��Y����
 *
 * ����ֵ:
 *   BOOL					- �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�����DIBͼ�������ֵ�˲���
 *
 ************************************************************************/

BOOL WINAPI MedianFilter(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, 
						 int iFilterH, int iFilterW, 
						 int iFilterMX, int iFilterMY)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ָ��Ҫ���������ָ��
	unsigned char*	lpDst;
	
	// ָ����ͼ���ָ��
	LPSTR			lpNewDIBBits;
	HLOCAL			hNewDIBBits;
	
	// ָ���˲��������ָ��
	unsigned char	* aValue;
	HLOCAL			hArray;
	
	// ѭ������
	LONG			i;
	LONG			j;
	LONG			k;
	LONG			l;
	
	// ͼ��ÿ�е��ֽ���
	LONG			lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lLineBytes * lHeight);
	
	// �ж��Ƿ��ڴ����ʧ��
	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);
	
	// ��ʼ��ͼ��Ϊԭʼͼ��
	memcpy(lpNewDIBBits, lpDIBBits, lLineBytes * lHeight);
	
	// ��ʱ�����ڴ棬�Ա����˲�������
	hArray = LocalAlloc(LHND, iFilterH * iFilterW);
	
	// �ж��Ƿ��ڴ����ʧ��
	if (hArray == NULL)
	{
		// �ͷ��ڴ�
		LocalUnlock(hNewDIBBits);
		LocalFree(hNewDIBBits);
		
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	aValue = (unsigned char * )LocalLock(hArray);
	
	// ��ʼ��ֵ�˲�
	// ��(��ȥ��Ե����)
	for(i = iFilterMY; i < lHeight - iFilterH + iFilterMY + 1; i++)
	{
		// ��(��ȥ��Ե����)
		for(j = iFilterMX; j < lWidth - iFilterW + iFilterMX + 1; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			lpDst = (unsigned char*)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// ��ȡ�˲�������
			for (k = 0; k < iFilterH; k++)
			{
				for (l = 0; l < iFilterW; l++)
				{
					// ָ��DIB��i - iFilterMY + k�У���j - iFilterMX + l�����ص�ָ��
					lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i + iFilterMY - k) + j - iFilterMX + l;
					
					// ��������ֵ
					aValue[k * iFilterW + l] = *lpSrc;
				}
			}
			
			// ��ȡ��ֵ
			* lpDst = GetMedianNum(aValue, iFilterH * iFilterW);
		}
	}
	
	// ���Ʊ任���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lLineBytes * lHeight);
	
	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	LocalUnlock(hArray);
	LocalFree(hArray);
	
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   GetMedianNum()
 *
 * ����:
 *   unsigned char * bpArray	- ָ��Ҫ��ȡ��ֵ������ָ��
 *   int   iFilterLen			- ���鳤��
 *
 * ����ֵ:
 *   unsigned char      - ����ָ���������ֵ��
 *
 * ˵��:
 *   �ú�����ð�ݷ���һά����������򣬲���������Ԫ�ص���ֵ��
 *
 ************************************************************************/

unsigned char WINAPI GetMedianNum(unsigned char * bArray, int iFilterLen)
{
	// ѭ������
	int		i;
	int		j;
	
	// �м����
	unsigned char bTemp;
	
	// ��ð�ݷ��������������
	for (j = 0; j < iFilterLen - 1; j ++)
	{
		for (i = 0; i < iFilterLen - j - 1; i ++)
		{
			if (bArray[i] > bArray[i + 1])
			{
				// ����
				bTemp = bArray[i];
				bArray[i] = bArray[i + 1];
				bArray[i + 1] = bTemp;
			}
		}
	}
	
	// ������ֵ
	if ((iFilterLen & 1) > 0)
	{
		// ������������Ԫ�أ������м�һ��Ԫ��
		bTemp = bArray[(iFilterLen + 1) / 2];
	}
	else
	{
		// ������ż����Ԫ�أ������м�����Ԫ��ƽ��ֵ
		bTemp = (bArray[iFilterLen / 2] + bArray[iFilterLen / 2 + 1]) / 2;
	}
	
	// ������ֵ
	return bTemp;
}

/*************************************************************************
 *
 * �������ƣ�
 *   GradSharp()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   BYTE  bThre		- ��ֵ
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ������ݶ��񻯡�
 *
 ************************************************************************/
BOOL WINAPI GradSharp(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	unsigned char*	lpSrc1;
	unsigned char*	lpSrc2;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// �м����
	BYTE	bTemp;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc  = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// ָ��DIB��i+1�У���j�����ص�ָ��
			lpSrc1 = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 2 - i) + j;
			
			// ָ��DIB��i�У���j+1�����ص�ָ��
			lpSrc2 = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j + 1;
			
			bTemp = abs((*lpSrc)-(*lpSrc1)) + abs((*lpSrc)-(*lpSrc2));
			
			// �ж��Ƿ�С����ֵ
			if (bTemp < 255)
			{
				// �ж��Ƿ������ֵ������С��������Ҷ�ֵ���䡣
				if (bTemp >= bThre)
				{
					// ֱ�Ӹ�ֵΪbTemp
					*lpSrc = bTemp;
				}
			}
			else
			{
				// ֱ�Ӹ�ֵΪ255
				*lpSrc = 255;
			}
		}
	}
	
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   ReplaceColorPal()
 *
 * ����:
 *   LPSTR lpDIB			- ָ��ԴDIBͼ��ָ��
 *   BYTE * bpColorsTable	- α��ɫ�����
 *
 * ����ֵ:
 *   BOOL					- �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�����ָ����α��ɫ��������滻ͼ��ĵ��԰壬����bpColorsTable
 * ָ��Ҫ�滻��α��ɫ�����
 *
 ************************************************************************/
BOOL WINAPI ReplaceColorPal(LPSTR lpDIB, BYTE * bpColorsTable)
{
	
	// ѭ������
	int i;
	
	// ��ɫ���е���ɫ��Ŀ
	WORD wNumColors;
	
	// ָ��BITMAPINFO�ṹ��ָ�루Win3.0��
	LPBITMAPINFO lpbmi;
	
	// ָ��BITMAPCOREINFO�ṹ��ָ��
	LPBITMAPCOREINFO lpbmc;
	
	// �����Ƿ���Win3.0 DIB�ı��
	BOOL bWinStyleDIB;
	
	// �������
	BOOL bResult = FALSE;
	
	// ��ȡָ��BITMAPINFO�ṹ��ָ�루Win3.0��
	lpbmi = (LPBITMAPINFO)lpDIB;
	
	// ��ȡָ��BITMAPCOREINFO�ṹ��ָ��
	lpbmc = (LPBITMAPCOREINFO)lpDIB;
	
	// ��ȡDIB����ɫ���е���ɫ��Ŀ
	wNumColors = ::DIBNumColors(lpDIB);
		
	// �ж���ɫ��Ŀ�Ƿ���256ɫ
	if (wNumColors == 256)
	{
		
		// �ж��Ƿ���WIN3.0��DIB
		bWinStyleDIB = IS_WIN30_DIB(lpDIB);
		
		// ��ȡα��ɫ���룬����DIB��ɫ��
		for (i = 0; i < (int)wNumColors; i++)
		{
			if (bWinStyleDIB)
			{
				// ����DIB��ɫ���ɫ����
				lpbmi->bmiColors[i].rgbRed = bpColorsTable[i * 4];
				
				// ����DIB��ɫ����ɫ����
				lpbmi->bmiColors[i].rgbGreen = bpColorsTable[i * 4 + 1];
				
				// ����DIB��ɫ����ɫ����
				lpbmi->bmiColors[i].rgbBlue = bpColorsTable[i * 4 + 2];
				
				// ����DIB��ɫ�屣��λ
				lpbmi->bmiColors[i].rgbReserved = 0;
			}
			else
			{
				// ����DIB��ɫ���ɫ����
				lpbmc->bmciColors[i].rgbtRed = bpColorsTable[i * 4];
				
				// ����DIB��ɫ����ɫ����
				lpbmc->bmciColors[i].rgbtGreen = bpColorsTable[i * 4 + 1];
				
				// ����DIB��ɫ����ɫ����
				lpbmc->bmciColors[i].rgbtBlue = bpColorsTable[i * 4 + 2];
			}
		}
	}
	
	// ����
	return bResult;	

}