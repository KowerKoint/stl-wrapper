#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <unordered_set>
#include "vector.hpp"

template <typename T, typename Hash = std::hash<T>, typename KeyEqual = std::equal_to<T>, typename Allocator = std::allocator<T>>
struct UnorderedSet : public __gnu_pbds::gp_hash_table<T, __gnu_pbds::null_type, Hash, KeyEqual, Allocator> {
    UnorderedSet& operator&=(const UnorderedSet& other) {
        for (auto it = this->begin(); it != this->end();) {
            if (other.find(*it) == other.end()) it = this->erase(it);
            else ++it;
        }
        return *this;
    }
    UnorderedSet operator&(const UnorderedSet& other) const {
        return UnorderedSet(*this) &= other;
    }
    UnorderedSet& operator|=(const UnorderedSet& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            this->insert(*it);
        }
        return *this;
    }
    UnorderedSet operator|(const UnorderedSet& other) const {
        return UnorderedSet(*this) |= other;
    }
    UnorderedSet& operator^=(const UnorderedSet& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            if (this->find(*it) == this->end()) this->insert(*it);
            else this->erase(*it);
        }
        return *this;
    }
    UnorderedSet operator^(const UnorderedSet& other) const {
        return UnorderedSet(*this) ^= other;
    }
    UnorderedSet& operator-=(const UnorderedSet& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            this->erase(*it);
        }
        return *this;
    }
    UnorderedSet operator-(const UnorderedSet& other) const {
        return UnorderedSet(*this) -= other;
    }
    friend std::ostream& operator<<(std::ostream& os, const UnorderedSet& set) {
        for (auto it = set.begin(); it != set.end(); ++it) {
            if(it != set.begin()) os << " ";
            os << *it;
        }
        return os;
    }
};
template <typename T, typename Hash = std::hash<T>, typename KeyEqual = std::equal_to<T>, typename Allocator = std::allocator<T>>
struct UnorderedMultiSet : std::unordered_multiset<T, Hash, KeyEqual, Allocator> {
    UnorderedMultiSet operator+=(const UnorderedMultiSet& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            this->insert(*it);
        }
        return *this;
    }
    UnorderedMultiSet operator+(const UnorderedMultiSet& other) const {
        return UnorderedMultiSet(*this) += other;
    }
    UnorderedMultiSet operator-=(const UnorderedMultiSet& other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            auto it2 = this->find(*it);
            if (it2 != this->end()) this->erase(it2);
        }
        return *this;
    }
    UnorderedMultiSet operator-(const UnorderedMultiSet& other) const {
        return UnorderedMultiSet(*this) -= other;
    }
    friend std::ostream& operator<<(std::ostream& os, const UnorderedMultiSet& set) {
        for (auto it = set.begin(); it != set.end(); ++it) {
            if(it != set.begin()) os << " ";
            os << *it;
        }
        return os;
    }
};
namespace std {
    template<typename T, typename Hash, typename KeyEqual, typename Allocator>
    struct hash<UnorderedSet<T, Hash, KeyEqual, Allocator>> {
        size_t operator()(const UnorderedSet<T, Hash, KeyEqual, Allocator>& set) const {
            Vector<T> vec(set.begin(), set.end());
            sort(vec.begin(), vec.end());
            return hash<Vector<T>>()(vec);
        }
    };
}
