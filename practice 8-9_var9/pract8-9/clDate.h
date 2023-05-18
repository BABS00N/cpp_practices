#include <iostream>
#include <string.h>
using namespace std;
#pragma once
class clDate
{
public:
    int day;
    int month;
    int year;
public:
    void print_date(ostream& os)
    {
        if (day > 9) {
            os << day;
        }
        else {
            os << "0" << day;
        }
        cout << ".";

        if (month > 9) {
            os << month;
        }
        else {
            os << "0" << month;
        }
        os << ".";
        os << year << endl;
    }
    bool operator> (const clDate& _date) const
    {
        if (this->year > _date.year)
            return true;
        else if (this->month > _date.month)
            return true;
        else if (this->day > _date.day)
            return true;
        else
            return false;
    }
    bool operator< (const clDate& _date) const
    {
        if (this->year < _date.year)
            return true;
        else if (this->month < _date.month)
            return true;
        else if (this->day < _date.day)
            return true;
        else
            return false;
    }
};

