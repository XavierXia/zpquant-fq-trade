// DlgMeddle.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "DlgMeddle.h"
#include "afxdialogex.h"
#include "resource.h"
#include <string>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem.hpp>
#ifndef BOOST_SPIRIT_THREADSAFE
#define BOOST_SPIRIT_THREADSAFE
#endif
#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/json_parser.hpp> 
#include <boost/date_time/posix_time/posix_time.hpp>
#include "MainFrm.h"
using namespace std;
// CDlgMeddle �Ի���
void Communicate(const char * address, unsigned int port, const std::stringstream & in, std::stringstream & out);
IMPLEMENT_DYNAMIC(CDlgMeddle, CDialogEx)

CDlgMeddle::CDlgMeddle(CWnd* pParent,
    string _strStrategyID,
    string _strIp,
    unsigned int _uPort,
    string _strName,
    string _strStrategyName,
    string _strStrategyComment)
    : CDialogEx(IDD_DIALOG_MEDDLE, pParent)
{
    _strStrategyID = _strStrategyID;
         _strIp = _strIp;
         _uPort = _uPort;
         _strName = _strName;
         _strStrategyName = _strStrategyName;
         _strStrategyComment = _strStrategyComment;
}

CDlgMeddle::~CDlgMeddle()
{
}

void CDlgMeddle::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_MEDDLE_COMMAND, m_editMeddleCommand);
    DDX_Control(pDX, IDC_LIST_MEDDLE_RESPONSE, m_listMeddleResponse);
    DDX_Control(pDX, IDC_STATIC_STRATEGY_LABEL, m_textLabel);
    DDX_Control(pDX, IDC_STATIC_COMMAND, m_textCommandLabel);
    DDX_Control(pDX, IDC_BUTTON_SEND_MEDDLE, m_butSendMeddle);
    DDX_Control(pDX, IDC_BUTTON_GET_MEDDLE_RESPONSE, m_butGetResponse);
}


BEGIN_MESSAGE_MAP(CDlgMeddle, CDialogEx)
    ON_WM_SIZE()
    ON_BN_CLICKED(IDC_BUTTON_SEND_MEDDLE, &CDlgMeddle::OnBnClickedButtonSendMeddle)
    ON_BN_CLICKED(IDC_BUTTON_GET_MEDDLE_RESPONSE, &CDlgMeddle::OnBnClickedButtonGetMeddleResponse)
END_MESSAGE_MAP()


// CDlgMeddle ��Ϣ�������


void CDlgMeddle::OnSize(UINT nType, int cx, int cy)
{
    CDialogEx::OnSize(nType, cx, cy);
#define HIGTH 25
    if (IsWindow(m_textLabel))
        m_textLabel.SetWindowPos(NULL, 0, 0, cx, HIGTH,SWP_NOZORDER);
    if(IsWindow(m_textCommandLabel))
        m_textCommandLabel.SetWindowPos(NULL, 0, HIGTH+1, cx*0.1, HIGTH, SWP_NOZORDER);

    if (IsWindow(m_editMeddleCommand))
        m_editMeddleCommand.SetWindowPos(NULL, cx*0.1 + 1, HIGTH + 1, cx*0.6, HIGTH, SWP_NOZORDER);

    if (IsWindow(m_butSendMeddle))
        m_butSendMeddle.SetWindowPos(NULL, cx*0.7 + 2, HIGTH + 1, cx*0.1, HIGTH, SWP_NOZORDER);

    if (IsWindow(m_butGetResponse))
        m_butGetResponse.SetWindowPos(NULL, cx*0.8 + 3, HIGTH + 1, cx*0.1, HIGTH, SWP_NOZORDER);

    if (IsWindow(m_listMeddleResponse))
        m_listMeddleResponse.SetWindowPos(NULL, 1, HIGTH * 2 + 5,cx , cy- HIGTH * 2-4, SWP_NOZORDER);
    // TODO: �ڴ˴������Ϣ����������
}


void CDlgMeddle::OnBnClickedButtonSendMeddle()
{
    CString commandW;
    m_editMeddleCommand.GetWindowTextW(commandW);
    string command = CW2A(commandW);
    boost::property_tree::ptree RequireMeddleFormat;
    RequireMeddleFormat.put("type", "reqmeddle");
    RequireMeddleFormat.put("strategyid", "");
    RequireMeddleFormat.put("command", command);
    for (auto & str : m_listStrategies)
    {
        boost::property_tree::ptree ResultMeddleFormat;
        std::stringstream in,out;
        RequireMeddleFormat.find("strategyid")->second.data() = get<0>(str);
        try {
            boost::property_tree::write_json(in, RequireMeddleFormat);
            Communicate(m_strIp.c_str(), m_uPort, in, out);
            boost::property_tree::read_json(out, ResultMeddleFormat);
        }
        catch (std::exception & err)
        {
            AppendOutput(get<0>(str),err.what());
        }

        auto ResultNode = ResultMeddleFormat.find("result");
        if (ResultNode != ResultMeddleFormat.not_found())
            AppendOutput(get<0>(str), ResultNode->second.data());
        else
            AppendOutput(get<0>(str),"Can not find <result>");
    }
}


void CDlgMeddle::OnBnClickedButtonGetMeddleResponse()
{
    CString commandW;
    m_editMeddleCommand.GetWindowTextW(commandW);
    string command = CW2A(commandW);
    boost::property_tree::ptree RequireMeddleFormat;
    RequireMeddleFormat.put("type", "reqgetmeddleresponse");
    RequireMeddleFormat.put("strategyid", "");
    for (auto &str : m_listStrategies)
    {
        boost::property_tree::ptree ResultMeddleFormat;
        std::stringstream in, out;
        RequireMeddleFormat.find("strategyid")->second.data() = get<0>(str);
        try {
            boost::property_tree::write_json(in, RequireMeddleFormat);
            Communicate(m_strIp.c_str(), m_uPort, in, out);
            boost::property_tree::read_json(out, ResultMeddleFormat);
        }
        catch (std::exception & err)
        {
            
            AppendOutput(get<0>(str),err.what());
            
        }
        
        for (auto & node : ResultMeddleFormat)
            AppendOutput(get<0>(str),node.second.data());
        
    }
}

void CDlgMeddle::AppendOutput(string sid,string response)
{
    
    int nRow = m_listMeddleResponse.InsertItem(m_listMeddleResponse.GetItemCount()+1, CA2W(sid.c_str()));
    m_listMeddleResponse.SetItemText(nRow, 1, CA2W(response.c_str()));
}

void CDlgMeddle::SetConfig(string _strIp,
    unsigned int _uPort,
    string _strName,
    list< tuple< string, string, string> > & _listStrategies)
{
    
    m_strIp= _strIp;
    m_uPort= _uPort;
    m_strName= _strName;
    m_listStrategies = _listStrategies;
    
    stringstream ss;
    ss << _strName << " ";
    for (auto & str : _listStrategies)
        ss << get<0>(str) << " ";
    m_textLabel.SetWindowTextW(CString(CA2W(ss.str().c_str())));

    {
        m_listMeddleResponse.InsertColumn(0, _T("����ID"), LVCFMT_LEFT, 70);// ������ 
        m_listMeddleResponse.InsertColumn(1, _T("��Ϣ"), LVCFMT_LEFT, 700);// ������ 
            
        LONG lStyle;
        lStyle = GetWindowLong(m_listMeddleResponse.m_hWnd, GWL_STYLE);// ��ȡ��ǰ����style 
        lStyle &= ~LVS_TYPEMASK; // �����ʾ��ʽλ 
        lStyle |= LVS_REPORT; // ����style 
        SetWindowLong(m_listMeddleResponse.m_hWnd, GWL_STYLE, lStyle);// ����style 
        DWORD dwStyle2 = m_listMeddleResponse.GetExtendedStyle();
        dwStyle2 |= LVS_EX_FULLROWSELECT;// ѡ��ĳ��ʹ���и�����ֻ������report ����listctrl �� 
        dwStyle2 |= LVS_EX_GRIDLINES;// �����ߣ�ֻ������report ����listctrl �� 
        dwStyle2 |= LVS_EX_CHECKBOXES;//item ǰ����checkbox �ؼ� 
        m_listMeddleResponse.SetExtendedStyle(dwStyle2); // ������չ��� 
    }
    
}
