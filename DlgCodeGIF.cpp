// DlgCodeGIF.cpp : implementation file

#include "stdafx.h"
#include "carplate.h"
#include "DlgCodeGIF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCodeGIF dialog


CDlgCodeGIF::CDlgCodeGIF(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCodeGIF::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCodeGIF)
	m_strFilePath = _T("");
	m_bInterlace = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgCodeGIF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCodeGIF)
	DDX_Text(pDX, IDC_EDIT_FileName, m_strFilePath);
	DDX_Radio(pDX, IDC_RADIO1, m_bInterlace);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCodeGIF, CDialog)
	//{{AFX_MSG_MAP(CDlgCodeGIF)
	ON_BN_CLICKED(IDC_btnSaveAs, OnbtnSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCodeGIF message handlers

void CDlgCodeGIF::OnbtnSaveAs() 
{
	// ��ʾѡ�񱣴��ļ�·��
	
	CFileDialog dlg(FALSE, "GIF", m_strFilePath, OFN_HIDEREADONLY, 
		"GIFͼ���ļ� (*.GIF) | *.GIF|�����ļ� (*.*) | *.*||", NULL);
	
	// ��ʾ�û�ѡ�񱣴��·��
	if (dlg.DoModal() != IDOK)
	{
		// ����
		return;
	}
	
	// ��ȡ�û�ָ�����ļ�·��
	m_strFilePath = dlg.GetPathName();
	
	// ����
	UpdateData(FALSE);
	
}

void CDlgCodeGIF::OnOK() 
{
	CFileFind fFind;
	
	// ����
	UpdateData(TRUE);
	
	// �ж��û�ָ�����ļ��Ƿ����
	if (fFind.FindFile(m_strFilePath, 0) != 0)
	{
		// ѯ���û��Ƿ񸲸�
		if (MessageBox("ָ�����ļ��Ѿ����ڣ��Ƿ񸲸ǣ�", "ϵͳ��ʾ", 
			MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON2) != IDYES)
		{
			// �˳�
			return;
		}
	}
	
	// ����Ĭ�ϵ�OnOK�¼�
	CDialog::OnOK();
}
