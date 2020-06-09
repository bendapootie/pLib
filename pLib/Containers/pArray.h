#pragma once


// Wrapper for statically sized arrays.  Provides error checking in debug builds
// and has no additional memory cost.
template <class Type, int Size>
class pArray
{
public:
	// Returns the maximum capacity.  For arrays, this is always the same as Count.
	int Capacity() const { return Size; }

	// Returns the number of entries in the list
	int Count() const { return Size; }

	// Returns 'true' if the passed in index is valid, 'false' otherwise
	bool IsValidIndex(int index) const { return (index >= 0) && (index < Size); }

	// Memsets all data to 0
	void Zero() { ZeroMemory(m_array, sizeof(m_array)); }

	// Bracket operator to make indexing like an array simple
	const Type& operator[](int index) const
	{
		pLib::Assert(IsValidIndex(index));
		return m_array[index];
	}

	Type& operator[](int index)
	{
		pLib::Assert(IsValidIndex(index));
		return m_array[index];
	}

	const Type* Ptr() const { return m_array; }
	Type* Ptr() { return m_array; }

private:
	Type m_array[Size];
};
