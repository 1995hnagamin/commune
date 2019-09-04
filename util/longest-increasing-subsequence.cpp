template <typename T>
size_t longest_incr_subseq(std::vector<T> const &seq, T infty) {
  size_t const n = seq.size();
  std::vector<T> dp(n, infty);
  for (size_t i = 0; i < n; ++i) {
    *std::lower_bound(begin(dp), end(dp), seq[i]) = seq[i];
  }
  return std::distance(
      begin(dp),
      std::lower_bound(begin(dp), end(dp), infty));
}

template <typename T, typename FnT>
size_t longest_incr_subseq(std::vector<T> const &seq, T infty, FnT comp) {
  size_t const n = seq.size();
  std::vector<T> dp(n, infty);
  for (size_t i = 0; i < n; ++i) {
    *std::lower_bound(begin(dp), end(dp), seq[i], comp) = seq[i];
  }
  return std::distance(
      begin(dp),
      std::lower_bound(begin(dp), end(dp), infty));
}
