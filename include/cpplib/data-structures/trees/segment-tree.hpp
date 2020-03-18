#pragma once
#include <cpplib/header.hpp>

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
 * Arranges data in a binary tree so that it
 * is possible to perform range queries and
 * modifications over an array effectively.
 *
 * Common kinds of use:
 * - Range Max Query;
 * - Range Min Query;
 * - Range Sum Query;
 * - Range Xor Query.
 *
 * Note: when the tree is constructed by
 * inserting each value one by one using set
 * and/or update, the time complexity is
 * actually O(n*log(n)).
 *
 * Note: it's recommended to remove the
 * pair<T, bool> set from SegTree<K, T>::Node
 * when it's not being used since it costs
 * a bunch of memory when many Segment Trees
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
     */
    struct Node {
        T value, lazy;
        pair<T, bool> set;

        Node() :
            lazy(0), set(0, false)
        {
            switch(K){
                case SegTreeKind::RMaxQ:
                    value = -INF;
                    break;
                case SegTreeKind::RMinQ:
                    value = INF;
                    break;
                case SegTreeKind::RSumQ:
                case SegTreeKind::RXorQ:
                default:
                    value = 0;
                    break;
            }
        }

        Node(const T value, const T lazy = 0) :
            value(value), lazy(lazy), set(0, false) {}

        /**
         * Checks if a value matches with this->value
         * according to the kind of the Segment Tree.
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
                        break;
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
                default:
                    break;
            }

            lazy = 0;
            set = {0, false};
        }

        /**
         * Merges two nodes into a new one according
         * to the kind of the Segment Tree.
         */
        static Node merge(const Node lhs, const Node rhs)
        {
            assert(lhs.lazy == 0 and rhs.lazy == 0);
            assert(!lhs.set.ss and !rhs.set.ss);
            switch(K){
                case SegTreeKind::RMaxQ:
                    return Node(max(lhs.value, rhs.value));
                case SegTreeKind::RMinQ:
                    return Node(min(lhs.value, rhs.value));
                case SegTreeKind::RSumQ:
                    return Node(lhs.value + rhs.value);
                case SegTreeKind::RXorQ:
                    return Node(lhs.value ^ rhs.value);
                default:
                    assert(false);
            }
        }
    };

    SegTree(const size_t arr_size) :
        tree(4*arr_size), arr_size(arr_size) {}

    SegTree(const vector<T> &arr) :
        SegTree(arr.size(), arr) {}

    SegTree(const size_t arr_size, const vector<T> &arr) :
        tree(4*arr_size), arr_size(arr_size)
    {
        build(0, arr_size-1, 0, arr);
    }

    /**
     * Finds the index of the first element over
     * the array that matches with value.
     *
     * It returns the size of the array when the
     * value doesn't match with any array value.
     *
     * Time Complexity: O(log(n)).
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
     * Where n is the size of the array.
     */
    T query(const size_t l, const size_t r)
    {
        assert(l <= r and r < arr_size);
        return query(0, arr_size-1, l, r, 0).value;
    }

    /**
     * Sets the ith array value to value.
     *
     * Time Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    void set(const size_t i, const T value)
    {
        assert(i < arr_size);
        set(i, i, value);
    }

    /**
     * Sets the array values in the range [l, r]
     * to value.
     *
     * Time Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    void set(const size_t l, const size_t r, const T value)
    {
        assert(l <= r and r < arr_size);
        set(0, arr_size-1, l, r, 0, value);
    }

    /**
     * Updates the ith array value according to
     * the kind of the Segment Tree.
     *
     * Time Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    void update(const size_t i, const T delta)
    {
        assert(i < arr_size);
        update(i, i, delta);
    }

    /**
     * Updates the array values in the range
     * [l, r] according to the kind of the
     * Segment Tree.
     *
     * Time Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    void update(const size_t l, const size_t r, const T delta)
    {
        assert(l <= r and r < arr_size);
        update(0, arr_size-1, l, r, 0, delta);
    }

    /**
     * Merges two trees into a new one according
     * to the kind of the Segment Tree.
     */
    static SegTree merge(const SegTree &lhs, const SegTree &rhs)
    {
        assert(lhs.arr_size == rhs.arr_size);

        SegTree result(lhs.arr_size);
        for(size_t i=0; i<4*lhs.arr_size; ++i)
            result.tree[i] = Node::merge(lhs.tree[i], rhs.tree[i]);
        return result;
    }

private:
    Node build(const size_t l, const size_t r, const size_t pos, const vector<T> &arr)
    {
        if(l == r)
            return tree[pos] = Node(arr[l]);

        size_t mid = (l + r)/2;
        return tree[pos] = Node::merge(build(l, mid, 2*pos+1, arr), build(mid+1, r, 2*pos+2, arr));
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

    Node query(const size_t l, const size_t r, const size_t i, const size_t j, const size_t pos)
    {
        propagate(l, r, pos);

        if(l > r or l > j or r < i)
            return Node();

        if(l >= i and r <= j)
            return tree[pos];

        size_t mid = (l + r)/2;
        return Node::merge(query(l, mid, i, j, 2*pos+1), query(mid+1, r, i, j, 2*pos+2));
    }

    Node set(const size_t l, const size_t r, const size_t i, const size_t j, const size_t pos, const T value)
    {
        propagate(l, r, pos);

        if(l > r or l > j or r < i)
            return tree[pos];

        if(l >= i and r <= j){
            tree[pos].set = {value, true};
            // it's important to propagate before returning and Node::merge.
            propagate(l, r, pos);
            return tree[pos];
        }

        size_t mid = (l + r)/2;
        return tree[pos] = Node::merge(set(l, mid, i, j, 2*pos+1, value), set(mid+1, r, i, j, 2*pos+2, value));
    }

    Node update(const size_t l, const size_t r, const size_t i, const size_t j, const size_t pos, const T delta)
    {
        propagate(l, r, pos);

        if(l > r or l > j or r < i)
            return tree[pos];

        if(l >= i and r <= j){
            tree[pos].lazy = delta;
            // it's important to propagate before returning and Node::merge.
            propagate(l, r, pos);
            return tree[pos];
        }

        size_t mid = (l + r)/2;
        return tree[pos] = Node::merge(update(l, mid, i, j, 2*pos+1, delta), update(mid+1, r, i, j, 2*pos+2, delta));
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
