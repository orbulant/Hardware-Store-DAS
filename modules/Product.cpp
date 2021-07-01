#include "Product.h"

// CONSTRUCTORS
Product::Product() {
    setID(rand() % 100 + 1);
    setName("");
    setDesc("");
    setCategoryName("");
    setPrice(0);
    setQuantity(0);
}

Product::Product(int id, string name, string desc, string category_name, double price, int quantity) {
    setID(id);
    setName(name);
    setDesc(desc);
    setCategoryName(category_name);
    setPrice(price);
    setQuantity(quantity);
}

// SETTERS
void Product::setID(int id){
    this->id = id;
}

void Product::setName(string name){
    this->name = name;
}

void Product::setDesc(string desc){
    this->desc = desc;
}

void Product::setCategoryName(string category_name){
    this->category_name = category_name;
}

void Product::setPrice(double price){
    this->price = price;
}

void Product::setQuantity(int quantity){
    this->quantity = quantity;
}