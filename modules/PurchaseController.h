#include <iostream>
#include "Utils.h"
#include "LinkedList.h"
#include "FileHandler.h"
#pragma once

using namespace std;

class PurchaseController{
    InputHelper inputHelper;
    FileHandler fh;
    string pathProduct = "json/product.json";
    string pathPurchase = "json/purchase.json";

    ProductLinkedList productList;
    PurchaseLinkedList purchaseList;

    public:
        // GETTERS
        InputHelper getInputHelper() { return inputHelper; }

        // CONSTRUCTOR
        PurchaseController(InputHelper inputHelper);

        // SETTERS
        void setInputHelper(InputHelper InputHelper);

        // METHODS
        void load();
        void add();
        void displayAll();
        void search();
        void sort();
        void unsort();
};