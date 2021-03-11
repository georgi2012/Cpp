#include <iostream>
#include <cstring>
#include "head.h"

using std::cin;
using std::cout;
using std::endl;

bool Student::isValidFN(const int facultyNumber) const
{
    return (facultyNumber >= 10000 && facultyNumber <= 99999);
}
bool Student::isValidname(const char *name) const
{
    return (strlen(name) <= 50);
}
bool Student::isValidGroup(const int group) const
{
    return (group >= 1 && group <= 8);
}

bool Student::isValidMajor(const char *major) const
{
    return (strcmp(major, "Informatics") == 0 ||
            strcmp(major, "Computer Science") == 0 ||
            strcmp(major, "Mathematics and Informatics") == 0 ||
            strcmp(major, "Mathematics") == 0 ||
            strcmp(major, "Software Engineering") == 0);
}
Student::Student()
{
    facultyNumber = 0;
    strcpy(name, "Name Not Added");
    strcpy(name, "Major Not Chosen");
    group = 0;
}
Student::Student(int facultyNumber, const char *name, const char *major, int group)
{
    if (isValidFN(facultyNumber))
    {
        this->facultyNumber = facultyNumber;
    }
    else
    {
        this->facultyNumber = 0;
    }
    if (isValidname(name))
    {
        strcpy(this->name, name);
    }
    else
    {
        strcpy(this->name, "Name Not Added");
    }
    if (isValidMajor(major))
    {
        strcpy(this->major, major);
    }
    else
    {
        strcpy(this->name, "Major Not Chosen");
    }
    if (isValidGroup(group))
    {
        this->group = group;
    }
    else{
         group = 0;
    }
}
Student::Student(const Student &newStudent)
{
    setMajor(newStudent.getMajor());
    strcpy(this->name, newStudent.getName());
    facultyNumber = newStudent.facultyNumber;
    group = newStudent.group;
}

Student &Student::operator=(const Student &newStudent) 
{
    if (this != &newStudent)
    {
        setMajor(newStudent.getMajor());
        strcpy(this->name, newStudent.getName());
        facultyNumber = newStudent.facultyNumber;
        group = newStudent.group;
    }
    return *this;
}

int Student::getFacultyNumber() const
{
    return facultyNumber;
}
const char *Student::getName() const
{
    return name;
}
const char *Student::getMajor() const
{
    return major;
}
int Student::getGroup() const
{
    return group;
}
void Student::setMajor(const char *newMajor)
{
    if (isValidMajor(newMajor))
    {
        strcpy(this->major, newMajor);
    }
    return;
}
void Student::setGroup(int newGroup)
{
    if (isValidGroup(newGroup))
    {
        this->group = newGroup;
    }
    return;
}
void Student::printInformation() const
{
    cout << "Name: " << name << endl;
    cout << "FN: " << facultyNumber << endl;
    cout << "Of group: " << group << endl;
    cout << "From :" << major << endl;
    return;
}
void Student::readFromConsole()
{
    int FN;
    char nameNew[51];
    char majorNew[33];
    int groupNew;
    cout << "Input\nFN:";
    cin >> FN;
    cout << "\nName:";
    cin >> nameNew;
    cout << "\nMajor:";
    cin >> majorNew;
    cout << "\nGroup:";
    cin >> group;

    if (isValidname(nameNew))
    {
        strcpy(name, nameNew);
    }
    if (isValidFN(FN))
    {
        facultyNumber = FN;
    }
    if (isValidGroup(groupNew))
    {
        group = groupNew;
    }
    if (isValidMajor(majorNew))
    {
        strcpy(major, majorNew);
    }
    return;
}

int main()
{

    return 0;
}
