/* Задан ориентированный граф. Найдите компоненты сильной связности заданного графа и топологически отсортируйте его конденсацию.
   1 ≤ points_number ≤ 20000
   1 ≤ roads_number ≤ 200000
*/

#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
 public:
  void operator>>(std::istream& input) {
    size_t points_number;
    size_t roads_number;
    input >> points_number;
    input >> roads_number;
    roads_.resize(points_number + 1);
    for (size_t i = 0; i < roads_number; i++) {
      size_t from;
      size_t destination;
      input >> from;
      input >> destination;
      roads_[from].push_back(destination);
    }
  }

  size_t GetPointsNumber() { return roads_.size(); }

  std::vector<size_t> GetRoads(size_t from) { return roads_[from]; }

 private:
  std::vector<std::vector<size_t>> roads_;
};

void SortByOut(Graph& graph, size_t vertex, std::vector<bool>& used,
               std::vector<size_t>& sort_by_out) {
  used[vertex] = true;
  for (size_t destination : graph.GetRoads(vertex)) {
    if (!used[destination]) {
      SortByOut(graph, destination, used, sort_by_out);
    }
  }
  sort_by_out.push_back(vertex);
}

void ReverseGraph(Graph& graph,
                  std::vector<std::vector<size_t>>& reverse_graph) {
  for (size_t from = 1; from < graph.GetPointsNumber(); from++) {
    for (size_t destination : graph.GetRoads(from)) {
      reverse_graph[destination].push_back(from);
    }
  }
}

void MarkComponents(Graph& graph, size_t vertex, size_t& number_components,
                    std::vector<size_t>& components,
                    std::vector<std::vector<size_t>>& reverse_graph) {
  components[vertex] = number_components + 1;
  for (size_t destination : reverse_graph[vertex]) {
    if (components[destination] == 0) {
      MarkComponents(graph, destination, number_components, components,
                     reverse_graph);
    }
  }
}

std::pair<size_t, std::vector<size_t>> FindComponents(Graph& graph) {
  size_t number_components = 0;
  size_t points_number = graph.GetPointsNumber();
  std::vector<bool> used(points_number, false);
  std::vector<size_t> sort_by_out(points_number);

  for (size_t i = 1; i < points_number; i++) {
    if (!used[i]) {
      SortByOut(graph, i, used, sort_by_out);
    }
  }

  std::reverse(sort_by_out.begin(), sort_by_out.end());
  std::vector<std::vector<size_t>> reverse_graph(points_number);
  ReverseGraph(graph, reverse_graph);
  std::vector<size_t> components(points_number);

  for (size_t vertex : sort_by_out) {
    if (components[vertex] == 0) {
      MarkComponents(graph, vertex, number_components, components,
                     reverse_graph);
      number_components++;
    }
  }

  return {number_components, components};
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph graph;
  graph >> std::cin;

  std::pair<size_t, std::vector<size_t>> components = FindComponents(graph);
  std::cout << components.first - 1 << "\n";
  for (size_t i = 1; i < components.second.size(); i++) {
    std::cout << components.second[i] << " ";
  }
}
