#pragma once

#include <iostream>
#include <string>

class FStudent
{

private:
	char* Name;
	int Age;

public:

	FStudent();

	FStudent(int InAge);

	~FStudent();

	void SetName(const char* NewName);

	void SetAge(const int NewAge);

	void Print();
};