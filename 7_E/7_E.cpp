/* Дан неориентированный (быть может несвязный) граф. Требуется найти все мосты в нем.
   1 <= points_number <= 20000
   1 <= roads_number <= 200000
*/

#include <iostream>
#include <map>
#include <set>
#include <vector>

class Graph {
 public:
  std::set<size_t> bridges;
  Graph(size_t points_number, size_t roads_number) {
    graph_.resize(points_number + 1);
    timein_.resize(points_number + 1);
    timeout_.resize(points_number + 1);
    used_.resize(points_number + 1);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    for (size_t i = 0; i < roads_number; i++) {
      size_t from;
      size_t destination;
      std::cin >> from >> destination;
      graph_[from].push_back(destination);
      graph_[destination].push_back(from);
      repeat_number_[{from, destination}].first = i + 1;
      repeat_number_[{from, destination}].second++;
      repeat_number_[{destination, from}].first = i + 1;
      repeat_number_[{destination, from}].second++;
    }
  }
  void FindPoints() {
    for (size_t i = 1; i < graph_.size(); i++) {
      if (!used_[i]) {
        DFS(i);
      }
    }
  }

 private:
  std::vector<std::vector<size_t>> graph_;
  std::vector<size_t> timein_;
  std::vector<size_t> timeout_;
  std::vector<bool> used_;
  std::map<std::pair<size_t, size_t>, std::pair<size_t, size_t>> repeat_number_;
  size_t timer_ = 0;

  void DFS(size_t vertex, size_t parent = 0) {
    timein_[vertex] = timer_++;
    timeout_[vertex] = timein_[vertex];
    used_[vertex] = true;
    for (size_t destination : graph_[vertex]) {
      if (destination == parent) {
        continue;
      }
      if (used_[destination]) {
        timeout_[vertex] = std::min(timeout_[vertex], timein_[destination]);
      } else {
        DFS(destination, vertex);
        timeout_[vertex] = std::min(timeout_[vertex], timeout_[destination]);
        if (timeout_[destination] > timein_[vertex]) {
          if (repeat_number_[{vertex, destination}].second == 1) {
            bridges.insert(repeat_number_[{vertex, destination}].first);
          }
        }
      }
    }
  }
};

int main() {
  size_t points_number;
  size_t roads_number;
  std::cin >> points_number >> roads_number;
  Graph graph(points_number, roads_number);
  graph.FindPoints();
  std::cout << graph.bridges.size() << "\n";
  for (size_t point : graph.bridges) {
    std::cout << point << '\n';
  }
}
