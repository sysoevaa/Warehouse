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
	void DrawProducts();
	void DrawShops();
	void DrawProviders();


	int GetSimStep() { return this->sim_step; };
	const vector<Shop*>& GetShops() { return this->shops; }
	Marketplace* GetProvider() { return this->provider; }
	Manager* GetManager() { return this->manager; }

	ProductDefinition* GetProductDefByIndex(int id);
	const vector<ProductDefinition*>& GetAllProdDefs();

private:
	Config();
	void AddDef(ProductDefinition* def);
	void AddShop(Shop* shop);
	void DeleteShop(Shop* shop);

	int sim_step;

	vector<ProductDefinition*> allDefs;
	vector<Shop*> shops;
	Marketplace* provider;
	Manager* manager;
};

