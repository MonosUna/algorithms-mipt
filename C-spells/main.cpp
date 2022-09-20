#include <algorithm>
#include <iostream>
using namespace std;
long long TryToFindMin(const int* a, int* opt, int i, int n) {
  int kl = 0, kp = 0, sl = 1, sp = 1;
  long long x1 = 0;
  while (i + sp < n && a[i + sp] >= a[i]) {
    ++kp;
    ++sp;
  }
  while (i - sl > -1 && a[i - sl] >= a[i]) {
    if (opt[i - sl] == 0) {
      ++kl;
      ++sl;
    } else {
      sl += opt[i - sl];
      kl += opt[i - sl];
    }
  }
  opt[i] = kl;
  x1 = (kl + kp + 1) * a[i];
  return x1;
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
    long long k = TryToFindMin(a, optimization, i, n);
    max1 = max(max1, k);
  }
  for (int i = 0; i < n; ++i) {
    cout << optimization[i] << " ";
  }
  cout << max1;
  delete[] a;
  delete[] optimization;
  return 0;
}