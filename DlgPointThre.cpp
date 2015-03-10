// DlgPointThre.cpp : implementation file

#include "stdafx.h"
#include "carplate.h"
#include "DlgPointThre.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgPointThre dialog


CDlgPointThre::CDlgPointThre(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPointThre::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgPointThre)
	m_bThre = 0;
	//}}AFX_DATA_INIT
}


void CDlgPointThre::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgPointThre)
	DDX_Text(pDX, IDC_EDIT_Thre, m_bThre);
	DDV_MinMaxByte(pDX, m_bThre, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPointThre, CDialog)
	//{{AFX_MSG_MAP(DlgPointThre)
	ON_EN_KILLFOCUS(IDC_EDIT_Thre, OnKillfocusEDITThre)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPointThre message handlers

BOOL CDlgPointThre::OnInitDialog() 
{
	
	// ����Ĭ��OnInitDialog����
	CDialog::OnInitDialog();
	
	// ��ȡ����ֱ��ͼ�ı�ǩ
	CWnd* pWnd = GetDlgItem(IDC_COORD);
	
	// �����������¼�����Ч����
	pWnd->GetClientRect(m_MouseRect);
	pWnd->ClientToScreen(&m_MouseRect);
	
	CRect rect;
	GetClientRect(rect);
	ClientToScreen(&rect);
	
	m_MouseRect.top -= rect.top;
	m_MouseRect.left -= rect.left;
	
	// ���ý�������¼�����Ч����
	m_MouseRect.top += 25;
	m_MouseRect.left += 10;
	m_MouseRect.bottom = m_MouseRect.top + 255;
	m_MouseRect.right = m_MouseRect.left + 256;
	
	// ��ʼ���϶�״̬
	m_bIsDraging = FALSE;
	
	// ����TRUE
	return TRUE;
}

void CDlgPointThre::OnKillfocusEDITThre() 
{
	// ����
	UpdateData(TRUE);
	
	// �ػ�
	InvalidateRect(m_MouseRect, TRUE);
}

void CDlgPointThre::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// ���û�������������ʼ�϶�
	
	// �ж��Ƿ�����Ч������
	if(m_MouseRect.PtInRect(point))
	{
		if (point.x == (m_MouseRect.left + m_bThre))
		{
			
			// �����϶�״̬
			m_bIsDraging = TRUE;
			
			// ���Ĺ��
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}
	
	// Ĭ�ϵ��������������¼�
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgPointThre::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// ���û��ͷ�������ֹͣ�϶�
	if (m_bIsDraging)
	{
		// �����϶�״̬
		m_bIsDraging = FALSE;
	}
	
	// Ĭ���ͷ������������¼�
	CDialog::OnLButtonUp(nFlags, point);
}

void CDlgPointThre::OnMouseMove(UINT nFlags, CPoint point) 
{
	// �жϵ�ǰ����Ƿ��ڻ�������
	if(m_MouseRect.PtInRect(point))
	{
		// �ж��Ƿ������϶�
		if (m_bIsDraging)
		{
			// ������ֵ
			m_bThre = (BYTE) (point.x - m_MouseRect.left);
			
			// ���Ĺ��
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
			
			// ����
			UpdateData(FALSE);
			
			// �ػ�
			InvalidateRect(m_MouseRect, TRUE);
		}
		else if (point.x == (m_MouseRect.left + m_bThre))
		{
			// ���Ĺ��
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}
	
	// Ĭ������ƶ������¼�
	CDialog::OnMouseMove(nFlags, point);
}

void CDlgPointThre::OnPaint() 
{
	// �ַ���
	CString str;
	
	// �豸������
	CPaintDC dc(this);
	
	// ��ȡ����������ı���
	CWnd* pWnd = GetDlgItem(IDC_COORD);
	
	// ָ��
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	
	pDC->Rectangle(0,0,330,300);
	
	// �������ʶ���
	CPen* pPenRed = new CPen;
	
	// ��ɫ����
	pPenRed->CreatePen(PS_SOLID,2,RGB(255,0,0));
	
	// �������ʶ���
	CPen* pPenBlue = new CPen;
	
	// ��ɫ����
	pPenBlue->CreatePen(PS_SOLID,2,RGB(0,0, 255));
	
	// �������ʶ���
	CPen* pPenGreen = new CPen;
	
	// ��ɫ����
	pPenGreen->CreatePen(PS_DOT,1,RGB(0,255,0));
	
	// ѡ�е�ǰ��ɫ���ʣ���������ǰ�Ļ���
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);
	
	// ����������
	pDC->MoveTo(10,10);
	
	// ��ֱ��
	pDC->LineTo(10,280);
	
	// ˮƽ��
	pDC->LineTo(320,280);
	
	// д����
	str.Format("0");
	pDC->TextOut(10, 281, str);
	
	str.Format("255");
	pDC->TextOut(265, 281, str);
	pDC->TextOut(11, 25, str);
	
	// ����X���ͷ
	pDC->LineTo(315,275);
	pDC->MoveTo(320,280);
	pDC->LineTo(315,285);
	
	// ����X���ͷ
	pDC->MoveTo(10,10);
	pDC->LineTo(5,15);
	pDC->MoveTo(10,10);
	pDC->LineTo(15,15);
	
	// ���ĳ���ɫ����
	pDC->SelectObject(pPenGreen);	
	
	// ���ƴ�����ֵ��
	pDC->MoveTo(m_bThre + 10, 25);
	pDC->LineTo(m_bThre + 10, 280);
	
	// ���ĳ���ɫ����
	pDC->SelectObject(pPenBlue);	
	
	// ��������ֵ
	str.Format("%d", m_bThre);
	pDC->TextOut(m_bThre + 10, 281, str);
	
	// �����û�ָ���Ĵ��ڣ�ע��ת������ϵ��
	pDC->MoveTo(10, 280);
	pDC->LineTo(m_bThre + 10, 280);
	pDC->LineTo(m_bThre + 10, 25);
	pDC->LineTo(265, 25);
	
	// �ָ���ǰ�Ļ���
	pDC->SelectObject(pOldPen);	
	
	// ���Ʊ�Ե
	pDC->MoveTo(10,25);
	pDC->LineTo(265,25);
	pDC->LineTo(265,280);
	
	// ɾ���µĻ���
	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;
}
