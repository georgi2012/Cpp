#include <iostream>
//#include "head.h"

using std::cout;
using std::cin;
using std::endl;


template <typename T, int N>
class Arrays{

  private:
   size_t size;
   T arr[N];

};

int main()
{
    Arrays<double , 10> arr;

    int a[]={1,2,5};
    for(int n:a)
    {
      cout<<n<<" ";
    }
    
    return 0;
}