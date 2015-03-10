// geotrans.h

#ifndef _INC_GeoTransAPI
#define _INC_GeoTransAPI

// ������
#define PI 3.1415926535

//�Ƕȵ�����ת���ĺ�
#define RADIAN(angle) ((angle)*PI/180.0) 


// ����ԭ��
BOOL WINAPI TranslationDIB1 (LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lXOffset, LONG lYOffset);
BOOL WINAPI TranslationDIB (LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG lXOffset, LONG lYOffset);
BOOL WINAPI MirrorDIB(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BOOL bDirection);
BOOL WINAPI TransposeDIB(LPSTR lpbi);
HGLOBAL WINAPI ZoomDIB(LPSTR lpbi, float fXZoomRatio, float fYZoomRatio);
HGLOBAL WINAPI RotateDIB(LPSTR lpbi, int iRotateAngle);
HGLOBAL WINAPI RotateDIB2(LPSTR lpbi, int iRotateAngle);
unsigned char WINAPI Interpolation (LPSTR lpDIBBits, LONG lWidth, LONG lHeight, FLOAT x, FLOAT y);


#endif //!_INC_GeoTransAPI