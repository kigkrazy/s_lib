#ifdef WIN32
#include <Windows.h>
#endif

#include <iostream>
#include "../../src/file_operation.hpp"
using namespace std;

using namespace std;

void main()
{
	CSFileOp sfTestWriteString("ssTestWriteString");
	sfTestWriteString.WriteFileFromString("test\ntest");
	string strTest;
	strTest = sfTestWriteString.ReadFile2String();
	cout << strTest << endl;

	CSFileOp sfTestWriteByte("ssTestWriteByte");
	sfTestWriteByte.WriteFileFromByte("test===================\n", 1, sizeof("test===================\n") - 1);
	sfTestWriteByte.WriteFile2TailFromByte("test===================\n", 1, sizeof("test===================\n") - 1);

	//cout << "test" << endl;
	CSFileOp sfIsDirTest("11");
	if (sfIsDirTest.IsFileExists())
	{
		cout << "File Exists!!" << endl;
	}
	else
	{
		cout << "File1 not Exists!!" << endl;
	}



	if (sfIsDirTest.IsDir())
	{
		cout << "File is Dir!!" << endl;
	}
	else
	{
		cout << "File1 not dir!!" << endl;
	}


	if (sfTestWriteByte.IsDir())
	{
		cout << "File is Dir!!" << endl;
	}
	else
	{
		cout << "File1 not dir!!" << endl;
	}
}

