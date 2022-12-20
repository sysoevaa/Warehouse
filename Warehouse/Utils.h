#pragma once
#include <random>
#include <chrono>

class Utils
{
public:
	static int Random(int low, int high);
	static int GetCurrentTime();
	static void SyncTime(int currentTime);

private:
	static std::mt19937 rng;
	static int time;
};

