#pragma once

#ifdef UNICODE
using _tstring = std::wstring;
#else
using _tstring = std::string;
#endif // UNICODE

#define THROW()	throw CException (__FUNCTION__, __LINE__, GetLastError ())



class CProcessData
{

	typedef DWORD (WINAPI *PFNTCREATETHREADEX) (
		PHANDLE                 ThreadHandle,
		ACCESS_MASK             DesiredAccess,
		LPVOID                  ObjectAttributes,
		HANDLE                  ProcessHandle,
		LPTHREAD_START_ROUTINE  lpStartAddress,
		LPVOID                  lpParameter,
		BOOL                    CreateSuspended,
		DWORD                   dwStackSize,
		DWORD                   dw1,
		DWORD                   dw2,
		LPVOID                  Unknown
		);

private:
	// Ŀ�괰�ھ��
	HWND m_hWnd;
	// Ŀ����̾��
	HANDLE m_hProcess;
	// Ŀ�����ID
	DWORD m_dwProcessId;
	// Ŀ����̵��߳̾��
	DWORD m_dwThreadId;
	// Ŀ����̿ռ��ַ
	DWORD m_dwOffset;
	// ע��DLL��Ŀ������е�ģ���ַ
	DWORD m_dwModule;
	// ע��DLL������Զ�̵��ú�����Ŀ������еĵ�ַ
	PTHREAD_START_ROUTINE m_pfnThreadRtn;
	// ע��DLL��·�����ļ���
	_tstring m_strLibFile;
	// Զ���̺߳�����
	std::string m_strFunction;
	// ע����
	bool m_bInject;

private:
	// ��ʼ����Ա
	void Init ();
	// �ж�Windows�汾
	bool IsVistaOrLater ();
	// ���ñ������������߳�
	HANDLE NtCreateRemoteThread (PTHREAD_START_ROUTINE pThreadProc, PVOID pContext);

public:
	CProcessData (const CProcessData&) = delete;
	CProcessData& operator=(const CProcessData&) = delete;
	
	// ���캯��
	// ����:	��ʼ�����ݳ�Ա
	CProcessData ()
	{
		//OutputDebugString (L"����\n");
		Init ();
	};
	
	// ��������
	// ����:	����Ѻ͹رվ����
	~CProcessData () {
		DetachProcess ();
		//OutputDebugString (L"����\n");
	};

public:
	// ����Ŀ����̲���ʼ��
	// ����:	����Ŀ����̲��򿪻�ȡ����ID�ͽ��̾��
	// ����:	�ɹ�����true, ʧ�ܵ���false
	// ����:	strTitle	Ŀ����̴��ڱ���
	//		strClass	Ŀ����̴�������
	bool AttachProcess (const _tstring& strTitle, const _tstring& strClass);
	
	// ����Ŀ����̲�����
	// ����:	����Ŀ����̲��򿪻�ȡ����ID�ͽ��̾��
	// ����:	�ɹ�����true, ʧ�ܵ���false
	// ����:	strTitle	Ŀ����̴��ڱ���
	//		strClass	Ŀ����̴�������
	void DetachProcess ();

	// ���õ���Ȩ��
	// ����:	���õ���Ȩ��
	// ����:	�ɹ�����true, ʧ�ܵ���false
	// ����:	bEnable true���� false����
	bool EnableDebugPrivilege (bool bEnable);

	// ע��DLL
	// ����:	��ָ�����Ƶ�DLLע�뵽Ŀ����̲�����DLL���Ƶ����ݳ�Ա
	// ����:	�ɹ�����true, ʧ�ܵ���false
	// ����:	strLibFile	ע��DLL��·�����ļ���
	bool InjectLib (const _tstring& strLibFile = TEXT ("\\InjectLib.dll"));
	
	// ע��DLL
	// ����:	��Ŀ�����ж��֮ǰע���DLL
	// ����:	�ɹ�����true, ʧ�ܵ���false
	// ����:	��
	bool EjectLib ();

	// Զ�̵���
	// ����:	����ע��DLL�ĵ���Զ�̺���
	// ����:	�ɹ�����true, ʧ�ܵ���false
	// ����:	pvContext	���ù�������Ҫ�Ĳ���, ����ΪNULL
	//		dwSize		pvContext�������ֽ���, ���pvContext����NULL, �ò���������
	//		strFunction	Զ�̺����ĵ�������
	bool RemoteCall (PVOID pvContext, DWORD dwSize, const std::string& strFunction = "GameCommand");

	// д�ڴ�
	// ����:	д���ݵ�Զ�̽���
	// ����:	�ɹ�����true, ʧ�ܵ���false
	// ����:	pvData		Ԥд��ı�������
	//		dwSize		pvData���ֽ���
	//		pvOffset	Ԥд���Զ��ƫ��
	bool WriteMem (PVOID pvData, DWORD dwSize, PVOID pvOffset);
	
	// ���ڴ�
	// ����:	д���ݵ�Զ�̽���
	// ����:	�ɹ�����true, ʧ�ܵ���false
	// ����:	pvData		Ԥ��ȡ�ı��ػ�����
	//		dwSize		pvData���ֽ���
	//		dwOffset	Ԥ��ȡ��Զ��ƫ��
	bool ReadMem (PVOID pvData, DWORD dwSize, DWORD dwOffset = 0);

	// ����ƫ��
	// ����:	�������б�ָ����ַ
	// ����:	�ɹ�����true, ʧ�ܵ���false
	// ����:	initOffset	ƫ���б�
	bool UpdateOffset (const std::initializer_list<DWORD>& initOffset);

	// ���º�����Ϥ�ڲ�״̬
	HWND GetHWnd () const;
	HANDLE GetHandle () const;
	DWORD GetProcessId () const;
	DWORD GetThreadId () const;
};

// ������쳣����
class CException
{
private:
	std::string m_function;
	ULONG m_line;
	DWORD m_error;
	bool m_silent;

public:
	CException (const std::string& function, ULONG line, DWORD e, bool silent = true)
		:m_function (function), m_line (line), m_error(e), m_silent(silent) {}
	
	void Trace () const {
		TCHAR msg[128] = {};
		StringCchPrintf (msg, 128, TEXT ("������:%S - ������%d�� - �������:%d\n"), m_function.c_str (), m_line, m_error);
		if (m_silent)
			OutputDebugString (msg);
		else
			MessageBox (nullptr, msg, nullptr, 0);
	}

};
