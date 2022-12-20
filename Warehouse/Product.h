#pragma once
#include <random>
#include <chrono>
#include <string>
#include <set>

using std::set;
using std::string;

class ProductDefinition {
public:
    string GetName() { return this->displayName; }
    void SetId(int id) { this->id = id; }

    ProductDefinition(string name, int price);
private:
    int id;
    int price;
    string displayName;
};

class Product {
public: 
    Product(ProductDefinition* base, int amount, int life);

    ProductDefinition* GetProductDef() { return this->def; }
    int GetAmount() { return this->amount; }

    bool IsValid();
private:
    static set<Product*> allProducts;

    ProductDefinition* def;
    int amount;
    int life;
};

