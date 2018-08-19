template<typename T, int N>
class Bit {
  public:
    Bit(T z): zero(z), bit() {
      std::fill(bit.begin(), bit.end(), zero);
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
    T const zero;
    std::array<T, N+1> bit;
};
