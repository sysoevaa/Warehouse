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

int Product::GetDays() {
    return days_;
}

void Product::SetDays(int new_days) {
    days_ = new_days;
}
