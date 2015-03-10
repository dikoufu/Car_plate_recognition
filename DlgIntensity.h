#if !defined(AFX_DLGINTENSITY_H__504BB8CE_7CF6_4D13_B5B7_DCC1BC84FEA5__INCLUDED_)
#define AFX_DLGINTENSITY_H__504BB8CE_7CF6_4D13_B5B7_DCC1BC84FEA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIntensity.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIntensity dialog

class CDlgIntensity : public CDialog
{
// Construction
public:
	
	// ��ǰ����϶�״̬��0��ʾδ�϶���1��ʾ�����϶����ޣ�2��ʾ�����϶����ޡ�
	int		m_iIsDraging;
	
	// ��Ӧ����¼��ľ�������
	CRect	m_MouseRect;
	
	// DIB�ĸ߶�
	LONG	m_lHeight;
	
	// DIB�Ŀ��
	LONG	m_lWidth;
	
	// ָ��ǰDIB���ص�ָ��
	char *	m_lpDIBBits;
	
	// �����Ҷ�ֵ�ļ���
	LONG	m_lCount[256];
	
	CDlgIntensity(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgIntensity)
	enum { IDD = IDD_DLG_Intensity };
	
	// ��ʾ�Ҷ����������
	int		m_iLowGray;
	
	// ��ʾ�Ҷ����������
	int		m_iUpGray;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIntensity)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIntensity)
	afx_msg void OnPaint();
	afx_msg void OnKillfocusEDITLowGray();
	afx_msg void OnKillfocusEDITUpGray();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINTENSITY_H__504BB8CE_7CF6_4D13_B5B7_DCC1BC84FEA5__INCLUDED_)
