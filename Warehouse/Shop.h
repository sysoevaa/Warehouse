#pragma once
#include "Product.h"
#include <vector>
#include <queue>

using std::vector;
using std::queue;

class IShopPoint;
struct ShopQuery {
    int start;
    int end;
    IShopPoint* requestor;
    IShopPoint* receiver;
    Product* product;
};

class IShopPoint {
public:
    virtual void OnReceived(ShopQuery* query) = 0;
    virtual ShopQuery* CreateQuery() = 0;
};

class Shop : IShopPoint {
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
};