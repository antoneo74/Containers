#ifndef SRC_CONTAINERS_S21_QUEUE_H_
#define SRC_CONTAINERS_S21_QUEUE_H_

#include "s21_list.h"

namespace s21 {
template <class T, class Container = s21::List<T>>
class Queue {
 public:
  //  Queue Member type
  using Pointer = typename Container::Pointer;
  using ValueType = typename Container::ValueType;
  using Reference = typename Container::Reference;
  using ConstReference = typename Container::ConstReference;
  using SizeType = typename Container::SizeType;

  // Queue Member functions
  Queue() : container_() {}
  explicit Queue(std::initializer_list<T> const &items) : container_(items) {}
  Queue(const Queue &q) : container_(q.container_) {}
  Queue(Queue &&q) noexcept : container_(std::move(q.container_)) {}
  ~Queue() = default;
  Queue &operator=(Queue &&q) noexcept {
    container_ = std::move(q.container_);
    return *this;
  }

  // Queue Element access
  ConstReference Front() const { return container_.Front(); }
  ConstReference Back() const { return container_.Back(); }

  // Queue Capacity
  bool Empty() const { return container_.Empty(); }
  SizeType Size() const { return container_.Size(); }

  //  Queue Modifiers
  void Push(ConstReference value) { container_.PushBack(value); }
  void Pop() { container_.PopFront(); }
  void Swap(Queue &other) { container_.Swap(other.container_); }

  template <typename... Args>
  void EmplaceBack(Args &&...args) {
    container_.EmplaceBack(std::forward<Args>(args)...);
  }

 private:
  Container container_;
};

}  // namespace s21

#endif  // SRC_CONTAINERS_S21_QUEUE_H_
