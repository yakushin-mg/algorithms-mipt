/* Очередь с обычными гоблинами (встают в конец очереди) и привилегированными (встают в середину очереди)
   1 <= number_requests <= 10^5
   1 <= element <= number_requests*/

#include <deque>
#include <iostream>
#include <queue>

class GoblinsQueue {
 public:
  void OrdinaryGoblin(int element);
  void VipGoblin(int element);
  int GoblinLeaves();

 private:
  std::queue<int> first_half_;
  std::deque<int> second_half_;

  void EqualityHalves();
};

void GoblinsQueue::OrdinaryGoblin(int element) {
  second_half_.push_back(element);
  EqualityHalves();
}

void GoblinsQueue::VipGoblin(int element) {
  if (first_half_.size() <= second_half_.size()) {
    first_half_.push(element);
  } else {
    second_half_.push_front(element);
  }
}

int GoblinsQueue::GoblinLeaves() {
  int goblin_number = first_half_.front();
  first_half_.pop();
  EqualityHalves();
  return goblin_number;
}

void GoblinsQueue::EqualityHalves() {
  if (first_half_.size() >= second_half_.size()) {
    return;
  }
  int element = second_half_.front();
  second_half_.pop_front();
  first_half_.push(element);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  GoblinsQueue queue;

  size_t number_requests;
  std::cin >> number_requests;

  for (size_t i = 0; i < number_requests; i++) {
    char request;
    int element;
    std::cin >> request;
    switch (request) {
      case '+':
        std::cin >> element;
        queue.OrdinaryGoblin(element);
        break;
      case '*':
        std::cin >> element;
        queue.VipGoblin(element);
        break;
      case '-':
        std::cout << queue.GoblinLeaves() << "\n";
        break;
    }
  }
}
