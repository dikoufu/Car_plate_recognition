// carplateView.cpp : implementation of the CCarplateView class

#include "stdafx.h"
#include "carplate.h"

#include "carplateDoc.h"
#include "carplateView.h"
#include "mainfrm.h"
#include "DlgIntensity.h"
#include "DlgLinerPara.h"
#include "DlgPointThre.h"
#include "DlgPointWin.h"
#include "DlgPointStre.h"
#include "DlgGeoTran.h"
#include "DlgGeoZoom.h"
#include "DlgGeoRota.h"
#include "DlgSmooth.h"
#include "DlgMidFilter.h"
#include "DlgSharpThre.h"
#include "DlgColor.h"
#include "ColorTable.h"

#include "cDlgMorphErosion.h"
#include "cDlgMorphDilation.h"
#include "cDlgMorphOpen.h"
#include "cDlgMorphClose.h"

#include "DlgHuffman.h"
#include "DlgShannon.h"
#include "DlgCodeGIF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCarplateView

IMPLEMENT_DYNCREATE(CCarplateView, CScrollView)

BEGIN_MESSAGE_MAP(CCarplateView, CScrollView)
	//{{AFX_MSG_MAP(CCarplateView)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_GEOM_TRAN, OnGeomTran)
	ON_COMMAND(ID_GEOM_MIRV, OnGeomMirv)
	ON_COMMAND(ID_GEOM_MIRH, OnGeomMirh)
	ON_COMMAND(ID_GEOM_ROTA, OnGeomRota)
	ON_COMMAND(ID_GEOM_TRPO, OnGeomTrpo)
	ON_COMMAND(ID_GEOM_ZOOM, OnGeomZoom)
	ON_COMMAND(ID_POINT_INVERT, OnPointInvert)
	ON_COMMAND(ID_POINT_EQUA, OnPointEqua)
	ON_COMMAND(ID_POINT_LINER, OnPointLiner)
	ON_COMMAND(ID_POINT_WIND, OnPointWind)
	ON_COMMAND(ID_VIEW_INTENSITY, OnViewIntensity)
	ON_COMMAND(ID_POINT_STRE, OnPointStre)
	ON_COMMAND(ID_FREQ_FOUR, OnFreqFour)
	ON_COMMAND(ID_FREQ_DCT, OnFreqDct)
	ON_COMMAND(ID_POINT_THRE, OnPointThre)
	ON_COMMAND(ID_ENHA_SMOOTH, OnEnhaSmooth)
	ON_COMMAND(ID_ENHA_MidianF, OnENHAMidianF)
	ON_COMMAND(ID_ENHA_SHARP, OnEnhaSharp)
	ON_COMMAND(ID_ENHA_COLOR, OnEnhaColor)
	ON_COMMAND(ID_FILE_256ToGray, OnFILE256ToGray)
	ON_COMMAND(ID_ENHA_GRADSHARP, OnEnhaGradsharp)
	ON_COMMAND(ID_FREQ_WALH, OnFreqWalh)
	ON_COMMAND(ID_CODE_HUFFMAN, OnCodeHuffman)
	ON_COMMAND(ID_CODE_RLE, OnCodeRLE)
	ON_COMMAND(ID_CODE_IRLE, OnCodeIRLE)
	ON_COMMAND(ID_CODE_JEPG, OnCodeJEPG)
	ON_COMMAND(ID_CODE_IJEPG, OnCodeIJEPG)
	ON_COMMAND(ID_CODE_SHANNON, OnCodeShannon)
	ON_COMMAND(ID_MORPH_EROSION, OnMorphErosion)
	ON_COMMAND(ID_MORPH_DILATION, OnMorphDilation)
	ON_COMMAND(ID_MORPH_OPEN, OnMorphOpen)
	ON_COMMAND(ID_MORPH_CLOSE, OnMorphClose)
	ON_COMMAND(ID_MORPH_THINING, OnMorphThining)
	ON_COMMAND(ID_EDGE_FILL, OnEdgeFill)
	ON_COMMAND(ID_EDGE_GAUSS, OnEdgeGauss)
	ON_COMMAND(ID_EDGE_HOUGH, OnEdgeHough)
	ON_COMMAND(ID_EDGE_KIRSCH, OnEdgeKirsch)
	ON_COMMAND(ID_EDGE_PREWITT, OnEdgePrewitt)
	ON_COMMAND(ID_EDGE_ROBERT, OnEdgeRobert)
	ON_COMMAND(ID_EDGE_SOBEL, OnEdgeSobel)
	ON_COMMAND(ID_EDGE_TRACE, OnEdgeTrace)
	ON_COMMAND(ID_DETECT_HPROJECTION, OnDetectHprojection)
	ON_COMMAND(ID_DETECT_MINUS, OnDetectMinus)
	ON_COMMAND(ID_DETECT_TEMPLATE, OnDetectTemplate)
	ON_COMMAND(ID_DETECT_THRESHOLD, OnDetectThreshold)
	ON_COMMAND(ID_DETECT_VPROJECTION, OnDetectVprojection)
	ON_COMMAND(ID_RESTORE_BLUR, OnRestoreBlur)
	ON_COMMAND(ID_RESTORE_INVERSE, OnRestoreInverse)
	ON_COMMAND(ID_RESTORE_NOISEBLUR, OnRestoreNoiseblur)
	ON_COMMAND(ID_RESTORE_RANDOMNOISE, OnRestoreRandomnoise)
	ON_COMMAND(ID_RESTORE_SALTNOISE, OnRestoreSaltnoise)
	ON_COMMAND(ID_RESTORE_WIENER, OnRestoreWiener)
	ON_COMMAND(ID_EDGE_CONTOUR, OnEdgeContour)
	ON_COMMAND(ID_CODE_LZW, OnCodeLzw)
	ON_COMMAND(ID_CODE_ILZW, OnCodeIlzw)
	ON_COMMAND(ID_EDGE_FILL2, OnEdgeFill2)
	ON_COMMAND(IDM_CARPLATE_INVARIANT, OnCarplateInvariant)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCarplateView construction/destruction

CCarplateView::CCarplateView()
{
	// TODO: add construction code here

}

CCarplateView::~CCarplateView()
{
}

BOOL CCarplateView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCarplateView drawing

void CCarplateView::OnDraw(CDC* pDC)
{
	
	// ��ʾ�ȴ����
	BeginWaitCursor();
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// ��ȡDIB
	HDIB hDIB = pDoc->GetHDIB();
	
	// �ж�DIB�Ƿ�Ϊ��
	if (hDIB != NULL)
	{
		LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
		
		// ��ȡDIB���
		int cxDIB = (int) ::DIBWidth(lpDIB);
		
		// ��ȡDIB�߶�
		int cyDIB = (int) ::DIBHeight(lpDIB);

		::GlobalUnlock((HGLOBAL) hDIB);
		
		CRect rcDIB;
		rcDIB.top = rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;
		
		CRect rcDest;
		
		// �ж��Ƿ��Ǵ�ӡ
		if (pDC->IsPrinting())
		{
			// �Ǵ�ӡ���������ͼ���λ�úʹ�С���Ա����ҳ��
			
			// ��ȡ��ӡҳ���ˮƽ���(����)
			int cxPage = pDC->GetDeviceCaps(HORZRES);
			
			// ��ȡ��ӡҳ��Ĵ�ֱ�߶�(����)
			int cyPage = pDC->GetDeviceCaps(VERTRES);
			
			// ��ȡ��ӡ��ÿӢ��������
			int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
			int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);
			
			// �����ӡͼ���С�����ţ�����ҳ���ȵ���ͼ���С��
			rcDest.top = rcDest.left = 0;
			rcDest.bottom = (int)(((double)cyDIB * cxPage * cyInch)
					/ ((double)cxDIB * cxInch));
			rcDest.right = cxPage;
			
			// �����ӡͼ��λ�ã���ֱ���У�
			int temp = cyPage - (rcDest.bottom - rcDest.top);
			rcDest.bottom += temp/2;
			rcDest.top += temp/2;

		}
		else   
		// �Ǵ�ӡ
		{
			// ��������ͼ��
			rcDest = rcDIB;
		}
		
		// ���DIB
		::PaintDIB(pDC->m_hDC, &rcDest, pDoc->GetHDIB(),
			&rcDIB, pDoc->GetDocPalette());
	}
	
	// �ָ��������
	EndWaitCursor();
	
}

/////////////////////////////////////////////////////////////////////////////
// CCarplateView printing

BOOL CCarplateView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// ������ҳ��Ϊһ��
	pInfo->SetMaxPage(1);

	return DoPreparePrinting(pInfo);
}

void CCarplateView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCarplateView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCarplateView diagnostics

#ifdef _DEBUG
void CCarplateView::AssertValid() const
{
	CView::AssertValid();
}

void CCarplateView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCarplateDoc* CCarplateView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCarplateDoc)));
	return (CCarplateDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCarplateView message handlers


BOOL CCarplateView::OnEraseBkgnd(CDC* pDC) 
{
	// ��Ҫ��Ϊ�������Ӵ���Ĭ�ϵı���ɫ
	// ����ɫ���ĵ���Ա����m_refColorBKGָ��

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();

	// ����һ��Brush
	CBrush brush(pDoc->m_refColorBKG);                                              
                                                                                  
	// ������ǰ��Brush
	CBrush* pOldBrush = pDC->SelectObject(&brush);
	
	// ��ȡ�ػ�����
	CRect rectClip;
	pDC->GetClipBox(&rectClip);
	
	// �ػ�
	pDC->PatBlt(rectClip.left, rectClip.top, rectClip.Width(), rectClip.Height(), PATCOPY);

	// �ָ���ǰ��Brush
	pDC->SelectObject(pOldBrush);                                                  

	// ����
	return TRUE;

}

LRESULT CCarplateView::OnDoRealize(WPARAM wParam, LPARAM)
{
	ASSERT(wParam != NULL);

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// �ж�DIB�Ƿ�Ϊ��
	if (pDoc->GetHDIB() == NULL)
	{
		// ֱ�ӷ���
		return 0L;
	}
	
	// ��ȡPalette
	CPalette* pPal = pDoc->GetDocPalette();
	if (pPal != NULL)
	{
		// ��ȡMainFrame
		CMainFrame* pAppFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
		ASSERT_KINDOF(CMainFrame, pAppFrame);
		
		CClientDC appDC(pAppFrame);

		// All views but one should be a background palette.
		// wParam contains a handle to the active view, so the SelectPalette
		// bForceBackground flag is FALSE only if wParam == m_hWnd (this view)
		CPalette* oldPalette = appDC.SelectPalette(pPal, ((HWND)wParam) != m_hWnd);
		
		if (oldPalette != NULL)
		{
			UINT nColorsChanged = appDC.RealizePalette();
			if (nColorsChanged > 0)
				pDoc->UpdateAllViews(NULL);
			appDC.SelectPalette(oldPalette, TRUE);
		}
		else
		{
			TRACE0("\tCCarplateView::OnPaletteChanged�е���SelectPalette()ʧ�ܣ�\n");
		}
	}
	
	return 0L;
}

void CCarplateView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
}

void CCarplateView::CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType) 
{
	CScrollView::OnInitialUpdate();
	ASSERT(GetDocument() != NULL);
	
	SetScrollSizes(MM_TEXT, GetDocument()->GetDocSize());
}

void CCarplateView::OnActivateView(BOOL bActivate, CView* pActivateView,
					CView* pDeactiveView)
{
	CScrollView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	if (bActivate)
	{
		ASSERT(pActivateView == this);
		OnDoRealize((WPARAM)m_hWnd, 0);   // same as SendMessage(WM_DOREALIZE);
	}
}

void CCarplateView::OnEditCopy() 
{
	// ���Ƶ�ǰͼ��

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// �򿪼�����
	if (OpenClipboard())
	{
		// ���Ĺ����״
		BeginWaitCursor();
		
		// ��ռ�����
		EmptyClipboard();
		
		// ���Ƶ�ǰͼ�񵽼�����
		SetClipboardData (CF_DIB, CopyHandle((HANDLE) pDoc->GetHDIB()) );
		
		// �رռ�����
		CloseClipboard();
		
		// �ָ����
		EndWaitCursor();
	}
}

void CCarplateView::OnEditPaste() 
{
	// ճ��ͼ��
	
	// ������DIB
	HDIB hNewDIB = NULL;
	
	// �򿪼�����
	if (OpenClipboard())
	{
		// ���Ĺ����״
		BeginWaitCursor();

		// ��ȡ�������е�ͼ��
		hNewDIB = (HDIB) CopyHandle(::GetClipboardData(CF_DIB));

		// �رռ�����
		CloseClipboard();
		
		// �ж��Ƿ��ȡ�ɹ�
		if (hNewDIB != NULL)
		{
			// ��ȡ�ĵ�
			CCarplateDoc* pDoc = GetDocument();

			// �滻DIB��ͬʱ�ͷž�DIB����
			pDoc->ReplaceHDIB(hNewDIB);

			// ����DIB��С�͵�ɫ��
			pDoc->InitDIBData();

			// ��������
			pDoc->SetModifiedFlag(TRUE);
			
			// �������ù�����ͼ��С
			SetScrollSizes(MM_TEXT, pDoc->GetDocSize());

			// ʵ���µĵ�ɫ��
			OnDoRealize((WPARAM)m_hWnd,0);

			// ������ͼ
			pDoc->UpdateAllViews(NULL);
		}
		// �ָ����
		EndWaitCursor();
	}
}

void CCarplateView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	// �����ǰDIB���󲻿գ����Ʋ˵�����Ч
	pCmdUI->Enable(GetDocument()->GetHDIB() != NULL);
}

void CCarplateView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	// �����ǰ����������DIB����ճ���˵�����Ч
	pCmdUI->Enable(::IsClipboardFormatAvailable(CF_DIB));
}

void CCarplateView::OnViewIntensity() 
{
	// �鿴��ǰͼ��Ҷ�ֱ��ͼ
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧�ֲ鿴256ɫλͼ�Ҷ�ֱ��ͼ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// �����Ի���
	CDlgIntensity dlgPara;
	
	// ��ʼ������ֵ
	dlgPara.m_lpDIBBits = lpDIBBits;
	dlgPara.m_lWidth = ::DIBWidth(lpDIB);
	dlgPara.m_lHeight = ::DIBHeight(lpDIB);
	dlgPara.m_iLowGray = 0;
	dlgPara.m_iUpGray = 255;
	
	// ��ʾ�Ի�����ʾ�û��趨ƽ����
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

//////////////////////////////////////////////////////////////////////////////////////
//  ͼ�������
//
void CCarplateView::OnPointInvert() 
{
	// ͼ��ɫ
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;
	
	// ���Ա任��б��
	FLOAT fA;
	
	// ���Ա任�Ľؾ�
	FLOAT fB;
	
	// ��ɫ���������Ա任�ķ�����-x + 255
	fA = -1.0;
	fB = 255.0;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�ķ�ɫ�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�ķ�ɫ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����LinerTrans()������ɫ
	LinerTrans(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), fA, fB);
	
	// ��������
	pDoc->SetModifiedFlag(TRUE);
	
	// ������ͼ
	pDoc->UpdateAllViews(NULL);
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnPointLiner() 
{
	// ���Ա任
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;
	
	// �����Ի���
	CDlgLinerPara dlgPara;
	
	// ���Ա任��б��
	FLOAT fA;
	
	// ���Ա任�Ľؾ�
	FLOAT fB;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�����Ա任�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����Ա任��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ��ʼ������ֵ
	dlgPara.m_fA = 2.0;
	dlgPara.m_fB = -128.0;
	
	// ��ʾ�Ի�����ʾ�û��趨ƽ����
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û��趨��ƽ����
	fA = dlgPara.m_fA;
	fB = dlgPara.m_fB;
	
	// ɾ���Ի���
	delete dlgPara;	
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����LinerTrans()�����������Ա任
	LinerTrans(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), fA, fB);
	
	// ��������
	pDoc->SetModifiedFlag(TRUE);
	
	// ������ͼ
	pDoc->UpdateAllViews(NULL);
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnPointThre() 
{
	// ��ֵ�任
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// �����Ի���
	CDlgPointThre  dlgPara;
	
	// ��ֵ
	BYTE	bThre;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ����ֵ�任�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ����ֵ�任��", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ��ʼ������ֵ
	dlgPara.m_bThre = 128;
	
	// ��ʾ�Ի�����ʾ�û��趨��ֵ
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û��趨����ֵ
	bThre = dlgPara.m_bThre;
	
	// ɾ���Ի���
	delete dlgPara;	
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����ThresholdTrans()����������ֵ�任
	ThresholdTrans(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), bThre);
	
	// ��������
	pDoc->SetModifiedFlag(TRUE);
	
	// ������ͼ
	pDoc->UpdateAllViews(NULL);
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
	
	// �ָ����
	EndWaitCursor();
}

void CCarplateView::OnPointWind() 
{
	// ���ڱ任
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;
	
	// �����Ի���
	CDlgPointWin  dlgPara;
	
	// ��������
	BYTE	bLow;
	
	// ��������
	BYTE	bUp;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�Ĵ��ڱ任�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�Ĵ��ڱ任��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ��ʼ������ֵ
	dlgPara.m_bLow = 0;
	dlgPara.m_bUp = 255;
	
	// ��ʾ�Ի�����ʾ�û��趨����������
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û��趨�Ĵ���������
	bLow = dlgPara.m_bLow;
	bUp = dlgPara.m_bUp;
	
	// ɾ���Ի���
	delete dlgPara;	
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����WindowTrans()�������д��ڱ任
	WindowTrans(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), bLow, bUp);
	
	// ��������
	pDoc->SetModifiedFlag(TRUE);
	
	// ������ͼ
	pDoc->UpdateAllViews(NULL);
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
	
	// �ָ����
	EndWaitCursor();
}

void CCarplateView::OnPointStre() 
{
	// �Ҷ�����
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// �����Ի���
	CDlgPointStre dlgPara;
	
	// ��1����
	BYTE	bX1;
	BYTE	bY1;
	
	// ��2����
	BYTE	bX2;
	BYTE	bY2;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�ĻҶ����죬�����Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�ĻҶ����죡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ��ʼ������ֵ
	dlgPara.m_bX1 = 50;
	dlgPara.m_bY1 = 30;
	dlgPara.m_bX2 = 200;
	dlgPara.m_bY2 = 220;
	
	// ��ʾ�Ի�����ʾ�û��趨����λ��
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û����趨
	bX1 = dlgPara.m_bX1;
	bY1 = dlgPara.m_bY1;
	bX2 = dlgPara.m_bX2;
	bY2 = dlgPara.m_bY2;
	
	// ɾ���Ի���
	delete dlgPara;	
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����GrayStretch()�������лҶ�����
	GrayStretch(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), bX1, bY1, bX2, bY2);
	
	// ��������
	pDoc->SetModifiedFlag(TRUE);
	
	// ������ͼ
	pDoc->UpdateAllViews(NULL);
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
}

void CCarplateView::OnPointEqua() 
{
	// �ҶȾ���
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��ֱ��ͼ���⣬�����Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ��ֱ��ͼ���⣡", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����InteEqualize()��������ֱ��ͼ����
	InteEqualize(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB));
	
	// ��������
	pDoc->SetModifiedFlag(TRUE);
	
	// ������ͼ
	pDoc->UpdateAllViews(NULL);
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

//////////////////////////////////////////////////////////////////////////////////////
//  ͼ�񼸺α任
//
void CCarplateView::OnGeomTran() 
{
	// ƽ��λͼ

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��ƽ�ƣ������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ��ƽ�ƣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	LONG lXOffset;
	LONG lYOffset;
	
	// �����Ի���
	CDlgGeoTran dlgPara;
	
	// ��ʼ������ֵ
	dlgPara.m_XOffset = 100;
	dlgPara.m_YOffset = 100;
	
	// ��ʾ�Ի�����ʾ�û��趨ƽ����
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û��趨��ƽ����
	lXOffset = dlgPara.m_XOffset;
	lYOffset = dlgPara.m_YOffset;
	
	// ɾ���Ի���
	delete dlgPara;	
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����TranslationDIB()����ƽ��DIB
	if (TranslationDIB1(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), lXOffset, lYOffset))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
}

void CCarplateView::OnGeomMirv() 
{
	// ��ֱ����
	

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR lpDIB;

	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�Ĵ�ֱ���������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�Ĵ�ֱ����", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����MirrorDIB()������ֱ����DIB
	if (MirrorDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), FALSE))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();

}

void CCarplateView::OnGeomMirh() 
{
	// ˮƽ����

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR lpDIB;

	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��ˮƽ���������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ��ˮƽ����", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����MirrorDIB()����ˮƽ����DIB
	if (MirrorDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), TRUE))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();

	
}

void CCarplateView::OnGeomTrpo() 
{
	// ͼ��ת��

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR lpDIB;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��ת�ã������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ��ת�ã�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����TransposeDIB()����ת��DIB
	if (TransposeDIB(lpDIB))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);
		
		// ����DIB��С�͵�ɫ��
		pDoc->InitDIBData();
		
		// �������ù�����ͼ��С
		SetScrollSizes(MM_TEXT, pDoc->GetDocSize());

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();

}

void CCarplateView::OnGeomZoom() 
{
	// ͼ������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR lpDIB;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�����ţ������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����ţ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���ű���
	float fXZoomRatio;
	float fYZoomRatio;
	
	// �����Ի���
	CDlgGeoZoom dlgPara;
	
	// ��ʼ������ֵ
	dlgPara.m_XZoom = 0.5;
	dlgPara.m_YZoom = 0.5;
	
	// ��ʾ�Ի�����ʾ�û��趨ƽ����
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û��趨��ƽ����
	fXZoomRatio = dlgPara.m_XZoom;
	fYZoomRatio = dlgPara.m_YZoom;
	
	// ɾ���Ի���
	delete dlgPara;	
	
	// ������DIB
	HDIB hNewDIB = NULL;
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����ZoomDIB()����ת��DIB
	hNewDIB = (HDIB) ZoomDIB(lpDIB, fXZoomRatio, fYZoomRatio);
	
	// �ж������Ƿ�ɹ�
	if (hNewDIB != NULL)
	{
		
		// �滻DIB��ͬʱ�ͷž�DIB����
		pDoc->ReplaceHDIB(hNewDIB);

		// ����DIB��С�͵�ɫ��
		pDoc->InitDIBData();
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);
		
		// �������ù�����ͼ��С
		SetScrollSizes(MM_TEXT, pDoc->GetDocSize());

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnGeomRota() 
{
	// ͼ����ת

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR lpDIB;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ����ת�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ����ת��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���ű���
	int iRotateAngle;
	
	// �����Ի���
	CDlgGeoRota dlgPara;
	
	// ��ʼ������ֵ
	dlgPara.m_iRotateAngle = 90;
	
	// ��ʾ�Ի�����ʾ�û��趨��ת�Ƕ�
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û��趨��ƽ����
	iRotateAngle = dlgPara.m_iRotateAngle;
	
	// ɾ���Ի���
	delete dlgPara;	
	
	
	// ������DIB
	HDIB hNewDIB = NULL;
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����RotateDIB()������תDIB
	hNewDIB = (HDIB) RotateDIB(lpDIB, iRotateAngle);
	
	// �ж���ת�Ƿ�ɹ�
	if (hNewDIB != NULL)
	{
		
		// �滻DIB��ͬʱ�ͷž�DIB����
		pDoc->ReplaceHDIB(hNewDIB);

		// ����DIB��С�͵�ɫ��
		pDoc->InitDIBData();
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);
		
		// �������ù�����ͼ��С
		SetScrollSizes(MM_TEXT, pDoc->GetDocSize());
		
		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
}

//////////////////////////////////////////////////////////////////////////////////////
//  ͼ����ǿ
//
void CCarplateView::OnEnhaSmooth() 
{
	// ͼ��ƽ��
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
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
	
	// ģ��Ԫ������
	FLOAT	aValue[25];
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��ƽ���������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ��ƽ����", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// �����Ի���
	CDlgSmooth dlgPara;
	
	// ��ģ�����鸳��ֵ��Ϊƽ��ģ�壩
	aValue[0] = 1.0;
	aValue[1] = 1.0;
	aValue[2] = 1.0;
	aValue[3] = 0.0;
	aValue[4] = 0.0;
	aValue[5] = 1.0;
	aValue[6] = 1.0;
	aValue[7] = 1.0;
	aValue[8] = 0.0;
	aValue[9] = 0.0;
	aValue[10] = 1.0;
	aValue[11] = 1.0;
	aValue[12] = 1.0;
	aValue[13] = 0.0;
	aValue[14] = 0.0;
	aValue[15] = 0.0;
	aValue[16] = 0.0;
	aValue[17] = 0.0;
	aValue[18] = 0.0;
	aValue[19] = 0.0;
	aValue[20] = 0.0;
	aValue[21] = 0.0;
	aValue[22] = 0.0;
	aValue[23] = 0.0;
	aValue[24] = 0.0;
	
	// ��ʼ���Ի������ֵ
	dlgPara.m_intType = 0;
	dlgPara.m_iTempH  = 3;
	dlgPara.m_iTempW  = 3;
	dlgPara.m_iTempMX = 1;
	dlgPara.m_iTempMY = 1;
	dlgPara.m_fTempC  = (FLOAT) (1.0 / 9.0);
	dlgPara.m_fpArray = aValue;
	
	// ��ʾ�Ի�����ʾ�û��趨ƽ����
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û��趨��ƽ����
	iTempH  = dlgPara.m_iTempH;
	iTempW  = dlgPara.m_iTempW;
	iTempMX = dlgPara.m_iTempMX;
	iTempMY = dlgPara.m_iTempMY;
	fTempC  = dlgPara.m_fTempC;
	
	// ɾ���Ի���
	delete dlgPara;	
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����Template()����ƽ��DIB
	if (::Template(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), 
		  iTempH, iTempW, iTempMX, iTempMY, aValue, fTempC))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnENHAMidianF() 
{
	// ��ֵ�˲�
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// �˲����ĸ߶�
	int iFilterH;
	
	// �˲����Ŀ��
	int iFilterW;
	
	// ����Ԫ�ص�X����
	int iFilterMX;
	
	// ����Ԫ�ص�Y����
	int iFilterMY;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ����ֵ�˲��������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ����ֵ�˲���", "ϵͳ��ʾ" ,
			MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// �����Ի���
	CDlgMidFilter dlgPara;
	
	// ��ʼ������ֵ
	dlgPara.m_iFilterType = 0;
	dlgPara.m_iFilterH = 3;
	dlgPara.m_iFilterW = 1;
	dlgPara.m_iFilterMX = 0;
	dlgPara.m_iFilterMY = 1;
	
	// ��ʾ�Ի�����ʾ�û��趨ƽ����
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û����趨
	iFilterH = dlgPara.m_iFilterH;
	iFilterW = dlgPara.m_iFilterW;
	iFilterMX = dlgPara.m_iFilterMX;
	iFilterMY = dlgPara.m_iFilterMY;
	
	// ɾ���Ի���
	delete dlgPara;	
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����MedianFilter()������ֵ�˲�
	if (::MedianFilter(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), 
		  iFilterH, iFilterW, iFilterMX, iFilterMY))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnEnhaGradsharp() 
{
	// �ݶ���
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);	
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ���ݶ��񻯣������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ���ݶ��񻯣�", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ��ֵ
	BYTE	bThre;
	
	// �����Ի���
	CDlgSharpThre dlgPara;
	
	// ��ʼ������ֵ
	dlgPara.m_bThre = 10;
	
	// ��ʾ�û�������ֵ
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û����趨
	bThre = dlgPara.m_bThre;
	
	// ɾ���Ի���
	delete dlgPara;	
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����GradSharp()���������ݶȰ���
	if (::GradSharp(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), bThre))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnEnhaSharp() 
{
	// ͼ����
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;
	
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
	
	// ģ��Ԫ������
	FLOAT	aValue[9];
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);	
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ���񻯣������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ���񻯣�", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����������˹ģ�����
	iTempW = 3;
	iTempH = 3;
	fTempC = 1.0;
	iTempMX = 1;
	iTempMY = 1;
	aValue[0] = -1.0;
	aValue[1] = -1.0;
	aValue[2] = -1.0;
	aValue[3] = -1.0;
	aValue[4] =  9.0;
	aValue[5] = -1.0;
	aValue[6] = -1.0;
	aValue[7] = -1.0;
	aValue[8] = -1.0;
	
	// ����Template()������������˹ģ����DIB
	if (::Template(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), 
		  iTempH, iTempW, iTempMX, iTempMY, aValue, fTempC))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
}

void CCarplateView::OnEnhaColor() 
{
	// α��ɫ����
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// �����û�ѡ���α��ɫ���������
	int		nColor;
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ��ֻ����256ɫλͼ��α��ɫ�任�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ��α��ɫ�任��", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// �����Ի���
	CDlgColor dlgPara;
	
	// ��ʼ������ֵ
	if (pDoc->m_nColorIndex >= 0)
	{
		// ��ʼѡ�е�ǰ��α��ɫ
		dlgPara.m_nColor = pDoc->m_nColorIndex;
	}
	else
	{
		// ��ʼѡ�лҶ�α��ɫ�����
		dlgPara.m_nColor = 0;
	}
	
	// ָ�����������ָ��
	dlgPara.m_lpColorName = (LPSTR) ColorScaleName;
	
	// α��ɫ������Ŀ
	dlgPara.m_nColorCount = COLOR_SCALE_COUNT;
	
	// �����ַ�������
	dlgPara.m_nNameLen = sizeof(ColorScaleName) / COLOR_SCALE_COUNT;
	
	// ��ʾ�Ի�����ʾ�û��趨ƽ����
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û����趨
	nColor = dlgPara.m_nColor;
	
	// ɾ���Ի���
	delete dlgPara;	
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// �ж�α��ɫ�����Ƿ�Ķ�
	if (pDoc->m_nColorIndex != nColor)
	{
		// ����ReplaceColorPal()�����任��ɫ��
		::ReplaceColorPal(lpDIB, (BYTE*) ColorsTable[nColor]);
		
		// �滻��ǰ�ĵ���ɫ��
		pDoc->GetDocPalette()->SetPaletteEntries(0, 256, (LPPALETTEENTRY) ColorsTable[nColor]);
		
		// �������Ա����
		pDoc->m_nColorIndex = nColor;
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);
		
		// ʵ���µĵ�ɫ��
		OnDoRealize((WPARAM)m_hWnd,0);
		
		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
}

void CCarplateView::OnFILE256ToGray() 
{
	// ��256ɫλͼת���ɻҶ�ͼ
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// ��ɫ���е���ɫ��Ŀ
	WORD wNumColors;
	
	// ��ȡDIB����ɫ���е���ɫ��Ŀ
	wNumColors = ::DIBNumColors(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ
	if (wNumColors != 256)
	{
		// ��ʾ�û�
		MessageBox("��256ɫλͼ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ָ��DIB���ص�ָ��
	BYTE *	lpSrc;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ͼ����
	LONG	lWidth;
	
	// ͼ��߶�
	LONG	lHeight;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ָ��BITMAPINFO�ṹ��ָ�루Win3.0��
	LPBITMAPINFO lpbmi;
	
	// ָ��BITMAPCOREINFO�ṹ��ָ��
	LPBITMAPCOREINFO lpbmc;
	
	// �����Ƿ���Win3.0 DIB�ı��
	BOOL bWinStyleDIB;
	
	// ��ȡָ��BITMAPINFO�ṹ��ָ�루Win3.0��
	lpbmi = (LPBITMAPINFO)lpDIB;
	
	// ��ȡָ��BITMAPCOREINFO�ṹ��ָ��
	lpbmc = (LPBITMAPCOREINFO)lpDIB;
	
	// �Ҷ�ӳ���
	BYTE bMap[256];
	
	// �ж��Ƿ���WIN3.0��DIB
	bWinStyleDIB = IS_WIN30_DIB(lpDIB);
	
	// ����Ҷ�ӳ������������ɫ�ĻҶ�ֵ����������DIB��ɫ��
	for (i = 0; i < 256; i ++)
	{
		if (bWinStyleDIB)
		{
			// �������ɫ��Ӧ�ĻҶ�ֵ
			bMap[i] = (BYTE)(0.299 * lpbmi->bmiColors[i].rgbRed +
						     0.587 * lpbmi->bmiColors[i].rgbGreen +
					         0.114 * lpbmi->bmiColors[i].rgbBlue + 0.5);
			
			// ����DIB��ɫ���ɫ����
			lpbmi->bmiColors[i].rgbRed = i;
			
			// ����DIB��ɫ����ɫ����
			lpbmi->bmiColors[i].rgbGreen = i;
			
			// ����DIB��ɫ����ɫ����
			lpbmi->bmiColors[i].rgbBlue = i;
			
			// ����DIB��ɫ�屣��λ
			lpbmi->bmiColors[i].rgbReserved = 0;
		}
		else
		{
			// �������ɫ��Ӧ�ĻҶ�ֵ
			bMap[i] = (BYTE)(0.299 * lpbmc->bmciColors[i].rgbtRed +
						     0.587 * lpbmc->bmciColors[i].rgbtGreen +
					         0.114 * lpbmc->bmciColors[i].rgbtBlue + 0.5);
			
			// ����DIB��ɫ���ɫ����
			lpbmc->bmciColors[i].rgbtRed = i;
			
			// ����DIB��ɫ����ɫ����
			lpbmc->bmciColors[i].rgbtGreen = i;
			
			// ����DIB��ɫ����ɫ����
			lpbmc->bmciColors[i].rgbtBlue = i;
		}
	}

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);	
	
	// ��ȡͼ����
	lWidth = ::DIBWidth(lpDIB);
	
	// ��ȡͼ��߶�
	lHeight = ::DIBHeight(lpDIB);
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ����ÿ�����ص���ɫ�����������ջҶ�ӳ����ɻҶ�ֵ��
	// ÿ��
	for(i = 0; i < lHeight; i++)
	{
		// ÿ��
		for(j = 0; j < lWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// �任
			*lpSrc = bMap[*lpSrc];
		}
	}
	
	// �滻��ǰ��ɫ��Ϊ�Ҷȵ�ɫ��
	pDoc->GetDocPalette()->SetPaletteEntries(0, 256, (LPPALETTEENTRY) ColorsTable[0]);
	
	// ��������
	pDoc->SetModifiedFlag(TRUE);
	
	// ʵ���µĵ�ɫ��
	OnDoRealize((WPARAM)m_hWnd,0);
	
	// ������ͼ
	pDoc->UpdateAllViews(NULL);
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();	
}

//////////////////////////////////////////////////////////////////////////////////////
//  ͼ�������任
//

void CCarplateView::OnFreqFour() 
{
	// ͼ����Ҷ�任
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�ĸ���Ҷ�任�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�ĸ���Ҷ�任��", "ϵͳ��ʾ" ,
			MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����Fourier()�������и���Ҷ�任
	if (::Fourier(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);
		
		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
	
	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnFreqDct() 
{
	// ͼ����ɢ���ұ任
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ����ɢ���ұ任�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ����ɢ���ұ任��", "ϵͳ��ʾ" ,
			MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����DIBDct()����������ɢ���ұ任
	if (::DIBDct(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);
		
		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
	
	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnFreqWalh() 
{
	// ͼ���ֶ�ʲ-������任
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ���ֶ�ʲ-������任�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ���ֶ�ʲ-������任��", "ϵͳ��ʾ" ,
			MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ����DIBWalsh()����DIBWalsh1()�������б任
	if (::DIBWalsh1(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);
		
		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
	
	// �ָ����
	EndWaitCursor();
	
}

//////////////////////////////////////////////////////////////////////////////////////
//  ��̬ѧ�任
//
void CCarplateView::OnMorphErosion() 
{
	//��ʴ����

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�ĸ�ʴ�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�ĸ�ʴ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	int nMode;
	
	// �����Ի���
	cDlgMorphErosion dlgPara;
	
	// ��ʼ������ֵ
	dlgPara.m_nMode = 0;
	
	// ��ʾ�Ի�����ʾ�û��趨��ʴ����
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û��趨�ĸ�ʴ����
	nMode = dlgPara.m_nMode;

	int structure[3][3];
	if (nMode == 2)
	{
		structure[0][0]=dlgPara.m_nStructure1;
		structure[0][1]=dlgPara.m_nStructure2;
		structure[0][2]=dlgPara.m_nStructure3;
		structure[1][0]=dlgPara.m_nStructure4;
		structure[1][1]=dlgPara.m_nStructure5;
		structure[1][2]=dlgPara.m_nStructure6;
		structure[2][0]=dlgPara.m_nStructure7;
		structure[2][1]=dlgPara.m_nStructure8;
		structure[2][2]=dlgPara.m_nStructure9;
	}
	
	// ɾ���Ի���
	delete dlgPara;	
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����ErosionDIB()������ʴDIB
	if (ErosionDIB(lpDIBBits, WIDTHBYTES(::DIBWidth(lpDIB) * 8), ::DIBHeight(lpDIB), nMode , structure))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܻ���ͼ���к���0��255֮�������ֵ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnMorphOpen() 
{
	//������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�Ŀ����㣬�����Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�Ŀ����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	int nMode;
	
	// �����Ի���
	cDlgMorphOpen dlgPara;
	
	// ��ʼ������ֵ
	dlgPara.m_nMode = 0;
	
	// ��ʾ�Ի�����ʾ�û��趨�����㷽��
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û��趨�Ŀ����㷽��
	nMode = dlgPara.m_nMode;

	int structure[3][3];
	if (nMode == 2)
	{
		structure[0][0]=dlgPara.m_nStructure1;
		structure[0][1]=dlgPara.m_nStructure2;
		structure[0][2]=dlgPara.m_nStructure3;
		structure[1][0]=dlgPara.m_nStructure4;
		structure[1][1]=dlgPara.m_nStructure5;
		structure[1][2]=dlgPara.m_nStructure6;
		structure[2][0]=dlgPara.m_nStructure7;
		structure[2][1]=dlgPara.m_nStructure8;
		structure[2][2]=dlgPara.m_nStructure9;
	}
	
	// ɾ���Ի���
	delete dlgPara;	
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����ErosionDIB()����������DIB
	//if (OpenDIB(lpDIBBits, WIDTHBYTES(::DIBWidth(lpDIB) * 8), ::DIBHeight(lpDIB), nMode , structure))
	if (OpenDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB), nMode , structure))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܻ���ͼ���к���0��255֮�������ֵ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
	
}

void CCarplateView::OnMorphThining() 
{
	//������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�ı����㣬�����Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ��ϸ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����ThiningDIB()������DIB���б�����
	if (ThiningDIB(lpDIBBits, WIDTHBYTES(::DIBWidth(lpDIB) * 8), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܻ���ͼ���к���0��255֮�������ֵ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnMorphClose() 
{
	//������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�ı����㣬�����Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�ı����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	int nMode;
	
	// �����Ի���
	cDlgMorphClose dlgPara;
	
	// ��ʼ������ֵ
	dlgPara.m_nMode = 0;
	
	// ��ʾ�Ի�����ʾ�û��趨�����㷽��
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û��趨�ı����㷽��
	nMode = dlgPara.m_nMode;

	int structure[3][3];
	if (nMode == 2)
	{
		structure[0][0]=dlgPara.m_nStructure1;
		structure[0][1]=dlgPara.m_nStructure2;
		structure[0][2]=dlgPara.m_nStructure3;
		structure[1][0]=dlgPara.m_nStructure4;
		structure[1][1]=dlgPara.m_nStructure5;
		structure[1][2]=dlgPara.m_nStructure6;
		structure[2][0]=dlgPara.m_nStructure7;
		structure[2][1]=dlgPara.m_nStructure8;
		structure[2][2]=dlgPara.m_nStructure9;
	}
	
	// ɾ���Ի���
	delete dlgPara;	
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����CloseDIB()������DIB���б�����
	if (CloseDIB(lpDIBBits, WIDTHBYTES(::DIBWidth(lpDIB) * 8), ::DIBHeight(lpDIB), nMode , structure))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܻ���ͼ���к���0��255֮�������ֵ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
		
}

void CCarplateView::OnMorphDilation() 
{
	//��������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�����ͣ������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����ͣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	int nMode;
	
	// �����Ի���
	cDlgMorphDilation dlgPara;
	
	// ��ʼ������ֵ
	dlgPara.m_nMode = 0;
	
	// ��ʾ�Ի�����ʾ�û��趨���ͷ���
	if (dlgPara.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û��趨�����ͷ���
	nMode = dlgPara.m_nMode;

	int structure[3][3];
	if (nMode == 2)
	{
		structure[0][0]=dlgPara.m_nStructure1;
		structure[0][1]=dlgPara.m_nStructure2;
		structure[0][2]=dlgPara.m_nStructure3;
		structure[1][0]=dlgPara.m_nStructure4;
		structure[1][1]=dlgPara.m_nStructure5;
		structure[1][2]=dlgPara.m_nStructure6;
		structure[2][0]=dlgPara.m_nStructure7;
		structure[2][1]=dlgPara.m_nStructure8;
		structure[2][2]=dlgPara.m_nStructure9;
	}
	
	// ɾ���Ի���
	delete dlgPara;	
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����DilationDIB()��������DIB
	if (DilationDIB(lpDIBBits, WIDTHBYTES(::DIBWidth(lpDIB) * 8), ::DIBHeight(lpDIB), nMode , structure))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܻ���ͼ���к���0��255֮�������ֵ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

//////////////////////////////////////////////////////////////////////////////////////
//  ��Ե������
//
void CCarplateView::OnEdgeHough() 
{
	//Hough����

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��Hough�任�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����HoughDIB()������DIB
	if (HoughDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܻ���ͼ���к���0��255֮�������ֵ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnEdgeGauss() 
{
	//Gauss��Ե�������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�ı�Ե��⣬�����Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����GaussDIB()������DIB���б�Ե���
	if (GaussDIB(lpDIBBits, WIDTHBYTES(::DIBWidth(lpDIB) * 8), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnEdgeKirsch() 
{
	//Kirsch��Ե�������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�ı�Ե��⣬�����Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����KirschDIB()������DIB���б�Ե���
	if (KirschDIB(lpDIBBits, WIDTHBYTES(::DIBWidth(lpDIB) * 8), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnEdgePrewitt() 
{
	//Prewitt��Ե�������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�ı�Ե��⣬�����Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����PrewittDIB()������DIB���б�Ե���
	if (PrewittDIB(lpDIBBits, WIDTHBYTES(::DIBWidth(lpDIB) * 8), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnEdgeRobert() 
{
	//Robert��Ե�������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�ı�Ե��⣬�����Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����RobertDIB()������DIB���б�Ե���
	if (RobertDIB(lpDIBBits, WIDTHBYTES(::DIBWidth(lpDIB) * 8), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
		
}

void CCarplateView::OnEdgeSobel() 
{
	//Sobel��Ե�������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�ı�Ե��⣬�����Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����SobelDIB()������DIB���б�Ե���
	if (SobelDIB(lpDIBBits, WIDTHBYTES(::DIBWidth(lpDIB) * 8), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
		
	
}

void CCarplateView::OnEdgeFill() 
{
	//�����������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��������䣬�����Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����FillDIB()������DIB�����������
	if (FillDIB(lpDIBBits, WIDTHBYTES(::DIBWidth(lpDIB) * 8), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
		
}

void CCarplateView::OnEdgeContour() 
{
	//������ȡ����

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��������ȡ�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����FillDIB()������DIB����������ȡ
	if (ContourDIB(lpDIBBits, WIDTHBYTES(::DIBWidth(lpDIB) * 8), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
}

void CCarplateView::OnEdgeTrace() 
{
	//������������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ���������٣������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����TraceDIB()������DIB������������
	if (TraceDIB(lpDIBBits, ::DIBWidth(lpDIB) , ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
}

//////////////////////////////////////////////////////////////////////////////////////
//  ͼ�����
//
void CCarplateView::OnDetectMinus() 
{
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR lpDIB,lpDIBBK;

	// ָ��DIB����ָ��
	LPSTR    lpDIBBits,lpDIBBitsBK;
	
	//ͼ��Ŀ����߶�
	long lWidth,lHeight;

	HDIB hDIBBK;

	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��ˮƽ���������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ��ƽ�ƣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	lWidth = ::DIBWidth(lpDIB);
	lHeight = ::DIBHeight(lpDIB);
	CFileDialog dlg(TRUE,"bmp","*.bmp");
	if(dlg.DoModal() == IDOK)
	{
 
	 	CFile file;
	 	CFileException fe;
 
	 	CString strPathName;
 
		strPathName = dlg.GetPathName();
 
		// ���ļ�
		VERIFY(file.Open(strPathName, CFile::modeRead | CFile::shareDenyWrite, &fe));

		// ���Ե���ReadDIBFile()��ȡͼ��
		TRY
		{
 			hDIBBK = ::ReadDIBFile(file);
		}
		CATCH (CFileException, eLoad)
		{
			// ��ȡʧ��
	 		file.Abort();
 		
			// �ָ������״
			EndWaitCursor();
 		
			// ����ʧ��
			//ReportSaveLoadException(strPathName, eLoad,
//				FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
			
			// ����DIBΪ��
			hDIBBK = NULL;
			
			// ����
			return;
		}
		END_CATCH
 	
		// ��ʼ��DIB
		//InitDIBData();
 	
		// �ж϶�ȡ�ļ��Ƿ�ɹ�
		if (hDIBBK == NULL)
		{
 			// ʧ�ܣ����ܷ�BMP��ʽ
 			CString strMsg;
 			strMsg = "��ȡͼ��ʱ���������ǲ�֧�ָ����͵�ͼ���ļ���";
 		
 			// ��ʾ����
 			MessageBox(strMsg, NULL, MB_ICONINFORMATION | MB_OK);
  		
 			// �ָ������״
 			EndWaitCursor();
 		
 			// ����
 			return;
 		}
 	}
	else
	{
 		// �ָ������״
 		EndWaitCursor();
 		
		return;
	}
	// ����DIB
	lpDIBBK = (LPSTR) ::GlobalLock((HGLOBAL) hDIBBK);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�Ĳ�Ӱ�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIBBK) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) hDIBBK);
		
		// ����
		return;
	}
	
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBitsBK = ::FindDIBBits(lpDIBBK);
	
	// ����AddMinusDIB()�����������DIB
	if (AddMinusDIB(lpDIBBits,lpDIBBitsBK, lWidth,lHeight,false))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
	::GlobalUnlock((HGLOBAL) hDIBBK);

	// �ָ����
	EndWaitCursor();	
}

void CCarplateView::OnDetectHprojection() 
{
	//ˮƽͶӰ

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��ͶӰ�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����HprojectDIB()������DIB����ˮƽͶӰ
	if (HprojectDIB(lpDIBBits,::DIBWidth(lpDIB), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
		
}

void CCarplateView::OnDetectVprojection() 
{
	//��ֱͶӰ

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��ͶӰ�������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����VprojectDIB()������DIB���д�ֱͶӰ
	if (VprojectDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
			
}

void CCarplateView::OnDetectTemplate() 
{
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR lpDIB,lpTemplateDIB;

	// ָ��DIB����ָ��
	LPSTR    lpDIBBits,lpTemplateDIBBits;
	
	//ͼ��Ŀ����߶�
	long lWidth,lHeight;

	//ģ��Ŀ����߶�
	long lTemplateWidth,lTemplateHeight;

	HDIB hTemplateDIB;

	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��ˮƽ���������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ��ƽ�ƣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	lWidth = ::DIBWidth(lpDIB);
	lHeight = ::DIBHeight(lpDIB);
	CFileDialog dlg(TRUE,"bmp","*.bmp");
	if(dlg.DoModal() == IDOK)
	{
 
	 	CFile file;
	 	CFileException fe;
 
	 	CString strPathName;
 
		strPathName = dlg.GetPathName();
 
		// ���ļ�
		VERIFY(file.Open(strPathName, CFile::modeRead | CFile::shareDenyWrite, &fe));

		// ���Ե���ReadDIBFile()��ȡͼ��
		TRY
		{
 			hTemplateDIB = ::ReadDIBFile(file);
		}
		CATCH (CFileException, eLoad)
		{
			// ��ȡʧ��
	 		file.Abort();
 		
			// �ָ������״
			EndWaitCursor();
 		
			// ����ʧ��
			//ReportSaveLoadException(strPathName, eLoad,
//				FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
			
			// ����DIBΪ��
			hTemplateDIB = NULL;
			
			// ����
			return;
		}
		END_CATCH
 	
		// ��ʼ��DIB
		//InitDIBData();
 	
		// �ж϶�ȡ�ļ��Ƿ�ɹ�
		if (hTemplateDIB == NULL)
		{
 			// ʧ�ܣ����ܷ�BMP��ʽ
 			CString strMsg;
 			strMsg = "��ȡͼ��ʱ���������ǲ�֧�ָ����͵�ͼ���ļ���";
 		
 			// ��ʾ����
 			MessageBox(strMsg, NULL, MB_ICONINFORMATION | MB_OK);
  		
 			// �ָ������״
 			EndWaitCursor();
 		
 			// ����
 			return;
 		}
 	}
	else
	{
 		// �ָ������״
 		EndWaitCursor();

		return;
	}
	// ����DIB
	lpTemplateDIB = (LPSTR) ::GlobalLock((HGLOBAL) hTemplateDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��ģ��ƥ�䣬�����Ŀ������ƣ�
	if (::DIBNumColors(lpTemplateDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) hTemplateDIB);
		
		// ����
		return;
	}
	
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpTemplateDIBBits = ::FindDIBBits(lpTemplateDIB);
	
	lTemplateWidth = ::DIBWidth(lpTemplateDIB);
	lTemplateHeight = ::DIBHeight(lpTemplateDIB);
	if(lTemplateHeight > lHeight || lTemplateWidth > lWidth )
	{
		// ��ʾ�û�
		MessageBox("ģ��ߴ����Դͼ��ߴ磡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) hTemplateDIB);
		
		// ����
		return;

	}
	// ����TemplateMatchDIB()��������ģ��ƥ��
	if (TemplateMatchDIB(lpDIBBits,lpTemplateDIBBits, lWidth,lHeight, lTemplateWidth,lTemplateHeight))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
	::GlobalUnlock((HGLOBAL) hTemplateDIB);

	// �ָ����
	EndWaitCursor();	
	
}


void CCarplateView::OnDetectThreshold() 
{
	//��ֵ�ָ�

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ����ֵ�ָ�����Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����ThresholdDIB()������DIB������ֵ�ָ�
	if (ThresholdDIB(lpDIBBits,::DIBWidth(lpDIB), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

//////////////////////////////////////////////////////////////////////////////////////
//  ͼ��ԭ
//
void CCarplateView::OnRestoreBlur() 
{
	//ͼ��ģ������������һ������ԭ��ͼ��

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��ģ�������������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����Blur1DIB()������DIB����ģ������
	if (BlurDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܻ�ͼ��ߴ粻����Ҫ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
		
}

void CCarplateView::OnRestoreInverse() 
{
	//ͼ�����˲���ԭ����

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�ĸ�ԭ�����������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����RestoreDIB()������DIB���и�ԭ
	if (RestoreDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܻ�ͼ��ߴ粻����Ҫ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
		
}

void CCarplateView::OnRestoreNoiseblur() 
{
	//ͼ��ģ������������һ������ԭ��ͼ��

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��ģ�������������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����NoiseBlurDIB()������DIB����ģ�����봦��
	if (NoiseBlurDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܻ�ͼ��ߴ粻����Ҫ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnRestoreWiener() 
{
	//ͼ��ά���˲���ԭ����

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�ĸ�ԭ�����������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����WienerDIB()������DIB���и�ԭ
	if (WienerDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܻ�ͼ��ߴ粻����Ҫ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
			
}

void CCarplateView::OnRestoreRandomnoise() 
{
	//ͼ������������ͼ���м����������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��ģ�������������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����RandomNoiseDIB()������DIB���м��봦��
	if (RandomNoiseDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();	
	
}

void CCarplateView::OnRestoreSaltnoise() 
{
	//ͼ������������ͼ���м��뽷������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��ģ�������������Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����SaltNoiseDIB()������DIB���м��봦��
	if (SaltNoiseDIB(lpDIBBits, ::DIBWidth(lpDIB), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();	
	
}


//////////////////////////////////////////////////////////////////////////////////////
//  ͼ�����
//
void CCarplateView::OnCodeHuffman() 
{
	// �鿴�����������
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��Դͼ�����ص�ָ��
	unsigned char *	lpSrc;
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// DIB�ĸ߶�
	LONG	lHeight;
	
	// DIB�Ŀ��
	LONG	lWidth;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ͼ����������
	LONG	lCountSum;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ��������Ҷ�ֵƵ�ʵ�����ָ��
	FLOAT * fFreq;
	
	// ��ȡ��ǰDIB��ɫ��Ŀ
	int		iColorNum;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ��ȡ��ǰDIB��ɫ��Ŀ
	iColorNum = ::DIBNumColors(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�������Ŀ������ƣ�
	if (iColorNum != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ���������룡", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	/******************************************************************************
	// ��ʼ��������Ҷȼ����ֵ�Ƶ��	
	//
	// �����Ҫ���������н��й��������룬ֻ��Ķ��˴����ɣ����磬ֱ�Ӹ�ֵ��
	   iColorNum = 8;
	   fFreq = new FLOAT[iColorNum];
	   fFreq[0] = 0.04;
	   fFreq[1] = 0.05;
	   fFreq[2] = 0.06;
	   fFreq[3] = 0.07;
	   fFreq[4] = 0.10;
	   fFreq[5] = 0.10;
	   fFreq[6] = 0.18;
	   fFreq[7] = 0.40;
	// �����Ϳ��Զ�ָ�������н��й���������
	******************************************************************************/
	
	// �����ڴ�
	fFreq = new FLOAT[iColorNum];
	
	// ����DIB���
	lWidth = ::DIBWidth(lpDIB);
	
	// ����DIB�߶�
	lHeight = ::DIBHeight(lpDIB);
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ���ü���Ϊ0
	for (i = 0; i < iColorNum; i ++)
	{
		// ����
		fFreq[i] = 0.0;
	}
	
	// ��������Ҷ�ֵ�ļ��������ڷ�256ɫλͼ���˴�������fFreq��ֵ��������ͬ��
	for (i = 0; i < lHeight; i ++)
	{
		for (j = 0; j < lWidth; j ++)
		{
			// ָ��ͼ��ָ��
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * i + j;
			
			// ������1
			fFreq[*(lpSrc)] += 1;
		}
	}
	
	// ����ͼ����������
	lCountSum = lHeight * lWidth;
	
	// ��������Ҷ�ֵ���ֵĸ���
	for (i = 0; i < iColorNum; i ++)
	{
		// �������
		fFreq[i] /= (FLOAT)lCountSum;
	}
	
	// ��������Ҷȼ����ֵ�Ƶ�ʽ���
	/*****************************************************************************/
	
	// �����Ի���
	CDlgHuffman dlgPara;
	
	// ��ʼ������ֵ
	dlgPara.m_fFreq = fFreq;
	dlgPara.m_iColorNum = iColorNum;
	
	// ��ʾ�Ի���
	dlgPara.DoModal();
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnCodeShannon() 
{
	// �鿴��ũ����ŵ�����
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��Դͼ�����ص�ָ��
	unsigned char *	lpSrc;
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// DIB�ĸ߶�
	LONG	lHeight;
	
	// DIB�Ŀ��
	LONG	lWidth;
	
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
	
	// ͼ����������
	LONG	lCountSum;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// ��������Ҷ�ֵƵ�ʵ�����ָ��
	FLOAT * fFreq;
	
	// ��ȡ��ǰDIB��ɫ��Ŀ
	int		iColorNum;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ��ȡ��ǰDIB��ɫ��Ŀ
	iColorNum = ::DIBNumColors(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ�������Ŀ������ƣ�
	if (iColorNum != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ��ũ����ŵ���룡", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	/******************************************************************************
	// ��ʼ��������Ҷȼ����ֵ�Ƶ��	
	//
	// �����Ҫ���������н�����ũ����ŵ���룬ֻ��Ķ��˴����ɣ����磬ֱ�Ӹ�ֵ��
	   iColorNum = 8;
	   fFreq = new FLOAT[iColorNum];
	   fFreq[0] = 0.0625;
	   fFreq[1] = 0.0625;
	   fFreq[2] = 0.0625;
	   fFreq[3] = 0.0625;
	   fFreq[4] = 0.125;
	   fFreq[5] = 0.125;
	   fFreq[6] = 0.25;
	   fFreq[7] = 0.25;
	// �����Ϳ��Զ�ָ�������н�����ũ����ŵ����
	******************************************************************************/
	
	// �����ڴ�
	fFreq = new FLOAT[iColorNum];
	
	// ����DIB���
	lWidth = ::DIBWidth(lpDIB);
	
	// ����DIB�߶�
	lHeight = ::DIBHeight(lpDIB);
	
	// ����ͼ��ÿ�е��ֽ���
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// ���ü���Ϊ0
	for (i = 0; i < iColorNum; i ++)
	{
		// ����
		fFreq[i] = 0.0;
	}
	
	// ��������Ҷ�ֵ�ļ��������ڷ�256ɫλͼ���˴�������fFreq��ֵ��������ͬ��
	for (i = 0; i < lHeight; i ++)
	{
		for (j = 0; j < lWidth; j ++)
		{
			// ָ��ͼ��ָ��
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * i + j;
			
			// ������1
			fFreq[*(lpSrc)] += 1;
		}
	}
	
	// ����ͼ����������
	lCountSum = lHeight * lWidth;
	
	// ��������Ҷ�ֵ���ֵĸ���
	for (i = 0; i < iColorNum; i ++)
	{
		// �������
		fFreq[i] /= (FLOAT)lCountSum;
	}
	
	// ��������Ҷȼ����ֵ�Ƶ�ʽ���
	/*****************************************************************************/
	
	// �����Ի���
	CDlgShannon dlgPara;
	
	// ��ʼ������ֵ
	dlgPara.m_fFreq = fFreq;
	dlgPara.m_iColorNum = iColorNum;
	
	// ��ʾ�Ի���
	dlgPara.DoModal();
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
	
}

void CCarplateView::OnCodeRLE() 
{
	// �Ե�ǰͼ������г̱��루��ΪPCX��ʽ�ļ���
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ���г̱��룩
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ���г̱��룡", "ϵͳ��ʾ" ,
			MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// �ļ�����·��
	CString strFilePath;
	
	// ��ʼ���ļ���Ϊԭʼ�ļ���
	strFilePath = pDoc->GetPathName();
	
	// ���ĺ�׺ΪPCX
	if (strFilePath.Right(4).CompareNoCase(".BMP") == 0)
	{
		// ���ĺ�׺ΪPCX
		strFilePath = strFilePath.Left(strFilePath.GetLength()-3) + "PCX";
	}
	else
	{
		// ֱ����Ӻ�׺PCX
		strFilePath += ".PCX";
	}
	
	// ����SaveAs�Ի���
	CFileDialog dlg(FALSE, "PCX", strFilePath, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		"PCXͼ���ļ� (*.PCX) | *.PCX|�����ļ� (*.*) | *.*||", NULL);
	
	// ��ʾ�û�ѡ�񱣴��·��
	if (dlg.DoModal() != IDOK)
	{
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// �ָ����
		EndWaitCursor();
		
		// ����
		return;
	}
	
	// ��ȡ�û�ָ�����ļ�·��
	strFilePath = dlg.GetPathName();
	
	// CFile��CFileException����
	CFile file;
	CFileException fe;
	
	// ���Դ���ָ����PCX�ļ�
	if (!file.Open(strFilePath, CFile::modeCreate |
	  CFile::modeReadWrite | CFile::shareExclusive, &fe))
	{
		// ��ʾ�û�
		MessageBox("��ָ��PCX�ļ�ʱʧ�ܣ�", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
		
		// ����
		return;
	}
	
	// ����DIBToPCX256()��������ǰ��DIB����Ϊ256ɫPCX�ļ�
	if (::DIBToPCX256(lpDIB, file))
	{
		// ��ʾ�û�
		MessageBox("�ɹ�����ΪPCX�ļ���", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("����ΪPCX�ļ�ʧ�ܣ�", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
	
	// �ָ����
	EndWaitCursor();
}

void CCarplateView::OnCodeIRLE() 
{
	// ����256ɫPCX�ļ�
	
	// �ļ�·��
	CString strFilePath;
	
	// ����Open�Ի���
	CFileDialog dlg(TRUE, "PCX", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		"PCXͼ���ļ� (*.PCX) | *.PCX|�����ļ� (*.*) | *.*||", NULL);
	
	// ��ʾ�û�ѡ�񱣴��·��
	if (dlg.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û�ָ�����ļ�·��
	strFilePath = dlg.GetPathName();
	
	// CFile��CFileException����
	CFile file;
	CFileException fe;
	
	// ���Դ�ָ����PCX�ļ�
	if (!file.Open(strFilePath, CFile::modeRead | CFile::shareDenyWrite, &fe))
	{
		// ��ʾ�û�
		MessageBox("��ָ��PCX�ļ�ʱʧ�ܣ�", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
		
		// ����
		return;
	}
	
	// ����ReadPCX256()������ȡָ����256ɫPCX�ļ�
	HDIB hDIB = ::ReadPCX256(file);
	
	if (hDIB != NULL)
	{
		// ��ʾ�û�
		//MessageBox("�ɹ���ȡPCX�ļ���", "ϵͳ��ʾ" , 
		//	MB_ICONINFORMATION | MB_OK);
		
		// ��ȡ�ĵ�
		CCarplateDoc* pDoc = GetDocument();
		
		// �滻DIB��ͬʱ�ͷž�DIB����
		pDoc->ReplaceHDIB(hDIB);
		
		// ����DIB��С�͵�ɫ��
		pDoc->InitDIBData();
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);
		
		// �������ù�����ͼ��С
		SetScrollSizes(MM_TEXT, pDoc->GetDocSize());
		
		// ʵ���µĵ�ɫ��
		OnDoRealize((WPARAM)m_hWnd,0);
		
		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("��ȡPCX�ļ�ʧ�ܣ�", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
	}
	
}

void CCarplateView::OnCodeLzw() 
{
	// �Ե�ǰͼ�����GIF-LZW���루��ΪGIF��ʽ�ļ���
	
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	
	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// �ж��Ƿ񳬹�256ɫ
	if (::DIBNumColors(lpDIB) > 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��< 256ɫλͼ��GIF-LZW���룡", "ϵͳ��ʾ" ,
			MB_ICONINFORMATION | MB_OK);
		
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// �ļ�����·��
	CString strFilePath;
	
	// ָ���Ƿ��Խ���ʽ����GIF�ļ�
	BOOL	bInterlace;
	
	// ��ʼ���ļ���Ϊԭʼ�ļ���
	strFilePath = pDoc->GetPathName();
	
	// ���ĺ�׺ΪGIF
	if (strFilePath.Right(4).CompareNoCase(".BMP") == 0)
	{
		// ���ĺ�׺ΪGIF
		strFilePath = strFilePath.Left(strFilePath.GetLength()-3) + "GIF";
	}
	else
	{
		// ֱ����Ӻ�׺GIF
		strFilePath += ".GIF";
	}
	
	// ����SaveAs�Ի���
	CDlgCodeGIF dlg;
	
	dlg.m_strFilePath = strFilePath;
	dlg.m_bInterlace = FALSE;
	
	// ��ʾ�û�ѡ�񱣴��·��
	if (dlg.DoModal() != IDOK)
	{
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// �ָ����
		EndWaitCursor();
		
		// ����
		return;
	}
	
	// ��ȡ�û�ָ�����ļ�·��
	strFilePath = dlg.m_strFilePath;
	bInterlace = dlg.m_bInterlace;
	
	// CFile��CFileException����
	CFile file;
	CFileException fe;
	
	// ���Դ���ָ����GIF�ļ�
	if (!file.Open(strFilePath, CFile::modeCreate |
	  CFile::modeReadWrite | CFile::shareExclusive, &fe))
	{
		// ��ʾ�û�
		MessageBox("��ָ��GIF�ļ�ʱʧ�ܣ�", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
		
		// ����
		return;
	}
	
	// ����DIBToGIF()��������ǰ��DIB����ΪGIF�ļ�
	if (::DIBToGIF(lpDIB, file, bInterlace))
	{
		// ��ʾ�û�
		MessageBox("�ɹ�����ΪGIF�ļ���", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("����ΪGIF�ļ�ʧ�ܣ�", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
	
	// �ָ����
	EndWaitCursor();
}

void CCarplateView::OnCodeIlzw() 
{
	// ����GIF�ļ�
	
	// �ļ�·��
	CString strFilePath;
	
	// ����Open�Ի���
	CFileDialog dlg(TRUE, "GIF", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		"GIFͼ���ļ� (*.GIF) | *.GIF|�����ļ� (*.*) | *.*||", NULL);
	
	// ��ʾ�û�ѡ�񱣴��·��
	if (dlg.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û�ָ�����ļ�·��
	strFilePath = dlg.GetPathName();
	
	// CFile��CFileException����
	CFile file;
	CFileException fe;
	
	// ���Դ�ָ����GIF�ļ�
	if (!file.Open(strFilePath, CFile::modeRead | CFile::shareDenyWrite, &fe))
	{
		// ��ʾ�û�
		MessageBox("��ָ��GIF�ļ�ʱʧ�ܣ�", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
		
		// ����
		return;
	}
	
	// ����ReadGIF()������ȡָ����GIF�ļ�
	HDIB hDIB = ::ReadGIF(file);
	
	if (hDIB != NULL)
	{
		// ��ʾ�û�
		//MessageBox("�ɹ���ȡGIF�ļ���", "ϵͳ��ʾ" , 
		//	MB_ICONINFORMATION | MB_OK);
		
		// ��ȡ�ĵ�
		CCarplateDoc* pDoc = GetDocument();
		
		// �滻DIB��ͬʱ�ͷž�DIB����
		pDoc->ReplaceHDIB(hDIB);
		
		// ����DIB��С�͵�ɫ��
		pDoc->InitDIBData();
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);
		
		// �������ù�����ͼ��С
		SetScrollSizes(MM_TEXT, pDoc->GetDocSize());
		
		// ʵ���µĵ�ɫ��
		OnDoRealize((WPARAM)m_hWnd,0);
		
		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("��ȡGIF�ļ�ʧ�ܣ�", "ϵͳ��ʾ" , 
			MB_ICONINFORMATION | MB_OK);
	}
	
}

void CCarplateView::OnCodeJEPG() 
{
	// TODO: Add your command handler code here
	
}

void CCarplateView::OnCodeIJEPG() 
{
	// TODO: Add your command handler code here
	
}


void CCarplateView::OnEdgeFill2() 
{
	//�����������

	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	
	// ָ��DIB��ָ��
	LPSTR	lpDIB;

	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	
	// �ж��Ƿ���8-bppλͼ������Ϊ�˷��㣬ֻ����8-bppλͼ��������䣬�����Ŀ������ƣ�
	if (::DIBNumColors(lpDIB) != 256)
	{
		// ��ʾ�û�
		MessageBox("Ŀǰֻ֧��256ɫλͼ�����㣡", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		
		// ����
		return;
	}
	
	// ���Ĺ����״
	BeginWaitCursor();

	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = ::FindDIBBits(lpDIB);
	
	// ����FillDIB()������DIB�����������
	if (Fill2DIB(lpDIBBits, WIDTHBYTES(::DIBWidth(lpDIB) * 8), ::DIBHeight(lpDIB)))
	{
		
		// ��������
		pDoc->SetModifiedFlag(TRUE);

		// ������ͼ
		pDoc->UpdateAllViews(NULL);
	}
	else
	{
		// ��ʾ�û�
		MessageBox("�����ڴ�ʧ�ܣ�", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
	}
	
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());

	// �ָ����
	EndWaitCursor();
		
}

void CCarplateView::OnCarplateInvariant() 
{
	int white=255;
	// ��ȡ�ĵ�
	CCarplateDoc* pDoc = GetDocument();
	// ָ��DIB��ָ��
	LPSTR	lpDIB;
	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHDIB());
	// ��ɫ���е���ɫ��Ŀ
	WORD wNumColors;
	// ��ȡDIB����ɫ���е���ɫ��Ŀ
	wNumColors = ::DIBNumColors(lpDIB);
	// �ж��Ƿ���8-bppλͼ
	if (wNumColors != 256)
	{
		// ��ʾ�û�
		MessageBox("��256ɫλͼ��", "ϵͳ��ʾ" , MB_ICONINFORMATION | MB_OK);
		// �������
		::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
		// ����
		return;
	}
	// ���Ĺ����״
	BeginWaitCursor();
	// ָ��DIB����ָ��
	LPSTR   lpDIBBits;
	// ָ��DIB���ص�ָ��
	BYTE *	lpSrc;
	// ѭ������
	LONG	i;
	LONG	j;
	// ͼ����
	LONG	lWidth;
	// ͼ��߶�
	LONG	lHeight;
	// ͼ��ÿ�е��ֽ���
	LONG	lLineBytes;
// ָ��BITMAPINFO�ṹ��ָ�루Win3.0��
	LPBITMAPINFO lpbmi;
	// ��ȡָ��BITMAPINFO�ṹ��ָ�루Win3.0��
	lpbmi = (LPBITMAPINFO)lpDIB;
	

	for (i = 0; i < 256; i ++)
{
   
	  if (lpbmi->bmiColors[i].rgbBlue==lpbmi->bmiColors[i].rgbGreen&&lpbmi->bmiColors[i].rgbGreen==lpbmi->bmiColors[i].rgbRed)
	     {
              
			            lpbmi->bmiColors[i].rgbRed = white;
                        lpbmi->bmiColors[i].rgbGreen = white;		
                        lpbmi->bmiColors[i].rgbBlue =white;
                        lpbmi->bmiColors[i].rgbReserved = 0;
	     }
    else
	   {
		double inva=abs(atan(sqrt(3)*(lpbmi->bmiColors[i].rgbGreen-lpbmi->bmiColors[i].rgbBlue)/((lpbmi->bmiColors[i].rgbRed-lpbmi->bmiColors[i].rgbGreen)+(lpbmi->bmiColors[i].rgbRed-lpbmi->bmiColors[i].rgbBlue))));
     if ((inva>=0.710&&inva<=1.50)||(inva>=0.23&&inva<=0.53)||(inva==0))
		   {}
else
		   {
		
			            lpbmi->bmiColors[i].rgbRed = white;
                        lpbmi->bmiColors[i].rgbGreen = white;		
                        lpbmi->bmiColors[i].rgbBlue = white;
                        lpbmi->bmiColors[i].rgbReserved = 0;
		   }
	}
	}
int num,o;
lpDIBBits=::FindDIBBits(lpDIB);
lWidth=::DIBWidth(lpDIB);
lHeight=::DIBHeight(lpDIB);
lLineBytes=WIDTHBYTES(lWidth*8);
for (i=0;i<lHeight;i++)
{
    num=0;
	for (j=0;j<lWidth;j++)
    {
      lpSrc=(BYTE*)lpDIBBits+lLineBytes*(lHeight-1-i)+j;
	  if (lpbmi->bmiColors[*lpSrc].rgbRed!=255&&lpbmi->bmiColors[*lpSrc].rgbGreen!=255&&	lpbmi->bmiColors[*lpSrc].rgbBlue!=255)
	     num=num+1;
	  else 
	     o=*lpSrc;
	}
      if(num<155)
      {
	   for(j=0;j<lWidth;j++)
	   {
	      lpSrc=(BYTE*)lpDIBBits+lLineBytes*(lHeight-1-i)+j;
	      *lpSrc=o;
	   }
      }
	
}	
	pDoc->SetModifiedFlag(TRUE);
	// ������ͼ
	pDoc->UpdateAllViews(NULL);
	// �������
	::GlobalUnlock((HGLOBAL) pDoc->GetHDIB());
// �ָ����
	EndWaitCursor();	
	
}
