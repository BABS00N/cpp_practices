#include <iostream>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <cstdlib>

using namespace std;

struct date
{
    int day;
    int month;
    int year;
};

struct record
{
    char product_name[12];
    char product_type[12];
    float coast;
    int min_count;
    date Date;
};

void tire()
{
    cout << endl;
    for (int i = 0; i < 101; i++) cout << "-";
    cout << endl;
}

void mid_position(const char text[30], unsigned short length)
{
    cout.width(length);
    cout << "" << text;
    cout.width(length + 1);
    cout << "|";
}

void comparison(float x, float y, float z, unsigned short& min_line, unsigned short& max_line)
{
    max_line = (x > y) ? 0 : 1;
    max_line = (max_line == 0) ? ((x > z) ? 0 : 2) : ((y > z) ? 1 : 2);
    min_line = (x < y) ? 0 : 1;
    min_line = (min_line == 0) ? ((x < z) ? 0 : 2) : ((y < z) ? 1 : 2);
}

void swap_str(char(&x)[12], char(&y)[12], char(&z)[12])
{
    strcpy_s(z, x);
    strcpy_s(x, y);
    strcpy_s(y, z);
}

void swap_float(float& x, float& y, float& z)
{
    z = x;
    x = y;
    y = z;
}

void swap_int(int& x, int& y, int& z)
{
    z = x;
    x = y;
    y = z;
}

void draw_date(struct record* line, int i, unsigned short length)
{
    cout.width(length); cout << "";

    if (line[i].Date.day > 9) { cout << line[i].Date.day << "."; }
    else { cout << "0" << line[i].Date.day << "."; }

    if (line[i].Date.month > 9) { cout << line[i].Date.month << "."; }
    else { cout << "0" << line[i].Date.month << "."; }

    if (line[i].Date.year > 9) { cout << line[i].Date.year; }
    else { cout << "0" << line[i].Date.year; }

    cout.width(length); cout << "";
}

void draw(struct record* line)
{
    cout.fill(' ');
    //Шапка
    tire();
    cout << "|Прайс-лист"; cout.width(90); cout << "|";

    tire();
    cout << "|";
    mid_position("Наименование товара", 1);
    mid_position("Тип товара", 1);
    mid_position("Цена за 1 шт (грн)", 3);
    mid_position("Минимальное количество", 1);
    mid_position("Дата", 5);
    tire();

    //Основные данные
    for (int i = 0; i < 3; i++)
    {
        cout << "|"; cout.width(21); cout << left << line[i].product_name;
        cout << "|"; cout.width(12); cout << left << line[i].product_type;
        cout << "|"; cout.width(24); cout.precision(5); cout << right << fixed << line[i].coast;
        cout << "|"; cout.width(24); cout << left << line[i].min_count;
        cout << "|"; draw_date(line, i, 2); cout << "|";
        tire();
    }

    //Примечание
    cout << "|"; cout.width(99);
    cout << left << "Примечание: К – канцтовары, О – оргтехника"; cout << "|";
    tire();
}

void swap_main(struct record* line)
{
    unsigned short choice, max_line = 0, min_line = 0;
    struct record additional_line;

    cout << "Цена за 1 шт (грн) "; cout.width(40); cout.fill('-'); cout << right << " 1" << endl;
    cout << "Минимальное количество "; cout.width(36); cout.fill('-'); cout << right << " 2" << endl;
    cout << "Дата "; cout.width(54); cout.fill('-'); cout << right << " 3" << endl;
    cout << "Выбирите столбец, по которому будет осортирована таблица: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        comparison(line[0].coast, line[1].coast, line[2].coast, min_line, max_line);
        break;
    }
    case 2:
    {
        comparison(float(line[0].min_count), float(line[1].min_count), float(line[2].min_count), min_line, max_line);
        break;
    }
    case 3:
    {
        int a, b, c;
        a = int(line[0].Date.year) * 10000 + int(line[0].Date.month) * 100 + int(line[0].Date.day);
        b = int(line[1].Date.year) * 10000 + int(line[1].Date.month) * 100 + int(line[1].Date.day);
        c = int(line[2].Date.year) * 10000 + int(line[2].Date.month) * 100 + int(line[2].Date.day);

        comparison(float(a), float(b), float(c), min_line, max_line);
        break;
    }
    default:
        break;
    }
    swap_str(line[max_line].product_name, line[min_line].product_name, additional_line.product_name);
    swap_str(line[max_line].product_type, line[min_line].product_type, additional_line.product_type);
    swap_float(line[max_line].coast, line[min_line].coast, additional_line.coast);
    swap_int((line[max_line].min_count), line[min_line].min_count, additional_line.min_count);
    swap_int(line[max_line].Date.day, line[min_line].Date.day, additional_line.Date.day);
    swap_int(line[max_line].Date.month, line[min_line].Date.month, additional_line.Date.month);
    swap_int(line[max_line].Date.year, line[min_line].Date.year, additional_line.Date.year);

    draw(line);
}



int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    struct record line[3];

    line[0] = { "Папка", "К", float(4.75000), 4, {03,07,2022} };
    line[1] = { "Бумага", "К", float(13.90000), 10, {03,04,2021} };
    line[2] = { "Калькулятор", "О", float(411.00000), 1, {04,03,2022} };

    draw(line);

    cout << endl;

    swap_main(line);

    int n = 3;
    record* A;
    A = (record*)malloc(n * sizeof(record));
    for (int i = 0; i < n; i++)
    {
        strcpy_s(A[i].product_name, line[i].product_name);
    }
    A = (record*)realloc(A, 10 * sizeof(record));

    record* B;

    B = (record*) new record[10];
    for (int i = 0; i < 10; i++)
    {
        B[i] = line[i];
    }
    
    for (int i = 0; i < 10; i++)
    {
        cout << endl << "Адрес B[i] " << &B[i] << " b[i]->product_name " << B[i].product_name;
    }
    free(A);
    delete[]B;
}