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

template<typename T, size_t N>
Matrix_ref<T, N - 1> Matrix<T, N>::operator[](size_t n) {
  return row(n);
}

template<typename T, size_t N>
template<typename F>
Matrix<T, N>& Matrix<T, N>::apply(F f) {
  for (auto& x : elems) f(x);
  return *this;
}

template<typename T, size_t N>
template<typename M, typename F>
Enable_if<Matrix_type<M>(), Matrix<T, N>&> Matrix<T, N>::apply(const M& m,
                                                               F f) {
  assert(same_extents(desc, m.descriptor()));

  for (auto i = begin(), j = m.begin(); i != end(); ++i, ++j) {
    f(*i, *j);
  }
  return *this;
}

template<typename T, size_t N>
Matrix<T, N>& Matrix<T, N>::operator+=(const T& value) {
  return apply([&](T& a) { a += value; });
}
template<typename T, size_t N>
Matrix<T, N>& operator+(const Matrix<T, N> T& m, const T& value) {
  Matrix<T, N> res = m;
  res += m;
  return res;
}

template<typename T, size_t N>
Matrix<T, N>& Matrix<T, N>::operator-=(const T& value) {
  return apply([&](T& a) { a -= value; });
}
template<typename T, size_t N>
Matrix<T, N>& operator-(const Matrix<T, N> T& m, const T& value) {
  Matrix<T, N> res = m;
  res -= m;
  return res;
}

template<typename T, size_t N>
Matrix<T, N>& Matrix<T, N>::operator*=(const T& value) {
  return apply([&](T& a) { a *= value; });
}
template<typename T, size_t N>
Matrix<T, N>& operator*(const Matrix<T, N> T& m, const T& value) {
  Matrix<T, N> res = m;
  res *= m;
  return res;
}

template<typename T, size_t N>
Matrix<T, N>& Matrix<T, N>::operator/=(const T& value) {
  return apply([&](T& a) { a /= value; });
}
template<typename T, size_t N>
Matrix<T, N>& operator/(const Matrix<T, N> T& m, const T& value) {
  Matrix<T, N> res = m;
  res /= m;
  return res;
}

template<typename T, size_t N>
Matrix<T, N>& Matrix<T, N>::operator%=(const T& value) {
  return apply([&](T& a) { a %= value; });
}
template<typename T, size_t N>
Matrix<T, N>& operator%(const Matrix<T, N> T& m, const T& value) {
  Matrix<T, N> res = m;
  res %= m;
  return res;
}

template<typename T, size_t N>
template<typename M>
Enable_if<Matrix_type<M>(), Matrix<T, N>&> Matrix<T, N>::operator+=(
  const M& m) {
  static_assert(m.order == N, "+=: mismatched Matrix dimensions");
  assert(same_extents(desc, m.descriptor()));

  return apply(m, [](T& a, const Value_type<M>& b) { a += b; });
}

template<typename T,
         typename T2,
         size_t N,
         typename RT = Matrix<Common_type<Value_type<T>, Value_type<T2>>, N>>
  > Matrix<RT, N> operator+(const Matrix<T, N>& a, const Matrix<T2, N>& b);
Matrix<RT, N> res = a;
res += b;
return res;
}
