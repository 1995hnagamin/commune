namespace { // GCD

template <typename T>
T gcd(T m, T n) {
  return (n == 0) ? m : gcd(n, m % n);
}

template <typename T>
T extgcd(T a, T b, T &x, T &y) {
  T d = a;
  if (b != 0) {
    d = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
  } else {
    x = 1, y = 0;
  }
  return d;
}

}
