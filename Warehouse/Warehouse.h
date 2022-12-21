#pragma once
#include <cassert>
#include <iostream>
#include <vector>
#include "ShopQuery.h"
#include "Shop.h"

using std::vector;
using std::cout;
using std::endl;

class Config;
class Shop;
class Marketplace;
class ShopQuery;
class Manager;
class Warehouse : public IShopPoint
{
public:
	static Warehouse* g_Instance;

	Warehouse(Config* cfg);

	void Present();
	void Update();
	Config* GetConfig() { return this->config; }

	virtual void OnReceived(ShopQuery* query);
	virtual ShopQuery* CreateQuery();
	virtual void ApplyBalanceChange(int change);

	vector<ProductDefinition*> GetAllDefs();
private:
	vector<Product*> storage;
	int simTime;
	Config* config;
	vector<ShopQuery*> globalQueries;

	void ProcessQuery(ShopQuery* query);
	const vector<Shop*>& GetShops();
	Marketplace* GetProvider();
	Manager* GetManager();
	void Simulate(int deltaTime);

	friend class Manager;
};
