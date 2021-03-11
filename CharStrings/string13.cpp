#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::nothrow;

int sizeOfString(const char *word)
{
    int i = 0;
    while (word[i] != '\0')
    {
        i++;
    }
    //cout<<"Size of string is :"<<i;
    return i;
}

int findEqualSymbow(const char symbow, const char *word)
{
    int i = 0;
    while (word[i] != '\0')
    {
        if (word[i] == symbow)
        {
            return i;
        }
        i++;
    }
    return -1;
}

void printAns(const char *firstWord, const char *secondWord, const unsigned int index1, const unsigned int index2)
{
    // cout<<"printing for "<<firstWord<<" and "<<secondWord<<endl;
    for (int i = 0; i < index2; i++) //second - vertical
    {
        for (int j = 0; j < index1; j++)
        {
            cout << " ";
        }
        cout << secondWord[i] << endl;
    }

    for (int i = 0; i < sizeOfString(firstWord); i++)
    {
        cout << firstWord[i];
    }
    cout << endl;

    for (int i = index2 + 1; i < sizeOfString(secondWord); i++) //second - vertical
    {
        for (int j = 0; j < index1; j++)
        {
            cout << " ";
        }
        cout << secondWord[i] << endl;
    }
    cout << endl;
    return;
}

int main()
{
    char firstWord[100] = {};
    char secondWord[100] = {};
    cin >> firstWord >> secondWord;
    cout << endl;

    int i = 0;
    int firstEqual = -1;
    while (firstWord[i] != '\0')
    {
        firstEqual = findEqualSymbow(firstWord[i], secondWord);
        if (firstEqual >= 0)
        {
            //cout<<"first index="<<i<<" and second = "<<firstEqual<<endl;
            printAns(firstWord, secondWord, i, firstEqual);
            break;
        }
        i++;
    }
    if (firstEqual < 0)
        {
           printAns(firstWord, secondWord, sizeOfString(firstWord)+1, sizeOfString(secondWord));
        }
    
    /*
Вход:
klaviatura
monitor

Изход:

    m
    o
    n
klaviatura
    t
    o
    r

    */

    return 0;
}
