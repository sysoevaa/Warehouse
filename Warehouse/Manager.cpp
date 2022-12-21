#include "Manager.h"

Manager::Manager() {
	this->totalProfit = 0;
}

void Manager::AddBalanceChange(int delta) {
	this->totalProfit += delta;
}

void Manager::PushQuery(ShopQuery* q) {
	this->pendingQueries.push_back(*q);
}

void Manager::Think(Warehouse* inst) {
	
}