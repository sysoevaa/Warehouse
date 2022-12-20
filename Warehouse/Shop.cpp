#include "Shop.h"
#include "Warehouse.h"

void Shop::Simulate(int deltaTime) {
    /*
     std::vector<Product> query;
    std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> gen(10, 10000);
    for (auto item : interestedItems) {
        this->AddQuery(Product(gen(rng), gen(rng) % 50 + 1,
            gen(rng) % 17 + 1, gen(rng) % 30 + 1));
    }
    return query;
    */
}

void Shop::OnReceived(ShopQuery* query) {

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
}

void Shop::AddInterested(ProductDefinition* def) {
    // check exists
    this->interestedItems.push_back(def);
}