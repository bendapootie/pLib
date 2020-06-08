#pragma once

//--------------------------------------------------------------------------------------
// Helper class to facilitate using the PImpl (Private Implementation) pattern.
//
// The PImpl pattern is a work-around for the fact that in C++ you generally declare
// your entire class in the header.
//
// Todo: Show Example of usage
//--------------------------------------------------------------------------------------
template <class Type>
class PImpl
{
public:
	PImpl() { m_data = new Type(); }
	~PImpl() { delete m_data; }

	// Allow for pointer-like access to contained type
	inline Type* operator -> () { return m_data; }
	inline const Type* operator -> () const { return m_data; }

private:
	// Todo: Should this use the new C++11 pointer goodies?
	// Using "std::unique_ptr<Type>" could be safer.
	Type* m_data;
};
