#pragma once
#include <vector>
#include <string>
#include <cassert>
#include "Shop.h"

using std::vector;
using std::string;

class Marketplace : public IShopPoint
{
public:
	Marketplace() { }

	virtual void OnReceived(ShopQuery* query);
	virtual ShopQuery* CreateQuery();
	virtual void ApplyBalanceChange(int change);

	void SetId(int id) { this->id = id; }
	string GetId() { return "##" + std::to_string(this->id); }

private:
	void Simulate(int deltaTime);

	int id;
};

