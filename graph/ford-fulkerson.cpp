template <typename T>
class ford_fulkerson {
  public:
    struct edge {
      explicit edge(size_t t, T c, size_t r) : to(t), cap(c), rev(r) {}
      size_t to; T cap; size_t rev;
    };

    explicit ford_fulkerson(size_t v): G(v), used(v) {}
    ~ford_fulkerson() = default;

    void add_edge(size_t from, size_t to, T cap) {
      G[from].emplace_back(to, cap, G[to].size());
      G[to].emplace_back(from, 0, G[from].size() - 1);
    }
    T dfs(size_t v, size_t t, T f) {
      if (v == t) return f;
      used[v] = true;
      for (auto &&e : G[v]) {
        if (used[e.to] || e.cap <= 0) continue;
        T d = dfs(e.to, t, std::min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          reverse(e).cap += d;
          return d;
        }
      }
      return 0;
    }
    T max_flow(size_t s, size_t t) {
      T flow = 0;
      while (true) {
        std::fill(used.begin(), used.end(), 0);
        T f = dfs(s, t, infty<T>);
        if (f == 0) return flow;
        flow += f;
      }
    }

  private:
    std::vector<std::vector<edge>> G;
    std::vector<bool> used;
    edge &reverse(edge const &e) {
      return G[e.to][e.rev];
    }
};
