#include <iostream>
#include <stdio.h>
#include <Windows.h>
using namespace std;

struct date
{
    unsigned short day;
    unsigned short month;
    unsigned short year;
};

struct record
{
    char transport_kind[5];
    char route[5];
    float route_length;
    int travel_time;
    date Date;
};

void tire()
{
    cout << endl;
    for (int i = 0; i < 99; i++) cout << "-";
    cout << endl;
}

void mid_position(const char text[30], unsigned short length)
{
    cout.width(length);
    cout << "" << text;
    cout.width(length + 1);
    cout << "|";
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
    cout << "|Ведомость общественного транспорта"; cout.width(64); cout << "|";

    //Вид транспорта|маршрута|Протяженность маршрута (км)|Время в дороге (мин)|Дата
    tire();
    cout << "|";
    mid_position("Вид транспорта", 1);
    mid_position("Маршрут", 1);
    mid_position("Протяженность маршрута(км)", 3);
    mid_position("Время в дороге (мин)", 1);
    mid_position("Дата", 5);
    tire();

    //Основные данные
    for (int i = 0; i < 3; i++)
    {
        cout << "|"; cout.width(16); cout << left << line[i].transport_kind;
        cout << "|"; cout.width(9); cout << left << line[i].route;
        cout << "|"; cout.width(32); cout.precision(3); cout << right << fixed << line[i].route_length;
        cout << "|"; cout.width(22); cout << left << line[i].travel_time;
        cout << "|"; draw_date(line, i, 2); cout << "|";
        tire();
    }

    //Примечание
    cout << "|"; cout.width(97);
    cout << left << "Примечание: Тр - трамвай, Тс - троллейбус, А - автобус"; cout << "|";
    tire();
}

void swap(struct record* line)
{
    unsigned short choice, max_line, min_line;
    struct record additional_line;

    cout << "Вид транспорта "; cout.width(44); cout.fill('-'); cout << right << " 1" << endl;
    cout << "Маршрут "; cout.width(51); cout.fill('-'); cout << right << " 2" << endl;
    cout << "Протяженность маршрута (км) "; cout.width(31); cout.fill('-'); cout << right << " 3" << endl;
    cout << "Время в дороге (мин) "; cout.width(38); cout.fill('-'); cout << right << " 4" << endl;
    cout << "Дата "; cout.width(54); cout.fill('-'); cout << right << " 5" << endl;
    cout << "Выбирите столбец, по которому будет осортирована таблица: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        if (line[0].transport_kind > line[1].transport_kind)
        {
            max_line = 0;
            min_line = 1;
        }
        else
        {
            max_line = 1;
            min_line = 0;
        }
        if (line[max_line].transport_kind < line[2].transport_kind)
        {
            max_line = 2;
        }
        if (line[min_line].transport_kind > line[2].transport_kind)
        {
            min_line = 2;
        }
    }
    case 2:
    {
        if (line[0].route > line[1].route)
        {
            max_line = 0;
            min_line = 1;
        }
        else
        {
            max_line = 1;
            min_line = 0;
        }
        if (line[max_line].route < line[2].route)
        {
            max_line = 2;
        }
        if (line[min_line].route > line[2].route)
        {
            min_line = 2;
        }
    }
    case 3:
    {
        if (line[0].route_length > line[1].route_length)
        {
            max_line = 0;
            min_line = 1;
        }
        else
        {
            max_line = 1;
            min_line = 0;
        }
        if (line[max_line].route_length < line[2].route_length)
        {
            max_line = 2;
        }
        if (line[min_line].route_length > line[2].route_length)
        {
            min_line = 2;
        }
    }
    case 4:
    {
        if (line[0].travel_time > line[1].travel_time)
        {
            max_line = 0;
            min_line = 1;
        }
        else
        {
            max_line = 1;
            min_line = 0;
        }
        if (line[max_line].travel_time < line[2].travel_time)
        {
            max_line = 2;
        }
        if (line[min_line].travel_time > line[2].travel_time)
        {
            min_line = 2;
        }
    }
    case 5:
    {
        int a, b, c;
        a = int(line[0].Date.year) * 10000 + int(line[0].Date.month) * 100 + int(line[0].Date.day);
        b = int(line[1].Date.year) * 10000 + int(line[1].Date.month) * 100 + int(line[1].Date.day);
        c = int(line[2].Date.year) * 10000 + int(line[2].Date.year) * 100 + int(line[2].Date.year);

        if (a > b)
        {
            if (a > c) max_line = 0;
            else max_line = 2;
        }
        else
        {
            if (b > c) max_line = 1;
            else max_line = 2;
        }
        if (a < b)
        {
            if (a < c) min_line = 0;
            else min_line = 2;
        }
        else
        {
            if (b < c) min_line = 1;
            else min_line = 2;
        }
    }
    default:
        break;
    }

    strcpy_s(additional_line.transport_kind, line[max_line].transport_kind);
    strcpy_s(line[max_line].transport_kind, line[min_line].transport_kind);
    strcpy_s(line[min_line].transport_kind, additional_line.transport_kind);

    strcpy_s(additional_line.route, line[max_line].route);
    strcpy_s(line[max_line].route, line[min_line].route);
    strcpy_s(line[min_line].route, additional_line.route);

    additional_line.route_length = line[max_line].route_length;
    line[max_line].route_length = line[min_line].route_length;
    line[min_line].route_length = additional_line.route_length;

    additional_line.travel_time = line[max_line].travel_time;
    line[max_line].travel_time = line[min_line].travel_time;
    line[min_line].travel_time = additional_line.travel_time;

    additional_line.Date.day = line[max_line].Date.day;
    line[max_line].Date.day = line[min_line].Date.day;
    line[min_line].Date.day = additional_line.Date.day;

    additional_line.Date.month = line[max_line].Date.month;
    line[max_line].Date.month = line[min_line].Date.month;
    line[min_line].Date.month = additional_line.Date.month;

    additional_line.Date.year = line[max_line].Date.year;
    line[max_line].Date.year = line[min_line].Date.year;
    line[min_line].Date.year = additional_line.Date.year;

    draw(line);
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    struct record line[3];

    line[0] = { "Тр.", "12", float(27.550), 75, {03,04,2022} };
    line[1] = { "Т-с", "17", float(13.600), 57, {03,04,2020} };
    line[2] = { "А", "12а", float(57.300), 117, {04,03,2022} };

    draw(line);

    cout << endl;

    swap(line);
}

/*additional_line.Date.day = line[max_line].Date.day; line[max_line].Date.day = line[min_line].Date.day; line[min_line].Date.day = additional_line.Date.day;
        additional_line.Date.month = line[max_line].Date.month; line[max_line].Date.month = line[min_line].Date.month; line[min_line].Date.month = additional_line.Date.month;
        additional_line.Date.year = line[max_line].Date.year; line[max_line].Date.year = line[min_line].Date.year; line[min_line].Date.year = additional_line.Date.year;*/