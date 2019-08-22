namespace { // Dijkstra's algorithm

template<typename WeightT>
struct dijkstra_result_t {
  std::vector<WeightT> distance;
};

template<typename WeightT>
dijkstra_result_t<WeightT>
dijkstra_algorithm(adjacency_list<WeightT> const &G, int start, WeightT inf) {
  std::vector<WeightT> dist(G.size(), inf);
  using P = std::tuple<WeightT, int>;
  std::priority_queue<P, std::vector<P>, std::greater<P> > que;
  que.emplace(0, start);
  while (!que.empty()) {
    WeightT dist2u; int u; std::tie(dist2u, u) = que.top();
    que.pop();
    if (dist2u >= dist[u]) {
      continue;
    }
    dist[u] = dist2u;
    for (auto &&e : G[u]) {
      que.emplace(dist2u + e.weight, e.to);
    }
  }
  return {
    dist
  };
}

} // namespace
