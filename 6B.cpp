#include <iostream>
#include <stack>
#include <vector>

int FindPos(std::vector<std::pair<int, int>>& dp, int number, int index) {
  int last = static_cast<int>(dp.size() - 1);
  if (dp.back().first >= number) {
    dp.emplace_back(number, index);
    return last + 1;
  }
  int l = 1, r = last;
  while (r - l > 1) {
    int m = (r + l) / 2;
    if (dp[m].first >= number) {
      l = m;
    } else {
      r = m;
    }
  }
  if (dp[l].first < number) {
    dp[l] = std::make_pair(number, index);
    return l;
  }
  dp[r] = std::make_pair(number, index);
  return r;
}

void CalculateDP(int count, std::vector<std::pair<int, int>>& dp,
                 std::vector<int>& positions, std::vector<int>& numbers) {
  for (int i = 2; i <= count; ++i) {
    int pos = FindPos(dp, numbers[i], i);
    positions[i] = dp[pos - 1].second;
  }
}

std::stack<int> CreateSequenceIndexes(std::vector<std::pair<int, int>>& dp,
                                      int max_length, std::vector<int>& positions) {
  std::stack<int> order;
  int last_index = dp[max_length].second;
  while (last_index != 0) {
    order.push(last_index);
    last_index = positions[last_index];
  }
  return order;
}

void PrintStack(std::stack<int> sequence) {
  while(!sequence.empty()) {
    std::cout << sequence.top() << " ";
    sequence.pop();
  }
}

std::stack<int> FindSequenceIndices(std::vector<int>& numbers, int count) {
  std::vector<std::pair<int, int>> dp(2);
//  дп хранит в ячейке i - наибольший возможный элемент последний элемент НнВП
//  длины i
  dp[1].first = numbers[1];
  dp[1].second = 1;
  std::vector<int> positions(count + 1);
  CalculateDP(count, dp, positions, numbers);
  int max_length = static_cast<int>(dp.size()) - 1;
  std::cout << max_length << "\n";
  return CreateSequenceIndexes(dp, max_length, positions);
}

int main() {
  int count;
  std::cin >> count;
  std::vector<int> numbers(count + 1);
  for (int i = 1; i <= count; ++i) {
    std::cin >> numbers[i];
  }
  PrintStack(FindSequenceIndices(numbers, count));
  return 0;
}