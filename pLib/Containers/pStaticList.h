#pragma once


// TODO: Make pStaticList and pList share a common interface???
// Behaves the same as pList, except it always takes up the maximum
// amount of memory and can't grow beyond it's maximum size.
template <class Type, int Size>
class pStaticList
{
public:
	pStaticList() : m_count(0) {}
	~pStaticList() {}	// Nothing for destructor to do

	// Returns the maximum capacity of the list
	int Capacity() const { return Size; }

	// Returns the number of entries in the list
	int Count() const { return m_count; }

	// Returns 'true' if the list has no entries (ie. Count == 0)
	bool IsEmpty() const { return Count() == 0; }

	// Returns 'true' if the list is full (ie. Count == Capacity)
	bool IsFull() const { return Count() == Capacity(); }

	// Returns 'true' if the passed in index is valid, 'false' otherwise
	bool IsValidIndex(int index) const { return (index >= 0) && (index < Count()); }

	// Removes all values from the list and sets its Count to 0
	void Clear() { m_count = 0; }

	// Adds a value to the end of the list
	void Add(const Type& value)
	{
		pLib::Assert(m_count < Size);
		m_array[m_count++] = value;
	}

	// Adds multiple copies of a value to the end of the list
	void AddMultiple(const Type& value, int numInstances)
	{
		pLib::Assert((m_count + numInstances - 1) < Size);
		for (int i = 0; i < numInstances; i++)
		{
			m_array[m_count++] = value;
		}
	}

	// Bracket operator to make indexing like an array simple
	const Type& operator[](int index) const
	{
		pLib::Assert(IsValidIndex(index));
		return m_array[index];
	}

	// Non-const bracket operator
	Type& operator[](int index)
	{
		pLib::Assert(IsValidIndex(index));
		return m_array[index];
	}

	// Removes the element at 'index'.  All elements at higher indicies are shifted down by one.
	// Element order is maintained at the cost of performance.
	void RemoveAt(int index)
	{
		pLib::Assert(IsValidIndex(index));
		// Shift everything down, copying over the removed element
		Type* dst = &m_array[index];
		const Type* src = &m_array[index + 1];
		const int size = sizeof(Type)* ((m_count - index) - 1);
		memcpy(dst, src, size);
		// decrement the count
		m_count--;
	}

	// Removes the element at 'index' by copying over it with the element at the end.
	// Much faster than 'RemoveAt', but doesn't maintain element ordering.
	void RemoveAtFast(int index)
	{
		pLib::Assert(IsValidIndex(index));
		// Shrink the list by 1
		m_count--;
		// Copy the last element over the one to be deleted
		m_array[index] = m_array[m_count];
	}

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

	const Type* Ptr() const { return m_array; }
	Type* Ptr() { return m_array; }

private:
	int m_count;
	Type m_array[Size];
};
