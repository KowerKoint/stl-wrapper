#include <algorithm>
#include <iostream>
#include <functional>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include "vector.hpp"

template <typename T, typename Compare = std::less<T>, typename Allocator = std::allocator<T>>
struct Set : public __gnu_pbds::tree<T, __gnu_pbds::null_type, Compare, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update, Allocator> {
    Set& operator&=(const Set& other) {
        Set result;
        std::set_intersection(this->begin(), this->end(), other.begin(), other.end(), std::inserter(result, result.begin()));
        this->swap(result);
        return *this;
    }
    Set operator&(const Set& other) const {
        return Set(*this) &= other;
    }
    Set& operator|=(const Set& other) {
        this->insert(other.begin(), other.end());
        return *this;
    }
    Set operator|(const Set& other) const {
        return Set(*this) |= other;
    }
    Set& operator^=(const Set& other) {
        Set result;
        std::set_symmetric_difference(this->begin(), this->end(), other.begin(), other.end(), std::inserter(result, result.begin()));
        this->swap(result);
        return *this;
    }
    Set operator^(const Set& other) const {
        return Set(*this) ^= other;
    }
    Set& operator-=(const Set& other) {
        Set result;
        std::set_difference(this->begin(), this->end(), other.begin(), other.end(), std::inserter(result, result.begin()));
        this->swap(result);
        return *this;
    }
    Set operator-(const Set& other) const {
        return Set(*this) -= other;
    }
    friend std::ostream& operator<<(std::ostream& os, const Set& set) {
        for(auto it = set.begin(); it != set.end(); ++it) {
            if(it != set.begin()) os << ' ';
            os << *it;
        }
        return os;
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
template <typename T, typename Compare = std::less<T>, typename Allocator = std::allocator<T>>
struct MultiSet : public __gnu_pbds::tree<T, __gnu_pbds::null_type, _set_util::CompareEqual<T, Compare>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update, Allocator> {
    MultiSet& operator+=(const MultiSet& other) {
        this->insert(other.begin(), other.end());
        return *this;
    }
    MultiSet operator+(const MultiSet& other) const {
        return MultiSet(*this) += other;
    }
    MultiSet& operator-=(const MultiSet& other) {
        for(auto it = other.begin(); it != other.end(); ++it) {
            auto it2 = this->find(*it);
            if(it2 != this->end()) this->erase(it2);
        }
        return *this;
    }
    MultiSet operator-(const MultiSet& other) const {
        return MultiSet(*this) -= other;
    }
    friend std::ostream& operator<<(std::ostream& os, const MultiSet& set) {
        for(auto it = set.begin(); it != set.end(); ++it) {
            if(it != set.begin()) os << ' ';
            os << *it;
        }
        return os;
    }
};
namespace std {
    template <typename T, typename Compare, typename Allocator>
    struct hash<Set<T, Compare, Allocator>> {
        size_t operator()(const Set<T, Compare, Allocator>& set) const {
            Vector<T> vec(set.begin(), set.end());
            return hash<Vector<T>>()(vec);
        }
    };
    template <typename T, typename Compare, typename Allocator>
    struct hash<MultiSet<T, Compare, Allocator>> {
        size_t operator()(const MultiSet<T, Compare, Allocator>& set) const {
            Vector<T> vec(set.begin(), set.end());
            return hash<Vector<T>>()(vec);
        }
    };
};
