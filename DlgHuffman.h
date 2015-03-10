#if !defined(AFX_DLGHUFFMAN_H__9BC92A31_5B8E_4A6D_B315_EE5ED22A2147__INCLUDED_)
#define AFX_DLGHUFFMAN_H__9BC92A31_5B8E_4A6D_B315_EE5ED22A2147__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHuffman.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHuffman dialog

class CDlgHuffman : public CDialog
{
// Construction
public:
	
	// �Ҷȼ�����Ŀ
	int m_iColorNum;
	
	// �����Ҷ�ֵ����Ƶ��
	FLOAT *	m_fFreq;
	
	// �����������
	CString	* m_strCode;
	
	CDlgHuffman(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgHuffman)
	enum { IDD = IDD_DLG_Huffman };
	CListCtrl	m_lstTable;
	double	m_dEntropy;
	double	m_dAvgCodeLen;
	double	m_dEfficiency;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHuffman)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHuffman)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHUFFMAN_H__9BC92A31_5B8E_4A6D_B315_EE5ED22A2147__INCLUDED_)
