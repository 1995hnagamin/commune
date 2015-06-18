// Verified AOJ DSL_2_A
#include<vector>
#include<iostream>
using namespace std;

template<typename T, T(*append)(T,T), T empty>
struct Segtree {
  struct Node {
    int lp, rp; // [l, r)
    T v;
    Node *lc, *rc;
    Node(T v_, int lp_, int rp_) : v(v_), lp(lp_), rp(rp_) {}
  };
  Node* root;
  
  T minv(Node* x, Node* y) {
    if (!x) return (!y)?empty:y->v;
    if (!y) return x->v;
    return append(x->v, y->v);
  }
  
  void update(Node* t, int k, T a) {
    if (t->rp - t->lp == 1 and t->lp == k) {
      t->v = a;
      return;
    } 
    int mid = (t->lp + t->rp) / 2;
    if (k < mid) {
      if (!(t->lc)) t->lc = new Node(empty, t->lp, mid);
      update(t->lc, k, a);
    } else {
      if (!(t->rc)) t->rc = new Node(empty, mid, t->rp);
      update(t->rc, k, a);
    }
    t->v = minv(t->lc, t->rc);
    return;
  }
  void update(int k, T a) { update(root, k, a); }
  
  // min([a,b))
  T query(Node* t, int a, int b) {
    if (!t) return empty;
    if (t->rp <= a || b <= t->lp) return empty;
    else if (a <= t->lp && t->rp <= b) return t->v;
    else {
      T vl = query(t->lc, a, b), vr = query(t->rc, a, b);
      return append(vl, vr);
    }
  }
  int query(int a, int b) { return query(root, a, b); }

  Segtree(int n_) {
    int n = 1;
    while (n < n_) n*=2;
    root = new Node(empty, 0, n);
  }
};

int getmin(int a, int b) {
  return (a > b ? b : a);
}

int main() {
  int n, q;
  cin >> n >> q;
  Segtree<int,getmin,2147483647> t(n);
  for (int i = 0; i < q; ++i) {
    int com, x, y;
    cin >> com >> x >> y;
    if (com == 1) {
      cout << t.query(x, y+1) << endl;
    } else {
      t.update(x, y);
    }
  }
}
