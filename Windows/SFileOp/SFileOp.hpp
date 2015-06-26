/*
* �ļ�����SFileOp.hpp
* ���ܣ���װһЩ�ļ���д����ز���
* ���ߣ�KigKrazy
* �������ڣ�2015��6��17��23:49:05
* �޸��ˣ�KigKrazy
* �޸����ڣ�2015��6��17��23:49:49
*/
#pragma once
#ifndef SFILE_OP_HPP_
#define SFILE_OP_HPP_
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <string>
#include <io.h>
#include <shlwapi.h>  
#pragma comment(lib,"shlwapi.lib")  
using namespace std;
class CSFileOp
{
public:
	//��ʼ��
	CSFileOp(){}
	
	CSFileOp(const string strFilePath)
	{
		m_strFilePath = strFilePath;
	}
	~CSFileOp(){};


	void SetFilePath(const string strFilePath)
	{
		m_strFilePath = strFilePath;
	}
	/*
	* ��������ReadFile2String
	* ������	
	* ���ܣ�	��ȡ�ļ�����
	* ����ֵ��	���ض�ȡ���ַ�������
	*/
	string ReadFile2String()
	{
		string strReadBuf = "";
		ifstream iStream(m_strFilePath.c_str());  
		if (!iStream.is_open())
		{
#if _DEBUG
			if (-1 == _access(m_strFilePath.c_str(), 00) )
			{
				string strDbg = m_strFilePath + "don't exit!";
				OutputDebugStringA(strDbg.c_str());
			}

			if (-1 == _access(m_strFilePath.c_str(), 06) )
			{
				string strDbg = m_strFilePath + "can't be read!";
				OutputDebugStringA(strDbg.c_str());
			}
#endif
			return strReadBuf;
		}
		stringstream ssAll;
		ssAll << iStream.rdbuf();
		iStream.close();
		strReadBuf = ssAll.str();
		return strReadBuf;
	}

	/*
	* ��������WriteFileFromString
	* ������	strWrite��д���ļ�������(����)
	* ���ܣ�	��strWrite������д���ļ�
	* ����ֵ��TRUEΪ�ɹ� FALSEΪ���ɹ�
	*/
	BOOL WriteFileFromString(const string strWrite)
	{
		ofstream oStream(m_strFilePath.c_str());
		if (!oStream.is_open())
			return FALSE;
		oStream << strWrite.c_str();
		oStream.close();
		return TRUE;
	}

	/*
	* ��������WriteFile2TailFromString
	* ������	strWrite��д���ļ������ݣ�׷�ӵ��ļ�ĩβ��
	* ���ܣ�	��strWrite������д���ļ�
	* ����ֵ��TRUEΪ�ɹ� FALSEΪ���ɹ�
	*/
	bool WriteFile2TailFromString(const string strWrite)
	{
		ofstream oStream(m_strFilePath.c_str(), ios::app);
		if (!oStream.is_open())
			return false;
		oStream.seekp(ios::end);
		oStream << strWrite.c_str();
		oStream.close();
		return true;
	}
	
	/*
	* ��������IsFileExist
	* ������
	* ���ܣ� �ж��ļ��Ƿ����
	* ����ֵ��1Ϊ���� 0Ϊ������
	*/
	BOOL IsFileExist()
	{
		if (-1 == _access(m_strFilePath.c_str(), 00) )
		{
			return FALSE;
		}

		return TRUE;
	}

	/*
	* ��������GetPath
	* ������ 
	* ���ܣ� ��ȡ�ļ�·��
	* ����ֵ��
	*/
	string GetPath()
	{
		return m_strFilePath;
	}

	/*
	* ��������SetPath
	* ������ strPath �ļ�·��
	* ���ܣ� �����ļ�·��
	* ����ֵ�� 
	*/
	void SetPath(string strPath)
	{
		m_strFilePath = strPath;
	}


	/*
	* ��������Delete
	* ������ ��
	* ���ܣ� ɾ���ļ�
	* ����ֵ�� 0��ʾ�ɹ������򷵻ش������
	*/
	DWORD Delete()
	{
		if (DeleteFileA(m_strFilePath.c_str()))
		{
			return 0;
		}
		return GetLastError();
	}

	/*
	* ��������IsDir
	* ������ ��
	* ���ܣ� �ж��Ƿ����ļ���
	* ����ֵ�� 1��ʾ���ļ���
	*/
	BOOL IsDir()
	{
		return PathIsDirectoryA(m_strFilePath.c_str());
	}

private:
	string m_strFilePath;	//��Ա��������ʾ�ļ�·��
};
#endif
