#include "Config.h"
#include "Product.h"
#include "Shop.h"
#include "Manager.h"

Config* Config::CreateDefault() {
	Config* config = new Config();

	config->sim_step = 1;

	config->AddDef(new ProductDefinition("Product 1", 100, 14));
	config->AddDef(new ProductDefinition("Product 2", 100, 14));
	config->AddDef(new ProductDefinition("Product 3", 100, 14));
	config->AddDef(new ProductDefinition("Product 4", 100, 14));

	Shop* shop = new Shop("Shawerma #1");
	config->AddShop(shop);


	config->manager = new Manager();
	return config;
}

void Config::Present() {
	// render
}

void Config::AddDef(ProductDefinition* def) {
	this->allDefs.push_back(def);
	def->SetId(this->allDefs.size());
}

void Config::AddProvider(Marketplace* market) {
	this->providers.push_back(market);
}
void Config::AddShop(Shop* shop) {
	this->shops.push_back(shop);
}

ProductDefinition* Config::GetProductDefById(int id) {
	if (id < 0 || id >= this->allDefs.size()) return nullptr;
	return this->allDefs[id];
}