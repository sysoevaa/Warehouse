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
    void SetLifeDays(int d) { this->defaultLife = std::max(1, d); }
    int GetPrice() { return this->price; }
    void SetPrice(int pr) { this->price = std::max(1, pr); }
    void SetId(int id) { this->id = id; }
    string GetId() { return "##" + std::to_string(this->id); }
    void SetMaxAmount(int am) { this->maxAmount = am; }
    int GetMaxAmount() { return this->maxAmount; }

    ProductDefinition(string name, int price, int life, int wareMax);
private:
    int id;
    int defaultLife;
    int price;
    int maxAmount;
    string displayName;
};

class Product {
public: 
    Product(ProductDefinition* base, int amount);
    ~Product();

    ProductDefinition* GetProductDef() { return this->def; }
    int GetAmount() { return this->amount; }
    int GetPrice() { return this->def->GetPrice() + this->priceDelta; }
    int GetTotalPrice() { return this->amount * this->GetPrice(); }
    bool IsValid();

    static void SimulateAll(int deltaTime);
    void ChangeAmount(int count);
    int GetDays();
    void SetPriceDelta(int dt) { this->priceDelta = dt; }


private:
    inline void Simulate(int deltaTime);

    static set<Product*> allProducts;

    ProductDefinition* def;
    int priceDelta;
    int amount;
    int life;
};

