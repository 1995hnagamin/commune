namespace { // Permutation

class permutation {
  public:
    explicit permutation(size_t n): dat(n) {
      for (size_t i = 0; i < n; ++i) { dat[i] = i; }
    }
    explicit permutation(std::vector<size_t> const &v): dat(v) {}
    size_t at(size_t i) const { return dat[i]; }
    size_t size() const { return dat.size(); }
  private:
    std::vector<size_t> dat;
};

permutation const
compose(permutation const &sigma, permutation const &tau) {
  assert(sigma.size() == tau.size());
  const auto n = sigma.size();
  std::vector<size_t> v;
  for (size_t i = 0; i < n; ++i) {
    v[i] = sigma.at(tau.at(i));
  }
  return permutation(v);
}

permutation const
operator *(permutation const &sigma, permutation const &tau) {
  return compose(sigma, tau);
}

permutation const
inverse(permutation const &sigma) {
  const auto n = sigma.size();
  std::vector<size_t> v(n);
  for (size_t i = 0; i < n; ++i) {
    v[sigma.at(i)] = i;
  }
  return permutation(v);
}

permutation const
pow(permutation const &sigma, size_t n) {
  permutation x(n);
  permutation a = sigma;
  while (n) {
    if (n & 1) { x = x * a; }
    a = a * a;
    n >>= 1;
  }
  return x;
}

std::vector<std::vector<size_t>>
cycle_decomposition(permutation const &sigma) {
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
