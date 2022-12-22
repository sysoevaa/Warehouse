#include "Product.h"

set<Product*> Product::allProducts;

ProductDefinition::ProductDefinition(string name, int prc, int life, int mx) {
    this->displayName = name;
    this->price = prc;
    this->defaultLife = life;
    this->maxAmount = mx;
    this->id = 0;
}


Product::Product(ProductDefinition* base, int amount) {
    this->def = base;
    this->amount = amount;
    this->priceDelta = 0;
    this->life = base->GetLifeDays();
    Product::allProducts.insert(this);
}
Product::~Product() {
    Product::allProducts.erase(this);
}

bool Product::IsValid() {
    return this->def && this->life >= 0 && this->amount > 0;
}

void Product::SimulateAll(int deltaTime) {
    for (auto& obj : Product::allProducts)
        obj->Simulate(deltaTime);
}

void Product::Simulate(int deltaTime) {
    this->life -= deltaTime;
}

void Product::ChangeAmount(int count) {
    this->amount -= count;
}

int Product::GetDays() {
    return this->life;
}