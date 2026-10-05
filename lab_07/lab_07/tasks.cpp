#include "tasks.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <map>
#include <limits>
#include <string>


//Проверки


int askInt(const std::string& prompt) {
    int x;
    while (true) {
        std::cout << prompt;
        if (std::cin >> x) return x;
        std::cout << "Ошибка: нужно целое число. Повторите.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int askInt(const std::string& prompt, int lo, int hi) {
    while (true) {
        int x = askInt(prompt);
        if (x >= lo && x <= hi) return x;
        std::cout << "Ошибка: значение должно быть в диапазоне ["
            << lo << "; " << hi << "]. Повторите.\n";
    }
}

void askLine(const std::string& prompt, std::string& out) {
    while (true) {
        std::cout << prompt;
        if (std::cin >> out && !out.empty()) return;
        std::cout << "Ошибка: пустая строка. Повторите.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

static bool askOpenOut(std::ofstream& f, const std::string& prompt) {
    while (true) {
        std::string fn;
        askLine(prompt, fn);
        f.open(fn.c_str());
        if (f.is_open()) return true;
        std::cout << "Не удалось открыть файл \"" << fn << "\". Повторите.\n";
        f.clear();
    }
}


std::vector<int> t1_man(int n) {
    std::vector<int> a(n);
    std::cout << "Введите " << n << " целых чисел:\n";
    for (int i = 0; i < n; ++i) {
        std::string p = "a[" + std::to_string(i) + "] = ";
        a[i] = askInt(p);
    }
    return a;
}

std::vector<int> t1_rnd(int n) {
    std::vector<int> a(n);
    std::srand(static_cast<unsigned>(std::time(NULL)));
    for (int i = 0; i < n; ++i) a[i] = std::rand() % 201 - 100;
    return a;
}

std::vector<int> t1_file(const std::string& fn, int& n) {
    std::ifstream f(fn.c_str());
    if (!f) { std::cout << "Не удалось открыть файл!\n"; n = 0; return std::vector<int>(); }
    f >> n;
    if (!f || n <= 0) {
        std::cout << "Некорректное содержимое файла\n";
        n = 0; return std::vector<int>();
    }
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (!(f >> a[i])) {
            std::cout << "Ошибка чтения элемента #" << i << "\n";
            n = 0; return std::vector<int>();
        }
    }
    return a;
}

std::string t1_fmt(const std::vector<int>& a, int k) {
    std::string s;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (i == k && k > 0 && k < (int)a.size()) s += " | ";
        else if (i > 0 && i != k) s += " ";
        s += std::to_string(a[i]);
    }
    return s;
}


void t1_run() { //Сортировка пузырьками
    int n = askInt("Введите N (>=1): ", 1, 100000);
    int c = askInt("Способ ввода: 1-ручной, 2-случайный, 3-из файла: ", 1, 3);

    std::vector<int> a;
    if (c == 1) a = t1_man(n);
    else if (c == 2) a = t1_rnd(n);
    else {
        std::string fn;
        while (true) {
            askLine("Имя входного файла: ", fn);
            std::ifstream test(fn.c_str());
            if (test.is_open()) { test.close(); break; }
            std::cout << "Не удалось открыть \"" << fn << "\". Повторите.\n";
        }
        int nn = n;
        a = t1_file(fn, nn);
        n = nn;
        if (n == 0) return;
    }


    std::cout << "Исходный массив: " << t1_fmt(a, 0) << "\n";


    std::ofstream f;
    if (!askOpenOut(f, "Имя файла протокола: ")) return;


    f << "Исходный массив: " << t1_fmt(a, 0) << "\n";


    int sorted = 0, iter = 1;
    while (sorted < n - 1) {
        int mx = sorted;
        for (int j = sorted + 1; j < n; ++j)
            if (a[j] > a[mx]) mx = j;
        for (int j = mx; j > sorted; --j) {
            int tmp = a[j];
            a[j] = a[j - 1];
            a[j - 1] = tmp;
        }
        ++sorted;
        f << "Итерация " << iter++ << ": " << t1_fmt(a, sorted) << "\n";
    }

    f << "Отсортированный массив:";
    for (int i = 0; i < n; ++i) f << " " << a[i];
    f << "\n";
    f.close();

    std::cout << "Протокол записан.\n";
    std::cout << "Отсортированный массив:";
    for (int i = 0; i < n; ++i) std::cout << " " << a[i];
    std::cout << "\n";
}



void t2_sort(Res* a, int n) { //Шейкер сортировка
    int left = 0, right = n - 1;
    bool swapped = true;
    while (swapped && left < right) {
        swapped = false;
        for (int j = left; j < right; ++j) {
            bool need = false;
            if (a[j].hours < a[j + 1].hours) need = true;
            else if (a[j].hours == a[j + 1].hours &&
                a[j].year > a[j + 1].year) need = true;
            if (need) {
                Res tmp = a[j]; a[j] = a[j + 1]; a[j + 1] = tmp;
                swapped = true;
            }
        }
        --right;
        for (int j = right; j > left; --j) {
            bool need = false;
            if (a[j - 1].hours < a[j].hours) need = true;
            else if (a[j - 1].hours == a[j].hours &&
                a[j - 1].year > a[j].year) need = true;
            if (need) {
                Res tmp = a[j - 1]; a[j - 1] = a[j]; a[j] = tmp;
                swapped = true;
            }
        }
        ++left;
    }
}


void t2_man(Rec* arr, int& n, int& K) { // Ручной ввод
    K = askInt("Введите код клиента K (10..99): ", 10, 99);
    n = askInt("Введите N (>=1): ", 1, 10000);
    std::cout << "Формат: <код 10..99> <часы 1..30> <год 2000..2010> <месяц 1..12>\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "Запись #" << (i + 1) << ":\n";
        arr[i].code = askInt("  код: ", 10, 99);
        arr[i].hours = askInt("  часы: ", 1, 30);
        arr[i].year = askInt("  год: ", 2000, 2010);
        arr[i].month = askInt("  месяц: ", 1, 12);
    }
}


void t2_rnd(Rec* arr, int& n, int& K) { // Случайная генерация
    std::srand(static_cast<unsigned>(std::time(NULL)));
    K = 10 + std::rand() % 90;
    n = 5 + std::rand() % 15;
    std::cout << "Сгенерирован K = " << K << ", N = " << n << "\n";
    for (int i = 0; i < n; ++i) {
        arr[i].code = 10 + std::rand() % 90;
        arr[i].hours = 1 + std::rand() % 30;
        arr[i].year = 2000 + std::rand() % 11;
        arr[i].month = 1 + std::rand() % 12;
    }
}


void t2_file(const std::string& fn, Rec* arr, int& n, int& K) { // Ввод из файла
    std::ifstream f(fn.c_str());
    if (!f) { std::cout << "Не удалось открыть файл\n"; n = 0; K = -1; return; }
    if (!(f >> K) || K < 10 || K > 99) {
        std::cout << "Некорректный код K в файле\n"; n = 0; K = -1; return;
    }
    if (!(f >> n) || n <= 0 || n > 10000) {
        std::cout << "Некорректное N в файле\n"; n = 0; K = -1; return;
    }
    for (int i = 0; i < n; ++i) {
        if (!(f >> arr[i].code >> arr[i].hours >> arr[i].year >> arr[i].month)) {
            std::cout << "Ошибка чтения записи #" << i << "\n";
            n = 0; K = -1; return;
        }
    }
}

void t2_run() {
    const int MAXN = 10000;
    Rec* data = new Rec[MAXN];
    int n = 0;
    int K = -1;

    int c = askInt("Способ ввода: 1-ручной, 2-случайный, 3-из файла: ", 1, 3);

    if (c == 1) t2_man(data, n, K);
    else if (c == 2) t2_rnd(data, n, K);
    else {
        std::string fn;
        while (true) {
            askLine("Имя входного файла: ", fn);
            std::ifstream test(fn.c_str());
            if (test.is_open()) { test.close(); break; }
            std::cout << "Не удалось открыть \"" << fn << "\". Повторите.\n";
        }
        t2_file(fn, data, n, K);
        if (K == -1) { delete[] data; return; }
    }

    
    const int MAXYEARS = 11; // Уникальные годы + максимум часов + месяц этого максимума.
    int years[MAXYEARS];
    int maxHours[MAXYEARS];
    int bestMonth[MAXYEARS];
    int yCount = 0;

    for (int i = 0; i < n; ++i) {
        if (data[i].code != K) continue;

        int y = data[i].year;
        int idx = -1;
        for (int j = 0; j < yCount; ++j) {
            if (years[j] == y) { idx = j; break; }
        }

        if (idx == -1) {
            years[yCount] = y;
            maxHours[yCount] = data[i].hours;
            bestMonth[yCount] = data[i].month;
            ++yCount;
        }
        else {
            if (data[i].hours > maxHours[idx] ||
                (data[i].hours == maxHours[idx] && data[i].month < bestMonth[idx])) {
                maxHours[idx] = data[i].hours;
                bestMonth[idx] = data[i].month;
            }
        }
    }

    delete[] data;

    if (yCount == 0) {
        std::cout << "Нет данных\n";
        return;
    }

    Res res[MAXYEARS];
    for (int i = 0; i < yCount; ++i) {
        res[i].hours = maxHours[i];
        res[i].year = years[i];
        res[i].month = bestMonth[i];
    }

    t2_sort(res, yCount);

    std::cout << "Результат:\n";
    for (int i = 0; i < yCount; ++i) {
        std::cout << res[i].hours << " " << res[i].year << " " << res[i].month << "\n";
    }
}


bool lt(const Stu& a, const Stu& b) {
    if (a.ball != b.ball) return a.ball < b.ball;
    return a.fam > b.fam;
}


std::vector<Stu> t3_man(int n) {
    std::vector<Stu> v(n);
    for (int i = 0; i < n; ++i) {
        std::cout << "Ученик " << (i + 1) << ":\n";
        askLine("  фамилия: ", v[i].fam);
        v[i].ball = askInt("  балл (0..100): ", 0, 100);
    }
    return v;
}

std::vector<Stu> t3_rnd(int n) {
    const char* nm[] = { "Иванов","Петров","Сидоров","Кузнецов","Смирнов",
                                "Попов","Волков","Соколов","Морозов","Новиков" };
    std::srand(static_cast<unsigned>(std::time(NULL)));
    std::vector<Stu> v(n);
    for (int i = 0; i < n; ++i) {
        v[i].fam = nm[std::rand() % 10];
        v[i].ball = 1 + std::rand() % 100;
    }
    return v;
}

std::vector<Stu> t3_file(const std::string& fn, int& n) {
    std::ifstream f(fn.c_str());
    if (!f) { std::cout << "Не удалось открыть файл\n"; n = 0; return std::vector<Stu>(); }
    if (!(f >> n) || n <= 0) {
        std::cout << "Некорректное N в файле\n"; n = 0; return std::vector<Stu>();
    }
    std::vector<Stu> v(n);
    for (int i = 0; i < n; ++i) {
        if (!(f >> v[i].fam >> v[i].ball)) {
            std::cout << "Ошибка чтения записи #" << i << "\n";
            n = 0; return std::vector<Stu>();
        }
    }
    return v;
}

void t3_sort(std::vector<Stu>& a) { //Сортировка бинарными вставками
    int n = (int)a.size();
    for (int i = 1; i < n; ++i) {
        Stu key = a[i];
        int l = 0, r = i;
        while (l < r) {
            int m = (l + r) / 2;
            if (lt(a[m], key)) l = m + 1;
            else               r = m;
        }
        for (int j = i; j > l; --j) a[j] = a[j - 1];
        a[l] = key;
    }
}

void t3_run() {
    int c = askInt("Способ ввода: 1-ручной, 2-случайный, 3-из файла: ", 1, 3);

    int n = 0;
    std::vector<Stu> d;

    if (c == 1) {
        n = askInt("Введите N (>=1): ", 1, 10000);
        d = t3_man(n);
    }
    else if (c == 2) {
        n = askInt("Введите N (>=1): ", 1, 10000);
        d = t3_rnd(n);
    }
    else {
        std::string fn;
        while (true) {
            askLine("Имя входного файла: ", fn);
            std::ifstream test(fn.c_str());
            if (test.is_open()) { test.close(); break; }
            std::cout << "Не удалось открыть \"" << fn << "\". Повторите.\n";
        }
        int nn = 0;
        d = t3_file(fn, nn);
        n = nn;
        if (n == 0) return;
    }

    t3_sort(d);

    std::ofstream f;
    if (!askOpenOut(f, "Имя выходного файла: ")) return;

    for (int i = 0; i < (int)d.size(); ++i)
        f << std::left << std::setw(15) << d[i].fam
        << std::right << std::setw(3) << d[i].ball << "\n";
    f.close();

    std::cout << "Результат записан.\n";
    for (int i = 0; i < (int)d.size(); ++i)
        std::cout << std::left << std::setw(15) << d[i].fam
        << std::right << std::setw(3) << d[i].ball << "\n";
}