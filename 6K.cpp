#include <iostream>
#include <stack>
#include <vector>

std::vector<std::vector<int>> FindPositions(std::vector<int>& prices,
                                            std::vector<int>& values,
                                            int resources,
                                            int count_of_assignments) {
  std::vector<std::vector<int>> positions(count_of_assignments,
                                          std::vector<int>(resources + 1, 0));
  std::vector<int> previous_dp(resources + 1, 0), last_dp(resources + 1, 0);
  for (int i = 0; i <= resources; ++i) {
    if (i < prices[0]) {
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
      if (j >= prices[i] &&
          last_dp[j] < previous_dp[j - prices[i]] + values[i]) {
        last_dp[j] = previous_dp[j - prices[i]] + values[i];
        positions[i][j] = 1;
      }
    }
    previous_dp = last_dp;
  }
  return positions;
}

void FindSequence(std::vector<std::vector<int>>& positions,
                  std::stack<int>& sequence, std::vector<int>& prices, int num,
                  int sum_price) {
  if (num == -1) {
    return;
  }
  if (positions[num][sum_price] == 1) {
    sum_price -= prices[num];
    --num;
    sequence.push(num + 2);
    FindSequence(positions, sequence, prices, num, sum_price);
  } else {
    --num;
    FindSequence(positions, sequence, prices, num, sum_price);
  }
}

void DisplaySequence(std::stack<int>& sequence) {
  while (!sequence.empty()) {
    std::cout << sequence.top() << "\n";
    sequence.pop();
  }
}

int main() {
  int count_of_assignments, resources;
  std::cin >> count_of_assignments >> resources;
  std::vector<int> prices(count_of_assignments), values(count_of_assignments);
  std::vector<std::vector<int>> positions(count_of_assignments,
                                          std::vector<int>(resources + 1, 0));
  for (int i = 0; i < count_of_assignments; ++i) {
    std::cin >> prices[i];
  }
  for (int i = 0; i < count_of_assignments; ++i) {
    std::cin >> values[i];
  }
  positions = FindPositions(prices, values, resources, count_of_assignments);
  std::stack<int> sequence;
  FindSequence(positions, sequence, prices, count_of_assignments - 1,
               resources);
  DisplaySequence(sequence);
  return 0;
}
