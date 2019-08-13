namespace { // Sunzi

template <uint32_t... m>
class Sunzi {
  public:
    constexpr static size_t L = sizeof...(m);
    using I = uint_fast32_t;

    constexpr Sunzi(): dat() { dat.fill(0); }
    constexpr Sunzi(int n): dat({ (n >= 0 ? n%m : m-((-n)%m))... }) { }
    constexpr Sunzi(Sunzi const &other) = default;
    constexpr std::array<I, L> data() const { return dat; }
    constexpr Sunzi &operator+=(Sunzi const &other) {
      constexpr std::array<I,L> mod = { m... };
      for (size_t i = 0; i < L; ++i) {
        dat[i] = (dat[i] + other.dat[i]) % mod[i];
      }
      return *this;
    }
    constexpr Sunzi &operator-=(Sunzi const &other) {
      constexpr std::array<I,L> mod = { m... };
      for (size_t i = 0; i < L; ++i) {
        dat[i] = (dat[i] + mod[i] - other.dat[i]) % mod[i];
      }
      return *this;
    }
    constexpr Sunzi &operator*=(Sunzi const &other) {
      constexpr std::array<I,L> mod = { m... };
      for (size_t i = 0; i < L; ++i) {
        uint_fast64_t n = ((uint_fast64_t)dat[i]) * ((uint_fast64_t)other.dat[i]);
        dat[i] = n % mod[i];
      }
      return *this;
    }

  private:
    std::array<I, L> dat;
};

template<uint32_t... m>
constexpr bool operator==(Sunzi<m...> const &a, Sunzi<m...> const &b) {
  return a.data() == b.data();
}

template<uint32_t... m>
constexpr Sunzi<m...> const operator+(Sunzi<m...> const &a, Sunzi<m...> const &b) {
  auto num = a;
  num += b;
  return num;
}

template<uint32_t... m>
constexpr Sunzi<m...> const operator-(Sunzi<m...> const &a, Sunzi<m...> const &b) {
  auto num = a;
  num -= b;
  return num;
}

template<uint32_t... m>
constexpr Sunzi<m...> const operator*(Sunzi<m...> const &a, Sunzi<m...> const &b) {
  auto num = a;
  num *= b;
  return num;
}

} // namespace
