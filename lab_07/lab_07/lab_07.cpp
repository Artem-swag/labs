#include "tasks.h"
#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    //setlocale(LC_ALL, "");

    int c = 0;
    do {
        std::cout << "\n МЕНЮ \n"
            << "1. Задача 1: сортировка простыми обменами\n"
            << "2. Задача 2: клиенты фитнес-центра\n"
            << "3. Задача 3: ученики (бинарные вставки)\n"
            << "0. Выход\n";
        c = askInt("Ваш выбор: ", 0, 3);
        switch (c) {
        case 1: t1_run(); break;
        case 2: t2_run(); break;
        case 3: t3_run(); break;
        case 0: std::cout << "До свидания!\n"; break;
        }
    } while (c != 0);
    return 0;
}