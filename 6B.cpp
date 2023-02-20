#include <iostream>
#include <stack>
#include <vector>

void PrintAnswer(std::vector<std::pair<int, int>>& dp, int answer,
                 std::vector<int>& positions) {
  std::stack<int> order;
  int last_index = dp[answer].second;
  while (last_index != 0) {
    order.push(last_index);
    last_index = positions[last_index];
  }
  for (int i = 1; i <= answer; ++i) {
    std::cout << order.top() << " ";
    order.pop();
  }
}

int FindPos(std::vector<std::pair<int, int>>& array, int number, int index) {
  int last = static_cast<int>(array.size() - 1);
  if (array.back().first >= number) {
    array.push_back(std::make_pair(number, index));
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

int main() {
  int count, answer = 1;
  std::cin >> count;
  std::vector<std::pair<int, int>> dp(2);
  std::cin >> dp[1].first;
  dp[1].second = 1;
  std::vector<int> positions(count + 1);
  for (int i = 2; i <= count; ++i) {
    int num;
    std::cin >> num;
    int pos = FindPos(dp, num, i);
    positions[i] = dp[pos - 1].second;
    if (pos > answer) {
      ++answer;
    }
  }
  std::cout << answer << "\n";
  PrintAnswer(dp, answer, positions);
  return 0;
}