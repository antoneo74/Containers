#ifndef SRC_S21_MAP_H_
#define SRC_S21_MAP_H_

#include <initializer_list>
#include <iostream>
//#include <iterator>
#include <limits>
#include"s21_vector.h"
#include <queue>  // не забыть поменять на нашу

namespace s21 {

	template <class Key, class T>
	struct MapNode {
		MapNode* parent = nullptr;
		MapNode* left = nullptr;
		MapNode* right = nullptr;
		std::pair<const Key, T> node_pair;
		MapNode() = default;
		explicit MapNode(const std::pair<const Key, T>& value) : node_pair(value) {};
		MapNode(const Key& key, const T& obj) : node_pair(key, obj) {};
	};

	template <class Key, class T>
	class Map {
	public:
		class MapIterator;
		class MapConstIterator;

		// List Member type
		using key_type = Key;
		using mapped_type = T;
		using value_type = std::pair<const key_type, mapped_type>;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = size_t;
		using node = MapNode< key_type, mapped_type>;
		using pointer = node*;
		using iterator = MapIterator;
		using const_iterator = MapConstIterator;
		using pair = std::pair<iterator, bool>;

		// internal class MapIterator
		class MapIterator {
			friend class Map;
		public:
			MapIterator(pointer obj) : current_(obj) {}
			MapIterator() : current_(nullptr) {}
			MapIterator(const MapIterator& obj) { current_ = obj.current_; }

			MapIterator& operator= (const MapIterator& obj) noexcept {
				current_ = obj.current_;
				return *this;
			}

			MapIterator& operator--() noexcept {
				if (current_->left) {
					current_ = current_->left;
					while (current_->right != nullptr) { current_ = current_->right; }
				}
				else {
					pointer tmp = current_->parent;
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
					while (current_->left != nullptr) { current_ = current_->left; }
				}
				else {
					pointer tmp = current_->parent;
					while (tmp && tmp->node_pair.first < current_->node_pair.first) {
						current_ = tmp;
						tmp = tmp->parent;
					}
					current_ = tmp;
				}
				return *this;
			}

			bool operator!=(const MapIterator& other) const noexcept { return (current_ != other.current_); }

			value_type* operator->() noexcept { return &(current_->node_pair); }

		private:
			pointer current_;
		};

		// internal class MapConstIterator
		class MapConstIterator {
			friend class Map;
		public:
			MapConstIterator(pointer obj) : current_(obj) {}
			MapConstIterator() : current_(nullptr) {}
			MapConstIterator(const MapIterator& obj) { current_ = obj.current_; }

			MapConstIterator& operator= (const MapIterator& obj) noexcept {
				current_ = obj.current_;
				return *this;
			}

			MapConstIterator& operator--() noexcept {
				if (current_->left) {
					current_ = current_->left;
					while (current_->right != nullptr) { current_ = current_->right; }
				}
				else {
					pointer tmp = current_->parent;
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
					while (current_->left != nullptr) { current_ = current_->left; }
				}
				else {
					pointer tmp = current_->parent;
					while (tmp && tmp->node_pair.first < current_->node_pair.first) {
						current_ = tmp;
						tmp = tmp->parent;
					}
					current_ = tmp;
				}
				return *this;
			}

			bool operator!=(const MapConstIterator& other) const noexcept { return (current_ != other.current_); }

			value_type* operator->() noexcept { return current_->node_pair; }

		private:
			const pointer current_;
		};

		// Map Member functions
		Map() = default;
		Map(std::initializer_list<value_type> const& items);
		explicit Map(const Map& m);
		Map(Map&& m) noexcept;
		~Map();
		Map& operator=(Map&& m) noexcept;

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
		pair Insert(const value_type& value);
		pair Insert(const Key& key, const T& obj);
		pair Insert_or_assign(const Key& key, const T& obj);
		void Erase(iterator pos);
		void Swap(Map& other);
		void Merge(Map& other);

		// Map Lookup
		bool Contains(const Key& key);

		// Bonus function
		template <typename... Args>
		Vector<pair> Emplace(Args&&... args);

		// Print
		void PrintMap();

	private:
		pointer root_ = nullptr;
		size_type size_{ 0 };

		// Other functions
		void CopyTree(const Map& other);
		void EraseList(pointer tmp);              //delete element, that has not children
		void EraseLeftBranch(pointer tmp);        //delete element, that has only left branch
		void EraseRightBranch(pointer tmp);       //delete element, that has only right branch
		void EraseNode(pointer tmp);              //delete element, that has two children
		pair  Search(const Key& key);
	};

	// Constructors

	template<class Key, class T>
	Map<Key, T>::Map(std::initializer_list<value_type> const& items) {
		for (auto it : items) {
			Insert(it);
		}
	}

	template<class Key, class T>
	Map<Key, T>::Map(const Map& m) { CopyTree(m); }

	template<class Key, class T>
	Map<Key, T>::Map(Map&& m) noexcept { Swap(m); }

	template<class Key, class T>
	Map<Key, T>::~Map() { Clear(); }

	template<class Key, class T>
	Map<Key, T>& Map<Key, T>::operator=(Map&& m) noexcept {
		Clear();
		Swap(m);
		return  *this;
	}

	template <class Key, class T>
	T& Map<Key, T>::At(const Key& key) {
		pair res = Search(key);
		if (!res.second) {
			throw std::out_of_range("This element is not exists");
		}
		return res.first->second;
	}

	template<class Key, class T>
	T& Map<Key, T>::operator[](const Key& key) {
		pair res = Search(key);
		if (!res.second) {
			auto tmp = Insert(key, T());
			return tmp.first->second;
		}
		return res.first->second;
	}

	// Map Iterators

	template<class Key, class T>
	typename Map<Key, T>::iterator Map<Key, T>::Begin() {
		if (!root_) {
			return iterator();
		}
		else {
			iterator begin(root_);
			while (begin.current_->left) {
				begin = begin.current_->left;
			}
			return begin;
		}
	}

	template<class Key, class T>
	typename Map<Key, T>::iterator Map<Key, T>::End() { return iterator(); }


	// Map Capacity

	template<class Key, class T>
	bool Map<Key, T>::Empty() const { return root_ == nullptr; }

	template<class Key, class T>
	typename Map<Key, T>::size_type Map<Key, T>::Size() { return size_; }

	template<class Key, class T>
	typename Map<Key, T>::size_type Map<Key, T>::Max_size() { return std::numeric_limits<size_type>::max() / sizeof(node); }

	// Map Modifiers

	template<class Key, class T>
	void Map<Key, T>::Clear() {
		for (iterator i = Begin(); i != End(); ) {
			iterator tmp = i;
			++i;
			Erase(tmp);
		}
	}

	template<class Key, class T>
	std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::Insert(const value_type& value) {
		pointer tmp = new node(value);
		if (!root_) {                   // if set is empty
			root_ = tmp;
		}
		else {
			pair top = Search(value.first);
			if (top.second) {
				delete tmp;
				return std::make_pair(iterator(root_), false);
			}
			else {
				tmp->parent = top.first.current_;
				if (top.first->first > value.first) { top.first.current_->left = tmp; }
				else { top.first.current_->right = tmp; }
			}
		}
		++size_;
		return std::make_pair(iterator(tmp), true);
	}

	template<class Key, class T>
	std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::Insert(const Key& key, const T& obj) {
		return Insert(std::make_pair(key, obj));
	}

	template<class Key, class T>
	std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::Insert_or_assign(const Key& key, const T& obj) {
		pair res = Search(key);
		if (!res.second) { return Insert(key, obj); }
		else {
			res.first->second = obj;
			return std::make_pair(res.first, true);
		}
	}

	template<class Key, class T>
	void Map<Key, T>::Erase(iterator pos) {
		pointer tmp = pos.current_;
		if (tmp) {
			if (!tmp->left && !tmp->right) { EraseList(tmp); }
			else if (tmp->left && !tmp->right) { EraseLeftBranch(tmp); }
			else if (!tmp->left && tmp->right) { EraseRightBranch(tmp); }
			else if (tmp->left && tmp->right) { EraseNode(tmp); }
			delete tmp;
			size_--;
		}
	}

	template<class Key, class T>
	void Map<Key, T>::Swap(Map& other) {
		if (this != &other) {
			std::swap(root_, other.root_);
			std::swap(size_, other.size_);
		}
	}

	template<class Key, class T>
	void Map<Key, T>::Merge(Map& other) {
		for (iterator i = other.Begin(); i != other.End(); ++i) {
			Insert(i.current_->node_pair);
		}
	}

	// Map Lookup

	template<class Key, class T>
	bool Map<Key, T>::Contains(const Key& key) {
		pair  res = Search(key);
		return res.second;
	}

	// Bonus Function

	template<class Key, class T>
	template<typename ...Args>
	Vector<typename Map<Key,T>::pair> Map<Key, T>::Emplace(Args && ...args) { // заменить на наш вектор???
		std::initializer_list<value_type> items{ args... };
		Vector<pair> res;
		
		for (auto it = items.begin(); it != items.end(); ++it) {
			res.Push_back(Insert(*it));
		}
		return res;
	}

	// Other functions

	template<class Key, class T>
	void Map<Key, T>::CopyTree(const Map& other) {
		if (other.root_) {
			std::queue<pointer> tmp;                    // не забыть поменять на нашу queue !!!!!
			tmp.push(other.root_);						// поменять на наш метод
			while (!tmp.empty()) {						// поменять на наш метод
				int n = tmp.size();                     // поменять на наш метод
				for (int i = 0; i < n; i++) {
					pointer curr = tmp.front();         // поменять на нащ метод
					tmp.pop();
					Insert(curr->node_pair);
					if (curr->left)
						tmp.push(curr->left);           // поменять на нащ метод
					if (curr->right)
						tmp.push(curr->right);          // поменять на нащ метод
				}
			}
		}
	}

	template<class Key, class T>
	void Map<Key, T>::PrintMap() {
		for (iterator i = Begin(); i != End(); ++i) {
			std::cout << i->first << "\t" << i->second << "\n";
		}
	}

	template<class Key, class T>
	void Map<Key, T>::EraseList(pointer tmp) {
		if (size_ == 1)	root_ = nullptr;
		else {
			if (tmp->parent->node_pair.first > tmp->node_pair.first) tmp->parent->left = nullptr;
			else tmp->parent->right = nullptr;
		}
	}

	template<class Key, class T>
	void Map<Key, T>::EraseLeftBranch(pointer tmp) {
		if (tmp == root_) {
			root_ = tmp->left;
			root_->parent = nullptr;
		}
		else {
			tmp->left->parent = tmp->parent;
			if (tmp->parent->node_pair.first > tmp->node_pair.first)tmp->parent->left = tmp->left;
			else tmp->parent->right = tmp->left;
			
		}
	}

	template<class Key, class T>
	void Map<Key, T>::EraseRightBranch(pointer tmp) {
		if (tmp == root_) {
			root_ = tmp->right;
			root_->parent = nullptr;
		}
		else {
			tmp->right->parent = tmp->parent;
			if (tmp->parent->node_pair.first > tmp->node_pair.first)tmp->parent->left = tmp->right;
			else tmp->parent->right = tmp->right;
		}
	}

	template<class Key, class T>
	void Map<Key, T>::EraseNode(pointer tmp) {
		iterator it(tmp);
		--it;
		iterator p(it.current_->parent);

		if (it.current_->left) {
			if (it->first > p->first) { p.current_->right = it.current_->left; }
			else { p.current_->left = it.current_->left; }
			it.current_->left->parent = p.current_;
		} else {
			if (it->first > p->first) p.current_->right = nullptr;
			else p.current_->left = nullptr;
		}

		it.current_->left = tmp->left;
		it.current_->right = tmp->right;
		it.current_->parent = tmp->parent;

		if(tmp->left) tmp->left->parent = it.current_;
		if(tmp->right) tmp->right->parent = it.current_;
		if (tmp == root_) root_ = it.current_;
		else {
			if (it->first > tmp->parent->node_pair.first) {
				tmp->parent->right = it.current_;
			}
			else {
				tmp->parent->left = it.current_;
			}
		}
	}

	template<class Key, class T>
	std::pair<typename Map<Key, T>::iterator, bool>  Map<Key, T>::Search(const Key& key) {
		pointer it = root_, top = it;
		while (it) {
			top = it;
			if (it->node_pair.first == key) { return std::make_pair(iterator(top), true); }
			else if (it->node_pair.first > key) { it = it->left; }
			else { it = it->right; }
		}
		return std::make_pair(iterator(top), false);
	}
} // namespace s21

#endif  // SRC_S21_MAP_H_
