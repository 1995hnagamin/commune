template<typename T>
T power(typename std::common_type<T>::type a, int n) {
  T ans = 1;
  while (n > 0) {
    if (n & 1) {
      ans *= a;
    }
    a = a * a;
    n >>= 1;
  }
  return ans;
}
