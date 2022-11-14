#include <iostream>
#include <vector>
struct MiniMax {
  int count;
  std::vector<std::pair<int, int>> min_heap;
  std::vector<std::pair<int, int>> max_heap;

  MiniMax() {
    count = 0;
    std::vector<std::pair<int, int>> array(200001);
    min_heap = array;
    max_heap = array;
  }

  void DoSwapInMin(int vertex1, int vertex2);

  void DoSwapInMax(int vertex1, int vertex2);

  void MaxSiftUp(int vertex);

  void MinSiftUp(int vertex);

  void MinSiftDown(int current_element);

  void MaxSiftDown(int current_element);

  void Insert(int number);

  void ExtractMin();

  void ExtractMax();

  void GetMin();

  void GetMax();

  void GetSize() const { std::cout << count << "\n"; }

  void DoClear();
};

void MiniMax::DoSwapInMin(int vertex1, int vertex2) {
  std::swap(max_heap[min_heap[vertex1].second].second,
            max_heap[min_heap[vertex2].second].second);
  std::swap(min_heap[vertex1], min_heap[vertex2]);
}

void MiniMax::DoSwapInMax(int vertex1, int vertex2) {
  std::swap(min_heap[max_heap[vertex1].second].second,
            min_heap[max_heap[vertex2].second].second);
  std::swap(max_heap[vertex1], max_heap[vertex2]);
}

void MiniMax::MaxSiftUp(int vertex) {
  while (vertex != 1 && max_heap[vertex].first > max_heap[vertex / 2].first) {
    DoSwapInMax(vertex, vertex / 2);
    vertex = vertex / 2;
  }
}

void MiniMax::MinSiftUp(int vertex) {
  while (vertex != 1 && min_heap[vertex].first < min_heap[vertex / 2].first) {
    DoSwapInMin(vertex, vertex / 2);
    vertex = vertex / 2;
  }
}

void MiniMax::MinSiftDown(int current_element) {
  while (2 * current_element <= count) {
    int descendant = 2 * current_element;
    if (2 * current_element + 1 <= count &&
        min_heap[2 * current_element].first >
            min_heap[2 * current_element + 1].first) {
      descendant = 2 * current_element + 1;
    }
    if (min_heap[current_element].first <= min_heap[descendant].first) {
      break;
    }
    DoSwapInMin(current_element, descendant);
    current_element = descendant;
  }
}

void MiniMax::MaxSiftDown(int current_element) {
  while (2 * current_element <= count) {
    int descendant = 2 * current_element;
    if (2 * current_element + 1 <= count &&
        max_heap[2 * current_element].first <
            max_heap[2 * current_element + 1].first) {
      descendant = 2 * current_element + 1;
    }
    if (max_heap[current_element].first >= max_heap[descendant].first) {
      break;
    }
    DoSwapInMax(current_element, descendant);
    current_element = descendant;
  }
}

void MiniMax::Insert(int number) {
  count++;
  min_heap[count] = std::make_pair(number, count);
  max_heap[count] = std::make_pair(number, count);
  MinSiftUp(count);
  MaxSiftUp(count);
  std::cout << "ok"
            << "\n";
}

void MiniMax::ExtractMin() {
  if (count == 0) {
    std::cout << "error"
              << "\n";
    return;
  }
  std::cout << min_heap[1].first << "\n";
  int position_of_min = min_heap[1].second;
  DoSwapInMax(position_of_min, count);
  DoSwapInMin(1, count);
  MaxSiftUp(position_of_min);
  --count;
  MinSiftDown(1);
}

void MiniMax::ExtractMax() {
  if (count == 0) {
    std::cout << "error"
              << "\n";
    return;
  }
  std::cout << max_heap[1].first << "\n";
  int position_of_max = max_heap[1].second;
  DoSwapInMin(position_of_max, count);
  DoSwapInMax(1, count);
  MinSiftUp(position_of_max);
  --count;
  MaxSiftDown(1);
}

void MiniMax::GetMin() {
  if (count == 0) {
    std::cout << "error"
              << "\n";
    return;
  }
  std::cout << min_heap[1].first << "\n";
}

void MiniMax::GetMax() {
  if (count == 0) {
    std::cout << "error"
              << "\n";
    return;
  }
  std::cout << max_heap[1].first << "\n";
}

void MiniMax::DoClear() {
  count = 0;
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
    my_struct.DoClear();
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