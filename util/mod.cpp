namespace  { // Mod

template<int mod>
class Modulo {
  public:
    constexpr Modulo(): num(0) {}
    constexpr Modulo(int n): num(n % mod) {}
    constexpr Modulo(Modulo const &) = default;
    constexpr int data() const { return num; }
    constexpr Modulo &operator+=(Modulo other) {
      num = (num + other.num) % mod;
      return *this;
    }
    constexpr Modulo &operator-=(Modulo other) {
      num = (num + mod - other.num) % mod;
      return *this;
    }
    constexpr Modulo &operator*=(Modulo other) {
      long long n = ((long long)num) * ((long long)other.num);
      num = n % mod;
      return *this;
    }
    constexpr Modulo &operator/=(Modulo other) {
      *this *= other.inverse();
      return *this;
    }
    constexpr static Modulo pow(Modulo a, int n, Modulo res) {
      if (n == 0) { return res; }
      return pow(a*a, n/2, (n&1)?(res*a):res);
    }
    constexpr Modulo inverse() const {
      return pow(*this, mod-2, Modulo(1));
    }
  private:
    int num;
};

template<int mod>
constexpr Modulo<mod> const operator+(Modulo<mod> a, Modulo<mod> b) {
  a += b;
  return a;
}

template<int mod>
constexpr Modulo<mod> const operator-(Modulo<mod> a, Modulo<mod> b) {
  a -= b;
  return a;
}

template<int mod>
constexpr Modulo<mod> const operator*(Modulo<mod> a, Modulo<mod> b) {
  a *= b;
  return a;
}

template<int mod>
constexpr Modulo<mod> const pow(Modulo<mod> a, int n) {
  return Modulo<mod>::pow(a, n, 1);
}

template<int mod>
constexpr Modulo<mod> const operator/(Modulo<mod> a, Modulo<mod> b) {
  a /= b;
  return a;
}

template<int mod, int size>
struct Factorial {
  using Mod = Modulo<mod>;
  Mod fact[size];
  constexpr Factorial(): fact() {
    fact[0] = 1;
    for (int i = 1; i < size; ++i) {
      fact[i] = Mod(i) * fact[i-1];
    }
  }
  Mod const comb(int n, int k) const {
    assert(k <= n && n < size);
    return fact[n] / (fact[k]*fact[n-k]);
  }
};

} // namespace
