#pragma once
#include "afxwin.h"
#include "StrategyData.h"

// CDlgSetShareValue �Ի���

class CDlgSetShareValue : public CDialogEx
{
    DECLARE_DYNAMIC(CDlgSetShareValue)

public:
    CDlgSetShareValue(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~CDlgSetShareValue();

// �Ի�������
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG_SET_SHARE_VALUE };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()
public:
    CEdit m_editIndex;
    CEdit m_editNewValue;
    static StrategyData::TSharedIndexType s_intIndex;
    static double s_dbNewValue;
    afx_msg void OnBnClickedOk();
};
