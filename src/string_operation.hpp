#include <string>
#include <boost/locale.hpp>  

using namespace std;

std::string ws2s(const std::wstring& ws)
{
	return boost::locale::conv::utf_to_utf<char>(ws);  
}


std::wstring s2ws(const std::string& s)
{
	return boost::locale::conv::utf_to_utf<wchar_t>(s);
}


//×Ö·û´®·Ö¸îº¯Êý
std::vector<std::string> split(const std::string str, const std::string pattern)
{
    string strParent = str;
    string strPattern = pattern;
    std::string::size_type pos;
    std::vector<std::string> result;
    strParent = strParent + strPattern;//À©Õ¹×Ö·û´®ÒÔ·½±ã²Ù×÷l
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
            //cout << s.c_str()<<endl;
            i = pos + strPattern.size() - 1;
        }
    }
    return result;
}