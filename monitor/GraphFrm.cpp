// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ������� 
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// ChildFrm.cpp : CGraphFrame ���ʵ��
//

#include "stdafx.h"
#include "Monitor.h"

#pragma region ptree
#ifndef BOOST_SPIRIT_THREADSAFE
#define BOOST_SPIRIT_THREADSAFE
#endif
#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/json_parser.hpp> 
using namespace boost::property_tree;
#pragma endregion
#include "GraphFrm.h"
#include "MainFrm.h"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem.hpp>
#include "GraphView.h"
#include "GraphDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
void Communicate(const char * address, unsigned int port, const std::stringstream & in, std::stringstream & out);
IMPLEMENT_DYNCREATE(CGraphFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CGraphFrame, CMDIChildWndEx)
    ON_WM_CREATE()
    ON_WM_CLOSE()
    ON_WM_CLOSE()
END_MESSAGE_MAP()

// CGraphFrame ����/����

CGraphFrame::CGraphFrame()
{
    
}

CGraphFrame::~CGraphFrame()
{
}

BOOL CGraphFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.style &= ~FWS_ADDTOTITLE;
    // TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
    if( !CMDIChildWndEx::PreCreateWindow(cs) )
        return FALSE;

    return TRUE;
}

// CGraphFrame ���

#ifdef _DEBUG
void CGraphFrame::AssertValid() const
{
    CMDIChildWndEx::AssertValid();
}

void CGraphFrame::Dump(CDumpContext& dc) const
{
    CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

int CGraphFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
        return -1;
    boost::property_tree::ptree m_treeInitTree;
    bool m_boolTimmerRunning = true;
    string _strStrategyID;
    string _strIp;
    unsigned int _uPort;
    string _strName;
    list< tuple< string, string,string> > _listStrateies;
    std::tie(_strIp, _uPort, _strName, _listStrateies)
        = dynamic_cast<CMainFrame*>(AfxGetMainWnd())->GetNextDocumentParam();
    
    
    stringstream ssTitle;
    ssTitle << _strName << " " << get<0>(_listStrateies.front()) << " " << get<1>(_listStrateies.front());
    CString Title = CA2W(ssTitle.str().c_str());
    SetWindowText(Title);
    return 0;
}

void CGraphFrame::OnClose()
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    auto mainf = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
    mainf->RemoveRequiryDataCallback(dynamic_cast<CGraphView*>(GetActiveView()));
    CMDIChildWndEx::OnClose();
}
