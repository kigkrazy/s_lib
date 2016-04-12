/******************************************************************************************
*
* Copyright 2016 KigKrazy
* 
* NOTE:
*	封装一些字符串转换，分割等操作
* 
* 项目地址：https://git.oschina.net/KigKrazy/s_lib.git
*
* 使用注意：
*	1.请先在工程中配置好boost目录
******************************************************************************************/

#include <string>
#include <boost/locale.hpp>  

using namespace std;

/*
* 函数名：ws2s
* 参数：
*	ws 需要转换的字符串
* 功能：	wstring转string
* 返回值：	转换后的string
*/
std::string ws2s(const std::wstring& ws)
{
	return boost::locale::conv::utf_to_utf<char>(ws);  
}

/*
* 函数名：s2ws
* 参数：
*	s 需要转换的字符串
* 功能：	tring转wstring
* 返回值：	转换后的wstring
*/
std::wstring s2ws(const std::string& s)
{
	return boost::locale::conv::utf_to_utf<wchar_t>(s);
}


/*
* 函数名：to_binary_str
* 参数：
*	buf 需要输出的地址指针
*	len 输出的长度
* 功能：	将内存中的数值转换为二进制字符串
* 返回值：	转换后的string
*/
std::string to_binary_str(const uint8_t* buf,int len)  
{  
    int output_len = len*8;  
    std::string output;  
    const char* m[] = {"0","1"};  
  
    for(int i = output_len - 1,j = 0; i >=0 ; --i,++j)  
    {  
        output.append(m[((uint8_t)buf[j/8] >> (i % 8)) & 0x01],1);  
    }  
    return output;  
}  
 
/*
* 函数名：to_binary_str
* 参数：
*	buf 需要输出的地址指针
*	len 输出的长度
*   tok 分割符
* 功能：	将内存中的数值转换为十六进制字符串
* 返回值：	转换后的string
*/
std::string to_hex_str(const uint8_t* buf,int len,std::string tok = "")  
{  
    std::string output;  
    char temp[8];  
    for (int i = 0; i < len; ++i)  
    {  
        sprintf(temp,"0x%.2x",(uint8_t)buf[i]);  
        output.append(temp,2);  
        output.append(tok);  
    }  
  
    return output;  
}  
/*
* 函数名：split
* 参数：
*	str 需要分割的字符串
*	pattern 分割符，可以是单字节字符，可以是一串字符串
* 功能：	字符串分割
* 返回值：	存放分割字符串的分割后的std::vector<std::string>类型
*/
std::vector<std::string> split(const std::string str, const std::string pattern)
{
    string strParent = str;
    string strPattern = pattern;
    std::string::size_type pos;
    std::vector<std::string> result;
    strParent = strParent + strPattern;//扩展字符串以方便操作l
    std::string::size_type size=strParent.size();
    for(int i = 0; i < (int)size; i++)
    {
        pos=strParent.find(strPattern,i);
        if(pos < size)
        {
            std::string s = strParent.substr(i, pos-i);
            if (s.size() > 0)
            {
                result.push_back(s);
            }
            i = pos + strPattern.size() - 1;
        }
    }
    return result;
}