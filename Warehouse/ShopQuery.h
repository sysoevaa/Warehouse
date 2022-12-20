#pragma once
#include "Utils.h"

class Product;
struct ShopQuery;
class IShopPoint {
public:
    virtual void OnReceived(ShopQuery* query) = 0;
    virtual ShopQuery* CreateQuery() = 0;
    virtual void ApplyBalanceChange(int delta) = 0;
};

class ShopQuery { // delayed RPC
public:
    bool IsFinished() { return this->left <= 0; }
    void Simulate(int deltaTime) { this->left -= deltaTime; }
    void Execute() { this->receiver->OnReceived(this); }
    int GetBalance() { return this->recvBalanceDelta; }
    IShopPoint* GetRequestor(){ return this->requestor; }

    static inline ShopQuery* Create(IShopPoint* from, IShopPoint* to, int delay, Product* item, int recvBalanceDelta) {
        ShopQuery* inst = new ShopQuery();
        inst->start = Utils::GetCurrentTime();
        inst->left = delay;
        inst->requestor = from;
        inst->receiver = to;
        inst->product = item;
        inst->recvBalanceDelta = recvBalanceDelta;
        return inst;
    }

private:
    ShopQuery() {};

    int start;
    int left;
    IShopPoint* requestor;
    IShopPoint* receiver;
    Product* product;
    int recvBalanceDelta;
};