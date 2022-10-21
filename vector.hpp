#pragma once
#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
struct Vector : std::vector<T> {
    Vector() noexcept : std::vector<T>() {}
    explicit Vector(size_t count) : std::vector<T>(count, T()) {}
    Vector(size_t count, const T& value) : std::vector<T>(count, value) {}
    template <typename InputIt>
    Vector(InputIt first, InputIt last) : std::vector<T>(first, last) {}
    Vector(const std::vector<T>& other) : std::vector<T>(other) {}
    Vector(std::vector<T>&& other) noexcept : std::vector<T>(std::move(other)) {}
    Vector(std::initializer_list<T> init) : std::vector<T>(init) {}
    const T& operator[](size_t i) const {
        assert(i < this->size());
        return std::vector<T>::operator[](i);
    }
    T& operator[](size_t i) {
        assert(i < this->size());
        return std::vector<T>::operator[](i);
    }
    const T& front() const {
        assert(!this->empty());
        return std::vector<T>::front();
    }
    T& front() {
        assert(!this->empty());
        return std::vector<T>::front();
    }
    const T& back() const {
        assert(!this->empty());
        return std::vector<T>::back();
    }
    T& back() {
        assert(!this->empty());
        return std::vector<T>::back();
    }
    friend std::istream& operator>>(std::istream& is, Vector& v) {
        for (auto& x : v) is >> x;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        for (size_t i = 0; i < v.size(); ++i) {
            if (i) os << ' ';
            os << v[i];
        }
        return os;
    }
};
namespace std {
    template <typename T>
    struct hash<Vector<T>> {
        size_t operator()(const Vector<T>& v) const {
            size_t seed = 0;
            for (const auto& x : v) seed ^= hash<T>{}(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };
};
