template<int size>
struct Sieve {
  constexpr Sieve(): factor() {
    factor[0] = factor[1] = 1;
    for (int p = 2; p < size; ++p) {
      if (factor[p]) { continue; }
      for (int n = 2*p; n < size; n += p) {
        factor[n] = p;
      }
    }
  }
  constexpr bool is_prime(int n) const {
    assert(n < size);
    return !(factor[n]);
  }
  int factor[size];
};
