namespace  { // Matrix

template<typename T>
class vec {
  public:
    using type = std::vector<T>;

    explicit vec(size_t s): size_(s), p(std::make_unique<type>(s)) {}
    explicit vec(type const &v): size_(v.size()), p(std::make_unique<type>(v)) {}
    vec(vec const &v) = delete;
    vec &operator=(vec const &) = delete;
    vec(vec &&v) noexcept = default;
    vec &operator=(vec &&v) noexcept = default;
    ~vec() = default;

    vec clone() const {
      auto v = static_cast<vec>(*p);
      return v;
    }
    size_t const size() const {
      return size_;
    }
    T &operator[](size_t i) {
      return (*p)[i];
    }
    T const &operator[](size_t i) const {
      return (*p)[i];
    }
    T const at(size_t i) const {
      return (*p)[i];
    }
    void set(size_t i, T x) {
      (*p)[i] = x;
    }
  private:
    size_t size_;
    std::unique_ptr<type> p;
};

template <typename T>
class matrix {
  public:
    using vec_type = std::vector<T>;
    using type = std::vector<vec_type>;

    explicit matrix(size_t h, size_t w):
      width_(w), height_(h), p(std::make_unique<type>(h, vec_type(w))) {}
    explicit matrix(size_t n): matrix(n, n) {}
    explicit matrix(type const &m):
      width_(m[0].size()), height_(m.size()), p(std::make_unique<type>(m)) {}
    matrix(matrix const &m) = delete;
    matrix &operator=(matrix const &m) = delete;
    matrix(matrix &&m) noexcept = default;
    matrix &operator=(matrix &&m) noexcept = default;
    ~matrix() = default;

    matrix clone() const {
      auto m = static_cast<matrix>(*p);
      return m;
    }
    size_t const width() const {
      return width_;
    }
    size_t const height() const {
      return height_;
    }
    T const at(size_t i, size_t j) const {
      return (*p)[i][j];
    }
    vec_type &operator[](size_t i) {
      return (*p)[i];
    }
    vec_type const &operator[](size_t i) const {
      return (*p)[i];
    }
    void set(size_t i, size_t j, T x) {
      (*p)[i][j] = x;
    }
    static matrix identity(size_t n) {
      matrix A(n);
      for (int i = 0; i < n; ++i) {
        A.set(i, i, 1);
      }
      return A;
    }
  private:
    size_t width_;
    size_t height_;
    std::unique_ptr<type> p;
};

template<typename T>
vec<T> operator*(matrix<T> const &A, vec<T> const &x) {
  vec<T> y(A.height());
  for (size_t i = 0, h = A.height(); i < h; ++i)
    for (size_t j = 0, w = A.width(); j < w; ++j)
      y[i] += A[i][j] * x[j];
  return y;
}

template<typename T>
matrix<T> operator*(matrix<T> const &A, matrix<T> const &B) {
  assert(A.width() == B.height());
  matrix<T> C(A.height(), B.width());
  for (size_t i = 0, h = A.height(); i < h; ++i)
    for (size_t k = 0, r = A.width(); k < r; ++k)
      for (size_t j = 0, w = B.width(); j < w; ++j)
        C[i][j] += A[i][k] * B[k][j];
  return C;
}

template<typename T>
matrix<T> pow(matrix<T> const &A, lli n) {
  auto M = A.clone();
  auto ans = matrix<T>::identity(M.height());
  while (n > 0) {
    if (n & 1) {
      ans = ans * M;
    }
    M = M * M;
    n >>= 1;
  }
  return ans;
}

} // namespace
