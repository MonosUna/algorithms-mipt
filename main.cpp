#include <iostream>
void SiftDown(long long* array, const int kSize, int current_element) {
  while (2 * current_element <= kSize) {
    int descendant = 2 * current_element;
    if (2 * current_element + 1 <= kSize &&
        array[2 * current_element] > array[2 * current_element + 1]) {
      descendant = 2 * current_element + 1;
    }
    if (array[current_element] <= array[descendant]) {
      break;
    }
    std::swap(array[descendant], array[current_element]);
    current_element = descendant;
  }
}
void SiftUp(long long* array, int cur_el) {
  while (cur_el != 1 && array[cur_el] < array[cur_el / 2]) {
    std::swap(array[cur_el], array[cur_el / 2]);
    cur_el = cur_el / 2;
  }
}
void DoRequests(long long* array, int& current_size, std::string input,
                const int kNumberOfRequest, long long* ptr) {
  if (input == "insert") {
    long long number;
    std::cin >> number;
    array[++current_size] = number;
    SiftUp(array, current_size);
    ptr[kNumberOfRequest] = number;
  }
  if (input == "getMin") {
    std::cout << array[1] << '\n';
  }
  if (input == "extractMin") {
    std::swap(array[1], array[current_size--]);
    SiftDown(array, current_size, 1);
  }
  if (input == "decreaseKey") {
    int num_of_request;
    long long difference;
    std::cin >> num_of_request >> difference;
    int node = 1;
    for (int i = 1; i <= current_size; ++i) {
      if (array[i] == ptr[num_of_request]) {
        array[i] -= difference;
        ptr[num_of_request] -= difference;
        node = i;
        break;
      }
    }
    SiftUp(array, node);
  }
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int count;
  std::cin >> count;
  long long* array = new long long[100'001];
  long long* ptr = new long long[count + 1];
  for (int i = 1; i <= count; i++) {
    ptr[i] = 1'000'000'001;
  }
  int cur_size = 0;
  for (int i = 1; i <= count; i++) {
    std::string type_of_input;
    std::cin >> type_of_input;
    DoRequests(array, cur_size, type_of_input, i, ptr);
  }
  delete[] array;
  delete[] ptr;
  return 0;
}
