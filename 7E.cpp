#include <algorithm>
#include <iostream>
#include <vector>

struct Graph {
 public:
  int count_of_vertex;
  int count_of_edges;
  std::vector<std::vector<std::pair<int, int>>> roads;
  std::vector<int> time;
  std::vector<int> min_in;
  std::vector<int> touched;
  std::vector<int> bridges;
  int timer = 0;
  Graph(int vertices, int edges, std::vector<std::vector<std::pair<int, int>>>& roads,
        std::vector<int> test) : count_of_vertex(vertices),
                                 count_of_edges(edges),
                                 roads(roads), time(test),
                                 min_in(test), touched(test),
                                 bridges(std::vector<int>()) { }

  void PrintBridges() {
    std::sort(bridges.begin(), bridges.end());

    std::cout << bridges.size() << "\n";
    for (int i : bridges) {
      std::cout << i << " ";
    }
  }

  bool isConnected() { return std::find(touched.begin() + 1, touched.end(), 0) == touched.end(); }
};

void DFS(int vertex, int parent, Graph& G) {
  G.time[vertex] = G.timer;
  G.touched[vertex] = 1;
  G.min_in[vertex] = G.timer++;
  for (std::pair x : G.roads[vertex]) {
    int son = x.first;
    if (parent == son) {
      continue;
    }
    if (G.touched[son] == 1) {
      G.min_in[vertex] = std::min(G.min_in[vertex], G.time[son]);
    }
    if (G.touched[son] == 0) {
      DFS(son, vertex, G);
      G.min_in[vertex] = std::min(G.min_in[vertex], G.min_in[son]);
      if (G.min_in[son] == G.time[son]) {
        int k = 0;
        for (auto it = G.roads[vertex].begin(); it < G.roads[vertex].end(); ++it) {
          if ((*it).first == son) {
            ++k;
          }
        }
        if (k == 1) {
          G.bridges.push_back(x.second);
        }
      }
    }
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
  Graph G(count_of_vertex, count_of_edges, roads, test);
  for (int i = 1; i < count_of_vertex; ++i) {
    if (G.touched[i] == 0) {
      DFS(i, -1, G);
    }
  }
  G.PrintBridges();
  return 0;
}