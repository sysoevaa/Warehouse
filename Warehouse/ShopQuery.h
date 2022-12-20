#pragma once
#include "Utils.h"

class Product;
struct ShopQuery;
class IShopPoint {
public:
    virtual void OnReceived(ShopQuery* query) = 0;
    virtual ShopQuery* CreateQuery() = 0;
};

struct ShopQuery { // delayed RPC
    int start;
    int left;
    IShopPoint* requestor;
    IShopPoint* receiver;
    Product* product;

    bool IsFinished() { return this->left <= 0; }
    void Simulate(int deltaTime) { this->left -= deltaTime; }
    void Execute() { this->receiver->OnReceived(this); }

    static ShopQuery* Create(IShopPoint* from, IShopPoint* to, int delay, Product* item) {
        ShopQuery* inst = new ShopQuery();
        inst->start = Utils::GetCurrentTime();
        inst->left = delay;
        inst->requestor = from;
        inst->receiver = to;
        inst->product = item;
        return inst;
    }

private:
    ShopQuery() {};
};