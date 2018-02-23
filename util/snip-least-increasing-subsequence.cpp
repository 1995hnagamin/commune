vector<int> lis(const vector<int>& a) {
  const int n = a.size();
  vector<int> A(n, INF);
  vector<int> id(n);
  for (int i = 0; i < n; ++i) {
    id[i] = distance(A.begin(), lower_bound(ALL(as), x));
    A[ id[i] ] = a[i];
  }
  int m = *max_element(id.begin(), id.end());
  vector<int> b(m+1);
  for (int i = n-1; i >= 0; --i)
    if (id[i] == m) b[m--] = a[i];
  return b;
}
