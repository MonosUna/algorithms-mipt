#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

bool Cmp(std::pair<std::pair<int, int>, int> pair1,
         std::pair<std::pair<int, int>, int> pair2) {
  if (pair1.first.first > pair2.first.first) {
    return true;
  }
  if (pair1.first.first < pair2.first.first) {
    return false;
  }
  return pair1.first.second < pair2.first.second;
}

struct VertexInfo {
  std::string color;
  int min_in;
  int min_out;
  bool touched;
  int num_of_component;
  VertexInfo() : color("WHITE"), min_in(-1), min_out(-1), touched(false) {}
  void ResetColor() { color = "WHITE"; }
};

class Graph {
 public:
  explicit Graph(std::vector<std::vector<int>>& roads)
      : count_of_vertices_(static_cast<int>(roads.size()) - 1), roads_(roads) {}
  std::vector<int> GetEdges(int vertex) const { return roads_[vertex]; }

  std::vector<std::vector<int>> GetReversedEdges() const;

  int Count() const { return count_of_vertices_; }

  std::pair<std::vector<int>, int> SearchConnectivityComponents();

 private:
  int count_of_vertices_;
  std::vector<std::vector<int>> roads_;

  std::vector<int> TopSort();
};

std::vector<std::vector<int>> Graph::GetReversedEdges() const {
  std::vector<std::vector<int>> reversed_roads(count_of_vertices_ + 1);
  for (int first = 1; first <= count_of_vertices_; ++first) {
    for (int second : roads_[first]) {
      if (first != second && std::find(reversed_roads[second].begin(),
                                       reversed_roads[second].end(),
                                       first) == reversed_roads[second].end()) {
        reversed_roads[second].push_back(first);
      }
    }
  }
  return reversed_roads;
}

void DFS(int vertex, const Graph& graph, int& time,
         std::vector<VertexInfo>& vertices) {
  ++time;
  vertices[vertex].color = "GRAY";
  vertices[vertex].min_in = time;
  for (int x : graph.GetEdges(vertex)) {
    if (vertices[x].color == "WHITE") {
      DFS(x, graph, time, vertices);
    }
  }
  vertices[vertex].min_out = time;
  vertices[vertex].touched = true;
  vertices[vertex].color = "BLACK";
}

std::vector<int> Graph::TopSort() {
  int count_of_vertices = Count();
  std::vector<VertexInfo> vertices(count_of_vertices + 1);
  std::vector<std::pair<std::pair<int, int>, int>> time_out;
  for (int i = 1; i <= count_of_vertices; ++i) {
    vertices[i].num_of_component = i;
  }
  int time = 0;
  for (int i = 1; i <= count_of_vertices; ++i) {
    if (!vertices[i].touched) {
      DFS(i, *this, time, vertices);
    }
  }
  for (int i = 1; i <= count_of_vertices; ++i) {
    time_out.push_back({{vertices[i].min_out, vertices[i].min_in}, i});
  }
  std::sort(time_out.begin(), time_out.end(), Cmp);

  std::vector<int> top_sorted_vertices;
  for (std::pair<std::pair<int, int>, int> time : time_out) {
    top_sorted_vertices.push_back(time.second);
  }
  return top_sorted_vertices;
}

void DFSwithGroupAssigment(
    int vertex, const Graph& graph, std::vector<VertexInfo>& vertices,
    int group, const std::vector<std::vector<int>>& reversed_roads) {
  vertices[vertex].color = "GRAY";
  for (int x : reversed_roads[vertex]) {
    if (vertices[x].color == "WHITE") {
      DFSwithGroupAssigment(x, graph, vertices, group, reversed_roads);
    }
  }
  vertices[vertex].touched = true;
  vertices[vertex].num_of_component = group;
  vertices[vertex].color = "BLACK";
}

std::pair<std::vector<int>, int> Graph::SearchConnectivityComponents() {
  std::vector<int> top_sorted = TopSort();
  std::vector<VertexInfo> vertices(count_of_vertices_ + 1);
  std::vector<std::vector<int>> reversed_roads = GetReversedEdges();
  int group = 1;
  for (int i : top_sorted) {
    if (!vertices[i].touched) {
      DFSwithGroupAssigment(i, *this, vertices, group, reversed_roads);
      ++group;
    }
  }
  std::vector<int> components(count_of_vertices_ + 1);
  for (int i = 0; i <= count_of_vertices_; ++i) {
    components[i] = vertices[i].num_of_component;
  }
  return {components, group - 1};
}

int main() {
  int count_of_vertex, count_of_edges;
  std::cin >> count_of_vertex >> count_of_edges;
  std::vector<std::vector<int>> roads(count_of_vertex + 1);
  for (int i = 0; i < count_of_edges; ++i) {
    int a, b;
    std::cin >> a >> b;
    if (a != b &&
        std::find(roads[a].begin(), roads[a].end(), b) == roads[a].end()) {
      roads[a].push_back(b);
    }
  }
  Graph graph(roads);
  auto groups = graph.SearchConnectivityComponents();
  std::cout << groups.second << "\n";
  for (auto it = groups.first.begin() + 1; it < groups.first.end(); ++it) {
    std::cout << *(it) << " ";
  }
  return 0;
}