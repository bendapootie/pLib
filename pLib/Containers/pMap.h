#pragma once

// TODO: Remove all STL includes
#include <map>

template <class KeyType, class ValueType>
class pMap
{
public:
	// Returns the number of entries in the map
	int Count() const { return (int)m_map.size(); }

	// Returns 'true' if the list has no entries (ie. Count == 0)
	bool IsEmpty() const { return Count() == 0; }

	// Removes all values from the map and sets its Count to 0
	void Clear() { m_map.clear(); }

	// Adds a key/value pair to the map
	void Add(const KeyType& key, const ValueType& _value) { m_map.insert(key, value); }

	// Bracket operator for accessing map values via key
	// Note: If the key does not exist, this will create an entry and return a default object
	ValueType& operator[](const KeyType& _key) { return m_map[_key]; }

	// Function for finding values without risk of creating a default value
	bool TryGetValue(const KeyType& _key, __out const ValueType* _outValue) const
	{
		auto it = m_map.find(_key);
		if (it != m_map.end())
		{
			_outValue = &it->second;
			return true;
		}
		return false;
	}

	// Removes an element from the map by key
	void Remove(const KeyType& _key) { m_map.erase(_key); }

	// Returns 'true' if the given key has an entry in the map
	bool Contains(const KeyType& _key) const
	{
		return (m_map.find(_key) != m_map.end());
	}

	// TODO: Support for-each operator
	// - Need iterator, const_iterator, and const/non-const versions of begin() and end()

private:
	// TODO: Make this not use std::map
	std::map<KeyType, ValueType> m_map;
};
