// carplateDoc.cpp : implementation of the CCarplateDoc class

#include "stdafx.h"
#include "carplate.h"

#include "carplateDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCarplateDoc

IMPLEMENT_DYNCREATE(CCarplateDoc, CDocument)

BEGIN_MESSAGE_MAP(CCarplateDoc, CDocument)
	//{{AFX_MSG_MAP(CCarplateDoc)
	ON_COMMAND(ID_FILE_REOPEN, OnFileReopen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCarplateDoc construction/destruction

CCarplateDoc::CCarplateDoc()
{
	// Ĭ�ϱ���ɫ����ɫ
	m_refColorBKG = 0x00808080;	
	
	// ��ʼ������
	m_hDIB = NULL;
	m_palDIB = NULL;
	m_sizeDoc = CSize(1,1);
}

CCarplateDoc::~CCarplateDoc()
{
	// �ж�DIB�����Ƿ����
	if (m_hDIB != NULL)
	{
		// ���DIB����
		::GlobalFree((HGLOBAL) m_hDIB);
	}
	
	// �жϵ�ɫ���Ƿ����
	if (m_palDIB != NULL)
	{
		// �����ɫ��
		delete m_palDIB;
	}
}

BOOL CCarplateDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCarplateDoc diagnostics

#ifdef _DEBUG
void CCarplateDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCarplateDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCarplateDoc commands

BOOL CCarplateDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDocument::CanCloseFrame(pFrame);
}

void CCarplateDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CDocument::DeleteContents();
}

BOOL CCarplateDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	CFile file;
	CFileException fe;

	// ���ļ�
	if (!file.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))
	{
		// ʧ��
		ReportSaveLoadException(lpszPathName, &fe,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		
		// ����FALSE
		return FALSE;
	}
	
	DeleteContents();
	
	// ���Ĺ����״
	BeginWaitCursor();
	
	// ���Ե���ReadDIBFile()��ȡͼ��
	TRY
	{
		m_hDIB = ::ReadDIBFile(file);
	}
	CATCH (CFileException, eLoad)
	{
		// ��ȡʧ��
		file.Abort();
		
		// �ָ������״
		EndWaitCursor();
		
		// ����ʧ��
		ReportSaveLoadException(lpszPathName, eLoad,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		
		// ����DIBΪ��
		m_hDIB = NULL;
		
		// ����FALSE
		return FALSE;
	}
	END_CATCH
	
	// ��ʼ��DIB
	InitDIBData();
	
	// �ָ������״
	EndWaitCursor();
	
	// �ж϶�ȡ�ļ��Ƿ�ɹ�
	if (m_hDIB == NULL)
	{
		// ʧ�ܣ����ܷ�BMP��ʽ
		CString strMsg;
		strMsg = "��ȡͼ��ʱ���������ǲ�֧�ָ����͵�ͼ���ļ���";
		
		// ��ʾ����
		MessageBox(NULL, strMsg, "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		
		// ����FALSE
		return FALSE;
	}
	
	// �����ļ�����
	SetPathName(lpszPathName);
	
	// ��ʼ���ͱ��ΪFALSE
	SetModifiedFlag(FALSE);
	
	// ����TRUE
	return TRUE;
}

void CCarplateDoc::OnFileReopen() 
{
 	// ���´�ͼ�񣬷��������޸�
 
	// �жϵ�ǰͼ���Ƿ��Ѿ����Ķ�
	if (IsModified())
	{
		// ��ʾ�û��ò�������ʧ���е�ǰ���޸�
		if (MessageBox(NULL, "���´�ͼ�񽫶�ʧ���иĶ����Ƿ������", "ϵͳ��ʾ", MB_ICONQUESTION | MB_YESNO) == IDNO)
		{
			// �û�ȡ��������ֱ�ӷ���
			return;
		}
	}
	
	CFile file;
 	CFileException fe;
 
 	CString strPathName;
  	
	// ��ȡ��ǰ�ļ�·��
 	strPathName = GetPathName();
 
 	// ���´��ļ�
 	if (!file.Open(strPathName, CFile::modeRead | CFile::shareDenyWrite, &fe))
 	{
 		// ʧ��
 		ReportSaveLoadException(strPathName, &fe,
 			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
 		
 		// ����
 		return;
 	}
 	
 	// ���Ĺ����״
 	BeginWaitCursor();
 	
 	// ���Ե���ReadDIBFile()��ȡͼ��
 	TRY
 	{
 		m_hDIB = ::ReadDIBFile(file);
 	}
 	CATCH (CFileException, eLoad)
 	{
 		// ��ȡʧ��
 		file.Abort();
 		
 		// �ָ������״
 		EndWaitCursor();
 		
 		// ����ʧ��
 		ReportSaveLoadException(strPathName, eLoad,
 			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
 		
 		// ����DIBΪ��
 		m_hDIB = NULL;
 		
 		// ����
 		return;
 	}
 	END_CATCH
 	
 	// ��ʼ��DIB
 	InitDIBData();
 	
 	// �ж϶�ȡ�ļ��Ƿ�ɹ�
 	if (m_hDIB == NULL)
 	{
 		// ʧ�ܣ����ܷ�BMP��ʽ
 		CString strMsg;
 		strMsg = "��ȡͼ��ʱ���������ǲ�֧�ָ����͵�ͼ���ļ���";
 		
 		// ��ʾ����
 		MessageBox(NULL, strMsg, "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
  		
 		// �ָ������״
 		EndWaitCursor();
 		
 		// ����
 		return;
 	}
 	
 	// ��ʼ���ͱ��ΪFALSE
 	SetModifiedFlag(FALSE);
 	
 	// ˢ��
 	UpdateAllViews(NULL);
  	
 	// �ָ������״
 	EndWaitCursor();
	
 	// ����
 	return;
 	
}

BOOL CCarplateDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	CFile file;
	CFileException fe;

	// ���ļ�
	if (!file.Open(lpszPathName, CFile::modeCreate |
	  CFile::modeReadWrite | CFile::shareExclusive, &fe))
	{
		// ʧ��
		ReportSaveLoadException(lpszPathName, &fe,
			TRUE, AFX_IDP_INVALID_FILENAME);
		
		// ����FALSE
		return FALSE;
	}

	// ���Ե���SaveDIB����ͼ��
	BOOL bSuccess = FALSE;
	TRY
	{
		
		// ���Ĺ����״
		BeginWaitCursor();

		// ���Ա���ͼ��
		bSuccess = ::SaveDIB(m_hDIB, file);

		// �ر��ļ�
		file.Close();
	}
	CATCH (CException, eSave)
	{
		// ʧ��
		file.Abort();
		
		// �ָ������״
		EndWaitCursor();
		ReportSaveLoadException(lpszPathName, eSave,
			TRUE, AFX_IDP_FAILED_TO_SAVE_DOC);
		
		// ����FALSE
		return FALSE;
	}
	END_CATCH

	// �ָ������״
	EndWaitCursor();
	
	// �����ͱ��ΪFALSE
	SetModifiedFlag(FALSE);

	if (!bSuccess)
	{
		// ����ʧ�ܣ�������������ʽ��DIB�����Զ�ȡ���ǲ��ܱ���
		// ������SaveDIB��������

		CString strMsg;
		strMsg = "�޷�����BMPͼ��";
		
		// ��ʾ����
		MessageBox(NULL, strMsg, "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
	}
	
	return bSuccess;
}

void CCarplateDoc::ReplaceHDIB(HDIB hDIB)
{
	// �滻DIB���ڹ���ճ�����õ��ú���
	
	// �ж�DIB�Ƿ�Ϊ��
	if (m_hDIB != NULL)
	{
		// �ǿգ������
		::GlobalFree((HGLOBAL) m_hDIB);
	}

	// �滻���µ�DIB����
	m_hDIB = hDIB;
	
}

void CCarplateDoc::InitDIBData()
{
	// ��ʼ��DIB����

	// �жϵ�ɫ���Ƿ�Ϊ��
	if (m_palDIB != NULL)
	{
		// ɾ����ɫ�����
		delete m_palDIB;

		// ���õ�ɫ��Ϊ��
		m_palDIB = NULL;
	}
	
	// ���DIB����Ϊ�գ�ֱ�ӷ���
	if (m_hDIB == NULL)
	{
		// ����
		return;
	}
	
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);
	
	// �ж�ͼ���Ƿ����
	if (::DIBWidth(lpDIB) > INT_MAX ||::DIBHeight(lpDIB) > INT_MAX)
	{
		::GlobalUnlock((HGLOBAL) m_hDIB);
		
		// �ͷ�DIB����
		::GlobalFree((HGLOBAL) m_hDIB);
		
		// ����DIBΪ��
		m_hDIB = NULL;
		
		CString strMsg;
		strMsg = "BMPͼ��̫��";
		
		// ��ʾ�û�
		MessageBox(NULL, strMsg, "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);
		
		// ����
		return;
	}
	
	// �����ĵ���С
	m_sizeDoc = CSize((int) ::DIBWidth(lpDIB), (int) ::DIBHeight(lpDIB));
	
	::GlobalUnlock((HGLOBAL) m_hDIB);
	
	// �����µ�ɫ��
	m_palDIB = new CPalette;
	
	// �ж��Ƿ񴴽��ɹ�
	if (m_palDIB == NULL)
	{
		// ʧ�ܣ��������ڴ治��
		::GlobalFree((HGLOBAL) m_hDIB);
		
		// ����DIB����Ϊ��
		m_hDIB = NULL;
		
		// ����
		return;
	}
	
	// ����CreateDIBPalette��������ɫ��
	if (::CreateDIBPalette(m_hDIB, m_palDIB) == NULL)
	{
		// ���ؿգ����ܸ�DIB����û�е�ɫ��
		
		// ɾ��
		delete m_palDIB;
		
		// ����Ϊ��
		m_palDIB = NULL;
		
		// ����
		return;
	}
}


