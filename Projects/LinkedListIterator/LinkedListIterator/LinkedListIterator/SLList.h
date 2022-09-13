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

	FSLList(const FSLList<T>& OtherList)
	{
		for (int i = 0; i < OtherList.Size; i++)
		{
			AddTail(OtherList[i]);
		}
	}

	~FSLList()
	{
		Clear();
	}

	T& operator[](const int Index)
	{
		FNode* Node = GetNode(Index);
		return Node->Element;
	}

	const T& operator[](const int Index) const
	{
		FNode* Node = GetNode(Index);
		return Node->Element;
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

	bool IsEmpty() const
	{
		return Size == 0;
	}

	int GetSize() const
	{
		return Size;
	}

	void AddHead(const T& NewElement)
	{
		FNode* Node = new FNode;
		Node->Element = NewElement;
		Node->Next = Head;
		Head = Node;

		if (!Tail)
		{
			Tail = Head;
		}
		Size++;
	}

	void AddTail(const T& NewElement)
	{
		if (Tail)
		{
			FNode* Node = new FNode;
			Node->Element = NewElement;
			Node->Next = nullptr;

			Tail->Next = Node;
			Tail = Node;

			Size++;
		}
		else //If Tail doesn't exist, there is no Head either
		{
			AddHead(NewElement);
		}
	}

	void Insert(const T& NewElement, const int Index)
	{
		if (Index < 0 || Index >= Size) //Bounds Checking
		{
			return;
		}
		else if (Index == 0) //Head
		{
			AddHead(NewElement)
		}
		else if(Index < Size)
		{
			FNode* Previous = GetNode(Index);

			FNode* NewNode = new FNode();
			NewNode->Element = NewElement;
			NewNode->Next = Previous->Next;

			Previous->Next = NewNode;

			Size++;
		}	
	}

	void Delete(const int Index)
	{
		if (Index < 0 || Index >= Size) //Bounds Checking
		{
			return;
		}
		else if (Index == 0) //Head
		{
			FNode* NewHead = Head->Next;
			delete Head;
			Head = NewHead;
		}
		else
		{
			FNode* Previous = GetNode(Index - 1);
			FNode* Current = Previous->Next;
			Previous->Next = Current->Next;
			delete Current;
		}
		Size--;
	}

	void Clear()
	{
		for (int i = 0; i < Size; i++)
		{
			FNode* Current = Head;
			Head = Head->Next;
			delete Current;
		}
		Size = 0;
	}


private:

	FNode* GetNode(const int Index)
	{
		FNode* Current = Head;
		for (int i = 0; i < Index; i++)
		{
			Current = Current->Next;
		}
		return Current;
	}
};