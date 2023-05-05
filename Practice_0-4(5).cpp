#include <iostream>
#include <Windows.h>
#include <fstream>
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
    string product;
    char type;
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

class clDate
{
private:
    unsigned short day;
    unsigned short month;
    unsigned short year;
public:
    clDate()
    {
        setDate(12, 4, 2023);
    }
    clDate(unsigned short _day, unsigned short _month, unsigned short _year)
    {
        setDate(_day, _month, _year);
    }
    clDate(Date _date)
    {
        setDate(_date);
    }
    clDate(const clDate& p)
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
    clRecord(fstream& file)
    {
        setRecord(file);
    }
    clRecord(Record* _Record)
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
    void setRecord(fstream& file)
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


void dash(unsigned short n)
{
    //cout << endl;
    cout.fill('-'); cout.width(n); cout << "-" << endl; cout.fill(' '); 
}

void center(string s, int recordsLen)
{
    int w = s.length();
    int delta = (recordsLen - w) / 2;
    cout << left;
    cout.fill(' ');
    cout.width(delta); cout << ' ' << s;
    cout.width(delta); cout << ' ';
}

void drawDate(unsigned short day, unsigned short month, unsigned short year, unsigned short w)
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
void draw(struct Record* records)
{
    cout.fill(' ');
    //Шапка
    cout << endl; dash(97);
    cout << "|Прайс-лист"; cout.width(86); cout << "|";

    cout << endl; dash(97);
    cout << "|";
    center("Наименование товара |", 1);
    center("Тип товара|", 1);
    center("Цена за 1 шт (грн)    |", 12);
    center("Минимальное количество|", 1);
    center("Дата    |", 7);
    cout << endl; dash(97);

    //Основные данные
    for (int i = 0; i < 3; i++)
    {
        cout << "|"; cout.width(21); cout << left << records[i].product;
        cout << "|"; cout.width(12); cout << left << records[i].type;
        cout << "|"; cout.width(24); cout.precision(5); cout << right << fixed << records[i].price;
        cout << "|"; cout.width(24); cout << left << records[i].min;
        cout << "|"; drawDate(records->date.day, records->date.month, records->date.year, 10); cout << "";
        cout << endl; dash(97);
    }

    //Примечание
    cout << "|"; cout.width(95);
    cout << left << "Примечание: К – канцтовары, О – оргтехника"; cout << "|";
    cout << endl; dash(97);
}
//------------------------------------------------
void comparison(float x, float y, float z, unsigned short& min_line, unsigned short& max_line)
{
    max_line = (x > y) ? 0 : 1;
    max_line = (max_line == 0) ? ((x > z) ? 0 : 2) : ((y > z) ? 1 : 2);
    min_line = (x < y) ? 0 : 1;
    min_line = (min_line == 0) ? ((x < z) ? 0 : 2) : ((y < z) ? 1 : 2);
}

void swap_str(string & x, string& y, string & z)
{
    z = x;
    x = y;
    y = z;
}

void swap_float(double& x, double& y, double& z)
{
    z = x;
    x = y;
    y = z;
}

void swap_int(unsigned short& x, unsigned short& y, unsigned short& z)
{
    z = x;
    x = y;
    y = z;
}

void swap_char(char& x, char& y, char& z)
{
    z = x;
    x = y;
    y = z;
}

void swap_main(struct Record* records)
{
    unsigned short choice, max_line = 0, min_line = 0;
    struct Record additional_line;

    cout << "Цена за 1 шт (грн) "; cout.width(40); cout.fill('-'); cout << right << " 1" << endl;
    cout << "Минимальное количество "; cout.width(36); cout.fill('-'); cout << right << " 2" << endl;
    cout << "Дата "; cout.width(54); cout.fill('-'); cout << right << " 3" << endl;
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
    case 3:
    {
        int a, b, c;
        a = int(records[0].date.year) * 10000 + int(records[0].date.month) * 100 + int(records[0].date.day);
        b = int(records[1].date.year) * 10000 + int(records[1].date.month) * 100 + int(records[1].date.day);
        c = int(records[2].date.year) * 10000 + int(records[2].date.month) * 100 + int(records[2].date.day);

        comparison(float(a), float(b), float(c), min_line, max_line);
        break;
    }
    default:
        break;
    }
    swap_str(records[max_line].product, records[min_line].product, additional_line.product);
    swap_char(records[max_line].type, records[min_line].type, additional_line.type);
    swap_float(records[max_line].price, records[min_line].price, additional_line.price);
    swap_int(records[max_line].min, records[min_line].min, additional_line.min);
    swap_int(records[max_line].date.day, records[min_line].date.day, additional_line.date.day);
    swap_int(records[max_line].date.month, records[min_line].date.month, additional_line.date.month);
    swap_int(records[max_line].date.year, records[min_line].date.year, additional_line.date.year);

    draw(records);
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
        for (int i = 0; i < (countItem - 1); i++)
        {
            current = current->next;
        }
        newItem->next = head;
        current->next = newItem;
    }
    countItem++;
}

void insertItem(int index, Record data)
{
    if (index < 1) { index = countItem + index; }
    else if (index > countItem) { index = abs(index % countItem); }
    index == 0 ? index = countItem : index;

    if (index == 1)
    {
        node* newItem = new node;
        node* current = head;
        newItem->data = data;
        while (current->next != head) { current = current->next; }
        current->next = newItem;
        newItem->next = head;
        head = newItem;
    }
    else
    {
        node* newItem = new node;
        newItem->data = data;
        node* current = head;
        for (int i = 1; i < (index - 1); i++)
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
    Record newRecords = { "Степлер",'K',50.99,1,{13,7,2023} };
    cout << endl << "Наименование товара: "; cin >> newRecords.product;
    cout << "Тип товара: "; cin >> newRecords.type;
    cout << "Цена за 1 шт (грн): "; cin >> newRecords.price;
    cout << "Минимальное количество: "; cin >> newRecords.min;
    cout << "Дата:" << endl << "     День: "; cin >> newRecords.date.day;
    cout << "     Месяц: "; cin >> newRecords.date.month;
    cout << "     Год: "; cin >> newRecords.date.year;
    int temp = countItem;
    int fix = 0;
    for (int i = 0; i < temp; i++)
    {
        if (newRecords.date.month == current->data.date.month)
        {
            insertItem(i + 1 + fix, newRecords);
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
    cout << "head[1] = " << head << "   head[1]->next = " << current << endl;
    for (int i = 2; i <= countItem; i++)
    {
        cout << "node[" << i << "] = " << current << "   node[" << i << "]->next = " << current->next << endl;
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

void changeLines(Record* newRecords, int max, int min)
{
    Record adRecords = newRecords[max];
    newRecords[max] = newRecords[min];
    newRecords[min] = adRecords;
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
    changeLines(records, max_line, min_line);
    writingBin(records);
    readingBin(records);
    file.close();
}

//------------------------------------------------

void praktika0()
{
    struct Record records[3];

    records[0] = { "Папка", 'К', float(4.75000), 4, {03,07,2022}};
    records[1] = { "Бумага", 'К', float(13.90000), 10, {03,04,2021} };
    records[2] = { "Калькулятор", 'О', float(411.00000), 1, {04,03,2022} };

    draw(records);
}

void praktika1()
{
    struct Record records[3];

    records[0] = { "Папка", 'K', float(4.75000), 4, {03,07,2022} };
    records[1] = { "Бумага", 'К', float(13.90000), 10, {03,04,2021} };
    records[2] = { "Калькулятор", 'О', float(411.00000), 1, {04,03,2022} };

    draw(records);

    cout << endl;

    swap_main(records);
}

void praktika2()
{
    struct Record records[3];

    records[0] = { "Папка", 'K', float(4.75000), 4, {03,07,2022} };
    records[1] = { "Бумага", 'K', float(13.90000), 10, {03,04,2021} };
    records[2] = { "Калькулятор", 'O', float(411.00000), 1, {04,03,2022} };

    draw(records);

    cout << endl;

    swap_main(records);

    int n = 3;
    Record* A;
    A = (Record*)malloc(n * sizeof(Record));
    for (int i = 0; i < n; i++)
    {
        A[i].product = records[i].product;
    }
    A = (Record*)realloc(A, 10 * sizeof(Record));

    Record* B;

    B = (Record*) new Record[10];
    for (int i = 0; i < 10; i++)
    {
        B[i] = records[i];
    }

    for (int i = 0; i < 10; i++)
    {
        cout << endl << "Адрес B[i] " << &B[i] << " b[i]->product " << B[i].product;
    }
    free(A);
    delete[]B;
}

void praktika3()
{
    Record records[10];
    records[0] = { "Папка",'K',4.75,4,{3,7,2022} };
    records[1] = { "Бумага",'K',13.9,10,{3,4,2021} };
    records[2] = { "Калькулятор",'O',411,1,{4,3,2022} };

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            addItem(records[j]);

    drawList();
    insertMonth();
    drawList();
    deleteList();
}

void praktika4()
{
    Record records[3];
    Record newRecords[3];
    records[0] = { "Папка",'K',4.75,4,{3,7,2022} };
    records[1] = { "Бумага",'К',13.9,10,{3,4,2021} };
    records[2] = { "Калькулятор",'O',411,1,{4,3,2022} };

    writingTxt(records);
    readingTxt(records);

    writingBin(records);
    readingBin(newRecords);

    compare(newRecords);
}

void praktika5() {
    fstream file("file.txt");
    Date date = { 9,4,2023 };

    clRecord staticRecords[3];
    staticRecords[0].setRecord("Папка", 'К', 4.75, 4, { 3,7,2022 });
    staticRecords[1].setRecord("Бумага", 'К', 13.9, 10, { 3,4,2021 });
    staticRecords[2].setRecord("Калькулятор", 'О', 411, 1, { 4,3,2022 });

    clRecord* dynamicRecords = new clRecord[3];
    dynamicRecords[0].setRecord("Папка", 'К', 4.75, 4, { 3,7,2022 });
    dynamicRecords[1].setRecord("Бумага", 'К', 13.9, 10, { 3,4,2021 });
    dynamicRecords[2].setRecord("Калькулятор", 'О', 411, 1, { 4,3,2022 });

    clDate A;
    clDate B(1, 2, 2023);
    clDate C(date);
    clDate* D = new clDate(12, 12, 1212);
    clDate DC(A);
    clRecord record1(file);
    clRecord* record2 = new clRecord;

    delete D;
    delete record2;
    delete[] dynamicRecords;
}

void menu() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int menu = -1;
	while (menu != 0) {
		cout << "Введите значение от 0 до 6:" << endl;
		cout << "0: Выход" << endl;
		cout << "1: Практика 0 (Вариант 9)" << endl;
		cout << "2: Практика 1 (Вариант 9)" << endl;
		cout << "3: Практика 2 (Вариант 7)" << endl;
		cout << "4: Практика 3 (Вариант 7)" << endl;
		cout << "5: Практика 4 (Вариант 7)" << endl;
		cout << "6: Практика 5 (Вариант 7)" << endl;
		cin >> menu;
		system("cls");
		switch (menu)
		{
		case 0: break;
		case 1: praktika0(); break;
		case 2: praktika1(); break;
		case 3: praktika2(); break;
		case 4: praktika3(); break;
		case 5: praktika4(); break;
		case 6: praktika5(); break;
		default:
			cout << "Введите другое значение. Вы ввели: " << menu << " Должно быть в диапазоне от 0 до 6" << endl;
			break;
		}
	}
}

int main()
{
	menu();
}