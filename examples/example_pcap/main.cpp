/******************************************************************************************
*
* Copyright 2016 KigKrazy
* 
* NOTE:
*	文件为winpcap的使用DEMO
*	本程序展示了如何用WINPACAP获取网卡信息：ipv4地址，ipv4掩码地址，ipv4广播地址，ipv4目的地址
* 
* 项目地址：https://git.oschina.net/KigKrazy/s_lib.git
*
* 使用注意：
*	1.请先在工程中配置好boost,winpcap目录
******************************************************************************************/
#include <iostream>
#ifdef WIN32
#define HAVE_REMOTE 
#define WPCAP
#endif // WIN32

#include <pcap.h>
#ifdef WIN32
#include <winsock.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>
#endif


#include <boost/thread/thread.hpp>


using namespace std;
using namespace boost;


pcap_if_t *g_all_devs = NULL;  
//pthread_t g_pthreadStartCatch;  
#define SNAPLEN 65535       //  各种协议数据包大小都不超过65535  
#define READ_TIMEOUT 500    //设置数据包抓取 超时时间，对pcap_dispatch，有效  


//函数声明
void free_devs();
void find_devs();
void if_print(pcap_if_t *dev);
char *iptos(u_long in);
char* ip6tos(struct sockaddr *sockaddr, char *address, int addrlen);

void free_devs()
{
	pcap_freealldevs(g_all_devs);
}

void find_devs()  
{  
	char errbuf[PCAP_ERRBUF_SIZE + 1];  
	int i = 0;  
	pcap_if_t *dev = NULL;

	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &g_all_devs, errbuf) == -1)//返回网卡列表，alldevs指向表头  
	{  
		std::cout << "Error in pcap_findalldevs: " << errbuf << std::endl;
		return;  
	}

	for(dev = g_all_devs; dev != NULL; dev = dev->next)  
	{  
		if_print(dev);
		++i;
		std::cout << "=========================================================" << std::endl;
	}

	if (i == 0)
	{
		std::cout << "No interfaces found! Make sure WinPcap is installed." << std::endl;
		return;
	}
} 

void if_print(pcap_if_t *dev)
{
	pcap_addr_t *addr_tmp;	//ip地址,掩码，等信息
	char ip6str[128];		

	//设备名
	std::cout << dev->name << std::endl;					

	//设备描述信息
	if(dev->description)												
		std::cout << "\t(" << dev->description << ")" << std::endl;		
	else
		std::cout << "\t(No description available)\n" << std::endl;

	//接口是否是回调的
	std::cout << "\tLoopback:" << ((dev->flags & PCAP_IF_LOOPBACK)?"yes":"no") << std::endl;

	//IP 地址
	for(addr_tmp = dev->addresses; addr_tmp; addr_tmp = addr_tmp->next) 
	{
		std::cout << "\tAddress Family: #" << addr_tmp->addr->sa_family << std::endl;

		switch(addr_tmp->addr->sa_family)
		{
		case AF_INET:
			std::cout << "\tAddress Family Name: AF_INET" << std::endl;
			if (addr_tmp->addr)
				std::cout << "\tAddress: " << iptos(((struct sockaddr_in *)addr_tmp->addr)->sin_addr.s_addr) << std::endl;					//ipv4地址
			if (addr_tmp->netmask)
				std::cout << "\tNetmask: " << iptos(((struct sockaddr_in *)addr_tmp->netmask)->sin_addr.s_addr) << std::endl;				//ipv4掩码地址
			if (addr_tmp->broadaddr)
				std::cout << "\tBroadcast Address: " << iptos(((struct sockaddr_in *)addr_tmp->broadaddr)->sin_addr.s_addr) << std::endl;	//ipv4广播地址
			if (addr_tmp->dstaddr)
				std::cout << "\tDestination Address: " << iptos(((struct sockaddr_in *)addr_tmp->dstaddr)->sin_addr.s_addr) << std::endl;	//ipv4目的地址
			break;
		case AF_INET6:
			std::cout << "\tAddress Family Name: AF_INET6" << std::endl;																	//ipv6地址
			if (addr_tmp->addr)
				std::cout << "\tAddress: " << ip6tos(addr_tmp->addr, ip6str, sizeof(ip6str)) << std::endl;
			break;
		default:
			std::cout << "\tAddress Family Name: Unknown\n" << std::endl;
			break;
		}
	}
}

/* 将数字类型的IP地址转换成字符串类型的 */
#define IPTOSBUFFERS    12
char *iptos(u_long in)
{
	static char output[IPTOSBUFFERS][3*4+3+1];
	static short which;
	u_char *p;

	p = (u_char *)&in;
	which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
	sprintf_s(output[which], "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
	return output[which];
}

char* ip6tos(struct sockaddr *sockaddr, char *address, int addrlen)
{
	socklen_t sockaddrlen;

#ifdef WIN32
	sockaddrlen = sizeof(struct sockaddr_in6);
#else
	sockaddrlen = sizeof(struct sockaddr_storage);
#endif


	if(getnameinfo(sockaddr, 
		sockaddrlen, 
		address, 
		addrlen, 
		NULL, 
		0, 
		NI_NUMERICHOST) != 0) address = NULL;

	return address;
}

int main(int ac, char* av[])
{
	find_devs();
	free_devs();
	std::system("pause");
	return 0;
}
