#include "Product.h"
#include "LinkedList.h"
#include "Utils.h"
#include "ProductController.h"

// CONSTRUCTOR
ProductController::ProductController(InputHelper inputHelper) {
    setInputHelper(inputHelper);
}

// SETTERS
void ProductController::setInputHelper(InputHelper inputHelper) {
    this->inputHelper = inputHelper;
}

// METHODS
void ProductController::load() {
    // read all available products
    productList.setNodeEnds(fh.createProductLinkedList(fh.readJSONFile(pathProduct)));
    // to keep track of selection choice
    int productChoice = 0;
    bool end = false;

    do{
        // switch statement here
        cout << "Available Product Related Functions:" << endl;
        cout << "[1] To Add A New Product" << endl;
        cout << "[2] To Update A Product Information" << endl;
        cout << "[3] To Delete A Product" << endl;
        cout << "[4] To Search For A Product" << endl;
        cout << "[5] To Display All Available Products" << endl;
        cout << "[6] To Filter Products Of A Category" << endl;
        cout << "[7] To Sort Products (Based On Quantity)" << endl;
        cout << "[0] to Return" << endl;

        // get choice input
        inputHelper.promptInput("Select an option: ", productChoice, 0, 7, 0, false);
        cout << endl;

        switch(productChoice){
            case 1: {
                add();
                break;
            }
            
            case 2: {
                update();
                break;
            }
            
            case 3: {
                remove();
                break;
            }

            case 4: {
                search();
                break;
            }

            case 5: {
                displayAll();
                break;
            }

            case 6: {
                filter();
                break;
            }

            case 7: {
                sort();
                unsort();
                break;
            }

            case 0: {
                end = true;
                // sort back sequence to id
                unsort();
                // 'save' changes
                fh.writeToFile(fh.morphProductNodetoJSON(productList.getNodeEnds()), pathProduct);
                productList.removeAll();
                break;
            }
        }
    } while (!end);
}

void ProductController::add(){
    cout << "Adding A Product" << endl;
    cout << "Enter [-1] To Cancel This Operation" << endl;
    cout << endl;

    string name, desc, category_name;
    double price;
    int quantity, category_index;
    Product product;

    if(inputHelper.promptInput("Enter A Product Name: ", name, "-1", false)) {
        goto endpoint;
    }

    if(inputHelper.promptInput("Enter A Product Description: ", desc, "-1", false)) {
        goto endpoint;
    }

    category_selection.printAllCategories();
    if(inputHelper.promptInput("Enter A Product Category Name: ", category_index, 1, category_selection.length(), -1, false)) {
        goto endpoint;
    } else {
        category_name = category_selection.get(category_index);
    }

    if(inputHelper.promptInput("Enter A Product Price (RMxx.xx): ", price, 1, 9999999, -1, false)) {
        goto endpoint;
    }

    if(inputHelper.promptInput("Enter A Product Quantity (>=1): ", quantity, 1, 9999999, -1, false)) {
        goto endpoint;
    }

    // get the largest id available and increment by one 
    product.setID(productList.getLatestID() + 1);
    product.setName(name);
    product.setDesc(desc);
    product.setCategoryName(category_name);
    product.setPrice(price);
    product.setQuantity(quantity);
    productList.insert(product);

    cout << endl;
    cout << "Successfully Inserted Product:" << endl;

    productList.printTableHead();
    productList.toString(product);

    endpoint:;
    cout << endl;
}

void ProductController::update(){
    int id;

    cout << "Select A Product By ID" << endl;
    if(inputHelper.promptInput("Enter A Product ID: ", id, 0, 9999999, -1, false)) {
        return;
    } else {
        if(productList.search(id)) {
            Product originalProduct = productList.get(id);
            
            cout << endl;
            productList.printTableHead();
            productList.toString(originalProduct);

            cout << "Enter [-1] To Cancel This Operation" << endl;
            cout << "Input [0] To Skip A Field" << endl;
            cout << endl;

            string name, desc, category_name;
            double price;
            int quantity, category_index;
            Product product;

            if(inputHelper.promptInput("Enter A Product Name: ", name, "-1", false)) {
                goto endpoint;
            }

            if(inputHelper.promptInput("Enter A Product Description: ", desc, "-1", false)) {
                goto endpoint;
            }

            category_selection.printAllCategories();
            if(inputHelper.promptInput("Enter A Product Category Name: ", category_index, 0, category_selection.length(), -1, false)) {
                goto endpoint;
            }

            if(inputHelper.promptInput("Enter A Product Price (RMxx.xx): ", price, 0, 9999999, -1, false)) {
                goto endpoint;
            }

            if(inputHelper.promptInput("Enter A Product Quantity (>=1): ", quantity, 0, 9999999, -1, false)) {
                goto endpoint;
            }

            product.setID(id); // set previous id

            // for some reason .empty() and == (only) not working on ""
            if(name.compare("0") != 0) {
                product.setName(name);
            } else {
                product.setName(originalProduct.getName());
            }

            if(desc.compare("0") != 0) {
                product.setDesc(desc);
            } else {
                product.setDesc(originalProduct.getDesc());
            }

            if(category_index != 0) {
                product.setCategoryName(category_selection.get(category_index));
            } else {
                product.setCategoryName(originalProduct.getCategory());
            }

            if(price != 0) {
                product.setPrice(price);
            } else {
                product.setPrice(originalProduct.getPrice());
            }

            if(quantity != 0) {
                product.setQuantity(quantity);
            } else {
                product.setQuantity(originalProduct.getQuantity());
            }

            productList.update(product, id);
            cout << endl;
            cout << "Successfully Updated Product: " << endl;

            // prints updated data
            productList.printTableHead();
            productList.toString(product);

            endpoint:;
            cout << endl;
        }
    }
}

void ProductController::remove(){
    int id;

    cout << "Select A Product By ID" << endl;
    if(inputHelper.promptInput("Enter A Product ID: ", id, 0, 9999999, -1, false)) {
        return;
    } else {
        if(productList.search(id)) {
            if(inputHelper.promptConfirmation()) {
                productList.remove(id);
            }
        }
    }
}

void ProductController::search(){
    int id;

    cout << "Search A Product By ID" << endl;
    if(inputHelper.promptInput("Enter A Product ID: ", id, 0, 9999999, -1, false)) {
        goto endpoint;
    } else {
        if(productList.search(id)) {
            productList.printTableHead();
            productList.toString(productList.get(id));
        }
    }

    endpoint:;
    cout << endl;
}

void ProductController::displayAll(){
    productList.searchAll();
}

void ProductController::filter(){
    //Declares category object.
    Category category;
    //Prints all categories present from the category list.
    category.printAllCategories();
    //Couts a console output to inform user to select a range from 0-9 as per the index
    cout << "Please select from a number ranging from [1] to [10]" << endl;
    //Declaring selection chocie variable.
    int selectionChoice;
    //Input Helper to obtain selection choice from users.
    if(inputHelper.promptInput("Enter your choice: ", selectionChoice, 0, 9999999, -1, false)){
        goto endpoint;
    } else {
        productList.searchByCategory(category.get(selectionChoice));
    }
    endpoint:;

    cout << endl;
}

void ProductController::sort(){
    Node<Product> *firstOne = productList.getNodeEnds()->next;
    Node<Product> *lastOne = productList.getNodeEnds()->last;
    //std::cout << firstOne << "\n\n";
    //std::cout << lastOne << "\n\n";
    productList.quickSortProduct(firstOne, lastOne);
    displayAll();
}

void ProductController::unsort(){
    Node<Product> *firstOne = productList.getNodeEnds()->next;
    Node<Product> *lastOne = productList.getNodeEnds()->last;
    productList.quickSortID(firstOne, lastOne);
}