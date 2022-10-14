#pragma once
#include <iostream>
#include <utility>

template <typename T1, typename T2>
struct Pair : public std::pair<T1, T2> {
    explicit constexpr Pair() : std::pair<T1, T2>() {}
    explicit constexpr Pair(const T1& first, const T2& second) : std::pair<T1, T2>(first, second) {}
    template <typename U1, typename U2>
    explicit constexpr Pair(U1&& first, U2&& second) : std::pair<T1, T2>(std::forward<U1>(first), std::forward<U2>(second)) {}
    template <typename U1, typename U2>
    explicit constexpr Pair(const std::pair<U1, U2>& other) : std::pair<T1, T2>(other) {}
    template <typename U1, typename U2>
    explicit constexpr Pair(std::pair<U1, U2>&& other) : std::pair<T1, T2>(std::move(other)) {}
    template <typename... Args1, typename... Args2>
    explicit constexpr Pair(std::piecewise_construct_t, std::tuple<Args1...> first_args, std::tuple<Args2...> second_args) : std::pair<T1, T2>(std::piecewise_construct, first_args, second_args) {}
    friend std::istream& operator>>(std::istream& is, Pair& p) {
        return is >> p.first >> p.second;
    }
    friend std::ostream& operator<<(std::ostream& os, const Pair& p) {
        return os << p.first << ' ' << p.second;
    }
};
namespace std {
    template <typename T1, typename T2>
    struct hash<Pair<T1, T2>> {
        size_t operator()(const Pair<T1, T2>& p) const {
            size_t seed = 0;
            seed ^= hash<T1>()(p.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= hash<T2>()(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };
}
