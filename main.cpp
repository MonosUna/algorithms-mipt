#include <deque>
#include <iostream>
struct GoblinsQueue
{
  std::deque<int> firsthalf;
  std::deque<int> secondhalf;
  int count = 0;

  void DoAdditionRequest(int number_of_goblin) {
    if (count % 2 == 1) {
      secondhalf.push_back(number_of_goblin);
    } else {
      secondhalf.push_back(number_of_goblin);
      int number_of_change = secondhalf.front();
      firsthalf.push_back(number_of_change);
      secondhalf.pop_front();
    }
  }

  void DoMultiplicationRequest(int number_of_goblin) {
    if (count % 2 == 1) {
      secondhalf.push_front(number_of_goblin);
    }
    if (count % 2 == 0) {
      firsthalf.push_back(number_of_goblin);
    }
  }

  void DoSubtractionRequest() {
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

  void DoInput(char type_of_input) {
    if (type_of_input == '+') {
      int number_of_goblin;
      std::cin >> number_of_goblin;
      DoAdditionRequest(number_of_goblin);
      count++;
    }
    if (type_of_input == '*') {
      int number_of_goblin;
      std::cin >> number_of_goblin;
      DoMultiplicationRequest(number_of_goblin);
      count++;
    }
    if (type_of_input == '-') {
      DoSubtractionRequest();
      count--;
    }
  }
};

int main() {
  int num = 0;
  std::cin >> num;
  GoblinsQueue queue;
  for (int i = 0; i < num; i++) {
    char type_of_input;
    std::cin >> type_of_input;
    queue.DoInput(type_of_input);
  }
  return 0;
}