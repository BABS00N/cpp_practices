#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

struct Date
{
    unsigned short day;
    unsigned short month;
    unsigned short year;
};
struct Record
{
    char product[15];
    char type[2];
    double price;
    unsigned short min;
    struct Date date;
};

void dash()
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

void drawDate(struct Record* records, int i, unsigned short length)
{
    cout.width(length); cout << "";

    if (records[i].date.day > 9) { cout << records[i].date.day << "."; }
    else { cout << "0" << records[i].date.day << "."; }

    if (records[i].date.month > 9) { cout << records[i].date.month << "."; }
    else { cout << "0" << records[i].date.month << "."; }

    if (records[i].date.year > 9) { cout << records[i].date.year; }
    else { cout << "0" << records[i].date.year; }

    cout.width(length); cout << "";
}
void draw(struct Record* records)
{
    cout.fill(' ');
    //Шапка
    dash();
    cout << "|Прайс-лист"; cout.width(90); cout << "|";

    dash();
    cout << "|";
    mid_position("Наименование товара", 1);
    mid_position("Тип товара", 1);
    mid_position("Цена за 1 шт (грн)", 3);
    mid_position("Минимальное количество", 1);
    mid_position("Дата", 5);
    dash();

    //Основные данные
    for (int i = 0; i < 3; i++)
    {
        cout << "|"; cout.width(21); cout << left << records[i].product;
        cout << "|"; cout.width(12); cout << left << records[i].type;
        cout << "|"; cout.width(24); cout.precision(5); cout << right << fixed << records[i].price;
        cout << "|"; cout.width(24); cout << left << records[i].min;
        cout << "|"; drawDate(records, i, 2); cout << "|";
        dash();
    }

    //Примечание
    cout << "|"; cout.width(99);
    cout << left << "Примечание: К – канцтовары, О – оргтехника"; cout << "|";
    dash();
}

//file.bin
void writingTxt(Record* records)
{
    ofstream file;
    file.open("Podrez.txt");
    for (int i = 0; i < 3; i++)
    {
        file << records[i].product << " ";
        file << records[i].type << " ";
        file << records[i].price << " ";
        file << records[i].min << " ";
        file << records[i].date.day << " ";
        file << records[i].date.month << " ";
        file << records[i].date.year << "\n";
    }
    file.close();
}
void readingTxt(Record* readRecords)
{
    ifstream file;
    file.open("Podrez.txt");
    for (int i = 0; i < 3; i++)
    {
        file >> readRecords[i].product;
        file >> readRecords[i].type;
        file >> readRecords[i].price;
        file >> readRecords[i].min;
        file >> readRecords[i].date.day;
        file >> readRecords[i].date.month;
        file >> readRecords[i].date.year;
    }
    cout << endl << "Чтенме текстового файла";
    draw(readRecords);
}

//file.txt
void writingBin(Record* records)
{
    ofstream file;
    file.open("Podrez.bin", ios_base::binary | ios_base::out);
    for (int i = 0; i < 3; i++)
    {
        file << records[i].product << " ";
        file << records[i].type << " ";
        file << records[i].price << " ";
        file << records[i].min << " ";
        file << records[i].date.day << " ";
        file << records[i].date.month << " ";
        file << records[i].date.year << "\n";
    }
    file.close();
}
void readingBin(Record* readRecords)
{
    ifstream file;
    file.open("Podrez.bin");
    for (int i = 0; i < 3; i++)
    {
        file >> readRecords[i].product;
        file >> readRecords[i].type;
        file >> readRecords[i].price; 
        file >> readRecords[i].min;
        file >> readRecords[i].date.day; 
        file >> readRecords[i].date.month;
        file >> readRecords[i].date.year;
    }
    cout << endl << "Чтенме бинарного файла";
    draw(readRecords);
}

//2 этап
void changeLines(Record* newRecords,int max, int min)
{
    Record adRecords = newRecords[max];
    newRecords[max] = newRecords[min];
    newRecords[min] = adRecords;
}

void comparison(double x, double y, double z, unsigned short& min_line, unsigned short& max_line)
{
    max_line = (x > y) ? 0 : 1;
    max_line = (max_line == 0) ? ((x > z) ? 0 : 2) : ((y > z) ? 1 : 2);
    min_line = (x < y) ? 0 : 1;
    min_line = (min_line == 0) ? ((x < z) ? 0 : 2) : ((y < z) ? 1 : 2);
}
void compare(Record* records)
{
    unsigned short choice, max_line = 0, min_line = 0;
    Record adRecords;

    cout << "Цена за 1 шт (грн) "; cout.width(40); cout.fill('-'); cout << right << " 1" << endl;
    cout << "Минимальное количество "; cout.width(36); cout.fill('-'); cout << right << " 2" << endl;
    cout << "Выбирите столбец, по которому будет осортирована таблица: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        comparison(records[0].price, records[1].price, records[2].price, min_line, max_line);
        break;
    }
    case 2:
    {
        comparison(float(records[0].min), float(records[1].min), float(records[2].min), min_line, max_line);
        break;
    }
    default:
        break;
    }

    fstream file;
    file.open("Podrez.bin", ios_base::binary | ios::in | ios::out);
    changeLines(records,max_line,min_line);
    writingBin(records);
    readingBin(records);
    file.close();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Record records[3];
    Record newRecords[3];
    records[0] = { "Папка","К",4.75,4,{3,7,2022} };
    records[1] = { "Бумага","К",13.9,10,{3,4,2021} };
    records[2] = { "Калькулятор","О",411,1,{4,3,2022} };

    writingTxt(records);
    readingTxt(records);

    writingBin(records);
    readingBin(newRecords);

    compare(newRecords);
}
