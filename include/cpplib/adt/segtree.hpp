#pragma once
#include <cpplib/adt/segtreeb.hpp>
#include <cpplib/stdinc.hpp>

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
T default_value(STKind k)
{
    switch(k) {
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
T merge_values(STKind k, const T lhs, const T rhs)
{
    switch(k) {
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
struct STNode : STNodeB<T>
{
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
        switch(K) {
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
        switch(K) {
            case RMaxQ:
            case RMinQ:
                this->value += this->lazy;
                break;
            case RSumQ:
                this->value += range * this->lazy;
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
