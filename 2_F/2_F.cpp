/* Написать двоичную кучу с операциями : insert, getMin, extractMin, decreaseKey
1 <= number_requests <= 10^6
- (10^9) <= element <= 10^9
0 <= delta <= 10^9 */

#include <iostream>
#include <string>
#include <vector>

class MinHeap {
 public:
  void Insert(long long element);
  void ExtractMin();
  long long GetMin();
  void DecreaseKey(size_t index, long long delta);

 private:
  std::vector<long long> heap_;
  std::vector<long long> values_requests_;

  void SiftUp(size_t son);
  void SiftDown(size_t parent);
  void FillingValues(long long element);
  size_t FindingElement(long long element, size_t parent);
};

void MinHeap::Insert(long long element) {
  FillingValues(element);
  heap_.push_back(element);
  SiftUp(heap_.size() - 1);
}

long long MinHeap::GetMin() {
  FillingValues(0);
  return heap_[0];
}

void MinHeap::ExtractMin() {
  FillingValues(0);
  std::swap(heap_[0], heap_[heap_.size() - 1]);
  heap_.pop_back();
  SiftDown(0);
}

void MinHeap::DecreaseKey(size_t index, long long delta) {
  FillingValues(0);
  size_t index_heap = FindingElement(values_requests_[index], 0);
  long long value = heap_[index_heap] - delta;
  heap_[index_heap] = value;
  SiftUp(index_heap);
  values_requests_[index] = value;
}

void MinHeap::SiftUp(size_t son) {
  if (son > 0) {
    size_t parent = (son - 1) / 2;
    if (heap_[son] < heap_[parent]) {
      std::swap(heap_[son], heap_[parent]);
      SiftUp(parent);
    }
  }
}

void MinHeap::SiftDown(size_t parent) {
  if (parent * 2 + 1 >= heap_.size()) {
    return;
  }
  size_t smallest_child = parent * 2 + 1;
  if (smallest_child + 1 < heap_.size() &&
      heap_[smallest_child + 1] < heap_[smallest_child]) {
    smallest_child += 1;
  }
  if (heap_[smallest_child] < heap_[parent]) {
    std::swap(heap_[smallest_child], heap_[parent]);
    SiftDown(smallest_child);
  }
}

void MinHeap::FillingValues(long long element) {
  values_requests_.push_back(element);
}

size_t MinHeap::FindingElement(long long element, size_t parent) {
  size_t index_heap = 0;
  if (element == heap_[parent]) {
    index_heap = parent;
    return index_heap;
  }
  size_t left_son = parent * 2 + 1;
  size_t right_son = parent * 2 + 2;
  if ((left_son < heap_.size()) && (element >= heap_[left_son])) {
    index_heap += FindingElement(element, left_son);
  }
  if ((right_son < heap_.size()) && (element >= heap_[right_son])) {
    index_heap += FindingElement(element, right_son);
  }
  return index_heap;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);

  size_t number_requests;
  std::cin >> number_requests;

  MinHeap heap;

  for (size_t i = 0; i < number_requests; i++) {
    std::string request;
    std::cin >> request;

    if (request == "insert") {
      long long element;
      std::cin >> element;
      heap.Insert(element);
    } else if (request == "getMin") {
      std::cout << heap.GetMin() << "\n";
    } else if (request == "extractMin") {
      heap.ExtractMin();
    } else {
      size_t index;
      long long delta;
      std::cin >> index >> delta;
      heap.DecreaseKey(index - 1, delta);
    }
  }
}
