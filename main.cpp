#include <cmath>
#include <iomanip>
#include <iostream>
int main() {
  int count;
  std::cin >> count;
  long double* height = new long double[count];
  long double* prefix_log = new long double[count];
  std::cin >> height[0];
  prefix_log[0] = log2l(height[0]);
  for (int i = 1; i < count; ++i) {
    std::cin >> height[i];
    prefix_log[i] = prefix_log[i - 1] + log2l(height[i]);
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int leftindex, rightindex;
    std::cin >> leftindex >> rightindex;
    long double resultlog;
    if (leftindex == 0) {
      resultlog = prefix_log[rightindex];
    } else {
      resultlog = prefix_log[rightindex] - prefix_log[leftindex - 1];
    }
    resultlog = resultlog / (rightindex - leftindex + 1);
    std::cout << std::fixed << std::showpoint << std::setprecision(6);
    std::cout << exp2l(resultlog) << "\n";
  }
  delete[] height;
  delete[] prefix_log;
  return 0;
}
