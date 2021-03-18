#include <iostream>
#include "Vector.h"
using std::cin;
using std::cout;
using std::endl;

int main()
{
    //Vector a(9000000000);

    Vector a(3);
    a.putValue(0, 2);
    a.putValue(1, 4);
    a.putValue(2, 0);
    a.add(a);
    a += a;
    try
    {
        cout << a.getValue(1) << "=" << a[1] << endl;
    }
    catch (int &number)
    {
        if (number < 0)
        {
            cout << "There is no such element in the Vector";
        }
    }
    try
    {
        a[4] = 4;
        cout << a[2] << endl;
    }
    catch (int &number)
    {
        if (number < 0)
        {
            cout << "There is no such element in the Vector\n";
        }
    }
    cout << (a == a) << endl;
    cout<<((5*a)==(a*5))<<endl;

   /* Vector b(a);
    b = a + a - a; //=a
    cout<<(b==a);
    std::cout << "\n";
    b = a - 2*a + a*2 + a*2; //=3*a 
    
    std::cout << (b==3*a)<<"\n";

    b = a + a*3 +  a - a ; //=-2a  
    cout<<"wtf";
    cout<<(b==a);
    std::cout << "\n";*/

    return 0;
}