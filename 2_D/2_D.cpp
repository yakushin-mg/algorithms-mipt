/* Очередь с поддержкой минимума и операциями: enqueue, dequeue, front, size, clear, min
   1 <= number_requests <= 2 * (10^5)
   1 <= element <= (10^9) */

#include <deque>
#include <iostream>
#include <string>

void IsEmpty() {
  std::cout << "error"
            << "\n";
}

using std::deque;

void FillingDeque(deque<int>& min_element, int element) {
  while ((!min_element.empty()) && (!(min_element.back() <= element))) {
    min_element.pop_back();
  }
  min_element.push_back(element);
}

void Enqueue(deque<int>& line, deque<int>& min_element) {
  int element;
  std::cin >> element;
  line.push_back(element);
  FillingDeque(min_element, element);
  std::cout << "ok"
            << "\n";
}

void Front(deque<int>& line) {
  if (line.empty()) {
    IsEmpty();
  } else {
    std::cout << line.front() << "\n";
  }
}

void PopDeque(deque<int>& min_element, int element) {
  if ((min_element.front()) == element) {
    min_element.pop_front();
  }
}

void Dequeue(deque<int>& line, deque<int>& min_element) {
  if (line.empty()) {
    IsEmpty();
  } else {
    int element;
    element = line.front();
    line.pop_front();
    PopDeque(min_element, element);
    std::cout << element << "\n";
  }
}

void Size(deque<int>& line) { std::cout << line.size() << "\n"; }

void ClearDeque(deque<int>& line) { line.clear(); }

void Clear(deque<int>& line) {
  ClearDeque(line);
  std::cout << "ok"
            << "\n";
}

void Min(deque<int>& line, deque<int>& min_element) {
  if (line.empty()) {
    IsEmpty();
  } else {
    std::cout << min_element.front() << "\n";
  }
}

void Requests(size_t number_requests) {
  deque<int> line;
  std::string request;
  deque<int> min_element;

  for (size_t i = 0; i < number_requests; i++) {
    std::cin >> request;
    if (request == "enqueue") {
      Enqueue(line, min_element);
    } else if (request == "dequeue") {
      Dequeue(line, min_element);
    } else if (request == "front") {
      Front(line);
    } else if (request == "size") {
      Size(line);
    } else if (request == "clear") {
      Clear(line);
      ClearDeque(min_element);
    } else {
      Min(line, min_element);
    }
  }
}

int main() {
  size_t number_requests;
  std::cin >> number_requests;
  Requests(number_requests);
}
