#pragma once
#include "StudentList.h"

class Student
{
private:
    unsigned int facultyNumber;
    char name[51];
    char major[33];
    int group;

    bool isValidMajor(const char *major) const;
    bool isValidFN(const int facultyNumber) const;
    bool isValidname(const char* name) const;
    bool isValidGroup(const int group) const;

    friend class StudentList;

public:
    Student();
    Student(int facultyNumber, const char *name, const char *major, int group);
    Student(const Student &newStudent);
    Student& operator=(const Student &newStudent);
    int getFacultyNumber() const;
    const char *getName() const;
    const char *getMajor() const;
    int getGroup() const;
    void setMajor(const char *newMajor);
    void setGroup(int newGroup);
    void printInformation() const;
    void readFromConsole();
};
