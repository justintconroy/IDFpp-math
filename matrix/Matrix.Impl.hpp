#ifndef MATRIX_IMPL_HPP
#define MATRIX_IMPL_HPP

namespace IDF::Math::Matrix_impl {

template<typename... Args>
inline constexpr bool Requesting_element() {
  return All(Convertible<Args, size_t>()...);
}

template<typename... Args>
inline constexpr bool Requesting_slice() {
  return All(Convertible<Args, size_t>()...);
}
} // namespace IDF::Math::Matrix_impl

#endif // MATRIX_IMPL_HPP
