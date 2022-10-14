#pragma once
#include <iostream>
#include <functional>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include "vector.hpp"

template <typename Key, typename Value, typename Compare = std::less<Key>>
struct Map : __gnu_pbds::tree<Key, Value, Compare, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> {
    Map& operator&=(const Map& other) {
        for (auto it = this->begin(); it != this->end(); ) {
            if (other.find(it->first) == other.end()) {
                it = this->erase(it);
            } else {
                ++it;
            }
        }
        return *this;
    }
    Map operator&(const Map& other) const {
        return Map(*this) &= other;
    }
    Map& operator|=(const Map& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            this->insert(*it);
        }
        return *this;
    }
    Map operator|(const Map& other) const {
        return Map(*this) |= other;
    }
    Map& operator^=(const Map& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            if (this->find(it->first) == this->end()) {
                this->insert(*it);
            } else {
                this->erase(it->first);
            }
        }
        return *this;
    }
    Map operator^(const Map& other) const {
        return Map(*this) ^= other;
    }
    Map& operator-=(const Map& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            this->erase(it->first);
        }
        return *this;
    }
    Map operator-(const Map& other) const {
        return Map(*this) -= other;
    }
    friend std::ostream& operator<<(std::ostream& out, const Map& map) {
        for (auto it = map.begin(); it != map.end(); ++it) {
            out << it->first << ' ' << it->second << '\n';
        }
        return out;
    }
};

namespace _map_util {
    template <typename T, typename Compare>
    struct CompareEqual {
        bool operator()(const T& lhs, const T& rhs) const {
            return !Compare()(rhs, lhs);
        }
    };
}
template <typename Key, typename Value, typename Compare = std::less<Key>>
struct MultiMap : __gnu_pbds::tree<Key, Value, _map_util::CompareEqual<Key, Compare>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> {
    MultiMap& operator+=(const MultiMap& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            this->insert(*it);
        }
        return *this;
    }
    MultiMap operator+(const MultiMap& other) const {
        return MultiMap(*this) += other;
    }
    MultiMap& operator-=(const MultiMap& other) const {
        for (auto it = other.begin(); it != other.end(); ++it) {
            auto it2 = this->find(it->first);
            if (it2 != this->end()) {
                this->erase(it2);
            }
        }
        return *this;
    }
    MultiMap operator-(const MultiMap& other) const {
        return MultiMap(*this) -= other;
    }
    friend std::ostream& operator<<(std::ostream& out, const MultiMap& map) {
        for (auto it = map.begin(); it != map.end(); ++it) {
            out << it->first << ' ' << it->second << '\n';
        }
        return out;
    }
};

namespace std {
    template <typename Key, typename Value, typename Compare>
    struct hash<Map<Key, Value, Compare>> {
        size_t operator()(const Map<Key, Value, Compare>& map) const {
            Vector<pair<Key, Value>> v(map.begin(), map.end());
            return hash<Vector<pair<Key, Value>>>()(v);
        }
    };
    template <typename Key, typename Value, typename Compare>
    struct hash<MultiMap<Key, Value, Compare>> {
        size_t operator()(const Map<Key, Value, Compare>& map) const {
            Vector<pair<Key, Value>> v(map.begin(), map.end());
            return hash<Vector<pair<Key, Value>>>()(v);
        }
    };
}
