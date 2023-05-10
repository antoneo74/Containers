#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>

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

  //	 Internal class ListIterator
  class ListIterator {
    friend class List;

   public:
    using pointer = Node*;
    using value_type = T;
    using size_type = size_t;
    ListIterator() = default;
    explicit ListIterator(pointer obj) : it_(obj){};

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

    ListIterator& operator+(size_type n) noexcept {
      while (n--) {
        it_ = it_->next_;
      }
      return *this;
    };

    value_type& operator*() const noexcept { return it_->value_; }

    bool operator!=(const ListIterator& other) const noexcept {
      return (it_ != other.it_);
    }

    bool operator==(const ListIterator& other) const noexcept {
      return (it_ == other.it_);
    }

   private:
    pointer it_ = nullptr;
  };

  //	 Internal class ListConstIterator
  class ListConstIterator {
    friend class List;

   public:
    using pointer = Node*;
    using value_type = T;
    using size_type = size_t;
    ListConstIterator() = default;
    explicit ListConstIterator(pointer obj) : it_(obj){};

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

    ListConstIterator& operator+(size_type n) noexcept {
      while (n--) {
        it_ = it_->next_;
      }
      return *this;
    };

    const value_type& operator*() const noexcept { return it_->value_; }

    bool operator!=(const ListConstIterator& other) const noexcept {
      return (it_ != other.it_);
    }

    bool operator==(const ListConstIterator& other) const noexcept {
      return (it_ == other.it_);
    }

   private:
    pointer it_ = nullptr;
  };

  // List Member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  using pointer = Node*;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  // List Functions
  List() = default;
  explicit List(size_type n);
  List(std::initializer_list<value_type> const& items);
  List(const List& l);
  List(List&& l);
  ~List();
  List& operator=(List&& l);

  // List Element access
  const_reference Front() const;
  const_reference Back() const;

  // List Iterators
  iterator Begin();
  iterator End();
  const_iterator Cbegin() const;
  const_iterator Cend() const;

  // List Capacity
  bool Empty() const;
  size_type Size() const;
  size_type MaxSize();

  // List Modifiers
  void Clear();
  iterator Insert(iterator pos, const_reference value);
  void Erase(iterator pos);
  void PushBack(const_reference value);
  void PopBack();
  void PushFront(const_reference value);
  void PopFront();
  void Swap(List& other);
  void Merge(List& other);
  void Splice(const_iterator pos, List& other);
  void Reverse();
  void Unique();
  void Sort();
  void PrintList();

  template <typename... Args>
  iterator Emplace(const_iterator pos, Args&&... args);
  template <typename... Args>
  void EmplaceBack(Args&&... args);
  template <typename... Args>
  void EmplaceFront(Args&&... args);

 private:
  pointer head_ = nullptr;
  pointer tail_ = nullptr;
  size_t size_{};
};

template <class T>
List<T>::List(size_type n) {
  while (n--) {
    PushBack(0);
  }
}

template <class T>
inline List<T>::List(std::initializer_list<value_type> const& items) {
  for (auto it = items.begin(); it != items.end(); it++) {
    PushBack(*it);
  }
}

template <class T>
List<T>::List(const List& l) {
  for (const_iterator it = l.Cbegin(); it != l.Cend(); ++it) {
    PushBack(*it);
  }
}

template <class T>
List<T>::List(List&& l) {
  Swap(l);
}

template <class T>
List<T>::~List() {
  Clear();
}

template <class T>
List<T>& List<T>::operator=(List&& l) {
  this.Clear();
  Swap(l);
  return *this;
}

template <class T>
typename List<T>::const_reference List<T>::Front() const {
  if (Empty()) {
    throw std::out_of_range("List is empty");
  }
  return head_->value_;
}

template <class T>
typename List<T>::const_reference List<T>::Back() const {
  if (Empty()) {
    throw std::out_of_range("List is empty");
  }
  return tail_->value_;
}

template <class T>
typename List<T>::iterator List<T>::Begin() {
  return iterator(head_);
}

template <class T>
typename List<T>::iterator List<T>::End() {
  return iterator();
}

template <class T>
typename List<T>::const_iterator List<T>::Cbegin() const {
  return const_iterator(head_);
}

template <class T>
typename List<T>::const_iterator List<T>::Cend() const {
  return const_iterator();
}

template <class T>
bool List<T>::Empty() const {
  return (size_ == 0);
}

template <class T>
typename List<T>::size_type List<T>::Size() const {
  return size_;
}

template <class T>
typename List<T>::size_type List<T>::MaxSize() {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <class T>
void List<T>::Clear() {
  while (head_) {
    PopFront();
  }
}

template <class T>
typename List<T>::iterator List<T>::Insert(iterator pos,
                                           const_reference value) {
  if (pos == End()) {
    PushBack(value);
    return iterator(tail_);
  } else if (pos == Begin()) {
    PushFront(value);
  } else {
    pointer current_node = pos.it_;
    pointer new_node = new Node(value);
    current_node->prev_->next_ = new_node;
    new_node->prev_ = current_node->prev_;
    current_node->prev_ = new_node;
    new_node->next_ = current_node;
    size_++;
  }
  return --pos;
}

template <class T>
void List<T>::Erase(iterator pos) {
  pointer tmp = pos.it_;
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
void List<T>::PushBack(const_reference value) {
  pointer node = new Node(value);
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
void List<T>::PushFront(const_reference value) {
  pointer node = new Node(value);
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
    const_iterator pos = Cend();
    Splice(pos, other);
  }
  Sort();
}

template <class T>
void List<T>::Splice(const_iterator pos, List& other) {
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
      pointer tmp = pos.it_;
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
    Sort();
    iterator first = Begin(), second = Begin() + 1;
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
  for (iterator i(head_); i != End(); ++i) {
    pointer tmp = i.it_;
    std::swap(tmp->next_, tmp->prev_);
  }
}

template <class T>
void List<T>::Sort() {
  if (Size() > 1) {
    iterator stop = Begin() + (Size() - 1);
    for (iterator first = Begin(); first != stop; --stop) {
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
void List<T>::PrintList() {
  iterator it_begin = Begin(), it_end = End();
  for (; it_begin != it_end; ++it_begin) {
    std::cout << *it_begin << "\t";
  }
  std::cout << "\n";
}

template <class T>
template <typename... Args>
typename List<T>::iterator List<T>::Emplace(const_iterator pos,
                                            Args&&... args) {
  if (pos == Cbegin()) {
    EmplaceFront(args...);
    return iterator(head_);
  } else if (pos == Cend()) {
    EmplaceBack(args...);
    return iterator(tail_);
  } else {
    pointer new_node = new Node{value_type(std::forward<Args>(args)...)};
    pointer current = pos.it_;
    current->prev_->next_ = new_node;
    new_node->prev_ = current->prev_;
    current->prev_ = new_node;
    new_node->next_ = current;
    size_++;
    return iterator(new_node);
  }
}

template <class T>
template <typename... Args>
void List<T>::EmplaceBack(Args&&... args) {
  pointer new_node = new Node(std::forward<Args>(args)...);
  if (Empty()) {
    head_ = tail_ = new_node;
  } else {
    tail_->next_ = new_node;
    new_node->prev_ = tail_;
    tail_ = new_node;
  }
  size_++;
}

template <class T>
template <typename... Args>
void List<T>::EmplaceFront(Args&&... args) {
  pointer new_node = new Node(std::forward<Args>(args)...);
  if (Empty()) {
    head_ = tail_ = new_node;
  } else {
    head_->prev_ = new_node;
    new_node->next_ = head_;
    head_ = new_node;
  }
  size_++;
}

}  // namespace s21

#endif  // SRC_S21_LIST_H_
