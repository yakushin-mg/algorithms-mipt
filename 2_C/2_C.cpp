/* 1 <= number_requests <= 10^5
   1 <= element <= number_requests*/

#include <deque>
#include <iostream>

using std::deque;

void OrdinaryGoblin(deque<int>& second_half) {
  int element;
  std::cin >> element;
  second_half.push_back(element);
}

void VipGoblin(deque<int>& first_half, deque<int>& second_half) {
  int element;
  std::cin >> element;
  if (first_half.size() <= second_half.size()) {
    first_half.push_back(element);
  } else {
    second_half.push_front(element);
  }
}

void GoblinAtTheShaman(deque<int>& first_half) {
  std::cout << first_half.front() << "\n";
  first_half.pop_front();
}

void EqualityHalves(deque<int>& first_half, deque<int>& second_half) {
  if (first_half.size() < second_half.size()) {
    int element = second_half.front();
    second_half.pop_front();
    first_half.push_back(element);
  }
}

void Goblins(size_t number_requests) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  deque<int> first_half;
  deque<int> second_half;

  char request;
  for (size_t i = 0; i < number_requests; i++) {
    std::cin >> request;
    switch (request) {
      case '+':
        OrdinaryGoblin(second_half);
        EqualityHalves(first_half, second_half);
        break;
      case '*':
        VipGoblin(first_half, second_half);
        break;
      case '-':
        GoblinAtTheShaman(first_half);
        EqualityHalves(first_half, second_half);
        break;
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  size_t number_requests;
  std::cin >> number_requests;
  Goblins(number_requests);
}
