#include <iostream>
#include <string>
#include <vector>
using std::swap;
using std::vector;
void SiftUp(vector<long long>& heap, size_t son) {
  if (son > 0) {
    size_t parent = (son - 1) / 2;
    if (heap[son] < heap[parent]) {
      swap(heap[son], heap[parent]);
      SiftUp(heap, parent);
    }
  }
}
void SiftDown(vector<long long>& heap, size_t parent) {
  if ((parent * 2 + 1) < heap.size()) {
    size_t left_son = parent * 2 + 1;
    if ((parent * 2 + 2) < heap.size()) {
      size_t right_son = parent * 2 + 2;
      if (heap[parent] > heap[left_son] && heap[parent] > heap[right_son]) {
        if (heap[left_son] < heap[right_son]) {
          swap(heap[parent], heap[left_son]);
          SiftDown(heap, left_son);
        } else {
          swap(heap[parent], heap[right_son]);
          SiftDown(heap, right_son);
        }
      } else if (heap[parent] > heap[left_son]) {
        swap(heap[parent], heap[left_son]);
        SiftDown(heap, left_son);
      } else if (heap[parent] > heap[right_son]) {
        swap(heap[parent], heap[right_son]);
        SiftDown(heap, right_son);
      }
    } else {
      if (heap[parent] > heap[left_son]) {
        swap(heap[parent], heap[left_son]);
        SiftDown(heap, left_son);
      }
    }
  }
}
void Insert(vector<long long>& heap, long long element) {
  heap.push_back(element);
  SiftUp(heap, heap.size() - 1);
}
void GetMin(vector<long long>& heap) { std::cout << heap[0] << "\n"; }
void ExtractMin(vector<long long>& heap) {
  swap(heap[0], heap[heap.size() - 1]);
  heap.pop_back();
  SiftDown(heap, 0);
}
size_t FindingElement(vector<long long>& heap, long long element,
                      size_t parent) {
  size_t index_heap = 0;
  if (element == heap[parent]) {
    index_heap = parent;
    return index_heap;
  }
  size_t left_son = parent * 2 + 1;
  size_t right_son = parent * 2 + 2;
  if ((left_son < heap.size()) && (element >= heap[left_son])) {
    index_heap += FindingElement(heap, element, left_son);
  }
  if ((right_son < heap.size()) && (element >= heap[right_son])) {
    index_heap += FindingElement(heap, element, right_son);
  }
  return index_heap;
}
long long DecreaseKey(vector<long long>& heap, size_t index_heap) {
  long long delta;
  std::cin >> delta;
  long long value = heap[index_heap] - delta;
  heap[index_heap] = value;
  SiftUp(heap, index_heap);
  return value;
}
void Requests(size_t number_requests) {
  vector<long long> heap;
  vector<long long> values_requests;
  std::string request;
  for (size_t i = 0; i < number_requests; i++) {
    std::cin >> request;
    if (request == "insert") {
      long long element;
      std::cin >> element;
      values_requests.push_back(element);
      Insert(heap, element);
    } else if (request == "getMin") {
      GetMin(heap);
      values_requests.push_back(0);
    } else if (request == "extractMin") {
      ExtractMin(heap);
      values_requests.push_back(0);
    } else {
      values_requests.push_back(0);
      size_t index;
      std::cin >> index;
      index -= 1;
      size_t index_heap = FindingElement(heap, values_requests[index], 0);
      long long value = DecreaseKey(heap, index_heap);
      values_requests[index] = value;
    }
  }
}
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  std::cout.tie(0);
  size_t number_requests;
  std::cin >> number_requests;
  Requests(number_requests);
}
