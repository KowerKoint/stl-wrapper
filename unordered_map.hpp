#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <unordered_map>
#include "vector.hpp"

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = std::allocator<std::pair<Key, Value>>>
struct UnorderedMap : public __gnu_pbds::gp_hash_table<Key, Value, Hash, KeyEqual, Allocator> {
    UnorderedMap& operator&=(const UnorderedMap& other) {
        for (auto it = this->begin(); it != this->end();) {
            if (other.find(*it) == other.end()) it = this->erase(it);
            else ++it;
        }
        return *this;
    }
    UnorderedMap operator&(const UnorderedMap& other) const {
        return UnorderedMap(*this) &= other;
    }
    UnorderedMap& operator|=(const UnorderedMap& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            this->insert(*it);
        }
        return *this;
    }
    UnorderedMap operator|(const UnorderedMap& other) const {
        return UnorderedMap(*this) |= other;
    }
    UnorderedMap& operator^=(const UnorderedMap& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            if (this->find(*it) == this->end()) this->insert(*it);
            else this->erase(*it);
        }
        return *this;
    }
    UnorderedMap operator^(const UnorderedMap& other) const {
        return UnorderedMap(*this) ^= other;
    }
    UnorderedMap& operator-=(const UnorderedMap& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            this->erase(*it);
        }
        return *this;
    }
    UnorderedMap operator-(const UnorderedMap& other) const {
        return UnorderedMap(*this) -= other;
    }
    friend std::ostream& operator<<(std::ostream& os, const UnorderedMap& set) {
        for (auto it = set.begin(); it != set.end(); ++it) {
            if(it != set.begin()) os << " ";
            os << *it;
        }
        return os;
    }
};
template <typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = std::allocator<std::pair<Key, Value>>>
struct UnorderedMultiMap : std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator> {
    UnorderedMultiMap operator+=(const UnorderedMultiMap& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            this->insert(*it);
        }
        return *this;
    }
    UnorderedMultiMap operator+(const UnorderedMultiMap& other) const {
        return UnorderedMultiMap(*this) += other;
    }
    UnorderedMultiMap operator-=(const UnorderedMultiMap& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            auto it2 = this->find(*it);
            if (it2 != this->end()) this->erase(it2);
        }
        return *this;
    }
    UnorderedMultiMap operator-(const UnorderedMultiMap& other) const {
        return UnorderedMultiMap(*this) -= other;
    }
    friend std::ostream& operator<<(std::ostream& os, const UnorderedMultiMap& set) {
        for (auto it = set.begin(); it != set.end(); ++it) {
            if(it != set.begin()) os << " ";
            os << *it;
        }
        return os;
    }
};
namespace std {
    template<typename T, typename Hash, typename KeyEqual, typename Allocator>
    struct hash<UnorderedMap<T, Hash, KeyEqual, Allocator>> {
        size_t operator()(const UnorderedMap<T, Hash, KeyEqual, Allocator>& set) const {
            Vector<T> vec(set.begin(), set.end());
            sort(vec.begin(), vec.end());
            return hash<Vector<T>>()(vec);
        }
    };
    template<typename T, typename Hash, typename KeyEqual, typename Allocator>
    struct hash<UnorderedMultiMap<T, Hash, KeyEqual, Allocator>> {
        size_t operator()(const UnorderedMultiMap<T, Hash, KeyEqual, Allocator>& set) const {
            Vector<T> vec(set.begin(), set.end());
            sort(vec.begin(), vec.end());
            return hash<Vector<T>>()(vec);
        }
    };
}
