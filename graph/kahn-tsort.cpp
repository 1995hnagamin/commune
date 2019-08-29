template<typename WeightT>
std::vector<size_t> kahn_tsort(adjacency_list<WeightT> const &G) {
  std::vector<size_t> ideg(G.size(), 0);
  for (size_t u = 0; u < G.size(); ++u) for (auto &&e : G[u]) { ++ideg[e.to]; }

  std::stack<size_t> stk;
  for (size_t u = 0; u < G.size(); ++u) {
    if (ideg[u] == 0) { stk.push(u); }
  }

  std::vector<size_t> vec;
  while (!stk.empty()) {
    size_t r = stk.top(); stk.pop(); vec.push_back(r);
    for (auto &&e : G[r]) {
      --ideg[e.to];
      if (ideg[e.to] == 0) { stk.push(e.to); }
    }
  }
  return vec;
}
