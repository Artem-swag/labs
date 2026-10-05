#include "task.h"
#include <iostream>
#include <limits>


long long Nod(long long a, long long b) { //Наибольший общий делитель
    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}


void Sokr(long long& a, long long& b) { // Сокращение дроби
    if (b < 0) {
        a = -a;
        b = -b;
    }
    long long g = Nod(a, b);
    if (g != 0) {
        a /= g;
        b /= g;
    }
}


void Summ(long long a, long long b, //Сумма двух дробей
    long long c, long long d,
    long long& e, long long& f) {
    e = a * d + c * b;
    f = b * d;
    Sokr(e, f);
}


void Mult(long long a, long long b, //Умножение двух дробей
    long long c, long long d,
    long long& e, long long& f) {
    e = a * c;
    f = b * d;
    Sokr(e, f);
}


void Input(long long& a, long long& b, const char* name) {
    using namespace std;

    while (true) {
        cout << "Введите " << name << " (числитель знаменатель): ";
        cin >> a >> b;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите два целых числа.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (b == 0) {
            cout << "Ошибка! Знаменатель не может быть 0.\n";
            continue;
        }
        Sokr(a, b);
        return;
    }
}


void Print(long long a, long long b) {
    using namespace std;

    if (b == 1) {
        cout << a;
    }
    else {
        cout << a << "/" << b;
    }
}