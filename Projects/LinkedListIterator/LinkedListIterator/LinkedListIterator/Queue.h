#pragma once
#include "SLList.h"

template <typename T>
class TQueue
{
private:

	TSLList<T> List;

public:

	TQueue()
	{

	}

	T& Front()
	{
		return List.GetHead();
	}

	const T& Front() const
	{
		return List.GetHead();
	}

	bool IsEmpty()
	{
		return List.IsEmpty();
	}

	int GetSize()
	{
		return List.GetSize();
	}

	void Dequeue()
	{
		List.RemoveHead();
	}

	void Enqueue(const T& Data)
	{
		List.AddTail(Data);
	}
};