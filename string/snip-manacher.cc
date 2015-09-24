vector<int> manacher(string &S) {
  int i = 0, j = 0, len = S.size();
  vector<int> R(len, 0);
  while (i < len) {
    while (i-j >= 0 and i+j < len and S[i-j] == S[i+j]) ++j;
    R[i] = j;
    int k = 1;
    while (i-k >= 0 and i+k < len and k+R[i-k] < j) {
      R[i+k] = R[i-k];
      ++k;
    }
    i+=k; j-=k;
  }
  return R;
}

int main() {
  string s;
  while (cin >> s) {
    for (int x : manacher(s)) {
      cout << x;
    }
    cout << endl;
  }
}
