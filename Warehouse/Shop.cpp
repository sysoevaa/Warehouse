#include "Shop.h"
#include "Warehouse.h"
#include "Utils.h"

void Shop::Simulate(int deltaTime) {
    if (Utils::GetCurrentTime() < this->nextBuyTime || !this->interestedItems.size())
        return;

    ProductDefinition* def = this->interestedItems[Utils::Random(0, this->interestedItems.size() - 1)];
    Product* prod = new Product(def, Utils::Random(1, 20));
    this->AddQuery(ShopQuery::Create(this, Warehouse::g_Instance, 1, prod, prod->GetTotalPrice()));

    this->nextBuyTime = Utils::GetCurrentTime() + Utils::Random(0, 3);
}

void Shop::OnReceived(ShopQuery* query) {

}

void Shop::ApplyBalanceChange(int change) {
    // infinite money glitch
}

void Shop::AddQuery(ShopQuery* query) {
    this->simQueries.push(query);
}

ShopQuery* Shop::CreateQuery() {
    if (this->simQueries.empty()) return nullptr;
    auto cp = this->simQueries.front();
    this->simQueries.pop();
    return cp;
}

Shop::Shop(string name) {
    this->displayName = name;
    this->nextBuyTime = Utils::Random(0, 2);
}

void Shop::AddInterested(ProductDefinition* def) {
    // check exists
    this->interestedItems.push_back(def);
}