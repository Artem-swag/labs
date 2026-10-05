#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <string>
#include <cmath>
#include <windows.h>
#include "tasks.h"


void Task1() {
    using namespace std;


    cout << "\n Задача 1: Подсчет степеней числа N \n";


    int N = 0;
    while (true) {
        N = InputInt("Введите N (> 1): ");
        if (N > 1) break;
        cout << "Ошибка! N должно быть больше 1.\n";
    }


    int numbers[10] = {};
    int choice = InputIntInRange("Выберите способ ввода (1 - ручной, 2 - случайный, 3 - из файла): ", 1, 3);


    switch (choice) {
    case 1: //Ручной ввод
        cout << "Введите 10 целых положительных чисел:\n";
        for (int i = 0; i < 10; i++) {
            while (true) {
                numbers[i] = InputInt(("Число " + to_string(i + 1) + ": ").c_str());
                if (numbers[i] > 0) break;
                cout << "Ошибка! Число должно быть положительным.\n";
            }
        }
        break;

    case 2: //Случайная генерация
        srand(static_cast<unsigned>(time(0)));
        cout << "Сгенерированные числа: ";
        for (int i = 0; i < 10; i++) {
            numbers[i] = rand() % 100 + 1;
            cout << numbers[i] << " ";
        }
        cout << endl;
        break;

    case 3: //Чтение с файла
    {
        ifstream file("task1_input.txt");
        if (!file) {
            cout << "Ошибка открытия файла task1_input.txt!\n";
            return;
        }
        cout << "Числа из файла: ";
        for (int i = 0; i < 10; i++) {
            if (!(file >> numbers[i])) {
                cout << "\nОшибка чтения данных из файла!\n";
                file.close();
                return;
            }
            cout << numbers[i] << " ";
        }
        cout << endl;
        file.close();
        break;
    }
    default:
        cout << "Неверный выбор!\n";
        return;
    }


    int count = 0;
    for (int i = 0; i < 10; i++) {
        if (IsPowerN(numbers[i], N)) {
            count++;
            cout << numbers[i] << " является степенью " << N << endl;
        }
    }

    cout << "Количество степеней числа " << N << ": " << count << endl;
}


void Task2() {
    using namespace std;


    cout << "\n Задача 2: Левый циклический сдвиг \n";


    double A1 = 0.0, B1 = 0.0, C1 = 0.0;
    double A2 = 0.0, B2 = 0.0, C2 = 0.0;
    int choice = InputIntInRange("Выберите способ ввода (1 - ручной, 2 - случайный, 3 - из файла): ", 1, 3);


    switch (choice) {
    case 1:
        A1 = InputDouble("Введите A1: ");
        B1 = InputDouble("Введите B1: ");
        C1 = InputDouble("Введите C1: ");
        A2 = InputDouble("Введите A2: ");
        B2 = InputDouble("Введите B2: ");
        C2 = InputDouble("Введите C2: ");
        break;

    case 2:
        srand(static_cast<unsigned>(time(0)));
        A1 = (rand() % 1000) / 10.0;
        B1 = (rand() % 1000) / 10.0;
        C1 = (rand() % 1000) / 10.0;
        A2 = (rand() % 1000) / 10.0;
        B2 = (rand() % 1000) / 10.0;
        C2 = (rand() % 1000) / 10.0;
        cout << "Первый набор: " << A1 << " " << B1 << " " << C1 << endl;
        cout << "Второй набор: " << A2 << " " << B2 << " " << C2 << endl;
        break;

    case 3: {
        ifstream file("task2_input.txt");
        if (!file) {
            cout << "Ошибка открытия файла task2_input.txt!\n";
            return;
        }
        if (!(file >> A1 >> B1 >> C1 >> A2 >> B2 >> C2)) {
            cout << "Ошибка чтения данных из файла!\n";
            file.close();
            return;
        }
        file.close();
        cout << "Первый набор: " << A1 << " " << B1 << " " << C1 << endl;
        cout << "Второй набор: " << A2 << " " << B2 << " " << C2 << endl;
        break;
    }
    default:
        cout << "Неверный выбор!\n";
        return;
    }


    cout << "\nДо сдвига:\n";
    cout << "Набор 1: (" << A1 << ", " << B1 << ", " << C1 << ")\n";
    cout << "Набор 2: (" << A2 << ", " << B2 << ", " << C2 << ")\n";


    ShiftLeft3(A1, B1, C1);
    ShiftLeft3(A2, B2, C2);


    cout << "\nПосле сдвига:\n";
    cout << "Набор 1: (" << A1 << ", " << B1 << ", " << C1 << ")\n";
    cout << "Набор 2: (" << A2 << ", " << B2 << ", " << C2 << ")\n";
}


void Task3() {
    using namespace std;


    cout << "\n Задача 3: Вычисление ln(1+x) \n";


    double x = 0.0;
    double epsilons[6] = {};
    int choice = InputIntInRange("Выберите способ ввода (1 - ручной, 2 - случайный, 3 - из файла): ", 1, 3);


    switch (choice) {
    case 1:
        while (true) {
            x = InputDouble("Введите x (|x| < 1): ");
            if (abs(x) < 1) break;
            cout << "Ошибка! |x| должен быть меньше 1.\n";
        }
        cout << "Введите 6 значений eps (каждое > 0):\n";
        for (int i = 0; i < 6; i++) {
            while (true) {
                epsilons[i] = InputDouble(("eps[" + to_string(i + 1) + "]: ").c_str());
                if (epsilons[i] > 0) break;
                cout << "Ошибка! eps должно быть > 0.\n";
            }
        }
        break;

    case 2:
        srand(static_cast<unsigned>(time(0)));
        x = (rand() % 180 - 90) / 100.0;
        cout << "x = " << x << endl;
        cout << "Epsilon: ";
        for (int i = 0; i < 6; i++) {
            epsilons[i] = 1.0 / (i + 2);
            cout << epsilons[i] << " ";
        }
        cout << endl;
        break;

    case 3: {
        ifstream file("task3_input.txt");
        if (!file) {
            cout << "Ошибка открытия файла task3_input.txt!\n";
            return;
        }
        if (!(file >> x)) {
            cout << "Ошибка чтения x из файла!\n";
            file.close();
            return;
        }
        for (int i = 0; i < 6; i++) {
            if (!(file >> epsilons[i])) {
                cout << "Ошибка чтения eps из файла!\n";
                file.close();
                return;
            }
        }
        file.close();
        cout << "x = " << x << endl;
        cout << "Epsilon: ";
        for (int i = 0; i < 6; i++) {
            cout << epsilons[i] << " ";
        }
        cout << endl;
        break;
    }
    default:
        cout << "Неверный выбор!\n";
        return;
    }


    if (abs(x) >= 1) {
        cout << "Ошибка: |x| должен быть < 1\n";
        return;
    }


    cout << fixed << setprecision(6);
    for (int i = 0; i < 6; i++) {
        if (epsilons[i] <= 0) {
            cout << "eps = " << epsilons[i] << ": пропущено (eps должно быть > 0)\n";
            continue;
        }
        double result = Ln1(x, epsilons[i]);
        cout << "eps = " << epsilons[i] << ": ln(1+" << x << ") ~= " << result << endl;
    }
}


void Task4() {
    using namespace std;


    cout << "\n Задача 4: Перевод в десятичную систему \n";


    int P = 0;
    long long X = 0;
    int choice = InputIntInRange("Выберите способ ввода (1 - ручной, 2 - случайный, 3 - из файла): ", 1, 3);


    switch (choice) {
    case 1:
        P = InputIntInRange("Введите основание P (2-9): ", 2, 9);
        X = InputLongLong("Введите число X: ");
        break;

    case 2:
        srand(static_cast<unsigned>(time(0)));
        P = rand() % 8 + 2;
        X = 0;
        {
            int digitsCount = rand() % 4 + 1;
            for (int i = 0; i < digitsCount; i++) {
                int digit = (i == 0) ? (rand() % (P - 1) + 1) : (rand() % P);
                X = X * 10 + digit;
            }
        }
        cout << "P = " << P << ", X = " << X << endl;
        break;

    case 3: {
        ifstream file("task4_input.txt");
        if (!file) {
            cout << "Ошибка открытия файла task4_input.txt!\n";
            return;
        }
        if (!(file >> P >> X)) {
            cout << "Ошибка чтения данных из файла!\n";
            file.close();
            return;
        }
        file.close();
        cout << "P = " << P << ", X = " << X << endl;
        break;
    }
    default:
        cout << "Неверный выбор!\n";
        return;
    }

    if (P < 2 || P > 9) {
        cout << "Ошибка: P должно быть от 2 до 9\n";
        return;
    }

    if (X < 0) {
        cout << "Ошибка: X должно быть неотрицательным\n";
        return;
    }

    {
        long long temp = X;
        while (temp > 0) {
            int digit = static_cast<int>(temp % 10);
            if (digit >= P) {
                cout << "Ошибка! Цифра " << digit << " недопустима для основания " << P << ".\n";
                return;
            }
            temp /= 10;
        }
    }


    int result = FromBasePToDecimal(X, P);
    cout << "Число " << X << " в системе с основанием " << P
        << " = " << result << " в десятичной системе\n";
}


void Task5() {
    using namespace std;


    cout << "\n Задача 5: Рекурсивная сумма \n";


    int N = 0;
    double x = 0.0;
    int choice = InputIntInRange("Выберите способ ввода (1 - ручной, 2 - случайный, 3 - из файла): ", 1, 3);


    switch (choice) {
    case 1:
        x = InputDouble("Введите x: ");
        N = InputIntInRange("Введите N (< 20): ", 1, 19);
        break;

    case 2:
        srand(static_cast<unsigned>(time(0)));
        x = (rand() % 200 - 100) / 100.0;
        N = rand() % 19 + 1;
        cout << "x = " << x << ", N = " << N << endl;
        break;

    case 3: {
        ifstream file("task5_input.txt");
        if (!file) {
            cout << "Ошибка открытия файла task5_input.txt!\n";
            return;
        }
        if (!(file >> x >> N)) {
            cout << "Ошибка чтения данных из файла!\n";
            file.close();
            return;
        }
        file.close();
        cout << "x = " << x << ", N = " << N << endl;
        break;
    }
    default:
        cout << "Неверный выбор!\n";
        return;
    }

    if (N <= 0 || N >= 20) {
        cout << "Ошибка: N должно быть натуральным числом < 20\n";
        return;
    }


    double S = SumOddPowers(x, N);
    cout << fixed << setprecision(4);
    cout << "Сумма первых " << N << " членов: S = " << S << endl;
}


int main() {
    using namespace std;


#ifdef _WIN32
    system("chcp 1251 > nul");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    setlocale(LC_ALL, "Russian");


    int choice = 0;


    do {
        cout << "              ГЛАВНОЕ МЕНЮ\n";
        cout << " 1 - Задача 1 (Степени числа N)\n";
        cout << " 2 - Задача 2 (Циклический сдвиг)\n";
        cout << " 3 - Задача 3 (ln(1+x))\n";
        cout << " 4 - Задача 4 (Перевод систем счисления)\n";
        cout << " 5 - Задача 5 (Рекурсивная сумма)\n";
        cout << " 0 - Выход\n";

        choice = InputIntInRange("Выберите задачу: ", 0, 5);

        switch (choice) {
        case 1: Task1(); break;
        case 2: Task2(); break;
        case 3: Task3(); break;
        case 4: Task4(); break;
        case 5: Task5(); break;
        case 0: cout << "Выход из программы.\n"; break;
        }
    } while (choice != 0);


    return 0;
}