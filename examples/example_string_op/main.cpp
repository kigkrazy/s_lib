#include <iostream>
#include <string>
#include "../../src/string_operation.hpp"
#include <boost/foreach.hpp>

using namespace std;

void main ()
{
	string stest_tpm = "tsssssss";
	wstring wstest_tpm = L"";
	wstest_tpm = s2ws(stest_tpm);
	cout << "string is :" << stest_tpm <<endl;
	wcout << L"wstring is :" << wstest_tpm <<endl;
	cout << "======================================" <<endl;

	stest_tpm = ws2s(wstest_tpm);
	wcout << L"wstring is :" << wstest_tpm <<endl;
	cout << "string is :" << stest_tpm <<endl;
	cout << "======================================" <<endl;


	string split_stest_tpm = "test,sss,gggg,jjj,`111";
	std::vector<std::string> vsplit;
	vsplit = split(split_stest_tpm, ",");
	
	for (std::vector<std::string>::iterator it = vsplit.begin(); it !=vsplit.end(); it++ )
	{
		cout << it->data() <<endl;
	}
	cout << "======================================" <<endl;


}