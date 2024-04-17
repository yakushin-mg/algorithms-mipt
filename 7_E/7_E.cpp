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
      roads_[destination].push_back(from);
      repeat_number_[{from, destination}].first = i + 1;
      repeat_number_[{from, destination}].second++;
      repeat_number_[{destination, from}].first = i + 1;
      repeat_number_[{destination, from}].second++;
    }
  }

  size_t GetPointsNumber() { return roads_.size(); }

  std::vector<size_t> GetRoads(size_t from) { return roads_[from]; }

  size_t GetRoadNumber(size_t from, size_t destination) {
    return repeat_number_[{from, destination}].first;
  }

  size_t GetRepeatNumber(size_t from, size_t destination) {
    return repeat_number_[{from, destination}].second;
  }

 private:
  std::vector<std::vector<size_t>> roads_;
  std::map<std::pair<size_t, size_t>, std::pair<size_t, size_t>> repeat_number_;
};

struct Time {
  size_t timer = 0;
  std::vector<size_t> in;
  std::vector<size_t> out;
};

void DFS(Graph& graph, size_t vertex, size_t parent, std::set<size_t>& bridges,
         Time& time, std::vector<bool>& used) {
  time.in[vertex] = time.timer++;
  time.out[vertex] = time.in[vertex];
  used[vertex] = true;
  for (size_t destination : graph.GetRoads(vertex)) {
    if (destination == parent) {
      continue;
    }
    if (used[destination]) {
      time.out[vertex] = std::min(time.out[vertex], time.in[destination]);
    } else {
      DFS(graph, destination, vertex, bridges, time, used);
      time.out[vertex] = std::min(time.out[vertex], time.out[destination]);
      if (time.out[destination] > time.in[vertex]) {
        if (graph.GetRepeatNumber(vertex, destination) == 1) {
          bridges.insert(graph.GetRoadNumber(vertex, destination));
        }
      }
    }
  }
}

std::set<size_t> FindBridges(Graph& graph) {
  std::set<size_t> bridges;
  Time time;
  size_t points_number = graph.GetPointsNumber();
  time.in.resize(points_number);
  time.out.resize(points_number);
  std::vector<bool> used(points_number);
  for (size_t i = 1; i < points_number; i++) {
    if (!used[i]) {
      DFS(graph, i, 0, bridges, time, used);
    }
  }
  return bridges;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Graph graph;
  graph >> std::cin;
  std::set<size_t> bridges = FindBridges(graph);
  std::cout << bridges.size() << "\n";
  for (size_t bridge : bridges) {
    std::cout << bridge << '\n';
  }
}
