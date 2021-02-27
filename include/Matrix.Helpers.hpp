#ifndef MATRIX_HELPERS_H
#define MATRIX_HELPERS_H

#include <array>
#include <cstddef>
#include <initializer_list>
#include <type_traits>

namespace IDF::Math {

template<typename T>
constexpr bool Is_class() {
  return std::is_class<T>::value;
}

template<typename X, typename Y>
constexpr bool Convertible() {
  return std::is_convertible<X, Y>::value;
}

template<bool B, typename T = void>
using Enable_if = typename std::enable_if<B, T>::type;

namespace Matrix_impl {
template<typename... Args>
inline constexpr bool Requesting_element() {
  return All(Convertible<Args, size_t>()...);
}
} // namespace Matrix_impl

template<size_t N>
struct Matrix_slice {
  Matrix_slice() = default; // An empty matrix: no elements.

  Matrix_slice(size_t offset,
               std::initializer_list<size_t> exts); // Starting offset and
                                                    // extents.
  Matrix_slice(size_t offset,
               std::initializer_list<size_t> exts,
               std::initializer_list<size_t> strs); // and strides.

  // N extents.
  template<typename... Dims>
  Matrix_slice(Dims... dims);

  // Calculate index from a set of subscripts.
  // template<typename... Dims,
  //          typename = Enable_if<All(Convertible<Dims, size_t>()...)>>
  // size_t operator()(Dims... dims) const;

  size_t size;                   // Total number of elements.
  size_t start;                  // Starting offset.
  std::array<size_t, N> extents; // Number of elements in each dimension.
  std::array<size_t, N> strides; // offsets between elements in each dimension.
};

template<typename T, size_t N>
class Matrix_initializer {};

template<typename U, size_t N>
class Matrix_ref;

} // namespace IDF::Math
#endif // MATRIX_HELPERS_H
