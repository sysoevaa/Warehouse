#pragma once
#include <vector>
#include <cassert>
#include "Shop.h"

using std::vector;

class Marketplace : public IShopPoint
{
public:
	virtual void OnReceived(ShopQuery* query);
	virtual ShopQuery* CreateQuery();
	virtual void ApplyBalanceChange(int change);

	void Simulate(int deltaTime);
};

