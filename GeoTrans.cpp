/**************************************************************************
 *  �ļ�����GeoTrans.cpp
 *
 *  ͼ�񼸺α任API�����⣺
 *
 *  TranslationDIB1()   - ͼ��ƽ��
 *  TranslationDIB()    - ͼ��ƽ��
 *  MirrorDIB()		    - ͼ����
 *  TransposeDIB()		- ͼ��ת��
 *  ZoomDIB()			- ͼ������
 *  RotateDIB()			- ͼ����ת
 *
 *************************************************************************/

#include "stdafx.h"
#include "geotrans.h"
#include "DIBAPI.h"

#include <math.h>
#include <direct.h>

/*************************************************************************
 *
 * �������ƣ�
 *   TranslationDIB1()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   LONG  lXOffset     - X��ƽ��������������
 *   LONG  lYOffset     - Y��ƽ��������������
 *
 * ����ֵ:
 *   BOOL               - ƽ�Ƴɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�������ˮƽ�ƶ�DIBͼ�񡣺�������ı�ͼ��Ĵ�С���Ƴ��Ĳ���ͼ��
 * ����ȥ���հײ����ð�ɫ��䡣
 *
 ************************************************************************/

BOOL WINAPI TranslationDIB1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lXOffset, LONG lYOffset)
{
	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;
	
	// ָ��Ҫ���������ָ��
	LPSTR	lpDst;
	
	// ָ����ͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	// ��������DIB�е�����
	LONG	i;
	LONG	j;
	
	// ������ԴDIB�е�����
	LONG	i0;
	LONG	j0;
	
	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;
	
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
	
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			// ע������DIB��ͼ���һ����ʵ���������һ�е�λ�ã����lpDst
			// ֵ����(char *)lpNewDIBBits + lLineBytes * i + j������
			// (char *)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j
			lpDst = (char *)lpNewDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// �����������ԴDIB�е�����
			i0 = i - lXOffset;
			j0 = j - lYOffset;
			
			// �ж��Ƿ���Դͼ��Χ��
			if( (j0 >= 0) && (j0 < lWidth) && (i0 >= 0) && (i0 < lHeight))
			{
				// ָ��ԴDIB��i0�У���j0�����ص�ָ��
				// ͬ��Ҫע��DIB���µ��õ�����
				lpSrc = (char *)lpDIBBits + lLineBytes * (lHeight - 1 - i0) + j0;
				
				// ��������
				*lpDst = *lpSrc;
			}
			else
			{
				// ����Դͼ��û�е����أ�ֱ�Ӹ�ֵΪ255
				* ((unsigned char*)lpDst) = 255;
			}
			
		}
	}
	
	// ����ƽ�ƺ��ͼ��
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
 *   TranslationDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   LONG  lXOffset     - X��ƽ��������������
 *   LONG  lYOffset     - Y��ƽ��������������
 *
 * ����ֵ:
 *   BOOL               - ƽ�Ƴɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�������ˮƽ�ƶ�DIBͼ�񡣺�������ı�ͼ��Ĵ�С���Ƴ��Ĳ���ͼ��
 * ����ȥ���հײ����ð�ɫ��䡣
 *
 ************************************************************************/

BOOL WINAPI TranslationDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lXOffset, LONG lYOffset)
{
	// ƽ�ƺ�ʣ��ͼ����Դͼ���е�λ�ã���������
	CRect	rectSrc;
	
	// ƽ�ƺ�ʣ��ͼ������ͼ���е�λ�ã���������
	CRect	rectDst;
	
	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;
	
	// ָ��Ҫ���������ָ��
	LPSTR	lpDst;
	
	// ָ����ͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;
	
	// ָ��ͼ���Ƿ�ȫ����ȥ��������
	BOOL	bVisible;

	// ѭ������
	LONG	i;
	
	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ����ֵ
	bVisible = TRUE;
	
	// ����rectSrc��rectDst��X����
	if (lXOffset <= -lWidth)
	{
		// X�᷽��ȫ���Ƴ���������
		bVisible = FALSE;
	}
	else if (lXOffset <= 0)
	{
		// �ƶ�����ͼ�������Ͻ�X����Ϊ0
		rectDst.left = 0;
		
		// �ƶ�����ͼ�������½�X����ΪlWidth - |lXOffset| = lWidth + lXOffset
		rectDst.right = lWidth + lXOffset;
	}
	else if (lXOffset < lWidth)
	{
		// �ƶ�����ͼ�������Ͻ�X����ΪlXOffset
		rectDst.left = lXOffset;
		
		// �ƶ�����ͼ�������½�X����ΪlWidth
		rectDst.right = lWidth;
	}
	else
	{
		// X�᷽��ȫ���Ƴ���������
		bVisible = FALSE;
	}
	
	// ƽ�ƺ�ʣ��ͼ����Դͼ���е�X����
	rectSrc.left = rectDst.left - lXOffset;
	rectSrc.right = rectDst.right - lXOffset;
	
	//  ����rectSrc��rectDst��Y����
	if (lYOffset <= -lHeight)
	{
		// Y�᷽��ȫ���Ƴ���������
		bVisible = FALSE;
	}
	else if (lYOffset <= 0)
	{
		// �ƶ�����ͼ�������Ͻ�Y����Ϊ0
		rectDst.top = 0;
		
		// �ƶ�����ͼ�������½�Y����ΪlHeight - |lYOffset| = lHeight + lYOffset
		rectDst.bottom = lHeight + lYOffset;
	}
	else if (lYOffset < lHeight)
	{
		// �ƶ�����ͼ�������Ͻ�Y����ΪlYOffset
		rectDst.top = lYOffset;
		
		// �ƶ�����ͼ�������½�Y����ΪlHeight
		rectDst.bottom = lHeight;
	}
	else
	{
		// X�᷽��ȫ���Ƴ���������
		bVisible = FALSE;
	}
	
	// ƽ�ƺ�ʣ��ͼ����Դͼ���е�Y����
	rectSrc.top = rectDst.top - lYOffset;
	rectSrc.bottom = rectDst.bottom - lYOffset;
	
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
	
	// ����в���ͼ��ɼ�
	if (bVisible)
	{

		// ƽ��ͼ��
		for(i = 0; i < (rectSrc.bottom - rectSrc.top); i++)
		{
			// Ҫ�����������㣬ע������DIBͼ�����������µ��õģ���һ�������Ǳ��������
			// һ�У���˸����������㲻��lpDIBBits + lLineBytes * (i + rectSrc.top) + 
			// rectSrc.left������ lpDIBBits + lLineBytes * (lHeight - i - rectSrc.top - 1) + 
			// rectSrc.left��
			
			lpSrc = (char *)lpDIBBits + lLineBytes * (lHeight - i - rectSrc.top - 1) + rectSrc.left;
			
			// ҪĿ����������
			// ͬ��ע�����µ��õ����⡣
			lpDst = (char *)lpNewDIBBits + lLineBytes * (lHeight - i - rectDst.top - 1) + 
				rectDst.left;
			
			// ����ÿһ�У����ΪrectSrc.right - rectSrc.left
			memcpy(lpDst, lpSrc, rectSrc.right - rectSrc.left);
			
		}
	}

	// ����ƽ�ƺ��ͼ��
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
 *   MirrorDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   BOOL  bDirection   - ����ķ���TRUE��ʾˮƽ����FALSE��ʾ��ֱ����
 *
 * ����ֵ:
 *   BOOL               - ����ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�����������DIBͼ�񡣿���ָ������ķ�ʽ��ˮƽ���Ǵ�ֱ��
 *
 ************************************************************************/

BOOL WINAPI MirrorDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BOOL bDirection)
{
	
	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;
	
	// ָ��Ҫ���������ָ��
	LPSTR	lpDst;
	
	// ָ����ͼ���ָ��
	LPSTR	lpBits;
	HLOCAL	hBits;

	// ѭ������
	LONG	i;
	LONG	j;
	
	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ��ʱ�����ڴ棬�Ա���һ��ͼ��
	hBits = LocalAlloc(LHND, lLineBytes);
	if (hBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpBits = (char * )LocalLock(hBits);
	
	// �жϾ���ʽ
	if (bDirection)
	{
		// ˮƽ����
		
		// ���ͼ��ÿ�н��в���
		for(i = 0; i < lHeight; i++)
		{
			// ���ÿ��ͼ����벿�ֽ��в���
			for(j = 0; j < lWidth / 2; j++)
			{
				
				// ָ������i�У���j�����ص�ָ��
				lpSrc = (char *)lpDIBBits + lLineBytes * i + j;
				
				// ָ������i�У�������j�����ص�ָ��
				lpDst = (char *)lpDIBBits + lLineBytes * (i + 1) - j;
				
				// ����һ������
				*lpBits = *lpDst;
				
				// ��������i�У���j�����ظ��Ƶ�������i�У�������j������
				*lpDst = *lpSrc;
				
				// ��������i�У�������j�����ظ��Ƶ�������i�У���j������
				*lpSrc = *lpBits;
			}
			
		}
	}
	else
	{
		// ��ֱ����

		// ����ϰ�ͼ����в���
		for(i = 0; i < lHeight / 2; i++)
		{
			
			// ָ������i����������ָ��
			lpSrc = (char *)lpDIBBits + lLineBytes * i;
			
			// ָ���i����������ָ��
			lpDst = (char *)lpDIBBits + lLineBytes * (lHeight - i - 1);
			
			// ����һ�У����ΪlWidth
			memcpy(lpBits, lpDst, lLineBytes);
			
			// ��������i�����ظ��Ƶ���i��
			memcpy(lpDst, lpSrc, lLineBytes);
			
			// ����i�����ظ��Ƶ�������i��
			memcpy(lpSrc, lpBits, lLineBytes);
			
		}
	}
	
	// �ͷ��ڴ�
	LocalUnlock(hBits);
	LocalFree(hBits);
	
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   TransposeDIB()
 *
 * ����:
 *   LPSTR lpDIB		- ָ��ԴDIB��ָ��
 *
 * ����ֵ:
 *   BOOL               - ת�óɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 *   �ú�������ת��DIBͼ�񣬼�ͼ��x��y���껥��������������ı�ͼ��Ĵ�С��
 * ����ͼ��ĸ߿�������
 *
 ************************************************************************/

BOOL WINAPI TransposeDIB(LPSTR lpDIB)
{
	
	// ͼ��Ŀ�Ⱥ͸߶�
	LONG	lWidth;
	LONG	lHeight;
	
	// ָ��Դͼ���ָ��
	LPSTR	lpDIBBits;
	
	// ָ��Դ���ص�ָ��
	LPSTR	lpSrc;
	
	// ָ��ת��ͼ���Ӧ���ص�ָ��
	LPSTR	lpDst;

	// ָ��ת��ͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;
	
	// ָ��BITMAPINFO�ṹ��ָ�루Win3.0��
	LPBITMAPINFOHEADER lpbmi;
	
	// ָ��BITMAPCOREINFO�ṹ��ָ��
	LPBITMAPCOREHEADER lpbmc;

	// ѭ������
	LONG	i;
	LONG	j;
	
	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;
	
	// ��ͼ��ÿ�е��ֽ���
	LONG lNewLineBytes;

	// ��ȡָ��
	lpbmi = (LPBITMAPINFOHEADER)lpDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpDIB;

	// �ҵ�ԴDIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ��ȡͼ���"���"��4�ı�����
	lWidth = ::DIBWidth(lpDIB);
	
	// ��ȡͼ��ĸ߶�
	lHeight = ::DIBHeight(lpDIB);
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ������ͼ��ÿ�е��ֽ���
	lNewLineBytes = WIDTHBYTES(lHeight * 8);
	
	// ��ʱ�����ڴ棬�Ա�����ͼ��
	hNewDIBBits = LocalAlloc(LHND, lWidth * lNewLineBytes);

	// �ж��Ƿ��ڴ����ʧ��
	if (hNewDIBBits == NULL)
	{
		// �����ڴ�ʧ��
		return FALSE;
	}
	
	// �����ڴ�
	lpNewDIBBits = (char * )LocalLock(hNewDIBBits);
	
	// ���ͼ��ÿ�н��в���
	for(i = 0; i < lHeight; i++)
	{
		// ���ÿ��ͼ��ÿ�н��в���
		for(j = 0; j < lWidth; j++)
		{
			
			// ָ��ԴDIB��i�У���j�����ص�ָ��
			lpSrc = (char *)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// ָ��ת��DIB��j�У���i�����ص�ָ��
			// ע��˴�lWidth��lHeight��ԴDIB�Ŀ�Ⱥ͸߶ȣ�Ӧ�û���
			lpDst = (char *)lpNewDIBBits + lNewLineBytes * (lWidth - 1 - j) + i;
			
			// ��������
			*lpDst = *lpSrc;
			
		}
		
	}
	
	// ����ת�ú��ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lNewLineBytes);
	
	// ����DIB��ͼ��ĸ߿�
	if (IS_WIN30_DIB(lpDIB))
	{
		// ����Windows 3.0 DIB
		lpbmi->biWidth = lHeight;
		
		lpbmi->biHeight = lWidth;
	}
	else
	{
		// ����������ʽ��DIB
		lpbmc->bcWidth = (unsigned short) lHeight;
		lpbmc->bcHeight = (unsigned short) lWidth;
	}
	
	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);
	
	// ����
	return TRUE;
}


/*************************************************************************
 *
 * �������ƣ�
 *   ZoomDIB()
 *
 * ����:
 *   LPSTR lpDIB		- ָ��ԴDIB��ָ��
 *   float fXZoomRatio	- X�᷽�����ű���
 *   float fYZoomRatio	- Y�᷽�����ű���
 *
 * ����ֵ:
 *   HGLOBAL            - ���ųɹ�������DIB��������򷵻�NULL��
 *
 * ˵��:
 *   �ú�����������DIBͼ�񣬷���������DIB�ľ����
 *
 ************************************************************************/

HGLOBAL WINAPI ZoomDIB(LPSTR lpDIB, float fXZoomRatio, float fYZoomRatio)
{
	
	// Դͼ��Ŀ�Ⱥ͸߶�
	LONG	lWidth;
	LONG	lHeight;
	
	// ���ź�ͼ��Ŀ�Ⱥ͸߶�
	LONG	lNewWidth;
	LONG	lNewHeight;
	
	// ���ź�ͼ��Ŀ�ȣ�lNewWidth'��������4�ı�����
	LONG	lNewLineBytes;
	
	// ָ��Դͼ���ָ��
	LPSTR	lpDIBBits;
	
	// ָ��Դ���ص�ָ��
	LPSTR	lpSrc;
	
	// ���ź���DIB���
	HDIB	hDIB;
	
	// ָ������ͼ���Ӧ���ص�ָ��
	LPSTR	lpDst;
	
	// ָ������ͼ���ָ��
	LPSTR	lpNewDIB;
	LPSTR	lpNewDIBBits;
	
	// ָ��BITMAPINFO�ṹ��ָ�루Win3.0��
	LPBITMAPINFOHEADER lpbmi;
	
	// ָ��BITMAPCOREINFO�ṹ��ָ��
	LPBITMAPCOREHEADER lpbmc;
	
	// ѭ����������������DIB�е����꣩
	LONG	i;
	LONG	j;
	
	// ������ԴDIB�е�����
	LONG	i0;
	LONG	j0;
	
	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;
	
	// �ҵ�ԴDIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ��ȡͼ��Ŀ��
	lWidth = ::DIBWidth(lpDIB);
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ��ȡͼ��ĸ߶�
	lHeight = ::DIBHeight(lpDIB);
	
	// �������ź��ͼ��ʵ�ʿ��
	// �˴�ֱ�Ӽ�0.5������ǿ������ת��ʱ���������룬����ֱ�ӽ�ȥС������
	lNewWidth = (LONG) (::DIBWidth(lpDIB) * fXZoomRatio + 0.5);
	
	// ������ͼ��ÿ�е��ֽ���
	lNewLineBytes = WIDTHBYTES(lNewWidth * 8);
	
	// �������ź��ͼ��߶�
	lNewHeight = (LONG) (lHeight * fYZoomRatio + 0.5);
	
	// �����ڴ棬�Ա�����DIB
	hDIB = (HDIB) ::GlobalAlloc(GHND, lNewLineBytes * lNewHeight + *(LPDWORD)lpDIB + ::PaletteSize(lpDIB));
	
	// �ж��Ƿ��ڴ����ʧ��
	if (hDIB == NULL)
	{
		// �����ڴ�ʧ��
		return NULL;
	}
	
	// �����ڴ�
	lpNewDIB =  (char * )::GlobalLock((HGLOBAL) hDIB);
	
	// ����DIB��Ϣͷ�͵�ɫ��
	memcpy(lpNewDIB, lpDIB, *(LPDWORD)lpDIB + ::PaletteSize(lpDIB));
	
	// �ҵ���DIB������ʼλ��
	lpNewDIBBits = ::FindDIBBits(lpNewDIB);
	
	// ��ȡָ��
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;
	
	// ����DIB��ͼ��ĸ߶ȺͿ��
	if (IS_WIN30_DIB(lpNewDIB))
	{
		// ����Windows 3.0 DIB
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		// ����������ʽ��DIB
		lpbmc->bcWidth = (unsigned short) lNewWidth;
		lpbmc->bcHeight = (unsigned short) lNewHeight;
	}
	
	// ���ͼ��ÿ�н��в���
	for(i = 0; i < lNewHeight; i++)
	{
		// ���ͼ��ÿ�н��в���
		for(j = 0; j < lNewWidth; j++)
		{
			
			// ָ����DIB��i�У���j�����ص�ָ��
			// ע��˴���Ⱥ͸߶�����DIB�Ŀ�Ⱥ͸߶�
			lpDst = (char *)lpNewDIBBits + lNewLineBytes * (lNewHeight - 1 - i) + j;
			
			// �����������ԴDIB�е�����
			i0 = (LONG) (i / fYZoomRatio + 0.5);
			j0 = (LONG) (j / fXZoomRatio + 0.5);
			
			// �ж��Ƿ���Դͼ��Χ��
			if( (j0 >= 0) && (j0 < lWidth) && (i0 >= 0) && (i0 < lHeight))
			{
				
				// ָ��ԴDIB��i0�У���j0�����ص�ָ��
				lpSrc = (char *)lpDIBBits + lLineBytes * (lHeight - 1 - i0) + j0;
				
				// ��������
				*lpDst = *lpSrc;
			}
			else
			{
				// ����Դͼ��û�е����أ�ֱ�Ӹ�ֵΪ255
				* ((unsigned char*)lpDst) = 255;
			}
			
		}
		
	}
	
	// ����
	return hDIB;
}

/*************************************************************************
 *
 * �������ƣ�
 *   RotateDIB()
 *
 * ����:
 *   LPSTR lpDIB		- ָ��ԴDIB��ָ��
 *   int iRotateAngle	- ��ת�ĽǶȣ�0-360�ȣ�
 *
 * ����ֵ:
 *   HGLOBAL            - ��ת�ɹ�������DIB��������򷵻�NULL��
 *
 * ˵��:
 *   �ú���������ͼ������Ϊ������תDIBͼ�񣬷���������DIB�ľ����
 * ���øú������Զ�����ͼ������ʾ���е����ء������в������ڽ���
 * ֵ�㷨���в�ֵ��
 *
 ************************************************************************/

HGLOBAL WINAPI RotateDIB(LPSTR lpDIB, int iRotateAngle)
{
	
	// Դͼ��Ŀ�Ⱥ͸߶�
	LONG	lWidth;
	LONG	lHeight;
	
	// ��ת��ͼ��Ŀ�Ⱥ͸߶�
	LONG	lNewWidth;
	LONG	lNewHeight;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ��ת��ͼ��Ŀ�ȣ�lNewWidth'��������4�ı�����
	LONG	lNewLineBytes;
	
	// ָ��Դͼ���ָ��
	LPSTR	lpDIBBits;
	
	// ָ��Դ���ص�ָ��
	LPSTR	lpSrc;
	
	// ��ת����DIB���
	HDIB	hDIB;
	
	// ָ����תͼ���Ӧ���ص�ָ��
	LPSTR	lpDst;
	
	// ָ����תͼ���ָ��
	LPSTR	lpNewDIB;
	LPSTR	lpNewDIBBits;
	
	// ָ��BITMAPINFO�ṹ��ָ�루Win3.0��
	LPBITMAPINFOHEADER lpbmi;
	
	// ָ��BITMAPCOREINFO�ṹ��ָ��
	LPBITMAPCOREHEADER lpbmc;
	
	// ѭ����������������DIB�е����꣩
	LONG	i;
	LONG	j;
	
	// ������ԴDIB�е�����
	LONG	i0;
	LONG	j0;
	
	// ��ת�Ƕȣ����ȣ�
	float	fRotateAngle;
	
	// ��ת�Ƕȵ����Һ�����
	float	fSina, fCosa;
	
	// Դͼ�ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	float	fSrcX1,fSrcY1,fSrcX2,fSrcY2,fSrcX3,fSrcY3,fSrcX4,fSrcY4;
	
	// ��ת���ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	float	fDstX1,fDstY1,fDstX2,fDstY2,fDstX3,fDstY3,fDstX4,fDstY4;
	
	// �����м䳣��
	float	f1,f2;
	
	// �ҵ�ԴDIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ��ȡͼ���"���"��4�ı�����
	lWidth = ::DIBWidth(lpDIB);
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ��ȡͼ��ĸ߶�
	lHeight = ::DIBHeight(lpDIB);
	
	// ����ת�ǶȴӶ�ת��������
	fRotateAngle = (float) RADIAN(iRotateAngle);
	
	// ������ת�Ƕȵ�����
	fSina = (float) sin((double)fRotateAngle);
	
	// ������ת�Ƕȵ�����
	fCosa = (float) cos((double)fRotateAngle);
	
	// ����ԭͼ���ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	fSrcX1 = (float) (- (lWidth  - 1) / 2);
	fSrcY1 = (float) (  (lHeight - 1) / 2);
	fSrcX2 = (float) (  (lWidth  - 1) / 2);
	fSrcY2 = (float) (  (lHeight - 1) / 2);
	fSrcX3 = (float) (- (lWidth  - 1) / 2);
	fSrcY3 = (float) (- (lHeight - 1) / 2);
	fSrcX4 = (float) (  (lWidth  - 1) / 2);
	fSrcY4 = (float) (- (lHeight - 1) / 2);
	
	// ������ͼ�ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	fDstX1 =  fCosa * fSrcX1 + fSina * fSrcY1;
	fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
	fDstX2 =  fCosa * fSrcX2 + fSina * fSrcY2;
	fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
	fDstX3 =  fCosa * fSrcX3 + fSina * fSrcY3;
	fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
	fDstX4 =  fCosa * fSrcX4 + fSina * fSrcY4;
	fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;
	
	// ������ת���ͼ��ʵ�ʿ��
	lNewWidth  = (LONG) ( max( fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2) ) + 0.5);
	
	// ������ͼ��ÿ�е��ֽ���
	lNewLineBytes = WIDTHBYTES(lNewWidth * 8);
	
	// ������ת���ͼ��߶�
	lNewHeight = (LONG) ( max( fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2) )  + 0.5);
	
	// �������������������Ժ�ÿ�ζ�������
	f1 = (float) (-0.5 * (lNewWidth - 1) * fCosa - 0.5 * (lNewHeight - 1) * fSina
		+ 0.5 * (lWidth  - 1));
	f2 = (float) ( 0.5 * (lNewWidth - 1) * fSina - 0.5 * (lNewHeight - 1) * fCosa
		+ 0.5 * (lHeight - 1));
	
	// �����ڴ棬�Ա�����DIB
	hDIB = (HDIB) ::GlobalAlloc(GHND, lNewLineBytes * lNewHeight + *(LPDWORD)lpDIB + ::PaletteSize(lpDIB));
	
	// �ж��Ƿ��ڴ����ʧ��
	if (hDIB == NULL)
	{
		// �����ڴ�ʧ��
		return NULL;
	}

	// �����ڴ�
	lpNewDIB =  (char * )::GlobalLock((HGLOBAL) hDIB);
	
	// ����DIB��Ϣͷ�͵�ɫ��
	memcpy(lpNewDIB, lpDIB, *(LPDWORD)lpDIB + ::PaletteSize(lpDIB));
	
	// �ҵ���DIB������ʼλ��
	lpNewDIBBits = ::FindDIBBits(lpNewDIB);
	
	// ��ȡָ��
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	// ����DIB��ͼ��ĸ߶ȺͿ��
	if (IS_WIN30_DIB(lpNewDIB))
	{
		// ����Windows 3.0 DIB
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		// ����������ʽ��DIB
		lpbmc->bcWidth = (unsigned short) lNewWidth;
		lpbmc->bcHeight = (unsigned short) lNewHeight;
	}
	
	// ���ͼ��ÿ�н��в���
	for(i = 0; i < lNewHeight; i++)
	{
		// ���ͼ��ÿ�н��в���
		for(j = 0; j < lNewWidth; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			// ע��˴���Ⱥ͸߶�����DIB�Ŀ�Ⱥ͸߶�
			lpDst = (char *)lpNewDIBBits + lNewLineBytes * (lNewHeight - 1 - i) + j;
			
			// �����������ԴDIB�е�����
			i0 = (LONG) (-((float) j) * fSina + ((float) i) * fCosa + f2 + 0.5);
			j0 = (LONG) ( ((float) j) * fCosa + ((float) i) * fSina + f1 + 0.5);
			
			// �ж��Ƿ���Դͼ��Χ��
			if( (j0 >= 0) && (j0 < lWidth) && (i0 >= 0) && (i0 < lHeight))
			{
				// ָ��ԴDIB��i0�У���j0�����ص�ָ��
				lpSrc = (char *)lpDIBBits + lLineBytes * (lHeight - 1 - i0) + j0;
				
				// ��������
				*lpDst = *lpSrc;
			}
			else
			{
				// ����Դͼ��û�е����أ�ֱ�Ӹ�ֵΪ255
				* ((unsigned char*)lpDst) = 255;
			}
			
		}
		
	}
	
	// ����
	return hDIB;
}


/*************************************************************************
 *
 * �������ƣ�
 *   RotateDIB2()
 *
 * ����:
 *   LPSTR lpDIB		- ָ��ԴDIB��ָ��
 *   int iRotateAngle	- ��ת�ĽǶȣ�0-360�ȣ�
 *
 * ����ֵ:
 *   HGLOBAL            - ��ת�ɹ�������DIB��������򷵻�NULL��
 *
 * ˵��:
 *   �ú���������ͼ������Ϊ������תDIBͼ�񣬷���������DIB�ľ����
 * ���øú������Զ�����ͼ������ʾ���е����ء������в���˫���Բ�
 * ֵ�㷨���в�ֵ��
 *
 ************************************************************************/

HGLOBAL WINAPI RotateDIB2(LPSTR lpDIB, int iRotateAngle)
{
	
	// Դͼ��Ŀ�Ⱥ͸߶�
	LONG	lWidth;
	LONG	lHeight;
	
	// ��ת��ͼ��Ŀ�Ⱥ͸߶�
	LONG	lNewWidth;
	LONG	lNewHeight;
	
	// ��ת��ͼ��Ŀ�ȣ�lNewWidth'��������4�ı�����
	LONG	lNewLineBytes;
	
	// ָ��Դͼ���ָ��
	LPSTR	lpDIBBits;
	
	// ��ת����DIB���
	HDIB	hDIB;
	
	// ָ����תͼ���Ӧ���ص�ָ��
	LPSTR	lpDst;
	
	// ָ����תͼ���ָ��
	LPSTR	lpNewDIB;
	LPSTR	lpNewDIBBits;
	
	// ָ��BITMAPINFO�ṹ��ָ�루Win3.0��
	LPBITMAPINFOHEADER lpbmi;
	
	// ָ��BITMAPCOREINFO�ṹ��ָ��
	LPBITMAPCOREHEADER lpbmc;
	
	// ѭ����������������DIB�е����꣩
	LONG	i;
	LONG	j;
	
	// ������ԴDIB�е�����
	FLOAT	i0;
	FLOAT	j0;
	
	// ��ת�Ƕȣ����ȣ�
	float	fRotateAngle;
	
	// ��ת�Ƕȵ����Һ�����
	float	fSina, fCosa;
	
	// Դͼ�ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	float	fSrcX1,fSrcY1,fSrcX2,fSrcY2,fSrcX3,fSrcY3,fSrcX4,fSrcY4;
	
	// ��ת���ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	float	fDstX1,fDstY1,fDstX2,fDstY2,fDstX3,fDstY3,fDstX4,fDstY4;
	
	// �����м䳣��
	float	f1,f2;
	
	// �ҵ�ԴDIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ��ȡͼ��Ŀ��
	lWidth = ::DIBWidth(lpDIB);
	
	// ��ȡͼ��ĸ߶�
	lHeight = ::DIBHeight(lpDIB);
	
	// ����ת�ǶȴӶ�ת��������
	fRotateAngle = (float) RADIAN(iRotateAngle);
	
	// ������ת�Ƕȵ�����
	fSina = (float) sin((double)fRotateAngle);
	
	// ������ת�Ƕȵ�����
	fCosa = (float) cos((double)fRotateAngle);
	
	// ����ԭͼ���ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	fSrcX1 = (float) (- (lWidth  - 1) / 2);
	fSrcY1 = (float) (  (lHeight - 1) / 2);
	fSrcX2 = (float) (  (lWidth  - 1) / 2);
	fSrcY2 = (float) (  (lHeight - 1) / 2);
	fSrcX3 = (float) (- (lWidth  - 1) / 2);
	fSrcY3 = (float) (- (lHeight - 1) / 2);
	fSrcX4 = (float) (  (lWidth  - 1) / 2);
	fSrcY4 = (float) (- (lHeight - 1) / 2);
	
	// ������ͼ�ĸ��ǵ����꣨��ͼ������Ϊ����ϵԭ�㣩
	fDstX1 =  fCosa * fSrcX1 + fSina * fSrcY1;
	fDstY1 = -fSina * fSrcX1 + fCosa * fSrcY1;
	fDstX2 =  fCosa * fSrcX2 + fSina * fSrcY2;
	fDstY2 = -fSina * fSrcX2 + fCosa * fSrcY2;
	fDstX3 =  fCosa * fSrcX3 + fSina * fSrcY3;
	fDstY3 = -fSina * fSrcX3 + fCosa * fSrcY3;
	fDstX4 =  fCosa * fSrcX4 + fSina * fSrcY4;
	fDstY4 = -fSina * fSrcX4 + fCosa * fSrcY4;
	
	// ������ת���ͼ��ʵ�ʿ��
	lNewWidth  = (LONG) ( max( fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2) ) + 0.5);
	lNewLineBytes = WIDTHBYTES(lNewWidth * 8);
	
	// ������ת���ͼ��߶�
	lNewHeight = (LONG) ( max( fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2) )  + 0.5);
	
	// �������������������Ժ�ÿ�ζ�������
	f1 = (float) (-0.5 * (lNewWidth - 1) * fCosa - 0.5 * (lNewHeight - 1) * fSina
		+ 0.5 * (lWidth  - 1));
	f2 = (float) ( 0.5 * (lNewWidth - 1) * fSina - 0.5 * (lNewHeight - 1) * fCosa
		+ 0.5 * (lHeight - 1));
	
	// �����ڴ棬�Ա�����DIB
	hDIB = (HDIB) ::GlobalAlloc(GHND, lNewLineBytes * lNewHeight + *(LPDWORD)lpDIB + ::PaletteSize(lpDIB));
	
	// �ж��Ƿ��ڴ����ʧ��
	if (hDIB == NULL)
	{
		// �����ڴ�ʧ��
		return NULL;
	}

	// �����ڴ�
	lpNewDIB =  (char * )::GlobalLock((HGLOBAL) hDIB);
	
	// ����DIB��Ϣͷ�͵�ɫ��
	memcpy(lpNewDIB, lpDIB, *(LPDWORD)lpDIB + ::PaletteSize(lpDIB));
	
	// �ҵ���DIB������ʼλ��
	lpNewDIBBits = ::FindDIBBits(lpNewDIB);
	
	// ��ȡָ��
	lpbmi = (LPBITMAPINFOHEADER)lpNewDIB;
	lpbmc = (LPBITMAPCOREHEADER)lpNewDIB;

	// ����DIB��ͼ��ĸ߶ȺͿ��
	if (IS_WIN30_DIB(lpNewDIB))
	{
		// ����Windows 3.0 DIB
		lpbmi->biWidth = lNewWidth;
		lpbmi->biHeight = lNewHeight;
	}
	else
	{
		// ����������ʽ��DIB
		lpbmc->bcWidth = (unsigned short) lNewWidth;
		lpbmc->bcHeight = (unsigned short) lNewHeight;
	}
	
	// ���ͼ��ÿ�н��в���
	for(i = 0; i < lNewHeight; i++)
	{
		// ���ͼ��ÿ�н��в���
		for(j = 0; j < lNewWidth; j++)
		{
			// ָ����DIB��i�У���j�����ص�ָ��
			// ע��˴���Ⱥ͸߶�����DIB�Ŀ�Ⱥ͸߶�
			lpDst = (char *)lpNewDIBBits + lNewLineBytes * (lNewHeight - 1 - i) + j;
			
			// �����������ԴDIB�е�����
			i0 = -((float) j) * fSina + ((float) i) * fCosa + f2;
			j0 =  ((float) j) * fCosa + ((float) i) * fSina + f1;
			
			// ����˫���Բ�ֵ�㷨����������ֵ
			*lpDst = Interpolation (lpDIBBits, lWidth, lHeight, j0, i0);
			
		}
		
	}
	
	// ����
	return hDIB;
}


/*************************************************************************
 *
 * �������ƣ�
 *   Interpolation()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   FLOAT x			- ��ֵԪ�ص�x����
 *   FLOAT y		    - ��ֵԪ�ص�y����
 *
 * ����ֵ:
 *   unsigned char      - ���ز�ֵ��������
 *
 * ˵��:
 *   �ú�������˫���Բ�ֵ�㷨����������ֵ�����ڳ���ͼ��Χ�����أ�
 * ֱ�ӷ���255��
 *
 ************************************************************************/

unsigned char WINAPI Interpolation (LPSTR lpDIBBits, LONG lWidth, LONG lHeight, FLOAT x, FLOAT y)
{
	
	// �ĸ����ٽ����ص�����(i1, j1), (i2, j1), (i1, j2), (i2, j2)
	LONG	i1, i2;
	LONG	j1, j2;
	
	// �ĸ����ٽ�����ֵ
	unsigned char	f1, f2, f3, f4;
	
	// ������ֵ�м�ֵ
	unsigned char	f12, f34;
	
	// ����һ��ֵ���������������С�ڸ�ֵʱ��Ϊ������ͬ
	FLOAT			EXP;
	
	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ��ֵ
	EXP = (FLOAT) 0.0001;
	
	// �����ĸ����ٽ����ص�����
	i1 = (LONG) x;
	i2 = i1 + 1;
	j1 = (LONG) y;
	j2 = j1 + 1;
	
	// ���ݲ�ͬ����ֱ���
	if( (x < 0) || (x > lWidth - 1) || (y < 0) || (y > lHeight - 1))
	{
		// Ҫ����ĵ㲻��Դͼ��Χ�ڣ�ֱ�ӷ���255��
		return 255;
	}
	else
	{
		if (fabs(x - lWidth + 1) <= EXP)
		{
			// Ҫ����ĵ���ͼ���ұ�Ե��
			if (fabs(y - lHeight + 1) <= EXP)
			{
				// Ҫ����ĵ�������ͼ�������½���һ�����أ�ֱ�ӷ��ظõ�����ֵ
				f1 = *((unsigned char *)lpDIBBits + lLineBytes * (lHeight - 1 - j1) + i1);
				return f1;
			}
			else
			{
				// ��ͼ���ұ�Ե���Ҳ������һ�㣬ֱ��һ�β�ֵ����
				f1 = *((unsigned char *)lpDIBBits + lLineBytes * (lHeight - 1 - j1) + i1);
				f3 = *((unsigned char *)lpDIBBits + lLineBytes * (lHeight - 1 - j1) + i2);
				
				// ���ز�ֵ���
				return ((unsigned char) (f1 + (y -j1) * (f3 - f1)));
			}
		}
		else if (fabs(y - lHeight + 1) <= EXP)
		{
			// Ҫ����ĵ���ͼ���±�Ե���Ҳ������һ�㣬ֱ��һ�β�ֵ����
			f1 = *((unsigned char *)lpDIBBits + lLineBytes * (lHeight - 1 - j1) + i1);
			f2 = *((unsigned char *)lpDIBBits + lLineBytes * (lHeight - 1 - j2) + i1);
			
			// ���ز�ֵ���
			return ((unsigned char) (f1 + (x -i1) * (f2 - f1)));
		}
		else
		{
			// �����ĸ����ٽ�����ֵ
			f1 = *((unsigned char *)lpDIBBits + lLineBytes * (lHeight - 1 - j1) + i1);
			f2 = *((unsigned char *)lpDIBBits + lLineBytes * (lHeight - 1 - j2) + i1);
			f3 = *((unsigned char *)lpDIBBits + lLineBytes * (lHeight - 1 - j1) + i2);
			f4 = *((unsigned char *)lpDIBBits + lLineBytes * (lHeight - 1 - j2) + i2);
			
			// ��ֵ1
			f12 = (unsigned char) (f1 + (x - i1) * (f2 - f1));
			
			// ��ֵ2
			f34 = (unsigned char) (f3 + (x - i1) * (f4 - f3));
			
			// ��ֵ3
			return ((unsigned char) (f12 + (y -j1) * (f34 - f12)));
		}
	}
}