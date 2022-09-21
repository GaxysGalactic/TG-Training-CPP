#pragma once

template <typename T>
class TDLList
{
//-------------------------------------------------------------------------------------------
//											MEMBERS
//-------------------------------------------------------------------------------------------
private:

	struct FNode
	{
		T Data;
		FNode* Next = nullptr;
		FNode* Previous = nullptr;
	};

	FNode* Head = nullptr;
	FNode* Tail = nullptr;

	int Size = 0;

public:

	class FIterator
	{
	private:

		FNode* Current = nullptr;

	public:

		FIterator(FNode* InCurrent)
		{
			Current = InCurrent;
		}

		FIterator& operator++()
		{
			Current = Current->Next;
			return *this;
		}

		T& operator*()
		{
			return Current->Data;
		}

		const T& operator*() const
		{
			return Current->Data;
		}

		bool operator!=(FIterator Other)
		{
			return Current != Other.Current;
		}

		const bool operator!=(FIterator Other) const
		{
			return Current != Other.Current;
		}
	};

//-------------------------------------------------------------------------------------------
//											FUNCTIONS
//-------------------------------------------------------------------------------------------
public:

	//-------------------------------------------------------------------------------------------
	//								CONSTRUCTORS & DESTRUCTORS
	//-------------------------------------------------------------------------------------------
	TDLList()
	{

	}

	//-------------------------------------------------------------------------------------------
	TDLList(const T& InData)
	{
		Head = new FNode();
		Head->Data = InData;
		Tail = Head;
		Size = 1;
	}

	//-------------------------------------------------------------------------------------------
	TDLList(const TDLList<T>& OtherList)
	{
		FNode* Current = OtherList.Head;
		for (int i = 0; i < OtherList.Size; i++)
		{
			AddTail(Current->Data);
			Current = Current->Next;
		}
	}

	//-------------------------------------------------------------------------------------------
	TDLList& operator=(const TDLList<T>& OtherList)
	{
		Clear();
		FNode* Current = OtherList.Head;
		for (int i = 0; i < OtherList.Size; i++)
		{
			AddTail(Current->Data);
			Current = Current->Next;
		}
		return *this;
	}

	//-------------------------------------------------------------------------------------------
	~TDLList()
	{
		Clear();
	}

	//-------------------------------------------------------------------------------------------
	//										ACCESS
	//-------------------------------------------------------------------------------------------
	T& operator[](const int Index)
	{
		FNode* Node = GetNode(Index);
		return Node->Data;
	}

	//-------------------------------------------------------------------------------------------
	const T& operator[](const int Index) const
	{
		FNode* Node = GetNode(Index);
		return Node->Data;
	}

	//-------------------------------------------------------------------------------------------
	T& GetHead()
	{
		return Head->Data;
	}

	//-------------------------------------------------------------------------------------------
	const T& GetHead() const
	{
		return Head->Data;
	}

	//-------------------------------------------------------------------------------------------
	T& GetTail()
	{
		return Tail->Data;
	}

	//-------------------------------------------------------------------------------------------
	const T& GetTail() const
	{
		return Tail->Data;
	}

	//-------------------------------------------------------------------------------------------
	//											SIZE
	//-------------------------------------------------------------------------------------------
	bool IsEmpty() const
	{
		return Size == 0;
	}

	//-------------------------------------------------------------------------------------------
	int GetSize() const
	{
		return Size;
	}

	//-------------------------------------------------------------------------------------------
	//										MODIFIERS
	//-------------------------------------------------------------------------------------------
	void AddHead(const T& NewData)
	{
		FNode* Node = new FNode;
		Node->Data = NewData;
		Node->Next = Head;

		if (!Head)
		{
			Tail = Node;
		}
		else
		{
			Head->Previous = Node;
		}
		Head = Node;
		++Size;
	}

	//-------------------------------------------------------------------------------------------
	void AddTail(const T& NewData)
	{
		if (Tail)
		{
			FNode* Node = new FNode;
			Node->Data = NewData;
			Node->Previous = Tail;
			Tail->Next = Node;
			Tail = Node;

			++Size;
		}
		else
		{
			AddHead(NewData);
		}
	}

	//-------------------------------------------------------------------------------------------
	void Insert(const T& NewData, const int Index)
	{
		if (Index < 0 || Index > Size) //Bounds Checking
		{
			return;
		}
		else if (Index == 0) //Head
		{
			AddHead(NewData);
		}
		else if (Index == Size) //Tail
		{
			AddTail(NewData);
		}
		else if (Index < Size)
		{
			FNode* Current = GetNode(Index);
			FNode* NewNode = new FNode;

			NewNode->Data = NewData;
			NewNode->Next = Current;
			NewNode->Previous = Current->Previous;

			Current->Previous->Next = NewNode;
			Current->Previous = NewNode;

			Size++;
		}
	}

	//-------------------------------------------------------------------------------------------
	void RemoveHead()
	{
		FNode* NewHead = Head->Next;
		delete Head;
		Head = NewHead;

		if (Size == 1)
		{
			Tail = nullptr;
		}
		else
		{
			Head->Previous = nullptr;
		}
		--Size;
	}

	//-------------------------------------------------------------------------------------------
	void Remove(const int Index)
	{
		if (Index < 0 || Index >= Size) //Bounds Checking
		{
			return;
		}
		else if (Index == 0) //Head
		{
			RemoveHead();
		}
		else
		{
			FNode* Current = GetNode(Index);
			Current->Previous->Next = Current->Next;

			if (Index == Size - 1)
			{
				Tail = Current->Previous;
			}
			else
			{
				Current->Next->Previous = Current->Previous;
			}
			delete Current;
			--Size;
		}
	}

	//-------------------------------------------------------------------------------------------
	void Clear()
	{
		while (Head)
		{
			RemoveHead();
		}
	}

	//-------------------------------------------------------------------------------------------
	//										ITERATOR
	//-------------------------------------------------------------------------------------------
	FIterator begin()
	{
		return FIterator(Head);
	}

	//-------------------------------------------------------------------------------------------
	FIterator end()
	{
		return FIterator(nullptr);
	}

	//-------------------------------------------------------------------------------------------
	//								TEMPLATES & PREDICATES
	//-------------------------------------------------------------------------------------------
	template<typename Pred>
	void ForEach(const Pred& Predicate)
	{
		for (T& Current : *this)
		{
			Predicate(Current);
		}
	}

	//-------------------------------------------------------------------------------------------
	template<typename Pred>
	T& FindByPredicate(const Pred& Predicate)
	{
		for (T& Current : *this)
		{
			if (Predicate(Current))
			{
				return Current;
			}
		}
		return nullptr;
	}

	//-------------------------------------------------------------------------------------------
	template<typename Pred>
	TDLList<T> FilterByPredicate(const Pred& Predicate)
	{
		TDLList<T> FilteredList;

		for (T& Current : *this)
		{
			if (Predicate(Current))
			{
				FilteredList.AddTail(Current);
			}
		}
		return FilteredList;
	}

	//-------------------------------------------------------------------------------------------
	template<typename Pred>
	void RemoveAllByPredicate(const Pred& Predicate)
	{
		FNode* Current = Head;
		for (int i = 0; i < Size; i++)
		{
			T Data = Current->Data;
			Current = Current->Next;

			if (Predicate(Current->Data))
			{
				Remove(i);
				i--;
			}
		}
	}

private:

	//-------------------------------------------------------------------------------------------
	//										UTILITY FUNCTIONS
	//-------------------------------------------------------------------------------------------
	FNode* GetNode(const int Index)
	{
		FNode* Current;
		if (Index < Size / 2)
		{
			Current = Head;
			for (int i = 0; i < Index; ++i)
			{
				Current = Current->Next;
			}
		}
		else
		{
			Current = Tail;
			for (int i = Size-1; i > Index; --i)
			{
				Current = Current->Previous;
			}
		}
		return Current;
	}
};