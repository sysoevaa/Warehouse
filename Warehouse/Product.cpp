#include "Product.h"

int Product::GetCost() {
    return cost_;
}

void Product::SetCost(int new_cost) {
    cost_ = new_cost;
}

int Product::GetType() {
    return type_;
}

void Product::SetType(int new_type) {
    type_ = new_type;
}

int Product::GetAmount() {
    return amount_;
}

void Product::SetAmount(int new_amount) {
    amount_ = new_amount;
}

const Product& Product::operator=(const Product& other) {
    type_ = other.type_;
    amount_ = other.amount_;
    cost_ = other.cost_;
    return *this;
}

