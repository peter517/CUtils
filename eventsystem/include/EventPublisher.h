
#ifndef CUTILS_EVENTPUBLISHER_H_
#define CUTILS_EVENTPUBLISHER_H_

#include <list>
#include <windows.h>

#include "..\include\Event.h"
#include "..\include\EventProcessor.h"
#include "..\..\..\CUtils\webrtc\system_wrappers\interface\thread_wrapper.h"
#include "..\..\..\CUtils\webrtc\system_wrappers\interface\event_wrapper.h"
#include "..\..\..\CUtils\webrtc\system_wrappers\interface\critical_section_wrapper.h"

class EventPublisher{
 
public:
	static EventPublisher * GetInstance();
	void Start();
	void Stop();
	void Destroy();
	void AddEventProcessor(EventProcessor * processor);	
	void PublishEvent(Event &event);
private:

	friend bool Run(void *data);
	void EventPublisher::DispatchEvent(Event & event);
	
	webrtc::CriticalSectionWrapper* m_critsect;
	webrtc::ThreadWrapper* m_thread;
	webrtc::EventWrapper* m_event_wapper;
	static EventPublisher* m_eventPublisher;
	std::list<EventProcessor*> m_processor_list;
	std::list<Event> m_event_list;

	EventPublisher(void);
	~EventPublisher(void);
};
#endif