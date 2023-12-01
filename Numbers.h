#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Number
{
public:
	uint64_t value;
	uint64_t unique_factors = 2; // excluding 1 and itself
	long double compositeness;
	string primeness;
public:
	Number();
	Number(uint64_t _value): value(_value), compositeness(2/value) {}
};

class Numbers
{
public:
	vector<Number> numVector;
	int size;
public:
	Numbers(int _size) : size(_size) {}

	void FillVector(int digits);
	void FillVector(bool randBool, int digits); 

	void ArePrime();

	void PrintNumbers();
	void PrintNumbers(int everyX);
};
