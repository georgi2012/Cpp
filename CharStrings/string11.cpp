#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::nothrow;

int sizeOfString(char *string)
{
    int i = 0;
    while (string[i] != '\0')
    {
        i++;
    }
    return i;
}

bool anagramaCheck(char *string1, char *string2)
{
    int size1 = sizeOfString(string1);
    if (size1 != sizeOfString(string2))
    {
        return false;
    }
    //else
    bool *isChecked = new (nothrow) bool[size1];
    bool isPossible = false;
    for (int i = 0; i < size1; i++)
    {
        isChecked[i] = false;
    }
    for (int i = 0; i < size1; i++)
    {
        isPossible = false;
        for (int j = 0; j < size1; j++)
        {
            if (!isChecked[j] && string2[j] == string1[i])
            {
                isChecked[j] = true;
                isPossible = true;
                break;
            }
        }
        if (!isPossible)
        {
            delete[] isChecked;
            return false;
        }
    }
    delete[] isChecked;
    return true;
}

int main()
{
    int n;
    cin >> n;
    char **strings = new (nothrow) char *[n];
    if (!strings)
    {
        std::cerr << "Problem allocating memory.";
        return 1;
    }
    bool *isUsed = new (nothrow) bool[n];
    if (!isUsed)
    {
        std::cerr << "Problem allocating memory.";
        delete[] strings;
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        strings[i] = new (nothrow) char[100];
        if (!strings[i])
        {
            std::cerr << "Problem allocating memory.";
            for (int j = 0; j <= i; j++)
            {
                delete[] strings[j];
            }
            return 1;
        }
        isUsed[i] = false;
        cin >> strings[i];
    }
    bool isPrinted = false;

    for (int i = 0; i < n - 1; i++)
    {
        isPrinted = false;
        if (isUsed[i])
        {
            continue;
        }
        for (int j = i + 1; j < n; j++)
        {
            if (!isUsed[j] && anagramaCheck(strings[i], strings[j]))
            {
                isUsed[i] = true;
                isUsed[j] = true;
                if (!isPrinted)
                {
                    cout << i + 1 << " " << j + 1 << " ";
                    isPrinted = true;
                }
                else
                {
                    cout << j + 1 << " ";
                }
            }
        }
        if (isPrinted)
        {
            cout << endl;
        }
    }
    delete[] isUsed;
    for (int i = 0; i < n; i++)
    {
        delete[] strings[i];
    }
    delete[] strings;
    return 0;
}
