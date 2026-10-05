#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "task.h"


int InputIntInRange(const char* prompt, int lo, int hi) {
    using namespace std;


    int v = 0;
    while (true) {
        cout << prompt;
        cin >> v;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка! Введите целое число.\n";
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (v >= lo && v <= hi) return v;
            cout << "Ошибка! Число должно быть в диапазоне [" << lo << ", " << hi << "].\n";
        }
    }
}


void Task6() {
    using namespace std;


    cout << "\n Задача 6: Вычисление (a/b + c/d + k/m) * e/f \n";


    long long a = 0, b = 1;  
    long long c = 0, d = 1;   
    long long k = 0, m = 1;   
    long long p = 0, q = 1;   


    int choice = InputIntInRange("Способ ввода (1 - ручной, 2 - случайный, 3 - из файла): ", 1, 3);


    switch (choice) {
    case 1:
        cout << "\nВыражение: (a/b + c/d + k/m) * e/f\n";
        Input(a, b, "a/b");
        Input(c, d, "c/d");
        Input(k, m, "k/m");
        Input(p, q, "e/f");
        break;

    case 2:
        srand(static_cast<unsigned>(time(0)));
        a = rand() % 19 - 9; b = rand() % 9 + 1;
        c = rand() % 19 - 9; d = rand() % 9 + 1;
        k = rand() % 19 - 9; m = rand() % 9 + 1;
        p = rand() % 19 - 9; q = rand() % 9 + 1;
        Sokr(a, b);
        Sokr(c, d);
        Sokr(k, m);
        Sokr(p, q);
        cout << "\nСгенерированные дроби:\n";
        cout << "a/b = "; Print(a, b); cout << "\n";
        cout << "c/d = "; Print(c, d); cout << "\n";
        cout << "k/m = "; Print(k, m); cout << "\n";
        cout << "e/f = "; Print(p, q); cout << "\n";
        break;

    case 3: {
        ifstream file("task6_input.txt");
        if (!file) {
            cout << "Ошибка открытия файла task6_input.txt!\n";
            return;
        }
        if (!(file >> a >> b >> c >> d >> k >> m >> p >> q)) {
            cout << "Ошибка чтения данных из файла!\n";
            file.close();
            return;
        }
        file.close();
        if (b == 0 || d == 0 || m == 0 || q == 0) {
            cout << "Ошибка! Один из знаменателей равен 0.\n";
            return;
        }
        Sokr(a, b);
        Sokr(c, d);
        Sokr(k, m);
        Sokr(p, q);
        cout << "\nДроби из файла:\n";
        cout << "a/b = "; Print(a, b); cout << "\n";
        cout << "c/d = "; Print(c, d); cout << "\n";
        cout << "k/m = "; Print(k, m); cout << "\n";
        cout << "e/f = "; Print(p, q); cout << "\n";
        break;
    }
    default:
        cout << "Неверный выбор!\n";
        return;
    }


    cout << "\n Пошаговое вычисление \n";


    long long s = 0, t = 1;
    Summ(a, b, c, d, s, t);
    cout << "a/b + c/d = "; Print(s, t); cout << "\n";


    long long u = 0, v = 1;
    Summ(s, t, k, m, u, v);
    cout << "a/b + c/d + k/m = "; Print(u, v); cout << "\n";


    long long r = 0, w = 1;
    Mult(u, v, p, q, r, w);
    cout << "(a/b + c/d + k/m) * e/f = "; Print(r, w); cout << "\n";


    double dec = static_cast<double>(r) / w;
    cout << "Десятичное значение: " << dec << "\n";


    if (w == 1) {
        cout << "Результат — целое число.\n";
    }
}


int main() {
    using namespace std;


    setlocale(LC_ALL, "Russian");


    int choice = 0;


    do {
        cout << "            ЗАДАЧА 6: ДРОБИ\n";
        cout << " 1 - Вычислить (a/b + c/d + k/m) * e/f\n";
        cout << " 0 - Выход\n";


        choice = InputIntInRange("Выберите действие: ", 0, 1);


        switch (choice) {
        case 1: Task6(); break;
        case 0: cout << "Выход из программы.\n"; break;
        }
    } while (choice != 0);
     

    return 0;
}