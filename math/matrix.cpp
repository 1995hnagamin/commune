namespace  { // Matrix

template<typename T>
class Vec {
  public:
    using type = std::vector<T>;

    explicit Vec(size_t s): size_(s), p(std::make_unique<type>(s)) {}
    explicit Vec(type const &v): size_(v.size()), p(std::make_unique<type>(v)) {}
    Vec(Vec const &v) = delete;
    Vec &operator=(Vec const &) = delete;
    Vec(Vec &&v) noexcept = default;
    Vec &operator=(Vec &&v) noexcept = default;
    ~Vec() = default;

    Vec clone() const {
      auto v = static_cast<Vec>(*p);
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
class Matrix {
  public:
    using vec_type = std::vector<T>;
    using type = std::vector<vec_type>;

    explicit Matrix(size_t h, size_t w):
      width_(w), height_(h), p(std::make_unique<type>(h, vec_type(w))) {}
    explicit Matrix(size_t n): Matrix(n, n) {}
    explicit Matrix(type const &m):
      width_(m[0].size()), height_(m.size()), p(std::make_unique<type>(m)) {}
    Matrix(Matrix const &m) = delete;
    Matrix &operator=(Matrix const &m) = delete;
    Matrix(Matrix &&m) noexcept = default;
    Matrix &operator=(Matrix &&m) noexcept = default;
    ~Matrix() = default;

    Matrix clone() const {
      auto m = static_cast<Matrix>(*p);
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
    static Matrix identity(size_t n) {
      Matrix A(n);
      for (int i = 0; i < n; ++i) {
        A.set(i, i, -1);
      }
      return A;
    }
  private:
    size_t width_;
    size_t height_;
    std::unique_ptr<type> p;
};

template<typename T>
Vec<T> operator*(Matrix<T> const &A, Vec<T> const &x) {
  Vec<T> y(A.height());
  for (size_t i = 0, h = A.height(); i < h; ++i)
    for (size_t j = 0, w = A.width(); j < w; ++j)
      y[i] += A[i][j] * x[j];
  return y;
}

template<typename T>
Matrix<T> operator*(Matrix<T> const &A, Matrix<T> const &B) {
  assert(A.width() == B.height());
  Matrix<T> C(A.height(), B.width());
  for (size_t i = 0, h = A.height(); i < h; ++i)
    for (size_t k = 0, r = A.width(); k < r; ++k)
      for (size_t j = 0, w = B.width(); j < w; ++j)
        C[i][j] += A[i][k] * B[k][j];
  return C;
}

template<typename T>
Matrix<T> pow(Matrix<T> const &A, int n) {
  if (n == 0) {
    return Matrix<T>::identity(A.height());
  } else if (n % 2 > 0) {
    return A * pow(A, n-1);
  } else {
    return pow(A * A, n/2);
  }
}

} // namespace
