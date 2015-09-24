#include<bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for (int i=(a);i<(b);i++)
#define RFOR(i,a,b) for (int i=(b)-1;i>=(a);i--)
#define REP(i,n) for (int i=0;i<(n);i++)
#define RREP(i,n) for (int i=(n)-1;i>=0;i--)
#define ALL(a) (a).begin(),(a).end()
const int INF = INT_MAX/3;
const double EPS = 1e-14;

template<typename U, typename T>
void chmin(U &x, T y) { x = min(x, y); }

template<typename U, typename T>
void chmax(U &x, T y) { x = max(x, y); }

typedef long long int lli;

const int PRIMEMAX = 10000;
int FACTOR[PRIMEMAX];
vector<int> Primes;
void sieve(int upb) {
  REP(n, upb) {
    FACTOR[0] = FACTOR[1] = -1;
    if (FACTOR[n] != 0) continue;
    Primes.push_back(n);
    int kn = n * n;
    while (kn < PRIMEMAX) { FACTOR[kn] = n; kn += n; }
  }
}

bool is_prime(int n) {
  return FACTOR[n] == 0;
}

int main() {
  cout << fixed << setprecision(12);   
  sieve(10000);
  for (int n:Primes) {
    cout << n << ",";
  }
  cout << endl;
  return 0;
}
