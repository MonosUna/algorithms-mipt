#include <cmath>
#include <iostream>
#include <vector>
int MaxDegreeOf2(int number) {
  int ans = 1;
  while (ans < number) {
    ans *= 2;
  }
  return ans / 2;
}

class SparseTable {
 public:
  explicit SparseTable(int count, std::vector<int> array) {
    size_ = count;
    Preprocessing(array);
  }

  int FindSecondStatistics(int left, int right) const;

 private:
  std::vector<std::vector<int>> table_;
  int size_;
  int FindMin(int left, int right) const;

  void Preprocessing(std::vector<int> array);
};

int SparseTable::FindMin(int left, int right) const {
  int length = right - left + 1;
  int column = log2(length - 1);
  if (length == 1) {
    column = 0;
  }
  if (column == 0) {
    if (table_[0][left] <= table_[0][right]) {
      return left;
    }
    return right;
  }
  if (table_[0][table_[column][left]] >
      table_[0][table_[column][right - MaxDegreeOf2(length) + 1]]) {
    return table_[column][right - MaxDegreeOf2(length) + 1];
  }
  return table_[column][left];
}

int SparseTable::FindSecondStatistics(int left, int right) const {
  int left_min = 1'000'000'000, right_min = 1'000'000'000;
  int place_of_min = FindMin(left, right);
  if (left <= place_of_min - 1) {
    left_min = table_[0][FindMin(left, place_of_min - 1)];
  }
  if (right >= place_of_min + 1) {
    right_min = table_[0][FindMin(place_of_min + 1, right)];
  }
  return std::min(left_min, right_min);
}

void SparseTable::Preprocessing(std::vector<int> array) {
  std::vector<int> input;
  input.push_back(0);
  for (int i = 1; i <= size_; i++) {
    input.push_back(array[i]);
  }
  table_.push_back(input);
  int indent = 1;
  if (1 <= std::log2(size_)) {
    std::vector<int> input2;
    input2.clear();
    input2.push_back(0);
    for (int i = 1; i <= size_; i++) {
      int right_border = std::min(i + indent, size_);
      if (table_[0][i] <= table_[0][right_border]) {
        input2.push_back(i);
      } else {
        input2.push_back(right_border);
      }
    }
    table_.push_back(input2);
    indent *= 2;
  }
  for (int k = 2; k <= std::log2(size_); k++) {
    std::vector<int> input1;
    input1.clear();
    input1.push_back(0);
    for (int i = 1; i <= size_; i++) {
      int right_border = std::min(i + indent, size_);
      if (table_[0][table_[k - 1][i]] <=
          table_[0][table_[k - 1][right_border]]) {
        input1.push_back(table_[k - 1][i]);
      } else {
        input1.push_back(table_[k - 1][right_border]);
      }
    }
    table_.push_back(input1);
    indent *= 2;
  }
}

int main() {
  int size, count_of_requests;
  std::cin >> size >> count_of_requests;
  std::vector<int> array(size + 1);
  for (int i = 1; i <= size; ++i) {
    std::cin >> array[i];
  }
  SparseTable my_struct(size, array);
  for (int i = 0; i < count_of_requests; ++i) {
    int left, right;
    std::cin >> left >> right;
    std::cout << my_struct.FindSecondStatistics(left, right) << "\n";
  }
  return 0;
}