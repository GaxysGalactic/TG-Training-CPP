#pragma once

template<typename T>
class TDynamicArray
{
private:
	int Capacity;
	int Size;
	T* Array;

public:

	TDynamicArray(int InCapacity)
	{
		Capacity = InCapacity;
		Size = 0;

		Array = new T[InCapacity];
	}

	~TDynamicArray()
	{
		delete[] Array;
	}
};