namespace { // RollingHash

template<typename T, typename I, I... base>
class RollingHash {
  public:
    size_t static constexpr L = sizeof...(base);
    std::array<T, L> static constexpr p = { T(base)... };

    explicit RollingHash(std::string const &s_): s(s_), n(s_.size()), pow(), phash() {
      REP(z, L) {
        pow[z] = std::vector<T>(n+1);
        phash[z] = std::vector<T>(n+1);
        pow[z][0] = 1, phash[z][0] = 0;
      }
      REP(z, L) REP(i, n) {
        phash[z][i+1] = T(s[i]) + phash[z][i] * p[z];
        pow[z][i+1] = pow[z][i] * p[z];
      }
    }
    std::array<T, L> hash_substr(size_t i, size_t j) const {
      std::array<T, L> ret;
      REP(z, L) {
        ret[z] = phash[z][j] - phash[z][i] * pow[z][j-i];
      }
      return ret;
    }

  private:
    std::string s;
    int n;
    std::array<std::vector<T>, L> pow;
    std::array<std::vector<T>, L> phash;
};

template<typename T, typename I, I... base>
std::array<T, RollingHash<T, I, base...>::L> const RollingHash<T, I, base...>::p;

} // namespace
