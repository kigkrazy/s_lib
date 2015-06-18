/*
文件名：ProcessOp.hpp
功能：	包装对Process的枚举，进程ID，句柄的获取
文件创建日期：	2015-06-03
作者：KigKrazy
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

		//检查参数
		if (!pszDosPath || !pszNtPath)
			return FALSE;

		//获取本地磁盘字符串
		if (GetLogicalDriveStrings(sizeof(szDriveStr), szDriveStr))
		{
			for (i = 0; szDriveStr[i]; i += 4)
			{
				if (!lstrcmpi(&(szDriveStr[i]), TEXT("A:\\")) || !lstrcmpi(&(szDriveStr[i]), TEXT("B:\\")))
					continue;

				szDrive[0] = szDriveStr[i];
				szDrive[1] = szDriveStr[i + 1];
				szDrive[2] = '\0';
				if (!QueryDosDevice(szDrive, szDevName, 100))//查询 Dos 设备名
					return FALSE;

				cchDevName = lstrlen(szDevName);
				if (_tcsnicmp(pszDosPath, szDevName, cchDevName) == 0)//命中
				{
					lstrcpy(pszNtPath, szDrive);//复制驱动器
					lstrcat(pszNtPath, pszDosPath + cchDevName);//复制路径

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
	// 函数名: EnableDebugPrivilege
	// 输   出: BOOL - 成功:TRUE, 失败:FALSE
	// 功   能: 提升/恢复权限
	// 参   数：表示权限名！一般使用SE_DEBUG_NAME（获取调试权限）作为传入参数，
	// 为其他参数名请自行查阅MSDN。
	//=========================================
	bool EnableDebugPriv(const TCHAR * _tszName)
	{
		//SE_DEBUG_NAME
		HANDLE hToken;
		TOKEN_PRIVILEGES tp;
		LUID luid;
		//打开进程令牌环
		if (!OpenProcessToken(GetCurrentProcess(),//取得句柄的令牌 OpenProcessToken()函数
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
			&hToken))
		{
			printf("OpenProcessToken error./n");
			CloseHandle(hToken);
			return false;
		}
		//获得进程本地唯一ID
		if (!LookupPrivilegeValue(NULL, _tszName, &luid))//一个权限对应的LUID值
		{
			printf("LookupPrivilege error!/n");
		}
		tp.PrivilegeCount = 1;
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		tp.Privileges[0].Luid = luid;
		//调整权限
		if (!AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))//调用AdjustTokenPrivileges对这个访问令牌进行修改
		{
			printf("AdjustTokenPrivileges error!/n");
			CloseHandle(hToken);
			return false;
		}
		CloseHandle(hToken);
		return true;
	}
	//=========================================
	// 函数名: DisableDebugPrivilege
	// 输   出: BOOL - 成功:TRUE, 失败:FALSE
	// 功   能: 移除权限
	// 参   数：表示权限名！
	//=========================================
	int DisableDebugPriv(const TCHAR * _tszName)
	{
		HANDLE hToken;
		TOKEN_PRIVILEGES tp;
		LUID luid;
		//打开进程令牌环
		if (!OpenProcessToken(GetCurrentProcess(),//取得句柄的令牌 OpenProcessToken()函数
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
			&hToken))
		{
			//printf("OpenProcessToken error./n");
			CloseHandle(hToken);
			return false;
		}
		//获得进程本地唯一ID
		if (!LookupPrivilegeValue(NULL, _tszName, &luid))//一个权限对应的LUID值
		{
			printf("LookupPrivilege error!/n");
		}
		tp.PrivilegeCount = 1;
		tp.Privileges[0].Attributes = SE_PRIVILEGE_REMOVED;
		tp.Privileges[0].Luid = luid;
		//调整权限
		if (!AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))//调用AdjustTokenPrivileges对这个访问令牌进行修改
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