#include "Manager.h"
#include "Marketplace.h"
#include <algorithm>


Manager::Manager() {
    this->totalProfit = 0;
}

void Manager::RememberProfit() {
    this->profitHistory.push_back(this->totalProfit);
}

void Manager::AddBalanceChange(int delta) {
    this->totalProfit += delta;
}

void Manager::PushQuery(ShopQuery* q) {
    this->pendingQueries.push_back(*q);
}

void Manager::RemoveExpired(Warehouse* warehouse) {
    auto vv = warehouse->GetStorage();
    vector<Product*> prods;
    prods.reserve(vv.size());
    for (auto& v : vv) {
        if (v->IsValid()) {
            prods.push_back(v);
        }
    }
    warehouse->SetStorage(prods);
}


void Manager::OrderMissing(Warehouse* warehouse) {
    this->RemoveExpired(warehouse);

    std::map<ProductDefinition*, int> amounts;

    for (auto& v : warehouse->GetStorage()) {
        if (v->IsValid())
            amounts[v->GetProductDef()] += v->GetAmount();
    }
    for (auto& q : warehouse->globalQueries) {
        if (q->GetRequestor() == warehouse->GetProvider() && q->GetProduct()->IsValid()) {
            amounts[q->GetProduct()->GetProductDef()] += q->GetProduct()->GetAmount();
        }
    }

    for (ProductDefinition* def : warehouse->GetAllDefs()) {
        int has = amounts[def];
        int need = def->GetMaxAmount() * 0.75f;
        if (has < need) {
            // order
            int rnd = Utils::Random(2, 5); // order delay
            Product* prod = new Product(def, need - has);
            cout << "Ordering " << prod->GetAmount() << " of " << def->GetName() << endl;
            warehouse->ProcessQuery(ShopQuery::Create(warehouse->GetProvider(), warehouse, rnd, prod, prod->GetTotalPrice()));
        }
    }
}

void GreedyManager::Think(Warehouse* warehouse) {
    RemoveExpired(warehouse);
    std::sort(pendingQueries.begin(), pendingQueries.end(),
        [&](ShopQuery& a, ShopQuery& b) {
            return a.GetBalance() > b.GetBalance();
        });
    for (auto item : pendingQueries) {
        vector<Product*> exist;
        for (auto& pr : warehouse->GetStorage()) {
            if (pr->IsValid() && pr->GetProductDef() == item.GetProduct()->GetProductDef()) {
                exist.push_back(pr);
            }
        }
        std::sort(exist.begin(), exist.end(),
            [&](Product* a, Product* b) {
                return a->GetDays() < b->GetDays();
        });

        if (item.GetProduct()->GetPrice() < item.GetProduct()->GetProductDef()->GetPrice()) {
            if (exist.size() > 0 && exist[0]->GetDays() > 3) {
                delete item.GetProduct(); // selling with losses, only accept if it's about to expire
                continue;
            }
        }

        for (auto& product : exist) {
            int count = std::min(product->GetAmount(), item.GetProduct()->GetAmount());
            if (!count) continue;
            cout << "Sold " << count << " of " << product->GetProductDef()->GetName() << endl;
            warehouse->ApplyBalanceChange(count * item.GetProduct()->GetPrice());
            product->ChangeAmount(count);
            break;
        }

        delete item.GetProduct();
    }   
    pendingQueries.clear();

    this->OrderMissing(warehouse);
}

void EconomyManager::Think(Warehouse* warehouse) {
    std::sort(warehouse->GetStorage().begin(), warehouse->GetStorage().end(),
        [&](Product* a, Product* b) {
            return a->GetDays() < b->GetDays();
        });

    for (auto item : pendingQueries) {
        auto name = item.GetProduct()->GetProductDef()->GetId();
        for (auto& product : warehouse->GetStorage()) {
            if (product->GetProductDef()->GetId() == name) {
                int count = std::min(product->GetAmount(), item.GetProduct()->GetAmount());
                warehouse->ApplyBalanceChange(count * item.GetProduct()->GetPrice());
                product->ChangeAmount(count);
            }
        }
        delete item.GetProduct();
    }
    pendingQueries.clear();
    this->OrderMissing(warehouse);
}

