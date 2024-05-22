/*  Есть K (graph_number) графов, в каждом из которых N (points_number_) городов
    и M (roads_number) дорог. Нужно найти расстояние от указанной вершины (start)
    до всех остальных.

    0 <= graph_number <= 5
    0 <= points_number_ <= 60000
    0 <= roads_number <= 200000

*/

#include <iostream>
#include <queue>
#include <vector>

const int cKInf = 2009000999;  // указано в задаче

struct Edge {
  size_t from;
  size_t to;
  int weight;

  Edge(size_t from, size_t to, int weight)
      : from(from), to(to), weight(weight) {}
};

class Graph {
 public:
  void operator>>(std::istream& input) {
    size_t roads_number;
    input >> points_number_ >> roads_number;
    roads_.resize(points_number_);
    for (size_t i = 1; i <= roads_number; i++) {
      size_t from;
      size_t to;
      int weight;
      input >> from >> to >> weight;
      roads_[from].push_back(Edge(from, to, weight));
      roads_[to].push_back(Edge(to, from, weight));
    }
  }

  const std::vector<Edge>& Roads(size_t from) const { return roads_[from]; }

  size_t PointsNumber() const { return points_number_; }

 private:
  std::vector<std::vector<Edge>> roads_;
  size_t points_number_;
};

std::vector<int> FindDistance(const Graph& graph, size_t start) {
  std::vector<int> dist(graph.PointsNumber(), cKInf);
  dist[start] = 0;
  std::priority_queue<std::pair<int, size_t>> heap;
  std::vector<bool> visited(graph.PointsNumber(), false);
  heap.push({dist[start], start});
  while (!heap.empty()) {
    std::pair<int, size_t> top;
    for (size_t i = 1; i <= heap.size(); i++) {
      if ((i == 1) || visited[top.second]) {
        top = heap.top();
        heap.pop();
      } else {
        break;
      }
    }
    if (heap.empty() && (visited[top.second])) {
      break;
    }
    visited[top.second] = true;
    if (top.first > dist[top.second]) {
      continue;
    }
    for (const Edge& edge : graph.Roads(top.second)) {
      if (dist[edge.to] > dist[edge.from] + edge.weight) {
        dist[edge.to] = dist[edge.from] + edge.weight;
        heap.push({dist[edge.to] * (-1), edge.to});
      }
    }
  }
  return dist;
}

int main() {
  size_t graph_number;
  std::cin >> graph_number;
  for (size_t i = 1; i <= graph_number; i++) {
    Graph graph;
    graph >> std::cin;
    size_t start;
    std::cin >> start;
    std::vector<int> dist = FindDistance(graph, start);
    for (size_t i = 0; i < dist.size(); i++) {
      if (dist[i] >= cKInf) {
        std::cout << cKInf << " ";
      } else {
        std::cout << dist[i] << " ";
      }
    }
  }
}
