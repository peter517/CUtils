
#ifndef CUTILS_STRINGUTILS_H_
#define CUTILS_STRINGUTILS_H_

#include <windows.h> 
#include <iostream> 
#include <sstream> 
#include <string>
#include <vector>


class StringUtils
{
public:
	StringUtils(void);
	~StringUtils(void);

	static std::vector<std::string> Split(const std::string &str, char delim);
	static std::string UTF8ToGBK(const std::string& strUTF8);
	static std::string GBKToUTF8(const std::string& strUTF8);
    static const char* GetFileNameFromPath(const char* file);
	static std::string GetLogInfo(const char* tag,const char* file, int line, const std::string& logStr);
};

#endif

