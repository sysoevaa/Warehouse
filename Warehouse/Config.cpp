#include "Config.h"
#include "Product.h"
#include "Shop.h"

Config* Config::CreateDefault() {
	Config* config = new Config();

	config->sim_step = 1;

	config->AddDef(new ProductDefinition("Product 1", 100));
	config->AddDef(new ProductDefinition("Product 2", 100));
	config->AddDef(new ProductDefinition("Product 3", 100));
	config->AddDef(new ProductDefinition("Product 4", 100));

	Shop* shop = new Shop();

	return config;
}

void Config::Present() {

}

void Config::AddDef(ProductDefinition* def) {
	this->allDefs.push_back(def);
	def->SetId(this->allDefs.size());
}

ProductDefinition* Config::GetProductDefById(int id) {
	if (id < 0 || id >= this->allDefs.size()) return nullptr;
	return this->allDefs[id];
}