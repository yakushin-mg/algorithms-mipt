/* Программа получает на вход количество участников в виде позывной гонщика — имя машины N (0 ≤ N ≤ 105). 
  Далее следует N строк, каждая строка содержит ровно два слова. Затем идет число Q (1 ≤ Q ≤ 105) — количество запросов к модулю.
  Далее на каждой следующей из Q строк идет слово, к которому надо вывести, если на входе имя, соответствующий позывной гонщика, иначе — имя машины, соответствующей гонщику.
  
  0 <= length <= 10^5
  0 <= questions_number <= 10^5 */

#include <iostream>
#include <string>
#include <vector>
class Treap {
 public:
  Treap() : top_(nullptr) {}

  ~Treap() { delete top_; }

  void Insert(std::vector<std::string> values);
  std::string Find(std::string value);

 private:
  struct Node {
    std::vector<std::string> key;
    size_t priority;
    Node* left_son;
    Node* right_son;

    Node(std::vector<std::string> key)
        : key(key), priority(rand()), left_son(nullptr), right_son(nullptr) {}

    ~Node() {
      delete left_son;
      delete right_son;
    }
  };

  Node* top_;

  std::pair<Node*, Node*> Split(Node* current, std::string value);
  Node* Merge(std::pair<Node*, Node*> trees);
  Node* Find(Node* current, std::string value);
};

void Treap::Insert(std::vector<std::string> values) {
  std::pair<Node*, Node*> sons = Split(top_, values[0]);
  top_ = Merge({sons.first, Merge({new Node(values), sons.second})});
}

std::string Treap::Find(std::string value) {
  Node* desired_node = Find(top_, value);
  return desired_node->key[1];
}

std::pair<Treap::Node*, Treap::Node*> Treap::Split(Node* current,
                                                   std::string value) {
  if (current == nullptr) {
    return {nullptr, nullptr};
  }
  if (current->key[0] < value) {
    std::pair<Node*, Node*> right_sons = Split(current->right_son, value);
    current->right_son = right_sons.first;
    return {current, right_sons.second};
  }
  std::pair<Node*, Node*> left_sons = Split(current->left_son, value);
  current->left_son = left_sons.second;
  return {left_sons.first, current};
}

Treap::Node* Treap::Merge(std::pair<Treap::Node*, Treap::Node*> trees) {
  if (trees.first == nullptr && trees.second == nullptr) {
    return nullptr;
  }
  if (trees.first == nullptr) {
    return trees.second;
  }
  if (trees.second == nullptr) {
    return trees.first;
  }
  if (trees.first->priority < trees.second->priority) {
    trees.first->right_son = Merge({trees.first->right_son, trees.second});
    return trees.first;
  }
  trees.second->left_son = Merge({trees.first, trees.second->left_son});
  return trees.second;
}

Treap::Node* Treap::Find(Treap::Node* current, std::string value) {
  if (current == nullptr) {
    return nullptr;
  }
  std::string current_value = current->key[0];
  if (current_value == value) {
    return current;
  }
  if (current_value < value) {
    return Find(current->right_son, value);
  }
  return Find(current->left_son, value);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  size_t length;
  std::cin >> length;

  Treap tree;

  for (size_t i = 0; i < length; ++i) {
    std::string racer_name;
    std::string car_name;
    std::cin >> racer_name >> car_name;
    tree.Insert({racer_name, car_name});
    tree.Insert({car_name, racer_name});
  }

  size_t questions_number;
  std::cin >> questions_number;

  for (size_t i = 0; i < questions_number; ++i) {
    std::string name;
    std::cin >> name;
    std::cout << tree.Find(name) << std::endl;
  }
}
