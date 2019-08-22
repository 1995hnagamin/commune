namespace { // Strongnly Connected Components

struct scc_result_t {
  std::vector<int> top_index;
  std::vector<std::vector<int> > components;
};


template<typename T>
scc_result_t
kosaraju_scc(adjacency_list<T> const &G) {
  int const N = G.size();

  // 1st DFS
  std::vector<bool> used(N, false);
  std::stack<int> order1;
  for (int s = 0; s < N; ++s) {
    if (used[s]) { continue; }
    std::stack<int> nodes;
    std::stack<bool> flags; // 0:visit, 1:index
    nodes.push(s); flags.push(0);
    while (!nodes.empty()) {
      auto const u = nodes.top(); nodes.pop();
      auto const is_visited = flags.top(); flags.pop();
      if (is_visited) {
        order1.push(u);
        continue;
      }
      if (used[u]) { continue; }
      used[u] = true;
      nodes.push(u); flags.push(1);
      for (auto &&e: G[u]) {
        nodes.push(e.to); flags.push(0);
      }
    }
  }

  // 2nd DFS
  auto const rG = inverse_graph(G);
  std::fill(begin(used), end(used), false);
  std::vector<int> order(N);
  std::vector<std::vector<int>> components;
  int top_index = 0;
  while (!order1.empty()) {
    auto const s = order1.top(); order1.pop();
    if (used[s]) { continue; }
    std::vector<int> scc;
    std::stack<int> stk; stk.push(s);
    while (!stk.empty()) {
      auto const u = stk.top(); stk.pop();
      if (used[u]) { continue; }
      used[u] = true;
      order[u] = top_index;
      scc.push_back(u);
      for (auto &&e: rG[u]) {
        stk.push(e.to);
      }
    }
    ++top_index;
    components.push_back(std::move(scc));
  }
  return { order, components };
}

} // namespace
