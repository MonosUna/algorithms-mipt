#include <iostream>
#include <stack>
#include <vector>

int FindPos(std::vector<std::pair<int, int>>& array, int number, int index) {
  int last = static_cast<int>(array.size() - 1);
  if (array.back().first >= number) {
    array.emplace_back(number, index);
    return last + 1;
  }
  int l = 1, r = last;
  while (r - l > 1) {
    int m = (r + l) / 2;
    if (array[m].first >= number) {
      l = m;
    } else {
      r = m;
    }
  }
  if (array[l].first < number) {
    array[l] = std::make_pair(number, index);
    return l;
  }
  array[r] = std::make_pair(number, index);
  return r;
}

int FindMaxLength(int count, std::vector<std::pair<int, int>>& dp,
                  std::vector<int>& positions, std::vector<int>& numbers) {
  int max_length = 1;
  for (int i = 2; i <= count; ++i) {
    int pos = FindPos(dp, numbers[i], i);
    positions[i] = dp[pos - 1].second;
    if (pos > max_length) {
      ++max_length;
    }
  }
  return max_length;
}

std::stack<int> FindSequence(std::vector<std::pair<int, int>>& dp,
                             int max_length, std::vector<int>& positions) {
  std::stack<int> order;
  int last_index = dp[max_length].second;
  while (last_index != 0) {
    order.push(last_index);
    last_index = positions[last_index];
  }
  return order;
}

void PrintSequence(std::stack<int> sequence, int max_length) {
  for (int i = 1; i <= max_length; ++i) {
    std::cout << sequence.top() << " ";
    sequence.pop();
  }
}

int main() {
  int count;
  std::cin >> count;
  std::vector<std::pair<int, int>> dp(2);
  std::vector<int> numbers(count + 1);
  for (int i = 1; i <= count; ++i) {
    std::cin >> numbers[i];
  }
  dp[1].first = numbers[1];
  dp[1].second = 1;
  std::vector<int> positions(count + 1);
  int max_length = FindMaxLength(count, dp, positions, numbers);
  std::cout << max_length << "\n";
  PrintSequence(FindSequence(dp, max_length, positions), max_length);
  return 0;
}