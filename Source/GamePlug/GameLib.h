#pragma once

// ��Ϸ��չ����
struct GAME_DATA_EX
{
	DWORD ID;
	DWORD RandomID;
	TCHAR Name[64];
	DWORD HP;
	DWORD MaxHP;
	DWORD MP;
	DWORD MaxMP;
	DWORD Attack;
	DWORD MaxAttack;
	DWORD Hit;
	DWORD Avoid;
	DWORD Armor;
	float X;
	float H;
	float Y;
	DWORD Level;
	DWORD Type;
};

// Npc��Ϣ������
enum NpcType
{
	NpcMonster = 6,
	NpcPerson = 7
};

/*
���ܣ���ȡ��Ϸ����ĳ����Ϣ
������
	GameData	������Ϣ, �ɵ��÷��ṩ�ռ�
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool GetPlayerInfo (std::vector<GAME_DATA_EX>& vectGameData);

/*
���ܣ���ʱ����ʾ�����Ϣ
��������
���أ���
*/
void TimerDisplayPlayerInfo ();

/*
���ܣ���ȡNpc��Ϣ
������
	vectGameData	������Ϣ������, �ɵ��÷��ṩ�ռ�
	bShow			true = ֱ����ʾ��Ϣ ; false = ����ʾ��Ϣ
	bSel			true = ѡ���Npc��Ϣ ; false = ��ѡ��Npc��Ϣ
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool GetNpcInfo (std::vector<GAME_DATA_EX>& vectGameData, bool bShow, bool bSel = false);

/*
���ܣ���ȡ������Ʒ��Ϣ
������
	vectGameData	������Ϣ������, �ɵ��÷��ṩ�ռ�
	bShow			true = ֱ����ʾ��Ϣ ; false = ����ʾ��Ϣ
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool GetFloorInfo (std::vector<GAME_DATA_EX>& vectGameData, bool bShow);

/*
���ܣ���ȡ���������Ϣ
������
	vectGameData	������Ϣ������, �ɵ��÷��ṩ�ռ�
	bShow			true = ֱ����ʾ��Ϣ ; false = ����ʾ��Ϣ
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool GetOtherPlayers (std::vector<GAME_DATA_EX>& vectGameData, bool bShow);

/*
���ܣ�����Զ�̹���
������
	pvContext	���������������ָ��
	dwSize		����������ֽ���
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool RemoteCall (PVOID pvContext, DWORD dwSize);

/*
���ܣ����ð�������
������
	dwCol		���ּ��͹��ܼ��İ�����
	dwIndex		���ּ��͹��ܼ��ı��
	bFn			ָ�� true = ���ܼ� ; false = ���ּ�
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool Accelerator (DWORD dwCol, DWORD dwIndex, BOOL bFn);

/*
���ܣ����ô�������
��������
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool Restore ();

/*
���ܣ��������ܹ���
��������
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool Run ();

/*
���ܣ������չ�����
��������
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool Attack ();

/*
���ܣ�������� ; ��� ; ��̯�ȹ���
������
	dwCallIndex		������������
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool Actions (DWORD dwCallIndex);

/*
���ܣ����ñ��鶯������
������
	dwFaceIndex	������������
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool Face (DWORD dwFaceIndex);

/*
���ܣ����õ���tabѡ�����npc����
��������
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool SelectBeast ();

/*
���ܣ����������سǹ���
��������
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool DeathReturn ();

/*
���ܣ������Զ���ҩ����
������
	bRed		true = ��ҩ ; false = ��ҩ
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool Supplement (bool bRed);

/*
���ܣ����ü��ܹ���
������
	dwSkillID	���ܱ��
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool Skill (DWORD dwSkillID);

/*
���ܣ����ü��ܹ���
������
	pChatText	�������������Զ��ָ��
	dwChatLevel	����Ƶ��
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool SendChat (PCTSTR pChatText, DWORD dwChatLevel);

/*
���ܣ��������߹���
������
	x			Ŀ������x
	y			Ŀ������y
	bAuto		true = �Զ�Ѱ· ; false = ��ͨ�ƶ�
���أ��ɹ�ִ��Ϊtrue ������Ϊfalse
*/
bool GoToXY (FLOAT x, FLOAT y, BOOL bAuto);

/*
���ܣ���Ϸ�����Ƿ����
������
	szProcessName	��Ϸ������
���أ����̴���Ϊtrue , ���̲�����Ϊfalse
*/
bool IsExistProcess (PCTSTR szProcessName);

/*
���ܣ���Ϸ�����Ƿ񱻿��Ʋ���ʾ������Ϣ
������
	hWnd	������ʾ��Ϣ���ڵ�HWND
���أ���
*/
void ProcessControl (HWND hWnd);

/*
���ܣ���Ϸ�����Ƿ�����
��������
���أ�����Ϊtrue , ����Ϊfalse
*/
bool IsOnline ();


/*
���ܣ��̰߳�ȫ�˳�
������
	hTheads		��Ҫ�رյ��߳̾��ָ��
	threadCount ���ָ��ĸ���
���أ���
*/void WaitForThreadQuit (HANDLE hTheads[], int threadCount);

/*
���ܣ������Ϸ���̼���Ϸ�����Ƿ��¼���̺߳���
������
	hWnd	������ʾ��Ϣ���ڵ�HWND
���أ��ɹ�ִ��Ϊtrue ������δ����
*/
DWORD __stdcall AutoTestThread (HWND hWnd);

/*
���ܣ��Զ���ʾ���״̬��Ϣ���̺߳���
������
	hWnd	������ʾ��Ϣ���ڵ�HWND
���أ��ɹ�ִ��Ϊtrue ������δ����
*/
DWORD __stdcall AutoInfoThread (HWND hWnd);

/*
���ܣ��Զ�������̺߳���
������
	hWnd	�����ȡ��Ϣ���ڵ�HWND
���أ��ɹ�ִ��Ϊtrue ������δ����
*/
DWORD __stdcall AutoChatThread (HWND hWnd);

/*
���ܣ��Զ��һ����̺߳���
������
	hWnd	������ʾ��Ϣ���ڵ�HWND
���أ��ɹ�ִ��Ϊtrue ������δ����
*/
DWORD __stdcall AutoOnHookThread (HWND hWnd);