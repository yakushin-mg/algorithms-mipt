/* Очередь с поддержкой минимума и операциями: enqueue, dequeue, front, size, clear, min
   для поддержки минимума использовал deque
   1 <= number_requests <= 2 * (10^5)
   1 <= element <= (10^9) */

#include <deque>
#include <iostream>
#include <queue>
#include <string>

class QueueWithMin {
 public:
  void Enqueue(long long element);
  long long Dequeue();
  long long Front();
  long long Size();
  void Clear();
  long long Min();
  bool IsEmpty();

 private:
  std::queue<long long> line_;
  std::deque<long long> min_element_;

  void UpdateMin(long long element);
  void PopMin(long long element);
};

void QueueWithMin::Enqueue(long long element) {
  line_.push(element);
  UpdateMin(element);
}

long long QueueWithMin::Dequeue() {
  long long element;
  element = line_.front();
  line_.pop();
  PopMin(element);
  return element;
}

long long QueueWithMin::Front() { return line_.front(); }

long long QueueWithMin::Size() { return line_.size(); }

void QueueWithMin::Clear() {
  while (!line_.empty()) {
    line_.pop();
  }
  min_element_.clear();
}

long long QueueWithMin::Min() { return min_element_.front(); }

bool QueueWithMin::IsEmpty() { return (line_.empty()); }

void QueueWithMin::UpdateMin(long long element) {
  while ((!min_element_.empty()) && (!(min_element_.back() <= element))) {
    min_element_.pop_back();
  }
  min_element_.push_back(element);
}

void QueueWithMin::PopMin(long long element) {
  if ((min_element_.front()) == element) {
    min_element_.pop_front();
  }
}

int main() {
  size_t number_requests;
  std::cin >> number_requests;

  QueueWithMin queue;

  for (size_t i = 0; i < number_requests; i++) {
    std::string request;
    std::cin >> request;
    if (request == "enqueue") {
      long long element;
      std::cin >> element;
      queue.Enqueue(element);
      std::cout << "ok"
                << "\n";
    } else if (request == "dequeue") {
      if (queue.IsEmpty()) {
        std::cout << "error"
                  << "\n";
      } else {
        std::cout << queue.Dequeue() << "\n";
      }
    } else if (request == "front") {
      if (queue.IsEmpty()) {
        std::cout << "error"
                  << "\n";
      } else {
        std::cout << queue.Front() << "\n";
      }
    } else if (request == "size") {
      std::cout << queue.Size() << "\n";
    } else if (request == "clear") {
      queue.Clear();
      std::cout << "ok"
                << "\n";
    } else {
      if (queue.IsEmpty()) {
        std::cout << "error"
                  << "\n";
      } else {
        std::cout << queue.Min() << "\n";
      }
    }
  }
}
