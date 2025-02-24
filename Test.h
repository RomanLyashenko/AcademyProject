#pragma once
using namespace std;
#include <string>
#include <vector>
#include <fstream>
#include "Admin.h"

class Test {
public:
    std::string category; // Категория теста
    std::string name;     // Название теста
    std::vector<std::string> questions; // Вопросы теста
    std::vector<std::pair<std::string, std::string>> answers; // Ответы (первый - правильный, второй - неправильный)

    // Метод для записи теста в файл
    void saveToFile(const std::string& filename);
};