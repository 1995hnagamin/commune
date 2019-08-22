namespace { // Fibonacci

template <typename T, size_t N>
class fibonacci_seq {
  public:
    static_assert(N >= 2, "N must be >= 2");
    constexpr fibonacci_seq(T zth, T fst): dat() {
      dat[0] = zth, dat[1] = fst;
      for (size_t i = 2; i < N; ++i) { dat[i] = dat[i-1] + dat[i-2]; }
    }
    constexpr fibonacci_seq(): fibonacci_seq(0, 1) {
    }
    constexpr T operator[] (size_t i) const {
      assert(i < N);
      return dat[i];
    }
  private:
    T dat[N];
};

template <size_t N, typename T>
constexpr std::bitset<N> zeckendorf_sum(T n) {
  auto constexpr F = fibonacci_seq<T, N+1>(1, 2);
  assert(n < F[N]);
  std::bitset<N> used(0);
  size_t i = N - 1;
  while (n > 0) {
    if (F[i] <= n) {
      used[i] = true;
      n -= F[i], i -= 2;
    } else {
      i -= 1;
    }
  }
  return used;
}

// O(Cap * 1.62^N)
template <size_t Cap, typename FnT>
void zeckendorf_scan(size_t N, FnT fn) {
  assert(N <= Cap);
  using T = uint64_t;
  auto const limit = fibonacci_seq<T, Cap+1>(1, 2)[N];
  for (T s = 0; s < limit; ++s) {
    fn(zeckendorf_sum<Cap>(s));
  }
}

} // namespace
