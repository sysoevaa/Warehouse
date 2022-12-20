#pragma once
#include "Product.h"
#include <vector>

class Shop {
public:
    Shop(std::vector<int>& items) : possible_items_(items) {}
    std::vector<Product> GenerateQuery();

private:
    std::vector<int> possible_items_;
};