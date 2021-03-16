#include <iostream>
#include "FunPtr1And2.h"

using std::cin;
using std::cout;
using std::endl;

bool problemTest(int *&numArr, const int size, bool (*problemToTest)(int *, const int, bool (*)(int)), bool (*problemHelpFunc)(int))
{
    return (problemToTest(numArr, size, problemHelpFunc));
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

    cout << "Testing funPtr1: \n";
    if (problemTest(array, size, any_of, isEvenNumber))
    {
        cout << "There is an even number among these !\n";
    }
    else
    {
        cout << "All are odd numbers!\n";
    }

    cout << "\nTesting funPtr2: \n";

    if (problemTest(array, size, all_of, isEvenNumber))
    {
        cout << "All are even numbers !";
    }
    else
    {
        cout << "There is an odd number!";
    }

    delete[] array;

    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> a8244f8c4d6a91ab22b583eb72c2d0471045acf7
