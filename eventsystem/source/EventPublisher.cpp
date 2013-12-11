#include "StdAfx.h"
#include "..\include\EventPublisher.h"


EventPublisher* EventPublisher::m_eventPublisher = new EventPublisher();

EventPublisher::EventPublisher(void)
{ 
	m_thread = webrtc::ThreadWrapper::CreateThread(Run,NULL);
	m_event_wapper = webrtc::EventWrapper::Create();
	m_critsect = webrtc::CriticalSectionWrapper::CreateCriticalSection();
}

EventPublisher::~EventPublisher(void)
{
	delete m_thread;
	delete m_event_wapper;
	delete m_critsect;
}

EventPublisher * EventPublisher::GetInstance()
{
	return m_eventPublisher;
}

void EventPublisher::AddEventProcessor( EventProcessor * processor )
{

	m_eventPublisher->m_critsect->Enter();

	std::list<EventProcessor *>::iterator it = m_eventPublisher->m_processor_list.begin();
	while(it != m_eventPublisher->m_processor_list.end()) {

		EventProcessor * p = *it;

		if (processor == p) {
			return;
		}
		it++;
	}
	m_eventPublisher->m_processor_list.push_back(processor);
	m_eventPublisher->m_critsect->Leave();
}

void EventPublisher::PublishEvent( Event &event )
{
	m_eventPublisher->m_critsect->Enter();

	m_eventPublisher->m_event_list.push_back(event);
	m_event_wapper->Set();

	m_eventPublisher->m_critsect->Leave();
}

bool Run(void *data){

	EventPublisher * publisher = EventPublisher::GetInstance();
	if (publisher == NULL) {
		return true;
	}

	if (publisher->m_event_list.size() == 0)
	{
		publisher->m_event_wapper->Wait(INFINITE);
	}

	std::list<Event> event_list_tmp;

	publisher->m_critsect->Enter();

	event_list_tmp = publisher->m_event_list;
	publisher->m_event_list.clear();

	publisher->m_critsect->Leave();
	

	std::list<Event>::iterator it = event_list_tmp.begin();
	while(it != event_list_tmp.end()) {
		Event event = *it;
		publisher->DispatchEvent(event);
		it++;
	}

	return true;

}


void EventPublisher::Start()
{
	unsigned int id;
	m_thread->Start(id);
}

void EventPublisher::Stop()
{
	m_thread->Stop();
}

void EventPublisher::DispatchEvent(Event & event) {

	std::list <EventProcessor *> processor_list = m_eventPublisher->m_processor_list; 

	std::list<EventProcessor *>::iterator it = processor_list.begin();
	while(it != processor_list.end()) {
		EventProcessor * processor = *it;
		processor->handleEvent(event);
		it++;
	}
}

void EventPublisher::Destroy()
{
	Stop();
	delete m_eventPublisher;
}
