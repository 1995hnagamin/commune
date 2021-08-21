template<typename T>
__attribute__((unused))
const auto minimum = static_cast<T const &(*)(T const &, T const &)>(std::min);
