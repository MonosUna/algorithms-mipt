// Дано K графов. В каждом найти минимальные расстояния от заданной вершины до
// остальных.

#include <iostream>
#include <set>
#include <vector>

class Graph {
 public:
  explicit Graph(std::vector<std::vector<std::pair<int, int>>>& roads)
      : count_of_vertices_(static_cast<int>(roads.size())), roads_(roads) {}

  std::vector<std::pair<int, int>> GetEdges(int vertex) const {
    return roads_[vertex];
  }

  int Count() const { return count_of_vertices_; }

 private:
  int count_of_vertices_;
  std::vector<std::vector<std::pair<int, int>>> roads_;
};

std::vector<int> CalculateMinimalDistances(const Graph& graph, int vertex,
                                           int max_value) {
  int count_of_vertices = graph.Count();
  std::vector<int> distances(count_of_vertices, max_value);
  distances[vertex] = 0;
  std::set<std::pair<int, int>> min_distances;
  for (int i = 0; i < count_of_vertices; ++i) {
    min_distances.insert({distances[i], i});
  }
  while (!min_distances.empty()) {
    std::pair min_pair = *min_distances.begin();
    min_distances.erase(min_pair);
    for (std::pair<int, int> edge : graph.GetEdges(min_pair.second)) {
      int value = distances[min_pair.second] + edge.second;
      if (value < distances[edge.first]) {
        min_distances.erase({distances[edge.first], edge.first});
        min_distances.insert({value, edge.first});
        distances[edge.first] = value;
      }
    }
  }
  return distances;
}

std::vector<std::vector<std::pair<int, int>>> FillRoads(int count_of_vertices,
                                                        int count_of_edges) {
  std::vector<std::vector<std::pair<int, int>>> roads(count_of_vertices);
  for (int i = 1; i < count_of_edges + 1; ++i) {
    int start;
    int finish;
    int distance;
    std::cin >> start >> finish >> distance;
    roads[start].emplace_back(finish, distance);
    roads[finish].emplace_back(start, distance);
  }
  return roads;
}

void PrintDistances(std::vector<int>& distances) {
  for (int distance : distances) {
    std::cout << distance << " ";
  }
  std::cout << "\n";
}

int main() {
  int count_of_maps;
  int start_vertex;
  const int kMaxValue = 2009000999;
  std::cin >> count_of_maps;
  for (int cur_map = 0; cur_map < count_of_maps; ++cur_map) {
    int count_of_vertices;
    int count_of_edges;
    std::cin >> count_of_vertices >> count_of_edges;
    auto roads = FillRoads(count_of_vertices, count_of_edges);
    std::cin >> start_vertex;
    Graph graph(roads);
    auto distances = CalculateMinimalDistances(graph, start_vertex, kMaxValue);
    PrintDistances(distances);
  }
}
