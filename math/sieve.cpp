template<int size>
struct sieve {
  sieve(): factor(), primes() {
    factor[0] = factor[1] = 1;
    for (int p = 2; p < size; ++p) {
      if (factor[p]) { continue; }
      primes.push_back(p);
      for (long long n = p*(long long)p; n < size; n += p) {
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
    assert(1 < n && n <= limit());
    return divisor(n) == n;
  }
  std::vector<int> prime_factors(int n) const {
    assert(0 < n && n <= limit());
    std::vector<int> ans;
    while (n > 1) {
      const auto p = divisor(n);
      ans.push_back(p);
      while (n % p == 0) { n /= p; }
    }
    return ans;
  }
  int factor[size];
  std::vector<int> primes;
};
