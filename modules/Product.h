#include <iostream>
using namespace std;
#pragma once

// Product class
class Product{
    int id;
    string name;
    string desc;
    string category_name;
    double price;
    int quantity;

    public:
        // GETTERS
        int getID() { return id; }
        string getName() { return name; }
        string getDesc() { return desc; }
        string getCategory() { return category_name; }
        double getPrice() { return price; }
        int getQuantity() { return quantity; }

        // CONSTRUCTORS
        Product();
        Product(int id, string name, string desc, string category_name, double price, int quantity);

        // SETTERS
        void setID(int id);
        void setName(string name);
        void setDesc(string desc);
        void setCategoryName(string category_name);
        void setPrice(double price);
        void setQuantity(int quantity);
};