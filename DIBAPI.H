// dibapi.h

#ifndef _INC_DIBAPI
#define _INC_DIBAPI

// DIB���
DECLARE_HANDLE(HDIB);

// DIB����
#define PALVERSION   0x300

/* DIB�� */

// �ж��Ƿ���Win 3.0��DIB
#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER))

// �����������Ŀ��
#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)

// �����������ĸ߶�
#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)

// �ڼ���ͼ���Сʱ�����ù�ʽ��biSizeImage = biWidth' �� biHeight��
// ��biWidth'��������biWidth�������biWidth'������4������������ʾ
// ���ڻ����biWidth�ģ���4�������������WIDTHBYTES������������
// biWidth'
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

// PCX�ļ�ͷ�ṹ
typedef struct{
		 BYTE bManufacturer;
		 BYTE bVersion;
		 BYTE bEncoding;
		 BYTE bBpp;
		 WORD wLeft;
		 WORD wTop;
		 WORD wRight;
		 WORD wBottom;
		 WORD wXResolution;
		 WORD wYResolution;
		 BYTE bPalette[48];
		 BYTE bReserved;
		 BYTE bPlanes;
		 WORD wLineBytes;
		 WORD wPaletteType;
		 WORD wSrcWidth;
		 WORD wSrcDepth;
		 BYTE bFiller[54];
} PCXHEADER;

// ����ԭ��
BOOL      WINAPI  PaintDIB (HDC, LPRECT, HDIB, LPRECT, CPalette* pPal);
BOOL      WINAPI  CreateDIBPalette(HDIB hDIB, CPalette* cPal);
LPSTR     WINAPI  FindDIBBits (LPSTR lpbi);
DWORD     WINAPI  DIBWidth (LPSTR lpDIB);
DWORD     WINAPI  DIBHeight (LPSTR lpDIB);
WORD      WINAPI  PaletteSize (LPSTR lpbi);
WORD      WINAPI  DIBNumColors (LPSTR lpbi);
WORD	  WINAPI  DIBBitCount(LPSTR lpbi);
HGLOBAL   WINAPI  CopyHandle (HGLOBAL h);

BOOL      WINAPI  SaveDIB (HDIB hDib, CFile& file);
HDIB      WINAPI  ReadDIBFile(CFile& file);

BOOL      WINAPI  DIBToPCX256(LPSTR lpDIB, CFile& file);
HDIB      WINAPI  ReadPCX256(CFile& file);

#endif //!_INC_DIBAPI
