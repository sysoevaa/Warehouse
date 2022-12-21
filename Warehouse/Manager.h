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

    virtual void Think(Warehouse* warehouse) = 0;

protected:
    std::vector<ShopQuery> pendingQueries;
    int totalProfit;
};

class GreedyManager : public Manager {
public:
    void Think(Warehouse* warehouse);
};

class EconomyManager : public Manager {
public:
    void Think(Warehouse* warehouse);
}