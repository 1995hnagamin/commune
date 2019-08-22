class union_find_tree {
  public:
    explicit union_find_tree(size_t n): par(n), rank(n, 0) {
      for (size_t i = 0; i < n; ++i) { par[i] = i; }
    }

    size_t find(size_t i) {
      if (par[i] == i) {
        return i;
      } else {
        return par[i] = find(par[i]);
      }
    }

    void unite(size_t i, size_t j) {
      i = find(i), j = find(j);
      if (i == j) { return; }

      if (rank[i] < rank[j]) {
        par[i] = j;
      } else {
        par[j] = i;
        if (rank[i] = rank[j]) { rank[i]++; }
      }
    }

    bool same(size_t i, size_t j) {
      return find(i) == find(j);
    }
  private:
    std::vector<size_t> par;
    std::vector<size_t> rank;
};
