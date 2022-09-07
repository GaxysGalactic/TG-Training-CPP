#pragma once

template<typename T>
class TDynamicArray
{
private:
	int Capacity;
	int Size;
	T* Array;

public:

	TDynamicArray(const int InCapacity)
	{
		Capacity = InCapacity;
		Size = 0;

		Array = new T[InCapacity];
	}

	~TDynamicArray()
	{
		delete[] Array;
	}

	T& operator[](const int Index)
	{
		return Array[Index];
	}

	const T& operator[](const int Index)
	{
		return Array[Index];
	}

	T& Front()
	{
		return Array[0];
	}

	const T& Front() const
	{
		return Array[0];
	}

	T& Back()
	{
		return Array[Size - 1];
	}

	const T& Back() const
	{
		return Array[Size - 1];
	}

	bool IsEmpty()
	{
		return Size == 0;
	}

	int GetSize()
	{
		return Size;
	}

	int GetCapacity()
	{
		return Capacity;
	}

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

	void Clear()
	{
		Size = 0;
	}

	void PushBack(const T Item)
	{
		if (Size == Capacity)
		{
			Reserve(Capacity * 2);
		}
		Array[Size] = Item;
		Size++;
	}

	void PopBack()
	{
		Size--;
	}

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
		
		for (i = Size; i > Index; i--)
		{
			Array[i] = Array[i-1];
		}

		Array[Index] = Item;
		Size++;
		return true;
	}

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

	void Resize(const int NewCapacity)
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

	void Append(TDynamicArray<T> OtherArray)
	{
		NewSize = Size + OtherArray.GetSize();
		Reserve(NewSize);

		for (int i = 0; i < OtherArray.GetSize(); i++)
		{
			PushBack(OtherArray[i]);
		}
	}
};