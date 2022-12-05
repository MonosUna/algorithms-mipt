#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
class HashTable {
 private:
  std::vector<std::list<int>> array_;
  int size_;
  int HashFunction(int number) { return (number * 123 + 47) % size_; }

 public:
  HashTable(int count) {
    size_ = count;
    std::vector<std::list<int>> new_array(size_);
    array_ = new_array;
  }
  void Add(int number);
  void Erase(int number);
  std::string Find(int number);
};

void HashTable::Add(int number) {
  int place = HashFunction(number);
  array_[place].push_back(number);
}

void HashTable::Erase(int number) {
  int place = HashFunction(number);
  array_[place].remove(number);
}

std::string HashTable::Find(int number) {
  int place = HashFunction(number);
  std::string answer = "NO";
  auto is_there_that_num =
      std::find(array_[place].begin(), array_[place].end(), number);
  if (is_there_that_num != array_[place].end()) {
    answer = "YES";
  }
  return answer;
}

int main() {
  int count_of_requests;
  std::cin >> count_of_requests;
  HashTable my_struct(count_of_requests);
  for (int i = 0; i < count_of_requests; ++i) {
    char type;
    int number;
    std::cin >> type >> number;
    if (type == '+') {
      my_struct.Add(number);
    }
    if (type == '-') {
      my_struct.Erase(number);
    }
    if (type == '?') {
      std::cout << my_struct.Find(number) << "\n";
    }
  }
  return 0;
}
