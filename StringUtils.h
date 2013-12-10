
#ifndef CUTILS_STRINGUTILS_H_
#define CUTILS_STRINGUTILS_H_

#include <iostream> 
#include <sstream> 
#include <string>
#include <vector>

class StringUtils
{
public:
	StringUtils(void);
	~StringUtils(void);

	static std::vector<std::string> split(const std::string &str, char delim);
};

#endif

