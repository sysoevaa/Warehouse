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
    void SetName(string n) { this->displayName = n; }
    int GetLifeDays() { return this->defaultLife; }
    void SetLifeDays(int d) { this->defaultLife = d; }
    int GetPrice() { return this->price; }
    void SetPrice(int pr) { this->price = pr; }
    void SetId(int id) { this->id = id; }
    string GetId() { return "##" + std::to_string(this->id); }

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
    int GetTotalPrice() { return this->amount * this->def->GetPrice(); }
    bool IsValid();

    static void SimulateAll(int deltaTime);
private:
    inline void Simulate(int deltaTime);

    static set<Product*> allProducts;

    ProductDefinition* def;
    int amount;
    int life;
};

