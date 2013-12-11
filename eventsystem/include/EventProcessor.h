#include "Event.h"
#ifndef CUTILS_EVENTPROCESSOR_H_
#define CUTILS_EVENTPROCESSOR_H_


class EventProcessor{

public:
	EventProcessor(void);
	~EventProcessor(void);
	virtual void handleEvent(Event event) = 0;
private:
	
};
#endif