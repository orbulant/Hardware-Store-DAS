#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <string>
#include "Utils.h"

bool InputHelper::promptInput(string text, string &variable, string exception, bool hasOptional) {
    bool valid = false;
    do{
        cout << text;
        getline(cin, variable);

        if(hasOptional && variable.compare("0") == 0) {
            cout << "Skipped.." << endl;

            variable = "";
            valid = true;
        } else {
            if(cin.fail() || variable.empty()) {
                cout << "Invalid Input" << endl;
                cin.clear();

                valid = false;
            } else {
                // cout << "Passed cin" << endl;
                // check if is exit key
                if(variable.compare(exception) == 0) {
                    // cout << "Is Exception" << endl;
                    // returns a flag to notify
                    return true;
                // check if input is enter (used for optionally update fields)
                } else {
                    // cout << "Is Valid" << endl;
                    valid = true;
                }
            }
        }
    } while (!valid);

    return false;
}

bool InputHelper::promptInput(string text, int &variable, int minimum, int maximum, int exception, bool hasOptional) {
    bool valid = false;
    do{
        cout << text;
        cin >> variable;
        // cout << variable << endl;
        // cout << minimum << endl;
        // cout << maximum << endl;
        // cout << cin.fail() << endl;
        // cout << (variable == minimum) << endl;
        // cout << (variable == maximum) << endl;
        // cout << (variable < minimum) << endl;
        // cout << (variable > maximum) << endl;
        // cout << (variable < minimum || variable > maximum) << endl;
        cin.ignore();

        if(hasOptional && variable == 0) {
            cout << "Skipped.." << endl;

            variable = 0;
            valid = true;
        } else {
            if(cin.fail()) {
                cout << "Invalid Input" << endl;
                cin.clear();
                cin.ignore();

                valid = false;
            } else {
                // cout << "Passed cin" << endl;
                if(variable == exception) {
                    // cout << "Is Exception" << endl;
                    return true;
                } else if(variable < minimum || variable > maximum) {
                    cout << "Invalid Input" << endl;
                    valid = false;
                } else {
                    // cout << "Is Valid" << endl;
                    valid = true;
                }
            }
        }
    } while (!valid);

    return false;
}

bool InputHelper::promptInput(string text, double &variable, double minimum, double maximum, double exception, bool hasOptional) {
    bool valid = false;
    do{
        cout << text;
        cin >> variable;
        // cout << fixed << setprecision(20) << variable << endl;
        // cout << fixed << setprecision(20) << minimum << endl;
        // cout << maximum << endl;
        // cout << cin.fail() << endl;
        // cout << (variable == minimum) << endl;
        // cout << (variable == maximum) << endl;
        // cout << (variable < minimum) << endl;
        // cout << (variable > maximum) << endl;
        // cout << (variable < minimum || variable > maximum) << endl;
        cin.ignore();

        if(hasOptional && variable == 0) {
            cout << "Skipped.." << endl;

            variable = 0;
            valid = true;
        } else {
            if(cin.fail()) {
                cout << "Invalid Input" << endl;
                cin.clear();
                cin.ignore();
                
                valid = false;
            } else {
                // cout << "Passed cin" << endl;
                if(variable == exception) {
                    // cout << "Is Exception" << endl;
                    return true;
                } else if(variable < minimum || variable > maximum) {
                    cout << "Here" << endl;
                    cout << "Invalid Input" << endl;
                    valid = false;
                } else {
                    // cout << "Is Valid" << endl;
                    variable = ceil(variable * 100.0) / 100.0;
                    valid = true;
                }
            }
        }
    } while (!valid);

    return false;
}

bool InputHelper::promptConfirmation() {
    bool valid = false;
    string confirmation;
    do{
        cout << "Confirm to proceed? [y/n]: ";
        cin >> confirmation;
        
        if(confirmation.compare("y") == 0) {
            return true;
        } else if (confirmation.compare("n") == 0) {
            return false;
        // check for datatype error and minimum boundary
        } else if (cin.fail()) {
            cout << "Invalid Input" << endl;
        } else {
            valid = true;
        }
    } while (!valid);

    return false;
}

void Category::printAllCategories() {
    cout << "---------------------------------------------------" << endl;
    cout << "List Of Available Categories: " << endl;

    for(int i = 1; i < 11; i++) {
        cout << "[" << i << "] " << category_list[i - 1] << endl;
    }
    
    cout << endl;
}

string Category::get(int index) {
    return category_list[index - 1];
}

int Category::length() {
    return sizeof(category_list)/sizeof(category_list[0]);
}