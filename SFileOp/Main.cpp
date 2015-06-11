#include <iostream>
#include <Windows.h>
#include "SFileOp.h"
using namespace std;

void main()
{
	//CSFileOp CSFileOp
	CSFileOp sfTest("c:\\ss\\sstest");
	sfTest.WriteFile2String("test\ntest");
	string strTest;
	strTest = sfTest.ReadFile2String();
	system("PAUSE");
}

