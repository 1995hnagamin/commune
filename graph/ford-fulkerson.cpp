class FordFulkerson {
  public:
    struct edge { int to, cap, rev; };

    explicit FordFulkerson(int v): G(v), used(v) {}
    ~FordFulkerson() = default;

    void add_edge(int from, int to, int cap) {
      G[from].push_back({to, cap, (int)G[to].size()});
      G[to].push_back({from, 0, (int)G[from].size()-1});
    }
    int dfs(int v, int t, int f) {
      if (v == t) return f;
      used[v] = true;

      for (int i = 0; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if (!used[e.to] and e.cap > 0) {
          int d = dfs(e.to, t, std::min(f, e.cap));
          if (d > 0) {
            e.cap -= d;
            G[e.to][e.rev].cap += d;
            return d;
          }
        }
      }
      return 0;
    }
    int max_flow(int s, int t) {
      int flow = 0;

      while (true) {
        std::fill(used.begin(), used.end(), 0);
        int f = dfs(s, t, INF);
        if (f == 0) return flow;
        flow += f;
      }
    }

  private:
    std::vector<std::vector<edge>> G;
    std::vector<bool> used;
};
