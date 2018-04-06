template<typename T, T inf>
class Lis {
  public:
    Lis(std::vector<T> const &s):
      n(s.size()), seq(s), dp(n, inf) {}
    size_t solve() {
      for (size_t i = 0; i < n; ++i) {
        *std::lower_bound(dp.begin(), dp.end(), seq[i]) = seq[i];
      }
      return std::distance(
          dp.begin(),
          std::lower_bound(dp.begin(), dp.end(), inf));
    }
    size_t solve(bool (*comp)(T const &, T const &)) {
      for (size_t i = 0; i < n; ++i) {
        *std::lower_bound(dp.begin(), dp.end(), seq[i], comp) = seq[i];
      }
      return std::distance(
          dp.begin(),
          std::lower_bound(dp.begin(), dp.end(), inf));
    }
  private:
    size_t const n;
    std::vector<T> const seq;
    std::vector<T> dp;
};
