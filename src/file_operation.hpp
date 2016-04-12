/******************************************************************************************
*
* Copyright 2016 KigKrazy
* 
* NOTE:
*	��װһЩ�ļ���д����ز���
* 
* ��Ŀ��ַ��https://git.oschina.net/KigKrazy/s_lib.git
*
* ʹ��ע�⣺
*	1.�����ڹ��������ú�boostĿ¼
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
			return strReadBuf;
		}
		stringstream ssAll;
		ssAll << iStream.rdbuf();
		iStream.close();
		strReadBuf = ssAll.str();
		return strReadBuf;
	}

	/*
	* ��������WriteFileFromByte
	* ������ 
	*	pWriteBuf д������ָ��
	*	iStructSize д�����ʹ�С
	*	iNum д����������͵ĸ���
	* ���ܣ� ���ֽ�Ϊ��λ���ļ�д������
	* ����ֵ�� 1��ʾ�ɹ�
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
	* ��������WriteFile2TailFromByte
	* ������ 
	*	pWriteBuf д������ָ��
	*	iStructSize д�����ʹ�С
	*	iNum д����������͵ĸ���
	* ���ܣ� �ж��Ƿ����ļ���
	* ����ֵ�� 1��ʾ���ļ���
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
	* ��������WriteFileFromString
	* ������	strWrite��д���ļ�������(����)
	* ���ܣ�	��strWrite������д���ļ�
	* ����ֵ��trueΪ�ɹ� falseΪ���ɹ�
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
	* ��������WriteFile2TailFromString
	* ������	strWrite��д���ļ������ݣ�׷�ӵ��ļ�ĩβ��
	* ���ܣ�	��strWrite������д���ļ�
	* ����ֵ��trueΪ�ɹ� falseΪ���ɹ�
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
	* ��������IsFileExist
	* ������
	* ���ܣ� �ж��ļ��Ƿ����
	* ����ֵ��1Ϊ���� 0Ϊ������
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
	* ����ֵ�� 1��ʾ�ɹ�������0,�ļ������ڷ���false
	*/
	bool Delete()
	{
		fs::path complete_path = fs::system_complete(fs::path(m_strFilePath.c_str()));
		return fs::remove(complete_path);
	}

	/*
	* ��������IsDir
	* ������ ��
	* ���ܣ� �ж��Ƿ����ļ���
	* ����ֵ�� 1��ʾ���ļ���
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
	* ��������MkDir
	* ������ ��
	* ���ܣ� �ж��Ƿ����ļ���
	* ����ֵ�� 1��ʾ�����ɹ������򷵻�ʧ�ܣ��ļ��Ѿ����ڷ���ʧ��
	*/
	bool MkDir()
	{
		fs::path complete_path = fs::system_complete(fs::path(m_strFilePath.c_str()));
		return fs::create_directory(complete_path);
	}
private:
	string m_strFilePath;		//��Ա��������ʾ�ļ�·��
};
#endif
