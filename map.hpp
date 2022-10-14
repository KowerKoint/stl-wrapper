#pragma once
#include <iostream>
#include <functional>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include "vector.hpp"

template <typename Key, typename Value, typename Compare = std::less<Key>>
struct Map : __gnu_pbds::tree<Key, Value, Compare, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> {
    Map() : __gnu_pbds::tree<Key, Value, Compare, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>() {}
    explicit Map(const Compare& comp) : __gnu_pbds::tree<Key, Value, Compare, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>(comp) {}
    template <typename It>
    Map(It first, It last, const Compare& comp = Compare()) : __gnu_pbds::tree<Key, Value, Compare, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>(first, last, comp) {}
    Map(const Map& other) : __gnu_pbds::tree<Key, Value, Compare, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>(other) {}
    Map(Map&& other) : __gnu_pbds::tree<Key, Value, Compare, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>(std::move(other)) {}
    Map(std::initializer_list<std::pair<Key, Value>> init, const Compare& comp = Compare()) : __gnu_pbds::tree<Key, Value, Compare, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>(init, comp) {}
    typename Map::const_iterator cbegin() const { return this->begin(); }
    typename Map::const_iterator cend() const { return this->end(); }
    typename Map::const_reverse_iterator crbegin() const { return this->rbegin(); }
    typename Map::const_reverse_iterator crend() const { return this->rend(); }
    template <typename K>
    std::pair<typename Map::iterator, typename Map::iterator> equal_range(const K& value) {
        return std::make_pair(lower_bound(value), upper_bound(value));
    }
    template <typename K>
    std::pair<typename Map::const_iterator, typename Map::const_iterator> equal_range(const K& value) const {
        return std::make_pair(lower_bound(value), upper_bound(value));
    }
    Value& at(const Key& key) {
        auto it = find(key);
        assert(it != this->end());
        return it->second;
    }
    const Value& at(const Key& key) const {
        auto it = find(key);
        assert(it != this->end());
        return it->second;
    }
    template <typename K>
    std::size_t count(const K& x) const { return this->find(x) != this->end(); }
    decltype(Compare()) key_comp() const { return Compare(); }
    template <typename... Args>
    std::pair<typename Map::iterator, bool> emplace(Args&&... args) {
        return this->insert(std::make_pair(std::forward<Args>(args)...));
    }
    template <typename... Args>
    typename Map::iterator emplace_hint(typename Map::const_iterator hint, Args&&... args) {
        return this->insert(hint, std::make_pair(std::forward<Args>(args)...));
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
    MultiMap() : __gnu_pbds::tree<Key, Value, _map_util::CompareEqual<Key, Compare>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>() {}
    explicit MultiMap(const Compare& comp) : __gnu_pbds::tree<Key, Value, _map_util::CompareEqual<Key, Compare>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>(comp) {}
    template <typename It>
    MultiMap(It first, It last, const Compare& comp = Compare()) : __gnu_pbds::tree<Key, Value, _map_util::CompareEqual<Key, Compare>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>(first, last, comp) {}
    MultiMap(const MultiMap& other) : __gnu_pbds::tree<Key, Value, _map_util::CompareEqual<Key, Compare>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>(other) {}
    MultiMap(MultiMap&& other) : __gnu_pbds::tree<Key, Value, _map_util::CompareEqual<Key, Compare>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>(std::move(other)) {}
    MultiMap(std::initializer_list<std::pair<Key, Value>> init, const Compare& comp = Compare()) : __gnu_pbds::tree<Key, Value, _map_util::CompareEqual<Key, Compare>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>(init, comp) {}
    typename MultiMap::const_iterator cbegin() const { return this->begin(); }
    typename MultiMap::const_iterator cend() const { return this->end(); }
    typename MultiMap::const_reverse_iterator crbegin() const { return this->rbegin(); }
    typename MultiMap::const_reverse_iterator crend() const { return this->rend(); }
    template <typename K>
    std::pair<typename MultiMap::iterator, typename MultiMap::iterator> equal_range(const K& value) {
        return std::make_pair(lower_bound(value), upper_bound(value));
    }
    template <typename K>
    std::pair<typename MultiMap::const_iterator, typename MultiMap::const_iterator> equal_range(const K& value) const {
        return std::make_pair(lower_bound(value), upper_bound(value));
    }
    Value& at(const Key& key) {
        auto it = find(key);
        assert(it != this->end());
        return it->second;
    }
    const Value& at(const Key& key) const {
        auto it = find(key);
        assert(it != this->end());
        return it->second;
    }
    template <typename K>
    std::size_t count(const K& x) const {
        auto range = equal_range(x);
        return std::distance(range.first, range.second);
    }
    decltype(Compare())key_comp() const { return Compare(); }
    template <typename... Args>
    typename MultiMap::iterator emplace(Args&&... args) {
        return this->insert(std::make_pair(std::forward<Args>(args)...));
    }
    template <typename... Args>
    typename MultiMap::iterator emplace_hint(typename MultiMap::const_iterator hint, Args&&... args) {
        return this->insert(hint, std::make_pair(std::forward<Args>(args)...));
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
