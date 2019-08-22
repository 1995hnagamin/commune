template<typename T>
class fenwick_tree {
  public:
    fenwick_tree(size_t size, T z): N(size), zero(z), bit(size+1, z) {
    }

    // [1,k]
    T sum(size_t k) const {
      T s = zero;
      for (size_t i = k; i > 0; i -= i&(-i)) { s += bit[i]; }
      return s;
    }

    // [l,r)
    T sum(size_t l, size_t r) const {
      assert(0 < l && l <= r);
      return sum(r-1) - sum(l-1);
    }

    void add(int k, T x) {
      for (size_t i = k; i <= N; i += i&(-i)) { bit[i] += x; }
    }

  private:
    size_t const N;
    T const zero;
    std::vector<T> bit;
};
