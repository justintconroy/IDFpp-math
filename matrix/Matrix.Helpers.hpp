#ifndef MATRIX_HELPERS_H
#define MATRIX_HELPERS_H

#include <array>
#include <cstddef>
#include <initializer_list>
#include <type_traits>

namespace IDF::Math {

template<typename T>
inline constexpr bool Is_class() {
  return std::is_class<T>::value;
}

template<typename X, typename Y>
inline constexpr bool Convertible() {
  return std::is_convertible<X, Y>::value;
}

template<typename X, typename Y>
inline constexpr bool Common_type() {
  return std::common_type<X, Y>::value;
}

template<typename T, size_t N>
using Value_type = typename Matrix<T, N>::value_type;

// template<Typename T>

template<bool B, typename T = void>
using Enable_if = typename std::enable_if<B, T>::type;

} // namespace IDF::Math
#endif // MATRIX_HELPERS_H
