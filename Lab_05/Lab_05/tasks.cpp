#include "tasks.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>



int countWords(const std::string& s) { //Подсчёт слов в строке
    int n = 0;
    bool inWord = false;
    for (char c : s) {
        if (c != ' ' && c != '\t' && !inWord) { ++n; inWord = true; }
        else if (c == ' ' || c == '\t')       inWord = false;
    }
    return n;
}


std::string replaceBrackets(const std::string& s) { //Замена символов в строке
    std::string r;
    for (char c : s) {
        if (c == '<')      r += "begin";
        else if (c == '>') r += "end";
        else               r += c;
    }
    return r;
}


bool isLetter(char c) { //Проверка символов
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я') ||
        c == 'ё' || c == 'Ё';
}
bool isDigit(char c) { return c >= '0' && c <= '9'; }
bool isLower(char c) { return (c >= 'a' && c <= 'z') || (c >= 'а' && c <= 'я') || c == 'ё'; }
bool isUpper(char c) { return (c >= 'A' && c <= 'Z') || (c >= 'А' && c <= 'Я') || c == 'Ё'; }
bool isControl(char c) { return static_cast<unsigned char>(c) <= 32; }


int countUnique(const std::string& s) { //Подсчёт уникальных символов в строке
    bool seen[256] = { false };
    int n = 0;
    for (unsigned char c : s) {
        if (c <= 32) continue;
        if (c == '.' || c == ',' || c == '!' || c == '?' ||
            c == ';' || c == ':' || c == '-' || c == '"' ||
            c == '\'' || c == '(' || c == ')' || c == '/' ||
            c == '\\' || c == '[' || c == ']' || c == '{' ||
            c == '}' || c == '<' || c == '>' || c == '|' ||
            c == '@' || c == '#' || c == '$' || c == '%' ||
            c == '^' || c == '&' || c == '*' || c == '+' ||
            c == '=' || c == '~' || c == '`')
            continue;
        if (!seen[c]) { seen[c] = true; ++n; }
    }
    return n;
}


bool isBinary(const std::string& s) { //Проверка, двоичное ли число
    if (s.empty()) return false;
    for (char c : s) if (c != '0' && c != '1') return false;
    return true;
}
long long toDecimal(const std::string& s) { //Перевод в десятичную с.ч.
    long long r = 0;
    for (char c : s) r = r * 2 + (c - '0');
    return r;
}


std::string makePassword(int level) { //Генерация пароля
    static bool seeded = false;
    if (!seeded) { srand((unsigned)time(nullptr)); seeded = true; }

    std::string chars;
    int len = 0;

    if (level == 1) {
        chars = "abcdefghijklmnopqrstuvwxyz0123456789";
        len = 6;
    }
    else if (level == 2) {
        chars = "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "0123456789";
        len = 10;
    }
    else if (level == 3) {
        chars = "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "0123456789"
            "!@#$%^&*()-_=+";
        len = 16;
    }
    else {
        return "";
    }

    std::string p;
    for (int i = 0; i < len; ++i) p += chars[rand() % chars.size()];
    return p;
}


void checkHomework(const std::string& inFile, const std::string& outFile) { //Чтение и разбор строки, сравнение с ответом
    std::ifstream fin(inFile);
    if (!fin.is_open()) {
        std::cout << "Ошибка: не открыть " << inFile << "\n";
        return;
    }
    std::ofstream fout(outFile);
    if (!fout.is_open()) {
        std::cout << "Ошибка: не создать " << outFile << "\n";
        return;
    }

    std::string line;
    int total = 0, correct = 0;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        int a, b, ans;
        char op, eq;
        std::istringstream iss(line);
        iss >> a >> op >> b >> eq >> ans;

        if (iss.fail() || eq != '=' || (op != '+' && op != '-')) {
            fout << line << " -\n";
            ++total;
            continue;
        }

        int right = (op == '+') ? a + b : a - b;
        fout << line << (right == ans ? " +" : " -") << "\n";
        ++total;
        if (right == ans) ++correct;
    }
    std::cout << "Примеров: " << total << ", правильных: " << correct << "\n";
}


//Дальше проверки и очистка


void clear() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


int askInt(const std::string& prompt) {
    int v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v) { clear(); return v; }
        std::cout << "Ошибка: нужно целое число.\n";
        clear();
    }
}


int askRange(const std::string& prompt, int lo, int hi) {
    while (true) {
        int v = askInt(prompt);
        if (v >= lo && v <= hi) return v;
        std::cout << "Ошибка: допустимо от " << lo << " до " << hi << ".\n";
    }
}


std::string askLine(const std::string& prompt) {
    std::string s;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, s);
        if (!s.empty()) return s;
        std::cout << "Ошибка: строка пустая.\n";
    }
}


char askChar(const std::string& prompt) {
    return askLine(prompt)[0];
}


std::string askFile(const std::string& prompt) {
    std::string name;
    while (true) {
        name = askLine(prompt);
        std::ifstream f(name);
        if (f.is_open()) return name;
        std::cout << "Ошибка: файл \"" << name << "\" не открывается.\n";
    }
}