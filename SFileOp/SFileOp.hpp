#pragma once
#ifndef SFILE_OP_HPP_
#define SFILE_OP_HPP_
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <string>
#include <io.h>
using namespace std;
class CSFileOp
{
public:
	//≥ı ºªØ
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

	BOOL WriteFile2String(const string strWrite)
	{
		ofstream oStream(m_strFilePath.c_str());
		if (!oStream.is_open())
			return FALSE;
		oStream << strWrite.c_str();
		oStream.close();
		return TRUE;
	}

	BOOL IsFileExist()
	{
		if (-1 == _access(m_strFilePath.c_str(), 00) )
		{
			return FALSE;
		}

		return TRUE;
	}
private:
	string m_strFilePath;
};
#endif