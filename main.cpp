#include <iostream>

int FindSizeOfTree(int number) {
  int k = 1;
  while (k < number) {
    k = k * 2;
  }
  return k * 2;
}

class SegmentTree {
 private:
  int count_;
  int size_of_tree_;
  int ans_ = -1;
  int* tree_;
  int FindLeftVision(int vertex);
  int FindRightVision(int vertex);

 public:
  SegmentTree(const int array[], int n) {
    count_ = n;
    size_of_tree_ = FindSizeOfTree(count_);
    tree_ = new int[size_of_tree_];
    for (int i = 0; i < n; ++i) {
      tree_[i + size_of_tree_ / 2] = array[i];
    }
    while (n + size_of_tree_ / 2 < size_of_tree_) {
      tree_[n + size_of_tree_ / 2] = 0;
      ++n;
    }
    for (int i = size_of_tree_ / 2 - 1; i > 0; --i) {
      tree_[i] = std::max(tree_[i * 2], tree_[i * 2 + 1]);
    }
  }

  void MakeChanges(int vertex, int new_value);
  void FindBigger(int vertex, int l, int r, int x);
  int GetAnswer();
  ~SegmentTree() { delete[] tree_; }
};

int SegmentTree::FindLeftVision(int vertex) {
  while (vertex * 2 < size_of_tree_) {
    vertex *= 2;
  }
  vertex -= size_of_tree_ / 2;
  return vertex;
}

int SegmentTree::FindRightVision(int vertex) {
  while ((vertex * 2) + 1 < size_of_tree_) {
    vertex = (vertex * 2) + 1;
  }
  vertex -= size_of_tree_ / 2;
  return vertex;
}

void SegmentTree::MakeChanges(int vertex, int new_value) {
  vertex += size_of_tree_ / 2;
  tree_[vertex] = new_value;
  vertex = vertex / 2;
  while (vertex > 0) {
    tree_[vertex] = std::max(tree_[vertex * 2], tree_[vertex * 2 + 1]);
    vertex = vertex / 2;
  }
}

void SegmentTree::FindBigger(int vertex, int l, int r, int x) {
  if (ans_ == -1 && tree_[1] >= x) {
    if (vertex * 2 >= size_of_tree_) {
      ans_ = 1 + vertex - (size_of_tree_ / 2);
      return;
    }
    if (tree_[vertex * 2] >= x && l <= FindRightVision(2 * vertex)) {
      FindBigger(
          vertex * 2, l,
          std::min(r, ((FindLeftVision(vertex) + FindRightVision(vertex)) / 2)),
          x);
    }
    if (tree_[vertex * 2 + 1] >= x && FindLeftVision(2 * vertex + 1) <= r) {
      FindBigger(
          vertex * 2 + 1,
          std::max(l, (FindLeftVision(vertex) + FindRightVision(vertex)) / 2),
          r, x);
    }
  }
}

int SegmentTree::GetAnswer() {
  int answer = ans_;
  ans_ = -1;
  return answer;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int n, count_of_requests;
  std::cin >> n >> count_of_requests;
  int* array = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }
  SegmentTree my_struct(array, n);
  for (int i = 0; i < count_of_requests; ++i) {
    int type, index, value;
    std::cin >> type >> index >> value;
    if (type == 0) {
      my_struct.MakeChanges(index - 1, value);
    }
    if (type == 1) {
      my_struct.FindBigger(1, index - 1, n - 1, value);
      std::cout << my_struct.GetAnswer() << "\n";
    }
  }
  delete[] array;
  return 0;
}
