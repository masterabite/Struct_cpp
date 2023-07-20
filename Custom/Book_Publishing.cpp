#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//структура издательства
struct publishing {
    int year;
    string name, city;

    //функции вывода в консоль
    void print() {
        printf("\tГод издания:\t\t%d\n", year);
        cout << "\tНазвание издания:\t" << name << '\n';
        cout << "\tГород:\t\t\t" << city << "\n";
    }
    void println() {
        print(); printf("\n");
    }

    //функция для считывания данные паспорта с консоли
    void scan() {
        cout << "Ввод информации об издательстве...\n";
        cout << "\tВведите год издания: "; cin >> year;
        cin.get();
        cout << "\tВведите название: "; getline(cin, name);
        cout << "\tВведите город: "; getline(cin, city);
    }
};

//структура книги
struct book {
    string name, author;    //название и имя автора
    int price, pages;       //кол-во страниц
    publishing publish;     //издательство

    //функции вывода в консоль
    void print() {
        printf("Информация о книге:\n");
        cout << "\tНазвание:\t\t" << name << '\n';
        printf("\tЦена:\t\t\t%d\n", price);
        printf("\tКол-во страниц:\t\t%d\n", pages);
        cout << "\tАвтор:\t\t\t" << author << '\n';
        publish.print();
    }
    void println() {
        print(); printf("\n");
    }

    //функция для считывания данные паспорта с консоли
    void scan() {
        cout << "Ввод информации о книге...\n";
        cout << "\tВведите название: "; getline(cin, name);
        cout << "\tВведите цену: "; cin >> price;
        cout << "\tВведите кол-во страниц: "; cin >> pages;
        cin.get();
        cout << "\tВведите автора: "; getline(cin, author);
        publish.scan();
    }

    void fscan(ifstream& fin) {
        if (!fin.is_open()) {
            return;
        }

        getline(fin, name);
        fin >> price >> pages;
        fin.get();
        getline(fin, author);
        fin >> publish.year;
        fin.get();
        getline(fin, publish.name);
        getline(fin, publish.city);
    }

} books[100];
int booksCount = 0; //общее кол-во книг

//функция добавления новой книги
void addBook() {
    books[booksCount++].scan();
    cout << "Книга успешно добавлена\n";
}

int main() {
    setlocale(LC_ALL, "Russian");
    int cnt; //переменная для поиска, означает кол-во найденных соответствий

    
    //вводим структуры
    char cmd = 'y';
    while (cmd == 'y') {
        addBook();
        printf("Продолжить ввод? y/n: ");
        cin >> cmd;
        cin.get();
    }

    cout << "Ввод завершен.\n";
    for (int i = 0; i < booksCount; ++i) {
        books[i].println();
    }

//1.________________________________________________________________
    cnt = 0; //кол-во соответствий
    printf("\nПоиск авторов, чьи книги стоят более 100 р...\n");
    for (int i = 0; i < booksCount; ++i) {
        if (books[i].price > 100) {
            ++cnt;
            printf("Найден автор: %s\n", books[i].author.c_str());
        }
    }
    printf("Поиск окончен. Всего соответствий: %d\n", cnt);
//  ________________________________________________________________  


//2.________________________________________________________________
    printf("\nПоиск издательств, в которых издано максимальное число книг, вышедших в заданном году...\n");
    int year;
    cout << "Введите год: "; cin >> year;
    printf("Список издательств:\n");
    int mx = 0; //максимальное кол-во книг в year году от одного издания
    for (int i = 0; i < booksCount; ++i) {
        cnt = 0; //кол-во книг изданных издательством, выпустившем i-ую книгу, в заданном году
        for (int j = 0; j < booksCount; ++j) {
            if (books[j].publish.year == year && books[i].publish.name == books[j].publish.name) {
                ++cnt;
            }
        }
        if (cnt > mx) {
            mx = cnt;
        }
    }

    //теперь выводим ответ
    for (int i = 0; i < booksCount; ++i) {

        bool check = true; //проверяем что мы это еще не выводили
        for (int j = 0; j < i; ++j) {
            if (books[i].publish.name == books[j].publish.name) {
                check = false;
            }
        }
        if (check) {
            cnt = 0; //кол-во книг изданных издательством, выпустившем i-ую книгу, в заданном году

            for (int j = 0; j < booksCount; ++j) {
                if (books[j].publish.year == year && books[i].publish.name == books[j].publish.name) {
                    ++cnt;
                }
            }

            if (cnt == mx) {
                cout << '\t' << books[i].publish.name << '\n';
            }
        }
    }
    cout << "Конец списка.\n";
 //  ________________________________________________________________  




//4.________________________________________________________________
    printf("\nСписок городов, в которых выпускаются самые дешевые книги:\n");

    int mn = books[0].price; //минимальная цена книг
    for (int i = 0; i < booksCount; ++i) {
        if (books[i].price < mn) {
            mn = books[i].price;
        }
    }

    //теперь выводим ответ
    for (int i = 0; i < booksCount; ++i) {

        bool check = true; //проверяем что мы это еще не выводили
        for (int j = 0; j < i; ++j) {
            if (books[i].price == books[j].price && books[i].publish.city == books[j].publish.city) {
                check = false;
            }
        }

        if (check && books[i].price == mn) {
            cout << '\t' << books[i].publish.city << '\n';
        }
    }
    cout << "Конец списка.\n";
//  ________________________________________________________________  


//5.________________________________________________________________
    printf("\nСписок авторов, книги которых имеют максимальную цену:\n");

    mx = books[0].price; //максимальное цена книг
    for (int i = 0; i < booksCount; ++i) {
        if (books[i].price > mx) {
            mx = books[i].price;
        }
    }

    //теперь выводим ответ
    for (int i = 0; i < booksCount; ++i) {

        bool check = true; //проверяем что мы эту функцию еще не выводили
        for (int j = 0; j < i; ++j) {
            if (books[i].price == books[j].price && books[i].author == books[j].author) {
                check = false;
            }
        }

        if (check && books[i].price == mx) {
            cout << '\t' << books[i].author << '\n';
        }
    }
    cout << "Конец списка.\n";
//  ________________________________________________________________  



//6.________________________________________________________________
    printf("\nПоиск авторов, все книги которых имеют число страниц, превышающее заданное...\n");
    int pages;
    cout << "Введите кол-во страниц: "; cin >> pages;
    printf("Список авторов:\n");

    //выводим ответ
    for (int i = 0; i < booksCount; ++i) {

        bool check = true; //проверяем что этот автор подходит еще не выводили
        for (int j = 0; j < booksCount; ++j) {
            if (books[i].author == books[j].author && books[j].pages <= pages) {
                check = false; 
                break;
            }
        }

        for (int j = 0; j < i; ++j) {
            if (books[i].author == books[j].author) { 
                check = false;
                break;
            }
        }

        if (check) {
            cout << '\t' << books[i].author << '\n';
        }
    }
    cout << "Конец списка.\n";
//  ________________________________________________________________  


//7.________________________________________________________________
    printf("\nПоиск городов, где расположено максимальное число издательств с разными названиями...\n");

    mx = 0; //максимальное кол-во изданий для одного города
    bool check = true;
    //ищем максимальное кол-во изданий в городе
    for (int i = 0; i < booksCount; ++i) {
        cnt = 0;
        for (int j = 0; j < booksCount; ++j) {
            check = true;
            for (int k = 0; k < j; ++k) {
                if (books[k].publish.name == books[j].publish.name && books[k].publish.city == books[j].publish.city) {
                    check = false;
                    break;
                }
            }
            
            if (check && books[j].publish.city == books[i].publish.city) {
                ++cnt;
            }
        }

        if (cnt > mx) {
            mx = cnt;
        }
    }

    //выводим ответ
    for (int i = 0; i < booksCount; ++i) {
        cnt = 0;
        for (int j = 0; j < booksCount; ++j) {
            check = true;
            for (int k = 0; k < j; ++k) {
                if (books[k].publish.name == books[j].publish.name && books[k].publish.city == books[j].publish.city) {
                    check = false;
                    break;
                }
            }

            if (check && books[j].publish.city == books[i].publish.city) {
                ++cnt;
            }
        }

        check = true;
        for (int j = 0; j < i; ++j) {
            if (books[j].publish.city == books[i].publish.city) {
                check = false;
                break;
            }
        }
        if (check && cnt == mx) {
            cout << books[i].publish.city << '\n';
        }
    }
    cout << "Конец списка.\n";
//  ________________________________________________________________  



//8.________________________________________________________________
    printf("\nПоиск книг, имеющих объем более 100 стр. и изданных в указанном городе...\n");
    string city;
    cout << "Введите город: "; 
    cin.get();
    getline(cin, city);

    printf("Список книг:\n");
    //выводим ответ
    for (int i = 0; i < booksCount; ++i) {

        check = true; //проверяем что эту книгу еще не выводили
        for (int j = 0; j < i; ++j) {
            if (books[i].name == books[j].name && books[j].publish.city == books[i].publish.city && books[i].pages == books[j].pages) {
                check = false;
                break;
            }
        }

        if (check && books[i].publish.city == city && books[i].pages > 100) {
            cout << '\t' << books[i].name << '\n';
        }
    }
    cout << "Конец списка.\n";
//  ________________________________________________________________  







//9.________________________________________________________________
    printf("\nСписок городов, где издаются книги, стоимость которых менее 200 р. при объеме более 100 стр: \n");

    printf("Список городов:\n");
    //выводим ответ
    for (int i = 0; i < booksCount; ++i) {

        check = true; //проверяем что эту книгу еще не выводили
        for (int j = 0; j < i; ++j) {
            if (books[i].publish.city == books[j].publish.city && books[j].price < 200 && books[j].pages > 100) {
                check = false;
                break;
            }
        }

        if (check && books[i].price < 200 && books[i].pages > 100) {
            cout << '\t' << books[i].publish.city << '\n';
        }
    }
    cout << "Конец списка.\n";
//  ________________________________________________________________  





//10.________________________________________________________________
    printf("\nПоиск книг, c самой низкой ценой, написанных указанным автором...\n");
    string author;
    cout << "Введите автора: ";
    getline(cin, author);
    //printf("|%s|", author.c_str());
    mn = -1;
    //ищем самую низкую цену
    for (int i = 0; i < booksCount; ++i) {
        if (books[i].author == author && (books[i].price < mn || mn == -1)) {
            mn = books[i].price;
        }
    }

    printf("Список книг:\n");
    //выводим ответ
    for (int i = 0; i < booksCount; ++i) {

        check = true; //проверяем что эту книгу еще не выводили
        for (int j = 0; j < i; ++j) {
            if (books[i].name == books[j].name && books[j].author == books[i].author && books[j].price == books[i].price) {
                check = false;
                break;
            }
        }

        if (check && books[i].author == author && books[i].price == mn) {
            cout << '\t' << books[i].name << '\n';
        }
    }
    cout << "Конец списка.\n";
//  ________________________________________________________________  
}
