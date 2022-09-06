#pragma once

template<typename T, int N>
class TStaticArray
{
private:
	int Size = N;
	T Array[N];

public:

	T& operator[](const int Index)
	{
		return Array[Index];
	};

	const T& operator[](const int Index) const 
	{
		return Array[Index];
	};

	T& Front()
	{
		return Array[0];
	};

	const T& Front() const
	{
		return Array[0];
	}

	T& Back()
	{
		return Array[Size - 1];
	};

	const T& Back() const
	{
		return Array[Size - 1];
	};

	T* GetData()
	{
		return Array;
	};

	const T* GetData() const
	{
		return Array;
	};

	bool IsEmpty() const
	{
		return Size == 0;
	};

	int GetSize() const
	{
		return Size;
	};

	void Fill(T Filler)
	{
		for (int i = 0; i < Size; i++)
		{
			Array[i] = Filler;
		}
	};

	void Swap(TStaticArray OtherArray)
	{
		TStaticArray<T, Size> TemporaryArray;
		for (int i = 0; i < Size; i++)
		{
			TemporaryArray[i] = OtherArray[i];
			OtherArray[i] = Array[i];
			Array[i] = TemporaryArray[i];
		}
	};
};