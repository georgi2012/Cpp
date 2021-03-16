#include <iostream>
//#include "head.h"
#include <exception>

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
    /*Arrays<double , 10> arr;

    int a[]={1,2,5};
    for(int n:a)
    {
      cout<<n<<" ";
    }*/
    long long * a;
    try{
      cout<<"Trying...";
      a=new long long [9000000000];
      cout<<"...tried";
      if(!a)
      {
        throw 1;
      }
    }
    catch(int num)
    {
      if(num==1)
      {
        cout<<" num "<<1<<std::endl;
      }
    }
    catch(std::exception &e)
    {
      cout<<"caught";
      //delete [] a;
      cout<<e.what();
      cout<<" is the error";
    }
    cout<<"\nalright!";
    delete[] a;
    
    return 0;
}