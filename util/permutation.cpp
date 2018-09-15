namespace { // Permutation

class Permutation {
  public:
    explicit Permutation(size_t n): dat(n) {
      for (size_t i = 0; i < n; ++i) { dat[i] = i; }
    }
    explicit Permutation(std::vector<size_t> const &v): dat(v) {}
    size_t at(size_t i) const { return dat[i]; }
    size_t size() const { return dat.size(); }
  private:
    std::vector<size_t> dat;
};

Permutation const
compose(Permutation const &sigma, Permutation const &tau) {
  assert(sigma.size() == tau.size());
  const auto n = sigma.size();
  std::vector<size_t> v;
  for (size_t i = 0; i < n; ++i) {
    v[i] = sigma.at(tau.at(i));
  }
  return Permutation(v);
}

Permutation const
operator *(Permutation const &sigma, Permutation const &tau) {
  return compose(sigma, tau);
}

Permutation const
inverse(Permutation const &sigma) {
  const auto n = sigma.size();
  std::vector<size_t> v(n);
  for (size_t i = 0; i < n; ++i) {
    v[sigma.at(i)] = i;
  }
  return Permutation(v);
}

Permutation const
pow(Permutation const &sigma, size_t n) {
  Permutation x(n);
  Permutation a = sigma;
  while (n) {
    if (n & 1) { x = x * a; }
    a = a * a;
    n >>= 1;
  }
  return x;
}

std::vector<std::vector<size_t>>
cycle_decomposition(Permutation const &sigma) {
  size_t const n = sigma.size();
  std::vector<std::vector<size_t>> ans;
  std::vector<bool> used(n);
  for (size_t start = 0; start < n; ++start) {
    if (used[start]) { continue; }
    size_t i = start;
    std::vector<size_t> v;
    while (!used[i]) {
      v.push_back(i);
      used[i] = true;
      i = sigma.at(i);
    }
    ans.push_back(v);
  }
  return ans;
}

} // namespace
