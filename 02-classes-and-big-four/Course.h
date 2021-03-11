#include "Student.h"

class Course{
private:
    char name[101]; //course name
    unsigned int capacity; //max students number
    Student *students;
    unsigned int size;

public:
    Course(char* courseName, const unsigned int courseCapacity);
    ~Course();
    bool enrolStudent(const Student newStudent);
    bool enrolStudents(const Student* newStudents, const unsigned int numOfStudents);
    void printInformation() const;

    const char* getCourseName() const;
    const int getCourseCapacity() const;
    
    bool setCourseName(char* name);
    bool setCourseCapacity(unsigned int newCapacity);

};