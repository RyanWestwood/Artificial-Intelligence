#include "Clock.h"
#include <chrono>
#include <iostream>

namespace CLOCK{
	namespace {
		std::chrono::steady_clock::time_point g_StartTime;
		std::chrono::steady_clock::time_point g_EndTime;
	}

	void StartTimer() {
		g_StartTime = std::chrono::high_resolution_clock::now();
	}

	void StopTimer(const char* function_name) {
		g_EndTime = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(g_EndTime - g_StartTime);
		std::cout << "Time taken by function (" << function_name << "): " << duration.count() << " milliseconds\n";
	}
}