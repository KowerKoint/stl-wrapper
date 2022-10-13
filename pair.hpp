#pragma once
#include <iostream>
#include <utility>

template <typename T1, typename T2>
struct Pair : std::pair<T1, T2> {
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
