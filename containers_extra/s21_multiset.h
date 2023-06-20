#ifndef SRC_CONTAINERS_EXTRA_S21_MULTISET_H_
#define SRC_CONTAINERS_EXTRA_S21_MULTISET_H_

#include <initializer_list>
#include <iterator>
#include <limits>

#include "../containers/s21_map.h"
#include "../containers/s21_queue.h"
#include "../containers/s21_vector.h"

namespace s21 {
template <class T>
struct MSetNode {
  MSetNode* parent = nullptr;
  MSetNode* left = nullptr;
  MSetNode* right = nullptr;
  Vector<T> value;
  MSetNode() = default;
  explicit MSetNode(const T& v) { value.PushBack(v); }
};

template <class T>
class Multiset {
 public:
  class MultisetIterator;
  class MultisetConstIterator;

  // Set Member type
  using ValueType = T;
  using Reference = ValueType&;
  using ConstReference = const ValueType&;
  using SizeType = size_t;
  using Node = MSetNode<T>;
  using Pointer = Node*;
  using Iterator = MultisetIterator;
  using ConstIterator = MultisetConstIterator;
  using Pair = std::pair<Iterator, bool>;

  // internal class MultisetIterator
  class MultisetIterator {
    friend class Multiset;

   public:
    MultisetIterator(Pointer obj, SizeType s) : current_(obj), s_(s) {}
    MultisetIterator() : current_(nullptr), s_(0) {}
    MultisetIterator(const MultisetIterator& obj)
        : current_(obj.current_), s_(obj.s_) {}

    MultisetIterator& operator=(const MultisetIterator& obj) noexcept {
      current_ = obj.current_;
      s_ = obj.s_;
      return *this;
    }

    MultisetIterator& operator--() noexcept {
      if (s_ > 1) {
        --s_;
      } else {
        if (current_->left) {
          current_ = current_->left;
          while (current_->right != nullptr) {
            current_ = current_->right;
          }
        } else {
          Pointer tmp = current_->parent;
          while (tmp && tmp->value[0] > current_->value[0]) {
            current_ = tmp;
            tmp = tmp->parent;
          }
          current_ = tmp;
        }
        if (current_) s_ = current_->value.Size();
      }
      return *this;
    }

    MultisetIterator& operator++() noexcept {
      if (s_ > 1) {
        --s_;
      } else {
        if (current_->right) {
          current_ = current_->right;
          while (current_->left != nullptr) {
            current_ = current_->left;
          }
        } else {
          Pointer tmp = current_->parent;
          while (tmp && tmp->value[0] < current_->value[0]) {
            current_ = tmp;
            tmp = tmp->parent;
          }
          current_ = tmp;
        }
        if (current_) s_ = current_->value.Size();
      }
      return *this;
    }

    bool operator!=(const MultisetIterator& other) const noexcept {
      return (current_ != other.current_);
    }

    ConstReference operator*() noexcept { return current_->value[0]; }

    Pointer operator->() { return current_; }

   private:
    Pointer current_;
    SizeType s_;
  };

  // internal class MultisetConstIterator
  class MultisetConstIterator {
    friend class Multiset;

   public:
    MultisetConstIterator(Pointer obj, SizeType s) : current_(obj), s_(s) {}
    MultisetConstIterator() : current_(nullptr), s_(0) {}
    MultisetConstIterator(const MultisetConstIterator& obj)
        : current_(obj.current_), s_(obj.s_) {}

    MultisetConstIterator& operator=(
        const MultisetConstIterator& obj) noexcept {
      current_ = obj.current_;
      s_ = obj.s_;
      return *this;
    }

    MultisetConstIterator& operator--() noexcept {
      if (s_ > 1) {
        --s_;
      } else {
        if (current_->left) {
          current_ = current_->left;
          while (current_->right != nullptr) {
            current_ = current_->right;
          }
        } else {
          Pointer tmp = current_->parent;
          while (tmp && tmp->value[0] > current_->value[0]) {
            current_ = tmp;
            tmp = tmp->parent;
          }
          current_ = tmp;
        }
        if (current_) s_ = current_->value.Size();
      }
      return *this;
    }

    MultisetConstIterator& operator++() noexcept {
      if (s_ > 1) {
        --s_;
      } else {
        if (current_->right) {
          current_ = current_->right;
          while (current_->left != nullptr) {
            current_ = current_->left;
          }
        } else {
          Pointer tmp = current_->parent;
          while (tmp && tmp->value[0] < current_->value[0]) {
            current_ = tmp;
            tmp = tmp->parent;
          }
          current_ = tmp;
        }
        if (current_) s_ = current_->value.Size();
      }
      return *this;
    }

    bool operator!=(const MultisetConstIterator& other) const noexcept {
      return (current_ != other.current_);
    }

    ConstReference operator*() noexcept { return current_->value[0]; }

    Pointer operator->() { return current_; }

   private:
    const Pointer current_;
    SizeType s_;
  };

  // Multiset Member functions
  Multiset() = default;
  Multiset(std::initializer_list<ValueType> const& items);
  explicit Multiset(const Multiset& s);
  Multiset(Multiset&& s) noexcept;
  ~Multiset();
  Multiset& operator=(Multiset&& s) noexcept;

  // Multiset Iterators
  Iterator Begin();
  Iterator End();

  // Multiset Capacity
  bool Empty();
  SizeType Size();
  SizeType MaxSize();

  // Multiset Modifiers
  void Clear();
  Iterator Insert(ConstReference value);
  void Erase(Iterator pos);
  void Swap(Multiset& other);
  void Merge(Multiset& other);

  // Multiset Lookup
  SizeType Count(ConstReference v);
  Iterator Find(ConstReference v);
  bool Contains(ConstReference v);
  std::pair<Iterator, Iterator> EqualRange(ConstReference v);
  Iterator LowerBound(ConstReference v);
  Iterator UpperBound(ConstReference v);

  // Bonus Function
  template <typename... Args>
  Vector<Pair> Emplace(Args&&... args);

 private:
  Pointer root_ = nullptr;
  SizeType size_{0};

  // Support functions
  void CopyTree(const Multiset& other);
  void EraseList(Pointer tmp);
  void EraseLeftBranch(Pointer tmp);
  void EraseRightBranch(Pointer tmp);
  void EraseNode(Pointer tmp);
  Pair Search(ConstReference v);
};

// Multiset Member functions
template <class T>
Multiset<T>::Multiset(std::initializer_list<ValueType> const& items) {
  for (auto it : items) {
    Insert(it);
  }
}

template <class T>
Multiset<T>::Multiset(const Multiset& s) {
  CopyTree(s);
}

template <class T>
Multiset<T>::Multiset(Multiset&& s) noexcept {
  Swap(s);
}

template <class T>
Multiset<T>::~Multiset() {
  Clear();
}

template <class T>
Multiset<T>& Multiset<T>::operator=(Multiset&& s) noexcept {
  Clear();
  Swap(s);
  return *this;
}

// Multiset Iterators
template <class T>
typename Multiset<T>::Iterator Multiset<T>::Begin() {
  if (!root_) {
    return Iterator();
  } else {
    Pointer begin = root_;
    while (begin->left) {
      begin = begin->left;
    }
    return Iterator(begin, begin->value.Size());
  }
}

template <class T>
typename Multiset<T>::Iterator Multiset<T>::End() {
  return Iterator();
}

// Multiset Capacity
template <class T>
bool Multiset<T>::Empty() {
  return root_ == nullptr;
}

template <class T>
typename Multiset<T>::SizeType Multiset<T>::Size() {
  return size_;
}

template <class T>
typename Multiset<T>::SizeType Multiset<T>::MaxSize() {
  return std::numeric_limits<SizeType>::max() / sizeof(Node);
}

// Multiset Modifiers
template <class T>
void Multiset<T>::Clear() {
  for (Iterator i = Begin(); i != End();) {
    Iterator tmp = i;
    ++i;
    Erase(tmp);
  }
}

template <class T>
typename Multiset<T>::Iterator Multiset<T>::Insert(ConstReference value) {
  Pointer tmp;
  if (!root_) {  // if set is empty
    tmp = new Node(value);
    root_ = tmp;
  } else {
    Pair top = Search(value);
    if (top.second) {
      top.first->value.PushBack(value);
      ++size_;
      ++(top.first.s_);
      return top.first;
    } else {
      tmp = new Node(value);
      tmp->parent = top.first.current_;
      if (*(top.first) > value) {
        top.first->left = tmp;
      } else {
        top.first->right = tmp;
      }
    }
  }
  ++size_;
  return Iterator(tmp, tmp->value.Size());
}

template <class T>
void Multiset<T>::Erase(Iterator pos) {
  if (pos->value.Size() > 1) {
    pos->value.PopBack();
    --size_;
  } else {
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
      --size_;
    }
  }
}

template <class T>
void Multiset<T>::Swap(Multiset& other) {
  if (this != &other) {
    std::swap(size_, other.size_);
    std::swap(root_, other.root_);
  }
}

template <class T>
void Multiset<T>::Merge(Multiset& other) {
  for (Iterator i = other.Begin(); i != other.End(); ++i) {
    Insert(*i);
  }
}

template <class T>
typename Multiset<T>::SizeType Multiset<T>::Count(ConstReference v) {
  Pair res = Search(v);
  return (res.second ? res.first->value.Size() : 0);
}

template <class T>
typename Multiset<T>::Iterator Multiset<T>::Find(ConstReference v) {
  Pair res = Search(v);
  if (res.second) return res.first;
  return Iterator();
}

template <class T>
bool Multiset<T>::Contains(ConstReference v) {
  Pair res = Search(v);
  return res.second;
}

template <class T>
std::pair<typename Multiset<T>::Iterator, typename Multiset<T>::Iterator>
Multiset<T>::EqualRange(ConstReference v) {
  return std::make_pair(LowerBound(v), UpperBound(v));
}

template <class T>
typename Multiset<T>::Iterator Multiset<T>::LowerBound(ConstReference v) {
  Pair res = Search(v);
  if (res.second)
    return res.first;
  else {
    return UpperBound(v);
  }
}

template <class T>
typename Multiset<T>::Iterator Multiset<T>::UpperBound(ConstReference v) {
  Iterator it;
  for (it = Begin(); it != End() && *it <= v; ++it) {
  }
  return it;
}

// Bonus Function
template <class T>
template <typename... Args>
Vector<typename Multiset<T>::Pair> Multiset<T>::Emplace(Args&&... args) {
  std::initializer_list<ValueType> items{args...};
  Vector<Pair> res;
  for (auto it = items.begin(); it != items.end(); ++it) {
    res.PushBack(std::make_pair(Insert(*it), true));
  }
  return res;
}

// Support functions
template <class T>
void Multiset<T>::CopyTree(const Multiset& other) {
  if (other.root_) {
    s21::Queue<Pointer> tmp;
    tmp.Push(other.root_);
    while (!tmp.Empty()) {
      int n = tmp.Size();
      for (int i = 0; i < n; ++i) {
        Pointer curr = tmp.Front();
        tmp.Pop();
        for (SizeType j = 0; j < curr->value.Size(); ++j) {
          Insert(curr->value[j]);
        }
        if (curr->left) {
          tmp.Push(curr->left);
        }
        if (curr->right) {
          tmp.Push(curr->right);
        }
      }
    }
  }
}

template <class T>
void Multiset<T>::EraseList(Pointer tmp) {
  if (size_ == 1)
    root_ = nullptr;
  else {
    if (tmp->parent->value[0] > tmp->value[0])
      tmp->parent->left = nullptr;
    else
      tmp->parent->right = nullptr;
  }
  delete tmp;
}

template <class T>
void Multiset<T>::EraseLeftBranch(Pointer tmp) {
  if (tmp == root_) {
    root_ = tmp->left;
    root_->parent = nullptr;
  } else {
    tmp->left->parent = tmp->parent;
    if (tmp->parent->value[0] > tmp->value[0])
      tmp->parent->left = tmp->left;
    else
      tmp->parent->right = tmp->left;
  }
  delete tmp;
}

template <class T>
void Multiset<T>::EraseRightBranch(Pointer tmp) {
  if (tmp == root_) {
    root_ = tmp->right;
    root_->parent = nullptr;
  } else {
    tmp->right->parent = tmp->parent;
    if (tmp->parent->value[0] > tmp->value[0])
      tmp->parent->left = tmp->right;
    else
      tmp->parent->right = tmp->right;
  }
  delete tmp;
}

template <class T>
void Multiset<T>::EraseNode(Pointer tmp) {
  Iterator it(tmp, tmp->value.Size());
  --it;
  Iterator p(it->parent, it->parent->value.Size());

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
    if (*it > tmp->parent->value[0]) {
      tmp->parent->right = it.current_;
    } else {
      tmp->parent->left = it.current_;
    }
  }
  delete tmp;
}

template <class T>
typename Multiset<T>::Pair Multiset<T>::Search(ConstReference v) {
  Pointer it = root_, top = it;
  while (it) {
    top = it;
    if (it->value[0] == v) {
      return std::make_pair(Iterator(top, top->value.Size()), true);
    } else if (it->value[0] > v) {
      it = it->left;
    } else {
      it = it->right;
    }
  }
  return std::make_pair(top ? Iterator(top, top->value.Size()) : Iterator(),
                        false);
}

}  // namespace s21

#endif  // SRC_CONTAINERS_EXTRA_S21_MULTISET_H_