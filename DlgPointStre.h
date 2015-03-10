#if !defined(AFX_DLGPOINTSTRE_H__45B95585_372F_4C49_8928_99D343D2DE00__INCLUDED_)
#define AFX_DLGPOINTSTRE_H__45B95585_372F_4C49_8928_99D343D2DE00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPointStre.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPointStre dialog

class CDlgPointStre : public CDialog
{
// Construction
public:
	
	// ��ǰ����϶�״̬��0��ʾδ�϶���1��ʾ�����϶���һ�㣬2��ʾ�����϶��ڶ��㡣
	int		m_iIsDraging;
	
	// ��Ӧ����¼��ľ�������
	CRect	m_MouseRect;
	
	// ��ʶ�Ƿ��Ѿ�������Ƥ����
	BOOL	m_bDrawed;
	
	// ��������������ʱ��λ��
	CPoint	m_p1;
	
	// ��������϶�ʱ��λ��
	CPoint	m_p2;
	
	CDlgPointStre(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPointStre)
	enum { IDD = IDD_DLG_PointStre };
	
	// ����ת�۵�����
	BYTE	m_bX1;
	BYTE	m_bY1;
	BYTE	m_bX2;
	BYTE	m_bY2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPointStre)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPointStre)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnKillfocusEditX1();
	afx_msg void OnKillfocusEditX2();
	afx_msg void OnKillfocusEditY1();
	afx_msg void OnKillfocusEditY2();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPOINTSTRE_H__45B95585_372F_4C49_8928_99D343D2DE00__INCLUDED_)
