template <typename T>
class Imos2D {
  public:
    Imos2D(size_t r, size_t c): r(r), c(c), area(r+1, std::vector<T>(c+1, 0)) {}
    void add(int bi, int bj, int ei, int ej) {
      bi = std::max(bi, 0); bj = std::max(bj, 0);
      ei = std::min(ei, (int)r); ej = std::min(ej, (int)c);
      ++area[bi][bj];
      --area[bi][ej+1];
      --area[ei+1][bj];
      ++area[ei+1][ej+1];
    }
    void accumulate() {
      for (size_t i = 0; i <= r; ++i) for (size_t j = 1; j <= c; ++j) {
        area[i][j] += area[i][j-1];
      }
      for (size_t i = 1; i <= r; ++i) for (size_t j = 0; j <= c; ++j) {
        area[i][j] += area[i-1][j];
      }
    }
    std::vector<std::vector<T>> data() const { return area; }
    T at(size_t i, size_t j) const { return area[i][j]; }
  private:
    size_t const r;
    size_t const c;
    std::vector<std::vector<T>> area;
};
