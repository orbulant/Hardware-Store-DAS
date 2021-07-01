#include <iostream>
#include "modules/Utils.h"
#include "modules/ProductController.h"
#include "modules/PurchaseController.h"

using namespace std;

// class methods
void choiceController(InputHelper inputHelper);
void purchaseController(InputHelper inputHelper);

void choiceController(InputHelper inputHelper) {
    int choice = 0;
    bool end = false;

    do{
        cout << "What would you like to do?" << endl;
        cout << "[1] for Product Related Functions" << endl;
        cout << "[2] for Purchase/Transaction Related Functions" << endl;
        cout << "[-1] to Terminate Console" << endl;

        // get choice input
        inputHelper.promptInput("Select an option: ", choice, -1, 2, -1, false);
        // cout << "Choice:" << choice << endl;
        cout << endl;

        switch(choice){
            case 1: {
                // redirect to product controller for choice selection
                ProductController productController(inputHelper);
                productController.load();
                break;
            }
            
            case 2: {
                // redirect to purchase controller for choice selection
                PurchaseController purchaseController(inputHelper);
                purchaseController.load();
                break;
            }

            case -1: {
                end = true;
                break;
            }

            default: {
                cout << "Invalid Input" << endl;
                break;
            }
        }
    } while(!end);
}

// Main class
int main() {
    cout << "------------\tINITIALIZING\t------------" << endl;
    InputHelper inputHelper;
    cout << "*********************************" << endl;
    cout << "* Welcome to ABC Hardware Store *" << endl;
    cout << "*********************************" << endl;
    cout << endl;

    choiceController(inputHelper);

    cout << "------------TERMINATING------------" << endl;
    cout << "\t Terminating Program \t" << endl;
    return 0;
}