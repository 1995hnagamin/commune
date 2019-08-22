std::vector<size_t>
manacher(std::string const &S) {
  size_t i = 0, j = 0;
  const auto len = static_cast<size_t>(S.size());
  std::vector<size_t> R(len, 0);
  while (i < len) {
    while (i >= j && i+j < len && S[i-j] == S[i+j]) { ++j; }
    R[i] = j;
    size_t k = 1;
    while (i >= k && i+k < len && k+R[i-k] < j) {
      R[i+k] = R[i-k];
      ++k;
    }
    i += k; j -= k;
  }
  return R;
}
