#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <string.h>

//функция считывает строку с клавиатуры (включая пробелы)
void scan_line(char* str) {
    char c = '\n';
    int len = 0;
    while (c == '\n') {
        c = getc(stdin);
    }

    while (c != '\n') {
        str[len++] = c;
        c = getc(stdin);
    }
    str[len] = '\0'; //обозначаем конец строки
}

//структура струдента
struct student {
    char fullname[72];  //ФИО
    char addr[72];      //адрес    
    char group[10];     //группа
    int rank;           //рейтинг
} students[100];
int studentsCount = 0; //общее кол-во студентов

//функция считывает с клавиатуры информацию о i-ом студенте 
void scan_student(int i) {
    printf("\nВвод информации о %d-м студенте...\n", i+1);
    printf("\tВведите ФИО: "); scan_line(students[i].fullname);
    printf("\tВведите домашний адрес: "); scan_line(students[i].addr);
    printf("\tВведите группу: "); scan_line(students[i].group);
    printf("\tВведите рейтинг: "); scanf("%d", &students[i].rank);
}

//функция считывает информацию о студенте и добавляет его в конец массива
void add_student() {
    scan_student(studentsCount++);
}

//функция ищет студента по ФИО
int find_student(char* fname) {
    for (int i = 0; i < studentsCount; ++i) {
        if (strcmp(students[i].fullname, fname) == 0) { //если совпадают ФИО поиска и ФИО i-ого студента
            return i;
        }
    }
    return -1; //если не нашли студента возвращаем отрицательный индекс
}

//функция меняет местами двух студентов с соответствующими индексами
void swap_student(int i1, int i2) {
    struct student* si = &students[i1];
    struct student* sl = &students[i2];
    struct student temp = *si;
    *si = *sl;
    *sl = temp;
}

//Функция удаления студента из массива
void erase_student(int i) {
    swap_student(i, studentsCount - 1);
    --studentsCount;
}

//функция сортирует массив по рейтингу студентов
void sort_students_rank() {
    for (int i = 0; i < studentsCount - 1; ++i) {
        for (int j = i + 1; j < studentsCount; ++j) {
            if (students[i].rank < students[j].rank) {
                swap_student(i, j);
            }
        }
    }
}

void print_student(int i) {
    printf("\n\tИнформация о %d-м студенте:\n", i+1);
    printf("\tФИО:\t %s\n", students[i].fullname);
    printf("\tАдрес:\t %s\n", students[i].addr);
    printf("\tГруппа:\t %s\n", students[i].group);
    printf("\tРейтинг: %d\n", students[i].rank);
}

void print_students() {
    printf("\nИнформация о всех студентах:\n");
    for (int i = 0; i < studentsCount; ++i) {
        print_student(i);
    }
}


int main() {
    setlocale(LC_ALL, "Russian");

    int cmd = 1; //команды для ввода

    //начальный ввод структур
    while (cmd) {
        add_student();
        printf("(1-продолжить/0-закончить) Введите 1 или 0: ");
        scanf("%d", &cmd);
    }

    while (true) {
        printf("\n0- Выход из программы\n");
        printf("1- добавление нового студента\n");
        printf("2- сортировка студентов по рейтингу\n");
        printf("3- поиск студента по ФИО\n");
        printf("4- Удаление студента по ФИО\n");
        printf("5- показать всех студентов\n");
        printf("Введите команду: "); scanf("%d", &cmd);

        if (cmd == 0) { break; }
        else if (cmd == 1) {
            add_student();
        }
        else if (cmd == 2) {
            sort_students_rank();
            printf("\nМассив успешно отсортирован.\n");
        }
        else if (cmd == 3) {
            char temp[72];
            printf("\nВведите ФИО: "); scan_line(temp);
            int pos = find_student(temp); //ищем позицию студента
            if (pos != -1) {
                printf("Студент найден под номером %d:\n", pos+1);
                print_student(pos);
            }
            else {
                printf("Студент не найден.\n");
            }
        }
        else if (cmd == 4) {
            char temp[72];
            printf("\nВведите ФИО: "); scan_line(temp);
            int pos = find_student(temp); //ищем позицию студента
            if (pos != -1) {
                erase_student(pos);
                printf("Информация о студенте успешно удалена.\n");
            }
            else {
                printf("Студент не найден.\n");
            }
        }
        else if (cmd == 5) {
            print_students();
        }
        else {
            printf("\nКоманда не найдена...\n");
        }
    }
    return 0;
}
