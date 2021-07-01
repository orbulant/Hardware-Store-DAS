#include <iostream>
#include <iomanip>
#include "LinkedList.h"
#include "Utils.h"
using namespace std;

/*
* * * * * * * * * * * * * * * * * * * * * * * *
*
    LINKED LIST CLASS
*
* * * * * * * * * * * * * * * * * * * * * * * *
*/

// CONSTRUCTOR 
template<typename T>
LinkedList<T>::LinkedList(){
    // create a new node head and set to the local variable
    setNodeEnds(new Node<T>);
}

/*
    DESTRUCTOR
    destroys linked list by calling remove all function

    NOTE:
    Spend too much time making this work but failed in the end
    Replaced with explicitly calling removeall when knowing the list will not be used anymore
*/
// template<typename T>
// LinkedList<T>::~LinkedList(){
//     // destroys the linked list by calling remove all to remove all the nodes
//     removeAll();
// } 

// SETTERS
template<typename T>
void LinkedList<T>::setNodeEnds(Node<T> *listEnds){
    this->listEnds = listEnds;
}

// METHOD
// add (default is append to last)
template<typename T>
void LinkedList<T>::insert(T data){
    // creates a new node of generic datatype
    Node<T> *node = new Node<T>;
    
    // sets the data in the new node to passed data
    node->data = data;

    // check if is first node in linked list
    if(listEnds->next == NULL) {
        // directly assign next to the created node
        listEnds->next = node;
    } else {
        // initialize temporary pointer
        Node<T> *pointer = listEnds->last;

        // set last pointer to the new node
        pointer->next = node;

        // set previous pointer for last node for backward traverse
        node->last = pointer;
    }

    // set the tail pointer to node end
    listEnds->last = node;
}

// update
template<typename T>
void LinkedList<T>::update(T data, int id){
    // get the node head
    Node<T> *pointer = listEnds;

    // check if there's a next node
    while(pointer->next != NULL) {
        // change the pointer to the next node
        pointer = pointer -> next;
        
        // check if its the item to be updated
        if(pointer->data.getID() == id) {
            // update the item
            pointer->data = data;
            // exit loop
            goto endpoint;
        }
    }

    // if no next node or no record found
    cout << "No record with ID " << id << " found!" << endl;
    cout << endl;
    // break here to skip not found message
    endpoint:;
}

// retrieve a specific record by id
template<typename T>
T LinkedList<T>::get(int id){
    // get the node head
    Node<T> *pointer = listEnds;

    // check if there's a next node
    while(pointer->next != NULL) {
        // change the pointer to the next node
        pointer = pointer -> next;
        
        // check if its the item to be searched
        if(pointer->data.getID() == id) {
            // returns the item and end this function
            return pointer->data;
        }
    }

    // if no next node or no record found
    cout << "No record with ID " << id << " found!" << endl;
    cout << endl;

    /*
        no return statement here
        Reason: Performed search(id) before calling this method to ensure that id exists
                Since search has helped check the existance of id, it will always be available when calling this method
                At least in the same runtime...
    */
   T temp;
   return temp;
}

// return all product object in the form of an array in linked list (used in purchase controller to convert product linked list into product array)
template<typename T>
T *LinkedList<T>::getAllAsArray(){
    // get the node head
    Node<T> *pointer = listEnds;
    // to keep track of array index
    int counter = 0;

    // creates a new array to be returned
    T *array = new T[length()];

    // check if there's a next node
    while(pointer->next != NULL) {
        // change the pointer to the next node
        pointer = pointer -> next;
        
        // add node to array according to index
        array[counter] = pointer->data;
        // increment index
        counter++;
    }
    
    return array;
}

// search one (id)
template<typename T>
bool LinkedList<T>::search(int id){
    // get the node head
    Node<T> *pointer = listEnds;

    // check if there's a next node
    while(pointer->next != NULL) {
        pointer = pointer -> next;
        
        // check if its the item to be searched
        if(pointer->data.getID() == id) {
            // exit loop if found and return true to indicate found
            return true;
        }
    }

    // if no next node or no record found
    cout << "No record with ID " << id << " found!" << endl;
    cout << endl;

    // return false to indicate not found
    return false;
}

// delete one (id)
template<typename T>
void LinkedList<T>::remove(int id){
    // pointer for current node
    Node<T> *pointer = listEnds;
    // pointer for previous node of current node
    Node<T> *previous;
    // pointer for next node of current node
    Node<T> *after;

    // check if there's a next node
    while(pointer->next != NULL) {
        // set current node as previous
        previous = pointer;
        // move one node ahead (which is now the current node)
        pointer = pointer->next;
        // move another one node ahead as next node (may be NULL)
        after = pointer->next;

        // check if its the item to be searched
        if(pointer->data.getID() == id) {
            // link the before node of current node
            previous->next = pointer->next;
            
            // check if next of current node is NULL
            if(after != NULL) {
                // link the after node of current node
                after->last = pointer->last;
            } else {
                // set last of node head as the previous node is the last node in the list
                listEnds->last = previous;
            }

            // deletes the item
            delete pointer;

            // print confirmation message
            cout << "Deleted Record Of ID: " << id << "!" << endl;
            goto endpoint;
        }
    }

    // if no next node or no record found
    cout << "No record with ID " << id << " found!" << endl;
    // break here to skip not found message
    endpoint:;
    cout << endl;
}

// delete all
template<typename T>
void LinkedList<T>::removeAll(){
    // set node head
    Node<T> *pointer = listEnds;
    // for to-be-delete nodes
    Node<T> *deletePointer;

    int counter = 0;

    // check if there's a next node
    while(pointer->next != NULL) {
        // mark node to be deleted
        deletePointer = pointer;
        
        // move on to next node
        pointer = pointer->next;

        // remove the node
        delete deletePointer;
        counter++;
    }

    // print confirmation message
    cout << "Deleted " << counter << " Product Records!" << endl;
    cout << endl;
}

template<typename T>
void LinkedList<T>::toString(T data) {
    // simple print for base class
    cout << "" << endl;
}

template<typename T>
// Quick Sort ID
void LinkedList<T>::quickSortID(Node<T> *left, Node<T> *right)
{
    if(right != NULL && left != right && left != right->next){
        Node<T> *p = partitionID(left,right);
        quickSortID(left, p->last);
        quickSortID(p->next, right);
    }
}

template<typename T>
// Partition QuickSort
Node<T> *LinkedList<T>::partitionID(Node<T> *left, Node<T> *right)
{
   Node<T> *pivot = right;
   Node<T> *i = left->last;
   for(Node<T> *ptr = left; ptr != right; ptr = ptr->next){
       if(ptr->data.getID() <= pivot->data.getID()){
           i = (i==NULL? left : i->next);
           T temp = i->data;
           i->data = ptr->data;
           ptr->data = temp;
       }
   }
   i = (i==NULL? left : i->next);
   T temp = i->data;
   i->data = pivot->data;
   pivot->data = temp;
   return i;
};

// check if either end is set
template<typename T>
bool LinkedList<T>::isEmptyEnds(){
    // check if there's a node head
    return listEnds == NULL;
}

// check if head end is set
template<typename T>
bool LinkedList<T>::isEmptyHead(){
    return listEnds->next == NULL;
}

// check if tail end is set
template<typename T>
bool LinkedList<T>::isEmptyTail(){
    return listEnds->last == NULL;
}

template<typename T>
int LinkedList<T>::length() {
    Node<T> *pointer = listEnds;
    int counter = 0;

    while(pointer->next != NULL) {
        pointer = pointer -> next;
        
        counter++;
    }

    return counter;
}

template<typename T>
int LinkedList<T>::getLatestID() {
    // get the node head
    Node<T> *pointer = listEnds;
    int id = 0;

    // check if there's a next node
    while(pointer->next != NULL) {
        pointer = pointer -> next;
        
        // check if is first node
        if(id == 0) {
            id = pointer->data.getID();
        } else {
            // check if its the item to be searched
            if(pointer->data.getID() > id) {
                // set data id as current id if value is more than current id
                id = pointer->data.getID();
            }
        }
    }
    
    return id;
}

/*
* * * * * * * * * * * * * * * * * * * * * * * *
*
    PRODUCT LINKED LIST CLASS
*
* * * * * * * * * * * * * * * * * * * * * * * *
*/

ProductLinkedList::ProductLinkedList() : LinkedList<Product>() {}

// Quick Sort Product
void ProductLinkedList::quickSortProduct(Node<Product> *left, Node<Product> *right)
{
    if(right != NULL && left != right && left != right->next){
        Node<Product> *p = partitionProduct(left,right);
        quickSortProduct(left, p->last);
        quickSortProduct(p->next, right);
    }
}

// Partition QuickSort
Node<Product> *ProductLinkedList::partitionProduct(Node<Product> *left, Node<Product> *right)
{
   Node<Product> *pivot = right;
   Node<Product> *i = left->last;
   for(Node<Product> *ptr = left; ptr != right; ptr = ptr->next){
       if(ptr->data.getQuantity() <= pivot->data.getQuantity()){
           i = (i==NULL? left : i->next);
           Product temp = i->data;
           i->data = ptr->data;
           ptr->data = temp;
       }
   }
   i = (i==NULL? left : i->next);
   Product temp = i->data;
   i->data = pivot->data;
   pivot->data = temp;
   return i;
};

// search all
void ProductLinkedList::searchAll(){
    Node<Product> *pointer = listEnds;

    cout << endl;
    cout << "Searching All Available Data: " << endl;
    printTableHead();
    
    while(pointer->next != NULL) {
        pointer = pointer -> next;
    
        // prints data
        toString(pointer->data);
    }

    cout << endl;
}

void ProductLinkedList::searchByCategory(string input){
    Node<Product> *pointer = listEnds;

    cout << endl;
    cout << "Searching All Available Data: " << endl;
    printTableHead();
    
    while(pointer->next != NULL) {
        pointer = pointer -> next;
        if((pointer->data.getCategory().compare(input)) == 0){
             // prints data
            toString(pointer->data);
        }
    }
}

void ProductLinkedList::printTableHead() {
    cout << left << "|" << setw(idWidth) << setfill(separator) << "ID";
    cout << left << "|" << setw(nameWidth) << setfill(separator) << "NAME";
    cout << left << "|" << setw(descWidth) << setfill(separator) << "DESCRIPTION";
    cout << left << "|" << setw(categoryWidth) << setfill(separator) << "CATEGORY";
    cout << left << "|" << setw(priceWidth) << setfill(separator) << "PRICE";
    cout << left << "|" << setw(quantityWidth) << setfill(separator) << "QUANTITY";
    cout << endl;

    cout << left << "|" << setw(idWidth) << setfill('-') << "";
    cout << left << "|" << setw(nameWidth) << setfill('-') << "";
    cout << left << "|" << setw(descWidth) << setfill('-') << "";
    cout << left << "|" << setw(categoryWidth) << setfill('-') << "";
    cout << left << "|" << setw(priceWidth) << setfill('-') << "";
    cout << left << "|" << setw(quantityWidth) << setfill('-') << "";
    cout << endl;
}

void ProductLinkedList::toString(Product product) {
    cout << left << "|"  << setw(idWidth) << setfill(separator) << product.getID();
    cout << left << "|"  << setw(nameWidth) << setfill(separator) <<  product.getName();
    cout << left << "|"  << setw(descWidth) << setfill(separator) <<  product.getDesc();
    cout << left << "|"  << setw(categoryWidth) << setfill(separator) <<  product.getCategory();
    cout << left << "|"  << setw(priceWidth) << setfill(separator) << fixed << setprecision(2) << product.getPrice();
    cout << left << "|"  << setw(quantityWidth) << setfill(separator) <<  product.getQuantity();
    cout << endl;
}

/*
* * * * * * * * * * * * * * * * * * * * * * * *
*
    PURCHASE LINKED LIST CLASS
*
* * * * * * * * * * * * * * * * * * * * * * * *
*/

PurchaseLinkedList::PurchaseLinkedList() : LinkedList<Purchase>() {

}

// Quick Sort Purchase
void PurchaseLinkedList::quickSortPurchase(Node<Purchase> *left, Node<Purchase> *right)
{
    if(right != NULL && left != right && left != right->next){
        Node<Purchase> *p = partitionPurchase(left,right);
        quickSortPurchase(left, p->last);
        quickSortPurchase(p->next, right);
    }
}
// Partition QuickSort
// Accepts a left node and right node.
Node<Purchase> *PurchaseLinkedList::partitionPurchase(Node<Purchase> *left, Node<Purchase> *right)
{

   Node<Purchase> *pivot = right;
   Node<Purchase> *i = left->last;
   for(Node<Purchase> *ptr = left; ptr != right; ptr = ptr->next){
       if(ptr->data.getPaidAmount() <= pivot->data.getPaidAmount()){
           i = (i==NULL? left : i->next);
           Purchase temp = i->data;
           i->data = ptr->data;
           ptr->data = temp;
       }
   }
   i = (i==NULL? left : i->next);
   Purchase temp = i->data;
   i->data = pivot->data;
   pivot->data = temp;
   return i;
};

// search all
void PurchaseLinkedList::searchAll(){
    Node<Purchase> *pointer = listEnds;

    cout << endl;
    cout << "Searching All Available Data: " << endl;
    
    while(pointer->next != NULL) {
        pointer = pointer -> next;
    
        // prints data
        toString(pointer->data);
    }

    cout << endl;
}

void PurchaseLinkedList::toString(Purchase purchase) {
    cout << "*******************************************************" << endl;
    cout << "Purchase ID: " << purchase.getID() << endl;
    cout << "Purchase Datetime: " << purchase.getDateTime() << endl;
    cout << "Purchase Paid Amount: " << purchase.getPaidAmount() << endl;
    cout << "Product List:" << endl;

    ProductLinkedList productList;
    vector<Product> *productArray = purchase.getProductList();

    for(int i = 0; i < productArray->size(); i++) {
        Product product = productArray->at(i);
        cout << "\t Product ID: " << product.getID() << endl;
        cout << "\t Product Name: " << product.getName() << endl;
        cout << "\t Product Description: " << product.getDesc() << endl;
        cout << "\t Product Category: " << product.getCategory() << endl;
        cout << "\t Product Unit Price: " << product.getPrice() << endl;
        cout << "\t --------------------------------------------------------------" << endl;
    }

    cout << endl;
}

template class LinkedList<Product>;
template class LinkedList<Purchase>;