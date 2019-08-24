namespace { // Kruskal

template <typename WeightT>
struct kruskal_result_t {
  WeightT cost;
  edges<WeightT> branches;
};

template <typename WeightT>
kruskal_result_t<WeightT>
kruskal_algorithm(adjacency_list<WeightT> const &G) {
  auto es = all_edges(G);
  std::sort(begin(es), end(es));

  WeightT cost = 0;
  edges<WeightT> branches;

  union_find_tree U(G.size());
  for (auto &&e: es) {
    if (!U.same(e.from, e.to)) {
      U.unite(e.from, e.to);
      cost += e.weight;
      branches.push_back(e);
    }
  }
  return { cost, branches };
}

} // namespace
