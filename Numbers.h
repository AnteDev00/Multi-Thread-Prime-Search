#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Number
{
public:
	uint64_t value;
	uint64_t unique_factors; 
	long double compositeness;
	string primeness;
public:
	Number(int _value) 
	{
		value = _value;
		primeness = "not-prime";
		compositeness = 1;
		if (value == 1) 
			unique_factors = 1;
		else 
			unique_factors = 2;
	}
};

class Numbers
{
public:
	vector<Number> numVector;
	int size;
public:
	Numbers(int _size) : size(_size) 
	{
		numVector.reserve(_size);
		for (int i = 1; i < size + 1; i++)
		{
			numVector.emplace_back(i % (size + 1));
		}
	}
	void ArePrime();
	void PrintNumbers(int msDelay);
};
