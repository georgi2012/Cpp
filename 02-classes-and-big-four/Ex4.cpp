#pragma once
#include <iostream>
#include <cstring>
#include "ListFunc.h"
#include "RetiredTeacher.h"

//#include "Course.h"
//#include "StudentFunc.h"
//using std::cin;
//using std::cout;
//using std::endl;
//using std::nothrow;
//these are already included

RetiredTeacher::RetiredTeacher(char *name, unsigned int years, unsigned int capacity = 2)
{
    if (strlen(name) > 100)
    {
        cout << "The name is too long . It will be set to Name#Unset by default.\n";
        strcpy(teacherName, "Name#Unset");
    }
    else
    {
        strcpy(teacherName, name);
    }
    if (years > 100)
    {
        cout << "That years value is unrealistic . Nobody will want to work for that long.\n";
        cout << "Years value set to 0.\n";
        yearsOfTeaching = 0;
    }
    else
    {
        yearsOfTeaching = years;
    }

    allCourses = new (std::nothrow) Course[capacity];
    if (!allCourses)
    {
        std::cerr << "Could not allocate enough memory for all courses. Capacity set to 0.\n ";
        courseCapacity = 0;
    }
    else
    {
        courseCapacity = capacity;
    }
    numberOfCourses = 0;
}

RetiredTeacher::RetiredTeacher()
{
    teacherName[0] = '\0';
    numberOfCourses = 0;
    courseCapacity = 0;
}

RetiredTeacher::~RetiredTeacher()
{
    delete[] allCourses;
    courseCapacity = 0;
    numberOfCourses = 0;
    teacherName[0] = '\0';
}

void RetiredTeacher::copyCourse(Course *&coursesDestination, Course newCourse, unsigned place)
{

    coursesDestination[place].setCourseName(newCourse.name);                     //set name
    coursesDestination[place].setCourseCapacity(newCourse.capacity);             //set capacity
    coursesDestination[place].enrolStudents(newCourse.students, newCourse.size); //copy student information
    //size will be set automatically
    return;
}

bool RetiredTeacher::addCourse(Course newCourse)
{
    if (numberOfCourses >= courseCapacity)
    {
        Course *newCourses = new (std::nothrow) Course[++courseCapacity];
        if (!newCourses)
        {
            std::cerr << "Allocating enough memory failed . New course could not be added.\n";
            return false;
        }
        for (int i = 0; i < numberOfCourses; i++)
        {
            copyCourse(newCourses, allCourses[i], i); //copy all existing courses to the new array
        }
        copyCourse(newCourses, newCourse, numberOfCourses++); //and add the new one
    }
    else //luckily , we have more space -> size<capacity
    {
        copyCourse(allCourses, newCourse, numberOfCourses++);
    }
    return true;
}

bool RetiredTeacher::hasTaught(char *courseName) const
{
    for (int i = 0; i < numberOfCourses; i++)
    {
        if (strcmp(allCourses[i].name, courseName) == 0)
        {
            return true;
        }
    }
    return false;
}

bool RetiredTeacher::hasTaught(Course course) const
{
    // If we suggest that he had no courses with the same name , than ...
    // return hasTaught(course.name);
    //... will do the job . But that makes no sense , does it ?
    //Let's suggest that he had the same course in different years for different students(mostly different...)
    //We will look for absolutely the same course by comparing everything!
    int br = 0;
    bool isEqual = true;
    for (br = 0; br < numberOfCourses; br++)
    {
        isEqual = true;
        if (strcmp(allCourses[br].name, course.name) == 0)
        {
            // we found a course with such name. Lets examine it!
            if (allCourses[br].size == course.size && allCourses[br].capacity == course.capacity)
            {
                for (int i = 0; i < allCourses[br].size; i++) // for each student in the course
                {
                    if (!(allCourses[br].students[i].getFacultyNumber() == course.students[i].getFacultyNumber() 
                    && allCourses[br].students[i].getName() == course.students[i].getName()
                    && allCourses[br].students[i].getGroup() == course.students[i].getGroup()))
                    //Ok , that's enough to make me believe that's (not) the same guy...
                    {
                        isEqual = false;
                        break;
                    }
                }
                if (isEqual) //everything is the same
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void RetiredTeacher::printInfo() const
{
    cout << "Teacher's name: " << teacherName << endl;
    cout << "Years of teaching :" << yearsOfTeaching << endl;
    cout << "\nAll courses :\n";
    for (int i = 0; i < numberOfCourses; i++)
    {
        //allCourses[i].printInformation(); //that will be waaay too long to read
        cout << i + 1 << ". " << allCourses[i].name << endl;
    }
    return;
}

void RetiredTeacher::setName(char *newName)
{
    if (strlen(newName) > 100)
    {
        cout << "The name is too long . Name not changed.\n";
        //strcpy(teacherName, "Name#Unset");
    }
    else
    {
        strcpy(teacherName, newName);
    }
    return;
}

void RetiredTeacher::setYears(unsigned const newYears)
{
    if (newYears > 100)
    {
        cout << "That years value is unrealistic . Nobody will want to work for that long.\n";
        cout << "Years value was not changed.\n";
    }
    else
    {
        yearsOfTeaching = newYears;
    }
    return;
}

/*int main()
{
    return 0;
}*/