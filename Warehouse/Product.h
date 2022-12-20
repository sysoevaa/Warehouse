#pragma once
#include <random>
#include <chrono>

class Product {
public: 
    Product(int cost, int amount, int type, int days) : cost_(cost), amount_(amount),
        type_(type), days_(days) {}
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

