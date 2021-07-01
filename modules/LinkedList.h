#include <iostream>
#include "Product.h"
#include "Purchase.h"
#pragma once
using namespace std;

/*
    Nodes for linked list
    Used Templates As Both Product And Purchase Can Use The Same Node.. 
    ..Without Needing To Make Different Nodes That Supports Different Datatypes
*/
template<typename T>
struct Node{
    T data;
    Node *next = NULL; // can be used to store next node address
    Node *last = NULL; // can be used to store previous node address
};

/*
    Linked List Manager
    Contains Common LinkedList Functions 
    Serves As Base Class For Derivations Of More Specific Linked Lists
*/
template<typename T>
class LinkedList{
    protected:
        // stores the head and tail information of linked list
        Node<T> *listEnds = NULL;
    public:
        // CONSTRUCTOR
        LinkedList();
        // GETTERS
        Node<T> *getNodeEnds() { return listEnds; }
        // SETTERS
        void setNodeEnds(Node<T> *listEnds);
        // METHODS
        // add
        void insert(T data);
        // update
        void update(T data, int id);
        // retrieving object
        T get(int id);
        T *getAllAsArray();
        // search one (id)
        bool search(int id);
        // delete one (id)
        void remove(int id);
        // delete all
        void removeAll();
        void toString(T data);
        // Quick Sort ID
        void quickSortID(Node<T> *left, Node<T> *right);
        // partition for quick sorting (id)
        Node<T> *partitionID(Node<T> *left, Node<T> *right);
        // check if either end is set
        bool isEmptyEnds();
        // check if head end is set
        bool isEmptyHead();
        // check if tail end is set
        bool isEmptyTail();

        // get length of linked list
        int length();
        
        // get the latest id in the list
        int getLatestID();
};

class ProductLinkedList : public LinkedList<Product> {
    // measurements for table output
    char separator = ' ';
    int idWidth = 6;
    int nameWidth = 30;
    int descWidth = 70;
    int categoryWidth = 20;
    int priceWidth = 30;
    int quantityWidth = 20;
    
    public:
        // CONSTRUCTOR
        ProductLinkedList();

        // METHODS
        // quick sorts product
        void quickSortProduct(Node<Product> *left, Node<Product> *right);
        // partition for quick sorting (quantity)
        Node<Product> *partitionProduct(Node<Product> *left, Node<Product> *right);
        // searches all product
        void searchAll();
        // searches product by category
        void searchByCategory(string input);
        // prints the table header onto console
        void printTableHead();
        // converts product object into readable(table row) string and prints to console
        void toString(Product product);      
};

class PurchaseLinkedList : public LinkedList<Purchase> {
    public:
        // CONSTRUCTOR
        PurchaseLinkedList();

        // METHODS
        // quick sorts purchase 
        void quickSortPurchase(Node<Purchase> *left, Node<Purchase> *right);
        // partition for quick sorting
        Node<Purchase> *partitionPurchase(Node<Purchase> *left, Node<Purchase> *right);
        // searches all purchase
        void searchAll();
        // converts purchase object into readable string and prints to console
        void toString(Purchase purchase);
};