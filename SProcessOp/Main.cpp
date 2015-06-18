#include <iostream>
#include "ProcessOp.hpp"

using namespace std;

void main()
{
	CProcessOP cp;
	list<PROCESSINFO> ls;
	cp.EnableDebugPriv(SE_DEBUG_NAME);
	ls = cp.GetCurProcessList();
	int i = 0;
	list<PROCESSINFO>::iterator lsItor;
	for (lsItor = ls.begin(); lsItor != ls.end(); lsItor++)
	{
		i++;
		wcout << lsItor->wstrProcessName << "   " << lsItor->dwProcessId << "   " << lsItor->wstrFullPath << endl;
		//wcout << lsItor->wstrProcessName << "   " << lsItor->dwProcessId << endl;

	}
	cout << i << endl;
	system("pause");
	//cout << "test " << endl;
}