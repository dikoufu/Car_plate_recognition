
/**************************************************************************
 *  �ļ�����PointTrans.cpp
 *
 *  ͼ�������API�����⣺
 *
 *  LinerTrans()		- ͼ�����Ա任
 *	WindowTrans()		- ͼ�񴰿ڱ任
 *  GrayStretch()		- ͼ��Ҷ�����
 *  InteEqualize()		��ֱ��ͼ����
 *
 *************************************************************************/

#include "stdafx.h"
#include "PointTrans.h"
#include "DIBAPI.h"

#include <math.h>
#include <direct.h>

/*************************************************************************
 *
 * �������ƣ�
 *   LinerTrans()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   FLOAT fA		    - ���Ա任��б��
 *   FLOAT fB           - ���Ա任�Ľؾ�
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����лҶȵ����Ա任������
 *
 ************************************************************************/

BOOL WINAPI LinerTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, FLOAT fA, FLOAT fB)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// �м����
	FLOAT	fTemp;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// ���Ա任
			fTemp = fA * (*lpSrc) + fB;
			
			// �ж��Ƿ񳬳���Χ
			if (fTemp > 255)
			{
				// ֱ�Ӹ�ֵΪ255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
			}
			else
			{
				// ��������
				*lpSrc = (unsigned char) (fTemp + 0.5);
			}
		}
	}
	
	// ����
	return TRUE;

}

/*************************************************************************
 *
 * �������ƣ�
 *   ThresholdTrans()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   BYTE  bThre	    - ��ֵ
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ�������ֵ�任�����ڻҶ�ֵС����ֵ������ֱ������
 * �Ҷ�ֵΪ0���Ҷ�ֵ������ֵ������ֱ������Ϊ255��
 *
 ************************************************************************/
BOOL WINAPI ThresholdTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// �ж��Ƿ�С����ֵ
			if ((*lpSrc) < bThre)
			{
				// ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
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
 *   WindowTrans()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   BYTE  bLow		    - ��������
 *   BYTE  bUp          - ��������
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����д��ڱ任��ֻ���ڴ��ڷ�Χ�ڵĻҶȱ��ֲ��䣬
 * С�����޵�����ֱ�����ûҶ�ֵΪ0���������޵�����ֱ�����ûҶ�ֵΪ255��
 *
 ************************************************************************/
BOOL WINAPI WindowTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bLow, BYTE bUp)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// �ж��Ƿ񳬳���Χ
			if ((*lpSrc) < bLow)
			{
				// ֱ�Ӹ�ֵΪ0
				*lpSrc = 0;
			}
			else if ((*lpSrc) > bUp)
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
 *   GrayStretch()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   BYTE bX1			- �Ҷ������һ�����X����
 *   BYTE bY1			- �Ҷ������һ�����Y����
 *   BYTE bX2			- �Ҷ�����ڶ������X����
 *   BYTE bY2			- �Ҷ�����ڶ������Y����
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ����лҶ����졣
 *
 ************************************************************************/
BOOL WINAPI GrayStretch(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// �Ҷ�ӳ���
	BYTE	bMap[256];
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ����Ҷ�ӳ���
	for (i = 0; i <= bX1; i++)
	{
		// �ж�bX1�Ƿ����0����ֹ��ĸΪ0��
		if (bX1 > 0)
		{
			// ���Ա任
			bMap[i] = (BYTE) bY1 * i / bX1;
		}
		else
		{
			// ֱ�Ӹ�ֵΪ0
			bMap[i] = 0;
		}
	}
	for (; i <= bX2; i++)
	{
		// �ж�bX1�Ƿ����bX2����ֹ��ĸΪ0��
		if (bX2 != bX1)
		{
			// ���Ա任
			bMap[i] = bY1 + (BYTE) ((bY2 - bY1) * (i - bX1) / (bX2 - bX1));
		}
		else
		{
			// ֱ�Ӹ�ֵΪbY1
			bMap[i] = bY1;
		}
	}
	for (; i < 256; i++)
	{
		// �ж�bX2�Ƿ����255����ֹ��ĸΪ0��
		if (bX2 != 255)
		{
			// ���Ա任
			bMap[i] = bY2 + (BYTE) ((255 - bY2) * (i - bX2) / (255 - bX2));
		}
		else
		{
			// ֱ�Ӹ�ֵΪ255
			bMap[i] = 255;
		}
	}
	
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// �����µĻҶ�ֵ
			*lpSrc = bMap[*lpSrc];
		}
	}
	
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   InteEqualize()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *
 * ����ֵ:
 *   BOOL               - �ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú���������ͼ�����ֱ��ͼ���⡣
 *
 ************************************************************************/
BOOL WINAPI InteEqualize(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ��ʱ����
	LONG	lTemp;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// �Ҷ�ӳ���
	BYTE	bMap[256];
	
	// �Ҷ�ӳ���
	LONG	lCount[256];
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ���ü���Ϊ0
	for (i = 0; i < 256; i ++)
	{
		// ����
		lCount[i] = 0;
	}
	
	// ��������Ҷ�ֵ�ļ���
	for (i = 0; i < lHeight; i ++)
	{
		for (j = 0; j < lWidth; j ++)
		{
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * i + j;
			
			// ������1
			lCount[*(lpSrc)]++;
		}
	}
	
	// ����Ҷ�ӳ���
	for (i = 0; i < 256; i++)
	{
		// ��ʼΪ0
		lTemp = 0;
		
		for (j = 0; j <= i ; j++)
		{
			lTemp += lCount[j];
		}
		
		// �����Ӧ���»Ҷ�ֵ
		bMap[i] = (BYTE) (lTemp * 255 / lHeight / lWidth);
	}
	
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// �����µĻҶ�ֵ
			*lpSrc = bMap[*lpSrc];
		}
	}
	
	// ����
	return TRUE;
}
