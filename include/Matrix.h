#ifndef IDF_MATRIX_H
#define IDF_MATRIX_H

#include <cstddef>
#include <initializer_list>
#include <vector>

namespace IDF::Math {
/**
 * @brief A multidimensional matrix of T's.
 * @param T Some numeric type.
 *
 * This implementation of a matrix is taken from Chapter 29 of
 * "The C Programming Language" 4th Edition by Bjarne Stroustrup
 * (6th printing, March 2018).
 */
template<typename T, size_t N>
class Matrix {
public:
  static constexpr size_t order = N; // Number of dimensions.
  using value_type              = T;
  using iterator                = typename std::vector<T>::iterator;
  using const_iterator          = typename std::vector<T>::const_iterator;

  Matrix()  = default;
  ~Matrix() = default;

  Matrix(Matrix&&) = default; // move
  Matrix& operator=(Matrix&&) = default;

  Matrix(const Matrix&) = default; // copy
  Matrix& operator=(const Matrix&) = default;

  // Construct & assign from Matrix_ref.
  // template<typename U>
  // Matrix(const Matrix_ref<U, N>&);
  // template<typename U>
  // Matrix& operator=(const Matrix_ref<U, N>&);

  // Specify the extents.
  template<typename... Exts>
  explicit Matrix(Exts... exts);

  // Initialize & assign from list.
  // Matrix(Matrix_initializer<T,N>);
  // Matrix& operator=(Matrix_initializer<T,N>);

  // Only use {} for elements.
  template<typename U>
  Matrix(std::initializer_list<U>) = delete;
  template<typename U>
  Matrix& operator=(std::initializer_list<U>) = delete;

  // Number of elements in Nth dimension.
  // size_t extent(size_t n) const { return desc.extents[n]; }

  // Total number of elements.
  size_t size() const { return elems.size(); }

  // The slice defining subscripting.
  // const Matrix_slice<N>& descriptor() const { return desc; }

  // "Flat" element access;
  T* data() { return elems.data(); }
  const T* data() const { return elems.data(); }

private:
  // Slice defining extents in the N dimensions.
  // Matrix_slice<N> desc;

  // The elements.
  std::vector<T> elems;
};
} // namespace IDF::Math

#endif // IDF_MATRIX_H
