#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_

#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>  // не забыть поменять на нашу
#include"s21_vector.h"
#include"s21_map.h"

namespace s21 {
	template <class T>
	struct MSetNode {
		MSetNode* parent = nullptr;
		MSetNode* left = nullptr;
		MSetNode* right = nullptr;
		Vector<T> value;
		MSetNode() = default;
		explicit MSetNode(const T& v) {
			value.Push_back(v);
		}
	};

	template <class T>
	class Multiset {
	public:
		class MultisetIterator;
		class MultisetConstIterator;

		// Set Member type
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = size_t;
		using node = MSetNode<T>;
		using pointer = node*;
		using iterator = MultisetIterator;
		using const_iterator = MultisetConstIterator;
		using pair = std::pair<iterator, bool>;

		// internal class MultisetIterator
		class MultisetIterator {
			friend class Multiset;
		public:
			MultisetIterator(pointer obj, size_type s) : current_(obj), s_(s) {}
			MultisetIterator() : current_(nullptr), s_(0) {}
			MultisetIterator(const MultisetIterator& obj) : current_(obj.current_), s_(obj.s_) {}

			MultisetIterator& operator= (const MultisetIterator& obj) noexcept {
				current_ = obj.current_;
				s_ = obj.s_;
				return *this;
			}

			MultisetIterator& operator--() noexcept {
				if (s_ > 1) {
					--s_;
				}
				else {
					if (current_->left) {
						current_ = current_->left;
						while (current_->right != nullptr) { current_ = current_->right; }
					}
					else {
						pointer tmp = current_->parent;
						while (tmp && tmp->value[0] > current_->value[0]) {
							current_ = tmp;
							tmp = tmp->parent;
						}
						current_ = tmp;
					}
					if(current_)
						s_ = current_->value.Size();
				}
				return *this;
			}

			MultisetIterator& operator++() noexcept {
				if (s_ > 1) {
					--s_;
				}
				else {
					if (current_->right) {
						current_ = current_->right;
						while (current_->left != nullptr) { current_ = current_->left; }
					}
					else {
						pointer tmp = current_->parent;
						while (tmp && tmp->value[0] < current_->value[0]) {
							current_ = tmp;
							tmp = tmp->parent;
						}
						current_ = tmp;
					}
					if(current_)
						s_ = current_->value.Size();
				}
				return *this;
			}

			bool operator!=(const MultisetIterator& other) const noexcept { return (current_ != other.current_); }

			const_reference operator*() noexcept { return current_->value[0]; }

			pointer operator -> () { return current_; }
		private:
			pointer current_;
			size_type s_;
		};

		// internal class MultisetConstIterator
		class MultisetConstIterator {
			friend class Multiset;
		public:
			MultisetConstIterator(pointer obj, size_type s) : current_(obj), s_(s) {}
			MultisetConstIterator() : current_(nullptr), s_(0) {}
			MultisetConstIterator(const MultisetConstIterator& obj) : current_(obj.current_), s_(obj.s_) {}

			MultisetConstIterator& operator= (const MultisetConstIterator& obj) noexcept {
				current_ = obj.current_;
				s_ = obj.s_;
				return *this;
			}

			MultisetConstIterator& operator--() noexcept {
				if (s_ > 1) {
					--s_;
				}
				else {
					if (current_->left) {
						current_ = current_->left;
						while (current_->right != nullptr) { current_ = current_->right; }
					}
					else {
						pointer tmp = current_->parent;
						while (tmp && tmp->value[0] > current_->value[0]) {
							current_ = tmp;
							tmp = tmp->parent;
						}
						current_ = tmp;
					}
					if (current_)
						s_ = current_->value.Size();
				}
				return *this;
			}

			MultisetConstIterator& operator++() noexcept {
				if (s_ > 1) {
					--s_;
				}
				else {
					if (current_->right) {
						current_ = current_->right;
						while (current_->left != nullptr) { current_ = current_->left; }
					}
					else {
						pointer tmp = current_->parent;
						while (tmp && tmp->value[0] < current_->value[0]) {
							current_ = tmp;
							tmp = tmp->parent;
						}
						current_ = tmp;
					}
					if (current_)
						s_ = current_->value.Size();
				}
				return *this;
			}

			bool operator!=(const MultisetConstIterator& other) const noexcept { return (current_ != other.current_); }

			const_reference operator*() noexcept { return current_->value[0]; }

			const pointer operator -> () { return current_; }
		private:
			const pointer current_;
			size_type s_;
		};

		// Multiset Member functions
		Multiset() = default;
		Multiset(std::initializer_list<value_type> const& items);
		explicit  Multiset(const Multiset& s);
		Multiset(Multiset&& s) noexcept;
		~Multiset();
		Multiset& operator=(Multiset&& s) noexcept;

		// Multiset Iterators
		iterator Begin();
		iterator End();

		// Multiset Capacity
		bool Empty();
		size_type Size();
		size_type Max_size();

		// Multiset Modifiers
		void Clear();
		iterator Insert(const_reference value);
		void Erase(iterator pos);
		void Swap(Multiset& other);
		void Merge(Multiset& other);

		// Multiset Lookup
		size_type Count(const_reference v);
		iterator Find(const_reference v);
		bool Contains(const_reference v);
		std::pair<iterator, iterator> EqualRange(const_reference v);
		iterator LowerBound(const_reference v);
		iterator UpperBound(const_reference v);


		// Bonus Function
		template <typename... Args>
		Vector<pair> Emplace(Args&&... args);

		// Other functions
		void CopyTree(Multiset& other);
		void EraseList(pointer tmp);
		void EraseLeftBranch(pointer tmp);
		void EraseRightBranch(pointer tmp);
		void EraseNode(pointer tmp);
		std::pair<iterator, bool> Search(const_reference v);
		void Print();

	private:
		pointer root_ = nullptr;
		size_type size_{ 0 };
	};

	// Multiset Member functions	

	template<class T>
	Multiset<T>::Multiset(std::initializer_list<value_type> const& items) {
		for (auto it : items) {
			Insert(it);
		}
	}

	template<class T>
	Multiset<T>::Multiset(const Multiset& s) { CopyTree(s); }

	template<class T>
	Multiset<T>::Multiset(Multiset&& s) noexcept { Swap(s); }

	template<class T>
	Multiset<T>::~Multiset() { Clear(); }

	template<class T>
	Multiset<T>& Multiset<T>::operator=(Multiset&& s) noexcept {
		Clear();
		Swap(s);
		return *this;
	}

	// Multiset Iterators

	template<class T>
	typename Multiset<T>::iterator Multiset<T>::Begin() {
		if (!root_) { return iterator(); }
		else {
			pointer begin = root_;
			while (begin->left) { begin = begin->left; }
			return iterator(begin, begin->value.Size());
		}
	}

	template<class T>
	typename Multiset<T>::iterator Multiset<T>::End() { return iterator(); }


	// Multiset Capacity

	template<class T>
	bool Multiset<T>::Empty() { return root_ == nullptr; }

	template<class T>
	typename Multiset<T>::size_type Multiset<T>::Size() { return size_; }

	template<class T>
	typename Multiset<T>::size_type Multiset<T>::Max_size() { return std::numeric_limits<size_type>::max() / sizeof(node); }


	// Multiset Modifiers
	template<class T>
	void Multiset<T>::Clear() {
		for (iterator i = Begin(); i != End(); ) {
			iterator tmp = i;
			++i;
			Erase(tmp);
		}
	}

	template<class T>
	typename Multiset<T>::iterator Multiset<T>::Insert(const_reference value) {
		pointer tmp = new node(value);
		if (!root_) {                   // if set is empty
			root_ = tmp;
		}
		else {
			pair top = Search(value);
			if (top.second) {
				top.first->value.Push_back(value);
				++size_;
				++(top.first.s_);
				return top.first;        
			}
			else {
				tmp->parent = top.first.current_;
				if (*(top.first) > value) { top.first->left = tmp; }
				else { top.first->right = tmp; }
			}
		}
		++size_;
		return iterator(tmp, tmp->value.Size());
	}

	template<class T>
	void Multiset<T>::Erase(iterator pos) {
		if (pos->value.Size() > 1) {
			pos->value.Pop_back();
			--size_;
		}
		else {
			pointer tmp = pos.current_;
			if (tmp) {
				if (!tmp->left && !tmp->right) { EraseList(tmp); }
				else if (tmp->left && !tmp->right) { EraseLeftBranch(tmp); }
				else if (!tmp->left && tmp->right) { EraseRightBranch(tmp); }
				else if (tmp->left && tmp->right) { EraseNode(tmp); }
				delete tmp;
				--size_;
			}
		}
	}

	template<class T>
	void Multiset<T>::Swap(Multiset& other) {
		if (this != &other) {
			std::swap(size_, other.size_);
			std::swap(root_, other.root_);
		}
	}

	template<class T>
	void Multiset<T>::Merge(Multiset& other) {
		for (iterator i = other.Begin(); i != other.End(); ++i) {
			Insert(*i);
		}
	}

	template<class T>
	typename Multiset<T>::size_type Multiset<T>::Count(const_reference v)
	{
		pair res = Search(v);
		return (res.second? res.first->value.Size():0);
	}

	template<class T>
	typename Multiset<T>::iterator Multiset<T>::Find(const_reference v)
	{
		pair res = Search(v);
		if (res.second) return res.first;
		return iterator();
	}

	template<class T>
	bool Multiset<T>::Contains(const_reference v) {
		pair  res = Search(v);
		return res.second;
	}

	template<class T>
	std::pair<typename Multiset<T>::iterator, typename Multiset<T>::iterator> Multiset<T>::EqualRange(const_reference v)
	{
		return std::make_pair(LowerBound(v), UpperBound(v));
	}

	template<class T>
	typename Multiset<T>::iterator Multiset<T>::LowerBound(const_reference v) {
		pair  res = Search(v);
		if(res.second) return res.first;
		else { return UpperBound(v); }
	}

	template<class T>
	typename Multiset<T>::iterator Multiset<T>::UpperBound(const_reference v) {
		iterator it;
		for (it = Begin(); it != End() && *it <= v; ++it) {}
		return it;
	}

	
	
	// Bonus Function

	template<class T>
	template<typename ...Args>
	Vector<typename Multiset<T>::pair> Multiset<T>::Emplace(Args && ...args) {
		std::initializer_list<value_type> items{ args... };
		Vector<pair> res;
		for (auto it = items.begin(); it != items.end(); ++it) {
			res.Push_back(std::make_pair(Insert(*it), true));
		}
		return res;
	}



	// Other functions
	template<class T>
	void Multiset<T>::CopyTree(Multiset& other) {
		if (other.root_) {
			std::queue<pointer> tmp;                         // не забыть поменять на нашу queue !!!!!
			tmp.push(other.root_);						// поменять на наш метод
			while (!tmp.empty()) {						// поменять на наш метод
				int n = tmp.size();                  // поменять на наш метод
				for (int i = 0; i < n; i++) {
					pointer curr = tmp.front();        // поменять на нащ метод
					tmp.pop();
					Insert(curr->value);
					if (curr->left)
						tmp.push(curr->left);        // поменять на нащ метод
					if (curr->right)
						tmp.push(curr->right);       // поменять на нащ метод
				}
			}
		}
	}

	template<class T>
	void Multiset<T>::EraseList(pointer tmp) {
		if (size_ == 1)	root_ = nullptr;
		else {
			if (tmp->parent->value[0] > tmp->value[0]) tmp->parent->left = nullptr;
			else tmp->parent->right = nullptr;
		}
	}

	template<class T>
	void Multiset<T>::EraseLeftBranch(pointer tmp) {
		if (tmp == root_) {
			root_ = tmp->left;
			root_->parent = nullptr;
		}
		else {
			tmp->left->parent = tmp->parent;
			if (tmp->parent->value[0] > tmp->value[0])tmp->parent->left = tmp->left;
			else tmp->parent->right = tmp->left;
		}
	}

	template<class T>
	void Multiset<T>::EraseRightBranch(pointer tmp) {
		if (tmp == root_) {
			root_ = tmp->right;
			root_->parent = nullptr;
		}
		else {
			tmp->right->parent = tmp->parent;
			if (tmp->parent->value[0] > tmp->value[0])tmp->parent->left = tmp->right;
			else tmp->parent->right = tmp->right;
		}
	}

	template<class T>
	void Multiset<T>::EraseNode(pointer tmp) {
		iterator it(tmp, tmp->value.Size());
		--it;
		iterator p(it->parent, it->parent->value.Size());

		if (it->left) {
			if (*it > *p) { p->right = it->left; }
			else { p->left = it->left; }
			it->left->parent = p.current_;
		}
		else {
			if (*it > *p) p->right = nullptr;
			else p->left = nullptr;
		}

		it->left = tmp->left;
		it->right = tmp->right;
		it->parent = tmp->parent;

		if (tmp->left) tmp->left->parent = it.current_;
		if (tmp->right) tmp->right->parent = it.current_;
		if (tmp == root_) root_ = it.current_;
		else {
			if (*it > tmp->parent->value[0]) {
				tmp->parent->right = it.current_;
			}
			else {
				tmp->parent->left = it.current_;
			}
		}
	}

	template<class T>
	std::pair<typename Multiset<T>::iterator, bool>  Multiset<T>::Search(const_reference v) {
		pointer it = root_, top = it;
		while (it) {
			top = it;
			if (it->value[0] == v) { return std::make_pair(iterator(top, top->value.Size()), true); }
			else if (it->value[0] > v) { it = it->left; }
			else { it = it->right; }
		}
		return std::make_pair(top?iterator(top, top->value.Size()):iterator(), false);
	}

	template<class T>
	void Multiset<T>::Print()
	{
		for (iterator i = Begin(); i != End(); ++i)
		{
			
				std::cout << *i << "\t";

			
		}
		std::cout << "\n";
	}

} // namespace s21

#endif  // SRC_S21_MULTISET_H_