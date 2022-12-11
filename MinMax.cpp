#include <iostream>
#include <vector>
class MiniMax {
 public:
  MiniMax() {
    count_ = 0;
    std::vector<std::pair<int, int>> array(1);
    min_heap_ = array;
    max_heap_ = array;
  }
  void Insert(int number);
  void ExtractMin();
  void ExtractMax();
  void GetMin() const;
  void GetMax() const;
  void GetSize() const { std::cout << count_ << "\n"; }
  void Clear();

 private:
  int count_;
  std::vector<std::pair<int, int>> min_heap_;
  std::vector<std::pair<int, int>> max_heap_;
  void SwapInMin(int vertex1, int vertex2);
  void SwapInMax(int vertex1, int vertex2);
  void MaxSiftUp(int vertex);
  void MinSiftUp(int vertex);
  void MinSiftDown(int current_element);
  void MaxSiftDown(int current_element);
};

void MiniMax::SwapInMin(int vertex1, int vertex2) {
  std::swap(max_heap_[min_heap_[vertex1].second].second,
            max_heap_[min_heap_[vertex2].second].second);
  std::swap(min_heap_[vertex1], min_heap_[vertex2]);
}

void MiniMax::SwapInMax(int vertex1, int vertex2) {
  std::swap(min_heap_[max_heap_[vertex1].second].second,
            min_heap_[max_heap_[vertex2].second].second);
  std::swap(max_heap_[vertex1], max_heap_[vertex2]);
}

void MiniMax::MaxSiftUp(int vertex) {
  while (vertex != 1 && max_heap_[vertex].first > max_heap_[vertex / 2].first) {
    SwapInMax(vertex, vertex / 2);
    vertex = vertex / 2;
  }
}

void MiniMax::MinSiftUp(int vertex) {
  while (vertex != 1 && min_heap_[vertex].first < min_heap_[vertex / 2].first) {
    SwapInMin(vertex, vertex / 2);
    vertex = vertex / 2;
  }
}

void MiniMax::MinSiftDown(int current_element) {
  while (2 * current_element <= count_) {
    int left = 2 * current_element, right = 2 * current_element + 1;
    int descendant = left;
    if (right <= count_ && min_heap_[left].first > min_heap_[right].first) {
      descendant = right;
    }
    if (min_heap_[current_element].first <= min_heap_[descendant].first) {
      break;
    }
    SwapInMin(current_element, descendant);
    current_element = descendant;
  }
}

void MiniMax::MaxSiftDown(int current_element) {
  while (2 * current_element <= count_) {
    int left = 2 * current_element, right = 2 * current_element + 1;
    int descendant = left;
    if (right <= count_ && max_heap_[left].first < max_heap_[right].first) {
      descendant = right;
    }
    if (max_heap_[current_element].first >= max_heap_[descendant].first) {
      break;
    }
    SwapInMax(current_element, descendant);
    current_element = descendant;
  }
}

void MiniMax::Insert(int number) {
  count_++;
  if (count_ == static_cast<int>(min_heap_.size())) {
    min_heap_.push_back(std::make_pair(number, count_));
    max_heap_.push_back(std::make_pair(number, count_));
  } else {
    min_heap_[count_] = std::make_pair(number, count_);
    max_heap_[count_] = std::make_pair(number, count_);
  }
  MinSiftUp(count_);
  MaxSiftUp(count_);
  std::cout << "ok"
            << "\n";
}

void MiniMax::ExtractMin() {
  if (count_ == 0) {
    std::cout << "error"
              << "\n";
    return;
  }
  std::cout << min_heap_[1].first << "\n";
  int position_of_min = min_heap_[1].second;
  SwapInMax(position_of_min, count_);
  SwapInMin(1, count_);
  MaxSiftUp(position_of_min);
  --count_;
  MinSiftDown(1);
}

void MiniMax::ExtractMax() {
  if (count_ == 0) {
    std::cout << "error"
              << "\n";
    return;
  }
  std::cout << max_heap_[1].first << "\n";
  int position_of_max = max_heap_[1].second;
  SwapInMin(position_of_max, count_);
  SwapInMax(1, count_);
  MinSiftUp(position_of_max);
  --count_;
  MaxSiftDown(1);
}

void MiniMax::GetMin() const {
  if (count_ == 0) {
    std::cout << "error"
              << "\n";
    return;
  }
  std::cout << min_heap_[1].first << "\n";
}

void MiniMax::GetMax() const {
  if (count_ == 0) {
    std::cout << "error"
              << "\n";
    return;
  }
  std::cout << max_heap_[1].first << "\n";
}

void MiniMax::Clear() {
  count_ = 0;
  std::cout << "ok"
            << "\n";
}

void DoRequest(std::string request, MiniMax& my_struct) {
  if (request == "insert") {
    int number;
    std::cin >> number;
    my_struct.Insert(number);
  }
  if (request == "extract_min") {
    my_struct.ExtractMin();
  }
  if (request == "extract_max") {
    my_struct.ExtractMax();
  }
  if (request == "get_min") {
    my_struct.GetMin();
  }
  if (request == "get_max") {
    my_struct.GetMax();
  }
  if (request == "size") {
    my_struct.GetSize();
  }
  if (request == "clear") {
    my_struct.Clear();
  }
}

int main() {
  int count_of_requests;
  MiniMax mini_max;
  std::cin >> count_of_requests;
  for (int i = 0; i < count_of_requests; ++i) {
    std::string request;
    std::cin >> request;
    DoRequest(request, mini_max);
  }
  return 0;
}
