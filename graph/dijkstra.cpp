namespace { // Dijkstra's algorithm

template<typename WeightT>
struct DijkstraResult {
  std::vector<WeightT> distance;
};

template<typename WeightT>
DijkstraResult<WeightT>
dijkstra_algorithm(AdjacencyList<WeightT> const &g, int start, WeightT inf) {
  int const N = g.size();
  std::vector<WeightT> dist(N, inf);
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
    for (auto &&e : g[u]) {
      que.emplace(dist2u + e.weight, e.to);
    }
  }
  return {
    dist
  };
}

} // namespace
