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
		Head = new FNode()->Element = FirstElement;
		Tail = Head;
		Size = 1;
	}


};