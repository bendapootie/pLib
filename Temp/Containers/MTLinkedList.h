#pragma once

template<class Type>
class MTLinkedListNode
{
private:
	// Private constructor and destructor to ensure Nodes created and
	// destroyed with CreateNode and DestroyNode defined in MTLinkedList.
	MTLinkedListNode() { pLib::Error("MTLinkedListNode constructor should never be called.  Use CreateNode/DestroyNode instead"); }
	~MTLinkedListNode() { pLib::Error("MTLinkedListNode destructor should never be called.  Use CreateNode/DestroyNode instead"); }

public:
	MTLinkedListNode<Type>* GetNext() { return reinterpret_cast<MTLinkedListNode<Type>*>(SListEntry.Next); }

	// Reverses a linked list in linear time.  Repoints the passed in node pointer to the new front node.
	static void ReverseList(MTLinkedListNode<Type>** nodeList)
	{
		// TODO: Move this function to a .inl file

		// Early out if passed a null pointer or an empty list
		if ((nodeList == nullptr) || (*nodeList == nullptr))
		{
			return;
		}

		MTLinkedListNode<Type>* previous = nullptr;
		MTLinkedListNode<Type>* current = *nodeList;
		while (current != nullptr)
		{
			MTLinkedListNode<Type>* next = current->GetNext();
			current->SListEntry.Next = reinterpret_cast<SLIST_ENTRY*>(previous);
			previous = current;
			current = next;
		}

		// Set nodeList to the new front of the list
		*nodeList = previous;
	}

public:
	// SLIST_ENTRY needs to be first so we can guarantee memory alignment
	SLIST_ENTRY SListEntry;
	Type Value;
};


// Linked list that can be accessed by multiple threads.
// Supports multiple producers and multiple consumers.
// This list supports FILO (ie. Stack) functionality with Push and Pop functions.
//
// To get FIFO (ie. Queue) functionality, Flush can be called by a single
// consumer with the returned list processed in reverse order.
template<class Type>
class MTLinkedList
{
public:
	MTLinkedList();
	~MTLinkedList();

	// Returns the number of entries in the list
	// Note: This isn't const because 'QueryDepthSList' needs a mutable list
	int Count();

	// Adds a value to the top of the stack.  A node is created to contain it.
	// Returns the previous head.
	// Note: The return value should generally not be used for anything except
	// comparing to nullptr to see if the list was previously empty.
	MTLinkedListNode<Type>* Push(MTLinkedListNode<Type>* node);

	// Removes the top value from the stack and returns it (or nullptr if empty).
	// It's the caller's responsibility to Destory the returned node.
	MTLinkedListNode<Type>* Pop();

	// Empties the list, returning the first node (or nullptr if empty).
	// It's the caller's responsibility to Destroy the entire returned chain.
	MTLinkedListNode<Type>* Flush();

public:
	// Helper functions to create and destroy nodes
	// These are the only way to create MTLinkedListNode instances
	static MTLinkedListNode<Type>* CreateNode(const Type& value);
	static void DestroyNode(MTLinkedListNode<Type>* node);

public:
	// Memory Alignment requirement for SLIST_xxx members
	static const int MemoryByteAlignment = MEMORY_ALLOCATION_ALIGNMENT;

private:
	SLIST_HEADER m_listHeader;
};


//-----------------------------------------------------------------------------
// MTLinkedList
//-----------------------------------------------------------------------------
template<class Type>
inline MTLinkedList<Type>::MTLinkedList()
{
	pLib::Assert((int)(&m_listHeader) % MemoryByteAlignment == 0, "m_listHeader needs to be memory aligned");
	InitializeSListHead(&m_listHeader);
}

template<class Type>
inline MTLinkedList<Type>::~MTLinkedList()
{
	pLib::Assert(Count() == 0, "Deleting an MTLinkedList that still has entries!  Potential memory leak.");
}

// Helper function to create and destroy nodes
template<class Type>
inline MTLinkedListNode<Type>* MTLinkedList<Type>::CreateNode(const Type& value)
{
	void* newMemory = _aligned_malloc(sizeof(MTLinkedListNode<Type>), MemoryByteAlignment);
	MTLinkedListNode<Type>* newNode = reinterpret_cast<MTLinkedListNode<Type>*>(newMemory);
	pLib::Assert((void*)&newNode->SListEntry == (void*)newNode, "SListEntry needs to be the first member in the Node so memory alignment can be assured");
	newNode->Value = value;
	return newNode;
}

template<class Type>
inline void MTLinkedList<Type>::DestroyNode(MTLinkedListNode<Type>* node)
{
	pLib::Assert((void*)&(node->SListEntry) == (void*)node, "SListEntry needs to be the first member in the Node so memory alignment can be assured");
	_aligned_free(node);
}

template<class Type>
inline int MTLinkedList<Type>::Count()
{
	return QueryDepthSList(&m_listHeader);
}

template<class Type>
inline MTLinkedListNode<Type>*  MTLinkedList<Type>::Push(MTLinkedListNode<Type>* node)
{
	PSLIST_ENTRY listEntry = InterlockedPushEntrySList(&m_listHeader, &(node->SListEntry));
	MTLinkedListNode<Type>* previousHead = reinterpret_cast<MTLinkedListNode<Type>*>(listEntry);
	return previousHead;
}

template<class Type>
inline MTLinkedListNode<Type>* MTLinkedList<Type>::Pop()
{
	Type returnValue;
	PSLIST_ENTRY listEntry = InterlockedPopEntrySList(&m_listHeader);
	MTLinkedListNode<Type>* node = reinterpret_cast<MTLinkedListNode<Type>*>(listEntry);
	return node;
}

template<class Type>
inline MTLinkedListNode<Type>* MTLinkedList<Type>::Flush()
{
	PSLIST_ENTRY listEntry = InterlockedFlushSList(&m_listHeader);
	MTLinkedListNode<Type>* node = reinterpret_cast<MTLinkedListNode<Type>*>(listEntry);
	return node;
}
