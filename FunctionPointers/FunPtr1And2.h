#pragma once

//funptr 1
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
//end

//funptr2

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
//end
