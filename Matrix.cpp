#include "Matrix.h"

using namespace IDF::Math;
using namespace std;

template<typename T, size_t N>
template<typename... Exts>
Matrix<T, N>::Matrix(Exts... exts)
  :                  // desc{exts...},   // Copy extents.
    elems(desc.size) // Allocate desc.size elements and default init them.
{}

template<typename T, size_t N>
Matrix<T, N>::Matrix(Matrix_initializer<T, N> init) {
  // Deduce extents from initializer list.
  // desc.extents = Matrix_impl::derive_extents(init);

  // Compute strides and size.
  // Matrix_impl::compute_strides(desc);

  // Make room for slices
  // elems.reserve(desc.size);

  // Initialize from initializer list.
  // Matrix_impl::insert_flat(init, elems);
  // assert(elems.size() == desc.size);
}

template<typename T, size_t N>
template<typename U>
Matrix<T, N>::Matrix(const Matrix_ref<U, N>& x)
  : desc{x.desc}, elems{x.begin(), x.end()} {
  // static_assert(Convertible<U, T>(),
  //               "Matrix constructor: incompatible element types");
}

template<typename T, size_t N>
template<typename U>
Matrix<T, N>& Matrix<T, N>::operator=(const Matrix_ref<U, N>& x) {
  // static_assert(Convertible<U, T>(),
  //               "Matrix =: incompatible element types");

  desc = x.desc;
  elems.assign(x.begin(), x.end());
  return *this;
}
