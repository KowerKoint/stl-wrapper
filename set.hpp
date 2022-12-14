#include <algorithm>
#include <iostream>
#include <functional>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include "vector.hpp"


template <typename T, typename Compare = std::less<T>>
using pbds_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, Compare, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

template <typename T, typename Compare = std::less<T>>
struct Set : public pbds_set<T, Compare> {
    Set() : pbds_set<T, Compare>() {}
    explicit Set(const Compare& comp) : pbds_set<T, Compare>(comp) {}
    template <typename It>
    Set(It first, It last, const Compare& comp = Compare()) : pbds_set<T, Compare>(first, last, comp) {}
    Set(const pbds_set<T, Compare>& other) : pbds_set<T, Compare>(other) {}
    Set(const std::set<T, Compare>& other) : pbds_set<T, Compare>(other.begin(), other.end()) {}
    Set(pbds_set<T, Compare>&& other) : pbds_set<T, Compare>(std::move(other)) {}
    Set(std::initializer_list<T> init, const Compare& comp = Compare()) : pbds_set<T, Compare>(init, comp) {}
    typename Set::const_iterator cbegin() const { return this->begin(); }
    typename Set::const_iterator cend() const { return this->end(); }
    typename Set::const_reverse_iterator crbegin() const { return this->rbegin(); }
    typename Set::const_reverse_iterator crend() const { return this->rend(); }
    template <typename K>
    std::pair<typename Set::iterator, typename Set::iterator> equal_range(const K& value) {
        return std::make_pair(lower_bound(value), upper_bound(value));
    }
    template <typename K>
    std::pair<typename Set::const_iterator, typename Set::const_iterator> equal_range(const K& value) const {
        return std::make_pair(lower_bound(value), upper_bound(value));
    }
    template <typename K>
    size_t count(const K& x) const { return this->find(x) != this->end(); }
    decltype(Compare()) key_comp() const { return Compare(); }
    template <typename... Args>
    std::pair<typename Set::iterator, bool> emplace(Args&&... args) {
        return this->insert(T(std::forward<Args>(args)...));
    }
    template <typename... Args>
    typename Set::iterator emplace_hint(typename Set::const_iterator hint, Args&&... args) {
        return this->insert(hint, T(std::forward<Args>(args)...));
    }
    friend std::ostream& operator<<(std::ostream& os, const Set& set) {
        Vector<T> vector(set.begin(), set.end());
        return os << vector;
    }
};

namespace _set_util {
    template <typename T, typename Compare>
    struct CompareEqual {
        bool operator()(const T& lhs, const T& rhs) const {
            return !Compare()(rhs, lhs);
        }
    };
}
template <typename T, typename Compare = std::less<T>>
using pbds_multiset = __gnu_pbds::tree<T, __gnu_pbds::null_type, _set_util::CompareEqual<T, Compare>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

template <typename T, typename Compare = std::less<T>>
struct MultiSet : public pbds_multiset<T, Compare> {
    MultiSet() : pbds_multiset<T, Compare>() {}
    explicit MultiSet(const Compare& comp) : pbds_multiset<T, Compare>(comp) {}
    template <typename It>
    MultiSet(It first, It last, const Compare& comp = Compare()) : pbds_multiset<T, Compare>(first, last, comp) {}
    MultiSet(const pbds_multiset<T, Compare>& other) : pbds_multiset<T, Compare>(other) {}
    MultiSet(const std::multiset<T, Compare>& other) : pbds_multiset<T, Compare>(other.begin(), other.end()) {}
    MultiSet(pbds_multiset<T, Compare>&& other) : pbds_multiset<T, Compare>(std::move(other)) {}
    MultiSet(std::initializer_list<T> init, const Compare& comp = Compare()) : pbds_multiset<T, Compare>(init, comp) {}
    typename MultiSet::const_iterator cbegin() const { return this->begin(); }
    typename MultiSet::const_iterator cend() const { return this->end(); }
    typename MultiSet::const_reverse_iterator crbegin() const { return this->rbegin(); }
    typename MultiSet::const_reverse_iterator crend() const { return this->rend(); }
    template <typename K>
    std::pair<typename MultiSet::iterator, typename MultiSet::iterator> equal_range(const K& value) {
        return std::make_pair(lower_bound(value), upper_bound(value));
    }
    template <typename K>
    std::pair<typename MultiSet::const_iterator, typename MultiSet::const_iterator> equal_range(const K& value) const {
        return std::make_pair(lower_bound(value), upper_bound(value));
    }
    template <typename K>
    size_t count(const K& x) const {
        auto range = equal_range(x);
        return std::distance(range.first, range.second);
    }
    decltype(Compare()) key_comp() const { return Compare(); }
    template <typename... Args>
    typename MultiSet::iterator emplace(Args&&... args) {
        return this->insert(T(std::forward<Args>(args)...));
    }
    template <typename... Args>
    typename MultiSet::iterator emplace_hint(typename MultiSet::const_iterator hint, Args&&... args) {
        return this->insert(hint, T(std::forward<Args>(args)...));
    }
    friend std::ostream& operator<<(std::ostream& os, const MultiSet& set) {
        Vector<T> vector(set.begin(), set.end());
        return os << vector;
    }
};
namespace std {
    template <typename T, typename Compare>
    struct hash<Set<T, Compare>> {
        size_t operator()(const Set<T, Compare>& set) const {
            Vector<T> vec(set.begin(), set.end());
            return hash<Vector<T>>()(vec);
        }
    };
    template <typename T, typename Compare>
    struct hash<MultiSet<T, Compare>> {
        size_t operator()(const MultiSet<T, Compare>& set) const {
            Vector<T> vec(set.begin(), set.end());
            return hash<Vector<T>>()(vec);
        }
    };
};
