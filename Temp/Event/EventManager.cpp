#include "Precompiled.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
	pLib::Assert(m_listeners.Count() == 0, "All EventListeners should have been removed by now");
}

void EventManager::RegisterEventListener(EventListener* listener)
{
	pLib::Assert(listener != nullptr, "Don't pass null into here");
	pLib::Assert(m_listeners.Contains(listener) == false, "EventListener added multiple times");
	m_listeners.Add(listener);
}

void EventManager::UnregisterEventListener(EventListener* listener)
{
	pLib::Assert(listener != nullptr, "Don't pass null into here");

	int index;
	m_listeners.FindIndex(listener, index);
	pLib::Assert(index >= 0, "EventListener not found in list");

	m_listeners.RemoveAt(index);
	pLib::Assert(m_listeners.Contains(listener) == false, "Something went wrong with the remove");
}

void EventManager::SendEvent(const EventBase& eventData)
{
	for (int i = 0; i < m_listeners.Count(); i++)
	{
		m_listeners[i]->HandleEvent(eventData);
	}
}
