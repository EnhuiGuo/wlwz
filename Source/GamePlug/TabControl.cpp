#include "CommandInfo.h"

const DWORD g_dwPageMax = 6;
HWND g_hPages[g_dwPageMax];

INT_PTR WINAPI Dlg_Child (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	bool bRet = false;

	switch (uMsg) {
		case WM_COMMAND: {
			switch (LOWORD (wParam))
			{
				/////////////////////////////////////////////////////////
				// ��ݼ�������뿪ʼ
				/////////////////////////////////////////////////////////
				case IDC_ACCELERATOR_F1: case IDC_ACCELERATOR_F2: 
				case IDC_ACCELERATOR_F3: case IDC_ACCELERATOR_F4:
				case IDC_ACCELERATOR_F5: case IDC_ACCELERATOR_F6: 
				case IDC_ACCELERATOR_F7: case IDC_ACCELERATOR_F8:
				case IDC_ACCELERATOR_1: case IDC_ACCELERATOR_2: 
				case IDC_ACCELERATOR_3: case IDC_ACCELERATOR_4: 
				case IDC_ACCELERATOR_5:	case IDC_ACCELERATOR_6: 
				case IDC_ACCELERATOR_7: case IDC_ACCELERATOR_8: 
				case IDC_ACCELERATOR_9: case IDC_ACCELERATOR_0:
				{
					BOOL bFn = LOWORD (wParam) <= IDC_ACCELERATOR_F8;
					DWORD dwIndex = bFn ? (LOWORD (wParam) - IDC_ACCELERATOR_F1)
						: (LOWORD (wParam) - IDC_ACCELERATOR_1);
					DWORD dwCol = bFn ? (SendDlgItemMessage (g_hPages[1], IDC_ACCELERATOR_FN, CB_GETCURSEL, 0, 0) + 1)
						: (SendDlgItemMessage (g_hPages[1], IDC_ACCELERATOR_N, CB_GETCURSEL, 0, 0) + 1);

					if (!(bRet = Accelerator (dwCol, dwIndex, bFn)))
						MsgBox (TEXT ("��ݼ�û��ִ��"));

					break;
				} // IDC_F1 ~ IDC_F8
				/////////////////////////////////////////////////////////
				// ѡ�ִ�����뿪ʼ
				/////////////////////////////////////////////////////////
				case IDC_ACCELERATOR_SELECT_BEAST: {
					if (!(bRet = SelectBeast ()))
						MsgBox (TEXT ("ѡ��û��ִ��"));

					break;
				} // case IDC_SELECT_BEAST
				/////////////////////////////////////////////////////////
				// �����سǴ�����뿪ʼ
				/////////////////////////////////////////////////////////
				case IDC_ACCELERATOR_DEATH_RETURN: {
					if (!(bRet = DeathReturn ()))
						MsgBox (TEXT ("�����س�û��ִ��"));

					break;
				} // case IDC_ACCELERATOR_DEATH_RETURN
				/////////////////////////////////////////////////////////
				// �Զ���ҩ������뿪ʼ
				/////////////////////////////////////////////////////////
				case IDC_ACCELERATOR_SUPPLEMENT_RED:
				case IDC_ACCELERATOR_SUPPLEMENT_BLUE: {
					MsgBox (TEXT ("�˹���Ϊ�Զ���������\r\n����������׸��ӷ���[��ҩ]��[����˪"));
					if (!(bRet = Supplement ((LOWORD (wParam) == IDC_ACCELERATOR_SUPPLEMENT_RED))))
						MsgBox (TEXT ("û��ҩ��"));

					break;
				} // case IDC_ACCELERATOR_SUPPLEMENT_RED
				/////////////////////////////////////////////////////////
				// ���ܴ�����뿪ʼ
				/////////////////////////////////////////////////////////
				case IDC_ACCELERATOR_SKILL_QFP:
				case IDC_ACCELERATOR_SKILL_ZLJ:
				case IDC_ACCELERATOR_SKILL_BACKCITY: {
					DWORD dwSkillIds[] = {
						2,3,78
					};
					if (!(bRet = Skill (dwSkillIds[LOWORD(wParam)-
						IDC_ACCELERATOR_SKILL_QFP])))
						MsgBox (TEXT ("����û��ִ��"));
					break;
				} // IDC_ACCELERATOR_SKILL_XX

				/////////////////////////////////////////////////////////
				// ���촦����뿪ʼ
				/////////////////////////////////////////////////////////
				case IDC_CHATSEND: {
					const DWORD dwTextSize = 80;
					TCHAR szChatText[dwTextSize]{};
					DWORD dwChatLevel = SendDlgItemMessage (g_hPages[2], IDC_CHATLEVEL, CB_GETCURSEL, 0, 0);
					if (0 != dwChatLevel) 
						StringCchCopy (szChatText, dwTextSize, TEXT ("!!"));

					if (0 != SendDlgItemMessage (g_hPages[2],
						IDC_CHATCONTENT, WM_GETTEXT, dwTextSize - _tcslen (szChatText),
						(LPARAM)(szChatText + _tcslen (szChatText)))) {
						if (!(bRet = SendChat (szChatText, dwChatLevel)))
							MsgBox (TEXT ("����û��ִ��"));
					}


					break;
				} // case IDC_CHATSEND
				case IDC_AUTO_CHAT: {
					UINT uCheckStatus = 0;
					uCheckStatus = Button_GetCheck (GetDlgItem (hwnd, IDC_AUTO_CHAT));
					
					if (BST_CHECKED == uCheckStatus) {
						const DWORD dwTextSize = 80;
						TCHAR szChatText[dwTextSize]{};
						if (0 == SendDlgItemMessage (hwnd, IDC_CHATCONTENT, WM_GETTEXT, dwTextSize, (LPARAM)szChatText) ||
							0 == SendDlgItemMessage (hwnd, IDC_INTERVAL_TIME, WM_GETTEXT, dwTextSize, (LPARAM)szChatText)) {
							MsgBox (TEXT ("��Ҫ��д�������ݺͼ��ʱ��!"));
							CheckDlgButton (hwnd, IDC_AUTO_CHAT, BST_UNCHECKED);
							break;
						}

						EnableWindow (GetDlgItem (hwnd, IDC_CHATCONTENT), false);
						EnableWindow (GetDlgItem (hwnd, IDC_INTERVAL_TIME), false);
						SetEvent (g_hAutoChatEvent);
					}
					else {
						EnableWindow (GetDlgItem (hwnd, IDC_CHATCONTENT), true);
						EnableWindow (GetDlgItem (hwnd, IDC_INTERVAL_TIME), true);
						ResetEvent (g_hAutoChatEvent);
					}

					break;
				} // case IDC_AUTO_CHAT

				/////////////////////////////////////////////////////////
				// ����������뿪ʼ
				/////////////////////////////////////////////////////////
				case IDC_ACTION_ATTACK: {		//�չ�
					if (!(bRet = Attack ())) {
						MsgBox (TEXT ("�չ�û��ִ��"));
					}
					break;
				} //case IDC_ACTION_ATTACK
				case IDC_ACTION_RUN: {			//����
					if (!(bRet = Run ())) {
						MsgBox (TEXT ("����û��ִ��"));
					}
					break;
				} //case IDC_ACTION_RUN
				case IDC_ACTION_REST: {			//����
					if (!(bRet = Restore ())) {
						MsgBox (TEXT ("����û��ִ��"));
					}
					break;
				} //case IDC_ACTION_REST
				case IDC_ACTION_ASSISTS: 		//����
				case IDC_ACTION_TEAM: 			//���
				case IDC_ACTION_LEAVE:			//���
				case IDC_ACTION_DEAL: 			//����
				case IDC_ACTION_STALL:			//��̯
				case IDC_ACTION_PICK: {			//ʰȡ
					if (!(bRet = Actions (LOWORD (wParam) - IDC_ACTION_ASSISTS))) {
						MsgBox (TEXT ("����û��ִ��"));
					}
					break;
				} //case IDC_ACTION_ASSISTS

				case IDC_ACTION_FACE_00:
				case IDC_ACTION_FACE_01:
				case IDC_ACTION_FACE_02:
				case IDC_ACTION_FACE_03:
				case IDC_ACTION_FACE_04:
				case IDC_ACTION_FACE_05:
				case IDC_ACTION_FACE_06:
				case IDC_ACTION_FACE_07:
				case IDC_ACTION_FACE_08:
				case IDC_ACTION_FACE_09:
				case IDC_ACTION_FACE_10: {		//����	
					if (!(bRet = Face (LOWORD (wParam) - IDC_ACTION_FACE_00))) {
						MsgBox (TEXT ("����û��ִ��"));
					}
					break;
				} //case IDC_ACTION_RUN

				case IDC_MOVEAUTOGOTO:
				case IDC_MOVEGOTO: {			//�ƶ�
					const DWORD dwTextSize = 10;
					TCHAR szBuffer[dwTextSize]{};
					float x, y;
					bool bOK = false;

					if (0 != SendDlgItemMessage (g_hPages[4],
						IDC_MOVEX, WM_GETTEXT, dwTextSize, (LPARAM)szBuffer)) {
						x = static_cast<float>(_ttof (szBuffer));
						bOK = true;
					}
					else {
						MsgBox (TEXT ("û����дX����"));
						
					}
					
					if (bOK && 0 != SendDlgItemMessage (g_hPages[4],
						IDC_MOVEY, WM_GETTEXT, dwTextSize, (LPARAM)szBuffer)) {
						y = static_cast<float>(_ttof (szBuffer));
					}
					else {
						MsgBox (TEXT ("û����дY����"));
						bOK = false;
					}

					if (bOK) {
						if (!(bRet = GoToXY (x, y, (LOWORD (wParam) == IDC_MOVEAUTOGOTO)))) {
							MsgBox (TEXT ("�ƶ�û��ִ��"));
						}
					}

					break;
				} // case IDC_MOVEGOTO
				
				/////////////////////////////////////////////////////////
				// �Զ��һ�������뿪ʼ
				/////////////////////////////////////////////////////////
				case IDC_HOOKSTART: {
					const DWORD dwTextSize = 4;
					TCHAR szMinHp[dwTextSize] = {};
					if (0 == SendDlgItemMessage (hwnd, IDC_HP_MIN, WM_GETTEXT, dwTextSize, (LPARAM)szMinHp)) {
						MsgBox (TEXT ("��СѪ��������д��С�ڵ���3���ַ�"));
						break;
					}

					std::vector<GAME_DATA_EX> vect;
					if (!GetPlayerInfo (vect)) {
						MsgBox (TEXT ("�����Ϣ��ȡʧ��!"));
						break;
					}

					DWORD dwMinHp = 0;
					dwMinHp = _tcstol (szMinHp, nullptr, 10);
					if (dwMinHp < 20 || dwMinHp > vect.back ().MaxHP) {
						MsgBox (TEXT ("��СѪ���������20��С�ڵ������Ѫ��"));
						break;
					}

					SetEvent (g_hAutoOnHookEvent);
					EnableWindow (GetDlgItem (hwnd, IDC_HOOKSTOP), true);
					EnableWindow (GetDlgItem (hwnd, IDC_HOOKSTART), false);

					break;
				} // case IDC_HOOKSTART

				case IDC_HOOKSTOP: {
					ResetEvent (g_hAutoOnHookEvent);
					EnableWindow (GetDlgItem (hwnd, IDC_HOOKSTOP), false);
					EnableWindow (GetDlgItem (hwnd, IDC_HOOKSTART), true);
					break;
				} // IDC_HOOKSTOP

				/////////////////////////////////////////////////////////
				// ��ѯ��Ϣ������뿪ʼ
				/////////////////////////////////////////////////////////
				case IDC_NPCINFO: {	// Npc��Ϣ
					std::vector<GAME_DATA_EX> vect;
					if (!(bRet = GetNpcInfo (vect, true))) {
						MsgBox (TEXT ("��ʾNpc�޻�û��ִ��"));
					}

					break;
				} // case IDC_NPCINFO:

				case IDC_FLOORINFO: {	// ������Ϣ
					std::vector<GAME_DATA_EX> vect;
					if (!(bRet = GetFloorInfo (vect, true))) {
						MsgBox (TEXT ("��ʾ������Ʒ�޻�û��ִ��"));
					}

					break;
				} // case IDC_FLOORINFO

				case IDC_OTHERPLAYER: {	// �������
					std::vector<GAME_DATA_EX> vect;
					if (!(bRet = GetOtherPlayers (vect, true))) {
						MsgBox (TEXT ("��ʾ��������޻�û��ִ��"));
					}

					break;
				} // case IDC_OTHERPLAYER

			} // switch (LOWORD (wParam))
		} // case WM_COMMAND
	} // switch (uMsg)

	return(bRet);
}

BOOL Dlg_OnNotify (HWND hwnd, INT id, LPNMHDR pnm)
{
	int        i;

	BOOL bRet = FALSE;

	if (pnm->code == TCN_SELCHANGE)
	{
		i = SendDlgItemMessage (hwnd, IDC_GAME_INFO, TCM_GETCURSEL, 0, 0);

		for (int ct = 0; ct < g_dwPageMax; ct++)
		{
			ShowWindow (g_hPages[ct], FALSE);	//�ٶ�����ʾ
			if (ct == i) {
				ShowWindow (g_hPages[i], TRUE); //��ʾPage iҳ
				bRet = TRUE;
			}
		}

		if (2 == i) {
			SendDlgItemMessage (g_hPages[i],
				IDC_CHATLEVEL, CB_RESETCONTENT, 0, 0); 
			SendDlgItemMessage (g_hPages[i],
				IDC_CHATLEVEL, CB_ADDSTRING, 0, (LPARAM)TEXT ("����"));
			SendDlgItemMessage (g_hPages[i],
				IDC_CHATLEVEL, CB_ADDSTRING, 0, (LPARAM)TEXT ("����"));
			SendDlgItemMessage (g_hPages[i],
				IDC_CHATLEVEL, CB_SETCURSEL, 0, 0);
		}
		
		if (1 == i) {
			SendDlgItemMessage (g_hPages[i],
				IDC_ACCELERATOR_FN, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage (g_hPages[i],
				IDC_ACCELERATOR_FN, CB_ADDSTRING, 0, (LPARAM)TEXT ("���ܼ�һ��"));
			SendDlgItemMessage (g_hPages[i],
				IDC_ACCELERATOR_FN, CB_ADDSTRING, 0, (LPARAM)TEXT ("���ܼ�����"));
			SendDlgItemMessage (g_hPages[i],
				IDC_ACCELERATOR_FN, CB_ADDSTRING, 0, (LPARAM)TEXT ("���ܼ�����"));
			SendDlgItemMessage (g_hPages[i],
				IDC_ACCELERATOR_FN, CB_SETCURSEL, 0, 0);
			
			SendDlgItemMessage (g_hPages[i],
				IDC_ACCELERATOR_N, CB_RESETCONTENT, 0, 0);
			SendDlgItemMessage (g_hPages[i],
				IDC_ACCELERATOR_N, CB_ADDSTRING, 0, (LPARAM)TEXT ("���ּ�һ��"));
			SendDlgItemMessage (g_hPages[i],
				IDC_ACCELERATOR_N, CB_ADDSTRING, 0, (LPARAM)TEXT ("���ּ�����"));
			SendDlgItemMessage (g_hPages[i],
				IDC_ACCELERATOR_N, CB_ADDSTRING, 0, (LPARAM)TEXT ("���ּ�����"));
			SendDlgItemMessage (g_hPages[i],
				IDC_ACCELERATOR_N, CB_SETCURSEL, 0, 0);
		}

		if (0 == i) SetEvent (g_hAutoInfoEvent);
		else ResetEvent (g_hAutoInfoEvent);
	}

	return bRet;
}