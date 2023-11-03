/*Найти среднее геометрическое на отрезке [r;l] (корень степени r - l + 1)
1 <= len_array <= 3* 10^5
0.01 <= sound_mandragora <= 10^3
1 <= quality <= 10^5
0 <= boarder <= len_array - 1
*/

#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
using std::vector;
void Geometry(vector<long double>& prefix_sum, size_t left_boarder,
              size_t right_boarder) {
  long double sum;
  const int kPrecision{6};
  sum = prefix_sum[right_boarder + 1] - prefix_sum[left_boarder];
  double degree = right_boarder - left_boarder + 1;
  std::cout << std::fixed << std::setprecision(kPrecision)
            << exp((1 / degree) * sum) << std::endl;
}

int main() {
  size_t len_array;
  std::cin >> len_array;
  vector<long double> sound(len_array + 1, 0);
  for (size_t i = 1; i <= len_array; i++) {
    std::cin >> sound[i];
  }
  vector<long double> prefix_sum(len_array + 1, 0);
  for (size_t i = 1; i <= len_array; i++) {
    prefix_sum[i] = prefix_sum[i - 1] + log(sound[i]);
  }
  size_t number_requests;
  std::cin >> number_requests;
  size_t left_boarder;
  size_t right_boarder;
  for (size_t i = 0; i < number_requests; i++) {
    std::cin >> left_boarder >> right_boarder;
    Geometry(prefix_sum, left_boarder, right_boarder);
  }
}
