#include <iostream>
#include <vector>
struct BigInteger {
  int size;
  std::vector<std::pair<long long, int>> array;
  std::vector<std::pair<long long, int>> ans;
  BigInteger(int number) { size = number; }
  void DoSecondPair(int num_of_iteration);
  void SortBasket();
  void GiveAnswer();
  void DefineArrays(std::vector<std::pair<long long, int>> number,
                    std::vector<std::pair<long long, int>> answer);
};

void BigInteger::DefineArrays(std::vector<std::pair<long long, int>> number,
                              std::vector<std::pair<long long, int>> answer) {
  ans = answer;
  array = number;
}

void BigInteger::SortBasket() {
  for (int j = 0; j < 4; j++) {
    DoSecondPair(j);
    int* count = new int[100'000];
    for (int i = 0; i < 100'000; ++i) {
      count[i] = 0;
    }
    for (int i = 1; i <= size; ++i) {
      ++count[array[i].second];
    }
    for (int i = 1; i < 100'000; ++i) {
      count[i] += count[i - 1];
    }
    for (int i = size; i >= 1; --i) {
      ans[count[array[i].second]--] = array[i];
    }
    delete[] count;
    array = ans;
  }
}

void BigInteger::DoSecondPair(int num_of_iteration) {
  for (int i = 1; i <= size; ++i) {
    long long divisible = 1;
    for (int j = 0; j < num_of_iteration; j++) {
      divisible = divisible * 100000;
    }
    int five_figures = ((array[i].first) / divisible) % 100'000;
    array[i].second = five_figures;
  }
}

void BigInteger::GiveAnswer() {
  for (int i = 1; i <= size; ++i) {
    std::cout << ans[i].first << " ";
  }
}

int main() {
  int count;
  std::cin >> count;
  BigInteger my_struct(count);
  std::vector<std::pair<long long, int>> numbers(count + 1);
  std::vector<std::pair<long long, int>> answers(count + 1);
  for (int i = 1; i <= count; ++i) {
    long long number;
    std::cin >> number;
    answers[i] = (std::make_pair(0, 0));
    numbers[i] = (std::make_pair(number, 0));
  }
  my_struct.DefineArrays(numbers, answers);
  my_struct.SortBasket();
  my_struct.GiveAnswer();
  return 0;
}