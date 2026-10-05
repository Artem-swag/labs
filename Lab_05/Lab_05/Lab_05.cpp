#include "tasks.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <clocale>
#ifdef _WIN32
#include <windows.h>
#endif


std::string readAll(const std::string& name) { 
    std::ifstream f(name);
    std::string s, line;
    while (std::getline(f, line)) s += line + "\n";
    return s;
}


std::string randomString(int len, const std::string& chars) {
    std::string r;
    for (int i = 0; i < len; ++i) r += chars[rand() % chars.size()];
    return r;
}


std::string inputByChoice(int sampleLen, const std::string& sampleChars) {
    std::cout << "1 - вручную, 2 - случайно, 3 - из файла\n";
    int m = askRange("Способ: ", 1, 3);

    if (m == 1) return askLine("Введите строку: ");
    if (m == 2) {
        std::string s = randomString(sampleLen, sampleChars);
        std::cout << "Строка: \"" << s << "\"\n";
        return s;
    }
    return readAll(askFile("Файл: "));
}


void task1() {
    std::cout << "\n Задача 1: Подсчёт слов \n";
    std::string s = inputByChoice(40, "abcdefghij ");
    std::cout << "Слов: " << countWords(s) << "\n";
}

void task2() {
    std::cout << "\n Задача 2: Замена < и > \n";
    std::string s = inputByChoice(30, "abc<>xyz<>");
    std::cout << "Результат: " << replaceBrackets(s) << "\n";
}

void task3() {
    std::cout << "\n Задача 3: Тип символа \n";
    std::cout << "1 - вручную, 2 - случайно\n";
    int m = askRange("Способ: ", 1, 2);

    char c;
    if (m == 1) {
        c = askChar("Символ: ");
    }
    else {
        std::string pool = "aZ7!<> #яЯ";
        c = pool[rand() % pool.size()];
        std::cout << "Символ: '" << c << "'\n";
    }

    std::cout << "1. Буква:        " << (isLetter(c) ? "True" : "False") << "\n";
    std::cout << "2. Цифра:        " << (isDigit(c) ? "True" : "False") << "\n";
    std::cout << "3. Строчная:     " << (isLower(c) ? "True" : "False") << "\n";
    std::cout << "4. Прописная:    " << (isUpper(c) ? "True" : "False") << "\n";
    std::cout << "5. Символ 0..32: " << (isControl(c) ? "True" : "False") << "\n";
}

void task4() {
    std::cout << "\n Задача 4: Различные символы \n";
    std::string s = inputByChoice(50, "abcABC123!@#abcABC");
    std::cout << "Различных символов: " << countUnique(s) << "\n";
}

void task5() {
    std::cout << "\n Задача 5: Двоичное число \n";
    std::cout << "1 - вручную, 2 - случайно, 3 - из файла\n";
    int m = askRange("Способ: ", 1, 3);

    std::string s;
    if (m == 1) {
        s = askLine("Введите двоичное число: ");
    }
    else if (m == 2) {
        s = randomString(8, "01");
        std::cout << "Число: " << s << "\n";
    }
    else {
        std::ifstream f(askFile("Файл: "));
        std::getline(f, s);
        while (!s.empty() && (s.back() == '\n' || s.back() == '\r' || s.back() == ' '))
            s.pop_back();
    }

    if (!isBinary(s)) std::cout << "False\n";
    else              std::cout << "Десятичное: " << toDecimal(s) << "\n";
}

void task6() {
    std::cout << "\n Задача 6: Генератор паролей \n";
    std::cout << "  1 - лёгкий  (6 символов)\n";
    std::cout << "  2 - средний (10 символов)\n";
    std::cout << "  3 - сложный (16 символов)\n";

    int level = askRange("Уровень: ", 1, 3);

    while (true) {
        std::cout << "Пароль: " << makePassword(level) << "\n";
        std::cout << "Ещё? (y/n): ";
        std::string s;
        std::getline(std::cin, s);
        if (s.empty() || (s[0] != 'y' && s[0] != 'Y')) break;
    }
}

void task7() {
    std::cout << "\n Задача 7: Проверка домашки \n";
    std::string in = askFile("Входной файл:  ");
    std::string out = askLine("Выходной файл: ");
    checkHomework(in, out);
}


int main() {
#ifdef _WIN32
    system("chcp 1251 > nul");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    setlocale(LC_ALL, "Russian");
    srand((unsigned)time(nullptr));



    setlocale(LC_ALL, "Russian");
    srand((unsigned)time(nullptr));


    while (true) {;
        std::cout << "                ГЛАВНОЕ МЕНЮ\n";
        std::cout << " 1. Подсчёт слов\n";
        std::cout << " 2. Замена < и >\n";
        std::cout << " 3. Тип символа\n";
        std::cout << " 4. Различные символы\n";
        std::cout << " 5. Двоичное число\n";
        std::cout << " 6. Генератор паролей\n";
        std::cout << " 7. Проверка домашки\n";
        std::cout << " 0. Выход\n";


        int choice = askRange("Ваш выбор: ", 0, 7);


        switch (choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 5: task5(); break;
        case 6: task6(); break;
        case 7: task7(); break;
        case 0: std::cout << "До свидания!\n"; return 0;
        }
    }
}