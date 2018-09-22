#include "CommandInfo.h"

HINSTANCE g_hInstExe;
UINT_PTR g_uiTimer = 0;
bool g_bAutoTestExit = false;

BOOL Dlg_OnInitDialog (HWND hWnd, HWND hwndFocus, LPARAM lParam) {

	SetDlgIcons (hWnd, 0);
	
	// ��ʼ��TAB�ؼ�

	static PTSTR pPageTitles[] = {
		TEXT ("��Ϣ"),
		TEXT ("����"),
		TEXT ("����"),
		TEXT ("����"),
		TEXT ("�ƶ�"),
		TEXT ("�һ�")
	};

	TCITEM  tie;
	tie.mask = TCIF_TEXT;

	RECT rect;
	for (size_t i = 0; i < g_dwPageMax; i++)
	{
		g_hPages[i] =
			CreateDialog (g_hInstExe, MAKEINTRESOURCE (IDD_DLG_PLAYER_PAGE + i),
				GetDlgItem (hWnd, IDC_GAME_INFO), Dlg_Child);

		tie.pszText = pPageTitles[i];
		SendDlgItemMessage (hWnd,
			IDC_GAME_INFO, TCM_INSERTITEM, i, (LPARAM)&tie);

		if (0 == i) {
			// �����õ�һ���ͻ��˴��ڳߴ���е���
			GetClientRect (g_hPages[i], &rect);
			rect.top += 20;
			rect.left += 0;
			rect.right -= 1;
			rect.bottom -= 2;
		}

		MoveWindow (g_hPages[i], rect.left, rect.top,
			rect.right - rect.left, rect.bottom - rect.top, true);

	}

	ShowWindow (g_hPages[0], SW_SHOW);
	
	//���������ı��������ַ���
	SendDlgItemMessage (g_hPages[2],
		IDC_CHATCONTENT, EM_SETLIMITTEXT, 77, 0);

	//����������ʱ���ı��������ַ���
	SendDlgItemMessage (g_hPages[2],
		IDC_INTERVAL_TIME, EM_SETLIMITTEXT, 4, 0);

	//���ùһ���СѪ��
	SendDlgItemMessage (g_hPages[5],
		IDC_HP_MIN, EM_SETLIMITTEXT, 4, 0);

	//���ùһ��ָ�Ĭ��
	CheckDlgButton (g_hPages[5], IDC_HP_RESTORE, BST_CHECKED);


	//���̿�����Ϣ
	ProcessControl (hWnd);

	g_hThreads[0] = chBEGINTHREADEX (nullptr, 0, AutoTestThread, hWnd, CREATE_SUSPENDED, 0);
	g_hThreads[1] = chBEGINTHREADEX (nullptr, 0, AutoChatThread, g_hPages[2], CREATE_SUSPENDED, 0);
	g_hThreads[2] = chBEGINTHREADEX (nullptr, 0, AutoInfoThread, g_hPages[0], CREATE_SUSPENDED, 0);
	g_hThreads[3] = chBEGINTHREADEX (nullptr, 0, AutoOnHookThread, g_hPages[5], CREATE_SUSPENDED, 0);
	for (size_t i = 0; i < g_dwThreadMax; i++)
	{
		if (nullptr == g_hThreads[i]) {
			MsgBox (TEXT ("����̴߳���ʧ��,��Ҫ��������������!"));
		}
		else {
			SetPriorityClass (g_hThreads[i], BELOW_NORMAL_PRIORITY_CLASS);
			ResumeThread (g_hThreads[i]);
		}
	}

	// ��ʼ��֪ͨ�¼�
	g_hOnlineEvent = CreateEvent (nullptr, true, false, nullptr);
	if (nullptr == g_hOnlineEvent)
		MsgBox (TEXT ("����֪ͨ�¼�����ʧ��,��Ҫ��������������!"));

	g_hExitEvent = CreateEvent (nullptr, true, false, nullptr);
	if (nullptr == g_hExitEvent)
		MsgBox (TEXT ("�˳�֪ͨ�¼�����ʧ��,��Ҫ��������������!"));

	g_hAutoChatEvent = CreateEvent (nullptr, true, false, nullptr);
	if (nullptr == g_hAutoChatEvent)
		MsgBox (TEXT ("�Զ�����֪ͨ�¼�����ʧ��,��Ҫ��������������!"));
	
	g_hAutoOnHookEvent = CreateEvent (nullptr, true, false, nullptr);
	if (nullptr == g_hAutoOnHookEvent)
		MsgBox (TEXT ("�Զ��һ�֪ͨ�¼�����ʧ��,��Ҫ��������������!"));
	
	g_hAutoInfoEvent = CreateEvent (nullptr, true, true, nullptr);
	if (nullptr == g_hAutoOnHookEvent)
		MsgBox (TEXT ("�Զ���Ϣ֪ͨ�¼�����ʧ��,��Ҫ��������������!"));


	return(TRUE);
}

///////////////////////////////////////////////////////////////////////////////

void Cls_OnTimer (HWND hWnd, UINT id) {
}

///////////////////////////////////////////////////////////////////////////////

void Dlg_OnCommand (HWND hWnd, int id, HWND hwndCtl, UINT codeNotify) {
	switch (id) {
		case IDCANCEL:
			// �˳��¼����ź�
			SetEvent (g_hExitEvent);
			WaitForThreadQuit (g_hThreads, g_dwThreadMax);

			// �ر������߳̾��
			for (size_t i = 0; i < g_dwThreadMax; i++) 
				if (nullptr != g_hThreads[i])
					CloseHandle (g_hThreads[i]);

			// �ر������¼����
			CloseHandle (g_hExitEvent);
			CloseHandle (g_hOnlineEvent);
			CloseHandle (g_hAutoChatEvent);
			CloseHandle (g_hAutoOnHookEvent);

			// �رնԻ���
			EndDialog (hWnd, id);

			break;

		case IDOK:
			break;
	}
}

INT_PTR WINAPI Dlg_Proc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {
		// ��ʼ���Ի���
		HANDLE_DLGMSG (hWnd, WM_INITDIALOG, Dlg_OnInitDialog);
		// ����������Ϣ
		HANDLE_DLGMSG (hWnd, WM_COMMAND, Dlg_OnCommand);
		// ʵʱ����
		HANDLE_DLGMSG (hWnd, WM_TIMER, Cls_OnTimer);
		// ����֪ͨ��Ϣ
		HANDLE_DLGMSG (hWnd, WM_NOTIFY, Dlg_OnNotify);
	}

	return(FALSE);
}

///////////////////////////////////////////////////////////////////////////////

int WINAPI _tWinMain (HINSTANCE hinstExe, HINSTANCE, PTSTR pszCmdLine, int)
{
	g_hInstExe = hinstExe;

	// �����Ի���
	DialogBoxParam (hinstExe, MAKEINTRESOURCE (IDD_DLG),
		NULL, Dlg_Proc, NULL);

	return(0);
}
