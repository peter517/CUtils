#include "StdAfx.h"
#include "..\include\StringUtils.h"


StringUtils::StringUtils(void)
{
}


StringUtils::~StringUtils(void)
{
}

std::vector<std::string> StringUtils::Split(const std::string &str, char delim){

	std::vector<std::string> strVector;
	std::stringstream ss(str);
	std::string item;

	while (std::getline(ss, item, delim)) {
		strVector.push_back(item);
	}
	return strVector;

} 

std::string StringUtils::UTF8ToGBK( const std::string& strUTF8 )
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);  
	wchar_t * wszGBK = new wchar_t[len + 1];  
	memset(wszGBK, 0, len * 2 + 2);  
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)strUTF8.c_str(), -1, wszGBK, len);  

	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);  
	char *szGBK = new char[len + 1];  
	memset(szGBK, 0, len + 1);  
	WideCharToMultiByte(CP_ACP,0, wszGBK, -1, szGBK, len, NULL, NULL);  
	std::string strTemp(szGBK);  

	delete[]szGBK;  
	delete[]wszGBK;  

	return strTemp;  

}

std::string StringUtils::GBKToUTF8( const std::string& strGBK )
{
	std::string strOutUTF8 = "";  
	WCHAR * str1;  

	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);  
	str1 = new WCHAR[n];  
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);  
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);  
	char * str2 = new char[n];  
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);  
	strOutUTF8 = str2; 

	delete[]str1;  
	str1 = NULL;  
	delete[]str2;  
	str2 = NULL;  

	return strOutUTF8; 
}
