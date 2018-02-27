template<typename T, int size>
class Bit {
  public:
    Bit(T z): zero(z) {
      for (int i = 0; i <= N; ++i) {
        bit[i] = zero;
      }
    }

    // [1,k]
    T sum(int k) const {
      T s = zero;
      for (int i = k; i > 0; i -= i&(-i)) {
        s += bit[i];
      }
      return s;
    }

    // [l,r)
    T sum(int l, int r) const {
      return sum(r-1) - sum(l-1);
    }

    void add(int k, T x) {
      for (int i = k; i <= N; i += i&(-i)) {
        bit[i] += x;
      }
    }

  private:
    int const N = size;
    T const zero;
    std::array<T, size+1> bit;
};
