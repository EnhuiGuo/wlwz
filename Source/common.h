#pragma once

// ��֧��XP����ϵͳ����
#define _WIN32_WINNT _WIN32_WINNT_WINXP 
#define WINVER       _WIN32_WINNT_WINXP 

// ���� UNICODE �汾��������
#ifndef UNICODE
#define UNICODE
#endif

// ���� UNICODE ͬʱ���� _UNICODE
#ifdef UNICODE
#ifndef _UNICODE
#define _UNICODE
#endif
#endif

///////////////////////// ���� Windows ���� /////////////////////////

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
#pragma warning(push, 3)
#include <Windows.h>
#pragma warning(pop) 
#pragma warning(push, 4)
#include <CommCtrl.h>
#include <process.h>

// ��ֹδ���ò�������
#pragma warning(disable:4100)

///////////////////////// ���ú������궨�� /////////////////////////

// ����Ի�����Ϣ
#define HANDLE_DLGMSG(hWnd, message, fn)                 \
   case (message): return (SetDlgMsgResult(hWnd, uMsg,     \
      HANDLE_##message((hWnd), (wParam), (lParam), (fn))))

// ���ó���ͼ��
inline void SetDlgIcons (HWND hWnd, int idi) {
	HICON hIcon = idi == 0 ? LoadIcon (NULL, IDI_APPLICATION)
		: LoadIcon ((HINSTANCE)GetWindowLongPtr (hWnd, GWLP_HINSTANCE),
			MAKEINTRESOURCE (idi));

	SendMessage (hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	SendMessage (hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
}

// C++ �����߳�
typedef unsigned (__stdcall *PTHREAD_START) (void *);

#define chBEGINTHREADEX(psa, cbStackSize, pfnStartAddr, \
   pvParam, dwCreateFlags, pdwThreadId)                 \
      ((HANDLE)_beginthreadex(                          \
         (void *)        (psa),                         \
         (unsigned)      (cbStackSize),                 \
         (PTHREAD_START) (pfnStartAddr),                \
         (void *)        (pvParam),                     \
         (unsigned)      (dwCreateFlags),               \
         (unsigned *)    (pdwThreadId)))

/////////////////////////// ������ʽ�嵥 ////////////////////////////


#pragma comment(linker, "/nodefaultlib:oldnames.lib")

// Needed for supporting XP/Vista styles.
#if defined(_M_IA64)
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='IA64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#if defined(_M_X64)
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.6000.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#if defined(_M_IX86)
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif


///////////////////////////////////////////////////////////////////////////////
/*
BOOL Dlg_OnInitDialog (HWND hWnd, HWND hwndFocus, LPARAM lParam) {

	SetDlgIcons (hWnd, 0);

	return(TRUE);
}

///////////////////////////////////////////////////////////////////////////////

void Dlg_OnCommand (HWND hWnd, int id, HWND hwndCtl, UINT codeNotify) {

	switch (id) {

		case IDCANCEL:
			// �رնԻ���
			EndDialog (hWnd, id);
			break;

		case IDOK:
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////

INT_PTR WINAPI Dlg_Proc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {
		// ��ʼ���Ի���
		HANDLE_DLGMSG (hwnd, WM_INITDIALOG, Dlg_OnInitDialog);
		// ����������Ϣ
		HANDLE_DLGMSG (hwnd, WM_COMMAND, Dlg_OnCommand);
	}

	return(FALSE);
}

///////////////////////////////////////////////////////////////////////////////

int WINAPI _tWinMain (HINSTANCE hinstExe, HINSTANCE, PTSTR pszCmdLine, int) 
{

	// �����Ի���
	DialogBoxParam (hinstExe, MAKEINTRESOURCE (IDD_DLG),
		NULL, Dlg_Proc, NULL);

	return(0);
}
*/
///////////////////////////////////////////////////////////////////////////////
