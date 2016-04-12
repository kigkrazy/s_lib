/******************************************************************************************
*
* Copyright 2016 KigKrazy
* 
* NOTE:
*	封装一些文件读写等相关操作
* 
* 项目地址：https://git.oschina.net/KigKrazy/s_lib.git
*
* 使用注意：
*	1.请先在工程中配置好boost目录
******************************************************************************************/
#pragma once
#ifndef SFILE_OP_HPP_
#define SFILE_OP_HPP_
#define  _CRT_SECURE_NO_WARNINGS

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
	bool WriteFileFromByte(const void *pWriteBuf, int iStructSize, int iStructNum)
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
	bool WriteFile2TailFromByte(const void *pWriteBuf, int iStructSize, int iStructNum)
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
	* 返回值：true为成功 false为不成功
	*/
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
	* 函数名：WriteFile2TailFromString
	* 参数：	strWrite：写入文件的内容（追加到文件末尾）
	* 功能：	将strWrite的内容写入文件
	* 返回值：true为成功 false为不成功
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
	bool IsFileExists()
	{
		if (fs::exists(fs::path(m_strFilePath.c_str())))
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
	* 返回值： 1表示成功，否则0,文件不存在返回false
	*/
	bool Delete()
	{
		fs::path complete_path = fs::system_complete(fs::path(m_strFilePath.c_str()));
		return fs::remove(complete_path);
	}

	/*
	* 函数名：IsDir
	* 参数： 无
	* 功能： 判断是否是文件夹
	* 返回值： 1表示是文件夹
	*/
	bool IsDir()
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


	/*
	* 函数名：MkDir
	* 参数： 无
	* 功能： 判断是否是文件夹
	* 返回值： 1表示创建成功，否则返回失败，文件已经存在返回失败
	*/
	bool MkDir()
	{
		fs::path complete_path = fs::system_complete(fs::path(m_strFilePath.c_str()));
		return fs::create_directory(complete_path);
	}
private:
	string m_strFilePath;		//成员变量，表示文件路径
};
#endif
