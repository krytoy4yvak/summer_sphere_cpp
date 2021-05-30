#pragma once
#include <iostream>
#include <memory>

template <class T>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    pointer allocate(size_type count) {
        pointer new_data = static_cast<pointer>(malloc(sizeof(value_type) * count));
        if (new_data == nullptr) {
            throw std::bad_alloc();
        }
        return new_data;
    }

    void deallocate(pointer ptr, size_type count) noexcept {
        free(ptr);
    }

    template<typename ... Args>
    void construct(pointer xptr, Args&&... args) {
        new(xptr) T(std::forward<Args>(args)...);
    }

    void destroy(pointer xptr) noexcept {
        xptr->~T();
    }
};

template <class T>
class Iterator
{
public:
    using It = Iterator<T>;

    Iterator(T* data) : values{data} { }

    bool operator==(const It& other) {
        return values == other.values;
    }

    bool operator!=(const It& other) {
        return values != other.values;
    }

    bool operator<(const It& other) {
        return values < other.values;
    }

    bool operator<=(const It& other) {
        return values <= other.values;
    }

    bool operator>(const It& other) {
        return values > other.values;
    }

    bool operator>=(const It& other) {
        return values >= other.values;
    }

    It& operator++() {
        ++values;
        return *this;
    }

    It operator++(int) {
        It old{*this};
        ++values;
        return old;
    }

    It& operator--() {
        --values;
        return *this;
    }

    It operator--(int) {
        It old{*this};
        --values;
        return old;
    }

    It operator+(int shift) const {
        return {values + shift};
    }

    It operator-(int shift) const {
        return {values - shift};
    }

    It& operator+=(int shift) {
        values += shift;
        return *this;
    }

    It& operator-=(int shift) {
        values -= shift;
        return *this;
    }

    T& operator*() {
        return *values;
    }

    const T& operator*() const  {
        return *values;
    }

private:
    T* values;
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using iterator = Iterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using size_type = std::size_t;

    Vector()
        : alloc{}
        , values{alloc.allocate(4)}
        , length{4}
        , size_{0}
    {
    }

    Vector(const Vector<T>& other)
        : alloc{}
        , values{alloc.allocate(other.size_)}
        , size_{0}
        , length{other.size_}
    {
        for (; size_ < other.size_; ++size_) {
            alloc.construct(values + size_, other.values[size_]);
        }
    }

    Vector(Vector<T> && other)
        : alloc{}
        , values{other.values}
        , size_{other.size_}
        , length{other.length}
    {
        other.values = nullptr;
        other.size_ = 0;
        other.length = 0;
    }

    Vector(std::initializer_list<T> l)
        : alloc{}
        , values{alloc.allocate(l.size())}
        , size_{0}
        , length{l.size()}
    {
        for (const T& value : l) {
            alloc.construct(values + size_++, std::move(value));
        }
    }

    ~Vector() {
        for (; size_ > 0;) {
            alloc.destroy(values + --size_);
        }
        alloc.deallocate(values, length);
    }

    Vector& operator=(const Vector& other){
        if (&other == this) {
            return *this;
        }
        T* new_data = alloc.allocate(other.size_);
        for (size_t i = 0; i < other.size_; ++i) {
            alloc.construct(new_data + i, other[i]);
        }
        for (size_t i = 0; i < size_; ++i) {
            alloc.destroy(values + i);
        }
        alloc.deallocate(values, length);
        values = new_data;
        size_ = other.size_;
        length = other.length;
        return *this;
    }

    Vector& operator=(Vector&& other) {
        for (size_t i = 0; i < size_; ++i) {
            alloc.destroy(values + i);
        }
        alloc.deallocate(values, length);
        values = other.values;
        other.values = nullptr;
        size_ = other.size_;
        length = other.length;
        return *this;
    }

    T& operator[](size_type i) {
        return values[i];
    }

    const T& operator[](size_type i) const {
        return values[i];
    }

    void push_back(const T& value) {
        if (size_ >= length) {
            reserve(size_ * 2);
        }
        alloc.construct(values + size_++, value);
    }

    void push_back(T&& value) {
        if (size_ >= length) {
            reserve(size_ * 2);
        }
        alloc.construct(values + size_++, std::move(value));
    }

    void pop_back() {
        alloc.destroy(values + --size_);
    }

    template<class ... Args>
    void emplace_back(Args&& ... args) {
        if (size_ >= length) {
            reserve(size_ * 2);
        }
        alloc.construct(values + size_++, std::forward<Args>(args)...);
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    size_type size() const noexcept {
        return size_;
    }

    size_type capacity() const noexcept {
        return length;
    }

    void clear() noexcept {
        for (; size_ > 0;) {
            alloc.destroy(values + --size_);
        }
    }

    iterator begin() {
        return {values};
    }

    iterator end() {
        return {values + size_};
    }

    reverse_iterator rbegin() {
        return {end()};
    }

    reverse_iterator rend() {
        return {begin()};
    }

    void resize(size_type new_size) {
        if (new_size != size_) {
            resize(new_size, T());
        }
    }

    // don't look on strong exception guarantee, too difficult
    void resize(size_type new_size, const T & value) {
        if (new_size > size_) {
            reserve(new_size);
            for (; size_ < new_size; ++size_) {
                alloc.construct(values + size_, value);
            }
        } else if (new_size < size_) {
            for (; size_ > new_size;) {
                alloc.destroy(values + --size_);
            }
        }
    }

    // try to strong exception guarantee
    void reserve(size_type new_cap) {
        if (new_cap <= length) {
            return;
        }
        T* new_data = alloc.allocate(new_cap);

        // if is not nothrow, standard speaks of undefined behavior
        if constexpr (std::is_nothrow_move_constructible<T>::value
                || !std::is_copy_constructible<T>::value) {
            for (size_type i = 0; i < size_; ++i) {
                alloc.construct(new_data + i, std::move(values[i]));
            }
        } else {
            size_type i;
            try { // try to copy, if error, free data
                for (i = 0; i < size_; ++i) {
                    alloc.construct(new_data + i, values[i]);
                }
            } catch (...) {
                for (; i > 0;) {
                    alloc.destroy(new_data + --i);
                }
                alloc.deallocate(new_data, length);
                throw;
            }

            for (; i > 0;) {
                alloc.destroy(values + --i);
            }
        }

        alloc.deallocate(values, length);
        values = new_data;
        length = new_cap;
    }

private:
    Alloc alloc;
    T* values;
    size_type length;
    size_type size_;
};