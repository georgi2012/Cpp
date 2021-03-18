#include "Vector.h"
#include <exception>
#include <iostream>

using std::cout;
Vector::Vector()
{
    arr = nullptr; //=new int[0];
    size = 0;
}

Vector::Vector(size_t n)
{
    size = n;
    try
    {
        arr = new int[n];
    }
    catch (const std::exception &e)
    {
        arr = nullptr;
        std::cout << e.what() << std::endl;
        size = 0;
    }
}

Vector::Vector(const Vector &obj) //copy
{
    size = obj.getSize();
    try
    {
        arr = new int(size);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        size = 0;
        arr = nullptr;
        return;
    }
    for (int i = 0; i < size; i++)
    {
        arr[i] = obj.getValue(i);
    }
}

bool Vector::putValue(int position, int el)
{
    if (position >= 0 && position < size)
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

int Vector::getValue(int position) const
{
    if (position >= 0 && position < size)
    {
        return arr[position];
    }
    throw -1;
}

bool Vector::add(const Vector &obj)
{
    if (obj.getSize() != size)
    {
        return false;
    }
    for (size_t i = 0; i < getSize(); i++)
    {
        arr[i] += obj.arr[i];
    }
    return true;
}

Vector::~Vector()
{
    delete[] arr;
    size = 0;
}

Vector &Vector::operator+=(Vector const &obj)
{
    if (obj.getSize() == size)
    {
        for (size_t i = 0; i < size; i++)
        {
            arr[i] += obj.arr[i];
        }
    }
    return *this;
}

Vector Vector::operator+(Vector const &obj)
{//cout<<"+";
    if (obj.getSize() == size)
    {
        Vector result(*this);
        result += obj;
        return result;
    }
    return (*this);
}

const int &Vector::operator[](size_t index) const
{
    if (index >= 0 && index < size)
    {
        return arr[index];
    }
    throw -2;
}

int &Vector::operator[](size_t index)
{
    if (index >= 0 && index < size)
    {
        return arr[index];
    }
    //return  &nullptr;
    throw -1; //no such thing
}

bool Vector::operator==(Vector const &obj)
{

    if (getSize() != obj.getSize())
    {
        return false;
    }
    for (size_t i = 0; i < getSize(); i++)
    {
        if (arr[i] != obj[i])
        {
            return false;
        }
    }

    return true;
}

Vector Vector::operator*(int mult)
{

    Vector result(*this);
    for (int i = 0; i < result.getSize(); i++)
    {
        result[i] *= mult;
    }
    return result;
}

Vector &Vector::operator*=(int mult)
{
    for (size_t i = 0; i < size; i++)
    {
        arr[i] *= mult;
    }
    return *this;
}

Vector &Vector::operator=(const Vector &obj)
{//cout<<"=";
    if (this != &obj)
    {
        size = obj.getSize();
        try
        {
            arr = new int(size);
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
            size = 0;
            arr = nullptr;
            return *this;
        }
        for (int i = 0; i < size; i++)
        {
            arr[i] = obj.getValue(i);
        }
    }
    return *this;
}

Vector &Vector::operator-=(Vector const &obj)
{
if (obj.getSize() == size)
    {
        for (size_t i = 0; i < size; i++)
        {
            arr[i] -= obj.arr[i];
        }
    }
    //else{ throwing error is a possibility}
    return *this;
}
Vector Vector::operator-(Vector const &obj)
{//cout<<"-";
     if (obj.getSize() == size)
    {
        Vector result(*this);
        result -= obj;
        return result;
    }
    //else { we can throw an error here or say that nothing was changed}
    return (*this);
}

Vector operator*(int num, const Vector &obj) // vector a = 5*b; b is also a vector
{

    Vector result(obj);
    for (int i = 0; i < result.getSize(); i++)
    {
        result[i] *= num;
    }
    return result;
}
