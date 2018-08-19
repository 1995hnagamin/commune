template<typename T, size_t max>
class BinomDist {
  public:
    constexpr BinomDist(T p): dp() {
      dp[0][0] = static_cast<T>(1);
      for (size_t n = 1; n <= max; ++n) {
        dp[n][n] = std::pow(p, n); dp[n][0] = std::pow(1-p, n);
        for (size_t k = 1; k < n; ++k) {
          dp[n][k] = dp[n-1][k-1]*p + dp[n-1][k]*(1-p);
        }
      }
    }
    constexpr T prob(int n, int k) const {
      assert(n >= k);
      return dp[n][k];
    }
  private:
    T dp[max+1][max+1];
};
