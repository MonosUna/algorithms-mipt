#include <iostream>

void FillCounting(int* counting, const int* array, int count) {
  for (int i = 0; i < count; ++i) {
    ++counting[array[i]];
  }
}

int main() {
  int count, order_statistics;
  std::cin >> count >> order_statistics;
  int* array = new int[count];
  std::cin >> array[0] >> array[1];
  for (int i = 2; i < count; ++i) {
    array[i] = (123 * array[i - 1] + 45 * array[i - 2]) % (10'004'321);
  }
  int* counting = new int[10'004'321]{0};
  FillCounting(counting, array, count);
  int k_cur = 0;
  for (int i = 0; i < 10'004'321; i++) {
    k_cur += counting[i];
    if (k_cur >= order_statistics) {
      std::cout << i;
      break;
    }
  }
  delete[] array;
  delete[] counting;
  return 0;
}