/*
* �ļ�����SFileOp.hpp
* ���ܣ��ַ���ת�����ָ�Ȳ���
* ���ߣ�KigKrazy
* �������ڣ�2016-04-06
* �޸��ˣ�KigKrazy
* �޸����ڣ�2016-04-06
* �޸��ˣ�KigKrazy
* �޸����ڣ�2016-04-06
*/

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