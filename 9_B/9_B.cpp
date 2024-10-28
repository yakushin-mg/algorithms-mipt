/* Требуется найти в связном графе остовное дерево минимального веса
   1 ≤ points_number_ ≤ 10^5
   1 ≤ roads_number ≤ 10^5
   1 ≤ weight ≤ 10^5
*/

#include <algorithm>
#include <iostream>
#include <vector>

struct Edge {
  size_t from;
  size_t to;
  long long weight;

  Edge(size_t from, size_t to, long long weight)
      : from(from), to(to), weight(weight) {}
};

class Graph {
 public:
  void operator>>(std::istream& input) {
    size_t roads_number;
    input >> points_number_ >> roads_number;
    for (size_t i = 1; i <= roads_number; i++) {
      size_t from;
      size_t to;
      int weight;
      input >> from >> to >> weight;
      edges_.push_back(Edge(from, to, weight));
    }
  }

  std::vector<Edge>& Edges() { return edges_; }

  size_t PointsNumber() const { return points_number_; }

 private:
  std::vector<Edge> edges_;
  size_t points_number_;
};

struct DSU {
  std::vector<size_t> parent;
  std::vector<size_t> size;

  DSU(size_t points_number) {
    parent.assign(points_number + 1, 0);
    size.assign(points_number + 1, 1);
    for (size_t i = 1; i <= points_number; i++) {
      parent[i] = i;
    }
  }

  size_t FindSet(size_t vertex) {
    if (vertex == parent[vertex]) {
      return vertex;
    }
    return parent[vertex] = FindSet(parent[vertex]);
  }

  void UnionSets(size_t first_vertex, size_t second_vertex) {
    first_vertex = FindSet(first_vertex);
    second_vertex = FindSet(second_vertex);
    if (first_vertex != second_vertex) {
      if (size[first_vertex] < size[second_vertex]) {
        std::swap(first_vertex, second_vertex);
      }
      parent[second_vertex] = first_vertex;
      size[first_vertex] += size[second_vertex];
    }
  }
};

bool Comparator(const Edge& first_edge, const Edge& second_edge) {
  return (first_edge.weight < second_edge.weight);
}

void Kruskal(Graph& graph, std::vector<Edge>& mst) {
  std::vector<bool> in_mst(graph.PointsNumber() + 1, false);
  std::sort(graph.Edges().begin(), graph.Edges().end(), Comparator);
  DSU set(graph.PointsNumber());
  for (Edge& edge : graph.Edges()) {
    if (set.FindSet(edge.from) != set.FindSet(edge.to)) {
      mst.push_back(edge);
      set.UnionSets(edge.from, edge.to);
    }
  }
}

long long WeightMST(Graph& graph) {
  std::vector<Edge> mst;
  Kruskal(graph, mst);
  long long weight_mst = 0;
  for (Edge edge : mst) {
    weight_mst += edge.weight;
  }
  return weight_mst;
}

int main() {
  Graph graph;
  graph >> std::cin;

  std::cout << WeightMST(graph);
}
