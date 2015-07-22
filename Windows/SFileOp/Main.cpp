#include <iostream>
#include <Windows.h>
#include "SFileOp.hpp"
using namespace std;

void main()
{
	//CSFileOp CSFileOp
	CSFileOp sfTest("sstest");
	sfTest.WriteFile2String("test\ntest");
	string strTest;
	strTest = sfTest.ReadFile2String();
	
	CSFileOp sfTest("wrBuftest");
	sfTest.WriteFileFromByte("test===================\n", 1, sizeof("test===================\n") - 1);
	sfTest.WriteFile2TailFromByte("test===================\n", 1, sizeof("test===================\n") - 1);

	//cout << "test" << endl;
	
	system("PAUSE");
}

