/*Найти k-ю порядковую статистику последовательности
1 ≤ k_index ≤ number_elements ≤ 10^7
0 ≤ sequence[i] < 10^7 + 4321)*/

#include <cmath>
#include <iostream>
#include <vector>
using std::vector;
size_t Partition(vector<int>& sequence, size_t start, size_t end, int pivot) {
  size_t less_count = 0;
  for (size_t i = start; i < end; i++) {
    if (sequence[i] <= pivot) {
      std::swap(sequence[i], sequence[start + less_count]);
      less_count += 1;
    }
  }
  std::swap(sequence[start + less_count], sequence[end]);
  return less_count;
}
int QuickSelect(vector<int>& sequence, size_t start, size_t end,
                size_t k_index) {
  if (start < end) {
    size_t less_count = Partition(sequence, start, end, sequence[end]);
    if (k_index < (start + less_count)) {
      return QuickSelect(sequence, start, start + less_count - 1, k_index);
    }
    if (k_index == (start + less_count)) {
      return sequence[start + less_count];
    }
    return QuickSelect(sequence, start + less_count + 1, end, k_index);
  }
  return sequence[start];
}
int main() {
  size_t length;
  std::cin >> length;
  size_t k_index;
  vector<int> sequence(length);
  std::cin >> k_index >> sequence[0] >> sequence[1];
  const int kFactor1 = 123;
  const int kFactor2 = 45;
  const int kFactor3 = pow(10, 7) + 4321;
  for (size_t i = 2; i < length; i++) {
    sequence[i] =
        (sequence[i - 1] * kFactor1 + sequence[i - 2] * kFactor2) % (kFactor3);
  }
  std::cout << QuickSelect(sequence, 0, sequence.size() - 1, k_index - 1);
}
