#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

struct Edge {
  int from;
  int to;
  double cap;
  double flow;

  Edge(int from, int to, double cap, double flow)
      : from(from), to(to), cap(cap), flow(flow) {}
  Edge() : from(0), to(0), cap(0.0), flow(0.0) {}

  double get_left_cap() const { return cap - flow; }
};

int num_of_other(int k) { return (k % 2 == 0) ? (k + 1) : (k - 1); }

struct VertexInfo {
  std::vector<int> edges_nums;
  int ptr;
  int group;

  VertexInfo() : edges_nums(), ptr(), group(-1) {}
};

void bfs(std::vector<VertexInfo>& vertices, const std::vector<Edge>& edges) {
  for (int i = 1; i < vertices.size(); ++i) {
    vertices[i].group = -1;
  }
  vertices[0].group = 0;
  std::queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int vertex = q.front();
    q.pop();
    for (int num : vertices[vertex].edges_nums) {
      int to = edges[num].to;
      if (edges[num].flow < edges[num].cap && vertices[to].group == -1) {
        vertices[to].group = vertices[vertex].group + 1;
        q.push(to);
      }
    }
  }
}

void dfs(int vertex, std::vector<bool>& used, const std::vector<Edge>& edges,
         const std::vector<VertexInfo>& vertices) {
  used[vertex] = true;
  for (int num : vertices[vertex].edges_nums) {
    int to = edges[num].to;
    if (edges[num].flow < edges[num].cap && !used[to]) {
      dfs(to, used, edges, vertices);
    }
  }
}

double dfsAddingFlow(int vertex, double current_flow,
                     std::vector<VertexInfo>& vertices,
                     std::vector<Edge>& edges) {
  int last = static_cast<int>(vertices.size()) - 1;
  if (vertex == last) {
    return current_flow;
  }
  while (vertices[vertex].ptr <
      static_cast<int>(vertices[vertex].edges_nums.size())) {
    int e_num = vertices[vertex].edges_nums[vertices[vertex].ptr];
    int to = edges[e_num].to;
    if (vertices[vertex].group + 1 != vertices[to].group ||
        std::abs(edges[e_num].get_left_cap()) < 0.00001) {
      vertices[vertex].ptr = vertices[vertex].ptr + 1;
      continue;
    }
    double x =
        dfsAddingFlow(to, std::min(current_flow, edges[e_num].get_left_cap()),
                      vertices, edges);
    if (std::abs(x) < 0.00001) {
      vertices[vertex].ptr = vertices[vertex].ptr + 1;
      continue;
    }
    edges[e_num].flow += x;
    edges[num_of_other(e_num)].flow -= x;
    return x;
  }
  return 0;
}

class network {
 public:
  network(double g, const std::vector<std::pair<int, int>>& other_edges,
          int count_of_vertices, const std::vector<int>& degrees) {
    finish = count_of_vertices + 1;
    count_of_vertices_ = finish + 1;
    std::vector<VertexInfo> vertices1(count_of_vertices_);
    int e = 0;
    int count_of_edges = static_cast<int>(other_edges.size());
    double edges_capacity = static_cast<double>(count_of_edges);
    for (std::pair x : other_edges) {
      int from = x.first;
      int to = x.second;
      edges.emplace_back(from, to, 1.0, 0.0);
      edges.emplace_back(to, from, 1.0, 0.0);
      vertices1[from].edges_nums.push_back(e);
      vertices1[to].edges_nums.push_back(e + 1);
      e += 2;
    }
    for (int i = 1; i <= count_of_vertices; ++i) {
      edges.emplace_back(0, i, edges_capacity, 0.0);
      edges.emplace_back(i, 0, 0.0, 0.0);
      vertices1[0].edges_nums.push_back(e);
      vertices1[i].edges_nums.push_back(e + 1);
      e += 2;
      edges.emplace_back(
          i, finish, edges_capacity + 2 * g - static_cast<double>(degrees[i]),
          0.0);
      edges.emplace_back(finish, i, 0.0, 0.0);
      vertices1[i].edges_nums.push_back(e);
      vertices1[finish].edges_nums.push_back(e + 1);
      e += 2;
    }
    vertices = vertices1;
  }

  std::vector<int> FindMinCut() {
    double max_start_flow = 100000.0;
    double max_flow = 0;
    while (true) {
      bfs(vertices, edges);
      if (vertices[finish].group == -1) {
        break;
      }
      for (int i = 0; i <= finish; ++i) {
        vertices[i].ptr = 0;
      }
      while (true) {
        double x = dfsAddingFlow(0, max_start_flow, vertices, edges);
        max_flow += x;
        if (std::abs(x) < 0.00001) {
          break;
        }
      }
    }
    for (int i = 0; i <= finish; ++i) {
      vertices[i].ptr = 0;
    }
    std::vector<int> vertices_in_min_cut;
    std::vector<bool> used(count_of_vertices_, false);
    dfs(0, used, edges, vertices);
    for (int i = 0; i < finish; ++i) {
      if (used[i]) {
        vertices_in_min_cut.push_back(i);
      }
    }
    return vertices_in_min_cut;
  }

 private:
  int count_of_vertices_;
  int start = 0;
  int finish;
  std::vector<Edge> edges;
  std::vector<VertexInfo> vertices;
};

std::vector<int> FindMaxDensitySubgraph(
    int count_of_vertices, int count_of_edges,
    const std::vector<std::pair<int, int>>& edges,
    const std::vector<int>& degrees) {
  double left = 0.0;
  auto right = static_cast<double>(count_of_edges);
  auto minimal_distance =
      1.0 / static_cast<double>(count_of_vertices * count_of_vertices -
          count_of_vertices);
  std::vector<int> vertices_in_subgraph;
  while (right - left >= minimal_distance) {
    double medium = (right + left) / 2;
    network net(medium, edges, count_of_vertices, degrees);
    auto vertices_in_min_cut = net.FindMinCut();
    if (vertices_in_min_cut.size() == 1) {
      right = medium;
    } else {
      vertices_in_subgraph = vertices_in_min_cut;
      left = medium;
    }
  }
  return vertices_in_subgraph;
}

int main() {
  int count_of_vertices, count_of_edges;
  std::cin >> count_of_vertices >> count_of_edges;
  std::vector<std::pair<int, int>> edges;
  std::vector<int> degrees(count_of_vertices + 1, 0);
  for (int e = 0; e < count_of_edges; ++e) {
    int to, from;
    std::cin >> from >> to;
    edges.emplace_back(to, from);
    degrees[from] += 1;
    degrees[to] += 1;
  }
  auto vertices_in_subgraph =
      FindMaxDensitySubgraph(count_of_vertices, count_of_edges, edges, degrees);
  if (count_of_edges == 0) {
    std::cout << 1 << "\n" << 1;
    return 0;
  }
  std::cout << vertices_in_subgraph.size() - 1 << "\n";
  for (size_t i = 1; i < vertices_in_subgraph.size(); ++i) {
    std::cout << vertices_in_subgraph[i] << "\n";
  }
}