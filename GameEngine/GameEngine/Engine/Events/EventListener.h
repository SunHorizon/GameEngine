#ifndef EventListener_H
#define EventListener_H

#include "MouseEventListener.h"

class EventListener
{
public:
	EventListener() = delete;
	

	EventListener(const EventListener&) = delete;
	EventListener(EventListener&&) = delete;
	EventListener& operator=(const EventListener&) = delete;
	EventListener& operator=(EventListener&&) = delete;
	~EventListener();
	
	static void Update();
};

#endif //!EventListener_H

