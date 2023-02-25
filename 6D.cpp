#include <cmath>
#include <iostream>
#include <vector>

int main() {
  int floor, count_of_planes;
  std::cin >> floor >> count_of_planes;
  int log2 = static_cast<int>(std::log2(floor));
  if (count_of_planes > log2) {
    count_of_planes = 1 + log2;
  }
  std::vector<int> previous_dp(floor + 1, 0);
  for (int i = 2; i <= floor; ++i) {
    previous_dp[i] = i - 1;
  }
  int answer = previous_dp[floor];
  for (int i = 2; i <= count_of_planes; ++i) {
    std::vector<int> last_dp(floor + 1, 0);
    last_dp[1] = 0;
    last_dp[2] = 1;
    int optimal_index = 1;
    for (int j = 3; j <= floor; ++j) {
      while (optimal_index <= j &&
          previous_dp[optimal_index] < last_dp[j - optimal_index]) {
        ++optimal_index;
      }
      last_dp[j] = std::min(std::max(previous_dp[optimal_index],
                                     last_dp[j - optimal_index]),
                            std::max(previous_dp[optimal_index + 1],
                                     last_dp[j - optimal_index - 1])) +
          1;
    }
    previous_dp = last_dp;
    answer = last_dp[floor];
  }
  if (count_of_planes == 0 && floor > 1) {
    std::cout << -1;
  } else {
    std::cout << answer;
  }
  return 0;
}