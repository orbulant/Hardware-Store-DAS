#include <iostream>
#include <vector>
#include "Product.h"

#pragma once
using namespace std;

// Purchase class
class Purchase{
    int id;
    string datetime;
    double paidamount;
    vector<Product> productArray;

    public:
        // GETTERS
        int getID() { return id; }
        string getDateTime() { return datetime; }
        double getPaidAmount() { return paidamount; }
        vector<Product> *getProductList() { return &productArray; }

        // CONSTRUCTORS
        Purchase();
        Purchase(int id, string datetime, double paidamount, vector<Product> productArray);

        // SETTERS
        void setID(int id);
        void setDatetime(string datetime);
        void setPaidAmount(double paidamount);
        void setProductList(vector<Product> productArray);
};
