#pragma once
#include <vector>
#include <queue>
#include "Product.h"
#include "ShopQuery.h"

using std::vector;
using std::queue;
using std::pair;


class Shop : public IShopPoint {
public:
    void Simulate(int deltaTime);
    virtual void OnReceived(ShopQuery* query);
    virtual ShopQuery* CreateQuery();
    virtual void ApplyBalanceChange(int change);
    string GetName() { return this->displayName; }
    void SetName(const string& name) { this->displayName = name; }
    void SetId(int id) { this->id = id; };
    string GetId() { return "##" + std::to_string(this->id); }

    Shop(string name);
    void AddInterested(ProductDefinition* def);
private:
    void AddQuery(ShopQuery* query);

    vector<ProductDefinition*> interestedItems;
    queue<ShopQuery*> simQueries;
    string displayName;
    int nextBuyTime;
    int id;
};