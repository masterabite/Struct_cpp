#include <iostream>
#include <string>

using namespace std;

//структура даты
class date {
public:
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

private:
    int day, month, year; //день месяц год
};

//структура паспорта
class owner {
public:

    //функции вывода в консоль
    void print() {
        printf("%s %s", surname.c_str(), name.c_str());
    }
    void println() {
        print(); printf("\n");
    }

    //функция для считывания данные паспорта с консоли
    void scan() {
        cout << "Введите фамилию и имя через пробел: ";
        cin >> surname >> name;
    }

private:
    string name;        //имя
    string surname;     //фамилия
};

//структура операции
class operation {
public:
    operation() {
        type = -1;
        sum = 0;
    }

    operation(int _sum) {
        type = _sum >= 0;
        sum = abs(_sum);
    }

    void print() {
        if (type < 0) {
            printf("Нет операций");
        }
        else {
            printf((type ? "Пополнение: +%.2lf руб." : "Снятие: -%.2lf руб."), sum);
        }
    }

    void println() {
        print(); printf("\n");
    }

    //функция возвращает численное представление операции 
    //если число отрицательное- снятие, наоборот- пополнение
    long double get_change() {
        return (type? sum: -sum);
    }

private:
    int type;          //тип операции: true- пополнение, false- снятие
    long double sum;    //сумма операции

};

//структура книги
class bank_account {
public:
    //функция для считывания данные паспорта с консоли
    void scan() {
        cout << "Создание банковского счета...\n";
        cout << "\tВвод даты...\n\t\t"; m_date.scan();
        cout << "\tВвод Владельца...\n\t\t"; m_owner.scan();
        cout << "\tВведите сумму: "; cin >> sum;
        last_op = {};
    }

    //вывод последней операции
    void print_last_op() {
        printf("Последняя операция:\t");
        last_op.println();
    }

    //функции вывода в консоль
    void print() {
        printf("Информация о банковском счете:\n");
        printf("\tВладелец:\t\t");
        m_owner.println();
        printf("\tДата создания:\t\t");
        m_date.println();
        printf("\tДоступно:\t\t%.2lf руб.\n\t", sum);
        print_last_op();
    }
    void println() {
        print(); printf("\n");
    }

    //функция пытается совершить операцию
    void do_op(operation op) {
        if (sum + op.get_change() < 0) {
            cout << "Ошибка: на счете недостаточно средств.\n";
        }
        else {
            sum += op.get_change();
            cout << "Операция совершена успешно.\n";
        }
        last_op = op;
    }

private:
    owner m_owner;          //владелец счета
    date m_date;            //дата создания счета
    long double sum;        //сумма
    operation last_op;      //последняя операция
};

int main() {
    setlocale(LC_ALL, "Russian");
    int cmd;
    long double temp_sum;

    bank_account ba;    //создаем банковский счет
    ba.scan();          //считываем информацию

    while (true) {
        printf("\n0- Выход из программы;\n");
        printf("1- Внести;\n");
        printf("2- Снять;\n");
        printf("3- Последняя операция;\n");
        printf("4- Вся информация о счете;\n");
        printf("Введите команду: "); cin >> cmd;

        if (cmd == 0) { break; }
        else if (cmd == 1) {
            cout << "Введите сумму: "; cin >> temp_sum;
            ba.do_op(abs(temp_sum));
        }
        else if (cmd == 2) {
            cout << "Введите сумму: "; cin >> temp_sum;
            ba.do_op(-abs(temp_sum));
        }
        else if (cmd == 3) {
            ba.print_last_op();
            printf("\n");
        }
        else if (cmd == 4) {
            ba.println();
        }
        else {
            cout << "Команда не найдена...\n";
        }
    }
    cin >> cmd;
}
