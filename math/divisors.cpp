template <typename T>
std::vector<T> divisors(T M) {
  std::vector<T> ans;
  T n = 0;
  for (n = 1; n * n < M; ++n) {
    if (M % n == 0) {
      ans.push_back(n);
      ans.push_back(M / n);
    }
  }
  if (n * n == M) {
    ans.push_back(n);
  }
  return ans;
}
