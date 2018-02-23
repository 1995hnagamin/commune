template<typename T>
class Matrix {
  private:
    int m, n;
    vector<vector<T>> data;
  public:
    Matrix(const vector<vector<T>>& data_) :
      m(static_cast<int>(data_.size())), n(static_cast<int>(data_.front().size())), data(data_) {;}
    Matrix(const vector<T> &vec) :
      m(static_cast<int>(vec.size())), n(1), data(vector<vector<T>>(n, vector<T>(1))) {
        REP(i, m) { data[i][0] = vec[i]; }
      }
    Matrix(int n_) : m(n_), n(n_), data(vector<vector<T>>(n, vector<T>(n))) {;}
    Matrix(int m_, int n_) : m(m_), n(n_), data(vector<vector<T>>(m, vector<T>(n))) {;}
    const T& get(int i, int j) const { return data[i][j]; }
    T& get(int i, int j) { return data[i][j]; }
    int row() const { return m; }
    int colomn() const { return n; }

    static Matrix identity(int n) {
      Matrix I(n);
      REP(i, n) { I.get(i, i) = static_cast<T>(1); }
      return I;
    }

    const Matrix operator-() {
      Matrix result(row(), colomn());
      REP(i, row()) REP(j, colomn()) { result.get(i, j) = -get(i, j); }
      return result;
    }
    const Matrix operator+(const Matrix rhs) {
      int m = row(), n = colomn();
      if (m != rhs.row() || n != rhs.colomn()) {
        cerr << "cannot add (" << m << "x" << n << ") Matrix & (" << rhs.row() << "x" << rhs.colomn() << ") Matrix";
        throw;
      }
      Matrix result(m, n);
      REP(i, m) REP(j, n) { result.get(i, j) = get(i, j) + rhs.get(i, j); }
      return result;
    }
    const Matrix operator-(const Matrix &rhs) {
      return *this + (-rhs);
    }
    const Matrix operator*(const Matrix &rhs) {
      if (colomn() != rhs.row()) {
        cerr << "cannot multiply (" << row() << "x" << colomn() << ") Matrix & (" << rhs.row() << "x" << rhs.colomn() << ") Matrix";
        throw;
      }
      int m = row(), n = rhs.colomn();
      Matrix result(m, n);
      REP(i, m) REP(j, n) {
        REP(k, colomn()) { result.get(i, j) += get(i, k) * rhs.get(k, j); }
      }
      return result;
    }
    const Matrix operator*(T lambda) {
      Matrix result = this;
      REP(i, row()) REP(j, colomn()) { result.get(i, j) *= lambda; }
      return result;
    }
    const Matrix operator^(int n) {
      if (n == 0) return identity(row());
      if (n % 2 == 0) {
        Matrix square = (*this) * (*this);
        return square ^ (n / 2);
      }
      Matrix recurs = (*this) ^ (n - 1);
      return (*this) * recurs;
    }
};

template<typename T>
Matrix<T> transpose(Matrix<T> matrix) {
  Matrix<T> result(matrix.colomn(), matrix.row());
  REP(i, matrix.row()) REP(j, matrix.colomn()) { result.get(j, i) = matrix.get(i, j); }
  return result;
}

template<typename T>
const Matrix<T> operator*(T lambda, const Matrix<T> &rhs) {
  return rhs * lambda;
}

template<typename T>
const Matrix<T> amendVertical(const Matrix<T> &upper, const Matrix<T> &lower) {
  if (upper.colomn() != lower.colomn()) {
    cerr << "cannot vertically amend (" << upper.row() << "x" << upper.colomn() << ") Matrix & ("
      << lower.row() << "x" << lower.colomn() << ") Matrix";
    throw;
  }
  int m1 = upper.row(), m2 = lower.row(), n = upper.colomn();
  Matrix<T> result(m1 + m2, n);
  REP(i, m1) REP(j, n) { result.get(i, j) = upper.get(i, j); }
  REP(i, m2) REP(j, n) { result.get(m1 + i, j) = lower.get(i, j); }
  return result;
}

template<typename T>
const Matrix<T> amendHorizontal(const Matrix<T> &left, const Matrix<T> &right) {
  if (left.row() != right.row()) {
    cerr << "cannot horizontally amend (" << left.row() << "x" << left.colomn() << ") Matrix & ("
      << right.row() << "x" << right.colomn() << ") Matrix";
    throw;
  }
  Matrix<T> trans = amendVertical(left.transpose(), right.transpose());
  return trans.transpose();
}
