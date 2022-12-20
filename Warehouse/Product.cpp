#include "Product.h"

set<Product*> Product::allProducts;

ProductDefinition::ProductDefinition(string name, int prc, int life) {
    this->displayName = name;
    this->price = prc;
    this->defaultLife = life;
    this->id = 0;
}


Product::Product(ProductDefinition* base, int amount) {
    this->def = base;
    this->amount = amount;
    this->life = base->GetLifeDays();
    Product::allProducts.insert(this);
}
Product::~Product() {
    Product::allProducts.erase(this);
}

bool Product::IsValid() {
    return this->def && this->life >= 0;
}

void Product::SimulateAll(int deltaTime) {
    for (auto& obj : Product::allProducts)
        obj->Simulate(deltaTime);
}

void Product::Simulate(int deltaTime) {
    this->life -= deltaTime;
}