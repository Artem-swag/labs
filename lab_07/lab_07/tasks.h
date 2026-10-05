#pragma once
#pragma once
#include <vector>
#include <string>

int  askInt(const std::string& prompt);
int  askInt(const std::string& prompt, int lo, int hi);
void askLine(const std::string& prompt, std::string& out);

void t1_run();
std::vector<int> t1_man(int n);
std::vector<int> t1_rnd(int n);
std::vector<int> t1_file(const std::string& fn, int& n);
std::string      t1_fmt(const std::vector<int>& a, int k);

struct Rec { int code, hours, year, month; };
struct Res { int hours, year, month; };


void t2_run();
void t2_man(Rec* arr, int& n, int& K);
void t2_rnd(Rec* arr, int& n, int& K);
void t2_file(const std::string& fn, Rec* arr, int& n, int& K);
void t2_sort(Res* a, int n);

struct Stu { std::string fam; int ball; };

void t3_run();
void t3_sort(std::vector<Stu>& a);
std::vector<Stu> t3_man(int n);
std::vector<Stu> t3_rnd(int n);
std::vector<Stu> t3_file(const std::string& fn, int& n);