namespace { // persistent segment tree

template<typename T, typename FnT, typename IndexT = int>
class persistent_segment_tree {
  public:
    struct node {
      IndexT lp, rp; // [l, r)
      T v;
      std::shared_ptr<node> lc, rc;
      node(T v_, IndexT lp_, IndexT rp_): lp(lp_), rp(rp_), v(v_), lc(), rc() {
      }
      T m_append(FnT const &append, T const &unit) const {
        if (!lc) { return rc? rc->v : unit; }
        if (!rc) { return lc->v; }
        return append(lc->v, rc->v);
      }
      std::shared_ptr<node>
      update(FnT const &append, T const &unit, IndexT k, T const &a) const {
        if (rp - lp <= 1 && lp == k) {
          auto const t = std::make_shared<node>(a, lp, rp);
          return t;
        }
        auto t = std::make_shared<node>(*this);
        IndexT mid = (lp + rp) / 2;
        if (k < mid) {
          auto const ch = lc? lc : std::make_shared<node>(unit, lp, mid);
          t->lc = ch->update(append, unit, k, a);
        } else {
          auto const ch = rc? rc : std::make_shared<node>(unit, mid, rp);
          t->rc = ch->update(append, unit, k, a);
        }
        t->v = t->m_append(append, unit);
        return t;
      }
      T query(FnT const &append, T const &unit, IndexT a, IndexT b) const {
        if (b <= lp || rp <= a) { return unit; }
        if (a <= lp && rp <= b) { return v; }
        auto const vl = lc? lc->query(append, unit, a, b) : unit;
        auto const vr = rc? rc->query(append, unit, a, b) : unit;
        return append(vl, vr);
      }
    };

    size_t update(IndexT k, T a) {
     auto const t = roots.back()->update(append, unit, k, a);
      roots.push_back(t);
      return roots.size() - 1;
    }

    // min([a,b))
    T query(size_t revision, IndexT a, IndexT b) {
      return roots[revision]->query(append, unit, a, b);
    }

    explicit persistent_segment_tree(FnT const &app, T const &un, IndexT n):
      append(app), unit(un), N(p2cl2(n)), roots()
    {
      roots.emplace_back(std::make_shared<node>(unit, 0, N));
    }

  private:
    FnT const append;
    T const unit;
    IndexT const N;
    std::vector<std::shared_ptr<node>> roots;

    static IndexT p2cl2(IndexT n) {
      IndexT N = 1;
      while (N < n) { N *= 2; }
      return N;
    }
};

template<typename T, typename FnT, typename IndexT = int>
persistent_segment_tree<T, typename std::decay<FnT>::type>
make_persistent_segment_tree(FnT const &app, T const &un, IndexT n) {
  using F = typename std::decay<FnT>::type;
  return persistent_segment_tree<T, F, IndexT>(app, un, n);
}

} // namespace
