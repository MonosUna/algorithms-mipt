// необходимо узнать есть ли в графе отрицательный цикл, а если есть вывести его

#include <iostream>
#include <vector>

struct Graph {
 private:
  int count_of_vertices_;
  std::vector<std::vector<int>> roads_;

 public:
  explicit Graph(std::vector<std::vector<int>>& roads)
      : count_of_vertices_(static_cast<int>(roads.size())), roads_(roads) {}

  int Count() const { return count_of_vertices_; }

  std::vector<std::vector<int>> GetEdges() const { return roads_; }
};

int CheckForNegativeCycle(std::vector<std::vector<int>>& dp, int count) {
  for (int i = 0; i < count; ++i) {
    if (dp[i][count] < dp[i][count - 1]) {
      return i;
    }
  }
  return -1;
}

std::vector<int> FindCycle(const std::vector<std::vector<int>>& positions, int start,
                           int length) {
  std::vector<int> cycle = {start};
  for (int i = 0; i <= length; ++i) {
    cycle.push_back(positions[start][length - i]);
    start = positions[start][length - i];
    if (start == cycle[0]) {
      break;
    }
  }
  return cycle;
}

std::vector<int> CalculateDPandReturnCycle(const Graph& graph, int max_value) {
  int vertices = graph.Count();
  auto roads = graph.GetEdges();
  std::vector<std::vector<int>> dp(vertices,
                                   std::vector<int>(vertices + 1, max_value));
//  ячейка dp[i][j] показывает минимальное расстояние от 0 вершины до i длины j.
  std::vector<std::vector<int>> previous(vertices,
                                         std::vector<int>(vertices + 1, -1));
  dp[0][0] = 0;
  for (int i = 1; i <= vertices; ++i) {
    for (int vertex = 0; vertex < vertices; ++vertex) {
      dp[vertex][i] = dp[vertex][i - 1];
      previous[vertex][i] = previous[vertex][i - 1];
      for (int other = 0; other < vertices; ++other) {
        if (roads[other][vertex] != max_value &&
            dp[vertex][i] > dp[other][i - 1] + roads[other][vertex]) {
          dp[vertex][i] = dp[other][i - 1] + roads[other][vertex];
          previous[vertex][i] = other;
        }
      }
    }
  }
  int num = CheckForNegativeCycle(dp, vertices);
  std::vector<int> cycle;
  if (num != -1) {
    cycle = FindCycle(previous, num, vertices);
  }
  return cycle;
}

std::vector<std::vector<int>> FillRoads(int count_of_vertices, int max_value) {
  std::vector<std::vector<int>> roads(
      count_of_vertices, std::vector<int>(count_of_vertices, max_value));
  for (int j = 0; j < count_of_vertices; ++j) {
    for (int i = 0; i < count_of_vertices; ++i) {
      std::cin >> roads[j][i];
    }
  }
  return roads;
}

void PrintResult(std::vector<int>& cycle) {
  if (cycle.empty()) {
    std::cout << "NO"
              << "\n";
  } else {
    std::cout << "YES"
              << "\n"
              << cycle.size() << "\n";
    for (auto it = cycle.rbegin(); it < cycle.rend(); ++it) {
      std::cout << *it + 1 << " ";
    }
  }
}

int main() {
  const int kMaxValue = 100000;
  int count_of_vertices;
  std::cin >> count_of_vertices;
  auto roads = FillRoads(count_of_vertices, kMaxValue);
  Graph graph(roads);
  auto cycle = CalculateDPandReturnCycle(graph, kMaxValue);
  PrintResult(cycle);
}