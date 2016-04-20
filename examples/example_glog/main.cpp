/******************************************************************************************
*
* Copyright 2016 KigKrazy
* 
* NOTE:文件为glog的使用DEMO
* 
* 项目地址：https://git.oschina.net/KigKrazy/s_lib.git
*
* 使用注意：
*	1.VS下使用请加上以下预处理器定义：
*		GOOGLE_GLOG_DLL_DECL=;GLOG_NO_ABBREVIATED_SEVERITIES;
*	2.请先在工程中配置好GLOG目录
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
	google::SetStderrLogging(google::GLOG_INFO);							////设置级别高于 google::FATAL 的日志同时输出到屏幕
#ifdef __linux__						
	//下面两种接口只用于LINUX
	google::InstallFailureSignalHandler();					
	google::InstallFailureWriter("/tmp/tmp.glog");
	google::SetLogDestination(google::GLOG_INFO, "/tmp/loginfo_");			//destination dir
#else
	google::SetLogDestination(google::GLOG_INFO, "D:/glog_tmp/loginfo_");	//destination dir
#endif	
	google::SetLogFilenameExtension("windows_");							//文件扩展名
	FLAGS_colorlogtostderr = true;											// Set log color
	FLAGS_logbufsecs = 0;													// Set log output speed(s)
	FLAGS_max_log_size = 1024;												// Set max log file size(GB)
	FLAGS_stop_logging_if_full_disk = true;									// If disk is full
	FLAGS_v = 3;															//VLOG中小于等于FLAGS_v则输出

	
	VLOG(1) << "if 1 <3 printf";											//1 < 3会输出log
	VLOG(1) << "if 4 > 3 printf";											//4 > 3不会输出LOG

	LOG(INFO) << "hello world"; 
	LOG(WARNING) << "hello world222222"; 

	DLOG_IF(INFO, 1) << "DLOG_IF(INFO, 1) test";

	DLOG(INFO) << "DLOG_IF(INFO, 1) test";
	system("pause");
	return 0;
}
