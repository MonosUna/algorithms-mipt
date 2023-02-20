#include <iostream>
#include <vector>

void PrintAnswer(std::vector<std::vector<int>>& positions,
                 std::vector<int>& prices, int num, int sum_price) {
  if (num == -1) {
    return;
  }
  if (positions[num][sum_price] == 1) {
    sum_price -= prices[num];
    --num;
    PrintAnswer(positions, prices, num, sum_price);
    std::cout << num + 2 << "\n";
  } else {
    --num;
    PrintAnswer(positions, prices, num, sum_price);
  }
}

int main() {
  int count_of_assignments, resources;
  std::cin >> count_of_assignments >> resources;
  std::vector<int> prises(count_of_assignments), values(count_of_assignments);
  std::vector<std::vector<int>> positions(count_of_assignments,
                                          std::vector<int>(resources + 1, 0));
  for (int i = 0; i < count_of_assignments; ++i) {
    std::cin >> prises[i];
  }
  for (int i = 0; i < count_of_assignments; ++i) {
    std::cin >> values[i];
  }
  std::vector<int> previous_dp(resources + 1, 0), last_dp(resources + 1, 0);
  for (int i = 0; i <= resources; ++i) {
    if (i < prises[0]) {
      previous_dp[i] = 0;
    } else {
      last_dp[i] = previous_dp[i] = values[0];
      positions[0][i] = 1;
    }
  }
  for (int i = 1; i < count_of_assignments; ++i) {
    for (int j = 0; j <= resources; ++j) {
      last_dp[j] = previous_dp[j];
      positions[i][j] = 0;
      if (j >= prises[i] &&
          last_dp[j] < previous_dp[j - prises[i]] + values[i]) {
        last_dp[j] = previous_dp[j - prises[i]] + values[i];
        positions[i][j] = 1;
      }
    }
    previous_dp = last_dp;
  }
  PrintAnswer(positions, prises, count_of_assignments - 1, resources);
  return 0;
}
