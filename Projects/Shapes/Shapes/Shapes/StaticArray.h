#pragma once

template<typename T, int N>
class TStaticArray
{
private:
	int Size = N;
	T Array[N];

public:

	T operator[](const int Index);

	T operator[](const int Index) const;

	T front();

	T front() const;

	T back();

	T back() const;

	T* GetData();

	T* GetData() const;
};