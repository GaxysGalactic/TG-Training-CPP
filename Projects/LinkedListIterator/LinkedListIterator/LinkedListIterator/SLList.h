#pragma once

template <typename T>
class FSLList
{

private:

	struct FNode
	{
		T Element;
		FNode* Next;
	};

	FNode* Head;
	FNode* Tail;

	int Size;

public:

	FSLList()
	{
		Head = nullptr;
		Tail = nullptr;
		Size = 0;
	}

	FSLList(const T& FirstElement)
	{
		Head = new FNode();
		Head -> Element = FirstElement;
		Tail = Head;
		Size = 1;
	}

	T& operator[](const int Index)
	{
		FNode* Current = Head;
		for (int i = 0; i < Index; i++)
		{
			Current = Current->Next;
		}
		return Current->Element;
	}

	const T& operator[](const int Index) const
	{
		FNode* Current = Head;
		for (int i = 0; i < Index; i++)
		{
			Current = Current->Next;
		}
		return Current->Element;
	}

	T& Head()
	{
		return Head->Element;
	}

	const T& Head() const
	{
		return Head->Element;
	}

	T& Tail()
	{
		return Tail->Element;
	}

	const T& Tail() const
	{
		return Tail->Element;
	}

};