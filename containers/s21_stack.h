#ifndef SRC_CONTAINERS_S21_STACK_H_
#define SRC_CONTAINERS_S21_STACK_H_

#include "s21_vector.h"

namespace s21 {
template <class T, class Container = s21::Vector<T>>
class Stack {
 public:
  // Stack Member type
  using ValueType = typename Container::ValueType;
  using Reference = typename Container::Reference;
  using ConstReference = typename Container::ConstReference;
  using SizeType = typename Container::SizeType;

  // Stack Member functions
  Stack() : container_() {}
  explicit Stack(std::initializer_list<ValueType> const &items)
      : container_(items) {}
  Stack(const Stack &s) : container_(s.container_) {}
  Stack(Stack &&s) noexcept : container_(std::move(s.container_)) {}
  ~Stack() = default;
  Stack &operator=(Stack &&s) noexcept {
    this->container_ = std::move(s.container_);
    return *this;
  }

  // Stack Element access
  ConstReference Top() const noexcept { return container_.Back(); }

  // Stack Capacity
  bool Empty() const { return container_.Empty(); }
  SizeType Size() const { return container_.Size(); }
  SizeType MaxSize() { return container_.MaxSize(); }

  // Stack Modifiers
  void Push(ConstReference value) { container_.PushBack(value); }
  void Pop() { container_.PopBack(); }
  void Swap(Stack &other) { container_.Swap(other.container_); }

  // Stack Modifiers
  template <typename... Args>
  void EmplaceFront(Args &&...args) {
    container_.EmplaceBack(std::forward<Args>(args)...);
  }

 private:
  Container container_;
};

}  // namespace s21

#endif  // SRC_CONTAINERS_S21_STACK_H_
