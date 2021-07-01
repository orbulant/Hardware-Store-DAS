#include <iostream>
#pragma once
using namespace std;

struct InputHelper{
    bool promptInput(string text, string &variable, string exception, bool hasOptional);
    bool promptInput(string text, int &variable, int minimum, int maximum, int exception, bool hasOptional);
    bool promptInput(string text, double &variable, double minimum, double maximum, double exception, bool hasOptional);
    bool promptConfirmation();
};

class Category{
    string category_list[10] = {
        "Monitor",
        "Motherboard",
        "CPU",
        "RAM",
        "PSU",
        "CD-ROM", // optical disk drive
        "HDD",
        "Laptop",
        "Keyboard",
        "Mouse",
    };

    public:
        void printAllCategories();
        string get(int index);
        int length();
};
