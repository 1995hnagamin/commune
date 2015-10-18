const int PRIMEMAX = 10000;
int FACTOR[PRIMEMAX];
vector<int> Primes;
void sieve() {
  FACTOR[0] = FACTOR[1] = -1;
  REP(n, PRIMEMAX) {
    if (FACTOR[n] != 0) continue;
    Primes.push_back(n);
    int kn = n * n;
    while (kn < PRIMEMAX) { FACTOR[kn] = n; kn += n; }
  }
}

bool is_prime(int n) {
  if (n < PRIMEMAX) return FACTOR[n] == 0;
  for (int p : Primes) {
    if (p * p > n) break;
    if (n % p == 0) return false;
  }
  return true;
}
