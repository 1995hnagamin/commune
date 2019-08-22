namespace { // persistent segment tree

template<typename T, typename FnT>
class persistent_segment_tree {
  public:
    struct Node {
      int lp, rp; // [l, r)
      T v;
      std::shared_ptr<Node> lc, rc;
      Node(T v_, int lp_, int rp_): lp(lp_), rp(rp_), v(v_), lc(), rc() {
      }
      T m_append(FnT const &append, T const &unit) const {
        if (!lc) { return rc? rc->v : unit; }
        if (!rc) { return lc->v; }
        return append(lc->v, rc->v);
      }
      std::shared_ptr<Node>
      update(FnT const &append, T const &unit, int k, T const &a) const {
        if (rp - lp <= 1 && lp == k) {
          auto const t = std::make_shared<Node>(a, lp, rp);
          return t;
        }
        auto t = std::make_shared<Node>(*this);
        int mid = (lp + rp) / 2;
        if (k < mid) {
          auto const ch = lc? lc : std::make_shared<Node>(unit, lp, mid);
          t->lc = ch->update(append, unit, k, a);
        } else {
          auto const ch = rc? rc : std::make_shared<Node>(unit, mid, rp);
          t->rc = ch->update(append, unit, k, a);
        }
        t->v = t->m_append(append, unit);
        return t;
      }
      T query(FnT const &append, T const &unit, int a, int b) const {
        if (b <= lp || rp <= a) { return unit; }
        if (a <= lp && rp <= b) { return v; }
        auto const vl = lc? lc->query(append, unit, a, b) : unit;
        auto const vr = rc? rc->query(append, unit, a, b) : unit;
        return append(vl, vr);
      }
    };

    size_t update(int k, T a) {
     auto const t = roots.back()->update(append, unit, k, a);
      roots.push_back(t);
      return roots.size() - 1;
    }

    // min([a,b))
    T query(int idx, int a, int b) {
      return roots[idx]->query(append, unit, a, b);
    }

    explicit persistent_segment_tree(FnT const &app, T const &un, int n):
      append(app), unit(un), N(1 << log2(n)), roots()
    {
      roots.emplace_back(std::make_shared<Node>(unit, 0, N));
    }

    static size_t log2(size_t n) {
      size_t p = 1;
      while ((1 << p) < n) { ++p; }
      return p;
    }

  private:
    FnT const append;
    T const unit;
    size_t const N;
    std::vector<std::shared_ptr<Node>> roots;
};

template<typename T, typename FnT>
persistent_segment_tree<T, typename std::decay<FnT>::type>
make_persistent_segment_tree(FnT const &app, T const &un, int n) {
  using F = typename std::decay<FnT>::type;
  return persistent_segment_tree<T, F>(app, un, n);
}

} // namespace
