// ************************************************************************
//  �ļ�����morph.cpp
//
//  ͼ����̬ѧ�任API�����⣺
//
//  ErosionDIB()    - ͼ��ʴ
//  DilationDIB()	- ͼ������
//  OpenDIB()		- ͼ������
//  CloseDIB()		- ͼ�������
//  ThiningDIB()	- ͼ��ϸ��
//
// ************************************************************************


#include "stdafx.h"
#include "morph.h"
#include "DIBAPI.h"

#include <math.h>
#include <direct.h>

/*************************************************************************
 *
 * �������ƣ�
 *   ErosiontionDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int   nMode		- ��ʴ��ʽ��0��ʾˮƽ����1��ʾ��ֱ����2��ʾ�Զ���ṹԪ�ء�
 *	 int   structure[3][3]
						- �Զ����3��3�ṹԪ�ء�
 *
 * ����ֵ:
 *   BOOL               - ��ʴ�ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ����и�ʴ���㡣�ṹԪ��Ϊˮƽ�����ֱ����������㣬�м��λ��ԭ�㣻
 * �������û��Լ�����3��3�ĽṹԪ�ء�
 * 
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL WINAPI ErosionDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode , int structure[3][3])
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
	int  n;
	int  m;

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


	if(nMode == 0)
	{
		//ʹ��ˮƽ����ĽṹԪ�ؽ��и�ʴ
		for(j = 0; j <lHeight; j++)
		{
			for(i = 1;i <lWidth-1; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char *)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if(pixel != 255 && *lpSrc != 0)
					return FALSE;
				
				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���Դͼ���е�ǰ���������������һ���㲻�Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				for (n = 0;n < 3;n++ )
				{
					pixel = *(lpSrc+n-1);
					if (pixel == 255 )
					{
						*lpDst = (unsigned char)255;
						break;
					}
				}
				
			}
		}

	}
	else if(nMode == 1)
	{
		//ʹ�ô�ֱ����ĽṹԪ�ؽ��и�ʴ
		for(j = 1; j <lHeight-1; j++)
		{
			for(i = 0;i <lWidth; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ��������ϱߺ����±ߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char *)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if(pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���Դͼ���е�ǰ���������������һ���㲻�Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				for (n = 0;n < 3;n++ )
				{
					pixel = *(lpSrc+(n-1)*lWidth);
					if (pixel == 255 )
					{
						*lpDst = (unsigned char)255;
						break;
					}
				}
				
			}
		}

	}
	else
	{
		//ʹ���Զ���ĽṹԪ�ؽ��и�ʴ
		for(j = 1; j <lHeight-1; j++)
		{
			for(i = 0;i <lWidth; i++)
			{
				//����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������
				//�����ϱߺ����±ߵ���������
				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char *)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if(pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ������һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				//ע����DIBͼ�������������µ��õ�
				for (m = 0;m < 3;m++ )
				{
					for (n = 0;n < 3;n++)
					{
						if( structure[m][n] == -1)
							continue;
						pixel = *(lpSrc + ((2-m)-1)*lWidth + (n-1));
						if (pixel == 255 )
						{	
							*lpDst = (unsigned char)255;
							break;
						}
					}
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
 *   DilationDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int   nMode		- ���ͷ�ʽ��0��ʾˮƽ����1��ʾ��ֱ����2��ʾ�Զ���ṹԪ�ء�
 *	 int   structure[3][3]
						- �Զ����3��3�ṹԪ�ء�
 *
 * ����ֵ:
 *   BOOL               - ���ͳɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ������������㡣�ṹԪ��Ϊˮƽ�����ֱ����������㣬�м��λ��ԭ�㣻
 * �������û��Լ�����3��3�ĽṹԪ�ء�
 * 
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/


BOOL WINAPI DilationDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode , int structure[3][3])
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
	int  n;
	int  m;

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


	if(nMode == 0)
	{
		//ʹ��ˮƽ����ĽṹԪ�ؽ�������
		for(j = 0; j <lHeight; j++)
		{
			for(i = 1;i <lWidth-1; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char *)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if(pixel != 255 && pixel != 0)
					return FALSE;
				
				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//Դͼ���е�ǰ�������������ֻҪ��һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
				for (n = 0;n < 3;n++ )
				{
					pixel = *(lpSrc+n-1);
					if (pixel == 0 )
					{
						*lpDst = (unsigned char)0;
						break;
					}
				}
				
			}
		}

	}
	else if(nMode == 1)
	{
		//ʹ�ô�ֱ����ĽṹԪ�ؽ�������
		for(j = 1; j <lHeight-1; j++)
		{
			for(i = 0;i <lWidth; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ��������ϱߺ����±ߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char *)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if(pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//Դͼ���е�ǰ�������������ֻҪ��һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
				for (n = 0;n < 3;n++ )
				{
					pixel = *(lpSrc+(n-1)*lWidth);
					if (pixel == 0 )
					{
						*lpDst = (unsigned char)0;
						break;
					}
				}
				
			}
		}

	}
	else
	{
		//ʹ���Զ���ĽṹԪ�ؽ�������
		for(j = 1; j <lHeight-1; j++)
		{
			for(i = 0;i <lWidth; i++)
			{
				//����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������
				//�����ϱߺ����±ߵ���������
				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char *)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if(pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ����ֻҪ��һ���Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
				//ע����DIBͼ�������������µ��õ�
				for (m = 0;m < 3;m++ )
				{
					for (n = 0;n < 3;n++)
					{
						if( structure[m][n] == -1)
							continue;
						pixel = *(lpSrc + ((2-m)-1)*lWidth + (n-1));
						if (pixel == 0 )
						{	
							*lpDst = (unsigned char)0;
							break;
						}
					}
				}
				
			}
		}

	}
	// �������ͺ��ͼ��
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
 *   OpenDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int   nMode		- �����㷽ʽ��0��ʾˮƽ����1��ʾ��ֱ����2��ʾ�Զ���ṹԪ�ء�
 *	 int   structure[3][3]
						- �Զ����3��3�ṹԪ�ء�
 *
 * ����ֵ:
 *   BOOL               - ������ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ����п����㡣�ṹԪ��Ϊˮƽ�����ֱ����������㣬�м��λ��ԭ�㣻
 * �������û��Լ�����3��3�ĽṹԪ�ء�
 * 
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL WINAPI OpenDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode , int structure[3][3])
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
	int  n;
	int  m;

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


	if(nMode == 0)
	{
		//ʹ��ˮƽ����ĽṹԪ�ؽ��и�ʴ
		for(j = 0; j <lHeight; j++)
		{
			for(i = 1;i <lWidth-1; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char *)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if(pixel != 255 && *lpSrc != 0)
					return FALSE;
				
				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���Դͼ���е�ǰ���������������һ���㲻�Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				for (n = 0;n < 3;n++ )
				{
					pixel = *(lpSrc+n-1);
					if (pixel == 255 )
					{
						*lpDst = (unsigned char)255;
						break;
					}
				}
				
			}
		}

	}
	else if(nMode == 1)
	{
		//ʹ�ô�ֱ����ĽṹԪ�ؽ��и�ʴ
		for(j = 1; j <lHeight-1; j++)
		{
			for(i = 0;i <lWidth; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ��������ϱߺ����±ߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char *)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if(pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���Դͼ���е�ǰ���������������һ���㲻�Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				for (n = 0;n < 3;n++ )
				{
					pixel = *(lpSrc+(n-1)*lWidth);
					if (pixel == 255 )
					{
						*lpDst = (unsigned char)255;
						break;
					}
				}
				
			}
		}

	}
	else
	{
		//ʹ���Զ���ĽṹԪ�ؽ��и�ʴ
		for(j = 1; j <lHeight-1; j++)
		{
			for(i = 0;i <lWidth; i++)
			{
				//����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������
				//�����ϱߺ����±ߵ���������
				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char *)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if(pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɺ�ɫ
				*lpDst = (unsigned char)0;

				//���ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ������һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɰ�ɫ
				//ע����DIBͼ�������������µ��õ�
				for (m = 0;m < 3;m++ )
				{
					for (n = 0;n < 3;n++)
					{
						if( structure[m][n] == -1)
							continue;
						pixel = *(lpSrc + ((2-m)-1)*lWidth + (n-1));
						if (pixel == 255 )
						{	
							*lpDst = (unsigned char)255;
							break;
						}
					}
				}
				
			}
		}

	}
	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// ���³�ʼ���·�����ڴ棬�趨��ʼֵΪ255
	//lpDst = (char *)lpNewDIBBits;
	//memset(lpDst, (BYTE)255, lWidth * lHeight);


	if(nMode == 0)
	{
		//ʹ��ˮƽ����ĽṹԪ�ؽ�������
		for(j = 0; j <lHeight; j++)
		{
			for(i = 1;i <lWidth-1; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char *)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if(pixel != 255 && *lpSrc != 0)
					return FALSE;
				
				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//Դͼ���е�ǰ�������������ֻҪ��һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
				for (n = 0;n < 3;n++ )
				{
					pixel = *(lpSrc+n-1);
					if (pixel == 0 )
					{
						*lpDst = (unsigned char)0;
						break;
					}
				}
				
			}
		}

	}
	else if(nMode == 1)
	{
		//ʹ�ô�ֱ����ĽṹԪ�ؽ�������
		for(j = 1; j <lHeight-1; j++)
		{
			for(i = 0;i <lWidth; i++)
			{
				//����ʹ��1��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ��������ϱߺ����±ߵ���������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char *)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if(pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//Դͼ���е�ǰ�������������ֻҪ��һ�����Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
				for (n = 0;n < 3;n++ )
				{
					pixel = *(lpSrc+(n-1)*lWidth);
					if (pixel == 0 )
					{
						*lpDst = (unsigned char)0;
						break;
					}
				}
				
			}
		}

	}
	else
	{
		//ʹ���Զ���ĽṹԪ�ؽ�������
		for(j = 1; j <lHeight-1; j++)
		{
			for(i = 0;i <lWidth; i++)
			{
				//����ʹ��3��3�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ���������ߺ����ұߵ���������
				//�����ϱߺ����±ߵ���������
				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char *)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if(pixel != 255 && *lpSrc != 0)
					return FALSE;

				//Ŀ��ͼ���еĵ�ǰ���ȸ��ɰ�ɫ
				*lpDst = (unsigned char)255;

				//ԭͼ���ж�Ӧ�ṹԪ����Ϊ��ɫ����Щ����ֻҪ��һ���Ǻ�ɫ��
				//��Ŀ��ͼ���еĵ�ǰ�㸳�ɺ�ɫ
				//ע����DIBͼ�������������µ��õ�
				for (m = 0;m < 3;m++ )
				{
					for (n = 0;n < 3;n++)
					{
						if( structure[m][n] == -1)
							continue;
						pixel = *(lpSrc + ((2-m)-1)*lWidth + (n-1));
						if (pixel == 0 )
						{	
							*lpDst = (unsigned char)0;
							break;
						}
					}
				}
				
			}
		}

	}
	// �������ͺ��ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);


	return TRUE;
}


/*************************************************************************
 *
 * �������ƣ�
 *   CloseDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *   int   nMode		- �����㷽ʽ��0��ʾˮƽ����1��ʾ��ֱ����2��ʾ�Զ���ṹԪ�ء�
 *	 int   structure[3][3]
						- �Զ����3��3�ṹԪ�ء�
 *
 * ����ֵ:
 *   BOOL               - ������ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ����п����㡣�ṹԪ��Ϊˮƽ�����ֱ����������㣬�м��λ��ԭ�㣻
 * �������û��Լ�����3��3�ĽṹԪ�ء�
 * 
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

/*************************************************************************
 *
 * �������ƣ�
 *   ThinDIB()
 *
 * ����:
 *   LPSTR lpDIBBits    - ָ��ԴDIBͼ��ָ��
 *   LONG  lWidth       - Դͼ���ȣ���������������4�ı�����
 *   LONG  lHeight      - Դͼ��߶ȣ���������
 *
 * ����ֵ:
 *   BOOL               - ������ɹ�����TRUE�����򷵻�FALSE��
 *
 * ˵��:
 * �ú������ڶ�ͼ�����ϸ�����㡣
 * 
 * Ҫ��Ŀ��ͼ��Ϊֻ��0��255�����Ҷ�ֵ�ĻҶ�ͼ��
 ************************************************************************/

BOOL WINAPI CloseDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, int nMode , int structure[3][3])
{
		if (DilationDIB(lpDIBBits, lWidth, lHeight, nMode , structure))
		{

			if (ErosionDIB(lpDIBBits, lWidth, lHeight, nMode , structure))
			{
				// ����
				return TRUE;

			}
		}
		return FALSE;
	
	// ����
	return TRUE;
}

BOOL WINAPI ThiningDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ��Դͼ���ָ��
	LPSTR	lpSrc;
	
	// ָ�򻺴�ͼ���ָ��
	LPSTR	lpDst;
	
	// ָ�򻺴�DIBͼ���ָ��
	LPSTR	lpNewDIBBits;
	HLOCAL	hNewDIBBits;

	//����
	BOOL bModified;

	//ѭ������
	long i;
	long j;
	int  n;
	int  m;

	//�ĸ�����
	BOOL bCondition1;
	BOOL bCondition2;
	BOOL bCondition3;
	BOOL bCondition4;

	//������
	unsigned char nCount;
	
	//����ֵ
	unsigned char pixel;

	//5��5������������ֵ
	unsigned char neighbour[5][5];

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

	bModified=TRUE;

	while(bModified)
	{

		bModified = FALSE;
		// ��ʼ���·�����ڴ棬�趨��ʼֵΪ255
		lpDst = (char *)lpNewDIBBits;
		memset(lpDst, (BYTE)255, lWidth * lHeight);

		for(j = 2; j <lHeight-2; j++)
		{
			for(i = 2;i <lWidth-2; i++)
			{

				bCondition1 = FALSE;
				bCondition2 = FALSE;
				bCondition3 = FALSE;
				bCondition4 = FALSE;

				//����ʹ��5��5�ĽṹԪ�أ�Ϊ��ֹԽ�磬���Բ�������Χ�ļ��кͼ�������

				// ָ��Դͼ������j�У���i�����ص�ָ��			
				lpSrc = (char *)lpDIBBits + lWidth * j + i;

				// ָ��Ŀ��ͼ������j�У���i�����ص�ָ��			
				lpDst = (char *)lpNewDIBBits + lWidth * j + i;

				//ȡ�õ�ǰָ�봦������ֵ��ע��Ҫת��Ϊunsigned char��
				pixel = (unsigned char)*lpSrc;

				//Ŀ��ͼ���к���0��255��������Ҷ�ֵ
				if(pixel != 255 && *lpSrc != 0)
					//return FALSE;
					continue;
				//���Դͼ���е�ǰ��Ϊ��ɫ��������
				else if(pixel == 255)
					continue;

				//��õ�ǰ�����ڵ�5��5����������ֵ����ɫ��0������ɫ��1����
				for (m = 0;m < 5;m++ )
				{
					for (n = 0;n < 5;n++)
					{
						neighbour[m][n] =(255 - (unsigned char)*(lpSrc + ((4 - m) - 2)*lWidth + n - 2 )) / 255;
					}
				}
//				neighbour[][]
				//����ж�������
				//�ж�2<=NZ(P1)<=6
				nCount =  neighbour[1][1] + neighbour[1][2] + neighbour[1][3] \
						+ neighbour[2][1] + neighbour[2][3] + \
						+ neighbour[3][1] + neighbour[3][2] + neighbour[3][3];
				if ( nCount >= 2 && nCount <=6)
					bCondition1 = TRUE;

				//�ж�Z0(P1)=1
				nCount = 0;
				if (neighbour[1][2] == 0 && neighbour[1][1] == 1)
					nCount++;
				if (neighbour[1][1] == 0 && neighbour[2][1] == 1)
					nCount++;
				if (neighbour[2][1] == 0 && neighbour[3][1] == 1)
					nCount++;
				if (neighbour[3][1] == 0 && neighbour[3][2] == 1)
					nCount++;
				if (neighbour[3][2] == 0 && neighbour[3][3] == 1)
					nCount++;
				if (neighbour[3][3] == 0 && neighbour[2][3] == 1)
					nCount++;
				if (neighbour[2][3] == 0 && neighbour[1][3] == 1)
					nCount++;
				if (neighbour[1][3] == 0 && neighbour[1][2] == 1)
					nCount++;
				if (nCount == 1)
					bCondition2 = TRUE;

				//�ж�P2*P4*P8=0 or Z0(p2)!=1
				if (neighbour[1][2]*neighbour[2][1]*neighbour[2][3] == 0)
					bCondition3 = TRUE;
				else
				{
					nCount = 0;
					if (neighbour[0][2] == 0 && neighbour[0][1] == 1)
						nCount++;
					if (neighbour[0][1] == 0 && neighbour[1][1] == 1)
						nCount++;
					if (neighbour[1][1] == 0 && neighbour[2][1] == 1)
						nCount++;
					if (neighbour[2][1] == 0 && neighbour[2][2] == 1)
						nCount++;
					if (neighbour[2][2] == 0 && neighbour[2][3] == 1)
						nCount++;
					if (neighbour[2][3] == 0 && neighbour[1][3] == 1)
						nCount++;
					if (neighbour[1][3] == 0 && neighbour[0][3] == 1)
						nCount++;
					if (neighbour[0][3] == 0 && neighbour[0][2] == 1)
						nCount++;
					if (nCount != 1)
						bCondition3 = TRUE;
				}

				//�ж�P2*P4*P6=0 or Z0(p4)!=1
				if (neighbour[1][2]*neighbour[2][1]*neighbour[3][2] == 0)
					bCondition4 = TRUE;
				else
				{
					nCount = 0;
					if (neighbour[1][1] == 0 && neighbour[1][0] == 1)
						nCount++;
					if (neighbour[1][0] == 0 && neighbour[2][0] == 1)
						nCount++;
					if (neighbour[2][0] == 0 && neighbour[3][0] == 1)
						nCount++;
					if (neighbour[3][0] == 0 && neighbour[3][1] == 1)
						nCount++;
					if (neighbour[3][1] == 0 && neighbour[3][2] == 1)
						nCount++;
					if (neighbour[3][2] == 0 && neighbour[2][2] == 1)
						nCount++;
					if (neighbour[2][2] == 0 && neighbour[1][2] == 1)
						nCount++;
					if (neighbour[1][2] == 0 && neighbour[1][1] == 1)
						nCount++;
					if (nCount != 1)
						bCondition4 = TRUE;
				}
				if(bCondition1 && bCondition2 && bCondition3 && bCondition4)
				{
					*lpDst = (unsigned char)255;
					bModified = TRUE;
				}
				else
				{
					*lpDst = (unsigned char)0;
				}
			}
		}
			// ���Ƹ�ʴ���ͼ��
			memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);


	}
	// ���Ƹ�ʴ���ͼ��
	memcpy(lpDIBBits, lpNewDIBBits, lWidth * lHeight);

	// �ͷ��ڴ�
	LocalUnlock(hNewDIBBits);
	LocalFree(hNewDIBBits);

	// ����
	return TRUE;
}

