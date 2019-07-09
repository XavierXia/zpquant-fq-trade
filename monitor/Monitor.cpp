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

// Monitor.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Monitor.h"
#include "MainFrm.h"

#include "GraphFrm.h"
#include "GraphDoc.h"
#include "GraphView.h"

#include "MeddleView.h"
#include "MeddleFrame.h"
#include "MeddleDoc.h"

#include "FloatingProfitView.h"
#include "FloatingProfitFrm.h"
#include "FloatingProfitDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMonitorApp

BEGIN_MESSAGE_MAP(CMonitorApp, CWinAppEx)
    ON_COMMAND(ID_APP_ABOUT, &CMonitorApp::OnAppAbout)
    // �����ļ��ı�׼�ĵ�����
    ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
    ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
    // ��׼��ӡ��������
    ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CMonitorApp ����

CMonitorApp::CMonitorApp()
{
    m_bHiColorIcons = TRUE;

    // ֧����������������
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
    // ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���: 
    //     1) �����д˸������ã�������������������֧�ֲ�������������
    //     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
    System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

    // TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
    //Ϊ CompanyName.ProductName.SubProduct.VersionInformation
    SetAppID(_T("Monitor.AppID.NoVersion"));

    // TODO: �ڴ˴���ӹ�����룬
    // ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CMonitorApp ����

CMonitorApp theApp;


// CMonitorApp ��ʼ��

BOOL CMonitorApp::InitInstance()
{
    // ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
    // ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
    //����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
    // �����ؼ��ࡣ
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinAppEx::InitInstance();


    // ��ʼ�� OLE ��
    if (!AfxOleInit())
    {
        AfxMessageBox(IDP_OLE_INIT_FAILED);
        return FALSE;
    }

    AfxEnableControlContainer();

    EnableTaskbarInteraction();

    // ʹ�� RichEdit �ؼ���Ҫ AfxInitRichEdit2()    
    // AfxInitRichEdit2();

    // ��׼��ʼ��
    // ���δʹ����Щ���ܲ�ϣ����С
    // ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
    // ����Ҫ���ض���ʼ������
    // �������ڴ洢���õ�ע�����
    // TODO: Ӧ�ʵ��޸ĸ��ַ�����
    // �����޸�Ϊ��˾����֯��
    SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
    LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


    InitContextMenuManager();
    InitShellManager();

    InitKeyboardManager();

    InitTooltipManager();
    CMFCToolTipInfo ttParams;
    ttParams.m_bVislManagerTheme = TRUE;
    theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
        RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

    // ע��Ӧ�ó�����ĵ�ģ�塣  �ĵ�ģ��
    // �������ĵ�����ܴ��ں���ͼ֮�������
    CMultiDocTemplate* pDocTemplate;
    pDocTemplate = new CMultiDocTemplate(IDR_GraphViewTYPE,
        RUNTIME_CLASS(CGraphDoc),
        RUNTIME_CLASS(CGraphFrame), // �Զ��� MDI �ӿ��
        RUNTIME_CLASS(CGraphView));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);


    pDocTemplate = new CMultiDocTemplate(IDR_MeddleViewTYPE,
        RUNTIME_CLASS(CMeddleDoc),
        RUNTIME_CLASS(CMeddleFrame), // �Զ��� MDI �ӿ��
        RUNTIME_CLASS(CMeddleView));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);

    pDocTemplate = new CMultiDocTemplate(IDR_FloatingProfitViewTYPE,
        RUNTIME_CLASS(CFloatingProfitDoc),
        RUNTIME_CLASS(CFloatingProfitFrame), // �Զ��� MDI �ӿ��
        RUNTIME_CLASS(CFloatingProfitView));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);

    // ������ MDI ��ܴ���
    CMainFrame* pMainFrame = new CMainFrame;
    if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
    {
        delete pMainFrame;
        return FALSE;
    }
    m_pMainWnd = pMainFrame;

    // �������к�׺ʱ�ŵ��� DragAcceptFiles
    //  �� MDI Ӧ�ó����У���Ӧ������ m_pMainWnd ֮����������
    // ������/��
    m_pMainWnd->DragAcceptFiles();

    // ������׼ shell ���DDE�����ļ�������������
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);
    cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
    // ���á�DDE ִ�С�
    EnableShellOpen();
    RegisterShellFileTypes(TRUE);


    // ��������������ָ�������  ���
    // �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;
    // �������ѳ�ʼ���������ʾ����������и���
    pMainFrame->ShowWindow(m_nCmdShow);
    pMainFrame->UpdateWindow();

    return TRUE;
}

int CMonitorApp::ExitInstance()
{
    //TODO: �����������ӵĸ�����Դ
    AfxOleTerm(FALSE);
    CleanState();
    return CWinAppEx::ExitInstance();
}

// CMonitorApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CMonitorApp::OnAppAbout()
{
    CAboutDlg aboutDlg;
    aboutDlg.DoModal();
}

// CMonitorApp �Զ������/���淽��

void CMonitorApp::PreLoadState()
{
    BOOL bNameValid;
    CString strName;
    bNameValid = strName.LoadString(IDS_EDIT_MENU);
    ASSERT(bNameValid);
    GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CMonitorApp::LoadCustomState()
{
}

void CMonitorApp::SaveCustomState()
{
}

// CMonitorApp ��Ϣ�������

