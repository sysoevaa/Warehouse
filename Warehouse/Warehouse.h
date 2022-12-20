#pragma once
#include <cassert>
#include <vector>
#include "ShopQuery.h"
#include "Shop.h"

using std::vector;

class Config;
class Shop;
class Marketplace;
class ShopQuery;
class Warehouse : public IShopPoint
{
public:
	static Warehouse* g_Instance;

	Warehouse(Config* cfg);

	void Present();
	void Update();

	virtual void OnReceived(ShopQuery* query);
	virtual ShopQuery* CreateQuery();
private:
	void Simulate(int deltaTime);


	int simTime;
	Config* config;
	vector<ShopQuery*> globalQueries;

	void ProcessQuery(ShopQuery* query);
	const vector<Shop*>& GetShops();
	const vector<Marketplace*>& GetProviders();
};
