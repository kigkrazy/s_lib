/*
* 文件名：SFileOp.hpp
* 功能：封装一些文件读写等相关操作
* 作者：KigKrazy
* 创建日期：2015年6月17日23:49:05
* 修改人：KigKrazy
* 修改日期：2015年6月17日23:49:49
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
	//初始化
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
	* 函数名：ReadFile2String
	* 参数：	
	* 功能：	读取文件内容
	* 返回值：	返回读取的字符串内容
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
	* 函数名：WriteFileFromString
	* 参数：	strWrite：写入文件的内容(覆盖)
	* 功能：	将strWrite的内容写入文件
	* 返回值：TRUE为成功 FALSE为不成功
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
	* 函数名：WriteFile2TailFromString
	* 参数：	strWrite：写入文件的内容（追加到文件末尾）
	* 功能：	将strWrite的内容写入文件
	* 返回值：TRUE为成功 FALSE为不成功
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
	* 函数名：IsFileExist
	* 参数：
	* 功能： 判断文件是否存在
	* 返回值：1为存在 0为不存在
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
	* 函数名：GetPath
	* 参数： 
	* 功能： 获取文件路径
	* 返回值：
	*/
	string GetPath()
	{
		return m_strFilePath;
	}

	/*
	* 函数名：SetPath
	* 参数： strPath 文件路径
	* 功能： 设置文件路径
	* 返回值： 
	*/
	void SetPath(string strPath)
	{
		m_strFilePath = strPath;
	}


	/*
	* 函数名：Delete
	* 参数： 无
	* 功能： 删除文件
	* 返回值： 0表示成功，否则返回错误代码
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
	* 函数名：IsDir
	* 参数： 无
	* 功能： 判断是否是文件夹
	* 返回值： 1表示是文件夹
	*/
	BOOL IsDir()
	{
		return PathIsDirectoryA(m_strFilePath.c_str());
	}

private:
	string m_strFilePath;	//成员变量，表示文件路径
};
#endif
