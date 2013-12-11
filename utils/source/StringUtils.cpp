#include "StdAfx.h"
#include "..\include\StringUtils.h"


StringUtils::StringUtils(void)
{
}


StringUtils::~StringUtils(void)
{
}

std::vector<std::string> StringUtils::split(const std::string &str, char delim){

	std::vector<std::string> strVector;
	std::stringstream ss(str);
	std::string item;

	while (std::getline(ss, item, delim)) {
		strVector.push_back(item);
	}
	return strVector;

} 
