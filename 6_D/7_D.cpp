//Вам задан ориентированный граф с N вершинами и M ребрами (1 ≤ N ≤ 20000, 1 ≤ M ≤ 200000). Найдите компоненты сильной связности заданного графа и топологически отсортируйте его конденсацию.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Graph {
 public:
  std::vector<size_t> components;
  size_t number_components;
  Graph(size_t points_number, size_t roads_number) {
    number_components = 0;
    graph_.resize(points_number + 1);
    reverse_graph_.resize(points_number + 1);
    components.assign(points_number + 1, 0);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    for (size_t i = 0; i < roads_number; i++) {
      size_t from;
      size_t destination;
      std::cin >> from >> destination;
      graph_[from].push_back(destination);
      reverse_graph_[destination].push_back(from);
    }
  }

  void FindComponents() {
    std::vector<bool> used(graph_.size(), false);
    std::vector<size_t> sort_by_out;
    for (size_t i = 1; i < graph_.size(); i++) {
      if (!used[i]) {
        SortByOut(i, used, sort_by_out);
      }
    }
    std::reverse(sort_by_out.begin(), sort_by_out.end());
    for (size_t vertex : sort_by_out) {
      if (components[vertex] == 0) {
        MarkComponents(vertex);
        number_components++;
      }
    }
  }

 private:
  std::vector<std::vector<size_t> > graph_;
  std::vector<std::vector<size_t> > reverse_graph_;

  void SortByOut(size_t vertex, std::vector<bool>& used,
                 std::vector<size_t>& sort_by_out) {
    used[vertex] = true;
    for (size_t destination : graph_[vertex]) {
      if (!used[destination]) {
        SortByOut(destination, used, sort_by_out);
      }
    }
    sort_by_out.push_back(vertex);
  }

  void MarkComponents(size_t vertex) {
    components[vertex] = number_components + 1;
    for (size_t destination : reverse_graph_[vertex]) {
      if (components[destination] == 0) {
        MarkComponents(destination);
      }
    }
  }
};

int main() {
  size_t points_number;
  size_t roads_number;
  std::cin >> points_number >> roads_number;
  Graph graph(points_number, roads_number);
  graph.FindComponents();
  std::cout << graph.number_components << "\n";
  for (size_t i = 1; i < graph.components.size(); i++) {
    std::cout << graph.components[i] << " ";
  }
}
