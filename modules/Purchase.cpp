#include "Purchase.h"

// CONSTRUCTORS
Purchase::Purchase() {
    setID(rand() % 100 + 1);
    setDatetime("");
    setPaidAmount(0);
}

Purchase::Purchase(int id, string datetime, double paidamount, vector<Product> productArray) {
    setID(id);
    setDatetime(datetime);
    setPaidAmount(paidamount);
    setProductList(productArray);
}

// SETTERS
void Purchase::setID(int id){
    this->id = id;
}

void Purchase::setDatetime(string datetime){
    this->datetime = datetime;
}

void Purchase::setPaidAmount(double paidamount){
    this->paidamount = paidamount;
}

void Purchase::setProductList(vector<Product> productArray){
    this->productArray = productArray;
}