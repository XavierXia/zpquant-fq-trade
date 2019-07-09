// DlgUpdateStrategyBin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "DlgUpdateStrategyBin.h"
#include "afxdialogex.h"


// CDlgUpdateStrategyBin �Ի���
std::string CDlgUpdateStrategyBin::s_strResult;
IMPLEMENT_DYNAMIC(CDlgUpdateStrategyBin, CDialogEx)

CDlgUpdateStrategyBin::CDlgUpdateStrategyBin(std::vector<std::string> & ValidBinName, CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_DIALOG_UPDATE_STRATEGY_BIN, pParent), m_ValidBinName(ValidBinName)
{

}

CDlgUpdateStrategyBin::~CDlgUpdateStrategyBin()
{
}

void CDlgUpdateStrategyBin::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, m_combValidStrategyBins);
}


BEGIN_MESSAGE_MAP(CDlgUpdateStrategyBin, CDialogEx)
    ON_BN_CLICKED(IDOK, &CDlgUpdateStrategyBin::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgUpdateStrategyBin ��Ϣ�������


BOOL CDlgUpdateStrategyBin::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    for (auto & bin : m_ValidBinName)
        m_combValidStrategyBins.AddString(CA2W(bin.c_str()));
    s_strResult = "";
    return TRUE; 
}


void CDlgUpdateStrategyBin::OnBnClickedOk()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    CString current;
    m_combValidStrategyBins.GetWindowTextW(current);
    s_strResult = CW2A(current);
    CDialogEx::OnOK();
}
