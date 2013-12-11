#ifndef CUTILS_EVENT_H_
#define CUTILS_EVENT_H_

#include <string>

class Event{

public:
	Event(void);
	~Event(void);
	Event(char* info,int code):m_info(info),m_code(code){}
	Event(char* info):m_info(info){}

	char* GetInfo() const { return m_info; }
	int GetCode() const { return m_code; }
private:
	char* m_info;
	int m_code;
};
#endif