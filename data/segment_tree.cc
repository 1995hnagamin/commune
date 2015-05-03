#include<vector>
using namespace std;

struct segment_tree {
  typedef int T;
  vector<T> dat;
  int n;
  const T empty = 1 << 17;
  T min(T x, T y) {
    return (x < y ? x : y);
  }
  
  segment_tree(int n_) {
    n = 1;
    while (n < n_) {
      n *= 2;
    }
    dat.reserve(2 * n - 1);
    for (int i = 0; i < 2 * n - 1; i++) {
      dat[i] = empty;
    }
  }

  void update(int k, T a) {
    k += n - 1;
    dat[k] = a;
    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
    }
  }

  // min([a, b))
  T query(int a, int b, int k, int l, int r) {
    if (r <= a || b <= l) {
      return empty;
    } else if (a <= l && r <= b) {
      return dat[k];
    } else {
      T vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
      T vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
      return min(vl, vr);
    }
  }

  T query(int a, int b) {
    return query(a, b, 0, 0, n);
  }
};

