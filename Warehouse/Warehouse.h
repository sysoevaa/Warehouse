#pragma once
#include <cassert>
#include <vector>

using std::vector;

class Config;
class Shop;
class Marketplace;
class Warehouse
{
public:
	static Warehouse* g_Instance;

	Warehouse(Config* cfg);

	void Simulate(int deltaTime);
	void Present();
	void Update();


private:
	int simTime;
	Config* config;

	const vector<Shop*>& GetShops();
	const vector<Marketplace*>& GetProviders();
};
