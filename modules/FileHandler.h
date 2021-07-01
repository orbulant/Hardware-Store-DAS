#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include "LinkedList.h"
#include "Product.h"
#include "Purchase.h"

#pragma once

using json = nlohmann::json;

class FileHandler{
    private:
    /*NOTHING*/

    public:
    /*CONSTRUCTORS*/
    FileHandler();
    /*DESTRUCTORS*/
    ~FileHandler();

    /*METHODS*/
    
    //READS JSON FILE AND RETURNS A JSON DATA TYPE
    json readJSONFile(string path);
    //CREATES A PRODUCT LINKED LIST
    Node<Product> *createProductLinkedList(json input); //RETURNS HEAD POINTER 
    Node<Purchase> *createPurchaseLinkedList(json input);//RETURNS HEAD POINTER
    //TRAVERSES AN ENTIRE LINKED LIST BY ACCEPTING THE HEAD NODE AND THEN TRAVERSING ALL THE WAY TO THE END, THEN RETURNS A JSON ARRAY WITH ALL THE DATA OBTAINED FROM EACH NODE
    json morphProductNodetoJSON(Node<Product> *productNode);
    json morphPurchaseNodetoJSON(Node<Purchase> *purchaseNode);
    //WRITES A JSON TO A FILE WITH A SPECIFIED PATH OUTPUT
    void writeToFile(json jsonInput, string outputPath);
};