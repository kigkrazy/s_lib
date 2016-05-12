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
* ��������hexdata_to_binarystr
* ������
*	buf ��Ҫ����ĵ�ַָ��
*	len ����ĳ���
* ���ܣ�	���ڴ��е���ֵת��Ϊ�������ַ���
* ����ֵ��	ת�����string
*/
std::string hexdata_to_binarystr(const uint8_t* buf,int len)  
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
* ��������hexdata_to_hexstr
* ������
*	buf ��Ҫ����ĵ�ַָ��
*	len ����ĳ���
*   tok �ָ��
* ���ܣ�	���ڴ��е���ֵת��Ϊʮ�������ַ���
* ����ֵ��	ת�����string
*/
std::string hexdata_to_hexstr(const uint8_t* buf, int len, std::string tok = "")  
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

/**************************************************************************** 
��������: hexstr_to_hexdata
��������: �ַ���ת��Ϊʮ������ 
�������: src �ַ��� cbuf ʮ������ len �ַ����ĳ��ȡ� 
�������: �� 
*****************************************************************************/  
static int hexstr_to_hexdata(char *src, unsigned char *cbuf, int len)  
{  
	unsigned char high, low;  
	int idx, ii=0;  
	for (idx=0; idx<len; idx+=2)   
	{  
		high = src[idx];  
		low = src[idx+1];  

		if(high>='0' && high<='9')  
			high = high-'0';  
		else if(high>='A' && high<='F')  
			high = high - 'A' + 10;  
		else if(high>='a' && high<='f')  
			high = high - 'a' + 10;  
		else  
			return -1;  

		if(low>='0' && low<='9')  
			low = low-'0';  
		else if(low>='A' && low<='F')  
			low = low - 'A' + 10;  
		else if(low>='a' && low<='f')  
			low = low - 'a' + 10;  
		else  
			return -1;  

		cbuf[ii++] = high<<4 | low;  
	}  
	return 1;  
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