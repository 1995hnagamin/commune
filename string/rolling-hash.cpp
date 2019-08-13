template<typename T, size_t L, typename I = T>
class RollingHash {
  public:
    explicit RollingHash(std::string const &s, std::array<I, L> const &base):
      p(convert(base)), str(s), n(str.size()), pow(), phash() {
      for (size_t z = 0; z < L; ++z) {
        pow[z] = std::vector<T>(n+1);
        phash[z] = std::vector<T>(n+1);
        pow[z][0] = 1, phash[z][0] = 0;
      }
      for (size_t z = 0; z < L; ++z) for (size_t i = 0; i < n; ++i) {
        phash[z][i+1] = T(str[i]) + phash[z][i] * p[z];
        pow[z][i+1] = pow[z][i] * p[z];
      }
    }
    size_t size() const { return n; }
    std::string to_string() const { return str; }
    // [i, j)
    std::array<T, L> hash_range(size_t i, size_t j) const {
      std::array<T, L> ret;
      for (size_t z = 0; z < L; ++z) {
        ret[z] = phash[z][j] - phash[z][i] * pow[z][j-i];
      }
      return ret;
    }
    void append(std::string const &s) {
      size_t const len = s.size();
      for (size_t z = 0; z < L; ++z) for (size_t i = 0; i < len; ++i) {
        phash[z].push_back(T(s[i]) + phash[z].back() * p[z]);
        pow[z].push_back(pow[z].back() * p[z]);
      }
      str += s;
      n += len;
    }
  private:
    static std::array<T, L> convert(std::array<I, L> const &v) {
      auto const n = v.size();
      std::array<T, L> w;
      for (size_t i = 0; i < n; ++i) {
        w[i] = static_cast<T>(v[i]);
      }
      return w;
    }

  public:
    std::array<T, L> const p;
  private:
    std::string str;
    size_t n;
    std::array<std::vector<T>, L> pow;
    std::array<std::vector<T>, L> phash;
};
