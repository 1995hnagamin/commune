namespace { // rolling-hash

template <typename T, size_t L>
struct memoized_expt {
  memoized_expt(std::array<T, L> const &base, size_t n): p(base), table(), sz(n) {
    for (size_t z = 0; z < L; ++z) {
      table[z] = std::vector<T>(n+1);
      table[z][0] = static_cast<T>(1);
    }
    for (size_t z = 0; z < L; ++z) for (size_t i = 0; i < n; ++i) {
      table[z][i+1] = table[z][i] * p[z];
    }
  }
  T pow(size_t z, int i) const {
    return table[z][i];
  }
  void extend(size_t diff) {
    for (size_t z = 0; z < L; ++z) for (size_t i = 0; i < diff; ++i) {
      table[z].push_back(table[z].back() * p[z]);
    }
    sz += diff;
  }
  std::array<T, L> p;
  std::array<std::vector<T>, L> table;
  size_t sz;
};

template <typename T, size_t L>
struct sq_expt {
  sq_expt(std::array<T, L> const &base, size_t): p(base) { }
  T pow(size_t z, int k) const {
    T val(1), a(p[z]);
    while (k > 0) {
      if (k & 1) { val *= a; }
      a *= a; k >>= 1;
    }
    return val;
  }
  void extend(size_t) { }
  std::array<T, L> p;
};

template<typename T, size_t L, template <class, size_t> class Pow = memoized_expt>
class rolling_hash {
  public:
    template <typename I>
    explicit rolling_hash(std::string const &s, std::array<I, L> const &base):
      str(s), n(str.size()), pow(convert(base), n), phash() {
      for (size_t z = 0; z < L; ++z) {
        phash[z] = std::vector<T>(n+1);
        phash[z][0] = 0;
        for (size_t i = 0; i < n; ++i) {
          phash[z][i+1] = T(str[i]) + phash[z][i] * pow.p[z];
        }
      }
    }
    size_t size() const { return n; }
    std::string to_string() const { return str; }
    // [i, j)
    std::array<T, L> hash_range(size_t i, size_t j) const {
      std::array<T, L> ret;
      for (size_t z = 0; z < L; ++z) {
        ret[z] = phash[z][j] - phash[z][i] * pow.pow(z, j-i);
      }
      return ret;
    }
    void append(std::string const &s) {
      size_t const len = s.size();
      for (size_t z = 0; z < L; ++z) for (size_t i = 0; i < len; ++i) {
        phash[z].push_back(T(s[i]) + phash[z].back() * pow.p[z]);
      }
      for (auto &&c: s) { str.push_back(c); }
      n += len;
    }
  private:
    template <typename I>
    static std::array<T, L> convert(std::array<I, L> const &v) {
      std::array<T, L> w;
      for (size_t i = 0, n = v.size(); i < n; ++i) {
        w[i] = static_cast<T>(v[i]);
      }
      return w;
    }

  private:
    std::string str;
    size_t n;
    Pow<T, L> pow;
    std::array<std::vector<T>, L> phash;
};

} // namespace
