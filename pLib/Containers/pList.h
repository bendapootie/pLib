#pragma once

// TODO: Remove all STL includes
#include <vector>
#include <algorithm>	// for std::sort
#include <functional>	// for std::function

template <class Type>
class pList
{
public:
	// Returns the maximum capacity of the list
	int Capacity() const { return Math::Int32Max; }

	// Returns the number of entries in the list
	int Count() const { return (int)m_list.size(); }

	// Returns 'true' if the list has no entries (ie. Count == 0)
	bool IsEmpty() const { return Count() == 0; }

	// Returns 'true' if the list is full (ie. Count == Capacity)
	bool IsFull() const { return Count() == Capacity(); }

	// Returns 'true' if the passed in index is valid, 'false' otherwise
	bool IsValidIndex(int index) const { return (index >= 0) && (index < Count()); }

	// Removes all values from the list and sets its Count to 0
	void Clear() { m_list.clear(); }

	// Adds a value to the end of the list
	void Add(const Type& value) { m_list.push_back(value); }

	// Adds multiple copies of a value to the end of the list
	void AddMultiple(const Type& value, int numInstances)
	{
		m_list.reserve(Count() + numInstances);
		for (int i = 0; i < numInstances; i++)
		{
			m_list.push_back(value);
		}
	}

	// Allocates memory for at least 'newCount' entries
	// Useful as an optimization when the final size of a list is known ahead of time
	void Reserve(int newCount) { m_list.reserve(newCount); }

	// Resizes the list.  If 'newSize' is larger than Count(), 'value' is copied into each of the new entries
	void Resize(int newCount, const Type& value) { m_list.resize(newCount, value); }

	// Bracket operator to make indexing like an array simple
	const Type& operator[](int index) const { return m_list.at(index); }
	Type& operator[](int index) { return m_list.at(index); }

	// Removes the element at 'index'.  All elements at higher indicies are shifted down by one.
	void RemoveAt(int index) { m_list.erase(m_list.begin() + index); }

	// Removes the element at 'index' by copying over it with the element at the end.
	// Much faster than 'RemoveAt', but doesn't maintain element ordering.
	void RemoveAtFast(int index) { m_list[index] = m_list.back(); m_list.pop_back(); }

	// Does a linear search through the list for the 'search' item.
	// If found, returns 'true' and sets 'outIndex' to the index
	// If not found, returns 'false' and leaves 'outIndex' undefined
	bool FindIndex(const Type& search, int& outIndex)
	{
		for (int i = 0; i < Count(); i++)
		{
			if (operator[](i) == search)
			{
				outIndex = i;
				return true;
			}
		}
		return false;
	}

	// Does a linear search through the list for the 'search' item.
	// If found, returns 'true'.  If not found, returns 'false'.
	bool Contains(const Type& search)
	{
		int index;
		return FindIndex(search, index);
	}
	
	void Sort()
	{
		std::sort(m_list.begin(), m_list.end());
	}

 	void Sort(std::function<bool(const Type& a, const Type& b)> comparison)
 	{
 		std::sort(m_list.begin(), m_list.end(), comparison);
 	}

	// TODO: Support for-each operator
	// - Need iterator, const_iterator, and const/non-const versions of begin() and end()

private:
	// TODO: Make this not use std::vector
	std::vector<Type> m_list;
};
