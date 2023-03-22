#include <iostream>
#include <Windows.h>
#include <string>
#include <math.h>
using namespace std;

#define N 95

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

struct node
{
    Record data;
    node* next;
};
node* head;
int countItem;

void dash(unsigned short n)
{
    cout.fill('-'); cout.width(n); cout << "-" << endl; cout.fill(' ');
}

void center(string s, int lineLen)
{
    int w = s.length();
    int delta = (lineLen - w) / 2;
    cout << left;
    cout.fill(' ');
    cout.width(delta); cout << ' ' << s;
    cout.width(delta); cout << ' ';
}

void drawDate(unsigned short day, unsigned short month, unsigned short year,unsigned short w)
{
    cout.width((w - 10) / 2); cout << "";

    if (day < 10) { cout << "0" << day << "."; }
    else { cout << day << "."; }

    if (month < 10) { cout << "0" << month << "."; }
    else { cout << month << "."; }

    cout << year;
    int t = (w - 10) / 2 + 1;
    cout.width(t); cout << right << "|";
}

void addItem(Record data)
{
    node* newItem = new node;
    newItem->data = data;
    if (countItem == 0)
    {
        head = newItem;
        head->next = head;
    }
    else
    {
        node* current = head;
        for (int i = 0; i < (countItem-1); i++)
        {
            current = current->next;
        }
        newItem->next=head;
        current->next = newItem;
    }
    countItem++;
}

void insertItem(int index, Record data)
{
    if (index < 1) {index = countItem+index;}
    else if (index > countItem) {index = abs(index % countItem);}
    index == 0 ? index = countItem: index;

    if(index == 1)
    {
        node* newItem = new node;
        newItem->data = data;
        newItem->next = head;
        head = newItem;
    }
    else
    {
        node* newItem = new node;
        newItem->data = data;
        node* current = head;
        for (int i = 1; i < (index-1); i++)
        {
            current = current->next;
        }
        newItem->next = current->next;
        current->next = newItem;
    }
    countItem++;
}

void insertMonth()
{
    node* current = head;
    Record newRecords = { "Степлер","К",50.99,1,{13,7,2023} };
    int temp = countItem;
    int fix = 0;
    for (int i = 0; i < temp; i++)
    {
        if (newRecords.date.month == current->data.date.month)
        {
            insertItem(i+1+fix, newRecords);
            fix++;
        }
        current = current->next;
    }
}

void drawHat()
{
    dash(N);
    cout.fill(' '); cout.width(N - 1); cout << left << "|Прайс-лист" << "|" << endl;
    dash(N);

    cout << '|'; center("Наименование товара", 20); cout << '|';
    center("Тип товара", 10); cout << '|';
    center("Цена за 1 шт (грн)", 16); cout << '|';
    center("Минимальное количество", 22); cout << '|';
    center("Дата", 12); cout << '|' << endl;
    dash(N);
}

void drawAdress()
{
    node* current = head->next;
    cout << "head[1] = " << head << endl;
    for (int i = 2; i <= countItem; i++)
    {
        cout << "node[" << i << "] = " << current << endl;
        current = current->next;
    }
}

void drawList()
{
    drawHat();
    node* current = head;
    for (int i = 0; i < countItem; i++)
    {
        cout << left << "|"; cout.width(21); cout << current->data.product; cout << "|";
        cout.width(12); cout << current->data.type; cout << "|";
        cout.width(20); cout.precision(5); cout << fixed << current->data.price; cout << "|";
        cout.width(24); cout << left << current->data.min; cout << "|";
        drawDate(current->data.date.day, current->data.date.month, current->data.date.year, 12);
        cout << endl; dash(N);
        current = current->next;
    }
    cout.fill(' '); cout.width(N - 1); cout << left << "|Примечание: К – канцтовары, О – оргтехника" << "|" << endl;
    dash(N);
    drawAdress();
}

void deleteList()
{
    node* current = head;
    node* temp;
    for (int i = 0; i < countItem; i++)
    {
        temp = current->next;
        delete[] current;
        current = temp;
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Record records[10];
    records[0] = { "Папка","К",4.75,4,{3,7,2022} };
    records[1] = { "Бумага","К",13.9,10,{3,4,2021} };
    records[2] = { "Калькулятор","О",411,1,{4,3,2022} };

    for (int i = 0; i<2; i++)
        for (int j=0;j<3;j++)
            addItem(records[j]);

    drawList();
    insertMonth();
    drawList();
    deleteList();
}