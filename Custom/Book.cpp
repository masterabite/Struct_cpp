#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//структура книги
struct book {
    string author, name;    //название и имя автора
    int year, count;        //год издания кол-во экземпляров
    string publishing;      //издательство

    //функции вывода в консоль
    void print() {
        cout << "\tАвтор:\t\t\t" << author << '\n';
        cout << "\tНазвание:\t\t" << name << '\n';
        cout << "\tИздательство:\t\t" << publishing << '\n';
        printf("\tГод изданияц:\t\t%d\n", year);
        printf("\tКол-во экземпляров:\t%d\n", count);
    }
    void println() {
        print(); printf("\n");
    }

    void fprint(ofstream& fout) {
        fout << author << '\n';
        fout << name << '\n';
        fout << publishing << '\n';
        fout << year << '\n';
        fout << count;
    }

    //функция для считывания данные паспорта с консоли
    void scan() {
        cout << "Ввод информации о книге...\n";
        cout << "\tВведите автора: "; getline(cin, author);
        cout << "\tВведите название: "; getline(cin, name);
        cout << "\tВведите издание: "; getline(cin, publishing);
        cout << "\tГод издания: "; cin >> year;
        cout << "\tКол-во экземпляра: "; cin >> count;
    }

    //считываем информацию из файла
    void fscan(ifstream& fin) {
        getline(fin, author);
        getline(fin, name);
        getline(fin, publishing);
        fin >> year;
        fin >> count; fin.get();
    }
} books[100]; //массив структур
int booksCount = 0; //общее кол-во книг


//функция добавления новой книги
void addBook() {
    books[booksCount++].scan();
    cout << "Книга успешно добавлена.\n";
}

//функция удаляет книгу по индексу
void eraseBook(int ind) {
    swap(books[booksCount - 1], books[ind]);
    --booksCount;
}

//загрузка из файла 
void load_from_file(string fname) {
    cout << "Загрузка из файла...\n";
    ifstream fin(fname);
    if (!fin.is_open()) {
        cout << "Не удалось открыть файл!\n";
        return;
    }

    booksCount = 0;
    while (!fin.eof()) {
        books[booksCount++].fscan(fin);
    }
    fin.close();
    printf("Файл \"%s\" успешно считан.\n", fname.c_str());
}

//сохранение в файл
void save_to_file(string fname) {
    cout << "Сохранение в файл...\n";
    ofstream fout(fname);
    if (!fout.is_open()) {
        printf("Не удалось открыть файл \"%s\" для записи.\n", fname.c_str());
        return;
    }
    for (int i = 0; i < booksCount; ++i) {
        books[i].fprint(fout);
        if (i != booksCount - 1) {
            fout << '\n';
        }
    }
    fout.close();
    printf("Файл \"%s\" успешно сохранен.\n", fname.c_str());
}


int main() {
    setlocale(LC_ALL, "Russian");
    int cmd;

    while (true) {
        printf("\n0- Выход из программы\n");
        printf("1- добавление новой книги\n");
        printf("2- поиск книги\n");
        printf("3- удаление униги\n");
        printf("4- просмотреть информацию о книгах библиотеки\n");
        printf("5- загрузить из файла\n");
        printf("6- сохранить в файл\n");
        printf("\nВведите команду: "); cin >> cmd; cin.get();

        if (cmd == 0) { break; }
        else if (cmd == 1) {                        //добавление книги
            addBook();
        }
        else if (cmd == 2) {                        //поиск книги
            printf("\t1- поиск по году выпуска\n");
            printf("\t2- поиск по автору\n");
            printf("\t3- поиск по издательству\n");
            printf("\t4- поиск по названию\n");
            printf("\tВведите команду: "); cin >> cmd; cin.get();
            if (cmd == 1) {
                int year;
                cout << "введите год выпуска: "; cin >> year; cin.get();
                cout << "Поиск книг...\n";
                for (int i = 0; i < booksCount; ++i) {
                    if (books[i].year == year) {
                        books[i].print();
                    }
                }
                cout << "Поиск окончен.\n";
            }
            else if (cmd == 2) {
                string author;
                cout << "введите автора: "; getline(cin, author);
                cout << "Поиск книг...\n";
                for (int i = 0; i < booksCount; ++i) {
                    if (books[i].author == author) {
                        books[i].print();
                    }
                }
                cout << "Поиск окончен.\n";
            }
            else if (cmd == 3) {
                string publishing;
                cout << "введите издательство: "; getline(cin, publishing);
                cout << "Поиск книг...\n";
                for (int i = 0; i < booksCount; ++i) {
                    if (books[i].publishing == publishing) {
                        books[i].print();
                    }
                }
                cout << "Поиск окончен.\n";
            }
            else if (cmd == 4) {
                string name;
                cout << "введите название: "; getline(cin, name);
                cout << "Поиск книг...\n";
                for (int i = 0; i < booksCount; ++i) {
                    if (books[i].name == name) {
                        books[i].print();
                    }
                }
                cout << "Поиск окончен.\n";
            }
        }
        else if (cmd == 3) {        //удаление книги по номеру
            int num;
            cout << "введите порядковый номер книги: "; cin >> num; --num; cin.get();
            cout << "Удаление книги...\n";
            if (num < 0 || num >= booksCount) {
                cout << "Ошибка. Выход за пределы массива.\n";
                continue;
            }

            eraseBook(num);
            cout << "Книга успешно удалена.\n";
        }
        else if (cmd == 4) {        //вывод всех книг
            if (booksCount == 0) {
                cout << "Список пуст!\n";
                continue;
            }
            cout << "Список книг:\n";
            for (int i = 0; i < booksCount; ++i) {
                printf("Информация о %d'й книге:\n", i+1);
                books[i].println();
            }
        }
        else if (cmd == 5) {
            string fname;
            cout << "Введите имя файла: "; 
            cin >> fname;
            load_from_file(fname);
        }
        else if (cmd == 6) {
            string fname;
            cout << "Введите имя файла: ";
            cin >> fname;
            save_to_file(fname);
        }
    }
}
