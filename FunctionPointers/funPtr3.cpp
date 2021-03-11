#include <iostream>

using std::cin;
using std::cout;
using std::endl;

bool firstIsBigger(const int num1, const int num2)
{
    return (num1 > num2);
}

void sort(int *&numArray, const int size, bool (*isBigger)(const int firstNum, const int secNum))
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (isBigger(numArray[i], numArray[j]))
            {
                std::swap(numArray[i], numArray[j]);
            }
        }
    }
    return;
}

void printSorted(int *&numArr, const int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << numArr[i] << " ";
    }
    cout << endl;
    return;
}

int main()
{
    int size;
    cin >> size;
    int *array = new (std::nothrow) int[size];
    if (!array)
    {
        std::cerr << "Problem allocating enough memory!";
        return 1;
    }
    for (int i = 0; i < size; i++)
    {
        cin >> array[i];
    }
    sort(array, size, firstIsBigger);
    printSorted(array, size);

    delete[] array;

    return 0;
}