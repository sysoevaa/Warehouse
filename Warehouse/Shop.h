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

    Shop(string name);
    void AddInterested(ProductDefinition* def);
private:
    void AddQuery(ShopQuery* query);

    vector<ProductDefinition*> interestedItems;
    queue<ShopQuery*> simQueries;
    string displayName;
    int nextBuyTime;
};