#include <iostream>
#include <string>

using namespace std;

//структура паспорта
struct passport {
    int series1, series2; //серия
    int number; //номер

    //функции вывода в консоль
    void print() {
        printf("Серия и номер паспорта: %2d %2d %6d", series1, series2, number);
    }
    void println() {
        print(); printf("\n");
    }

    //функция для считывания данные паспорта с консоли
    void scan() {
        cout << "Введите серию и номер паспорта: ";
        cin >> series1 >> series2 >> number;
    }
};

//структура даты
struct date {
    int day, month, year; //день месяц год

    date() {
        day = 1;
        month = 1;
        year = 1999;
    }

    //полный конструктор
    date(int _day, int _month, int _year) {
        day = _day;
        month = _month;
        year = _year;
    }

    //функции вывода в консоль
    void print() {
        printf("%2d.%2d.%4d", day, month, year);
    }
    void println() {
        print(); printf("\n");
    }

    //функция для считывания данные паспорта с консоли
    void scan() {
        cout << "Введите день месяц и год через пробел: ";
        cin >> day >> month >> year;
    }
};

//структура книги
struct book {
    string name, author;    //название и имя автора
    int pages, year;        //кол-во страниц, год издания

    //функции вывода в консоль
    void print() {
        printf("Информация о книге:\n");
        cout << "\tНазвание:\t" << name << '\n';
        cout << "\tАвтор:\t\t" << author << '\n';
        printf("\tКол-во страниц:\t%d\n", pages);
        printf("\tГод издания:\t%d\n", year);
    }
    void println() {
        print(); printf("\n");
    }

    //функция для считывания данные паспорта с консоли
    void scan() {
        cout << "Ввод информации о книге...\n";
        cout << "\tВведите название: "; getline(cin, name);
        cout << "\tВведите автора: "; getline(cin, author);
        cout << "\tВведите кол-во страниц: "; cin >> pages;
        cout << "\tВведите год издания: "; cin >> year;
    }
} books[100];
int booksCount = 0; //общее кол-во книг

struct reader {
    string fName;       //ФИО
    int year;           //Год рождения
    string gender;      //Пол
    passport pass;      //Данные паспорта
    string address;     //Адрес
    string number;      //Номер телефона

    //функции вывода в консоль
    void print() {
        printf("Информация о читателе:\n");
        cout << "\tФИО:\t" << fName << '\n';
        printf("\tГод рожения:\t%d\n", year);
        cout << "\tПол:\t" << gender << "\n\t";
        pass.println();
        cout << "\tАдрес:\t" << address << "\n";
        cout << "\tНомер телефона:\t" << number << '\n';
    }
    void println() {
        print(); printf("\n");
    }

    //функция для считывания данные паспорта с консоли
    void scan() {
        cout << "Ввод информации о читателе...\n";
        cout << "\tВведите ФИО: "; getline(cin, fName);
        cout << "\tВведите год рождения: "; cin >> year;
        cout << "\tВведите пол: "; cin >> gender;
        cout << "\t";
        pass.scan(); getline(cin, address);
        cout << "\tВведите адрес: "; getline(cin, address);
        cout << "\tВведите номер телефона: "; getline(cin, number);
    }
} readers[100];
int readersCount = 0; //общее кол-во читателей

struct list {
    reader* _reader;
    book* _book;
    date _date;
    int weeks;

    //функции вывода в консоль
    void print() {
        cout << "\tФИО читателя:\t" << _reader->fName << '\n';
        cout << "\tНазвание книги:\t" << _book->name << '\n';
        cout << "\tДата выдачи: "; _date.println();
        cout << "\tВыдана на срок в неделях: " << weeks << '\n';
    }
    void println() {
        print(); printf("\n");
    }

} lendList[100];
int lendsCount = 0; //общее кол-во выданных книг


//функция добавления новой книги
void addBook() {
    books[booksCount++].scan();
    cout << "Книга успешно добавлена\n";
}

//функция поиска книги по автору или названию
book* findBook(string str) {
    cout << "Поиск книги...\n";
    for (int i = 0; i < booksCount; ++i) {
        if (books[i].name.find(str) != string::npos ||
            books[i].author.find(str) != string::npos) {
            cout << "Книга найдена.\n";
            return &books[i];
        }
    }
    cout << "Книга не найдена!\n";
    return nullptr;
}

//функция добавления читателя
void addReader() {
    readers[readersCount++].scan();
    cout << "Читатель успешно добавлен\n";
}

//функция поиска читателя
reader* findReader(string str) {
    cout << "Поиск читателя...\n";
    for (int i = 0; i < readersCount; ++i) {
        if (readers[i].fName.find(str) != string::npos) {
            cout << "Читатель найден.\n";
            return &readers[i];
        }
    }
    cout << "Читатель не найден!\n";
    return nullptr;
}

bool addLend() {
    string fName, name;
    cout << "\tВведите фамилию читателя: "; getline(cin, fName);
    lendList[lendsCount]._reader = findReader(fName);
    if (lendList[lendsCount]._reader == nullptr) {
        return false;
    }

    cout << "\tВведите название книги: "; getline(cin, name);
    lendList[lendsCount]._book = findBook(name);
    if (lendList[lendsCount]._book == nullptr) {
        return false;
    }

    lendList[lendsCount]._date.scan();
    cout << "\tВведите срок в неделях: "; cin >> lendList[lendsCount].weeks;

    cout << "Книга успешно выдана.\n";
    ++lendsCount;
    return true;
}

bool eraseLend() {
    string fName, name;
    reader* _reader;
    book* _book;
    cout << "\tВведите ФИО читателя: "; getline(cin, fName);
    cout << "\tВведите название книги: "; getline(cin, fName);
    _book = findBook(name);
    _reader = findReader(fName);

    for (int i = 0; i < lendsCount; ++i) {
        if (lendList[i]._reader == _reader && lendList[i]._book == _book) {
            swap(lendList[i], lendList[lendsCount - 1]);
            --lendsCount;
            cout << "Книга успешно возвращена.\n";
            return true;
        }
    }

    cout << "Не удалось найти соответствующую выдачу...\n";
    return false;
}

void findLend(string fName) {
    cout << "Поиск книг...\n";
    reader* _reader = findReader(fName);
    cout << "Найденные книги:\n";
    for (int i = 0; i < lendsCount; ++i) {
        if (lendList[i]._reader == _reader) {
             cout << "\t" << lendList[i]._book->name << '\n';
        }
    }
    cout << "Поиск окончен.\n";
}

//функция редактирования списка
void listEdit() {
    printf("\nРедактирование списка...\n");
    printf("\t0-\tВывод списка\n");
    printf("\t1-\tВыдать книгу\n");
    printf("\t2-\tВернуть книгу\n");

    int cmd;
    string temp;
    printf("\tВведите команду: "); cin >> cmd; getline(cin, temp);

    if (cmd == 0) {
        for (int i = 0; i < lendsCount; ++i) {
            lendList[i].print();
        }
    }
    else if (cmd == 1) {
        addLend();
    }
    else if (cmd == 2) {
        eraseLend();
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int cmd;
    string temp;

    while (true) {
        printf("\n0- Выход из программы\n");
        printf("1- добавление новой книги\n");
        printf("2- поиск книги по автору или названию\n");
        printf("3- добавление нового читателя\n");
        printf("4- поиск читателя по фамилии\n");
        printf("5- редактирование списка выданных книг\n");
        printf("6- вывод книг, выданных читателю с заданной фамилией\n");
        printf("Введите команду: "); cin >> cmd; getline(cin, temp);

        if (cmd == 0) { break; }
        else if (cmd == 1) {
            addBook();
        }
        else if (cmd == 2) {
            cout << "Введите название или автора: "; getline(cin, temp);
            book* _book = findBook(temp);
            if (_book != nullptr) {
                _book->print();
            }
        }
        else if (cmd == 3) {
            addReader();
        }
        else if (cmd == 4) {
            cout << "Введите фамилию читателя: "; getline(cin, temp);
            reader* _reader = findReader(temp);
            if (_reader != nullptr) {
                _reader->print();
            }
        }
        else if (cmd == 5) {
            listEdit();
        }
        else if (cmd == 6) {
            cout << "Введите фамилию чиитателя: "; getline(cin, temp);
            reader* _reader = findReader(temp);
            for (int i = 0; i < lendsCount; ++i) {
                if (lendList[i]._reader == _reader) {
                    cout << "Найдена книга: " << lendList[i]._book->name << '\n';
                }
            }
        }
        else {
            cout << "Команда не найдена...\n";
        }
    }
    cin >> cmd;
}
