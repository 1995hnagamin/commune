namespace { // Graph Basics

template<typename WeightT>
struct Edge {
  int from, to;
  WeightT weight;
  Edge(int s, int d, WeightT w): from(s), to(d), weight(w) {}
};

template<typename WeightT>
bool
operator< (Edge<WeightT> const &lhs, Edge<WeightT> const &rhs) {
  if (lhs.weight != rhs.weight) {
    return lhs.weight < rhs.weight;
  } else if (lhs.from != rhs.from) {
    return lhs.from < rhs.from;
  }
  return lhs.to < rhs.to;
}

template<typename WeightT>
using Edges = std::vector<Edge<WeightT> >;

template<typename WeightT>
using AdjacencyList = std::vector<Edges<WeightT> >;

template<typename WeightT>
void
add_undir_edge(AdjacencyList<WeightT> &graph, int u, int v, WeightT w) {
  graph[u].emplace_back(u, v, w);
  graph[v].emplace_back(v, u, w);
}

template<typename WeightT>
AdjacencyList<WeightT>
inverse_graph(AdjacencyList<WeightT> const &G) {
  size_t const n = G.size();
  AdjacencyList<WeightT> F(n);
  for (size_t i = 0; i < n; ++i) {
    for (auto &&e: G[i]) {
      F[e.to].emplace_back(e.to, e.from, e.weight);
    }
  }
  return F;
}

} // namespace
