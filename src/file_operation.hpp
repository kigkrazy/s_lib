/*
* 文件名：SFileOp.hpp
* 功能：封装一些文件读写等相关操作
* 作者：KigKrazy
* 创建日期：2015年6月17日23:49:05
* 修改人：KigKrazy
* 修改日期：2015年6月17日23:49:49
* 修改人：KigKrazy
* 修改日期：2015年7月22日16:53:56
*/
#pragma once
#ifndef SFILE_OP_HPP_
#define SFILE_OP_HPP_
#define  _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <sstream>
#include <fstream>
#include <string>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/convenience.hpp>

using namespace std;
namespace fs = boost::filesystem;

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
			return strReadBuf;
		}
		stringstream ssAll;
		ssAll << iStream.rdbuf();
		iStream.close();
		strReadBuf = ssAll.str();
		return strReadBuf;
	}

	/*
	* 函数名：WriteFileFromByte
	* 参数： 
	*	pWriteBuf 写入数据指针
	*	iStructSize 写入类型大小
	*	iNum 写入的数据类型的个数
	* 功能： 以字节为单位向文件写入数据
	* 返回值： 1表示成功
	*/
	BOOL WriteFileFromByte(const void *pWriteBuf, int iStructSize, int iStructNum)
	{
#ifdef WIN32
		FILE *pfWrite = NULL;
		fopen_s(&pfWrite, m_strFilePath.c_str(), "wb");
#else
		FILE * pfWrite = fopen(m_strFilePath.c_str(), "wb");
#endif // WIN32

		fwrite(pWriteBuf, iStructSize, iStructNum, pfWrite);
		fclose(pfWrite);
		return true;
	}

	/*
	* 函数名：WriteFile2TailFromByte
	* 参数： 
	*	pWriteBuf 写入数据指针
	*	iStructSize 写入类型大小
	*	iNum 写入的数据类型的个数
	* 功能： 判断是否是文件夹
	* 返回值： 1表示是文件夹
	*/
	BOOL WriteFile2TailFromByte(const void *pWriteBuf, int iStructSize, int iStructNum)
	{
#ifdef WIN32
	FILE * pfWrite = NULL;
	fopen_s(&pfWrite, m_strFilePath.c_str(), "at+");
#else
		FILE * pfWrite = fopen(m_strFilePath.c_str(), "at+");
#endif // WIN32
		fwrite(pWriteBuf, iStructSize, iStructNum, pfWrite);
		fclose(pfWrite);
		return true;
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
		ofstream oStream;
		oStream.open(m_strFilePath.c_str(), ios::app);
		if (!oStream.is_open())
			return false;
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
	BOOL IsFileExists()
	{
		if (fs::exists(fs::path(m_strFilePath.c_str(), fs::native)))
		{
			return true;
		}
		else
		{
			return false;
		}
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
		fs::path complete_path = fs::system_complete(fs::path(m_strFilePath.c_str()));
		if (fs::directory_file == fs::status(complete_path).type())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	string m_strFilePath;	//成员变量，表示文件路径
};
#endif
