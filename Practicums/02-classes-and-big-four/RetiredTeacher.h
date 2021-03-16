#pragma once
#include "StudentList.h"

class RetiredTeacher{
    private:
        char teacherName[101];
        unsigned int yearsOfTeaching;
        unsigned int numberOfCourses;
        unsigned int courseCapacity;
        Course* allCourses;

        void copyCourse(Course* &coursesDestination,Course newCourse, unsigned place);

    public:
        RetiredTeacher();
        RetiredTeacher(char* name,unsigned int years ,unsigned int capacity=4);
        ~RetiredTeacher();

        bool addCourse(Course newCourse) ;
        bool hasTaught(char* courseName) const ;
        bool hasTaught(Course course) const ;
        void printInfo() const;
        //additional setters
        void setName(char* newName);
        void setYears(unsigned const newYears);

};
