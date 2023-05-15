#ifndef SRC_S21_SET_H_
#define SRC_S21_SET_H_

#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>  // не забыть поменять на нашу
#include"s21_vector.h"
#include"s21_map.h"
#include"s21_multiset.h"
#include<set>

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
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using size_type = size_t;
		using node = SetNode<T>;
		using pointer = node*;
		using iterator = SetIterator;
		using const_iterator = SetConstIterator;
		using pair = std::pair<iterator, bool>;

		// internal class SetIterator
		class SetIterator {
			friend class Set;
		public:
			SetIterator(pointer obj) : current_(obj) {}
			SetIterator() : current_(nullptr) {}
			SetIterator(const SetIterator& obj) { current_ = obj.current_; }

			SetIterator& operator= (const SetIterator& obj) noexcept {
				current_ = obj.current_;
				return *this;
			}

			SetIterator& operator--() noexcept {
				if (current_->left) {
					current_ = current_->left;
					while (current_->right != nullptr) { current_ = current_->right; }
				} else {
					pointer tmp = current_->parent;
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
					while (current_->left != nullptr) { current_ = current_->left; }
				} else {
					pointer tmp = current_->parent;
					while (tmp && tmp->value < current_->value) {
						current_ = tmp;
						tmp = tmp->parent;
					}
					current_ = tmp;
				}
				return *this;
			}

			bool operator!=(const SetIterator& other) const noexcept { return (current_ != other.current_); }

			reference operator*() noexcept { return current_->value; }

			pointer operator -> () { return current_; }
		private:
			pointer current_;
		};

		// internal class SetConstIterator
		class SetConstIterator {
			friend class Set;
		public:
			SetConstIterator(pointer obj) : current_(obj) {}
			SetConstIterator() : current_(nullptr) {}
			SetConstIterator(const SetConstIterator& obj) { current_ = obj.current_; }

			SetConstIterator& operator= (const SetConstIterator& obj) noexcept {
				current_ = obj.current_;
				return *this;
			}

			SetConstIterator& operator--() noexcept {
				if (current_->left) {
					current_ = current_->left;
					while (current_->right != nullptr) { current_ = current_->right; }
				}
				else {
					pointer tmp = current_->parent;
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
					while (current_->left != nullptr) { current_ = current_->left; }
				}
				else {
					pointer tmp = current_->parent;
					while (tmp && tmp->value < current_->value) {
						current_ = tmp;
						tmp = tmp->parent;
					}
					current_ = tmp;
				}
				return *this;
			}

			bool operator!=(const SetConstIterator& other) const noexcept { return (current_ != other.current_); }

			const_reference operator*() noexcept { return current_->value; }
		private:
			const pointer current_;
		};
		
		// Set Member functions
		Set() = default;
		Set(std::initializer_list<value_type> const& items);
		explicit  Set(const Set& s);
		Set(Set&& s) noexcept;
		~Set();
		Set& operator=(Set&& s) noexcept;

		// Set Iterators
		iterator Begin();
		iterator End();

		// Set Capacity
		bool Empty();
		size_type Size();
		size_type Max_size();

		// Set Modifiers
		void Clear();
		pair Insert(const_reference value);
		void Erase(iterator pos);
		void Swap(Set& other);
		void Merge(Set& other);

		// Set Lookup
		iterator Find(const_reference v);
		bool Contains(const_reference v);

		// Bonus Function
		template <typename... Args>
		Vector<pair> Emplace(Args&&... args);

		// Other functions
		void CopyTree(Set& other);
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

	// Set Member functions	
	
	template<class T>
	Set<T>::Set(std::initializer_list<value_type> const& items) {
		for (auto it : items) {
			Insert(it);
		}
	}
	
	template<class T>
	Set<T>::Set(const Set& s) { CopyTree(s); }

	template<class T>
	Set<T>::Set(Set&& s) noexcept {Swap(s);}

	template<class T>
	Set<T>::~Set() {Clear();}

	template<class T>
	Set<T>& Set<T>::operator=(Set&& s) noexcept {
		Clear();
		Swap(s);
		return *this;
	}

	// Set Iterators

	template<class T>
	typename Set<T>::iterator Set<T>::Begin() {
		if (!root_) {return iterator();}
		else {
			iterator begin(root_);
			while (begin->left) {begin = begin->left;}
			return begin;
		}
	}

	template<class T>
	typename Set<T>::iterator Set<T>::End() {return iterator();}


	// Set Capacity

	template<class T>
	bool Set<T>::Empty() {	return root_ == nullptr; }

	template<class T>
	typename Set<T>::size_type Set<T>::Size() {	return size_; }

	template<class T>
	typename Set<T>::size_type Set<T>::Max_size() { return std::numeric_limits<size_type>::max() / sizeof(node); }


	// Set Modifiers
	template<class T>
	void Set<T>::Clear() {
		for (iterator i = Begin(); i != End(); ) {
			iterator tmp = i;
			++i;
			Erase(tmp);
		}
	}

	template<class T>
	std::pair<typename Set<T>::iterator, bool> Set<T>::Insert(const_reference value) {
		pointer tmp = new node(value);
		if (!root_) {                   // if set is empty
			root_ = tmp;
		}
		else {
			pair top = Search(value);
			if (top.second) {
				delete tmp;
				return std::make_pair(iterator(root_), false);
			}
			else {
				tmp->parent = top.first.current_;
				if (*(top.first) > value) { top.first->left = tmp; }
				else { top.first->right = tmp; }
			}
		}
		++size_;
		return std::make_pair(iterator(tmp), true);
	}

	template<class T>
	void Set<T>::Erase(iterator pos) {
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

	template<class T>
	void Set<T>::Swap(Set& other){
		if (this != &other) {
			std::swap(size_, other.size_);
			std::swap(root_, other.root_);
		}
	}

	template<class T>
	void Set<T>::Merge(Set& other) {
		for (iterator i = other.Begin(); i != other.End(); ++i) {
			Insert(*i);
		}
	}

	template<class T>
	typename Set<T>::iterator Set<T>::Find(const_reference v)
	{
		pair res = Search(v);
		if (res.second) return res.first;
		return iterator();
	}

	template<class T>
	bool Set<T>::Contains(const_reference v) {
		pair  res = Search(v);
		return res.second;
	}

	
	// Bonus Function
	template<class T>
	template<typename ...Args>
	Vector<typename Set<T>::pair> Set<T>::Emplace(Args && ...args) {
		std::initializer_list<value_type> items{ args... };
		Vector<pair> res;
		for (auto it = items.begin(); it != items.end(); ++it) {
			res.Push_back(Insert(*it));
		}
		return res;
	}



	// Other functions
	template<class T>
	void Set<T>::CopyTree(Set& other) {
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
	void Set<T>::EraseList(pointer tmp) {
		if (size_ == 1)	root_ = nullptr;
		else {
			if (tmp->parent->value > tmp->value) tmp->parent->left = nullptr;
			else tmp->parent->right = nullptr;
		}
	}

	template<class T>
	void Set<T>::EraseLeftBranch(pointer tmp) {
		if (tmp == root_) {
			root_ = tmp->left;
			root_->parent = nullptr;
		}
		else {
			tmp->left->parent = tmp->parent;
			if (tmp->parent->value > tmp->value)tmp->parent->left = tmp->left;
			else tmp->parent->right = tmp->left;
		}
	}

	template<class T>
	void Set<T>::EraseRightBranch(pointer tmp) {
		if (tmp == root_) {
			root_ = tmp->right;
			root_->parent = nullptr;
		}
		else {
			tmp->right->parent = tmp->parent;
			if (tmp->parent->value > tmp->value)tmp->parent->left = tmp->right;
			else tmp->parent->right = tmp->right;
		}
	}

	template<class T>
	void Set<T>::EraseNode(pointer tmp) {
		iterator it(tmp);
		--it;
		iterator p(it->parent);

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
			if (*it > tmp->parent->value) {
				tmp->parent->right = it.current_;
			}
			else {
				tmp->parent->left = it.current_;
			}
		}
	}

	template<class T>
	std::pair<typename Set<T>::iterator, bool>  Set<T>::Search(const_reference v) {
		pointer it = root_, top = it;
		while (it) {
			top = it;
			if (it->value == v) { return std::make_pair(iterator(top), true); }
			else if (it->value > v) { it = it->left; }
			else { it = it->right; }
		}
		return std::make_pair(iterator(top), false);
	}

	template<class T>
	void Set<T>::Print()
	{
		for (auto i = Begin(); i != End(); ++i)
		{
			std::cout << *i << "\t";
		}
		std::cout << "\n";
	}

} // namespace s21

#endif  // SRC_S21_SET_H_


int main() {
	//s21::Set<int> b;

	//b.Insert(13);
	//b.Insert(1);
	//b.Insert(24);
	//b.Insert(8);
	//b.Emplace(44);
	//b.Print();
	//std::cout << b.Empty()<< "\n";
	//s21::Set<int> a{ 12,55,24,87,124,24,13 };
	//a.Print();
	//
	//s21::Map<int, int> zzz;
	//zzz.Emplace(std::make_pair(2, 4));

	using iterator = s21::Multiset<int>::iterator;
	s21::Multiset<int> ms{5, 1,7,3,1 };
	iterator it = ms.Begin();
	++it;
	ms.Insert(3);
	ms.Insert(3);
	//std::cout << sss->value
	//ms.Erase(it);
	ms.Emplace(18);
	ms.Print();
	iterator sss = ms.UpperBound(2);
	std::cout << *sss<< "\n";
	//ms.Erase(EqualRange(3));

	/*std::multiset<int> aaa{ 1,3,5,8,9 };
	std::multiset<int>::iterator i = aaa.upper_bound(9);
	std::cout << *i;*/

	return 0;
}