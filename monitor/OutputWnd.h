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

#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList ����

class COutputWnd : public CDockablePane
{
// ����
public:
    COutputWnd();

    void UpdateFonts();

// ����
protected:
    
    CListCtrl m_wndOutput;

protected:
    void AdjustHorzScroll(CListBox& wndListBox);

// ʵ��
public:
    virtual ~COutputWnd();
    BOOL CanBeClosed() const;
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);

    DECLARE_MESSAGE_MAP()
    afx_msg LRESULT OnMsgOutputWndDisplayMessage(WPARAM wParam, LPARAM lParam);
};

