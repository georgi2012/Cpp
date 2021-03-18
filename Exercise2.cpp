#include <iostream>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;


struct Point 
{
    
    int x;
    int y;

    void addCoords()
    {
        cin>>x>>y;
        return;
    }
    void printCoords()
    {
        cout<<"point corrdinates: ("<<x<<" "<<y<<")\n";
        return;
    }

    double distanceToCenter()
    {
      return sqrt(x*x+y*y);
    }
};

double distanceBetweenPoints(const Point first, const Point second)
{
   return sqrt(pow(first.x+second.x,2)+pow(first.y+second.y,2));
}


int main()
{
   Point first,second;
   first.addCoords();
   second.addCoords();
   first.printCoords();
   second.printCoords();
   cout<<"For first to (0,0) :"<<first.distanceToCenter()<<endl;
   cout<<"For second to (0,0) :"<<second.distanceToCenter()<<endl;
   cout<<"Dist between 1 and 2 :"<<distanceBetweenPoints(first,second)<<endl;


    return 0;
}