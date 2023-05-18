#include <iostream>
#include <string.h>
#include "clDate.h"
using namespace std;
#pragma once
class clStudent
{
protected:
    string surname;
    string name;
    string patronymic;
    clDate birthDate;
    string sex;
    clDate admissionDate;
    int schoolarsip;
    friend istream& operator >> (istream& is, clStudent& student);
    friend ostream& operator<<(ostream& os, clStudent& student);
public:
    bool operator<(const clStudent& _student) const
    {
        if (this->schoolarsip != _student.schoolarsip)
            return this->schoolarsip < _student.schoolarsip;
        else
            return this->admissionDate < _student.admissionDate;
    }
    bool operator>(const clStudent& _student) const
    {
        if (this->schoolarsip != _student.schoolarsip)
            return this->schoolarsip > _student.schoolarsip;
        else
            return this->admissionDate > _student.admissionDate;
    }
};