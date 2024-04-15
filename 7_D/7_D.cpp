/* Задан ориентированный граф. Найдите компоненты сильной связности заданного графа и топологически отсортируйте его конденсацию.
   1 ≤ points_number ≤ 20000
   1 ≤ roads_number ≤ 200000
*/

#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
 public:
  std::vector<std::vector<size_t>> graph;
  std::vector<std::vector<size_t>> reverse_graph;

  void operator>>(std::istream& input) {
    size_t points_number;
    size_t roads_number;
    input >> points_number;
    input >> roads_number;
    graph.resize(points_number + 1);
    reverse_graph.resize(points_number + 1);
    for (size_t i = 0; i < roads_number; i++) {
      size_t from;
      size_t destination;
      input >> from;
      input >> destination;
      graph[from].push_back(destination);
      reverse_graph[destination].push_back(from);
    }
  }
};

void SortByOut(Graph& dag, size_t vertex, std::vector<bool>& used,
               std::vector<size_t>& sort_by_out) {
  used[vertex] = true;
  for (size_t destination : dag.graph[vertex]) {
    if (!used[destination]) {
      SortByOut(dag, destination, used, sort_by_out);
    }
  }
  sort_by_out.push_back(vertex);
}

void MarkComponents(Graph& dag, size_t vertex, size_t& number_components,
                    std::vector<size_t>& components) {
  components[vertex] = number_components + 1;
  for (size_t destination : dag.reverse_graph[vertex]) {
    if (components[destination] == 0) {
      MarkComponents(dag, destination, number_components, components);
    }
  }
}

std::pair<size_t, std::vector<size_t>> FindComponents(Graph& dag) {
  size_t number_components = 0;
  std::vector<size_t> components(dag.graph.size());
  std::vector<bool> used(dag.graph.size(), false);
  std::vector<size_t> sort_by_out(dag.graph.size());
  for (size_t i = 1; i < dag.graph.size(); i++) {
    if (!used[i]) {
      SortByOut(dag, i, used, sort_by_out);
    }
  }
  std::reverse(sort_by_out.begin(), sort_by_out.end());
  for (size_t vertex : sort_by_out) {
    if (components[vertex] == 0) {
      MarkComponents(dag, vertex, number_components, components);
      number_components++;
    }
  }
  return {number_components, components};
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph dag;
  dag >> std::cin;
  std::pair<size_t, std::vector<size_t>> components = FindComponents(dag);
  std::cout << components.first - 1 << "\n";
  for (size_t i = 1; i < components.second.size(); i++) {
    std::cout << components.second[i] << " ";
  }
}
