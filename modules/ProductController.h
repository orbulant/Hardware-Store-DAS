#include <iostream>
#include "Utils.h"
#include "LinkedList.h"
#include "FileHandler.h"
#pragma once

using namespace std;

class ProductController{
    Category category_selection;
    InputHelper inputHelper;
    FileHandler fh;
    string pathProduct = "json/product.json";

    ProductLinkedList productList;

    public:
        // GETTERS
        InputHelper getInputHelper() { return inputHelper; }

        // CONSTRUCTOR
        ProductController(InputHelper inputHelper);

        // SETTERS
        void setInputHelper(InputHelper inputHelper);

        // METHODS
        void load();
        void add();
        void update();
        void remove();
        void search();
        void displayAll();
        void filter();
        void sort();
        void unsort();
};