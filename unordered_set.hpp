#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <unordered_set>
#include "vector.hpp"

template <typename T, typename Hash = std::hash<T>, typename KeyEqual = std::equal_to<T>>
struct UnorderedSet : public __gnu_pbds::gp_hash_table<T, __gnu_pbds::null_type, Hash, KeyEqual> {
    UnorderedSet() : __gnu_pbds::gp_hash_table<T, __gnu_pbds::null_type, Hash, KeyEqual>() {}
    explicit UnorderedSet(std::size_t bucket_count, const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual()) : __gnu_pbds::gp_hash_table<T, __gnu_pbds::null_type, Hash, KeyEqual>(bucket_count, hash, equal) {}
    template <typename InputIt>
    UnorderedSet(InputIt first, InputIt last, std::size_t bucket_count = 1, const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual()) : __gnu_pbds::gp_hash_table<T, __gnu_pbds::null_type, Hash, KeyEqual>(first, last, bucket_count, hash, equal) {}
    UnorderedSet(const UnorderedSet& other) : __gnu_pbds::gp_hash_table<T, __gnu_pbds::null_type, Hash, KeyEqual>(other) {}
    UnorderedSet(UnorderedSet&& other) : __gnu_pbds::gp_hash_table<T, __gnu_pbds::null_type, Hash, KeyEqual>(std::move(other)) {}
    UnorderedSet(std::initializer_list<T> init, std::size_t bucket_count = 1, const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual()) : __gnu_pbds::gp_hash_table<T, __gnu_pbds::null_type, Hash, KeyEqual>(init, bucket_count, hash, equal) {}
    typename UnorderedSet::const_iterator cbegin() const { return this->begin(); }
    typename UnorderedSet::const_iterator cend() const { return this->end(); }
    KeyEqual key_eq() const { return KeyEqual(); }
    std::size_t count(const T& value) const { return this->find(value) != this->end(); }
    template <typename... Args>
    std::pair<typename UnorderedSet::iterator, bool> emplace(Args&&... args) { return this->insert(T(std::forward<Args>(args)...)); }
    template <typename... Args>
    typename UnorderedSet::iterator emplace_hint(typename UnorderedSet::const_iterator hint, Args&&... args) { return this->insert(hint, T(std::forward<Args>(args)...)); }
    friend std::ostream& operator<<(std::ostream& os, const UnorderedSet& set) {
        for (auto it = set.begin(); it != set.end(); ++it) {
            if(it != set.begin()) os << " ";
            os << *it;
        }
        return os;
    }
};
template <typename T, typename Hash = std::hash<T>, typename KeyEqual = std::equal_to<T>>
struct UnorderedMultiSet : std::unordered_multiset<T, Hash, KeyEqual> {
    UnorderedMultiSet() : std::unordered_multiset<T, Hash, KeyEqual>() {}
    explicit UnorderedMultiSet(std::size_t bucket_count, const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual()) : std::unordered_multiset<T, Hash, KeyEqual>(bucket_count, hash, equal) {}
    template <typename InputIt>
    UnorderedMultiSet(InputIt first, InputIt last, std::size_t bucket_count = 1, const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual()) : std::unordered_multiset<T, Hash, KeyEqual>(first, last, bucket_count, hash, equal) {}
    UnorderedMultiSet(const UnorderedMultiSet& other) : std::unordered_multiset<T, Hash, KeyEqual>(other) {}
    UnorderedMultiSet(UnorderedMultiSet&& other) : std::unordered_multiset<T, Hash, KeyEqual>(std::move(other)) {}
    UnorderedMultiSet(std::initializer_list<T> init, std::size_t bucket_count = 1, const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual()) : std::unordered_multiset<T, Hash, KeyEqual>(init, bucket_count, hash, equal) {}
    friend std::ostream& operator<<(std::ostream& os, const UnorderedMultiSet& set) {
        for (auto it = set.begin(); it != set.end(); ++it) {
            if(it != set.begin()) os << " ";
            os << *it;
        }
        return os;
    }
};
namespace std {
    template<typename T, typename Hash, typename KeyEqual>
    struct hash<UnorderedSet<T, Hash, KeyEqual>> {
        size_t operator()(const UnorderedSet<T, Hash, KeyEqual>& set) const {
            Vector<T> vec(set.begin(), set.end());
            sort(vec.begin(), vec.end());
            return hash<Vector<T>>()(vec);
        }
    };
    template<typename T, typename Hash, typename KeyEqual>
    struct hash<UnorderedMultiSet<T, Hash, KeyEqual>> {
        size_t operator()(const UnorderedMultiSet<T, Hash, KeyEqual>& set) const {
            Vector<T> vec(set.begin(), set.end());
            sort(vec.begin(), vec.end());
            return hash<Vector<T>>()(vec);
        }
    };
}
