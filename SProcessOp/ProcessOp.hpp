/*
�ļ�����ProcessOp.hpp
���ܣ�	��װ��Process��ö�٣�����ID������Ļ�ȡ
�ļ��������ڣ�	2015-06-03
���ߣ�KigKrazy
*/
#ifndef WINDOW_PROCESSOP_HPP_ 
#define WINDOW_PROCESSOP_HPP_ 
#include <iostream>
#include <windows.h>
#include <string>
#include <tchar.h>
#include <list> 
//include <xstring>
#include <tlhelp32.h>
#include "Psapi.h"
#pragma  comment (lib, "psapi.lib")

using namespace std;



typedef struct ProcessInfo { 
	DWORD dwProcessId;
	wstring wstrProcessName; 
	wstring wstrFullPath;
	//wstring m_class; 
}PROCESSINFO, *PPROCESSINFO;


class CProcessOP
{
private:


protected:
	BOOL DosPathToNtPath(LPTSTR pszDosPath, LPTSTR pszNtPath)
	{
		TCHAR			szDriveStr[500];
		TCHAR			szDrive[3];
		TCHAR			szDevName[100];
		INT				cchDevName;
		INT				i;

		//������
		if (!pszDosPath || !pszNtPath)
			return FALSE;

		//��ȡ���ش����ַ���
		if (GetLogicalDriveStrings(sizeof(szDriveStr), szDriveStr))
		{
			for (i = 0; szDriveStr[i]; i += 4)
			{
				if (!lstrcmpi(&(szDriveStr[i]), TEXT("A:\\")) || !lstrcmpi(&(szDriveStr[i]), TEXT("B:\\")))
					continue;

				szDrive[0] = szDriveStr[i];
				szDrive[1] = szDriveStr[i + 1];
				szDrive[2] = '\0';
				if (!QueryDosDevice(szDrive, szDevName, 100))//��ѯ Dos �豸��
					return FALSE;

				cchDevName = lstrlen(szDevName);
				if (_tcsnicmp(pszDosPath, szDevName, cchDevName) == 0)//����
				{
					lstrcpy(pszNtPath, szDrive);//����������
					lstrcat(pszNtPath, pszDosPath + cchDevName);//����·��

					return TRUE;
				}
			}
		}

		lstrcpy(pszNtPath, pszDosPath);

		return FALSE;
	}


	wstring GetProcessFullPath(DWORD dwPid)
	{
		wchar_t wszImagePath[MAX_PATH] = {0};
		wstring wstrRes = L"";
		HANDLE  hProcess;
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, dwPid);
		if (!hProcess)
		{
			return wstrRes;
		}

		if (!GetProcessImageFileNameW(hProcess, wszImagePath, MAX_PATH))
		{
			CloseHandle(hProcess);
			return FALSE;
		}

		if (!DosPathToNtPath(wszImagePath, wstrRes))
		{
			CloseHandle(hProcess);
			return wstrRes;
		}

/*
		GetModuleFileNameEx(hProcess, NULL, wszImagePath, MAX_PATH + 1);
		if (wcslen(wszImagePath))
		{
			wstrRes = wszImagePath;
		}
		if (hProcess)
		{
			CloseHandle(hProcess);
		}*/
		return wstrRes;
	}

public:
	list<wchar_t *> m_lsProcessName;

	list<PROCESSINFO> GetCurProcessList()
	{
		list<PROCESSINFO> lsProcess;
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (INVALID_HANDLE_VALUE == hSnapshot) return lsProcess;
		PROCESSENTRY32 ProcessInfo = { 0 };
		ProcessInfo.dwSize = sizeof(PROCESSENTRY32);
		BOOL bRes = Process32First(hSnapshot, &ProcessInfo);
		while (bRes) {
			//hModule = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pinfo->th32ProcessID);
			//Module32First(hModule, minfo);
			//GetShortPathName(minfo->szExePath, shortpath, 256);
			//printf("%s --- %s ", pinfo->szExeFile, shortpath);
			//lsProcess.push_back(ProcessInfo.szExeFile);
			if (0 != ProcessInfo.th32ProcessID && 4 != ProcessInfo.th32ProcessID)
			{
				PROCESSINFO pi;
				pi.wstrProcessName = ProcessInfo.szExeFile;
				pi.dwProcessId = ProcessInfo.th32ProcessID;
				pi.wstrFullPath = GetProcessFullPath(ProcessInfo.th32ProcessID);
 				lsProcess.push_back(pi);
			}
			bRes = Process32Next(hSnapshot, &ProcessInfo);
		}
		CloseHandle(hSnapshot);
		return lsProcess;
	}

	//=========================================
	// ������: EnableDebugPrivilege
	// ��   ��: BOOL - �ɹ�:TRUE, ʧ��:FALSE
	// ��   ��: ����/�ָ�Ȩ��
	// ��   ������ʾȨ������һ��ʹ��SE_DEBUG_NAME����ȡ����Ȩ�ޣ���Ϊ���������
	// Ϊ���������������в���MSDN��
	//=========================================
	bool EnableDebugPriv(const TCHAR * _tszName)
	{
		//SE_DEBUG_NAME
		HANDLE hToken;
		TOKEN_PRIVILEGES tp;
		LUID luid;
		//�򿪽������ƻ�
		if (!OpenProcessToken(GetCurrentProcess(),//ȡ�þ�������� OpenProcessToken()����
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
			&hToken))
		{
			printf("OpenProcessToken error./n");
			CloseHandle(hToken);
			return false;
		}
		//��ý��̱���ΨһID
		if (!LookupPrivilegeValue(NULL, _tszName, &luid))//һ��Ȩ�޶�Ӧ��LUIDֵ
		{
			printf("LookupPrivilege error!/n");
		}
		tp.PrivilegeCount = 1;
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		tp.Privileges[0].Luid = luid;
		//����Ȩ��
		if (!AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))//����AdjustTokenPrivileges������������ƽ����޸�
		{
			printf("AdjustTokenPrivileges error!/n");
			CloseHandle(hToken);
			return false;
		}
		CloseHandle(hToken);
		return true;
	}
	//=========================================
	// ������: DisableDebugPrivilege
	// ��   ��: BOOL - �ɹ�:TRUE, ʧ��:FALSE
	// ��   ��: �Ƴ�Ȩ��
	// ��   ������ʾȨ������
	//=========================================
	int DisableDebugPriv(const TCHAR * _tszName)
	{
		HANDLE hToken;
		TOKEN_PRIVILEGES tp;
		LUID luid;
		//�򿪽������ƻ�
		if (!OpenProcessToken(GetCurrentProcess(),//ȡ�þ�������� OpenProcessToken()����
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
			&hToken))
		{
			//printf("OpenProcessToken error./n");
			CloseHandle(hToken);
			return false;
		}
		//��ý��̱���ΨһID
		if (!LookupPrivilegeValue(NULL, _tszName, &luid))//һ��Ȩ�޶�Ӧ��LUIDֵ
		{
			printf("LookupPrivilege error!/n");
		}
		tp.PrivilegeCount = 1;
		tp.Privileges[0].Attributes = SE_PRIVILEGE_REMOVED;
		tp.Privileges[0].Luid = luid;
		//����Ȩ��
		if (!AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))//����AdjustTokenPrivileges������������ƽ����޸�
		{
			printf("AdjustTokenPrivileges error!/n");
			CloseHandle(hToken);
			return false;
		}
		CloseHandle(hToken);
		return true;
	}
};

#endif 