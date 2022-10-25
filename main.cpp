//В первой строке входных данный записано число
// N (1 ≤ N ≤ 105) — количество запросов к программе.
// Следующие N строк содержат описание запросов в формате:
//«+ i» — гоблин с номером i (1 ≤ i ≤ N) встает в конец очереди;
//«* i» — привилегированный гоблин с номером i встает в середину очереди;
//«-» — первый гоблин из очереди уходит к шаманам.
// Гарантируется, что на момент такого запроса очередь не пуста.
//Для каждого запроса типа «-» программа должна вывести номер гоблина,
// который должен зайти к шаманам.
#include <deque>
#include <iostream>
struct GoblinsQueue {
  std::deque<int> firsthalf;
  std::deque<int> secondhalf;
  int count = 0;
  void AddInTheUsualWay(int number_of_goblin);
  void AddWithPriority(int number_of_goblin);
  void DoSubtractionRequest();
};

void GoblinsQueue::AddInTheUsualWay(int number_of_goblin) {
  if (count % 2 == 1) {
    secondhalf.push_back(number_of_goblin);
  } else {
    secondhalf.push_back(number_of_goblin);
    int number_of_change = secondhalf.front();
    firsthalf.push_back(number_of_change);
    secondhalf.pop_front();
  }
}

void GoblinsQueue::AddWithPriority(int number_of_goblin) {
  if (count % 2 == 1) {
    secondhalf.push_front(number_of_goblin);
  }
  if (count % 2 == 0) {
    firsthalf.push_back(number_of_goblin);
  }
}

void GoblinsQueue::DoSubtractionRequest() {
  if (count % 2 == 1) {
    int number_of_outsider = firsthalf.front();
    std::cout << number_of_outsider << '\n';
    firsthalf.pop_front();
  }
  if (count % 2 == 0) {
    int number_of_outsider = firsthalf.front();
    std::cout << number_of_outsider << '\n';
    firsthalf.pop_front();
    firsthalf.push_back(secondhalf.front());
    secondhalf.pop_front();
  }
}

int main() {
  int num = 0;
  std::cin >> num;
  GoblinsQueue queue;
  for (int i = 0; i < num; i++) {
    char type_of_input;
    std::cin >> type_of_input;
    if (type_of_input == '+') {
      int number_of_goblin;
      std::cin >> number_of_goblin;
      queue.AddInTheUsualWay(number_of_goblin);
      queue.count++;
    }
    if (type_of_input == '*') {
      int number_of_goblin;
      std::cin >> number_of_goblin;
      queue.AddWithPriority(number_of_goblin);
      queue.count++;
    }
    if (type_of_input == '-') {
      queue.DoSubtractionRequest();
      queue.count--;
    }
  }
  return 0;
}