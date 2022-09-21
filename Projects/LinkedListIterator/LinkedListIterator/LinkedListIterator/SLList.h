#pragma once
#include <functional>

template <typename T>
class TSLList
{
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
			return Current->Element;
		}

		const T& operator*() const
		{
			return Current->Element;
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

private:

	struct FNode
	{
		T Element;
		FNode* Next = nullptr;
	};

	FNode* Head = nullptr;
	FNode* Tail = nullptr;

	int Size = 0;

public:

	//-------------------------------------------------------------------------------------------
	//								CONSTRUCTORS & DESTRUCTORS
	//-------------------------------------------------------------------------------------------
	TSLList()
	{

	}

	//-------------------------------------------------------------------------------------------
	TSLList(const T& FirstElement)
	{
		Head = new FNode();
		Head -> Element = FirstElement;
		Tail = Head;
		Size = 1;
	}

	//-------------------------------------------------------------------------------------------
	TSLList(const TSLList<T>& OtherList)
	{
		FNode* Current = OtherList.Head;
		for (int i = 0; i < OtherList.Size; i++)
		{
			AddTail(Current->Element);
			Current = Current->Next;
		}
	}

	//-------------------------------------------------------------------------------------------
	TSLList& operator=(const TSLList<T>& OtherList)
	{
		Clear();
		FNode* Current = OtherList.Head;
		for (int i = 0; i < OtherList.Size; i++)
		{
			AddTail(Current->Element);
			Current = Current->Next;
		}
		return *this;
	}

	//-------------------------------------------------------------------------------------------
	~TSLList()
	{
		Clear();
	}

	//-------------------------------------------------------------------------------------------
	//										ACCESS
	//-------------------------------------------------------------------------------------------
	T& operator[](const int Index)
	{
		FNode* Node = GetNode(Index);
		return Node->Element;
	}

	//-------------------------------------------------------------------------------------------
	const T& operator[](const int Index) const
	{
		FNode* Node = GetNode(Index);
		return Node->Element;
	}

	//-------------------------------------------------------------------------------------------
	T& GetHead()
	{
		return Head->Element;
	}

	//-------------------------------------------------------------------------------------------
	const T& GetHead() const
	{
		return Head->Element;
	}

	//-------------------------------------------------------------------------------------------
	T& GetTail()
	{
		return Tail->Element;
	}

	//-------------------------------------------------------------------------------------------
	const T& GetTail() const
	{
		return Tail->Element;
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

	//-------------------------------------------------------------------------------------------
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

	//-------------------------------------------------------------------------------------------
	void Insert(const T& NewElement, const int Index)
	{
		if (Index < 0 || Index > Size) //Bounds Checking
		{
			return;
		}
		else if (Index == 0) //Head
		{
			AddHead(NewElement);
		}
		else if (Index == Size)
		{
			AddTail(NewElement);
		}
		else if(Index < Size)
		{
			FNode* Previous = GetNode(Index-1);

			FNode* NewNode = new FNode();
			NewNode->Element = NewElement;
			NewNode->Next = Previous->Next;

			Previous->Next = NewNode;

			Size++;
		}	
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
			FNode* NewHead = Head->Next;
			delete Head;
			Head = NewHead;

			if (Size == 1)
			{
				Tail = nullptr;
			}
		}
		else
		{
			FNode* Previous = GetNode(Index - 1);
			FNode* Current = Previous->Next;
			Previous->Next = Current->Next;
			delete Current;

			if (Index == Size - 1)
			{
				Tail = Previous;
			}
		}
		Size--;
	}

	//-------------------------------------------------------------------------------------------
	void Clear()
	{
		for (int i = 0; i < Size; i++)
		{
			FNode* Current = Head;
			Head = Head->Next;
			delete Current;
		}
		Tail = nullptr;
		Size = 0;
	}

	//-------------------------------------------------------------------------------------------
	//								TEMPLATES & PREDICATES
	//-------------------------------------------------------------------------------------------
	template<typename Pred>
	void ForEach(const Pred& Predicate)
	{
		FNode* Current = Head;
		for (int i = 0; i < Size; i++)
		{
			Predicate(Current->Element);
			Current = Current->Next;
		}
	}

	//-------------------------------------------------------------------------------------------
	template<typename Pred>
	T& FindByPredicate(const Pred& Predicate)
	{
		FNode* Current = Head;
		for (int i = 0; i < Size; i++)
		{
			if (Predicate(Current->Element))
			{
				return &Current->Element;
			}
			Current = Current->Next;
		}
		return nullptr;
	}

	//-------------------------------------------------------------------------------------------
	template<typename Pred>
	TSLList<T> FilterByPredicate(const Pred& Predicate)
	{
		TSLList<T> FilteredList;
		FNode* Current = Head;
		for (int i = 0; i < Size; i++)
		{
			if (Predicate(Current->Element))
			{
				FilteredList.AddTail(Current->Element);
			}
			Current = Current->Next;
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
			T Element = Current->Element;
			Current = Current->Next;

			if (Predicate(Current->Element))
			{
				Remove(i);
				i--;
			}
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



private:

	//-------------------------------------------------------------------------------------------
	//										UTILITY FUNCTIONS
	//-------------------------------------------------------------------------------------------
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