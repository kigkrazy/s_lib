/******************************************************************************************
*
* Copyright 2016 KigKrazy
* 
* NOTE:�ļ�Ϊglog��ʹ��DEMO
* 
* ��Ŀ��ַ��https://git.oschina.net/KigKrazy/s_lib.git
*
* ʹ��ע�⣺
*	1.VS��ʹ�����������Ԥ���������壺
*		GOOGLE_GLOG_DLL_DECL=;GLOG_NO_ABBREVIATED_SEVERITIES;
*	2.�����ڹ��������ú�GLOGĿ¼
******************************************************************************************/
#include <iostream>
#include <iterator>
#include <glog/logging.h>

using namespace std;

int main(int ac, char* av[])
{
	string test(av[0]);
	test = test + "-info";
	google::InitGoogleLogging(test.c_str());
	google::SetStderrLogging(google::GLOG_INFO);							////���ü������ google::FATAL ����־ͬʱ�������Ļ
#ifdef __linux__						
	//�������ֽӿ�ֻ����LINUX
	google::InstallFailureSignalHandler();					
	google::InstallFailureWriter("/tmp/tmp.glog");
	google::SetLogDestination(google::GLOG_INFO, "/tmp/loginfo_");			//destination dir
#else
	google::SetLogDestination(google::GLOG_INFO, "D:/glog_tmp/loginfo_");	//destination dir
#endif	
	google::SetLogFilenameExtension("windows_");							//�ļ���չ��
	FLAGS_colorlogtostderr = true;											// Set log color
	FLAGS_logbufsecs = 0;													// Set log output speed(s)
	FLAGS_max_log_size = 1024;												// Set max log file size(GB)
	FLAGS_stop_logging_if_full_disk = true;									// If disk is full
	FLAGS_v = 3;															//VLOG��С�ڵ���FLAGS_v�����

	
	VLOG(1) << "if 1 <3 printf";											//1 < 3�����log
	VLOG(1) << "if 4 > 3 printf";											//4 > 3�������LOG

	LOG(INFO) << "hello world"; 
	LOG(WARNING) << "hello world222222"; 

	DLOG_IF(INFO, 1) << "DLOG_IF(INFO, 1) test";

	DLOG(INFO) << "DLOG_IF(INFO, 1) test";
	system("pause");
	return 0;
}
