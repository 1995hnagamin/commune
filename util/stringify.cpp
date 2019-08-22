namespace { // stringify

__attribute__((unused))
void stringify_helper(std::ostringstream &oss, std::string const &s) {
  oss << '\"' << s << '\"';
}

template<typename T>
__attribute__((unused))
void stringify_helper(std::ostringstream &oss, T const &x) {
  oss << std::to_string(x);
}

template<>
__attribute__((unused))
void stringify_helper(std::ostringstream &oss, std::string const &s) {
  oss << "\"" << s << "\"";
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
