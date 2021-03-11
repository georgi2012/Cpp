#include <iostream>

using std::cin;
using std::cout;
using std::endl;

bool isEvenNumber(int num)
{
    return !(num % 2);
}

bool all_of(int *numArray, const int size, bool (*isEven)(int number))
{
    for (int i = 0; i < size; i++)
    {
        if (!isEven(numArray[i]))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int size;
    cin >> size;
    int *array = new (std::nothrow) int[size];
    for (int i = 0; i < size; i++)
    {
        cin >> array[i];
    }
    if (all_of(array, size, isEvenNumber))
    {
        cout << "All are even numbers !";
    }
    else
    {
        cout << "There is an odd number!";
    }

    delete[] array;

    return 0;
}