// Verified AOJ DSL_2_A
#include<vector>
using namespace std;

template<typename T, T(*append)(T,T)>
struct Segtree {
  struct Node {
    int lp, rp; // [l, r)
    T v;
    Node *lc, *rc;
    Node(T v_, int lp_, int rp_) : 
      v(v_), lp(lp_), rp(rp_), lc(), rc() {}
    Node() : lc(), rc() {}
  };
  vector<Node*> roots;
  T empty;
  
  T minv(Node* x, Node* y) {
    if (!x) return (!y)?empty:y->v;
    if (!y) return x->v;
    return append(x->v, y->v);
  }
  
  Node* update(const Node* t, int k, T a) {
    if (t->rp - t->lp <= 1 and t->lp == k) {
      Node* t2 = new Node(a, t->lp, t->rp);
      return t2;
    } 
    Node* t2 = t;
    int mid = (t->lp + t->rp) / 2;
    if (k < mid) {
      if (!(t->lc)) t2->lc = new Node(empty, t->lp, mid);
      t2->lc = update(t->lc, k, a);
    } else {
      if (!(t->rc)) t->rc = new Node(empty, mid, t->rp);
      t2->rc = update(t->rc, k, a);
    }
    t2->v = minv(t2->lc, t2->rc);
    return t2;
  }
  int update(int k, T a) {
    Node* t = update(roots.back(), k, a);
    roots.push_back(t);
    return roots.size() - 1;
  }
  
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
  T query(int idx, int a, int b) { 
    return query(roots[idx], a, b); 
  }

  Segtree(int n_, T empty_) {
    int n = 1;
    empty = empty_;
    while (n < n_) n*=2;
    Node* t2 = new Node(empty, 0, n);
    roots.push_back(t2);
  }
};

template<typename T>
T getmin(T a, T b) { return (a > b ? b : a); }
