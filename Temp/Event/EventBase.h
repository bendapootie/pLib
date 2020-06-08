#pragma once

enum class EventType
{
	Invalid = -1,
	ResourceUpdate = 0,		// Resource addition, removal
	EntityUpdate,			// Entity addition, removal, changes
	Count	// Number of EventType entries
};



//=============================================================================
// EventBase
//=============================================================================
class EventBase
{
public:
	EventBase() : m_type(EventType::Invalid) {}
	EventBase(EventType type) : m_type(type) {}

	EventType GetEventType() const { return m_type; }

private:
	const EventType m_type;
};
