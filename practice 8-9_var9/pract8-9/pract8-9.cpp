#include <iostream>
#include <string.h>
#include "clGroup.h"
#include <Windows.h>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Ввод данных о группе" << endl;
    clGroup BBBO;
    cout << "Ввод данных о студентах" << endl;
    BBBO.addStudent();
    cout << endl << endl;
    BBBO.addStudent();
    cout << endl << endl;
    BBBO.addStudent();
    cout << endl << endl;
    cout << "======================= ВЫВОД ДО СОРТИРОВКИ =======================" << endl;
    cout << BBBO << endl << endl;
    BBBO.insertSortGroup();
    cout << "======================= ВЫВОД ПОСЛЕ СОРТИРОВКИ =======================" << endl;
    cout << BBBO;
    return 0;
}

