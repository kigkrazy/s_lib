#include <iostream>
#include <string>
#include <string.h>
#include "SimpleIni.h"
using namespace std;


void main ()
{
	CSimpleIniA ini; 
	string strData;

	//���Section��KEY
	cout << "================================="<<endl;
	cout << "Save to file!!"<<endl;
	ini.LoadFile("myfile.ini");
	ini.SetValue("student", "name", "LiLei");
	ini.SetValue("student", "age", "19");
	ini.SetValue("student", "�༶", "3");
	ini.SetValue("student", "�Ա�", "��");
	ini.SaveFile("myfile.ini");		//���޸ĵ�����д���ļ�	
	cout << "================================="<<endl;
	
	//���ļ����ݱ��浽strData;
	ini.Save(strData);
	cout<< strData.c_str() <<endl;
	cout << "================================="<<endl;
	//���ݸ���
	cout << "update!!"<<endl;
	ini.SetValue("student", "�Ա�", "Ů");
	ini.SaveFile("myfile.ini");
	ini.Save(strData);
	cout<< strData.c_str() <<endl;
	cout << "================================="<<endl;
	//���KEY����
	cout << "Get Key value!!"<<endl;
	string strGetValue = ini.GetValue("student2", "name");
	cout << "Key Name is: "<<strGetValue.c_str()<<endl;



	system("pause");
}