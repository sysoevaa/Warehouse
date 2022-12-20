#include "Utils.h"

std::mt19937 Utils::rng = std::mt19937(std::chrono::high_resolution_clock::now().time_since_epoch().count());
int Utils::time = 0;

int Utils::Random(int low, int high) {
	std::uniform_int_distribution<> gen(low, high);
	return gen(rng);
}

int Utils::GetCurrentTime() {
	return Utils::time;
}

void Utils::SyncTime(int currentTime) {
	Utils::time = currentTime;
}