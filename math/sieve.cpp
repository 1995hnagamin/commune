template<int size>
struct Sieve {
  Sieve(): factor(), primes() {
    factor[0] = factor[1] = 1;
    for (int p = 2; p < size; ++p) {
      if (factor[p]) { continue; }
      primes.push_back(p);
      for (int n = 2*p; n < size; n += p) {
        factor[n] = p;
      }
    }
  }
  long long int limit() const {
    const auto p = static_cast<long long int>(primes.back());
    return p * p;
  }
  int divisor(int n) const {
    assert(1 < n && n <= limit());
    if (n < size) { return factor[n]? factor[n]:n; }
    for (auto &&p : primes) {
      if (n % p == 0) { return p; }
    }
    return n;
  }
  bool is_prime(int n) const {
    assert(n < size);
    return !(factor[n]);
  }
  int factor[size];
  std::vector<int> primes;
};
