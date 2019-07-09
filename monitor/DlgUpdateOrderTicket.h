#pragma once
#include "afxwin.h"


// CDlgUpdateOrderTicket �Ի���

class CDlgUpdateOrderTicket : public CDialogEx
{
    DECLARE_DYNAMIC(CDlgUpdateOrderTicket)
    static int s_intMaxTickets;
    static int s_intRemainTickets;
public:
    CDlgUpdateOrderTicket(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~CDlgUpdateOrderTicket();

// �Ի�������
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG_UPDATE_ORDER_TICKET };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()
public:
    CEdit m_editMaxTicketsCount;
    CEdit m_editRemainTicketsCount;
    afx_msg void OnBnClickedOk();
};
