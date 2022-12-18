#include <iostream>
#include <vector>
int FindSizeOfTree(int number) {
  int k = 1;
  while (k < number) {
    k = k * 2;
  }
  return k * 2;
}
class SegmentTree {
 public:
  explicit SegmentTree(std::vector<int> array, int n) {
    count_ = n;
    size_of_tree_ = FindSizeOfTree(count_);
    tree_ = std::vector<int>(size_of_tree_);
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

  void Update(int vertex, int new_value);
  int FindBigger(int start_position, int value) const;

 private:
  int count_;
  int size_of_tree_;
  std::vector<int> tree_;
  int FindLeftVision(int vertex) const;
  int FindRightVision(int vertex) const;
  int FindBiggerAssist(int vertex, int l, int r, int x, int maximum) const;
};

int SegmentTree::FindLeftVision(int vertex) const {
  while (vertex * 2 < size_of_tree_) {
    vertex *= 2;
  }
  vertex -= size_of_tree_ / 2;
  return vertex;
}

int SegmentTree::FindRightVision(int vertex) const {
  while ((vertex * 2) + 1 < size_of_tree_) {
    vertex = (vertex * 2) + 1;
  }
  vertex -= size_of_tree_ / 2;
  return vertex;
}

void SegmentTree::Update(int vertex, int new_value) {
  vertex += size_of_tree_ / 2;
  tree_[vertex] = new_value;
  vertex = vertex / 2;
  while (vertex > 0) {
    tree_[vertex] = std::max(tree_[vertex * 2], tree_[vertex * 2 + 1]);
    vertex = vertex / 2;
  }
}

int SegmentTree::FindBiggerAssist(int vertex, int l, int r, int x,
                                  int maximum) const {
  int a = count_ + 1, b = count_ + 1;
  if (tree_[1] >= x) {
    int left = vertex * 2, right = vertex * 2 + 1;
    if (left >= size_of_tree_) {
      maximum = 1 + vertex - (size_of_tree_ / 2);
      return maximum;
    }
    if (tree_[left] >= x && l <= FindRightVision(left)) {
      a = FindBiggerAssist(
          left, l,
          std::min(r, ((FindLeftVision(vertex) + FindRightVision(vertex)) / 2)),
          x, maximum);
    }
    if (a == count_ + 1 && tree_[right] >= x && FindLeftVision(right) <= r) {
      b = FindBiggerAssist(
          right,
          std::max(l, (FindLeftVision(vertex) + FindRightVision(vertex)) / 2),
          r, x, maximum);
    }
  }
  if (vertex == 1 && a == count_ + 1 && b == count_ + 1) {
    return -1;
  }
  return std::min(a, b);
}

int SegmentTree::FindBigger(int start_position, int value) const {
  return FindBiggerAssist(1, start_position - 1, count_ - 1, value, -1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int count_of_places, count_of_requests;
  std::cin >> count_of_places >> count_of_requests;
  std::vector<int> array(count_of_places);
  for (int i = 0; i < count_of_places; ++i) {
    std::cin >> array[i];
  }
  SegmentTree my_struct(array, count_of_places);
  for (int i = 0; i < count_of_requests; ++i) {
    int type, index, value;
    std::cin >> type >> index >> value;
    if (type == 0) {
      my_struct.Update(index - 1, value);
    }
    if (type == 1) {
      std::cout << my_struct.FindBigger(index, value) << "\n";
    }
  }
  return 0;
}
