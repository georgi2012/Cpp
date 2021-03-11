#include <iostream>

using std::cin;
using std::cout;
using std::endl;

struct StudentResult{
     double K1,K2;
     double D1,D2,D3;
     double PI,UI;
};

void calcAndPrint(StudentResult &student)
{
   double first=(student.PI+student.UI)/2;
   double second=(student.K1+student.K2 +(student.D1+student.D2+student.D3)/3)/3;
   cout<<"Final result : "<<(first+second)/2;
   return;

}

int main()
{
    StudentResult student;
    cin>>student.K1>>student.K2>>student.D1>>student.D2>>student.D3>>student.PI>>student.UI;
    calcAndPrint(student);

    return 0;
}
