#include <algorithm>
#include <iostream>
#include <vector>

struct VertexInfo {
  int min_in;
  int min_out;
  bool touched;
  VertexInfo() : min_in(-1), min_out(-1), touched(false) {}
};

class Graph {
 private:
  int count_of_vertex_;
  std::vector<std::vector<std::pair<int, int>>> roads_;

 public:
  explicit Graph(std::vector<std::vector<std::pair<int, int>>>& roads) : count_of_vertex_(static_cast<int>(roads.size()) - 1),
                                                                              roads_(roads) {}

  std::vector<std::pair<int, int>> GetEdges(int vertex) const { return roads_[vertex]; }


  std::vector<int> FindBridges(std::vector<VertexInfo>& vertices);
};

void DFS(std::pair<int, int> edge, Graph& G, std::vector<int>& bridges, std::vector<VertexInfo>& vertices, int& time) {
  int vertex = edge.first;
  int parent = edge.second;
  vertices[vertex].min_in = time;
  vertices[vertex].touched = true;
  vertices[vertex].min_out = time++;
  for (std::pair x : G.GetEdges(vertex)) {
    int son = x.first;
    if (parent == son) {
      continue;
    }
    if (vertices[son].touched ) {
      vertices[vertex].min_out  = std::min(vertices[vertex].min_out , vertices[son].min_in);
    }
    if (!vertices[son].touched) {
      DFS({son, vertex}, G, bridges, vertices, time);
      vertices[vertex].min_out  = std::min(vertices[vertex].min_out , vertices[son].min_out);
      if (vertices[son].min_in == vertices[son].min_out) {
        int k = 0;
        auto edges = G.GetEdges(vertex);
        for (auto it = edges.begin(); it < edges.end(); ++it) {
          if ((*it).first == son) {
            ++k;
          }
        }
        if (k == 1) {
          bridges.push_back(x.second);
        }
      }
    }
  }
}

std::vector<int> Graph::FindBridges(std::vector<VertexInfo>& vertices) {
  std::vector<int> bridges;
  int time = 0;
  for (int i = 1; i < count_of_vertex_; ++i) {
    if (!vertices[i].touched) {
      DFS({i, -1}, *this, bridges, vertices, time);
    }
  }
  return bridges;
}

void PrintBridges(std::vector<int>& bridges) {
  std::sort(bridges.begin(), bridges.end());
  std::cout << bridges.size() << "\n";
  for (int i : bridges) {
    std::cout << i << " ";
  }
}


int main() {
  int count_of_vertex, count_of_edges;
  std::cin >> count_of_vertex >> count_of_edges;
  std::vector<std::vector<std::pair<int, int>>> roads(count_of_vertex +1);
  std::vector<int> test(count_of_vertex + 1, 0);
  for (int i = 1; i < count_of_edges + 1; ++i) {
    int a, b;
    std::cin >> a >> b;
    if (a != b) {
      roads[a].emplace_back(b, i);
      roads[b].emplace_back(a, i);
    }
  }
  Graph G(roads);
  std::vector<VertexInfo> vertices(count_of_vertex + 1);
  auto bridges = G.FindBridges(vertices);
  PrintBridges(bridges);
  return 0;
}