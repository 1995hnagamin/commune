namespace  { // Mod

template<int mod>
class modulo {
  public:
    constexpr modulo(): num(0) {}
    constexpr modulo(int n): num(n >= 0 ? n%mod : mod-((-n)%mod)) {}
    constexpr modulo(modulo const &) = default;
    constexpr int data() const { return num; }
    constexpr modulo &operator+=(modulo other) {
      num = (num + other.num) % mod;
      return *this;
    }
    constexpr modulo &operator-=(modulo other) {
      num = (num + mod - other.num) % mod;
      return *this;
    }
    constexpr modulo &operator*=(modulo other) {
      long long n = ((long long)num) * ((long long)other.num);
      num = n % mod;
      return *this;
    }
    constexpr modulo &operator/=(modulo other) {
      *this *= other.inverse();
      return *this;
    }
    constexpr static modulo pow(modulo a, int n, modulo res) {
      if (n == 0) { return res; }
      return pow(a*a, n/2, (n&1)?(res*a):res);
    }
    constexpr modulo inverse() const {
      return pow(*this, mod-2, modulo(1));
    }
  private:
    int num;
};

template<int mod>
constexpr modulo<mod> const operator+(modulo<mod> a, modulo<mod> b) {
  a += b;
  return a;
}

template<int mod>
constexpr modulo<mod> const operator-(modulo<mod> a, modulo<mod> b) {
  a -= b;
  return a;
}

template<int mod>
constexpr modulo<mod> const operator*(modulo<mod> a, modulo<mod> b) {
  a *= b;
  return a;
}

template<int mod>
constexpr modulo<mod> const pow(modulo<mod> a, int n) {
  return modulo<mod>::pow(a, n, 1);
}

template<int mod>
constexpr modulo<mod> const operator/(modulo<mod> a, modulo<mod> b) {
  a /= b;
  return a;
}

template<int mod, int size>
struct factorial {
  using Mod = modulo<mod>;
  Mod fact[size];
  Mod invfact[size];
  constexpr factorial(): fact(), invfact() {
    fact[0] = 1;
    for (int i = 1; i < size; ++i) {
      fact[i] = Mod(i) * fact[i-1];
    }
    invfact[size-1] = fact[size-1].inverse();
    for (int i = size - 1; i > 0; --i) {
      invfact[i-1] = invfact[i] * Mod(i);
    }
  }
  Mod const comb(int n, int k) const {
    assert(k <= n && n < size);
    return fact[n] * invfact[k] * invfact[n-k];
  }
};

} // namespace
