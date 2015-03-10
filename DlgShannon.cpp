// DlgShannon.cpp : implementation file
#include "stdafx.h"
#include "carplate.h"
#include "DlgShannon.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgShannon dialog


CDlgShannon::CDlgShannon(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShannon::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShannon)
	m_dEntropy = 0.0;
	m_dAvgCodeLen = 0.0;
	m_dEfficiency = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgShannon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShannon)
	DDX_Control(pDX, IDC_LST_Table, m_lstTable);
	DDX_Text(pDX, IDC_EDIT1, m_dEntropy);
	DDX_Text(pDX, IDC_EDIT2, m_dAvgCodeLen);
	DDX_Text(pDX, IDC_EDIT3, m_dEfficiency);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShannon, CDialog)
	//{{AFX_MSG_MAP(CDlgShannon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgShannon message handlers

BOOL CDlgShannon::OnInitDialog() 
{
	
	// �ַ�������
	CString	str;
	
	// ѭ������
	LONG	i;
	LONG	j;
	
	// �м����
	FLOAT	fT;
	LONG	iTemp;
	
	// ��������м���������
	FLOAT *	fTemp;
	
	// ����ӳ���ϵ������
	LONG *	iMap;
	
	// ��ǰ���������Ƶ�ʺ�
	FLOAT	fTotal;
	
	// ������������ɵĸ�����
	LONG	iCount = 0;
	
	// Ƶ�ʺ�
	FLOAT	fSum;
	
	// ��ʼλ��
	LONG	iStart;
	
	// ָ�򲼶��������ָ��
	BOOL	* bFinished;
	
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
	
	// �����ڴ�
	fTemp = new FLOAT[m_iColorNum];
	m_strCode = new CString[m_iColorNum];
	bFinished = new BOOL[m_iColorNum];
	iMap  = new LONG[m_iColorNum];
	
	fTotal = 0;
	
	// ��ʼ��fTempΪm_fFreq, bFinishedΪFALSE
	for (i = 0; i < m_iColorNum; i ++)
	{
		// ��ֵ
		fTemp[i] = m_fFreq[i];
		
		// ��ʼ��ӳ���ϵ
		iMap[i] = i;
		
		// ��ʼ��ΪFALSE
		bFinished[i] = FALSE;
		
		// ����fTotal
		fTotal += m_fFreq[i];
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
				iTemp = iMap[i];
				iMap[i] = iMap[i+1];
				iMap[i+1] = iTemp;
				
			}
		}
	}
	
	//////////////////////////////////////////////////////////
	// ������ũ����ŵ�����
	
	// �ҵ����ʴ���0���ſ�ʼ����
	for (iStart = 0; iStart < m_iColorNum - 1; iStart ++)
	{
		// �жϸ����Ƿ����0
		if (fTemp[iStart] > 0)
		{
			// ����
			break;
		}
	}
	
	// ��ʼ������
	fSum = 0;
	str = "1";
	
	// ��ʼ����
	while(iCount < m_iColorNum)
	{
		// ��ʼ��iCountΪiStart
		iCount = iStart;
		
		// ѭ������
		for (i = iStart; i < m_iColorNum; i ++)
		{
			// �ж��Ƿ�������
			if (bFinished[i] == FALSE)
			{
				// ����û����ɣ���������
				
				// fSum�ӵ�ǰ���ֵ�Ƶ��
				fSum += fTemp[i];
				
				// �ж��Ƿ񳬳��ܺ͵�һ��
				if (fSum > fTotal/2.0)
				{
					// ������׷�ӵ��ַ���Ϊ0
					str = "0";
				}
				
				// ����׷���ַ�1��0
				m_strCode[iMap[i]] += str;
				
				// �ж��Ƿ������һ��
				if (fSum == fTotal)
				{
					// ���һ���ֱ��룬���¼���fTotal
					
					// ��ʼ��fSumΪ0
					fSum = 0;
					
					// �ж��Ƿ������һ��Ԫ��
					if (i == m_iColorNum - 1)
					{
						// ��������ô���ʼ�㿪ʼ
						j = iStart;
					}
					else
					{
						// ����������ô���һ���㿪ʼ
						j = i + 1;
					}
					
					// ����jֵ
					iTemp = j;
					str = m_strCode[iMap[j]];
					
					// ������һ�ε�fTotal
					fTotal = 0;
					for (; j < m_iColorNum; j++)
					{
						// �ж��Ƿ���ͬһ�α���
						if ((m_strCode[iMap[j]].Right(1) != str.Right(1)) 
							|| (m_strCode[iMap[j]].GetLength() != str.GetLength()))
						{
							// �˳�ѭ��
							break;
						}
						
						// �ۼ�
						fTotal += fTemp[j];
					}
					
					// ��ʼ��strΪ1
					str = "1";
					
					// �ж��Ƿ�öγ���Ϊ1
					if (iTemp + 1 == j)
					{
						// �ǣ���ʾ�öα����Ѿ����
						bFinished[iTemp] = TRUE;
					}
				}
			}
			else
			{
				// iCount��1
				iCount ++;
				
				// ������һ��ѭ����fTotal
				
				// ��ʼ��fSumΪ0
				fSum = 0;
				
				// �ж��Ƿ������һ��Ԫ��
				if (i == m_iColorNum - 1)
				{
					// ��������ô���ʼ�㿪ʼ
					j = iStart;
				}
				else
				{
					// ����������ô���һ���㿪ʼ
					j = i + 1;
				}
				
				// ����jֵ
				iTemp = j;
				str = m_strCode[iMap[j]];
				
				// ������һ�ε�fTotal
				fTotal = 0;
				for (; j < m_iColorNum; j++)
				{
					// �ж��Ƿ���ͬһ�α���
					if ((m_strCode[iMap[j]].Right(1) != str.Right(1)) 
						|| (m_strCode[iMap[j]].GetLength() != str.GetLength()))
					{
						// �˳�ѭ��
						break;
					}
					
					// �ۼ�
					fTotal += fTemp[j];
				}
				
				// ��ʼ��strΪ1
				str = "1";
				
				// �ж��Ƿ�öγ���Ϊ1
				if (iTemp + 1 == j)
				{
					// �ǣ���ʾ�öα����Ѿ����
					bFinished[iTemp] = TRUE;
				}
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
	
	// ListCtrl��ITEM
	LV_ITEM lvitem;
	
	// �м����������ListCtrl����ӵ�ITEM���
	int		iActualItem;
	
	// ����List�ؼ���ʽ
	m_lstTable.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	
	// ��List�ؼ����Header
	m_lstTable.InsertColumn(0, "�Ҷ�ֵ", LVCFMT_LEFT, 60, 0);
	m_lstTable.InsertColumn(1, "����Ƶ��", LVCFMT_LEFT, 78, 0);
	m_lstTable.InsertColumn(2, "��ũ��ŵ����", LVCFMT_LEFT, 110, 1);
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
		
		// �����ũ��ŵ����
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
