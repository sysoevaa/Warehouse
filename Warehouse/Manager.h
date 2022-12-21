#pragma once
#include <vector>

#include "Shop.h"

using std::vector;

class Warehouse;
class Manager
{
public:
	Manager();

	void AddBalanceChange(int delta);
	void PushQuery(ShopQuery* q);

	void Think(Warehouse* warehouse);

private:
	std::vector<ShopQuery> pendingQueries;
	int totalProfit;
};

