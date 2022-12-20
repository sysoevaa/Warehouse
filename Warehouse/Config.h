#pragma once
#include <vector>
#include <map>

using std::vector;

class Shop;
class Marketplace;
class ProductDefinition;
class Manager;
class Config
{
public:
	static Config* CreateDefault();
	void Present();


	int GetSimStep() { return this->sim_step; };
	const vector<Shop*>& GetShops() { return this->shops; }
	const vector<Marketplace*>& GetProviders() { return this->providers; }
	Manager* GetManager() { return this->manager; }

	ProductDefinition* GetProductDefById(int id);

private:
	Config() {};
	void AddDef(ProductDefinition* def);
	void AddShop(Shop* shop);
	void AddProvider(Marketplace* market);

	int sim_step;

	vector<ProductDefinition*> allDefs;
	vector<Shop*> shops;
	vector<Marketplace*> providers;
	Manager* manager;
};

