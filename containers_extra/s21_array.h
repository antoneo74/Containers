#ifndef SRC_CONTAINERS_EXTRA_S21_Array_H_
#define SRC_CONTAINERS_EXTRA_S21_Array_H_

#include <initializer_list>
#include <iterator>

namespace s21 {
template <class T, const size_t N>
class Array {
 public:
  // Array Member type
  using ValueType = T;
  using Reference = T &;
  using ConstReference = const T &;
  using Iterator = T *;
  using ConstIterator = const T *;
  using SizeType = size_t;

  // Array Member functions
  Array() : size_(N) {}
  explicit Array(std::initializer_list<ValueType> const &items);
  Array(const Array &a);
  Array(Array &&a) noexcept;
  ~Array() = default;
  Array &operator=(Array &&a) noexcept;

  // Array Element access
  Reference At(SizeType pos);
  Reference operator[](SizeType pos);
  ConstReference Front() const;
  ConstReference Back() const;
  Iterator Data() noexcept;

  // Array Iterators
  Iterator Begin() noexcept;
  Iterator End() noexcept;
  ConstIterator Cbegin() const noexcept;
  ConstIterator Cend() const noexcept;

  // Array Capacity
  bool Empty() const noexcept;
  SizeType Size() const noexcept;
  SizeType MaxSize() const noexcept;

  // Array Modifiers
  void Swap(Array &other);
  void Fill(ConstReference value);

 private:
  ValueType data_[N];
  SizeType size_;
};

// Array Member functions
template <class T, const size_t N>
Array<T, N>::Array(std::initializer_list<ValueType> const &items) : Array() {
  if (size_ < items.size()) {
    throw std::out_of_range("Invalid amount of items");
  }
  Fill(0);

  SizeType i = 0;
  for (auto it = items.begin(); it != items.end(); ++it, ++i) {
    data_[i] = *it;
  }
}

template <class T, const size_t N>
Array<T, N>::Array(const Array &a) : Array() {
  std::copy(a.Cbegin(), a.Cend(), data_);
}

template <class T, const size_t N>
Array<T, N>::Array(Array &&a) noexcept : Array() {
  Swap(a);
}

template <class T, const size_t N>
Array<T, N> &Array<T, N>::operator=(Array &&a) noexcept {
  Swap(a);
  return *this;
}

// Array Element access
template <class T, const size_t N>
typename Array<T, N>::Reference Array<T, N>::At(SizeType pos) {
  if (pos >= size_) {
    throw std::out_of_range("Position is out of range");
  }
  return data_[pos];
}

template <class T, const size_t N>
typename Array<T, N>::Reference Array<T, N>::operator[](SizeType pos) {
  return data_[pos];
}

template <class T, const size_t N>
typename Array<T, N>::ConstReference Array<T, N>::Front() const {
  return data_[0];
}

template <class T, const size_t N>
typename Array<T, N>::ConstReference Array<T, N>::Back() const {
  return data_[size_ - 1];
}

template <class T, const size_t N>
typename Array<T, N>::Iterator Array<T, N>::Data() noexcept {
  return Begin();
}

// Array Iterators
template <class T, const size_t N>
typename Array<T, N>::Iterator Array<T, N>::Begin() noexcept {
  return Iterator(&data_[0]);
}

template <class T, const size_t N>
typename Array<T, N>::Iterator Array<T, N>::End() noexcept {
  return Iterator(&data_[size_]);
}

template <class T, const size_t N>
typename Array<T, N>::ConstIterator Array<T, N>::Cbegin() const noexcept {
  return ConstIterator(&data_[0]);
}

template <class T, const size_t N>
typename Array<T, N>::ConstIterator Array<T, N>::Cend() const noexcept {
  return ConstIterator(&data_[size_]);
}

// Array Capacity
template <class T, const size_t N>
bool Array<T, N>::Empty() const noexcept {
  return !size_;
}

template <class T, const size_t N>
typename Array<T, N>::SizeType Array<T, N>::Size() const noexcept {
  return size_;
}

template <class T, const size_t N>
typename Array<T, N>::SizeType Array<T, N>::MaxSize() const noexcept {
  return Size();
}

// Array Modifiers
template <class T, const size_t N>
void Array<T, N>::Swap(Array<T, N> &other) {
  for (size_t i = 0; i < N; ++i) {
    std::swap(data_[i], other.data_[i]);
  }
}

template <class T, const size_t N>
void Array<T, N>::Fill(ConstReference value) {
  SizeType i = 0;
  for (auto it = Begin(); it != End(); ++it, ++i) {
    data_[i] = value;
  }
}

}  // namespace s21

#endif  // SRC_CONTAINERS_EXTRA_S21_Array_H_
