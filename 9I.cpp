#include <iostream>
#include <vector>

void dfs(int vertex, std::vector<bool>& used,
         const std::vector<std::vector<int>>& edges) {
  if (used[vertex]) {
    return;
  }
  used[vertex] = true;
  for (int to : edges[vertex]) {
    if (!used[to]) {
      dfs(to, used, edges);
    }
  }
}

class BipartiteGraph {
 private:
  int count_of_vertices;
  int first_part_size;
  int second_part_size;
  std::vector<std::vector<int>> from_first_edges;

 public:
  explicit BipartiteGraph(int first_part_size, int second_part_size,
                          std::vector<std::vector<int>>& edges)
      : first_part_size(first_part_size),
        second_part_size(second_part_size),
        count_of_vertices(first_part_size + second_part_size),
        from_first_edges(edges) {}

  std::pair<std::vector<int>, std::vector<int>> FindMinimalControlSet();
};

std::pair<std::vector<int>, std::vector<int>>
BipartiteGraph::FindMinimalControlSet() {
  std::vector<int> match(first_part_size);
  for (int i = 0; i < first_part_size; ++i) {
    int matching_to_current_vertex;
    std::cin >> matching_to_current_vertex;
    if (matching_to_current_vertex != 0)
      match[i] = matching_to_current_vertex + first_part_size - 1;
    else {
      match[i] = -1;
    }
  }
  std::vector<std::vector<int>> edges(first_part_size + second_part_size);
  for (int i = 0; i < first_part_size; ++i) {
    for (int to : from_first_edges[i]) {
      if (to == match[i]) {
        edges[to].push_back(i);
      } else {
        edges[i].push_back(to);
      }
    }
  }
  std::vector<bool> used(first_part_size + second_part_size, false);
  for (int i = 0; i < first_part_size; ++i) {
    if (match[i] == -1) {
      dfs(i, used, edges);
    }
  }
  std::vector<int> first_part_coverage, second_part_coverage;
  for (int i = 0; i < first_part_size + second_part_size; ++i) {
    if (i < first_part_size && !used[i]) {
      first_part_coverage.push_back(i + 1);
    }
    if (i >= first_part_size && used[i]) {
      second_part_coverage.push_back(i - first_part_size + 1);
    }
  }
  return {first_part_coverage, second_part_coverage};
}

int main() {
  int first_part_size, second_part_size;
  std::cin >> first_part_size >> second_part_size;
  std::vector<std::vector<int>> first_edges(first_part_size);
  for (int i = 0; i < first_part_size; ++i) {
    int count_of_current_vertex_edges;
    std::cin >> count_of_current_vertex_edges;
    std::vector<int> edges_for_current_vertex(count_of_current_vertex_edges);
    for (int k = 0; k < count_of_current_vertex_edges; ++k) {
      std::cin >> edges_for_current_vertex[k];
      edges_for_current_vertex[k] += first_part_size - 1;
    }
    first_edges[i] = edges_for_current_vertex;
  }
  BipartiteGraph graph(first_part_size, second_part_size, first_edges);
  auto first_and_second_part = graph.FindMinimalControlSet();
  auto first_part_coverage = first_and_second_part.first;
  auto second_part_coverage = first_and_second_part.second;
  std::cout << first_part_coverage.size() + second_part_coverage.size() << "\n";
  std::cout << first_part_coverage.size() << " ";
  for (int i : first_part_coverage) {
    std::cout << i << " ";
  }
  std::cout << "\n" << second_part_coverage.size() << " ";
  for (int i : second_part_coverage) {
    std::cout << i << " ";
  }
  return 0;
}