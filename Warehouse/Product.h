#pragma once

class Product {
public: 
    Product(int cost, int amount, int type) : cost_(cost), amount_(amount), type_(type) {}
    int GetCost();
    void SetCost(int new_cost);
    int GetType();
    void SetType(int new_type);
    int GetAmount();
    void SetAmount(int new_amount);
    const Product& operator=(const Product& other);
private:
    int cost_, amount_, type_;
};

