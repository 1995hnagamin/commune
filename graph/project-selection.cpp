template <typename T, template <class> class Solver>
class project_selection {
  public:
    explicit project_selection(size_t n): solver(n+2), offset(0), red(n), blue(n+1) {}
    ~project_selection() = default;

    void add_red_benefit(size_t i, T benefit) {
      if (benefit > 0) {
        offset += benefit;
        solver.add_edge(red, i, benefit);
      } else {
        solver.add_edge(i, blue, -benefit);
      }
    }
    void add_red_penalty(size_t i, T penalty) {
      add_red_benefit(i, -penalty);
    }
    void add_split_penalty(size_t r, size_t b, T penalty) {
      solver.add_edge(r, b, penalty);
    }
    T max_benefit() {
      return offset - solver.max_flow(red, blue);
    }
  private:
    Solver<T> solver;
    T offset;
    size_t const red; size_t const blue;
};
