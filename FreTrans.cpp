/**************************************************************************
 *  �ļ�����FreTrans.cpp
 *
 *  �����任API�����⣺
 *
 *  FFT()				- ���ٸ���Ҷ�任
 *  IFFT()				- ���ٸ���Ҷ���任
 *  DCT()				- ��ɢ���ұ任
 *  WALSH()				- �ֶ�ʲ��������任
 *
 *  Fourier()			- ͼ��ĸ���Ҷ�任
 *  DIBDct()			- ͼ�����ɢ���ұ任
 *  DIBWalsh()			- ͼ����ֶ�ʲ��������任
 *
 *************************************************************************/

#include "FreTrans.h"
#include "stdafx.h"
#include "DIBAPI.h"

#include <math.h>
#include <direct.h>
#include <complex>
using namespace std;

// ������
#define PI 3.1415926535

/*************************************************************************
 *
 * �������ƣ�
 *   FFT()
 *
 * ����:
 *   complex<double> * TD	- ָ��ʱ�������ָ��
 *   complex<double> * FD	- ָ��Ƶ�������ָ��
 *   r						��2������������������
 *
 * ����ֵ:
 *   �ޡ�
 *
 * ˵��:
 *   �ú�������ʵ�ֿ��ٸ���Ҷ�任��
 *
 ************************************************************************/
VOID WINAPI FFT(complex<double> * TD, complex<double> * FD, int r)
{
	// ����Ҷ�任����
	LONG	count;
	
	// ѭ������
	int		i,j,k;
	
	// �м����
	int		bfsize,p;
	
	// �Ƕ�
	double	angle;
	
	complex<double> *W,*X1,*X2,*X;
	
	// ���㸶��Ҷ�任����
	count = 1 << r;
	
	// ������������洢��
	W  = new complex<double>[count / 2];
	X1 = new complex<double>[count];
	X2 = new complex<double>[count];
	
	// �����Ȩϵ��
	for(i = 0; i < count / 2; i++)
	{
		angle = -i * PI * 2 / count;
		W[i] = complex<double> (cos(angle), sin(angle));
	}
	
	// ��ʱ���д��X1
	memcpy(X1, TD, sizeof(complex<double>) * count);
	
	// ���õ����㷨���п��ٸ���Ҷ�任
	for(k = 0; k < r; k++)
	{
		for(j = 0; j < 1 << k; j++)
		{
			bfsize = 1 << (r-k);
			for(i = 0; i < bfsize / 2; i++)
			{
				p = j * bfsize;
				X2[i + p] = X1[i + p] + X1[i + p + bfsize / 2];
				X2[i + p + bfsize / 2] = (X1[i + p] - X1[i + p + bfsize / 2]) * W[i * (1<<k)];
			}
		}
		X  = X1;
		X1 = X2;
		X2 = X;
	}
	
	// ��������
	for(j = 0; j < count; j++)
	{
		p = 0;
		for(i = 0; i < r; i++)
		{
			if (j&(1<<i))
			{
				p+=1<<(r-i-1);
			}
		}
		FD[j]=X1[p];
	}
	
	// �ͷ��ڴ�
	delete W;
	delete X1;
	delete X2;
}

/*************************************************************************
 *
 * �������ƣ�
 *   IFFT()
 *
 * ����:
 *   complex<double> * FD	- ָ��Ƶ��ֵ��ָ��
 *   complex<double> * TD	- ָ��ʱ��ֵ��ָ��
 *   r						��2������
 *
 * ����ֵ:
 *   �ޡ�
 *
 * ˵��:
 *   �ú�������ʵ�ֿ��ٸ���Ҷ���任��
 *
 ************************************************************************/
VOID WINAPI IFFT(complex<double> * FD, complex<double> * TD, int r)
{
	// ����Ҷ�任����
	LONG	count;
	
	// ѭ������
	int		i;
	
	complex<double> *X;
	
	// ���㸶��Ҷ�任����
	count = 1 << r;
	
	// ������������洢��
	X = new complex<double>[count];
	
	// ��Ƶ���д��X
	memcpy(X, FD, sizeof(complex<double>) * count);
	
	// ����
	for(i = 0; i < count; i++)
	{
		X[i] = complex<double> (X[i].real(), -X[i].imag());
	}
	
	// ���ÿ��ٸ���Ҷ�任
	FFT(X, TD, r);
	
	// ��ʱ���Ĺ���
	for(i = 0; i < count; i++)
	{
		TD[i] = complex<double> (TD[i].real() / count, -TD[i].imag() / count);
	}
	
	// �ͷ��ڴ�
	delete X;
}

/*************************************************************************
 *
 * �������ƣ�
 *   Fourier()
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
 *   �ú���������ͼ����и���Ҷ�任��
 *
 ************************************************************************/
BOOL WINAPI Fourier(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// �м����
	double	dTemp;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG	w;
	LONG	h;
	
	int		wp;
	int		hp;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ����ֵ
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	while(w * 2 <= lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while(h * 2 <= lHeight)
	{
		h *= 2;
		hp++;
	}
	
	// �����ڴ�
	complex<double> *TD = new complex<double>[w * h];
	complex<double> *FD = new complex<double>[w * h];
	
	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < w; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// ��ʱ��ֵ
			TD[j + w * i] = complex<double>(*(lpSrc), 0);
		}
	}
	
	for(i = 0; i < h; i++)
	{
		// ��y������п��ٸ���Ҷ�任
		FFT(&TD[w * i], &FD[w * i], wp);
	}
	
	// ����任���
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			TD[i + h * j] = FD[j + w * i];
		}
	}
	
	for(i = 0; i < w; i++)
	{
		// ��x������п��ٸ���Ҷ�任
		FFT(&TD[i * h], &FD[i * h], hp);
	}
	
	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < w; j++)
		{
			// ����Ƶ��
			dTemp = sqrt(FD[j * h + i].real() * FD[j * h + i].real() + 
				         FD[j * h + i].imag() * FD[j * h + i].imag()) / 100;
			
			// �ж��Ƿ񳬹�255


			if (dTemp > 255)
			{
				// ���ڳ����ģ�ֱ������Ϊ255
				dTemp = 255;
			}

			// ָ��DIB��(i<h/2 ? i+h/2 : i-h/2)�У���(j<w/2 ? j+w/2 : j-w/2)�����ص�ָ��
			// �˴���ֱ��ȡi��j����Ϊ�˽��任���ԭ���Ƶ�����
			//lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * 
				(lHeight - 1 - (i<h/2 ? i+h/2 : i-h/2)) + (j<w/2 ? j+w/2 : j-w/2);
			
			// ����Դͼ��
			* (lpSrc) = (BYTE)(dTemp);
		}
	}
	
	// ɾ����ʱ����
	delete TD;
	delete FD;
	
	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   DCT()
 *
 * ����:
 *   double * f				- ָ��ʱ��ֵ��ָ��
 *   double * F				- ָ��Ƶ��ֵ��ָ��
 *   r						��2������
 *
 * ����ֵ:
 *   �ޡ�
 *
 * ˵��:
 *   �ú�������ʵ�ֿ�����ɢ���ұ任���ú�������2N��Ŀ��ٸ���Ҷ�任
 * ��ʵ����ɢ���ұ任��
 *
 ************************************************************************/
VOID WINAPI DCT(double *f, double *F, int r)
{
	// ��ɢ���ұ任����
	LONG	count;
	
	// ѭ������
	int		i;
	
	// �м����
	double	dTemp;
	
	complex<double> *X;
	
	// ������ɢ���ұ任����
	count = 1<<r;
	
	// �����ڴ�
	X = new complex<double>[count*2];
	
	// ����ֵΪ0
	memset(X, 0, sizeof(complex<double>) * count * 2);
	
	// ��ʱ���д������X
	for(i=0;i<count;i++)
	{
		X[i] = complex<double> (f[i], 0);
	}
	
	// ���ÿ��ٸ���Ҷ�任
	FFT(X,X,r+1);
	
	// ����ϵ��
	dTemp = 1/sqrt(count);
	
	// ��F[0]
	F[0] = X[0].real() * dTemp;
	
	dTemp *= sqrt(2);
	
	// ��F[u]	
	for(i = 1; i < count; i++)
	{
		F[i]=(X[i].real() * cos(i*PI/(count*2)) + X[i].imag() * sin(i*PI/(count*2))) * dTemp;
	}
	
	// �ͷ��ڴ�
	delete X;
}

/*************************************************************************
 *
 * �������ƣ�
 *   IDCT()
 *
 * ����:
 *   double * F				- ָ��Ƶ��ֵ��ָ��
 *   double * f				- ָ��ʱ��ֵ��ָ��
 *   r						��2������
 *
 * ����ֵ:
 *   �ޡ�
 *
 * ˵��:
 *   �ú�������ʵ�ֿ�����ɢ���ҷ��任���ú���Ҳ����2N��Ŀ��ٸ���Ҷ�任
 * ��ʵ����ɢ���ҷ��任��
 *
 ************************************************************************/
VOID WINAPI IDCT(double *F, double *f, int r)
{
	// ��ɢ���ҷ��任����
	LONG	count;
	
	// ѭ������
	int		i;
	
	// �м����
	double	dTemp, d0;
	
	complex<double> *X;
	
	// ������ɢ���ұ任����
	count = 1<<r;
	
	// �����ڴ�
	X = new complex<double>[count*2];
	
	// ����ֵΪ0
	memset(X, 0, sizeof(complex<double>) * count * 2);
	
	// ��Ƶ��任���д������X
	for(i=0;i<count;i++)
	{
		X[i] = complex<double> (F[i] * cos(i*PI/(count*2)), F[i] * sin(i*PI/(count*2)));
	}
	
	// ���ÿ��ٸ���Ҷ���任
	IFFT(X,X,r+1);
	
	// ����ϵ��
	dTemp = sqrt(2.0/count);
	d0 = (sqrt(1.0/count) - dTemp) * F[0];
	
	// ����f(x)
	for(i = 0; i < count; i++)
	{
		f[i] = d0 + X[i].real()* dTemp * 2 * count;
	}
	
	// �ͷ��ڴ�
	delete X;
}

/*************************************************************************
 *
 * �������ƣ�
 *   DIBDct()
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
 *   �ú���������ͼ�������ɢ���ұ任��
 *
 ************************************************************************/
BOOL WINAPI DIBDct(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG	w;
	LONG	h;
	
	// �м����
	double	dTemp;
	
	int		wp;
	int		hp;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ����ֵ
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// ���������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	while(w * 2 <= lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while(h * 2 <= lHeight)
	{
		h *= 2;
		hp++;
	}
	
	// �����ڴ�
	double *f = new double[w * h];
	double *F = new double[w * h];
	
	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < w; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// ��ʱ��ֵ
			f[j + i * w] = *(lpSrc);
		}
	}
	
	for(i = 0; i < h; i++)
	{
		// ��y���������ɢ���ұ任
		DCT(&f[w * i], &F[w * i], wp);
	}
	
	// ���������
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			f[j * h + i] = F[j + w * i];
		}
	}
	
	for(j = 0; j < w; j++)
	{
		// ��x���������ɢ���ұ任
		DCT(&f[j * h], &F[j * h], hp);
	}
	
	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < w; j++)
		{
			// ����Ƶ��
			dTemp = fabs(F[j*h+i]);
			
			// �ж��Ƿ񳬹�255
			if (dTemp > 255)
			{
				// ���ڳ����ģ�ֱ������Ϊ255
				dTemp = 255;
			}
			
			// ָ��DIB��y�У���x�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// ����Դͼ��
			* (lpSrc) = (BYTE)(dTemp);
		}
	}
	
	// �ͷ��ڴ�
	delete f;
	delete F;

	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   WALSH()
 *
 * ����:
 *   double * f				- ָ��ʱ��ֵ��ָ��
 *   double * F				- ָ��Ƶ��ֵ��ָ��
 *   r						��2������
 *
 * ����ֵ:
 *   �ޡ�
 *
 * ˵��:
 *   �ú�������ʵ�ֿ����ֶ�ʲ-������任��
 *
 ************************************************************************/

VOID WINAPI WALSH(double *f, double *F, int r)
{
	// �ֶ�ʲ-������任����
	LONG	count;
	
	// ѭ������
	int		i,j,k;
	
	// �м����
	int		bfsize,p;
	
	double *X1,*X2,*X;
	
	// ��������ֶ�ʲ�任����
	count = 1 << r;
	
	// �����������������
	X1 = new double[count];
	X2 = new double[count];
	
	// ��ʱ���д������X1
	memcpy(X1, f, sizeof(double) * count);
	
	// ��������
	for(k = 0; k < r; k++)
	{
		for(j = 0; j < 1<<k; j++)
		{
			bfsize = 1 << (r-k);
			for(i = 0; i < bfsize / 2; i++)
			{
				p = j * bfsize;
				X2[i + p] = X1[i + p] + X1[i + p + bfsize / 2];
				X2[i + p + bfsize / 2] = X1[i + p] - X1[i + p + bfsize / 2];
			}
		}
		
		// ����X1��X2  
		X = X1;
		X1 = X2;
		X2 = X;
	}
	
	// ����ϵ��
	for(j = 0; j < count; j++)
	{
		p = 0;
		for(i = 0; i < r; i++)
		{
			if (j & (1<<i))
			{
				p += 1 << (r-i-1);
			}
		}

		F[j] = X1[p] / count;
	}
	
	// �ͷ��ڴ�
	delete X1;
	delete X2;
}

/*************************************************************************
 *
 * �������ƣ�
 *   IWALSH()
 *
 * ����:
 *   double * F				- ָ��Ƶ��ֵ��ָ��
 *   double * f				- ָ��ʱ��ֵ��ָ��
 *   r						��2������
 *
 * ����ֵ:
 *   �ޡ�
 *
 * ˵��:
 *   �ú�������ʵ�ֿ����ֶ�ʲ-�����귴�任��
 *
 ************************************************************************/

VOID WINAPI IWALSH(double *F, double *f, int r)
{
	// �任����
	LONG	count;
	
	// ѭ������
	int		i;
	
	// ����任����
	count = 1 << r;
	
	// ���ÿ����ֶ�ʲ��������任���з��任
	WALSH(F, f, r);
	
	// ����ϵ��
	for(i = 0; i < count; i++)
	{
		f[i] *= count;
	}
}

/*************************************************************************
 *
 * �������ƣ�
 *   DIBWalsh()
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
 *   �ú���������ͼ������ֶ�ʲ-������任���������ȶ�ͼ��ÿ�н���һά
 * �ֶ�ʲ��������任��Ȼ��Ա任�����ÿ�н���һά�ֶ�ʲ��������任��
 *
 ************************************************************************/

BOOL WINAPI DIBWalsh(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG	w;
	LONG	h;
	
	// �м����
	double	dTemp;
	
	int		wp;
	int		hp;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ����ֵ
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// ���������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	while(w * 2 <= lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while(h * 2 <= lHeight)
	{
		h *= 2;
		hp++;
	}
	
	// �����ڴ�
	double *f = new double[w * h];
	double *F = new double[w * h];
	
	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < w; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// ��ʱ��ֵ
			f[j + i * w] = *(lpSrc);
		}
	}
	
	for(i = 0; i < h; i++)
	{
		// ��y��������ֶ�ʲ-������任
		WALSH(f + w * i, F + w * i, wp);
	}
	
	// ���������
	for(i = 0; i < h; i++)
	{
		for(j = 0; j < w; j++)
		{
			f[j * h + i] = F[j + w * i];
		}
	}
	
	for(j = 0; j < w; j++)
	{
		// ��x��������ֶ�ʲ-������任
		WALSH(f + j * h, F + j * h, hp);
	}
	
	// ��
	for(i = 0; i < h; i++)
	{
		// ��
		for(j = 0; j < w; j++)
		{
			// ����Ƶ��
			dTemp = fabs(F[j * h + i] * 1000);
			
			// �ж��Ƿ񳬹�255
			if (dTemp > 255)
			{
				// ���ڳ����ģ�ֱ������Ϊ255
				dTemp = 255;
			}
			
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// ����Դͼ��
			* (lpSrc) = (BYTE)(dTemp);
		}
	}
	
	//�ͷ��ڴ�
	delete f;
	delete F;

	// ����
	return TRUE;
}

/*************************************************************************
 *
 * �������ƣ�
 *   DIBWalsh1()
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
 *   �ú���������ͼ������ֶ�ʲ-������任�������治ͬ���ǣ��˴��ǽ���ά
 * ����ת����һ����������Ȼ��Ը�����������һ��һά�ֶ�ʲ-������任��
 *
 ************************************************************************/

BOOL WINAPI DIBWalsh1(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// ָ��Դͼ���ָ��
	unsigned char*	lpSrc;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ���и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	LONG	w;
	LONG	h;
	
	// �м����
	double	dTemp;
	
	int		wp;
	int		hp;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ����ֵ
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	
	// ���������ɢ���ұ任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	while(w * 2 <= lWidth)
	{
		w *= 2;
		wp++;
	}
	
	while(h * 2 <= lHeight)
	{
		h *= 2;
		hp++;
	}
	
	// �����ڴ�
	double *f = new double[w * h];
	double *F = new double[w * h];
	
	// ��
	for(i = 0; i < w; i++)
	{
		// ��
		for(j = 0; j < h; j++)
		{
			// ָ��DIB��j�У���i�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - j) + i;
			
			// ��ʱ��ֵ
			f[j + i * w] = *(lpSrc);
		}
	}
	
	// ���ÿ����ֶ�ʲ��������任
	WALSH(f, F, wp + hp);
	
	// ��
	for(i = 0; i < w; i++)
	{
		// ��
		for(j = 0; j < h; j++)
		{
			// ����Ƶ��
			dTemp = fabs(F[i * w + j] * 1000);
			
			// �ж��Ƿ񳬹�255
			if (dTemp > 255)
			{
				// ���ڳ����ģ�ֱ������Ϊ255
				dTemp = 255;
			}
			
			// ָ��DIB��j�У���i�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - j) + i;
			
			// ����Դͼ��
			* (lpSrc) = (BYTE)(dTemp);
		}
	}
	
	//�ͷ��ڴ�
	delete f;
	delete F;

	// ����
	return TRUE;
}
