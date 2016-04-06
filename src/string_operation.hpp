/*
* 文件名：SFileOp.hpp
* 功能：字符串转换，分割等操作
* 作者：KigKrazy
* 创建日期：2016-04-06
* 修改人：KigKrazy
* 修改日期：2016-04-06
* 修改人：KigKrazy
* 修改日期：2016-04-06
*/

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