/*Написать алгоритм быстрой сортировки
1 <= length <= 10^5
abs(array[i]) <= 10^9 */

#include <iostream>
#include <vector>
using std::vector;
std::pair<size_t, size_t> Partition(vector<int>& array, size_t start,
                                    size_t end) {
  std::pair<size_t, size_t> less_bigger_counts{0, 0};
  if (start + 1 >= end) {
    return less_bigger_counts;
  }
  vector<int> extra;
  int pivot = array[(start + end) / 2];
  size_t less_count = 0;
  for (size_t i = start; i < end; i++) {
    if (array[i] < pivot) {
      extra.push_back(array[i]);
      less_count++;
    }
  }
  for (size_t i = start; i < end; i++) {
    if (array[i] == pivot) {
      extra.push_back(array[i]);
    }
  }
  size_t bigger_count = 0;
  for (size_t i = start; i < end; i++) {
    if (array[i] > pivot) {
      extra.push_back(array[i]);
      bigger_count++;
    }
  }
  for (size_t i = 0; i < extra.size(); i++) {
    array[start + i] = extra[i];
  }
  less_bigger_counts = {less_count, bigger_count};
  return less_bigger_counts;
}

void QuickSort(vector<int>& array, size_t start, size_t end) {
  std::pair<size_t, size_t> less_bigger_counts = Partition(array, start, end);
  size_t less_count = less_bigger_counts.first;
  size_t bigger_count = less_bigger_counts.second;
  if (less_count >= 2) {
    QuickSort(array, start, start + less_count);
  }
  if (bigger_count >= 2) {
    QuickSort(array, end - bigger_count, end);
  }
}

int main() {
  size_t length;
  std::cin >> length;
  vector<int> array(length);
  for (size_t i = 0; i < length; i++) {
    std::cin >> array[i];
  }
  QuickSort(array, 0, length);
  for (size_t i = 0; i < length; i++) {
    std::cout << array[i] << " ";
  }
}
