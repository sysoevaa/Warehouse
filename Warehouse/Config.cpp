#include "Config.h"
#include "Product.h"
#include "Shop.h"
#include "Manager.h"
#include "Marketplace.h"

#include "imgui/imgui.h"

Config::Config() {
	this->manager = 0;
	this->provider = 0;
	this->sim_step = 1;
}

Config* Config::CreateDefault() {
	Config* config = new Config();

	config->sim_step = 1;

	config->AddDef(new ProductDefinition("Product 1", 100, 14, 20));
	config->AddDef(new ProductDefinition("Product 2", 100, 14, 20));
	config->AddDef(new ProductDefinition("Product 3", 100, 14, 20));
	config->AddDef(new ProductDefinition("Product 4", 100, 14, 20));

	config->AddShop(new Shop("Shawerma #1"));
	config->AddShop(new Shop("Shawerma #2"));
	config->AddShop(new Shop("Shawerma #3"));
	config->AddShop(new Shop("Shawerma #4"));
	config->AddShop(new Shop("Shawerma #5"));
	config->AddShop(new Shop("Shawerma #6"));
	config->AddShop(new Shop("Shawerma #7"));

	config->manager = new GreedyManager();
	config->provider = new Marketplace();
	return config;
}

const vector<ProductDefinition*>& Config::GetAllProdDefs() {
	return this->allDefs;
}

void Config::DrawShops() {
	// render
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 5));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 10));

	ImGui::BeginChild("Shops", ImVec2(300, 500), true);
	ImGui::Text("Shops");

	if (ImGui::BeginTable("Shops", 1, ImGuiTableFlags_Borders)) {
		for (auto& shop : this->GetShops()) {
			ImGui::TableNextRow();

			ImGui::TableNextColumn();
			char buf[256] = { 0 };
			strcpy_s(buf, shop->GetName().c_str());
			ImGui::SetNextItemWidth(150);
			ImGui::InputText(shop->GetId().c_str(), buf, sizeof(buf), ImGuiInputTextFlags_NoHorizontalScroll);
			shop->SetName(buf);

			ImGui::SameLine();
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);

			if (ImGui::Button(("Delete" + shop->GetId()).c_str())) {
				this->DeleteShop(shop);
				break;
			}
		}
		ImGui::EndTable();
	}

	if (ImGui::Button("Add new shop")) {
		Shop* newShop = new Shop("Unnamed shop");
		this->AddShop(newShop);
	}

	ImGui::EndChild();

	ImGui::PopStyleVar(2);
}

void Config::DrawProducts() {
	// render
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 5));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 10));

	ImGui::BeginChild("Products", ImVec2(300, 500), true);
	ImGui::Text("Products");

	if (ImGui::BeginTable("Products", 1, ImGuiTableFlags_Borders, ImVec2(300, 0))) {
		for (auto& def : this->allDefs) {

			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			char buf[256] = { 0 };
			strcpy_s(buf, def->GetName().c_str());
			ImGui::SetNextItemWidth(150);
			ImGui::InputText(def->GetId().c_str(), buf, sizeof(buf), ImGuiInputTextFlags_NoHorizontalScroll);
			def->SetName(buf);

			int price = def->GetPrice();
			ImGui::SetNextItemWidth(70);
			ImGui::InputInt(("Price" + def->GetId()).c_str(), &price, 1, 30);
			def->SetPrice(price);

			int days = def->GetLifeDays();
			ImGui::SetNextItemWidth(70);
			ImGui::InputInt(("Life days" + def->GetId()).c_str(), &days, 1, 3);
			def->SetLifeDays(days);

			int amount = def->GetMaxAmount();
			ImGui::SetNextItemWidth(70);
			ImGui::InputInt(("Max Amount" + def->GetId()).c_str(), &amount, 1, 200);
			def->SetMaxAmount(amount);
		}
		ImGui::EndTable();
	}

	if (ImGui::Button("Add new product")) {
		ProductDefinition* def = new ProductDefinition("Unnamed product", 100, 14, 30);
		this->AddDef(def);
	}

	ImGui::EndChild();

	ImGui::PopStyleVar(2);
}

void Config::DeleteShop(Shop* shop) {
	for (auto it = this->shops.begin(); it != this->shops.end(); ++it) {
		if (*it == shop) {
			this->shops.erase(it);
			break;
		}
	}
}

void Config::DrawProviders() {
	
}

void Config::AddDef(ProductDefinition* def) {
	static int defCount = 0;
	this->allDefs.push_back(def);
	def->SetId(++defCount);
}

void Config::AddShop(Shop* shop) {
	static int shopCount = 0;
	this->shops.push_back(shop);
	shop->SetId(++shopCount);
}

ProductDefinition* Config::GetProductDefByIndex(int id) {
	if (id < 0 || id >= this->allDefs.size()) return nullptr;
	return this->allDefs[id];
}