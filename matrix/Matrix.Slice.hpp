#ifndef MATRIX_SLICE_HPP
#define MATRIX_SLICE_HPP

namespace IDF::Math {
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
} // namespace IDF::Math
#endif // MATRIX_SLICE_HPP
