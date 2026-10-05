#pragma once
#include <string>


int countWords(const std::string& s);
std::string replaceBrackets(const std::string& s);
bool isLetter(char c);
bool isDigit(char c);
bool isLower(char c);
bool isUpper(char c);
bool isControl(char c);
int countUnique(const std::string& s);
bool isBinary(const std::string& s);
long long toDecimal(const std::string& s);
std::string makePassword(int level);
void checkHomework(const std::string& inFile, const std::string& outFile);


int askInt(const std::string& prompt);
int askRange(const std::string& prompt, int lo, int hi);
std::string askLine(const std::string& prompt);
char askChar(const std::string& prompt);
std::string askFile(const std::string& prompt);