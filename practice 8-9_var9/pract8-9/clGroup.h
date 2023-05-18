#include <iostream>
#include <string.h>
#include "clStudent.h"
using namespace std;
#pragma once
class clGroup
{
protected:
    string group;
    string insitut;
    string department;
    string surname_curator;
    string name_curator;
    string patronymic_curator;
    int count;
    clStudent* students;
    friend ostream& operator<<(ostream& os, clGroup& group);
public:
    clGroup()
    {
        count = 0;
        students = NULL;
        cout << "Введите группу: ";
        cin >> group;
        cout << "Введите институт: ";
        cin >> insitut;
        cout << "Введите выпускающую кафедру: ";
        cin >> department;
        cout << "Введите фамилию куратора: ";
        cin >> surname_curator;
        cout << "Введите имя куратора: ";
        cin >> name_curator;
        cout << "Введите отчество куратора: ";
        cin >> patronymic_curator;
    }
    void addStudent()
    {
        clStudent new_student;
        cin >> new_student;
        if (count == 0)
        {
            students = new clStudent[1];
            students[0] = new_student;
            count++;
        }
        else {
            count++;
            clStudent* ols = students;
            students = new clStudent[count];
            for (int i = 0; i < count - 1; i++)
            {
                students[i] = ols[i];
            }
            students[count - 1] = new_student;
        }
    }
    void insertSortGroup()
    {
        for (int i = 0; i < count; i++)
        {
            clStudent tmp = students[i];
            for (int j = i; j >= 0; j--)
            {
                if (j > 0 && students[j - 1] > tmp) {
                    students[j] = students[j - 1];
                }
                else {
                    students[j] = tmp;
                    break;
                }

            }
        }
    }
    ~clGroup()
    {
        delete[] students;
    }
};

istream& operator>> (istream& is, clStudent& student)
{
    cout << "Введите фамилию: ";
    is >> student.surname;
    cout << "Введите имя: ";
    is >> student.name;
    cout << "Введите отчество: ";
    is >> student.patronymic;
    cout << "Введите год рождения(ДД.ММ.ГГГГ): ";
    is >> student.birthDate.day;
    is.ignore();
    is >> student.birthDate.month;
    is.ignore();
    is >> student.birthDate.year;
    cout << "Введите пол: ";
    is >> student.sex;
    cout << "Введите дату поступления в институт(ДД.ММ.ГГГГ): ";
    is >> student.admissionDate.day;
    is.ignore();
    is >> student.admissionDate.month;
    is.ignore();
    is >> student.admissionDate.year;
    cout << "Введите стипендию: ";
    is >> student.schoolarsip;
    return is;
}
ostream& operator<<(ostream& os, clStudent& student)
{
    os << "Фамилия: " << student.surname << endl;
    os << "Имя: " << student.name << endl;
    os << "Отчество: " << student.patronymic << endl;
    os << "Дата рождения: ";
    student.birthDate.print_date(os);
    os << "Пол: " << student.sex << endl;
    os << "Дата поступления в институт: ";
    student.admissionDate.print_date(os);
    os << "Стипендия: " << student.schoolarsip << endl;
    os << "--------------------------------------------------------" << endl;
    return os;
}
ostream& operator<<(ostream& os, clGroup& group)
{
    os << "=============== Данные о группе =============" << endl;
    os << "Группа: " << group.group << endl;
    os << "Институт: " << group.insitut << endl;
    os << "Выпускающая кафедра: " << group.department << endl;
    os << "ФИО куратора группы: " << group.surname_curator << ' ' << group.name_curator << ' ' << group.patronymic_curator << endl;
    os << "============== Вывод всех студентов в данной группе =============" << endl;
    for (int i = 0; i < group.count; i++)
    {
        os << group.students[i] << endl;
    }

    return os;
}
