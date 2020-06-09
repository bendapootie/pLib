#pragma once

class EventManager
{
public:
	EventManager();
	~EventManager();

	void Initialize() {}

	void RegisterEventListener(EventListener* listener);
	void UnregisterEventListener(EventListener* listener);

	void SendEvent(const EventBase& eventData);

private:
	pList<EventListener*> m_listeners;
};
