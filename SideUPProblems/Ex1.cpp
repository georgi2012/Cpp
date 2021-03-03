#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int perfectSize(unsigned long number)
{
    int br = 0;
    while (number > 0)
    {
        number /= 16;
        br++;
    }
    return br;
}

void convertToHex(unsigned long &number, char *&hexa,const int &size)
{
    short index = 0;
    short remaining = 0;

    while (number > 0)
    {
        remaining = number % 16;
        number /= 16;
        if (remaining <= 9)
        {
            hexa[size-index-1] = remaining + '0';
        }
        else
        {
            hexa[size-index-1] = remaining - 10 + 'A';
        }
        index++;
    }

    return;
}

int main()
{
    
    unsigned long number;
    cin >> number;
    const int size=perfectSize(number);
    char *hexa = new (std::nothrow) char[size];
    convertToHex(number, hexa,size);
    cout << hexa;

    delete[] hexa;

    return 0;
}