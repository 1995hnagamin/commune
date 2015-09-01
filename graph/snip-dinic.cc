const int VMAX;

struct edge { int to, cap, rev; };

vector<edge> G[VMAX];
bool used[VMAX];

void add_edge(int from, int to, int cap) {
  G[from].push_back((edge){to, cap, G[to].size()});
  G[to].push_back((edge){from, cap, G[from].size() - 1});
}

int dfs(int v, int t, int f) {
  if (v == t) return f;
  used[v] = true;

  for (int i = 0; i < G[v].size(); i++) {
    edge &e = G[v][i];
    if (!used[e.to] and e.cap > 0) {
      int d = dfs(e.to, t, min(f, e.cap));
      if (d > 0) {
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

void bfs(int s) {
  memset(level, -1, sizeof(level));
  queue<int> que;
  level[s] = 0;
  que.push(s);
  while(!que.empty()) {
    int v = que.front; que.pop();
    for (int i = 0; i < G[v].size(); i++~) {
      edge &e = G[v][i];
      if (e.cap > 0 and level[e.to] < 0) {
        level[e.to] = level[v] + 1;
        que.push(e.to);
      }
    }
  }
}

int max_flow(int s, int t) {
  int flow = 0;

  while (true) {
    bfs(s);
    if (lebel[t] < 0) return flow;
    memset(iter, 0, sizeof(iter));
    int f;
    while ((f = dfs(s, t, INF)) > 0) {
      flow += f;
    }
  }
}
