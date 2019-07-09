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

// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif
enum TViewUpdateType
{
	InitChart,
	AppendValue
};

#define MSG_CTRADESERVERPANEL_TAB_CHANGED (WM_USER + 1)
#define MSG_C_MAIN_FRAME_SHOW_MESSAGE (WM_USER + 2)
#define MSG_TREE_ITEM_DB_CLICK (WM_USER + 3)
#define MSG_PROP_ITEM_R_CLICK (WM_USER + 4)
#define MSG_ADD_SOURCE_DLG_COMB_SEL_CHANGED (WM_USER + 5)
#define MSG_OUTPUT_WND_DISPLAY_MESSAGE  (WM_USER + 6)
#define MSG_ON_UPDATE_VIEW  (WM_USER + 7)
#define MSG_ON_VIEW_INIT_FINISHED  (WM_USER + 8)
#define MSG_SEND_MEDDLE  (WM_USER + 9)
#define MSG_MEDDLE_RESPONSE  (WM_USER + 10)
#define MSG_STRATEGY_BIN_CHANGED  (WM_USER + 11)
#define MSG_ARCHIVEFILE_CHANGED  (WM_USER + 12)
#define MSG_DRAG_JSON_FILE (WM_USER + 13)
#define MSG_GRAPH_VIEW_UPDATE  (WM_USER + 14)
#define MSG_RESET_PROBE_GRAPH  (WM_USER + 15)
#define MSG_INIT_TREE_HAS_FETCHED   (WM_USER + 16)
#define MSG_SHOW_HIDE_CUSTOM_BUTTON   (WM_USER + 17)