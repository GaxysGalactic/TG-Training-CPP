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

	void Reserve(int NewCapacity)
	{
		if (NewCapacity <= Capacity)
		{
			return;
		}

		T* NewArray = new T[NewCapacity];
		for (int i = 0; i < Size; i++)
		{
			NewArray[i] = Array[i];
		}

		delete[] Array;
		Array = NewArray;
	}

	void ShrinkToFit()
	{
		if (Capacity == Size)
		{
			return;
		}

		T* NewArray = new T[Size];
		for (int i = 0; i < Size; i++)
		{
			NewArray[i] = Array[i];
		}

		delete[] Array;
		Array = NewArray;
	}
};