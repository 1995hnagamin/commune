struct BIT {
  typedef int T;
  const T zero = 0;
  vector<T> bit;
  int n;
  BIT(int n_, T initializer) {
    n = n_;
    bit.reserve(n + 1);
    for (int i = 0; i < n + 1; i++) {
      bit[i] = initializer;
    }
  }

  T sum(int i) {
    T s = 0;
    while (i > 0) {
      s += bit[i];
      i -= i & -i;
    }
    return s;
  }

  void add(int i, T x) {
    while (i <= n) {
      bit[i] += x;
      i += i & -i;
    }
  }
};
