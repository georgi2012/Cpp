#pragma once
#include<iostream>
using std::size_t;

class Vector
{
private:
	size_t size;
	int* arr;
public:
	Vector();
	Vector(size_t n);
	Vector(const Vector& obj);
	~Vector();
	Vector& operator=(const Vector& obj);
	bool putValue(int position, int el);
	int getValue(int position) const;
	size_t getSize() const;
	bool add(const Vector& obj);
	Vector  operator+ (Vector const& obj);
	Vector& operator+= (Vector const& obj);
	Vector  operator* (int mult); 
	Vector& operator*= (int mult); 
	const int& operator[](size_t idx) const;
	int& operator[](size_t index);
	bool operator==(Vector const& obj);
    Vector& operator-= (Vector const& obj); 
    Vector operator- (Vector const& obj); 
    //Vector& operator\= and Vector& operator\ are not suitable for int vector
};


Vector operator*( int num, const Vector& obj);
