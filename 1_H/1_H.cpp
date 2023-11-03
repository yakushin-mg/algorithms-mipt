/*Написать алгоритм быстрой сортировки
1 <= length_array <= 10^5
abs(array[i]) <= 10^9 */

#include <iostream>
#include <vector>
using std::vector;
void QuickSort(vector<int>& array, vector<int>& extra, size_t start,
               size_t end) {
  if (start + 1 < end) {
    int pivot = array[(start + end) / 2];
    size_t index_extra = start;
    for (size_t i = start; i < end; i++) {
      if (array[i] < pivot) {
        extra[index_extra++] = array[i];
      }
    }
    size_t equal_count = 0;
    for (size_t i = start; i < end; i++) {
      if (array[i] == pivot) {
        extra[index_extra++] = array[i];
        equal_count += 1;
      }
    }
    size_t bigger_count = 0;
    for (size_t i = start; i < end; i++) {
      if (array[i] > pivot) {
        extra[index_extra++] = array[i];
        bigger_count += 1;
      }
    }
    for (size_t i = start; i < end; i++) {
      array[i] = extra[i];
    }
    QuickSort(array, extra, start, end - equal_count - bigger_count);
    QuickSort(array, extra, end - bigger_count, end);
  }
}
int main() {
  size_t length_array;
  std::cin >> length_array;
  vector<int> array(length_array);
  for (size_t i = 0; i < length_array; i++) {
    std::cin >> array[i];
  }
  vector<int> extra(length_array);
  QuickSort(array, extra, 0, length_array);
  for (size_t i = 0; i < length_array; i++) {
    std::cout << array[i] << " ";
  }
}
