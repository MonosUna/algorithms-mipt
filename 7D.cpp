#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

int tm = 0;

void DFS(int vertex, std::vector<std::string>& colors,
         std::vector<std::vector<int>>& roads,
         std::vector<std::tuple<int, int, int>>& time,
         std::vector<int>& touched) {
  ++tm;
  colors[vertex] = "GRAY";
  std::get<1>(time[vertex]) = tm;
  for (int x : roads[vertex]) {
    if (colors[x] == "WHITE") {
      DFS(x, colors, roads, time, touched);
    }
  }
  std::get<0>(time[vertex]) = tm;
  touched[vertex] = 1;
  colors[vertex] = "BLACK";
}

std::vector<int> TopSort(int count_of_vertex,
                         std::vector<std::vector<int>>& roads) {
  std::vector<std::string> colors(count_of_vertex + 1, "WHITE");
  std::vector<std::tuple<int, int, int>> time(count_of_vertex + 1, {0, 0, 0});
  std::vector<int> touched(count_of_vertex + 1, 0);
  for (int i = 1; i <= count_of_vertex; ++i) {
    std::get<2>(time[i]) = i;
    if (touched[i] == 0) {
      DFS(i, colors, roads, time, touched);
    }
  }
  for (int i = 1; i <= count_of_vertex; ++i) {
    std::get<0>(time[i]) = count_of_vertex - std::get<0>(time[i]);
  }
  std::sort(time.begin(), time.end());
  std::vector<int> ans;
  for (auto it = time.begin() + 1; it < time.end(); it++) {
    ans.push_back(std::get<2>(*it));
  }
  return ans;
}

void DfsKosaraju(int vertex, std::vector<std::string>& colors,
                 std::vector<std::vector<int>>& reversed_roads,
                 std::vector<int>& touched, int group) {
  colors[vertex] = "GRAY";
  for (int x : reversed_roads[vertex]) {
    if (colors[x] == "WHITE") {
      DfsKosaraju(x, colors, reversed_roads, touched, group);
    }
  }
  touched[vertex] = group;
  colors[vertex] = "BLACK";
}

void Print(int group, std::vector<int>& touched) {
  std::cout << group << "\n";
  for (auto it = touched.begin() + 1; it < touched.end(); ++it) {
    std::cout << *(it) << " ";
  }
}

void Kosaraju(int count_of_vertex,
              std::vector<std::vector<int>>& reversed_roads,
              std::vector<int>& top_sorted) {
  std::vector<std::string> colors(count_of_vertex + 1, "WHITE");
  std::vector<int> touched(count_of_vertex + 1, 0);
  int group = 1;
  for (int i : top_sorted) {
    if (touched[i] == 0) {
      DfsKosaraju(i, colors, reversed_roads, touched, group);
      ++group;
    }
  }
  Print(group - 1, touched);
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
  std::vector<int> top_sorted = TopSort(count_of_vertex, roads);
  Kosaraju(count_of_vertex, reversed_roads, top_sorted);
  return 0;
}