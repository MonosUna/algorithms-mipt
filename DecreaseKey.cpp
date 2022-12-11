#include <iostream>
#include <vector>
class Heap {
 public:
  explicit Heap(int count) {
    size_ = 0;
    array_ = std::vector<long long>(1, 0);
    ptr_ = std::vector<long long>(count + 1, 1'000'000'001);
  }
  void Insert(long long number, int number_of_request);
  void GetMin() const { std::cout << array_[1] << '\n'; };
  void ExtractMin();
  void DecreaseKey(int num_of_request, long long difference);
  
 private:
  int size_;
  std::vector<long long> array_;
  std::vector<long long> ptr_;
  void SiftDown(int current_element);
  void SiftUp(int current_element);
};

void Heap::SiftDown(int current_element) {
  while (2 * current_element <= size_) {
    int left = 2 * current_element, right = 2 * current_element + 1;
    int descendant = left;
    if (right <= size_ && array_[left] > array_[right]) {
      descendant = right;
    }
    if (array_[current_element] <= array_[descendant]) {
      break;
    }
    std::swap(array_[descendant], array_[current_element]);
    current_element = descendant;
  }
}

void Heap::SiftUp(int current_element) {
  while (current_element != 1 &&
         array_[current_element] < array_[current_element / 2]) {
    std::swap(array_[current_element], array_[current_element / 2]);
    current_element = current_element / 2;
  }
}

void Heap::Insert(long long number, int number_of_request) {
  array_.push_back(number);
  if (static_cast<int>(array_.size()) - 1 == size_) {
    array_.push_back(number);
  } else {
    array_[size_ + 1] = number;
  }
  size_++;
  SiftUp(size_);
  ptr_[number_of_request] = number;
}

void Heap::ExtractMin() {
  std::swap(array_[1], array_[size_--]);
  SiftDown(1);
}

void Heap::DecreaseKey(int num_of_request, long long difference) {
  int node = 1;
  for (int i = 1; i <= size_; ++i) {
    if (array_[i] == ptr_[num_of_request]) {
      array_[i] -= difference;
      ptr_[num_of_request] -= difference;
      node = i;
      break;
    }
  }
  SiftUp(node);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int count;
  std::cin >> count;
  Heap my_heap(count);
  for (int i = 1; i <= count; i++) {
    std::string type_of_input;
    std::cin >> type_of_input;
    if (type_of_input == "insert") {
      long long number;
      std::cin >> number;
      my_heap.Insert(number, i);
    }
    if (type_of_input == "getMin") {
      my_heap.GetMin();
    }
    if (type_of_input == "extractMin") {
      my_heap.ExtractMin();
    }
    if (type_of_input == "decreaseKey") {
      int num_of_request;
      long long difference;
      std::cin >> num_of_request >> difference;
      my_heap.DecreaseKey(num_of_request, difference);
    }
  }
  return 0;
}
