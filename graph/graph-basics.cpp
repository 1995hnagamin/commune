namespace { // Graph Basics

template<typename WeightT>
struct edge {
  int from, to;
  WeightT weight;
  edge(int s, int d, WeightT w): from(s), to(d), weight(w) {}
};

template<typename WeightT>
bool
operator< (edge<WeightT> const &lhs, edge<WeightT> const &rhs) {
  if (lhs.weight != rhs.weight) {
    return lhs.weight < rhs.weight;
  } else if (lhs.from != rhs.from) {
    return lhs.from < rhs.from;
  }
  return lhs.to < rhs.to;
}

template<typename WeightT>
using edges = std::vector<edge<WeightT> >;

template<typename WeightT>
using adjacency_list = std::vector<edges<WeightT> >;

template<typename WeightT>
void
add_undir_edge(adjacency_list<WeightT> &G, int u, int v, WeightT w) {
  G[u].emplace_back(u, v, w);
  G[v].emplace_back(v, u, w);
}

template<typename WeightT>
adjacency_list<WeightT>
inverse_graph(adjacency_list<WeightT> const &G) {
  size_t const n = G.size();
  adjacency_list<WeightT> F(n);
  for (auto &&es: G) for (auto &&e: es) {
    F[e.to].emplace_back(e.to, e.from, e.weight);
  }
  return F;
}

} // namespace
