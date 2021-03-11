#include <iostream>

using std::cin;
using std::cout;
using std::endl;

struct Student
{
  char name[100] = {};
  unsigned int FN;
};

void findStudent(Student *pupils, int FN, unsigned const int n)
{
  for (auto i = 0; i < n; i++)
  {
    if (pupils[i].FN == FN)
    {
      cout << pupils[i].name << endl;
      return;
    }
  }
  cout<<"No such animal!"<<endl;
  return;
}

main()
{
  int n, FN;
  cin >> n;
  Student *studentArray = new Student[n];
  for (int i = 0; i < n; i++)
  {
    cin >> studentArray[i].name >> studentArray[i].FN;
  }
  cin>>FN;
   findStudent(studentArray,FN,n );
  delete[] studentArray;
  return 0;
}
