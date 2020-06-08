#pragma once

class EventListener
{
public:
	virtual void HandleEvent(const EventBase& eventData) = 0;
};
