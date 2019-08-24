template<typename T, typename Iterator>
std::vector<T> reservoir_sampling(Iterator first, Iterator last, int k) {
  std::vector<T> ret(k);
  Iterator iter = first; int n;
  for (n = 0; n < k; ++n, ++iter) { ret[n] = *iter; }
  std::random_device rd; std::mt19937 g(rd());
  for (; iter != last; ++iter, ++n) {
    std::uniform_int_distribution<> dis(0, n-1);
    auto const r = dis(g);
    if (r < k) {
      ret[r] = *iter;
    }
  }
  return ret;
}
