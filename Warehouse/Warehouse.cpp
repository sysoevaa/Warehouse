#include "Warehouse.h"
#include "Config.h"

Warehouse* Warehouse::g_Instance = nullptr;

Warehouse::Warehouse(Config* cfg) {
	assert(cfg && "Cfg null");
	assert(!Warehouse::g_Instance && "only 1 warehouse instance is allowed lmao");
	this->config = cfg;
	this->simTime = 0;

	Warehouse::g_Instance = this;
}

void Warehouse::Present() {
	// render
}

void Warehouse::Simulate(int deltaTime) {
	// logic

}

void Warehouse::Update() {
	this->Simulate(this->config->GetSimStep());
	this->simTime += this->config->GetSimStep();
}

const vector<Shop*>& Warehouse::GetShops() {
	return this->config->GetShops();
}

const vector<Marketplace*>& Warehouse::GetProviders() {
	return this->config->GetProviders();
}