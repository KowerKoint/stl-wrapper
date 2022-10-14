#pragma once
#include <cassert>
#include <iostream>
#include <vector>

template <typename T, typename Allocator = std::allocator<T>>
struct Vector : std::vector<T, Allocator> {
    Vector() noexcept(noexcept(Allocator())) : std::vector<T, Allocator>(Allocator()) {}
    explicit Vector(const Allocator& alloc) noexcept : std::vector<T, Allocator>(alloc) {}
    explicit Vector(size_t count, const Allocator& alloc = Allocator()) : std::vector<T, Allocator>(count, T(), alloc) {}
    Vector(size_t count, const T& value, const Allocator& alloc = Allocator()) : std::vector<T, Allocator>(count, value, alloc) {}
    template <typename InputIt>
    Vector(InputIt first, InputIt last, const Allocator& alloc = Allocator()) : std::vector<T, Allocator>(first, last, alloc) {}
    Vector(const Vector& other) : std::vector<T, Allocator>(other) {}
    Vector(Vector&& other) noexcept : std::vector<T, Allocator>(std::move(other)) {}
    Vector(const Vector& other, const Allocator& alloc) : std::vector<T, Allocator>(other, alloc) {}
    Vector(Vector&& other, const Allocator& alloc) : std::vector<T, Allocator>(std::move(other), alloc) {}
    Vector(std::initializer_list<T> init, const Allocator& alloc = Allocator()) : std::vector<T, Allocator>(init, alloc) {}
    const T& operator[](std::size_t i) const {
        assert(i < this->size());
        return std::vector<T, Allocator>::operator[](i);
    }
    T& operator[](std::size_t i) {
        assert(i < this->size());
        return std::vector<T, Allocator>::operator[](i);
    }
    const T& front() const {
        assert(!this->empty());
        return std::vector<T, Allocator>::front();
    }
    T& front() {
        assert(!this->empty());
        return std::vector<T, Allocator>::front();
    }
    const T& back() const {
        assert(!this->empty());
        return std::vector<T, Allocator>::back();
    }
    T& back() {
        assert(!this->empty());
        return std::vector<T, Allocator>::back();
    }
    friend std::istream& operator>>(std::istream& is, Vector& v) {
        for (auto& x : v) is >> x;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        for (std::size_t i = 0; i < v.size(); ++i) {
            if (i) os << ' ';
            os << v[i];
        }
        return os;
    }
};
namespace std {
    template <typename T, typename Allocator>
    struct hash<Vector<T, Allocator>> {
        std::size_t operator()(const Vector<T, Allocator>& v) const {
            std::size_t seed = 0;
            for (const auto& x : v) seed ^= hash<T>{}(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };
};
