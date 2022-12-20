#pragma once
#include <random>
#include <chrono>
#include <string>

using std::string;

class ProductDefinition {

    string GetName() { return this->displayName; }
    void SetId(int id) { this->id = id; }
private:
    int id;
    string displayName;
};

class Product {
public: 
    Product(ProductDefinition* base, int amount, int life) {}

    int GetCost();
    void SetCost(int new_cost);
    int GetType();
    void SetType(int new_type);
    int GetAmount();
    void SetAmount(int new_amount);
    int GetDays();
    void SetDays(int new_days);
private:
    int cost_, amount_, type_, days_;
};

