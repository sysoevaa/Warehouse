#pragma once
#include "Shop.h"
#include "Product.h"
#include "Marketplace.h"
#include <vector>

class Stock {
public: 
    Stock(std::vector<int>& capacity, int count_places) : capacity_(capacity),
        count_marketplace_(count_places), income_(0) {};
    void GetIncome(); 
    void Supply(std::vector<Product>& products);

private:
    int count_marketplace_;
    std::vector<int> capacity_; // max possible amount for each item
    std::vector<int> fill_; 
    int income_;
};

