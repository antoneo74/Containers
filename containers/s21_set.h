#ifndef SRC_CONTAINERS_S21_SET_H_
#define SRC_CONTAINERS_S21_SET_H_

#include <initializer_list>
#include <iterator>
#include <limits>

#include "../containers_extra/s21_multiset.h"
#include "s21_map.h"
#include "s21_queue.h"
#include "s21_vector.h"

namespace s21 {
template <class T>
struct SetNode {
  SetNode* parent = nullptr;
  SetNode* left = nullptr;
  SetNode* right = nullptr;
  T value;
  SetNode() = default;
  explicit SetNode(const T& v) : value(v) {}
};

template <class T>
class Set {
 public:
  class SetIterator;
  class SetConstIterator;

  // Set Member type
  using ValueType = T;
  using Reference = ValueType&;
  using ConstReference = const ValueType&;
  using SizeType = size_t;
  using Node = SetNode<T>;
  using Pointer = Node*;
  using Iterator = SetIterator;
  using ConstIterator = SetConstIterator;
  using Pair = std::pair<Iterator, bool>;

  // internal class SetIterator
  class SetIterator {
    friend class Set;

   public:
    SetIterator(Pointer obj) : current_(obj) {}
    SetIterator() : current_(nullptr) {}
    SetIterator(const SetIterator& obj) { current_ = obj.current_; }

    SetIterator& operator=(const SetIterator& obj) noexcept {
      current_ = obj.current_;
      return *this;
    }

    SetIterator& operator--() noexcept {
      if (current_->left) {
        current_ = current_->left;
        while (current_->right != nullptr) {
          current_ = current_->right;
        }
      } else {
        Pointer tmp = current_->parent;
        while (tmp && tmp->value > current_->value) {
          current_ = tmp;
          tmp = tmp->parent;
        }
        current_ = tmp;
      }
      return *this;
    }

    SetIterator& operator++() noexcept {
      if (current_->right) {
        current_ = current_->right;
        while (current_->left != nullptr) {
          current_ = current_->left;
        }
      } else {
        Pointer tmp = current_->parent;
        while (tmp && tmp->value < current_->value) {
          current_ = tmp;
          tmp = tmp->parent;
        }
        current_ = tmp;
      }
      return *this;
    }

    bool operator!=(const SetIterator& other) const noexcept {
      return (current_ != other.current_);
    }

    Reference operator*() noexcept { return current_->value; }

    Pointer operator->() { return current_; }

   private:
    Pointer current_;
  };

  // internal class SetConstIterator
  class SetConstIterator {
    friend class Set;

   public:
    SetConstIterator(Pointer obj) : current_(obj) {}
    SetConstIterator() : current_(nullptr) {}
    SetConstIterator(const SetConstIterator& obj) { current_ = obj.current_; }

    SetConstIterator& operator=(const SetConstIterator& obj) noexcept {
      current_ = obj.current_;
      return *this;
    }

    SetConstIterator& operator--() noexcept {
      if (current_->left) {
        current_ = current_->left;
        while (current_->right != nullptr) {
          current_ = current_->right;
        }
      } else {
        Pointer tmp = current_->parent;
        while (tmp && tmp->value > current_->value) {
          current_ = tmp;
          tmp = tmp->parent;
        }
        current_ = tmp;
      }
      return *this;
    }

    SetConstIterator& operator++() noexcept {
      if (current_->right) {
        current_ = current_->right;
        while (current_->left != nullptr) {
          current_ = current_->left;
        }
      } else {
        Pointer tmp = current_->parent;
        while (tmp && tmp->value < current_->value) {
          current_ = tmp;
          tmp = tmp->parent;
        }
        current_ = tmp;
      }
      return *this;
    }

    bool operator!=(const SetConstIterator& other) const noexcept {
      return (current_ != other.current_);
    }

    ConstReference operator*() noexcept { return current_->value; }

   private:
    const Pointer current_;
  };

  // Set Member functions
  Set() = default;
  Set(std::initializer_list<ValueType> const& items);
  Set(const Set& s);
  Set(Set&& s) noexcept;
  ~Set();
  Set& operator=(Set&& s) noexcept;

  // Set Iterators
  Iterator Begin();
  Iterator End();

  // Set Capacity
  bool Empty();
  SizeType Size();
  SizeType MaxSize();

  // Set Modifiers
  void Clear();
  Pair Insert(ConstReference value);
  void Erase(Iterator pos);
  void Swap(Set& other);
  void Merge(Set& other);

  // Set Lookup
  Iterator Find(ConstReference v);
  bool Contains(ConstReference v);

  // Bonus Function
  template <typename... Args>
  Vector<Pair> Emplace(Args&&... args);

 private:
  Pointer root_ = nullptr;
  SizeType size_{0};

  // Support functions
  void CopyTree(const Set& other);
  void EraseList(Pointer tmp);
  void EraseLeftBranch(Pointer tmp);
  void EraseRightBranch(Pointer tmp);
  void EraseNode(Pointer tmp);
  std::pair<Iterator, bool> Search(ConstReference v);
};

// Set Member functions
template <class T>
Set<T>::Set(std::initializer_list<ValueType> const& items) {
  for (auto it : items) {
    Insert(it);
  }
}

template <class T>
Set<T>::Set(const Set& s) {
  CopyTree(s);
}

template <class T>
Set<T>::Set(Set&& s) noexcept {
  Swap(s);
}

template <class T>
Set<T>::~Set() {
  Clear();
}

template <class T>
Set<T>& Set<T>::operator=(Set&& s) noexcept {
  Clear();
  Swap(s);
  return *this;
}

// Set Iterators
template <class T>
typename Set<T>::Iterator Set<T>::Begin() {
  if (!root_) {
    return Iterator();
  } else {
    Iterator begin(root_);
    while (begin->left) {
      begin = begin->left;
    }
    return begin;
  }
}

template <class T>
typename Set<T>::Iterator Set<T>::End() {
  return Iterator();
}

// Set Capacity
template <class T>
bool Set<T>::Empty() {
  return root_ == nullptr;
}

template <class T>
typename Set<T>::SizeType Set<T>::Size() {
  return size_;
}

template <class T>
typename Set<T>::SizeType Set<T>::MaxSize() {
  return std::numeric_limits<SizeType>::max() / sizeof(Node);
}

// Set Modifiers
template <class T>
void Set<T>::Clear() {
  for (Iterator i = Begin(); i != End();) {
    Iterator tmp = i;
    ++i;
    Erase(tmp);
  }
}

template <class T>
std::pair<typename Set<T>::Iterator, bool> Set<T>::Insert(
    ConstReference value) {
  Pointer tmp = new Node(value);
  if (!root_) {  // if set is empty
    root_ = tmp;
  } else {
    Pair top = Search(value);
    if (top.second) {
      delete tmp;
      return std::make_pair(Iterator(root_), false);
    } else {
      tmp->parent = top.first.current_;
      if (*(top.first) > value) {
        top.first->left = tmp;
      } else {
        top.first->right = tmp;
      }
    }
  }
  ++size_;
  return std::make_pair(Iterator(tmp), true);
}

template <class T>
void Set<T>::Erase(Iterator pos) {
  Pointer tmp = pos.current_;
  if (tmp) {
    if (!tmp->left && !tmp->right) {
      EraseList(tmp);
    } else if (tmp->left && !tmp->right) {
      EraseLeftBranch(tmp);
    } else if (!tmp->left && tmp->right) {
      EraseRightBranch(tmp);
    } else if (tmp->left && tmp->right) {
      EraseNode(tmp);
    }
    delete tmp;
    size_--;
  }
}

template <class T>
void Set<T>::Swap(Set& other) {
  if (this != &other) {
    std::swap(size_, other.size_);
    std::swap(root_, other.root_);
  }
}

template <class T>
void Set<T>::Merge(Set& other) {
  for (Iterator i = other.Begin(); i != other.End(); ++i) {
    Insert(*i);
  }
}

template <class T>
typename Set<T>::Iterator Set<T>::Find(ConstReference v) {
  Pair res = Search(v);
  if (res.second) return res.first;
  return Iterator();
}

template <class T>
bool Set<T>::Contains(ConstReference v) {
  Pair res = Search(v);
  return res.second;
}

// Bonus Function
template <class T>
template <typename... Args>
Vector<typename Set<T>::Pair> Set<T>::Emplace(Args&&... args) {
  std::initializer_list<ValueType> items{args...};
  Vector<Pair> res;
  for (auto it = items.begin(); it != items.end(); ++it) {
    res.PushBack(Insert(*it));
  }
  return res;
}

// Support functions
template <class T>
void Set<T>::CopyTree(const Set& other) {
  if (other.root_) {
    s21::Queue<Pointer> tmp;
    tmp.Push(other.root_);
    while (!tmp.Empty()) {
      int n = tmp.Size();
      for (int i = 0; i < n; i++) {
        Pointer curr = tmp.Front();
        tmp.Pop();
        Insert(curr->value);
        if (curr->left) tmp.Push(curr->left);
        if (curr->right) tmp.Push(curr->right);
      }
    }
  }
}

template <class T>
void Set<T>::EraseList(Pointer tmp) {
  if (size_ == 1)
    root_ = nullptr;
  else {
    if (tmp->parent->value > tmp->value)
      tmp->parent->left = nullptr;
    else
      tmp->parent->right = nullptr;
  }
}

template <class T>
void Set<T>::EraseLeftBranch(Pointer tmp) {
  if (tmp == root_) {
    root_ = tmp->left;
    root_->parent = nullptr;
  } else {
    tmp->left->parent = tmp->parent;
    if (tmp->parent->value > tmp->value)
      tmp->parent->left = tmp->left;
    else
      tmp->parent->right = tmp->left;
  }
}

template <class T>
void Set<T>::EraseRightBranch(Pointer tmp) {
  if (tmp == root_) {
    root_ = tmp->right;
    root_->parent = nullptr;
  } else {
    tmp->right->parent = tmp->parent;
    if (tmp->parent->value > tmp->value)
      tmp->parent->left = tmp->right;
    else
      tmp->parent->right = tmp->right;
  }
}

template <class T>
void Set<T>::EraseNode(Pointer tmp) {
  Iterator it(tmp);
  --it;
  Iterator p(it->parent);

  if (it->left) {
    if (*it > *p) {
      p->right = it->left;
    } else {
      p->left = it->left;
    }
    it->left->parent = p.current_;
  } else {
    if (*it > *p)
      p->right = nullptr;
    else
      p->left = nullptr;
  }

  it->left = tmp->left;
  it->right = tmp->right;
  it->parent = tmp->parent;

  if (tmp->left) tmp->left->parent = it.current_;
  if (tmp->right) tmp->right->parent = it.current_;
  if (tmp == root_)
    root_ = it.current_;
  else {
    if (*it > tmp->parent->value) {
      tmp->parent->right = it.current_;
    } else {
      tmp->parent->left = it.current_;
    }
  }
}

template <class T>
std::pair<typename Set<T>::Iterator, bool> Set<T>::Search(ConstReference v) {
  Pointer it = root_, top = it;
  while (it) {
    top = it;
    if (it->value == v) {
      return std::make_pair(Iterator(top), true);
    } else if (it->value > v) {
      it = it->left;
    } else {
      it = it->right;
    }
  }
  return std::make_pair(Iterator(top), false);
}

}  // namespace s21

#endif  // SRC_CONTAINERS_S21_SET_H_
