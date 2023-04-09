#include <iostream>
#include <Windows.h>
#include <fstream>
using namespace std;

struct Date
{
    unsigned short day;
    unsigned short month;
    unsigned short year;
};

struct Record
{
    string product;
    char type;
    double price;
    unsigned short min;
    struct Date date;
};

class clDate
{
private:
    unsigned short day;
    unsigned short month;
    unsigned short year;
public:
    clDate()
    {
        setDate(12,4,2023);
    }
    clDate(unsigned short _day, unsigned short _month, unsigned short _year)
    {
        setDate(_day, _month, _year);
    }
    clDate(Date _date)
    {
        setDate(_date);
    }
    clDate(const clDate &p)
    {
        this->day = p.day;
        this->month = p.month;
        this->year = p.year;
        if (day < 26)
        {
            day += 5;
        }
        else
        {
            cout << "Недопустимая дата\n";
        }
        
    }

    ~clDate() {};

    void setDate(unsigned short _day, unsigned short _month, unsigned short _year)
    {
        day = _day;
        month = _month;
        year = _year;
    }
    void setDate(Date _date)
    {
        setDate(_date.day, _date.month, _date.year);
    }
    void setDate(Date* _date)
    {
        setDate(_date->day, _date->month, _date->year);
    }

    void getDate()
    {
        Date _date;
        _date.day = this->day;
        _date.month = this->month;
        _date.year = this->year;
        printDate(_date);
    }

    void printDate(Date _date)
    {
        if (_date.day < 10) { cout << 0; }
        cout << day << ".";
        if (_date.month < 10) { cout << 0; }
        cout << month << "." << year << endl;
    }
};

class clRecord
{
    string product;
private:
    double price;
protected:
    unsigned short min;
    clDate date;
public:
    char type;

    clRecord()
    {
        setRecord("Пресс-папье", 'К', 17499.99, 1, { 29,8,2015 });
    }
    clRecord(fstream &file)
    {
        setRecord(file);
    }
    clRecord(Record * _Record)
    {
        setRecord(_Record);
    }

    ~clRecord() {};

    /*void setRecord()
    {

    }*/
    void setRecord(string _product, char _type, double _price, unsigned short _min, clDate _clDate)
    {
        product = _product;
        type = _type;
        price = _price;
        min = _min;
        date = _clDate;
    }
    void setRecord(fstream &file)
    {
        unsigned short _day;
        unsigned short _month;
        unsigned short _year;

        file >> product;
        file >> type;
        file >> price;
        file >> min;
        file >> _day;
        file >> _month;
        file >> _year;

        date.setDate(_day, _month, _year);
    }
    void setRecord(Record* record)
    {
        setRecord(record->product, record->type, record->price, record->min, record->date);
    }

    void getRecord()
    {
        cout << product << " " << type << " " << price << " " << min << " ";
        date.getDate();
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    fstream file("file.txt");
    Date date = { 9,4,2023 };

    clRecord staticRecords[3];
    staticRecords[0].setRecord( "Папка",'К',4.75,4,{3,7,2022} );
    staticRecords[1].setRecord("Бумага", 'К', 13.9, 10, { 3,4,2021 });
    staticRecords[2].setRecord("Калькулятор", 'О', 411, 1, { 4,3,2022 });

    clRecord* dynamicRecords = new clRecord[3];
    dynamicRecords[0].setRecord("Папка", 'К', 4.75, 4, { 3,7,2022 });
    dynamicRecords[1].setRecord("Бумага", 'К', 13.9, 10, { 3,4,2021 });
    dynamicRecords[2].setRecord("Калькулятор", 'О', 411, 1, { 4,3,2022 });

    clDate A;
    clDate B(1, 2, 2023);
    clDate C(date);
    clDate* D = new clDate(12,12,1212);
    clDate DC(A);
    clRecord record1(file);
    clRecord* record2 = new clRecord;

    delete D;
    delete record2;
    delete[] dynamicRecords;
};
