#include "Clock.h"
#include <chrono>
#include <iostream>
#include <numeric>
#define CLOCK 0

namespace timer
{
  namespace
  {
    std::chrono::high_resolution_clock::time_point g_StartTime;
    std::chrono::high_resolution_clock::time_point g_EndTime;
    std::vector<std::chrono::microseconds>         times;
  } // namespace

  void StartTimer()
  {
    g_StartTime = std::chrono::high_resolution_clock::now();
  }

  void StopTimer(const char* function_name)
  {
    g_EndTime     = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(g_EndTime - g_StartTime);
    times.push_back(duration);
    if(times.size() % 10 == 0)
    {
      auto avg = std::accumulate(times.begin(), times.end(), std::chrono::microseconds{0});
      auto amount = times.size();
      std::cout << "Avg: " << avg / amount << "\n";
    }
#if CLOCK == 1
    std::cout << "Time taken by function (" << function_name << "): " << duration.count()
              << " microseconds\n";
#endif // CLOCK
  }
}