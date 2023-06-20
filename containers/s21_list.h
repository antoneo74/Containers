#ifndef SRC_CONTAINERS_S21_LIST_H_
#define SRC_CONTAINERS_S21_LIST_H_

#include <initializer_list>
#include <iterator>
#include <limits>

namespace s21 {
template <class T>
class List {
 public:
  struct Node {
    T value_;
    Node* next_ = nullptr;
    Node* prev_ = nullptr;
    Node(T value) : value_(value){};
    template <typename... Args>
    Node(Args&&... args) : value_(std::forward<Args>(args)...){};
  };

  // Internal class ListIterator
  class ListIterator {
    friend class List;

   public:
    using Pointer = Node*;
    using ValueType = T;
    using SizeType = size_t;
    ListIterator() = default;
    explicit ListIterator(Pointer obj) : it_(obj){};

    ListIterator& operator++() noexcept {
      it_ = it_->next_;
      return *this;
    };

    ListIterator operator++(int) noexcept {
      ListIterator tmp = *this;
      it_ = it_->next_;
      return tmp;
    };

    ListIterator& operator--() noexcept {
      it_ = it_->prev_;
      return *this;
    };

    ListIterator& operator+(SizeType n) noexcept {
      while (n--) {
        it_ = it_->next_;
      }
      return *this;
    };

    ValueType& operator*() const noexcept { return it_->value_; }

    bool operator!=(const ListIterator& other) const noexcept {
      return (it_ != other.it_);
    }

    bool operator==(const ListIterator& other) const noexcept {
      return (it_ == other.it_);
    }

   private:
    Pointer it_ = nullptr;
  };

  // Internal class ListConstIterator
  class ListConstIterator {
    friend class List;

   public:
    using Pointer = Node*;
    using ValueType = T;
    using SizeType = size_t;
    ListConstIterator() = default;
    explicit ListConstIterator(Pointer obj) : it_(obj){};

    ListConstIterator& operator++() noexcept {
      it_ = it_->next_;
      return *this;
    };

    ListConstIterator operator++(int) noexcept {
      ListConstIterator tmp = *this;
      it_ = it_->next_;
      return tmp;
    };

    ListConstIterator& operator--() noexcept {
      it_ = it_->prev_;
      return *this;
    };

    ListConstIterator& operator+(SizeType n) noexcept {
      while (n--) {
        it_ = it_->next_;
      }
      return *this;
    };

    const ValueType& operator*() const noexcept { return it_->value_; }

    bool operator!=(const ListConstIterator& other) const noexcept {
      return (it_ != other.it_);
    }

    bool operator==(const ListConstIterator& other) const noexcept {
      return (it_ == other.it_);
    }

   private:
    Pointer it_ = nullptr;
  };

  // List Member type
  using ValueType = T;
  using Reference = T&;
  using ConstReference = const T&;
  using SizeType = size_t;
  using Pointer = Node*;
  using Iterator = ListIterator;
  using ConstIterator = ListConstIterator;

  // List Functions
  List() = default;
  explicit List(SizeType n);
  List(std::initializer_list<ValueType> const& items);
  List(const List& l);
  List(List&& l) noexcept;
  ~List();
  List& operator=(List&& l) noexcept;

  // List Element access
  ConstReference Front() const;
  ConstReference Back() const;

  // List Iterators
  Iterator Begin();
  Iterator End();
  ConstIterator Cbegin() const;
  ConstIterator Cend() const;

  // List Capacity
  bool Empty() const;
  SizeType Size() const;
  SizeType MaxSize();

  // List Modifiers
  void Clear();
  Iterator Insert(Iterator pos, ConstReference value);
  void Erase(Iterator pos);
  void PushBack(ConstReference value);
  void PopBack();
  void PushFront(ConstReference value);
  void PopFront();
  void Swap(List& other);
  void Merge(List& other);
  void Splice(ConstIterator pos, List& other);
  void Reverse();
  void Unique();
  void Sort();

  template <typename... Args>
  Iterator Emplace(ConstIterator pos, Args&&... args);
  template <typename... Args>
  void EmplaceBack(Args&&... args);
  template <typename... Args>
  void EmplaceFront(Args&&... args);

 private:
  Pointer head_ = nullptr;
  Pointer tail_ = nullptr;
  SizeType size_{};
};

template <class T>
List<T>::List(SizeType n) {
  while (n--) {
    PushBack(0);
  }
}

template <class T>
inline List<T>::List(std::initializer_list<ValueType> const& items) {
  for (auto it = items.begin(); it != items.end(); it++) {
    PushBack(*it);
  }
}

template <class T>
List<T>::List(const List& l) {
  for (ConstIterator it = l.Cbegin(); it != l.Cend(); ++it) {
    PushBack(*it);
  }
}

template <class T>
List<T>::List(List&& l) noexcept {
  Swap(l);
}

template <class T>
List<T>::~List() {
  Clear();
}

template <class T>
List<T>& List<T>::operator=(List&& l) noexcept {
  this->Clear();
  Swap(l);
  return *this;
}

template <class T>
typename List<T>::ConstReference List<T>::Front() const {
  if (Empty()) {
    throw std::out_of_range("Container is empty");
  }
  return head_->value_;
}

template <class T>
typename List<T>::ConstReference List<T>::Back() const {
  if (Empty()) {
    throw std::out_of_range("Container is empty");
  }
  return tail_->value_;
}

template <class T>
typename List<T>::Iterator List<T>::Begin() {
  return Iterator(head_);
}

template <class T>
typename List<T>::Iterator List<T>::End() {
  return Iterator();
}

template <class T>
typename List<T>::ConstIterator List<T>::Cbegin() const {
  return ConstIterator(head_);
}

template <class T>
typename List<T>::ConstIterator List<T>::Cend() const {
  return ConstIterator();
}

template <class T>
bool List<T>::Empty() const {
  return (size_ == 0);
}

template <class T>
typename List<T>::SizeType List<T>::Size() const {
  return size_;
}

template <class T>
typename List<T>::SizeType List<T>::MaxSize() {
  return std::numeric_limits<SizeType>::max() / sizeof(Node);
}

template <class T>
void List<T>::Clear() {
  while (head_) {
    PopFront();
  }
}

template <class T>
typename List<T>::Iterator List<T>::Insert(Iterator pos, ConstReference value) {
  if (pos == End()) {
    PushBack(value);
    return Iterator(tail_);
  } else if (pos == Begin()) {
    PushFront(value);
  } else {
    Pointer current_node = pos.it_;
    Pointer new_node = new Node(value);
    current_node->prev_->next_ = new_node;
    new_node->prev_ = current_node->prev_;
    current_node->prev_ = new_node;
    new_node->next_ = current_node;
    size_++;
  }
  return --pos;
}

template <class T>
void List<T>::Erase(Iterator pos) {
  Pointer tmp = pos.it_;
  if (tmp == nullptr) {
    throw std::out_of_range("Iterator is NULL");
  }
  if (tmp == head_) {
    PopFront();
  } else if (tmp == tail_) {
    PopBack();
  } else {
    tmp->next_->prev_ = tmp->prev_;
    tmp->prev_->next_ = tmp->next_;
    size_--;
    delete tmp;
  }
}

template <class T>
void List<T>::PushBack(ConstReference value) {
  Pointer node = new Node(value);
  if (Empty()) {
    head_ = tail_ = node;
  } else {
    tail_->next_ = node;
    node->prev_ = tail_;
    tail_ = node;
  }
  size_++;
}

template <class T>
void List<T>::PopBack() {
  if (size_ == 1) {
    delete tail_;
    head_ = tail_ = nullptr;
    size_ = 0;
  } else if (size_ > 1) {
    tail_ = tail_->prev_;
    delete tail_->next_;
    tail_->next_ = nullptr;
    size_--;
  }
}

template <class T>
void List<T>::PushFront(ConstReference value) {
  Pointer node = new Node(value);
  if (Empty()) {
    head_ = tail_ = node;
  } else {
    head_->prev_ = node;
    node->next_ = head_;
    head_ = node;
  }
  size_++;
}

template <class T>
void List<T>::PopFront() {
  if (size_ == 1) {
    delete head_;
    head_ = tail_ = nullptr;
    size_ = 0;
  } else if (size_ > 1) {
    head_ = head_->next_;
    delete head_->prev_;
    head_->prev_ = nullptr;
    size_--;
  }
}

template <class T>
void List<T>::Swap(List& other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

template <class T>
void List<T>::Merge(List& other) {
  if (Empty() && !other.Empty()) {
    Swap(other);
  } else if (!Empty() && !other.Empty()) {
    ConstIterator pos = Cend();
    Splice(pos, other);
  }
}

template <class T>
void List<T>::Splice(ConstIterator pos, List& other) {
  if (!other.Empty()) {
    if (Empty()) {
      head_ = other.head_;
      tail_ = other.tail_;
    } else if (pos == Cbegin()) {
      head_->prev_ = other.tail_;
      other.tail_->next_ = head_;
      head_ = other.head_;
    } else if (pos == Cend()) {
      tail_->next_ = other.head_;
      other.head_->prev_ = tail_;
      tail_ = other.tail_;
    } else {
      Pointer tmp = pos.it_;
      tmp->prev_->next_ = other.head_;
      other.head_->prev_ = tmp->prev_;
      tmp->prev_ = other.tail_;
      other.tail_->next_ = tmp;
    }
    size_ += other.size_;
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }
}

template <class T>
void List<T>::Unique() {
  if (Size() > 1) {
    Iterator first = Begin(), second = Begin() + 1;
    while (second != End()) {
      if (*first == *second) {
        Erase(second);
        second = first;
      } else {
        ++first;
      }
      ++second;
    }
  }
}

template <class T>
void List<T>::Reverse() {
  std::swap(head_, tail_);
  for (Iterator i(head_); i != End(); ++i) {
    Pointer tmp = i.it_;
    std::swap(tmp->next_, tmp->prev_);
  }
}

template <class T>
void List<T>::Sort() {
  if (Size() > 1) {
    Iterator stop = Begin() + (Size() - 1);
    for (Iterator first = Begin(); first != stop; --stop) {
      bool flag = true;
      auto second = Begin() + 1;
      for (; first != stop; ++first, ++second) {
        if (*first > *second) {
          std::swap(*first, *second);
          flag = false;
        }
      }
      if (flag) break;
      first = Begin();
    }
  }
}

template <class T>
template <typename... Args>
typename List<T>::Iterator List<T>::Emplace(ConstIterator pos, Args&&... args) {
  if (pos == Cbegin()) {
    EmplaceFront(args...);
    return Iterator(head_);
  } else if (pos == Cend()) {
    EmplaceBack(args...);
    return Iterator(tail_);
  } else {
    Pointer new_node = new Node{ValueType(std::forward<Args>(args)...)};
    Pointer current = pos.it_;
    current->prev_->next_ = new_node;
    new_node->prev_ = current->prev_;
    current->prev_ = new_node;
    new_node->next_ = current;
    size_++;
    return Iterator(new_node);
  }
}

template <class T>
template <typename... Args>
void List<T>::EmplaceBack(Args&&... args) {
  PushBack(std::forward<Args>(args)...);
}

template <class T>
template <typename... Args>
void List<T>::EmplaceFront(Args&&... args) {
  PushFront(std::forward<Args>(args)...);
}

}  // namespace s21

#endif  // SRC_CONTAINERS_S21_LIST_H_
