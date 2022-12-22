#pragma once
#include <vector>
#include "Shop.h"
#include "Warehouse.h"
#include "Config.h"

using std::vector;

class Warehouse;
class Manager {
public:
    Manager();

    void AddBalanceChange(int delta);
    void PushQuery(ShopQuery* q);
    int GetTotalProfit() { return this->totalProfit; }

    virtual void Think(Warehouse* warehouse) = 0;
    void OrderMissing(Warehouse* warehouse);
    void RemoveExpired(Warehouse* warehouse);
    const vector<float>& GetProfitHistory() { return this->profitHistory; }

protected:
    std::vector<ShopQuery> pendingQueries;
    int totalProfit;
    vector<float> profitHistory;
};

class GreedyManager : public Manager {
public:
    virtual void Think(Warehouse* warehouse);
};

class EconomyManager : public Manager {
public:
    virtual void Think(Warehouse* warehouse);
};