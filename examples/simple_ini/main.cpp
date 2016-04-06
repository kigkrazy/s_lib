#include <iostream>
#include <string>
#include <string>
#include "../../src/simpleini/SimpleIni.h"

#ifdef __linux__
#include "../../src/simpleini/ConvertUTF.h"
#endif // __linux__


using namespace std;


void main ()
{
	CSimpleIniA ini; 
	string strData;

	//添加Section与KEY
	cout << "================================="<<endl;
	cout << "Save to file!!"<<endl;
	ini.LoadFile("myfile.ini");
	ini.SetValue("student", "name", "LiLei");
	ini.SetValue("student", "age", "19");
	ini.SetValue("student", "班级", "3");
	ini.SetValue("student", "性别", "男");
	ini.SaveFile("myfile.ini");		//将修改的内容写入文件	
	cout << "================================="<<endl;
	
	//将文件内容保存到strData;
	ini.Save(strData);
	cout<< strData.c_str() <<endl;
	cout << "================================="<<endl;
	//内容更新
	cout << "update!!"<<endl;
	ini.SetValue("student", "性别", "女");
	ini.SaveFile("myfile.ini");
	ini.Save(strData);
	cout<< strData.c_str() <<endl;
	cout << "================================="<<endl;
	//获得KEY内容
	cout << "Get Key value!!"<<endl;
	string strGetValue = ini.GetValue("student", "name");
	cout << "Key Name is: "<<strGetValue.c_str()<<endl;

	//system("pause");
}