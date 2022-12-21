#include "Manager.h"
#include <algorithm>


Manager::Manager() {
    this->totalProfit = 0;
}

void Manager::AddBalanceChange(int delta) {
    this->totalProfit += delta;
}

void Manager::PushQuery(ShopQuery* q) {
    this->pendingQueries.push_back(*q);
}

void GreedyManager::Think(Warehouse* warehouse) {
    std::sort(pendingQueries.begin(), pendingQueries.end(),
        [&](ShopQuery& a, ShopQuery& b) {
            return a.GetBalance() > b.GetBalance();
        });
    for (auto item : pendingQueries) {
        auto name = item.GetProduct()->GetProductDef()->GetName();
        for (auto& product : warehouse->GetStorage()) {
            if (product->GetProductDef()->GetName() == name) {
                int count = std::min(product->GetAmount(), item.GetProduct()->GetAmount());
                warehouse->ApplyBalanceChange(count * item.GetProduct()->GetProductDef()->GetPrice());
                totalProfit += count * item.GetProduct()->GetProductDef()->GetPrice();
                product->ChangeAmount(count);
                if (product->GetAmount() <= 1) {
                    // query to marketplace;
                }
            }
        }
    }
}

void EconomyManager::Think(Warehouse* warehouse) {
    std::sort(pendingQueries.begin(), pendingQueries.end(),
        [&](ShopQuery& a, ShopQuery& b) {
            return a.GetProduct()->GetDays() < b.GetProduct()->GetDays();
        });
    for (auto item : pendingQueries) {
        auto name = item.GetProduct()->GetProductDef()->GetName();
        for (auto& product : warehouse->GetStorage()) {
            if (product->GetProductDef()->GetName() == name) {
                int count = std::min(product->GetAmount(), item.GetProduct()->GetAmount());
                warehouse->ApplyBalanceChange(count * item.GetProduct()->GetProductDef()->GetPrice());
                totalProfit += count * item.GetProduct()->GetProductDef()->GetPrice();
                product->ChangeAmount(count);
                if (product->GetAmount() <= 1) {
                    // query to marketplace;
                }
            }
        }
    }
}

