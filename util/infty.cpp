template<typename T>
__attribute__((unused))
T constexpr infty = std::numeric_limits<T>::max / 3;
template<>
__attribute__((unused))
auto constexpr infty<int> = 1'100'100'100;
template<>
__attribute__((unused))
auto constexpr infty<long long int> = 100'500'400'300'200'100LL;
