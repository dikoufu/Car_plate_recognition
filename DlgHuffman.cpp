// DlgHuffman.cpp : implementation file

#include "stdafx.h"
#include "carplate.h"
#include "DlgHuffman.h"
#include "DIBAPI.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHuffman dialog


CDlgHuffman::CDlgHuffman(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHuffman::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHuffman)
	m_dEntropy = 0.0;
	m_dAvgCodeLen = 0.0;
	m_dEfficiency = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgHuffman::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHuffman)
	DDX_Control(pDX, IDC_LST_Table, m_lstTable);
	DDX_Text(pDX, IDC_EDIT1, m_dEntropy);
	DDX_Text(pDX, IDC_EDIT2, m_dAvgCodeLen);
	DDX_Text(pDX, IDC_EDIT3, m_dEfficiency);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHuffman, CDialog)
	//{{AFX_MSG_MAP(CDlgHuffman)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHuffman message handlers

BOOL CDlgHuffman::OnInitDialog() 
{
	
	// �ַ�������
	CString	str;
	
	// ѭ������
	LONG	i;
	LONG	j;
	LONG	k;
	
	// �м����
	FLOAT	fT;
	
	// ListCtrl��ITEM
	LV_ITEM lvitem;
	
	// �м����������ListCtrl����ӵ�ITEM���
	int		iActualItem;
	
	// ����Ĭ�ϵ�OnInitDialog()����
	CDialog::OnInitDialog();
	
	// ��ʼ������
	m_dEntropy = 0.0;
	m_dAvgCodeLen = 0.0;
	
	// ����ͼ����
	for (i = 0; i < m_iColorNum; i ++)
	{
		// �жϸ����Ƿ����0
		if (m_fFreq[i] > 0)
		{
			// ����ͼ����
			m_dEntropy -= m_fFreq[i] * log(m_fFreq[i]) / log(2.0);
		}
	}
	
	// ��������м���������
	FLOAT *	fTemp;
	
	// ����ӳ���ϵ������
	int	*	iMap;
	
	// �����ڴ�
	fTemp = new FLOAT[m_iColorNum];
	iMap  = new int[m_iColorNum];
	m_strCode = new CString[m_iColorNum];
	
	// ��ʼ��fTempΪm_fFreq
	for (i = 0; i < m_iColorNum; i ++)
	{
		// ��ֵ
		fTemp[i] = m_fFreq[i];
		iMap[i] = i;
	}
	
	// ��ð�ݷ��Խ��лҶ�ֵ���ֵĸ������򣬽������������fTemp��
	for (j = 0; j < m_iColorNum - 1; j ++)
	{
		for (i = 0; i < m_iColorNum - j - 1; i ++)
		{
			if (fTemp[i] > fTemp[i + 1])
			{
				// ����
				fT = fTemp[i];
				fTemp[i] = fTemp[i + 1];
				fTemp[i + 1] = fT;
				
				// ����ӳ���ϵ
				for (k = 0; k < m_iColorNum; k ++)
				{
					// �ж��Ƿ���fTemp[i]���ӽڵ�
					if (iMap[k] == i)
					{
						// �ı�ӳ�䵽�ڵ�i+1
						iMap[k] = i + 1;
					}
					else if (iMap[k] == i + 1)
					{
						// �ı�ӳ�䵽�ڵ�i
						iMap[k] = i;
					}
				}
			}
		}
	}
	
	//////////////////////////////////////////////////////////
	// ��������������
	
	// �ҵ����ʴ���0���ſ�ʼ����
	for (i = 0; i < m_iColorNum - 1; i ++)
	{
		// �жϸ����Ƿ����0
		if (fTemp[i] > 0)
		{
			break;
		}
	}
	
	// ��ʼ����
	for (; i < m_iColorNum - 1; i ++)
	{
		// ����m_strCode
		for (k = 0; k < m_iColorNum; k ++)
		{
			// �ж��Ƿ���fTemp[i]���ӽڵ�
			if (iMap[k] == i)
			{
				// �ı�����ַ���
				m_strCode[k] = "1" + m_strCode[k];
			}
			else if (iMap[k] == i + 1)
			{
				// �ı�����ַ���
				m_strCode[k] = "0" + m_strCode[k];
			}
		}
		
		// ������С������������ӣ�������fTemp[i + 1]��
		fTemp[i + 1] += fTemp[i];
		
		// �ı�ӳ���ϵ
		for (k = 0; k < m_iColorNum; k ++)
		{
			// �ж��Ƿ���fTemp[i]���ӽڵ�
			if (iMap[k] == i)
			{
				// �ı�ӳ�䵽�ڵ�i+1
				iMap[k] = i + 1;
			}
		}
		
		// ��������
		for (j = i + 1; j < m_iColorNum - 1; j ++)
		{
			if (fTemp[j] > fTemp[j + 1])
			{
				// ����
				fT = fTemp[j];
				fTemp[j] = fTemp[j + 1];
				fTemp[j + 1] = fT;
				
				// ����ӳ���ϵ
				for (k = 0; k < m_iColorNum; k ++)
				{
					// �ж��Ƿ���fTemp[i]���ӽڵ�
					if (iMap[k] == j)
					{
						// �ı�ӳ�䵽�ڵ�j+1
						iMap[k] = j + 1;
					}
					else if (iMap[k] == j + 1)
					{
						// �ı�ӳ�䵽�ڵ�j
						iMap[k] = j;
					}
				}
			}
			else
			{
				// �˳�ѭ��
				break;
			}
		}
	}
	
	// ����ƽ�����ֳ���
	for (i = 0; i < m_iColorNum; i ++)
	{
		// �ۼ�
		m_dAvgCodeLen += m_fFreq[i] * m_strCode[i].GetLength();
	}
	
	// �������Ч��
	m_dEfficiency = m_dEntropy / m_dAvgCodeLen;
	
	// ����䶯
	UpdateData(FALSE);
	
	//////////////////////////////////////////////////////////
	// ���������
	
	// ����List�ؼ���ʽ
	m_lstTable.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	
	// ��List�ؼ����Header
	m_lstTable.InsertColumn(0, "�Ҷ�ֵ", LVCFMT_LEFT, 60, 0);
	m_lstTable.InsertColumn(1, "����Ƶ��", LVCFMT_LEFT, 78, 0);
	m_lstTable.InsertColumn(2, "����������", LVCFMT_LEFT, 110, 1);
	m_lstTable.InsertColumn(3, "���ֳ���", LVCFMT_LEFT, 78, 2);
	
	// ������ʽΪ�ı�
	lvitem.mask = LVIF_TEXT;
	
	// ����ƽ�����ֳ���
	for (i = 0; i < m_iColorNum; i ++)
	{
		// ���һ��
		lvitem.iItem = m_lstTable.GetItemCount();
		str.Format("%u",i);
		lvitem.iSubItem = 0;
		lvitem.pszText= (LPTSTR)(LPCTSTR)str;
		iActualItem = m_lstTable.InsertItem(&lvitem);
		
		// ���������
		lvitem.iItem = iActualItem;
		
		// ��ӻҶ�ֵ���ֵ�Ƶ��
		lvitem.iSubItem = 1;
		str.Format("%f",m_fFreq[i]);
		lvitem.pszText = (LPTSTR)(LPCTSTR)str;
		m_lstTable.SetItem(&lvitem);
		
		// ��ӹ���������
		lvitem.iSubItem = 2;
		lvitem.pszText = (LPTSTR)(LPCTSTR)m_strCode[i];
		m_lstTable.SetItem(&lvitem);
		
		// ������ֳ���
		lvitem.iSubItem = 3;
		str.Format("%u",m_strCode[i].GetLength());
		lvitem.pszText = (LPTSTR)(LPCTSTR)str;
		m_lstTable.SetItem(&lvitem);
	}	
	
	// ����TRUE
	return TRUE;
}
