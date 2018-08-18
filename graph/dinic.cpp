class Dinic {
  public:
    struct edge {
      explicit edge(size_t t, int c, size_t r):
        to(t), cap(c), rev(r) {}
      size_t to; int cap; size_t rev;
    };

    explicit Dinic(size_t v): G(v), level(v) {}
    ~Dinic() = default;

    void add_edge(size_t from, size_t to, int cap) {
      G[from].emplace_back(to, cap, G[to].size());
      G[to].emplace_back(from, 0, G[from].size() - 1);
    }
    void bfs(size_t s) {
      std::fill(level.begin(), level.end(), -1);
      std::queue<size_t> que;
      level[s] = 0;
      que.push(s);
      while (!que.empty()) {
        const auto v = que.front();
        que.pop();
        for (auto &&e : G[v]) {
          if (e.cap <= 0 || level[e.to] >= 0) continue;
          level[e.to] = level[v] + 1;
          que.push(e.to);
        }
      }
    }
    int dfs(size_t v, size_t t, int f) {
      if (v == t) return f;
      for (auto &&e : G[v]) {
        if (e.cap <= 0 || level[v] >= level[e.to]) continue;
        int d = dfs(e.to, t, std::min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          reverse(e).cap += d;
          return d;
        }
      }
      return 0;
    }
    int max_flow(size_t s, size_t t) {
      int flow = 0;
      while (true) {
        bfs(s);
        if (level[t] < 0) return flow;
        int f;
        while ((f = dfs(s, t, INF)) > 0) {
          flow += f;
        }
      }
    }
  private:
    std::vector<std::vector<edge>> G;
    std::vector<int> level;
    edge &reverse(edge const &e) {
      return G[e.to][e.rev];
    }
};
