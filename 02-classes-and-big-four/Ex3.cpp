#pragma once
#include <iostream>
#include <cstring>
#include "Course.h"
#include "StudentFunc.h"

using std::cin;
using std::cout;
using std::endl;
using std::nothrow;

Course::Course(char *courseName, const unsigned int courseCapacity)
{
    if (strlen(courseName) > 100)
    {
        cout << "The course name is too long . It will be set to Computer Science by default.\n";
        strcpy(name, "Computer Science");
    }
    else
    {
        strcpy(name, courseName);
    }

    size = 0;
    capacity = courseCapacity;
    students = new (nothrow) Student[capacity];
    if (!students)
    {
        std::cerr << "There was a problem allocating enough memory for all students. Capacity set to 0.\n";
        capacity = 0;
    }
}

bool Course::enrolStudent(const Student newStudent)
{
    if (size >= capacity)
    {
        cout << "The course it already full.\n";
        return false;
    }
    students[size].group = newStudent.group;
    strcpy(students[size].name, newStudent.name);
    strcpy(students[size].major, newStudent.major);
    students[size].facultyNumber = newStudent.facultyNumber;
    size++;
    return true;
}

bool Course::enrolStudents(const Student *newStudents, const unsigned int numOfStudents)
{
    unsigned br = 0;
    while (br < numOfStudents && enrolStudent(newStudents[br]))
    {
        br++;
    }
    return (br == numOfStudents); //if all students were added succesfully
}

void Course::printInformation() const
{
    cout << "Course name : " << name << endl;
    cout << "Course capacity: " << capacity << endl;
    cout << "List of all students in the course:\n";
    for (int i = 0; i < size; i++)
    {
        students[i].printInformation();
    }
    return;
}

const char *Course::getCourseName() const
{
    return name;
}

const int Course::getCourseCapacity() const
{
    return capacity;
}

bool Course::setCourseName(char *name)
{
    if (strlen(name) > 100)
    {
        cout << "The new name is too long to be used.\n";
        return false;
    }
    strcpy(this->name, name);
    return true;
}

bool Course::setCourseCapacity(unsigned int newCapacity)
{
    if(newCapacity<size)
    {
        cout<<"There are already more students in the course than it's size.\n";
        cout<<"You can NOT kick students from the course. No changes were made.\n";
        return false;
    }
    else if (newCapacity==capacity){
        return true;
    }
    else // new > old || (new<old && size < new)
    {
        Student* newStudents=new (nothrow) Student[newCapacity];
        if(!newStudents)
        {
            std::cerr<<"There was a problem allocating enough memmory. ";
            cout<<"Capacity was not changed . Current capacity : "<<capacity;
            return false;
        }

        capacity=newCapacity;
        for (int i=0;i<size;i++)
        {
            newStudents[i].group = students[i].group;
            strcpy(newStudents[i].name, students[i].name);
            strcpy(newStudents[i].major, students[i].major);
            newStudents[i].facultyNumber = students[i].facultyNumber;
        }
        delete[] students;
        students=newStudents;
        return true;
    }
}

Course::~Course(){
    delete[] students;
    name[0]='\0';
    capacity=0;
    size=0;
}


int main()
{
    return 0;
}
