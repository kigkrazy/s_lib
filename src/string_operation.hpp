/******************************************************************************************
*
* Copyright 2016 KigKrazy
* 
* NOTE:
*	��װһЩ�ַ���ת�����ָ�Ȳ���
* 
* ��Ŀ��ַ��https://git.oschina.net/KigKrazy/s_lib.git
*
* ʹ��ע�⣺
*	1.�����ڹ��������ú�boostĿ¼
******************************************************************************************/

#include <string>
#include <boost/locale.hpp>  

using namespace std;

/*
* ��������ws2s
* ������
*	ws ��Ҫת�����ַ���
* ���ܣ�	wstringתstring
* ����ֵ��	ת�����string
*/
std::string ws2s(const std::wstring& ws)
{
	return boost::locale::conv::utf_to_utf<char>(ws);  
}

/*
* ��������s2ws
* ������
*	s ��Ҫת�����ַ���
* ���ܣ�	tringתwstring
* ����ֵ��	ת�����wstring
*/
std::wstring s2ws(const std::string& s)
{
	return boost::locale::conv::utf_to_utf<wchar_t>(s);
}


/*
* ��������to_binary_str
* ������
*	buf ��Ҫ����ĵ�ַָ��
*	len ����ĳ���
* ���ܣ�	���ڴ��е���ֵת��Ϊ�������ַ���
* ����ֵ��	ת�����string
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
* ��������to_binary_str
* ������
*	buf ��Ҫ����ĵ�ַָ��
*	len ����ĳ���
*   tok �ָ��
* ���ܣ�	���ڴ��е���ֵת��Ϊʮ�������ַ���
* ����ֵ��	ת�����string
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
* ��������split
* ������
*	str ��Ҫ�ָ���ַ���
*	pattern �ָ���������ǵ��ֽ��ַ���������һ���ַ���
* ���ܣ�	�ַ����ָ�
* ����ֵ��	��ŷָ��ַ����ķָ���std::vector<std::string>����
*/
std::vector<std::string> split(const std::string str, const std::string pattern)
{
    string strParent = str;
    string strPattern = pattern;
    std::string::size_type pos;
    std::vector<std::string> result;
    strParent = strParent + strPattern;//��չ�ַ����Է������l
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