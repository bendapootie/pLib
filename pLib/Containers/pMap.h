#pragma once

#include "pLib.h"
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

	// Returns true if map has an entry for the given key
	bool HasKey(const KeyType& _key) const { return m_map.find(_key) != m_map.end(); }

	// Adds a key/value pair to the map
	// If key already exists, sets the value associated with the key
	void Add(const KeyType& _key, const ValueType& _value) { m_map[_key] = _value; }

	// Bracket operator for accessing map values via key
	// Note: If the key does not exist, this will create an entry and return a default object
	ValueType& operator[](const KeyType& _key) { return m_map[_key]; }

	// Function for finding values without risk of creating a default value
	bool TryGetValue(const KeyType& _key, __out ValueType* _outValue) const
	{
		auto it = m_map.find(_key);
		if (it != m_map.end())
		{
			*_outValue = it->second;
			return true;
		}
		return false;
	}

	// Returns pointer to value in map or null if key isn't found
	// Note: This pointer is only valid until an add or remove is made to the map
	const ValueType* FindPointerToValue(const KeyType& _key) const
	{
		auto it = m_map.find(_key);
		if (it != m_map.end())
		{
			return &it->second;
		}
		return nullptr;
	}

	ValueType* FindPointerToValue(const KeyType& _key)
	{
		return const_cast<ValueType*>(const_cast<const pMap<KeyType, ValueType>*>(this)->FindPointerToValue(_key));
	}

	pList<KeyType> GetListOfKeys() const
	{
		pList<KeyType> keys;
		for (auto it = m_map.begin(); it != m_map.end(); it++)
		{
			keys.Add(it->first);
		}
		return keys;
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
