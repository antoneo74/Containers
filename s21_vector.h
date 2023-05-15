#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

namespace s21 {
    template <class T>
    class Vector {
    public:
        // Vector Member type
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using const_reference = const T&;
        using size_type = size_t;

        // internal class VectorIterator
        class VectorIterator {
            friend class Vector;

        public:
            VectorIterator() = default;

            VectorIterator(const VectorIterator& it) : current_(it.current_) {}

            VectorIterator(const pointer v) : current_(v) {}

            VectorIterator& operator=(const VectorIterator& it) noexcept {
                current_ = it.current_;
                return *this;
            }

            VectorIterator& operator--() noexcept {
                --current_;
                return *this;
            }

            VectorIterator& operator++() noexcept {
                ++current_;
                return *this;
            }

            VectorIterator& operator+(size_type n) noexcept {
                while (n--) {
                    ++current_;
                }
                return *this;
            }

            bool operator!=(const VectorIterator& other) const noexcept {
                return (current_ != other.current_);
            }

            reference operator*() noexcept { return *current_; }

        private:
            pointer current_ = nullptr;
        };

        // internal class VectorConstIterator
        class VectorConstIterator {
            friend class Vector;

        public:
            VectorConstIterator() = default;

            VectorConstIterator(const VectorConstIterator& it)
                : current_(it.current_) {}

            VectorConstIterator(const pointer v) : current_(v) {}

            VectorConstIterator& operator=(const VectorConstIterator& it) noexcept {
                current_ = it.current_;
                return *this;
            }

            VectorConstIterator& operator--() noexcept {
                --current_;
                return *this;
            }

            VectorConstIterator& operator++() noexcept {
                ++current_;
                return *this;
            }

            VectorConstIterator& operator+(size_type n) noexcept {
                while (n--) {
                    ++current_;
                }
                return *this;
            }

            bool operator!=(const VectorConstIterator& other) const noexcept {
                return (current_ != other.current_);
            }

            reference operator*() noexcept { return *current_; }

        private:
            pointer current_ = nullptr;
        };

        using iterator = VectorIterator;
        using const_iterator = VectorConstIterator;

        // Vector Member functions
        Vector() = default;
        explicit Vector(size_type n);
        Vector(std::initializer_list<value_type> const& items);
        Vector(const Vector& v);
        Vector(Vector&& v) noexcept;
        ~Vector();
        Vector<T>& operator=(Vector&& v) noexcept;

        // Vector Element access
        reference At(size_type pos);
        reference operator[](size_type pos);
        const_reference Front();
        const_reference Back();
        T* Data();

        // Vector Iterators
        iterator Begin();
        iterator End();
        const_iterator Cbegin();
        const_iterator Cend();

        // Vector Capacity
        bool Empty();
        size_type Size();
        size_type Max_size();
        void Reserve(size_type size);
        size_type Capacity();
        void Shrink_to_fit();

        // Vector Modifiers
        void Clear();
        iterator Insert(iterator pos, const_reference value);
        void Erase(iterator pos);
        void Push_back(const_reference value);
        void Pop_back();
        void Swap(Vector& other);

        // Bonus functions
        template <typename... Args>
        iterator Emplace(const_iterator pos, Args&&... args);
        template <typename... Args>
        void EmplaceBack(Args&&... args);

        // Other functions
        void Resize();
        void Print();
        void MoveData();

    private:
        size_type size_ = 0;
        size_type capacity_ = 0;
        pointer vector_ = nullptr;
    };

    // Vector Member functions

    template <class T>
    Vector<T>::Vector(size_type n) : size_(n), capacity_(n) {
        vector_ = capacity_ ? new value_type[capacity_] : nullptr;
    }

    template <class T>
    Vector<T>::Vector(std::initializer_list<value_type> const& items) {
        size_ = items.size();
        capacity_ = items.size();
        vector_ = new value_type[capacity_];
        std::copy(items.begin(), items.end(), vector_);
    }

    template <class T>
    Vector<T>::Vector(const Vector& v) {
        size_ = v.size_;
        capacity_ = v.capacity_;
        if (capacity_) vector_ = new value_type[capacity_];
        std::copy(v.vector_, v.vector_ + v.size_, vector_);
    }

    template <class T>
    Vector<T>::Vector(Vector&& v) noexcept {
        Swap(v);
    }

    template <class T>
    Vector<T>::~Vector() {
        Clear();
    }

    template <class T>
    Vector<T>& Vector<T>::operator=(Vector&& v) noexcept {
        Clear();
        Swap(v);
        return *this;
    }

    // Vector Element access

    template <class T>
    typename Vector<T>::reference Vector<T>::At(size_type pos) {
        if (pos >= size_) throw std::out_of_range("This index is out of range");
        return vector_[pos];
    }

    template <class T>
    typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
        return vector_[pos];
    }

    template <class T>
    typename Vector<T>::const_reference Vector<T>::Front() {
        return vector_[0];
    }

    template <class T>
    typename Vector<T>::const_reference Vector<T>::Back() {
        return vector_[size_ - 1];
    }

    template <class T>
    T* Vector<T>::Data() {
        return vector_;
    }

    // Vector Iterators

    template <class T>
    typename Vector<T>::iterator Vector<T>::Begin() {
        return iterator(&vector_[0]);
    }

    template <class T>
    typename Vector<T>::iterator Vector<T>::End() {
        return iterator(&vector_[size_]);
    }

    template <class T>
    typename Vector<T>::const_iterator Vector<T>::Cbegin() {
        return const_iterator(&vector_[0]);
    }

    template <class T>
    typename Vector<T>::const_iterator Vector<T>::Cend() {
        return iterator(&vector_[size_]);
    }

    // Vector Capacity

    template <class T>
    bool Vector<T>::Empty() {
        return size_ == 0;
    }

    template <class T>
    typename Vector<T>::size_type Vector<T>::Size() {
        return size_;
    }

    template <class T>
    typename Vector<T>::size_type Vector<T>::Max_size() {
        return std::numeric_limits<size_type>::max() / sizeof(vector_);
    }

    template <class T>
    void Vector<T>::Reserve(size_type size) {
        if (size <= capacity_) return;
        capacity_ = size;
        MoveData();
    }

    template <class T>
    typename Vector<T>::size_type Vector<T>::Capacity() {
        return capacity_;
    }

    template <class T>
    void Vector<T>::Shrink_to_fit() {
        capacity_ = size_;
        MoveData();
    }

    // Vector Modifiers

    template <class T>
    void Vector<T>::Clear() {
        size_ = capacity_ = 0;
        delete[] vector_;
    }

    template <class T>
    typename Vector<T>::iterator Vector<T>::Insert(iterator pos,
        const_reference value) {
        size_type index = pos.current_ - Begin().current_;
        if (pos.current_ - End().current_ > 0)
            throw std::out_of_range("This index is out of range");
        if (size_ == capacity_) {
            Resize();
            pos = iterator(&vector_[index]);
        }
        for (auto i = --End(), j = End(); j != pos; --i, --j) {
            *j = *i;
        }
        *pos = value;
        ++size_;
        return pos;
    }

    template <class T>
    void Vector<T>::Erase(iterator pos) {
        if (pos.current_ - End().current_ >= 0)
            throw std::out_of_range("This index is out of range");
        for (iterator i = pos, j = (++pos); j != End(); ++i, ++j) {
            *i = *j;
        }
        --size_;
    }

    template <class T>
    void Vector<T>::Push_back(const_reference value) {
        if (size_ == capacity_) Resize();
        vector_[size_++] = value;
    }

    template <class T>
    void Vector<T>::Pop_back() {
        --size_;
    }

    template <class T>
    void Vector<T>::Swap(Vector& other) {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(vector_, other.vector_);
    }

    // Bonus functions

    template <class T>
    template <typename... Args>
    typename Vector<T>::iterator Vector<T>::Emplace(const_iterator pos,
        Args&&... args) {
        size_type index = pos.current_ - Begin().current_;
        iterator result(&vector_[index]);
        if (result.current_ - End().current_ > 0)
            throw std::out_of_range("This index is out of range");
        if (size_ == capacity_) {
            Resize();
            result = iterator(&vector_[index]);
        }
        for (auto i = --End(), j = End(); j != result; --i, --j) {
            *j = *i;
        }
        *result = T(std::forward<Args>(args)...);
        ++size_;
        return result;
    }

    template <class T>
    template <typename... Args>
    void Vector<T>::EmplaceBack(Args&&... args) {
        if (size_ == capacity_) Resize();
        *End() = T(std::forward<Args>(args)...);
        ++size_;
    }

    // Other functions

    template <class T>
    void Vector<T>::Resize() {
        capacity_ = capacity_ ? capacity_ * 2 : 1;
        MoveData();
    }

    template <class T>
    void Vector<T>::Print() {
        for (auto it = Begin(); it != End(); ++it) {
            std::cout << *it << "\t";
        }
        std::cout << "\n";
    }

    template <class T>
    void Vector<T>::MoveData() {
        pointer tmp = vector_;
        vector_ = new value_type[capacity_];
        std::copy(tmp, tmp + size_, vector_);
        delete[] tmp;
    }

}  // namespace s21

#endif  // SRC_S21_VECTOR_H_
