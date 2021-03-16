#include "Vector.h"
#include <exception>
#include <iostream>

Vector::Vector()
{
	arr = nullptr; //=new int[0];
	size = 0;
}


Vector::Vector(size_t n)
{ 
	size = n;
	try {
		arr = new int[n]; 
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		size = 0;
	}
}

Vector::Vector(const Vector& obj) //copy
{
	size = obj.getSize();
	try {
		arr = new int(size);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		size = 0;
		return;
	}
	for (int i = 0; i < size; i++)
	{
		arr[i] = obj.getValue(i);
	}

}

bool Vector::putValue(int position, int el)
{
	if (position >=0 && position<size)
	{
		arr[position] = el;
		return true;
	}
	return false;
}

size_t Vector::getSize() const
{
	return size;
}
int Vector::getValue(int position) const {
	if (position >= 0 && position < size) {
		return arr[position];
	}
	return -1; //?
}

bool Vector::add(const Vector& obj) {
	if (obj.getSize() != size)
	{
		return false;
	}
	for (size_t i = 0; i < getSize();i++) {
		arr[i] += obj.arr[i];
	}
	return true;
}

Vector::~Vector()
{
	delete[] arr;
	size = 0;
}

Vector& Vector::operator+= (Vector const& obj) {
	if (obj.getSize() == size)
	{
		for (size_t i = 0; i < size; i++) {
			arr[i] += obj.arr[i];
		}
	}
	return *this;
}

Vector Vector::operator+ (Vector const& obj) {
	if (obj.getSize() == size) {
		Vector result(*this);
		result += obj;
		return result;
	}
	return (*this);
}

const int& Vector::operator[](size_t index) const {
	if (index >= 0 && index < size) {
		return arr[index];
	}
	return -1;//?
}

int& Vector::operator[](size_t index) {
	if (index >= 0 && index < size) {
		return arr[index];
	}
	//return  //?
}

bool Vector::operator==(Vector const& obj)
{
	if (getSize() != obj.getSize()) {
		return false;
	}
	for (size_t i = 0; i <getSize(); i++) {
		if (arr[i] != obj[i]) {
			return false;
		}
	}

	return true;
}