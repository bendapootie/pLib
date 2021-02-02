#pragma once


// Wrapper for statically sized string.
// Provides error checking in debug builds and has no additional memory cost.
template <int MaxCapacity, bool ErrorOnOverflow = true>
class pStaticString
{
public:
	static constexpr int GetMaxCapacity() { return MaxCapacity; }

public:
	// c'tor to create empty string
	pStaticString()
	{
		static_assert(MaxCapacity > 0, "Verify positive capacity");
		m_array[0] = 0;
	}

	pStaticString(const char* c_str)
	{
		*this = c_str;
	}

	// Returns the maximum capacity
	int Capacity() const { return MaxCapacity; }

	// Returns the length of the string
	int Length() const { return m_length; }

	// Returns 'true' if the passed in index is valid, 'false' otherwise
	bool IsValidIndex(int index) const { return (index >= 0) && (index < m_length); }

	// Empties the string
	void Clear() { *this = ""; }

	bool IsTruncated() const { return m_isTruncated; }

	// Bracket operator to make indexing like an array simple
	char operator[](int index) const
	{
		pLib::Assert(IsValidIndex(index));
		return m_array[index];
	}

	char& operator[](int index)
	{
		pLib::Assert(IsValidIndex(index));
		return m_array[index];
	}

	void operator = (const char* c_str)
	{
		int i = 0;
		while ((i < (MaxCapacity - 1)) && (c_str[i] != 0))
		{
			m_array[i] = c_str[i];
			i++;
		}
		m_length = i;
		// null terminate string
		m_array[i] = 0;
		m_isTruncated = c_str[i] != m_array[i];
		pLib::Assert((ErrorOnOverflow && m_isTruncated) == false, "pStaticString overflowed");
	}
	
	bool operator < (const pStaticString<MaxCapacity>& other) const
	{
		return strcmp(m_array, other.m_array) < 0;
	}

	bool operator > (const pStaticString<MaxCapacity>& other) const
	{
		return strcmp(m_array, other.m_array) > 0;
	}

	bool operator == (const pStaticString<MaxCapacity>& other) const
	{
		return (m_length != other.m_length) ? false : (strcmp(m_array, other.m_array) == 0);
	}

	bool operator != (const pStaticString<MaxCapacity>& other) const
	{
		return !(*this == other);
	}

	const char* c_str() const { return m_array; }

	void Format(const char* text, ...);

private:
	// Putting the char array first so format strings can use this class directly
	// TODO: Not sure that's good practice, but it works /shrug
	char m_array[MaxCapacity];
	int m_length = 0;
	bool m_isTruncated = false;
};


template <int MaxCapacity, bool ErrorOnOverflow>
void pStaticString<MaxCapacity, ErrorOnOverflow>::Format(const char* text, ...)
{
	va_list args;
	va_start(args, text);
	const int nBuf = vsnprintf_s(m_array, MaxCapacity, _TRUNCATE, text, args);
	va_end(args);

	if (nBuf < 0)
	{
		m_length = MaxCapacity - 1;	// Take into account null terminator
		m_isTruncated = true;
		pLib::Assert(ErrorOnOverflow == false, "pStaticString overflowed");
	}
	else
	{
		m_length = nBuf;
		m_isTruncated = false;
	}
}
