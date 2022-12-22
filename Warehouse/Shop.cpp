#include "Shop.h"
#include "Warehouse.h"
#include "Utils.h"

void Shop::Simulate(int deltaTime) {
    if (Utils::GetCurrentTime() < this->nextBuyTime)
        return;

    const auto& prods = Warehouse::g_Instance->GetAllDefs();

    ProductDefinition* def = prods[Utils::Random(0, prods.size() - 1)];
    Product* prod = new Product(def, Utils::Random(1, 20));
    int delta = Utils::Random(-100, 100);
    prod->SetPriceDelta(delta);
    cout << "Shop ordered " << prod->GetAmount() << " of " << prod->GetProductDef()->GetName() << " delta " << delta << endl;
    this->AddQuery(ShopQuery::Create(this, Warehouse::g_Instance, 1, prod, prod->GetTotalPrice()));

    this->nextBuyTime = Utils::GetCurrentTime() + Utils::Random(0, 2);
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
