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
        cout << "������� ������: ";
        cin >> group;
        cout << "������� ��������: ";
        cin >> insitut;
        cout << "������� ����������� �������: ";
        cin >> department;
        cout << "������� ������� ��������: ";
        cin >> surname_curator;
        cout << "������� ��� ��������: ";
        cin >> name_curator;
        cout << "������� �������� ��������: ";
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
    cout << "������� �������: ";
    is >> student.surname;
    cout << "������� ���: ";
    is >> student.name;
    cout << "������� ��������: ";
    is >> student.patronymic;
    cout << "������� ��� ��������(��.��.����): ";
    is >> student.birthDate.day;
    is.ignore();
    is >> student.birthDate.month;
    is.ignore();
    is >> student.birthDate.year;
    cout << "������� ���: ";
    is >> student.sex;
    cout << "������� ���� ����������� � ��������(��.��.����): ";
    is >> student.admissionDate.day;
    is.ignore();
    is >> student.admissionDate.month;
    is.ignore();
    is >> student.admissionDate.year;
    cout << "������� ���������: ";
    is >> student.schoolarsip;
    return is;
}
ostream& operator<<(ostream& os, clStudent& student)
{
    os << "�������: " << student.surname << endl;
    os << "���: " << student.name << endl;
    os << "��������: " << student.patronymic << endl;
    os << "���� ��������: ";
    student.birthDate.print_date(os);
    os << "���: " << student.sex << endl;
    os << "���� ����������� � ��������: ";
    student.admissionDate.print_date(os);
    os << "���������: " << student.schoolarsip << endl;
    os << "--------------------------------------------------------" << endl;
    return os;
}
ostream& operator<<(ostream& os, clGroup& group)
{
    os << "=============== ������ � ������ =============" << endl;
    os << "������: " << group.group << endl;
    os << "��������: " << group.insitut << endl;
    os << "����������� �������: " << group.department << endl;
    os << "��� �������� ������: " << group.surname_curator << ' ' << group.name_curator << ' ' << group.patronymic_curator << endl;
    os << "============== ����� ���� ��������� � ������ ������ =============" << endl;
    for (int i = 0; i < group.count; i++)
    {
        os << group.students[i] << endl;
    }

    return os;
}
