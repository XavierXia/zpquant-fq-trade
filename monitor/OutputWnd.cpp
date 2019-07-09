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

#include "stdafx.h"

#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputWnd::COutputWnd()
{
}

COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_MESSAGE(MSG_OUTPUT_WND_DISPLAY_MESSAGE, &COutputWnd::OnMsgOutputWndDisplayMessage)
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CDockablePane::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rectDummy;
    rectDummy.SetRectEmpty();

    // ����ѡ�����: 
    const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

    if (!m_wndOutput.Create(dwStyle, rectDummy, this, 0))
    {
        TRACE0("δ�ܴ����������\n");
        return -1;      // δ�ܴ���
    }

    UpdateFonts();
    {
#define LIST m_wndOutput
        LIST.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 100);// ������ 
        LIST.InsertColumn(1, _T("ʱ��"), LVCFMT_LEFT, 180);// ������ 
        LIST.InsertColumn(2, _T("��Ϣ����"), LVCFMT_LEFT, 1000);// ������ 
        LONG lStyle;
        lStyle = GetWindowLong(LIST.m_hWnd, GWL_STYLE);// ��ȡ��ǰ����style 
        lStyle &= ~LVS_TYPEMASK; // �����ʾ��ʽλ 
        lStyle |= LVS_REPORT; // ����style 
        SetWindowLong(LIST.m_hWnd, GWL_STYLE, lStyle);// ����style 
        DWORD dwStyle = LIST.GetExtendedStyle();
        dwStyle |= LVS_EX_FULLROWSELECT;// ѡ��ĳ��ʹ���и�����ֻ������report ����listctrl �� 
        dwStyle |= LVS_EX_GRIDLINES;// �����ߣ�ֻ������report ����listctrl �� 
        LIST.SetExtendedStyle(dwStyle); // ������չ��� 
    }
    return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
    CDockablePane::OnSize(nType, cx, cy);

    // ѡ��ؼ�Ӧ��������������: 
    m_wndOutput.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
    CClientDC dc(this);
    CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);

    int cxExtentMax = 0;

    for (int i = 0; i < wndListBox.GetCount(); i ++)
    {
        CString strItem;
        wndListBox.GetText(i, strItem);

        cxExtentMax = max(cxExtentMax, (int)dc.GetTextExtent(strItem).cx);
    }

    wndListBox.SetHorizontalExtent(cxExtentMax);
    dc.SelectObject(pOldFont);
}

BOOL COutputWnd::CanBeClosed() const
{
    return FALSE;
}
void COutputWnd::UpdateFonts()
{
    m_wndOutput.SetFont(&afxGlobalData.fontRegular);
}


afx_msg LRESULT COutputWnd::OnMsgOutputWndDisplayMessage(WPARAM wParam, LPARAM lParam)
{
    CString * msg = reinterpret_cast<CString*>(wParam);


    SYSTEMTIME st;
    GetLocalTime(&st);
    CString _time;
    _time.Format(L"%d-%d-%d %d:%d:%d.%d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    CString ID;
    int cnt = this->m_wndOutput.GetItemCount();
    ID.Format(_T("%d"), cnt);
    int nRow = m_wndOutput.InsertItem(0, ID);
    m_wndOutput.SetItemText(nRow, 1, _time);
    m_wndOutput.SetItemText(nRow, 2, *msg);
    delete msg;

    return 0;
}
