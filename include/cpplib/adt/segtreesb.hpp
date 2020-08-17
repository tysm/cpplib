#pragma once
#include <cpplib/adt/segtreeb.hpp>
#include <cpplib/stdinc.hpp>

/**
 * Segment Tree S Node Base.
 *
 * Note: this implementation only adds
 * required variables to perform set
 * operations.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
template<typename T>
struct STNodeSB : STNodeB<T>
{
    using super_type = STNodeB<T>;
    pair<T, bool> set = {0, false};

    STNodeSB() :
        super_type() {}

    STNodeSB(const T value) :
        super_type(value) {}

    STNodeSB(const STNodeSB &lhs, const STNodeSB &rhs)
    {
        // meant to create a node by merging lhs and rhs.
    }

    virtual void reset_lazy()
    {
        this->lazy = 0;
    }
};

/**
 * Segment Tree S Base.
 *
 * Note: this implementation only adds
 * (range and point) set operations
 * since it costs a bunch of extra time and
 * memory (mainly when many Segment Trees
 * are constructed, e.g.: Segment Tree 2D).
 *
 * Note: when the tree is constructed by
 * inserting each value one by one using
 * set and/or update, the time complexity
 * is actually O(n*log(n)).
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the size of the array.
 */
template<typename NodeS, typename T>
class SegTreeSB : public SegTreeB<NodeS, T>
{
public:
    SegTreeSB() :
        super_type() {}

    SegTreeSB(const size_t arr_size) :
        super_type(arr_size) {}

    SegTreeSB(const vector<T> &arr) :
        super_type(arr) {}

    SegTreeSB(const size_t arr_size, const vector<T> &arr) :
        super_type(arr_size, arr) {}

    SegTreeSB(const SegTreeSB &lhs, const SegTreeSB &rhs) :
        super_type(lhs, rhs) {}

    /**
     * Sets the ith array value to value.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    void set(const size_t i, const T value)
    {
        assert(i < this->arr_size);
        set(i, i, value);
    }

    /**
     * Sets the array values in the range
     * [l, r] to value.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    void set(const size_t l, const size_t r, const T value)
    {
        assert(l <= r and r < this->arr_size);
        set(0, this->arr_size - 1, l, r, 0, value);
    }

private:
    using super_type = SegTreeB<NodeS, T>;

    NodeS set(const size_t l, const size_t r, const size_t i, const size_t j, const size_t pos, const T value)
    {
        propagate(l, r, pos);

        if(l > j or r < i)
            return this->tree[pos];

        if(l >= i and r <= j) {
            this->tree[pos].set = {value, true};
            // it's important to propagate before returning and merge nodes.
            propagate(l, r, pos);
            return this->tree[pos];
        }

        size_t mid = (l + r) / 2;
        return this->tree[pos] = NodeS(set(l, mid, i, j, 2 * pos + 1, value), set(mid + 1, r, i, j, 2 * pos + 2, value));
    }

    void propagate(const size_t l, const size_t r, const size_t pos)
    {
        if(!this->tree[pos].has_lazy() and !this->tree[pos].set.second)
            return;

        T lazy = this->tree[pos].lazy;
        pair<T, bool> set = this->tree[pos].set;
        this->tree[pos].update(r - l + 1);

        if(l != r) {
            if(set.second) {
                this->tree[2 * pos + 1].set = set;
                this->tree[2 * pos + 2].set = set;

                this->tree[2 * pos + 1].reset_lazy();
                this->tree[2 * pos + 2].reset_lazy();
            }
            this->tree[2 * pos + 1].update_lazy(lazy);
            this->tree[2 * pos + 2].update_lazy(lazy);
        }
    }
};
