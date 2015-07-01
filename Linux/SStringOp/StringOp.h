#ifndef _STRING_OP_H
#define _STRING_OP_H

#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>
using namespace std;

std::string ws2s(const std::wstring& ws);
std::wstring s2ws(const std::string& s);
//字符串分割函数
std::vector<std::string> split(const std::string str, const std::string pattern);

#endif