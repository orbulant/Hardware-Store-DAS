#include <ctime>
#include <vector>
#include "Purchase.h"
#include "LinkedList.h"
#include "Utils.h"
#include "PurchaseController.h"

// CONSTRUCTOR
PurchaseController::PurchaseController(InputHelper inputHelper) {
    // can load purchase into linked list from db
    setInputHelper(inputHelper);
}

// SETTERS
void PurchaseController::setInputHelper(InputHelper inputHelper) {
    this->inputHelper = inputHelper;
}

// METHODS
void PurchaseController::load() {
    // read all available products
    productList.setNodeEnds(fh.createProductLinkedList(fh.readJSONFile(pathProduct)));
    // read all available purchase
    purchaseList.setNodeEnds(fh.createPurchaseLinkedList(fh.readJSONFile(pathPurchase)));

    // to keep track of selection choice
    int purchaseChoice = 0;
    bool end = false;

    do{
        // switch statement here
        cout << "Available Product Related Functions:" << endl;
        cout << "[1] To Add A New Purchase" << endl;
        cout << "[2] To Display All Available Purchases" << endl;
        cout << "[3] To Sort Purchases (Based On Total Price)" << endl;
        cout << "[4] To Search For A Purchase" << endl;
        cout << "[0] to Return" << endl;

        // get choice input
        inputHelper.promptInput("Select an option: ", purchaseChoice, 0, 4, 0, false);
        cout << endl;

        switch(purchaseChoice){
            case 1: {
                add();
                break;
            }
            
            case 2: {
                displayAll();
                break;
            }
            
            case 3: {
                sort();
                unsort();
                break;
            }

            case 4: {
                search();
                break;
            }

            case 0: {
                end = true;
                // sort back sequence to id
                unsort();
                // 'save' changes
                fh.writeToFile(fh.morphProductNodetoJSON(productList.getNodeEnds()), pathProduct);
                productList.removeAll();
                fh.writeToFile(fh.morphPurchaseNodetoJSON(purchaseList.getNodeEnds()), pathPurchase);
                purchaseList.removeAll();
                break;
            }
        }
    } while (!end);
}

void PurchaseController::add(){
    cout << "Adding A Purchase" << endl;
    cout << "Enter [0] To Stop Adding Products" << endl;
    
    vector<Product> productArray;
    Purchase purchase;

    bool end = false;

    do{
        // displays all product
        productList.searchAll();

        int id;

        cout << "Select A Product By ID" << endl;
        if(!inputHelper.promptInput("Enter A Product ID: ", id, 0, 9999999, -1, false)) {
            if(id == 0) {
                end = true;
            } else {
                if(productList.search(id)) {
                    Product product = productList.get(id);
                    
                    if(product.getQuantity() > 0) {
                        // add to vector
                        productArray.push_back(product);
                        cout << endl;
                        cout << "Successfully Inserted Product:" << endl;

                        // decrement the quantity
                        product.setQuantity(product.getQuantity() - 1);
                        productList.update(product, product.getID());

                        productList.printTableHead();
                        productList.toString(product);
                    } else {
                        cout << "Oops! No More Stock For This Item Left!" << endl;
                    }

                    cout << endl;
                } else {
                    cout << "Product ID " << id << " Does Not Exists!" << endl;
                }
            }
        }
    } while (!end);

    // check if any product has been added
    int listLength = productArray.size();
    if(listLength != 0) {
        string datetime;
        // set current date time
        time_t now = time(0);
        datetime = ctime(&now);

        double totalAmount;
        // get total price
        for(int i = 0; i < listLength; i++) {
            totalAmount += productArray[i].getPrice();
        }

        totalAmount = round(totalAmount);
        cout << "Enter [0] To Cancel Purchase" << endl;
        cout << "Total Amount Is (RM): " << totalAmount << endl;

        int paidAmount;
        // using the int datatype function to avoid inaccurate precision comparison of double/float
        if(!inputHelper.promptInput("Enter Paid Amount (RM): ", paidAmount, totalAmount, totalAmount, 0, false)) {
            // removes the weird \n at the last two positions of datetime
            purchase.setDatetime(datetime.substr(0, datetime.length() - 1));
            purchase.setPaidAmount(paidAmount);
            purchase.setProductList(productArray);
            purchaseList.insert(purchase);
            
            cout << endl;
            cout << "Successfully Inserted Purchase" << endl;
            
            purchaseList.toString(purchase);
            cout << endl;

            goto endpoint;
        }
    }

    // return back all the deducted product quantity
    for(int i = 0; i < listLength; i++) {
        int id = productArray.at(i).getID();

        if(productList.search(id)) {
            Product product = productList.get(id);
            // increment the quantity
            product.setQuantity(product.getQuantity() + 1);
            productList.update(product, product.getID());
        }
    }

    cout << "Oops! Looks Like The Customer Didn't Bought Anything!" << endl;
    cout << endl;
    endpoint:;
}

void PurchaseController::displayAll(){
    purchaseList.searchAll();
}

void PurchaseController::search(){
    int id;

    cout << "Search A Purchase By ID" << endl;
    if(!inputHelper.promptInput("Enter A Product ID: ", id, 0, 9999999, -1, false)) {
        if(purchaseList.search(id)) {
            purchaseList.toString(purchaseList.get(id));
        }
    }
    
    cout << endl;
}

void PurchaseController::sort(){
    Node<Purchase> *firstOne = purchaseList.getNodeEnds()->next;
    Node<Purchase> *lastOne = purchaseList.getNodeEnds()->last;
    purchaseList.quickSortPurchase(firstOne, lastOne);
    displayAll();
}

void PurchaseController::unsort(){
    Node<Purchase> *firstOne = purchaseList.getNodeEnds()->next;
    Node<Purchase> *lastOne = purchaseList.getNodeEnds()->last;
    purchaseList.quickSortID(firstOne, lastOne);
}