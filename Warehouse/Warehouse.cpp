#include "Warehouse.h"
#include "Config.h"
#include "Product.h"
#include "Shop.h"
#include "Marketplace.h"
#include "Utils.h"
#include "Manager.h"

#include "imgui.h"

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
	ImGui::Text("Main window");

}

void Warehouse::Simulate(int deltaTime) {
	// logic
	Product::SimulateAll(deltaTime);

	vector<ShopQuery*> nextPending;
	nextPending.reserve(this->globalQueries.size());
	for (auto& query : this->globalQueries) {
		query->Simulate(deltaTime);
		if (query->IsFinished()) {
			query->Execute();
			delete query;
		}
		else {
			nextPending.push_back(query);
		}
	}
	this->globalQueries = nextPending;

	for (auto& shop : this->GetShops()) {
		shop->Simulate(deltaTime);
		while (ShopQuery* q = shop->CreateQuery()) {
			this->ProcessQuery(q);
		}
	}
	//
	this->GetManager()->Think(this);

	while (ShopQuery* q = this->CreateQuery()) {
		this->ProcessQuery(q);
	}
}

void Warehouse::ProcessQuery(ShopQuery* query) {
	if (query->IsFinished()) {
		query->Execute();
		delete query;
		return;
	}
	this->globalQueries.push_back(query);
}

void Warehouse::Update() {
	if (this->simTime > 50) return;
	cout << "----------------------------TIME " << this->simTime << endl;
	this->Simulate(this->config->GetSimStep());
	this->simTime += this->config->GetSimStep();
	Utils::SyncTime(this->simTime);
}

const vector<Shop*>& Warehouse::GetShops() {
	return this->config->GetShops();
}

Marketplace* Warehouse::GetProvider() {
	return this->config->GetProvider();
}
Manager* Warehouse::GetManager() {
	return this->config->GetManager();
}

void Warehouse::OnReceived(ShopQuery* query) {
	if (dynamic_cast<Marketplace*>(query->GetRequestor())) {
		this->storage.push_back(query->GetProduct());
		this->ApplyBalanceChange(-query->GetBalance()); // pay
		cout << "Received " << query->GetProduct()->GetAmount() << " of " << query->GetProduct()->GetProductDef()->GetName() << endl;
	}
	else if (dynamic_cast<Shop*>(query->GetRequestor())) {
		// hmn add profit, depends on amount we can ship next frame
		this->GetManager()->PushQuery(query);
	}
}

void Warehouse::ApplyBalanceChange(int change) {
	this->GetManager()->AddBalanceChange(change);
	cout << "Warehouse balance: " << this->GetManager()->GetTotalProfit() << endl;
}

ShopQuery* Warehouse::CreateQuery() {
	return nullptr;
}

vector<ProductDefinition*> Warehouse::GetAllDefs() {
	return this->config->GetAllProdDefs();
}

vector<Product*> Warehouse::GetStorage() {
	return storage;
}