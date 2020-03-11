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
 * Note: when the Tree is constructed by
 * inserting each value on by one using set
 * and/or update, the time complexity is
 * actually O(n*log(n)).
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the size of the array.
 */
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
        SegTreeKind kind;
        int value, lazy;
        pair<int, bool> set;

        Node(const SegTreeKind kind) :
            kind(kind), lazy(0), set(0, false)
        {
            switch(kind){
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

        Node(const SegTreeKind kind, const int value, const int lazy = 0) :
            kind(kind), value(value), lazy(lazy), set(0, false) {}

        /**
         * Checks if a value matches with this->value
         * according to the kind of the Segment Tree.
         */
        bool match(const int value) const
        {
            switch(kind){
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
         * Merges two nodes into a new one according
         * to the kind of the Segment Tree.
         */
        static Node merge(const SegTreeKind kind, const Node lhs, const Node rhs)
        {
            assert(lhs.lazy == 0 and rhs.lazy == 0);
            assert(!lhs.set.ss and !rhs.set.ss);
            switch(kind){
                case SegTreeKind::RMaxQ:
                    return Node(kind, max(lhs.value, rhs.value));
                case SegTreeKind::RMinQ:
                    return Node(kind, min(lhs.value, rhs.value));
                case SegTreeKind::RSumQ:
                    return Node(kind, lhs.value + rhs.value);
                case SegTreeKind::RXorQ:
                    return Node(kind, lhs.value ^ rhs.value);
                default:
                    assert(false);
            }
        }
    };

    SegTree(const SegTreeKind kind, const int arr_size) :
        kind(kind), tree(4*arr_size, Node(kind)), arr_size(arr_size) {}

    SegTree(const SegTreeKind kind, const vi &arr) :
        kind(kind), tree(4*arr.size(), Node(kind)), arr_size(arr.size())
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
    int find(const int value)
    {
        return find(0, arr_size-1, 0, value);
    }

    /**
     * Computes the ith array value.
     *
     * Time Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    int query(const int i)
    {
        assert(0 <= i and i < arr_size);
        return query(i, i);
    }

    /**
     * Computes the value corresponding to the
     * range [l, r] of the array.
     *
     * Time Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    int query(const int l, const int r)
    {
        assert(0 <= l and l <= r and r < arr_size);
        return query(0, arr_size-1, l, r, 0).value;
    }

    /**
     * Sets the ith array value to value.
     *
     * Time Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    void set(const int i, const int value)
    {
        assert(0 <= i and i < arr_size);
        set(i, i, value);
    }

    /**
     * Sets the array values in the range [l, r]
     * to value.
     *
     * Time Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    void set(const int l, const int r, const int value)
    {
        assert(0 <= l and l <= r and r < arr_size);
        set(0, arr_size-1, l, r, 0, value);
    }

    /**
     * Updates the ith array value according to
     * the kind of the Segment Tree.
     *
     * Time Complexity: O(log(n)).
     * Where n is the size of the array.
     */
    void update(const int i, const int delta)
    {
        assert(0 <= i and i < arr_size);
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
    void update(const int l, const int r, const int delta)
    {
        assert(0 <= l and l <= r and r < arr_size);
        update(0, arr_size-1, l, r, 0, delta);
    }

private:
    Node build(const int l, const int r, const int pos, const vi &arr)
    {
        if(l == r)
            return tree[pos] = Node(kind, arr[l]);

        int mid = (l + r)/2;
        return tree[pos] = Node::merge(kind, build(l, mid, 2*pos+1, arr), build(mid+1, r, 2*pos+2, arr));
    }

    int find(const int l, const int r, const int pos, const int value)
    {
        propagate(l, r, pos);

        if(!tree[pos].match(value))
            return arr_size;
        else if(l == r)
            return l;

        int mid = (l + r)/2;
        int ans = find(l, mid, 2*pos+1, value);
        return ans != arr_size? ans : find(mid+1, r, 2*pos+2, value);
    }

    Node query(const int l, const int r, const int i, const int j, const int pos)
    {
        propagate(l, r, pos);

        if(l > r or l > j or r < i)
            return Node(kind);

        if(l >= i and r <= j)
            return tree[pos];

        int mid = (l + r)/2;
        return Node::merge(kind, query(l, mid, i, j, 2*pos+1), query(mid+1, r, i, j, 2*pos+2));
    }

    Node set(const int l, const int r, const int i, const int j, const int pos, const int value)
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

        int mid = (l + r)/2;
        return tree[pos] = Node::merge(kind, set(l, mid, i, j, 2*pos+1, value), set(mid+1, r, i, j, 2*pos+2, value));
    }

    Node update(const int l, const int r, const int i, const int j, const int pos, const int delta)
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

        int mid = (l + r)/2;
        return tree[pos] = Node::merge(kind, update(l, mid, i, j, 2*pos+1, delta), update(mid+1, r, i, j, 2*pos+2, delta));
    }

    void propagate(int l, int r, int pos)
    {
        int lazy = tree[pos].lazy;
        pair<int, bool> set = tree[pos].set;

        if(lazy == 0 and !set.ss)
            return;

        if(set.ss){
            switch (kind){
                case SegTreeKind::RMaxQ:
                case SegTreeKind::RMinQ:
                    tree[pos].value = set.ff;
                    break;
                case SegTreeKind::RSumQ:
                    tree[pos].value = (r - l + 1)*set.ff;
                    break;
                case SegTreeKind::RXorQ:
                    tree[pos].value = ((r - l + 1)%2)*set.ff;
                    break;
                default:
                    break;
            }
        }

        switch (kind){
            case SegTreeKind::RMaxQ:
            case SegTreeKind::RMinQ:
                tree[pos].value += lazy;
                break;
            case SegTreeKind::RSumQ:
                tree[pos].value += (r - l + 1)*lazy;
                break;
            case SegTreeKind::RXorQ:
            default:
                break;
        }

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

        tree[pos].lazy = 0;
        tree[pos].set = {0, false};
    }

    SegTreeKind kind;
    vector<Node> tree;
    int arr_size;
};
