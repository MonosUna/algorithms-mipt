#include <iostream>
#include <vector>
void FindRemain(int num_of_iteration,
                  std::vector<std::pair<long long, int>>& array, int size) {
  for (int i = 1; i <= size; ++i) {
    long long divisible = 1;
    for (int j = 0; j < num_of_iteration; j++) {
      divisible = divisible * 100000;
    }
    int five_figures = ((array[i].first) / divisible) % 100'000;
    array[i].second = five_figures;
  }
}
int main() {
  int count;
  std::cin >> count;
  std::vector<std::pair<long long, int>> numbers(count + 1);
  std::vector<std::pair<long long, int>> answers(count + 1);
  for (int i = 1; i <= count; ++i) {
    long long number;
    std::cin >> number;
    answers[i] = (std::make_pair(0, 0));
    numbers[i] = (std::make_pair(number, 0));
  }
  for (int j = 0; j < 4; j++) {
    FindRemain(j, numbers, count);
    int* counts = new int[100'000];
    for (int i = 0; i < 100'000; ++i) {
      counts[i] = 0;
    }
    for (int i = 1; i <= count; ++i) {
      ++counts[numbers[i].second];
    }
    for (int i = 1; i < 100'000; ++i) {
      counts[i] += counts[i - 1];
    }
    for (int i = count; i >= 1; --i) {
      answers[counts[numbers[i].second]--] = numbers[i];
    }
    delete[] counts;
    numbers = answers;
  }
  for (int i = 1; i <= count; ++i) {
    std::cout << answers[i].first << "\n";
  }
  return 0;
}