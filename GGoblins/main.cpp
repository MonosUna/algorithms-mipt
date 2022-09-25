#include <deque>
#include <iostream>
using namespace std;
void Vhod1(deque<int>& first, deque<int>& second, int& count, char k, int i) {
  if (k == '+' && count % 2 == 1) {
    second.push_back(i);
  }
  if (k == '+' && count % 2 == 0) {
    second.push_back(i);
    int r = second.front();
    first.push_back(r);
    second.pop_front();
  }
  if (k == '*' && count % 2 == 1) {
    second.push_front(i);
  }
  if (k == '*' && count % 2 == 0) {
    first.push_back(i);
  }
}
void Vhod2(deque<int>& first, deque<int>& second, int& count, char k) {
  if (k == '-' && count % 2 == 1) {
    int r = first.front();
    cout << r << endl;
    first.pop_front();
  }
  if (k == '-' && count % 2 == 0) {
    int r = first.front();
    cout << r << endl;
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
    char vvod1;
    int vvod2 = 0;
    cin >> vvod1;
    if (vvod1 != '-') {
      cin >> vvod2;
    }
    Vhod1(firsthalf, secondhalf, count, vvod1, vvod2);
    Vhod2(firsthalf, secondhalf, count, vvod1);
    if (vvod1 != '-') {
      ++count;
    }
    if (vvod1 == '-') {
      --count;
    }
  }
  return 0;
}