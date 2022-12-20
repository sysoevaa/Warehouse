#include "Manager.h"

Manager::Manager() {
	this->totalProfit = 0;
}

void Manager::AddBalanceChange(int delta) {
	this->totalProfit += delta;
}