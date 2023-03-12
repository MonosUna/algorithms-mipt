#include <cmath>
#include <iostream>
#include <vector>

int FindMinimalCountOfAttempts(int floor, int count_of_planes) {
  std::vector<int> previous_dp(floor + 1, 0);
  //  dp[i][j] - минимальное число попыток, чтобы установить "плохой" этаж,
  //  если высота j, используя i самолетов. Храним 2 последних столбца дп.
  for (int i = 2; i <= floor; ++i) {
    previous_dp[i] = i - 1;
  }
  int min_attempts = previous_dp[floor];
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
    min_attempts = last_dp[floor];
  }
  if (count_of_planes == 0 && floor > 1) {
    min_attempts = -1;
  }
  return min_attempts;
}

int main() {
  int floor, count_of_planes;
  std::cin >> floor >> count_of_planes;
  int optimal_count = static_cast<int>(std::log2(floor)) + 1;
  if (count_of_planes > optimal_count) {
    count_of_planes = optimal_count;
  }
  std::cout << FindMinimalCountOfAttempts(floor, count_of_planes);
  return 0;
}