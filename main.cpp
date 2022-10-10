#include <deque>
#include <iostream>
using namespace std;
void DoEasyInput(deque<int>& first, deque<int>& second, int& count,
                 char type_of_operation, int number_of_goblin) {
  if (type_of_operation == '+' && count % 2 == 1) {
    second.push_back(number_of_goblin);
  }
  if (type_of_operation == '+' && count % 2 == 0) {
    second.push_back(number_of_goblin);
    int number_of_change = second.front();
    first.push_back(number_of_change);
    second.pop_front();
  }
  if (type_of_operation == '*' && count % 2 == 1) {
    second.push_front(number_of_goblin);
  }
  if (type_of_operation == '*' && count % 2 == 0) {
    first.push_back(number_of_goblin);
  }
}
void DoHardInput(deque<int>& first, deque<int>& second, int& count,
                 char type_of_operation) {
  if (type_of_operation == '-' && count % 2 == 1) {
    int number_of_outsider = first.front();
    cout << number_of_outsider << endl;
    first.pop_front();
  }
  if (type_of_operation == '-' && count % 2 == 0) {
    int number_of_outsider = first.front();
    cout << number_of_outsider << endl;
    first.pop_front();
    first.push_back(second.front());
    second.pop_front();
  }
}
int main() {
  deque<int> firsthalf;
  deque<int> secondhalf;
  firsthalf.clear();
  secondhalf.clear();
  int num = 0;
  int count = 0;
  cin >> num;
  for (int i = 0; i < num; i++) {
    char type_of_operation;
    int number = 0;
    cin >> type_of_operation;
    if (type_of_operation != '-') {
      cin >> number;
    }
    DoEasyInput(firsthalf, secondhalf, count, type_of_operation, number);
    DoHardInput(firsthalf, secondhalf, count, type_of_operation);
    if (type_of_operation != '-') {
      ++count;
    }
    if (type_of_operation == '-') {
      --count;
    }
  }
  return 0;
}