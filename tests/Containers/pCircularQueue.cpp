#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace pLib_Test
{
	static void TestErrorHandler(pLib::ErrorLevel errorLevel, const char* message)
	{
		OutputDebugString(message);
		if (errorLevel >= pLib::ErrorLevel::Error)
		{
			throw message;
		}
	}

	TEST_CLASS(Test_Containers_CircularQueue)
	{
	public:
		
		TEST_METHOD(Test_CircularQueue)
		{
			pLib::PushErrorHandler(TestErrorHandler);
			const int capacity = 5;
			pCircularQueue<int, capacity> queue;

			// Should have an empty queue here with a max capacity of 4
			Assert::IsTrue(queue.Capacity() == capacity, L"Empty queue should report a capacity correctly");
			Assert::IsTrue(queue.Count() == 0, L"Empty queue should report zero count");
			for (int i = -1; i < queue.Capacity() + 1; i++)
			{
				Assert::IsTrue(queue.IsValidIndex(i) == false, L"An empty queue shouldn't have any valid indicies");
			}

			try { auto a = queue.Front(); Assert::Fail(L"Index out of bounds expected"); }
			catch (...) {}	// Exception expected
			try { auto a = queue.Back(); Assert::Fail(L"Index out of bounds expected"); }
			catch (...) {}	// Exception expected

			// Add a single item
			queue.PushBack(12345);
			Assert::IsTrue(queue.Count() == 1);
			Assert::IsTrue(queue[0] == 12345);
			Assert::IsTrue(queue.Front() == queue[0]);
			Assert::IsTrue(queue.Back() == queue.Front());
			try {
				int value = queue[1];
				Assert::Fail(L"Index out of bounds should have thrown an exception");
			}
			catch(...)
			{
				// Exception expected
			}
			queue.Front() = 54321;
			Assert::IsTrue(queue.Back() == queue.Front());

			int oldFront = queue.PopFront();
			Assert::IsTrue(oldFront == 54321);
			Assert::IsTrue(queue.Count() == 0);

			// Add and remove several items and verify resulting state
			queue.PushBack(2);
			Assert::IsTrue(queue.Front() == 2);
			Assert::IsTrue(queue.Back() == 2);
			queue.PushBack(3);
			Assert::IsTrue(queue.Front() == 2);
			Assert::IsTrue(queue.Back() == 3);
			queue.PushFront(1);
			Assert::IsTrue(queue.Front() == 1);
			Assert::IsTrue(queue.Back() == 3);
			queue.PushFront(0);
			Assert::IsTrue(queue.Front() == 0);
			Assert::IsTrue(queue.Back() == 3);
			queue.PushBack(4);
			Assert::IsTrue(queue.Front() == 0);
			Assert::IsTrue(queue.Back() == 4);
			Assert::IsTrue(queue.Count() == 5);
			Assert::IsTrue(queue.IsValidIndex(-1) == false);
			for (int i = 0; i < queue.Count(); i++)
			{
				Assert::IsTrue(queue.IsValidIndex(i));
				Assert::IsTrue(queue[i] == i);
			}
			Assert::IsTrue(queue.IsValidIndex(5) == false);

			Assert::IsTrue(queue.PopFront() == 0);
			Assert::IsTrue(queue.Front() == 1);
			queue.PushBack(5);
			Assert::IsTrue(queue.Front() == 1);
			Assert::IsTrue(queue.Back() == 5);

			queue.Clear();
			Assert::IsTrue(queue.Count() == 0);
		}

	private:
	};
}