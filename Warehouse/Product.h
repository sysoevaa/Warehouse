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
    int GetLifeDays() { return this->defaultLife; }
    void SetId(int id) { this->id = id; }

    ProductDefinition(string name, int price, int life);
private:
    int id;
    int defaultLife;
    int price;
    string displayName;
};

class Product {
public: 
    Product(ProductDefinition* base, int amount);
    ~Product();

    ProductDefinition* GetProductDef() { return this->def; }
    int GetAmount() { return this->amount; }
    bool IsValid();

    static void SimulateAll(int deltaTime);
private:
    inline void Simulate(int deltaTime);

    static set<Product*> allProducts;

    ProductDefinition* def;
    int amount;
    int life;
};

