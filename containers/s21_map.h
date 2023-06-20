#ifndef SRC_CONTAINERS_S21_Map_H_
#define SRC_CONTAINERS_S21_Map_H_

#include <initializer_list>
#include <limits>

#include "s21_queue.h"
#include "s21_vector.h"

namespace s21 {
template <class Key, class T>
struct MapNode {
  MapNode* parent = nullptr;
  MapNode* left = nullptr;
  MapNode* right = nullptr;
  std::pair<const Key, T> node_pair;
  MapNode() = default;
  explicit MapNode(const std::pair<const Key, T>& value) : node_pair(value){};
  MapNode(const Key& key, const T& obj) : node_pair(key, obj){};
};

template <class Key, class T>
class Map {
 public:
  class MapIterator;
  class MapConstIterator;

  // List Member type
  using KeyType = Key;
  using MappedType = T;
  using ValueType = std::pair<const KeyType, MappedType>;
  using Reference = ValueType&;
  using ConstReference = const ValueType&;
  using SizeType = size_t;
  using Node = MapNode<KeyType, MappedType>;
  using Pointer = Node*;
  using Iterator = MapIterator;
  using ConstIterator = MapConstIterator;
  using Pair = std::pair<Iterator, bool>;

  // internal class MapIterator
  class MapIterator {
    friend class Map;

   public:
    MapIterator(Pointer obj) : current_(obj) {}
    MapIterator() : current_(nullptr) {}
    MapIterator(const MapIterator& obj) { current_ = obj.current_; }

    MapIterator& operator=(const MapIterator& obj) noexcept {
      current_ = obj.current_;
      return *this;
    }

    MapIterator& operator--() noexcept {
      if (current_->left) {
        current_ = current_->left;
        while (current_->right != nullptr) {
          current_ = current_->right;
        }
      } else {
        Pointer tmp = current_->parent;
        while (tmp && tmp->node_pair.first > current_->node_pair.first) {
          current_ = tmp;
          tmp = tmp->parent;
        }
        current_ = tmp;
      }
      return *this;
    }

    MapIterator& operator++() noexcept {
      if (current_->right) {
        current_ = current_->right;
        while (current_->left != nullptr) {
          current_ = current_->left;
        }
      } else {
        Pointer tmp = current_->parent;
        while (tmp && tmp->node_pair.first < current_->node_pair.first) {
          current_ = tmp;
          tmp = tmp->parent;
        }
        current_ = tmp;
      }
      return *this;
    }

    bool operator!=(const MapIterator& other) const noexcept {
      return (current_ != other.current_);
    }

    ValueType* operator->() noexcept { return &(current_->node_pair); }

   private:
    Pointer current_;
  };

  // internal class MapConstIterator
  class MapConstIterator {
    friend class Map;

   public:
    MapConstIterator(Pointer obj) : current_(obj) {}
    MapConstIterator() : current_(nullptr) {}
    MapConstIterator(const MapIterator& obj) { current_ = obj.current_; }

    MapConstIterator& operator=(const MapIterator& obj) noexcept {
      current_ = obj.current_;
      return *this;
    }

    MapConstIterator& operator--() noexcept {
      if (current_->left) {
        current_ = current_->left;
        while (current_->right != nullptr) {
          current_ = current_->right;
        }
      } else {
        Pointer tmp = current_->parent;
        while (tmp && tmp->node_pair.first > current_->node_pair.first) {
          current_ = tmp;
          tmp = tmp->parent;
        }
        current_ = tmp;
      }
      return *this;
    }

    MapConstIterator& operator++() noexcept {
      if (current_->right) {
        current_ = current_->right;
        while (current_->left != nullptr) {
          current_ = current_->left;
        }
      } else {
        Pointer tmp = current_->parent;
        while (tmp && tmp->node_pair.first < current_->node_pair.first) {
          current_ = tmp;
          tmp = tmp->parent;
        }
        current_ = tmp;
      }
      return *this;
    }

    bool operator!=(const MapConstIterator& other) const noexcept {
      return (current_ != other.current_);
    }

    ValueType* operator->() noexcept { return current_->node_pair; }

   private:
    const Pointer current_;
  };

  // Map Member functions
  Map() = default;
  Map(std::initializer_list<ValueType> const& items);
  explicit Map(const Map& m);
  Map(Map&& m) noexcept;
  ~Map();
  Map& operator=(Map&& m) noexcept;

  // Map Element access
  T& At(const Key& key);
  T& operator[](const Key& key);

  // Map Iterators
  Iterator Begin();
  Iterator End();

  // Map Capacity
  bool Empty() const;
  SizeType Size();
  SizeType MaxSize();

  // Map Modifiers
  void Clear();
  Pair Insert(const ValueType& value);
  Pair Insert(const Key& key, const T& obj);
  Pair InsertOrAssign(const Key& key, const T& obj);
  void Erase(Iterator pos);
  void Swap(Map& other);
  void Merge(Map& other);

  // Map Lookup
  bool Contains(const Key& key);

  // Bonus function
  template <typename... Args>
  Vector<Pair> Emplace(Args&&... args);

 private:
  Pointer root_ = nullptr;
  SizeType size_{0};

  // Support functions
  void CopyTree(const Map& other);
  void EraseList(Pointer tmp);  // delete element, that has not children
  void EraseLeftBranch(
      Pointer tmp);  // delete element, that has only left branch
  void EraseRightBranch(
      Pointer tmp);             // delete element, that has only right branch
  void EraseNode(Pointer tmp);  // delete element, that has two children
  Pair Search(const Key& key);
};

// Constructors
template <class Key, class T>
Map<Key, T>::Map(std::initializer_list<ValueType> const& items) {
  for (auto it : items) {
    Insert(it);
  }
}

template <class Key, class T>
Map<Key, T>::Map(const Map& m) {
  CopyTree(m);
}

template <class Key, class T>
Map<Key, T>::Map(Map&& m) noexcept {
  Swap(m);
}

template <class Key, class T>
Map<Key, T>::~Map() {
  Clear();
}

template <class Key, class T>
Map<Key, T>& Map<Key, T>::operator=(Map&& m) noexcept {
  Clear();
  Swap(m);
  return *this;
}

template <class Key, class T>
T& Map<Key, T>::At(const Key& key) {
  Pair res = Search(key);
  if (!res.second) {
    throw std::out_of_range("This element is not exists");
  }
  return res.first->second;
}

template <class Key, class T>
T& Map<Key, T>::operator[](const Key& key) {
  Pair res = Search(key);
  if (!res.second) {
    auto tmp = Insert(key, T());
    return tmp.first->second;
  }
  return res.first->second;
}

// Map Iterators
template <class Key, class T>
typename Map<Key, T>::Iterator Map<Key, T>::Begin() {
  if (!root_) {
    return Iterator();
  } else {
    Iterator begin(root_);
    while (begin.current_->left) {
      begin = begin.current_->left;
    }
    return begin;
  }
}

template <class Key, class T>
typename Map<Key, T>::Iterator Map<Key, T>::End() {
  return Iterator();
}

// Map Capacity
template <class Key, class T>
bool Map<Key, T>::Empty() const {
  return root_ == nullptr;
}

template <class Key, class T>
typename Map<Key, T>::SizeType Map<Key, T>::Size() {
  return size_;
}

template <class Key, class T>
typename Map<Key, T>::SizeType Map<Key, T>::MaxSize() {
  return std::numeric_limits<SizeType>::max() / sizeof(Node);
}

// Map Modifiers
template <class Key, class T>
void Map<Key, T>::Clear() {
  for (Iterator i = Begin(); i != End();) {
    Iterator tmp = i;
    ++i;
    Erase(tmp);
  }
}

template <class Key, class T>
std::pair<typename Map<Key, T>::Iterator, bool> Map<Key, T>::Insert(
    const ValueType& value) {
  Pointer tmp = new Node(value);
  if (!root_) {  // if set is empty
    root_ = tmp;
  } else {
    Pair top = Search(value.first);
    if (top.second) {
      delete tmp;
      return std::make_pair(Iterator(root_), false);
    } else {
      tmp->parent = top.first.current_;
      if (top.first->first > value.first) {
        top.first.current_->left = tmp;
      } else {
        top.first.current_->right = tmp;
      }
    }
  }
  ++size_;
  return std::make_pair(Iterator(tmp), true);
}

template <class Key, class T>
std::pair<typename Map<Key, T>::Iterator, bool> Map<Key, T>::Insert(
    const Key& key, const T& obj) {
  return Insert(std::make_pair(key, obj));
}

template <class Key, class T>
std::pair<typename Map<Key, T>::Iterator, bool> Map<Key, T>::InsertOrAssign(
    const Key& key, const T& obj) {
  Pair res = Search(key);
  if (!res.second) {
    return Insert(key, obj);
  } else {
    res.first->second = obj;
    return std::make_pair(res.first, true);
  }
}

template <class Key, class T>
void Map<Key, T>::Erase(Iterator pos) {
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

template <class Key, class T>
void Map<Key, T>::Swap(Map& other) {
  if (this != &other) {
    std::swap(root_, other.root_);
    std::swap(size_, other.size_);
  }
}

template <class Key, class T>
void Map<Key, T>::Merge(Map& other) {
  for (Iterator i = other.Begin(); i != other.End(); ++i) {
    Insert(i.current_->node_pair);
  }
}

// Map Lookup
template <class Key, class T>
bool Map<Key, T>::Contains(const Key& key) {
  Pair res = Search(key);
  return res.second;
}

// Bonus Function
template <class Key, class T>
template <typename... Args>
Vector<typename Map<Key, T>::Pair> Map<Key, T>::Emplace(Args&&... args) {
  std::initializer_list<ValueType> items{args...};
  Vector<Pair> res;

  for (auto it = items.begin(); it != items.end(); ++it) {
    res.PushBack(Insert(*it));
  }
  return res;
}

// Other functions
template <class Key, class T>
void Map<Key, T>::CopyTree(const Map& other) {
  if (other.root_) {
    s21::Queue<Pointer> tmp;
    tmp.Push(other.root_);
    while (!tmp.Empty()) {
      int n = tmp.Size();
      for (int i = 0; i < n; i++) {
        Pointer curr = tmp.Front();
        tmp.Pop();
        Insert(curr->node_pair);
        if (curr->left) tmp.Push(curr->left);
        if (curr->right) tmp.Push(curr->right);
      }
    }
  }
}

template <class Key, class T>
void Map<Key, T>::EraseList(Pointer tmp) {
  if (size_ == 1)
    root_ = nullptr;
  else {
    if (tmp->parent->node_pair.first > tmp->node_pair.first)
      tmp->parent->left = nullptr;
    else
      tmp->parent->right = nullptr;
  }
}

template <class Key, class T>
void Map<Key, T>::EraseLeftBranch(Pointer tmp) {
  if (tmp == root_) {
    root_ = tmp->left;
    root_->parent = nullptr;
  } else {
    tmp->left->parent = tmp->parent;
    if (tmp->parent->node_pair.first > tmp->node_pair.first)
      tmp->parent->left = tmp->left;
    else
      tmp->parent->right = tmp->left;
  }
}

template <class Key, class T>
void Map<Key, T>::EraseRightBranch(Pointer tmp) {
  if (tmp == root_) {
    root_ = tmp->right;
    root_->parent = nullptr;
  } else {
    tmp->right->parent = tmp->parent;
    if (tmp->parent->node_pair.first > tmp->node_pair.first)
      tmp->parent->left = tmp->right;
    else
      tmp->parent->right = tmp->right;
  }
}

template <class Key, class T>
void Map<Key, T>::EraseNode(Pointer tmp) {
  Iterator it(tmp);
  --it;
  Iterator p(it.current_->parent);

  if (it.current_->left) {
    if (it->first > p->first) {
      p.current_->right = it.current_->left;
    } else {
      p.current_->left = it.current_->left;
    }
    it.current_->left->parent = p.current_;
  } else {
    if (it->first > p->first)
      p.current_->right = nullptr;
    else
      p.current_->left = nullptr;
  }

  it.current_->left = tmp->left;
  it.current_->right = tmp->right;
  it.current_->parent = tmp->parent;

  if (tmp->left) tmp->left->parent = it.current_;
  if (tmp->right) tmp->right->parent = it.current_;
  if (tmp == root_)
    root_ = it.current_;
  else {
    if (it->first > tmp->parent->node_pair.first) {
      tmp->parent->right = it.current_;
    } else {
      tmp->parent->left = it.current_;
    }
  }
}

template <class Key, class T>
std::pair<typename Map<Key, T>::Iterator, bool> Map<Key, T>::Search(
    const Key& key) {
  Pointer it = root_, top = it;
  while (it) {
    top = it;
    if (it->node_pair.first == key) {
      return std::make_pair(Iterator(top), true);
    } else if (it->node_pair.first > key) {
      it = it->left;
    } else {
      it = it->right;
    }
  }
  return std::make_pair(Iterator(top), false);
}
}  // namespace s21

#endif  // SRC_CONTAINERS_S21_Map_H_
