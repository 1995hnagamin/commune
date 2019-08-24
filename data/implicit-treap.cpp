namespace  { // Implicit Treap

template <typename T, typename FnT, typename Serv>
class itreap {
  public:
    struct node_t {
      using ptr_t = std::unique_ptr<node_t>;
      T key; double prio; ptr_t lc, rc; size_t cnt; T sum;
      explicit node_t(T v, double p): key(v), prio(p), lc(), rc(), cnt(1), sum(v) {}
      static size_t count(node_t *t) { return t? t->cnt : 0; }
      static size_t total(node_t *t, T unit) { return t? t->sum : unit; }
      T at(size_t idx) const {
        auto const ls = count(lc.get());
        if (idx == ls) { return key; }
        return (idx < ls)? lc->at(idx) : rc->at(idx - ls - 1);
      }
      void recompute(FnT const &append, T unit) {
        cnt = count(lc.get()) + 1 + count(rc.get());
        auto const lv = total(lc.get(), unit);
        auto const rv = total(rc.get(), unit);
        sum = append(lv, append(key, rv));
      }
      static std::pair<ptr_t, ptr_t> split(ptr_t t, size_t k, FnT const &app, T unit) {
        if (!t) { return std::make_pair(nullptr, nullptr); }
        if (k <= count(t->lc.get())) {
          auto s = split(std::move(t->lc), k, app, unit);
          t->lc = std::move(s.second); t->recompute(app, unit);
          return std::make_pair(std::move(s.first), std::move(t));
        } else {
          auto s = split(std::move(t->rc), k - count(t->lc.get()) - 1, app, unit);
          t->rc = std::move(s.first); t->recompute(app, unit);
          return std::make_pair(std::move(t), std::move(s.second));
        }
      }
      static ptr_t merge(ptr_t l, ptr_t r, FnT const &app, T unit) {
        if (!l || !r) { return std::move(l? l : r); }
        if (l->prio > r->prio) {
          l->rc = merge(std::move(l->rc), std::move(r), app, unit);
          l->recompute(app, unit);
          return l;
        } else {
          r->lc = merge(std::move(l), std::move(r->lc), app, unit);
          r->recompute(app, unit);
          return r;
        }
      }
    };
    using ptr_t = typename node_t::ptr_t;

    explicit itreap(std::shared_ptr<Serv> s, size_t N, T v): srv(s), root() {
      for (size_t i = 0; i < N; ++i) {
        push_back(v);
      }
    }
    explicit itreap(std::shared_ptr<Serv> s, ptr_t &&r): srv(s), root(std::move(r)) {}
    T const operator[] (size_t idx) const {
      return root->at(idx);
    }
    void update(size_t idx, T v) {
      auto right = eliminate(idx+1);
      eliminate(idx);
      push_back(v);
      merge(std::move(right));
    }
    void merge(itreap &&right) {
      root = node_t::merge(std::move(root), std::move(right.root), srv->get_op(), srv->get_unit());
    }
    void push_back(T v) {
      auto const p = srv->generate_priority();
      root = node_t::merge(std::move(root), std::make_unique<node_t>(v, p),
          srv->get_op(), srv->get_unit());
    }
    itreap eliminate(size_t N) {
      auto s = node_t::split(std::move(root), N, srv->get_op(), srv->get_unit());
      root = std::move(s.first);
      return itreap(srv, std::move(s.second));
    }
    void insert(size_t idx, T v) {
      auto const right = eliminate(idx);
      push_back(v);
      merge(std::move(right));
    }
    void erase(size_t idx) {
      auto right = eliminate(idx);
      merge(right.eliminate(1));
    }
    T query(size_t first, size_t last) {
      if (first == last) { return 0; }
      auto right = eliminate(last);
      auto mid = eliminate(first);
      T ans = mid.root->sum;
      merge(std::move(mid));
      merge(std::move(right));
      return ans;
    }
  private:
    std::shared_ptr<Serv> srv;
    ptr_t root;
};

template <typename T, typename FnT>
class itreap_server: public std::enable_shared_from_this<itreap_server<T, FnT>> {
  public:
    using Seq = itreap<T, FnT, itreap_server>;
    static std::shared_ptr<itreap_server> create(FnT fn, T e) {
      return std::make_shared<itreap_server>(fn, e);
    }
    explicit itreap_server(FnT fn, T e):
      mt(std::random_device()()), dis(0, 1), append(fn), unit(e) { }
    Seq make_seq(size_t N, T v) {
      return Seq(this->shared_from_this(), N, v);
    }
    double generate_priority() {
      return dis(mt);
    }
    FnT const &get_op() const { return append; }
    T get_unit() const { return unit; }
  private:
    std::mt19937 mt;
    std::uniform_real_distribution<double> dis;
    FnT append;
    T unit;
};

} // namespace
