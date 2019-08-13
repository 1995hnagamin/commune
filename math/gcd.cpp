namespace { // GCD

template <typename T>
T gcd(T m, T n) {
  return (n == 0) ? m : gcd(n, m % n);
}

}
