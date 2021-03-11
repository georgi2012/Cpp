#pragma once
#include <iostream>
#include <cstring>
#include "Student.h"
#include "StudentList.h"

using std::cin;
using std::cout;
using std::endl;
using std::nothrow;

StudentList::StudentList(int capacity)

{
    if (capacity < 0)
    {
        cout << "Capacity can't be a negative number . The current capacity will be set to 0 .\n";
        capacity = 0;
    }
    else if (capacity > 200)
    {
        cout << "The maximum is 200 students and so the capacity will be set to 200 .\n ";
        capacity = 200;
    }
    students = new (nothrow) Student[capacity];
    if (!students)
    {
        std::cerr << "There was a problem allocating enough memory .\n";
        cout << "Capacity set to 0.\n";
        capacity = 0;
    }
    this->capacity = capacity;
    size = 0;
}

void StudentList::copyStudents(Student *&newStudents, Student *&students)
{
    for (int i = 0; i < size; i++)
    {
        newStudents[i].facultyNumber = students[i].facultyNumber;
        strcpy(newStudents[i].name, students[i].name);
        strcpy(newStudents[i].major, students[i].major);
        newStudents[i].group = students[i].group;
    }
    return;
}

void StudentList::add(const Student &student)
{
    if (capacity == 200)
    {
        cout << "No space for new students .\n";
        return;
    }
    if (searchInTheList(student.getFacultyNumber()) < 0) //not in the list
    {
        if (capacity <= size) //no more space
        {
            Student *newStudents = new (nothrow) Student[++capacity];
            if (!newStudents)
            {
                std::cerr << "There was a problem allocating enough memory .\n";
                cout << "No new student was added.\n";
                return;
            }
            copyStudents(newStudents, students);
            size++;
            delete[] students;
            students = newStudents;
            return;
        }
    }
    else
    {
        cout << "There is already such student in the list . It won't be added again.\n";
        return;
    }
}

void StudentList::remove(int facultyNumber)
{
    if (searchInTheList(facultyNumber) >= 0)
    {
        for (int i = searchInTheList(facultyNumber) + 1; i < size; i++)
        {
            students[i - 1].facultyNumber = students[i].facultyNumber;
            students[i - 1].group = students[i].group;
            strcpy(students[i - 1].name, students[i].name);
            strcpy(students[i - 1].major, students[i].major);
        }
        size--;
        return;
    }
    else
    {
        cout << "No such student found in the list.\n";
        return;
    }
}

int StudentList::searchInTheList(int FN) const
{
    for (int i = 0; i < size; i++)
    {
        if (students[i].getFacultyNumber() == FN)
        {
            return i;
        }
    }
    return -1; // not found
}

void StudentList::remove(const Student &student) // ???
{
    remove(student.facultyNumber);
    return;
}

bool StudentList::contains(int facultyNumber) const
{
    return (searchInTheList(facultyNumber) >= 0);
}

bool StudentList::contains(const Student &student) const //???
{
    return (searchInTheList(student.facultyNumber) >= 0);
}

void StudentList::print() const
{
    for (int i = 0; i < size; i++)
    {
        students[i].printInformation();
    }
    return;
}

StudentList::~StudentList()
{
    delete[] students;
    size = 0;
    capacity = 0;
}

int main()
{

    return 0;
}
