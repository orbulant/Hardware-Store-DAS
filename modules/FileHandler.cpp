#include <iostream>
#include <fstream>
#include <iomanip>
#include "json.hpp"
#include "FileHandler.h"
#include "LinkedList.h"
#include "Product.h"
#include "Purchase.h"


using json = nlohmann::json;

/*CONSTRUCTOR*/
FileHandler::FileHandler()
{
}

/*DESTRUCTOR*/
FileHandler::~FileHandler()
{
}

/*METHODS*/
json FileHandler::readJSONFile(string path)
{
    ifstream jsonfile(path);

    //Parses json file into json structure called "j_complete"
    json j_complete = json::parse(jsonfile);

    //cout what it reads
    //std::cout << std::setw(4) << j_complete << "\n\n";
    //std::cout << "Size of JSON File: "<< j_complete.size() << "\n\n";
    return j_complete;
}

Node<Product> *FileHandler::createProductLinkedList(json input)
{
    Node<Product> *headPtr;

    ProductLinkedList pllm;

    for (int i = 0; i < input.size(); i++)
    {
        Product p;
        p.setCategoryName(input.at(i)["Category"].get<std::string>());
        p.setDesc(input.at(i)["Description"].get<std::string>());
        p.setID(input.at(i)["ID"].get<int>());
        p.setName(input.at(i)["Name"].get<std::string>());
        p.setPrice(input.at(i)["Price"].get<double>());
        p.setQuantity(input.at(i)["Quantity"].get<int>());
        pllm.insert(p);
    }

    headPtr = pllm.getNodeEnds();

    return headPtr;
}

json FileHandler::morphProductNodetoJSON(Node<Product> *productNode)
{
    // cout << "Head Node: " << productNode << endl;
    //Creates a product buffer object, p.
    Product p;
    //Creates product node next pointer;
    // ^ changed pointer to store node head
    Node<Product> *pNext = productNode;
    //Creates JSON object for product.
    json j;
    //Creates JSON buffer.
    json output = json::array({});
    //Assigns product from node to p.
    // productNode -> product = p;
    // productNode -> next = pNext;
    while (pNext->next != NULL)
    {
        pNext = pNext->next;

        p = pNext->data;

        j["Category"] = p.getCategory();
        j["Description"] = p.getDesc();
        j["ID"] = p.getID();
        j["Name"] = p.getName();
        j["Price"] = p.getPrice();
        j["Quantity"] = p.getQuantity();

        output.insert(output.end(), j);
    }
    return output;
}

Node<Purchase> *FileHandler::createPurchaseLinkedList(json input)
{
    Node<Purchase> *headPurchasePtr;

    PurchaseLinkedList purchaseLLM;
    
    for (int i = 0; i < input.size(); i++)
    {
        //Creates a new purchase object.
        Purchase purchase;
        //Sets ID
        purchase.setID(input.at(i)["ID"].get<int>());
        //Sets Date Time
        purchase.setDatetime(input.at(i)["DateTime"].get<std::string>());
        //Sets PaidAmount
        purchase.setPaidAmount(input.at(i)["PaidAmount"].get<double>());
        //Set ProductList
        vector<Product> productList;
        for (int j=0; j < input.at(i)["ProductList"].size(); j++)
        {
            Product p;
            p.setCategoryName(input.at(i)["ProductList"].at(j)["Category"].get<std::string>());
            p.setDesc(input.at(i)["ProductList"].at(j)["Description"].get<std::string>());
            p.setID(input.at(i)["ProductList"].at(j)["ID"].get<int>());
            p.setName(input.at(i)["ProductList"].at(j)["Name"].get<std::string>());
            p.setPrice(input.at(i)["ProductList"].at(j)["Price"].get<double>());
            p.setQuantity(input.at(i)["ProductList"].at(j)["Quantity"].get<int>());
            productList.emplace_back(p);
        }
        purchase.setProductList(productList);

        purchaseLLM.insert(purchase);
    }

    headPurchasePtr = purchaseLLM.getNodeEnds();

    return headPurchasePtr;
}

json FileHandler::morphPurchaseNodetoJSON(Node<Purchase> *purchaseNode)
{
    //Creates Buffer Purchase Object
    Purchase p;
    //Creates product node pointer to the next;
    Node<Purchase> *pNext = purchaseNode;
    //Creates JSON Buffers
    json output = json::array({});
    json purchase;

    while (pNext->next != NULL)
    {
        //Sets pNext, a pointer, to the next node
        pNext = pNext->next;
        //Assigns current node's data to purchase object
        p = pNext->data;
        //Retrieves purchase object's data and sets it to json buffer, purchase(individual purchase)
        purchase["DateTime"] = p.getDateTime();
        purchase["ID"] = p.getID();
        purchase["PaidAmount"] = p.getPaidAmount();

        //Creates a product list json buffer
        vector<Product> productListBuffer = *p.getProductList();
        json productListJSON = json::array({});
        for (int i = 0; i < productListBuffer.size(); i++)
        {
            json productJSON;
            Product product = productListBuffer.at(i);
            productJSON["Category"] = product.getCategory();
            productJSON["Description"] = product.getDesc();
            productJSON["ID"] = product.getID();
            productJSON["Name"] = product.getName();
            productJSON["Price"] = product.getPrice();
            productJSON["Quantity"] = product.getQuantity();
            productListJSON.insert(productListJSON.end(), productJSON);
        }
        purchase["ProductList"] = productListJSON;
        output.insert(output.end(), purchase);
    }
    return output;
}

void FileHandler::writeToFile(json jsonInput, string outputPath)
{
    std::string stringBuffer = jsonInput.dump();
    ofstream targetFile;
    targetFile.open(outputPath);
    targetFile << stringBuffer;
    targetFile.close();
}