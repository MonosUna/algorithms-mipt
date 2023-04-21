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

struct Graph {
 public:
  int count_of_vertices;
  int count_of_edges;
  std::vector<std::vector<int>> roads;
  std::vector<std::vector<int>> reversed_roads;

  Graph(int vertices, int edges, std::vector<std::vector<int>>& roads,
        std::vector<std::vector<int>>& reversed_roads)
      : count_of_vertices(vertices),
        count_of_edges(edges),
        roads(roads),
        reversed_roads(reversed_roads) {}
};

struct VertexInfo {
  std::string color;
  int min_in;
  int min_out;
  bool touched;
  int num_of_component;
  VertexInfo() : color("WHITE"), min_in(-1), min_out(-1), touched(false) {}
  void ResetColor() { color = "WHITE"; }
};

void DFS(int vertex, Graph& graph, int& time,
         std::vector<VertexInfo>& vertices) {
  ++time;
  vertices[vertex].color = "GRAY";
  vertices[vertex].min_in = time;
  for (int x : graph.roads[vertex]) {
    if (vertices[x].color == "WHITE") {
      DFS(x, graph, time, vertices);
    }
  }
  vertices[vertex].min_out = time;
  vertices[vertex].touched = true;
  vertices[vertex].color = "BLACK";
}

std::vector<int> TopSort(Graph& graph) {
  int count_of_vertices = graph.count_of_vertices;
  std::vector<VertexInfo> vertices(count_of_vertices + 1);
  std::vector<std::pair<std::pair<int, int>, int>> time_out;
  for (int i = 1; i <= count_of_vertices; ++i) {
    vertices[i].num_of_component = i;
  }
  int time = 0;
  for (int i = 1; i <= count_of_vertices; ++i) {
    if (!vertices[i].touched) {
      DFS(i, graph, time, vertices);
    }
  }

  for (int i = 1; i <= count_of_vertices; ++i) {
    time_out.push_back({{vertices[i].min_out, vertices[i].min_in}, i});
  }
  std::sort(time_out.begin(), time_out.end(), Cmp);

  std::vector<int> ans;
  for (std::pair<std::pair<int, int>, int> time : time_out) {
    ans.push_back(time.second);
  }
  return ans;
}

void DfsKosaraju(int vertex, Graph& graph, std::vector<VertexInfo>& vertices,
                 int group) {
  vertices[vertex].color = "GRAY";
  for (int x : graph.reversed_roads[vertex]) {
    if (vertices[x].color == "WHITE") {
      DfsKosaraju(x, graph, vertices, group);
    }
  }
  vertices[vertex].touched = true;
  vertices[vertex].num_of_component = group;
  vertices[vertex].color = "BLACK";
}

void Print(int group, std::vector<int>& touched) {
  std::cout << group << "\n";
  for (auto it = touched.begin() + 1; it < touched.end(); ++it) {
    std::cout << *(it) << " ";
  }
}

void Kosaraju(int count_of_vertices, Graph& graph,
              std::vector<int>& top_sorted) {
  std::vector<VertexInfo> vertices(count_of_vertices + 1);
  int group = 1;
  for (int i : top_sorted) {
    if (!vertices[i].touched) {
      DfsKosaraju(i, graph, vertices, group);
      ++group;
    }
  }
  std::vector<int> components(count_of_vertices + 1);
  for (int i = 0; i <= count_of_vertices; ++i) {
    components[i] = vertices[i].num_of_component;
  }
  Print(group - 1, components);
}

int main() {
  int count_of_vertex, count_of_edges;
  std::cin >> count_of_vertex >> count_of_edges;
  std::vector<std::vector<int>> roads(count_of_vertex + 1),
      reversed_roads(count_of_vertex + 1);
  for (int i = 0; i < count_of_edges; ++i) {
    int a, b;
    std::cin >> a >> b;
    if (a != b &&
        std::find(roads[a].begin(), roads[a].end(), b) == roads[a].end()) {
      roads[a].push_back(b);
      reversed_roads[b].push_back(a);
    }
  }
  Graph graph(count_of_vertex, count_of_edges, roads, reversed_roads);
  std::vector<int> top_sorted = TopSort(graph);
  Kosaraju(count_of_vertex, graph, top_sorted);
  return 0;
}