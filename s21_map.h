#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>  // не забыть поменять на наш

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
  // List Member type
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;
  using node = MapNode<key_type, mapped_type>;

  // internal class MapIterator
  class MapIterator {
    friend class Map;

   public:
    MapIterator(node* obj) : current_(obj) {}
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
        node* tmp = current_->parent;
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
        node* tmp = current_->parent;
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

    value_type* operator->() noexcept { return &(current_->node_pair); }

   private:
    node* current_;
  };

  // internal class MapConstIterator
  class MapConstIterator {
    friend class Map;

   public:
    MapConstIterator(const node* obj) : current_(obj) {}
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
        node* tmp = current_->parent;
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
        node* tmp = current_->parent;
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

    value_type* operator->() noexcept { return current_->node_pair; }

   private:
    const node* current_;
  };

  using iterator = MapIterator;
  using const_iterator = MapConstIterator;

  // Map Member functions

  Map() = default;
  Map(std::initializer_list<value_type> const& items);
  explicit Map(const Map& m);
  Map(Map&& m);
  ~Map();
  Map& operator=(Map&& m);

  // Map Element access

  T& At(const Key& key);
  T& operator[](const Key& key);

  // Map Iterators

  iterator Begin();
  iterator End();

  // Map Capacity

  bool Empty() const;
  size_type Size();
  size_type Max_size();

  // Map Modifiers

  void Clear();
  std::pair<iterator, bool> Insert(const value_type& value);
  std::pair<iterator, bool> Insert(const Key& key, const T& obj);
  std::pair<iterator, bool> Insert_or_assign(const Key& key, const T& obj);
  void Erase(iterator pos);
  void Swap(Map& other);
  void Merge(Map& other);

  // Map Lookup

  bool Contains(const Key& key);

  // Helpers function
  void InsertRecursive(node* tmp, iterator it, iterator prev, bool left);
  void InsertHelpers(node* tmp);
  void CopyTree(Map& other);
  void PrintMap();
  void EraseList(node* tmp);        // delete element, that has not children
  void EraseLeftBranch(node* tmp);  // delete element, that has only left branch
  void EraseRightBranch(
      node* tmp);             // delete element, that has only right branch
  void EraseNode(node* tmp);  // delete element, that has two children
  iterator Search(const Key& key);

  // Bonus function
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> Emplace(Args&&... args);

 private:
  node* root_ = nullptr;
  size_type size_{0};
};

// Constructors

template <class Key, class T>
Map<Key, T>::Map(std::initializer_list<value_type> const& items) {
  for (auto it = items.begin(); it != items.end(); it++) {
    Insert(*it);
  }
}

template <class Key, class T>
Map<Key, T>::Map(const Map& m) {
  CopyTree(m);
}

template <class Key, class T>
Map<Key, T>::Map(Map&& m) {
  Swap(m);
}

template <class Key, class T>
Map<Key, T>::~Map() {
  if (!Empty()) {
    Clear();
  }
}

template <class Key, class T>
Map<Key, T>& Map<Key, T>::operator=(Map&& m) {
  Clear();
  Swap(m);
  return *this;
}

template <class Key, class T>
T& Map<Key, T>::At(const Key& key) {
  iterator res = Search(key);
  if (!res.current_) {
    throw std::out_of_range("This element is not exists");
  }
  return res->second;
}

template <class Key, class T>
T& Map<Key, T>::operator[](const Key& key) {
  iterator res = Search(key);
  if (!res.current_) {
    auto tmp = Insert(key, T());
    return tmp.first->second;
  }
  return res->second;
}

// Map Iterators

template <class Key, class T>
typename Map<Key, T>::iterator Map<Key, T>::Begin() {
  if (!root_) {
    return iterator();
  } else {
    iterator begin(root_);
    while (begin.current_->left) {
      begin = begin.current_->left;
    }
    return begin;
  }
}

template <class Key, class T>
typename Map<Key, T>::iterator Map<Key, T>::End() {
  return iterator();
}

// Map Capacity

template <class Key, class T>
bool Map<Key, T>::Empty() const {
  return root_ == nullptr;
}

template <class Key, class T>
typename Map<Key, T>::size_type Map<Key, T>::Size() {
  return size_;
}

template <class Key, class T>
typename Map<Key, T>::size_type Map<Key, T>::Max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(node);
}

// Map Modifiers

template <class Key, class T>
void Map<Key, T>::Clear() {
  for (iterator i = Begin(); i != End();) {
    iterator tmp = i;
    ++i;
    Erase(tmp);
  }
}

template <class Key, class T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::Insert(
    const value_type& value) {
  const key_type key = value.first;
  if (!Contains(key)) {
    node* tmp = new node(value);
    InsertHelpers(tmp);
    return std::make_pair(iterator(tmp), true);
  } else {
    return std::make_pair(iterator(root_), false);
  }
}

template <class Key, class T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::Insert(
    const Key& key, const T& obj) {
  if (!Contains(key)) {
    node* tmp = new node(key, obj);
    InsertHelpers(tmp);
    return std::make_pair(iterator(tmp), true);
  } else {
    return std::make_pair(iterator(root_), false);
  }
}

template <class Key, class T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::Insert_or_assign(
    const Key& key, const T& obj) {
  iterator res = Search(key);
  if (!res.current_) {
    node* tmp = new node(key, obj);
    InsertHelpers(tmp);
    return std::make_pair(iterator(tmp), true);
  } else {
    res->second = obj;
    return std::make_pair(res, true);
  }
}

template <class Key, class T>
void Map<Key, T>::Erase(iterator pos) {
  node* tmp = pos.current_;
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
  std::swap(root_, other.root_);
}

template <class Key, class T>
void Map<Key, T>::Merge(Map& other) {
  for (iterator i = other.Begin(); i != other.End(); ++i) {
    Insert(i->node_pair);
  }
}

// Map Lookup

template <class Key, class T>
bool Map<Key, T>::Contains(const Key& key) {
  iterator res = Search(key);
  return !res.current_ ? false : true;
}

// Helpers function

template <class Key, class T>
void Map<Key, T>::InsertRecursive(node* tmp, iterator it, iterator prev,
                                  bool left) {
  if (!it.current_) {
    tmp->parent = prev.current_;
    if (left) {
      prev.current_->left = tmp;
    } else {
      prev.current_->right = tmp;
    }
    size_++;
  } else if (tmp->node_pair.first < it->first) {
    prev = it;
    it = iterator(it.current_->left);
    left = true;
    InsertRecursive(tmp, it, prev, left);
  } else if (tmp->node_pair.first > it->first) {
    prev = it;
    it = iterator(it.current_->right);
    left = false;
    InsertRecursive(tmp, it, prev, left);
  }
}

template <class Key, class T>
void Map<Key, T>::InsertHelpers(node* tmp) {
  if (!root_) {
    root_ = tmp;
    size_++;
  } else {
    iterator it(root_), prev;
    bool left = true;
    InsertRecursive(tmp, it, prev, left);
  }
}

template <class Key, class T>
void Map<Key, T>::CopyTree(Map& other) {
  if (other.root_) {
    std::queue<node*> tmp;  // не забыть поменять на нашу queue !!!!!
    tmp.push(other.root_);  // поменять на наш метод
    while (!tmp.empty())    // поменять на наш метод
    {
      int n = tmp.size();  // поменять на наш метод
      for (int i = 0; i < n; i++) {
        node* curr = tmp.front();  // поменять на наш метод
        tmp.pop();
        Insert(curr->node_pair);
        if (curr->left) tmp.push(curr->left);  // поменять на наш метод
        if (curr->right) tmp.push(curr->right);  // поменять на наш метод
      }
    }
  }
}

template <class Key, class T>
void Map<Key, T>::PrintMap() {
  for (iterator i = Begin(); i != End(); ++i) {
    std::cout << i->first << "\t" << i->second << "\n";
  }
}

template <class Key, class T>
void Map<Key, T>::EraseList(node* tmp) {
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
void Map<Key, T>::EraseLeftBranch(node* tmp) {
  if (tmp == root_) {
    root_ = tmp->left;
    root_->parent = nullptr;
  } else {
    tmp->left->parent = tmp->parent;
    tmp->parent->left = tmp->left;
  }
}

template <class Key, class T>
void Map<Key, T>::EraseRightBranch(node* tmp) {
  if (tmp == root_) {
    root_ = tmp->right;
    root_->parent = nullptr;
  } else {
    tmp->right->parent = tmp->parent;
    tmp->parent->left = tmp->right;
  }
}

template <class Key, class T>
void Map<Key, T>::EraseNode(node* tmp) {
  node* check = tmp;
  if (tmp->left && tmp->right) {
    tmp = tmp->left;
    if (!tmp->left && !tmp->right) {
      check->left = nullptr;
    } else if (tmp->right) {
      while (tmp->right) {
        tmp = tmp->right;
      }
      if (!tmp->left) {
        tmp->parent->right = nullptr;
      } else {
        tmp->left->parent = tmp->parent;
        tmp->parent->right = tmp->left;
      }
    } else {
      check->left = tmp->left;
      tmp->left->parent = check;
    }
    node* new_node = new MapNode<Key, T>(check->node_pair);
    new_node->left = tmp->left;
    new_node->right = tmp->right;
    new_node->parent = tmp->parent;
    tmp->left->parent = new_node;
    tmp->right->parent = new_node;
    delete check;
  }
}

template <class Key, class T>
typename Map<Key, T>::iterator Map<Key, T>::Search(const Key& key) {
  if (!Empty()) {
    if (root_->node_pair.first > key)  // search at left branch of tree
    {
      for (iterator i = Begin(); i != iterator(root_); ++i) {
        if (i->first == key) return i;
      }
    } else  // search at right branch of tree
    {
      for (iterator i = iterator(root_); i != End(); ++i) {
        if (i->first == key) return i;
      }
    }
  }
  return iterator();
}

// Bonus Function

template <class Key, class T>
template <typename... Args>
std::vector<std::pair<typename Map<Key, T>::iterator, bool>>
Map<Key, T>::Emplace(Args&&... args)  // поменять на наш вектор???
{
  std::initializer_list<value_type> items{args...};
  std::vector<std::pair<iterator, bool>> res;
  for (auto it = items.begin(); it != items.end(); ++it) {
    res.push_back(insert(*it));
  }
  return res;
}

}  // namespace s21

#endif  // SRC_S21_MAP_H_
