#include <iostream>
#include <vector>
#include <algorithm>

class DSU {
  std::vector<int> sets;
  std::vector<int> dimensions;

 public:
  DSU(int size)
      : sets(std::vector<int>(size + 1)),
        dimensions(std::vector<int>(size + 1, 0)) {
    for (int i = 1; i <= size; ++i) {
      sets[i] = i;
      dimensions[i] = 1;
    }
  }

  int find(int vertex) {
    if (sets[vertex] == vertex) {
      return vertex;
    }
    return sets[vertex] = find(sets[vertex]);
  }

  void union_(int vertex1, int vertex2) {
    int parent1 = find(vertex1);
    int parent2 = find(vertex2);
    if (dimensions[parent1] >= dimensions[parent2]) {
      sets[parent2] = parent1;
      dimensions[parent1] += parent2;
    } else {
      sets[parent1] = parent2;
      dimensions[parent2] += parent1;
    }
  }
};

int main() {
  int count_of_vertices;
  int count_of_edges;
  std::cin >> count_of_vertices >> count_of_edges;
  DSU set(count_of_vertices);
  std::vector<std::pair<int, std::pair<int, int>>> edges;
  for (int i = 1; i <= count_of_edges; ++i) {
    std::pair<int, std::pair<int, int>> my_pair;
    std::cin >> my_pair.second.first >> my_pair.second.second >> my_pair.first;
    edges.push_back(my_pair);
  }
  std::sort(edges.begin(), edges.end());
  int sum = 0;
  for (std::pair<int, std::pair<int, int>> edge : edges) {
    int first = edge.second.first;
    int second = edge.second.second;
    int weight = edge.first;
    if (set.find(first) != set.find(second)) {
      set.union_(first, second);
      sum += weight;
    }
  }
  std::cout << sum;
  return 0;
}