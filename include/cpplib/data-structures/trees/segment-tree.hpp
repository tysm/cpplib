#pragma once
#include <cpplib/stdinc.hpp>

enum class SegTreeKind
{
    RMaxQ,
    RMinQ,
    RSumQ,
    RXorQ,
};

/**
 * Segment Tree.
 *
 * Arranges data in a binary tree so that
 * it is possible to perform range queries
 * and modifications over an array
 * effectively.
 *
 * Common kinds of use:
 * - Range Max Query;
 * - Range Min Query;
 * - Range Sum Query;
 * - Range Xor Query.
 *
 * Note: when the tree is constructed by
 * inserting each value one by one using
 * set and/or update, the time complexity
 * is actually O(n*log(n)).
 *
 * Note: it's recommended to remove the
 * pair<T, bool> set from
 * SegTree<K, T>::Node when it's not being
 * used since it costs a bunch of time and
 * memory mainly when many Segment Trees
 * are constructed (e.g., Segment Tree 2D).
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the size of the array.
 */
template<SegTreeKind K, typename T>
class SegTree
{
public:
    /**
     * Segment Tree Node.
     *
     * Helps to hold range data dynamically so
     * that only a small number of nodes are
     * visited per query.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    struct Node {
        T value, lazy = 0;
        pair<T, bool> set = {0, false};

        Node() :
            value(Node::default_value()) {}

        Node(const T value) :
            value(value) {}

        Node(const Node &lhs, const Node &rhs)
        {
            assert(lhs.lazy == 0 and rhs.lazy == 0);
            assert(!lhs.set.ss and !rhs.set.ss);
            value = Node::merge_values(lhs.value, rhs.value);
        }

        /**
         * Checks if a value matches with
         * this->value according to the
         * SegmentTreeKind.
         *
         * Time Complexity: O(1).
         * Space Complexity: O(1).
         */
        bool match(const T value) const
        {
            switch(K){
                case SegTreeKind::RMaxQ:
                    return this->value >= value;
                    // return this->value > value;
                case SegTreeKind::RMinQ:
                    return this->value <= value;
                    // return this->value < value;
                case SegTreeKind::RSumQ:
                case SegTreeKind::RXorQ:
                default:
                    assert(false);
            }
        }

        /**
         * Updates the current node according to
         * the SegmentTreeKind.
         *
         * Time Complexity: O(1).
         * Space Complexity: O(1).
         */
        void update(const size_t range)
        {
            if(set.ss){
                switch (K){
                    case SegTreeKind::RMaxQ:
                    case SegTreeKind::RMinQ:
                        value = set.ff;
                        break;
                    case SegTreeKind::RSumQ:
                        value = range*set.ff;
                        break;
                    case SegTreeKind::RXorQ:
                        value = (range%2)*set.ff;
                        break;
                    default:
                        assert(false);
                }
            }

            switch (K){
                case SegTreeKind::RMaxQ:
                case SegTreeKind::RMinQ:
                    value += lazy;
                    break;
                case SegTreeKind::RSumQ:
                    value += range*lazy;
                    break;
                case SegTreeKind::RXorQ:
                    break;
                default:
                    assert(false);
            }

            lazy = 0;
            set = {0, false};
        }

        /**
         * Returns the default value according to
         * the SegmentTreeKind.
         *
         * Time Complexity: O(1).
         * Space Complexity: O(1).
         */
        static T default_value()
        {
            switch(K){
                case SegTreeKind::RMaxQ:
                    return -INF;
                case SegTreeKind::RMinQ:
                    return INF;
                case SegTreeKind::RSumQ:
                    return 0;
                case SegTreeKind::RXorQ:
                    return 0;
                default:
                    assert(false);
            }
        }

        /**
         * Merges two values into a new one
         * according to the SegmentTreeKind.
         *
         * Time Complexity: O(1).
         * Space Complexity: O(1).
         */
        static T merge_values(const T lhs, const T rhs)
        {
            switch(K){
                case SegTreeKind::RMaxQ:
                    return max(lhs, rhs);
                case SegTreeKind::RMinQ:
                    return min(lhs, rhs);
                case SegTreeKind::RSumQ:
                    return lhs + rhs;
                case SegTreeKind::RXorQ:
                    return lhs ^ rhs;
                default:
                    assert(false);
            }
        }
    };

    SegTree() = delete;

    SegTree(const size_t arr_size) :
        tree(4*arr_size), arr_size(arr_size) {}

    SegTree(const vector<T> &arr) :
        SegTree(arr.size(), arr) {}

    SegTree(const size_t arr_size, const vector<T> &arr) :
        tree(4*arr_size), arr_size(arr_size)
    {
        build(0, arr_size-1, 0, arr);
    }

    SegTree(const SegTree &lhs, const SegTree &rhs) :
        SegTree(lhs.arr_size)
    {
        assert(lhs.arr_size == rhs.arr_size);
        for(size_t i=0; i<4*arr_size; ++i)
            tree[i] = Node(lhs.tree[i], rhs.tree[i]);
    }

    /**
     * Finds the index of the first element
     * over the array that matches with value.
     *
     * It returns the size of the array when
     * the value doesn't match with any array
     * value.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    size_t find(const T value)
    {
        return find(0, arr_size-1, 0, value);
    }

    /**
     * Computes the ith array value.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    T query(const size_t i)
    {
        assert(i < arr_size);
        return query(i, i);
    }

    /**
     * Computes the value corresponding to the
     * range [l, r] of the array.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    T query(const size_t l, const size_t r)
    {
        assert(l <= r and r < arr_size);
        return query(0, arr_size-1, l, r, 0);
    }

    /**
     * Sets the ith array value to value.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    void set(const size_t i, const T value)
    {
        assert(i < arr_size);
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
        assert(l <= r and r < arr_size);
        set(0, arr_size-1, l, r, 0, value);
    }

    /**
     * Updates the ith array value according to
     * the SegmentTreeKind.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    void update(const size_t i, const T delta)
    {
        assert(i < arr_size);
        update(i, i, delta);
    }

    /**
     * Updates the array values in the range
     * [l, r] according to the SegmentTreeKind.
     *
     * Time Complexity: O(log(n)).
     * Space Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    void update(const size_t l, const size_t r, const T delta)
    {
        assert(l <= r and r < arr_size);
        update(0, arr_size-1, l, r, 0, delta);
    }

private:
    Node build(const size_t l, const size_t r, const size_t pos, const vector<T> &arr)
    {
        if(l == r)
            return tree[pos] = Node(arr[l]);

        size_t mid = (l + r)/2;
        return tree[pos] = Node(build(l, mid, 2*pos+1, arr), build(mid+1, r, 2*pos+2, arr));
    }

    size_t find(const size_t l, const size_t r, const size_t pos, const T value)
    {
        propagate(l, r, pos);

        if(!tree[pos].match(value))
            return arr_size;
        else if(l == r)
            return l;

        size_t mid = (l + r)/2;
        size_t ans = find(l, mid, 2*pos+1, value);
        return ans != arr_size? ans : find(mid+1, r, 2*pos+2, value);
    }

    T query(const size_t l, const size_t r, const size_t i, const size_t j, const size_t pos)
    {
        propagate(l, r, pos);

        if(l > j or r < i)
            return Node::default_value();

        if(l >= i and r <= j)
            return tree[pos].value;

        size_t mid = (l + r)/2;
        return Node::merge_values(query(l, mid, i, j, 2*pos+1), query(mid+1, r, i, j, 2*pos+2));
    }

    Node set(const size_t l, const size_t r, const size_t i, const size_t j, const size_t pos, const T value)
    {
        propagate(l, r, pos);

        if(l > j or r < i)
            return tree[pos];

        if(l >= i and r <= j){
            tree[pos].set = {value, true};
            // it's important to propagate before returning and merge nodes.
            propagate(l, r, pos);
            return tree[pos];
        }

        size_t mid = (l + r)/2;
        return tree[pos] = Node(set(l, mid, i, j, 2*pos+1, value), set(mid+1, r, i, j, 2*pos+2, value));
    }

    Node update(const size_t l, const size_t r, const size_t i, const size_t j, const size_t pos, const T delta)
    {
        propagate(l, r, pos);

        if(l > j or r < i)
            return tree[pos];

        if(l >= i and r <= j){
            tree[pos].lazy = delta;
            // it's important to propagate before returning and merge nodes.
            propagate(l, r, pos);
            return tree[pos];
        }

        size_t mid = (l + r)/2;
        return tree[pos] = Node(update(l, mid, i, j, 2*pos+1, delta), update(mid+1, r, i, j, 2*pos+2, delta));
    }

    void propagate(const size_t l, const size_t r, const size_t pos)
    {
        T lazy = tree[pos].lazy;
        pair<T, bool> set = tree[pos].set;

        if(lazy == 0 and !set.ss)
            return;

        tree[pos].update((r - l + 1));

        if(l != r){
            if(set.ss){
                tree[2*pos+1].set = set;
                tree[2*pos+2].set = set;

                tree[2*pos+1].lazy = 0;
                tree[2*pos+2].lazy = 0;
            }
            tree[2*pos+1].lazy += lazy;
            tree[2*pos+2].lazy += lazy;
        }
    }

    vector<Node> tree;
    size_t arr_size;
};
