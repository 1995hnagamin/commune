template<typename T, typename FnT, typename IndexT = int>
class ThriftySegmentTree {
  public:
    struct Node {
      T v;
      IndexT lp, rp; // [l, r)
      std::unique_ptr<Node> lc, rc;
      Node(T v_, IndexT lp_, IndexT rp_):
        v(v_), lp(lp_), rp(rp_), lc(), rc() {}
      void update(FnT const &append, T const &unit, IndexT k, T x) {
        if (rp <= lp + 1 && lp == k) {
          v = x;
          return;
        }
        const auto mid = (lp + rp) / 2;
        if (k < mid) {
          if (!lc) lc = std::make_unique<Node>(unit, lp, mid);
          lc->update(append, unit, k, x);
        } else {
          if (!rc) rc = std::make_unique<Node>(unit, mid, rp);
          rc->update(append, unit, k, x);
        }
        v = m_append(append, unit);
      }
      T m_append(FnT const &append, T const &unit) const {
        if (!lc) { return rc? rc->v : unit; }
        if (!rc) { return lc->v; }
        return append(lc->v, rc->v);
      }
      T query(FnT const &append, T const &unit, IndexT a, IndexT b) const {
        if (b <= lp || rp <= a) { return unit; }
        if (a <= lp && rp <= b) { return v; }
        const auto vl = lc? lc->query(append, unit, a, b) : unit;
        const auto vr = rc? rc->query(append, unit, a, b) : unit;
        return append(vl, vr);
      }
      T at(T const &unit, IndexT k) const {
        const auto mid = (lp + rp) / 2;
        if (k < mid) {
          return lc? lc->at(unit, k) : unit;
        } else {
          return rc? rc->at(unit, k) : unit;
        }
      }
    };
    explicit ThriftySegmentTree(FnT const &app, T const &un, IndexT n):
      append(app), unit(un), N(1 << log2(n)),
      root(std::make_unique<Node>(un, 0, N)) {
    }
    ~ThriftySegmentTree() = default;
    void update(IndexT k, T x) {
      root->update(append, unit, k, x);
    }
    T at(IndexT k) const {
      return root->at(unit, k);
    }
    T query(IndexT a, IndexT b) const {
      return root->query(append, unit, a, b);
    }
    T query() const {
      return query(0, N);
    }
  private:
    FnT const append;
    T const unit;
    size_t const N;
    std::unique_ptr<Node> root;

    static size_t log2(size_t n) {
      size_t p = 1;
      while ((1 << p) < n) { ++p; }
      return p;
    }
};
