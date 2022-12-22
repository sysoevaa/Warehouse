#include "Warehouse.h"
#include "Config.h"
#include "Product.h"
#include "Shop.h"
#include "Marketplace.h"
#include "Utils.h"
#include "Manager.h"

#include "imgui/imgui.h"

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
	ImGui::Text(("Current day: " + std::to_string(this->simTime)).c_str());
	ImGui::SameLine();
	if (ImGui::Button("Simulate 1 day"))
		this->wantsSimTime += 1;
	ImGui::Text(("Current profit: " + std::to_string(this->GetManager()->GetTotalProfit())).c_str());

	const auto& vl = this->GetManager()->GetProfitHistory();
	float(*fn)(void*, int) = [](void* data, int idx) { return *((float*)data + idx); };
	ImGui::PlotLines("Total profit", fn, (void*)vl.data(), vl.size(), 0, 0, FLT_MAX, FLT_MAX, ImVec2(0, 90));



	ImGuiTableFlags tableFlags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersH | ImGuiTableFlags_BordersOuterH |
		ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterV | ImGuiTableFlags_BordersInnerV |
		ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner;
	static bool display_headers = true;

	ImGui::Separator();
	ImGui::Text("Orders");
	ImGui::BeginChild("child", ImVec2(0, 300), true);
	if (ImGui::BeginTable("Orders", 3, tableFlags))
	{
		ImGui::TableSetupColumn("Product");
		ImGui::TableSetupColumn("Count");
		ImGui::TableSetupColumn("Price");
		ImGui::TableHeadersRow();

		for (int row = 0; row < this->globalQueries.size(); row++)
		{
			ShopQuery* query = this->globalQueries[row];
			if (!dynamic_cast<Shop*>(query->GetRequestor()))
				continue;
			ImGui::TableNextRow();

			for (int column = 0; column < 3; column++)
			{
				ImGui::TableSetColumnIndex(column);
				if (column == 0)
				{
					ImGui::TextUnformatted(query->GetProduct()->GetProductDef()->GetName().c_str());
				}
				else if (column == 1)
				{
					ImGui::TextUnformatted(std::to_string(query->GetProduct()->GetAmount()).c_str());
				}
				else if (column == 2)
				{
					ImGui::TextUnformatted(std::to_string(query->GetBalance()).c_str());
				}
			}
		}
		ImGui::EndTable();
	}
	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::Separator();
	ImGui::Text("Storage");
	ImGui::BeginChild("child1", ImVec2(0, 300), true);
	if (ImGui::BeginTable("Storage", 2, tableFlags))
	{
		if (display_headers)
		{
			ImGui::TableSetupColumn("Product");
			ImGui::TableSetupColumn("Expiration after");
			//ImGui::TableSetupColumn("Price");
			ImGui::TableHeadersRow();
		}
		for (auto type : this->storage) {
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::TextUnformatted(type->GetProductDef()->GetName().c_str());
			ImGui::TableSetColumnIndex(1);
			ImGui::TextUnformatted(std::to_string(type->GetDays()).c_str());
		}
		ImGui::EndTable();
	}
	ImGui::EndChild();
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
	this->GetManager()->RememberProfit();

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
	while (this->simTime < this->wantsSimTime) {
		cout << "----------------------------TIME " << this->simTime << endl;
		this->Simulate(this->config->GetSimStep());
		this->simTime += this->config->GetSimStep();
		Utils::SyncTime(this->simTime);
	}
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