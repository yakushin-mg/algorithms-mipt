/*  Карлу необходимо выполнить для мистера Правды N поручений, каждое из них характеризуется двумя числами:
    необходимое число ресурсов m и награда c. Сиджею негде набирать ресурсы, так что он ограничен M единицами ресурсов. 
    Какие задания он может выполнить, чтобы максимизировать награду?
    1 <= order_number <= 100
    1 <= limit <= 10000
    1 <= resources_for_orders[i] <= 100
    1 <= rewards[i] <= 100
    
    dp[i][j] - максимальная награда с тратой ресурсов <= j , если использовать
    только первые i поручений

    База
    dp[0][j] = 0 (так как выполняем 0 поручений)
    dp[i][0] = 0 (так как потрачено 0 ресурсов)
    
    Рассчет
    1) dp[i][j] = dp[i - 1][j] если кол-во ресурсов, требуемых за i-е поручение > j
    2) dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - resources[i]] + rewards[i]):
       1) Не берем i-й предмет, тогда берем ситуацию с такой же максимально
           допустимой суммарной наградой и первыми (i-1) поручениями
       2) Берем i-й предмет, тогда нужно взять максимульную награду
            без награды за это поручение
        
    Восстановление ответа
    Смотрим взяли ли мы i-е поручение:
    1) Если нет, то просто переходим к (i - 1) поручению (проверяем равны ли
       dp[i][j] и dp[i - 1][j])
    2) Если да, то переходим к (i - 1) поручению и вычитаем из j количество 
       потраченных ресурсов на i-е поручение
*/

#include <iostream>
#include <vector>

std::vector<size_t> Orders(size_t order_number, size_t limit,
                           std::vector<size_t>& resources,
                           std::vector<size_t>& rewards) {
  std::vector<std::vector<size_t> > dp(order_number + 1,
                                       std::vector<size_t>(limit + 1));
  for (size_t i = 1; i <= order_number; i++) {
    for (size_t j = 1; j <= limit; j++) {
      if (resources[i] > j) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] =
            std::max(dp[i - 1][j], dp[i - 1][j - resources[i]] + rewards[i]);
      }
    }
  }
  std::vector<size_t> orders;
  size_t orders_index = order_number;
  size_t max_resources_index = limit;
  while (orders_index > 0 && max_resources_index > 0) {
    if (dp[orders_index][max_resources_index] !=
        dp[orders_index - 1][max_resources_index]) {
      orders.push_back(orders_index);
      max_resources_index -= resources[orders_index];
    }
    orders_index--;
  }
  return orders;
}

void InputData(std::vector<size_t>& array) {
  for (size_t i = 1; i < array.size(); i++) {
    std::cin >> array[i];
  }
}

int main() {
  size_t order_number;
  size_t limit;
  std::cin >> order_number >> limit;
  std::vector<size_t> resources(order_number + 1);
  InputData(resources);
  std::vector<size_t> rewards(order_number + 1);
  InputData(rewards);
  std::vector<size_t> orders = Orders(order_number, limit, resources, rewards);
  for (size_t order : orders) {
    std::cout << order << "\n";
  }
}
