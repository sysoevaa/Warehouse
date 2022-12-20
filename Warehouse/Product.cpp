#include "Product.h"

ProductDefinition::ProductDefinition(string name, int prc) {
    this->displayName = name;
    this->price = prc;
    this->id = 0;
}


Product::Product(ProductDefinition* base, int amount, int life) {
    this->def = base;
    this->amount = amount;
    this->life = life;
}

bool Product::IsValid() {
    return this->def && this->life >= 0;
}