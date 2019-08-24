namespace { // stringify

template<typename T>
__attribute__((unused))
void stringify_helper(std::ostringstream &oss, T const &x) {
  oss << std::to_string(x);
}

__attribute__((unused))
void stringify_helper(std::ostringstream &oss, char const *s) {
  oss << "\"" << s << "\"";
}

__attribute__((unused))
void stringify_helper(std::ostringstream &oss, std::string const &s) {
  oss << "\"" << s << "\"";
}

template<typename ...T>
struct stringify_tuple {
  using tuple_t = std::tuple<T...>;
  template <size_t I>
  static int call_for(std::ostringstream &oss, tuple_t const &t) {
    oss << (I > 0? ", ": "") << std::get<I>(t);
    return 0;
  }
  template <size_t ...I>
  static void call(std::ostringstream &oss, tuple_t const &t, std::index_sequence<I...>) {
    oss << "(";
    int arr[] = { 0, call_for<I>(oss, t)... }; (void)arr;
    oss << ")";
  }
};

template<typename ...T>
void stringify_helper(std::ostringstream &oss, std::tuple<T...> const &t) {
  stringify_tuple<T...>::call(oss, t, std::make_index_sequence<sizeof...(T)>{});
}

template<typename T, typename U>
__attribute__((unused))
void stringify_helper(std::ostringstream &oss, std::pair<T, U> const &p) {
  oss << "(";
  stringify_helper(oss, p.first);
  oss << ", ";
  stringify_helper(oss, p.second);
  oss << ")";
}

template<template<typename... Args> class Temp, typename... Args>
__attribute__((unused))
void stringify_helper(std::ostringstream &oss, Temp<Args...> const &v) {
  bool b = false;
  oss << "{";
  for (auto &&x : v) {
    if (b) { oss << ", "; }
    stringify_helper(oss, x);
    b = true;
  }
  oss << "}";
}

template<typename Head, typename... Tail>
__attribute__((unused))
std::string stringify(Head const &head, Tail const &...tail) {
  std::ostringstream oss;
  if (sizeof...(tail) > 0) { oss << "["; }
  stringify_helper(oss, head);
  int const arr[] = { (oss << ", ", stringify_helper(oss, tail), 0)... };
  (void)arr;
  if (sizeof...(tail) > 0) { oss << "]"; }
  return oss.str();
}

} // namespace
