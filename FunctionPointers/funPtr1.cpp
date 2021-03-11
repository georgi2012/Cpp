#include <iostream>

using std::cin;
using std::cout;
using std::endl;

bool isEvenNumber(int num)
{
  return !(num % 2);
}

bool any_of(int *numArray, const int size, bool (*isEven)(int number))
{
  for (int i = 0; i < size; i++)
  {
    if (isEven(numArray[i]))
    {
      return true;
    }
  }
  return false;
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
  if (any_of(array, size, isEvenNumber))
  {
    cout << "There is an even number among these !";
  }
  else
  {
    cout << "All are odd numbers!";
  }

  delete[] array;

  return 0;
}
