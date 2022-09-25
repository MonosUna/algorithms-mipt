#include <algorithm>
#include <iostream>
using namespace std;
int TryToFindMin(const int* a, int* opt, int i, int n) {
  int kl = 0, kp = 0, sl = 1, sp = 1;
  while (i + sp < n && a[i + sp] >= a[i]) {
    ++kp;
    ++sp;
  }
  while (i - sl > -1 && a[i - sl] >= a[i]) {
    kl += opt[i - sl] + 1;
    sl += opt[i - sl] + 1;
  }
  opt[i] = kl;
  return kl + kp + 1;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n = 0;
  long long max1 = 0;
  cin >> n;
  int* a = new int[n];
  int* optimization = new int[n];
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  for (int i = 0; i < n; ++i) {
    long long y = (TryToFindMin(a, optimization, i, n)), x = a[i];
    long long k = x * y;
    max1 = max(max1, k);
  }
  cout << max1;
  delete[] a;
  delete[] optimization;
  return 0;
}