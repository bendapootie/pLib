#pragma once


// Wrapper for statically sized circular queue.
// Provides error checking in debug builds
// and has no additional memory cost.
template <class Type, int MaximumCapacity>
class pCircularQueue
{
public:
	pCircularQueue() { Clear(); }

	// Returns the maximum capacity of the queue
	int Capacity() const { return MaximumCapacity; }

	// Returns the number of entries in the list
	int Count() const { return m_count; }

	// Returns 'true' if the list has no entries (ie. Count == 0)
	bool IsEmpty() const { return Count() == 0; }

	// Returns 'true' if the list is full (ie. Count == Capacity)
	bool IsFull() const { return Count() == Capacity(); }

	// Returns 'true' if the passed in index is valid, 'false' otherwise
	bool IsValidIndex(int index) const { return (index >= 0) && (index < Count()); }

	// Removes all values from the list and sets its Count to 0
	void Clear() { m_firstIndex = 0;  m_count = 0; }

	// Adds a value to the end of the queue (Same as PushBack)
	// 'Add' function is kept here for consistency with other containers
	void Add(const Type& value)
	{
		PushBack(value);
	}

	// Bracket operator to make indexing like an array simple
	const Type& operator[](int index) const
	{
		pLib::Assert(IsValidIndex(index));
		const int arrayIndex = (m_firstIndex + index) % MaximumCapacity;
		return m_array[arrayIndex];
	}

	Type& operator[](int index)
	{
		pLib::Assert(IsValidIndex(index));
		const int arrayIndex = (m_firstIndex + index) % MaximumCapacity;
		return m_array[arrayIndex];
	}

	// Return the first element in the queue
	const Type& Front() const
	{
		return (*this)[0];
	}

	Type& Front()
	{
		return (*this)[0];
	}

	// Return the last element in the queue
	const Type& Back() const
	{
		return (*this)[m_count - 1];
	}

	Type& Back()
	{
		return (*this)[m_count - 1];
	}

	// Adds a value to the end of the queue
	void PushBack(const Type& value)
	{
		pLib::Assert(m_count < Capacity());
		const int arrayIndex = (m_firstIndex + m_count) % MaximumCapacity;
		m_array[arrayIndex] = value;
		m_count++;
	}

	// Adds a value to the front of the queue
	void PushFront(const Type& value)
	{
		pLib::Assert(m_count < Capacity());
		m_firstIndex = (m_firstIndex + MaximumCapacity - 1) % MaximumCapacity;
		m_count++;
		m_array[m_firstIndex] = value;
	}

	// Removs the first element in the queue and returns a copy of it
	Type PopFront()
	{
		Type value = Front();
		m_firstIndex++;
		m_count--;
		return value;
	}

	// Removs the last element in the queue and returns a copy of it
	Type PopBack()
	{
		Type value = Back();
		m_count--;
		return value;
	}

private:
	int m_firstIndex;
	int m_count;
	Type m_array[MaximumCapacity];
};
