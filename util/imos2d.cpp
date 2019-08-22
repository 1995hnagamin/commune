template <typename T>
class imos_2d {
  public:
    imos_2d(int r, int c): r(r), c(c), area(r+1, std::vector<T>(c+1, 0)) {}
    void add(int bi, int bj, int ei, int ej) {
      bi = std::max(bi, 0); bj = std::max(bj, 0);
      ei = std::min(ei, r); ej = std::min(ej, c);
      ++area[bi][bj];
      --area[bi][ej+1];
      --area[ei+1][bj];
      ++area[ei+1][ej+1];
    }
    void accumulate() {
      for (int i = 0; i <= r; ++i) for (int j = 1; j <= c; ++j) {
        area[i][j] += area[i][j-1];
      }
      for (int i = 1; i <= r; ++i) for (int j = 0; j <= c; ++j) {
        area[i][j] += area[i-1][j];
      }
    }
    std::vector<std::vector<T>> data() const { return area; }
    T at(int i, int j) const { return area[i][j]; }
  private:
    int const r;
    int const c;
    std::vector<std::vector<T>> area;
};
