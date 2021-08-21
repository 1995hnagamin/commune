template<typename T>
__attribute__((unused))
const auto maximum = static_cast<T const &(*)(T const &, T const &)>(std::max);
