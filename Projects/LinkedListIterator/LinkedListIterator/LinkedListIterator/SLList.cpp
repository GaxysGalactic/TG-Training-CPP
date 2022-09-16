#include "SLList.h"
#include <iostream>

int main()
{
	TSLList<int> List;

	List.AddHead(1);
	List.AddTail(2);
	List.AddTail(3);
	List.AddHead(0);

	List.Remove(2);
	List.Insert(2, 2);

	List.ForEach([](const int SomeInt) {std::cout << SomeInt << std::endl; });

	TSLList<int> List2(List);

	List.Clear();

	std::cout << List.GetSize();

	//List2.ForEach([](const int SomeInt) {std::cout << SomeInt << std::endl; });

	for (int SomeInt : List2)
	{
		std::cout << SomeInt << std::endl;
	}
}