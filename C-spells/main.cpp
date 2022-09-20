#include <algorithm>
#include <iostream>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n = 0;
  long long max1 = 0;
  cin >> n;
  int* a = new int[n];
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    long long kl = 0, kp = 0, sl = 1, sp = 1;
    while (i - sl > -1 && a[i - sl] >= a[i]) {
      ++kl;
      ++sl;
    }
    while (i + sp < n && a[i + sp] >= a[i]) {
      ++kp;
      ++sp;
    }
    max1 = max((kl + kp + 1) * a[i], max1);
  }
  cout << max1;
  delete[] a;
  return 0;
}