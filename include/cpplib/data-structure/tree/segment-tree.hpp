#pragma once
#include <cpplib/stdinc.hpp>

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
template<typename T>
struct STNodeB {
    T value, lazy = 0;

    STNodeB()
    {
        // meant to create a node with default value.
    }

    STNodeB(const T value) :
        value(value)
    {
        // meant to initialize a node with a defined value.
    }

    STNodeB(const STNodeB &lhs, const STNodeB &rhs)
    {
        // meant to create a node by merging lhs and rhs.
    }

    /**
     * Checks if a value matches with
     * this->value according to the
     * node implementation.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    virtual bool match(const T value) const = 0;

    /**
     * Updates the current node according to
     * the node implementation.
     *
     * Time Complexity: O(1).
     * Space Complexity: O(1).
     */
    virtual void update(const size_t range) = 0;
};

/**
 * Segment Tree.
 *
 * Arranges data in a binary tree so that
 * it is possible to perform range queries
 * and modifications over an array
 * effectively.
 *
 * Note: when the tree is constructed by
 * inserting each value one by one using
 * update the time complexity is actually
 * O(n*log(n)).
 *
 * Time Complexity: O(n).
 * Space Complexity: O(n).
 * Where n is the size of the array.
 */
template<typename Node, typename T>
class SegTreeB
{
public:
    SegTreeB() = delete;

    SegTreeB(const size_t arr_size) :
        tree(4*arr_size), arr_size(arr_size) {}

    SegTreeB(const vector<T> &arr) :
        SegTreeB(arr.size(), arr) {}

    SegTreeB(const size_t arr_size, const vector<T> &arr) :
        tree(4*arr_size), arr_size(arr_size)
    {
        build(0, arr_size-1, 0, arr);
    }

    SegTreeB(const SegTreeB &lhs, const SegTreeB &rhs) :
        SegTreeB(lhs.arr_size)
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
        return query(0, arr_size-1, l, r, 0).value;
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

    Node query(const size_t l, const size_t r, const size_t i, const size_t j, const size_t pos)
    {
        propagate(l, r, pos);

        if(l > j or r < i)
            return Node();

        if(l >= i and r <= j)
            return tree[pos];

        size_t mid = (l + r)/2;
        return Node(query(l, mid, i, j, 2*pos+1), query(mid+1, r, i, j, 2*pos+2));
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

    virtual void propagate(const size_t l, const size_t r, const size_t pos)
    {
        T lazy = tree[pos].lazy;

        if(lazy == 0)
            return;

        tree[pos].update(r - l + 1);

        if(l != r){
            tree[2*pos+1].lazy += lazy;
            tree[2*pos+2].lazy += lazy;
        }
    }

protected:
    vector<Node> tree;
    size_t arr_size;
};

/**
 * Segment Tree Node.
 *
 * Note: this implementation only adds
 * required variables to perform set
 * operations.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
template<typename T>
struct STNodeSB : STNodeB<T> {
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
};

/**
 * Segment Tree.
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
    SegTreeSB() = delete;

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
        set(0, this->arr_size-1, l, r, 0, value);
    }

private:
    using super_type = SegTreeB<NodeS, T>;

    NodeS set(const size_t l, const size_t r, const size_t i, const size_t j, const size_t pos, const T value)
    {
        propagate(l, r, pos);

        if(l > j or r < i)
            return this->tree[pos];

        if(l >= i and r <= j){
            this->tree[pos].set = {value, true};
            // it's important to propagate before returning and merge nodes.
            propagate(l, r, pos);
            return this->tree[pos];
        }

        size_t mid = (l + r)/2;
        return this->tree[pos] = NodeS(set(l, mid, i, j, 2*pos+1, value), set(mid+1, r, i, j, 2*pos+2, value));
    }

    void propagate(const size_t l, const size_t r, const size_t pos)
    {
        T lazy = this->tree[pos].lazy;
        pair<T, bool> set = this->tree[pos].set;

        if(lazy == 0 and !set.ss)
            return;

        this->tree[pos].update(r - l + 1);

        if(l != r){
            if(set.ss){
                this->tree[2*pos+1].set = set;
                this->tree[2*pos+2].set = set;

                this->tree[2*pos+1].lazy = 0;
                this->tree[2*pos+2].lazy = 0;
            }
            this->tree[2*pos+1].lazy += lazy;
            this->tree[2*pos+2].lazy += lazy;
        }
    }
};

enum class STKind
{
    RMaxQ,
    RMinQ,
    RSumQ,
    RXorQ,
};

const STKind RMaxQ = STKind::RMaxQ;
const STKind RMinQ = STKind::RMinQ;
const STKind RSumQ = STKind::RSumQ;
const STKind RXorQ = STKind::RXorQ;

/**
 * Returns the default value according to
 * the SegmentTreeKind.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
template<typename T>
T default_value(STKind k){
    switch(k){
        case RMaxQ:
            return -INF;
        case RMinQ:
            return INF;
        case RSumQ:
            return 0;
        case RXorQ:
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
template<typename T>
T merge_values(STKind k, const T lhs, const T rhs){
    switch(k){
        case RMaxQ:
            return max(lhs, rhs);
        case RMinQ:
            return min(lhs, rhs);
        case RSumQ:
            return lhs + rhs;
        case RXorQ:
            return lhs ^ rhs;
        default:
            assert(false);
    }
}

/**
 * Segment Tree Node.
 *
 * Note: this is a node implementation
 * for common use cases such as:
 * - Range Max Query;
 * - Range Min Query;
 * - Range Sum Query;
 * - Range Xor Query.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
template<STKind K, typename T>
struct STNode : STNodeB<T> {
    using super_type = STNodeB<T>;

    STNode() :
        super_type(default_value<T>(K)) {}

    STNode(const T value) :
        super_type(value) {}

    STNode(const STNode &lhs, const STNode &rhs) :
        super_type(merge_values<T>(K, lhs.value, rhs.value))
    {
        assert(lhs.lazy == 0 and rhs.lazy == 0);
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
            case RMaxQ:
                return this->value >= value;
                // return this->value > value;
            case RMinQ:
                return this->value <= value;
                // return this->value < value;
            case RSumQ:
            case RXorQ:
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
        switch (K){
            case RMaxQ:
            case RMinQ:
                this->value += this->lazy;
                break;
            case RSumQ:
                this->value += range*this->lazy;
                break;
            case RXorQ:
                break;
            default:
                assert(false);
        }
        this->lazy = 0;
    }
};

template<STKind K, typename T>
using SegTree = SegTreeB<STNode<K, T>, T>;

/**
 * Segment Tree Node.
 *
 * Note: this implementation only
 * adds set operations.
 *
 * Time Complexity: O(1).
 * Space Complexity: O(1).
 */
template<STKind K, typename T>
struct STNodeS : STNodeSB<T> {
    using super_type = STNodeSB<T>;

    STNodeS() :
        super_type(default_value<T>(K)) {}

    STNodeS(const T value) :
        super_type(value) {}

    STNodeS(const STNodeS &lhs, const STNodeS &rhs) :
        super_type(merge_values<T>(K, lhs.value, rhs.value))
    {
        assert(lhs.lazy == 0 and rhs.lazy == 0);
        assert(!lhs.set.ss and !rhs.set.ss);
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
            case RMaxQ:
                return this->value >= value;
                // return this->value > value;
            case RMinQ:
                return this->value <= value;
                // return this->value < value;
            case RSumQ:
            case RXorQ:
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
        if(this->set.ss){
            switch (K){
                case RMaxQ:
                case RMinQ:
                    this->value = this->set.ff;
                    break;
                case RSumQ:
                    this->value = range*this->set.ff;
                    break;
                case RXorQ:
                    this->value = (range%2)*this->set.ff;
                    break;
                default:
                    assert(false);
            }
        }

        switch (K){
            case RMaxQ:
            case RMinQ:
                this->value += this->lazy;
                break;
            case RSumQ:
                this->value += range*this->lazy;
                break;
            case RXorQ:
                break;
            default:
                assert(false);
        }

        this->lazy = 0;
        this->set = {0, false};
    }
};

template<STKind K, typename T>
using SegTreeS = SegTreeSB<STNodeS<K, T>, T>;
