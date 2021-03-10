#pragma once
#include "Student.h"

struct StudentList
{
private:
    Student *students; // up to 200
    unsigned short capacity; //up to 200
    unsigned short size;
    int searchInTheList(int FN) const;
    void copyStudents(Student *&newStudents,Student* &students) ;
public:
    StudentList(int capacity);
    void add(const Student &student);
    void remove(int facultyNumber);
    void remove(const Student &student);
    bool contains(int facultyNumber) const;
    bool contains(const Student &student) const;
    void print() const; 
    ~StudentList();
    
};