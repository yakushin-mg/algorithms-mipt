/*  Есть граф из N (points_number_) городов. 
    Нужно найти отрицательный цикл и вывести его, если он существует.

    0 <= points_number_ <= 100
*/

#include <algorithm>
#include <iostream>
#include <vector>

const long long cKInf = 1e18;
const long long cKMax = 1e5;

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
    input >> points_number_;
    for (size_t from = 1; from <= points_number_; from++) {
      for (size_t to = 1; to <= points_number_; to++) {
        long long weight;
        input >> weight;
        if (weight == cKMax) {
          weight = cKInf;
        }
        roads_.push_back(Edge(from, to, weight));
      }
    }
  }

  std::vector<Edge> Roads() { return roads_; }

  size_t PointsNumber() const { return points_number_; }

 private:
  std::vector<Edge> roads_;
  size_t points_number_;
};

void FordBellman(Graph& graph, std::vector<size_t>& cycle) {
  size_t points_number = graph.PointsNumber();
  std::vector<long long> dist(points_number + 1, cKInf);
  dist[1] = 0;
  std::vector<size_t> prev_vertex(points_number + 1, 0);
  for (size_t i = 0; i < points_number - 1; i++) {
    for (Edge& edge : graph.Roads()) {
      if (dist[edge.to] > dist[edge.from] + edge.weight) {
        dist[edge.to] = dist[edge.from] + edge.weight;
        prev_vertex[edge.to] = edge.from;
      }
    }
  }
  size_t neg_vertex = 0;
  for (Edge& edge : graph.Roads()) {
    if (dist[edge.to] > dist[edge.from] + edge.weight) {
      dist[edge.to] = dist[edge.from] + edge.weight;
      prev_vertex[edge.to] = edge.from;
      neg_vertex = edge.to;
    }
  }
  if (neg_vertex == 0) {
    return;
  }
  size_t start_cycle = neg_vertex;
  for (size_t i = 0; i < points_number; i++) {
    start_cycle = prev_vertex[start_cycle];
  }
  size_t cur_vertex = start_cycle;
  while (cur_vertex != start_cycle || cycle.size() <= 1) {
    cycle.push_back(cur_vertex);
    cur_vertex = prev_vertex[cur_vertex];
  }
  cycle.push_back(cur_vertex);
  std::reverse(cycle.begin(), cycle.end());
}

int main() {
  Graph graph;
  graph >> std::cin;

  std::vector<size_t> cycle;
  FordBellman(graph, cycle);
  if (cycle.empty()) {
    std::cout << "NO"
              << "\n";
  } else {
    std::cout << "YES"
              << "\n";
    std::cout << cycle.size() << "\n";
    for (size_t vertex : cycle) {
      std::cout << vertex << " ";
    }
  }
}
