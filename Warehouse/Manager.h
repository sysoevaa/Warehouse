#pragma once
class Manager
{
public:
	Manager();

	void AddBalanceChange(int delta);

private:
	int totalProfit;
};

