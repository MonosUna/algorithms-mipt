#include <iostream>
#include <vector>
#include <set>

class Network {
 public:
  explicit Network(std::vector<std::pair<int, int>>& other_edges, int count_of_vertices,
                   std::vector<std::pair<int, int>>& cap_and_cost);

  long long FindMinCost();

 private:
  struct Edge {
    int from;
    int to;
    int cap;
    long long flow;
    long long cost;

    explicit Edge(int from, int to, long long cap, long long cost) : from(from), to(to), cap(cap), flow(0), cost(cost) {}
    Edge() : from(0), to(0), cap(0), flow(0), cost(0) {}

    long long get_left_cap() const { return cap - flow; }

  };

  int num_of_other(int k) {
    return (k % 2 == 0) ? (k + 1) : (k - 1);
  }

  struct VertexInfo {
    std::vector<int> edges_nums;

    VertexInfo(): edges_nums(){ }
  };

  int count_of_vertices_;
  int count_of_edges_;
  int start;
  int finish;
  std::vector<Edge> edges;
  std::vector<VertexInfo> vertices;

  std::vector<long long> CalculateMinimalDistancesFromStartToAllVertices();

  std::pair<long long, long long> CalculateMinCostAndMaxFlow(std::vector<long long>& potentials);
};

std::vector<long long> Network::CalculateMinimalDistancesFromStartToAllVertices() {
  int max_value = 1'000'000;
  std::vector<std::vector<long long>> dp(count_of_vertices_ + 1,
                                         std::vector<long long>(count_of_vertices_ + 1, max_value));
  dp[start][0] = 0;
  for (int i = 1; i <= count_of_vertices_; ++i) {
    for (int vertex = start; vertex <= count_of_vertices_; ++vertex) {
      dp[vertex][i] = dp[vertex][i - 1];
      for (int edge : vertices[vertex].edges_nums) {
        int edge_num = num_of_other(edge);
        int from = edges[edge_num].from;
        long long cost = edges[edge_num].cost;
        if (edges[edge_num].get_left_cap() > 0 && (dp[vertex][i] > dp[from][i - 1] + cost)) {
          dp[vertex][i] = dp[from][i - 1] + cost;
        }
      }
    }
  }
  for (int i = 0; i < count_of_vertices_ + 1; ++i) {
    dp[count_of_vertices_][i] = dp[i][count_of_vertices_];
  }
  return dp[count_of_vertices_];
}

std::pair<long long, long long> Network::CalculateMinCostAndMaxFlow(std::vector<long long>& potentials) {
//  Используется алгоритм Дейкстры с потенциалами Джонсона
  long long max_value = 1'000'000;
  std::vector<long long> distances(count_of_vertices_ + 1, max_value);
  std::vector<int> prev_edge_num (count_of_vertices_ + 1, -1);
  std::vector<int> prev_vertex(count_of_vertices_ + 1, -1);
  distances[start] = 0;
  std::set<std::pair<int, int>> heap;
  heap.insert({distances[start], start});
  while(!heap.empty()) {
    int vertex = heap.begin()->second;
    heap.erase(heap.begin());
    for (int edge_num : vertices[vertex].edges_nums) {
      int to = edges[edge_num].to;
      long long cost = edges[edge_num].cost;
      long long new_cost = potentials[vertex] + cost - potentials[to];
      if (edges[edge_num].get_left_cap() > 0 && new_cost + distances[vertex] < distances[to]) {
        heap.erase({distances[to], to});
        heap.insert({distances[vertex] + new_cost, to});
        distances[to] = new_cost + distances[vertex];
        prev_edge_num[to] = edge_num;
        prev_vertex[to] = vertex;
      }
    }
  }
  potentials = distances;
  if (distances[finish] == max_value) {
    return {-1, -1};
  }
  long long min_cap = max_value;
  int cur_v = finish;
  while (cur_v != start) {
    int pred = prev_vertex[cur_v];
    int prev_edge = prev_edge_num[cur_v];
    min_cap = std::min(min_cap, edges[prev_edge].get_left_cap());
    cur_v = pred;
  }
  cur_v = finish;
  long long sum_cost = 0;
  while (cur_v != start) {
    int pred = prev_vertex[cur_v];
    int prev_edge = prev_edge_num[cur_v];
    edges[prev_edge].flow += min_cap;
    edges[num_of_other(prev_edge)].flow -= min_cap;
    sum_cost += (edges[prev_edge].cost * min_cap);
    cur_v = pred;
  }
  return {min_cap, sum_cost};
}

Network::Network(std::vector<std::pair<int, int>>& other_edges, int count_of_vertices,
                 std::vector<std::pair<int, int>>& cap_and_cost) {
  finish = count_of_vertices;
  start = 1;
  count_of_vertices_ = count_of_vertices;
  std::vector<VertexInfo> vertices1(count_of_vertices_ + 1);
  int e = 0;
  for (size_t i = 0; i < other_edges.size(); ++i) {
    auto x = other_edges[i];
    auto y = cap_and_cost[i];
    int from = x.first;
    int to = x.second;
    int cap = y.first;
    int cost = y.second;
    edges.emplace_back(from, to, cap, cost);
    edges.emplace_back(to, from, 0, -cost);
    vertices1[from].edges_nums.push_back(e);
    vertices1[to].edges_nums.push_back(e + 1);
    e += 2;
  }
  vertices = vertices1;
  count_of_edges_ = e;
}

long long Network::FindMinCost() {
  long long max_flow = 0;
  long long min_cost = 0;
  auto potentials = CalculateMinimalDistancesFromStartToAllVertices();
  while(true) {
    auto x = CalculateMinCostAndMaxFlow(potentials);
    if (x.first == -1) {
      return min_cost;
    }
    max_flow += static_cast<long long>(x.first);
    min_cost += x.second;
  }
}

int main() {
  int N, M;
  std::cin >> N >> M;
  std::vector<std::pair<int, int>> other_edges;
  std::vector<std::pair<int, int>> cap_and_cost;
  for (int i = 0; i < M; ++i) {
    int from, to, cap, cost;
    std::cin >> from >> to >> cap >> cost;
    other_edges.emplace_back(from, to);
    cap_and_cost.emplace_back(cap, cost);
  }
  Network net(other_edges, N, cap_and_cost);
  std::cout << net.FindMinCost();
}