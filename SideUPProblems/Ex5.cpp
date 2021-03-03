#include <iostream>

using std::cin;
using std::cout;
using std::endl;

bool recursionCheck(unsigned long num, const int numToSearch)
{
    //cout<<num<<" ";
    if (num == 0)
    {
        return true;
    }
    if (num % 10 == numToSearch)
    {
        return false;
    }
    return recursionCheck(num / 10, numToSearch);
}

int main()
{
    unsigned long num;
    cin >> num;
    int index = 0;
    while (num > 0)
    {
        //cout<<endl;
        if(recursionCheck(num/10, num % 10)==false)
        {
            cout<<"There are repeating numbers.\n";
            return 0;
        }
        num /= 10;
    }
    cout<<"There are NO repeating numbers.\n";
    return 0;
}