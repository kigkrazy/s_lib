#ifndef _CFile_H
#define _CFile_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

using namespace std;

class CFile
{
private:
	string m_strFilePath;

public:

	CFile(){};

	~CFile(){};

	CFile(string strFilePath)
	{
		m_strFilePath = strFilePath;
	}

	void SetFilePath(string strFilePath)
	{
		m_strFilePath = strFilePath;
	}

	string ReadFile2String()
	{
		string strReadBuf = "";
		ifstream iStream(m_strFilePath.c_str());  
		if (!iStream.is_open())
		{
			return strReadBuf;
		}
		stringstream ssAll;
		ssAll << iStream.rdbuf();
		iStream.close();
		strReadBuf = ssAll.str();
		return strReadBuf;
	}

	bool WriteFileFromString(const string strWrite)
	{
		ofstream oStream(m_strFilePath.c_str());
		if (!oStream.is_open())
			return false;
		oStream << strWrite.c_str();
		oStream.close();
		return true;
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
	
	bool IsExist()
	{
		if(0 == m_strFilePath.length())
			return false;

		bool bRet = false;
		struct  stat  st;
		if (0 == stat(m_strFilePath.c_str(), &st))
		{
			bRet = true;
		}
		return bRet;
	}

	long GetFileSize()
	{
		if (!IsExist())
			return 0;
		ifstream in(m_strFilePath.c_str());
    		in.seekg(0, ios::end);      //�����ļ�ָ�뵽�ļ�����β��
    		streampos ps = in.tellg();  //��ȡ�ļ�ָ���λ��
    		in.close();                 //�ر��ļ���
    		return ps;
	}

	void DeleteFile()
	{
		if (IsExist())
		{
			remove(m_strFilePath.c_str());
		}
	}

	bool IsDir()
	{
		if (!IsExist())
		{
			return false;
		}
		struct stat info;
		stat(m_strFilePath.c_str(), &info);
		if(S_ISDIR(info.st_mode))
    			return true;
    		return false;
	}
};
#endif