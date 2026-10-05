#include "tasks.h"
#include <cmath>
#include <iostream>
#include <limits>


bool IsPowerN(int K, int N) { //Проверка на степень
    if (K <= 0 || N <= 1) return false;
    if (K == 1) return true;

    while (K > 1) {
        if (K % N != 0) return false;
        K /= N;
    }
    return K == 1;
}


void ShiftLeft3(double& A, double& B, double& C) { //Сдвиг трёх чисел
    double temp = A;
    A = B;
    B = C;
    C = temp;
}


double Ln1(double x, double epsilon) { //Вычисление ряда чисел
    if (std::abs(x) >= 1) return 0;

    double sum = 0;
    double term = x;
    int n = 0;

    while (std::abs(term) > epsilon) {
        sum += term;
        n++;
        term = std::pow(-1, n) * std::pow(x, n + 1) / (n + 1);
    }

    return sum;
}


int FromBasePToDecimal(long long X, int P) { //Перевод в десятичную систему
    int result = 0;
    int power = 1;

    while (X > 0) {
        int d = X % 10;
        result += d * power;
        power *= P;
        X /= 10;
    }

    return result;
}


double SumOddPowers(double x, int N) { //Рекурсивный подсчёт суммы
    if (N == 0) return 0;

    double power = 1;
    for (int i = 0; i < 2 * N - 1; i++) {
        power *= x;
    }

    return power + SumOddPowers(x, N - 1);
}


//Дальше идут проверки


int InputInt(const char* prompt) {
    using std::cin;
    using std::cout;
    using std::numeric_limits;
    using std::streamsize;

    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите целое число.\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

int InputIntInRange(const char* prompt, int min, int max) {
    using std::cout;

    int value;
    while (true) {
        value = InputInt(prompt);
        if (value >= min && value <= max) {
            return value;
        }
        cout << "Ошибка! Число должно быть в диапазоне [" << min << ", " << max << "].\n";
    }
}

double InputDouble(const char* prompt) {
    using std::cin;
    using std::cout;
    using std::numeric_limits;
    using std::streamsize;

    double value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите число.\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

long long InputLongLong(const char* prompt) {
    using std::cin;
    using std::cout;
    using std::numeric_limits;
    using std::streamsize;

    long long value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите целое число.\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}