#pragma once

template<typename T>
class TDynamicArray
{
private:
	int Capacity = 0;
	int Size = 0;
	T* Array;

public:

	//-------------------------------------------------------------------------------------------
	//								CONSTRUCTORS & DESTRUCTORS
	//-------------------------------------------------------------------------------------------
	
	TDynamicArray()
	{
		
	}

	TDynamicArray(const int InCapacity)
	{
		Capacity = InCapacity;
		Array = new T[Capacity];
	}

	//-------------------------------------------------------------------------------------------
	~TDynamicArray()
	{
		delete[] Array;
	}

	//-------------------------------------------------------------------------------------------
	TDynamicArray(const TDynamicArray& OtherArray)
	{
		Append(OtherArray);
	}

	//-------------------------------------------------------------------------------------------
	//										OPERATORS
	//-------------------------------------------------------------------------------------------

	T& operator[](const int Index)
	{
		return Array[Index];
	}

	//-------------------------------------------------------------------------------------------
	const T& operator[](const int Index) const
	{
		return Array[Index];
	}

	//-------------------------------------------------------------------------------------------
	void operator=(const TDynamicArray<T>& OtherArray)
	{
		Clear();
		Append(OtherArray);
	}

	//-------------------------------------------------------------------------------------------
	//											ACCESSING
	//-------------------------------------------------------------------------------------------

	T& Front()
	{
		return Array[0];
	}

	//-------------------------------------------------------------------------------------------
	const T& Front() const
	{
		return Array[0];
	}

	//-------------------------------------------------------------------------------------------
	T& Back()
	{
		return Array[Size - 1];
	}

	//-------------------------------------------------------------------------------------------
	const T& Back() const
	{
		return Array[Size - 1];
	}

	//-------------------------------------------------------------------------------------------
	T* GetData()
	{
		return Array;
	};

	//-------------------------------------------------------------------------------------------
	const T* GetData() const
	{
		return Array;
	};

	//-------------------------------------------------------------------------------------------
	//											CAPACITY
	//-------------------------------------------------------------------------------------------

	bool IsEmpty()
	{
		return Size == 0;
	}

	//-------------------------------------------------------------------------------------------
	int GetSize()
	{
		return Size;
	}

	//-------------------------------------------------------------------------------------------
	int GetCapacity()
	{
		return Capacity;
	}

	//-------------------------------------------------------------------------------------------
	bool Reserve(const int NewCapacity)
	{
		if (NewCapacity <= Capacity)
		{
			return false;
		}

		T* NewArray = new T[NewCapacity];
		for (int i = 0; i < Size; i++)
		{
			NewArray[i] = Array[i];
		}

		delete[] Array;
		Array = NewArray;

		Capacity = NewCapacity;
		return true;
	}

	//-------------------------------------------------------------------------------------------
	bool ShrinkToFit()
	{
		if (Capacity == Size)
		{
			return false;
		}

		T* NewArray = new T[Size];
		for (int i = 0; i < Size; i++)
		{
			NewArray[i] = Array[i];
		}

		delete[] Array;
		Array = NewArray;

		Capacity = Size;
		return true;
	}

	//-------------------------------------------------------------------------------------------
	//											MODIFIERS
	//-------------------------------------------------------------------------------------------

	void Clear()
	{
		Size = 0;
	}

	//-------------------------------------------------------------------------------------------
	void PushBack(const T Item)
	{
		if (Size == Capacity)
		{
			if (Capacity == 0)
			{
				Reserve(1);
			}
			Reserve(Capacity * 2);
		}
		Array[Size] = Item;
		Size++;
	}

	//-------------------------------------------------------------------------------------------
	void PopBack()
	{
		Size--;
	}

	//-------------------------------------------------------------------------------------------
	bool Insert(const T Item, const int Index)
	{
		if (Index > Size)
		{
			return false;
		}

		if (Index == Size)
		{
			PushBack(Item);
			Size++;
			return true;
		}

		if (Size == Capacity)
		{
			Reserve(Capacity * 2);
		}
		
		for (int i = Size; i > Index; i--)
		{
			Array[i] = Array[i-1];
		}

		Array[Index] = Item;
		Size++;
		return true;
	}

	//-------------------------------------------------------------------------------------------
	bool Erase(const int Index)
	{
		if (Index > Size)
		{
			return false;
		}

		if (Index == Size)
		{
			PopBack();
			Size--;
			return true;
		}

		for (int i = 0; i < Size - 1; i++)
		{
			Array[i] = Array[i + 1];
		}
		Size--;
		return true;
	}

	//-------------------------------------------------------------------------------------------
	void Resize(const int NewSize)
	{
		if (Size > Capacity)
		{
			Reserve(NewSize);
		}
		Size = NewSize;
	}

	//-------------------------------------------------------------------------------------------
	void Resize(const int NewSize, const T Item)
	{
		if (Size <= NewSize)
		{
			Size = NewSize;
		}
		else
		{
			if (NewSize > Capacity)
			{
				Reserve(NewSize);
			}
			for (int i = Size; i < NewSize; i++)
			{
				Array[i] = Item;
			}
		}
	}

	//-------------------------------------------------------------------------------------------
	void Append(const TDynamicArray<T> OtherArray)
	{
		int NewSize = Size + OtherArray.GetSize();
		Reserve(NewSize);

		for (int i = 0; i < OtherArray.GetSize(); i++)
		{
			PushBack(OtherArray[i]);
		}
	}

	//-------------------------------------------------------------------------------------------
	//											CUSTOM METHODS
	//-------------------------------------------------------------------------------------------

	void RefactorCapacityTo(const int NewCapacity)
	{
		if (!Reserve(NewCapacity))
		{
			if (NewCapacity == Size)
			{
				return;
			}

			T* NewArray = new T[NewCapacity];
			if (Size > NewCapacity)
			{
				Size = NewCapacity;
			}

			for (int i = 0; i < Size; i++)
			{
				NewArray[i] = Array[i];
			}

			Capacity = NewCapacity;
			delete[] Array;
			Array = NewArray;
		}
	}

	//-------------------------------------------------------------------------------------------
	void Fill(const T Item, const bool FillToCapacity)
	{
		if (FillToCapacity)
		{
			for (int i = 0; i < Capacity; i++)
			{
				Array[i] = Item;
			}
		}
		else
		{
			for (int i = 0; i < Size; i++)
			{
				Array[i] = Item;
			}
		}
	}
};