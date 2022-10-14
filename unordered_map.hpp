#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <unordered_map>
#include "vector.hpp"

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
struct UnorderedMap : public __gnu_pbds::gp_hash_table<Key, Value, Hash, KeyEqual> {
    UnorderedMap() : __gnu_pbds::gp_hash_table<Key, Value, Hash, KeyEqual>() {}
    explicit UnorderedMap(std::size_t bucket_count, const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual()) : __gnu_pbds::gp_hash_table<Key, Value, Hash, KeyEqual>(bucket_count, hash, equal) {}
    template <typename InputIt>
    UnorderedMap(InputIt first, InputIt last, std::size_t bucket_count = 1, const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual()) : __gnu_pbds::gp_hash_table<Key, Value, Hash, KeyEqual>(first, last, bucket_count, hash, equal) {}
    UnorderedMap(const UnorderedMap& other) : __gnu_pbds::gp_hash_table<Key, Value, Hash, KeyEqual>(other) {}
    UnorderedMap(UnorderedMap&& other) noexcept : __gnu_pbds::gp_hash_table<Key, Value, Hash, KeyEqual>(std::move(other)) {}
    UnorderedMap(std::initializer_list<std::pair<Key, Value>> init, std::size_t bucket_count = 1, const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual()) : __gnu_pbds::gp_hash_table<Key, Value, Hash, KeyEqual>(init, bucket_count, hash, equal) {}
    friend std::ostream& operator<<(std::ostream& os, const UnorderedMap& set) {
        for (auto it = set.begin(); it != set.end(); ++it) {
            os << it->first << ' ' << it->second << '\n';
        }
        return os;
    }
};
template <typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
struct UnorderedMultiMap : std::unordered_multimap<Key, Value, Hash, KeyEqual> {
    UnorderedMultiMap() : std::unordered_multimap<Key, Value, Hash, KeyEqual>() {}
    explicit UnorderedMultiMap(std::size_t bucket_count, const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual()) : std::unordered_multimap<Key, Value, Hash, KeyEqual>(bucket_count, hash, equal) {}
    template <typename InputIt>
    UnorderedMultiMap(InputIt first, InputIt last, std::size_t bucket_count = 1, const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual()) : std::unordered_multimap<Key, Value, Hash, KeyEqual>(first, last, bucket_count, hash, equal) {}
    UnorderedMultiMap(const UnorderedMultiMap& other) : std::unordered_multimap<Key, Value, Hash, KeyEqual>(other) {}
    UnorderedMultiMap(UnorderedMultiMap&& other) noexcept : std::unordered_multimap<Key, Value, Hash, KeyEqual>(std::move(other)) {}
    UnorderedMultiMap(std::initializer_list<std::pair<Key, Value>> init, std::size_t bucket_count = 1, const Hash& hash = Hash(), const KeyEqual& equal = KeyEqual()) : std::unordered_multimap<Key, Value, Hash, KeyEqual>(init, bucket_count, hash, equal) {}
    friend std::ostream& operator<<(std::ostream& os, const UnorderedMultiMap& map) {
        for (auto it = map.begin(); it != map.end(); ++it) {
            os << it->first << ' ' << it->second << '\n';
        }
        return os;
    }
};
namespace std {
    template<typename T, typename Hash, typename KeyEqual>
    struct hash<UnorderedMap<T, Hash, KeyEqual>> {
        size_t operator()(const UnorderedMap<T, Hash, KeyEqual>& map) const {
            Vector<T> vec(map.begin(), map.end());
            sort(vec.begin(), vec.end());
            return hash<Vector<T>>()(vec);
        }
    };
    template<typename T, typename Hash, typename KeyEqual>
    struct hash<UnorderedMultiMap<T, Hash, KeyEqual>> {
        size_t operator()(const UnorderedMultiMap<T, Hash, KeyEqual>& map) const {
            Vector<T> vec(map.begin(), map.end());
            sort(vec.begin(), vec.end());
            return hash<Vector<T>>()(vec);
        }
    };
}
