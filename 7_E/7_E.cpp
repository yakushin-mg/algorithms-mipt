//Дан неориентированный (быть может несвязный) граф. Требуется найти все мосты в нем.

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class Graph {
 public:
  std::set<size_t> answer;
  Graph(size_t points_number, size_t roads_number) {
    graph_.resize(points_number + 1);
    tin_.resize(points_number + 1);
    ret_.resize(points_number + 1);
    used_.resize(points_number + 1);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    for (size_t i = 0; i < roads_number; i++) {
      size_t otkuda;
      size_t kuda;
      std::cin >> otkuda >> kuda;
      graph_[otkuda].push_back(kuda);
      graph_[kuda].push_back(otkuda);
      number_kolvo_[{otkuda, kuda}].first = i + 1;
      number_kolvo_[{otkuda, kuda}].second++;
      number_kolvo_[{kuda, otkuda}].first = i + 1;
      number_kolvo_[{kuda, otkuda}].second++;
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
  std::vector<size_t> tin_;
  std::vector<size_t> ret_;
  std::vector<bool> used_;
  std::map<std::pair<size_t, size_t>, std::pair<size_t, size_t>> number_kolvo_;
  size_t timer_ = 0;

  void DFS(size_t vertex, size_t parent = 0) {
    tin_[vertex] = timer_++;
    ret_[vertex] = tin_[vertex];
    used_[vertex] = true;
    for (size_t kuda : graph_[vertex]) {
      if (kuda == parent) {
        continue;
      }
      if (used_[kuda]) {
        ret_[vertex] = std::min(ret_[vertex], tin_[kuda]);
      } else {
        DFS(kuda, vertex);
        ret_[vertex] = std::min(ret_[vertex], ret_[kuda]);
        if (ret_[kuda] > tin_[vertex]) {
          if (number_kolvo_[{vertex, kuda}].second == 1) {
            answer.insert(number_kolvo_[{vertex, kuda}].first);
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
  std::cout << graph.answer.size() << "\n";
  for (size_t point : graph.answer) {
    std::cout << point << '\n';
  }
}
