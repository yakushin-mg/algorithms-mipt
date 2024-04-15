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
  std::vector<std::vector<size_t>> roads;
  std::map<std::pair<size_t, size_t>, std::pair<size_t, size_t>> repeat_number;

  void operator>>(std::istream& input) {
    size_t points_number;
    size_t roads_number;
    input >> points_number;
    input >> roads_number;
    roads.resize(points_number + 1);
    for (size_t i = 0; i < roads_number; i++) {
      size_t from;
      size_t destination;
      input >> from;
      input >> destination;
      roads[from].push_back(destination);
      roads[destination].push_back(from);
      repeat_number[{from, destination}].first = i + 1;
      repeat_number[{from, destination}].second++;
      repeat_number[{destination, from}].first = i + 1;
      repeat_number[{destination, from}].second++;
    }
  }

  std::set<size_t> bridges;

 private:
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
  for (size_t destination : graph.roads[vertex]) {
    if (destination == parent) {
      continue;
    }
    if (used[destination]) {
      time.out[vertex] = std::min(time.out[vertex], time.in[destination]);
    } else {
      DFS(graph, destination, vertex, bridges, time, used);
      time.out[vertex] = std::min(time.out[vertex], time.out[destination]);
      if (time.out[destination] > time.in[vertex]) {
        if (graph.repeat_number[{vertex, destination}].second == 1) {
          bridges.insert(graph.repeat_number[{vertex, destination}].first);
        }
      }
    }
  }
}

std::set<size_t> FindBridges(Graph& graph) {
  std::set<size_t> bridges;
  Time time;
  time.in.resize(graph.roads.size());
  time.out.resize(graph.roads.size());
  std::vector<bool> used(graph.roads.size());
  for (size_t i = 1; i < graph.roads.size(); i++) {
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
