#ifndef SRC_CONTAINERS_S21_VECTOR_H_
#define SRC_CONTAINERS_S21_VECTOR_H_

#include <initializer_list>
#include <iterator>
#include <limits>

namespace s21 {
template <class T>
class Vector {
 public:
  // Vector Member type
  using ValueType = T;
  using Pointer = T*;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;

  // internal class VectorIterator
  class VectorIterator {
    friend class Vector;

   public:
    VectorIterator() = default;

    VectorIterator(const VectorIterator& it) : current_(it.current_) {}

    VectorIterator(const Pointer v) : current_(v) {}

    VectorIterator& operator=(const VectorIterator& it) noexcept {
      current_ = it.current_;
      return *this;
    }

    VectorIterator& operator--() noexcept {
      --current_;
      return *this;
    }

    VectorIterator& operator++() noexcept {
      ++current_;
      return *this;
    }

    VectorIterator& operator+(SizeType n) noexcept {
      while (n--) {
        ++current_;
      }
      return *this;
    }

    bool operator!=(const VectorIterator& other) const noexcept {
      return (current_ != other.current_);
    }

    Reference operator*() noexcept { return *current_; }

   private:
    Pointer current_ = nullptr;
  };

  // internal class VectorConstIterator
  class VectorConstIterator {
    friend class Vector;

   public:
    VectorConstIterator() = default;

    VectorConstIterator(const VectorConstIterator& it)
        : current_(it.current_) {}

    VectorConstIterator(const Pointer v) : current_(v) {}

    VectorConstIterator& operator=(const VectorConstIterator& it) noexcept {
      current_ = it.current_;
      return *this;
    }

    VectorConstIterator& operator--() noexcept {
      --current_;
      return *this;
    }

    VectorConstIterator& operator++() noexcept {
      ++current_;
      return *this;
    }

    VectorConstIterator& operator+(SizeType n) noexcept {
      while (n--) {
        ++current_;
      }
      return *this;
    }

    bool operator!=(const VectorConstIterator& other) const noexcept {
      return (current_ != other.current_);
    }

    Reference operator*() noexcept { return *current_; }

   private:
    Pointer current_ = nullptr;
  };

  using Iterator = VectorIterator;
  using ConstIterator = VectorConstIterator;

  // Vector Member functions
  Vector() = default;
  explicit Vector(SizeType n);
  Vector(std::initializer_list<ValueType> const& items);
  Vector(const Vector& v);
  Vector(Vector&& v) noexcept;
  ~Vector();
  Vector<T>& operator=(Vector&& v) noexcept;

  // Vector Element access
  Reference At(SizeType pos);
  Reference operator[](SizeType pos);
  ConstReference Front() const;
  ConstReference Back() const;
  T* Data();

  // Vector Iterators
  Iterator Begin();
  Iterator End();
  ConstIterator Cbegin() const;
  ConstIterator Cend() const;

  // Vector Capacity
  bool Empty() const;
  SizeType Size() const;
  SizeType MaxSize();
  void Reserve(SizeType size);
  SizeType Capacity();
  void ShrinkToFit();

  // Vector Modifiers
  void Clear();
  Iterator Insert(Iterator pos, ConstReference value);
  void Erase(Iterator pos);
  void PushBack(ConstReference value);
  void PopBack();
  void Swap(Vector& other);

  // Bonus functions
  template <typename... Args>
  Iterator Emplace(ConstIterator pos, Args&&... args);
  template <typename... Args>
  void EmplaceBack(Args&&... args);

 private:
  SizeType size_ = 0;
  SizeType capacity_ = 0;
  Pointer vector_ = nullptr;

  // Support functions
  void ReSize();
  void MoveData();
};

// Vector Member functions
template <class T>
Vector<T>::Vector(SizeType n) : size_(n), capacity_(n) {
  vector_ = capacity_ ? new ValueType[capacity_] : nullptr;
}

template <class T>
Vector<T>::Vector(std::initializer_list<ValueType> const& items) {
  size_ = items.size();
  capacity_ = items.size();
  vector_ = new ValueType[capacity_];
  std::copy(items.begin(), items.end(), vector_);
}

template <class T>
Vector<T>::Vector(const Vector& v) {
  size_ = v.size_;
  capacity_ = v.capacity_;
  if (capacity_) vector_ = new ValueType[capacity_];
  std::copy(v.vector_, v.vector_ + v.size_, vector_);
}

template <class T>
Vector<T>::Vector(Vector&& v) noexcept {
  Swap(v);
}

template <class T>
Vector<T>::~Vector() {
  Clear();
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector&& v) noexcept {
  Clear();
  Swap(v);
  return *this;
}

// Vector Element access
template <class T>
typename Vector<T>::Reference Vector<T>::At(SizeType pos) {
  if (pos >= size_) throw std::out_of_range("This index is out of range");
  return vector_[pos];
}

template <class T>
typename Vector<T>::Reference Vector<T>::operator[](SizeType pos) {
  return vector_[pos];
}

template <class T>
typename Vector<T>::ConstReference Vector<T>::Front() const {
  return vector_[0];
}

template <class T>
typename Vector<T>::ConstReference Vector<T>::Back() const {
  return vector_[size_ - 1];
}

template <class T>
T* Vector<T>::Data() {
  return vector_;
}

// Vector Iterators
template <class T>
typename Vector<T>::Iterator Vector<T>::Begin() {
  return Iterator(&vector_[0]);
}

template <class T>
typename Vector<T>::Iterator Vector<T>::End() {
  return Iterator(&vector_[size_]);
}

template <class T>
typename Vector<T>::ConstIterator Vector<T>::Cbegin() const {
  return ConstIterator(&vector_[0]);
}

template <class T>
typename Vector<T>::ConstIterator Vector<T>::Cend() const {
  return ConstIterator(&vector_[size_]);
}

// Vector Capacity
template <class T>
bool Vector<T>::Empty() const {
  return size_ == 0;
}

template <class T>
typename Vector<T>::SizeType Vector<T>::Size() const {
  return size_;
}

template <class T>
typename Vector<T>::SizeType Vector<T>::MaxSize() {
  return std::numeric_limits<SizeType>::max() / sizeof(vector_);
}

template <class T>
void Vector<T>::Reserve(SizeType n) {
  if (n > capacity_) {
    capacity_ = n;
    MoveData();
  }
}

template <class T>
typename Vector<T>::SizeType Vector<T>::Capacity() {
  return capacity_;
}

template <class T>
void Vector<T>::ShrinkToFit() {
  capacity_ = size_;
  MoveData();
}

// Vector Modifiers
template <class T>
void Vector<T>::Clear() {
  if (capacity_) {
    delete[] vector_;
    size_ = capacity_ = 0;
  }
}

template <class T>
typename Vector<T>::Iterator Vector<T>::Insert(Iterator pos,
                                               ConstReference value) {
  SizeType index = pos.current_ - Begin().current_;
  if (pos.current_ - End().current_ > 0)
    throw std::out_of_range("This index is out of range");
  if (size_ == capacity_) {
    ReSize();
    pos = Iterator(&vector_[index]);
  }
  for (auto i = --End(), j = End(); j != pos; --i, --j) {
    *j = *i;
  }
  *pos = value;
  ++size_;
  return pos;
}

template <class T>
void Vector<T>::Erase(Iterator pos) {
  if (pos.current_ - End().current_ >= 0)
    throw std::out_of_range("This index is out of range");
  for (Iterator i = pos, j = (++pos); j != End(); ++i, ++j) {
    *i = *j;
  }
  --size_;
}

template <class T>
void Vector<T>::PushBack(ConstReference value) {
  if (size_ == capacity_) ReSize();
  vector_[size_++] = value;
}

template <class T>
void Vector<T>::PopBack() {
  --size_;
}

template <class T>
void Vector<T>::Swap(Vector& other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(vector_, other.vector_);
}

// Bonus functions
template <class T>
template <typename... Args>
typename Vector<T>::Iterator Vector<T>::Emplace(ConstIterator pos,
                                                Args&&... args) {
  SizeType index = pos.current_ - Begin().current_;
  Iterator result(&vector_[index]);
  if (result.current_ - End().current_ > 0)
    throw std::out_of_range("This index is out of range");
  if (size_ == capacity_) {
    ReSize();
    result = Iterator(&vector_[index]);
  }
  for (auto i = --End(), j = End(); j != result; --i, --j) {
    *j = *i;
  }
  *result = T(std::forward<Args>(args)...);
  ++size_;
  return result;
}

template <class T>
template <typename... Args>
void Vector<T>::EmplaceBack(Args&&... args) {
  if (size_ == capacity_) ReSize();
  *End() = T(std::forward<Args>(args)...);
  ++size_;
}

// Support functions
template <class T>
void Vector<T>::ReSize() {
  capacity_ = capacity_ ? capacity_ * 2 : 1;
  MoveData();
}

template <class T>
void Vector<T>::MoveData() {
  if (!vector_) {
    vector_ = new ValueType[capacity_];
  } else {
    Pointer tmp = new ValueType[capacity_];
    std::copy(vector_, vector_ + size_, tmp);
    delete[] vector_;
    vector_ = tmp;
    tmp = nullptr;
  }
}

}  // namespace s21

#endif  // SRC_CONTAINERS_S21_VECTOR_H_