#include <iostream>
#include <vector>

int Bit(int mask, int pos) { return ((mask >> (pos)) % 2); }

bool CheckCorrectness(int mask, int pos, std::vector<std::vector<int>>& matrix,
                      int height) {
  for (int j = 0; j < height; ++j) {
    if (Bit(mask, j) + matrix[pos][j] == 1) {
      return false;
    }
  }
  return true;
}

int FindPreviousMask(int mask, int first_el, int height) {
  int ans = first_el, last_bit = first_el;
  for (int i = 1; i < height; ++i) {
    int sum = last_bit + Bit(mask, i) + Bit(mask, i - 1);
    if (sum == 3 || sum == 0) {
      return -1;
    }
    last_bit = 0;
    if (sum == 1) {
      last_bit = 1;
      ans += (1 << i);
    }
  }
  return ans;
}

int FindCount(int height, std::vector<int>& prev_dp, int mod) {
  int count = 0;
  for (int i = 0; i < (1 << height); ++i) {
    count += prev_dp[i];
    count %= mod;
  }
  return count;
}

std::vector<int> CalculateDP(std::vector<std::vector<int>>& matrix, int mod) {
  int length = static_cast<int>(matrix.size());
  int height = static_cast<int>(matrix[0].size());
  std::vector<int> prev_dp(1 << height, 0), cur_dp(1 << height, 0);
  for (int mask = 0; mask < (1 << height); ++mask) {
    if (CheckCorrectness(mask, 0, matrix, height)) {
      prev_dp[mask] = 1;
    }
  }
  for (int column = 1; column < length; ++column) {
    std::vector<int> cur_dp(1 << height, 0);
    for (int mask = 0; mask < (1 << height); ++mask) {
      if (CheckCorrectness(mask, column, matrix, height)) {
        int prev_mask0 = FindPreviousMask(mask, 0, height);
        int prev_mask1 = FindPreviousMask(mask, 1, height);
        if (prev_mask0 != -1 &&
            CheckCorrectness(prev_mask0, column - 1, matrix, height)) {
          cur_dp[mask] += prev_dp[prev_mask0];
          cur_dp[mask] %= mod;
        }
        if (prev_mask1 != -1 &&
            CheckCorrectness(prev_mask1, column - 1, matrix, height)) {
          cur_dp[mask] += prev_dp[prev_mask1];
          cur_dp[mask] %= mod;
        }
      }
    }
    prev_dp = cur_dp;
  }
  return prev_dp;
}

int main() {
  int height, length, mod = 1'000'000'007;
  std::cin >> height >> length;
  std::vector<std::vector<int>> matrix(length, std::vector<int>(height, -1));
  for (int i = 0; i < height; ++i) {
    std::string row;
    std::cin >> row;
    for (int j = 0; j < length; ++j) {
      if (row[j] == '+') {
        matrix[j][i] = 1;
      }
      if (row[j] == '-') {
        matrix[j][i] = 0;
      }
    }
  }
  std::vector<int> last_column = CalculateDP(matrix, mod);
  std::cout << FindCount(height, last_column, mod);
  return 0;
}